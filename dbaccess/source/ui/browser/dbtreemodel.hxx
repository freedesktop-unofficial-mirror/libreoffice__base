/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: dbtreemodel.hxx,v $
 *
 *  $Revision: 1.15 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 14:27:13 $
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

#ifndef DBAUI_DBTREEMODEL_HXX
#define DBAUI_DBTREEMODEL_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _SVLBOX_HXX
#include <svtools/svlbox.hxx>
#endif
#ifndef _SVLBOXITM_HXX
#include <svtools/svlbitm.hxx>
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _SBA_UNODATBR_HXX_
#include "unodatbr.hxx"
#endif

// syntax of the tree					userdata
// datasource							holds the connection
//		queries							holds the nameaccess for the queries
//			query						holds the query
//		tables							holds the nameaccess for the tables
//			table						holds the table
//		bookmarks						holds the nameaccess for the document links
//			table						holds the document links


namespace com { namespace sun { namespace star { namespace lang { class XMultiServiceFactory; } } } }

namespace dbaui
{
    //========================================================================
    //= DBTreeListModel
    //========================================================================
    class DBTreeListModel : public SvLBoxTreeList
    {
    public:
        struct DBTreeListUserData
        {
            ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
                                            xObject;
            SbaTableQueryBrowser::EntryType	eType;
            String                          sAccessor;

            DBTreeListUserData();
            ~DBTreeListUserData();
        };

        static sal_uInt16 getImageResId(SbaTableQueryBrowser::EntryType _eType,sal_Bool _bHiContrast);
    };
}

#endif // DBAUI_DBTREEMODEL_HXX
