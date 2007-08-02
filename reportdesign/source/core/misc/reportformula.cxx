/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: reportformula.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2007-08-02 14:31:39 $
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
#include "precompiled_reportdesign.hxx"
#include "reportformula.hxx"

/** === begin UNO includes === **/
/** === end UNO includes === **/

#include <rtl/ustrbuf.hxx>

//........................................................................
namespace rptui
{
//........................................................................

    /** === begin UNO using === **/
    using ::com::sun::star::uno::Any;
    /** === end UNO using === **/

    namespace
    {
        //----------------------------------------------------------------
        const ::rtl::OUString&  lcl_getExpressionPrefix( sal_Int32* _pTakeLengthOrNull = NULL )
        {
            static ::rtl::OUString s_sPrefix( RTL_CONSTASCII_USTRINGPARAM( "rpt:" ) );
            if ( _pTakeLengthOrNull )
                *_pTakeLengthOrNull = s_sPrefix.getLength();
            return s_sPrefix;
        }

        //----------------------------------------------------------------
        const ::rtl::OUString&  lcl_getFieldPrefix( sal_Int32* _pTakeLengthOrNull = NULL )
        {
            static ::rtl::OUString s_sPrefix( RTL_CONSTASCII_USTRINGPARAM( "field:" ) );
            if ( _pTakeLengthOrNull )
                *_pTakeLengthOrNull = s_sPrefix.getLength();
            return s_sPrefix;
        }
    }

    //====================================================================
    //= ReportFormula
    //====================================================================
    //--------------------------------------------------------------------
    ReportFormula::ReportFormula()
        :m_eType( Invalid )
    {
    }

    //--------------------------------------------------------------------
    ReportFormula::ReportFormula( const ::rtl::OUString& _rFormula )
        :m_eType( Invalid )
    {
        impl_construct( _rFormula );
    }

    //--------------------------------------------------------------------
    ReportFormula::ReportFormula( const Any& _rWrappedFormula )
        :m_eType( Invalid )
    {
        ::rtl::OUString sFormula;
        OSL_VERIFY( _rWrappedFormula >>= sFormula );
        impl_construct( sFormula );
    }

    //--------------------------------------------------------------------
    ReportFormula::ReportFormula( const BindType _eType, const ::rtl::OUString& _rFieldOrExpression )
        :m_eType( _eType )
    {
        switch ( m_eType )
        {
        case Expression:
        {
            if ( _rFieldOrExpression.indexOf( lcl_getExpressionPrefix() ) == 0 )
                m_sCompleteFormula = _rFieldOrExpression;
            else
                m_sCompleteFormula = lcl_getExpressionPrefix() + _rFieldOrExpression;
        }
        break;

        case Field:
        {
            ::rtl::OUStringBuffer aBuffer;
            aBuffer.append( lcl_getFieldPrefix() );
            aBuffer.appendAscii( "[" );
            aBuffer.append( _rFieldOrExpression );
            aBuffer.appendAscii( "]" );
            m_sCompleteFormula = aBuffer.makeStringAndClear();
        }
        break;
        default:
            OSL_ENSURE( false, "ReportFormula::ReportFormula: illegal bind type!" );
            return;
        }

        m_sUndecoratedContent = _rFieldOrExpression;
    }

    //--------------------------------------------------------------------
    void ReportFormula::impl_construct( const ::rtl::OUString& _rFormula )
    {
        m_sCompleteFormula = _rFormula;

        sal_Int32 nPrefixLen( -1 );
        // is it an ordinary expression?
        if ( m_sCompleteFormula.indexOf( lcl_getExpressionPrefix( &nPrefixLen ) ) == 0 )
        {
            m_eType = Expression;
            m_sUndecoratedContent = m_sCompleteFormula.copy( nPrefixLen );
            return;
        }

        /// does it refer to a field?
        if ( m_sCompleteFormula.indexOf( lcl_getFieldPrefix( &nPrefixLen ) ) == 0 )
        {
            if  (   ( m_sCompleteFormula.getLength() >= nPrefixLen + 2 )
                &&  ( m_sCompleteFormula[ nPrefixLen ] == '[' )
                &&  ( m_sCompleteFormula[ m_sCompleteFormula.getLength() - 1 ] == ']' )
                )
            {
                m_eType = Field;
                m_sUndecoratedContent = m_sCompleteFormula.copy( nPrefixLen + 1, m_sCompleteFormula.getLength() - nPrefixLen - 2 );
                return;
            }
        }

        m_eType = Invalid;
    }

    //--------------------------------------------------------------------
    ::rtl::OUString ReportFormula::getBracketedFieldOrExpression() const
    {
        bool bIsField = ( getType() == Field );
        ::rtl::OUStringBuffer aFieldContent;
        if ( bIsField )
            aFieldContent.appendAscii( "[" ); 
        aFieldContent.append( getUndecoratedContent() );
        if ( bIsField )
            aFieldContent.appendAscii( "]" );

        return aFieldContent.makeStringAndClear();
    }

//........................................................................
} // namespace rptui
//........................................................................

