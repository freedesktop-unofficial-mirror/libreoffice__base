/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: DBSetupConnectionPages.cxx,v $
 * $Revision: 1.19.18.1 $
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
#include "precompiled_dbaccess.hxx"
#ifndef DBAUI_DBSETUPCONNECTIONPAGES_HXX
#include "DBSetupConnectionPages.hxx"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _DBAUI_AUTOCONTROLS_HRC_
#include "AutoControls.hrc"
#endif
#ifndef _DBAUI_DBADMINSETUP_HRC_
#include "dbadminsetup.hrc"
#endif
#ifndef _SFXITEMSET_HXX 
#include <svtools/itemset.hxx>
#endif
#ifndef _SFXSTRITEM_HXX 
#include <svtools/stritem.hxx>
#endif
#ifndef _SFXENUMITEM_HXX 
#include <svtools/eitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX 
#include <svtools/intitem.hxx>
#endif
#ifndef _DBAUI_DATASOURCEITEMS_HXX_
#include "dsitems.hxx"
#endif
#include "dsnItem.hxx"
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef _DBAUI_LOCALRESACCESS_HXX_
#include "localresaccess.hxx"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SV_MNEMONIC_HXX
#include <vcl/mnemonic.hxx>
#endif
#ifndef _SVTOOLS_CJKOPTIONS_HXX
#include <svtools/cjkoptions.hxx>
#endif
#include <jvmaccess/virtualmachine.hxx>
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef DBAUI_DRIVERSETTINGS_HXX
#include "DriverSettings.hxx"
#endif
#ifndef _DBAUI_DBADMIN_HXX_
#include "dbadmin.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif

#ifndef _COM_SUN_STAR_UI_DIALOGS_XFOLDERPICKER_HPP_
#include <com/sun/star/ui/dialogs/XFolderPicker.hpp>
#endif
// #106016# ------------------------------------
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#include <com/sun/star/sdbc/XDriverAccess.hpp>
#include "dbustrings.hrc"
#ifndef SVTOOLS_FILENOTATION_HXX_
#include <svtools/filenotation.hxx>
#endif

#ifndef _UNOTOOLS_LOCALFILEHELPER_HXX
#include <unotools/localfilehelper.hxx>
#endif
#ifndef _UNOTOOLS_UCBHELPER_HXX
#include <unotools/ucbhelper.hxx>
#endif
#ifndef _UCBHELPER_COMMANDENVIRONMENT_HXX
#include <ucbhelper/commandenvironment.hxx>
#endif
#ifndef DBAUI_FILEPICKER_INTERACTION_HXX
#include "finteraction.hxx"
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif

#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif

#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif

#ifndef SVTOOLS_INC_ROADMAPWIZARD_HXX
#include <svtools/roadmapwizard.hxx>
#endif

#ifndef DBAUI_TEXTCONNECTIONHELPER_HXX
#include "TextConnectionHelper.hxx"
#endif


//.........................................................................
namespace dbaui
{
//.........................................................................
using namespace ::com::sun::star;
//	using namespace ::com::sun::star::ucb;
//	using namespace ::com::sun::star::ui::dialogs;
//	using namespace ::com::sun::star::sdbc;
//	using namespace ::com::sun::star::beans;
//	using namespace ::com::sun::star::lang;
//	using namespace ::com::sun::star::container;
//	using namespace ::dbtools;
//	using namespace ::svt;

    OGenericAdministrationPage*	OTextConnectionPageSetup::CreateTextTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OTextConnectionPageSetup( pParent, _rAttrSet ) );
    }


    //========================================================================
    //= OTextConnectionPageSetup
    //========================================================================
