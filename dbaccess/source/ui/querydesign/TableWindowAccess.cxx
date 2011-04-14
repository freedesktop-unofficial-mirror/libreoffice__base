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
#include "precompiled_dbui.hxx"
#ifndef DBACCESS_TABLEWINDOWACCESS_HXX
#include "TableWindowAccess.hxx"
#endif
#ifndef DBACCESS_JACCESS_HXX
#include "JAccess.hxx"
#endif
#ifndef DBAUI_TABLEWINDOW_HXX
#include "TableWindow.hxx"
#endif
#ifndef DBAUI_TABLEWINDOWLISTBOX_HXX
#include "TableWindowListBox.hxx"
#endif
#ifndef DBAUI_JOINDESIGNVIEW_HXX
#include "JoinDesignView.hxx"
#endif
#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEROLE_HPP_
#include <com/sun/star/accessibility/AccessibleRole.hpp>
#endif												 
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLERELATIONTYPE_HPP_
#include <com/sun/star/accessibility/AccessibleRelationType.hpp>
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLESTATETYPE_HPP_
#include <com/sun/star/accessibility/AccessibleStateType.hpp>
#endif
#ifndef _COM_SUN_STAR_ACCESSIBILITY_ACCESSIBLEEVENTID_HPP_
#include <com/sun/star/accessibility/AccessibleEventId.hpp>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _DBU_QRY_HRC_
#include "dbu_qry.hrc"
#endif


namespace dbaui
{
    using namespace ::com::sun::star::accessibility;
    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::lang;
    //	using namespace ::com::sun::star::awt;
    using namespace ::com::sun::star;

