/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: SingleSelectQueryComposer.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 13:34:08 $
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
#ifndef DBACCESS_CORE_API_SINGLESELECTQUERYCOMPOSER_HXX
#define DBACCESS_CORE_API_SINGLESELECTQUERYCOMPOSER_HXX

#ifndef _COM_SUN_STAR_SDB_XPARAMETERSSUPPLIER_HPP_
#include <com/sun/star/sdb/XParametersSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XSINGLESELECTQUERYCOMPOSER_HPP_
#include <com/sun/star/sdb/XSingleSelectQueryComposer.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XTYPECONVERTER_HPP_
#include <com/sun/star/script/XTypeConverter.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE5_HXX_
#include <cppuhelper/implbase5.hxx>
#endif
#ifndef _CONNECTIVITY_PARSE_SQLITERATOR_HXX_
#include <connectivity/sqliterator.hxx>
#endif
#ifndef _CONNECTIVITY_SQLPARSE_HXX
#include <connectivity/sqlparse.hxx>
#endif
#ifndef _DBASHARED_APITOOLS_HXX_
#include "apitools.hxx"
#endif
#ifndef _TOOLS_INTN_HXX
#include <tools/intn.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _COMPHELPER_PROPERTYCONTAINER_HXX_
#include <comphelper/propertycontainer.hxx>
#endif

#include <memory>

namespace com { namespace sun { namespace star { namespace util {
    class XNumberFormatsSupplier;
    class XNumberFormatter;
}}}}

namespace dbaccess
{
    typedef ::cppu::ImplHelper5<	::com::sun::star::sdb::XSingleSelectQueryComposer,
                                    ::com::sun::star::sdb::XParametersSupplier,
                                    ::com::sun::star::sdbcx::XColumnsSupplier,
                                    ::com::sun::star::sdbcx::XTablesSupplier,
                                    ::com::sun::star::lang::XServiceInfo	> OSingleSelectQueryComposer_BASE;

    class OPrivateColumns;
    class OPrivateTables;

