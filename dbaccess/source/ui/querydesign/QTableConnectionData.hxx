/*************************************************************************
 *
 *  $RCSfile: QTableConnectionData.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: oj $ $Date: 2002-02-06 08:15:30 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef DBAUI_QTABLECONNECTIONDATA_HXX
#define DBAUI_QTABLECONNECTIONDATA_HXX

#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef DBAUI_TABLEFIELDDESC_HXX
#include "TableFieldDescription.hxx"
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif
//#ifndef DBAUI_QUERYCONTROLLER_HXX
//#include "querycontroller.hxx"
//#endif

namespace dbaui
{
    class OQueryTableConnectionData : public OTableConnectionData
    {
        sal_Int32		m_nFromEntryIndex;
        sal_Int32		m_nDestEntryIndex;
        EJoinType		m_eJoinType;

        ETableFieldType	m_eFromType;
        ETableFieldType	m_eDestType;

        // meine Basisklasse merkt sich leider nur die Fensternamen (was hier das selbe wie die Aliasnamen ist), ich aber brauche
        // auch Zugriff auf die realen Tabellennamen. Damit ich mir nicht die Fenster dazu merken muss (das waere schmutzig, da die
        // TabConDatas normalerweise vom Dokument verwaltet werden und voellig losgeloest von der Repraesentation der Tabellen als
        // Fenster sein sollten), habe ich zwei ::rtl::OUString-Member
        ::rtl::OUString	m_strSourceTableName;
        ::rtl::OUString	m_strDestTableName;

    protected:
        // fuer das Anlegen und Duplizieren von Lines vom eigenen Typ
        virtual OConnectionLineDataRef CreateLineDataObj();
        virtual OConnectionLineDataRef CreateLineDataObj( const OConnectionLineData& rConnLineData );

        OQueryTableConnectionData& operator=( const OQueryTableConnectionData& rConnData );
    public:
        TYPEINFO();
        OQueryTableConnectionData();
        OQueryTableConnectionData( const OQueryTableConnectionData& rConnData );
        OQueryTableConnectionData( const ::rtl::OUString& strSourceTable, const ::rtl::OUString& strDestTable,
            const ::rtl::OUString& strSourceAlias, const ::rtl::OUString& strDestAlias, const ::rtl::OUString& rConnName=::rtl::OUString());
        virtual ~OQueryTableConnectionData();

        virtual void CopyFrom(const OTableConnectionData& rSource);
        virtual OTableConnectionData* NewInstance() const;

        
        /** Update create a new connection

            @return true if successful
        */
        virtual BOOL Update();

        ::rtl::OUString	GetTableName(EConnectionSide nWhich) const;
        ::rtl::OUString	GetAliasName(EConnectionSide nWhich) const;

        sal_Int32		GetFieldIndex(EConnectionSide nWhich) const { return nWhich==JTCS_TO ? m_nDestEntryIndex : m_nFromEntryIndex; }
        void			SetFieldIndex(EConnectionSide nWhich, sal_Int32 nVal) { if (nWhich==JTCS_TO) m_nDestEntryIndex=nVal; else m_nFromEntryIndex=nVal; }

        ETableFieldType	GetFieldType(EConnectionSide nWhich) const { return nWhich==JTCS_TO ? m_eDestType : m_eFromType; }
        void			SetFieldType(EConnectionSide nWhich, ETableFieldType eType) { if (nWhich==JTCS_TO) m_eDestType=eType; else m_eFromType=eType; }

        void			InitFromDrag(const OTableFieldDescRef& rDragLeft, const OTableFieldDescRef& rDragRight);

        EJoinType		GetJoinType() const { return m_eJoinType; };
        void			SetJoinType(const EJoinType& eJT) { m_eJoinType = eJT; };

    };

}
#endif // DBAUI_QTABLECONNECTIONDATA_HXX
