 /*************************************************************************
 *
 *  $RCSfile: cfgimport.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2005-03-11 11:00:24 $
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

#include "cfgimport.hxx"

#ifndef CFG_REGHELPER_HXX
#include "cfg_reghelper.hxx"
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_XNAMINGSERVICE_HPP_
#include <com/sun/star/uno/XNamingService.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERYDEFINITIONSSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XDATADESCRIPTORFACTORY_HPP_
#include <com/sun/star/sdbcx/XDataDescriptorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSET_HPP_
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XAPPEND_HPP_
#include <com/sun/star/sdbcx/XAppend.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XSTORABLE_HPP_
#include <com/sun/star/frame/XStorable.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP_
#include <com/sun/star/sdb/XOfficeDatabaseDocument.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XDOCUMENTDATASOURCE_HPP_
#include <com/sun/star/sdb/XDocumentDataSource.hpp>
#endif
#ifndef _URLOBJ_HXX //autogen wg. INetURLObject
#include <tools/urlobj.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_PATHOPTIONS_HXX
#include <svtools/pathoptions.hxx>
#endif
#ifndef _COM_SUN_STAR_FRAME_XCOMPONENTLOADER_HPP_
#include <com/sun/star/frame/XComponentLoader.hpp>
#endif
#ifndef DBACCESS_SHARED_CFGSTRINGS_HRC
#include "cfgstrings.hrc"
#endif
#ifndef _UNOTOOLS_UCBHELPER_HXX
#include <unotools/ucbhelper.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEACCESS_HPP_
#include <com/sun/star/container/XNameAccess.hpp>
#endif
#ifndef _SFX_DOCFILT_HACK_HXX
#include <sfx2/docfilt.hxx>
#endif
#ifndef _COMPHELPER_STREAMSECTION_HXX_
#include <comphelper/streamsection.hxx>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASINK_HPP_
#include <com/sun/star/io/XActiveDataSink.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XOBJECTINPUTSTREAM_HPP_
#include <com/sun/star/io/XObjectInputStream.hpp>
#endif
#ifndef _COMPHELPER_BASIC_IO_HXX_
#include <comphelper/basicio.hxx>
#endif
#ifndef _COMPHELPER_SEQSTREAM_HXX
#include <comphelper/seqstream.hxx>
#endif
#ifndef _COM_SUN_STAR_SDB_XREPORTDOCUMENTSSUPPLIER_HPP_
#include <com/sun/star/sdb/XReportDocumentsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XFORMDOCUMENTSSUPPLIER_HPP_
#include <com/sun/star/sdb/XFormDocumentsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_CONFIGURATION_BACKEND_XLAYER_HPP_
#include <com/sun/star/configuration/backend/XLayer.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XLOADABLE_HPP_
#include <com/sun/star/frame/XLoadable.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XTYPEDETECTION_HPP_
#include <com/sun/star/document/XTypeDetection.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEVENTSSUPPLIER_HPP_
#include <com/sun/star/document/XEventsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XCLOSEABLE_HPP_
#include <com/sun/star/util/XCloseable.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMEREPLACE_HPP_
#include <com/sun/star/container/XNameReplace.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_FORMCOMPONENTTYPE_HPP_
#include <com/sun/star/form/FormComponentType.hpp>
#endif
#ifndef _COM_SUN_STAR_DRAWING_XDRAWPAGESUPPLIER_HPP_
#include <com/sun/star/drawing/XDrawPageSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMSSUPPLIER_HPP_
#include <com/sun/star/form/XFormsSupplier.hpp>
#endif


extern "C" void SAL_CALL createRegistryInfo_OCfgImport( )
{
    static ::dbacfg::OMultiInstanceAutoRegistration< ::dbacfg::OCfgImport > aAutoRegistration;
}

#define DATASOURCES				1
#define	DATASOURCE				2
#define DATASOURCESETTINGS		3
#define TABLES					4
#define QUERIES					5
#define BOOKMARKS				6
#define DATASOURCESETTING		7
#define BOOKMARK				8
#define QUERY					9
#define TABLE					10
#define DATASETTINGS			11
#define COLUMNS					12
#define COLUMN					13
#define NO_PROP					14
#define LOGINTIMEOUT			15

//--------------------------------------------------------------------------
using namespace dbacfg;
// {
    using namespace ::com::sun::star::util;
    using namespace ::com::sun::star::sdb;
    using namespace ::com::sun::star::sdbcx;
    using namespace ::com::sun::star::frame;
    using namespace ::com::sun::star::document;
    using namespace ::com::sun::star::io;
    using namespace ::com::sun::star::form;
    using namespace ::com::sun::star::drawing;
    using namespace ::com::sun::star::container;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::task;
    using namespace ::com::sun::star::configuration::backend;
    using namespace ::utl;
    using namespace ::comphelper;

    void LoadTableWindows(const Reference< XObjectInputStream>& _rxIn,Sequence<PropertyValue>& _rViewProps);
    void LoadTableWindowData(const Reference<XObjectInputStream>& _rxIn,PropertyValue* _pValue);
    void LoadTableFields(const Reference< XObjectInputStream>& _rxIn,Sequence<PropertyValue>& _rViewProps);
    void LoadTableFieldDesc(const Reference< XObjectInputStream>& _rxIn,PropertyValue& _rProperty);
    sal_Bool isDocumentReport(const Reference< XMultiServiceFactory >& _xORB,const ::rtl::OUString& _sDocumentLocation);
// -------------
// - OCfgImport -
// -------------

OCfgImport::OCfgImport( const Reference< XMultiServiceFactory >& _rxMSF )
    :m_xORB( _rxMSF )
    ,m_bPropertyMayBeVoid(sal_True)
{
}

// -----------------------------------------------------------------------------

OCfgImport::~OCfgImport() throw()
{
}
// -----------------------------------------------------------------------------
IMPLEMENT_SERVICE_INFO1_STATIC( OCfgImport, "com.sun.star.comp.sdb.DataSourceMigration", "com.sun.star.sdb.DataSourceMigration")
// -----------------------------------------------------------------------------
// XInitialization
void SAL_CALL OCfgImport::initialize( const Sequence< Any >& _aArguments ) throw(Exception, RuntimeException)
{
    const Any* pIter = _aArguments.getConstArray();
    const Any* pEnd = pIter + _aArguments.getLength();
    Sequence<NamedValue> aOldConfigValues;
    NamedValue aValue;
    for(;pIter != pEnd;++pIter)
    {
        *pIter >>= aValue;
        if ( aValue.Name.equalsAscii("OldConfiguration") && (aValue.Value >>= aOldConfigValues) )
        {
            const NamedValue* pIter = aOldConfigValues.getConstArray();
            const NamedValue* pEnd	  = pIter + aOldConfigValues.getLength();
            for(;pIter != pEnd;++pIter)
            {
                if ( pIter->Name.equalsAscii("org.openoffice.Office.DataAccess") )
                {
                    pIter->Value >>= m_xLayer;
                    break;
                }
            }
            break;
        }
    }
}
// -----------------------------------------------------------------------------

void LoadTableWindows(const Reference< XObjectInputStream>& _rxIn,Sequence<PropertyValue>& _rViewProps)
{
    try
    {
        OStreamSection aSection(_rxIn.get());

        sal_Int32 nCount = 0;
        _rxIn >> nCount;
        if ( nCount > 0 )
        {
            PropertyValue *pViewIter = _rViewProps.getArray();
            PropertyValue *pEnd = pViewIter + _rViewProps.getLength();
            const static ::rtl::OUString s_sTables(RTL_CONSTASCII_USTRINGPARAM("Tables"));
            for (; pViewIter != pEnd && pViewIter->Name != s_sTables; ++pViewIter)
                ;

            if ( pViewIter == pEnd )
            {
                sal_Int32 nLen = _rViewProps.getLength();
                _rViewProps.realloc( nLen + 1 );
                pViewIter = _rViewProps.getArray() + nLen;
                pViewIter->Name = s_sTables;
            }

            Sequence<PropertyValue> aTables(nCount);
            PropertyValue *pIter = aTables.getArray();


            for(sal_Int32 i=0;i<nCount;++i,++pIter)
            {
                pIter->Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Table")) + ::rtl::OUString::valueOf(i+1);
                LoadTableWindowData(_rxIn,pIter);
            }
        }
    }
    catch(Exception&)
    {
    }
}
// -----------------------------------------------------------------------------
void LoadTableWindowData(const Reference<XObjectInputStream>& _rxIn,PropertyValue* _pValue)
{
    ::rtl::OUString sComposedName,aTableName,aWinName;
    sal_Int32 nX,nY,nWidth,nHeight;
    sal_Bool bShowAll;

    OStreamSection aSection(_rxIn.get());
    _rxIn >> sComposedName;
    _rxIn >> aTableName;
    _rxIn >> aWinName;
    _rxIn >> nX;
    _rxIn >> nY;
    _rxIn >> nWidth;
    _rxIn >> nHeight;
    _rxIn >> bShowAll;

    Sequence<PropertyValue> aWindow(8);
    sal_Int32 nPos = 0;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ComposedName"));
    aWindow[nPos++].Value <<= sComposedName;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TableName"));
    aWindow[nPos++].Value <<= aTableName;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WindowName"));
    aWindow[nPos++].Value <<= aWinName;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WindowTop"));
    aWindow[nPos++].Value <<= nY;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WindowLeft"));
    aWindow[nPos++].Value <<= nX;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WindowWidth"));
    aWindow[nPos++].Value <<= nWidth;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("WindowHeight"));
    aWindow[nPos++].Value <<= nHeight;
    aWindow[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ShowAll"));
    aWindow[nPos++].Value <<= bShowAll;

    _pValue->Value <<= aWindow;
}
// -----------------------------------------------------------------------------
void LoadTableFields(const Reference< XObjectInputStream>& _rxIn,Sequence<PropertyValue>& _rViewProps)
{
    LoadTableWindows(_rxIn,_rViewProps);
    OStreamSection aSection(_rxIn.get());
    PropertyValue *pIter = NULL;
    try
    {
        sal_Int32 nSplitPos,nVisibleRows;
        // some data
        _rxIn >> nSplitPos;
        _rxIn >> nVisibleRows;

        sal_Int32 nCount = 0;
        _rxIn >> nCount;

        sal_Int32 nLen = _rViewProps.getLength();
        _rViewProps.realloc( nLen + 2 + (nCount != 0 ? 1 : 0) );
        pIter = _rViewProps.getArray() + nLen;

        if ( nCount != 0 )
        {
            pIter->Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Fields"));

            Sequence<PropertyValue> aFields(nCount);
            PropertyValue *pFieldsIter = aFields.getArray();
            // the fielddata
            for(sal_Int32 j=0;j<nCount;++j)
            {
                if ( aSection.available() )
                {
                    pFieldsIter->Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Field")) + ::rtl::OUString::valueOf(j+1);
                    LoadTableFieldDesc(_rxIn,*pFieldsIter++);
                }
            }
            pIter->Value <<= aFields;
            ++pIter;
        }

        pIter->Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("SplitterPosition"));
        pIter->Value <<= nSplitPos;
        ++pIter;
        pIter->Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("VisibleRows"));
        pIter->Value <<= nVisibleRows;
    }
    catch(Exception&)
    {
    }
}
// -----------------------------------------------------------------------------
void LoadTableFieldDesc(const Reference< XObjectInputStream>& _rxIn,PropertyValue& _rProperty)
{
    ::rtl::OUString		aTableName;
    ::rtl::OUString		aAliasName;		// table range
    ::rtl::OUString		aFieldName;		// column
    ::rtl::OUString		aFieldAlias;	// column alias
    ::rtl::OUString		aDatabaseName;	// qualifier or catalog
    ::rtl::OUString		aFunctionName;	// enth"alt den Funktionsnamen, nur wenn eFunctionType != FKT_NONE gesetzt

    sal_Int32			eDataType;
    sal_Int32			eFunctionType;
    sal_Int32			eFieldType;
    sal_Int32			eOrderDir;
    sal_Int32			nColWidth;
    sal_Bool			bGroupBy;
    sal_Bool			bVisible;

    OStreamSection aSection(_rxIn.get());
    _rxIn >> aTableName;
    _rxIn >> aAliasName;
    _rxIn >> aFieldName;
    _rxIn >> aFieldAlias;
    _rxIn >> aDatabaseName;
    _rxIn >> aFunctionName;
    _rxIn >> eDataType;
    _rxIn >> eFunctionType;
    _rxIn >> eFieldType;
    _rxIn >> eOrderDir;
    _rxIn >> nColWidth;
    _rxIn >> bGroupBy;
    _rxIn >> bVisible;

    Sequence<PropertyValue> aFieldDesc(13);
    sal_Int32 nPos = 0;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AliasName"));
    aFieldDesc[nPos++].Value <<= aAliasName;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("TableName"));
    aFieldDesc[nPos++].Value <<= aTableName;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FieldName"));
    aFieldDesc[nPos++].Value <<= aFieldName;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FieldAlias"));
    aFieldDesc[nPos++].Value <<= aFieldAlias;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DatabaseName"));
    aFieldDesc[nPos++].Value <<= aDatabaseName;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FunctionName"));
    aFieldDesc[nPos++].Value <<= aFunctionName;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DataType"));
    aFieldDesc[nPos++].Value <<= eDataType;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FunctionType"));
    aFieldDesc[nPos++].Value <<= (sal_Int32)eFunctionType;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FieldType"));
    aFieldDesc[nPos++].Value <<= (sal_Int32)eFieldType;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OrderDir"));
    aFieldDesc[nPos++].Value <<= (sal_Int32)eOrderDir;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ColWidth"));
    aFieldDesc[nPos++].Value <<= nColWidth;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("GroupBy"));
    aFieldDesc[nPos++].Value <<= bGroupBy;
    aFieldDesc[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Visible"));
    aFieldDesc[nPos++].Value <<= bVisible;

    _rProperty.Value <<= aFieldDesc;
}
// -----------------------------------------------------------------------------
void closeDocument(const Reference< XModel >& _xDocument)
{
    Reference< XCloseable > xCloseable( _xDocument, UNO_QUERY );
    if ( xCloseable.is() )
    {
        try
        {
            xCloseable->close( sal_True );
        }
        catch( Exception& )
        {
        }
    }
}
// -----------------------------------------------------------------------------
sal_Bool isDocumentReport(const Reference< XMultiServiceFactory >& _xORB,const ::rtl::OUString& _sDocumentLocation)
{
    sal_Bool bReport = sal_False;
    try
    {
        Reference< XModel > xDocument(_xORB->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.text.TextDocument"))),UNO_QUERY);
        if ( xDocument.is() )
        {
            Reference< XLoadable > xLoadable( xDocument, UNO_QUERY );
            if ( xLoadable.is() )
            {
                Sequence< PropertyValue > aMedDescr(4);
                sal_Int32 nPos = 0;
                aMedDescr[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("AsTemplate"));
                aMedDescr[nPos++].Value <<= sal_False;
                aMedDescr[nPos].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Hidden"));
                aMedDescr[nPos++].Value <<= sal_False;
                aMedDescr[nPos].Name = PROPERTY_URL;
                aMedDescr[nPos++].Value <<= _sDocumentLocation;
                aMedDescr[nPos].Name = ::rtl::OUString::createFromAscii( "ReadOnly" );
                aMedDescr[nPos++].Value <<= sal_True;
                Reference< XTypeDetection > xTypeDetection(_xORB->createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.TypeDetection")) ),UNO_QUERY );

                if ( !xTypeDetection.is() )
                    throw RuntimeException(); // TODO

                // get TypeName
                ::rtl::OUString aTypeName = xTypeDetection->queryTypeByDescriptor( aMedDescr, sal_True );
                const PropertyValue* pIter = aMedDescr.getConstArray();
                const PropertyValue* pEnd	  = pIter + aMedDescr.getLength();
                for( ; pIter != pEnd && !pIter->Name.equalsAscii( "FilterName" ); ++pIter)
                    ;
                if ( aTypeName.getLength() && pIter == pEnd )
                {
                    Reference<XNameAccess> xNameAccess( xTypeDetection, UNO_QUERY );
                    if ( xNameAccess.is() && xNameAccess->hasByName( aTypeName ) )
                    {
                        Sequence<PropertyValue> aTypes;
                        xNameAccess->getByName(aTypeName) >>= aTypes;
                        const PropertyValue* pIter = aTypes.getConstArray();
                        const PropertyValue* pEnd	  = pIter + aTypes.getLength();
                        for( ; pIter != pEnd && !pIter->Name.equalsAscii( "PreferredFilter" ) ; ++pIter)
                            ;
                        if ( pIter != pEnd )
                        {
                            sal_Int32 nLen = aMedDescr.getLength();
                            aMedDescr.realloc(nLen+1);
                            aMedDescr[nLen].Value = pIter->Value;
                            aMedDescr[nLen].Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FilterName"));
                        }
                    }
                }
                try
                {
                    xLoadable->load(aMedDescr);

                    Reference< XEventsSupplier> xEventsSup(xDocument,UNO_QUERY);
                    Reference< XNameReplace> xEvents = xEventsSup.is() ? xEventsSup->getEvents() : Reference< XNameReplace>();
                    static const ::rtl::OUString s_sOnNew = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OnNew"));
                    if ( xEvents.is() && xEvents->hasByName(s_sOnNew) )
                    {
                        Sequence<PropertyValue> aEventDesc;
                        if ( (xEvents->getByName(s_sOnNew) >>= aEventDesc ) && aEventDesc.getLength() )
                        {
                            ::rtl::OUString sScript;
                            const PropertyValue* pIter = aEventDesc.getConstArray();
                            const PropertyValue* pEnd  = pIter + aEventDesc.getLength();
                            for( ; pIter != pEnd && !pIter->Name.equalsAscii( "Script" ) ; ++pIter)
                                ;
                            if ( pIter != pEnd && (pIter->Value >>= sScript) )
                                bReport = sScript.equalsAscii("service:com.sun.star.wizards.report.CallReportWizard?fill");
                        }
                    }
                    if ( !bReport )
                    {
                        sal_Bool bForm = sal_False;
                        Reference< XDrawPageSupplier> xDrawPageSup(xDocument,UNO_QUERY);
                        Reference< XFormsSupplier> xFormsSup(xDrawPageSup.is() ? xDrawPageSup->getDrawPage() : Reference< XDrawPage>(),UNO_QUERY);
                        Reference< XNameContainer> xForms(xFormsSup.is() ? xFormsSup->getForms() : Reference< XNameContainer>(),UNO_QUERY);
                        Sequence< ::rtl::OUString> aSeq = xForms.is() ? xForms->getElementNames() : Sequence< ::rtl::OUString>();
                        const ::rtl::OUString* pIter = aSeq.getConstArray();
                        const ::rtl::OUString* pEnd	  = pIter + aSeq.getLength();
                        for(;pIter != pEnd && !bForm;++pIter)
                        {
                            Reference< XNameContainer> xControls(xForms->getByName(*pIter),UNO_QUERY);
                            Sequence< ::rtl::OUString> aControlSeq = xControls.is() ? xControls->getElementNames() : Sequence< ::rtl::OUString>();
                            const ::rtl::OUString* pControlIter = aControlSeq.getConstArray();
                            const ::rtl::OUString* pControlEnd	= pControlIter + aControlSeq.getLength();
                            for(;pControlIter != pControlEnd && !bForm;++pControlIter)
                            {
                                Reference<XPropertySet> xProp(xControls->getByName(*pControlIter),UNO_QUERY);
                                sal_Int16 nClassId = 0;
                                const static ::rtl::OUString s_sClassId = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ClassId"));
                                if ( xProp.is()
                                    && xProp->getPropertySetInfo().is()
                                    && xProp->getPropertySetInfo()->hasPropertyByName(s_sClassId)
                                    && (xProp->getPropertyValue(s_sClassId) >>= nClassId) )
                                {
                                    bForm = nClassId != FormComponentType::HIDDENCONTROL;
                                }
                            }
                        }
                        bReport = !bForm;
                    }
                }
                catch( Exception& )
                {
                    closeDocument(xDocument);
                }
            }
            closeDocument(xDocument);
        }
    }
    catch(Exception)
    {
        OSL_ENSURE(0,"isDocumentReport: catched exception!");
    }
    return bReport;
}
// -----------------------------------------------------------------------------
void OCfgImport::createDataSource(const ::rtl::OUString& _sName)
{
    SvtPathOptions aPathOptions;
    const String& rsWorkPath = aPathOptions.GetWorkPath();

    ::rtl::OUString sExtension;
    static const String s_sDatabaseType = String::CreateFromAscii("StarOffice XML (Base)");
    const SfxFilter* pFilter = SfxFilter::GetFilterByName( s_sDatabaseType);
    OSL_ENSURE(pFilter,"Filter: StarOffice XML (Base) could not be found!");
    if ( pFilter )
    {
        String aRet = pFilter->GetDefaultExtension();
        while( aRet.SearchAndReplaceAscii( "*.", String() ) != STRING_NOTFOUND );
        sExtension = aRet;
    }
    // then look for which of them settings are stored in the configuration
    ::rtl::OUString sFileName;
    try
    {
        m_xModel.set(m_xORB->createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.OfficeDatabaseDocument"))),UNO_QUERY);

        if ( !m_xModel.is() )
            return;

        Reference<XOfficeDatabaseDocument> xOfficeDoc(m_xModel,UNO_QUERY);
        if ( xOfficeDoc.is() )
            m_xCurrentDS.set(xOfficeDoc->getDataSource(),UNO_QUERY);
        

        INetURLObject aURL(rsWorkPath,INetURLObject::WAS_ENCODED);
        aURL.insertName(_sName,false,INetURLObject::LAST_SEGMENT,true,INetURLObject::ENCODE_ALL);
        aURL.setExtension(sExtension);

        sFileName = aURL.GetMainURL(INetURLObject::NO_DECODE);

        sal_Int32 i = 0;
        // create unique name
        while ( UCBContentHelper::IsDocument(sFileName) )
        {
            sFileName = _sName + ::rtl::OUString::valueOf(++i);
            aURL.setName(sFileName,INetURLObject::LAST_SEGMENT,true,INetURLObject::ENCODE_ALL);
            aURL.setExtension(sExtension);
            sFileName = aURL.GetMainURL(INetURLObject::NO_DECODE);
        }
        m_xModel->attachResource(sFileName,Sequence<PropertyValue>());
    }
    catch(Exception&)
    {
        OSL_ENSURE(0,"Exception: convert");
        UCBContentHelper::Kill(sFileName);
    }
}
// -----------------------------------------------------------------------------
void OCfgImport::createObject(sal_Bool _bQuery ,const ::rtl::OUString& _sName)
{
    if ( !m_xCurrentObject.is() )
    {
        Sequence< Any > aArguments(1);
        PropertyValue aValue;
        // set as folder
        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Name"));
        aValue.Value <<= _sName;
        aArguments[0] <<= aValue;
        m_xCurrentObject.set(m_xORB->createInstanceWithArguments(_bQuery ? SERVICE_SDB_COMMAND_DEFINITION : SERVICE_SDB_TABLEDEFINITION ,aArguments ),UNO_QUERY);
    }
}
// -----------------------------------------------------------------------------
void OCfgImport::setProperties()
{
    if ( m_aValues.getLength() )
    {
        OSL_ENSURE(m_aProperties.getLength() == m_aValues.getLength(),"Count is not equal!");
        try
        {
            Reference< XMultiPropertySet >	xFormMultiSet;
            if ( m_xCurrentColumn.is() )
                xFormMultiSet.set(m_xCurrentColumn,UNO_QUERY);
            else if ( m_xCurrentObject.is() )
                xFormMultiSet.set(m_xCurrentObject,UNO_QUERY);
            else if ( m_xCurrentDS.is() )
                xFormMultiSet.set(m_xCurrentDS,UNO_QUERY);

            if ( xFormMultiSet.is() )
                xFormMultiSet->setPropertyValues(m_aProperties, m_aValues);
        }
        catch(const Exception& e)
        {
            throw WrappedTargetException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Property could not be set.")),*this,makeAny(e));
        }
        m_aValues = Sequence< Any>();
        m_aProperties = Sequence< ::rtl::OUString>();
    }
}
// -----------------------------------------------------------------------------
Any SAL_CALL OCfgImport::execute( const Sequence< NamedValue >& Arguments ) throw (IllegalArgumentException, Exception, RuntimeException)
{
    m_xLayer->readData(this);
    return Any();
}
// -----------------------------------------------------------------------------
// XLayerHandler
void SAL_CALL OCfgImport::startLayer()
    throw(WrappedTargetException)
{
}
// -----------------------------------------------------------------------------

void SAL_CALL OCfgImport::endLayer()
    throw(
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL OCfgImport::overrideNode(
        const ::rtl::OUString& aName,
        sal_Int16 aAttributes,
        sal_Bool bClear)
    throw(
        MalformedDataException,
        WrappedTargetException )
{
    addOrReplaceNode(aName,aAttributes);
}
// -----------------------------------------------------------------------------

void SAL_CALL OCfgImport::addOrReplaceNode(
        const ::rtl::OUString& aName,
        sal_Int16 aAttributes)
    throw(
        MalformedDataException,
        WrappedTargetException )
{
    if ( !m_aStack.empty() )
    {
        switch(m_aStack.top().second)
        {
            case DATASOURCES:
                m_sCurrentDataSourceName = aName;
                if ( m_sCurrentDataSourceName.equalsAscii("Bibliography") )
                {
                    Reference< XNameAccess > xDatabaseContext(m_xORB->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
                    if ( xDatabaseContext.is() && xDatabaseContext->hasByName(m_sCurrentDataSourceName) )
                    {
                        m_xCurrentDS.set(xDatabaseContext->getByName(m_sCurrentDataSourceName),UNO_QUERY);
                        Reference<XDocumentDataSource> xDocumentDataSource(m_xCurrentDS,UNO_QUERY);
                        if ( xDocumentDataSource.is() )
                            m_xModel.set(xDocumentDataSource->getDatabaseDocument(),UNO_QUERY);
                    }
                }
                if ( !m_xCurrentDS.is() )
                    createDataSource(m_sCurrentDataSourceName);

                m_aStack.push(TElementStack::value_type(aName,DATASOURCE));
                break;
            case DATASOURCESETTINGS:
                {
                    PropertyValue aValue;
                    aValue.Name = aName;
                    m_aDataSourceSettings.push_back(aValue);
                    m_aStack.push(TElementStack::value_type(aName,DATASOURCESETTING));
                }
                break;
            case TABLES:
                m_aStack.push(TElementStack::value_type(aName,TABLE));
                createObject(sal_False,aName);
                break;
            case QUERIES:
                m_aStack.push(TElementStack::value_type(aName,QUERY));
                createObject(sal_True,aName);
                break;
            case COLUMNS:
                if ( !m_xCurrentColumn.is() )
                {
                    Reference<XColumnsSupplier> xSupplier(m_xCurrentObject,UNO_QUERY);
                    if ( xSupplier.is() )
                    {
                        Reference<XDataDescriptorFactory> xFact(xSupplier->getColumns(),UNO_QUERY);

                        m_xCurrentColumn = ( xFact.is() ? xFact->createDataDescriptor() : Reference<XPropertySet>());
                        if ( m_xCurrentColumn.is() )
                            m_xCurrentColumn->setPropertyValue(PROPERTY_NAME,makeAny(aName));
                    }
                }
                m_aStack.push(TElementStack::value_type(aName,COLUMN));
                break;
            case BOOKMARKS:
                m_aStack.push(TElementStack::value_type(aName,BOOKMARK));
                break;
        }
    }
    /*if ( aName.equalsAscii("org.openoffice.Office.DataAccess") )
        m_aStack.push(TElementStack::value_type(aName,0));
    else*/
    if ( aName.equalsAscii("DataSources") )
        m_aStack.push(TElementStack::value_type(aName,DATASOURCES));
    else if ( aName.equalsAscii("DataSourceSettings") )
        m_aStack.push(TElementStack::value_type(aName,DATASOURCESETTINGS));
    else if ( aName.equalsAscii("Tables") )
        m_aStack.push(TElementStack::value_type(aName,TABLES));
    else if ( aName.equalsAscii("Queries") )
        m_aStack.push(TElementStack::value_type(aName,QUERIES));
    else if ( aName == CONFIGKEY_DBLINK_BOOKMARKS )
        m_aStack.push(TElementStack::value_type(aName,BOOKMARKS));
    else if ( aName == CONFIGKEY_SETTINGS )
        m_aStack.push(TElementStack::value_type(aName,DATASETTINGS));
    else if ( aName.equalsAscii("Font") )
        m_aStack.push(TElementStack::value_type(aName,DATASETTINGS));
    else if ( aName == CONFIGKEY_QRYDESCR_COLUMNS )
        m_aStack.push(TElementStack::value_type(aName,COLUMNS));
    else if ( aName.equalsAscii("Font") )
        m_aStack.push(TElementStack::value_type(aName,DATASETTINGS));
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::addOrReplaceNodeFromTemplate(
        const ::rtl::OUString& aName,
        const TemplateIdentifier& aTemplate,
        sal_Int16 aAttributes )
    throw(
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::endNode()
    throw(
        MalformedDataException,
        WrappedTargetException )
{
    if ( !m_aStack.empty() )
    {
        switch(m_aStack.top().second)
        {
            case DATASOURCE:
                {
                    setProperties();
                    Reference<XStorable> xStr(m_xModel,UNO_QUERY);
                    if ( xStr.is() )
                    {
                        xStr->store();
                        xStr = NULL;
                    }
                    // register the new datbase document

                    if ( !m_sCurrentDataSourceName.equalsAscii("Bibliography") )
                    {
                        // create unique name
                        Reference< XNameAccess > xDatabaseContext(m_xORB->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);
                        if ( xDatabaseContext.is() )
                        {
                            sal_Int32 i = 0;
                            ::rtl::OUString sName;
                            sName = m_sCurrentDataSourceName;
                            while ( xDatabaseContext->hasByName(sName) )
                            {
                                sName = m_sCurrentDataSourceName + ::rtl::OUString::valueOf(++i);
                            }
                            Reference< XNamingService>(xDatabaseContext,UNO_QUERY)->registerObject(sName,m_xCurrentDS);
                        }
                    }
                    ::comphelper::disposeComponent(m_xModel);
                    m_xCurrentDS = NULL;
                }
                break;
            case DATASOURCESETTINGS:
                OSL_ENSURE(m_xCurrentDS.is(),"Data Source is NULL!");
                {
                    PropertyValue* pSettings = m_aDataSourceSettings.empty() ? NULL : &m_aDataSourceSettings[0];
                    m_xCurrentDS->setPropertyValue(PROPERTY_INFO,makeAny(Sequence< PropertyValue >(pSettings, m_aDataSourceSettings.size())));
                }
                break;
            case TABLE:
                {
                    setProperties();
                    Reference<XTablesSupplier> xSupplier(m_xCurrentDS,UNO_QUERY);
                    Reference<XNameContainer> xTables(xSupplier->getTables(),UNO_QUERY);
                    ::rtl::OUString sName;
                    m_xCurrentObject->getPropertyValue(PROPERTY_NAME) >>= sName;
                    if ( !xTables->hasByName(sName) )
                        xTables->insertByName(sName,makeAny(m_xCurrentObject));
                    m_xCurrentObject = NULL;
                }
                break;
            case QUERY:
                {
                    setProperties();
                    Reference<XQueryDefinitionsSupplier> xQueriesSupplier(m_xCurrentDS,UNO_QUERY);
                    Reference<XNameContainer> xQueries(xQueriesSupplier->getQueryDefinitions(),UNO_QUERY);
                    xQueries->insertByName(m_aStack.top().first,makeAny(m_xCurrentObject));
                    m_xCurrentObject = NULL;
                }
                break;
            case BOOKMARK:
                try
                {
                    if ( !UCBContentHelper::IsDocument(m_sDocumentLocation) )
                        return;

                    sal_Bool bForm = sal_True;
                    bForm = !isDocumentReport(m_xORB,m_sDocumentLocation);
                    Reference<XNameAccess> xNames;
                    if ( bForm )
                    {
                        Reference<XFormDocumentsSupplier> xSup(m_xModel,UNO_QUERY);
                        if ( xSup.is() )
                            xNames = xSup->getFormDocuments();
                    }
                    else
                    {
                        Reference<XReportDocumentsSupplier> xSup(m_xModel,UNO_QUERY);
                        if ( xSup.is() )
                            xNames = xSup->getReportDocuments();
                    }

                    if ( xNames.is() && m_sBookmarkName.getLength() )
                    {
                        ::rtl::OUString sServiceName = SERVICE_SDB_DOCUMENTDEFINITION;
                        Sequence< Any > aArguments(3);
                        PropertyValue aValue;
                        // set as folder
                        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Name"));
                        aValue.Value <<= m_sBookmarkName;
                        aArguments[0] <<= aValue;
                        //parent
                        aValue.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Parent"));
                        aValue.Value <<= xNames;
                        aArguments[1] <<= aValue;

                        aValue.Name = PROPERTY_URL;
                        aValue.Value <<= m_sDocumentLocation;
                        aArguments[2] <<= aValue;

                        Reference<XMultiServiceFactory> xORB(xNames,UNO_QUERY);
                        if ( xORB.is() )
                        {
                            Reference<XInterface> xComponent = xORB->createInstanceWithArguments(SERVICE_SDB_DOCUMENTDEFINITION,aArguments);
                            Reference<XNameContainer> xNameContainer(xNames,UNO_QUERY);
                            if ( xNameContainer.is() )
                                xNameContainer->insertByName(m_sBookmarkName,makeAny(xComponent));
                        }
                    }
                }
                catch(Exception&)
                {
                    OSL_ENSURE(0,"convertLinks: Exception catched!");
                }
                m_sBookmarkName = ::rtl::OUString();
                m_sDocumentLocation = ::rtl::OUString();
                break;
            case COLUMN:
                if ( m_xCurrentColumn.is() )
                {
                    setProperties();
                    Reference<XColumnsSupplier> xSupplier(m_xCurrentObject,UNO_QUERY);
                    Reference<XAppend> xAppend(xSupplier->getColumns(),UNO_QUERY);
                    if ( xAppend.is() )
                        xAppend->appendByDescriptor(m_xCurrentColumn);
                    m_xCurrentColumn = NULL;
                }
                break;
        }

        m_aStack.pop();
    }
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::dropNode(
        const ::rtl::OUString& aName )
    throw(
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::overrideProperty(
        const ::rtl::OUString& aName,
        sal_Int16 aAttributes,
        const Type& aType,
        sal_Bool bClear )
    throw(
        MalformedDataException,
        WrappedTargetException )
{
    m_bPropertyMayBeVoid = sal_True;
    if ( !m_aStack.empty() )
    {
        switch(m_aStack.top().second)
        {
            case DATASOURCE:
                {
                    m_bPropertyMayBeVoid = sal_False;
                    ::rtl::OUString sProp;
                    if ( aName == CONFIGKEY_DBLINK_CONNECTURL )
                        sProp = PROPERTY_URL;
                    else if ( aName == CONFIGKEY_DBLINK_USER )
                        sProp = PROPERTY_USER;
                    else if ( aName == CONFIGKEY_DBLINK_TABLEFILTER )
                        sProp = PROPERTY_TABLEFILTER;
                    else if ( aName == CONFIGKEY_DBLINK_TABLETYEFILTER )
                        sProp = PROPERTY_TABLETYPEFILTER;
                    else if ( aName == CONFIGKEY_DBLINK_PASSWORDREQUIRED )
                        sProp = PROPERTY_ISPASSWORDREQUIRED;
                    else if ( aName == CONFIGKEY_DBLINK_SUPPRESSVERSIONCL )
                        sProp = PROPERTY_SUPPRESSVERSIONCL;
                    else if ( aName == CONFIGKEY_LAYOUTINFORMATION )
                        sProp = PROPERTY_LAYOUTINFORMATION;

                    if ( sProp.getLength() )
                    {
                        sal_Int32 nPos = m_aProperties.getLength();
                        m_aProperties.realloc(nPos+1);
                        m_aProperties[nPos] = sProp;
                    }
                    else if ( aName == CONFIGKEY_DBLINK_LOGINTIMEOUT )
                        m_aStack.push(TElementStack::value_type(aName,LOGINTIMEOUT));
                    else
                        m_aStack.push(TElementStack::value_type(aName,NO_PROP));
                }
                break;
            case QUERY:
                {
                    m_bPropertyMayBeVoid = sal_False;
                    ::rtl::OUString sProp;
                    if ( aName == CONFIGKEY_QRYDESCR_COMMAND )
                        sProp = PROPERTY_COMMAND;
                    else if ( aName == CONFIGKEY_QRYDESCR_USE_ESCAPE_PROCESSING )
                        sProp = PROPERTY_USE_ESCAPE_PROCESSING;
                    else if ( aName == CONFIGKEY_QRYDESCR_UPDATE_TABLENAME )
                        sProp = PROPERTY_UPDATE_TABLENAME;
                    else if ( aName == CONFIGKEY_QRYDESCR_UPDATE_SCHEMANAME )
                        sProp = PROPERTY_UPDATE_SCHEMANAME;
                    else if ( aName == CONFIGKEY_QRYDESCR_UPDATE_CATALOGNAME )
                        sProp = PROPERTY_UPDATE_CATALOGNAME;
                    else if ( aName == CONFIGKEY_LAYOUTINFORMATION )
                        sProp = PROPERTY_LAYOUTINFORMATION;

                    if ( sProp.getLength() )
                    {
                        sal_Int32 nPos = m_aProperties.getLength();
                        m_aProperties.realloc(nPos+1);
                        m_aProperties[nPos] = sProp;
                    }
                    else
                        m_aStack.push(TElementStack::value_type(aName,NO_PROP));
                }
                break;
            case DATASETTINGS:
                {
                    m_bPropertyMayBeVoid = sal_False;
                    ::rtl::OUString sProp;
                    if (	  aName == CONFIGKEY_DEFSET_FILTER ) sProp = PROPERTY_FILTER;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_NAME ) sProp = PROPERTY_FONTNAME;
                    else if ( aName == CONFIGKEY_DEFSET_ORDER ) sProp = PROPERTY_ORDER;
                    else if ( aName == CONFIGKEY_DEFSET_APPLYFILTER ) sProp = PROPERTY_APPLYFILTER;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_DEFSET_ROW_HEIGHT) ) sProp = PROPERTY_ROW_HEIGHT;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_DEFSET_TEXTCOLOR) ) sProp = PROPERTY_TEXTCOLOR;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_DEFSET_FONT_UNDERLINECOLOR) ) sProp = PROPERTY_TEXTLINECOLOR;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_CHARACTEREMPHASIS ) sProp = PROPERTY_TEXTEMPHASIS;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_CHARACTERRELIEF ) sProp = PROPERTY_TEXTRELIEF;
                        // font
                    else if ( aName == CONFIGKEY_DEFSET_FONT_HEIGHT ) sProp = PROPERTY_FONTHEIGHT;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_WIDTH ) sProp = PROPERTY_FONTWIDTH;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_STYLENAME ) sProp = PROPERTY_FONTSTYLENAME;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_FAMILY ) sProp = PROPERTY_FONTFAMILY;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_CHARSET ) sProp = PROPERTY_FONTCHARSET;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_PITCH ) sProp = PROPERTY_FONTPITCH;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_CHARACTERWIDTH ) sProp = PROPERTY_FONTCHARWIDTH;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_WEIGHT ) sProp = PROPERTY_FONTWEIGHT;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_UNDERLINE ) sProp = PROPERTY_FONTUNDERLINE;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_STRIKEOUT ) sProp = PROPERTY_FONTSTRIKEOUT;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_ORIENTATION ) sProp = PROPERTY_FONTORIENTATION;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_KERNING ) sProp = PROPERTY_FONTKERNING;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_WORDLINEMODE ) sProp = PROPERTY_FONTWORDLINEMODE;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_TYPE ) sProp = PROPERTY_FONTTYPE;
                    else if ( aName == CONFIGKEY_DEFSET_FONT_SLANT ) sProp = PROPERTY_FONTSLANT;

                    if ( sProp.getLength() )
                    {
                        sal_Int32 nPos = m_aProperties.getLength();
                        m_aProperties.realloc(nPos+1);
                        m_aProperties[nPos] = sProp;
                    }
                    else
                        m_aStack.push(TElementStack::value_type(aName,NO_PROP));
                }
                break;
            case COLUMN:
                {
                    ::rtl::OUString sProp;
                    m_bPropertyMayBeVoid = sal_False;
                    if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_ALIGNMENT) ) sProp = PROPERTY_ALIGN;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_WIDTH) ) sProp = PROPERTY_WIDTH;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_RELPOSITION) ) sProp = PROPERTY_RELATIVEPOSITION;
                    else if ( aName == CONFIGKEY_COLUMN_HIDDEN ) sProp = PROPERTY_HIDDEN;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_HELPTEXT) ) sProp = PROPERTY_HELPTEXT;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_CONTROLDEFAULT) ) sProp = PROPERTY_CONTROLDEFAULT;
                    else if ( m_bPropertyMayBeVoid = (aName == CONFIGKEY_COLUMN_NUMBERFORMAT) ) sProp = PROPERTY_NUMBERFORMAT;


                    if ( sProp.getLength() )
                    {
                        sal_Int32 nPos = m_aProperties.getLength();
                        m_aProperties.realloc(nPos+1);
                        m_aProperties[nPos] = sProp;
                    }
                    else
                        m_aStack.push(TElementStack::value_type(aName,NO_PROP));
                }
                break;
            case BOOKMARK:
                break;
        }
    }
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::setPropertyValue(
        const Any& aValue )
    throw(
        MalformedDataException,
        WrappedTargetException )
{
    if ( !m_aStack.empty() )
    {
        switch(m_aStack.top().second)
        {
            case LOGINTIMEOUT:
                {
                    Reference< ::com::sun::star::sdbc::XDataSource> xDataSource(m_xCurrentDS,UNO_QUERY);
                    sal_Int32 nTimeOut = 0;
                    aValue >>= nTimeOut;
                    if ( xDataSource.is() && nTimeOut >= 0 )
                        xDataSource->setLoginTimeout(nTimeOut);
                    m_aStack.pop();
                }
                break;
            case DATASOURCESETTING:
                OSL_ENSURE(!m_aDataSourceSettings.empty(),"Settings are emtpy!");
                if ( aValue.hasValue() )
                    m_aDataSourceSettings.rbegin()->Value = aValue;
                else
                    m_aDataSourceSettings.pop_back();
                break;
            case BOOKMARK:
                aValue >>= m_sDocumentLocation;
                break;
            case NO_PROP:
                m_aStack.pop();
                break;
            default:
                OSL_ENSURE(m_aProperties.getLength(),"Properties are zero!");
                if ( m_aProperties.getLength() )
                {
                    if ( m_aProperties[m_aProperties.getLength()-1] != PROPERTY_LAYOUTINFORMATION )
                    {
                        if ( !m_bPropertyMayBeVoid && !aValue.hasValue() )
                        {
                            m_aProperties.realloc(m_aProperties.getLength()-1);
                        }
                        else
                        {
                            sal_Int32 nPos = m_aValues.getLength();
                            m_aValues.realloc(nPos+1);
                            m_aValues[nPos] = aValue;
                        }
                    }
                    else
                    {
                        try
                        {
                            Sequence< sal_Int8 > aInputSequence;
                            aValue >>= aInputSequence;
                            sal_Int32 nPos = m_aValues.getLength();
                            m_aValues.realloc(nPos+1);
                            Sequence< PropertyValue > aLayout;
                            if ( aInputSequence.getLength() )
                            {
                                Reference< XInputStream>	   xInStreamHelper = new SequenceInputStream(aInputSequence);; 	// used for wrapping sequence to xinput
                                Reference< XObjectInputStream> xInStream = Reference< XObjectInputStream >(m_xORB->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.ObjectInputStream")),UNO_QUERY);
                                Reference< XInputStream> xMarkInStream = Reference< XInputStream >(m_xORB->createInstance(::rtl::OUString::createFromAscii("com.sun.star.io.MarkableInputStream")),UNO_QUERY);
                                Reference< XActiveDataSink >(xMarkInStream,UNO_QUERY)->setInputStream(xInStreamHelper);
                                Reference< XActiveDataSink >   xInDataSource(xInStream, UNO_QUERY);
                                OSL_ENSURE(xInDataSource.is(),"Couldn't create com.sun.star.io.ObjectInputStream!");
                                xInDataSource->setInputStream(xMarkInStream);

                                if ( DATASOURCE == m_aStack.top().second )
                                    LoadTableWindows(xInStream,aLayout);
                                else if ( QUERY == m_aStack.top().second )
                                    LoadTableFields(xInStream,aLayout);
                            }
                            m_aValues[nPos] <<= aLayout;
                        }
                        catch(const Exception& e)
                        {
                            throw WrappedTargetException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Property could not be set.")),*this,makeAny(e));
                        }
                    }
                }
                break;
        }
    }
}
// -----------------------------------------------------------------------------

void SAL_CALL OCfgImport::setPropertyValueForLocale(
        const Any& aValue,
        const ::rtl::OUString& aLocale )
    throw(
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::endProperty()
    throw(
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::addProperty( 	 
        const rtl::OUString& aName,
        sal_Int16 aAttributes,
        const Type& aType )
    throw(	 
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------

void SAL_CALL  OCfgImport::addPropertyWithValue( 	 
        const rtl::OUString& aName,
        sal_Int16 aAttributes,
        const Any& aValue ) 
    throw(	 
        MalformedDataException,
        WrappedTargetException )
{
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// }// dbacfg
// -----------------------------------------------------------------------------
