/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: singledoccontroller.cxx,v $
 *
 *  $Revision: 1.20 $
 *
 *  last change: $Author: vg $ $Date: 2007-01-15 14:36:28 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#ifndef DBAUI_SINGLEDOCCONTROLLER_HXX
#include "singledoccontroller.hxx"
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_ 
#include <comphelper/sequence.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_ 
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_ 
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XDOCUMENTDATASOURCE_HPP_
#include <com/sun/star/sdb/XDocumentDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP_
#include <com/sun/star/sdb/XOfficeDatabaseDocument.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_ 
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX 
#include <tools/debug.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_ 
#include <comphelper/types.hxx>
#endif
#ifndef _SV_MSGBOX_HXX 
#include <vcl/msgbox.hxx>
#endif
#ifndef _DBU_MISC_HRC_
#include "dbu_misc.hrc"
#endif
#ifndef DBAUI_DATAVIEW_HXX
#include "dataview.hxx"
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_ 
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif

//........................................................................
namespace dbaui
{
//........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::container;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::sdb;
    using namespace ::com::sun::star::frame;

    //====================================================================
    //= OSingleDocumentController
    //====================================================================
    //--------------------------------------------------------------------
    OSingleDocumentController::OSingleDocumentController(const Reference< XMultiServiceFactory >& _rxORB)
        :OSingleDocumentController_CBASE( _rxORB )
        ,m_bSuspended( sal_False )
        ,m_bEditable(sal_True)
        ,m_bModified(sal_False)

    {
    }

    //--------------------------------------------------------------------
    void OSingleDocumentController::initializeConnection( const Reference< XConnection >& _rxForeignConn )
    {
        DBG_ASSERT( !isConnected(), "OSingleDocumentController::initializeConnection: not to be called when already connected!" );
            // usually this gets called from within initialize of derived classes ...
        if ( isConnected() )
            disconnect();

        m_xConnection.reset( _rxForeignConn, SharedConnection::NoTakeOwnership );
        m_aSdbMetaData.reset( m_xConnection );
        startConnectionListening( m_xConnection );

        // get the data source the connection belongs to
        if ( !m_xDataSource.is() )
        {
            try
            {
                Reference< XChild > xConnAsChild( m_xConnection, UNO_QUERY );
                Reference< XDataSource > xDS;
                if ( xConnAsChild.is() )
                    xDS = Reference< XDataSource >( xConnAsChild->getParent(), UNO_QUERY );

                // (take the indirection through XDataSource to ensure we have a correct object ....)
                m_xDataSource.set(xDS,UNO_QUERY);
                DBG_ASSERT( m_xDataSource.is(), "OSingleDocumentController::initializeConnection: could not retrieve the data source!" );

                if ( m_xDataSource.is() )
                {
                    m_xDataSource->getPropertyValue( PROPERTY_NAME ) >>= m_sDataSourceName;
                    DBG_ASSERT( m_sDataSourceName.getLength(), "OSingleDocumentController::initializeConnection: invalid data source name!" );
                }
            }
            catch( const Exception& )
            {
                DBG_ERROR( "OSingleDocumentController::initializeConnection: caught an exception!" );
            }
        }
    }

    //--------------------------------------------------------------------
    void OSingleDocumentController::reconnect( sal_Bool _bUI )
    {
        OSL_ENSURE(!m_bSuspended, "Cannot reconnect while suspended!");
        
        stopConnectionListening( m_xConnection );
        m_aSdbMetaData.reset( NULL );
        m_xConnection.clear();

        // reconnect
        sal_Bool bReConnect = sal_True;
        if ( _bUI )
        {
            QueryBox aQuery( getView(), ModuleRes(QUERY_CONNECTION_LOST) );
            bReConnect = ( RET_YES == aQuery.Execute() );
        }

        // now really reconnect ...
        if ( bReConnect )
        {
            m_xConnection.reset( connect( Reference<XDataSource>(m_xDataSource,UNO_QUERY), sal_True ), SharedConnection::TakeOwnership );
            m_aSdbMetaData.reset( m_xConnection );
        }

        // invalidate all slots
        InvalidateAll();
    }

