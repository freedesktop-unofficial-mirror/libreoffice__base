/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: TokenWriter.cxx,v $
 *
 *  $Revision: 1.35 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-30 08:51:00 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbaccess.hxx"
#ifndef DBAUI_TOKENWRITER_HXX
#include "TokenWriter.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef DBAUI_RTFREADER_HXX
#include "RtfReader.hxx"
#endif
#ifndef DBAUI_HTMLREADER_HXX
#include "HtmlReader.hxx"
#endif
#ifndef DBACCESS_SHARED_DBUSTRINGS_HRC
#include "dbustrings.hrc"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif
#ifndef _COMPHELPER_TYPES_HXX_
#include <comphelper/types.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_XCONNECTION_HPP_
#include <com/sun/star/sdbc/XConnection.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XCOLUMNSSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XColumnsSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETMETADATASUPPLIER_HPP_
#include <com/sun/star/sdbc/XResultSetMetaDataSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROWSET_HPP_
#include <com/sun/star/sdbc/XRowSet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBCX_XTABLESSUPPLIER_HPP_
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_XQUERIESSUPPLIER_HPP_
#include <com/sun/star/sdb/XQueriesSupplier.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATASOURCE_HPP_
#include <com/sun/star/sdbc/XDataSource.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTWEIGHT_HPP_
#include <com/sun/star/awt/FontWeight.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTSTRIKEOUT_HPP_
#include <com/sun/star/awt/FontStrikeout.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTSLANT_HPP_
#include <com/sun/star/awt/FontSlant.hpp>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTUNDERLINE_HPP_
#include <com/sun/star/awt/FontUnderline.hpp>
#endif
#ifndef _HTMLKYWD_HXX
#include <svtools/htmlkywd.hxx>
#endif
#ifndef _RTFKEYWD_HXX
#include <svtools/rtfkeywd.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _HTMLOUT_HXX
#include <svtools/htmlout.hxx>
#endif
#ifndef _SFXDOCINF_HXX
#include <sfx2/docinf.hxx>
#endif
#ifndef _FRMHTMLW_HXX
#include <sfx2/frmhtmlw.hxx>
#endif
#ifndef _NUMUNO_HXX
#include <svtools/numuno.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef DBAUI_TOOLS_HXX
#include "UITools.hxx"
#endif
#ifndef _TOOLKIT_HELPER_VCLUNOHELPER_HXX_
#include <toolkit/helper/vclunohelper.hxx>
#endif
#ifndef _SV_OUTDEV_HXX
#include <vcl/outdev.hxx>
#endif
#ifndef _RTFOUT_HXX
#include <svtools/rtfout.hxx>
#endif

using namespace dbaui;
using namespace dbtools;
using namespace svx;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::util;
using ::com::sun::star::frame::XModel;

#if defined(UNX)
const char __FAR_DATA ODatabaseImportExport::sNewLine = '\012';
#else
const char __FAR_DATA ODatabaseImportExport::sNewLine[] = "\015\012";
#endif

const static char __FAR_DATA sMyBegComment[]	= "<!-- ";
const static char __FAR_DATA sMyEndComment[]	= " -->";
const static char __FAR_DATA sFontFamily[]		= "font-family: ";
const static char __FAR_DATA sFontSize[]		= "font-size: ";

#define SBA_FORMAT_SELECTION_COUNT	4

DBG_NAME(ODatabaseImportExport)
//======================================================================
ODatabaseImportExport::ODatabaseImportExport(const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                                             const Reference< XMultiServiceFactory >& _rM,
                                             const Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                                             const String& rExchange)
                                             :m_xFormatter(_rxNumberF)
    ,m_xFactory(_rM)
    ,m_nCommandType(CommandType::TABLE)
    ,m_pReader(NULL)
    ,m_pRowMarker(NULL)
    ,m_bInInitialize(sal_False)
    ,m_bCheckOnly(sal_False)
{

    DBG_CTOR(ODatabaseImportExport,NULL);

    osl_incrementInterlockedCount( &m_refCount );
    impl_initFromDescriptor( _aDataDescriptor, false );

    xub_StrLen nCount = rExchange.GetTokenCount(char(11));
    if( nCount > SBA_FORMAT_SELECTION_COUNT && rExchange.GetToken(4).Len())
    {
        m_pRowMarker = new sal_Int32[nCount-SBA_FORMAT_SELECTION_COUNT];
        for(xub_StrLen i=SBA_FORMAT_SELECTION_COUNT;i<nCount;++i)
            m_pRowMarker[i-SBA_FORMAT_SELECTION_COUNT] = rExchange.GetToken(i,char(11)).ToInt32();
    }
    osl_decrementInterlockedCount( &m_refCount );
}
// -----------------------------------------------------------------------------
// import data
ODatabaseImportExport::ODatabaseImportExport( const ::dbtools::SharedConnection& _rxConnection,
        const Reference< XNumberFormatter >& _rxNumberF, const Reference< XMultiServiceFactory >& _rM )
    :m_xConnection(_rxConnection)
    ,m_xFormatter(_rxNumberF)
    ,m_xFactory(_rM)
    ,m_nCommandType(::com::sun::star::sdb::CommandType::TABLE)
    ,m_pReader(NULL)
    ,m_pRowMarker(NULL)
    ,m_bInInitialize(sal_False)
    ,m_bCheckOnly(sal_False)
{
    DBG_CTOR(ODatabaseImportExport,NULL);
}
//-------------------------------------------------------------------
ODatabaseImportExport::~ODatabaseImportExport()
{
    DBG_DTOR(ODatabaseImportExport,NULL);
    acquire();

    disposing();

    if(m_pReader)
        m_pReader->release();
    delete m_pRowMarker;
}
// -----------------------------------------------------------------------------
void ODatabaseImportExport::disposing()
{
    DBG_CHKTHIS(ODatabaseImportExport,NULL);
    // remove me as listener
    Reference< XComponent >  xComponent(m_xConnection, UNO_QUERY);
    if (xComponent.is())
    {
        Reference< XEventListener> xEvt((::cppu::OWeakObject*)this,UNO_QUERY);
        xComponent->removeEventListener(xEvt);
    }
    m_xConnection.clear();

    ::comphelper::disposeComponent(m_xRow);

    m_xObject.clear();
    m_xResultSetMetaData.clear();
    m_xResultSet.clear();
    m_xRow.clear();
    m_xFormatter.clear();

    m_aKeepModelAlive.clear();
}
// -----------------------------------------------------------------------------
void SAL_CALL ODatabaseImportExport::disposing( const EventObject& Source ) throw(::com::sun::star::uno::RuntimeException)
{
    DBG_CHKTHIS(ODatabaseImportExport,NULL);
    Reference<XConnection> xCon(Source.Source,UNO_QUERY);
    if(m_xConnection.is() && m_xConnection == xCon)
    {
        m_xConnection.clear();
        disposing();
        if(!m_bInInitialize)
            initialize();
    }
}
// -----------------------------------------------------------------------------
void ODatabaseImportExport::initialize( const ODataAccessDescriptor& _aDataDescriptor )
{
    impl_initFromDescriptor( _aDataDescriptor, true );
}

