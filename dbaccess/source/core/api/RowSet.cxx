/*************************************************************************
 *
 *  $RCSfile: RowSet.cxx,v $
 *
 *  $Revision: 1.117 $
 *
 *  last change: $Author: oj $ $Date: 2002-12-10 15:49:46 $
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
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
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
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
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
#ifndef _COM_SUN_STAR_SDBCX_COMPAREBOOKMARK_HPP_
#include <com/sun/star/sdbcx/CompareBookmark.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBACCESS_CORE_API_ROWSETCACHE_HXX
#include "RowSetCache.hxx"
#endif
#ifndef _DBA_REGHELPER_HXX_
#include "dba_reghelper.hxx"
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
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COMPHELPER_SEQSTREAM_HXX
#include <comphelper/seqstream.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef DBACCESS_CORE_API_QUERYCOMPOSER_HXX
#include "querycomposer.hxx"
#endif
#ifndef _DBA_CORE_TABLECONTAINER_HXX_
#include "tablecontainer.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_XINTERACTIONSUPPLYPARAMETERS_HPP_
#include <com/sun/star/sdb/XInteractionSupplyParameters.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_PARAMETERSREQUEST_HPP_
#include <com/sun/star/sdb/ParametersRequest.hpp>
#endif
#include <com/sun/star/sdb/ParametersRequest.hpp>
#ifndef _COM_SUN_STAR_SDB_XPARAMETERSSUPPLIER_HPP_
#include <com/sun/star/sdb/XParametersSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATSSUPPLIER_HPP_
#include <com/sun/star/util/XNumberFormatsSupplier.hpp>
#endif
#ifndef _COMPHELPER_INTERACTION_HXX_
#include <comphelper/interaction.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBCX_COMPAREBOOKMARK_HPP_
#include <com/sun/star/sdbcx/CompareBookmark.hpp>
#endif
#ifndef _DBA_CORE_RESOURCE_HXX_
#include "core_resource.hxx"
#endif
#ifndef _DBA_CORE_RESOURCE_HRC_
#include "core_resource.hrc"
#endif
#ifndef _DBHELPER_DBCONVERSION_HXX_
#include <connectivity/dbconversion.hxx>
#endif

using namespace utl;
using namespace dbaccess;
using namespace connectivity;
using namespace comphelper;
using namespace dbtools;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::util;
using namespace ::cppu;
using namespace ::osl;

//--------------------------------------------------------------------------
extern "C" void SAL_CALL createRegistryInfo_ORowSet()
{
    static OMultiInstanceAutoRegistration< ORowSet > aAutoRegistration;
}
// -----------------------------------------------------------------------------
#define NOTIFY_LISTERNERS(_rListeners,T,method)									  \
    Sequence< Reference< XInterface > > aListenerSeq = _rListeners.getElements(); \
                                                                                  \
    const Reference< XInterface >* pxIntBegin = aListenerSeq.getConstArray();	  \
    const Reference< XInterface >* pxInt = pxIntBegin + aListenerSeq.getLength(); \
                                                                                  \
    _rGuard.clear();															  \
    while( pxInt > pxIntBegin )													  \
    {																			  \
        try																		  \
        {																		  \
            while( pxInt > pxIntBegin )											  \
            {																	  \
                --pxInt;														  \
                static_cast< T* >( pxInt->get() )->method(aEvt);				  \
            }																	  \
        }																		  \
        catch( RuntimeException& )												  \
        {																		  \
        }																		  \
    }																			  \
    _rGuard.reset();

#define NOTIFY_LISTERNERS_CHECK(_rListeners,T,method)							  \
    Sequence< Reference< XInterface > > aListenerSeq = _rListeners.getElements(); \
                                                                                  \
    const Reference< XInterface >* pxIntBegin = aListenerSeq.getConstArray();	  \
    const Reference< XInterface >* pxInt = pxIntBegin + aListenerSeq.getLength(); \
                                                                                  \
    _rGuard.clear();															  \
    sal_Bool bCheck = sal_True;													  \
    while( pxInt > pxIntBegin && bCheck )										  \
    {																			  \
        try																		  \
        {																		  \
            while( pxInt > pxIntBegin && bCheck )								  \
            {																	  \
                --pxInt;														  \
                bCheck = static_cast< T* >( pxInt->get() )->method(aEvt);		  \
            }																	  \
        }																		  \
        catch( RuntimeException& )												  \
        {																		  \
        }																		  \
    }																			  \
    _rGuard.reset();

                                                                                  
//..................................................................
namespace dbaccess
{
//..................................................................


//--------------------------------------------------------------------------
Reference< XInterface > ORowSet_CreateInstance(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return *(new ORowSet(_rxFactory));
}
//--------------------------------------------------------------------------
ORowSet::ORowSet(const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xFac)
    : ORowSet_BASE1(m_aMutex)
    , ORowSetBase(ORowSet_BASE1::rBHelper,&m_aMutex)
    , m_xServiceManager(_xFac)
    ,m_aRowsetListeners(*m_pMutex)
    ,m_aApproveListeners(*m_pMutex)
    ,m_nFetchDirection(FetchDirection::FORWARD)
    ,m_nFetchSize(1)
    ,m_nCommandType(CommandType::COMMAND)
    ,m_nMaxFieldSize(0)
    ,m_nTransactionIsolation(0)
    ,m_nPrivileges(0)
    ,m_nAsyncUpdateRowCount(0)
    ,m_nMaxRows(0)
    ,m_nQueryTimeOut(0)
    ,m_bUseEscapeProcessing(sal_True)
    ,m_bApplyFilter(sal_False)
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
    ,m_bCanUpdateInsertedRows(sal_True)
    ,m_pTables(NULL)
    ,m_bOwnConnection(sal_False)
{
    m_nResultSetType = ResultSetType::SCROLL_INSENSITIVE;
    m_nResultSetConcurrency = ResultSetConcurrency::UPDATABLE;
    m_pMySelf = this;
    m_aActiveConnection <<= m_xActiveConnection;

    sal_Int32 nRBT	= PropertyAttribute::READONLY	| PropertyAttribute::BOUND		| PropertyAttribute::TRANSIENT;
    sal_Int32 nRT	= PropertyAttribute::READONLY	| PropertyAttribute::TRANSIENT;
    sal_Int32 nBT	= PropertyAttribute::BOUND		| PropertyAttribute::TRANSIENT;

    // sdb.RowSet Properties
    registerMayBeVoidProperty(PROPERTY_ACTIVECONNECTION,PROPERTY_ID_ACTIVECONNECTION,	PropertyAttribute::MAYBEVOID|PropertyAttribute::TRANSIENT|PropertyAttribute::BOUND,	&m_aActiveConnection,	::getCppuType(reinterpret_cast< Reference< XConnection >* >(NULL)));
    registerProperty(PROPERTY_DATASOURCENAME,		PROPERTY_ID_DATASOURCENAME,			PropertyAttribute::BOUND,		&m_aDataSourceName,		::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_COMMAND,				PROPERTY_ID_COMMAND,				PropertyAttribute::BOUND,		&m_aCommand,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_COMMANDTYPE,			PROPERTY_ID_COMMANDTYPE,			PropertyAttribute::BOUND,		&m_nCommandType,		::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_ACTIVECOMMAND,		PROPERTY_ID_ACTIVECOMMAND,			nRBT,							&m_aActiveCommand,		::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_IGNORERESULT,			PROPERTY_ID_IGNORERESULT,			PropertyAttribute::BOUND,		&m_bIgnoreResult,		::getBooleanCppuType());
    registerProperty(PROPERTY_FILTER,				PROPERTY_ID_FILTER,					PropertyAttribute::BOUND,		&m_aFilter,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_APPLYFILTER,			PROPERTY_ID_APPLYFILTER,			PropertyAttribute::BOUND,		&m_bApplyFilter,		::getBooleanCppuType());
    registerProperty(PROPERTY_ORDER,				PROPERTY_ID_ORDER,					PropertyAttribute::BOUND,		&m_aOrder,				::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_PRIVILEGES,			PROPERTY_ID_PRIVILEGES,				nRT,							&m_nPrivileges,			::getCppuType(reinterpret_cast< sal_Int32*>(NULL)));
    registerProperty(PROPERTY_ISMODIFIED,			PROPERTY_ID_ISMODIFIED,				nBT,							&m_bModified,			::getBooleanCppuType());
    registerProperty(PROPERTY_ISNEW,				PROPERTY_ID_ISNEW,					nRBT,							&m_bNew,				::getBooleanCppuType());


    // sdbcx.ResultSet Properties
    registerProperty(PROPERTY_ISBOOKMARKABLE,		PROPERTY_ID_ISBOOKMARKABLE,			nRT,							&m_bIsBookmarable,		::getBooleanCppuType());
    registerProperty(PROPERTY_CANUPDATEINSERTEDROWS,PROPERTY_ID_CANUPDATEINSERTEDROWS,	nRT,							&m_bCanUpdateInsertedRows,		::getBooleanCppuType());
    // sdbc.ResultSet Properties
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
    registerProperty(PROPERTY_PASSWORD,				PROPERTY_ID_PASSWORD,				PropertyAttribute::TRANSIENT,	&m_aPassword,			::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));

    registerProperty(PROPERTY_UPDATE_CATALOGNAME,	PROPERTY_ID_UPDATE_CATALOGNAME,		PropertyAttribute::BOUND,		&m_aUpdateCatalogName,	::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_UPDATE_SCHEMANAME,	PROPERTY_ID_UPDATE_SCHEMANAME,		PropertyAttribute::BOUND,		&m_aUpdateSchemaName,	::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));
    registerProperty(PROPERTY_UPDATE_TABLENAME,		PROPERTY_ID_UPDATE_TABLENAME,		PropertyAttribute::BOUND,		&m_aUpdateTableName,	::getCppuType(reinterpret_cast< ::rtl::OUString*>(NULL)));

    m_aParameterRow.clear(); // because it was constructed with one element as default
}
// -------------------------------------------------------------------------
//	typedef ::comphelper::OPropertyArrayUsageHelper<ORowSet> ORowSet_Prop;

void SAL_CALL ORowSet::setFastPropertyValue_NoBroadcast(sal_Int32 nHandle,const Any& rValue) throw (Exception)
{
    switch(nHandle)
    {
        case PROPERTY_ID_ISMODIFIED:
            m_bModified = cppu::any2bool(rValue);
            break;
        case PROPERTY_ID_FETCHDIRECTION:
            if( m_nResultSetType == ResultSetType::FORWARD_ONLY)
                throw Exception(); // else run through
        default:
            OPropertyContainer::setFastPropertyValue_NoBroadcast(nHandle,rValue);
    }

    switch(nHandle)
    {
        case PROPERTY_ID_ACTIVECONNECTION:
            // the new connection
            {
                Reference< XConnection > xNewConnection;
                m_aActiveConnection >>= xNewConnection;
                setActiveConnection(xNewConnection, sal_False);
            }

            m_bOwnConnection		= sal_False;
            m_bCreateStatement		= sal_True;
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
            if(!m_xStatement.is())
            {
                Reference< XConnection >  xNewConn;
                Any aNewConn;
                aNewConn <<= xNewConn;
                setFastPropertyValue(PROPERTY_ID_ACTIVECONNECTION, aNewConn);
            }
            else
                m_bRebuildConnOnExecute = sal_True;
            m_bCreateStatement = sal_True;
            //	m_bOwnConnection   = sal_True;
            break;
        case PROPERTY_ID_FETCHSIZE:
            if(m_pCache)
            {
                m_pCache->setMaxRowSize(m_nFetchSize);
                fireRowcount();
            }
            break;
        case PROPERTY_ID_FILTER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_ORDER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_URL:
            // is the connection-to-be-built determined by the url (which is the case if m_aDataSourceName is empty) ?
            if (!m_aDataSourceName.getLength())
            {
                // are we active at the moment ?
                if (m_xStatement.is())
                    // yes -> the next execute needs to rebuild our connection because of this new property
                    m_bRebuildConnOnExecute = sal_True;
                else
                {	// no -> drop our active connection (if we have one) as it doesn't correspond to this new property value anymore
                    Reference< XConnection >  xNewConn;
                    Any aNewConn;
                    aNewConn <<= xNewConn;
                    setFastPropertyValue(PROPERTY_ID_ACTIVECONNECTION, aNewConn);
                }
            }
            m_bCreateStatement = sal_True;
            m_bOwnConnection = sal_True;
            break;
        case PROPERTY_ID_USER:
            m_bCreateStatement = sal_True;
            break;
        case PROPERTY_ID_TYPEMAP:
            ::cppu::extractInterface(m_xTypeMap,m_aTypeMap);
            break;
        default:
            ;
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
            rValue.setValue(&m_bModified,::getCppuBooleanType());
            break;			
        case PROPERTY_ID_ISNEW:
            rValue.setValue(&m_bNew,::getCppuBooleanType());
            break;
        case PROPERTY_ID_PRIVILEGES:
            rValue <<= m_pCache->m_nPrivileges;
            break;
        case PROPERTY_ID_ACTIVECONNECTION:
            rValue <<= m_xActiveConnection;
            break;
        case PROPERTY_ID_TYPEMAP:
            rValue <<= m_xTypeMap;
            break;
        default:
            ORowSetBase::getFastPropertyValue(rValue,nHandle);
        };
    }	
    else
    {
        switch(nHandle)
        {
            case PROPERTY_ID_ACTIVECONNECTION:
                rValue <<= m_xActiveConnection;
                break;
            case PROPERTY_ID_TYPEMAP:
                rValue <<= m_xTypeMap;
                break;
            default:
                ORowSetBase::getFastPropertyValue(rValue,nHandle);
        }
    }
}
// -------------------------------------------------------------------------
// com::sun::star::XTypeProvider
Sequence< Type > SAL_CALL ORowSet::getTypes() throw (RuntimeException)
{
    OTypeCollection aTypes(::getCppuType( (const Reference< XPropertySet > *)0 ),
                            ::getCppuType( (const Reference< XFastPropertySet > *)0 ),
                            ::getCppuType( (const Reference< XMultiPropertySet > *)0 ),
                           ::comphelper::concatSequences(ORowSet_BASE1::getTypes(),ORowSetBase::getTypes()));
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

// com::sun::star::XInterface
Any SAL_CALL ORowSet::queryInterface( const Type & rType ) throw (RuntimeException)
{
    return ORowSet_BASE1::queryInterface( rType);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::acquire() throw()
{
    ORowSet_BASE1::acquire();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::release() throw()
{
    ORowSet_BASE1::release();
}
// -------------------------------------------------------------------------

// com::sun::star::XUnoTunnel
sal_Int64 SAL_CALL ORowSet::getSomething( const Sequence< sal_Int8 >& rId ) throw(RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;

    return 0;
}
// -------------------------------------------------------------------------
// com::sun::star::XAggregation
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
    return rtl::OUString::createFromAscii("com.sun.star.comp.dba.ORowSet");
}
// -------------------------------------------------------------------------
// ::com::sun::star::XServiceInfo
::rtl::OUString SAL_CALL ORowSet::getImplementationName(  ) throw(RuntimeException)
{
    return getImplementationName_Static();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL ORowSet::supportsService( const ::rtl::OUString& _rServiceName ) throw(RuntimeException)
{
    return ::comphelper::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
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
    OPropertyContainer::disposing();

    MutexGuard aGuard(m_aMutex);
    EventObject aDisposeEvent;
    aDisposeEvent.Source = static_cast< XComponent* >(this);
    m_aRowsetListeners.disposeAndClear( aDisposeEvent );
    m_aApproveListeners.disposeAndClear( aDisposeEvent );

    // just because we want to clear all see freeResources()
    m_bCreateStatement = sal_True;
    freeResources();
    m_xServiceManager	= NULL;
    // remove myself as dispose listener
    Reference< XComponent >  xComponent(m_xActiveConnection, UNO_QUERY);
    if (xComponent.is())
    {
        Reference<XEventListener> xEvt;
        query_aggregation(this,xEvt);
        xComponent->removeEventListener(xEvt);
    }

    m_aActiveConnection = Any(); // the any conatains a reference too
    if(m_bOwnConnection)
        ::comphelper::disposeComponent(m_xActiveConnection);
    m_xActiveConnection = NULL;
    

    ORowSetBase::disposing();
}
// -------------------------------------------------------------------------
void ORowSet::freeResources()
{
    MutexGuard aGuard(m_aMutex);

    // free all clones
    for (connectivity::OWeakRefArray::iterator i = m_aClones.begin(); m_aClones.end() != i; i++)
    {
        Reference< XComponent > xComp(i->get(), UNO_QUERY);
        if (xComp.is())
            xComp->dispose();
    }
    m_aClones.clear();
    if (m_bCreateStatement)
    {
        // the columns must be disposed before the querycomposer is disposed because
        // their owner can be the composer
        TDataColumns().swap(m_aDataColumns);// clear and resize capacity
        m_xColumns		= NULL;
        if(m_pColumns)
            m_pColumns->disposing();
        // dispose the composer to avoid that everbody knows that the querycomposer is eol
        Reference< XComponent > xComp(m_xComposer, UNO_QUERY);
        if (xComp.is())
            xComp->dispose();
        m_xComposer		= NULL;

        DELETEZ(m_pCache);
        
        if(m_pTables)
        {
            m_pTables->dispose(); // clear all references
            DELETEZ(m_pTables);
        }

        m_xStatement	= NULL;
        m_xTypeMap		= NULL;
        
        m_aBookmark		= Any();
        m_bBeforeFirst	= sal_True;
        m_bAfterLast	= sal_False;
        m_bRowCountFinal= sal_False;
        m_bNew			= sal_False;
        m_bModified		= sal_False;
        m_nRowCount		= 0;
        m_aOldRow		= NULL;
    }
}

// -------------------------------------------------------------------------
void ORowSet::setActiveConnection( Reference< XConnection >& _rxNewConn, sal_Bool _bFireEvent )
{
    if (_rxNewConn.get() == m_xActiveConnection.get())
        // nothing to do
        return;

    // remove the event listener for the old connection
    Reference< XComponent >  xComponent(m_xActiveConnection, UNO_QUERY);
    if (xComponent.is())
    {
        Reference<XEventListener> xListener;
        query_aggregation(this, xListener);
        xComponent->removeEventListener(xListener);
    }

    // if we owned the connection, remember it for later disposing
    if(m_bOwnConnection)
        m_xOldConnection = m_xActiveConnection;

    // for firing the PropertyChangeEvent
    sal_Int32 nHandle = PROPERTY_ID_ACTIVECONNECTION;
    Any aOldConnection; aOldConnection <<= m_xActiveConnection;
    Any aNewConnection; aNewConnection <<= _rxNewConn;

    // set the new connection
    m_xActiveConnection = _rxNewConn;
    if (m_xActiveConnection.is())
        m_aActiveConnection <<= m_xActiveConnection;
    else
        m_aActiveConnection.clear();

    // fire the event
    if (_bFireEvent)
        fire(&nHandle, &aNewConnection, &aOldConnection, 1, sal_False);

    // register as event listener for the new connection
    xComponent = Reference< XComponent >(m_xActiveConnection, UNO_QUERY);
    if (xComponent.is())
    {
        Reference<XEventListener> xListener;
        query_aggregation(this, xListener);
        xComponent->addEventListener(xListener);
    }
}

// -------------------------------------------------------------------------
// ::com::sun::star::XEventListener
void SAL_CALL ORowSet::disposing( const ::com::sun::star::lang::EventObject& Source ) throw(RuntimeException)
{
    // close rowset because the connection is going to be deleted (someone told me :-)
    Reference<XConnection> xCon(Source.Source,UNO_QUERY);
    if(m_xActiveConnection == xCon)
    {
        close();
        {
            MutexGuard aGuard( m_aMutex );
            Reference< XConnection > xXConnection; 
            setActiveConnection( xXConnection );
        }
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
        ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);
    }
    // additionals things to set
    m_bCreateStatement = sal_True;
    freeResources();
}
// -------------------------------------------------------------------------
// comphelper::OPropertyArrayUsageHelper
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
    typedef ::comphelper::OPropertyArrayUsageHelper<ORowSet> ORowSet_PROP;
    return *ORowSet_PROP::getArrayHelper();
}
// -----------------------------------------------------------------------------
void ORowSet::updateValue(sal_Int32 columnIndex,const ORowSetValue& x)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );
    checkUpdateConditions(columnIndex);
    checkUpdateIterator();

    ::connectivity::ORowSetValue aOldValue((*(*m_aCurrentRow))[columnIndex]);
    m_pCache->updateValue(columnIndex,x);
    // we have to notify all listeners
    (*(*m_aCurrentRow))[columnIndex] = x;
    firePropertyChange(columnIndex-1 ,aOldValue);
    fireProperty(PROPERTY_ID_ISMODIFIED,sal_True,sal_False);
}
// -------------------------------------------------------------------------
// XRowUpdate
void SAL_CALL ORowSet::updateNull( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,ORowSetValue());
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBoolean( sal_Int32 columnIndex, sal_Bool x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateByte( sal_Int32 columnIndex, sal_Int8 x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateShort( sal_Int32 columnIndex, sal_Int16 x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateInt( sal_Int32 columnIndex, sal_Int32 x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateLong( sal_Int32 columnIndex, sal_Int64 x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateFloat( sal_Int32 columnIndex, float x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateDouble( sal_Int32 columnIndex, double x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateString( sal_Int32 columnIndex, const ::rtl::OUString& x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBytes( sal_Int32 columnIndex, const Sequence< sal_Int8 >& x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateDate( sal_Int32 columnIndex, const ::com::sun::star::util::Date& x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateTime( sal_Int32 columnIndex, const ::com::sun::star::util::Time& x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateTimestamp( sal_Int32 columnIndex, const ::com::sun::star::util::DateTime& x ) throw(SQLException, RuntimeException)
{
    updateValue(columnIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateBinaryStream( sal_Int32 columnIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );

    checkUpdateConditions(columnIndex);

    checkUpdateIterator();
    ::connectivity::ORowSetValue aOldValue;
    if((*(*m_aCurrentRow))[columnIndex].getTypeKind() == DataType::BLOB)
    {
        m_pCache->updateBinaryStream(columnIndex,x,length);
        aOldValue = (*(*m_aCurrentRow))[columnIndex];
        (*(*m_aCurrentRow))[columnIndex] = makeAny(x);
    }
    else
    {
        Sequence<sal_Int8> aSeq;
        if(x.is())
            x->readSomeBytes(aSeq,length);
        updateValue(columnIndex,aSeq);
        aOldValue = (*(*m_aCurrentRow))[columnIndex];
        (*(*m_aCurrentRow))[columnIndex] = aSeq;
    }
    
    firePropertyChange(columnIndex-1 ,aOldValue);
    fireProperty(PROPERTY_ID_ISMODIFIED,sal_True,sal_False);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateCharacterStream( sal_Int32 columnIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );
    checkUpdateConditions(columnIndex);

    checkUpdateIterator();
    m_pCache->updateCharacterStream(columnIndex,x,length);

    ::connectivity::ORowSetValue aOldValue((*(*m_aCurrentRow))[columnIndex]);
    (*(*m_aCurrentRow))[columnIndex] = makeAny(x);
    firePropertyChange(columnIndex-1 ,aOldValue);
    fireProperty(PROPERTY_ID_ISMODIFIED,sal_True,sal_False);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateObject( sal_Int32 columnIndex, const Any& x ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );
    checkUpdateConditions(columnIndex);

    checkUpdateIterator();

    Any aNewValue = x;

    if ( m_pColumns )
    {
        Reference<XPropertySet> xColumn;
        m_pColumns->getByIndex(columnIndex-1) >>= xColumn;
        sal_Int32 nColType;
        xColumn->getPropertyValue(PROPERTY_TYPE) >>= nColType;
        switch( nColType )
        {
            case DataType::DATE:
            case DataType::TIME:
            case DataType::TIMESTAMP:
            {
                double nValue;
                if ( x >>= nValue )
                {
                    if ( DataType::TIMESTAMP == nColType ) 
                        aNewValue <<= dbtools::DBTypeConversion::toDateTime( nValue );
                    else if ( DataType::DATE == nColType ) 
                        aNewValue <<= dbtools::DBTypeConversion::toDate( nValue );
                    else
                        aNewValue <<= dbtools::DBTypeConversion::toTime( nValue );
                }
                break;
            }
        }
    }

    if (!::dbtools::implUpdateObject(this, columnIndex, aNewValue))
    {	// there is no other updateXXX call which can handle the value in x
        ::connectivity::ORowSetValue aOldValue((*(*m_aCurrentRow))[columnIndex]);
        m_pCache->updateObject(columnIndex,aNewValue);
        // we have to notify all listeners
        (*(*m_aCurrentRow))[columnIndex] = aNewValue;
        firePropertyChange(columnIndex-1 ,aOldValue);
        fireProperty(PROPERTY_ID_ISMODIFIED,sal_True,sal_False);
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateNumericObject( sal_Int32 columnIndex, const Any& x, sal_Int32 scale ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );
    checkUpdateConditions(columnIndex);

    checkUpdateIterator();
    ::connectivity::ORowSetValue aOldValue((*(*m_aCurrentRow))[columnIndex]);
    m_pCache->updateNumericObject(columnIndex,x,scale);
    // we have to notify all listeners
    (*(*m_aCurrentRow))[columnIndex] = x;
    firePropertyChange(columnIndex-1 ,aOldValue);
    fireProperty(PROPERTY_ID_ISMODIFIED,sal_True,sal_False);
}
// -------------------------------------------------------------------------

// XResultSetUpdate
void SAL_CALL ORowSet::insertRow(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);
    // insertRow is not allowd when 
    // standing not on the insert row nor 
    // when the row isn't modified
    // or the concurency is read only
    ::osl::ResettableMutexGuard aGuard( *m_pMutex );
    if(!m_pCache || !m_bNew || !m_bModified || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY)
        throwFunctionSequenceException(*this);

    if(m_bModified)
    {
        // remember old value for fire
        sal_Bool bOld = m_bNew;

        ORowSetRow aOldValues;
        if ( !m_aCurrentRow.isNull() )
            aOldValues = new ORowSetValueVector( m_aCurrentRow->getBody() );
        RowChangeEvent aEvt(*this,RowChangeAction::INSERT,1);
        if(notifyAllListenersRowBeforeChange(aGuard,aEvt))
        {
            ::osl::MutexGuard aCacheGuard( *m_pMutex);
            sal_Bool bInserted = m_pCache->insertRow();

            // notification order
            // - column values
            setCurrentRow(sal_False,aOldValues,aGuard); // we don't move here

            // make sure that our row is set to the new inserted row before clearing the inser flags in the cache
            m_pCache->resetInsertRow(bInserted);

            // - rowChanged
            notifyAllListenersRowChanged(aGuard,aEvt);

            // - IsModified
            if(!m_bModified)
                fireProperty(PROPERTY_ID_ISMODIFIED,sal_False,sal_True);
            OSL_ENSURE( !m_bModified, "ORowSet::insertRow: just updated, but _still_ modified?" );

            // - IsNew
            if(m_bNew != bOld)
                fireProperty(PROPERTY_ID_ISNEW,m_bNew,bOld);

            // - RowCount/IsRowCountFinal
            fireRowcount();
        }
    }
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL ORowSet::getRow(  ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aRowCountMutex );
    checkCache();

    // check if we are inserting a row
    return (m_pCache && ( m_pCache->m_bInserted || m_bModified )) ? 0 : ORowSetBase::getRow();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::updateRow(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);
    // not allowed when standing on insert row
    ::osl::ResettableMutexGuard aGuard( *m_pMutex );
    if(!m_pCache || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY || m_bNew)
        throwFunctionSequenceException(*this);

    if(m_bModified)
    {
        ORowSetRow aOldValues = new ORowSetValueVector( m_aCurrentRow->getBody() );

        RowChangeEvent aEvt(*this,RowChangeAction::UPDATE,1);
        if(notifyAllListenersRowBeforeChange(aGuard,aEvt))
        {
            m_pCache->updateRow(m_aCurrentRow.operator ->());
            m_aBookmark		= m_pCache->getBookmark();
            m_aCurrentRow	= m_pCache->m_aMatrixIter;
            m_aOldRow		= (*m_aCurrentRow);

            // notification order
            // - column values
            ORowSetBase::firePropertyChange(aOldValues);

            // - rowChanged
            notifyAllListenersRowChanged(aGuard,aEvt);

            // - IsModified
            if(!m_bModified)
                fireProperty(PROPERTY_ID_ISMODIFIED,sal_False,sal_True);
            OSL_ENSURE( !m_bModified, "ORowSet::updateRow: just updated, but _still_ modified?" );
        }
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::deleteRow(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::ResettableMutexGuard aGuard( *m_pMutex );
    // deleteRow is not allowed when: 
    // stands before the first row
    // after the last row
    // stands on the insert row
    // the concurrency is read only
    if(!m_pCache || m_bBeforeFirst || m_bAfterLast || m_bNew || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY)
        throwFunctionSequenceException(*this);
    

    // this call position the cache indirect 
    notifyClonesRowDelete(m_aBookmark);

    positionCache();

    ORowSetRow aOldValues = new ORowSetValueVector( m_pCache->m_aMatrixIter->getBody() );

    RowChangeEvent aEvt(*this,RowChangeAction::DELETE,1);
    if(notifyAllListenersRowBeforeChange(aGuard,aEvt))
    {
        m_nPosition = m_pCache->getRow();
        m_pCache->deleteRow();
        notifyClonesRowDeleted(m_aBookmark);

        m_aBookmark		= Any();
        m_aCurrentRow	= NULL;
        m_aCurrentRow.setBookmark(Any());

        ORowSetNotifier aNotifier( this );
            // this will call cancelRowModification on the cache if necessary

        // notification order
        // - rowChanged
        notifyAllListenersRowChanged(aGuard,aEvt);

        // - IsModified
        // - IsNew
        aNotifier.fire( );

        // - RowCount/IsRowCountFinal
        fireRowcount();
    }
}
// -------------------------------------------------------------------------
void ORowSet::implCancelRowUpdates( sal_Bool _bNotifyModified ) SAL_THROW( ( SQLException, RuntimeException ) )
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( *m_pMutex );
    if(m_bBeforeFirst || m_bAfterLast)
        return; // nothing to do so return

    // cancelRowUpdates is not allowed when: 
    // standing on the insert row
    // the concurrency is read only
    if(!m_pCache || m_bNew || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY)
        throwFunctionSequenceException(*this);

    positionCache();

    m_pCache->cancelRowUpdates();
    ORowSetRow aOldValues = new ORowSetValueVector( m_aCurrentRow->getBody() );

    m_aBookmark		= m_pCache->getBookmark();
    m_aCurrentRow	= m_pCache->m_aMatrixIter;
    m_aCurrentRow.setBookmark(m_aBookmark);

    // notification order
    // - column values
    ORowSetBase::firePropertyChange(aOldValues);
    // IsModified
    if( !m_bModified && _bNotifyModified )
        fireProperty(PROPERTY_ID_ISMODIFIED,sal_False,sal_True);
}

// -------------------------------------------------------------------------
void SAL_CALL ORowSet::cancelRowUpdates(  ) throw(SQLException, RuntimeException)
{
    implCancelRowUpdates( sal_True );
}

// -------------------------------------------------------------------------
void SAL_CALL ORowSet::addRowSetListener( const Reference< XRowSetListener >& listener ) throw(RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    if(listener.is())
        m_aRowsetListeners.addInterface(listener);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::removeRowSetListener( const Reference< XRowSetListener >& listener ) throw(RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    if(listener.is())
        m_aRowsetListeners.removeInterface(listener);
}
// -----------------------------------------------------------------------------
void ORowSet::notifyAllListeners(::osl::ResettableMutexGuard& _rGuard)
{
    EventObject aEvt(*m_pMySelf);
    NOTIFY_LISTERNERS(m_aRowsetListeners,XRowSetListener,rowSetChanged);
}
// -------------------------------------------------------------------------
void ORowSet::notifyAllListenersCursorMoved(::osl::ResettableMutexGuard& _rGuard)
{
    EventObject aEvt(*m_pMySelf);
    NOTIFY_LISTERNERS(m_aRowsetListeners,XRowSetListener,cursorMoved);
}
// -------------------------------------------------------------------------
void ORowSet::notifyAllListenersRowChanged(::osl::ResettableMutexGuard& _rGuard,const RowChangeEvent &aEvt)
{
    NOTIFY_LISTERNERS(m_aRowsetListeners,XRowSetListener,rowChanged);
}
// -------------------------------------------------------------------------
sal_Bool ORowSet::notifyAllListenersCursorBeforeMove(::osl::ResettableMutexGuard& _rGuard)
{
    EventObject aEvt(*m_pMySelf);
    NOTIFY_LISTERNERS_CHECK(m_aApproveListeners,XRowSetApproveListener,approveCursorMove);
    return bCheck;
}
// -------------------------------------------------------------------------
sal_Bool ORowSet::notifyAllListenersRowBeforeChange(::osl::ResettableMutexGuard& _rGuard,const RowChangeEvent &aEvt)
{
    NOTIFY_LISTERNERS_CHECK(m_aApproveListeners,XRowSetApproveListener,approveRowChange);
    return bCheck;
}
// -------------------------------------------------------------------------
void ORowSet::fireRowcount()
{
    if(m_nRowCount != m_pCache->m_nRowCount)
    {
        sal_Int32 nHandle = PROPERTY_ID_ROWCOUNT;
        Any aNew,aOld;
        aNew <<= m_pCache->m_nRowCount;aOld <<= m_nRowCount;
        fire(&nHandle,&aNew,&aOld,1,sal_False);
        m_nRowCount = m_pCache->m_nRowCount;
    }
    if(!m_bRowCountFinal && m_bRowCountFinal != m_pCache->m_bRowCountFinal)
    {
        sal_Int32 nHandle = PROPERTY_ID_ISROWCOUNTFINAL;
        Any aNew,aOld;
        aNew <<= bool2any(m_pCache->m_bRowCountFinal);
        aOld <<= bool2any(m_bRowCountFinal);
        fire(&nHandle,&aNew,&aOld,1,sal_False);
        m_bRowCountFinal = m_pCache->m_bRowCountFinal;
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::moveToInsertRow(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::ResettableMutexGuard aGuard( *m_pMutex );
    checkPositioningAllowed();

    if(notifyAllListenersCursorBeforeMove(aGuard))
    {
        // remember old value for fire
        // check before because the resultset could be empty
        if(m_aBookmark.hasValue())
            positionCache();

        ORowSetRow aOldValues;
        if ( !m_bBeforeFirst && !m_bAfterLast && m_pCache->m_aMatrixIter != m_pCache->getEnd() && m_pCache->m_aMatrixIter->isValid() )
            aOldValues = new ORowSetValueVector( m_pCache->m_aMatrixIter->getBody() );

        const sal_Bool bNewState = m_bNew;
        const sal_Bool bModState = m_bModified;

        m_pCache->moveToInsertRow();
        m_aCurrentRow = m_pCache->m_aInsertRow;

        // notification order
        // - column values
        ORowSetBase::firePropertyChange(aOldValues);

        // - cursorMoved
        notifyAllListenersCursorMoved(aGuard);

        // - IsModified
        if ( bModState != m_bModified )
            fireProperty( PROPERTY_ID_ISMODIFIED, m_bModified, bModState );

        // - IsNew
        if ( bNewState != m_bNew )
            fireProperty( PROPERTY_ID_ISNEW, m_bNew, bNewState );
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::moveToCurrentRow(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::ResettableMutexGuard aGuard( *m_pMutex );

    checkPositioningAllowed();

    if(m_pCache && ( m_pCache->m_bInserted || m_bModified ))
    {
        if(notifyAllListenersCursorBeforeMove(aGuard))
        {
            positionCache();
            m_pCache->moveToCurrentRow();

            ORowSetNotifier aNotifier( this );
                // this will call cancelRowModification on the cache if necessary

            // notification order
            // - cursorMoved
            notifyAllListenersCursorMoved(aGuard);

            // - IsModified
            // - IsNew
            aNotifier.fire();
        }
    }
}
// -------------------------------------------------------------------------
// XRow
sal_Bool SAL_CALL ORowSet::wasNull(  ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return ( m_pCache && ( m_pCache->m_bInserted || m_bModified ) ) ? (*(*m_pCache->m_aInsertRow))[m_nLastColumnIndex].isNull() : ORowSetBase::wasNull();
}
// -----------------------------------------------------------------------------
const ORowSetValue& ORowSet::getInsertValue(sal_Int32 columnIndex)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    if ( m_pCache && ( m_pCache->m_bInserted || m_bModified) )
        return 	(*(*m_pCache->m_aInsertRow))[m_nLastColumnIndex = columnIndex];

    OSL_ENSURE(m_pCache->m_aInsertRow != m_aCurrentRow,"Current row stand on the insert row but all flags are wrong!");
    return getValue(columnIndex);
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL ORowSet::getString( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL ORowSet::getBoolean( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int8 SAL_CALL ORowSet::getByte( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int16 SAL_CALL ORowSet::getShort( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL ORowSet::getInt( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int64 SAL_CALL ORowSet::getLong( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
float SAL_CALL ORowSet::getFloat( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
double SAL_CALL ORowSet::getDouble( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL ORowSet::getBytes( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::Date SAL_CALL ORowSet::getDate( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::Time SAL_CALL ORowSet::getTime( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::DateTime SAL_CALL ORowSet::getTimestamp( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return getInsertValue(columnIndex);
}
// -------------------------------------------------------------------------
Reference< ::com::sun::star::io::XInputStream > SAL_CALL ORowSet::getBinaryStream( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    if(m_pCache && ( m_pCache->m_bInserted || m_bModified ))
    {
        checkCache();
        return new ::comphelper::SequenceInputStream((*(*m_pCache->m_aInsertRow))[m_nLastColumnIndex = columnIndex].getSequence());
    }

    return ORowSetBase::getBinaryStream(columnIndex);
}
// -------------------------------------------------------------------------
Reference< ::com::sun::star::io::XInputStream > SAL_CALL ORowSet::getCharacterStream( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    if(m_pCache && ( m_pCache->m_bInserted || m_bModified ))
    {
        checkCache();
        return new ::comphelper::SequenceInputStream((*(*m_pCache->m_aInsertRow))[m_nLastColumnIndex = columnIndex].getSequence());
    }

    return ORowSetBase::getCharacterStream(columnIndex);
}
// -------------------------------------------------------------------------
Any SAL_CALL ORowSet::getObject( sal_Int32 columnIndex, const Reference< XNameAccess >& typeMap ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return Any();
}
// -------------------------------------------------------------------------
Reference< XRef > SAL_CALL ORowSet::getRef( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return Reference< XRef >();
}
// -------------------------------------------------------------------------
Reference< XBlob > SAL_CALL ORowSet::getBlob( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return Reference< XBlob >();
}
// -------------------------------------------------------------------------
Reference< XClob > SAL_CALL ORowSet::getClob( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return Reference< XClob >();
}
// -------------------------------------------------------------------------
Reference< XArray > SAL_CALL ORowSet::getArray( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( *m_pMutex );
    checkCache();

    return Reference< XArray >();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::executeWithCompletion( const Reference< XInteractionHandler >& _rxHandler ) throw(SQLException, RuntimeException)
{
    if (!_rxHandler.is())
        execute();

    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    // tell everybody that we will change the result set
    approveExecution();

    ResettableMutexGuard aGuard( m_aMutex );
    
    // create and fill a composer
    Reference<XSQLQueryComposer>  xComposer = getCurrentSettingsComposer(this, m_xServiceManager);

    // we have to set this here again because getCurrentSettingsComposer can force a setpropertyvalue

    // OJ: why? When the ActiveConnection is set again, m_bOwnConnection should be true
    //	m_bOwnConnection = sal_True;
    try
    {
        freeResources();

        // calc the connection to be used
        if (m_xActiveConnection.is() && m_bRebuildConnOnExecute) {
            // there was a setProperty(ActiveConnection), but a setProperty(DataSource) _after_ that, too
            Reference< XConnection > xXConnection;
            setActiveConnection( xXConnection );
        }
        calcConnection(_rxHandler);
        m_bRebuildConnOnExecute = sal_False;
        ::dbtools::askForParameters(xComposer,this,m_xActiveConnection,_rxHandler);
    }
    // ensure that only the allowed exceptions leave this block
    catch(SQLException&)
    {
        throw;
    }
    catch(RuntimeException&)
    {
        throw;
    }
    catch(Exception&)
    {
        DBG_ERROR("ORowSet::executeWithCompletion: caught an unexpected exception type while filling in the parameters!");
    }
    
    // we're done with the parameters, now for the real execution

    //  do the real execute
    execute_NoApprove_NoNewConn(aGuard);
}
// -------------------------------------------------------------------------
void ORowSet::approveExecution() throw (RowSetVetoException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    EventObject aEvt(*this);
    OInterfaceIteratorHelper aApproveIter(m_aApproveListeners);
    while (aApproveIter.hasMoreElements())
    {
        if (!((XRowSetApproveListener*)aApproveIter.next())->approveRowSetChange(aEvt))
            throw RowSetVetoException();
    }
}
// -------------------------------------------------------------------------
// XRowSet
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::execute(  ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    // tell everybody that we will change the result set
    approveExecution();

    ResettableMutexGuard aGuard( m_aMutex );
    freeResources();

    // calc the connection to be used
    if (m_xActiveConnection.is() && m_bRebuildConnOnExecute) {
        // there was a setProperty(ActiveConnection), but a setProperty(DataSource) _after_ that, too
        Reference< XConnection> xXConnection;
        setActiveConnection( xXConnection );
    }

    calcConnection(NULL);
    m_bRebuildConnOnExecute = sal_False;

    // do the real execute
    execute_NoApprove_NoNewConn(aGuard);

}
// -----------------------------------------------------------------------------
// XRowSet
void ORowSet::execute_NoApprove_NoNewConn(ResettableMutexGuard& _rClearForNotification)
{
    // now we can dispose our old connection
    ::comphelper::disposeComponent(m_xOldConnection);
    m_xOldConnection = NULL;

    ::rtl::OUString aSql;
    // do we need a new statement
    if (m_bCreateStatement)
    {
        m_xStatement	= NULL;
        m_xComposer		= NULL;

        // Build the statement
        sal_Bool bUseEscapeProcessing;
        Reference< ::com::sun::star::container::XNameAccess > xTables;
        // xTables will be filled in getCommand
        m_aActiveCommand = getCommand(bUseEscapeProcessing,xTables);
        if (!m_aActiveCommand.getLength())
            throwGenericSQLException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Empty command submitted!")),*this);

        {
            m_xStatement = m_xActiveConnection->prepareStatement(
                                        aSql = getComposedQuery(m_aActiveCommand, bUseEscapeProcessing,xTables));
        
            if(m_xStatement.is())
            {
                Reference<XPropertySet> xProp(m_xStatement,UNO_QUERY);
                
                try
                {
                    xProp->setPropertyValue(PROPERTY_USEBOOKMARKS,makeAny(sal_True));
                    xProp->setPropertyValue(PROPERTY_RESULTSETTYPE,makeAny(ResultSetType::SCROLL_SENSITIVE));
                    xProp->setPropertyValue(PROPERTY_RESULTSETCONCURRENCY,makeAny(ResultSetConcurrency::UPDATABLE));
                    
                }
                catch(Exception&)
                {
                    // this exception doesn't matter here because when we catch an exception 
                    // than the driver doesn't support this feature
                }
                //	xProp->setPropertyValue(PROPERTY_RESULTSETTYPE,makeAny(m_nResultSetType));
                //	xProp->setPropertyValue(PROPERTY_RESULTSETCONCURRENCY,makeAny(m_nResultSetConcurrency));
                //	if(m_nFetchDirection != FetchDirection::FORWARD)
                    //	xProp->setPropertyValue(PROPERTY_FETCHDIRECTION,makeAny((sal_Int32)m_nFetchDirection));

                {
                    Reference<XParameters> xParam(m_xStatement,UNO_QUERY);
                    sal_Int32 i = 1;
                    for(ORowVector< ORowSetValue >::const_iterator aIter = m_aParameterRow.begin(); aIter != m_aParameterRow.end();++aIter,++i)
                    {
                        ::dbtools::setObjectWithInfo(xParam,i,aIter->makeAny(),aIter->getTypeKind());
                    }
                    
                    Reference< XResultSet> xRs = m_xStatement->executeQuery();
                    // create the composed table name
                    ::rtl::OUString aComposedTableName;
                    if(m_aUpdateTableName.getLength())
                        composeTableName(m_xActiveConnection->getMetaData(),m_aUpdateCatalogName,m_aUpdateSchemaName,m_aUpdateTableName,aComposedTableName,sal_False,::dbtools::eInDataManipulation);

                    m_pCache = new ORowSetCache(xRs,m_xComposer,m_xServiceManager,m_aParameterRow,aComposedTableName,m_bModified,m_bNew);
                    m_pCache->setMaxRowSize(m_nFetchSize);
                    m_aCurrentRow	= m_pCache->createIterator();
                    // now we can clear the parameter row
                    m_aParameterRow.clear();

                    // get the locale
                    ConfigManager*	pConfigMgr = ConfigManager::GetConfigManager();
                    Locale aLocale;
                    pConfigMgr->GetDirectConfigProperty(ConfigManager::LOCALE) >>= aLocale;

                    // get the numberformatTypes
                    OSL_ENSURE(m_xActiveConnection.is(),"No ActiveConnection");
                    Reference< XNumberFormatTypes> xNumberFormatTypes;
                    Reference< XChild> xChild(m_xActiveConnection,UNO_QUERY);
                    if(xChild.is())
                    {
                        Reference< XPropertySet> xProp(xChild->getParent(),UNO_QUERY);
                        if(xProp.is())
                        {
                            Reference< XNumberFormatsSupplier> xNumberFormat;
                            ::cppu::extractInterface(xNumberFormat,xProp->getPropertyValue(PROPERTY_NUMBERFORMATSSUPPLIER));
                            if(xNumberFormat.is())
                                m_xNumberFormatTypes = Reference< XNumberFormatTypes>(xNumberFormat->getNumberFormats(),UNO_QUERY);
                        }
                    }

                    ::vos::ORef< ::connectivity::OSQLColumns> aColumns = new ::connectivity::OSQLColumns();	
                    ::std::vector< ::rtl::OUString> aNames;
                    ::rtl::OUString aDescription;
                    sal_Int32 nFormatKey = 0;

                    if(!m_xColumns.is())
                    {
                        // use the meta data
                        Reference<XResultSetMetaDataSupplier> xMetaSup(m_xStatement,UNO_QUERY); 
                        Reference<XResultSetMetaData> xMetaData = xMetaSup->getMetaData();
                        
                        
                        try
                        {
                            sal_Int32 nCount = xMetaData->getColumnCount();
                            m_aDataColumns.reserve(nCount+1);
                            aColumns->reserve(nCount+1);
                            DECLARE_STL_USTRINGACCESS_MAP(int,StringMap);
                            StringMap aColumnMap;
                            for (sal_Int32 i = 0 ; i < nCount; ++i)
                            {
                                // retrieve the name of the column
                                ::rtl::OUString sName = xMetaData->getColumnName(i + 1);
                                // check for duplicate entries
                                if(aColumnMap.find(sName) != aColumnMap.end())
                                {
                                    ::rtl::OUString sAlias(sName);
                                    sal_Int32 i=1;
                                    while(aColumnMap.find(sAlias) != aColumnMap.end())
                                    {
                                        (sAlias = sName) += ::rtl::OUString::valueOf(i++);
                                    }
                                    sName = sAlias;
                                }
                                ORowSetDataColumn* pColumn = new ORowSetDataColumn(	getMetaData(),
                                                                                    this,
                                                                                    this,
                                                                                    i+1,
                                                                                    aDescription,
                                                                                    m_aCurrentRow,
                                                                                    m_pCache->getEnd());
                                aColumnMap.insert(StringMap::value_type(sName,0));
                                aColumns->push_back(pColumn);
                                pColumn->setName(sName);
                                aNames.push_back(sName);
                                m_aDataColumns.push_back(pColumn);

                                try
                                {
                                    nFormatKey = 0;
                                    if(m_xNumberFormatTypes.is())
                                        nFormatKey = ::dbtools::getDefaultNumberFormat(pColumn,m_xNumberFormatTypes,aLocale);
                                    
                                    
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_NUMBERFORMAT,makeAny(nFormatKey));
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_RELATIVEPOSITION,makeAny(sal_Int32(i+1)));
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_WIDTH,makeAny(sal_Int32(227)));
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_ALIGN,makeAny((sal_Int32)0));
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HIDDEN,::cppu::bool2any(sal_False));
                                }
                                catch(Exception&)
                                {
                                }
                            }
                        }
                        catch (SQLException&)
                        {
                        }
                    }
                    else
                    {
                        // create the rowset columns
                        Reference<XResultSetMetaData> xMeta = getMetaData();
                        sal_Int32 nCount = xMeta->getColumnCount();
                        m_aDataColumns.reserve(nCount+1);
                        aColumns->reserve(nCount+1);
                        ::std::map<Reference<XPropertySet>,int> aColumnMap; // need to find duplicates

                        for(sal_Int32 i=1; i <= nCount ;++i)
                        {
                            sal_Bool bReFetchName = sal_False;
                            ::rtl::OUString sName = xMeta->getColumnName(i);
                            Reference<XPropertySet> xColumn;
                            if (m_xColumns->hasByName(sName))
                                m_xColumns->getByName(sName) >>= xColumn;
                            if (!xColumn.is() && m_xColumns->hasByName(xMeta->getColumnLabel(i)))
                                m_xColumns->getByName(xMeta->getColumnLabel(i)) >>= xColumn;
                            // check if column already in the list we need another
                            if(aColumnMap.find(xColumn) != aColumnMap.end())
                            {
                                xColumn = NULL; 
                                bReFetchName = sal_True;
                            }
                            if(!xColumn.is())
                            {
                                // no column found so we could look at the position i
                                Reference<XIndexAccess> xIndexAccess(m_xColumns,UNO_QUERY);
                                if(xIndexAccess.is() && i <= xIndexAccess->getCount())
                                {
                                    xIndexAccess->getByIndex(i-1) >>= xColumn;
                                }
                                else
                                {
                                    Sequence< ::rtl::OUString> aSeq = m_xColumns->getElementNames();
                                    if( i <= aSeq.getLength())
                                        m_xColumns->getByName(aSeq.getConstArray()[i-1]) >>= xColumn;
                                }
                            }
                            DBG_ASSERT(xColumn.is(), "ORowSet::execute_NoApprove_NoNewConn: invalid column (NULL)!");
                            if(bReFetchName && xColumn.is())
                                xColumn->getPropertyValue(PROPERTY_NAME) >>= sName;
                            aColumnMap.insert(::std::map< Reference<XPropertySet>,int>::value_type(xColumn,0));

                            Reference<XPropertySetInfo> xInfo = xColumn.is() ? xColumn->getPropertySetInfo() : Reference<XPropertySetInfo>();
                            if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_DESCRIPTION))
                                aDescription = comphelper::getString(xColumn->getPropertyValue(PROPERTY_DESCRIPTION));

                            ORowSetDataColumn* pColumn = new ORowSetDataColumn(	getMetaData(),
                                                                                this,
                                                                                this,
                                                                                i,
                                                                                aDescription,
                                                                                m_aCurrentRow,
                                                                                m_pCache->getEnd());
                            aColumns->push_back(pColumn);
                            if(!sName.getLength())
                            {
                                if(xColumn.is())
                                    xColumn->getPropertyValue(PROPERTY_NAME) >>= sName;
                                else
                                    sName = ::rtl::OUString::createFromAscii("Expression1");
                            }
                            pColumn->setName(sName);
                            aNames.push_back(sName);
                            m_aDataColumns.push_back(pColumn);

                            try
                            {
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_ALIGN))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_ALIGN,xColumn->getPropertyValue(PROPERTY_ALIGN));

                                nFormatKey = 0;
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_NUMBERFORMAT))
                                    nFormatKey = comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_NUMBERFORMAT));
                                if (!nFormatKey && xColumn.is() && m_xNumberFormatTypes.is())
                                    nFormatKey = ::dbtools::getDefaultNumberFormat(xColumn,m_xNumberFormatTypes,aLocale);
                                
                                pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_NUMBERFORMAT,makeAny(nFormatKey));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_RELATIVEPOSITION))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_RELATIVEPOSITION,xColumn->getPropertyValue(PROPERTY_RELATIVEPOSITION));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_WIDTH))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_WIDTH,xColumn->getPropertyValue(PROPERTY_WIDTH));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_HIDDEN))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HIDDEN,xColumn->getPropertyValue(PROPERTY_HIDDEN));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_CONTROLMODEL))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLMODEL,xColumn->getPropertyValue(PROPERTY_CONTROLMODEL));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_HELPTEXT))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HELPTEXT,xColumn->getPropertyValue(PROPERTY_HELPTEXT));
                                if(xInfo.is() && xInfo->hasPropertyByName(PROPERTY_CONTROLDEFAULT))
                                    pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLDEFAULT,xColumn->getPropertyValue(PROPERTY_CONTROLDEFAULT));
                            }
                            catch(Exception&)
                            {
                            }
                        }
                    }
                    // now create the columns we need
                    if(m_pColumns)
                        m_pColumns->assign(aColumns,aNames);
                    else
                        m_pColumns = new ORowSetDataColumns(m_xActiveConnection->getMetaData()->supportsMixedCaseQuotedIdentifiers(),
                                                            aColumns,*this,m_aColumnsMutex,aNames);
                }
            }
            else
            {
                ::rtl::OUString sErrorMsg(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("The command '")));
                sErrorMsg += aSql;
                sErrorMsg += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("' does not succeed."));
                throwGenericSQLException(sErrorMsg,*this);
            }
        }
    }
    checkCache();
    _rClearForNotification.clear();
    // notify the rowset listeners
    notifyAllListeners(_rClearForNotification);
}
// -------------------------------------------------------------------------
// XRowSetApproveBroadcaster
void SAL_CALL ORowSet::addRowSetApproveListener( const Reference< XRowSetApproveListener >& listener ) throw(RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );

    m_aApproveListeners.addInterface(listener);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::removeRowSetApproveListener( const Reference< XRowSetApproveListener >& listener ) throw(RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

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
        ORowSetClone* pClone = new ORowSetClone(*this,m_pMutex);
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
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    if(m_pCache)
        m_pCache->cancel();
}
// -------------------------------------------------------------------------

// ::com::sun::star::sdbcx::XDeleteRows
Sequence< sal_Int32 > SAL_CALL ORowSet::deleteRows( const Sequence< Any >& rows ) throw(SQLException, RuntimeException)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    if(!m_pCache || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY)
        throwFunctionSequenceException(*this);

    ::osl::ResettableMutexGuard aGuard( *m_pMutex );

    Sequence< sal_Int32 > aRet;
    RowChangeEvent aEvt(*this,RowChangeAction::DELETE,rows.getLength());
    // notify the rowset listeners
    if(notifyAllListenersRowBeforeChange(aGuard,aEvt))
    {
        // first notify the clones so that they can save their position
        const Any* pBegin = rows.getConstArray();
        const Any* pEnd   = pBegin + rows.getLength();
        for(;pBegin != pEnd;++pBegin)
        {
            notifyClonesRowDelete(*pBegin);
            if(compareBookmarks( m_aBookmark,*pBegin) == 0)
            {
                positionCache();
                m_nPosition = m_pCache->getRow();
            }
        }
        // now delete the rows
        aRet = m_pCache->deleteRows(rows);

        // now notify that we have deleted
        pBegin = rows.getConstArray();

        const sal_Int32* pRetBegin	= aRet.getConstArray();
        const sal_Int32* pRetEnd	= pRetBegin + aRet.getLength();
        OSL_ENSURE(aRet.getLength() == rows.getLength(),"ORowSet::deleteRows: The length of the rows and returnstatus is not equal!");
        for(;pBegin != pEnd;++pBegin)
        {
            if(*pRetBegin)
            {
                notifyClonesRowDeleted(*pBegin);
                if(compareBookmarks( m_aBookmark,*pBegin) == 0)
                {
                    m_aOldRow		= NULL;
                    m_aCurrentRow	= m_pCache->getEnd();
                    m_aBookmark		= Any();
                    m_aCurrentRow.setBookmark(m_aBookmark);	
                }
            }
        }

        aEvt.Rows = aRet.getLength();

        // we have to check if we stand on the insert row and if so we have to reset it
        ORowSetNotifier aNotifier( this );
            // this will call cancelRowModification on the cache if necessary

        // notification order
        // - rowChanged
        notifyAllListenersRowChanged(aGuard,aEvt);

        // - IsModified
        // - IsNew
        aNotifier.fire();

        // - RowCount/IsRowCountFinal
        fireRowcount();
    }
    return aRet;
}
// -----------------------------------------------------------------------------
void ORowSet::notifyClonesRowDelete(const Any& _rBookmark)
{
    for (connectivity::OWeakRefArray::iterator i = m_aClones.begin(); m_aClones.end() != i; i++)
    {
        Reference< XUnoTunnel > xTunnel(i->get(),UNO_QUERY);
        if(xTunnel.is())
        {
            ORowSetClone* pClone = (ORowSetClone*)xTunnel->getSomething(ORowSetClone::getUnoTunnelImplementationId());
            if(pClone)		  
                pClone->rowDelete(_rBookmark);
        }
    }
}
//------------------------------------------------------------------------------
void ORowSet::notifyClonesRowDeleted(const Any& _rBookmark)
{
    for (connectivity::OWeakRefArray::iterator i = m_aClones.begin(); m_aClones.end() != i; i++)
    {
        Reference< XUnoTunnel > xTunnel(i->get(),UNO_QUERY);
        if(xTunnel.is())
        {
            ORowSetClone* pClone = (ORowSetClone*)xTunnel->getSomething(ORowSetClone::getUnoTunnelImplementationId());
            if(pClone)		  
                pClone->rowDeleted(_rBookmark);
        }
    }
}
//------------------------------------------------------------------------------
Reference< XConnection >  ORowSet::calcConnection(const Reference< XInteractionHandler >& _rxHandler) throw( SQLException, RuntimeException )
{
    MutexGuard aGuard(m_aMutex);
    if (!m_xActiveConnection.is())
    {
        Reference< XConnection > xNewConn;
        if (m_aDataSourceName.getLength())
        {
            // is it a file url?
            Reference< ::com::sun::star::container::XNameAccess >  xNamingContext(m_xServiceManager->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
            if (xNamingContext.is() && xNamingContext->hasByName(m_aDataSourceName))
            {
                try
                {
                    if(_rxHandler.is())
                    {
                        Reference< XCompletedConnection> xComplConn(Reference< XNamingService > (xNamingContext, UNO_QUERY)->getRegisteredObject(m_aDataSourceName), UNO_QUERY);
                        if(xComplConn.is())
                            xNewConn = xComplConn->connectWithCompletion(_rxHandler);
                    }
                    else
                    {
                        Reference< XDataSource >  xDataSource(Reference< XNamingService > (xNamingContext, UNO_QUERY)->getRegisteredObject(m_aDataSourceName), UNO_QUERY);
                        if (xDataSource.is())
                            xNewConn = xDataSource->getConnection(m_aUser, m_aPassword);
                    }
                }
                catch (SQLException &e)
                {
                    throw e;
                }
                catch (Exception&)
                {
                    throw SQLException();
                }
            }
        }
        setActiveConnection(xNewConn);
        m_bOwnConnection = sal_True;
    }
    return m_xActiveConnection;
}
//------------------------------------------------------------------------------
rtl::OUString ORowSet::getCommand(sal_Bool& bEscapeProcessing,::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxRetTables)  throw( SQLException)
{
    // create the sql command
    // from a table name or get the command out of a query (not a view)
    // the last use the command as it is
    bEscapeProcessing = m_bUseEscapeProcessing;
    rtl::OUString aQuery;
    if (m_aCommand.getLength())
    {
        // i always need a tables for the querycomposer
        Reference< XTablesSupplier >  xTablesAccess(m_xActiveConnection, UNO_QUERY);
        if (xTablesAccess.is())
        {
            _rxRetTables = xTablesAccess->getTables();
        }
        else // the connection is no table supplier so I make it myself
        {
            if(!m_xActiveConnection.is())
                throw SQLException(DBACORE_RESSTRING(RID_STR_CONNECTION_INVALID),*this,SQLSTATE_GENERAL,1000,Any() );
            sal_Bool bCase = sal_True;
            try
            {
                bCase = m_xActiveConnection->getMetaData()->storesMixedCaseQuotedIdentifiers();
            }
            catch(SQLException&)
            {
            }
            m_pTables = new OTableContainer(OConfigurationNode(),OConfigurationTreeRoot(),*this,m_aMutex,m_xActiveConnection,bCase);
            _rxRetTables = m_pTables;
            Sequence< ::rtl::OUString> aTableFilter(1);
            aTableFilter[0] = ::rtl::OUString::createFromAscii("%");
            m_pTables->construct(aTableFilter,Sequence< ::rtl::OUString>());
        }
        switch (m_nCommandType)
        {
            case CommandType::TABLE:
            {
                OSL_ENSURE(_rxRetTables.is(),"ORowSet::getCommand: We got no tables from the connection!");
                if ( _rxRetTables.is() && _rxRetTables->hasByName(m_aCommand) )
                {
                    Reference< XPropertySet > xTable;
                    ::cppu::extractInterface(xTable,_rxRetTables->getByName(m_aCommand));

                    Reference<XColumnsSupplier> xSup(xTable,UNO_QUERY);
                    if ( xSup.is() )
                        m_xColumns = xSup->getColumns();

                    aQuery = rtl::OUString::createFromAscii("SELECT * FROM ");
                    aQuery += ::dbtools::quoteTableName(m_xActiveConnection->getMetaData(), m_aCommand,::dbtools::eInDataManipulation);
                }
                else
                {
                    ::rtl::OUString sError(RTL_CONSTASCII_USTRINGPARAM("There exists no table with given name: \""));
                    sError += m_aCommand;
                    sError += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\"!"));
                    throwGenericSQLException(sError,*this);
                }
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
                        ::cppu::extractInterface(xQuery,xQueries->getByName(m_aCommand));
                        xQuery->getPropertyValue(PROPERTY_COMMAND) >>= aQuery;
                        bEscapeProcessing = any2bool(xQuery->getPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING));

                        ::rtl::OUString aCatalog,aSchema,aTable;
                        xQuery->getPropertyValue(PROPERTY_UPDATE_CATALOGNAME)	>>= aCatalog;
                        xQuery->getPropertyValue(PROPERTY_UPDATE_SCHEMANAME)	>>= aSchema;
                        xQuery->getPropertyValue(PROPERTY_UPDATE_TABLENAME)		>>= aTable;
                        if(aTable.getLength())
                            composeTableName(m_xActiveConnection->getMetaData(),aCatalog,aSchema,aTable,m_aUpdateTableName,sal_False,::dbtools::eInDataManipulation);

                        Reference<XColumnsSupplier> xSup(xQuery,UNO_QUERY);
                        if(xSup.is())
                            m_xColumns = xSup->getColumns();
                    }
                    else
                    {
                        ::rtl::OUString sError(RTL_CONSTASCII_USTRINGPARAM("There exists no query with given name: \""));
                        sError += m_aCommand;
                        sError += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\"!"));
                        throwGenericSQLException(sError,*this);
                    }
                }
                else
                    throw SQLException(::rtl::OUString::createFromAscii("The interface XQueriesSupplier is not available!"),*this,::rtl::OUString(),0,Any());
            }	break;
            default:
                aQuery = m_aCommand;
        }
    }
    return aQuery;
}
//------------------------------------------------------------------------------
rtl::OUString ORowSet::getComposedQuery(const rtl::OUString& rQuery, sal_Bool bEscapeProcessing,::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxRetTables) throw( SQLException, RuntimeException )
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
            }
            catch (Exception&)
            {
                m_xComposer = NULL;
            }
        }
        if(!m_xComposer.is()) // no composer so we create one
        {
            OQueryComposer* pComposer = new OQueryComposer(_rxRetTables,m_xActiveConnection,m_xServiceManager);
            m_xComposer = pComposer;
        }
        if(m_xComposer.is())
        {
            m_xComposer->setQuery(rQuery);

            if(m_bIgnoreResult)
                m_xComposer->setFilter(::rtl::OUString::createFromAscii("0=1"));
            else if (m_aFilter.getLength() && m_bApplyFilter)
                m_xComposer->setFilter(m_aFilter);

            if (m_aOrder.getLength())
                m_xComposer->setOrder(m_aOrder);
            
            aFilterStatement = m_xComposer->getComposedQuery();
            if(!m_xColumns.is())
            {
                Reference<XColumnsSupplier> xCols(m_xComposer,UNO_QUERY);
                m_xColumns = xCols->getColumns();
            }
        }
    }
    return aFilterStatement;
}
// -----------------------------------------------------------------------------
void ORowSet::checkAndResizeParameters(sal_Int32 parameterIndex)
{
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);
    if (parameterIndex < 1)
        throwInvalidIndexException(*this);
    else if ((sal_Int32)m_aParameterRow.size() < parameterIndex)
        m_aParameterRow.resize(parameterIndex);
}
// -------------------------------------------------------------------------
// XParameters
void SAL_CALL ORowSet::setNull( sal_Int32 parameterIndex, sal_Int32 sqlType ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);

    m_aParameterRow[parameterIndex-1].setNull();
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObjectNull( sal_Int32 parameterIndex, sal_Int32 sqlType, const ::rtl::OUString& typeName ) throw(SQLException, RuntimeException)
{
    
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
    m_aParameterRow[parameterIndex-1].setNull();
}
// -----------------------------------------------------------------------------
void ORowSet::setParameter(sal_Int32 parameterIndex, const ORowSetValue& x)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
    
    m_aParameterRow[parameterIndex-1] = x;
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBoolean( sal_Int32 parameterIndex, sal_Bool x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setByte( sal_Int32 parameterIndex, sal_Int8 x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setShort( sal_Int32 parameterIndex, sal_Int16 x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setInt( sal_Int32 parameterIndex, sal_Int32 x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setLong( sal_Int32 parameterIndex, sal_Int64 x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setFloat( sal_Int32 parameterIndex, float x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setDouble( sal_Int32 parameterIndex, double x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setString( sal_Int32 parameterIndex, const ::rtl::OUString& x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBytes( sal_Int32 parameterIndex, const Sequence< sal_Int8 >& x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setDate( sal_Int32 parameterIndex, const ::com::sun::star::util::Date& x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setTime( sal_Int32 parameterIndex, const ::com::sun::star::util::Time& x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setTimestamp( sal_Int32 parameterIndex, const ::com::sun::star::util::DateTime& x ) throw(SQLException, RuntimeException)
{
    setParameter(parameterIndex,x);
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setBinaryStream( sal_Int32 parameterIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
    try
    {
        Sequence <sal_Int8> aData;
        x->readBytes(aData, length);
        m_aParameterRow[parameterIndex-1] = aData;
        x->closeInput();
    }
    catch( Exception& )
    {
        throw SQLException();
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setCharacterStream( sal_Int32 parameterIndex, const Reference< ::com::sun::star::io::XInputStream >& x, sal_Int32 length ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
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
    catch( Exception& )
    {
        throw SQLException();
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObject( sal_Int32 parameterIndex, const Any& x ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
    if (!::dbtools::implSetObject(this, parameterIndex, x))
    {	// there is no other setXXX call which can handle the value in x
        throw SQLException();		
    }
}
// -------------------------------------------------------------------------
void SAL_CALL ORowSet::setObjectWithInfo( sal_Int32 parameterIndex, const Any& x, sal_Int32 targetSqlType, sal_Int32 scale ) throw(SQLException, RuntimeException)
{
    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    checkAndResizeParameters(parameterIndex);
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
    ::connectivity::checkDisposed(ORowSet_BASE1::rBHelper.bDisposed);

    ::osl::MutexGuard aGuard( m_aColumnsMutex );
    // this is the real clear
    m_aParameterRow = connectivity::ORowVector< ORowSetValue >();
    m_aParameterRow.clear();
}
// -------------------------------------------------------------------------
void ORowSet::firePropertyChange(sal_Int32 _nPos,const ::connectivity::ORowSetValue& _rOldValue)
{
    OSL_ENSURE(_nPos < (sal_Int32)m_aDataColumns.size(),"nPos is invalid!");
    m_aDataColumns[_nPos]->fireValueChange(_rOldValue);
}

// -----------------------------------------------------------------------------
void ORowSet::doCancelModification( )
{
    OSL_ENSURE( isModification(), "ORowSet::doCancelModification: invalid call (no cache!)!" );
    if ( isModification() )
        m_pCache->cancelRowModification();
}

// -----------------------------------------------------------------------------
sal_Bool ORowSet::isModification( )
{
    return m_pCache && m_pCache->m_bInserted;
}

// -----------------------------------------------------------------------------
sal_Bool ORowSet::isModified( )
{
    return m_bModified;
}

// -----------------------------------------------------------------------------
sal_Bool ORowSet::isNew( )
{
    return m_bNew;
}

// -----------------------------------------------------------------------------
void ORowSet::checkUpdateIterator()
{
    if(!m_bModified && !m_bNew)
    {
        m_pCache->setUpdateIterator(m_aCurrentRow);
        m_aCurrentRow = m_pCache->m_aInsertRow;
    }
}
// -----------------------------------------------------------------------------
void ORowSet::checkUpdateConditions(sal_Int32 columnIndex)
{
    if(!m_pCache || columnIndex <= 0 || m_aCurrentRow == NULL || m_aCurrentRow == m_pCache->getEnd() || m_nResultSetConcurrency == ResultSetConcurrency::READ_ONLY)
        throwFunctionSequenceException(*this);
}
// -----------------------------------------------------------------------------
void SAL_CALL ORowSet::refreshRow(  ) throw(SQLException, RuntimeException)
{
    ORowSetNotifier aNotifier( this );
        // this will call cancelRowModification on the cache if necessary

    // notification order:
    if ( m_bModified && m_pCache )
        // - column values
        implCancelRowUpdates( sal_False ); // do _not_ notify the IsModify - will do this ourself below

    ORowSetBase::refreshRow();

    // - IsModified
    // - IsNew
    aNotifier.fire( );
}
// ***********************************************************
//  ORowSetClone
// ***********************************************************
DBG_NAME(ORowSetClone);
//--------------------------------------------------------------------------
ORowSetClone::ORowSetClone(ORowSet& rParent,::osl::Mutex* _pMutex)
             :OSubComponent(m_aMutex, rParent)
             ,ORowSetBase(OComponentHelper::rBHelper,_pMutex)
             ,m_nFetchDirection(rParent.m_nFetchDirection)
             ,m_nFetchSize(rParent.m_nFetchSize)
             ,m_bDeleted(rParent.m_bDeleted)
             ,m_bRowObsolete(rParent.m_bRowObsolete)
             ,m_bIsBookmarable(sal_True)
             ,m_pParent(&rParent)
{
    DBG_CTOR(ORowSetClone, NULL);

    m_nResultSetType		= rParent.m_nResultSetType;
    m_nResultSetConcurrency = ResultSetConcurrency::READ_ONLY;
    m_pMySelf				= this;
    m_bClone				= sal_True;
    m_bBeforeFirst			= rParent.m_bBeforeFirst;
    m_bAfterLast			= rParent.m_bAfterLast;
    m_pCache				= rParent.m_pCache;
    m_aBookmark				= rParent.m_aBookmark;
    m_aCurrentRow			= m_pCache->createIterator();
    m_xNumberFormatTypes	= rParent.m_xNumberFormatTypes;

    ::vos::ORef< ::connectivity::OSQLColumns> aColumns = new ::connectivity::OSQLColumns();
    ::std::vector< ::rtl::OUString> aNames;

    ::rtl::OUString aDescription;
    ConfigManager*	pConfigMgr = ConfigManager::GetConfigManager();
    Locale aLocale;
    pConfigMgr->GetDirectConfigProperty(ConfigManager::LOCALE) >>= aLocale;

    Sequence< ::rtl::OUString> aSeq = rParent.m_pColumns->getElementNames();
    const ::rtl::OUString* pBegin	= aSeq.getConstArray();
    const ::rtl::OUString* pEnd		= pBegin + aSeq.getLength();
    aColumns->reserve(aSeq.getLength()+1);
    for(sal_Int32 i=1;pBegin != pEnd ;++pBegin,++i)
    {
        Reference<XPropertySet> xColumn;
        rParent.m_pColumns->getByName(*pBegin) >>= xColumn;
        if(xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DESCRIPTION))
            aDescription = comphelper::getString(xColumn->getPropertyValue(PROPERTY_DESCRIPTION));

        ORowSetColumn* pColumn = new ORowSetColumn(	rParent.getMetaData(),
                                                            this,
                                                            i,
                                                            aDescription,
                                                            m_aCurrentRow,
                                                            m_pCache->getEnd());
        aColumns->push_back(pColumn);
        pColumn->setName(*pBegin);
        aNames.push_back(*pBegin);
        m_aDataColumns.push_back(pColumn);

        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_ALIGN,xColumn->getPropertyValue(PROPERTY_ALIGN));
        sal_Int32 nFormatKey = comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_NUMBERFORMAT));
        if(!nFormatKey && xColumn.is() && m_xNumberFormatTypes.is())
            nFormatKey = ::dbtools::getDefaultNumberFormat(xColumn,m_xNumberFormatTypes,aLocale);
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_NUMBERFORMAT,makeAny(nFormatKey));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_RELATIVEPOSITION,xColumn->getPropertyValue(PROPERTY_RELATIVEPOSITION));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_WIDTH,xColumn->getPropertyValue(PROPERTY_WIDTH));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HIDDEN,xColumn->getPropertyValue(PROPERTY_HIDDEN));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLMODEL,xColumn->getPropertyValue(PROPERTY_CONTROLMODEL));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_HELPTEXT,xColumn->getPropertyValue(PROPERTY_HELPTEXT));
        pColumn->setFastPropertyValue_NoBroadcast(PROPERTY_ID_CONTROLDEFAULT,xColumn->getPropertyValue(PROPERTY_CONTROLDEFAULT));

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
    DBG_DTOR(ORowSetClone, NULL);
}
// com::sun::star::XTypeProvider
//--------------------------------------------------------------------------
Sequence< Type > ORowSetClone::getTypes() throw (RuntimeException)
{
    return ::comphelper::concatSequences(OSubComponent::getTypes(),ORowSetBase::getTypes());
}
// com::sun::star::XInterface
//--------------------------------------------------------------------------
Any ORowSetClone::queryInterface( const Type & rType ) throw (RuntimeException)
{
    Any aRet = ORowSetBase::queryInterface(rType);
    if(!aRet.hasValue())
        aRet = OSubComponent::queryInterface(rType);
    return aRet;
}
//------------------------------------------------------------------------------
void ORowSetClone::acquire() throw()
{
    OSubComponent::acquire();
}

//------------------------------------------------------------------------------
void ORowSetClone::release() throw()
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
    return ::comphelper::findValue(getSupportedServiceNames(), _rServiceName, sal_True).getLength() != 0;
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
    MutexGuard aGuard( m_aMutex );
    ORowSetBase::disposing();
    
    m_pParent	= NULL;
    m_pMutex	= &m_aMutex; // this must be done here because someone could hold a ref to us and try to do something 
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

// comphelper::OPropertyArrayUsageHelper
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
    typedef ::comphelper::OPropertyArrayUsageHelper<ORowSetClone> ORowSetClone_PROP;
    return *ORowSetClone_PROP::getArrayHelper();
}
// -------------------------------------------------------------------------
//--------------------------------------------------------------------------
Sequence< sal_Int8 > ORowSetClone::getUnoTunnelImplementationId()
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
// -----------------------------------------------------------------------------
// com::sun::star::XUnoTunnel
sal_Int64 SAL_CALL ORowSetClone::getSomething( const Sequence< sal_Int8 >& rId ) throw(RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getUnoTunnelImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;

    return 0;
}
// -----------------------------------------------------------------------------
void ORowSetClone::rowDelete(const ::com::sun::star::uno::Any& _rBookmark)
{
    if(compareBookmarks(_rBookmark,m_aBookmark) == 0)
    {
        OSL_ENSURE(m_aBookmark.hasValue(),"ORowSetClone::rowDelete: Bookmark isn't valid!");
        ::osl::MutexGuard aGuard( *m_pMutex );
        m_pCache->moveToBookmark(m_aBookmark);
        m_nPosition = m_pCache->getRow();
    }
}
// -----------------------------------------------------------------------------
void ORowSetClone::rowDeleted(const ::com::sun::star::uno::Any& _rBookmark)
{
    if(compareBookmarks(_rBookmark,m_aBookmark) == 0)
    {
        m_aBookmark		= Any();
        m_aCurrentRow	= NULL;
        m_aCurrentRow.setBookmark(Any());
    }
}
// -----------------------------------------------------------------------------
void SAL_CALL ORowSetClone::setFastPropertyValue_NoBroadcast(sal_Int32 nHandle,const Any& rValue) throw (Exception)
{
    switch(nHandle)
    {
    case PROPERTY_ID_FETCHSIZE:
        if(m_pParent)
            m_pParent->setFastPropertyValue_NoBroadcast(nHandle,rValue);
        // run through
    default:
        OPropertyContainer::setFastPropertyValue_NoBroadcast(nHandle,rValue);
    }
    
}

// -----------------------------------------------------------------------------
void ORowSetClone::doCancelModification( )
{
    OSL_ENSURE( sal_False, "ORowSetClone::doCancelModification: invalid call!" );
}

// -----------------------------------------------------------------------------
sal_Bool ORowSetClone::isModification( )
{
    return sal_False;
}

// -----------------------------------------------------------------------------
sal_Bool ORowSetClone::isModified( )
{
    return sal_False;
}

// -----------------------------------------------------------------------------
sal_Bool ORowSetClone::isNew( )
{
    return sal_False;
}

}
