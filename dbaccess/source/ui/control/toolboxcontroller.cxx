/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"
#ifndef DBACCESS_TOOLBOXCONTROLLER_HXX
#include "toolboxcontroller.hxx"
#endif
#ifndef _COM_SUN_STAR_UI_IMAGETYPE_HPP_
#include <com/sun/star/ui/ImageType.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XDISPATCHPROVIDER_HPP_
#include <com/sun/star/frame/XDispatchProvider.hpp>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _SV_MENU_HXX
#include <vcl/menu.hxx>
#endif
#ifndef _COM_SUN_STAR_UI_XUICONFIGURATIONMANAGER_HPP_
#include <com/sun/star/ui/XUIConfigurationManager.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XMODULEUICONFIGURATIONMANAGERSUPPLIER_HPP_
#include <com/sun/star/ui/XModuleUIConfigurationManagerSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XIMAGEMANAGER_HPP_
#include <com/sun/star/ui/XImageManager.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_IMAGETYPE_HPP_
#include <com/sun/star/ui/ImageType.hpp>
#endif
#ifndef _COM_SUN_STAR_GRAPHIC_XGRAPHIC_HPP_
#include <com/sun/star/graphic/XGraphic.hpp>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _SV_TOOLBOX_HXX
#include <vcl/toolbox.hxx>
#endif
#ifndef _DBU_RESOURCE_HRC_
#include "dbu_resource.hrc"
#endif
#ifndef INCLUDED_SVTOOLS_MISCOPT_HXX
#include <svtools/miscopt.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_MODULEOPTIONS_HXX
#include <unotools/moduleoptions.hxx>
#endif
#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif
#ifndef INCLUDED_SVTOOLS_MENUOPTIONS_HXX
#include <svtools/menuoptions.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif


extern "C" void SAL_CALL createRegistryInfo_OToolboxController()
{
    static ::dbaui::OMultiInstanceAutoRegistration< ::dbaui::OToolboxController> aAutoRegistration;
}
namespace dbaui
{
    using namespace svt;
    using namespace ::com::sun::star::graphic;
    using namespace com::sun::star::uno;
    using namespace com::sun::star::beans;
    using namespace com::sun::star::lang;
    using namespace ::com::sun::star::frame;
    using namespace ::com::sun::star::util;
    using namespace ::com::sun::star::ui;

    namespace
    {
        void lcl_copy(Menu* _pMenu,USHORT _nMenuId,USHORT _nMenuPos,ToolBox* _pToolBox,USHORT _nToolId,const ::rtl::OUString& _sCommand)
        {
            if ( _pMenu->GetItemType(_nMenuPos) != MENUITEM_STRING )
                _pToolBox->SetItemImage(_nToolId, _pMenu->GetItemImage(_nMenuId));
            _pToolBox->SetItemCommand( _nToolId, _sCommand);
            _pToolBox->SetHelpId(_nToolId, _pMenu->GetHelpId(_nMenuId));
            _pToolBox->SetHelpText(_nToolId, _pMenu->GetHelpText(_nMenuId));
            _pToolBox->SetQuickHelpText(_nToolId, _pMenu->GetTipHelpText(_nMenuId));
            _pToolBox->SetItemText(_nToolId, _pMenu->GetItemText(_nMenuId));
        }
    }

