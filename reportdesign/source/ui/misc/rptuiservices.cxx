/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: rptuiservices.cxx,v $
 * $Revision: 1.5 $
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
#include "precompiled_reportdesign.hxx"
#include <cppuhelper/factory.hxx>
#include <osl/diagnose.h>
#include <cppuhelper/implementationentry.hxx>
#include "ReportController.hxx"
#include "toolboxcontroller.hxx"
#include "DefaultInspection.hxx"
#include "ReportComponentHandler.hxx"
#include "GeometryHandler.hxx"
#include "DataProviderHandler.hxx"

/********************************************************************************************/

using namespace ::rptui;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

//***************************************************************************************
//
// registry functions
namespace
{

cppu::ImplementationEntry entries[] = {
    { &OReportController::create, &OReportController::getImplementationName_Static, &OReportController::getSupportedServiceNames_Static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { &OToolboxController::create, &OToolboxController::getImplementationName_Static, &OToolboxController::getSupportedServiceNames_Static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { &DefaultComponentInspectorModel::create, &DefaultComponentInspectorModel::getImplementationName_Static, &DefaultComponentInspectorModel::getSupportedServiceNames_static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { &ReportComponentHandler::create, &ReportComponentHandler::getImplementationName_Static, &ReportComponentHandler::getSupportedServiceNames_static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { &GeometryHandler::create, &GeometryHandler::getImplementationName_Static, &GeometryHandler::getSupportedServiceNames_static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { &DataProviderHandler::create, &DataProviderHandler::getImplementationName_Static, &DataProviderHandler::getSupportedServiceNames_static,
        &cppu::createSingleComponentFactory, 0, 0 },
    { 0, 0, 0, 0, 0, 0 } 
};
}

extern "C" void * SAL_CALL component_getFactory(
    char const * implName, void * serviceManager, void * registryKey)
{
    return cppu::component_getFactoryHelper(
        implName, serviceManager, registryKey, entries);
}

extern "C" void SAL_CALL component_getImplementationEnvironment(
    char const ** envTypeName, uno_Environment **)
{
    *envTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME;
}

extern "C" sal_Bool SAL_CALL component_writeInfo(
    void * serviceManager, void * registryKey)
{
    return cppu::component_writeInfoHelper(
        serviceManager, registryKey, entries);
}
