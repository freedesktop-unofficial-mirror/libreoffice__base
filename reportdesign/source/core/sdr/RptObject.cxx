/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: RptObject.cxx,v $
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
#include "precompiled_reportdesign.hxx"
#include "RptObject.hxx"
#include <vector>
#include <algorithm>

#include <RptDef.hxx>
#include <svx/unoshape.hxx>
#include "RptModel.hxx"
#include "RptObjectListener.hxx"
#include <toolkit/helper/vclunohelper.hxx>
#include <toolkit/helper/convert.hxx>
#include "RptPage.hxx"
#include "corestrings.hrc"
#include <dbaccess/singledoccontroller.hxx>
#include "ModuleHelper.hxx"

#include <RptResId.hrc>
#include <svx/xflclit.hxx>
#include <svx/xlnclit.hxx>
#include <svx/xlndsit.hxx>
#include <svx/xlineit0.hxx>
#include <svx/sderitm.hxx>
#include <svx/xlnwtit.hxx>
#include <svx/xlntrit.hxx>
#include <com/sun/star/style/XStyle.hpp>
#include <com/sun/star/awt/XTabControllerModel.hpp>
#include <com/sun/star/awt/XUnoControlContainer.hpp>
#include <com/sun/star/awt/XVclContainerPeer.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/script/XScriptEventsSupplier.hpp>
#include <com/sun/star/container/XContainer.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/report/XShape.hpp>
#include <com/sun/star/report/XFixedLine.hpp>
#include <com/sun/star/chart/ChartDataRowSource.hpp>
#include <com/sun/star/chart2/data/XDataReceiver.hpp>
#include <com/sun/star/chart2/data/DatabaseDataProvider.hpp>
#include <com/sun/star/chart2/XChartDocument.hpp>
#include <comphelper/genericpropertyset.hxx>
#include <comphelper/processfactory.hxx>
#include <comphelper/property.hxx>
#include "PropertyForward.hxx"
#include <connectivity/dbtools.hxx>
#include "UndoActions.hxx"
#include "UndoEnv.hxx"
#include <algorithm>
#include <functional>

