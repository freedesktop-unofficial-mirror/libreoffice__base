/*************************************************************************
 *
 *  $RCSfile: RowSetCacheIterator.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: oj $ $Date: 2001-06-26 10:12:41 $
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
 *  Source License Version 1.1 (the License); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an AS IS basis,
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
#ifndef DBACCESS_ROWSETCACHEITERATOR_HXX
#include "RowSetCacheIterator.hxx"
#endif
#ifndef DBACCESS_CORE_API_ROWSETCACHE_HXX
#include "RowSetCache.hxx"
#endif

using namespace dbaccess;
ORowSetCacheIterator::ORowSetCacheIterator(const ORowSetCacheIterator& _rRH)
: m_pCache(_rRH.m_pCache)
, m_aIter(_rRH.m_aIter)
{
}
// -----------------------------------------------------------------------------
ORowSetCacheIterator::operator ORowSetMatrix::iterator()
{
    if(m_aIter->second.aIterator == NULL || 
       m_aIter->second.aIterator == m_pCache->m_pMatrix->end())
    {
        OSL_ENSURE(m_aIter->second.aBookmark.hasValue(),"bookmark has no value!");
        m_pCache->moveToBookmark(m_aIter->second.aBookmark);
        m_aIter->second.aIterator = m_pCache->m_aMatrixIter;
    }
    return m_aIter->second.aIterator;
}
// -----------------------------------------------------------------------------
ORowSetCacheIterator& ORowSetCacheIterator::operator =(const ORowSetCacheIterator& _rRH)
{
    if(this == &_rRH)
        return *this;

    m_pCache = _rRH.m_pCache;
    m_aIter	 = _rRH.m_aIter;

    return *this;
}
// -----------------------------------------------------------------------------
ORowSetCacheIterator& ORowSetCacheIterator::operator =(const ORowSetMatrix::iterator& _rIter)
{
    m_aIter->second.aIterator = _rIter;
    return *this;
}
// -----------------------------------------------------------------------------
ORowSetRow& ORowSetCacheIterator::operator *()
{
    return *m_aIter->second.aIterator;
}
// -----------------------------------------------------------------------------
const ORowSetRow& ORowSetCacheIterator::operator *() const
{
    if(m_aIter->second.aIterator == NULL || 
       m_aIter->second.aIterator == m_pCache->m_pMatrix->end())
    {
        OSL_ENSURE(m_aIter->second.aBookmark.hasValue(),"bookmark has no value!");
        m_pCache->moveToBookmark(m_aIter->second.aBookmark);
        m_aIter->second.aIterator = m_pCache->m_aMatrixIter;
    }
    return *m_aIter->second.aIterator;
}
// -----------------------------------------------------------------------------
ORowSetMatrix::iterator& ORowSetCacheIterator::operator ->()
{
    return m_aIter->second.aIterator;
}
// -----------------------------------------------------------------------------
const ORowSetMatrix::iterator& ORowSetCacheIterator::operator ->() const
{
    if(m_aIter->second.aIterator == NULL || 
       m_aIter->second.aIterator == m_pCache->m_pMatrix->end())
    {
        OSL_ENSURE(m_aIter->second.aBookmark.hasValue(),"bookmark has no value!");
        m_pCache->moveToBookmark(m_aIter->second.aBookmark);
        m_aIter->second.aIterator = m_pCache->m_aMatrixIter;
    }
    return m_aIter->second.aIterator;
}
// -----------------------------------------------------------------------------
bool ORowSetCacheIterator::operator !=(const ORowSetMatrix::iterator& _rRH) const
{
    return m_aIter->second.aIterator != _rRH;
}
// -----------------------------------------------------------------------------
bool ORowSetCacheIterator::operator ==(const ORowSetMatrix::iterator& _rRH) const
{
    return m_aIter->second.aIterator == _rRH;
}
// -----------------------------------------------------------------------------
void ORowSetCacheIterator::setBookmark(const ::com::sun::star::uno::Any&	_rBookmark)
{
    m_aIter->second.aBookmark = _rBookmark;
}



