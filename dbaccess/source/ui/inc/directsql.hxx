/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: directsql.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:52:11 $
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

#ifndef _DBACCESS_UI_DIRECTSQL_HXX_
#define _DBACCESS_UI_DIRECTSQL_HXX_

#ifndef _SV_DIALOG_HXX
#include <vcl/dialog.hxx>
#endif
#ifndef _SVEDIT_HXX 
#include <svtools/svmedit.hxx>
#endif
#ifndef _SV_FIXED_HXX 
#include <vcl/fixed.hxx>
#endif
#ifndef _SV_LSTBOX_HXX 
#include <vcl/lstbox.hxx>
#endif
#ifndef _SV_BUTTON_HXX 
#include <vcl/button.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_ 
#include <comphelper/stl_types.hxx>
#endif
#include <deque>

#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _UNOTOOLS_EVENTLISTENERADAPTER_HXX_ 
#include <unotools/eventlisteneradapter.hxx>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif

//........................................................................
namespace dbaui
{
//........................................................................

    //====================================================================
    //= DirectSQLDialog
    //====================================================================
    class DirectSQLDialog
            :public ModalDialog
            ,public ::utl::OEventListenerAdapter
    {
    protected:
        ::osl::Mutex	m_aMutex;

        FixedLine		m_aFrame;
        FixedText		m_aSQLLabel;
        MultiLineEdit	m_aSQL;
        PushButton		m_aExecute;
        FixedText		m_aHistoryLabel;
        ListBox*		m_pSQLHistory;
        FixedLine		m_aStatusFrame;
        MultiLineEdit	m_aStatus;
        FixedLine		m_aButtonSeparator;
        HelpButton		m_aHelp;
        PushButton		m_aClose;

        typedef ::std::deque< String >	StringQueue;
        StringQueue		m_aStatementHistory;	// previous statements
        StringQueue		m_aNormalizedHistory;	// previous statements, normalized to be used in the list box

        sal_Int32		m_nHistoryLimit;
        sal_Int32		m_nStatusCount;

        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >
                        m_xConnection;

    public:
        DirectSQLDialog(
            Window* _pParent,
            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxConn);
        ~DirectSQLDialog();

        /// add an history entry
        void addHistoryEntry(const String& _rStatement);

        /// set the limit for the history size
        void setHistoryLimit(sal_Int32 _nMaxEntries);

        /// number of history entries
        sal_Int32 getHistorySize() const;

    protected:
        void executeCurrent();
        void switchToHistory(sal_Int32 _nHistoryPos, sal_Bool _bUpdateListBox = sal_True);

        // OEventListenerAdapter
        virtual void _disposing( const ::com::sun::star::lang::EventObject& _rSource );

    protected:
        DECL_LINK( OnExecute, void* );
        DECL_LINK( OnClose, void* );
        DECL_LINK( OnListEntrySelected, void* );
        DECL_LINK( OnStatementModified, void* );

    private:
        /// adds a statement to the statement history
        void implAddToStatementHistory(const String& _rStatement);

        /// ensures that our history has at most m_nHistoryLimit entries
        void implEnsureHistoryLimit();

        /// executes the statement given, adds the status to the status list
        void implExecuteStatement(const String& _rStatement);

        /// adds a status text to the status list
        void addStatusText(const String& _rMessage);

#ifdef DBG_UTIL
        const sal_Char* impl_CheckInvariants() const;
#endif
    };

    //====================================================================
#ifdef DBG_UTIL
#define CHECK_INVARIANTS(methodname)	\
    {	\
        const sal_Char* pError = impl_CheckInvariants();	\
        if (pError)	\
            OSL_ENSURE(sal_False, (ByteString(methodname) += ByteString(": ") += ByteString(pError)).GetBuffer());	\
    }
#else
#define CHECK_INVARIANTS(methodname)
#endif

//........................................................................
}	// namespace dbaui
//........................................................................

#endif // _DBACCESS_UI_DIRECTSQL_HXX_

