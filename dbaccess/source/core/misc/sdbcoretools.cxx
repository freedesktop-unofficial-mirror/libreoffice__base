/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sdbcoretools.cxx,v $
 * $Revision: 1.10 $
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

#include "sdbcoretools.hxx"
#include "dbastrings.hrc"

/** === begin UNO includes === **/
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/container/XChild.hpp>
#include <com/sun/star/util/XModifiable.hpp>
#include <com/sun/star/sdb/XDocumentDataSource.hpp>
#include <com/sun/star/task/XInteractionRequestStringResolver.hpp>
/** === end UNO includes === **/

#include <tools/diagnose_ex.h>
#include <tools/debug.hxx>
#include <comphelper/componentcontext.hxx>
#include <comphelper/interaction.hxx>
#include <rtl/ref.hxx>
#include <rtl/ustrbuf.hxx>

//.........................................................................
namespace dbaccess
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::util;
    using namespace ::com::sun::star::sdbc;
    using namespace ::com::sun::star::sdb;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::task;
    using namespace ::com::sun::star::container;

    // =========================================================================
    // -------------------------------------------------------------------------
    void notifyDataSourceModified(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxObject,sal_Bool _bModified)
    {
        Reference< XInterface > xDs = getDataSource( _rxObject );
        Reference<XDocumentDataSource> xDocumentDataSource(xDs,UNO_QUERY);
        if ( xDocumentDataSource.is() )
            xDs = xDocumentDataSource->getDatabaseDocument();
        Reference< XModifiable > xModi( xDs, UNO_QUERY );
        if ( xModi.is() )
            xModi->setModified(_bModified);
    }

    // -------------------------------------------------------------------------
    Reference< XInterface > getDataSource( const Reference< XInterface >& _rxDependentObject )
    {
        Reference< XInterface > xParent = _rxDependentObject;
        Reference< XInterface > xReturn;
        while( xParent.is() )
        {
            xReturn = xParent;
            Reference<XChild> xChild(xParent,UNO_QUERY);
            xParent.set(xChild.is() ? xChild->getParent() : Reference< XInterface >(),UNO_QUERY);
        }
        return xReturn;
    }

    // -------------------------------------------------------------------------
    bool getDataSourceSetting( const Reference< XInterface >& _rxDataSource, const sal_Char* _pAsciiSettingsName,
        Any& /* [out] */ _rSettingsValue )
    {
        bool bIsPresent = false;
        try
        {
            Reference< XPropertySet > xDataSource( _rxDataSource, UNO_QUERY );
            OSL_ENSURE( xDataSource.is(), "getDataSourceSetting: invalid data source object!" );
            if ( !xDataSource.is() )
                return false;

            Sequence< PropertyValue > aSettings;
            OSL_VERIFY( xDataSource->getPropertyValue( PROPERTY_INFO ) >>= aSettings );
            const PropertyValue* pSetting = aSettings.getConstArray();
            const PropertyValue* pSettingEnd = aSettings.getConstArray() + aSettings.getLength();
            for ( ; pSetting != pSettingEnd; ++pSetting )
            {
                if ( pSetting->Name.equalsAscii( _pAsciiSettingsName ) )
                {
                    _rSettingsValue = pSetting->Value;
                    bIsPresent = true;
                    break;
                }
            }
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "getDataSourceSetting: caught an exception!" );
        }
        return bIsPresent;
    }

// -----------------------------------------------------------------------------
    ::rtl::OUString extractExceptionMessage( const ::comphelper::ComponentContext& _rContext, const Any& _rError )
    {
        ::rtl::OUString sDisplayMessage;

        try
        {
            Reference< XInteractionRequestStringResolver > xStringResolver;
            if ( _rContext.createComponent( "com.sun.star.task.InteractionRequestStringResolver", xStringResolver ) )
            {
                ::rtl::Reference< ::comphelper::OInteractionRequest > pRequest( new ::comphelper::OInteractionRequest( _rError ) );
                ::rtl::Reference< ::comphelper::OInteractionApprove > pApprove( new ::comphelper::OInteractionApprove );
                pRequest->addContinuation( pApprove.get() );
                Optional< ::rtl::OUString > aMessage = xStringResolver->getStringFromInformationalRequest( pRequest.get() );
                if ( aMessage.IsPresent )
                    sDisplayMessage = aMessage.Value;
            }
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }

        if ( !sDisplayMessage.getLength() )
        {
            Exception aExcept;
            _rError >>= aExcept;

            ::rtl::OUStringBuffer aBuffer;
            aBuffer.append( _rError.getValueTypeName() );
            aBuffer.appendAscii( ":\n" );
            aBuffer.append( aExcept.Message );

            sDisplayMessage = aBuffer.makeStringAndClear();
        }

        return sDisplayMessage;
    }

// -----------------------------------------------------------------------------
//.........................................................................
}	// namespace dbaccess
//.........................................................................

