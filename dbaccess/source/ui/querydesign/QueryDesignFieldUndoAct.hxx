/*************************************************************************
 *
 *  $RCSfile: QueryDesignFieldUndoAct.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: oj $ $Date: 2002-08-19 08:01:26 $
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
#ifndef DBAUI_QUERYDESIGNFIELDUNDOACT_HXX
#define DBAUI_QUERYDESIGNFIELDUNDOACT_HXX

#ifndef DBAUI_GENERALUNDO_HXX
#include "GeneralUndo.hxx"
#endif
#ifndef _DBU_QRY_HRC_
#include "dbu_qry.hrc"
#endif
#ifndef DBAUI_QUERYDESIGN_OSELECTIONBROWSEBOX_HXX
#include "SelectionBrowseBox.hxx"
#endif


namespace dbaui
{
    // ================================================================================================
    // OQueryDesignFieldUndoAct - Basisklasse fuer Undos in der Feldauflistung im Abfrageentwurf

    
    class OQueryDesignFieldUndoAct : public OCommentUndoAction
    {
    protected:
        OSelectionBrowseBox*	pOwner;
        USHORT					m_nColumnPostion;

        virtual void	Undo() = 0;
        virtual void	Redo() = 0;

    public:
        OQueryDesignFieldUndoAct(OSelectionBrowseBox* pSelBrwBox, USHORT nCommentID) : OCommentUndoAction(nCommentID), pOwner(pSelBrwBox), m_nColumnPostion(BROWSER_INVALIDID) { }

        inline void SetColumnPosition(USHORT _nColumnPostion) { m_nColumnPostion = _nColumnPostion; }
    };

    // ================================================================================================
    // OTabFieldCellModifiedUndoAct - Undo-Klasse fuer Aendern einer Zelle einer Spaltenbeschreibung

    class OTabFieldCellModifiedUndoAct : public OQueryDesignFieldUndoAct
    {
    protected:
        String		m_strNextCellContents;
        sal_Int32	m_nCellIndex;

    public:
        OTabFieldCellModifiedUndoAct(OSelectionBrowseBox* pSelBrwBox) 
            : OQueryDesignFieldUndoAct(pSelBrwBox, STR_QUERY_UNDO_MODIFY_CELL) 
            ,m_nCellIndex(BROWSER_INVALIDID){ }

        inline void SetCellContents(const String& str)	{ m_strNextCellContents = str; }
        inline void SetCellIndex(sal_Int32 nIndex)		{ m_nCellIndex = nIndex; }

        virtual void Undo();
        virtual void Redo() { Undo(); }
    };

    // ================================================================================================
    // OTabFieldSizedUndoAct - Undo-Klasse fuer Aendern einer Spaltenbreite

    class OTabFieldSizedUndoAct : public OQueryDesignFieldUndoAct
    {
    protected:
        long		m_nNextWidth;

    public:
        OTabFieldSizedUndoAct(OSelectionBrowseBox* pSelBrwBox) : OQueryDesignFieldUndoAct(pSelBrwBox, STR_QUERY_UNDO_SIZE_COLUMN), m_nNextWidth(0) { }

        inline void SetOriginalWidth(long nWidth) { m_nNextWidth = nWidth; }

        virtual void Undo();
        virtual void Redo() { Undo(); }
    };

    // ================================================================================================
    // OTabFieldUndoAct - Basisklasse fuer Undos in der Feldauflistung im Abfrageentwurf, die mit Veraendern einer kompletten Feldbeschreibung zu tun haben

    class OTabFieldUndoAct : public OQueryDesignFieldUndoAct
    {
    protected:
        OTableFieldDescRef		pDescr;		// geloeschte Spaltenbeschreibung

    public:
        OTabFieldUndoAct(OSelectionBrowseBox* pSelBrwBox, USHORT nCommentID) : OQueryDesignFieldUndoAct(pSelBrwBox, nCommentID) { }

        void SetTabFieldDescr(OTableFieldDescRef pDescription) { pDescr = pDescription; }
    };

    // ================================================================================================
    // OTabFieldDelUndoAct - Undo-Klasse fuer Loeschen eines Feldes

    class OTabFieldDelUndoAct : public OTabFieldUndoAct
    {
    protected:
        virtual void Undo() { pOwner->InsertColumn(pDescr, m_nColumnPostion); }
        virtual void Redo() { pOwner->RemoveColumn(pDescr->GetColumnId()); }

    public:
        OTabFieldDelUndoAct(OSelectionBrowseBox* pSelBrwBox) : OTabFieldUndoAct(pSelBrwBox, STR_QUERY_UNDO_TABFIELDDELETE) { }
    };

    // ================================================================================================
    // OTabFieldDelUndoAct - Undo-Klasse fuer Anlegen eines Feldes

    class OTabFieldCreateUndoAct : public OTabFieldUndoAct
    {
    protected:
        virtual void Undo() { pOwner->RemoveColumn(pDescr->GetColumnId());}
        virtual void Redo() { pOwner->InsertColumn(pDescr, m_nColumnPostion);}

    public:
        OTabFieldCreateUndoAct(OSelectionBrowseBox* pSelBrwBox) : OTabFieldUndoAct(pSelBrwBox, STR_QUERY_UNDO_TABFIELDCREATE) { }
    };

    // ================================================================================================
    // OTabFieldMovedUndoAct - Undo-class when a field was moved inside the selection

    class OTabFieldMovedUndoAct : public OTabFieldUndoAct
    {
    protected:
        virtual void Undo();
        virtual void Redo() 
        { 
            Undo();
        }

    public:
        OTabFieldMovedUndoAct(OSelectionBrowseBox* pSelBrwBox) : OTabFieldUndoAct(pSelBrwBox, STR_QUERY_UNDO_TABFIELDMOVED) { }
    };
}
#endif // DBAUI_QUERYDESIGNFIELDUNDOACT_HXX



