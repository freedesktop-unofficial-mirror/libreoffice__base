/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DbAdminImpl.hxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-05-10 10:22:58 $
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

#ifndef _DBAUI_DBADMINIMPL_HXX_
#define _DBAUI_DBADMINIMPL_HXX_

#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDRIVER_HPP_
#include <com/sun/star/sdbc/XDriver.hpp>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

class Window;
//.........................................................................
namespace dbaui
{
//.........................................................................
    class IItemSetHelper;
    //========================================================================
    //= ODbDataSourceAdministrationHelper
    //========================================================================
    class ODbDataSourceAdministrationHelper
    {
    public:
        DECLARE_STL_MAP(sal_Int32, ::rtl::OUString, ::std::less< sal_Int32 >, MapInt2String);

    private:
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >
                            m_xORB;					/// service factory
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >
                                m_xDatabaseContext;		/// database context we're working in
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XNamingService >
                                m_xDynamicContext;		/// just another interface of the context ...
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >   m_xDatasource;
        ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >         m_xModel;

        ::com::sun::star::uno::Any				m_aDataSourceOrName;
        typedef	::std::set< ::rtl::OUString >	StringSet;
        typedef	StringSet::const_iterator		ConstStringSetIterator;

        
        MapInt2String			m_aDirectPropTranslator;	/// translating property id's into names (direct properties of a data source)
        MapInt2String			m_aIndirectPropTranslator;	/// translating property id's into names (indirect properties of a data source)
        Window*					m_pParent;
        IItemSetHelper*			m_pItemSetHelper;
    public:

        ODbDataSourceAdministrationHelper(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB
                                        ,Window* _pParent
                                        ,IItemSetHelper* _pItemSetHelper);

        /** translate the current dialog SfxItems into driver relevant PropertyValues
            @see successfullyConnected
        */
        sal_Bool	getCurrentSettings(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rDriverParams);

        /** to be called if the settings got from getCurrentSettings have been used for successfully connecting
            @see getCurrentSettings
        */
        void		successfullyConnected();

        /// clear the password in the current data source's item set
        void		clearPassword();

        inline ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > getORB() const { return m_xORB; }

        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess > getDatabaseContext() const { return m_xDatabaseContext; }
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XNamingService > getDynamicContext() const { return m_xDynamicContext; }

        /** creates a new connection. The caller is responsible to dispose it !!!!
        */
        ::std::pair< ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >,sal_Bool>		createConnection();

        /** return the corresponding driver for the selected URL
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDriver >			getDriver();

        /** returns the data source the dialog is currently working with
        */
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >	getCurrentDataSource();
        // returns the Url of a database document
        String              getDocumentUrl(SfxItemSet& _rDest);

        void setDataSourceOrName( const ::com::sun::star::uno::Any& _rDataSourceOrName );

        /** extracts the connection type from the given set<p/>
            The connection type is determined by the value of the DSN item, analyzed by the TypeCollection item.
        */
        DATASOURCE_TYPE		getDatasourceType(const SfxItemSet& _rSet) const;

        /** returns the connection URL
            @return
                The connection URL
        */
        String getConnectionURL() const;

        /// fill the nescessary information from the url line
        void convertUrl(SfxItemSet& _rDest);

        const MapInt2String& getIndirectProperties() const { return m_aIndirectPropTranslator; }

        /** translates properties of an UNO data source into SfxItems
            @param	_rxSource
                The data source
            @param	_rDest
                The item set to fill.
        */
        void translateProperties(
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxSource,
                SfxItemSet& _rDest);

        /** translate SfxItems into properties of an UNO data source
            @param	_rSource
                The item set to read from.
            @param	_rxDest
                The data source to fill.
        */
        void translateProperties(
                const SfxItemSet& _rSource,
                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxDest);

        sal_Bool saveChanges(const SfxItemSet& _rSource);
    protected:
        /** fill a data source info array with the settings from a given item set
        */
        void fillDatasourceInfo(const SfxItemSet& _rSource, ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue >& _rInfo);

        /// translate the given value into an SfxPoolItem, put this into the given set under the given id
        void		implTranslateProperty(SfxItemSet& _rSet, sal_Int32  _nId, const ::com::sun::star::uno::Any& _rValue);
        
        /// translate the given SfxPoolItem into an <type scope="com.sun.star.Any">uno</type>
        ::com::sun::star::uno::Any implTranslateProperty(const SfxPoolItem* _pItem);

        /// translate the given SfxPoolItem into an <type scope="com.sun.star.Any">uno</type>, set it (under the given name) on the given property set
        void		implTranslateProperty(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxSet, const ::rtl::OUString& _rName, const SfxPoolItem* _pItem);

        /** check if the data source described by the given set needs authentication<p/>
            The return value depends on the data source type only.
        */
        sal_Bool			hasAuthentication(const SfxItemSet& _rSet) const;

#ifdef DBG_UTIL
        ::rtl::OString translatePropertyId( sal_Int32 _nId );
#endif
    };

//.........................................................................
}	// namespace dbaui
//.........................................................................

#endif // _DBAUI_DBADMINIMPL_HXX_

