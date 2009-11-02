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

#include "apitools.hxx"
#include "dbastrings.hrc"
#include "definitioncolumn.hxx"
#include "sdbcoretools.hxx"

#include <com/sun/star/beans/PropertyAttribute.hpp>

#include <comphelper/property.hxx>
#include <comphelper/types.hxx>
#include <cppuhelper/typeprovider.hxx>
#include <tools/debug.hxx>
#include <tools/diagnose_ex.h>

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

//------------------------------------------------------------------------------
void OTableColumnDescriptor::impl_registerProperties( const bool _bActAsDescriptor )
{
    sal_Int32 nDefaultAttr = _bActAsDescriptor ? 0 : PropertyAttribute::READONLY;

    registerProperty( PROPERTY_TYPENAME, PROPERTY_ID_TYPENAME, nDefaultAttr, &m_aTypeName, ::getCppuType( &m_aTypeName ) );
    registerProperty( PROPERTY_DESCRIPTION, PROPERTY_ID_DESCRIPTION, nDefaultAttr, &m_aDescription, ::getCppuType( &m_aDescription ) );
    registerProperty( PROPERTY_DEFAULTVALUE, PROPERTY_ID_DEFAULTVALUE, nDefaultAttr, &m_aDefaultValue, ::getCppuType( &m_aDefaultValue ) );

    if ( _bActAsDescriptor )
        registerProperty( PROPERTY_AUTOINCREMENTCREATION, PROPERTY_ID_AUTOINCREMENTCREATION, nDefaultAttr, &m_aAutoIncrementValue, ::getCppuType( &m_aAutoIncrementValue ) );

    registerProperty( PROPERTY_TYPE, PROPERTY_ID_TYPE, nDefaultAttr, &m_nType, ::getCppuType( &m_nType ) );
    registerProperty( PROPERTY_PRECISION, PROPERTY_ID_PRECISION, nDefaultAttr, &m_nPrecision, ::getCppuType( &m_nPrecision ) );
    registerProperty( PROPERTY_SCALE, PROPERTY_ID_SCALE, nDefaultAttr, &m_nScale, ::getCppuType( &m_nScale ) );
    registerProperty( PROPERTY_ISNULLABLE, PROPERTY_ID_ISNULLABLE, nDefaultAttr, &m_nIsNullable, ::getCppuType( &m_nIsNullable ) );
    registerProperty( PROPERTY_ISAUTOINCREMENT, PROPERTY_ID_ISAUTOINCREMENT, nDefaultAttr, &m_bAutoIncrement, ::getCppuType( &m_bAutoIncrement ) );
    registerProperty( PROPERTY_ISROWVERSION, PROPERTY_ID_ISROWVERSION, nDefaultAttr, &m_bRowVersion, ::getCppuType( &m_bRowVersion ) );
    registerProperty( PROPERTY_ISCURRENCY, PROPERTY_ID_ISCURRENCY, nDefaultAttr, &m_bCurrency, ::getCppuType( &m_bCurrency ) );

    OColumnSettings::registerProperties( *this );
}

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
    Sequence< Property > aProps;
    describeProperties( aProps );
    return new ::cppu::OPropertyArrayHelper( aProps );
}

// cppu::OPropertySetHelper
//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OTableColumnDescriptor::getInfoHelper()
{
    return *static_cast< ::comphelper::OPropertyArrayUsageHelper< OTableColumnDescriptor >* >(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
void OTableColumnDescriptor::setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const Any& rValue ) throw (Exception)
{
    OColumn::setFastPropertyValue_NoBroadcast( nHandle, rValue );
    ::dbaccess::notifyDataSourceModified( m_xParent, sal_True );
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

// -------------------------------------------------------------------------
OTableColumn::OTableColumn( const ::rtl::OUString& _rName )
    :OTableColumnDescriptor( false )
{
    DBG_CTOR(OTableColumn,NULL);
    m_sName = _rName;
}

// -------------------------------------------------------------------------
OTableColumn::OTableColumn(const Reference<XPropertySet>& _xColumn)
    :OTableColumnDescriptor( false )
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
        { PROPERTY_CONTROLDEFAULT,   PROPERTY_ID_CONTROLDEFAULT },
        { PROPERTY_HIDDEN,   PROPERTY_ID_HIDDEN }
    };
    for ( size_t i=0; i < sizeof( aProps ) / sizeof( aProps[0] ); ++i )
    {
        if ( xPSI->hasPropertyByName( aProps[i].sName ) )
            OTableColumnDescriptor::setFastPropertyValue_NoBroadcast( aProps[i].nHandle, _xColumn->getPropertyValue( aProps[i].sName ) );
    }
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
    return OTableColumnDescriptor::createArrayHelper();
}

