/*************************************************************************
 *
 *  $RCSfile: querycontroller.cxx,v $
 *
 *  $Revision: 1.82 $
 *
 *  last change: $Author: oj $ $Date: 2002-10-04 12:32:24 $
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
#ifndef DBAUI_QUERYCONTROLLER_HXX
#include "querycontroller.hxx"
#endif
#ifndef DBAUI_QUERYVIEW_HXX
#include "queryview.hxx"
#endif
#ifndef _DBAU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _SFXSIDS_HRC
#include <sfx2/sfxsids.hrc>
#endif
#ifndef _DBU_QRY_HRC_
#include "dbu_qry.hrc"
#endif
#ifndef _SV_TOOLBOX_HXX
#include <vcl/toolbox.hxx>
#endif
#ifndef DBACCESS_UI_BROWSER_ID_HXX
#include "browserids.hxx"
#endif
#ifndef DBAUI_QUERYCONTAINERWINDOW_HXX
#include "querycontainerwindow.hxx"
#endif
#ifndef DBAUI_QUERYVIEW_TEXT_HXX
#include "QueryTextView.hxx"
#endif
#ifndef DBAUI_QUERYDESIGNVIEW_HXX
#include "QueryDesignView.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSERFACTORY_HPP_
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XLOADEVENTLISTENER_HPP_
#include <com/sun/star/frame/XLoadEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XVIEWSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XViewsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_FRAMESEARCHFLAG_HPP_
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef DBAUI_DLGSAVE_HXX
#include "dlgsave.hxx"
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCHILD_HPP_
#include <com/sun/star/container/XChild.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDROP_HPP_
#include <com/sun/star/sdbcx/XDrop.hpp>
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
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#include "TableConnectionData.hxx"
#endif
#ifndef DBAUI_QYDLGTAB_HXX
#include "adtabdlg.hxx"
#endif
#ifndef DBAUI_QUERYVIEWSWITCH_HXX
#include "QueryViewSwitch.hxx"
#endif
#ifndef _COMPHELPER_STREAMSECTION_HXX_
#include <comphelper/streamsection.hxx>
#endif
#ifndef _COMPHELPER_BASIC_IO_HXX_
#include <comphelper/basicio.hxx>
#endif
#ifndef DBAUI_TABLEFIELDDESC_HXX
#include "TableFieldDescription.hxx"
#endif
#ifndef DBAUI_QUERY_TABLEWINDOWDATA_HXX
#include "QTableWindowData.hxx"
#endif
#ifndef _COMPHELPER_SEQSTREAM_HXX
#include <comphelper/seqstream.hxx>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef DBAUI_QUERY_TABLEWINDOW_HXX
#include "QTableWindow.hxx"
#endif
#ifndef _DBAUI_SQLMESSAGE_HXX_
#include "sqlmessage.hxx"
#endif
#ifndef _COM_SUN_STAR_UTIL_XFLUSHABLE_HPP_
#include <com/sun/star/util/XFlushable.hpp>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef DBAUI_QUERYTABLEVIEW_HXX
#include "QueryTableView.hxx"
#endif

extern "C" void SAL_CALL createRegistryInfo_OQueryControl()
{
    static ::dbaui::OMultiInstanceAutoRegistration< ::dbaui::OQueryController > aAutoRegistration;
}

namespace dbaui
{
    using namespace ::connectivity;
#ifdef DEBUG	
    namespace
    {
        // -----------------------------------------------------------------------------
        void insertParseTree(SvTreeListBox* _pBox,::connectivity::OSQLParseNode* _pNode,SvLBoxEntry* _pParent = NULL)
        {
            ::rtl::OUString rString;
            if (!_pNode->isToken())
            {
                // Regelnamen als rule: ...
                rString = ::rtl::OUString::createFromAscii("RULE_ID: ");
                rString += ::rtl::OUString::valueOf( (sal_Int32)_pNode->getRuleID());
                rString+= ::rtl::OUString::createFromAscii("(");
                rString += OSQLParser::RuleIDToStr(_pNode->getRuleID());
                rString+= ::rtl::OUString::createFromAscii(")");
                

                _pParent = _pBox->InsertEntry(rString,_pParent);
                
                // einmal auswerten wieviel Subtrees dieser Knoten besitzt
                sal_uInt32 nStop = _pNode->count();
                // hol dir den ersten Subtree
                for(sal_uInt32 i=0;i<nStop;++i)
                    insertParseTree(_pBox,_pNode->getChild(i),_pParent);
            }
            else 
            {
                // ein Token gefunden
                // tabs fuer das Einruecken entsprechend nLevel

                switch (_pNode->getNodeType()) 
                {

                case SQL_NODE_KEYWORD:
                    {rString+= ::rtl::OUString::createFromAscii("SQL_KEYWORD:");
                     rString += ::rtl::OUString::createFromAscii(OSQLParser::TokenIDToStr(_pNode->getTokenID()).getStr());
                     
                     break;}

                case SQL_NODE_COMPARISON:
                    {rString+= ::rtl::OUString::createFromAscii("SQL_COMPARISON:");
                    rString += _pNode->getTokenValue();	// haenge Nodevalue an
                            // und beginne neu Zeile
                    break;}

                case SQL_NODE_NAME:
                    {rString+= ::rtl::OUString::createFromAscii("SQL_NAME:");
                     rString+= ::rtl::OUString::createFromAscii("\"");
                     rString += _pNode->getTokenValue();
                     rString+= ::rtl::OUString::createFromAscii("\"");
                     
                     break;}

                case SQL_NODE_STRING:
                    {rString += ::rtl::OUString::createFromAscii("SQL_STRING:'");
                     rString += _pNode->getTokenValue();
                     break;}

                case SQL_NODE_INTNUM:
                    {rString += ::rtl::OUString::createFromAscii("SQL_INTNUM:");
                     rString += _pNode->getTokenValue();
                     break;}

                case SQL_NODE_APPROXNUM:
                    {rString += ::rtl::OUString::createFromAscii("SQL_APPROXNUM:");
                     rString += _pNode->getTokenValue();
                     break;}

                case SQL_NODE_PUNCTUATION:
                    {rString += ::rtl::OUString::createFromAscii("SQL_PUNCTUATION:");
                    rString += _pNode->getTokenValue();	// haenge Nodevalue an
                    break;}

                case SQL_NODE_AMMSC:
                    {rString += ::rtl::OUString::createFromAscii("SQL_AMMSC:");
                    rString += _pNode->getTokenValue();	// haenge Nodevalue an
                    
                    break;}

                default:
                    OSL_ASSERT("OSQLParser::ShowParseTree: unzulaessiger NodeType");
                    rString += _pNode->getTokenValue();
                }
                _pBox->InsertEntry(rString,_pParent);
            }
        }

    }
#endif // DEBUG

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
using namespace ::com::sun::star::awt;
using namespace ::dbtools;

using namespace ::comphelper;

namespace
{
    void switchDesignModeImpl(OQueryContainerWindow* _pWindow,sal_Bool& _rbDesign)
    {
        if ( !_pWindow->switchView() )
        {
            _rbDesign = !_rbDesign;
            _pWindow->switchView();
        }
    }
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OQueryController::getImplementationName() throw( RuntimeException )
{
    return getImplementationName_Static();
}

//------------------------------------------------------------------------------
::rtl::OUString OQueryController::getImplementationName_Static() throw( RuntimeException )
{
    return ::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.OQueryDesign");
}
//------------------------------------------------------------------------------
Sequence< ::rtl::OUString> OQueryController::getSupportedServiceNames_Static(void) throw( RuntimeException )
{
    Sequence< ::rtl::OUString> aSupported(1);
    aSupported.getArray()[0] = ::rtl::OUString::createFromAscii("com.sun.star.sdb.QueryDesign");
    return aSupported;
}
//-------------------------------------------------------------------------
Sequence< ::rtl::OUString> SAL_CALL OQueryController::getSupportedServiceNames() throw(RuntimeException)
{
    return getSupportedServiceNames_Static();
}
// -------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OQueryController::Create(const Reference<XMultiServiceFactory >& _rxFactory)
{
    return *(new OQueryController(_rxFactory));
}
DBG_NAME(OQueryController);
// -----------------------------------------------------------------------------
OQueryController::OQueryController(const Reference< XMultiServiceFactory >& _rM)
        : OJoinController(_rM)
    ,m_bDesign(sal_False)
    ,m_bDistinct(sal_False)
    ,m_bViewAlias(sal_False)
    ,m_bViewTable(sal_False)
    ,m_bViewFunction(sal_False)
    ,m_bEsacpeProcessing(sal_True)
    ,m_pSqlIterator(NULL)
    ,m_nSplitPos(-1)
    ,m_nVisibleRows(0x400)
    ,m_bCreateView(sal_False)
{
    DBG_CTOR(OQueryController,NULL);
    m_pParseContext = new svxform::OSystemParseContext();
    m_pSqlParser	= new OSQLParser(_rM,m_pParseContext);
    InvalidateAll();
}
// -----------------------------------------------------------------------------
OQueryController::~OQueryController()
{
    DBG_DTOR(OQueryController,NULL);
}
// -----------------------------------------------------------------------------
void OQueryController::deleteIterator()
{
    if(m_pSqlIterator)
    {
        delete m_pSqlIterator->getParseTree();
        m_pSqlIterator->dispose();
        delete m_pSqlIterator;
        m_pSqlIterator = NULL;
    }
}
// -----------------------------------------------------------------------------
void OQueryController::disposing()
{
    deleteIterator();

    delete m_pSqlParser;
    delete m_pParseContext;

    clearFields();
    OTableFields().swap(m_vUnUsedFieldsDesc);

    m_pView		= NULL;

    ::comphelper::disposeComponent(m_xComposer);
    OJoinController::disposing();
}
// -----------------------------------------------------------------------------
void OQueryController::clearFields()
{
    OTableFields().swap(m_vTableFieldDesc);
}
// -----------------------------------------------------------------------------
FeatureState OQueryController::GetState(sal_uInt16 _nId) const
{
    FeatureState aReturn;
    aReturn.bEnabled = sal_True;
        // (disabled automatically)

    switch (_nId)
    {
        case ID_BROWSER_ESACPEPROCESSING:
            aReturn.aState = ::cppu::bool2any(!m_bEsacpeProcessing);
            aReturn.bEnabled = m_pSqlIterator != NULL && !m_bDesign;
            break;
        case ID_RELATION_ADD_RELATION:
            aReturn.bEnabled = isEditable() && m_bDesign && m_vTableData.size() > 1;
            break;
        case ID_BROWSER_SAVEASDOC:
            aReturn.bEnabled = !m_bCreateView && (!m_bDesign || !(m_vTableFieldDesc.empty() || m_vTableData.empty()));
            break;
        case ID_BROWSER_SAVEDOC:
            aReturn.bEnabled = isModified() && (!m_bDesign || !(m_vTableFieldDesc.empty() || m_vTableData.empty()));
            break;
        case SID_PRINTDOCDIRECT:
            break;
        case ID_BROWSER_CUT:
            aReturn.bEnabled = isEditable() && getContainer() && getContainer()->isCutAllowed();
            break;
        case ID_BROWSER_COPY:
            aReturn.bEnabled = getContainer() && getContainer()->isCopyAllowed();
            break;
        case ID_BROWSER_PASTE:
            aReturn.bEnabled = isEditable() && getContainer() && getContainer()->isPasteAllowed();
            break;
        case ID_BROWSER_SQL:
            aReturn.bEnabled = m_bEsacpeProcessing && m_pSqlIterator;
            aReturn.aState = ::cppu::bool2any(m_bDesign);
            break;
        case ID_BROWSER_CLEAR_QUERY:
            aReturn.bEnabled = isEditable() && (m_sStatement.getLength() || !m_vTableData.empty());
            break;
        case ID_BROWSER_QUERY_VIEW_FUNCTIONS:
        case ID_BROWSER_QUERY_VIEW_TABLES:
        case ID_BROWSER_QUERY_VIEW_ALIASES:
            aReturn.aState = ::cppu::bool2any(getContainer() && getContainer()->isSlotEnabled(_nId));
            aReturn.bEnabled = m_bDesign;
            break;
        case ID_BROWSER_QUERY_DISTINCT_VALUES:
            aReturn.bEnabled = m_bDesign && isEditable();
            aReturn.aState = ::cppu::bool2any(m_bDistinct);
            break;
        case ID_BROWSER_QUERY_EXECUTE:
            aReturn.bEnabled = sal_True;
            break;
#ifdef DEBUG
        case ID_EDIT_QUERY_SQL:
            break;
#endif
        case ID_BROWSER_ADDTABLE:
            if ( !m_bDesign )
            {
                aReturn.bEnabled = sal_False;
                break;
            }
            // run through
        default:
            aReturn = OJoinController::GetState(_nId);
            break;
    }
    return aReturn;
}
// -----------------------------------------------------------------------------
void OQueryController::Execute(sal_uInt16 _nId)
{
    switch(_nId)
    {
        case ID_BROWSER_ESACPEPROCESSING:
            m_bEsacpeProcessing = !m_bEsacpeProcessing;
            setModified(sal_True);
            InvalidateFeature(ID_BROWSER_SQL);
            break;
        case ID_BROWSER_SAVEASDOC:
        case ID_BROWSER_SAVEDOC:
            doSaveAsDoc(ID_BROWSER_SAVEASDOC == _nId);
            // check we have a view and if we could saved it correctly
            if(m_bCreateView && !isModified())
                closeTask();
            break;
        case ID_RELATION_ADD_RELATION:
            {
                OJoinDesignView* pView = getJoinView();
                if( pView )
                    static_cast<OQueryTableView*>(pView->getTableView())->createNewConnection();
            }
            break;
        case SID_PRINTDOCDIRECT:
            break;
        case ID_BROWSER_CUT:
            getContainer()->cut();
            break;
        case ID_BROWSER_COPY:
            getContainer()->copy();
            break;
        case ID_BROWSER_PASTE:
            getContainer()->paste();
            break;
        case ID_BROWSER_SQL:
            if(getContainer()->checkStatement())
            {
                try
                {
                    ::rtl::OUString aErrorMsg;
                    m_sStatement = getContainer()->getStatement();
                    if(!m_sStatement.getLength() && m_pSqlIterator)
                    {
                        // change the view of the data
                        delete m_pSqlIterator->getParseTree();
                        m_pSqlIterator->setParseTree(NULL);
                        m_bDesign = !m_bDesign;
                        switchDesignModeImpl(getContainer(),m_bDesign);
                    }
                    else
                    {
                        ::connectivity::OSQLParseNode* pNode = m_pSqlParser->parseTree(aErrorMsg,m_sStatement,m_bDesign);
                        //	m_pParseNode = pNode;
                        if(pNode)
                        {
                            delete m_pSqlIterator->getParseTree();
                            m_pSqlIterator->setParseTree(pNode);
                            m_pSqlIterator->traverseAll();
                            SQLWarning aWarning = m_pSqlIterator->getWarning();
                            if(aWarning.Message.getLength())
                                showError(SQLExceptionInfo(aWarning));
                            else
                            {
                                const OSQLTables& xTabs = m_pSqlIterator->getTables();
                                if( m_pSqlIterator->getStatementType() != SQL_STATEMENT_SELECT && m_pSqlIterator->getStatementType() != SQL_STATEMENT_SELECT_COUNT || xTabs.begin() == xTabs.end())
                                {
                                    ModuleRes aModuleRes(STR_QRY_NOSELECT);
                                    String sTmpStr(aModuleRes);
                                    ::rtl::OUString sError(sTmpStr);
                                    showError(SQLException(sError,NULL,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("S1000")),1000,Any()));
                                }
                                else
                                {
                                    // change the view of the data
                                    m_bDesign = !m_bDesign;
                                    m_sStatement = ::rtl::OUString();
                                    pNode->parseNodeToStr(	m_sStatement,
                                                            getMetaData()); // we don't want any international keywords here
                                    getContainer()->SaveUIConfig();
                                    switchDesignModeImpl(getContainer(),m_bDesign);
                                }
                            }
                        }
                        else
                        {
                            ModuleRes aModuleRes(STR_QRY_SYNTAX);
                            String sTmpStr(aModuleRes);
                            ::rtl::OUString sError(sTmpStr);
                            showError(SQLException(sError,NULL,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("S1000") ),1000,Any()));
                        }
                    }
                }
                catch(SQLException& e)
                {
                    ::dbtools::SQLExceptionInfo aInfo(e);
                    showError(aInfo);
                }
                catch(Exception&)
                {
                }
                if(m_bDesign)
                {
                    InvalidateFeature(ID_BROWSER_ADDTABLE);
                    InvalidateFeature(ID_RELATION_ADD_RELATION);
                }
            }
            break;
        case ID_BROWSER_CLEAR_QUERY:
            {
                getUndoMgr()->EnterListAction( String( ModuleRes(STR_QUERY_UNDO_TABWINDELETE) ), String() );
                getContainer()->clear();
                getUndoMgr()->LeaveListAction();

                m_sStatement = ::rtl::OUString();
                if(m_bDesign)
                    InvalidateFeature(ID_BROWSER_ADDTABLE);
            }
            //	InvalidateFeature(ID_BROWSER_QUERY_EXECUTE);
            break;
        case ID_BROWSER_QUERY_VIEW_FUNCTIONS:
        case ID_BROWSER_QUERY_VIEW_TABLES:
        case ID_BROWSER_QUERY_VIEW_ALIASES:
            getContainer()->setSlotEnabled(_nId,!getContainer()->isSlotEnabled(_nId));
            setModified(sal_True);
            break;
        case ID_BROWSER_QUERY_DISTINCT_VALUES:
            m_bDistinct = !m_bDistinct;
            setModified(sal_True);
            break;
        case ID_BROWSER_QUERY_EXECUTE:
            if ( getContainer()->checkStatement() )
                executeQuery();
            break;
        case ID_QUERY_ZOOM_IN:
            {
//				m_aZoom *= Fraction(1,10);
//				static_cast<OQueryViewSwitch*>(getView())->zoomTableView(m_aZoom);
            }
            break;
        case ID_QUERY_ZOOM_OUT:
            {
//				if(m_aZoom != Fraction(1,1))
//					m_aZoom /= Fraction(1,10);
//				static_cast<OQueryViewSwitch*>(getView())->zoomTableView(m_aZoom);
            }
            break;
#ifdef DEBUG
        case ID_EDIT_QUERY_SQL:
            {
                ::rtl::OUString aErrorMsg;
                m_sStatement = getContainer()->getStatement();
                ::connectivity::OSQLParseNode* pNode = m_pSqlParser->parseTree( aErrorMsg, m_sStatement, m_bDesign );
                if ( pNode )
                {
                    Window* pView = getView();
                    ModalDialog* pWindow = new ModalDialog(pView);
                    pWindow->SetPosSizePixel(Point(0,0),pView->GetSizePixel());
                    SvTreeListBox* pTreeBox = new SvTreeListBox(pWindow);
                    pTreeBox->SetPosSizePixel(Point(0,0),pView->GetSizePixel());

                    insertParseTree(pTreeBox,pNode);
                    
                    pTreeBox->Show();
                    pWindow->Execute();

                    delete pTreeBox;
                    delete pWindow;
                    delete pNode;
                }
                break;
            }
#endif
        default:
            OJoinController::Execute(_nId);
            return; // else we would invalidate twice
    }
    InvalidateFeature(_nId);
}
// -----------------------------------------------------------------------------
void SAL_CALL OQueryController::initialize( const Sequence< Any >& aArguments ) throw(Exception, RuntimeException)
{
    OJoinController::initialize(aArguments);

    PropertyValue aValue;
    const Any* pBegin	= aArguments.getConstArray();
    const Any* pEnd		= pBegin + aArguments.getLength();

    for(;pBegin != pEnd;++pBegin)
    {
        if (!(*pBegin >>= aValue))
            continue;

        if (0 == aValue.Name.compareToAscii(PROPERTY_ACTIVECONNECTION))
        {
            Reference< XConnection > xConn;
            aValue.Value >>= xConn;
            if ( xConn.is() )
                initializeConnection( xConn );
        }
        else if(0 == aValue.Name.compareToAscii(PROPERTY_DATASOURCENAME))
        {
            ::rtl::OUString sDataSource;
            aValue.Value >>= sDataSource;
            initializeDataSourceName( sDataSource );
        }
        else if(0 == aValue.Name.compareToAscii(PROPERTY_CURRENTQUERY))
        {
            aValue.Value >>= m_sName;
        }
        else if(0 == aValue.Name.compareToAscii(PROPERTY_QUERYDESIGNVIEW))
        {
            m_bDesign = ::cppu::any2bool(aValue.Value);
        }
        else if(0 == aValue.Name.compareToAscii(PROPERTY_CREATEVIEW))
        {
            m_bCreateView = ::cppu::any2bool(aValue.Value);
        }
    }

    if ( !ensureConnected( sal_False ) )
    {	// we have no connection so what else should we do
        m_bDesign = sal_False;
        if(m_bCreateView)
        {
            {
                String aMessage(ModuleRes(RID_STR_CONNECTION_LOST));
                ODataView* pWindow = getView();
                InfoBox(pWindow, aMessage).Execute();
            }
            throw SQLException();
        }
    }

    // we need a datasource
    if(isConnected())
    {
        // now we have to check if our database supports views
        if(m_bCreateView)
        {
            // we only supply views when the connection is a XViewsSupplier
            Reference<XViewsSupplier> xViewsSup(getConnection(),UNO_QUERY);
            if(!xViewsSup.is())
            {	// we can't create views so we ask if the user wants to create a query instead
                m_bCreateView = sal_False;
                sal_Bool bClose = sal_False;
                {
                    String aTitle(ModuleRes(STR_QUERYDESIGN_NO_VIEW_SUPPORT));
                    String aMessage(ModuleRes(STR_QUERYDESIGN_NO_VIEW_ASK));
                    ODataView* pWindow = getView();
                    OSQLMessageBox aDlg(pWindow,aTitle, aMessage,WB_YES_NO|WB_DEF_YES,OSQLMessageBox::Query);
                    bClose = aDlg.Execute() == RET_NO;
                }
                if(bClose)
                    throw Exception();
            }
        }
    }

    OSL_ENSURE(getDataSource().is(),"OQueryController::initialize: need a datasource!");

    try
    {
        if(!m_xFormatter.is() && haveDataSource())
        {
            Reference< XNumberFormatsSupplier> xSupplier;
            ::cppu::extractInterface(xSupplier, getDataSource()->getPropertyValue(PROPERTY_NUMBERFORMATSSUPPLIER));
            if(xSupplier.is())
            {
                m_xFormatter = Reference< ::com::sun::star::util::XNumberFormatter >(getORB()
                    ->createInstance(::rtl::OUString::createFromAscii("com.sun.star.util.NumberFormatter")), UNO_QUERY);
                m_xFormatter->attachNumberFormatsSupplier(xSupplier);
            }
            OSL_ENSURE(m_xFormatter.is(),"No NumberFormatter!");
        }
        getContainer()->initialize();
        resetImpl();
        switchDesignModeImpl(getContainer(),m_bDesign);
        getUndoMgr()->Clear();

        if(m_bDesign && !m_sName.getLength())
            Execute(ID_BROWSER_ADDTABLE);
        setModified(sal_False);

        // set the title of the beamer
        Reference<XPropertySet> xProp(m_xCurrentFrame,UNO_QUERY);
        if(xProp.is() && xProp->getPropertySetInfo()->hasPropertyByName(PROPERTY_TITLE))
        {
            ::rtl::OUString sName = m_sName;
            if(!sName.getLength())
            {
                String aName = String(ModuleRes(m_bCreateView ? STR_VIEW_TITLE : STR_QRY_TITLE));
                aName = aName.GetToken(0,' ');
                sName = ::dbtools::createUniqueName(getElements(),aName);
                sName = aName + ::rtl::OUString::createFromAscii(": ") + sName;
            }
            xProp->setPropertyValue(PROPERTY_TITLE,makeAny(sName));
        }
    }
    catch(SQLException& e)
    {
        OSL_ENSURE(sal_False, "OQueryController::initialize: caught an exception!");
        // we caught an exception so we switch to text only mode
        {
            m_bDesign = sal_False;
            getContainer()->initialize();
            ODataView* pWindow = getView();
            OSQLMessageBox(pWindow,e).Execute();
        }
        throw;
    }
}
// -----------------------------------------------------------------------------
void OQueryController::setQueryComposer()
{
    if(isConnected())
    {
        Reference< XSQLQueryComposerFactory >  xFactory(getConnection(), UNO_QUERY);
        OSL_ENSURE(xFactory.is(),"Connection doesn't support a querycomposer");
        if (xFactory.is())
        {
            try
            {
                m_xComposer = xFactory->createQueryComposer();
                getContainer()->setStatement(m_sStatement);
            }
            catch (Exception&)
            {
                m_xComposer = NULL;
            }
            OSL_ENSURE(m_xComposer.is(),"No querycomposer available!");
            Reference<XTablesSupplier> xTablesSup(getConnection(), UNO_QUERY);
            deleteIterator();
            m_pSqlIterator = new ::connectivity::OSQLParseTreeIterator(xTablesSup->getTables(),getMetaData(),NULL,m_pSqlParser);
        }
    }
}
// -----------------------------------------------------------------------------
sal_Bool OQueryController::Construct(Window* pParent)
{
    // TODO: we have to check if we should create the text- or the design- view

    m_pView = new OQueryContainerWindow(pParent,this,m_xMultiServiceFacatory);

    return OSingleDocumentController::Construct(pParent);
}

// -----------------------------------------------------------------------------
OJoinDesignView* OQueryController::getJoinView()
{
    return getContainer()->getDesignView();
}
// -----------------------------------------------------------------------------
void OQueryController::AddSupportedFeatures()
{
    OJoinController::AddSupportedFeatures();
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Copy")]				= ID_BROWSER_COPY;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Cut")]					= ID_BROWSER_CUT;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:Paste")]				= ID_BROWSER_PASTE;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:SaveAs")]				= SID_SAVEASDOC;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/EsacpeProcessing")]	= ID_BROWSER_ESACPEPROCESSING;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ViewFunctions")]	= ID_BROWSER_QUERY_VIEW_FUNCTIONS;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ViewTables")]		= ID_BROWSER_QUERY_VIEW_TABLES;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ViewAliases")]		= ID_BROWSER_QUERY_VIEW_ALIASES;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/DistinctValues")]	= ID_BROWSER_QUERY_DISTINCT_VALUES;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ChangeDesignMode")]	= ID_BROWSER_SQL;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ClearQuery")]		= ID_BROWSER_CLEAR_QUERY;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ExecuteQuery")]		= ID_BROWSER_QUERY_EXECUTE;
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/AddRelation")]		= ID_RELATION_ADD_RELATION;
#ifdef DEBUG
    m_aSupportedFeatures[ ::rtl::OUString::createFromAscii(".uno:DB/ShowParseTree")]	= ID_EDIT_QUERY_SQL;
#endif
}
// -----------------------------------------------------------------------------
ToolBox* OQueryController::CreateToolBox(Window* _pParent)
{
    return new ToolBox(_pParent, ModuleRes(RID_BRW_QUERYDESIGN_TOOLBOX));
}
// -----------------------------------------------------------------------------
void OQueryController::setModified(sal_Bool _bModified)
{
    OJoinController::setModified(_bModified);
    InvalidateFeature(ID_BROWSER_CLEAR_QUERY);
    InvalidateFeature(ID_BROWSER_SAVEASDOC);
    InvalidateFeature(ID_BROWSER_QUERY_EXECUTE);
}
// -----------------------------------------------------------------------------
void SAL_CALL OQueryController::disposing( const EventObject& Source ) throw(RuntimeException)
{
    Reference< XFrame > xSource(Source.Source, UNO_QUERY);
    if (xSource.is() && getContainer())
    {
        if (xSource.get() == m_xCurrentFrame.get())
        {	// our frame is beeing disposed -> close the preview window (if we have one)
            Reference<XFrame> xXFrame( getContainer()->getPreviewFrame());
            ::comphelper::disposeComponent( xXFrame );
        }
        else if (xSource.get() == getContainer()->getPreviewFrame().get())
        {
            getContainer()->disposingPreview();
        }
    }

    OJoinController::disposing(Source);
}
// -----------------------------------------------------------------------------
void OQueryController::reconnect(sal_Bool _bUI)
{
    deleteIterator();
    ::comphelper::disposeComponent(m_xComposer);

    OJoinController::reconnect( _bUI );

    if (isConnected())
    {
        // we hide the add table dialog because the tables in it are from the old connection
        if(m_pAddTabDlg)
            m_pAddTabDlg->Hide();
        InvalidateFeature(ID_BROWSER_ADDTABLE);
        setQueryComposer();
    }
    else
    {
        if(m_bDesign)
        {
            m_bDesign = sal_False;
            // don't call Execute(SQL) because this changes the sql statement
            getContainer()->switchView();
        }
        InvalidateAll();
    }
}
// -----------------------------------------------------------------------------
void OQueryController::Save(const Reference< XObjectOutputStream>& _rxOut)
{
    OJoinController::Save(_rxOut);
    OStreamSection aSection(_rxOut.get());

    // some data
    _rxOut->writeLong(m_nSplitPos);
    _rxOut->writeLong(m_nVisibleRows);

    // the fielddata
    OTableFields::const_iterator aFieldIter = m_vTableFieldDesc.begin();
    sal_Int32 nCount = 0;
    for(;aFieldIter != m_vTableFieldDesc.end();++aFieldIter)
    {
        if(!(*aFieldIter)->IsEmpty())
            ++nCount;
    }
    _rxOut->writeLong(nCount);
    aFieldIter = m_vTableFieldDesc.begin();
    for(;aFieldIter != m_vTableFieldDesc.end();++aFieldIter)
    {
        if(!(*aFieldIter)->IsEmpty())
            (*aFieldIter)->Save(_rxOut);
    }
    _rxOut->writeLong(m_nVisibleRows);
}
// -----------------------------------------------------------------------------
void OQueryController::Load(const Reference< XObjectInputStream>& _rxIn)
{
    OJoinController::Load(_rxIn);
    OStreamSection aSection(_rxIn.get());
    try
    {
        // some data
        m_nSplitPos = _rxIn->readLong();
        m_nVisibleRows = _rxIn->readLong();

        //////////////////////////////////////////////////////////////////////
        // Liste loeschen
        OTableFields().swap(m_vTableFieldDesc);

        sal_Int32 nCount = 0;
        nCount = _rxIn->readLong();
        m_vTableFieldDesc.reserve(nCount);
        for(sal_Int32 j=0;j<nCount;++j)
        {
            if(aSection.available())
            {
                OTableFieldDescRef pData = new OTableFieldDesc();
                pData->Load(_rxIn);
                m_vTableFieldDesc.push_back(pData);
            }
        }
    }
    catch(Exception&)
    {
    }
    if(aSection.available())
        m_nVisibleRows = _rxIn->readLong();
}

// -----------------------------------------------------------------------------
OTableWindowData* OQueryController::createTableWindowData()
{
    return new OQueryTableWindowData();
}
// -----------------------------------------------------------------------------
Reference<XNameAccess> OQueryController::getElements()  const
{
    Reference<XNameAccess> xElements;
    if(m_bCreateView)
    {
        Reference<XViewsSupplier> xConSup(getConnection(),UNO_QUERY);
        if(xConSup.is())
            xElements = xConSup->getViews();
    }
    else
    {
        Reference<XQueriesSupplier> xConSup(getConnection(),UNO_QUERY);
        if(xConSup.is())
            xElements = xConSup->getQueries();
        else
        {
            Reference<XQueryDefinitionsSupplier> xSup(getDataSource(),UNO_QUERY);
            if(xSup.is())
                xElements = xSup->getQueryDefinitions();
        }
    }
    return xElements;
}

//typedef ::cppu::ImplHelper1< XLoadEventListener > OQueryControllerLoadListener_BASE;
//class OQueryControllerLoadListener : public OQueryControllerLoadListener_BASE
//{
//	OQueryController* m_pController;
//public:
//	OQueryControllerLoadListener(OQueryController* _pController) : m_pController(_pController)
//	{
//		OSL_ENSURE(m_pController,"Controller can not be NULL!");
//	}
//	// -----------------------------------------------------------------------------
//	virtual void SAL_CALL disposing( const EventObject& Source ) throw (RuntimeException)
//	{
//	}
//	// -----------------------------------------------------------------------------
//	// XLoadEventListener
//	virtual void SAL_CALL loadFinished( const Reference< XFrameLoader >& aLoader ) throw (RuntimeException)
//	{
//	}
//	// -----------------------------------------------------------------------------
//	virtual void SAL_CALL loadCancelled( const Reference< XFrameLoader >& aLoader ) throw (RuntimeException)
//	{
//		m_pController->Execute(ID_BROWSER_CLOSE);
//	}
//};
// -----------------------------------------------------------------------------
void OQueryController::executeQuery()
{
    // we don't need to check the connection here because we already check the composer
    // which can't live without his connection
    ::rtl::OUString sTranslatedStmt = translateStatement();

    if ( getDataSourceName().getLength() && sTranslatedStmt.getLength() )
    {
        try
        {
            getContainer()->showPreview(m_xCurrentFrame);

//			Reference< XFrame > xBeamer = getContainer()->getPreviewFrame();
//			Reference< XLoadEventListener> xLoadEvtL = new OQueryControllerLoadListener(this);
//			xBeamer->addFrameActionListener( xLoadEvtL );

            URL aWantToDispatch;
            aWantToDispatch.Complete = ::rtl::OUString::createFromAscii(".component:DB/DataSourceBrowser");

            ::rtl::OUString sFrameName = FRAME_NAME_QUERY_PREVIEW;
            //  | FrameSearchFlag::CREATE
            sal_Int32 nSearchFlags = FrameSearchFlag::CHILDREN;

            Reference< XDispatch> xDisp;
            Reference< XDispatchProvider> xProv(m_xCurrentFrame->findFrame(sFrameName,nSearchFlags),UNO_QUERY);
            if(!xProv.is())
            {
                xProv = Reference< XDispatchProvider>(m_xCurrentFrame, UNO_QUERY);
                if (xProv.is())
                    xDisp = xProv->queryDispatch(aWantToDispatch, sFrameName, nSearchFlags);
            }
            else
            {
                xDisp = xProv->queryDispatch(aWantToDispatch, sFrameName, FrameSearchFlag::SELF);
            }
            if (xDisp.is())
            {
                Sequence< PropertyValue> aProps(10);
                aProps[0].Name = PROPERTY_DATASOURCENAME;
                aProps[0].Value <<= getDataSourceName();

                aProps[1].Name = PROPERTY_COMMANDTYPE;
                aProps[1].Value <<= CommandType::COMMAND;

                aProps[2].Name = PROPERTY_COMMAND;
                aProps[2].Value <<= sTranslatedStmt;

                aProps[3].Name = PROPERTY_SHOWTREEVIEW;
                aProps[3].Value = ::cppu::bool2any(sal_False);

                aProps[4].Name = PROPERTY_SHOWTREEVIEWBUTTON;
                aProps[4].Value = ::cppu::bool2any(sal_False);

                aProps[5].Name = PROPERTY_ACTIVECONNECTION;
                aProps[5].Value <<= getConnection();

                aProps[6].Name = PROPERTY_UPDATE_CATALOGNAME;
                aProps[6].Value <<= m_sUpdateCatalogName;

                aProps[7].Name = PROPERTY_UPDATE_SCHEMANAME;
                aProps[7].Value <<= m_sUpdateSchemaName;

                aProps[8].Name = PROPERTY_UPDATE_TABLENAME;
                aProps[8].Value <<= m_sUpdateTableName;

                aProps[9].Name = PROPERTY_USE_ESCAPE_PROCESSING;
                aProps[9].Value = ::cppu::bool2any(m_bEsacpeProcessing);

                xDisp->dispatch(aWantToDispatch, aProps);
                // check the state of the beamer
                // be notified when the beamer frame is closed
                Reference< XComponent >  xComponent(m_xCurrentFrame->findFrame(sFrameName,nSearchFlags), UNO_QUERY);
                if (xComponent.is())
                {
                    OSL_ENSURE(Reference< XFrame >(xComponent, UNO_QUERY).get() == getContainer()->getPreviewFrame().get(),
                        "OQueryController::executeQuery: oops ... which window do I have here?");
                    Reference< XEventListener> xEvtL((::cppu::OWeakObject*)this,UNO_QUERY);
                    xComponent->addEventListener(xEvtL);
                }
            }
            else
            {
                OSL_ENSURE(0,"Couldn't create a beamer window!");
            }
        }
        catch(const Exception&)
        {
            OSL_ENSURE(0,"Couldn't create a beamer window!");
        }
    }
}
// -----------------------------------------------------------------------------
String OQueryController::getMenu() const
{
    return String::CreateFromInt32(RID_QUERY_DESIGN_MAIN_MENU);
}
// -----------------------------------------------------------------------------
sal_Bool OQueryController::askForNewName(const Reference<XNameAccess>& _xElements,sal_Bool _bSaveAs)
{
    sal_Bool bRet = sal_True;
    sal_Bool bNew = 0 == m_sName.getLength();
    bNew = bNew || _bSaveAs || (_xElements.is() && !_xElements->hasByName(m_sName));
    if(bNew)
    {
        Reference<XDatabaseMetaData> xMetaData;
        if(isConnected())
            xMetaData = getMetaData();
        String aDefaultName;
        if(_bSaveAs && !bNew)
            aDefaultName = String(m_sName);
        else
        {
            String aName = String(ModuleRes(m_bCreateView ? STR_VIEW_TITLE : STR_QRY_TITLE));
            aName = aName.GetToken(0,' ');
            if(m_bCreateView && isConnected())
                aDefaultName = ::dbaui::createDefaultName(xMetaData,_xElements,aName);
            else
                aDefaultName = String(::dbtools::createUniqueName(_xElements,aName));
        }


        OSaveAsDlg aDlg(
                getView(), 
                m_bCreateView ? CommandType::TABLE : CommandType::QUERY, 
                _xElements,
                xMetaData, 
                getConnection(),
                aDefaultName,
                _bSaveAs ? SAD_OVERWRITE : SAD_DEFAULT);

        if(bRet = (aDlg.Execute() == RET_OK))
        {
            m_sName = aDlg.getName();
            if(m_bCreateView)
            {
                m_sUpdateCatalogName	= aDlg.getCatalog();
                m_sUpdateSchemaName		= aDlg.getSchema();
            }
        }
        else if(!_bSaveAs)
            m_sName = ::rtl::OUString(); // reset the name because we don't want to save it
    }
    return bRet;
}
// -----------------------------------------------------------------------------
void OQueryController::doSaveAsDoc(sal_Bool _bSaveAs)
{
    OSL_ENSURE(isEditable(),"Slot ID_BROWSER_SAVEDOC should not be enabled!");
    if(!::dbaui::checkDataSourceAvailable(::comphelper::getString(getDataSource()->getPropertyValue(PROPERTY_NAME)),getORB()))
    {
        String aMessage(ModuleRes(STR_DATASOURCE_DELETED));
        String sTitle(ModuleRes(STR_STAT_WARNING));
        OSQLMessageBox aMsg(getView(),sTitle,aMessage);
        aMsg.Execute();
    }
    else
    {
        Reference<XNameAccess> xElements = getElements();
        if(xElements.is())
        {
            if(!getContainer()->checkStatement())
                return;

            ::rtl::OUString sTranslatedStmt = translateStatement();

            if(sTranslatedStmt.getLength())
            {
                sal_Bool bNew = 0 == m_sName.getLength();
                bNew = bNew || _bSaveAs || !xElements->hasByName(m_sName);
                // first we need a name for our query so ask the user
                // did we get a name
                if(askForNewName(xElements,_bSaveAs) && m_sName.getLength())
                {
                    SQLExceptionInfo aInfo;
                    try
                    {
                        Reference<XPropertySet> xProp;
                        if(bNew) // just to make sure the query already exists
                        {
                            if(xElements->hasByName(m_sName))
                            {
                                Reference<XDrop> xNameCont(xElements,UNO_QUERY);
                                if(xNameCont.is())
                                    xNameCont->dropByName(m_sName);
                                else
                                {
                                    Reference<XNameContainer> xCont(xElements,UNO_QUERY);
                                    if(xCont.is())
                                        xCont->removeByName(m_sName);
                                }
                            }

                            Reference<XDataDescriptorFactory> xFact(xElements,UNO_QUERY);
                            if(xFact.is())
                            {
                                xProp = xFact->createDataDescriptor();
                                // to set the name is only allowed when the wuery is new
                                xProp->setPropertyValue(PROPERTY_NAME,makeAny(m_sName));
                            }
                            else
                            {
                                Reference<XSingleServiceFactory> xSingleFac(xElements,UNO_QUERY);
                                OSL_ENSURE(xSingleFac.is(),"No XSingleServiceFactory available!");
                                xProp = Reference<XPropertySet>(xSingleFac->createInstance(),UNO_QUERY);
                            }
                            OSL_ENSURE(xProp.is(),"OQueryController::Execute ID_BROWSER_SAVEDOC: Create query failed!");

                        }
                        else
                        {
                            xElements->getByName(m_sName) >>= xProp;
                        }



                        xProp->setPropertyValue(PROPERTY_COMMAND,makeAny(sTranslatedStmt));

                        // some properties are only valid for a query object
                        if(m_bCreateView)
                        {
                            xProp->setPropertyValue(PROPERTY_CATALOGNAME,makeAny(m_sUpdateCatalogName));
                            xProp->setPropertyValue(PROPERTY_SCHEMANAME,makeAny(m_sUpdateSchemaName));
                        }
                        else
                        {
                            xProp->setPropertyValue(PROPERTY_UPDATE_TABLENAME,makeAny(m_sUpdateTableName));
                            xProp->setPropertyValue(PROPERTY_UPDATE_CATALOGNAME,makeAny(m_sUpdateCatalogName));
                            xProp->setPropertyValue(PROPERTY_UPDATE_SCHEMANAME,makeAny(m_sUpdateSchemaName));
                            xProp->setPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING,::cppu::bool2any(m_bEsacpeProcessing));

                            // now we save the layout information
                            //  create the output stream
                            getContainer()->SaveUIConfig();
                            Sequence< sal_Int8 > aOutputSeq;
                            {
                                Reference< XOutputStream>		xOutStreamHelper = new OSequenceOutputStream(aOutputSeq);
                                Reference< XObjectOutputStream>	xOutStream(getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectOutputStream")),UNO_QUERY);
                                Reference< XOutputStream>	xMarkOutStream(getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableOutputStream")),UNO_QUERY);
                                Reference< XActiveDataSource >(xMarkOutStream,UNO_QUERY)->setOutputStream(xOutStreamHelper);
                                Reference< XActiveDataSource > xOutDataSource(xOutStream, UNO_QUERY);
                                OSL_ENSURE(xOutDataSource.is(),"Couldn't create com.sun.star.io.ObjectOutputStream!");
                                xOutDataSource->setOutputStream(xMarkOutStream);
                                Save(xOutStream);
                            }
                            xProp->setPropertyValue(PROPERTY_LAYOUTINFORMATION,makeAny(aOutputSeq));
                        }

                        if(bNew)
                        {
                            Reference<XAppend> xAppend(xElements,UNO_QUERY);
                            if(xAppend.is())
                            {
                                xAppend->appendByDescriptor(xProp);
//								if(!xElements->hasByName(m_sName))
//								{
//									Reference<XNamed> xName(xProp,UNO_QUERY);
//									if(xName.is()) // it could be that the name changed
//										m_sName = xName->getName();
//								}
//								if(xElements->hasByName(m_sName))
//									xElements->getByName(m_sName) >>= xProp;
                            }
                            else
                            {
                                Reference<XNameContainer> xCont(xElements,UNO_QUERY);
                                if(xCont.is())
                                    xCont->insertByName(m_sName,makeAny(xProp));
                            }

                            if(m_bCreateView)
                            {
                                Reference<XPropertySet> xProp2;
                                if(xElements->hasByName(m_sName))
                                    xElements->getByName(m_sName) >>= xProp2;
                                if(!xProp2.is()) // correct name and try again
                                {
                                    // it can be that someone inserted new data for us
                                    ::rtl::OUString sCatalog,sSchema,sTable,sComposedName;
                                    xProp->getPropertyValue(PROPERTY_CATALOGNAME)	>>= sCatalog;
                                    xProp->getPropertyValue(PROPERTY_SCHEMANAME)	>>= sSchema;
                                    xProp->getPropertyValue(PROPERTY_NAME)			>>= sTable;

                                    ::dbtools::composeTableName(getMetaData(),sCatalog,sSchema,sTable,sComposedName,sal_False);
                                    m_sName = sComposedName;
                                }
                                // now check if our datasource has set a tablefilter and if append the new table name to it
                                ::dbaui::appendToFilter(getConnection(),m_sName,getORB(),getView()); // we are not interessted in the return value
                            }
                        }
                        else
                        {
                            Reference<XFlushable> xFlush(xProp,UNO_QUERY);
                            if(xFlush.is())
                                xFlush->flush();
                        }
                        setModified(sal_False);
                    }
                    catch(SQLContext& e)
                    {
                        m_sName = ::rtl::OUString();
                        aInfo = SQLExceptionInfo(e);
                    }
                    catch(SQLWarning& e)
                    {
                        m_sName = ::rtl::OUString();
                        aInfo = SQLExceptionInfo(e);
                    }
                    catch(SQLException& e)
                    {
                        m_sName = ::rtl::OUString();
                        aInfo = SQLExceptionInfo(e);
                    }
                    catch(Exception&)
                    {
                        m_sName = ::rtl::OUString();
                        OSL_ENSURE(0,"OQueryController::doSaveAsDoc: Query could not be inserted!");
                    }
                    showError(aInfo);
                }
            }
        }
    }
}
// -----------------------------------------------------------------------------
::rtl::OUString OQueryController::translateStatement()
{
    // now set the properties
    m_sStatement = getContainer()->getStatement();
    ::rtl::OUString sTranslatedStmt;
    if(m_sStatement.getLength() && m_xComposer.is() && m_bEsacpeProcessing)
    {
        try
        {
            ::rtl::OUString aErrorMsg;

            ::connectivity::OSQLParseNode* pNode = m_pSqlParser->parseTree( aErrorMsg, m_sStatement, m_bDesign );
            if(pNode)
            {
                pNode->parseNodeToStr(	sTranslatedStmt,
                                        getMetaData());
                delete pNode;
            }
            m_xComposer->setQuery(sTranslatedStmt);
            sTranslatedStmt = m_xComposer->getComposedQuery();
        }
        catch(SQLException& e)
        {
            ::dbtools::SQLExceptionInfo aInfo(e);
            showError(aInfo);
            // an error occured so we clear the statement
            sTranslatedStmt = ::rtl::OUString();
        }
    }
    else if(!m_sStatement.getLength())
    {
        ModuleRes aModuleRes(STR_QRY_NOSELECT);
        String sTmpStr(aModuleRes);
        ::rtl::OUString sError(sTmpStr);
        showError(SQLException(sError,NULL,::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("S1000") ),1000,Any()));
    }
    else
        sTranslatedStmt = m_sStatement;

    return sTranslatedStmt;
}
// -----------------------------------------------------------------------------
short OQueryController::saveModified()
{
    short nRet = RET_YES;
    if(isConnected() && isModified() && (!m_bDesign || !(m_vTableFieldDesc.empty() || m_vTableData.empty())))
    {
        QueryBox aQry(getView(), ModuleRes(m_bCreateView ? QUERY_VIEW_DESIGN_SAVEMODIFIED : QUERY_DESIGN_SAVEMODIFIED));
        nRet = aQry.Execute();
        if(nRet == RET_YES)
        {
            doSaveAsDoc(sal_False);
            nRet = (m_sName.getLength() != 0 && !isModified()) ? RET_YES : RET_CANCEL;
        }
    }
    return nRet;
}
// -----------------------------------------------------------------------------
void OQueryController::resetImpl()
{
    // get command from the query if a query name was supplied
    if(m_sName.getLength())
    {
        OSL_ENSURE(!m_bCreateView,"Can not support a name for a view!");
        Reference<XNameAccess> xQueries = getElements();
        if(xQueries.is())
        {
            Reference<XPropertySet> xProp;
            if(xQueries->hasByName(m_sName) && ::cppu::extractInterface(xProp,xQueries->getByName(m_sName)) && xProp.is())
            {
                xProp->getPropertyValue(PROPERTY_COMMAND) >>= m_sStatement;
                m_bDesign = m_bDesign && (m_bEsacpeProcessing = ::cppu::any2bool(xProp->getPropertyValue(PROPERTY_USE_ESCAPE_PROCESSING)));
                // load the layoutInformation
                try
                {
                    Sequence< sal_Int8 > aInputSequence;
                    xProp->getPropertyValue(PROPERTY_LAYOUTINFORMATION) >>= aInputSequence;
                    {
                        Reference< XInputStream>	   xInStreamHelper = new SequenceInputStream(aInputSequence);; 	// used for wrapping sequence to xinput
                        Reference< XObjectInputStream> xInStream = Reference< XObjectInputStream >(getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectInputStream")),UNO_QUERY);
                        Reference< XInputStream> xMarkInStream = Reference< XInputStream >(getORB()->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableInputStream")),UNO_QUERY);
                        Reference< XActiveDataSink >(xMarkInStream,UNO_QUERY)->setInputStream(xInStreamHelper);
                        Reference< XActiveDataSink >   xInDataSource(xInStream, UNO_QUERY);
                        OSL_ENSURE(xInDataSource.is(),"Couldn't create com.sun.star.io.ObjectInputStream!");
                        xInDataSource->setInputStream(xMarkInStream);
                        Load(xInStream);
                    }
                }
                catch(Exception&)
                {
                }
                setQueryComposer();
                if(m_bEsacpeProcessing)
                {
                    ::rtl::OUString aErrorMsg;
                    ::connectivity::OSQLParseNode* pNode = m_pSqlParser->parseTree(aErrorMsg,m_sStatement,m_bDesign);
                    //	m_pParseNode = pNode;
                    if(pNode)
                    {
                        if(m_pSqlIterator)
                        {
                            delete m_pSqlIterator->getParseTree();
                            m_pSqlIterator->setParseTree(pNode);
                            m_pSqlIterator->traverseAll();
                            SQLWarning aWarning = m_pSqlIterator->getWarning();
                            if(aWarning.Message.getLength())
                            {
                                showError(SQLExceptionInfo(aWarning));
                                m_bDesign = sal_False;
                            }
                        }
                        else
                        {
                            delete pNode;
                            m_bDesign = sal_False;
                        }
                    }
                    else
                    {
                        String aTitle(ModuleRes(STR_SVT_SQL_SYNTAX_ERROR));
                        OSQLMessageBox aDlg(getView(),aTitle,aErrorMsg);
                        aDlg.Execute();
                        m_bDesign = sal_False; // the statement can't be parsed so we show the text view
                    }
                }
            }
        }

    }
    if(!m_pSqlIterator)
        setQueryComposer();
    OSL_ENSURE(m_pSqlIterator,"No SQLIterator set!");

    getContainer()->setNoneVisbleRow(m_nVisibleRows);
}
// -----------------------------------------------------------------------------
void OQueryController::reset()
{
    resetImpl();
    getContainer()->reset();
    getUndoMgr()->Clear();
}
// -----------------------------------------------------------------------------
} // namespace dbaui
// -----------------------------------------------------------------------------
