/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: genericcontroller.cxx,v $
 *
 *  $Revision: 1.65 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 14:29:16 $
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
#ifndef DBAUI_GENERICCONTROLLER_HXX
#include "genericcontroller.hxx"
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _TOOLKIT_AWT_VCLXWINDOW_HXX_
#include <toolkit/awt/vclxwindow.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef DBAUI_DATAVIEW_HXX
#include "dataview.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _VCL_STDTEXT_HXX
#include <vcl/stdtext.hxx>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLOSEABLE_HPP_
#include <com/sun/star/util/XCloseable.hpp>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _DBAUI_COMMON_TYPES_HXX_
#include "commontypes.hxx"
#endif

#ifndef _SV_WAITOBJ_HXX
#include <vcl/waitobj.hxx>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef SVTOOLS_URIHELPER_HXX
#include <svtools/urihelper.hxx>
#endif
#ifndef _DBAUI_DATASOURCECONNECTOR_HXX_
#include "datasourceconnector.hxx"
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <svtools/moduleoptions.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XMODIFIABLE_HPP_
#include <com/sun/star/util/XModifiable.hpp>
#endif
#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#include <algorithm>

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::awt;
using namespace ::dbtools;
using namespace ::dbaui;
using namespace ::comphelper;

// -------------------------------------------------------------------------
#define ALL_FEATURES	-1

// -------------------------------------------------------------------------
typedef ::std::hash_map< sal_Int16, sal_Int16 > CommandHashMap;
typedef ::std::list< DispatchInformation > DispatchInfoList;

// -------------------------------------------------------------------------
const ::rtl::OUString& getConfirmDeletionURL()
{
    static const ::rtl::OUString sConfirmDeletionURL( RTL_CONSTASCII_USTRINGPARAM( ".uno:FormSlots/ConfirmDeletion" ) );
    return sConfirmDeletionURL;
}

// -------------------------------------------------------------------------
OGenericUnoController::OGenericUnoController(const Reference< XMultiServiceFactory >& _rM)
    :OGenericUnoController_COMPBASE(m_aMutex)
    ,m_aAsyncInvalidateAll(LINK(this, OGenericUnoController, OnAsyncInvalidateAll))
    ,m_aAsyncCloseTask(LINK(this, OGenericUnoController, OnAsyncCloseTask))
    ,m_xMultiServiceFacatory(_rM)
    ,m_bCurrentlyModified(sal_False)
    ,m_bFrameUiActive(sal_False)
    ,m_pView(NULL)
    ,m_bPreview(sal_False)
    ,m_bReadOnly(sal_False)
#if OSL_DEBUG_LEVEL >= 2
    ,m_bDescribingSupportedFeatures( false )
#endif
{
    try
    {
        m_xUrlTransformer = Reference< XURLTransformer > (_rM->createInstance(::rtl::OUString::createFromAscii("com.sun.star.util.URLTransformer")), UNO_QUERY);
    }
    catch(Exception&)
    {
    }
}

// -----------------------------------------------------------------------------
OGenericUnoController::~OGenericUnoController()
{
}

// -----------------------------------------------------------------------------
sal_Bool OGenericUnoController::Construct(Window* pParent)
{
    OSL_ENSURE( getView(), "the view is NULL!" );

    if ( getView() )
    {
        getView()->Construct();
        getView()->Show();
    }

#if OSL_DEBUG_LEVEL >= 2
    m_bDescribingSupportedFeatures = true;
#endif
    m_aSupportedFeatures.clear();
    describeSupportedFeatures();
#if OSL_DEBUG_LEVEL >= 2
    m_bDescribingSupportedFeatures = false;
#endif

    // create the database context
    DBG_ASSERT(m_xMultiServiceFacatory.is(), "OGenericUnoController::Construct need a service factory!");
    try
    {
        m_xDatabaseContext = Reference< XNameAccess >(m_xMultiServiceFacatory->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
    }
    catch(Exception&)
    {
        DBG_ERROR("OGenericUnoController::Construct: could not create (or start listening at) the database context!");
    }

    if (!m_xDatabaseContext.is())
    {		// at least notify the user. Though the whole component does not make any sense without the database context ...
        ShowServiceNotAvailableError(getView(), String(SERVICE_SDB_DATABASECONTEXT), sal_True);
    }
    return sal_True;
}
//------------------------------------------------------------------------------
IMPL_LINK(OGenericUnoController, OnAsyncInvalidateAll, void*, EMPTYARG)
{
    if ( !OGenericUnoController_COMPBASE::rBHelper.bInDispose && !OGenericUnoController_COMPBASE::rBHelper.bDisposed )
        InvalidateFeature_Impl();
    return 0L;
}
// -----------------------------------------------------------------------------
Reference< XWindow > OGenericUnoController::getComponentWindow() const
{
    return VCLUnoHelper::GetInterface( getView() );
}
// -----------------------------------------------------------------------------
void OGenericUnoController::impl_initialize(const Sequence< Any >& aArguments)
{
}
// -------------------------------------------------------------------------
void SAL_CALL OGenericUnoController::initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException)
{
    vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard(m_aMutex);

    Reference< XWindow >		xParent;
    Reference< XFrame > xFrame;

    PropertyValue aValue;
    const Any* pIter	= aArguments.getConstArray();
    const Any* pEnd 	= pIter + aArguments.getLength();

    for ( ; pIter != pEnd; ++pIter )
    {
        if ( ( *pIter >>= aValue ) && ( 0 == aValue.Name.compareToAscii( "Frame" ) ) )
        {
            aValue.Value >>= xFrame;
        }
        /* #i42316#
        else if ( ( *pIter >>= aValue ) && ( 0 == aValue.Name.compareToAscii( "ReadOnly" ) ) )
        {
            aValue.Value >>= m_bReadOnly;
        }
        */
        else if ( ( *pIter >>= aValue ) && ( 0 == aValue.Name.compareToAscii( "Preview" ) ) )
        {
            aValue.Value >>= m_bPreview;
            m_bReadOnly = sal_True;
        }
    }
    try
    {
        if ( xFrame.is() )
        {
            xParent = xFrame->getContainerWindow();
            VCLXWindow* pParentComponent = VCLXWindow::GetImplementation(xParent);
            Window* pParentWin = pParentComponent ? pParentComponent->GetWindow() : NULL;
            if (!pParentWin)
            {
                throw Exception(::rtl::OUString::createFromAscii("Parent window is null"),*this);
            }

            Construct( pParentWin );
        }
        else
        {
            OSL_ENSURE(0,"OGenericUnoController::initialize: Frame is null!");
        }
        ODataView* pView = getView();
        if ( (m_bReadOnly || m_bPreview) && pView )
            pView->EnableInput(FALSE);
        impl_initialize(aArguments);
    }
    catch(Exception& e)
    {
        // no one clears my view if I won't
        ::std::auto_ptr<Window> aTemp(m_pView);
        m_pView = NULL;
        throw e;
    }
    if ( xFrame.is() )
        xFrame->setComponent(getComponentWindow(), this);
}

