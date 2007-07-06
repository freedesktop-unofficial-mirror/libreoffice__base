/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: AppController.hxx,v $
 *
 *  $Revision: 1.19 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-06 07:58:06 $
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

#ifndef DBAUI_APPCONTROLLER_HXX
#define DBAUI_APPCONTROLLER_HXX

#ifndef DBAUI_GENERICCONTROLLER_HXX
#include "genericcontroller.hxx"
#endif
#ifndef _SV_TIMER_HXX
#include <vcl/timer.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_
#include <svx/dataaccessdescriptor.hxx>
#endif
#ifndef DBAUI_APPELEMENTTYPE_HXX
#include "AppElementType.hxx"
#endif
#ifndef _SOT_STORAGE_HXX
#include <sot/storage.hxx>
#endif
#ifndef DBAUI_IAPPELEMENTNOTIFICATION_HXX
#include "IAppElementNotification.hxx"
#endif
/** === begin UNO includes === **/
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYCHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_APPLICATION_XDATABASEDOCUMENTUI_HPP_
#include <com/sun/star/sdb/application/XDatabaseDocumentUI.hpp>
#endif
/** === end UNO includes === **/
#ifndef _DBACCESS_UI_CALLBACKS_HXX_
#include "callbacks.hxx"
#endif
#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef DBUI_TABLECOPYHELPER_HXX
#include "TableCopyHelper.hxx"
#endif
#ifndef _DBAUI_LINKEDDOCUMENTS_HXX_
#include "linkeddocuments.hxx"
#endif
#ifndef DBACCESS_SOURCE_UI_INC_DOCUMENTCONTROLLER_HXX
#include "documentcontroller.hxx"
#endif
#ifndef _DBAUI_COMMON_TYPES_HXX_
#include "commontypes.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif

#include <memory>

class ListBox;
class SvLBoxEntry;
class SvTreeListBox;
class TransferableHelper;
class TransferableClipboardListener;
class SfxFilter;

FORWARD_DECLARE_INTERFACE(container,XNameContainer)
FORWARD_DECLARE_INTERFACE(container,XContainer)
FORWARD_DECLARE_INTERFACE(util,XNumberFormatter)
FORWARD_DECLARE_INTERFACE(util,XCloseable)
FORWARD_DECLARE_INTERFACE(ucb,XContent)
//........................................................................
namespace dbaui
{
//........................................................................
    //====================================================================
    //= OApplicationController
    //====================================================================
    class OApplicationController;
    class OApplicationView;
    class OLinkedDocumentsAccess;
    typedef OGenericUnoController					OApplicationController_CBASE;
    typedef ::cppu::ImplHelper3 <   ::com::sun::star::container::XContainerListener
                                ,   ::com::sun::star::beans::XPropertyChangeListener
                                ,   ::com::sun::star::sdb::application::XDatabaseDocumentUI
                                >	OApplicationController_Base;

