/*************************************************************************
 *
 *  $RCSfile: datasource.cxx,v $
 *
 *  $Revision: 1.41 $
 *
 *  last change: $Author: hr $ $Date: 2001-11-01 16:29:21 $
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

#ifndef _DBA_COREDATAACCESS_DATASOURCE_HXX_
#include "datasource.hxx"
#endif
#ifndef _DBA_CORE_USERINFORMATION_HXX_
#include "userinformation.hxx"
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
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COMPHELPER_STREAMSECTION_HXX_ 
#include <comphelper/streamsection.hxx>
#endif

#ifndef _COM_SUN_STAR_SDBC_XDRIVERACCESS_HPP_ 
#include <com/sun/star/sdbc/XDriverAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XPERSISTOBJECT_HPP_
#include <com/sun/star/io/XPersistObject.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDRIVERMANAGER_HPP_
#include <com/sun/star/sdbc/XDriverManager.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XINTERACTIONSUPPLYAUTHENTICATION_HPP_
#include <com/sun/star/ucb/XInteractionSupplyAuthentication.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_AUTHENTICATIONREQUEST_HPP_
#include <com/sun/star/ucb/AuthenticationRequest.hpp>
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

#ifndef _DBA_CORE_CONNECTION_HXX_
#include "connection.hxx"
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_GUARDING_HXX_ 
#include <comphelper/guarding.hxx>
#endif

using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::ucb;
using namespace ::cppu;
using namespace ::osl;
using namespace ::vos;
using namespace ::utl;
using namespace ::dbtools;
using namespace ::comphelper;

// persistent tokens
#define PT_SVFORMATTER		0x0001

//........................................................................
namespace dbaccess
{
//........................................................................

//============================================================
//= OAuthenticationContinuation
//============================================================
    class OAuthenticationContinuation : public OInteraction< XInteractionSupplyAuthentication >
    {
        sal_Bool	m_bDatasourceReadonly : 1;	// if sal_True, the data source using this continuation
                                                // is readonly, which means that no user can be set and 
                                                // the password can't be remembered
        sal_Bool	m_bRemberPassword : 1;		// remember the password for this session ?

        ::rtl::OUString		m_sUser;			// the user
        ::rtl::OUString		m_sPassword;		// the user's password

    public:
        OAuthenticationContinuation(sal_Bool _bReadOnlyDS = sal_False);

        virtual sal_Bool SAL_CALL canSetRealm(  ) throw(RuntimeException);
        virtual void SAL_CALL setRealm( const ::rtl::OUString& Realm ) throw(RuntimeException);
        virtual sal_Bool SAL_CALL canSetUserName(  ) throw(RuntimeException);
        virtual void SAL_CALL setUserName( const ::rtl::OUString& UserName ) throw(RuntimeException);
        virtual sal_Bool SAL_CALL canSetPassword(  ) throw(RuntimeException);
        virtual void SAL_CALL setPassword( const ::rtl::OUString& Password ) throw(RuntimeException);
        virtual Sequence< RememberAuthentication > SAL_CALL getRememberPasswordModes( RememberAuthentication& Default ) throw(RuntimeException);
        virtual void SAL_CALL setRememberPassword( RememberAuthentication Remember ) throw(RuntimeException);
        virtual sal_Bool SAL_CALL canSetAccount(  ) throw(RuntimeException);
        virtual void SAL_CALL setAccount( const ::rtl::OUString& Account ) throw(RuntimeException);
        virtual Sequence< RememberAuthentication > SAL_CALL getRememberAccountModes( RememberAuthentication& Default ) throw(RuntimeException);
        virtual void SAL_CALL setRememberAccount( RememberAuthentication Remember ) throw(RuntimeException);

        ::rtl::OUString	getUser() const				{ return m_sUser; }
        ::rtl::OUString	getPassword() const			{ return m_sPassword; }
        sal_Bool		getRememberPassword() const	{ return m_bRemberPassword; }
    };

    //--------------------------------------------------------------------------
    OAuthenticationContinuation::OAuthenticationContinuation(sal_Bool _bReadOnlyDS)
        :m_bDatasourceReadonly(_bReadOnlyDS)
        ,m_bRemberPassword(sal_True)	// TODO: a meaningfull default
    {
    }

    //--------------------------------------------------------------------------
    sal_Bool SAL_CALL OAuthenticationContinuation::canSetRealm(  ) throw(RuntimeException)
    {
        return sal_False;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setRealm( const ::rtl::OUString& Realm ) throw(RuntimeException)
    {
        DBG_ERROR("OAuthenticationContinuation::setRealm: not supported!");
    }

    //--------------------------------------------------------------------------
    sal_Bool SAL_CALL OAuthenticationContinuation::canSetUserName(  ) throw(RuntimeException)
    {
        return !m_bDatasourceReadonly;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setUserName( const ::rtl::OUString& _rUser ) throw(RuntimeException)
    {
        m_sUser = _rUser;
    }

    //--------------------------------------------------------------------------
    sal_Bool SAL_CALL OAuthenticationContinuation::canSetPassword(  ) throw(RuntimeException)
    {
        return sal_True;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setPassword( const ::rtl::OUString& _rPassword ) throw(RuntimeException)
    {
        m_sPassword = _rPassword;
    }

    //--------------------------------------------------------------------------
    Sequence< RememberAuthentication > SAL_CALL OAuthenticationContinuation::getRememberPasswordModes( RememberAuthentication& _reDefault ) throw(RuntimeException)
    {
        Sequence< RememberAuthentication > aReturn(1);
        _reDefault = aReturn[0] = (m_bDatasourceReadonly ? RememberAuthentication_NO : RememberAuthentication_SESSION);
        return aReturn;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setRememberPassword( RememberAuthentication _eRemember ) throw(RuntimeException)
    {
        m_bRemberPassword = (RememberAuthentication_NO != _eRemember);
    }

    //--------------------------------------------------------------------------
    sal_Bool SAL_CALL OAuthenticationContinuation::canSetAccount(  ) throw(RuntimeException)
    {
        return sal_False;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setAccount( const ::rtl::OUString& ) throw(RuntimeException)
    {
        DBG_ERROR("OAuthenticationContinuation::setAccount: not supported!");
    }

    //--------------------------------------------------------------------------
    Sequence< RememberAuthentication > SAL_CALL OAuthenticationContinuation::getRememberAccountModes( RememberAuthentication& _reDefault ) throw(RuntimeException)
    {
        Sequence < RememberAuthentication > aReturn(1);
        aReturn[0] = RememberAuthentication_NO;
        _reDefault = RememberAuthentication_NO;
        return aReturn;
    }

    //--------------------------------------------------------------------------
    void SAL_CALL OAuthenticationContinuation::setRememberAccount( RememberAuthentication Remember ) throw(RuntimeException)
    {
        DBG_ERROR("OAuthenticationContinuation::setRememberAccount: not supported!");
    }

//============================================================
//= ODatabaseContext
//============================================================
DBG_NAME(ODatabaseSource)
//--------------------------------------------------------------------------
extern "C" void SAL_CALL createRegistryInfo_ODatabaseSource()
{
    static OMultiInstanceAutoRegistration< ODatabaseSource > aAutoRegistration;
}

//--------------------------------------------------------------------------
Reference< XInterface > ODatabaseSource_CreateInstance(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return *(new ODatabaseSource(_rxFactory));
}

//--------------------------------------------------------------------------
ODatabaseSource::ODatabaseSource(const Reference< XMultiServiceFactory >& _rxFactory)
            :OSubComponent(m_aMutex, Reference< XInterface >())
            ,OConfigurationFlushable(m_aMutex)
            ,OPropertySetHelper(OComponentHelper::rBHelper)
            ,m_nLoginTimeout(0)
            ,m_xServiceFactory(_rxFactory)
            ,m_bReadOnly(sal_False)	// we're created as service and have to allow the setting of properties
            ,m_bPasswordRequired(sal_False)
            ,m_bSuppressVersionColumns(sal_True)
            ,m_aBookmarks(*this, m_aMutex)
            ,m_aCommandDefinitions(*this, m_aMutex)
{
    // some kind of default
    DBG_CTOR(ODatabaseSource,NULL);
    m_sConnectURL = ::rtl::OUString::createFromAscii("jdbc:");
    m_aTableFilter.realloc(1);
    m_aTableFilter[0] = ::rtl::OUString::createFromAscii("%");
}

//--------------------------------------------------------------------------
ODatabaseSource::ODatabaseSource(
                    OWeakObject& _rParent,
                    const OConfigurationNode& _rConfigRoot,
                    const ::rtl::OUString& _rRegistrationName,
                    const Reference< XMultiServiceFactory >& _rxFactory)
            :OSubComponent(m_aMutex, _rParent)
            ,OConfigurationFlushable(m_aMutex)
            ,OPropertySetHelper(OComponentHelper::rBHelper)
            ,m_nLoginTimeout(0)
            ,m_sName(_rRegistrationName)
            ,m_xServiceFactory(_rxFactory)
            ,m_bReadOnly(sal_True)		// assume readonly for the moment, adjusted below
            ,m_bPasswordRequired(sal_False)
            ,m_bSuppressVersionColumns(sal_True)
            ,m_aBookmarks(*this, m_aMutex)
            ,m_aCommandDefinitions(*this, m_aMutex)
{
    m_aConfigurationNode = _rConfigRoot.cloneAsRoot();

    DBG_CTOR(ODatabaseSource,NULL);
    DBG_ASSERT(m_aConfigurationNode.isValid(), "ODatabaseSource::ODatabaseSource : use ctor 1 if you can't supply a configuration location at the moment !");
    if (m_aConfigurationNode.isValid())
        initializeFromConfiguration();
    // adjust our readonly flag
    m_bReadOnly = !m_aConfigurationNode.isValid() || m_aConfigurationNode.isReadonly();
}

//--------------------------------------------------------------------------
ODatabaseSource::~ODatabaseSource()
{
    DBG_DTOR(ODatabaseSource,NULL);
}

// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< Type > ODatabaseSource::getTypes() throw (RuntimeException)
{
    OTypeCollection aPropertyHelperTypes(	::getCppuType( (const Reference< XFastPropertySet > *)0 ),
                                            ::getCppuType( (const Reference< XPropertySet > *)0 ),
                                            ::getCppuType( (const Reference< XMultiPropertySet > *)0 ));

    return ::comphelper::concatSequences(
        ::comphelper::concatSequences(
            OSubComponent::getTypes(),
            OConfigurationFlushable::getTypes(),
            aPropertyHelperTypes.getTypes()
        ),
        ODatabaseSource_Base::getTypes()
    );
}

//--------------------------------------------------------------------------
Sequence< sal_Int8 > ODatabaseSource::getUnoTunnelImplementationId() throw (RuntimeException)
{
    static OImplementationId * pId = 0;
    if (! pId)
    {
        MutexGuard aGuard( Mutex::getGlobalMutex() );
        if (! pId)
        {
            static OImplementationId aId;
            pId = &aId;
        }
    }
    return pId->getImplementationId();
}

//--------------------------------------------------------------------------
Sequence< sal_Int8 > ODatabaseSource::getImplementationId() throw (RuntimeException)
{
    return getUnoTunnelImplementationId();
}

// com::sun::star::uno::XInterface
//--------------------------------------------------------------------------
Any ODatabaseSource::queryInterface( const Type & rType ) throw (RuntimeException)
{
    Any aIface = OSubComponent::queryInterface( rType );
    if (!aIface.hasValue())
        aIface = ODatabaseSource_Base::queryInterface( rType );
    if (!aIface.hasValue())
        aIface = OConfigurationFlushable::queryInterface( rType );
    if (!aIface.hasValue())
        aIface = ::cppu::queryInterface(
                    rType,
                    static_cast< XPropertySet* >( this ),
                    static_cast< XFastPropertySet* >( this ),
                    static_cast< XMultiPropertySet* >( this ));
    return aIface;
}

//--------------------------------------------------------------------------
void ODatabaseSource::acquire() throw ()
{
    OSubComponent::acquire();
}

//--------------------------------------------------------------------------
void ODatabaseSource::release() throw ()
{
    OSubComponent::release();
}
// -----------------------------------------------------------------------------
void SAL_CALL ODatabaseSource::disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException)
{
    for (OWeakConnectionArray::iterator i = m_aConnections.begin(); m_aConnections.end() != i; i++)
    {
        if(Source.Source == i->get())
        {
            *i = OWeakConnection();
        }
    }
    
}
// XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString ODatabaseSource::getImplementationName(  ) throw(RuntimeException)
{
    return getImplementationName_Static();
}

//------------------------------------------------------------------------------
rtl::OUString ODatabaseSource::getImplementationName_Static(  ) throw(RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.comp.dba.ODatabaseSource");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > ODatabaseSource::getSupportedServiceNames(  ) throw (RuntimeException)
{
    return getSupportedServiceNames_Static();
}

//------------------------------------------------------------------------------
Reference< XInterface > ODatabaseSource::Create(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return ODatabaseSource_CreateInstance(_rxFactory);
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > ODatabaseSource::getSupportedServiceNames_Static(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 1 );
    aSNS[0] = SERVICE_SDB_DATASOURCE;
    return aSNS;
}

//------------------------------------------------------------------------------
sal_Bool ODatabaseSource::supportsService( const ::rtl::OUString& _rServiceName ) throw (RuntimeException)
{
    return ::comphelper::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
}

// com::sun::star::lang::XUnoTunnel
//------------------------------------------------------------------
sal_Int64 ODatabaseSource::getSomething( const Sequence< sal_Int8 > & rId ) throw (RuntimeException)
{
    if (rId.getLength() != 16)
        return 0;

    if (0 == rtl_compareMemory(getUnoTunnelImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;

    if (0 == rtl_compareMemory(OContainerElement::getUnoTunnelImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)static_cast<OContainerElement*>(this);

    return 0;
}

// OComponentHelper
//------------------------------------------------------------------------------
void ODatabaseSource::disposing()
{
    OPropertySetHelper::disposing();
    OConfigurationFlushable::disposing();

    MutexGuard aGuard(m_aMutex);

    if (m_aConfigurationNode.isValid())
        flush();
        // TODO : we need a mechanism for determining wheter we're modified and need that call or not

    Reference< XConnection > xConn;
    for (OWeakConnectionArray::iterator i = m_aConnections.begin(); m_aConnections.end() != i; i++)
    {
        xConn = *i;
        if (xConn.is())
            xConn->close();
    }
    m_aConnections.clear();

    m_aRenameNode.clear();
}

//------------------------------------------------------------------------------
Reference< XConnection > ODatabaseSource::buildLowLevelConnection(const ::rtl::OUString& _rUid, const ::rtl::OUString& _rPwd)
{
    Reference< XConnection > xReturn;
    Reference< XDriverManager > xManager(m_xServiceFactory->createInstance(SERVICE_SDBC_CONNECTIONPOOL)
        , UNO_QUERY);

    ::rtl::OUString sUser(_rUid);
    ::rtl::OUString sPwd(_rPwd);
    if ((0 == sUser.getLength()) && (0 == sPwd.getLength()) && (0 != m_sUser.getLength()))
    {	// ease the usage of this method. data source which are intended to have a user automatically
        // fill in the user/password combination if the caller of this method does not specify otherwise
        // 86951 - 05/08/2001 - frank.schoenheit@germany.sun.com
        sUser = m_sUser;
        if (0 != m_aPassword.getLength())
            sPwd = m_aPassword;
    }

    sal_uInt16 nExceptionMessageId = RID_STR_COULDNOTCONNECT_UNSPECIFIED;
    if (xManager.is())
    {
        sal_Int32 nAdditionalArgs(0);
        if (sUser.getLength()) ++nAdditionalArgs;
        if (sPwd.getLength()) ++nAdditionalArgs;

        Sequence< PropertyValue > aUserPwd(nAdditionalArgs);
        if (sUser.getLength())
        {
            aUserPwd[0].Name = ::rtl::OUString::createFromAscii("user");
            aUserPwd[0].Value <<= sUser;
        }
        if (sPwd.getLength())
        {
            aUserPwd[1].Name = ::rtl::OUString::createFromAscii("password");
            aUserPwd[1].Value <<= sPwd;
        }
        if (nAdditionalArgs)
            xReturn = xManager->getConnectionWithInfo(m_sConnectURL, ::comphelper::concatSequences(aUserPwd,m_aInfo));
        else
            xReturn = xManager->getConnectionWithInfo(m_sConnectURL,m_aInfo);

        if ( !xReturn.is() )
        {
            // try to examine what went wrong
            Reference< XDriver > xDriver;
            try
            {
                Reference< XDriverAccess > xAccessDrivers( xManager, UNO_QUERY );
                if ( xAccessDrivers.is() )
                    xDriver = xAccessDrivers->getDriverByURL( m_sConnectURL );
            }
            catch( const Exception& )
            {
                DBG_ERROR( "ODatabaseSource::buildLowLevelConnection: got a strange exception while analyzing the error!" );
            }

            if ( !xDriver.is() )
                nExceptionMessageId = RID_STR_COULDNOTCONNECT_NODRIVER;
        }
    }
    else
        nExceptionMessageId = RID_STR_COULDNOTLOAD_MANAGER;

    if ( !xReturn.is() )
    {
        ::rtl::OUString sMessage = DBACORE_RESSTRING( nExceptionMessageId );

        SQLContext aContext;
        aContext.Details = m_sConnectURL;

        throwGenericSQLException( sMessage, static_cast< XDataSource* >( this ), makeAny( aContext ) );
    }

    return xReturn;
}

//------------------------------------------------------------------------------
const Reference< XNumberFormatsSupplier > & ODatabaseSource::getNumberFormatsSupplier()
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
        DBG_ASSERT(m_xNumberFormatsSupplier.is(), "ODatabaseSource::getNumberFormatsSupplier : could not instantiate the formats supplier !");
    }
    return m_xNumberFormatsSupplier;
}


// OPropertySetHelper
//------------------------------------------------------------------------------
Reference< XPropertySetInfo >  ODatabaseSource::getPropertySetInfo() throw (RuntimeException)
{
    return createPropertySetInfo( getInfoHelper() ) ;
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* ODatabaseSource::createArrayHelper( ) const
{
    BEGIN_PROPERTY_HELPER(12)
        DECL_PROP0(INFO,						Sequence< PropertyValue >);
        DECL_PROP1_BOOL(ISPASSWORDREQUIRED,									BOUND);
        DECL_PROP1_BOOL(ISREADONLY,											READONLY);
        DECL_PROP0(LAYOUTINFORMATION,			Sequence< sal_Int8 >);
        DECL_PROP1(NAME,						::rtl::OUString,			READONLY);
        DECL_PROP2_IFACE(NUMBERFORMATSSUPPLIER,	XNumberFormatsSupplier,		READONLY, TRANSIENT);
        DECL_PROP1(PASSWORD,					::rtl::OUString,			TRANSIENT);
        DECL_PROP1_BOOL(SUPPRESSVERSIONCL,									BOUND);
        DECL_PROP1(TABLEFILTER,					Sequence< ::rtl::OUString >,BOUND);
        DECL_PROP1(TABLETYPEFILTER,				Sequence< ::rtl::OUString >,BOUND);
        DECL_PROP0(URL,							::rtl::OUString);
        DECL_PROP1(USER,						::rtl::OUString,			BOUND);
    END_PROPERTY_HELPER();
}

// cppu::OPropertySetHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& ODatabaseSource::getInfoHelper()
{
    return *getArrayHelper();
}

//------------------------------------------------------------------------------
sal_Bool ODatabaseSource::convertFastPropertyValue(Any & rConvertedValue, Any & rOldValue, sal_Int32 nHandle, const Any& rValue ) throw( IllegalArgumentException  )
{
    if (m_bReadOnly)
        throw IllegalArgumentException();

    sal_Bool bModified(sal_False);
    switch (nHandle)
    {
        case PROPERTY_ID_TABLEFILTER:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aTableFilter);
            break;
        case PROPERTY_ID_TABLETYPEFILTER:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aTableTypeFilter);
            break;
        case PROPERTY_ID_USER:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_sUser);
            break;
        case PROPERTY_ID_PASSWORD:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aPassword);
            break;
        case PROPERTY_ID_ISPASSWORDREQUIRED:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_bPasswordRequired);
            break;
        case PROPERTY_ID_SUPPRESSVERSIONCL:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_bSuppressVersionColumns);
            break;
        case PROPERTY_ID_LAYOUTINFORMATION:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aLayoutInformation);
            break;
        case PROPERTY_ID_URL:
        {
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_sConnectURL);
        }	break;
        case PROPERTY_ID_INFO:
        {
            Sequence<PropertyValue> aValues;
            if (!(rValue >>= aValues))
                throw IllegalArgumentException();

            bModified = sal_True;
                // don't wan't to check the properties, it's seems more expensiv than just to set the same props again

            rConvertedValue = rValue;
            rOldValue <<= m_aInfo;
        }	break;
        default:
            DBG_ERROR("unknown Property");
    }
    return bModified;
}

//------------------------------------------------------------------------------
void ODatabaseSource::setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const Any& rValue ) throw (Exception)
{
    switch(nHandle)
    {
        case PROPERTY_ID_TABLEFILTER:
            rValue >>= m_aTableFilter;
            break;
        case PROPERTY_ID_TABLETYPEFILTER:
            rValue >>= m_aTableTypeFilter;
            break;
        case PROPERTY_ID_USER:
            rValue >>= m_sUser;
            // if the user name changed, reset the password
            m_aPassword = ::rtl::OUString();
            break;
        case PROPERTY_ID_PASSWORD:
            rValue >>= m_aPassword;
            break;
        case PROPERTY_ID_ISPASSWORDREQUIRED:
            m_bPasswordRequired = any2bool(rValue);
            break;
        case PROPERTY_ID_SUPPRESSVERSIONCL:
            m_bSuppressVersionColumns = any2bool(rValue);
            break;
        case PROPERTY_ID_URL:
            rValue >>= m_sConnectURL;
            break;
        case PROPERTY_ID_INFO:
            rValue >>= m_aInfo;
            break;
        case PROPERTY_ID_LAYOUTINFORMATION:
            rValue >>= m_aLayoutInformation;
            break;
    }
}

//------------------------------------------------------------------------------
void ODatabaseSource::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_TABLEFILTER:
            rValue <<= m_aTableFilter;
            break;
        case PROPERTY_ID_TABLETYPEFILTER:
            rValue <<= m_aTableTypeFilter;
            break;
        case PROPERTY_ID_USER:
            rValue <<= m_sUser;
            break;
        case PROPERTY_ID_PASSWORD:
            rValue <<= m_aPassword;
            break;
        case PROPERTY_ID_ISPASSWORDREQUIRED:
            rValue = bool2any(m_bPasswordRequired);
            break;
        case PROPERTY_ID_SUPPRESSVERSIONCL:
            rValue = bool2any(m_bSuppressVersionColumns);
            break;
        case PROPERTY_ID_ISREADONLY:
            rValue = bool2any(m_bReadOnly);
            break;
        case PROPERTY_ID_INFO:
            rValue <<= m_aInfo;
            break;
        case PROPERTY_ID_URL:
            rValue <<= m_sConnectURL;
            break;
        case PROPERTY_ID_NUMBERFORMATSSUPPLIER:
            rValue <<= const_cast<ODatabaseSource*>(this)->getNumberFormatsSupplier();
            break;
        case PROPERTY_ID_NAME:
            rValue <<= m_sName;
            break;
        case PROPERTY_ID_LAYOUTINFORMATION:
            rValue <<= m_aLayoutInformation;
            break;
        default:
            DBG_ERROR("unknown Property");
    }
}

// XDataSource
//------------------------------------------------------------------------------
void ODatabaseSource::setLoginTimeout(sal_Int32 seconds) throw( SQLException, RuntimeException )
{
    MutexGuard aGuard(m_aMutex);
    m_nLoginTimeout = seconds;
}

//------------------------------------------------------------------------------
sal_Int32 ODatabaseSource::getLoginTimeout(void) throw( SQLException, RuntimeException )
{
    return m_nLoginTimeout;
}


// XCompletedConnection
//------------------------------------------------------------------------------
Reference< XConnection > SAL_CALL ODatabaseSource::connectWithCompletion( const Reference< XInteractionHandler >& _rxHandler ) throw(SQLException, RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    if (OComponentHelper::rBHelper.bDisposed)
        throw DisposedException();

    if (!_rxHandler.is())
    {
        DBG_ERROR("ODatabaseSource::connectWithCompletion: invalid interaction handler!");
        return getConnection(m_sUser, m_aPassword);
    }

    ::rtl::OUString sUser(m_sUser), sPassword(m_aPassword);
    sal_Bool bNewPasswordGiven = sal_False;

    if (m_bPasswordRequired && (0 == sPassword.getLength()))
    {	// we need a password, but don't have one yet.
        // -> ask the user

        // build an interaction request
        // two continuations (Ok and Cancel)
        OInteractionAbort* pAbort = new OInteractionAbort;
        OAuthenticationContinuation* pAuthenticate = new OAuthenticationContinuation(m_bReadOnly);

        // the request
        AuthenticationRequest aRequest;
        aRequest.ServerName = m_sName;
        aRequest.HasRealm = aRequest.HasAccount = sal_False;
        aRequest.HasUserName = aRequest.HasPassword = sal_True;
        aRequest.UserName = m_sUser;
        aRequest.Password = m_aPassword;
        OInteractionRequest* pRequest = new OInteractionRequest(makeAny(aRequest));
        Reference< XInteractionRequest > xRequest(pRequest);
        // some knittings
        pRequest->addContinuation(pAbort);
        pRequest->addContinuation(pAuthenticate);

        // handle the request
        try
        {
            MutexRelease aRelease(m_aMutex);
                // release the mutex when calling the handler, it may need to lock the SolarMutex
            _rxHandler->handle(xRequest);
        }
        catch(Exception&)
        {
            DBG_ERROR("ODatabaseSource::connectWithCompletion: caught an exception while calling the handler!");
        }

        if (!pAuthenticate->wasSelected())
            return Reference< XConnection >();

        // get the result
        sUser = m_sUser = pAuthenticate->getUser();
        sPassword = pAuthenticate->getPassword();

        if (pAuthenticate->getRememberPassword())
        {
            m_aPassword = pAuthenticate->getPassword();
            bNewPasswordGiven = sal_True;
        }
    }

    try
    {
        return getConnection(sUser, sPassword);
    }
    catch(Exception&)
    {
        if (bNewPasswordGiven)
            // assume that we had an authentication problem. Without this we may, after an unsucessfull connect, while
            // the user gave us a password an the order to remember it, never allow an password input again (at least
            // not without restarting the session)
            m_aPassword = ::rtl::OUString();
        throw;
    }

    DBG_ERROR("ODatabaseSource::connectWithCompletion: reached the unreacable!");
    return Reference< XConnection >();
}

//------------------------------------------------------------------------------
Reference< XConnection > ODatabaseSource::getConnection(const rtl::OUString& user, const rtl::OUString& password) throw( SQLException, RuntimeException )
{
    MutexGuard aGuard(m_aMutex);
    if (OComponentHelper::rBHelper.bDisposed)
        throw DisposedException();

    Reference< XConnection > xSdbcConn = buildLowLevelConnection(user, password);
    DBG_ASSERT( xSdbcConn.is(), "ODatabaseSource::getConnection: invalid return value of buildLowLevelConnection!" );
        // buildLowLevelConnection is expected to always succeed

    Reference< XConnection > xConn;
    if ( xSdbcConn.is() )
    {
        // build a connection server and return it (no stubs)
        xConn = new OConnection(*this, m_aConfigurationNode.openNode(CONFIGKEY_DBLINK_TABLES),m_aConfigurationNode,xSdbcConn, m_xServiceFactory);
        Reference< XComponent> xComp(xConn,UNO_QUERY);
        if(xComp.is())
        {
            xComp->addEventListener(this);
        }
        m_aConnections.push_back(OWeakConnection(xConn));
    }

    return xConn;
}


//------------------------------------------------------------------------------
void ODatabaseSource::flush_NoBroadcast_NoCommit()
{
    flushToConfiguration();
}

//------------------------------------------------------------------------------
Reference< XNameAccess > SAL_CALL ODatabaseSource::getBookmarks(  ) throw (RuntimeException)
{
    return static_cast< XNameContainer* >(&m_aBookmarks);
}

//------------------------------------------------------------------------------
Reference< XNameAccess > SAL_CALL ODatabaseSource::getQueryDefinitions( ) throw(RuntimeException)
{
    return static_cast< XNameContainer* >(&m_aCommandDefinitions);
}
// -----------------------------------------------------------------------------
class OConnectionNotifier //: public ::std::unary_function<OWeakConnection,void>
{
    ::utl::OConfigurationTreeRoot m_aConfigTreeNode;
public:
    OConnectionNotifier()
    {
    }
    OConnectionNotifier(const ::utl::OConfigurationTreeRoot& _rConfigTreeNode) : m_aConfigTreeNode(_rConfigTreeNode)
    {
    }

    void operator()(OWeakConnection& _xConnection)
    {
        Reference<XConnection> xConn(_xConnection);
        Reference< XUnoTunnel > xTunnel(xConn, UNO_QUERY);

        OConnection* pObjectImpl = NULL;
        if (xTunnel.is())
        {
            static Sequence<sal_Int8> aTunnelId = OConnection::getUnoTunnelImplementationId();
            pObjectImpl = reinterpret_cast<OConnection*> (xTunnel->getSomething(aTunnelId));
        }
        if(pObjectImpl)
        {
            if (m_aConfigTreeNode.isValid())
                pObjectImpl->setNewConfigNode(m_aConfigTreeNode);
            else
                pObjectImpl->flushMembers();
        }
    }
};
// -----------------------------------------------------------------------------
void ODatabaseSource::inserted(const Reference< XInterface >& _rxContainer, const ::rtl::OUString& _rRegistrationName, const OConfigurationTreeRoot& _rConfigRoot)
{
    MutexGuard aGuard(m_aMutex);

    DBG_ASSERT(!m_aConfigurationNode.isValid(), "ODatabaseSource::inserted : you're not allowed to change the location if the current one is valid !");
    DBG_ASSERT(_rConfigRoot.isValid(), "ODatabaseSource::inserted : invalid argument (the configuration root) !");
    DBG_ASSERT(_rRegistrationName.getLength() != 0, "ODatabaseSource::inserted : invalid argument (the name) !");
    DBG_ASSERT(!m_xParent.is(), "ODatabaseSource::inserted : already connected to a parent !");

    m_aConfigurationNode = _rConfigRoot;
    m_xParent = _rxContainer;
    m_sName = _rRegistrationName;

    if (m_aConfigurationNode.isValid())
    {
        // propagate the new location to our documents
        // (Usually, we do this from within the ctor which gets a config node, but if we're here, we have been
        // instantiated as service, so we didn't have any config location before, so the documents haven't any, too.)
        initializeDocuments(sal_False);
        // we now have to set the new confignode at our connections
        ::std::for_each(m_aConnections.begin(),m_aConnections.end(),OConnectionNotifier(m_aConfigurationNode));
        // and now flush
        flushToConfiguration();
    }

    // adjust our readonly flag
    m_bReadOnly = !m_aConfigurationNode.isValid() || m_aConfigurationNode.isReadonly();
}

//------------------------------------------------------------------------------
void ODatabaseSource::removed()
{
    MutexGuard aGuard(m_aMutex);
    DBG_ASSERT(m_xParent.is(), "ODatabaseSource::removed : not connected to a parent !");

    // dispose the document containers so they release the documents and the configuration resources
    m_aBookmarks.dispose();
    m_aCommandDefinitions.dispose();

    m_xParent = NULL;
    m_aConfigurationNode.clear();
    m_sName = ::rtl::OUString();

    m_bReadOnly = sal_False;
}

//------------------------------------------------------------------------------
void ODatabaseSource::initializeDocuments(sal_Bool _bRead)
{
    // initialize the document containers
    m_aBookmarks.initialize(m_aConfigurationNode.openNode(CONFIGKEY_DBLINK_BOOKMARKS).cloneAsRoot(), _bRead);
    m_aCommandDefinitions.initialize(m_aConfigurationNode.openNode(CONFIGKEY_DBLINK_QUERYDOCUMENTS).cloneAsRoot(), _bRead);
}

//------------------------------------------------------------------------------
void ODatabaseSource::initializeFromConfiguration()
{
    if (!m_aConfigurationNode.isValid())
    {
        DBG_ERROR("ODatabaseSource::initializeFromConfiguration : invalid configuration key !");
        return;
    }

    m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_CONNECTURL) >>= m_sConnectURL;
    m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_USER) >>= m_sUser;
    m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_TABLEFILTER) >>= m_aTableFilter;
    m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_TABLETYEFILTER) >>= m_aTableTypeFilter;
    m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_LOGINTIMEOUT) >>= m_nLoginTimeout;
    m_bPasswordRequired = ::cppu::any2bool(m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_PASSWORDREQUIRED));
    m_bSuppressVersionColumns = ::cppu::any2bool(m_aConfigurationNode.getNodeValue(CONFIGKEY_DBLINK_SUPPRESSVERSIONCL));
    m_aConfigurationNode.getNodeValue(CONFIGKEY_LAYOUTINFORMATION) >>= m_aLayoutInformation;

    // the property sequence in m_aInfo
    OConfigurationNode aInfoNode = m_aConfigurationNode.openNode(CONFIGKEY_DBLINK_INFO);
    if (aInfoNode.isValid())
    {
        Sequence< ::rtl::OUString > aNodeNames = aInfoNode.getNodeNames();
        m_aInfo.realloc(aNodeNames.getLength());
        PropertyValue* pInfos = m_aInfo.getArray();

        for (	const ::rtl::OUString* pNodeNames = aNodeNames.getConstArray() + aNodeNames.getLength() - 1;
                pNodeNames >= aNodeNames.getConstArray();
                --pNodeNames, ++pInfos
            )
        {
            OConfigurationNode aItemSubNode = aInfoNode.openNode(*pNodeNames);
            pInfos->Name = *pNodeNames;
            pInfos->Value = aItemSubNode.getNodeValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Value")));
        }
    }

    initializeDocuments();
}

//------------------------------------------------------------------------------
void ODatabaseSource::flushDocuments()
{
    if ( m_aBookmarks.hasValidLocation() )
        m_aBookmarks.flush();
    if ( m_aCommandDefinitions.hasValidLocation() )
        m_aCommandDefinitions.flush();
}
// -----------------------------------------------------------------------------
void ODatabaseSource::flushTables()
{
    // flush all tables and queries
    ::std::for_each(m_aConnections.begin(),m_aConnections.end(),OConnectionNotifier());
}
//------------------------------------------------------------------------------
void ODatabaseSource::flushToConfiguration()
{
    if (!m_aConfigurationNode.isValid())
    {
        DBG_ERROR("ODatabaseSource::flushToConfiguration : invalid configuration key !");
        return;
    }

    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_CONNECTURL, makeAny(m_sConnectURL));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_USER, makeAny(m_sUser));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_TABLEFILTER, makeAny(m_aTableFilter));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_TABLETYEFILTER, makeAny(m_aTableTypeFilter));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_LOGINTIMEOUT, makeAny(m_nLoginTimeout));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_PASSWORDREQUIRED, ::cppu::bool2any(m_bPasswordRequired));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_DBLINK_SUPPRESSVERSIONCL, ::cppu::bool2any(m_bSuppressVersionColumns));
    m_aConfigurationNode.setNodeValue(CONFIGKEY_LAYOUTINFORMATION, makeAny(m_aLayoutInformation));

    // write the additional info tags
    OConfigurationNode aInfoNode = m_aConfigurationNode.openNode(CONFIGKEY_DBLINK_INFO);
    if (aInfoNode.isValid())
    {
        // stage 0: collect all names under the info node which currently exist
        ::std::set< rtl::OUString > aExistentKeys;
        Sequence< ::rtl::OUString > aNodeNames = aInfoNode.getNodeNames();
        const ::rtl::OUString* pNodeNames		=					aNodeNames.getConstArray();
        const ::rtl::OUString* pNodeNamesEnd	= pNodeNames	+	aNodeNames.getLength();
        for ( ; pNodeNames != pNodeNamesEnd; ++pNodeNames )
            aExistentKeys.insert( *pNodeNames );


        // stage 1: write all currently set info values
        static ::rtl::OUString s_sValueConfigKey( RTL_CONSTASCII_USTRINGPARAM("Value") );
        ::std::set< rtl::OUString > aUsedKeys;
        const PropertyValue* pInfoValues = m_aInfo.getConstArray();
        for (sal_Int32 i=0; i<m_aInfo.getLength(); ++i, ++pInfoValues)
        {
            OConfigurationNode aSettingsItem;
            if (aExistentKeys.end() == aExistentKeys.find(pInfoValues->Name))
            {
                // we do not have such a key -> create it
                aSettingsItem = aInfoNode.createNode(pInfoValues->Name);
            }
            else
            {
                aSettingsItem = aInfoNode.openNode(pInfoValues->Name);
                aExistentKeys.erase(pInfoValues->Name);
                    // no need to delete this previously-existing node afterwards ....
            }
            aSettingsItem.setNodeValue(s_sValueConfigKey, pInfoValues->Value);
        }

        // stage 2: delete all info values which may be present in the registry, but not used by the current values
        for (	::std::set< rtl::OUString >::const_iterator aErase = aExistentKeys.begin();
                aErase != aExistentKeys.end();
                ++aErase
            )
        {
            aInfoNode.removeNode(*aErase);
        }
    }

    flushDocuments();
    flushTables();
    // TODO : flushing of queries/tables ?

    m_aConfigurationNode.commit( );
}

//........................................................................
}	// namespace dbaccess
//........................................................................

