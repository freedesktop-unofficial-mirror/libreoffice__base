/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: QueryViewSwitch.cxx,v $
 *
 *  $Revision: 1.28 $
 *
 *  last change: $Author: kz $ $Date: 2007-05-10 10:38:41 $
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
#ifndef DBAUI_QUERYVIEWSWITCH_HXX
#include "QueryViewSwitch.hxx"
#endif
#ifndef DBAUI_QUERYDESIGNVIEW_HXX
#include "QueryDesignView.hxx"
#endif
#ifndef DBAUI_QUERYVIEW_TEXT_HXX
#include "QueryTextView.hxx"
#endif
#ifndef DBAUI_QUERYCONTAINERWINDOW_HXX
#include "querycontainerwindow.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBU_QRY_HRC_
#include "dbu_qry.hrc"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef DBAUI_QYDLGTAB_HXX
#include "adtabdlg.hxx"
#endif
#ifndef DBAUI_QUERYCONTROLLER_HXX
#include "querycontroller.hxx"
#endif
#ifndef DBAUI_SQLEDIT_HXX
#include "sqledit.hxx"
#endif
#ifndef DBAUI_QUERYCONTAINERWINDOW_HXX
#include "querycontainerwindow.hxx"
#endif

using namespace dbaui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;

DBG_NAME(OQueryViewSwitch)
OQueryViewSwitch::OQueryViewSwitch(OQueryContainerWindow* _pParent, OQueryController* _pController,const Reference< XMultiServiceFactory >& _rFactory)
: m_bAddTableDialogWasVisible(sal_False)
{								 
    DBG_CTOR(OQueryViewSwitch,NULL);
    
    m_pTextView		= new OQueryTextView(_pParent);
    m_pDesignView	= new OQueryDesignView(_pParent,_pController,_rFactory);
}
// -----------------------------------------------------------------------------
OQueryViewSwitch::~OQueryViewSwitch()
{
    DBG_DTOR(OQueryViewSwitch,NULL);
    {
        ::std::auto_ptr<Window> aTemp(m_pTextView);
        m_pTextView = NULL;
    }
    {
        ::std::auto_ptr<Window> aTemp(m_pDesignView);
        m_pDesignView = NULL;
    }	
}
// -------------------------------------------------------------------------
void OQueryViewSwitch::Construct()
{
    m_pDesignView->Construct( );
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::initialize()
{
    // initially be in SQL mode
    m_pTextView->Show();
    m_pDesignView->initialize();
}
// -------------------------------------------------------------------------
void OQueryViewSwitch::resizeDocumentView(Rectangle& _rPlayground)
{
    m_pTextView->SetPosSizePixel( _rPlayground.TopLeft(), _rPlayground.GetSize() );
    m_pDesignView->SetPosSizePixel( _rPlayground.TopLeft(), _rPlayground.GetSize() );
    
    // just for completeness: there is no space left, we occupied it all ...
    _rPlayground.SetPos( _rPlayground.BottomRight() );
    _rPlayground.SetSize( Size( 0, 0 ) );
}
// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::checkStatement()
{
    if(m_pTextView->IsVisible())
        return m_pTextView->checkStatement();
    return m_pDesignView->checkStatement();
}
// -----------------------------------------------------------------------------
::rtl::OUString OQueryViewSwitch::getStatement()
{
    if(m_pTextView->IsVisible())
        return m_pTextView->getStatement();
    return m_pDesignView->getStatement();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::setReadOnly(sal_Bool _bReadOnly)
{
    if(m_pTextView->IsVisible())
        m_pTextView->setReadOnly(_bReadOnly);
    else
        m_pDesignView->setReadOnly(_bReadOnly);
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::clear()
{
    if(m_pTextView->IsVisible())
        m_pTextView->clear();
    else
        m_pDesignView->clear();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::GrabFocus()
{
    if ( m_pTextView && m_pTextView->IsVisible() )
        m_pTextView->GrabFocus();
    else if ( m_pDesignView && m_pDesignView->IsVisible() )
        m_pDesignView->GrabFocus();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::setStatement(const ::rtl::OUString& _rsStatement)
{
    if(m_pTextView->IsVisible())
        m_pTextView->setStatement(_rsStatement);
    else
        m_pDesignView->setStatement(_rsStatement);
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::copy()
{
    if(m_pTextView->IsVisible())
        m_pTextView->copy();
    else
        m_pDesignView->copy();
}
// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::isCutAllowed()
{
    if(m_pTextView->IsVisible())
        return m_pTextView->isCutAllowed();
    return m_pDesignView->isCutAllowed();
}
// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::isCopyAllowed()
{
    if(m_pTextView->IsVisible())
        return m_pTextView->isCopyAllowed();
    return m_pDesignView->isCopyAllowed();
}
// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::isPasteAllowed()
{
    if(m_pTextView->IsVisible())
        return m_pTextView->isPasteAllowed();
    return m_pDesignView->isPasteAllowed();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::cut()
{
    if(m_pTextView->IsVisible())
        m_pTextView->cut();
    else
        m_pDesignView->cut();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::paste()
{
    if(m_pTextView->IsVisible())
        m_pTextView->paste();
    else
        m_pDesignView->paste();
}
// -----------------------------------------------------------------------------
OQueryContainerWindow* OQueryViewSwitch::getContainer() const
{
    Window* pDesignParent = getDesignView() ? getDesignView()->GetParent() : NULL;
    return static_cast< OQueryContainerWindow* >( pDesignParent );
}

// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::switchView()
{
    sal_Bool bRet = sal_True;
    sal_Bool bGraphicalDesign = static_cast<OQueryController*>(m_pDesignView->getController())->isDesignMode();

    OAddTableDlg* pAddTabDialog( getAddTableDialog() );

    if ( !bGraphicalDesign ) // we have to hide the add table dialog
    {
        m_bAddTableDialogWasVisible = pAddTabDialog ? pAddTabDialog->IsVisible() : false;
        if ( m_bAddTableDialogWasVisible )
            pAddTabDialog->Hide();
    }

    OQueryContainerWindow* pContainer = getContainer();
    if ( !bGraphicalDesign )
    {
        m_pDesignView->stopTimer();
        m_pTextView->getSqlEdit()->startTimer();

        m_pTextView->clear();
        m_pTextView->setStatement(static_cast<OQueryController*>(m_pDesignView->getController())->getStatement());
    }
    else
    {
        ::rtl::OUString sOldStatement = static_cast<OQueryController*>(m_pDesignView->getController())->getStatement();
        // we have to stop the sqledit from our textview
        m_pTextView->getSqlEdit()->stopTimer();

        if ( pAddTabDialog )
            pAddTabDialog->Update();
        bRet = m_pDesignView->InitFromParseNode();

        // only show the view when the data is inserted
        m_pDesignView->startTimer();
    }

    if ( bRet )
    {
        m_pTextView->Show	( !bGraphicalDesign );
        m_pDesignView->Show	( bGraphicalDesign );
        if ( bGraphicalDesign && m_bAddTableDialogWasVisible && pAddTabDialog )
            pAddTabDialog->Show();

        GrabFocus();
    }

    if ( pContainer )
        pContainer->Resize();

    m_pDesignView->getController()->getUndoMgr()->Clear();
    m_pDesignView->getController()->InvalidateAll();

    return bRet;
}
// -----------------------------------------------------------------------------
OAddTableDlg* OQueryViewSwitch::getAddTableDialog()
{
    if ( !m_pDesignView )
        return NULL;
    if ( !m_pDesignView->getController() )
        return NULL;
    return m_pDesignView->getController()->getAddTableDialog();
}
// -----------------------------------------------------------------------------
sal_Bool OQueryViewSwitch::isSlotEnabled(sal_Int32 _nSlotId)
{
    return m_pDesignView->isSlotEnabled(_nSlotId); 
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::setSlotEnabled(sal_Int32 _nSlotId,sal_Bool _bEnable)
{
    m_pDesignView->setSlotEnabled(_nSlotId,_bEnable); 
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::SaveUIConfig()
{
    if(m_pDesignView->IsVisible())
        m_pDesignView->SaveUIConfig();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::SetPosSizePixel( Point _rPt,Size _rSize)
{
    m_pDesignView->SetPosSizePixel( _rPt,_rSize);
    m_pDesignView->Resize();
    m_pTextView->SetPosSizePixel( _rPt,_rSize);
}
// -----------------------------------------------------------------------------
Reference< XMultiServiceFactory > OQueryViewSwitch::getORB() const 
{ 
    return m_pDesignView->getORB(); 
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::reset()
{
    m_pDesignView->reset();
    if ( m_pDesignView->InitFromParseNode() )
        switchView();
}
// -----------------------------------------------------------------------------
void OQueryViewSwitch::setNoneVisbleRow(sal_Int32 _nRows)
{
    if(m_pDesignView)
        m_pDesignView->setNoneVisbleRow(_nRows);	
}
// -----------------------------------------------------------------------------
