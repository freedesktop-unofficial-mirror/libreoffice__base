/*************************************************************************
* DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
* 
* Copyright 2009 by Sun Microsystems, Inc.
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
************************************************************************/

#ifndef SUBCOMPONENTS_HXX
#define SUBCOMPONENTS_HXX

#include "dbaccessdllapi.h"

/** === begin UNO includes === **/
#include <com/sun/star/sdb/application/DatabaseObject.hpp>
/** === end UNO includes === **/

#include <rtl/ustring.hxx>

#include <hash_map>
#include <map>

//........................................................................
namespace dbaccess
{
//........................................................................

    namespace DatabaseObject = ::com::sun::star::sdb::application::DatabaseObject;

    // -------------------------------------------------------------------
    enum SubComponentType
    {
        TABLE = DatabaseObject::TABLE,
        QUERY = DatabaseObject::QUERY,
        FORM = DatabaseObject::FORM,
        REPORT = DatabaseObject::REPORT,

        RELATION_DESIGN = 1000,

        UNKNOWN         = 10001
    };

    // -------------------------------------------------------------------
    struct DBACCESS_DLLPRIVATE SubComponentDescriptor
    {
        ::rtl::OUString     sName;
        bool                bForEditing;

        SubComponentDescriptor()
            :sName()
            ,bForEditing( false )
        {
        }

        SubComponentDescriptor( const ::rtl::OUString& i_rName, const bool i_bForEditing )
            :sName( i_rName )
            ,bForEditing( i_bForEditing )
        {
        }
    };

    // -------------------------------------------------------------------
    typedef ::std::hash_map< ::rtl::OUString, SubComponentDescriptor, ::rtl::OUStringHash > MapStringToCompDesc;
    typedef ::std::map< SubComponentType, MapStringToCompDesc > MapCompTypeToCompDescs;


//........................................................................
} // namespace dbaccess
//........................................................................

#endif // SUBCOMPONENTS_HXX
