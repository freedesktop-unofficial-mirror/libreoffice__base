/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: queryorder.cxx,v $
 *
 *  $Revision: 1.15 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:09:53 $
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

    arrLbFields[0] = &aLB_ORDERFIELD1;
    arrLbFields[1] = &aLB_ORDERFIELD2;
    arrLbFields[2] = &aLB_ORDERFIELD3;

    arrLbValues[0] = &aLB_ORDERVALUE1;
    arrLbValues[1] = &aLB_ORDERVALUE2;
    arrLbValues[2] = &aLB_ORDERVALUE3;

    xub_StrLen j;
    for(j=0 ; j < DOG_ROWS ; j++ )
    {
        arrLbFields[j]->InsertEntry( aSTR_NOENTRY );
    }

    for( j=0 ; j < DOG_ROWS ; j++ )
    {
        arrLbFields[j]->SelectEntryPos(0);
        arrLbValues[j]->SelectEntryPos(0);
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
                        arrLbFields[j]->InsertEntry(*pIter);
                    }
                }
            }
        }

        m_sOrgOrder = m_xQueryComposer->getOrder();

        SetOrderList( m_sOrgOrder );
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
void DlgOrderCrit::EnableLines()
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);
    if( LbPos(aLB_ORDERFIELD1) == 0 )
    {
        String aOrderList(GetOrderList());
        if(aOrderList.GetTokenCount(','))
            SetOrderList(aOrderList);
        else
        {
            aLB_ORDERFIELD2.Disable();
            aLB_ORDERVALUE2.Disable();

            aLB_ORDERFIELD3.Disable();
            aLB_ORDERVALUE3.Disable();
        }
    }
    else
    {
        aLB_ORDERFIELD2.Enable();
        aLB_ORDERVALUE2.Enable();

        aLB_ORDERFIELD3.Enable();
        aLB_ORDERVALUE3.Enable();
    }

    if( LbPos(aLB_ORDERFIELD2) == 0 )
    {
        String aOrderList(GetOrderList());
        if(aOrderList.GetTokenCount(','))
            SetOrderList(aOrderList);
        else
        {
            aLB_ORDERFIELD3.Disable();
            aLB_ORDERVALUE3.Disable();
        }
    }
    else
    {
        aLB_ORDERFIELD3.Enable();
        aLB_ORDERVALUE3.Enable();
    }
}

//------------------------------------------------------------------------------
void DlgOrderCrit::SetOrderList( const String& _rOrderList )
{
    DBG_CHKTHIS(DlgOrderCrit,NULL);
    Reference<XDatabaseMetaData> xMetaData = m_xConnection->getMetaData();
    ::rtl::OUString sQuote	= xMetaData.is() ? xMetaData->getIdentifierQuoteString() : ::rtl::OUString();

    xub_StrLen nLen = _rOrderList.GetTokenCount(',');
    xub_StrLen i;
    for(i=0;i<nLen && i<DOG_ROWS;++i)
    {
        String aOrder = _rOrderList.GetToken(i,',');
        aOrder.EraseTrailingChars();
        String sColumnName = aOrder.GetToken(0,' ');

        xub_StrLen nCount = sColumnName.GetTokenCount('.');
        if ( nCount > 1)
            sColumnName = sColumnName.GetToken(nCount-1,'.');

        if(sQuote.getLength() && sColumnName.Len() && sColumnName.GetChar(0) == sQuote.getStr()[0] && sColumnName.GetChar(sColumnName.Len()-1) == sQuote.getStr()[0])
        {
            sColumnName.Erase(0,1);
            sColumnName.Erase(sColumnName.Len()-1,1);
        }
        arrLbFields[i]->SelectEntry( sColumnName );
        xub_StrLen nAsc = (aOrder.GetTokenCount(' ') == 2) ? (aOrder.GetToken(1,' ').EqualsAscii("ASC") ? 0 : 1) : 0;
        arrLbValues[i]->SelectEntryPos( nAsc );
    }

    // die nicht gesetzten auf 'kein' 'aufsteigend'
    xub_StrLen nItemsSet = std::min(nLen, xub_StrLen(DOG_ROWS));
    for (i=0 ; i<DOG_ROWS-nItemsSet; ++i)
    {
        arrLbFields[2-i]->SelectEntryPos( 0 );
        arrLbValues[2-i]->SelectEntryPos( 0 );
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
        if(arrLbFields[i]->GetSelectEntryPos() != 0)
        {
            if(sOrder.getLength())
                sOrder += ::rtl::OUString::createFromAscii(",");

            String sName = arrLbFields[i]->GetSelectEntry();
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
            if(arrLbValues[i]->GetSelectEntryPos())
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





