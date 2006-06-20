/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dsEntriesNoExp.cxx,v $
 *
 *  $Revision: 1.15 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 02:57:13 $
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

#ifndef _SBA_UNODATBR_HXX_
#include "unodatbr.hxx"
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef _DBAUI_LISTVIEWITEMS_HXX_
#include "listviewitems.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef DBACCESS_UI_DBTREEVIEW_HXX
#include "dbtreeview.hxx"
#endif
#ifndef DBAUI_DBTREELISTBOX_HXX
#include "dbtreelistbox.hxx"
#endif
#ifndef _DBU_BRW_HRC_
#include "dbu_brw.hrc"
#endif
#ifndef DBAUI_DBTREEMODEL_HXX
#include "dbtreemodel.hxx"
#endif

using namespace ::com::sun::star::frame;
using namespace ::dbtools;
using namespace ::svx;

// .........................................................................
namespace dbaui
{
// .........................................................................
// -----------------------------------------------------------------------------
SbaTableQueryBrowser::EntryType SbaTableQueryBrowser::getChildType( SvLBoxEntry* _pEntry ) const 
{
    DBG_ASSERT(isContainer(_pEntry), "SbaTableQueryBrowser::getChildType: invalid entry!");
    switch (getEntryType(_pEntry))
    {
        case etTableContainer:
            return etTable;
        case etQueryContainer:
            return etQuery;
        default:
            break;
    }
    return etUnknown;
}

// -----------------------------------------------------------------------------
String SbaTableQueryBrowser::GetEntryText( SvLBoxEntry* _pEntry ) const
{
    return m_pTreeView->getListBox()->GetEntryText(_pEntry);
}

// -----------------------------------------------------------------------------
SbaTableQueryBrowser::EntryType SbaTableQueryBrowser::getEntryType( SvLBoxEntry* _pEntry ) const
{
    if (!_pEntry)
        return etUnknown;

    SvLBoxEntry* pRootEntry 	= m_pTreeView->getListBox()->GetRootLevelParent(_pEntry);
    SvLBoxEntry* pEntryParent	= m_pTreeView->getListBox()->GetParent(_pEntry);
    SvLBoxEntry* pTables		= m_pTreeView->getListBox()->GetEntry(pRootEntry, CONTAINER_TABLES);
    SvLBoxEntry* pQueries		= m_pTreeView->getListBox()->GetEntry(pRootEntry, CONTAINER_QUERIES);

#ifdef DBG_UTIL
    String sTest;
    if (pTables) sTest = m_pTreeView->getListBox()->GetEntryText(pTables);
    if (pQueries) sTest = m_pTreeView->getListBox()->GetEntryText(pQueries);
#endif

    if (pRootEntry == _pEntry)
        return etDatasource;

    if (pTables == _pEntry)
        return etTableContainer;

    if (pQueries == _pEntry)
        return etQueryContainer;

    if (pTables == pEntryParent)
        return etTable;

    if (pQueries == pEntryParent)
        return etQuery;

    return etUnknown;
}
//------------------------------------------------------------------------------
void SbaTableQueryBrowser::select(SvLBoxEntry* _pEntry, sal_Bool _bSelect)
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING) : NULL;
    if (pTextItem)
    {
        static_cast<OBoldListboxString*>(pTextItem)->emphasize(_bSelect);
        m_pTreeModel->InvalidateEntry(_pEntry);
    }
    else
        DBG_ERROR("SbaTableQueryBrowser::select: invalid entry!");
}

