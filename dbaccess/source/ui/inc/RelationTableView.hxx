/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: RelationTableView.hxx,v $
 * $Revision: 1.10 $
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
#ifndef DBAUI_RELATION_TABLEVIEW_HXX
#define DBAUI_RELATION_TABLEVIEW_HXX
                                 
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif

namespace dbaui
{
    class ORelationDesignView;
    class ORelationTableView : public OJoinTableView
    {
        OTableConnection*				 m_pExistingConnection; // is set when a connection was draged on an existing connection
        TTableConnectionData::value_type m_pCurrentlyTabConnData; // set when we creating a connection with more than one keycolumn
    protected:
        virtual void ConnDoubleClicked( OTableConnection* pConnection );
        virtual void AddTabWin(const ::rtl::OUString& _rComposedName, const ::rtl::OUString& rWinName, BOOL bNewTable = FALSE);

        virtual OTableWindow* createWindow(const TTableWindowData::value_type& _pData);

        /** determines whether the classes Init method should accept a query name, or only table names
        */
        virtual bool    allowQueries() const;

    public:
        ORelationTableView( Window* pParent, ORelationDesignView* pView );
        virtual ~ORelationTableView();

        virtual void RemoveTabWin( OTableWindow* pTabWin );
        virtual void AddConnection(const OJoinExchangeData& jxdSource, const OJoinExchangeData& jxdDest);
        virtual ::std::vector<OTableConnection*>::const_iterator RemoveConnection(OTableConnection* pConn,sal_Bool _bDelete);

        virtual void ReSync();

        void AddNewRelation();
            // reisst den Dialog fuer eine voellig neue Relation hoch
        // wird vom AddTabDlg benutzt, um festzustellen, ob noch Tabellen hinzugefuegt werden duerfen
        virtual BOOL IsAddAllowed();

        virtual void lookForUiActivities();
    };
}
#endif // DBAUI_RELATION_TABLEVIEW_HXX


