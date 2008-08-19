/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ReportWindow.cxx,v $
 * $Revision: 1.9 $
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
#include "ReportWindow.hxx"
#include "ReportSection.hxx"
#include "SectionView.hxx"
#include "ViewsWindow.hxx"
#include "ReportRuler.hxx"
#include "DesignView.hxx"

#include <tools/debug.hxx>
#include <svtools/colorcfg.hxx>
#include <svtools/itempool.hxx>
#include <svtools/syslocale.hxx>

#include "RptDef.hxx"
#include "dlgedfunc.hxx"
#include "RptModel.hxx"
#include "uistrings.hrc"
#include "RptPage.hxx"
#include "ReportController.hxx"
#include "EndMarker.hxx"
#include "ColorChanger.hxx"
#include "ScrollHelper.hxx"

#include "helpids.hrc"
#include "dlgedfac.hxx"
#include <boost/bind.hpp>
#include <toolkit/helper/vclunohelper.hxx>


#define SECTION_OFFSET	3
namespace rptui
{
using namespace ::com::sun::star;
using namespace ::comphelper;
//==================================================================
// class OReportWindow
//==================================================================
DBG_NAME( rpt_OReportWindow )
//------------------------------------------------------------------------------
OReportWindow::OReportWindow(OScrollWindowHelper* _pParent,ODesignView* _pView) 
: Window(_pParent,WB_DIALOGCONTROL)
,m_aHRuler(this)
,m_pView(_pView)
,m_pParent(_pParent)
,m_aViewsWindow(this)
,m_pObjFac( new DlgEdFactory() )
{
    DBG_CTOR( rpt_OReportWindow,NULL);
    SetHelpId(UID_RPT_REPORTWINDOW);
    SetMapMode( MapMode( MAP_100TH_MM ) );

    m_aViewsWindow.Show();

    m_aHRuler.Show();	
    m_aHRuler.Activate();
    m_aHRuler.SetPagePos(0);
    m_aHRuler.SetBorders();
    m_aHRuler.SetIndents();
    m_aHRuler.SetMargin1();
    m_aHRuler.SetMargin2();
    const MeasurementSystem eSystem = SvtSysLocale().GetLocaleData().getMeasurementSystemEnum();
    m_aHRuler.SetUnit(MEASURE_METRIC == eSystem ? FUNIT_CM : FUNIT_INCH);

    ImplInitSettings();
}
//------------------------------------------------------------------------------
OReportWindow::~OReportWindow()
{
    DBG_DTOR( rpt_OReportWindow,NULL);
}
// -----------------------------------------------------------------------------
void OReportWindow::initialize()
{
    m_aViewsWindow.initialize();
}
//----------------------------------------------------------------------------
void OReportWindow::SetInsertObj( USHORT eObj,const ::rtl::OUString& _sShapeType )
{
    m_aViewsWindow.SetInsertObj( eObj,_sShapeType);	
}

//----------------------------------------------------------------------------
rtl::OUString OReportWindow::GetInsertObjString() const
{
    return m_aViewsWindow.GetInsertObjString();
}
//------------------------------------------------------------------------------
void OReportWindow::SetMode( DlgEdMode eNewMode )
{
    m_aViewsWindow.SetMode(eNewMode);		
}
//----------------------------------------------------------------------------
void OReportWindow::removeSection(USHORT _nPosition)
{
    m_aViewsWindow.removeSection(_nPosition);
    m_pParent->setTotalSize(GetTotalWidth(),GetTotalHeight());
    m_aViewsWindow.Invalidate(INVALIDATE_TRANSPARENT);
    //Resize();
}
//----------------------------------------------------------------------------
void OReportWindow::addSection(const uno::Reference< report::XSection >& _xSection,const ::rtl::OUString& _sColorEntry,USHORT _nPosition)
{
    if ( !_xSection.is() )
        return;
    
    m_aViewsWindow.addSection(_xSection,_sColorEntry,_nPosition);	
    
    Resize();
    m_pParent->setTotalSize(GetTotalWidth(),GetTotalHeight());
}
//------------------------------------------------------------------------------
void OReportWindow::toggleGrid(sal_Bool _bVisible)
{
    m_aViewsWindow.toggleGrid(_bVisible);
}
//----------------------------------------------------------------------------
void OReportWindow::showRuler(sal_Bool _bShow)
{
    m_aHRuler.Show(_bShow);
    
    m_aViewsWindow.showRuler(_bShow);
}
//------------------------------------------------------------------------------
sal_Int32 OReportWindow::getMaxMarkerWidth(sal_Bool _bWithEnd) const
{
    Fraction aStartWith(long(REPORT_STARTMARKER_WIDTH));
    aStartWith *= m_aViewsWindow.GetMapMode().GetScaleX();
    if ( _bWithEnd )
        aStartWith += Fraction(long(REPORT_ENDMARKER_WIDTH));
    return sal_Int32((long)aStartWith);
}
//------------------------------------------------------------------------------
sal_Int32 OReportWindow::GetTotalWidth() const
{ 
    sal_Int32 nWidth = 0;
    if ( !m_aViewsWindow.empty() )
    {
        Fraction aStartWith(long(REPORT_ENDMARKER_WIDTH + REPORT_STARTMARKER_WIDTH));
        aStartWith *= m_aViewsWindow.GetMapMode().GetScaleX();
        const sal_Int32 nPaperWidth = getStyleProperty<awt::Size>(m_pView->getController().getReportDefinition(),PROPERTY_PAPERSIZE).Width;
        const Size aPageSize = m_aViewsWindow.LogicToPixel(Size(nPaperWidth,0));
        nWidth = aPageSize.Width() + long(aStartWith);
    }
    return nWidth; 
}
//------------------------------------------------------------------------------
void OReportWindow::Resize()
{
    Window::Resize();
    if ( !m_aViewsWindow.empty() )
    {
        const Size aTotalOutputSize = GetOutputSizePixel();
        Fraction aStartWith(long(REPORT_STARTMARKER_WIDTH));
        aStartWith *= m_aViewsWindow.GetMapMode().GetScaleX();

        const Point aOffset = LogicToPixel( Point( SECTION_OFFSET, SECTION_OFFSET ), MAP_APPFONT );
        Point aStartPoint((long)aStartWith + aOffset.X(),0);
        uno::Reference<report::XReportDefinition> xReportDefinition = getReportView()->getController().getReportDefinition();
        const sal_Int32 nPaperWidth = getStyleProperty<awt::Size>(xReportDefinition,PROPERTY_PAPERSIZE).Width;
        sal_Int32 nLeftMargin = getStyleProperty<sal_Int32>(xReportDefinition,PROPERTY_LEFTMARGIN);
        sal_Int32 nRightMargin = getStyleProperty<sal_Int32>(xReportDefinition,PROPERTY_RIGHTMARGIN);
        Size aPageSize  = m_aViewsWindow.LogicToPixel(Size(nPaperWidth,0));
        nLeftMargin     = m_aViewsWindow.LogicToPixel(Size(nLeftMargin,0)).Width();
        nRightMargin    = m_aViewsWindow.LogicToPixel(Size(nRightMargin,0)).Width();

        aPageSize.Height() = m_aHRuler.GetSizePixel().Height();

        const long nTermp(m_aViewsWindow.getTotalHeight() + aPageSize.Height());
        long nSectionsHeight = ::std::max<long>(nTermp,aTotalOutputSize.Height());

        m_aHRuler.SetPosSizePixel(aStartPoint,aPageSize);
        m_aHRuler.SetNullOffset(nLeftMargin);
        m_aHRuler.SetMargin1(0);
        m_aHRuler.SetMargin2(aPageSize.Width() - nLeftMargin - nRightMargin);
    
        aStartPoint.Y() += aPageSize.Height();
        nSectionsHeight -= aStartPoint.Y();

        aStartPoint.X() = aOffset.X();
      
        m_aViewsWindow.SetPosSizePixel(aStartPoint,Size(aTotalOutputSize.Width(),nSectionsHeight));
    }
}
//------------------------------------------------------------------------------
Point OReportWindow::getScrollOffset() const
{
    return m_pParent->getScrollOffset();
}
//------------------------------------------------------------------------------
void OReportWindow::ImplInitSettings()
{
    SetBackground( );
}
//-----------------------------------------------------------------------------
void OReportWindow::DataChanged( const DataChangedEvent& rDCEvt )
{
    Window::DataChanged( rDCEvt );

    if ( (rDCEvt.GetType() == DATACHANGED_SETTINGS) &&
         (rDCEvt.GetFlags() & SETTINGS_STYLE) )
    {
        ImplInitSettings();		
        Invalidate();
    }
}
//------------------------------------------------------------------------------
sal_Int32 OReportWindow::GetTotalHeight() const
{
    return m_aHRuler.GetSizePixel().Height() + m_aViewsWindow.getTotalHeight();
}
//------------------------------------------------------------------------------
void OReportWindow::ScrollChildren(long nDeltaX, long nDeltaY)
{
    if ( nDeltaX )
    {
        MapMode aMap = m_aHRuler.GetMapMode();
        Point aOrg( aMap.GetOrigin() );
        aMap.SetOrigin( Point(aOrg.X() - nDeltaX, aOrg.Y()));
        m_aHRuler.SetMapMode( aMap );
        m_aHRuler.Scroll(-nDeltaX,0);
    }

    
    m_aViewsWindow.scrollChildren(nDeltaX,nDeltaY);
}
//----------------------------------------------------------------------------
USHORT OReportWindow::getSectionCount() const
{
    return m_aViewsWindow.getSectionCount();
}
//----------------------------------------------------------------------------
void OReportWindow::notifyHeightChanged()
{
    m_pParent->setTotalSize(GetTotalWidth(),GetTotalHeight());
    //Resize();
    //Invalidate(INVALIDATE_TRANSPARENT);
}
//----------------------------------------------------------------------------
BOOL OReportWindow::HasSelection()
{
    return m_aViewsWindow.HasSelection();
}
//----------------------------------------------------------------------------
void OReportWindow::Delete()
{
    
    m_aViewsWindow.Delete();
}
//----------------------------------------------------------------------------
void OReportWindow::Copy()
{	
    
    m_aViewsWindow.Copy();
}
//----------------------------------------------------------------------------
void OReportWindow::Paste()
{
    
    m_aViewsWindow.Paste();
}
//----------------------------------------------------------------------------
BOOL OReportWindow::IsPasteAllowed()
{
    return m_aViewsWindow.IsPasteAllowed();
}
//-----------------------------------------------------------------------------
void OReportWindow::SelectAll(const sal_uInt16 _nObjectType)
{
    
    m_aViewsWindow.SelectAll(_nObjectType);
}
//-----------------------------------------------------------------------------
void OReportWindow::unmarkAllObjects(OSectionView* _pSectionView)
{
    
    m_aViewsWindow.unmarkAllObjects(_pSectionView);
}
//-----------------------------------------------------------------------------
void OReportWindow::showProperties(const uno::Reference< report::XSection>& _xReportComponent)
{
    ::boost::shared_ptr<OSectionWindow> pSectionWindow = m_aViewsWindow.getReportSection( _xReportComponent );
    m_pView->UpdatePropertyBrowserDelayed(pSectionWindow->getReportSection().getSectionView());
}
//------------------------------------------------------------------------------
sal_Bool OReportWindow::handleKeyEvent(const KeyEvent& _rEvent)
{
    return m_aViewsWindow.handleKeyEvent(_rEvent);
}
//------------------------------------------------------------------------
void OReportWindow::setMarked(OSectionView* _pSectionView,sal_Bool _bMark)
{
    if ( _pSectionView )
        m_aViewsWindow.setMarked(_pSectionView,_bMark);
}
//------------------------------------------------------------------------
void OReportWindow::setMarked(const uno::Reference< report::XSection>& _xSection,sal_Bool _bMark)
{
    
    m_aViewsWindow.setMarked(_xSection,_bMark);
}
//------------------------------------------------------------------------
void OReportWindow::setMarked(const uno::Sequence< uno::Reference< report::XReportComponent> >& _xShape,sal_Bool _bMark)
{
    
    m_aViewsWindow.setMarked(_xShape,_bMark);
}
//-----------------------------------------------------------------------------
::boost::shared_ptr<OSectionWindow> OReportWindow::getMarkedSection(NearSectionAccess nsa) const
{
    return  m_aViewsWindow.getMarkedSection(nsa);
}
// -------------------------------------------------------------------------
void OReportWindow::markSection(const sal_uInt16 _nPos) 
{
    
    m_aViewsWindow.markSection(_nPos);
}
// -----------------------------------------------------------------------------
void OReportWindow::fillCollapsedSections(::std::vector<sal_uInt16>& _rCollapsedPositions) const
{
    
    m_aViewsWindow.fillCollapsedSections(_rCollapsedPositions);
}
// -----------------------------------------------------------------------------
void OReportWindow::collapseSections(const uno::Sequence< ::com::sun::star::beans::PropertyValue>& _aCollpasedSections)
{
    
    m_aViewsWindow.collapseSections(_aCollpasedSections);
}
// -----------------------------------------------------------------------------
void OReportWindow::alignMarkedObjects(sal_Int32 _nControlModification,bool _bAlignAtSection, bool bBoundRects)
{
    
    m_aViewsWindow.alignMarkedObjects(_nControlModification, _bAlignAtSection, bBoundRects);
}
// -----------------------------------------------------------------------------
void OReportWindow::setGridSnap(BOOL bOn)
{
    
    m_aViewsWindow.setGridSnap(bOn);
}
// -----------------------------------------------------------------------------
void OReportWindow::setDragStripes(BOOL bOn)
{
    
    m_aViewsWindow.setDragStripes(bOn);
}
// -----------------------------------------------------------------------------
BOOL OReportWindow::isDragStripes() const
{
    return m_aViewsWindow.isDragStripes();
}
// -----------------------------------------------------------------------------
sal_uInt32 OReportWindow::getMarkedObjectCount() const
{
    return m_aViewsWindow.getMarkedObjectCount();
}
// -----------------------------------------------------------------------------
void OReportWindow::zoom(const sal_Int16 _nZoom)
{
    m_aHRuler.SetZoom(Fraction(_nZoom,100));
    m_aHRuler.Invalidate();
    
    m_aViewsWindow.zoom(_nZoom);
    notifyHeightChanged();
    Resize();
    
    Invalidate(INVALIDATE_NOERASE | INVALIDATE_NOCHILDREN | INVALIDATE_TRANSPARENT);
}
// -----------------------------------------------------------------------------
void OReportWindow::fillControlModelSelection(::std::vector< uno::Reference< uno::XInterface > >& _rSelection) const
{
    m_aViewsWindow.fillControlModelSelection(_rSelection);
}

//==================================================================
}	//rptui
//==================================================================

