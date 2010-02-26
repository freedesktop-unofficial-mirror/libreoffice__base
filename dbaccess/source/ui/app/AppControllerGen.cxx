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
#include "precompiled_dbaccess.hxx"

#include "AppController.hxx"
#include "AppDetailView.hxx"
#include "AppView.hxx"
#include "dbaccess_slotid.hrc"
#include "dbu_app.hrc"
#include "dbustrings.hrc"
#include "defaultobjectnamecheck.hxx"
#include "dlgsave.hxx"
#include "UITools.hxx"
#include "subcomponentmanager.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/container/XChild.hpp>
#include <com/sun/star/container/XContainer.hpp>
#include <com/sun/star/container/XHierarchicalNameContainer.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/lang/XEventListener.hpp>
#include <com/sun/star/sdb/CommandType.hpp>
#include <com/sun/star/sdb/SQLContext.hpp>
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#include <com/sun/star/sdbcx/XRename.hpp>
#include <com/sun/star/sdb/ErrorCondition.hpp>
#include <com/sun/star/sdb/application/DatabaseObject.hpp>
#include <com/sun/star/sdb/SQLContext.hpp>
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
#include <com/sun/star/ucb/Command.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#include <com/sun/star/uno/XNamingService.hpp>
#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/util/XRefreshable.hpp>
#include <com/sun/star/lang/XEventListener.hpp>
/** === end UNO includes === **/

#include <cppuhelper/exc_hlp.hxx>
#include <connectivity/dbexception.hxx>
#include <connectivity/dbtools.hxx>
#include <connectivity/sqlerror.hxx>
#include <connectivity/dbexception.hxx>
#include <sfx2/mailmodelapi.hxx>
#include <svx/dbaexchange.hxx>
#include <toolkit/unohlp.hxx>
#include <tools/diagnose_ex.h>
#include <tools/urlobj.hxx>
#include <unotools/bootstrap.hxx>
#include <vcl/mnemonic.hxx>
#include <vcl/svapp.hxx>
#include <vcl/waitobj.hxx>
#include <vos/mutex.hxx>

//........................................................................
namespace dbaui
{
using namespace ::dbtools;
using namespace ::connectivity;
using namespace ::svx;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::ucb;

/** === begin UNO using === **/
using ::com::sun::star::util::XCloseable;
using ::com::sun::star::ui::XContextMenuInterceptor;
/** === end UNO using === **/
namespace DatabaseObject = ::com::sun::star::sdb::application::DatabaseObject;
namespace ErrorCondition = ::com::sun::star::sdb::ErrorCondition;

//........................................................................
// -----------------------------------------------------------------------------

class CloseChecker : public ::cppu::WeakImplHelper1< com::sun::star::lang::XEventListener >
{
    bool    m_bClosed;

public:
    CloseChecker()
        :m_bClosed( false )
    {
    }

    virtual ~CloseChecker()
    {
    }

    bool isClosed()
    {
        return true;
    }

