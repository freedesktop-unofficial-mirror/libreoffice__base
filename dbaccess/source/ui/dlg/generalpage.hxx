/*************************************************************************
 *
 *  $RCSfile: generalpage.hxx,v $
 *
 *  $Revision: 1.15 $
 *
 *  last change: $Author: obo $ $Date: 2005-07-08 10:39:24 $
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

#ifndef _DBAUI_GENERALPAGE_HXX_
#define _DBAUI_GENERALPAGE_HXX_

#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef DBACCESS_SOURCE_UI_INC_OPENDOCCONTROLS_HXX
#include "opendoccontrols.hxx"
#endif
#ifndef _SV_FIXED_HXX
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _SV_EDIT_HXX
#include <vcl/edit.hxx>
#endif
#include <memory>

//.........................................................................
namespace dbaui
{
//.........................................................................
    class IAdminHelper;
    class RadioDependentEnabler;
    //=========================================================================
    //= OGeneralPage
    //=========================================================================
    class OGeneralPage : public OGenericAdministrationPage
    {
        OGeneralPage(Window* pParent, const SfxItemSet& _rItems, sal_Bool _bDBWizardMode = sal_False);
        ~OGeneralPage();

    public:
        enum CreationMode
        {
            eCreateNew,
            eConnectExternal,
            eOpenExisting
        };

        struct DocumentDescriptor
        {
            String  sURL;
            String  sFilter;
        };

    private:
        // dialog controls
        FixedText           m_aFTHeaderText;
        FixedText           m_aFTHelpText;
        FixedText           m_aFT_DatasourceTypeHeader;
        RadioButton         m_aRB_CreateDatabase;
        RadioButton         m_aRB_OpenDocument;
        RadioButton         m_aRB_GetExistingDatabase;
        FixedText           m_aFT_DocListLabel;
        ::std::auto_ptr< OpenDocumentListBox >
                            m_pLB_DocumentList;
        OpenDocumentButton  m_aPB_OpenDocument;
        FixedText			m_aTypePreLabel;
        FixedText			m_aDatasourceTypeLabel;
        ::std::auto_ptr< ListBox >
                            m_pDatasourceType;
        FixedText           m_aFTDataSourceAppendix;
        FixedText			m_aTypePostLabel;
        FixedText			m_aSpecialMessage;
        sal_Bool            m_DBWizardMode;
        String				m_sMySQLEntry;
        CreationMode        m_eOriginalCreationMode;
        DocumentDescriptor  m_aBrowsedDocument;

        ::std::auto_ptr< RadioDependentEnabler >
                            m_pSelectTypeController;
        ::std::auto_ptr< RadioDependentEnabler >
                            m_pOpenDocController;


        ODsnTypeCollection*	m_pCollection;	/// the DSN type collection instance
        DECLARE_STL_MAP(DATASOURCE_TYPE, String, ::std::less< DATASOURCE_TYPE >, SelectionHistory);
        DATASOURCE_TYPE		m_eCurrentSelection;	/// currently selected type
        DATASOURCE_TYPE		m_eNotSupportedKnownType;	/// if a data source of an unsupported, but known type is encountered ....
        SelectionHistory	m_aSelectionHistory;	/// last selected ConnectURLs for all types

        enum SPECIAL_MESSAGE
        {
            smNone,
            smUnsupportedType
        };
        SPECIAL_MESSAGE		m_eLastMessage;

        Link				m_aTypeSelectHandler;	/// to be called if a new type is selected
        Link				m_aCreationModeHandler;	/// to be called if a new type is selected
        Link				m_aDocumentSelectionHandler;    /// to be called when a document in the RecentDoc list is selected
        Link                m_aChooseDocumentHandler;       /// to be called when a recent document has been definately chosen
        sal_Bool			m_bDisplayingInvalid : 1;	// the currently displayed data source is deleted
        sal_Bool			m_bUserGrabFocus : 1;
        String				VerifyDisplayName(DATASOURCE_TYPE eType, String _sDisplayName);
        void				insertDatasourceTypeEntryData(DATASOURCE_TYPE eType, String sDisplayName);

    public:
        static SfxTabPage*	Create(Window* pParent, const SfxItemSet& _rAttrSet, sal_Bool _bDBWizardMode = sal_False);

        /// set a handler which gets called every time the user selects a new type
        void			SetTypeSelectHandler(const Link& _rHandler) { m_aTypeSelectHandler = _rHandler; }
        void			SetCreationModeHandler(const Link& _rHandler) { m_aCreationModeHandler = _rHandler; }
        void			SetDocumentSelectionHandler( const Link& _rHandler) { m_aDocumentSelectionHandler = _rHandler; }
        void			SetChooseDocumentHandler( const Link& _rHandler) { m_aChooseDocumentHandler = _rHandler; }
        CreationMode    GetDatabaseCreationMode() const;

        DocumentDescriptor  GetSelectedDocument() const;

        /// get the currently selected datasource type
        DATASOURCE_TYPE	GetSelectedType() const { return m_eCurrentSelection; }

    protected:
        // SfxTabPage overridables
        virtual	BOOL FillItemSet(SfxItemSet& _rCoreAttrs);
        virtual	void Reset(const SfxItemSet& _rCoreAttrs);

        virtual void implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);

        virtual void GetFocus();

        // <method>OGenericAdministrationPage::fillControls</method>
        virtual void fillControls(::std::vector< ISaveValueWrapper* >& _rControlList);
        // <method>OGenericAdministrationPage::fillWindows</method>
        virtual void fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList);

    protected:

        void onTypeSelected(const DATASOURCE_TYPE _eType);
        void initializeHistory();
        void initializeTypeList();

        void implSetCurrentType( const DATASOURCE_TYPE _eType );

        void switchMessage(sal_Bool _bDeleted,const DATASOURCE_TYPE _eType);

        /// sets the the title of the parent dialog
        void setParentTitle(DATASOURCE_TYPE _eSelectedType);

        DECL_LINK(OnDatasourceTypeSelected, ListBox*);
        DECL_LINK(OnSetupModeSelected, RadioButton*);
        DECL_LINK(OnDocumentSelected, ListBox*);
        DECL_LINK(OnOpenDocument, PushButton*);
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................
#endif // _DBAUI_GENERALPAGE_HXX_
