/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
#include "precompiled_reportdesign.hxx"

#include "formatnormalizer.hxx"
#include "RptModel.hxx"

/** === begin UNO includes === **/
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#include <com/sun/star/sdb/XParametersSupplier.hpp>
#include <com/sun/star/util/XNumberFormatTypes.hpp>
/** === end UNO includes === **/

#include <dbaccess/dbsubcomponentcontroller.hxx>
#include <unotools/syslocale.hxx>
#include <connectivity/statementcomposer.hxx>
#include <connectivity/dbtools.hxx>
#include <tools/diagnose_ex.h>

//........................................................................
namespace rptui
{
//........................................................................

    /** === begin UNO using === **/
    using ::com::sun::star::uno::Reference;
    using ::com::sun::star::report::XReportDefinition;
    using ::com::sun::star::report::XFormattedField;
    using ::com::sun::star::uno::UNO_QUERY;
    using ::com::sun::star::sdb::XSingleSelectQueryComposer;
    using ::com::sun::star::sdbcx::XColumnsSupplier;
    using ::com::sun::star::container::XIndexAccess;
    using ::com::sun::star::beans::XPropertySet;
    using ::com::sun::star::uno::UNO_QUERY_THROW;
    using ::com::sun::star::uno::Exception;
    using ::com::sun::star::sdb::XParametersSupplier;
    using ::com::sun::star::sdbc::SQLException;
    using ::com::sun::star::util::XNumberFormatsSupplier;
    using ::com::sun::star::util::XNumberFormatTypes;
    using ::com::sun::star::uno::makeAny;
    /** === end UNO using === **/

    //====================================================================
    //= FormatNormalizer
    //====================================================================
    DBG_NAME(rpt_FormatNormalizer)    
    //--------------------------------------------------------------------
    FormatNormalizer::FormatNormalizer( const OReportModel& _rModel )
        :m_rModel( _rModel )
        ,m_xReportDefinition( )
        ,m_bFieldListDirty( true )
    {
        DBG_CTOR(rpt_FormatNormalizer,NULL);        
    }

