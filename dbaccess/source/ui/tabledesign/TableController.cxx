/*************************************************************************
 *
 *  $RCSfile: TableController.cxx,v $
 *
 *  $Revision: 1.25 $
 *
 *  last change: $Author: oj $ $Date: 2001-04-11 11:34:35 $
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
#ifndef DBUI_TABLECONTROLLER_HXX
#include "TableController.hxx"
#endif

#ifndef _DBAU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _SFXSIDS_HRC
#include <sfx2/sfxsids.hrc>
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _SV_TOOLBOX_HXX 
#include <vcl/toolbox.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"		   
#endif
#ifndef _COMPHELPER_TYPES_HXX_ 
#include <comphelper/types.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBAUI_DLGSAVE_HXX
#include "dlgsave.hxx"
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_ 
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_ 
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_ 
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_KEYTYPE_HPP_
#include <com/sun/star/sdbcx/KeyType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_ 
#include <com/sun/star/sdbcx/XDrop.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XALTERTABLE_HPP_
#include <com/sun/star/sdbcx/XAlterTable.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLWARNING_HPP_
#include <com/sun/star/sdbc/SQLWarning.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XINDEXESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XIndexesSupplier.hpp>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COM_SUN_STAR_UI_XEXECUTABLEDIALOG_HPP_ 
#include <com/sun/star/ui/XExecutableDialog.hpp>
#endif
#ifndef _COMPHELPER_STREAMSECTION_HXX_
#include <comphelper/streamsection.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef DBAUI_TABLEDESIGNVIEW_HXX
#include "TableDesignView.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef DBAUI_TABLEROW_HXX
#include "TableRow.hxx"
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif
#ifndef DBAUI_TABLEEDITORCONTROL_HXX
#include "TEditControl.hxx"
#endif
#ifndef DBAUI_TABLEDESCRIPTIONWINDOW_HXX
#include "TableDescWin.hxx"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _SV_MSGBOX_HXX 
#include <vcl/msgbox.hxx>
#endif
#ifndef _DBAUI_INDEXDIALOG_HXX_
#include "indexdialog.hxx"
#endif

extern "C" void SAL_CALL createRegistryInfo_OTableControl()
{
    static ::dbaui::OMultiInstanceAutoRegistration< ::dbaui::OTableController > aAutoRegistration;
}


using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::ui;
using namespace ::dbtools;
using namespace ::dbaui;
using namespace ::comphelper;

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OTableController::getImplementationName() throw( RuntimeException )
{
    return getImplementationName_Static();
}

//------------------------------------------------------------------------------
::rtl::OUString OTableController::getImplementationName_Static() throw( RuntimeException )
{
    return ::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.OTableDesign");
}
//------------------------------------------------------------------------------
Sequence< ::rtl::OUString> OTableController::getSupportedServiceNames_Static(void) throw( RuntimeException )
{
    Sequence< ::rtl::OUString> aSupported(1);
    aSupported.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.sdb.TableDesign");
    return aSupported;
}
//-------------------------------------------------------------------------
Sequence< ::rtl::OUString> SAL_CALL OTableController::getSupportedServiceNames() throw(RuntimeException)
{
    return getSupportedServiceNames_Static();
}
// -------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OTableController::Create(const Reference<XMultiServiceFactory >& _rxFactory)
{
    return *(new OTableController(_rxFactory));
}
// -----------------------------------------------------------------------------
OTableController::OTableController(const Reference< XMultiServiceFactory >& _rM) : OGenericUnoController(_rM)
    ,m_bEditable(sal_True)
    ,m_bModified(sal_False)
    ,m_bOwnConnection(sal_False)
    ,m_sTypeNames(ModuleRes(STR_TABLEDESIGN_DBFIELDTYPES))
    ,m_bNew(sal_True)
{
    InvalidateAll();
}
// -----------------------------------------------------------------------------
OTableController::~OTableController()
{
    OTypeInfoMap::iterator aIter = m_aTypeInfo.begin();
    for(;aIter != m_aTypeInfo.end();++aIter)
        delete aIter->second;

    m_aTypeInfo.clear();
}

// -----------------------------------------------------------------------------
void OTableController::startTableListening()
{
    Reference< XComponent >  xComponent(m_xTable, UNO_QUERY);
    if (xComponent.is())
        xComponent->addEventListener(static_cast<XPropertyChangeListener*>(this));
}

// -----------------------------------------------------------------------------
void OTableController::stopTableListening()
{
    Reference< XComponent >  xComponent(m_xTable, UNO_QUERY);
    if (xComponent.is())
        xComponent->removeEventListener(static_cast<XPropertyChangeListener*>(this));
}

// -----------------------------------------------------------------------------
void OTableController::startConnectionListening()
{
    // we have to remove ourself before dispoing the connection
    Reference< XComponent >  xComponent(m_xConnection, UNO_QUERY);
    if (xComponent.is())
        xComponent->addEventListener(static_cast<XPropertyChangeListener*>(this));
}

// -----------------------------------------------------------------------------
void OTableController::stopConnectionListening()
{
    // we have to remove ourself before dispoing the connection
    Reference< XComponent >  xComponent(m_xConnection, UNO_QUERY);
    if (xComponent.is())
        xComponent->removeEventListener(static_cast<XPropertyChangeListener*>(this));
}

// -----------------------------------------------------------------------------
void OTableController::disposing()
{
    OGenericUnoController::disposing();

    delete m_pView;
    m_pView		= NULL;
    
    stopConnectionListening();
    if(m_bOwnConnection)
        ::comphelper::disposeComponent(m_xConnection);
    m_xConnection = NULL;

    ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
    for(;aIter != m_vRowList.end();++aIter)
        delete *aIter;
}
// -----------------------------------------------------------------------------
FeatureState OTableController::GetState(sal_uInt16 _nId)
{
    FeatureState aReturn;
        // (disabled automatically)

    switch (_nId)
    {
        case ID_TABLE_DESIGN_NO_CONNECTION:
            aReturn.aState = ::cppu::bool2any(m_xConnection.is());
            break;
        case ID_BROWSER_EDITDOC:
            aReturn.aState = ::cppu::bool2any(m_bEditable);
            aReturn.bEnabled = m_bNew || m_bEditable || isAddAllowed() || isDropAllowed() || isAlterAllowed();
            break;
        case ID_BROWSER_SAVEASDOC:
            aReturn.bEnabled = m_xConnection.is();
            break;
        case ID_BROWSER_SAVEDOC:
            aReturn.bEnabled = m_bModified;
            break;
        case ID_BROWSER_CUT:
            aReturn.bEnabled = m_bEditable && static_cast<OTableDesignView*>(getView())->isCutAllowed();
            break;
        case ID_BROWSER_COPY:
            aReturn.bEnabled = sal_True;
            break;
        case ID_BROWSER_PASTE:
            aReturn.bEnabled = m_bEditable;
            break;
        case ID_BROWSER_UNDO:
            aReturn.bEnabled = m_bEditable && m_aUndoManager.GetUndoActionCount() != 0;
            break;
        case ID_BROWSER_REDO:
            aReturn.bEnabled = m_bEditable && m_aUndoManager.GetRedoActionCount() != 0;
            break;
        case SID_INDEXDESIGN:
            aReturn.bEnabled =
                (	(	(m_bNew || m_bModified)
                    ||	Reference< XIndexesSupplier >(m_xTable, UNO_QUERY).is()
                    )
                &&	m_xConnection.is()
                );
                // for a new table, assume that we can edit indexes
            break;
    }
    return aReturn;
}
// -----------------------------------------------------------------------------
void OTableController::Execute(sal_uInt16 _nId)
{
    switch(_nId)
    {
        case ID_TABLE_DESIGN_NO_CONNECTION:
            if(!m_xConnection.is())
                createNewConnection(sal_False); // ask the user for a new connection
            break;
        case ID_BROWSER_EDITDOC:
            m_bEditable = !m_bEditable;
            static_cast<OTableDesignView*>(getView())->setReadOnly(!m_bEditable);
            InvalidateFeature(ID_BROWSER_PASTE);
            InvalidateFeature(ID_BROWSER_CLEAR_QUERY);
            break;
        case ID_BROWSER_SAVEASDOC:
            doSaveDoc(sal_True);
            break;
        case ID_BROWSER_SAVEDOC:
            doSaveDoc(sal_False);
            break;
        case ID_BROWSER_CUT:
            static_cast<OTableDesignView*>(getView())->cut();
            break;
        case ID_BROWSER_COPY:
            static_cast<OTableDesignView*>(getView())->copy();
            break;
        case ID_BROWSER_PASTE:
            static_cast<OTableDesignView*>(getView())->paste();
            break;
        case ID_BROWSER_UNDO:
            m_aUndoManager.Undo();
            InvalidateFeature(ID_BROWSER_REDO);
            break;
        case ID_BROWSER_REDO:
            m_aUndoManager.Redo();
            InvalidateFeature(ID_BROWSER_UNDO);
            break;
        case SID_INDEXDESIGN:
            doEditIndexes();
            break;
    }
    InvalidateFeature(_nId);
}

// -----------------------------------------------------------------------------
sal_Bool OTableController::doSaveDoc(sal_Bool _bSaveAs)
{
    if(!m_xConnection.is())
        createNewConnection(sal_True); // ask the user for a new connection
    Reference<XTablesSupplier> xTablesSup(m_xConnection,UNO_QUERY);

    if (!xTablesSup.is())
    {
        String aMessage(ModuleRes(STR_TABLEDESIGN_CONNECTION_MISSING));
        String sTitle(ModuleRes(STR_STAT_WARNING));
        OSQLMessageBox aMsg(getView(),sTitle,aMessage);
        aMsg.Execute();
        return sal_False;
    }

    Reference<XNameAccess> xTables;
    ::rtl::OUString sCatalog, sSchema;

    sal_Bool bNew = (0 == m_sName.getLength());
    bNew = bNew || m_bNew || _bSaveAs;

    try
    {
        xTables = xTablesSup->getTables();
        OSL_ENSURE(xTables.is(),"The queries can't be null!");

        // first we need a name for our query so ask the user
        if(bNew)
        {
            String aDefaultName;
            if (_bSaveAs && !bNew)
                 aDefaultName = String(m_sName);
            else
            {
                String aName = String(ModuleRes(STR_TBL_TITLE));
                aName = aName.GetToken(0,' ');
                aDefaultName = String(::dbtools::createUniqueName(xTables,aName));
            }
            
            OSaveAsDlg aDlg(getView(),CommandType::TABLE,xTables,m_xConnection->getMetaData(),aDefaultName);
            if(aDlg.Execute() == RET_OK)
            {
                m_sName = aDlg.getName();
                sCatalog = aDlg.getCatalog();
                sSchema	 = aDlg.getSchema();
            }
        }

        // did we get a name
        if(!m_sName.getLength())
            return sal_False;
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "OTableController::doSaveDoc: nothing is expected to happen here!");
    }

    SQLExceptionInfo aInfo;
    try
    {
        // check the columns for double names
        checkColumns(bNew || !xTables->hasByName(m_sName));

        Reference<XPropertySet> xTable;
        if(bNew || !xTables->hasByName(m_sName)) // just to make sure the table already exists
        {
            if(xTables->hasByName(m_sName))
            {
                Reference<XDrop> xNameCont(xTable,UNO_QUERY);
                xNameCont->dropByName(m_sName);
            }

            Reference<XDataDescriptorFactory> xFact(xTables,UNO_QUERY);
            OSL_ENSURE(xFact.is(),"OTableController::doSaveDoc: No XDataDescriptorFactory available!");
            xTable = xFact->createDataDescriptor();
            OSL_ENSURE(xTable.is(),"OTableController::doSaveDoc: Create query failed!");
            // to set the name is only allowed when the wuery is new
            xTable->setPropertyValue(PROPERTY_CATALOGNAME,makeAny(sCatalog));
            xTable->setPropertyValue(PROPERTY_SCHEMANAME,makeAny(sSchema));
            xTable->setPropertyValue(PROPERTY_NAME,makeAny(m_sName));

            // now append the columns
            Reference<XColumnsSupplier> xColSup(xTable,UNO_QUERY);
            appendColumns(xColSup);
            // now append the primary key
            Reference<XKeysSupplier> xKeySup(xTable,UNO_QUERY);
            appendKey(xKeySup);
        }
//				else
//				{
//					xTables->getByName(m_sName) >>= xTable;
//				}
        // now set the properties
        if(bNew)
        {
            Reference<XAppend> xAppend(xTables,UNO_QUERY);
            OSL_ENSURE(xAppend.is(),"OTableController::doSaveDoc: No XAppend Interface!");
            xAppend->appendByDescriptor(xTable);

            assignTable();
            if(!m_xTable.is()) // correct name and try again
            {	
                // it can be that someone inserted new data for us
                ::rtl::OUString sCatalog,sSchema,sTable,sComposedName;
                xTable->getPropertyValue(PROPERTY_CATALOGNAME)	>>= sCatalog;
                xTable->getPropertyValue(PROPERTY_SCHEMANAME)	>>= sSchema;
                xTable->getPropertyValue(PROPERTY_NAME)			>>= sTable;

                ::dbtools::composeTableName(m_xConnection->getMetaData(),sCatalog,sSchema,sTable,sComposedName,sal_False);
                m_sName = sComposedName;
                assignTable();									
            }
        }
        else if(m_xTable.is())
        {
            alterColumns();
        }
        reSyncRows();
    }
    catch(SQLContext& e) 
    { 
        m_sName = ::rtl::OUString();
        stopTableListening();
        m_xTable = NULL;
        aInfo = SQLExceptionInfo(e); 
    }
    catch(SQLWarning& e)
    { 
        m_sName = ::rtl::OUString();
        stopTableListening();
        m_xTable = NULL;
        aInfo = SQLExceptionInfo(e); 
    }
    catch(SQLException& e)
    { 
        m_sName = ::rtl::OUString();
        stopTableListening();
        m_xTable = NULL;
        aInfo = SQLExceptionInfo(e); 
    }
    catch(Exception&)
    {
        m_sName = ::rtl::OUString();
        stopTableListening();
        m_xTable = NULL;
        OSL_ENSURE(sal_False, "OTableController::doSaveDoc: table could not be inserted (caught a generic exception)!");
        return sal_False;
    }

    showError(aInfo);
    return !aInfo.isValid();
}

// -----------------------------------------------------------------------------
void OTableController::doEditIndexes()
{
    // table needs to be saved before editing indexes
    if (m_bNew || m_bModified)
    {
        QueryBox aAsk(getView(), ModuleRes(QUERY_SAVE_TABLE_EDIT_INDEXES));
        if (RET_YES != aAsk.Execute())
            return;

        if (!doSaveDoc(sal_False))
            return;

        OSL_ENSURE(!m_bNew && !m_bModified, "OTableController::doEditIndexes: what the hell did doSaveDoc do?");
    }

    Reference< XNameAccess > xIndexes;			// will be the keys of the table
    Sequence< ::rtl::OUString > aFieldNames;	// will be the column names of the table
    try
    {
        // get the keys
        Reference< XIndexesSupplier > xIndexesSupp(m_xTable, UNO_QUERY);
        if (xIndexesSupp.is())
        {
            xIndexes = xIndexesSupp->getIndexes();
            OSL_ENSURE(xIndexes.is(), "OTableController::doEditIndexes: no keys got from the indexes supplier!");
        }
        else
            OSL_ENSURE(sal_False, "OTableController::doEditIndexes: should never have reached this (no indexes supplier)!");

        // get the field names
        Reference< XColumnsSupplier > xColSupp(m_xTable, UNO_QUERY);
        OSL_ENSURE(xColSupp.is(), "OTableController::doEditIndexes: no columns supplier!");
        if (xColSupp.is())
        {
            Reference< XNameAccess > xCols = xColSupp->getColumns();
            OSL_ENSURE(xCols.is(), "OTableController::doEditIndexes: no columns!");
            if (xCols.is())
                aFieldNames = xCols->getElementNames();
        }
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "OTableController::doEditIndexes: caught an exception while retrieving the indexes/columns!");
    }

    if (!xIndexes.is())
        return;

    DbaIndexDialog aDialog(getView(), aFieldNames, xIndexes, getORB(),m_xConnection.is() ? m_xConnection->getMetaData()->getMaxColumnsInIndex() : sal_Int32(0));
    if (RET_OK != aDialog.Execute())
        return;

}

// -----------------------------------------------------------------------------
void SAL_CALL OTableController::initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException)
{
    try
    {
        OGenericUnoController::initialize(aArguments);

        PropertyValue aValue;
        const Any* pBegin	= aArguments.getConstArray();
        const Any* pEnd		= pBegin + aArguments.getLength();

        for(;pBegin != pEnd;++pBegin)
        {
            if((*pBegin >>= aValue) && aValue.Name == PROPERTY_ACTIVECONNECTION)
            {
                aValue.Value >>= m_xConnection;
                OSL_ENSURE(m_xConnection.is(),"We need at least a connection!");
                // get notified if connection is in disposing
                startConnectionListening();
            }
            else if(aValue.Name == PROPERTY_DATASOURCENAME)
            {
                aValue.Value >>= m_sDataSourceName;
            }
            else if(aValue.Name == PROPERTY_CURRENTTABLE)
            {
                aValue.Value >>= m_sName;
            }
        }

        if (!m_xConnection.is())
        {	// whoever instantiated us did not give us a connection to share. Okay, create an own one
            createNewConnection(sal_False);
        }
        if(!m_xConnection.is()) // so what should otherwise
        {
            {
                String aMessage(ModuleRes(RID_STR_CONNECTION_LOST));
                ODataView* pWindow = getView();
                InfoBox(pWindow, aMessage).Execute();
            }
        }

        assignTable();
        if(!m_xFormatter.is())
        {
            Reference< XChild> xChild(m_xConnection,UNO_QUERY);
            if(xChild.is())
            {
                Reference< XPropertySet> xProp(xChild->getParent(),UNO_QUERY);
                if(xProp.is())
                {
                    Reference< XNumberFormatsSupplier> xSupplier;
                    xProp->getPropertyValue(PROPERTY_NUMBERFORMATSSUPPLIER) >>= xSupplier;
                    if(xSupplier.is())
                    {
                        m_xFormatter = Reference< ::com::sun::star::util::XNumberFormatter >(getORB()
                            ->createInstance(::rtl::OUString::createFromAscii("com.sun.star.util.NumberFormatter")), UNO_QUERY);
                        m_xFormatter->attachNumberFormatsSupplier(xSupplier);
                    }
                }
            }
            OSL_ENSURE(m_xFormatter.is(),"No NumberFormatter!");
        }
        fillTypeInfo();				// fill the needed type information
        loadData();					// fill the column information form the table
        getView()->initialize();	// show the windows and fill with our informations
        getUndoMgr()->Clear();		// clear all undo redo things
        setModified(sal_False);		// and we are not modified yet
        // set the title of the beamer
        Reference<XPropertySet> xProp(m_xCurrentFrame,UNO_QUERY);
        if(xProp.is() && xProp->getPropertySetInfo()->hasPropertyByName(PROPERTY_TITLE))
        {
            ::rtl::OUString sName = String(ModuleRes(STR_TABLEDESIGN_TITLE));
            sName += ::rtl::OUString::createFromAscii(" ");
            sName += m_sDataSourceName;
            xProp->setPropertyValue(PROPERTY_TITLE,makeAny(sName));
        }
    }
    catch(SQLException&)
    {
        OSL_ENSURE(sal_False, "OTableController::initialize: caught an exception!");
    }
}
// -----------------------------------------------------------------------------
sal_Bool OTableController::Construct(Window* pParent)
{
    m_pView = new OTableDesignView(pParent,m_xMultiServiceFacatory,this);
    OGenericUnoController::Construct(pParent);
    m_pView->Construct(NULL);
    m_pView->Show();
    return sal_True;
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableController::propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt)
{
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableController::elementInserted(const ::com::sun::star::container::ContainerEvent& Event) throw( RuntimeException )
{
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableController::elementRemoved(const ::com::sun::star::container::ContainerEvent& Event) throw( RuntimeException )
{
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableController::elementReplaced(const ::com::sun::star::container::ContainerEvent& Event) throw( RuntimeException )
{
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OTableController::suspend(sal_Bool _bSuspend) throw( RuntimeException )
{
    if(isModified())
    {
        QueryBox aQry(getView(), ModuleRes(TABLE_DESIGN_SAVEMODIFIED));
        switch (aQry.Execute())
        {
            case RET_YES:
                Execute(ID_BROWSER_SAVEDOC);
                if(isModified())
                    return sal_False; // when we save the table this must be false else some press cancel
                break;
            case RET_CANCEL:
                return sal_False;
            default:
                break;
        }
    }
    return sal_True;
}
// -----------------------------------------------------------------------------
void OTableController::AddSupportedFeatures()
{
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DBSlots/Redo")] = ID_BROWSER_REDO;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DBSlots/Save")] = ID_BROWSER_SAVEDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DBSlots/Undo")] = ID_BROWSER_UNDO;

    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:BrowserMode")] = SID_BROWSER_MODE;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:HelpMenu")]	= SID_HELPMENU;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:NewDoc")]		= SID_NEWDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:SaveAsDoc")]	= SID_SAVEASDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:ExplorerContentOpen")]			= SID_EXPLORERCONTENT_OPEN;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:ExplorerContentOpenDocument")]	= SID_EXPLORERCONTENT_OPEN_DOCUMENT;

}
// -----------------------------------------------------------------------------
ToolBox* OTableController::CreateToolBox(Window* _pParent)
{
    return new ToolBox(_pParent, ModuleRes(RID_BRW_TABLEDESIGN_TOOLBOX));
}
// -----------------------------------------------------------------------------
SfxUndoManager* OTableController::getUndoMgr()
{
    return &m_aUndoManager;
}
// -----------------------------------------------------------------------------
void OTableController::setModified(sal_Bool _bModified)
{
    m_bModified = _bModified;
    InvalidateFeature(ID_BROWSER_SAVEDOC);
    InvalidateFeature(ID_BROWSER_SAVEASDOC);
    InvalidateFeature(SID_INDEXDESIGN);
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableController::disposing( const EventObject& Source ) throw(RuntimeException)
{
    if (m_xConnection.is() && Reference<XConnection>(Source.Source,UNO_QUERY) == m_xConnection)
    {
        // our connection was disposed so we need a new one
        createNewConnection(sal_True);
        // remove from the table
        Reference< XComponent >  xComponent(m_xTable, UNO_QUERY);
        if (xComponent.is())
        {
            Reference<XEventListener> xEvtL((::cppu::OWeakObject*)this,UNO_QUERY);
            xComponent->removeEventListener(xEvtL);
        }
        stopTableListening();
        m_xTable	= NULL;
        assignTable();
        if(!m_xTable.is())
        {
            m_bNew		= sal_True;
            setModified(sal_True);
        }
        InvalidateAll();
    }
    else if(Reference<XPropertySet>(Source.Source,UNO_QUERY) == m_xTable)
    {	// some deleted our table so we have a new one
        stopTableListening();
        m_xTable	= NULL;
        m_bNew		= sal_True;
        setModified(sal_True);
    }
}
// -----------------------------------------------------------------------------
void OTableController::Save(const Reference< XObjectOutputStream>& _rxOut)
{
    OStreamSection aSection(_rxOut.get());

}
// -----------------------------------------------------------------------------
void OTableController::Load(const Reference< XObjectInputStream>& _rxIn)
{
    OStreamSection aSection(_rxIn.get());
}
// -----------------------------------------------------------------------------
void OTableController::createNewConnection(sal_Bool _bUI)
{
    stopConnectionListening();
    m_xConnection		= NULL;
    m_bOwnConnection	= sal_False;

    if (!_bUI || (RET_YES == QueryBox(getView(),ModuleRes(TABLE_QUERY_CONNECTION_LOST)).Execute()))
    {
        m_xConnection = connect(m_sDataSourceName);
        startConnectionListening();
        m_bOwnConnection = m_xConnection.is();
    }
    ToolBox* pToolBox = getView()->getToolBox();
    if(pToolBox)
    {
        if(m_xConnection.is())
        {
            pToolBox->RemoveItem(pToolBox->GetItemPos(ID_TABLE_DESIGN_NO_CONNECTION)-1);
            pToolBox->HideItem(ID_TABLE_DESIGN_NO_CONNECTION);
        }
        else if(!pToolBox->IsItemVisible(ID_TABLE_DESIGN_NO_CONNECTION))
        {

            pToolBox->InsertSeparator(pToolBox->GetItemPos(ID_TABLE_DESIGN_NO_CONNECTION));
            pToolBox->ShowItem(ID_TABLE_DESIGN_NO_CONNECTION);
        }
    }
}
// -----------------------------------------------------------------------------
void OTableController::fillTypeInfo()
{
    if(!getConnection().is())
        return;
    Reference< XResultSet> xRs = getConnection()->getMetaData ()->getTypeInfo ();
    Reference< XRow> xRow(xRs,UNO_QUERY);
    // Information for a single SQL type
    
    ::rtl::OUString aB1 = ::rtl::OUString::createFromAscii(" [ ");
    ::rtl::OUString aB2 = ::rtl::OUString::createFromAscii(" ]");
    // Loop on the result set until we reach end of file
    while (xRs->next()) 
    {
        OTypeInfo* pInfo = new OTypeInfo();
        pInfo->aTypeName		= xRow->getString (1);
        pInfo->nType			= xRow->getShort (2);
        pInfo->nPrecision		= xRow->getInt (3);
        pInfo->aLiteralPrefix	= xRow->getString (4);
        pInfo->aLiteralSuffix	= xRow->getString (5);
        pInfo->aCreateParams	= xRow->getString (6);
        pInfo->bNullable		= xRow->getInt (7) == ColumnValue::NULLABLE;
        pInfo->bCaseSensitive	= xRow->getBoolean (8);
        pInfo->nSearchType		= xRow->getShort (9);
        pInfo->bUnsigned		= xRow->getBoolean (10);
        pInfo->bCurrency		= xRow->getBoolean (11);
        pInfo->bAutoIncrement	= xRow->getBoolean (12);
        pInfo->aLocalTypeName	= xRow->getString (13);
        pInfo->nMinimumScale	= xRow->getShort (14);
        pInfo->nMaximumScale	= xRow->getShort (15);
        pInfo->nNumPrecRadix	= xRow->getInt (18);
        
        String aName;
        switch(pInfo->nType)
        {
            case DataType::CHAR:
                aName = m_sTypeNames.GetToken(TYPE_CHAR);
                break;
            case DataType::VARCHAR:
                aName = m_sTypeNames.GetToken(TYPE_TEXT);
                break;
            case DataType::DECIMAL:
                aName = m_sTypeNames.GetToken(TYPE_DECIMAL);
                break;
            case DataType::NUMERIC:
                aName = m_sTypeNames.GetToken(TYPE_NUMERIC);
                break;
            case DataType::BIGINT:
                aName = m_sTypeNames.GetToken(TYPE_BIGINT);
                break;
            case DataType::FLOAT:
                aName = m_sTypeNames.GetToken(TYPE_FLOAT);
                break;
            case DataType::DOUBLE:
                aName = m_sTypeNames.GetToken(TYPE_DOUBLE);
                break;
            case DataType::LONGVARCHAR:
                aName = m_sTypeNames.GetToken(TYPE_MEMO);
                break;
            case DataType::LONGVARBINARY:
                aName = m_sTypeNames.GetToken(TYPE_IMAGE);
                break;
            case DataType::DATE:
                aName = m_sTypeNames.GetToken(TYPE_DATE);
                break;
            case DataType::TIME:
                aName = m_sTypeNames.GetToken(TYPE_TIME);
                break;
            case DataType::TIMESTAMP:
                aName = m_sTypeNames.GetToken(TYPE_DATETIME);
                break;
            case DataType::BIT:
                aName = m_sTypeNames.GetToken(TYPE_BOOL);
                break;
            case DataType::TINYINT:
                aName = m_sTypeNames.GetToken(TYPE_TINYINT);
                break;
            case DataType::SMALLINT:
                aName = m_sTypeNames.GetToken(TYPE_SMALLINT);
                break;
            case DataType::INTEGER:
                aName = m_sTypeNames.GetToken(TYPE_INTEGER);
                break;
            case DataType::REAL:
                aName = m_sTypeNames.GetToken(TYPE_REAL);
                break;
            case DataType::BINARY:
                aName = m_sTypeNames.GetToken(TYPE_BINARY);
                break;
            case DataType::VARBINARY:
                aName = m_sTypeNames.GetToken(TYPE_VARBINARY);
                break;
            case DataType::SQLNULL:
                aName = m_sTypeNames.GetToken(TYPE_SQLNULL);
                break;
            case DataType::OBJECT:
                aName = m_sTypeNames.GetToken(TYPE_OBJECT);
                break;
            case DataType::DISTINCT:
                aName = m_sTypeNames.GetToken(TYPE_DISTINCT);
                break;
            case DataType::STRUCT:
                aName = m_sTypeNames.GetToken(TYPE_STRUCT);
                break;
            case DataType::ARRAY:
                aName = m_sTypeNames.GetToken(TYPE_ARRAY);
                break;
            case DataType::BLOB:
                aName = m_sTypeNames.GetToken(TYPE_BLOB);
                break;
            case DataType::CLOB:
                aName = m_sTypeNames.GetToken(TYPE_CLOB);
                break;
            case DataType::REF:
                aName = m_sTypeNames.GetToken(TYPE_REF);
                break;
            case DataType::OTHER:
                aName = m_sTypeNames.GetToken(TYPE_OTHER);
                break;
            default:
                OSL_ENSURE(0,"Unknown type");
        }
        pInfo->aUIName = aName.GetBuffer();
        pInfo->aUIName += aB1;
        pInfo->aUIName += pInfo->aTypeName;
        pInfo->aUIName += aB2;
        // Now that we have the type info, save it in the multimap 
        m_aTypeInfo.insert(OTypeInfoMap::value_type(pInfo->nType,pInfo));
    }
    // for a faster index access
    OTypeInfoMap::iterator aIter = m_aTypeInfo.begin();
    for(;aIter != m_aTypeInfo.end();++aIter)
        m_aTypeInfoIndex.push_back(aIter);

    // Close the result set/statement.

    ::comphelper::disposeComponent(xRs);
}
// -----------------------------------------------------------------------------
const OTypeInfo* OTableController::getTypeInfoByType(sal_Int32 _nDataType) const 
{ 
    OTypeInfoMap::const_iterator aIter = m_aTypeInfo.find(_nDataType);
    if(aIter != m_aTypeInfo.end())
        return aIter->second; 
    OSL_ENSURE(0,"Wrong DataType supplied!");
    return NULL;
}
// -----------------------------------------------------------------------------
void OTableController::appendColumns(Reference<XColumnsSupplier>& _rxColSup,sal_Bool _bKeyColumns)
{
    try
    {
        // now append the columns
        OSL_ENSURE(_rxColSup.is(),"No columns supplier");
        if(!_rxColSup.is())
            return;
        Reference<XNameAccess> xColumns = _rxColSup->getColumns();
        OSL_ENSURE(xColumns.is(),"No columns");
        Reference<XDataDescriptorFactory> xColumnFactory(xColumns,UNO_QUERY);

        Reference<XAppend> xAppend(xColumns,UNO_QUERY);
        OSL_ENSURE(xAppend.is(),"No XAppend Interface!");

        ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
        for(;aIter != m_vRowList.end();++aIter)
        {
            OSL_ENSURE(*aIter,"OTableRow is null!");
            OFieldDescription* pField = (*aIter)->GetActFieldDescr();
            if(!pField)
                continue;
            
            Reference<XPropertySet> xColumn;
            if(pField->IsPrimaryKey() || !_bKeyColumns)
                xColumn = xColumnFactory->createDataDescriptor();
            if(xColumn.is())
            {
                if(!_bKeyColumns)
                    setColumnProperties(xColumn,pField);
                else
                    xColumn->setPropertyValue(PROPERTY_NAME,makeAny(pField->GetName()));

                xAppend->appendByDescriptor(xColumn);
                xColumn = NULL;
                // now only the settings are missing
                if(xColumns->hasByName(pField->GetName()))
                {
                    xColumns->getByName(pField->GetName()) >>= xColumn;
                    if(xColumn.is())
                    {
                        if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                            xColumn->setPropertyValue(PROPERTY_FORMATKEY,makeAny(pField->GetFormatKey()));
                        if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                            xColumn->setPropertyValue(PROPERTY_ALIGN,makeAny((sal_Int32)pField->GetHorJustify()));
                    }
                }
                else
                {
                    OSL_ENSURE(sal_False, "OTableController::appendColumns: invalid field name!");
                }
                
            }
        }
    }
    catch(SQLException& e)
    {
        showError(SQLExceptionInfo(e));
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "OTableController::appendColumns: caught an exception!");
    }
}
// -----------------------------------------------------------------------------
void OTableController::appendKey(Reference<XKeysSupplier>& _rxSup)
{
    if(!_rxSup.is())
        return; // the database doesn't support keys
    try
    {
        OSL_ENSURE(_rxSup.is(),"No XKeysSupplier!");
        Reference<XDataDescriptorFactory> xKeyFactory(_rxSup->getKeys(),UNO_QUERY);
        OSL_ENSURE(xKeyFactory.is(),"No XDataDescriptorFactory Interface!");
        Reference<XAppend> xAppend(xKeyFactory,UNO_QUERY);
        OSL_ENSURE(xAppend.is(),"No XAppend Interface!");

        Reference<XPropertySet> xKey = xKeyFactory->createDataDescriptor();
        OSL_ENSURE(xKey.is(),"Key is null!");
        xKey->setPropertyValue(PROPERTY_TYPE,makeAny(KeyType::PRIMARY));

        Reference<XColumnsSupplier> xColSup(xKey,UNO_QUERY);
        if(xColSup.is())
        {
            appendColumns(xColSup,sal_True);
            Reference<XNameAccess> xColumns = xColSup->getColumns();
            if(xColumns->getElementNames().getLength())
                xAppend->appendByDescriptor(xKey);
        }
        
    }
    catch(SQLException& e)
    {
        showError(SQLExceptionInfo(e));
    }
    catch(Exception&)
    {
        OSL_ENSURE(sal_False, "OTableController::appendKey: caught an exception!");
    }
}
// -----------------------------------------------------------------------------
void OTableController::loadData()
{
    //////////////////////////////////////////////////////////////////////
    // Wenn Datenstruktur bereits vorhanden, Struktur leeren
    ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
    for(;aIter != m_vRowList.begin();++aIter)
        delete *aIter;
    m_vRowList.clear();

    OTableRow* pTabEdRow = NULL;
    Reference< XDatabaseMetaData> xMetaData = getConnection().is() ? getConnection()->getMetaData() : Reference< XDatabaseMetaData>();
    //////////////////////////////////////////////////////////////////////
    // Datenstruktur mit Daten aus DatenDefinitionsObjekt fuellen
    if(m_xTable.is() && xMetaData.is())
    {
        Reference<XColumnsSupplier> xColSup(m_xTable,UNO_QUERY);
        OSL_ENSURE(xColSup.is(),"No XColumnsSupplier!");
        Reference<XNameAccess> xColumns = xColSup->getColumns();
        OFieldDescription* pActFieldDescr = NULL;
        String aType;
        //////////////////////////////////////////////////////////////////////
        // ReadOnly-Flag
        // Bei Drop darf keine Zeile editierbar sein.
        // Bei Add duerfen nur die leeren Zeilen editierbar sein.
        // Bei Add und Drop koennen alle Zeilen editiert werden.
        //	sal_Bool bReadOldRow = xMetaData->supportsAlterTableWithAddColumn() && xMetaData->supportsAlterTableWithDropColumn();
        sal_Bool bIsAlterAllowed = isAlterAllowed();
        Sequence< ::rtl::OUString> aColumns = xColumns->getElementNames();
        const ::rtl::OUString* pBegin	= aColumns.getConstArray();
        const ::rtl::OUString* pEnd		= pBegin + aColumns.getLength();

        for(;pBegin != pEnd;++pBegin)
        {
            Reference<XPropertySet> xColumn;
            xColumns->getByName(*pBegin) >>= xColumn;
            sal_Int32 nType			= 0;
            sal_Int32 nScale		= 0;
            sal_Int32 nPrecision	= 0;
            sal_Int32 nNullable		= 0;
            sal_Int32 nFormatKey	= 0;
            sal_Int32 nAlign		= 0;

            sal_Bool bIsAutoIncrement,bIsCurrency;
            ::rtl::OUString sName,sDefaultValue,sDescription,sTypeName;

            // get the properties from the column
            xColumn->getPropertyValue(PROPERTY_NAME)			>>= sName;
            xColumn->getPropertyValue(PROPERTY_TYPENAME)		>>= sTypeName;
            xColumn->getPropertyValue(PROPERTY_ISNULLABLE)		>>= nNullable;
            bIsAutoIncrement	= ::cppu::any2bool(xColumn->getPropertyValue(PROPERTY_ISAUTOINCREMENT));
            bIsCurrency			= ::cppu::any2bool(xColumn->getPropertyValue(PROPERTY_ISCURRENCY));
            xColumn->getPropertyValue(PROPERTY_TYPE)			>>= nType;
            xColumn->getPropertyValue(PROPERTY_SCALE)			>>= nScale;
            xColumn->getPropertyValue(PROPERTY_PRECISION)		>>= nPrecision;


            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
                xColumn->getPropertyValue(PROPERTY_DESCRIPTION)	>>= sDescription;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
                xColumn->getPropertyValue(PROPERTY_DEFAULTVALUE)>>= sDefaultValue;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                xColumn->getPropertyValue(PROPERTY_FORMATKEY)	>>= nFormatKey;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                xColumn->getPropertyValue(PROPERTY_ALIGN)		>>= nAlign;


            pTabEdRow = new OTableRow();
            pTabEdRow->SetReadOnly(!bIsAlterAllowed);
            // search for type
            ::std::pair<OTypeInfoMap::iterator, OTypeInfoMap::iterator> aPair = m_aTypeInfo.equal_range(nType);
            OTypeInfoMap::iterator aIter = aPair.first;
            if(aIter == m_aTypeInfo.end())
                continue;
            for(;aIter != aPair.second;++aIter)
            {
                // search the best matching type
                if(	aIter->second->aTypeName == sTypeName	&& 
                    aIter->second->nPrecision >= nPrecision && 
                    aIter->second->nMaximumScale >= nScale)
                    break;
            }

            pTabEdRow->SetFieldType( aIter->second );
            pActFieldDescr = pTabEdRow->GetActFieldDescr();
            pActFieldDescr->SetName(sName);
            pActFieldDescr->SetFormatKey(nFormatKey);
            //	pActFieldDescr->SetPrimaryKey(pPrimary->GetValue());
            pActFieldDescr->SetDescription(sDescription);
            pActFieldDescr->SetAutoIncrement(bIsAutoIncrement);
            pActFieldDescr->SetHorJustify((SvxCellHorJustify)nAlign);
            pActFieldDescr->SetCurrency(bIsCurrency);

            //////////////////////////////////////////////////////////////////////
            // Spezielle Daten
            pActFieldDescr->SetIsNullable(nNullable);
            pActFieldDescr->SetDefaultValue(sDefaultValue);
            pActFieldDescr->SetPrecision(nPrecision);
            pActFieldDescr->SetScale(nScale);
            
            m_vRowList.push_back( pTabEdRow);
        }
        // fill the primary  key information
        Reference<XNameAccess> xKeyColumns	= getKeyColumns();
        if(xKeyColumns.is())
        {
            Sequence< ::rtl::OUString> aKeyColumns = xKeyColumns->getElementNames();
            const ::rtl::OUString* pKeyBegin	= aKeyColumns.getConstArray();
            const ::rtl::OUString* pKeyEnd		= pKeyBegin + aKeyColumns.getLength();

            for(;pKeyBegin != pKeyEnd;++pKeyBegin)
            {
                ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
                for(;aIter != m_vRowList.end();++aIter)
                {
                    if((*aIter)->GetActFieldDescr()->GetName() == *pKeyBegin)
                    {
                        (*aIter)->SetPrimaryKey(sal_True);
                        break;
                    }
                }
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////
    // Leere Zeilen fuellen

    OTypeInfoMap::iterator aTypeIter = m_aTypeInfo.find(DataType::VARCHAR);
    if(aTypeIter == m_aTypeInfo.end())
        aTypeIter = m_aTypeInfo.begin();

    OSL_ENSURE(aTypeIter != m_aTypeInfo.end(),"We have no type infomation!");

    sal_Bool bReadRow = !isAddAllowed();
    for(sal_Int32 i=m_vRowList.size(); i<128; i++ )
    {
        pTabEdRow = new OTableRow();
        pTabEdRow->SetReadOnly(bReadRow);
        m_vRowList.push_back( pTabEdRow);
    }
}
// -----------------------------------------------------------------------------
Reference<XNameAccess> OTableController::getKeyColumns() const
{
    // use keys and indexes for excat postioning
    // first the keys
    Reference<XKeysSupplier> xKeySup(m_xTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    Reference<XColumnsSupplier> xKeyColsSup;
    Reference<XNameAccess> xKeyColumns;
    if(xKeys.is())
    {
        Reference<XPropertySet> xProp;
        for(sal_Int32 i=0;i< xKeys->getCount();++i)
        {
            xKeys->getByIndex(i) >>= xProp;
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(KeyType::PRIMARY == nKeyType)
            {
                xKeyColsSup = Reference<XColumnsSupplier>(xProp,UNO_QUERY);
                OSL_ENSURE(xKeyColsSup.is(),"Columnsupplier is null!");
                xKeyColumns = xKeyColsSup->getColumns();
                break;
            }
        }
    }

    return xKeyColumns;
}
// -----------------------------------------------------------------------------
void OTableController::checkColumns(sal_Bool _bNew) throw(::com::sun::star::sdbc::SQLException)
{
    sal_Bool bFoundPKey = sal_False;
    Reference< XDatabaseMetaData> xMetaData = m_xConnection.is() ? m_xConnection->getMetaData() : Reference< XDatabaseMetaData>();

    ::comphelper::UStringMixEqual bCase(xMetaData.is() ? xMetaData->storesMixedCaseQuotedIdentifiers() : sal_True);
    ::std::vector<OTableRow*>::const_iterator aIter = m_vRowList.begin();
    for(;aIter != m_vRowList.end();++aIter)
    {
        OFieldDescription* pFieldDesc = (*aIter)->GetActFieldDescr();
        if (pFieldDesc && pFieldDesc->GetName().getLength())
        {
            bFoundPKey |=  (*aIter)->IsPrimaryKey();
            sal_uInt16 nErrorRes = sal_uInt16(-1);
            sal_uInt16 nFieldPos = sal_uInt16(-1);
            // first check for duplicate names
            ::std::vector<OTableRow*>::const_iterator aIter2 = aIter+1;
            for(;aIter2 != m_vRowList.end();++aIter2)
            {
                OFieldDescription* pCompareDesc = (*aIter2)->GetActFieldDescr();
                if (pCompareDesc && bCase(pCompareDesc->GetName(),pFieldDesc->GetName()))
                {
                    String strMessage = String(ModuleRes(STR_TABLEDESIGN_DUPLICATE_NAME));
                    strMessage.SearchAndReplaceAscii("$column$", pFieldDesc->GetName());
                    throw SQLException(strMessage,*this,::rtl::OUString::createFromAscii("HY0000"),1000,Any());
                }
            }
        }
    }
    if(!bFoundPKey)
    {
        if(_bNew && xMetaData.is() && xMetaData->supportsCoreSQLGrammar())
        {
            String sTitle(ModuleRes(STR_TABLEDESIGN_NO_PRIM_KEY_HEAD));
            String sMsg(ModuleRes(STR_TABLEDESIGN_NO_PRIM_KEY));
            OSQLMessageBox aBox(getView(), sTitle,sMsg, WB_YES_NO_CANCEL | WB_DEF_YES);

            INT16 nReturn = aBox.Execute();

            if (nReturn == RET_YES)
            {
                OTableRow* pNewRow = new OTableRow();
                const OTypeInfo* pTypeInfo = NULL;
                // first we search for a type which supports autoIncrement
                OTypeInfoMap::const_iterator aIter = m_aTypeInfo.begin();
                for(;aIter != m_aTypeInfo.end();++aIter)
                {
                    if(aIter->second->bAutoIncrement)
                    {	// therefor we have searched 
                        pTypeInfo = aIter->second;
                        break;
                    }
                    else if(aIter->second->nType == DataType::INTEGER)
                        pTypeInfo = aIter->second; // alternative
                }
                if(!pTypeInfo) // just a fallback
                    pTypeInfo = getTypeInfoByType(DataType::VARCHAR);

                pNewRow->SetFieldType( pTypeInfo );
                OFieldDescription* pActFieldDescr = pNewRow->GetActFieldDescr();

                pActFieldDescr->SetAutoIncrement(pTypeInfo->bAutoIncrement);
                pActFieldDescr->SetIsNullable(ColumnValue::NO_NULLS);


                pActFieldDescr->SetName( createUniqueName(::rtl::OUString::createFromAscii("ID") ));
                pActFieldDescr->SetPrimaryKey( sal_True );
                m_vRowList.insert(m_vRowList.begin(),pNewRow);

                static_cast<OTableDesignView*>(getView())->GetEditorCtrl()->DisplayData(0);
            }
        }
    }
}
// -----------------------------------------------------------------------------
void OTableController::alterColumns()
{
    Reference<XColumnsSupplier> xColSup(m_xTable,UNO_QUERY);
    OSL_ENSURE(xColSup.is(),"What happen here?!");

    Reference<XNameAccess> xColumns = xColSup->getColumns();
    OSL_ENSURE(xColumns.is(),"No columns");
    Reference<XAlterTable> xAlter(m_xTable,UNO_QUERY);	// can be null

    sal_Int32 nColumnCount = xColumns->getElementNames().getLength();
    Reference<XDrop> xDrop(xColumns,UNO_QUERY);			// can be null
    Reference<XAppend> xAppend(xColumns,UNO_QUERY);		// can be null
    Reference<XDataDescriptorFactory> xColumnFactory(xColumns,UNO_QUERY); // can be null

    sal_Bool bReload = sal_False; // refresh the data

    // contains all columns names which are already handled those which are not in the list will be deleted
    Reference< XDatabaseMetaData> xMetaData = m_xConnection.is() ? m_xConnection->getMetaData() : Reference< XDatabaseMetaData>();

    ::std::map< ::rtl::OUString,sal_Bool,::comphelper::UStringMixLess> aColumns(xMetaData.is() ? xMetaData->storesMixedCaseQuotedIdentifiers() : sal_True);
    ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
    for(sal_Int32 nPos = 0;aIter != m_vRowList.end();++aIter,++nPos)
    {
        OSL_ENSURE(*aIter,"OTableRow is null!");
        OFieldDescription* pField = (*aIter)->GetActFieldDescr();
        if(!pField)
            continue;
        
        Reference<XPropertySet> xColumn;
        if(xColumns->hasByName(pField->GetName()))
        {
            aColumns[pField->GetName()] = sal_True;
            xColumns->getByName(pField->GetName()) >>= xColumn;
            OSL_ENSURE(xColumn.is(),"Column is null!");
            
            sal_Int32 nType,nPrecision,nScale,nNullable,nFormatKey=0,nAlignment=0;
            sal_Bool bAutoIncrement;
            ::rtl::OUString sDescription,sDefaultValue;

            xColumn->getPropertyValue(PROPERTY_TYPE)			>>= nType;
            xColumn->getPropertyValue(PROPERTY_PRECISION)		>>= nPrecision;
            xColumn->getPropertyValue(PROPERTY_SCALE)			>>= nScale;
            xColumn->getPropertyValue(PROPERTY_ISNULLABLE)		>>= nNullable;
            bAutoIncrement = ::cppu::any2bool(xColumn->getPropertyValue(PROPERTY_ISAUTOINCREMENT));
            //	xColumn->getPropertyValue(PROPERTY_ISCURRENCY,::cppu::bool2any(pField->IsCurrency()));
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
                xColumn->getPropertyValue(PROPERTY_DESCRIPTION) >>= sDescription;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
                xColumn->getPropertyValue(PROPERTY_DEFAULTVALUE) >>= sDefaultValue;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                xColumn->getPropertyValue(PROPERTY_FORMATKEY)	>>= nFormatKey;
            if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                xColumn->getPropertyValue(PROPERTY_ALIGN)		>>= nAlignment;

            // check if something changed
            if((nType != pField->GetType()					|| 
                nPrecision != pField->GetPrecision()		|| 
                nScale != pField->GetScale()				|| 
                nNullable != pField->GetIsNullable()		|| 
                bAutoIncrement != pField->IsAutoIncrement() || 
                sDescription != pField->GetDescription()	|| 
                sDefaultValue != pField->GetDefaultValue()) && 
                xColumnFactory.is())
            {
                Reference<XPropertySet> xNewColumn;
                xNewColumn = xColumnFactory->createDataDescriptor();
                setColumnProperties(xNewColumn,pField);
                // first try to alter the column
                sal_Bool bNotOk = sal_False;
                try
                {
                    // first try if we can alter the column
                    if(xAlter.is())
                        xAlter->alterColumnByName(pField->GetName(),xNewColumn);
                }
                catch(SQLException&)
                {
                    bNotOk = sal_True;
                }
                // if something went wrong or the can't alter columns
                // drop and append a new one
                if((!xAlter.is() || bNotOk) && xDrop.is() && xAppend.is())
                {
                    xDrop->dropByName(pField->GetName());
                    xAppend->appendByDescriptor(xNewColumn);
                }
                // exceptions are catched outside
                xNewColumn = NULL;
                xColumns->getByName(pField->GetName()) >>= xColumn;
                bReload = sal_True;
            }
            
            if(nFormatKey != pField->GetFormatKey())
            {
                if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                    xColumn->setPropertyValue(PROPERTY_FORMATKEY,makeAny(pField->GetFormatKey()));
            }
            if(nAlignment != (sal_Int32)pField->GetHorJustify())
            {
                if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                    xColumn->setPropertyValue(PROPERTY_ALIGN,makeAny(nAlignment));
            }
        }
        else if(xColumnFactory.is() && xAppend.is())
        {// column not found by its name so we assume it is new
            // Column is new
            xColumn = xColumnFactory->createDataDescriptor();
            setColumnProperties(xColumn,pField);
            xAppend->appendByDescriptor(xColumn);
            if(xColumns->hasByName(pField->GetName()))
            {	// ask for the append by name
                aColumns[pField->GetName()] = sal_True;
                xColumns->getByName(pField->GetName()) >>= xColumn;
                if(xColumn.is())
                {
                    if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                        xColumn->setPropertyValue(PROPERTY_FORMATKEY,makeAny(pField->GetFormatKey()));
                    if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                        xColumn->setPropertyValue(PROPERTY_ALIGN,makeAny((sal_Int32)pField->GetHorJustify()));
                }
            }
            else
            {
                OSL_ENSURE(sal_False, "OTableController::alterColumns: invalid column!");
            }
        }
        else if(xColumnFactory.is() && xAlter.is() && nPos < nColumnCount)
        { // we can't find the column nor can we append a new one so we alter it by index
            Reference<XPropertySet> xNewColumn;
            xNewColumn = xColumnFactory->createDataDescriptor();
            setColumnProperties(xNewColumn,pField);
            xAlter->alterColumnByIndex(nPos,xNewColumn);
            if(xColumns->hasByName(pField->GetName()))
            {	// ask for the append by name
                aColumns[pField->GetName()] = sal_True;
                xColumns->getByName(pField->GetName()) >>= xColumn;
                if(xColumn.is())
                {
                    if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
                        xColumn->setPropertyValue(PROPERTY_FORMATKEY,makeAny(pField->GetFormatKey()));
                    if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
                        xColumn->setPropertyValue(PROPERTY_ALIGN,makeAny((sal_Int32)pField->GetHorJustify()));
                }
            }
            else
            {
                OSL_ENSURE(sal_False, "OTableController::alterColumns: invalid column (2)!");
            }
        }
        else
            bReload = sal_True;
    }

    Reference<XNameAccess> xKeyColumns	= getKeyColumns();
    // now we have to look for the columns who where deleted
    if(xDrop.is())
    {
        Sequence< ::rtl::OUString> aColumnNames = xColumns->getElementNames();
        const ::rtl::OUString* pBegin = aColumnNames.getConstArray();
        const ::rtl::OUString* pEnd = pBegin + aColumnNames.getLength();
        for(;pBegin != pEnd;++pBegin)
        {
            if(aColumns.find(*pBegin) == aColumns.end()) // found a column to delete
            {
                if(xKeyColumns.is() && xKeyColumns->hasByName(*pBegin)) // check if this column is a memeber of the primary key
                {
                    String aMsgT(ModuleRes(STR_TBL_COLUMN_IS_KEYCOLUMN));
                    aMsgT.SearchAndReplace(String::CreateFromAscii("\"$column$\""),*pBegin);
                    String aTitle(ModuleRes(STR_TBL_COLUMN_IS_KEYCOLUMN_TITLE));
                    OSQLMessageBox aMsg(getView(),aTitle,aMsgT,WB_YES_NO| WB_DEF_YES);
                    if(aMsg.Execute() == RET_YES)
                    {
                        xKeyColumns = NULL;
                        dropKey();
                    }
                    else
                    {
                        bReload = sal_True;
                        continue;
                    }
                }
                Reference<XDrop> xDrop(xColumns,UNO_QUERY);
                xDrop->dropByName(*pBegin);
            }
        }
    }
    // check if we have to do something with the primary key
    if(xKeyColumns.is())
    {
        aIter = m_vRowList.begin();
        for(;aIter != m_vRowList.end();++aIter)
        {
            OSL_ENSURE(*aIter,"OTableRow is null!");
            OFieldDescription* pField = (*aIter)->GetActFieldDescr();
            if(!pField)
                continue;
            if(pField->IsPrimaryKey() && !xKeyColumns->hasByName(pField->GetName()))
            {
                dropKey();
                Reference<XKeysSupplier> xKeySup(m_xTable,UNO_QUERY);
                appendKey(xKeySup);
                break;
            }
        }
    }
    else
    {
        Reference<XKeysSupplier> xKeySup(m_xTable,UNO_QUERY);
        appendKey(xKeySup);
    }

    reSyncRows();

    if(bReload)
    {
        loadData();					// fill the column information form the table
        static_cast<OTableDesignView*>(getView())->reSync();	// show the windows and fill with our informations
        getUndoMgr()->Clear();		// clear all undo redo things
        setModified(sal_False);		// and we are not modified yet
    }
}
// -----------------------------------------------------------------------------
void OTableController::setColumnProperties(const Reference<XPropertySet>& _rxColumn,const OFieldDescription* _pFieldDesc)
{
    _rxColumn->setPropertyValue(PROPERTY_NAME,makeAny(_pFieldDesc->GetName()));
    _rxColumn->setPropertyValue(PROPERTY_TYPE,makeAny(_pFieldDesc->GetType()));
    _rxColumn->setPropertyValue(PROPERTY_TYPENAME,makeAny(_pFieldDesc->getTypeInfo()->aTypeName));
    _rxColumn->setPropertyValue(PROPERTY_PRECISION,makeAny(_pFieldDesc->GetPrecision()));
    _rxColumn->setPropertyValue(PROPERTY_SCALE,makeAny(_pFieldDesc->GetScale()));
    _rxColumn->setPropertyValue(PROPERTY_ISNULLABLE, makeAny(_pFieldDesc->GetIsNullable()));
    _rxColumn->setPropertyValue(PROPERTY_ISAUTOINCREMENT,::cppu::bool2any(_pFieldDesc->IsAutoIncrement()));
    //	_rxColumn->setPropertyValue(PROPERTY_ISCURRENCY,::cppu::bool2any(_pFieldDesc->IsCurrency()));
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
        _rxColumn->setPropertyValue(PROPERTY_DESCRIPTION,makeAny(_pFieldDesc->GetDescription()));
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
        _rxColumn->setPropertyValue(PROPERTY_DEFAULTVALUE,makeAny(_pFieldDesc->GetDefaultValue()));
}
// -----------------------------------------------------------------------------
void OTableController::dropKey()
{
    Reference<XKeysSupplier> xKeySup(m_xTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    if(xKeys.is())
    {
        Reference<XPropertySet> xProp;
        for(sal_Int32 i=0;i< xKeys->getCount();++i)
        {
            xKeys->getByIndex(i) >>= xProp;
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(KeyType::PRIMARY == nKeyType)
            {
                Reference<XDrop> xDrop(xKeys,UNO_QUERY);
                xDrop->dropByIndex(i); // delete the key
                break;
            }
        }
    }
}
// -----------------------------------------------------------------------------
void OTableController::assignTable() 
{
    // get the table
    if(m_sName.getLength())
    {
        Reference<XNameAccess> xNameAccess;
        Reference<XTablesSupplier> xSup(m_xConnection,UNO_QUERY);
        if(xSup.is())
        {
            xNameAccess = xSup->getTables();
            OSL_ENSURE(xNameAccess.is(),"no nameaccess for the queries!");

            Reference<XPropertySet> xProp;
            if(xNameAccess->hasByName(m_sName) && ::cppu::extractInterface(xProp,xNameAccess->getByName(m_sName)) && xProp.is()) 
            {
                m_xTable = xProp;
                startTableListening();

                // check if we set the table editable
                Reference<XAlterTable> xAlter(m_xTable,UNO_QUERY);
                m_bEditable = isAlterAllowed() || isDropAllowed() || isAddAllowed();
                if(!m_bEditable)
                {
                    ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
                    for(; aIter != m_vRowList.end(); ++aIter)
                        (*aIter)->SetReadOnly(sal_True);
                }
                m_bNew = sal_False;
                // be notified when the table is in disposing
                InvalidateAll();
            }
        }
    }
}
// -----------------------------------------------------------------------------
sal_Bool OTableController::isAddAllowed() const
{
    Reference<XColumnsSupplier> xColsSup(m_xTable,UNO_QUERY);
    sal_Bool bAddAllowed = !m_xTable.is();
    if(xColsSup.is())
        bAddAllowed = Reference<XAppend>(xColsSup->getColumns(),UNO_QUERY).is();

    Reference< XDatabaseMetaData> xMetaData = m_xConnection.is() ? m_xConnection->getMetaData() : Reference< XDatabaseMetaData >();
    bAddAllowed = bAddAllowed || ( xMetaData.is() && xMetaData->supportsAlterTableWithAddColumn());

    return bAddAllowed;
}
// -----------------------------------------------------------------------------
sal_Bool OTableController::isDropAllowed() const
{
    Reference<XColumnsSupplier> xColsSup(m_xTable,UNO_QUERY);
    sal_Bool bDropAllowed = !m_xTable.is();
    if(xColsSup.is())
        bDropAllowed = Reference<XDrop>(xColsSup->getColumns(),UNO_QUERY).is();

    Reference< XDatabaseMetaData> xMetaData = m_xConnection.is() ? m_xConnection->getMetaData() : Reference< XDatabaseMetaData >();
    bDropAllowed = bDropAllowed || ( xMetaData.is() && xMetaData->supportsAlterTableWithDropColumn());

    return bDropAllowed;
}
// -----------------------------------------------------------------------------
sal_Bool OTableController::isAlterAllowed() const
{
    sal_Bool bAllowed(!m_xTable.is() || Reference<XAlterTable>(m_xTable,UNO_QUERY).is());
    return bAllowed;
}
// -----------------------------------------------------------------------------
void OTableController::reSyncRows()
{
    sal_Bool bAlterAllowed	= isAlterAllowed();
    sal_Bool bAddAllowed	= isAddAllowed();
    ::std::vector<OTableRow*>::iterator aIter = m_vRowList.begin();
    for(;aIter != m_vRowList.end();++aIter)
    {
        OSL_ENSURE(*aIter,"OTableRow is null!");
        OFieldDescription* pField = (*aIter)->GetActFieldDescr();
        if(pField)
            (*aIter)->SetReadOnly(!bAlterAllowed);
        else
            (*aIter)->SetReadOnly(!bAddAllowed);
            
    }
    static_cast<OTableDesignView*>(getView())->reSync();	// show the windows and fill with our informations

    getUndoMgr()->Clear();		// clear all undo redo things
    setModified(sal_False);		// and we are not modified yet
}
// -----------------------------------------------------------------------------
::rtl::OUString OTableController::createUniqueName(const ::rtl::OUString& _rName)
{
    ::rtl::OUString sName = _rName;
    Reference< XDatabaseMetaData> xMetaData = m_xConnection.is() ? m_xConnection->getMetaData() : Reference< XDatabaseMetaData>();

    ::comphelper::UStringMixEqual bCase(xMetaData.is() ? xMetaData->storesMixedCaseQuotedIdentifiers() : sal_True);

    ::std::vector<OTableRow*>::const_iterator aIter = m_vRowList.begin();
    for(sal_Int32 i=0;aIter != m_vRowList.end();++aIter)
    {
        OFieldDescription* pFieldDesc = (*aIter)->GetActFieldDescr();
        if (pFieldDesc && pFieldDesc->GetName().getLength() && bCase(sName,pFieldDesc->GetName()))
        { // found a second name of _rName so we need another
            sName = _rName + ::rtl::OUString::valueOf(++i);
            aIter = m_vRowList.begin(); // and retry
        }
    }
    return sName;
}
// -----------------------------------------------------------------------------





