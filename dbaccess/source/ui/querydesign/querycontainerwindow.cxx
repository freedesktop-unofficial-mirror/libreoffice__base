/*************************************************************************
 *
 *  $RCSfile: querycontainerwindow.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: oj $ $Date: 2002-03-01 14:42:07 $
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef DBAUI_QUERYCONTAINERWINDOW_HXX
#include "querycontainerwindow.hxx"
#endif
#ifndef DBAUI_QUERYDESIGNVIEW_HXX
#include "QueryDesignView.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif
#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_ 
#include <toolkit/unohlp.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _SFXSIDS_HRC
#include <sfx2/sfxsids.hrc>
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_TOOLBOX_HXX 
#include <vcl/toolbox.hxx>
#endif
//.........................................................................
namespace dbaui
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::frame;

    //=====================================================================
    //= OQueryContainerWindow
    //=====================================================================
    DBG_NAME(OQueryContainerWindow)
    OQueryContainerWindow::OQueryContainerWindow(Window* pParent, OQueryController* _pController,const Reference< XMultiServiceFactory >& _rFactory) 
        :ODataView(pParent,_pController, _rFactory)
        ,m_pBeamerSeparator( NULL )
        ,m_pBeamer(NULL)
        ,m_pViewSwitch(NULL)
    {
        DBG_CTOR(OQueryContainerWindow,NULL);
        m_pViewSwitch = new OQueryViewSwitch(this,_pController,_rFactory);
        
        m_pSplitter = new Splitter(this,WB_VSCROLL);
        m_pSplitter->Hide();
        m_pSplitter->SetSplitHdl( LINK( this, OQueryContainerWindow, SplitHdl ) );
        m_pSplitter->SetBackground( Wallpaper( Application::GetSettings().GetStyleSettings().GetDialogColor() ) );
    }
    // -----------------------------------------------------------------------------
    OQueryContainerWindow::~OQueryContainerWindow()
    {
        if(m_xBeamer.is())
            m_xBeamer->setComponent(NULL,NULL);
        m_xBeamer	= NULL;
        DELETEZ( m_pBeamer );
        DELETEZ( m_pBeamerSeparator );
        DELETEZ( m_pSplitter );
        DELETEZ( m_pViewSwitch );
        DBG_DTOR(OQueryContainerWindow,NULL);
    }
    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::switchView()
    {
        m_pViewSwitch->switchView();
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::resizeAll( const Rectangle& _rPlayground )
    {
        Rectangle aPlayground( _rPlayground );

        if ( m_pBeamer && m_pBeamer->IsVisible() )
        {
            // position the beamer separator
            if ( m_pBeamerSeparator )
            {
                Size aSeparatorSize = Size( aPlayground.GetWidth(), 2 );
                m_pBeamerSeparator->SetPosSizePixel( aPlayground.TopLeft(), aSeparatorSize );
                aPlayground.Top() += aSeparatorSize.Height() + 1;
            }

            // calc pos and size of the splitter
            Point aSplitPos		= m_pSplitter->GetPosPixel();
            Size aSplitSize		= m_pSplitter->GetOutputSizePixel();
            aSplitSize.Width() = aPlayground.GetWidth();

            if ( aSplitPos.Y() <= aPlayground.Top() )
                aSplitPos.Y() = aPlayground.Top() + sal_Int32( aPlayground.GetHeight() * 0.2 );

            if ( aSplitPos.Y() + aSplitSize.Height() > aPlayground.GetHeight() )
                aSplitPos.Y() = aPlayground.GetHeight() - aSplitSize.Height();

            // set pos and size of the splitter
            m_pSplitter->SetPosSizePixel( aSplitPos, aSplitSize );
            m_pSplitter->SetDragRectPixel(	aPlayground );

            // set pos and size of the beamer
            Size aBeamerSize( aPlayground.GetWidth(), aSplitPos.Y() );
            m_pBeamer->SetPosSizePixel( aPlayground.TopLeft(), aBeamerSize );

            // shrink the playground by the size which is occupied by the beamer
            aPlayground.Top() = aSplitPos.Y() + aSplitSize.Height();
        }

        ODataView::resizeAll( aPlayground );
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::resizeDocumentView( Rectangle& _rPlayground )
    {
        m_pViewSwitch->SetPosSizePixel( _rPlayground.TopLeft(), Size( _rPlayground.GetWidth(), _rPlayground.GetHeight() ) );

        ODataView::resizeDocumentView( _rPlayground );
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::GetFocus()
    {
        if(m_pViewSwitch)
            m_pViewSwitch->GetFocus();
    }
    // -----------------------------------------------------------------------------
    IMPL_LINK( OQueryContainerWindow, SplitHdl, void*, p )
    {
        long nTest = m_pSplitter->GetPosPixel().Y();
        m_pSplitter->SetPosPixel( Point( m_pSplitter->GetPosPixel().X(),m_pSplitter->GetSplitPosPixel() ) );
        Resize();

        return 0L;
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::Construct()
    {
        m_pViewSwitch->Construct();
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::initialize(const Reference<XFrame>& _xFrame)
    {
        // append our frame
        Reference < XFramesSupplier > xSup(_xFrame,UNO_QUERY);
        Reference < XFrames > xFrames = xSup->getFrames();
        xFrames->append( m_xBeamer );
    }

    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::disposingPreview()
    {
        // here I know that we will be destroyed from the frame
        m_pBeamer = NULL;
        m_xBeamer = NULL;
        m_pSplitter->Hide();
        Resize();
    }
    // -----------------------------------------------------------------------------
    long OQueryContainerWindow::PreNotify( NotifyEvent& rNEvt )
    {
        BOOL bHandled = FALSE;
        switch (rNEvt.GetType())
        {
            case EVENT_KEYINPUT:
                {
                    const KeyCode& rCode = rNEvt.GetKeyEvent()->GetKeyCode();
                    if (	m_pViewSwitch 
                        &&	!rCode.IsMod1() 
                        &&	!rCode.IsMod2() 
                        &&	rCode.GetCode() == KEY_F6)
                    {
                        ToolBox* pToolBox	= getToolBox();
                        Window*  pLeft		= m_pViewSwitch->getActive();
                        //	if ( !rCode.IsShift() )
                        {
                            if ( m_pBeamer && pLeft && m_pBeamer->HasChildPathFocus() )
                            {
                                pLeft->GrabFocus();
                                bHandled = sal_True;
                            }
                            else if ( m_pBeamer && pToolBox && pToolBox->HasChildPathFocus() )
                            {
                                m_pBeamer->GrabFocus();
                                bHandled = sal_True;
                            }
                            else if ( pLeft && pToolBox && pToolBox->HasChildPathFocus() )
                            {
                                pLeft->GrabFocus();
                                bHandled = sal_True;
                            }
                            else if ( pToolBox )
                            {
                                pToolBox->GrabFocus();
                                bHandled = sal_True;
                            }
                        }
                    }
                }

                break;
            case  EVENT_GETFOCUS:
                if ( m_pViewSwitch )
                {
                    OJoinController* pController = m_pViewSwitch->getDesignView()->getController();
                    pController->InvalidateFeature(SID_CUT);
                    pController->InvalidateFeature(SID_COPY);
                    pController->InvalidateFeature(SID_PASTE);
                }
        }
        return bHandled ? 1L : ODataView::PreNotify(rNEvt);
    }
    // -----------------------------------------------------------------------------
    void OQueryContainerWindow::showPreview(const Reference<XFrame>& _xFrame)
    {
        if(!m_pBeamer)
        {
            m_pBeamer = new OBeamer(this);
            m_xBeamer = Reference<XFrame>(m_pViewSwitch->getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.frame.Frame")),UNO_QUERY);
            OSL_ENSURE(m_xBeamer.is(),"No frame created!");
            m_xBeamer->initialize( VCLUnoHelper::GetInterface ( m_pBeamer ) );
            m_xBeamer->setName(FRAME_NAME_QUERY_PREVIEW);

            // append our frame
            Reference < XFramesSupplier > xSup(_xFrame,UNO_QUERY);
            Reference < XFrames > xFrames = xSup->getFrames();
            xFrames->append( m_xBeamer );

            Size aSize = GetOutputSizePixel();
            Size aBeamer(aSize.Width(),sal_Int32(aSize.Height()*0.33));

            const long	nFrameHeight = LogicToPixel( Size( 0, 3 ), MAP_APPFONT ).Height();
            Point aPos(0,aBeamer.Height()+nFrameHeight);

            m_pBeamer->SetPosSizePixel(Point(0,0),aBeamer);
            m_pBeamer->Show();

            m_pSplitter->SetPosSizePixel( Point(0,aBeamer.Height()), Size(aSize.Width(),nFrameHeight) );
            // a default pos for the splitter, so that the listbox is about 80 (logical) pixels wide
            m_pSplitter->SetSplitPosPixel( aBeamer.Height() );
            m_pViewSwitch->SetPosSizePixel(aPos,Size(aBeamer.Width(),aSize.Height() - aBeamer.Height()-nFrameHeight));

            m_pSplitter->Show();

            if ( !m_pBeamerSeparator )
            {
                m_pBeamerSeparator = new FixedLine( this );
                m_pBeamerSeparator->Show( );
            }

            Resize();
        }	
    }
    // -----------------------------------------------------------------------------


//.........................................................................
}	// namespace dbaui
//.........................................................................

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.4  2002/02/11 12:58:53  oj
 *	#90580# enable F6 key for components
 *	
 *	Revision 1.3  2001/09/20 12:56:16  oj
 *	#92232# fixes for BIGINT type and new property HELPTEXT
 *	
 *	Revision 1.2  2001/09/07 10:05:58  fs
 *	#65293# syntax
 *	
 *	Revision 1.1  2001/08/23 14:39:40  fs
 *	initial checkin - outsourced from QueryTextView.hxx (the container window for the query design)
 *	
 *
 *	Revision 1.0 23.08.01 12:15:26  fs
 ************************************************************************/

