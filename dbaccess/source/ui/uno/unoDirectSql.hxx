/*************************************************************************
 *
 *  $RCSfile: unoDirectSql.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: obo $ $Date: 2005-03-18 10:12:21 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef DBAUI_UNODIRECTSQL_HXX
#define DBAUI_UNODIRECTSQL_HXX

#ifndef _SVT_GENERICUNODIALOG_HXX_
#include <svtools/genericunodialog.hxx>
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSER_HPP_ 
#include <com/sun/star/sdb/XSQLQueryComposer.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_ 
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROWSET_HPP_ 
#include <com/sun/star/sdbc/XRowSet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

    //=====================================================================
    //= ODirectSQLDialog
    //=====================================================================
    class ODirectSQLDialog;
    typedef ::svt::OGenericUnoDialog										ODirectSQLDialog_BASE;
    typedef ::comphelper::OPropertyArrayUsageHelper< ODirectSQLDialog >		ODirectSQLDialog_PBASE;

    class ODirectSQLDialog
            :public ODirectSQLDialog_BASE
            ,public ODirectSQLDialog_PBASE
            ,public OModuleClient
    {
        ::rtl::OUString m_sInitialSelection;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > m_xActiveConnection;
    protected:
        ODirectSQLDialog(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB);
        virtual ~ODirectSQLDialog();

    public:
        DECLARE_IMPLEMENTATION_ID( );

        DECLARE_SERVICE_INFO_STATIC( );

        DECLARE_PROPERTYCONTAINER_DEFAULTS( );

    protected:
        // OGenericUnoDialog overridables
        virtual Dialog*	createDialog(Window* _pParent);
        virtual void implInitialize(const com::sun::star::uno::Any& _rValue);
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // DBAUI_UNODIRECTSQL_HXX

