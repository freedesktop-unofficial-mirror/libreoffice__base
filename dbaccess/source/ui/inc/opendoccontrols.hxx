/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: opendoccontrols.hxx,v $
 * $Revision: 1.4 $
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

#ifndef DBACCESS_SOURCE_UI_INC_OPENDOCCONTROLS_HXX
#define DBACCESS_SOURCE_UI_INC_OPENDOCCONTROLS_HXX

#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#include <map>

//........................................................................
namespace dbaui
{
//........................................................................

    //====================================================================
    //= OpenDocumentButton
    //====================================================================
    /** a button which can be used to open a document

        The text of the button is the same as for the "Open" command in the application
        UI. Additionally, the icon for this command is also displayed on the button.
    */
    class OpenDocumentButton : public PushButton
    {
    private:
        ::rtl::OUString     m_sModule;

    public:
        OpenDocumentButton( Window* _pParent, const sal_Char* _pAsciiModuleName, const ResId& _rResId );

    protected:
        void    impl_init( const sal_Char* _pAsciiModuleName );
    };

    //====================================================================
    //= OpenDocumentListBox
    //====================================================================
    class OpenDocumentListBox : public ListBox
    {
    private:
        typedef ::std::pair< String, String >       StringPair;
        typedef ::std::map< USHORT, StringPair >    MapIndexToStringPair;

        ::rtl::OUString         m_sModule;
        MapIndexToStringPair    m_aURLs;

    public:
        OpenDocumentListBox( Window* _pParent, const sal_Char* _pAsciiModuleName, const ResId& _rResId );

        String  GetSelectedDocumentURL() const;
        String  GetSelectedDocumentFilter() const;

    protected:
        virtual void        RequestHelp( const HelpEvent& _rHEvt );

        StringPair  impl_getDocumentAtIndex( USHORT _nListIndex, bool _bSystemNotation = false ) const;

    private:
        void    impl_init( const sal_Char* _pAsciiModuleName );
    };

//........................................................................
} // namespace dbaui
//........................................................................

#endif // DBACCESS_SOURCE_UI_INC_OPENDOCCONTROLS_HXX

