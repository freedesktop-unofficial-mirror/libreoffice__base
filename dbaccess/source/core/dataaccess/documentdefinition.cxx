/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: documentdefinition.cxx,v $
 *
 *  $Revision: 1.48 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:38:09 $
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

#ifndef _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_
#include "documentdefinition.hxx"
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef DBACORE_SDBCORETOOLS_HXX
#include "sdbcoretools.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_MEDIADESCRIPTOR_HXX_
#include <comphelper/mediadescriptor.hxx>
#endif
#ifndef _COMPHELPER_CLASSIDS_HXX
#include <comphelper/classids.hxx>
#endif
#ifndef _COM_SUN_STAR_AWT_XTOPWINDOW_HPP_
#include <com/sun/star/awt/XTopWindow.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_SIZE_HPP_
#include <com/sun/star/awt/Size.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCONTROLLER_HPP_
#include <com/sun/star/frame/XController.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XJOBEXECUTOR_HPP_
#include <com/sun/star/task/XJobExecutor.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDERINTERCEPTION_HPP_
#include <com/sun/star/frame/XDispatchProviderInterception.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XFRAMESSUPPLIER_HPP_
#include <com/sun/star/frame/XFramesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_INSERTCOMMANDARGUMENT_HPP_
#include <com/sun/star/ucb/InsertCommandArgument.hpp>
#endif
#include <com/sun/star/report/XReportDefinition.hpp>
#include <com/sun/star/report/XReportEngine.hpp>
#ifndef _COM_SUN_STAR_UCB_OPENMODE_HPP_
#include <com/sun/star/ucb/OpenMode.hpp>
#endif
#ifndef _COM_SUN_STAR_XEMBEDOBJECTFACTORY_HPP_
#include <com/sun/star/embed/XEmbedObjectFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_XEMBEDOBJECTCREATOR_HPP_
#include <com/sun/star/embed/XEmbedObjectCreator.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_ASPECTS_HPP_
#include <com/sun/star/embed/Aspects.hpp>
#endif
#ifndef _UCBHELPER_CANCELCOMMANDEXECUTION_HXX_
#include <ucbhelper/cancelcommandexecution.hxx>
#endif
#ifndef _COM_SUN_STAR_UCB_UNSUPPORTEDDATASINKEXCEPTION_HPP_
#include <com/sun/star/ucb/UnsupportedDataSinkException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_UNSUPPORTEDOPENMODEEXCEPTION_HPP_
#include <com/sun/star/ucb/UnsupportedOpenModeException.hpp>
#endif
#ifndef _COM_SUN_STAR_ELEMENTMODES_HPP_
#include <com/sun/star/embed/ElementModes.hpp>
#endif
#ifndef _COM_SUN_STAR_XEMBEDPERSIST_HPP_
#include <com/sun/star/embed/XEmbedPersist.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBEDSTATES_HPP_
#include <com/sun/star/embed/EmbedStates.hpp>
#endif
#ifndef _COM_SUN_STAR_XCOMPONENTSUPPLIER_HPP_
#include <com/sun/star/embed/XComponentSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_ENTRYINITMODES_HPP_
#include <com/sun/star/embed/EntryInitModes.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_MISSINGPROPERTIESEXCEPTION_HPP_
#include <com/sun/star/ucb/MissingPropertiesException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_MISSINGINPUTSTREAMEXCEPTION_HPP_
#include <com/sun/star/ucb/MissingInputStreamException.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_OPENCOMMANDARGUMENT2_HPP_
#include <com/sun/star/ucb/OpenCommandArgument2.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLOSEBROADCASTER_HPP_
#include <com/sun/star/util/XCloseBroadcaster.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODULE_HPP_
#include <com/sun/star/frame/XModule.hpp>
#endif
#ifndef _COM_SUN_STAR_DATATRANSFER_DATAFLAVOR_HPP_
#include <com/sun/star/datatransfer/DataFlavor.hpp>
#endif
#ifndef _COM_SUN_STAR_DATATRANSFER_XTRANSFERABLE_HPP_
#include <com/sun/star/datatransfer/XTransferable.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_XTRANSACTEDOBJECT_HPP_
#include <com/sun/star/embed/XTransactedObject.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_XCOMMONEMBEDPERSIST_HPP_
#include <com/sun/star/embed/XCommonEmbedPersist.hpp>
#endif
#ifndef DBA_INTERCEPT_HXX
#include "intercept.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_XINTERACTIONDOCUMENTSAVE_HPP_
#include <com/sun/star/sdb/XInteractionDocumentSave.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_DOCUMENTSAVEREQUEST_HPP_
#include <com/sun/star/sdb/DocumentSaveRequest.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XDOCUMENTINFOSUPPLIER_HPP_
#include <com/sun/star/document/XDocumentInfoSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_MACROEXECMODE_HPP_
#include <com/sun/star/document/MacroExecMode.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMSSUPPLIER_HPP_
#include <com/sun/star/form/XFormsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COMPHELPER_INTERACTION_HXX_
#include <comphelper/interaction.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _COM_SUN_STAR_VIEW_XVIEWSETTINGSSUPPLIER_HPP_
#include <com/sun/star/view/XViewSettingsSupplier.hpp>
#endif
#ifndef _DBA_CORE_RESOURCE_HXX_
#include "core_resource.hxx"
#endif
#ifndef _DBA_CORE_RESOURCE_HRC_
#include "core_resource.hrc"
#endif
#ifndef _DBA_COREDATAACCESS_DATASOURCE_HXX_
#include "datasource.hxx"
#endif
#ifndef _COM_SUN_STAR_EMBED_XSTATECHANGEBROADCASTER_HPP_
#include <com/sun/star/embed/XStateChangeBroadcaster.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONAPPROVE_HPP_
#include <com/sun/star/task/XInteractionApprove.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONDISAPPROVE_HPP_
#include <com/sun/star/task/XInteractionDisapprove.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XLAYOUTMANAGER_HPP_
#include <com/sun/star/frame/XLayoutManager.hpp>
#endif
#ifndef _CPPUHELPER_COMPBASE1_HXX_
#include <cppuhelper/compbase1.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COMPHELPER_SEQUENCEASHASHMAP_HXX_
#include <comphelper/sequenceashashmap.hxx>
#endif
#ifndef _COMPHELPER_MIMECONFIGHELPER_HXX_
#include <comphelper/mimeconfighelper.hxx>
#endif
#ifndef _COMPHELPER_STORAGEHELPER_HXX
#include <comphelper/storagehelper.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTENTENUMERATIONACCESS_HPP_
#include <com/sun/star/container/XContentEnumerationAccess.hpp>
#endif
#include <com/sun/star/io/WrongFormatException.hpp>

using namespace ::com::sun::star;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::embed;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::document;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::datatransfer;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::drawing;
using namespace ::osl;
using namespace ::comphelper;
using namespace ::cppu;
namespace css = ::com::sun::star;


