/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: TableConnection.cxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 03:27:50 $
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
#ifndef DBAUI_TABLECONNECTION_HXX
#include "TableConnection.hxx"
#endif
#ifndef DBAUI_CONNECTIONLINE_HXX
#include "ConnectionLine.hxx"
#endif
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef DBACCESS_CONNECTIONLINEACCESS_HXX
#include "ConnectionLineAccess.hxx"
#endif
#include <algorithm>


using namespace dbaui;
using namespace comphelper;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::accessibility;

TYPEINIT0(OTableConnection);
//========================================================================
// class OTableConnection
//========================================================================
namespace dbaui
{
    DBG_NAME(OTableConnection)
    //------------------------------------------------------------------------
    OTableConnection::OTableConnection( OJoinTableView* _pContainer, OTableConnectionData* _pTabConnData )
        :Window(_pContainer)
        ,m_pData( _pTabConnData )
        ,m_pParent( _pContainer )
        ,m_bSelected( FALSE )
    {
        DBG_CTOR(OTableConnection,NULL);
        Init();
        Show();
    }

    //------------------------------------------------------------------------
    OTableConnection::OTableConnection( const OTableConnection& _rConn ) : Window(_rConn.m_pParent)
    {
        DBG_CTOR(OTableConnection,NULL);
        m_pData = _rConn.GetData()->NewInstance();
        *this = _rConn;
    }

    //------------------------------------------------------------------------
    void OTableConnection::Init()
    {
        //////////////////////////////////////////////////////////////////////
        // Linienliste mit Defaults initialisieren
        OConnectionLineDataVec* pLineData = GetData()->GetConnLineDataList();
        OConnectionLineDataVec::const_iterator aIter = pLineData->begin();
        m_vConnLine.reserve(pLineData->size());
        for(;aIter != pLineData->end();++aIter)
            m_vConnLine.push_back( new OConnectionLine(this, *aIter) );
    }

    //------------------------------------------------------------------------
    OConnectionLine* OTableConnection::CreateConnLine( const OConnectionLine& rConnLine )
    {
        return new OConnectionLine( rConnLine );
    }
    // -----------------------------------------------------------------------------
    void OTableConnection::clearLineData()
    {
        for(::std::vector<OConnectionLine*>::iterator aLineIter = m_vConnLine.begin();aLineIter != m_vConnLine.end();++aLineIter)
            delete *aLineIter;
        m_vConnLine.clear();
    }
    //------------------------------------------------------------------------
    void OTableConnection::UpdateLineList()
    {
        //////////////////////////////////////////////////////////////////////
        // Linienliste loeschen
        clearLineData();

        Init();
    }

    //------------------------------------------------------------------------
    OTableConnection& OTableConnection::operator=( const OTableConnection& rConn )
    {
        if( &rConn == this )
            return *this;

        // Linienliste loeschen
        clearLineData();

        // Linienliste kopieren
        if(! rConn.GetConnLineList()->empty() )
        {
            const ::std::vector<OConnectionLine*>* pLine = rConn.GetConnLineList();
            ::std::vector<OConnectionLine*>::const_iterator aIter = pLine->begin();
            m_vConnLine.reserve(pLine->size());
            for(;aIter != pLine->end();++aIter)
                m_vConnLine.push_back( CreateConnLine( **aIter ));
        }

        // da mir die Daten nicht gehoeren, loesche ich die alten nicht
        m_pData->CopyFrom(*rConn.GetData());
            // CopyFrom ist virtuell, damit ist es kein Problem, wenn m_pData von einem von OTableConnectionData abgeleiteten Typ ist

        m_bSelected = rConn.m_bSelected;
        m_pParent = rConn.m_pParent;

        return *this;
    }


    //------------------------------------------------------------------------
    bool OTableConnection::RecalcLines()
    {
        // call RecalcLines on each line
        ::std::for_each(m_vConnLine.begin(),m_vConnLine.end(),::std::mem_fun(&OConnectionLine::RecalcLine));
        return true;
    }
    //------------------------------------------------------------------------
    OTableWindow* OTableConnection::GetSourceWin() const
    {
        return m_pParent->GetTabWindow( GetData()->GetSourceWinName() );
    }
    //------------------------------------------------------------------------
    OTableWindow* OTableConnection::GetDestWin() const
    {
        return m_pParent->GetTabWindow( GetData()->GetDestWinName() );
    }

    //------------------------------------------------------------------------
    void OTableConnection::Select()
    {
        m_bSelected = TRUE;
        m_pParent->Invalidate( GetBoundingRect(), INVALIDATE_NOCHILDREN);
    }

    //------------------------------------------------------------------------
    void OTableConnection::Deselect()
    {
        m_bSelected = FALSE;
        InvalidateConnection();
    }

    //------------------------------------------------------------------------
    BOOL OTableConnection::CheckHit( const Point& rMousePos ) const
    {								 
        //////////////////////////////////////////////////////////////////////
        // check if the point hit our line
        ::std::vector<OConnectionLine*>::const_iterator aIter = ::std::find_if(m_vConnLine.begin(),
                                                                         m_vConnLine.end(),
                                                                         ::std::bind2nd(TConnectionLineCheckHitFunctor(),rMousePos));
        return aIter != m_vConnLine.end();
    }

    //------------------------------------------------------------------------
    bool OTableConnection::InvalidateConnection()
    {
        Rectangle rcBounding = GetBoundingRect();
        rcBounding.Bottom() += 1;
        rcBounding.Right() += 1;
            // ich glaube, dass sich Invalidate und Draw(Rectangle) nicht konsistent verhalten : jedenfalls waere dadurch zu
            // erklaeren, warum ohne diesen Fake hier beim Loeschen einer Connection ein Strich an ihrem unteren Ende stehen bleibt :
            // Invalidate erfasst dabei offensichtlich eine Pixelzeile weniger als Draw.
            // Oder alles haengt ganz anders zusammen ... jedenfalls klappt es so ...
        m_pParent->Invalidate( rcBounding, INVALIDATE_NOCHILDREN );

        return true;
    }

    //------------------------------------------------------------------------
    Rectangle OTableConnection::GetBoundingRect() const
    {
        //////////////////////////////////////////////////////////////////////
        // Aus allen Linien das umgebende Rechteck bestimmen
        Rectangle aBoundingRect( Point(0,0), Point(0,0) );
        Rectangle aTempRect;
        for(::std::vector<OConnectionLine*>::const_iterator aIter = m_vConnLine.begin();aIter != m_vConnLine.end();++aIter)
        {
            aTempRect = (*aIter)->GetBoundingRect();

            //////////////////////////////////////////////////////////////////////
            // Ist das BoundingRect dieser Linie gueltig?
            if( (aTempRect.GetWidth()!=1) && (aTempRect.GetHeight()!=1) )
            {
                if( (aBoundingRect.GetWidth()==1) && (aBoundingRect.GetHeight()==1) )
                    aBoundingRect = aTempRect;
                else
                    aBoundingRect.Union( aTempRect );
            }
        }

        return aBoundingRect;
    }

    //------------------------------------------------------------------------
    void OTableConnection::Draw( const Rectangle& /*rRect*/ )
    {
        //////////////////////////////////////////////////////////////////////
        // Linien zeichnen
        ::std::for_each(m_vConnLine.begin(),m_vConnLine.end(),TConnectionLineDrawFunctor(m_pParent));
    }
    // -----------------------------------------------------------------------------
}



