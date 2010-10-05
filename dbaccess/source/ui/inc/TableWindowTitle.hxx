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
#ifndef DBAUI_TABLEWINDOWTITLE_HXX
#define DBAUI_TABLEWINDOWTITLE_HXX

#include <vcl/fixed.hxx>

namespace dbaui
{
    class OTableWindow;
    class OTableWindowTitle : public FixedText
    {
        OTableWindow* m_pTabWin;

    protected:
        virtual void Command(const CommandEvent& rEvt);
        //	virtual void Paint( const Rectangle& rRect );
        virtual void MouseButtonDown( const MouseEvent& rEvt );
        virtual void KeyInput( const KeyEvent& rEvt );
        virtual void DataChanged( const DataChangedEvent& rDCEvt );

    public:
        OTableWindowTitle( OTableWindow* pParent );
        virtual ~OTableWindowTitle();
        virtual void LoseFocus();
        virtual void GetFocus();
        virtual void RequestHelp( const HelpEvent& rHEvt );
        // window override
        virtual void StateChanged( StateChangedType nStateChange );
    };
}
#endif // DBAUI_TABLEWINDOWTITLE_HXX

