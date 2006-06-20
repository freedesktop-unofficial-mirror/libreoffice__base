/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ConnectionLine.cxx,v $
 *
 *  $Revision: 1.10 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 03:24:53 $
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
#ifndef DBAUI_CONNECTIONLINE_HXX
#include "ConnectionLine.hxx"
#endif
#ifndef DBAUI_CONNECTIONLINEDATA_HXX
#include "ConnectionLineData.hxx"
#endif
#ifndef DBAUI_TABLEWINDOW_HXX
#include "TableWindow.hxx"
#endif
#ifndef DBAUI_TABLEWINDOWLISTBOX_HXX
#include "TableWindowListBox.hxx"
#endif
#ifndef DBAUI_TABLECONNECTION_HXX
#include "TableConnection.hxx"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _INC_MATH
#include <math.h>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif


using namespace dbaui;
const long DESCRIPT_LINE_WIDTH = 15;
const long HIT_SENSITIVE_RADIUS = 5;

namespace
{
    /** calcRect creates a new rectangle with the given points
            @param	_rBase		the base point
            @param	_aVector	the vector which will be added
    */
    inline Rectangle calcRect(const Point& _rBase,const Point& _aVector)
    {
        return Rectangle( _rBase - _aVector, _rBase + _aVector );
    }
    // -----------------------------------------------------------------------------
    /** GetTextPos calculate the rectangle for the connection to be drawn
            @param	_pWin			the table window where to draw it
            @param	_aConnPos		the connection point
            @param	_aDescrLinePos	the description line pos
    */
    Rectangle GetTextPos(const OTableWindow* _pWin, const Point& _aConnPos,const Point& _aDescrLinePos)
    {
        OTableWindowListBox* pListBox = _pWin ? _pWin->GetListBox() : NULL;
        DBG_ASSERT(_pWin && pListBox, "OConnectionLine::GetSourceTextPos : invalid call !");

        Rectangle aReturn;
        if ( pListBox )
        {
            long nRowHeight = pListBox->GetEntryHeight();
            aReturn.Top() = _aConnPos.Y() - nRowHeight;
            aReturn.Bottom() = aReturn.Top() + nRowHeight;
            if (_aDescrLinePos.X() < _aConnPos.X())
            {
                aReturn.Left() = _aDescrLinePos.X();
                aReturn.Right() = aReturn.Left() + _aConnPos.X() - _aDescrLinePos.X();
            }
            else
            {
                aReturn.Left() = _aConnPos.X();
                aReturn.Right() = aReturn.Left() + _aDescrLinePos.X() - _aConnPos.X();
            }
        }

        return aReturn;
    }
    // -----------------------------------------------------------------------------
    /** calcPointsYValue calculate the points Y value in relation to the listbox entry
            @param	_pWin			the corresponding window
            @param	_pEntry			the source or dest entry
            @param	_rNewConPos		(in/out) the connection pos
            @param	_rNewDescrPos	(in/out) the description pos
    */
    void calcPointsYValue(const OTableWindow* _pWin,SvLBoxEntry* _pEntry,Point& _rNewConPos,Point& _rNewDescrPos)
    {
        const OTableWindowListBox* pListBox = _pWin->GetListBox();
        long nRowHeight = pListBox->GetEntryHeight();

        _rNewConPos.Y() = _pWin->GetPosPixel().Y();
        _rNewConPos.Y() += pListBox->GetPosPixel().Y();
        long nEntryPos = pListBox->GetEntryPosition( _pEntry ).Y();

        if( nEntryPos >= 0 )
        {
            _rNewConPos.Y() += nEntryPos;
            _rNewConPos.Y() += (long)( 0.5 * nRowHeight );
        }
        else
            _rNewConPos.Y() -= (long)( 0.5 * nRowHeight );

        long nListBoxBottom = _pWin->GetPosPixel().Y()
                                + pListBox->GetPosPixel().Y()
                                + pListBox->GetSizePixel().Height();
        if( _rNewConPos.Y() > nListBoxBottom )
            _rNewConPos.Y() = nListBoxBottom + 2;

        _rNewDescrPos.Y() = _rNewConPos.Y();
    }
    // -----------------------------------------------------------------------------
}

