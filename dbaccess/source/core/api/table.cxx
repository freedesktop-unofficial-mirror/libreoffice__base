/*************************************************************************
 *
 *  $RCSfile: table.cxx,v $
 *
 *  $Revision: 1.28 $
 *
 *  last change: $Author: fs $ $Date: 2001-06-18 11:43:14 $
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

#ifndef _DBA_CORE_TABLE_HXX_
#include "table.hxx"
#endif
#ifndef _DBACORE_DEFINITIONCOLUMN_HXX_
#include <definitioncolumn.hxx>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _COMPHELPER_ENUMHELPER_HXX_
#include <comphelper/enumhelper.hxx>
#endif
#ifndef _COMPHELPER_CONTAINER_HXX_
#include <comphelper/container.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COM_SUN_STAR_UTIL_XREFRESHLISTENER_HPP_
#include <com/sun/star/util/XRefreshListener.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_PRIVILEGE_HPP_
#include <com/sun/star/sdbcx/Privilege.hpp>
#endif
#ifndef DBACCESS_CORE_API_KEYS_HXX
#include "CKeys.hxx"
#endif
#ifndef DBACCESS_INDEXES_HXX_
#include "CIndexes.hxx"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _CONNECTIVITY_SDBCX_COLUMN_HXX_
#include <connectivity/sdbcx/VColumn.hxx>
#endif

using namespace dbaccess;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::osl;
using namespace ::comphelper;
using namespace ::cppu;
using namespace ::utl;

typedef ::std::map <sal_Int32, OTableColumn*, std::less <sal_Int32> > OColMap;

//==========================================================================
//= ODBTable
//==========================================================================
DBG_NAME(ODBTable)
//--------------------------------------------------------------------------
ODBTable::ODBTable(const OConfigurationNode& _rTableConfig,
        const Reference< ::com::sun::star::sdbc::XDatabaseMetaData >& _rxMetaData,
        const ::rtl::OUString& _rCatalog, 
        const ::rtl::OUString& _rSchema, 
        const ::rtl::OUString& _rName,
        const ::rtl::OUString& _rType, 
        const ::rtl::OUString& _rDesc) throw(SQLException)
        : connectivity::sdbcx::OTable(_rxMetaData->storesMixedCaseQuotedIdentifiers(),_rName,_rType,_rDesc,_rSchema,_rCatalog)
        ,OConfigurationFlushable(m_aMutex,_rTableConfig.isValid() ? _rTableConfig.cloneAsRoot() : OConfigurationTreeRoot())
        ,m_nPrivileges(0)
        ,m_xMetaData(_rxMetaData)
{
    DBG_CTOR(ODBTable, NULL);
    osl_incrementInterlockedCount( &m_refCount );

    DBG_ASSERT(_rxMetaData.is(), "ODBTable::ODBTable : invalid conn !");
    DBG_ASSERT(_rName.getLength(), "ODBTable::ODBTable : name !");
    // register our properties
    construct();
    refreshColumns();
    //	refreshKeys();
    //	refreshIndexes();

    // load the settings from the configuration
    if(m_aConfigurationNode.isValid())
    {
        // our own settings
        loadFrom(m_aConfigurationNode.openNode(CONFIGKEY_SETTINGS));

        // our column's settings
        OColumns* pColumns = static_cast<OColumns*>(m_pColumns);
        if(pColumns)
            pColumns->loadSettings(m_aConfigurationNode.openNode(CONFIGKEY_QRYDESCR_COLUMNS));
    }
    // we don't collect the privileges here, this is potentially expensive. Instead we determine them on request.
    // (see getFastPropertyValue)
    m_nPrivileges = -1;
    osl_decrementInterlockedCount( &m_refCount );

    // TODO : think about collecting the privileges here, as we can't ensure that in getFastPropertyValue, where
    // we do this at the moment, the statement needed can be supplied by the connection (for example the SQL-Server
    // ODBC driver does not allow more than one statement per connection, and in getFastPropertyValue it's more
    // likely that it's already used up than it's here.)
}
// -----------------------------------------------------------------------------
ODBTable::ODBTable(	const Reference< ::com::sun::star::sdbc::XDatabaseMetaData >& _rxMetaData)
                throw(::com::sun::star::sdbc::SQLException) 
        : connectivity::sdbcx::OTable(_rxMetaData->storesMixedCaseQuotedIdentifiers())
        ,OConfigurationFlushable(m_aMutex)
        ,m_nPrivileges(-1)
        ,m_xMetaData(_rxMetaData)
{
    construct();
}
// -------------------------------------------------------------------------
ODBTable::~ODBTable()
{
    DBG_DTOR(ODBTable, NULL);
}

//--------------------------------------------------------------------------
OColumn* ODBTable::createColumn(const ::rtl::OUString& _rName) const
{
    OColumn* pReturn = NULL;

    Reference< XNamed > xRet = NULL;
    if(m_xDriverColumns.is() && m_xDriverColumns->hasByName(_rName))
    {
        Reference<XPropertySet> xProp;
        m_xDriverColumns->getByName(_rName) >>= xProp;

        pReturn = new OTableColumnWrapper(xProp);
    }
    else
    {
        Any aCatalog;
        aCatalog = const_cast<ODBTable*>(this)->getPropertyValue(PROPERTY_CATALOGNAME);

        ::rtl::OUString aSchema, aTable;
        const_cast<ODBTable*>(this)->getPropertyValue(PROPERTY_SCHEMANAME)	>>= aSchema;
        const_cast<ODBTable*>(this)->getPropertyValue(PROPERTY_NAME)		>>= aTable;

        Reference< XResultSet > xResult = m_xMetaData->getColumns(aCatalog, aSchema, aTable, _rName);

        if(xResult.is())
        {
            Reference< XRow > xRow(xResult,UNO_QUERY);
            while(xResult->next())
            {
                if(xRow->getString(4) == _rName)
                {
                    sal_Int32		nField5	= xRow->getInt(5);
                    ::rtl::OUString aField6 = xRow->getString(6);
                    sal_Int32		nField7 = xRow->getInt(7)
                                ,	nField9 = xRow->getInt(9)
                                ,	nField11= xRow->getInt(11);
                    

                    connectivity::sdbcx::OColumn* pRet = new connectivity::sdbcx::OColumn(_rName,
                                                aField6,
                                                xRow->getString(13),
                                                nField11,
                                                nField7,
                                                nField9,
                                                nField5,
                                                sal_False,sal_False,sal_False,isCaseSensitive());

                    Reference<XPropertySet> xProp = pRet;
                    pReturn = new OTableColumnWrapper(xProp);
                    break;
                }
            }
        }
    }
    return pReturn;
}

//--------------------------------------------------------------------------
Sequence< sal_Int8 > ODBTable::getImplementationId() throw (RuntimeException)
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

// OComponentHelper
//------------------------------------------------------------------------------
void SAL_CALL ODBTable::disposing()
{
    OTable_Base::disposing();
    OConfigurationFlushable::disposing();

    MutexGuard aGuard(m_aMutex);
    m_xMetaData		= NULL;
}

//------------------------------------------------------------------------------
void ODBTable::getFastPropertyValue(Any& _rValue, sal_Int32 _nHandle) const
{
    if ((PROPERTY_ID_PRIVILEGES == _nHandle) && (-1 == m_nPrivileges))
    {	// somebody is asking for the privileges an we do not know them, yet
        const_cast<ODBTable*>(this)->m_nPrivileges = 0;	// don't allow anything if something goes wrong
        try
        {
            Any aVal;
            if(m_CatalogName.getLength())
                aVal <<= m_CatalogName;
            Reference< XResultSet > xPrivileges = m_xMetaData->getTablePrivileges(aVal, m_SchemaName, m_Name);
            Reference< XRow > xCurrentRow(xPrivileges, UNO_QUERY);

            if (xCurrentRow.is())
            {
                ::rtl::OUString sUserWorkingFor = m_xMetaData->getUserName();
                // after creation the set is positioned before the first record, per definitionem

                ::rtl::OUString sPrivilege, sGrantee;
                while (xPrivileges->next())
                {
#ifdef DBG_UTIL
                    ::rtl::OUString sCat, sSchema, sName, sGrantor, sGrantable;
                    sCat		= xCurrentRow->getString(1);
                    sSchema		= xCurrentRow->getString(2);
                    sName		= xCurrentRow->getString(3);
                    sGrantor	= xCurrentRow->getString(4);
#endif
                    sGrantee	= xCurrentRow->getString(5);
                    sPrivilege	= xCurrentRow->getString(6);
#ifdef DBG_UTIL
                    sGrantable	= xCurrentRow->getString(7);
#endif

                    if (sUserWorkingFor != sGrantee)
                        continue;

                    if (sPrivilege.compareToAscii("SELECT") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::SELECT;
                    else if (sPrivilege.compareToAscii("INSERT") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::INSERT;
                    else if (sPrivilege.compareToAscii("UPDATE") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::UPDATE;
                    else if (sPrivilege.compareToAscii("DELETE") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::DELETE;
                    else if (sPrivilege.compareToAscii("READ") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::READ;
                    else if (sPrivilege.compareToAscii("CREATE") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::CREATE;
                    else if (sPrivilege.compareToAscii("ALTER") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::ALTER;
                    else if (sPrivilege.compareToAscii("REFERENCE") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::REFERENCE;
                    else if (sPrivilege.compareToAscii("DROP") == 0)
                        const_cast<ODBTable*>(this)->m_nPrivileges |= Privilege::DROP;
                }
            }
            disposeComponent(xPrivileges);
        }
        catch(SQLException& e)
        {
            UNUSED(e);
            DBG_ERROR("ODBTable::ODBTable : could not collect the privileges !");
        }
    }

    OTable_Base::getFastPropertyValue(_rValue, _nHandle);
}
// -------------------------------------------------------------------------
void ODBTable::construct()
{
    OTable_Base::construct();

    registerProperty(PROPERTY_FILTER, PROPERTY_ID_FILTER, PropertyAttribute::BOUND,
                    &m_sFilter, ::getCppuType(&m_sFilter));

    registerProperty(PROPERTY_ORDER, PROPERTY_ID_ORDER, PropertyAttribute::BOUND,
                    &m_sOrder, ::getCppuType(&m_sOrder));

    registerProperty(PROPERTY_APPLYFILTER, PROPERTY_ID_APPLYFILTER, PropertyAttribute::BOUND,
                    &m_bApplyFilter, ::getBooleanCppuType());

    registerProperty(PROPERTY_FONT, PROPERTY_ID_FONT, PropertyAttribute::BOUND,
                    &m_aFont, ::getCppuType(&m_aFont));

    registerMayBeVoidProperty(PROPERTY_ROW_HEIGHT, PROPERTY_ID_ROW_HEIGHT, PropertyAttribute::BOUND | PropertyAttribute::MAYBEVOID,
                    &m_aRowHeight, ::getCppuType(static_cast<sal_Int32*>(NULL)));

    registerMayBeVoidProperty(PROPERTY_TEXTCOLOR, PROPERTY_ID_TEXTCOLOR, PropertyAttribute::BOUND | PropertyAttribute::MAYBEVOID,
                    &m_aTextColor, ::getCppuType(static_cast<sal_Int32*>(NULL)));

    registerProperty(PROPERTY_PRIVILEGES, PROPERTY_ID_PRIVILEGES, PropertyAttribute::BOUND | PropertyAttribute::READONLY,
                    &m_nPrivileges, ::getCppuType(static_cast<sal_Int32*>(NULL)));
}
// -----------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* ODBTable::createArrayHelper( sal_Int32 _nId) const
{
    Sequence< Property > aProps;
    describeProperties(aProps);
    if(!_nId)
    {
        Property* pBegin	= aProps.getArray();
        Property* pEnd		= pBegin + aProps.getLength();
        for(;pBegin != pEnd;++pBegin)
        {
            if (0 == pBegin->Name.compareToAscii(PROPERTY_CATALOGNAME))
                pBegin->Attributes = PropertyAttribute::READONLY;
            else if (0 == pBegin->Name.compareToAscii(PROPERTY_SCHEMANAME))
                pBegin->Attributes = PropertyAttribute::READONLY;
            else if (0 == pBegin->Name.compareToAscii(PROPERTY_DESCRIPTION))
                pBegin->Attributes = PropertyAttribute::READONLY;
            else if (0 == pBegin->Name.compareToAscii(PROPERTY_NAME))
                pBegin->Attributes = PropertyAttribute::READONLY;
        }
    }
    
    return new ::cppu::OPropertyArrayHelper(aProps);			
}
// -----------------------------------------------------------------------------																
::cppu::IPropertyArrayHelper & SAL_CALL ODBTable::getInfoHelper() 
{																
    return *ODBTable_PROP::getArrayHelper(isNew() ? 1 : 0);
}
// -------------------------------------------------------------------------
// XServiceInfo
IMPLEMENT_SERVICE_INFO1(ODBTable, "com.sun.star.sdb.dbaccess.ODBTable", SERVICE_SDBCX_TABLE)
// -------------------------------------------------------------------------
Any SAL_CALL ODBTable::queryInterface( const Type & rType ) throw(RuntimeException)
{
    Any aRet;
    if(rType == getCppuType( (Reference<XRename>*)0))
        return Any();
    if(rType == getCppuType( (Reference<XAlterTable>*)0))
        return Any();
    aRet = OTable_Base::queryInterface( rType);
    
    if(!aRet.hasValue())
        aRet = OConfigurationFlushable::queryInterface( rType);

    return aRet;
}
// -------------------------------------------------------------------------
Sequence< Type > SAL_CALL ODBTable::getTypes(  ) throw(RuntimeException)
{
    Type aRenameType = getCppuType( (Reference<XRename>*)0);
    Type aAlterType = getCppuType( (Reference<XAlterTable>*)0);

    Sequence< Type > aTypes(OTable_Base::getTypes());
    Sequence< Type > aRet(aTypes.getLength()-2);

    const Type* pBegin = aTypes.getConstArray();
    const Type* pEnd = pBegin + aTypes.getLength();
    for(sal_Int32 i=0;pBegin != pEnd ;++pBegin)
    {
        if(*pBegin != aRenameType && *pBegin != aAlterType)
        {
            aRet.getArray()[i++] = *pBegin;
        }
    }
    return ::comphelper::concatSequences(aRet,OConfigurationFlushable::getTypes());
}
// -----------------------------------------------------------------------------
void ODBTable::flush_NoBroadcast_NoCommit()
{
    if(m_aConfigurationNode.isValid())
    {
        storeTo(m_aConfigurationNode.openNode(CONFIGKEY_SETTINGS));
        OColumns* pColumns = static_cast<OColumns*>(m_pColumns);
        if(pColumns)
        {
            pColumns->storeSettings(m_aConfigurationNode.openNode(CONFIGKEY_QRYDESCR_COLUMNS));
        }
    }
}
// XRename,
//------------------------------------------------------------------------------
void SAL_CALL ODBTable::rename( const ::rtl::OUString& _rNewName ) throw(SQLException, ElementExistException, RuntimeException)
{
    throw SQLException(::rtl::OUString::createFromAscii("Driver does not support this function!"),*this,::rtl::OUString::createFromAscii("IM001"),0,Any());
}

// XAlterTable,
//------------------------------------------------------------------------------
void SAL_CALL ODBTable::alterColumnByName( const ::rtl::OUString& _rName, const Reference< XPropertySet >& _rxDescriptor ) throw(SQLException, NoSuchElementException, RuntimeException)
{
    if(m_pColumns->hasByName(_rName))
    {
        ::rtl::OUString sSql = ::rtl::OUString::createFromAscii("ALTER TABLE ");
        ::rtl::OUString aQuote	= m_xMetaData->getIdentifierQuoteString(  );
        ::rtl::OUString sCatalog,sSchema,sTable,sComposedName;

        if(m_xMetaData->supportsCatalogsInTableDefinitions())
            sCatalog = m_CatalogName;
        if(m_xMetaData->supportsSchemasInTableDefinitions())
            sSchema = m_SchemaName;

        ::dbtools::composeTableName(m_xMetaData,sCatalog,sSchema,m_Name,sComposedName,sal_True);
        if(!sComposedName.getLength())
            ::dbtools::throwFunctionSequenceException(*this);

        sSql += sComposedName;
        sSql += ::rtl::OUString::createFromAscii(" ALTER ");
        sSql += ::dbtools::quoteName(aQuote,_rName);

        ::rtl::OUString sNewDefaultValue,sDefaultValue;

        Reference<XPropertySet> xColumn;
        m_pColumns->getByName(_rName) >>= xColumn;
        if(_rxDescriptor->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
            _rxDescriptor->getPropertyValue(PROPERTY_DEFAULTVALUE) >>= sNewDefaultValue;
        if(xColumn.is() && xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
            xColumn->getPropertyValue(PROPERTY_DEFAULTVALUE) >>= sDefaultValue;

        if(sNewDefaultValue != sDefaultValue)
        {
            if(sNewDefaultValue.getLength())
            {
                sSql += ::rtl::OUString::createFromAscii(" SET DEFAULT ");
                sSql += sNewDefaultValue;
            }
            else
                sSql += ::rtl::OUString::createFromAscii(" DROP DEFAULT");
            OSL_ENSURE(m_xMetaData->getConnection().is(),"Connection is null!");
            Reference< XStatement > xStmt = m_xMetaData->getConnection()->createStatement(  );
            if(xStmt.is())
                xStmt->execute(sSql);
        }
        else
            // not supported
            throw SQLException(::rtl::OUString::createFromAscii("Driver does not support this function!"),*this,::rtl::OUString::createFromAscii("IM001"),0,Any());
    }
    else
        // not supported
        throw SQLException(::rtl::OUString::createFromAscii("Driver does not support this function!"),*this,::rtl::OUString::createFromAscii("IM001"),0,Any());
    m_pColumns->refresh();
}

//------------------------------------------------------------------------------
void SAL_CALL ODBTable::alterColumnByIndex( sal_Int32 _nIndex, const Reference< XPropertySet >& _rxDescriptor ) throw(SQLException, IndexOutOfBoundsException, RuntimeException)
{
    if(_nIndex < m_pColumns->getCount())
    {
        Reference<XPropertySet> xColumn;
        m_pColumns->getByIndex(_nIndex) >>= xColumn;
        alterColumnByName(::comphelper::getString(xColumn->getPropertyValue(PROPERTY_NAME)),_rxDescriptor);
    }
    else // not supported
        throw SQLException(::rtl::OUString::createFromAscii("Driver does not support this function!"),*this,::rtl::OUString::createFromAscii("IM001"),0,Any());
}
// -------------------------------------------------------------------------
void ODBTable::refreshColumns()
{
    ::std::vector< ::rtl::OUString> aVector;
    
    Reference<XNameAccess> xNames;
    if(!isNew())
    {
        Any aVal;
        if(m_CatalogName.getLength())
            aVal <<= m_CatalogName;
        Reference< XResultSet > xResult = m_xMetaData->getColumns(aVal,
                                        m_SchemaName,m_Name,::rtl::OUString::createFromAscii("%"));

        if(xResult.is())
        {
            Reference< XRow > xRow(xResult,UNO_QUERY);
            while(xResult->next())
                aVector.push_back(xRow->getString(4));
        }

        
    }
    if(!m_pColumns)
    {
        OColumns* pCol = new OColumns(*this, m_aMutex, xNames, isCaseSensitive(), aVector, this,this,
                                    m_xMetaData->supportsAlterTableWithAddColumn(),
                                    m_xMetaData->supportsAlterTableWithDropColumn());
        pCol->setParent(this);

        if(m_pColumns)
            delete m_pColumns;

        m_pColumns	= pCol;	
    }
    else
        m_pColumns->reFill(aVector);

}
// -------------------------------------------------------------------------
void ODBTable::refreshPrimaryKeys(std::vector< ::rtl::OUString>& _rKeys)
{
    Any aVal;
    if(m_CatalogName.getLength())
        aVal <<= m_CatalogName;

    Reference< XResultSet > xResult = m_xMetaData->getPrimaryKeys(aVal,m_SchemaName,m_Name);

    if(xResult.is())
    {
        Reference< XRow > xRow(xResult,UNO_QUERY);
        if(xResult->next()) // there can be only one primary key
        {
            ::rtl::OUString aPkName = xRow->getString(6);
            _rKeys.push_back(aPkName);
        }
    }
}
// -------------------------------------------------------------------------
void ODBTable::refreshForgeinKeys(std::vector< ::rtl::OUString>& _rKeys)
{
    Any aVal;
    if(m_CatalogName.getLength())
        aVal <<= m_CatalogName;

    Reference< XResultSet > xResult = m_xMetaData->getImportedKeys(aVal,m_SchemaName,m_Name);

    if(xResult.is())
    {
        Reference< XRow > xRow(xResult,UNO_QUERY);
        while(xResult->next())
            _rKeys.push_back(xRow->getString(12));
    }
}
// -------------------------------------------------------------------------
void ODBTable::refreshKeys()
{
    ::std::vector< ::rtl::OUString> aVector;
    Reference<XIndexAccess> xKeys;
    if(!isNew())
    {
        try { refreshPrimaryKeys(aVector); }
        catch(SQLException&)
        {	// allowed to fail
            OSL_TRACE("ODBTable::refreshKeys: caught an exception while refreshing the primary keys\n");
        }

        try { refreshForgeinKeys(aVector); }
        catch(SQLException&)
        {	// allowed to fail
            OSL_TRACE("ODBTable::refreshKeys: caught an exception while refreshing the foreign keys\n");
        }
    }
    if(!m_pKeys)
        m_pKeys	= new OKeys(this,m_aMutex,aVector,xKeys);
    else
        m_pKeys->reFill(aVector);
}
// -------------------------------------------------------------------------
void ODBTable::refreshIndexes()
{
    if(!isNew())
    {
        ::std::vector< ::rtl::OUString> aVector;
        Reference<XNameAccess> xNames;
        Any aVal;
        if(m_CatalogName.getLength())
            aVal <<= m_CatalogName;

        // fill indexes
        Reference< XResultSet > xResult = m_xMetaData->getIndexInfo(aVal,m_SchemaName,m_Name,sal_False,sal_False);

        if(xResult.is())
        {
            Reference< XRow > xRow(xResult,UNO_QUERY);
            ::rtl::OUString aName,aDot = ::rtl::OUString::createFromAscii(".");
            while(xResult->next())
            {
                aName = xRow->getString(5);
                if(aName.getLength())
                    aName += aDot;
                aName += xRow->getString(6);
                if(aName.getLength())
                    aVector.push_back(aName);
            }
        }

        if(!m_pIndexes)
            m_pIndexes	= new OIndexes(this,m_aMutex,aVector,xNames);
        else
            m_pIndexes->reFill(aVector);
    }
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL ODBTable::getName() throw(RuntimeException)
{
    ::rtl::OUString aVal;
    dbtools::composeTableName(m_xMetaData,m_CatalogName,m_SchemaName,m_Name,aVal,sal_False);
    return aVal;
}
// -----------------------------------------------------------------------------
sal_Int64 SAL_CALL ODBTable::getSomething( const Sequence< sal_Int8 >& rId ) throw(RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getUnoTunnelImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return (sal_Int64)this;
    return OTable_Base::getSomething(rId);
}
// -----------------------------------------------------------------------------
Sequence< sal_Int8 > ODBTable::getUnoTunnelImplementationId()
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
Reference< XPropertySet > ODBTable::createEmptyObject()
{
    OTableColumnDescriptor* pRet = new OTableColumnDescriptor();
    Reference< XPropertySet > xRet = pRet;
    return xRet;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void SAL_CALL ODBTable::acquire() throw(::com::sun::star::uno::RuntimeException)
{
    OTable_Base::acquire();
}
// -----------------------------------------------------------------------------
void SAL_CALL ODBTable::release() throw(::com::sun::star::uno::RuntimeException)
{
    OTable_Base::release();
}
// -----------------------------------------------------------------------------



