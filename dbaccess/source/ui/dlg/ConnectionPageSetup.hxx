/*************************************************************************
 *
 *  $RCSfile: ConnectionPageSetup.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: pjunck $ $Date: 2004-10-27 12:58:59 $
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): Berend Cornelius
 *
 *
 ************************************************************************/


#ifndef DBAUI_CONNECTIONPAGESETUP_HXX
#define DBAUI_CONNECTIONPAGESETUP_HXX
#ifndef DBAUI_CONNECTIONHELPER_HXX
#include "ConnectionHelper.hxx"
#endif

#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif

#ifndef _SV_FIELD_HXX 
#include <vcl/field.hxx>
#endif


//.........................................................................
namespace dbaui
{
//.........................................................................
/*	// #106016# --------------
    enum IS_PATH_EXIST
    {
        PATH_NOT_EXIST = 0,
        PATH_EXIST,
        PATH_NOT_KNOWN
    };
    */

    class IAdminHelper;
    //=========================================================================
    //= OConnectionTabPageSetup
    //=========================================================================

    /** implements the connection page of teh data source properties dialog.
    */
    class OConnectionTabPageSetup : public OConnectionHelper
    {

        ODsnTypeCollection*	m_pCollection;	/// the DSN type collection instance
        sal_Bool			m_bUserGrabFocus : 1;
    protected:

        FixedText           m_aFT_HelpText;

        // called when the test connection button was clicked
        DECL_LINK(OnTestConnectionClickHdl,PushButton*);
        DECL_LINK(OnEditModified,Edit*);

    public:
        static	OGenericAdministrationPage*	CreateDbaseTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateMSAccessTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateAdabasTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateADOTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateODBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet );


        virtual void SetServiceFactory(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > _rxORB)
        {
            OConnectionHelper::SetServiceFactory(_rxORB);
//			m_aET_Connection.initializeTypeCollection(m_xORB);
        }


        virtual	BOOL		FillItemSet	(SfxItemSet& _rCoreAttrs);

        virtual void		implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);
        virtual sal_Bool    commitPage(COMMIT_REASON _eReason);


        inline void enableConnectionURL() { m_aET_Connection.SetReadOnly(sal_False); }
        inline void disableConnectionURL() { m_aET_Connection.SetReadOnly(); }

        /** changes the connection URL.
            <p>The new URL must be of the type which is currently selected, only the parts which do not
            affect the type may be changed (compared to the previous URL).</p>
        */
        void	changeConnectionURL( const String& _rNewDSN );
        String	getConnectionURL( ) const;


    protected:
        OConnectionTabPageSetup(Window* pParent, USHORT _rId, const SfxItemSet& _rCoreAttrs, USHORT _nHelpTextResId, USHORT _nHeaderResId, USHORT _nUrlResId, sal_Bool _bgetConnection = sal_True);
        virtual bool checkTestConnection();
        void toggleURLControlGroup(BOOL _bEnable);
            // nControlFlags ist eine Kombination der CBTP_xxx-Konstanten
        virtual ~OConnectionTabPageSetup();

    private:


        /** enables the test connection button, if allowed
        */


        /** opens the FileOpen dialog and asks for a FileName
            @param	_sFilterName
                The filter name.
            @param	_sExtension
                The filter extension.
        */
// void askForFileName(const ::rtl::OUString& _sFilterName, const ::rtl::OUString& _sExtension);
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif 