// -----------------------------------------------------------------------------
void ODatabaseImportExport::impl_initFromDescriptor( const ODataAccessDescriptor& _aDataDescriptor, bool _bPlusDefaultInit)
{
    DBG_CHKTHIS(ODatabaseImportExport,NULL);
    m_sDataSourceName = _aDataDescriptor.getDataSource();
    _aDataDescriptor[daCommandType] >>= m_nCommandType;
    _aDataDescriptor[daCommand]		>>= m_sName;
    // some additonal information
    if(_aDataDescriptor.has(daConnection))
    {
        Reference< XConnection > xPureConn( _aDataDescriptor[daConnection], UNO_QUERY );
        m_xConnection.reset( xPureConn, SharedConnection::NoTakeOwnership );
    }
    if(_aDataDescriptor.has(daSelection))
        _aDataDescriptor[daSelection]	>>= m_aSelection;

    sal_Bool bBookmarkSelection = sal_True;	// the default if not present
    if ( _aDataDescriptor.has( daBookmarkSelection ) )
    {
        _aDataDescriptor[ daBookmarkSelection ] >>= bBookmarkSelection;
        DBG_ASSERT( !bBookmarkSelection, "ODatabaseImportExport::ODatabaseImportExport: bookmarked selection not yet supported!" );
    }


    if(_aDataDescriptor.has(daCursor))
        _aDataDescriptor[daCursor]	>>= m_xResultSet;

    if ( _bPlusDefaultInit )
        initialize();
}
// -----------------------------------------------------------------------------
void ODatabaseImportExport::initialize()
{
    DBG_CHKTHIS(ODatabaseImportExport,NULL);
    m_bInInitialize = sal_True;

    if ( !m_xConnection.is() )
    {	// we need a connection
        OSL_ENSURE(m_sDataSourceName.getLength(),"There must be a datsource name!");
        Reference<XNameAccess> xDatabaseContext = Reference< XNameAccess >(m_xFactory->createInstance(SERVICE_SDB_DATABASECONTEXT), UNO_QUERY);

        try
        {
            Reference< XDataSource > xDataSource( xDatabaseContext->getByName( m_sDataSourceName ), UNO_QUERY_THROW );
            Reference< XModel > xDocument( getDataSourceOrModel( xDataSource ), UNO_QUERY_THROW );
            m_aKeepModelAlive = SharedModel( xDocument );
        }
        catch( const Exception& )
        {
            OSL_ENSURE( sal_False, "ODatabaseImportExport::initialize: could not obtaine the document model!" );
        }

        Reference< XEventListener> xEvt((::cppu::OWeakObject*)this,UNO_QUERY);

        Reference< XConnection > xConnection;
        SQLExceptionInfo aInfo = ::dbaui::createConnection( m_sDataSourceName, xDatabaseContext, m_xFactory, xEvt, xConnection );
        m_xConnection.reset( xConnection );

        if(aInfo.isValid() && aInfo.getType() == SQLExceptionInfo::SQL_EXCEPTION)
            throw *static_cast<const SQLException*>(aInfo);
    }
    else
    {
        Reference< XEventListener> xEvt((::cppu::OWeakObject*)this,UNO_QUERY);
        Reference< XComponent >  xComponent(m_xConnection, UNO_QUERY);
        if (xComponent.is() && xEvt.is())
            xComponent->addEventListener(xEvt);
    }

    Reference<XNameAccess> xNameAccess;
    switch(m_nCommandType)
    {
        case CommandType::TABLE:
            {
                // only for tables
                Reference<XTablesSupplier> xSup(m_xConnection,UNO_QUERY);
                if(xSup.is())
                    xNameAccess = xSup->getTables();
            }
            break;
        case CommandType::QUERY:
            {
                Reference<XQueriesSupplier> xSup(m_xConnection,UNO_QUERY);
                if(xSup.is())
                    xNameAccess = xSup->getQueries();
            }
            break;
    }
    if(xNameAccess.is() && xNameAccess->hasByName(m_sName))
    {
        Reference<XPropertySet> xSourceObject;
        xNameAccess->getByName(m_sName) >>= m_xObject;
    }

    if(m_xObject.is())
    {
        try
        {
            if(m_xObject->getPropertySetInfo()->hasPropertyByName(PROPERTY_FONT))
                m_xObject->getPropertyValue(PROPERTY_FONT) >>= m_aFont;

            // the result set may be already set with the datadescriptor
            if ( m_xResultSet.is() )
            {
                m_xRow.set(m_xResultSet,UNO_QUERY);
                m_xResultSetMetaData = Reference<XResultSetMetaDataSupplier>(m_xRow,UNO_QUERY)->getMetaData();
            }
            else
            {
                m_xResultSet.set(m_xFactory->createInstance(::rtl::OUString::createFromAscii("com.sun.star.sdb.RowSet")),UNO_QUERY);
                Reference<XPropertySet > xProp(m_xResultSet,UNO_QUERY);
                if(xProp.is())
                {
                    xProp->setPropertyValue( PROPERTY_ACTIVE_CONNECTION, makeAny( m_xConnection.getTyped() ) );
                    xProp->setPropertyValue(PROPERTY_COMMAND_TYPE,makeAny(m_nCommandType));
                    xProp->setPropertyValue(PROPERTY_COMMAND,makeAny(m_sName));
                    Reference<XRowSet> xRowSet(xProp,UNO_QUERY);
                    xRowSet->execute();
                    m_xRow.set(xRowSet,UNO_QUERY);
                    m_xResultSetMetaData = Reference<XResultSetMetaDataSupplier>(m_xRow,UNO_QUERY)->getMetaData();
                }
                else
                    OSL_ENSURE(sal_False, "ODatabaseImportExport::initialize: could not instantiate a rowset!");
            }
        }
        catch(Exception& )
        {
            m_xRow = NULL;
            m_xResultSetMetaData = NULL;
            ::comphelper::disposeComponent(m_xResultSet);
            throw;
        }
    }
    if ( !m_aFont.Name.getLength() )
    {
        Font aApplicationFont = OutputDevice::GetDefaultFont(
            DEFAULTFONT_SANS_UNICODE,
            Application::GetSettings().GetUILanguage(),
            DEFAULTFONT_FLAGS_ONLYONE
        );
        m_aFont = VCLUnoHelper::CreateFontDescriptor( aApplicationFont );
    }

    m_bInInitialize = sal_False;
}
//======================================================================
BOOL ORTFImportExport::Write()
{
    (*m_pStream) << '{'		<< sRTF_RTF;
    (*m_pStream) << sRTF_ANSI	<< ODatabaseImportExport::sNewLine;
    rtl_TextEncoding eDestEnc = RTL_TEXTENCODING_MS_1252;

    /*
    // Access RTF Export Beispiel
    {\rtf1\ansi
        {\colortbl\red0\green0\blue0;\red255\green255\blue255;\red192\green192\blue192;}
        {\fonttbl\f0\fcharset0\fnil MS Sans Serif;\f1\fcharset0\fnil Arial;\f2\fcharset0\fnil Arial;}
        \trowd\trgaph40
                \clbrdrl\brdrs\brdrcf0\clbrdrt\brdrs\brdrcf0\clbrdrb\brdrs\brdrcf0\clbrdrr\brdrs\brdrcf0\clshdng10000\clcfpat2\cellx1437
                \clbrdrl\brdrs\brdrcf0\clbrdrt\brdrs\brdrcf0\clbrdrb\brdrs\brdrcf0\clbrdrr\brdrs\brdrcf0\clshdng10000\clcfpat2\cellx2874
        {
            \trrh-270\pard\intbl
                {\qc\fs20\b\f1\cf0\cb2 text\cell}
                \pard\intbl
                {\qc\fs20\b\f1\cf0\cb2 datum\cell}
                \pard\intbl\row
        }
        \trowd\trgaph40\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx1437\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx2874
        {\trrh-270\pard\intbl
            {\ql\fs20\f2\cf0\cb1 heute\cell}
            \pard\intbl
            {\qr\fs20\f2\cf0\cb1 10.11.98\cell}
            \pard\intbl\row
        }
        \trowd\trgaph40\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx1437\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx2874
        {\trrh-270\pard\intbl
            {\ql\fs20\f2\cf0\cb1 morgen\cell}
            \pard\intbl
            {\qr\fs20\f2\cf0\cb1 11.11.98\cell}
            \pard\intbl\row
        }
        \trowd\trgaph40\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx1437\clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx2874
        {\trrh-270\pard\intbl
            {\ql\fs20\f2\cf0\cb1 bruder\cell}
            \pard\intbl
            {\qr\fs20\f2\cf0\cb1 21.04.98\cell}
            \pard\intbl\row
        }
        \trowd\trgaph40
        \clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx
        \clbrdrl\brdrs\brdrcf2\clbrdrt\brdrs\brdrcf2\clbrdrb\brdrs\brdrcf2\clbrdrr\brdrs\brdrcf2\clshdng10000\clcfpat1\cellx2874
        {\trrh-270\pard\intbl
            {\ql\fs20\f2\cf0\cb1 vater\cell}
            \pard\intbl
            {\qr\fs20\f2\cf0\cb1 28.06.98\cell}
            \pard\intbl\row
        }
    }
    */

    BOOL bBold			= ( ::com::sun::star::awt::FontWeight::BOLD		== m_aFont.Weight );
    BOOL bItalic		= ( ::com::sun::star::awt::FontSlant_ITALIC		== m_aFont.Slant );
    BOOL bUnderline		= ( ::com::sun::star::awt::FontUnderline::NONE	!= m_aFont.Underline );
    BOOL bStrikeout		= ( ::com::sun::star::awt::FontStrikeout::NONE	!= m_aFont.Strikeout );

    sal_Int32 nColor = 0;
    if(m_xObject.is())
        m_xObject->getPropertyValue(PROPERTY_TEXTCOLOR)	>>= nColor;
    ::Color aColor(nColor);

    ByteString aFonts(String(m_aFont.Name),eDestEnc);
    if(!aFonts.Len())
    {
        String aName = Application::GetSettings().GetStyleSettings().GetAppFont().GetName();
        aFonts = ByteString (aName,eDestEnc);
    }
    ::rtl::OString aFormat("\\fcharset0\\fnil ");
    ByteString aFontNr;

    (*m_pStream)	<< "{\\fonttbl";
    xub_StrLen nTokenCount = aFonts.GetTokenCount();
    for(xub_StrLen j=0;j<nTokenCount;++j)
    {
        (*m_pStream) << "\\f";
        m_pStream->WriteNumber(j);
        (*m_pStream) << aFormat;
        (*m_pStream) << aFonts.GetToken(j).GetBuffer();
        (*m_pStream) << ';';
    }
    (*m_pStream) << '}' ;
    (*m_pStream) << ODatabaseImportExport::sNewLine;
    // write the rtf color table
    (*m_pStream) << '{' << sRTF_COLORTBL << sRTF_RED;
    m_pStream->WriteNumber(aColor.GetRed());
    (*m_pStream) << sRTF_GREEN;
    m_pStream->WriteNumber(aColor.GetGreen());
    (*m_pStream) << sRTF_BLUE;
    m_pStream->WriteNumber(aColor.GetBlue());

    (*m_pStream) << ";\\red255\\green255\\blue255;\\red192\\green192\\blue192;}"
                 << ODatabaseImportExport::sNewLine;

    sal_Int32 nCellx = 1437;
    ::rtl::OString aTRRH("\\trrh-270\\pard\\intbl");
    ::rtl::OString aFS("\\fs20\\f0\\cf0\\cb2");
    ::rtl::OString aFS2("\\fs20\\f1\\cf0\\cb1");
    ::rtl::OString aCell1("\\clbrdrl\\brdrs\\brdrcf0\\clbrdrt\\brdrs\\brdrcf0\\clbrdrb\\brdrs\\brdrcf0\\clbrdrr\\brdrs\\brdrcf0\\clshdng10000\\clcfpat2\\cellx");
    ::rtl::OString aCell2("\\clbrdrl\\brdrs\\brdrcf2\\clbrdrt\\brdrs\\brdrcf2\\clbrdrb\\brdrs\\brdrcf2\\clbrdrr\\brdrs\\brdrcf2\\clshdng10000\\clcfpat1\\cellx");

    (*m_pStream) << sRTF_TROWD << sRTF_TRGAPH;
    m_pStream->WriteNumber(40);
    (*m_pStream) << ODatabaseImportExport::sNewLine;

    if(m_xObject.is())
    {
        Reference<XColumnsSupplier> xColSup(m_xObject,UNO_QUERY);
        Reference<XNameAccess> xColumns = xColSup->getColumns();
        Sequence< ::rtl::OUString> aNames(xColumns->getElementNames());
        const ::rtl::OUString* pIter = aNames.getConstArray();

        sal_Int32 nCount = aNames.getLength();
        sal_Bool bUseResultMetaData = sal_False;
        if ( !nCount )
        {
            nCount = m_xResultSetMetaData->getColumnCount();
            bUseResultMetaData = sal_True;
        }

        for( sal_Int32 i=1; i<=nCount; ++i )
        {
            (*m_pStream) << aCell1;
            m_pStream->WriteNumber(i*nCellx);
            (*m_pStream) << ODatabaseImportExport::sNewLine;
        }

        // Spaltenbeschreibung
        (*m_pStream) << '{' << ODatabaseImportExport::sNewLine;
        (*m_pStream) << aTRRH;


        ::rtl::OString* pHorzChar = new ::rtl::OString[nCount];

        for ( sal_Int32 i=1; i <= nCount; ++i )
        {
            sal_Int32 nAlign = 0;
            ::rtl::OUString sColumnName;
            if ( bUseResultMetaData )
                sColumnName = m_xResultSetMetaData->getColumnName(i);
            else
            {
                sColumnName = *pIter;
                Reference<XPropertySet> xColumn;
                xColumns->getByName(sColumnName) >>= xColumn;
                xColumn->getPropertyValue(PROPERTY_ALIGN) >>= nAlign;
                ++pIter;
            }

            const char* pChar;
            switch( nAlign )
            {
                case 1:	pChar = sRTF_QC;	break;
                case 2:	pChar = sRTF_QR;	break;
                case 0:
                default:pChar = sRTF_QL;	break;
            }

            pHorzChar[i-1] = pChar; // um sp"ater nicht immer im ITEMSET zuw"uhlen

            (*m_pStream) << ODatabaseImportExport::sNewLine;
            (*m_pStream) << '{';
            (*m_pStream) << sRTF_QC;   // column header always centered

            if ( bBold )		(*m_pStream) << sRTF_B;
            if ( bItalic )		(*m_pStream) << sRTF_I;
            if ( bUnderline )	(*m_pStream) << sRTF_UL;
            if ( bStrikeout )	(*m_pStream) << sRTF_STRIKE;

            (*m_pStream) << aFS;
            (*m_pStream) << ' ';
            RTFOutFuncs::Out_String(*m_pStream,sColumnName,eDestEnc);

            (*m_pStream) << sRTF_CELL;
            (*m_pStream) << '}';
            (*m_pStream) << ODatabaseImportExport::sNewLine;
            (*m_pStream) << sRTF_PARD	<< sRTF_INTBL;
        }

        (*m_pStream) << sRTF_ROW;
        (*m_pStream) << ODatabaseImportExport::sNewLine << '}';
        (*m_pStream) << ODatabaseImportExport::sNewLine;

        sal_Int32 k=1;
        sal_Int32 kk=0;
        m_xResultSet->beforeFirst(); // set back before the first row
        while(m_xResultSet->next())
        {
            if(!m_pRowMarker || m_pRowMarker[kk] == k)
            {
                ++kk;
                (*m_pStream) << sRTF_TROWD << sRTF_TRGAPH;
                m_pStream->WriteNumber(40);
                (*m_pStream) << ODatabaseImportExport::sNewLine;

                for ( sal_Int32 i=1; i<=nCount; ++i )
                {
                    (*m_pStream) << aCell2;
                    m_pStream->WriteNumber(i*nCellx);
                    (*m_pStream) << ODatabaseImportExport::sNewLine;
                }

                (*m_pStream) << '{';
                (*m_pStream) << aTRRH;
                for ( sal_Int32 i=1; i<=nCount; ++i )
                {
                    (*m_pStream) << ODatabaseImportExport::sNewLine;
                    (*m_pStream) << '{';
                    (*m_pStream) << pHorzChar[i-1];

                    if ( bBold )		(*m_pStream) << sRTF_B;
                    if ( bItalic )		(*m_pStream) << sRTF_I;
                    if ( bUnderline )	(*m_pStream) << sRTF_UL;
                    if ( bStrikeout )	(*m_pStream) << sRTF_STRIKE;

                    (*m_pStream) << aFS2;
                    (*m_pStream) << ' ';

                    try
                    {
                        ::rtl::OUString sValue = m_xRow->getString(i);
                        if (!m_xRow->wasNull())
                            RTFOutFuncs::Out_String(*m_pStream,sValue,eDestEnc);
                    }
                    catch (Exception&)
                    {
                        OSL_ENSURE(0,"RTF WRITE!");
                    }

                    (*m_pStream) << sRTF_CELL;
                    (*m_pStream) << '}';
                    (*m_pStream) << ODatabaseImportExport::sNewLine;
                    (*m_pStream) << sRTF_PARD	<< sRTF_INTBL;
                }
                (*m_pStream) << sRTF_ROW << ODatabaseImportExport::sNewLine;
                (*m_pStream) << '}';
            }
            ++k;
        }

        delete [] pHorzChar;
    }

    (*m_pStream) << '}' << ODatabaseImportExport::sNewLine;
    (*m_pStream) << (BYTE) 0;
    return ((*m_pStream).GetError() == SVSTREAM_OK);
}
//-------------------------------------------------------------------
BOOL ORTFImportExport::Read()
{
    SvParserState eState = SVPAR_ERROR;
    if ( m_pStream )
    {
        m_pReader = new ORTFReader((*m_pStream),m_xConnection,m_xFormatter,m_xFactory);
        ((ORTFReader*)m_pReader)->AddRef();
        if ( isCheckEnabled() )
            m_pReader->enableCheckOnly();
        eState = ((ORTFReader*)m_pReader)->CallParser();
        m_pReader->release();
        m_pReader = NULL;
    }

    return eState != SVPAR_ERROR;
}
//-------------------------------------------------------------------
//===================================================================
const sal_Int16 __FAR_DATA OHTMLImportExport::nDefaultFontSize[SBA_HTML_FONTSIZES] =
{
    HTMLFONTSZ1_DFLT, HTMLFONTSZ2_DFLT, HTMLFONTSZ3_DFLT, HTMLFONTSZ4_DFLT,
    HTMLFONTSZ5_DFLT, HTMLFONTSZ6_DFLT, HTMLFONTSZ7_DFLT
};

