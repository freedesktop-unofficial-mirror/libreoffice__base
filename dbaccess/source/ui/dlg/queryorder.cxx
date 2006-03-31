/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: queryorder.cxx,v $
 *
 *  $Revision: 1.16 $
 *
 *  last change: $Author: vg $ $Date: 2006-03-31 12:14:33 $
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
#ifndef DBAUI_QUERYORDER_HRC
#include "queryorder.hrc"
#endif
#ifndef DBAUI_QUERYORDER_HXX
#include "queryorder.hxx"
#endif

#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif

#ifndef _COM_SUN_STAR_SDB_XSINGLESELECTQUERYCOMPOSER_HPP_
#include <com/sun/star/sdb/XSingleSelectQueryComposer.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNSEARCH_HPP_
#include <com/sun/star/sdbc/ColumnSearch.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _CONNECTIVITY_PARSE_SQLITERATOR_HXX_
#include <connectivity/sqliterator.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif

#ifndef TOOLS_DIAGNOSE_EX_H
#include <tools/diagnose_ex.h>
#endif

#include <algorithm>


using namespace dbaui;
using namespace connectivity;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;

DBG_NAME(DlgOrderCrit);
//------------------------------------------------------------------------------
DlgOrderCrit::DlgOrderCrit(	Window * pParent,
                            const Reference< XConnection>& _rxConnection,
                            const Reference< XSingleSelectQueryComposer >& _rxComposer,
                            const Reference< XNameAccess>& _rxCols)
             :ModalDialog( pParent, ModuleRes(DLG_ORDERCRIT) )
            ,aLB_ORDERFIELD1(	this, ResId( LB_ORDERFIELD1 ) )
            ,aLB_ORDERVALUE1(	this, ResId( LB_ORDERVALUE1 ) )
            ,aLB_ORDERFIELD2(	this, ResId( LB_ORDERFIELD2 ) )
            ,aLB_ORDERVALUE2(	this, ResId( LB_ORDERVALUE2 ) )
            ,aLB_ORDERFIELD3(	this, ResId( LB_ORDERFIELD3 ) )
            ,aLB_ORDERVALUE3(	this, ResId( LB_ORDERVALUE3 ) )
            ,aFT_ORDERFIELD(	this, ResId( FT_ORDERFIELD ) )
            ,aFT_ORDERAFTER1(	this, ResId( FT_ORDERAFTER1 ) )
            ,aFT_ORDERAFTER2(	this, ResId( FT_ORDERAFTER2 ) )
            ,aFT_ORDEROPER(		this, ResId( FT_ORDEROPER ) )
            ,aFT_ORDERDIR(		this, ResId( FT_ORDERDIR ) )
            ,aBT_OK(			this, ResId( BT_OK ) )
            ,aBT_CANCEL(		this, ResId( BT_CANCEL ) )
            ,aBT_HELP(			this, ResId( BT_HELP ) )
            ,aFL_ORDER(         this, ResId( FL_ORDER ) )
            ,aSTR_NOENTRY(		ResId( STR_NOENTRY ) )
            ,m_xQueryComposer( _rxComposer )
            ,m_xColumns(_rxCols)
            ,m_xConnection(_rxConnection)
{
    DBG_CTOR(DlgOrderCrit,NULL);

    AllSettings aSettings( GetSettings() );
    StyleSettings aStyle( aSettings.GetStyleSettings() );
    aStyle.SetAutoMnemonic( FALSE );
    aSettings.SetStyleSettings( aStyle );
    SetSettings( aSettings );

    m_aColumnList[0] = &aLB_ORDERFIELD1;
    m_aColumnList[1] = &aLB_ORDERFIELD2;
    m_aColumnList[2] = &aLB_ORDERFIELD3;

    m_aValueList[0] = &aLB_ORDERVALUE1;
    m_aValueList[1] = &aLB_ORDERVALUE2;
    m_aValueList[2] = &aLB_ORDERVALUE3;

    xub_StrLen j;
    for(j=0 ; j < DOG_ROWS ; j++ )
    {
        m_aColumnList[j]->InsertEntry( aSTR_NOENTRY );
    }

    for( j=0 ; j < DOG_ROWS ; j++ )
    {
        m_aColumnList[j]->SelectEntryPos(0);
        m_aValueList[j]->SelectEntryPos(0);
    }
    try
    {
        // ... sowie auch die restlichen Felder
        Sequence< ::rtl::OUString> aNames = m_xColumns->getElementNames();
        const ::rtl::OUString* pIter = aNames.getConstArray();
        const ::rtl::OUString* pEnd   = pIter + aNames.getLength();
        Reference<XPropertySet> xColumn;
        for(;pIter != pEnd;++pIter)
        {
            xColumn.set(m_xColumns->getByName(*pIter),UNO_QUERY);
            OSL_ENSURE(xColumn.is(),"Column is null!");
            if ( xColumn.is() )
            {
                sal_Int32 nDataType;
                xColumn->getPropertyValue(PROPERTY_TYPE) >>= nDataType;
                sal_Int32 eColumnSearch = dbtools::getSearchColumnFlag(m_xConnection,nDataType);
                if(eColumnSearch != ColumnSearch::NONE)
                {
                    for( j=0 ; j < DOG_ROWS ; j++ )
                    {
                        m_aColumnList[j]->InsertEntry(*pIter);
                    }
                }
            }
        }

        m_sOrgOrder = m_xQueryComposer->getOrder();
        impl_initializeOrderList_nothrow();
    }
    catch(const Exception&)
    {
        OSL_ENSURE(0,"Exception catched while filling order lines!");
    }
    EnableLines();

    aLB_ORDERFIELD1.SetSelectHdl(LINK(this,DlgOrderCrit,FieldListSelectHdl));
    aLB_ORDERFIELD2.SetSelectHdl(LINK(this,DlgOrderCrit,FieldListSelectHdl));

    FreeResource();

}