//------------------------------------------------------------------------------
Any SAL_CALL OGenericUnoController::queryInterface(const Type& _rType) throw (RuntimeException)
{
    Any aReturn = OGenericUnoController_COMPBASE::queryInterface(_rType);
    if (!aReturn.hasValue())
        aReturn = OGenericUnoController_CTRBASE::queryInterface(_rType);
    return aReturn;
}

//------------------------------------------------------------------------------
void SAL_CALL OGenericUnoController::acquire(  ) throw ()
{
    OGenericUnoController_COMPBASE::acquire();
}

//------------------------------------------------------------------------------
void SAL_CALL OGenericUnoController::release(  ) throw ()
{
    OGenericUnoController_COMPBASE::release();
}

//------------------------------------------------------------------------------
Sequence< Type > SAL_CALL OGenericUnoController::getTypes(	) throw (RuntimeException)
{
    return ::comphelper::concatSequences(
        OGenericUnoController_COMPBASE::getTypes(),
        OGenericUnoController_CTRBASE::getTypes()
    );
}

//------------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL OGenericUnoController::getImplementationId(  ) throw (RuntimeException)
{
    static ::cppu::OImplementationId * pId = 0;
    if (! pId)
    {
        ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
        if (! pId)
        {
            static ::cppu::OImplementationId aId;
            pId = &aId;
        }
    }
    return pId->getImplementationId();
}

// -------------------------------------------------------------------------
sal_Bool OGenericUnoController::startFrameListening( )
{
    if ( m_xCurrentFrame.is() )
        m_xCurrentFrame->addFrameActionListener( static_cast< XFrameActionListener* >( this ) );
    return m_xCurrentFrame.is();
}

// -------------------------------------------------------------------------
void OGenericUnoController::stopFrameListening( )
{
    if ( m_xCurrentFrame.is() )
        m_xCurrentFrame->removeFrameActionListener( static_cast< XFrameActionListener* >( this ) );
}

// -------------------------------------------------------------------------
void OGenericUnoController::disposing(const EventObject& Source) throw( RuntimeException )
{
    // our frame ?
    Reference< XFrame >  xSourceFrame(Source.Source, UNO_QUERY);
    if ( xSourceFrame == m_xCurrentFrame )
        stopFrameListening( );
}
//------------------------------------------------------------------------
void OGenericUnoController::modified(const EventObject& aEvent) throw( RuntimeException )
{
    ::osl::MutexGuard aGuard(m_aMutex);	
    if ( !isDataSourceReadOnly() )
    {
        Reference<XModifiable> xModi(aEvent.Source,UNO_QUERY);
        if ( xModi.is() )
            m_bCurrentlyModified = xModi->isModified(); // can only be reset by save
        else
            m_bCurrentlyModified = sal_True;
    }
    InvalidateFeature(ID_BROWSER_SAVEDOC);
    InvalidateFeature(ID_BROWSER_UNDO);
}
// -----------------------------------------------------------------------
void OGenericUnoController::attachFrame(const Reference< XFrame > & xFrame) throw( RuntimeException )
{
    ::osl::MutexGuard aGuard(m_aMutex);	
    stopFrameListening( );

    m_xCurrentFrame = xFrame;

    if ( startFrameListening( ) )
        m_bFrameUiActive = m_xCurrentFrame->isActive();
    loadMenu(xFrame);
    if ( m_xCurrentFrame.is() )
        updateTitle();
    if ( getView() )
        getView()->attachFrame(xFrame);
}
// -----------------------------------------------------------------------------
void OGenericUnoController::updateTitle()
{
}
// -----------------------------------------------------------------------------
struct CommandCollector : public ::std::unary_function< SupportedFeatures::value_type, void>
{
    sal_uInt16  m_nFeature;
    StringBag&  m_rFeatureCommands;
    CommandCollector( sal_uInt16 _nFeature, StringBag& _rFeatureCommands )
        :m_nFeature        ( _nFeature         )
        ,m_rFeatureCommands( _rFeatureCommands )
    {
    }

    void operator() ( const SupportedFeatures::value_type& lhs )
    {
        if ( lhs.second.nFeatureId == m_nFeature )
            m_rFeatureCommands.insert( lhs.first );
    }
};

