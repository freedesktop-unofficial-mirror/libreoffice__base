/*************************************************************************
 *
 *  $RCSfile: dbexchange.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: fs $ $Date: 2001-03-28 15:41:04 $
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
#define DBAUI_DBEXCHANGE_HXX

#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_ 
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_ 
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSER_HPP_ 
#include <com/sun/star/sdb/XSQLQueryComposer.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _TRANSFER_HXX 
#include <svtools/transfer.hxx>
#endif

namespace dbaui
{

#define DCF_OBJECT_DESCRIPTOR		0x0001
#define DCF_HTML_TABLE				0x0002
#define DCF_RTF_TABLE				0x0004
#define DCF_ALL						DCF_OBJECT_DESCRIPTOR | DCF_HTML_TABLE | DCF_RTF_TABLE

    class ORTFImportExport;
    class OHTMLImportExport;
    class ODataClipboard : public TransferableHelper
    {
        ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > m_aSeq;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener> m_xHtml;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener> m_xRtf;
        OHTMLImportExport*		m_pHtml;
        ORTFImportExport*		m_pRtf;

        sal_Int32				m_nFormats;

        sal_Int32				m_nObjectType;
            // the object type as extracted from the property sequence given in the ctor.
            // We need different clipboard formats for queries and tables, so we need this information
        ::rtl::OUString			m_sCompatibleObjectDescription;
            // needed to provide a SOT_FORMATSTR_ID_SBA_DATAEXCHANGE format

    public:
        ODataClipboard(
            const ::rtl::OUString&	_rDatasource,
            const sal_Int32			_nCommandType,
            const ::rtl::OUString&	_rCommand,
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection,
            const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxFormatter,
            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB,
            const sal_Int32 _nFormats = DCF_ALL
        );

        /** with this ctor, only the object descriptor format will be provided
        */
        ODataClipboard(
            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxLivingForm,
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer >& _rxComposer
        );
            // (the query composer could be obtained from the connection which is a property of the form,
            // but for simplity we pass it here .... if somebody needs this class, having a form, but no composer,
            // we can adjust this

        /// add a row to the object descriptor
        void addRow(sal_Int32 _nRow);

    protected:
        virtual void		AddSupportedFormats();
        virtual sal_Bool	GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
        virtual void		ObjectReleased();
        virtual sal_Bool	WriteObject( SotStorageStreamRef& rxOStm, void* pUserObject, sal_uInt32 nUserObjectId, const ::com::sun::star::datatransfer::DataFlavor& rFlavor );
    };
}

#endif //  DBAUI_DBEXCHANGE_HXX







