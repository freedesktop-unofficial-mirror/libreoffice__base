/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: unoadmin.hxx,v $
 * $Revision: 1.13 $
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

#ifndef _DBAUI_UNOADMIN_
#define _DBAUI_UNOADMIN_

#ifndef _SVT_GENERICUNODIALOG_HXX_
#include <svtools/genericunodialog.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif

class SfxItemSet;
class SfxItemPool;
class SfxPoolItem;

//.........................................................................
namespace dbaui
{
//.........................................................................

class IDatabaseSettingsDialog;

//=========================================================================
//= ODatabaseAdministrationDialog
//=========================================================================
typedef ::svt::OGenericUnoDialog ODatabaseAdministrationDialogBase;
class ODatabaseAdministrationDialog
        :public ODatabaseAdministrationDialogBase
{
    OModuleClient    m_aModuleClient;
protected:
    SfxItemSet*				m_pDatasourceItems;		// item set for the dialog
    SfxItemPool*			m_pItemPool;			// item pool for the item set for the dialog
    SfxPoolItem**			m_pItemPoolDefaults;	// pool defaults
    ODsnTypeCollection*		m_pCollection;			// datasource type collection

    ::com::sun::star::uno::Any			m_aInitialSelection;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > m_xActiveConnection;

protected:
    ODatabaseAdministrationDialog(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB);
    virtual ~ODatabaseAdministrationDialog();
protected:
// OGenericUnoDialog overridables
    virtual void destroyDialog();
    virtual void implInitialize(const com::sun::star::uno::Any& _rValue);
};

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_UNOADMIN_