    //--------------------------------------------------------------------
    void OSingleDocumentController::disconnect()
    {
        stopConnectionListening(m_xConnection);
        m_aSdbMetaData.reset( NULL );
        m_xConnection.clear();

        InvalidateAll();
    }

    //--------------------------------------------------------------------
    void OSingleDocumentController::losingConnection()
    {
        // our connection was disposed so we need a new one
        reconnect( sal_True );
    }

    //--------------------------------------------------------------------
    void SAL_CALL OSingleDocumentController::disposing()
    {
        OSingleDocumentController_CBASE::disposing();
        m_aUndoManager.Clear();

        disconnect();

        m_aModelConnector.clear();

        attachFrame( Reference < XFrame >() );

        m_xDataSource.clear();
    }

    //--------------------------------------------------------------------
    sal_Bool OSingleDocumentController::Construct(Window* _pParent)
    {
        DBG_ASSERT( getView(), "OSingleDocumentController::Construct: have no view!" );
        if ( getView() )
            getView()->enableSeparator( );

        return OSingleDocumentController_CBASE::Construct( _pParent );
    }

    //--------------------------------------------------------------------
    void SAL_CALL OSingleDocumentController::disposing(const EventObject& _rSource) throw( RuntimeException )
    {
        if ( _rSource.Source == getConnection() )
        {
            if (    !m_bSuspended // when already suspended then we don't have to reconnect
                &&	!getBroadcastHelper().bInDispose  
                &&	!getBroadcastHelper().bDisposed 
                &&	isConnected() 
                )
            {
                losingConnection();
            }
            else
            {
                m_xConnection.reset( m_xConnection, SharedConnection::NoTakeOwnership );
                    // this prevents the "disposeComponent" call in disconnect
                disconnect();
            }
        }
        else
            OSingleDocumentController_CBASE::disposing( _rSource );
    }
    //--------------------------------------------------------------------
    namespace
    {
        void concatSQLExceptions(Any& _rChainLeft, const Any& _rChainRight)
        {
            if (!_rChainLeft.hasValue())
                _rChainLeft = _rChainRight;
            else
            {
                // to travel the chain by reference (and not by value), we need the getValue ...
                // looks like a hack, but the meaning of getValue is documented, and it's the only chance for reference-traveling ....

                DBG_ASSERT(::dbtools::SQLExceptionInfo(_rChainLeft).isValid(), "concatSQLExceptions: invalid warnings chain (this will crash)!");

                const SQLException* pChainTravel = static_cast<const SQLException*>(_rChainLeft.getValue());
                ::dbtools::SQLExceptionIteratorHelper aReferenceIterHelper(*pChainTravel);
                while (aReferenceIterHelper.hasMoreElements())
                    pChainTravel = aReferenceIterHelper.next();

                // reached the end of the chain, and pChainTravel points to the last element
                const_cast<SQLException*>(pChainTravel)->NextException = _rChainRight;
            }
        }

    }
    //--------------------------------------------------------------------
    /** appends an error in the current environment.
        @param	_aException
            contains a description of the error or the error directly
    */
    void OSingleDocumentController::appendError(const ::com::sun::star::sdbc::SQLException& _aException)
    {
        concatSQLExceptions(m_aCurrentError,makeAny(_aException));
    }
    //--------------------------------------------------------------------
    /** clears the error state.
    */
    void OSingleDocumentController::clearError()
    {
        m_aCurrentError = Any();
    }
    //--------------------------------------------------------------------
    /** set the current error in the given parameter.
        @param	_rException
            will contain the current error
    */
    void OSingleDocumentController::getError(::com::sun::star::sdbc::SQLException& _rException ) const
    {
        m_aCurrentError >>= _rException;
    }
    //--------------------------------------------------------------------
    sal_Bool OSingleDocumentController::hasError() const
    {
        return m_aCurrentError.hasValue();
    }
    //--------------------------------------------------------------------
    sal_Bool SAL_CALL OSingleDocumentController::suspend(sal_Bool bSuspend) throw( RuntimeException )
    {
        m_bSuspended = bSuspend;
        if ( !bSuspend && !isConnected() )
            reconnect(sal_True);

            
        return sal_True;
    }
    // -----------------------------------------------------------------------------
    FeatureState OSingleDocumentController::GetState(sal_uInt16 _nId) const
    {
        FeatureState aReturn;
            // (disabled automatically)
        aReturn.bEnabled = sal_True;

        switch (_nId)
        {
            case ID_BROWSER_UNDO:
                aReturn.bEnabled = m_bEditable && m_aUndoManager.GetUndoActionCount() != 0;
                if ( aReturn.bEnabled )
                {
                    String sUndo(ModuleRes(STR_UNDO_COLON));
                    sUndo += String(RTL_CONSTASCII_USTRINGPARAM(" "));
                    sUndo += m_aUndoManager.GetUndoActionComment();
                    aReturn.sTitle = sUndo;
                }
                break;
            case ID_BROWSER_REDO:
                aReturn.bEnabled = m_bEditable && m_aUndoManager.GetRedoActionCount() != 0;
                if ( aReturn.bEnabled )
                {
                    String sRedo(ModuleRes(STR_REDO_COLON));
                    sRedo += String(RTL_CONSTASCII_USTRINGPARAM(" "));
                    sRedo += m_aUndoManager.GetRedoActionComment();
                    aReturn.sTitle = sRedo;
                }
                break;
            default:
                aReturn = OSingleDocumentController_CBASE::GetState(_nId);
        }
        return aReturn;
    }
    // -----------------------------------------------------------------------------
    void OSingleDocumentController::Execute(sal_uInt16 _nId, const Sequence< PropertyValue >& /*aArgs*/)
    {
        switch(_nId)
        {
            case ID_BROWSER_CLOSE:
                closeTask();
                return;
            case ID_BROWSER_UNDO:
                m_aUndoManager.Undo();
                InvalidateFeature(ID_BROWSER_REDO);
                break;
            case ID_BROWSER_REDO:
                m_aUndoManager.Redo();
                InvalidateFeature(ID_BROWSER_UNDO);
                break;
        }
        InvalidateFeature(_nId);
    }
    // -----------------------------------------------------------------------------
    SfxUndoManager* OSingleDocumentController::getUndoMgr()
    {
        return &m_aUndoManager;
    }
    // -----------------------------------------------------------------------------
    void OSingleDocumentController::addUndoActionAndInvalidate(SfxUndoAction *_pAction)
    {
        // add undo action
        m_aUndoManager.AddUndoAction(_pAction);
        // when we add an undo action the controller was modified
        setModified(sal_True);
        // now inform me that or states changed
        InvalidateFeature(ID_BROWSER_UNDO);
        InvalidateFeature(ID_BROWSER_REDO);
    }
    // -----------------------------------------------------------------------------
    void OSingleDocumentController::setModified(sal_Bool _bModified)
    {
        m_bModified = _bModified;
        InvalidateFeature(ID_BROWSER_SAVEDOC);

        if ( isFeatureSupported( ID_BROWSER_SAVEASDOC ) )
            InvalidateFeature(ID_BROWSER_SAVEASDOC);
    }
    // -----------------------------------------------------------------------------
    Reference< XModel >  SAL_CALL OSingleDocumentController::getModel(void) throw( RuntimeException )
    {
        return NULL;//Reference< XModel >(m_xDataSource,UNO_QUERY); // OJ: i31891
    }
    // -----------------------------------------------------------------------------
    sal_Bool SAL_CALL OSingleDocumentController::attachModel(const Reference< XModel > & _rxModel) throw( RuntimeException )
    {
        ::osl::MutexGuard aGuard( m_aMutex );	

        Reference< XOfficeDatabaseDocument > xOfficeDoc( _rxModel, UNO_QUERY );
        m_xDataSource.set( xOfficeDoc.is() ? xOfficeDoc->getDataSource() : Reference<XDataSource>(), UNO_QUERY );

        m_aModelConnector.clear();
        if ( m_xDataSource.is() )
            m_aModelConnector = ModelControllerConnector( _rxModel, this );

        return sal_True;
    }
    // -----------------------------------------------------------------------------
     ::rtl::OUString OSingleDocumentController::getDataSourceName() const
     { 
         ::rtl::OUString sName;
         if ( m_xDataSource.is() )
             m_xDataSource->getPropertyValue(PROPERTY_NAME) >>= sName;
         return sName; 
     }
//........................................................................
}	// namespace dbaui
//........................................................................