DBG_NAME(OTextConnectionPageSetup)
//------------------------------------------------------------------------
    OTextConnectionPageSetup::OTextConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_TEXT, _rCoreAttrs, STR_TEXT_HELPTEXT, STR_TEXT_HEADERTEXT, STR_TEXT_PATH_OR_FILE)
    {
        DBG_CTOR(OTextConnectionPageSetup,NULL);

        m_pTextConnectionHelper = new OTextConnectionHelper( this, TC_EXTENSION | TC_SEPARATORS );
        m_pTextConnectionHelper->SetClickHandler(LINK( this, OTextConnectionPageSetup, ImplGetExtensionHdl ) );

        FreeResource();
    }


    // -----------------------------------------------------------------------
    OTextConnectionPageSetup::~OTextConnectionPageSetup()
    {
        DELETEZ(m_pTextConnectionHelper);
    
        DBG_DTOR(OTextConnectionPageSetup,NULL);
    }   

    IMPL_LINK(OTextConnectionPageSetup, ImplGetExtensionHdl, OTextConnectionHelper*, /*_pTextConnectionHelper*/)
    {                            
        SetRoadmapStateValue((m_pTextConnectionHelper->GetExtension().Len() > 0) && OConnectionTabPageSetup::checkTestConnection());
        callModifiedHdl();
        return sal_True;
    }


    bool OTextConnectionPageSetup::checkTestConnection()
    {
        bool bDoEnable = OConnectionTabPageSetup::checkTestConnection();
        bDoEnable = (m_pTextConnectionHelper->GetExtension().Len() > 0) && bDoEnable;
        return bDoEnable;
    }

    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillControls(_rControlList);
        m_pTextConnectionHelper->fillControls(_rControlList);
    }
    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillWindows(_rControlList);
        m_pTextConnectionHelper->fillWindows(_rControlList);
    }
    // -----------------------------------------------------------------------
    void OTextConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // first check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);
        OConnectionTabPageSetup::implInitControls( _rSet, _bSaveValue);
        m_pTextConnectionHelper->implInitControls(_rSet, bValid);
    }


    // -----------------------------------------------------------------------
    sal_Bool OTextConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        bChangedSomething = m_pTextConnectionHelper->FillItemSet(_rSet, bChangedSomething);
        return bChangedSomething;
    }

    
    sal_Bool OTextConnectionPageSetup::prepareLeave(){
        return m_pTextConnectionHelper->prepareLeave();
    }


    OGenericAdministrationPage*	OLDAPConnectionPageSetup::CreateLDAPTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OLDAPConnectionPageSetup( pParent, _rAttrSet ) );
    }


    //========================================================================
    //= OLDAPPageSetup
    //========================================================================
    OLDAPConnectionPageSetup::OLDAPConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_LDAP), _rCoreAttrs)
        ,m_aFTHeaderText        (this, ModuleRes(FT_LDAP_HEADERTEXT))
        ,m_aFTHelpText          (this, ModuleRes(FT_LDAP_HELPTEXT))
        ,m_aFTHostServer	    (this, ModuleRes(FT_AUTOHOSTNAME))
        ,m_aETHostServer	    (this, ModuleRes(ET_AUTOHOSTNAME))
        ,m_aFTBaseDN			(this, ModuleRes(FT_AUTOBASEDN))
        ,m_aETBaseDN		    (this, ModuleRes(ET_AUTOBASEDN))
        ,m_aFTPortNumber		(this, ModuleRes(FT_AUTOPORTNUMBER))
        ,m_aNFPortNumber	    (this, ModuleRes(NF_AUTOPORTNUMBER))
        ,m_aFTDefaultPortNumber (this, ModuleRes(FT_AUTOPORTNUMBERDEFAULT))
        ,m_aCBUseSSL            (this, ModuleRes(CB_WIZ_USESSL))
    {
        SetControlFontWeight(&m_aFTHeaderText);
        m_aFTDefaultPortNumber.SetText(String(ModuleRes(STR_LDAP_DEFAULT)));
        m_aETHostServer.SetModifyHdl(getControlModifiedLink());
        m_aETBaseDN.SetModifyHdl(getControlModifiedLink());
        m_aNFPortNumber.SetModifyHdl(getControlModifiedLink());
        m_aCBUseSSL.SetToggleHdl(getControlModifiedLink());
        // #98982# OJ
        m_aNFPortNumber.SetUseThousandSep(sal_False);
        SetRoadmapStateValue(sal_False);
        FreeResource();
    }

    // -----------------------------------------------------------------------
    /* OGenericAdministrationPage*	ODriversSettings::CreateLDAP( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OLDAPConnectionPageSetup( pParent, _rAttrSet ) );
    }*/

    // -----------------------------------------------------------------------
    sal_Bool OLDAPConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
           sal_Bool bChangedSomething = sal_False;
        fillString(_rSet,&m_aETBaseDN,DSID_CONN_LDAP_BASEDN, bChangedSomething);
        fillInt32(_rSet,&m_aNFPortNumber,DSID_CONN_LDAP_PORTNUMBER,bChangedSomething);

        if ( m_aETHostServer.GetText() != m_aETHostServer.GetSavedValue() )
        {
            DbuTypeCollectionItem* pCollectionItem = PTR_CAST(DbuTypeCollectionItem, _rSet.GetItem(DSID_TYPECOLLECTION));
            ::dbaccess::ODsnTypeCollection* pCollection = NULL;
            if (pCollectionItem)
                pCollection = pCollectionItem->getCollection();
            DBG_ASSERT(pCollection, "OLDAPConnectionPageSetup::FillItemSet : really need a DSN type collection !");

            String sUrl = pCollection->getDatasourcePrefix( ::dbaccess::DST_LDAP);
            sUrl += m_aETHostServer.GetText();
            _rSet.Put(SfxStringItem(DSID_CONNECTURL, sUrl));
            bChangedSomething = sal_True;
        }

        // fillString(_rSet,&m_aETHostServer, DSID_CONNECTURL, bChangedSomething);
        fillBool(_rSet,&m_aCBUseSSL,DSID_CONN_LDAP_USESSL,bChangedSomething);
        return bChangedSomething;
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETHostServer));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETBaseDN));
        _rControlList.push_back(new OSaveValueWrapper<NumericField>(&m_aNFPortNumber));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBUseSSL));
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHostServer));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTBaseDN));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDefaultPortNumber));
    }
    // -----------------------------------------------------------------------
    void OLDAPConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);


        SFX_ITEMSET_GET(_rSet, pBaseDN, SfxStringItem, DSID_CONN_LDAP_BASEDN, sal_True);
        SFX_ITEMSET_GET(_rSet, pPortNumber, SfxInt32Item, DSID_CONN_LDAP_PORTNUMBER, sal_True);

        if ( bValid ) 
        {
            m_aETBaseDN.SetText(pBaseDN->GetValue());
            m_aNFPortNumber.SetValue(pPortNumber->GetValue());
        }
           OGenericAdministrationPage::implInitControls(_rSet, _bSaveValue);	
        callModifiedHdl();
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OLDAPConnectionPageSetup, OnEditModified, Edit*, /*_pEdit*/)
    {
        sal_Bool bRoadmapState = ((m_aETHostServer.GetText().Len() != 0 ) && ( m_aETBaseDN.GetText().Len() != 0 ) && (m_aFTPortNumber.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
        callModifiedHdl();
        return 0L;
    }


    // ----------------------------------------------------------------------- //OGenericAdministrationPage*
    OMySQLIntroPageSetup* OMySQLIntroPageSetup::CreateMySQLIntroTabPage( Window* _pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OMySQLIntroPageSetup( _pParent, _rAttrSet) );
    }

DBG_NAME(OMySQLIntroPageSetup)

    OMySQLIntroPageSetup::OMySQLIntroPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
            :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_MYSQL_INTRO), _rCoreAttrs)
            ,m_aRB_ODBCDatabase(this, ModuleRes(RB_CONNECTVIAODBC))
            ,m_aRB_JDBCDatabase(this, ModuleRes(RB_CONNECTVIAJDBC))
            ,m_aRB_NATIVEDatabase(this, ModuleRes(RB_CONNECTVIANATIVE))
            ,m_aFT_ConnectionMode(this, ModuleRes(FT_MYSQLCONNECTIONMODE))
            ,m_aFT_Helptext(this, ModuleRes(FT_MYSQL_HELPTEXT))
            ,m_aFT_Headertext(this, ModuleRes(FT_MYSQL_HEADERTEXT))
    {
        DBG_CTOR(OMySQLIntroPageSetup,NULL);

        SetControlFontWeight(&m_aFT_Headertext);
           m_aRB_JDBCDatabase.SetToggleHdl(LINK(this, OMySQLIntroPageSetup, OnSetupModeSelected));
        m_aRB_NATIVEDatabase.SetToggleHdl(LINK(this, OMySQLIntroPageSetup, OnSetupModeSelected));
        m_aRB_JDBCDatabase.SetState(sal_True);
        FreeResource();
    }

    IMPL_LINK(OMySQLIntroPageSetup, OnSetupModeSelected, RadioButton*, /*_pBox*/)
    {
        maClickHdl.Call( this );
        return true;
    }

    // -----------------------------------------------------------------------
    OMySQLIntroPageSetup::~OMySQLIntroPageSetup()
    {
    
        DBG_DTOR(OMySQLIntroPageSetup,NULL);
    }


    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool /*_bSaveValue*/)
    {
        DbuTypeCollectionItem* pCollectionItem = PTR_CAST(DbuTypeCollectionItem, _rSet.GetItem(DSID_TYPECOLLECTION));
        ::dbaccess::ODsnTypeCollection* pCollection = NULL;
        if (pCollectionItem)
        {
            pCollection = pCollectionItem->getCollection();
            String sUrl = pCollection->getDatasourcePrefix( ::dbaccess::DST_MYSQL_NATIVE);
            uno::Reference< sdbc::XDriverAccess > xDriverManager( m_xORB->createInstance( SERVICE_SDBC_DRIVERMANAGER ), uno::UNO_QUERY );
            if ( xDriverManager.is() && xDriverManager->getDriverByURL( sUrl ).is() )
            {
                m_aRB_NATIVEDatabase.Show();
                m_aRB_JDBCDatabase.SetState(sal_False);
                m_aRB_NATIVEDatabase.SetState(sal_True);
            }
        }
    }


    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& /*_rControlList*/)
    {
    }

    // -----------------------------------------------------------------------
    void OMySQLIntroPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& /*_rControlList*/)
    {
    }


    // -----------------------------------------------------------------------
    BOOL OMySQLIntroPageSetup::FillItemSet(SfxItemSet& /*_rSet*/)
    {
        OSL_ENSURE(sal_False,"Who called me?! Please ask oj for more information.");
        return sal_True;
    }


    OMySQLIntroPageSetup::ConnectionType OMySQLIntroPageSetup::getMySQLMode()
    {
        if (m_aRB_JDBCDatabase.IsChecked())
            return VIA_JDBC;
        else if (m_aRB_NATIVEDatabase.IsChecked())
            return VIA_NATIVE;
        else
            return VIA_ODBC;
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OGeneralSpecialJDBCConnectionPageSetup::CreateMySQLJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OGeneralSpecialJDBCConnectionPageSetup( pParent, 
                                                         PAGE_DBWIZARD_MYSQL_JDBC, 
                                                         _rAttrSet,
                                                         DSID_MYSQL_PORTNUMBER ,
                                                         STR_MYSQL_DEFAULT,
                                                         "com.mysql.jdbc.Driver", 
                                                         STR_MYSQLJDBC_HELPTEXT, 
                                                         STR_MYSQLJDBC_HEADERTEXT,
                                                         STR_MYSQL_DRIVERCLASSTEXT) );
    }

    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OGeneralSpecialJDBCConnectionPageSetup::CreateMySQLNATIVETabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OGeneralSpecialJDBCConnectionPageSetup( pParent, 
                                                         PAGE_DBWIZARD_MYSQL_NATIVE, 
                                                         _rAttrSet,
                                                         DSID_MYSQL_PORTNUMBER ,
                                                         STR_MYSQL_DEFAULT,
                                                         NULL, 
                                                         STR_MYSQLJDBC_HELPTEXT, 
                                                         STR_MYSQLJDBC_HEADERTEXT,
                                                         0) );
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OGeneralSpecialJDBCConnectionPageSetup::CreateOracleJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OGeneralSpecialJDBCConnectionPageSetup( pParent, 
                                                          PAGE_DBWIZARD_ORACLE, 
                                                          _rAttrSet, 
                                                          DSID_ORACLE_PORTNUMBER,
                                                          STR_ORACLE_DEFAULT, 
                                                          "oracle.jdbc.driver.OracleDriver", 
                                                          STR_ORACLE_HELPTEXT, 
                                                          STR_ORACLE_HEADERTEXT,
                                                          STR_ORACLE_DRIVERCLASSTEXT) );
    }


    //========================================================================
    //= OMySQLJDBCConnectionPageSetup
    //========================================================================
    OGeneralSpecialJDBCConnectionPageSetup::OGeneralSpecialJDBCConnectionPageSetup( Window* pParent,USHORT _nResId, const SfxItemSet& _rCoreAttrs ,USHORT _nPortId, USHORT _nDefaultPortResId, const sal_Char* _pDriverName, USHORT _nHelpTextResId, USHORT _nHeaderTextResId, USHORT _nDriverClassId)
        :OGenericAdministrationPage(pParent, ModuleRes(_nResId), _rCoreAttrs)
        ,m_pFTHeaderText        (NULL)
        ,m_aFTHelpText          (this, ModuleRes(FT_AUTOWIZARDHELPTEXT))
        ,m_aFTDatabasename	    (this, ModuleRes(FT_AUTODATABASENAME))
        ,m_aETDatabasename	    (this, ModuleRes(ET_AUTODATABASENAME))
        ,m_aFTHostname		    (this, ModuleRes(FT_AUTOHOSTNAME))
        ,m_aETHostname		    (this, ModuleRes(ET_AUTOHOSTNAME))
        ,m_aFTPortNumber	    (this, ModuleRes(FT_AUTOPORTNUMBER))
        ,m_aFTDefaultPortNumber (this, ModuleRes(FT_AUTOPORTNUMBERDEFAULT))
        ,m_aNFPortNumber	    (this, ModuleRes(NF_AUTOPORTNUMBER))
        ,m_aFTSocket		    (this, ModuleRes(FT_SOCKET))
        ,m_aETSocket		    (this, ModuleRes(ET_SOCKET))
        ,m_aFTDriverClass	    (this, ModuleRes(FT_AUTOJDBCDRIVERCLASS))
        ,m_aETDriverClass	    (this, ModuleRes(ET_AUTOJDBCDRIVERCLASS))
        ,m_aPBTestJavaDriver	(this, ModuleRes(PB_AUTOTESTDRIVERCLASS))
        ,m_nPortId(_nPortId)
        ,m_bUseClass(true)
    {
        if ( _nDriverClassId )
            m_aFTDriverClass.SetText(String(ModuleRes(_nDriverClassId)));
        else
        {
            m_bUseClass = false;
            m_aFTDriverClass.Show(FALSE);
            m_aPBTestJavaDriver.Show(FALSE);
            m_aETDriverClass.Show(FALSE);
        }
        
        m_aFTSocket.Show(_nResId == PAGE_DBWIZARD_MYSQL_NATIVE && !m_bUseClass);
        m_aETSocket.Show(_nResId == PAGE_DBWIZARD_MYSQL_NATIVE && !m_bUseClass);

        m_aFTDefaultPortNumber.SetText(String(ModuleRes(_nDefaultPortResId)));
        String sHelpText = String(ModuleRes(_nHelpTextResId));
        m_aFTHelpText.SetText(sHelpText);
        //TODO this code snippet is redundant
        SetHeaderText(FT_AUTOWIZARDHEADER, _nHeaderTextResId); 

        m_aETDatabasename.SetModifyHdl(getControlModifiedLink());
        m_aETHostname.SetModifyHdl(getControlModifiedLink());
        m_aNFPortNumber.SetModifyHdl(getControlModifiedLink());
        m_aETSocket.SetModifyHdl(getControlModifiedLink());

        if ( m_bUseClass )
        {
            m_aETDriverClass.SetModifyHdl(LINK(this, OGeneralSpecialJDBCConnectionPageSetup, OnEditModified));
            m_aPBTestJavaDriver.SetClickHdl(LINK(this,OGeneralSpecialJDBCConnectionPageSetup,OnTestJavaClickHdl));
        }
        
        m_aNFPortNumber.SetUseThousandSep(sal_False);
        if ( m_bUseClass )
            m_sDefaultJdbcDriverName = String::CreateFromAscii(_pDriverName);
        SetRoadmapStateValue(sal_False);
        FreeResource();
    }


    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDatabasename));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDriverClass));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETHostname));
        _rControlList.push_back(new OSaveValueWrapper<NumericField>(&m_aNFPortNumber));
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETSocket));
    }
    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDatabasename));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHostname));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDefaultPortNumber));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTSocket));
        if ( m_bUseClass )
            _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDriverClass));
    }

    // -----------------------------------------------------------------------
    sal_Bool OGeneralSpecialJDBCConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = sal_False;
        if ( m_bUseClass )
            fillString(_rSet,&m_aETDriverClass,DSID_JDBCDRIVERCLASS,bChangedSomething);
        fillString(_rSet,&m_aETHostname,DSID_CONN_HOSTNAME,bChangedSomething);
        fillString(_rSet,&m_aETDatabasename,DSID_DATABASENAME,bChangedSomething);
        fillInt32(_rSet,&m_aNFPortNumber,m_nPortId,bChangedSomething );
        fillString(_rSet,&m_aETSocket,DSID_CONN_SOCKET,bChangedSomething);
        return bChangedSomething;
    }

    // -----------------------------------------------------------------------
    void OGeneralSpecialJDBCConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);

        const SfxStringItem *pDrvItem = NULL;
        if ( m_bUseClass )
            pDrvItem = (const SfxStringItem*) (_rSet).GetItem( DSID_JDBCDRIVERCLASS, sal_True, TYPE(SfxStringItem) );
        
        SFX_ITEMSET_GET(_rSet, pHostName, SfxStringItem, DSID_CONN_HOSTNAME, sal_True);
        SFX_ITEMSET_GET(_rSet, pPortNumber, SfxInt32Item, m_nPortId, sal_True);
        SFX_ITEMSET_GET(_rSet, pSocket, SfxStringItem, DSID_CONN_SOCKET, sal_True);

        if ( bValid )
        {
            if ( m_bUseClass )
            {
                m_aETDriverClass.SetText(pDrvItem->GetValue());
                m_aETDriverClass.ClearModifyFlag();
            }

            m_aETHostname.SetText(pHostName->GetValue());
            m_aETHostname.ClearModifyFlag();

            m_aNFPortNumber.SetValue(pPortNumber->GetValue());
            m_aNFPortNumber.ClearModifyFlag();

            m_aETSocket.SetText(pSocket->GetValue());
            m_aETSocket.ClearModifyFlag();
        }
        OGenericAdministrationPage::implInitControls(_rSet, _bSaveValue);

        // to get the correct value when saveValue was called by base class
        if ( m_bUseClass && !m_aETDriverClass.GetText().Len() )
        {
            m_aETDriverClass.SetText(m_sDefaultJdbcDriverName);
            m_aETDriverClass.SetModifyFlag();
        }
        callModifiedHdl();

        sal_Bool bRoadmapState = ((m_aETDatabasename.GetText().Len() != 0 ) && ( m_aETHostname.GetText().Len() != 0 ) && (m_aNFPortNumber.GetText().Len() != 0 ) && ( !m_bUseClass || m_aETDriverClass.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OGeneralSpecialJDBCConnectionPageSetup, OnTestJavaClickHdl, PushButton*, /*_pButton*/)
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        OSL_ENSURE(m_bUseClass,"Who called this one?");

        sal_Bool bSuccess = sal_False;
        try
        {
            if ( m_aETDriverClass.GetText().Len() )
            {
// TODO chage jvmaccess
                ::rtl::Reference< jvmaccess::VirtualMachine > xJVM = ::connectivity::getJavaVM(m_pAdminDialog->getORB());
                bSuccess = ::connectivity::existsJavaClassByName(xJVM,m_aETDriverClass.GetText());
            }
        }
        catch(::com::sun::star::uno::Exception&)
        {
        }

        USHORT nMessage = bSuccess ? STR_JDBCDRIVER_SUCCESS : STR_JDBCDRIVER_NO_SUCCESS;
        OSQLMessageBox aMsg( this, String( ModuleRes( nMessage ) ), String() );
        aMsg.Execute();
        return 0L;
    }
    
    // -----------------------------------------------------------------------
    IMPL_LINK(OGeneralSpecialJDBCConnectionPageSetup, OnEditModified, Edit*, _pEdit)
    {
        if ( m_bUseClass && _pEdit == &m_aETDriverClass )
            m_aPBTestJavaDriver.Enable( m_aETDriverClass.GetText().Len() != 0 );
        sal_Bool bRoadmapState = ((m_aETDatabasename.GetText().Len() != 0 ) && ( m_aETHostname.GetText().Len() != 0 ) && (m_aNFPortNumber.GetText().Len() != 0 ) && ( !m_bUseClass || m_aETDriverClass.GetText().Len() != 0 ));
        SetRoadmapStateValue(bRoadmapState);
        callModifiedHdl();
        return 0L;
    }


    // -----------------------------------------------------------------------
    OGenericAdministrationPage*	OJDBCConnectionPageSetup::CreateJDBCTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OJDBCConnectionPageSetup( pParent, _rAttrSet));
    }


    //========================================================================
    //= OMySQLJDBCConnectionPageSetup
    //========================================================================
    OJDBCConnectionPageSetup::OJDBCConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs)
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_JDBC, _rCoreAttrs, STR_JDBC_HELPTEXT, STR_JDBC_HEADERTEXT, STR_COMMONURL)
        ,m_aFTDriverClass	    (this, ModuleRes(FT_AUTOJDBCDRIVERCLASS))
        ,m_aETDriverClass	    (this, ModuleRes(ET_AUTOJDBCDRIVERCLASS))
        ,m_aPBTestJavaDriver	(this, ModuleRes(PB_AUTOTESTDRIVERCLASS))
    {
        m_aETDriverClass.SetModifyHdl(LINK(this, OJDBCConnectionPageSetup, OnEditModified));
        m_aPBTestJavaDriver.SetClickHdl(LINK(this,OJDBCConnectionPageSetup,OnTestJavaClickHdl));
        FreeResource();
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETDriverClass));
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTDriverClass));
    }

    // -----------------------------------------------------------------------
    sal_Bool OJDBCConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        fillString(_rSet,&m_aETDriverClass,DSID_JDBCDRIVERCLASS,bChangedSomething);
        return bChangedSomething;
    }

    // -----------------------------------------------------------------------
    void OJDBCConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);

        SFX_ITEMSET_GET(_rSet, pDrvItem, SfxStringItem, DSID_JDBCDRIVERCLASS, sal_True);

        if ( bValid )
        {
            m_aETDriverClass.SetText(pDrvItem->GetValue());
            m_aETDriverClass.ClearModifyFlag();
        }
        sal_Bool bEnable = pDrvItem->GetValue().Len() != 0;
        m_aPBTestJavaDriver.Enable(bEnable);
        OConnectionTabPageSetup::implInitControls(_rSet, _bSaveValue);

        SetRoadmapStateValue(checkTestConnection());
    }


    bool OJDBCConnectionPageSetup::checkTestConnection()
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        BOOL bEnableTestConnection = !m_aET_Connection.IsVisible() || (m_aET_Connection.GetTextNoPrefix().Len() != 0);
        bEnableTestConnection = bEnableTestConnection && (m_aETDriverClass.GetText().Len() != 0);
        return bEnableTestConnection;
