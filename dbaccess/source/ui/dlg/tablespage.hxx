/*************************************************************************
 *
 *  $RCSfile: tablespage.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: fs $ $Date: 2001-08-14 14:12:22 $
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

#ifndef _DBAUI_TABLESPAGE_HXX_
#define _DBAUI_TABLESPAGE_HXX_

#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _COM_SUN_STAR_I18N_XCOLLATOR_HPP_
#include <com/sun/star/i18n/XCollator.hpp>
#endif
#ifndef _SV_TOOLBOX_HXX 
#include <vcl/toolbox.hxx>
#endif
#ifndef _DBAUI_CONTAINERMULTIPLEXER_HXX_
#include "containermultiplexer.hxx"
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

    //========================================================================
    //= OTableSubscriptionPage
    //========================================================================
    class ODbAdminDialog;
    class OTableSubscriptionPage
            :public OGenericAdministrationPage
            ,public OContainerListener
    {
        friend class ODbAdminDialog;

    private:
        FixedLine				m_aTables;
        ToolBox					m_aActions;
        OTableTreeListBox		m_aTablesList;
        FixedText				m_aExplanation;
        FixedLine				m_aColumnsLine;
        CheckBox				m_aSuppressVersionColumns;
        sal_Bool				m_bCheckedAll : 1;
        sal_Bool				m_bCatalogAtStart : 1;
        ::rtl::OUString			m_sCatalogSeparator;
        ODbAdminDialog*			m_pAdminDialog;		/** needed for translating an SfxItemSet into Sequence< PropertyValue >
                                                        (for building an XConnection)
                                                    */
        DECLARE_STL_VECTOR( OContainerListenerAdapter*, AdapterArray );
        ::osl::Mutex			m_aNotifierMutex;
        AdapterArray			m_aNotifiers;

        ::rtl::OUString			m_sDSName;

        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >
                                m_xCurrentConnection;	/// valid as long as the page is active
        ::com::sun::star::uno::Reference< ::com::sun::star::i18n::XCollator >
                                m_xCollator;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
                                m_xORB;

    public:
        static	SfxTabPage*	Create( Window* _pParent, const SfxItemSet& _rAttrSet);
        virtual	BOOL		FillItemSet(SfxItemSet& _rCoreAttrs);
        virtual void		ActivatePage(const SfxItemSet& _rSet);
        virtual int			DeactivatePage(SfxItemSet* _pSet);

        void setServiceFactory(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > _rxORB)
            { m_aTablesList.setServiceFactory(m_xORB = _rxORB); }

        virtual OPageSettings*	createViewSettings();
        virtual void			fillViewSettings(OPageSettings* _pSettings);
        virtual void			restoreViewSettings(const OPageSettings* _pSettings);

    protected:
        void SetAdminDialog(ODbAdminDialog* _pDialog) { m_pAdminDialog = _pDialog; }

        DECL_LINK( OnTreeEntryCompare, const SvSortData* );
        DECL_LINK( OnToolboxClicked, void* );
        DECL_LINK( OnTreeEntrySelected, void* );
        DECL_LINK( OnTreeEntryChecked, Control* );

    private:
        OTableSubscriptionPage( Window* pParent, const SfxItemSet& _rCoreAttrs );
        ~OTableSubscriptionPage();

        /** get the composed name of the entry given
            @param _pEntry
                the entry which's name is to be retrieved. Must be a leaf entry.
        */
        ::rtl::OUString getComposedEntryName(SvLBoxEntry* _pEntry);

        /**	check the tables in <member>m_aTablesList</member> according to <arg>_rTables</arg>
        */
        void implCheckTables(const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rTables);

        /// returns the next sibling, if not available, the next sibling of the parent, a.s.o.
        SvLBoxEntry* implNextSibling(SvLBoxEntry* _pEntry) const;

        /// updates the states of the toolbox buttons
        void implUpdateToolbox();

        /** return the current selection in <member>m_aTablesList</member>
        */
        ::com::sun::star::uno::Sequence< ::rtl::OUString > collectDetailedSelection() const;

        // helper for remembering view settings
        struct OTablePageViewSettings : public OToolboxedPageViewSettings
        {
            StringArray		aExpandedEntries;
            StringArray		aSelectedEntries;
            ::rtl::OUString	sFocusEntry;
        };

        /// retrieve the current view settings
        void	getViewSettings(OTablePageViewSettings& _rFillIt);
        /// initialize the page from the given view settings
        void	restoreViewSettings(const OTablePageViewSettings& _rInitializeFrom);

        typedef sal_Bool (SvListView::*EntryPredicateCheck) (SvListEntry*) const;
        /// collects the names of the entries which for which the given predicate is <TRUE/>
        void	collectEntryPaths(StringArray& _rFillInPaths, EntryPredicateCheck _pPredicateCheck);

        typedef void (OTableSubscriptionPage::*EntryAction) (SvLBoxEntry*);
        /// execute the given action on a list of entries described by paths
        void	actOnEntryPaths(const StringArray& _rFillInPaths, EntryAction _pAction);

        /// get the entry described by the given path
        SvLBoxEntry*	getEntryFromPath(const ::rtl::OUString& _rPath);

        /// helper for actOnEntryPaths
        void	doExpand(SvLBoxEntry*);
        /// helper for actOnEntryPaths
        void	doSelect(SvLBoxEntry*);

        /// executes a toolbox slot
        void doToolboxAction(sal_uInt16 _nId);

        /// deletes all selected tables
        void dropSelection();

        /// (un)check all entries
        void CheckAll( BOOL bCheck = sal_True );

        virtual void implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);

        void retireNotifiers();

        // checks the tables according to the filter given
        // in oppsofite to implCheckTables, this method handles the case of an empty sequence, too ...
        void implCompleteTablesCheck( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rTableFilter );

        // OContainerListener
        virtual void _elementInserted( const ::com::sun::star::container::ContainerEvent& _rEvent ) throw(::com::sun::star::uno::RuntimeException);
        virtual void _elementRemoved( const ::com::sun::star::container::ContainerEvent& _Event ) throw(::com::sun::star::uno::RuntimeException);
        virtual void _elementReplaced( const ::com::sun::star::container::ContainerEvent& _rEvent ) throw(::com::sun::star::uno::RuntimeException);
        virtual void _disposing(const ::com::sun::star::lang::EventObject& _rSource) throw( ::com::sun::star::uno::RuntimeException);
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_TABLESPAGE_HXX_

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.2  2001/08/14 12:10:12  fs
 *	preparations for #86945# (be a container listener ...)
 *	
 *	Revision 1.1  2001/05/29 09:59:46  fs
 *	initial checkin - outsourced the class from commonpages
 *	
 *
 *	Revision 1.0 29.05.01 11:08:49  fs
 ************************************************************************/