namespace rptui
{

using namespace ::com::sun::star;
using namespace uno;
using namespace beans;
using namespace reportdesign;
using namespace container;
using namespace script;
//----------------------------------------------------------------------------
sal_uInt16 OObjectBase::getObjectType(const uno::Reference< report::XReportComponent>& _xComponent)
{
    uno::Reference< lang::XServiceInfo > xServiceInfo( _xComponent , uno::UNO_QUERY );
    OSL_ENSURE(xServiceInfo.is(),"Who deletes the XServiceInfo interface!");
    if ( xServiceInfo.is() )
    {
        if ( xServiceInfo->supportsService( SERVICE_FIXEDTEXT ))
            return OBJ_DLG_FIXEDTEXT;
        if ( xServiceInfo->supportsService( SERVICE_FIXEDLINE ))
        {
            uno::Reference< report::XFixedLine> xFixedLine(_xComponent,uno::UNO_QUERY);
            return xFixedLine->getOrientation() ? OBJ_DLG_HFIXEDLINE : OBJ_DLG_VFIXEDLINE;
        }
        if ( xServiceInfo->supportsService( SERVICE_IMAGECONTROL))
            return OBJ_DLG_IMAGECONTROL;
        if ( xServiceInfo->supportsService( SERVICE_FORMATTEDFIELD )) 
            return OBJ_DLG_FORMATTEDFIELD;
        if ( xServiceInfo->supportsService( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.OLE2Shape")) ) )
            return OBJ_OLE2;
        if ( xServiceInfo->supportsService( SERVICE_SHAPE )) 
            return OBJ_CUSTOMSHAPE;
        if ( xServiceInfo->supportsService( SERVICE_REPORTDEFINITION ) )
            return OBJ_DLG_SUBREPORT;
        return OBJ_OLE2;
    }
    return 0;
}
// -----------------------------------------------------------------------------
SdrObject* OObjectBase::createObject(const uno::Reference< report::XReportComponent>& _xComponent)
{
    SdrObject* pNewObj = NULL;
    sal_uInt16 nType = OObjectBase::getObjectType(_xComponent);
    switch( nType )
    {
        case OBJ_DLG_FIXEDTEXT:
            {
                OUnoObject* pUnoObj = new OUnoObject( _xComponent 
                                    ,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.form.component.FixedText")) 
                                    ,OBJ_DLG_FIXEDTEXT);
                pNewObj = pUnoObj;
            
                uno::Reference<beans::XPropertySet> xControlModel(pUnoObj->GetUnoControlModel(),uno::UNO_QUERY);
                if ( xControlModel.is() )
                    xControlModel->setPropertyValue( PROPERTY_MULTILINE,uno::makeAny(sal_True));
            }
            break;
        case OBJ_DLG_IMAGECONTROL:
            pNewObj = new OUnoObject(_xComponent
                                    ,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.form.component.DatabaseImageControl")) 
                                    ,OBJ_DLG_IMAGECONTROL);
            break;
        case OBJ_DLG_FORMATTEDFIELD:
            pNewObj = new OUnoObject( _xComponent
                                    ,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.form.component.FormattedField")) 
                                    ,OBJ_DLG_FORMATTEDFIELD);
            break;
        case OBJ_DLG_HFIXEDLINE:
        case OBJ_DLG_VFIXEDLINE:
            pNewObj = new OUnoObject( _xComponent
                                    ,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.awt.UnoControlFixedLineModel")) 
                                    ,nType);
            break;
        case OBJ_CUSTOMSHAPE:
            pNewObj = OCustomShape::Create( _xComponent );
            break;
        case OBJ_DLG_SUBREPORT:
        case OBJ_OLE2:
            pNewObj = OOle2Obj::Create( _xComponent,nType );
            break;
        default:
            OSL_ENSURE(0,"Unknown object id");
            break;
    }

    ensureSdrObjectOwnership( _xComponent );

    return pNewObj;
}
// -----------------------------------------------------------------------------
const TPropertyNamePair& getPropertyNameMap(sal_uInt16 _nObjectId)
{
    switch(_nObjectId)
    {
        case OBJ_DLG_IMAGECONTROL:
            {
                static TPropertyNamePair s_aNameMap;
                if ( s_aNameMap.empty() )
                {
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBACKGROUND,PROPERTY_BACKGROUNDCOLOR));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBORDER,PROPERTY_BORDER));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBORDERCOLOR,PROPERTY_BORDERCOLOR));
                    //s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_PARAADJUST,PROPERTY_ALIGN));
                }
                return s_aNameMap;
            }

        case OBJ_DLG_FIXEDTEXT:
        case OBJ_DLG_FORMATTEDFIELD:
            {
                static TPropertyNamePair s_aNameMap;
                if ( s_aNameMap.empty() )
                {
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CHARCOLOR,PROPERTY_TEXTCOLOR));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBACKGROUND,PROPERTY_BACKGROUNDCOLOR));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CHARUNDERLINECOLOR,PROPERTY_TEXTLINECOLOR));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CHARRELIEF,PROPERTY_FONTRELIEF));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CHARFONTHEIGHT,PROPERTY_FONTHEIGHT));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CHARSTRIKEOUT,PROPERTY_FONTSTRIKEOUT));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLTEXTEMPHASISMARK,PROPERTY_FONTEMPHASISMARK));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBORDER,PROPERTY_BORDER));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_CONTROLBORDERCOLOR,PROPERTY_BORDERCOLOR));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_PARAADJUST,PROPERTY_ALIGN));
                }
                return s_aNameMap;
            }

        case OBJ_CUSTOMSHAPE:
            {
                static TPropertyNamePair s_aNameMap;
                if ( s_aNameMap.empty() )
                {
                    s_aNameMap.insert(TPropertyNamePair::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FillColor")),PROPERTY_CONTROLBACKGROUND));
                    s_aNameMap.insert(TPropertyNamePair::value_type(PROPERTY_PARAADJUST,PROPERTY_ALIGN));
                }
                return s_aNameMap;
            }

        default:
            break;
    }
    static TPropertyNamePair s_aEmptyNameMap;
    return s_aEmptyNameMap;
}
// -----------------------------------------------------------------------------

