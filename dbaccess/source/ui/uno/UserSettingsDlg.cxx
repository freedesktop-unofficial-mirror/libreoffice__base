/*************************************************************************
 *
 *  $RCSfile: UserSettingsDlg.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-02 16:22:05 $
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

#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _DBAUI_USERSETTINGSDLG_HXX
#include "UserSettingsDlg.hxx"
#endif
#ifndef DBAUI_USERADMINDLG_HXX
#include "UserAdminDlg.hxx"
#endif


using namespace dbaui;

extern "C" void SAL_CALL createRegistryInfo_OUserSettingsDialog()
{
    static OMultiInstanceAutoRegistration< OUserSettingsDialog > aAutoRegistration;
}

//.........................................................................
namespace dbaui
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::beans;

//=========================================================================
//-------------------------------------------------------------------------
OUserSettingsDialog::OUserSettingsDialog(const Reference< XMultiServiceFactory >& _rxORB)
    :ODatabaseAdministrationDialog(_rxORB)
{
}
//-------------------------------------------------------------------------
Sequence<sal_Int8> SAL_CALL OUserSettingsDialog::getImplementationId(  ) throw(RuntimeException)
{
    static ::cppu::OImplementationId aId;
    return aId.getImplementationId();
}

//-------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OUserSettingsDialog::Create(const Reference< XMultiServiceFactory >& _rxFactory)
{
    return *(new OUserSettingsDialog(_rxFactory));
}

//-------------------------------------------------------------------------
::rtl::OUString SAL_CALL OUserSettingsDialog::getImplementationName() throw(RuntimeException)
{
    return getImplementationName_Static();
}

//-------------------------------------------------------------------------
::rtl::OUString OUserSettingsDialog::getImplementationName_Static() throw(RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("org.openoffice.comp.dbu.OUserSettingsDialog"));
}

//-------------------------------------------------------------------------
::comphelper::StringSequence SAL_CALL OUserSettingsDialog::getSupportedServiceNames() throw(RuntimeException)
{
    return getSupportedServiceNames_Static();
}

//-------------------------------------------------------------------------
::comphelper::StringSequence OUserSettingsDialog::getSupportedServiceNames_Static() throw(RuntimeException)
{
    ::comphelper::StringSequence aSupported(1);
    aSupported.getArray()[0] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.UserAdministrationDialog"));
    return aSupported;
}

//-------------------------------------------------------------------------
Reference<XPropertySetInfo>  SAL_CALL OUserSettingsDialog::getPropertySetInfo() throw(RuntimeException)
{
    Reference<XPropertySetInfo>  xInfo( createPropertySetInfo( getInfoHelper() ) );
    return xInfo;
}

//-------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OUserSettingsDialog::getInfoHelper()
{
    return *const_cast<OUserSettingsDialog*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OUserSettingsDialog::createArrayHelper( ) const
{
    Sequence< Property > aProps;
    describeProperties(aProps);
    return new ::cppu::OPropertyArrayHelper(aProps);
}
//------------------------------------------------------------------------------
Dialog*	OUserSettingsDialog::createDialog(Window* _pParent)
{
    OUserAdminDlg* pDlg = new OUserAdminDlg(_pParent, m_pDatasourceItems, m_xORB,m_aInitialSelection);
    return pDlg;
}

//.........................................................................
}	// namespace dbaui
//.........................................................................

