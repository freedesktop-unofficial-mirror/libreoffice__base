/*************************************************************************
 *
 *  $RCSfile: dsntypes.cxx,v $
 *
 *  $Revision: 1.23 $
 *
 *  last change: $Author: kz $ $Date: 2005-01-21 17:20:52 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _DBAUI_DSNTYPES_HXX_
#include "dsntypes.hxx"
#endif
#ifndef _DBU_MISC_HRC_
#include "dbu_misc.hrc"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _DBU_MISCRES_HRC_
#include "dbumiscres.hrc"
#endif
#ifndef _UNOTOOLS_CONFIGNODE_HXX_
#include <unotools/confignode.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _TOOLS_RC_HXX
#include <tools/rc.hxx>
#endif
// --- needed because of the solar mutex
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _OSL_FILE_HXX_
#include <osl/file.hxx>
#endif
// ---
#ifndef _COM_SUN_STAR_SDBC_XDRIVERACCESS_HPP_ 
#include <com/sun/star/sdbc/XDriverAccess.hpp>
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
//.........................................................................
namespace dbaui
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::sdbc;

    namespace 
    {
        void lcl_extractHostAndPort(const String& _sUrl,String& _sHostname,sal_Int32& _nPortNumber)
        {
            if ( _sUrl.GetTokenCount(':') >= 2 )
            {
                _sHostname		= _sUrl.GetToken(0,':');
                _nPortNumber	= _sUrl.GetToken(1,':').ToInt32();
            }
        }
        class ODataSourceTypeStringListResource : public Resource
        {
            ::std::vector<String>	m_aStrings;
        public:
            ODataSourceTypeStringListResource(USHORT _nResId ) : Resource(ModuleRes(_nResId))
            {
                m_aStrings.reserve(STR_END);
                for (int i = STR_MYSQL_ODBC; i < STR_END ; ++i)
                {
                    m_aStrings.push_back(String(ResId(i)));
                }
                
            }
            ~ODataSourceTypeStringListResource()
            {
                FreeResource();
            }
            /** fill the vector with our readed strings
                @param	_rToFill
                    Vector to fill.
            */
            inline void fill( ::std::vector<String>& _rToFill )
            {
                _rToFill = m_aStrings;
            }


            /** returns the String with a given resource id
                @param	_nResId
                    The resource id. It will not be checked if this id exists.
                
                @return	String
                    The string.
            */
            String getString(USHORT _nResId) 
            {
                return String(ResId(_nResId));
            }
        };
    }
//=========================================================================
//= ODsnTypeCollection
//=========================================================================
DBG_NAME(ODsnTypeCollection)
//-------------------------------------------------------------------------
ODsnTypeCollection::ODsnTypeCollection()
#ifdef DBG_UTIL
:m_nLivingIterators(0)
#endif
{
    ::vos::OGuard aGuard( Application::GetSolarMutex() );
    DBG_CTOR(ODsnTypeCollection,NULL); 
    ODataSourceTypeStringListResource aTypes(RSC_DATASOURCE_TYPES);
    aTypes.fill(m_aDsnPrefixes);

    ODataSourceTypeStringListResource aDisplayNames(RSC_DATASOURCE_TYPE_UINAMES);
    aDisplayNames.fill(m_aDsnTypesDisplayNames);


    DBG_ASSERT(m_aDsnTypesDisplayNames.size() == m_aDsnPrefixes.size(),
        "ODsnTypeCollection::ODsnTypeCollection : invalid resources !");
    String sCurrentType;

    for (StringVector::iterator aIter = m_aDsnPrefixes.begin();aIter != m_aDsnPrefixes.end();++aIter)
    {
        m_aDsnTypes.push_back(implDetermineType(*aIter));
    }
}

