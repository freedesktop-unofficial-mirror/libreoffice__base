/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbui.hxx"

#include "ConnectionPageSetup.hxx"
#include "AutoControlsDef.hrc"
#include "dbadminsetup.hrc"
#include "dbu_dlg.hrc"
#include <svl/itemset.hxx>
#include <unotools/pathoptions.hxx>
#include <svl/stritem.hxx>
#include <svl/eitem.hxx>
#include <svl/intitem.hxx>
#include "dsitems.hxx"
#include "dbaccess_helpid.hrc"
#include "localresaccess.hxx"
#include <osl/process.h>
#include <vcl/msgbox.hxx>
#include <sfx2/filedlghelper.hxx>
#include "dbadmin.hxx"
#include "dbadmin.hrc"
#include <comphelper/types.hxx>
#include <vcl/stdtext.hxx>
#include "sqlmessage.hxx"
#include "odbcconfig.hxx"
#include "dsselect.hxx"
#include <svl/filenotation.hxx>
#include "dbustrings.hrc"
#include <com/sun/star/ui/dialogs/XFolderPicker.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/task/XInteractionHandler.hpp>
#include <com/sun/star/ucb/XProgressHandler.hpp>
#include <com/sun/star/sdbc/XConnection.hpp>
#include "UITools.hxx"
#include <unotools/localfilehelper.hxx>
#include <unotools/ucbhelper.hxx>
#include <ucbhelper/commandenvironment.hxx>
#include "finteraction.hxx"
#include <connectivity/CommonTools.hxx>
#include <tools/urlobj.hxx>
#include <sfx2/docfilt.hxx>
#include <vcl/mnemonic.hxx>

