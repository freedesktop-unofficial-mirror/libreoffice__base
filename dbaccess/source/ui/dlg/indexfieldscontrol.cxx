/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: indexfieldscontrol.cxx,v $
 *
 *  $Revision: 1.14 $
 *
 *  last change: $Author: hr $ $Date: 2005-09-23 12:31:19 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _DBAUI_INDEXFIELDSCONTROL_HXX_
#include "indexfieldscontrol.hxx"
#endif
#ifndef _DBU_DLG_HRC_
#include "dbu_dlg.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
#ifndef _DBA_DBACCESS_HELPID_HRC_
#include "dbaccess_helpid.hrc"
#endif

//......................................................................
namespace dbaui
{
//......................................................................

#define BROWSER_STANDARD_FLAGS		BROWSER_COLUMNSELECTION | BROWSER_HLINESFULL | BROWSER_VLINESFULL |	\
                                    BROWSER_HIDECURSOR | BROWSER_HIDESELECT | BROWSER_AUTO_HSCROLL | BROWSER_AUTO_VSCROLL

#define COLUMN_ID_FIELDNAME		1
#define	COLUMN_ID_ORDER			2

    using namespace ::com::sun::star::uno;
    using namespace ::svt;

    //==================================================================
    //= DbaMouseDownListBoxController
    //==================================================================
    class DbaMouseDownListBoxController : public ListBoxCellController
    {
    protected:
        Link	m_aOriginalModifyHdl;
        Link	m_aAdditionalModifyHdl;

    public:
        DbaMouseDownListBoxController(ListBoxControl* _pParent)
            :ListBoxCellController(_pParent)
        {
        }

        void SetAdditionalModifyHdl(const Link& _rHdl);

    protected:
        virtual sal_Bool WantMouseEvent() const { return sal_True; }
        virtual void SetModifyHdl(const Link& _rHdl);

    private:
        void implCheckLinks();
        DECL_LINK( OnMultiplexModify, void* );
    };

    //------------------------------------------------------------------
    void DbaMouseDownListBoxController::SetAdditionalModifyHdl(const Link& _rHdl)
    {
        m_aAdditionalModifyHdl = _rHdl;
        implCheckLinks();
    }

    //------------------------------------------------------------------
    void DbaMouseDownListBoxController::SetModifyHdl(const Link& _rHdl)
    {
        m_aOriginalModifyHdl = _rHdl;
        implCheckLinks();
    }

    //------------------------------------------------------------------
    IMPL_LINK( DbaMouseDownListBoxController, OnMultiplexModify, void*, _pArg )
    {
        if (m_aAdditionalModifyHdl.IsSet())
            m_aAdditionalModifyHdl.Call(_pArg);
        if (m_aOriginalModifyHdl.IsSet())
            m_aOriginalModifyHdl.Call(_pArg);
        return 0L;
    }

    //------------------------------------------------------------------
    void DbaMouseDownListBoxController::implCheckLinks()
    {
        if (m_aAdditionalModifyHdl.IsSet() || m_aOriginalModifyHdl.IsSet())
            ListBoxCellController::SetModifyHdl(LINK(this, DbaMouseDownListBoxController, OnMultiplexModify));
        else
            ListBoxCellController::SetModifyHdl(Link());
    }

    //==================================================================
    //= IndexFieldsControl
    //==================================================================
DBG_NAME(IndexFieldsControl)
//------------------------------------------------------------------
    IndexFieldsControl::IndexFieldsControl( Window* _pParent, const ResId& _rId ,sal_Int32 _nMaxColumnsInIndex)
        :EditBrowseBox(_pParent, _rId, EBBF_SMART_TAB_TRAVEL | EBBF_ACTIVATE_ON_BUTTONDOWN, BROWSER_STANDARD_FLAGS)
        ,m_aSeekRow(m_aFields.end())
        ,m_pSortingCell(NULL)
        ,m_pFieldNameCell(NULL)
        ,m_nMaxColumnsInIndex(_nMaxColumnsInIndex)
    {
        DBG_CTOR(IndexFieldsControl,NULL);

        SetUniqueId( UID_DLGINDEX_INDEXDETAILS_BACK );
        GetDataWindow().SetUniqueId( UID_DLGINDEX_INDEXDETAILS_MAIN );
    }

