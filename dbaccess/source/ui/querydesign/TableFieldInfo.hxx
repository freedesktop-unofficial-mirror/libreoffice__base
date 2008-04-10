/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: TableFieldInfo.hxx,v $
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
#ifndef DBAUI_TABLEFIELDINFO_HXX
#define DBAUI_TABLEFIELDINFO_HXX

#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

namespace dbaui
{
    class OTableFieldInfo
    {
    private:
        ETableFieldType	m_eFieldType;
        sal_Int32		m_eDataType;

    public:
        OTableFieldInfo();
        ~OTableFieldInfo();

        inline ETableFieldType	GetKeyType() const { return m_eFieldType; }
        inline void				SetKey(ETableFieldType bKey=TAB_NORMAL_FIELD) { m_eFieldType = bKey; }
        inline sal_Int32		GetDataType() const { return m_eDataType; }
        inline void				SetDataType(sal_Int32 eTyp) { m_eDataType = eTyp; }
    };
}
#endif // DBAUI_TABLEFIELDINFO_HXX


