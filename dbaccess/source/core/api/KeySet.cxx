/*************************************************************************
 *
 *  $RCSfile: KeySet.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: oj $ $Date: 2001-01-22 07:38:23 $
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

#ifndef DBACCESS_CORE_API_KEYSET_HXX
#include "KeySet.hxx"
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XPREPAREDSTATEMENT_HPP_
#include <com/sun/star/sdbc/XPreparedStatement.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCxParameterS_HPP_
#include <com/sun/star/sdbc/XParameters.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef DBACCESS_SHARED_DBASTRINGS_HRC
#include "dbastrings.hrc"
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBCX_XKEYSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XKeysSupplier.hpp>
#endif
#ifndef _CPPUHELPER_TYPEPROVIDER_HXX_
#include <cppuhelper/typeprovider.hxx>
#endif


using namespace dbaccess;
using namespace connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbc;
//	using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;
using namespace ::cppu;
using namespace ::osl;

// -----------------------------------------------------------------------------
OKeySetBookmark::~OKeySetBookmark()
{
    if(m_pKeySet)
        m_pKeySet->RemoveBookmarkPos(m_aPosIter);
}
// -----------------------------------------------------------------------------
void OKeySetBookmark::removeKeySet()
{
    m_pKeySet = NULL;
    m_aPosIter = NULL;
}
// -----------------------------------------------------------------------------
sal_Int32 OKeySetBookmark::getRealPos() const { return m_aPosIter->first; }
// -----------------------------------------------------------------------------
sal_Int64 SAL_CALL OKeySetBookmark::getSomething( const Sequence< sal_Int8 >& _rIdentifier ) throw(RuntimeException)
{
    if (_rIdentifier.getLength() != 16)
        return NULL;

    if (0 == rtl_compareMemory(getUnoTunnelImplementationId().getConstArray(),  _rIdentifier.getConstArray(), 16 ) )
        return reinterpret_cast<sal_Int64>(this);

    return NULL;
}

//--------------------------------------------------------------------------
Sequence< sal_Int8 > OKeySetBookmark::getUnoTunnelImplementationId()
{
    static OImplementationId * pId = 0;
    if (! pId)
    {
        MutexGuard aGuard( Mutex::getGlobalMutex() );
        if (! pId)
        {
            static OImplementationId aId;
            pId = &aId;
        }
    }
    return pId->getImplementationId();
}
// -----------------------------------------------------------------------------
void OKeySetBookmark::setPosIterator(const OBookmarkMap::iterator& _rIter) 
{ 
    m_aPosIter = _rIter; 
}
// -----------------------------------------------------------------------------
// -------------------------------------------------------------------------
OKeySet::OKeySet(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDriverSet)
            : OCacheSet(_xDriverSet)
{
}
// -----------------------------------------------------------------------------
OKeySet::~OKeySet()
{
    OBookmarkMap::iterator aIter = m_aBookmarkMap.begin();
    for(;aIter != m_aBookmarkMap.end();++aIter)
    {
        Reference< XUnoTunnel> xTunnel = aIter->second;
        if(xTunnel.is())
        {
            OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
            if(pExistent)
                pExistent->removeKeySet();
        }
    }
}
// -----------------------------------------------------------------------------
void OKeySet::RemoveBookmarkPos(OBookmarkMap::iterator& _rIter)
{
    sal_Int32 nSize = m_aBookmarkMap.size();

    if(_rIter != m_aBookmarkMap.end())
        m_aBookmarkMap.erase(_rIter->first);
}
// -------------------------------------------------------------------------
Any SAL_CALL OKeySet::getBookmark( const ORowSetRow& _rRow ) throw(SQLException, RuntimeException)
{
    sal_Int32 nPos = m_xDriverSet->getRow();
    if(!nPos)
        return Any();

    if(m_aDeletedRows.size())
    {
        sal_Int32 nDiff = ::std::upper_bound(m_aDeletedRows.begin(),m_aDeletedRows.end(),nPos) - m_aDeletedRows.begin();
        nPos += nDiff;
    }

    Reference< XUnoTunnel> xRef;
    OBookmarkMap::iterator aIter = m_aBookmarkMap.find(nPos);
    if(aIter == m_aBookmarkMap.end())
    {
        OKeySetBookmark* pBookmark= new OKeySetBookmark(this,m_aBookmarkMap.end());
        xRef = pBookmark;
        pBookmark->setPosIterator(m_aBookmarkMap.insert(OBookmarkMap::value_type(nPos,xRef)).first);
        
    }
    else
        xRef = aIter->second;
    
    return makeAny(xRef);
}
    
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OKeySet::moveToBookmark( const ::com::sun::star::uno::Any& bookmark ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    Reference< XUnoTunnel> xTunnel;
    bookmark >>= xTunnel;
    if(xTunnel.is())
    {
        OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
        if(pExistent)
        {
            
            sal_Int32 nPos = pExistent->getRealPos();

            if(m_aDeletedRows.size())
            {
                sal_Int32 nDiff = ::std::upper_bound(m_aDeletedRows.begin(),m_aDeletedRows.end(),nPos) - m_aDeletedRows.begin();
                nPos -= nDiff;
            }
            return m_xDriverSet->absolute(nPos);
        }
    }
    return sal_False;
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OKeySet::moveRelativeToBookmark( const ::com::sun::star::uno::Any& bookmark, sal_Int32 rows ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
    Reference< XUnoTunnel> xTunnel;
    bookmark >>= xTunnel;
    if(xTunnel.is())
    {
        OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
        if(pExistent)
        {
            sal_Int32 nPos = pExistent->getRealPos() + rows;
            if(m_aDeletedRows.size())
            {
                sal_Int32 nDiff = ::std::upper_bound(m_aDeletedRows.begin(),m_aDeletedRows.end(),nPos) - m_aDeletedRows.begin();
                nPos -= nDiff;
            }
            return m_xDriverSet->absolute(nPos);
        }
    }
    return sal_False;
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OKeySet::compareBookmarks( const Any& first, const Any& second ) throw(SQLException, RuntimeException)
{
    Reference< XUnoTunnel> xFirst,xSecond;
    first >>= xFirst;
    second >>= xSecond;
    
    return (xFirst != xSecond) ? CompareBookmark::NOT_EQUAL : CompareBookmark::EQUAL;
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OKeySet::hasOrderedBookmarks(  ) throw(SQLException, RuntimeException)
{
    return sal_True;
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OKeySet::hashBookmark( const Any& bookmark ) throw(SQLException, RuntimeException)
{
    Reference< XUnoTunnel> xTunnel;
    bookmark >>= xTunnel;
    if(xTunnel.is())
    {
        OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
        if(pExistent)
        {
            return pExistent->getRealPos();
        }
    }
    return -1;
}
// -------------------------------------------------------------------------
// ::com::sun::star::sdbcx::XDeleteRows
Sequence< sal_Int32 > SAL_CALL OKeySet::deleteRows( const Sequence< Any >& rows ,const connectivity::OSQLTable& _xTable) throw(SQLException, RuntimeException)
{
    Reference<XPropertySet> xSet(_xTable,UNO_QUERY);
    fillTableName(xSet);

    ::rtl::OUString aSql = ::rtl::OUString::createFromAscii("DELETE FROM ");
    aSql += m_aComposedTableName;
    aSql += ::rtl::OUString::createFromAscii(" WHERE ");

    // list all cloumns that should be set
    static ::rtl::OUString aQuote	= m_xConnection->getMetaData()->getIdentifierQuoteString();
    static ::rtl::OUString aAnd		= ::rtl::OUString::createFromAscii(" AND ");
    static ::rtl::OUString aOr		= ::rtl::OUString::createFromAscii(" OR ");


    // use keys and indexes for excat postioning
    // first the keys
    Reference<XKeysSupplier> xKeySup(_xTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    Reference<XColumnsSupplier> xKeyColsSup;
    Reference<XIndexAccess> xKeyColumns;
    if(xKeys.is() && xKeys->getCount())
    {
        xKeys->getByIndex(0) >>= xKeyColsSup; // there is only one key per table
        if(xKeyColsSup.is())
            xKeyColumns = Reference<XIndexAccess>(xKeyColsSup->getColumns(),UNO_QUERY);
    }

    if(!xKeyColumns.is())
        throw SQLException();

    ::rtl::OUString aColumnName;
    ::std::vector< ::rtl::OUString> aColumnNames;
    for(sal_Int32 i=0;i < xKeyColumns->getCount();++i)
    {
        Reference<XPropertySet> xSet;
        xKeyColumns->getByIndex(i) >>= xSet;
        xSet->getPropertyValue(PROPERTY_NAME) >>= aColumnName;
        aColumnNames.push_back(aColumnName);
    }

    const Any* pBegin	= rows.getConstArray();
    const Any* pEnd		= pBegin + rows.getLength();

    Sequence< Any > aKeys;
    for(;pBegin != pEnd;++pBegin)
    {
        aSql += ::rtl::OUString::createFromAscii("( ");
        //	pBegin >>= aKeys;
        for(::std::vector< ::rtl::OUString>::const_iterator aIter = aColumnNames.begin();aIter != aColumnNames.end();++aIter)
        {
            ((aSql += aQuote) += *aIter) += aQuote;
            aSql += ::rtl::OUString::createFromAscii(" = ?");
            aSql += aAnd;
        }
        aSql = aSql.replaceAt(aSql.getLength()-5,5,::rtl::OUString::createFromAscii(" )"));
        aSql += aOr;
    }
    aSql = aSql.replaceAt(aSql.getLength()-3,3,::rtl::OUString::createFromAscii(" "));

    // now create end execute the prepared statement
    Reference< XPreparedStatement > xPrep(m_xConnection->prepareStatement(aSql));
    Reference< XParameters > xParameter(xPrep,UNO_QUERY);

    pBegin	= rows.getConstArray();
    i=1;
    for(;pBegin != pEnd;++pBegin)
    {
        Sequence< Any >* pValuePair = (Sequence< Any >*)pBegin->getValue();

        const Any* pValBegin	= pValuePair->getConstArray();
        const Any* pValEnd		= pValBegin + pValuePair->getLength();

        for(;pValBegin != pValEnd; ++pValBegin,++i)
        {
            switch(pValBegin->getValueTypeClass())
            {
            case TypeClass_STRING:
            case TypeClass_CHAR:
                {
                    ::rtl::OUString aVal;
                    *pValBegin >>= aVal;
                    xParameter->setString(i,aVal);
                }
                break;
            case TypeClass_BOOLEAN:
                xParameter->setBoolean(i,*(sal_Bool*)pValBegin->getValue());
                break;
            case TypeClass_BYTE:
                xParameter->setByte(i,*(sal_Int8*)pValBegin->getValue());
                break;
            case TypeClass_SHORT:
            case TypeClass_UNSIGNED_SHORT:
                xParameter->setShort(i,*(sal_Int16*)pValBegin->getValue());
                break;
            case TypeClass_LONG:
            case TypeClass_UNSIGNED_LONG:
                xParameter->setInt(i,*(sal_Int32*)pValBegin->getValue());
                break;
            case TypeClass_FLOAT:
                xParameter->setFloat(i,*(float*)pValBegin->getValue());
                break;
            case TypeClass_DOUBLE:
                xParameter->setDouble(i,*(double*)pValBegin->getValue());
                break;
            };
        }
    }

    sal_Bool bOk = xPrep->executeUpdate() > 0;
    Sequence< sal_Int32 > aRet(rows.getLength());
    memset(aRet.getArray(),bOk,sizeof(sal_Int32)*aRet.getLength());
    if(bOk)
    {
        const Any* pBegin	= rows.getConstArray();
        const Any* pEnd		= pBegin + rows.getLength();

        for(;pBegin != pEnd;++pBegin)
        {
            Reference< XUnoTunnel> xTunnel;
            *pBegin >>= xTunnel;
            if(xTunnel.is())
            {
                OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
                if(pExistent)
                {	
                    OBookmarkMap::iterator aIter = pExistent->getPosIterator();
                    m_aDeletedRows.insert(upper_bound(m_aDeletedRows.begin(),m_aDeletedRows.end(),aIter->first),aIter->first);
                    m_aBookmarkMap.erase(aIter);
                    pExistent->setPosIterator(m_aBookmarkMap.end());
                }
            }
        }
    }
    return aRet;
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::updateRow(const ORowSetRow& _rInsertRow ,const ORowSetRow& _rOrginalRow,const connectivity::OSQLTable& _xTable  ) throw(SQLException, RuntimeException)
{
    OCacheSet::updateRow( _rInsertRow,_rOrginalRow,_xTable);
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::insertRow( const ORowSetRow& _rInsertRow,const connectivity::OSQLTable& _xTable ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException)
{
    OCacheSet::insertRow( _rInsertRow,_xTable);
    if(rowInserted())
    {
        OBookmarkMap::iterator aIter = m_aBookmarkMap.begin();
        for(;aIter != m_aBookmarkMap.end();++aIter)
        {
            Reference< XUnoTunnel> xTunnel = aIter->second;
            if(xTunnel.is())
            {
                OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
                if(pExistent)
                    pExistent->removeKeySet();
            }
        }
        m_aBookmarkMap.clear();
        m_aDeletedRows.clear();
//		sal_Bool bFound = sal_False;
//		if(m_xDriverSet->last()) // check if the driver append new rows at the end
//		{
//			ORowSetRow aRow;
//			fillValueRow(aRow,m_xDriverRow->getRow());
//			connectivity::ORowVector< ORowSetValue >::iterator aIter = aRow->begin()+1;
//			connectivity::ORowVector< ORowSetValue >::iterator aCompareIter = _rInsertRow->begin()+1;
//			for(;aIter != aRow->end();++aIter,++aCompareIter)
//			{
//				if(*aCompareIter != *aIter)
//					break;
//			}
//			bFound = aIter == aRow->end();
//
//		}
//		if(!bFound)
//		{
//			m_xDriverSet->beforeFirst();
//			while(m_xDriverSet->next())
//			{
//			}
//		}
//		(*_rInsertRow->begin()) = m_xRowLocate->getBookmark();
    }
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::deleteRow(const ORowSetRow& _rDeleteRow,const connectivity::OSQLTable& _xTable   ) throw(SQLException, RuntimeException)
{
    OCacheSet::deleteRow(_rDeleteRow,_xTable);
    if(rowDeleted())
    {
        Reference< XUnoTunnel> xTunnel;
        (*_rDeleteRow)[0].getAny() >>= xTunnel;
        if(xTunnel.is())
        {
            OKeySetBookmark* pExistent = (OKeySetBookmark*)xTunnel->getSomething(OKeySetBookmark::getUnoTunnelImplementationId());
            if(pExistent)
            {	
                OBookmarkMap::iterator aIter = pExistent->getPosIterator();
                m_aDeletedRows.insert(upper_bound(m_aDeletedRows.begin(),m_aDeletedRows.end(),aIter->first),aIter->first);
                m_aBookmarkMap.erase(pExistent->getPosIterator()->first);
                pExistent->setPosIterator(m_aBookmarkMap.end());
            }
        }
    }
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::cancelRowUpdates(  ) throw(SQLException, RuntimeException)
{
    m_bInserted = m_bUpdated = m_bDeleted = sal_False;
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::moveToInsertRow(  ) throw(SQLException, RuntimeException)
{
}
// -------------------------------------------------------------------------
void SAL_CALL OKeySet::moveToCurrentRow(  ) throw(SQLException, RuntimeException)
{
}
// -------------------------------------------------------------------------

/*------------------------------------------------------------------------

    $Log: not supported by cvs2svn $
    Revision 1.6  2000/11/15 15:57:40  oj
    change for rowset
    
    Revision 1.5  2000/10/30 09:24:02  oj
    use tablecontainer if no tablesupplier is supported
    
    Revision 1.4  2000/10/25 07:30:24  oj
    make strings unique for lib's
    
    Revision 1.3  2000/10/17 10:18:12  oj
    some changes for the rowset
    
    Revision 1.2  2000/10/11 11:18:10  fs
    replace unotools with comphelper
    
    Revision 1.1.1.1  2000/09/19 00:15:38  hr
    initial import

    Revision 1.2  2000/09/18 14:52:46  willem.vandorp
    OpenOffice header added.

    Revision 1.1  2000/09/01 15:19:46  oj
    rowset addons

    Revision 1.0 01.08.2000 09:09:34  oj
------------------------------------------------------------------------*/