    OToolboxController::OToolboxController(const Reference< XMultiServiceFactory >& _rxORB)
        : m_nToolBoxId(1)
    {
        osl_incrementInterlockedCount(&m_refCount);
        m_xServiceManager = _rxORB;
        osl_decrementInterlockedCount(&m_refCount);

    }
    // -----------------------------------------------------------------------------
    IMPLEMENT_SERVICE_INFO1_STATIC(OToolboxController,"com.sun.star.sdb.ApplicationToolboxController","com.sun.star.frame.ToolboxController")
    // -----------------------------------------------------------------------------
    // XInterface
    Any SAL_CALL OToolboxController::queryInterface( const Type& _rType ) throw (RuntimeException)
    {
        Any aReturn = ToolboxController::queryInterface(_rType);
        if (!aReturn.hasValue())
            aReturn = TToolboxController_BASE::queryInterface(_rType);
        return aReturn;
    }
    // -----------------------------------------------------------------------------
    void SAL_CALL OToolboxController::acquire() throw ()
    {
        ToolboxController::acquire();
    }
    // -----------------------------------------------------------------------------
    void SAL_CALL OToolboxController::release() throw ()
    {
        ToolboxController::release();
    }
    // -----------------------------------------------------------------------------
    void SAL_CALL OToolboxController::initialize( const Sequence< Any >& _rArguments ) throw (Exception, RuntimeException)
    {
        ToolboxController::initialize(_rArguments);
        vos::OGuard aSolarMutexGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard(m_aMutex);

        if ( m_aCommandURL.equalsAscii(".uno:DBNewForm") )
        {
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewForm"))           ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewView"))           ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewViewSQL"))        ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewQuery"))          ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewQuerySql"))       ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewReport"))			,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewReportAutoPilot")),sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBNewTable"))          ,sal_True));
        }
        else
        {
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:Refresh"))         ,sal_True));
            m_aStates.insert(TCommandState::value_type(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(".uno:DBRebuildData"))   ,sal_True));
        }

        TCommandState::iterator aIter = m_aStates.begin();
        TCommandState::iterator aEnd = m_aStates.end();
        for (; aIter != aEnd; ++aIter)
            addStatusListener(aIter->first);

        ToolBox*    pToolBox = static_cast<ToolBox*>(VCLUnoHelper::GetWindow(getParent()));
        if ( pToolBox )
        {
            USHORT nCount = pToolBox->GetItemCount();
            for (USHORT nPos = 0; nPos < nCount; ++nPos)
            {
                USHORT nItemId = pToolBox->GetItemId(nPos);
                if ( pToolBox->GetItemCommand(nItemId) == String(m_aCommandURL) )
                {
                    m_nToolBoxId = nItemId;
                    break;
                }
            }

            // check if paste special is allowed, when not don't add DROPDOWN
            pToolBox->SetItemBits(m_nToolBoxId,pToolBox->GetItemBits(m_nToolBoxId) | TIB_DROPDOWN);
        }
    }
    // -----------------------------------------------------------------------------
    void SAL_CALL OToolboxController::statusChanged( const FeatureStateEvent& Event ) throw ( RuntimeException )
    {
        vos::OGuard aSolarMutexGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard(m_aMutex);
        TCommandState::iterator aFind = m_aStates.find( Event.FeatureURL.Complete );
        if ( aFind != m_aStates.end() )
        {
            aFind->second = Event.IsEnabled;
            if ( m_aCommandURL == aFind->first && !Event.IsEnabled )
            {
                ::std::auto_ptr<PopupMenu> pMenu = getMenu();
                USHORT nCount = pMenu->GetItemCount();
                for (USHORT i = 0; i < nCount; ++i)
                {
                    USHORT nItemId = pMenu->GetItemId(i);
                    aFind = m_aStates.find(pMenu->GetItemCommand(nItemId));
                    if ( aFind != m_aStates.end() && aFind->second )
                    {
                        m_aCommandURL = aFind->first;

                        ToolBox* pToolBox = static_cast<ToolBox*>(VCLUnoHelper::GetWindow(getParent()));
                        lcl_copy(pMenu.get(),nItemId,i,pToolBox,m_nToolBoxId, m_aCommandURL);
                        break;
                    }
                }
            }
        }
    }
    // -----------------------------------------------------------------------------
    ::std::auto_ptr<PopupMenu> OToolboxController::getMenu()
    {
        ::std::auto_ptr<PopupMenu> pMenu;
        if ( m_aStates.size() > 2 )
        {
            pMenu.reset( new PopupMenu( ModuleRes( RID_MENU_APP_NEW ) ) );

            sal_Bool bHighContrast = isHighContrast();

            try
            {
                Reference<XModuleUIConfigurationManagerSupplier> xModuleCfgMgrSupplier(getServiceManager()->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.ui.ModuleUIConfigurationManagerSupplier"))),UNO_QUERY);
                Reference<XUIConfigurationManager> xUIConfigMgr = xModuleCfgMgrSupplier->getUIConfigurationManager(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.OfficeDatabaseDocument")));
                Reference<XImageManager> xImageMgr(xUIConfigMgr->getImageManager(),UNO_QUERY);


                short nImageType = hasBigImages() ? ImageType::SIZE_LARGE : ImageType::SIZE_DEFAULT;
                if ( bHighContrast )
                    nImageType |= ImageType::COLOR_HIGHCONTRAST;

                Sequence< ::rtl::OUString> aSeq(1);
                USHORT nCount = pMenu->GetItemCount();
                for (USHORT nPos = 0; nPos < nCount; ++nPos)
                {
                    if ( pMenu->GetItemType( nPos ) == MENUITEM_SEPARATOR )
                        continue;

                    USHORT nItemId = pMenu->GetItemId(nPos);
                    aSeq[0] = pMenu->GetItemCommand(nItemId);
                    Sequence< Reference<XGraphic> > aImages = xImageMgr->getImages(nImageType,aSeq);

                    Image aImage(aImages[0]);
                    pMenu->SetItemImage(nItemId,aImage);
                    TCommandState::iterator aFind = m_aStates.find( aSeq[0] );
                    if ( aFind != m_aStates.end() )
                    {
                        pMenu->EnableItem(nItemId,aFind->second);
                    }
                }
            }
            catch(const Exception&)
            {
                DBG_UNHANDLED_EXCEPTION();
            }
        }
        else
        {
            pMenu.reset( new PopupMenu( ModuleRes( RID_MENU_REFRESH_DATA ) ) );
        }
        return pMenu;
    }
    // -----------------------------------------------------------------------------
    Reference< ::com::sun::star::awt::XWindow > SAL_CALL OToolboxController::createPopupWindow() throw (RuntimeException)
    {
        // execute the menu
        vos::OGuard aSolarMutexGuard( Application::GetSolarMutex() );
        ::osl::MutexGuard aGuard(m_aMutex);

        ToolBox* pToolBox = static_cast<ToolBox*>(VCLUnoHelper::GetWindow(getParent()));
        ::std::auto_ptr<PopupMenu> pMenu = getMenu();

        USHORT nSelected = pMenu->Execute(pToolBox, pToolBox->GetItemRect( m_nToolBoxId ),POPUPMENU_EXECUTE_DOWN);
        // "cleanup" the toolbox state
        Point aPoint = pToolBox->GetItemRect( m_nToolBoxId ).TopLeft();
        MouseEvent aLeave( aPoint, 0, MOUSE_LEAVEWINDOW | MOUSE_SYNTHETIC );
        pToolBox->MouseMove( aLeave );
        pToolBox->SetItemDown( m_nToolBoxId, sal_False);

        if ( nSelected )
        {
            m_aCommandURL = pMenu->GetItemCommand(nSelected);
            lcl_copy(pMenu.get(),nSelected,pMenu->GetItemPos(nSelected),pToolBox,m_nToolBoxId, m_aCommandURL);

            Reference<XDispatch> xDispatch = m_aListenerMap.find(m_aCommandURL)->second;
            if ( xDispatch.is() )
            {
                URL aUrl;
                Sequence < PropertyValue > aArgs;
                aUrl.Complete = m_aCommandURL;
                OSL_ENSURE(aUrl.Complete.getLength(),"Command is empty!");
                if ( getURLTransformer().is() )
                    getURLTransformer()->parseStrict(aUrl);
                xDispatch->dispatch(aUrl,aArgs);

            }
        }
        return Reference< ::com::sun::star::awt::XWindow >();
    }
    // -----------------------------------------------------------------------------
    // -----------------------------------------------------------------------------
//..........................................................................
} // dbaui
//..........................................................................