//========================================================================
// class OConnectionLine
//========================================================================
DBG_NAME(OConnectionLine)
//------------------------------------------------------------------------
OConnectionLine::OConnectionLine( OTableConnection* _pConn, OConnectionLineDataRef _pLineData )
    : m_pTabConn( _pConn )
     ,m_pData( _pLineData )
     ,m_pSourceEntry( NULL )
     ,m_pDestEntry( NULL )
{
    DBG_CTOR(OConnectionLine,NULL);
}

//------------------------------------------------------------------------
OConnectionLine::OConnectionLine( OTableConnection* _pConn, const String& _rSourceFieldName,
                                  const String& _rDestFieldName )
    :m_pTabConn( _pConn )
    ,m_pData(NULL)
    ,m_pSourceEntry( NULL )
    ,m_pDestEntry( NULL )
{
    DBG_CTOR(OConnectionLine,NULL);
    m_pData = new OConnectionLineData( _rSourceFieldName,_rDestFieldName);
}

//------------------------------------------------------------------------
OConnectionLine::OConnectionLine( const OConnectionLine& _rLine )
{
    DBG_CTOR(OConnectionLine,NULL);
    m_pData = new OConnectionLineData( *_rLine.GetData() );
    *this = _rLine;
}

//------------------------------------------------------------------------
OConnectionLine::~OConnectionLine()
{
    DBG_DTOR(OConnectionLine,NULL);
}

//------------------------------------------------------------------------
void OConnectionLine::SetSourceFieldName( const String& rSourceFieldName )
{
    m_pData->SetSourceFieldName( rSourceFieldName );
}

//------------------------------------------------------------------------
void OConnectionLine::SetDestFieldName( const String& rDestFieldName )
{
    m_pData->SetDestFieldName( rDestFieldName );
}

//------------------------------------------------------------------------
OConnectionLine& OConnectionLine::operator=( const OConnectionLine& rLine )
{
    if( &rLine != this )
    {
        // da mir die Daten nicht gehoeren, loesche ich die alten nicht
        m_pData->CopyFrom(*rLine.GetData());
            // CopyFrom ist virtuell, damit ist es kein Problem, wenn m_pData von einem von OTableConnectionData abgeleiteten Typ ist

        m_pTabConn = rLine.m_pTabConn;
        m_pSourceEntry = rLine.m_pSourceEntry;
        m_pDestEntry = rLine.m_pDestEntry;
        m_aSourceConnPos = rLine.m_aSourceConnPos;
        m_aDestConnPos = rLine.m_aDestConnPos;
        m_aSourceDescrLinePos = rLine.m_aSourceDescrLinePos;
        m_aDestDescrLinePos = rLine.m_aDestDescrLinePos;
    }

    return *this;
}

//------------------------------------------------------------------------
BOOL OConnectionLine::Connect( const String& rSourceFieldName, const String& rDestFieldName )
{
    //////////////////////////////////////////////////////////////////////
    // Parameter duerfen nicht leer sein
    if( !rSourceFieldName.Len() || !rDestFieldName.Len() )
        return FALSE;

    //////////////////////////////////////////////////////////////////////
    // Feldnamen setzen
    m_pData->SetSourceFieldName( rSourceFieldName );
    m_pData->SetDestFieldName( rDestFieldName );

    return TRUE;
}


