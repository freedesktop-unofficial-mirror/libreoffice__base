/*************************************************************************
 *
 *  $RCSfile: CacheSet.cxx,v $
 *
 *  $Revision: 1.27 $
 *
 *  last change: $Author: oj $ $Date: 2001-10-26 07:50:50 $
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
#ifndef DBACCESS_CORE_API_CACHESET_HXX
#include "CacheSet.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBCX_COMPAREBOOKMARK_HPP_
#include <com/sun/star/sdbcx/CompareBookmark.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XPREPAREDSTATEMENT_HPP_
#include <com/sun/star/sdbc/XPreparedStatement.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XPARAMETERS_HPP_
#include <com/sun/star/sdbc/XParameters.hpp>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XKEYSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XKeysSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XINDEXESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XIndexesSupplier.hpp>
#endif
#ifndef _LIST_
#include <list>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBCX_KEYTYPE_HPP_
#include <com/sun/star/sdbcx/KeyType.hpp>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif

using namespace comphelper;

using namespace dbaccess;
using namespace dbtools;
using namespace connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
//	using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::io;
//	using namespace ::cppu;
using namespace ::osl;

// -------------------------------------------------------------------------
OCacheSet::~OCacheSet()
{
    try
    {
        m_xDriverSet = NULL;  
        m_xDriverRow = NULL;  
        m_xSetMetaData = NULL;
        m_xConnection = NULL; 
    }
    catch(Exception&)
    {
        OSL_ENSURE(0,"Exception occured");
    }
    catch(...)
    {
        OSL_ENSURE(0,"Unknown Exception occured");
    }
}
// -----------------------------------------------------------------------------
void OCacheSet::fillTableName(const Reference<XPropertySet>& _xTable)  throw(SQLException, RuntimeException)
{
    OSL_ENSURE(_xTable.is(),"OCacheSet::fillTableName: PropertySet is empty!");
    if(!m_aComposedTableName.getLength())
    {
        Reference<XDatabaseMetaData> xMeta(m_xConnection->getMetaData());
        composeTableName(xMeta
                        ,comphelper::getString(_xTable->getPropertyValue(PROPERTY_CATALOGNAME))
                        ,comphelper::getString(_xTable->getPropertyValue(PROPERTY_SCHEMANAME))
                        ,comphelper::getString(_xTable->getPropertyValue(PROPERTY_NAME))
                        ,m_aComposedTableName
                        ,sal_True);
    }
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::insertRow( const ORowSetRow& _rInsertRow,const connectivity::OSQLTable& _xTable ) throw(SQLException, RuntimeException)
{
    ::rtl::OUString aSql(::rtl::OUString::createFromAscii("INSERT INTO "));
    Reference<XPropertySet> xSet(_xTable,UNO_QUERY);
    fillTableName(xSet);

    aSql += m_aComposedTableName;
    aSql += ::rtl::OUString::createFromAscii(" ( ");
    // set values and column names
    ::rtl::OUString aValues = ::rtl::OUString::createFromAscii(" VALUES ( ");
    static ::rtl::OUString aPara = ::rtl::OUString::createFromAscii("?,");
    ::rtl::OUString aQuote = m_xConnection->getMetaData()->getIdentifierQuoteString();
    static ::rtl::OUString aComma = ::rtl::OUString::createFromAscii(",");
    sal_Int32 i = 1;
    ORowVector< ORowSetValue >::const_iterator aIter = _rInsertRow->begin()+1;
    for(; aIter != _rInsertRow->end();++aIter)
    {
        aSql += ::dbtools::quoteName( aQuote,m_xSetMetaData->getColumnName(i++));
        aSql += aComma;
        aValues += aPara;
    }

    aSql = aSql.replaceAt(aSql.getLength()-1,1,::rtl::OUString::createFromAscii(")"));
    aValues = aValues.replaceAt(aValues.getLength()-1,1,::rtl::OUString::createFromAscii(")"));

    aSql += aValues;
    // now create end execute the prepared statement
    {
        Reference< XPreparedStatement > xPrep(m_xConnection->prepareStatement(aSql));
        Reference< XParameters > xParameter(xPrep,UNO_QUERY);
        i = 1;
        for(aIter = _rInsertRow->begin()+1; aIter != _rInsertRow->end();++aIter,++i)
        {
            if(aIter->isNull())
                xParameter->setNull(i,aIter->getTypeKind());
            else
                setParameter(i,xParameter,*aIter);
        }

        m_bInserted = xPrep->executeUpdate() > 0;
    }
    
//	::rtl::OUString aCountSql = ::rtl::OUString::createFromAscii("SELECT COUNT(*) FROM ");
//	aCountSql += m_aComposedTableName;
//	try
//	{
//		Reference< XStatement > xStmt(m_xConnection->createStatement());
//		Reference<XResultSet> xRes(xStmt->executeQuery(aCountSql));
//		if(xRes.is() && xRes->next())
//		{
//			Reference<XRow> xRow(xRes,UNO_QUERY);
//		}
//	}
//	catch(SQLException&)
//	{
//	}
    
    // TODO set the bookmark in the insert row
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::updateRow(const ORowSetRow& _rInsertRow ,const ORowSetRow& _rOrginalRow,const connectivity::OSQLTable& _xTable  ) throw(SQLException, RuntimeException)
{
    Reference<XPropertySet> xSet(_xTable,UNO_QUERY);
    fillTableName(xSet);

    ::rtl::OUString aSql = ::rtl::OUString::createFromAscii("UPDATE ");
    aSql += m_aComposedTableName;
    aSql += ::rtl::OUString::createFromAscii(" SET ");
    // list all cloumns that should be set
    static ::rtl::OUString aPara	= ::rtl::OUString::createFromAscii(" = ?,");
    ::rtl::OUString aQuote	= m_xConnection->getMetaData()->getIdentifierQuoteString();
    static ::rtl::OUString aAnd		= ::rtl::OUString::createFromAscii(" AND ");

    sal_Int32 i = 1;
    ORowVector< ORowSetValue >::const_iterator aIter = _rInsertRow->begin()+1;

    // use keys and indexes for excat postioning
    // first the keys
    Reference<XKeysSupplier> xKeySup(_xTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    Reference<XColumnsSupplier> xKeyColsSup;
    Reference<XNameAccess> xKeyColumns;
    if(xKeys.is() && xKeys->getCount())
    {
        Reference<XPropertySet> xProp;
        Reference<XColumnsSupplier> xColumnsSupplier;
        // search the one and only primary key
        for(sal_Int32 i=0;i< xKeys->getCount();++i)
        {
            ::cppu::extractInterface(xProp,xKeys->getByIndex(i));
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(KeyType::PRIMARY == nKeyType)
            {
                xKeyColsSup = Reference<XColumnsSupplier>(xProp,UNO_QUERY);
                break;
            }
        }
        if(xKeyColsSup.is())
            xKeyColumns = xKeyColsSup->getColumns();
    }
    // second the indexes
    Reference<XIndexesSupplier> xIndexSup(_xTable,UNO_QUERY);
    Reference<XIndexAccess> xIndexes;
    if(xIndexSup.is())
        xIndexes = Reference<XIndexAccess>(xIndexSup->getIndexes(),UNO_QUERY);

    //	Reference<XColumnsSupplier>
    Reference<XPropertySet> xIndexColsSup;
    Reference<XNameAccess> xIndexColumns;
    ::std::vector< Reference<XNameAccess> > aAllIndexColumns;
    for(sal_Int32 j=0;j<xIndexes->getCount();++j)
    {
        ::cppu::extractInterface(xIndexColsSup,xIndexes->getByIndex(j));
        if(	xIndexColsSup.is()
            && comphelper::getBOOL(xIndexColsSup->getPropertyValue(PROPERTY_ISUNIQUE))
            && !comphelper::getBOOL(xIndexColsSup->getPropertyValue(PROPERTY_ISPRIMARYKEYINDEX))
          )
            aAllIndexColumns.push_back(Reference<XColumnsSupplier>(xIndexColsSup,UNO_QUERY)->getColumns());
    }

    ::rtl::OUString aColumnName;
    ::rtl::OUString aCondition;
    ::std::list< sal_Int32> aOrgValues;
    sal_Int32 nCheckCount = 1; // index for the orginal values
    for(; aIter != _rInsertRow->end();++aIter,++nCheckCount,++i)
    {
        aColumnName = m_xSetMetaData->getColumnName(i);
        if(xKeyColumns.is() && xKeyColumns->hasByName(aColumnName))
        {
            aCondition += ::dbtools::quoteName( aQuote,aColumnName);
            if(aIter->isNull())
                aCondition += ::rtl::OUString::createFromAscii(" IS NULL");
            else
                aCondition += ::rtl::OUString::createFromAscii(" = ?");
            aCondition += aAnd;
            aOrgValues.push_back(nCheckCount);

        }
        for( ::std::vector< Reference<XNameAccess> >::const_iterator aIndexIter = aAllIndexColumns.begin();
                aIndexIter != aAllIndexColumns.end();++aIndexIter)
        {
            if((*aIndexIter)->hasByName(aColumnName))
            {
                aCondition += ::dbtools::quoteName( aQuote,aColumnName);
                if(aIter->isNull())
                    aCondition += ::rtl::OUString::createFromAscii(" IS NULL");
                else
                    aCondition += ::rtl::OUString::createFromAscii(" = ?");
                aCondition += aAnd;
                aOrgValues.push_back(nCheckCount);
                break;
            }
        }
        if(aIter->isModified())
        {
            aSql += ::dbtools::quoteName( aQuote,aColumnName);
            aSql += aPara;
        }
    }
    aSql = aSql.replaceAt(aSql.getLength()-1,1,::rtl::OUString::createFromAscii(" "));
    if(aCondition.getLength())
    {
        aCondition = aCondition.replaceAt(aCondition.getLength()-5,5,::rtl::OUString::createFromAscii(" "));

        aSql += ::rtl::OUString::createFromAscii(" WHERE ");
        aSql += aCondition;
    }
    else
        throw SQLException();

    // now create end execute the prepared statement
    Reference< XPreparedStatement > xPrep(m_xConnection->prepareStatement(aSql));
    Reference< XParameters > xParameter(xPrep,UNO_QUERY);
    i = 1;
    for(aIter = _rInsertRow->begin()+1; aIter != _rInsertRow->end();++aIter)
    {
        if(aIter->isModified())
            setParameter(i++,xParameter,*aIter);
    }
    for(::std::list< sal_Int32>::const_iterator aOrgValue = aOrgValues.begin(); aOrgValue != aOrgValues.end();++aOrgValue,++i)
    {
        setParameter(i,xParameter,(*_rOrginalRow)[*aOrgValue]);
    }

     m_bUpdated = xPrep->executeUpdate() > 0;
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::deleteRow(const ORowSetRow& _rDeleteRow ,const connectivity::OSQLTable& _xTable  ) throw(SQLException, RuntimeException)
{
    Reference<XPropertySet> xSet(_xTable,UNO_QUERY);
    fillTableName(xSet);

    ::rtl::OUString aSql = ::rtl::OUString::createFromAscii("DELETE FROM ");
    aSql += m_aComposedTableName;
    aSql += ::rtl::OUString::createFromAscii(" WHERE ");

    // list all cloumns that should be set
    ::rtl::OUString aQuote	= m_xConnection->getMetaData()->getIdentifierQuoteString();
    static ::rtl::OUString aAnd		= ::rtl::OUString::createFromAscii(" AND ");

    sal_Int32 i = 1;
    ORowVector< ORowSetValue >::const_iterator aIter = _rDeleteRow->begin()+1;

    // use keys and indexes for excat postioning
    // first the keys
    Reference<XKeysSupplier> xKeySup(_xTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    Reference<XColumnsSupplier> xKeyColsSup;
    Reference<XNameAccess> xKeyColumns;
    if(xKeys.is() && xKeys->getCount())
    {
        Reference<XPropertySet> xProp;
        Reference<XColumnsSupplier> xColumnsSupplier;
        // search the one and only primary key
        for(sal_Int32 i=0;i< xKeys->getCount();++i)
        {
            ::cppu::extractInterface(xProp,xKeys->getByIndex(i));
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(KeyType::PRIMARY == nKeyType)
            {
                xKeyColsSup = Reference<XColumnsSupplier>(xProp,UNO_QUERY);
                break;
            }
        }
        if(xKeyColsSup.is())
            xKeyColumns = xKeyColsSup->getColumns();
    }
    // second the indexes
    Reference<XIndexesSupplier> xIndexSup(_xTable,UNO_QUERY);
    Reference<XIndexAccess> xIndexes;
    if(xIndexSup.is())
        xIndexes = Reference<XIndexAccess>(xIndexSup->getIndexes(),UNO_QUERY);

    //	Reference<XColumnsSupplier>
    Reference<XPropertySet> xIndexColsSup;
    Reference<XNameAccess> xIndexColumns;
    ::std::vector< Reference<XNameAccess> > aAllIndexColumns;
    if(xIndexes.is())
    {
        for(sal_Int32 j=0;j<xIndexes->getCount();++j)
        {
            ::cppu::extractInterface(xIndexColsSup,xIndexes->getByIndex(j));
            if(	xIndexColsSup.is()
                && comphelper::getBOOL(xIndexColsSup->getPropertyValue(PROPERTY_ISUNIQUE))
                && !comphelper::getBOOL(xIndexColsSup->getPropertyValue(PROPERTY_ISPRIMARYKEYINDEX))
              )
                aAllIndexColumns.push_back(Reference<XColumnsSupplier>(xIndexColsSup,UNO_QUERY)->getColumns());
        }
    }

    ::rtl::OUString aColumnName;
    ::std::list< sal_Int32> aOrgValues;
    sal_Int32 nCheckCount = 1; // index for the orginal values
    for(; aIter != _rDeleteRow->end();++aIter,++nCheckCount)
    {
        {
            aColumnName = m_xSetMetaData->getColumnName(i++);
            if(xKeyColumns.is() && xKeyColumns->hasByName(aColumnName))
            {
                aSql += ::dbtools::quoteName( aQuote,aColumnName);
                if(aIter->isNull())
                    aSql += ::rtl::OUString::createFromAscii(" IS NULL");
                else
                    aSql += ::rtl::OUString::createFromAscii(" = ?");
                aSql += aAnd;
                aOrgValues.push_back(nCheckCount);

            }
            for( ::std::vector< Reference<XNameAccess> >::const_iterator aIndexIter = aAllIndexColumns.begin();
                    aIndexIter != aAllIndexColumns.end();++aIndexIter)
            {
                if((*aIndexIter)->hasByName(aColumnName))
                {
                    aSql += ::dbtools::quoteName( aQuote,aColumnName);
                    if(aIter->isNull())
                        aSql += ::rtl::OUString::createFromAscii(" IS NULL");
                    else
                        aSql += ::rtl::OUString::createFromAscii(" = ?");
                    aSql += aAnd;
                    aOrgValues.push_back(nCheckCount);
                    break;
                }
            }
        }
    }
    aSql = aSql.replaceAt(aSql.getLength()-5,5,::rtl::OUString::createFromAscii(" "));

    // now create end execute the prepared statement
    Reference< XPreparedStatement > xPrep(m_xConnection->prepareStatement(aSql));
    Reference< XParameters > xParameter(xPrep,UNO_QUERY);
    i = 1;
    for(::std::list< sal_Int32>::const_iterator j = aOrgValues.begin(); j != aOrgValues.end();++j,++i)
    {
        setParameter(i,xParameter,(*_rDeleteRow)[*j]);
    }

    m_bDeleted = xPrep->executeUpdate() > 0;
}
// -------------------------------------------------------------------------
void OCacheSet::setParameter(sal_Int32 nPos,Reference< XParameters > _xParameter,const ORowSetValue& _rValue) throw(SQLException, RuntimeException)
{
    if(!_rValue.isNull())
    {
        switch(_rValue.getTypeKind())
        {
            case DataType::CHAR:
            case DataType::VARCHAR:
            case DataType::DECIMAL:
            case DataType::NUMERIC:
                _xParameter->setString(nPos,_rValue);
                break;
            case DataType::BIGINT:
                _xParameter->setLong(nPos,_rValue);
                break;
            case DataType::BIT:
                _xParameter->setBoolean(nPos,_rValue);
                break;
            case DataType::TINYINT:
                _xParameter->setByte(nPos,_rValue);
                break;
            case DataType::SMALLINT:
                _xParameter->setShort(nPos,_rValue);
                break;
            case DataType::INTEGER:
                _xParameter->setInt(nPos,_rValue);
                break;
            case DataType::FLOAT:
                _xParameter->setFloat(nPos,_rValue);
                break;
            case DataType::DOUBLE:
            case DataType::REAL:
                _xParameter->setDouble(nPos,_rValue);
                break;
            case DataType::DATE:
                _xParameter->setDate(nPos,_rValue);
                break;
            case DataType::TIME:
                _xParameter->setTime(nPos,_rValue);
                break;
            case DataType::TIMESTAMP:
                _xParameter->setTimestamp(nPos,_rValue);
                break;
            case DataType::BINARY:
            case DataType::VARBINARY:
            case DataType::LONGVARBINARY:
            case DataType::LONGVARCHAR:
                _xParameter->setBytes(nPos,_rValue);
                break;
            case DataType::CLOB:
                {
                    Reference<XInputStream> xStream;
                    _rValue.getAny() >>= xStream;
                    _xParameter->setCharacterStream(nPos,xStream,xStream.is() ? xStream->available() : sal_Int32(0));
                }
                break;
            case DataType::BLOB:
                {
                    Reference<XInputStream> xStream;
                    _rValue.getAny() >>= xStream;
                    _xParameter->setBinaryStream(nPos,xStream,xStream.is() ? xStream->available() : sal_Int32(0));
                }
                break;
        }
    }
    else
        _xParameter->setNull(nPos,_rValue.getTypeKind());
}
// -------------------------------------------------------------------------
void OCacheSet::fillValueRow(ORowSetRow& _rRow,sal_Int32 _nPosition)
{
    connectivity::ORowVector< ORowSetValue >::iterator aIter = _rRow->begin();
    Any aBookmark = getBookmark(_rRow);
    if(!aBookmark.hasValue())
        aBookmark = makeAny(_nPosition);
    (*aIter) = aBookmark;
    ++aIter;
    for(sal_Int32 i=1;aIter != _rRow->end();++aIter,++i)
    {
        sal_Int32 nType = m_xSetMetaData->getColumnType(i);
        
        switch(nType)
        {
        case DataType::CHAR:
        case DataType::VARCHAR:
        case DataType::DECIMAL:
        case DataType::NUMERIC:
            (*aIter) = getString(i);
            break;
        case DataType::BIGINT:
            (*aIter) = getLong(i);
            break;
        case DataType::FLOAT:
            (*aIter) = getFloat(i);
            break;
        case DataType::DOUBLE:
        case DataType::REAL:
            (*aIter) = getDouble(i);
            break;
        case DataType::DATE:
            (*aIter) = getDate(i);
            break;
        case DataType::TIME:
            (*aIter) = getTime(i);
            break;
        case DataType::TIMESTAMP:
            (*aIter) = getTimestamp(i);
            break;
        case DataType::BINARY:
        case DataType::VARBINARY:
        case DataType::LONGVARBINARY:
        case DataType::LONGVARCHAR:
            (*aIter) = getBytes(i);
            break;
        case DataType::BIT:
            (*aIter) = getBoolean(i);
            break;
        case DataType::TINYINT:
            (*aIter) = getByte(i);
            break;
        case DataType::SMALLINT:
            (*aIter) = getShort(i);
            break;
        case DataType::INTEGER:
            (*aIter) = getInt(i);
            break;
        default:
            OSL_ENSURE(0,"ORowSetValue::makeAny(): UNSPUPPORTED TYPE!");
        }
        if(wasNull())
            aIter->setNull();
        if(nType != aIter->getTypeKind())
        {
            aIter->setTypeKind(nType);
        }

    }
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::wasNull(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->wasNull();
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OCacheSet::getString( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getString(columnIndex);
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::getBoolean( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getBoolean(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int8 SAL_CALL OCacheSet::getByte( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getByte(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int16 SAL_CALL OCacheSet::getShort( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getShort(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OCacheSet::getInt( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getInt(columnIndex);
}
// -------------------------------------------------------------------------
sal_Int64 SAL_CALL OCacheSet::getLong( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getLong(columnIndex);
}
// -------------------------------------------------------------------------
float SAL_CALL OCacheSet::getFloat( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getFloat(columnIndex);
}
// -------------------------------------------------------------------------
double SAL_CALL OCacheSet::getDouble( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getDouble(columnIndex);
}
// -------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL OCacheSet::getBytes( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getBytes(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::Date SAL_CALL OCacheSet::getDate( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getDate(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::Time SAL_CALL OCacheSet::getTime( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getTime(columnIndex);
}
// -------------------------------------------------------------------------
::com::sun::star::util::DateTime SAL_CALL OCacheSet::getTimestamp( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getTimestamp(columnIndex);
}
// -------------------------------------------------------------------------
Reference< ::com::sun::star::io::XInputStream > SAL_CALL OCacheSet::getBinaryStream( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getBinaryStream(columnIndex);
}
// -------------------------------------------------------------------------
Reference< ::com::sun::star::io::XInputStream > SAL_CALL OCacheSet::getCharacterStream( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getCharacterStream(columnIndex);
}
// -------------------------------------------------------------------------
Any SAL_CALL OCacheSet::getObject( sal_Int32 columnIndex, const Reference< ::com::sun::star::container::XNameAccess >& typeMap ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getObject(columnIndex,typeMap);
}
// -------------------------------------------------------------------------
Reference< XRef > SAL_CALL OCacheSet::getRef( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getRef(columnIndex);
}
// -------------------------------------------------------------------------
Reference< XBlob > SAL_CALL OCacheSet::getBlob( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getBlob(columnIndex);
}
// -------------------------------------------------------------------------
Reference< XClob > SAL_CALL OCacheSet::getClob( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getClob(columnIndex);
}
// -------------------------------------------------------------------------
Reference< XArray > SAL_CALL OCacheSet::getArray( sal_Int32 columnIndex ) throw(SQLException, RuntimeException)
{
    return m_xDriverRow->getArray(columnIndex);
}
// -------------------------------------------------------------------------
// XResultSet
sal_Bool SAL_CALL OCacheSet::next(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->next();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::isBeforeFirst(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->isBeforeFirst();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::isAfterLast(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->isAfterLast();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::isFirst(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->isFirst();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::isLast(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->isLast();
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::beforeFirst(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    m_xDriverSet->beforeFirst();
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::afterLast(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    m_xDriverSet->afterLast();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::first(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->first();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::last(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->last();
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OCacheSet::getRow(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->getRow();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::absolute( sal_Int32 row ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->absolute(row);
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::relative( sal_Int32 rows ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->relative(rows);
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::previous(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    return m_xDriverSet->previous();
}
// -------------------------------------------------------------------------
void SAL_CALL OCacheSet::refreshRow(  ) throw(SQLException, RuntimeException)
{
    m_xDriverSet->refreshRow();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::rowUpdated(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->rowUpdated();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::rowInserted(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->rowInserted();
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OCacheSet::rowDeleted(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->rowDeleted();
}
// -------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OCacheSet::getStatement(  ) throw(SQLException, RuntimeException)
{
    return m_xDriverSet->getStatement();
}
// -----------------------------------------------------------------------------