//-------------------------------------------------------------------------
ODsnTypeCollection::~ODsnTypeCollection()
{
    DBG_DTOR(ODsnTypeCollection,NULL); 
    DBG_ASSERT(0 == m_nLivingIterators, "ODsnTypeCollection::~ODsnTypeCollection : there are still living iterator objects!");	
}
// -----------------------------------------------------------------------------
void ODsnTypeCollection::initUserDriverTypes(const Reference< XMultiServiceFactory >& _rxORB)
{
    // read the user driver out of the configuration
    // the config node where all pooling relevant info are stored under
    ::utl::OConfigurationTreeRoot aUserDefinedDriverRoot = ::utl::OConfigurationTreeRoot::createWithServiceFactory(
        _rxORB, ::dbaui::getUserDefinedDriverNodeName(), -1, ::utl::OConfigurationTreeRoot::CM_READONLY);

    if ( aUserDefinedDriverRoot.isValid() )
    {
        Sequence< ::rtl::OUString > aDriverKeys = aUserDefinedDriverRoot.getNodeNames();
        const ::rtl::OUString* pDriverKeys = aDriverKeys.getConstArray();
        const ::rtl::OUString* pDriverKeysEnd = pDriverKeys + aDriverKeys.getLength();
        for (sal_Int32 i=0;pDriverKeys != pDriverKeysEnd && i <= DST_USERDEFINE10; ++pDriverKeys)
        {
            ::utl::OConfigurationNode aThisDriverSettings = aUserDefinedDriverRoot.openNode(*pDriverKeys);
            if ( aThisDriverSettings.isValid() )
            {
                // read the needed information
                ::rtl::OUString sDsnPrefix,sDsnTypeDisplayName,sExtension;
                aThisDriverSettings.getNodeValue(getDriverTypeDisplayNodeName()) >>= sDsnTypeDisplayName;
                aThisDriverSettings.getNodeValue(getDriverDsnPrefixNodeName()) >>= sDsnPrefix;
                aThisDriverSettings.getNodeValue(getDriverExtensionNodeName()) >>= sExtension;

                m_aDsnTypesDisplayNames.push_back(sDsnTypeDisplayName);
                m_aDsnPrefixes.push_back(sDsnPrefix);
                m_aDsnTypes.push_back(static_cast<DATASOURCE_TYPE>(DST_USERDEFINE1 + i++));
                m_aUserExtensions.push_back(sExtension);
            }
        }
    }
}

//-------------------------------------------------------------------------
DATASOURCE_TYPE ODsnTypeCollection::getType(const String& _rDsn) const
{
    DATASOURCE_TYPE eType = DST_UNKNOWN;
    // look for user defined driver types
    StringVector::const_iterator aIter = m_aDsnPrefixes.begin();
    StringVector::const_iterator aEnd = m_aDsnPrefixes.end();
    for (; aIter != aEnd; ++aIter)
    {
        if ( _rDsn.Len() >= aIter->Len() && aIter->EqualsIgnoreCaseAscii(_rDsn,0, aIter->Len()) )
        {
            size_t nPos = (aIter - m_aDsnPrefixes.begin());
            if ( nPos < m_aDsnTypes.size() )
            {
                eType = m_aDsnTypes[nPos];
                break;
            }
        }
    }
    return eType;
}

//-------------------------------------------------------------------------
String ODsnTypeCollection::getTypeDisplayName(DATASOURCE_TYPE _eType) const
{
    String sDisplayName;

    sal_Int32 nIndex = implDetermineTypeIndex(_eType);
    if ((nIndex >= 0) && (nIndex < (sal_Int32)m_aDsnTypesDisplayNames.size()))
        sDisplayName = m_aDsnTypesDisplayNames[nIndex];

    return sDisplayName;
}

//-------------------------------------------------------------------------
String ODsnTypeCollection::getDatasourcePrefix(DATASOURCE_TYPE _eType) const
{
    String sPrefix;
    sal_Int32 nIndex = implDetermineTypeIndex(_eType);
    if ((nIndex >= 0) && (nIndex < (sal_Int32)m_aDsnPrefixes.size()))
        sPrefix = m_aDsnPrefixes[nIndex];

    return sPrefix;
}

