/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

// no include "precompiled_dbaccess.hxx" because this file is meant to
// be included in other cxx files

#ifndef _REGISTRATIONHELPER_CXX_INCLUDED_INDIRECTLY_
#error "don't build this file directly! use dbu_reghelper.cxx instead!"
#endif

using namespace ::com::sun::star;
using namespace ::comphelper;
using namespace ::cppu;

uno::Sequence< ::rtl::OUString >*				    OModuleRegistration::s_pImplementationNames = NULL;
uno::Sequence< uno::Sequence< ::rtl::OUString > >*	OModuleRegistration::s_pSupportedServices = NULL;
uno::Sequence< sal_Int64 >*		            OModuleRegistration::s_pCreationFunctionPointers = NULL;
uno::Sequence< sal_Int64 >*				    OModuleRegistration::s_pFactoryFunctionPointers = NULL;

//--------------------------------------------------------------------------
void OModuleRegistration::registerComponent(
    const ::rtl::OUString& _rImplementationName,
    const uno::Sequence< ::rtl::OUString >& _rServiceNames,
    ComponentInstantiation _pCreateFunction,
    FactoryInstantiation _pFactoryFunction)
{
    if (!s_pImplementationNames)
    {
        OSL_ENSURE(!s_pSupportedServices && !s_pCreationFunctionPointers && !s_pFactoryFunctionPointers,
            "OModuleRegistration::registerComponent : inconsistent state (the pointers (1)) !");
        s_pImplementationNames = new uno::Sequence< ::rtl::OUString >;
        s_pSupportedServices = new uno::Sequence< uno::Sequence< ::rtl::OUString > >;
        s_pCreationFunctionPointers = new uno::Sequence< sal_Int64 >;
        s_pFactoryFunctionPointers = new uno::Sequence< sal_Int64 >;
    }
    OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
        "OModuleRegistration::registerComponent : inconsistent state (the pointers (2)) !");

    OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
        "OModuleRegistration::registerComponent : inconsistent state !");

    sal_Int32 nOldLen = s_pImplementationNames->getLength();
    s_pImplementationNames->realloc(nOldLen + 1);
    s_pSupportedServices->realloc(nOldLen + 1);
    s_pCreationFunctionPointers->realloc(nOldLen + 1);
    s_pFactoryFunctionPointers->realloc(nOldLen + 1);

    s_pImplementationNames->getArray()[nOldLen] = _rImplementationName;
    s_pSupportedServices->getArray()[nOldLen] = _rServiceNames;
    s_pCreationFunctionPointers->getArray()[nOldLen] = reinterpret_cast<sal_Int64>(_pCreateFunction);
    s_pFactoryFunctionPointers->getArray()[nOldLen] = reinterpret_cast<sal_Int64>(_pFactoryFunction);
}

//--------------------------------------------------------------------------
void OModuleRegistration::revokeComponent(const ::rtl::OUString& _rImplementationName)
{
    if (!s_pImplementationNames)
    {
        OSL_ENSURE(sal_False, "OModuleRegistration::revokeComponent : have no class infos ! Are you sure called this method at the right time ?");
        return;
    }
    OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
        "OModuleRegistration::revokeComponent : inconsistent state (the pointers) !");
    OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
        "OModuleRegistration::revokeComponent : inconsistent state !");

    sal_Int32 nLen = s_pImplementationNames->getLength();
    const ::rtl::OUString* pImplNames = s_pImplementationNames->getConstArray();
    for (sal_Int32 i=0; i<nLen; ++i, ++pImplNames)
    {
        if (pImplNames->equals(_rImplementationName))
        {
            removeElementAt(*s_pImplementationNames, i);
            removeElementAt(*s_pSupportedServices, i);
            removeElementAt(*s_pCreationFunctionPointers, i);
            removeElementAt(*s_pFactoryFunctionPointers, i);
            break;
        }
    }

    if (s_pImplementationNames->getLength() == 0)
    {
        delete s_pImplementationNames; s_pImplementationNames = NULL;
        delete s_pSupportedServices; s_pSupportedServices = NULL;
        delete s_pCreationFunctionPointers; s_pCreationFunctionPointers = NULL;
        delete s_pFactoryFunctionPointers; s_pFactoryFunctionPointers = NULL;
    }
}

//--------------------------------------------------------------------------
uno::Reference< uno::XInterface > OModuleRegistration::getComponentFactory(
    const ::rtl::OUString& _rImplementationName,
    const uno::Reference< lang::XMultiServiceFactory >& _rxServiceManager)
{
    OSL_ENSURE(_rxServiceManager.is(), "OModuleRegistration::getComponentFactory : invalid argument (service manager) !");
    OSL_ENSURE(_rImplementationName.getLength(), "OModuleRegistration::getComponentFactory : invalid argument (implementation name) !");

    if (!s_pImplementationNames)
    {
        OSL_ENSURE(sal_False, "OModuleRegistration::getComponentFactory : have no class infos ! Are you sure called this method at the right time ?");
        return NULL;
    }
    OSL_ENSURE(s_pImplementationNames && s_pSupportedServices && s_pCreationFunctionPointers && s_pFactoryFunctionPointers,
        "OModuleRegistration::getComponentFactory : inconsistent state (the pointers) !");
    OSL_ENSURE(	(s_pImplementationNames->getLength() == s_pSupportedServices->getLength())
                &&	(s_pImplementationNames->getLength() == s_pCreationFunctionPointers->getLength())
                &&	(s_pImplementationNames->getLength() == s_pFactoryFunctionPointers->getLength()),
        "OModuleRegistration::getComponentFactory : inconsistent state !");


    uno::Reference< uno::XInterface > xReturn;


    sal_Int32 nLen = s_pImplementationNames->getLength();
    const ::rtl::OUString* pImplName = s_pImplementationNames->getConstArray();
    const uno::Sequence< ::rtl::OUString >* pServices = s_pSupportedServices->getConstArray();
    const sal_Int64* pComponentFunction = s_pCreationFunctionPointers->getConstArray();
    const sal_Int64* pFactoryFunction = s_pFactoryFunctionPointers->getConstArray();

    for (sal_Int32 i=0; i<nLen; ++i, ++pImplName, ++pServices, ++pComponentFunction, ++pFactoryFunction)
    {
        if (pImplName->equals(_rImplementationName))
        {
            const FactoryInstantiation FactoryInstantiationFunction = reinterpret_cast<const FactoryInstantiation>(*pFactoryFunction);
            const ComponentInstantiation ComponentInstantiationFunction = reinterpret_cast<const ComponentInstantiation>(*pComponentFunction);

            xReturn = FactoryInstantiationFunction( _rxServiceManager, *pImplName, ComponentInstantiationFunction, *pServices, NULL);
            if (xReturn.is())
            {
                xReturn->acquire();
                return xReturn.get();
            }
        }
    }

    return NULL;
}


