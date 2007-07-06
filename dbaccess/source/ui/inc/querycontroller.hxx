/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: querycontroller.hxx,v $
 *
 *  $Revision: 1.36 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-06 08:31:39 $
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
#ifndef DBAUI_QUERYCONTROLLER_HXX
#define DBAUI_QUERYCONTROLLER_HXX

#ifndef DBAUI_JOINCONTROLLER_HXX
#include "JoinController.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSQLQUERYCOMPOSER_HPP_
#include <com/sun/star/sdb/XSQLQueryComposer.hpp>
#endif
#ifndef DBAUI_QUERYVIEW_HXX
#include "queryview.hxx"
#endif
#ifndef _UNDO_HXX
#include <svtools/undo.hxx>
#endif
#ifndef _COMPHELPER_PROPERTYCONTAINER_HXX_
#include <comphelper/propertycontainer.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _CONNECTIVITY_PARSE_SQLITERATOR_HXX_
#include <connectivity/sqliterator.hxx>
#endif
#ifndef _CONNECTIVITY_SQLPARSE_HXX
#include <connectivity/sqlparse.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _CONNECTIVITY_SQLNODE_HXX
#include <connectivity/sqlnode.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif
#ifndef SVX_QUERYDESIGNCONTEXT_HXX
#include "svx/ParseContext.hxx"
#endif
#ifndef DBAUI_QUERYCONTAINERWINDOW_HXX
#include "querycontainerwindow.hxx"
#endif
#ifndef DBAUI_TABLEFIELDDESC_HXX
#include "TableFieldDescription.hxx"
#endif

class VCLXWindow;
namespace dbaui
{
    class OQueryView;
    class OQueryContainerWindow;
    class OTableConnectionData;
    class OTableWindowData;
    class OAddTableDlg;
    class OTableFieldDesc;
    class OQueryTableWindow;

