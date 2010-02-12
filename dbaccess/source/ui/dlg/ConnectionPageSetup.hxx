/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
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

    class IDatabaseSettingsDialog;
    //=========================================================================
    //= OConnectionTabPageSetup
    //=========================================================================

    /** implements the connection page of the data source properties dialog.
    */
    class OConnectionTabPageSetup : public OConnectionHelper
    {
        sal_Bool			m_bUserGrabFocus : 1;
    protected:

        FixedText           m_aFT_HelpText;

        // called when the test connection button was clicked
        DECL_LINK(OnEditModified,Edit*);

    public:
        static	OGenericAdministrationPage*	CreateDbaseTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateMSAccessTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateAdabasTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateADOTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateODBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet );
        static	OGenericAdministrationPage*	CreateUserDefinedTabPage( Window* pParent, const SfxItemSet& _rAttrSet );


        virtual	BOOL		FillItemSet	(SfxItemSet& _rCoreAttrs);

        virtual void		implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);
        virtual sal_Bool    commitPage( CommitPageReason _eReason );


        inline void enableConnectionURL() { m_aConnectionURL.SetReadOnly(sal_False); }
        inline void disableConnectionURL() { m_aConnectionURL.SetReadOnly(); }

        /** changes the connection URL.
            <p>The new URL must be of the type which is currently selected, only the parts which do not
            affect the type may be changed (compared to the previous URL).</p>
        */
        void	changeConnectionURL( const String& _rNewDSN );
        String	getConnectionURL( ) const;


    protected:
        OConnectionTabPageSetup(Window* pParent, USHORT _rId, const SfxItemSet& _rCoreAttrs, USHORT _nHelpTextResId, USHORT _nHeaderResId, USHORT _nUrlResId);
        virtual bool checkTestConnection();
            // nControlFlags ist eine Kombination der CBTP_xxx-Konstanten
        virtual ~OConnectionTabPageSetup();
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif 