// -----------------------------------------------------------------------
void OGenericUnoController::ImplBroadcastFeatureState(const ::rtl::OUString& _rFeature, const Reference< XStatusListener > & xListener, sal_Bool _bIgnoreCache)
{
    sal_uInt16 nFeat = m_aSupportedFeatures[ _rFeature ].nFeatureId;
    FeatureState aFeatState( GetState( nFeat ) );

    FeatureState& rCachedState = m_aStateCache[nFeat];	// creates if neccessary

    if(!_bIgnoreCache)
    {
        // check if we really need to notify the listeners : this method may be called much more often than needed, so check
        // the cached state of the feature
        sal_Bool bAlreadyCached = (m_aStateCache.find(nFeat) != m_aStateCache.end());
        if (bAlreadyCached && (rCachedState.bEnabled == aFeatState.bEnabled))
        {	// the enabled flag hasn't changed, maybe the state ?
            if (rCachedState.aState.getValueTypeClass() == aFeatState.aState.getValueTypeClass())
            {	// at least the type of the state hasn't
                sal_Bool bEqualValue = sal_False;
                switch (rCachedState.aState.getValueTypeClass())
                {
                    case TypeClass_VOID:
                        bEqualValue = !aFeatState.aState.hasValue();
                        break;
                    case TypeClass_BOOLEAN:
                        bEqualValue = ::comphelper::getBOOL(rCachedState.aState) == ::comphelper::getBOOL(aFeatState.aState);
                        break;
                    case TypeClass_SHORT:
                        bEqualValue = ::comphelper::getINT16(rCachedState.aState) == ::comphelper::getINT16(aFeatState.aState);
                        break;
                    case TypeClass_LONG:
                        bEqualValue = ::comphelper::getINT32(rCachedState.aState) == ::comphelper::getINT32(aFeatState.aState);
                        break;
                    case TypeClass_STRING:
                        bEqualValue = ::comphelper::getString(rCachedState.aState).equals(::comphelper::getString(aFeatState.aState));
                        break;
                    default:
                        DBG_ERROR("OGenericUnoController::ImplBroadcastFeatureState : unknown state type (not implemented yet) !");
                        break;
                }
                if (bEqualValue)
                    return;
            }
        }
    }
    rCachedState = aFeatState;

    FeatureStateEvent aEvent;
    aEvent.FeatureURL.Complete = _rFeature;
    if (m_xUrlTransformer.is())
        m_xUrlTransformer->parseStrict(aEvent.FeatureURL);
    aEvent.Source		= (XDispatch*)this;
    aEvent.IsEnabled	= aFeatState.bEnabled;
    aEvent.Requery		= aFeatState.bRequery;
    aEvent.State		= aFeatState.aState;

    // a special listener ?
    if (xListener.is())
        xListener->statusChanged(aEvent);
    else
    {	// no -> iterate through all listeners responsible for the URL
        StringBag aFeatureCommands;
        ::std::for_each(
            m_aSupportedFeatures.begin(),
            m_aSupportedFeatures.end(),
            CommandCollector( nFeat, aFeatureCommands )
        );

        // it is possible that listeners are registered or revoked while
        // we are notifying them, so we must use a copy of m_arrStatusListener, not
        // m_arrStatusListener itself
        // #121276# / 2005-05-19 / frank.schoenheit@sun.com
        Dispatch aNotifyLoop( m_arrStatusListener );
        DispatchIterator iterSearch = aNotifyLoop.begin();
        DispatchIterator iterEnd = aNotifyLoop.end();

        while (iterSearch != iterEnd)
        {
            DispatchTarget& rCurrent = *iterSearch;
            if ( aFeatureCommands.find( rCurrent.aURL.Complete ) != aFeatureCommands.end() )
            {
                aEvent.FeatureURL.Complete = rCurrent.aURL.Complete;
                if (m_xUrlTransformer.is())
                    m_xUrlTransformer->parseStrict(aEvent.FeatureURL);
                rCurrent.xListener->statusChanged(aEvent);
            }
            ++iterSearch;
        }
    }

}

//------------------------------------------------------------------------------
sal_Bool OGenericUnoController::isFeatureSupported( sal_Int32 _nId )
{
    SupportedFeatures::iterator aFeaturePos = ::std::find_if(
        m_aSupportedFeatures.begin(),
        m_aSupportedFeatures.end(),
        ::std::bind2nd( SupportedFeaturesEqualId(), _nId )
    );

    return ( m_aSupportedFeatures.end() != aFeaturePos && aFeaturePos->first.getLength());
}

// -----------------------------------------------------------------------
void OGenericUnoController::InvalidateFeature(const ::rtl::OUString& _rURLPath, const Reference< XStatusListener > & _xListener, sal_Bool _bForceBroadcast)
{
    ImplInvalidateFeature( m_aSupportedFeatures[ _rURLPath ].nFeatureId, _xListener, _bForceBroadcast );
}

// -----------------------------------------------------------------------------
void OGenericUnoController::InvalidateFeature_Impl()
{
#ifdef DBG_UTIL
    static sal_Int32 s_nRecursions = 0;
    ++s_nRecursions;
#endif

    sal_Bool bEmpty = sal_True;
    FeaturePair aNextFeature;
    {
        ::osl::MutexGuard aGuard( m_aFeatureMutex);
        bEmpty = m_aFeaturesToInvalidate.empty();
        if (!bEmpty)
            aNextFeature = m_aFeaturesToInvalidate.front();
    }
    while(!bEmpty)
    {
        if ( ALL_FEATURES == aNextFeature.nId )
        {
            InvalidateAll_Impl();
            break;
        }
        else
        {
            SupportedFeatures::iterator aFeaturePos = ::std::find_if(
                m_aSupportedFeatures.begin(),
                m_aSupportedFeatures.end(),
                ::std::bind2nd( SupportedFeaturesEqualId(), aNextFeature.nId )
            );

#if OSL_DEBUG_LEVEL > 0
            if ( m_aSupportedFeatures.end() == aFeaturePos )
            {
                ::rtl::OString sMessage( "OGenericUnoController::InvalidateFeature_Impl: feature id " );
                sMessage += ::rtl::OString::valueOf( aNextFeature.nId );
                sMessage += ::rtl::OString( " has been invalidated, but is not supported!" );
                OSL_ENSURE( false, sMessage.getStr() );
            }
#endif
            if ( m_aSupportedFeatures.end() != aFeaturePos )
                // we really know this feature
                ImplBroadcastFeatureState( aFeaturePos->first, aNextFeature.xListener, aNextFeature.bForceBroadcast );
        }

        ::osl::MutexGuard aGuard( m_aFeatureMutex);
        m_aFeaturesToInvalidate.pop_front();
        bEmpty = m_aFeaturesToInvalidate.empty();
        if (!bEmpty)
            aNextFeature = m_aFeaturesToInvalidate.front();
    }

#ifdef DBG_UTIL
    --s_nRecursions;
#endif
}

