/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: RowSetRow.hxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 10:02:58 $
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
#ifndef DBACCESS_CORE_API_ROWSETROW_HXX
#define DBACCESS_CORE_API_ROWSETROW_HXX

#ifndef _VOS_REF_HXX_
#include <vos/ref.hxx>
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef _CONNECTIVITY_FILE_VALUE_HXX_
#include "connectivity/FValue.hxx"
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif

namespace dbaccess
{
    typedef connectivity::ORowVector< connectivity::ORowSetValue >	ORowSetValueVector;
    typedef ::vos::ORef< ORowSetValueVector >						ORowSetRow;
    typedef ::std::vector< ORowSetRow >								ORowSetMatrix;

    class ORowSetOldRowHelper
    {
        oslInterlockedCount			m_refCount;
        ORowSetRow					m_aRow;

        ORowSetOldRowHelper& operator=(const ORowSetOldRowHelper& _rRH);
        ORowSetOldRowHelper(const ORowSetOldRowHelper& _rRh);
    public:
        ORowSetOldRowHelper() : m_refCount(0){}
        ORowSetOldRowHelper(const ORowSetRow& _rRow) 
            : m_refCount(0)
            , m_aRow(_rRow)
        {}
//		ORowSetOldRowHelper(const ORowSetOldRowHelper& _rRh)
//			: m_refCount(0)
//			, m_aRow(_rRh.m_aRow)
//		{}

        void acquire()
        {
            osl_incrementInterlockedCount( &m_refCount );
        }
        void release()
        {
            if (! osl_decrementInterlockedCount( &m_refCount ))
                delete this;
        }
        inline ORowSetRow getRow() const { return m_aRow; }
        inline void clearRow() { m_aRow = NULL; }
        inline void setRow(const ORowSetRow& _rRow) { m_aRow = _rRow; }
    };

    typedef ::vos::ORef< ORowSetOldRowHelper >	TORowSetOldRowHelperRef;

    class ORowSetValueCompare
    {
        const ::com::sun::star::uno::Any& m_rAny;
    public:
        ORowSetValueCompare(const ::com::sun::star::uno::Any& _rAny) : m_rAny(_rAny){}

        sal_Bool operator ()(const ORowSetRow& _rRH)
        {
            switch((*_rRH)[0].getTypeKind())
            {
                case ::com::sun::star::sdbc::DataType::TINYINT:
                case ::com::sun::star::sdbc::DataType::SMALLINT:
                case ::com::sun::star::sdbc::DataType::INTEGER:
                    return comphelper::getINT32(m_rAny) == (sal_Int32)(*_rRH)[0];
                    break;
                default:
                {
                    ::com::sun::star::uno::Sequence<sal_Int8> aSeq;
                    m_rAny >>= aSeq;
                    return aSeq == (*_rRH)[0];
                }
            }
        }
    };
}
#endif // DBACCESS_CORE_API_ROWSETROW_HXX