DBG_NAME( rpt_OObjectBase )
OObjectBase::OObjectBase(const uno::Reference< report::XReportComponent>& _xComponent)
:m_bIsListening(sal_False)
{
    DBG_CTOR( rpt_OObjectBase,NULL);	
    m_xReportComponent = _xComponent;
}
//----------------------------------------------------------------------------
OObjectBase::OObjectBase(const ::rtl::OUString& _sComponentName)
:m_sComponentName(_sComponentName)
,m_bIsListening(sal_False)
{
    DBG_CTOR( rpt_OObjectBase,NULL);
}
//----------------------------------------------------------------------------
OObjectBase::~OObjectBase()
{
    DBG_DTOR( rpt_OObjectBase,NULL);	
    m_xMediator.reset();
    if ( isListening() )
        EndListening();
    m_xReportComponent.clear();
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection> OObjectBase::getSection() const
{
    uno::Reference< report::XSection> xSection;
    OReportPage* pPage = dynamic_cast<OReportPage*>(GetImplPage());
    if ( pPage )
        xSection = pPage->getSection();
    return xSection;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XReportComponent> OObjectBase::getReportComponent() const
{
    return m_xReportComponent;
}
// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySet> OObjectBase::getAwtComponent()
{
    return uno::Reference< beans::XPropertySet>();
}
// -----------------------------------------------------------------------------
sal_Bool OObjectBase::IsInside(const Rectangle& _rRect,const Point& rPnt,USHORT nTol) const
{
    sal_Bool bRet = sal_False;
    Rectangle aRect( _rRect );
    if ( !aRect.IsEmpty() )
    {
        aRect.Left() -= nTol;
        aRect.Top() -= nTol;
        aRect.Right() = ( aRect.Right() == RECT_EMPTY ? _rRect.Left() + nTol : aRect.Right() + nTol );
        aRect.Bottom() = ( aRect.Bottom() == RECT_EMPTY ? _rRect.Top() + nTol : aRect.Bottom() + nTol );

        bRet = aRect.IsInside( rPnt );
    }
    return bRet;
}
//----------------------------------------------------------------------------
void OObjectBase::StartListening()
{
    DBG_CHKTHIS( rpt_OObjectBase,NULL);
    OSL_ENSURE(!isListening(), "OUnoObject::StartListening: already listening!");

    if ( !isListening() && m_xReportComponent.is() )
    {
        m_bIsListening = sal_True;
        
        if ( !m_xPropertyChangeListener.is() )
        {
            m_xPropertyChangeListener = new OObjectListener( this );
            // register listener to all properties
            m_xReportComponent->addPropertyChangeListener( ::rtl::OUString() , m_xPropertyChangeListener );
        }
    }
}
//----------------------------------------------------------------------------
void OObjectBase::EndListening(sal_Bool /*bRemoveListener*/)
{
    DBG_CHKTHIS( rpt_OObjectBase,NULL);
    OSL_ENSURE(!m_xReportComponent.is() || isListening(), "OUnoObject::EndListening: not listening currently!");

    m_bIsListening = sal_False;
    if ( isListening() && m_xReportComponent.is() )
    {
        // XPropertyChangeListener
        if ( m_xPropertyChangeListener.is() )
        {
            // remove listener
            try
            {
                m_xReportComponent->removePropertyChangeListener( ::rtl::OUString() , m_xPropertyChangeListener );
            }
            catch(uno::Exception)
            {
                OSL_ENSURE(0,"OObjectBase::EndListening: Exception caught!");
            }
        }
        m_xPropertyChangeListener.clear();
    }
}
//----------------------------------------------------------------------------
void OObjectBase::SetPropsFromRect(const Rectangle& _rRect)
{
    DBG_CHKTHIS( rpt_OObjectBase,NULL);
    // set properties
    OReportPage* pPage = dynamic_cast<OReportPage*>(GetImplPage());
    if ( pPage && !_rRect.IsEmpty() )
    {
        uno::Reference<report::XSection> xSection = pPage->getSection();
        if ( xSection.is() && (static_cast<sal_uInt32>(_rRect.getHeight() + _rRect.Top()) > xSection->getHeight()) )
            xSection->setHeight(_rRect.getHeight() + _rRect.Top());

        // TODO
        //pModel->GetRefDevice()->Invalidate(INVALIDATE_CHILDREN);
    }
}
//----------------------------------------------------------------------------
void OObjectBase::_propertyChange( const  beans::PropertyChangeEvent& /*evt*/ ) throw( uno::RuntimeException)
{
    DBG_CHKTHIS( rpt_OObjectBase,NULL);
}
//----------------------------------------------------------------------------
void OObjectBase::SetObjectItemHelper(const SfxPoolItem& /*rItem*/)
{
    // do nothing
}

//----------------------------------------------------------------------------
sal_Bool OObjectBase::supportsService( const ::rtl::OUString& _sServiceName ) const
{
    DBG_CHKTHIS( rpt_OObjectBase,NULL);
    sal_Bool bSupports = sal_False;

    Reference< lang::XServiceInfo > xServiceInfo( m_xReportComponent , UNO_QUERY );
        // TODO: cache xServiceInfo as member?
    if ( xServiceInfo.is() )
        bSupports = xServiceInfo->supportsService( _sServiceName );

    return bSupports;
}

//----------------------------------------------------------------------------
void OObjectBase::ensureSdrObjectOwnership( const uno::Reference< uno::XInterface >& _rxShape )
{
    // UNDO in the report designer is implemented at the level of the XShapes, not
    // at the level of SdrObjects. That is, if an object is removed from the report
    // design, then this happens by removing the XShape from the UNO DrawPage, and
    // putting this XShape (resp. the ReportComponent which wraps it) into an UNDO
    // action.
    // Unfortunately, the SvxDrawPage implementation usually deletes SdrObjects
    // which are removed from it, which is deadly for us. To prevent this,
    // we give the XShape implementation the ownership of the SdrObject, which
    // ensures the SvxDrawPage won't delete it.
    SvxShape* pShape = SvxShape::getImplementation( _rxShape );
    OSL_ENSURE( pShape, "OObjectBase::ensureSdrObjectOwnership: can't access the SvxShape!" );
    if ( pShape )
    {
        OSL_ENSURE( !pShape->HasSdrObjectOwnership(), "OObjectBase::ensureSdrObjectOwnership: called twice?" );
        pShape->TakeSdrObjectOwnership();
    }
}

//----------------------------------------------------------------------------
uno::Reference< uno::XInterface > OObjectBase::getUnoShapeOf( SdrObject& _rSdrObject )
{
    uno::Reference< uno::XInterface > xShape( _rSdrObject.getWeakUnoShape() );
    if ( xShape.is() )
        return xShape;

    xShape = _rSdrObject.SdrObject::getUnoShape();
    if ( !xShape.is() )
        return xShape;

    ensureSdrObjectOwnership( xShape );

    m_xKeepShapeAlive = xShape;
    return xShape;
}

//----------------------------------------------------------------------------
TYPEINIT1(OCustomShape, SdrObjCustomShape);
DBG_NAME( rpt_OCustomShape );
OCustomShape::OCustomShape(const uno::Reference< report::XReportComponent>& _xComponent
                           )
          :SdrObjCustomShape()
          ,OObjectBase(_xComponent)
{
    DBG_CTOR( rpt_OCustomShape, NULL);
    // start listening
    mxUnoShape = uno::Reference< uno::XInterface >(_xComponent,uno::UNO_QUERY);
    m_bIsListening = sal_True;
}
//----------------------------------------------------------------------------
OCustomShape::OCustomShape(const ::rtl::OUString& _sComponentName)
          :SdrObjCustomShape()
          ,OObjectBase(_sComponentName)
{
    DBG_CTOR( rpt_OCustomShape, NULL);
    m_bIsListening = sal_True;
}

//----------------------------------------------------------------------------
OCustomShape::~OCustomShape()
{
    DBG_DTOR( rpt_OCustomShape, NULL);
    //mxUnoShape = uno::WeakReference< uno::XInterface >();
}
// -----------------------------------------------------------------------------
UINT16 OCustomShape::GetObjIdentifier() const
{
    return UINT16(OBJ_CUSTOMSHAPE);
}
//----------------------------------------------------------------------------
UINT32 OCustomShape::GetObjInventor() const
{
    return ReportInventor;
}
//----------------------------------------------------------------------------
SdrPage* OCustomShape::GetImplPage() const
{
    return GetPage();
}
//----------------------------------------------------------------------------
void OCustomShape::SetSnapRectImpl(const Rectangle& _rRect)
{
    SetSnapRect( _rRect );
}
//----------------------------------------------------------------------------
sal_Int32 OCustomShape::GetStep() const
{
    // get step property
    sal_Int32 nStep = 0;
    OSL_ENSURE(0,"Who called me!");
    return nStep;
}
//----------------------------------------------------------------------------
void OCustomShape::NbcMove( const Size& rSize )
{
    if ( m_bIsListening )
    {
        m_bIsListening = sal_False;

        if ( m_xReportComponent.is() )
        {
            OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            m_xReportComponent->setPositionX(m_xReportComponent->getPositionX() + rSize.A());
            m_xReportComponent->setPositionY(m_xReportComponent->getPositionY() + rSize.B());
        }
        
        // set geometry properties	
        SetPropsFromRect(GetSnapRect());

        m_bIsListening = sal_True;
    }
    else
        SdrObjCustomShape::NbcMove( rSize );
}
//----------------------------------------------------------------------------
void OCustomShape::NbcResize(const Point& rRef, const Fraction& xFract, const Fraction& yFract)
{
    SdrObjCustomShape::NbcResize( rRef, xFract, yFract );

    SetPropsFromRect(GetSnapRect());
}
//----------------------------------------------------------------------------
void OCustomShape::NbcSetLogicRect(const Rectangle& rRect)
{
    SdrObjCustomShape::NbcSetLogicRect(rRect);
    SetPropsFromRect(rRect);
}
//----------------------------------------------------------------------------
FASTBOOL OCustomShape::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
{
    FASTBOOL bResult = SdrObjCustomShape::EndCreate(rStat, eCmd);
    if ( bResult )
    {
        OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
        if ( pRptModel )
        {
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            if ( !m_xReportComponent.is() )
                m_xReportComponent.set(getUnoShape(),uno::UNO_QUERY);
        }
        SetPropsFromRect(GetSnapRect());
    }

    return bResult;
}
//----------------------------------------------------------------------------
SdrObject* OCustomShape::CheckHit( const Point& rPnt, USHORT nTol,const SetOfByte* pSet ) const
{
    // #109994# fixed here, because the drawing layer doesn't handle objects
    // with a width or height of 0 in a proper way
    if ( IsInside(aOutRect,rPnt,nTol) )
        return const_cast<OCustomShape*>(this);

    return SdrObjCustomShape::CheckHit( rPnt, nTol, pSet );
}

//----------------------------------------------------------------------------
void OCustomShape::SetObjectItemHelper(const SfxPoolItem& rItem)
{
    SetObjectItem(rItem);
    // TODO
    //getSectionWindow()->getView()->AdjustMarkHdl();
}

// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySet> OCustomShape::getAwtComponent()
{
    return uno::Reference< beans::XPropertySet>(m_xReportComponent,uno::UNO_QUERY);
}

//----------------------------------------------------------------------------
uno::Reference< uno::XInterface > OCustomShape::getUnoShape()
{
    return OObjectBase::getUnoShapeOf( *this );
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
TYPEINIT1(OUnoObject, SdrUnoObj);
DBG_NAME( rpt_OUnoObject );
//----------------------------------------------------------------------------
OUnoObject::OUnoObject(const ::rtl::OUString& _sComponentName
                       ,const ::rtl::OUString& rModelName
                       ,sal_uInt16   _nObjectType)
          :SdrUnoObj(rModelName, sal_True)
          ,OObjectBase(_sComponentName)
          ,m_nObjectType(_nObjectType)
{
    DBG_CTOR( rpt_OUnoObject, NULL);
}
//----------------------------------------------------------------------------
OUnoObject::OUnoObject(const uno::Reference< report::XReportComponent>& _xComponent
                       ,const ::rtl::OUString& rModelName
                       ,sal_uInt16   _nObjectType)
          :SdrUnoObj(rModelName, sal_True)
          ,OObjectBase(_xComponent)
          ,m_nObjectType(_nObjectType)
{
    DBG_CTOR( rpt_OUnoObject, NULL);
    mxUnoShape = uno::Reference< uno::XInterface >(_xComponent,uno::UNO_QUERY);
}
//----------------------------------------------------------------------------
OUnoObject::~OUnoObject()
{
    DBG_DTOR( rpt_OUnoObject, NULL);
    //mxUnoShape = uno::WeakReference< uno::XInterface >();
}
// -----------------------------------------------------------------------------
UINT16 OUnoObject::GetObjIdentifier() const
{
    return UINT16(m_nObjectType);
}
//----------------------------------------------------------------------------
UINT32 OUnoObject::GetObjInventor() const
{
    return ReportInventor;
}
//----------------------------------------------------------------------------
SdrPage* OUnoObject::GetImplPage() const
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    return GetPage();
}
//----------------------------------------------------------------------------
void OUnoObject::SetSnapRectImpl(const Rectangle& _rRect)
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    SetSnapRect( _rRect );
}
//----------------------------------------------------------------------------
sal_Int32 OUnoObject::GetStep() const
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    // get step property
    sal_Int32 nStep = 0;
    OSL_ENSURE(0,"Who called me!");
    return nStep;
}