//-------------------------------------------------------------------------
String ODsnTypeCollection::cutPrefix(const String& _rDsn) const
{
    DATASOURCE_TYPE eType = getType(_rDsn);
    String sPrefix = getDatasourcePrefix(eType);
    return _rDsn.Copy(sPrefix.Len());
}
// -----------------------------------------------------------------------------
namespace
{
    ::rtl::OUString lcl_getEmbeddedDatabases()
    {
        static ::rtl::OUString s_sNodeName(RTL_CONSTASCII_USTRINGPARAM("org.openoffice.Office.DataAccess/EmbeddedDatabases"));
        return s_sNodeName;
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString lcl_getDefaultEmbeddedDatabase()
    {
        static ::rtl::OUString s_sNodeName(RTL_CONSTASCII_USTRINGPARAM("DefaultEmbeddedDatabase"));
        return s_sNodeName;
    }
    // -----------------------------------------------------------------------------
    ::rtl::OUString lcl_getEmbeddedDatabaseNames()
    {
        static ::rtl::OUString s_sNodeName(RTL_CONSTASCII_USTRINGPARAM("EmbeddedDatabaseNames"));
        return s_sNodeName;
    }
    // -----------------------------------------------------------------------------
    ::utl::OConfigurationNode lcl_getEmbeddedDatabase(const Reference< XMultiServiceFactory >& _rxORB)
    {
        ::utl::OConfigurationTreeRoot aEmbeddedDatabases = ::utl::OConfigurationTreeRoot::createWithServiceFactory(
            _rxORB, ::dbaui::lcl_getEmbeddedDatabases(), -1, ::utl::OConfigurationTreeRoot::CM_READONLY);

        if ( aEmbeddedDatabases.isValid() )
        {
            ::rtl::OUString sDefaultEmbededDatabaseName;
            aEmbeddedDatabases.getNodeValue(::dbaui::lcl_getDefaultEmbeddedDatabase()) >>= sDefaultEmbededDatabaseName;

            ::utl::OConfigurationNode aEmbddedDatabaseNames = aEmbeddedDatabases.openNode(::dbaui::lcl_getEmbeddedDatabaseNames());
            if ( aEmbddedDatabaseNames.isValid() )
            {
                ::utl::OConfigurationNode aEmbeddedDatabase = aEmbddedDatabaseNames.openNode(sDefaultEmbededDatabaseName);
                if ( aEmbeddedDatabase.isValid() )
                {
                    return aEmbeddedDatabase;
                }
            }
        }
        return ::utl::OConfigurationNode();
    }
}
// -----------------------------------------------------------------------------
void ODsnTypeCollection::extractHostNamePort(const String& _rDsn,String& _sDatabaseName,String& _rsHostname,sal_Int32& _nPortNumber) const
{
    DATASOURCE_TYPE eType = getType(_rDsn);
    String sUrl = cutPrefix(_rDsn);
    switch( eType )
    {
        case DST_ORACLE_JDBC:
            lcl_extractHostAndPort(sUrl,_rsHostname,_nPortNumber);
            if ( !_rsHostname.Len() && sUrl.GetTokenCount(':') == 2 )
            {
                _nPortNumber = -1;
                _rsHostname = sUrl.GetToken(0,':');
            }
            if ( _rsHostname.Len() )
                _rsHostname = _rsHostname.GetToken(_rsHostname.GetTokenCount('@') - 1,'@');
            _sDatabaseName = sUrl.GetToken(sUrl.GetTokenCount(':') - 1,':');
            break;
        case DST_LDAP:
            lcl_extractHostAndPort(sUrl,_sDatabaseName,_nPortNumber);
            break;
        case DST_ADABAS:
            if ( sUrl.GetTokenCount(':') == 2 )
                _rsHostname = sUrl.GetToken(0,':');
            _sDatabaseName = sUrl.GetToken(sUrl.GetTokenCount(':') - 1,':');
            break;
        case DST_MYSQL_JDBC:
            {
                lcl_extractHostAndPort(sUrl,_rsHostname,_nPortNumber);

                if ( _nPortNumber == -1 && !_rsHostname.Len() && sUrl.GetTokenCount('/') == 2 )
                    _rsHostname = sUrl.GetToken(0,'/');
                _sDatabaseName = sUrl.GetToken(sUrl.GetTokenCount('/') - 1,'/');
            }
            break;
        case DST_MSACCESS:
            {
                ::rtl::OUString sNewFileName;
                if ( ::osl::FileBase::getFileURLFromSystemPath( sUrl, sNewFileName ) == ::osl::FileBase::E_None )
                {
                    _sDatabaseName = sNewFileName;
                }
            }
            break;
    }
}
//-------------------------------------------------------------------------
String ODsnTypeCollection::getTypeDisplayName(const String& _rDsn) const
{
    return getTypeDisplayName(getType(_rDsn));
}

//-------------------------------------------------------------------------
sal_Bool ODsnTypeCollection::isFileSystemBased(DATASOURCE_TYPE _eType) const
{
    switch (_eType)
    {
        case DST_DBASE:
        case DST_FLAT:
        case DST_CALC:
        case DST_MSACCESS:
            return sal_True;

        case DST_USERDEFINE1:
        case DST_USERDEFINE2:
        case DST_USERDEFINE3:
        case DST_USERDEFINE4:
        case DST_USERDEFINE5:
        case DST_USERDEFINE6:
        case DST_USERDEFINE7:
        case DST_USERDEFINE8:
        case DST_USERDEFINE9:
        case DST_USERDEFINE10:
        {
            StringVector::size_type nPos = static_cast<sal_Int16>(_eType-DST_USERDEFINE1);
            return nPos < m_aUserExtensions.size() ? m_aUserExtensions[nPos].Len() != 0 : sal_False;
        }
        default:
            return sal_False;
    }
}


sal_Bool ODsnTypeCollection::supportsTableCreation(DATASOURCE_TYPE _eType)
{     
    BOOL bSupportsTableCreation;
        switch( _eType )
        {
            case DST_MOZILLA:
            case DST_OUTLOOK:
            case DST_OUTLOOKEXP:
            case DST_FLAT:
            case DST_EVOLUTION:
            case DST_CALC:
                bSupportsTableCreation = FALSE;
                break;
            case DST_DBASE:
            case DST_ADABAS:
            case DST_ADO:
            case DST_MSACCESS:
            case DST_MYSQL_ODBC:
            case DST_ODBC:
            case DST_MYSQL_JDBC:
            case DST_ORACLE_JDBC:
            case DST_LDAP:
            case DST_JDBC:
            default:
                bSupportsTableCreation = TRUE;
                break;
        }
        return bSupportsTableCreation;
}
// -----------------------------------------------------------------------------
sal_Bool ODsnTypeCollection::supportsBrowsing(DATASOURCE_TYPE _eType)
{     
    sal_Bool bEnableBrowseButton = sal_False;
    switch( _eType )
    {
        case DST_DBASE:
        case DST_FLAT:
        case DST_CALC:
        case DST_ADABAS:
        case DST_ADO:
        case DST_MSACCESS:
        case DST_MYSQL_ODBC:
        case DST_ODBC:
            bEnableBrowseButton = TRUE;
            break;
        case DST_MYSQL_JDBC:
        case DST_ORACLE_JDBC:
        case DST_LDAP:
        case DST_MOZILLA:
        case DST_OUTLOOK:
        case DST_OUTLOOKEXP:
        case DST_JDBC:
        case DST_EVOLUTION:
            bEnableBrowseButton = FALSE;
            break;
        default:
            bEnableBrowseButton = getTypeExtension(_eType).Len() != 0;
            break;
    }
    return bEnableBrowseButton;
}


//-------------------------------------------------------------------------
sal_Bool ODsnTypeCollection::hasAuthentication(DATASOURCE_TYPE _eType) const
{
    switch (_eType)
    {
        case DST_USERDEFINE1:	/// first user defined driver
        case DST_USERDEFINE2:
        case DST_USERDEFINE3:
        case DST_USERDEFINE4:
        case DST_USERDEFINE5:
        case DST_USERDEFINE6:
        case DST_USERDEFINE7:
        case DST_USERDEFINE8:
        case DST_USERDEFINE9:
        case DST_USERDEFINE10:
        case DST_ADABAS:
        case DST_JDBC:
        case DST_MYSQL_ODBC:
        case DST_ORACLE_JDBC:
        case DST_MYSQL_JDBC:
        case DST_ODBC:
        case DST_ADO:
        case DST_LDAP:
        case DST_CALC:
            return sal_True;
            break;
        case DST_MSACCESS:
        case DST_MOZILLA:
        case DST_EVOLUTION:
        case DST_OUTLOOK:
        case DST_OUTLOOKEXP: //????
        case DST_DBASE:
        case DST_FLAT:
        case DST_EMBEDDED:
        default:
            return sal_False;
    }
}

//-------------------------------------------------------------------------
DATASOURCE_TYPE ODsnTypeCollection::implDetermineType(const String& _rDsn) const
{
    sal_uInt16 nSeparator = _rDsn.Search((sal_Unicode)':');
    if (STRING_NOTFOUND == nSeparator)
    {
        // there should be at least one such separator
        DBG_ERROR("ODsnTypeCollection::implDetermineType : missing the colon !");
        return DST_UNKNOWN;
    }
    // find first :
    sal_uInt16 nOracleSeparator = _rDsn.Search((sal_Unicode)':', nSeparator + 1);
    if ( nOracleSeparator != STRING_NOTFOUND )
    {
        nOracleSeparator = _rDsn.Search((sal_Unicode)':', nOracleSeparator + 1);
        if (nOracleSeparator != STRING_NOTFOUND && _rDsn.EqualsIgnoreCaseAscii("jdbc:oracle:thin", 0, nOracleSeparator))
            return DST_ORACLE_JDBC;
    }

    if (_rDsn.EqualsIgnoreCaseAscii("jdbc", 0, nSeparator))
        return DST_JDBC;

    // find second :
    nSeparator = _rDsn.Search((sal_Unicode)':', nSeparator + 1);
    if (STRING_NOTFOUND == nSeparator)
    {
        // at the moment only jdbc is allowed to have just one separator
        DBG_ERROR("ODsnTypeCollection::implDetermineType : missing the second colon !");
        return DST_UNKNOWN;
    }

    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:adabas", 0, nSeparator))
        return DST_ADABAS;
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:odbc", 0, nSeparator))
        return DST_ODBC;
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:dbase", 0, nSeparator))
        return DST_DBASE;
    
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:ado:", 0, nSeparator))
    {
        nSeparator = _rDsn.Search((sal_Unicode)':', nSeparator + 1);
        if (STRING_NOTFOUND != nSeparator && _rDsn.EqualsIgnoreCaseAscii("sdbc:ado:access",0, nSeparator) )
            return DST_MSACCESS;
        return DST_ADO;	
    }
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:flat:", 0, nSeparator))
        return DST_FLAT;
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:calc:", 0, nSeparator))
        return DST_CALC;

    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:embedded:", 0, nSeparator))
        return DST_EMBEDDED;

    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:address:", 0, nSeparator))
    {
        ++nSeparator;
        if (_rDsn.EqualsIgnoreCaseAscii("mozilla", nSeparator,_rDsn.Len() - nSeparator))
            return DST_MOZILLA;
        if (_rDsn.EqualsIgnoreCaseAscii("ldap:", nSeparator,_rDsn.Len() - nSeparator))
            return DST_LDAP;
        if (_rDsn.EqualsIgnoreCaseAscii("outlook", nSeparator,_rDsn.Len() - nSeparator))
            return DST_OUTLOOK;
        if (_rDsn.EqualsIgnoreCaseAscii("outlookexp", nSeparator,_rDsn.Len() - nSeparator))
            return DST_OUTLOOKEXP;
        if (_rDsn.EqualsIgnoreCaseAscii("evolution", nSeparator,_rDsn.Len() - nSeparator))
            return DST_EVOLUTION;
    }

    // find third :
    nSeparator = _rDsn.Search((sal_Unicode)':', nSeparator + 1);
    if (STRING_NOTFOUND == nSeparator)
    {
        DBG_ERROR("ODsnTypeCollection::implDetermineType : missing the third colon !");
        return DST_UNKNOWN;
    }

    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:mysql:odbc", 0, nSeparator))
        return DST_MYSQL_ODBC;
    if (_rDsn.EqualsIgnoreCaseAscii("sdbc:mysql:jdbc", 0, nSeparator))
        return DST_MYSQL_JDBC;
    
    

    DBG_ERROR("ODsnTypeCollection::implDetermineType : unrecognized data source type !");
    return DST_UNKNOWN;
}
// -----------------------------------------------------------------------------
sal_Int32 ODsnTypeCollection::implDetermineTypeIndex(DATASOURCE_TYPE _eType) const
{
    DBG_ASSERT(
            (m_aDsnTypesDisplayNames.size() == m_aDsnPrefixes.size())
        &&	(m_aDsnTypesDisplayNames.size() == m_aDsnTypes.size()),
        "ODsnTypeCollection::implDetermineTypeIndex : inconsistent structures !");

    // the type of the datasource described by the DSN string
    if (DST_UNKNOWN == _eType)
    {
        return -1;
    }

    // search this type in our arrays
    sal_Int32 nIndex = 0;
    ConstTypeVectorIterator aSearch = m_aDsnTypes.begin();

    for (; aSearch != m_aDsnTypes.end(); ++nIndex, ++aSearch)
        if (*aSearch == _eType)
            return nIndex;

    DBG_ERROR("ODsnTypeCollection::implDetermineTypeIndex : recognized the DSN schema, but did not find the type!");
    return -1;
}
// -----------------------------------------------------------------------------
DATASOURCE_TYPE ODsnTypeCollection::getEmbeddedDatabaseType(const Reference< XMultiServiceFactory >& _rxORB) const
{
    DATASOURCE_TYPE eRet = DST_DBASE;
    ::utl::OConfigurationNode aEmbeddedDatabase = lcl_getEmbeddedDatabase(_rxORB);
    if ( aEmbeddedDatabase.isValid() )
    {
        ::rtl::OUString sURLPrefix = getEmbeddedDatabaseURL(_rxORB);
        Reference< XDriverAccess > xDriverManager(_rxORB->createInstance(SERVICE_SDBC_DRIVERMANAGER), UNO_QUERY);
        if ( xDriverManager.is() && xDriverManager->getDriverByURL(sURLPrefix).is() )
        {
            eRet = DST_EMBEDDED;
        }
    }
    return eRet;
}
// -----------------------------------------------------------------------------
::rtl::OUString ODsnTypeCollection::getEmbeddedDatabaseURL(const Reference< XMultiServiceFactory >& _rxORB) const
{
    ::rtl::OUString sRet;
    ::utl::OConfigurationNode aEmbeddedDatabase = lcl_getEmbeddedDatabase(_rxORB);
    if ( aEmbeddedDatabase.isValid() )
    {
        static ::rtl::OUString s_sURL(RTL_CONSTASCII_USTRINGPARAM("URL"));
        aEmbeddedDatabase.getNodeValue(s_sURL) >>= sRet;
    }
    return sRet;
}
// -----------------------------------------------------------------------------
::rtl::OUString ODsnTypeCollection::getEmbeddedDatabaseUIName(const Reference< XMultiServiceFactory >& _rxORB) const
{
    ::rtl::OUString sRet;
    ::utl::OConfigurationNode aEmbeddedDatabase = lcl_getEmbeddedDatabase(_rxORB);
    if ( aEmbeddedDatabase.isValid() )
    {
        // read the needed information
        static ::rtl::OUString s_sUIName(RTL_CONSTASCII_USTRINGPARAM("UIName"));
        aEmbeddedDatabase.getNodeValue(s_sUIName) >>= sRet;
    }
    return sRet;
}
// -----------------------------------------------------------------------------
Sequence<PropertyValue> ODsnTypeCollection::getEmbeddedDatabaseProperties(const Reference< XMultiServiceFactory >& _rxORB) const
{
    Sequence<PropertyValue> aRet;
    ::utl::OConfigurationNode aEmbeddedDatabase = lcl_getEmbeddedDatabase(_rxORB);
    if ( aEmbeddedDatabase.isValid() )
    {
        static ::rtl::OUString s_sEmbeddedDatabaseSettings(RTL_CONSTASCII_USTRINGPARAM("EmbeddedDatabaseSettings"));
        ::utl::OConfigurationNode aSettings = aEmbeddedDatabase.openNode(s_sEmbeddedDatabaseSettings);
        if ( aSettings.isValid() )
        {
            Sequence< ::rtl::OUString > aNodeNames = aSettings.getNodeNames();
            aRet.realloc(aNodeNames.getLength());
            PropertyValue* pInfos = aRet.getArray();

            for (	const ::rtl::OUString* pNodeNames = aNodeNames.getConstArray() + aNodeNames.getLength() - 1;
                    pNodeNames >= aNodeNames.getConstArray();
                    --pNodeNames, ++pInfos
                )
            {
                ::utl::OConfigurationNode aItemSubNode = aSettings.openNode(*pNodeNames);
                pInfos->Name = *pNodeNames;
                pInfos->Value = aItemSubNode.getNodeValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Value")));
            }
        }			
    }
    return aRet;
}
//-------------------------------------------------------------------------
sal_Int32 ODsnTypeCollection::implDetermineTypeIndex(const String& _rDsn) const
{
    return implDetermineTypeIndex(getType(_rDsn));
}
// -----------------------------------------------------------------------------
String ODsnTypeCollection::getTypeExtension(DATASOURCE_TYPE _eType) const
{ 
    StringVector::size_type nPos = static_cast<sal_Int16>(_eType-DST_USERDEFINE1);
    return nPos < m_aUserExtensions.size() ? m_aUserExtensions[nPos] : String();
}
//-------------------------------------------------------------------------
ODsnTypeCollection::TypeIterator ODsnTypeCollection::begin() const
{
    return TypeIterator(this, 0);
}

//-------------------------------------------------------------------------
ODsnTypeCollection::TypeIterator ODsnTypeCollection::end() const
{
    return TypeIterator(this, m_aDsnTypes.size());
}

//=========================================================================
//= ODsnTypeCollection::TypeIterator
//=========================================================================
//-------------------------------------------------------------------------
ODsnTypeCollection::TypeIterator::TypeIterator(const ODsnTypeCollection* _pContainer, sal_Int32 _nInitialPos)
    :m_pContainer(_pContainer)
    ,m_nPosition(_nInitialPos)
{
    DBG_ASSERT(m_pContainer, "ODsnTypeCollection::TypeIterator::TypeIterator : invalid container!");
#ifdef DBG_UTIL
    ++const_cast<ODsnTypeCollection*>(m_pContainer)->m_nLivingIterators;
#endif
}

//-------------------------------------------------------------------------
ODsnTypeCollection::TypeIterator::TypeIterator(const TypeIterator& _rSource)
    :m_pContainer(_rSource.m_pContainer)
    ,m_nPosition(_rSource.m_nPosition)
{
#ifdef DBG_UTIL
    ++const_cast<ODsnTypeCollection*>(m_pContainer)->m_nLivingIterators;
#endif
}

//-------------------------------------------------------------------------
ODsnTypeCollection::TypeIterator::~TypeIterator()
{
#ifdef DBG_UTIL
    --const_cast<ODsnTypeCollection*>(m_pContainer)->m_nLivingIterators;
#endif
}

//-------------------------------------------------------------------------
DATASOURCE_TYPE	ODsnTypeCollection::TypeIterator::getType() const
{
    DBG_ASSERT(m_nPosition < (sal_Int32)m_pContainer->m_aDsnTypes.size(), "ODsnTypeCollection::TypeIterator::getType : invalid position!");
    return m_pContainer->m_aDsnTypes[m_nPosition];
}

//-------------------------------------------------------------------------
String ODsnTypeCollection::TypeIterator::getPrefix() const
{
    DBG_ASSERT(m_nPosition < (sal_Int32)m_pContainer->m_aDsnPrefixes.size(), "ODsnTypeCollection::TypeIterator::getPrefix : invalid position!");
    return m_pContainer->m_aDsnPrefixes[m_nPosition];
}

//-------------------------------------------------------------------------
String ODsnTypeCollection::TypeIterator::getDisplayName() const
{
    DBG_ASSERT(m_nPosition < (sal_Int32)m_pContainer->m_aDsnTypesDisplayNames.size(), "ODsnTypeCollection::TypeIterator::getDisplayName : invalid position!");
    return m_pContainer->m_aDsnTypesDisplayNames[m_nPosition];
}

//-------------------------------------------------------------------------
const ODsnTypeCollection::TypeIterator&	ODsnTypeCollection::TypeIterator::operator++()
{
    DBG_ASSERT(m_nPosition < (sal_Int32)m_pContainer->m_aDsnTypes.size(), "ODsnTypeCollection::TypeIterator::operator++ : invalid position!");
    if (m_nPosition < (sal_Int32)m_pContainer->m_aDsnTypes.size())
        ++m_nPosition;
    return *this;
}

//-------------------------------------------------------------------------
const ODsnTypeCollection::TypeIterator&	ODsnTypeCollection::TypeIterator::operator--()
{
    DBG_ASSERT(m_nPosition >= 0, "ODsnTypeCollection::TypeIterator::operator-- : invalid position!");
    if (m_nPosition >= 0)
        --m_nPosition;
    return *this;
}

//-------------------------------------------------------------------------
bool operator==(const ODsnTypeCollection::TypeIterator& lhs, const ODsnTypeCollection::TypeIterator& rhs)
{
    return (lhs.m_pContainer == rhs.m_pContainer) && (lhs.m_nPosition == rhs.m_nPosition);
}

//=========================================================================
//= DbuTypeCollectionItem
//=========================================================================
TYPEINIT1(DbuTypeCollectionItem, SfxPoolItem);
//-------------------------------------------------------------------------
DbuTypeCollectionItem::DbuTypeCollectionItem(sal_Int16 _nWhich, ODsnTypeCollection* _pCollection)
    :SfxPoolItem(_nWhich)
    ,m_pCollection(_pCollection)
{
}

//-------------------------------------------------------------------------
DbuTypeCollectionItem::DbuTypeCollectionItem(const DbuTypeCollectionItem& _rSource)
    :SfxPoolItem(_rSource)
    ,m_pCollection(_rSource.getCollection())
{
}

//-------------------------------------------------------------------------
int DbuTypeCollectionItem::operator==(const SfxPoolItem& _rItem) const
{
    DbuTypeCollectionItem* pCompare = PTR_CAST(DbuTypeCollectionItem, &_rItem);
    return pCompare && (pCompare->getCollection() == getCollection());
}

//-------------------------------------------------------------------------
SfxPoolItem* DbuTypeCollectionItem::Clone(SfxItemPool* _pPool) const
{
    return new DbuTypeCollectionItem(*this);
}
//.........................................................................
}	// namespace dbaui
//.........................................................................

