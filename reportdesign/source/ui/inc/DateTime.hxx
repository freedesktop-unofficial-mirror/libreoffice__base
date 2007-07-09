#ifndef RPTUI_DATETIME_HXX
#define RPTUI_DATETIME_HXX
/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DateTime.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:30 $
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

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif
#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_LSTBOX_HXX
#include <vcl/lstbox.hxx>
#endif
#ifndef _SV_FIELD_HXX
#include <vcl/field.hxx>
#endif
#ifndef _SV_BUTTON_HXX
#include <vcl/button.hxx>
#endif
#ifndef _COM_SUN_STAR_REPORT_XREPORTDEFINITION_HPP_
#include <com/sun/star/report/XReportDefinition.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif

namespace rptui
{
class OReportController;
/*************************************************************************
|*
|* Groups and Sorting dialog
|*
\************************************************************************/
class ODateTimeDialog :	public ModalDialog
{
    FixedLine								m_aFLDate;
    CheckBox								m_aDate;
    RadioButton								m_aDateF1;
    RadioButton								m_aDateF2;
    RadioButton								m_aDateF3;
    FixedLine								m_aFLTime;
    CheckBox								m_aTime;
    RadioButton								m_aTimeF1;
    RadioButton								m_aTimeF2;
    RadioButton								m_aTimeF3;
    FixedLine								m_aFL1;
    OKButton								m_aPB_OK;
    CancelButton							m_aPB_CANCEL;
    HelpButton								m_aPB_Help;


    ::rptui::OReportController*				m_pController;
    ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection>			
                                            m_xHoldAlive;
    ::com::sun::star::lang::Locale			m_nLocale;

    /** returns the format string.
    */
    ::rtl::OUString getFormatString(::sal_Int16 _nNumberFormatIndex);

    /** returns the format
        @param	_bDate	<TRUE/> when the date format should be returned otherwise the time format will be returned.
    */
    sal_Int16 getFormatIndex(sal_Bool _bDate);

    /** returns the number format key
        @param	_nNumberFormatIndex the number format index @see com::sun::star::i18n::NumberFormatIndex
    */
    sal_Int32 getFormatKey(::sal_Int16 _nNumberFormatIndex);

    DECL_LINK( CBClickHdl, CheckBox* );
    ODateTimeDialog(const ODateTimeDialog&);
    void operator =(const ODateTimeDialog&);
public:
    ODateTimeDialog( Window* pParent
                        ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection>& _xHoldAlive
                        ,::rptui::OReportController* _pController);
    virtual ~ODateTimeDialog();
    virtual short	Execute();
};
// =============================================================================
} // namespace rptui
// =============================================================================
#endif // RPTUI_DATETIME_HXX
