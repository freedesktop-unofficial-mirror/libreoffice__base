/*************************************************************************
 *
 *  $RCSfile: unodatbr.cxx,v $
 *
 *  $Revision: 1.85 $
 *
 *  last change: $Author: oj $ $Date: 2001-07-03 07:46:43 $
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

#ifndef _SVX_GRIDCTRL_HXX
#include <svx/gridctrl.hxx>
#endif
#ifndef _SBA_UNODATBR_HXX_
#include "unodatbr.hxx"
#endif
#ifndef _SBA_GRID_HXX
#include "sbagrid.hxx"
#endif
#ifndef _SVTREEBOX_HXX
#include <svtools/svtreebx.hxx>
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <svx/dataaccessdescriptor.hxx>
#endif

#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/unohlp.hxx>
#endif
#ifndef _COM_SUN_STAR_FORM_XLOADABLE_HPP_
#include <com/sun/star/form/XLoadable.hpp>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <sfx2/dispatch.hxx>
#endif

#ifndef _SV_MULTISEL_HXX //autogen
#include <tools/multisel.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XWARNINGSSUPPLIER_HPP_
#include <com/sun/star/sdbc/XWarningsSupplier.hpp>
#endif
#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
#endif
#ifndef _SV_WAITOBJ_HXX
#include <vcl/waitobj.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SFXAPP_HXX //autogen
#include <sfx2/app.hxx>
#endif
#ifndef _SV_WRKWIN_HXX //autogen
#include <vcl/wrkwin.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XGRIDCOLUMNFACTORY_HPP_
#include <com/sun/star/form/XGridColumnFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_TEXTALIGN_HPP_
#include <com/sun/star/awt/TextAlign.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XBOOKMARKSSUPPLIER_HPP_
#include <com/sun/star/sdb/XBookmarksSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XVIEWSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_
#include <com/sun/star/sdbcx/XDrop.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_ 
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _SVX_ALGITEM_HXX //autogen
#include <svx/algitem.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XRESULTSETACCESS_HPP_
#include <com/sun/star/sdb/XResultSetAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLWARNING_HPP_
#include <com/sun/star/sdbc/SQLWarning.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_ 
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef DBAUI_DBTREEMODEL_HXX
#include "dbtreemodel.hxx"
#endif
#ifndef DBACCESS_UI_DBTREEVIEW_HXX
#include "dbtreeview.hxx"
#endif
#ifndef _SVLBOXITM_HXX
#include <svtools/svlbitm.hxx>
#endif
#ifndef _SV_SPLIT_HXX
#include <vcl/split.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef DBACCESS_SBA_GRID_HRC
#include "sbagrid.hrc"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif
#ifndef DBAUI_DBTREELISTBOX_HXX
#include "dbtreelistbox.hxx"
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef _COM_SUN_STAR_UTIL_XFLUSHABLE_HPP_
#include <com/sun/star/util/XFlushable.hpp>
#endif
#ifndef _DBAUI_QUERYDESIGNACCESS_HXX_
#include "querydesignaccess.hxx"
#endif
#ifndef _DBAUI_LISTVIEWITEMS_HXX_
#include "listviewitems.hxx"
#endif
#ifndef _CPPUHELPER_IMPLBASE2_HXX_
#include <cppuhelper/implbase2.hxx>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef DBAUI_TOKENWRITER_HXX
#include "TokenWriter.hxx"
#endif
#ifndef DBAUI_DBEXCHANGE_HXX
#include "dbexchange.hxx"
#endif
#ifndef DBAUI_WIZ_COPYTABLEDIALOG_HXX
#include "WCopyTable.hxx"
#endif
#ifndef DBAUI_WIZ_EXTENDPAGES_HXX
#include "WExtendPages.hxx"
#endif
#ifndef DBAUI_WIZ_NAMEMATCHING_HXX
#include "WNameMatch.hxx"
#endif
#ifndef DBAUI_WIZ_COLUMNSELECT_HXX
#include "WColumnSelect.hxx"
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
#ifndef DBAUI_WIZARD_CPAGE_HXX
#include "WCPage.hxx"
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef DBAUI_RTFREADER_HXX
#include "RtfReader.hxx"
#endif
#ifndef DBAUI_HTMLREADER_HXX
#include "HtmlReader.hxx"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef DBAUI_DLGSAVE_HXX
#include "dlgsave.hxx"
#endif
#ifndef _SOT_STORAGE_HXX
#include <sot/storage.hxx>
#endif
#ifndef _DBAUI_LINKEDDOCUMENTS_HXX_
#include "linkeddocuments.hxx"
#endif
#ifndef _DBACCESS_UI_DIRECTSQL_HXX_
#include "directsql.hxx"
#endif


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::datatransfer;
using namespace ::dbtools;
using namespace ::svx;

// .........................................................................
namespace dbaui
{
// .........................................................................

//==================================================================
//= SbaTableQueryBrowser
//==================================================================
// -------------------------------------------------------------------------
extern "C" void SAL_CALL createRegistryInfo_OBrowser()
{
    static OMultiInstanceAutoRegistration< SbaTableQueryBrowser > aAutoRegistration;
}

// -------------------------------------------------------------------------
void SafeAddPropertyListener(const Reference< XPropertySet > & xSet, const ::rtl::OUString& rPropName, XPropertyChangeListener* pListener)
{
    Reference< XPropertySetInfo >  xInfo = xSet->getPropertySetInfo();
    if (xInfo->hasPropertyByName(rPropName))
        xSet->addPropertyChangeListener(rPropName, pListener);
}

// -------------------------------------------------------------------------
void SafeRemovePropertyListener(const Reference< XPropertySet > & xSet, const ::rtl::OUString& rPropName, XPropertyChangeListener* pListener)
{
    Reference< XPropertySetInfo >  xInfo = xSet->getPropertySetInfo();
    if (xInfo->hasPropertyByName(rPropName))
        xSet->removePropertyChangeListener(rPropName, pListener);
}
//-------------------------------------------------------------------------
::rtl::OUString SAL_CALL SbaTableQueryBrowser::getImplementationName() throw(RuntimeException)
{
    return getImplementationName_Static();
}
//-------------------------------------------------------------------------
::comphelper::StringSequence SAL_CALL SbaTableQueryBrowser::getSupportedServiceNames() throw(RuntimeException)
{
    return getSupportedServiceNames_Static();
}
// -------------------------------------------------------------------------
::rtl::OUString SbaTableQueryBrowser::getImplementationName_Static() throw(RuntimeException)
{
    return ::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.ODatasourceBrowser");
}
//-------------------------------------------------------------------------
::comphelper::StringSequence SbaTableQueryBrowser::getSupportedServiceNames_Static() throw(RuntimeException)
{
    ::comphelper::StringSequence aSupported(1);
    aSupported.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.sdb.DataSourceBrowser");
    return aSupported;
}
//-------------------------------------------------------------------------
Reference< XInterface > SAL_CALL SbaTableQueryBrowser::Create(const Reference<XMultiServiceFactory >& _rxFactory)
{
    ::vos::OGuard aGuard(Application::GetSolarMutex());
    return *(new SbaTableQueryBrowser(_rxFactory));
}
//------------------------------------------------------------------------------
SbaTableQueryBrowser::SbaTableQueryBrowser(const Reference< XMultiServiceFactory >& _rM)
    :SbaXDataBrowserController(_rM)
    ,m_aSelectionListeners(m_aMutex)
    ,m_pTreeModel(NULL)
    ,m_pTreeView(NULL)
    ,m_pSplitter(NULL)
    ,m_pCurrentlyDisplayed(NULL)
    ,m_nAsyncDrop(0)
{
    // calc the title for the load stopper
//	sal_uInt32 nTitleResId;
//	switch (m_xDefinition->GetKind())
//	{
//		case dbTable : nTitleResId = STR_TBL_TITLE; break;
//		case dbQuery : nTitleResId = STR_QRY_TITLE; break;
//		default : DBG_ERROR("OpenDataObjectThread::run : invalid object !");
//	}
//	String sTemp = String(ModuleRes(nTitleResId));
//	sTemp.SearchAndReplace('#', m_xDefinition->Name());
//	m_sLoadStopperCaption = String(ModuleRes(RID_STR_OPEN_OBJECT));
//	m_sLoadStopperCaption += ' ';
//	m_sLoadStopperCaption += sTemp;
}

//------------------------------------------------------------------------------
SbaTableQueryBrowser::~SbaTableQueryBrowser()
{
}

//------------------------------------------------------------------------------
Any	SAL_CALL SbaTableQueryBrowser::queryInterface(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = SbaXDataBrowserController::queryInterface(_rType);
    if (!aReturn.hasValue())
        aReturn = SbaTableQueryBrowser_Base::queryInterface(_rType);
    return aReturn;
}

//------------------------------------------------------------------------------
Sequence< Type > SAL_CALL SbaTableQueryBrowser::getTypes(  ) throw (RuntimeException)
{
    return ::comphelper::concatSequences(
        SbaXDataBrowserController::getTypes(),
        SbaTableQueryBrowser_Base::getTypes()
    );
}

//------------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL SbaTableQueryBrowser::getImplementationId(  ) throw (RuntimeException)
{
    static ::cppu::OImplementationId aId;
    return aId.getImplementationId();
}

//------------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::disposing()
{
    ::vos::OGuard aGuard(Application::GetSolarMutex());
        // doin' a lot of VCL stuff here -> lock the SolarMutex

    // kiss our listeners goodbye
    EventObject aEvt(*this);
    m_aSelectionListeners.disposeAndClear(aEvt);

    // reset the content's tree view: it holds a reference to our model which is to be deleted immediately,
    // and it will live longer than we do.
    if (getBrowserView())
        getBrowserView()->setTreeView(NULL);

    if (m_pTreeModel)
    {
        // clear the user data of the tree model
        SvLBoxEntry* pEntryLoop = m_pTreeModel->First();
        while (pEntryLoop)
        {
            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntryLoop->GetUserData());
            if(pData)
            {
                Reference<XConnection> xCon(pData->xObject,UNO_QUERY);
                if(xCon.is())
                {
                    Reference< XComponent >  xComponent(xCon, UNO_QUERY);
                    if (xComponent.is())
                    {
                        Reference< ::com::sun::star::lang::XEventListener> xEvtL((::cppu::OWeakObject*)this,UNO_QUERY);
                        xComponent->removeEventListener(xEvtL);
                    }
                    ::comphelper::disposeComponent(pData->xObject);
                }
                delete pData;
            }
            pEntryLoop = m_pTreeModel->Next(pEntryLoop);
        }
    }
    m_pCurrentlyDisplayed = NULL;
    // clear the tree model
    delete m_pTreeModel;
    m_pTreeModel = NULL;

    // remove ourself as status listener
    implRemoveStatusListeners();

    // remove the container listener from the database context
    Reference< XContainer > xDatasourceContainer(m_xDatabaseContext, UNO_QUERY);
    if (xDatasourceContainer.is())
        xDatasourceContainer->removeContainerListener(this);

    SbaXDataBrowserController::disposing();
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::Construct(Window* pParent)
{
    if (!SbaXDataBrowserController::Construct(pParent))
        return sal_False;

    try
    {
        Reference< XContainer > xDatasourceContainer(m_xDatabaseContext, UNO_QUERY);
        if (xDatasourceContainer.is())
            xDatasourceContainer->addContainerListener(this);
        else
            DBG_ERROR("SbaTableQueryBrowser::Construct: the DatabaseContext should allow us to be a listener!");

        // the collator for the string compares
        m_xCollator = Reference< XCollator >(getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.i18n.Collator")), UNO_QUERY);
        if (m_xCollator.is())
            m_xCollator->loadDefaultCollator(Application::GetSettings().GetLocale(), 0);
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::Construct: could not create (or start listening at) the database context!");
    }
    // some help ids
    if (getBrowserView() && getBrowserView()->getVclControl())
    {

        // create controls and set sizes
        const long	nFrameWidth = getBrowserView()->LogicToPixel( Size( 3, 0 ), MAP_APPFONT ).Width();

        m_pSplitter = new Splitter(getBrowserView(),WB_HSCROLL);
        m_pSplitter->SetPosSizePixel( Point(0,0), Size(nFrameWidth,0) );
        m_pSplitter->SetBackground( Wallpaper( Application::GetSettings().GetStyleSettings().GetDialogColor() ) );
        m_pSplitter->Show();

        m_pTreeView = new DBTreeView(getBrowserView(),m_xMultiServiceFacatory, WB_TABSTOP);
        m_pTreeView->Show();
        m_pTreeView->SetPreExpandHandler(LINK(this, SbaTableQueryBrowser, OnExpandEntry));
        m_pTreeView->getListBox()->setControlActionListener(this);
        m_pTreeView->SetHelpId(HID_CTL_TREEVIEW);

        // a default pos for the splitter, so that the listbox is about 80 (logical) pixels wide
        m_pSplitter->SetSplitPosPixel( getBrowserView()->LogicToPixel( Size( 80, 0 ), MAP_APPFONT ).Width() );

        getBrowserView()->setSplitter(m_pSplitter);
        getBrowserView()->setTreeView(m_pTreeView);

        // fill view with data
        m_pTreeModel = new DBTreeListModel;
        m_pTreeModel->SetSortMode(SortAscending);
        m_pTreeModel->SetCompareHdl(LINK(this, SbaTableQueryBrowser, OnTreeEntryCompare));
        m_pTreeView->setModel(m_pTreeModel);
        m_pTreeView->setSelectHdl(LINK(this, SbaTableQueryBrowser, OnSelectEntry));
        m_pTreeView->getListBox()->SetDoubleClickHdl(LINK(this, SbaTableQueryBrowser, OnEntryDoubleClicked));
        initializeTreeModel();

        // TODO
        getBrowserView()->getVclControl()->GetDataWindow().SetUniqueId(UID_DATABROWSE_DATAWINDOW);
        getBrowserView()->getVclControl()->SetHelpId(HID_CTL_TABBROWSER);
        getBrowserView()->SetUniqueId(UID_CTL_CONTENT);
        if (getBrowserView()->getVclControl()->GetHeaderBar())
            getBrowserView()->getVclControl()->GetHeaderBar()->SetHelpId(HID_DATABROWSE_HEADER);
        InvalidateFeature(ID_BROWSER_EXPLORER);
    }

    return sal_True;
}
// -------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::InitializeForm(const Reference< ::com::sun::star::sdbc::XRowSet > & _rxForm)
{
    if(!m_pCurrentlyDisplayed)
        return sal_True;
    // this method set all format settings from the orignal table or query
    try
    {
        // we send all properties at once, maybe the implementation is clever enough to handle one big PropertiesChanged
        // more effective than many small PropertyChanged ;)
        Sequence< ::rtl::OUString> aProperties(3);
        Sequence< Any> aValues(3);

        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
        OSL_ENSURE(pData,"No user data set at the currently displayed entry!");
        Reference<XPropertySet> xTableProp(pData->xObject,UNO_QUERY);
        OSL_ENSURE(xTableProp.is(),"No table available!");

        // is the filter intially applied ?
        aProperties.getArray()[0]	= PROPERTY_APPLYFILTER;
        aValues.getArray()[0]		= xTableProp->getPropertyValue(PROPERTY_APPLYFILTER);

        // the initial filter
        aProperties.getArray()[1]	= PROPERTY_FILTER;
        aValues.getArray()[1]		= xTableProp->getPropertyValue(PROPERTY_FILTER);

        // the initial ordering
        aProperties.getArray()[2]	= PROPERTY_ORDER;
        aValues.getArray()[2]		= xTableProp->getPropertyValue(PROPERTY_ORDER);

        Reference< XMultiPropertySet >  xFormMultiSet(_rxForm, UNO_QUERY);
        xFormMultiSet->setPropertyValues(aProperties, aValues);
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::InitializeForm : something went wrong !");
        return sal_False;
    }


    return sal_True;
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::InitializeGridModel(const Reference< ::com::sun::star::form::XFormComponent > & xGrid)
{
    try
    {

        Reference< ::com::sun::star::form::XGridColumnFactory >  xColFactory(xGrid, UNO_QUERY);
        Reference< XNameContainer >  xColContainer(xGrid, UNO_QUERY);
        // first we have to clear the grid
        {
            Sequence< ::rtl::OUString > aNames = xColContainer->getElementNames();
            const ::rtl::OUString* pBegin	= aNames.getConstArray();
            const ::rtl::OUString* pEnd		= pBegin + aNames.getLength();
            for (; pBegin != pEnd;++pBegin)
                xColContainer->removeByName(*pBegin);
        }

        Reference< XChild > xGridAsChild(xGrid, UNO_QUERY);
        Reference< XLoadable > xFormAsLoadable;
        if (xGridAsChild.is())
            xFormAsLoadable = xFormAsLoadable.query(xGridAsChild->getParent());
        if (xFormAsLoadable.is() && xFormAsLoadable->isLoaded())
        {
            // set the formats from the table
            if(m_pCurrentlyDisplayed)
            {
                Sequence< ::rtl::OUString> aProperties(6);
                Sequence< Any> aValues(6);

                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
                Reference<XPropertySet> xTableProp(pData->xObject,UNO_QUERY);
                OSL_ENSURE(xTableProp.is(),"SbaTableQueryBrowser::InitializeGridModel: No table available!");

                aProperties.getArray()[0]	= PROPERTY_FONT;
                aValues.getArray()[0]		= xTableProp->getPropertyValue(PROPERTY_FONT);
                aProperties.getArray()[1]	= PROPERTY_TEXTEMPHASIS;
                aValues.getArray()[1]		= xTableProp->getPropertyValue(PROPERTY_TEXTEMPHASIS);
                aProperties.getArray()[2]	= PROPERTY_TEXTRELIEF;
                aValues.getArray()[2]		= xTableProp->getPropertyValue(PROPERTY_TEXTRELIEF);
                aProperties.getArray()[3]	= PROPERTY_ROW_HEIGHT;
                aValues.getArray()[3]		= xTableProp->getPropertyValue(PROPERTY_ROW_HEIGHT);
                aProperties.getArray()[4]	= PROPERTY_TEXTCOLOR;
                aValues.getArray()[4]		= xTableProp->getPropertyValue(PROPERTY_TEXTCOLOR);
                aProperties.getArray()[5]	= PROPERTY_TEXTLINECOLOR;
                aValues.getArray()[5]		= xTableProp->getPropertyValue(PROPERTY_TEXTLINECOLOR);

                Reference< XMultiPropertySet >  xFormMultiSet(xGrid, UNO_QUERY);
                xFormMultiSet->setPropertyValues(aProperties, aValues);
            }


            // get the formats supplier of the database we're working with
            Reference< ::com::sun::star::util::XNumberFormatsSupplier >  xSupplier = getNumberFormatter()->getNumberFormatsSupplier();

            Reference<XConnection> xConnection;
            Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
            ::cppu::extractInterface(xConnection,xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION));
            OSL_ENSURE(xConnection.is(),"A ActiveConnection should normaly exists!");

            Reference<XChild> xChild(xConnection,UNO_QUERY);
            Reference<XPropertySet> xDataSourceProp(xChild->getParent(),UNO_QUERY);
            sal_Bool bSupress = ::cppu::any2bool(xDataSourceProp->getPropertyValue(PROPERTY_SUPPRESSVERSIONCL));

            // insert the column into the gridcontrol so that we see something :-)
            ::rtl::OUString aCurrentModelType;
            Reference<XColumnsSupplier> xSupCols(getRowSet(),UNO_QUERY);
            Reference<XNameAccess> xColumns		= xSupCols->getColumns();
            Sequence< ::rtl::OUString> aNames	= xColumns->getElementNames();
            const ::rtl::OUString* pBegin		= aNames.getConstArray();
            const ::rtl::OUString* pEnd			= pBegin + aNames.getLength();

            Reference<XPropertySet> xColumn;
            for (sal_uInt16 i=0; pBegin != pEnd; ++i,++pBegin)
            {
                // Typ
                // first get type to determine wich control we need
                ::cppu::extractInterface(xColumn,xColumns->getByName(*pBegin));

                // ignore the column when it is a rowversion one
                if(bSupress && xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ISROWVERSION)
                            && ::cppu::any2bool(xColumn->getPropertyValue(PROPERTY_ISROWVERSION)))
                    continue;

                sal_Bool bIsFormatted			= sal_False;
                sal_Bool bFormattedIsNumeric	= sal_True;
                sal_Int32 nType = comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_TYPE));
                switch(nType)
                {
                    // TODO : die Strings fuer die Column-Typen irgendwo richtig platzieren
                    case DataType::BIT:
                        aCurrentModelType = ::rtl::OUString::createFromAscii("CheckBox");
                        break;

                    case DataType::BINARY:
                    case DataType::VARBINARY:
                    case DataType::LONGVARBINARY:
                        aCurrentModelType = ::rtl::OUString::createFromAscii("TextField");
                        break;

                    case DataType::VARCHAR:
                    case DataType::LONGVARCHAR:
                    case DataType::CHAR:
                        bFormattedIsNumeric = sal_False;
                        // _NO_ break !
                    default:
                        aCurrentModelType = ::rtl::OUString::createFromAscii("FormattedField");
                        bIsFormatted = sal_True;
                        break;
                }

                Reference< XPropertySet >  xCurrentCol = xColFactory->createColumn(aCurrentModelType);
                xCurrentCol->setPropertyValue(PROPERTY_CONTROLSOURCE, makeAny(*pBegin));
                xCurrentCol->setPropertyValue(PROPERTY_LABEL, makeAny(*pBegin));
                if (bIsFormatted)
                {
                    if (xSupplier.is())
                        xCurrentCol->setPropertyValue(::rtl::OUString::createFromAscii("FormatsSupplier"), makeAny(xSupplier));
                    xCurrentCol->setPropertyValue(PROPERTY_FORMATKEY, xColumn->getPropertyValue(PROPERTY_FORMATKEY));
                    xCurrentCol->setPropertyValue(::rtl::OUString::createFromAscii("TreatAsNumber"), ::cppu::bool2any(bFormattedIsNumeric));
                }

                // default value
                if (nType == DataType::BIT)
                {
                    Any aDefault; aDefault <<= ((sal_Int16)STATE_DONTKNOW);
                    if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
                        aDefault <<= (comphelper::getString(xColumn->getPropertyValue(PROPERTY_DEFAULTVALUE)).toInt32() == 0) ? (sal_Int16)STATE_NOCHECK : (sal_Int16)STATE_CHECK;
                    xCurrentCol->setPropertyValue(PROPERTY_DEFAULTSTATE, aDefault);
                }

                // transfer properties from the definition to the UNO-model :
                // ... the hidden flag
                xCurrentCol->setPropertyValue(PROPERTY_HIDDEN, xColumn->getPropertyValue(PROPERTY_HIDDEN));

                // ... the initial colum width
                xCurrentCol->setPropertyValue(PROPERTY_WIDTH, xColumn->getPropertyValue(PROPERTY_WIDTH));

                // ... horizontal justify
                xCurrentCol->setPropertyValue(PROPERTY_ALIGN, makeAny(sal_Int16(::comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_ALIGN)))));

                // ... the 'comment' property as helptext (will usually be shown as header-tooltip)

                Any aDescription; aDescription <<= ::rtl::OUString();
                if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
                    aDescription <<= comphelper::getString(xColumn->getPropertyValue(PROPERTY_DESCRIPTION));
                xCurrentCol->setPropertyValue(PROPERTY_HELPTEXT, xColumn->getPropertyValue(PROPERTY_DESCRIPTION));

                xColContainer->insertByName(*pBegin, makeAny(xCurrentCol));
            }
        }
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::InitializeGridModel : something went wrong !");
        return sal_False;
    }


    return sal_True;
}

//------------------------------------------------------------------------------
ToolBox* SbaTableQueryBrowser::CreateToolBox(Window* _pParent)
{
    return new ToolBox(_pParent, ModuleRes(RID_BRW_QRY_TOOLBOX));
}

// -----------------------------------------------------------------------------
Reference<XPropertySet> getColumnHelper(SvLBoxEntry* _pCurrentlyDisplayed,const Reference<XPropertySet>& _rxSource)
{
    Reference<XPropertySet> xRet;
    if(_pCurrentlyDisplayed)
    {
        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pCurrentlyDisplayed->GetUserData());
        Reference<XColumnsSupplier> xColumnsSup(pData->xObject,UNO_QUERY);
        Reference<XNameAccess> xNames = xColumnsSup->getColumns();
        ::rtl::OUString aName;
        _rxSource->getPropertyValue(PROPERTY_NAME) >>= aName;
        if(xNames.is() && xNames->hasByName(aName))
            ::cppu::extractInterface(xRet,xNames->getByName(aName));
    }
    return xRet;
}

// -----------------------------------------------------------------------
void SbaTableQueryBrowser::transferChangedControlProperty(const ::rtl::OUString& _rProperty, const Any& _rNewValue)
{
    if(m_pCurrentlyDisplayed)
    {
        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
        Reference< XPropertySet > xProp(pData->xObject, UNO_QUERY);
        OSL_ENSURE(xProp.is(),"SbaTableQueryBrowser::transferChangedControlProperty: no table/query object!");
        if (xProp.is())
            xProp->setPropertyValue(_rProperty, _rNewValue);
    }
}

// -----------------------------------------------------------------------
void SbaTableQueryBrowser::propertyChange(const PropertyChangeEvent& evt)
{
    SbaXDataBrowserController::propertyChange(evt);

    try
    {
        Reference< XPropertySet >  xSource(evt.Source, UNO_QUERY);
        if (!xSource.is())
            return;

        // one of the many properties which require us to update the definition ?
        // a column's width ?
        else if (evt.PropertyName.equals(PROPERTY_WIDTH))
        {	// a column width has changed -> update the model
            // (the update of the view is done elsewhere)
            Reference<XPropertySet> xProp = getColumnHelper(m_pCurrentlyDisplayed,xSource);
            if(xProp.is())
            {
                if(!evt.NewValue.hasValue())
                    xProp->setPropertyValue(PROPERTY_WIDTH,makeAny((sal_Int32)227));
                else
                    xProp->setPropertyValue(PROPERTY_WIDTH,evt.NewValue);
            }
        }

        // a column's 'visible' state ?
        else if (evt.PropertyName.equals(PROPERTY_HIDDEN))
        {
            Reference<XPropertySet> xProp = getColumnHelper(m_pCurrentlyDisplayed,xSource);
            if(xProp.is())
                xProp->setPropertyValue(PROPERTY_HIDDEN,evt.NewValue);
        }

        // a columns alignment ?
        else if (evt.PropertyName.equals(PROPERTY_ALIGN))
        {
            Reference<XPropertySet> xProp = getColumnHelper(m_pCurrentlyDisplayed,xSource);
            try
            {
                if(xProp.is())
                {
                    if(evt.NewValue.hasValue())
                    {
                        sal_Int16 nAlign = 0;
                        if(evt.NewValue >>= nAlign)
                            xProp->setPropertyValue(PROPERTY_ALIGN,makeAny(sal_Int32(nAlign)));
                        else
                            xProp->setPropertyValue(PROPERTY_ALIGN,evt.NewValue);
                    }
                    else
                        xProp->setPropertyValue(PROPERTY_ALIGN,makeAny((sal_Int32)0));
                }
            }
            catch(Exception&)
            {
                OSL_ENSURE(sal_False, "SbaTableQueryBrowser::propertyChange: caught an exception!");
            }
        }

        // a column's format ?
        else if	(	(evt.PropertyName.equals(PROPERTY_FORMATKEY))
            &&	(TypeClass_LONG == evt.NewValue.getValueTypeClass())
            )
        {
            // update the model (means the definition object)
            Reference<XPropertySet> xProp = getColumnHelper(m_pCurrentlyDisplayed,xSource);
            if(xProp.is())
                xProp->setPropertyValue(PROPERTY_FORMATKEY,evt.NewValue);
        }

        // some table definition properties ?
        // the height of the rows in the grid ?
        else if (evt.PropertyName.equals(PROPERTY_ROW_HEIGHT))
        {
            if(m_pCurrentlyDisplayed)
            {
                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
                Reference<XPropertySet> xProp(pData->xObject,UNO_QUERY);
                OSL_ENSURE(xProp.is(),"No table available!");

                sal_Bool bDefault = !evt.NewValue.hasValue();
                if (bDefault)
                    xProp->setPropertyValue(PROPERTY_ROW_HEIGHT,makeAny((sal_Int32)45));
                else
                    xProp->setPropertyValue(PROPERTY_ROW_HEIGHT,evt.NewValue);
            }
        }

        else if	(	evt.PropertyName.equals(PROPERTY_FONT)			// the font ?
                ||	evt.PropertyName.equals(PROPERTY_TEXTCOLOR)		// the text color ?
                ||	evt.PropertyName.equals(PROPERTY_FILTER)		// the filter ?
                ||	evt.PropertyName.equals(PROPERTY_ORDER)			// the sort ?
                ||	evt.PropertyName.equals(PROPERTY_APPLYFILTER)	// the appliance of the filter ?
                ||	evt.PropertyName.equals(PROPERTY_TEXTLINECOLOR)	// the text line color ?
                ||	evt.PropertyName.equals(PROPERTY_TEXTEMPHASIS)	// the text emphasis ?
                ||	evt.PropertyName.equals(PROPERTY_TEXTRELIEF)	// the text relief ?
                )
        {
            transferChangedControlProperty(evt.PropertyName, evt.NewValue);
        }
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::propertyChange: caught an exception!");
    }
}

// -----------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::suspend(sal_Bool bSuspend) throw( RuntimeException )
{
    if (!SbaXDataBrowserController::suspend(bSuspend))
        return sal_False;

    if(m_pCurrentlyDisplayed)
    {
        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
        if(pData)
        {
            try
            {
                Reference<XFlushable> xFlush(pData->xObject,UNO_QUERY);
                if(xFlush.is())
                    xFlush->flush();
            }
            catch(DisposedException&)
            {
                OSL_ENSURE(0,"Object already disposed!");
            }
            catch(Exception&)
            {
            }
        }
    }

    return sal_True;
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::statusChanged( const FeatureStateEvent& _rEvent ) throw(RuntimeException)
{
    // search the external dispatcher causing this call
    Reference< XDispatch > xSource(_rEvent.Source, UNO_QUERY);
    for	(	SpecialSlotDispatchersIterator aLoop = m_aDispatchers.begin();
            aLoop != m_aDispatchers.end();
            ++aLoop
        )
    {
        if (_rEvent.FeatureURL.Complete == getURLForId(aLoop->first).Complete)
        {
            DBG_ASSERT(xSource.get() == aLoop->second.get(), "SbaTableQueryBrowser::statusChanged: inconsistent!");
            // update the enabled state
            m_aDispatchStates[aLoop->first] = _rEvent.IsEnabled;

            switch (aLoop->first)
            {
                case ID_BROWSER_DOCUMENT_DATASOURCE:
                {
                    // if it's the slot for the document data source, remember the state
                    Sequence< PropertyValue > aDescriptor;
    #ifdef DBG_UTIL
                    sal_Bool bProperFormat =
    #endif
                    _rEvent.State >>= aDescriptor;
                    OSL_ENSURE(bProperFormat, "SbaTableQueryBrowser::statusChanged: need a data access descriptor here!");
                    m_aDocumentDataSource.initializeFrom(aDescriptor);

                    OSL_ENSURE(m_aDocumentDataSource.has(daDataSource) && m_aDocumentDataSource.has(daCommand) && m_aDocumentDataSource.has(daCommandType),
                        "SbaTableQueryBrowser::statusChanged: incomplete descriptor!");

                    // check if we know the object which is set as document data source
                    checkDocumentDataSource();
                }
                break;

                default:
                    // update the toolbox
                    implCheckExternalSlot(aLoop->first);
                    break;
            }
            break;
        }
    }

    DBG_ASSERT(aLoop != m_aDispatchers.end(), "SbaTableQueryBrowser::statusChanged: don't know who sent this!");
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::checkDocumentDataSource()
{
    SvLBoxEntry* pDataSourceEntry = NULL;
    SvLBoxEntry* pContainerEntry = NULL;
    SvLBoxEntry* pObjectEntry = getObjectEntry(m_aDocumentDataSource, &pDataSourceEntry, &pContainerEntry, sal_False);
    sal_Bool bKnownDocDataSource = (NULL != pObjectEntry);
    if (!bKnownDocDataSource)
    {
        // TODO: should we expand the object container? This may be too expensive just for checking ....
        bKnownDocDataSource = (NULL != pDataSourceEntry) && (NULL != pContainerEntry);
    }

    m_aDispatchStates[ID_BROWSER_DOCUMENT_DATASOURCE] = m_aDispatchStates[ID_BROWSER_DOCUMENT_DATASOURCE] && bKnownDocDataSource;

    // update the toolbox
    implCheckExternalSlot(ID_BROWSER_DOCUMENT_DATASOURCE);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::extractDescriptorProps(const ::svx::ODataAccessDescriptor& _rDescriptor, ::rtl::OUString& _rDataSource, ::rtl::OUString& _rCommand, sal_Int32& _rCommandType, sal_Bool& _rEscapeProcessing)
{
    _rDescriptor[daDataSource] >>= _rDataSource;
    _rDescriptor[daCommand] >>= _rCommand;
    _rDescriptor[daCommandType] >>= _rCommandType;

    // escape processing is the only one allowed not to be present
    _rEscapeProcessing = sal_True;
    if (_rDescriptor.has(daEscapeProcessing))
        _rEscapeProcessing = ::cppu::any2bool(_rDescriptor[daEscapeProcessing]);
}

// -------------------------------------------------------------------------
SvLBoxEntry* SbaTableQueryBrowser::getObjectEntry(const ::rtl::OUString& _rDataSource, const ::rtl::OUString& _rCommand, sal_Int32 _nCommandType,
        SvLBoxEntry** _ppDataSourceEntry, SvLBoxEntry** _ppContainerEntry,
        sal_Bool _bExpandAncestors)
{
    if (_ppDataSourceEntry)
        *_ppDataSourceEntry = NULL;
    if (_ppContainerEntry)
        *_ppContainerEntry = NULL;

    SvLBoxEntry* pObject = NULL;
    if (m_pTreeView && m_pTreeView->getListBox())
    {
        // look for the data source entry
        SvLBoxEntry* pDataSource = m_pTreeView->getListBox()->GetEntryPosByName(_rDataSource, NULL);
        if (_ppDataSourceEntry)
            // (caller wants to have it ...)
            *_ppDataSourceEntry = pDataSource;

        if (pDataSource)
        {
            // expand if required so
            if (_bExpandAncestors)
                m_pTreeView->getListBox()->Expand(pDataSource);

            // look for the object container
            SvLBoxEntry* pCommandType = NULL;
            switch (_nCommandType)
            {
                case CommandType::TABLE:
                    pCommandType = m_pTreeView->getListBox()->GetModel()->GetEntry(pDataSource, CONTAINER_TABLES);
                    break;

                case CommandType::QUERY:
                    pCommandType = m_pTreeView->getListBox()->GetModel()->GetEntry(pDataSource, CONTAINER_QUERIES);
                    break;
            }

            if (_ppContainerEntry)
                *_ppContainerEntry = pCommandType;

            if (pCommandType)
            {
                // expand if required so
                if (_bExpandAncestors)
                    m_pTreeView->getListBox()->Expand(pCommandType);

                // look for the object
                pObject = m_pTreeView->getListBox()->GetEntryPosByName(_rCommand, pCommandType);
            }
        }
    }
    return pObject;
}

// -------------------------------------------------------------------------
SvLBoxEntry* SbaTableQueryBrowser::getObjectEntry(const ::svx::ODataAccessDescriptor& _rDescriptor,
        SvLBoxEntry** _ppDataSourceEntry, SvLBoxEntry** _ppContainerEntry,
        sal_Bool _bExpandAncestors)
{
    // extract the props from the descriptor
    ::rtl::OUString sDataSource;
    ::rtl::OUString sCommand;
    sal_Int32 nCommandType = CommandType::COMMAND;
    sal_Bool bEscapeProcessing = sal_True;
    extractDescriptorProps(_rDescriptor, sDataSource, sCommand, nCommandType, bEscapeProcessing);

    return getObjectEntry(sDataSource, sCommand, nCommandType, _ppContainerEntry, _ppDataSourceEntry, _bExpandAncestors);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::connectExternalDispatches()
{
    Reference< XDispatchProvider >  xProvider(m_xCurrentFrame, UNO_QUERY);
    DBG_ASSERT(xProvider.is(), "SbaTableQueryBrowser::attachFrame: no DispatchPprovider !");
    if (xProvider.is())
    {
        sal_Int32 nExternalIds[] = { ID_BROWSER_DOCUMENT_DATASOURCE, ID_BROWSER_FORMLETTER, ID_BROWSER_INSERTCOLUMNS, ID_BROWSER_INSERTCONTENT };
        for (sal_Int32 i=0; i<sizeof(nExternalIds)/sizeof(nExternalIds[0]); ++i)
        {
            URL aURL = getURLForId(nExternalIds[i]);
            m_aDispatchers[nExternalIds[i]] = xProvider->queryDispatch(aURL, ::rtl::OUString::createFromAscii("_parent"), FrameSearchFlag::PARENT);
            if (m_aDispatchers[nExternalIds[i]].get() == static_cast< XDispatch* >(this))
                // as the URL is one of our "supported features", we may answer the request ourself if nobody out there
                // is interested in.
                m_aDispatchers[nExternalIds[i]].clear();

            // assume te general availability of the feature. This is overruled if there is no dispatcher for the URL
            m_aDispatchStates[nExternalIds[i]] = sal_True;

            if (m_aDispatchers[nExternalIds[i]].is())
            {
                try
                {
                    m_aDispatchers[nExternalIds[i]]->addStatusListener(this, aURL);
                }
                catch(DisposedException&)
                {
                    OSL_ENSURE(0,"Object already disposed!");
                }
                catch(Exception&)
                {
                    DBG_ERROR("SbaTableQueryBrowser::attachFrame: could not attach a status listener!");
                }
            }

            implCheckExternalSlot(nExternalIds[i]);
        }
    }
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::implCheckExternalSlot(sal_Int32 _nId)
{
    // check if we have to hide this item from the toolbox
    ToolBox* pTB = getBrowserView()->getToolBox();
    if (pTB)
    {
        sal_Bool bHaveDispatcher = m_aDispatchers[_nId].is();
        if (bHaveDispatcher != pTB->IsItemVisible((sal_uInt16)_nId))
            bHaveDispatcher ? pTB->ShowItem((sal_uInt16)_nId) : pTB->HideItem((sal_uInt16)_nId);
    }

    // and invalidate this feature in general
    InvalidateFeature((sal_uInt16)_nId);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::disposing( const EventObject& _rSource ) throw(RuntimeException)
{
    // search the external dispatcher causing this call in our map
    Reference< XDispatch > xSource(_rSource.Source, UNO_QUERY);
    if(xSource.is())
    {
        for	(	SpecialSlotDispatchersIterator aLoop = m_aDispatchers.begin();
                aLoop != m_aDispatchers.end();
                ++aLoop
            )
        {
            if (aLoop->second.get() == xSource.get())
            {
                SpecialSlotDispatchersIterator aPrevious = aLoop;
                --aPrevious;

                // remove it
                m_aDispatchers.erase(aLoop);
                m_aDispatchStates.erase(aLoop->first);

                // maybe update the UI
                implCheckExternalSlot(aLoop->first);

                // continue, the same XDispatch may be resposible for more than one URL
                aLoop = aPrevious;
            }
        }
    }
    else
    {
        Reference<XConnection> xCon(_rSource.Source, UNO_QUERY);
        if(xCon.is())
        {	// our connection is in dispose so we have to find the entry equal with this connection
            // and close it what means to collapse the entry
            // get the top-level representing the removed data source
            SvLBoxEntry* pDSLoop = m_pTreeView->getListBox()->FirstChild(NULL);
            while (pDSLoop)
            {
                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pDSLoop->GetUserData());
                if(pData && pData->xObject == xCon)
                {
                    // we set the conenction to null to avoid a second disposing of the connection
                    pData->xObject = NULL;
                    closeConnection(pDSLoop,sal_False);
                    break;
                }

                pDSLoop = m_pTreeView->getListBox()->NextSibling(pDSLoop);
            }
        }
        else
            SbaXDataBrowserController::disposing(_rSource);
    }
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::implRemoveStatusListeners()
{
    // clear all old dispatches
    for	(	ConstSpecialSlotDispatchersIterator aLoop = m_aDispatchers.begin();
            aLoop != m_aDispatchers.end();
            ++aLoop
        )
    {
        if (aLoop->second.is())
        {
            try
            {
                aLoop->second->removeStatusListener(this, getURLForId(aLoop->first));
            }
            catch (Exception&)
            {
                DBG_ERROR("SbaTableQueryBrowser::attachFrame: could not remove a status listener!");
            }
        }
    }
    m_aDispatchers.clear();
    m_aDispatchStates.clear();
}

// -------------------------------------------------------------------------
sal_Bool SAL_CALL SbaTableQueryBrowser::select( const Any& _rSelection ) throw (IllegalArgumentException, RuntimeException)
{
    Sequence< PropertyValue > aDescriptorSequence;
    if (!(_rSelection >>= aDescriptorSequence))
        throw IllegalArgumentException(::rtl::OUString(), *this, 1);
        // TODO: error message

    ODataAccessDescriptor aDescriptor;
    try
    {
        aDescriptor = ODataAccessDescriptor(aDescriptorSequence);
    }
    catch(const Exception&)
    {
        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::select: could not extract the descriptor!");
    }

    // check the precense of the props we need
    if (!aDescriptor.has(daDataSource) || !aDescriptor.has(daCommand) || !aDescriptor.has(daCommandType))
        throw IllegalArgumentException(::rtl::OUString(), *this, 1);
        // TODO: error message

    return implSelect(aDescriptor);
}

// -------------------------------------------------------------------------
Any SAL_CALL SbaTableQueryBrowser::getSelection(  ) throw (RuntimeException)
{
    Any aReturn;

    try
    {
        Reference< XLoadable > xLoadable(getRowSet(), UNO_QUERY);
        if (xLoadable.is() && xLoadable->isLoaded())
        {
            Reference< XPropertySet > aFormProps(getRowSet(), UNO_QUERY);
            ODataAccessDescriptor aDescriptor(aFormProps);
            // remove properties which are not part of our "selection"
            aDescriptor.erase(daConnection);
            aDescriptor.erase(daCursor);

            aReturn <<= aDescriptor.createPropertyValueSequence();
        }
    }
    catch(const Exception&)
    {
        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::getSelection: caught an exception while retrieving the selection!");
    }

    return aReturn;
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::addSelectionChangeListener( const Reference< XSelectionChangeListener >& _rxListener ) throw (RuntimeException)
{
    m_aSelectionListeners.addInterface(_rxListener);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::removeSelectionChangeListener( const Reference< XSelectionChangeListener >& _rxListener ) throw (RuntimeException)
{
    m_aSelectionListeners.removeInterface(_rxListener);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::attachFrame(const Reference< ::com::sun::star::frame::XFrame > & _xFrame) throw( RuntimeException )
{
    implRemoveStatusListeners();

    SbaXDataBrowserController::attachFrame(_xFrame);

    // get the dispatchers for the external slots
    connectExternalDispatches();
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::addModelListeners(const Reference< ::com::sun::star::awt::XControlModel > & _xGridControlModel)
{
    SbaXDataBrowserController::addModelListeners(_xGridControlModel);
    Reference< XPropertySet >  xSourceSet(_xGridControlModel, UNO_QUERY);
    if (xSourceSet.is())
    {
        xSourceSet->addPropertyChangeListener(PROPERTY_ROW_HEIGHT, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->addPropertyChangeListener(PROPERTY_FONT, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->addPropertyChangeListener(PROPERTY_TEXTCOLOR, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->addPropertyChangeListener(PROPERTY_TEXTLINECOLOR, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->addPropertyChangeListener(PROPERTY_TEXTEMPHASIS, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->addPropertyChangeListener(PROPERTY_TEXTRELIEF, static_cast<XPropertyChangeListener*>(this));
    }

}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::removeModelListeners(const Reference< ::com::sun::star::awt::XControlModel > & _xGridControlModel)
{
    SbaXDataBrowserController::removeModelListeners(_xGridControlModel);
    Reference< XPropertySet >  xSourceSet(_xGridControlModel, UNO_QUERY);
    if (xSourceSet.is())
    {
        xSourceSet->removePropertyChangeListener(PROPERTY_ROW_HEIGHT, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->removePropertyChangeListener(PROPERTY_FONT, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->removePropertyChangeListener(PROPERTY_TEXTCOLOR, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->removePropertyChangeListener(PROPERTY_TEXTLINECOLOR, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->removePropertyChangeListener(PROPERTY_TEXTEMPHASIS, static_cast<XPropertyChangeListener*>(this));
        xSourceSet->removePropertyChangeListener(PROPERTY_TEXTRELIEF, static_cast<XPropertyChangeListener*>(this));
    }
}
// -------------------------------------------------------------------------
void SbaTableQueryBrowser::RowChanged()
{
    if(getBrowserView())
    {
        SbaGridControl* pControl = getBrowserView()->getVclControl();
        if (!pControl->IsEditing())
            InvalidateFeature(ID_BROWSER_COPY);
    }
    SbaXDataBrowserController::RowChanged();
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::ColumnChanged()
{
    if(getBrowserView())
    {
        SbaGridControl* pControl = getBrowserView()->getVclControl();
        if (!pControl->IsEditing())
            InvalidateFeature(ID_BROWSER_COPY);
    }
    SbaXDataBrowserController::ColumnChanged();
}

// -------------------------------------------------------------------------
String SbaTableQueryBrowser::getURL() const
{
    return String();
}
// -----------------------------------------------------------------------
void SbaTableQueryBrowser::InvalidateFeature(sal_uInt16 nId, const Reference< ::com::sun::star::frame::XStatusListener > & xListener)
{
    SbaXDataBrowserController::InvalidateFeature(nId, xListener);
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::AddColumnListener(const Reference< XPropertySet > & xCol)
{
    SbaXDataBrowserController::AddColumnListener(xCol);
    SafeAddPropertyListener(xCol, PROPERTY_WIDTH, static_cast<XPropertyChangeListener*>(this));
    SafeAddPropertyListener(xCol, PROPERTY_HIDDEN, static_cast<XPropertyChangeListener*>(this));
    SafeAddPropertyListener(xCol, PROPERTY_ALIGN, static_cast<XPropertyChangeListener*>(this));
    SafeAddPropertyListener(xCol, PROPERTY_FORMATKEY, static_cast<XPropertyChangeListener*>(this));
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::RemoveColumnListener(const Reference< XPropertySet > & xCol)
{
    SbaXDataBrowserController::RemoveColumnListener(xCol);
    SafeRemovePropertyListener(xCol, PROPERTY_WIDTH, static_cast<XPropertyChangeListener*>(this));
    SafeRemovePropertyListener(xCol, PROPERTY_HIDDEN, static_cast<XPropertyChangeListener*>(this));
    SafeRemovePropertyListener(xCol, PROPERTY_ALIGN, static_cast<XPropertyChangeListener*>(this));
    SafeRemovePropertyListener(xCol, PROPERTY_FORMATKEY, static_cast<XPropertyChangeListener*>(this));
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::FormLoaded(sal_Bool _bWasSynch)
{
    SbaXDataBrowserController::FormLoaded(_bWasSynch);

    // if the form has been loaded, this means that our "selection" has changed
    ::com::sun::star::lang::EventObject aEvt(*this);
    ::cppu::OInterfaceIteratorHelper aIter(m_aSelectionListeners);
    while (aIter.hasMoreElements())
        static_cast< XSelectionChangeListener* >(aIter.next())->selectionChanged(aEvt);
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::AddSupportedFeatures()
{
    SbaXDataBrowserController::AddSupportedFeatures();

    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Title")]				= ID_BROWSER_TITLE;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/FormLetter")]	= ID_BROWSER_FORMLETTER;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/InsertColumns")] = ID_BROWSER_INSERTCOLUMNS;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/InsertContent")] = ID_BROWSER_INSERTCONTENT;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/ToggleExplore")] = ID_BROWSER_EXPLORER;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/DocumentDataSource")] = ID_BROWSER_DOCUMENT_DATASOURCE;

            // TODO reenable our own code if we really have a handling for the formslots
//	ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToFirst"),		SID_FM_RECORD_FIRST		),
//	ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToLast"),		SID_FM_RECORD_LAST		),
//	ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToNew"),		SID_FM_RECORD_NEW		),
//	ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToNext"),		SID_FM_RECORD_NEXT		),
//	ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToPrev"),		SID_FM_RECORD_PREV		)

}

//------------------------------------------------------------------------------
FeatureState SbaTableQueryBrowser::GetState(sal_uInt16 nId)
{
    FeatureState aReturn;
        // (disabled automatically)

    // no chance without a view
    if (!getBrowserView() || !getBrowserView()->getVclControl())
        return aReturn;

    // "toggle explorer" is always enabled (if we have a explorer)
    if (ID_BROWSER_EXPLORER == nId)
    {       // this slot is available even if no form is loaded
        aReturn.bEnabled = sal_True;
        aReturn.aState = ::cppu::bool2any(haveExplorer());
        return aReturn;
    }

    try
    {
        sal_Bool bHandled = sal_False;
        switch (nId)
        {
            case ID_BROWSER_CLOSE:
                // the close button should always be enabled
                aReturn.bEnabled = sal_True;
                bHandled = sal_True;
                break;

            case ID_BROWSER_DOCUMENT_DATASOURCE:
                // the slot is enabled if we have an external dispatcher able to handle it,
                // and the dispatcher must have enabled the slot in general
                if (m_aDispatchers[nId].is())
                    aReturn.bEnabled = m_aDispatchStates[nId];
                else
                    aReturn.bEnabled = sal_False;
                bHandled = sal_True;
                break;
        }

        if (bHandled)
            return aReturn;

        // no chance without valid models
        if (isValid() && !isValidCursor() && nId != ID_BROWSER_CLOSE) 
            return aReturn;

        // no chance while loading the form
        if (PendingLoad())
            return aReturn;

        switch (nId)
        {
            case ID_BROWSER_INSERTCOLUMNS:
            case ID_BROWSER_INSERTCONTENT:
            case ID_BROWSER_FORMLETTER:
            {
                // the slot is enabled if we have an external dispatcher able to handle it,
                // and the dispatcher must have enabled the slot in general
                if (m_aDispatchers[nId].is())
                    aReturn.bEnabled = m_aDispatchStates[nId];
                else
                    aReturn.bEnabled = sal_False;

                // for the Insert* slots, we need at least one selected row
                if (ID_BROWSER_FORMLETTER != nId)
                    aReturn.bEnabled = aReturn.bEnabled && getBrowserView()->getVclControl()->GetSelectRowCount();

                // disabled for native queries which are not saved within the database
                // 67706 - 23.08.99 - FS
                Reference< XPropertySet >  xDataSource(getRowSet(), UNO_QUERY);
                try
                {
                    aReturn.bEnabled = aReturn.bEnabled && xDataSource.is();

                    if (xDataSource.is())
                    {
                        sal_Int32 nType = ::comphelper::getINT32(xDataSource->getPropertyValue(PROPERTY_COMMANDTYPE));
                        aReturn.bEnabled = aReturn.bEnabled && ((::comphelper::getBOOL(xDataSource->getPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING)) || (nType == ::com::sun::star::sdb::CommandType::QUERY)));
                    }
                }
                catch(DisposedException&)
                {
                    OSL_ENSURE(sal_False, "SbaTableQueryBrowser::GetState: object already disposed!");
                }
                catch(Exception&)
                {
                    OSL_ENSURE(sal_False, "SbaTableQueryBrowser::GetState: caught a strange exception!!");
                }

            }
            break;
            case ID_BROWSER_TITLE:
                {
                    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
                    sal_Int32 nCommandType = CommandType::TABLE;
                    xProp->getPropertyValue(PROPERTY_COMMANDTYPE) >>= nCommandType;
                    String sTitle;
                    switch (nCommandType)
                    {
                        case CommandType::TABLE:
                            sTitle = String(ModuleRes(STR_TBL_TITLE)); break;
                        case CommandType::QUERY:
                        case CommandType::COMMAND:
                            sTitle = String(ModuleRes(STR_QRY_TITLE)); break;
                        default:
                            DBG_ASSERT(sal_False, "SbaTableQueryBrowser::GetState: unknown command type!");
                    }
                    ::rtl::OUString aName;
                    xProp->getPropertyValue(PROPERTY_COMMAND) >>= aName;
                    String sObject(aName.getStr());

                    sTitle.SearchAndReplace('#',sObject);
                    aReturn.aState <<= ::rtl::OUString(sTitle);
                    aReturn.bEnabled = sal_True;
                }
                break;
            case ID_BROWSER_TABLEATTR:
            case ID_BROWSER_ROWHEIGHT:
            case ID_BROWSER_COLATTRSET:
            case ID_BROWSER_COLWIDTH:
                aReturn.bEnabled = getBrowserView() && getBrowserView()->getVclControl() && isValid() && isValidCursor();
                //	aReturn.bEnabled &= getDefinition() && !getDefinition()->GetDatabase()->IsReadOnly();
                break;

            case ID_BROWSER_EDITDOC:
                aReturn = SbaXDataBrowserController::GetState(nId);
                //	aReturn.bEnabled &= !getDefinition()->IsLocked();
                    // somebody is modifying the definition -> no edit mode
                break;

            case ID_BROWSER_COPY:
                if(m_pTreeView->HasChildPathFocus())
                {
                    SvLBoxEntry* pEntry = m_pTreeView->getListBox()->GetCurEntry();
                    EntryType eType = getEntryType(pEntry);
                    aReturn.bEnabled = (eType == etTable || eType == etQuery || eType == etView);
                    break;
                }
                else if (getBrowserView() && getBrowserView()->getVclControl() && !getBrowserView()->getVclControl()->IsEditing())
                {
                    SbaGridControl* pControl = getBrowserView()->getVclControl();
                    aReturn.bEnabled = pControl->canCopyCellText(pControl->GetCurRow(), pControl->GetCurColumnId());
                }
                else
                    return SbaXDataBrowserController::GetState(nId);
                break;

            case ID_BROWSER_CUT:
                if(m_pTreeView->HasChildPathFocus())
                    aReturn.bEnabled = sal_False;
                else
                    return SbaXDataBrowserController::GetState(nId);
                break;

            case ID_BROWSER_PASTE:
                // first look which side is active
                if(m_pTreeView->HasChildPathFocus())
                {
                    SvLBoxEntry* pEntry = m_pTreeView->getListBox()->GetCurEntry();
                    EntryType eType = getEntryType(pEntry);
                    switch(eType)
                    {
                        case etQuery:
                        case etQueryContainer:
                        {
#if SUPD < 631
                            TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard());
#else
                            TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(getView()));
#endif
                            aReturn.bEnabled = aTransferData.HasFormat(SOT_FORMATSTR_ID_DBACCESS_QUERY);
                            break;
                        }
                        case etView:
                        case etTable:
                        case etTableContainer:
                            aReturn.bEnabled = ((eType == etTable || eType == etView || eType == etTableContainer) && isTableFormat());
                            break;
                        default:
                            aReturn.bEnabled = sal_False;
                    }
                    break;
                }
                else
                    return SbaXDataBrowserController::GetState(nId);
                break;

            default:
                return SbaXDataBrowserController::GetState(nId);
        }
    }
    catch(Exception& e)
    {
#if DBG_UTIL
        String sMessage("SbaXDataBrowserController::GetState(", RTL_TEXTENCODING_ASCII_US);
        sMessage += String::CreateFromInt32(nId);
        sMessage.AppendAscii(") : catched an exception ! message : ");
        sMessage += (const sal_Unicode*)e.Message;
        DBG_ERROR(ByteString(sMessage, gsl_getSystemTextEncoding()).GetBuffer());
#else
        e;	// make compiler happy
#endif
    }

    return aReturn;

}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::Execute(sal_uInt16 nId)
{
    switch (nId)
    {
        case ID_BROWSER_EXPLORER:
            toggleExplorer();
            break;

        case ID_BROWSER_EDITDOC:
            SbaXDataBrowserController::Execute(nId);
            break;

        case ID_BROWSER_DOCUMENT_DATASOURCE:
            implSelect(m_aDocumentDataSource);
            break;

        case ID_BROWSER_INSERTCOLUMNS:
        case ID_BROWSER_INSERTCONTENT:
        case ID_BROWSER_FORMLETTER:
            if (getBrowserView() && isValidCursor())
            {
                // the URL the slot id is assigned to
                URL aParentUrl = getURLForId(nId);

                // let the dispatcher execute the slot
                Reference< XDispatch > xDispatch(m_aDispatchers[nId]);
                if (xDispatch.is())
                {
                    // set the properties for the dispatch

                    // first fill the selection
                    SbaGridControl* pGrid = getBrowserView()->getVclControl();
                    MultiSelection* pSelection = (MultiSelection*)pGrid->GetSelection();
                    Sequence< Any > aSelection;
                    if (pSelection != NULL)
                    {
                        aSelection.realloc(pSelection->GetSelectCount());
                        long nIdx = pSelection->FirstSelected();
                        Any* pSelectionNos = aSelection.getArray();
                        while (nIdx >= 0)
                        {
                            *pSelectionNos++ <<= (sal_Int32)(nIdx + 1);
                            nIdx = pSelection->NextSelected();
                        }
                    }

                    Reference< XResultSet > xCursorClone;
                    try
                    {
                        Reference< XResultSetAccess > xResultSetAccess(getRowSet(),UNO_QUERY);
                        if (xResultSetAccess.is())
                            xCursorClone = xResultSetAccess->createResultSet();
                    }
                    catch(DisposedException&)
                    {
                        OSL_ENSURE(0,"Object already disposed!");
                    }
                    catch(Exception&)
                    {
                        DBG_ERROR("SbaTableQueryBrowser::Execute(ID_BROWSER_?): could not clone the cursor!");
                    }

                    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);

                    try
                    {
                        ODataAccessDescriptor aDescriptor;
                        aDescriptor[daDataSource]	=	xProp->getPropertyValue(PROPERTY_DATASOURCENAME);
                        aDescriptor[daCommand]		=	xProp->getPropertyValue(PROPERTY_COMMAND);
                        aDescriptor[daCommandType]	=	xProp->getPropertyValue(PROPERTY_COMMANDTYPE);
                        aDescriptor[daConnection]	=	xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION);
                        aDescriptor[daCursor]		<<=	xCursorClone;
                        aDescriptor[daSelection]	<<=	aSelection;

                        xDispatch->dispatch(aParentUrl, aDescriptor.createPropertyValueSequence());
                    }
                    catch(Exception&)
                    {
                        DBG_ERROR("SbaTableQueryBrowser::Execute(ID_BROWSER_?): could not dispatch the slot (caught an exception)!");
                    }
                }
            }
            break;

        case ID_BROWSER_CLOSE:
            {
                Reference<XComponent> xComp(m_xCurrentFrame,UNO_QUERY);
                ::comphelper::disposeComponent(xComp);
            }
            break;
        
        case ID_BROWSER_PASTE:
            if(m_pTreeView->HasChildPathFocus())
            {
#if SUPD<631
                TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard());
#else
                TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(getView()));
#endif
                SvLBoxEntry* pEntry = m_pTreeView->getListBox()->GetCurEntry();
                EntryType eType = getEntryType(pEntry);
                switch(eType)
                {
                    case etQuery:
                    case etQueryContainer:
                        implPasteQuery(pEntry, aTransferData);
                        break;
                    
                    case etView:
                    case etTable:
                    case etTableContainer:
                        implPasteTable( pEntry, aTransferData );
                    default:
                        ;
                }
                break;
            }// else run through
        case ID_BROWSER_COPY:
            if(m_pTreeView->HasChildPathFocus())
            {
                SvLBoxEntry* pEntry = m_pTreeView->getListBox()->GetCurEntry();
                TransferableHelper* pTransfer = NULL;
                Reference< XTransferable> aEnsureDelete;
                EntryType eType = getEntryType(pEntry);
                pTransfer		= implCopyObject( pEntry, eType == etQuery ? CommandType::QUERY : CommandType::TABLE);
                aEnsureDelete	= pTransfer;
                if (pTransfer)
#if SUPD<631
                    pTransfer->CopyToClipboard();
#else
                    pTransfer->CopyToClipboard(getView());
#endif
            }
            else if (getBrowserView() && getBrowserView()->getVclControl() && !getBrowserView()->getVclControl()->IsEditing())
            {
                SbaGridControl* pControl = getBrowserView()->getVclControl();
                pControl->copyCellText(pControl->GetCurRow(), pControl->GetCurColumnId());
            }
            else
                SbaXDataBrowserController::Execute(nId);
            break;

        case ID_BROWSER_CUT:// cut isn't allowed for the treeview
        default:
            SbaXDataBrowserController::Execute(nId);
            break;
    }
}
// -------------------------------------------------------------------------
void SbaTableQueryBrowser::implAddDatasource(const String& _rDbName, Image& _rDbImage,
        String& _rQueryName, Image& _rQueryImage, String& _rTableName, Image& _rTableImage,
        String& _rBookmarkName, Image& _rBookmarkImage)
{
    // initialize the names/images if necessary
    if (!_rQueryName.Len())
        _rQueryName = String(ModuleRes(RID_STR_QUERIES_CONTAINER));
    if (!_rTableName.Len())
        _rTableName = String(ModuleRes(RID_STR_TABLES_CONTAINER));
    if (!_rBookmarkName.Len())
        _rBookmarkName = String(ModuleRes(RID_STR_BOOKMARKS_CONTAINER));

    if (!_rQueryImage)
        _rQueryImage = Image(ModuleRes(QUERYFOLDER_TREE_ICON));
    if (!_rTableImage)
        _rTableImage = Image(ModuleRes(TABLEFOLDER_TREE_ICON));
    if (!_rBookmarkImage)
        _rBookmarkImage = Image(ModuleRes(BOOKMARKFOLDER_TREE_ICON));

    if (!_rDbImage)
        _rDbImage = Image(ModuleRes(IMG_DATABASE));

    // add the entry for the data source
    SvLBoxEntry* pDatasourceEntry = m_pTreeView->getListBox()->InsertEntry(_rDbName, _rDbImage, _rDbImage, NULL, sal_False);
    DBTreeListModel::DBTreeListUserData* pDSData = new DBTreeListModel::DBTreeListUserData;
    pDSData->eType = etDatasource;
    pDatasourceEntry->SetUserData(pDSData);

    // the child for the queries container
    {
        SvLBoxEntry* pQueries = m_pTreeView->getListBox()->InsertEntry(_rQueryName, _rQueryImage, _rQueryImage, pDatasourceEntry, sal_True);
        DBTreeListModel::DBTreeListUserData* pQueriesData = new DBTreeListModel::DBTreeListUserData;
        pQueriesData->eType = etQueryContainer;
        pQueries->SetUserData(pQueriesData);
    }

    // the child for the tables container
    {
        SvLBoxEntry* pTables = m_pTreeView->getListBox()->InsertEntry(_rTableName, _rTableImage, _rTableImage, pDatasourceEntry, sal_True);
        DBTreeListModel::DBTreeListUserData* pTablesData = new DBTreeListModel::DBTreeListUserData;
        pTablesData->eType = etTableContainer;
        pTables->SetUserData(pTablesData);
    }

    // the child for the boomarks container
    {
        SvLBoxEntry* pBookmarks = m_pTreeView->getListBox()->InsertEntry(_rBookmarkName, _rBookmarkImage, _rBookmarkImage, pDatasourceEntry, sal_True);
        DBTreeListModel::DBTreeListUserData* pBookmarksData = new DBTreeListModel::DBTreeListUserData;
        pBookmarksData->eType = etBookmarkContainer;
        pBookmarks->SetUserData(pBookmarksData);
    }
}
// -------------------------------------------------------------------------
void SbaTableQueryBrowser::initializeTreeModel()
{
    if (m_xDatabaseContext.is())
    {
        Image aDBImage, aQueriesImage, aTablesImage, aBookmarksImage;
        String sQueriesName, sTablesName, aBookmarksName;

        // fill the model with the names of the registered datasources
        Sequence< ::rtl::OUString > aDatasources = m_xDatabaseContext->getElementNames();
        const ::rtl::OUString* pBegin	= aDatasources.getConstArray();
        const ::rtl::OUString* pEnd		= pBegin + aDatasources.getLength();
        for (; pBegin != pEnd; ++pBegin)
            implAddDatasource(*pBegin, aDBImage, sQueriesName, aQueriesImage, sTablesName, aTablesImage, aBookmarksName, aBookmarksImage);
    }
}
// -------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::populateTree(const Reference<XNameAccess>& _xNameAccess, 
                                            SvLBoxEntry* _pParent, 
                                            const EntryType& _rEntryType)
{
    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pParent->GetUserData());
    if(pData) // don't ask if the nameaccess is already set see OnExpandEntry views and tables
        pData->xObject = _xNameAccess;

    ModuleRes aResId(DBTreeListModel::getImageResId(_rEntryType));
    Image aImage(aResId);
    
    try
    {
        Sequence< ::rtl::OUString > aNames = _xNameAccess->getElementNames();
        const ::rtl::OUString* pBegin	= aNames.getConstArray();
        const ::rtl::OUString* pEnd		= pBegin + aNames.getLength();
        for (; pBegin != pEnd; ++pBegin)
        {
            if(!m_pTreeView->getListBox()->GetEntryPosByName(*pBegin,_pParent))
            {
                DBTreeListModel::DBTreeListUserData* pEntryData = new DBTreeListModel::DBTreeListUserData;
                pEntryData->eType = _rEntryType;
                m_pTreeView->getListBox()->InsertEntry(*pBegin, aImage, aImage, _pParent, sal_False,LIST_APPEND,pEntryData);
            }
        }
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::populateTree: could not fill the tree");
        return sal_False;
    }
    return sal_True;
}
//------------------------------------------------------------------------------
IMPL_LINK(SbaTableQueryBrowser, OnExpandEntry, SvLBoxEntry*, _pParent)
{
    if (_pParent->HasChilds())
        // nothing to to ...
        return 1L;

    ::osl::MutexGuard aGuard(m_aEntryMutex);

    SvLBoxEntry* pFirstParent = m_pTreeView->getListBox()->GetRootLevelParent(_pParent);
    OSL_ENSURE(pFirstParent,"SbaTableQueryBrowser::OnExpandEntry: No rootlevelparent!");

    DBTreeListModel::DBTreeListUserData* pData = static_cast< DBTreeListModel::DBTreeListUserData* >(_pParent->GetUserData());
    OSL_ENSURE(pData,"SbaTableQueryBrowser::OnExpandEntry: No user data!");
    SvLBoxString* pString = static_cast<SvLBoxString*>(pFirstParent->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING));
    OSL_ENSURE(pString,"SbaTableQueryBrowser::OnExpandEntry: No string item!");

    if (etTableContainer == pData->eType)
    {
        // it could be that we already have a connection
        DBTreeListModel::DBTreeListUserData* pFirstData = static_cast<DBTreeListModel::DBTreeListUserData*>(pFirstParent->GetUserData());
        Reference<XConnection> xConnection(pFirstData->xObject,UNO_QUERY);
        WaitObject aWaitCursor(getBrowserView());
        if(!pFirstData->xObject.is())
        {
            // show the "connecting to ..." status
            String sConnecting(ModuleRes(STR_CONNECTING_DATASOURCE));
            sConnecting.SearchAndReplaceAscii("$name$", pString->GetText());
            BrowserViewStatusDisplay aShowStatus(static_cast<UnoDataBrowserView*>(getView()), sConnecting);

            // connect
            xConnection = connect(pString->GetText(), sal_True);
            pFirstData->xObject = xConnection;
        }
        if(xConnection.is())
        {
            Reference< XWarningsSupplier > xWarnings(xConnection, UNO_QUERY);
            if (xWarnings.is())
                xWarnings->clearWarnings();

            // first insert the views because the tables can also include
            // views but that time the bitmap is the wrong one
            // the nameaccess will be overwriten in populateTree
            Reference<XViewsSupplier> xViewSup(xConnection,UNO_QUERY);
            if(xViewSup.is())
                populateTree(xViewSup->getViews(),_pParent,etView);

            Reference<XTablesSupplier> xTabSup(xConnection,UNO_QUERY);
            if(xTabSup.is())
            {
                populateTree(xTabSup->getTables(),_pParent,etTable);
                Reference<XContainer> xCont(xTabSup->getTables(),UNO_QUERY);
                if(xCont.is())
                    // add as listener to know when elements are inserted or removed
                    xCont->addContainerListener(this);
            }

            if (xWarnings.is())
            {
                SQLExceptionInfo aInfo(xWarnings->getWarnings());
                if (aInfo.isValid() && sal_False)
                {
                    SQLContext aContext;
                    aContext.Message = String(ModuleRes(STR_OPENTABLES_WARNINGS));
                    aContext.Details = String(ModuleRes(STR_OPENTABLES_WARNINGS_DETAILS));
                    aContext.NextException = aInfo.get();
                    aInfo = aContext;
                    showError(aInfo);
                }
                // TODO: we need a better concept for these warnings:
                // something like "don't show any warnings for this datasource, again" would be nice
                // But this requires an extension of the InteractionHandler and an additional property on the data source
            }
        }
        else
            return 0L;
                // 0 indicates that an error occured
    }
    else
    {	// we have to expand the queries or bookmarks
        if (ensureEntryObject(_pParent))
        {
            Reference< XNameAccess > xCollection(static_cast< DBTreeListModel::DBTreeListUserData* >(_pParent->GetUserData())->xObject, UNO_QUERY);
            populateTree(xCollection, _pParent, etQuery == getChildType(_pParent) ? etQuery : etBookmark);
        }
    }
    return 1L;
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::ensureEntryObject( SvLBoxEntry* _pEntry )
{
    DBG_ASSERT(_pEntry, "SbaTableQueryBrowser::ensureEntryObject: invalid argument!");
    if (!_pEntry)
        return sal_False;

    EntryType eType = getEntryType( _pEntry );

    // the user data of the entry
    DBTreeListModel::DBTreeListUserData* pEntryData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pEntry->GetUserData());
    OSL_ENSURE(pEntryData,"ensureEntryObject: user data should already be set!");

    if (pEntryData->xObject.is())
        // nothing to do
        return sal_True;

    SvLBoxEntry* pDataSourceEntry = m_pTreeView->getListBox()->GetRootLevelParent(_pEntry);
    switch (eType)
    {
        case etQueryContainer:
        {
            try
            {
                Reference< XQueryDefinitionsSupplier > xQuerySup;
                m_xDatabaseContext->getByName( GetEntryText( pDataSourceEntry ) ) >>= xQuerySup;
                if (xQuerySup.is())
                {
                    Reference< XNameAccess > xQueryDefs = xQuerySup->getQueryDefinitions();
                    Reference< XContainer > xCont(xQueryDefs, UNO_QUERY);
                    if (xCont.is())
                        // add as listener to get notified if elements are inserted or removed
                        xCont->addContainerListener(this);

                    pEntryData->xObject = xQueryDefs;
                }
                else
                    DBG_ERROR("SbaTableQueryBrowser::ensureEntryObject: no XQueryDefinitionsSupplier interface!");
            }
            catch(Exception&)
            {
                DBG_ERROR("SbaTableQueryBrowser::ensureEntryObject: caught an exception while retrieving the queries container!");
            }
        }
        break;

        case etBookmarkContainer:
        {
            try
            {
                Reference< XBookmarksSupplier > xBookmarksSupp;
                m_xDatabaseContext->getByName( GetEntryText( pDataSourceEntry ) ) >>= xBookmarksSupp;
                if (xBookmarksSupp.is())
                {
                    Reference< XNameAccess > xBookmarks = xBookmarksSupp->getBookmarks();
                    Reference< XContainer > xCont(xBookmarks, UNO_QUERY);
                    if (xCont.is())
                        // add as listener to get notified if elements are inserted or removed
                        xCont->addContainerListener(this);

                    pEntryData->xObject = xBookmarks;
                }
                else
                    DBG_ERROR("SbaTableQueryBrowser::ensureEntryObject: no XBookmarksSupplier interface!");
            }
            catch(Exception&)
            {
                DBG_ERROR("SbaTableQueryBrowser::ensureEntryObject: caught an exception while retrieving the bookmarks container!");
            }
        }
        break;

        default:
            DBG_ERROR("SbaTableQueryBrowser::ensureEntryObject: ooops ... missing some implementation here!");
            // TODO ...
            break;
    }

    return pEntryData->xObject.is();
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::isSelected(SvLBoxEntry* _pEntry) const
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING) : NULL;
    if (pTextItem)
        return static_cast<OBoldListboxString*>(pTextItem)->isEmphasized();
    else
        DBG_ERROR("SbaTableQueryBrowser::isSelected: invalid entry!");
    return sal_False;
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::select(SvLBoxEntry* _pEntry, sal_Bool _bSelect)
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING) : NULL;
    if (pTextItem)
    {
        static_cast<OBoldListboxString*>(pTextItem)->emphasize(_bSelect);
        m_pTreeModel->InvalidateEntry(_pEntry);
    }
    else
        DBG_ERROR("SbaTableQueryBrowser::select: invalid entry!");
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::selectPath(SvLBoxEntry* _pEntry, sal_Bool _bSelect)
{
    while (_pEntry)
    {
        select(_pEntry, _bSelect);
        _pEntry = m_pTreeModel->GetParent(_pEntry);
    }
}

//------------------------------------------------------------------------------
IMPL_LINK(SbaTableQueryBrowser, OnEntryDoubleClicked, SvLBoxEntry*, _pEntry)
{
    SvLBoxEntry* pSelected = m_pTreeView->getListBox()->FirstSelected();
    if (!pSelected)
    {
        DBG_ERROR("SbaTableQueryBrowser::OnEntryDoubleClicked: invalid selection!");
        return 0L;
    }

    if (etBookmark != getEntryType(pSelected))
        return 0L;

    // a bookmarks has been double-clicked
    SvLBoxEntry* pContainer = m_pTreeView->getListBox()->GetParent(pSelected);
    if (!ensureEntryObject(pContainer))
        return 0L;

    DBTreeListModel::DBTreeListUserData* pContainerData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());
    Reference< XNameAccess > xBookmarks(pContainerData->xObject, UNO_QUERY);

    OLinkedDocumentsAccess aHelper(getView(), getORB(), xBookmarks);
    aHelper.open(GetEntryText(pSelected), sal_True);

    return 1L;
};

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::implSelect(const ::svx::ODataAccessDescriptor& _rDescriptor)
{
    // extract the props
    ::rtl::OUString sDataSource;
    ::rtl::OUString sCommand;
    sal_Int32 nCommandType = CommandType::COMMAND;
    sal_Bool bEscapeProcessing = sal_True;
    extractDescriptorProps(_rDescriptor, sDataSource, sCommand, nCommandType, bEscapeProcessing);

    // select it
    return implSelect(sDataSource, sCommand, nCommandType, bEscapeProcessing);
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::implSelect(const ::rtl::OUString& _rDataSourceName, const ::rtl::OUString& _rCommand,
                                      const sal_Int32 _nCommandType, const sal_Bool _bEscapeProcessing,
                                      const Reference<XConnection>& _rxConnection)
{
    if (_rDataSourceName.getLength() && _rCommand.getLength() && (-1 != _nCommandType))
    {
        setTitle(_rDataSourceName,_rCommand);
        SvLBoxEntry* pDataSource = NULL;
        SvLBoxEntry* pCommandType = NULL;
        SvLBoxEntry* pCommand = getObjectEntry(_rDataSourceName, _rCommand, _nCommandType, &pDataSource, &pCommandType, sal_True);

        if (pDataSource)
        {
            if (pCommand)
               m_pTreeView->getListBox()->Select(pCommand);
            else if (!pCommandType)
            {	// we have a command and need to display this in the rowset
                Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
                if(xProp.is())
                {
                    Reference< ::com::sun::star::form::XLoadable >  xLoadable(xProp,UNO_QUERY);
                    try
                    {
                        // the values allowing the RowSet to re-execute
                        xProp->setPropertyValue(PROPERTY_DATASOURCENAME, makeAny(_rDataSourceName));
                        if(_rxConnection.is())
                            xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,makeAny(_rxConnection));

                            // set this _before_ setting the connection, else the rowset would rebuild it ...
                        xProp->setPropertyValue(PROPERTY_COMMANDTYPE, makeAny(_nCommandType));
                        xProp->setPropertyValue(PROPERTY_COMMAND, makeAny(_rCommand));
                        xProp->setPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING, ::cppu::bool2any(_bEscapeProcessing));

                        // the formatter depends on the data source we're working on, so rebuild it here ...
                        initFormatter();

                        // switch the grid to design mode while loading
                        getBrowserView()->getGridControl()->setDesignMode(sal_True);
                        InitializeForm(getRowSet());

                        {
                            FormErrorHelper aHelper(this);
                            // load the row set
                            if (xLoadable->isLoaded())
                                // reload does not work if not already loaded
                                xLoadable->reload();
                            else
                                xLoadable->load();
                            // initialize the model
                            InitializeGridModel(getFormComponent());
                        }

                        FormLoaded(sal_True);
                        return sal_True;
                    }
                    catch(SQLException& e)
                    {
                        showError(SQLExceptionInfo(e));
                    }
                    catch(Exception&)
                    {
                        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::implSelect: something strange happended!");
                    }
                }
            }
        }
    }
    return sal_False;
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::openHelpAgent(sal_Int32 _nHelpId)
{
    try
    {
        URL aURL;
        aURL.Complete = ::rtl::OUString::createFromAscii("vnd.sun.star.help://database.hlp/");
        aURL.Complete += ::rtl::OUString::valueOf(_nHelpId);
        if (m_xUrlTransformer.is())
            m_xUrlTransformer->parseStrict(aURL);

        Reference< XDispatchProvider > xDispProv(m_xCurrentFrame, UNO_QUERY);
        Reference< XDispatch > xHelpDispatch;
        if (xDispProv.is())
            xHelpDispatch = xDispProv->queryDispatch(aURL, ::rtl::OUString::createFromAscii("_helpagent"), FrameSearchFlag::PARENT | FrameSearchFlag::SELF);
        OSL_ENSURE(xHelpDispatch.is(), "SbaTableQueryBrowser::openHelpAgent: could not get a dispatcher!");
        if (xHelpDispatch.is())
        {
            xHelpDispatch->dispatch(aURL, Sequence< PropertyValue >());
        }
    }
    catch(const Exception&)
    {
        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::openHelpAgent: caught an exception while executing the dispatch!");
    }
}

//------------------------------------------------------------------------------
IMPL_LINK(SbaTableQueryBrowser, OnSelectEntry, SvLBoxEntry*, _pEntry)
{
    ::osl::MutexGuard aGuard(m_aEntryMutex);

    DBTreeListModel::DBTreeListUserData* pEntryData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pEntry->GetUserData());
    switch (pEntryData->eType)
    {
        case etTable:
        case etQuery:
        case etView:
            break;
        case etBookmark:
            openHelpAgent(HID_DSBROWSER_BOOKMARKSELECTED);
            return 0L;
        default:
            // nothing to do
            return 0L;
    }

    OSL_ENSURE(m_pTreeModel->HasParent(_pEntry), "SbaTableQueryBrowser::OnSelectEntry: invalid entry (1)!");
    OSL_ENSURE(m_pTreeModel->HasParent(m_pTreeModel->GetParent(_pEntry)), "SbaTableQueryBrowser::OnSelectEntry: invalid entry (2)!");
    
    // get the entry for the tables or queries
    SvLBoxEntry* pContainer = m_pTreeModel->GetParent(_pEntry);
    DBTreeListModel::DBTreeListUserData* pContainerData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());

    // get the entry for the datasource
    SvLBoxEntry* pConnection = m_pTreeModel->GetParent(pContainer);
    DBTreeListModel::DBTreeListUserData* pConData = static_cast<DBTreeListModel::DBTreeListUserData*>(pConnection->GetUserData());

    // reinitialize the rowset
    // but first check if it is necessary
    // get all old properties
    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
    ::rtl::OUString aOldName;
    xProp->getPropertyValue(PROPERTY_COMMAND) >>= aOldName;
    sal_Int32 nOldType;
    xProp->getPropertyValue(PROPERTY_COMMANDTYPE) >>= nOldType;
    Reference<XConnection> xOldConnection;
    ::cppu::extractInterface(xOldConnection,xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION));
    // the name of the table or query
    SvLBoxString* pString = (SvLBoxString*)_pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING);
    OSL_ENSURE(pString,"There must be a string item!");
    ::rtl::OUString aName(pString->GetText().GetBuffer());

    Reference<XConnection> xConnection(pConData->xObject,UNO_QUERY);
    sal_Int32 nCommandType =	( etTableContainer == pContainerData->eType)
                            ?	CommandType::TABLE
                            :	CommandType::QUERY;

    // check if need to rebuild the rowset
    sal_Bool bRebuild = xOldConnection != xConnection || nOldType != nCommandType || aName != aOldName;

    Reference< ::com::sun::star::form::XLoadable >  xLoadable(getRowSet(),UNO_QUERY);
    bRebuild |= !xLoadable->isLoaded();
    if(bRebuild)
    {
        try
        {
            // if table was selected before flush it
            if(m_pCurrentlyDisplayed)
            {
                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
                if(pData) // can be null because the first load can be failed @see below
                {
                    Reference<XFlushable> xFlush(pData->xObject,UNO_QUERY);
                    if(xFlush.is())
                        xFlush->flush();
                }
            }
        }
        catch(Exception&)
        {
            OSL_ENSURE(0,"Object can not be flushed!");
        }
        try
        {
            WaitObject aWaitCursor(getBrowserView());

            // tell the old entry it has been deselected
            selectPath(m_pCurrentlyDisplayed, sal_False);
            m_pCurrentlyDisplayed = _pEntry;
            // tell the new entry it has been selected
            selectPath(m_pCurrentlyDisplayed, sal_True);

            // get the name of the data source currently selected
            ::rtl::OUString sDataSourceName;
            SvLBoxEntry* pEntry = m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyDisplayed);

            if (pEntry)
            {
                SvLBoxItem* pTextItem = pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING);
                if (pTextItem)
                    sDataSourceName = static_cast<SvLBoxString*>(pTextItem)->GetText();
            }
            if(!xConnection.is())
            {
                xConnection = connect(sDataSourceName, sal_True);
                pConData->xObject = xConnection;
            }
            if(!xConnection.is())
            {
                unloadForm(sal_False,sal_False);
                return 0L;
            }

            Reference<XNameAccess> xNameAccess;
            switch(nCommandType)
            {
                case CommandType::TABLE:
                    {
                        // only for tables
                        if(!pContainerData->xObject.is())
                        {
                            Reference<XTablesSupplier> xSup(xConnection,UNO_QUERY);
                            if(xSup.is())
                                xNameAccess = xSup->getTables();

                            pContainerData->xObject = xNameAccess;
                        }
                        else
                            xNameAccess = Reference<XNameAccess>(pContainerData->xObject,UNO_QUERY);
                    }
                    break;
                case CommandType::QUERY:
                    {
                        Reference<XQueriesSupplier> xSup(xConnection,UNO_QUERY);
                        if(xSup.is())
                            xNameAccess = xSup->getQueries();
                    }
                    break;
            }
            if(xNameAccess.is() && xNameAccess->hasByName(aName))
            {
                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
                if(!pData->xObject.is())
                {
                    Reference<XInterface> xObject;
                    if(xNameAccess->getByName(aName) >>= xObject) // remember the table or query object
                        pData->xObject = xObject;
                }
            }
            // the values allowing the RowSet to re-execute
            xProp->setPropertyValue(PROPERTY_DATASOURCENAME,makeAny(sDataSourceName));
                // set this _before_ setting the connection, else the rowset would rebuild it ...
            xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,makeAny(xConnection));
            xProp->setPropertyValue(PROPERTY_COMMANDTYPE,makeAny(nCommandType));
            xProp->setPropertyValue(PROPERTY_COMMAND,makeAny(aName));
            // the formatter depends on the data source we're working on, so rebuild it here ...
            initFormatter();

            String sStatus(ModuleRes( CommandType::TABLE == nCommandType ? STR_LOADING_TABLE : STR_LOADING_QUERY ));
            sStatus.SearchAndReplaceAscii("$name$", aName);
            BrowserViewStatusDisplay aShowStatus(static_cast<UnoDataBrowserView*>(getView()), sStatus);

            // switch the grid to design mode while loading
            getBrowserView()->getGridControl()->setDesignMode(sal_True);
            InitializeForm(getRowSet());

            // load the row set
            {
                FormErrorHelper aNoticeErrors(this);

                if (xLoadable->isLoaded())
                    // reload does not work if not already loaded
                    xLoadable->reload();
                else
                    xLoadable->load();

                // initialize the model
                InitializeGridModel(getFormComponent());

                FormLoaded(sal_True);
            }
            // set the title of the beamer
            
            setTitle(sDataSourceName,aName);
        }
        catch(SQLException& e)
        {
            showError(SQLExceptionInfo(e));
            // reset the values
            xProp->setPropertyValue(PROPERTY_DATASOURCENAME,Any());
            xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,Any());
        }
        catch(Exception&)
        {
            // reset the values
            xProp->setPropertyValue(PROPERTY_DATASOURCENAME,Any());
            xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,Any());
        }
        catch(...)
        {
            OSL_ENSURE(0,"Unkown Exception in SbaTableQueryBrowser::OnSelectEntry!");
        }
    }
    return 0L;
}

// -----------------------------------------------------------------------------
SvLBoxEntry* SbaTableQueryBrowser::getEntryFromContainer(const Reference<XNameAccess>& _rxNameAccess)
{
    SvLBoxEntry* pDSLoop = m_pTreeView->getListBox()->FirstChild(NULL);
    SvLBoxEntry* pContainer = NULL;
    while (pDSLoop)
    {
        pContainer	= m_pTreeView->getListBox()->GetEntry(pDSLoop, CONTAINER_QUERIES);
        DBTreeListModel::DBTreeListUserData* pQueriesData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());
        if(pQueriesData && pQueriesData->xObject.get() == _rxNameAccess.get())
            break;

        pContainer	= m_pTreeView->getListBox()->GetEntry(pDSLoop, CONTAINER_TABLES);
        DBTreeListModel::DBTreeListUserData* pTablesData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());
        if(pTablesData && pTablesData->xObject.get() == _rxNameAccess.get())
            break;

        pContainer	= m_pTreeView->getListBox()->GetEntry(pDSLoop, CONTAINER_BOOKMARKS);
        DBTreeListModel::DBTreeListUserData* pBookmarksData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());
        if(pBookmarksData && pBookmarksData->xObject.get() == _rxNameAccess.get())
            break;

        pDSLoop		= m_pTreeView->getListBox()->NextSibling(pDSLoop);
        pContainer	= NULL;
    }
    return pContainer;
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementInserted( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aEntryMutex);

    Reference< XNameAccess > xNames(_rEvent.Source, UNO_QUERY);
    // first search for a definition container where we can insert this element

    SvLBoxEntry* pEntry = getEntryFromContainer(xNames);
    if(pEntry)	// found one
    {
        // insert the new entry into the tree
        DBTreeListModel::DBTreeListUserData* pContainerData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntry->GetUserData());
        OSL_ENSURE(pContainerData, "elementInserted: There must be user data for this type!");

        sal_Bool bIsTable = etTableContainer == pContainerData->eType;
        if (bIsTable)
        {
            // only insert userdata when we have a table because the query is only a commanddefinition object and not a query
            DBTreeListModel::DBTreeListUserData* pNewData = new DBTreeListModel::DBTreeListUserData;
            
            _rEvent.Element >>= pNewData->xObject;// remember the new element
            // now we have to check which type we have here
            Reference<XPropertySet> xProp(pNewData->xObject,UNO_QUERY);
            ::rtl::OUString sType;
            if(xProp->getPropertySetInfo()->hasPropertyByName(PROPERTY_TYPE))
                xProp->getPropertyValue(PROPERTY_TYPE) >>= sType;
            if(sType.getLength() && sType == ::rtl::OUString::createFromAscii("VIEW"))
                pNewData->eType = etView;
            else
                pNewData->eType = etTable;

            sal_uInt16 nImageResId = DBTreeListModel::getImageResId(pNewData->eType);
            Image aImage = Image(ModuleRes(nImageResId));
            m_pTreeView->getListBox()->InsertEntry(::comphelper::getString(_rEvent.Accessor),
                                                                            aImage, 
                                                                            aImage, 
                                                                            pEntry, 
                                                                            sal_False,
                                                                            LIST_APPEND,
                                                                            pNewData);
        }
        else
        {
            if ((sal_Int32)m_pTreeView->getListBox()->GetChildCount(pEntry) < ( xNames->getElementNames().getLength() - 1 ) )
            {
                // the item inserts its children on demand, but it has not been expanded yet. So ensure here and
                // now that it has all items
                populateTree(xNames, pEntry, pContainerData->eType == etQueryContainer ? etQuery : etBookmark);
            }
            else
            {
                DBTreeListModel::DBTreeListUserData* pNewData = new DBTreeListModel::DBTreeListUserData;
                //	_rEvent.Element >>= pNewData->xObject;// remember the new element
                pNewData->eType = pContainerData->eType == etQueryContainer ? etQuery : etBookmark;

                sal_uInt16 nImageResId = DBTreeListModel::getImageResId(pNewData->eType);
                Image aImage = Image(ModuleRes(nImageResId));
                m_pTreeView->getListBox()->InsertEntry(::comphelper::getString(_rEvent.Accessor),
                                                                                aImage, 
                                                                                aImage, 
                                                                                pEntry, 
                                                                                sal_False,
                                                                                LIST_APPEND,
                                                                                pNewData);
            }
        }
    }
    else if (xNames.get() == m_xDatabaseContext.get())
    {	// a new datasource has been added to the context
        // the name of the new ds
        ::rtl::OUString sNewDS;
        _rEvent.Accessor >>= sNewDS;

        // add new entries to the list box model
        Image a, b, c, d;	// not interested in  reusing them
        String e, f, g;
        implAddDatasource(sNewDS, a, e, b, f, c, g, d);
    }
    else
        SbaXDataBrowserController::elementInserted(_rEvent);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementRemoved( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aEntryMutex);

    Reference< XNameAccess > xNames(_rEvent.Source, UNO_QUERY);
    // get the top-level representing the removed data source
    // and search for the queries and tables
    SvLBoxEntry* pContainer = getEntryFromContainer(xNames);
    if (pContainer)
    { // a query or table has been removed
        String aName = ::comphelper::getString(_rEvent.Accessor).getStr();

        if	(	m_pCurrentlyDisplayed
            &&	getEntryType(m_pCurrentlyDisplayed) == getChildType(pContainer)
            &&	m_pTreeView->getListBox()->GetEntryText(m_pCurrentlyDisplayed) == aName
            )
        {	// the element displayed currently has been replaced

            // we need to remember the old value
            SvLBoxEntry* pTemp = m_pCurrentlyDisplayed;

            // unload
            unloadForm(sal_False, sal_False); // don't dispose the connection, don't flush

            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pTemp->GetUserData());
            pTemp->SetUserData(NULL);
            delete pData;
                // the data could be null because we have a table which isn't correct
            m_pTreeModel->Remove(pTemp);
        }
        else
        {
            // remove the entry from the model
            SvLBoxEntry* pChild = m_pTreeModel->FirstChild(pContainer);
            while(pChild)
            {
                if (m_pTreeView->getListBox()->GetEntryText(pChild) == aName)
                {
                    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pChild->GetUserData());
                    pChild->SetUserData(NULL);
                    delete pData;
                    m_pTreeModel->Remove(pChild);
                    break;
                }
                pChild = m_pTreeModel->NextSibling(pChild);
            }
        }

        // maybe the object which is part of the document data source has been removed
        checkDocumentDataSource();
    }
    else if (xNames.get() == m_xDatabaseContext.get())
    {	// a datasource has been removed from the context

        // the name
        ::rtl::OUString sNewDS;
        _rEvent.Accessor >>= sNewDS;
        String sNewDatasource = sNewDS;

        // get the top-level representing the removed data source
        SvLBoxEntry* pDSLoop = m_pTreeView->getListBox()->FirstChild(NULL);
        while (pDSLoop)
        {
            if (m_pTreeView->getListBox()->GetEntryText(pDSLoop) == sNewDatasource)
                break;

            pDSLoop = m_pTreeView->getListBox()->NextSibling(pDSLoop);
        }

        if (pDSLoop)
        {
            if (isSelected(pDSLoop))
            {	// a table or query belonging to the deleted data source is currently beeing displayed.
                OSL_ENSURE(m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyDisplayed) == pDSLoop, "SbaTableQueryBrowser::elementRemoved: inconsistence (1)!");
                unloadForm(sal_True, sal_False); // don't flush
            }
            else
                OSL_ENSURE(
                        (NULL == m_pCurrentlyDisplayed)
                    ||	(m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyDisplayed) != pDSLoop), "SbaTableQueryBrowser::elementRemoved: inconsistence (2)!");

            // look for user data to delete
            SvTreeEntryList* pList = m_pTreeModel->GetChildList(pDSLoop);
            if(pList)
            {
                SvLBoxEntry* pEntryLoop = static_cast<SvLBoxEntry*>(pList->First());
                while (pEntryLoop)
                {
                    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntryLoop->GetUserData());
                    delete pData;
                    pEntryLoop = static_cast<SvLBoxEntry*>(pList->Next());
                }
            }
            // remove the entry. This should remove all children, too.
            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pDSLoop->GetUserData());
            delete pData;
            m_pTreeModel->Remove(pDSLoop);
        }
        else
            DBG_ERROR("SbaTableQueryBrowser::elementRemoved: unknown datasource name!");

        // maybe the object which is part of the document data source has been removed
        checkDocumentDataSource();
    }
    else
        SbaXDataBrowserController::elementRemoved(_rEvent);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementReplaced( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aEntryMutex);

    Reference< XNameAccess > xNames(_rEvent.Source, UNO_QUERY);
    SvLBoxEntry* pContainer = getEntryFromContainer(xNames);
    if (pContainer)
    {	 // a table or query as been replaced
        String aName = ::comphelper::getString(_rEvent.Accessor).getStr();

        if	(	m_pCurrentlyDisplayed
            &&	getEntryType(m_pCurrentlyDisplayed) == getChildType(pContainer)
            &&	m_pTreeView->getListBox()->GetEntryText(m_pCurrentlyDisplayed) == aName
            )
        {	// the element displayed currently has been replaced

            // we need to remember the old value
            SvLBoxEntry* pTemp = m_pCurrentlyDisplayed;
            unloadForm(sal_False); // don't dispose the connection

            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pTemp->GetUserData());
            if (pData)
            {
                if (etTable == pData->eType || etView == pData->eType)
                { // only insert userdata when we have a table because the query is only a commanddefinition object and not a query
                     _rEvent.Element >>= pData->xObject;// remember the new element
                }
                else
                {
                    pTemp->SetUserData(NULL);
                    delete pData;
                }
            }
            else
                OSL_ENSURE(etBookmarkContainer == getEntryType(pContainer), "SbaTableQueryBrowser::elementReplaced: a non-bookmark entry without data?");
        }
        else
        {
            // find the entry for this name
            SvLBoxEntry* pChild = m_pTreeModel->FirstChild(pContainer);
            while(pChild)
            {
                if (m_pTreeView->getListBox()->GetEntryText(pChild) == aName)
                {
                    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pChild->GetUserData());
                    if (pData)
                    {
                        if (etTable == pData->eType || etView == pData->eType)
                        { // only insert userdata when we have a table because the query is only a commanddefinition object and not a query
                            _rEvent.Element >>= pData->xObject;// remember the new element
                        }
                        else
                        {
                            pChild->SetUserData(NULL);
                            delete pData;
                        }
                    }
                    else
                        OSL_ENSURE(etBookmarkContainer == getEntryType(pContainer), "SbaTableQueryBrowser::elementReplaced: a non-bookmark entry without data (2)?");
                    break;
                }
                pChild = m_pTreeModel->NextSibling(pChild);
            }
        }

        // maybe the object which is part of the document data source has been removed
        checkDocumentDataSource();
    }
    else if (xNames.get() == m_xDatabaseContext.get())
    {	// a datasource has been replaced in the context
        DBG_ERROR("SbaTableQueryBrowser::elementReplaced: no support for replaced data sources!");
            // very suspicious: the database context should not allow to replace data source, only to register
            // and revoke them
    }
    else
        SbaXDataBrowserController::elementReplaced(_rEvent);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::closeConnection(SvLBoxEntry* _pDSEntry,sal_Bool _bDisposeConnection)
{
    DBG_ASSERT(_pDSEntry, "SbaTableQueryBrowser::closeConnection: invalid entry (NULL)!");
    OSL_ENSURE(m_pTreeView->getListBox()->GetRootLevelParent(_pDSEntry) == _pDSEntry, "SbaTableQueryBrowser::closeConnection: invalid entry (not top-level)!");

    // if one of the entries of the given DS is displayed currently, unload the form
    if (m_pCurrentlyDisplayed && (m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyDisplayed) == _pDSEntry))
        unloadForm(_bDisposeConnection);

    // collapse the query/table container
    for (SvLBoxEntry* pContainers = m_pTreeModel->FirstChild(_pDSEntry); pContainers; pContainers= m_pTreeModel->NextSibling(pContainers))
    {
        m_pTreeView->getListBox()->Collapse(pContainers);
        m_pTreeView->getListBox()->EnableExpandHandler(pContainers);
        // and delete their children (they are connection-relative)
        for	(SvLBoxEntry* pElements = m_pTreeModel->FirstChild(pContainers); pElements; )
        {
            SvLBoxEntry* pRemove = pElements;
            pElements= m_pTreeModel->NextSibling(pElements);
            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pRemove->GetUserData());
            delete pData;
            m_pTreeModel->Remove(pRemove);
        }
    }
    // collapse the entry itself
    m_pTreeView->getListBox()->Collapse(_pDSEntry);

    // get the connection
    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pDSEntry->GetUserData());
    if(_bDisposeConnection) // and dispose/reset it
    {
        Reference< XComponent >  xComponent(pData->xObject, UNO_QUERY);
        if (xComponent.is())
        {
            Reference< ::com::sun::star::lang::XEventListener> xEvtL((::cppu::OWeakObject*)this,UNO_QUERY);
            xComponent->removeEventListener(xEvtL);
        }
        ::comphelper::disposeComponent(pData->xObject);
    }
    pData->xObject.clear();
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::unloadForm(sal_Bool _bDisposeConnection, sal_Bool _bFlushData)
{
    if (!m_pCurrentlyDisplayed)
        // nothing to do
        return;

    SvLBoxEntry* pDSEntry = m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyDisplayed);

    // de-select the path for the currently displayed table/query
    if (m_pCurrentlyDisplayed)
    {
        if (_bFlushData)
        {
            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(m_pCurrentlyDisplayed->GetUserData());
            try
            {
                if(pData)
                {
                    Reference<XFlushable> xFlush(pData->xObject, UNO_QUERY);
                    if(xFlush.is())
                        xFlush->flush();
                }
            }
            catch (RuntimeException&)
            {
                OSL_ENSURE(sal_False, "SbaTableQueryBrowser::unloadForm: could not flush the data (caught a RuntimeException)!");
            }
        }
        selectPath(m_pCurrentlyDisplayed, sal_False);
    }
    m_pCurrentlyDisplayed = NULL;

    try
    {
        // get the active connection. We need to dispose it.
        Reference< XPropertySet > xProp(getRowSet(),UNO_QUERY);
        Reference< XConnection > xConn;
        ::cppu::extractInterface(xConn, xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION));
#ifdef DEBUG
        {
            Reference< XComponent > xComp;
            ::cppu::extractInterface(xComp, xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION));
        }
#endif

        // unload the form
        Reference< XLoadable > xLoadable(getRowSet(), UNO_QUERY);
        xLoadable->unload();

        // clear the grid control
        Reference< XNameContainer >  xColContainer(getControlModel(), UNO_QUERY);
        // first we have to clear the grid
        {
            Sequence< ::rtl::OUString > aNames = xColContainer->getElementNames();
            const ::rtl::OUString* pBegin	= aNames.getConstArray();
            const ::rtl::OUString* pEnd		= pBegin + aNames.getLength();
            for (; pBegin != pEnd;++pBegin)
                xColContainer->removeByName(*pBegin);
        }

        // dispose the connection
        if(_bDisposeConnection)
        {
            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pDSEntry->GetUserData());
            if(pData)
            {
                Reference< XComponent >  xComponent(pData->xObject, UNO_QUERY);
                if (xComponent.is())
                {
                    Reference< ::com::sun::star::lang::XEventListener> xEvtL((::cppu::OWeakObject*)this,UNO_QUERY);
                    xComponent->removeEventListener(xEvtL);
                }
                pData->xObject = NULL;
            }
            ::comphelper::disposeComponent(xConn);
        }
    }
    catch(SQLException& e)
    {
        showError(SQLExceptionInfo(e));
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::unloadForm: could not reset the form");
    }
}
// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException)
{
    ::vos::OGuard aGuard(Application::GetSolarMutex());
        // doin' a lot of VCL stuff here -> lock the SolarMutex

    // first initialize the parent
    SbaXDataBrowserController::initialize( aArguments );

    Reference<XConnection> xConnection;
    PropertyValue aValue;
    const Any* pBegin	= aArguments.getConstArray();
    const Any* pEnd		= pBegin + aArguments.getLength();

    ::rtl::OUString aTableName,aCatalogName,aSchemaName;

    sal_Bool bEsacpeProcessing = sal_True;
    sal_Int32 nInitialDisplayCommandType;
    ::rtl::OUString sInitialDataSourceName;
    ::rtl::OUString sInitialCommand;

    for(;pBegin != pEnd;++pBegin)
    {
        if (!(*pBegin >>= aValue))
            continue;

        if (0 == aValue.Name.compareToAscii(PROPERTY_DATASOURCENAME))
            aValue.Value >>= sInitialDataSourceName;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_COMMANDTYPE))
            aValue.Value >>= nInitialDisplayCommandType;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_COMMAND))
            aValue.Value >>= sInitialCommand;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_ACTIVECONNECTION))
            ::cppu::extractInterface(xConnection,aValue.Value);
        else if (0 == aValue.Name.compareToAscii(PROPERTY_UPDATE_CATALOGNAME))
            aValue.Value >>= aCatalogName;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_UPDATE_SCHEMANAME))
            aValue.Value >>= aSchemaName;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_UPDATE_TABLENAME))
            aValue.Value >>= aTableName;
        else if (0 == aValue.Name.compareToAscii(PROPERTY_USE_ESCAPE_PROCESSING))
            bEsacpeProcessing = ::cppu::any2bool(aValue.Value);
        else if (0 == aValue.Name.compareToAscii(PROPERTY_SHOWTREEVIEW))
        {
            try
            {
                if(::cppu::any2bool(aValue.Value))
                    showExplorer();
                else
                    hideExplorer();
            }
            catch(Exception&)
            {
            }
        }
        else if (0 == aValue.Name.compareToAscii(PROPERTY_SHOWTREEVIEWBUTTON))
        {
            try
            {
                if (!::cppu::any2bool(aValue.Value) && getView())
                {
                    // hide the explorer and the separator
                    getView()->getToolBox()->HideItem(ID_BROWSER_EXPLORER);
                    getView()->getToolBox()->HideItem(getView()->getToolBox()->GetItemId(getView()->getToolBox()->GetItemPos(ID_BROWSER_EXPLORER)+1));
                    getView()->getToolBox()->ShowItem(ID_BROWSER_CLOSE);
                }
            }
            catch(Exception&)
            {
            }
        }
    }

    if (implSelect(sInitialDataSourceName, sInitialCommand, nInitialDisplayCommandType, bEsacpeProcessing,xConnection))
    {
        try
        {
            Reference< XPropertySet > xProp(getRowSet(), UNO_QUERY);
            xProp->setPropertyValue(PROPERTY_UPDATE_CATALOGNAME,makeAny(aCatalogName));
            xProp->setPropertyValue(PROPERTY_UPDATE_SCHEMANAME,makeAny(aSchemaName));
            xProp->setPropertyValue(PROPERTY_UPDATE_TABLENAME,makeAny(aTableName));
            
        }
        catch(const Exception&)
        {
            OSL_ENSURE(sal_False, "SbaTableQueryBrowser::initialize: could not set the update related names!");
        }
    }
    else
    {
        // set a default title
        ::rtl::OUString sTitle = String(ModuleRes(STR_DSBROWSER_TITLE));
        setTitle(sTitle,::rtl::OUString());
    }
}

// -------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::haveExplorer() const
{
    return m_pTreeView && m_pTreeView->IsVisible();
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::hideExplorer()
{
    if (!haveExplorer())
        return;
    if (!getBrowserView())
        return;

    m_pTreeView->Hide();
    m_pSplitter->Hide();
    getBrowserView()->Resize();

    InvalidateFeature(ID_BROWSER_EXPLORER);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::showExplorer()
{
    if (haveExplorer())
        return;

    if (!getBrowserView())
        return;

    m_pTreeView->Show();
    m_pSplitter->Show();
    getBrowserView()->Resize();

    InvalidateFeature(ID_BROWSER_EXPLORER);
}

// -----------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::ensureConnection(SvLBoxEntry* _pAnyEntry, Reference< XConnection>& _xConnection)
{
    SvLBoxEntry* pDSEntry = m_pTreeView->getListBox()->GetRootLevelParent(_pAnyEntry);
    DBTreeListModel::DBTreeListUserData* pDSData =
                pDSEntry
            ?	static_cast<DBTreeListModel::DBTreeListUserData*>(pDSEntry->GetUserData())
            :	NULL;

    return ensureConnection( pDSEntry, pDSData, _xConnection);
}

// -----------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::ensureConnection(SvLBoxEntry* _pDSEntry, void* pDSData, Reference<XConnection>& _xConnection)
{
    if(_pDSEntry)
    {
        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pDSData);
        ::rtl::OUString aDSName = GetEntryText(_pDSEntry);

        if (pData)
            _xConnection = Reference<XConnection>(pData->xObject,UNO_QUERY);
        if(!_xConnection.is() && pData)
        {
            // show the "connecting to ..." status
            String sConnecting(ModuleRes(STR_CONNECTING_DATASOURCE));
            sConnecting.SearchAndReplaceAscii("$name$", aDSName);
            BrowserViewStatusDisplay aShowStatus(static_cast<UnoDataBrowserView*>(getView()), sConnecting);

            _xConnection = connect(aDSName, sal_True);
            pData->xObject = _xConnection; // share the conenction with the querydesign
        }
    }

    return _xConnection.is();
}

// -----------------------------------------------------------------------------
IMPL_LINK( SbaTableQueryBrowser, OnTreeEntryCompare, const SvSortData*, _pSortData )
{
    SvLBoxEntry* pLHS = static_cast<SvLBoxEntry*>(_pSortData->pLeft);
    SvLBoxEntry* pRHS = static_cast<SvLBoxEntry*>(_pSortData->pRight);
    DBG_ASSERT(pLHS && pRHS, "SbaTableQueryBrowser::OnTreeEntryCompare: invalid tree entries!");
    // we want the table entry and the end so we have to do a check

    if (isContainer(pRHS))
    {
        // don't use getEntryType (directly or indirecly) for the LHS:
        // LHS is currently beeing inserted, so it is not "completely valid" at the moment

        const EntryType eRight = getEntryType(pRHS);
        if (etTableContainer == eRight)
            // every other container should be placed _before_ the bookmark container
            return -1;

        const String sLeft = m_pTreeView->getListBox()->GetEntryText(pLHS);

        EntryType eLeft;
        if (String(ModuleRes(RID_STR_TABLES_CONTAINER)) == sLeft)
            eLeft = etTableContainer;
        else if (String(ModuleRes(RID_STR_QUERIES_CONTAINER)) == sLeft)
            eLeft = etQueryContainer;
        else
            eLeft = etBookmarkContainer;

        return	eLeft < eRight
            ?	COMPARE_LESS
            :		eLeft == eRight
                ?	COMPARE_EQUAL
                :	COMPARE_GREATER;
    }

    SvLBoxString* pLeftTextItem = static_cast<SvLBoxString*>(pLHS->GetFirstItem(SV_ITEM_ID_LBOXSTRING));
    SvLBoxString* pRightTextItem = static_cast<SvLBoxString*>(pRHS->GetFirstItem(SV_ITEM_ID_LBOXSTRING));
    DBG_ASSERT(pLeftTextItem && pRightTextItem, "SbaTableQueryBrowser::OnTreeEntryCompare: invalid text items!");

    String sLeftText = pLeftTextItem->GetText();
    String sRightText = pRightTextItem->GetText();

    sal_Int32 nCompareResult = 0;	// equal by default

    if (m_xCollator.is())
    {
        try
        {
            nCompareResult = m_xCollator->compareString(sLeftText, sRightText);
        }
        catch(Exception&)
        {
        }
    }
    else
        // default behaviour if we do not have a collator -> do the simple string compare
        nCompareResult = sLeftText.CompareTo(sRightText);

    return nCompareResult;
}

// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::implDirectSQL( SvLBoxEntry* _pApplyTo )
{
    try
    {
        Reference<XConnection> xConnection;
        if(!ensureConnection(_pApplyTo, xConnection))
            return;

        DirectSQLDialog aDlg(getView(), xConnection);
        aDlg.Execute();
    }
    catch(const SQLException& e)
    {
        showError(SQLExceptionInfo(e));
    }
    catch(const Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::implDirectSQL: caught an (unknown) exception!");
    }
}

// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::implAdministrate( SvLBoxEntry* _pApplyTo )
{
    try
    {
        // the parameters:
        Sequence< Any > aArgs(2);
        // the parent window
        aArgs[0] <<= PropertyValue(
            ::rtl::OUString::createFromAscii("ParentWindow"), 0,
            makeAny(VCLUnoHelper::GetInterface(m_pTreeView->getListBox()->Window::GetParent())), PropertyState_DIRECT_VALUE);
        // the initial selection
        SvLBoxEntry* pTopLevelSelected = _pApplyTo;
        while (pTopLevelSelected && m_pTreeView->getListBox()->GetParent(pTopLevelSelected))
            pTopLevelSelected = m_pTreeView->getListBox()->GetParent(pTopLevelSelected);
        ::rtl::OUString sInitialSelection;
        if (pTopLevelSelected)
            sInitialSelection = m_pTreeView->getListBox()->GetEntryText(pTopLevelSelected);
        aArgs[1] <<= PropertyValue(
            ::rtl::OUString::createFromAscii("InitialSelection"), 0,
            makeAny(sInitialSelection), PropertyState_DIRECT_VALUE);

        // create the dialog
        Reference< XExecutableDialog > xAdminDialog;
        xAdminDialog = Reference< XExecutableDialog >(
            m_xMultiServiceFacatory->createInstanceWithArguments(::rtl::OUString::createFromAscii("com.sun.star.sdb.DatasourceAdministrationDialog"),
                aArgs), UNO_QUERY);

        // execute it
        if (xAdminDialog.is())
            xAdminDialog->execute();
    }
    catch(::com::sun::star::uno::Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::implAdministrate: caught an exception while creating/executing the dialog!");
    }
}

// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::implCreateObject( SvLBoxEntry* _pApplyTo, sal_uInt16 _nAction )
{
    try
    {
        ::osl::MutexGuard aGuard(m_aEntryMutex);

        // get all needed properties for design
        Reference<XConnection> xConnection;	 // supports the service sdb::connection
        if(!ensureConnection(_pApplyTo, xConnection))
            return;

        ::rtl::OUString sCurrentObject;
        if ((ID_EDIT_QUERY_DESIGN == _nAction || ID_EDIT_TABLE == _nAction) && _pApplyTo)
        {
            // get the name of the query
            SvLBoxItem* pQueryTextItem = _pApplyTo->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING);
            if (pQueryTextItem)
                sCurrentObject = static_cast<SvLBoxString*>(pQueryTextItem)->GetText();

            DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pApplyTo->GetUserData());
            if(!pData->xObject.is())
            {
                // the query has not been accessed before -> create it's user data

                Reference<XNameAccess> xNameAccess;
                if(ID_EDIT_TABLE == _nAction)
                {
                    Reference<XTablesSupplier> xSup(xConnection,UNO_QUERY);
                    if(xSup.is())
                        xNameAccess = xSup->getTables();
                }
                else
                {
                    Reference<XQueriesSupplier> xSup(xConnection,UNO_QUERY);
                    if(xSup.is())
                        xNameAccess = xSup->getQueries();
                }

                SvLBoxItem* pTextItem = _pApplyTo->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING);
                if (pTextItem)
                    sCurrentObject = static_cast<SvLBoxString*>(pTextItem)->GetText();

                if(xNameAccess.is() && xNameAccess->hasByName(sCurrentObject))  // remember the table or query object
                    xNameAccess->getByName(sCurrentObject) >>= pData->xObject;
            }
        }

        ODesignAccess* pDispatcher = NULL;
        sal_Bool bEdit = sal_False;
        switch(_nAction)
        {
            case ID_TREE_RELATION_DESIGN:
                pDispatcher = new ORelationDesignAccess(m_xMultiServiceFacatory);
                break;
            case ID_EDIT_TABLE:
                bEdit = sal_True; // run through
            case ID_NEW_TABLE_DESIGN:
                pDispatcher = new OTableDesignAccess(m_xMultiServiceFacatory) ;
                break;
            case ID_EDIT_QUERY_DESIGN:
                bEdit = sal_True; // run through
            case ID_NEW_QUERY_DESIGN:
            case ID_NEW_QUERY_SQL:
                pDispatcher = new OQueryDesignAccess(m_xMultiServiceFacatory, sal_False, ID_NEW_QUERY_SQL == _nAction);
                break;
            case ID_NEW_VIEW_DESIGN:
                pDispatcher = new OQueryDesignAccess(m_xMultiServiceFacatory, sal_True) ;
                break;
        }
        ::rtl::OUString aDSName = GetEntryText( m_pTreeView->getListBox()->GetRootLevelParent( _pApplyTo ) );

        if (bEdit)
            pDispatcher->edit(aDSName, sCurrentObject, xConnection);
        else
            pDispatcher->create(aDSName, xConnection);
        delete pDispatcher;
    }
    catch(SQLException& e)
    {
        showError(SQLExceptionInfo(e));
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::implCreateObject: caught an exception!");
    }
}

// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::implRemoveQuery( SvLBoxEntry* _pApplyTo )
{
    String sDsName = GetEntryText( m_pTreeView->getListBox()->GetRootLevelParent( _pApplyTo ) );
    String sName = GetEntryText( _pApplyTo );
    if (!sDsName.Len() || !sName.Len())
    {
        DBG_ERROR("SbaTableQueryBrowser::implRemoveQuery: invalid entries detected!");
        return;
    }

    String aMsg(ModuleRes(STR_QUERY_DELETE_QUERY));
    aMsg.SearchAndReplaceAscii("$name$", sName);
    OSQLMessageBox aDlg(getBrowserView()->getVclControl(),String(ModuleRes(STR_TITLE_CONFIRM_DELETION )),aMsg,WB_YES_NO | WB_DEF_YES,OSQLMessageBox::Query);
    if(aDlg.Execute() == RET_YES)
    {
        Reference<XQueryDefinitionsSupplier> xSet;
        try
        {
            if(m_xDatabaseContext->hasByName(sDsName))
                m_xDatabaseContext->getByName(sDsName) >>= xSet;
        }
        catch(Exception&)
        {
        }
        if(xSet.is())
        {
            Reference<XNameContainer> xNames(xSet->getQueryDefinitions(),UNO_QUERY);
            if(xNames.is())
            {
                try
                {
                    xNames->removeByName(sName);
                }
                catch(SQLException& e)
                {
                    showError(SQLExceptionInfo(e));
                }
                catch(Exception&)
                {
                    DBG_ERROR("SbaTableQueryBrowser::implRemoveQuery: caught a generic exception!");
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::implDropTable( SvLBoxEntry* _pApplyTo )
{
    ::osl::MutexGuard aGuard(m_aEntryMutex);
    Reference<XConnection> xConnection;	 // supports the service sdb::connection
    if(!ensureConnection(_pApplyTo, xConnection))
        return;

    // get all needed properties for design
    Reference<XTablesSupplier> xSup(xConnection,UNO_QUERY);
    OSL_ENSURE(xSup.is(),"SbaTableQueryBrowser::implDropTable: no XTablesSuppier!");
    if(!xSup.is())
        return;

    ::rtl::OUString sTableName = GetEntryText( _pApplyTo );

    Reference<XNameAccess> xTables = xSup->getTables();
    Reference<XDrop> xDrop(xTables,UNO_QUERY);
    if(xDrop.is())
    {
        String aMsg(ModuleRes(STR_QUERY_DELETE_TABLE));
        aMsg.SearchAndReplace(String::CreateFromAscii("%1"),String(sTableName));
        OSQLMessageBox aDlg(getBrowserView()->getVclControl(),String(ModuleRes(STR_TITLE_CONFIRM_DELETION )),aMsg,WB_YES_NO | WB_DEF_YES,OSQLMessageBox::Query);
        if(aDlg.Execute() == RET_YES)
        {
            SQLExceptionInfo aErrorInfo;
            try
            {
                if(xTables->hasByName(sTableName))
                    xDrop->dropByName(sTableName);
                else
                {// could be a view
                    Reference<XViewsSupplier> xViewsSup(xConnection,UNO_QUERY);
                    
                    Reference<XNameAccess> xViews;
                    if(xViewsSup.is())
                        xViews = xViewsSup->getViews();
                    if(xViews.is() && xViews->hasByName(sTableName))
                    {
                        xDrop = Reference<XDrop>(xViews,UNO_QUERY);
                        if(xDrop.is())
                            xDrop->dropByName(sTableName);
                    }
                }
            }
            catch(SQLContext& e) { aErrorInfo = e; }
            catch(SQLWarning& e) { aErrorInfo = e; }
            catch(SQLException& e) { aErrorInfo = e; }
            catch(Exception&)
            {
                DBG_ERROR("SbaTableQueryBrowser::implDropTable: suspicious exception caught!");
            }

            if (aErrorInfo.isValid())
                showError(aErrorInfo);
        }
    }
    else
    {
        String sMessage(ModuleRes(STR_MISSING_TABLES_XDROP));
        ErrorBox aError(getView(), WB_OK, sMessage);
        aError.Execute();
    }
}

// -----------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::requestContextMenu( const CommandEvent& _rEvent )
{
    Point aPosition;
    SvLBoxEntry* pEntry = NULL;
    SvLBoxEntry* pOldSelection = NULL;
    if (_rEvent.IsMouseEvent())
    {
        aPosition = _rEvent.GetMousePosPixel();
        // ensure that the entry which the user clicked at is selected
        pEntry = m_pTreeView->getListBox()->GetEntry(aPosition);
        if (pEntry && !m_pTreeView->getListBox()->IsSelected(pEntry))
        {
            pOldSelection = m_pTreeView->getListBox()->FirstSelected();
            m_pTreeView->getListBox()->lockAutoSelect();
            m_pTreeView->getListBox()->Select(pEntry);
            m_pTreeView->getListBox()->unlockAutoSelect();
        }
    }
    else
    {
        // use the center of the current entry
        pEntry = m_pTreeView->getListBox()->GetCurEntry();
        OSL_ENSURE(pEntry,"No current entry!");
        aPosition = m_pTreeView->getListBox()->GetEntryPos(pEntry);
        aPosition.X() += m_pTreeView->getListBox()->GetOutputSizePixel().Width() / 2;
        aPosition.Y() += m_pTreeView->getListBox()->GetEntryHeight() / 2;
    }

    // disable entries according to the currently selected entry

    // does the datasource which the selected entry belongs to has an open connection ?
    SvLBoxEntry* pDSEntry = NULL;
    DBTreeListModel::DBTreeListUserData* pDSData = NULL;
    DBTreeListModel::DBTreeListUserData* pEntryData = NULL;
    if(pEntry)
    {
        pDSEntry = m_pTreeView->getListBox()->GetRootLevelParent(pEntry);
        pDSData =	pDSEntry
                ?	static_cast<DBTreeListModel::DBTreeListUserData*>(pDSEntry->GetUserData())
                :	NULL;
        pEntryData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntry->GetUserData());
    }

    
    EntryType eType = pEntryData ? pEntryData->eType : etUnknown;

    // get the popup menu to use
    sal_uInt16 nMenuResId = MENU_BROWSER_DEFAULTCONTEXT;
    if (pEntry && (etDatasource != getEntryType(pEntry)))
    {
        switch (eType)
        {
            case etTable:
            case etTableContainer:
                nMenuResId = MENU_BROWSER_TABLECONTEXT;
                break;
            case etView:
                nMenuResId = MENU_BROWSER_VIEWCONTEXT;
                break;

            case etQueryContainer:
            case etQuery:
                nMenuResId = MENU_BROWSER_QUERYCONTEXT;
                break;

            case etBookmarkContainer:
            case etBookmark:
                nMenuResId = MENU_BROWSER_BOOKMARKCONTEXT;
                break;
        }
    }

    ModuleRes nMenuRes( nMenuResId );
    PopupMenu aContextMenu( nMenuRes );
    PopupMenu* pDynamicSubMenu = NULL;

    // enable menu entries
    if (!pDSData || !pDSData->xObject.is())
    {	// no -> disable the connection-related menu entries
        aContextMenu.EnableItem(ID_TREE_CLOSE_CONN, sal_False);
        aContextMenu.EnableItem(ID_TREE_REBUILD_CONN, sal_False);
    }

    if(pEntry)
    {
        switch (eType)
        {
            // 1. for tables
            case etTableContainer:
            case etTable:
            {
                // 1.2 pasting tables
                sal_Bool bPasteAble = isTableFormat();
                aContextMenu.EnableItem(ID_TREE_TABLE_PASTE, bPasteAble);

                // 1.3 actions on existing tables
                aContextMenu.EnableItem(ID_EDIT_TABLE,		etTable == eType);
                aContextMenu.EnableItem(ID_DROP_TABLE,		etTable == eType);
                aContextMenu.EnableItem(ID_TREE_TABLE_COPY,	etTable == eType);
            }
            break;
            // 2. for views
            case etView:
            {
                // 2.2 pasting tables
                sal_Bool bPasteAble = isTableFormat();
                aContextMenu.EnableItem(ID_TREE_VIEW_PASTE, bPasteAble);

                // 2.3 actions on existing tables
                aContextMenu.EnableItem(ID_DROP_VIEW,		sal_True);
                aContextMenu.EnableItem(ID_TREE_VIEW_COPY,	sal_True);

            }
            break;

            // 3. for queries
            case etQueryContainer:
            case etQuery:
            {
                // 3.2 actions on existing queries
                aContextMenu.EnableItem(ID_EDIT_QUERY_DESIGN,	etQuery == eType);
                aContextMenu.EnableItem(ID_DROP_QUERY,			etQuery == eType);
                aContextMenu.EnableItem(ID_TREE_QUERY_COPY,		etQuery == eType);
            }
            break;

            // 4. for bookmarks
            case etBookmarkContainer:
            case etBookmark:
            {
                aContextMenu.EnableItem(ID_EDIT_LINK,		etBookmark == eType);
                aContextMenu.EnableItem(ID_DROP_LINK,		etBookmark == eType);
                aContextMenu.EnableItem(ID_OPEN_DOCUMENT,	etBookmark == eType);
                aContextMenu.EnableItem(ID_EDIT_DOCUMENT,	etBookmark == eType);

                pDynamicSubMenu = new PopupMenu(ModuleRes(RID_NEW_FORM));
                aContextMenu.SetPopupMenu(ID_CREATE_NEW_DOC, pDynamicSubMenu);
            }
            break;
        }
    }

    // rebuild conn not implemented yet
    aContextMenu.EnableItem(ID_TREE_REBUILD_CONN, sal_False);

    if (!m_xMultiServiceFacatory.is())
        // no ORB -> no administration dialog
        aContextMenu.EnableItem(ID_TREE_ADMINISTRATE, sal_False);

    // no disabled entries
    aContextMenu.RemoveDisabledEntries();

    sal_Bool bReopenConn = sal_False;
    USHORT nPos = aContextMenu.Execute(m_pTreeView->getListBox(), aPosition);

    delete pDynamicSubMenu;
    pDynamicSubMenu = NULL;

    // restore the old selection
    if (pOldSelection)
    {
        m_pTreeView->getListBox()->lockAutoSelect();
        m_pTreeView->getListBox()->Select(pOldSelection);
        m_pTreeView->getListBox()->unlockAutoSelect();
    }

    switch (nPos)
    {
        case ID_TREE_ADMINISTRATE:
            implAdministrate(pEntry);
            break;

        case ID_DIRECT_SQL:
            implDirectSQL(pEntry);
            break;

        case ID_TREE_REBUILD_CONN:
            bReopenConn = sal_True;

        case ID_TREE_CLOSE_CONN:
            openHelpAgent(HID_DSBROWSER_DISCONNECTING);
            closeConnection(pDSEntry);
            break;

        case ID_TREE_RELATION_DESIGN:
        case ID_NEW_TABLE_DESIGN:
        case ID_NEW_VIEW_DESIGN:
        case ID_NEW_QUERY_DESIGN:
        case ID_NEW_QUERY_SQL:
        case ID_EDIT_QUERY_DESIGN:
        case ID_EDIT_TABLE:
            implCreateObject( pEntry, nPos );
            break;

        case ID_DROP_QUERY:
            implRemoveQuery( pEntry );
            break;

        case ID_DROP_TABLE:
        case ID_DROP_VIEW:
            implDropTable( pEntry );
            break;

        case ID_TREE_QUERY_COPY:
        {
            TransferableHelper* pTransfer = implCopyObject( pEntry, CommandType::QUERY );
            Reference< XTransferable> aEnsureDelete = pTransfer;
            if (pTransfer)
#if SUPD<631
                pTransfer->CopyToClipboard();
#else
                pTransfer->CopyToClipboard(getView());
#endif
        }
        break;

        case ID_TREE_TABLE_COPY:
        case ID_TREE_VIEW_COPY:
        {
            TransferableHelper* pTransfer = implCopyObject( pEntry, CommandType::TABLE );
            Reference< XTransferable> aEnsureDelete = pTransfer;

            if (pTransfer)
#if SUPD<631
                pTransfer->CopyToClipboard();
#else
                pTransfer->CopyToClipboard(getView());
#endif
        }
        break;

        case ID_TREE_TABLE_PASTE:
        case ID_TREE_VIEW_PASTE:
        {
#if SUPD<631
            TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard());
#else
            TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(getView()));
#endif
            implPasteTable( pEntry, aTransferData );
        }
        break;

        case ID_NEW_LINK:
        case ID_OPEN_DOCUMENT:
        case ID_EDIT_DOCUMENT:
        case ID_EDIT_LINK:
        case ID_DROP_LINK:
        case ID_FORM_NEW_TEXT:
        case ID_FORM_NEW_CALC:
        case ID_FORM_NEW_IMPRESS:
        case ID_FORM_NEW_PILOT:
        case ID_FORM_NEW_TEMPLATE:
        {
            // get the container of the bookmarks
            SvLBoxEntry* pContainer = isContainer(pEntry) ? pEntry : m_pTreeView->getListBox()->GetParent(pEntry);
            if (!ensureEntryObject(pContainer))
                break;

            String sSelectedObject = GetEntryText(pEntry);

            DBTreeListModel::DBTreeListUserData* pContainerData = static_cast<DBTreeListModel::DBTreeListUserData*>(pContainer->GetUserData());
            Reference< XNameAccess > xBookmarks(pContainerData->xObject, UNO_QUERY);

            OLinkedDocumentsAccess aHelper(getView(), getORB(), xBookmarks);

            switch (nPos)
            {
                case ID_NEW_LINK:
                    aHelper.addLinkUI();
                    break;

                case ID_OPEN_DOCUMENT:
                    aHelper.open(sSelectedObject, sal_True);
                    break;

                case ID_EDIT_DOCUMENT:
                    aHelper.open(sSelectedObject, sal_False);
                    break;

                case ID_EDIT_LINK:
                {
                    ::rtl::OUString sNewName, sNewLocation;
                    aHelper.edit(sSelectedObject, sNewName, sNewLocation);
                }
                break;

                case ID_DROP_LINK:
                    aHelper.drop(sSelectedObject);
                    break;

                case ID_FORM_NEW_TEXT:
                case ID_FORM_NEW_CALC:
                case ID_FORM_NEW_IMPRESS:
                case ID_FORM_NEW_PILOT:
                case ID_FORM_NEW_TEMPLATE:
                    aHelper.newForm(nPos);
                    break;

                default:
                    DBG_ERROR("SbaTableQueryBrowser::requestContextMenu: invalid menu id!");
                    break;
            }
        }
        break;
    }

    return sal_True;	// handled
}

// -----------------------------------------------------------------------------
SbaTableQueryBrowser::EntryType SbaTableQueryBrowser::getChildType( SvLBoxEntry* _pEntry )
{
    DBG_ASSERT(isContainer(_pEntry), "SbaTableQueryBrowser::getChildType: invalid entry!");
    switch (getEntryType(_pEntry))
    {
        case etTableContainer:
            return etTable;
        case etQueryContainer:
            return etQuery;
        case etBookmarkContainer:
            return etBookmark;
    }
    return etUnknown;
}

// -----------------------------------------------------------------------------
String SbaTableQueryBrowser::GetEntryText( SvLBoxEntry* _pEntry )
{
    return m_pTreeView->getListBox()->GetEntryText(_pEntry);
}

// -----------------------------------------------------------------------------
SbaTableQueryBrowser::EntryType SbaTableQueryBrowser::getEntryType( SvLBoxEntry* _pEntry )
{
    if (!_pEntry)
        return etUnknown;

    SvLBoxEntry* pRootEntry		= m_pTreeView->getListBox()->GetRootLevelParent(_pEntry);
    SvLBoxEntry* pEntryParent	= m_pTreeView->getListBox()->GetParent(_pEntry);
    SvLBoxEntry* pTables		= m_pTreeView->getListBox()->GetEntry(pRootEntry, CONTAINER_TABLES);
    SvLBoxEntry* pQueries		= m_pTreeView->getListBox()->GetEntry(pRootEntry, CONTAINER_QUERIES);
    SvLBoxEntry* pBookmarks		= m_pTreeView->getListBox()->GetEntry(pRootEntry, CONTAINER_BOOKMARKS);

#ifdef DBG_UTIL
    String sTest;
    if (pTables) sTest = m_pTreeView->getListBox()->GetEntryText(pTables);
    if (pQueries) sTest = m_pTreeView->getListBox()->GetEntryText(pQueries);
    if (pBookmarks) sTest = m_pTreeView->getListBox()->GetEntryText(pBookmarks);
#endif

    if (pRootEntry == _pEntry)
        return etDatasource;

    if (pTables == _pEntry)
        return etTableContainer;

    if (pQueries == _pEntry)
        return etQueryContainer;

    if (pBookmarks == _pEntry)
        return etBookmarkContainer;

    if (pTables == pEntryParent)
        return etTable;

    if (pQueries == pEntryParent)
        return etQuery;

    if (pBookmarks == pEntryParent)
        return etBookmark;

    return etUnknown;
}
// -----------------------------------------------------------------------------
// set the title of the beamer
void SbaTableQueryBrowser::setTitle(const ::rtl::OUString& _rsDataSourceName,const ::rtl::OUString& _rsName)  const
{
    ::rtl::OUString sTitle = _rsDataSourceName;
    if(_rsName.getLength())
    {
        sTitle += ::rtl::OUString::createFromAscii(": ");
        sTitle += _rsName;
    }
    Reference<XPropertySet> xProp(m_xCurrentFrame,UNO_QUERY);
    if(xProp.is() && xProp->getPropertySetInfo()->hasPropertyByName(PROPERTY_TITLE))
        xProp->setPropertyValue(PROPERTY_TITLE,makeAny(sTitle));
}

// .........................................................................
}	// namespace dbaui
// .........................................................................