    class OSingleSelectQueryComposer :	 public ::comphelper::OMutexAndBroadcastHelper
                                        ,public OSubComponent
                                        ,public ::comphelper::OPropertyContainer
                                        ,public ::comphelper::OPropertyArrayUsageHelper < OSingleSelectQueryComposer >
                                        ,public OSingleSelectQueryComposer_BASE
    {
        enum SQLPart
        {
            Where = 0,      // the 0 is important, as it will be used as index into arrays
            Group,
            Having,
            Order,

            SQLPartCount
        };
        inline void incSQLPart( SQLPart& e ) { e = (SQLPart)(1 + (size_t)e); }
        enum EColumnType
        {
            SelectColumns		= 0,
            GroupByColumns		= 1,
            OrderColumns		= 2,
            ParameterColumns	= 3
        };
        typedef ::std::const_mem_fun_t< const ::connectivity::OSQLParseNode*, ::connectivity::OSQLParseTreeIterator >
                                                TGetParseNode;
        ::connectivity::OSQLParser				m_aSqlParser;
        ::connectivity::OSQLParseTreeIterator	m_aSqlIterator;         // the iterator for the complete statement
        ::connectivity::OSQLParseTreeIterator	m_aAdditiveIterator;    // the iterator for the "additive statement" (means without the clauses of the elementary statement)
        ::std::vector<OPrivateColumns*>			m_aColumnsCollection;   // used for columns and parameters of old queries
        ::std::vector<OPrivateTables*>			m_aTablesCollection;

        ::std::vector< ::rtl::OUString >        m_aElementaryParts;     // the filter/groupby/having/order of the elementary statement

        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>				m_xConnection;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData>		m_xMetaData;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>			m_xTableSupplier;
        ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >	m_xNumberFormatsSupplier;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>			m_xColumns;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >	m_xServiceFactory;
        ::com::sun::star::uno::Reference< ::com::sun::star::script::XTypeConverter >		m_xTypeConverter;

        ::std::vector<OPrivateColumns*>			m_aCurrentColumns;
        OPrivateTables*							m_pTables;		// currently used tables

        ::rtl::OUString							m_aPureSelectSQL;   // the pure select statement, without filter/order/groupby/having
        ::rtl::OUString							m_sDecimalSep;
        ::com::sun::star::lang::Locale			m_aLocale;
        sal_Int32								m_nBoolCompareMode; // how to compare bool values

        // <properties>
        ::rtl::OUString							m_sOrignal;
        // </properties>


        sal_Bool setORCriteria(::connectivity::OSQLParseNode* pCondition, ::connectivity::OSQLParseTreeIterator& _rIterator,
            ::std::vector< ::std::vector < ::com::sun::star::beans::PropertyValue > >& rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;
        sal_Bool setANDCriteria(::connectivity::OSQLParseNode* pCondition, ::connectivity::OSQLParseTreeIterator& _rIterator,
            ::std::vector < ::com::sun::star::beans::PropertyValue > & rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;
        sal_Bool setComparsionPredicate(::connectivity::OSQLParseNode* pCondition, ::connectivity::OSQLParseTreeIterator& _rIterator,
            ::std::vector < ::com::sun::star::beans::PropertyValue > & rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;

        ::rtl::OUString getColumnName(::connectivity::OSQLParseNode* pColumnRef,::connectivity::OSQLParseTreeIterator& _rIterator) const;
        ::rtl::OUString getTableAlias(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column ) const;
        sal_Int32 getPredicateType(::connectivity::OSQLParseNode * _pPredicate) const;
        // clears all Columns,Parameters and tables and insert it to their vectors
        void clearCurrentCollections();
        // clear only the parameter columns
        void clearParametersCollection();

        /** retrieves a particular part of a statement
            @param _rIterator
                the iterator to use.
        */
        ::rtl::OUString getStatementPart( TGetParseNode& _aGetFunctor, ::connectivity::OSQLParseTreeIterator& _rIterator );
        void setQuery_Impl( const ::rtl::OUString& command );

        void setConditionByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column
                                , sal_Bool andCriteria
                                ,::std::mem_fun1_t<bool,OSingleSelectQueryComposer,::rtl::OUString>& _aSetFunctor);


        /** getStructuredCondition returns the structured condition for the where or having clause
            @param	_aGetFunctor
                A member function to get the correct parse node.

            @return
                The structured filter
        */
        ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >
                    getStructuredCondition( TGetParseNode& _aGetFunctor );

        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >
                    setCurrentColumns( EColumnType _eType, const ::vos::ORef< ::connectivity::OSQLColumns >& _rCols );

        //helper methods for mem_fun_t
        inline bool implSetFilter(::rtl::OUString _sFilter) { setFilter(_sFilter); return true;}
        inline bool implSetHavingClause(::rtl::OUString _sFilter) { setHavingClause(_sFilter); return true;}

        /** returns the part of the seelect statement
            @param	_ePart
                Which part should be returned.
            @param	_bWithKeyword
                If <TRUE/> the keyword will be added too. Otherwise not.
            @param _rIterator
                The iterator to use.

            @return
                The part of the select statement.
        */
        ::rtl::OUString getSQLPart( SQLPart _ePart, ::connectivity::OSQLParseTreeIterator& _rIterator, sal_Bool _bWithKeyword );

        /** retrieves the keyword for the given SQLPart
        */
        ::rtl::OUString getKeyword( SQLPart _ePart ) const;

        /** sets a single "additive" clause, means a filter/groupby/having/order clause
        */
        void setSingleAdditiveClause( SQLPart _ePart, const ::rtl::OUString& _rClause );

        /** composes a statement from m_aPureSelectSQL and the 4 usual clauses
        */
        ::rtl::OUString composeStatementFromParts( const ::std::vector< ::rtl::OUString >& _rParts );

    protected:
        virtual ~OSingleSelectQueryComposer();
    public:

        OSingleSelectQueryComposer(	const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _xTableSupplier,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _xConnection,
                        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xServiceFactory);


        enum BoolComparison
        {
            BOOL_COMPARISON_DEFAULT	= 0, // column = 0, column = 1
            BOOL_COMPARISON_SQL		= 1, // column Is true, column Is false
            BOOL_COMPARISON_MISC	= 2, // column = false, column = true
            BOOL_COMPARISON_ACCESS	= 3  // column = 0, column = -1
        };

        void SAL_CALL disposing(void);
        // ::com::sun::star::lang::XTypeProvider
        DECLARE_TYPEPROVIDER( );

        // com::sun::star::lang::XUnoTunnel
        virtual sal_Int64 SAL_CALL getSomething( const ::com::sun::star::uno::Sequence< sal_Int8 >& aIdentifier ) throw(::com::sun::star::uno::RuntimeException);
        // ::com::sun::star::uno::XInterface
        DECLARE_XINTERFACE( )

        // XServiceInfo
        DECLARE_SERVICE_INFO();

        DECLARE_PROPERTYCONTAINER_DEFAULTS();

        // ::com::sun::star::sdb::XSingleSelectQueryComposer
        virtual ::rtl::OUString SAL_CALL getElementaryQuery() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setElementaryQuery( const ::rtl::OUString& _rElementary ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setFilter( const ::rtl::OUString& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setStructuredFilter( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendFilterByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column, sal_Bool andCriteria ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendGroupByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setGroup( const ::rtl::OUString& group ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setHavingClause( const ::rtl::OUString& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setStructuredHavingClause( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendHavingClauseByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column, sal_Bool andCriteria ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendOrderByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column, sal_Bool ascending ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setOrder( const ::rtl::OUString& order ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);

        // XSingleSelectQueryAnalyzer
        virtual ::rtl::OUString SAL_CALL getQuery(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setQuery( const ::rtl::OUString& command ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getFilter(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > > SAL_CALL getStructuredFilter(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getGroup(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > SAL_CALL getGroupColumns(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getHavingClause(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > > SAL_CALL getStructuredHavingClause(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::rtl::OUString SAL_CALL getOrder(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > SAL_CALL getOrderColumns(  ) throw (::com::sun::star::uno::RuntimeException);

        // XColumnsSupplier
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getColumns(  ) throw(::com::sun::star::uno::RuntimeException);
        // XTablesSupplier
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > SAL_CALL getTables(  ) throw(::com::sun::star::uno::RuntimeException);
        // XParametersSupplier
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess > SAL_CALL getParameters(  ) throw(::com::sun::star::uno::RuntimeException);
    };
}
#endif // DBACCESS_CORE_API_SINGLESELECTQUERYCOMPOSER_HXX
