/*************************************************************************
 *
 *  $RCSfile: JoinDesignView.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: fs $ $Date: 2001-03-15 08:26:26 $
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
#ifndef DBAUI_JOINDESIGNVIEW_HXX
#include "JoinDesignView.hxx"
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif
#ifndef _SV_TOOLBOX_HXX 
#include <vcl/toolbox.hxx>
#endif
#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef _UNDO_HXX
#include <svtools/undo.hxx>
#endif
#ifndef DBAUI_QYDLGTAB_HXX
#include "adtabdlg.hxx"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef DBAUI_TABLECONNECTION_HXX
#include "TableConnection.hxx"
#endif
#ifndef DBAUI_CONNECTIONLINE_HXX
#include "ConnectionLine.hxx"
#endif
#ifndef DBAUI_CONNECTIONLINEDATA_HXX
#include "ConnectionLineData.hxx"
#endif
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif

using namespace ::dbaui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::i18n;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

OJoinDesignView::OJoinDesignView(Window* _pParent, OJoinController* _pController,const Reference< XMultiServiceFactory >& _rFactory)
    :ODataView(_pParent,_rFactory)
    ,m_pController(_pController)
    ,m_pTableView(NULL)
    ,m_pAddTabDlg(NULL)
{
    m_pScrollWindow = new OScrollWindowHelper(this);
}
// -----------------------------------------------------------------------------
OJoinDesignView::~OJoinDesignView()
{
    delete m_pAddTabDlg;
    delete m_pTableView;
    delete m_pScrollWindow;
}
// -------------------------------------------------------------------------
void OJoinDesignView::Construct(const Reference< ::com::sun::star::awt::XControlModel >& xModel)
{
    m_pScrollWindow->setTableView(m_pTableView);
    m_pScrollWindow->Show();
    m_pTableView->Show();
    
    m_pAddTabDlg = new OAddTableDlg(m_pTableView);
    SetBackground( Wallpaper( Application::GetSettings().GetStyleSettings().GetFaceColor()) );

    ODataView::Construct(xModel); // initialize m_xMe
}
// -----------------------------------------------------------------------------
void OJoinDesignView::initialize()
{
    getAddTableDialog()->Update();
}
// -------------------------------------------------------------------------
void OJoinDesignView::resizeControl(Rectangle& _rRect)
{
    Window::Resize();
    Size aSize = GetOutputSizePixel();

    Size aToolBoxSize;
    ToolBox* pToolBox = getToolBox();
    if(pToolBox)
        aToolBoxSize = pToolBox->GetOutputSizePixel();
    Point aTopLeft(_rRect.TopLeft());
    aTopLeft.Y() += aToolBoxSize.Height();

    aSize.Height() -= aToolBoxSize.Height();
    m_pScrollWindow->SetPosSizePixel(aTopLeft,aSize);
    
    aToolBoxSize.Width() += _rRect.getWidth();
    _rRect.SetSize(aToolBoxSize);
}
// -----------------------------------------------------------------------------
void OJoinDesignView::setReadOnly(sal_Bool _bReadOnly)
{
}
// -----------------------------------------------------------------------------
void OJoinDesignView::TableDeleted(const ::rtl::OUString& rAliasName)
{
}
// -----------------------------------------------------------------------------
void OJoinDesignView::zoomTableView(const Fraction& _rFraction)
{
    m_pTableView->SetZoom(_rFraction);
}
// -----------------------------------------------------------------------------
void OJoinDesignView::SaveUIConfig()
{
    OJoinController* pCtrl = getController();
    if (pCtrl)
        pCtrl->SaveTabWinsPosSize( m_pTableView->GetTabWinMap(), m_pScrollWindow->GetHScrollBar()->GetThumbPos(), m_pScrollWindow->GetVScrollBar()->GetThumbPos() );
}
// -----------------------------------------------------------------------------
void OJoinDesignView::SaveTabWinUIConfig(OTableWindow* pWin)
{
    getController()->SaveTabWinPosSize(pWin, m_pScrollWindow->GetHScrollBar()->GetThumbPos(), m_pScrollWindow->GetVScrollBar()->GetThumbPos());
}
// -----------------------------------------------------------------------------






