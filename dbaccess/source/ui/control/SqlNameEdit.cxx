/*************************************************************************
 *
 *  $RCSfile: SqlNameEdit.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: oj $ $Date: 2001-07-16 07:44:54 $
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
        if(m_bCheck)
        {
            XubString sSavedValue	= _sOldValue;
            XubString sText			= _sToCheck;
            xub_StrLen nMatch		= 0;
            for(xub_StrLen i=nMatch;i < sText.Len();++i)
            {
                if(!isCharOk(sText.GetBuffer()[i],i == 0,m_bOnlyUpperCase,m_sAllowedChars))
                {
                    if(i) // only set when not first char
                        sSavedValue = sText.Copy(nMatch,i-nMatch);
                    _rsCorrected = sSavedValue;
                    bCorrected = sal_True;
                    break;
                }
            }
        }
        return bCorrected;
    }
    //------------------------------------------------------------------
    void OSQLNameEdit::Modify()
    {
        ::rtl::OUString sCorrected;
        if(checkString(GetSavedValue(),GetText(),sCorrected))
            SetText(sCorrected);
        SaveValue();
        Edit::Modify();
    }
    //------------------------------------------------------------------
    void OSQLNameComboBox::Modify()
    {
        ::rtl::OUString sCorrected;
        if(checkString(GetSavedValue(),GetText(),sCorrected))
        {
            SetText(sCorrected);
            SaveValue();
        }
        ComboBox::Modify();
    }
}
// -----------------------------------------------------------------------------