// -----------------------------------------------------------------------
void OGenericUnoController::ImplInvalidateFeature( sal_Int32 _nId, const Reference< ::com::sun::star::frame::XStatusListener >& _xListener, sal_Bool _bForceBroadcast )
{
    FeaturePair aPair;
    aPair.nId				= _nId;
    aPair.xListener 		= _xListener;
    aPair.bForceBroadcast	= _bForceBroadcast;

    sal_Bool bWasEmpty;
    {
        ::osl::MutexGuard aGuard( m_aFeatureMutex);
        bWasEmpty = m_aFeaturesToInvalidate.empty();
        m_aFeaturesToInvalidate.push_back(aPair);
    }

    if ( bWasEmpty )
        m_aAsyncInvalidateAll.Call();
}

// -----------------------------------------------------------------------
void OGenericUnoController::InvalidateFeature(sal_uInt16 _nId, const Reference< XStatusListener > & _xListener, sal_Bool _bForceBroadcast)
{
    ImplInvalidateFeature( _nId, _xListener, _bForceBroadcast );
}

// -----------------------------------------------------------------------
void OGenericUnoController::InvalidateAll()
{
    ImplInvalidateFeature( ALL_FEATURES, NULL, sal_True );
}

// -----------------------------------------------------------------------------
void OGenericUnoController::InvalidateAll_Impl()
{
    // ---------------------------------
    // invalidate all aupported features
    
    for (   SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.begin();
            aIter != m_aSupportedFeatures.end();
            ++aIter
        )
        ImplBroadcastFeatureState( aIter->first, NULL, sal_True );

    {
        ::osl::MutexGuard aGuard( m_aFeatureMutex);
        DBG_ASSERT(m_aFeaturesToInvalidate.size(), "OGenericUnoController::InvalidateAll_Impl: to be called from within InvalidateFeature_Impl only!");
        m_aFeaturesToInvalidate.pop_front();
        if(!m_aFeaturesToInvalidate.empty())
            m_aAsyncInvalidateAll.Call();
    }
}

// -----------------------------------------------------------------------
Reference< XDispatch >	OGenericUnoController::queryDispatch(const URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags) throw( RuntimeException )
{
    Reference< XDispatch > xReturn;

    // URL's we can handle ourself?
    if	(	aURL.Complete.equals( getConfirmDeletionURL() )
        ||	( m_aSupportedFeatures.find( aURL.Complete ) != m_aSupportedFeatures.end() )
        )
    {
        xReturn = static_cast< XDispatch* >( this );
    }
    // no? -> ask the slave dispatcher
    else if ( m_xSlaveDispatcher.is() )
    {
        xReturn = m_xSlaveDispatcher->queryDispatch(aURL, aTargetFrameName, nSearchFlags);
    }

    // outta here
    return xReturn;
}

// -----------------------------------------------------------------------
Sequence< Reference< XDispatch > > OGenericUnoController::queryDispatches(const Sequence< DispatchDescriptor >& aDescripts) throw( RuntimeException )
{
    Sequence< Reference< XDispatch > > aReturn;
    sal_Int32 nLen = aDescripts.getLength();
    if ( nLen )
    {
        aReturn.realloc( nLen );
                Reference< XDispatch >* pReturn 	= aReturn.getArray();
        const	Reference< XDispatch >* pReturnEnd	= aReturn.getArray() + nLen;
        const	DispatchDescriptor* 	pDescripts	= aDescripts.getConstArray();

        for ( ; pReturn != pReturnEnd; ++ pReturn, ++pDescripts )
        {
            *pReturn = queryDispatch( pDescripts->FeatureURL, pDescripts->FrameName, pDescripts->SearchFlags );
        }
    }

    return aReturn;
}

// -----------------------------------------------------------------------
Reference< XDispatchProvider >	OGenericUnoController::getSlaveDispatchProvider(void) throw( RuntimeException )
{
    return m_xSlaveDispatcher;
}

// -----------------------------------------------------------------------
void OGenericUnoController::setSlaveDispatchProvider(const Reference< XDispatchProvider > & _xNewProvider) throw( RuntimeException )
{
    m_xSlaveDispatcher = _xNewProvider;
}

// -----------------------------------------------------------------------
Reference< XDispatchProvider >	OGenericUnoController::getMasterDispatchProvider(void) throw( RuntimeException )
{
    return m_xMasterDispatcher;
}

// -----------------------------------------------------------------------
void OGenericUnoController::setMasterDispatchProvider(const Reference< XDispatchProvider > & _xNewProvider) throw( RuntimeException )
{
    m_xMasterDispatcher = _xNewProvider;
}

// -----------------------------------------------------------------------
void OGenericUnoController::dispatch(const URL& _aURL, const Sequence< PropertyValue >& aArgs) throw(RuntimeException)
{
    executeUnChecked(_aURL,aArgs);
}

