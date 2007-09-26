/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlControlProperty.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-09-26 14:21:17 $
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

#ifndef RPT_XMLCONTROLPROPERTY_HXX
#include "xmlControlProperty.hxx"
#endif
#ifndef _XMLOFF_XMLUCONV_HXX
#include <xmloff/xmluconv.hxx>
#endif
#ifndef RPT_XMLFILTER_HXX
#include "xmlfilter.hxx"
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <xmloff/xmltoken.hxx>
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include <xmloff/nmspmap.hxx>
#endif
#ifndef RPT_XMLENUMS_HXX
#include "xmlEnums.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _DATETIME_HXX
#include <tools/datetime.hxx>
#endif
#ifndef _UNOTOOLS_DATETIME_HXX_
#include <unotools/datetime.hxx>
#endif
#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif

#define TYPE_DATE		1
#define TYPE_TIME		2
#define TYPE_DATETIME	3

namespace rptxml
{
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::xml::sax;

DBG_NAME( rpt_OXMLControlProperty )

OXMLControlProperty::OXMLControlProperty( ORptFilter& rImport
                ,sal_uInt16 nPrfx
                ,const ::rtl::OUString& _sLocalName
                ,const Reference< XAttributeList > & _xAttrList
                ,const Reference< XPropertySet >& _xControl
                ,OXMLControlProperty* _pContainer) :
    SvXMLImportContext( rImport, nPrfx, _sLocalName )
    ,m_xControl(_xControl)
    ,m_pContainer(_pContainer)
    ,m_bIsList(sal_False)
{
    DBG_CTOR( rpt_OXMLControlProperty,NULL);

    m_aPropType = ::getVoidCppuType();

    OSL_ENSURE(_xAttrList.is(),"Attribute list is NULL!");
    OSL_ENSURE(m_xControl.is(),"Control is NULL!");
    
    const SvXMLNamespaceMap& rMap = rImport.GetNamespaceMap();
    const SvXMLTokenMap& rTokenMap = rImport.GetControlPropertyElemTokenMap();

    const sal_Int16 nLength = (_xAttrList.is()) ? _xAttrList->getLength() : 0;
    for(sal_Int16 i = 0; i < nLength; ++i)
    {
     ::rtl::OUString sLocalName;
        const rtl::OUString sAttrName = _xAttrList->getNameByIndex( i );
        const sal_uInt16 nPrefix = rMap.GetKeyByAttrName( sAttrName,&sLocalName );
        rtl::OUString sValue = _xAttrList->getValueByIndex( i );

        switch( rTokenMap.Get( nPrefix, sLocalName ) )
        {
            case XML_TOK_LIST_PROPERTY:
                m_bIsList = sValue.equalsAscii("true");
                break;
            case XML_TOK_VALUE_TYPE:
                {
                    // needs to be translated into a ::com::sun::star::uno::Type
                    DECLARE_STL_USTRINGACCESS_MAP( ::com::sun::star::uno::Type, MapString2Type );
                    static MapString2Type s_aTypeNameMap;
                    if (!s_aTypeNameMap.size())
                    {
                        s_aTypeNameMap[GetXMLToken( XML_BOOLEAN)]	= ::getBooleanCppuType();
                        s_aTypeNameMap[GetXMLToken( XML_FLOAT)]		= ::getCppuType( static_cast< double* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_DOUBLE)]	= ::getCppuType( static_cast< double* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_STRING)]	= ::getCppuType( static_cast< ::rtl::OUString* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_INT)]		= ::getCppuType( static_cast< sal_Int32* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_SHORT)]		= ::getCppuType( static_cast< sal_Int16* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_DATE)]		= ::getCppuType( static_cast< com::sun::star::util::Date* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_TIME)]		= ::getCppuType( static_cast< com::sun::star::util::Time* >(NULL) );
                        s_aTypeNameMap[GetXMLToken( XML_VOID)]		= ::getVoidCppuType();
                    }

                    const ConstMapString2TypeIterator aTypePos = s_aTypeNameMap.find(sValue);
                    OSL_ENSURE(s_aTypeNameMap.end() != aTypePos, "OXMLControlProperty::OXMLControlProperty: invalid type!");
                    if (s_aTypeNameMap.end() != aTypePos)
                        m_aPropType = aTypePos->second;
                }
                break;
            case XML_TOK_PROPERTY_NAME:
                m_aSetting.Name = sValue;
                break;
            default:
                break;
        }
    }
    
}
// -----------------------------------------------------------------------------