//------------------------------------------------------------------------------
void SbaTableQueryBrowser::selectPath(SvLBoxEntry* _pEntry, sal_Bool _bSelect)
{
    while (_pEntry)
    {
        select(_pEntry, _bSelect);
        _pEntry = m_pTreeModel->GetParent(_pEntry);
    }
}
//------------------------------------------------------------------------------
sal_Bool SbaTableQueryBrowser::isSelected(SvLBoxEntry* _pEntry) const
{
    SvLBoxItem* pTextItem = _pEntry ? _pEntry->GetFirstItem(SV_ITEM_ID_BOLDLBSTRING) : NULL;
    if (pTextItem)
        return static_cast<OBoldListboxString*>(pTextItem)->isEmphasized();
    else
        DBG_ERROR("SbaTableQueryBrowser::isSelected: invalid entry!");
    return sal_False;
}
//------------------------------------------------------------------------------
void SbaTableQueryBrowser::SelectionChanged()
{
    if ( !m_bShowMenu )
    {
        InvalidateFeature(ID_BROWSER_INSERTCOLUMNS);
        InvalidateFeature(ID_BROWSER_INSERTCONTENT);
        InvalidateFeature(ID_BROWSER_FORMLETTER);
    }
}
//------------------------------------------------------------------------------
void SbaTableQueryBrowser::describeSupportedFeatures()
{
    SbaXDataBrowserController::describeSupportedFeatures();

    implDescribeSupportedFeature( ".uno:Title",                             ID_BROWSER_TITLE );
    if ( !m_bShowMenu )
    {
        implDescribeSupportedFeature( ".uno:DSBrowserExplorer",                 ID_BROWSER_EXPLORER, CommandGroup::VIEW );

        implDescribeSupportedFeature( ".uno:DSBFormLetter",                     ID_BROWSER_FORMLETTER, CommandGroup::DOCUMENT );
        implDescribeSupportedFeature( ".uno:DSBInsertColumns",                  ID_BROWSER_INSERTCOLUMNS, CommandGroup::INSERT );
        implDescribeSupportedFeature( ".uno:DSBInsertContent",                  ID_BROWSER_INSERTCONTENT, CommandGroup::INSERT );
        implDescribeSupportedFeature( ".uno:DSBDocumentDataSource",             ID_BROWSER_DOCUMENT_DATASOURCE, CommandGroup::VIEW );

        implDescribeSupportedFeature( ".uno:DataSourceBrowser/FormLetter",          ID_BROWSER_FORMLETTER );
        implDescribeSupportedFeature( ".uno:DataSourceBrowser/InsertColumns",       ID_BROWSER_INSERTCOLUMNS );
        implDescribeSupportedFeature( ".uno:DataSourceBrowser/InsertContent",       ID_BROWSER_INSERTCONTENT );
        implDescribeSupportedFeature( ".uno:DataSourceBrowser/DocumentDataSource",  ID_BROWSER_DOCUMENT_DATASOURCE );
    }

    implDescribeSupportedFeature( ".uno:CloseWin",      ID_BROWSER_CLOSE, CommandGroup::DOCUMENT );
    implDescribeSupportedFeature( ".uno:DBRebuildData", ID_BROWSER_REFRESH_REBUILD, CommandGroup::DATA );
}
// -------------------------------------------------------------------------
String SbaTableQueryBrowser::getURL() const
{
    return String();
}
// -----------------------------------------------------------------------------
void SbaTableQueryBrowser::notifyHiContrastChanged()
{
    if ( m_pTreeView )
    {
        sal_Bool bHiContrast = isHiContrast();

        if ( m_bHiContrast != bHiContrast )
        {
            m_bHiContrast = bHiContrast;
            // change all bitmap entries
            SvLBoxEntry* pEntryLoop = m_pTreeModel->First();
            while ( pEntryLoop )
            {
                DBTreeListModel::DBTreeListUserData* pData = static_cast<DBTreeListModel::DBTreeListUserData*>(pEntryLoop->GetUserData());
                if ( pData )
                {
                    ModuleRes aResId(DBTreeListModel::getImageResId(pData->eType,isHiContrast()));
                    Image aImage(aResId);
                    USHORT nCount = pEntryLoop->ItemCount();
                    for (USHORT i=0;i<nCount;++i)
                    {
                        SvLBoxItem* pItem = pEntryLoop->GetItem(i);
                        if ( pItem && pItem->IsA() == SV_ITEM_ID_LBOXCONTEXTBMP)
                        {
                            static_cast<SvLBoxContextBmp*>(pItem)->SetBitmap1( aImage );
                            static_cast<SvLBoxContextBmp*>(pItem)->SetBitmap2( aImage );
                            break;
                        }
                    }
                }
                pEntryLoop = m_pTreeModel->Next(pEntryLoop);
            }
        }
    }
}
// -----------------------------------------------------------------------------
// .........................................................................
}	// namespace dbaui
// .........................................................................

