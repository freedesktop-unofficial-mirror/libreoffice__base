/*************************************************************************
 *
 *  $RCSfile: RowSet.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hr $ $Date: 2000-09-19 00:15:38 $
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
#ifndef DBACCESS_CORE_API_ROWSET_HXX
#include "RowSet.hxx"
#endif
#ifndef _DBASHARED_STRINGCONSTANTS_HRC_
#include "stringconstants.hrc"
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.h>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _UTL_SEQUENCE_HXX_
#include <unotools/sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_ROWSETVETOEXCEPTION_HPP_
#include <com/sun/star/sdb/RowSetVetoException.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_FETCHDIRECTION_HPP_
#include <com/sun/star/sdbc/FetchDirection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_RESULTSETCONCURRENCY_HPP_
#include <com/sun/star/sdbc/ResultSetConcurrency.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_ROWCHANGEACTION_HPP_
#include <com/sun/star/sdb/RowChangeAction.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDRIVERACCESS_HPP_
#include <com/sun/star/sdbc/XDriverAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADEFINITIONSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XDataDefinitionSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _UTL_UNO3_DB_TOOLS_HXX_
#include <unotools/dbtools.hxx>
#endif
#ifndef _CPPUHELPER_EXTRACT_HXX_
#include <cppuhelper/extract.hxx>
#endif
#ifndef DBACCESS_CORE_API_ROWSETCACHE_HXX
#include "RowSetCache.hxx"
#endif
#ifndef _DBA_CORE_REGISTRYHELPER_HXX_
#include "registryhelper.hxx"
#endif
#ifndef _DBA_REGISTRATION_HELPER_HXX_
#include "registrationhelper.hxx"
#endif
#ifndef _DBA_CORE_TABLECONTAINER_HXX_
#include "tablecontainer.hxx"
#endif
#ifdef DEBUG
#ifndef _COM_SUN_STAR_SDBC_XDRIVERMANAGER_HPP_
#include <com/sun/star/sdbc/XDriverManager.hpp>
#endif
#endif 
#ifndef _DBACORE_DATACOLUMN_HXX_
#include "CRowSetDataColumn.hxx"
#endif
#ifndef DBACCESS_CORE_API_CROWSETCOLUMN_HXX
#include "CRowSetColumn.hxx"
#endif

using namespace dbaccess;
using namespace connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::cppu;
using namespace ::osl;

//--------------------------------------------------------------------------
extern "C" void SAL_CALL createRegistryInfo_ORowSet()
{
    static OMultiInstanceAutoRegistration< ORowSet > aAutoRegistration;
}

//--------------------------------------------------------------------------
Reference< XInterface > ORowSet_CreateInstance(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return *(new ORowSet(_rxFactory));
}
//--------------------------------------------------------------------------
ORowSet::ORowSet(const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xFac) 
    : ORowSet_BASE1(m_aMutex)
    , ORowSetBase(ORowSet_BASE1::rBHelper)
    , m_xServiceManager(_xFac)
    ,m_pParseTree(NULL)
    ,m_nFetchDirection(FetchDirection::FORWARD)
    ,m_nFetchSize(1)
    ,m_nResultSetConcurrency(ResultSetConcurrency::UPDATABLE)
    ,m_nResultSetType(ResultSetType::SCROLL_INSENSITIVE)
    ,m_nCommandType(CommandType::COMMAND)
    ,m_nMaxFieldSize(0)
    ,m_nTransactionIsolation(0)
    ,m_nPrivileges(0)
    ,m_nAsyncUpdateRowCount(0)
    ,m_nMaxRows(0)
    ,m_nQueryTimeOut(0)
    ,m_bUseEscapeProcessing(sal_True)
    ,m_bApplyFilter(sal_False)
    ,m_bIgnoreResult(sal_False)
    ,m_bInserted(sal_False)
    ,m_bDeleted(sal_False)
    ,m_bUpdated(sal_False)
    ,m_bCreateStatement(sal_True)
    ,m_bCanceled(sal_False)
    ,m_bRowObsolete(sal_False)
    ,m_bModified(sal_False)
    ,m_bOwnsResultRow(sal_False)
    ,m_bRebuildConnOnExecute(sal_False)
    ,m_bNew(sal_False)
    ,m_bIsBookmarable(sal_True)
{

    m_pMySelf = this;
    m_aActiveConnection <<= m_xActiveConnection;

    sal_Int32 nRBT	= PropertyAttribute::READONLY	| PropertyAttribute::BOUND		| PropertyAttribute::TRANSIENT;
    sal_Int32 nRT	= PropertyAttribute::READONLY	| PropertyAttribute::TRANSIENT;
    sal_Int32 nBT	= PropertyAttribute::BOUND		| PropertyAttribute::TRANSIENT;

    // sdb.RowSet Properties
    registerMayBeVoidProperty(PROPERTY_ACTIVECONNECTION,PROPERTY_ID_ACTIVECONNECTION,	PropertyAttribute::MAYBEVOID|PropertyAttribute::TRANSIENT,	&m_aActiveConnection,	::getCppuType(reinterpret_cast< Reference< XConnection >* >(NULL)));
    registerProperty(PROPERTY_DATASOURCENAME,		PROPERTY_ID_DATASOURCENAME,			PropertyAttribute::BOUND,		&m_aDataSourceName,		::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_COMMAND,				PROPERTY_ID_COMMAND,				PropertyAttribute::BOUND,		&m_aCommand,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_COMMANDTYPE,			PROPERTY_ID_COMMANDTYPE,			PropertyAttribute::BOUND,		&m_nCommandType,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_ACTIVECOMMAND,		PROPERTY_ID_ACTIVECOMMAND,			nRBT,							&m_aCommand,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_IGNORERESULT,			PROPERTY_ID_IGNORERESULT,			PropertyAttribute::BOUND,		&m_bIgnoreResult,		::getBooleanCppuType());
    registerProperty(PROPERTY_FILTER,				PROPERTY_ID_FILTER,					PropertyAttribute::BOUND,		&m_aFilter,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_APPLYFILTER,			PROPERTY_ID_APPLYFILTER,			PropertyAttribute::BOUND,		&m_bApplyFilter,		::getBooleanCppuType());
    registerProperty(PROPERTY_ORDER,				PROPERTY_ID_ORDER,					PropertyAttribute::BOUND,		&m_aOrder,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_PRIVILEGES,			PROPERTY_ID_PRIVILEGES,				nRT,							&m_nPrivileges,			::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_ISMODIFIED,			PROPERTY_ID_ISMODIFIED,				nRBT,							&m_bModified,			::getBooleanCppuType());
    registerProperty(PROPERTY_ISNEW,				PROPERTY_ID_ISNEW,					nRBT,							&m_bNew,				::getBooleanCppuType());
    

    // sdbcx.ResultSet Properties
    registerProperty(PROPERTY_ISBOOKMARKABLE,		PROPERTY_ID_ISBOOKMARKABLE,			nRT,							&m_bIsBookmarable,		::getBooleanCppuType());

    // sdbc.ResultSet Properties
    //	registerProperty(PROPERTY_CURSORNAME,			PROPERTY_ID_CURSORNAME,				PropertyAttribute::READONLY,	&m_aCursorName,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_RESULTSETCONCURRENCY,	PROPERTY_ID_RESULTSETCONCURRENCY,	PropertyAttribute::TRANSIENT,	&m_nResultSetConcurrency,::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_RESULTSETTYPE,		PROPERTY_ID_RESULTSETTYPE,			PropertyAttribute::TRANSIENT,	&m_nResultSetType,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_FETCHDIRECTION,		PROPERTY_ID_FETCHDIRECTION,			PropertyAttribute::TRANSIENT,	&m_nFetchDirection,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_FETCHSIZE,			PROPERTY_ID_FETCHSIZE,				PropertyAttribute::TRANSIENT,	&m_nFetchSize,			::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    
    // sdbc.RowSet Properties
    registerProperty(PROPERTY_URL,					PROPERTY_ID_URL,					0,								&m_aURL,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_TRANSACTIONISOLATION,	PROPERTY_ID_TRANSACTIONISOLATION,	PropertyAttribute::TRANSIENT,	&m_nTransactionIsolation,::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerMayBeVoidProperty(PROPERTY_TYPEMAP,		PROPERTY_ID_TYPEMAP,				PropertyAttribute::MAYBEVOID|PropertyAttribute::TRANSIENT,	&m_aTypeMap,			::getCppuType(reinterpret_cast< Reference< XNameAccess >* >(NULL)));
    registerProperty(PROPERTY_USE_ESCAPE_PROCESSING,PROPERTY_ID_USE_ESCAPE_PROCESSING,	0,								&m_bUseEscapeProcessing,::getBooleanCppuType()	);
    registerProperty(PROPERTY_QUERYTIMEOUT,			PROPERTY_ID_QUERYTIMEOUT,			PropertyAttribute::TRANSIENT,	&m_nQueryTimeOut,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_MAXFIELDSIZE,			PROPERTY_ID_MAXFIELDSIZE,			PropertyAttribute::TRANSIENT,	&m_nMaxFieldSize,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_MAXROWS,				PROPERTY_ID_MAXROWS,				0,								&m_nMaxRows,			::getCppuType(reinterpret_cast< sal_Int32*>(NULL)) );
    registerProperty(PROPERTY_USER,					PROPERTY_ID_USER,					PropertyAttribute::TRANSIENT,	&m_aUser,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_PASSWORD,				PROPERTY_ID_PASSWORD,				0,								&m_aPassword,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));

    registerProperty(PROPERTY_ISINSERTONLY,			PROPERTY_ID_ISINSERTONLY,			PropertyAttribute::BOUND,		&m_bIgnoreResult,		::getBooleanCppuType());
}
// -------------------------------------------------------------------------
//	typedef ::utl::OPropertyArrayUsageHelper<ORowSet> ORowSet_Prop;

void SAL_CALL ORowSet::setFastPropertyValue_NoBroadcast(sal_Int32 nHandle,const Any& rValue) throw (Exception)
{
    OSimplePropertyContainer::setFastPropertyValue_NoBroadcast(nHandle,rValue);
    switch(nHandle)
    {
        case PROPERTY_ID_ACTIVECONNECTION:
            m_bCreateStatement = sal_True;
            m_bRebuildConnOnExecute = sal_False;
            break;
        case PROPERTY_ID_APPLYFILTER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_COMMAND:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_COMMANDTYPE:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_DATASOURCENAME:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_FETCHSIZE:
            break;
        case PROPERTY_ID_FILTER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_ORDER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_URL:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_USER:
            m_bCreateStatement = sal_True;
            break;
    };
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::getFastPropertyValue(Any& rValue,sal_Int32 nHandle) const
{
    if(m_pCache)
    {
        switch(nHandle)
        {
        case PROPERTY_ID_ISMODIFIED:
            rValue.setValue(&m_pCache->m_bModified,::getCppuBooleanType());
            break;			
        case PROPERTY_ID_ISNEW:
            rValue.setValue(&m_pCache->m_bNew,::getCppuBooleanType());
            break;
        case PROPERTY_ID_PRIVILEGES:
            rValue <<= m_pCache->m_nPrivileges;
            break;
        default:
            ORowSetBase::getFastPropertyValue(rValue,nHandle);
        };
    }	
    else
        ORowSetBase::getFastPropertyValue(rValue,nHandle);
}
// -------------------------------------------------------------------------
// com::sun::star::lang::XTypeProvider
Sequence< Type > SAL_CALL ORowSet::getTypes() throw (RuntimeException)
{
    OTypeCollection aTypes(::getCppuType( (const Reference< XPropertySet > *)0 ),
                            ::getCppuType( (const Reference< XFastPropertySet > *)0 ),
                            ::getCppuType( (const Reference< XMultiPropertySet > *)0 ),
                           ::utl::concatSequences(ORowSet_BASE1::getTypes(),ORowSetBase::getTypes()));
    return aTypes.getTypes();
}
// -------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL ORowSet::getImplementationId() throw (RuntimeException)
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
// -------------------------------------------------------------------------

// com::sun::star::uno::XInterface
Any SAL_CALL ORowSet::queryInterface( const Type & rType ) throw (RuntimeException)
{
    return ORowSet_BASE1::queryInterface( rType);
//	Any aRet(::cppu::queryInterface(rType,static_cast< XPropertySet * >( this )));
//	if (!aRet.hasValue())
//	{
//		aRet = ORowSet_BASE1::queryInterface(rType);
//		if (!aRet.hasValue())
//			aRet = ORowSet_BASE2::queryInterface(rType);
//	}
//
//	return aRet;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::acquire() throw(RuntimeException)
{
    ORowSet_BASE1::acquire();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::release() throw(RuntimeException)
{
    ORowSet_BASE1::release();
}
// -------------------------------------------------------------------------

// com::sun::star::lang::XUnoTunnel
sal_Int64 SAL_CALL ORowSet::getSomething( const Sequence< sal_Int8 >& rId ) throw(RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;

    return 0;
}
// -------------------------------------------------------------------------
// com::sun::star::uno::XAggregation
Any SAL_CALL ORowSet::queryAggregation( const Type& rType ) throw(RuntimeException)
{
    Any aRet(ORowSetBase::queryInterface(rType));
    if (!aRet.hasValue())
        aRet = ORowSet_BASE1::queryAggregation(rType);
    return aRet;
}
//------------------------------------------------------------------------------
rtl::OUString ORowSet::getImplementationName_Static(  ) throw(RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.dbaccess.ORowSet");
}
// -------------------------------------------------------------------------
// ::com::sun::star::lang::XServiceInfo
::rtl::OUString SAL_CALL ORowSet::getImplementationName(  ) throw(RuntimeException)
{
    return getImplementationName_Static();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL ORowSet::supportsService( const ::rtl::OUString& _rServiceName ) throw(RuntimeException)
{
    return ::utl::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
}
//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > ORowSet::getSupportedServiceNames_Static(  ) throw (RuntimeException)
{
    Sequence< rtl::OUString > aSNS( 5 );
    aSNS[0] = SERVICE_SDBC_RESULTSET;
    aSNS[1] = SERVICE_SDBC_ROWSET;
    aSNS[2] = SERVICE_SDBCX_RESULTSET;
    aSNS[3] = SERVICE_SDB_RESULTSET;
    aSNS[4] = SERVICE_SDB_ROWSET;
    return aSNS;
}
// -------------------------------------------------------------------------
Sequence< ::rtl::OUString > SAL_CALL ORowSet::getSupportedServiceNames(  ) throw(RuntimeException)
{
    return getSupportedServiceNames_Static();
}
//------------------------------------------------------------------------------
Reference< XInterface > ORowSet::Create(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return ORowSet_CreateInstance(_rxFactory);
}
// -------------------------------------------------------------------------
// OComponentHelper
void SAL_CALL ORowSet::disposing(void)
{
    ORowSetBase::disposing();

    MutexGuard aGuard(m_aMutex);

    // free all clones
    for (connectivity::OWeakRefArray::iterator i = m_aClones.begin(); m_aClones.end() != i; i++)
    {
        Reference< XComponent > xComp(i->get(), UNO_QUERY);
        if (xComp.is())
            xComp->dispose();
    }
    m_aClones.clear();

    delete m_pParseTree;
    m_pParseTree = NULL;
}
// -------------------------------------------------------------------------

// ::com::sun::star::lang::XEventListener
void SAL_CALL ORowSet::disposing( const ::com::sun::star::lang::EventObject& Source ) throw(RuntimeException)
{
    // close rowset because the connection is going to be deleted (someone told me :-) 
    close();
    {
        MutexGuard aGuard( m_aMutex );
        //	m_xActiveConnection = NULL;
    }
}
// -------------------------------------------------------------------------

// XCloseable
void SAL_CALL ORowSet::close(  ) throw(SQLException, RuntimeException)
{
    if(m_pCache)
        m_pCache->close();
    {
        MutexGuard aGuard( m_aMutex );
        if (ORowSet_BASE1::rBHelper.bDisposed)
            throw DisposedException();
    }
    // additionals things to set
    m_bCreateStatement = sal_True;
    m_xStatement = NULL;
    m_xComposer = NULL;
}
// -------------------------------------------------------------------------
// utl::OPropertyArrayUsageHelper
::cppu::IPropertyArrayHelper* ORowSet::createArrayHelper( ) const
{
    Sequence< Property > aProps;
    describeProperties(aProps);
    return new ::cppu::OPropertyArrayHelper(aProps);
}
// -------------------------------------------------------------------------
// cppu::OPropertySetHelper
::cppu::IPropertyArrayHelper& SAL_CALL ORowSet::getInfoHelper()
{
    typedef ::utl::OPropertyArrayUsageHelper<ORowSet> ORowSet_PROP;
    return *ORowSet_PROP::getArrayHelper();
}
// -------------------------------------------------------------------------
// XRowUpdate
void SAL_CALL ORowSet::updateNull( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateNull(columnIndex);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBoolean( sal_Int32 columnIndex, sal_Bool x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateBoolean(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateByte( sal_Int32 columnIndex, sal_Int8 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateByte(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateShort( sal_Int32 columnIndex, sal_Int16 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateShort(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateInt( sal_Int32 columnIndex, sal_Int32 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateInt(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateLong( sal_Int32 columnIndex, sal_Int64 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateLong(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateFloat( sal_Int32 columnIndex, float x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateFloat(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateDouble( sal_Int32 columnIndex, double x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateDouble(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateString( sal_Int32 columnIndex, const ::rtl::OUString& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateString(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBytes( sal_Int32 columnIndex, const Sequence< sal_Int8 >& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateBytes(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateDate( sal_Int32 columnIndex, const ::com::sun::star::util::Date& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateDate(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateTime( sal_Int32 columnIndex, const ::com::sun::star::util::Time& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateTime(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateTimestamp( sal_Int32 columnIndex, const ::com::sun::star::util::DateTime& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateTimestamp(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBinaryStream( sal_Int32 columnIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateBinaryStream(columnIndex,x,length);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateCharacterStream( sal_Int32 columnIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateCharacterStream(columnIndex,x,length);
}							  
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateObject( sal_Int32 columnIndex, const Any& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateObject(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateNumericObject( sal_Int32 columnIndex, const Any& x, sal_Int32 scale ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->updateNumericObject(columnIndex,x,scale);
}
// -------------------------------------------------------------------------
Reference< XInterface > SAL_CALL ORowSet::getStatement(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    return m_xStatement;
}
// -------------------------------------------------------------------------

// XResultSetUpdate
void SAL_CALL ORowSet::insertRow(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    if(!m_pCache)
        throw FunctionSequenceException(*this);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    // remember old value for fire
    Any aOld = bool2any(m_pCache->m_bNew);

    RowChangeEvent aEvt(*this,RowChangeAction::INSERT,1);
    NOTIFY_ALL_LISTENERS_ROW_BEFORECHANGE()
    m_pCache->insertRow();
    NOTIFY_ALL_LISTENERS_ROW_CHANGED()

    // fire PROPERTY_ID_ISNEW
    sal_Int32 nHandle = PROPERTY_ID_ISNEW;
    
    if(m_pCache->m_bNew != any2bool(aOld))
    {
        Any aNew = bool2any(m_pCache->m_bNew);
        fire(&nHandle, &aNew, &aOld, 1, sal_False );
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateRow(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    if(!m_pCache)
        throw FunctionSequenceException(*this);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    RowChangeEvent aEvt(*this,RowChangeAction::UPDATE,1);
    NOTIFY_ALL_LISTENERS_ROW_BEFORECHANGE()
    m_pCache->updateRow();
    NOTIFY_ALL_LISTENERS_ROW_CHANGED()
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::deleteRow(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    RowChangeEvent aEvt(*this,RowChangeAction::DELETE,1);
    NOTIFY_ALL_LISTENERS_ROW_BEFORECHANGE()
    m_pCache->deleteRow();
    NOTIFY_ALL_LISTENERS_ROW_CHANGED()
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::cancelRowUpdates(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    m_pCache->cancelRowUpdates();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::moveToInsertRow(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    // remember old value for fire
    Any aOld = bool2any(m_pCache->m_bNew);

    NOTIFY_ALL_LISTENERS_CURSOR_BEFOREMOVE()
    m_pCache->moveToInsertRow();
    NOTIFY_ALL_LISTENERS_CURSOR_MOVED()

    // fire PROPERTY_ID_ISNEW
    sal_Int32 nHandle = PROPERTY_ID_ISNEW;
    
    if(m_pCache->m_bNew != any2bool(aOld))
    {
        Any aNew = bool2any(m_pCache->m_bNew);
        fire(&nHandle, &aNew, &aOld, 1, sal_False );
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::moveToCurrentRow(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);
    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    NOTIFY_ALL_LISTENERS_CURSOR_BEFOREMOVE()
    m_pCache->moveToCurrentRow();
    NOTIFY_ALL_LISTENERS_CURSOR_MOVED()
}
// -------------------------------------------------------------------------

// XRowSet
void SAL_CALL ORowSet::execute(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    // tell everybody that we will change the result set
    EventObject aEvt(*this);
    OInterfaceIteratorHelper aApproveIter(m_aApproveListeners);
    while (aApproveIter.hasMoreElements())
    {
        if (!((XRowSetApproveListener*)aApproveIter.next())->approveRowSetChange(aEvt))
            throw RowSetVetoException();
    }

    {
        ClearableMutexGuard aGuard( m_aMutex );
        if (ORowSet_BASE1::rBHelper.bDisposed)
            throw DisposedException();

        // calc the connection to be used
        if (m_xActiveConnection.is() && m_bRebuildConnOnExecute)
            // there was a setProperty(ActiveConnection), but a setProperty(DataSource) _after_ that, too
            m_xActiveConnection = NULL;

        calcConnection();

        m_bRebuildConnOnExecute = sal_False;
        ::rtl::OUString aSql;
        // do we need a new statement
        if (m_bCreateStatement)
        {
            // if we need a new statement we have to free the previous used columns
            //	m_aColumns.disposing();
            m_xStatement = NULL;
            m_xComposer = NULL;

            // Build the statement
            sal_Bool bUseEscapeProcessing;
            m_aActiveCommand = getCommand(bUseEscapeProcessing);
            if (m_aActiveCommand.len())
                m_xStatement = m_xActiveConnection->prepareStatement(
                                            aSql = getComposedQuery(m_aActiveCommand, bUseEscapeProcessing));

            Reference<XPropertySet> xProp(m_xStatement,UNO_QUERY);
            xProp->setPropertyValue(PROPERTY_RESULTSETTYPE,makeAny(m_nResultSetType));
            xProp->setPropertyValue(PROPERTY_RESULTSETCONCURRENCY,makeAny(m_nResultSetConcurrency));
            xProp->setPropertyValue(PROPERTY_FETCHDIRECTION,makeAny((sal_Int32)m_nFetchDirection));
        }

        if(m_pIterator)
            DELETEZ(m_pIterator);
        if(m_pParseTree)
            DELETEZ(m_pParseTree);

        String aErr;
        m_pParseTree = m_aParser.parseTree(aErr,aSql);
        if(m_pParseTree)
        {
            Reference<XNameAccess> xTables;

            //	Reference< XDriverAccess> xManager(m_xServiceManager->createInstance(SERVICE_SDBC_DRIVERMANAGER), UNO_QUERY);
            //	Reference< XDataDefinitionSupplier > xSupp(xManager->getDriverByURL(m_xActiveConnection->getMetaData()->getURL()),UNO_QUERY);
            Reference< XTablesSupplier > xMasterTables(m_xActiveConnection,UNO_QUERY);
            if(xMasterTables.is())
                xTables = xMasterTables->getTables();
            else
            {
                OTableContainer* pTables = new OTableContainer(*this,m_aMutex);
                Sequence< ::rtl::OUString > a;
                pTables->construct(m_xActiveConnection,a,a);
                xTables = pTables;
            }

            {
                m_pIterator = new OSQLParseTreeIterator(xTables,m_xActiveConnection->getMetaData(),m_pParseTree);
                m_pIterator->traverseAll();
                //	m_aColumns = m_pIterator->getSelectColumns();

                Reference<XParameters> xParam(m_xStatement,UNO_QUERY);
                sal_Int32 i = 1;
                for(ORowVector< ORowSetValue >::const_iterator aIter = m_aParameterRow.begin(); aIter != m_aParameterRow.end();++aIter,++i)
                {
                    if(aIter->isNull())
                        xParam->setNull(i,aIter->getTypeKind());
                    else
                    {
                        switch(aIter->getTypeKind())
                        {
                            case DataType::CHAR:
                            case DataType::VARCHAR:
                                xParam->setString(i,*aIter);
                                break;
                            case DataType::DOUBLE:
                            case DataType::FLOAT:
                            case DataType::REAL:
                            case DataType::DECIMAL:
                            case DataType::NUMERIC:
                                xParam->setDouble(i,*aIter);
                                break;
                            case DataType::DATE:
                                xParam->setDate(i,*aIter);
                                break;
                            case DataType::TIME:
                                xParam->setTime(i,*aIter);
                                break;
                            case DataType::TIMESTAMP:
                                xParam->setTimestamp(i,*aIter);
                                break;
                            case DataType::BINARY:
                            case DataType::VARBINARY:
                            case DataType::LONGVARBINARY:				 
                            case DataType::LONGVARCHAR:
                                xParam->setBytes(i,*aIter);
                                break;
                            case DataType::BIT:
                                xParam->setBoolean(i,*aIter);
                                break;
                            case DataType::TINYINT:
                                xParam->setByte(i,*aIter);
                                break;
                            case DataType::SMALLINT:
                                xParam->setShort(i,*aIter);
                                break;
                            case DataType::INTEGER:
                                xParam->setInt(i,*aIter);
                                break;
                        }
                    }
                }
                Reference< XResultSet> xRs = m_xStatement->executeQuery();
                m_pCache = new ORowSetCache(xRs,m_pIterator,m_aUpdateTableName);

                if(!m_xColumns.is())
                {
                    ::vos::ORef<OSQLColumns> rColumns = m_pIterator->getSelectColumns();
                    if(rColumns.isValid())
                    {
                        ORowSetDataColumns_COLLECTION aColumns;
                        ::std::vector< ::rtl::OUString> aNames;
                        sal_Int32 i=1;
                        for(OSQLColumns::const_iterator aIter = rColumns->begin();aIter != rColumns->end();++aIter,++i)
                        {
                            ORowSetDataColumn* pColumn = new ORowSetDataColumn(getMetaData(),this,this,i,m_pCache->getIterator(),m_pCache->getEnd());
                            aColumns.push_back(pColumn);
                            pColumn->setName(getMetaData()->getColumnName(i));
                            aNames.push_back(pColumn->getName());
                        }
                        m_pColumns = new ORowSetDataColumns(m_xActiveConnection->getMetaData()->supportsMixedCaseQuotedIdentifiers(),
                                                            aColumns,*this,m_aColumnsMutex,aNames);
                    }
                }
                else
                {
                    ORowSetDataColumns_COLLECTION aColumns;
                    ::std::vector< ::rtl::OUString> aNames;

                    Sequence< ::rtl::OUString> aSeq = m_xColumns->getElementNames();
                    const ::rtl::OUString* pBegin	= aSeq.getConstArray();
                    const ::rtl::OUString* pEnd		= pBegin + aSeq.getLength();
                    for(sal_Int32 i=1;pBegin != pEnd ;++pBegin,++i)
                    {
                        ORowSetDataColumn* pColumn = new ORowSetDataColumn(	getMetaData(),
                                                                            this,
                                                                            this,
                                                                            i,
                                                                            m_pCache->getIterator(),
                                                                            m_pCache->getEnd());
                        aColumns.push_back(pColumn);
                        pColumn->setName(*pBegin);
                        aNames.push_back(*pBegin);

                        Reference<XPropertySet> xColumn;
                        m_xColumns->getByName(*pBegin) >>= xColumn;
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_ALIGN,xColumn->getPropertyValue(PROPERTY_ALIGN));
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_NUMBERFORMAT,xColumn->getPropertyValue(PROPERTY_NUMBERFORMAT));
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_RELATIVEPOSITION,xColumn->getPropertyValue(PROPERTY_RELATIVEPOSITION));
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_WIDTH,xColumn->getPropertyValue(PROPERTY_WIDTH));
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HIDDEN,xColumn->getPropertyValue(PROPERTY_HIDDEN));
                        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLMODEL,xColumn->getPropertyValue(PROPERTY_CONTROLMODEL));

                    }
                    m_pColumns = new ORowSetDataColumns(m_xActiveConnection->getMetaData()->supportsMixedCaseQuotedIdentifiers(),
                                                        aColumns,*this,m_aColumnsMutex,aNames);
                }
            }
        }
        if(!m_pCache)
            throw FunctionSequenceException(*this);
    }
    // notify the rowset listeners
    NOTIFY_ALL_LISTENERS();
}
// -------------------------------------------------------------------------
// XRowSetApproveBroadcaster
void SAL_CALL ORowSet::addRowSetApproveListener( const Reference< XRowSetApproveListener >& listener ) throw(RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    m_aApproveListeners.addInterface(listener);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::removeRowSetApproveListener( const Reference< XRowSetApproveListener >& listener ) throw(RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    m_aApproveListeners.removeInterface(listener);
}
// -------------------------------------------------------------------------

// XResultSetAccess
Reference< XResultSet > SAL_CALL ORowSet::createResultSet(  ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    if(m_xStatement.is())
    {
        ORowSetClone* pClone = new ORowSetClone(*this);
        Reference< XResultSet > xRet(pClone);
        m_aClones.push_back(WeakReferenceHelper(xRet));
        return xRet;
    }
    return Reference< XResultSet >();
}
// -------------------------------------------------------------------------

// ::com::sun::star::util::XCancellable
void SAL_CALL ORowSet::cancel(  ) throw(RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(m_pCache)
        m_pCache->cancel();
}
// -------------------------------------------------------------------------

// ::com::sun::star::sdbcx::XDeleteRows
Sequence< sal_Int32 > SAL_CALL ORowSet::deleteRows( const Sequence< Any >& rows ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();

    if(!m_pCache)
        throw FunctionSequenceException(*this);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    RowChangeEvent aEvt(*this,RowChangeAction::DELETE,rows.getLength());
    // notify the rowset listeners
    NOTIFY_ALL_LISTENERS_ROW_BEFORECHANGE()

    return m_pCache->deleteRows(rows);
}
//------------------------------------------------------------------------------
Reference< XConnection >  ORowSet::calcConnection() throw( SQLException, RuntimeException )
{
    MutexGuard aGuard(m_aMutex);
    if (!m_xActiveConnection.is())
    {
        if (m_aDataSourceName.len())
        {
            // is it a file url?
            Reference< ::com::sun::star::container::XNameAccess >  xNamingContext(m_xServiceManager->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
            if (xNamingContext.is() && xNamingContext->hasByName(m_aDataSourceName))
            {
                try
                {
                    Reference< XDataSource >  xDataSource(Reference< XNamingService > (xNamingContext, UNO_QUERY)->getRegisteredObject(m_aDataSourceName), UNO_QUERY);
                    if (xDataSource.is())
                        m_xActiveConnection = xDataSource->getConnection(m_aUser, m_aPassword);
                }
                catch (SQLException &e)
                {
                    throw e;
                }
                catch (...)
                {
                    throw SQLException();
                }
            }
            else
            {
#ifdef DEBUG
                Reference<XDriverManager> xMan(m_xServiceManager->createInstance(::rtl::OUString::createFromAscii("com.sun.star.sdbc.DriverManager")),UNO_QUERY);
                m_xActiveConnection = xMan->getConnection(::rtl::OUString::createFromAscii("sdbc:dbase:g:\\office50\\user\\database\\biblio\\biblio.dbf"));
                if(!m_xActiveConnection.is())
#endif
                    throw SQLException();

            }
//			{
//				Reference< XDatabaseEnvironment >  xEnvironment(m_xServiceManager->createInstance(SERVICE_SDB_DATABASEENVIRONMENT), UNO_QUERY);
//				if (xEnvironment.is())
//				{
//					Reference< XDataSource >  xDataSource(xEnvironment->getDatabaseAccess(m_aDataSourceName), UNO_QUERY);
//					if (xDataSource.is())
//						m_xActiveConnection = xDataSource->getConnection(m_aUser, m_aPassword);
//				}
//			}
        }
//		else if (m_aURL.len())
//		{
//			Reference< XDatabaseEnvironment >  xEnvironment(m_xServiceManager->createInstance(SERVICE_SDB_DATABASEENVIRONMENT), UNO_QUERY);
//			if (xEnvironment.is())
//			{
//				if (m_aUser.len())
//				{
//					Sequence< PropertyValue > aInfo(2);
//					aInfo.getArray()[0].Name = rtl::OUString::createFromAscii("User");
//					aInfo.getArray()[0].Value <<= m_aUser;
//					aInfo.getArray()[1].Name = rtl::OUString::createFromAscii("Password");
//					aInfo.getArray()[1].Value <<= m_aPassword;
//					m_xActiveConnection = xEnvironment->getConnectionWithInfo(m_aURL, aInfo);
//				}
//				else
//					m_xActiveConnection = xEnvironment->getConnection(m_aURL);
//			}
//		}

        // listen if the connection disappears
        Reference< XComponent >  xComponent(m_xActiveConnection, UNO_QUERY);
        if (xComponent.is())
            xComponent->addEventListener(this);
    }
    return m_xActiveConnection;
}
//------------------------------------------------------------------------------
rtl::OUString ORowSet::getCommand(sal_Bool& bEscapeProcessing)
{
    // create the sql command
    // from a table name or get the command out of a query (not a view)
    // the last use the command as it is
    bEscapeProcessing = m_bUseEscapeProcessing;
    rtl::OUString aQuery;
    if (m_aCommand.len())
    {
        switch (m_nCommandType)
        {
            case CommandType::TABLE:
            {
                Reference< XTablesSupplier >  xTablesAccess(m_xActiveConnection, UNO_QUERY);
                if (xTablesAccess.is())
                {
                    Reference< ::com::sun::star::container::XNameAccess >  xTables(xTablesAccess->getTables());
                    if (xTables->hasByName(m_aCommand))
                    {
                        Reference< XPropertySet > xTable;
                        xTables->getByName(m_aCommand) >>= xTable;

                        Reference<XColumnsSupplier> xSup(xTable,UNO_QUERY);
                        if(xSup.is())
                            m_xColumns = xSup->getColumns();
                    }
                }
                aQuery = rtl::OUString::createFromAscii("SELECT * FROM ");
                aQuery += ::utl::quoteTableName(m_xActiveConnection->getMetaData(), m_aCommand);
            }
                break;
            case CommandType::QUERY:
            {
                Reference< XQueriesSupplier >  xQueriesAccess(m_xActiveConnection, UNO_QUERY);
                if (xQueriesAccess.is())
                {
                    Reference< ::com::sun::star::container::XNameAccess >  xQueries(xQueriesAccess->getQueries());
                    if (xQueries->hasByName(m_aCommand))
                    {
                        Reference< XPropertySet > xQuery;
                        xQueries->getByName(m_aCommand) >>= xQuery;
                        xQuery->getPropertyValue(PROPERTY_COMMAND) >>= aQuery;
                        bEscapeProcessing = any2bool(xQuery->getPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING));
                        
                        ::rtl::OUString aCatalog,aSchema,aTable;
                        xQuery->getPropertyValue(CONFIGKEY_QRYDESCR_UPDATE_CATALOGNAME) >>= aCatalog;
                        xQuery->getPropertyValue(CONFIGKEY_QRYDESCR_UPDATE_SCHEMANAME)	>>= aSchema;
                        xQuery->getPropertyValue(CONFIGKEY_QRYDESCR_UPDATE_TABLENAME)	>>= aTable;
                        
                        composeTableName(m_xActiveConnection->getMetaData(),aCatalog,aSchema,aTable,m_aUpdateTableName,sal_False);

                        Reference<XColumnsSupplier> xSup(xQuery,UNO_QUERY);
                        if(xSup.is())
                            m_xColumns = xSup->getColumns();
                    }
                }
            }	break;
            default:
                aQuery = m_aCommand;
        }
    }
    return aQuery;
}
//------------------------------------------------------------------------------
rtl::OUString ORowSet::getComposedQuery(const rtl::OUString& rQuery, sal_Bool bEscapeProcessing) throw( SQLException, RuntimeException )
{
    // use query composer to make a useful query with filter and/or order by part
    rtl::OUString aFilterStatement = rQuery;
    if (bEscapeProcessing)
    {
        Reference< XSQLQueryComposerFactory >  xFactory(m_xActiveConnection, UNO_QUERY);
        if (xFactory.is())
        {				  
            try
            {
                m_xComposer = xFactory->createQueryComposer();
                m_xComposer->setQuery(rQuery);

                if (m_aFilter.len() && m_bApplyFilter)
                    m_xComposer->setFilter(m_aFilter);
                if (m_aOrder.len())
                    m_xComposer->setOrder(m_aOrder);

                aFilterStatement = m_xComposer->getComposedQuery();
            }
            catch (...)
            {
                m_xComposer = NULL;
            }
        }										   
    }
    return aFilterStatement;
}
// -------------------------------------------------------------------------					 
// XParameters
void SAL_CALL ORowSet::setNull( sal_Int32 parameterIndex, sal_Int32 sqlType ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    m_aParameterRow[parameterIndex-1].setNull();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObjectNull( sal_Int32 parameterIndex, sal_Int32 sqlType, const ::rtl::OUString& typeName ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1].setNull();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBoolean( sal_Int32 parameterIndex, sal_Bool x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setByte( sal_Int32 parameterIndex, sal_Int8 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = (sal_Int32)x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setShort( sal_Int32 parameterIndex, sal_Int16 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = (sal_Int32)x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setInt( sal_Int32 parameterIndex, sal_Int32 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setLong( sal_Int32 parameterIndex, sal_Int64 x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setFloat( sal_Int32 parameterIndex, float x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setDouble( sal_Int32 parameterIndex, double x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setString( sal_Int32 parameterIndex, const ::rtl::OUString& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBytes( sal_Int32 parameterIndex, const Sequence< sal_Int8 >& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setDate( sal_Int32 parameterIndex, const ::com::sun::star::util::Date& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setTime( sal_Int32 parameterIndex, const ::com::sun::star::util::Time& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setTimestamp( sal_Int32 parameterIndex, const ::com::sun::star::util::DateTime& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBinaryStream( sal_Int32 parameterIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    try
    {
        Sequence <sal_Int8> aData;
        x->readBytes(aData, length);
        m_aParameterRow[parameterIndex-1] = aData;
        x->closeInput();
    }
    catch( ... )
    {
        throw SQLException();
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setCharacterStream( sal_Int32 parameterIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    try
    {
        Sequence <sal_Int8> aData;
        rtl::OUString aDataStr;
        // the data is given as character data and the length defines the character length
        sal_Int32 nSize = x->readBytes(aData, length * sizeof(sal_Unicode));
        if (nSize / sizeof(sal_Unicode))
            aDataStr = rtl::OUString((sal_Unicode*)aData.getConstArray(), nSize / sizeof(sal_Unicode));
        m_aParameterRow[parameterIndex-1] = aDataStr;
        m_aParameterRow[parameterIndex-1].setTypeKind(DataType::LONGVARCHAR);
        x->closeInput();
    }
    catch( ... )
    {
        throw SQLException();
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObject( sal_Int32 parameterIndex, const Any& x ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    if (x.getValueTypeClass() == TypeClass_ANY)
        setObject(parameterIndex, Any(*(Any*)x.getValue()));
    else
    {
        try
        {
            switch (x.getValueTypeClass())
            {
                case TypeClass_VOID:
                    setNull(parameterIndex, DataType::SQLNULL);
                    break;
                case TypeClass_STRING:
                    setString(parameterIndex, *(rtl::OUString*)x.getValue());
                    break;
                case TypeClass_BOOLEAN:
                    setBoolean(parameterIndex, *(sal_Bool *)x.getValue());
                    break;
                case TypeClass_BYTE:
                    setByte(parameterIndex, *(sal_Int8 *)x.getValue());
                    break;
                case TypeClass_UNSIGNED_SHORT:
                case TypeClass_SHORT:
                    setShort(parameterIndex, *(sal_Int16*)x.getValue());
                    break;
                case TypeClass_CHAR:
                    setShort(parameterIndex, *(sal_Int16*)(sal_Unicode *)x.getValue());//XXX
                    break;
                case TypeClass_LONG:
                case TypeClass_UNSIGNED_LONG:
                    setInt(parameterIndex, *(sal_Int32*)x.getValue());
                    break;
                case TypeClass_FLOAT:
                    setFloat(parameterIndex, *(float*)x.getValue());
                    break;
                case TypeClass_DOUBLE:
                    setDouble(parameterIndex, *(double*)x.getValue());
                    break;
                case TypeClass_SEQUENCE:
                    if (x.getValueType() == ::getCppuType((const Sequence< sal_Int8 > *)0))
                        setBytes(parameterIndex, *(Sequence<sal_Int8>*)x.getValue());
                    else
                        throw IllegalArgumentException();
                    break;
                case TypeClass_STRUCT:
                case TypeClass_INTERFACE:
                    if (x.getValueType() == ::getCppuType(static_cast<Reference< ::com::sun::star::io::XInputStream>*>(NULL)))
                    {
                        Reference< ::com::sun::star::io::XInputStream >  xStream;
                        x >>= xStream;
                        setBinaryStream(parameterIndex, xStream, xStream->available());
                    }
                    else if (x.getValueType() == ::getCppuType((const ::com::sun::star::util::DateTime*)0))
                        setTimestamp(parameterIndex, *(::com::sun::star::util::DateTime*)x.getValue());
                    else if (x.getValueType() == ::getCppuType((const ::com::sun::star::util::Date*)0))
                        setDate(parameterIndex, *(::com::sun::star::util::Date*)x.getValue());
                    else if (x.getValueType() == ::getCppuType((const ::com::sun::star::util::Time*)0))
                        setTime(parameterIndex, *(::com::sun::star::util::Time*)x.getValue());
                    else
                        throw SQLException();
                    break;
                default:
                    throw SQLException();
            }
        }
        catch( ... )
        {
            throw SQLException();
        }
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObjectWithInfo( sal_Int32 parameterIndex, const Any& x, sal_Int32 targetSqlType, sal_Int32 scale ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    else if (parameterIndex < 1)
        throw SQLException();
    else if (m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    setObject(parameterIndex, x);
    m_aParameterRow[parameterIndex-1].setTypeKind(targetSqlType);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setRef( sal_Int32 parameterIndex, const Reference< XRef >& x ) throw(SQLException, RuntimeException)
{
    throw SQLException();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBlob( sal_Int32 parameterIndex, const Reference< XBlob >& x ) throw(SQLException, RuntimeException)
{
    throw SQLException();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setClob( sal_Int32 parameterIndex, const Reference< XClob >& x ) throw(SQLException, RuntimeException)
{
    throw SQLException();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setArray( sal_Int32 parameterIndex, const Reference< XArray >& x ) throw(SQLException, RuntimeException)
{
    throw SQLException();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::clearParameters(  ) throw(SQLException, RuntimeException)
{
    if (ORowSet_BASE1::rBHelper.bDisposed)
        throw DisposedException();
    
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    m_aParameterRow.clear();
}
// -------------------------------------------------------------------------
//************************************************************
//  ORowSetClone
//************************************************************
DBG_NAME(ORowSetClone);
//--------------------------------------------------------------------------
ORowSetClone::ORowSetClone(ORowSet& rParent)
             :OSubComponent(m_aMutex, rParent)
             ,ORowSetBase(OComponentHelper::rBHelper)
             ,m_nFetchDirection(rParent.m_nFetchDirection)
             ,m_nFetchSize(rParent.m_nFetchSize)
             ,m_nResultSetConcurrency(ResultSetConcurrency::READ_ONLY)
             ,m_nResultSetType(rParent.m_nResultSetType)
             
             ,m_bDeleted(rParent.m_bDeleted)
             ,m_bRowObsolete(rParent.m_bRowObsolete)
             ,m_nPosition(rParent.m_nPosition)
             ,m_bIsBookmarable(sal_True)
{
    DBG_CTOR(ORowSetClone, NULL);

    m_pMySelf		= this;
    m_bClone		= sal_True;

    m_bBeforeFirst	= rParent.m_bBeforeFirst;
    m_bAfterLast	= rParent.m_bAfterLast;
    m_pIterator		= rParent.m_pIterator;
    m_pCache		= rParent.m_pCache;

    //	m_pCache = rParent.m_pCache->createClone();

    ORowSetDataColumns_COLLECTION aColumns;
    ::std::vector< ::rtl::OUString> aNames;

    Sequence< ::rtl::OUString> aSeq = rParent.m_pColumns->getElementNames();
    const ::rtl::OUString* pBegin	= aSeq.getConstArray();
    const ::rtl::OUString* pEnd		= pBegin + aSeq.getLength();
    for(sal_Int32 i=1;pBegin != pEnd ;++pBegin,++i)
    {
        ORowSetColumn* pColumn = new ORowSetColumn(	rParent.getMetaData(),
                                                            this,
                                                            i,
                                                            m_pCache->getIterator(),
                                                            m_pCache->getEnd());
        aColumns.push_back(pColumn);
        pColumn->setName(*pBegin);
        aNames.push_back(*pBegin);

        Reference<XPropertySet> xColumn;
        rParent.m_pColumns->getByName(*pBegin) >>= xColumn;
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_ALIGN,xColumn->getPropertyValue(PROPERTY_ALIGN));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_NUMBERFORMAT,xColumn->getPropertyValue(PROPERTY_NUMBERFORMAT));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_RELATIVEPOSITION,xColumn->getPropertyValue(PROPERTY_RELATIVEPOSITION));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_WIDTH,xColumn->getPropertyValue(PROPERTY_WIDTH));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HIDDEN,xColumn->getPropertyValue(PROPERTY_HIDDEN));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLMODEL,xColumn->getPropertyValue(PROPERTY_CONTROLMODEL));

    }
    m_pColumns = new ORowSetDataColumns(rParent.m_xActiveConnection->getMetaData()->supportsMixedCaseQuotedIdentifiers(),
                                        aColumns,*this,m_aMutex,aNames);

    sal_Int32 nRT	= PropertyAttribute::READONLY	| PropertyAttribute::TRANSIENT;

    // sdb.RowSet Properties
    //	registerProperty(PROPERTY_CURSORNAME,		PROPERTY_ID_CURSORNAME,			PropertyAttribute::READONLY,		&m_aDataSourceName,		::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));

    registerProperty(PROPERTY_RESULTSETCONCURRENCY,	PROPERTY_ID_RESULTSETCONCURRENCY,	PropertyAttribute::READONLY,	&m_nResultSetConcurrency,::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_RESULTSETTYPE,		PROPERTY_ID_RESULTSETTYPE,			PropertyAttribute::READONLY,	&m_nResultSetType,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_FETCHDIRECTION,		PROPERTY_ID_FETCHDIRECTION,			PropertyAttribute::TRANSIENT,	&m_nFetchDirection,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_FETCHSIZE,			PROPERTY_ID_FETCHSIZE,				PropertyAttribute::TRANSIENT,	&m_nFetchSize,			::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_ISBOOKMARKABLE,		PROPERTY_ID_ISBOOKMARKABLE,			nRT,							&m_bIsBookmarable,		::getBooleanCppuType());
}

//--------------------------------------------------------------------------
ORowSetClone::~ORowSetClone()
{
    //	delete m_pCache;
    DBG_DTOR(ORowSetClone, NULL);
}
// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< Type > ORowSetClone::getTypes() throw (RuntimeException)
{
    return ::utl::concatSequences(OSubComponent::getTypes(),ORowSetBase::getTypes());
}
// com::sun::star::uno::XInterface
//--------------------------------------------------------------------------
Any ORowSetClone::queryInterface( const Type & rType ) throw (RuntimeException)
{
    Any aRet = ORowSetBase::queryInterface(rType);
    if(!aRet.hasValue())
        aRet = OSubComponent::queryInterface(rType);
    return aRet;
}
//------------------------------------------------------------------------------
void ORowSetClone::acquire() throw(::com::sun::star::uno::RuntimeException)
{
    OSubComponent::acquire();
}

//------------------------------------------------------------------------------
void ORowSetClone::release() throw(::com::sun::star::uno::RuntimeException)
{
    OSubComponent::release();
}

// XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString ORowSetClone::getImplementationName(  ) throw(RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.ORowSetClone");
}

//------------------------------------------------------------------------------
sal_Bool ORowSetClone::supportsService( const ::rtl::OUString& _rServiceName ) throw (RuntimeException)
{
    return ::utl::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > ORowSetClone::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBC_RESULTSET;
    aSNS[1] = SERVICE_SDB_RESULTSET;
    return aSNS;
}

// OComponentHelper
//------------------------------------------------------------------------------
void ORowSetClone::disposing()
{
    ORowSetBase::disposing();
    OSubComponent::disposing();
}

// XCloseable
//------------------------------------------------------------------------------
void ORowSetClone::close(void) throw( SQLException, RuntimeException )
{
    {
        MutexGuard aGuard( m_aMutex );
        if (OComponentHelper::rBHelper.bDisposed)
            throw DisposedException();
    }
    dispose();
}
// -------------------------------------------------------------------------

// utl::OPropertyArrayUsageHelper
::cppu::IPropertyArrayHelper* ORowSetClone::createArrayHelper( ) const
{
    Sequence< Property > aProps;
    describeProperties(aProps);
    return new ::cppu::OPropertyArrayHelper(aProps);
}
// -------------------------------------------------------------------------

// cppu::OPropertySetHelper
::cppu::IPropertyArrayHelper& SAL_CALL ORowSetClone::getInfoHelper()
{
    typedef ::utl::OPropertyArrayUsageHelper<ORowSetClone> ORowSetClone_PROP;
    return *ORowSetClone_PROP::getArrayHelper();
}
// -------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL ORowSetClone::getImplementationId() throw (RuntimeException)
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
// -------------------------------------------------------------------------
// com::sun::star::lang::XUnoTunnel
sal_Int64 SAL_CALL ORowSetClone::getSomething( const Sequence< sal_Int8 >& rId ) throw(RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;

    return 0;
}

/*------------------------------------------------------------------------

    $Log: not supported by cvs2svn $
    Revision 1.2  2000/09/18 14:52:46  willem.vandorp
    OpenOffice header added.
    
    Revision 1.1  2000/09/01 15:19:23  oj
    rowset addons
    
    Revision 1.0 25.07.2000 14:10:09  oj
------------------------------------------------------------------------*/

