/*************************************************************************
 *
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
// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"

#include "DatabaseDataProvider.hxx"
#include "dbastrings.hrc"
#include "cppuhelper/implbase1.hxx"
#include <comphelper/types.hxx>
#include <connectivity/FValue.hxx>
#include <connectivity/dbtools.hxx>
#include <rtl/ustrbuf.hxx>
#include <rtl/math.hxx>

#include <com/sun/star/task/XInteractionHandler.hpp>
#include <com/sun/star/sdb/XCompletedExecution.hpp>
#include <com/sun/star/sdb/CommandType.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/sdbc/XResultSet.hpp>
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#include <com/sun/star/sdbc/XResultSetMetaData.hpp>
#include <com/sun/star/sdbc/XColumnLocate.hpp>
#include <com/sun/star/beans/NamedValue.hpp>
#include <com/sun/star/chart/ChartDataRowSource.hpp>
#include <com/sun/star/chart/XChartDataArray.hpp>

#include <vector>
#include <list>

namespace dbaccess
{
using namespace ::com::sun::star;
using ::com::sun::star::sdbc::SQLException;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::RuntimeException;
// -----------------------------------------------------------------------------
DatabaseDataProvider::DatabaseDataProvider(uno::Reference< uno::XComponentContext > const & context) :
    TDatabaseDataProvider(m_aMutex),
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >(
        context, static_cast< Implements >(
            IMPLEMENTS_PROPERTY_SET), uno::Sequence< ::rtl::OUString >()),
    m_aParameterManager( m_aMutex, uno::Reference< lang::XMultiServiceFactory >(context->getServiceManager(),uno::UNO_QUERY) ),
    m_aFilterManager( uno::Reference< lang::XMultiServiceFactory >(context->getServiceManager(),uno::UNO_QUERY) ),
    m_xContext(context),
    m_CommandType(sdb::CommandType::COMMAND), // #i94114
    m_RowLimit(0),
    m_EscapeProcessing(sal_True),
    m_ApplyFilter(sal_True)
{
    m_xInternal.set( m_xContext->getServiceManager()->createInstanceWithContext(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.chart.InternalDataProvider")),m_xContext ), uno::UNO_QUERY );
    m_xRangeConversion.set(m_xInternal,uno::UNO_QUERY);
    m_xComplexDescriptionAccess.set(m_xInternal,uno::UNO_QUERY);

    osl_incrementInterlockedCount( &m_refCount );
    {
        m_xRowSet.set( m_xContext->getServiceManager()->createInstanceWithContext(SERVICE_SDB_ROWSET,m_xContext ), uno::UNO_QUERY );
        m_xAggregate.set(m_xRowSet,uno::UNO_QUERY);
        m_xAggregateSet.set(m_xRowSet,uno::UNO_QUERY);
        uno::Reference<beans::XPropertySet> xProp(static_cast< ::cppu::OWeakObject* >( this ),uno::UNO_QUERY);
        m_aFilterManager.initialize( m_xAggregateSet );
        m_aParameterManager.initialize( xProp, m_xAggregate );
        m_xAggregateSet->setPropertyValue(PROPERTY_COMMAND_TYPE,uno::makeAny(m_CommandType));
        m_xAggregateSet->setPropertyValue(PROPERTY_ESCAPE_PROCESSING,uno::makeAny(m_EscapeProcessing));
    }
    osl_decrementInterlockedCount( &m_refCount );
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::disposing()
{
    lang::EventObject aEvt(static_cast<XWeak*>(this));
    m_aParameterManager.disposing( aEvt );

    m_aParameterManager.dispose();   // (to free any references it may have to me)
    m_aFilterManager.dispose();      // (dito)

    m_xParent.clear();
    m_xAggregateSet.clear();
    m_xAggregate.clear();
    m_xRangeConversion.clear();
    ::comphelper::disposeComponent(m_xRowSet);
    ::comphelper::disposeComponent(m_xInternal);
    m_xActiveConnection.clear();
}
// -----------------------------------------------------------------------------
uno::Any DatabaseDataProvider::queryInterface(uno::Type const & type) throw (uno::RuntimeException)
{
    return TDatabaseDataProvider::queryInterface(type);
}
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
rtl::OUString DatabaseDataProvider::getImplementationName_Static(  ) throw(uno::RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.comp.chart2.data.DatabaseDataProvider");
}
// -----------------------------------------------------------------------------
// -------------------------------------------------------------------------
// XServiceInfo
::rtl::OUString SAL_CALL DatabaseDataProvider::getImplementationName(  ) throw(uno::RuntimeException)
{
    return getImplementationName_Static();
}
// -----------------------------------------------------------------------------
// -------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::supportsService( const ::rtl::OUString& _rServiceName ) throw(uno::RuntimeException)
{
    return ::comphelper::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
}
// -----------------------------------------------------------------------------
//------------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > DatabaseDataProvider::getSupportedServiceNames_Static(  ) throw (uno::RuntimeException)
{
    uno::Sequence< rtl::OUString > aSNS( 1 );
    aSNS[0] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.chart2.data.DatabaseDataProvider"));
    return aSNS;
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL DatabaseDataProvider::getSupportedServiceNames(  ) throw(uno::RuntimeException)
{
    return getSupportedServiceNames_Static();
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > DatabaseDataProvider::Create(uno::Reference< uno::XComponentContext > const & context)
{
    return *(new DatabaseDataProvider(context)) ;
}
// -----------------------------------------------------------------------------
// lang::XInitialization:
void SAL_CALL DatabaseDataProvider::initialize(const uno::Sequence< uno::Any > & aArguments) throw (uno::RuntimeException, uno::Exception)
{
    osl::MutexGuard g(m_aMutex);
    const uno::Any* pIter   = aArguments.getConstArray();
    const uno::Any* pEnd    = pIter + aArguments.getLength();
    for(;pIter != pEnd;++pIter)
    {
        if ( !m_xActiveConnection.is() )
            (*pIter) >>= m_xActiveConnection;
        else if ( !m_xHandler.is() )
            (*pIter) >>= m_xHandler;
    }
    m_xAggregateSet->setPropertyValue( PROPERTY_ACTIVE_CONNECTION, uno::makeAny( m_xActiveConnection ) );
}
// -----------------------------------------------------------------------------

// chart2::data::XDataProvider:
::sal_Bool SAL_CALL DatabaseDataProvider::createDataSourcePossible(const uno::Sequence< beans::PropertyValue > & _aArguments) throw (uno::RuntimeException)
{
    //::osl::ResettableMutexGuard aClearForNotifies(m_aMutex);
    const beans::PropertyValue* pArgIter = _aArguments.getConstArray();
    const beans::PropertyValue* pArgEnd  = pArgIter + _aArguments.getLength();
    for(;pArgIter != pArgEnd;++pArgIter)
    {
        if ( pArgIter->Name.equalsAscii("DataRowSource") )
        {
            ::com::sun::star::chart::ChartDataRowSource eRowSource = ::com::sun::star::chart::ChartDataRowSource_COLUMNS;
            pArgIter->Value >>= eRowSource;
            if ( eRowSource != ::com::sun::star::chart::ChartDataRowSource_COLUMNS )
                return sal_False;
        } // if ( pArgIter->Name.equalsAscii("DataRowSource") )
        else if ( pArgIter->Name.equalsAscii("CellRangeRepresentation") )
        {
            ::rtl::OUString sRange;
            pArgIter->Value >>= sRange;
            if ( !sRange.equalsAscii("all") )
                return sal_False;
        }
        else if ( pArgIter->Name.equalsAscii("FirstCellAsLabel") )
        {
            sal_Bool bFirstCellAsLabel = sal_True;
            pArgIter->Value >>= bFirstCellAsLabel;
            if ( !bFirstCellAsLabel )
                return sal_False;
        }
    }
    return sal_True;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
uno::Reference< chart2::data::XDataSource > SAL_CALL DatabaseDataProvider::createDataSource(const uno::Sequence< beans::PropertyValue > & _aArguments) throw (uno::RuntimeException, lang::IllegalArgumentException)
{
    osl::ResettableMutexGuard aClearForNotifies(m_aMutex);
    if ( createDataSourcePossible(_aArguments) )
    {
        sal_Bool bHasCategories = sal_True;
        uno::Sequence< uno::Sequence< ::rtl::OUString > > aColumnNames;
        const beans::PropertyValue* pArgIter = _aArguments.getConstArray();
        const beans::PropertyValue* pArgEnd  = pArgIter + _aArguments.getLength();
        for(;pArgIter != pArgEnd;++pArgIter)
        {
            if ( pArgIter->Name.equalsAscii("HasCategories") )
            {
                pArgIter->Value >>= bHasCategories;
                
            }
            else if ( pArgIter->Name.equalsAscii("ComplexColumnDescriptions") )
            {
                pArgIter->Value >>= aColumnNames;
            }
        }
        bool bRet = false;
        if ( m_Command.getLength() != 0 && m_xActiveConnection.is() )
        {
            try
            {
                impl_fillRowSet_throw();
                impl_executeRowSet_throw(aClearForNotifies);
                impl_fillInternalDataProvider_throw(bHasCategories,aColumnNames);
                bRet = true;
            }
            catch(const uno::Exception& /*e*/)
            {
            }
        }
        if ( !bRet ) // no command set or an error occured, use Internal data handler
        {
            uno::Reference< lang::XInitialization> xIni(m_xInternal,uno::UNO_QUERY);
            if ( xIni.is() )
            {
                uno::Sequence< uno::Any > aArgs(1);
                beans::NamedValue aParam(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CreateDefaultData")),uno::makeAny(sal_True));
                aArgs[0] <<= aParam;
                xIni->initialize(aArgs);
            }
        }

    }
    return m_xInternal->createDataSource(_aArguments);
}
// -----------------------------------------------------------------------------

