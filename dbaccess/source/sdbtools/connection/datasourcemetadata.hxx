/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: datasourcemetadata.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2006-07-10 15:19:34 $
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

#ifndef DBACCESS_DATASOURCEMETADATA_HXX
#define DBACCESS_DATASOURCEMETADATA_HXX

#ifndef DBACCESS_CONNECTION_DEPENDENT_HXX
#include "connectiondependent.hxx"
#endif

/** === begin UNO includes === **/
#ifndef _COM_SUN_STAR_SDB_TOOLS_XDATASOURCEMETADATA_HPP_
#include <com/sun/star/sdb/tools/XDataSourceMetaData.hpp>
#endif
/** === end UNO includes === **/

#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

#include <memory>

//........................................................................
namespace sdbtools
{
//........................................................................

    //====================================================================
    //= DataSourceMetaData
    //====================================================================
    typedef ::cppu::WeakImplHelper1 <   ::com::sun::star::sdb::tools::XDataSourceMetaData
                                    >   DataSourceMetaData_Base;
    struct DataSourceMetaData_Impl;
    /** default implementation for XDataSourceMetaData
    */
    class DataSourceMetaData    :public DataSourceMetaData_Base
                                ,public ConnectionDependentComponent
    {
    private:
        ::std::auto_ptr< DataSourceMetaData_Impl >   m_pImpl;

    public:
        /** constructs the instance
            @param  _rxConnection
                the connection to work with. Will be held weak. Must not be <NULL/>.
            @throws ::com::sun::star::lang::NullPointerException
                if _rxConnection is <NULL/>
        */
        DataSourceMetaData( const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConnection );

        // XDataSourceMetaData
        virtual ::sal_Bool SAL_CALL supportsQueriesInFrom(  ) throw (::com::sun::star::uno::RuntimeException);

    protected:
        virtual ~DataSourceMetaData();

    private:
        DataSourceMetaData();                                  // never implemented
        DataSourceMetaData( const DataSourceMetaData& );              // never implemented
        DataSourceMetaData& operator=( const DataSourceMetaData& );   // never implemented
    };


//........................................................................
} // namespace sdbtools
//........................................................................

#endif // DBACCESS_DATASOURCEMETADATA_HXX
