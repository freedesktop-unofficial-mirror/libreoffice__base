/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: DesignView.hxx,v $
 * $Revision: 1.5 $
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
#ifndef RPTUI_DESIGNVIEW_HXX
#define RPTUI_DESIGNVIEW_HXX

#include <dbaccess/dataview.hxx>
#include <com/sun/star/frame/XController.hpp>
#include <com/sun/star/report/XSection.hpp>
#include <com/sun/star/report/XReportComponent.hpp>
#include <vcl/split.hxx>
#include <vcl/scrbar.hxx>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/datatransfer/DataFlavor.hpp>
#include <tools/link.hxx>
#include <tools/gen.hxx> 
#include <vcl/timer.hxx>
#include <svtools/hint.hxx>
#include <svtools/brdcst.hxx>
#include <comphelper/stl_types.hxx>
#include "ReportDefines.hxx"
#include <svtools/colorcfg.hxx>
#include <boost/shared_ptr.hpp>
#include <svx/svdedtv.hxx>
#include <vcl/tabpage.hxx>
#include <vcl/splitwin.hxx>
#include <MarkedSection.hxx>

class KeyEvent;
class MouseEvent;
class Timer;
class Window;

namespace rptui
{
    class OScrollWindowHelper;
    class OReportSection;
    class OUnoObject;
    class OSectionView;
    class OReportController;
    class PropBrw;
    class OAddFieldWindow;
    class OReportModel;
    class ONavigator;
    //==================================================================
    //==================================================================
    class ODesignView : public dbaui::ODataView, public SfxBroadcaster, public IMarkedSection
    {
    private:
        //Splitter							m_aSplitter;
        SplitWindow*                        m_pSplitWin;

        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>		m_xReportComponent;
        OReportController*					m_pReportController;        
        OScrollWindowHelper*                m_pScrollWindow;
        Window*								m_pTaskPane;
        PropBrw*							m_pPropWin;
        OAddFieldWindow*					m_pAddField;
        OSectionView*						m_pCurrentView;
        ONavigator*                         m_pReportExplorer;
        Timer								m_aMarkTimer;
        Point								m_aScrollOffset;
        DlgEdMode							m_eMode;
        USHORT								m_nCurrentPosition;
        USHORT								m_eActObj;
        BOOL								m_bFirstDraw;
        Size								m_aGridSize;
        BOOL								m_bGridVisible;
        BOOL								m_bGridSnap;
        BOOL								m_bInSplitHandler;
        

        DECL_LINK( MarkTimeout, Timer * );
        DECL_LINK( SplitHdl, void* );
        
        void ImplInitSettings();

        ODesignView(ODesignView&);
        void operator =(ODesignView&);
    protected:
        // return the Rectangle where I can paint myself
        virtual void resizeDocumentView(Rectangle& rRect);
        // return the Rectangle where I can paint myself
        virtual void DataChanged( const DataChangedEvent& rDCEvt );

    public:
        ODesignView(Window* pParent, 
                    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&,
                    OReportController* _pController);
        virtual ~ODesignView();

        // window overloads
        virtual void MouseButtonDown( const MouseEvent& rMEvt );
        virtual long PreNotify( NotifyEvent& rNEvt );
        virtual void GetFocus();

        // set the view readonly or not
        virtual void setReadOnly(sal_Bool _bReadOnly);

        virtual void initialize();

        inline OReportController*	getController() const { return m_pReportController; }

        void 			SetMode( DlgEdMode m_eMode );
        void			SetInsertObj( USHORT eObj,const ::rtl::OUString& _sShapeType = ::rtl::OUString());
        USHORT    		GetInsertObj() const;
        rtl::OUString   GetInsertObjString() const;
        DlgEdMode   	GetMode() const { return m_eMode; }

        /** cuts the current selection in this section
        */
        void Cut();

        /** copies the current selection in this section
        */
        void Copy();

        /**	returns if paste is allowed
        *
        * \return <TRUE/> if paste is allowed
        */
        BOOL IsPasteAllowed();

        /** paste a new control in this section
        */
        void Paste();

        /** Deletes the current selection in this section
        *
        */
        void Delete();

        /** align all marked objects in all sections
        */
        void alignMarkedObjects(sal_Int32 _nControlModification, bool _bAlignAtSection, bool bBoundRects = false);