    class OQueryController;
    typedef ::comphelper::OPropertyContainer                            OQueryController_PBase;
    typedef ::comphelper::OPropertyArrayUsageHelper< OQueryController > OQueryController_PABase;
    class OQueryController  :public OJoinController
                            ,public OQueryController_PBase
                            ,public OQueryController_PABase
    {
        OTableFields							m_vTableFieldDesc;
        OTableFields							m_vUnUsedFieldsDesc; // contains fields which aren't visible and don't have any criteria

        ::svxform::OSystemParseContext*			m_pParseContext;
        ::connectivity::OSQLParser              m_aSqlParser;
        ::connectivity::OSQLParseTreeIterator*  m_pSqlIterator;
        ::std::vector<sal_uInt32>				m_vColumnWidth;

        ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer > 	m_xComposer;

        ::rtl::OUString	m_sStatement;		    // contains the sql statement
        ::rtl::OUString	m_sUpdateCatalogName;   // catalog for update data
        ::rtl::OUString	m_sUpdateSchemaName;    // schema for update data
        ::rtl::OUString	m_sUpdateTableName;     // table for update data
        ::rtl::OUString	m_sName;			    // name of the query

        sal_Int32		m_nVisibleRows;		// which rows the selection browse should show
        sal_Int32		m_nSplitPos;		// the position of the splitter
        sal_Bool		m_bDesign;			// if design is true then we show the complete design otherwise only the text format
        sal_Bool		m_bDistinct;		// true when you want "select distinct" otherwise false
        sal_Bool		m_bViewAlias;		// show the alias row in the design view
        sal_Bool		m_bViewTable;		// show the table row in the design view
        sal_Bool		m_bViewFunction;	// show the function row in the design view
        sal_Bool		m_bEsacpeProcessing;// is true when we shouldn't parse the statement
        sal_Bool		m_bCreateView;		// set to true when we should create a view otherwise we create a normal query
        sal_Bool        m_bIndependent;     // are we creating an "independent" SQL command (which does *not* belong to a data source)?

        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess> getElements() const;
        sal_Bool askForNewName(	const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _xElements,
                            sal_Bool _bSaveAs);
        // creates the querycomposer
        void setQueryComposer();
        void deleteIterator();
        void executeQuery();
        void doSaveAsDoc(sal_Bool _bSaveAs);

        void saveViewSettings(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _rViewProps);
        void loadViewSettings(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _rViewProps);	
        ::rtl::OUString translateStatement( bool _bFireStatementChange = true );
        

    protected:
        // all the features which should be handled by this class
        virtual void			describeSupportedFeatures();
        // state of a feature. 'feature' may be the handle of a ::com::sun::star::util::URL somebody requested a dispatch interface for OR a toolbar slot.
        virtual FeatureState	GetState(sal_uInt16 nId) const;
        // execute a feature
        virtual void			Execute(sal_uInt16 nId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs);

        virtual void			reconnect( sal_Bool _bUI );
        virtual void			updateTitle( );

        OQueryContainerWindow*	getContainer() const { return static_cast< OQueryContainerWindow* >( getView() ); }

    public:
        OQueryController(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM);

        virtual ~OQueryController();
        OTableFields&	getTableFieldDesc()			{ return m_vTableFieldDesc; }
        OTableFields&	getUnUsedFields()			{ return m_vUnUsedFieldsDesc; }

        void			clearFields();

        virtual void	setModified(sal_Bool _bModified=sal_True);
        
        // should the statement be parsed by our own sql parser
        sal_Bool		isEsacpeProcessing()	const { return m_bEsacpeProcessing; }
        sal_Bool		isDesignMode()			const { return m_bDesign; }
        sal_Bool		isDistinct()			const { return m_bDistinct; }
        
        ::rtl::OUString	getStatement()			const { return m_sStatement; }
        sal_Int32		getSplitPos()			const { return m_nSplitPos;}
        sal_Int32		getVisibleRows()		const { return m_nVisibleRows; }

        void			setDistinct(sal_Bool _bDistinct)		{ m_bDistinct = _bDistinct;}
        void			setSplitPos(sal_Int32 _nSplitPos)		{ m_nSplitPos = _nSplitPos;}
        void			setVisibleRows(sal_Int32 _nVisibleRows)	{ m_nVisibleRows = _nVisibleRows;}

        ::connectivity::OSQLParser&             getParser()         { return m_aSqlParser;  }
        ::connectivity::OSQLParseTreeIterator&	getParseIterator()  { return *m_pSqlIterator; }
        sal_uInt32 getColWidth(sal_uInt16 _nPos) const 
        { 
            return m_vColumnWidth.size() < _nPos ? m_vColumnWidth[_nPos] : sal_uInt32(0);
        }

        virtual sal_Bool Construct(Window* pParent);

        DECLARE_XINTERFACE( )
        DECLARE_XTYPEPROVIDER( )
        // XPropertySet
        virtual com::sun::star::uno::Reference<com::sun::star::beans::XPropertySetInfo>  SAL_CALL getPropertySetInfo() throw(com::sun::star::uno::RuntimeException);
        virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

        // XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::lang::XComponent
        virtual void		SAL_CALL disposing();

        virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::rtl::OUString> SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
        // need by registration
        static ::rtl::OUString getImplementationName_Static() throw( ::com::sun::star::uno::RuntimeException );
        static ::com::sun::star::uno::Sequence< ::rtl::OUString > getSupportedServiceNames_Static(void) throw( ::com::sun::star::uno::RuntimeException );
        static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >
                SAL_CALL Create(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >&);

    protected:
        virtual void    onLoadedMenu(const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XLayoutManager >& _xLayoutManager);
        // OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

        virtual OTableWindowData* createTableWindowData();
        virtual OJoinDesignView*  getJoinView();
        // ask the user if the design should be saved when it is modified
        virtual short saveModified();
        virtual void reset();
        virtual void impl_initialize();

        void		resetImpl();

        /// sets m_sStatement, and notifies our respective property change listeners
        void    setStatement_fireEvent( const ::rtl::OUString& _rNewStatement, bool _bFireStatementChange = true );

        // OJoinController overridables
        virtual bool allowViews() const;
        virtual bool allowQueries() const;

    private:
        DECL_LINK( OnExecuteAddTable, void* );
    };
}
#endif // DBAUI_QUERYCONTROLLER_HXX

