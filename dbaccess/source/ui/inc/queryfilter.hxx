/*************************************************************************
 *
 *  $RCSfile: queryfilter.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: fs $ $Date: 2002-04-09 14:45:02 $
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

#ifndef DBAUI_QUERYFILTER_HXX
#define DBAUI_QUERYFILTER_HXX

#ifndef _DIALOG_HXX //autogen
#include <vcl/dialog.hxx>
#endif

#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif

#ifndef _EDIT_HXX //autogen
#include <vcl/edit.hxx>
#endif

#ifndef _FIXED_HXX //autogen
#include <vcl/fixed.hxx>
#endif

#ifndef _BUTTON_HXX //autogen
#include <vcl/button.hxx>
#endif
#ifndef _CONNECTIVITY_PARSE_SQLITERATOR_HXX_
#include <connectivity/sqliterator.hxx>
#endif

#ifndef CONNECTIVITY_PREDICATEINPUT_HXX
#include <connectivity/predicateinput.hxx>
#endif
#ifndef DBAUI_QUERYDESIGNCONTEXT_HXX
#include "ParseContext.hxx"
#endif

namespace rtl
{
    class OUString;
}
namespace com
{
    namespace sun
    {
        namespace star
        {
            namespace sdb
            {
                class XSQLQueryComposer;
            }
            namespace sdbc
            {
                class XConnection;
                class XDatabaseMetaData;
            }
            namespace container
            {
                class XNameAccess;
            }
            namespace beans
            {
                struct PropertyValue;
            }
        }
    }
}
//==================================================================
// DlgFilterCrit
//==================================================================
namespace dbaui
{
    class DlgFilterCrit	:public ModalDialog
                        ,public OParseContextClient
    {
    private:
        ListBox			aLB_WHEREFIELD1;
        ListBox			aLB_WHERECOMP1;
        Edit			aET_WHEREVALUE1;
        ListBox			aLB_WHERECOND2;
        ListBox			aLB_WHEREFIELD2;
        ListBox			aLB_WHERECOMP2;
        Edit			aET_WHEREVALUE2;
        ListBox			aLB_WHERECOND3;
        ListBox			aLB_WHEREFIELD3;
        ListBox			aLB_WHERECOMP3;
        Edit			aET_WHEREVALUE3;
        FixedText		aFT_WHEREFIELD;
        FixedText		aFT_WHERECOMP;
        FixedText		aFT_WHEREVALUE;
        FixedText		aFT_WHEREOPER;
        FixedLine       aFL_FIELDS;
        OKButton		aBT_OK;
        CancelButton	aBT_CANCEL;
        HelpButton		aBT_HELP;
        String			aSTR_NOENTRY;
        String			aSTR_COMPARE_OPERATORS;

        ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer>		m_xQueryComposer;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>		m_xColumns;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>			m_xConnection;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData>	m_xMetaData;

        ::dbtools::OPredicateInputController	m_aPredicateInput;

        void			SelectField( ListBox& rBox, const String& rField );
        DECL_LINK( ListSelectHdl, ListBox * );
        DECL_LINK( ListSelectCompHdl, ListBox * );
        void			SetLine( USHORT nIdx,const ::com::sun::star::beans::PropertyValue& _rItem,sal_Bool _bOr );
        void			EnableLines();
        ::connectivity::OSQLPredicateType GetOSQLPredicateType(USHORT nPos,USHORT nCount) const;
        USHORT			GetSelectionPos(::connectivity::OSQLPredicateType eType,const ListBox& rListBox) const;
        ::rtl::OUString	getCondition(const ListBox& _rField,const ListBox& _rComp,const Edit& _rValue) const;
        void			correctCondition(const ::rtl::OUString& _rColumnName,String& _rCondition);
        void			addQuoting(const ::rtl::OUString& _rColumnName,String& _rCondition)  const;

        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > getMatchingColumn( const Edit& _rValueInput ) const;
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > getColumn( const ::rtl::OUString& _rFieldName ) const;

    public:
        DlgFilterCrit(	Window * pParent,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _rxConnection,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer>& _rxQueryComposer,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _rxCols,
                        const String& rFieldName = String()
                    );
        ~DlgFilterCrit();

        String			BuildWherePart();

        void			GetFilterList( ) const;

    protected:
        DECL_LINK( PredicateLoseFocus, Edit* );
    };

}

#endif // DBAUI_QUERYFILTER_HXX


