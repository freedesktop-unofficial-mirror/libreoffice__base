/*************************************************************************
 *
 *  $RCSfile: dbexchange.cxx,v $
 *
 *  $Revision: 1.18 $
 *
 *  last change: $Author: oj $ $Date: 2002-03-21 07:21:24 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef DBAUI_DBEXCHANGE_HXX
#include "dbexchange.hxx"
#endif
#ifndef _SOT_FORMATS_HXX
#include <sot/formats.hxx>
#endif
#ifndef _SOT_STORAGE_HXX 
#include <sot/storage.hxx>
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef DBAUI_TOKENWRITER_HXX
#include "TokenWriter.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <svx/dataaccessdescriptor.hxx>
#endif

namespace dbaui
{
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::sdb;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::util;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::datatransfer;
    using namespace ::svx;

    // -----------------------------------------------------------------------------
    ODataClipboard::ODataClipboard(
                    const ::rtl::OUString&	_rDatasource,
                    const sal_Int32			_nCommandType,
                    const ::rtl::OUString&	_rCommand,
                    const Reference< XConnection >& _rxConnection,
                    const Reference< XNumberFormatter >& _rxFormatter,
                    const Reference< XMultiServiceFactory >& _rxORB)
        :ODataAccessObjectTransferable( _rDatasource, _nCommandType, _rCommand, _rxConnection )
        ,m_pHtml(NULL)
        ,m_pRtf(NULL)
    {
        m_pHtml = new OHTMLImportExport(getDescriptor(), _rxORB, _rxFormatter);
        m_xHtml = m_pHtml;

        m_pRtf = new ORTFImportExport(getDescriptor(), _rxORB, _rxFormatter);
        m_xRtf = m_pRtf;
    }

    // -----------------------------------------------------------------------------
    ODataClipboard::ODataClipboard(	const Reference< XPropertySet >& _rxLivingForm, 
                                    const Sequence< Any >& _rSelectedRows,
                                    const Reference< XResultSet>& _rxResultSet)
        :ODataAccessObjectTransferable( _rxLivingForm )
        ,m_pHtml(NULL)
        ,m_pRtf(NULL)
    {
        getDescriptor()[daSelection]	<<= _rSelectedRows;
        getDescriptor()[daCursor]		<<= _rxResultSet;
        addCompatibleSelectionDescription( _rSelectedRows );
    }

    // -----------------------------------------------------------------------------
    sal_Bool ODataClipboard::WriteObject( SotStorageStreamRef& rxOStm, void* pUserObject, sal_uInt32 nUserObjectId, const ::com::sun::star::datatransfer::DataFlavor& rFlavor )
    {
        if (nUserObjectId == SOT_FORMAT_RTF || nUserObjectId == SOT_FORMATSTR_ID_HTML || nUserObjectId == SOT_FORMATSTR_ID_HTML_SIMPLE)
        {
            ODatabaseImportExport* pExport = reinterpret_cast<ODatabaseImportExport*>(pUserObject);
            if(pExport)
            {
                pExport->setStream(&rxOStm);
                return pExport->Write();
            }
        }
        return sal_False;
    }

    // -----------------------------------------------------------------------------
    void ODataClipboard::AddSupportedFormats()
    {
        // RTF?
        if (m_pRtf)
            AddFormat(SOT_FORMAT_RTF);

        // HTML?
        if (m_pHtml)
        {
            AddFormat(SOT_FORMATSTR_ID_HTML);
            AddFormat(SOT_FORMATSTR_ID_HTML_SIMPLE);
        }

        ODataAccessObjectTransferable::AddSupportedFormats();
    }

    // -----------------------------------------------------------------------------
    sal_Bool ODataClipboard::GetData( const DataFlavor& rFlavor )
    {
        ULONG nFormat = SotExchange::GetFormat(rFlavor);
        switch (nFormat)
        {
            case SOT_FORMAT_RTF:
                m_pRtf->initialize();
                return SetObject(m_pRtf, SOT_FORMAT_RTF, rFlavor);

            case SOT_FORMATSTR_ID_HTML:
                m_pHtml->initialize();
                return SetObject(m_pHtml, SOT_FORMATSTR_ID_HTML, rFlavor);

            case SOT_FORMATSTR_ID_HTML_SIMPLE:
                m_pHtml->initialize();
                return SetObject(m_pHtml, SOT_FORMATSTR_ID_HTML_SIMPLE, rFlavor);
        }

        return ODataAccessObjectTransferable::GetData( rFlavor );
    }

    // -----------------------------------------------------------------------------
    void ODataClipboard::ObjectReleased()
    {
        m_pHtml = NULL;
        m_pRtf = NULL;
        m_xHtml	= m_xRtf = NULL;

        ODataAccessObjectTransferable::ObjectReleased( );
    }

    // -----------------------------------------------------------------------------
}