    //------------------------------------------------------------------
    IndexFieldsControl::~IndexFieldsControl()
    {
        delete m_pSortingCell;
        delete m_pFieldNameCell;
    
        DBG_DTOR(IndexFieldsControl,NULL);
    }

    //------------------------------------------------------------------
    sal_Bool IndexFieldsControl::SeekRow(long nRow)
    {
        if (!EditBrowseBox::SeekRow(nRow))
            return sal_False;

        if (nRow < 0)
        {
            m_aSeekRow = m_aFields.end();
        }
        else
        {
            m_aSeekRow = m_aFields.begin() + nRow;
            OSL_ENSURE(m_aSeekRow <= m_aFields.end(), "IndexFieldsControl::SeekRow: invalid row!");
        }

        return sal_True;
    }

    //------------------------------------------------------------------
    void IndexFieldsControl::PaintCell( OutputDevice& _rDev, const Rectangle& _rRect, sal_uInt16 _nColumnId ) const
    {
        Point aPos(_rRect.TopLeft());
        aPos.X() += 1;

        String aText = GetRowCellText(m_aSeekRow,_nColumnId);
        Size TxtSize(GetDataWindow().GetTextWidth(aText), GetDataWindow().GetTextHeight());

        // clipping
        if (aPos.X() < _rRect.Right() || aPos.X() + TxtSize.Width() > _rRect.Right() ||
            aPos.Y() < _rRect.Top() || aPos.Y() + TxtSize.Height() > _rRect.Bottom())
            _rDev.SetClipRegion( _rRect );

        // allow for a disabled control ...
        sal_Bool bEnabled = IsEnabled();
        Color aOriginalColor = _rDev.GetTextColor();
        if (!bEnabled)
            _rDev.SetTextColor(GetSettings().GetStyleSettings().GetDisableColor());

        // draw the text
        _rDev.DrawText(aPos, aText);

        // reset the color (if necessary)
        if (!bEnabled)
            _rDev.SetTextColor(aOriginalColor);

        if (_rDev.IsClipRegion())
            _rDev.SetClipRegion();
    }

    //------------------------------------------------------------------
    void IndexFieldsControl::initializeFrom(const IndexFields& _rFields)
    {
        // copy the field descriptions
        m_aFields = _rFields;
        m_aSeekRow = m_aFields.end();

        SetUpdateMode(sal_False);
        // remove all rows
        RowRemoved(1, GetRowCount());
        // insert rows for the the fields
        RowInserted(GetRowCount(), m_aFields.size(), sal_False);
        // insert an additional row for a new field for that index
//		if(!m_nMaxColumnsInIndex || GetRowCount() < m_nMaxColumnsInIndex )
            RowInserted(GetRowCount(), 1, sal_False);
        SetUpdateMode(sal_True);

        GoToRowColumnId(0, COLUMN_ID_FIELDNAME);
    }

    //------------------------------------------------------------------
    void IndexFieldsControl::commitTo(IndexFields& _rFields)
    {
        // do not just copy the array, we may have empty field names (which should not be copied)
        _rFields.resize(m_aFields.size());
        ConstIndexFieldsIterator aSource = m_aFields.begin();
        ConstIndexFieldsIterator aSourceEnd = m_aFields.end();
        IndexFieldsIterator aDest = _rFields.begin();
        for (; aSource < aSourceEnd; ++aSource)
            if (0 != aSource->sFieldName.Len())
            {
                *aDest = *aSource;
                ++aDest;
            }

        _rFields.resize(aDest - _rFields.begin());
    }

