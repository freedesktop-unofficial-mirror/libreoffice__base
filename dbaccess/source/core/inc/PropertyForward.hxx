/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: PropertyForward.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 13:33:28 $
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
#ifndef DBA_PROPERTYSETFORWARD_HXX
#define DBA_PROPERTYSETFORWARD_HXX

#ifndef _COM_SUN_STAR_BEANS_XPROPERTYCHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif

#include <vector>

//........................................................................
namespace dbaccess
{
//........................................................................
    typedef	::cppu::WeakImplHelper1	<	::com::sun::star::beans::XPropertyChangeListener
                                    >	OPropertyForward_Base;
    class OPropertyForward : public ::comphelper::OBaseMutex
                            ,public OPropertyForward_Base
    {
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>		m_xSource;
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>		m_xDest;
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo>	m_xDestInfo;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>		m_xDestContainer;
        ::rtl::OUString	m_sName;
        sal_Bool		m_bInInsert;
    protected:
        virtual ~OPropertyForward();
    public:
        OPropertyForward(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xSource
                        ,const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _xDestContainer
                        ,const ::rtl::OUString& _sName
                        ,const ::std::vector< ::rtl::OUString>& _aPropertyList = ::std::vector< ::rtl::OUString>());

        // ::com::sun::star::beans::XPropertyChangeListener
        virtual void SAL_CALL propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& evt ) throw(::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::lang::XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& _rSource ) throw (::com::sun::star::uno::RuntimeException);

        void setDefinition(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xDest);
    };
//........................................................................
}	// namespace dbaccess
//........................................................................
#endif // DBA_PROPERTYSETFORWARD_HXX