sal_Int16 OHTMLImportExport::nFontSize[SBA_HTML_FONTSIZES] = { 0 };

const sal_Int16 OHTMLImportExport::nCellSpacing = 0;
const char __FAR_DATA OHTMLImportExport::sIndentSource[nIndentMax+1] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

//========================================================================
// Makros fuer HTML-Export
//========================================================================
#define OUT_PROLOGUE()		((*m_pStream) << sHTML30_Prologue << ODatabaseImportExport::sNewLine << ODatabaseImportExport::sNewLine)
#define TAG_ON( tag )		HTMLOutFuncs::Out_AsciiTag( (*m_pStream), tag )
#define TAG_OFF( tag )		HTMLOutFuncs::Out_AsciiTag( (*m_pStream), tag, FALSE )
#define OUT_STR( str )		HTMLOutFuncs::Out_String( (*m_pStream), str )
#define OUT_LF()			(*m_pStream) << ODatabaseImportExport::sNewLine << GetIndentStr()
#define lcl_OUT_LF() 		(*m_pStream) << ODatabaseImportExport::sNewLine
#define TAG_ON_LF( tag )	(TAG_ON( tag ) << ODatabaseImportExport::sNewLine << GetIndentStr())
#define TAG_OFF_LF( tag )	(TAG_OFF( tag ) << ODatabaseImportExport::sNewLine << GetIndentStr())
#define OUT_HR()			TAG_ON_LF( sHTML_horzrule )
#define OUT_COMMENT( comment )	((*m_pStream) << sMyBegComment, OUT_STR( comment ) << sMyEndComment << ODatabaseImportExport::sNewLine << GetIndentStr())
#define lcl_OUT_COMMENT( comment )	((*m_pStream) << sMyBegComment, OUT_STR( comment ) << sMyEndComment << ODatabaseImportExport::sNewLine)

