/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: TokenWriter.hxx,v $
 * $Revision: 1.23 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#ifndef DBAUI_TOKENWRITER_HXX
#define DBAUI_TOKENWRITER_HXX

#ifndef DBAUI_DATABASEEXPORT_HXX
#include "DExport.hxx"
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _COM_SUN_STAR_AWT_FONTDESCRIPTOR_HPP_
#include <com/sun/star/awt/FontDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSET_HPP_
#include <com/sun/star/sdbc/XResultSet.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XRESULTSETUPDATE_HPP_
#include <com/sun/star/sdbc/XResultSetUpdate.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_XROW_HPP_
#include <com/sun/star/sdbc/XRow.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XEVENTLISTENER_HPP_
#include <com/sun/star/lang/XEventListener.hpp>
#endif
#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COM_SUN_STAR_BEANS_PROPERTYVALUE_HPP_
#include <com/sun/star/beans/PropertyValue.hpp>
#endif
#ifndef _COM_SUN_STAR_SDB_COMMANDTYPE_HPP_
#include <com/sun/star/sdb/CommandType.hpp>
#endif
#ifndef _SVX_DATACCESSDESCRIPTOR_HXX_ 
#include <svx/dataaccessdescriptor.hxx>
#endif
#ifndef _DBAUI_COMMON_TYPES_HXX_
#include "commontypes.hxx"
#endif
#include <memory>

namespace com { namespace sun { namespace star { 
    namespace sdbc{
        class XRowUpdate;
    }
}}}

namespace dbaui
{
    // =========================================================================
    // ODatabaseImportExport Basisklasse f"ur Import/Export
    // =========================================================================
    class ODatabaseExport;
    typedef ::cppu::WeakImplHelper1< ::com::sun::star::lang::XEventListener> ODatabaseImportExport_BASE;
    class ODatabaseImportExport : public ODatabaseImportExport_BASE
    {
    private:
        void disposing();
        void impl_initializeRowMember_throw();

    protected:
        typedef ::utl::SharedUNOComponent   <   ::com::sun::star::frame::XModel
                                            ,   ::utl::CloseableComponent
                                            >   SharedModel;

    protected:
        ::com::sun::star::lang::Locale	                                                m_aLocale;
        ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>					m_aSelection;
        SvStream*																		m_pStream;
        ::com::sun::star::awt::FontDescriptor											m_aFont;
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >		m_xObject;		// table/query
        SharedConnection                                                                m_xConnection;	// 
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet >			m_xResultSet;	// 
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRow >				m_xRow;	// 
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetMetaData >	m_xResultSetMetaData;	// 
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >   m_xRowSetColumns;
        ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > 	m_xFormatter;	// a number formatter working with the connection's NumberFormatsSupplier
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory> m_xFactory;
        SharedModel                                                                     m_aKeepModelAlive;

        ::rtl::OUString m_sName;
        //dyf add 20070601 
        //for transfor the tablename
        ::rtl::OUString m_sDefaultTableName;
        //dyf add end
        ::rtl::OUString m_sDataSourceName;
        sal_Int32		m_nCommandType;

#if defined UNX
        static const char __FAR_DATA sNewLine;
#else
        static const char __FAR_DATA sNewLine[];
#endif

        ODatabaseExport*	m_pReader;
        sal_Int32*			m_pRowMarker; // wenn gesetzt, dann nur diese Rows kopieren
        rtl_TextEncoding    m_eDestEnc;
        sal_Bool			m_bInInitialize;
        sal_Bool			m_bCheckOnly;

        // export data
        ODatabaseImportExport(	const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                                const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                                const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                                const String& rExchange = String());

        // import data
        ODatabaseImportExport(	const SharedConnection& _rxConnection,
                                const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                                const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM);

        virtual ~ODatabaseImportExport();

        virtual void initialize();
    public:
        void setStream(SvStream* _pStream){  m_pStream = _pStream; }

        //dyf add 20070601
        //for set the tablename
        void setSTableName(const ::rtl::OUString &_sTableName){ m_sDefaultTableName = _sTableName; }
        //dyf add end