    //------------------------------------------------------------------
    sal_uInt32 IndexFieldsControl::GetTotalCellWidth(long _nRow, sal_uInt16 _nColId)
    {
        if (COLUMN_ID_ORDER == _nColId)
        {
            sal_Int32 nWidthAsc = GetTextWidth(m_sAscendingText) + GetSettings().GetStyleSettings().GetScrollBarSize();
            sal_Int32 nWidthDesc = GetTextWidth(m_sDescendingText) + GetSettings().GetStyleSettings().GetScrollBarSize();
            // maximum plus some additional space
            return (nWidthAsc > nWidthDesc ? nWidthAsc : nWidthDesc) + GetTextWidth('0') * 2;
        }
        return EditBrowseBox::GetTotalCellWidth(_nRow, _nColId);
    }

    //------------------------------------------------------------------
    void IndexFieldsControl::Init(const Sequence< ::rtl::OUString >& _rAvailableFields)
    {
        RemoveColumns();

        m_sAscendingText = String(ModuleRes(STR_ORDER_ASCENDING));
        m_sDescendingText = String(ModuleRes(STR_ORDER_DESCENDING));

        // the "sort order" column
        String sColumnName = String(ModuleRes(STR_TAB_INDEX_SORTORDER));
        // the width of the order column is the maximum widths of the texts used
        // (the title of the column)
        sal_Int32 nSortOrderColumnWidth = GetTextWidth(sColumnName);
        // ("ascending" + scrollbar width)
        sal_Int32 nOther = GetTextWidth(m_sAscendingText) + GetSettings().GetStyleSettings().GetScrollBarSize();
        nSortOrderColumnWidth = nSortOrderColumnWidth > nOther ? nSortOrderColumnWidth : nOther;
        // ("descending" + scrollbar width)
        nOther = GetTextWidth(m_sDescendingText) + GetSettings().GetStyleSettings().GetScrollBarSize();
        nSortOrderColumnWidth = nSortOrderColumnWidth > nOther ? nSortOrderColumnWidth : nOther;
        // (plus some additional space)
        nSortOrderColumnWidth += GetTextWidth('0') * 2;
        InsertDataColumn(COLUMN_ID_ORDER, sColumnName, nSortOrderColumnWidth, HIB_STDSTYLE, 1);

        // for the width: both columns together should be somewhat smaller than the whole window (without the scrollbar)
        sal_Int32 nFieldNameWidth = GetSizePixel().Width();
        nFieldNameWidth -= nSortOrderColumnWidth;

        StyleSettings aSystemStyle = Application::GetSettings().GetStyleSettings();
        nFieldNameWidth -= aSystemStyle.GetScrollBarSize();
        nFieldNameWidth -= 8;

        // the "field name" column
        sColumnName = String(ModuleRes(STR_TAB_INDEX_FIELD));
        InsertDataColumn(COLUMN_ID_FIELDNAME, sColumnName, nFieldNameWidth, HIB_STDSTYLE, 0);

        // create the cell controllers
        // for the field name cell
        m_pFieldNameCell = new ListBoxControl(&GetDataWindow());
        m_pFieldNameCell->InsertEntry(String());
        const ::rtl::OUString* pFields = _rAvailableFields.getConstArray();
        const ::rtl::OUString* pFieldsEnd = pFields + _rAvailableFields.getLength();
        for (;pFields < pFieldsEnd; ++pFields)
            m_pFieldNameCell->InsertEntry(*pFields);
        // for the sort cell
        m_pSortingCell = new ListBoxControl(&GetDataWindow());
        m_pSortingCell->InsertEntry(m_sAscendingText);
        m_pSortingCell->InsertEntry(m_sDescendingText);

        m_pFieldNameCell->SetHelpId( HID_DLGINDEX_INDEXDETAILS_FIELD );
        m_pSortingCell->SetHelpId( HID_DLGINDEX_INDEXDETAILS_SORTORDER );
    }

