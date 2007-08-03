/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ReportDefinition.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2007-08-03 09:53:39 $
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
#ifndef REPORTDESIGN_API_REPORTDEFINITION_HXX
#include "ReportDefinition.hxx"
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYATTRIBUTE_HPP_
#include <com/sun/star/beans/PropertyAttribute.hpp>
#endif
#ifndef _COM_SUN_STAR_REPORT_GROUPKEEPTOGETHER_HPP_
#include <com/sun/star/report/GroupKeepTogether.hpp>
#endif
#ifndef _COM_SUN_STAR_REPORT_REPORTPRINTOPTION_HPP_
#include <com/sun/star/report/ReportPrintOption.hpp>
#endif
#ifndef _COM_SUN_STAR_REPORT_XFUNCTION_HPP_
#include <com/sun/star/report/XFunction.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_BORDERLINE_HPP_
#include <com/sun/star/table/BorderLine.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_SHADOWFORMAT_HPP_
#include <com/sun/star/table/ShadowFormat.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_PAGESTYLELAYOUT_HPP_
#include <com/sun/star/style/PageStyleLayout.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_GRAPHICLOCATION_HPP_
#include <com/sun/star/style/GraphicLocation.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_ATTRIBUTEDATA_HPP_
#include <com/sun/star/xml/AttributeData.hpp>
#endif
#ifndef _COMPHELPER_NAMECONTAINER_HXX_
#include <comphelper/namecontainer.hxx>
#endif
#ifndef _COMPHELPER_BROADCASTHELPER_HXX_
#include <comphelper/broadcasthelper.hxx>
#endif
#ifndef _COMPHELPER_SEQUENCE_HXX_
#include <comphelper/sequence.hxx>
#endif
#ifndef _SV_SVAPP_HXX //autogen
#include <vcl/svapp.hxx>
#endif
#ifndef _VOS_MUTEX_HXX_
#include <vos/mutex.hxx>
#endif
#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
#ifndef COMPHELPER_PROPERTYSTATECONTAINER_HXX
#include <comphelper/propertystatecontainer.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_ARRAY_HELPER_HXX_ 
#include <comphelper/proparrhlp.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_XMULTIPROPERTYSTATES_HPP_
#include <com/sun/star/beans/XMultiPropertyStates.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_EVENTOBJECT_HPP_
#include <com/sun/star/document/EventObject.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEVENTLISTENER_HPP_
#include <com/sun/star/document/XEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_XSTYLE_HPP_
#include <com/sun/star/style/XStyle.hpp>
#endif
#ifndef _COMPHELPER_DOCUMENTCONSTANTS_HXX
#include <comphelper/documentconstants.hxx>
#endif
#ifndef _COM_SUN_STAR_EMBED_XTRANSACTEDOBJECT_HPP_
#include <com/sun/star/embed/XTransactedObject.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_EMBEDMAPUNITS_HPP_
#include <com/sun/star/embed/EmbedMapUnits.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XACTIVEDATASOURCE_HPP_
#include <com/sun/star/io/XActiveDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_EMBED_ELEMENTMODES_HPP_
#include <com/sun/star/embed/ElementModes.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XSEEKABLE_HPP_
#include <com/sun/star/io/XSeekable.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATOR_HPP_
#include <com/sun/star/task/XStatusIndicator.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORFACTORY_HPP_
#include <com/sun/star/task/XStatusIndicatorFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_UI_XUICONFIGURATIONSTORAGE_HPP_
#include <com/sun/star/ui/XUIConfigurationStorage.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XEXPORTER_HPP_
#include <com/sun/star/document/XExporter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XIMPORTER_HPP_
#include <com/sun/star/document/XImporter.hpp>
#endif
#ifndef _COM_SUN_STAR_DOCUMENT_XFILTER_HPP_
#include <com/sun/star/document/XFilter.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_ERRORCODEIOEXCEPTION_HPP_
#include <com/sun/star/task/ErrorCodeIOException.hpp>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XDOCUMENTHANDLER_HPP_
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#endif
#ifndef REPORTDESIGN_SHARED_CORESTRINGS_HRC
#include "corestrings.hrc"
#endif
#ifndef REPORTDESIGN_API_GROUPS_HXX
#include "Groups.hxx"
#endif
#ifndef REPORTDESIGN_API_SECTION_HXX
#include "Section.hxx"
#endif
#include "FixedLine.hxx"
#ifndef REPORTDESIGN_CORE_RESOURCE_HRC_
#include "core_resource.hrc"
#endif
#ifndef REPORTDESIGN_CORE_RESOURCE_HXX_
#include "core_resource.hxx"
#endif
#ifndef REPORTDESIGN_TOOLS_HXX
#include "Tools.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _CONNECTIVITY_COMMONTOOLS_HXX_
#include <connectivity/CommonTools.hxx>
#endif
#ifndef _COMPHELPER_PROPERTY_HXX_
#include <comphelper/property.hxx>
#endif
#ifndef _COMPHELPER_PROPERTSETINFO_HXX_
#include <comphelper/propertysetinfo.hxx>
#endif
#ifndef _COMPHELPER_GENERICPROPERTYSET_HXX_
#include <comphelper/genericpropertyset.hxx>
#endif
#ifndef _COMPHELPER_MEDIADESCRIPTOR_HXX_
#include <comphelper/mediadescriptor.hxx>
#endif
#ifndef _COMPHELPER_NAMECONTAINER_HXX_
#include <comphelper/namecontainer.hxx>
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATOR_HPP_
#include <com/sun/star/task/XStatusIndicator.hpp>
#endif
#ifndef REPORTDESIGN_API_FUNCTIONS_HXX
#include "Functions.hxx"
#endif
#include <boost/mem_fn.hpp>
#include <boost/bind.hpp>
#include <boost/utility.hpp>
#ifndef INCLUDED_SVTOOLS_SAVEOPT_HXX
#include <svtools/saveopt.hxx>
#endif
#ifndef REPORT_RPTMODEL_HXX
#include "RptModel.hxx"
#endif
#ifndef RPT_FORMATTEDFIELD_HXX
#include "FormattedField.hxx"
#endif
#ifndef RPT_FIXEDTEXT_HXX
#include "FixedText.hxx"
#endif
#ifndef RPT_IMAGECONTROL_HXX
#include "ImageControl.hxx"
#endif
#ifndef RPT_SHAPE_HXX
#include "Shape.hxx"
#endif
#ifndef _SFXITEMPOOL_HXX
#include <svtools/itempool.hxx>
#endif
#ifndef _SVDLAYER_HXX
#include <svx/svdlayer.hxx>
#endif
#ifndef _CPPUHELPER_INTERFACECONTAINER_H_
#include <cppuhelper/interfacecontainer.h>
#endif
#ifndef RPT_REPORTCOMPONENT_HXX
#include "ReportComponent.hxx"
#endif
#ifndef _COM_SUN_STAR_SDB_XOFFICEDATABASEDOCUMENT_HPP_
#include <com/sun/star/sdb/XOfficeDatabaseDocument.hpp>
#endif
#ifndef _COM_SUN_STAR_STYLE_NUMBERINGTYPE_HPP_
#include <com/sun/star/style/NumberingType.hpp>
#endif

#define MAP_LEN(x) x, sizeof(x) - 1
#define MAP_CHAR_LEN(x) ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(x))
//	page styles
#define SC_UNO_PAGE_GRAPHICFILT		"BackGraphicFilter"
#define SC_UNO_PAGE_LEFTBORDER		"LeftBorder"
#define SC_UNO_PAGE_RIGHTBORDER		"RightBorder"
#define SC_UNO_PAGE_BOTTBORDER		"BottomBorder"
#define SC_UNO_PAGE_TOPBORDER		"TopBorder"
#define SC_UNO_PAGE_LEFTBRDDIST		"LeftBorderDistance"
#define SC_UNO_PAGE_RIGHTBRDDIST	"RightBorderDistance"
#define SC_UNO_PAGE_BOTTBRDDIST		"BottomBorderDistance"
#define SC_UNO_PAGE_TOPBRDDIST		"TopBorderDistance"
#define SC_UNO_PAGE_BORDERDIST		"BorderDistance"
#define SC_UNO_PAGE_SHADOWFORM		"ShadowFormat"
#define SC_UNO_PAGE_PAPERTRAY		"PrinterPaperTray"
#define SC_UNO_PAGE_SCALEVAL		"PageScale"
#define SC_UNO_PAGE_SCALETOPAG		"ScaleToPages"
#define SC_UNO_PAGE_SCALETOX        "ScaleToPagesX"
#define SC_UNO_PAGE_SCALETOY        "ScaleToPagesY"
#define SC_UNO_PAGE_FIRSTPAGE		"FirstPageNumber"
#define SC_UNO_PAGE_LEFTHDRCONT		"LeftPageHeaderContent"
#define SC_UNO_PAGE_LEFTFTRCONT		"LeftPageFooterContent"
#define SC_UNO_PAGE_RIGHTHDRCON		"RightPageHeaderContent"
#define SC_UNO_PAGE_RIGHTFTRCON		"RightPageFooterContent"
#define SC_UNO_PAGE_PRINTFORMUL		"PrintFormulas"
#define SC_UNO_PAGE_PRINTZERO		"PrintZeroValues"
#define SC_UNO_PAGE_HDRBACKCOL		"HeaderBackColor"
#define SC_UNO_PAGE_HDRBACKTRAN		"HeaderBackTransparent"
#define SC_UNO_PAGE_HDRGRFFILT		"HeaderBackGraphicFilter"
#define SC_UNO_PAGE_HDRGRFLOC		"HeaderBackGraphicLocation"
#define SC_UNO_PAGE_HDRGRFURL		"HeaderBackGraphicURL"
#define SC_UNO_PAGE_HDRLEFTBOR		"HeaderLeftBorder"
#define SC_UNO_PAGE_HDRRIGHTBOR		"HeaderRightBorder"
#define SC_UNO_PAGE_HDRBOTTBOR		"HeaderBottomBorder"
#define SC_UNO_PAGE_HDRTOPBOR		"HeaderTopBorder"
#define SC_UNO_PAGE_HDRLEFTBDIS		"HeaderLeftBorderDistance"
#define SC_UNO_PAGE_HDRRIGHTBDIS	"HeaderRightBorderDistance"
#define SC_UNO_PAGE_HDRBOTTBDIS		"HeaderBottomBorderDistance"
#define SC_UNO_PAGE_HDRTOPBDIS		"HeaderTopBorderDistance"
#define SC_UNO_PAGE_HDRBRDDIST		"HeaderBorderDistance"
#define SC_UNO_PAGE_HDRSHADOW		"HeaderShadowFormat"
#define SC_UNO_PAGE_HDRLEFTMAR		"HeaderLeftMargin"
#define SC_UNO_PAGE_HDRRIGHTMAR		"HeaderRightMargin"
#define SC_UNO_PAGE_HDRBODYDIST		"HeaderBodyDistance"
#define SC_UNO_PAGE_HDRHEIGHT		"HeaderHeight"
#define SC_UNO_PAGE_HDRON			"HeaderIsOn"
#define SC_UNO_PAGE_HDRDYNAMIC		"HeaderIsDynamicHeight"
#define SC_UNO_PAGE_HDRSHARED		"HeaderIsShared"
#define SC_UNO_PAGE_FTRBACKCOL		"FooterBackColor"
#define SC_UNO_PAGE_FTRBACKTRAN		"FooterBackTransparent"
#define SC_UNO_PAGE_FTRGRFFILT		"FooterBackGraphicFilter"
#define SC_UNO_PAGE_FTRGRFLOC		"FooterBackGraphicLocation"
#define SC_UNO_PAGE_FTRGRFURL		"FooterBackGraphicURL"
#define SC_UNO_PAGE_FTRLEFTBOR		"FooterLeftBorder"
#define SC_UNO_PAGE_FTRRIGHTBOR		"FooterRightBorder"
#define SC_UNO_PAGE_FTRBOTTBOR		"FooterBottomBorder"
#define SC_UNO_PAGE_FTRTOPBOR		"FooterTopBorder"
#define SC_UNO_PAGE_FTRLEFTBDIS		"FooterLeftBorderDistance"
#define SC_UNO_PAGE_FTRRIGHTBDIS	"FooterRightBorderDistance"
#define SC_UNO_PAGE_FTRBOTTBDIS		"FooterBottomBorderDistance"
#define SC_UNO_PAGE_FTRTOPBDIS		"FooterTopBorderDistance"
#define SC_UNO_PAGE_FTRBRDDIST		"FooterBorderDistance"
#define SC_UNO_PAGE_FTRSHADOW		"FooterShadowFormat"
#define SC_UNO_PAGE_FTRLEFTMAR		"FooterLeftMargin"
#define SC_UNO_PAGE_FTRRIGHTMAR		"FooterRightMargin"
#define SC_UNO_PAGE_FTRBODYDIST		"FooterBodyDistance"
#define SC_UNO_PAGE_FTRHEIGHT		"FooterHeight"
#define SC_UNO_PAGE_FTRON			"FooterIsOn"
#define SC_UNO_PAGE_FTRDYNAMIC		"FooterIsDynamicHeight"
#define SC_UNO_PAGE_FTRSHARED		"FooterIsShared"