// -----------------------------------------------------------------------
void OGenericUnoController::addStatusListener(const Reference< XStatusListener > & aListener, const URL& _rURL) throw(RuntimeException)
{
    // remeber the listener together with the URL
    m_arrStatusListener.insert(m_arrStatusListener.end(), DispatchTarget(_rURL, aListener));
    // initially broadcast the state
    ImplBroadcastFeatureState(_rURL.Complete, aListener, sal_True);
        // force the new state to be broadcasted to the new listener
}

// -----------------------------------------------------------------------
void OGenericUnoController::removeStatusListener(const Reference< XStatusListener > & aListener, const URL& _rURL) throw(RuntimeException)
{
    DispatchIterator iterSearch = m_arrStatusListener.begin();

    sal_Bool bRemoveForAll = (_rURL.Complete.getLength() == 0);
    while ( iterSearch != m_arrStatusListener.end() )
    {
        DispatchTarget& rCurrent = *iterSearch;
        if	(	(rCurrent.xListener == aListener)
            &&	(	bRemoveForAll
                ||	(rCurrent.aURL.Complete.equals(_rURL.Complete))
                )
            )
        {
            m_arrStatusListener.erase( iterSearch );
            if (!bRemoveForAll)
                // remove the listener only for the given URL, so we can exit the loop after deletion
                break;
        }
        else
            ++iterSearch;
    }

    SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.find(_rURL.Complete);
    if (aIter != m_aSupportedFeatures.end())
    {	// clear the cache for that feature
        StateCacheIterator aCachePos = m_aStateCache.find( aIter->second.nFeatureId );
        if ( aCachePos != m_aStateCache.end() )
            m_aStateCache.erase( aCachePos );
    }

    // now remove the listener from the deque
    ::osl::MutexGuard aGuard( m_aFeatureMutex);
    m_aFeaturesToInvalidate.erase(
        ::std::remove_if(	m_aFeaturesToInvalidate.begin(),
                            m_aFeaturesToInvalidate.end(),
                            ::std::bind2nd(FeaturePairFunctor(),aListener))
        ,m_aFeaturesToInvalidate.end());
}

// -----------------------------------------------------------------------
void OGenericUnoController::disposing()
{
    {
        EventObject aDisposeEvent;
        aDisposeEvent.Source = static_cast<XWeak*>(this);
        Dispatch aStatusListener = m_arrStatusListener;
        Dispatch::iterator aEnd = aStatusListener.end();
        for (Dispatch::iterator aIter = aStatusListener.begin(); aIter != aEnd; ++aIter)
        {		
            aIter->xListener->disposing(aDisposeEvent);
        }
        m_arrStatusListener.clear();
    }

    m_xDatabaseContext = NULL;
    {
        ::osl::MutexGuard aGuard( m_aFeatureMutex);
        m_aAsyncInvalidateAll.CancelCall();
        m_aFeaturesToInvalidate.clear();
    }

    // check out from all the objects we are listening
    // the frame
    stopFrameListening( );
}

// -----------------------------------------------------------------------
void OGenericUnoController::addEventListener(const Reference< XEventListener > & aListener) throw(RuntimeException)
{
    OGenericUnoController_COMPBASE::addEventListener(aListener);
}

// -----------------------------------------------------------------------
void OGenericUnoController::removeEventListener(const Reference< XEventListener > & aListener) throw(RuntimeException)
{
    OGenericUnoController_COMPBASE::removeEventListener(aListener);
}

//------------------------------------------------------------------------------
void OGenericUnoController::frameAction(const FrameActionEvent& aEvent) throw( RuntimeException )
{
    if ((XFrame*)aEvent.Frame.get() == (XFrame*)m_xCurrentFrame.get())
        m_bFrameUiActive =	( FrameAction_FRAME_UI_ACTIVATED == aEvent.Action )
                        ||	( FrameAction_FRAME_ACTIVATED == aEvent.Action );
}

//------------------------------------------------------------------------------
void OGenericUnoController::implDescribeSupportedFeature( const sal_Char* _pAsciiCommandURL,
        sal_uInt16 _nFeatureId, sal_Int16 _nCommandGroup )
{
#if OSL_DEBUG_LEVEL >= 2
    OSL_ENSURE( m_bDescribingSupportedFeatures, "OGenericUnoController::implDescribeSupportedFeature: bad timing for this call!" );
#endif

    ControllerFeature aFeature;
    aFeature.Command = ::rtl::OUString::createFromAscii( _pAsciiCommandURL );
    aFeature.nFeatureId = _nFeatureId;
    aFeature.GroupId = _nCommandGroup;

#if OSL_DEBUG_LEVEL > 0
    OSL_ENSURE( m_aSupportedFeatures.find( aFeature.Command ) == m_aSupportedFeatures.end(),
        "OGenericUnoController::implDescribeSupportedFeature: this feature is already there!" );
#endif
    m_aSupportedFeatures[ aFeature.Command ] = aFeature;
}

//------------------------------------------------------------------------------
void OGenericUnoController::describeSupportedFeatures()
{
    // add all supported features
    implDescribeSupportedFeature( ".uno:Copy", ID_BROWSER_COPY, CommandGroup::EDIT );
    implDescribeSupportedFeature( ".uno:Cut", ID_BROWSER_CUT, CommandGroup::EDIT );
    implDescribeSupportedFeature( ".uno:Paste", ID_BROWSER_PASTE, CommandGroup::EDIT );
    implDescribeSupportedFeature( ".uno:ClipboardFormatItems", ID_BROWSER_CLIPBOARD_FORMAT_ITEMS );
    implDescribeSupportedFeature( ".uno:DSBEditDoc", ID_BROWSER_EDITDOC, CommandGroup::DOCUMENT );
}