uno::Sequence< beans::PropertyValue > SAL_CALL DatabaseDataProvider::detectArguments(const uno::Reference< chart2::data::XDataSource > & _xDataSource) throw (uno::RuntimeException)
{
    uno::Sequence< beans::PropertyValue > aArguments( 4 );
    aArguments[0] = beans::PropertyValue(
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("CellRangeRepresentation")), -1, uno::Any(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("all")) ),
        beans::PropertyState_DIRECT_VALUE );
    aArguments[1] = beans::PropertyValue(
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DataRowSource")), -1, uno::makeAny( chart::ChartDataRowSource_COLUMNS ),
        beans::PropertyState_DIRECT_VALUE );
    // internal data always contains labels and categories
    aArguments[2] = beans::PropertyValue(
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FirstCellAsLabel")), -1, uno::makeAny( true ), beans::PropertyState_DIRECT_VALUE );
    sal_Bool bHasCategories = sal_False;
    if( _xDataSource.is())
    {
      uno::Sequence< uno::Reference< chart2::data::XLabeledDataSequence > > aSequences(_xDataSource->getDataSequences());
      const sal_Int32 nCount( aSequences.getLength());
      for( sal_Int32 nIdx=0; nIdx<nCount; ++nIdx )
      {
          if( aSequences[nIdx].is() )
          {
              uno::Reference< beans::XPropertySet > xSeqProp( aSequences[nIdx]->getValues(), uno::UNO_QUERY );
              ::rtl::OUString aRole;
              if( xSeqProp.is() &&
                  (xSeqProp->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Role"))) >>= aRole) &&
                  aRole.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM("categories")) )
              {
                  bHasCategories = sal_True;
                  break;
              }
          }
      }
    }

    aArguments[3] = beans::PropertyValue(
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HasCategories")), -1, uno::makeAny( bHasCategories ), beans::PropertyState_DIRECT_VALUE );
    return aArguments;
}
// -----------------------------------------------------------------------------

::sal_Bool SAL_CALL DatabaseDataProvider::createDataSequenceByRangeRepresentationPossible(const ::rtl::OUString & /*aRangeRepresentation*/) throw (uno::RuntimeException)
{
    return sal_True;
}
// -----------------------------------------------------------------------------
uno::Any DatabaseDataProvider::impl_getNumberFormatKey_nothrow(const ::rtl::OUString & _sRangeRepresentation) const
{
    ::std::map< ::rtl::OUString,com::sun::star::uno::Any>::const_iterator aFind = m_aNumberFormats.find(_sRangeRepresentation);
    if ( aFind != m_aNumberFormats.end() )
        return aFind->second;
    return uno::makeAny(sal_Int32(0));
}
// -----------------------------------------------------------------------------
uno::Reference< chart2::data::XDataSequence > SAL_CALL DatabaseDataProvider::createDataSequenceByRangeRepresentation(const ::rtl::OUString & _sRangeRepresentation) throw (uno::RuntimeException, lang::IllegalArgumentException)
{
    osl::MutexGuard g(m_aMutex);
    uno::Reference< chart2::data::XDataSequence > xData = m_xInternal->createDataSequenceByRangeRepresentation(_sRangeRepresentation);;
    uno::Reference<beans::XPropertySet> xProp(xData,uno::UNO_QUERY);
    const static ::rtl::OUString s_sNumberFormatKey(RTL_CONSTASCII_USTRINGPARAM("NumberFormatKey"));
    if ( xProp.is() && xProp->getPropertySetInfo()->hasPropertyByName(s_sNumberFormatKey) )
    {
        xProp->setPropertyValue(s_sNumberFormatKey,impl_getNumberFormatKey_nothrow(_sRangeRepresentation));
    }
    return xData;
}

uno::Sequence< uno::Sequence< rtl::OUString > > SAL_CALL DatabaseDataProvider::getComplexRowDescriptions() throw (uno::RuntimeException)
{
    return m_xComplexDescriptionAccess->getComplexRowDescriptions();
}
void SAL_CALL DatabaseDataProvider::setComplexRowDescriptions( const uno::Sequence< uno::Sequence< ::rtl::OUString > >& aRowDescriptions ) throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->setComplexRowDescriptions(aRowDescriptions);
}
uno::Sequence< uno::Sequence< rtl::OUString > > SAL_CALL DatabaseDataProvider::getComplexColumnDescriptions() throw (uno::RuntimeException)
{
    return m_xComplexDescriptionAccess->getComplexColumnDescriptions();
}
void SAL_CALL DatabaseDataProvider::setComplexColumnDescriptions( const uno::Sequence< uno::Sequence< rtl::OUString > >& aColumnDescriptions ) throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->setComplexColumnDescriptions(aColumnDescriptions);
}
// ____ XChartDataArray ____
uno::Sequence< uno::Sequence< double > > SAL_CALL DatabaseDataProvider::getData()    throw (uno::RuntimeException)
{
    return m_xComplexDescriptionAccess->getData();
}