//		m_aTestConnection.Enable(bEnableTestConnection);
    }


    // -----------------------------------------------------------------------
    IMPL_LINK(OJDBCConnectionPageSetup, OnTestJavaClickHdl, PushButton*, /*_pButton*/)
    {
        OSL_ENSURE(m_pAdminDialog,"No Admin dialog set! ->GPF");
        sal_Bool bSuccess = sal_False;
        try
        {
            if ( m_aETDriverClass.GetText().Len() )
            {
// TODO chage jvmaccess
                ::rtl::Reference< jvmaccess::VirtualMachine > xJVM = ::connectivity::getJavaVM(m_pAdminDialog->getORB());
                bSuccess = xJVM.is() && ::connectivity::existsJavaClassByName(xJVM,m_aETDriverClass.GetText());
            }
        }
        catch(::com::sun::star::uno::Exception&)
        {
        }

        USHORT nMessage = bSuccess ? STR_JDBCDRIVER_SUCCESS : STR_JDBCDRIVER_NO_SUCCESS;
        OSQLMessageBox aMsg( this, String( ModuleRes( nMessage ) ), String() );
        aMsg.Execute();
        return 0L;
    }

    // -----------------------------------------------------------------------
    IMPL_LINK(OJDBCConnectionPageSetup, OnEditModified, Edit*, _pEdit)
    {
        if ( _pEdit == &m_aETDriverClass )
            m_aPBTestJavaDriver.Enable( m_aETDriverClass.GetText().Len() != 0 );
        SetRoadmapStateValue(checkTestConnection());
        // tell the listener we were modified
        callModifiedHdl();
        return 0L;
    }


    OGenericAdministrationPage*	OSpreadSheetConnectionPageSetup::CreateSpreadSheetTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OSpreadSheetConnectionPageSetup( pParent, _rAttrSet ) );
    }

