/*************************************************************************
 *
 *  $RCSfile: TEditControl.cxx,v $
 *
 *  $Revision: 1.16 $
 *
 *  last change: $Author: fs $ $Date: 2001-06-29 08:41:14 $
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
#ifndef DBAUI_TABLEEDITORCONTROL_HXX
#include "TEditControl.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XALTERTABLE_HPP_
#include <com/sun/star/sdbcx/XAlterTable.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_
#include <com/sun/star/sdbcx/XDrop.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTYPES_HPP_
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _SV_CLIP_HXX 
#include <vcl/clip.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif
#ifndef DBAUI_TABLEDESCRIPTIONWINDOW_HXX
#include "TableDescWin.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef DBAUI_FIELDDESCRIPTIONCONTROL_HXX
#include "FieldDescControl.hxx"
#endif
#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef _SV_MSGBOX_HXX 
#include <vcl/msgbox.hxx>
#endif
#ifndef DBAUI_TABLEUNDO_HXX
#include "TableUndo.hxx"
#endif
#ifndef DBUI_TABLECONTROLLER_HXX
#include "TableController.hxx"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef DBAUI_SQLNAMEEDIT_HXX
#include "SqlNameEdit.hxx"
#endif
#ifndef DBAUI_TABLEROW_EXCHANGE_HXX
#include "TableRowExchange.hxx"
#endif
#ifndef _SOT_STORAGE_HXX 
#include <sot/storage.hxx>
#endif

using namespace ::dbaui;
using namespace ::comphelper;
using namespace ::svt;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdb;

namespace dbaui
{
    extern String GetTypeString( sal_uInt16 nType );
}
//==============================================================================

//	TYPEINIT1(OTableEditorCtrl, DBView);
DBG_NAME(OTableEditorCtrl);

//==============================================================================

#define HANDLE_ID		0

// Anzahl Spalten beim Neuanlegen
#define NEWCOLS		   128

// default Spaltenbreiten
#define FIELDNAME_WIDTH		100
#define FIELDTYPE_WIDTH		150
#define FIELDDESCR_WIDTH	300

// Maximale Eingabelaenge im Beschreibungsfeld
#define MAX_DESCR_LEN		256


#define CONTROL_SPACING_X	18	// 6
#define	CONTROL_SPACING_Y	5
#define CONTROL_HEIGHT		20
#define CONTROL_WIDTH_1		140	// 100
#define CONTROL_WIDTH_2		100 // 60
#define CONTROL_WIDTH_3		250
#define CONTROL_WIDTH_4		(CONTROL_WIDTH_3 - CONTROL_HEIGHT - 5)


//==================================================================
//------------------------------------------------------------------
OTableEditorCtrl::ClipboardInvalidator::ClipboardInvalidator(sal_uInt32 nTimeout,OTableEditorCtrl* _pOwner)
: m_pOwner(_pOwner)
{
    m_aInvalidateTimer.SetTimeout(nTimeout);
    m_aInvalidateTimer.SetTimeoutHdl(LINK(this, OTableEditorCtrl::ClipboardInvalidator, OnInvalidate));
    m_aInvalidateTimer.Start();
}

//------------------------------------------------------------------
OTableEditorCtrl::ClipboardInvalidator::~ClipboardInvalidator()
{
    m_aInvalidateTimer.Stop();
}

//------------------------------------------------------------------
IMPL_LINK(OTableEditorCtrl::ClipboardInvalidator, OnInvalidate, void*, EMPTYARG)
{
    m_pOwner->GetView()->getController()->InvalidateFeature(SID_CUT);
    m_pOwner->GetView()->getController()->InvalidateFeature(SID_COPY);
    m_pOwner->GetView()->getController()->InvalidateFeature(SID_PASTE);
    return 0L;
}

//==================================================================
void OTableEditorCtrl::Init()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    OTableRowView::Init();

    //////////////////////////////////////////////////////////////////////
    // Soll der Entwurf ReadOnly geoeffnet werden ?
    sal_Bool bRead(GetView()->getController()->isReadOnly());

    SetReadOnly( bRead );

    //////////////////////////////////////////////////////////////////////
    // Spalten einfuegen
    String aColumnName( ModuleRes(STR_TAB_FIELD_NAME) );
    InsertDataColumn( 1, aColumnName, FIELDNAME_WIDTH );

    aColumnName = String( ModuleRes(STR_TAB_FIELD_DATATYPE) );
    InsertDataColumn( 2, aColumnName, FIELDTYPE_WIDTH );

    aColumnName = String( ModuleRes(STR_TAB_FIELD_DESCR) );
    InsertDataColumn( 3, aColumnName, FIELDDESCR_WIDTH );

    InitCellController();

    //////////////////////////////////////////////////////////////////////
    // Zeilen einfuegen
    RowInserted(0, m_pRowList->size(), sal_True);
}

//==================================================================
void OTableEditorCtrl::UpdateAll()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    RowRemoved(0, GetRowCount(), sal_False);
    m_nDataPos = 0;

    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
    GetView()->getController()->InvalidateFeature(SID_SAVEDOC);
    Invalidate();
}
//==================================================================
OTableEditorCtrl::OTableEditorCtrl(Window* pWindow)
                   :OTableRowView(pWindow)
                   ,m_aInvalidate(500,this)
                   ,pNameCell(NULL)
                   ,pTypeCell(NULL)
                   ,pDescrCell(NULL)
                   ,nIndexEvent(0)
                   ,nOldDataPos(-1)
                   ,bSaveOnMove(sal_True)
                   ,nCutEvent(0)
                   ,nPasteEvent(0)
                   ,nDeleteEvent(0)
                   ,nInsNewRowsEvent(0)
                   ,nInvalidateTypeEvent(0)
                   ,nEntryNotFoundEvent(0)
                   ,bReadOnly(sal_True)
                   ,pActRow(NULL)
                   ,pDescrWin(NULL)
                   ,m_eChildFocus(NONE)
{
    DBG_CTOR(OTableEditorCtrl,NULL);

    SetHelpId(HID_TABDESIGN_BACKGROUND);
    GetDataWindow().SetHelpId(HID_CTL_TABLEEDIT);

    m_pRowList = GetView()->getController()->getRows();
    m_nDataPos = 0;
}

//------------------------------------------------------------------------------
SfxUndoManager* OTableEditorCtrl::GetUndoManager() const
{
    return GetView()->getController()->getUndoMgr();
}

//------------------------------------------------------------------------------
BOOL OTableEditorCtrl::IsReadOnly()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    return bReadOnly;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::SetReadOnly( sal_Bool bRead )
{
    // nix zu tun ?
    if (bRead == IsReadOnly())
        // diese Abfrage ist wichtig, da die zugrundeliegende Def sonst im folgenden gelockt oder ge-unlocked wird, obwohl es
        // nicht notwendig waere (und was schlimmer ist, das wuerde dann auch nicht wieder rueckgaengig gemacht)
        return;

    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    bReadOnly = bRead;

    //////////////////////////////////////////////////////////////////////
    // Aktive Zelle disablen
    long nRow(GetCurRow());
    sal_uInt16 nCol(GetCurColumnId());
    DeactivateCell();

    //////////////////////////////////////////////////////////////////////
    // ::com::sun::star::beans::Property Controls disablen
//	if (pDescrWin)
//		pDescrWin->SetReadOnly(bReadOnly || !SetDataPtr(nRow) || GetActRow()->IsReadOnly());

    //////////////////////////////////////////////////////////////////////
    // Cursor des Browsers anpassen
    BrowserMode nMode(BROWSER_COLUMNSELECTION | BROWSER_MULTISELECTION | BROWSER_KEEPSELECTION |
                      BROWSER_HLINESFULL	  | BROWSER_VLINESFULL|BROWSER_AUTOSIZE_LASTCOL);
    if( !bReadOnly )
        nMode |= BROWSER_HIDECURSOR;
    SetMode(nMode);

    if( !bReadOnly )
        ActivateCell( nRow, nCol );
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::InitCellController()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Zelle Feldname
    Reference<XConnection> xCon = GetView()->getController()->getConnection();
    Reference< XDatabaseMetaData> xMetaData = xCon.is() ? xCon->getMetaData() : Reference< XDatabaseMetaData>();

    xub_StrLen nMaxTextLen((xub_StrLen)xMetaData.is() ? xMetaData->getMaxColumnNameLength() : 0);

    if( nMaxTextLen == 0 )
        nMaxTextLen = EDIT_NOLIMIT;	

    pNameCell = new OSQLNameEdit( &GetDataWindow(), xMetaData.is() ? xMetaData->getExtraNameCharacters() : ::rtl::OUString(),WB_LEFT );
    pNameCell->SetMaxTextLen( nMaxTextLen );

    //////////////////////////////////////////////////////////////////////
    // Zelle Typ
    pTypeCell = new ListBoxControl( &GetDataWindow() );

    //////////////////////////////////////////////////////////////////////
    // Zelle Beschreibung
    pDescrCell = new Edit( &GetDataWindow(), WB_LEFT );
    pDescrCell->SetMaxTextLen( MAX_DESCR_LEN );

    pNameCell->SetHelpId(HID_TABDESIGN_NAMECELL);
    pTypeCell->SetHelpId(HID_TABDESIGN_TYPECELL);
    pDescrCell->SetHelpId(HID_TABDESIGN_COMMENTCELL);

    ClearModified();
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::ClearModified()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    pNameCell->ClearModifyFlag();
    pDescrCell->ClearModifyFlag();
    pTypeCell->SaveValue();
}

//------------------------------------------------------------------------------
OTableEditorCtrl::~OTableEditorCtrl()
{
    DBG_DTOR(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Undo-Manager zuruecksetzen
    GetUndoManager()->Clear();

    //////////////////////////////////////////////////////////////////////
    // Moegliche Events aus Queue entfernen
    if( nCutEvent )
        Application::RemoveUserEvent( nCutEvent );
    if( nPasteEvent )
        Application::RemoveUserEvent( nPasteEvent );
    if( nDeleteEvent )
        Application::RemoveUserEvent( nDeleteEvent );
    if( nInsNewRowsEvent )
        Application::RemoveUserEvent( nInsNewRowsEvent );
    if( nInvalidateTypeEvent )
        Application::RemoveUserEvent( nInvalidateTypeEvent );
    if( nEntryNotFoundEvent )
        Application::RemoveUserEvent( nEntryNotFoundEvent );

    //////////////////////////////////////////////////////////////////////
    // Controltypen zerstoeren
    delete pNameCell;
    delete pTypeCell;
    delete pDescrCell;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::SetDataPtr( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    if(nRow == -1)
        return sal_False;

    OSL_ENSURE((xub_StrLen)nRow < m_pRowList->size(),"Row is greater than size!");
    if(nRow >= (long)m_pRowList->size())
        return NULL;
    pActRow = (*m_pRowList)[nRow];
    return pActRow != NULL;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::SeekRow(long _nRow)
{
    // die Basisklasse braucht den Aufruf, da sie sich dort merkt, welche Zeile gepainted wird
    EditBrowseBox::SeekRow(_nRow);

    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    m_nCurrentPos = _nRow;
    return SetDataPtr(_nRow);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::PaintCell(OutputDevice& rDev, const Rectangle& rRect,
                                   sal_uInt16 nColumnId ) const
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    String aText( GetCellText( m_nCurrentPos, nColumnId ));
    Point aPos(rRect.TopLeft());
    Size TxtSize(GetDataWindow().GetTextWidth(aText), GetDataWindow().GetTextHeight());

    if (aPos.X() < rRect.Right() || aPos.X() + TxtSize.Width() > rRect.Right() ||
        aPos.Y() < rRect.Top() || aPos.Y() + TxtSize.Height() > rRect.Bottom())
        rDev.SetClipRegion( rRect );

    rDev.DrawText(aPos, aText);

    if (rDev.IsClipRegion())
        rDev.SetClipRegion();
//	rDev.DrawText(rRect.TopLeft(), aText);
//	rDev.SetClipRegion( );
}

//------------------------------------------------------------------------------
CellController* OTableEditorCtrl::GetController(long nRow, sal_uInt16 nColumnId)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Wenn EditorCtrl ReadOnly ist, darf nicht editiert werden
    Reference<XPropertySet> xTable = GetView()->getController()->getTable();
    if (IsReadOnly() || (	xTable.is() && 
                            xTable->getPropertySetInfo()->hasPropertyByName(PROPERTY_TYPE) && 
                            ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) == ::rtl::OUString::createFromAscii("VIEW")))
        return NULL;

    //////////////////////////////////////////////////////////////////////
    // Wenn Zeile ReadOnly ist, darf sie nicht editiert werden
    SetDataPtr( nRow );
    if( pActRow->IsReadOnly() )
        return NULL;

    OFieldDescription* pActFieldDescr = pActRow->GetActFieldDescr();
    switch (nColumnId)
    {
        case FIELD_NAME:
            return new EditCellController( pNameCell );
        case FIELD_TYPE:
            if (pActFieldDescr && (pActFieldDescr->GetName().getLength() != 0))
                return new ListBoxCellController( pTypeCell );
            else return NULL;
        case FIELD_DESCR:
            if (pActFieldDescr && (pActFieldDescr->GetName().getLength() != 0))
                return new EditCellController( pDescrCell );
            else return NULL;
        default:
            return NULL;
    }
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::InitController(CellControllerRef&, long nRow, sal_uInt16 nColumnId)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    SeekRow( nRow == -1 ? GetCurRow() : nRow);
    OFieldDescription* pActFieldDescr = pActRow->GetActFieldDescr();
    String aInitString;

    switch (nColumnId)
    {
        case FIELD_NAME:
            if( pActFieldDescr )
                aInitString = pActFieldDescr->GetName();
            pNameCell->SetText( aInitString );
            break;
        case FIELD_TYPE:
            {
                if( pActFieldDescr )
                    aInitString = pActFieldDescr->getTypeInfo()->aUIName;

                //////////////////////////////////////////////////////////////
                // Anpassen des ComboBoxInhalts
                pTypeCell->Clear();
                if( !pActFieldDescr )
                    break;
                    
                const OTypeInfoMap* pTypeInfo = GetView()->getController()->getTypeInfo();
                OTypeInfoMap::const_iterator aIter = pTypeInfo->begin();
                for(;aIter != pTypeInfo->end();++aIter)
                    pTypeCell->InsertEntry( aIter->second->aUIName );
                pTypeCell->SelectEntry( aInitString );
            }

            break;
        case FIELD_DESCR:
            if( pActFieldDescr )
                aInitString = pActFieldDescr->GetDescription();
            pDescrCell->SetText( aInitString );
            break;

    }
}

//------------------------------------------------------------------------------
EditBrowseBox::RowStatus OTableEditorCtrl::GetRowStatus(long nRow) const
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    ( (OTableEditorCtrl*)this )->SetDataPtr( nRow );
    if( !pActRow )
        return EditBrowseBox::CLEAN;
    if (nRow >= 0 && nRow == m_nDataPos)
    {
        if( pActRow->IsPrimaryKey() )
            return EditBrowseBox::CURRENT_PRIMARYKEY;
        return EditBrowseBox::CURRENT;
    }
    else
    {
        if( pActRow->IsPrimaryKey() )
            return EditBrowseBox::PRIMARYKEY;
        return EditBrowseBox::CLEAN;
    }
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::SaveCurRow()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    if (GetFieldDescr(GetCurRow()) == NULL)
        // in der Zeile, in der ich mich i.A. befinde, stehen keine Daten
        return sal_True;
    if (!SaveModified())
        return sal_False;

    SetDataPtr(GetCurRow());
    pDescrWin->SaveData( pActRow->GetActFieldDescr() );
    return sal_True;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::DisplayData(long nRow, sal_Bool bGrabFocus)
{
    // zur richtigen Zelle fahren
    SetDataPtr(nRow);

    // Editier-Modus temporaer aus
    sal_Bool bWasEditing = IsEditing();
    if (bWasEditing)
        DeactivateCell();

    CellControllerRef aTemp;
    InitController(aTemp, nRow, FIELD_NAME);
    InitController(aTemp, nRow, FIELD_TYPE);
    InitController(aTemp, nRow, FIELD_DESCR);

    GoToRow(nRow);
    // das Description-Window aktualisieren
    GetView()->GetDescWin()->DisplayData(GetFieldDescr(nRow));
    // neu zeichnen
    RowModified(nRow);

    // wieder an
    if (bWasEditing || bGrabFocus)
        ActivateCell(nRow, GetCurColumnId(), bGrabFocus);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::CursorMoved()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Zeilenwechsel ?
    m_nDataPos = GetCurRow();
    if( m_nDataPos != nOldDataPos && m_nDataPos != -1)
    {
        CellControllerRef aTemp;
        InitController(aTemp,m_nDataPos,FIELD_NAME);
        InitController(aTemp,m_nDataPos,FIELD_TYPE);
        InitController(aTemp,m_nDataPos,FIELD_DESCR);
    }

    OTableRowView::CursorMoved();
}

//------------------------------------------------------------------------------
sal_Int32 OTableEditorCtrl::HasFieldName( const String& rFieldName )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    Reference<XConnection> xCon = GetView()->getController()->getConnection();
    Reference< XDatabaseMetaData> xMetaData = xCon.is() ? xCon->getMetaData() : Reference< XDatabaseMetaData>();

    ::comphelper::UStringMixEqual bCase(xMetaData.is() ? xMetaData->storesMixedCaseQuotedIdentifiers() : sal_True);

    ::std::vector<OTableRow*>::iterator aIter = m_pRowList->begin();
    OFieldDescription* pFieldDescr;
    sal_Int32 nCount(0);
    for(;aIter != m_pRowList->end();++aIter)
    {
        pFieldDescr = (*aIter)->GetActFieldDescr();
        if( pFieldDescr && bCase(rFieldName,pFieldDescr->GetName()))
            nCount++;
    }
    return nCount;
}
// --------------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::SaveData(long nRow, sal_uInt16 nColId)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////
    // Zellinhalte in Datenstruktur speichern
    SetDataPtr( nRow == -1 ? GetCurRow() : nRow);
    OFieldDescription* pActFieldDescr = pActRow->GetActFieldDescr();

    switch( nColId)
    {
        //////////////////////////////////////////////////////////////
        // Speichern Inhalt NameCell
        case FIELD_NAME:
        {
            //////////////////////////////////////////////////////////////
            // Wenn kein Name, nichts machen
            String aName(pNameCell->GetText());

            if( !aName.Len() )
            {
                //////////////////////////////////////////////////////////////
                // Wenn FieldDescr existiert, wurde Feld geloescht und alter Inhalt wird wiederhergestellt
                if (pActFieldDescr)
                {
                    GetUndoManager()->AddUndoAction(new OTableEditorTypeSelUndoAct(this, nRow, FIELD_TYPE, pActFieldDescr->getTypeInfo()));
                    SwitchType(NULL);
                    pActFieldDescr = pActRow->GetActFieldDescr();
                }
                else
                    return sal_True;
            }
            if(pActFieldDescr)
                pActFieldDescr->SetName( aName );
            pNameCell->ClearModifyFlag();

            break;
        }

        //////////////////////////////////////////////////////////////
        // Speichern Inhalt TypeCell
        case FIELD_TYPE:
            break;

        //////////////////////////////////////////////////////////////
        // Speichern Inhalt DescrCell
        case FIELD_DESCR:
        {
            //////////////////////////////////////////////////////////////
            // Wenn aktuelle Feldbeschreibung NULL, Default setzen
            if( !pActFieldDescr )
                pDescrCell->SetText(String());
            else
                pActFieldDescr->SetDescription( pDescrCell->GetText() );
            break;
        }
        case FIELD_PROPERTY_DEFAULT:
        case FIELD_PROPERTY_REQUIRED:
        case FIELD_PROPERTY_TEXTLEN:
        case FIELD_PROPERTY_NUMTYPE:
        case FIELD_PROPERTY_AUTOINC:
        case FIELD_PROPERTY_LENGTH:
        case FIELD_PROPERTY_SCALE:
        case FIELD_PROPERTY_BOOL_DEFAULT:
            pDescrWin->SaveData(pActFieldDescr);
            break;
    }
    return sal_True;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::SaveModified()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    sal_uInt16 nColId = GetCurColumnId();

    switch( nColId )
    {
        //////////////////////////////////////////////////////////////
        // NameCell
        case FIELD_NAME:
        {
            // removed the former duplicate-check. this is done in OTableDocShell::CheckDefConsistency now.
            // FS - 07.12.99 - 69575

        } break;

        //////////////////////////////////////////////////////////////
        // TypeCell
        case FIELD_TYPE:
        {
            //////////////////////////////////////////////////////////////////////
            // Type umstellen
            SwitchType(GetView()->getController()->getTypeInfo(pTypeCell->GetSelectEntryPos()));
        } break;
    }

    return sal_True;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::CursorMoving(long nNewRow, sal_uInt16 nNewCol)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    if (!EditBrowseBox::CursorMoving(nNewRow, nNewCol))
        return sal_False;

    //////////////////////////////////////////////////////////////////////
    // Wird nach SaveModified() gerufen, aktuelle Zeile ist noch die alte
    m_nDataPos = nNewRow;
    nOldDataPos = GetCurRow();

    //////////////////////////////////////////////////////////////////////
    // Marker umsetzen
    InvalidateStatusCell( nOldDataPos );
    InvalidateStatusCell( m_nDataPos );

    //////////////////////////////////////////////////////////////////////
    // Daten des Propertyfensters speichern
    if( SetDataPtr(nOldDataPos) && pDescrWin)
        pDescrWin->SaveData( pActRow->GetActFieldDescr() );

    //////////////////////////////////////////////////////////////////////
    // Neue Daten im Propertyfenster anzeigen
    if( SetDataPtr(m_nDataPos) && pDescrWin)
        pDescrWin->DisplayData( pActRow->GetActFieldDescr() );

    return sal_True;
}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, InvalidateFieldType, void*, EMPTYTAG )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    nInvalidateTypeEvent = 0;
    Invalidate( GetFieldRectPixel(nOldDataPos, FIELD_TYPE) );

    return 0;
}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, EntryNotFound, void*, EMPTYTAG )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    nEntryNotFoundEvent = 0;
    ErrorBox( this, ModuleRes(ERR_INVALID_LISTBOX_ENTRY) ).Execute();

    return 0;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::CellModified( long nRow, sal_uInt16 nColId )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    //////////////////////////////////////////////////////////////
    // Wenn aktuelle Feldbeschreibung NULL, Default setzen
    if(nRow == -1)
        nRow = GetCurRow();
    SetDataPtr( nRow );
    OFieldDescription* pActFieldDescr = pActRow->GetActFieldDescr();

    GetUndoManager()->EnterListAction(String::CreateFromAscii("TODO"), String());
    if (!pActFieldDescr)
    {
        OTypeInfoMap::const_iterator aTypeIter = GetView()->getController()->getTypeInfo()->find(DataType::VARCHAR);
        if(aTypeIter == GetView()->getController()->getTypeInfo()->end())
            aTypeIter = GetView()->getController()->getTypeInfo()->begin();
        pActRow->SetFieldType( aTypeIter->second );
        nInvalidateTypeEvent = Application::PostUserEvent( LINK(this, OTableEditorCtrl, InvalidateFieldType) );
        pActFieldDescr = pActRow->GetActFieldDescr();
        pDescrWin->DisplayData( pActFieldDescr );
        GetUndoManager()->AddUndoAction( new OTableEditorTypeSelUndoAct(this, nRow, nColId+1, NULL) );
    }

    if( nColId != FIELD_TYPE )
        GetUndoManager()->AddUndoAction( new OTableDesignCellUndoAct(this, nRow, nColId) );
    else
    {
        GetUndoManager()->AddUndoAction(new OTableEditorTypeSelUndoAct(this, GetCurRow(), nColId, GetFieldDescr(GetCurRow())->getTypeInfo()));
        USHORT nPos = pTypeCell->GetSelectEntryPos();
        if(nPos != LISTBOX_ENTRY_NOTFOUND)
            SwitchType( GetView()->getController()->getTypeInfo(nPos) );
        else
            SwitchType(NULL);

    }
    
    SaveData(nRow,nColId);
    // SaveData could create a undo action as well
    GetUndoManager()->LeaveListAction();
    RowModified(nRow);
    CellControllerRef xController(Controller());
    if(xController.Is())
        xController->SetModified();
    
    //////////////////////////////////////////////////////////////////////
    // Das ModifyFlag setzen
    GetView()->getController()->setModified( sal_True );
    GetView()->getController()->InvalidateFeature(SID_SAVEDOC);
    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::CellModified()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    CellModified( GetCurRow(), GetCurColumnId() );
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::Undo()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
    GetView()->getController()->InvalidateFeature(SID_SAVEDOC);
}


//------------------------------------------------------------------------------
void OTableEditorCtrl::Redo()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
    GetView()->getController()->InvalidateFeature(SID_SAVEDOC);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::CopyRows()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // set to the right row and save it
    if( SetDataPtr(m_nDataPos) )
        pDescrWin->SaveData( pActRow->GetActFieldDescr() );

    //////////////////////////////////////////////////////////////////////
    // Selektierte Zeilen in die ClipboardListe kopieren
    OTableRow* pClipboardRow;
    OTableRow* pRow;
    ::std::vector<OTableRow*> vClipboardList;

    for( long nIndex=FirstSelectedRow(); nIndex>=0; nIndex=NextSelectedRow() )
    {
        pRow = (*m_pRowList)[nIndex];
        pClipboardRow = new OTableRow( *pRow );
        vClipboardList.push_back( pClipboardRow);
    }
    if(vClipboardList.size())
    {
        OTableRowExchange* pData = new OTableRowExchange(vClipboardList);
        Reference< ::com::sun::star::datatransfer::XTransferable> xRef = pData;
#if SUPD<631
        pData->CopyToClipboard();
#else
        pData->CopyToClipboard(GetParent());
#endif
    }
}

//------------------------------------------------------------------------------
String OTableEditorCtrl::GenerateName( const String& rName )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Basisnamen zum Anhaengen einer Numerierung erstellen
    String aBaseName;
    Reference<XConnection> xCon = GetView()->getController()->getConnection();
    Reference< XDatabaseMetaData> xMetaData = xCon.is() ? xCon->getMetaData() : Reference< XDatabaseMetaData>();

    xub_StrLen nMaxTextLen((xub_StrLen)( xMetaData.is() ? xMetaData->getMaxColumnNameLength() : 0));

    if( (rName.Len()+2) >nMaxTextLen )
        aBaseName = rName.Copy( 0, nMaxTextLen-2 );
    else
        aBaseName = rName;

    //////////////////////////////////////////////////////////////////////
    // Namen durchnumerieren (bis 99)
    String aFieldName( rName);
    sal_Int32 i=1;
    while( HasFieldName(aFieldName) )
    {
        aFieldName = aBaseName;
        aFieldName += String::CreateFromInt32(i);
        i++;
    }

    return aFieldName;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::InsertRows( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    ::std::vector< OTableRow*> vInsertedUndoRedoRows; // need for undo/redo handling
    //////////////////////////////////////////////////////////////////////
    // get rows from clipboard
#if SUPD<631
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard());
#else
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(GetParent()));
#endif
    if(aTransferData.HasFormat(SOT_FORMATSTR_ID_SBA_TABED))
    {
        SotStorageStreamRef aStreamRef;
        aTransferData.GetSotStorageStream(SOT_FORMATSTR_ID_SBA_TABED,aStreamRef);
        if(aStreamRef.Is())
        {
            aStreamRef->Seek(STREAM_SEEK_TO_BEGIN);
            aStreamRef->ResetError();
            long nInsertRow = nRow;
            String aFieldName;
            OTableRow* pRow;
            sal_Int32 nSize = 0;
            (*aStreamRef) >> nSize;
            for(sal_Int32 i=0;i < nSize;++i)
            {
                pRow = new OTableRow();
                (*aStreamRef) >> *pRow;
                pRow->SetReadOnly( sal_False );
                sal_Int32 nType = pRow->GetActFieldDescr()->GetType();
                pRow->GetActFieldDescr()->SetType(GetView()->getController()->getTypeInfoByType(nType));
                //////////////////////////////////////////////////////////////////////
                // Anpassen des Feldnamens
                aFieldName = GenerateName( pRow->GetActFieldDescr()->GetName() );
                pRow->GetActFieldDescr()->SetName( aFieldName );

                m_pRowList->insert( m_pRowList->begin()+nInsertRow,pRow );
                vInsertedUndoRedoRows.push_back(new OTableRow(*pRow));
                nInsertRow++;
            }
        }
    }
    //////////////////////////////////////////////////////////////////////
    // Beim RowInserted wird CursorMoved gerufen.
    // Die UI-Daten duerfen hier beim CursorMoved nicht gespeichert werden.
    bSaveOnMove = sal_False;
    RowInserted( nRow,vInsertedUndoRedoRows.size(),sal_True );
    bSaveOnMove = sal_True;

    //////////////////////////////////////////////////////////////////////
    // Undo-Action erzeugen
    GetUndoManager()->AddUndoAction( new OTableEditorInsUndoAct(this, nRow,vInsertedUndoRedoRows) );
    GetView()->getController()->setModified( sal_True );
    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::DeleteRows()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    OSL_ENSURE(GetView()->getController()->isDropAllowed(),"Call of DeleteRows not valid here. Please check isDropAllowed!");
    //////////////////////////////////////////////////////////////////////
    // Undo-Action erzeugen
    GetUndoManager()->AddUndoAction( new OTableEditorDelUndoAct(this) );
    

    //////////////////////////////////////////////////////////////////////
    // Alle markierten Zeilen loeschen
    long nIndex = FirstSelectedRow();
    nOldDataPos = nIndex;
    bSaveOnMove = sal_False;

    while( nIndex >= 0 )
    {
        //////////////////////////////////////////////////////////////////////
        // Zeile entfernen
        delete (*m_pRowList)[nIndex];
        m_pRowList->erase( m_pRowList->begin()+nIndex );
        RowRemoved( nIndex, 1, sal_True );

        //////////////////////////////////////////////////////////////////////
        // Leerzeile am Ende wieder einfuegen
        m_pRowList->push_back( new OTableRow());
        RowInserted( GetRowCount()-1, 1, sal_True );

        nIndex = FirstSelectedRow();
    }

    bSaveOnMove = sal_True;

    //////////////////////////////////////////////////////////////////////
    // Erzwingen, dass der aktuelle Datensatz angezeigt wird
    m_nDataPos = GetCurRow();
    InvalidateStatusCell( nOldDataPos );
    InvalidateStatusCell( m_nDataPos );
    SetDataPtr( m_nDataPos );
    ActivateCell();
    pDescrWin->DisplayData( pActRow->GetActFieldDescr() );
    GetView()->getController()->setModified( sal_True );
    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::InsertNewRows( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    OSL_ENSURE(GetView()->getController()->isAddAllowed(),"Call of InsertNewRows not valid here. Please check isAppendAllowed!");
    //////////////////////////////////////////////////////////////////////
    // Undo-Action erzeugen
    long nInsertRows = GetSelectRowCount();
    if( !nInsertRows )
        nInsertRows = 1;
    GetUndoManager()->AddUndoAction( new OTableEditorInsNewUndoAct(this, nRow, nInsertRows) );
    //////////////////////////////////////////////////////////////////////
    // Zahl der selektierten Zeilen werden neu eingefuegt
    for( long i=nRow; i<(nRow+nInsertRows); i++ )
        m_pRowList->insert( m_pRowList->begin()+i ,new OTableRow());
    RowInserted( nRow, nInsertRows, sal_True );

    GetView()->getController()->setModified( sal_True );
    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
}

//------------------------------------------------------------------------------
String OTableEditorCtrl::GetControlText( long nRow, sal_uInt16 nColId )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Controls des Browsers auslesen
    if( nColId < FIELD_FIRST_VIRTUAL_COLUMN )
    {
        GoToRow( nRow );
        GoToColumnId( nColId );
        CellControllerRef xController = Controller();
        if(xController.Is())
            return xController->GetWindow().GetText();
        else
            return GetCellText(nRow,nColId);
    }

    //////////////////////////////////////////////////////////////////////
    // Controls der Tabpage Auslesen
    else
        return pDescrWin->GetControlText( nColId );
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::SetControlText( long nRow, sal_uInt16 nColId, const String& rText )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Controls des Browsers setzen
    if( nColId < FIELD_FIRST_VIRTUAL_COLUMN )
    {
        GoToRow( nRow );
        GoToColumnId( nColId );
        CellControllerRef xController = Controller();
        if(xController.Is())
            xController->GetWindow().SetText( rText );
        else
            RowModified(nRow,nColId);
    }

    //////////////////////////////////////////////////////////////////////
    // Controls der Tabpage setzen
    else
    {
        pDescrWin->SetControlText( nColId, rText );
    }
}
//------------------------------------------------------------------------------
void OTableEditorCtrl::SetData( long nRow, sal_uInt16 nColId, const OTypeInfo* _pTypeInfo )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Aktuellen Datenzeiger umsetzen
    if( nRow == -1 )
        nRow = GetCurRow();
    OFieldDescription* pFieldDescr = GetFieldDescr( nRow );
    if( !pFieldDescr && nColId != FIELD_TYPE)
        return;

    //////////////////////////////////////////////////////////////////////
    // Einzelne Felder setzen
    switch( nColId )
    {
        case FIELD_TYPE:
            SwitchType( _pTypeInfo );
            break;
        default:
            OSL_ENSURE(sal_False, "OTableEditorCtrl::SetData: invalid column!");
    }
    SetControlText(nRow,nColId,_pTypeInfo ? _pTypeInfo->aUIName : ::rtl::OUString());
}
//------------------------------------------------------------------------------
void OTableEditorCtrl::SetData( long nRow, sal_uInt16 nColId, const String& _rNewData )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Aktuellen Datenzeiger umsetzen
    if( nRow == -1 )
        nRow = GetCurRow();
    OFieldDescription* pFieldDescr = GetFieldDescr( nRow );
    if( !pFieldDescr && nColId != FIELD_TYPE)
        return;
//	{
//		OTypeInfoMap::const_iterator aTypeIter = GetView()->getController()->getTypeInfo()->find(DataType::VARCHAR);
//		if(aTypeIter == GetView()->getController()->getTypeInfo()->end())
//			aTypeIter = GetView()->getController()->getTypeInfo()->begin();
//
//		OTableRow* pRow = (*m_pRowList)[nRow];
//		pRow->SetFieldType( aTypeIter->second );
//		pFieldDescr = pRow->GetActFieldDescr();
//	}

    
    //////////////////////////////////////////////////////////////////////
    // Einzelne Felder setzen
    switch( nColId )
    {
        case FIELD_NAME:
            pFieldDescr->SetName( _rNewData );
            break;

        case FIELD_TYPE:
            OSL_ENSURE(sal_False, "OTableEditorCtrl::SetData: invalid column!");
            break;

        case FIELD_DESCR:
            pFieldDescr->SetDescription( _rNewData );
            break;

        case FIELD_PROPERTY_DEFAULT:
            pFieldDescr->SetDefaultValue( _rNewData );
            break;

        case FIELD_PROPERTY_REQUIRED:
            pFieldDescr->SetIsNullable( _rNewData.ToInt32() );
            break;

        case FIELD_PROPERTY_TEXTLEN:
        case FIELD_PROPERTY_LENGTH:
            pFieldDescr->SetPrecision( _rNewData.ToInt32() );
            break;

        case FIELD_PROPERTY_NUMTYPE:
            //	pFieldDescr->SetNumType( _rNewData );
            OSL_ENSURE(sal_False, "OTableEditorCtrl::SetData: invalid column!");
            break;

        case FIELD_PROPERTY_AUTOINC:
            {
                String strYes(ModuleRes(STR_VALUE_YES));
                String strNo(ModuleRes(STR_VALUE_NO));
                pFieldDescr->SetAutoIncrement(_rNewData.Equals(strYes));
            }
            break;
        case FIELD_PROPERTY_SCALE:
            pFieldDescr->SetScale(_rNewData.ToInt32());
            break;

        case FIELD_PROPERTY_BOOL_DEFAULT:
            pFieldDescr->SetDefaultValue(GetView()->GetDescWin()->BoolStringPersistent(_rNewData));
            break;

        case FIELD_PROPERTY_FORMAT:
            pFieldDescr->SetFormatKey(_rNewData.ToInt32());
            break;
    }

    SetControlText(nRow,nColId,_rNewData);
}

//------------------------------------------------------------------------------
String OTableEditorCtrl::GetData( long nRow, sal_uInt16 nColId )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    OFieldDescription* pFieldDescr = GetFieldDescr( nRow );
    if( !pFieldDescr )
        return String();

    //////////////////////////////////////////////////////////////////////
    // Aktuellen Datenzeiger umsetzen
    if( nRow==-1 )
        nRow = GetCurRow();
    SetDataPtr( nRow );

    static const String strYes(ModuleRes(STR_VALUE_YES));
    static const String strNo(ModuleRes(STR_VALUE_NO));
    //////////////////////////////////////////////////////////////////////
    // Einzelne Felder auslesen
    switch( nColId )
    {
        case FIELD_NAME:
            return pFieldDescr->GetName();

        case FIELD_TYPE:
            return pFieldDescr->getTypeInfo()->aUIName;

        case FIELD_DESCR:
            return pFieldDescr->GetDescription();

        case FIELD_PROPERTY_DEFAULT:
            return pFieldDescr->GetDefaultValue();

        case FIELD_PROPERTY_REQUIRED:
            return pFieldDescr->GetIsNullable() == ColumnValue::NULLABLE ? strYes : strNo;

        case FIELD_PROPERTY_TEXTLEN:
        case FIELD_PROPERTY_LENGTH:
            return String::CreateFromInt32(pFieldDescr->GetPrecision());

        case FIELD_PROPERTY_NUMTYPE:
            OSL_ENSURE(sal_False, "OTableEditorCtrl::GetData: invalid column!");
            //	return pFieldDescr->GetNumType();

        case FIELD_PROPERTY_AUTOINC:
            return pFieldDescr->IsAutoIncrement() ? strYes : strNo;

        case FIELD_PROPERTY_SCALE:
            return String::CreateFromInt32(pFieldDescr->GetScale());

        case FIELD_PROPERTY_BOOL_DEFAULT:
            return GetView()->GetDescWin()->BoolStringUI(pFieldDescr->GetDefaultValue());

        case FIELD_PROPERTY_FORMAT:
            return String::CreateFromInt32(pFieldDescr->GetFormatKey());
    }

    return String();
}

//------------------------------------------------------------------------------
String OTableEditorCtrl::GetCellText( long nRow, sal_uInt16 nColId ) const
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Text aus Dokumentdaten holen
    return const_cast<OTableEditorCtrl*>(this)->GetData( nRow, nColId );
}

//------------------------------------------------------------------------------
sal_uInt32 OTableEditorCtrl::GetTotalCellWidth(long nRow, sal_uInt16 nColId)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    return GetTextWidth(GetCellText(nRow, nColId)) + 2 * GetTextWidth('0');
}

//------------------------------------------------------------------------------
OFieldDescription* OTableEditorCtrl::GetFieldDescr( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    sal_uInt16 nListCount(m_pRowList->size());
    if( (nRow<0) || (nRow>=nListCount) )
    {
        OSL_ENSURE(0,"(nRow<0) || (nRow>=nListCount)");
        return NULL;
    }
    OTableRow* pRow = (*m_pRowList)[ nRow ];
    if( !pRow )
        return NULL;
    return pRow->GetActFieldDescr();
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsCutAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    sal_Bool bIsCutAllowed = (GetView()->getController()->isAddAllowed() && GetView()->getController()->isDropAllowed()) || 
                            GetView()->getController()->isAlterAllowed();

    if(bIsCutAllowed)
    {
        if(m_eChildFocus == DESCRIPTION)
            bIsCutAllowed = pDescrCell->GetSelected().Len() != 0;
        else if(m_eChildFocus == NAME)
            bIsCutAllowed = pNameCell->GetSelected().Len() != 0;
        else if(m_eChildFocus == ROW)
        // only rows are selected for cutting so we look if all rows are valid
        // wwe don't waant to copy empty rows here
            bIsCutAllowed = IsCopyAllowed(nRow);
        else
            bIsCutAllowed = sal_False;
    }

//	Reference<XPropertySet> xTable = GetView()->getController()->getTable();
//	if( !IsCopyAllowed(nRow) || (xTable.is() && ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) == ::rtl::OUString::createFromAscii("VIEW")))
//		return sal_False;

    //	return bCutAllowed && IsDeleteAllowed( nRow );
    return bIsCutAllowed;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsCopyAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    Reference<XPropertySet> xTable = GetView()->getController()->getTable();
    if( !GetSelectRowCount() || (xTable.is() && ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) == ::rtl::OUString::createFromAscii("VIEW")))
        return sal_False;

    //////////////////////////////////////////////////////////////////////
    // Wenn eine der markierten Zeilen leer ist, kein Copy moeglich
    OTableRow* pRow;
    long nIndex = FirstSelectedRow();
    while( nIndex >= 0 )
    {
        pRow = (*m_pRowList)[nIndex];
        if( !pRow->GetActFieldDescr() )
            return sal_False;

        nIndex = NextSelectedRow();
    }

    return sal_True;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsPasteAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    return GetView()->getController()->isAddAllowed();
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::Cut()
{
    if(m_eChildFocus == NAME)
    {
        if(GetView()->getController()->isAlterAllowed())
        {
            SaveData(-1,FIELD_NAME);
            pNameCell->Cut();
            CellModified(-1,FIELD_NAME);
        }
    }
    else if(m_eChildFocus == DESCRIPTION)
    {
        if(GetView()->getController()->isAlterAllowed())
        {
            SaveData(-1,FIELD_DESCR);
            pDescrCell->Cut();
            CellModified(-1,FIELD_DESCR);
        }
    }
    else if(m_eChildFocus == ROW)
    {
        if (nCutEvent)
            Application::RemoveUserEvent(nCutEvent);
        nCutEvent = Application::PostUserEvent(LINK(this, OTableEditorCtrl, DelayedCut));
    }
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::Copy()
{
    if(GetSelectRowCount())
        OTableRowView::Copy();
    else if(m_eChildFocus == NAME)
        pNameCell->Copy();
    else if(m_eChildFocus == DESCRIPTION)
        pDescrCell->Copy();
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::Paste()
{
#if SUPD<631
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard());
#else
    TransferableDataHelper aTransferData(TransferableDataHelper::CreateFromSystemClipboard(GetParent()));
#endif
    if(aTransferData.HasFormat(SOT_FORMATSTR_ID_SBA_TABED))
    {
        if( nPasteEvent )
            Application::RemoveUserEvent( nPasteEvent );
        nPasteEvent = Application::PostUserEvent( LINK(this, OTableEditorCtrl, DelayedPaste) );
    }
    else if(m_eChildFocus == NAME)
    {
        if(GetView()->getController()->isAlterAllowed())
            pNameCell->Paste();
    }
    else if(m_eChildFocus == DESCRIPTION)
    {
        if(GetView()->getController()->isAlterAllowed())
            pDescrCell->Paste();
    }
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsDeleteAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    return GetSelectRowCount() != 0 && GetView()->getController()->isDropAllowed();
//	Reference<XPropertySet> xTable = GetView()->getController()->getTable();
//	if( !GetSelectRowCount() || (xTable.is() && ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) == ::rtl::OUString::createFromAscii("VIEW")))
//		return sal_False;
//
//	// Wenn nur Felder hinzugefuegt werden duerfen, Delete nur auf neuen Feldern
//	Reference<XConnection> xCon = GetView()->getController()->getConnection();
//	Reference< XDatabaseMetaData> xMetaData = xCon.is() ? xCon->getMetaData() : NULL;
//
//	return	!(xTable.is() && xTable->getPropertySetInfo()->getPropertyByName(PROPERTY_NAME).Attributes & PropertyAttribute::READONLY) || 
//			( xMetaData.is() && xMetaData->supportsAlterTableWithAddColumn() && xMetaData->supportsAlterTableWithDropColumn());
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsInsertNewAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);

    sal_Bool bInsertNewAllowed = GetView()->getController()->isAddAllowed();
    //////////////////////////////////////////////////////////////
    // Wenn nur Felder hinzugefuegt werden duerfen, Paste nur in neue Felder
    if (bInsertNewAllowed && !GetView()->getController()->isDropAllowed())
    {
        SetDataPtr(nRow);
        if( GetActRow()->IsReadOnly() )
            return sal_False;
    }

    return bInsertNewAllowed;
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsPrimaryKeyAllowed( long nRow )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    if( !GetSelectRowCount() )
        return sal_False;

    Reference<XConnection> xCon = GetView()->getController()->getConnection();

    Reference< XDatabaseMetaData> xMetaData = xCon.is() ? xCon->getMetaData() : Reference< XDatabaseMetaData>();
    Reference<XPropertySet> xTable = GetView()->getController()->getTable();
    Reference<XKeysSupplier> xKeySup(xTable,UNO_QUERY);
    Reference<XIndexAccess> xIndexAccess;
    if(xKeySup.is())
        xIndexAccess = xKeySup->getKeys();

    if(!xIndexAccess.is() && (!xMetaData.is() || !xMetaData->supportsCoreSQLGrammar()))
        return sal_False; // no primary keys allowed

    //////////////////////////////////////////////////////////////
    // Key darf nicht veraendert werden
    // Dies gilt jedoch nur, wenn die Tabelle nicht neu ist und keine ::com::sun::star::sdbcx::View. Ansonsten wird kein DROP ausgef�hrt

    sal_Bool bDropNotAllowed = sal_False;
    if (!(	GetView()->getController()->isDropAllowed() ||
                !(xTable.is() && xTable->getPropertySetInfo()->getPropertyByName(PROPERTY_NAME).Attributes & PropertyAttribute::READONLY)) &&
            GetView()->getController()->isAddAllowed() &&
                (xTable.is() && ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) != ::rtl::OUString::createFromAscii("VIEW")))
        bDropNotAllowed = sal_True;

    //////////////////////////////////////////////////////////////
    // Wenn leeres Feld, kein PrimKey
    // Eintrag wird nur erlaubt, wenn
    // - kein leerer Eintrag in der Selection ist
    // - kein Eintrag vom Typ Memo oder Image ist
    // - kein DROP erlaubt ist (s.o.) und die Spalte noch kein Required (not null) gesetzt hatte.
    long nIndex = FirstSelectedRow();
    OTableRow* pRow;
    while( nIndex >= 0 )
    {
        pRow = (*m_pRowList)[nIndex];
        OFieldDescription *pFieldDescr = pRow->GetActFieldDescr();
        if(!pFieldDescr)
            return sal_False;
        else
        {
            //////////////////////////////////////////////////////////////
            // Wenn Feldtyp Memo oder Image, kein PrimKey
            // oder wenn Spalten nicht gedroped werden k�nnen und das Required Flag ist nicht gesetzt
            // oder wenn eine ::com::sun::star::sdbcx::View vorhanden ist und das Required Flag nicht gesetzt ist
            const OTypeInfo* pTypeInfo = pFieldDescr->getTypeInfo();
            if( pTypeInfo->nSearchType == ColumnSearch::NONE || 
                (bDropNotAllowed && pFieldDescr->IsNullable()) ||
                (xTable.is() && ::comphelper::getString(xTable->getPropertyValue(PROPERTY_TYPE)) == ::rtl::OUString::createFromAscii("VIEW") && 
                !(!pFieldDescr->IsNullable() || pFieldDescr->IsAutoIncrement())))
                return sal_False;
        }

        nIndex = NextSelectedRow();
    }

    return sal_True;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::Command(const CommandEvent& rEvt)
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    switch (rEvt.GetCommand())
    {
        case COMMAND_CONTEXTMENU:
        {
            //////////////////////////////////////////////////////////////
            // Falls kein MouseEvent, an Basisklasse weiterleiten
            if (!rEvt.IsMouseEvent())
            {
                OTableRowView::Command(rEvt);
                return;
            }

            //////////////////////////////////////////////////////////////
            // Kontextmenu einblenden
            if( !IsReadOnly() )
            {
                sal_uInt16 nColId = GetColumnAtXPosPixel(rEvt.GetMousePosPixel().X());
                long   nRow = GetRowAtYPosPixel(rEvt.GetMousePosPixel().Y());

                if ( nColId == HANDLE_ID )
                {
                    PopupMenu aContextMenu(ModuleRes(RID_TABLEDESIGNROWPOPUPMENU));
                    long nSelectRowCount = GetSelectRowCount();
                    sal_Bool bRowsSelected(nSelectRowCount ? sal_True : sal_False);

                    aContextMenu.EnableItem( SID_CUT, IsCutAllowed(nRow) );
                    aContextMenu.EnableItem( SID_COPY, IsCopyAllowed(nRow) );
                    aContextMenu.EnableItem( SID_PASTE, IsPasteAllowed(nRow) );
                    aContextMenu.EnableItem( SID_DELETE, IsDeleteAllowed(nRow) );
                    aContextMenu.EnableItem( SID_TABLEDESIGN_TABED_PRIMARYKEY, IsPrimaryKeyAllowed(nRow) );
                    aContextMenu.EnableItem( SID_TABLEDESIGN_INSERTROWS, IsInsertNewAllowed(nRow) );
                    aContextMenu.CheckItem( SID_TABLEDESIGN_TABED_PRIMARYKEY, IsRowSelected(GetCurRow()) && IsPrimaryKey() );

                    // jetzt alles, was disabled wurde, wech
                    aContextMenu.RemoveDisabledEntries(sal_True, sal_True);

                    //////////////////////////////////////////////////////////////
                    // Alle Aktionen, die die Zeilenzahl veraendern, muessen asynchron
                    // ausgefuehrt werden->sonst Probleme zwischen Kontextmenu u. Browser
                    m_nDataPos = GetCurRow();
                    switch (aContextMenu.Execute(this, rEvt.GetMousePosPixel()))
                    {
                        case SID_CUT:
                            Cut();
                            break;
                        case SID_COPY:
                            Copy();
                            break;
                        case SID_PASTE:
                            Paste();
                            break;
                        case SID_DELETE:
                            if( nDeleteEvent )
                                Application::RemoveUserEvent( nDeleteEvent );
                            nDeleteEvent = Application::PostUserEvent( LINK(this, OTableEditorCtrl, DelayedDelete) );
                            break;
                        case SID_TABLEDESIGN_INSERTROWS:
                            if( nInsNewRowsEvent )
                                Application::RemoveUserEvent( nInsNewRowsEvent );
                            nInsNewRowsEvent = Application::PostUserEvent( LINK(this, OTableEditorCtrl, DelayedInsNewRows) );
                            break;
                        case SID_TABLEDESIGN_TABED_PRIMARYKEY:
                            SetPrimaryKey( !IsPrimaryKey() );
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        break;
        default:
            OTableRowView::Command(rEvt);
    }

}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, DelayedCut, void*, EMPTYTAG )
{
    nCutEvent = 0;
    OTableRowView::Cut();
    return 0;
}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, DelayedPaste, void*, EMPTYTAG )
{
    nPasteEvent = 0;

    // die Zeile, bei der eigefuegt werden wuerde
    sal_Int32 nPastePosition = GetSelectRowCount() ? FirstSelectedRow() : GetCurRow();

    if (!IsInsertNewAllowed(nPastePosition))
    {	// kein Einfuegen erlaubt, sondern nur anhaengen, also testen, ob hinter der PastePosition noch
        // belegte Zeilen erscheinen

        sal_Int32 nFreeFromPos;	// ab da nur freie Zeilen
        ::std::vector<OTableRow*>::reverse_iterator aIter = m_pRowList->rbegin();
        for(nFreeFromPos = m_pRowList->size();
            aIter != m_pRowList->rend() && (!(*aIter) || !(*aIter)->GetActFieldDescr() || !(*aIter)->GetActFieldDescr()->GetName().getLength());
            --nFreeFromPos, ++aIter)
            ;
        if (nPastePosition < nFreeFromPos)	// es gibt mindestens eine belegte hinter PastePosition -> ganz nach hinten
            nPastePosition = nFreeFromPos;
    }

    OTableRowView::Paste( nPastePosition );
    SetNoSelection();
    GoToRow( nPastePosition );

    return 0;
}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, DelayedDelete, void*, EMPTYTAG )
{
    nDeleteEvent = 0;
    DeleteRows();
    return 0;
}

//------------------------------------------------------------------------------
IMPL_LINK( OTableEditorCtrl, DelayedInsNewRows, void*, EMPTYTAG )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    nInsNewRowsEvent = 0;
    InsertNewRows( GetSelectRowCount() ? FirstSelectedRow() : m_nDataPos );
    SetNoSelection();
    GoToRow( m_nDataPos );

    return 0;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::SetPrimaryKey( sal_Bool bSet )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Evtl. vorhandene Primary Keys loeschen
    MultiSelection aDeletedPrimKeys;
    aDeletedPrimKeys.SetTotalRange( Range(0,GetRowCount()) );
    long nIndex = 0;

    ::std::vector<OTableRow*>::const_iterator aIter = m_pRowList->begin();
    for(;aIter != m_pRowList->end();++aIter)
    {
        OFieldDescription *pFieldDescr = (*aIter)->GetActFieldDescr();
        if( pFieldDescr && (*aIter)->IsPrimaryKey() )
        {
            (*aIter)->SetPrimaryKey( sal_False );
            if(!bSet && pFieldDescr->getTypeInfo()->bNullable)
            {
                pFieldDescr->SetIsNullable(ColumnValue::NO_NULLS);
                pFieldDescr->SetDefaultValue(String());
                //////////////////////////////////////////////////////////////////////
                // Die Fielddesription updaten
                pDescrWin->DisplayData(pFieldDescr);
            }

            nIndex = m_pRowList->end() - aIter;
            aDeletedPrimKeys.Insert( nIndex );
            aDeletedPrimKeys.Select( nIndex );
        }
    }

    //////////////////////////////////////////////////////////////////////
    // Die Primary Keys der markierten Zeilen setzen
    MultiSelection aInsertedPrimKeys;
    aInsertedPrimKeys.SetTotalRange( Range(0,GetRowCount()) );
    if( bSet )
    {
        nIndex = FirstSelectedRow();
        while( nIndex >= 0 )
        {
            //////////////////////////////////////////////////////////////////////
            // Key setzen
            OTableRow* pRow = (*m_pRowList)[nIndex];
            OFieldDescription *pFieldDescr = pRow->GetActFieldDescr();
            if(pFieldDescr)
            {
                pRow->SetPrimaryKey( sal_True );

                if(pFieldDescr->getTypeInfo()->bNullable)
                {
                    pFieldDescr->SetIsNullable(ColumnValue::NO_NULLS);
                    pFieldDescr->SetDefaultValue(String());
                    //////////////////////////////////////////////////////////////////////
                    // Die Fielddesription updateten
                    pDescrWin->DisplayData(pFieldDescr);
                }

                aInsertedPrimKeys.Insert( nIndex );
                aInsertedPrimKeys.Select( nIndex );
            }

            nIndex = NextSelectedRow();
        }
    }

    GetUndoManager()->AddUndoAction( new OPrimKeyUndoAct(this, aDeletedPrimKeys, aInsertedPrimKeys) );

    //////////////////////////////////////////////////////////////////////
    // Handle-Spalte invalidieren
    InvalidateHandleColumn();


    //////////////////////////////////////////////////////////////////////
    // Das ModifyFlag der TableDocSh setzen
    GetView()->getController()->setModified( sal_True );
    GetView()->getController()->InvalidateFeature(SID_SAVEDOC);
    GetView()->getController()->InvalidateFeature(SID_UNDO);
    GetView()->getController()->InvalidateFeature(SID_REDO);
}

//------------------------------------------------------------------------------
sal_Bool OTableEditorCtrl::IsPrimaryKey()
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Gehoeren alle markierten Felder zu einem Primary Key ?
    long nPrimaryKeys = 0;
    ::std::vector<OTableRow*>::const_iterator aIter = m_pRowList->begin();
    for(sal_Int32 nRow=0;aIter != m_pRowList->end();++aIter,++nRow)
    {
        if( IsRowSelected(nRow) && !(*aIter)->IsPrimaryKey() )
            return sal_False;
        if( (*aIter)->IsPrimaryKey() )
            nPrimaryKeys++;
    }

    //////////////////////////////////////////////////////////////////////
    // Gibt es unselektierte Felder, die noch zu dem Key gehoeren ?
    return GetSelectRowCount() == nPrimaryKeys;
}

//------------------------------------------------------------------------------
void OTableEditorCtrl::SwitchType( const OTypeInfo* _pType )
{
    DBG_CHKTHIS(OTableEditorCtrl,NULL);
    //////////////////////////////////////////////////////////////////////
    // Wenn noch kein Feldname vergeben wurde
    long nRow(GetCurRow());
    OFieldDescription* pActFieldDescr = GetFieldDescr( nRow );
    if( pActFieldDescr )
        //////////////////////////////////////////////////////////////////////
        // Alte Beschreibung speichern
        pDescrWin->SaveData( pActFieldDescr );

    //////////////////////////////////////////////////////////////////////
    // Neue Beschreibung darstellen
    OTableRow* pRow = (*m_pRowList)[nRow];
    pRow->SetFieldType( _pType, sal_True );
    if(_pType)
    {
        sal_uInt16 nCurrentlySelected = pTypeCell->GetSelectEntryPos();
        OTableController* pController = GetView()->getController();

        if ((LISTBOX_ENTRY_NOTFOUND == nCurrentlySelected) || (pController->getTypeInfo(nCurrentlySelected) != _pType))
        {
            USHORT nEntryPos = 0;
            const OTypeInfoMap* pTypeInfo = GetView()->getController()->getTypeInfo();
            OTypeInfoMap::const_iterator aIter = pTypeInfo->begin();
            for(;aIter != pTypeInfo->end();++aIter,++nEntryPos)
            {
                if(aIter->second == _pType)
                    break;
            }
            if (nEntryPos < pTypeCell->GetEntryCount())
                pTypeCell->SelectEntryPos( nEntryPos );
        }
    }

    pActFieldDescr = pRow->GetActFieldDescr();
    if (pActFieldDescr != NULL && !pActFieldDescr->GetFormatKey())
    {
        sal_Int32 nFormatKey = ::dbtools::getDefaultNumberFormat( pActFieldDescr->GetType(),
            pActFieldDescr->GetScale(),
            pActFieldDescr->IsCurrency(),
            Reference< XNumberFormatTypes>(GetView()->getController()->getNumberFormatter()->getNumberFormatsSupplier()->getNumberFormats(),UNO_QUERY),
            GetView()->getLocale());

        pActFieldDescr->SetFormatKey(nFormatKey);
    }

    pDescrWin->DisplayData( pActFieldDescr );
}
// -----------------------------------------------------------------------------
OTableDesignView* OTableEditorCtrl::GetView() const
{
    return static_cast<OTableDesignView*>(GetParent()->GetParent());
}
// -----------------------------------------------------------------------------
void OTableEditorCtrl::DeactivateCell(sal_Bool bUpdate)
{
    OTableRowView::DeactivateCell(bUpdate);
    // now we have to deactivate the field description
    long nRow(GetCurRow());
    sal_uInt16 nCol(GetCurColumnId());
    if (pDescrWin)
        pDescrWin->SetReadOnly(bReadOnly || !SetDataPtr(nRow) || GetActRow()->IsReadOnly());
}
//------------------------------------------------------------------------------
long OTableEditorCtrl::PreNotify( NotifyEvent& rNEvt )
{
    if (rNEvt.GetType() == EVENT_GETFOCUS)
    {
        if( pDescrCell && pDescrCell->HasChildPathFocus() )
            m_eChildFocus = DESCRIPTION;
        else if(pNameCell && pNameCell->HasChildPathFocus() )
            m_eChildFocus = NAME;
        else
            m_eChildFocus = ROW;
    }
        
    return OTableRowView::PreNotify(rNEvt);
}
// -----------------------------------------------------------------------------




