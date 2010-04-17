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
#ifndef DBAUI_QUERYADDTABCONNUNDOACTION_HXX
#define DBAUI_QUERYADDTABCONNUNDOACTION_HXX

#ifndef DBAUI_QUERYTABCONNUNDOACTION_HXX
#include "QueryTabConnUndoAction.hxx"
#endif

namespace dbaui
{
    // ================================================================================================
    // OQueryAddTabConnUndoAction - Undo-Klasse fuer Einfuegen einer Connection

    class OQueryTableView;
    class OQueryAddTabConnUndoAction : public OQueryTabConnUndoAction
    {
    public:
        OQueryAddTabConnUndoAction(OQueryTableView* pOwner);

        virtual void Undo();
        virtual void Redo();
    };

    // ================================================================================================
    // OQueryDelTabConnUndoAction - Undo-Klasse fuer Einfuegen einer Connection

    class OQueryDelTabConnUndoAction : public OQueryTabConnUndoAction
    {
    public:
        OQueryDelTabConnUndoAction(OQueryTableView* pOwner);

        virtual void Undo();
        virtual void Redo();
    };
}
#endif // DBAUI_QUERYADDTABCONNUNDOACTION_HXX