        /** checks if alignment is possible in the current section
        */
        sal_Bool isAlignPossible() const;

        /** All objects will be marked.
        */
        void            SelectAll();

        /// checks if a selection exists
        BOOL			HasSelection();

        void            UpdatePropertyBrowserDelayed(OSectionView* _pView);

        USHORT			getSectionCount() const;

        /** removes the section at the given position.
        *
        * \param _nPosition Zero based.
        */
        void			removeSection(USHORT _nPosition);

        /** adds a new section at position _nPosition.
            If the section is <NULL/> nothing happens.
            If the position is grater than the current elements, the section will be appended.
        */
        void			addSection(const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >& _xSection
                                    ,const ::rtl::OUString& _sColorEntry
                                    ,USHORT _nPosition = USHRT_MAX);

        inline Size		getGridSize() const { return m_aGridSize; }
        inline BOOL		isGridSnap() const { return m_bGridSnap; }
        void            setGridSnap(BOOL bOn);
        void            setDragStripes(BOOL bOn);
        BOOL            isDragStripes() const;
        /** turns the grid on or off
        *
        * \param _bGridVisible
        */
        void			toggleGrid(sal_Bool _bGridVisible);

        void			togglePropertyBrowser(sal_Bool _bToogleOn);

        BOOL			isAddFieldVisible() const;
        void			toggleAddField();

        BOOL			isReportExplorerVisible() const;
        void			toggleReportExplorer();

        /** shows or hides the ruler.
        */
        void			showRuler(sal_Bool _bShow);

        /** unmark all objects on the views without the given one.
        *
        * @param _pSectionView The view where the objects should not be unmarked.
        */
        void			unmarkAllObjects(OSectionView* _pSectionView);

        /** triggers the property browser with the section
            @param	_xReportComponent the report component
        */
        void			showProperties( const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _xReportComponent);
        ::com::sun::star::uno::Any getCurrentlyShownProperty() const;

        /** returns the current section or the detail section if no section was selected previously
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection > getCurrentSection() const;

        /** returns the current control report model or <NULL/>
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::report::XReportComponent > getCurrentControlModel() const;

        // IMarkedSection
        ::boost::shared_ptr<OReportSection> getMarkedSection(NearSectionAccess nsa = CURRENT) const;
        virtual void markSection(const sal_uInt16 _nPos);

        /** fills the positions of all collapsed sections.
        *
        * \param _rCollapsedPositions Out parameter which holds afterwards all positions of the collapsed sections.
        */
        void fillCollapsedSections(::std::vector<sal_uInt16>& _rCollapsedPositions) const;

        /** collpase all sections given by their position
        *
        * \param _aCollpasedSections The position of the sections which should be collapsed.
        */
        void collapseSections(const com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _aCollpasedSections);

        ::rtl::OUString  getCurrentPage() const;
        void             setCurrentPage(const ::rtl::OUString& _sLastActivePage);

        /** calculate the max width of the markers
        *
        * @param _bWithEnd	if <TRUE/> the end marker will be used for calculation as well otherwise not.
        * \return the max width
        */
        sal_Int32	     getMaxMarkerWidth(sal_Bool _bWithEnd) const;

        /** checks if the keycode is known by the child windows
            @param	_rCode	the keycode
            @return <TRUE/> if the keycode is handled otherwise <FALSE/>
        */
        sal_Bool		 handleKeyEvent(const KeyEvent& _rEvent);
        
        /** set the section as marked or not marked
            @param	_pSectionView	the section where to set the marked flag
            @param	_bMark	the marked flag
        */
        void			setMarked(OSectionView* _pSectionView,sal_Bool _bMark);

        void			setMarked(const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection>& _xSection,sal_Bool _bMark);
        void			setMarked(const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::report::XReportComponent> >& _xShape,sal_Bool _bMark);

        /** returns if the view handles the event by itself
        *
        * \param _nId the command id
        * \return  <FALSE/> is the event is not handled by the view otherwise <TRUE/>
        */
        sal_Bool        isHandleEvent(sal_uInt16 _nId) const;

        sal_uInt32      getMarkedObjectCount() const;
    };
//==================================================================
}	//rptui
//==================================================================
#endif // RPTUI_DESIGNVIEW_HXX