// =============================================================================
namespace reportdesign
{
// =============================================================================
    using namespace com::sun::star;
    using namespace comphelper;
    using namespace rptui;
// -----------------------------------------------------------------------------
// local functions
// -----------------------------------------------------------------------------
void lcl_setModelReadOnly(const uno::Reference< embed::XStorage >& _xStorage,::boost::shared_ptr<rptui::OReportModel>& _rModel)
{
    uno::Reference<beans::XPropertySet> xProp(_xStorage,uno::UNO_QUERY);
    sal_Int32 nOpenMode = embed::ElementModes::READ;
    if ( xProp.is() )
        xProp->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OpenMode"))) >>= nOpenMode;

    _rModel->SetReadOnly((nOpenMode & embed::ElementModes::WRITE) != embed::ElementModes::WRITE);
}
void lcl_stripLoadArguments( ::comphelper::MediaDescriptor& _rDescriptor, uno::Sequence< beans::PropertyValue >& _rArgs )
{
    _rDescriptor.erase( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "StatusIndicator" ) ) );
    _rDescriptor.erase( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "InteractionHandler" ) ) );
    _rDescriptor.erase( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "Model" ) ) );
    _rDescriptor >> _rArgs;
}
// -----------------------------------------------------------------------------
void lcl_extractAndStartStatusIndicator( const ::comphelper::MediaDescriptor& _rDescriptor, uno::Reference< task::XStatusIndicator >& _rxStatusIndicator,
    uno::Sequence< uno::Any >& _rCallArgs )
{
    try
    {
        _rxStatusIndicator = _rDescriptor.getUnpackedValueOrDefault( _rDescriptor.PROP_STATUSINDICATOR(), _rxStatusIndicator );
        if ( _rxStatusIndicator.is() )
        {
            _rxStatusIndicator->start( ::rtl::OUString(), (sal_Int32)1000000 );

            sal_Int32 nLength = _rCallArgs.getLength();
            _rCallArgs.realloc( nLength + 1 );
            _rCallArgs[ nLength ] <<= _rxStatusIndicator;
        }
    }
    catch( const uno::Exception& )
    {
        OSL_ENSURE( sal_False, "lcl_extractAndStartStatusIndicator: caught an exception!" );
    }
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface> lcl_createDefault()
{
    comphelper::PropertyMapEntry aExportInfoMap[] =
    {
        { MAP_LEN( "UsePrettyPrinting" ), 0, &::getCppuType((sal_Bool*)0), beans::PropertyAttribute::MAYBEVOID, 0},
        { NULL, 0, 0, NULL, 0, 0 }
    };
    uno::Reference< beans::XPropertySet > xInfoSet( comphelper::GenericPropertySet_CreateInstance( new comphelper::PropertySetInfo( aExportInfoMap ) ) );
    return xInfoSet.get();
}
// -----------------------------------------------------------------------------
typedef ::comphelper::OPropertyStateContainer		OStyle_PBASE;
class OStyle;
typedef ::comphelper::OPropertyArrayUsageHelper	<	OStyle
                                                >	OStyle_PABASE;
typedef ::cppu::WeakImplHelper2< style::XStyle, beans::XMultiPropertyStates> TStyleBASE;

class OStyle :   public ::comphelper::OMutexAndBroadcastHelper
                ,public TStyleBASE
                ,public OStyle_PBASE
                ,public OStyle_PABASE
{
    awt::Size m_aSize;

protected:
    void getPropertyDefaultByHandle( sal_Int32 _nHandle, uno::Any& _rDefault ) const;
    ~OStyle(){}
public:
    OStyle();
    

    DECLARE_XINTERFACE( )

    // XPropertySet
    com::sun::star::uno::Reference<com::sun::star::beans::XPropertySetInfo>  SAL_CALL getPropertySetInfo() throw(com::sun::star::uno::RuntimeException);
    ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();
    ::cppu::IPropertyArrayHelper* createArrayHelper( ) const;

    // XStyle
    ::sal_Bool SAL_CALL isUserDefined(  ) throw (uno::RuntimeException);
    ::sal_Bool SAL_CALL isInUse(  ) throw (uno::RuntimeException);
    ::rtl::OUString SAL_CALL getParentStyle(  ) throw (uno::RuntimeException);
    void SAL_CALL setParentStyle( const ::rtl::OUString& aParentStyle ) throw (container::NoSuchElementException, uno::RuntimeException);
    // XNamed
    ::rtl::OUString SAL_CALL getName(  ) throw (uno::RuntimeException);
    void SAL_CALL setName( const ::rtl::OUString& aName ) throw (uno::RuntimeException);

    // XMultiPropertyState
    uno::Sequence< beans::PropertyState > SAL_CALL getPropertyStates( const uno::Sequence< ::rtl::OUString >& aPropertyNames ) throw (beans::UnknownPropertyException, uno::RuntimeException)
    {
        return OStyle_PBASE::getPropertyStates(aPropertyNames);
    }
    void SAL_CALL setAllPropertiesToDefault(  ) throw (uno::RuntimeException);
    void SAL_CALL setPropertiesToDefault( const uno::Sequence< ::rtl::OUString >& aPropertyNames ) throw (beans::UnknownPropertyException, uno::RuntimeException);
    uno::Sequence< uno::Any > SAL_CALL getPropertyDefaults( const uno::Sequence< ::rtl::OUString >& aPropertyNames ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException);
};
// -----------------------------------------------------------------------------
OStyle::OStyle()
:OStyle_PBASE(m_aBHelper)
,m_aSize(21000,29700)
{
    const style::GraphicLocation eGraphicLocation = style::GraphicLocation_NONE;
    const sal_Bool bFalse = sal_False;
    const sal_Bool bTrue = sal_True;
    const sal_Int32 nMargin = 2000;
    //const sal_Int32 nColor = COL_WHITE;
    const sal_Int32 nTransparent = COL_TRANSPARENT;
    const sal_Int32 nZero = 0;
    const sal_Int16 n16Zero = 0;
    const sal_Int16 nNummeringType = style::NumberingType::ARABIC;
    const ::rtl::OUString sName(RTL_CONSTASCII_USTRINGPARAM("Default"));
    const ::rtl::OUString sEmpty;
    const table::BorderLine eBorderLine(0,0,0,0);
    const table::ShadowFormat eShadowFormat(table::ShadowLocation_NONE,0,0,0);
    const style::PageStyleLayout ePageStyleLayout = style::PageStyleLayout_ALL;
    const sal_Int32 nBound = beans::PropertyAttribute::BOUND;
    const sal_Int32 nMayBeVoid = beans::PropertyAttribute::MAYBEVOID;

    sal_Int32 i = 0;
    registerPropertyNoMember( PROPERTY_NAME, ++i,nBound,::getCppuType( static_cast< ::rtl::OUString *>(NULL) ), &sName );

    registerPropertyNoMember(PROPERTY_BACKCOLOR,	                ++i,nBound,::getCppuType((const sal_Int32*)0) ,&nTransparent);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_GRAPHICFILT),	++i,nBound,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);

    registerPropertyNoMember(PROPERTY_BACKGRAPHICLOCATION,	++i,nBound,::getCppuType((const style::GraphicLocation*)0) ,&eGraphicLocation);
    //registerPropertyNoMember(PROPERTY_BACKGRAPHICURL,	++i,nBound,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);
    registerPropertyNoMember(PROPERTY_BACKTRANSPARENT,	++i,nBound,::getBooleanCppuType() ,&bTrue);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_BACKCOLOR),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_BORDERDIST),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_BOTTBORDER),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_BOTTBRDDIST),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(PROPERTY_BOTTOMMARGIN,	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nMargin);
    registerPropertyNoMember(MAP_CHAR_LEN("DisplayName"),		++i,nBound,::getCppuType((rtl::OUString*)0) ,&sEmpty);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FIRSTPAGE),	++i,nBound,::getCppuType((const sal_Int16*)0) ,&n16Zero);
    //
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBACKCOL),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nTransparent);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRGRFFILT),	++i,nBound,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRGRFLOC),	++i,nBound,::getCppuType((const style::GraphicLocation*)0) ,&eGraphicLocation);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRGRFURL),	++i,nBound,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBACKTRAN),	++i,nBound,::getBooleanCppuType() ,&bTrue);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_FTRBACKCOL),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBODYDIST),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBRDDIST),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBOTTBOR),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRBOTTBDIS),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_FTRDYNAMIC),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRHEIGHT),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRDYNAMIC),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRON),		++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRSHARED),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRLEFTBOR),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRLEFTBDIS),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRLEFTMAR),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_FTRON),		++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRRIGHTBOR),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRRIGHTBDIS),++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRRIGHTMAR),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRSHADOW),	++i,nBound,::getCppuType((const table::ShadowFormat*)0) ,&eShadowFormat);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_FTRSHARED),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRTOPBOR),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_FTRTOPBDIS),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    //
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBACKCOL),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nTransparent);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRGRFFILT),	++i,nBound|nMayBeVoid,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRGRFLOC),	++i,nBound|nMayBeVoid,::getCppuType((const style::GraphicLocation*)0) ,&eGraphicLocation);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRGRFURL),	++i,nBound|nMayBeVoid,::getCppuType((const ::rtl::OUString*)0) ,&sEmpty);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBACKTRAN),	++i,nBound|nMayBeVoid,::getBooleanCppuType() ,&bTrue);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_HDRBACKCOL),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBODYDIST),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBRDDIST),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBOTTBOR),	++i,nBound|nMayBeVoid,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRBOTTBDIS),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_HDRDYNAMIC),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRHEIGHT),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRDYNAMIC),	++i,nBound|nMayBeVoid,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRON),		++i,nBound|nMayBeVoid,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRSHARED),	++i,nBound|nMayBeVoid,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRLEFTBOR),	++i,nBound|nMayBeVoid,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRLEFTBDIS),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRLEFTMAR),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_HDRON),		++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRRIGHTBOR),	++i,nBound|nMayBeVoid,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRRIGHTBDIS),++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRRIGHTMAR),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRSHADOW),	++i,nBound|nMayBeVoid,::getCppuType((const table::ShadowFormat*)0) ,&eShadowFormat);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_HDRSHARED),	++i,nBound,::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRTOPBOR),	++i,nBound|nMayBeVoid,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_HDRTOPBDIS),	++i,nBound|nMayBeVoid,::getCppuType((const sal_Int32*)0) ,&nZero);
    //
    registerProperty(PROPERTY_HEIGHT,		++i,nBound,&m_aSize.Height,		::getCppuType((const sal_Int32*)0) );
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_BACKTRANS),	++i,nBound,	::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(PROPERTY_ISLANDSCAPE,	                ++i,nBound,			::getBooleanCppuType() ,&bFalse);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_LEFTBORDER),	++i,nBound,		::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_LEFTBRDDIST),	++i,nBound,		::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(PROPERTY_LEFTMARGIN,	++i,beans::PropertyAttribute::BOUND,		::getCppuType((const sal_Int32*)0) ,&nMargin);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_LEFTFTRCONT),	++i,nBound,::getCppuType((const uno::Reference< sheet::XHeaderFooterContent >*)0) ,NULL);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_LEFTHDRCONT),	++i,nBound,::getCppuType((const uno::Reference< sheet::XHeaderFooterContent >*)0) ,NULL);
    registerPropertyNoMember(PROPERTY_NUMBERINGTYPE,	            ++i,nBound,::getCppuType((const sal_Int16*)0) ,&nNummeringType);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_SCALEVAL),	++i,nBound,::getCppuType((const sal_Int16*)0) ,&n16Zero);
    registerPropertyNoMember(PROPERTY_PAGESTYLELAYOUT,	            ++i,nBound,::getCppuType((const style::PageStyleLayout*)0) ,&ePageStyleLayout);
    const ::rtl::OUString sPaperTray(RTL_CONSTASCII_USTRINGPARAM("[From printer settings]"));
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_PAPERTRAY),	++i,nBound,::getCppuType((const ::rtl::OUString*)0) ,&sPaperTray);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_RIGHTBORDER),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_RIGHTBRDDIST),++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(PROPERTY_RIGHTMARGIN,	++i,beans::PropertyAttribute::BOUND,::getCppuType((const sal_Int32*)0) ,&nMargin);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_RIGHTFTRCON),	++i,nBound,::getCppuType((const uno::Reference< sheet::XHeaderFooterContent >*)0) ,NULL);
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_RIGHTHDRCON),	++i,nBound,::getCppuType((const uno::Reference< sheet::XHeaderFooterContent >*)0) ,NULL);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_SCALETOPAG),	++i,nBound,::getCppuType((const sal_Int16*)0) ,&n16Zero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_SCALETOX),	++i,nBound,::getCppuType((const sal_Int16*)0) ,&n16Zero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_SCALETOY),	++i,nBound,::getCppuType((const sal_Int16*)0) ,&n16Zero);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_SHADOWFORM),	++i,nBound,::getCppuType((const table::ShadowFormat*)0) ,&eShadowFormat);
    registerProperty(PROPERTY_PAPERSIZE,		            ++i,beans::PropertyAttribute::BOUND,&m_aSize,::getCppuType((const awt::Size*)0) );
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_TOPBORDER),	++i,nBound,::getCppuType((const table::BorderLine*)0) ,&eBorderLine);
    registerPropertyNoMember(MAP_CHAR_LEN(SC_UNO_PAGE_TOPBRDDIST),	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nZero);
    registerPropertyNoMember(PROPERTY_TOPMARGIN,	++i,nBound,::getCppuType((const sal_Int32*)0) ,&nMargin);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_FTRBACKTRAN),++i,nBound,::getBooleanCppuType() ,&bFalse);
    //registerPropertyNoMember(MAP_CHAR_LEN(OLD_UNO_PAGE_HDRBACKTRAN),++i,nBound,::getBooleanCppuType() ,&bFalse);
    uno::Reference< container::XNameContainer> xAttribs = ::comphelper::NameContainer_createInstance(::getCppuType(static_cast< xml::AttributeData* >(NULL)));
    registerPropertyNoMember(MAP_CHAR_LEN("UserDefinedAttributes"),		++i,nBound,::getCppuType((uno::Reference<container::XNameContainer>*)0) ,&xAttribs);
    registerProperty(PROPERTY_WIDTH,		++i,nBound,&m_aSize.Width,::getCppuType((const sal_Int32*)0) );
    //registerPropertyNoMember(MAP_CHAR_LEN(SC_UNONAME_WRITING),		++i,nBound,:.getCppuType((sal_Int16*)0) ,&n16Zero);
    registerPropertyNoMember(MAP_CHAR_LEN("PrinterName"),				++i,nBound,::getCppuType((const ::rtl::OUString*)0),&sEmpty);
    uno::Sequence<sal_Int8> aSe;
    registerPropertyNoMember(MAP_CHAR_LEN("PrinterSetup"),				++i,nBound,::getCppuType((const uno::Sequence<sal_Int8>*)0),&aSe);
        

}
// -----------------------------------------------------------------------------
IMPLEMENT_FORWARD_XINTERFACE2(OStyle,TStyleBASE,OStyle_PBASE)
// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySetInfo>  SAL_CALL OStyle::getPropertySetInfo() throw(uno::RuntimeException)
{
    return createPropertySetInfo( getInfoHelper() );
}
// -----------------------------------------------------------------------------
void OStyle::getPropertyDefaultByHandle( sal_Int32 /*_nHandle*/, uno::Any& /*_rDefault*/ ) const
{
}
//-------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OStyle::getInfoHelper()
{
    return *const_cast<OStyle*>(this)->getArrayHelper();
}
//--------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OStyle::createArrayHelper( ) const
{
    uno::Sequence< beans::Property > aProps;
    describeProperties(aProps);
    return new ::cppu::OPropertyArrayHelper(aProps);
}
// -----------------------------------------------------------------------------
// XStyle
::sal_Bool SAL_CALL OStyle::isUserDefined(  ) throw (uno::RuntimeException)
{
    return sal_False;
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OStyle::isInUse(  ) throw (uno::RuntimeException)
{
    return sal_True;
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL OStyle::getParentStyle(  ) throw (uno::RuntimeException)
{
    return ::rtl::OUString();
}
// -----------------------------------------------------------------------------
void SAL_CALL OStyle::setParentStyle( const ::rtl::OUString& /*aParentStyle*/ ) throw (container::NoSuchElementException, uno::RuntimeException)
{
}
// -----------------------------------------------------------------------------
// XNamed
::rtl::OUString SAL_CALL OStyle::getName(  ) throw (uno::RuntimeException)
{
    ::rtl::OUString sName;
    getPropertyValue(PROPERTY_NAME) >>= sName;
    return sName;
}
// -----------------------------------------------------------------------------
void SAL_CALL OStyle::setName( const ::rtl::OUString& aName ) throw (uno::RuntimeException)
{
    setPropertyValue(PROPERTY_NAME,uno::makeAny(aName));
}
// -----------------------------------------------------------------------------
void SAL_CALL OStyle::setAllPropertiesToDefault(  ) throw (uno::RuntimeException)
{
}
// -----------------------------------------------------------------------------
void SAL_CALL OStyle::setPropertiesToDefault( const uno::Sequence< ::rtl::OUString >& aPropertyNames ) throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    const ::rtl::OUString* pIter = aPropertyNames.getConstArray();
    const ::rtl::OUString* pEnd	  = pIter + aPropertyNames.getLength();
    for(;pIter != pEnd;++pIter)
        setPropertyToDefault(*pIter);
}
// -----------------------------------------------------------------------------
uno::Sequence< uno::Any > SAL_CALL OStyle::getPropertyDefaults( const uno::Sequence< ::rtl::OUString >& aPropertyNames ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    uno::Sequence< uno::Any > aRet(aPropertyNames.getLength());
    const ::rtl::OUString* pIter = aPropertyNames.getConstArray();
    const ::rtl::OUString* pEnd	  = pIter + aPropertyNames.getLength();
    for(sal_Int32 i = 0;pIter != pEnd;++pIter,++i)
        aRet[i] = getPropertyDefault(*pIter);
    return aRet;
}
// -----------------------------------------------------------------------------
struct OReportDefinitionImpl
{
    uno::WeakReference< uno::XInterface >	                m_xParent;
    ::cppu::OInterfaceContainerHelper			            m_aStorageChangeListeners;
    ::cppu::OInterfaceContainerHelper			            m_aCloseListener;
    ::cppu::OInterfaceContainerHelper			            m_aModifyListeners;
    ::cppu::OInterfaceContainerHelper			            m_aDocEventListeners;
    ::std::vector< uno::Reference< frame::XController> >    m_aControllers;
    uno::Sequence< ::rtl::OUString > 						m_aMasterFields;
    uno::Sequence< ::rtl::OUString > 						m_aDetailFields;
    uno::Sequence< beans::PropertyValue >	                m_aArgs;
    
    uno::Reference< report::XGroups >		                m_xGroups;
    uno::Reference< report::XSection>		                m_xReportHeader;
    uno::Reference< report::XSection>		                m_xReportFooter;
    uno::Reference< report::XSection>		                m_xPageHeader;
    uno::Reference< report::XSection>		                m_xPageFooter;
    uno::Reference< report::XSection>		                m_xDetail;
    uno::Reference< embed::XStorage >		                m_xStorage;
    uno::Reference< frame::XController >	                m_xCurrentController;
    uno::Reference< container::XIndexAccess >               m_xViewData;
    uno::Reference< container::XNameAccess >                m_xStyles;
    uno::Reference< report::XFunctions >                    m_xFunctions;
    uno::Reference< ui::XUIConfigurationManager>            m_xUIConfigurationManager;
    uno::Reference< util::XNumberFormatsSupplier>           m_xNumberFormatsSupplier;

    ::boost::shared_ptr<rptui::OReportModel>                m_pReportModel;
    ::rtl::OUString 										m_sCaption;
    ::rtl::OUString 										m_sCommand;
    ::rtl::OUString 										m_sFilter;
    ::rtl::OUString 										m_sMimeType;
    ::rtl::OUString 										m_sIdentifier;
    awt::Size												m_aVisualAreaSize;
    ::sal_Int64												m_nAspect;		
    ::sal_Int16 											m_nGroupKeepTogether;
    ::sal_Int16 											m_nPageHeaderOption;
    ::sal_Int16 											m_nPageFooterOption;
    ::sal_Int32 											m_nCommandType;
    sal_Bool												m_bControllersLocked;
    sal_Bool												m_bModified;
    sal_Bool												m_bEscapeProcessing;
    OReportDefinitionImpl(::osl::Mutex& _aMutex)
    :m_aStorageChangeListeners(_aMutex)
    ,m_aCloseListener(_aMutex)
    ,m_aModifyListeners(_aMutex)
    ,m_aDocEventListeners(_aMutex)
    ,m_sMimeType(MIMETYPE_OASIS_OPENDOCUMENT_TEXT)
    ,m_sIdentifier(SERVICE_REPORTDEFINITION)
    ,m_nGroupKeepTogether(0)
    ,m_nPageHeaderOption(0)
    ,m_nPageFooterOption(0)
    ,m_nCommandType(sdb::CommandType::TABLE)
    ,m_bControllersLocked(sal_False)
    ,m_bModified(sal_False)
    ,m_bEscapeProcessing(sal_True)
    {}

    OReportDefinitionImpl(::osl::Mutex& _aMutex,const OReportDefinitionImpl& _aCopy)
    :m_aStorageChangeListeners(_aMutex)
    ,m_aCloseListener(_aMutex)
    ,m_aModifyListeners(_aMutex)
    ,m_aDocEventListeners(_aMutex)
    ,m_sMimeType(_aCopy.m_sMimeType)
    ,m_sIdentifier(_aCopy.m_sIdentifier)
    ,m_nGroupKeepTogether(_aCopy.m_nGroupKeepTogether)
    ,m_nPageHeaderOption(_aCopy.m_nPageHeaderOption)
    ,m_nPageFooterOption(_aCopy.m_nPageFooterOption)
    ,m_nCommandType(_aCopy.m_nCommandType)
    ,m_bControllersLocked(_aCopy.m_bControllersLocked)
    ,m_bModified(_aCopy.m_bModified)
    ,m_bEscapeProcessing(_aCopy.m_bEscapeProcessing)
    {}
};

DBG_NAME( rpt_OReportDefinition )
// -----------------------------------------------------------------------------
OReportDefinition::OReportDefinition(uno::Reference< uno::XComponentContext > const & _xContext)
: ReportDefinitionBase(m_aMutex)
,ReportDefinitionPropertySet(_xContext,static_cast< Implements >(IMPLEMENTS_PROPERTY_SET),uno::Sequence< ::rtl::OUString >())
,m_aProps(new OReportComponentProperties(_xContext))
,m_pImpl(new OReportDefinitionImpl(m_aMutex))
{
    DBG_CTOR( rpt_OReportDefinition,NULL);
    m_aProps->m_sName  = RPT_RESSTRING(RID_STR_REPORT,m_aProps->m_xContext->getServiceManager());
    osl_incrementInterlockedCount(&m_refCount);
    {
        init();
        m_pImpl->m_xGroups = new OGroups(this,m_aProps->m_xContext);
        m_pImpl->m_xDetail = new OSection(this,m_aProps->m_xContext);
        m_pImpl->m_xDetail->setName(RPT_RESSTRING(RID_STR_DETAIL,m_aProps->m_xContext->getServiceManager()));
    }
    osl_decrementInterlockedCount( &m_refCount );
}
// -----------------------------------------------------------------------------
OReportDefinition::OReportDefinition(uno::Reference< uno::XComponentContext > const & _xContext
                                     ,const uno::Reference< lang::XMultiServiceFactory>& _xFactory
                                     ,uno::Reference< drawing::XShape >& _xShape)
: ReportDefinitionBase(m_aMutex)
,ReportDefinitionPropertySet(_xContext,static_cast< Implements >(IMPLEMENTS_PROPERTY_SET),uno::Sequence< ::rtl::OUString >())
,m_aProps(new OReportComponentProperties(_xContext))
,m_pImpl(new OReportDefinitionImpl(m_aMutex))
{
    DBG_CTOR( rpt_OReportDefinition,NULL);
    m_aProps->m_sName  = RPT_RESSTRING(RID_STR_REPORT,m_aProps->m_xContext->getServiceManager());
    m_aProps->m_xFactory = _xFactory;
    osl_incrementInterlockedCount(&m_refCount);
    {
        m_aProps->setShape(_xShape,this,m_refCount);
        init();
        m_pImpl->m_xGroups = new OGroups(this,m_aProps->m_xContext);
        m_pImpl->m_xDetail = new OSection(this,m_aProps->m_xContext);
        m_pImpl->m_xDetail->setName(RPT_RESSTRING(RID_STR_DETAIL,m_aProps->m_xContext->getServiceManager()));
    }
    osl_decrementInterlockedCount( &m_refCount );
}
// -----------------------------------------------------------------------------
OReportDefinition::OReportDefinition(const OReportDefinition& _rCopy)
: cppu::BaseMutex()
,ReportDefinitionBase(m_aMutex)
,ReportDefinitionPropertySet(_rCopy.m_aProps->m_xContext,static_cast< Implements >(IMPLEMENTS_PROPERTY_SET),uno::Sequence< ::rtl::OUString >())
,m_aProps(new OReportComponentProperties(*_rCopy.m_aProps))
,m_pImpl(new OReportDefinitionImpl(m_aMutex,*_rCopy.m_pImpl))
{
    DBG_CTOR( rpt_OReportDefinition,NULL);
    osl_incrementInterlockedCount(&m_refCount);
    {
        init();
        OGroups* pGroups = new OGroups(this,m_aProps->m_xContext);
        m_pImpl->m_xGroups = pGroups;
        pGroups->copyGroups(_rCopy.m_pImpl->m_xGroups);
        m_pImpl->m_xDetail = new OSection(this,m_aProps->m_xContext);
        OSection::lcl_copySection(_rCopy.m_pImpl->m_xDetail,m_pImpl->m_xDetail);

        setPageHeaderOn(_rCopy.m_pImpl->m_xPageHeader.is());
        setPageFooterOn(_rCopy.m_pImpl->m_xPageFooter.is());
        setReportHeaderOn(_rCopy.m_pImpl->m_xReportHeader.is());
        setReportFooterOn(_rCopy.m_pImpl->m_xReportFooter.is());
        OSection::lcl_copySection(_rCopy.m_pImpl->m_xPageHeader,m_pImpl->m_xPageHeader);
        OSection::lcl_copySection(_rCopy.m_pImpl->m_xPageFooter,m_pImpl->m_xPageFooter);
        OSection::lcl_copySection(_rCopy.m_pImpl->m_xReportHeader,m_pImpl->m_xReportHeader);
        OSection::lcl_copySection(_rCopy.m_pImpl->m_xReportFooter,m_pImpl->m_xReportFooter);
    }
    osl_decrementInterlockedCount( &m_refCount );
}
// -----------------------------------------------------------------------------
OReportDefinition::~OReportDefinition()
{
    DBG_DTOR( rpt_OReportDefinition,NULL);
    if ( !ReportDefinitionBase::rBHelper.bInDispose && !ReportDefinitionBase::rBHelper.bDisposed )
    {
        acquire();
        dispose();
    }
}
// -----------------------------------------------------------------------------
IMPLEMENT_FORWARD_REFCOUNT( OReportDefinition, ReportDefinitionBase )
//IMPLEMENT_FORWARD_XINTERFACE2(OReportDefinition,ReportDefinitionBase,ReportDefinitionPropertySet)
void OReportDefinition::init()
{
    try
    {
        m_pImpl->m_pReportModel.reset(new OReportModel());
        m_pImpl->m_pReportModel->GetItemPool().FreezeIdRanges();
        m_pImpl->m_pReportModel->SetScaleUnit( MAP_100TH_MM );
        SdrLayerAdmin& rAdmin = m_pImpl->m_pReportModel->GetLayerAdmin();
        rAdmin.NewStandardLayer();
        rAdmin.NewLayer( UniString::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM( "HiddenLayer" ) ) );
        m_pImpl->m_xFunctions = new OFunctions(this,m_aProps->m_xContext);
    }
    catch(uno::Exception)
    {
        OSL_ENSURE(0,"Error!");
    }
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::dispose() throw(uno::RuntimeException) 
{
    ReportDefinitionPropertySet::dispose();
    cppu::WeakComponentImplHelperBase::dispose();
    m_aProps->dispose(m_refCount);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::disposing()
{
    m_pImpl->m_aControllers.clear();
    uno::Reference< frame::XModel > xHoldAlive( this );
    {
        notifyEvent(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OnUnload")));

        lang::EventObject aDisposeEvent( static_cast< ::cppu::OWeakObject* >( this ) );
        m_pImpl->m_aModifyListeners.disposeAndClear( aDisposeEvent );
        m_pImpl->m_aCloseListener.disposeAndClear( aDisposeEvent );
        m_pImpl->m_aDocEventListeners.disposeAndClear( aDisposeEvent );
        m_pImpl->m_aStorageChangeListeners.disposeAndClear( aDisposeEvent );

        ::comphelper::disposeComponent(m_pImpl->m_xGroups);
        ::comphelper::disposeComponent(m_pImpl->m_xReportHeader);
        ::comphelper::disposeComponent(m_pImpl->m_xReportFooter);
        ::comphelper::disposeComponent(m_pImpl->m_xPageHeader);
        ::comphelper::disposeComponent(m_pImpl->m_xPageFooter);
        ::comphelper::disposeComponent(m_pImpl->m_xDetail);
        ::comphelper::disposeComponent(m_pImpl->m_xFunctions);
        //::comphelper::disposeComponent(m_pImpl->m_xStorage);
            // don't dispose, this currently is the task of either the ref count going to
            // 0, or of the embedded object (if we're embedded, which is the only possible
            // case so far)
            // #i78366# / 2007-06-18 / frank.schoenheit@sun.com
        m_pImpl->m_xStorage.clear();
        m_pImpl->m_xViewData.clear();
        m_pImpl->m_xCurrentController.clear();
        m_pImpl->m_xNumberFormatsSupplier.clear();
        m_pImpl->m_xStyles.clear();
        m_pImpl->m_xUIConfigurationManager.clear();
        m_pImpl->m_pReportModel.reset();
        m_pImpl->m_aArgs.realloc(0);
    }
}
// -----------------------------------------------------------------------------
::rtl::OUString OReportDefinition::getImplementationName_Static(  ) throw(uno::RuntimeException)
{
    return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.report.OReportDefinition"));
}

//--------------------------------------------------------------------------
::rtl::OUString SAL_CALL OReportDefinition::getImplementationName(  ) throw(uno::RuntimeException)
{
    return getImplementationName_Static();
}
//--------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > OReportDefinition::getSupportedServiceNames_Static(  ) throw(uno::RuntimeException)
{
    uno::Sequence< ::rtl::OUString > aServices(1);
    aServices.getArray()[0] = SERVICE_REPORTDEFINITION;
    
    return aServices;
}
// --------------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getSupportedServiceNames(  ) throw(uno::RuntimeException)
{
    // first collect the services which are supported by our aggregate
    uno::Sequence< ::rtl::OUString > aSupported;
    if ( m_aProps->m_xServiceInfo.is() )
        aSupported = m_aProps->m_xServiceInfo->getSupportedServiceNames();

    // append our own service, if necessary
    if ( 0 == ::comphelper::findValue( aSupported, SERVICE_REPORTDEFINITION, sal_True ).getLength() )
    {
        sal_Int32 nLen = aSupported.getLength();
        aSupported.realloc( nLen + 1 );
        aSupported[ nLen ] = SERVICE_REPORTDEFINITION;
    }

    // outta here
    return aSupported;
}

// --------------------------------------------------------------------------------
sal_Bool SAL_CALL OReportDefinition::supportsService( const ::rtl::OUString& _rServiceName ) throw(uno::RuntimeException)
{
    return ::comphelper::findValue( getSupportedServiceNames(), _rServiceName, sal_True ).getLength() != 0;
}

// --------------------------------------------------------------------------------
uno::Any SAL_CALL OReportDefinition::queryInterface( const uno::Type& _rType ) throw (uno::RuntimeException)
{
    uno::Any aReturn = ReportDefinitionBase::queryInterface(_rType);
    if ( !aReturn.hasValue() )
        aReturn = ReportDefinitionPropertySet::queryInterface(_rType);

    return aReturn.hasValue() ? aReturn : (m_aProps->m_xProxy.is() ? m_aProps->m_xProxy->queryAggregation(_rType) : aReturn);
}
// --------------------------------------------------------------------------------
uno::Sequence< uno::Type > SAL_CALL OReportDefinition::getTypes(  ) throw (uno::RuntimeException)
{
    if ( m_aProps->m_xTypeProvider.is() )
        return ::comphelper::concatSequences(
            ReportDefinitionBase::getTypes(),
            m_aProps->m_xTypeProvider->getTypes()
        );
    return ReportDefinitionBase::getTypes();
}
//------------------------------------------------------------------------------
uno::Reference< uno::XInterface > OReportDefinition::create(uno::Reference< uno::XComponentContext > const & xContext)
{
    return *(new OReportDefinition(xContext));
}

// -----------------------------------------------------------------------------
// XReportDefinition
::rtl::OUString SAL_CALL OReportDefinition::getCaption() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_sCaption;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setCaption( const ::rtl::OUString& _caption ) throw (uno::RuntimeException)
{
    set(PROPERTY_CAPTION,_caption,m_pImpl->m_sCaption);
}
// -----------------------------------------------------------------------------
::sal_Int16 SAL_CALL OReportDefinition::getGroupKeepTogether() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_nGroupKeepTogether;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setGroupKeepTogether( ::sal_Int16 _groupkeeptogether ) throw (uno::RuntimeException)
{
    if ( _groupkeeptogether < report::GroupKeepTogether::PER_PAGE || _groupkeeptogether > report::GroupKeepTogether::PER_COLUMN )
        throwIllegallArgumentException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com::sun::star::report::GroupKeepTogether"))
                        ,*this
                        ,1
                        ,m_aProps->m_xContext);
    set(PROPERTY_GROUPKEEPTOGETHER,_groupkeeptogether,m_pImpl->m_nGroupKeepTogether);
}
// -----------------------------------------------------------------------------
::sal_Int16 SAL_CALL OReportDefinition::getPageHeaderOption() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_nPageHeaderOption;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPageHeaderOption( ::sal_Int16 _pageheaderoption ) throw (uno::RuntimeException)
{
    if ( _pageheaderoption < report::ReportPrintOption::ALL_PAGES || _pageheaderoption > report::ReportPrintOption::NOT_WITH_REPORT_HEADER_FOOTER )
        throwIllegallArgumentException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com::sun::star::report::ReportPrintOption"))
                        ,*this
                        ,1
                        ,m_aProps->m_xContext);
    set(PROPERTY_PAGEHEADEROPTION,_pageheaderoption,m_pImpl->m_nPageHeaderOption);
}
// -----------------------------------------------------------------------------
::sal_Int16 SAL_CALL OReportDefinition::getPageFooterOption() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_nPageFooterOption;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPageFooterOption( ::sal_Int16 _pagefooteroption ) throw (uno::RuntimeException)
{
    if ( _pagefooteroption < report::ReportPrintOption::ALL_PAGES || _pagefooteroption > report::ReportPrintOption::NOT_WITH_REPORT_HEADER_FOOTER )
        throwIllegallArgumentException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com::sun::star::report::ReportPrintOption"))
                        ,*this
                        ,1
                        ,m_aProps->m_xContext);
    set(PROPERTY_PAGEFOOTEROPTION,_pagefooteroption,m_pImpl->m_nPageFooterOption);
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getMasterFields() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_aMasterFields;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setMasterFields( const uno::Sequence< ::rtl::OUString >& _masterfields ) throw (uno::RuntimeException)
{
    set(PROPERTY_MASTERFIELDS,_masterfields,m_pImpl->m_aMasterFields);
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getDetailFields() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_aDetailFields;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setDetailFields( const uno::Sequence< ::rtl::OUString >& _detailfields ) throw (uno::RuntimeException)
{
    set(PROPERTY_DETAILFIELDS,_detailfields,m_pImpl->m_aDetailFields);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL OReportDefinition::getCommand() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_sCommand;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setCommand( const ::rtl::OUString& _command ) throw (uno::RuntimeException)
{
    set(PROPERTY_COMMAND,_command,m_pImpl->m_sCommand);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getCommandType() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_nCommandType;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setCommandType( ::sal_Int32 _commandtype ) throw (uno::RuntimeException)
{
    if ( _commandtype < sdb::CommandType::TABLE || _commandtype > sdb::CommandType::COMMAND )
        throwIllegallArgumentException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com::sun::star::sdb::CommandType"))
                        ,*this
                        ,1
                        ,m_aProps->m_xContext);
    set(PROPERTY_COMMANDTYPE,_commandtype,m_pImpl->m_nCommandType);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL OReportDefinition::getFilter() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_sFilter;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setFilter( const ::rtl::OUString& _filter ) throw (uno::RuntimeException)
{
    set(PROPERTY_FILTER,_filter,m_pImpl->m_sFilter);
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getEscapeProcessing() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_bEscapeProcessing;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setEscapeProcessing( ::sal_Bool _escapeprocessing ) throw (uno::RuntimeException)
{
    set(PROPERTY_ESCAPEPROCESSING,_escapeprocessing,m_pImpl->m_bEscapeProcessing);
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getReportHeaderOn() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xReportHeader.is();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setReportHeaderOn( ::sal_Bool _reportheaderon ) throw (uno::RuntimeException)
{
    if ( _reportheaderon != m_pImpl->m_xReportHeader.is() )
    {
        setSection(PROPERTY_REPORTHEADERON,_reportheaderon,RPT_RESSTRING(RID_STR_REPORT_HEADER,m_aProps->m_xContext->getServiceManager()),m_pImpl->m_xReportHeader);
    }
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getReportFooterOn() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xReportFooter.is();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setReportFooterOn( ::sal_Bool _reportfooteron ) throw (uno::RuntimeException)
{
    if ( _reportfooteron != m_pImpl->m_xReportFooter.is() )
    {
        setSection(PROPERTY_REPORTFOOTERON,_reportfooteron,RPT_RESSTRING(RID_STR_REPORT_FOOTER,m_aProps->m_xContext->getServiceManager()),m_pImpl->m_xReportFooter);
    }
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getPageHeaderOn() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xPageHeader.is();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPageHeaderOn( ::sal_Bool _pageheaderon ) throw (uno::RuntimeException)
{
    if ( _pageheaderon != m_pImpl->m_xPageHeader.is() )
    {
        setSection(PROPERTY_PAGEHEADERON,_pageheaderon,RPT_RESSTRING(RID_STR_PAGE_HEADER,m_aProps->m_xContext->getServiceManager()),m_pImpl->m_xPageHeader);
    }
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getPageFooterOn() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xPageFooter.is();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPageFooterOn( ::sal_Bool _pagefooteron ) throw (uno::RuntimeException)
{
    if ( _pagefooteron != m_pImpl->m_xPageFooter.is() )
    {
        setSection(PROPERTY_PAGEFOOTERON,_pagefooteron,RPT_RESSTRING(RID_STR_PAGE_FOOTER,m_aProps->m_xContext->getServiceManager()),m_pImpl->m_xPageFooter);
    }
}
// -----------------------------------------------------------------------------
uno::Reference< report::XGroups > SAL_CALL OReportDefinition::getGroups() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xGroups;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getReportHeader() throw (container::NoSuchElementException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( !m_pImpl->m_xReportHeader.is() )
        throw container::NoSuchElementException();
    return m_pImpl->m_xReportHeader;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getPageHeader() throw (container::NoSuchElementException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( !m_pImpl->m_xPageHeader.is() )
        throw container::NoSuchElementException();
    return m_pImpl->m_xPageHeader;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getDetail() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_pImpl->m_xDetail;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getPageFooter() throw (container::NoSuchElementException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( !m_pImpl->m_xPageFooter.is() )
        throw container::NoSuchElementException();
    return m_pImpl->m_xPageFooter;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getReportFooter() throw (container::NoSuchElementException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( !m_pImpl->m_xReportFooter.is() )
        throw container::NoSuchElementException();
    return m_pImpl->m_xReportFooter;
}
//------------------------------------------------------------------------------
uno::Reference< document::XEventBroadcaster > SAL_CALL OReportDefinition::getEventBroadcaster(  ) throw (lang::DisposedException, uno::Exception, uno::RuntimeException)
{
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return this;
}
//------------------------------------------------------------------------------
// XReportComponent
::rtl::OUString SAL_CALL OReportDefinition::getName() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aProps->m_sName;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setName( const ::rtl::OUString& _name ) throw (uno::RuntimeException,beans::PropertyVetoException)
{
    set(PROPERTY_NAME,_name,m_aProps->m_sName);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getHeight() throw (uno::RuntimeException)
{
    return getSize().Height;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setHeight( ::sal_Int32 _height ) throw (uno::RuntimeException)
{
    awt::Size aSize = getSize();
    aSize.Height = _height;
    setSize(aSize);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getPositionX() throw (uno::RuntimeException)
{
    return getPosition().X;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPositionX( ::sal_Int32 _positionx ) throw (uno::RuntimeException)
{
    awt::Point aPos = getPosition();
    aPos.X = _positionx;
    setPosition(aPos);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getPositionY() throw (uno::RuntimeException)
{
    return getPosition().Y;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPositionY( ::sal_Int32 _positiony ) throw (uno::RuntimeException)
{
    awt::Point aPos = getPosition();
    aPos.Y = _positiony;
    setPosition(aPos);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getWidth() throw (uno::RuntimeException)
{
    return getSize().Width;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setWidth( ::sal_Int32 _width ) throw (uno::RuntimeException)
{
    awt::Size aSize = getSize();
    aSize.Width = _width;
    setSize(aSize);
}
// -----------------------------------------------------------------------------
::sal_Int16  SAL_CALL OReportDefinition::getControlBorder() throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aProps->m_nBorder;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setControlBorder( ::sal_Int16 _border ) throw (lang::IllegalArgumentException, beans::UnknownPropertyException, uno::RuntimeException)
{
    set(PROPERTY_CONTROLBORDER,_border,m_aProps->m_nBorder);
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getControlBorderColor() throw (beans::UnknownPropertyException,uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aProps->m_nBorderColor;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setControlBorderColor( ::sal_Int32 _bordercolor ) throw (beans::UnknownPropertyException,lang::IllegalArgumentException,uno::RuntimeException)
{
    set(PROPERTY_CONTROLBORDERCOLOR,_bordercolor,m_aProps->m_nBorderColor);
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::getPrintRepeatedValues() throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aProps->m_bPrintRepeatedValues;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPrintRepeatedValues( ::sal_Bool _printrepeatedvalues ) throw (beans::UnknownPropertyException, uno::RuntimeException)
{
    set(PROPERTY_PRINTREPEATEDVALUES,_printrepeatedvalues,m_aProps->m_bPrintRepeatedValues);
}
// -----------------------------------------------------------------------------
uno::Reference< report::XSection > SAL_CALL OReportDefinition::getSection() throw (uno::RuntimeException)
{
    uno::Reference< container::XChild > xParent(getParent(  ),uno::UNO_QUERY);
    return lcl_getSection(xParent);
}
// -----------------------------------------------------------------------------
uno::Reference< beans::XPropertySetInfo > SAL_CALL OReportDefinition::getPropertySetInfo(  ) throw(uno::RuntimeException)
{
    return ReportDefinitionPropertySet::getPropertySetInfo();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPropertyValue( const ::rtl::OUString& aPropertyName, const uno::Any& aValue ) throw (beans::UnknownPropertyException, beans::PropertyVetoException, lang::IllegalArgumentException, lang::WrappedTargetException, uno::RuntimeException)
{
    ReportDefinitionPropertySet::setPropertyValue( aPropertyName, aValue );
}
// -----------------------------------------------------------------------------
uno::Any SAL_CALL OReportDefinition::getPropertyValue( const ::rtl::OUString& PropertyName ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    return ReportDefinitionPropertySet::getPropertyValue( PropertyName);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::addPropertyChangeListener( const ::rtl::OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& xListener ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    ReportDefinitionPropertySet::addPropertyChangeListener( aPropertyName, xListener );
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removePropertyChangeListener( const ::rtl::OUString& aPropertyName, const uno::Reference< beans::XPropertyChangeListener >& aListener ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    ReportDefinitionPropertySet::removePropertyChangeListener( aPropertyName, aListener );
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::addVetoableChangeListener( const ::rtl::OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    ReportDefinitionPropertySet::addVetoableChangeListener( PropertyName, aListener );
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removeVetoableChangeListener( const ::rtl::OUString& PropertyName, const uno::Reference< beans::XVetoableChangeListener >& aListener ) throw (beans::UnknownPropertyException, lang::WrappedTargetException, uno::RuntimeException)
{
    ReportDefinitionPropertySet::removeVetoableChangeListener( PropertyName, aListener );
}
// -----------------------------------------------------------------------------
// XChild
uno::Reference< uno::XInterface > SAL_CALL OReportDefinition::getParent(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    uno::Reference< container::XChild > xChild;
    comphelper::query_aggregation(m_aProps->m_xProxy,xChild);
    if ( xChild.is() )
        return xChild->getParent();
    return m_pImpl->m_xParent;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setParent( const uno::Reference< uno::XInterface >& Parent ) throw (lang::NoSupportException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    m_aProps->m_xParent = uno::Reference< container::XChild >(Parent,uno::UNO_QUERY);
    m_pImpl->m_xParent = Parent;
    uno::Reference< container::XChild > xChild;
    comphelper::query_aggregation(m_aProps->m_xProxy,xChild);
    if ( xChild.is() )
        xChild->setParent(Parent);
}
// -----------------------------------------------------------------------------
// XCloneable
uno::Reference< util::XCloneable > SAL_CALL OReportDefinition::createClone(  ) throw (uno::RuntimeException)
{
    OSL_ENSURE(0,"Not yet implemented correctly");
    uno::Reference< report::XReportComponent> xSource = this;
    uno::Reference< report::XReportDefinition> xSet(cloneObject(xSource,m_aProps->m_xFactory,SERVICE_REPORTDEFINITION),uno::UNO_QUERY_THROW);
    return xSet.get();
}
// -----------------------------------------------------------------------------
void OReportDefinition::setSection(	 const ::rtl::OUString& _sProperty
                            ,const sal_Bool& _bOn
                            ,const ::rtl::OUString& _sName
                            ,uno::Reference< report::XSection>& _member)
{
    BoundListeners l;
    {
        ::osl::MutexGuard aGuard(m_aMutex);
        prepareSet(_sProperty, uno::makeAny(_member), uno::makeAny(_bOn), &l);
        lcl_createSectionIfNeeded(_bOn ,this,_member,_sProperty == PROPERTY_PAGEHEADERON || _sProperty == PROPERTY_PAGEFOOTERON);
        if ( _member.is() )
            _member->setName(_sName);
    }
    l.notify();
}
// -----------------------------------------------------------------------------
// XCloseBroadcaster
void SAL_CALL OReportDefinition::addCloseListener( const uno::Reference< util::XCloseListener >& _xListener ) throw (uno::RuntimeException)
{
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( _xListener.is() )
        m_pImpl->m_aCloseListener.addInterface(_xListener);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removeCloseListener( const uno::Reference< util::XCloseListener >& _xListener ) throw (uno::RuntimeException)
{
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aCloseListener.removeInterface(_xListener);
}
// -----------------------------------------------------------------------------
// XCloseable
void SAL_CALL OReportDefinition::close( ::sal_Bool _bDeliverOwnership ) throw (util::CloseVetoException, uno::RuntimeException)
{
    vos::OGuard aSolarGuard( Application::GetSolarMutex() );

    ::osl::ResettableMutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    // notify our container listeners
    lang::EventObject aEvt( static_cast< ::cppu::OWeakObject* >( this ) );		
    aGuard.clear();
    m_pImpl->m_aCloseListener.forEach<util::XCloseListener>(
        ::boost::bind(&util::XCloseListener::queryClosing,_1,boost::cref(aEvt),boost::cref(_bDeliverOwnership)));
    aGuard.reset();
    

    ::std::vector< uno::Reference< frame::XController> > aCopy = m_pImpl->m_aControllers;
    ::std::vector< uno::Reference< frame::XController> >::iterator aIter = aCopy.begin();
    ::std::vector< uno::Reference< frame::XController> >::iterator aEnd = aCopy.end();
    for (;aIter != aEnd ; ++aIter)
    {
        if ( aIter->is() )
        {
            try
            {
                uno::Reference< util::XCloseable> xFrame( (*aIter)->getFrame(), uno::UNO_QUERY );
                if ( xFrame.is() )
                    xFrame->close( _bDeliverOwnership );
            }
            catch( const util::CloseVetoException& ) { throw; }
            catch( const uno::Exception& )
            {
                OSL_ENSURE( sal_False, "ODatabaseDocument::impl_closeControllerFrames: caught an unexpected exception!" );
            }
        }
    }
    
    aGuard.clear();
    m_pImpl->m_aCloseListener.notifyEach(&util::XCloseListener::notifyClosing,aEvt);
    aGuard.reset();
    
    dispose();
}
// -----------------------------------------------------------------------------
// XModel
::sal_Bool SAL_CALL OReportDefinition::attachResource( const ::rtl::OUString& /*_rURL*/, const uno::Sequence< beans::PropertyValue >& _aArguments ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    ::comphelper::MediaDescriptor aDescriptor( _aArguments );
    fillArgs(aDescriptor);
    return sal_True;
}
// -----------------------------------------------------------------------------
void OReportDefinition::fillArgs(::comphelper::MediaDescriptor& _aDescriptor)
{
    uno::Sequence<beans::PropertyValue> aComponentData;
    aComponentData = _aDescriptor.getUnpackedValueOrDefault(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ComponentData")),aComponentData);
    if ( aComponentData.getLength() && !m_pImpl->m_xNumberFormatsSupplier.is() )
    {
        ::comphelper::SequenceAsHashMap aComponentDataMap( aComponentData );
        uno::Reference<sdbc::XConnection> xConnection;
        xConnection = aComponentDataMap.getUnpackedValueOrDefault(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("ActiveConnection")),xConnection);
        m_pImpl->m_xNumberFormatsSupplier = dbtools::getNumberFormats(xConnection);
    }
    if ( !m_pImpl->m_xNumberFormatsSupplier.is() )
    {
        m_pImpl->m_xNumberFormatsSupplier.set(
                    m_aProps->m_xContext->getServiceManager()->createInstanceWithContext(
                        ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.util.NumberFormatsSupplier")) ,m_aProps->m_xContext),
                        uno::UNO_QUERY_THROW
                );
    }
    lcl_stripLoadArguments( _aDescriptor, m_pImpl->m_aArgs );
    ::rtl::OUString sCaption;
    sCaption = _aDescriptor.getUnpackedValueOrDefault(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("DocumentTitle")),sCaption);
    setCaption(sCaption);
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL OReportDefinition::getURL(  ) throw (uno::RuntimeException)
{
    return ::rtl::OUString();
}
// -----------------------------------------------------------------------------
uno::Sequence< beans::PropertyValue > SAL_CALL OReportDefinition::getArgs(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_aArgs;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::connectController( const uno::Reference< frame::XController >& _xController ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aControllers.push_back(_xController);
    sal_Int32 nCount;
    if ( _xController.is() && m_pImpl->m_xViewData.is() && ( nCount = m_pImpl->m_xViewData->getCount()) != 0)
    {
        _xController->restoreViewData(m_pImpl->m_xViewData->getByIndex(nCount - 1));
    }
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::disconnectController( const uno::Reference< frame::XController >& _xController ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    ::std::vector< uno::Reference< frame::XController> >::iterator aFind = ::std::find(m_pImpl->m_aControllers.begin(),m_pImpl->m_aControllers.end(),_xController);
    if ( aFind != m_pImpl->m_aControllers.end() )
        m_pImpl->m_aControllers.erase(aFind);
    if ( m_pImpl->m_xCurrentController == _xController )
        m_pImpl->m_xCurrentController.clear();
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::lockControllers(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_bControllersLocked = sal_True;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::unlockControllers(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_bControllersLocked = sal_False;
}
// -----------------------------------------------------------------------------
::sal_Bool SAL_CALL OReportDefinition::hasControllersLocked(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_bControllersLocked;
}
// -----------------------------------------------------------------------------
uno::Reference< frame::XController > SAL_CALL OReportDefinition::getCurrentController(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_xCurrentController;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setCurrentController( const uno::Reference< frame::XController >& _xController ) throw (container::NoSuchElementException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( ::std::find(m_pImpl->m_aControllers.begin(),m_pImpl->m_aControllers.end(),_xController) == m_pImpl->m_aControllers.end() )
        throw container::NoSuchElementException();
    m_pImpl->m_xCurrentController = _xController;
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > SAL_CALL OReportDefinition::getCurrentSelection(  ) throw (uno::RuntimeException)
{
    return uno::Reference< uno::XInterface >();
}
// -----------------------------------------------------------------------------

// XStorageBasedDocument
void SAL_CALL OReportDefinition::loadFromStorage( const uno::Reference< embed::XStorage >& _xStorageToLoadFrom
                                                 , const uno::Sequence< beans::PropertyValue >& _aMediaDescriptor ) throw (lang::IllegalArgumentException, frame::DoubleInitializationException, io::IOException, uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);

    m_pImpl->m_xStorage = _xStorageToLoadFrom;

    ::comphelper::MediaDescriptor aDescriptor( _aMediaDescriptor );
    fillArgs(aDescriptor);
    aDescriptor.createItemIfMissing(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Storage")),uno::makeAny(_xStorageToLoadFrom));
    
    uno::Sequence< uno::Any > aDelegatorArguments(_aMediaDescriptor.getLength());
    uno::Any* pIter = aDelegatorArguments.getArray();
    uno::Any* pEnd  = pIter + aDelegatorArguments.getLength();
    for(sal_Int32 i = 0;pIter != pEnd;++pIter,++i)
    {
        *pIter <<= _aMediaDescriptor[i];
    }
    sal_Int32 nPos = aDelegatorArguments.getLength();
    aDelegatorArguments.realloc(nPos+1);
    beans::PropertyValue aPropVal;
    aPropVal.Name = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Storage"));
    aPropVal.Value <<= _xStorageToLoadFrom;
    aDelegatorArguments[nPos] <<= aPropVal;

    uno::Reference< document::XFilter > xFilter(
        m_aProps->m_xContext->getServiceManager()->createInstanceWithArgumentsAndContext(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.comp.report.OReportFilter")),aDelegatorArguments,m_aProps->m_xContext),
        uno::UNO_QUERY_THROW );

    uno::Reference< document::XImporter> xImporter(xFilter,uno::UNO_QUERY_THROW);
    uno::Reference<XComponent> xComponent(static_cast<OWeakObject*>(this),uno::UNO_QUERY);
    xImporter->setTargetDocument(xComponent);
    
    ::comphelper::MediaDescriptor aTemp;
    aTemp << aDelegatorArguments;
    xFilter->filter(aTemp.getAsConstPropertyValueList());

    lcl_setModelReadOnly(m_pImpl->m_xStorage,m_pImpl->m_pReportModel);
    //LLA: if read only, try to load writer
    // sal_Bool bIsReadOnly = aTemp.getUnpackedValueOrDefault(MediaDescriptor::PROP_READONLY(), sal_False); 
    // if (bIsReadOnly)
    // {
    //     // try to open the writer
    //     bIsReadOnly = sal_True;
    // }
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::storeToStorage( const uno::Reference< embed::XStorage >& _xStorageToSaveTo, const uno::Sequence< beans::PropertyValue >& _aMediaDescriptor ) throw (lang::IllegalArgumentException, io::IOException, uno::Exception, uno::RuntimeException)
{
    if ( !_xStorageToSaveTo.is() )
        throw lang::IllegalArgumentException(RPT_RESSTRING(RID_STR_ARGUMENT_IS_NULL,m_aProps->m_xContext->getServiceManager()),*this,1);

    vos::OGuard aSolarGuard( Application::GetSolarMutex() );
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    // create XStatusIndicator
    uno::Reference<task::XStatusIndicator> xStatusIndicator;
    uno::Sequence< uno::Any > aDelegatorArguments;
    ::comphelper::MediaDescriptor aDescriptor( _aMediaDescriptor );
    lcl_extractAndStartStatusIndicator( aDescriptor, xStatusIndicator, aDelegatorArguments );

    // properties
    uno::Sequence < beans::PropertyValue > aProps;

    // export sub streams for package, else full stream into a file
    sal_Bool bWarn = sal_False, bErr = sal_False;
    ::rtl::OUString sWarnFile, sErrFile;

    uno::Reference< beans::XPropertySet> xProp(_xStorageToSaveTo,uno::UNO_QUERY);
    if ( xProp.is() )
    {
        static const ::rtl::OUString sPropName(RTL_CONSTASCII_USTRINGPARAM("MediaType"));
        ::rtl::OUString sOldMediaType;
        xProp->getPropertyValue(sPropName) >>= sOldMediaType;
        if ( !xProp->getPropertyValue(sPropName).hasValue() || !sOldMediaType.getLength() )
            xProp->setPropertyValue( sPropName, uno::makeAny(MIMETYPE_OASIS_OPENDOCUMENT_REPORT) );
    }

    /** property map for export info set */
    comphelper::PropertyMapEntry aExportInfoMap[] =
    {
        { MAP_LEN( "UsePrettyPrinting" ), 0, &::getCppuType((sal_Bool*)0), beans::PropertyAttribute::MAYBEVOID, 0},
        { NULL, 0, 0, NULL, 0, 0 }
    };
    uno::Reference< beans::XPropertySet > xInfoSet( comphelper::GenericPropertySet_CreateInstance( new comphelper::PropertySetInfo( aExportInfoMap ) ) );

    SvtSaveOptions aSaveOpt;
    xInfoSet->setPropertyValue(rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("UsePrettyPrinting")), uno::makeAny(aSaveOpt.IsPrettyPrinting()));
    sal_Int32 nArgsLen = aDelegatorArguments.getLength();
    aDelegatorArguments.realloc(nArgsLen+1);
    aDelegatorArguments[nArgsLen] <<= xInfoSet;

    uno::Reference<XComponent> xCom(static_cast<OWeakObject*>(this),uno::UNO_QUERY);
    if( !bErr )
    {
        if( !WriteThroughComponent(
            xCom, "settings.xml",
            "com.sun.star.comp.report.XMLSettingsExporter",
            aDelegatorArguments, aProps, sal_True,_xStorageToSaveTo ) )
        {
            if( !bWarn )
            {
                bWarn = sal_True;
                sWarnFile = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("settings.xml"));
            }
        }
    }

    if( !bErr )
    {
        if( !WriteThroughComponent(
            xCom, "styles.xml",
            "com.sun.star.comp.report.XMLStylesExporter",
            aDelegatorArguments, aProps, sal_True,_xStorageToSaveTo ) )
        {
            if( !bWarn )
            {
                bWarn = sal_True;
                sWarnFile = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("styles.xml"));
            }
        }
    }

    if ( !bErr )
    {
        if( !WriteThroughComponent(
                xCom, "content.xml",
                "com.sun.star.comp.report.ExportFilter",
                aDelegatorArguments, aProps, sal_True,_xStorageToSaveTo ) )
        {
            bErr = sal_True;
            sErrFile = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("content.xml"));
        }
    }


    if ( xStatusIndicator.is() )
        xStatusIndicator->end();
    if ( !bErr )
    {
        try
        {
            uno::Reference<embed::XTransactedObject> xTransact(_xStorageToSaveTo,uno::UNO_QUERY);
            if ( xTransact.is() )
                xTransact->commit();
        }
        catch(uno::Exception)
        {
            OSL_ENSURE(0,"Exception Caught: Could not commit report storage!");
            throw io::IOException();
        }
    }
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::switchToStorage( const uno::Reference< embed::XStorage >& _xStorage ) throw (lang::IllegalArgumentException, io::IOException, uno::Exception, uno::RuntimeException)
{
    if ( !_xStorage.is() )
        throw lang::IllegalArgumentException(RPT_RESSTRING(RID_STR_ARGUMENT_IS_NULL,m_aProps->m_xContext->getServiceManager()),*this,1);
    {
        ::osl::MutexGuard aGuard(m_aMutex);
        ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
        m_pImpl->m_xStorage = _xStorage;
        lcl_setModelReadOnly(m_pImpl->m_xStorage,m_pImpl->m_pReportModel);
    }
    // notify our container listeners
    m_pImpl->m_aStorageChangeListeners.forEach<document::XStorageChangeListener>(
            ::boost::bind(&document::XStorageChangeListener::notifyStorageChange,_1,boost::cref(static_cast<OWeakObject*>(this)),boost::cref(_xStorage)));
}
// -----------------------------------------------------------------------------
uno::Reference< embed::XStorage > SAL_CALL OReportDefinition::getDocumentStorage(  ) throw (io::IOException, uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_xStorage;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::addStorageChangeListener( const uno::Reference< document::XStorageChangeListener >& xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( xListener.is() )
        m_pImpl->m_aStorageChangeListeners.addInterface(xListener);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removeStorageChangeListener( const uno::Reference< document::XStorageChangeListener >& xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aStorageChangeListeners.removeInterface(xListener);
}
// -----------------------------------------------------------------------------
sal_Bool OReportDefinition::WriteThroughComponent(
    const uno::Reference<lang::XComponent> & xComponent,
    const sal_Char* pStreamName,
    const sal_Char* pServiceName,
    const uno::Sequence<uno::Any> & rArguments,
    const uno::Sequence<beans::PropertyValue> & rMediaDesc,
    sal_Bool bPlainStream
    ,const uno::Reference<embed::XStorage>& _xStorageToSaveTo)
{
    OSL_ENSURE( NULL != pStreamName, "Need stream name!" );
    OSL_ENSURE( NULL != pServiceName, "Need service name!" );
    try
    {
        uno::Reference<embed::XStorage> xMyStorage = _xStorageToSaveTo;
        // open stream
        ::rtl::OUString sStreamName = ::rtl::OUString::createFromAscii( pStreamName );
        uno::Reference<io::XStream> xStream = xMyStorage->openStreamElement( sStreamName,embed::ElementModes::READWRITE | embed::ElementModes::TRUNCATE );
        if ( !xStream.is() )
            return sal_False;
        uno::Reference<io::XOutputStream> xOutputStream = xStream->getOutputStream();
        OSL_ENSURE(xOutputStream.is(), "Can't create output stream in package!");
        if ( ! xOutputStream.is() )
            return sal_False;

        uno::Reference<beans::XPropertySet> xStreamProp(xOutputStream,uno::UNO_QUERY);
        OSL_ENSURE(xStreamProp.is(),"No valid preoperty set for the output stream!");

        uno::Reference<io::XSeekable> xSeek(xStreamProp,uno::UNO_QUERY);
        if ( xSeek.is() )
        {
            OSL_TRACE("Length of stream %i",(int)xSeek->getPosition());
            xSeek->seek(0);
        }

        ::rtl::OUString aPropName(RTL_CONSTASCII_USTRINGPARAM("MediaType"));
        ::rtl::OUString aMime( RTL_CONSTASCII_USTRINGPARAM("text/xml") );
        uno::Any aAny;
        aAny <<= aMime;
        xStreamProp->setPropertyValue( aPropName, aAny );

        if( bPlainStream )
        {
            aAny <<= sal_False; 
            xStreamProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("Compressed") ), aAny );
        }
        else
        {
            xStreamProp->setPropertyValue( ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("Encrypted") ), uno::makeAny(sal_True) );
        }


        // set buffer and create outputstream

        // write the stuff
        sal_Bool bRet = WriteThroughComponent(
            xOutputStream, xComponent,
            pServiceName, rArguments, rMediaDesc );
        // finally, commit stream.
        return bRet;
    }
    catch(const uno::Exception& e)
    {
        (void)e; // helper to know what e contains
        throw;
    }
}
// -----------------------------------------------------------------------------
sal_Bool OReportDefinition::WriteThroughComponent(
    const uno::Reference<io::XOutputStream> & xOutputStream,
    const uno::Reference<lang::XComponent> & xComponent,
    const sal_Char* pServiceName,
    const uno::Sequence<uno::Any> & rArguments,
    const uno::Sequence<beans::PropertyValue> & rMediaDesc)
{
    OSL_ENSURE( xOutputStream.is(), "I really need an output stream!" );
    OSL_ENSURE( xComponent.is(), "Need component!" );
    OSL_ENSURE( NULL != pServiceName, "Need component name!" );

    // get component
    uno::Reference< io::XActiveDataSource > xSaxWriter(
        m_aProps->m_xContext->getServiceManager()->createInstanceWithContext(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.xml.sax.Writer")),m_aProps->m_xContext),
        uno::UNO_QUERY );
    OSL_ENSURE( xSaxWriter.is(), "can't instantiate XML com.sun.star.xml.sax.Writer" );
    if(!xSaxWriter.is())
        return sal_False;

    // connect XML writer to output stream
    xSaxWriter->setOutputStream( xOutputStream );

    // prepare arguments (prepend doc handler to given arguments)
    uno::Reference<xml::sax::XDocumentHandler> xDocHandler( xSaxWriter,uno::UNO_QUERY);
    uno::Sequence<uno::Any> aArgs( 1 + rArguments.getLength() );
    aArgs[0] <<= xDocHandler;
    for(sal_Int32 i = 0; i < rArguments.getLength(); i++)
        aArgs[i+1] = rArguments[i];

    // get filter component
    uno::Reference< document::XExporter > xExporter(
        m_aProps->m_xContext->getServiceManager()->createInstanceWithArgumentsAndContext(
            ::rtl::OUString::createFromAscii(pServiceName), aArgs,m_aProps->m_xContext), uno::UNO_QUERY);
    OSL_ENSURE( xExporter.is(),
            "can't instantiate export filter component" );
    if( !xExporter.is() )
        return sal_False;

    // connect model and filter
    xExporter->setSourceDocument( xComponent );

    // filter!
    uno::Reference<document::XFilter> xFilter( xExporter, uno::UNO_QUERY );
    return xFilter->filter( rMediaDesc );
}
// -----------------------------------------------------------------------------
// XLoadable
void SAL_CALL OReportDefinition::initNew(  ) throw (frame::DoubleInitializationException, io::IOException, uno::Exception, uno::RuntimeException)
{
     setPageHeaderOn( sal_True );
     setPageFooterOn( sal_True );
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::load( const uno::Sequence< beans::PropertyValue >& /*lArguments*/ ) throw (frame::DoubleInitializationException, io::IOException, uno::Exception, uno::RuntimeException)
{
}
// -----------------------------------------------------------------------------
// XVisualObject
void SAL_CALL OReportDefinition::setVisualAreaSize( ::sal_Int64 _nAspect, const awt::Size& _aSize ) throw (lang::IllegalArgumentException, embed::WrongStateException, uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aVisualAreaSize = _aSize;
    m_pImpl->m_nAspect = _nAspect;
}
// -----------------------------------------------------------------------------
awt::Size SAL_CALL OReportDefinition::getVisualAreaSize( ::sal_Int64 /*nAspect*/ ) throw (lang::IllegalArgumentException, embed::WrongStateException, uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_aVisualAreaSize;
}
// -----------------------------------------------------------------------------
embed::VisualRepresentation SAL_CALL OReportDefinition::getPreferredVisualRepresentation( ::sal_Int64 /*nAspect*/ ) throw (lang::IllegalArgumentException, embed::WrongStateException, uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    embed::VisualRepresentation aVisualRepresentation;
    return aVisualRepresentation;
}
// -----------------------------------------------------------------------------
::sal_Int32 SAL_CALL OReportDefinition::getMapUnit( ::sal_Int64 /*nAspect*/ ) throw (uno::Exception, uno::RuntimeException)
{
    return embed::EmbedMapUnits::ONE_100TH_MM;
}
// -----------------------------------------------------------------------------
// XModifiable
::sal_Bool SAL_CALL OReportDefinition::isModified(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_bModified;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setModified( ::sal_Bool _bModified ) throw (beans::PropertyVetoException, uno::RuntimeException)
{
    ::osl::ResettableMutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_pImpl->m_pReportModel->IsReadOnly() && _bModified )
        throw beans::PropertyVetoException();
    if ( m_pImpl->m_bModified != _bModified )
    {
        m_pImpl->m_bModified = _bModified;
        lang::EventObject aEvent(*this);
        aGuard.clear();
        m_pImpl->m_aModifyListeners.notifyEach(&util::XModifyListener::modified,aEvent);
        notifyEvent(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("OnModifyChanged")));
    }
}
// -----------------------------------------------------------------------------
// XModifyBroadcaster
void SAL_CALL OReportDefinition::addModifyListener( const uno::Reference< util::XModifyListener >& _xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( _xListener.is() )
        m_pImpl->m_aModifyListeners.addInterface(_xListener);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removeModifyListener( const uno::Reference< util::XModifyListener >& _xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aModifyListeners.removeInterface(_xListener);
}
// -----------------------------------------------------------------------------
void OReportDefinition::notifyEvent(const ::rtl::OUString& _sEventName)
{
    try
    {
        ::osl::ResettableMutexGuard aGuard(m_aMutex);
        ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
        document::EventObject aEvt(*this, _sEventName);		
        aGuard.clear();
        m_pImpl->m_aDocEventListeners.notifyEach(&document::XEventListener::notifyEvent,aEvt);
    }
    catch(uno::Exception&)
    {
    }
}
// -----------------------------------------------------------------------------
// document::XEventBroadcaster
void SAL_CALL OReportDefinition::addEventListener(const uno::Reference< document::XEventListener >& _xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( _xListener.is() )
        m_pImpl->m_aDocEventListeners.addInterface(_xListener);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::removeEventListener( const uno::Reference< document::XEventListener >& _xListener ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_aDocEventListeners.removeInterface(_xListener);
}
// -----------------------------------------------------------------------------
// document::XEventListener
void SAL_CALL OReportDefinition::notifyEvent( const document::EventObject& aEvent ) throw (uno::RuntimeException)
{
    // used only to forward external events (e.g. for doc creation) from the frame loader
    // to the global event broadcaster and all other interested doc event listener.
    notifyEvent(aEvent.EventName);
}
// -----------------------------------------------------------------------------
// document::XViewDataSupplier
uno::Reference< container::XIndexAccess > SAL_CALL OReportDefinition::getViewData(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( !m_pImpl->m_xViewData.is() )
    {
        m_pImpl->m_xViewData.set(m_aProps->m_xContext->getServiceManager()->createInstanceWithContext(
                ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.document.IndexedPropertyValues")),m_aProps->m_xContext ),uno::UNO_QUERY);
        //uno::Sequence< beans::PropertyValue > aProps;
        //m_pImpl->m_xViewData->insertByIndex(m_pImpl->m_xViewData->getCount(),uno::makeAny(aProps));
        uno::Reference< container::XIndexContainer > xContainer(m_pImpl->m_xViewData,uno::UNO_QUERY);
        ::std::vector< uno::Reference< frame::XController> >::iterator aIter = m_pImpl->m_aControllers.begin();
        ::std::vector< uno::Reference< frame::XController> >::iterator aEnd = m_pImpl->m_aControllers.end();
        for (;aIter != aEnd ; ++aIter)
        {
            if ( aIter->is() )
            {
                try
                {
                    xContainer->insertByIndex(xContainer->getCount(),(*aIter)->getViewData());
                }
                catch(uno::Exception&)
                {
                }
            } // if ( aIter->is() )
        }
        
    }
    return m_pImpl->m_xViewData;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setViewData( const uno::Reference< container::XIndexAccess >& Data ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_xViewData = Data;
}
// -----------------------------------------------------------------------------
uno::Reference< report::XFunctions > SAL_CALL OReportDefinition::getFunctions() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_xFunctions;
}
// -----------------------------------------------------------------------------
uno::Reference< ui::XUIConfigurationManager > SAL_CALL OReportDefinition::getUIConfigurationManager(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);

    if ( !m_pImpl->m_xUIConfigurationManager.is() )
    {
        m_pImpl->m_xUIConfigurationManager.set(m_aProps->m_xContext->getServiceManager()->createInstanceWithContext(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.ui.UIConfigurationManager")),m_aProps->m_xContext),
            uno::UNO_QUERY);

        uno::Reference< ui::XUIConfigurationStorage > xUIConfigStorage( m_pImpl->m_xUIConfigurationManager, uno::UNO_QUERY );
        if ( xUIConfigStorage.is() )
        {
            uno::Reference< embed::XStorage > xConfigStorage;
            // initialize ui configuration manager with document substorage
            xUIConfigStorage->setStorage( xConfigStorage );
        }
    }

    return m_pImpl->m_xUIConfigurationManager;
}
// -----------------------------------------------------------------------------
uno::Reference< embed::XStorage > SAL_CALL OReportDefinition::getDocumentSubStorage( const ::rtl::OUString& aStorageName, sal_Int32 nMode ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_xStorage->openStorageElement(aStorageName, nMode);
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getDocumentSubStoragesNames(  ) throw (io::IOException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    uno::Reference<container::XNameAccess> xNameAccess(m_pImpl->m_xStorage,uno::UNO_QUERY);
    return xNameAccess.is() ? xNameAccess->getElementNames() : uno::Sequence< ::rtl::OUString >();
}
// -----------------------------------------------------------------------------
::rtl::OUString SAL_CALL OReportDefinition::getMimeType() throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_sMimeType;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setMimeType( const ::rtl::OUString& _mimetype ) throw (lang::IllegalArgumentException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    uno::Sequence< ::rtl::OUString > aList = getAvailableMimeTypes();
    const ::rtl::OUString* pEnd = aList.getConstArray()+aList.getLength();
    if ( ::std::find(aList.getConstArray(),pEnd,_mimetype) == pEnd )
        throwIllegallArgumentException(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("getAvailableMimeTypes()"))
                        ,*this
                        ,1
                        ,m_aProps->m_xContext);
    set(PROPERTY_MIMETYPE,_mimetype,m_pImpl->m_sMimeType);
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getAvailableMimeTypes(  ) throw (lang::DisposedException, uno::Exception, uno::RuntimeException)
{
    static uno::Sequence< ::rtl::OUString > s_aList;
    if ( !s_aList.hasElements() )
    {
        s_aList.realloc(2);
        s_aList[0] = MIMETYPE_OASIS_OPENDOCUMENT_TEXT;
        s_aList[1] = MIMETYPE_OASIS_OPENDOCUMENT_SPREADSHEET;
    }
    
    return s_aList;
}
// -----------------------------------------------------------------------------
// com::sun::star::XUnoTunnel
sal_Int64 SAL_CALL OReportDefinition::getSomething( const uno::Sequence< sal_Int8 >& rId ) throw(uno::RuntimeException)
{
    if (rId.getLength() == 16 && 0 == rtl_compareMemory(getUnoTunnelImplementationId().getConstArray(),  rId.getConstArray(), 16 ) )
        return reinterpret_cast<sal_Int64>(this);
    else
    {
        uno::Reference< lang::XUnoTunnel> xUnoTunnel(m_pImpl->m_xNumberFormatsSupplier,uno::UNO_QUERY);
        if ( xUnoTunnel.is() )
            return xUnoTunnel->getSomething(rId);
    }

    return 0;
}
// -----------------------------------------------------------------------------
uno::Sequence< sal_Int8 > SAL_CALL OReportDefinition::getImplementationId(  ) throw (uno::RuntimeException)
{
    return OReportDefinition::getUnoTunnelImplementationId();
}
//--------------------------------------------------------------------------
uno::Sequence< sal_Int8 > OReportDefinition::getUnoTunnelImplementationId()
{
    static ::cppu::OImplementationId * pId = 0;
    if (! pId)
    {
        ::osl::MutexGuard aGuard( ::osl::Mutex::getGlobalMutex() );
        if (! pId)
        {
            static ::cppu::OImplementationId aId;
            pId = &aId;
        }
    }
    return pId->getImplementationId();
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XComponentContext > OReportDefinition::getContext()
{ 
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_aProps->m_xContext; 
}
// -----------------------------------------------------------------------------
::boost::shared_ptr<rptui::OReportModel> OReportDefinition::getSdrModel() const
{
    return m_pImpl->m_pReportModel;
}
// -----------------------------------------------------------------------------
::boost::shared_ptr<rptui::OReportModel> OReportDefinition::getSdrModel(uno::Reference< report::XReportDefinition >& _xReportDefinition)
{
    ::boost::shared_ptr<rptui::OReportModel> pReportModel;
    uno::Reference< lang::XUnoTunnel > xUT( _xReportDefinition, uno::UNO_QUERY );
    if( xUT.is() )
        pReportModel = reinterpret_cast<OReportDefinition*>(sal::static_int_cast<sal_uIntPtr>(xUT->getSomething( OReportDefinition::getUnoTunnelImplementationId())))->getSdrModel();
    return pReportModel;
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > SAL_CALL OReportDefinition::createInstanceWithArguments( const ::rtl::OUString& aServiceSpecifier, const uno::Sequence< uno::Any >& _aArgs)
    throw( uno::Exception, uno::RuntimeException )
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);

    uno::Reference< drawing::XShape > xShape;
    const uno::Any* pIter = _aArgs.getConstArray();
    const uno::Any* pEnd	  = pIter + _aArgs.getLength();
    for(;pIter != pEnd && !xShape.is();++pIter)
        xShape.set(*pIter,uno::UNO_QUERY);

    uno::Reference< uno::XInterface > xReportComponent;
    if ( xShape.is() )
    {
        if ( aServiceSpecifier == SERVICE_FORMATTEDFIELD )
        {
            uno::Reference<report::XFormattedField> xProp = new OFormattedField(m_aProps->m_xContext,this,xShape);
            xReportComponent = xProp;
            if ( xShape.is() )
                throw uno::Exception();
            xProp->setPropertyValue( PROPERTY_FORMATSSUPPLIER, uno::makeAny(uno::Reference< util::XNumberFormatsSupplier >(*this,uno::UNO_QUERY)) );
        }
        else if ( aServiceSpecifier == SERVICE_FIXEDTEXT)
        {
            xReportComponent = static_cast<cppu::OWeakObject*>(new OFixedText(m_aProps->m_xContext,this,xShape));
            if ( xShape.is() )
                throw uno::Exception();
        }
        else if ( aServiceSpecifier == SERVICE_FIXEDLINE)
        {
            xReportComponent = static_cast<cppu::OWeakObject*>(new OFixedLine(m_aProps->m_xContext,this,xShape));
            if ( xShape.is() )
                throw uno::Exception();
        }
        else if ( aServiceSpecifier == SERVICE_IMAGECONTROL )
        {
            xReportComponent = static_cast<cppu::OWeakObject*>(new OImageControl(m_aProps->m_xContext,this,xShape));
            if ( xShape.is() )
                throw uno::Exception();
        }
        else if ( aServiceSpecifier == SERVICE_REPORTDEFINITION )
        {
            xReportComponent = static_cast<cppu::OWeakObject*>(new OReportDefinition(m_aProps->m_xContext,this,xShape));
            if ( xShape.is() )
                throw uno::Exception();
        }
        else if ( xShape.is() )
        {
            xReportComponent = static_cast<cppu::OWeakObject*>(new OShape(m_aProps->m_xContext,this,xShape));
            if ( xShape.is() )
                throw uno::Exception();
        }
    }
    return xReportComponent;
}
// -----------------------------------------------------------------------------
uno::Reference< uno::XInterface > SAL_CALL OReportDefinition::createInstance( const ::rtl::OUString& aServiceSpecifier ) throw(uno::Exception, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    uno::Reference< drawing::XShape > xShape;
    if ( aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.report.") ) == 0 )
    {
        if ( aServiceSpecifier == SERVICE_SHAPE )
            xShape.set(SvxUnoDrawMSFactory::createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.CustomShape")) ),uno::UNO_QUERY_THROW);
        else
            xShape.set(SvxUnoDrawMSFactory::createInstance( ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.ControlShape")) ),uno::UNO_QUERY_THROW);
    }
    else if ( aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.form.component.") ) == 0 )
    {
        xShape.set(m_aProps->m_xContext->getServiceManager()->createInstanceWithContext(aServiceSpecifier,m_aProps->m_xContext),uno::UNO_QUERY);
    }
    else if ( aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.style.PageStyle") ) == 0 ||
              aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.style.FrameStyle") ) == 0 ||
              aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.style.GraphicStyle") ) == 0 
              )
    {
        uno::Reference< style::XStyle> xStyle = new OStyle();
        xStyle->setName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("Default")));
        uno::Reference<beans::XPropertySet> xProp(xStyle,uno::UNO_QUERY);
        ::rtl::OUString sTray;
        xProp->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PrinterPaperTray")))>>= sTray;
        
        return xStyle.get();
    }
    else if ( aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.document.Settings") ) == 0 )
    {
        uno::Reference<beans::XPropertySet> xProp = new OStyle();
        
        return xProp.get();
    }
    else if ( aServiceSpecifier.indexOf( ::rtl::OUString::createFromAscii("com.sun.star.drawing.Defaults") ) == 0 )
    {
        uno::Reference<beans::XPropertySet> xProp = new OStyle();
        
        return xProp.get();
    }
    else
        xShape.set(SvxUnoDrawMSFactory::createInstance( aServiceSpecifier ),uno::UNO_QUERY_THROW);
    

    uno::Reference< uno::XInterface > xReturn;
    {
        uno::Sequence< uno::Any > aArgs(1);
        aArgs[0] <<= xShape;
        xShape.clear();
        xReturn = createInstanceWithArguments(aServiceSpecifier,aArgs);
    }
    return xReturn;
}
//-----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OReportDefinition::getAvailableServiceNames(void) throw( uno::RuntimeException )
{
    static const ::rtl::OUString aSvxComponentServiceNameList[] =
    {
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.form.component.FixedText")),
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.form.component.DatabaseImageControl")),
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.PageStyle")),
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.GraphicStyle")),
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.FrameStyle")),
        ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.drawing.Defaults"))
    };

    static const sal_uInt16 nSvxComponentServiceNameListCount = sizeof(aSvxComponentServiceNameList) / sizeof ( aSvxComponentServiceNameList[0] );

    uno::Sequence< ::rtl::OUString > aSeq( nSvxComponentServiceNameListCount );
    ::rtl::OUString* pStrings = aSeq.getArray();
    for( sal_uInt16 nIdx = 0; nIdx < nSvxComponentServiceNameListCount; nIdx++ )
        pStrings[nIdx] = aSvxComponentServiceNameList[nIdx];

    uno::Sequence< ::rtl::OUString > aParentSeq( SvxUnoDrawMSFactory::getAvailableServiceNames() );
    return concatServiceNames( aParentSeq, aSeq );
}
// -----------------------------------------------------------------------------
// XShape
awt::Point SAL_CALL OReportDefinition::getPosition(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_aProps->m_xShape.is() )
        return m_aProps->m_xShape->getPosition();
    return awt::Point(m_aProps->m_nPosX,m_aProps->m_nPosY);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setPosition( const awt::Point& aPosition ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_aProps->m_xShape.is() )
        m_aProps->m_xShape->setPosition(aPosition);
    set(PROPERTY_POSITIONX,aPosition.X,m_aProps->m_nPosX);
    set(PROPERTY_POSITIONY,aPosition.Y,m_aProps->m_nPosY);
}
// -----------------------------------------------------------------------------
awt::Size SAL_CALL OReportDefinition::getSize(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_aProps->m_xShape.is() )
        return m_aProps->m_xShape->getSize();
    return awt::Size(m_aProps->m_nWidth,m_aProps->m_nHeight);
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setSize( const awt::Size& aSize ) throw (beans::PropertyVetoException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_aProps->m_xShape.is() )
        m_aProps->m_xShape->setSize(aSize);
    set(PROPERTY_WIDTH,aSize.Width,m_aProps->m_nWidth);
    set(PROPERTY_HEIGHT,aSize.Height,m_aProps->m_nHeight);
}
// -----------------------------------------------------------------------------

// XShapeDescriptor
::rtl::OUString SAL_CALL OReportDefinition::getShapeType(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( m_aProps->m_xShape.is() )
        return m_aProps->m_xShape->getShapeType();
    return ::rtl::OUString();
}
// -----------------------------------------------------------------------------
typedef ::cppu::WeakImplHelper2< container::XNameContainer,
                             container::XIndexAccess
                            > TStylesBASE;
class OStylesHelper : public ::cppu::BaseMutex, public TStylesBASE
{
    typedef ::std::map< ::rtl::OUString, uno::Any  , ::comphelper::UStringMixLess> TStyleElements;
    TStyleElements                                  m_aElements;
    ::std::vector<TStyleElements::iterator>         m_aElementsPos;
    uno::Type                                       m_aType;

    OStylesHelper(const OStylesHelper&);
    void operator =(const OStylesHelper&);
protected:
    virtual ~OStylesHelper(){}
public:
    OStylesHelper(const uno::Type _aType = ::getCppuType(static_cast< uno::Reference< container::XElementAccess >* >(NULL)));

    // XNameContainer
    virtual void SAL_CALL insertByName( const ::rtl::OUString& aName, const uno::Any& aElement ) throw(lang::IllegalArgumentException, container::ElementExistException,lang::WrappedTargetException, uno::RuntimeException);
    virtual void SAL_CALL removeByName( const ::rtl::OUString& Name ) throw(container::NoSuchElementException, lang::WrappedTargetException,uno::RuntimeException);

    // XNameReplace
    virtual void SAL_CALL replaceByName( const ::rtl::OUString& aName, const uno::Any& aElement ) throw(lang::IllegalArgumentException, container::NoSuchElementException,lang::WrappedTargetException, uno::RuntimeException);

    // container::XElementAccess
    uno::Type SAL_CALL getElementType(  ) throw(uno::RuntimeException);
    sal_Bool SAL_CALL hasElements(  ) throw(uno::RuntimeException);
    // container::XIndexAccess
    sal_Int32 SAL_CALL getCount(  ) throw(uno::RuntimeException);
    uno::Any SAL_CALL getByIndex( sal_Int32 Index ) throw(lang::IndexOutOfBoundsException, lang::WrappedTargetException, uno::RuntimeException);

        // container::XNameAccess
    uno::Any SAL_CALL getByName( const ::rtl::OUString& aName ) throw(container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException);
    uno::Sequence< ::rtl::OUString > SAL_CALL getElementNames(  ) throw(uno::RuntimeException);
    sal_Bool SAL_CALL hasByName( const ::rtl::OUString& aName ) throw(uno::RuntimeException);
};

OStylesHelper::OStylesHelper(const uno::Type _aType)
: cppu::BaseMutex()
,m_aType(_aType)
{
}
// -----------------------------------------------------------------------------;
// container::XElementAccess
uno::Type SAL_CALL OStylesHelper::getElementType(  ) throw(uno::RuntimeException)
{
    return m_aType;
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OStylesHelper::hasElements(  ) throw(uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return !m_aElementsPos.empty();
}
// -----------------------------------------------------------------------------
// container::XIndexAccess
sal_Int32 SAL_CALL OStylesHelper::getCount(  ) throw(uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aElementsPos.size();
}
// -----------------------------------------------------------------------------
uno::Any SAL_CALL OStylesHelper::getByIndex( sal_Int32 Index ) throw(lang::IndexOutOfBoundsException, lang::WrappedTargetException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( Index < 0 || Index >= static_cast<sal_Int32>(m_aElementsPos.size()) )
        throw lang::IndexOutOfBoundsException();
    return uno::makeAny(m_aElementsPos[Index]->second);
}
// -----------------------------------------------------------------------------
// container::XNameAccess
uno::Any SAL_CALL OStylesHelper::getByName( const ::rtl::OUString& aName ) throw(container::NoSuchElementException, lang::WrappedTargetException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    TStyleElements::iterator aFind = m_aElements.find(aName);
    if ( aFind == m_aElements.end() )
        throw container::NoSuchElementException();
    return uno::makeAny(aFind->second);
}
// -----------------------------------------------------------------------------
uno::Sequence< ::rtl::OUString > SAL_CALL OStylesHelper::getElementNames(  ) throw(uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    uno::Sequence< ::rtl::OUString > aNameList(m_aElementsPos.size());
    
    ::rtl::OUString* pStringArray = aNameList.getArray();
    ::std::vector<TStyleElements::iterator>::const_iterator aEnd = m_aElementsPos.end();
    for(::std::vector<TStyleElements::iterator>::const_iterator aIter = m_aElementsPos.begin();         aIter != aEnd;++aIter,++pStringArray)
        *pStringArray = (*aIter)->first;
    
    return aNameList;
}
// -----------------------------------------------------------------------------
sal_Bool SAL_CALL OStylesHelper::hasByName( const ::rtl::OUString& aName ) throw(uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    return m_aElements.find(aName) != m_aElements.end();
}
// -----------------------------------------------------------------------------
// XNameContainer
void SAL_CALL OStylesHelper::insertByName( const ::rtl::OUString& aName, const uno::Any& aElement ) throw(lang::IllegalArgumentException, container::ElementExistException,lang::WrappedTargetException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    if ( m_aElements.find(aName) != m_aElements.end() )
        throw container::ElementExistException();
    
    if ( !aElement.isExtractableTo(m_aType) )
        throw lang::IllegalArgumentException();

    m_aElementsPos.push_back(m_aElements.insert(TStyleElements::value_type(aName,aElement)).first);
}
// -----------------------------------------------------------------------------
void SAL_CALL OStylesHelper::removeByName( const ::rtl::OUString& aName ) throw(container::NoSuchElementException, lang::WrappedTargetException,uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    TStyleElements::iterator aFind = m_aElements.find(aName);
    if ( aFind != m_aElements.end() )
        throw container::NoSuchElementException();
    m_aElementsPos.erase(::std::find(m_aElementsPos.begin(),m_aElementsPos.end(),aFind));
    m_aElements.erase(aFind);
}
// -----------------------------------------------------------------------------
// XNameReplace
void SAL_CALL OStylesHelper::replaceByName( const ::rtl::OUString& aName, const uno::Any& aElement ) throw(lang::IllegalArgumentException, container::NoSuchElementException,lang::WrappedTargetException, uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    TStyleElements::iterator aFind = m_aElements.find(aName);
    if ( aFind != m_aElements.end() )
        throw container::NoSuchElementException();
    if ( !aElement.isExtractableTo(m_aType) )
        throw lang::IllegalArgumentException();
    aFind->second = aElement;
}
// -----------------------------------------------------------------------------
uno::Reference< container::XNameAccess > SAL_CALL OReportDefinition::getStyleFamilies(  ) throw (uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    if ( !m_pImpl->m_xStyles.is() )
    {
        m_pImpl->m_xStyles = new OStylesHelper();
        uno::Reference< container::XNameContainer> xStyles(m_pImpl->m_xStyles,uno::UNO_QUERY);

        uno::Reference< container::XNameContainer> xPageStyles = new OStylesHelper(::getCppuType(static_cast< uno::Reference<style::XStyle>* >(NULL)));
        xStyles->insertByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("PageStyles")),uno::makeAny(xPageStyles));
        uno::Reference< style::XStyle> xPageStyle(createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.PageStyle"))),uno::UNO_QUERY);
        xPageStyles->insertByName(xPageStyle->getName(),uno::makeAny(xPageStyle));

        uno::Reference< container::XNameContainer> xFrameStyles = new OStylesHelper(::getCppuType(static_cast< uno::Reference<style::XStyle>* >(NULL)));
        xStyles->insertByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("FrameStyles")),uno::makeAny(xFrameStyles));
        uno::Reference< style::XStyle> xFrameStyle(createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.FrameStyle"))),uno::UNO_QUERY);
        xFrameStyles->insertByName(xFrameStyle->getName(),uno::makeAny(xFrameStyle));

        uno::Reference< container::XNameContainer> xGraphicStyles = new OStylesHelper(::getCppuType(static_cast< uno::Reference<style::XStyle>* >(NULL)));
        xStyles->insertByName(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("graphics")),uno::makeAny(xGraphicStyles));
        uno::Reference< style::XStyle> xGraphicStyle(createInstance(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.style.GraphicStyle"))),uno::UNO_QUERY);
        xGraphicStyles->insertByName(xGraphicStyle->getName(),uno::makeAny(xGraphicStyle));
    }
    return m_pImpl->m_xStyles;
}
::rtl::OUString SAL_CALL  OReportDefinition::getIdentifier(  ) throw (::com::sun::star::uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    return m_pImpl->m_sIdentifier;
}
// -----------------------------------------------------------------------------
void SAL_CALL OReportDefinition::setIdentifier( const ::rtl::OUString& Identifier ) throw (::com::sun::star::uno::RuntimeException)
{
    ::osl::MutexGuard aGuard(m_aMutex);
    ::connectivity::checkDisposed(ReportDefinitionBase::rBHelper.bDisposed);
    m_pImpl->m_sIdentifier = Identifier;
}
// -----------------------------------------------------------------------------
// XNumberFormatsSupplier
uno::Reference< beans::XPropertySet > SAL_CALL OReportDefinition::getNumberFormatSettings(  ) throw (uno::RuntimeException)
{
    if ( m_pImpl->m_xNumberFormatsSupplier.is() )
        return m_pImpl->m_xNumberFormatsSupplier->getNumberFormatSettings();
    return uno::Reference< beans::XPropertySet >();
}
// -----------------------------------------------------------------------------
uno::Reference< util::XNumberFormats > SAL_CALL OReportDefinition::getNumberFormats(  ) throw (uno::RuntimeException)
{
    if ( m_pImpl->m_xNumberFormatsSupplier.is() )
        return m_pImpl->m_xNumberFormatsSupplier->getNumberFormats();
    return uno::Reference< util::XNumberFormats >();
}
// -----------------------------------------------------------------------------
// =============================================================================
}// namespace reportdesign
// =============================================================================

