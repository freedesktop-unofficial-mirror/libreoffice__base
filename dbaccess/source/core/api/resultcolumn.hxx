/*************************************************************************
 *
 *  $RCSfile: resultcolumn.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: oj $ $Date: 2000-11-03 14:32:31 $
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

#ifndef _DBACORE_RESULTCOLUMN_HXX_
#define _DBACORE_RESULTCOLUMN_HXX_

#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATA_HDL_
#include <com/sun/star/sdbc/XResultSetMetaData.hdl>
#endif
#ifndef _DBA_COREAPI_COLUMN_HXX_
#include <column.hxx>
#endif
namespace dbaccess
{
    //************************************************************
    //  OResultColumn
    //************************************************************
    class OResultColumn : public OColumn,
                          public ::comphelper::OPropertyArrayUsageHelper < OResultColumn >
    {
    protected:
        ::com::sun::star::uno::Reference < ::com::sun::star::sdbc::XResultSetMetaData >	m_xMetaData;
        sal_Int32				m_nPos;

    public:
        OResultColumn(const ::com::sun::star::uno::Reference < ::com::sun::star::sdbc::XResultSetMetaData >& _xMetaData,
                      sal_Int32 _nPos);

    // com::sun::star::lang::XTypeProvider
        virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw (::com::sun::star::uno::RuntimeException);

    // com::sun::star::lang::XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw(::com::sun::star::uno::RuntimeException);

    // cppu::OComponentHelper
        virtual void SAL_CALL disposing(void);

    // comphelper::OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    // cppu::OPropertySetHelper
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
        virtual void SAL_CALL getFastPropertyValue(
                                    ::com::sun::star::uno::Any& rValue,
                                    sal_Int32 nHandle
                                         ) const;
    };
}
#endif // _DBACORE_RESULTCOLUMN_HXX_

