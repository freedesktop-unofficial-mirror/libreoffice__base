/*************************************************************************
 *
 *  $RCSfile: adminpages.hxx,v $
 *
 *  $Revision: 1.22 $
 *
 *  last change: $Author: fs $ $Date: 2001-05-29 10:17:26 $
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

#ifndef _DBAUI_ADMINPAGES_HXX_
#define _DBAUI_ADMINPAGES_HXX_

#ifndef _SFXTABDLG_HXX
#include <sfx2/tabdlg.hxx>
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
#ifndef _SV_BUTTON_HXX
#include <vcl/imagebtn.hxx>
#endif
#ifndef _SV_GROUP_HXX
#include <vcl/group.hxx>
#endif
#ifndef _SV_COMBOBOX_HXX
#include <vcl/combobox.hxx>
#endif
#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef _DBAUI_CHARSETS_HXX_
#include "charsets.hxx"
#endif
#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif
#ifndef _DBAUI_TABLETREE_HXX_
#include "tabletree.hxx"
#endif
#ifndef _DBAUI_COMMON_TYPES_HXX_
#include "commontypes.hxx"
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

    //=========================================================================
    //= OPageSettings
    //=========================================================================
    struct OPageSettings
    {
        virtual ~OPageSettings();
    };

    //=========================================================================
    //= OToolboxedPageViewSettings
    //=========================================================================
    struct OToolboxedPageViewSettings : public OPageSettings
    {
        sal_uInt16		nDelayedToolboxAction;

        OToolboxedPageViewSettings() : nDelayedToolboxAction(0) { }
    };

    //=========================================================================
    //= OGenericAdministrationPage
    //=========================================================================
    class ODbAdminDialog;
    class OGenericAdministrationPage : public SfxTabPage
    {
    protected:
        Link		m_aModifiedHandler;		/// to be called if something on the page has been modified

    public:
        OGenericAdministrationPage(Window* _pParent, const ResId& _rId, const SfxItemSet& _rAttrSet);

        /// set a handler which gets called every time something on the page has been modified
        void			SetModifiedHandler(const Link& _rHandler) { m_aModifiedHandler = _rHandler; }

        /** create an instance of view settings for the page
            <p>The caller is responsible for destroying the object later on.</p>
            <p>The page may return <NULL/> if it does not support view settings.</p>
        */
        virtual OPageSettings*	createViewSettings();

        /** get the pages current view settings, if any
        */
        virtual void			fillViewSettings(OPageSettings* _pSettings);

        /** called by the dialog after changes have been applied asnychronously
            <p>The page can use this method to restore it's (non-persistent, e.g. view-) settings to the
            state before the changes have been applied</p>
            <p>This method is necessary because during applying, the page may die and be re-created.</p>

            @param _pPageState
                the page state as given in <method>ODbAdminDialog::applyChangesAsync</method>
            @see ODbAdminDialog::applyChangesAsync
        */
        virtual void			restoreViewSettings(const OPageSettings* _pSettings);

    protected:
        /// default implementation: call FillItemSet, call checkItems,
        virtual int DeactivatePage(SfxItemSet* pSet);
        /// default implementation: call implInitControls with the given item set and _bSaveValue = sal_False
        virtual	void Reset(const SfxItemSet& _rCoreAttrs);
        /// default implementation: call implInitControls with the given item set and _bSaveValue = sal_True
        virtual void ActivatePage(const SfxItemSet& _rSet);

    protected:
        void callModifiedHdl() const { if (m_aModifiedHandler.IsSet()) m_aModifiedHandler.Call((void*)this); }

        /// called from within DeactivatePage. The page is allowed to be deactivated if this method returns sal_True
        virtual sal_Bool checkItems() { return sal_True; }

        /** called from within Reset and ActivatePage, use to initialize the controls with the items from the given set
            @param		_bSaveValue		if set to sal_True, the implementation should call SaveValue on all relevant controls
        */
        virtual void implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue) { }

        /// analyze the invalid and the readonly flag which may be present in the set
        void getFlags(const SfxItemSet& _rSet, sal_Bool& _rValid, sal_Bool& _rReadonly);

        /** prepares an action which requires a connection to work with.

            <p>It is checked if the current data source is modified. If in this case the dialog is appliable, and
            the user confirms the apply, an asyncApplyChanges (on the dialog) with the page settings given is executed.

            <p>If no async apply is necessary, the settings given (if not <NULL/> are deleted.</p>
            @return
                <TRUE/> if the action can be continued, <FALSE/> otherwise
        */
        sal_Bool prepareConnectionAction( ODbAdminDialog* _pDialog, const String& _rActionDescription, OPageSettings** _pViewSettings = NULL );

    protected:
        /** This link be used for controls where the tabpage does not need to take any special action when the control
            is modified. The implementation just calls callModifiedHdl.
        */
        DECL_LINK(OnControlModified, Control*);

        /// may be used in SetXXXHdl calls to controls, is a link to <method>OnControlModified</method>
        Link getControlModifiedLink() { return LINK(this, OGenericAdministrationPage, OnControlModified); }
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_ADMINPAGES_HXX_

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.21  2001/05/23 13:47:00  fs
 *	#86444# +prepareConnectionAction
 *	
 *	Revision 1.20  2001/05/10 13:34:29  fs
 *	#86223# +OPageSettings/createViewSettings/filleViewSettings/restoreViewSettings
 *	
 *	Revision 1.19  2001/01/26 16:12:12  fs
 *	split up the file
 *	
 *	Revision 1.18  2001/01/26 06:59:12  fs
 *	some basics for the query administration page - not enabled yet
 *	
 *	Revision 1.17  2001/01/04 11:21:45  fs
 *	#81485# +OAdoDetailsPage
 *	
 *	Revision 1.16  2000/12/07 14:15:42  oj
 *	#81131# check installed adabas dbs
 *	
 *	Revision 1.0 26.09.00 11:46:15  fs
 ************************************************************************/