    //------------------------------------------------------------------
    CellController* IndexFieldsControl::GetController(long _nRow, sal_uInt16 _nColumnId)
    {
        if (!IsEnabled())
            return NULL;

        ConstIndexFieldsIterator aRow;
        sal_Bool bNewField = !implGetFieldDesc(_nRow, aRow);

        DbaMouseDownListBoxController* pReturn = NULL;
        switch (_nColumnId)
        {
            case COLUMN_ID_ORDER:
                if (!bNewField && m_pSortingCell && 0 != aRow->sFieldName.Len())
                    pReturn = new DbaMouseDownListBoxController(m_pSortingCell);
                break;

            case COLUMN_ID_FIELDNAME:
                pReturn = new DbaMouseDownListBoxController(m_pFieldNameCell);
                break;

            default:
                OSL_ENSURE(sal_False, "IndexFieldsControl::GetController: invalid column id!");
        }

        if (pReturn)
            pReturn->SetAdditionalModifyHdl(LINK(this, IndexFieldsControl, OnListEntrySelected));

        return pReturn;
    }

    //------------------------------------------------------------------
    sal_Bool IndexFieldsControl::implGetFieldDesc(long _nRow, ConstIndexFieldsIterator& _rPos)
    {
        _rPos = m_aFields.end();
        if ((_nRow < 0) || (_nRow >= (sal_Int32)m_aFields.size()))
            return sal_False;
        _rPos = m_aFields.begin() + _nRow;
        return sal_True;
    }

    //------------------------------------------------------------------
    sal_Bool IndexFieldsControl::IsModified() const
    {
        return EditBrowseBox::IsModified();
    }

    //------------------------------------------------------------------
    sal_Bool IndexFieldsControl::SaveModified()
    {
        if (!IsModified())
            return sal_True;

        switch (GetCurColumnId())
        {
            case COLUMN_ID_FIELDNAME:
            {
                String sFieldSelected = m_pFieldNameCell->GetSelectEntry();
                sal_Bool bEmptySelected = 0 == sFieldSelected.Len();
                if (isNewField())
                {
                    if (!bEmptySelected)
                    {
                        // add a new field to the collection
                        OIndexField aNewField;
                        aNewField.sFieldName = sFieldSelected;
                        m_aFields.push_back(aNewField);
                        RowInserted(GetRowCount(), 1, sal_True);
                    }
                }
                else
                {
                    sal_Int32 nRow = GetCurRow();
                    OSL_ENSURE(nRow < (sal_Int32)m_aFields.size(), "IndexFieldsControl::SaveModified: invalid current row!");
                    if (nRow >= 0)	// may be -1 in case the control was empty
                    {
                        // remove the field from the selection
                        IndexFieldsIterator aPos = m_aFields.begin() + nRow;

                        if (bEmptySelected)
                        {
                            aPos->sFieldName = String();

                            // invalidate the row to force repaint
                            Invalidate(GetRowRectPixel(nRow));
                            return sal_True;
                        }

                        if (sFieldSelected == aPos->sFieldName)
                            // nothing changed
                            return sal_True;

                        aPos->sFieldName = sFieldSelected;
                    }
                }

                Invalidate(GetRowRectPixel(GetCurRow()));
            }
            break;
            case COLUMN_ID_ORDER:
            {
                OSL_ENSURE(!isNewField(), "IndexFieldsControl::SaveModified: why the hell ...!!!");
                // selected entry
                sal_uInt16 nPos = m_pSortingCell->GetSelectEntryPos();
                OSL_ENSURE(LISTBOX_ENTRY_NOTFOUND != nPos, "IndexFieldsControl::SaveModified: how did you get this selection??");
                // adjust the sort flag in the index field description
                OIndexField& rCurrentField = m_aFields[GetCurRow()];
                rCurrentField.bSortAscending = (0 == nPos);

            }
            break;
            default:
                OSL_ENSURE(sal_False, "IndexFieldsControl::SaveModified: invalid column id!");
        }
        return sal_True;
    }