//------------------------------------------------------------------------------

#define LbText(x)		((x).GetSelectEntry())
#define LbPos(x)		((x).GetSelectEntryPos())

//------------------------------------------------------------------------------
DlgOrderCrit::~DlgOrderCrit()
{
    DBG_DTOR(DlgOrderCrit,NULL);
}

//------------------------------------------------------------------------------
IMPL_LINK_INLINE_START( DlgOrderCrit, FieldListSelectHdl, ListBox *, pListBox )
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);
    EnableLines();
    return 0;
}
IMPL_LINK_INLINE_END( DlgOrderCrit, FieldListSelectHdl, ListBox *, pListBox )

//------------------------------------------------------------------------------
void DlgOrderCrit::impl_initializeOrderList_nothrow()
{
    try
    {
        const ::rtl::OUString sNameProperty = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Name" ) );
        const ::rtl::OUString sAscendingProperty = ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "IsAscending" ) );

        Reference< XIndexAccess > xOrderColumns( m_xQueryComposer->getOrderColumns(), UNO_QUERY_THROW );
        sal_Int32 nColumns = xOrderColumns->getCount();
        if ( nColumns > DOG_ROWS )
            nColumns = DOG_ROWS;

        for ( sal_Int32 i = 0; i < nColumns; ++i )
        {
            Reference< XPropertySet > xColumn( xOrderColumns->getByIndex( i ), UNO_QUERY_THROW );

            ::rtl::OUString sColumnName;
            sal_Bool        bIsAscending( sal_True );

            xColumn->getPropertyValue( sNameProperty ) >>= sColumnName;
            xColumn->getPropertyValue( sAscendingProperty ) >>= bIsAscending;

            m_aColumnList[i]->SelectEntry( sColumnName );
            m_aValueList[i]->SelectEntryPos( bIsAscending ? 0 : 1 );
        }
    }
    catch( const Exception& )
    {
        DBG_UNHANDLED_EXCEPTION();
    }
}

//------------------------------------------------------------------------------
void DlgOrderCrit::EnableLines()
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);

    if ( aLB_ORDERFIELD1.GetSelectEntryPos() == 0 )
    {
        aLB_ORDERFIELD2.Disable();
        aLB_ORDERVALUE2.Disable();

        aLB_ORDERFIELD2.SelectEntryPos( 0 );
        aLB_ORDERVALUE2.SelectEntryPos( 0 );
    }
    else
    {
        aLB_ORDERFIELD2.Enable();
        aLB_ORDERVALUE2.Enable();
    }

    if ( aLB_ORDERFIELD2.GetSelectEntryPos() == 0 )
    {
        aLB_ORDERFIELD3.Disable();
        aLB_ORDERVALUE3.Disable();

        aLB_ORDERFIELD3.SelectEntryPos( 0 );
        aLB_ORDERVALUE3.SelectEntryPos( 0 );
    }
    else
    {
        aLB_ORDERFIELD3.Enable();
        aLB_ORDERVALUE3.Enable();
    }
}

//------------------------------------------------------------------------------
::rtl::OUString DlgOrderCrit::GetOrderList( ) const
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);
    Reference<XDatabaseMetaData> xMetaData = m_xConnection->getMetaData();
    ::rtl::OUString sQuote	= xMetaData.is() ? xMetaData->getIdentifierQuoteString() : ::rtl::OUString();
    static const ::rtl::OUString sDESC = ::rtl::OUString::createFromAscii(" DESC ");
    static const ::rtl::OUString sASC  = ::rtl::OUString::createFromAscii(" ASC ");

    Reference< XNameAccess> xColumns = Reference< XColumnsSupplier >(m_xQueryComposer,UNO_QUERY)->getColumns();

    ::rtl::OUString sOrder;
    for( sal_uInt16 i=0 ; i<DOG_ROWS; i++ )
    {
        if(m_aColumnList[i]->GetSelectEntryPos() != 0)
        {
            if(sOrder.getLength())
                sOrder += ::rtl::OUString::createFromAscii(",");

            String sName = m_aColumnList[i]->GetSelectEntry();
            try
            {
                sal_Bool bFunction = sal_False;
                Reference< XPropertySet > xColumn;
                if ( xColumns.is() && xColumns->hasByName( sName ) && (xColumns->getByName( sName ) >>= xColumn) && xColumn.is() )
                {
                    if ( xColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_REALNAME) )
                    {
                        ::rtl::OUString sRealName;
                        xColumn->getPropertyValue(PROPERTY_REALNAME)	>>= sRealName;
                        sName = sRealName;
                        static ::rtl::OUString sAgg(RTL_CONSTASCII_USTRINGPARAM("AggregateFunction"));
                        static ::rtl::OUString sFunction(RTL_CONSTASCII_USTRINGPARAM("Function"));
                        if ( xColumn->getPropertySetInfo()->hasPropertyByName(sFunction) )
                            xColumn->getPropertyValue(sFunction) >>= bFunction;
                    }
                }
                if ( bFunction )
                    sOrder += sName;
                else
                    sOrder += ::dbtools::quoteName(sQuote,sName);
            }
            catch(Exception)
            {
            }
            if(m_aValueList[i]->GetSelectEntryPos())
                sOrder += sDESC;
            else
                sOrder += sASC;
        }
    }
    return sOrder;
}

//------------------------------------------------------------------------------
void DlgOrderCrit::BuildOrderPart()
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);
    m_xQueryComposer->setOrder(GetOrderList());
}
// -----------------------------------------------------------------------------





