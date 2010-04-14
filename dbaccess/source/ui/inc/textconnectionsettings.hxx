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

#ifndef TEXTCONNECTIONSETTINGS_HXX
#define TEXTCONNECTIONSETTINGS_HXX

#include "propertystorage.hxx"

/** === begin UNO includes === **/
/** === end UNO includes === **/

#include <vcl/dialog.hxx>
#include <vcl/button.hxx>

#include <memory>

class SfxItemSet;
//........................................................................
namespace dbaui
{
//........................................................................

    class OTextConnectionHelper;

    //====================================================================
    //= TextConnectionSettingsDialog
    //====================================================================
    class TextConnectionSettingsDialog : public ModalDialog
    {
    public:
        TextConnectionSettingsDialog( Window* _pParent, SfxItemSet& _rItems );
        ~TextConnectionSettingsDialog();

        /** initializes a set of PropertyStorage instaces, which are bound to
            the text-connection relevant items in our item sets
        */
        static void bindItemStorages( SfxItemSet& _rSet, PropertyValues& _rValues );

        virtual short	Execute();

    private:
        ::std::auto_ptr< OTextConnectionHelper >    m_pTextConnectionHelper;
        OKButton                                    m_aOK;
        CancelButton                                m_aCancel;
        SfxItemSet&                                 m_rItems;

    private:
        DECL_LINK( OnOK, PushButton* );
    };

//........................................................................
} // namespace dbaui
//........................................................................

#endif // TEXTCONNECTIONSETTINGS_HXX
