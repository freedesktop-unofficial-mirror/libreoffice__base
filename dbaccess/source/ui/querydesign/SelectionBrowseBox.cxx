/*************************************************************************
 *
 *  $RCSfile: SelectionBrowseBox.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: oj $ $Date: 2001-02-14 14:54:11 $
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
#ifndef DBAUI_QUERYDESIGN_OSELECTIONBROWSEBOX_HXX
#include "SelectionBrowseBox.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef DBAUI_QUERYDESIGNVIEW_HXX
#include "QueryDesignView.hxx"
#endif
#ifndef DBAUI_QUERYCONTROLLER_HXX
#include "querycontroller.hxx"
#endif
#ifndef DBAUI_QUERYTABLEVIEW_HXX
#include "QueryTableView.hxx"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef DBAUI_TABLEFIELDINFO_HXX
#include "TableFieldInfo.hxx"
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#include "dbaccess_helpid.hrc"
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _SV_SYSTEM_HXX
#include <vcl/system.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef DBAUI_QUERY_TABLEWINDOW_HXX
#include "QTableWindow.hxx"
#endif
#ifndef DBAUI_QUERYTABLEVIEW_HXX
#include "QueryTableView.hxx"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _SV_DRAG_HXX
#include <vcl/drag.hxx>
#endif
#ifndef __SGI_STL_ROPE
#include <rope>
#endif
#ifndef DBAUI_QUERYDESIGNFIELDUNDOACT_HXX
#include "QueryDesignFieldUndoAct.hxx"
#endif
#ifndef _SV_EXCHANGE_HXX
#include <vcl/exchange.hxx>
#endif
#ifndef _SVX_DBEXCH_HRC
#include <svx/dbexch.hrc>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef _CPPUHELPER_EXTRACT_HXX_
#include <cppuhelper/extract.hxx>
#endif


using namespace ::dbaui;
using namespace ::connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;

const String g_strOne = String::CreateFromAscii("1");
const String g_strZero = String::CreateFromAscii("0");

#define DEFAULT_QUERY_COLS	20
#define DEFAULT_SIZE	GetTextWidth(g_strZero) * 30
#define CHECKBOX_SIZE	10
#define HANDLE_ID	0
#define REGISTERID() (Exchange::RegisterFormatName( String::CreateFromAscii(SBA_JOIN_EXCHANGE_FORMAT) ))

DBG_NAME(OSelectionBrowseBox);
//------------------------------------------------------------------------------
OSelectionBrowseBox::OSelectionBrowseBox( Window* pParent )
                   :DbBrowseBox( pParent,DBBF_NOROWPICTURE, WB_3DLOOK, BROWSER_COLUMNSELECTION | BROWSER_HIDESELECT | BROWSER_KEEPSELECTION |
                                  BROWSER_HIDECURSOR | BROWSER_HLINESFULL | BROWSER_VLINESFULL)
                   ,m_nVisibleCount(0)
                   ,m_aFunctionStrings(ModuleRes(STR_QUERY_FUNCTIONS))
                   ,m_bOrderByUnRelated(sal_True)
                   ,m_bGroupByUnRelated(sal_True)
{
    DBG_CTOR(OSelectionBrowseBox,NULL);
    SetHelpId(HID_CTL_QRYDGNCRIT);

    m_nMode = BROWSER_COLUMNSELECTION | BROWSER_HIDESELECT | BROWSER_KEEPSELECTION | BROWSER_HIDECURSOR | BROWSER_HLINESFULL | BROWSER_VLINESFULL;

    m_pTextCell		= new Edit(&GetDataWindow());
    //	m_pTextCell->EnableSpecialCheck(sal_False);
    m_pVisibleCell	= new DbCheckBoxCtrl(&GetDataWindow());
    m_pTableCell	= new DbListBoxCtrl(&GetDataWindow());
    m_pFieldCell	= new DbComboBoxCtrl(&GetDataWindow());
    m_pOrderCell	= new DbListBoxCtrl(&GetDataWindow());
    m_pFunctionCell	= new DbListBoxCtrl(&GetDataWindow());

    m_pVisibleCell->SetHelpId(HID_QRYDGN_ROW_VISIBLE);
    m_pTableCell->SetHelpId(HID_QRYDGN_ROW_TABLE);
    m_pFieldCell->SetHelpId(HID_QRYDGN_ROW_FIELD);
    m_pOrderCell->SetHelpId(HID_QRYDGN_ROW_ORDER);
    m_pFunctionCell->SetHelpId(HID_QRYDGN_ROW_FUNCTION);

    //////////////////////////////////////////////////////////////////////
    // TriState der ::com::sun::star::form::CheckBox abschalten
    m_pVisibleCell->GetBox().EnableTriState( sal_False );

    Font aTitleFont = System::GetStandardFont(STDFONT_SWISS);
    aTitleFont.SetSize(Size(0, 6));
    SetTitleFont(aTitleFont);

    String aTxt(ModuleRes(STR_QUERY_SORTTEXT));
    xub_StrLen nCount = aTxt.GetTokenCount();
    xub_StrLen nIdx = 0;
    for (; nIdx < nCount; nIdx++)
        m_pOrderCell->InsertEntry(aTxt.GetToken(nIdx));

    for(long i=0;i < BROW_ROW_CNT;i++)
        m_bVisibleRow.push_back(sal_True);

    m_bVisibleRow[BROW_FUNCTION_ROW] = sal_False;   // zuerst ausblenden
}

//------------------------------------------------------------------------------
OSelectionBrowseBox::~OSelectionBrowseBox()
{
    DBG_DTOR(OSelectionBrowseBox,NULL);
    
    delete m_pTextCell;
    delete m_pVisibleCell;
    delete m_pFieldCell;
    delete m_pTableCell;
    delete m_pOrderCell;
    delete m_pFunctionCell;
}
// -----------------------------------------------------------------------------
void OSelectionBrowseBox::initialize()
{
    Reference< XDatabaseMetaData >  xMetaData = getDesignView()->getController()->getConnection()->getMetaData();
    // Diese Funktionen stehen nur unter CORE zur Verf�gung
    if(xMetaData->supportsCoreSQLGrammar())
    {
        xub_StrLen nCount	= m_aFunctionStrings.GetTokenCount();
        for (xub_StrLen nIdx = 0; nIdx < nCount; nIdx++)
            m_pFunctionCell->InsertEntry(m_aFunctionStrings.GetToken(nIdx));
    }
    else // sonst nur COUNT(*)
    {
        m_pFunctionCell->InsertEntry(m_aFunctionStrings.GetToken(0));
        m_pFunctionCell->InsertEntry(m_aFunctionStrings.GetToken(2)); // 2 -> COUNT
    }

    m_bOrderByUnRelated = xMetaData->supportsOrderByUnrelated();
    m_bGroupByUnRelated = xMetaData->supportsGroupByUnrelated();

    Init();
}
//==============================================================================
OQueryDesignView* OSelectionBrowseBox::getDesignView()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OSL_ENSURE(static_cast<const OQueryDesignView*>(GetParent()),"Parent isn't an OQueryDesignView!");
    return static_cast<OQueryDesignView*>(GetParent());
}
// -----------------------------------------------------------------------------
OQueryDesignView* OSelectionBrowseBox::getDesignView() const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OSL_ENSURE(static_cast<const OQueryDesignView*>(GetParent()),"Parent isn't an OQueryDesignView!");
    return static_cast<OQueryDesignView*>(GetParent());
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::Init()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DbBrowseBox::Init();

    SetMapMode( MapMode(MAP_TWIP) );
    GetDataWindow().SetMapMode( GetMapMode() );

    Font	aFont( GetDataWindow().GetFont() );
    aFont.SetWeight( WEIGHT_NORMAL );
    GetDataWindow().SetFont( aFont );

    //xxx richtige Zeilenhoehe fuer EditEng ???
    long nLSize = GetDataWindow().GetTextHeight() + 4;
    SetDataRowHeight(nLSize);

    EnableDrop();
    SetTitleLines(1);
    // Anzahl der sichtbaren Zeilen ermitteln
    for(long i=0;i<BROW_ROW_CNT;i++)
    {
        if(m_bVisibleRow[i])
            m_nVisibleCount++;
    }
    RowInserted(0, m_nVisibleCount, sal_False);
    Reference< XDatabaseMetaData >  xMetaData = getDesignView()->getController()->getConnection()->getMetaData();

    m_nMaxColumns = xMetaData->getMaxColumnsInSelect();
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::ClearAll()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    SetUpdateMode(sal_False);

    if (GetCurRow() != 0)
        GoToRow(0);

    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    for(;aIter != getDesignView()->getController()->getTableFieldDesc()->end();++aIter)
        delete *aIter;
    getDesignView()->getController()->getTableFieldDesc()->clear();

    sal_uInt16 nCurCol	= GetCurColumnId();
    long nCurRow		= GetCurRow();
    DeactivateCell();

    RemoveColumns();
    InsertHandleColumn( 70 );
    SetUpdateMode(sal_True);


#if defined (OS2)
    Invalidate();
#endif

}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetReadOnly(sal_Bool bRO)
{
    if (bRO)
    {
        DeactivateCell();
        m_nMode &= ~BROWSER_HIDECURSOR;
        SetMode(m_nMode);
    }
    else
    {
        m_nMode |= BROWSER_HIDECURSOR;
        SetMode(m_nMode);
        ActivateCell();
    }
}

//------------------------------------------------------------------------------
DbCellController* OSelectionBrowseBox::GetController(long nRow, sal_uInt16 nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    DBG_ASSERT(pEntry, "OSelectionBrowseBox::GetController : keine FieldDescription !");

    if (!pEntry)
        return NULL;

    if (getDesignView()->getController()->isReadOnly())
        return NULL;

    long nCellIndex = GetRealRow(nRow);
    switch (nCellIndex)
    {
        case BROW_FIELD_ROW:
            return new DbComboBoxCellController(m_pFieldCell);
        case BROW_TABLE_ROW:
            return new DbListBoxCellController(m_pTableCell);
        case BROW_VIS_ROW:
            return new DbCheckBoxCellController(m_pVisibleCell);
        case BROW_ORDER_ROW:
            return new DbListBoxCellController(m_pOrderCell);
        case BROW_FUNCTION_ROW:
            return new DbListBoxCellController(m_pFunctionCell);
        default:
            return new DbEditCellController(m_pTextCell);
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::InitController(DbCellControllerRef& rController, long nRow, sal_uInt16 nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OSL_ENSURE(getDesignView()->getController()->getTableFieldDesc()->size() > (nColId-1),"ColID is to great!");
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    DBG_ASSERT(pEntry, "OSelectionBrowseBox::InitController : keine FieldDescription !");
    long nCellIndex = GetRealRow(nRow);

    switch (nCellIndex)
    {
        case BROW_FIELD_ROW:
        {
            m_pFieldCell->Clear();
            m_pFieldCell->SetText(String());

            String aField(pEntry->GetField());
            String aTable(pEntry->GetAlias());

            getDesignView()->fillValidFields(aTable, m_pFieldCell);

            // * durch alias.* ersetzen
            if ((aField.GetChar(0) == '*') && aTable.Len())
            {
                aField = aTable;
                aField.AppendAscii(".*");
            }
            m_pFieldCell->SetText(aField);
        }	break;
        case BROW_TABLE_ROW:
        {
            m_pTableCell->Clear();
            if(pEntry->GetFunctionType() != FKT_CONDITION)
            {
                m_pTableCell->Enable();
                m_pTableCell->EnableInput(sal_True);
                OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                if (pTabWinList)
                {
                    OJoinTableView::OTableWindowMap::iterator aIter = pTabWinList->begin();
                    for(;aIter != pTabWinList->end();++aIter)
                        m_pTableCell->InsertEntry(static_cast<OQueryTableWindow*>(aIter->second)->GetAliasName());

                    m_pTableCell->InsertEntry(String(ModuleRes(STR_QUERY_NOTABLE)), 0);
                    if (pEntry->GetAlias().getLength())
                        m_pTableCell->SelectEntry(pEntry->GetAlias());
                    else
                        m_pTableCell->SelectEntry(String(ModuleRes(STR_QUERY_NOTABLE)));
                }
            }
            else
            {
                m_pTableCell->Disable();
                m_pTableCell->EnableInput(sal_False);
            }


        }	break;
        case BROW_VIS_ROW:
        {
            m_pVisibleCell->GetBox().Check(pEntry->IsVisible());
            m_pVisibleCell->GetBox().SaveValue();

            if(pEntry->GetFunctionType() == FKT_CONDITION)
            {
                m_pTextCell->Disable();
                m_pTextCell->EnableInput(sal_False);
            }
            else
            {
                m_pTextCell->Enable();
                m_pTextCell->EnableInput(sal_True);
            }

            if(!pEntry->IsVisible() && pEntry->GetOrderDir() != ORDER_NONE && !m_bOrderByUnRelated)
            {
                // Spalte muss sichtbar sein, um im ORDER BY aufzutauchen
                pEntry->SetVisible(sal_True);
                m_pVisibleCell->GetBox().Check(pEntry->IsVisible());
                m_pVisibleCell->GetBox().SaveValue();
                m_pVisibleCell->GetBox().Disable();
                m_pVisibleCell->GetBox().EnableInput(sal_False);
                String aMessage(ModuleRes(STR_QRY_ORDERBY_UNRELATED));
                OQueryDesignView* paDView = getDesignView();
                InfoBox(paDView, aMessage).Execute();
            }
        }	break;
        case BROW_ORDER_ROW:
        {
            m_pOrderCell->SelectEntryPos(pEntry->GetOrderDir());
            if(pEntry->GetFunctionType() == FKT_CONDITION)
            {
                m_pOrderCell->Disable();
                m_pOrderCell->EnableInput(sal_False);
            }
            else
            {
                m_pOrderCell->Enable();
                m_pOrderCell->EnableInput(sal_True);
            }
        }	break;
        case BROW_COLUMNALIAS_ROW:
            {

                m_pTextCell->SetText(pEntry->GetFieldAlias());
                m_pTextCell->ClearModifyFlag();
                if (!m_pTextCell->HasFocus())
                    m_pTextCell->GrabFocus();

                if(pEntry->GetFunctionType() == FKT_CONDITION)
                {
                    m_pTextCell->Disable();
                    m_pTextCell->EnableInput(sal_False);
                }
                else
                {
                    m_pTextCell->Enable();
                    m_pTextCell->EnableInput(sal_True);
                }
                if (m_pTextCell->GetHelpId() != HID_QRYDGN_ROW_ALIAS)
                    // da TextCell in verschiedenen Kontexten verwendet wird, muss ich den gecachten HelpText loeschen
                    m_pTextCell->SetHelpText(String());
                m_pTextCell->SetHelpId(HID_QRYDGN_ROW_ALIAS);
            }
            break;
        case BROW_FUNCTION_ROW:
        {
            Reference< XDatabaseMetaData >  xMetaData = getDesignView()->getController()->getConnection()->getMetaData();
            // Diese Funktionen stehen nur unter CORE zur Verf�gung
            if(xMetaData->supportsCoreSQLGrammar())
            {
                if(pEntry->IsGroupBy())
                {
                    m_pFunctionCell->SelectEntry(m_pFunctionCell->GetEntry(m_pFunctionCell->GetEntryCount()-1));
                }
                else if(m_pFunctionCell->GetEntryPos(String(pEntry->GetFunction())) != COMBOBOX_ENTRY_NOTFOUND)
                    m_pFunctionCell->SelectEntry(String(pEntry->GetFunction()));
                else
                    m_pFunctionCell->SelectEntryPos(0);

                if(pEntry->GetFunctionType() == FKT_CONDITION)
                {
                    m_pFunctionCell->Disable();
                    m_pFunctionCell->EnableInput(sal_False);
                }
                else
                {
                    m_pFunctionCell->Enable();
                    m_pFunctionCell->EnableInput(sal_True);
                }
            }
            else
            {
                // nur COUNT(*) erlaubt
                if(pEntry->GetField().getLength() && pEntry->GetField().toChar() != '*')
                    m_pFunctionCell->RemoveEntry(1);
                else if(m_pFunctionCell->GetEntryCount() < 2)
                    m_pFunctionCell->InsertEntry(m_aFunctionStrings.GetToken(2)); // 2 -> COUNT
                if(m_pFunctionCell->GetEntryPos(String(pEntry->GetFunction())) != COMBOBOX_ENTRY_NOTFOUND)
                    m_pFunctionCell->SelectEntry(pEntry->GetFunction());
                else
                    m_pFunctionCell->SelectEntryPos(0);
            }
        }
            break;
        default:
        {
            sal_uInt16	nIdx = nCellIndex-BROW_CRIT1_ROW;
            String	aText( pEntry->GetCriteria( nIdx ) );

            m_pTextCell->SetText(aText);
            m_pTextCell->ClearModifyFlag();
            if (!m_pTextCell->HasFocus())
                m_pTextCell->GrabFocus();

            if(pEntry->GetFunctionType() == FKT_CONDITION)
            {
                m_pTextCell->Disable();
                m_pTextCell->EnableInput(sal_False);
            }
            else
            {
                m_pTextCell->Enable();
                m_pTextCell->EnableInput(sal_True);
            }
            if (m_pTextCell->GetHelpId() != HID_QRYDGN_ROW_CRIT)
                // da TextCell in verschiedenen Kontexten verwendet wird, muss ich den gecachten HelpText loeschen
                m_pTextCell->SetHelpText(String());
            m_pTextCell->SetHelpId(HID_QRYDGN_ROW_CRIT);
        }
    }
    Controller()->ClearModified();
}

//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::SaveModified()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OTableFieldDesc* pEntry = NULL;
    if(getDesignView()->getController()->getTableFieldDesc()->size() > GetCurColumnId() - 1)
        pEntry = (*getDesignView()->getController()->getTableFieldDesc())[GetCurColumnId() - 1];

    sal_Bool bWasEmpty = pEntry ? pEntry->IsEmpty() : sal_False;
    sal_Bool bError = sal_False;

    if (pEntry && Controller().Is() && Controller()->IsModified())
    {
        // fuer die Undo-Action
        String strOldCellContents;
        long nRow = GetRealRow(GetCurRow());
        switch (nRow)
        {
            case BROW_VIS_ROW:
                if((m_bOrderByUnRelated || pEntry->GetOrderDir() == ORDER_NONE) && 
                   (m_bGroupByUnRelated || !pEntry->IsGroupBy()))
                {
                    strOldCellContents = pEntry->IsVisible() ? g_strOne : g_strZero;
                    pEntry->SetVisible(m_pVisibleCell->GetBox().IsChecked());
                }
                else
                {
                    strOldCellContents = pEntry->IsVisible() ? g_strOne : g_strZero;
                    pEntry->SetVisible(sal_True);
                    m_pVisibleCell->GetBox().Check();
                }
                break;

            case BROW_FIELD_ROW:
            {
                String aFieldName(m_pFieldCell->GetText());
                
                sal_Bool bIsPredicate = sal_False;
                // wenn das Ergebnis ein Praedikat -> OK
                String aTest(aFieldName);

                OQueryTableWindow* pWin = static_cast<OQueryTableWindow*>(pEntry->GetTabWindow());

                if (!pWin && (aFieldName.GetTokenCount('.') == 2))
                {
                    OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                    if (pTabWinList)
                    {
                        OJoinTableView::OTableWindowMapIterator aIter = pTabWinList->find(aFieldName.GetToken(0, '.'));
                        if(aIter != pTabWinList->end())
                            pWin = static_cast<OQueryTableWindow*>(aIter->second);
                    }
                }

                Reference<XPropertySet> xColumn;
                if (pWin)
                {
                    Reference<XNameAccess> xColumns = pWin->GetOriginalColumns();
                    if (aFieldName.GetTokenCount('.') == 2 && xColumns->hasByName(aFieldName.GetToken(1,'.')))	// falls alias.Feld angegeben
                        ::cppu::extractInterface(xColumn,xColumns->getByName(aFieldName.GetToken(1,'.')));
                    else if(xColumns->hasByName(aFieldName))
                        ::cppu::extractInterface(xColumn,xColumns->getByName(aFieldName));
                }

                if(!xColumn.is()) // only when text not a column of the table
                {
                    ::rtl::OUString aErrorMsg;
                    bIsPredicate = sal_True; // #72670#
                    ::connectivity::OSQLParser* pParser = getDesignView()->getController()->getParser();
                    OSQLParseNode* pParseNode = pParser->predicateTree(aErrorMsg, aTest, 
                                                                        getDesignView()->getController()->getNumberFormatter(), 
                                                                        xColumn);
                    if (pParseNode)
                    {
                        pEntry->SetVisible(sal_False);
                        bWasEmpty = sal_False; // XXXXX
                        delete pParseNode;
                        pEntry->SetFunctionType(FKT_CONDITION);
                        RowModified(GetBrowseRow(BROW_VIS_ROW), GetCurColumnId());
                    }
                    else
                        pEntry->SetFunctionType(FKT_OTHER);
                }

                xub_StrLen nCount(aFieldName.GetTokenCount('('));
                if(nCount < 2 && !bIsPredicate) // keine Funktion
                {
                    if (aFieldName.GetTokenCount('.') == 2)	// falls alias.Feld angegeben
                    {
                        String sTableAlias(aFieldName.GetToken(0, '.'));
                        aFieldName = aFieldName.GetToken(1,'.');

                        // das erste Token in das Tabellenfeld eintragen (und entsprechend den Entry anpassen)
                        pEntry->SetAlias(sTableAlias);
                        if(m_bVisibleRow[BROW_TABLE_ROW])
                            RowModified(GetBrowseRow(BROW_TABLE_ROW), GetCurColumnId());

                        OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                        if (pTabWinList)
                        {
                            OJoinTableView::OTableWindowMapIterator aIter = pTabWinList->find(sTableAlias);
                            if(aIter != pTabWinList->end())
                            {
                                OQueryTableWindow* pEntryTab = static_cast<OQueryTableWindow*>(aIter->second);
                                if (pEntryTab)
                                {
                                    pEntry->SetDatabase(pEntryTab->GetComposedName());
                                    pEntry->SetTable(pEntryTab->GetTableName());
                                }
                            }
                        }
                    }
                    strOldCellContents = pEntry->GetField();
                    pEntry->SetField(aFieldName);

                    // Falls nur COUNT(*) erlaubt wird
                    Reference< XDatabaseMetaData >  xMetaData = getDesignView()->getController()->getConnection()->getMetaData();
                    if(xMetaData->supportsCoreSQLGrammar()
                        && aFieldName.GetChar(0) != '*' && pEntry->GetFunction().getLength())
                    {
                        pEntry->SetFunction(::rtl::OUString());
                        m_pFunctionCell->SelectEntryPos(0);
                        if(!m_bVisibleRow[BROW_FUNCTION_ROW])
                        {
                            SetRowVisible(BROW_FUNCTION_ROW, sal_True);
                        }
                        RowModified(GetBrowseRow(BROW_FUNCTION_ROW), GetCurColumnId());
                    }
                    pEntry->SetFunctionType(FKT_NONE);
                }
                else
                {	// Funktion eingegeben
                    // m_pFieldCell auf Inhalt der Funktion setzen und pEntry mit ganzem Wert setzen
                    // BROW_FUNCTION_ROW setzen
                    strOldCellContents = pEntry->GetField();

                    String aFkt(aFieldName.GetToken(0,'('));

                    if(pEntry->GetFunctionType() != FKT_CONDITION && GetFunktionName(aFkt))
                    {
                        // ist Aggregatefuntkion
                        pEntry->SetFunction(aFkt);
                        String aParameter(aFieldName.GetToken(1,'('));
                        aParameter = aParameter.GetToken(aParameter.GetTokenCount()-1,')');
                        pEntry->SetField(aParameter); // nur die Parameter einf"ugen
                        pEntry->SetFunctionType(FKT_AGGREGATE);
                        if (aParameter.GetTokenCount('.') == 2)	// falls alias.Feld angegeben
                        {
                            String sTableAlias(aParameter.GetToken(0, '.'));
                            aParameter = aParameter.GetToken(1,'.');

                            // das erste Token in das Tabellenfeld eintragen (und entsprechend den Entry anpassen)
                            pEntry->SetAlias(sTableAlias);
                            if(m_bVisibleRow[BROW_TABLE_ROW])
                                RowModified(GetBrowseRow(BROW_TABLE_ROW), GetCurColumnId());

                            OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                            if (pTabWinList)
                            {
                                OJoinTableView::OTableWindowMapIterator aIter = pTabWinList->find(sTableAlias);
                                if(aIter != pTabWinList->end())
                                {
                                    OQueryTableWindow* pEntryTab = static_cast<OQueryTableWindow*>(aIter->second);
                                    pEntry->SetDatabase(pEntryTab->GetComposedName());
                                    pEntry->SetTable(pEntryTab->GetTableName());
                                }
                            }
                        }
                        else
                        {
                            // nur eine Tabelle vorhanden oder der Benutzer hat vergessen diese anzugeben
                            // also einfach die erst beste nehmen
                            OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                            if(pTabWinList)
                            {
                                OQueryTableWindow* pEntryTab = static_cast<OQueryTableWindow*>(pTabWinList->begin()->second);
                                if (pEntryTab)
                                {
                                    pEntry->SetDatabase(pEntryTab->GetComposedName());
                                    pEntry->SetTable(pEntryTab->GetTableName());
                                    pEntry->SetAlias(pEntry->GetTable());
                                }
                            }
                        }

                        m_pFieldCell->SetText(aParameter);
                        m_pFunctionCell->SelectEntry(aFkt);
                        if(!m_bVisibleRow[BROW_FUNCTION_ROW])
                        {
                            SetRowVisible(BROW_FUNCTION_ROW, sal_True);
                        }
                        RowModified(GetBrowseRow(BROW_FUNCTION_ROW), GetCurColumnId());
                        RowModified(GetBrowseRow(BROW_TABLE_ROW), GetCurColumnId());
                    }
                    else
                    {
                        pEntry->SetField(aFieldName);
                        pEntry->SetAlias(String());
                        pEntry->SetTable(String());
                        pEntry->SetTabWindow(NULL);
                        m_pFieldCell->SetText(aFieldName);
                        m_pFunctionCell->SelectEntryPos(0);
                        if(m_bVisibleRow[BROW_TABLE_ROW])
                            RowModified(GetBrowseRow(BROW_TABLE_ROW), GetCurColumnId());
                    }
                }

                if (!aFieldName.Len())
                {
                    ::std::replace(getDesignView()->getController()->getTableFieldDesc()->begin(),getDesignView()->getController()->getTableFieldDesc()->end(),pEntry,new OTableFieldDesc);
                    sal_uInt16 nCol = GetCurColumnId();
                    for (int i = 0; i < m_nVisibleCount; i++)	// Spalte neu zeichnen
                        RowModified(i,nCol);
                }
                getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_EXECUTE );
            }
            break;

            case BROW_TABLE_ROW:
            {
                String aAliasName = m_pTableCell->GetSelectEntry();
                strOldCellContents = pEntry->GetAlias();
                if (m_pTableCell->GetSelectEntryPos() != 0)
                    pEntry->SetAlias(aAliasName);
                else
                    pEntry->SetAlias(String());

                // jetzt noch ::com::sun::star::data::Database und Tabelle uebernehmen
                OJoinTableView::OTableWindowMap* pTabWinList = getDesignView()->getTableView()->GetTabWinMap();
                if (pTabWinList)
                {
                    OJoinTableView::OTableWindowMapIterator aIter = pTabWinList->find(aAliasName);
                    if(aIter != pTabWinList->end())
                    {
                        OQueryTableWindow* pEntryTab = static_cast<OQueryTableWindow*>(aIter->second);
                        if (pEntryTab)
                        {
                            pEntry->SetDatabase(pEntryTab->GetComposedName());
                            pEntry->SetTable(pEntryTab->GetTableName());
                        }
                    }
                }
            }	break;

            case BROW_ORDER_ROW:
            {
                strOldCellContents = String((sal_uInt16)pEntry->GetOrderDir());
                sal_uInt16 nIdx = m_pOrderCell->GetSelectEntryPos();
                if (nIdx == sal_uInt16(-1))
                    nIdx = 0;
                pEntry->SetOrderDir(EOrderDir(nIdx));
                if(!m_bOrderByUnRelated)
                {
                    pEntry->SetVisible(sal_True);
                    m_pVisibleCell->GetBox().Check();
                    RowModified(GetBrowseRow(BROW_VIS_ROW), GetCurColumnId());
                }
            }	break;

            case BROW_COLUMNALIAS_ROW:
                strOldCellContents = pEntry->GetFieldAlias();
                pEntry->SetFieldAlias(m_pTextCell->GetText());
                break;
            case BROW_FUNCTION_ROW:
                {
                    strOldCellContents = pEntry->GetFunction();
                    sal_uInt16 nPos = m_pFunctionCell->GetSelectEntryPos();
                    Reference< XDatabaseMetaData >  xMetaData = getDesignView()->getController()->getConnection()->getMetaData();
                    // Diese Funktionen stehen nur unter CORE zur Verf�gung
                    sal_uInt16 nFunctionCount =
                                        xMetaData->supportsCoreSQLGrammar()
                                                            ?
                                        m_pFunctionCell->GetEntryCount()-1
                                                            :
                                        m_pFunctionCell->GetEntryCount();
                    if(nPos >= 1 && nPos < nFunctionCount)
                    {
                        pEntry->SetFunctionType(FKT_AGGREGATE);
                        pEntry->SetFunction(m_pFunctionCell->GetEntry(nPos));
                        pEntry->SetGroupBy(sal_False);
                    }
                    else
                    {
                        pEntry->SetFunctionType(FKT_NONE);
                        if(nPos > 1)
                        {
                            pEntry->SetGroupBy(sal_True);
                            if(!m_bGroupByUnRelated)
                            {
                                pEntry->SetVisible(sal_True);
                                m_pVisibleCell->GetBox().Check();
                                RowModified(GetBrowseRow(BROW_VIS_ROW), GetCurColumnId());
                            }
                        }
                        else
                            pEntry->SetGroupBy(sal_False);
                        pEntry->SetFunction(String());
                    }
                }
                break;
            default:
            {

                sal_uInt16	nIdx = nRow - BROW_CRIT1_ROW;
                String aText = m_pTextCell->GetText();

                aText.EraseLeadingChars();
                ::rtl::OUString aCrit;
                if(aText.Len())
                {
                    ::connectivity::OSQLParser* pParser = getDesignView()->getController()->getParser();
                    OQueryTableWindow* pWin = static_cast<OQueryTableWindow*>(pEntry->GetTabWindow());
                    
                    String aTest(aText);
                    
                    Reference<XPropertySet> xColumn;
                    if (pWin)
                    {
                        Reference<XNameAccess> xColumns = pWin->GetOriginalColumns();
                        if (xColumns->hasByName(pEntry->GetField()))	
                            ::cppu::extractInterface(xColumn,xColumns->getByName(pEntry->GetField()));
                    }

                    ::rtl::OUString aErrorMsg;
                    OSQLParseNode* pParseNode = pParser->predicateTree(aErrorMsg, aTest, getDesignView()->getController()->getNumberFormatter(), xColumn);
                    if (pParseNode)
                    {
                        pParseNode->parseNodeToPredicateStr(aCrit,
                                                            getDesignView()->getController()->getConnection()->getMetaData(),
                                                            getDesignView()->getController()->getNumberFormatter(), 
                                                            xColumn,
                                                            getDesignView()->getLocale(),
                                                            getDesignView()->getDecimalSeparator().toChar(),
                                                            &(getDesignView()->getController()->getParser()->getContext()));
                        delete pParseNode;
                    }
                    else
                    {				   
                        if(xColumn.is())
                        {
                            sal_Int32 nType = 0;
                            xColumn->getPropertyValue(PROPERTY_TYPE) >>= nType;
                            switch(nType)
                            {
                                case DataType::CHAR:
                                case DataType::VARCHAR:
                                case DataType::LONGVARCHAR:
                                    if(aTest.GetChar(0) != '\'' || aTest.GetChar(aTest.Len() -1) != '\'')
                                    {
                                        aTest.SearchAndReplaceAll(String::CreateFromAscii("'"),String::CreateFromAscii("''"));
                                        String aTmp(String::CreateFromAscii("'"));
                                        (aTmp += aTest) += String::CreateFromAscii("'");
                                        aTest = aTmp;
                                    }
                                    break;
                                default:
                                    ;
                            }
                            pParseNode = pParser->predicateTree(aErrorMsg, aTest, getDesignView()->getController()->getNumberFormatter(), xColumn);
                            if (pParseNode)
                            {
                                pParseNode->parseNodeToPredicateStr(aCrit, 
                                                                    getDesignView()->getController()->getConnection()->getMetaData(),
                                                                    getDesignView()->getController()->getNumberFormatter(), 
                                                                    xColumn, 
                                                                    getDesignView()->getLocale(),
                                                                    getDesignView()->getDecimalSeparator().toChar(),
                                                                    &(getDesignView()->getController()->getParser()->getContext()));
                                delete pParseNode;
                            }
                            else
                            {
                                //	SbaExtInfoBox(this,aErrorMsg).Execute();
                                // TODO show error
                                bError = sal_True;
                            }
                        }
                        else
                        {
                            //	SbaExtInfoBox(this,aErrorMsg).Execute();
                            // TODO show error
                            bError = sal_True;
                        }
                    }
                }
                strOldCellContents = pEntry->GetCriteria(nIdx);
                pEntry->SetCriteria(nIdx, aCrit);
                if(aCrit.getLength() && nRow >= (GetRowCount()-1))
                {
                    RowInserted( GetRowCount()-1, 1, TRUE );
                    m_bVisibleRow.push_back(sal_True);
                    ++m_nVisibleCount;
                }
            }
        }
        if(!bError && Controller())
            Controller()->ClearModified();

        RowModified(GetCurRow(), GetCurColumnId());

        // und noch die Undo-Action fuer das Ganze
        OTabFieldCellModifiedUndoAct* pUndoAct = new OTabFieldCellModifiedUndoAct(this);
        pUndoAct->SetCellIndex(GetCurRow());
        pUndoAct->SetColId(GetCurColumnId());
        pUndoAct->SetCellContents(strOldCellContents);
        getDesignView()->getController()->getUndoMgr()->AddUndoAction(pUndoAct);
    }

    // habe ich Daten in einer FieldDescription gespeichert, die vorher leer war und es nach den Aenderungen nicht mehr ist ?
    if (pEntry && bWasEmpty && !pEntry->IsEmpty() && !bError)
    {
        // Default auf sichtbar
        pEntry->SetVisible(sal_True);
        RowModified(BROW_VIS_ROW, GetCurColumnId());

        // wenn noetig neue freie Spalten anlegen
        long nDummy;
        CheckFreeColumns(nDummy);
    }

    return pEntry != NULL && !bError;
}

//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::SeekRow(long nRow)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    sal_Bool bRet = sal_False;

    m_nSeekRow = nRow;
    if (nRow < m_nVisibleCount )
        bRet = sal_True;

    return bRet;
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::PaintCell(OutputDevice& rDev, const Rectangle& rRect, sal_uInt16 nColumnId) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    rDev.SetClipRegion( rRect );
    OTableFieldDesc* pEntry = NULL;
    
    if(getDesignView()->getController()->getTableFieldDesc()->size() > nColumnId - 1)
        pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColumnId - 1];

    if (!pEntry)
        return;

    long nRow = GetRealRow(m_nSeekRow);
    if (nRow == BROW_VIS_ROW)
        PaintTristate(rDev, rRect, pEntry->IsVisible() ? STATE_CHECK : STATE_NOCHECK);
    else
        rDev.DrawText(rRect.TopLeft(), GetCellText(nRow, nColumnId));

    rDev.SetClipRegion( );
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::PaintStatusCell(OutputDevice& rDev, const Rectangle& rRect) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    Point	aPos(rRect.TopLeft());
    aPos.Y() -= 2;
    String	aLabel(ModuleRes(STR_QUERY_HANDLETEXT));

    // ab BROW_CRIT2_ROW werden alle Zeilen mit "oder" angegeben
    xub_StrLen nToken = (sal_uInt16) (m_nSeekRow >= GetBrowseRow(BROW_CRIT2_ROW))
                                ?
            BROW_CRIT2_ROW : GetRealRow(m_nSeekRow);
    rDev.DrawText(aPos, aLabel.GetToken(nToken));
}

//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::QueryDrop(const BrowserDropEvent& rEvt)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    return rEvt.GetColumnId() > 0 && rEvt.GetRow() >= 0 && DragServer::HasFormat(0, REGISTERID());
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::RemoveColumn(sal_uInt16 nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(getDesignView()->getController()->getTableFieldDesc()->size() == ColCount() - 1, "OSelectionBrowseBox::RemoveColumn : inkonsistent state !");
        // das Control sollte immer genau eine Spalte mehr haben, naemlich die HandleColumn
    DBG_ASSERT((nColId == 0) || (nColId <= getDesignView()->getController()->getTableFieldDesc()->size()), "OSelectionBrowseBox::RemoveColumn : invalid parameter nColId");
        // ColId ist bei mir gleichbedeutend mit Position, und da sollte die Bedingung natuerlich zutreffen

    sal_uInt16 nCurCol = GetCurColumnId();
    long nCurRow = GetCurRow();

    DeactivateCell();
    // Spalteninfo rausnehmen und am Ende neues Info einfuegen
    OTableFieldDesc* pOld = (*getDesignView()->getController()->getTableFieldDesc())[((sal_uInt32)nColId - 1)];
    getDesignView()->getController()->getTableFieldDesc()->erase( getDesignView()->getController()->getTableFieldDesc()->begin() + ((sal_uInt32)nColId - 1) );
        // der Aufrufer ist dafuer verantwortlich, sich vorher die Description zu besorgen und die irgendwie aufzuraeumen
        // (im Normalfall wohl erst mal in ein Undo zu schieben)
    OTableFieldDesc* pNew = new OTableFieldDesc;
    getDesignView()->getController()->getTableFieldDesc()->push_back(pNew);

    // Nachfolgende Spalten optisch verschieben
    sal_uInt16 nCount = (sal_uInt16)ColCount();
        // (das funktioniert nur, weil hier Column-Id gleich Column-Pos ist)
    for (sal_uInt16 i = nColId; i < nCount; i++)
        SetColumnWidth(i, GetColumnWidth(i + 1));

    // letzte Spalte erhaelt den default Wert
    SetColumnWidth(nCount-1, DEFAULT_SIZE);
    pNew->SetColWidth(DEFAULT_SIZE);

    // Neuzeichnen
    Rectangle aInvalidRect = GetInvalidRect( nColId );
    Invalidate( aInvalidRect );

    ActivateCell( nCurRow, nCurCol );

    getDesignView()->getController()->setModified();

    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_UNDO );
    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_REDO );
    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_EXECUTE );

}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::RemoveField(sal_uInt16 nId, sal_Bool bActivate)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OSL_ENSURE(getDesignView()->getController()->getTableFieldDesc()->size() > (nId-1),"ID is to great!");

    OTableFieldDesc* pDesc = (*getDesignView()->getController()->getTableFieldDesc())[(sal_uInt32)(nId - 1)] ;
    pDesc->SetColWidth( (sal_uInt16)GetColumnWidth(nId) );	// hat er sich vorher leider nicht gemerkt

    // UndoAction erzeugen
    OTabFieldDelUndoAct* pUndoAction = new OTabFieldDelUndoAct( this );
    pUndoAction->SetTabFieldDescr(pDesc);
    pUndoAction->SetOwnership(sal_True);
    pUndoAction->SetColId( nId );
    getDesignView()->getController()->getUndoMgr()->AddUndoAction( pUndoAction );

    RemoveColumn(nId);

    // damit das Ganze potentiell unendlich ist, zieht ein Remove auch gleich ein Insert einer leeren Spalte nach sich
//	AppendNewCol(1);

    getDesignView()->getController()->InvalidateFeature(ID_BROWSER_UNDO);
    getDesignView()->getController()->InvalidateFeature(ID_BROWSER_REDO);
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::MouseButtonDown(const BrowserMouseEvent& rEvt)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    if( rEvt.IsLeft() )
    {
        sal_Bool bOnHeader = rEvt.GetRow() < 0 && rEvt.GetColumnId() != HANDLE_ID;
        // wenn ein Header selectiert wird, mu� die selection angezeigt werden, sonst nicht)
        if (bOnHeader)
        {
            if (GetSelectColumnCount() == 0)
                // wenn es schon eine selektierte Spalte gibt, bin ich schon im richtigen Modus
                if ((m_nMode & BROWSER_HIDESELECT) == BROWSER_HIDESELECT)
                {
                    m_nMode &= ~BROWSER_HIDESELECT;
                    m_nMode |= BROWSER_MULTISELECTION;
                    SetMode(m_nMode);
                }
        }
        else if (!((m_nMode & BROWSER_HIDESELECT) == BROWSER_HIDESELECT))
        {
            if (GetSelectColumnCount() != 0)
                SetNoSelection();
            if (rEvt.GetColumnId() == HANDLE_ID)
            {
                m_nMode |= BROWSER_HIDESELECT;
                m_nMode &= ~BROWSER_MULTISELECTION;
                SetMode(m_nMode);
            }
        }
    }
    DbBrowseBox::MouseButtonDown(rEvt);
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::MouseButtonUp(const BrowserMouseEvent& rEvt)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DbBrowseBox::MouseButtonUp( rEvt );
    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_EXECUTE );
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::KeyInput( const KeyEvent& rEvt )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    if (IsColumnSelected(GetCurColumnId()))
    {
        if (rEvt.GetKeyCode().GetCode() == KEY_DELETE &&	// Delete rows
            !rEvt.GetKeyCode().IsShift() &&
            !rEvt.GetKeyCode().IsMod1())
        {
            RemoveField(GetCurColumnId());
            return;
        }
    }
    DbBrowseBox::KeyInput(rEvt);
}


//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::Drop( const BrowserDropEvent& rEvt )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OTableFieldDesc aInfo;
    if (DragServer::HasFormat(0,REGISTERID()))
    {
        // Einfuegen des Feldes an der gewuenschten Position
        SvDataObjectRef xDataObj = SvDataObject::PasteDragServer(rEvt);
        OJoinExchObj* xJoinExchObj = (OJoinExchObj*)&xDataObj;
        OJoinExchangeData jxdSource = xJoinExchObj->GetSourceDescription();
        InsertField(jxdSource);
    }
    return sal_False;
}

//------------------------------------------------------------------------------
OTableFieldDesc* OSelectionBrowseBox::AppendNewCol( sal_uInt16 nCnt )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    // es koennen mehrere angelegt werden, aber der Erste
    // wird returnt
    sal_uInt32 nCount = getDesignView()->getController()->getTableFieldDesc()->size();
    OTableFieldDesc* pNewDesc;
    for (sal_uInt16 i=0 ; i<nCnt ; i++)
    {
        pNewDesc = new OTableFieldDesc;
        pNewDesc->SetColWidth(DEFAULT_SIZE);
        getDesignView()->getController()->getTableFieldDesc()->push_back(pNewDesc);
        InsertDataColumn((sal_uInt16)getDesignView()->getController()->getTableFieldDesc()->size(), String(), DEFAULT_SIZE, HIB_STDSTYLE, HEADERBAR_APPEND);
    }

    return (*getDesignView()->getController()->getTableFieldDesc())[nCount];
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::DeleteFields(const String& rAliasName)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    if (getDesignView()->getController()->getTableFieldDesc()->size())
    {
        sal_uInt16 nColId = GetCurColumnId();
        sal_uInt32 nRow = GetCurRow();

        sal_Bool bWasEditing = IsEditing();
        if (bWasEditing)
            DeactivateCell();

        ::std::vector<OTableFieldDesc*>::reverse_iterator aIter = getDesignView()->getController()->getTableFieldDesc()->rbegin();
        OTableFieldDesc* pEntry = NULL;
        for(sal_Int32 nPos=getDesignView()->getController()->getTableFieldDesc()->size();aIter != getDesignView()->getController()->getTableFieldDesc()->rend();++aIter,--nPos)
        {
            pEntry = *aIter;
            if (pEntry->GetAlias() == ::rtl::OUString(rAliasName) )
                RemoveField((sal_uInt16)nPos, sal_False);
        }

        if (bWasEditing)
            ActivateCell(nRow , nColId);
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetColWidth()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    // Spaltenbreite ermitteln
    sal_uInt16 nColCount = ColCount();
    sal_uInt32 nColWidth = 0;

    for( sal_uInt16 nColId=1; nColId<=nColCount; nColId++ )
    {
        nColWidth = getDesignView()->getController()->getColWidth( nColId );

        if( nColWidth == 0)
            nColWidth = DEFAULT_SIZE;
        SetColumnWidth( nColId, nColWidth );
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetColWidth(sal_uInt16 nColId, long nNewWidth)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    sal_Bool bWasEditing = IsEditing();
    if (bWasEditing)
        DeactivateCell();

    // die Basisklasse machen lassen
    SetColumnWidth(nColId, nNewWidth);

    // der FieldDescription Bescheid sagen
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId - 1];
    if (pEntry)
        pEntry->SetColWidth(GetColumnWidth(nColId));

    if (bWasEditing)
        ActivateCell(GetCurRow(), GetCurColumnId());
}

//------------------------------------------------------------------------------
Rectangle OSelectionBrowseBox::GetInvalidRect( sal_uInt16 nColId )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    //////////////////////////////////////////////////////////////////////
    // Rechteck ist erst einmal der gesamte Outputbereich des Fensters
    Rectangle aInvalidRect( Point(0,0), GetOutputSizePixel() );

    //////////////////////////////////////////////////////////////////////
    // Dann wird die linke Seite angepasst
    Rectangle aFieldRect(GetCellRect( 0, nColId ));	// used instead of GetFieldRectPixel
    aInvalidRect.Left() = aFieldRect.Left();

    return aInvalidRect;
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::InsertColumn(OTableFieldDesc* pEntry, long& nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(getDesignView()->getController()->getTableFieldDesc()->size() == ColCount() - 1, "OSelectionBrowseBox::InsertColumn : inkonsistent state !");
        // das Control sollte immer genau eine Spalte mehr haben, naemlich die HandleColumn
    DBG_ASSERT((nColId == -1) || (nColId <= getDesignView()->getController()->getTableFieldDesc()->size()), "OSelectionBrowseBox::InsertColumn : invalid parameter nColId.");
        // -1 heisst ganz hinten, Count heisst ganz hinten, der Rest bezeichnet eine richtige Position

    sal_uInt16 nCurCol = GetCurColumnId();
    long nCurRow = GetCurRow();

    DeactivateCell();

    // Gueltigkeit von nColId pruefen (ColId von 1 bis ...)
    // Wenn zu klein oder zu gross, auf Ende der Liste setzen
    if ((nColId == -1) || (nColId >= getDesignView()->getController()->getTableFieldDesc()->size()))	 // Anhaengen des Feldes
    {
        if (FindFirstFreeCol(nColId) == NULL)	// keine freie Column mehr
        {
            AppendNewCol(1);
            nColId = getDesignView()->getController()->getTableFieldDesc()->size();
        }
        else
            nColId++; // innerhalb der vorgegebenen Liste
    }

    // in Liste der Spaltenbeschreibungen neues Element
    getDesignView()->getController()->getTableFieldDesc()->insert( getDesignView()->getController()->getTableFieldDesc()->begin()+(sal_uInt32)nColId-1 ,pEntry);
    // da ich meine Spaltenzahl immer auf dem selben Wert wie die Zahl der FieldDescriptions halten muss (plus 1, da es eine
    // HandleClumn gibt), muss ich fuer diese gerade eingefuegte Description auch eine loeschen
    long nFirstFreeCol = -1;
    CheckFreeColumns(nFirstFreeCol);
        // (es kann sein, dass es keine leere gab, dann erzwingt CheckFreeColumns das)

    delete (*getDesignView()->getController()->getTableFieldDesc())[(sal_uInt16)nFirstFreeCol];
    getDesignView()->getController()->getTableFieldDesc()->erase(getDesignView()->getController()->getTableFieldDesc()->begin()+(sal_uInt16)nFirstFreeCol);

    // jetzt kann wieder keine leere Spalte vorhanden sein (falls naemlich die soeben geloeschte die einzige war) ...
    CheckFreeColumns(nFirstFreeCol);

    // Nachfolgende Spalten optisch verschieben
    sal_uInt16 nCount = (sal_uInt16)getDesignView()->getController()->getTableFieldDesc()->size();
    for (sal_uInt16 i = nCount-1; i > nColId; --i)
        SetColumnWidth(i, GetColumnWidth(i - 1));

    // Spaltenbreite setzen
    SetColumnWidth((sal_uInt16)nColId, pEntry->GetColWidth() );

    // Neuzeichnen
    Rectangle aInvalidRect = GetInvalidRect( (sal_uInt16)nColId );
    Invalidate( aInvalidRect );

    ActivateCell( nCurRow, nCurCol );
    getDesignView()->getController()->setModified();

    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_UNDO );
    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_REDO );
    getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_EXECUTE );
}

//------------------------------------------------------------------------------
OTableFieldDesc* OSelectionBrowseBox::InsertField(const OJoinExchangeData& jxdSource, long nColId, sal_Bool bVis, sal_Bool bActivate)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OQueryTableWindow* pSourceWin = static_cast<OQueryTableWindow*>(jxdSource.pListBox->GetTabWin());
    if (!pSourceWin)
        return NULL;

    // Namen/Position des selektierten Feldes
    String aFieldName = jxdSource.pListBox->GetEntryText(jxdSource.pEntry);
    sal_uInt32 nFieldIndex = jxdSource.pListBox->GetModel()->GetAbsPos(jxdSource.pEntry);
    OTableFieldInfo* pInf = static_cast<OTableFieldInfo*>(jxdSource.pEntry->GetUserData());

    // eine DragInfo aufbauen, damit ich mich auf das andere InsertField zurueckziehen kann
    OTableFieldDesc aInfo;
    aInfo.SetTabWindow(pSourceWin);
    aInfo.SetFieldIndex(nFieldIndex);
    aInfo.SetFieldType(pInf->GetKeyType());
    aInfo.SetField(aFieldName);
    aInfo.SetTable(pSourceWin->GetTableName());
    aInfo.SetAlias(pSourceWin->GetAliasName());
    aInfo.SetDatabase(pSourceWin->GetComposedName());

    aInfo.SetDataType(pInf->GetDataType());
    aInfo.SetVisible(bVis);

    return InsertField(aInfo, nColId, bVis, bActivate);
}

//------------------------------------------------------------------------------
OTableFieldDesc* OSelectionBrowseBox::InsertField(const OTableFieldDesc& rInfo, long nColId, sal_Bool bVis, sal_Bool bActivate)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);

    if(m_nMaxColumns && m_nMaxColumns <= FieldsCount())
        return NULL;
    if (bActivate)
        SaveModified();

    // Neue Spaltenbeschreibung
    OTableFieldDesc* pEntry = new OTableFieldDesc(rInfo);
    pEntry->SetVisible(bVis);
    sal_uInt32 nColWidth;
    if( getDesignView()->getColWidth(rInfo.GetAlias(), rInfo.GetField(), nColWidth) )
        pEntry->SetColWidth( (sal_uInt16)nColWidth );
    else
        pEntry->SetColWidth( (sal_uInt16)DEFAULT_SIZE );

    // Spalte einfuegen
    InsertColumn( pEntry, nColId );

    // UndoAction erzeugen
    OTabFieldCreateUndoAct* pUndoAction = new OTabFieldCreateUndoAct( this );
    pUndoAction->SetTabFieldDescr( pEntry );
    pUndoAction->SetOwnership(sal_False);
    pUndoAction->SetColId( nColId );
    getDesignView()->getController()->getUndoMgr()->AddUndoAction( pUndoAction );

    return pEntry;
}

//------------------------------------------------------------------------------
sal_uInt16 OSelectionBrowseBox::FieldsCount()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    sal_uInt16 nCount = 0;

    while (aIter != getDesignView()->getController()->getTableFieldDesc()->end())
    {
        if ((*aIter) && !(*aIter)->IsEmpty())
            nCount++;
        ++aIter;
    }

    return nCount;
}

//------------------------------------------------------------------------------
OTableFieldDesc* OSelectionBrowseBox::FindFirstFreeCol( long& rCol )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    rCol = -1;
    while (aIter != getDesignView()->getController()->getTableFieldDesc()->end())
    {
        ++rCol;
        if ((*aIter) && (*aIter)->IsEmpty())
            return *aIter;
        ++aIter;
    }

    return NULL;
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::CheckFreeColumns(long& rCol)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    if (FindFirstFreeCol(rCol) == NULL)
    {
        // es ist voll, also einen Packen Spalten anhaengen
        AppendNewCol(DEFAULT_QUERY_COLS);
        OSL_VERIFY(FindFirstFreeCol(rCol));
    }
}
//------------------------------------------------------------------------------
void OSelectionBrowseBox::AddGroupBy( const OTableFieldDesc& rInfo )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(!rInfo.IsEmpty(),"AddGroupBy:: OTableFieldDesc sollte nicht Empty sein!");
    OTableFieldDesc* pEntry;
    ::comphelper::UStringMixEqual bCase(getDesignView()->getController()->getConnection()->getMetaData()->storesMixedCaseQuotedIdentifiers());
    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    for(;aIter != getDesignView()->getController()->getTableFieldDesc()->end();++aIter)
    {
        pEntry = *aIter;
        OSL_ENSURE(pEntry,"OTableFieldDesc was null!");

        ::rtl::OUString	aField = pEntry->GetField();
        ::rtl::OUString	aAlias = pEntry->GetAlias();

        if (bCase(aField,rInfo.GetField()) && 
            bCase(aAlias,rInfo.GetAlias()) && 
            pEntry->GetFunctionType() == rInfo.GetFunctionType())
        {
            if((pEntry->GetFunctionType() == FKT_AGGREGATE && rInfo.IsGroupBy()))
                pEntry->SetGroupBy(sal_False);
            else
            {
                pEntry->SetGroupBy(rInfo.IsGroupBy());
                if(!m_bOrderByUnRelated && pEntry->IsGroupBy())
                    pEntry->SetVisible(sal_True);
            }
            break;
        }
    }

    if (aIter == getDesignView()->getController()->getTableFieldDesc()->end())
    {
        OTableFieldDesc* pTmp = InsertField(rInfo, -1, sal_False, sal_False );
        if((pTmp->GetFunctionType() == FKT_AGGREGATE && rInfo.IsGroupBy())) // das GroupBy wird bereits von rInfo "ubernommen
            pTmp->SetGroupBy(sal_False);
    }
}
//------------------------------------------------------------------------------
void OSelectionBrowseBox::AddCondition( const OTableFieldDesc& rInfo, const String& rValue, const sal_uInt16 nLevel, const char* pOp )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(!rInfo.IsEmpty(),"AddCondition:: OTableFieldDesc sollte nicht Empty sein!");
    OTableFieldDesc* pEntry;
    ::comphelper::UStringMixEqual bCase(getDesignView()->getController()->getConnection()->getMetaData()->storesMixedCaseQuotedIdentifiers());

    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    for(;aIter != getDesignView()->getController()->getTableFieldDesc()->end();++aIter)
    {
        pEntry = *aIter;
        ::rtl::OUString	aField = pEntry->GetField();
        ::rtl::OUString	aAlias = pEntry->GetAlias();

        if (bCase(aField,rInfo.GetField()) && 
            bCase(aAlias,rInfo.GetAlias()) && 
            pEntry->GetFunctionType() == rInfo.GetFunctionType())
        {
            if((pEntry->GetFunctionType() == FKT_AGGREGATE && rInfo.IsGroupBy()))
                pEntry->SetGroupBy(sal_False);
            else
            {
                pEntry->SetGroupBy(rInfo.IsGroupBy());
                if(!m_bOrderByUnRelated && pEntry->IsGroupBy())
                    pEntry->SetVisible(sal_True);
            }
            if (!pEntry->GetCriteria(nLevel).getLength())
            {
                pEntry->SetCriteria( nLevel, rValue);
                if(nLevel == (m_nVisibleCount-BROW_CRIT1_ROW-1))
                {
                    RowInserted( GetRowCount()-1, 1, TRUE );
                    m_bVisibleRow.push_back(sal_True);
                    ++m_nVisibleCount;
                }
                break;
            }
        }
    }

    if (aIter == getDesignView()->getController()->getTableFieldDesc()->end())
    {
        OTableFieldDesc* pTmp = InsertField(rInfo, -1, sal_False, sal_False );
        if((pTmp->GetFunctionType() == FKT_AGGREGATE && rInfo.IsGroupBy())) // das GroupBy wird bereits von rInfo "ubernommen
            pTmp->SetGroupBy(sal_False);
        if(pTmp)
        {
            pTmp->SetCriteria( nLevel, rValue);
            if(nLevel == (m_nVisibleCount-BROW_CRIT1_ROW-1))
            {
                RowInserted( GetRowCount()-1, 1, TRUE );
                m_bVisibleRow.push_back(sal_True);
                ++m_nVisibleCount;
            }
        }
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::AddOrder( const OTableFieldDesc& rInfo, const EOrderDir eDir, sal_uInt16& nPos )
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(!rInfo.IsEmpty(),"AddOrder:: OTableFieldDesc sollte nicht Empty sein!");
    // nPos merkt sich die Spalte in die Sortierung eingetragen wird,
    // da weitere Sortierungen nur dahinter abgelegt werden duerfen
    OTableFieldDesc* pEntry;
    ::comphelper::UStringMixEqual bCase(getDesignView()->getController()->getConnection()->getMetaData()->storesMixedCaseQuotedIdentifiers());

    ::std::vector<OTableFieldDesc*>::iterator aIter = getDesignView()->getController()->getTableFieldDesc()->begin();
    for(;aIter != getDesignView()->getController()->getTableFieldDesc()->end();++aIter)
    {
        pEntry = *aIter;
        ::rtl::OUString	aField = pEntry->GetField();
        ::rtl::OUString	aAlias = pEntry->GetAlias();

        if (bCase(aField,rInfo.GetField()) && 
            bCase(aAlias,rInfo.GetAlias()))
        {
            if(!m_bOrderByUnRelated)
                pEntry->SetVisible(sal_True);
            pEntry->SetOrderDir( eDir );
            nPos = getDesignView()->getController()->getTableFieldDesc()->end() - aIter;
            break;
        }
    }

    if (aIter == getDesignView()->getController()->getTableFieldDesc()->end())
    {
        OTableFieldDesc* pTmp = InsertField(rInfo, -1, sal_False, sal_False );
        if(pTmp)
        {
            if(!m_bOrderByUnRelated)
                pEntry->SetVisible(sal_True);
            pTmp->SetOrderDir( eDir );
        }

        nPos = (sal_uInt16)( getDesignView()->getController()->getTableFieldDesc()->size()-1 );
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::ArrangeControls(sal_uInt16& nX, sal_uInt16 nY)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DbBrowseBox::ArrangeControls(nX, nY);
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::Save()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    if (IsModified())
        SaveModified();
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::CellModified()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    long nRow = GetRealRow(GetCurRow());
    switch (nRow)
    {
        case BROW_VIS_ROW:
            {
                OTableFieldDesc*	pEntry = (*getDesignView()->getController()->getTableFieldDesc())[GetCurColumnId() - 1];
                sal_uInt16 nIdx = m_pOrderCell->GetSelectEntryPos();
                if(!m_bOrderByUnRelated && nIdx > 0 && nIdx != sal_uInt16(-1))
                {
                    m_pVisibleCell->GetBox().Check();
                    pEntry->SetVisible(sal_True);
                }
                else
                    pEntry->SetVisible(m_pVisibleCell->GetBox().IsChecked());
            }
            break;
    }
    getDesignView()->getController()->setModified();
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::Fill()
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(ColCount() >= 1, "OSelectionBrowseBox::Fill : please call only after inserting the handle column !");

    sal_uInt16 nColCount = ColCount() - 1;
    if (nColCount < DEFAULT_QUERY_COLS)
        AppendNewCol(DEFAULT_QUERY_COLS - nColCount);
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::Command(const CommandEvent& rEvt)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    switch (rEvt.GetCommand())
    {
        case COMMAND_CONTEXTMENU:
        {
            if (!rEvt.IsMouseEvent())
            {
                DbBrowseBox::Command(rEvt);
                return;
            }

            Point aPoint(rEvt.GetMousePosPixel());
            sal_uInt16 nColId = GetColumnAtXPosPixel(rEvt.GetMousePosPixel().X());
            long   nRow = GetRowAtYPosPixel(rEvt.GetMousePosPixel().Y());

            if (nRow < 0 && nColId > HANDLE_ID && IsColumnSelected(nColId) )
            {
                if (!getDesignView()->getController()->isReadOnly())
                {
                    PopupMenu aContextMenu(ModuleRes(RID_QUERYCOLPOPUPMENU));
                    switch (aContextMenu.Execute(this, aPoint))
                    {
                        case SID_DELETE:				// Aussch
                            RemoveField(nColId);
                            break;
                    }
                }
            }
            else if(nRow >= 0 && nColId <= HANDLE_ID)
            {
                if (!getDesignView()->getController()->isReadOnly())
                {
                    PopupMenu aContextMenu(ModuleRes(RID_QUERYFUNCTION_POPUPMENU));
                    aContextMenu.CheckItem( ID_QUERY_FUNCTION, m_bVisibleRow[BROW_FUNCTION_ROW]);
                    aContextMenu.CheckItem( ID_QUERY_TABLENAME, m_bVisibleRow[BROW_TABLE_ROW]);
                    aContextMenu.CheckItem( ID_QUERY_ALIASNAME, m_bVisibleRow[BROW_COLUMNALIAS_ROW]);
                    aContextMenu.CheckItem( ID_QUERY_DISTINCT, getDesignView()->getController()->isDistinct());

                    switch (aContextMenu.Execute(this, aPoint))
                    {
                        case ID_QUERY_FUNCTION:
                            SetRowVisible(BROW_FUNCTION_ROW, !IsRowVisible(BROW_FUNCTION_ROW));
                            getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_VIEW_FUNCTIONS );
                            break;
                        case ID_QUERY_TABLENAME:
                            SetRowVisible(BROW_TABLE_ROW, !IsRowVisible(BROW_TABLE_ROW));
                            getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_VIEW_TABLES );
                            break;
                        case ID_QUERY_ALIASNAME:
                            SetRowVisible(BROW_COLUMNALIAS_ROW, !IsRowVisible(BROW_COLUMNALIAS_ROW));
                            getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_VIEW_ALIASES );
                            break;
                        case ID_QUERY_DISTINCT:
                            getDesignView()->getController()->setDistinct(!getDesignView()->getController()->isDistinct());
                            getDesignView()->getController()->setModified();
                            getDesignView()->getController()->InvalidateFeature( ID_BROWSER_QUERY_DISTINCT_VALUES );
                            break;
                    }

                    getDesignView()->getController()->setModified();
                }
            }
            else
            {
                DbBrowseBox::Command(rEvt);
                return;
            }
        }
        default:
            DbBrowseBox::Command(rEvt);
    }
}

//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::IsRowVisible(sal_uInt16 _nWhich) const
{
    DBG_ASSERT(_nWhich>=0 && _nWhich<(m_bVisibleRow.size()), "OSelectionBrowseBox::IsRowVisible : invalid parameter !");
    return m_bVisibleRow[_nWhich];
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetRowVisible(sal_uInt16 _nWhich, sal_Bool _bVis)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(_nWhich>=0 && _nWhich<m_bVisibleRow.size(), "OSelectionBrowseBox::SetRowVisible : invalid parameter !");

    sal_Bool bWasEditing = IsEditing();
    if (bWasEditing)
        DeactivateCell();

    // do this before removing or inserting rows, as this triggers ActivateCell-calls, which rely on m_bVisibleRow
    m_bVisibleRow[_nWhich] = !m_bVisibleRow[_nWhich];

    long nId = GetBrowseRow(_nWhich);
    if (_bVis)
    {
        RowInserted(nId,1);
        m_nVisibleCount++;
    }
    else
    {
        RowRemoved(nId,1);
        m_nVisibleCount--;
    }

    if (bWasEditing)
        ActivateCell();
}

//------------------------------------------------------------------------------
long OSelectionBrowseBox::GetBrowseRow(long nRowId) const
{
    long nCount(0);
    for(long i=0;i<nRowId;i++)
    {
        if(m_bVisibleRow[i])
            nCount++;
    }
    return nCount;
}
//------------------------------------------------------------------------------
long OSelectionBrowseBox::GetRealRow(long nRowId) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    long nErg=0,i;
    for(i=0;i < m_bVisibleRow.size(); i++)
    {
        if(m_bVisibleRow[i])
        {
            if(nErg++ == nRowId)
                break;
        }
    }
    DBG_ASSERT(nErg <= m_bVisibleRow.size(),"nErg kann nicht groesser als BROW_ROW_CNT sein!");
    return i;
}
static long nVisibleRowMask[] =
                    {
                            0x0001,
                            0x0002,
                            0x0004,
                            0x0008,
                            0x0010,
                            0x0020,
                            0x0040,
                            0x0080,
                            0x0100,
                            0x0200,
                            0x0400,
                            0x0800
                    };
//------------------------------------------------------------------------------
sal_Int32 OSelectionBrowseBox::GetNoneVisibleRows() const
{
    sal_Int32 nErg(0);
    // only the foirst 11 row are interesting
    sal_Int32 nSize = sizeof(nVisibleRowMask) / sizeof(nVisibleRowMask[0]);
    for(sal_Int32 i=0;i<nSize;i++)
    {
        if(!m_bVisibleRow[i])
            nErg |= nVisibleRowMask[i];
    }
    return nErg;
}
//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetNoneVisbleRow(long nRows)
{
    // only the foirst 11 row are interesting
    sal_Int32 nSize = sizeof(nVisibleRowMask) / sizeof(nVisibleRowMask[0]);
    for(sal_Int32 i=0;i< nSize;i++)
        m_bVisibleRow[i] = !(nRows & nVisibleRowMask[i]);
}
//------------------------------------------------------------------------------
String OSelectionBrowseBox::GetCellText(long nRow, sal_uInt16 nColId) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    DBG_ASSERT(pEntry != NULL, "OSelectionBrowseBox::GetCellText : invalid column id, prepare for GPF ... ");
    if(pEntry->IsEmpty())
        return String();
    //if (!pEntry)
    //	return String();

    String aText;
    switch (nRow)
    {
        case BROW_TABLE_ROW:
            aText = pEntry->GetAlias();
            break;
        case BROW_FIELD_ROW:
        {
            String aField = pEntry->GetField();
            if (aField.GetChar(0) == '*')					// * durch alias.* ersetzen
            {
                aField = pEntry->GetAlias();
                aField += '.';
                aField += '*';
            }
            aText = aField;
        }	break;
        case BROW_ORDER_ROW:
            if (pEntry->GetOrderDir() != ORDER_NONE)
                aText = String(ModuleRes(STR_QUERY_SORTTEXT) ).GetToken(pEntry->GetOrderDir());
            break;
        case BROW_VIS_ROW:
            break;
        case BROW_COLUMNALIAS_ROW:
            aText = pEntry->GetFieldAlias();
            break;
        case BROW_FUNCTION_ROW:
            if(pEntry->GetFunctionType() == FKT_AGGREGATE)
                aText = pEntry->GetFunction();
            else if(pEntry->IsGroupBy())
                aText = m_aFunctionStrings.GetToken(m_aFunctionStrings.GetTokenCount()-1);
            break;
        default:
            aText = pEntry->GetCriteria(nRow - BROW_CRIT1_ROW);
    }
    return aText;
}
//------------------------------------------------------------------------------
sal_Bool OSelectionBrowseBox::GetFunktionName(String& rFkt)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    sal_Bool bErg=sal_True;
    String aText;

    if(rFkt.EqualsIgnoreCaseAscii("AVG"))
       rFkt = m_pFunctionCell->GetEntry(1);
    else if(rFkt.EqualsIgnoreCaseAscii("COUNT"))
       rFkt = m_pFunctionCell->GetEntry(2);
    else if(rFkt.EqualsIgnoreCaseAscii("MAX"))
       rFkt = m_pFunctionCell->GetEntry(3);
    else if(rFkt.EqualsIgnoreCaseAscii("MIN"))
       rFkt = m_pFunctionCell->GetEntry(4);
    else if(rFkt.EqualsIgnoreCaseAscii("SUM"))
       rFkt = m_pFunctionCell->GetEntry(5);
    else
    {
        xub_StrLen nCount = m_aFunctionStrings.GetTokenCount();
        for (xub_StrLen i = 0; i < nCount-1; i++) // Gruppierung wird nicht mit gez"ahlt
        {
            if(rFkt.EqualsIgnoreCaseAscii(m_aFunctionStrings.GetToken(i)))
            {
                rFkt = m_aFunctionStrings.GetToken(i);
                break;
            }
        }
        if(i == nCount-1)
            bErg = sal_False;
    }
    return bErg;
}
//------------------------------------------------------------------------------
String OSelectionBrowseBox::GetCellContents(sal_uInt16 nCellIndex, long nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(nCellIndex <	(GetRowCount()-1),"CellIndex ist zu gross");
    SaveModified();

    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId - 1];
    DBG_ASSERT(pEntry != NULL, "OSelectionBrowseBox::GetCellContents : invalid column id, prepare for GPF ... ");


    long nRow = GetRealRow(nCellIndex);
    switch (nRow)
    {
        case BROW_VIS_ROW :
            return pEntry->IsVisible() ? g_strOne : g_strZero;
        case BROW_ORDER_ROW:
        {
            sal_uInt16 nIdx = m_pOrderCell->GetSelectEntryPos();
            if (nIdx == sal_uInt16(-1))
                nIdx = 0;
            return String(nIdx);
        }
        default:
            return GetCellText(nRow, nColId);
    }
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::SetCellContents(sal_uInt16 nRow, long nColId, const String& strNewText)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    sal_Bool bWasEditing = IsEditing() && (GetCurColumnId() == nColId) && (GetCurRow() == nRow);
    if (bWasEditing)
        DeactivateCell();

    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId - 1];
    DBG_ASSERT(pEntry != NULL, "OSelectionBrowseBox::SetCellContents : invalid column id, prepare for GPF ... ");

    long nCellIndex = GetRealRow(nRow);
    switch (nCellIndex)
    {
        case BROW_VIS_ROW:
            pEntry->SetVisible(strNewText == g_strOne);
            break;
        case BROW_FIELD_ROW:
            pEntry->SetField(strNewText);
            if (strNewText.Len() == 0)			// bei leerem Feld auch den Tabellennamen loeschen
                pEntry->SetAlias(strNewText);
            break;
        case BROW_TABLE_ROW:
            pEntry->SetAlias(strNewText);
            break;
        case BROW_ORDER_ROW:
        {
            sal_uInt16 nIdx = (sal_uInt16)strNewText.ToInt32();
            pEntry->SetOrderDir(EOrderDir(nIdx));
        }	break;
        case BROW_COLUMNALIAS_ROW:
            pEntry->SetFieldAlias(strNewText);
            break;
        case BROW_FUNCTION_ROW:
            pEntry->SetFunction(strNewText);
            if(m_aFunctionStrings.GetToken(m_aFunctionStrings.GetTokenCount()-1).EqualsIgnoreCaseAscii(strNewText))
                pEntry->SetGroupBy(sal_True);
            else
                pEntry->SetFunctionType(FKT_AGGREGATE);
            break;
        default:
            pEntry->SetCriteria(nCellIndex - BROW_CRIT1_ROW, strNewText);
    }

    RowModified(nCellIndex, nColId);

    // die entsprechende Feld-Beschreibung ist jetzt leer -> Visible auf sal_False (damit das konsistent mit normalen leeren Spalten ist)
    if (pEntry->IsEmpty())
        pEntry->SetVisible(sal_False);

    if (bWasEditing)
        ActivateCell(nCellIndex, nColId);

    getDesignView()->getController()->setModified();
}
//------------------------------------------------------------------------------
sal_uInt32 OSelectionBrowseBox::GetTotalCellWidth(long nRow, sal_uInt16 nColId) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    if (!pEntry)
        return DEFAULT_SIZE;

    long nRowId = GetRealRow(nRow);
    if (nRowId == BROW_VIS_ROW)
        return CHECKBOX_SIZE;
    else
        return  GetDataWindow().GetTextWidth(GetCellText(nRowId, nColId));
}

//------------------------------------------------------------------------------
void OSelectionBrowseBox::ColumnResized(sal_uInt16 nColId)
{
    if (getDesignView()->getController()->isReadOnly())
        return;
    // The resizing of columns can't be suppressed (BrowseBox doesn't support that) so we have to do this
    // fake. It's not _that_ bad : the user may change column widths while in read-only mode to see all details
    // but the changes aren't permanent ...

    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT(nColId <= getDesignView()->getController()->getTableFieldDesc()->size(),"ColumnResized:: nColId sollte nicht groesser als List::count sein!");
    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    DBG_ASSERT(pEntry, "OSelectionBrowseBox::ColumnResized : keine FieldDescription !");
    getDesignView()->getController()->setModified();
    DbBrowseBox::ColumnResized(nColId);

    if (pEntry)
    {
        OTabFieldSizedUndoAct* pUndo = new OTabFieldSizedUndoAct(this);
        pUndo->SetColId(nColId);
        pUndo->SetOriginalWidth(pEntry->GetColWidth());
        getDesignView()->getController()->getUndoMgr()->AddUndoAction(pUndo);
        pEntry->SetColWidth(GetColumnWidth(nColId));
    }
}

//------------------------------------------------------------------------------
sal_uInt32 OSelectionBrowseBox::GetTotalCellWidth(long nRowId, sal_uInt16 nColId)
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    DBG_ASSERT((nColId == 0) || (nColId <= getDesignView()->getController()->getTableFieldDesc()->size()), "OSelectionBrowseBox::GetTotalCellWidth : invalid parameter nColId");

    OTableFieldDesc* pEntry = (*getDesignView()->getController()->getTableFieldDesc())[nColId-1];
    DBG_ASSERT(pEntry!=NULL, "OSelectionBrowseBox::GetTotalCellWidth : invalid FieldDescription !");

    long nRow = GetRealRow(nRowId);
    String strText(GetCellText(nRow, nColId));
    return GetDataWindow().LogicToPixel(Size(GetDataWindow().GetTextWidth(strText),0)).Width();
}

//------------------------------------------------------------------------------
sal_uInt16 OSelectionBrowseBox::GetDefaultColumnWidth(const String& rName) const
{
    DBG_CHKTHIS(OSelectionBrowseBox,NULL);
    // die Baissklasse macht das von dem Text abhaengig, ich habe aber keine Spaltenueberschriften, daher haette ich
    // hier gern einen anderen Default-Wert
    return DEFAULT_SIZE;
}
//------------------------------------------------------------------------------
