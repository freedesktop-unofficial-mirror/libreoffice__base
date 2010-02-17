/*************************************************************************
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

#include "subcomponentmanager.hxx"
#include "AppController.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/frame/XModel2.hpp>
#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/awt/XTopWindow.hpp>
#include <com/sun/star/embed/XComponentSupplier.hpp>
#include <com/sun/star/ucb/XCommandProcessor.hpp>
#include <com/sun/star/document/XDocumentEventBroadcaster.hpp>
/** === end UNO includes === **/

#include <tools/diagnose_ex.h>
#include <vcl/svapp.hxx>
#include <vos/mutex.hxx>

#include <hash_map>
#include <algorithm>
#include <functional>

//........................................................................
namespace dbaui
{
//........................................................................

    /** === begin UNO using === **/
    using ::com::sun::star::uno::Reference;
    using ::com::sun::star::uno::XInterface;
    using ::com::sun::star::uno::UNO_QUERY;
    using ::com::sun::star::uno::UNO_QUERY_THROW;
    using ::com::sun::star::uno::UNO_SET_THROW;
    using ::com::sun::star::uno::Exception;
    using ::com::sun::star::uno::RuntimeException;
    using ::com::sun::star::uno::Any;
    using ::com::sun::star::uno::makeAny;
    using ::com::sun::star::uno::Sequence;
    using ::com::sun::star::uno::Type;
    using ::com::sun::star::frame::XFrame;
    using ::com::sun::star::frame::XController;
    using ::com::sun::star::frame::XModel;
    using ::com::sun::star::lang::EventObject;
    using ::com::sun::star::lang::XComponent;
    using ::com::sun::star::frame::XModel2;
    using ::com::sun::star::container::XEnumeration;
    using ::com::sun::star::util::XCloseable;
    using ::com::sun::star::awt::XTopWindow;
    using ::com::sun::star::embed::XComponentSupplier;
    using ::com::sun::star::ucb::XCommandProcessor;
    using ::com::sun::star::ucb::Command;
    using ::com::sun::star::document::XDocumentEventBroadcaster;
    /** === end UNO using === **/

    //==============================================================================
    //= helper structs
    //==============================================================================
    namespace
    {
        struct SubComponentDescriptor
        {
            /// the frame which the component resides in. Must not be <NULL/>
            Reference< XFrame >             xFrame;
            /// the controller of the sub component. Must not be <NULL/>
            Reference< XController >        xController;
            /// the model of the sub component. Might be <NULL/>
            Reference< XModel >             xModel;
            /// the document definition which holds the component, if any
            Reference< XCommandProcessor > xComponentCommandProcessor;

            SubComponentDescriptor()
                :xFrame()
                ,xController()
                ,xModel()
            {
            }

            SubComponentDescriptor( const Reference< XComponent >& _rxComponent )
            {
                if ( !impl_constructFrom( _rxComponent ) )
                {
                    Reference< XComponentSupplier > xCompSupp( _rxComponent, UNO_QUERY_THROW );
                    Reference< XComponent > xComponent( xCompSupp->getComponent(), UNO_QUERY_THROW );
                    if ( !impl_constructFrom( xComponent ) )
                        throw RuntimeException( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Illegal component type." ) ), NULL );
                    xComponentCommandProcessor.set( _rxComponent, UNO_QUERY_THROW );
                }
            }

            inline bool is() const { return xFrame.is(); }

        private:
            bool impl_constructFrom( const Reference< XComponent >& _rxComponent )
            {
                // is it a model?
                xModel.set( _rxComponent, UNO_QUERY );
                if ( xModel.is() )
                {
                    xController.set( xModel->getCurrentController() );
                    if ( xController.is() )
                        xFrame.set( xController->getFrame(), UNO_SET_THROW );
                }
                else
                {
                    // is it a controller?
                    xController.set( _rxComponent, UNO_QUERY );
                    if ( xController.is() )
                    {
                        xFrame.set( xController->getFrame(), UNO_SET_THROW );
                    }
                    else
                    {
                        // is it a frame?
                        xFrame.set( _rxComponent, UNO_QUERY );
                        if ( !xFrame.is() )
                            return false;

                        // ensure we have a controller
                        xController.set( xFrame->getController(), UNO_SET_THROW );
                    }

                    // check wether there is a model (not required)
                    xModel.set( xController->getModel() );
                }

                return true;
            }
        };

