/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ModuleHelper.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _RPTUI_MODULE_HELPER_RPT_HXX_
#define _RPTUI_MODULE_HELPER_RPT_HXX_

#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <tools/resmgr.hxx>
#include "dllapi.h"
//.........................................................................
namespace rptui
{
//.........................................................................
    //=========================================================================
    //= OModule
    //=========================================================================
    class OModuleImpl;
    class REPORTDESIGN_DLLPUBLIC OModule
    {
        friend class OModuleClient;

    private:
        OModule();
            // not implemented. OModule is a static class

    protected:
        static ::osl::Mutex	s_aMutex;		/// access safety
        static sal_Int32	s_nClients;		/// number of registered clients
        static OModuleImpl*	s_pImpl;		/// impl class. lives as long as at least one client for the module is registered

    public:
        /// get the vcl res manager of the module
        static ResMgr*	getResManager();
    protected:
        /// register a client for the module
        static void	registerClient();
        /// revoke a client for the module
        static void	revokeClient();

    private:
        /** ensure that the impl class exists
            @precond m_aMutex is guarded when this method gets called
        */
        static void ensureImpl();
    };

    //=========================================================================
    //= OModuleClient
    //=========================================================================
    /** base class for objects which uses any global module-specific ressources 
    */
    class REPORTDESIGN_DLLPUBLIC OModuleClient
    {
    public:
        OModuleClient()		{ OModule::registerClient(); }
        ~OModuleClient()	{ OModule::revokeClient(); }
    };

    //=========================================================================
    //= ModuleRes
    //=========================================================================
    /** specialized ResId, using the ressource manager provided by the global module
    */
    class REPORTDESIGN_DLLPUBLIC ModuleRes : public ::ResId
    {
    public:
        ModuleRes(USHORT _nId) : ResId(_nId, *OModule::getResManager()) { }
    };
//.........................................................................
}	// namespace rptui
//.........................................................................

#endif // _RPTUI_MODULE_HELPER_RPT_HXX_