    OTableWindowAccess::OTableWindowAccess(OTableWindow* _pTable)
        :VCLXAccessibleComponent(_pTable->GetComponentInterface().is() ? _pTable->GetWindowPeer() : NULL) 
        ,m_pTable(_pTable)
    {
    }
    // -----------------------------------------------------------------------------
    void SAL_CALL OTableWindowAccess::disposing()
    {
        m_pTable = NULL;
        VCLXAccessibleComponent::disposing();
    }
    // -----------------------------------------------------------------------------
    void OTableWindowAccess::ProcessWindowEvent( const VclWindowEvent& rVclWindowEvent )
    {
        if ( rVclWindowEvent.GetId() == VCLEVENT_OBJECT_DYING )
        {
            ::osl::MutexGuard aGuard( m_aMutex );
            m_pTable = NULL;
        }

        VCLXAccessibleComponent::ProcessWindowEvent( rVclWindowEvent );
    }
    // -----------------------------------------------------------------------------
    Any SAL_CALL OTableWindowAccess::queryInterface( const Type& aType ) throw (RuntimeException)
    {
        Any aRet(VCLXAccessibleComponent::queryInterface( aType ));
        return aRet.hasValue() ? aRet : OTableWindowAccess_BASE::queryInterface( aType );
    }
    // -----------------------------------------------------------------------------
    Sequence< Type > SAL_CALL OTableWindowAccess::getTypes(  ) throw (RuntimeException)
    {
        return ::comphelper::concatSequences(VCLXAccessibleComponent::getTypes(),OTableWindowAccess_BASE::getTypes());
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString SAL_CALL OTableWindowAccess::getImplementationName() throw(RuntimeException)
    {
        return getImplementationName_Static();
    }
    // -----------------------------------------------------------------------------
    Sequence< ::rtl::OUString > SAL_CALL OTableWindowAccess::getSupportedServiceNames() throw(RuntimeException)
    {
        return getSupportedServiceNames_Static();
    }
    // -----------------------------------------------------------------------------
    // XServiceInfo - static methods
    Sequence< ::rtl::OUString > OTableWindowAccess::getSupportedServiceNames_Static(void) throw( RuntimeException )
    {
        Sequence< ::rtl::OUString > aSupported(2);
        aSupported[0] = ::rtl::OUString::createFromAscii("com.sun.star.accessibility.Accessible");
        aSupported[1] = ::rtl::OUString::createFromAscii("com.sun.star.accessibility.AccessibleContext");
        return aSupported;
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString OTableWindowAccess::getImplementationName_Static(void) throw( RuntimeException )
    {
        return ::rtl::OUString::createFromAscii("org.openoffice.comp.dbu.TableWindowAccessibility");
    }
    // -----------------------------------------------------------------------------
    // XAccessibleContext
    sal_Int32 SAL_CALL OTableWindowAccess::getAccessibleChildCount(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        sal_Int32 nCount = 0;
        if(m_pTable)
        {
            if(m_pTable->GetTitleCtrl())
                ++nCount;
            if(m_pTable->GetListBox())
                ++nCount;
        }
        return nCount;
    }
    // -----------------------------------------------------------------------------
    Reference< XAccessible > SAL_CALL OTableWindowAccess::getAccessibleChild( sal_Int32 i ) throw (IndexOutOfBoundsException,RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        Reference< XAccessible > aRet;
        if(m_pTable)
        {
            switch(i)
            {
                case 0:
                    if(m_pTable->GetTitleCtrl())
                    {
                        aRet = m_pTable->GetTitleCtrl()->GetAccessible();
                        break;
                    } // fall through if title control does not exist
                case 1:
                    if(m_pTable->GetListBox())
                        aRet = m_pTable->GetListBox()->GetAccessible();
                    break;
                default:
                    throw IndexOutOfBoundsException();
            }
        }
        return aRet;
    }
    // -----------------------------------------------------------------------------
    sal_Int32 SAL_CALL OTableWindowAccess::getAccessibleIndexInParent(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        sal_Int32 nIndex = -1;
        if( m_pTable )
        {
            // search the postion of our table window in the table window map
            OJoinTableView::OTableWindowMap* pMap = m_pTable->getTableView()->GetTabWinMap();
            OJoinTableView::OTableWindowMap::iterator aIter = pMap->begin();
            OJoinTableView::OTableWindowMap::iterator aEnd = pMap->end();
            for (nIndex = 0; aIter != aEnd && aIter->second != m_pTable; ++nIndex,++aIter)
                ;
            nIndex = aIter != aEnd ? nIndex : -1;
        }
        return nIndex;
    }
    // -----------------------------------------------------------------------------
    sal_Int16 SAL_CALL OTableWindowAccess::getAccessibleRole(  ) throw (RuntimeException)
    {
        return AccessibleRole::PANEL; // ? or may be an AccessibleRole::WINDOW
    }
    // -----------------------------------------------------------------------------
    Reference< XAccessibleRelationSet > SAL_CALL OTableWindowAccess::getAccessibleRelationSet(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        return this;
    }
    // -----------------------------------------------------------------------------
    // XAccessibleComponent
    Reference< XAccessible > SAL_CALL OTableWindowAccess::getAccessibleAtPoint( const awt::Point& _aPoint ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        Reference< XAccessible > aRet;
        if( m_pTable )
        {
            Point aPoint(_aPoint.X,_aPoint.Y);
            Rectangle aRect(m_pTable->GetDesktopRectPixel());
            if( aRect.IsInside(aPoint) )
                aRet = this;
            else if( m_pTable->GetListBox()->GetDesktopRectPixel().IsInside(aPoint))
                aRet = m_pTable->GetListBox()->GetAccessible();
        }
        return aRet;
    }
    // -----------------------------------------------------------------------------
    Reference< XAccessible > OTableWindowAccess::getParentChild(sal_Int32 _nIndex)
    {
        Reference< XAccessible > xReturn;
        Reference< XAccessible > xParent = getAccessibleParent();
        if ( xParent.is() )
        {
            Reference< XAccessibleContext > xParentContext = xParent->getAccessibleContext();
            if ( xParentContext.is() )
            {
                xReturn = xParentContext->getAccessibleChild(_nIndex);
            }
        }
        return xReturn;
    }	
    // -----------------------------------------------------------------------------

    sal_Int32 SAL_CALL OTableWindowAccess::getRelationCount(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        return m_pTable ? m_pTable->getTableView()->getConnectionCount(m_pTable) : sal_Int32(0);
    }
    // -----------------------------------------------------------------------------
    AccessibleRelation SAL_CALL OTableWindowAccess::getRelation( sal_Int32 nIndex ) throw (IndexOutOfBoundsException, RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        if( nIndex < 0 || nIndex >= getRelationCount() )
            throw IndexOutOfBoundsException();

        AccessibleRelation aRet;
        if( m_pTable )
        {
            OJoinTableView* pView = m_pTable->getTableView();
            ::std::vector<OTableConnection*>::const_iterator aIter = pView->getTableConnections(m_pTable) + nIndex;
            aRet.TargetSet.realloc(1);
            aRet.TargetSet[0] = getParentChild(aIter - pView->getTableConnections()->begin());
            aRet.RelationType = AccessibleRelationType::CONTROLLER_FOR;
        }
        return aRet;
    }
    // -----------------------------------------------------------------------------
    sal_Bool SAL_CALL OTableWindowAccess::containsRelation( sal_Int16 aRelationType ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        return		AccessibleRelationType::CONTROLLER_FOR == aRelationType 
                &&	m_pTable && m_pTable->getTableView()->ExistsAConn(m_pTable);
    }
    // -----------------------------------------------------------------------------
    AccessibleRelation SAL_CALL OTableWindowAccess::getRelationByType( sal_Int16 aRelationType ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        if( AccessibleRelationType::CONTROLLER_FOR == aRelationType && m_pTable)
        {
            OJoinTableView* pView = m_pTable->getTableView();
            const ::std::vector<OTableConnection*>* pConnectionList = pView->getTableConnections();
            
            ::std::vector<OTableConnection*>::const_iterator aIter = pView->getTableConnections(m_pTable);
            ::std::vector<OTableConnection*>::const_iterator aEnd = pConnectionList->end();
            ::std::vector< Reference<XInterface> > aRelations;
            aRelations.reserve(5); // just guessing
            for (; aIter != aEnd ; ++aIter )
                aRelations.push_back(getParentChild(aIter - pConnectionList->begin()));
            
            Reference<XInterface> *pRelations = aRelations.empty() ? 0 : &aRelations[0];
            Sequence< Reference<XInterface> > aSeq(pRelations, aRelations.size());
            return AccessibleRelation(AccessibleRelationType::CONTROLLER_FOR,aSeq);
        }
        return AccessibleRelation();
    }
    // -----------------------------------------------------------------------------
    sal_Bool OTableWindowAccess::isEditable() const
    {
        return m_pTable && !m_pTable->getTableView()->getDesignView()->getController().isReadOnly();
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString SAL_CALL OTableWindowAccess::getTitledBorderText(  ) throw (RuntimeException)
    {
        return getAccessibleName(  );
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString SAL_CALL OTableWindowAccess::getAccessibleName(  ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex  );
        ::rtl::OUString sAccessibleName;
        if ( m_pTable )
            sAccessibleName = m_pTable->getTitle();
        return sAccessibleName;
    }
    // -----------------------------------------------------------------------------
    Reference< XAccessibleContext > SAL_CALL OTableWindowAccess::getAccessibleContext(  ) throw (::com::sun::star::uno::RuntimeException)
    {
        return this;
    }
    // -----------------------------------------------------------------------------

}
// -----------------------------------------------------------------------------

