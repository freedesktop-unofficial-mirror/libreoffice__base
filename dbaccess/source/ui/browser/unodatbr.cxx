/*************************************************************************
 *
 *  $RCSfile: unodatbr.cxx,v $
 *
 *  $Revision: 1.16 $
 *
 *  last change: $Author: fs $ $Date: 2000-12-15 15:54:12 $
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
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif

//#ifndef _DLGSIZE_HXX
//#include "dlgsize.hxx"
//#endif
//#ifndef _SBA_SBATTRDLG_HXX
//#include "dlgattr.hxx"
//#endif
#ifndef _COM_SUN_STAR_FORM_XLOADABLE_HPP_
#include <com/sun/star/form/XLoadable.hpp>
#endif
#ifndef _SV_MSGBOX_HXX //autogen
#include <vcl/msgbox.hxx>
#endif
#ifndef _CPPUHELPER_EXTRACT_HXX_
#include <cppuhelper/extract.hxx>
#endif

#ifndef _SFXDISPATCH_HXX //autogen
#include <sfx2/dispatch.hxx>
#endif

#ifndef _SV_MULTISEL_HXX //autogen
#include <tools/multisel.hxx>
#endif

#ifndef _URLOBJ_HXX //autogen
#include <tools/urlobj.hxx>
#endif

#ifndef _SFXINTITEM_HXX //autogen
#include <svtools/intitem.hxx>
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

#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
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
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
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
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XVIEWSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
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
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _SVX_ALGITEM_HXX //autogen
#include <svx/algitem.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XRESULTSETACCESS_HPP_
#include <com/sun/star/sdb/XResultSetAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLWARNING_HPP_
#include <com/sun/star/sdbc/SQLWarning.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_XWINDOW_HPP_
#include <com/sun/star/awt/XWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYSTATE_HPP_
#include <com/sun/star/beans/PropertyState.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
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
#ifndef _SV_WAITOBJ_HXX
#include <vcl/waitobj.hxx>
#endif

using namespace ::com::sun::star::ui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ui;
using namespace ::com::sun::star::task;
using namespace ::dbtools;

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
    return ::rtl::OUString::createFromAscii("org.openoffice.dbaccess.ODatabaseBrowser");
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
    return *(new SbaTableQueryBrowser(_rxFactory));
}
//------------------------------------------------------------------------------
SbaTableQueryBrowser::SbaTableQueryBrowser(const Reference< XMultiServiceFactory >& _rM)
    :SbaXDataBrowserController(_rM)
    ,m_pTreeModel(NULL)
    ,m_pTreeView(NULL)
    ,m_pSplitter(NULL)
    ,m_pCurrentlyLoaded(NULL)
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
void SAL_CALL SbaTableQueryBrowser::dispose()
{
    // reset the content's tree view: it holds a reference to our model which is to be deleted immediately,
    // and it will live longer than we do.
    if (getContent())
        getContent()->setTreeView(NULL);

    // clear the user data of the tree model
    SvLBoxEntry* pEntryLoop = m_pTreeModel->First();
    while (pEntryLoop)
    {
        DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntryLoop->GetUserData());
        if(pData)
        {
            ::comphelper::disposeComponent(pData->xObject);
            delete pData;
        }
        pEntryLoop = m_pTreeModel->Next(pEntryLoop);
    }
    // clear the tree model
    delete m_pTreeModel;
    m_pTreeModel = NULL;

    // remove the container listener from the database context
    Reference< XContainer > xDatasourceContainer(m_xDatabaseContext, UNO_QUERY);
    if (xDatasourceContainer.is())
        xDatasourceContainer->removeContainerListener(this);

    SbaXDataBrowserController::dispose();
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::Construct(Window* pParent)
{
    if (!SbaXDataBrowserController::Construct(pParent))
        return sal_False;

    // create the database context
    DBG_ASSERT(m_xMultiServiceFacatory.is(), "SbaTableQueryBrowser::Constructneed a service factory !");
    try
    {
        m_xDatabaseContext = Reference< XNameAccess >(m_xMultiServiceFacatory->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
        Reference< XContainer > xDatasourceContainer(m_xDatabaseContext, UNO_QUERY);
        if (xDatasourceContainer.is())
            xDatasourceContainer->addContainerListener(this);
        else
            DBG_ERROR("SbaTableQueryBrowser::Construct: the DatabaseContext should allow us to be a listener!");
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::Construct: could not create (or start listening at) the database context!");
    }

    if (!m_xDatabaseContext.is())
    {	// at least notify the user. Though the whole component does not make any sense without the database context ...
        ShowServiceNotAvailableError(getContent(), String(SERVICE_SDB_DATABASECONTEXT), sal_True);
    }

    // some help ids
    if (getContent() && getContent()->getVclControl())
    {
        
        // create controls and set sizes
        const long	nFrameWidth = getContent()->LogicToPixel( Size( 3, 0 ), MAP_APPFONT ).Width();

        m_pSplitter = new Splitter(getContent(),WB_HSCROLL);
        m_pSplitter->SetPosSizePixel( Point(0,0), Size(nFrameWidth,0) );
        m_pSplitter->SetBackground( Wallpaper( Application::GetSettings().GetStyleSettings().GetDialogColor() ) );
        m_pSplitter->Show();

        m_pTreeView = new DBTreeView(getContent(), m_xMultiServiceFacatory, WB_TABSTOP);
        m_pTreeView->Show();
        m_pTreeView->SetPreExpandHandler(LINK(this, SbaTableQueryBrowser, OnExpandEntry));
        m_pTreeView->SetContextMenuHandler(LINK(this, SbaTableQueryBrowser, OnListContextMenu));
        m_pTreeView->SetHelpId(HID_CTL_TREEVIEW);

        // a default pos for the splitter, so that the listbox is about 80 (logical) pixels wide
        m_pSplitter->SetSplitPosPixel( getContent()->LogicToPixel( Size( 80, 0 ), MAP_APPFONT ).Width() );

        getContent()->setSplitter(m_pSplitter);
        getContent()->setTreeView(m_pTreeView);

        // fill view with data
        m_pTreeModel = new DBTreeListModel;
        m_pTreeView->setModel(m_pTreeModel);
        m_pTreeView->setSelectHdl(LINK(this, SbaTableQueryBrowser, OnSelectEntry));
        initializeTreeModel();

        // TODO
        getContent()->getVclControl()->GetDataWindow().SetUniqueId(UID_DATABROWSE_DATAWINDOW);
        getContent()->getVclControl()->SetHelpId(HID_CTL_TABBROWSER);
        getContent()->SetUniqueId(UID_CTL_CONTENT);
        if (getContent()->getVclControl()->GetHeaderBar())
            getContent()->getVclControl()->GetHeaderBar()->SetHelpId(HID_DATABROWSE_HEADER);

        InvalidateFeature(ID_BROWSER_EXPLORER);
    }

    return sal_True;
}
// -------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::InitializeForm(const Reference< ::com::sun::star::sdbc::XRowSet > & _rxForm)
{
    try
    {
        // set the parent of the ::com::sun::star::form::Form
        Reference< ::com::sun::star::form::XForm >  xForm(_rxForm, UNO_QUERY);
//		{
//			DbEnvironmentAccess aEnv;
//			if (aEnv.getEnv().is())
//			{
//				Reference< ::com::sun::star::sdb::XDatabaseAccess >  xDatabase = aEnv.getEnv()->getDatabaseAccess(m_xDatabase->Name());
//				if (xDatabase.is())
//					xForm->setParent(xDatabase->getConnection(::rtl::OUString(),::rtl::OUString()));
//			}
//		}

        // we send all properties at once, maybe the implementation is clever enough to handle one big PropertiesChanged
        // more effective than many small PropertyChanged ;)
        Sequence< ::rtl::OUString> aProperties(6);
        Sequence< Any> aValues(6);

        // is the filter intially applied ?
//		const SfxBoolItem* pFilterApplied = (const SfxBoolItem*)getDefinition()->GetObjAttrs()->GetItem(SBA_DEF_FILTERAPPLIED);
//		aProperties.getArray()[0] = PROPERTY_APPLYFILTER;
//		aValues.getArray()[0] = ::utl::makeBoolAny((sal_Bool)(pFilterApplied ? pFilterApplied->GetValue() : sal_False));
//
//		// cursor source
//		aProperties.getArray()[1] = PROPERTY_COMMAND;
//		aValues.getArray()[1] <<= ::rtl::OUString(m_xDefinition->Name());
//			// may be replaced with a sql statement below
//
//		// cursor source type
//		aProperties.getArray()[2] = PROPERTY_COMMANDTYPE;
//
//		sal_Int32 nType = ::com::sun::star::sdb::CommandType::COMMAND;
//		sal_Bool bEscapeProcessing = sal_True;
//		switch (m_xDefinition->GetKind())
//		{
//			case dbTable : nType = ::com::sun::star::sdb::CommandType::TABLE; break;
//			case dbQuery :
//				if (m_xDefinition->Name().Len())
//					nType = ::com::sun::star::sdb::CommandType::QUERY;
//				else
//				{	// it is a temporary query object
//					SbaQueryDef* pQuery = PTR_CAST(SbaQueryDef, &m_xDefinition);
//					DBG_ASSERT(pQuery, "SbaTableQueryBrowser::InitializeForm : the object is of kind dbQuery but no query def ?");
//
//					if (pQuery->IsNative())
//						bEscapeProcessing = sal_False;
//					
//					aValues.getArray()[1] <<= ::rtl::OUString(pQuery->Statement());
//				}
//				break;
//
//			default : DBG_ERROR("SbaTableQueryBrowser::InitializeForm : the definition has to be a table or a query !");
//		}
//		aValues.getArray()[2] <<= nType;
//
//		// escape processing ?
//		aProperties.getArray()[3] = PROPERTY_USE_ESCAPE_PROCESSING;
//		aValues.getArray()[3].setValue(&bEscapeProcessing,::getBooleanCppuType());
//
//		// the initial filter
//		const SfxStringItem* pFilterSort = (const SfxStringItem*)getDefinition()->GetObjAttrs()->GetItem(SBA_DEF_FILTER);
//		aProperties.getArray()[4] = PROPERTY_FILTER;
//		aValues.getArray()[4] <<= ::rtl::OUString(pFilterSort ? ::rtl::OUString(pFilterSort->GetValue()) : ::rtl::OUString());
//
//		// the initial ordering
//		pFilterSort = (const SfxStringItem*)getDefinition()->GetObjAttrs()->GetItem(SBA_DEF_SORT);
//		aProperties.getArray()[5] = PROPERTY_ORDER;
//		aValues.getArray()[5] <<= ::rtl::OUString(pFilterSort ? ::rtl::OUString(pFilterSort->GetValue()) : ::rtl::OUString());
//
//		Reference< XMultiPropertySet >  xFormMultiSet(_rxForm, UNO_QUERY);
//		xFormMultiSet->setPropertyValues(aProperties, aValues);
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
        
        // get the formats supplier of the database we're working with
        Reference< ::com::sun::star::util::XNumberFormatsSupplier >  xSupplier = getNumberFormatter()->getNumberFormatsSupplier();

        Reference<XConnection> xConnection; 
        Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
        xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION) >>= xConnection;
        OSL_ENSHURE(xConnection.is(),"A ActiveConnection should normaly exists!");

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
            xColumns->getByName(*pBegin) >>= xColumn;

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
            xCurrentCol->setPropertyValue(PROPERTY_ALIGN, xColumn->getPropertyValue(PROPERTY_ALIGN));

            // ... the 'comment' property as helptext (will usually be shown as header-tooltip)
            
            Any aDescription; aDescription <<= ::rtl::OUString();
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
                aDescription <<= comphelper::getString(xColumn->getPropertyValue(PROPERTY_DESCRIPTION));
            xCurrentCol->setPropertyValue(PROPERTY_HELPTEXT, xColumn->getPropertyValue(PROPERTY_DESCRIPTION));

            xColContainer->insertByName(*pBegin, makeAny(xCurrentCol));
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
    ToolBox* pTB = NULL;
    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
    if(xProp.is())
    {
        sal_Int32 nType;
        xProp->getPropertyValue(::rtl::OUString::createFromAscii("CommandType")) >>= nType;

        sal_uInt16 nResId = 0;
        switch (nType)
        {
            case CommandType::TABLE :	nResId = RID_BRW_TAB_TOOLBOX; break;
            case CommandType::QUERY :	nResId = RID_BRW_QRY_TOOLBOX; break;
            case CommandType::COMMAND:	nResId = RID_BRW_QRY_TOOLBOX; break;
            default : return NULL;
        }

        pTB = new ToolBox(_pParent, ModuleRes(nResId));
        if (!pTB)
            return NULL;
    }
    return pTB;
}

// -----------------------------------------------------------------------
void SbaTableQueryBrowser::propertyChange(const PropertyChangeEvent& evt)
{
    SbaXDataBrowserController::propertyChange(evt);

//	Reference< XPropertySet >  xSource(evt.Source, UNO_QUERY);
//	if (!xSource.is())
//		return;
//
//	// one of the many properties which require us to update the definition ?
//	// a column's width ?
//	if (evt.PropertyName.equals(PROPERTY_WIDTH))
//	{	// a column width has changed -> update the model
//		// (the update of the view is done elsewhere)
//		SbaColumn* pAffectedCol = GetDefinitionCol(xSource);
//		if (pAffectedCol)
//		{
//			SbaColRowSizeItem aNewWidth(SBA_DEF_FLTCOLWIDTH);
//			sal_Bool bDefault = !evt.NewValue.hasValue();
//			SfxBoolItem aDefault(SBA_DEF_FLTCOLWIDTH_DEFAULT, bDefault);
//			if (bDefault)
//				// this is for older versions which don't know the default flag
//				aNewWidth.PutLogicValue((sal_uInt16)227);
//			else
//				aNewWidth.PutLogicValue((sal_uInt16)::utl::getINT32(evt.NewValue));
//
//			pAffectedCol->Put(aNewWidth);
//			pAffectedCol->Put(aDefault);
//		}
//	}
//
//	// a column's 'visible' state ?
//	if (evt.PropertyName.equals(PROPERTY_HIDDEN))
//	{
//		SbaColumn* pAffectedCol = GetDefinitionCol(xSource);
//		if (pAffectedCol)
//			pAffectedCol->Put(SfxBoolItem(SBA_DEF_FLTHIDE, ::utl::getBOOL(evt.NewValue)));
//	}
//
//	// a columns alignment ?
//	if (evt.PropertyName.equals(PROPERTY_ALIGN))
//	{
//		SbaColumn* pAffectedCol = GetDefinitionCol(xSource);
//		if (pAffectedCol)
//		{
//			SvxCellHorJustify eHorJustify = SVX_HOR_JUSTIFY_STANDARD;
//			if (evt.NewValue.hasValue())
//				switch (::utl::getINT16(evt.NewValue))
//				{
//					case ::com::sun::star::awt::TextAlign::LEFT:
//						eHorJustify = SVX_HOR_JUSTIFY_LEFT;
//						break;
//					case ::com::sun::star::awt::TextAlign::CENTER:
//						eHorJustify = SVX_HOR_JUSTIFY_CENTER;
//						break;
//					case ::com::sun::star::awt::TextAlign::RIGHT:
//						eHorJustify = SVX_HOR_JUSTIFY_RIGHT;
//						break;
//				}
//
//			pAffectedCol->Put(SvxHorJustifyItem(eHorJustify, SBA_ATTR_ALIGN_HOR_JUSTIFY));
//		}
//	}
//
//	// a column's format ?
//	if	(	(evt.PropertyName.equals(PROPERTY_FORMATKEY))
//		&&	(TypeClass_LONG == evt.NewValue.getValueTypeClass())
//		)
//	{
//		// update the model (means the definition object)
//		SbaColumn* pAffectedCol = GetDefinitionCol(xSource);
//		if (pAffectedCol)
//			pAffectedCol->Put(SfxUInt32Item(SBA_DEF_FMTVALUE, ::utl::getINT32(evt.NewValue)));
//	}
//
//	// some table definition properties ?
//	// the height of the rows in the grid ?
//	if (evt.PropertyName.equals(PROPERTY_ROW_HEIGHT))
//	{
//		if (getDefinition())
//		{
//			SbaColRowSizeItem aNewHeight(SBA_DEF_ROWHEIGHT);
//			sal_Bool bDefault = !evt.NewValue.hasValue();
//			SfxBoolItem aDefault(SBA_DEF_FLTCOLWIDTH_DEFAULT, bDefault);
//
//			if (bDefault)
//				aNewHeight.PutLogicValue((sal_uInt16)45);
//			else
//				aNewHeight.PutLogicValue((sal_uInt16)::utl::getINT32(evt.NewValue));
//
//			getDefinition()->GetObjAttrs()->Put(aNewHeight);
//			getDefinition()->GetObjAttrs()->Put(aDefault);
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
//
//	// the font of the grid ?
//	if (evt.PropertyName.equals(PROPERTY_FONT))
//	{
//		if (getDefinition())
//		{
//			BuildItemsFromFont(getDefinition()->GetObjAttrs(), *(::com::sun::star::awt::FontDescriptor*)evt.NewValue.getValue());
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
//
//	// the text color of the grid ?
//	if (evt.PropertyName.equals(PROPERTY_TEXTCOLOR))
//	{
//		if (getDefinition())
//		{
//			SvxColorItem aColor(Color(::utl::getINT32(evt.NewValue)), SBA_DEF_FONTCOLOR);
//			getDefinition()->GetObjAttrs()->Put(aColor);
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
//
//	// the filter ?
//	if (evt.PropertyName.equals(PROPERTY_FILTER))
//	{
//		if (getDefinition())
//		{
//			SfxStringItem aFilter(SBA_DEF_FILTER, ::utl::getString(evt.NewValue));
//			getDefinition()->GetObjAttrs()->Put(aFilter);
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
//
//	// the sort ?
//	if (evt.PropertyName.equals(PROPERTY_ORDER))
//	{
//		if (getDefinition())
//		{
//			SfxStringItem aSort(SBA_DEF_SORT, ::utl::getString(evt.NewValue));
//			getDefinition()->GetObjAttrs()->Put(aSort);
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
//
//	// the appliance of the filter ?
//	if (evt.PropertyName.equals(PROPERTY_APPLYFILTER))
//	{
//		if (getDefinition())
//		{
//			SfxBoolItem aApplied(SBA_DEF_FILTERAPPLIED, ::utl::getBOOL(evt.NewValue));
//			getDefinition()->GetObjAttrs()->Put(aApplied);
//			getDefinition()->PutObjAttrs(*(getDefinition()->GetObjAttrs()));
//				// this sets the modified flagd
//		}
//	}
}

// -----------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::suspend(sal_Bool bSuspend) throw( RuntimeException )
{
    if (!SbaXDataBrowserController::suspend(bSuspend))
        return sal_False;

//	if (getDefinition())
//	{
//		// let the definition save its UI settings
//		SbaDBDataDef* pDef = getDefinition();
//		if (pDef && !pDef->GetDatabase()->IsReadOnly() && pDef->IsModified())
//			pDef->Update();
//
//		// we aren't using the definition anymore
//		if (m_bUsingDefinition)
//		{
//			pDef->ReleaseUsage();
//			m_xDefinition = NULL;
//			m_bUsingDefinition = false;
//		}
//		
//	}
//
//	// we don't need to listen at the definition and its database anymore
    //	EndListening(*SBA_MOD());

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
            m_aDispatchStates[aLoop->first] = _rEvent.IsEnabled;
            implCheckExternalSlot(aLoop->first);
            break;
        }
    }
    DBG_ASSERT(aLoop != m_aDispatchers.end(), "SbaTableQueryBrowser::statusChanged: don't know who sent this!");
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::implCheckExternalSlot(sal_Int32 _nId)
{
    // check if we have to hide this item from the toolbox
    ToolBox* pTB = getContent()->getToolBox();
    if (pTB)
    {
        sal_Bool bHaveDispatcher = m_aDispatchers[_nId].is();
        if (bHaveDispatcher != pTB->IsItemVisible(_nId))
            bHaveDispatcher ? pTB->ShowItem(_nId) : pTB->HideItem(_nId);
    }

    // and invalidate this feature in general
    InvalidateFeature(_nId);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::disposing( const EventObject& _rSource ) throw(RuntimeException)
{
    // search the external dispatcher causing this call in our map
    Reference< XDispatch > xSource(_rSource.Source, UNO_QUERY);
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

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::attachFrame(const Reference< ::com::sun::star::frame::XFrame > & _xFrame) throw( RuntimeException )
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

    SbaXDataBrowserController::attachFrame(_xFrame);

    // get the dispatchers for the external slots
    Reference< XDispatchProvider >  xProvider(m_xCurrentFrame, UNO_QUERY);
    DBG_ASSERT(xProvider.is(), "SbaTableQueryBrowser::attachFrame: no DispatchPprovider !");
    if (xProvider.is())
    {
        sal_Int32 nExternalIds[] = { ID_BROWSER_FORMLETTER, ID_BROWSER_INSERTCOLUMNS, ID_BROWSER_INSERTCONTENT };
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
void SbaTableQueryBrowser::addModelListeners(const Reference< ::com::sun::star::awt::XControlModel > & _xGridControlModel)
{
    SbaXDataBrowserController::addModelListeners(_xGridControlModel);
    Reference< XPropertySet >  xCols(_xGridControlModel, UNO_QUERY);
    if (xCols.is())
    {
        xCols->addPropertyChangeListener(PROPERTY_ROW_HEIGHT, (XPropertyChangeListener*)this);
        xCols->addPropertyChangeListener(PROPERTY_FONT, (XPropertyChangeListener*)this);
        xCols->addPropertyChangeListener(PROPERTY_TEXTCOLOR, (XPropertyChangeListener*)this);
    }

}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::removeModelListeners(const Reference< ::com::sun::star::awt::XControlModel > & _xGridControlModel)
{
    SbaXDataBrowserController::removeModelListeners(_xGridControlModel);
    Reference< XPropertySet >  xSourceSet(_xGridControlModel, UNO_QUERY);
    if (xSourceSet.is())
    {
        xSourceSet->removePropertyChangeListener(PROPERTY_ROW_HEIGHT, (XPropertyChangeListener*)this);
        xSourceSet->removePropertyChangeListener(PROPERTY_FONT, (XPropertyChangeListener*)this);
        xSourceSet->removePropertyChangeListener(PROPERTY_TEXTCOLOR, (XPropertyChangeListener*)this);
    }
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
    SafeAddPropertyListener(xCol, PROPERTY_WIDTH, (XPropertyChangeListener*)this);
    SafeAddPropertyListener(xCol, PROPERTY_HIDDEN, (XPropertyChangeListener*)this);
    SafeAddPropertyListener(xCol, PROPERTY_ALIGN, (XPropertyChangeListener*)this);
    SafeAddPropertyListener(xCol, PROPERTY_FORMATKEY, (XPropertyChangeListener*)this);
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::RemoveColumnListener(const Reference< XPropertySet > & xCol)
{
    SbaXDataBrowserController::RemoveColumnListener(xCol);
    SafeRemovePropertyListener(xCol, PROPERTY_WIDTH, (XPropertyChangeListener*)this);
    SafeRemovePropertyListener(xCol, PROPERTY_HIDDEN, (XPropertyChangeListener*)this);
    SafeRemovePropertyListener(xCol, PROPERTY_ALIGN, (XPropertyChangeListener*)this);
    SafeRemovePropertyListener(xCol, PROPERTY_FORMATKEY, (XPropertyChangeListener*)this);
}
//------------------------------------------------------------------------------
void SbaTableQueryBrowser::AddSupportedFeatures()
{
    SbaXDataBrowserController::AddSupportedFeatures();

    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Title")]				= ID_BROWSER_TITLE;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/FormLetter")]	= ID_BROWSER_FORMLETTER;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/InsertColumns")] = ID_BROWSER_INSERTCOLUMNS;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/InsertContent")] = ID_BROWSER_INSERTCONTENT;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DataSourceBrowser/ToggleExplorer")] = ID_BROWSER_EXPLORER;
    
            // TODO reenable our own code if we really have a handling for the formslots
//		ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToFirst"),		SID_FM_RECORD_FIRST		),
//		ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToLast"),		SID_FM_RECORD_LAST		),
//		ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToNew"),		SID_FM_RECORD_NEW		),
//		ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToNext"),		SID_FM_RECORD_NEXT		),
//		ControllerFeature( ::rtl::OUString::createFromAscii("private:FormSlot/moveToPrev"),		SID_FM_RECORD_PREV		)

}

//------------------------------------------------------------------------------
FeatureState SbaTableQueryBrowser::GetState(sal_uInt16 nId)
{
    FeatureState aReturn;
        // (disabled automatically)

    if (ID_BROWSER_EXPLORER == nId)
    {	// this slot is available even if no form is loaded
        aReturn.bEnabled = sal_True;
        aReturn.aState = ::cppu::bool2any(haveExplorer());
        return aReturn;
    }

    try
    {
        // no chance without a view
        if (!getContent() || !getContent()->getVclControl())
            return aReturn;
        // no chance without valid models
        if (isValid() && !isValidCursor())
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
                    aReturn.bEnabled = aReturn.bEnabled && getContent()->getVclControl()->GetSelectRowCount();

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
                catch(Exception&)
                {
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
                            sTitle = String(ModuleRes(STR_QRY_TITLE)); break;
                        default:
                            DBG_ASSERT(0,"Unbekannte DBDef Art");
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
                aReturn.bEnabled = getContent() && getContent()->getVclControl() && isValid() && isValidCursor();
                //	aReturn.bEnabled &= getDefinition() && !getDefinition()->GetDatabase()->IsReadOnly();
                break;

            case ID_BROWSER_EDITDOC:
                aReturn = SbaXDataBrowserController::GetState(nId);
                //	aReturn.bEnabled &= !getDefinition()->IsLocked();
                    // somebody is modifying the definition -> no edit mode
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
    ;

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

        case ID_BROWSER_INSERTCOLUMNS:
        case ID_BROWSER_INSERTCONTENT:
        case ID_BROWSER_FORMLETTER:
            if (getContent() && isValidCursor())
            {
                // the URL the slot id is assigned to
                URL aParentUrl = getURLForId(nId);

                // let the dispatcher execute the slot
                Reference< XDispatch > xDispatch(m_aDispatchers[nId]);
                if (xDispatch.is())
                {
                    // set the properties for the dispatch
                    
                    // first fill the selection
                    SbaGridControl* pGrid = getContent()->getVclControl();
                    MultiSelection* pSelection = (MultiSelection*)pGrid->GetSelection();
                    Sequence< sal_Int32 > aSelection;
                    if (pSelection != NULL)
                    {
                        aSelection.realloc(pSelection->GetSelectCount());
                        long nIdx = pSelection->FirstSelected();
                        sal_Int32 i = 0;
                        while (nIdx >= 0)
                        {
                            aSelection[i++] = nIdx+1;
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
                    catch(Exception&)
                    {
                        DBG_ERROR("SbaTableQueryBrowser::Execute(ID_BROWSER_?): could not clone the cursor!");
                    }

                    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
                    
                    try
                    {
                        Sequence< PropertyValue> aProps(5);
                        aProps[0] = PropertyValue(PROPERTY_DATASOURCENAME, -1, xProp->getPropertyValue(PROPERTY_DATASOURCENAME), PropertyState_DIRECT_VALUE);
                        aProps[1] = PropertyValue(PROPERTY_COMMAND, -1, xProp->getPropertyValue(PROPERTY_COMMAND), PropertyState_DIRECT_VALUE);
                        aProps[2] = PropertyValue(PROPERTY_COMMANDTYPE, -1, xProp->getPropertyValue(PROPERTY_COMMANDTYPE), PropertyState_DIRECT_VALUE);
                        aProps[3] = PropertyValue(::rtl::OUString::createFromAscii("Selection"), -1, makeAny(aSelection), PropertyState_DIRECT_VALUE);
                        aProps[4] = PropertyValue(::rtl::OUString::createFromAscii("Cursor"), -1, makeAny(xCursorClone), PropertyState_DIRECT_VALUE);

                        xDispatch->dispatch(aParentUrl, aProps);
                    }
                    catch(Exception&)
                    {
                        DBG_ERROR("SbaTableQueryBrowser::Execute(ID_BROWSER_?): could not dispatch the slot (caught an exception)!");
                    }
                }
            }
            break;

        default:
            SbaXDataBrowserController::Execute(nId);
            break;
    }
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::implAddDatasource(const String& _rDbName, Image& _rDbImage,
        String& _rQueryName, Image& _rQueryImage, String& _rTableName, Image& _rTableImage)
{
    // initialize the names/images if necessary
    if (!_rQueryName.Len())
        _rQueryName = String(ModuleRes(RID_STR_QUERIES_CONTAINER));
    if (!_rTableName.Len())
        _rTableName = String(ModuleRes(RID_STR_TABLES_CONTAINER));

    if (!_rQueryImage)
        _rQueryImage = Image(ModuleRes(QUERYFOLDER_TREE_ICON));
    if (!_rTableImage)
        _rTableImage = Image(ModuleRes(TABLEFOLDER_TREE_ICON));

    if (!_rDbImage)
        _rDbImage = Image(ModuleRes(IMG_DATABASE));

    // add the entry for the data source
    SvLBoxEntry* pDatasourceEntry = m_pTreeView->getListBox()->InsertEntry(_rDbName, _rDbImage, _rDbImage, NULL, sal_False);
    pDatasourceEntry->SetUserData(new DBTreeListModel::DBTreeListUserData);

    // the child for the queries container
    SvLBoxEntry* pQueries = m_pTreeView->getListBox()->InsertEntry(_rQueryName, _rQueryImage, _rQueryImage, pDatasourceEntry, sal_True);
    DBTreeListModel::DBTreeListUserData* pQueriesData = new DBTreeListModel::DBTreeListUserData;
    pQueriesData->bTable = sal_False;
    pQueries->SetUserData(pQueriesData);

    // the child for the tables container
    SvLBoxEntry* pTables = m_pTreeView->getListBox()->InsertEntry(_rTableName, _rTableImage, _rTableImage, pDatasourceEntry, sal_True);
    DBTreeListModel::DBTreeListUserData* pTablesData = new DBTreeListModel::DBTreeListUserData;
    pTablesData->bTable = sal_True;
    pTables->SetUserData(pTablesData);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::initializeTreeModel()
{
    if (m_xDatabaseContext.is())
    {
        Image aDBImage, aQueriesImage, aTablesImage;
        String sQueriesName, sTablesName;

        // fill the model with the names of the registered datasources
        Sequence< ::rtl::OUString > aDatasources = m_xDatabaseContext->getElementNames();
        const ::rtl::OUString* pBegin	= aDatasources.getConstArray();
        const ::rtl::OUString* pEnd		= pBegin + aDatasources.getLength();
        for (; pBegin != pEnd; ++pBegin)
            implAddDatasource(*pBegin, aDBImage, sQueriesName, aQueriesImage, sTablesName, aTablesImage);
    }
}

// -------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::populateTree(const Reference<XNameAccess>& _xNameAccess, SvLBoxEntry* _pParent, const Image& _rImage)
{
    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pParent->GetUserData());
    if(pData)
        pData->xObject = _xNameAccess;

    try
    {
        Sequence< ::rtl::OUString > aNames = _xNameAccess->getElementNames();
        const ::rtl::OUString* pBegin	= aNames.getConstArray();
        const ::rtl::OUString* pEnd		= pBegin + aNames.getLength();
        for (; pBegin != pEnd; ++pBegin)
            m_pTreeView->getListBox()->InsertEntry(*pBegin, _rImage, _rImage, _pParent, sal_False);
    }
    catch(Exception&)
    {
        DBG_ERROR("SbaTableQueryBrowser::populateTree: could not fill the tree");
        return sal_False;
    }
    return sal_True;
}

//------------------------------------------------------------------------------
IMPL_LINK(SbaTableQueryBrowser, OnListContextMenu, const CommandEvent*, _pEvent)
{
    PopupMenu aContextMenu(ModuleRes(MENU_BROWSERTREE_CONTEXT));
    Point aPosition;
    if (_pEvent->IsMouseEvent())
    {
        aPosition = _pEvent->GetMousePosPixel();
        // ensure that the entry which the user clicked at is selected
        SvLBoxEntry* pClickedAt = m_pTreeView->getListBox()->GetEntry(aPosition);
        if (pClickedAt && !m_pTreeView->getListBox()->IsSelected(pClickedAt))
            m_pTreeView->getListBox()->SelectEntry(pClickedAt);
    }
    else
    {
        // use the center of the current entry
        aPosition = m_pTreeView->getListBox()->GetEntryPos(m_pTreeView->getListBox()->GetCurEntry());
        aPosition.X() += m_pTreeView->getListBox()->GetOutputSizePixel().Width() / 2;
        aPosition.Y() += m_pTreeView->getListBox()->GetEntryHeight() / 2;
    }

    // disable entries according to the currently selected entry

    // does the datasource which the selected entry belongs to has an open connection ?
    SvLBoxEntry* pDSEntry = m_pTreeView->getListBox()->GetRootLevelParent(m_pTreeView->getListBox()->GetCurEntry());
    DBTreeListModel::DBTreeListUserData* pDSData =
                pDSEntry
            ?	static_cast<DBTreeListModel::DBTreeListUserData*>(pDSEntry->GetUserData())
            :	NULL;
    if (!pDSData || !pDSData->xObject.is())
    {	// no -> disable the connection-related menu entries
        aContextMenu.EnableItem(ID_TREE_CLOSE_CONN, sal_False);
        aContextMenu.EnableItem(ID_TREE_REBUILD_CONN, sal_False);
    }

    // rebuild conn not implemented yet
    aContextMenu.EnableItem(ID_TREE_REBUILD_CONN, sal_False);

    if (!m_xMultiServiceFacatory.is())
        // no ORB -> no administration dialog
        aContextMenu.EnableItem(ID_TREE_ADMINISTRATE, sal_False);

    // no disabled entries
    aContextMenu.RemoveDisabledEntries();

    sal_Bool bReopenConn = sal_False;
    switch (aContextMenu.Execute(m_pTreeView->getListBox(), aPosition))
    {
        case ID_TREE_ADMINISTRATE:
            try
            {
                // the parameters:
                Sequence< Any > aArgs(2);
                // the parent window
                aArgs[0] <<= PropertyValue(
                    ::rtl::OUString::createFromAscii("ParentWindow"), 0, 
                    makeAny(VCLUnoHelper::GetInterface(m_pTreeView->getListBox()->Window::GetParent())), PropertyState_DIRECT_VALUE);
                // the initial selection
                SvLBoxEntry* pTopLevelSelected = m_pTreeView->getListBox()->GetCurEntry();
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
            }
            break;
        case ID_TREE_REBUILD_CONN:
            bReopenConn = sal_True;
        case ID_TREE_CLOSE_CONN:
        {
            closeConnection(pDSEntry);
        }
        break;
    }

    return 1L;	// handled
}

//------------------------------------------------------------------------------
IMPL_LINK(SbaTableQueryBrowser, OnExpandEntry, SvLBoxEntry*, _pParent)
{
    if (_pParent->HasChilds())
        // nothing to to ...
        return 1L;

    SvLBoxEntry* pFirstParent = m_pTreeView->getListBox()->GetRootLevelParent(_pParent);
    OSL_ENSHURE(pFirstParent,"SbaTableQueryBrowser::OnExpandEntry: No rootlevelparent!");

    DBTreeListModel::DBTreeListUserData* pData = static_cast< DBTreeListModel::DBTreeListUserData* >(_pParent->GetUserData());
    OSL_ENSHURE(pData,"SbaTableQueryBrowser::OnExpandEntry: No user data!");
    SvLBoxString* pString = static_cast<SvLBoxString*>(pFirstParent->GetFirstItem(SV_ITEM_ID_DBTEXTITEM));
    OSL_ENSHURE(pString,"SbaTableQueryBrowser::OnExpandEntry: No string item!");
    String aName(pString->GetText());
    Any aValue;
    try { aValue = m_xDatabaseContext->getByName(aName); }
    catch(Exception&) { }
    if(pData->bTable)
    {
        Reference<XPropertySet> xProp;
        aValue >>= xProp;
        ::rtl::OUString sPwd, sUser;
        sal_Bool bPwdReq = sal_False;

        if (!xProp.is())
        {
            OSL_ENSURE(sal_False, "SbaTableQueryBrowser::OnExpandEntry: could not retrieve the data source object!");
            return 0;	// indicates an error
        }

        try
        {
            xProp->getPropertyValue(PROPERTY_PASSWORD) >>= sPwd;
            bPwdReq = cppu::any2bool(xProp->getPropertyValue(PROPERTY_ISPASSWORDREQUIRED));
            xProp->getPropertyValue(PROPERTY_USER) >>= sUser;
        }
        catch(Exception&)
        {
            DBG_ERROR("SbaTableQueryBrowser::OnExpandEntry: error while retrieving data source properties!");
        }

        SQLExceptionInfo aInfo;
        try
        {
            WaitObject aWaitCursor(getContent());

            Reference<XConnection> xConnection;	 // supports the service sdb::connection
            if(bPwdReq && !sPwd.getLength())
            {	// password required, but empty -> connect using an interaction handler
                Reference<XCompletedConnection> xConnectionCompletion(xProp, UNO_QUERY);
                if (!xConnectionCompletion.is())
                {
                    DBG_ERROR("SbaTableQueryBrowser::OnExpandEntry: missing an interface ... need an error message here!");
                }
                else
                {	// instantiate the default SDB interaction handler
                    Reference< XInteractionHandler > xHandler(m_xMultiServiceFacatory->createInstance(SERVICE_SDB_INTERACTION_HANDLER), UNO_QUERY);
                    if (!xHandler.is())
                        ShowServiceNotAvailableError(getContent(), String(SERVICE_SDB_INTERACTION_HANDLER), sal_True);
                    else
                        xConnection = xConnectionCompletion->connectWithCompletion(xHandler);
                }
            }
            else
            {
                Reference<XDataSource> xDataSource(xProp,UNO_QUERY);
                xConnection = xDataSource->getConnection(sUser, sPwd);
            }

            if(xConnection.is())
            {
                DBTreeListModel::DBTreeListUserData* pFirstData = (DBTreeListModel::DBTreeListUserData*)pFirstParent->GetUserData();
                if(!pFirstData->xObject.is())
                    pFirstData->xObject = xConnection;

                Reference<XTablesSupplier> xTabSup(xConnection,UNO_QUERY);
                if(xTabSup.is())
                {
                    Image aImage(ModuleRes(TABLE_TREE_ICON));
                    populateTree(xTabSup->getTables(),_pParent,aImage);
                }

                Reference<XViewsSupplier> xViewSup(xConnection,UNO_QUERY);
                if(xViewSup.is())
                {
                    Image aImage(ModuleRes(VIEW_TREE_ICON));
                    populateTree(xViewSup->getViews(),_pParent,aImage);
                }
            }
        }
        catch(SQLContext& e) { aInfo = SQLExceptionInfo(e); }
        catch(SQLWarning& e) { aInfo = SQLExceptionInfo(e); }
        catch(SQLException& e) { aInfo = SQLExceptionInfo(e); }
        catch(Exception&) { DBG_ERROR("SbaTableQueryBrowser::OnExpandEntry: could not connect - unknown exception!"); }

        if (aInfo.isValid())
        {
            try
            {
                Sequence< Any > aArgs(1);
                aArgs[0] <<= PropertyValue(PROPERTY_SQLEXCEPTION, 0, aInfo.get(), PropertyState_DIRECT_VALUE);
                Reference< XExecutableDialog > xErrorDialog(
                    m_xMultiServiceFacatory->createInstanceWithArguments(::rtl::OUString::createFromAscii("com.sun.star.sdb.ErrorMessageDialog"), aArgs), UNO_QUERY);
                if (xErrorDialog.is())
                    xErrorDialog->execute();
            }
            catch(Exception&)
            {
                DBG_ERROR("SbaTableQueryBrowser::OnExpandEntry: could not display the error message!");
            }
            return 0L;
                // 0 indicates that an error occured
        }
    }
    else // we have to expand the queries
    {
        Reference<XQueryDefinitionsSupplier> xQuerySup;
        if(aValue >>= xQuerySup)
        {
            Image aImage(ModuleRes(QUERY_TREE_ICON));
            populateTree(xQuerySup->getQueryDefinitions(),_pParent,aImage);
        }
    }

    return 1L;
}

//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::isSelected(SvLBoxEntry* _pEntry) const
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_DBTEXTITEM) : NULL;
    if (pTextItem)
        return static_cast<DSBrowserString*>(pTextItem)->isSelected();
    else
        DBG_ERROR("SbaTableQueryBrowser::isSelected: invalid entry!");
    return sal_False;
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::select(SvLBoxEntry* _pEntry, sal_Bool _bSelect)
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_DBTEXTITEM) : NULL;
    if (pTextItem)
    {
        static_cast<DSBrowserString*>(pTextItem)->Select(_bSelect);
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
IMPL_LINK(SbaTableQueryBrowser, OnSelectEntry, SvLBoxEntry*, _pEntry)
{
    // reinitialize the rowset
    // but first check if it is necessary
    Reference<XPropertySet> xProp(getRowSet(),UNO_QUERY);
    ::rtl::OUString aOldName;
    xProp->getPropertyValue(PROPERTY_COMMAND) >>= aOldName;
    sal_Int32 nOldType;
    xProp->getPropertyValue(PROPERTY_COMMANDTYPE) >>= nOldType;
    Reference<XConnection> xOldConnection;
    xProp->getPropertyValue(PROPERTY_ACTIVECONNECTION) >>= xOldConnection;
    // the name of the table or query
    SvLBoxString* pString = (SvLBoxString*)_pEntry->GetFirstItem(SV_ITEM_ID_DBTEXTITEM);
    ::rtl::OUString aName(pString->GetText().GetBuffer());

    SvLBoxEntry* pTables = m_pTreeModel->GetParent(_pEntry);
    DBTreeListModel::DBTreeListUserData* pData = (DBTreeListModel::DBTreeListUserData*)pTables->GetUserData();
    SvLBoxEntry* pConnection = m_pTreeModel->GetParent(pTables);
    DBTreeListModel::DBTreeListUserData* pConData = (DBTreeListModel::DBTreeListUserData*)pConnection->GetUserData();

    Reference<XConnection> xConnection(pConData->xObject,UNO_QUERY);
    sal_Int32 nCommandType = pData->bTable ? CommandType::TABLE : CommandType::QUERY;

    sal_Bool bRebuild = xOldConnection != xConnection || nOldType != nCommandType || aName != aOldName;

    Reference< ::com::sun::star::form::XLoadable >  xLoadable(getRowSet(),UNO_QUERY);
    bRebuild |= !xLoadable->isLoaded();

    if(bRebuild)
    {
        WaitObject aWaitCursor(getContent());

        // tell the old entry it has been deselected
        selectPath(m_pCurrentlyLoaded, sal_False);
        m_pCurrentlyLoaded = _pEntry;
        // tell the new entry it has been selected
        selectPath(m_pCurrentlyLoaded, sal_True);

        // get the name of the data source currently selected
        ::rtl::OUString sDataSourceName;
        SvLBoxEntry* pEntry = m_pCurrentlyLoaded;
        while (pEntry && (NULL != m_pTreeModel->GetParent(pEntry)))
            pEntry = m_pTreeModel->GetParent(pEntry);
        if (pEntry)
        {
            SvLBoxItem* pTextItem = pEntry->GetFirstItem(SV_ITEM_ID_DBTEXTITEM);
            if (pTextItem)
                sDataSourceName = static_cast<SvLBoxString*>(pTextItem)->GetText();
        }

        // the values allowing the RowSet to re-execute
        xProp->setPropertyValue(PROPERTY_DATASOURCENAME,makeAny(sDataSourceName));
            // set this _before_ setting the connection, else the rowset would rebuild it ...
        xProp->setPropertyValue(PROPERTY_ACTIVECONNECTION,makeAny(xConnection));
        xProp->setPropertyValue(PROPERTY_COMMANDTYPE,makeAny(nCommandType));
        xProp->setPropertyValue(PROPERTY_COMMAND,makeAny(aName));

        // the formatter depends on the data source we're working on, so rebuild it here ...
        initFormatter();

        // switch the grid to design mode while loading
        getContent()->getGridControl()->setDesignMode(sal_True);
        // load the row set
        if (xLoadable->isLoaded())
            // reload does not work if not already loaded
            xLoadable->reload();
        else
            xLoadable->load();

        // initialize the model
        InitializeGridModel(getFormComponent());

        // reload the row set
        // TODO: this is a HACK. At the moment, InitializeGridModel needs the column information of the rowset
        // to create the grid columns. This is simply wrong. In needs to use the colums as supplied by
        // the object (table or query) we're displaying.
        xLoadable->reload();

        FormLoaded(sal_True);
    }
    return 0L;
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementInserted( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    if (Reference< XNameAccess >(_rEvent.Source, UNO_QUERY).get() == m_xDatabaseContext.get())
    {	// a new datasource has been added to the context
        // the name of the new ds
        ::rtl::OUString sNewDS;
        _rEvent.Accessor >>= sNewDS;

        // add new entries to th list box model
        Image a, b, c;	// not interested in  reusing them
        String d, e;
        implAddDatasource(sNewDS, a, d, b, e, c);
    }
    else
        SbaXDataBrowserController::elementInserted(_rEvent);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementRemoved( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    if (Reference< XNameAccess >(_rEvent.Source, UNO_QUERY).get() == m_xDatabaseContext.get())
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
                OSL_ENSURE(m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyLoaded) == pDSLoop, "SbaTableQueryBrowser::elementRemoved: inconsistence (1)!");

                // unload
                unloadForm();

                // remove the entry from the model
                m_pTreeModel->Remove(pDSLoop);
            }
            else
            {
                OSL_ENSURE(m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyLoaded) != pDSLoop, "SbaTableQueryBrowser::elementRemoved: inconsistence (1)!");
                // remove the entry. This should remove all children, too.
                m_pTreeModel->Remove(pDSLoop);
            }
        }
        else
            DBG_ERROR("SbaTableQueryBrowser::elementRemoved: unknown datasource name!");
    }
    else
        SbaXDataBrowserController::elementRemoved(_rEvent);
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::elementReplaced( const ContainerEvent& _rEvent ) throw(RuntimeException)
{
    if (Reference< XNameAccess >(_rEvent.Source, UNO_QUERY).get() == m_xDatabaseContext.get())
    {	// a datasource has been replaced in the context
        DBG_ERROR("SbaTableQueryBrowser::elementReplaced: no support for replaced data sources!");
            // very suspicious: the database context should not allow to replace data source, only to register
            // and revoke them
    }
    else
        SbaXDataBrowserController::elementReplaced(_rEvent);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::closeConnection(SvLBoxEntry* _pDSEntry)
{
    DBG_ASSERT(_pDSEntry, "SbaTableQueryBrowser::closeConnection: invalid entry (NULL)!");
    OSL_ENSHURE(m_pTreeView->getListBox()->GetRootLevelParent(_pDSEntry) == _pDSEntry, "SbaTableQueryBrowser::closeConnection: invalid entry (not top-level)!");

    // if one of the entries of the given DS is displayed currently, unload the form
    if (m_pCurrentlyLoaded && (m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyLoaded) == _pDSEntry))
        unloadForm();

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
            m_pTreeModel->Remove(pRemove);
        }
    }
    // collapse the entry itself
    m_pTreeView->getListBox()->Collapse(_pDSEntry);

    // get the connection
    DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(_pDSEntry->GetUserData());
    // and dispose/reset it
    ::comphelper::disposeComponent(pData->xObject);
    pData->xObject.clear();
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::unloadForm()
{
    if (!m_pCurrentlyLoaded)
        // nothing to do
        return;

    SvLBoxEntry* pDSEntry = m_pTreeView->getListBox()->GetRootLevelParent(m_pCurrentlyLoaded);

    // de-select the path for the currently displayed table/query
    if (m_pCurrentlyLoaded)
        selectPath(m_pCurrentlyLoaded, sal_False);
    m_pCurrentlyLoaded = NULL;

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
        ::comphelper::disposeComponent(xConn);
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "SbaTableQueryBrowser::unloadForm: could not reset the form");
    }
}

// -------------------------------------------------------------------------
void SAL_CALL SbaTableQueryBrowser::initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException)
{
    // first initialize the parent
    SbaXDataBrowserController::initialize( aArguments );

    PropertyValue aValue;
    const Any* pBegin	= aArguments.getConstArray();
    const Any* pEnd		= pBegin + aArguments.getLength();

    m_nDefaultCommandType = -1;
    for(;pBegin != pEnd;++pBegin)
    {
        if((*pBegin >>= aValue) && aValue.Name == PROPERTY_DATASOURCENAME)
            aValue.Value >>= m_sDefaultDataSourceName;
        else if(aValue.Name == PROPERTY_COMMANDTYPE)
            aValue.Value >>= m_nDefaultCommandType;
        else if(aValue.Name == PROPERTY_COMMAND)
            aValue.Value >>= m_sDefaultCommand;
    }

    if(m_sDefaultDataSourceName.getLength() && m_sDefaultCommand.getLength() && m_nDefaultCommandType != -1)
    {
        SvLBoxEntry* pDataSource = m_pTreeView->getListBox()->GetEntryPosByName(m_sDefaultDataSourceName,NULL);
        if(pDataSource)
        {
            m_pTreeView->getListBox()->Expand(pDataSource);
            SvLBoxEntry* pCommandType = NULL;
            if(CommandType::TABLE == m_nDefaultCommandType)
                pCommandType = m_pTreeView->getListBox()->GetModel()->GetEntry(pDataSource,1);
            else if(CommandType::QUERY == m_nDefaultCommandType)
                pCommandType = m_pTreeView->getListBox()->GetModel()->GetEntry(pDataSource,0);
            if(pCommandType)
            {
                // we need to expand the command
                m_pTreeView->getListBox()->Expand(pCommandType);
                SvLBoxEntry* pCommand = m_pTreeView->getListBox()->GetEntryPosByName(m_sDefaultCommand,pCommandType);
                if(pCommand)
                   m_pTreeView->getListBox()->Select(pCommand);
            }
        }
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
    if (!getContent())
        return;

    m_pTreeView->Hide();
    m_pSplitter->Hide();
    getContent()->Resize();

    InvalidateFeature(ID_BROWSER_EXPLORER);
}

// -------------------------------------------------------------------------
void SbaTableQueryBrowser::showExplorer()
{
    if (haveExplorer())
        return;

    if (!getContent())
        return;

    m_pTreeView->Show();
    m_pSplitter->Show();
    getContent()->Resize();

    InvalidateFeature(ID_BROWSER_EXPLORER);
}

// .........................................................................
}	// namespace dbaui
// .........................................................................


