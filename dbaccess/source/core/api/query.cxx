/*************************************************************************
 *
 *	$RCSfile: query.cxx,v $
 *
 *	$Revision: 1.25 $
 *
 *	last change: $Author: rt $ $Date: 2004-01-07 15:44:42 $
 *
 *	The Contents of this file are made available subject to the terms of
 *	either of the following licenses
 *
 *		   - GNU Lesser General Public License Version 2.1
 *		   - Sun Industry Standards Source License Version 1.1
 *
 *	Sun Microsystems Inc., October, 2000
 *
 *	GNU Lesser General Public License Version 2.1
 *	=============================================
 *	Copyright 2000 by Sun Microsystems, Inc.
 *	901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *	This library is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU Lesser General Public
 *	License version 2.1, as published by the Free Software Foundation.
 *
 *	This library is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *	Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public
 *	License along with this library; if not, write to the Free Software
 *	Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *	MA	02111-1307	USA
 *
 *
 *	Sun Industry Standards Source License Version 1.1
 *	=================================================
 *	The contents of this file are subject to the Sun Industry Standards
 *	Source License Version 1.1 (the "License"); You may not use this file
 *	except in compliance with the License. You may obtain a copy of the
 *	License at http://www.openoffice.org/license.html.
 *
 *	Software provided under this License is provided on an "AS IS" basis,
 *	WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *	WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *	MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *	See the License for the specific provisions governing your rights and
 *	obligations concerning the Software.
 *
 *	The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *	Copyright: 2000 by Sun Microsystems, Inc.
 *
 *	All Rights Reserved.
 *
 *	Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _DBA_COREAPI_QUERY_HXX_
#include "query.hxx"
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef DBA_CORE_WARNINGS_HXX
#include "warnings.hxx"
#endif

#ifndef _CPPUHELPER_QUERYINTERFACE_HXX_
#include <cppuhelper/queryinterface.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_AGGREGATION_HXX_
#include <comphelper/propagg.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif

#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_DISPOSEDEXCEPTION_HPP_
#include <com/sun/star/lang/DisposedException.hpp>
#endif
#ifndef _COMPHELPER_TYPES_HXX_ 
#include <comphelper/types.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _DBACORE_DEFINITIONCOLUMN_HXX_
#include "definitioncolumn.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSER_HPP_
#include <com/sun/star/sdb/XSQLQueryComposer.hpp>
#endif

#include <functional>

#ifndef DBACORE_SDBCORETOOLS_HXX
#include "sdbcoretools.hxx"
#endif
#ifndef DBACCESS_CORE_API_QUERYCOMPOSER_HXX
#include "querycomposer.hxx"
#endif

using namespace dbaccess;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::comphelper;
using namespace ::osl;
using namespace ::cppu;
using namespace ::utl;

#define AGG_PROPERTY(handle, propname_out)	\
    static_cast< ::comphelper::OPropertyArrayAggregationHelper* >(const_cast< OQuery* >(this)->getArrayHelper())->fillAggregatePropertyInfoByHandle(&propname_out, NULL, handle)

//........................................................................
namespace dbaccess
{
//........................................................................

    //=====================================================================
    //= helper
    //=====================================================================
    struct TRelease : ::std::unary_function< OQuery::TNameColumnMap::value_type ,void> 
    {
        inline void operator()(const OQuery::TNameColumnMap::value_type& _aType)
        {
            _aType.second->release();
        }
    };

//==========================================================================
//= OQuery
//==========================================================================
DBG_NAME(OQuery)
//--------------------------------------------------------------------------
OQuery::OQuery(const Reference< XPropertySet >& _rxCommandDefinition, const Reference< XConnection >& _rxConn)
    :OConfigurationFlushable(m_aMutex)
    ,OQueryDescriptor(_rxCommandDefinition)
    ,m_bCaseSensitiv(sal_True)
    ,m_xCommandDefinition(_rxCommandDefinition)
    ,m_eDoingCurrently(NONE)
    ,m_xConnection(_rxConn)
    ,m_pWarnings( NULL )
{
    DBG_CTOR(OQuery, NULL);

    DBG_ASSERT(m_xCommandDefinition.is(), "OQuery::OQuery : invalid CommandDefinition object !");
    if (m_xCommandDefinition.is())
    {
        m_xCommandDefinition->addPropertyChangeListener(::rtl::OUString(), this);
        //	m_xCommandDefinition->addPropertyChangeListener(PROPERTY_NAME, this);
        m_xCommandPropInfo = m_xCommandDefinition->getPropertySetInfo();

        // TODO : be a listener on the configuration node which is responsible for my properties not belonging
        // to the CommandDefinition
    }
    DBG_ASSERT(m_xConnection.is(), "OQuery::OQuery : invalid connection !");
}

//--------------------------------------------------------------------------
OQuery::~OQuery()
{
    DBG_DTOR(OQuery, NULL);
}

//--------------------------------------------------------------------------
void SAL_CALL OQuery::acquire(	) throw()
{
    OQueryDescriptor::acquire();
}

//--------------------------------------------------------------------------
void SAL_CALL OQuery::release(	) throw()
{
    OQueryDescriptor::release();
}

// XTypeProvider
//--------------------------------------------------------------------------
Sequence< Type > SAL_CALL OQuery::getTypes() throw (RuntimeException)
{
    return ::comphelper::concatSequences(OQueryDescriptor::getTypes(), OQuery_Base::getTypes(), OConfigurationFlushable::getTypes());
}

// XInterface
//--------------------------------------------------------------------------
Any SAL_CALL OQuery::queryInterface( const Type& _rType ) throw(RuntimeException)
{
    Any aReturn = OQuery_Base::queryInterface(_rType);
    if (!aReturn.hasValue())
        aReturn = OQueryDescriptor::queryInterface(_rType);
    if (!aReturn.hasValue())
        aReturn = OConfigurationFlushable::queryInterface(_rType);
    return aReturn;
}

//--------------------------------------------------------------------------
void OQuery::implCollectColumns( )
{
    try
    {
        // empty the target container
        clearColumns( );

        // fill the columns with columns from the statement
        Reference< XSQLQueryComposerFactory >  xFactory(m_xConnection, UNO_QUERY);
        Reference< XSQLQueryComposer > xComposer;
        if (xFactory.is())
        {
            try
            {
                xComposer = xFactory->createQueryComposer();
            }
            catch (Exception&)
            {
                xComposer = NULL;
            }
        }
        if(xComposer.is())
        {
            xComposer->setQuery(m_sCommand);

            //	xComposer->setFilter(::rtl::OUString::createFromAscii("0=1")); // i21125 
            //	aFilterStatement = m_xComposer->getComposedQuery();
            Reference<XColumnsSupplier> xCols(xComposer,UNO_QUERY);
            Reference< XNameAccess > xColumns = xCols->getColumns();
            if(xColumns.is())
            {
                Sequence< ::rtl::OUString> aNames = xColumns->getElementNames();
                const ::rtl::OUString* pBegin = aNames.getConstArray();
                const ::rtl::OUString* pEnd   = pBegin + aNames.getLength();
                for ( ;pBegin != pEnd; ++pBegin)
                {
                    Reference<XPropertySet> xSource;
                    xColumns->getByName( *pBegin ) >>= xSource;
                    OTableColumn* pColumn = new OTableColumn( xSource );

                    implAppendColumn( *pBegin, pColumn );
                }
            }
        }
    }
    catch( const SQLContext& e )
    {
        if ( m_pWarnings )
            m_pWarnings->appendWarning( e );
    }
    catch( const SQLWarning& e )
    {
        if ( m_pWarnings )
            m_pWarnings->appendWarning( e );
    }
    catch( const SQLException& e )
    {
        if ( m_pWarnings )
            m_pWarnings->appendWarning( e );
    }
    catch( const Exception& )
    {
        DBG_ERROR( "OQuery::implCollectColumns: caught a strange exception!" );
    }
}

//--------------------------------------------------------------------------
void OQuery::rebuildColumns()
{
    implCollectColumns( );
}

// XServiceInfo
//--------------------------------------------------------------------------
IMPLEMENT_SERVICE_INFO3(OQuery, "com.sun.star.sdb.dbaccess.OQuery", SERVICE_SDB_DATASETTINGS, SERVICE_SDB_QUERY, SERVICE_SDB_QUERYDEFINITION)

// ::com::sun::star::beans::XPropertyChangeListener
//--------------------------------------------------------------------------
void SAL_CALL OQuery::propertyChange( const PropertyChangeEvent& _rSource ) throw(RuntimeException)
{
    sal_Int32 nOwnHandle = -1;
    {
        MutexGuard aGuard(m_aMutex);

        DBG_ASSERT(_rSource.Source.get() == Reference< XInterface >(m_xCommandDefinition, UNO_QUERY).get(),
            "OQuery::propertyChange : where did this call come from ?");

        if (m_eDoingCurrently == SETTING_PROPERTIES)
            // we're setting the property ourself, so we will do the neccessary notifications later
            return;

        // forward this to our own member holding a copy of the property value
        if (getArrayHelper()->hasPropertyByName(_rSource.PropertyName))
        {
            Property aOwnProp = getArrayHelper()->getPropertyByName(_rSource.PropertyName);
            nOwnHandle = aOwnProp.Handle;
            OQueryDescriptor::setFastPropertyValue_NoBroadcast(nOwnHandle, _rSource.NewValue);
                // don't use our own setFastPropertyValue_NoBroadcast, this would forward it to the CommandSettings,
                // again
                // and don't use the "real" setPropertyValue, this is to expensive and not sure to succeed
        }
        else
        {
            DBG_ERROR("OQuery::propertyChange : my CommandDefinition has more properties than I do !");
        }
    }

    fire(&nOwnHandle, &_rSource.NewValue, &_rSource.OldValue, 1, sal_False);
}

//--------------------------------------------------------------------------
void SAL_CALL OQuery::disposing( const EventObject& _rSource ) throw (RuntimeException)
{
    MutexGuard aGuard(m_aMutex);

    DBG_ASSERT(_rSource.Source.get() == Reference< XInterface >(m_xCommandDefinition, UNO_QUERY).get(),
        "OQuery::disposing : where did this call come from ?");

    m_xCommandDefinition->removePropertyChangeListener(::rtl::OUString(), this);
    m_xCommandDefinition = NULL;
}

// XDataDescriptorFactory
//--------------------------------------------------------------------------
Reference< XPropertySet > SAL_CALL OQuery::createDataDescriptor(  ) throw(RuntimeException)
{
    return new OQueryDescriptor(*this);
}

// OQueryDescriptor
//--------------------------------------------------------------------------
void OQuery::storeTo( const ::utl::OConfigurationNode& _rConfigLocation )
{
    OQueryDescriptor::storeTo( _rConfigLocation, getDataSourceNumberFormats( m_xConnection ) );
}

//--------------------------------------------------------------------------
void OQuery::loadFrom( const OConfigurationNode& _rConfigLocation )
{
    OQueryDescriptor::loadFrom( _rConfigLocation, getDataSourceNumberFormats( m_xConnection ) );

    m_aConfigurationNode = _rConfigLocation.cloneAsRoot();
}

// OConfigurationFlushable
//--------------------------------------------------------------------------
void OQuery::flush_NoBroadcast_NoCommit()
{
    if (!m_aConfigurationNode.isValid())
        throw DisposedException();

    storeTo( m_aConfigurationNode );
}

// pseudo-XComponent
//--------------------------------------------------------------------------
void SAL_CALL OQuery::dispose()
{
    MutexGuard aGuard(m_aMutex);
    if (m_xCommandDefinition.is())
    {
        m_xCommandDefinition->removePropertyChangeListener(::rtl::OUString(), this);
        m_xCommandDefinition = NULL;
    }
    m_aConfigurationNode.clear();
    OQueryDescriptor::dispose();

    m_pWarnings = NULL;
}

//--------------------------------------------------------------------------
void OQuery::setFastPropertyValue_NoBroadcast( sal_Int32 _nHandle, const Any& _rValue ) throw (Exception)
{
    OQueryDescriptor::setFastPropertyValue_NoBroadcast(_nHandle, _rValue);
    ::rtl::OUString sAggPropName;
    sal_Int16 nAttr = 0;
    if (getInfoHelper().fillPropertyMembersByHandle(&sAggPropName,&nAttr,_nHandle) && 
        m_xCommandPropInfo.is() &&
        m_xCommandPropInfo->hasPropertyByName(sAggPropName))
    {	// the base class holds the property values itself, but we have to forward this to our CommandDefinition

        m_eDoingCurrently = SETTING_PROPERTIES;
        OAutoActionReset(this);
        m_xCommandDefinition->setPropertyValue(sAggPropName, _rValue);

        if ( PROPERTY_ID_COMMAND == _nHandle )
            // the columns are out of date if we are based on a new statement ....
            // 90573 - 16.08.2001 - frank.schoenheit@sun.com
            setColumnsOutOfDate();
    }
}

//--------------------------------------------------------------------------
Reference< XPropertySetInfo > SAL_CALL OQuery::getPropertySetInfo(	) throw(RuntimeException)
{
    return createPropertySetInfo( getInfoHelper() ) ;
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OQuery::getInfoHelper()
{
    return *getArrayHelper();
}

//--------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OQuery::createArrayHelper( ) const
{
    Sequence< Property > aProps;
    // our own props
    describeProperties(aProps);
    return new ::cppu::OPropertyArrayHelper(aProps);
}
// -----------------------------------------------------------------------------
OColumn* OQuery::createColumn(const ::rtl::OUString& _rName) const
{
    return NULL;
}

// -----------------------------------------------------------------------------
::utl::OConfigurationNode OQuery::getObjectLocation() const
{
    return m_aConfigurationNode;
}
// -----------------------------------------------------------------------------
void SAL_CALL OQuery::rename( const ::rtl::OUString& newName ) throw (SQLException, ElementExistException, RuntimeException)
{
    MutexGuard aGuard(m_aMutex);
    Reference<XRename> xRename(m_xCommandDefinition,UNO_QUERY);
    OSL_ENSURE(xRename.is(),"No XRename interface!");
    if(xRename.is())
        xRename->rename(newName);
}

// -----------------------------------------------------------------------------
//........................................................................
}	// namespace dbaccess
//........................................................................