//----------------------------------------------------------------------------
void OUnoObject::NbcMove( const Size& rSize )
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    
    if ( m_bIsListening )
    {
        // stop listening
        OObjectBase::EndListening(sal_False);

        if ( m_xReportComponent.is() )
        {
            OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            m_xReportComponent->setPositionX(m_xReportComponent->getPositionX() + rSize.A());
            m_xReportComponent->setPositionY(m_xReportComponent->getPositionY() + rSize.B());
        }
        
        // set geometry properties	
        SetPropsFromRect(GetLogicRect());

        // start listening
        OObjectBase::StartListening();
    }
    else
        SdrUnoObj::NbcMove( rSize );
}

//----------------------------------------------------------------------------

void OUnoObject::NbcResize(const Point& rRef, const Fraction& xFract, const Fraction& yFract)
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    SdrUnoObj::NbcResize( rRef, xFract, yFract );

    // stop listening
    OObjectBase::EndListening(sal_False);
    
    // set geometry properties	
    SetPropsFromRect(GetLogicRect());

    // start listening
    OObjectBase::StartListening();
}
//----------------------------------------------------------------------------
void OUnoObject::NbcSetLogicRect(const Rectangle& rRect)
{
    SdrUnoObj::NbcSetLogicRect(rRect);
    // stop listening
    OObjectBase::EndListening(sal_False);
    
    // set geometry properties	
    SetPropsFromRect(rRect);

    // start listening
    OObjectBase::StartListening();
}
//----------------------------------------------------------------------------