//------------------------------------------------------------------------
Rectangle OConnectionLine::GetBoundingRect()
{
    //////////////////////////////////////////////////////////////////////
    // Umgebendes Rechteck bestimmen
    Rectangle aBoundingRect( Point(0,0), Point(0,0) );
    if( !IsValid() )
        return aBoundingRect;

    Point aTopLeft;
    Point aBottomRight;

    if( m_aSourceDescrLinePos.Y() <= m_aDestDescrLinePos.Y() )
    {
        aTopLeft.Y() = m_aSourceDescrLinePos.Y();
        aBottomRight.Y() = m_aDestDescrLinePos.Y();
    }
    else
    {
        aTopLeft.Y() = m_aDestDescrLinePos.Y();
        aBottomRight.Y() = m_aSourceDescrLinePos.Y();
    }

    if( m_aSourceDescrLinePos.X() <= m_aDestDescrLinePos.X() )
    {
        aTopLeft.X() = m_aSourceDescrLinePos.X();
        aBottomRight.X() = m_aDestDescrLinePos.X();
    }
    else
    {
        aTopLeft.X() = m_aDestDescrLinePos.X();
        aBottomRight.X() = m_aSourceDescrLinePos.X();
    }

    //////////////////////////////////////////////////////////////////////
    // Linie verlaeuft in z-Form
    if( Abs(m_aSourceConnPos.X() - m_aDestConnPos.X()) > Abs(m_aSourceDescrLinePos.X() - m_aDestDescrLinePos.X()) )
    {
        aTopLeft.X() -= DESCRIPT_LINE_WIDTH;
        aBottomRight.X() += DESCRIPT_LINE_WIDTH;
    }

    aBoundingRect = Rectangle( aTopLeft-Point(0,17), aBottomRight+Point(0,2) );

    return aBoundingRect;
}
// -----------------------------------------------------------------------------
void calcPointX1(const OTableWindow* _pWin,Point& _rNewConPos,Point& _rNewDescrPos)
{
    _rNewConPos.X() = _pWin->GetPosPixel().X() + _pWin->GetSizePixel().Width();
    _rNewDescrPos.X() = _rNewConPos.X();
    _rNewConPos.X() += DESCRIPT_LINE_WIDTH;
}
// -----------------------------------------------------------------------------
void calcPointX2(const OTableWindow* _pWin,Point& _rNewConPos,Point& _rNewDescrPos)
{
    _rNewConPos.X() = _pWin->GetPosPixel().X();
    _rNewDescrPos.X() = _rNewConPos.X();
    _rNewConPos.X() -= DESCRIPT_LINE_WIDTH;
}
//------------------------------------------------------------------------
BOOL OConnectionLine::RecalcLine()
{
    //////////////////////////////////////////////////////////////////////
    // Fenster und Entries muessen gesetzt sein
    const OTableWindow* pSourceWin = m_pTabConn->GetSourceWin();
    const OTableWindow* pDestWin = m_pTabConn->GetDestWin();

    if( !pSourceWin || !pDestWin )
        return FALSE;

    m_pSourceEntry = pSourceWin->GetListBox()->GetEntryFromText( GetData()->GetSourceFieldName() );
    m_pDestEntry = pDestWin->GetListBox()->GetEntryFromText( GetData()->GetDestFieldName() );

    if( !m_pSourceEntry || !m_pDestEntry )
        return FALSE;

    //////////////////////////////////////////////////////////////////////
    // X-Koordinaten bestimmen
    Point aSourceCenter( 0, 0 );
    Point aDestCenter( 0, 0 );

    aSourceCenter.X() = pSourceWin->GetPosPixel().X() + (long)( 0.5*pSourceWin->GetSizePixel().Width() );
    aDestCenter.X() = pDestWin->GetPosPixel().X() + (long)( 0.5*pDestWin->GetSizePixel().Width() );

    const OTableWindow* pFirstWin	= pDestWin;
    const OTableWindow* pSecondWin	= pSourceWin;
    Point* pFirstConPos				= &m_aDestConnPos;
    Point* pFirstDescrPos			= &m_aDestDescrLinePos;
    Point* pSecondConPos			= &m_aSourceConnPos;
    Point* pSecondDescrPos			= &m_aSourceDescrLinePos;
    if( aDestCenter.X() > aSourceCenter.X() )
    {
        pFirstWin		= pSourceWin;
        pSecondWin		= pDestWin;
        pFirstConPos	= &m_aSourceConnPos;
        pFirstDescrPos	= &m_aSourceDescrLinePos;
        pSecondConPos	= &m_aDestConnPos;
        pSecondDescrPos	= &m_aDestDescrLinePos;
    }

    calcPointX1(pFirstWin,*pFirstConPos,*pFirstDescrPos);
    calcPointX2(pSecondWin,*pSecondConPos,*pSecondDescrPos);

    //////////////////////////////////////////////////////////////////////
    // aSourceConnPosY bestimmen
    calcPointsYValue(pSourceWin,m_pSourceEntry,m_aSourceConnPos,m_aSourceDescrLinePos);
    
    //////////////////////////////////////////////////////////////////////
    // aDestConnPosY bestimmen
    calcPointsYValue(pDestWin,m_pDestEntry,m_aDestConnPos,m_aDestDescrLinePos);

    return TRUE;
}
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------
void OConnectionLine::Draw( OutputDevice* pOutDev )
{
    const UINT16 nRectSize = 3;

    //////////////////////////////////////////////////////////////////////
    // Neue Dimensionen berechnen
    if( !RecalcLine() )
        return;

    //////////////////////////////////////////////////////////////////////
    // Zeichnen der Linien
    if (m_pTabConn->IsSelected())
        pOutDev->SetLineColor(Application::GetSettings().GetStyleSettings().GetHighlightColor());
    else
        pOutDev->SetLineColor(Application::GetSettings().GetStyleSettings().GetWindowTextColor());

    pOutDev->DrawLine( m_aSourceDescrLinePos, m_aSourceConnPos );
    pOutDev->DrawLine( m_aDestDescrLinePos, m_aDestConnPos );
    pOutDev->DrawLine( m_aSourceConnPos, m_aDestConnPos );
    // wenn die  Linie selektiert ist, sollte sie dicker erscheinen
    // da OutputDevice nach meinem Wissen (das ich nur aus dem Headerfile habe) kein
    // SetLineWidth (o.�.) hat, ein Fake
    if (m_pTabConn->IsSelected())
    {
        UINT16 xOffset, yOffset;
        if (abs(m_aSourceConnPos.Y() - m_aDestConnPos.Y()) > abs(m_aSourceConnPos.X()-m_aDestConnPos.X()))
        {
            xOffset = 1;
            yOffset = 0;
        } else
        {
            xOffset = 0;
            yOffset = 1;
        }

        Point aPos1(-xOffset, -yOffset);
        Point aPos2(xOffset, yOffset);
        pOutDev->DrawLine(m_aSourceConnPos + aPos1, m_aDestConnPos + aPos1);
        pOutDev->DrawLine(m_aSourceConnPos + aPos2, m_aDestConnPos + aPos2);
    }


    //////////////////////////////////////////////////////////////////////
    // draw the connection rectangles
    pOutDev->SetFillColor(Application::GetSettings().GetStyleSettings().GetWindowColor());

    Point aVector(nRectSize,nRectSize);
    pOutDev->DrawRect( calcRect(m_aSourceDescrLinePos,aVector) );
    pOutDev->DrawRect( calcRect( m_aDestDescrLinePos,aVector) );
}
// -----------------------------------------------------------------------------
BOOL OConnectionLine::IsValid() const
{
    return m_pData.isValid() && m_pData->IsValid();
}
//------------------------------------------------------------------------
double dist_Euklid(const Point &p1, const Point& p2,const Point& pM, Point& q)
{
    Point v(p2 - p1);
    Point w(pM - p1);
    double a = sqrt((double)(v.X()*v.X() + v.Y()*v.Y()));
    double l = (v.X() * w.Y() - v.Y() * w.X()) / a;
    double a2 = w.X()*v.X()+w.Y()*v.Y();
    a = a2 / (a * a);
    q.X() = long(p1.X() + a * v.X()); 
    q.Y() = long(p1.Y() + a * v.Y());
    return l;
}
//------------------------------------------------------------------------
bool OConnectionLine::CheckHit( const Point& rMousePos ) const
{
    //////////////////////////////////////////////////////////////////////
    /*
        Vorgehensweise beim HitTest:
        Es wird der Abstand nach Euklid berechnet.
    */
    Point q;
    double l = fabs(dist_Euklid(m_aSourceConnPos,m_aDestConnPos,rMousePos,q));
    if( l < HIT_SENSITIVE_RADIUS)
    {
        if(::std::min(m_aSourceConnPos.X(),m_aDestConnPos.X()) <= q.X() && ::std::min(m_aSourceConnPos.Y(),m_aDestConnPos.Y()) <= q.Y()
            && q.X() <= ::std::max(m_aDestConnPos.X(),m_aSourceConnPos.X())   && q.Y() <= ::std::max(m_aDestConnPos.Y(),m_aSourceConnPos.Y()))
            return true;
    }

    return false;
}
// -----------------------------------------------------------------------------
Rectangle OConnectionLine::GetSourceTextPos() const 
{ 
    return GetTextPos(m_pTabConn->GetSourceWin(),m_aSourceConnPos,m_aSourceDescrLinePos); 
}
// -----------------------------------------------------------------------------
Rectangle OConnectionLine::GetDestTextPos() const 
{ 
    return GetTextPos(m_pTabConn->GetDestWin(),m_aDestConnPos,m_aDestDescrLinePos); 
}
// -----------------------------------------------------------------------------
Point OConnectionLine::getMidPoint() const
{
    Point aDest = m_aDestConnPos - m_aSourceConnPos;
    aDest.X() /= 2;
    aDest.Y() /= 2;

    return m_aSourceConnPos + aDest;
}
// -----------------------------------------------------------------------------


