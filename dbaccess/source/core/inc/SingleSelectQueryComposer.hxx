/*************************************************************************
 *
 *  $RCSfile: SingleSelectQueryComposer.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2003-12-16 12:41:56 $
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
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
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
#ifndef _COM_SUN_STAR_SDB_XSINGLESELECTQUERYANALYZER_HPP_
#include <com/sun/star/sdb/XSingleSelectQueryAnalyzer.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XTYPECONVERTER_HPP_
#include <com/sun/star/script/XTypeConverter.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE6_HXX_
#include <cppuhelper/implbase6.hxx>
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


namespace com { namespace sun { namespace star { namespace util {
    class XNumberFormatsSupplier;
    class XNumberFormatter;
}}}}

namespace dbaccess
{
    typedef ::cppu::ImplHelper6<	::com::sun::star::sdb::XSingleSelectQueryComposer,
                                    ::com::sun::star::sdb::XSingleSelectQueryAnalyzer,
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
            Where,
            Group,
            Having,
            Order
        };
        enum EColumnType
        {
            SelectColumns		= 0,
            GroupByColumns		= 1,
            OrderColumns		= 2,
            ParameterColumns	= 3
        };
        ::connectivity::OSQLParser				m_aSqlParser;
        ::connectivity::OSQLParseTreeIterator	m_aSqlIterator;
        ::std::vector<OPrivateColumns*>			m_aColumnsCollection; // used for columns and parameters of old queries
        ::std::vector<OPrivateTables*>			m_aTablesCollection;
        
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>				m_xConnection;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData>		m_xMetaData;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>			m_xTableSupplier;
        ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatsSupplier >	m_xNumberFormatsSupplier;
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>			m_xColumns;
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >	m_xServiceFactory;
        ::com::sun::star::uno::Reference< ::com::sun::star::script::XTypeConverter >		m_xTypeConverter;

        ::std::vector<OPrivateColumns*>			m_aCurrentColumns;
        OPrivateTables*							m_pTables;		// currently used tables

        ::rtl::OUString							m_aWorkSql;
        ::rtl::OUString							m_sDecimalSep;
        ::com::sun::star::lang::Locale			m_aLocale;
        sal_Int32								m_nBoolCompareMode; // how to compare bool values

        // <properties>
        ::rtl::OUString							m_sOrignal;
        // </properties>


        sal_Bool setORCriteria(::connectivity::OSQLParseNode* pCondition,
            ::std::vector< ::std::vector < ::com::sun::star::beans::PropertyValue > >& rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;
        sal_Bool setANDCriteria(::connectivity::OSQLParseNode* pCondition,
            ::std::vector < ::com::sun::star::beans::PropertyValue > & rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;
        sal_Bool setComparsionPredicate(::connectivity::OSQLParseNode* pCondition,
            ::std::vector < ::com::sun::star::beans::PropertyValue > & rFilters, const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > & xFormatter) const;

        ::rtl::OUString getColumnName(::connectivity::OSQLParseNode* pColumnRef) const;
        ::rtl::OUString getTableAlias(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column ) const;
        sal_Int32 getPredicateType(::connectivity::OSQLParseNode * _pPredicate) const;
        // clears all Columns,Parameters and tables and insert it to their vectors
        void clearCurrentCollections();

        ::rtl::OUString getStatementPart(::std::const_mem_fun_t< const ::connectivity::OSQLParseNode*,::connectivity::OSQLParseTreeIterator>& _aGetFunctor);
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
                    getStructuredCondition( ::std::const_mem_fun_t< const ::connectivity::OSQLParseNode*,::connectivity::OSQLParseTreeIterator>& _aGetFunctor );

        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >
                    setColumns( EColumnType _eType
                    ,::std::const_mem_fun_t< ::vos::ORef< ::connectivity::OSQLColumns>,::connectivity::OSQLParseTreeIterator>& _aGetFunctor );

        //helper methods for mem_fun_t
        inline bool implSetFilter(::rtl::OUString _sFilter) { setFilter(_sFilter); return true;}
        inline bool implSetHavingClause(::rtl::OUString _sFilter) { setHavingClause(_sFilter); return true;}

        /** returns the part of the seelect statement
            @param	_ePart
                Which part should be returned.
            @param	_bWithKeyword
                If <TRUE/> the keyword will be added too. Otherwise not.
            
            @return
                The part of the select statement.
        */
        ::rtl::OUString getSQLPart(SQLPart _ePart,sal_Bool _bWithKeyword = sal_True);

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
        virtual void SAL_CALL setFilter( const ::rtl::OUString& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setStructuredFilter( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendFilterByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column, sal_Bool andCriteria ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendGroupByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setGroup( const ::rtl::OUString& group ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setHavingClause( const ::rtl::OUString& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setStructuredHavingFilter( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > >& filter ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL appendHavingFilterByColumn( const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& column, sal_Bool andCriteria ) throw (::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
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
        virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue > > SAL_CALL getStructuredHavingFilter(  ) throw (::com::sun::star::uno::RuntimeException);
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