//.........................................................................
namespace dbaui
{
//.........................................................................
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::ucb;
    using namespace ::com::sun::star::ui::dialogs;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::container;
    using namespace ::dbtools;
    using namespace ::svt;



    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateDbaseTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_DBASE,    _rAttrSet, STR_DBASE_HELPTEXT,    STR_DBASE_HEADERTEXT,    STR_DBASE_PATH_OR_FILE);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }


    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateMSAccessTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_MSACCESS, _rAttrSet, STR_MSACCESS_HELPTEXT, STR_MSACCESS_HEADERTEXT, STR_MSACCESS_MDB_FILE);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }

    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateAdabasTabPage( Window* pParent,	const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_ADABAS, _rAttrSet, STR_ADABAS_HELPTEXT, STR_ADABAS_HEADERTEXT, STR_ADABAS_DATABASE_NAME);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }

    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateADOTabPage( Window* pParent,	const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_ADO, _rAttrSet, STR_ADO_HELPTEXT, STR_ADO_HEADERTEXT, STR_COMMONURL);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }

    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateODBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_ODBC, _rAttrSet, STR_ODBC_HELPTEXT, STR_ODBC_HEADERTEXT, STR_NAME_OF_ODBC_DATASOURCE);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }

    OGenericAdministrationPage*	OConnectionTabPageSetup::CreateUserDefinedTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        OConnectionTabPageSetup* oDBWizardPage = new OConnectionTabPageSetup( pParent, PAGE_DBWIZARD_USERDEFINED, _rAttrSet, USHRT_MAX, USHRT_MAX, STR_COMMONURL);
        oDBWizardPage->FreeResource();
        return oDBWizardPage;
    }


    //========================================================================
    //= OConnectionTabPageSetup
    //========================================================================
    DBG_NAME(OConnectionTabPageSetup)
    OConnectionTabPageSetup::OConnectionTabPageSetup(Window* pParent, sal_uInt16 _rId, const SfxItemSet& _rCoreAttrs, sal_uInt16 _nHelpTextResId, sal_uInt16 _nHeaderResId, sal_uInt16 _nUrlResId)
        :OConnectionHelper(pParent, ModuleRes(_rId), _rCoreAttrs)
        ,m_bUserGrabFocus(sal_True)
        ,m_aFT_HelpText(this, ModuleRes(FT_AUTOWIZARDHELPTEXT))
    {
        DBG_CTOR(OConnectionTabPageSetup, NULL);

        if ( USHRT_MAX != _nHelpTextResId )
        {
            String sHelpText = String(ModuleRes(_nHelpTextResId));
            m_aFT_HelpText.SetText(sHelpText);
        }
        else
            m_aFT_HelpText.Hide();


        if ( USHRT_MAX != _nHeaderResId )
            SetHeaderText(FT_AUTOWIZARDHEADER, _nHeaderResId);

        if ( USHRT_MAX != _nUrlResId )
        {
            String sLabelText = String(ModuleRes(_nUrlResId));
            m_aFT_Connection.SetText(sLabelText);
            if ( USHRT_MAX == _nHelpTextResId )
            {
                Point aPos = m_aFT_HelpText.GetPosPixel();
                Point aFTPos = m_aFT_Connection.GetPosPixel();
                Point aEDPos = m_aConnectionURL.GetPosPixel();
                Point aPBPos = m_aPB_Connection.GetPosPixel();

                aEDPos.Y() = aPos.Y() + aEDPos.Y() - aFTPos.Y();
                aPBPos.Y() = aPos.Y() + aPBPos.Y() - aFTPos.Y();
                aFTPos.Y() = aPos.Y();
                m_aFT_Connection.SetPosPixel(aFTPos);
                m_aConnectionURL.SetPosPixel(aEDPos);
                m_aPB_Connection.SetPosPixel(aPBPos);
            }
        }
        else
            m_aFT_Connection.Hide();

        m_aConnectionURL.SetModifyHdl(LINK(this, OConnectionTabPageSetup, OnEditModified));

        SetRoadmapStateValue(sal_False);
    }

    // -----------------------------------------------------------------------
    OConnectionTabPageSetup::~OConnectionTabPageSetup()
    {
        DBG_DTOR(OConnectionTabPageSetup,NULL);
    }

    // -----------------------------------------------------------------------
    void OConnectionTabPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        m_eType = m_pAdminDialog->getDatasourceType(_rSet);
        // special handling for oracle, this can only happen
        // if the user enters the same url as used for Oracle and we are on the JDBC path
        //! TODO
        //if (  ::dbaccess::DST_ORACLE_JDBC == m_eType )
        //    m_eType =  ::dbaccess::DST_JDBC;

        OConnectionHelper::implInitControls(_rSet, _bSaveValue);

        //! TODO
        //if ( m_eType >=  ::dbaccess::DST_USERDEFINE1 )
        //{
        //	String sDisplayName = m_pCollection->getTypeDisplayName(m_eType);
        //	FixedText* ppTextControls[] ={&m_aFT_Connection};
        //	for (size_t i = 0; i < SAL_N_ELEMENTS(ppTextControls); ++i)
        //	{
        //		ppTextControls[i]->SetText(sDisplayName);
        //	}
        //}

        callModifiedHdl();
    }
    // -----------------------------------------------------------------------
       sal_Bool OConnectionTabPageSetup::commitPage( ::svt::WizardTypes::CommitPageReason /*_eReason*/ )
    {
        return commitURL();
    }

    // -----------------------------------------------------------------------
    sal_Bool OConnectionTabPageSetup::FillItemSet(SfxItemSet& _rSet)
    {
        sal_Bool bChangedSomething = sal_False;
        fillString(_rSet,&m_aConnectionURL, DSID_CONNECTURL, bChangedSomething);
        return bChangedSomething;
    }
    // -----------------------------------------------------------------------
    bool OConnectionTabPageSetup::checkTestConnection()
    {
        return !m_aConnectionURL.IsVisible() || (m_aConnectionURL.GetTextNoPrefix().Len() != 0);
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OConnectionTabPageSetup, OnEditModified, Edit*, /*_pEdit*/)
    {
        SetRoadmapStateValue(checkTestConnection());
        callModifiedHdl();
        return 0L;
    }
//.........................................................................
}	// namespace dbaui
//.........................................................................


/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
