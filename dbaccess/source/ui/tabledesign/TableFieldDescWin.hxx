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
#ifndef DBAUI_TABLEFIELDDESCRIPTION_HXX
#define DBAUI_TABLEFIELDDESCRIPTION_HXX

#ifndef _SV_TABPAGE_HXX 
#include <vcl/tabpage.hxx>
#endif
#ifndef DBAUI_TABLEFIELDDESCGENPAGE_HXX
#include "FieldDescGenWin.hxx"
#endif
#ifndef DBACCESS_TABLEDESIGN_ICLIPBOARDTEST_HXX
#include "IClipBoardTest.hxx"
#endif

class FixedText;
namespace dbaui
{
    class OFieldDescGenWin;
    class OTableDesignHelpBar;
    class OFieldDescription;
    //==================================================================
    // Ableitung von TabPage ist ein Trick von TH,
    // um Aenderungen der Systemfarben zu bemerken (Bug #53905)
    class OTableFieldDescWin : public TabPage
                                ,public IClipboardTest
    {
        enum ChildFocusState
        {
            DESCRIPTION,
            HELP,
            NONE
        };
    private:
        OTableDesignHelpBar*	m_pHelpBar;
        OFieldDescGenWin*		m_pGenPage;
        FixedText*				m_pHeader;
        ChildFocusState			m_eChildFocus;

        IClipboardTest* getActiveChild() const;

    protected:
        virtual void Resize();
        virtual void Paint( const Rectangle& rRect );

    public:
        OTableFieldDescWin( Window* pParent);
        virtual ~OTableFieldDescWin();

        virtual void Init();

        void DisplayData( OFieldDescription* pFieldDescr );
        void SaveData( OFieldDescription* pFieldDescr );
        void SetReadOnly( BOOL bReadOnly );

        // window overloads
        virtual long PreNotify( NotifyEvent& rNEvt );
        virtual void GetFocus();
        virtual void LoseFocus();

        void SetControlText( USHORT nControlId, const String& rText )
                { m_pGenPage->SetControlText(nControlId,rText); }
        String GetControlText( USHORT nControlId )
                { return m_pGenPage->GetControlText(nControlId); }

        //	short GetFormatCategory(OFieldDescription* pFieldDescr) { return m_pGenPage ? m_pGenPage->GetFormatCategory(pFieldDescr) : -1; }
            // liefert zum am Feld eingestellten Format einen der CAT_xxx-Werte (CAT_NUMBER, CAT_DATE ...)

        String	BoolStringPersistent(const String& rUIString) const { return m_pGenPage->BoolStringPersistent(rUIString); }
        String	BoolStringUI(const String& rPersistentString) const { return m_pGenPage->BoolStringUI(rPersistentString); }

        // IClipboardTest
        virtual sal_Bool isCutAllowed();
        virtual sal_Bool isCopyAllowed();
        virtual sal_Bool isPasteAllowed();
        virtual sal_Bool hasChildPathFocus() { return HasChildPathFocus(); }

        virtual void copy();
        virtual void cut();
        virtual void paste();

        inline OFieldDescGenWin* getGenPage() const { return m_pGenPage; }
        inline OTableDesignHelpBar*	getHelpBar() const { return m_pHelpBar; }

    };
}
#endif // DBAUI_TABLEFIELDDESCRIPTION_HXX




