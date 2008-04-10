/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: TablesSingleDlg.hxx,v $
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

#ifndef _DBAUI_TABLESSINGLEDLG_HXX_
#define _DBAUI_TABLESSINGLEDLG_HXX_

#ifndef _BASEDLGS_HXX
#include <sfx2/basedlgs.hxx>
#endif
#ifndef DBAUI_ITEMSETHELPER_HXX
#include "IItemSetHelper.hxx"
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif

#include <memory>

FORWARD_DECLARE_INTERFACE(beans,XPropertySet)
FORWARD_DECLARE_INTERFACE(sdbc,XConnection)
FORWARD_DECLARE_INTERFACE(lang,XMultiServiceFactory)

//.........................................................................
namespace dbaui
{
//.........................................................................
class ODbDataSourceAdministrationHelper;
    //========================================================================
    //= OTableSubscriptionDialog
    //========================================================================
    class OTableSubscriptionDialog : public SfxSingleTabDialog, public IItemSetHelper
    {
        ::std::auto_ptr<ODbDataSourceAdministrationHelper>	m_pImpl;
        sal_Bool m_bStopExecution; // set when the dialog should not be executed

        DECL_LINK( OKClickHdl, OKButton* );
        SfxItemSet*				m_pOutSet;
    public:

        OTableSubscriptionDialog(Window* pParent
            ,SfxItemSet* _pItems
            ,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB
            ,const ::com::sun::star::uno::Any& _aDataSourceName
        );
        virtual ~OTableSubscriptionDialog();

        // forwards from ODbDataSourceAdministrationHelper
        void		successfullyConnected();
        sal_Bool	getCurrentSettings(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rDriverParams);
        void		clearPassword();
        String		getConnectionURL() const;
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >	getCurrentDataSource();
        inline void endExecution() { m_bStopExecution = sal_True; }

        virtual const SfxItemSet* getOutputSet() const;
        virtual SfxItemSet* getWriteOutputSet();

        virtual short	Execute();
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_TABLESSINGLEDLG_HXX_

