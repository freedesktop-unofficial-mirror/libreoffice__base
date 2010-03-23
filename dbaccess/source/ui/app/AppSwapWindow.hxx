/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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
#ifndef DBAUI_APPSWAPWINDOW_HXX
#define DBAUI_APPSWAPWINDOW_HXX

#ifndef DBACCESS_TABLEDESIGN_ICLIPBOARDTEST_HXX
#include "IClipBoardTest.hxx"
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef DBAUI_APPICONCONTROL_HXX
#include "AppIconControl.hxx"
#endif
#ifndef DBAUI_APPELEMENTTYPE_HXX
#include "AppElementType.hxx"
#endif

namespace dbaui
{
    class OAppBorderWindow;
    //==================================================================
    class OApplicationSwapWindow :  public Window, 
                                    public IClipboardTest
    {
        OApplicationIconControl				m_aIconControl;
        ElementType							m_eLastType;
        OAppBorderWindow&					m_rBorderWin;

        void ImplInitSettings( BOOL bFont, BOOL bForeground, BOOL bBackground );

        DECL_LINK( OnContainerSelectHdl,	SvtIconChoiceCtrl* );
        DECL_LINK( ChangeToLastSelected, void* );
    protected:
        virtual void DataChanged(const DataChangedEvent& rDCEvt);
    public:
        OApplicationSwapWindow( Window* _pParent, OAppBorderWindow& _rBorderWindow );
        virtual ~OApplicationSwapWindow();
        // window overloads
        virtual void Resize();


        inline sal_Bool isCutAllowed()		{ return sal_False; }
        inline sal_Bool isCopyAllowed()		{ return sal_False; }
        inline sal_Bool isPasteAllowed()	{ return sal_False; }
        virtual sal_Bool hasChildPathFocus() { return HasChildPathFocus(); }
        inline void copy()	{ }
        inline void cut()	{ }
        inline void paste()	{ }

        inline ULONG					GetEntryCount() const { return m_aIconControl.GetEntryCount(); }
        inline SvxIconChoiceCtrlEntry*	GetEntry( ULONG nPos ) const { return m_aIconControl.GetEntry(nPos); }
        inline Rectangle				GetBoundingBox( SvxIconChoiceCtrlEntry* pEntry ) const { return m_aIconControl.GetBoundingBox(pEntry); }

        /** automatically creates mnemonics for the icon/texts in our left hand side panel
        */
        void    createIconAutoMnemonics( MnemonicGenerator& _rMnemonics );

        /** called to give the window the chance to intercept key events, while it has not
            the focus

            @return <TRUE/> if and only if the event has been handled, and should not
                not be further processed
        */
        bool    interceptKeyInput( const KeyEvent& _rEvent );

        /// return the element of currently select entry
        ElementType getElementType() const;


        /** clears the selection in the icon choice control and calls the handler
        */
        void clearSelection();

        /** changes the container which should be displayed. The select handler will also be called.
            @param	_eType
                Which container to show.
        */
        void selectContainer(ElementType _eType);

    private:
        bool onContainerSelected( ElementType _eType );
    };
// .............................................................
} // namespace dbaui
// .............................................................
#endif // DBAUI_APPSWAPWINDOW_HXX

