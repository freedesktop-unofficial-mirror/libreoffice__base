/*************************************************************************
 *
 *  $RCSfile: FieldDescriptions.cxx,v $
 *
 *  $Revision: 1.15 $
 *
 *  last change: $Author: rt $ $Date: 2004-11-26 18:19:52 $
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
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
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

#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _DBU_TBL_HRC_
#include "dbu_tbl.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif

#define DEFAULT_VARCHAR_PRECSION	50
#define DEFAULT_OTHER_PRECSION		16
#define DEFAULT_NUMERIC_PRECSION	5
#define DEFAULT_NUMERIC_SCALE		0


using namespace dbaui;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;

//========================================================================
// class OFieldDescription
//========================================================================
DBG_NAME(OFieldDescription);
//------------------------------------------------------------------------------
OFieldDescription::OFieldDescription() :
    m_bIsPrimaryKey(sal_False)
    ,m_nFormatKey(0)
    ,m_bIsAutoIncrement(sal_False)
    ,m_eHorJustify(SVX_HOR_JUSTIFY_STANDARD)
    ,m_nScale(0)
    ,m_nPrecision(0)
    ,m_pType()
    ,m_nIsNullable(ColumnValue::NULLABLE)
    ,m_nType(DataType::VARCHAR)
    ,m_bIsCurrency(sal_False)
{
    DBG_CTOR(OFieldDescription,NULL);
}

//------------------------------------------------------------------------------
OFieldDescription::OFieldDescription( const OFieldDescription& rDescr ) :
     m_sName(rDescr.m_sName)          
    ,m_sTypeName(rDescr.m_sTypeName)      
    ,m_sDescription(rDescr.m_sDescription)   
    ,m_aDefaultValue(rDescr.m_aDefaultValue)  
    ,m_aControlDefault(rDescr.m_aControlDefault)  
    ,m_sAutoIncrementValue(rDescr.m_sAutoIncrementValue)  
    ,m_pType(rDescr.m_pType)          
    ,m_nPrecision(rDescr.m_nPrecision)      
    ,m_nScale(rDescr.m_nScale)          
    ,m_nIsNullable(rDescr.m_nIsNullable)     
    ,m_nFormatKey(rDescr.m_nFormatKey)     
    ,m_eHorJustify(rDescr.m_eHorJustify)    
    ,m_bIsAutoIncrement(rDescr.m_bIsAutoIncrement)
    ,m_bIsPrimaryKey(rDescr.m_bIsPrimaryKey) 
    ,m_nType(DataType::VARCHAR)
{
    DBG_CTOR(OFieldDescription,NULL);
}
// -----------------------------------------------------------------------------
OFieldDescription::OFieldDescription(	const ::rtl::OUString&	_sName,
                    const ::rtl::OUString&	_sTypeName,
                    const ::rtl::OUString&	_sDescription,
                    const ::com::sun::star::uno::Any&	_aDefaultValue,
                    const ::com::sun::star::uno::Any&	_aControlDefault,
                    const ::rtl::OUString&	_sAutoIncrementValue,
                    const TOTypeInfoSP&		_pType,
                    sal_Int32				_nPrecision,
                    sal_Int32				_nScale,
                    sal_Int32				_nIsNullable,
                    sal_Int32				_nFormatKey,
                    SvxCellHorJustify		_eHorJustify,
                    sal_Bool				_bIsAutoIncrement,
                    sal_Bool				_bIsPrimaryKey,
                    sal_Bool				_bIsCurrency)	 :
 m_sName(_sName)          
,m_sTypeName(_sTypeName)      
,m_sDescription(_sDescription)   
,m_aDefaultValue(_aDefaultValue)  
,m_aControlDefault(_aControlDefault)  
,m_sAutoIncrementValue(_sAutoIncrementValue)
,m_pType(_pType)          
,m_nPrecision(_nPrecision)      
,m_nScale(_nScale)          
,m_nIsNullable(_nIsNullable)     
,m_nFormatKey(_nFormatKey)     
,m_eHorJustify(_eHorJustify)    
,m_bIsAutoIncrement(_bIsAutoIncrement)
,m_bIsPrimaryKey(_bIsPrimaryKey) 
,m_bIsCurrency(_bIsCurrency)
{
     DBG_DTOR(OFieldDescription,NULL);
}

//------------------------------------------------------------------------------
OFieldDescription::~OFieldDescription()
{
    DBG_DTOR(OFieldDescription,NULL);
}
//------------------------------------------------------------------------------
OFieldDescription::OFieldDescription(const Reference< XPropertySet >& xAffectedCol,sal_Bool _bUseAsDest)
    :m_bIsPrimaryKey(sal_False)
    ,m_nFormatKey(0)
    ,m_bIsAutoIncrement(sal_False)
    ,m_eHorJustify(SVX_HOR_JUSTIFY_STANDARD)
    ,m_nScale(0)
    ,m_nPrecision(0)
    ,m_pType()
    ,m_nIsNullable(ColumnValue::NULLABLE)
    ,m_nType(DataType::VARCHAR)
    ,m_bIsCurrency(sal_False)
{
    DBG_CTOR(OFieldDescription,NULL);
    OSL_ENSURE(xAffectedCol.is(),"PropetySet can notbe null!");
    if ( xAffectedCol.is() )
    {
        if ( _bUseAsDest )
        {
            m_xDest = xAffectedCol;
            m_xDestInfo = xAffectedCol->getPropertySetInfo();;
        }
        else
        {
            Reference<XPropertySetInfo> xPropSetInfo = xAffectedCol->getPropertySetInfo();
            if(xPropSetInfo->hasPropertyByName(PROPERTY_NAME))
                SetName(::comphelper::getString(xAffectedCol->getPropertyValue(PROPERTY_NAME)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_DESCRIPTION))
                SetDescription(::comphelper::getString(xAffectedCol->getPropertyValue(PROPERTY_DESCRIPTION)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_DEFAULTVALUE))
                SetDefaultValue( xAffectedCol->getPropertyValue(PROPERTY_DEFAULTVALUE) );
            
            if(xPropSetInfo->hasPropertyByName(PROPERTY_CONTROLDEFAULT))
                SetControlDefault( xAffectedCol->getPropertyValue(PROPERTY_CONTROLDEFAULT) );

            if(xPropSetInfo->hasPropertyByName(PROPERTY_AUTOINCREMENTCREATION))
                SetAutoIncrementValue(::comphelper::getString(xAffectedCol->getPropertyValue(PROPERTY_AUTOINCREMENTCREATION)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_TYPE))
                SetTypeValue(::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_TYPE)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_PRECISION))
                SetPrecision(::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_PRECISION)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_SCALE))
                SetScale(::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_SCALE)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_ISNULLABLE))
                SetIsNullable(::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_ISNULLABLE)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_FORMATKEY))
                SetFormatKey(::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_FORMATKEY)));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_ALIGN))
                SetHorJustify( ::dbaui::mapTextJustify(::comphelper::getINT16(xAffectedCol->getPropertyValue(PROPERTY_ALIGN))));
            if(xPropSetInfo->hasPropertyByName(PROPERTY_ISAUTOINCREMENT))
                SetAutoIncrement(::cppu::any2bool(xAffectedCol->getPropertyValue(PROPERTY_ISAUTOINCREMENT)));
        }
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::FillFromTypeInfo(const TOTypeInfoSP& _pType,sal_Bool _bForce,sal_Bool _bReset)
{							  
    TOTypeInfoSP pOldType = getTypeInfo();
    if ( _pType != pOldType )
    {
        // reset type depending information
        if ( _bReset )
        {
            SetFormatKey(0);
            SetControlDefault(Any());
        }

        sal_Bool bForce = _bForce || pOldType.get() == NULL || pOldType->nType != _pType->nType;
        switch ( _pType->nType )
        {
            case DataType::CHAR:
            case DataType::VARCHAR:
                if ( bForce )
                {
                    sal_Int32 nPrec = DEFAULT_VARCHAR_PRECSION;
                    if ( GetPrecision() )
                        nPrec = GetPrecision();
                    SetPrecision(::std::min<sal_Int32>(nPrec,_pType->nPrecision));
                }
                break;
            default:
                if ( bForce )
                {
                    sal_Int32 nPrec = DEFAULT_OTHER_PRECSION;
                    if ( GetPrecision() )
                        nPrec = GetPrecision();
                    if ( _pType->nPrecision )
                        SetPrecision(::std::min<sal_Int32>(nPrec ? nPrec : DEFAULT_NUMERIC_PRECSION,_pType->nPrecision));
                    if ( _pType->nMaximumScale )
                        SetScale(::std::min<sal_Int32>(GetScale() ? GetScale() : DEFAULT_NUMERIC_SCALE,_pType->nMaximumScale));
                }
        }
        if ( !_pType->aCreateParams.getLength() )
        {
            SetPrecision(_pType->nPrecision);
            SetScale(_pType->nMinimumScale);
        }
        if ( !_pType->bNullable && IsNullable() )
            SetIsNullable(ColumnValue::NO_NULLS);
        if ( !_pType->bAutoIncrement && IsAutoIncrement() )
            SetAutoIncrement(sal_False);
        SetCurrency( _pType->bCurrency );
        SetType(_pType);
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetName(const ::rtl::OUString& _rName)							
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_NAME) )
            m_xDest->setPropertyValue(PROPERTY_NAME,makeAny(_rName));
        else
            m_sName = _rName; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetDescription(const ::rtl::OUString& _rDescription)			
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_DESCRIPTION) )
            m_xDest->setPropertyValue(PROPERTY_DESCRIPTION,makeAny(_rDescription));
        else
            m_sDescription = _rDescription; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetDefaultValue(const Any& _rDefaultValue)		
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_DEFAULTVALUE) )
            m_xDest->setPropertyValue(PROPERTY_DEFAULTVALUE,makeAny(_rDefaultValue));
        else
            m_aDefaultValue = _rDefaultValue; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetControlDefault(const Any& _rControlDefault)	
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_CONTROLDEFAULT) )
            m_xDest->setPropertyValue(PROPERTY_CONTROLDEFAULT,makeAny(_rControlDefault));
        else
            m_aControlDefault = _rControlDefault; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetAutoIncrementValue(const ::rtl::OUString& _sAutoIncValue)	
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_AUTOINCREMENTCREATION) )
            m_xDest->setPropertyValue(PROPERTY_AUTOINCREMENTCREATION,makeAny(_sAutoIncValue));
        else
            m_sAutoIncrementValue = _sAutoIncValue; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetType(TOTypeInfoSP _pType)									
{ 
    m_pType = _pType; 
    if ( m_pType.get() ) 
    {
        try
        {
            if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_TYPE) )
                m_xDest->setPropertyValue(PROPERTY_TYPE,makeAny(m_pType->nType));
            else
                m_nType = m_pType->nType; 
        }
        catch(Exception)
        {
            OSL_ENSURE(0,"Exception catched while set a value!");
        }
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetTypeValue(sal_Int32 _nType)									
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_TYPE) )
            m_xDest->setPropertyValue(PROPERTY_TYPE,makeAny(_nType));
        else
        {
            m_nType = _nType; 
            OSL_ENSURE(!m_pType.get(),"Invalid call here!");
        }
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetPrecision(const sal_Int32& _rPrecision)						
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_PRECISION) )
            m_xDest->setPropertyValue(PROPERTY_PRECISION,makeAny(_rPrecision));
        else
            m_nPrecision = _rPrecision; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetScale(const sal_Int32& _rScale)								
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_SCALE) )
            m_xDest->setPropertyValue(PROPERTY_SCALE,makeAny(_rScale));
        else
            m_nScale = _rScale; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetIsNullable(const sal_Int32& _rIsNullable)					
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ISNULLABLE) )
            m_xDest->setPropertyValue(PROPERTY_ISNULLABLE,makeAny(_rIsNullable));
        else
            m_nIsNullable = _rIsNullable; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetFormatKey(const sal_Int32& _rFormatKey)						
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_FORMATKEY) )
            m_xDest->setPropertyValue(PROPERTY_FORMATKEY,makeAny(_rFormatKey));
        else
            m_nFormatKey = _rFormatKey;
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetHorJustify(const SvxCellHorJustify& _rHorJustify)			
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ALIGN) )
            m_xDest->setPropertyValue(PROPERTY_ALIGN,makeAny( dbaui::mapTextAllign(_rHorJustify)));
        else
            m_eHorJustify = _rHorJustify; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetAutoIncrement(sal_Bool _bAuto)								
{ 
    try
    {
        if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ISAUTOINCREMENT) )
            m_xDest->setPropertyValue(PROPERTY_ISAUTOINCREMENT,makeAny(_bAuto));
        else
            m_bIsAutoIncrement = _bAuto; 
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"Exception catched while set a value!");
    }
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetPrimaryKey(sal_Bool _bPKey)									
{ 
    m_bIsPrimaryKey = _bPKey; 
    if ( _bPKey ) 
        SetIsNullable(::com::sun::star::sdbc::ColumnValue::NO_NULLS); 
}
// -----------------------------------------------------------------------------
void OFieldDescription::SetCurrency(sal_Bool _bIsCurrency)								
{ 
    m_bIsCurrency = _bIsCurrency; 
}
// -----------------------------------------------------------------------------

::rtl::OUString				OFieldDescription::GetName()				const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_NAME) )
        return ::comphelper::getString(m_xDest->getPropertyValue(PROPERTY_NAME));
    else
        return m_sName; 
}
// -----------------------------------------------------------------------------
::rtl::OUString				OFieldDescription::GetDescription()			const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_DESCRIPTION) )
        return ::comphelper::getString(m_xDest->getPropertyValue(PROPERTY_DESCRIPTION));
    else
        return m_sDescription; 
}
// -----------------------------------------------------------------------------
::com::sun::star::uno::Any	OFieldDescription::GetDefaultValue()		const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_DEFAULTVALUE) )
        return m_xDest->getPropertyValue(PROPERTY_DEFAULTVALUE);
    else
        return m_aDefaultValue; 
}
// -----------------------------------------------------------------------------
::com::sun::star::uno::Any	OFieldDescription::GetControlDefault()		const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_CONTROLDEFAULT) )
        return m_xDest->getPropertyValue(PROPERTY_CONTROLDEFAULT);
    else
        return m_aControlDefault; 
}
// -----------------------------------------------------------------------------
::rtl::OUString				OFieldDescription::GetAutoIncrementValue()	const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_AUTOINCREMENTCREATION) )
        return ::comphelper::getString(m_xDest->getPropertyValue(PROPERTY_AUTOINCREMENTCREATION));
    else
        return m_sAutoIncrementValue; 
}
// -----------------------------------------------------------------------------
sal_Int32					OFieldDescription::GetType()				const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_TYPE) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_TYPE));
    else
        return m_pType.get() ? m_pType->nType : m_nType; 
}
// -----------------------------------------------------------------------------
sal_Int32					OFieldDescription::GetPrecision()			const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_PRECISION) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_PRECISION));
    else
        return m_nPrecision; 
}
// -----------------------------------------------------------------------------
sal_Int32					OFieldDescription::GetScale()				const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_SCALE) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_SCALE));
    else
        return m_nScale; 
}
// -----------------------------------------------------------------------------
sal_Int32					OFieldDescription::GetIsNullable()			const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ISNULLABLE) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_ISNULLABLE));
    else
        return m_nIsNullable; 
}
// -----------------------------------------------------------------------------
sal_Int32					OFieldDescription::GetFormatKey()			const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_FORMATKEY) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_FORMATKEY));
    else
        return m_nFormatKey; 
}
// -----------------------------------------------------------------------------
SvxCellHorJustify			OFieldDescription::GetHorJustify()			const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ALIGN) )
        return ::dbaui::mapTextJustify(::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_ALIGN)));
    else
        return m_eHorJustify; 
}
// -----------------------------------------------------------------------------
TOTypeInfoSP				OFieldDescription::getTypeInfo()			const 
{ 
    return m_pType; 
}
// -----------------------------------------------------------------------------
sal_Bool					OFieldDescription::IsAutoIncrement()		const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ISAUTOINCREMENT) )
        return ::cppu::any2bool(m_xDest->getPropertyValue(PROPERTY_ISAUTOINCREMENT));
    else
        return m_bIsAutoIncrement; 
}
// -----------------------------------------------------------------------------
sal_Bool					OFieldDescription::IsPrimaryKey()			const 
{ 
    return m_bIsPrimaryKey; 
}
// -----------------------------------------------------------------------------
sal_Bool					OFieldDescription::IsCurrency()				const 
{ 
        return m_bIsCurrency; 
}
// -----------------------------------------------------------------------------
sal_Bool					OFieldDescription::IsNullable()				const 
{ 
    if ( m_xDest.is() && m_xDestInfo->hasPropertyByName(PROPERTY_ISNULLABLE) )
        return ::comphelper::getINT32(m_xDest->getPropertyValue(PROPERTY_ISNULLABLE)) == ::com::sun::star::sdbc::ColumnValue::NULLABLE;
    else
        return m_nIsNullable == ::com::sun::star::sdbc::ColumnValue::NULLABLE; 
}



