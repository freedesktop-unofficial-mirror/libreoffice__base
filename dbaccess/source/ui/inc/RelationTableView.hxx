/*************************************************************************
 *
 *  $RCSfile: RelationTableView.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: oj $ $Date: 2002-02-08 08:56:33 $
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
#ifndef DBAUI_RELATION_TABLEVIEW_HXX
#define DBAUI_RELATION_TABLEVIEW_HXX
                                 
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif

namespace dbaui
{
    class ORelationDesignView;
    class ORelationTableConnectionData;
    class ORelationTableView : public OJoinTableView
    {
        OTableConnection*				m_pExistingConnection; // is set when a connection was draged on an existing connection
        ORelationTableConnectionData*	m_pCurrentlyTabConnData; // set when we creating a connection with more than one keycolumn
    protected:
        virtual void ConnDoubleClicked( OTableConnection* pConnection );
        virtual void KeyInput( const KeyEvent& rEvt );
        virtual void AddTabWin(const ::rtl::OUString& _rComposedName, const ::rtl::OUString& rWinName, BOOL bNewTable = FALSE);

    public:
        ORelationTableView( Window* pParent, ORelationDesignView* pView );
        virtual ~ORelationTableView();

        //	virtual void AddTabWin(const ::rtl::OUString& _rComposedName, const ::rtl::OUString& rWinName, BOOL bNewTable = FALSE);
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