DBG_NAME(OSpreadSheetConnectionPageSetup)

    OSpreadSheetConnectionPageSetup::OSpreadSheetConnectionPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OConnectionTabPageSetup(pParent, PAGE_DBWIZARD_SPREADSHEET, _rCoreAttrs, STR_SPREADSHEET_HELPTEXT, STR_SPREADSHEET_HEADERTEXT, STR_SPREADSHEETPATH)
            , m_aCBPasswordrequired(this, ModuleRes(CB_SPREADSHEETPASSWORDREQUIRED))
    {
        DBG_CTOR(OSpreadSheetConnectionPageSetup,NULL);

           m_aCBPasswordrequired.SetToggleHdl(getControlModifiedLink());
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OSpreadSheetConnectionPageSetup::~OSpreadSheetConnectionPageSetup()
    {
    
        DBG_DTOR(OSpreadSheetConnectionPageSetup,NULL);
    }


    void OSpreadSheetConnectionPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& /*_rControlList*/)
    {
    }

    // -----------------------------------------------------------------------
    void OSpreadSheetConnectionPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        OConnectionTabPageSetup::fillControls(_rControlList);
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBPasswordrequired));

    }

    // -----------------------------------------------------------------------
    void OSpreadSheetConnectionPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue)
    {
        OConnectionTabPageSetup::implInitControls(_rSet, _bSaveValue);
    }

    // -----------------------------------------------------------------------
    sal_Bool OSpreadSheetConnectionPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = OConnectionTabPageSetup::FillItemSet(_rSet);
        fillBool(_rSet,&m_aCBPasswordrequired,DSID_PASSWORDREQUIRED,bChangedSomething);
        return bChangedSomething;
    }

    OGenericAdministrationPage*	OAuthentificationPageSetup::CreateAuthentificationTabPage( Window* pParent, const SfxItemSet& _rAttrSet )
    {
        return ( new OAuthentificationPageSetup( pParent, _rAttrSet) );
    }

