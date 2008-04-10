/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: SectionView.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef _REPORT_SECTIONVIEW_HXX
#define _REPORT_SECTIONVIEW_HXX


#include <svx/svdview.hxx>
namespace rptui
{
class OReportWindow;
class OReportSection;

//============================================================================
// OSectionView
//============================================================================

class OSectionView : public SdrView
{
private:
    OReportWindow*		m_pReportWindow;
    OReportSection*		m_pSectionWindow;

    void ObjectRemovedInAliveMode( const SdrObject* pObject );
    OSectionView(const OSectionView&);
    void operator =(const OSectionView&);
public:
    TYPEINFO();

    OSectionView( SdrModel* pModel, OReportSection* _pSectionWindow, OReportWindow* pEditor );
    virtual ~OSectionView();

    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
    virtual void MarkListHasChanged();
    virtual void MakeVisible( const Rectangle& rRect, Window& rWin );

    inline OReportSection*	getSectionWindow() const { return m_pSectionWindow; }
};
}
#endif //_REPORT_SECTIONVIEW_HXX
