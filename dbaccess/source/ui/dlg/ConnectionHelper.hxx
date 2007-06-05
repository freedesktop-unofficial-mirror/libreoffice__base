/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ConnectionHelper.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: ihi $ $Date: 2007-06-05 14:41:35 $
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

#ifndef DBAUI_CONNECTIONHELPER_HXX
#define DBAUI_CONNECTIONHELPER_HXX

#ifndef _DBAUI_ADMINPAGES_HXX_
#include "adminpages.hxx"
#endif
#ifndef _UCBHELPER_CONTENT_HXX
#include <ucbhelper/content.hxx>
#endif
#ifndef _DBAUI_CURLEDIT_HXX_
#include "curledit.hxx"
#endif
#ifndef _SFX_FILEDLGHELPER_HXX
#include <sfx2/filedlghelper.hxx>
#endif


#define FILL_STRING_ITEM(editcontrol, itemset, itemid, modifiedflag)	\
    if (editcontrol.GetText() != editcontrol.GetSavedValue())			\
    {																	\
        itemset.Put(SfxStringItem(itemid, editcontrol.GetText()));		\
        modifiedflag = sal_True;										\
    }

//.........................................................................
namespace dbaui
{
//.........................................................................

    // #106016# --------------
    enum IS_PATH_EXIST
    {
        PATH_NOT_EXIST = 0,
        PATH_EXIST,
        PATH_NOT_KNOWN
    };

    class IDatabaseSettingsDialog;

    class OConnectionHelper : public OGenericAdministrationPage
    {
        sal_Bool			m_bUserGrabFocus : 1;

    public:
        OConnectionHelper( Window* pParent, const ResId& _rId, const SfxItemSet& _rCoreAttrs);
        virtual ~OConnectionHelper();
        FixedText			m_aFT_Connection;
        OConnectionURLEdit	m_aET_Connection;
        PushButton			m_aPB_Connection;
        DATASOURCE_TYPE		m_eType;          // the type can't be changed in this class, so we hold it as member.

    public:

        // setting/retrieving the current connection URL
        // necessary because for some types, the URL must be decoded for display purposes
        ODsnTypeCollection*	m_pCollection;	/// the DSN type collection instance
        virtual long    PreNotify( NotifyEvent& _rNEvt );

        // <method>OGenericAdministrationPage::fillControls</method>
        virtual void    fillControls(::std::vector< ISaveValueWrapper* >& _rControlList);
        // <method>OGenericAdministrationPage::fillWindows</method>
        virtual void    fillWindows(::std::vector< ISaveValueWrapper* >& _rControlList);
        virtual void    implInitControls(const SfxItemSet& _rSet, sal_Bool _bSaveValue);


        // setting/retrieving the current connection URL
        // necessary because for some types, the URL must be decoded for display purposes
        String		getURL( OConnectionURLEdit* _m_pConnection ) const;
        void		setURL( const String& _rURL, OConnectionURLEdit* _m_pConnection );

        String		getURLNoPrefix( ) const;
        void		setURLNoPrefix( const String& _rURL );

        /** checks if the path is existence
            @param	_rURL
                The URL to check.
        */          
        sal_Int32	checkPathExistence(const String& _rURL);

        
        IS_PATH_EXIST	pathExists(const ::rtl::OUString& _rURL, sal_Bool bIsFile) const;
        sal_Bool		createDirectoryDeep(const String& _rPathNormalized);
        sal_Bool		commitURL();

        /** opens the FileOpen dialog and asks for a FileName
            @param	_aFileOpen
                Executes the file open dialog, which must be filled from caller.
        */
        void askForFileName(::sfx2::FileDialogHelper& _aFileOpen);

           virtual void SetServiceFactory(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > _rxORB)
        {
            OGenericAdministrationPage::SetServiceFactory(_rxORB);
            m_aET_Connection.initializeTypeCollection(m_xORB);
        }

    protected:              
        DECL_LINK(OnBrowseConnections, PushButton*);
        void		setURL( const String& _rURL );
        String		implGetURL( sal_Bool _bPrefix ) const;
        void		implSetURL( const String& _rURL, sal_Bool _bPrefix );
        StringBag getInstalledAdabasDBDirs(const String &_rPath,const ::ucbhelper::ResultSetInclude& _reResultSetInclude);
        StringBag getInstalledAdabasDBs(const String &_rConfigDir,const String &_rWorkDir);
        virtual bool checkTestConnection();

        void    implUpdateURLDependentStates() const;
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // DBAUI_CONNECTIONHELPER_HXX