        struct SelectSubComponent : public ::std::unary_function< SubComponentDescriptor, Reference< XComponent > >
        {
            Reference< XComponent > operator()( const SubComponentDescriptor _desc ) const
            {
                if ( _desc.xModel.is() )
                    return _desc.xModel.get();
                OSL_ENSURE( _desc.xController.is(), "SelectSubComponent::operator(): illegal component!" );
                return _desc.xController.get();
            }
        };

        struct SubComponentAccessor
        {
            /// the name of the sub component
            ::rtl::OUString sName;
            /// type of the component - usually an ElementType value
            sal_Int32       nComponentType;
            /// the mode in which the sub component has been opened
            ElementOpenMode eOpenMode;

            SubComponentAccessor()
                :sName()
                ,nComponentType( sal_Int32( E_NONE ) )
                ,eOpenMode( E_OPEN_NORMAL )
            {
            }

            SubComponentAccessor( const ::rtl::OUString& _rName, const sal_Int32 _nCompType, const ElementOpenMode _eMode )
                :sName( _rName )
                ,nComponentType( _nCompType )
                ,eOpenMode( _eMode )
            {
            }
        };

        struct SubComponentAccessorHash : public ::std::unary_function< SubComponentAccessor, size_t >
        {
            size_t operator()( const SubComponentAccessor& _lhs ) const
            {
                return _lhs.sName.hashCode() + _lhs.nComponentType + size_t( _lhs.eOpenMode );
            }
        };
        struct SubComponentAccessorEqual : public ::std::binary_function< SubComponentAccessor, SubComponentAccessor, bool >
        {
            bool operator()( const SubComponentAccessor& _lhs, const SubComponentAccessor& _rhs ) const
            {
                return  (   _lhs.sName          == _rhs.sName           )
                    &&  (   _lhs.nComponentType == _rhs.nComponentType  )
                    &&  (   _lhs.eOpenMode      == _rhs.eOpenMode       );
            }
        };

        typedef ::std::hash_map< SubComponentAccessor, SubComponentDescriptor, SubComponentAccessorHash, SubComponentAccessorEqual >
                SubComponentMap;

    }

    //==============================================================================
    //= SubComponentManager_Data
    //==============================================================================
    struct SubComponentManager_Data
    {
        SubComponentManager_Data( OApplicationController& _rController, const ::comphelper::SharedMutex& _rMutex )
            :m_rController( _rController )
            ,m_aMutex( _rMutex )
        {
        }

        OApplicationController&             m_rController;
        mutable ::comphelper::SharedMutex   m_aMutex;
        SubComponentMap                     m_aComponents;

        ::osl::Mutex&   getMutex() const { return m_aMutex; }
    };

    //====================================================================
    //= SubComponentManager
    //====================================================================
    //--------------------------------------------------------------------
    SubComponentManager::SubComponentManager( OApplicationController& _rController, const ::comphelper::SharedMutex& _rMutex )
        :m_pData( new SubComponentManager_Data( _rController, _rMutex ) )
    {
    }

    //--------------------------------------------------------------------
    SubComponentManager::~SubComponentManager()
    {
    }

    //--------------------------------------------------------------------
    void SubComponentManager::disposing()
    {
        ::osl::MutexGuard aGuard( m_pData->getMutex() );
        m_pData->m_aComponents.clear();
    }

