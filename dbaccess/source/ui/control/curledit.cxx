/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: curledit.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 14:33:39 $
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

#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................
    DBG_NAME(OConnectionURLEdit)
//=========================================================================
//= OConnectionURLEdit
//=========================================================================
//-------------------------------------------------------------------------
OConnectionURLEdit::OConnectionURLEdit(Window* _pParent, WinBits _nStyle,BOOL _bShowPrefix)
    :Edit(_pParent, _nStyle)
    ,m_pForcedPrefix(NULL)
    ,m_bShowPrefix(_bShowPrefix)
{	
    DBG_CTOR(OConnectionURLEdit ,NULL);
}

//-------------------------------------------------------------------------
OConnectionURLEdit::OConnectionURLEdit(Window* _pParent, const ResId& _rResId,BOOL _bShowPrefix)
    :Edit(_pParent, _rResId)
    ,m_pForcedPrefix(NULL)
    ,m_bShowPrefix(_bShowPrefix)
{
    DBG_CTOR(OConnectionURLEdit ,NULL);
}

//-------------------------------------------------------------------------
OConnectionURLEdit::~OConnectionURLEdit()
{
    DBG_DTOR(OConnectionURLEdit ,NULL);
    // delete my sub controls
    Edit* pSubEdit = GetSubEdit();
    SetSubEdit(NULL);
    delete pSubEdit;
    delete m_pForcedPrefix;	
}

//-------------------------------------------------------------------------
void OConnectionURLEdit::SetTextNoPrefix(const String& _rText)
{
    DBG_ASSERT(GetSubEdit(), "OConnectionURLEdit::SetTextNoPrefix: have no current type, not changing the text!");
    if (GetSubEdit())
        GetSubEdit()->SetText(_rText);
}

//-------------------------------------------------------------------------
String OConnectionURLEdit::GetTextNoPrefix() const
{
    if (GetSubEdit())
        return GetSubEdit()->GetText();
    return GetText();
}

//-------------------------------------------------------------------------
void OConnectionURLEdit::SetText(const String& _rStr)
{
    Selection aNoSelection(0,0);
    SetText(_rStr, aNoSelection);
}

//-------------------------------------------------------------------------
void OConnectionURLEdit::SetText(const String& _rStr, const Selection& _rNewSelection)
{
    // create new sub controls, if necessary
    if (!GetSubEdit())
        SetSubEdit(new Edit(this, 0));
    if ( !m_pForcedPrefix )
    {
        m_pForcedPrefix = new FixedText(this, WB_VCENTER);

        // we use a gray background for the fixed text
        StyleSettings aSystemStyle = Application::GetSettings().GetStyleSettings();
        m_pForcedPrefix->SetBackground(Wallpaper(aSystemStyle.GetDialogColor()));
    }

    m_pForcedPrefix->Show(m_bShowPrefix);

    sal_Bool bIsEmpty = 0 == _rStr.Len();
    // calc the prefix
    String sPrefix;
    if (!bIsEmpty)
    {
        // determine the type of the new URL described by the new text
        DATASOURCE_TYPE	eType = m_aTypeCollection.getType(_rStr);
        // and the prefix belonging to this type
        if (DST_UNKNOWN != eType)
            sPrefix = m_aTypeCollection.getDatasourcePrefix(eType);
        else
            DBG_ERROR("OConnectionURLEdit::SetText : the new text is no valid connection URL!");
    }

    // the fixed text gets the prefix
    if ( m_pForcedPrefix )
        m_pForcedPrefix->SetText(sPrefix);

    // both subs have to be resized according to the text len of the prefix
    Size aMySize = GetSizePixel();
    sal_Int32 nTextWidth = 0;
    if ( m_pForcedPrefix && m_bShowPrefix)
    {
        nTextWidth = m_pForcedPrefix->GetTextWidth(sPrefix) + 2;
        m_pForcedPrefix->SetPosSizePixel(Point(0, -2), Size(nTextWidth, aMySize.Height()));
    }
    GetSubEdit()->SetPosSizePixel(Point(nTextWidth, -2), Size(aMySize.Width() - nTextWidth - 4, aMySize.Height()));
        // -2 because the edit has a frame which is 2 pixel wide ... should not be necessary, but I don't fully understand this ....

    // show the sub controls (in case they were just created)
    GetSubEdit()->Show();

    // do the real SetTex
//	Edit::SetText(bIsEmpty ? _rStr : m_aTypeCollection.cutPrefix(_rStr), _rNewSelection);
    String sNewText( _rStr );
    if ( !bIsEmpty )
        sNewText  =m_aTypeCollection.cutPrefix( _rStr );
    Edit::SetText( sNewText );
}

//-------------------------------------------------------------------------
String OConnectionURLEdit::GetText() const
{
    if ( m_pForcedPrefix )
        return m_pForcedPrefix->GetText() += Edit::GetText();
    return Edit::GetText();
}
// -----------------------------------------------------------------------------
void OConnectionURLEdit::ShowPrefix(BOOL _bShowPrefix)
{
    m_bShowPrefix = _bShowPrefix;
    if ( m_pForcedPrefix )
        m_pForcedPrefix->Show(m_bShowPrefix);
}
//.........................................................................
}	// namespace dbaui
//.........................................................................

