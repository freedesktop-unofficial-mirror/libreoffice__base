/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: formatnormalizer.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:16 $
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

#include "formatnormalizer.hxx"
#include "RptModel.hxx"

/** === begin UNO includes === **/
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XPARAMETERSSUPPLIER_HPP_
#include <com/sun/star/sdb/XParametersSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
/** === end UNO includes === **/

#include <dbaccess/singledoccontroller.hxx>
#include <svtools/syslocale.hxx>
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
    /** === end UNO using === **/

    //====================================================================
    //= FormatNormalizer
    //====================================================================
    //--------------------------------------------------------------------
    FormatNormalizer::FormatNormalizer( const OReportModel& _rModel )
        :m_rModel( _rModel )
        ,m_xReportDefinition( )
        ,m_bFieldListDirty( true )
    {
    }

    //--------------------------------------------------------------------
    FormatNormalizer::~FormatNormalizer()
    {
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
        if  (   !_rChangedPropName.equalsAscii( "Command" )
            &&  !_rChangedPropName.equalsAscii( "CommandType" )
            &&  !_rChangedPropName.equalsAscii( "EscapeProcessing" )
            )
            // nothing we're interested in
            return;
        m_bFieldListDirty = true;
    }

    //--------------------------------------------------------------------
    void FormatNormalizer::impl_onFormattedProperttyChange( const Reference< XFormattedField >& _rxFormatted, const ::rtl::OUString& _rChangedPropName )
    {
        if  ( !_rChangedPropName.equalsAscii( "DataField" ) )
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

        ::dbaui::OSingleDocumentController* pController( m_rModel.getController() );
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
                OSL_ENSURE( false, "FormatNormalizer::impl_adjustFormatToDataFieldType_nothrow: suspicious data field value!" );
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
