/*************************************************************************
 *
 *  $RCSfile: TableDesignControl.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: oj $ $Date: 2002-09-24 09:18:57 $
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
#ifndef DBAUI_TABLEDESIGNCONTROL_HXX
#define DBAUI_TABLEDESIGNCONTROL_HXX

#ifndef _TABBAR_HXX //autogen
#include <svtools/tabbar.hxx>
#endif
#ifndef _SVTOOLS_EDITBROWSEBOX_HXX_
#include <svtools/editbrowsebox.hxx>
#endif

#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif

#define TABPAGESIZE 70
namespace dbaui
{
    class OTableDesignView;
    class OTypeInfo;
    //==================================================================
    class OTableRowView : public ::svt::EditBrowseBox
    {
        friend class OTableDesignUndoAct;

    protected:
        long	m_nDataPos;				// derzeit benoetigte Zeile
        long	m_nCurrentPos;			// Aktuelle Position der ausgewaehlten Column
    private:
        USHORT	m_nCurUndoActId;
    protected:
        BOOL	m_bCurrentModified;
        BOOL	m_bUpdatable;
        BOOL	m_bClipboardFilled;

    public:
        OTableRowView(Window* pParent);
        virtual ~OTableRowView();

        virtual void				SetData( long nRow, USHORT nColId, const OTypeInfo* _pTypeInfo ) = 0;
        virtual void				SetData( long nRow, USHORT nColId, const ::com::sun::star::uno::Any& _rNewData ) = 0;
        virtual ::com::sun::star::uno::Any			GetData( long nRow, USHORT nColId ) = 0;
        virtual void				SetControlText( long nRow, USHORT nColId, const String& rText ) = 0;
        virtual String				GetControlText( long nRow, USHORT nColId ) = 0;

        virtual OTableDesignView* GetView() const = 0;

        USHORT	GetCurUndoActId(){ return m_nCurUndoActId; }

        virtual void Cut();
        virtual void Copy();
        virtual void Paste();

    protected:
        void Paste( long nRow );

        virtual void CopyRows()								= 0;
        virtual void DeleteRows()							= 0;
        virtual void InsertRows( long nRow )				= 0;
        virtual void InsertNewRows( long nRow )				= 0;

        virtual sal_Bool IsPrimaryKeyAllowed( long nRow )	= 0;
        virtual sal_Bool IsInsertNewAllowed( long nRow )	= 0;
        virtual sal_Bool IsDeleteAllowed( long nRow )		= 0;

        virtual BOOL IsUpdatable() const {return m_bUpdatable;}
        virtual void SetUpdatable( BOOL bUpdate=TRUE );

        virtual RowStatus GetRowStatus(long nRow) const;
        virtual void KeyInput(const KeyEvent& rEvt);
        virtual void Command( const CommandEvent& rEvt );

        virtual void Init();
    };
}
#endif // DBAUI_TABLEDESIGNCONTROL_HXX