void SAL_CALL DatabaseDataProvider::setData( const uno::Sequence< uno::Sequence< double > >& rDataInRows )    throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->setData(rDataInRows);
}

void SAL_CALL DatabaseDataProvider::setRowDescriptions( const uno::Sequence< rtl::OUString >& aRowDescriptions )    throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->setRowDescriptions(aRowDescriptions);
}

void SAL_CALL DatabaseDataProvider::setColumnDescriptions( const uno::Sequence< rtl::OUString >& aColumnDescriptions )    throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->setColumnDescriptions(aColumnDescriptions);
}

uno::Sequence< rtl::OUString > SAL_CALL DatabaseDataProvider::getRowDescriptions()    throw (uno::RuntimeException)
{    
    return m_xComplexDescriptionAccess->getRowDescriptions();
}

uno::Sequence< rtl::OUString > SAL_CALL DatabaseDataProvider::getColumnDescriptions()    throw (uno::RuntimeException)
{    
    return m_xComplexDescriptionAccess->getColumnDescriptions();
}

// ____ XChartData (base of XChartDataArray) ____
void SAL_CALL DatabaseDataProvider::addChartDataChangeEventListener(const uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& x)    throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->addChartDataChangeEventListener(x);
}

void SAL_CALL DatabaseDataProvider::removeChartDataChangeEventListener(const uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& x)    throw (uno::RuntimeException)
{
    m_xComplexDescriptionAccess->removeChartDataChangeEventListener(x);
}

