/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbwiz.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2008-03-06 18:25:41 $
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

#ifndef DBAUI_DBWIZ_HXX
#define DBAUI_DBWIZ_HXX

#ifndef _SFXTABDLG_HXX
#include <sfx2/tabdlg.hxx>
#endif
#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef DBAUI_ITEMSETHELPER_HXX
#include "IItemSetHelper.hxx"
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _SVTOOLS_WIZARDMACHINE_HXX_
#include <svtools/wizardmachine.hxx>
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#include <memory>

FORWARD_DECLARE_INTERFACE(beans,XPropertySet)
FORWARD_DECLARE_INTERFACE(sdbc,XConnection)
FORWARD_DECLARE_INTERFACE(lang,XMultiServiceFactory)

//.........................................................................
namespace dbaui
{
//.........................................................................

class ODsnTypeCollection;

//=========================================================================
//= ODbTypeWizDialog
//=========================================================================
class OGeneralPage;
class ODbDataSourceAdministrationHelper;
/** tab dialog for administrating the office wide registered data sources
*/
class ODbTypeWizDialog : public svt::OWizardMachine , public IItemSetHelper, public IDatabaseSettingsDialog,public dbaui::OModuleClient
{
private:
    OModuleClient m_aModuleClient;
    ::std::auto_ptr<ODbDataSourceAdministrationHelper>	m_pImpl;
    SfxItemSet*				m_pOutSet;
    DATASOURCE_TYPE			m_eType;

    sal_Bool				m_bResetting : 1;	/// sal_True while we're resetting the pages
    sal_Bool				m_bApplied : 1;		/// sal_True if any changes have been applied while the dialog was executing
    sal_Bool				m_bUIEnabled : 1;	/// <TRUE/> if the UI is enabled, false otherwise. Cannot be switched back to <TRUE/>, once it is <FALSE/>

public:
    /** ctor. The itemset given should have been created by <method>createItemSet</method> and should be destroyed
        after the dialog has been destroyed
    */
    ODbTypeWizDialog(Window* pParent
        ,SfxItemSet* _pItems
        ,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB
        ,const ::com::sun::star::uno::Any& _aDataSourceName
        );
    virtual ~ODbTypeWizDialog();

    virtual const SfxItemSet* getOutputSet() const;
    virtual SfxItemSet* getWriteOutputSet();

    // forwards to ODbDataSourceAdministrationHelper
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > getORB() const;
    virtual ::std::pair< ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >,sal_Bool> createConnection();
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDriver >	getDriver();
    virtual DATASOURCE_TYPE		getDatasourceType(const SfxItemSet& _rSet) const;
    virtual void clearPassword();
    virtual sal_Bool saveDatasource();
    virtual void setTitle(const ::rtl::OUString& _sTitle);
    virtual void enableConfirmSettings( bool _bEnable );

protected:
    /// to override to create new pages
    virtual TabPage*	createPage(WizardState _nState);
    virtual WizardState	determineNextState(WizardState _nCurrentState) const;
    virtual	sal_Bool	leaveState(WizardState _nState);
    virtual ::svt::IWizardPage* getWizardPage(TabPage* _pCurrentPage) const;
    virtual sal_Bool onFinish(sal_Int32 _nResult);

protected:
    inline sal_Bool	isUIEnabled() const { return m_bUIEnabled; }
    inline void		disabledUI() { m_bUIEnabled = sal_False; }

    /// select a datasource with a given name, adjust the item set accordingly, and everything like that ..
    void implSelectDatasource(const ::rtl::OUString& _rRegisteredName);
    void resetPages(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxDatasource);

    enum ApplyResult
    {
        AR_LEAVE_MODIFIED,		// somthing was modified and has successfully been committed
        AR_LEAVE_UNCHANGED,		// no changes were made
        AR_KEEP					// don't leave the page (e.g. because an error occured)
    };
    /** apply all changes made
    */
    ApplyResult	implApplyChanges();

private:
    DECL_LINK(OnTypeSelected, OGeneralPage*);
};

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // DBAUI_DBWIZ_HXX

