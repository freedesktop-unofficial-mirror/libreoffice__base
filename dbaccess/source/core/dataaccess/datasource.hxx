/*************************************************************************
 *
 *  $RCSfile: datasource.hxx,v $
 *
 *  $Revision: 1.19 $
 *
 *  last change: $Author: oj $ $Date: 2002-08-12 08:54:23 $
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
#define _DBA_COREDATAACCESS_DATASOURCE_HXX_

#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XBOOKMARKSSUPPLIER_HPP_
#include <com/sun/star/sdb/XBookmarksSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XISOLATEDCONNECTION_HPP_
#include <com/sun/star/sdbc/XIsolatedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef _CPPUHELPER_PROPSHLP_HXX
#include <cppuhelper/propshlp.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE8_HXX_
#include <cppuhelper/implbase8.hxx>
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _DBA_REGHELPER_HXX_
#include "dba_reghelper.hxx"
#endif
#ifndef _DBA_CORE_BOOKMARKCONTAINER_HXX_
#include "bookmarkcontainer.hxx"
#endif
#ifndef _DBA_COREDATAACCESS_COMMANDCONTAINER_HXX_
#include "commandcontainer.hxx"
#endif
#ifndef _DBA_CORE_CONTAINERELEMENT_HXX_
#include "containerelement.hxx"
#endif
#ifndef _DBA_CORE_CONFIGURATIONFLUSHABLE_HXX_
#include "configurationflushable.hxx"
#endif
#ifndef _VOS_REF_HXX_
#include <vos/ref.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _UNOTOOLS_CONFIGNODE_HXX_
#include <unotools/confignode.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
//........................................................................
namespace dbaccess
{
//........................................................................

class OSharedConnectionManager;
typedef ::com::sun::star::uno::WeakReference< ::com::sun::star::sdbc::XConnection > OWeakConnection;
typedef std::vector< OWeakConnection > OWeakConnectionArray;

//============================================================
//= ODatabaseSource
//============================================================
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
    ODatabaseSource_CreateInstance(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

typedef	::cppu::ImplHelper8	<	::com::sun::star::lang::XServiceInfo
                            ,	::com::sun::star::lang::XUnoTunnel
                            ,	::com::sun::star::sdbc::XDataSource
                            ,	::com::sun::star::sdb::XBookmarksSupplier
                            ,	::com::sun::star::sdb::XQueryDefinitionsSupplier
                            ,	::com::sun::star::sdb::XCompletedConnection
                            ,	::com::sun::star::lang::XEventListener
                            ,	::com::sun::star::sdbc::XIsolatedConnection
                            >	ODatabaseSource_Base;

class ODatabaseSource	:public ::comphelper::OBaseMutex
                    ,public OSubComponent
                    ,public OContainerElement
                    ,public OConfigurationFlushable
                    ,public ::cppu::OPropertySetHelper
                    ,public ::comphelper::OPropertyArrayUsageHelper < ODatabaseSource >
                    ,public ODatabaseSource_Base
{
    friend class ODatabaseContext;
    friend class OConnection;
    friend class OSharedConnectionManager;
    friend ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
        ODatabaseSource_CreateInstance(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

protected:
    OWeakConnectionArray		m_aConnections;

    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >	m_xServiceFactory;

    OBookmarkContainer				m_aBookmarks;
    OCommandContainer				m_aCommandDefinitions;
    ::utl::OConfigurationNode		m_aRenameNode;		// is set when the datasource was removed to allow the renaming

// <properties>
    ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >
                                                        m_xNumberFormatsSupplier;
    ::rtl::OUString										m_sConnectURL;
    ::rtl::OUString										m_sName;		// transient, our creator has to tell us the title
    ::rtl::OUString										m_sUser;
    ::rtl::OUString										m_aPassword;	// transient !
    ::com::sun::star::uno::Sequence< ::rtl::OUString >	m_aTableFilter;
    ::com::sun::star::uno::Sequence< ::rtl::OUString >	m_aTableTypeFilter;
    ::com::sun::star::uno::Sequence< sal_Int8>			m_aLayoutInformation;
    sal_Int32											m_nLoginTimeout;
    sal_Bool											m_bReadOnly : 1;
    sal_Bool											m_bPasswordRequired : 1;
    sal_Bool											m_bSuppressVersionColumns : 1;
    ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >
                                                        m_aInfo;
// </properties>

    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener> m_xSharedConnectionManager;
    OSharedConnectionManager*							m_pSharedConnectionManager;
protected:
    ODatabaseSource(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory);
    virtual ~ODatabaseSource();
public:
    ODatabaseSource(
        ::cppu::OWeakObject& _rParent,
        const ::utl::OConfigurationNode& _rConfigRoot,
        const ::rtl::OUString& _rRegistrationName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory);
    

// com::sun::star::lang::XTypeProvider
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes() throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

// com::sun::star::uno::XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type & rType ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL acquire() throw( );
    virtual void SAL_CALL release() throw( );

// ::com::sun::star::lang::XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::lang::XServiceInfo - static methods
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::rtl::OUString getImplementationName_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
        SAL_CALL Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

// com::sun::star::lang::XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);
    static ::com::sun::star::uno::Sequence< sal_Int8 > getUnoTunnelImplementationId() throw (::com::sun::star::uno::RuntimeException);

// OComponentHelper
    virtual void SAL_CALL disposing(void);

// com::sun::star::beans::XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);
    // XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

// comphelper::OPropertyArrayUsageHelper
    virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

// cppu::OPropertySetHelper
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    virtual sal_Bool SAL_CALL convertFastPropertyValue(
                            ::com::sun::star::uno::Any & rConvertedValue,
                            ::com::sun::star::uno::Any & rOldValue,
                            sal_Int32 nHandle,
                            const ::com::sun::star::uno::Any& rValue )
                                throw (::com::sun::star::lang::IllegalArgumentException);
    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(
                                sal_Int32 nHandle,
                                const ::com::sun::star::uno::Any& rValue
                                                 )
                                                 throw (::com::sun::star::uno::Exception);
    virtual void SAL_CALL getFastPropertyValue( ::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;

// ::com::sun::star::sdb::XCompletedConnection
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL connectWithCompletion( const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >& handler ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

// ::com::sun::star::sdbc::XDataSource
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getConnection( const ::rtl::OUString& user, const ::rtl::OUString& password ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setLoginTimeout( sal_Int32 seconds ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getLoginTimeout(  ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

// :: com::sun::star::sdb::XBookmarksSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getBookmarks(  ) throw (::com::sun::star::uno::RuntimeException);

// :: com::sun::star::sdb::XQueryDefinitionsSupplier
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getQueryDefinitions(  ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::sdbc::XIsolatedConnection
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getIsolatedConnection( const ::rtl::OUString& user, const ::rtl::OUString& password ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getIsolatedConnectionWithCompletion( const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >& handler ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

protected:
    // OConfigurationFlushable
    virtual void flush_NoBroadcast_NoCommit();

protected:
// helper
    const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >&
            getNumberFormatsSupplier();

    /** open a connection for the current settings. this is the simple connection we get from the driver
        manager, so it can be used as a master for a "high level" sdb connection.
    */
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > buildLowLevelConnection(
        const ::rtl::OUString& _rUid, const ::rtl::OUString& _rPwd 
        );

    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > buildIsolatedConnection(
        const rtl::OUString& user, const rtl::OUString& password
        );


// OContainerElement
    virtual void		inserted(
        const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContainer,
        const ::rtl::OUString& _rElementName,
        const ::utl::OConfigurationTreeRoot& _rConfigRoot);

    virtual void		removed();

    virtual sal_Bool	isContainerElement() const { return m_aConfigurationNode.isValid(); }

// other stuff
    void	initializeFromConfiguration();
    void	flushToConfiguration();

    void	initializeDocuments(sal_Bool _bRead = sal_True);
    void	flushDocuments();
    void	flushTables();

    inline ::utl::OConfigurationNode getRenameNode() const { return m_aRenameNode; }
    inline void setRenameNode(const ::utl::OConfigurationNode& _aOldNode) { m_aRenameNode = _aOldNode; }
    inline void clearRenameNode() { m_aRenameNode.clear(); }		   

    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getConnection( const ::rtl::OUString& user, const ::rtl::OUString& password , sal_Bool _bIsolated) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL connectWithCompletion( const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >& handler , sal_Bool _bIsolated) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

    void clearConnections();
};

//........................................................................
}	// namespace dbaccess
//........................................................................

#endif // _DBA_COREDATAACCESS_DATALINK_HXX_

