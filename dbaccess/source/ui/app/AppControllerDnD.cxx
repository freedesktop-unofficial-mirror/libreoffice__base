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

#ifndef DBAUI_APPCONTROLLER_HXX
#include "AppController.hxx"
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSINGLESELECTQUERYCOMPOSER_HPP_
#include <com/sun/star/sdb/XSingleSelectQueryComposer.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XSTORABLE_HPP_
#include <com/sun/star/frame/XStorable.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XHIERARCHICALNAMECONTAINER_HPP_
#include <com/sun/star/container/XHierarchicalNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XBOOKMARKSSUPPLIER_HPP_
#include <com/sun/star/sdb/XBookmarksSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XVIEWSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_
#include <com/sun/star/sdbcx/XDrop.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _UNOTOOLS_UCBHELPER_HXX
#include <unotools/ucbhelper.hxx>
#endif
#ifndef DBAUI_DLGSAVE_HXX
#include "dlgsave.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _CPPUHELPER_EXC_HLP_HXX_
#include <cppuhelper/exc_hlp.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _SV_WAITOBJ_HXX
#include <vcl/waitobj.hxx>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif
#ifndef DBAUI_APPVIEW_HXX
#include "AppView.hxx"
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <svx/dataaccessdescriptor.hxx>
#endif
#ifndef SVX_DBAOBJECTEX_HXX
#include <svx/dbaobjectex.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBAU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _DBU_APP_HRC_
#include "dbu_app.hrc"
#endif
#ifndef _SV_MENU_HXX
#include <vcl/menu.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SVLBOXITM_HXX
#include <svtools/svlbitm.hxx>
#endif
#ifndef _DBAUI_LISTVIEWITEMS_HXX_
#include "listviewitems.hxx"
#endif
#ifndef DBAUI_APPDETAILVIEW_HXX
#include "AppDetailView.hxx"
#endif
#ifndef _DBAUI_LINKEDDOCUMENTS_HXX_
#include "linkeddocuments.hxx"
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef DBAUI_DBEXCHANGE_HXX
#include "dbexchange.hxx"
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#include <algorithm>
#ifndef _SVTREEBOX_HXX
#include <svtools/svtreebx.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XREPORTDOCUMENTSSUPPLIER_HPP_
#include <com/sun/star/sdb/XReportDocumentsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XFORMDOCUMENTSSUPPLIER_HPP_
#include <com/sun/star/sdb/XFormDocumentsSupplier.hpp>
#endif
#ifndef _FILEDLGHELPER_HXX
#include <sfx2/filedlghelper.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <unotools/pathoptions.hxx>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX
#include <sfx2/docfilt.hxx>
#endif
#ifndef _SVT_FILEVIEW_HXX
#include <svtools/fileview.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef DBACCESS_SOURCE_UI_MISC_DEFAULTOBJECTNAMECHECK_HXX
#include "defaultobjectnamecheck.hxx"
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#include "subcomponentmanager.hxx"

