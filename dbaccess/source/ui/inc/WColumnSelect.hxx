/*************************************************************************
 *
 *  $RCSfile: WColumnSelect.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: oj $ $Date: 2001-10-18 06:52:55 $
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
#ifndef DBAUI_WIZ_COLUMNSELECT_HXX
#define DBAUI_WIZ_COLUMNSELECT_HXX

#ifndef DBAUI_WIZ_TABBPAGE_HXX
#include "WTabPage.hxx"
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif

namespace dbaui
{
    // ========================================================
    // Wizard Page: OWizColumnSelect
    // ========================================================

    class OWizColumnSelect : public OWizardPage
    {

        FixedLine               m_flColumns;
        MultiListBox			m_lbOrgColumnNames; // left side
        ImageButton             m_ibColumn_RH;
        ImageButton             m_ibColumns_RH;
        ImageButton             m_ibColumn_LH;
        ImageButton             m_ibColumns_LH;
        MultiListBox			m_lbNewColumnNames; // right side
        sal_Bool				m_bAttrsChanged;


        DECL_LINK( ButtonClickHdl, Button * );
        DECL_LINK( ListDoubleClickHdl, MultiListBox * );


        void clearListBox(MultiListBox& _rListBox);
        void fillColumns(		ListBox* pRight,
                                ::std::vector< ::rtl::OUString> &_rRightColumns);

        void createNewColumn(	ListBox* _pListbox,
                                OFieldDescription* _pSrcField,
                                ::std::vector< ::rtl::OUString>& _rRightColumns,
                                const ::rtl::OUString&	_sColumnName,
                                const ::rtl::OUString&	_sExtraChars,
                                sal_Int32				_nMaxNameLen,
                                const ::comphelper::TStringMixEqualFunctor& _aCase,
                                USHORT nPos = LISTBOX_APPEND);

        void moveColumn(		ListBox* _pRight,
                                ListBox* _pLeft,
                                ::std::vector< ::rtl::OUString>& _rRightColumns,
                                const ::rtl::OUString&	_sColumnName,
                                const ::rtl::OUString&	_sExtraChars,
                                sal_Int32				_nMaxNameLen,
                                const ::comphelper::TStringMixEqualFunctor& _aCase);

        void enableButtons();
    public:
        virtual	void			Reset ( );
        virtual void			ActivatePage();
        virtual sal_Bool		LeavePage();
        virtual String			GetTitle() const ;

        OWizColumnSelect(Window* pParent);
        virtual ~OWizColumnSelect();
    };
}
#endif // DBAUI_WIZ_COLUMNSELECT_HXX



