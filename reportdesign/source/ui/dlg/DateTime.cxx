/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DateTime.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: ihi $ $Date: 2007-11-20 19:06:58 $
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
#include "precompiled_reportdesign.hxx"

#ifndef RPTUI_DATETIME_HXX
#include "DateTime.hxx"
#endif
#ifndef RPTUI_DATETIME_HRC
#include "DateTime.hrc"
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _RPTUI_DLGRESID_HRC
#include "RptResId.hrc"
#endif
#ifndef _RPTUI_SLOTID_HRC_
#include "rptui_slotid.hrc"
#endif
#ifndef _RPTUI_MODULE_HELPER_DBU_HXX_
#include "ModuleHelper.hxx"
#endif
#ifndef RTPUI_REPORTDESIGN_HELPID_HRC
#include "helpids.hrc"
#endif
#ifndef _SV_MSGBOX_HXX
#include <vcl/msgbox.hxx>
#endif
#ifndef _GLOBLMN_HRC
#include <svx/globlmn.hrc>
#endif
#ifndef _SBASLTID_HRC
#include <svx/svxids.hrc>
#endif
#ifndef _DBHELPER_DBCONVERSION_HXX_
#include <connectivity/dbconversion.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_SYSLOCALE_HXX
#include <svtools/syslocale.hxx>
#endif
#ifndef RPTUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _REPORT_RPTUIDEF_HXX
#include "RptDef.hxx"
#endif
#ifndef REPORTDESIGN_SHARED_UISTRINGS_HRC
#include "uistrings.hrc"
#endif
#ifndef RPTUI_REPORTCONTROLLER_HXX
#include "ReportController.hxx"
#endif
#ifndef _COM_SUN_STAR_REPORT_XFORMATTEDFIELD_HPP_
#include <com/sun/star/report/XFormattedField.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_TIME_HPP_
#include <com/sun/star/util/Time.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_NUMBERFORMAT_HPP_
#include <com/sun/star/util/NumberFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATPREVIEWER_HPP_
#include <com/sun/star/util/XNumberFormatPreviewer.hpp>
#endif
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#ifndef _COM_SUN_STAR_I18N_NUMBERFORMATINDEX_HPP_
#include <com/sun/star/i18n/NumberFormatIndex.hpp>
#endif
#ifndef _COMPHELPER_NUMBERS_HXX_
#include <comphelper/numbers.hxx>
#endif
#include <algorithm>