#define DEFAULT_WIDTH  15000
#define DEFAULT_HEIGHT 10000
//........................................................................
namespace dbaccess
{
    //==================================================================
    // OEmbedObjectHolder
    //==================================================================
    typedef ::cppu::WeakComponentImplHelper1<	::com::sun::star::embed::XStateChangeListener > TEmbedObjectHolder;
    class OEmbedObjectHolder :	 public ::comphelper::OBaseMutex
                                ,public TEmbedObjectHolder
    {
        Reference< XEmbeddedObject > m_xBroadCaster;
        ODocumentDefinition*				 m_pDefinition;
        sal_Bool							 m_bInStateChange;
    protected:
        virtual void SAL_CALL disposing();
    public:
        OEmbedObjectHolder(const Reference< XEmbeddedObject >& _xBroadCaster,ODocumentDefinition* _pDefinition)
            : TEmbedObjectHolder(m_aMutex)
            ,m_xBroadCaster(_xBroadCaster)
            ,m_pDefinition(_pDefinition)
            ,m_bInStateChange(sal_False)
        {
            osl_incrementInterlockedCount( &m_refCount );
            {
                if ( m_xBroadCaster.is() )
                    m_xBroadCaster->addStateChangeListener(this);
            }
            osl_decrementInterlockedCount( &m_refCount );
        }

        virtual void SAL_CALL changingState( const ::com::sun::star::lang::EventObject& aEvent, ::sal_Int32 nOldState, ::sal_Int32 nNewState ) throw (::com::sun::star::embed::WrongStateException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL stateChanged( const ::com::sun::star::lang::EventObject& aEvent, ::sal_Int32 nOldState, ::sal_Int32 nNewState ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw (::com::sun::star::uno::RuntimeException);
    };
    //------------------------------------------------------------------
    void SAL_CALL OEmbedObjectHolder::disposing()
    {
        if ( m_xBroadCaster.is() )
            m_xBroadCaster->removeStateChangeListener(this);
        m_xBroadCaster = NULL;
        m_pDefinition = NULL;
    }
    //------------------------------------------------------------------
    void SAL_CALL OEmbedObjectHolder::changingState( const ::com::sun::star::lang::EventObject& /*aEvent*/, ::sal_Int32 /*nOldState*/, ::sal_Int32 /*nNewState*/ ) throw (::com::sun::star::embed::WrongStateException, ::com::sun::star::uno::RuntimeException)
    {
    }
    //------------------------------------------------------------------
    void SAL_CALL OEmbedObjectHolder::stateChanged( const ::com::sun::star::lang::EventObject& aEvent, ::sal_Int32 nOldState, ::sal_Int32 nNewState ) throw (::com::sun::star::uno::RuntimeException)
    {
        if ( !m_bInStateChange && nNewState == EmbedStates::RUNNING && nOldState == EmbedStates::ACTIVE && m_pDefinition )
        {
            m_bInStateChange = sal_True;
            Reference<XInterface> xInt(static_cast< ::cppu::OWeakObject* >(m_pDefinition),UNO_QUERY);
            {
                Reference<XEmbeddedObject> xEmbeddedObject(aEvent.Source,UNO_QUERY);
                if ( xEmbeddedObject.is() )
                    xEmbeddedObject->changeState(EmbedStates::LOADED);
            }
            m_bInStateChange = sal_False;
        }
    }
    //------------------------------------------------------------------
    void SAL_CALL OEmbedObjectHolder::disposing( const ::com::sun::star::lang::EventObject& /*Source*/ ) throw (::com::sun::star::uno::RuntimeException)
    {
        m_xBroadCaster = NULL;
    }

    //==================================================================
    // OEmbeddedClientHelper
    //==================================================================
    typedef ::cppu::WeakImplHelper1 <   XEmbeddedClient
                                    >   EmbeddedClientHelper_BASE;
    class OEmbeddedClientHelper : public EmbeddedClientHelper_BASE
    {
        ODocumentDefinition* m_pClient;
    public:
        OEmbeddedClientHelper(ODocumentDefinition* _pClient) :m_pClient(_pClient) {}

        virtual void SAL_CALL saveObject(  ) throw (ObjectSaveVetoException, Exception, RuntimeException)
        {
        }
        virtual void SAL_CALL onShowWindow( sal_Bool /*bVisible*/ ) throw (RuntimeException)
        {
        }
        // XComponentSupplier
        virtual Reference< ::com::sun::star::util::XCloseable > SAL_CALL getComponent(  ) throw (RuntimeException)
        {
            return Reference< css::util::XCloseable >();
        }

        // XEmbeddedClient
        virtual void SAL_CALL visibilityChanged( ::sal_Bool /*bVisible*/ ) throw (WrongStateException, RuntimeException)
        {
        }
        inline void resetClient(ODocumentDefinition* _pClient) { m_pClient = _pClient; }
    };

    //==================================================================
    // LifetimeCoupler
    //==================================================================
    typedef ::cppu::WeakImplHelper1 <   css::lang::XEventListener
                                    >   LifetimeCoupler_Base;
    /** helper class which couples the lifetime of a component to the lifetim
        of another component

        Instances of this class are constructed with two components. The first is
        simply held by reference, and thus kept alive. The second one is observed
        for <code>disposing</code> calls - if they occur, i.e. if the component dies,
        the reference to the first component is cleared.

        This way, you can ensure that a certain component is kept alive as long
        as a second component is not disposed.
    */
    class LifetimeCoupler : public LifetimeCoupler_Base
    {
    private:
        Reference< XInterface > m_xClient;

    public:
        inline static void couple( const Reference< XInterface >& _rxClient, const Reference< XComponent >& _rxActor )
        {
            Reference< css::lang::XEventListener > xEnsureDelete( new LifetimeCoupler( _rxClient, _rxActor ) );
        }

    private:
        inline LifetimeCoupler( const Reference< XInterface >& _rxClient, const Reference< XComponent >& _rxActor )
            :m_xClient( _rxClient )
        {
            DBG_ASSERT( _rxActor.is(), "LifetimeCoupler::LifetimeCoupler: this will crash!" );
            osl_incrementInterlockedCount( &m_refCount );
            {
                _rxActor->addEventListener( this );
            }
            osl_decrementInterlockedCount( &m_refCount );
            DBG_ASSERT( m_refCount, "LifetimeCoupler::LifetimeCoupler: the actor is not holding us by hard ref - this won't work!" );
        }

        virtual void SAL_CALL disposing( const css::lang::EventObject& Source ) throw (RuntimeException);
    protected:
    };

    //------------------------------------------------------------------
    void SAL_CALL LifetimeCoupler::disposing( const css::lang::EventObject& /*Source*/ ) throw (RuntimeException)
    {
        m_xClient.clear();
    }

    //==================================================================
    // ODocumentSaveContinuation
    //==================================================================
    class ODocumentSaveContinuation : public OInteraction< XInteractionDocumentSave >
    {
        ::rtl::OUString		m_sName;
        Reference<XContent>	m_xParentContainer;

    public:
        ODocumentSaveContinuation() { }

        inline Reference<XContent>	getContent() const { return m_xParentContainer; }
        inline ::rtl::OUString		getName() const { return m_sName; }

        // XInteractionDocumentSave
        virtual void SAL_CALL setName( const ::rtl::OUString& _sName,const Reference<XContent>& _xParent) throw(RuntimeException);
    };

    //------------------------------------------------------------------
    void SAL_CALL ODocumentSaveContinuation::setName( const ::rtl::OUString& _sName,const Reference<XContent>& _xParent) throw(RuntimeException)
    {
        m_sName = _sName;
        m_xParentContainer = _xParent;
    }

::rtl::OUString ODocumentDefinition::GetDocumentServiceFromMediaType( const Reference< XStorage >& xStorage
                                                    ,const ::rtl::OUString& sEntName 
                                                    ,const Reference< XMultiServiceFactory >& _xORB
                                                    ,Sequence< sal_Int8 >& _rClassId
                                                    )
{
    ::rtl::OUString sResult;
    try
    {
        if ( xStorage->isStorageElement( sEntName ) )
        {
            // the object must be based on storage

            Reference< XPropertySet > xPropSet( xStorage->openStorageElement( sEntName, ElementModes::READ ), UNO_QUERY_THROW );

            ::rtl::OUString aMediaType;
            try {
                Any aAny = xPropSet->getPropertyValue( ::rtl::OUString::createFromAscii( "MediaType" ) );
                aAny >>= aMediaType;
            }
            catch ( Exception& )
            {
            }
            ::comphelper::MimeConfigurationHelper aConfigHelper(_xORB);
            sResult = aConfigHelper.GetDocServiceNameFromMediaType(aMediaType);
            _rClassId = aConfigHelper.GetSequenceClassIDRepresentation(aConfigHelper.GetExplicitlyRegisteredObjClassID(aMediaType));
            if ( !_rClassId.getLength() && sResult.getLength() )
            {
                Reference< XNameAccess > xObjConfig = aConfigHelper.GetObjConfiguration();
                if ( xObjConfig.is() )
                {
                    try
                    {
                        Sequence< ::rtl::OUString > aClassIDs = xObjConfig->getElementNames();
                        for ( sal_Int32 nInd = 0; nInd < aClassIDs.getLength(); nInd++ )
                        {
                            Reference< XNameAccess > xObjectProps;
                            ::rtl::OUString aEntryDocName;

                            if (    ( xObjConfig->getByName( aClassIDs[nInd] ) >>= xObjectProps ) && xObjectProps.is()
                                 && ( xObjectProps->getByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ObjectDocumentServiceName"))
                                              ) >>= aEntryDocName )
                                 && aEntryDocName.equals( sResult ) )
                            {
                                _rClassId = aConfigHelper.GetSequenceClassIDRepresentation(aClassIDs[nInd]);
                                break;
                            }
                        }
                    }
                    catch( Exception& )
                    {}
                }
            }

            ::comphelper::disposeComponent( xPropSet );
        }
    }
    catch ( Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
    return sResult;
}
// -----------------------------------------------------------------------------
//==========================================================================
//= ODocumentDefinition
//==========================================================================
DBG_NAME(ODocumentDefinition)

//--------------------------------------------------------------------------
ODocumentDefinition::ODocumentDefinition(const Reference< XInterface >& _rxContainer
                                         , const Reference< XMultiServiceFactory >& _xORB
                                         ,const TContentPtr& _pImpl
                                         , sal_Bool _bForm
                                         , const Sequence< sal_Int8 >& _aClassID
                                         ,const Reference<XConnection>& _xConnection
                                         )
                                         :OContentHelper(_xORB,_rxContainer,_pImpl)
    ,OPropertyStateContainer(m_aBHelper)
    ,m_pInterceptor(NULL)
    ,m_bForm(_bForm)
    ,m_bOpenInDesign(sal_False)
    ,m_bInExecute(sal_False)
    ,m_pClientHelper(NULL)
{
    DBG_CTOR(ODocumentDefinition, NULL);
    registerProperties();
    if ( _aClassID.getLength() )
        loadEmbeddedObject(MacroExecMode::USE_CONFIG,_aClassID,_xConnection);
}

//--------------------------------------------------------------------------
ODocumentDefinition::~ODocumentDefinition()
{
    DBG_DTOR(ODocumentDefinition, NULL);
    if ( !m_aBHelper.bInDispose && !m_aBHelper.bDisposed )
    {
        acquire();
        dispose();
    }

    if ( m_pInterceptor )
    {
        m_pInterceptor->dispose();
        m_pInterceptor->release();
        m_pInterceptor = NULL;
    }
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::closeObject()
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( m_xEmbeddedObject.is() )
    {
        try
        {
            Reference< com::sun::star::util::XCloseable> xCloseable(m_xEmbeddedObject,UNO_QUERY);
            if ( xCloseable.is() )
                xCloseable->close(sal_True);
        }
        catch(Exception)
        {
        }
        m_xEmbeddedObject = NULL;
        if ( m_pClientHelper )
        {
            m_pClientHelper->resetClient(NULL);
            m_pClientHelper->release();
            m_pClientHelper = NULL;
        }
    }
}
// -----------------------------------------------------------------------------
void SAL_CALL ODocumentDefinition::disposing()
{
    OContentHelper::disposing();
    ::osl::MutexGuard aGuard(m_aMutex);
    closeObject();
    ::comphelper::disposeComponent(m_xListener);
    m_xDesktop = NULL;
}
// -----------------------------------------------------------------------------
IMPLEMENT_TYPEPROVIDER3(ODocumentDefinition,OContentHelper,OPropertyStateContainer,ODocumentDefinition_Base);
IMPLEMENT_FORWARD_XINTERFACE3( ODocumentDefinition,OContentHelper,OPropertyStateContainer,ODocumentDefinition_Base)
IMPLEMENT_SERVICE_INFO1(ODocumentDefinition,"com.sun.star.comp.dba.ODocumentDefinition",SERVICE_SDB_DOCUMENTDEFINITION)
//--------------------------------------------------------------------------
void ODocumentDefinition::registerProperties()
{
    registerProperty(PROPERTY_NAME, PROPERTY_ID_NAME, PropertyAttribute::BOUND | PropertyAttribute::READONLY | PropertyAttribute::CONSTRAINED,
                    &m_pImpl->m_aProps.aTitle, ::getCppuType(&m_pImpl->m_aProps.aTitle));
    registerProperty(PROPERTY_AS_TEMPLATE, PROPERTY_ID_AS_TEMPLATE, PropertyAttribute::BOUND | PropertyAttribute::READONLY | PropertyAttribute::CONSTRAINED,
                    &m_pImpl->m_aProps.bAsTemplate, ::getCppuType(&m_pImpl->m_aProps.bAsTemplate));
    registerProperty(PROPERTY_PERSISTENT_NAME, PROPERTY_ID_PERSISTENT_NAME, PropertyAttribute::BOUND | PropertyAttribute::READONLY | PropertyAttribute::CONSTRAINED,
                    &m_pImpl->m_aProps.sPersistentName, ::getCppuType(&m_pImpl->m_aProps.sPersistentName));
    registerProperty(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsForm")), PROPERTY_ID_IS_FORM, PropertyAttribute::BOUND | PropertyAttribute::READONLY | PropertyAttribute::CONSTRAINED,
                    &m_bForm, ::getCppuType(&m_bForm));
}
// -----------------------------------------------------------------------------
Reference< XPropertySetInfo > SAL_CALL ODocumentDefinition::getPropertySetInfo(  ) throw(RuntimeException)
{
    Reference<XPropertySetInfo> xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//--------------------------------------------------------------------------
IPropertyArrayHelper& ODocumentDefinition::getInfoHelper()
{
    return *getArrayHelper();
}


//--------------------------------------------------------------------------
IPropertyArrayHelper* ODocumentDefinition::createArrayHelper( ) const
{
    Sequence< Property > aProps;
    describeProperties(aProps);
    return new OPropertyArrayHelper(aProps);
}
class OExecuteImpl
{
    sal_Bool& m_rbSet;
public:
    OExecuteImpl(sal_Bool& _rbSet) : m_rbSet(_rbSet){ m_rbSet=sal_True; }
    ~OExecuteImpl(){ m_rbSet = sal_False; }
};
// -----------------------------------------------------------------------------
namespace
{
    bool lcl_extractOpenMode( const Any& _rValue, sal_Int32& /* [out] */ _rMode )
    {
        OpenCommandArgument aOpenCommand;
        if ( _rValue >>= aOpenCommand )
            _rMode = aOpenCommand.Mode;
        else
        {
            OpenCommandArgument2 aOpenCommand2;
            if ( _rValue >>= aOpenCommand2 )
                _rMode = aOpenCommand2.Mode;
            else
                return false;
        }
        return true;
    }
}

// -----------------------------------------------------------------------------
void ODocumentDefinition::impl_removeFrameFromDesktop_throw( const Reference< XFrame >& _rxFrame )
{
    if ( !m_xDesktop.is() )
        m_xDesktop.set( m_xORB->createInstance( SERVICE_FRAME_DESKTOP ), UNO_QUERY_THROW );

    Reference< XFrames > xFrames( m_xDesktop->getFrames(), UNO_QUERY_THROW );
    xFrames->remove( _rxFrame );
}

// -----------------------------------------------------------------------------
void ODocumentDefinition::impl_onActivateEmbeddedObject( bool _bOpenedInDesignMode )
{
    try
    {
        Reference< XModel > xModel( getComponent(), UNO_QUERY );
        Reference< XController > xController( xModel.is() ? xModel->getCurrentController() : Reference< XController >() );
        if ( !xController.is() )
            return;

        if ( !m_xListener.is() )
            // it's the first time the embedded object has been activated
            // create an OEmbedObjectHolder
            m_xListener = new OEmbedObjectHolder(m_xEmbeddedObject,this);

        Reference< XFrame > xFrame( xController->getFrame() );
        if ( xFrame.is() )
        {
            // raise the window to top (especially necessary if this is not the first activation)
            Reference< XTopWindow > xTopWindow( xFrame->getContainerWindow(), UNO_QUERY_THROW );
            xTopWindow->toFront();

            // remove the frame from the desktop's frame collection because we need full control of it.
            impl_removeFrameFromDesktop_throw( xFrame );
        }

        // ensure that we ourself are kept alive as long as the embedded object's frame is
        // opened
        LifetimeCoupler::couple( *this, Reference< XComponent >( xFrame, UNO_QUERY_THROW ) );

        // init the edit view
        if ( _bOpenedInDesignMode )
            impl_initObjectEditView( xController );
    }
    catch( const RuntimeException& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}

// -----------------------------------------------------------------------------
namespace
{
    // =========================================================================
    // = PreserveVisualAreaSize
    // =========================================================================
    /** stack-guard for preserving the size of the VisArea of an XModel
    */
    class PreserveVisualAreaSize
    {
    private:
        Reference< XVisualObject >  m_xVisObject;
        ::com::sun::star::awt::Size m_aOriginalSize;

    public:
        inline PreserveVisualAreaSize( const Reference< XModel >& _rxModel )
            :m_xVisObject( _rxModel, UNO_QUERY )
        {
            if ( m_xVisObject.is() )
            {
                try
                {
                    m_aOriginalSize = m_xVisObject->getVisualAreaSize( Aspects::MSOLE_CONTENT );
                }
                catch ( Exception& )
                {
                    DBG_ERROR( "PreserveVisualAreaSize::PreserveVisualAreaSize: caught an exception!" );
                }
            }
        }

        inline ~PreserveVisualAreaSize()
        {
            if ( m_xVisObject.is() && m_aOriginalSize.Width && m_aOriginalSize.Height )
            {
                try
                {
                    m_xVisObject->setVisualAreaSize( Aspects::MSOLE_CONTENT, m_aOriginalSize );
                }
                catch ( Exception& )
                {
                    DBG_ERROR( "PreserveVisualAreaSize::~PreserveVisualAreaSize: caught an exception!" );
                }
            }
        }
    };

    // =========================================================================
    // = LayoutManagerLock
    // =========================================================================
    /** helper class for stack-usage which during its lifetime locks a layout manager
    */
    class LayoutManagerLock
    {
    private:
        Reference< XLayoutManager > m_xLayoutManager;

    public:
        inline LayoutManagerLock( const Reference< XController >& _rxController )
        {
            DBG_ASSERT( _rxController.is(), "LayoutManagerLock::LayoutManagerLock: this will crash!" );
            Reference< XFrame > xFrame( _rxController->getFrame() );
            try
            {
                Reference< XPropertySet > xPropSet( xFrame, UNO_QUERY_THROW );
                m_xLayoutManager.set(
                    xPropSet->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "LayoutManager" ) ) ),
                    UNO_QUERY_THROW );
                m_xLayoutManager->lock();

            }
            catch( Exception& )
            {
                DBG_ERROR( "LayoutManagerLock::LayoutManagerLock: caught an exception!" );
            }
        }

        inline ~LayoutManagerLock()
        {
            try
            {
                // unlock the layout manager
                if ( m_xLayoutManager.is() )
                    m_xLayoutManager->unlock();
            }
            catch( Exception& )
            {
                DBG_ERROR( "LayoutManagerLock::~LayoutManagerLock: caught an exception!" );
            }
        }
    };
}

// -----------------------------------------------------------------------------
void ODocumentDefinition::impl_initObjectEditView( const Reference< XController >& _rxController )
{
    if ( !m_bForm )
        // currently, only forms need to be initialized
        return;

    try
    {
        Reference< XViewSettingsSupplier > xSettingsSupplier( _rxController, UNO_QUERY_THROW );
        Reference< XPropertySet > xViewSettings( xSettingsSupplier->getViewSettings(), UNO_QUERY_THROW );

        // The visual area size can be changed by the setting of the following properties
        // so it should be restored later
        PreserveVisualAreaSize aPreserveVisAreaSize( _rxController->getModel() );

        // Layout manager should not layout while the size is still not restored
        // so it will stay locked for this time
        LayoutManagerLock aLockLayout( _rxController );

        // setting of the visual properties
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowRulers")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowVertRuler")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowHoriRuler")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsRasterVisible")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsSnapToRaster")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowOnlineLayout")),makeAny(sal_True));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RasterSubdivisionX")),makeAny(sal_Int32(5)));
        xViewSettings->setPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RasterSubdivisionY")),makeAny(sal_Int32(5)));

        Reference< XModifiable > xModifiable( _rxController->getModel(), UNO_QUERY_THROW );
        xModifiable->setModified( sal_False );
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}

