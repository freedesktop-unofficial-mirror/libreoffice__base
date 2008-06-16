/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: DatabaseDataProvider.hxx,v $
 * $Revision: 1.4 $
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
#ifndef DBA_DATABASEDATAPROVIDER_HXX_INCLUDED
#define DBA_DATABASEDATAPROVIDER_HXX_INCLUDED

#include "sal/config.h"

#include "com/sun/star/uno/XComponentContext.hpp"
#include "com/sun/star/lang/XServiceInfo.hpp"
#include "com/sun/star/chart2/data/XDatabaseDataProvider.hpp"
#include "com/sun/star/chart2/XInternalDataProvider.hpp"
#include <com/sun/star/sdbc/XRowSet.hpp>
#include <com/sun/star/sdbc/XParameters.hpp>
#include <com/sun/star/container/XChild.hpp>

#include "cppuhelper/compbase3.hxx"
#include "cppuhelper/basemutex.hxx"
#include "cppuhelper/propertysetmixin.hxx"
#include <cppuhelper/implementationentry.hxx>

#include <comphelper/sequence.hxx>

#include "connectivity/parameters.hxx"
#include "connectivity/filtermanager.hxx"


namespace dbaccess
{

class DatabaseDataSource;
typedef ::cppu::WeakComponentImplHelper3<   ::com::sun::star::chart2::data::XDatabaseDataProvider
                                          , ::com::sun::star::container::XChild
                                          , ::com::sun::star::lang::XServiceInfo > TDatabaseDataProvider;

class DatabaseDataProvider: private ::cppu::BaseMutex,
                            public TDatabaseDataProvider,
                            public ::cppu::PropertySetMixin< ::com::sun::star::chart2::data::XDatabaseDataProvider >
{
public:
    explicit DatabaseDataProvider(::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > const & context);

    // ::com::sun::star::lang::XServiceInfo - static methods
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::rtl::OUString getImplementationName_Static(void) throw( ::com::sun::star::uno::RuntimeException );
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
        SAL_CALL Create(::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext > const & context);

private:
    // ::com::sun::star::uno::XInterface:
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface(::com::sun::star::uno::Type const & type) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire() throw ()
        { TDatabaseDataProvider::acquire(); }
    virtual void SAL_CALL release() throw ()
        { TDatabaseDataProvider::release(); }

    // ::com::sun::star::lang::XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::chart2::data::XDataProvider:
    virtual ::sal_Bool SAL_CALL createDataSourcePossible(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > & aArguments) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::chart2::data::XDataSource > SAL_CALL createDataSource(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > & aArguments) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > SAL_CALL detectArguments(const ::com::sun::star::uno::Reference< ::com::sun::star::chart2::data::XDataSource > & xDataSource) throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Bool SAL_CALL createDataSequenceByRangeRepresentationPossible(const ::rtl::OUString & aRangeRepresentation) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::chart2::data::XDataSequence > SAL_CALL createDataSequenceByRangeRepresentation(const ::rtl::OUString & aRangeRepresentation) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sheet::XRangeSelection > SAL_CALL getRangeSelection() throw (::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::chart2::data::XRangeXMLConversion:
    virtual ::rtl::OUString SAL_CALL convertRangeToXML(const ::rtl::OUString & aRangeRepresentation) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);
    virtual ::rtl::OUString SAL_CALL convertRangeFromXML(const ::rtl::OUString & aXMLRange) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);

