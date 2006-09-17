/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: resultcolumn.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-17 06:35:57 $
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
#ifndef _DBACORE_RESULTCOLUMN_HXX_
#include "resultcolumn.hxx"
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _CPPUHELPER_EXC_HLP_HXX_
#include <cppuhelper/exc_hlp.hxx>
#endif
#ifndef _OSL_THREAD_H_
#include <osl/thread.h>
#endif

using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::osl;
using namespace ::comphelper;
using namespace ::cppu;
using namespace dbaccess;

DBG_NAME(OResultColumn)
//--------------------------------------------------------------------------
OResultColumn::OResultColumn(
                         const Reference < XResultSetMetaData >& _xMetaData,
                         sal_Int32 _nPos,
                         const Reference< XDatabaseMetaData >& _rxDBMeta )
                     :m_xMetaData(_xMetaData)
                     ,m_xDBMetaData(_rxDBMeta)
                     ,m_nPos(_nPos)
{
    DBG_CTOR(OResultColumn,NULL);
}
// -----------------------------------------------------------------------------
void OResultColumn::impl_determineIsRowVersion_nothrow()
{
    if ( m_aIsRowVersion.hasValue() )
        return;
    m_aIsRowVersion <<= (sal_Bool)(sal_False);

    OSL_ENSURE( m_xDBMetaData.is(), "OResultColumn::impl_determineIsRowVersion_nothrow: no DBMetaData!" );
    if ( !m_xDBMetaData.is() )
        return;
    
    try
    {
        ::rtl::OUString sCatalog, sSchema, sTable, sColumnName;
        getPropertyValue( PROPERTY_CATALOGNAME ) >>= sCatalog;
        getPropertyValue( PROPERTY_SCHEMANAME ) >>= sSchema;
        getPropertyValue( PROPERTY_TABLENAME ) >>= sTable;
        getPropertyValue( PROPERTY_NAME ) >>= sColumnName;

        Reference< XResultSet > xVersionColumns = m_xDBMetaData->getVersionColumns(
            makeAny( sCatalog ), sSchema, sTable );
        if ( xVersionColumns.is() ) // allowed to be NULL
        {
            Reference< XRow > xResultRow( xVersionColumns, UNO_QUERY_THROW );
            while ( xVersionColumns->next() )
            {
                if ( xResultRow->getString( 2 ) == sColumnName )
                {
                    m_aIsRowVersion <<= (sal_Bool)(sal_True);
                    break;
                }
            }
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}
// -----------------------------------------------------------------------------
OResultColumn::~OResultColumn()
{
    DBG_DTOR(OResultColumn,NULL);
}
// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OResultColumn::getImplementationId() throw (RuntimeException)
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

// XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OResultColumn::getImplementationName(  ) throw(RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OResultColumn");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OResultColumn::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMN;
    aSNS[1] = SERVICE_SDB_RESULTCOLUMN;
    return aSNS;
}

// OComponentHelper
//------------------------------------------------------------------------------
void OResultColumn::disposing()
{
    OColumn::disposing();

    MutexGuard aGuard(m_aMutex);
    m_xMetaData = NULL;
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OResultColumn::createArrayHelper( ) const
{
    BEGIN_PROPERTY_HELPER(21)
        DECL_PROP1(CATALOGNAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(DISPLAYSIZE,				sal_Int32,			READONLY);
        DECL_PROP1_BOOL(ISAUTOINCREMENT,						READONLY);
        DECL_PROP1_BOOL(ISCASESENSITIVE,						READONLY);
        DECL_PROP1_BOOL(ISCURRENCY,								READONLY);
        DECL_PROP1_BOOL(ISDEFINITELYWRITABLE,					READONLY);
        DECL_PROP1(ISNULLABLE,				sal_Int32,			READONLY);
        DECL_PROP1_BOOL(ISREADONLY,								READONLY);
        DECL_PROP1_BOOL(ISROWVERSION,                           READONLY);
        DECL_PROP1_BOOL(ISSEARCHABLE,							READONLY);
        DECL_PROP1_BOOL(ISSIGNED,								READONLY);
        DECL_PROP1_BOOL(ISWRITABLE,								READONLY);
        DECL_PROP1(LABEL,					::rtl::OUString,	READONLY);
        DECL_PROP1(NAME,					::rtl::OUString,	READONLY);
        DECL_PROP1(PRECISION,				sal_Int32,			READONLY);
        DECL_PROP1(SCALE,					sal_Int32,			READONLY);
        DECL_PROP1(SCHEMANAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(SERVICENAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(TABLENAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(TYPE,					sal_Int32,			READONLY);
        DECL_PROP1(TYPENAME,				::rtl::OUString,	READONLY);
    END_PROPERTY_HELPER();
}

// cppu::OPropertySetHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OResultColumn::getInfoHelper()
{
    return *static_cast< ::comphelper::OPropertyArrayUsageHelper< OResultColumn >* >(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OResultColumn::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    try
    {
        switch (nHandle)
        {
            case PROPERTY_ID_ISROWVERSION:
                const_cast< OResultColumn* >( this )->impl_determineIsRowVersion_nothrow();
                rValue = m_aIsRowVersion;
                break;
            case PROPERTY_ID_TABLENAME:
                rValue <<= m_xMetaData->getTableName(m_nPos);
                break;
            case PROPERTY_ID_SCHEMANAME:
                rValue <<= m_xMetaData->getSchemaName(m_nPos);
                break;
            case PROPERTY_ID_CATALOGNAME:
                rValue <<= m_xMetaData->getCatalogName(m_nPos);
                break;
            case PROPERTY_ID_ISSIGNED:
            {
                sal_Bool bVal = m_xMetaData->isSigned(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISCURRENCY:
            {
                sal_Bool bVal = m_xMetaData->isCurrency(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISSEARCHABLE:
            {
                sal_Bool bVal = m_xMetaData->isSearchable(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISCASESENSITIVE:
            {
                sal_Bool bVal = m_xMetaData->isCaseSensitive(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISREADONLY:
            {
                sal_Bool bVal = m_xMetaData->isReadOnly(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISWRITABLE:
            {
                sal_Bool bVal = m_xMetaData->isWritable(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISDEFINITELYWRITABLE:
            {
                sal_Bool bVal = m_xMetaData->isDefinitelyWritable(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISAUTOINCREMENT:
            {
                sal_Bool bVal = m_xMetaData->isAutoIncrement(m_nPos);
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_SERVICENAME:
                rValue <<= m_xMetaData->getColumnServiceName(m_nPos);
                break;
            case PROPERTY_ID_LABEL:
                rValue <<= m_xMetaData->getColumnLabel(m_nPos);
                break;
            case PROPERTY_ID_DISPLAYSIZE:
                rValue <<= m_xMetaData->getColumnDisplaySize(m_nPos);
                break;
            case PROPERTY_ID_TYPE:
                rValue <<= m_xMetaData->getColumnType(m_nPos);
                break;
            case PROPERTY_ID_PRECISION:
                rValue <<= m_xMetaData->getPrecision(m_nPos);
                break;
            case PROPERTY_ID_SCALE:
                rValue <<= m_xMetaData->getScale(m_nPos);
                break;
            case PROPERTY_ID_ISNULLABLE:
                rValue <<= m_xMetaData->isNullable(m_nPos);
                break;
            case PROPERTY_ID_TYPENAME:
                rValue <<= m_xMetaData->getColumnTypeName(m_nPos);
                break;
            case PROPERTY_ID_NAME:
                OColumn::getFastPropertyValue( rValue, nHandle );
                break;
        }
    }
    catch (SQLException& )
    {
        // default handling if we caught an exception
        switch (nHandle)
        {
            case PROPERTY_ID_LABEL:
            case PROPERTY_ID_TYPENAME:
            case PROPERTY_ID_SERVICENAME:
            case PROPERTY_ID_TABLENAME:
            case PROPERTY_ID_SCHEMANAME:
            case PROPERTY_ID_CATALOGNAME:
                // empty string'S
                rValue <<= rtl::OUString();
                break;
            case PROPERTY_ID_ISROWVERSION:
            case PROPERTY_ID_ISAUTOINCREMENT:
            case PROPERTY_ID_ISWRITABLE:
            case PROPERTY_ID_ISDEFINITELYWRITABLE:
            case PROPERTY_ID_ISCASESENSITIVE:
            case PROPERTY_ID_ISSEARCHABLE:
            case PROPERTY_ID_ISCURRENCY:
            case PROPERTY_ID_ISSIGNED:
            {
                sal_Bool bVal = sal_False;
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_ISREADONLY:
            {
                sal_Bool bVal = sal_True;
                rValue.setValue(&bVal, getBooleanCppuType());
            }	break;
            case PROPERTY_ID_SCALE:
            case PROPERTY_ID_PRECISION:
            case PROPERTY_ID_DISPLAYSIZE:
                rValue <<= sal_Int32(0);
                break;
            case PROPERTY_ID_TYPE:
                rValue <<= sal_Int32(DataType::SQLNULL);
                break;
            case PROPERTY_ID_ISNULLABLE:
                rValue <<= ColumnValue::NULLABLE_UNKNOWN;
                break;
        }
    }
}