    //------------------------------------------------------------------
    void IndexFieldsControl::InitController(CellControllerRef& _rController, long _nRow, sal_uInt16 _nColumnId)
    {
        ConstIndexFieldsIterator aFieldDescription;
        sal_Bool bNewField = !implGetFieldDesc(_nRow, aFieldDescription);

        switch (_nColumnId)
        {
            case COLUMN_ID_FIELDNAME:
                m_pFieldNameCell->SelectEntry(bNewField ? String() : aFieldDescription->sFieldName);
                m_pFieldNameCell->SaveValue();
                break;

            case COLUMN_ID_ORDER:
                m_pSortingCell->SelectEntry(aFieldDescription->bSortAscending ? m_sAscendingText : m_sDescendingText);
                m_pSortingCell->SaveValue();
                break;

            default:
                OSL_ENSURE(sal_False, "IndexFieldsControl::InitController: invalid column id!");
        }
    }

    //------------------------------------------------------------------
    IMPL_LINK( IndexFieldsControl, OnListEntrySelected, ListBox*, _pBox )
    {
        if (!_pBox->IsTravelSelect() && m_aModifyHdl.IsSet())
            m_aModifyHdl.Call(this);

        if (_pBox == m_pFieldNameCell)
        {	// a field has been selected
            if (GetCurRow() >= GetRowCount() - 2)
            {	// and we're in one of the last two rows
                String sSelectedEntry = m_pFieldNameCell->GetSelectEntry();
                sal_Int32 nCurrentRow = GetCurRow();
                sal_Int32 nRowCount = GetRowCount();

                OSL_ENSURE(((sal_Int32)(m_aFields.size() + 1)) == nRowCount, "IndexFieldsControl::OnListEntrySelected: inconsistence!");

                if (sSelectedEntry.Len() && (nCurrentRow == nRowCount - 1) /*&& (!m_nMaxColumnsInIndex || nRowCount < m_nMaxColumnsInIndex )*/ )
                {	// in the last row, an non-empty string has been selected
                    // -> insert a new row
                    m_aFields.push_back(OIndexField());
                    RowInserted(GetRowCount(), 1);
                    Invalidate(GetRowRectPixel(nCurrentRow));
                }
                else if (!sSelectedEntry.Len() && (nCurrentRow == nRowCount - 2))
                {	// in the (last-1)th row, an empty entry has been selected
                    // -> remove the last row
                    m_aFields.erase(m_aFields.end() - 1);
                    RowRemoved(GetRowCount() - 1, 1);
                    Invalidate(GetRowRectPixel(nCurrentRow));
                }
            }

            SaveModified();
        }
        return 0L;
    }
    //------------------------------------------------------------------
    String IndexFieldsControl::GetCellText(long _nRow,sal_uInt16 nColId) const
    {
        ConstIndexFieldsIterator aRow = m_aFields.end();
        if ( _nRow >= 0 )
        {
            aRow = m_aFields.begin() + _nRow;
            OSL_ENSURE(aRow <= m_aFields.end(), "IndexFieldsControl::SeekRow: invalid row!");
        }
        return GetRowCellText(aRow,nColId);
    }
    //------------------------------------------------------------------
    String IndexFieldsControl::GetRowCellText(const ConstIndexFieldsIterator& _rRow,sal_uInt16 nColId) const
    {
        if (_rRow < m_aFields.end())
        {
            switch (nColId)
            {
                case COLUMN_ID_FIELDNAME:
                    return _rRow->sFieldName;
                case COLUMN_ID_ORDER:
                    if (0 == _rRow->sFieldName.Len())
                        return String();
                    else
                        return _rRow->bSortAscending ? m_sAscendingText : m_sDescendingText;
                default:
                    OSL_ENSURE(sal_False, "IndexFieldsControl::GetCurrentRowCellText: invalid column id!");
            }
        }
        return String();
    }
    //------------------------------------------------------------------
    sal_Bool IndexFieldsControl::IsTabAllowed(sal_Bool bForward) const
    {
        return sal_False;
    }
    //------------------------------------------------------------------

//......................................................................
}	// namespace dbaui
//......................................................................

