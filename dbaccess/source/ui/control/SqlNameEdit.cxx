/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SqlNameEdit.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 14:32:32 $
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
#ifndef DBAUI_SQLNAMEEDIT_HXX
#include "SqlNameEdit.hxx"
#endif
namespace dbaui
{
    //------------------------------------------------------------------
    sal_Bool isCharOk(sal_Unicode _cChar,sal_Bool _bFirstChar,sal_Bool _bUpperCase,const ::rtl::OUString& _sAllowedChars)
    {
        return	(_cChar >= 'A' && _cChar <= 'Z'						||
                 _cChar == '_'										||
                 _sAllowedChars.indexOf(_cChar) != -1				||
                 (!_bFirstChar && (_cChar >= '0' && _cChar <= '9'))	||
                 (!_bUpperCase && (_cChar >= 'a' && _cChar <= 'z')));

    }
    //------------------------------------------------------------------
    sal_Bool OSQLNameChecker::checkString(	const ::rtl::OUString& _sOldValue,
                                        const ::rtl::OUString& _sToCheck,
                                        ::rtl::OUString& _rsCorrected)
    {
        sal_Bool bCorrected = sal_False;
        if ( m_bCheck )
        {
            XubString sSavedValue	= _sOldValue;
            XubString sText			= _sToCheck;
            xub_StrLen nMatch		= 0;
            for ( xub_StrLen i=nMatch;i < sText.Len(); ++i )
            {
                if ( !isCharOk( sText.GetBuffer()[i], i == 0, m_bOnlyUpperCase, m_sAllowedChars ) )
                {
                    _rsCorrected += sText.Copy( nMatch, i - nMatch );
                    bCorrected = sal_True;
                    nMatch = i + 1;
                }
            }
            _rsCorrected += sText.Copy( nMatch, sText.Len() - nMatch );
        }
        return bCorrected;
    }
    //------------------------------------------------------------------
    void OSQLNameEdit::Modify()
    {
        ::rtl::OUString sCorrected;
        if ( checkString( GetSavedValue(),GetText(),sCorrected ) )
        {
            Selection aSel = GetSelection();
            aSel.setMax( aSel.getMin() );
            SetText( sCorrected, aSel );

            SaveValue();
        }
        Edit::Modify();
    }
    //------------------------------------------------------------------
    void OSQLNameComboBox::Modify()
    {
        ::rtl::OUString sCorrected;
        if ( checkString( GetSavedValue(),GetText(),sCorrected ) )
        {
            Selection aSel = GetSelection();
            aSel.setMax( aSel.getMin() );
            SetText( sCorrected );

            SaveValue();
        }
        ComboBox::Modify();
    }
}
// -----------------------------------------------------------------------------

