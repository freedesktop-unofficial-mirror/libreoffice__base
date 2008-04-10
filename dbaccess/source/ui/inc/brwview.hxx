/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: brwview.hxx,v $
 * $Revision: 1.14 $
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

#ifndef _SBX_BRWVIEW_HXX
#define _SBX_BRWVIEW_HXX

#ifndef _SV_WINDOW_HXX //autogen
#include <vcl/window.hxx>
#endif

#ifndef _TOOLS_RESID_HXX //autogen wg. ResId
#include <tools/resid.hxx>
#endif

#ifndef _COM_SUN_STAR_AWT_POSSIZE_HPP_
#include <com/sun/star/awt/PosSize.hpp>
#endif
#ifndef DBAUI_DATAVIEW_HXX
#include "dataview.hxx"
#endif
#ifndef _UNOTOOLS_EVENTLISTENERADAPTER_HXX_
#include <unotools/eventlisteneradapter.hxx>
#endif


namespace com { namespace sun { namespace star { namespace awt {
    class XControl;
    class XControlContainer;
    class XControlModel;
}}}}

// =========================================================================
class ResMgr;
class Splitter;

namespace dbaui
{
    class DBTreeListModel;
    class DBTreeView;
    class SbaGridControl;

    class UnoDataBrowserView : public ODataView, public ::utl::OEventListenerAdapter
    {
    protected:
        ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl > 				m_xGrid;			// our grid's UNO representation
        ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer > 		m_xMe;				// our own UNO representation
        DBTreeView*				m_pTreeView;
        Splitter*				m_pSplitter;
        mutable SbaGridControl*	m_pVclControl;	// our grid's VCL representation
        Window*					m_pStatus;

        DECL_LINK( SplitHdl, void* );
    // attribute access
    public:
        ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControl > 			getGridControl() const	{ return m_xGrid; }
        SbaGridControl*			getVclControl() const;

    public:
        UnoDataBrowserView(	Window* pParent,
                            IController* _pController,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& );
        virtual ~UnoDataBrowserView();

        /// late construction
        virtual void Construct(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel >& xModel);

        /**	as columns may be hidden there is a difference between a columns model pos and its view pos
            so we you may use these translation function
        */
        sal_uInt16 View2ModelPos(sal_uInt16 nPos) const;
        ///	for the same reason the view column count isn't the same as the model column count

        void setSplitter(Splitter* _pSplitter);
        void setTreeView(DBTreeView* _pTreeView);

        void	showStatus( const String& _rStatus );
        void	hideStatus();

        ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlContainer > 	 getContainer() { return m_xMe; }
        
    protected:
        virtual long PreNotify( NotifyEvent& rNEvt );
        virtual void GetFocus();
        virtual void resizeDocumentView(Rectangle& rRect);
        virtual void _disposing( const ::com::sun::star::lang::EventObject& _rSource );

    private:
        using ODataView::Construct;
    };

    class BrowserViewStatusDisplay
    {
    protected:
        UnoDataBrowserView*		m_pView;

    public:
        BrowserViewStatusDisplay( UnoDataBrowserView* _pView, const String& _rStatus );
        ~BrowserViewStatusDisplay( );
    };
}
#endif // _SBX_BRWVIEW_HXX

