/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: WNameMatch.hxx,v $
 * $Revision: 1.8 $
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
#ifndef DBAUI_WIZ_NAMEMATCHING_HXX
#define DBAUI_WIZ_NAMEMATCHING_HXX

#ifndef DBAUI_WIZ_TABBPAGE_HXX
#include "WTabPage.hxx"
#endif
#ifndef _DBAUI_MARKTREE_HXX_
#include "marktree.hxx"
#endif
#ifndef DBAUI_DATABASEEXPORT_HXX
#include "DExport.hxx"
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif
#ifndef DBAUI_WIZ_COPYTABLEDIALOG_HXX
#include "WCopyTable.hxx"
#endif

namespace dbaui
{
    // ========================================================
    // columns are at root only no children
    // ========================================================
    class OColumnTreeBox : public OMarkableTreeListBox
    {
        sal_Bool m_bReadOnly;
    protected:
        virtual void InitEntry(SvLBoxEntry* pEntry, const String& rStr, const Image& rImg1, const Image& rImg2, SvLBoxButtonKind eButtonKind);

    public:
        OColumnTreeBox( Window* pParent, const ResId& rResId );

        void FillListBox( const ODatabaseExport::TColumnVector& _rList);
        void SetReadOnly(sal_Bool _bRo=sal_True) { m_bReadOnly = _bRo; }
        virtual sal_Bool Select( SvLBoxEntry* pEntry, sal_Bool bSelect=sal_True );

    private:
        using OMarkableTreeListBox::Select;
    };

    // ========================================================
    // Wizard Page: OWizNameMatching
    // Name matching for data appending
    // ========================================================
    class OWizNameMatching : public OWizardPage
    {
        FixedText			m_FT_TABLE_LEFT;
        FixedText			m_FT_TABLE_RIGHT;
        OColumnTreeBox		m_CTRL_LEFT;	// left side
        OColumnTreeBox		m_CTRL_RIGHT;	// right side
        ImageButton         m_ibColumn_up;
        ImageButton         m_ibColumn_down;
        ImageButton         m_ibColumn_up_right;
        ImageButton         m_ibColumn_down_right;
        PushButton			m_pbAll;
        PushButton			m_pbNone;
        String				m_sSourceText;
        String				m_sDestText;

        sal_Bool			m_bAttrsChanged;

        DECL_LINK( ButtonClickHdl, Button * );
        DECL_LINK( RightButtonClickHdl, Button * );
        DECL_LINK( AllNoneClickHdl, Button * );
        DECL_LINK( TableListClickHdl, SvTreeListBox* );
        DECL_LINK( TableListRightSelectHdl, SvTreeListBox* );

    public:
        virtual	void			Reset ( );
        virtual void			ActivatePage();
        virtual sal_Bool		LeavePage();
        virtual String			GetTitle() const ;

        OWizNameMatching(Window* pParent);
        virtual ~OWizNameMatching();

    };
}
#endif // DBAUI_WIZ_NAMEMATCHING_HXX



