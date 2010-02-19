/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: dbastrings.cxx,v $
 * $Revision: 1.11 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif

namespace dbaccess
{

#include "stringconstants.inc"
    //============================================================
    //= SQLSTATE
    //============================================================
    IMPLEMENT_CONSTASCII_USTRING(SQLSTATE_GENERAL, "01000");

    //============================================================
    //= Properties
    //============================================================
    IMPLEMENT_CONSTASCII_USTRING( PROPERTY_APPLYFORMDESIGNMODE, "ApplyFormDesignMode"   );
    IMPLEMENT_CONSTASCII_USTRING( PROPERTY_IS_FORM,             "IsForm"                );
    IMPLEMENT_CONSTASCII_USTRING( PROPERTY_PERSISTENT_PATH,     "PersistentPath"        );
}
