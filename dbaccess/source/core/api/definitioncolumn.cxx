/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: definitioncolumn.cxx,v $
 * $Revision: 1.26 $
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

#ifndef _DBA_COREAPI_DEFINITIONSETTINGS_HXX_
#include "definitioncolumn.hxx"
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef DBACORE_SDBCORETOOLS_HXX
#include "sdbcoretools.hxx"
#endif


using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::cppu;
using namespace ::comphelper;
using namespace ::osl;
using namespace dbaccess;

#define HAS_DESCRIPTION		        0x00000001
#define HAS_DEFAULTVALUE	        0x00000002
#define HAS_ROWVERSION		        0x00000004
#define HAS_AUTOINCREMENT_CREATION	0x00000008

//============================================================
//= OTableColumnDescriptor
//============================================================
IMPLEMENT_FORWARD_XINTERFACE2(OTableColumnDescriptor,OColumn,TXChild)

// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OTableColumnDescriptor::getImplementationId() throw (RuntimeException)
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

// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OTableColumnDescriptor::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OTableColumnDescriptor");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OTableColumnDescriptor::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMNDESCRIPTOR;
    aSNS[1] = SERVICE_SDB_COLUMNSETTINGS;
    return aSNS;
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OTableColumnDescriptor::createArrayHelper( ) const
{
    BEGIN_PROPERTY_HELPER(20)
        DECL_PROP2(ALIGN,					sal_Int32,			BOUND,MAYBEVOID);
        DECL_PROP1(AUTOINCREMENTCREATION,::rtl::OUString,	MAYBEVOID);
        DECL_PROP2(CONTROLDEFAULT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_IFACE(CONTROLMODEL,		XPropertySet, 		BOUND		);
        DECL_PROP0(DEFAULTVALUE,		::rtl::OUString		);
        DECL_PROP0(DESCRIPTION,			::rtl::OUString		);
        DECL_PROP2(NUMBERFORMAT,			sal_Int32,			BOUND,MAYBEVOID);
        DECL_PROP2(HELPTEXT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_BOOL(HIDDEN,	 							BOUND);
        DECL_PROP0_BOOL(ISAUTOINCREMENT		 				);
        DECL_PROP0_BOOL(ISCURRENCY		 				);
        DECL_PROP0(ISNULLABLE,			sal_Int32			);
        DECL_PROP0_BOOL(ISROWVERSION						);
        DECL_PROP0(NAME,				::rtl::OUString		);
        DECL_PROP0(PRECISION,			sal_Int32			);
        DECL_PROP2(RELATIVEPOSITION,	sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP0(SCALE,				sal_Int32			);
        DECL_PROP0(TYPE,				sal_Int32			);
        DECL_PROP0(TYPENAME,			::rtl::OUString		);
        DECL_PROP2(WIDTH,				sal_Int32,			BOUND, MAYBEVOID);
    END_PROPERTY_HELPER();
}

// cppu::OPropertySetHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OTableColumnDescriptor::getInfoHelper()
{
    return *static_cast< ::comphelper::OPropertyArrayUsageHelper< OTableColumnDescriptor >* >(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OTableColumnDescriptor::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_TYPE:
            rValue <<= m_nType;
            break;
        case PROPERTY_ID_PRECISION:
            rValue <<= m_nPrecision;
            break;
        case PROPERTY_ID_SCALE:
            rValue <<= m_nScale;
            break;
        case PROPERTY_ID_ISNULLABLE:
            rValue <<= m_nIsNullable;
            break;
        case PROPERTY_ID_TYPENAME:
            rValue <<= m_aTypeName;
            break;
        case PROPERTY_ID_DESCRIPTION:
            rValue <<= m_aDescription;
            break;
        case PROPERTY_ID_DEFAULTVALUE:
            rValue <<= m_aDefaultValue;
            break;
        case PROPERTY_ID_AUTOINCREMENTCREATION:
            rValue <<= m_aAutoIncrementValue;
            break;
        case PROPERTY_ID_ISAUTOINCREMENT:
        {
            sal_Bool bVal = m_bAutoIncrement;
            rValue.setValue(&bVal, getBooleanCppuType());
        }	break;
        case PROPERTY_ID_ISCURRENCY:
        {
            sal_Bool bVal = m_bCurrency;
            rValue.setValue(&bVal, getBooleanCppuType());
        }	break;
        case PROPERTY_ID_ISROWVERSION:
        {
            sal_Bool bVal = m_bRowVersion;
            rValue.setValue(&bVal, getBooleanCppuType());
        }	break;
        case PROPERTY_ID_NAME:
            OColumn::getFastPropertyValue( rValue, nHandle );
            break;
        default:
            OColumnSettings::getFastPropertyValue( rValue, nHandle );
    }
}

//------------------------------------------------------------------------------
sal_Bool OTableColumnDescriptor::convertFastPropertyValue(
                            Any & rConvertedValue,
                            Any & rOldValue,
                            sal_Int32 nHandle,
                            const Any& rValue )
                                throw (IllegalArgumentException)
{
    sal_Bool bModified = sal_False;
    switch (nHandle)
    {
        case PROPERTY_ID_TYPE:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_nType);
            break;
        case PROPERTY_ID_PRECISION:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_nPrecision);
            break;
        case PROPERTY_ID_SCALE:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_nScale);
            break;
        case PROPERTY_ID_ISNULLABLE:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_nIsNullable);
            break;
        case PROPERTY_ID_TYPENAME:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aTypeName);
            break;
        case PROPERTY_ID_DESCRIPTION:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aDescription);
            break;
        case PROPERTY_ID_DEFAULTVALUE:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aDefaultValue);
            break;
        case PROPERTY_ID_AUTOINCREMENTCREATION:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_aAutoIncrementValue);
            break;
        case PROPERTY_ID_ISAUTOINCREMENT:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_bAutoIncrement);
            break;
        case PROPERTY_ID_ISCURRENCY:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_bCurrency);
            break;
        case PROPERTY_ID_ISROWVERSION:
            bModified = ::comphelper::tryPropertyValue(rConvertedValue, rOldValue, rValue, m_bRowVersion);
            break;
        case PROPERTY_ID_NAME:
            bModified = OColumn::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
            break;
        default:
            bModified = OColumnSettings::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
    }
    return bModified;
}