//........................................................................
namespace dbaui
{
//........................................................................
using namespace ::dbtools;
using namespace ::svx;
using namespace ::svtools;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::util;

// -----------------------------------------------------------------------------
void OApplicationController::deleteTables(const ::std::vector< ::rtl::OUString>& _rList)
{
    SharedConnection xConnection( ensureConnection() );

    Reference<XTablesSupplier> xSup(xConnection,UNO_QUERY);
    OSL_ENSURE(xSup.is(),"OApplicationController::deleteTable: no XTablesSuppier!");
    if ( xSup.is() )
    {
        Reference<XNameAccess> xTables = xSup->getTables();
        Reference<XDrop> xDrop(xTables,UNO_QUERY);
        if ( xDrop.is() )
        {
            bool bConfirm = true;
            ::std::vector< ::rtl::OUString>::const_iterator aEnd = _rList.end();
            for (::std::vector< ::rtl::OUString>::const_iterator aIter = _rList.begin(); aIter != aEnd; ++aIter)
            {
                ::rtl::OUString sTableName = *aIter;

                sal_Int32 nResult = RET_YES;
                if ( bConfirm )
                    nResult = ::dbaui::askForUserAction(getView(),STR_TITLE_CONFIRM_DELETION ,STR_QUERY_DELETE_TABLE,_rList.size() > 1 && (aIter+1) != _rList.end(),sTableName);

                bool bUserConfirmedDelete =
                            ( RET_YES == nResult )
                        ||  ( RET_ALL == nResult );
                if ( bUserConfirmedDelete && m_pSubComponentManager->closeSubFrames( sTableName, E_TABLE ) )
                {
                    SQLExceptionInfo aErrorInfo;
                    try
                    {
                        if ( xTables->hasByName(sTableName) )
                            xDrop->dropByName(sTableName);
                        else
                        {// could be a view
                            Reference<XViewsSupplier> xViewsSup(xConnection,UNO_QUERY);

                            Reference<XNameAccess> xViews;
                            if ( xViewsSup.is() )
                            {
                                xViews = xViewsSup->getViews();
                                if ( xViews.is() && xViews->hasByName(sTableName) )
                                {
                                    xDrop.set(xViews,UNO_QUERY);
                                    if ( xDrop.is() )
                                        xDrop->dropByName(sTableName);
                                }
                            }
                        }
                    }
                    catch(SQLContext& e) { aErrorInfo = e; }
                    catch(SQLWarning& e) { aErrorInfo = e; }
                    catch(SQLException& e) { aErrorInfo = e; }
                    catch(WrappedTargetException& e)
                    {
                        SQLException aSql;
                        if(e.TargetException >>= aSql)
                            aErrorInfo = aSql;
                        else
                            OSL_ENSURE(sal_False, "OApplicationController::implDropTable: something strange happended!");
                    }
                    catch( const Exception& )
                    {
                        DBG_UNHANDLED_EXCEPTION();
                    }

                    if ( aErrorInfo.isValid() )
                        showError(aErrorInfo);

                    if ( RET_ALL == nResult )
                        bConfirm = false;
                }
                else
                    break;
            }
        }
        else
        {
            String sMessage(ModuleRes(STR_MISSING_TABLES_XDROP));
            ErrorBox aError(getView(), WB_OK, sMessage);
            aError.Execute();
        }
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::deleteObjects( ElementType _eType, const ::std::vector< ::rtl::OUString>& _rList, bool _bConfirm )
{
    Reference< XNameContainer > xNames( getElements( _eType ), UNO_QUERY );
    Reference< XHierarchicalNameContainer > xHierarchyName( xNames, UNO_QUERY );
    if ( xNames.is() )
    {
        ByteString sDialogPosition;
        svtools::QueryDeleteResult_Impl eResult = _bConfirm ? svtools::QUERYDELETE_YES : svtools::QUERYDELETE_ALL;

        // The list of elements to delete is allowed to contain related elements: A given element may
        // be the ancestor or child of another element from the list.
        // We want to ensure that ancestors get deleted first, so we normalize the list in this respect.
        // #i33353# - 2004-09-27 - fs@openoffice.org
        ::std::set< ::rtl::OUString > aDeleteNames;
            // Note that this implicitly uses ::std::less< ::rtl::OUString > a comparison operation, which
            // results in lexicographical order, which is exactly what we need, because "foo" is *before*
            // any "foo/bar" in this order.
        ::std::copy(
            _rList.begin(), _rList.end(),
            ::std::insert_iterator< ::std::set< ::rtl::OUString > >( aDeleteNames, aDeleteNames.begin() )
        );

        ::std::set< ::rtl::OUString >::size_type nCount = aDeleteNames.size();
        for ( ::std::set< ::rtl::OUString >::size_type nObjectsLeft = nCount; !aDeleteNames.empty(); )
        {
            ::std::set< ::rtl::OUString >::iterator  aThisRound = aDeleteNames.begin();

            if ( eResult != svtools::QUERYDELETE_ALL )
            {
                svtools::QueryDeleteDlg_Impl aDlg( getView(), *aThisRound );

                if ( sDialogPosition.Len() )
                    aDlg.SetWindowState( sDialogPosition );

                if ( nObjectsLeft > 1 )
                    aDlg.EnableAllButton();

                if ( aDlg.Execute() == RET_OK )
                    eResult = aDlg.GetResult();
                else
                    return;

                sDialogPosition = aDlg.GetWindowState( );
            }

            bool bSuccess = false;

            bool bUserConfirmedDelete =
                        ( eResult == svtools::QUERYDELETE_ALL )
                    ||  ( eResult == svtools::QUERYDELETE_YES );

            if  (   bUserConfirmedDelete
                &&  (   ( _eType == E_QUERY ) ? m_pSubComponentManager->closeSubFrames( *aThisRound, _eType ) : true )
                )
            {
                try
                {
                    if ( xHierarchyName.is() )
                        xHierarchyName->removeByHierarchicalName( *aThisRound );
                    else
                        xNames->removeByName( *aThisRound );

                    bSuccess = true;

                    // now that we removed the element, care for all it's child elements
                    // which may also be a part of the list
                    // #i33353# - 2004-09-27 - fs@openoffice.org
                    OSL_ENSURE( aThisRound->getLength() - 1 >= 0, "OApplicationController::deleteObjects: empty name?" );
                    ::rtl::OUStringBuffer sSmallestSiblingName( *aThisRound );
                    sSmallestSiblingName.append( (sal_Unicode)( '/' + 1) );

                    ::std::set< ::rtl::OUString >::iterator aUpperChildrenBound = aDeleteNames.lower_bound( sSmallestSiblingName.makeStringAndClear() );
                    for ( ::std::set< ::rtl::OUString >::iterator aObsolete = aThisRound;
                          aObsolete != aUpperChildrenBound;
                        )
                    {
#if OSL_DEBUG_LEVEL > 0
                        ::rtl::OUString sObsoleteName = *aObsolete;
#endif
                        ::std::set< ::rtl::OUString >::iterator aNextObsolete = aObsolete; ++aNextObsolete;
                        aDeleteNames.erase( aObsolete );
                        --nObjectsLeft;
                        aObsolete = aNextObsolete;
                    }
                }
                catch(const SQLException&)
                {
                    showError( SQLExceptionInfo( ::cppu::getCaughtException() ) );
                }
                catch(WrappedTargetException& e)
                {
                    SQLException aSql;
                    if ( e.TargetException >>= aSql )
                        showError( SQLExceptionInfo( e.TargetException ) );
                    else
                        OSL_ENSURE( sal_False, "OApplicationController::deleteObjects: something strange happended!" );
                }
                catch( const Exception& )
                {
                    DBG_UNHANDLED_EXCEPTION();
                }
            }

            if ( !bSuccess )
            {
                // okay, this object could not be deleted (or the user did not want to delete it),
                // but continue with the rest
                aDeleteNames.erase( aThisRound );
                --nObjectsLeft;
            }
        }
    }
}
// -----------------------------------------------------------------------------
void OApplicationController::deleteEntries()
{
    ::vos::OGuard aSolarGuard(Application::GetSolarMutex());
    ::osl::MutexGuard aGuard( getMutex() );

    if ( getContainer() )
    {
        ::std::vector< ::rtl::OUString> aList;
        getSelectionElementNames(aList);
        ElementType eType = getContainer()->getElementType();
        switch(eType)
        {
        case E_TABLE:
            deleteTables(aList);
            break;
        case E_QUERY:
            deleteObjects( E_QUERY, aList, true );
            break;
        case E_FORM:
            deleteObjects( E_FORM, aList, true );
            break;
        case E_REPORT:
            deleteObjects( E_REPORT, aList, true );
            break;
        case E_NONE:
            break;
        }
    }
}
// -----------------------------------------------------------------------------
const SharedConnection& OApplicationController::ensureConnection( ::dbtools::SQLExceptionInfo* _pErrorInfo )
{
    ::vos::OGuard aSolarGuard(Application::GetSolarMutex());
    ::osl::MutexGuard aGuard( getMutex() );

    if ( !m_xDataSourceConnection.is() )
    {
        WaitObject aWO(getView());
        String sConnectingContext( ModuleRes( STR_COULDNOTCONNECT_DATASOURCE ) );
        sConnectingContext.SearchAndReplaceAscii("$name$", getStrippedDatabaseName());

        m_xDataSourceConnection.reset( connect( getDatabaseName(), sConnectingContext, _pErrorInfo ) );
        if ( m_xDataSourceConnection.is() )
        {
            SQLExceptionInfo aError;
            try
            {
                m_xMetaData = m_xDataSourceConnection->getMetaData();
            }
            catch( const SQLException& )
            {
                aError = ::cppu::getCaughtException();
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }
            if ( aError.isValid() )
            {
                if ( _pErrorInfo )
                {
                    *_pErrorInfo = aError;
                }
                else
                {
                    showError( aError );
                }
            }
        }
    }
    return m_xDataSourceConnection;
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::isDataSourceReadOnly() const
{
    Reference<XStorable> xStore(m_xModel,UNO_QUERY);
    return !xStore.is() || xStore->isReadonly();
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::isConnectionReadOnly() const
{
    sal_Bool bIsConnectionReadOnly = sal_True;
    if ( m_xMetaData.is() )
    {
        try
        {
            bIsConnectionReadOnly = m_xMetaData->isReadOnly();
        }
        catch(const SQLException&)
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    // TODO check configuration
    return bIsConnectionReadOnly;
}
// -----------------------------------------------------------------------------
Reference< XNameAccess > OApplicationController::getElements( ElementType _eType )
{
    Reference< XNameAccess > xElements;
    try
    {
        switch ( _eType )
        {
        case E_REPORT:
        {
            Reference< XReportDocumentsSupplier > xSupp( m_xModel, UNO_QUERY_THROW );
            xElements.set( xSupp->getReportDocuments(), UNO_SET_THROW );
        }
        break;

        case E_FORM:
        {
            Reference< XFormDocumentsSupplier > xSupp( m_xModel, UNO_QUERY_THROW );
            xElements.set( xSupp->getFormDocuments(), UNO_SET_THROW );
        }
        break;

        case E_QUERY:
        {
            xElements.set( getQueryDefintions(), UNO_QUERY_THROW );
        }
        break;

        case E_TABLE:
        {
            if ( m_xDataSourceConnection.is() )
            {
                Reference< XTablesSupplier > xSup( getConnection(), UNO_QUERY_THROW );
                xElements.set( xSup->getTables(), UNO_SET_THROW );
            }
        }
        break;

        default:
            break;
        }
    }
    catch(const Exception&)
    {
        DBG_UNHANDLED_EXCEPTION();
    }

    return xElements;
}
// -----------------------------------------------------------------------------
void OApplicationController::getSelectionElementNames(::std::vector< ::rtl::OUString>& _rNames) const
{
    ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( getMutex() );

    OSL_ENSURE(getContainer(),"View isn't valid! -> GPF");

    getContainer()->getSelectionElementNames( _rNames );
}

// -----------------------------------------------------------------------------
::std::auto_ptr< OLinkedDocumentsAccess > OApplicationController::getDocumentsAccess( ElementType _eType )
{
    OSL_ENSURE( ( _eType == E_TABLE ) || ( _eType == E_QUERY ) || ( _eType == E_FORM ) || ( _eType == E_REPORT ),
        "OApplicationController::getDocumentsAccess: only forms and reports are supported here!" );

    SharedConnection xConnection( ensureConnection() );
    Reference< XNameAccess > xDocContainer;

    if ( ( _eType == E_FORM ) | ( _eType == E_REPORT ) )
    {
        xDocContainer.set( getElements( _eType ) );
        OSL_ENSURE( xDocContainer.is(), "OApplicationController::getDocumentsAccess: invalid container!" );
    }

    ::std::auto_ptr< OLinkedDocumentsAccess > pDocuments( new OLinkedDocumentsAccess(
        getView(), this, getORB(), xDocContainer, xConnection, getDatabaseName()
    ) );
    return pDocuments;
}
// -----------------------------------------------------------------------------
TransferableHelper* OApplicationController::copyObject()
{
    try
    {
        ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard( getMutex() );

        ElementType eType = getContainer()->getElementType();
        TransferableHelper* pData = NULL;
        switch( eType )
        {
            case E_TABLE:
            case E_QUERY:
            {
                SharedConnection xConnection( ensureConnection() );
                Reference< XDatabaseMetaData> xMetaData;
                if ( xConnection.is() )
                    xMetaData = xConnection->getMetaData();

                ::rtl::OUString sName = getContainer()->getQualifiedName( NULL );
                if ( sName.getLength() )
                {
                    ::rtl::OUString sDataSource	= getDatabaseName();

                    if ( eType == E_TABLE )
                    {
                        pData = new ODataClipboard(sDataSource, CommandType::TABLE, sName, xConnection, getNumberFormatter(xConnection,getORB()), getORB());
                    }
                    else
                    {
                        pData = new ODataClipboard(sDataSource, CommandType::QUERY, sName, getNumberFormatter(xConnection,getORB()), getORB());
                    }
                }
            }
                break;
            case E_FORM:
            case E_REPORT:
            {
                ::std::vector< ::rtl::OUString> aList;
                getSelectionElementNames(aList);
                Reference< XHierarchicalNameAccess > xElements(getElements(eType),UNO_QUERY);
                if ( xElements.is() && !aList.empty() )
                {
                    Reference< XContent> xContent(xElements->getByHierarchicalName(*aList.begin()),UNO_QUERY);
                    pData = new OComponentTransferable( getDatabaseName(), xContent );
                }
            }
            break;
            default:
                break;
        }

        // the owner ship goes to ODataClipboards
        return pData;
    }
    catch(const SQLException&)
    {
        showError( SQLExceptionInfo( ::cppu::getCaughtException() ) );
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
    return NULL;
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::paste( ElementType _eType,const ::svx::ODataAccessDescriptor& _rPasteData,const String& _sParentFolder ,sal_Bool _bMove)
{
    try
    {
        if ( _eType == E_QUERY )
        {
            sal_Int32 nCommandType = CommandType::TABLE;
            if ( _rPasteData.has(daCommandType) )
                _rPasteData[daCommandType]		>>= nCommandType;

            if ( CommandType::QUERY == nCommandType || CommandType::COMMAND == nCommandType )
            {
                // read all nescessary data

                ::rtl::OUString	sCommand;
                sal_Bool bEscapeProcessing = sal_True;

                _rPasteData[daCommand] >>= sCommand;
                if ( _rPasteData.has(daEscapeProcessing) )
                    _rPasteData[daEscapeProcessing]	>>= bEscapeProcessing;

                // plausibility check
                sal_Bool bValidDescriptor = sal_False;
                ::rtl::OUString	sDataSourceName = _rPasteData.getDataSource();
                if (CommandType::QUERY == nCommandType)
                    bValidDescriptor = sDataSourceName.getLength() && sCommand.getLength();
                else if (CommandType::COMMAND == nCommandType)
                    bValidDescriptor = (0 != sCommand.getLength());
                if (!bValidDescriptor)
                {
                    DBG_ERROR("OApplicationController::paste: invalid descriptor!");
                    return sal_False;
                }

                // the target object name (as we'll suggest it to the user)
                ::rtl::OUString sTargetName;
                try
                {
                    if ( CommandType::QUERY == nCommandType )
                        sTargetName = sCommand;

                    if ( !sTargetName.getLength() )
                    {
                        String sDefaultName = String( ModuleRes( STR_QRY_TITLE ) );
                        sDefaultName = sDefaultName.GetToken( 0, ' ' );

                        Reference< XNameAccess > xQueries( getQueryDefintions(), UNO_QUERY_THROW );
                        sTargetName = ::dbtools::createUniqueName( xQueries, sDefaultName, sal_False );
                    }
                }
                catch(const Exception&)
                {
                    DBG_UNHANDLED_EXCEPTION();
                }

                Reference< XPropertySet > xQuery;
                if (CommandType::QUERY == nCommandType)
                {
                    // need to extract the statement and the escape processing flag from the query object
                    sal_Bool bSuccess = sal_False;
                    try
                    {
                        // the concrete query
                        Reference< XQueryDefinitionsSupplier > xSourceQuerySup(
                            getDataSourceByName( sDataSourceName, getView(), getORB(), NULL ),
                            UNO_QUERY_THROW );
                        Reference< XNameAccess > xQueries( xSourceQuerySup->getQueryDefinitions(), UNO_SET_THROW );
                        if ( xQueries->hasByName( sCommand ) )
                        {
                            xQuery.set( xQueries->getByName(sCommand), UNO_QUERY_THROW );
                            bSuccess = true;
                        }
                    }
                    catch(SQLException&) { throw; }	// caught and handled by the outer catch
                    catch( const Exception& )
                    {
                        DBG_UNHANDLED_EXCEPTION();
                    }

                    if (!bSuccess)
                    {
                        DBG_ERROR("OApplicationController::paste: could not extract the source query object!");
                        // TODO: maybe this is worth an error message to be displayed to the user ....
                        return sal_False;
                    }
                }


                Reference< XNameContainer > xDestQueries(getQueryDefintions(), UNO_QUERY);
                Reference< XSingleServiceFactory > xQueryFactory(xDestQueries, UNO_QUERY);
                if (!xQueryFactory.is())
                {
                    DBG_ERROR("OApplicationController::paste: invalid destination query container!");
                    return sal_False;
                }

                // here we have everything needed to create a new query object ...
                // ... ehm, except a new name
                ensureConnection();

                DynamicTableOrQueryNameCheck aNameChecker( getConnection(), CommandType::QUERY );
                ::dbtools::SQLExceptionInfo aDummy;
                bool bNeedAskForName =  ( sCommand.getLength() == 0 )
                                            /* we did not have a source name, so the target name was auto-generated */
                                    ||  ( !aNameChecker.isNameValid( sTargetName, aDummy ) );
                                            /*  name is invalid in the target DB (e.g. because it already
                                                has a /table/ with that name) */
                if ( bNeedAskForName )
                {
                    OSaveAsDlg aAskForName(	getView(),
                                            CommandType::QUERY,
                                            getORB(),
                                            getConnection(),
                                            sTargetName,
                                            aNameChecker,
                                            SAD_ADDITIONAL_DESCRIPTION | SAD_TITLE_PASTE_AS);
                    if ( RET_OK != aAskForName.Execute() )
                        // cancelled by the user
                        return sal_False;
                    sTargetName = aAskForName.getName();
                }

                // create a new object
                Reference< XPropertySet > xNewQuery(xQueryFactory->createInstance(), UNO_QUERY);
                DBG_ASSERT(xNewQuery.is(), "OApplicationController::paste: invalid object created by factory!");
                if (xNewQuery.is())
                {
                    // initialize
                    if ( xQuery.is() )
                        ::comphelper::copyProperties(xQuery,xNewQuery);
                    else
                    {
                        xNewQuery->setPropertyValue(PROPERTY_COMMAND,makeAny(sCommand));
                        xNewQuery->setPropertyValue(PROPERTY_ESCAPE_PROCESSING,makeAny(bEscapeProcessing));
                    }
                    // insert
                    xDestQueries->insertByName( sTargetName, makeAny(xNewQuery) );
                    xNewQuery.set(xDestQueries->getByName( sTargetName),UNO_QUERY);
                    if ( xQuery.is() && xNewQuery.is() )
                    {
                        Reference<XColumnsSupplier> xSrcColSup(xQuery,UNO_QUERY);
                        Reference<XColumnsSupplier> xDstColSup(xNewQuery,UNO_QUERY);
                        if ( xSrcColSup.is() && xDstColSup.is() )
                        {
                            Reference<XNameAccess> xSrcNameAccess = xSrcColSup->getColumns();
                            Reference<XNameAccess> xDstNameAccess = xDstColSup->getColumns();
                            Reference<XDataDescriptorFactory> xFac(xDstNameAccess,UNO_QUERY);
                            Reference<XAppend> xAppend(xFac,UNO_QUERY);
                            if ( xSrcNameAccess.is() && xDstNameAccess.is() && xSrcNameAccess->hasElements() && xAppend.is() )
                            {
                                Reference<XPropertySet> xDstProp(xFac->createDataDescriptor());

                                Sequence< ::rtl::OUString> aSeq = xSrcNameAccess->getElementNames();
                                const ::rtl::OUString* pIter = aSeq.getConstArray();
                                const ::rtl::OUString* pEnd	  = pIter + aSeq.getLength();
                                for( ; pIter != pEnd ; ++pIter)
                                {
                                    Reference<XPropertySet> xSrcProp(xSrcNameAccess->getByName(*pIter),UNO_QUERY);
                                    ::comphelper::copyProperties(xSrcProp,xDstProp);
                                    xAppend->appendByDescriptor(xDstProp);
                                }
                            }
                        }
                    }
                }
            }
            else
                OSL_TRACE("There should be a sequence in it!");
            return sal_True;
        }
        else if ( _rPasteData.has(daComponent) ) // forms or reports
        {
            Reference<XContent> xContent;
            _rPasteData[daComponent] >>= xContent;
            return insertHierachyElement(_eType,_sParentFolder,Reference<XNameAccess>(xContent,UNO_QUERY).is(),xContent,_bMove);
        }
    }
    catch(const SQLException&) { showError( SQLExceptionInfo( ::cppu::getCaughtException() ) ); }
    catch(const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
    return sal_False;
}
// -----------------------------------------------------------------------------
Reference<XNameContainer> OApplicationController::getQueryDefintions() const
{
    Reference<XQueryDefinitionsSupplier> xSet(m_xDataSource,UNO_QUERY);
    Reference<XNameContainer> xNames;
    if ( xSet.is() )
    {
        xNames.set(xSet->getQueryDefinitions(),UNO_QUERY);
    }
    return xNames;
}
// -----------------------------------------------------------------------------
void OApplicationController::getSupportedFormats(ElementType _eType,::std::vector<SotFormatStringId>& _rFormatIds) const
{
    switch( _eType )
    {
        case E_TABLE:
            _rFormatIds.push_back(SOT_FORMATSTR_ID_DBACCESS_TABLE);
            _rFormatIds.push_back(SOT_FORMAT_RTF);
            _rFormatIds.push_back(SOT_FORMATSTR_ID_HTML);
            // run through
        case E_QUERY:
            _rFormatIds.push_back(SOT_FORMATSTR_ID_DBACCESS_QUERY);
            break;
        default:
            break;
    }
}
// -----------------------------------------------------------------------------
sal_Bool OApplicationController::isTableFormat()  const
{
    return m_aTableCopyHelper.isTableFormat(getViewClipboard());
}
// -----------------------------------------------------------------------------
IMPL_LINK( OApplicationController, OnAsyncDrop, void*, /*NOTINTERESTEDIN*/ )
{
    m_nAsyncDrop = 0;
    ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard( getMutex() );


    if ( m_aAsyncDrop.nType == E_TABLE )
    {
        SharedConnection xConnection( ensureConnection() );
        if ( xConnection.is() )
            m_aTableCopyHelper.asyncCopyTagTable( m_aAsyncDrop, getDatabaseName(), xConnection );
    }
    else
    {
        if ( paste(m_aAsyncDrop.nType,m_aAsyncDrop.aDroppedData,m_aAsyncDrop.aUrl,m_aAsyncDrop.nAction == DND_ACTION_MOVE)
            && m_aAsyncDrop.nAction == DND_ACTION_MOVE )
        {
            Reference<XContent> xContent;
            m_aAsyncDrop.aDroppedData[daComponent] >>= xContent;
            ::std::vector< ::rtl::OUString> aList;
            sal_Int32 nIndex = 0;
            ::rtl::OUString sName = xContent->getIdentifier()->getContentIdentifier();
            ::rtl::OUString sErase = sName.getToken(0,'/',nIndex); // we don't want to have the "private:forms" part
            if ( nIndex != -1 )
            {
                aList.push_back(sName.copy(sErase.getLength() + 1));
                deleteObjects( m_aAsyncDrop.nType, aList, false );
            }
        }
    }

    m_aAsyncDrop.aDroppedData.clear();

    return 0L;
}
//........................................................................
}	// namespace dbaui
//........................................................................