OXMLControlProperty::~OXMLControlProperty()
{
    DBG_DTOR( rpt_OXMLControlProperty,NULL);
}
// -----------------------------------------------------------------------------
SvXMLImportContext* OXMLControlProperty::CreateChildContext(
        sal_uInt16 nPrefix,
        const ::rtl::OUString& rLocalName,
        const Reference< XAttributeList > & xAttrList )
{
    SvXMLImportContext *pContext = 0;
    ORptFilter& rImport = GetOwnImport();
    const SvXMLTokenMap&	rTokenMap	= rImport.GetControlPropertyElemTokenMap();

    switch( rTokenMap.Get( nPrefix, rLocalName ) )
    {
        case XML_TOK_LIST_PROPERTY:
            rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
            pContext = new OXMLControlProperty( rImport, nPrefix, rLocalName,xAttrList,m_xControl);
            break;
        case XML_TOK_VALUE:
            rImport.GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
            pContext = new OXMLControlProperty( rImport, nPrefix, rLocalName,xAttrList,m_xControl,this );
            break;
        default:
            break;
    }

    if( !pContext )
        pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );

    return pContext;
}
// -----------------------------------------------------------------------------
void OXMLControlProperty::EndElement()
{
    if ( m_aSetting.Name.getLength() && m_xControl.is() )
    {
        if ( m_bIsList && !m_aSequence.getLength() )
            m_aSetting.Value <<= m_aSequence;
        try
        {
            m_xControl->setPropertyValue(m_aSetting.Name,m_aSetting.Value);
        }
        catch(const Exception&)
        {
            OSL_ENSURE(0,"Unknown property found!");
        }
    }
}
// -----------------------------------------------------------------------------
void OXMLControlProperty::Characters( const ::rtl::OUString& rChars )
{
    if ( m_pContainer )
        m_pContainer->addValue(rChars);
}
// -----------------------------------------------------------------------------
void OXMLControlProperty::addValue(const ::rtl::OUString& _sValue)
{
    Any aValue;
    if( TypeClass_VOID != m_aPropType.getTypeClass() )
        aValue = convertString(m_aPropType, _sValue);

    if ( !m_bIsList )
        m_aSetting.Value = aValue;
    else 
    {
        sal_Int32 nPos = m_aSequence.getLength();
        m_aSequence.realloc(nPos+1);
        m_aSequence[nPos] = aValue;
    }
}
// -----------------------------------------------------------------------------
ORptFilter& OXMLControlProperty::GetOwnImport()
{
    return static_cast<ORptFilter&>(GetImport());
}
// -----------------------------------------------------------------------------
Any OXMLControlProperty::convertString(const ::com::sun::star::uno::Type& _rExpectedType, const ::rtl::OUString& _rReadCharacters)
{
    ORptFilter& rImporter = GetOwnImport();
    Any aReturn;
    switch (_rExpectedType.getTypeClass())
    {
        case TypeClass_BOOLEAN:		// sal_Bool
        {
            sal_Bool bValue;
        #if OSL_DEBUG_LEVEL > 0
            sal_Bool bSuccess =
        #endif
            rImporter.GetMM100UnitConverter().convertBool(bValue, _rReadCharacters);
            OSL_ENSURE(bSuccess,
                    ::rtl::OString("OXMLControlProperty::convertString: could not convert \"")
                +=	::rtl::OString(_rReadCharacters.getStr(), _rReadCharacters.getLength(), RTL_TEXTENCODING_ASCII_US)
                +=	::rtl::OString("\" into a boolean!"));
            aReturn <<= bValue;
        }
        break;
        case TypeClass_SHORT:		// sal_Int16
        case TypeClass_LONG:		// sal_Int32
            {	// it's a real int32/16 property
                sal_Int32 nValue(0);
        #if OSL_DEBUG_LEVEL > 0
                sal_Bool bSuccess =
        #endif
                rImporter.GetMM100UnitConverter().convertNumber(nValue, _rReadCharacters);
                OSL_ENSURE(bSuccess,
                        ::rtl::OString("OXMLControlProperty::convertString: could not convert \"")
                    +=	::rtl::OString(_rReadCharacters.getStr(), _rReadCharacters.getLength(), RTL_TEXTENCODING_ASCII_US)
                    +=	::rtl::OString("\" into an integer!"));
                if (TypeClass_SHORT == _rExpectedType.getTypeClass())
                    aReturn <<= (sal_Int16)nValue;
                else
                    aReturn <<= (sal_Int32)nValue;
                break;
            }
        case TypeClass_HYPER:
        {
            OSL_ENSURE(sal_False, "OXMLControlProperty::convertString: 64-bit integers not implemented yet!");
        }
        break;
        case TypeClass_DOUBLE:
        {
            double nValue = 0.0;
        #if OSL_DEBUG_LEVEL > 0
            sal_Bool bSuccess =
        #endif
            rImporter.GetMM100UnitConverter().convertDouble(nValue, _rReadCharacters);
            OSL_ENSURE(bSuccess,
                    ::rtl::OString("OXMLControlProperty::convertString: could not convert \"")
                +=	::rtl::OString(_rReadCharacters.getStr(), _rReadCharacters.getLength(), RTL_TEXTENCODING_ASCII_US)
                +=	::rtl::OString("\" into a double!"));
            aReturn <<= (double)nValue;
        }
        break;
        case TypeClass_STRING:
            aReturn <<= _rReadCharacters;
            break;
        case TypeClass_STRUCT:
            {
                // recognized structs:
                static ::com::sun::star::uno::Type s_aDateType		= ::getCppuType(static_cast< ::com::sun::star::util::Date* >(NULL));
                static ::com::sun::star::uno::Type s_aTimeType		= ::getCppuType(static_cast< ::com::sun::star::util::Time* >(NULL));
                static ::com::sun::star::uno::Type s_aDateTimeType	= ::getCppuType(static_cast< ::com::sun::star::util::DateTime* >(NULL));
                sal_Int32 nType = 0;
                if	( _rExpectedType.equals(s_aDateType) ) 
                    nType = TYPE_DATE;
                else if ( _rExpectedType.equals(s_aTimeType) )
                    nType = TYPE_TIME;
                else if ( _rExpectedType.equals(s_aDateTimeType) )
                    nType = TYPE_DATETIME;
                if ( !nType )
                {
                    // first extract the double
                    double nValue = 0;
                #if OSL_DEBUG_LEVEL > 0
                    sal_Bool bSuccess =
                #endif
                    rImporter.GetMM100UnitConverter().convertDouble(nValue, _rReadCharacters);
                    OSL_ENSURE(bSuccess,
                            ::rtl::OString("OPropertyImport::convertString: could not convert \"")
                        +=	::rtl::OString(_rReadCharacters.getStr(), _rReadCharacters.getLength(), RTL_TEXTENCODING_ASCII_US)
                        +=	::rtl::OString("\" into a double!"));

                    // then convert it into the target type
                    switch (nType)
                    {
                        case TYPE_DATE:
                        {
                            OSL_ENSURE(((sal_uInt32)nValue) - nValue == 0,
                                "OPropertyImport::convertString: a Date value with a fractional part?");
                            aReturn <<= implGetDate(nValue);
                        }
                        break;
                        case TYPE_TIME:
                        {
                            OSL_ENSURE(((sal_uInt32)nValue) == 0,
                                "OPropertyImport::convertString: a Time value with more than a fractional part?");
                            aReturn <<= implGetTime(nValue);
                        }
                        break;
                        case TYPE_DATETIME:
                        {
                            ::com::sun::star::util::Time aTime = implGetTime(nValue);
                            ::com::sun::star::util::Date aDate = implGetDate(nValue);

                            ::com::sun::star::util::DateTime aDateTime;
                            aDateTime.HundredthSeconds = aTime.HundredthSeconds;
                            aDateTime.Seconds = aTime.Seconds;
                            aDateTime.Minutes = aTime.Minutes;
                            aDateTime.Hours = aTime.Hours;
                            aDateTime.Day = aDate.Day;
                            aDateTime.Month = aDate.Month;
                            aDateTime.Year = aDate.Year;
                            aReturn <<= aDateTime;
                        }
                        break;
                        default:
                            break;
                    }
                }
                else
                    OSL_ENSURE(sal_False, "OPropertyImport::convertString: unsupported property type!");
            }
            break;
        default:
            OSL_ENSURE(sal_False, "OXMLControlProperty::convertString: invalid type class!");
    }

    return aReturn;
}
//---------------------------------------------------------------------
::com::sun::star::util::Time OXMLControlProperty::implGetTime(double _nValue)
{
    ::com::sun::star::util::Time aTime;
    sal_uInt32 nIntValue = sal_Int32(_nValue * 8640000);
    nIntValue *= 8640000;
    aTime.HundredthSeconds = (sal_uInt16)( nIntValue % 100 );
    nIntValue /= 100;
    aTime.Seconds = (sal_uInt16)( nIntValue % 60 );
    nIntValue /= 60;
    aTime.Minutes = (sal_uInt16)( nIntValue % 60 );
    nIntValue /= 60;
    OSL_ENSURE(nIntValue < 24, "OPropertyImport::implGetTime: more than a day?");
    aTime.Hours = static_cast< sal_uInt16 >( nIntValue );

    return aTime;
}

//---------------------------------------------------------------------
::com::sun::star::util::Date OXMLControlProperty::implGetDate(double _nValue)
{
    Date aToolsDate((sal_uInt32)_nValue);
    ::com::sun::star::util::Date aDate;
    ::utl::typeConvert(aToolsDate, aDate);
    return aDate;
}
//----------------------------------------------------------------------------
} // namespace rptxml
// -----------------------------------------------------------------------------