    // ::com::sun::star::lang::XInitialization:
    virtual void SAL_CALL initialize(const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any > & aArguments) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::uno::Exception);

    // ::com::sun::star::beans::XPropertySet:
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setPropertyValue(const ::rtl::OUString & aPropertyName, const ::com::sun::star::uno::Any & aValue) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::beans::PropertyVetoException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::lang::WrappedTargetException);
    virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(const ::rtl::OUString & PropertyName) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException);
    virtual void SAL_CALL addPropertyChangeListener(const ::rtl::OUString & aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & xListener) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException);
    virtual void SAL_CALL removePropertyChangeListener(const ::rtl::OUString & aPropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertyChangeListener > & aListener) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException);
    virtual void SAL_CALL addVetoableChangeListener(const ::rtl::OUString & PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener > & aListener) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException);
    virtual void SAL_CALL removeVetoableChangeListener(const ::rtl::OUString & PropertyName, const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XVetoableChangeListener > & aListener) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::lang::WrappedTargetException);

    // ::com::sun::star::chart2::data::XDatabaseDataProvider:
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getMasterFields() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setMasterFields(const ::com::sun::star::uno::Sequence< ::rtl::OUString > & the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getDetailFields() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setDetailFields(const ::com::sun::star::uno::Sequence< ::rtl::OUString > & the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getCommand() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setCommand(const ::rtl::OUString & the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Int32 SAL_CALL getCommandType() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setCommandType(::sal_Int32 the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getFilter() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setFilter(const ::rtl::OUString & the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Bool SAL_CALL getApplyFilter() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setApplyFilter( ::sal_Bool _applyfilter ) throw (::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getHavingClause() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setHavingClause( const ::rtl::OUString& _havingclause ) throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getGroupBy() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setGroupBy( const ::rtl::OUString& _groupby ) throw (::com::sun::star::beans::UnknownPropertyException, ::com::sun::star::uno::RuntimeException);
    virtual ::rtl::OUString SAL_CALL getOrder() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setOrder( const ::rtl::OUString& _order ) throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Bool SAL_CALL getEscapeProcessing() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setEscapeProcessing(::sal_Bool the_value) throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Int32 SAL_CALL getRowLimit() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setRowLimit( ::sal_Int32 _rowlimit ) throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getActiveConnection() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setActiveConnection(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > & the_value) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);
    virtual ::rtl::OUString SAL_CALL getDataSourceName() throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setDataSourceName( const ::rtl::OUString& _datasourcename ) throw (::com::sun::star::uno::RuntimeException);

    // com::sun::star::sdbc::XParameters
    virtual void SAL_CALL setNull(sal_Int32 parameterIndex, sal_Int32 sqlType) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setObjectNull(sal_Int32 parameterIndex, sal_Int32 sqlType, const ::rtl::OUString& typeName) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setBoolean(sal_Int32 parameterIndex, sal_Bool x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setByte(sal_Int32 parameterIndex, sal_Int8 x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setShort(sal_Int32 parameterIndex, sal_Int16 x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setInt(sal_Int32 parameterIndex, sal_Int32 x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setLong(sal_Int32 parameterIndex, sal_Int64 x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setFloat(sal_Int32 parameterIndex, float x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setDouble(sal_Int32 parameterIndex, double x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setString(sal_Int32 parameterIndex, const ::rtl::OUString& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setBytes(sal_Int32 parameterIndex, const ::com::sun::star::uno::Sequence< sal_Int8 >& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setDate(sal_Int32 parameterIndex, const ::com::sun::star::util::Date& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setTime(sal_Int32 parameterIndex, const ::com::sun::star::util::Time& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setTimestamp(sal_Int32 parameterIndex, const ::com::sun::star::util::DateTime& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setBinaryStream(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream>& x, sal_Int32 length) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setCharacterStream(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream>& x, sal_Int32 length) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setObject(sal_Int32 parameterIndex, const ::com::sun::star::uno::Any& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setObjectWithInfo(sal_Int32 parameterIndex, const ::com::sun::star::uno::Any& x, sal_Int32 targetSqlType, sal_Int32 scale) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setRef(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRef>& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setBlob(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XBlob>& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setClob(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XClob>& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setArray(sal_Int32 parameterIndex, const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XArray>& x) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL clearParameters() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

    // com::sun::star::sdbc::XRowSet
    virtual void SAL_CALL execute() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL addRowSetListener(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSetListener>& _rxListener) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeRowSetListener(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSetListener>& _rxListener) throw(::com::sun::star::uno::RuntimeException);

    // com::sun::star::sdbc::XResultSet
    virtual sal_Bool SAL_CALL next() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isBeforeFirst() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isAfterLast() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isFirst() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL isLast() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL beforeFirst() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL afterLast() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL first() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL last() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Int32 SAL_CALL getRow() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL absolute(sal_Int32 row) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL relative(sal_Int32 rows) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL previous() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL refreshRow() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL rowUpdated() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL rowInserted() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL rowDeleted() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL getStatement() throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

    // conatiner::XChild
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > SAL_CALL getParent(  ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL setParent( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& Parent ) throw (::com::sun::star::lang::NoSupportException, ::com::sun::star::uno::RuntimeException);
private:
    DatabaseDataProvider(DatabaseDataProvider &); // not defined
    void operator =(DatabaseDataProvider &); // not defined

    virtual ~DatabaseDataProvider() {}

    // This function is called upon disposing the component,
    // if your component needs special work when it becomes
    // disposed, do it here.
    virtual void SAL_CALL disposing();

    void impl_fillRowSet_throw();
    bool impl_executeRowSet_throw(::osl::ResettableMutexGuard& _rClearForNotifies);
    bool fillParameters( ::osl::ResettableMutexGuard& _rClearForNotifies, const ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >& _rxCompletionHandler );
    void impl_fillInternalDataProvider_throw();
    void impl_invalidateParameter_nothrow();

    template <typename T> void set(	 const ::rtl::OUString& _sProperty
                                        ,const T& _Value
                                        ,T& _member)
    {
        BoundListeners l;
        {
            ::osl::MutexGuard aGuard(m_aMutex);
            prepareSet(_sProperty, ::com::sun::star::uno::makeAny(_member), ::com::sun::star::uno::makeAny(_Value), &l);
            _member = _Value;
        }
        l.notify();
    }

    ::dbtools::ParameterManager m_aParameterManager;
    ::dbtools::FilterManager    m_aFilterManager;

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >            m_xContext;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >                 m_xActiveConnection;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowSet >                     m_xRowSet;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart2::XInternalDataProvider >     m_xInternal;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart2::data::XRangeXMLConversion>  m_xRangeConversion;
    // the object doin' most of the work - an SDB-rowset
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XAggregation> 		            m_xAggregate;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>                m_xAggregateSet;
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> 		            m_xParent;
    ::com::sun::star::uno::Sequence< ::rtl::OUString >                                      m_MasterFields;
    ::com::sun::star::uno::Sequence< ::rtl::OUString >                                      m_DetailFields;
    
    ::rtl::OUString     m_Command;
    ::rtl::OUString     m_DataSourceName;
    ::sal_Int32         m_CommandType;
    sal_Int32           m_RowLimit;
    ::rtl::OUString     m_Filter;
    ::rtl::OUString     m_HavingClause;
    ::rtl::OUString     m_Order;
    ::rtl::OUString     m_GroupBy;
    ::sal_Bool          m_EscapeProcessing;
    ::sal_Bool          m_ApplyFilter;
};

} // namespace dbaccess

#endif // DBA_DATABASEDATAPROVIDER_HXX_INCLUDED