    //--------------------------------------------------------------------
    FormatNormalizer::~FormatNormalizer()
    {
        DBG_DTOR(rpt_FormatNormalizer,NULL);        
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::notifyPropertyChange( const ::com::sun::star::beans::PropertyChangeEvent& _rEvent )
    {
        if ( !impl_lateInit() )
            return;

        if ( ( _rEvent.Source == m_xReportDefinition ) && m_xReportDefinition.is() )
        {
            impl_onDefinitionPropertyChange( _rEvent.PropertyName );
            return;
        }

        Reference< XFormattedField > xFormatted( _rEvent.Source, UNO_QUERY );
        if ( xFormatted.is() )
            impl_onFormattedProperttyChange( xFormatted, _rEvent.PropertyName );
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::notifyElementInserted( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxElement )
    {
        if ( !impl_lateInit() )
            return;

        Reference< XFormattedField > xFormatted( _rxElement, UNO_QUERY );
        if ( !xFormatted.is() )
            return;

        impl_adjustFormatToDataFieldType_nothrow( xFormatted );
    }

    //--------------------------------------------------------------------
    bool FormatNormalizer::impl_lateInit()
    {
        if ( m_xReportDefinition.is() )
            return true;

        m_xReportDefinition = m_rModel.getReportDefinition();
        return m_xReportDefinition.is();
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::impl_onDefinitionPropertyChange( const ::rtl::OUString& _rChangedPropName )
    {
        if  (   !_rChangedPropName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "Command" ) )
            &&  !_rChangedPropName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "CommandType" ) )
            &&  !_rChangedPropName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "EscapeProcessing" ) )
            )
            // nothing we're interested in
            return;
        m_bFieldListDirty = true;
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::impl_onFormattedProperttyChange( const Reference< XFormattedField >& _rxFormatted, const ::rtl::OUString& _rChangedPropName )
    {
        if  ( !_rChangedPropName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM( "DataField" ) ) )
            // nothing we're interested in
            return;

        impl_adjustFormatToDataFieldType_nothrow( _rxFormatted );
    }

    //--------------------------------------------------------------------
    namespace
    {
        void lcl_collectFields_throw( const Reference< XIndexAccess >& _rxColumns, FormatNormalizer::FieldList& _inout_rFields )
        {
            try
            {
                sal_Int32 nCount( _rxColumns->getCount() );
                _inout_rFields.reserve( _inout_rFields.size() + (size_t)nCount );

                Reference< XPropertySet > xColumn;
                FormatNormalizer::Field aField;

                for ( sal_Int32 i=0; i<nCount; ++i )
                {
                    xColumn.set( _rxColumns->getByIndex( i ), UNO_QUERY_THROW );
                    OSL_VERIFY( xColumn->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Name"       ) ) ) >>= aField.sName       );
                    OSL_VERIFY( xColumn->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Type"       ) ) ) >>= aField.nDataType   );
                    OSL_VERIFY( xColumn->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Scale"      ) ) ) >>= aField.nScale      );
                    OSL_VERIFY( xColumn->getPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "IsCurrency" ) ) ) >>= aField.bIsCurrency );
                    _inout_rFields.push_back( aField );
                }
            }
            catch( const Exception& )
            {
                DBG_UNHANDLED_EXCEPTION();
            }
        }
    }

    //--------------------------------------------------------------------
    bool FormatNormalizer::impl_ensureUpToDateFieldList_nothrow()
    {
        if ( !m_bFieldListDirty )
            return true;
        m_aFields.resize( 0 );

        OSL_PRECOND( m_xReportDefinition.is(), "FormatNormalizer::impl_ensureUpToDateFieldList_nothrow: no report definition!" );
        if ( !m_xReportDefinition.is() )
            return false;

        ::dbaui::DBSubComponentController* pController( m_rModel.getController() );
        OSL_ENSURE( pController, "FormatNormalizer::impl_ensureUpToDateFieldList_nothrow: no controller? how can *this* happen?!" );
        if ( !pController )
            return false;

        try
        {
            ::dbtools::StatementComposer aComposer( pController->getConnection(), m_xReportDefinition->getCommand(),
                m_xReportDefinition->getCommandType(), m_xReportDefinition->getEscapeProcessing() );

            Reference< XSingleSelectQueryComposer > xComposer( aComposer.getComposer() );
            if ( !xComposer.is() )
                return false;


            Reference< XColumnsSupplier > xSuppCols( xComposer, UNO_QUERY_THROW );
            Reference< XIndexAccess > xColumns( xSuppCols->getColumns(), UNO_QUERY_THROW );
            lcl_collectFields_throw( xColumns, m_aFields );

            Reference< XParametersSupplier > xSuppParams( xComposer, UNO_QUERY_THROW );
            Reference< XIndexAccess > xParams( xSuppParams->getParameters(), UNO_QUERY_THROW );
            lcl_collectFields_throw( xParams, m_aFields );
        }
        catch( const SQLException& )
        {
            // silence it. This might happen for instance when the user sets an non-existent table,
            // or things like this
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }

        m_bFieldListDirty = false;
        return true;
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::impl_adjustFormatToDataFieldType_nothrow( const Reference< XFormattedField >& _rxFormatted )
    {
        if ( !impl_ensureUpToDateFieldList_nothrow() )
            // unable to obtain a recent field list
            return;

        try
        {
            sal_Int32 nFormatKey = _rxFormatted->getFormatKey();
            if ( nFormatKey != 0 )
                // it's not the "standard numeric" format -> not interested in
                return;

            ::rtl::OUString sDataField( _rxFormatted->getDataField() );
            const ::rtl::OUString sFieldPrefix( RTL_CONSTASCII_USTRINGPARAM( "field:[" ) );
            if ( sDataField.indexOf( sFieldPrefix ) != 0 )
                // not bound to a table field
                // TODO: we might also do this kind of thing for functions and expressions ...
                return;
            if ( sDataField.getStr()[ sDataField.getLength() - 1 ] != ']' )
            {
                // last character is not the closing brace
                OSL_FAIL( "FormatNormalizer::impl_adjustFormatToDataFieldType_nothrow: suspicious data field value!" );
                return;
            }
            sDataField = sDataField.copy( sFieldPrefix.getLength(), sDataField.getLength() - sFieldPrefix.getLength() - 1 );

            FieldList::const_iterator field = m_aFields.begin();
            for ( ; field != m_aFields.end(); ++field )
            {
                if ( field->sName == sDataField )
                    break;
            }
            if ( field == m_aFields.end() )
                // unknown field
                return;

            Reference< XNumberFormatsSupplier >  xSuppNumFmts( _rxFormatted->getFormatsSupplier(), UNO_QUERY_THROW );
            Reference< XNumberFormatTypes > xNumFmtTypes( xSuppNumFmts->getNumberFormats(), UNO_QUERY_THROW );

            nFormatKey = ::dbtools::getDefaultNumberFormat( field->nDataType, field->nScale, field->bIsCurrency, xNumFmtTypes,
                SvtSysLocale().GetLocaleData().getLocale() );
            _rxFormatted->setFormatKey( nFormatKey );
        }
        catch( const Exception& )
        {
            DBG_UNHANDLED_EXCEPTION();
        }
    }

//........................................................................
} // namespace rptui
//........................................................................

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