    class OApplicationController
            :public OApplicationController_CBASE
            ,public OApplicationController_Base
            ,public IApplicationElementNotification
            ,public IControlActionListener
            ,public IContainerFoundListener
            ,public IViewChangeListener
    {
        friend class OConnectionChangeBroadcaster;
    public:
        typedef ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainer > TContainer;
        typedef ::std::vector< TContainer >                                                 TContainerVector;

        typedef ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >      TComponent;
        typedef ::std::map< TComponent, TComponent >                                        TDocuments;

    private:

        OTableCopyHelper::DropDescriptor			m_aAsyncDrop;

        SharedConnection        m_xDataSourceConnection;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData >
                                m_xMetaData;

        OModuleClient	m_aModuleClient;
        TransferableDataHelper	m_aSystemClipboard;		// content of the clipboard
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >   m_xDataSource;
        ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >
                                m_xModel;
        ModelControllerConnector
                                m_aModelConnector;
        TContainerVector		m_aCurrentContainers;	// the containers where we are listener on
        TDocuments				m_aDocuments;
        ODsnTypeCollection		m_aTypeCollection;
        OTableCopyHelper        m_aTableCopyHelper;
        TransferableClipboardListener*
                                m_pClipbordNotifier;		// notifier for changes in the clipboard
        mutable ::rtl::OUString	m_sDatabaseName;
        sal_Int32				m_nAsyncDrop;
        PreviewMode				m_ePreviewMode;				// the mode of the preview
        ElementType				m_eOldType;
        sal_Bool				m_bPreviewEnabled;			// true when the preview should enabled
        sal_Bool				m_bNeedToReconnect;			// true when the settings of the data source were modified and the connection is no longer up to date
        sal_Bool				m_bSuspended		: 1;	// is true when the controller was already suspended


        OApplicationView*		getContainer() const;

        /** returns the database name
            @return
                the database name
        */
        inline ::rtl::OUString getDatabaseName() const { return m_sDatabaseName; }

        /** returns the stripped database name.
            @return
                The stripped database name either the registered naem or if it is a file url the last segment.
        */
        ::rtl::OUString getStrippedDatabaseName() const;

        /** return the element type for given container
            @param	_xContainer	The container where the element type has to be found
            @return	the element type coressponding to the given container
        */
        ElementType getElementType(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainer >& _xContainer) const;

        /** opens a new frame with either the table or the query or report or form or view
            @param	_sName
                The name of the object to open
            @param	_eType
                Defines the type to open
            @param	_eOpenMode
                denotes the mode in which to open the object
            @param _nInstigatorCommand
                denotes the command which instigated the action. Might be 0.
            @return the form or report model will only be returned, otherwise <NULL/>
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent > openElement(
            const ::rtl::OUString& _sName,
            ElementType _eType,
            OLinkedDocumentsAccess::EOpenMode _eOpenMode,
            sal_uInt16 _nInstigatorCommand = 0
        );

        /** opens a new frame for creation or auto pilot
            @param	_eType
                Defines the type to open
            @param	_bSQLView
                If <TRUE/> the query design will be opened in SQL view, otherwise not.
        */
        void newElement( ElementType _eType , sal_Bool _bSQLView );

        /** creates a new database object, using an auto pilot
            @param _eType
                Defines the type of the object to create
            @precond
                Our mutex must not be locked.
            @since #i39203#
        */
        void newElementWithPilot( ElementType _eType );

        /** converts the query to a view
            @param	_sName
                The name of the query.
        */
        void convertToView(const ::rtl::OUString& _sName);

        /** checks if the selected data source is read only
            @return
                <TRUE/> if read only, otherwise <FALSE/>
        */
        virtual sal_Bool isDataSourceReadOnly() const;

        /** checks if the connection for the selected data source is read only. If the connection doesn't exist, <TRUE/> will be returned.
            @return
                <TRUE/> if read only or doesn't exist, otherwise <FALSE/>
        */
        sal_Bool isConnectionReadOnly() const;

        /** fills the list with the selected entries.
            @param	_rNames
        */
        void getSelectionElementNames( ::std::vector< ::rtl::OUString>& _rNames );

        /// deletes the entries selected.
        void deleteEntries();

        /// renames the selected entry in the detail page
        void renameEntry();

        /** deletes queries, forms, or reports
            @param	_eType
                the type of the objects
            @param	_rList
                The names of the elements to delete
            @param	_bConfirm
                determines whether the user must confirm the deletion
        */
        void deleteObjects(	ElementType _eType,
                            const ::std::vector< ::rtl::OUString>& _rList,
                            bool _bConfirm );

        /** deletes multiple elements from the given container
            @param	_rxNames
                the object container
            @param	_rList
                The names of the elements to delete
            @param	_bConfirm
                determines whether the user must confirm the deletion
        */
        void deleteObjects(	const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& _rxNames,
                            const ::std::vector< ::rtl::OUString>& _rList,
                            bool _bConfirm );


        /** deletes tables.
            @param	_rList
                The list of tables.
        */
        void deleteTables(const ::std::vector< ::rtl::OUString>& _rList);

        /// copies the current object into clipboard
        TransferableHelper* copyObject();

        /** fills all elements of the wanted type into the list.
            @param	_eType
                The type.
            @param	_rList
                The list to fill.
        */
        void getElements(ElementType _eType,::std::vector< ::rtl::OUString>& _rList);

        /// returns the nameaccess
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > getElements(ElementType _eType);

        ///

        /** returns the document access for the specific type
            @param	_eType
                the type
            @return	::std::auto_ptr<OLinkedDocumentsAccess>
        */
        ::std::auto_ptr<OLinkedDocumentsAccess> getDocumentsAccess(ElementType _eType);

        /// returns the query definitions of the active data source.
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer> getQueryDefintions() const;

        /** pastes a special format from the system clipboard to the currently selected object types
            @param	_nFormatId
                The format to be copied.
        */
        void pasteFormat(sal_uInt32 _nFormatId);

        /** pastes a query, form or report into the data source
            @param	_eType
                The type of the object to paste.
            @param	_rPasteData
                The data descriptor.
            @param	_sParentFolder
                The name of the parent folder if it exists.
            @param	_bMove
                if <TRUE/> the name of the content must be inserted without any change, otherwise not.
            @return
                <TRUE/> if the paste opertions was successfull, otherwise <FALSE/>.
        */
        sal_Bool paste( ElementType _eType,const ::svx::ODataAccessDescriptor& _rPasteData ,const String& _sParentFolder = String(),sal_Bool _bMove = sal_False);

        /// returns the system clipboard.
        const TransferableDataHelper& getViewClipboard() const { return m_aSystemClipboard; }

        /// returns <TRUE/> if the clipboard supports a table format, otherwise <FALSE/>.
        sal_Bool isTableFormat() const;

        /** copies a table which was constructed by tags like HTML or RTF
            @param	_rDesc
                The Drop descriptor
            @param	_bCheck
                If set to <TRUE/> than the controller checks only if a copy is possible.
        */
        sal_Bool copyTagTable(  OTableCopyHelper::DropDescriptor& _rDesc
                                , sal_Bool _bCheck);

        /** fills the vector with all supported formats
            @param	_eType
                The type for which we need the formats
            @param	_rFormatIds
                The vector to be filled up.
        */
        void getSupportedFormats(ElementType _eType,::std::vector<SotFormatStringId>& _rFormatIds) const;

        /** adds a listener to the current name access.
            @param	_xCollection
                The collection where we want to listen on.
        */
        void addContainerListener(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _xCollection);

        /** opens a uno dialog withthe currently selected data source as initialize argument
            @param	_sServiceName
                The serivce name of the dialog to be executed.
        */
        void openDialog(const ::rtl::OUString& _sServiceName);

        /** opens the administration dialog for the selected data source
        */
        void openDataSourceAdminDialog();

        /** opens the table filter dialog for the selected data source
        */
        void openTableFilterDialog();

        /** opens the DirectSQLDialog to execute hand made sql statements.
        */
        void openDirectSQLDialog();

        /** when the settings of the data source changed,
            it opens a dialog which ask to close all depending documents, then recreate the connection.
            The SolarMutex has to be locked before calling this.
        */
        void askToReconnect();

        /** suspend one document.
            @return
                <TRUE/> if the document could be suspended, otherwise <FALSE/>.
        */
        sal_Bool suspendDocument(const TDocuments::key_type& _xComponent,sal_Bool _bSuspend);

        /** suspend all open documents.
            @return
                <TRUE/> if all documents could be suspended, otherwise <FALSE/>.
        */
        sal_Bool suspendDocuments(sal_Bool bSuspend);

        /** add event listener and remember the document
            @param	_xDocument
                the new document, may be <NULL/>
            @param	_xDefinition
                The defintion object.
        */
        void addDocumentListener(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& _xDocument,
                                const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& _xDefinition);

        /** Inserts a new object into the hierachy given be the type.
            @param	_eType
                Where to insert the new item.
            @param	_sParentFolder
                The name of the parent folder if it exists.
            @param	_xContent
                The content to insert.
            @param	_bMove
                if <TRUE/> the name of the content must be inserted without any change, otherwise not.
            @return
                <TRUE/> if the insert opertions was successfull, otherwise <FALSE/>.
        */
        sal_Bool insertHierachyElement(	 ElementType _eType
                                    ,const String& _sParentFolder
                                    ,sal_Bool _bCollection = sal_True
                                    ,const ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XContent>& _xContent = ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XContent>()
                                    ,sal_Bool _bMove = sal_False);
        /** checks if delete command or rename comamnd is allowed
            @param	_eType
                The element type.
            @param	_bDelete
                If <TRUE> then the delete command should be checked.
            @return
                <TRUE> if the command is allowed
        */
        sal_Bool isRenameDeleteAllowed(ElementType _eType,sal_Bool _bDelete) const;
        /** all selected entries will be opened, or edited, or converted to a view
            @param	_nId
                The slot which should be executed.
            @param	_eOpenMode
                Defines the mode of opening. @see OLinkedDocumentsAccess::EOpenMode
        */
        void doAction(sal_uInt16 _nId ,OLinkedDocumentsAccess::EOpenMode _eOpenMode);
    protected:
        // ----------------------------------------------------------------
        // initalizing members
        /** forces usage of a connection which we do not own
            <p>To be used from within XInitialization::initialize only.</p>
        */
        void					initializeConnection( const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _rxForeignConn );

        // state of a feature. 'feature' may be the handle of a ::com::sun::star::util::URL somebody requested a dispatch interface for OR a toolbar slot.
        virtual FeatureState	GetState(sal_uInt16 nId) const;
        // execute a feature
        virtual void			Execute(sal_uInt16 nId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs);

        // IControlActionListener overridables
        virtual sal_Bool		requestContextMenu( const CommandEvent& _rEvent );
        virtual sal_Bool        requestQuickHelp( const SvLBoxEntry* _pEntry, String& _rText ) const;
        virtual sal_Bool		requestDrag( sal_Int8 _nAction, const Point& _rPosPixel );
        virtual sal_Int8		queryDrop( const AcceptDropEvent& _rEvt, const DataFlavorExVector& _rFlavors );
        virtual sal_Int8		executeDrop( const ExecuteDropEvent& _rEvt );

        // OGenericUnoController
        virtual void			updateTitle( );
        virtual void            onLoadedMenu( const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XLayoutManager >& _xLayoutManager );
        virtual void            impl_initialize();

        virtual ~OApplicationController();

    public:
        OApplicationController(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxORB);

        DECLARE_XINTERFACE( )
        DECLARE_XTYPEPROVIDER( )

        // XServiceInfo
        virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString> SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
        // need by registration
        static ::rtl::OUString getImplementationName_Static() throw( ::com::sun::star::uno::RuntimeException );
        static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
        static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
                SAL_CALL Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

        // ::com::sun::star::frame::XController
        virtual sal_Bool SAL_CALL suspend(sal_Bool bSuspend) throw( ::com::sun::star::uno::RuntimeException );
        virtual sal_Bool SAL_CALL attachModel(const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > & xModel) throw( ::com::sun::star::uno::RuntimeException );
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >  SAL_CALL getModel(void) throw( ::com::sun::star::uno::RuntimeException );

        // ::com::sun::star::frame::XFrameActionListener
        virtual void SAL_CALL frameAction(const ::com::sun::star::frame::FrameActionEvent& aEvent) throw( ::com::sun::star::uno::RuntimeException );

        // ::com::sun::star::container::XContainerListener
        virtual void SAL_CALL elementInserted(const ::com::sun::star::container::ContainerEvent& Event) throw( ::com::sun::star::uno::RuntimeException );
        virtual void SAL_CALL elementRemoved(const ::com::sun::star::container::ContainerEvent& Event) throw( ::com::sun::star::uno::RuntimeException );
        virtual void SAL_CALL elementReplaced(const ::com::sun::star::container::ContainerEvent& Event) throw( ::com::sun::star::uno::RuntimeException );

        // XPropertyChangeListener
        virtual void SAL_CALL propertyChange( const ::com::sun::star::beans::PropertyChangeEvent& evt ) throw (::com::sun::star::uno::RuntimeException);

        // XDatabaseDocumentUI
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDataSource > SAL_CALL getDataSource() throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindow > SAL_CALL getApplicationMainWindow() throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > SAL_CALL getActiveConnection() throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL isConnected(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::sal_Bool SAL_CALL connect(  ) throw (::com::sun::star::uno::RuntimeException);

        /** retrieves the current connection, creates it if necessary
        */
        const SharedConnection& ensureConnection();

        /** retrieves the current connection
        */
        const SharedConnection& getConnection() const { return m_xDataSourceConnection; }

        /// determines whether we're currently connected to the database
        bool isConnected() const { return m_xDataSourceConnection.is(); }

        const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData >&
            getConnectionMetaData() const { return m_xMetaData; }

        /** refreshes the tables
        */
        void refreshTables();

        /// @see <method>IApplicationElementNotification::onEntryDoubleClick</method>
        virtual bool onEntryDoubleClick(SvTreeListBox* _pTree);
        /// @see <method>IApplicationElementNotification::onCreationClick</method>
        virtual void onCreationClick(const ::rtl::OUString& _sCommand);
        /// @see <method>IApplicationElementNotification::onContainerSelect</method>
        virtual sal_Bool onContainerSelect(ElementType _eType);
        /// @see <method>IApplicationElementNotification::onEntrySelect</method>
        virtual void onEntrySelect(SvLBoxEntry* _pEntry);
        /// @see <method>IApplicationElementNotification::onEntryDeSelect</method>
        virtual void onEntryDeSelect(SvTreeListBox* _pTree);
        /// @see <method>IApplicationElementNotification::onCutEntry</method>
        virtual void onCutEntry(SvLBoxEntry* _pEntry);
        /// @see <method>IApplicationElementNotification::onCopyEntry</method>
        virtual void onCopyEntry(SvLBoxEntry* _pEntry);
        /// @see <method>IApplicationElementNotification::onPasteEntry</method>
        virtual void onPasteEntry(SvLBoxEntry* _pEntry);
        /// @see <method>IApplicationElementNotification::onDeleteEntry</method>
        virtual void onDeleteEntry(SvLBoxEntry* _pEntry);

        DECL_LINK( OnInvalidateClipboard, void* );
        DECL_LINK( OnClipboardChanged, void* );
        DECL_LINK( OnAsyncDrop, void* );
        DECL_LINK( OnCreateWithPilot, void* );

        // IContainerFoundListener
        virtual void containerFound( const ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainer >& _xContainer);

        // IViewChangeListener
        virtual void previewChanged( sal_Int32 _nMode);

    protected:
        using OApplicationController_CBASE::connect;

        /** disconnects from our XConnection, and cleans up this connection
        */
        virtual void		disconnect();

        // late construction
        virtual sal_Bool	Construct(Window* pParent);
        virtual void		describeSupportedFeatures();

    protected:
        // XEventListener
        virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

        // OComponentHelper
        virtual void SAL_CALL disposing();
    };

//........................................................................
}	// namespace dbaui
//........................................................................

#endif // DBAUI_APPCONTROLLER_HXX