DBG_NAME(OAuthentificationPageSetup)

    OAuthentificationPageSetup::OAuthentificationPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
        :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_AUTHENTIFICATION), _rCoreAttrs )
        , m_aFTHelpText             (this, ModuleRes(FT_AUTHENTIFICATIONHELPTEXT))
        , m_aFTHeaderText           (this, ModuleRes(FT_AUTHENTIFICATIONHEADERTEXT))
        , m_aFTUserName             (this, ModuleRes(FT_GENERALUSERNAME))
        , m_aETUserName             (this, ModuleRes(ET_GENERALUSERNAME))
        , m_aCBPasswordRequired     (this, ModuleRes(CB_GENERALPASSWORDREQUIRED))
        , m_aPBTestConnection       (this, ModuleRes(PB_TESTCONNECTION))
    {
        DBG_CTOR(OAuthentificationPageSetup,NULL);

        SetControlFontWeight(&m_aFTHeaderText);
        m_aETUserName.SetModifyHdl(getControlModifiedLink());
        m_aCBPasswordRequired.SetClickHdl(getControlModifiedLink());
           m_aPBTestConnection.SetClickHdl(LINK(this,OGenericAdministrationPage,OnTestConnectionClickHdl));
        FreeResource();
    }


    // -----------------------------------------------------------------------
    OAuthentificationPageSetup::~OAuthentificationPageSetup()
    {
    
        DBG_DTOR(OAuthentificationPageSetup,NULL);
    }


    void OAuthentificationPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTUserName));
        _rControlList.push_back(new ODisableWrapper<PushButton>(&m_aPBTestConnection));
    }

    // -----------------------------------------------------------------------
    void OAuthentificationPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<Edit>(&m_aETUserName));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBPasswordRequired));
    }

    // -----------------------------------------------------------------------
    void OAuthentificationPageSetup::implInitControls(const SfxItemSet& _rSet, sal_Bool /*_bSaveValue*/)
    {
        // check whether or not the selection is invalid or readonly (invalid implies readonly, but not vice versa)
        sal_Bool bValid, bReadonly;
        getFlags(_rSet, bValid, bReadonly);
        SFX_ITEMSET_GET(_rSet, pUidItem, SfxStringItem, DSID_USER, sal_True);
        SFX_ITEMSET_GET(_rSet, pAllowEmptyPwd, SfxBoolItem, DSID_PASSWORDREQUIRED, sal_True);

        m_aETUserName.SetText(pUidItem->GetValue());
        m_aCBPasswordRequired.Check(pAllowEmptyPwd->GetValue());

        m_aETUserName.ClearModifyFlag();
    }

    // -----------------------------------------------------------------------
    sal_Bool OAuthentificationPageSetup::FillItemSet( SfxItemSet& _rSet )
    {
        sal_Bool bChangedSomething = sal_False;

        if (m_aETUserName.GetText() != m_aETUserName.GetSavedValue())
        {
            _rSet.Put(SfxStringItem(DSID_USER, m_aETUserName.GetText()));
            _rSet.Put(SfxStringItem(DSID_PASSWORD, String()));
            bChangedSomething = sal_True;
        }
        fillBool(_rSet,&m_aCBPasswordRequired,DSID_PASSWORDREQUIRED,bChangedSomething);
        return bChangedSomething;
    }


    OGenericAdministrationPage*	OFinalDBPageSetup::CreateFinalDBTabPageSetup( Window* pParent, const SfxItemSet& _rAttrSet)
    {
        return ( new OFinalDBPageSetup( pParent, _rAttrSet) );
    }