//============================================================
//= OColumnWrapper
//============================================================
DBG_NAME(OColumnWrapper);
//--------------------------------------------------------------------------
OColumnWrapper::OColumnWrapper( const Reference< XPropertySet > & rCol, const bool _bNameIsReadOnly )
    :OColumn( _bNameIsReadOnly )
    ,m_xAggregate(rCol)
    ,m_nColTypeID(-1)
{
    DBG_CTOR(OColumnWrapper,NULL);
    // which type of aggregate property do we have?
    // we distingish the properties by the containment of optional properties
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
// -----------------------------------------------------------------------------
OColumnWrapper::~OColumnWrapper()
{
    DBG_DTOR(OColumnWrapper,NULL);
}

//------------------------------------------------------------------------------
::rtl::OUString OColumnWrapper::impl_getPropertyNameFromHandle( const sal_Int32 _nHandle ) const
{
    ::rtl::OUString sPropName;
    sal_Int16 nAttributes( 0 );
    const_cast< OColumnWrapper* >( this )->getInfoHelper().fillPropertyMembersByHandle( &sPropName, &nAttributes, _nHandle );
    OSL_ENSURE( sPropName.getLength(), "OColumnWrapper::impl_getPropertyNameFromHandle: property not found!" );
    return sPropName;
}

//------------------------------------------------------------------------------
void OColumnWrapper::getFastPropertyValue( Any& rValue, sal_Int32 nHandle ) const
{
    // derived classes are free to either use the OPropertyContainer(Helper) mechanisms for properties,
    // or to declare additional properties which are to be forwarded to the wrapped object. So we need
    // to distinguish those cases.
    if ( OColumn::isRegisteredProperty( nHandle ) )
    {
        OColumn::getFastPropertyValue( rValue, nHandle );
    }
    else
    {
        rValue = m_xAggregate->getPropertyValue( impl_getPropertyNameFromHandle( nHandle ) );
    }
}

//------------------------------------------------------------------------------
sal_Bool OColumnWrapper::convertFastPropertyValue( Any & rConvertedValue, Any & rOldValue, sal_Int32 nHandle,
            const Any& rValue ) throw (IllegalArgumentException)
{
    sal_Bool bModified( sal_False );
    if ( OColumn::isRegisteredProperty( nHandle ) )
    {
        bModified = OColumn::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
    }
    else
    {
        getFastPropertyValue( rOldValue, nHandle );
        if ( rOldValue != rValue )
        {
            rConvertedValue = rValue;
            bModified = sal_True;
        }
    }
    return bModified;
}

//------------------------------------------------------------------------------
void OColumnWrapper::setFastPropertyValue_NoBroadcast( sal_Int32 nHandle, const Any& rValue ) throw (Exception)
{
    if ( OColumn::isRegisteredProperty( nHandle ) )
    {
        OColumn::setFastPropertyValue_NoBroadcast( nHandle, rValue );
    }
    else
    {
        m_xAggregate->setPropertyValue( impl_getPropertyNameFromHandle( nHandle ), rValue );
    }
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
//--------------------------------------------------------------------------
OTableColumnDescriptorWrapper::OTableColumnDescriptorWrapper( const Reference< XPropertySet >& _rCol, const bool _bPureWrap, const bool _bIsDescriptor )
    :OColumnWrapper( _rCol, !_bIsDescriptor )
    ,m_bPureWrap( _bPureWrap )
    ,m_bIsDescriptor( _bIsDescriptor )
{
    // let the ColumnSettings register its properties
    OColumnSettings::registerProperties( *this );
}

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
    const sal_Int32 nHaveAlways = 7;

    // Which optional properties are contained?
    sal_Int32 nHaveOptionally = 0;
    if (nId & HAS_DESCRIPTION)
        ++nHaveOptionally;
    if (nId & HAS_DEFAULTVALUE)
        ++nHaveOptionally;
    if (nId & HAS_ROWVERSION)
        ++nHaveOptionally;
    if ( nId & HAS_AUTOINCREMENT_CREATION )
        ++nHaveOptionally;

    const sal_Int32 nPropertyCount( nHaveAlways + nHaveOptionally );
    Sequence< Property > aTableDescProperties( nPropertyCount );
    Property* pDesc = aTableDescProperties.getArray();
    sal_Int32 nPos = 0;

    DECL_PROP0_BOOL( ISAUTOINCREMENT                );
    DECL_PROP0_BOOL( ISCURRENCY                     );
    DECL_PROP0( ISNULLABLE,         sal_Int32       );
    DECL_PROP0( PRECISION,          sal_Int32		);
    DECL_PROP0( SCALE,              sal_Int32		);
    DECL_PROP0( TYPE,               sal_Int32		);
    DECL_PROP0( TYPENAME,           ::rtl::OUString );

    if ( nId & HAS_AUTOINCREMENT_CREATION )
    {
        DECL_PROP1( AUTOINCREMENTCREATION, ::rtl::OUString, MAYBEVOID );
    }
    if ( nId & HAS_DEFAULTVALUE )
    {
        DECL_PROP0( DEFAULTVALUE, ::rtl::OUString );
    }
    if ( nId & HAS_DESCRIPTION )
    {
        DECL_PROP0( DESCRIPTION, ::rtl::OUString );
    }
    if ( nId & HAS_ROWVERSION )
    {
        DECL_PROP0_BOOL( ISROWVERSION );
    }

    OSL_ENSURE( nPos == nPropertyCount, "OTableColumnDescriptorWrapper::createArrayHelper: something went wrong!" );

    if ( !m_bIsDescriptor )
    {
        for (   Property* prop = aTableDescProperties.getArray();
                prop != aTableDescProperties.getArray() + aTableDescProperties.getLength();
                ++prop
            )
        {
            prop->Attributes |= PropertyAttribute::READONLY;
        }
    }

    // finally also describe the properties which are maintained by our base class, in particular the OPropertyContainerHelper
    Sequence< Property > aBaseProperties;
    describeProperties( aBaseProperties );

    Sequence< Property > aAllProperties( ::comphelper::concatSequences( aTableDescProperties, aBaseProperties ) );
    return new ::cppu::OPropertyArrayHelper( aAllProperties, sal_False );
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
        rValue = m_xAggregate->getPropertyValue( impl_getPropertyNameFromHandle( nHandle ) );
    }
    else
    {
        OColumnWrapper::getFastPropertyValue( rValue, nHandle );
    }
}

