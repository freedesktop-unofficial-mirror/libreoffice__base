/*************************************************************************
 *
 *  $RCSfile: tablecontainer.hxx,v $
 *
 *  $Revision: 1.23 $
 *
 *  last change: $Author: rt $ $Date: 2004-10-22 09:00:56 $
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
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

#ifndef _DBA_CORE_TABLECONTAINER_HXX_
#define _DBA_CORE_TABLECONTAINER_HXX_

#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XENUMERATIONACCESS_HPP_
#include <com/sun/star/container/XEnumerationAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XREFRESHABLE_HPP_
#include <com/sun/star/util/XRefreshable.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef DBACCESS_CORE_FILTERED_CONTAINER_HXX
#include "FilteredContainer.hxx"
#endif
#ifndef DBA_CORE_WARNINGS_HXX
#include "warnings.hxx"
#endif
#ifndef DBA_CORE_REFRESHLISTENER_HXX
#include "RefreshListener.hxx"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif

namespace dbaccess
{
    typedef ::cppu::ImplHelper1< ::com::sun::star::container::XContainerListener> OTableContainer_Base;

    //==========================================================================
    //= OTableContainer
    //==========================================================================
    class OTable;
    class OTableContainer;
    class OContainerMediator;
    
    class OTableContainer :  public OFilteredContainer,
                             public OTableContainer_Base
    {
    protected:
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >	m_xTableDefinitions;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainerListener >	m_xTableMediator;
        OContainerMediator*		m_pMediator;
        sal_Bool				m_bInAppend;				// true when we are in append mode
        sal_Bool				m_bInDrop;					// set when we are in the drop method
        

        // OFilteredContainer
        virtual void addMasterContainerListener();
        virtual void removeMasterContainerListener();
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > getTableTypeFilter(const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rTableTypeFilter) const;

        // ::connectivity::sdbcx::OCollection
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNamed >		createObject(const ::rtl::OUString& _rName);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >	createEmptyObject();
        virtual void appendObject( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& descriptor );
        virtual void dropObject(sal_Int32 _nPos,const ::rtl::OUString _sElementName);

        virtual sal_Bool isNameValid(const ::rtl::OUString& _rName,
                                    const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rTableFilter,
                                    const ::com::sun::star::uno::Sequence< ::rtl::OUString >& _rTableTypeFilter,
                                    const ::std::vector< WildCard >& _rWCSearch) const;
        virtual void SAL_CALL disposing();

        virtual void notifyDataSourceModified();

    public:
        /** ctor of the container. The parent has to support the <type scope="com::sun::star::sdbc">XConnection</type>
            interface.<BR>
            @param			_rParent			the object which acts as parent for the container.
                                                all refcounting is rerouted to this object
            @param			_rMutex				the access safety object of the parent
            @param			_rTableFilter		restricts the visible tables by name
            @param			_rTableTypeFilter	restricts the visible tables by type
            @see			construct
        */
        OTableContainer( ::cppu::OWeakObject& _rParent,
            ::osl::Mutex& _rMutex,
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _xCon,
            sal_Bool _bCase,
            const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer >&	_xTableDefinitions,
            IRefreshListener*	_pRefreshListener = NULL,
            IWarningsContainer* _pWarningsContainer = NULL
            );

        virtual ~OTableContainer();
        
        inline virtual void SAL_CALL acquire() throw(){ OFilteredContainer::acquire();}
        inline virtual void SAL_CALL release() throw(){ OFilteredContainer::release();}
    // ::com::sun::star::lang::XServiceInfo
        DECLARE_SERVICE_INFO();

        // XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw (::com::sun::star::uno::RuntimeException);
        // XContainerListener
        virtual void SAL_CALL elementInserted( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL elementRemoved( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL elementReplaced( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);

    };
}
#endif // _DBA_CORE_TABLECONTAINER_HXX_