    //--------------------------------------------------------------------
    namespace
    {
        bool lcl_fallbackToAnotherController( SubComponentDescriptor& _rCompDesc )
        {
            Reference< XController > xFallback;
            OSL_PRECOND( _rCompDesc.xModel.is(), "lcl_fallbackToAnotherController: illegal call!" );
            if ( !_rCompDesc.xModel.is() )
                return false;

            xFallback.set( _rCompDesc.xModel->getCurrentController() );
            if ( xFallback == _rCompDesc.xController )
                // don't accept the very same controller as fallback
                xFallback.clear();

            if ( !xFallback.is() )
            {
                // perhaps XModel2 can be of help here
                Reference< XModel2 > xModel2( _rCompDesc.xModel, UNO_QUERY );
                Reference< XEnumeration > xControllerEnum;
                if ( xModel2.is() )
                    xControllerEnum = xModel2->getControllers();
                while ( xControllerEnum.is() && xControllerEnum->hasMoreElements() )
                {
                    xFallback.set( xControllerEnum->nextElement(), UNO_QUERY );
                    if ( xFallback == _rCompDesc.xController )
                        xFallback.clear();
                }
            }

            if ( xFallback.is() )
            {
                _rCompDesc.xController = xFallback;
                _rCompDesc.xFrame.set( xFallback->getFrame(), UNO_SET_THROW );
                return true;
            }

            return false;
        }

        //----------------------------------------------------------------
        bool lcl_closeComponent( const Reference< XCommandProcessor >& _rxCommandProcessor )
        {
            bool bSuccess = false;
            try
            {
                Reference< XCommandProcessor > xCommandProcessor( _rxCommandProcessor, UNO_SET_THROW );
                sal_Int32 nCommandIdentifier = xCommandProcessor->createCommandIdentifier();

                Command aCommand;
                aCommand.Name = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "close" ) );
                xCommandProcessor->execute( aCommand, nCommandIdentifier, NULL );
                bSuccess = true;
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }
            return bSuccess;
        }

        //----------------------------------------------------------------
        bool lcl_closeComponent( const SubComponentDescriptor& _rComponent )
        {
            if ( _rComponent.xComponentCommandProcessor.is() )
                return lcl_closeComponent( _rComponent.xComponentCommandProcessor );

            Reference< XController > xController( _rComponent.xController );
            OSL_ENSURE( xController.is(), "lcl_closeComponent: invalid controller!" );

            // suspend the controller in the document
            if ( xController.is() )
                if ( !xController->suspend( sal_True ) )
                    return false;

            bool bSuccess = false;
            try
            {
                Reference< XCloseable > xCloseable( _rComponent.xFrame, UNO_QUERY_THROW );
                xCloseable->close( sal_True );
                bSuccess = true;
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }
            return bSuccess;
        }