FASTBOOL OUnoObject::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    FASTBOOL bResult = SdrUnoObj::EndCreate(rStat, eCmd);
    if ( bResult )
    {
        OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
        if ( pRptModel )
        {
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            if ( !m_xReportComponent.is() )
                m_xReportComponent.set(getUnoShape(),uno::UNO_QUERY);
            // set labels	
            if ( m_xReportComponent.is() )
            {
                try
                {
                    if ( supportsService( SERVICE_FIXEDTEXT ) )
                    {
                        m_xReportComponent->setPropertyValue( PROPERTY_LABEL, uno::makeAny(GetDefaultName(this)) );
                    }
                }
                catch(const uno::Exception&)
                {
                    OSL_ENSURE(0,"OUnoObject::EndCreate: Exception caught!");
                }
            }
        }
        // set geometry properties	
        SetPropsFromRect(GetLogicRect());
    }

    return bResult;
}
//----------------------------------------------------------------------------
::rtl::OUString OUnoObject::GetDefaultName(const OUnoObject* _pObj)
{	
    sal_uInt16 nResId = 0;
    ::rtl::OUString aDefaultName = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("HERE WE HAVE TO INSERT OUR NAME!"));
    if ( _pObj->supportsService( SERVICE_FIXEDTEXT ) )
    {
        nResId = RID_STR_CLASS_FIXEDTEXT;
    }
    else if ( _pObj->supportsService( SERVICE_FIXEDLINE ) )
    {
        nResId = RID_STR_CLASS_FIXEDLINE;
    }
    else if ( _pObj->supportsService( SERVICE_IMAGECONTROL ) )
    {
        nResId = RID_STR_CLASS_IMAGECONTROL;
    }
    else if ( _pObj->supportsService( SERVICE_FORMATTEDFIELD ) )
    {
        nResId = RID_STR_CLASS_FORMATTEDFIELD;
    }

    if (nResId)
        aDefaultName = ::rtl::OUString( String(ModuleRes(nResId)) );			

    return aDefaultName;
}
//----------------------------------------------------------------------------
SdrObject* OUnoObject::CheckHit( const Point& rPnt, USHORT nTol,const SetOfByte* pSet ) const
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    if ( IsInside(aOutRect,rPnt,nTol) )
        return const_cast<OUnoObject*>(this);

    return SdrUnoObj::CheckHit( rPnt, nTol, pSet );
}
// -----------------------------------------------------------------------------
void OUnoObject::_propertyChange( const  beans::PropertyChangeEvent& evt ) throw( uno::RuntimeException)
{
    DBG_CHKTHIS( rpt_OUnoObject,NULL);
    OObjectBase::_propertyChange(evt);
    if (isListening())
    {
        if ( evt.PropertyName == PROPERTY_CHARCOLOR )
        {
            Reference<XPropertySet> xControlModel(GetUnoControlModel(),uno::UNO_QUERY);
            if ( xControlModel.is() )
            {
                OObjectBase::EndListening(sal_False);
                try
                {
                    xControlModel->setPropertyValue(PROPERTY_TEXTCOLOR,evt.NewValue);
                }
                catch(uno::Exception&)
                {
                }
                OObjectBase::StartListening();
            }
        }
        else if ( evt.PropertyName == PROPERTY_NAME )
        {
            Reference<XPropertySet> xControlModel(GetUnoControlModel(),uno::UNO_QUERY);
            if ( xControlModel.is() && xControlModel->getPropertySetInfo()->hasPropertyByName(PROPERTY_NAME) )
            {
                // get old name
                ::rtl::OUString aOldName;
                evt.OldValue >>= aOldName;

                // get new name
                ::rtl::OUString aNewName;
                evt.NewValue >>= aNewName;

                if ( !aNewName.equals(aOldName) )
                {
                    // set old name property
                    OObjectBase::EndListening(sal_False);
                    if ( m_xMediator.is() )
                        m_xMediator.get()->stopListening();
                    try
                    {
                        xControlModel->setPropertyValue( PROPERTY_NAME, evt.NewValue );
                    }
                    catch(uno::Exception&)
                    {
                    }
                    if ( m_xMediator.is() )
                        m_xMediator.get()->startListening();
                    OObjectBase::StartListening();
                }
            }
        } 
    }
}
// -----------------------------------------------------------------------------
void OUnoObject::CreateMediator(sal_Bool _bReverse)
{
    if ( !m_xMediator.is() )
    {
        if ( !m_xReportComponent.is() )
            m_xReportComponent.set(getUnoShape(),uno::UNO_QUERY);

        Reference<XPropertySet> xControlModel(GetUnoControlModel(),uno::UNO_QUERY);
        if ( !m_xMediator.is() && m_xReportComponent.is() && xControlModel.is() )
            m_xMediator = TMediator::createFromQuery(new OPropertyMediator(m_xReportComponent.get(),xControlModel,getPropertyNameMap(GetObjIdentifier()),_bReverse));
        OObjectBase::StartListening();
    }
}
// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySet> OUnoObject::getAwtComponent()
{
    return Reference<XPropertySet>(GetUnoControlModel(),uno::UNO_QUERY);
}

// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > OUnoObject::getUnoShape()
{
    return OObjectBase::getUnoShapeOf( *this );
}
// -----------------------------------------------------------------------------
SdrObject* OUnoObject::Clone() const
{
    SdrObject* pClone = SdrUnoObj::Clone();
    if ( pClone )
    {
        Reference<XPropertySet> xSource(const_cast<OUnoObject*>(this)->getUnoShape(),uno::UNO_QUERY);
        Reference<XPropertySet> xDest(pClone->getUnoShape(),uno::UNO_QUERY);
        if ( xSource.is() && xDest.is() )
            comphelper::copyProperties(xSource.get(),xDest.get());
    } // if ( pClone )
    return pClone;
}
//----------------------------------------------------------------------------
// OOle2Obj
//----------------------------------------------------------------------------
TYPEINIT1(OOle2Obj, SdrOle2Obj);
DBG_NAME( rpt_OOle2Obj );
OOle2Obj::OOle2Obj(const uno::Reference< report::XReportComponent>& _xComponent,UINT16 _nType)
          :SdrOle2Obj()
          ,OObjectBase(_xComponent)
          ,m_nType(_nType)
{
    DBG_CTOR( rpt_OOle2Obj, NULL);

    // start listening
    mxUnoShape = uno::Reference< uno::XInterface >(_xComponent,uno::UNO_QUERY);
    m_bIsListening = sal_True;
    //uno::Reference< embed::XEmbeddedObject > xEmbed(_xComponent,uno::UNO_QUERY);
    //OSL_ENSURE(xEmbed.is(),"This is no embedded object!");

    //SetObjRef(xEmbed);
}
//----------------------------------------------------------------------------
OOle2Obj::OOle2Obj(const ::rtl::OUString& _sComponentName,UINT16 _nType)
          :SdrOle2Obj()
          ,OObjectBase(_sComponentName)
          ,m_nType(_nType)
{
    DBG_CTOR( rpt_OOle2Obj, NULL);
    m_bIsListening = sal_True;
}
//----------------------------------------------------------------------------
OOle2Obj::~OOle2Obj()
{
    DBG_DTOR( rpt_OOle2Obj, NULL);
}
// -----------------------------------------------------------------------------
UINT16 OOle2Obj::GetObjIdentifier() const
{
    return m_nType;
}
//----------------------------------------------------------------------------
UINT32 OOle2Obj::GetObjInventor() const
{
    return ReportInventor;
}
//----------------------------------------------------------------------------
SdrPage* OOle2Obj::GetImplPage() const
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    return GetPage();
}
//----------------------------------------------------------------------------
void OOle2Obj::SetSnapRectImpl(const Rectangle& _rRect)
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    SetSnapRect( _rRect );
}
//----------------------------------------------------------------------------
sal_Int32 OOle2Obj::GetStep() const
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    // get step property
    sal_Int32 nStep = 0;
    OSL_ENSURE(0,"Who called me!");
    return nStep;
}