//------------------------------------------------------------------------------
sal_Bool OTableColumnDescriptorWrapper::convertFastPropertyValue( Any & rConvertedValue, Any & rOldValue, sal_Int32 nHandle, const Any& rValue ) throw (IllegalArgumentException)
{
    sal_Bool bModified(sal_False);
    if ( m_bPureWrap )
    {
        // do not delegate to OColumnWrapper: It would, for the properties which were registered with registerProperty,
        // ask the OPropertyContainer base class, which is not what we want here.
        // TODO: the whole "m_bPureWrap"-thingie is strange. We should have a dedicated class doing this wrapping,
        // not a class which normally serves other purposes, and only sometimes does a "pure wrap". It makes the
        // code unnecessarily hard to maintain, and error prone.
        rOldValue = m_xAggregate->getPropertyValue( impl_getPropertyNameFromHandle( nHandle ) );
        if ( rOldValue != rValue )
        {
            rConvertedValue = rValue;
            bModified = sal_True;
        }
    }
    else
    {
        bModified = OColumnWrapper::convertFastPropertyValue( rConvertedValue, rOldValue, nHandle, rValue );
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
    {
        m_xAggregate->setPropertyValue( impl_getPropertyNameFromHandle( nHandle ), rValue );
    }
    else
    {
        OColumnWrapper::setFastPropertyValue_NoBroadcast( nHandle, rValue );
    }
}

//============================================================
//= OTableColumnWrapper
//============================================================
//--------------------------------------------------------------------------
OTableColumnWrapper::OTableColumnWrapper( const Reference< XPropertySet >& rCol, const Reference< XPropertySet >& _xColDefintion,
            bool _bPureWrap )
    :OTableColumnDescriptorWrapper( rCol, _bPureWrap, false )
{
    osl_incrementInterlockedCount( &m_refCount );
    if ( _xColDefintion.is() )
    {
        try
        {
            ::comphelper::copyProperties( _xColDefintion, this );
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }
    osl_decrementInterlockedCount( &m_refCount );
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
    return rtl::OUString::createFromAscii( "com.sun.star.sdb.OTableColumnWrapper" );
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
    return OTableColumnDescriptorWrapper::createArrayHelper( nId );
}