//------------------------------------------------------------------------------
void OTableColumnDescriptor::setFastPropertyValue_NoBroadcast(
                                            sal_Int32 nHandle,
                                            const Any& rValue
                                                 )
                                                 throw (Exception)
{
    switch (nHandle)
    {
        case PROPERTY_ID_TYPE:
            OSL_VERIFY( rValue >>= m_nType );
            break;
        case PROPERTY_ID_PRECISION:
            OSL_VERIFY( rValue >>= m_nPrecision );
            break;
        case PROPERTY_ID_SCALE:
            OSL_VERIFY( rValue >>= m_nScale );
            break;
        case PROPERTY_ID_ISNULLABLE:
            OSL_VERIFY( rValue >>= m_nIsNullable );
            break;
        case PROPERTY_ID_TYPENAME:
            OSL_VERIFY( rValue >>= m_aTypeName );
            break;
        case PROPERTY_ID_DESCRIPTION:
            OSL_VERIFY( rValue >>= m_aDescription );
            break;
        case PROPERTY_ID_DEFAULTVALUE:
            OSL_VERIFY( rValue >>= m_aDefaultValue );
            break;
        case PROPERTY_ID_AUTOINCREMENTCREATION:
            OSL_VERIFY( rValue >>= m_aAutoIncrementValue );
            break;
        case PROPERTY_ID_ISAUTOINCREMENT:
            OSL_VERIFY( rValue >>= m_bAutoIncrement );
            break;
        case PROPERTY_ID_ISCURRENCY:
            OSL_VERIFY( rValue >>= m_bCurrency );
            break;
        case PROPERTY_ID_ISROWVERSION:
            OSL_VERIFY( rValue >>= m_bRowVersion );
            break;
        case PROPERTY_ID_NAME:
            OColumn::setFastPropertyValue_NoBroadcast( nHandle, rValue );
            break;
        default:
            OColumnSettings::setFastPropertyValue_NoBroadcast( nHandle, rValue );
    }
    ::dbaccess::notifyDataSourceModified(m_xParent,sal_True);
}

