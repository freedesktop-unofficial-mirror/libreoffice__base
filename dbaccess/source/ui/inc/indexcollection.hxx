/*************************************************************************
 *
 *  $RCSfile: indexcollection.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-05 08:59:50 $
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

#ifndef _DBAUI_INDEXCOLLECTION_HXX_
#define _DBAUI_INDEXCOLLECTION_HXX_

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_SQLEXCEPTION_HPP_
#include <com/sun/star/sdbc/SQLException.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _DBAUI_INDEXES_HXX_
#include "indexes.hxx"
#endif

#if SUPD<625
    // In SRC624 and below, the SAL_THROW was defined in another way -> redefine it the way it's used from SRC625 onwards
    // (more precise: from UDK211 onwards, but we don't have a variable for this ...)

    #ifdef __cplusplus

        #undef SAL_THROW

        #if defined(__GNUC__) || defined(__SUNPRO_CC)
            #define SAL_THROW( exc )
        #else
            #define SAL_THROW( exc ) throw exc
        #endif
        #define SAL_THROW_EXTERN_C() throw ()

    #else
        #define SAL_THROW_EXTERN_C()
    #endif

#endif

//......................................................................
namespace dbaui
{
//......................................................................

    //==================================================================
    //= OIndexCollection
    //==================================================================
    class OIndexCollection
    {
    protected:
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >
                    m_xIndexes;

        // cached information
        Indexes		m_aIndexes;

    public:
        // construction
        OIndexCollection();
        OIndexCollection(const OIndexCollection& _rSource);
        //	OIndexCollection(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxIndexes);

        const OIndexCollection& operator=(const OIndexCollection& _rSource);

        // iterating through the collection
        typedef OIndex* iterator;
        typedef OIndex const* const_iterator;

        /// get access to the first element of the index collection
        Indexes::const_iterator begin() const { return m_aIndexes.begin(); }
        /// get access to the first element of the index collection
        Indexes::iterator begin() { return m_aIndexes.begin(); }
        /// get access to the (last + 1st) element of the index collection
        Indexes::const_iterator end() const { return m_aIndexes.end(); }
        /// get access to the (last + 1st) element of the index collection
        Indexes::iterator end() { return m_aIndexes.end(); }

        // searching
        Indexes::const_iterator find(const String& _rName) const;
        Indexes::iterator find(const String& _rName);
        Indexes::const_iterator findOriginal(const String& _rName) const;
        Indexes::iterator findOriginal(const String& _rName);

        // inserting without committing
        // the OriginalName of the newly inserted index will be empty, thus indicating that it's new
        Indexes::iterator insert(const String& _rName);
        // commit a new index, which is already part if the collection, but does not have an equivalent in the
        // data source, yet
        void commitNewIndex(const Indexes::iterator& _rPos) SAL_THROW((::com::sun::star::sdbc::SQLException));

        // reset the data for the given index
        void resetIndex(const Indexes::iterator& _rPos) SAL_THROW((::com::sun::star::sdbc::SQLException));

        // attach to a new key container
        void attach(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxIndexes);
        // detach from the container
        void detach();

        // is the object valid?
        sal_Bool	isValid() const { return m_xIndexes.is(); }
        // number of contained indexes
        sal_Int32	size() const { return m_aIndexes.size(); }

        /// drop an index, and remove it from the collection
        sal_Bool	drop(const Indexes::iterator& _rPos) SAL_THROW((::com::sun::star::sdbc::SQLException));
        /// simply drop the index described by the name, but don't remove the descriptor from the collection
        sal_Bool	dropNoRemove(const Indexes::iterator& _rPos) SAL_THROW((::com::sun::star::sdbc::SQLException));

    protected:
        void implConstructFrom(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxIndexes);
        void implFillIndexInfo(OIndex& _rIndex, ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > _rxDescriptor) SAL_THROW((::com::sun::star::uno::Exception));
        void implFillIndexInfo(OIndex& _rIndex) SAL_THROW((::com::sun::star::uno::Exception));
    };


//......................................................................
}	// namespace dbaui
//......................................................................

#endif // _DBAUI_INDEXCOLLECTION_HXX_