namespace rptui
{
using namespace ::com::sun::star;
using namespace ::comphelper;

DBG_NAME( rpt_ODateTimeDialog )
//========================================================================
// class ODateTimeDialog
//========================================================================
ODateTimeDialog::ODateTimeDialog( Window* _pParent
                                           ,const uno::Reference< report::XSection >& _xHoldAlive
                                           ,OReportController* _pController)
    : ModalDialog( _pParent, ModuleRes(RID_DATETIME_DLG) )
    ,m_aDate(this,	 		 ModuleRes(CB_DATE		) )
    ,m_aFTDateFormat(this,	 ModuleRes(FT_DATE_FORMAT	) )
    ,m_aDateListBox(this,	 ModuleRes(LB_DATE_TYPE	) )
    ,m_aFL0(this,            ModuleRes(FL_SEPARATOR0		) )
    ,m_aTime(this,	         ModuleRes(CB_TIME		) )
    ,m_aFTTimeFormat(this,	 ModuleRes(FT_TIME_FORMAT ) )
    ,m_aTimeListBox(this,	 ModuleRes(LB_TIME_TYPE	) )
    ,m_aFL1(this,         ModuleRes(FL_SEPARATOR1) )
    ,m_aPB_OK(this,		ModuleRes(PB_OK))
    ,m_aPB_CANCEL(this,	ModuleRes(PB_CANCEL))
    ,m_aPB_Help(this,	ModuleRes(PB_HELP))
    ,m_aDateControlling()
    ,m_aTimeControlling()
    ,m_pController(_pController)
    ,m_xHoldAlive(_xHoldAlive)
{
    DBG_CTOR( rpt_ODateTimeDialog,NULL);

    try
    {
        SvtSysLocale aSysLocale;
        m_nLocale = aSysLocale.GetLocaleData().getLocale();
        // Fill listbox with all well known date types
        InsertEntry(util::NumberFormat::DATE);
        InsertEntry(util::NumberFormat::TIME);
    }
    catch(uno::Exception&)
    {
    }

    m_aDateListBox.SetDropDownLineCount(20);
    m_aDateListBox.SelectEntryPos(0);

    m_aTimeListBox.SetDropDownLineCount(20);
    m_aTimeListBox.SelectEntryPos(0);

    // use nice enhancement, to toggle enable/disable if a checkbox is checked or not
    m_aDateControlling.enableOnCheckMark( m_aDate, m_aFTDateFormat, m_aDateListBox);
    m_aTimeControlling.enableOnCheckMark( m_aTime, m_aFTTimeFormat, m_aTimeListBox);

    CheckBox* pCheckBoxes[] = { &m_aDate,&m_aTime};
    for ( size_t i = 0 ; i < sizeof(pCheckBoxes)/sizeof(pCheckBoxes[0]); ++i)
        pCheckBoxes[i]->SetClickHdl(LINK(this,ODateTimeDialog,CBClickHdl));

    FreeResource();
}
// -----------------------------------------------------------------------------
    void ODateTimeDialog::InsertEntry(sal_Int16 _nNumberFormatId)
    {
        const bool bTime = util::NumberFormat::TIME == _nNumberFormatId;
        ListBox* pListBox = &m_aDateListBox;
        if ( bTime )
            pListBox = &m_aTimeListBox;
        
        const uno::Reference< util::XNumberFormatter> xNumberFormatter = m_pController->getReportNumberFormatter();
        const uno::Reference< util::XNumberFormats> xFormats = xNumberFormatter->getNumberFormatsSupplier()->getNumberFormats();
        const uno::Sequence<sal_Int32> aFormatKeys = xFormats->queryKeys(_nNumberFormatId,m_nLocale,sal_True);
        const sal_Int32* pIter = aFormatKeys.getConstArray();
        const sal_Int32* pEnd  = pIter + aFormatKeys.getLength();
        for(;pIter != pEnd;++pIter)
        {
            const sal_Int16 nPos = pListBox->InsertEntry(getFormatStringByKey(*pIter,xFormats,bTime));
            pListBox->SetEntryData(nPos, reinterpret_cast<void*>(*pIter));
        }
    }
//------------------------------------------------------------------------
ODateTimeDialog::~ODateTimeDialog()
{
    DBG_DTOR( rpt_ODateTimeDialog,NULL);	
}
// -----------------------------------------------------------------------------
short ODateTimeDialog::Execute()
{
    DBG_CHKTHIS( rpt_ODateTimeDialog,NULL);
    short nRet = ModalDialog::Execute();
    if ( nRet == RET_OK && (m_aDate.IsChecked() || m_aTime.IsChecked()) )
    {
        try
        {
            sal_Int32 nLength = 0;
            uno::Sequence<beans::PropertyValue> aValues( 6 );
            aValues[nLength].Name = PROPERTY_SECTION;
            aValues[nLength++].Value <<= m_xHoldAlive;

            aValues[nLength].Name = PROPERTY_TIME_STATE;
            aValues[nLength++].Value <<= m_aTime.IsChecked();

            aValues[nLength].Name = PROPERTY_DATE_STATE;
            aValues[nLength++].Value <<= m_aDate.IsChecked();

            aValues[nLength].Name = PROPERTY_FORMATKEYDATE;
            aValues[nLength++].Value <<= getFormatKey(sal_True);

            aValues[nLength].Name = PROPERTY_FORMATKEYTIME;
            aValues[nLength++].Value <<= getFormatKey(sal_False);

            sal_Int32 nWidth = 0;
            if ( m_aDate.IsChecked() )
            {
                String sDateFormat = m_aDateListBox.GetEntry( m_aDateListBox.GetSelectEntryPos() );
                nWidth = LogicToLogic(PixelToLogic(Size(GetCtrlTextWidth(sDateFormat),0)).Width(),GetMapMode().GetMapUnit(),MAP_100TH_MM);
            }
            if ( m_aTime.IsChecked() )
            {
                String sDateFormat = m_aTimeListBox.GetEntry( m_aTimeListBox.GetSelectEntryPos() );
                nWidth = ::std::max<sal_Int32>(LogicToLogic(PixelToLogic(Size(GetCtrlTextWidth(sDateFormat),0)).Width(),GetMapMode().GetMapUnit(),MAP_100TH_MM),nWidth);
            }

            if ( nWidth > 4000 )
            {
                aValues[nLength].Name = PROPERTY_WIDTH;
                aValues[nLength++].Value <<= nWidth;
            }

            m_pController->executeChecked(SID_DATETIME,aValues);
        }
        catch(uno::Exception&)
        {
            nRet = RET_NO;
        }
    }
    return nRet;
}
// -----------------------------------------------------------------------------
::rtl::OUString ODateTimeDialog::getFormatStringByKey(::sal_Int32 _nNumberFormatKey,const uno::Reference< util::XNumberFormats>& _xFormats,bool _bTime)
{
    uno::Reference< beans::XPropertySet> xFormSet = _xFormats->getByKey(_nNumberFormatKey);
    OSL_ENSURE(xFormSet.is(),"XPropertySet is null!");
    ::rtl::OUString sFormat;
    xFormSet->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FormatString"))) >>= sFormat;

    double nValue = 0;
    if ( _bTime )
    {
        Time aCurrentTime;
        nValue = ::dbtools::DBTypeConversion::toDouble(::dbtools::DBTypeConversion::toTime(aCurrentTime.GetTime()));
    }
    else
    {
        Date aCurrentDate;
        static ::com::sun::star::util::Date STANDARD_DB_DATE(30,12,1899);
        nValue = ::dbtools::DBTypeConversion::toDouble(::dbtools::DBTypeConversion::toDate(static_cast<sal_Int32>(aCurrentDate.GetDate())),STANDARD_DB_DATE);
    }

    uno::Reference< util::XNumberFormatPreviewer> xPreViewer(m_pController->getReportNumberFormatter(),uno::UNO_QUERY);
    OSL_ENSURE(xPreViewer.is(),"XNumberFormatPreviewer is null!");
    return xPreViewer->convertNumberToPreviewString(sFormat,nValue,m_nLocale,sal_True);
}
// -----------------------------------------------------------------------------
IMPL_LINK( ODateTimeDialog, CBClickHdl, CheckBox*, _pBox )
{
   (void)_pBox;
    DBG_CHKTHIS( rpt_ODateTimeDialog,NULL);

     if ( _pBox == &m_aDate || _pBox == &m_aTime)
     {
         sal_Bool bDate = m_aDate.IsChecked();
        sal_Bool bTime = m_aTime.IsChecked();
        if (!bDate && !bTime)
        {
            m_aPB_OK.Disable();
        }
        else
        {
            m_aPB_OK.Enable();
        }
    }
    return 1L;
}
// -----------------------------------------------------------------------------
sal_Int32 ODateTimeDialog::getFormatKey(sal_Bool _bDate) const
{
    DBG_CHKTHIS( rpt_ODateTimeDialog,NULL);
    sal_Int32 nFormatKey;
    if ( _bDate )
    {
         // 	nFormat = m_aDateF1.IsChecked() ? i18n::NumberFormatIndex::DATE_SYSTEM_LONG : (m_aDateF2.IsChecked() ? i18n::NumberFormatIndex::DATE_SYS_DMMMYYYY : i18n::NumberFormatIndex::DATE_SYSTEM_SHORT);
         nFormatKey = static_cast<sal_Int32>(reinterpret_cast<sal_IntPtr>(m_aDateListBox.GetEntryData( m_aDateListBox.GetSelectEntryPos() )));
    }
    else
    {
        // 	nFormat = m_aTimeF1.IsChecked() ? i18n::NumberFormatIndex::TIME_HHMMSS : (m_aTimeF2.IsChecked() ? i18n::NumberFormatIndex::TIME_HHMMSSAMPM : i18n::NumberFormatIndex::TIME_HHMM);
         nFormatKey = static_cast<sal_Int32>(reinterpret_cast<sal_IntPtr>(m_aTimeListBox.GetEntryData( m_aTimeListBox.GetSelectEntryPos() )));
    }
    return nFormatKey;
}
// =============================================================================
} // rptui
// =============================================================================
