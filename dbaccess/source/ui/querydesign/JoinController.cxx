/*************************************************************************
 *
 *  $RCSfile: JoinController.cxx,v $
 *
 *  $Revision: 1.24 $
 *
 *  last change: $Author: oj $ $Date: 2002-05-24 13:19:53 $
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
#ifndef _SFXSIDS_HRC
#include <sfx2/sfxsids.hrc>
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef _SV_TOOLBOX_HXX 
#include <vcl/toolbox.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"		   
#endif
#ifndef _COMPHELPER_TYPES_HXX_ 
#include <comphelper/types.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_ 
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_ 
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_ 
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_KEYTYPE_HPP_
#include <com/sun/star/sdbcx/KeyType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_ 
#include <com/sun/star/sdbcx/XDrop.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XALTERTABLE_HPP_
#include <com/sun/star/sdbcx/XAlterTable.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLWARNING_HPP_
#include <com/sun/star/sdbc/SQLWarning.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_ 
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COMPHELPER_STREAMSECTION_HXX_
#include <comphelper/streamsection.hxx>
#endif
#ifndef _COMPHELPER_BASIC_IO_HXX_
#include <comphelper/basicio.hxx>
#endif
#ifndef _COMPHELPER_SEQSTREAM_HXX
#include <comphelper/seqstream.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef _SV_MSGBOX_HXX 
#include <vcl/msgbox.hxx>
#endif
#ifndef DBAUI_TABLEWINDOWDATA_HXX
#include "TableWindowData.hxx"
#endif
#ifndef DBAUI_TABLEWINDOW_HXX
#include "TableWindow.hxx"
#endif
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef DBAUI_QYDLGTAB_HXX
#include "adtabdlg.hxx"
#endif
#ifndef _SV_WAITOBJ_HXX
#include <vcl/waitobj.hxx>
#endif

using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::frame;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::ui::dialogs;
using namespace ::dbtools;
using namespace ::dbaui;
using namespace ::comphelper;

DBG_NAME(OJoinController); 
// -----------------------------------------------------------------------------
OJoinController::OJoinController(const Reference< XMultiServiceFactory >& _rM) : OJoinController_BASE(_rM)
    ,m_bEditable(sal_True)
    ,m_bModified(sal_False)
    ,m_bViewsAllowed(sal_True)
    ,m_pAddTabDlg(NULL)
{
    DBG_CTOR(OJoinController,NULL); 
}
// -----------------------------------------------------------------------------
OJoinController::~OJoinController()
{
    DBG_DTOR(OJoinController,NULL); 
}

// -----------------------------------------------------------------------------
void SAL_CALL OJoinController::disposing( const EventObject& _rSource ) throw(RuntimeException)
{
    OJoinController_BASE::disposing( _rSource );
}

// -----------------------------------------------------------------------------
OJoinDesignView* OJoinController::getJoinView()
{
    return static_cast< OJoinDesignView* >( getView() );
}

// -----------------------------------------------------------------------------
void OJoinController::disposing()
{
    OJoinController_BASE::disposing();
    m_pView			= NULL;
    m_pAddTabDlg	= NULL;

    {
        ::std::vector< OTableConnectionData*>::iterator aIter = m_vTableConnectionData.begin();
        for(;aIter != m_vTableConnectionData.end();++aIter)
            delete *aIter;
        m_vTableConnectionData.clear();
    }
    {
        ::std::vector< OTableWindowData*>::iterator aIter = m_vTableData.begin();
        for(;aIter != m_vTableData.end();++aIter)
            delete *aIter;
        m_vTableData.clear();
    }
}
// -----------------------------------------------------------------------------
SfxUndoManager* OJoinController::getUndoMgr()
{
    return &m_aUndoManager;
}
// -----------------------------------------------------------------------------
void OJoinController::addUndoActionAndInvalidate(SfxUndoAction *_pAction)
{
    // add undo action
    m_aUndoManager.AddUndoAction(_pAction);
    // when we add an undo action the controller was modified
    setModified(sal_True);
    // now inform me that or states changed
    InvalidateFeature(ID_BROWSER_UNDO);
    InvalidateFeature(ID_BROWSER_REDO);
}
// -----------------------------------------------------------------------------
void OJoinController::setModified(sal_Bool _bModified)
{
    m_bModified = _bModified;
    InvalidateFeature(ID_BROWSER_SAVEDOC);
    InvalidateFeature(ID_RELATION_ADD_RELATION);
}
// -----------------------------------------------------------------------------
void OJoinController::Save(const Reference< XObjectOutputStream>& _rxOut)
{
    OStreamSection aSection(_rxOut.get());
    // save all tablewindow data
    _rxOut << (sal_Int32)m_vTableData.size();

    //	::std::for_each(m_vTableData.begin(),m_vTableData.end(),::std::bind2nd(::std::mem_fun(&OTableWindowData::Save),_rxOut));

    ::std::vector< OTableWindowData*>::const_iterator aIter = m_vTableData.begin();
    for(;aIter != m_vTableData.end();++aIter)
        (*aIter)->Save(_rxOut);
}
// -----------------------------------------------------------------------------
void OJoinController::Load(const Reference< XObjectInputStream>& _rxIn)
{
    try
    {
        OStreamSection aSection(_rxIn.get());
        //////////////////////////////////////////////////////////////////////
        // Liste loeschen
        ::std::vector< OTableWindowData*>::iterator aIter = m_vTableData.begin();
        for(;aIter != m_vTableData.end();++aIter)
            delete *aIter;
        m_vTableData.clear();

        sal_Int32 nCount = 0;
        _rxIn >> nCount;
        m_vTableData.reserve(nCount);
        for(sal_Int32 i=0;i<nCount;++i)
        {
            OTableWindowData* pData = createTableWindowData();
            pData->Load(_rxIn);
            m_vTableData.push_back(pData);
        }
    }
    catch(Exception&)
    {
    }
}
// -----------------------------------------------------------------------------
void OJoinController::SaveTabWinPosSize(OTableWindow* pTabWin, long nOffsetX, long nOffsetY)
{
    // die Daten zum Fenster
    OTableWindowData* pData = pTabWin->GetData();
    OSL_ENSURE(pData != NULL, "SaveTabWinPosSize : TabWin hat keine Daten !");

    // Position & Size der Daten neu setzen (aus den aktuellen Fenster-Parametern)
    Point aPos = pTabWin->GetPosPixel();
    aPos.X() += nOffsetX;
    aPos.Y() += nOffsetY;
    pData->SetPosition(aPos);
    pData->SetSize(pTabWin->GetSizePixel());

}
// -----------------------------------------------------------------------------
FeatureState OJoinController::GetState(sal_uInt16 _nId) const
{
    FeatureState aReturn;
        // (disabled automatically)
    aReturn.bEnabled = sal_True;

    switch (_nId)
    {
        case SID_CLOSEDOC:
            break;
        case ID_BROWSER_EDITDOC:
            aReturn.aState = ::cppu::bool2any(m_bEditable);
            break;
        case ID_BROWSER_SAVEDOC:
            aReturn.bEnabled = isConnected() && m_bModified;
            break;
        case ID_BROWSER_ADDTABLE:
            if (aReturn.bEnabled = getView() && const_cast< OJoinController* >( this )->getJoinView()->getTableView()->IsAddAllowed())
                aReturn.aState = ::cppu::bool2any(m_pAddTabDlg && m_pAddTabDlg->IsVisible());
            else
                aReturn.aState = ::cppu::bool2any(sal_False);
            break;
        case ID_BROWSER_UNDO:
            aReturn.bEnabled = m_bEditable && m_aUndoManager.GetUndoActionCount() != 0;
            break;
        case ID_BROWSER_REDO:
            aReturn.bEnabled = m_bEditable && m_aUndoManager.GetRedoActionCount() != 0;
            break;
    }
    return aReturn;
}
// -----------------------------------------------------------------------------
void OJoinController::Execute(sal_uInt16 _nId)
{
    switch(_nId)
    {
        case SID_CLOSEDOC:
            closeTask();
            return;
            break;
        case ID_BROWSER_EDITDOC:
            if(m_bEditable)
            { // the state should be changed to not editable
                switch (saveModified())
                {
                    case RET_CANCEL:
                        // don't change anything here so return
                        return;
                        break;
                    case RET_NO:
                        reset();
                        setModified(sal_False);		// and we are not modified yet
                        break;
                    default:
                        break;
                }
            }
            m_bEditable = !m_bEditable;
            getJoinView()->setReadOnly(!m_bEditable);
            InvalidateAll();
            return;
            break;
        case ID_BROWSER_UNDO:
            m_aUndoManager.Undo();
            InvalidateFeature(ID_BROWSER_REDO);
            break;
        case ID_BROWSER_REDO:
            m_aUndoManager.Redo();
            InvalidateFeature(ID_BROWSER_UNDO);
            break;
        case ID_BROWSER_ADDTABLE:
            if(!m_pAddTabDlg)
                m_pAddTabDlg = getJoinView()->getAddTableDialog();
            if(m_pAddTabDlg->IsVisible())
            {
                m_pAddTabDlg->Show(!m_pAddTabDlg->IsVisible());
                m_pView->GrabFocus();
            }
            else if(getJoinView()->getTableView()->IsAddAllowed())
            {
                {
                    WaitObject aWaitCursor(getView());
                    m_pAddTabDlg->Update();
                }
                m_pAddTabDlg->Show(!m_pAddTabDlg->IsVisible());
            }
            break;
    }
    InvalidateFeature(_nId);
}
// -----------------------------------------------------------------------------
void OJoinController::SaveTabWinsPosSize( OJoinTableView::OTableWindowMap* pTabWinList, long nOffsetX, long nOffsetY )
{
    // Das Loeschen und Neuanlegen der alten Implementation ist unter dem aktuellen Modell nicht mehr richtig : Die TabWins
    // habe einen Zeiger auf ihre Daten, verwaltet werden sie aber von mir. Wenn ich die alten loesche, haben die TabWins
    // ploetzlich Zeiger auf nicht mehr existente Objekte.
    // Wenn die TabWins ein SetData haetten, koennte ich mir das sparen ... haben sie aber nicht, ausserdem muesste ich dann immer
    // noch Informationen, die sich eigentlich nicht geaendert haben, auch neu setzen.
    // Also loesche ich die TabWinDatas nicht, sondern aktualisiere sie nur.
    DBG_ASSERT(m_vTableData.size() == pTabWinList->size(),
        "OJoinController::SaveTabWinsPosSize : inkonsistenter Zustand : sollte genausviel TabWinDatas haben wie TabWins !");

    OJoinTableView::OTableWindowMap::iterator aIter = pTabWinList->begin();
    for(;aIter != pTabWinList->end();++aIter)
        SaveTabWinPosSize(aIter->second, nOffsetX, nOffsetY);
}
// -----------------------------------------------------------------------------
void OJoinController::removeConnectionData(OTableConnectionData* _pData)
{
    m_vTableConnectionData.erase( ::std::find(m_vTableConnectionData.begin(),m_vTableConnectionData.end(),_pData));
}
// -----------------------------------------------------------------------------
void OJoinController::AddSupportedFeatures()
{
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Redo")]		= ID_BROWSER_REDO;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Save")]		= ID_BROWSER_SAVEDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Undo")]		= ID_BROWSER_UNDO;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:CloseDoc")]	= SID_CLOSEDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/AddTable")]	= ID_BROWSER_ADDTABLE;
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OJoinController::suspend(sal_Bool bSuspend) throw( RuntimeException )
{
    return saveModified() != RET_CANCEL;
}
// -----------------------------------------------------------------------------