// -----------------------------------------------------------------------------
Any SAL_CALL ODocumentDefinition::execute( const Command& aCommand, sal_Int32 CommandId, const Reference< XCommandEnvironment >& Environment ) throw (Exception, CommandAbortedException, RuntimeException)
{
    Any aRet;
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( !m_bInExecute )
    {
        OExecuteImpl aExecuteGuard(m_bInExecute);
        sal_Bool bOpenInDesign = aCommand.Name.equalsAscii("openDesign");
        sal_Bool bOpenForMail = aCommand.Name.equalsAscii("openForMail");
        if ( aCommand.Name.compareToAscii( "open" ) == 0 || bOpenInDesign || bOpenForMail )
        {
            //////////////////////////////////////////////////////////////////
            // open command for a folder content
            //////////////////////////////////////////////////////////////////
            Reference< XConnection> xConnection;
            sal_Int32 nOpenMode = OpenMode::DOCUMENT;

            lcl_extractOpenMode( aCommand.Argument, nOpenMode );

            Sequence< PropertyValue > aArguments;
            if ( aCommand.Argument >>= aArguments )
            {
                const PropertyValue* pIter = aArguments.getConstArray();
                const PropertyValue* pEnd  = pIter + aArguments.getLength();
                for(;pIter != pEnd;++pIter)
                {
                    if ( pIter->Name == PROPERTY_ACTIVECONNECTION )
                        xConnection.set(pIter->Value,UNO_QUERY);
                    else
                        lcl_extractOpenMode( pIter->Value, nOpenMode );
                }
            }

            if ( xConnection.is() )
                m_xLastKnownConnection = xConnection;

            if  (   ( nOpenMode == OpenMode::ALL )
                ||  ( nOpenMode == OpenMode::FOLDERS )
                ||  ( nOpenMode == OpenMode::DOCUMENTS )
                ||  ( nOpenMode == OpenMode::DOCUMENT_SHARE_DENY_NONE )
                ||  ( nOpenMode == OpenMode::DOCUMENT_SHARE_DENY_WRITE )
                )
            {
                // opening as folder is not supported
                ucbhelper::cancelCommandExecution(
                        makeAny( UnsupportedOpenModeException(
                                        rtl::OUString(),
                                        static_cast< cppu::OWeakObject * >( this ),
                                        sal_Int16( nOpenMode ) ) ),
                        Environment );
                    // Unreachable
                DBG_ERROR( "unreachable" );
              }

            Reference<XModel> xModel;
            if ( m_pImpl->m_aProps.sPersistentName.getLength() )
            {
                m_bOpenInDesign = bOpenInDesign;
                loadEmbeddedObject(MacroExecMode::USE_CONFIG,Sequence< sal_Int8 >(),xConnection,!bOpenInDesign);
                if ( m_xEmbeddedObject.is() )
                {
                    xModel.set(getComponent(),UNO_QUERY);
                    Reference< report::XReportDefinition> xReportDefinition(xModel,UNO_QUERY);

                    if ( !bOpenForMail && !(!bOpenInDesign && xReportDefinition.is()) )
                    {
                        Reference< XModule> xModule(xModel,UNO_QUERY);
                        if ( xModule.is() )
                        {
                            if ( m_bForm )
                                xModule->setIdentifier(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.FormDesign")));
                            else if ( !xReportDefinition.is() )
                                xModule->setIdentifier(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.TextReportDesign")));
                        }
                        m_xEmbeddedObject->changeState(EmbedStates::ACTIVE);
                        impl_onActivateEmbeddedObject( bOpenInDesign );
                    }
                    else if ( !bOpenInDesign && xReportDefinition.is() )
                    {
                        // we are in ReadOnly mode
                        // we would like to open the Writer or Calc with the report direct, without design it.
                        Reference< report::XReportEngine> xReportEngine( m_xORB->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.report.OReportEngineJFree"))) ,UNO_QUERY);
                    
                        xReportEngine->setReportDefinition(xReportDefinition);
                        xReportEngine->setActiveConnection(m_xLastKnownConnection);
                        aRet <<= xReportEngine->createDocumentAlive(NULL);
                        return aRet;            
                    }

                    fillReportData(!bOpenInDesign);
                    aRet <<= xModel;
                }
            }
        }
        else if ( aCommand.Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "copyTo" ) ) )
        {
            Sequence<Any> aIni;
            aCommand.Argument >>= aIni;
            if ( aIni.getLength() != 2 )
            {
                OSL_ENSURE( sal_False, "Wrong argument type!" );
                ucbhelper::cancelCommandExecution(
                    makeAny( IllegalArgumentException(
                                        rtl::OUString(),
                                        static_cast< cppu::OWeakObject * >( this ),
                                        -1 ) ),
                    Environment );
                // Unreachable
            }
            Reference< XStorage> xStorage(aIni[0],UNO_QUERY);
            ::rtl::OUString sPersistentName;
            aIni[1] >>= sPersistentName;
            loadEmbeddedObject(MacroExecMode::USE_CONFIG, Sequence< sal_Int8 >(), Reference< XConnection >(), sal_False );
            Reference<XEmbedPersist> xPersist(m_xEmbeddedObject,UNO_QUERY);
            if ( xPersist.is() )
            {
                xPersist->storeToEntry(xStorage,sPersistentName,Sequence<PropertyValue>(),Sequence<PropertyValue>());
                xPersist->storeOwn();
                m_xEmbeddedObject->changeState(EmbedStates::LOADED);
            }
            else
                throw CommandAbortedException();
        }
        else if ( aCommand.Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "preview" ) ) )
        {
            generateNewImage(aRet);
        }
        else if ( aCommand.Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "insert" ) ) )
        {
            Sequence<Any> aIni;
            aCommand.Argument >>= aIni;
            if ( aIni.getLength() > 0 && aIni.getLength() < 2 )
            {
                OSL_ENSURE( sal_False, "Wrong argument type!" );
                ucbhelper::cancelCommandExecution(
                    makeAny( IllegalArgumentException(
                                        rtl::OUString(),
                                        static_cast< cppu::OWeakObject * >( this ),
                                        -1 ) ),
                    Environment );
                // Unreachable
            }
            ::rtl::OUString sURL;
            aIni[0] >>= sURL;
            insert(sURL,Environment);
        }
        else if ( aCommand.Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "getdocumentinfo" ) ) )
        {
            fillDocumentInfo(aRet);
        }
        else if ( aCommand.Name.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "delete" ) ) )
        {
            //////////////////////////////////////////////////////////////////
            // delete
            //////////////////////////////////////////////////////////////////
            closeObject();
            Reference< XStorage> xStorage = getStorage();
            if ( xStorage.is() )
                xStorage->removeElement(m_pImpl->m_aProps.sPersistentName);

            dispose();
        }
        else
            aRet = OContentHelper::execute(aCommand,CommandId,Environment);
    }
    return aRet;
}
// -----------------------------------------------------------------------------
namespace
{
    void lcl_resetChildFormsToEmptyDataSource( const Reference< XIndexAccess>& _rxFormsContainer )
    {
        OSL_PRECOND( _rxFormsContainer.is(), "lcl_resetChildFormsToEmptyDataSource: illegal call!" );
        sal_Int32 count = _rxFormsContainer->getCount();
        for ( sal_Int32 i = 0; i < count; ++i )
        {
            Reference< XForm > xForm( _rxFormsContainer->getByIndex( i ), UNO_QUERY );
            if ( !xForm.is() )
                continue;

            // if the element is a form, reset its DataSourceName property to an empty string
            try
            {
                Reference< XPropertySet > xFormProps( xForm, UNO_QUERY_THROW );
                xFormProps->setPropertyValue( PROPERTY_DATASOURCENAME, makeAny( ::rtl::OUString() ) );
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }

            // if the element is a container itself, step down the component hierarchy
            Reference< XIndexAccess > xContainer( xForm, UNO_QUERY );
            if ( xContainer.is() )
                lcl_resetChildFormsToEmptyDataSource( xContainer );
        }
    }