        // -----------------------------------------------------------------------------
        void lcl_notifySubComponentEvent( const SubComponentManager_Data& _rData, const sal_Char* _pAsciiEventName,
                const SubComponentDescriptor& _rComponent )
        {
            try
            {
                Reference< XDocumentEventBroadcaster > xBroadcaster( _rData.m_rController.getModel(), UNO_QUERY_THROW );
                xBroadcaster->notifyDocumentEvent(
                    ::rtl::OUString::createFromAscii( _pAsciiEventName ),
                    &_rData.m_rController,
                    makeAny( _rComponent.xFrame )
                );
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }
        }
    }

    //--------------------------------------------------------------------
    void SAL_CALL SubComponentManager::disposing( const EventObject& _rSource ) throw (RuntimeException)
    {
        ::osl::ClearableMutexGuard aGuard( m_pData->getMutex() );

        SubComponentDescriptor aClosedComponent;

        for (   SubComponentMap::iterator comp = m_pData->m_aComponents.begin();
                comp != m_pData->m_aComponents.end();
                ++comp
            )
        {
            bool bRemove = false;

            if ( comp->second.xController == _rSource.Source )
            {
                if ( !comp->second.xModel.is() )
                {
                    bRemove = true;
                }
                else
                {
                    // maybe this is just one view to the sub document, and only this view is closed
                    if ( !lcl_fallbackToAnotherController( comp->second ) )
                    {
                        bRemove = true;
                    }
                }
            }
            else if ( comp->second.xModel == _rSource.Source )
            {
                bRemove = true;
            }

            if ( bRemove )
            {
                aClosedComponent = comp->second;
                m_pData->m_aComponents.erase( comp );
                break;
            }
        }

        if ( aClosedComponent.is() )
        {
            aGuard.clear();
            lcl_notifySubComponentEvent( *m_pData, "OnSubComponentClosed", aClosedComponent );
        }
    }

    //--------------------------------------------------------------------
    Sequence< Reference< XComponent> > SubComponentManager::getSubComponents() const
    {
        ::osl::MutexGuard aGuard( m_pData->getMutex() );

        Sequence< Reference< XComponent > > aComponents( m_pData->m_aComponents.size() );
        ::std::transform(
            m_pData->m_aComponents.begin(),
            m_pData->m_aComponents.end(),
            aComponents.getArray(),
            ::std::compose1( SelectSubComponent(), ::std::select2nd< SubComponentMap::value_type >() )
        );
        return aComponents;
    }

    // -----------------------------------------------------------------------------
    sal_Bool SubComponentManager::closeSubComponents()
    {
        ::vos::OGuard aSolarGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard( m_pData->getMutex() );

        try
        {
            typedef ::std::vector< SubComponentAccessor > ComponentAccessors;
            ComponentAccessors aClosedComponents;

            SubComponentMap aComponents( m_pData->m_aComponents );
            for (   SubComponentMap::const_iterator comp = aComponents.begin();
                    comp != aComponents.end();
                    ++comp
                )
            {
                lcl_closeComponent( comp->second );
            }
        }
        catch ( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }

        return empty();
    }

    // -----------------------------------------------------------------------------
    bool SubComponentManager::empty() const
    {
        ::osl::MutexGuard aGuard( m_pData->getMutex() );
        return m_pData->m_aComponents.empty();
    }

    // -----------------------------------------------------------------------------
    void SubComponentManager::onSubComponentOpened( const ::rtl::OUString&  _rName, const sal_Int32 _nComponentType,
        const ElementOpenMode _eOpenMode, const Reference< XComponent >& _rxComponent )
    {
        ::osl::ClearableMutexGuard aGuard( m_pData->getMutex() );

        // put into map
        SubComponentAccessor aKey( _rName, _nComponentType, _eOpenMode );
        SubComponentDescriptor aElement( _rxComponent );
        ENSURE_OR_THROW( aElement.xModel.is() || aElement.xController.is(), "illegal component" );

        m_pData->m_aComponents.insert( SubComponentMap::value_type(
            aKey, aElement
        ) ) ;

        // add as listener
        if ( aElement.xController.is() )
            aElement.xController->addEventListener( this );
        if ( aElement.xModel.is() )
            aElement.xModel->addEventListener( this );

        // notify this to interested parties
        aGuard.clear();
        lcl_notifySubComponentEvent( *m_pData, "OnSubComponentOpened", aElement );
    }

    // -----------------------------------------------------------------------------
    bool SubComponentManager::activateSubFrame( const ::rtl::OUString& _rName, const sal_Int32 _nComponentType, const ElementOpenMode _eOpenMode ) const
    {
        ::osl::MutexGuard aGuard( m_pData->getMutex() );

        SubComponentAccessor aKey( _rName, _nComponentType, _eOpenMode );
        SubComponentMap::const_iterator pos = m_pData->m_aComponents.find( aKey );
        if ( pos == m_pData->m_aComponents.end() )
            // no component with this name/type/open mode
            return false;

        const Reference< XFrame > xFrame( pos->second.xFrame, UNO_SET_THROW );
        const Reference< XTopWindow > xTopWindow( xFrame->getContainerWindow(), UNO_QUERY_THROW );
        xTopWindow->toFront();

        return true;
    }

    // -----------------------------------------------------------------------------
    bool SubComponentManager::closeSubFrames( const ::rtl::OUString& _rName, const sal_Int32 _nComponentType )
    {
        ::osl::MutexGuard aGuard( m_pData->getMutex() );

        SubComponentMap aWorkingCopy( m_pData->m_aComponents );
        for (   SubComponentMap::const_iterator comp = aWorkingCopy.begin();
                comp != aWorkingCopy.end();
                ++comp
            )
        {
            if ( ( comp->first.sName != _rName ) || ( comp->first.nComponentType != _nComponentType ) )
                continue;

            if ( !lcl_closeComponent( comp->second ) )
                return false;
        }

        return true;
    }

//........................................................................
} // namespace dbaui
//........................................................................
