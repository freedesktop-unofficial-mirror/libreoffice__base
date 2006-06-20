/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: uiservices.cxx,v $
 *
 *  $Revision: 1.20 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 03:24:41 $
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

#ifndef _CPPUHELPER_FACTORY_HXX_
#include <cppuhelper/factory.hxx>
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif

/********************************************************************************************/

using namespace ::rtl;
using namespace ::dbaui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

//***************************************************************************************
//
// registry functions
extern "C" void SAL_CALL createRegistryInfo_OTableFilterDialog();
extern "C" void SAL_CALL createRegistryInfo_ODataSourcePropertyDialog();
extern "C" void SAL_CALL createRegistryInfo_OSQLMessageDialog();
extern "C" void SAL_CALL createRegistryInfo_OBrowser();
extern "C" void SAL_CALL createRegistryInfo_OFormGridView();
extern "C" void SAL_CALL createRegistryInfo_DBContentLoader();
extern "C" void SAL_CALL writeDBLoaderInfo(void* pRegistryKey);
extern "C" void SAL_CALL createRegistryInfo_OInteractionHandler();
extern "C" void SAL_CALL createRegistryInfo_SbaXGridControl();
extern "C" void SAL_CALL createRegistryInfo_OQueryControl();
extern "C" void SAL_CALL createRegistryInfo_OTableControl();
extern "C" void SAL_CALL createRegistryInfo_ORelationControl();
extern "C" void SAL_CALL createRegistryInfo_ComposerDialogs();
extern "C" void SAL_CALL createRegistryInfo_ODBApplication();
extern "C" void SAL_CALL createRegistryInfo_ODirectSQLDialog();
extern "C" void SAL_CALL createRegistryInfo_OAdvancedSettingsDialog();
extern "C" void SAL_CALL createRegistryInfo_ODBTypeWizDialog();
extern "C" void SAL_CALL createRegistryInfo_OUserSettingsDialog();
extern "C" void SAL_CALL createRegistryInfo_ODBTypeWizDialogSetup();
extern "C" void SAL_CALL createRegistryInfo_OCallDBTypeWizDialogSetup();
extern "C" void SAL_CALL createRegistryInfo_OAdabasSettingsDialog();
extern "C" void SAL_CALL createRegistryInfo_OColumnControlModel();
extern "C" void SAL_CALL createRegistryInfo_OColumnControl();
extern "C" void SAL_CALL createRegistryInfo_OToolboxController();
extern "C" void SAL_CALL createRegistryInfo_OStatusbarController();

//***************************************************************************************
extern "C" void SAL_CALL createRegistryInfo_DBU()
{
    static sal_Bool bInit = sal_False;
    if (!bInit)
    {
        createRegistryInfo_OTableFilterDialog();
        createRegistryInfo_ODataSourcePropertyDialog();
        createRegistryInfo_OSQLMessageDialog();
        createRegistryInfo_OBrowser();
        createRegistryInfo_OFormGridView();
        createRegistryInfo_DBContentLoader();
        createRegistryInfo_OInteractionHandler();
        createRegistryInfo_SbaXGridControl();
        createRegistryInfo_OQueryControl();
        createRegistryInfo_OTableControl();
        createRegistryInfo_ORelationControl();
        createRegistryInfo_ComposerDialogs();
        createRegistryInfo_ODBApplication();
        createRegistryInfo_ODirectSQLDialog();
        createRegistryInfo_OAdvancedSettingsDialog();
        createRegistryInfo_ODBTypeWizDialog();
        createRegistryInfo_ODBTypeWizDialogSetup();
        createRegistryInfo_OCallDBTypeWizDialogSetup();
            createRegistryInfo_OUserSettingsDialog();
        createRegistryInfo_OAdabasSettingsDialog();
        createRegistryInfo_OColumnControlModel();
        createRegistryInfo_OColumnControl();
        createRegistryInfo_OToolboxController();
        createRegistryInfo_OStatusbarController();
        bInit = sal_True;
    }
}

//---------------------------------------------------------------------------------------

extern "C" void SAL_CALL component_getImplementationEnvironment(
                const sal_Char	**ppEnvTypeName,
                uno_Environment	**/*ppEnv*/
            )
{
    createRegistryInfo_DBU();
    *ppEnvTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

//---------------------------------------------------------------------------------------
extern "C" sal_Bool SAL_CALL component_writeInfo(
                void* pServiceManager,
                void* pRegistryKey
            )
{
    if (pRegistryKey)
    try
    {
        writeDBLoaderInfo(pRegistryKey);
        return ::dbaui::OModuleRegistration::writeComponentInfos(
            static_cast<XMultiServiceFactory*>(pServiceManager),
            static_cast<XRegistryKey*>(pRegistryKey));
    }
    catch (InvalidRegistryException& )
    {
        OSL_ENSURE(sal_False, "DBA::component_writeInfo : could not create a registry key ! ## InvalidRegistryException !");
    }

    return sal_False;
}

//---------------------------------------------------------------------------------------
extern "C" void* SAL_CALL component_getFactory(
                    const sal_Char* pImplementationName,
                    void* pServiceManager,
                    void* /*pRegistryKey*/)
{
    Reference< XInterface > xRet;
    if (pServiceManager && pImplementationName)
    {
        xRet = ::dbaui::OModuleRegistration::getComponentFactory(
            ::rtl::OUString::createFromAscii(pImplementationName),
            static_cast< XMultiServiceFactory* >(pServiceManager));
    }

    if (xRet.is())
        xRet->acquire();
    return xRet.get();
};
