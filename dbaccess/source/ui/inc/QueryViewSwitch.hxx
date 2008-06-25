/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: QueryViewSwitch.hxx,v $
 * $Revision: 1.15 $
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
#ifndef DBAUI_QUERYVIEWSWITCH_HXX
#define DBAUI_QUERYVIEWSWITCH_HXX

#ifndef DBAUI_QUERYVIEW_HXX
#include "queryview.hxx"
#endif

namespace dbaui
{
    class OQueryDesignView;
    class OQueryTextView;
    class OAddTableDlg;
    class OQueryContainerWindow;
    class OQueryViewSwitch 
    {
        OQueryDesignView*	m_pDesignView;
        OQueryTextView*		m_pTextView;
        sal_Bool			m_bAddTableDialogWasVisible; // true if so
    public:
        OQueryViewSwitch(OQueryContainerWindow* pParent, OQueryController& _rController,const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& );
        virtual ~OQueryViewSwitch();

        virtual sal_Bool isCutAllowed();
        virtual sal_Bool isPasteAllowed();
        virtual sal_Bool isCopyAllowed();
        virtual void copy();
        virtual void cut();
        virtual void paste();
        // clears the whole query
        virtual void clear();
        // set the view readonly or not
        virtual void setReadOnly(sal_Bool _bReadOnly);
        // check if the statement is correct when not returning false
        virtual sal_Bool checkStatement();
        // set the statement for representation
        virtual void setStatement(const ::rtl::OUString& _rsStatement);
        // returns the current sql statement
        virtual ::rtl::OUString getStatement();
        /// late construction
        virtual void Construct();
        virtual void initialize();
        /** show the text or the design view
            @return
                <TRUE/> when all went right otherwise <FALSE/> which implies an aditional
                call of switchView from the controller to restore the old state
        */
        sal_Bool switchView();
        sal_Bool isSlotEnabled(sal_Int32 _nSlotId);
        void	 setSlotEnabled(sal_Int32 _nSlotId,sal_Bool _bEnable);
        void	 setNoneVisbleRow(sal_Int32 _nRows);
        // returs the add table dialog from the design view
        OAddTableDlg* getAddTableDialog();
        void SaveUIConfig();
        void reset();
        void GrabFocus();

        OQueryDesignView*		getDesignView() const { return m_pDesignView; }
        OQueryContainerWindow*	getContainer() const;

        void SetPosSizePixel( Point _rPt,Size _rSize);
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > getORB() const;
    protected:
        // return the Rectangle where I can paint myself
        virtual void resizeDocumentView(Rectangle& rRect);
    };
}
#endif // DBAUI_QUERYVIEWSWITCH_HXX

