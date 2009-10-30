/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: definitioncolumn.hxx,v $
 * $Revision: 1.7 $
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
#ifndef _DBACORE_DEFINITIONCOLUMN_HXX_
#define _DBACORE_DEFINITIONCOLUMN_HXX_

#include "apitools.hxx"
#include "column.hxx"
#include "columnsettings.hxx"

#include <com/sun/star/sdbc/DataType.hpp>
#include <com/sun/star/sdbc/ColumnValue.hpp>
#include <com/sun/star/container/XChild.hpp>

#include <comphelper/IdPropArrayHelper.hxx>
#include <comphelper/uno3.hxx>
#include <cppuhelper/implbase1.hxx>


namespace dbaccess
{

    typedef ::cppu::ImplHelper1< ::com::sun::star::container::XChild > TXChild;
    /**
     *	provides the properties for description. A descriptor could be used to create a new table column.
     */
    class OTableColumnDescriptor : public OColumn
                                  ,public OColumnSettings
                                  ,public ::comphelper::OPropertyArrayUsageHelper < OTableColumnDescriptor >
                                  ,public TXChild
    {
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >			m_xParent;
    protected:
    //	<properties>
        rtl::OUString			m_aTypeName;
        rtl::OUString			m_aDescription;
        rtl::OUString			m_aDefaultValue;
        rtl::OUString			m_aAutoIncrementValue;
        sal_Int32				m_nType;
        sal_Int32				m_nPrecision;
        sal_Int32				m_nScale;
        sal_Int32				m_nIsNullable;
        sal_Bool				m_bAutoIncrement;
        sal_Bool				m_bRowVersion;
        sal_Bool				m_bCurrency;
    //	</properties>
    public:
        OTableColumnDescriptor():m_nType(::com::sun::star::sdbc::DataType::SQLNULL)
                           ,m_nPrecision(0)
                           ,m_nScale(0)
                           ,m_nIsNullable(::com::sun::star::sdbc::ColumnValue::NULLABLE_UNKNOWN)
                           ,m_bAutoIncrement(sal_False)
                           ,m_bRowVersion(sal_False)
                           ,m_bCurrency(sal_False){}

        DECLARE_XINTERFACE( )
    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::container::XChild
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL getParent(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setParent( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& Parent ) throw (::com::sun::star::lang::NoSupportException, ::com::sun::star::uno::RuntimeException);

    // ::comphelper::OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper() const;

    // ::cppu::OPropertySetHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual void SAL_CALL getFastPropertyValue(
                                    ::com::sun::star::uno::Any& rValue,
                                    sal_Int32 nHandle
                                         ) const;
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

    protected:
        // XUnoTunnel
        virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);

    protected:
        using OColumn::getFastPropertyValue;
    };

    /** describes a column of a table or query
     */
    class OTableColumn  :public OTableColumnDescriptor
                        ,public ::comphelper::OPropertyArrayUsageHelper < OTableColumn >
    {
        friend class ODBTable;

    protected:
        virtual ~OTableColumn();
    public:
        OTableColumn(const ::rtl::OUString& _rName);
        OTableColumn(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xColumn);

    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // ::comphelper::OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper() const;
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
    };

    /**
     *	describes all properties for a columns of a table. Only the view parts are provided
     *	directly, all the other parts are derived from a driver implementation
     */
    class OColumnWrapper : public OColumn
    {
    protected:
        // definition which is provided by a driver!
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
                                m_xAggregate;

        sal_Int32				m_nColTypeID;

    protected:
        OColumnWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rCol);
        virtual ~OColumnWrapper();

    public:
        virtual void SAL_CALL getFastPropertyValue(
                                ::com::sun::star::uno::Any& rValue,
                                sal_Int32 nHandle
                                 ) const;
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

        virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);
    //	Helper
//		sal_Int32	getColumnTypeID() const {return m_nColTypeID;}

    protected:
        using OColumn::getFastPropertyValue;
    };

    /**
     *	provides the properties for description. A descriptor could be used to create a new table column.
     */
    class OTableColumnDescriptorWrapper :   public OColumnWrapper,
                                            public OColumnSettings,
                                            public ::comphelper::OIdPropertyArrayUsageHelper < OTableColumnDescriptorWrapper >
    {
        sal_Bool m_bPureWrap;
    public:
        OTableColumnDescriptorWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rCol,sal_Bool _bPureWrap = sal_False)
                            :OColumnWrapper(rCol),m_bPureWrap(_bPureWrap){}

    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // OIdPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper(sal_Int32 nId) const;

    // cppu::OPropertySetHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual void SAL_CALL getFastPropertyValue(
                                    ::com::sun::star::uno::Any& rValue,
                                    sal_Int32 nHandle
                                         ) const;
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

    protected:
        // XUnoTunnel
        virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);

    protected:
        using OColumnWrapper::getFastPropertyValue;
    };

    /**
     *	describes all properties for a columns of a table. Only the view parts are provided
     *	directly, all the other parts are derived from a driver implementation
     */
    class OTableColumnWrapper : public OTableColumnDescriptorWrapper,
                                public ::comphelper::OIdPropertyArrayUsageHelper < OTableColumnWrapper >
    {
    protected:
        ~OTableColumnWrapper();
    public:
        OTableColumnWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rCol
                            ,const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rColDefintion
                            ,sal_Bool _bPureWrap = sal_False);

    // ::com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // OIdPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper(sal_Int32 nId) const;
    };

    /**
     *	describes all properties for a columns of an index.
     */
    class OIndexColumnWrapper : public OColumnWrapper,
                                public ::comphelper::OPropertyArrayUsageHelper < OIndexColumnWrapper >
    {
    protected:
    //	<properties>
        sal_Bool				m_bAscending;
    //	</properties>

    public:
        OIndexColumnWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rCol )
                            :OColumnWrapper(rCol) {}

    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper() const;

        virtual void SAL_CALL getFastPropertyValue(
                                    ::com::sun::star::uno::Any& rValue,
                                    sal_Int32 nHandle
                                         ) const;

    protected:
        using OColumnWrapper::getFastPropertyValue;
    };

    /**
     *	describes all properties for a columns of an key column.
     */
    class OKeyColumnWrapper : public OColumnWrapper,
                              public ::comphelper::OPropertyArrayUsageHelper < OKeyColumnWrapper >
    {
    protected:
    //	<properties>
        rtl::OUString			m_aRelatedColumn;
    //	</properties>

    public:
        OKeyColumnWrapper(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& rCol)
                        :OColumnWrapper(rCol) {}

    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper() const;

        virtual void SAL_CALL getFastPropertyValue(
                                    ::com::sun::star::uno::Any& rValue,
                                    sal_Int32 nHandle
                                         ) const;

    protected:
        using OColumnWrapper::getFastPropertyValue;
    };
}
#endif // _DBACORE_DEFINITIONCOLUMN_HXX_