DBG_NAME(OFinalDBPageSetup)

    OFinalDBPageSetup::OFinalDBPageSetup( Window* pParent, const SfxItemSet& _rCoreAttrs )
    :OGenericAdministrationPage(pParent, ModuleRes(PAGE_DBWIZARD_FINAL), _rCoreAttrs )
    , m_aFTFinalHeader              (this, ModuleRes(FT_FINALHEADER))
    , m_aFTFinalHelpText            (this, ModuleRes(FT_FINALHELPTEXT))
    , m_aRBRegisterDataSource       (this, ModuleRes(RB_REGISTERDATASOURCE))
    , m_aRBDontregisterDataSource   (this, ModuleRes(RB_DONTREGISTERDATASOURCE))
    , m_aFTAdditionalSettings       (this, ModuleRes(FT_ADDITIONALSETTINGS))
    , m_aCBOpenAfterwards           (this, ModuleRes(CB_OPENAFTERWARDS))
    , m_aCBStartTableWizard         (this, ModuleRes(CB_STARTTABLEWIZARD))
    , m_aFTFinalText                (this, ModuleRes(FT_FINALTEXT))        
    {
        DBG_CTOR(OFinalDBPageSetup,NULL);

        String stext = m_aFTFinalHeader.GetText();
        SetControlFontWeight(&m_aFTFinalHeader);
        m_aCBOpenAfterwards.SetClickHdl(LINK(this, OFinalDBPageSetup, OnOpenSelected));
        m_aCBStartTableWizard.SetClickHdl(getControlModifiedLink());
        m_aRBRegisterDataSource.SetState(sal_True);
        FreeResource();

        sal_Int32 nUnrelatedHeight  = LogicToPixel( Size( 0, UNRELATED_CONTROLS ), MAP_APPFONT ).Height();
        sal_Int32 nRelatedHeight    = LogicToPixel( Size( 0, RELATED_CONTROLS ), MAP_APPFONT ).Height();

        ::std::pair<Window*,sal_Int32> pWindows[] = { 	
            ::std::pair<Window*,sal_Int32>(&m_aFTFinalHelpText,nRelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aRBRegisterDataSource,nRelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aRBDontregisterDataSource,nUnrelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aFTAdditionalSettings,nRelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aCBOpenAfterwards,nRelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aCBStartTableWizard,nUnrelatedHeight)
            ,::std::pair<Window*,sal_Int32>(&m_aFTFinalText,nUnrelatedHeight)
        };

        Point aPos(m_aFTFinalHeader.GetPosPixel());
        Size aStart(m_aFTFinalHeader.GetSizePixel());
        aPos.Y() += aStart.Height() + nUnrelatedHeight;
        sal_Int32 nCount = sizeof(pWindows) / sizeof(pWindows[0]);
        for (sal_Int32 i=0; i < nCount; ++i)
        {
            aPos.X() = pWindows[i].first->GetPosPixel().X();
            Size aSize = pWindows[i].first->GetSizePixel();
            FixedText* pText = dynamic_cast<FixedText*>(pWindows[i].first);
            CheckBox* pCheck = dynamic_cast<CheckBox*>(pWindows[i].first);
            RadioButton* pRadio = dynamic_cast<RadioButton*>(pWindows[i].first);
            if ( pText )
                aSize = pText->CalcMinimumSize(aSize.Width());
            else if ( pRadio )
                aSize = pRadio->CalcMinimumSize(aSize.Width());
            else if ( pCheck )
                aSize = pCheck->CalcMinimumSize(aSize.Width());
            pWindows[i].first->SetPosSizePixel(aPos,aSize);
            aPos.Y() += aSize.Height() + pWindows[i].second;
        }
    }


    // -----------------------------------------------------------------------
    OFinalDBPageSetup::~OFinalDBPageSetup()
    {
    
        DBG_DTOR(OFinalDBPageSetup,NULL);
    }

    sal_Bool OFinalDBPageSetup::IsDatabaseDocumentToBeRegistered()
    {   
        return m_aRBRegisterDataSource.IsChecked() && m_aRBRegisterDataSource.IsEnabled();
    }

    sal_Bool OFinalDBPageSetup::IsDatabaseDocumentToBeOpened()
    {          
        return m_aCBOpenAfterwards.IsChecked() && m_aCBOpenAfterwards.IsEnabled();
    }

    sal_Bool OFinalDBPageSetup::IsTableWizardToBeStarted()
    {
        return m_aCBStartTableWizard.IsChecked() && m_aCBStartTableWizard.IsEnabled();
    }


    void OFinalDBPageSetup::fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalHeader));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalHelpText));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTAdditionalSettings));
        _rControlList.push_back(new ODisableWrapper<FixedText>(&m_aFTFinalText));
    }

    // -----------------------------------------------------------------------
    void OFinalDBPageSetup::fillControls(::std::vector< ISaveValueWrapper* >& _rControlList)
    {
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBOpenAfterwards));
        _rControlList.push_back(new OSaveValueWrapper<CheckBox>(&m_aCBStartTableWizard));
        _rControlList.push_back(new OSaveValueWrapper<RadioButton>(&m_aRBRegisterDataSource));
        _rControlList.push_back(new OSaveValueWrapper<RadioButton>(&m_aRBDontregisterDataSource));
    }

    // -----------------------------------------------------------------------
    void OFinalDBPageSetup::implInitControls(const SfxItemSet& /*_rSet*/, sal_Bool /*_bSaveValue*/)
    {
        m_aCBOpenAfterwards.Check();
    }

    void OFinalDBPageSetup::enableTableWizardCheckBox( sal_Bool _bSupportsTableCreation)
    {
        m_aCBStartTableWizard.Enable(_bSupportsTableCreation);
    }

    // -----------------------------------------------------------------------
    sal_Bool OFinalDBPageSetup::FillItemSet( SfxItemSet& /*_rSet*/ )
    {
        return sal_True;
    }
    // -----------------------------------------------------------------------------
    IMPL_LINK(OFinalDBPageSetup, OnOpenSelected, CheckBox*, _pBox)
    {
        m_aCBStartTableWizard.Enable( _pBox->IsEnabled() && _pBox->IsChecked() );
        callModifiedHdl();
        // outta here
        return 0L;
    }
//.........................................................................
}
// namespace dbaui
//.........................................................................