        virtual BOOL Write()	= 0; // Export
        virtual BOOL Read()		= 0; // Import

        void initialize(const ::svx::ODataAccessDescriptor& _aDataDescriptor);
        
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

        void enableCheckOnly() { m_bCheckOnly = sal_True; }
        sal_Bool isCheckEnabled() const { return m_bCheckOnly; }

    private:
        void impl_initFromDescriptor( const ::svx::ODataAccessDescriptor& _aDataDescriptor, bool _bPlusDefaultInit );
    };

    // =========================================================================
    // RTF Im- und Export
    // =========================================================================

    class ORTFImportExport : public ODatabaseImportExport
    {

    public:
        // export data
        ORTFImportExport(	const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                            const String& rExchange = String()) 
                            : ODatabaseImportExport(_aDataDescriptor,_rM,_rxNumberF,rExchange) {};

        // import data
        ORTFImportExport(	const SharedConnection& _rxConnection,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM) 
                        : ODatabaseImportExport(_rxConnection,_rxNumberF,_rM) 
        {}

        virtual BOOL Write();
        virtual BOOL Read();
    };
    // =========================================================================
    // HTML Im- und Export
    // =========================================================================
    #define SBA_HTML_FONTSIZES 7
    const sal_Int16 nIndentMax = 23;
    class OHTMLImportExport : public ODatabaseImportExport
    {
        // default HtmlFontSz[1-7]
        static const sal_Int16	nDefaultFontSize[SBA_HTML_FONTSIZES];
        // HtmlFontSz[1-7] in s*3.ini [user]
        static sal_Int16		nFontSize[SBA_HTML_FONTSIZES];
        static const sal_Int16	nCellSpacing;
        static const char __FAR_DATA sIndentSource[];
        char					sIndent[nIndentMax+1];
        sal_Int16				m_nIndent;
    #ifdef DBG_UTIL
        BOOL					m_bCheckFont;
    #endif

        void WriteHeader();
        void WriteBody();
        void WriteTables();
        void WriteCell( sal_Int32 nFormat,sal_Int32 nWidthPixel,sal_Int32 nHeightPixel,const char* pChar,const String& rValue,const char* pHtmlTag);
        void IncIndent( sal_Int16 nVal );
        const char*			GetIndentStr() { return sIndent; }
        void FontOn();
        inline void FontOff();

    public:
        // export data
        OHTMLImportExport(	const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                            const String& rExchange = String());
        // import data
        OHTMLImportExport(	const SharedConnection& _rxConnection,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter >& _rxNumberF,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM) 
                        : ODatabaseImportExport(_rxConnection,_rxNumberF,_rM) 
        {}

        virtual BOOL Write();
        virtual BOOL Read();

    };
    // =========================================================================
    // normal RowSet Im- und Export
    // =========================================================================

    class ORowSetImportExport : public ODatabaseImportExport
    {
        OModuleClient		m_aModuleClient;
        ::std::vector<sal_Int32>	m_aColumnMapping;
        ::std::vector<sal_Int32>	m_aColumnTypes;
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate >	m_xTargetResultSetUpdate;	// 
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XRowUpdate >			m_xTargetRowUpdate;			//
        ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetMetaData >	m_xTargetResultSetMetaData;	// 
        Window*						m_pParent;
        sal_Bool					m_bAlreadyAsked;

        sal_Bool insertNewRow();
    protected:
        virtual void initialize();

    public:
        // export data
        ORowSetImportExport(Window* _pParent,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSetUpdate >& _xResultSetUpdate,
                            const ::svx::ODataAccessDescriptor& _aDataDescriptor,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM,
                            const String& rExchange = String());

        // import data
        ORowSetImportExport(const SharedConnection& _rxConnection,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM) 
                        : ODatabaseImportExport(_rxConnection,NULL,_rM) 
        {}
        
        virtual BOOL Write();
        virtual BOOL Read();

    private:
        using ODatabaseImportExport::initialize;
    };

}
#endif // DBAUI_TOKENWRITER_HXX



