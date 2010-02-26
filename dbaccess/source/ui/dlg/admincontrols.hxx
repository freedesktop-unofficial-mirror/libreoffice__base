/*************************************************************************
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

#ifndef DBACCESS_ADMINCONTROLS_HXX
#define DBACCESS_ADMINCONTROLS_HXX

#include "adminpages.hxx"

#include <vcl/edit.hxx>
#include <vcl/field.hxx>
#include <vcl/fixed.hxx>

#include <svtools/dialogcontrolling.hxx>

//........................................................................
namespace dbaui
{
//........................................................................

    //====================================================================
    //= MySQLNativeSettings
    //====================================================================
    class MySQLNativeSettings : public Control
    {
    private:
        FixedText           m_aDatabaseNameLabel;
        Edit                m_aDatabaseName;
        RadioButton         m_aHostPortRadio;
        RadioButton         m_aSocketRadio;
        RadioButton         m_aNamedPipeRadio;
        FixedText           m_aHostNameLabel;
        Edit                m_aHostName;
        FixedText           m_aPortLabel;
        NumericField		m_aPort;
        FixedText			m_aDefaultPort;
        Edit				m_aSocket;
        Edit				m_aNamedPipe;

        ::svt::ControlDependencyManager
                            m_aControlDependencies;

    public:
        MySQLNativeSettings( Window& _rParent, const Link& _rControlModificationLink );
        ~MySQLNativeSettings();

        void fillControls( ::std::vector< ISaveValueWrapper* >& _rControlList );
        void fillWindows( ::std::vector< ISaveValueWrapper* >& _rControlList );

        BOOL FillItemSet( SfxItemSet& _rCoreAttrs );
        void implInitControls( const SfxItemSet& _rSet );

        bool canAdvance() const;
    };

//........................................................................
} // namespace dbaui
//........................................................................

#endif // DBACCESS_ADMINCONTROLS_HXX