//------------------------------------------------------------------------------
FeatureState OGenericUnoController::GetState(sal_uInt16 nId) const
{
    FeatureState aReturn;
        // (disabled automatically)

    try
    {
        switch (nId)
        {
            case ID_BROWSER_UNDO:
            case ID_BROWSER_SAVEDOC:
                aReturn.bEnabled = sal_True;
                break;
            case 99:
                aReturn.bEnabled = sal_False;
                break;
        }
    }
    catch(Exception& e)
    {
#if DBG_UTIL
        String sMessage("OGenericUnoController::GetState(", RTL_TEXTENCODING_ASCII_US);
        sMessage += String::CreateFromInt32(nId);
        sMessage.AppendAscii("): caught an exception ! message : ");
        sMessage += (const sal_Unicode*)e.Message;
        DBG_ERROR(ByteString(sMessage, gsl_getSystemTextEncoding()).GetBuffer());
#else
        e;	// make compiler happy
#endif
    }

    return aReturn;
}
//------------------------------------------------------------------------------
URL OGenericUnoController::getURLForId(sal_Int32 _nId) const
{
    URL aReturn;
    if ( m_xUrlTransformer.is() )
    {
        SupportedFeatures::const_iterator aIter = ::std::find_if(
            m_aSupportedFeatures.begin(),
            m_aSupportedFeatures.end(),
            ::std::bind2nd( SupportedFeaturesEqualId(), _nId )
        );

        if ( m_aSupportedFeatures.end() != aIter && aIter->first.getLength() )
        {
            aReturn.Complete = aIter->first;
            m_xUrlTransformer->parseStrict( aReturn );
        }
    }
    return aReturn;
}

//-------------------------------------------------------------------------
sal_Bool SAL_CALL OGenericUnoController::supportsService(const ::rtl::OUString& ServiceName) throw(RuntimeException)
{
    Sequence< ::rtl::OUString > aSupported(getSupportedServiceNames());

    const ::rtl::OUString* pArray = aSupported.getConstArray();
    const ::rtl::OUString* pArrayEnd = aSupported.getConstArray() + aSupported.getLength();

    for ( ;( pArray != pArrayEnd ) && !pArray->equals( ServiceName ); ++pArray )
        ;
    return pArray != pArrayEnd;
}

// -----------------------------------------------------------------------------
void OGenericUnoController::startConnectionListening(const Reference< XConnection >& _rxConnection)
{
    // we have to remove ourself before dispoing the connection
    Reference< XComponent >  xComponent(_rxConnection, UNO_QUERY);
    if (xComponent.is())
        xComponent->addEventListener(static_cast<XFrameActionListener*>(this));
}

// -----------------------------------------------------------------------------
void OGenericUnoController::stopConnectionListening(const Reference< XConnection >& _rxConnection)
{
    // we have to remove ourself before dispoing the connection
    Reference< XComponent >  xComponent(_rxConnection, UNO_QUERY);
    if (xComponent.is())
        xComponent->removeEventListener(static_cast<XFrameActionListener*>(this));
}
// -----------------------------------------------------------------------------
Reference< XConnection > OGenericUnoController::connect(
            const Reference< XDataSource>& _xDataSource
            ,sal_Bool _bStartListening
        )
{
    WaitObject aWaitCursor(getView());

    const ::rtl::OUString sNoContext;
    ODatasourceConnector aConnector(m_xMultiServiceFacatory, getView(), sNoContext, sNoContext);
    Reference<XConnection> xConnection = aConnector.connect(_xDataSource);

    // be notified when connection is in disposing
    if (_bStartListening)
        startConnectionListening(xConnection);

    return xConnection;
}
// -----------------------------------------------------------------------------
Reference<XConnection> OGenericUnoController::connect(const ::rtl::OUString& _rDataSourceName, sal_Bool _bStartListening)
{
    const ::rtl::OUString sNoContext;
    return connect( _rDataSourceName, sNoContext, sNoContext, _bStartListening );
}

// -----------------------------------------------------------------------------
Reference< XConnection > OGenericUnoController::connect(
    const ::rtl::OUString& _rDataSourceName, const ::rtl::OUString& _rContextInformation,
    const ::rtl::OUString& _rContextDetails, sal_Bool _bStartListening )
{
    WaitObject aWaitCursor(getView());

    ODatasourceConnector aConnector(m_xMultiServiceFacatory, getView(), _rContextInformation, _rContextDetails);
    Reference<XConnection> xConnection = aConnector.connect(_rDataSourceName);

    // be notified when connection is in disposing
    if (_bStartListening)
        startConnectionListening(xConnection);

    return xConnection;
}

// -----------------------------------------------------------------------------
void OGenericUnoController::showError(const SQLExceptionInfo& _rInfo)
{
    ::dbaui::showError(_rInfo,getView(),getORB());
}
// -----------------------------------------------------------------------------
Reference< ::com::sun::star::frame::XLayoutManager > OGenericUnoController::getLayoutManager(const Reference< XFrame >& _xFrame) const
{
    Reference< XPropertySet > xPropSet( _xFrame, UNO_QUERY );
    Reference< ::com::sun::star::frame::XLayoutManager > xLayoutManager;
    if ( xPropSet.is() )
    {
        try
        {
            xLayoutManager.set(xPropSet->getPropertyValue( rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "LayoutManager" ))),UNO_QUERY);
        }
        catch ( Exception& )
        {
        }
    }
    return xLayoutManager;
}
// -----------------------------------------------------------------------------
void OGenericUnoController::loadMenu(const Reference< XFrame >& _xFrame)
{
    
    Reference< ::com::sun::star::frame::XLayoutManager > xLayoutManager = getLayoutManager(_xFrame);
    
        
    if ( xLayoutManager.is() )
    {
        xLayoutManager->lock();
        xLayoutManager->createElement( rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "private:resource/menubar/menubar" )));
        xLayoutManager->createElement( rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "private:resource/toolbar/toolbar" )));
        xLayoutManager->unlock();
        xLayoutManager->doLayout();
    }

    onLoadedMenu( xLayoutManager );
}

