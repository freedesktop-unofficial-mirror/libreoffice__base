/*************************************************************************
 *
 *  $RCSfile: marktree.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: oj $ $Date: 2002-08-19 07:41:26 $
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

#ifndef _DBAUI_MARKTREE_HXX_
#include "marktree.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBU_CONTROL_HRC_
#include "dbu_control.hrc"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

//========================================================================
//= OMarkableTreeListBox
//========================================================================
//------------------------------------------------------------------------
OMarkableTreeListBox::OMarkableTreeListBox( Window* pParent, WinBits nWinStyle ) : SvTreeListBox(pParent,nWinStyle)
{
    InitButtonData();
}
//------------------------------------------------------------------------
OMarkableTreeListBox::OMarkableTreeListBox( Window* pParent, const ResId& rResId) : SvTreeListBox(pParent,rResId)
{
    InitButtonData();
}
//------------------------------------------------------------------------
OMarkableTreeListBox::~OMarkableTreeListBox()
{
    delete m_pCheckButton;
}
// -----------------------------------------------------------------------------
void OMarkableTreeListBox::notifyHiContrastChanged()
{
    // old actions now done in SvTreeListBox::DataChanged() / InitSettings()
}
//------------------------------------------------------------------------
void OMarkableTreeListBox::Paint(const Rectangle& _rRect)
{
    if (!IsEnabled())
    {
        Font aOldFont = GetFont();
        Font aNewFont(aOldFont);

        StyleSettings aSystemStyle = Application::GetSettings().GetStyleSettings();
        aNewFont.SetColor(aSystemStyle.GetDisableColor());

        SetFont(aNewFont);
        SvTreeListBox::Paint(_rRect);
        SetFont(aOldFont);
    }
    else
        SvTreeListBox::Paint(_rRect);
}
//------------------------------------------------------------------------
void OMarkableTreeListBox::InitButtonData()
{
    SetNodeDefaultImages( );

    m_pCheckButton = new SvLBoxButtonData( this );
    OMarkableTreeListBox::notifyHiContrastChanged();
    EnableCheckButton( m_pCheckButton );
}
//------------------------------------------------------------------------
void OMarkableTreeListBox::KeyInput( const KeyEvent& rKEvt )
{
    // nur wenn space
    if (rKEvt.GetKeyCode().GetCode() == KEY_SPACE && !rKEvt.GetKeyCode().IsShift() && !rKEvt.GetKeyCode().IsMod1())
    {
        SvLBoxEntry* pHdlEntry = GetHdlEntry();
        if(pHdlEntry)
        {
            SvButtonState eState = GetCheckButtonState( pHdlEntry);
            if(eState == SV_BUTTON_CHECKED)
                SetCheckButtonState( pHdlEntry,SV_BUTTON_UNCHECKED);
            else
                SetCheckButtonState( pHdlEntry,SV_BUTTON_CHECKED);

            CheckButtonHdl();
        }
        else
            SvTreeListBox::KeyInput(rKEvt);
    }
    else
        SvTreeListBox::KeyInput(rKEvt);

}
//------------------------------------------------------------------------
SvButtonState OMarkableTreeListBox::implDetermineState(SvLBoxEntry* _pEntry)
{
    SvButtonState eState = GetCheckButtonState(_pEntry);
    if (!GetModel()->HasChilds(_pEntry))
        // nothing to do in this bottom-up routine if there are no children ...
        return eState;
#ifdef DBG_UTIL
    String sEntryText = GetEntryText(_pEntry);
#endif

    // loop through the children and check their states
    sal_uInt16 nCheckedChildren = 0;
    sal_uInt16 nChildrenOverall = 0;

    SvLBoxEntry* pChildLoop = GetModel()->FirstChild(_pEntry);
    while (pChildLoop)
    {
#ifdef DBG_UTIL
        String sChildText = GetEntryText(pChildLoop);
#endif
        SvButtonState eChildState = implDetermineState(pChildLoop);
        if (SV_BUTTON_TRISTATE == eChildState)
            break;

        if (SV_BUTTON_CHECKED == eChildState)
            ++nCheckedChildren;
        ++nChildrenOverall;

        pChildLoop = GetModel()->NextSibling(pChildLoop);
    }

    if (pChildLoop)
    {
        // we did not finish the loop because at least one of the children is in tristate
        eState = SV_BUTTON_TRISTATE;

        // but this means that we did not finish all the siblings of pChildLoop, so their checking may be
        // incorrect at the moment
        // -> correct this
        // 88485 - 20.06.2001 - frank.schoenheit@sun.com
        while (pChildLoop)
        {
            implDetermineState(pChildLoop);
            pChildLoop = GetModel()->NextSibling(pChildLoop);
        }
    }
    else
        // none if the children is in tristate
        if (nCheckedChildren)
            // we have at least one chil checked
            if (nCheckedChildren != nChildrenOverall)
                // not all children are checked
                eState = SV_BUTTON_TRISTATE;
            else
                // all children are checked
                eState = SV_BUTTON_CHECKED;
        else
            // no children are checked
            eState = SV_BUTTON_UNCHECKED;

    // finally set the entry to the state we just determined
    SetCheckButtonState(_pEntry, eState);

    // outta here
    return eState;
}

//------------------------------------------------------------------------
void OMarkableTreeListBox::CheckButtons()
{
    SvLBoxEntry* pEntry = GetModel()->First();
    while (pEntry)
    {
        implDetermineState(pEntry);
        pEntry = GetModel()->NextSibling(pEntry);
    }

#if 0
    // Plausibilit"atspr"ufung
    SvButtonState eState;
    SvLBoxEntry* pEntry = GetModel()->First();
    while(pEntry)
    {
        if(!GetModel()->HasChilds(pEntry))
        {
            sal_uInt16 nCheck=0;
            sal_uInt16 nCount=0;
            SvLBoxEntry* pChildEntry = pEntry;
            while(pChildEntry)
            {
                if(GetCheckButtonState(pChildEntry) == SV_BUTTON_CHECKED)
                    nCheck++;
                nCount++;
                pChildEntry = GetModel()->NextSibling(pChildEntry);
            }

            if(nCheck && nCount != nCheck)
                eState = SV_BUTTON_TRISTATE;
            else if(nCheck)
                eState = SV_BUTTON_CHECKED;
            else
                eState = SV_BUTTON_UNCHECKED;

            SvLBoxEntry* pSchema = GetModel()->GetParent(pEntry);
            if(pSchema)
            {
                pEntry = GetModel()->NextSibling(pSchema);
                SetCheckButtonState(pSchema, eState);
            }
            else
                pEntry = NULL; // wenn kein Schema dann sind bereits alle pEntry's durchlaufen worden
        }
        else
            pEntry = GetModel()->Next(pEntry);
    }

    SvLBoxEntry* pCatalog = GetModel()->First();
    SvLBoxEntry* pSchema = NULL;
    if(GetModel()->HasChilds(pCatalog) && GetModel()->HasChilds(pSchema = GetModel()->Next(pCatalog)))
    {
        sal_uInt16 nCheck	=0;
        sal_uInt16 nTri		=0;
        sal_uInt16 nCount	=0;
        while(pSchema)
        {
            if((eState = GetCheckButtonState(pSchema)) == SV_BUTTON_TRISTATE)
                break;

            if(eState == SV_BUTTON_CHECKED)
                nCheck++;
            nCount++;
            pSchema = GetModel()->NextSibling(pSchema);
        }

        if(eState != SV_BUTTON_TRISTATE)
        {
            if(nCheck && nCount == nCheck)
                eState = SV_BUTTON_CHECKED;
            else if(nCheck)
                eState = SV_BUTTON_TRISTATE;
            else
                eState = SV_BUTTON_UNCHECKED;
        }
        SetCheckButtonState( pCatalog,eState);
    }
#endif
}
//------------------------------------------------------------------------
void OMarkableTreeListBox::CheckButtonHdl()
{
    checkedButton_noBroadcast(GetHdlEntry());
    if (m_aCheckButtonHandler.IsSet())
        m_aCheckButtonHandler.Call(this);
}

//------------------------------------------------------------------------
void OMarkableTreeListBox::checkedButton_noBroadcast(SvLBoxEntry* _pEntry)
{
    SvButtonState eState = GetCheckButtonState( _pEntry);
    if (GetModel()->HasChilds(_pEntry))	// Falls Kinder, dann diese auch checken
    {
        SvLBoxEntry* pChildEntry = GetModel()->Next(_pEntry);
        SvLBoxEntry* pSiblingEntry = GetModel()->NextSibling(_pEntry);
        while(pChildEntry && pChildEntry != pSiblingEntry)
        {
            SetCheckButtonState(pChildEntry, eState);
            pChildEntry = GetModel()->Next(pChildEntry);
        }
    }

    SvLBoxEntry* pEntry = IsSelected(_pEntry) ? FirstSelected() : NULL;
    while(pEntry)
    {
        SetCheckButtonState(pEntry,eState);
        if(GetModel()->HasChilds(pEntry))	// Falls Kinder, dann diese auch checken
        {
            SvLBoxEntry* pChildEntry = GetModel()->Next(pEntry);
            SvLBoxEntry* pSiblingEntry = GetModel()->NextSibling(pEntry);
            while(pChildEntry && pChildEntry != pSiblingEntry)
            {
                SetCheckButtonState(pChildEntry,eState);
                pChildEntry = GetModel()->Next(pChildEntry);
            }
        }
        pEntry = NextSelected(pEntry);
    }
    CheckButtons();
}

//------------------------------------------------------------------------
SvLBoxEntry* OMarkableTreeListBox::GetEntryPosByName(const String& aName,SvLBoxEntry* pStart) const
{
    SvLBoxEntry* pEntry = pStart ? GetModel()->FirstChild(pStart) : GetModel()->First();
    while(pEntry && !GetEntryText(pEntry).Equals(aName))
        pEntry = GetModel()->Next(pEntry);

    return pEntry;
}

//.........................................................................
}	// namespace dbaui
//.........................................................................

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.8  2002/07/22 07:37:42  oj
 *	#101514# remove resource entries for PLUS and MINUS
 *	
 *	Revision 1.7  2002/05/24 09:54:45  gt
 *	#99251# use of default images from SvLBoxButtonData
 *	
 *	Revision 1.6  2002/04/29 08:49:26  oj
 *	#98772# hi contrast changes
 *	
 *	Revision 1.5  2001/06/20 09:53:46  fs
 *	#88485# corrected implDetermineState for a special case
 *	
 *	Revision 1.4  2001/04/27 08:10:27  fs
 *	+implDeterminedState - needed to correctly implement CheckButtons
 *	
 *	Revision 1.3  2001/01/30 08:30:11  fs
 *	+checkedButton_noBroadcast
 *	
 *	Revision 1.2  2000/10/09 12:34:33  fs
 *	use a different font when painting a disabled control
 *	
 *	Revision 1.1  2000/10/05 10:00:43  fs
 *	initial checkin
 *	
 *
 *	Revision 1.0 28.09.00 13:22:30  fs
 ************************************************************************/