double SAL_CALL DatabaseDataProvider::getNotANumber()    throw (uno::RuntimeException)
{
    return m_xComplexDescriptionAccess->getNotANumber();
}

::sal_Bool SAL_CALL DatabaseDataProvider::isNotANumber( double nNumber )    throw (uno::RuntimeException)
{
    return m_xComplexDescriptionAccess->isNotANumber(nNumber);
}

// -----------------------------------------------------------------------------

uno::Reference< sheet::XRangeSelection > SAL_CALL DatabaseDataProvider::getRangeSelection() throw (uno::RuntimeException)
{
    // TODO: Exchange the default return implementation for "getRangeSelection" !!!
    // Exchange the default return implementation.
    // NOTE: Default initialized polymorphic structs can cause problems because of
    // missing default initialization of primitive types of some C++ compilers or
    // different Any initialization in Java and C++ polymorphic structs.
    return uno::Reference< sheet::XRangeSelection >();
}
// -----------------------------------------------------------------------------
// chart2::data::XRangeXMLConversion:
::rtl::OUString SAL_CALL DatabaseDataProvider::convertRangeToXML(const ::rtl::OUString & _sRangeRepresentation) throw (uno::RuntimeException, lang::IllegalArgumentException)
{
    osl::MutexGuard g(m_aMutex);
    return m_xRangeConversion->convertRangeToXML(_sRangeRepresentation);
}
// -----------------------------------------------------------------------------

::rtl::OUString SAL_CALL DatabaseDataProvider::convertRangeFromXML(const ::rtl::OUString & _sXMLRange) throw (uno::RuntimeException, lang::IllegalArgumentException)
{
    osl::MutexGuard g(m_aMutex);
    return m_xRangeConversion->convertRangeFromXML(_sXMLRange);
}
// -----------------------------------------------------------------------------