// -----------------------------------------------------------------------------
void OGenericUnoController::onLoadedMenu(const Reference< ::com::sun::star::frame::XLayoutManager >& _xLayoutManager)
{
    // not interested in
}

// -----------------------------------------------------------------------------
void OGenericUnoController::closeTask()
{
    m_aAsyncCloseTask.Call();
}
// -----------------------------------------------------------------------------
IMPL_LINK(OGenericUnoController, OnAsyncCloseTask, void*, EMPTYARG)
{
    if(!OGenericUnoController_COMPBASE::rBHelper.bInDispose)
    {
        try
        {
/*AS           // #104032# OJ
            URL aURL;
            aURL.Complete = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:CloseDoc"));
            if (m_xUrlTransformer.is())
                m_xUrlTransformer->parseStrict(aURL);
            Reference< XDispatchProvider > xDispProv(m_xCurrentFrame, UNO_QUERY);
            Reference< XDispatch > xCloseDispatch;
            if (xDispProv.is())
                xCloseDispatch = xDispProv->queryDispatch(aURL, m_xCurrentFrame->getName(), FrameSearchFlag::SELF);
            OSL_ENSURE(xCloseDispatch.is(), "SbaTableQueryBrowser::OnAsyncCloseTask: could not get a dispatcher!");
            if ( xCloseDispatch.is() && xCloseDispatch != *this )
            {
                xCloseDispatch->dispatch(aURL, Sequence< PropertyValue >());
            }
            else*/
            {
                Reference< ::com::sun::star::util::XCloseable > xCloseable(m_xCurrentFrame,UNO_QUERY);
                if(xCloseable.is())
                    xCloseable->close(sal_False); // false - holds the owner ship for this frame inside this object!
            }
        }
        catch(const Exception&) {}
    }
    return 0L;
}
// -----------------------------------------------------------------------------
Any SAL_CALL OGenericUnoController::getViewData(void) throw( RuntimeException )
{
    return Any();
}
// -----------------------------------------------------------------------------
void SAL_CALL OGenericUnoController::restoreViewData(const Any& Data) throw( RuntimeException )
{
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OGenericUnoController::attachModel(const Reference< XModel > & xModel) throw( RuntimeException )
{
    return sal_False;
}
// -----------------------------------------------------------------------------
void OGenericUnoController::executeUnChecked(const ::com::sun::star::util::URL& _rCommand, const Sequence< PropertyValue >& aArgs)
{
    SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.find( _rCommand.Complete );
    if (aIter != m_aSupportedFeatures.end())
        Execute( aIter->second.nFeatureId, aArgs );
}
// -----------------------------------------------------------------------------
void OGenericUnoController::executeChecked(const ::com::sun::star::util::URL& _rCommand, const Sequence< PropertyValue >& aArgs)
{
    SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.find( _rCommand.Complete );
    if ( aIter != m_aSupportedFeatures.end() )
    {
        sal_uInt16 nFeatureId = aIter->second.nFeatureId;
        if ( GetState( nFeatureId ).bEnabled )
            Execute( nFeatureId, aArgs );
    }
}
// -----------------------------------------------------------------------------
//------------------------------------------------------------------------------
namespace
{
    ::rtl::OUString lcl_getModuleHelpModuleName( const Reference< XFrame >& _rxFrame )
    {
        const sal_Char* pReturn = NULL;

        try
        {
            // get the model of the document in the given frame
            Reference< XController > xController;
            if ( _rxFrame.is() )
                xController = _rxFrame->getController();
            Reference< XModel > xModel;
            if ( xController.is() )
                xModel = xController->getModel();
            Reference< XServiceInfo > xSI( xModel, UNO_QUERY );

            if ( !xSI.is() )
            {	// try to go up the frame hierarchy

                Reference< XFrame > xParentFrame;
                if ( _rxFrame.is() )
                    xParentFrame = xParentFrame.query( _rxFrame->getCreator() );
                // did we find a parent frame? Which is no top-level frame?
                if ( xParentFrame.is() && !_rxFrame->isTop() )
                    // TODO: to prevent framework assertions, re-insert this "isTop" once 98303 is fixed
                    return lcl_getModuleHelpModuleName( xParentFrame );
            }
            else
            {
#if OSL_DEBUG_LEVEL > 0
                Sequence< ::rtl::OUString > sServiceNames = xSI->getSupportedServiceNames();
                const ::rtl::OUString* pLoop = sServiceNames.getConstArray();
                for ( sal_Int32 i=0; i<sServiceNames.getLength(); ++i, ++pLoop )
                {
                    sal_Int32 nDummy = 0;
                }
#endif

                // check which service we know ....
                static const sal_Char* pTransTable[] = {
                    "com.sun.star.sdb.OfficeDatabaseDocument","sdatabase",
                    "com.sun.star.text.TextDocument",	"swriter",
                    "com.sun.star.sheet.SpreadsheetDocument", "scalc",
                    "com.sun.star.presentation.PresentationDocument", "simpress",
                    "com.sun.star.drawing.DrawingDocument", "sdraw",
                    "com.sun.star.formula.FormularProperties", "smath",
                    "com.sun.star.chart.ChartDocument", "schart"
                };
                OSL_ENSURE( ( sizeof( pTransTable ) / sizeof( pTransTable[0] ) ) % 2 == 0,
                    "lcl_getModuleHelpModuleName: odd size of translation table!" );

                // loop through the table
                sal_Int32 nTableEntries = ( sizeof( pTransTable ) / sizeof( pTransTable[0] ) ) / 2;
                const sal_Char** pDocumentService = pTransTable;
                const sal_Char** pHelpModuleName = pTransTable + 1;
                for ( sal_Int32 j=0; j<nTableEntries; ++j )
                {
                    if ( xSI->supportsService( ::rtl::OUString::createFromAscii( *pDocumentService ) ) )
                    {	// found a table entry which matches the model's services
                        pReturn = *pHelpModuleName;
                        break;
                    }

                    ++pDocumentService; ++pDocumentService;
                    ++pHelpModuleName; ++pHelpModuleName;
                }
            }

            if ( !pReturn )
            {
                // could not determine the document type we're living in
                // ->fallback
                SvtModuleOptions aModOpt;
                if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SWRITER ) )
                    pReturn = "swriter";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SDATABASE ) )
                    pReturn = "sdatabase";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SCALC ) )
                    pReturn = "scalc";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SIMPRESS ) )
                    pReturn = "simpress";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SDRAW ) )
                    pReturn = "sdraw";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SMATH ) )
                    pReturn = "smath";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SCHART ) )
                    pReturn = "schart";
                else if ( aModOpt.IsModuleInstalled( SvtModuleOptions::E_SBASIC ) )
                    pReturn = "sbasic";
                else
                {
                    OSL_ENSURE( sal_False, "lcl_getModuleHelpModuleName: no installed module found" );
                }
            }
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "lcl_getModuleHelpModuleName: caught an exception!" );
        }

        if ( !pReturn )
            pReturn = "swriter";

        return ::rtl::OUString::createFromAscii( pReturn );
    }
}