//----------------------------------------------------------------------------
void OOle2Obj::NbcMove( const Size& rSize )
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    
    if ( m_bIsListening )
    {
        // stop listening
        OObjectBase::EndListening(sal_False);

        if ( m_xReportComponent.is() )
        {
            OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            m_xReportComponent->setPositionX(m_xReportComponent->getPositionX() + rSize.A());
            m_xReportComponent->setPositionY(m_xReportComponent->getPositionY() + rSize.B());
        }
        
        // set geometry properties	
        SetPropsFromRect(GetLogicRect());

        // start listening
        OObjectBase::StartListening();
    }
    else
        SdrOle2Obj::NbcMove( rSize );
}

//----------------------------------------------------------------------------

void OOle2Obj::NbcResize(const Point& rRef, const Fraction& xFract, const Fraction& yFract)
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    SdrOle2Obj::NbcResize( rRef, xFract, yFract );

    // stop listening
    OObjectBase::EndListening(sal_False);
    
    // set geometry properties	
    SetPropsFromRect(GetLogicRect());

    // start listening
    OObjectBase::StartListening();
}
//----------------------------------------------------------------------------
void OOle2Obj::NbcSetLogicRect(const Rectangle& rRect)
{
    SdrOle2Obj::NbcSetLogicRect(rRect);
    // stop listening
    OObjectBase::EndListening(sal_False);
    
    // set geometry properties	
    SetPropsFromRect(rRect);

    // start listening
    OObjectBase::StartListening();
}
//----------------------------------------------------------------------------

FASTBOOL OOle2Obj::EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd)
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    FASTBOOL bResult = SdrOle2Obj::EndCreate(rStat, eCmd);
    if ( bResult )
    {
        OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
        if ( pRptModel )
        {
            OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
            if ( !m_xReportComponent.is() )
                m_xReportComponent.set(getUnoShape(),uno::UNO_QUERY);
        }
        // set geometry properties	
        SetPropsFromRect(GetLogicRect());
    }

    return bResult;
}
//----------------------------------------------------------------------------
SdrObject* OOle2Obj::CheckHit( const Point& rPnt, USHORT nTol,const SetOfByte* pSet ) const
{
    DBG_CHKTHIS( rpt_OOle2Obj,NULL);
    if ( IsInside(aOutRect,rPnt,nTol) )
        return const_cast<OOle2Obj*>(this);

    return SdrOle2Obj::CheckHit( rPnt, nTol, pSet );
}
// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySet> OOle2Obj::getAwtComponent()
{
    return uno::Reference< beans::XPropertySet>(m_xReportComponent,uno::UNO_QUERY);
}

// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > OOle2Obj::getUnoShape()
{
    uno::Reference< uno::XInterface> xShape = OObjectBase::getUnoShapeOf( *this );
    if ( !m_xReportComponent.is() )
    {
        OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
        OXUndoEnvironment::OUndoEnvLock aLock(pRptModel->GetUndoEnv());
        m_xReportComponent.set(xShape,uno::UNO_QUERY);
    }
    return xShape;
}
// -----------------------------------------------------------------------------
uno::Reference< chart2::data::XDatabaseDataProvider > lcl_getDataProvider(const uno::Reference < embed::XEmbeddedObject >& _xObj)
{
    uno::Reference< chart2::data::XDatabaseDataProvider > xSource;
    uno::Reference< embed::XComponentSupplier > xCompSupp(_xObj,uno::UNO_QUERY);
    if( xCompSupp.is())
    {
        uno::Reference< chart2::XChartDocument> xChartDoc( xCompSupp->getComponent(), uno::UNO_QUERY );
        if ( xChartDoc.is() )
        {
            xSource.set(xChartDoc->getDataProvider(),uno::UNO_QUERY);
        }
    } // if( xCompSupp.is())
    return xSource;
}
// -----------------------------------------------------------------------------
// Clone() soll eine komplette Kopie des Objektes erzeugen.
SdrObject* OOle2Obj::Clone() const
{
    OOle2Obj* pObj = static_cast<OOle2Obj*>(SdrOle2Obj::Clone());
    OReportModel* pRptModel = static_cast<OReportModel*>(GetModel());
    svt::EmbeddedObjectRef::TryRunningState( pObj->GetObjRef() );
    pObj->impl_createDataProvider_nothrow(pRptModel->getReportDefinition().get());
    
    uno::Reference< chart2::data::XDatabaseDataProvider > xSource( lcl_getDataProvider(GetObjRef()) );
    uno::Reference< chart2::data::XDatabaseDataProvider > xDest( lcl_getDataProvider(pObj->GetObjRef()) );
    if ( xSource.is() && xDest.is() )
        comphelper::copyProperties(xSource.get(),xDest.get());

    pObj->initializeChart(pRptModel->getReportDefinition().get());
    return pObj;
}
// -----------------------------------------------------------------------------
void OOle2Obj::impl_createDataProvider_nothrow(const uno::Reference< frame::XModel>& _xModel)
{
    uno::Reference < embed::XEmbeddedObject > xObj = GetObjRef();
    uno::Reference< chart2::data::XDataReceiver > xReceiver;
    uno::Reference< embed::XComponentSupplier > xCompSupp( xObj, uno::UNO_QUERY );
    if( xCompSupp.is())
        xReceiver.set( xCompSupp->getComponent(), uno::UNO_QUERY );
    OSL_ASSERT( xReceiver.is());
    if( xReceiver.is() )
    {
        uno::Reference< lang::XMultiServiceFactory> xFac(_xModel,uno::UNO_QUERY);
        uno::Reference< chart2::data::XDatabaseDataProvider > xDataProvider( xFac->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.chart2.data.DataProvider"))),uno::UNO_QUERY);
        xReceiver->attachDataProvider( xDataProvider.get() );
    }
}
// -----------------------------------------------------------------------------
void OOle2Obj::initializeChart( const uno::Reference< frame::XModel>& _xModel)
{
    uno::Reference < embed::XEmbeddedObject > xObj = GetObjRef();
    uno::Reference< chart2::data::XDataReceiver > xReceiver;
    uno::Reference< embed::XComponentSupplier > xCompSupp( xObj, uno::UNO_QUERY );
    if( xCompSupp.is())
        xReceiver.set( xCompSupp->getComponent(), uno::UNO_QUERY );
    OSL_ASSERT( xReceiver.is());
    if( xReceiver.is() )
    {
        // lock the model to suppress any internal updates
        uno::Reference< frame::XModel > xChartModel( xReceiver, uno::UNO_QUERY );
        if( xChartModel.is() )
            xChartModel->lockControllers();

        if ( !lcl_getDataProvider(xObj).is() )
            impl_createDataProvider_nothrow(_xModel);

        uno::Reference< util::XNumberFormatsSupplier > xNumberFormatsSupplier( _xModel, uno::UNO_QUERY );
        xReceiver->attachNumberFormatsSupplier( xNumberFormatsSupplier );

        uno::Sequence< beans::PropertyValue > aArgs( 4 );
        aArgs[0] = beans::PropertyValue(
            ::rtl::OUString::createFromAscii("CellRangeRepresentation"), -1,
            uno::makeAny( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("all")) ), beans::PropertyState_DIRECT_VALUE );
        aArgs[1] = beans::PropertyValue(
            ::rtl::OUString::createFromAscii("HasCategories"), -1,
            uno::makeAny( sal_True ), beans::PropertyState_DIRECT_VALUE );
        aArgs[2] = beans::PropertyValue(
            ::rtl::OUString::createFromAscii("FirstCellAsLabel"), -1,
            uno::makeAny( sal_False ), beans::PropertyState_DIRECT_VALUE );
        aArgs[3] = beans::PropertyValue(
            ::rtl::OUString::createFromAscii("DataRowSource"), -1,
            uno::makeAny( chart::ChartDataRowSource_COLUMNS ), beans::PropertyState_DIRECT_VALUE );
        xReceiver->setArguments( aArgs );

        if( xChartModel.is() )
            xChartModel->unlockControllers();
    }
}
// -----------------------------------------------------------------------------
uno::Reference< style::XStyle> getUsedStyle(const uno::Reference< report::XReportDefinition>& _xReport)
{
    uno::Reference<container::XNameAccess> xStyles = _xReport->getStyleFamilies();
    uno::Reference<container::XNameAccess> xPageStyles(xStyles->getByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PageStyles"))),uno::UNO_QUERY);
    
    uno::Reference< style::XStyle> xReturn;
    uno::Sequence< ::rtl::OUString> aSeq = xPageStyles->getElementNames();
    const ::rtl::OUString* pIter = aSeq.getConstArray();
    const ::rtl::OUString* pEnd	  = pIter + aSeq.getLength();
    for(;pIter != pEnd && !xReturn.is() ;++pIter)
    {
        uno::Reference< style::XStyle> xStyle(xPageStyles->getByName(*pIter),uno::UNO_QUERY);
        if ( xStyle->isInUse() )
            xReturn = xStyle;
    }
    return xReturn;
}
//----------------------------------------------------------------------------
//============================================================================
} // rptui
//============================================================================
