/*************************************************************************
 *
 *  $RCSfile: dbadmin.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: fs $ $Date: 2000-10-05 10:04:31 $
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
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _DBAUI_DBADMIN_HXX_
#include "dbadmin.hxx"
#endif
#ifndef _DBAUI_DBADMIN_HRC_
#include "dbadmin.hrc"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBAUI_DATASOURCEITEMS_HXX_
#include "dsitems.hxx"
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
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _DBASHARED_STRINGCONSTANTS_HRC_
#include "stringconstants.hrc"
#endif
#ifndef _CPPUHELPER_EXTRACT_HXX_
#include <cppuhelper/extract.hxx>
#endif
#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _DBAUI_LOCALRESACCESS_HXX_
#include "localresaccess.hxx"
#endif
#ifndef _DBAUI_STRINGLISTITEM_HXX_
#include "stringlistitem.hxx"
#endif

#define MODIFIED_MARKER		" (*)"

//.........................................................................
namespace dbaui
{
//.........................................................................

using namespace dbaccess;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::beans;
using namespace com::sun::star::container;

//=========================================================================
//= ODbAdminDialog
//=========================================================================
//-------------------------------------------------------------------------
ODbAdminDialog::ODbAdminDialog(Window* _pParent, SfxItemSet* _pItems, const Reference< XMultiServiceFactory >& _rxORB)
    :SfxTabDialog(_pParent, ModuleRes(DLG_DATABASE_ADMINISTRATION), _pItems)
    ,m_aSelector(this, ResId(WND_DATASOURCESELECTOR))
    ,m_xORB(_rxORB)
{
    // add the initial tab pages
    AddTabPage(PAGE_GENERAL, String(ResId(STR_PAGETITLE_GENERAL)), OGeneralPage::Create, NULL);
    AddTabPage(PAGE_TABLESUBSCRIPTION, String(ResId(STR_PAGETITLE_TABLESUBSCRIPTION)), OTableSubscriptionPage::Create, NULL);

    // no local resources needed anymore
    FreeResource();

    // register the view window
    SetViewWindow(&m_aSelector);
    SetViewAlign(WINDOWALIGN_LEFT);

    // do some knittings
    m_aSelector.m_aDatasourceList.SetSelectHdl(LINK(this, ODbAdminDialog, OnDatasourceSelected));

    // concretize some items in our set which are independent of a concret selected datasource
//	GetInputSetImpl()->Put(DbuTypeCollectionItem(DSID_TYPECOLLECTION, m_pCollection));

    // create the DatabaseContext service
    DBG_ASSERT(m_xORB.is(), "ODbAdminDialog::ODbAdminDialog : need a service factory !");
    try
    {
        m_xDatabaseContext = Reference< XNameAccess >(m_xORB->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
    }
    catch(Exception&)
    {
    }

    ::rtl::OUString sInitialSelection;	// will be the initial selection

    if (!m_xDatabaseContext.is())
    {
        ShowServiceNotAvailableError(_pParent, String(SERVICE_SDB_DATABASECONTEXT), sal_True);
    }
    else
    {
        // fill the listbox with the names of the registered datasources
        Sequence< ::rtl::OUString > aDatasources = m_xDatabaseContext->getElementNames();
        const ::rtl::OUString* pDatasources = aDatasources.getConstArray();
        for (sal_Int32 i=0; i<aDatasources.getLength(); ++i, ++pDatasources)
        {
            sal_Int16 nPos = m_aSelector.m_aDatasourceList.InsertEntry(*pDatasources);
            m_aSelector.m_aDatasourceList.SetEntryData(nPos, reinterpret_cast<void*>(sal_False));
                // the entry data is the modified flags
        }

        if (!aDatasources.getLength())
        {
            WarningBox(_pParent, ModuleRes(ERR_NOREGISTEREDDATASOURCES)).Execute();
        }
        else
            sInitialSelection = aDatasources[0];
    }
    // TODO : get the initial selection from the configuration

    implSelectDatasource(sInitialSelection);
}

//-------------------------------------------------------------------------
ODbAdminDialog::~ODbAdminDialog()
{
    SetInputSet(NULL);
    DELETEZ(pExampleSet);
}

//-------------------------------------------------------------------------
Sequence< PropertyValue > ODbAdminDialog::toDriverParams(const SfxItemSet& _rSet)
{
    // TODO
    return Sequence< PropertyValue >();
}

//-------------------------------------------------------------------------
void ODbAdminDialog::toDialogItems(const Sequence< PropertyValue >& _rProperties, SfxItemSet& _rOutSet)
{
    // TODO
}

//-------------------------------------------------------------------------
void ODbAdminDialog::PageCreated(USHORT _nId, SfxTabPage& _rPage)
{
    // register ourself as modified listener
    static_cast<OGenericAdministrationPage&>(_rPage).SetModifiedHandler(LINK(this, ODbAdminDialog, OnDatasourceModifed));

    // some registrations which depend on the type of the page
    switch (_nId)
    {
        case PAGE_GENERAL:
            static_cast<OGeneralPage&>(_rPage).SetTypeSelectHandler(LINK(this, ODbAdminDialog, OnTypeSelected));
            break;
        case PAGE_TABLESUBSCRIPTION:
            static_cast<OTableSubscriptionPage&>(_rPage).setServiceFactory(m_xORB);
            break;
    }

    SfxTabDialog::PageCreated(_nId, _rPage);
}

//-------------------------------------------------------------------------
SfxItemSet* ODbAdminDialog::createItemSet(SfxItemSet*& _rpSet, SfxItemPool*& _rpPool, SfxPoolItem**& _rppDefaults, ODsnTypeCollection* _pTypeCollection)
{
    // just to be sure ....
    _rpSet = NULL;
    _rpPool = NULL;
    _rppDefaults = NULL;

    // create and initialize the defaults
    _rppDefaults = new SfxPoolItem*[DSID_LAST_ITEM_ID - DSID_FIRST_ITEM_ID + 1];
    SfxPoolItem** pCounter = _rppDefaults;	// want to modify this without affecting the out param _rppDefaults
    *pCounter++ = new SfxStringItem(DSID_NAME, String());
    *pCounter++ = new SfxStringItem(DSID_CONNECTURL, String());
    *pCounter++ = new OStringListItem(DSID_TABLEFILTER, Sequence< ::rtl::OUString >());
    *pCounter++ = new DbuTypeCollectionItem(DSID_TYPECOLLECTION, _pTypeCollection);
    *pCounter++ = new SfxBoolItem(DSID_INVALID_SELECTION, sal_False);
    *pCounter++ = new SfxBoolItem(DSID_READONLY, sal_False);
    *pCounter++ = new SfxStringItem(DSID_USER, String());
    *pCounter++ = new SfxStringItem(DSID_PASSWORD, String());
    *pCounter++ = new SfxStringItem(DSID_ADDITIONALOPTIONS, String());
    *pCounter++ = new SfxStringItem(DSID_CHARSET, String());
    *pCounter++ = new SfxBoolItem(DSID_ASKFOREMPTYPWD, sal_False);
    *pCounter++ = new SfxBoolItem(DSID_SHOWDELETEDROWS, sal_False);
    *pCounter++ = new SfxBoolItem(DSID_ALLOWLONGTABLENAMES, sal_False);
    *pCounter++ = new SfxStringItem(DSID_JDBCDRIVERCLASS, String());
    *pCounter++ = new SfxUInt16Item(DSID_FIELDDELIMITER, ';');
    *pCounter++ = new SfxUInt16Item(DSID_TEXTDELIMITER, '"');
    *pCounter++ = new SfxUInt16Item(DSID_DECIMALDELIMITER, '.');
    *pCounter++ = new SfxUInt16Item(DSID_THOUSANDSDELIMITER, ',');
    *pCounter++ = new SfxStringItem(DSID_TEXTFILEEXTENSION, String::CreateFromAscii("txt"));
    *pCounter++ = new SfxBoolItem(DSID_TEXTFILEHEADER, sal_True);

    // create the pool
    static SfxItemInfo __READONLY_DATA aItemInfos[DSID_LAST_ITEM_ID - DSID_FIRST_ITEM_ID + 1] =
    {
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
    };

    _rpPool = new SfxItemPool(String::CreateFromAscii("DSAItemPool"), DSID_FIRST_ITEM_ID, DSID_LAST_ITEM_ID,
        aItemInfos, _rppDefaults);
    _rpPool->FreezeIdRanges();

    // and, finally, the set
    _rpSet = new SfxItemSet(*_rpPool, sal_True);

    return _rpSet;
}

//-------------------------------------------------------------------------
void ODbAdminDialog::destroyItemSet(SfxItemSet*& _rpSet, SfxItemPool*& _rpPool, SfxPoolItem**& _rppDefaults)
{
    // _first_ delete the set (refering the pool)
    if (_rpSet)
    {
        delete _rpSet;
        _rpSet = NULL;
    }

    // delete the pool
    if (_rpPool)
    {
        _rpPool->ReleaseDefaults(sal_True);
            // the "true" means delete the items, too
        delete _rpPool;
        _rpPool = NULL;
    }

    // reset the defaults ptr
    _rppDefaults = NULL;
        // no need to explicitly delete the defaults, this has been done by the ReleaseDefaults
}

//-------------------------------------------------------------------------
IMPL_LINK(ODbAdminDialog, OnDatasourceSelected, ListBox*, _pBox)
{
    sal_Int16 nSelected = _pBox->GetSelectEntryPos();
    sal_Bool bModified = reinterpret_cast<sal_Bool>(_pBox->GetEntryData(nSelected));

    // if the entry is modified, we have to remove the modified marker to get the correct name
    String sSelected = _pBox->GetEntry(nSelected);

    if (bModified)
        implSelectDatasource(sSelected.Copy(0, sSelected.Len() - (sizeof(MODIFIED_MARKER) - 1)));
    else
        implSelectDatasource(sSelected);
    return 0L;
}

//-------------------------------------------------------------------------
IMPL_LINK(ODbAdminDialog, OnDatasourceModifed, SfxTabPage*, _pTabPage)
{
    // check if the currently selected entry is already marked as modified
    sal_Int16 nSelected = m_aSelector.m_aDatasourceList.GetSelectEntryPos();
    sal_Bool bModified = reinterpret_cast<sal_Bool>(m_aSelector.m_aDatasourceList.GetEntryData(nSelected));
    if (bModified)
        // yes -> nothing to do
        return 0L;

    // no -> append the modified marker to the text
    // (unfortunally the ListBox does not have an operation such as SetEntryText ...)
    m_aSelector.m_aDatasourceList.SetUpdateMode(sal_False);
    String sText = m_aSelector.m_aDatasourceList.GetEntry(nSelected);
    m_aSelector.m_aDatasourceList.RemoveEntry(nSelected);
    sText.AppendAscii(MODIFIED_MARKER);
    nSelected = m_aSelector.m_aDatasourceList.InsertEntry(sText, nSelected);
    m_aSelector.m_aDatasourceList.SelectEntryPos (nSelected, sal_True);
    m_aSelector.m_aDatasourceList.SetUpdateMode(sal_True);

    // mark it as modified
    m_aSelector.m_aDatasourceList.SetEntryData(nSelected, reinterpret_cast<void*>(sal_True));

    return 0L;
}

//-------------------------------------------------------------------------
IMPL_LINK(ODbAdminDialog, OnTypeSelected, OGeneralPage*, _pTabPage)
{
    // remove all current detail pages
    while (m_aCurrentDetailPages.size())
    {
        RemoveTabPage(m_aCurrentDetailPages.top());
        m_aCurrentDetailPages.pop();
    }

    // open our own resource block, as the page titles are strings local to this block
    OLocalResourceAccess aDummy(DLG_DATABASE_ADMINISTRATION, RSC_TABDIALOG);

    // and insert the new ones
    switch (_pTabPage->GetSelectedType())
    {
        case DST_DBASE:
            AddTabPage(PAGE_DBASE, String(ResId(STR_PAGETITLE_DBASE)), ODbaseDetailsPage::Create, 0, sal_False, 1);
            m_aCurrentDetailPages.push(PAGE_DBASE);
            break;
        case DST_JDBC:
            AddTabPage(PAGE_JDBC, String(ResId(STR_PAGETITLE_JDBC)), OJdbcDetailsPage::Create, 0, sal_False, 1);
            m_aCurrentDetailPages.push(PAGE_JDBC);
            break;
        case DST_TEXT:
            AddTabPage(PAGE_TEXT, String(ResId(STR_PAGETITLE_TEXT)), OTextDetailsPage::Create, 0, sal_False, 1);
            m_aCurrentDetailPages.push(PAGE_TEXT);
            break;
        case DST_ODBC:
            AddTabPage(PAGE_ODBC, String(ResId(STR_PAGETITLE_ODBC)), OOdbcDetailsPage::Create, 0, sal_False, 1);
            m_aCurrentDetailPages.push(PAGE_ODBC);
            break;
        case DST_ADABAS:
            AddTabPage(PAGE_ADABAS, String(ResId(STR_PAGETITLE_ADABAS)), OAdabasDetailsPage::Create, 0, sal_False, 1);
            m_aCurrentDetailPages.push(PAGE_ADABAS);
            break;
    }

    return 0L;
}

//-------------------------------------------------------------------------
void ODbAdminDialog::implSelectDatasource(const ::rtl::OUString& _rRegisteredName)
{
    DBG_ASSERT(m_xDatabaseContext.is(), "ODbAdminDialog::implSelectDatasource : have no database context!");
    Reference< XPropertySet > xDatasource;
    try
    {
        if (m_xDatabaseContext.is() && _rRegisteredName.getLength())
            ::cppu::extractInterface(xDatasource, m_xDatabaseContext->getByName(_rRegisteredName));
    }
    catch(NoSuchElementException&)
    {
        DBG_ERROR("ODbAdminDialog::implSelectDatasource : did not find the element with the given name!");
    }
    catch(WrappedTargetException&)
    {
        DBG_ERROR("ODbAdminDialog::implSelectDatasource : caught a WrappedTargetException!");
    }
    if (!xDatasource.is())
    {
        m_aSelector.m_aDatasourceList.SelectEntryPos(m_aSelector.m_aDatasourceList.GetSelectEntryPos(), sal_False);
    }
    else
        m_aSelector.m_aDatasourceList.SelectEntry(_rRegisteredName);

    // the selection is valid if and only if we have a datasource now
    GetInputSetImpl()->Put(SfxBoolItem(DSID_INVALID_SELECTION, !xDatasource.is()));
        // (sal_False tells the tab pages to disable and reset all their controls, which is different
        // from "just set them to readonly")

    // reset the pages
    resetPages(xDatasource);
}

//-------------------------------------------------------------------------
void ODbAdminDialog::resetPages(const Reference< XPropertySet >& _rxDatasource)
{
    // remove all tab pages (except the general one)
    // remove all current detail pages
    while (m_aCurrentDetailPages.size())
    {
        RemoveTabPage(m_aCurrentDetailPages.top());
        m_aCurrentDetailPages.pop();
    }
    // remove the table/query tab pages
    RemoveTabPage(PAGE_TABLESUBSCRIPTION);

    // extract all relevant data from the property set
    ::rtl::OUString sNewConnectURL, sName;
    try
    {
        if (_rxDatasource.is())
        {
            _rxDatasource->getPropertyValue(PROPERTY_URL) >>= sNewConnectURL;
            _rxDatasource->getPropertyValue(PROPERTY_NAME) >>= sName;
        }
    }
    catch(Exception&)
    {
        DBG_ERROR("ODbAdminDialog::toDialogItems : could not extract all the relevant datasource properties!");
    }

    GetInputSetImpl()->Put(SfxStringItem(DSID_CONNECTURL, sNewConnectURL));
    GetInputSetImpl()->Put(SfxStringItem(DSID_NAME, sName));

    // propagate this set as our new input set and reset the example set
    SetInputSet(GetInputSetImpl());
    delete pExampleSet;
    pExampleSet = new SfxItemSet(*GetInputSetImpl());

    // and again, add the non-details tab pages
    {
        OLocalResourceAccess aDummy(DLG_DATABASE_ADMINISTRATION, RSC_TABDIALOG);
        AddTabPage(PAGE_TABLESUBSCRIPTION, String(ResId(STR_PAGETITLE_TABLESUBSCRIPTION)), OTableSubscriptionPage::Create, NULL);
    }

    // propagate the new data to the general tab page the general tab page
    SfxTabPage* pGeneralPage = GetTabPage(PAGE_GENERAL);
    if (pGeneralPage)
        pGeneralPage->Reset(*GetInputSetImpl());
    // if this is NULL, the page has not been created yet, which means we're called before the
    // dialog was displayed (probably from inside the ctor)
}

//=========================================================================
//= ODatasourceSelector
//=========================================================================
//-------------------------------------------------------------------------
ODatasourceSelector::ODatasourceSelector(Window* _pParent, const ResId& _rResId)
    :Window(_pParent, _rResId)
    ,m_aBorderWindow	(this, ResId(WND_SELECTORBORDER))
    ,m_aTitle			(this, ResId(FT_SELECTOR_TITLE))
    ,m_aDatasourceList	(this, ResId(LB_DATASOURCES))
{
    FreeResource();

    m_aDatasourceList.SetZOrder(NULL, WINDOW_ZORDER_FIRST);

    m_aDatasourceList.EnableClipSiblings(sal_True);
     m_aBorderWindow.EnableClipSiblings(sal_True);
}

//-------------------------------------------------------------------------
ODatasourceSelector::~ODatasourceSelector()
{
}

//-------------------------------------------------------------------------
void ODatasourceSelector::Resize()
{
    Window::Resize();
    // set the border window to the same size weself have
    Size aSize = GetSizePixel();
    m_aBorderWindow.SetSizePixel(aSize);

    // resize the text field
    sal_Int32 nTextHeight = LogicToPixel(Size(0, GetTextHeight())).Height();
    nTextHeight += 4;	// leave a margin
    m_aTitle.SetPosPixel(Point(2, 2 + 2));
    m_aTitle.SetSizePixel(Size(aSize.Width() - 4, nTextHeight));

    // resize the listbox accordingly
    m_aDatasourceList.SetPosPixel(Point(2, 4 + nTextHeight));
    m_aDatasourceList.SetSizePixel(Size(aSize.Width() - 4, aSize.Height() - 4 - nTextHeight));
}

//.........................................................................
}	// namespace dbaui
//.........................................................................

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *
 *	Revision 1.0 20.09.00 10:55:58  fs
 ************************************************************************/

