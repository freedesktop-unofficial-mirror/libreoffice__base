/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: sqledit.hxx,v $
 * $Revision: 1.5.60.2 $
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
#ifndef DBAUI_SQLEDIT_HXX
#define DBAUI_SQLEDIT_HXX

#include <svtools/editsyntaxhighlighter.hxx>
#include <svtools/lstner.hxx>
#include <svtools/colorcfg.hxx>
#include <svtools/sourceviewconfig.hxx>

namespace dbaui
{
    class OQueryTextView;
    class OSqlEdit : public MultiLineEditSyntaxHighlight, SfxListener
    {
    private:
        Timer					m_timerInvalidate;
        Timer					m_timerUndoActionCreation;
        Link					m_lnkTextModifyHdl;
        String					m_strOrigText;		// wird beim Undo wiederhergestellt
        OQueryTextView*			m_pView;
        BOOL					m_bAccelAction;		// Wird bei Cut, Copy, Paste gesetzt
        BOOL					m_bStopTimer;
        svt::SourceViewConfig	m_SourceViewConfig;
        svtools::ColorConfig	m_ColorConfig;

        DECL_LINK(OnUndoActionTimer, void*);
        DECL_LINK(OnInvalidateTimer, void*);

    private: 
        void			ImplSetFont();

    protected:
        virtual void KeyInput( const KeyEvent& rKEvt );
        virtual void GetFocus();

        DECL_LINK(ModifyHdl, void*);

    public:
        OSqlEdit( OQueryTextView* pParent,  WinBits nWinStyle = WB_LEFT | WB_VSCROLL |WB_BORDER);
        virtual ~OSqlEdit();

        // Edit overridables
        virtual void SetText(const String& rNewText);
        using MultiLineEditSyntaxHighlight::SetText;

        // own functionality
        BOOL IsInAccelAct();

        void SetTextModifyHdl(const Link& lnk) { m_lnkTextModifyHdl = lnk; }
            // bitte nicht SetModifyHdl benutzen, den brauche ich selber, der hier wird von dem damit gesetzten Handler
            // gerufen
            // der Link bekommt einen Pointer-to-string, der nach dem Link nicht mehr gueltig ist

        void stopTimer();
        void startTimer();

        virtual void	Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
        using MultiLineEditSyntaxHighlight::Notify;
    };
}

#endif // DBAUI_SQLEDIT_HXX