//-------------------------------------------------------------------
OHTMLImportExport::OHTMLImportExport(const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                                     const Reference< XMultiServiceFactory >& _rM,
                                     const Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                                     const String& rExchange)
        : ODatabaseImportExport(_aDataDescriptor,_rM,_rxNumberF,rExchange)
    ,m_nIndent(0)
#ifdef DBG_UTIL
    ,m_bCheckFont(FALSE)
#endif
{
    strncpy( sIndent, sIndentSource ,std::min(sizeof(sIndent),sizeof(sIndentSource)));
    sIndent[0] = 0;
}
//-------------------------------------------------------------------
BOOL OHTMLImportExport::Write()
{
    if(m_xObject.is())
    {
        (*m_pStream) << '<' << sHTML_doctype << ' ' << sHTML_doctype32 << '>' << ODatabaseImportExport::sNewLine << ODatabaseImportExport::sNewLine;
        TAG_ON_LF( sHTML_html );
        WriteHeader();
        OUT_LF();
        WriteBody();
        OUT_LF();
        TAG_OFF_LF( sHTML_html );

        return ((*m_pStream).GetError() == SVSTREAM_OK);
    }
    return sal_False;
}
//-------------------------------------------------------------------
BOOL OHTMLImportExport::Read()
{
    SvParserState eState = SVPAR_ERROR;
    if ( m_pStream )
    {
        m_pReader = new OHTMLReader((*m_pStream),m_xConnection,m_xFormatter,m_xFactory);
        ((OHTMLReader*)m_pReader)->AddRef();
        if ( isCheckEnabled() )
            m_pReader->enableCheckOnly();
        //dyf add 20070601
        m_pReader->SetTableName(m_sDefaultTableName);
        //dyf add end
        eState = ((OHTMLReader*)m_pReader)->CallParser();
        m_pReader->release();
        m_pReader = NULL;
    }

    return eState != SVPAR_ERROR;
}
//-------------------------------------------------------------------
void OHTMLImportExport::WriteHeader()
{
    SfxDocumentInfo rInfo;
    rInfo.SetTitle(m_sName);
    String	aStrOut;

    IncIndent(1); TAG_ON_LF( sHTML_head );

    SfxFrameHTMLWriter::Out_DocInfo( (*m_pStream), String(), &rInfo, sIndent );
    OUT_LF();
    IncIndent(-1); OUT_LF(); TAG_OFF_LF( sHTML_head );
}
//-----------------------------------------------------------------------
void OHTMLImportExport::WriteBody()
{

    IncIndent(1); TAG_ON_LF( sHTML_style );

    (*m_pStream) << sMyBegComment; OUT_LF();
    (*m_pStream) << sHTML_body << " { " << sFontFamily << '\"' << ::rtl::OString(m_aFont.Name,m_aFont.Name.getLength(), gsl_getSystemTextEncoding()) << '\"';
        // TODO : think about the encoding of the font name
    (*m_pStream) << "; " << sFontSize;
    m_pStream->WriteNumber(m_aFont.Height);
    (*m_pStream) << '}';

    OUT_LF();
    (*m_pStream) << sMyEndComment;
    IncIndent(-1); OUT_LF(); TAG_OFF_LF( sHTML_style );
    OUT_LF();

    // default Textfarbe schwarz
    (*m_pStream) << '<' << sHTML_body << ' ' << sHTML_O_text << '=';
    sal_Int32 nColor = 0;
    if(m_xObject.is())
        m_xObject->getPropertyValue(PROPERTY_TEXTCOLOR)	>>= nColor;
    ::Color aColor(nColor);
    HTMLOutFuncs::Out_Color( (*m_pStream), aColor );

    ::rtl::OString sOut( ' ' );
    sOut = sOut + sHTML_O_bgcolor;
    sOut = sOut + "=";
    (*m_pStream) << sOut;
    HTMLOutFuncs::Out_Color( (*m_pStream), aColor );

    (*m_pStream) << '>'; OUT_LF();

    WriteTables();

    TAG_OFF_LF( sHTML_body );
}
//-----------------------------------------------------------------------
void OHTMLImportExport::WriteTables()
{
    ::rtl::OString aStrOut  = sHTML_table;
    aStrOut = aStrOut + " ";
    aStrOut = aStrOut + sHTML_frame;
    aStrOut = aStrOut + "=";
    aStrOut = aStrOut + sHTML_TF_void;

    Sequence< ::rtl::OUString> aNames;
    Reference<XNameAccess> xColumns;
    sal_Bool bUseResultMetaData = sal_False;
    if(m_xObject.is())
    {
        Reference<XColumnsSupplier> xColSup(m_xObject,UNO_QUERY);
        xColumns = xColSup->getColumns();
        aNames = xColumns->getElementNames();
        if ( !aNames.getLength() )
        {
            sal_Int32 nCount = m_xResultSetMetaData->getColumnCount();
            aNames.realloc(nCount);
            for (sal_Int32 i= 0; i < nCount; ++i)
                aNames[i] = m_xResultSetMetaData->getColumnName(i+1);
            bUseResultMetaData = sal_True;
        }
    }

    aStrOut	= aStrOut + " ";
    aStrOut	= aStrOut + sHTML_O_align;
    aStrOut	= aStrOut + "=";
    aStrOut	= aStrOut + sHTML_AL_left;
    aStrOut	= aStrOut + " ";
    aStrOut	= aStrOut + sHTML_O_cellspacing;
    aStrOut	= aStrOut + "=";
    aStrOut	= aStrOut + ::rtl::OString::valueOf((sal_Int32)nCellSpacing);
    aStrOut	= aStrOut + " ";
    aStrOut	= aStrOut + sHTML_O_cols;
    aStrOut	= aStrOut + "=";
    aStrOut	= aStrOut + ::rtl::OString::valueOf(aNames.getLength());
    aStrOut	= aStrOut + " ";
    aStrOut	= aStrOut + sHTML_O_border;
    aStrOut	= aStrOut + "=1";

    IncIndent(1);
    TAG_ON( aStrOut );

    FontOn();

    TAG_ON( sHTML_caption );
    TAG_ON( sHTML_bold );

    (*m_pStream)	<< ::rtl::OString(m_sName,m_sName.getLength(), gsl_getSystemTextEncoding());
        // TODO : think about the encoding of the name
    TAG_OFF( sHTML_bold );
    TAG_OFF( sHTML_caption );

    FontOff();
    OUT_LF();
    // </FONT>

    IncIndent(1);
    TAG_ON_LF( sHTML_thead );

    IncIndent(1);
    TAG_ON_LF( sHTML_tablerow );

    if(m_xObject.is())
    {
        sal_Int32* pFormat = new sal_Int32[aNames.getLength()];

        const char **pHorJustify = new const char*[aNames.getLength()];
        sal_Int32 *pColWidth = new sal_Int32[aNames.getLength()];


        sal_Int32 nHeight = 0;
        m_xObject->getPropertyValue(PROPERTY_ROW_HEIGHT) >>= nHeight;

        // 1. die Spaltenbeschreibung rauspusten
        const ::rtl::OUString* pIter = aNames.getConstArray();
        const ::rtl::OUString* pEnd = pIter + aNames.getLength();

        for( sal_Int32 i=0;pIter != pEnd; ++pIter,++i )
        {
            sal_Int32 nAlign = 0;
            pFormat[i] = 0;
            pColWidth[i] = 100;
            if ( !bUseResultMetaData )
            {
                Reference<XPropertySet> xColumn;
                xColumns->getByName(*pIter) >>= xColumn;
                xColumn->getPropertyValue(PROPERTY_ALIGN) >>= nAlign;
                pFormat[i] = ::comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_FORMATKEY));
                pColWidth[i] = ::comphelper::getINT32(xColumn->getPropertyValue(PROPERTY_WIDTH));
            }

            switch( nAlign )
            {
                case 1:		pHorJustify[i] = sHTML_AL_center;	break;
                case 2:		pHorJustify[i] = sHTML_AL_right;	break;
                default:	pHorJustify[i] = sHTML_AL_left;		break;
            }

            if(i == aNames.getLength()-1)
                IncIndent(-1);

            WriteCell(pFormat[i],pColWidth[i],nHeight,pHorJustify[i],*pIter,sHTML_tableheader);
        }

        IncIndent(-1);
        TAG_OFF_LF( sHTML_tablerow );
        TAG_OFF_LF( sHTML_thead );

        IncIndent(1);
        TAG_ON_LF( sHTML_tbody );

        // 2. und jetzt die Daten

        sal_Int32 j=1;
        sal_Int32 kk=0;
        m_xResultSet->beforeFirst(); // set back before the first row
        while(m_xResultSet->next())
        {
            IncIndent(1);
            TAG_ON_LF( sHTML_tablerow );

            if(!m_pRowMarker || m_pRowMarker[kk] == j)
            {
                ++kk;
                for(sal_Int32 i=1;i<=aNames.getLength();++i)
                {
                    if(i == aNames.getLength())
                        IncIndent(-1);

                    String aValue;
                    try
                    {
                        ::rtl::OUString sValue = m_xRow->getString(i);
                        if (!m_xRow->wasNull())
                        {
                            aValue = sValue;
                        }
                    }
                    catch ( Exception& )
                    {
                        OSL_ENSURE(sal_False, "OHTMLImportExport::WriteTables: caught an exception!");
                    }
                    WriteCell(pFormat[i-1],pColWidth[i-1],nHeight,pHorJustify[i-1],aValue,sHTML_tabledata);
                }
            }
            ++j;
            TAG_OFF_LF( sHTML_tablerow );
        }

        delete [] pFormat;
        delete [] pHorJustify;
        delete [] pColWidth;
    }
    else
    {
        IncIndent(-1);
        TAG_OFF_LF( sHTML_tablerow );
        TAG_OFF_LF( sHTML_thead );

        IncIndent(1);
        TAG_ON_LF( sHTML_tbody );
    }

    IncIndent(-1); OUT_LF(); TAG_OFF_LF( sHTML_tbody );
    IncIndent(-1); TAG_OFF_LF( sHTML_table );
}
//-----------------------------------------------------------------------
void OHTMLImportExport::WriteCell( sal_Int32 nFormat,sal_Int32 nWidthPixel,sal_Int32 nHeightPixel,const char* pChar,const String& rValue,const char* pHtmlTag)
{
    BOOL bValueData;
    bValueData = FALSE;

    ::rtl::OString aStrTD = pHtmlTag;

    nWidthPixel  = nWidthPixel	? nWidthPixel	: 86;
    nHeightPixel = nHeightPixel ? nHeightPixel	: 17;

    // trotz der <TABLE COLS=n> und <COL WIDTH=x> Angaben noetig,
    // da die nicht von Netscape beachtet werden..
    // Spaltenbreite
    aStrTD = aStrTD + " ";
    aStrTD = aStrTD + sHTML_O_width;
    aStrTD = aStrTD + "=";
    aStrTD = aStrTD + ::rtl::OString::valueOf((sal_Int32)nWidthPixel);
    // Zeilenhoehe
    aStrTD = aStrTD + " ";
    aStrTD = aStrTD + sHTML_O_height;
    aStrTD = aStrTD + "=";
    aStrTD = aStrTD + ::rtl::OString::valueOf((sal_Int32)nHeightPixel);

    aStrTD = aStrTD + " ";
    aStrTD = aStrTD + sHTML_O_align;
    aStrTD = aStrTD + "=";
    aStrTD = aStrTD + pChar;

    double fVal = 0.0;

    Reference< ::com::sun::star::util::XNumberFormatsSupplier >  xSupplier = m_xFormatter->getNumberFormatsSupplier();
    SvNumberFormatsSupplierObj* pSupplierImpl = SvNumberFormatsSupplierObj::getImplementation( xSupplier );
    SvNumberFormatter* pFormatter = pSupplierImpl ? pSupplierImpl->GetNumberFormatter() : NULL;
    if(pFormatter)
    {
        try
        {
            fVal = m_xFormatter->convertStringToNumber(nFormat,rValue);
            ByteString aTmpString(aStrTD);
            HTMLOutFuncs::CreateTableDataOptionsValNum( aTmpString, bValueData, fVal,nFormat, *pFormatter );
        }
        catch(Exception&)
        {
            ByteString aTmpString(aStrTD);
            HTMLOutFuncs::CreateTableDataOptionsValNum( aTmpString, bValueData, fVal,nFormat, *pFormatter );
        }
    }

    TAG_ON( aStrTD );

    FontOn();

    BOOL bBold			= ( ::com::sun::star::awt::FontWeight::BOLD		== m_aFont.Weight );
    BOOL bItalic		= ( ::com::sun::star::awt::FontSlant_ITALIC		== m_aFont.Slant );
    BOOL bUnderline		= ( ::com::sun::star::awt::FontUnderline::NONE	!= m_aFont.Underline );
    BOOL bStrikeout		= ( ::com::sun::star::awt::FontStrikeout::NONE	!= m_aFont.Strikeout );

    if ( bBold )		TAG_ON( sHTML_bold );
    if ( bItalic )		TAG_ON( sHTML_italic );
    if ( bUnderline )	TAG_ON( sHTML_underline );
    if ( bStrikeout )	TAG_ON( sHTML_strike );

    if ( !rValue.Len() )
        TAG_ON( sHTML_linebreak );		// #42573# keine komplett leere Zelle
    else
        OUT_STR( rValue );

    if ( bStrikeout )	TAG_OFF( sHTML_strike );
    if ( bUnderline )	TAG_OFF( sHTML_underline );
    if ( bItalic )		TAG_OFF( sHTML_italic );
    if ( bBold )		TAG_OFF( sHTML_bold );

    FontOff();

    TAG_OFF_LF( pHtmlTag );
}
//-----------------------------------------------------------------------
void OHTMLImportExport::FontOn()
{
#ifdef DBG_UTIL
        m_bCheckFont = TRUE;
#endif

    // <FONT FACE="xxx">
    ::rtl::OString aStrOut  = "<";
    aStrOut  = aStrOut + sHTML_font;
    aStrOut  = aStrOut + " ";
    aStrOut  = aStrOut + sHTML_O_face;
    aStrOut  = aStrOut + "=";
    aStrOut  = aStrOut + "\"";
    aStrOut  = aStrOut + ::rtl::OString(m_aFont.Name,m_aFont.Name.getLength(),gsl_getSystemTextEncoding());
        // TODO : think about the encoding of the font name
    aStrOut  = aStrOut + "\"";
    aStrOut  = aStrOut + " ";
    aStrOut  = aStrOut + sHTML_O_color;
    aStrOut  = aStrOut + "=";
    (*m_pStream) << aStrOut;

    sal_Int32 nColor = 0;
    if(m_xObject.is())
        m_xObject->getPropertyValue(PROPERTY_TEXTCOLOR)	>>= nColor;
    ::Color aColor(nColor);

    HTMLOutFuncs::Out_Color( (*m_pStream), aColor );
    (*m_pStream) << ">";
}
//-----------------------------------------------------------------------
inline void OHTMLImportExport::FontOff()
{
    DBG_ASSERT(m_bCheckFont,"Kein FontOn() gerufen");
    TAG_OFF( sHTML_font );
#ifdef DBG_UTIL
    m_bCheckFont = FALSE;
#endif
}
//-----------------------------------------------------------------------
void OHTMLImportExport::IncIndent( sal_Int16 nVal )
{
    sIndent[m_nIndent] = '\t';
    m_nIndent = m_nIndent + nVal;
    if ( m_nIndent < 0 )
        m_nIndent = 0;
    else if ( m_nIndent > nIndentMax )
        m_nIndent = nIndentMax;
    sIndent[m_nIndent] = 0;
}
// -----------------------------------------------------------------------------