//------------------------------------------------------------------------------
void OGenericUnoController::openHelpAgent(sal_Int32 _nHelpId)
{
    try
    {
        URL aURL = createHelpAgentURL(lcl_getModuleHelpModuleName( getFrame() ),_nHelpId);
        if (m_xUrlTransformer.is())
            m_xUrlTransformer->parseStrict(aURL);

        Reference< XDispatchProvider > xDispProv(m_xCurrentFrame, UNO_QUERY);
        Reference< XDispatch > xHelpDispatch;
        if (xDispProv.is())
            xHelpDispatch = xDispProv->queryDispatch(aURL, ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("_helpagent")), FrameSearchFlag::PARENT | FrameSearchFlag::SELF);
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
// -----------------------------------------------------------------------------
Reference< ::com::sun::star::awt::XWindow> OGenericUnoController::getTopMostContainerWindow() const
{
    Reference< ::com::sun::star::awt::XWindow> xWindow;
    // get the top most window
    if ( m_xCurrentFrame.is() )
    {
        xWindow = m_xCurrentFrame->getContainerWindow();
        Reference<XFrame> xFrame = m_xCurrentFrame;
        while ( xFrame.is() && !xFrame->isTop() )
        {
            xFrame.set(xFrame->getCreator(),UNO_QUERY);
        }
        if ( xFrame.is() )
            xWindow = xFrame->getContainerWindow();
    }
    return xWindow;
}
// -----------------------------------------------------------------------------
void OGenericUnoController::setTitle(const ::rtl::OUString& _sName)
{
    try
    {
        Reference<XPropertySet> xProp(m_xCurrentFrame,UNO_QUERY);
        if ( xProp.is() && xProp->getPropertySetInfo()->hasPropertyByName(PROPERTY_TITLE) )
        {
            xProp->setPropertyValue(PROPERTY_TITLE,makeAny(_sName));
        }
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while setting the title!");
    }
}
// -----------------------------------------------------------------------------
void OGenericUnoController::executeChecked(sal_uInt16 _nCommandId, const Sequence< PropertyValue >& aArgs)
{
    if ( isCommandEnabled(_nCommandId) )
        Execute(_nCommandId, aArgs);
}

// -----------------------------------------------------------------------------
sal_Bool OGenericUnoController::isCommandEnabled(sal_uInt16 _nCommandId) const
{
    return GetState( _nCommandId ).bEnabled;
}

// -----------------------------------------------------------------------------
sal_Bool OGenericUnoController::isCommandEnabled(const ::com::sun::star::util::URL& _rCommand) const
{
    OSL_ENSURE(_rCommand.Complete.getLength(),"Empty command url!");
    sal_Bool bIsEnabled = sal_False;
    SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.find( _rCommand.Complete );
    if ( aIter != m_aSupportedFeatures.end() )
        bIsEnabled = isCommandEnabled( aIter->second.nFeatureId );

    return bIsEnabled;
}

// -----------------------------------------------------------------------------
Sequence< ::sal_Int16 > SAL_CALL OGenericUnoController::getSupportedCommandGroups() throw (RuntimeException)
{
    CommandHashMap aCmdHashMap;
    for (   SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.begin();
            aIter != m_aSupportedFeatures.end();
            ++aIter
        )
        aCmdHashMap.insert( CommandHashMap::value_type( aIter->second.GroupId, 0 ));

    Sequence< sal_Int16 > aCommandGroups( aCmdHashMap.size() );
    ::std::transform( aCmdHashMap.begin(),
        aCmdHashMap.end(),
        aCommandGroups.getArray(),
        ::std::select1st< CommandHashMap::value_type >()
    );

    return aCommandGroups;
}

// -----------------------------------------------------------------------------
Sequence< DispatchInformation > SAL_CALL OGenericUnoController::getConfigurableDispatchInformation( ::sal_Int16 CommandGroup ) throw (RuntimeException)
{
    DispatchInfoList    aInformationList;
    DispatchInformation aDispatchInfo;
    for (   SupportedFeatures::const_iterator aIter = m_aSupportedFeatures.begin();
            aIter != m_aSupportedFeatures.end();
            ++aIter
        )
    {
        if ( sal_Int16( aIter->second.GroupId ) == CommandGroup )
        {
            aDispatchInfo = aIter->second;
            aInformationList.push_back( aDispatchInfo );
        }
    }

    Sequence< DispatchInformation > aInformation( aInformationList.size() );
    ::std::transform( aInformationList.begin(),
        aInformationList.end(),
        aInformation.getArray(),
        ::std::identity< DispatchInformation >()
    );

    return aInformation;
}
