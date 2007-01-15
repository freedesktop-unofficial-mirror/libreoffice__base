/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: datasettings.cxx,v $
 *
 *  $Revision: 1.25 $
 *
 *  last change: $Author: vg $ $Date: 2007-01-15 14:30:31 $
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

#ifndef _DBA_CORE_DATASETTINGS_HXX_
#include "datasettings.hxx"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _DBA_CORE_PROPERTYHELPER_HXX_
#include "propertyhelper.hxx"
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWEIGHT_HPP_
#include <com/sun/star/awt/FontWeight.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTEMPHASISMARK_HPP_
#include <com/sun/star/awt/FontEmphasisMark.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTRELIEF_HPP_
#include <com/sun/star/awt/FontRelief.hpp>
#endif

#ifndef _COM_SUN_STAR_AWT_FONTWIDTH_HPP_
#include <com/sun/star/awt/FontWidth.hpp>
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::beans;
using namespace ::comphelper;
using namespace ::cppu;

//........................................................................
namespace dbaccess
{
//........................................................................
float ConvertFontWeight( ::FontWeight eWeight )
{
    if( eWeight == WEIGHT_DONTKNOW )
        return ::com::sun::star::awt::FontWeight::DONTKNOW;
    else if( eWeight == WEIGHT_THIN )
        return ::com::sun::star::awt::FontWeight::THIN;
    else if( eWeight == WEIGHT_ULTRALIGHT )
        return ::com::sun::star::awt::FontWeight::ULTRALIGHT;
    else if( eWeight == WEIGHT_LIGHT )
        return ::com::sun::star::awt::FontWeight::LIGHT;
    else if( eWeight == WEIGHT_SEMILIGHT )
        return ::com::sun::star::awt::FontWeight::SEMILIGHT;
    else if( ( eWeight == WEIGHT_NORMAL ) || ( eWeight == WEIGHT_MEDIUM ) )
        return ::com::sun::star::awt::FontWeight::NORMAL;
    else if( eWeight == WEIGHT_SEMIBOLD )
        return ::com::sun::star::awt::FontWeight::SEMIBOLD;
    else if( eWeight == WEIGHT_BOLD )
        return ::com::sun::star::awt::FontWeight::BOLD;
    else if( eWeight == WEIGHT_ULTRABOLD )
        return ::com::sun::star::awt::FontWeight::ULTRABOLD;
    else if( eWeight == WEIGHT_BLACK )
        return ::com::sun::star::awt::FontWeight::BLACK;

    OSL_ENSURE(0, "Unknown FontWeigth" );
    return ::com::sun::star::awt::FontWeight::DONTKNOW;
}
// -----------------------------------------------------------------------------
float ConvertFontWidth( ::FontWidth eWidth )
{
    if( eWidth == WIDTH_DONTKNOW )
        return ::com::sun::star::awt::FontWidth::DONTKNOW;
    else if( eWidth == WIDTH_ULTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::ULTRACONDENSED;
    else if( eWidth == WIDTH_EXTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::EXTRACONDENSED;
    else if( eWidth == WIDTH_CONDENSED )
        return ::com::sun::star::awt::FontWidth::CONDENSED;
    else if( eWidth == WIDTH_SEMI_CONDENSED )
        return ::com::sun::star::awt::FontWidth::SEMICONDENSED;
    else if( eWidth == WIDTH_NORMAL )
        return ::com::sun::star::awt::FontWidth::NORMAL;
    else if( eWidth == WIDTH_SEMI_EXPANDED )
        return ::com::sun::star::awt::FontWidth::SEMIEXPANDED;
    else if( eWidth == WIDTH_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXPANDED;
    else if( eWidth == WIDTH_EXTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXTRAEXPANDED;
    else if( eWidth == WIDTH_ULTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::ULTRAEXPANDED;
    
    OSL_ENSURE(0, "Unknown FontWidth" );
    return ::com::sun::star::awt::FontWidth::DONTKNOW;
}
//------------------------------------------------------------------
::com::sun::star::awt::FontDescriptor ImplCreateFontDescriptor( const Font& rFont )
{
    ::com::sun::star::awt::FontDescriptor aFD;
    aFD.Name			= rFont.GetName();
    aFD.StyleName		= rFont.GetStyleName();
    aFD.Height			= (sal_Int16)rFont.GetSize().Height();
    aFD.Width			= (sal_Int16)rFont.GetSize().Width();
    aFD.Family			= (sal_Int16)rFont.GetFamily();
    aFD.CharSet			= rFont.GetCharSet();
    aFD.Pitch			= (sal_Int16)rFont.GetPitch();
    aFD.CharacterWidth	= ConvertFontWidth( rFont.GetWidthType() );
    aFD.Weight			= ConvertFontWeight( rFont.GetWeight() );
    aFD.Slant			= (::com::sun::star::awt::FontSlant)rFont.GetItalic();
    aFD.Underline		= (sal_Int16)rFont.GetUnderline();
    aFD.Strikeout		= (sal_Int16)rFont.GetStrikeout();
    aFD.Orientation		= rFont.GetOrientation();
    aFD.Kerning			= rFont.IsKerning();
    aFD.WordLineMode	= rFont.IsWordLineMode();
    aFD.Type			= 0;   // ??? => Nur an Metric...
    return aFD;
}


//==========================================================================
//= ODataSettings
//==========================================================================
//--------------------------------------------------------------------------
void ODataSettings::registerPropertiesFor(ODataSettings_Base* _pItem)
{
    if ( m_bQuery )
    {
        registerProperty(PROPERTY_HAVING_CLAUSE, PROPERTY_ID_HAVING_CLAUSE, PropertyAttribute::BOUND,
                    &_pItem->m_sHavingClause, ::getCppuType(&_pItem->m_sHavingClause));

        registerProperty(PROPERTY_GROUP_BY, PROPERTY_ID_GROUP_BY, PropertyAttribute::BOUND,
                    &_pItem->m_sGroupBy, ::getCppuType(&_pItem->m_sGroupBy));
    }

    registerProperty(PROPERTY_FILTER, PROPERTY_ID_FILTER, PropertyAttribute::BOUND,
                    &_pItem->m_sFilter, ::getCppuType(&_pItem->m_sFilter));

    registerProperty(PROPERTY_ORDER, PROPERTY_ID_ORDER, PropertyAttribute::BOUND,
                    &_pItem->m_sOrder, ::getCppuType(&_pItem->m_sOrder));

    registerProperty(PROPERTY_APPLYFILTER, PROPERTY_ID_APPLYFILTER, PropertyAttribute::BOUND,
                    &_pItem->m_bApplyFilter, ::getBooleanCppuType());

    registerProperty(PROPERTY_FONT, PROPERTY_ID_FONT, PropertyAttribute::BOUND,
                    &_pItem->m_aFont, ::getCppuType(&_pItem->m_aFont));

    registerMayBeVoidProperty(PROPERTY_ROW_HEIGHT, PROPERTY_ID_ROW_HEIGHT, PropertyAttribute::BOUND | PropertyAttribute::MAYBEVOID,
                    &_pItem->m_aRowHeight, ::getCppuType(static_cast<sal_Int32*>(NULL)));

    registerMayBeVoidProperty(PROPERTY_TEXTCOLOR, PROPERTY_ID_TEXTCOLOR, PropertyAttribute::BOUND | PropertyAttribute::MAYBEVOID,
                    &_pItem->m_aTextColor, ::getCppuType(static_cast<sal_Int32*>(NULL)));

    registerMayBeVoidProperty(PROPERTY_TEXTLINECOLOR, PROPERTY_ID_TEXTLINECOLOR, PropertyAttribute::BOUND | PropertyAttribute::MAYBEVOID,
                    &_pItem->m_aTextLineColor, ::getCppuType(static_cast<sal_Int32*>(NULL)));

    registerProperty(PROPERTY_TEXTEMPHASIS, PROPERTY_ID_TEXTEMPHASIS, PropertyAttribute::BOUND,
        &_pItem->m_nFontEmphasis, ::getCppuType(&_pItem->m_nFontEmphasis));

    registerProperty(PROPERTY_TEXTRELIEF, PROPERTY_ID_TEXTRELIEF, PropertyAttribute::BOUND,&_pItem->m_nFontRelief, ::getCppuType(&_pItem->m_nFontRelief));

    registerProperty(PROPERTY_FONTNAME,			PROPERTY_ID_FONTNAME,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Name,			::getCppuType(&_pItem->m_aFont.Name));
    registerProperty(PROPERTY_FONTHEIGHT,		PROPERTY_ID_FONTHEIGHT,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Height,			::getCppuType(&_pItem->m_aFont.Height));
    registerProperty(PROPERTY_FONTWIDTH,		PROPERTY_ID_FONTWIDTH,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Width,			::getCppuType(&_pItem->m_aFont.Width));
    registerProperty(PROPERTY_FONTSTYLENAME,	PROPERTY_ID_FONTSTYLENAME,	 PropertyAttribute::BOUND,&_pItem->m_aFont.StyleName,		::getCppuType(&_pItem->m_aFont.StyleName));
    registerProperty(PROPERTY_FONTFAMILY,		PROPERTY_ID_FONTFAMILY,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Family,			::getCppuType(&_pItem->m_aFont.Family));
    registerProperty(PROPERTY_FONTCHARSET,		PROPERTY_ID_FONTCHARSET,	 PropertyAttribute::BOUND,&_pItem->m_aFont.CharSet,			::getCppuType(&_pItem->m_aFont.CharSet));
    registerProperty(PROPERTY_FONTPITCH,		PROPERTY_ID_FONTPITCH,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Pitch,			::getCppuType(&_pItem->m_aFont.Pitch));
    registerProperty(PROPERTY_FONTCHARWIDTH,	PROPERTY_ID_FONTCHARWIDTH,	 PropertyAttribute::BOUND,&_pItem->m_aFont.CharacterWidth,	::getCppuType(&_pItem->m_aFont.CharacterWidth));
    registerProperty(PROPERTY_FONTWEIGHT,		PROPERTY_ID_FONTWEIGHT,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Weight,			::getCppuType(&_pItem->m_aFont.Weight));
    registerProperty(PROPERTY_FONTSLANT,		PROPERTY_ID_FONTSLANT,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Slant,			::getCppuType(&_pItem->m_aFont.Slant));
    registerProperty(PROPERTY_FONTUNDERLINE,	PROPERTY_ID_FONTUNDERLINE,	 PropertyAttribute::BOUND,&_pItem->m_aFont.Underline,		::getCppuType(&_pItem->m_aFont.Underline));
    registerProperty(PROPERTY_FONTSTRIKEOUT,	PROPERTY_ID_FONTSTRIKEOUT,	 PropertyAttribute::BOUND,&_pItem->m_aFont.Strikeout,		::getCppuType(&_pItem->m_aFont.Strikeout));
    registerProperty(PROPERTY_FONTORIENTATION,	PROPERTY_ID_FONTORIENTATION, PropertyAttribute::BOUND,&_pItem->m_aFont.Orientation,		::getCppuType(&_pItem->m_aFont.Orientation));
    registerProperty(PROPERTY_FONTKERNING,		PROPERTY_ID_FONTKERNING,	 PropertyAttribute::BOUND,&_pItem->m_aFont.Kerning,			::getCppuType(&_pItem->m_aFont.Kerning));
    registerProperty(PROPERTY_FONTWORDLINEMODE, PROPERTY_ID_FONTWORDLINEMODE,PropertyAttribute::BOUND,&_pItem->m_aFont.WordLineMode,	::getCppuType(&_pItem->m_aFont.WordLineMode));
    registerProperty(PROPERTY_FONTTYPE,			PROPERTY_ID_FONTTYPE,		 PropertyAttribute::BOUND,&_pItem->m_aFont.Type,			::getCppuType(&_pItem->m_aFont.Type));
}

//--------------------------------------------------------------------------
ODataSettings::ODataSettings(OBroadcastHelper& _rBHelper,sal_Bool _bQuery)
    :OPropertyStateContainer(_rBHelper)
    ,ODataSettings_Base()
    ,m_bQuery(_bQuery)
{
}

//--------------------------------------------------------------------------
ODataSettings::ODataSettings(const ODataSettings& _rSource, ::cppu::OBroadcastHelper& _rBHelper,sal_Bool _bQuery)
    :OPropertyStateContainer(_rBHelper)
    ,ODataSettings_Base(_rSource)
    ,m_bQuery(_bQuery)
{
}

//--------------------------------------------------------------------------
ODataSettings_Base::ODataSettings_Base()
    :m_bApplyFilter(sal_False)
    ,m_aFont(::comphelper::getDefaultFont())
    ,m_nFontEmphasis(::com::sun::star::awt::FontEmphasisMark::NONE)
    ,m_nFontRelief(::com::sun::star::awt::FontRelief::NONE)
{
}

//--------------------------------------------------------------------------
ODataSettings_Base::ODataSettings_Base(const ODataSettings_Base& _rSource)
{
    m_sFilter		= _rSource.m_sFilter;
    m_sHavingClause	= _rSource.m_sHavingClause;
    m_sGroupBy		= _rSource.m_sGroupBy;
    m_sOrder		= _rSource.m_sOrder;
    m_bApplyFilter	= _rSource.m_bApplyFilter;
    m_aFont			= _rSource.m_aFont;
    m_aRowHeight	= _rSource.m_aRowHeight;
    m_aTextColor	= _rSource.m_aTextColor;
    m_aTextLineColor= _rSource.m_aTextLineColor;
    m_nFontEmphasis	= _rSource.m_nFontEmphasis;
    m_nFontRelief	= _rSource.m_nFontRelief;
}
// -----------------------------------------------------------------------------
void ODataSettings::getPropertyDefaultByHandle( sal_Int32 _nHandle, Any& _rDefault ) const
{
    static ::com::sun::star::awt::FontDescriptor aFD = ::comphelper::getDefaultFont();
    switch( _nHandle )
    {
        case PROPERTY_ID_HAVING_CLAUSE:
        case PROPERTY_ID_GROUP_BY:
        case PROPERTY_ID_FILTER:
        case PROPERTY_ID_ORDER:
            _rDefault <<= ::rtl::OUString();
            break;
        case PROPERTY_ID_FONT:
            _rDefault <<= ::comphelper::getDefaultFont();
            break;
        case PROPERTY_ID_APPLYFILTER:
            _rDefault <<= sal_False;
            break;
        case PROPERTY_ID_TEXTRELIEF:
            _rDefault <<= ::com::sun::star::awt::FontRelief::NONE;
            break;
        case PROPERTY_ID_TEXTEMPHASIS:
            _rDefault <<= ::com::sun::star::awt::FontEmphasisMark::NONE;
            break;
        case PROPERTY_ID_FONTNAME:
            _rDefault <<= aFD.Name;
            break;
        case PROPERTY_ID_FONTHEIGHT:
            _rDefault <<= aFD.Height;
            break;
        case PROPERTY_ID_FONTWIDTH:
            _rDefault <<= aFD.Width;
            break;
        case PROPERTY_ID_FONTSTYLENAME:
            _rDefault <<= aFD.StyleName;
            break;
        case PROPERTY_ID_FONTFAMILY:
            _rDefault <<= aFD.Family;
            break;
        case PROPERTY_ID_FONTCHARSET:
            _rDefault <<= aFD.CharSet;
            break;
        case PROPERTY_ID_FONTPITCH:
            _rDefault <<= aFD.Pitch;
            break;
        case PROPERTY_ID_FONTCHARWIDTH:
            _rDefault <<= aFD.CharacterWidth;
            break;
        case PROPERTY_ID_FONTWEIGHT:
            _rDefault <<= aFD.Weight;
            break;
        case PROPERTY_ID_FONTSLANT:
            _rDefault <<= aFD.Slant; 
            break;
        case PROPERTY_ID_FONTUNDERLINE:
            _rDefault <<= aFD.Underline;
            break;
        case PROPERTY_ID_FONTSTRIKEOUT:
            _rDefault <<= aFD.Strikeout;
            break;
        case PROPERTY_ID_FONTORIENTATION:
            _rDefault <<= aFD.Orientation;
            break;
        case PROPERTY_ID_FONTKERNING:
            _rDefault <<= aFD.Kerning;
            break;
        case PROPERTY_ID_FONTWORDLINEMODE:
            _rDefault <<= aFD.WordLineMode;
            break;
        case PROPERTY_ID_FONTTYPE:
            _rDefault <<= aFD.Type;
            break;
    }
}
//........................................................................
}	// namespace dbaccess
//........................................................................