// com.sun.star.beans.XPropertySet:
uno::Reference< beans::XPropertySetInfo > SAL_CALL DatabaseDataProvider::getPropertySetInfo() throw (uno::RuntimeException)
{
    return ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::getPropertySetInfo();
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setPropertyValue(const ::rtl::OUString & aPropertyName, const uno::Any & aValue) throw (uno::RuntimeException, beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException)
{
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::setPropertyValue(aPropertyName, aValue);
}
// -----------------------------------------------------------------------------

uno::Any SAL_CALL DatabaseDataProvider::getPropertyValue(const ::rtl::OUString & aPropertyName) throw (uno::RuntimeException, beans::UnknownPropertyException, lang::WrappedTargetException)
{
    return ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::getPropertyValue(aPropertyName);
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::addPropertyChangeListener(const ::rtl::OUString & aPropertyName, const uno::Reference< beans::XPropertyChangeListener > & xListener) throw (uno::RuntimeException, beans::UnknownPropertyException, lang::WrappedTargetException)
{
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::addPropertyChangeListener(aPropertyName, xListener);
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::removePropertyChangeListener(const ::rtl::OUString & aPropertyName, const uno::Reference< beans::XPropertyChangeListener > & xListener) throw (uno::RuntimeException, beans::UnknownPropertyException, lang::WrappedTargetException)
{
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::removePropertyChangeListener(aPropertyName, xListener);
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::addVetoableChangeListener(const ::rtl::OUString & aPropertyName, const uno::Reference< beans::XVetoableChangeListener > & xListener) throw (uno::RuntimeException, beans::UnknownPropertyException, lang::WrappedTargetException)
{
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::addVetoableChangeListener(aPropertyName, xListener);
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::removeVetoableChangeListener(const ::rtl::OUString & aPropertyName, const uno::Reference< beans::XVetoableChangeListener > & xListener) throw (uno::RuntimeException, beans::UnknownPropertyException, lang::WrappedTargetException)
{
    ::cppu::PropertySetMixin< chart2::data::XDatabaseDataProvider >::removeVetoableChangeListener(aPropertyName, xListener);
}
// -----------------------------------------------------------------------------

// chart2::data::XDatabaseDataProvider:
uno::Sequence< ::rtl::OUString > SAL_CALL DatabaseDataProvider::getMasterFields() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_MasterFields;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setMasterFields(const uno::Sequence< ::rtl::OUString > & the_value) throw (uno::RuntimeException)
{
    impl_invalidateParameter_nothrow();
    set(rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("MasterFields")),the_value,m_MasterFields);
}
// -----------------------------------------------------------------------------

uno::Sequence< ::rtl::OUString > SAL_CALL DatabaseDataProvider::getDetailFields() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_DetailFields;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setDetailFields(const uno::Sequence< ::rtl::OUString > & the_value) throw (uno::RuntimeException)
{
    set(rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DetailFields")),the_value,m_DetailFields);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL DatabaseDataProvider::getCommand() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_Command;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setCommand(const ::rtl::OUString & the_value) throw (uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        impl_invalidateParameter_nothrow();
        m_xAggregateSet->setPropertyValue( PROPERTY_COMMAND,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_COMMAND,the_value,m_Command);
}
// -----------------------------------------------------------------------------

::sal_Int32 SAL_CALL DatabaseDataProvider::getCommandType() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_CommandType;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setCommandType(::sal_Int32 the_value) throw (uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_xAggregateSet->setPropertyValue( PROPERTY_COMMAND_TYPE,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_COMMAND_TYPE,the_value,m_CommandType);
}
// -----------------------------------------------------------------------------

::rtl::OUString SAL_CALL DatabaseDataProvider::getFilter() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_aFilterManager.getFilterComponent( dbtools::FilterManager::fcPublicFilter );
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setFilter(const ::rtl::OUString & the_value) throw (uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_aFilterManager.setFilterComponent( dbtools::FilterManager::fcPublicFilter, the_value );
    }
    set(PROPERTY_FILTER,the_value,m_Filter);
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL DatabaseDataProvider::getApplyFilter() throw (RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_ApplyFilter;
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setApplyFilter( ::sal_Bool the_value ) throw (RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_xAggregateSet->setPropertyValue( PROPERTY_APPLYFILTER,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_APPLYFILTER,the_value,m_ApplyFilter);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL DatabaseDataProvider::getHavingClause() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_HavingClause;
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setHavingClause( const ::rtl::OUString& the_value ) throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_xAggregateSet->setPropertyValue( PROPERTY_HAVING_CLAUSE,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_HAVING_CLAUSE,the_value,m_HavingClause);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL DatabaseDataProvider::getGroupBy() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_GroupBy;
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setGroupBy( const ::rtl::OUString& the_value ) throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_xAggregateSet->setPropertyValue( PROPERTY_GROUP_BY,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_GROUP_BY,the_value,m_GroupBy);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL DatabaseDataProvider::getOrder() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_Order;
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setOrder( const ::rtl::OUString& the_value ) throw (uno::RuntimeException)
{
    {
        osl::MutexGuard g(m_aMutex);
        m_xAggregateSet->setPropertyValue( PROPERTY_ORDER,   uno::makeAny( the_value ) );
    }
    set(PROPERTY_ORDER,the_value,m_Order);
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL DatabaseDataProvider::getEscapeProcessing() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_EscapeProcessing;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setEscapeProcessing(::sal_Bool the_value) throw (uno::RuntimeException)
{
    set(PROPERTY_ESCAPE_PROCESSING,the_value,m_EscapeProcessing);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL DatabaseDataProvider::getRowLimit() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_RowLimit;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setRowLimit(::sal_Int32 the_value) throw (uno::RuntimeException)
{
    set(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("RowLimit")),the_value,m_RowLimit);
}
// -----------------------------------------------------------------------------
uno::Reference< sdbc::XConnection > SAL_CALL DatabaseDataProvider::getActiveConnection() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_xActiveConnection;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setActiveConnection(const uno::Reference< sdbc::XConnection > & the_value) throw (uno::RuntimeException, lang::IllegalArgumentException)
{
    if ( !the_value.is() )
        throw lang::IllegalArgumentException();
    set(PROPERTY_ACTIVE_CONNECTION,the_value,m_xActiveConnection);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL DatabaseDataProvider::getDataSourceName() throw (uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    return m_DataSourceName;
}
// -----------------------------------------------------------------------------

void SAL_CALL DatabaseDataProvider::setDataSourceName(const ::rtl::OUString& the_value) throw (uno::RuntimeException)
{
    set(PROPERTY_DATASOURCENAME,the_value,m_DataSourceName);
}
// -----------------------------------------------------------------------------
void DatabaseDataProvider::impl_executeRowSet_throw(::osl::ResettableMutexGuard& _rClearForNotifies)
{
    if ( impl_fillParameters_nothrow(_rClearForNotifies) )
        m_xRowSet->execute();
}
// -----------------------------------------------------------------------------
void DatabaseDataProvider::impl_fillInternalDataProvider_throw(sal_Bool _bHasCategories,const uno::Sequence< uno::Sequence< ::rtl::OUString > >& i_aColumnNames)
{
    // clear the data before fill the new one
    uno::Reference< chart::XChartDataArray> xChartData(m_xInternal,uno::UNO_QUERY);
    if ( xChartData.is() )
    {
        xChartData->setData(uno::Sequence< uno::Sequence<double> >());
        xChartData->setColumnDescriptions(uno::Sequence< ::rtl::OUString >());
        if ( m_xInternal->hasDataByRangeRepresentation(::rtl::OUString::valueOf(sal_Int32(0))) )
            m_xInternal->deleteSequence(0);
    }

    uno::Reference< sdbcx::XColumnsSupplier> xColSup(m_xRowSet,uno::UNO_QUERY_THROW);
    uno::Reference< container::XNameAccess > xColumns = xColSup->getColumns();
    uno::Sequence< ::rtl::OUString > aColumns;
    if ( i_aColumnNames.getLength() )
    {
        aColumns.realloc(1);
        aColumns[0] = xColumns->getElementNames()[0];
        for(sal_Int32 i = 0 ; i < i_aColumnNames.getLength();++i)
        {
            if ( i_aColumnNames[i].getLength() )
            {
                sal_Int32 nCount = aColumns.getLength();
                aColumns.realloc(nCount+1);
                aColumns[nCount] = i_aColumnNames[i][0];
            }
        }
    }
    else
    {
        aColumns = xColumns->getElementNames();
    }
    // fill the data
    uno::Reference< sdbc::XResultSet> xRes(m_xRowSet,uno::UNO_QUERY_THROW);
    uno::Reference< sdbc::XRow> xRow(m_xRowSet,uno::UNO_QUERY_THROW);
    uno::Reference< sdbc::XResultSetMetaData> xResultSetMetaData = uno::Reference< sdbc::XResultSetMetaDataSupplier>(m_xRowSet,uno::UNO_QUERY)->getMetaData();
    uno::Reference< sdbc::XColumnLocate> xColumnLocate(m_xRowSet,uno::UNO_QUERY_THROW);

    ::std::vector<sal_Int32> aColumnTypes;
    uno::Sequence< uno::Any > aLabelArgs(1);
    const sal_Int32 nCount = aColumns.getLength();
    if ( nCount )
        aColumnTypes.push_back(xResultSetMetaData->getColumnType(1));

    ::std::vector< sal_Int32 > aColumnPositions;
    const ::rtl::OUString* pIter = aColumns.getConstArray();
    const ::rtl::OUString* pEnd = pIter + aColumns.getLength();
    for(sal_Int32 k = 0;pIter != pEnd;++pIter,++k)
    {
        aColumnPositions.push_back(xColumnLocate->findColumn(*pIter));
        uno::Reference< beans::XPropertySet> xColumn(xColumns->getByName(*pIter),uno::UNO_QUERY);
        sal_Int32 nType = sdbc::DataType::VARCHAR;
        if ( xColumn.is() )
        {
            m_aNumberFormats.insert( ::std::map< ::rtl::OUString,uno::Any>::value_type(::rtl::OUString::valueOf(k),xColumn->getPropertyValue(PROPERTY_NUMBERFORMAT)));
            xColumn->getPropertyValue(PROPERTY_TYPE) >>= nType;
        }
        aColumnTypes.push_back(nType);
    }

    ::std::vector< ::rtl::OUString > aRowLabels;
    ::std::vector< ::std::vector< double > > aDataValues;
    sal_Int32 nRowCount = 0;
    ::connectivity::ORowSetValue aValue;
    while( xRes->next() && (!m_RowLimit || nRowCount < m_RowLimit) )
    {
        ++nRowCount;
        
        aValue.fill(1,aColumnTypes[0],xRow);
        aRowLabels.push_back(aValue.getString());
        ::std::vector< double > aRow;
        ::std::vector< sal_Int32 >::iterator aColumnPosIter = aColumnPositions.begin();
        ::std::vector< sal_Int32 >::iterator aColumnPosEnd = aColumnPositions.end();
        sal_Int32 i = 0;
        if ( _bHasCategories )
        {
            ++aColumnPosIter;
            ++i;
        }
        for (; aColumnPosIter != aColumnPosEnd; ++aColumnPosIter,++i)
        {
            aValue.fill(*aColumnPosIter,aColumnTypes[i],xRow);
            if ( aValue.isNull() )
            {
                double nValue;
                ::rtl::math::setNan( &nValue );
                aRow.push_back(nValue);
            }
            else
                aRow.push_back(aValue.getDouble());
        }
        aDataValues.push_back(aRow);
    } // while( xRes->next() && (!m_RowLimit || nRowCount < m_RowLimit) )

    // insert default data when no rows exist
    if ( !nRowCount )
    {
        nRowCount = 3;
        const double fDefaultData[ ] =
            { 9.10, 3.20, 4.54,
              2.40, 8.80, 9.65,
              3.10, 1.50, 3.70,
              4.30, 9.02, 6.20 };
        for(sal_Int32 h = 0,k = 0; h < nRowCount; ++h,++k )
        {
            aRowLabels.push_back(::rtl::OUString::valueOf(h+1));
            ::std::vector< double > aRow;
            const sal_Int32 nSize = sizeof(fDefaultData)/sizeof(fDefaultData[0]);
            for (sal_Int32 j = 0; j < (nCount-1); ++j,++k)
            {            
                if ( k >= nSize )
                    k = 0;
                aRow.push_back(fDefaultData[k]);
            } // for (sal_Int32 j = 0,k = 0; j < (nCount-1); ++j,++k)
            aDataValues.push_back(aRow);
        }
    } // if ( !nRowCount )
        
    uno::Reference< chart::XChartDataArray> xData(m_xInternal,uno::UNO_QUERY);
    xData->setRowDescriptions(uno::Sequence< ::rtl::OUString >(&(*aRowLabels.begin()),aRowLabels.size()));
    xData->setColumnDescriptions(uno::Sequence< ::rtl::OUString >(aColumns.getArray()+ (_bHasCategories ? 1 : 0),aColumns.getLength() - (_bHasCategories ? 1 : 0) ));
    uno::Sequence< uno::Sequence< double > > aData(aDataValues.size());
    uno::Sequence< double >* pDataIter  = aData.getArray();
    uno::Sequence< double >* pDataEnd   = pDataIter + aData.getLength();
    for(sal_Int32 i= 0;pDataIter != pDataEnd; ++pDataIter,++i )
    {
        if ( !aDataValues[i].empty() )
            *pDataIter = uno::Sequence< double >(&(*(aDataValues[i]).begin()),(aDataValues[i]).size());
    }
    xData->setData(aData);
}
// -----------------------------------------------------------------------------
void DatabaseDataProvider::impl_fillRowSet_throw()
{
    m_xAggregateSet->setPropertyValue( PROPERTY_FILTER,   uno::makeAny( getFilter() ) );
    uno::Reference< sdbc::XParameters> xParam(m_xRowSet,uno::UNO_QUERY_THROW);
    xParam->clearParameters( );
}
// -----------------------------------------------------------------------------
bool DatabaseDataProvider::impl_fillParameters_nothrow( ::osl::ResettableMutexGuard& _rClearForNotifies)
{
    // do we have to fill the parameters again?
    if ( !m_aParameterManager.isUpToDate() )
        m_aParameterManager.updateParameterInfo( m_aFilterManager );

    if ( m_aParameterManager.isUpToDate() )
        return m_aParameterManager.fillParameterValues( m_xHandler, _rClearForNotifies );

    return true;
}
// com::sun::star::sdbc::XParameters
//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setNull(sal_Int32 parameterIndex, sal_Int32 sqlType) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setNull(parameterIndex, sqlType);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setObjectNull(sal_Int32 parameterIndex, sal_Int32 sqlType, const ::rtl::OUString& typeName) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setObjectNull(parameterIndex, sqlType, typeName);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setBoolean(sal_Int32 parameterIndex, sal_Bool x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setBoolean(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setByte(sal_Int32 parameterIndex, sal_Int8 x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setByte(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setShort(sal_Int32 parameterIndex, sal_Int16 x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setShort(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setInt(sal_Int32 parameterIndex, sal_Int32 x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setInt(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setLong(sal_Int32 parameterIndex, sal_Int64 x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setLong(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setFloat(sal_Int32 parameterIndex, float x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setFloat(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setDouble(sal_Int32 parameterIndex, double x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setDouble(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setString(sal_Int32 parameterIndex, const ::rtl::OUString& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setString(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setBytes(sal_Int32 parameterIndex, const uno::Sequence< sal_Int8 >& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setBytes(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setDate(sal_Int32 parameterIndex, const util::Date& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setDate(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setTime(sal_Int32 parameterIndex, const util::Time& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setTime(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setTimestamp(sal_Int32 parameterIndex, const util::DateTime& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setTimestamp(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setBinaryStream(sal_Int32 parameterIndex, const uno::Reference<io::XInputStream>& x, sal_Int32 length) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setBinaryStream(parameterIndex, x, length);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setCharacterStream(sal_Int32 parameterIndex, const uno::Reference<io::XInputStream>& x, sal_Int32 length) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setCharacterStream(parameterIndex, x, length);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setObjectWithInfo(sal_Int32 parameterIndex, const uno::Any& x, sal_Int32 targetSqlType, sal_Int32 scale) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setObjectWithInfo(parameterIndex, x, targetSqlType, scale);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setObject(sal_Int32 parameterIndex, const uno::Any& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setObject(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setRef(sal_Int32 parameterIndex, const uno::Reference<sdbc::XRef>& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setRef(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setBlob(sal_Int32 parameterIndex, const uno::Reference<sdbc::XBlob>& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setBlob(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setClob(sal_Int32 parameterIndex, const uno::Reference<sdbc::XClob>& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setClob(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setArray(sal_Int32 parameterIndex, const Reference<sdbc::XArray>& x) throw( SQLException, RuntimeException )
{
    m_aParameterManager.setArray(parameterIndex, x);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::clearParameters() throw( SQLException, RuntimeException )
{
    m_aParameterManager.clearParameters();
}
//==============================================================================
// com::sun::star::sdbc::XRowSet
//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::execute() throw( SQLException, RuntimeException )
{
    uno::Sequence< beans::PropertyValue > aEmpty;
    createDataSource(aEmpty);
}
//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::addRowSetListener(const uno::Reference<sdbc::XRowSetListener>& _rListener) throw( RuntimeException )
{
    if (m_xRowSet.is())
        m_xRowSet->addRowSetListener(_rListener);
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::removeRowSetListener(const uno::Reference<sdbc::XRowSetListener>& _rListener) throw( RuntimeException )
{
    if (m_xRowSet.is())
        m_xRowSet->removeRowSetListener(_rListener);
}
//==============================================================================
// com::sun::star::sdbc::XResultSet
//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::next() throw( SQLException, RuntimeException )
{
    return m_xRowSet->next();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::isBeforeFirst() throw( SQLException, RuntimeException )
{
    return m_xRowSet->isBeforeFirst();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::isAfterLast() throw( SQLException, RuntimeException )
{
    return m_xRowSet->isAfterLast();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::isFirst() throw( SQLException, RuntimeException )
{
    return m_xRowSet->isFirst();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::isLast() throw( SQLException, RuntimeException )
{
    return m_xRowSet->isLast();
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::beforeFirst() throw( SQLException, RuntimeException )
{
    m_xRowSet->beforeFirst();
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::afterLast() throw( SQLException, RuntimeException )
{
    m_xRowSet->afterLast();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::first() throw( SQLException, RuntimeException )
{
    return m_xRowSet->first();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::last() throw( SQLException, RuntimeException )
{
    return m_xRowSet->last();
}

//------------------------------------------------------------------------------
sal_Int32 SAL_CALL DatabaseDataProvider::getRow() throw( SQLException, RuntimeException )
{
    return m_xRowSet->getRow();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::absolute(sal_Int32 row) throw( SQLException, RuntimeException )
{
    return m_xRowSet->absolute(row);
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::relative(sal_Int32 rows) throw( SQLException, RuntimeException )
{
    return m_xRowSet->relative(rows);
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::previous() throw( SQLException, RuntimeException )
{
    return m_xRowSet->previous();
}

//------------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::refreshRow() throw( SQLException, RuntimeException )
{
    m_xRowSet->refreshRow();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::rowUpdated() throw( SQLException, RuntimeException )
{
    return m_xRowSet->rowUpdated();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::rowInserted() throw( SQLException, RuntimeException )
{
    return m_xRowSet->rowInserted();
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL DatabaseDataProvider::rowDeleted() throw( SQLException, RuntimeException )
{
    return m_xRowSet->rowDeleted();
}

//------------------------------------------------------------------------------
uno::Reference< uno::XInterface > SAL_CALL DatabaseDataProvider::getStatement() throw( SQLException, RuntimeException )
{
    return m_xRowSet->getStatement();
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > SAL_CALL DatabaseDataProvider::getParent(  ) throw (uno::RuntimeException)
{
    return m_xParent;
}
// -----------------------------------------------------------------------------
void SAL_CALL DatabaseDataProvider::setParent( const uno::Reference< uno::XInterface >& _xParent ) throw (lang::NoSupportException, uno::RuntimeException)
{
    osl::MutexGuard g(m_aMutex);
    m_xParent = _xParent;
}
// -----------------------------------------------------------------------------
void DatabaseDataProvider::impl_invalidateParameter_nothrow()
{
    osl::MutexGuard g(m_aMutex);
    m_aParameterManager.clearAllParameterInformation();
}
// -----------------------------------------------------------------------------
} // namespace dbaccess