    // interface XEventListener
    virtual void SAL_CALL disposing( const EventObject& /*Source*/ ) throw( RuntimeException )
    {
        m_bClosed = true;
    }

};
// -----------------------------------------------------------------------------
void OApplicationController::convertToView(const ::rtl::OUString& _sName)
{
    try
    {
        SharedConnection xConnection( getConnection() );
        Reference< XQueriesSupplier > xSup( xConnection, UNO_QUERY_THROW );
        Reference< XNameAccess > xQueries( xSup->getQueries(), UNO_QUERY_THROW );
        Reference< XPropertySet > xSourceObject( xQueries->getByName( _sName ), UNO_QUERY_THROW );

        Reference< XTablesSupplier > xTablesSup( xConnection, UNO_QUERY_THROW );
        Reference< XNameAccess > xTables( xTablesSup->getTables(), UNO_QUERY_THROW );

        Reference< XDatabaseMetaData  > xMeta = xConnection->getMetaData();

        String aName = String(ModuleRes(STR_TBL_TITLE));
        aName = aName.GetToken(0,' ');
        String aDefaultName = ::dbaui::createDefaultName(xMeta,xTables,aName);

        DynamicTableOrQueryNameCheck aNameChecker( xConnection, CommandType::TABLE );
        OSaveAsDlg aDlg( getView(), CommandType::TABLE, getORB(), xConnection, aDefaultName, aNameChecker );
        if ( aDlg.Execute() == RET_OK )
        {
            ::rtl::OUString sName = aDlg.getName();
            ::rtl::OUString sCatalog = aDlg.getCatalog();
            ::rtl::OUString sSchema	 = aDlg.getSchema();
            ::rtl::OUString sNewName(
                ::dbtools::composeTableName( xMeta, sCatalog, sSchema, sName, sal_False, ::dbtools::eInTableDefinitions ) );
            Reference<XPropertySet> xView = ::dbaui::createView(sNewName,xConnection,xSourceObject);
            if ( !xView.is() )
                throw SQLException(String(ModuleRes(STR_NO_TABLE_FORMAT_INSIDE)),*this,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("S1000")) ,0,Any());
            getContainer()->elementAdded(E_TABLE,sNewName,makeAny(xView));
        }
    }
    catch(const SQLException& )
    {
        showError( SQLExceptionInfo( ::cppu::getCaughtException() ) );
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::pasteFormat(sal_uInt32 _nFormatId)
{
    if ( _nFormatId )
    {
        try
        {
            const TransferableDataHelper& rClipboard = getViewClipboard();
            ElementType eType = getContainer()->getElementType();
            if ( eType == E_TABLE )
            {
                m_aTableCopyHelper.pasteTable( _nFormatId, rClipboard, getDatabaseName(), ensureConnection() );
            }
            else
                paste( eType, ODataAccessObjectTransferable::extractObjectDescriptor( rClipboard ) );

        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::openDataSourceAdminDialog()
{
    openDialog( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.sdb.DatasourceAdministrationDialog" ) ) );
}

// -----------------------------------------------------------------------------
void OApplicationController::openDialog( const ::rtl::OUString& _sServiceName )
{
    try
    {
        ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard( getMutex() );
        WaitObject aWO(getView());

        Sequence< Any > aArgs(3);
        sal_Int32 nArgPos = 0;

        Reference< ::com::sun::star::awt::XWindow> xWindow = getTopMostContainerWindow();
        if ( !xWindow.is() )
        {
            DBG_ASSERT( getContainer(), "OApplicationController::Construct: have no view!" );
            if ( getContainer() )
                xWindow = VCLUnoHelper::GetInterface(getView()->Window::GetParent());
        }
        // the parent window
        aArgs[nArgPos++] <<= PropertyValue( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParentWindow")),
                                    0,
                                    makeAny(xWindow),
                                    PropertyState_DIRECT_VALUE);

        // the initial selection
        ::rtl::OUString sInitialSelection;
        if ( getContainer() )
            sInitialSelection = getDatabaseName();
        if ( sInitialSelection.getLength() )
        {
            aArgs[ nArgPos++ ] <<= PropertyValue(
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "InitialSelection" ) ), 0,
                makeAny( sInitialSelection ), PropertyState_DIRECT_VALUE );
        }

        SharedConnection xConnection( getConnection() );
        if ( xConnection.is() )
        {
            aArgs[ nArgPos++ ] <<= PropertyValue(
                PROPERTY_ACTIVE_CONNECTION, 0,
                makeAny( xConnection ), PropertyState_DIRECT_VALUE );
        }
        aArgs.realloc( nArgPos );

        // create the dialog
        Reference< XExecutableDialog > xAdminDialog;
        xAdminDialog = Reference< XExecutableDialog >(
            getORB()->createInstanceWithArguments(_sServiceName,aArgs), UNO_QUERY);

        // execute it
        if (xAdminDialog.is())
            xAdminDialog->execute();
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::openTableFilterDialog()
{
    openDialog( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.sdb.TableFilterDialog" ) ) );
}

// -----------------------------------------------------------------------------
void OApplicationController::refreshTables()
{
    if ( getContainer() && getContainer()->getDetailView() )
    {
        WaitObject aWO(getView());
        OSL_ENSURE(getContainer()->getElementType() == E_TABLE,"Only allowed when the tables container is selected!");
        try
        {
            Reference<XRefreshable> xRefresh(getElements(E_TABLE),UNO_QUERY);
            if ( xRefresh.is() )
                xRefresh->refresh();
        }
        catch(const Exception&)
        {
            OSL_ENSURE(0,"Could not refresh tables!");
        }

        getContainer()->getDetailView()->clearPages(sal_False);
        getContainer()->getDetailView()->createTablesPage( ensureConnection() );
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::openDirectSQLDialog()
{
    openDialog( SERVICE_SDB_DIRECTSQLDIALOG );
}
// -----------------------------------------------------------------------------
void SAL_CALL OApplicationController::propertyChange( const PropertyChangeEvent& evt ) throw (RuntimeException)
{
    ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( getMutex() );
    if ( evt.PropertyName == PROPERTY_USER )
    {
        m_bNeedToReconnect = sal_True;
        InvalidateFeature(SID_DB_APP_STATUS_USERNAME);
    }
    else if ( evt.PropertyName == PROPERTY_URL )
    {
        m_bNeedToReconnect = sal_True;
        InvalidateFeature(SID_DB_APP_STATUS_DBNAME);
        InvalidateFeature(SID_DB_APP_STATUS_TYPE);
        InvalidateFeature(SID_DB_APP_STATUS_HOSTNAME);
    }
    else if ( PROPERTY_NAME == evt.PropertyName )
    {
        const ElementType eType = getContainer()->getElementType();
        if ( eType == E_FORM || eType == E_REPORT )
        {
            ::rtl::OUString sOldName,sNewName;
            evt.OldValue >>= sOldName;
            evt.NewValue >>= sNewName;
            Reference<XChild> xChild(evt.Source,UNO_QUERY);
            if ( xChild.is() )
            {
                Reference<XContent> xContent(xChild->getParent(),UNO_QUERY);
                if ( xContent.is() )
                    sOldName = xContent->getIdentifier()->getContentIdentifier() + ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("/")) + sOldName;
            }

            getContainer()->elementReplaced( eType , sOldName, sNewName );
        }
    }

    EventObject aEvt;
    aEvt.Source = m_xModel;
    modified(aEvt);
}

// -----------------------------------------------------------------------------
Reference< XDataSource > SAL_CALL OApplicationController::getDataSource() throw (RuntimeException)
{
    ::osl::MutexGuard aGuard( getMutex() );
    Reference< XDataSource > xDataSource( m_xDataSource, UNO_QUERY );
    return xDataSource;
}

// -----------------------------------------------------------------------------
Reference< XWindow > SAL_CALL OApplicationController::getApplicationMainWindow() throw (RuntimeException)
{
    ::osl::MutexGuard aGuard( getMutex() );
    Reference< XFrame > xFrame( getFrame(), UNO_QUERY_THROW );
    Reference< XWindow > xWindow( xFrame->getContainerWindow(), UNO_QUERY_THROW );
    return xWindow;
}

// -----------------------------------------------------------------------------
Sequence< Reference< XComponent > > SAL_CALL OApplicationController::getSubComponents() throw (RuntimeException)
{
    return m_pSubComponentManager->getSubComponents();
}

// -----------------------------------------------------------------------------
Reference< XConnection > SAL_CALL OApplicationController::getActiveConnection() throw (RuntimeException)
{
    ::osl::MutexGuard aGuard( getMutex() );
    return m_xDataSourceConnection.getTyped();
}

// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OApplicationController::isConnected(  ) throw (RuntimeException)
{
    ::osl::MutexGuard aGuard( getMutex() );
    return m_xDataSourceConnection.is();
}

// -----------------------------------------------------------------------------
void SAL_CALL OApplicationController::connect(  ) throw (SQLException, RuntimeException)
{
    SQLExceptionInfo aError;
    SharedConnection xConnection = ensureConnection( &aError );
    if ( !xConnection.is() )
    {
        if ( aError.isValid() )
            aError.doThrow();

        // no particular error, but nonetheless could not connect -> throw a generic exception
        String sConnectingContext( ModuleRes( STR_COULDNOTCONNECT_DATASOURCE ) );
        sConnectingContext.SearchAndReplaceAscii( "$name$", getStrippedDatabaseName() );
        ::dbtools::throwGenericSQLException( sConnectingContext, *this );
    }
}

// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OApplicationController::closeSubComponents(  ) throw (RuntimeException)
{
    return m_pSubComponentManager->closeSubComponents();
}


// -----------------------------------------------------------------------------
namespace
{
    ElementType lcl_objectType2ElementType( const sal_Int32 _nObjectType )
    {
        ElementType eType( E_NONE );
        switch ( _nObjectType )
        {
        case DatabaseObject::TABLE:  eType = E_TABLE;   break;
        case DatabaseObject::QUERY:  eType = E_QUERY;   break;
        case DatabaseObject::FORM:   eType = E_FORM;    break;
        case DatabaseObject::REPORT: eType = E_REPORT;  break;
        default:
            OSL_ENSURE( false, "lcl_objectType2ElementType: unsupported object type!" );
                // this should have been caught earlier
        }
        return eType;
    }
}

// -----------------------------------------------------------------------------
void OApplicationController::impl_validateObjectTypeAndName_throw( const sal_Int32 _nObjectType, const ::rtl::OUString& _rObjectName )
{
    // ensure we're connected
    if ( !isConnected() )
    {
        SQLError aError( getORB() );
        aError.raiseException( ErrorCondition::DB_NOT_CONNECTED, *this );
    }

    // ensure a proper object type
    if  (   ( _nObjectType != DatabaseObject::TABLE )
        &&  ( _nObjectType != DatabaseObject::QUERY )
        &&  ( _nObjectType != DatabaseObject::FORM )
        &&  ( _nObjectType != DatabaseObject::REPORT )
        )
        throw IllegalArgumentException( ::rtl::OUString(), *this, 1 );

    // ensure an existing object
    Reference< XNameAccess > xContainer( getElements( lcl_objectType2ElementType( _nObjectType ) ) );
    if ( !xContainer.is() )
        // all possible reasons for this (e.g. not being connected currently) should
        // have been handled before
        throw RuntimeException( ::rtl::OUString(), *this );

    bool bExistentObject = false;
    switch ( _nObjectType )
    {
    case DatabaseObject::TABLE:
    case DatabaseObject::QUERY:
        bExistentObject = xContainer->hasByName( _rObjectName );
        break;
    case DatabaseObject::FORM:
    case DatabaseObject::REPORT:
    {
        Reference< XHierarchicalNameAccess > xHierarchy( xContainer, UNO_QUERY_THROW );
        bExistentObject = xHierarchy->hasByHierarchicalName( _rObjectName );
    }
    break;
    }

    if ( !bExistentObject )
        throw NoSuchElementException( _rObjectName, *this );
}

// -----------------------------------------------------------------------------
Reference< XComponent > SAL_CALL OApplicationController::loadComponent( ::sal_Int32 _ObjectType,
    const ::rtl::OUString& _ObjectName, ::sal_Bool _ForEditing ) throw (IllegalArgumentException, NoSuchElementException, SQLException, RuntimeException)
{
    return loadComponentWithArguments( _ObjectType, _ObjectName, _ForEditing, Sequence< PropertyValue >() );
}

// -----------------------------------------------------------------------------
Reference< XComponent > SAL_CALL OApplicationController::loadComponentWithArguments( ::sal_Int32 _ObjectType,
    const ::rtl::OUString& _ObjectName, ::sal_Bool _ForEditing, const Sequence< PropertyValue >& _Arguments ) throw (IllegalArgumentException, NoSuchElementException, SQLException, RuntimeException)
{
    ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( getMutex() );

    impl_validateObjectTypeAndName_throw( _ObjectType, _ObjectName );

    Reference< XComponent > xComponent( openElementWithArguments(
        _ObjectName,
        lcl_objectType2ElementType( _ObjectType ),
        _ForEditing ? E_OPEN_DESIGN : E_OPEN_NORMAL,
        _ForEditing ? SID_DB_APP_EDIT : SID_DB_APP_OPEN,
        ::comphelper::NamedValueCollection( _Arguments )
    ) );

    return xComponent;
}

// -----------------------------------------------------------------------------
void SAL_CALL OApplicationController::registerContextMenuInterceptor( const Reference< XContextMenuInterceptor >& _Interceptor ) throw (RuntimeException)
{
    if ( _Interceptor.is() )
        m_aContextMenuInterceptors.addInterface( _Interceptor );
}

// -----------------------------------------------------------------------------
void SAL_CALL OApplicationController::releaseContextMenuInterceptor( const Reference< XContextMenuInterceptor >& _Interceptor ) throw (RuntimeException)
{
    m_aContextMenuInterceptors.removeInterface( _Interceptor );
}

// -----------------------------------------------------------------------------
void OApplicationController::previewChanged( sal_Int32 _nMode )
{
    ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( getMutex() );

    if ( m_xDataSource.is() && !isDataSourceReadOnly() )
    {
        try
        {
            ::comphelper::NamedValueCollection aLayoutInfo( m_xDataSource->getPropertyValue( PROPERTY_LAYOUTINFORMATION ) );
            sal_Int32 nOldMode = aLayoutInfo.getOrDefault( "Preview", _nMode );
            if ( nOldMode != _nMode )
            {
                aLayoutInfo.put( "Preview", _nMode );
                m_xDataSource->setPropertyValue( PROPERTY_LAYOUTINFORMATION, makeAny( aLayoutInfo.getPropertyValues() ) );
            }
        }
        catch ( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    InvalidateFeature(SID_DB_APP_DISABLE_PREVIEW);
    InvalidateFeature(SID_DB_APP_VIEW_DOCINFO_PREVIEW);
    InvalidateFeature(SID_DB_APP_VIEW_DOC_PREVIEW);
}
// -----------------------------------------------------------------------------
//void OApplicationController::updateTitle()
//{
//	::rtl::OUString sName = getStrippedDatabaseName();
//
//	String sTitle = String(ModuleRes(STR_APP_TITLE));
//	sName = sName + sTitle;
//#ifdef DBG_UTIL
//    ::rtl::OUString aDefault;
//	sName += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" ["));
//    sName += utl::Bootstrap::getBuildIdData( aDefault );
//	sName += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("]"));
//#endif
//}
// -----------------------------------------------------------------------------
void OApplicationController::askToReconnect()
{
    if ( m_bNeedToReconnect )
    {
        m_bNeedToReconnect = sal_False;
        sal_Bool bClear = sal_True;
        if ( !m_pSubComponentManager->empty() )
        {
            QueryBox aQry(getView(), ModuleRes(APP_CLOSEDOCUMENTS));
            switch (aQry.Execute())
            {
                case RET_YES:
                    closeSubComponents();
                    break;
                default:
                    bClear = sal_False;
                    break;
            }
        }
        if ( bClear )
        {
            ElementType eType = getContainer()->getElementType();
            disconnect();
            getContainer()->getDetailView()->clearPages(sal_False);
            getContainer()->selectContainer(E_NONE); // invalidate the old selection
            m_eCurrentType = E_NONE;
            getContainer()->selectContainer(eType); // reselect the current one again
        }
    }
}

// -----------------------------------------------------------------------------
::rtl::OUString OApplicationController::getDatabaseName() const
{
    ::rtl::OUString sDatabaseName;
    try
    {
        if ( m_xDataSource.is() )
        {
            OSL_VERIFY( m_xDataSource->getPropertyValue( PROPERTY_NAME ) >>= sDatabaseName );
        }
    }
    catch ( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
    return sDatabaseName;
}

// -----------------------------------------------------------------------------
::rtl::OUString OApplicationController::getStrippedDatabaseName() const
{
    ::rtl::OUString sDatabaseName;
    return ::dbaui::getStrippedDatabaseName( m_xDataSource, sDatabaseName );
}

// -----------------------------------------------------------------------------
void OApplicationController::onDocumentOpened( const ::rtl::OUString& _rName, const sal_Int32 _nType,
        const ElementOpenMode _eMode, const Reference< XComponent >& _xDocument, const Reference< XComponent >& _rxDefinition )
{
    OSL_PRECOND( _xDocument.is(), "OApplicationController::onDocumentOpened: illegal document!" );
    if ( !_xDocument.is() )
        return;

    try
    {
        m_pSubComponentManager->onSubComponentOpened( _rName, _nType, _eMode, _rxDefinition.is() ? _rxDefinition : _xDocument );

        if ( _rxDefinition.is() )
        {
            Reference< XPropertySet > xProp( _rxDefinition, UNO_QUERY_THROW );
            Reference< XPropertySetInfo > xPSI( xProp->getPropertySetInfo(), UNO_SET_THROW );
            xProp->addPropertyChangeListener( PROPERTY_NAME, static_cast< XPropertyChangeListener* >( this ) );
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::insertHierachyElement(ElementType _eType,const String& _sParentFolder,sal_Bool _bCollection,const Reference<XContent>& _xContent,sal_Bool _bMove)
{
    Reference<XHierarchicalNameContainer> xNames(getElements(_eType), UNO_QUERY);
    return dbaui::insertHierachyElement(getView()
                           ,getORB()
                           ,xNames
                           ,_sParentFolder
                           ,_eType == E_FORM
                           ,_bCollection
                           ,_xContent
                           ,_bMove);
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::isRenameDeleteAllowed(ElementType _eType,sal_Bool _bDelete) const
{
    ElementType eType = getContainer()->getElementType();
    sal_Bool bEnabled = !isDataSourceReadOnly() && eType == _eType;
    if ( bEnabled )
    {

        if ( E_TABLE == eType )
            bEnabled = !isConnectionReadOnly() && getContainer()->isALeafSelected();

        sal_Bool bCompareRes = sal_False;
        if ( _bDelete )
            bCompareRes = getContainer()->getSelectionCount() > 0;
        else
        {
            bCompareRes = getContainer()->getSelectionCount() == 1;
            if ( bEnabled && bCompareRes && E_TABLE == eType )
            {
                ::std::vector< ::rtl::OUString> aList;
                getSelectionElementNames(aList);

                try
                {
                    Reference< XNameAccess > xContainer = const_cast<OApplicationController*>(this)->getElements(eType);
                    bEnabled = (xContainer.is() && xContainer->hasByName(*aList.begin()));
                    if ( bEnabled )
                        bEnabled = Reference<XRename>(xContainer->getByName(*aList.begin()),UNO_QUERY).is();
                }
                catch(Exception&)
                {
                    bEnabled = sal_False;
                }
            }
        }

        bEnabled = bEnabled && bCompareRes;
    }
    return bEnabled;
}
// -----------------------------------------------------------------------------
void OApplicationController::onLoadedMenu(const Reference< ::com::sun::star::frame::XLayoutManager >& _xLayoutManager)
{

    if ( _xLayoutManager.is() )
    {
        static ::rtl::OUString s_sStatusbar(RTL_CONSTASCII_USTRINGPARAM("private:resource/statusbar/statusbar"));
        _xLayoutManager->createElement( s_sStatusbar );
        _xLayoutManager->requestElement( s_sStatusbar );

        if ( getContainer() )
        {
            // we need to share the "mnemonic space":
            MnemonicGenerator aMnemonicGenerator;
            // - the menu already has mnemonics
            SystemWindow* pSystemWindow = getContainer()->GetSystemWindow();
            MenuBar* pMenu = pSystemWindow ? pSystemWindow->GetMenuBar() : NULL;
            if ( pMenu )
            {
                USHORT nMenuItems = pMenu->GetItemCount();
                for ( USHORT i = 0; i < nMenuItems; ++i )
                    aMnemonicGenerator.RegisterMnemonic( pMenu->GetItemText( pMenu->GetItemId( i ) ) );
            }
            // - the icons should use automatic ones
            getContainer()->createIconAutoMnemonics( aMnemonicGenerator );
            // - as well as the entries in the task pane
            getContainer()->setTaskExternalMnemonics( aMnemonicGenerator );
        }

        Execute( SID_DB_APP_VIEW_FORMS, Sequence< PropertyValue >() );
        InvalidateAll();
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::doAction(sal_uInt16 _nId ,ElementOpenMode _eOpenMode)
{
    ::std::vector< ::rtl::OUString> aList;
    getSelectionElementNames(aList);
    ElementType eType = getContainer()->getElementType();
    ::comphelper::NamedValueCollection aArguments;
    ElementOpenMode eOpenMode = _eOpenMode;
    if ( eType == E_REPORT && E_OPEN_FOR_MAIL == _eOpenMode )
    {
        aArguments.put("Hidden",true);
        eOpenMode = E_OPEN_NORMAL;
    }

    ::std::vector< ::std::pair< ::rtl::OUString ,Reference< XModel > > > aCompoments;
    ::std::vector< ::rtl::OUString>::iterator aEnd = aList.end();
    for (::std::vector< ::rtl::OUString>::iterator aIter = aList.begin(); aIter != aEnd; ++aIter)
    {
        if ( SID_DB_APP_CONVERTTOVIEW == _nId )
            convertToView(*aIter);
        else
        {
            Reference< XModel > xModel( openElementWithArguments( *aIter, eType, eOpenMode, _nId,aArguments ), UNO_QUERY );
            aCompoments.push_back( ::std::pair< ::rtl::OUString, Reference< XModel > >( *aIter, xModel ) );
        }
    }

    // special handling for mail, if more than one document is selected attach them all
    if ( _eOpenMode == E_OPEN_FOR_MAIL )
    {
        
        ::std::vector< ::std::pair< ::rtl::OUString ,Reference< XModel > > >::iterator componentIter = aCompoments.begin();
        ::std::vector< ::std::pair< ::rtl::OUString ,Reference< XModel > > >::iterator componentEnd = aCompoments.end();
        ::rtl::OUString aDocTypeString;
        SfxMailModel aSendMail;
        SfxMailModel::SendMailResult eResult = SfxMailModel::SEND_MAIL_OK;
        for (; componentIter != componentEnd && SfxMailModel::SEND_MAIL_OK == eResult; ++componentIter)
        {
            try
            {
                Reference< XModel > xModel(componentIter->second,UNO_QUERY);

                // Send document as e-Mail using stored/default type
                eResult = aSendMail.AttachDocument(aDocTypeString,xModel,componentIter->first);
                ::comphelper::disposeComponent(xModel);
            }
            catch(const Exception&)
            {
                DBG_UNHANDLED_EXCEPTION();
            }
        }
        if ( !aSendMail.IsEmpty() )
            aSendMail.Send( getFrame() );
    }
}
// -----------------------------------------------------------------------------
ElementType OApplicationController::getElementType(const Reference< XContainer >& _xContainer) const
{
    ElementType eRet = E_NONE;
    Reference<XServiceInfo> xServiceInfo(_xContainer,UNO_QUERY);
    if ( xServiceInfo.is() )
    {
        if ( xServiceInfo->supportsService(SERVICE_SDBCX_TABLES) )
            eRet = E_TABLE;
        else if ( xServiceInfo->supportsService(SERVICE_NAME_FORM_COLLECTION) )
            eRet = E_FORM;
        else if ( xServiceInfo->supportsService(SERVICE_NAME_REPORT_COLLECTION) )
            eRet = E_REPORT;
        else
            eRet = E_QUERY;
    }
    return eRet;
}

//........................................................................
}	// namespace dbaui
//........................................................................
