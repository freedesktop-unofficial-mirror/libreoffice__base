/*************************************************************************
 *
 *  $RCSfile: UITools.cxx,v $
 *
 *  $Revision: 1.22 $
 *
 *  last change: $Author: oj $ $Date: 2001-10-18 12:04:10 $
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

#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_EXTRACT_HXX_
#include <comphelper/extract.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XCOMPLETEDCONNECTION_HPP_
#include <com/sun/star/sdb/XCompletedConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_SQLCONTEXT_HPP_
#include <com/sun/star/sdb/SQLContext.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XKEYSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XKeysSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_DIALOGS_XEXECUTABLEDIALOG_HPP_ 
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXACCESS_HPP_
#include <com/sun/star/container/XIndexAccess.hpp>
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _TOOLKIT_AWT_VCLXWINDOW_HXX_
#include <toolkit/awt/vclxwindow.hxx>
#endif
#ifndef _VCL_STDTEXT_HXX 
#include <vcl/stdtext.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSETINFO_HPP_
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_TEXTALIGN_HPP_
#include <com/sun/star/awt/TextAlign.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
#include <com/sun/star/awt/FontDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWEIGHT_HPP_
#include <com/sun/star/awt/FontWeight.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTRELIEF_HPP_
#include <com/sun/star/awt/FontRelief.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWIDTH_HPP_
#include <com/sun/star/awt/FontWidth.hpp>
#endif
#ifndef DBAUI_SBATTRDLG_HRC
#include "dlgattr.hrc"
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif					  
#ifndef DBAUI_FIELDDESCRIPTIONS_HXX
#include "FieldDescriptions.hxx"
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif

#ifndef _SVX_SVXIDS_HRC
#include <svx/svxids.hrc>
#endif

#define ITEMID_HORJUSTIFY		SID_ATTR_ALIGN_HOR_JUSTIFY
#define ITEMID_VERJUSTIFY		SID_ATTR_ALIGN_VER_JUSTIFY
#define ITEMID_ORIENTATION		SID_ATTR_ALIGN_ORIENTATION
#define ITEMID_LINEBREAK		SID_ATTR_ALIGN_LINEBREAK
#define ITEMID_MARGIN			SID_ATTR_ALIGN_MARGIN
#define ITEMID_NUMBERINFO		SID_ATTR_NUMBERFORMAT_INFO

#ifndef _SFXITEMPOOL_HXX 
#include <svtools/itempool.hxx>
#endif
#ifndef _SFXITEMSET_HXX //autogen wg. SfxItemSet
#include <svtools/itemset.hxx>
#endif
#ifndef DBACCESS_SBA_GRID_HRC
#include "sbagrid.hrc"
#endif
#ifndef _SFXRNGITEM_HXX
#include <svtools/rngitem.hxx>
#endif
#ifndef _SFXINTITEM_HXX 
#include <svtools/intitem.hxx>
#endif
#ifndef _SVX_ALGITEM_HXX 
#include <svx/algitem.hxx>
#endif
#ifndef _SVX_NUMINF_HXX 
#include <svx/numinf.hxx>
#endif
#define _ZFORLIST_DECLARE_TABLE
#ifndef _SVX_NUMINF_HXX 
#include <svx/numinf.hxx>
#endif
#ifndef _EEITEMID_HXX
#include <svx/eeitemid.hxx>
#endif
#ifndef _ZFORLIST_HXX 
#include <svtools/zforlist.hxx>
#endif
#ifndef DBAUI_SBATTRDLG_HXX
#include "dlgattr.hxx"
#endif
#ifndef _SV_MSGBOX_HXX 
#include <vcl/msgbox.hxx>
#endif
// .........................................................................
namespace dbaui
{
// .........................................................................
using namespace ::dbtools;
using namespace ::comphelper;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::task;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;
using namespace ::com::sun::star::ui::dialogs;



// -----------------------------------------------------------------------------
void composeTableName(	const Reference< XDatabaseMetaData >& _rxMetaData,
                        const Reference< XPropertySet >& _rxTable,
                        ::rtl::OUString& _rComposedName,
                        sal_Bool _bQuote)
{
    OSL_ENSURE(_rxTable.is(),"Table can not be null!");
    if(_rxTable.is())
    {
        Reference< XPropertySetInfo > xInfo = _rxTable->getPropertySetInfo();
        if(xInfo->hasPropertyByName(PROPERTY_CATALOGNAME) && xInfo->hasPropertyByName(PROPERTY_SCHEMANAME) && xInfo->hasPropertyByName(PROPERTY_NAME))
        {
            ::rtl::OUString aCatalog,aSchema,aTable;
            _rxTable->getPropertyValue(PROPERTY_CATALOGNAME)>>= aCatalog;
            _rxTable->getPropertyValue(PROPERTY_SCHEMANAME) >>= aSchema;
            _rxTable->getPropertyValue(PROPERTY_NAME)		>>= aTable;

            ::dbtools::composeTableName(_rxMetaData,aCatalog,aSchema,aTable,_rComposedName,_bQuote);
        }
    }
}
// -----------------------------------------------------------------------------

SQLExceptionInfo createConnection(	const ::rtl::OUString& _rsDataSourceName,
                                     const Reference< ::com::sun::star::container::XNameAccess >& _xDatabaseContext,
                                    const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rMF,
                                    Reference< ::com::sun::star::lang::XEventListener>& _rEvtLst,
                                    Reference< ::com::sun::star::sdbc::XConnection>& _rOUTConnection )
{
    Any aValue;
    try 
    { 
        aValue = _xDatabaseContext->getByName(_rsDataSourceName); 
    }
    catch(Exception&) 
    {
    }
    SQLExceptionInfo aInfo;
    Reference<XPropertySet> xProp;
    aValue >>= xProp;
    if (!xProp.is())
    {
        OSL_ENSURE(0,"createConnection: coult not retrieve the data source!");
        return aInfo;
    }

    ::rtl::OUString sPwd, sUser;
    sal_Bool bPwdReq = sal_False;
    try
    {
        xProp->getPropertyValue(PROPERTY_PASSWORD) >>= sPwd;
        bPwdReq = ::cppu::any2bool(xProp->getPropertyValue(PROPERTY_ISPASSWORDREQUIRED));
        xProp->getPropertyValue(PROPERTY_USER) >>= sUser;
    }
    catch(Exception&)
    {
        OSL_ENSURE(0,"createConnection: error while retrieving data source properties!");
    }

    
    try
    {
        if(bPwdReq && !sPwd.getLength())
        {	// password required, but empty -> connect using an interaction handler
            Reference<XCompletedConnection> xConnectionCompletion(xProp, UNO_QUERY);
            if (!xConnectionCompletion.is())
            {
                OSL_ENSURE(0,"createConnection: missing an interface ... need an error message here!");
            }
            else
            {	// instantiate the default SDB interaction handler
                Reference< XInteractionHandler > xHandler(_rMF->createInstance(SERVICE_SDB_INTERACTION_HANDLER), UNO_QUERY);
                if (!xHandler.is())
                {
                    OSL_ENSURE(sal_False, "createConnection: could not instantiate an interaction handler!");
                    // ShowServiceNotAvailableError(NULL, String(SERVICE_SDB_INTERACTION_HANDLER), sal_True);
                        // TODO: a real parent!
                }
                else
                    _rOUTConnection = xConnectionCompletion->connectWithCompletion(xHandler);
            }
        }
        else
        {
            Reference<XDataSource> xDataSource(xProp,UNO_QUERY);
            _rOUTConnection = xDataSource->getConnection(sUser, sPwd);
        }
        // be notified when connection is in disposing
        Reference< XComponent >  xComponent(_rOUTConnection, UNO_QUERY);
        if (xComponent.is() && _rEvtLst.is())
            xComponent->addEventListener(_rEvtLst);
    }
    catch(SQLContext& e) { aInfo = SQLExceptionInfo(e); }
    catch(SQLWarning& e) { aInfo = SQLExceptionInfo(e); }
    catch(SQLException& e) { aInfo = SQLExceptionInfo(e); }
    catch(Exception&) { OSL_ENSURE(0,"SbaTableQueryBrowser::OnExpandEntry: could not connect - unknown exception!"); }

    //	showError(aInfo);

    return aInfo;
}
// -----------------------------------------------------------------------------
void showError(const SQLExceptionInfo& _rInfo,Window* _pParent,const Reference< XMultiServiceFactory >& _xFactory)
{
    OSL_ENSURE(_pParent,"showError: Parent window must be NOT NULL!");
    ::dbtools::showError(_rInfo,VCLUnoHelper::GetInterface(_pParent),_xFactory);
}
// -----------------------------------------------------------------------------
::std::vector< Reference<XNameAccess> > getKeyColumns(const Reference<XPropertySet >& _rxTable,
                                                      sal_Int32 _nKeyType)
{
    // use keys and indexes for excat postioning
    // first the keys
    Reference<XKeysSupplier> xKeySup(_rxTable,UNO_QUERY);
    Reference<XIndexAccess> xKeys;
    if(xKeySup.is())
        xKeys = xKeySup->getKeys();

    ::std::vector< Reference<XNameAccess> > vRet;
    
    if(xKeys.is())
    {
        Reference<XPropertySet> xProp;
        for(sal_Int32 i=0;i< xKeys->getCount();++i)
        {
            xKeys->getByIndex(i) >>= xProp;
            sal_Int32 nKeyType = 0;
            xProp->getPropertyValue(PROPERTY_TYPE) >>= nKeyType;
            if(_nKeyType == nKeyType)
            {
                Reference<XColumnsSupplier> xKeyColsSup(xProp,UNO_QUERY);
                OSL_ENSURE(xKeyColsSup.is(),"Columnsupplier is null!");
                vRet.push_back(xKeyColsSup->getColumns());
            }
        }
    }

    return vRet;
}
// -----------------------------------------------------------------------------

const OTypeInfo* getTypeInfoFromType(const OTypeInfoMap& _rTypeInfo,
                               sal_Int32 _nType,
                               const ::rtl::OUString& _sTypeName,
                               sal_Int32 _nPrecision,
                               sal_Int32 _nScale,
                               sal_Bool& _brForceToType)
{
    const OTypeInfo* pTypeInfo = NULL;
    _brForceToType = sal_False;
    // search for type
    ::std::pair<OTypeInfoMap::const_iterator, OTypeInfoMap::const_iterator> aPair = _rTypeInfo.equal_range(_nType);
    OTypeInfoMap::const_iterator aIter = aPair.first;
    if(aIter != _rTypeInfo.end()) // compare with end is correct here
    {
        for(;aIter != aPair.second;++aIter)
        {
            // search the best matching type
    #ifdef DBG_UTIL
            ::rtl::OUString sDBTypeName = aIter->second->aTypeName;
            sal_Int32		nDBTypePrecision = aIter->second->nPrecision;
            sal_Int32		nDBTypeScale = aIter->second->nMaximumScale;
    #endif
            if	(	(	!_sTypeName.getLength()
                    ||	(aIter->second->aTypeName.equalsIgnoreAsciiCase(_sTypeName))
                    )
                &&	(aIter->second->nPrecision		>= _nPrecision)
                &&	(aIter->second->nMaximumScale	>= _nScale)
                )
                break;
        }

        if (aIter == aPair.second)
        {
            for(aIter = aPair.first; aIter != aPair.second; ++aIter)
            {
                // search the best matching type (now comparing the local names)
                if	(	(aIter->second->aLocalTypeName.equalsIgnoreAsciiCase(_sTypeName))
                    &&	(aIter->second->nPrecision		>= _nPrecision)
                    &&	(aIter->second->nMaximumScale	>= _nScale)
                    )
                {
                    OSL_ENSURE(sal_False,
                        (	::rtl::OString("getTypeInfoFromType: assuming column type ")
                        +=	::rtl::OString(aIter->second->aTypeName.getStr(), aIter->second->aTypeName.getLength(), gsl_getSystemTextEncoding())
                        +=	::rtl::OString("\" (expected type name ")
                        +=	::rtl::OString(_sTypeName.getStr(), _sTypeName.getLength(), gsl_getSystemTextEncoding())
                        +=	::rtl::OString(" matches the type's local name).")).getStr());
                    break;
                }
            }
        }

        if (aIter == aPair.second)
        {	// no match for the names, no match for the local names
            // -> drop the precision and the scale restriction, accept any type with the property
            // type id (nType)

            // we can not assert here because we could be in d&d
/*
            OSL_ENSURE(sal_False,
                (	::rtl::OString("getTypeInfoFromType: did not find a matching type")
                +=	::rtl::OString(" (expected type name: ")
                +=	::rtl::OString(_sTypeName.getStr(), _sTypeName.getLength(), gsl_getSystemTextEncoding())
                +=	::rtl::OString(")! Defaulting to the first matching type.")).getStr());
*/
            pTypeInfo = aPair.first->second;
            _brForceToType = sal_True;
        }
        else
            pTypeInfo = aIter->second;
    }
    else
    {
        ::comphelper::TStringMixEqualFunctor aCase(sal_False);
        // search for typeinfo where the typename is equal _sTypeName
        OTypeInfoMap::const_iterator aFind = ::std::find_if(_rTypeInfo.begin(),
                                                            _rTypeInfo.end(),
                                                            ::std::compose1(
                                                                ::std::bind2nd(aCase, _sTypeName),
                                                                ::std::compose1(
                                                                    ::std::mem_fun(&OTypeInfo::getDBName),
                                                                    ::std::select2nd<OTypeInfoMap::value_type>())
                                                                )
                                                            );
        if(aFind != _rTypeInfo.end())
            pTypeInfo = aFind->second;
    }
        

    OSL_ENSURE(pTypeInfo, "getTypeInfoFromType: no type info found for this type!");
    return pTypeInfo;
}
// -----------------------------------------------------------------------------
void fillTypeInfo(	const Reference< ::com::sun::star::sdbc::XConnection>& _rxConnection,
                    const String& _rsTypeNames,
                    OTypeInfoMap& _rTypeInfoMap,
                    ::std::vector<OTypeInfoMap::iterator>& _rTypeInfoIters)
{
    if(!_rxConnection.is())
        return;
    Reference< XResultSet> xRs = _rxConnection->getMetaData ()->getTypeInfo ();
    Reference< XRow> xRow(xRs,UNO_QUERY);
    // Information for a single SQL type
    if(xRs.is())
    {
        static const ::rtl::OUString aB1 = ::rtl::OUString::createFromAscii(" [ ");
        static const ::rtl::OUString aB2 = ::rtl::OUString::createFromAscii(" ]");
        // Loop on the result set until we reach end of file
        while (xRs->next()) 
        {
            OTypeInfo* pInfo = new OTypeInfo();
            pInfo->aTypeName		= xRow->getString (1);
            pInfo->nType			= xRow->getShort (2);
            pInfo->nPrecision		= xRow->getInt (3);
            pInfo->aLiteralPrefix	= xRow->getString (4);
            pInfo->aLiteralSuffix	= xRow->getString (5);
            pInfo->aCreateParams	= xRow->getString (6);
            pInfo->bNullable		= xRow->getInt (7) == ColumnValue::NULLABLE;
            pInfo->bCaseSensitive	= xRow->getBoolean (8);
            pInfo->nSearchType		= xRow->getShort (9);
            pInfo->bUnsigned		= xRow->getBoolean (10);
            pInfo->bCurrency		= xRow->getBoolean (11);
            pInfo->bAutoIncrement	= xRow->getBoolean (12);
            pInfo->aLocalTypeName	= xRow->getString (13);
            pInfo->nMinimumScale	= xRow->getShort (14);
            pInfo->nMaximumScale	= xRow->getShort (15);
            pInfo->nNumPrecRadix	= xRow->getInt (18);
            
            String aName;
            switch(pInfo->nType)
            {
                case DataType::CHAR:
                    aName = _rsTypeNames.GetToken(TYPE_CHAR);
                    break;
                case DataType::VARCHAR:
                    aName = _rsTypeNames.GetToken(TYPE_TEXT);
                    break;
                case DataType::DECIMAL:
                    aName = _rsTypeNames.GetToken(TYPE_DECIMAL);
                    break;
                case DataType::NUMERIC:
                    aName = _rsTypeNames.GetToken(TYPE_NUMERIC);
                    break;
                case DataType::BIGINT:
                    aName = _rsTypeNames.GetToken(TYPE_BIGINT);
                    break;
                case DataType::FLOAT:
                    aName = _rsTypeNames.GetToken(TYPE_FLOAT);
                    break;
                case DataType::DOUBLE:
                    aName = _rsTypeNames.GetToken(TYPE_DOUBLE);
                    break;
                case DataType::LONGVARCHAR:
                    aName = _rsTypeNames.GetToken(TYPE_MEMO);
                    break;
                case DataType::LONGVARBINARY:
                    aName = _rsTypeNames.GetToken(TYPE_IMAGE);
                    break;
                case DataType::DATE:
                    aName = _rsTypeNames.GetToken(TYPE_DATE);
                    break;
                case DataType::TIME:
                    aName = _rsTypeNames.GetToken(TYPE_TIME);
                    break;
                case DataType::TIMESTAMP:
                    aName = _rsTypeNames.GetToken(TYPE_DATETIME);
                    break;
                case DataType::BIT:
                    aName = _rsTypeNames.GetToken(TYPE_BOOL);
                    break;
                case DataType::TINYINT:
                    aName = _rsTypeNames.GetToken(TYPE_TINYINT);
                    break;
                case DataType::SMALLINT:
                    aName = _rsTypeNames.GetToken(TYPE_SMALLINT);
                    break;
                case DataType::INTEGER:
                    aName = _rsTypeNames.GetToken(TYPE_INTEGER);
                    break;
                case DataType::REAL:
                    aName = _rsTypeNames.GetToken(TYPE_REAL);
                    break;
                case DataType::BINARY:
                    aName = _rsTypeNames.GetToken(TYPE_BINARY);
                    break;
                case DataType::VARBINARY:
                    aName = _rsTypeNames.GetToken(TYPE_VARBINARY);
                    break;
                case DataType::SQLNULL:
                    aName = _rsTypeNames.GetToken(TYPE_SQLNULL);
                    break;
                case DataType::OBJECT:
                    aName = _rsTypeNames.GetToken(TYPE_OBJECT);
                    break;
                case DataType::DISTINCT:
                    aName = _rsTypeNames.GetToken(TYPE_DISTINCT);
                    break;
                case DataType::STRUCT:
                    aName = _rsTypeNames.GetToken(TYPE_STRUCT);
                    break;
                case DataType::ARRAY:
                    aName = _rsTypeNames.GetToken(TYPE_ARRAY);
                    break;
                case DataType::BLOB:
                    aName = _rsTypeNames.GetToken(TYPE_BLOB);
                    break;
                case DataType::CLOB:
                    aName = _rsTypeNames.GetToken(TYPE_CLOB);
                    break;
                case DataType::REF:
                    aName = _rsTypeNames.GetToken(TYPE_REF);
                    break;
                case DataType::OTHER:
                    aName = _rsTypeNames.GetToken(TYPE_OTHER);
                    break;
                default:
                    OSL_ENSURE(0,"Unknown type");
            }
            pInfo->aUIName = aName.GetBuffer();
            pInfo->aUIName += aB1;
            pInfo->aUIName += pInfo->aTypeName;
            pInfo->aUIName += aB2;
            // Now that we have the type info, save it in the multimap 
            _rTypeInfoMap.insert(OTypeInfoMap::value_type(pInfo->nType,pInfo));
        }
        // for a faster index access
        _rTypeInfoIters.reserve(_rTypeInfoMap.size());

        OTypeInfoMap::iterator aIter = _rTypeInfoMap.begin();
        for(;aIter != _rTypeInfoMap.end();++aIter)
            _rTypeInfoIters.push_back(aIter);

        // Close the result set/statement.

        ::comphelper::disposeComponent(xRs);
    }
}
// -----------------------------------------------------------------------------
void setColumnProperties(const Reference<XPropertySet>& _rxColumn,const OFieldDescription* _pFieldDesc)
{
    _rxColumn->setPropertyValue(PROPERTY_NAME,makeAny(_pFieldDesc->GetName()));
    _rxColumn->setPropertyValue(PROPERTY_TYPE,makeAny(_pFieldDesc->GetType()));
    _rxColumn->setPropertyValue(PROPERTY_TYPENAME,makeAny(_pFieldDesc->getTypeInfo()->aTypeName));
    _rxColumn->setPropertyValue(PROPERTY_PRECISION,makeAny(_pFieldDesc->GetPrecision()));
    _rxColumn->setPropertyValue(PROPERTY_SCALE,makeAny(_pFieldDesc->GetScale()));
    _rxColumn->setPropertyValue(PROPERTY_ISNULLABLE, makeAny(_pFieldDesc->GetIsNullable()));
    _rxColumn->setPropertyValue(PROPERTY_ISAUTOINCREMENT,::cppu::bool2any(_pFieldDesc->IsAutoIncrement()));
    //	_rxColumn->setPropertyValue(PROPERTY_ISCURRENCY,::cppu::bool2any(_pFieldDesc->IsCurrency()));
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_DEFAULTVALUE))
        _rxColumn->setPropertyValue(PROPERTY_DEFAULTVALUE,makeAny(_pFieldDesc->GetDefaultValue()));
}
// -----------------------------------------------------------------------------
::rtl::OUString createDefaultName(const Reference< XDatabaseMetaData>& _xMetaData,const Reference<XNameAccess>& _xTables,const ::rtl::OUString& _sName)
{
    OSL_ENSURE(_xMetaData.is(),"No MetaData!");
    ::rtl::OUString sDefaultName = _sName;
    try
    {
        ::rtl::OUString sCatalog,sSchema,sCompsedName;
        if(_xMetaData->supportsCatalogsInTableDefinitions())
        {
            try
            {
                Reference<XResultSet> xRes = _xMetaData->getCatalogs();
                Reference<XRow> xRow(xRes,UNO_QUERY);
                ::rtl::OUString sCatalog;
                while(xRes.is() && xRes->next())
                {
                    sCatalog = xRow->getString(1);
                    if(!xRow->wasNull())
                        break;
                }
            }
            catch(const SQLException&)
            {
            }
        }
        if(_xMetaData->supportsSchemasInTableDefinitions())
        {
            sSchema = _xMetaData->getUserName();
        }
        ::dbtools::composeTableName(_xMetaData,sCatalog,sSchema,_sName,sCompsedName,sal_False);
        sDefaultName = ::dbtools::createUniqueName(_xTables,sCompsedName);
    }
    catch(const SQLException&)
    {
    }
    return sDefaultName;
}
// -----------------------------------------------------------------------------
sal_Bool checkDataSourceAvailable(const ::rtl::OUString& _sDataSourceName,const Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xORB)
{
    sal_Bool bRet = sal_False;
    Reference< XNameAccess > xDataBaseContext(_xORB->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
    if(xDataBaseContext.is())
        bRet = xDataBaseContext->hasByName(_sDataSourceName);
    return bRet;
}
// -----------------------------------------------------------------------------
sal_Int32 mapTextAllign(const SvxCellHorJustify& _eAlignment)
{
    sal_Int32 nAlignment = com::sun::star::awt::TextAlign::LEFT;
    switch (_eAlignment)
    {
        case SVX_HOR_JUSTIFY_STANDARD:
        case SVX_HOR_JUSTIFY_LEFT:		nAlignment = ::com::sun::star::awt::TextAlign::LEFT;	break;
        case SVX_HOR_JUSTIFY_CENTER:	nAlignment = ::com::sun::star::awt::TextAlign::CENTER;	break;
        case SVX_HOR_JUSTIFY_RIGHT:		nAlignment = ::com::sun::star::awt::TextAlign::RIGHT;	break;
        default:
            OSL_ENSURE(0,"Invalid TextAlign!");
    }
    return nAlignment;
}
// -----------------------------------------------------------------------------
void setColumnUiProperties(	const Reference< XPropertySet>& _rxColumn,const OFieldDescription* _pFieldDesc)
{
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_FORMATKEY))
        _rxColumn->setPropertyValue(PROPERTY_FORMATKEY,makeAny(_pFieldDesc->GetFormatKey()));
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_ALIGN))
        _rxColumn->setPropertyValue(PROPERTY_ALIGN,makeAny(dbaui::mapTextAllign(_pFieldDesc->GetHorJustify())));
    if(_rxColumn->getPropertySetInfo()->hasPropertyByName(PROPERTY_HELPTEXT))
        _rxColumn->setPropertyValue(PROPERTY_HELPTEXT,makeAny(_pFieldDesc->GetDescription()));
}
// -----------------------------------------------------------------------------
float ConvertFontWeight( ::FontWeight eWeight )
{
    if( eWeight == WEIGHT_DONTKNOW )
        return ::com::sun::star::awt::FontWeight::DONTKNOW;
    else if( eWeight == WEIGHT_THIN )
        return ::com::sun::star::awt::FontWeight::THIN;
    else if( eWeight == WEIGHT_ULTRALIGHT )
        return ::com::sun::star::awt::FontWeight::ULTRALIGHT;
    else if( eWeight == WEIGHT_LIGHT )
        return ::com::sun::star::awt::FontWeight::LIGHT;
    else if( eWeight == WEIGHT_SEMILIGHT )
        return ::com::sun::star::awt::FontWeight::SEMILIGHT;
    else if( ( eWeight == WEIGHT_NORMAL ) || ( eWeight == WEIGHT_MEDIUM ) )
        return ::com::sun::star::awt::FontWeight::NORMAL;
    else if( eWeight == WEIGHT_SEMIBOLD )
        return ::com::sun::star::awt::FontWeight::SEMIBOLD;
    else if( eWeight == WEIGHT_BOLD )
        return ::com::sun::star::awt::FontWeight::BOLD;
    else if( eWeight == WEIGHT_ULTRABOLD )
        return ::com::sun::star::awt::FontWeight::ULTRABOLD;
    else if( eWeight == WEIGHT_BLACK )
        return ::com::sun::star::awt::FontWeight::BLACK;

    OSL_ENSURE(0, "Unknown FontWeigth" );
    return ::com::sun::star::awt::FontWeight::DONTKNOW;
}
// -----------------------------------------------------------------------------
float ConvertFontWidth( ::FontWidth eWidth )
{
    if( eWidth == WIDTH_DONTKNOW )
        return ::com::sun::star::awt::FontWidth::DONTKNOW;
    else if( eWidth == WIDTH_ULTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::ULTRACONDENSED;
    else if( eWidth == WIDTH_EXTRA_CONDENSED )
        return ::com::sun::star::awt::FontWidth::EXTRACONDENSED;
    else if( eWidth == WIDTH_CONDENSED )
        return ::com::sun::star::awt::FontWidth::CONDENSED;
    else if( eWidth == WIDTH_SEMI_CONDENSED )
        return ::com::sun::star::awt::FontWidth::SEMICONDENSED;
    else if( eWidth == WIDTH_NORMAL )
        return ::com::sun::star::awt::FontWidth::NORMAL;
    else if( eWidth == WIDTH_SEMI_EXPANDED )
        return ::com::sun::star::awt::FontWidth::SEMIEXPANDED;
    else if( eWidth == WIDTH_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXPANDED;
    else if( eWidth == WIDTH_EXTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::EXTRAEXPANDED;
    else if( eWidth == WIDTH_ULTRA_EXPANDED )
        return ::com::sun::star::awt::FontWidth::ULTRAEXPANDED;
    
    OSL_ENSURE(0, "Unknown FontWidth" );
    return ::com::sun::star::awt::FontWidth::DONTKNOW;
}
// -----------------------------------------------------------------------------
::com::sun::star::awt::FontDescriptor CreateFontDescriptor( const Font& rFont )
{
    ::com::sun::star::awt::FontDescriptor aFD;
    aFD.Name			= rFont.GetName();
    aFD.StyleName		= rFont.GetStyleName();
    aFD.Height			= (sal_Int16)rFont.GetSize().Height();
    aFD.Width			= (sal_Int16)rFont.GetSize().Width();
    aFD.Family			= rFont.GetFamily();
    aFD.CharSet			= rFont.GetCharSet();
    aFD.Pitch			= rFont.GetPitch();
    aFD.CharacterWidth	= ConvertFontWidth( rFont.GetWidthType() );
    aFD.Weight			= ConvertFontWeight( rFont.GetWeight() );
    aFD.Slant			= (::com::sun::star::awt::FontSlant)rFont.GetItalic();
    aFD.Underline		= rFont.GetUnderline();
    aFD.Strikeout		= rFont.GetStrikeout();
    aFD.Orientation		= rFont.GetOrientation();
    aFD.Kerning			= rFont.IsKerning();
    aFD.WordLineMode	= rFont.IsWordLineMode();
    aFD.Type			= 0;   // ??? => Nur an Metric...
    return aFD;
}
// -----------------------------------------------------------------------------
void callColumnFormatDialog(const Reference<XPropertySet>& xAffectedCol, 
                            const Reference<XPropertySet>& xField,
                            SvNumberFormatter* _pFormatter,
                            Window* _pParent)
{
    if (xAffectedCol.is() && xField.is())
    {
        Reference< XPropertySetInfo >  xInfo = xAffectedCol->getPropertySetInfo();
        sal_Bool bHasFormat = xInfo->hasPropertyByName(PROPERTY_FORMATKEY);
        sal_Int32 nDataType = ::comphelper::getINT32(xField->getPropertyValue(PROPERTY_TYPE));

        SvxCellHorJustify eJustify(SVX_HOR_JUSTIFY_STANDARD);
        Any aAlignment = xAffectedCol->getPropertyValue(PROPERTY_ALIGN);
        if (aAlignment.hasValue())
            switch (::comphelper::getINT16(aAlignment))
            {
                case ::com::sun::star::awt::TextAlign::LEFT		: eJustify = SVX_HOR_JUSTIFY_LEFT; break;
                case ::com::sun::star::awt::TextAlign::CENTER	: eJustify = SVX_HOR_JUSTIFY_CENTER; break;
                case ::com::sun::star::awt::TextAlign::RIGHT	: eJustify = SVX_HOR_JUSTIFY_RIGHT; break;
                default:
                    OSL_ENSURE(0,"Invalid TextAlign!");
            }
        sal_uInt16 nFlags;
        sal_Int32  nFormatKey = ::comphelper::getINT32(xAffectedCol->getPropertyValue(PROPERTY_FORMATKEY));
        if(callColumnFormatDialog(_pParent,_pFormatter,nDataType,nFormatKey,eJustify,nFlags,bHasFormat))
        {
            try
            {
                xAffectedCol->setPropertyValue(PROPERTY_ALIGN, makeAny((sal_Int16)dbaui::mapTextAllign(eJustify)));
                if (nFlags & TP_ATTR_NUMBER)
                    xAffectedCol->setPropertyValue(PROPERTY_FORMATKEY, makeAny(nFormatKey));
            }
            catch(const Exception&)
            {
                // could not set the column properties here
            }

        }
    }
}
// -----------------------------------------------------------------------------
sal_Bool callColumnFormatDialog(Window* _pParent,
                                SvNumberFormatter* _pFormatter,
                                sal_Int32 _nDataType,
                                sal_Int32& _nFormatKey,
                                SvxCellHorJustify& _eJustify,
                                sal_uInt16&	_nFlags,
                                sal_Bool  _bHasFormat)
{
    sal_Bool bRet = sal_False;
    // the allowed format changes depend of the type of the field ...
    _nFlags = TP_ATTR_ALIGN;
    
    if (_bHasFormat)
        _nFlags |= TP_ATTR_NUMBER;

    // ------------
    // UNO->ItemSet
    static SfxItemInfo aItemInfos[] =
    {
        { 0, 0 },
        { SID_ATTR_NUMBERFORMAT_VALUE,		SFX_ITEM_POOLABLE },
        { SID_ATTR_ALIGN_HOR_JUSTIFY,		SFX_ITEM_POOLABLE },
        { SID_ATTR_NUMBERFORMAT_ONE_AREA,	SFX_ITEM_POOLABLE },
        { SID_ATTR_NUMBERFORMAT_INFO,		SFX_ITEM_POOLABLE }
    };
    static sal_uInt16 aAttrMap[] =
    {
        SBA_DEF_RANGEFORMAT, SBA_ATTR_ALIGN_HOR_JUSTIFY,
        SID_ATTR_NUMBERFORMAT_ONE_AREA, SID_ATTR_NUMBERFORMAT_ONE_AREA,
        SID_ATTR_NUMBERFORMAT_INFO, SID_ATTR_NUMBERFORMAT_INFO,
        0
    };

    SfxPoolItem* pDefaults[] =
    {
        new SfxRangeItem(SBA_DEF_RANGEFORMAT, SBA_DEF_FMTVALUE, SBA_ATTR_ALIGN_HOR_JUSTIFY),
        new SfxUInt32Item(SBA_DEF_FMTVALUE),
        new SvxHorJustifyItem(SVX_HOR_JUSTIFY_STANDARD, SBA_ATTR_ALIGN_HOR_JUSTIFY),
        new SfxBoolItem(SID_ATTR_NUMBERFORMAT_ONE_AREA, sal_False),
        new SvxNumberInfoItem(SID_ATTR_NUMBERFORMAT_INFO)
    };

    SfxItemPool* pPool = new SfxItemPool(String::CreateFromAscii("GridBrowserProperties"), SBA_DEF_RANGEFORMAT, SBA_ATTR_ALIGN_HOR_JUSTIFY, aItemInfos, pDefaults);
    pPool->SetDefaultMetric( SFX_MAPUNIT_TWIP );	// ripped, don't understand why
    pPool->FreezeIdRanges();						// the same

    SfxItemSet* pFormatDescriptor = new SfxItemSet(*pPool, aAttrMap);
    // fill it
    pFormatDescriptor->Put(SvxHorJustifyItem(_eJustify, SBA_ATTR_ALIGN_HOR_JUSTIFY));
    sal_Bool bText = sal_False;
    if (_bHasFormat)
    {
        // if the col is bound to a text field we have to disallow all non-text formats
        if ((DataType::CHAR == _nDataType) || (DataType::VARCHAR == _nDataType) || (DataType::LONGVARCHAR == _nDataType))
        {
            sal_Bool bText = sal_True;
            pFormatDescriptor->Put(SfxBoolItem(SID_ATTR_NUMBERFORMAT_ONE_AREA, sal_True));
            if (!_pFormatter->IsTextFormat(_nFormatKey))
                // text fields can only have text formats
                _nFormatKey = _pFormatter->GetStandardFormat(NUMBERFORMAT_TEXT,_pParent->GetSettings().GetLanguage());
        }

        pFormatDescriptor->Put(SfxUInt32Item(SBA_DEF_FMTVALUE, _nFormatKey));
    }

    if (!bText)
    {
        double dPreviewVal = 1234.56789;
        SvxNumberInfoItem aFormatter(_pFormatter, dPreviewVal, SID_ATTR_NUMBERFORMAT_INFO);
        pFormatDescriptor->Put(aFormatter);
    }

    {	// want the dialog to be destroyed before our set
        SbaSbAttrDlg aDlg(_pParent, pFormatDescriptor, _pFormatter, _nFlags);
        if (RET_OK == aDlg.Execute())
        {
            // ------------
            // ItemSet->UNO
            // UNO-properties
            const SfxItemSet* pSet = aDlg.GetExampleSet();
            // (of course we could put the modified items directly into the column, but then the UNO-model
            // won't reflect these changes, and why do we have a model, then ?)

            // horizontal justify
            SFX_ITEMSET_GET(*pSet, pHorJustify, SvxHorJustifyItem, SBA_ATTR_ALIGN_HOR_JUSTIFY, sal_True);

            _eJustify = (SvxCellHorJustify)pHorJustify->GetValue();

            // format key
            if (_nFlags & TP_ATTR_NUMBER)
            {
                SFX_ITEMSET_GET(*pSet, pFormat, SfxUInt32Item, SBA_DEF_FMTVALUE, sal_True);
                _nFormatKey = (sal_Int32)pFormat->GetValue();
            }
            bRet = sal_True;
        }
            // deleted formats
        const SfxItemSet* pResult = aDlg.GetOutputItemSet();
        if (pResult)
        {
            const SfxPoolItem* pItem = pResult->GetItem( SID_ATTR_NUMBERFORMAT_INFO );
            const SvxNumberInfoItem* pInfoItem = static_cast<const SvxNumberInfoItem*>(pItem);
            if (pInfoItem && pInfoItem->GetDelCount())
            {
                const sal_uInt32* pDeletedKeys = pInfoItem->GetDelArray();

                for (sal_uInt16 i=0; i< pInfoItem->GetDelCount(); ++i, ++pDeletedKeys)
                    _pFormatter->DeleteEntry(*pDeletedKeys);
            }
        }
    }

    delete pFormatDescriptor;
    delete pPool;
    for (sal_uInt16 i=0; i<sizeof(pDefaults)/sizeof(pDefaults[0]); ++i)
        delete pDefaults[i];

    return bRet;
}
// .........................................................................
}
// .........................................................................
