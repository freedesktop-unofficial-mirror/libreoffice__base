/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: WCPage.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: hr $ $Date: 2007-09-26 14:50:29 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/
#ifndef DBAUI_WIZARD_CPAGE_HXX
#define DBAUI_WIZARD_CPAGE_HXX

#ifndef DBAUI_WIZ_TABBPAGE_HXX
#include "WTabPage.hxx"
#endif
#ifndef DBAUI_WIZ_COPYTABLEDIALOG_HXX
#include "WCopyTable.hxx"
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_GROUP_HXX
#include <vcl/group.hxx>
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_EDIT_HXX
#include <vcl/edit.hxx>
#endif
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif

namespace dbaui
{
    class OWizColumnSelect;
    class OWizNormalExtend;
    //========================================================================
    class OCopyTable : public OWizardPage
    {
    protected:
        FixedText								m_ftTableName;
        Edit									m_edTableName;
        FixedLine                               m_aFL_Options;
        RadioButton								m_aRB_DefData;
        RadioButton								m_aRB_Def;
        RadioButton								m_aRB_View;
        RadioButton								m_aRB_AppendData;
        CheckBox								m_aCB_PrimaryColumn;
        FixedText								m_aFT_KeyName;
        Edit									m_edKeyName;
        OCopyTableWizard::Wizard_Create_Style	m_eOldStyle;

        OWizColumnSelect*						m_pPage2;
        OWizNormalExtend*						m_pPage3;

        BOOL									m_bIsViewAllowed;
        BOOL									m_bPKeyAllowed;


        DECL_LINK( AppendDataClickHdl, Button* );
        DECL_LINK( RadioChangeHdl, Button* );
        DECL_LINK( KeyClickHdl, Button* );

        sal_Bool checkAppendData();
        //--------dyf add
        void SetAppendDataRadio();
        //--------add end

    public:
        virtual	void			Reset();
        virtual void			ActivatePage();
        virtual BOOL			LeavePage();
        virtual String			GetTitle() const ;

        OCopyTable( Window * pParent, EImportMode atWhat, BOOL bIsView );//, OCopyTableWizard::Wizard_Create_Style nLastAction );
        virtual ~OCopyTable();

        inline BOOL IsOptionDefData()		const { return m_aRB_DefData.IsChecked(); }
        inline BOOL IsOptionDef()			const { return m_aRB_Def.IsChecked(); }
        inline BOOL IsOptionAppendData()	const { return m_aRB_AppendData.IsChecked(); }
        inline BOOL IsOptionView()			const { return m_aRB_View.IsChecked(); }
        String      GetKeyName()            const { return m_edKeyName.GetText(); }

        //--------dyf add 2007/7/10
        void setCreateStyleAction();//const OCopyTableWizard::Wizard_Create_Style& _eStyle
        //--------add end
    };
}
#endif // DBAUI_WIZARD_CPAGE_HXX


