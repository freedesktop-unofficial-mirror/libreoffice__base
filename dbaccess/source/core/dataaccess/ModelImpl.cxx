/*************************************************************************
 *
 *  $RCSfile: ModelImpl.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-06-27 08:25:59 $
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

#ifndef _DBA_COREDATAACCESS_MODELIMPL_HXX_
#include "ModelImpl.hxx"
#endif
#ifndef _DBA_CORE_USERINFORMATION_HXX_
#include "userinformation.hxx"
#endif
#ifndef _DBA_COREDATAACCESS_COMMANDCONTAINER_HXX_
#include "commandcontainer.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _COMPHELPER_SEQSTREAM_HXX
#include <comphelper/seqstream.hxx>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _DBA_CORE_RESOURCE_HXX_
#include "core_resource.hxx"
#endif
#ifndef _DBA_CORE_RESOURCE_HRC_
#include "core_resource.hrc"
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _DBA_COREDATAACCESS_DATABASECONTEXT_HXX_
#include "databasecontext.hxx"
#endif
#ifndef _DBA_COREDATAACCESS_DATASOURCE_HXX_
#include "datasource.hxx"
#endif
#ifndef _DBA_COREDATAACCESS_DATABASEDOCUMENT_HXX_
#include "databasedocument.hxx"
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDRIVERACCESS_HPP_
#include <com/sun/star/sdbc/XDriverAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_XTRANSACTIONBROADCASTER_HPP_
#include <com/sun/star/embed/XTransactionBroadcaster.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDRIVERMANAGER_HPP_
#include <com/sun/star/sdbc/XDriverManager.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATOR_HPP_
#include <com/sun/star/task/XStatusIndicator.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XINTERACTIONSUPPLYAUTHENTICATION_HPP_
#include <com/sun/star/ucb/XInteractionSupplyAuthentication.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_AUTHENTICATIONREQUEST_HPP_
#include <com/sun/star/ucb/AuthenticationRequest.hpp>
#endif
#ifndef _COM_SUN_STAR_REFLECTION_XPROXYFACTORY_HPP_
#include <com/sun/star/reflection/XProxyFactory.hpp>
#endif
#ifndef _TYPELIB_TYPEDESCRIPTION_HXX_
#include <typelib/typedescription.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COMPHELPER_INTERACTION_HXX_
#include <comphelper/interaction.hxx>
#endif
#ifndef DBA_COREDATAACCESS_COMMITLISTENER_HXX
#include "commitlistener.hxx"
#endif
#ifndef _DBA_CORE_CONNECTION_HXX_
#include "connection.hxx"
#endif
#ifndef _COMPHELPER_GUARDING_HXX_
#include <comphelper/guarding.hxx>
#endif
#ifndef _RTL_DIGEST_H_
#include <rtl/digest.h>
#endif
#ifndef _COM_SUN_STAR_EMBED_XTRANSACTEDOBJECT_HPP_
#include <com/sun/star/embed/XTransactedObject.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _URLOBJ_HXX
#include <tools/urlobj.hxx>
#endif
#ifndef _ERRCODE_HXX
#include <tools/errcode.hxx>
#endif
#ifndef _COM_SUN_STAR_VIEW_XSELECTIONSUPPLIER_HPP_
#include <com/sun/star/view/XSelectionSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XIMPORTER_HPP_
#include <com/sun/star/document/XImporter.hpp>
#endif
#ifndef _COMPHELPER_MEDIADESCRIPTOR_HXX_
#include <comphelper/mediadescriptor.hxx>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XIMPORTER_HPP_
#include <com/sun/star/document/XImporter.hpp>
#endif
#include <algorithm>

using namespace ::com::sun::star::document;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::embed;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::ucb;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::view;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::reflection;
using namespace ::com::sun::star::xml::sax;
using namespace ::cppu;
using namespace ::osl;
using namespace ::vos;
using namespace ::dbtools;
using namespace ::comphelper;
namespace css = ::com::sun::star;

//........................................................................
namespace dbaccess
{
//........................................................................

//============================================================
//= ODatabaseModelImpl
//============================================================
DBG_NAME(ODatabaseModelImpl)
//--------------------------------------------------------------------------
ODatabaseModelImpl::ODatabaseModelImpl(const Reference< XMultiServiceFactory >& _rxFactory
                                       , const Reference< XModel>& _xModel)
            :m_xServiceFactory(_rxFactory)
            ,m_bReadOnly(sal_False)	// we're created as service and have to allow the setting of properties
            ,m_bPasswordRequired(sal_False)
            ,m_bSuppressVersionColumns(sal_True)
            ,m_pSharedConnectionManager(NULL)
            ,m_bModified(sal_False)
            ,m_bDocumentReadOnly(sal_False)
            ,m_bDisposingSubStorages( sal_False )
            ,m_pDBContext(NULL)
            ,m_nControllerLockCount(0)
            ,m_bOwnStorage(sal_False)
            ,m_xModel(_xModel)
            ,m_nLoginTimeout(0)
            ,m_refCount(0)
{
    // some kind of default
    DBG_CTOR(ODatabaseModelImpl,NULL);
    m_sConnectURL = ::rtl::OUString::createFromAscii("jdbc:");
    m_aTableFilter.realloc(1);
    m_aTableFilter[0] = ::rtl::OUString::createFromAscii("%");
    lateInit();
}

//--------------------------------------------------------------------------
ODatabaseModelImpl::ODatabaseModelImpl(
                    const ::rtl::OUString& _rRegistrationName,
                    const Reference< XMultiServiceFactory >& _rxFactory,
                    ODatabaseContext* _pDBContext
                    )
            :m_sName(_rRegistrationName)
            ,m_xServiceFactory(_rxFactory)
            ,m_bReadOnly(sal_True)		// assume readonly for the moment, adjusted below
            ,m_bPasswordRequired(sal_False)
            ,m_bSuppressVersionColumns(sal_True)
            ,m_pSharedConnectionManager(NULL)
            ,m_bModified(sal_False)
            ,m_bDocumentReadOnly(sal_False)
            ,m_bDisposingSubStorages( sal_False )
            ,m_pDBContext(_pDBContext)
            ,m_nControllerLockCount(0)
            ,m_bOwnStorage(sal_False)
            ,m_nLoginTimeout(0)
            ,m_refCount(0)
{
    DBG_CTOR(ODatabaseModelImpl,NULL);
    // adjust our readonly flag

    lateInit();
}

//--------------------------------------------------------------------------
ODatabaseModelImpl::~ODatabaseModelImpl()
{
    DBG_DTOR(ODatabaseModelImpl,NULL);
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::lateInit()
{
    m_bReadOnly = sal_False;
    m_aContainer.resize(4);
}
// -----------------------------------------------------------------------------
::rtl::OUString ODatabaseModelImpl::getURL(  )
{
      return m_sRealFileURL;
}
// -----------------------------------------------------------------------------
void SAL_CALL ODatabaseModelImpl::disposing( const ::com::sun::star::lang::EventObject& Source ) throw(RuntimeException)
{
    Reference<XConnection> xCon(Source.Source,UNO_QUERY);
    if ( xCon.is() )
    {
        bool bStore = false;
        OWeakConnectionArray::iterator aEnd = m_aConnections.end();
        for (OWeakConnectionArray::iterator i = m_aConnections.begin(); aEnd != i; ++i)
        {
            if ( xCon == i->get() )
            {
                *i = OWeakConnection();
                bStore = true;
                break;
            }
        }

        if ( bStore )
            commitRootStorage();
    }
    else // storage
    {
        if ( !m_bDisposingSubStorages )
        {
            Reference<XStorage> xStorage(Source.Source,UNO_QUERY);
            TStorages::iterator aFind = ::std::find_if(m_aStorages.begin(),m_aStorages.end(),
                                                ::std::compose1(::std::bind2nd(::std::equal_to<Reference<XStorage> >(),xStorage),::std::select2nd<TStorages::value_type>()));
            if ( aFind != m_aStorages.end() )
                m_aStorages.erase(aFind);
        }
    }
}
//------------------------------------------------------------------------------
void ODatabaseModelImpl::clearConnections()
{
    Reference< XConnection > xConn;
    for (OWeakConnectionArray::iterator i = m_aConnections.begin(); m_aConnections.end() != i; ++i)
    {
        xConn = *i;
        if ( xConn.is() )
        {
            try
            {
                xConn->close();
            }
            catch(Exception)
            {
                OSL_ENSURE(0,"Exception catched while closing a connection!");
            }
        }
    }
    m_aConnections.clear();

    m_pSharedConnectionManager = NULL;
    m_xSharedConnectionManager = NULL;
}
//------------------------------------------------------------------------------
void ODatabaseModelImpl::dispose()
{
    ::std::vector<TContentPtr>::iterator aIter = m_aContainer.begin();
    ::std::vector<TContentPtr>::iterator aEnd = m_aContainer.end();
    for (;aIter != aEnd ; ++aIter)
    {
        if ( aIter->get() )
            (*aIter)->m_pDataSource = NULL;
    }
    m_aContainer.clear();

    clearConnections();

    disposeControllerFrames();

    m_xCurrentController = NULL;
    m_xNumberFormatsSupplier = NULL;

    try
    {
        sal_Bool bStore = commitEmbeddedStorage();
        disposeStorages();
        if ( bStore )
            commitRootStorage();

        if ( m_bOwnStorage )
            ::comphelper::disposeComponent(m_xStorage);
    }
    catch(Exception&)
    {
    }
    m_xStorage = NULL;
}
// -----------------------------------------------------------------------------
const Reference< XNumberFormatsSupplier > & ODatabaseModelImpl::getNumberFormatsSupplier()
{
    if (!m_xNumberFormatsSupplier.is())
    {
        // the arguments : the locale of the current user
        UserInformation aUserInfo;
        Sequence< Any > aArguments(1);
        aArguments.getArray()[0] <<= aUserInfo.getUserLanguage();

        m_xNumberFormatsSupplier = Reference< XNumberFormatsSupplier >(m_xServiceFactory->createInstanceWithArguments(
                ::rtl::OUString::createFromAscii("com.sun.star.util.NumberFormatsSupplier"),
                aArguments),
            UNO_QUERY);
        DBG_ASSERT(m_xNumberFormatsSupplier.is(), "ODatabaseModelImpl::getNumberFormatsSupplier : could not instantiate the formats supplier !");
    }
    return m_xNumberFormatsSupplier;
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::disposeStorages() SAL_THROW(())
{
    m_bDisposingSubStorages = sal_True;

    TStorages::iterator aEnd = m_aStorages.end();
    for ( TStorages::iterator aIter = m_aStorages.begin();
          aIter != aEnd ;
          ++aIter
        )
    {
        try
        {
            ::comphelper::disposeComponent( aIter->second );
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "ODatabaseModelImpl::disposeStorages: caught an exception!" );
        }
    }
    m_aStorages.clear();

    m_bDisposingSubStorages = sal_False;
}
// -----------------------------------------------------------------------------
Reference< XSingleServiceFactory > ODatabaseModelImpl::createStorageFactory() const
{
    return Reference< XSingleServiceFactory >(
        m_xServiceFactory->createInstance(
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.embed.StorageFactory" ) )
        ),
        UNO_QUERY
    );
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::commitRootStorage()
{
#if OSL_DEBUG_LEVEL > 0
    bool bSuccess =
#endif
    commitStorageIfWriteable_ignoreErrors( getStorage() );
    OSL_ENSURE( bSuccess || !getStorage().is(),
        "ODatabaseModelImpl::commitRootStorage: could commit the storage!" );
}
// -----------------------------------------------------------------------------
Reference<XStorage> ODatabaseModelImpl::getStorage()
{
    if ( !m_xStorage.is() )
    {
        Reference< XSingleServiceFactory> xStorageFactory = createStorageFactory();
        if ( xStorageFactory.is() && m_sRealFileURL.getLength() )
        {
            Sequence<Any> aArgs(2);
            const PropertyValue* pEnd = m_aArgs.getConstArray() + m_aArgs.getLength();
            const PropertyValue* pValue =::std::find_if(
                m_aArgs.getConstArray(),
                pEnd,
                ::std::bind2nd(
                    ::comphelper::TPropertyValueEqualFunctor(),
                    ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Stream" ) )
                ));

            if ( pValue && pValue != pEnd )
                aArgs[0] = pValue->Value;
            else
            {
                pValue =::std::find_if(
                    m_aArgs.getConstArray(),
                    pEnd,
                    ::std::bind2nd(
                        ::comphelper::TPropertyValueEqualFunctor(),
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "InputStream" ) )
                    ));

                if ( pValue && pValue != pEnd )
                    aArgs[0] = pValue->Value;
                else if ( m_sRealFileURL.getLength() )
                    aArgs[0] <<= m_sRealFileURL;
            }

            if ( aArgs[0].hasValue() )
            {
                aArgs[1] <<= ElementModes::READWRITE;

                try
                {
                    m_xStorage.set( xStorageFactory->createInstanceWithArguments( aArgs ),UNO_QUERY );
                }
                catch(Exception)
                {
                    m_bDocumentReadOnly = sal_True;
                    aArgs[1] <<= ElementModes::READ;
                    try
                    {
                        m_xStorage.set( xStorageFactory->createInstanceWithArguments( aArgs ),UNO_QUERY );
                    }
                    catch(Exception)
                    {
                    }
                }
                m_bOwnStorage = m_xStorage.is();
            }
        }
    }
    return m_xStorage;
}
// -----------------------------------------------------------------------------
Reference<XStorage> ODatabaseModelImpl::getStorage(const ::rtl::OUString& _sStorageName,const Reference<css::embed::XTransactionListener>& _xEventListener, sal_Int32 nMode)
{
    OSL_ENSURE(_sStorageName.getLength(),"ODatabaseModelImpl::getStorage: Invalid storage name!");
    OSL_ENSURE(_xEventListener.is(),"No Eventlistener set!");
    Reference<XStorage> xStorage;
    TStorages::iterator aFind = m_aStorages.find(_sStorageName);
    if ( aFind == m_aStorages.end() )
    {
        Reference<XStorage> xMyStorage = getStorage();
        Reference<XNameAccess> xNames(xMyStorage,UNO_QUERY);
        if ( xMyStorage.is() )
        {
            try
            {
                xStorage = xMyStorage->openStorageElement(_sStorageName, m_bDocumentReadOnly ? ElementModes::READ : nMode);
                Reference<XTransactionBroadcaster> xBroad(xStorage,UNO_QUERY);
                if ( xBroad.is() )
                    xBroad->addTransactionListener(_xEventListener);
                aFind = m_aStorages.insert(TStorages::value_type(_sStorageName,xStorage)).first;
            }
            catch(Exception&)
            {
            }
        }
    }

    if ( aFind != m_aStorages.end() )
        xStorage = aFind->second;

    return xStorage;
}
// -----------------------------------------------------------------------------
bool ODatabaseModelImpl::commitStorageIfWriteable( const Reference< XStorage >& _rxStorage ) SAL_THROW(( IOException, WrappedTargetException, RuntimeException ))
{
    bool bSuccess = false;
    Reference<XTransactedObject> xTrans( _rxStorage, UNO_QUERY );
    if ( xTrans.is() )
    {
        sal_Int32 nMode = ElementModes::READ;
        try
        {
            Reference< XPropertySet > xStorageProps( _rxStorage, UNO_QUERY_THROW );
            xStorageProps->getPropertyValue(
                ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "OpenMode" ) ) ) >>= nMode;
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "ODatabaseModelImpl::commitStorageIfWriteable: could not determine the OpenMode of the storage!" );
        }

        if ( ( nMode & ElementModes::WRITE ) != 0 )
            xTrans->commit();
        bSuccess = true;
    }
    return bSuccess;
}
// -----------------------------------------------------------------------------
bool ODatabaseModelImpl::commitStorageIfWriteable_ignoreErrors( const Reference< XStorage >& _rxStorage ) SAL_THROW(())
{
    bool bSuccess = false;
    try
    {
        bSuccess = commitStorageIfWriteable( _rxStorage );
    }
    catch( const Exception& )
    {
        OSL_ENSURE( sal_False, "ODatabaseModelImpl::commitStorageIfWriteable_ignoreErrors: caught an exception!" );
    }
    return bSuccess;
}
// -----------------------------------------------------------------------------
sal_Bool ODatabaseModelImpl::commitEmbeddedStorage()
{
    sal_Bool bStore = sal_False;
    TStorages::iterator aFind = m_aStorages.find(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("database")));
    if ( aFind != m_aStorages.end() )
        bStore = commitStorageIfWriteable_ignoreErrors( aFind->second );
    return bStore;
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::setModified( sal_Bool _bModified )
{
    try
    {
        Reference<XModifiable> xModi(m_xModel.get(),UNO_QUERY);
        if ( xModi.is() )
            xModi->setModified(_bModified);
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched!");
    }
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::disposeControllerFrames()
{
    ::std::vector< Reference< XController> > aCopy = m_aControllers;
    ::std::vector< Reference< XController> >::iterator aIter = aCopy.begin();
    ::std::vector< Reference< XController> >::iterator aEnd = aCopy.end();
    for (;aIter != aEnd ; ++aIter)
    {
        if ( aIter->is() )
        {
            Reference< XFrame> xFrame = (*aIter)->getFrame();
            ::comphelper::disposeComponent(xFrame);
        }
    }
}
// -----------------------------------------------------------------------------
Reference<XDataSource> ODatabaseModelImpl::getDataSource()
{
    Reference<XDataSource> xDs = m_xDataSource;
    if ( !xDs.is() )
    { // no data source, so we have to create one and register it later on
        xDs = new ODatabaseSource(this);
        m_xDataSource = xDs;
    }
    return xDs;
}
// -----------------------------------------------------------------------------
Reference< XModel> ODatabaseModelImpl::getModel()
{
    Reference< XModel> xModel = m_xModel;
    if ( !xModel.is() )
        xModel = new ODatabaseDocument(this);
    return xModel;
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::clear()
{
    try
    {
        Reference< XComponent > xComp(m_xDataSource.get(), UNO_QUERY);
        m_xDataSource = WeakReference<XDataSource>();
        if ( xComp.is() )
            xComp->dispose();
        ::comphelper::disposeComponent(m_xModel);
    }
    catch(Exception&)
    {
        m_xModel = NULL;
    }
}
// -----------------------------------------------------------------------------
oslInterlockedCount SAL_CALL ODatabaseModelImpl::acquire()
{
    return osl_incrementInterlockedCount(&m_refCount);
}
// -----------------------------------------------------------------------------
oslInterlockedCount SAL_CALL ODatabaseModelImpl::release()
{
    if ( osl_decrementInterlockedCount(&m_refCount) == 0 )
    {
        clear();
        dispose();
        m_pDBContext->deregisterPrivate(m_sRealFileURL);
        delete this;
        return 0;
    }
    return m_refCount;
}
// -----------------------------------------------------------------------------
void ODatabaseModelImpl::commitStorages() SAL_THROW(( IOException, RuntimeException ))
{
    try
    {
        TStorages::iterator aIter = m_aStorages.begin();
        TStorages::iterator aEnd = m_aStorages.end();
        for (; aIter != aEnd ; ++aIter)
            commitStorageIfWriteable( aIter->second );
    }
    catch(WrappedTargetException)
    {
        // WrappedTargetException not allowed to leave
        throw IOException();
    }
}
//........................................................................
}	// namespace dbaccess
//........................................................................

