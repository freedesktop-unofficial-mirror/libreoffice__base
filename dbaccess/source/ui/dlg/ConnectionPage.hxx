/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ConnectionPage.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-05-10 10:21:49 $
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

#ifndef DBAUI_CONNECTIONPAGE_HXX
#define DBAUI_CONNECTIONPAGE_HXX

#ifndef DBAUI_CONNECTIONHELPER_HXX
#include "ConnectionHelper.hxx"
#endif
#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif

//.........................................................................
namespace dbaui
{
//.........................................................................

    class IDatabaseSettingsDialog;
    //=========================================================================
    //= OConnectionTabPage
    //=========================================================================

    /** implements the connection page of teh data source properties dialog.
    */
    class OConnectionTabPage : public OConnectionHelper
    {
        ODsnTypeCollection*	m_pCollection;	/// the DSN type collection instance
        sal_Bool			m_bUserGrabFocus : 1;
    protected:
        // connection 
        FixedLine			m_aFL1;
        // user authentification
        FixedLine			m_aFL2;
        FixedText			m_aUserNameLabel;
        Edit				m_aUserName;
        CheckBox			m_aPasswordRequired;

        // jdbc driver
        FixedLine			m_aFL3;
        FixedText			m_aJavaDriverLabel;
        Edit				m_aJavaDriver;
        PushButton			m_aTestJavaDriver;

        // connection test
        PushButton			m_aTestConnection;


        // called when the test connection button was clicked
        DECL_LINK(OnBrowseConnections, PushButton*);
        DECL_LINK(OnTestJavaClickHdl,PushButton*);
        DECL_LINK(OnEditModified,Edit*);

    public:
        static	SfxTabPage*	Create( Window* pParent, const SfxItemSet& _rAttrSet );
        virtual	BOOL		FillItemSet	(SfxItemSet& _rCoreAttrs);

        virtual void		implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);

        virtual void SetServiceFactory(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > _rxORB)
        { 
            OGenericAdministrationPage::SetServiceFactory(_rxORB);
            m_aET_Connection.initializeTypeCollection(m_xORB);
        }

        inline void enableConnectionURL() { m_aET_Connection.SetReadOnly(sal_False); }
        inline void disableConnectionURL() { m_aET_Connection.SetReadOnly(); }

        /** changes the connection URL.
            <p>The new URL must be of the type which is currently selected, only the parts which do not
            affect the type may be changed (compared to the previous URL).</p>
        */
    private:
        OConnectionTabPage(Window* pParent, const SfxItemSet& _rCoreAttrs);
            // nControlFlags ist eine Kombination der CBTP_xxx-Konstanten
        virtual ~OConnectionTabPage();

        // <method>OGenericAdministrationPage::fillControls</method>
        virtual void fillControls(::std::vector< ISaveValueWrapper* >& _rControlList);
        // <method>OGenericAdministrationPage::fillWindows</method>
        virtual void fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList);

    private:
        /** enables the test connection button, if allowed
        */
        virtual bool checkTestConnection();
    };
//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_DETAILPAGES_HXX_
