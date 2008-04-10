/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: warnings.hxx,v $
 * $Revision: 1.6 $
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

#ifndef DBA_CORE_WARNINGS_HXX
#define DBA_CORE_WARNINGS_HXX

/** ==== begin UNO includes === **/
#ifndef _COM_SUN_STAR_SDBC_XWARNINGSSUPPLIER_HPP_
#include <com/sun/star/sdbc/XWarningsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
/** ==== end UNO includes === **/

//.........................................................................
namespace dbaccess
{
//.........................................................................

    //=====================================================================
    //= IWarningsContainer
    //=====================================================================
    class SAL_NO_VTABLE IWarningsContainer
    {
    public:
        virtual void appendWarning(const ::com::sun::star::sdbc::SQLException& _rWarning) = 0;
        virtual void appendWarning(const ::com::sun::star::sdbc::SQLWarning& _rWarning) = 0;
        virtual void appendWarning(const ::com::sun::star::sdb::SQLContext& _rContext) = 0;
    };

    //====================================================================
    //= WarningsContainer
    //====================================================================
    /** helper class for implementing XWarningsSupplier, which mixes own warnings with
        warnings obtained from an external instance
    */
    class WarningsContainer : public IWarningsContainer
    {
    private:
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XWarningsSupplier >   m_xExternalWarnings;
        ::com::sun::star::uno::Any	                                                    m_aOwnWarnings;

    public:
        WarningsContainer() { }
        WarningsContainer( const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XWarningsSupplier >& _rxExternalWarnings )
            :m_xExternalWarnings( _rxExternalWarnings )
        {
        }
        virtual ~WarningsContainer();

        // convenience
        /** appends an SQLWarning instance to the chain
            @param  _rWarning
                the warning message
            @param  _pAsciiSQLState
                the SQLState of the warning
            @param  _rxContext
                the context of the warning
        */
        void appendWarning(
            const ::rtl::OUString& _rWarning,
            const sal_Char* _pAsciiSQLState,
            const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >& _rxContext );

        // IWarningsContainer
        virtual void appendWarning(const ::com::sun::star::sdbc::SQLException& _rWarning);
        virtual void appendWarning(const ::com::sun::star::sdbc::SQLWarning& _rWarning);
        virtual void appendWarning(const ::com::sun::star::sdb::SQLContext& _rContext);

        // XWarningsSupplier
        ::com::sun::star::uno::Any SAL_CALL getWarnings(  ) const;
        void SAL_CALL clearWarnings(  );
    };

//.........................................................................
}	// namespace dbaccess
//.........................................................................

#endif // DBA_CORE_WARNINGS_HXX

