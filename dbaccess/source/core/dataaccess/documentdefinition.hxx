/*************************************************************************
 *
 *  $RCSfile: documentdefinition.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: fs $ $Date: 2000-10-11 11:19:39 $
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

#ifndef _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_
#define _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_

#ifndef _CPPUHELPER_PROPSHLP_HXX
#include <cppuhelper/propshlp.hxx>
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_HXX_
#include <cppuhelper/interfacecontainer.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

#ifndef _DBA_CORE_CONTAINERELEMENT_HXX_
#include "containerelement.hxx"
#endif
#ifndef _DBA_REGISTRATION_HELPER_HXX_
#include "registrationhelper.hxx"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif

#ifndef _COM_SUN_STAR_LANG_XUNOTUNNEL_HPP_
#include <com/sun/star/lang/XUnoTunnel.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XFLUSHABLE_HPP_
#include <com/sun/star/util/XFlushable.hpp>
#endif

//==========================================================================
//= ODocumentDefinition - a database "document" which is simply a link to a real
//=					  document
//==========================================================================
typedef ::cppu::WeakImplHelper3<
                    ::com::sun::star::lang::XUnoTunnel,
                    ::com::sun::star::lang::XServiceInfo,
                    ::com::sun::star::util::XFlushable
                    > ODocumentDefinition_Base;

class ODocumentDefinition
        :public ODocumentDefinition_Base
        ,public OContainerElement
        ,public OMutexAndBroadcastHelper
        ,public ::cppu::OPropertySetHelper
        ,public ::comphelper::OPropertyArrayUsageHelper< ODocumentDefinition >
{
protected:
    ::cppu::OInterfaceContainerHelper	m_aFlushListeners;

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >				m_xContainer;
    ::com::sun::star::uno::Reference< ::com::sun::star::registry::XRegistryKey >		m_xConfigurationRoot;

// <properties>
    ::rtl::OUString		m_sElementName;
    ::rtl::OUString		m_sDocumentLocation;
// </properties>

private:
    ODocumentDefinition();

protected:
    ~ODocumentDefinition();

public:
    ODocumentDefinition(
            const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContainer,
            const ::rtl::OUString& _rElementName,
            const ::com::sun::star::uno::Reference< ::com::sun::star::registry::XRegistryKey >& _rxConfigurationRoot
        );

// ::com::sun::star::uno::XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire(  ) throw(::com::sun::star::uno::RuntimeException) { ODocumentDefinition_Base::acquire(); }
    virtual void SAL_CALL release(  ) throw(::com::sun::star::uno::RuntimeException) { ODocumentDefinition_Base::release(); }

// ::com::sun::star::lang::XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::lang::XServiceInfo - static methods
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::rtl::OUString getImplementationName_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
         SAL_CALL Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

// ::com::sun::star::lang::XUnoTunnel
    virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::beans::XPropertySet
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::util::XFlushable
    virtual void SAL_CALL flush(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addFlushListener( const ::com::sun::star::uno::Reference< ::com::sun::star::util::XFlushListener >& l ) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeFlushListener( const ::com::sun::star::uno::Reference< ::com::sun::star::util::XFlushListener >& l ) throw(::com::sun::star::uno::RuntimeException);

// OPropertySetHelper
    virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

    virtual sal_Bool SAL_CALL convertFastPropertyValue(
                ::com::sun::star::uno::Any& rConvertedValue, ::com::sun::star::uno::Any& rOldValue,
                sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue)
            throw (::com::sun::star::lang::IllegalArgumentException);

    virtual void SAL_CALL setFastPropertyValue_NoBroadcast(
                sal_Int32 nHandle, const ::com::sun::star::uno::Any& rValue )
            throw (::com::sun::star::uno::Exception);

    virtual void SAL_CALL getFastPropertyValue(
                ::com::sun::star::uno::Any& rValue, sal_Int32 nHandle ) const;

// OContainerElement
    virtual void		inserted(
        const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContainer,
        const ::rtl::OUString& _rElementName,
        const ::com::sun::star::uno::Reference< ::com::sun::star::registry::XRegistryKey >& _rxConfigRoot);

    virtual void		removed();

    virtual sal_Bool	isContainerElement() const { return m_xConfigurationRoot.is(); }

protected:
// OPropertyArrayUsageHelper
    virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    /// read the objects properties from the configuration
    void initializeFromConfiguration();
};

#endif // _DBA_COREDATAACCESS_DOCUMENTDEFINITION_HXX_