    void lcl_resetFormsToEmptyDataSource( const Reference< XEmbeddedObject>& _rxEmbeddedObject )
    {
        try
        {
            Reference< XComponentSupplier > xCompProv( _rxEmbeddedObject, UNO_QUERY_THROW );
            Reference< XDrawPageSupplier > xSuppPage( xCompProv->getComponent(), UNO_QUERY_THROW );
                // if this interface does not exist, then either getComponent returned NULL,
                // or the document is a multi-page document. The latter is allowed, but currently
                // simply not handled by this code, as it would not normally happen.

            Reference< XFormsSupplier > xSuppForms( xSuppPage->getDrawPage(), UNO_QUERY_THROW );
            Reference< XIndexAccess > xForms( xSuppForms->getForms(), UNO_QUERY_THROW );
            lcl_resetChildFormsToEmptyDataSource( xForms );
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }

    }
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::insert(const ::rtl::OUString& _sURL, const Reference< XCommandEnvironment >& Environment)
    throw( Exception )
{
    osl::ClearableGuard< osl::Mutex > aGuard( m_aMutex );

    // Check, if all required properties were set.
    if ( !_sURL.getLength() || m_xEmbeddedObject.is() )
    {
        OSL_ENSURE( sal_False, "Content::insert - property value missing!" );

        Sequence< rtl::OUString > aProps( 1 );
        aProps[ 0 ] = PROPERTY_URL;
        ucbhelper::cancelCommandExecution(
            makeAny( MissingPropertiesException(
                                rtl::OUString(),
                                static_cast< cppu::OWeakObject * >( this ),
                                aProps ) ),
            Environment );
        // Unreachable
    }


    if ( !m_xEmbeddedObject.is() )
    {
        Reference< XStorage> xStorage = getStorage();
        if ( xStorage.is() )
        {
            Reference< XEmbedObjectCreator> xEmbedFactory( m_xORB->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.embed.EmbeddedObjectCreator"))) ,UNO_QUERY);
            if ( xEmbedFactory.is() )
            {
                Sequence<PropertyValue> aEmpty,aMediaDesc(1);
                aMediaDesc[0].Name = PROPERTY_URL;
                aMediaDesc[0].Value <<= _sURL;
                m_xEmbeddedObject.set(xEmbedFactory->createInstanceInitFromMediaDescriptor( xStorage
                                                                                ,m_pImpl->m_aProps.sPersistentName
                                                                                ,aMediaDesc
                                                                                ,aEmpty),UNO_QUERY);

                lcl_resetFormsToEmptyDataSource( m_xEmbeddedObject );
                // #i57669# / 2005-12-01 / frank.schoenheit@sun.com

                Reference<XEmbedPersist> xPersist(m_xEmbeddedObject,UNO_QUERY);
                if ( xPersist.is() )
                {
                    xPersist->storeOwn();
                }
                try
                {
                    Reference< com::sun::star::util::XCloseable> xCloseable(m_xEmbeddedObject,UNO_QUERY);
                    if ( xCloseable.is() )
                        xCloseable->close(sal_True);
                }
                catch(Exception)
                {
                }
                m_xEmbeddedObject = NULL;
              }
        }
    }

//  @@@
//	storeData();

    aGuard.clear();
//	inserted();
}
// -----------------------------------------------------------------------------
sal_Bool ODocumentDefinition::save(sal_Bool _bApprove)
{
    // default handling: instantiate an interaction handler and let it handle the parameter request
    if ( !m_bOpenInDesign )
        return sal_False;
    try
    {

        {
            ::vos::OGuard aSolarGuard(Application::GetSolarMutex());

            // the request
            Reference<XNameAccess> xName(m_xParentContainer,UNO_QUERY);
            DocumentSaveRequest aRequest;
            aRequest.Name = m_pImpl->m_aProps.aTitle;
            if ( !aRequest.Name.getLength() )
            {
                if ( m_bForm )
                    aRequest.Name = DBACORE_RESSTRING( RID_STR_FORM );
                else
                    aRequest.Name = DBACORE_RESSTRING( RID_STR_REPORT );
                aRequest.Name = ::dbtools::createUniqueName(xName,aRequest.Name);
            }

            aRequest.Content.set(m_xParentContainer,UNO_QUERY);
            OInteractionRequest* pRequest = new OInteractionRequest(makeAny(aRequest));
            Reference< XInteractionRequest > xRequest(pRequest);
            // some knittings
            // two continuations allowed: OK and Cancel
            ODocumentSaveContinuation* pDocuSave = NULL;

            if ( !m_pImpl->m_aProps.aTitle.getLength() )
            {
                pDocuSave = new ODocumentSaveContinuation;
                pRequest->addContinuation(pDocuSave);
            }
            OInteraction< XInteractionApprove >* pApprove = NULL;
            if ( _bApprove )
            {
                pApprove = new OInteraction< XInteractionApprove >;
                pRequest->addContinuation(pApprove);
            }

            OInteraction< XInteractionDisapprove >* pDisApprove = new OInteraction< XInteractionDisapprove >;
            pRequest->addContinuation(pDisApprove);

            OInteractionAbort* pAbort = new OInteractionAbort;
            pRequest->addContinuation(pAbort);

            // create the handler, let it handle the request
            Reference< XInteractionHandler > xHandler(m_xORB->createInstance(SERVICE_SDB_INTERACTION_HANDLER), UNO_QUERY);
            if ( xHandler.is() )
                xHandler->handle(xRequest);

            if ( pAbort->wasSelected() )
                return sal_False;
            if  ( pDisApprove->wasSelected() )
                return sal_True;
            if ( pDocuSave && pDocuSave->wasSelected() )
            {
                ::osl::MutexGuard aGuard(m_aMutex);
                Reference<XNameContainer> xNC(pDocuSave->getContent(),UNO_QUERY);
                if ( xNC.is() )
                {
                    m_pImpl->m_aProps.aTitle = pDocuSave->getName();
                    Reference< XContent> xContent = this;
                    xNC->insertByName(pDocuSave->getName(),makeAny(xContent));

                    updateDocumentTitle();
                }
            }
        }

        ::osl::MutexGuard aGuard(m_aMutex);
        Reference<XEmbedPersist> xPersist(m_xEmbeddedObject,UNO_QUERY);
        if ( xPersist.is() )
        {
            xPersist->storeOwn();
            notifyDataSourceModified();
        }
    }
    catch(Exception&)
    {
        OSL_ENSURE(0,"ODocumentDefinition::save: caught an Exception (tried to let the InteractionHandler handle it)!");
    }
    return sal_True;
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::fillLoadArgs(Sequence<PropertyValue>& _rArgs,Sequence<PropertyValue>& _rEmbeddedObjectDescriptor,const Reference<XConnection>& _xConnection,sal_Bool _bReadOnly,sal_Int16 _nMarcoExcecMode)
{
    sal_Int32 nLen = _rArgs.getLength();
    {
        Sequence<PropertyValue> aDocumentContext(2);
        aDocumentContext[0].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ActiveConnection"));
        aDocumentContext[0].Value <<= _xConnection;

        aDocumentContext[1].Name = PROPERTY_APPLYFORMDESIGNMODE;
        aDocumentContext[1].Value <<= !_bReadOnly;

        _rArgs.realloc(nLen+1);
        _rArgs[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ComponentData"));
        _rArgs[nLen++].Value <<= aDocumentContext;
    }

    _rArgs.realloc(nLen+2);
    _rArgs[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ReadOnly"));
    _rArgs[nLen++].Value <<= _bReadOnly;

    _rArgs[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("MacroExecutionMode"));
    _rArgs[nLen++].Value <<= _nMarcoExcecMode;

    if ( m_pImpl->m_aProps.aTitle.getLength() )
    {
        _rArgs.realloc(nLen+1);
        _rArgs[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DocumentTitle"));
        _rArgs[nLen++].Value <<= m_pImpl->m_aProps.aTitle;
    }

    if ( m_pInterceptor )
    {
        m_pInterceptor->dispose();
        m_pInterceptor->release();
        m_pInterceptor = NULL;
    }

    m_pInterceptor = new OInterceptor( this ,_bReadOnly);
    m_pInterceptor->acquire();
    Reference<XDispatchProviderInterceptor> xInterceptor = m_pInterceptor;

    _rEmbeddedObjectDescriptor.realloc(2);
    nLen = 0;
    _rEmbeddedObjectDescriptor[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OutplaceDispatchInterceptor"));
    _rEmbeddedObjectDescriptor[nLen++].Value <<= xInterceptor;

    uno::Sequence< uno::Any > aOutFrameProps(2);
    PropertyValue aProp;
    aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TopWindow"));
    aProp.Value <<= sal_True;
    aOutFrameProps[0] <<= aProp;
    
    Reference< XModel > xDatabaseDocumentModel;
    if ( m_pImpl->m_pDataSource )
        xDatabaseDocumentModel = m_pImpl->m_pDataSource->getModel_noCreate();

    Reference< XController > xDatabaseDocumentController;
    if ( xDatabaseDocumentModel.is() )
        xDatabaseDocumentController = xDatabaseDocumentModel->getCurrentController();

    if ( xDatabaseDocumentController.is() )
    {
        aProp.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ParentFrame"));
        aProp.Value <<= xDatabaseDocumentController->getFrame();
        aOutFrameProps[1] <<= aProp;
    }

    _rEmbeddedObjectDescriptor[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OutplaceFrameProperties"));
    _rEmbeddedObjectDescriptor[nLen++].Value <<= aOutFrameProps;
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::loadEmbeddedObject(sal_Int16 _nMarcoExcecMode,const Sequence< sal_Int8 >& _aClassID,const Reference<XConnection>& _xConnection,sal_Bool _bReadOnly)
{
    if ( !m_xEmbeddedObject.is() )
    {
        Reference< XStorage> xStorage = getStorage();
        if ( xStorage.is() )
        {
            Reference< XEmbedObjectFactory> xEmbedFactory( m_xORB->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.embed.OOoEmbeddedObjectFactory"))) ,UNO_QUERY);
            if ( xEmbedFactory.is() )
            {
                ::rtl::OUString sDocumentService;
                sal_Bool bSetSize = sal_False;
                sal_Int32 nEntryConnectionMode = EntryInitModes::DEFAULT_INIT;
                Sequence< sal_Int8 > aClassID = _aClassID;
                if ( aClassID.getLength() )
                {
                    nEntryConnectionMode = EntryInitModes::TRUNCATE_INIT;
                    bSetSize = sal_True;
                }
                else
                {
                    sDocumentService = GetDocumentServiceFromMediaType(xStorage,m_pImpl->m_aProps.sPersistentName,m_xORB,aClassID);
                    // check if we are not a form and
                    // the com.sun.star.report.pentaho.SOReportJobFactory is not present.
                    if (m_bForm == 0 /* MAGIC! */ && !sDocumentService.equalsAscii("com.sun.star.text.TextDocument"))
                    {
                        // we seems to be a new report, check if report extension is present.
                        Reference< XContentEnumerationAccess > xEnumAccess(m_xORB, UNO_QUERY);
                        static ::rtl::OUString s_sReportDesign(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.report.pentaho.SOReportJobFactory"));
                        Reference< XEnumeration > xEnumDrivers = xEnumAccess->createContentEnumeration(s_sReportDesign);
                        if ( !xEnumDrivers.is() || !xEnumDrivers->hasMoreElements() )
                        {
                            com::sun::star::io::WrongFormatException aWFE;
                            aWFE.Message = ::rtl::OUString::createFromAscii("Extension not present.");
                            throw aWFE;
                        }
                    }
                    if ( !aClassID.getLength() )
                    {
                        if ( m_bForm )
                            aClassID = MimeConfigurationHelper::GetSequenceClassID(SO3_SW_CLASSID);
                        else
                        {
                            aClassID = MimeConfigurationHelper::GetSequenceClassID(SO3_RPT_CLASSID_90);
                        }
                    }
                }

                OSL_ENSURE( aClassID.getLength(),"No Class ID" );

                Sequence<PropertyValue> aArgs,aEmbeddedObjectDescriptor;
                fillLoadArgs(aArgs,aEmbeddedObjectDescriptor,_xConnection,_bReadOnly,_nMarcoExcecMode);

                m_xEmbeddedObject.set(xEmbedFactory->createInstanceUserInit(aClassID
                                                                            ,sDocumentService
                                                                            ,xStorage
                                                                            ,m_pImpl->m_aProps.sPersistentName
                                                                            ,nEntryConnectionMode
                                                                            ,aArgs
                                                                            ,aEmbeddedObjectDescriptor
                                                                            ),UNO_QUERY);
                if ( m_xEmbeddedObject.is() )
                {
                    if ( !m_pClientHelper )
                    {
                        m_pClientHelper = new OEmbeddedClientHelper(this);
                        m_pClientHelper->acquire();
                    }
                    Reference<XEmbeddedClient> xClient = m_pClientHelper;
                    m_xEmbeddedObject->setClientSite(xClient);
                    m_xEmbeddedObject->changeState(EmbedStates::RUNNING);
                    if ( bSetSize )
                    {
                        ::com::sun::star::awt::Size aSize;
                        aSize.Width = DEFAULT_WIDTH;
                        aSize.Height = DEFAULT_HEIGHT;

                        m_xEmbeddedObject->setVisualAreaSize(Aspects::MSOLE_CONTENT,aSize);
                    }
                }
              }
        }
    }
    else if ( m_xEmbeddedObject->getCurrentState() == EmbedStates::LOADED )
    {
        if ( !m_pClientHelper )
        {
            m_pClientHelper = new OEmbeddedClientHelper(this);
            m_pClientHelper->acquire();
        }
        Reference<XEmbeddedClient> xClient = m_pClientHelper;
        m_xEmbeddedObject->setClientSite(xClient);

        Sequence<PropertyValue> aArgs,aEmbeddedObjectDescriptor;
        fillLoadArgs(aArgs,aEmbeddedObjectDescriptor,_xConnection,_bReadOnly,_nMarcoExcecMode);
        Reference<XCommonEmbedPersist> xCommon(m_xEmbeddedObject,UNO_QUERY);
        OSL_ENSURE(xCommon.is(),"unsupported interface!");
        if ( xCommon.is() )
            xCommon->reload(aArgs,aEmbeddedObjectDescriptor);
        m_xEmbeddedObject->changeState(EmbedStates::RUNNING);
    }

    Reference<XModel> xModel(getComponent(),UNO_QUERY);
    // set the OfficeDatabaseDocument instance as parent of the embedded document
    // #i40358# / 2005-01-19 / frank.schoenheit@sun.com
    Reference< XChild > xDepdendDocAsChild( xModel, UNO_QUERY );
    if ( xDepdendDocAsChild.is() )
    {
        try
        {
            if ( !xDepdendDocAsChild->getParent().is() )
            {   // first encounter
                xDepdendDocAsChild->setParent( getDataSource( m_xParentContainer ) );
            }
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "ODocumentDefinition::loadEmbeddedObject: caught an exception while setting the parent of the embedded object!" );
        }
    }

    if ( xModel.is() )
    {
        Sequence<PropertyValue> aArgs = xModel->getArgs();
        ::comphelper::MediaDescriptor aHelper(aArgs);
        aHelper[ ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "ReadOnly" ) )] <<= _bReadOnly;

        if ( m_pImpl->m_aProps.aTitle.getLength() )
            aHelper[ 
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DocumentTitle" ) )] <<= m_pImpl->m_aProps.aTitle;

        aHelper[ 
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "MacroExecutionMode" ))] <<= _nMarcoExcecMode;

        aHelper >> aArgs;

        xModel->attachResource(xModel->getURL(),aArgs);
    }
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::generateNewImage(Any& _rImage)
{
    loadEmbeddedObject( MacroExecMode::NEVER_EXECUTE,Sequence< sal_Int8 >(), Reference< XConnection >(), sal_True );
    if ( m_xEmbeddedObject.is() )
    {
        try
        {
            Reference<XTransferable> xTransfer(getComponent(),UNO_QUERY);
            if ( xTransfer.is() )
            {
                DataFlavor aFlavor;
                aFlavor.MimeType = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("image/png"));
                aFlavor.HumanPresentableName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Portable Network Graphics"));
                aFlavor.DataType = ::getCppuType(static_cast< const Sequence < sal_Int8 >* >(NULL));

                _rImage = xTransfer->getTransferData( aFlavor );
            }
        }
        catch( Exception )
        {
        }
    }
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::getPropertyDefaultByHandle( sal_Int32 /*_nHandle*/, Any& _rDefault ) const
{
    _rDefault.clear();
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::fillDocumentInfo(Any& _rInfo)
{
    loadEmbeddedObject( MacroExecMode::NEVER_EXECUTE,Sequence< sal_Int8 >(), Reference< XConnection >(), sal_True );
    if ( m_xEmbeddedObject.is() )
    {
        try
        {
            Reference<XDocumentInfoSupplier> xDocSup(getComponent(),UNO_QUERY);
            if ( xDocSup.is() )
                _rInfo <<= xDocSup->getDocumentInfo();
        }
        catch( Exception e )
        {
        }
    }
}
// -----------------------------------------------------------------------------
Reference< ::com::sun::star::util::XCloseable> ODocumentDefinition::getComponent() throw (RuntimeException)
{
    OSL_ENSURE(m_xEmbeddedObject.is(),"Illegal call for embeddedObject");
    Reference< ::com::sun::star::util::XCloseable> xComp;
    if ( m_xEmbeddedObject.is() )
    {
        int nOldState = m_xEmbeddedObject->getCurrentState();
        int nState = nOldState;
        if ( nOldState == EmbedStates::LOADED )
        {
            m_xEmbeddedObject->changeState( EmbedStates::RUNNING );
            nState = EmbedStates::RUNNING;
        }

        if ( nState == EmbedStates::ACTIVE || nState == EmbedStates::RUNNING )
        {
            Reference<XComponentSupplier> xCompProv(m_xEmbeddedObject,UNO_QUERY);
            if ( xCompProv.is() )
            {
                xComp = xCompProv->getComponent();
                OSL_ENSURE(xComp.is(),"No valid component");
            }
        }
    }
    return xComp;
}
// -----------------------------------------------------------------------------
void SAL_CALL ODocumentDefinition::rename( const ::rtl::OUString& _rNewName ) throw (SQLException, ElementExistException, RuntimeException)
{
    try
    {
        osl::ClearableGuard< osl::Mutex > aGuard(m_aMutex);
        if ( _rNewName.equals( m_pImpl->m_aProps.aTitle ) )
            return;

        // document definitions are organized in a hierarchicalway, so reject names
        // which contain a /, as this is reserved for hierarchy level separation
        if ( _rNewName.indexOf( '/' ) != -1 )
        {
            ::dbtools::throwGenericSQLException(
                DBA_RES( RID_STR_NO_SLASH_IN_OBJECT_NAME ), *this );
        }

        sal_Int32 nHandle = PROPERTY_ID_NAME;
        Any aOld = makeAny( m_pImpl->m_aProps.aTitle );
        Any aNew = makeAny( _rNewName );

        aGuard.clear();
        fire(&nHandle, &aNew, &aOld, 1, sal_True );
        m_pImpl->m_aProps.aTitle = _rNewName;
        fire(&nHandle, &aNew, &aOld, 1, sal_False );

        ::osl::ClearableGuard< ::osl::Mutex > aGuard2( m_aMutex );
        if ( m_xEmbeddedObject.is() && m_xEmbeddedObject->getCurrentState() == EmbedStates::ACTIVE )
            updateDocumentTitle();
    }
    catch(const PropertyVetoException&)
    {
        throw ElementExistException(_rNewName,*this);
    }
}
// -----------------------------------------------------------------------------
Reference< XStorage> ODocumentDefinition::getStorage() const
{
    static const ::rtl::OUString s_sForms = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("forms"));
    static const ::rtl::OUString s_sReports = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("reports"));
    return  m_pImpl->m_pDataSource
        ?   m_pImpl->m_pDataSource->getStorage( m_bForm ? s_sForms : s_sReports )
        :   Reference< XStorage>();
}
// -----------------------------------------------------------------------------
sal_Bool ODocumentDefinition::isModified()
{
    osl::ClearableGuard< osl::Mutex > aGuard(m_aMutex);
    sal_Bool bRet = sal_False;
    if ( m_xEmbeddedObject.is() )
    {
        Reference<XModifiable> xModel(getComponent(),UNO_QUERY);
        bRet = xModel.is() && xModel->isModified();
    }
    return bRet;
}
// -----------------------------------------------------------------------------
bool ODocumentDefinition::prepareClose()
{
    if ( !m_xEmbeddedObject.is() )
        return true;

    try
    {
        // suspend the controller. Embedded objects are not allowed to rais
        // own UI on their own decision, instead, this has always to be triggered
        // by the embedding component. Thus, we do the suspend call here.
        // #i49370# / 2005-06-09 / frank.schoenheit@sun.com

        Reference< XModel > xModel( getComponent(), UNO_QUERY );
        Reference< XController > xController;
        if ( xModel.is() )
            xController = xModel->getCurrentController();
        OSL_ENSURE( xController.is(), "ODocumentDefinition::prepareClose: no controller!" );
        if ( !xController.is() )
            return sal_False;
        
        sal_Bool bCouldSuspend = xController->suspend( sal_True );
        if ( !bCouldSuspend )
            // controller vetoed the closing
            return false;

        if ( isModified() && !save( sal_True ) )
        {
            if ( bCouldSuspend )
                // revert suspension
                xController->suspend( sal_False );
            // saving failed or was cancelled
            return false;
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }

    return true;
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::fillReportData(sal_Bool _bFill)
{
    if ( !m_bForm && _bFill && m_pImpl->m_aProps.bAsTemplate && !m_bOpenInDesign ) // open a report in alive mode, so we need to fill it
    {
        Sequence<Any> aArgs(2);
        PropertyValue aValue;
        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TextDocument"));
        aValue.Value <<= getComponent();
        aArgs[0] <<= aValue;
           aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ActiveConnection"));
           aValue.Value <<= m_xLastKnownConnection;
           aArgs[1] <<= aValue;

        Reference< XJobExecutor > xExecuteable(m_xORB->createInstanceWithArguments(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.wizards.report.CallReportWizard")),aArgs),UNO_QUERY);
        if ( xExecuteable.is() )
            xExecuteable->trigger(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("fill")));
    }
}
// -----------------------------------------------------------------------------
void ODocumentDefinition::updateDocumentTitle()
{
    if ( m_pImpl->m_aProps.aTitle.getLength() )
    {
        Reference<XModel> xModel(getComponent(),UNO_QUERY);
        if ( xModel.is() )
        {
            Sequence<PropertyValue> aArgs = xModel->getArgs();
            ::comphelper::MediaDescriptor aHelper(aArgs);
            aHelper[ ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "DocumentTitle" ) )] <<= m_pImpl->m_aProps.aTitle;
            aHelper >> aArgs;
            xModel->attachResource(xModel->getURL(),aArgs);
        }
    }
}
//........................................................................
}	// namespace dbaccess
//........................................................................