// -----------------------------------------------------------------------------
sal_Int64 SAL_CALL OTableColumnDescriptor::getSomething( const Sequence< sal_Int8 >& aIdentifier ) throw(RuntimeException)
{
    sal_Int64 nReturn = OColumn::getSomething( aIdentifier );
    if ( !nReturn )
        nReturn = OColumnSettings::getSomething( aIdentifier );
    return nReturn;
}

// -----------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OTableColumnDescriptor::getParent(  ) throw (RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_xParent;
}
// -----------------------------------------------------------------------------
void SAL_CALL OTableColumnDescriptor::setParent( const Reference< XInterface >& _xParent ) throw (NoSupportException, RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    m_xParent = _xParent;
}
//============================================================
//= OTableColumn
//============================================================
DBG_NAME(OTableColumn);
OTableColumn::OTableColumn(const ::rtl::OUString& _rName)
{
    DBG_CTOR(OTableColumn,NULL);
    m_sName = _rName;
}
// -------------------------------------------------------------------------
OTableColumn::OTableColumn(const Reference<XPropertySet>& _xColumn) 
{
    DBG_CTOR(OTableColumn,NULL);

    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_TYPENAME ) >>= m_aTypeName );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_ISNULLABLE ) >>= m_nIsNullable );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_PRECISION ) >>= m_nPrecision );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_SCALE ) >>= m_nScale );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_TYPE ) >>= m_nType );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_ISAUTOINCREMENT ) >>= m_bAutoIncrement );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_ISCURRENCY ) >>= m_bCurrency );
    OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_NAME ) >>= m_sName );
    m_bRowVersion = sal_False;

    Reference< XPropertySetInfo > xPSI( _xColumn->getPropertySetInfo(), UNO_SET_THROW );
    if ( xPSI->hasPropertyByName( PROPERTY_DEFAULTVALUE ) )
        OSL_VERIFY( _xColumn->getPropertyValue( PROPERTY_DEFAULTVALUE ) >>= m_aDefaultValue );

    // if the source column also has column settings, copy those
    struct ColumnSettingDescriptor
    {
        ::rtl::OUString sName;
        sal_Int32       nHandle;
    };
    ColumnSettingDescriptor aProps[] =
    {
        { PROPERTY_WIDTH,            PROPERTY_ID_WIDTH },
        { PROPERTY_NUMBERFORMAT,     PROPERTY_ID_NUMBERFORMAT },
        { PROPERTY_RELATIVEPOSITION, PROPERTY_ID_RELATIVEPOSITION },
        { PROPERTY_ALIGN,            PROPERTY_ID_ALIGN },
        { PROPERTY_HELPTEXT,         PROPERTY_ID_HELPTEXT },
        { PROPERTY_CONTROLDEFAULT,   PROPERTY_ID_CONTROLDEFAULT }
    };
    for ( size_t i=0; i < sizeof( aProps ) / sizeof( aProps[0] ); ++i )
    {
        if ( xPSI->hasPropertyByName( aProps[i].sName ) )
            OColumnSettings::setFastPropertyValue_NoBroadcast( aProps[i].nHandle, _xColumn->getPropertyValue( aProps[i].sName ) );
    }

    if ( xPSI->hasPropertyByName( PROPERTY_HIDDEN ) )
        OColumnSettings::setFastPropertyValue_NoBroadcast( PROPERTY_ID_HIDDEN, _xColumn->getPropertyValue( PROPERTY_HIDDEN ) );
}

// -----------------------------------------------------------------------------
OTableColumn::~OTableColumn()
{
    DBG_DTOR(OTableColumn,NULL);
}

// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OTableColumn::getImplementationId() throw (RuntimeException)
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

// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OTableColumn::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OTableColumn");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OTableColumn::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMN;
    aSNS[1] = SERVICE_SDB_COLUMNSETTINGS;
    return aSNS;
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OTableColumn::getInfoHelper()
{
    return *static_cast< ::comphelper::OPropertyArrayUsageHelper< OTableColumn >* >(this)->getArrayHelper();
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OTableColumn::createArrayHelper( ) const
{
    BEGIN_PROPERTY_HELPER(19)
        DECL_PROP2(ALIGN,				sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP2(CONTROLDEFAULT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_IFACE(CONTROLMODEL,	XPropertySet ,		BOUND);
        DECL_PROP1(DEFAULTVALUE,		::rtl::OUString,	READONLY);
        DECL_PROP1(DESCRIPTION,			::rtl::OUString,	READONLY);
        DECL_PROP2(NUMBERFORMAT,		sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP2(HELPTEXT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_BOOL(HIDDEN,	 							BOUND);
        DECL_PROP1_BOOL(ISAUTOINCREMENT,	 				READONLY);
        DECL_PROP1_BOOL(ISCURRENCY,	 				READONLY);
        DECL_PROP1(ISNULLABLE,			sal_Int32,			READONLY);
        DECL_PROP1_BOOL(ISROWVERSION,						READONLY);
        DECL_PROP1(NAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(PRECISION,			sal_Int32,			READONLY);
        DECL_PROP2(RELATIVEPOSITION,	sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP1(SCALE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPENAME,			::rtl::OUString,	READONLY);
        DECL_PROP2(WIDTH,				sal_Int32,			BOUND, MAYBEVOID);
    END_PROPERTY_HELPER();
}

//============================================================
//= OColumnWrapper
//============================================================
DBG_NAME(OColumnWrapper);
//--------------------------------------------------------------------------
OColumnWrapper::OColumnWrapper(const Reference< XPropertySet > & rCol)
               :m_xAggregate(rCol)
               ,m_nColTypeID(-1)
{
    DBG_CTOR(OColumnWrapper,NULL);
    // which type of aggregate property do we have
    if (m_nColTypeID == -1)
    {
        // we distingish the properties by the containment of optional properties, these are:
        // Description	0x0001
        // Hidden		0x0002									    
        // IsRowVersion 0x0004
        m_nColTypeID = 0;
        if ( m_xAggregate.is() )
        {
            Reference <XPropertySetInfo > xInfo(m_xAggregate->getPropertySetInfo());
            m_nColTypeID |= xInfo->hasPropertyByName(PROPERTY_DESCRIPTION) ? HAS_DESCRIPTION : 0;
            m_nColTypeID |= xInfo->hasPropertyByName(PROPERTY_DEFAULTVALUE) ? HAS_DEFAULTVALUE : 0;
            m_nColTypeID |= xInfo->hasPropertyByName(PROPERTY_ISROWVERSION) ? HAS_ROWVERSION : 0;
            m_nColTypeID |= xInfo->hasPropertyByName(PROPERTY_AUTOINCREMENTCREATION) ? HAS_AUTOINCREMENT_CREATION : 0;            

            m_xAggregate->getPropertyValue(PROPERTY_NAME) >>= m_sName;
        }
    }
}
// -----------------------------------------------------------------------------
OColumnWrapper::~OColumnWrapper()
{
    DBG_DTOR(OColumnWrapper,NULL);
}

//------------------------------------------------------------------------------
void OColumnWrapper::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_NAME:
            rValue <<= m_sName;
            break;
        default:
        {
            // get the property name
            ::rtl::OUString aPropName;
            sal_Int16 nAttributes;
            const_cast<OColumnWrapper*>(this)->getInfoHelper().
                        fillPropertyMembersByHandle(&aPropName, &nAttributes, nHandle);
            OSL_ENSURE(aPropName.getLength(), "property not found?");

            // now read the value
            rValue = m_xAggregate->getPropertyValue(aPropName);
        }
    }
}

//------------------------------------------------------------------------------
sal_Bool OColumnWrapper::convertFastPropertyValue(
                            Any & rConvertedValue,
                            Any & rOldValue,
                            sal_Int32 nHandle,
                            const Any& rValue )
                                throw (IllegalArgumentException)
{
    // used for the name
    sal_Bool bModified = OColumn::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );

    // get the property name
    ::rtl::OUString aPropName;
    sal_Int16 nAttributes;
    getInfoHelper().fillPropertyMembersByHandle(&aPropName, &nAttributes, nHandle);
    OSL_ENSURE(aPropName.getLength(), "property not found?");

    // now read the value
    m_xAggregate->setPropertyValue(aPropName, rValue);
    return bModified;
}

//------------------------------------------------------------------------------
void OColumnWrapper::setFastPropertyValue_NoBroadcast(
                                                sal_Int32 nHandle,
                                                const Any& rValue
                                                 )
                                                 throw (Exception)
{
    OColumn::setFastPropertyValue_NoBroadcast( nHandle, rValue );
}
// -----------------------------------------------------------------------------
sal_Int64 SAL_CALL OColumnWrapper::getSomething( const Sequence< sal_Int8 >& aIdentifier ) throw(RuntimeException)
{
    sal_Int64 nRet = OColumn::getSomething(aIdentifier);
    if(!nRet)
    {
        Reference<XUnoTunnel> xTunnel(m_xAggregate,UNO_QUERY);
        if(xTunnel.is())
            nRet = xTunnel->getSomething(aIdentifier);
    }
    return nRet;
}
//============================================================
//= OTableColumnDescriptorWrapper
//============================================================
// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OTableColumnDescriptorWrapper::getImplementationId() throw (RuntimeException)
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

// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OTableColumnDescriptorWrapper::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OTableColumnDescriptorWrapper");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OTableColumnDescriptorWrapper::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMNDESCRIPTOR;
    aSNS[1] = SERVICE_SDB_COLUMNSETTINGS;
    return aSNS;
}

// -----------------------------------------------------------------------------
sal_Int64 SAL_CALL OTableColumnDescriptorWrapper::getSomething( const Sequence< sal_Int8 >& aIdentifier ) throw(RuntimeException)
{
    sal_Int64 nReturn = OColumnWrapper::getSomething( aIdentifier );
    if ( !nReturn )
        nReturn = OColumnSettings::getSomething( aIdentifier );
    return nReturn;
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OTableColumnDescriptorWrapper::createArrayHelper( sal_Int32 nId ) const
{
    // BEGIN_PROPERTY_HELPER(17)
    sal_Int32 nPropertyCount = 16;
    // How many properties do we have?
    // Which optional properties are contained?
    if (nId & HAS_DESCRIPTION)
        ++nPropertyCount;
    if (nId & HAS_DEFAULTVALUE)
        ++nPropertyCount;
    if (nId & HAS_ROWVERSION)
        ++nPropertyCount;
    if ( nId & HAS_AUTOINCREMENT_CREATION )
        ++nPropertyCount;

    Sequence< Property> aDescriptor(nPropertyCount);
    Property* pDesc = aDescriptor.getArray();
    sal_Int32 nPos = 0;

    //		Description, Defaultvalue, IsRowVersion
        DECL_PROP2(ALIGN,					sal_Int32,			BOUND,MAYBEVOID);
        if ( nId & HAS_AUTOINCREMENT_CREATION )
        {
            DECL_PROP1(AUTOINCREMENTCREATION,::rtl::OUString,	MAYBEVOID);
        }
        DECL_PROP2(CONTROLDEFAULT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_IFACE(CONTROLMODEL,		XPropertySet, 		BOUND		);
        if (nId & HAS_DEFAULTVALUE)
        {
            DECL_PROP0(DEFAULTVALUE,	::rtl::OUString );
        }

        if (nId & HAS_DESCRIPTION)
        {
            DECL_PROP0(DESCRIPTION,		::rtl::OUString );
        }

        DECL_PROP2(NUMBERFORMAT,			sal_Int32,			BOUND,MAYBEVOID);
        DECL_PROP2(HELPTEXT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_BOOL(HIDDEN,	 							BOUND);
        DECL_PROP0_BOOL(ISAUTOINCREMENT 	 				);
        DECL_PROP0_BOOL(ISCURRENCY 	 						);		
        DECL_PROP0(ISNULLABLE,			sal_Int32			);

        if (nId & HAS_ROWVERSION)
        {
            DECL_PROP0_BOOL(ISROWVERSION					);
        }

        DECL_PROP0(NAME,				::rtl::OUString 	);
        DECL_PROP0(PRECISION,			sal_Int32			);
        DECL_PROP2(RELATIVEPOSITION,	sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP0(SCALE,				sal_Int32			);
        DECL_PROP0(TYPE,				sal_Int32			);
        DECL_PROP0(TYPENAME,			::rtl::OUString 	);
        DECL_PROP1(WIDTH,				sal_Int32,			MAYBEVOID);
    END_PROPERTY_HELPER();
}

// cppu::OPropertySetHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OTableColumnDescriptorWrapper::getInfoHelper()
{
    return *static_cast< OIdPropertyArrayUsageHelper< OTableColumnDescriptorWrapper >* >(this)->getArrayHelper(m_nColTypeID);
}

//------------------------------------------------------------------------------
void OTableColumnDescriptorWrapper::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    if ( m_bPureWrap )
    {
        // get the property name
        ::rtl::OUString aPropName;
        sal_Int16 nAttributes;
        const_cast<OTableColumnDescriptorWrapper*>(this)->getInfoHelper().
            fillPropertyMembersByHandle(&aPropName, &nAttributes, nHandle);
        OSL_ENSURE(aPropName.getLength(), "property not found?");

        // now read the value
        rValue = m_xAggregate->getPropertyValue(aPropName);
    }
    else
    {
        switch (nHandle)
        {
            case PROPERTY_ID_ALIGN:
            case PROPERTY_ID_NUMBERFORMAT:
            case PROPERTY_ID_RELATIVEPOSITION:
            case PROPERTY_ID_WIDTH:
            case PROPERTY_ID_HIDDEN:
            case PROPERTY_ID_CONTROLMODEL:
            case PROPERTY_ID_HELPTEXT:
            case PROPERTY_ID_CONTROLDEFAULT:
                OColumnSettings::getFastPropertyValue( rValue, nHandle );
                break;
            default:
            {
                // get the property name
                ::rtl::OUString aPropName;
                sal_Int16 nAttributes;
                const_cast<OTableColumnDescriptorWrapper*>(this)->getInfoHelper().
                    fillPropertyMembersByHandle(&aPropName, &nAttributes, nHandle);
                OSL_ENSURE(aPropName.getLength(), "property not found?");

                // now read the value
                rValue = m_xAggregate->getPropertyValue(aPropName);
            }
        }
    }
}

//------------------------------------------------------------------------------
sal_Bool OTableColumnDescriptorWrapper::convertFastPropertyValue(
                            Any & rConvertedValue,
                            Any & rOldValue,
                            sal_Int32 nHandle,
                            const Any& rValue )
                                throw (IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    if ( m_bPureWrap )
        bModified = OColumnWrapper::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
    else
    {
        switch (nHandle)
        {
            case PROPERTY_ID_ALIGN:
            case PROPERTY_ID_NUMBERFORMAT:
            case PROPERTY_ID_RELATIVEPOSITION:
            case PROPERTY_ID_WIDTH:
            case PROPERTY_ID_HIDDEN:
            case PROPERTY_ID_CONTROLMODEL:
            case PROPERTY_ID_HELPTEXT:
            case PROPERTY_ID_CONTROLDEFAULT:
                bModified = OColumnSettings::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
                break;
            default:
                bModified = OColumnWrapper::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
        }
    }
    return bModified;
}

//------------------------------------------------------------------------------
void OTableColumnDescriptorWrapper::setFastPropertyValue_NoBroadcast(
                                                sal_Int32 nHandle,
                                                const Any& rValue
                                                 )
                                                 throw (Exception)
{
    if ( m_bPureWrap )
        OColumnWrapper::setFastPropertyValue_NoBroadcast( nHandle, rValue );
    else
    {
        switch (nHandle)
        {
            case PROPERTY_ID_ALIGN:
            case PROPERTY_ID_NUMBERFORMAT:
            case PROPERTY_ID_RELATIVEPOSITION:
            case PROPERTY_ID_WIDTH:
            case PROPERTY_ID_HIDDEN:
            case PROPERTY_ID_CONTROLMODEL:
            case PROPERTY_ID_HELPTEXT:
            case PROPERTY_ID_CONTROLDEFAULT:
                OColumnSettings::setFastPropertyValue_NoBroadcast( nHandle, rValue );
                break;
            default:
                OColumnWrapper::setFastPropertyValue_NoBroadcast( nHandle, rValue );
        }
    }
}

//============================================================
//= OTableColumnWrapper
//============================================================
//--------------------------------------------------------------------------
OTableColumnWrapper::OTableColumnWrapper(const Reference< XPropertySet >& rCol
                                        ,const Reference< XPropertySet >& _xColDefintion
                                        ,sal_Bool _bPureWrap)
    :OTableColumnDescriptorWrapper(rCol,_bPureWrap) 
{
    osl_incrementInterlockedCount(&m_refCount);
    if ( _xColDefintion.is() )
    {
        try
        {
            ::comphelper::copyProperties(_xColDefintion,this);
        }
        catch(Exception&)
        {
            OSL_ENSURE(sal_False, "OTableColumnWrapper::OTableColumnWrapper: caught an exception!");
        }
    }
    osl_decrementInterlockedCount(&m_refCount);
}

//--------------------------------------------------------------------------
OTableColumnWrapper::~OTableColumnWrapper()
{
}

// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OTableColumnWrapper::getImplementationId() throw (RuntimeException)
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
// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OTableColumnWrapper::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OTableColumnWrapper");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OTableColumnWrapper::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMN;
    aSNS[1] = SERVICE_SDB_COLUMNSETTINGS;
    return aSNS;
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OTableColumnWrapper::getInfoHelper()
{
    return *static_cast< OIdPropertyArrayUsageHelper< OTableColumnWrapper >* >(this)->getArrayHelper(m_nColTypeID);
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OTableColumnWrapper::createArrayHelper( sal_Int32 nId ) const
{
    // BEGIN_PROPERTY_HELPER(17)
    sal_Int32 nPropertyCount = 16;
    // How many properties do we have?
    // Which optional properties are contained?
    if (nId & HAS_DESCRIPTION)
        nPropertyCount++;
    if (nId & HAS_DEFAULTVALUE)
        nPropertyCount++;
    if (nId & HAS_ROWVERSION)
        nPropertyCount++;
    if ( nId & HAS_AUTOINCREMENT_CREATION )
        ++nPropertyCount;

    Sequence< Property> aDescriptor(nPropertyCount);
    Property* pDesc = aDescriptor.getArray();
    sal_Int32 nPos = 0;

    //		Description, Defaultvalue, IsRowVersion
        DECL_PROP2(ALIGN,				sal_Int32,			BOUND, MAYBEVOID);
        if ( nId & HAS_AUTOINCREMENT_CREATION )
        {
            DECL_PROP1(AUTOINCREMENTCREATION,::rtl::OUString,	MAYBEVOID);
        }
        DECL_PROP2(CONTROLDEFAULT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_IFACE(CONTROLMODEL,	XPropertySet ,		BOUND);
        if (nId & HAS_DEFAULTVALUE)
        {
            DECL_PROP1(DEFAULTVALUE,		::rtl::OUString,	READONLY);
        }

        if (nId & HAS_DESCRIPTION)
        {
            DECL_PROP1(DESCRIPTION,			::rtl::OUString,	READONLY);
        }

        DECL_PROP2(NUMBERFORMAT,		sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP2(HELPTEXT,			::rtl::OUString,	BOUND,MAYBEVOID);
        DECL_PROP1_BOOL(HIDDEN,	 							BOUND);
        DECL_PROP1_BOOL(ISAUTOINCREMENT,	 				READONLY);
        DECL_PROP1_BOOL(ISCURRENCY,			 				READONLY);
        
        DECL_PROP1(ISNULLABLE,			sal_Int32,			READONLY);

        if (nId & HAS_ROWVERSION)
        {
            DECL_PROP1_BOOL(ISROWVERSION,						READONLY);
        }

        DECL_PROP1(NAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(PRECISION,			sal_Int32,			READONLY);
        DECL_PROP2(RELATIVEPOSITION,	sal_Int32,			BOUND, MAYBEVOID);
        DECL_PROP1(SCALE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPENAME,			::rtl::OUString,	READONLY);
        DECL_PROP2(WIDTH,				sal_Int32,			BOUND, MAYBEVOID);
    END_PROPERTY_HELPER();
}

//============================================================
//= OIndexColumnWrapper
//============================================================
// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OIndexColumnWrapper::getImplementationId() throw (RuntimeException)
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
// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OIndexColumnWrapper::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OIndexColumnWrapper");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OIndexColumnWrapper::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMN;
    aSNS[1] = SERVICE_SDBCX_INDEXCOLUMN;
    return aSNS;
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OIndexColumnWrapper::getInfoHelper()
{
    return *static_cast< OPropertyArrayUsageHelper< OIndexColumnWrapper >* >(this)->getArrayHelper();
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OIndexColumnWrapper::createArrayHelper() const
{
    BEGIN_PROPERTY_HELPER(9)
        DECL_PROP1_BOOL(ISASCENDING,	 				READONLY);
        DECL_PROP1_BOOL(ISAUTOINCREMENT,	 				READONLY);
        DECL_PROP1_BOOL(ISCURRENCY,	 				READONLY);
        DECL_PROP1(ISNULLABLE,			sal_Int32,			READONLY);
        DECL_PROP1(NAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(PRECISION,			sal_Int32,			READONLY);
        DECL_PROP1(SCALE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPENAME,			::rtl::OUString,	READONLY);
    END_PROPERTY_HELPER();
}

//------------------------------------------------------------------------------
void OIndexColumnWrapper::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_ISASCENDING:
        {
            sal_Bool bVal = m_bAscending;
            rValue.setValue(&bVal, getBooleanCppuType());
        }	break;
        default:
            OColumnWrapper::getFastPropertyValue( rValue, nHandle );
    }
}

//============================================================
//= OKeyColumnWrapper
//============================================================
// com::sun::star::lang::XTypeProvider
//--------------------------------------------------------------------------
Sequence< sal_Int8 > OKeyColumnWrapper::getImplementationId() throw (RuntimeException)
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
// ::com::sun::star::lang::XServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OKeyColumnWrapper::getImplementationName(  ) throw (RuntimeException)
{
    return rtl::OUString::createFromAscii("com.sun.star.sdb.OIndexColumnWrapper");
}

//------------------------------------------------------------------------------
Sequence< ::rtl::OUString > OKeyColumnWrapper::getSupportedServiceNames(  ) throw (RuntimeException)
{
    Sequence< ::rtl::OUString > aSNS( 2 );
    aSNS[0] = SERVICE_SDBCX_COLUMN;
    aSNS[1] = SERVICE_SDBCX_KEYCOLUMN;
    return aSNS;
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OKeyColumnWrapper::getInfoHelper()
{
    return *static_cast< OPropertyArrayUsageHelper< OKeyColumnWrapper >* >(this)->getArrayHelper();
}

// comphelper::OPropertyArrayUsageHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OKeyColumnWrapper::createArrayHelper() const
{
    BEGIN_PROPERTY_HELPER(9)
        DECL_PROP1_BOOL(ISAUTOINCREMENT,	 				READONLY);
        DECL_PROP1_BOOL(ISCURRENCY,	 				READONLY);
        DECL_PROP1(ISNULLABLE,			sal_Int32,			READONLY);
        DECL_PROP1(NAME,				::rtl::OUString,	READONLY);
        DECL_PROP1(PRECISION,			sal_Int32,			READONLY);
        DECL_PROP1(RELATEDCOLUMN,		::rtl::OUString,	READONLY);
        DECL_PROP1(SCALE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPE,				sal_Int32,			READONLY);
        DECL_PROP1(TYPENAME,			::rtl::OUString,	READONLY);
    END_PROPERTY_HELPER();
}

//------------------------------------------------------------------------------
void OKeyColumnWrapper::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    switch (nHandle)
    {
        case PROPERTY_ID_RELATEDCOLUMN:
            rValue <<= m_aRelatedColumn;
            break;
        default:
            OColumnWrapper::getFastPropertyValue( rValue, nHandle );
    }
}


