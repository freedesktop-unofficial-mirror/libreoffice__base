/*************************************************************************
 *
 *  $RCSfile: UITools.hxx,v $
 *
 *  $Revision: 1.11 $
 *
 *  last change: $Author: oj $ $Date: 2002-04-29 08:07:40 $
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
#define DBAUI_TOOLS_HXX

#ifndef _DBHELPER_DBEXCEPTION_HXX_
#include <connectivity/dbexception.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif
#ifndef _SVX_SVXENUM_HXX 
#include <svx/svxenum.hxx>
#endif
#ifndef _SV_TASKPANELIST_HXX 
#include <vcl/taskpanelist.hxx>
#endif

// we only need forward decl here
namespace com { namespace sun { namespace star {

    namespace beans		{ class XPropertySet;}
    namespace container { class XNameAccess;}
    namespace lang 
    { 
        class XEventListener;
        class XMultiServiceFactory;
    }
    namespace awt
    {
        struct FontDescriptor;
    }
    namespace sdbc 
    { 
        class XDatabaseMetaData;
        class XConnection;
    }
    
}}}

class Window;
class ToolBox;
class Font;
class SvNumberFormatter;
// .........................................................................
namespace dbaui
{
// .........................................................................

    /** compose a complete table name from it's up to three parts, regarding to the database meta data composing rules
        the PropertySet must be support the service com::sun::star::sdbc::table
    */
    void composeTableName(	const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData >& _rxMetaData,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxTable,
                            ::rtl::OUString& _rComposedName,
                            sal_Bool _bQuote);

    /** creates a new connection and appends the eventlistener
        @param	_rsDataSourceName		name of the datasource
        @param	_xDatabaseContext		the database context
        @param	_rEvtLst				the eventlistener which will be added to the new created connection
        @param	_rOUTConnection			this parameter will be filled with the new created connection
        @return	SQLExceptionInfo		contains a SQLException, SQLContext or a SQLWarning when they araised else .isValid() will return false
    */
    ::dbtools::SQLExceptionInfo createConnection(	
                                    const ::rtl::OUString& _rsDataSourceName,
                                     const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _xDatabaseContext,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rMF,
                                    ::com::sun::star::uno::Reference< ::com::sun::star::lang::XEventListener>& _rEvtLst,
                                    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _rOUTConnection );

    /**	 creates a error dialog which displays the SQLExceptionInfo. Also it supports a "more" button where detailed information are available
        @param	_rInfo					the error which should be shown, if the info is not valid no error dialog will appear
        @param	_pParent				the parent of the error dialog
        @param	_xFactory				need to create the dialog
    */
    void showError(	const ::dbtools::SQLExceptionInfo& _rInfo,
                    Window* _pParent,
                    const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xFactory);

    /** return a vector which contains all key columns for the @see com::sun::star::sdbc::KeyType _nKeyType
        @param	_rxTable				the table which must be a @see com::sun::star::sdbcx::XColumnsSupplier
        @param	_nKeyType				@see com::sun::star::sdbc::KeyType
    */

    ::std::vector< ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess> > 
        getKeyColumns(	const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxTable,
                        sal_Int32 _nKeyType);

    /** fills a map and a vector with localized type names
        @param	_rxConnection	the connection to acces the metadata
        @param	_rsTypeNames	a list of localized type names seperated with ';'
        @param	_rTypeInfoMap	the filled map with the type names
        @param 	_rTypeInfoIters	the vector filled with map iterators
    */
    void fillTypeInfo(	const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _rxConnection,
                        const String& _rsTypeNames,
                        OTypeInfoMap& _rTypeInfoMap,
                        ::std::vector<OTypeInfoMap::iterator>& _rTypeInfoIters);

    /** fill a column with data of a field description
        @param	_rxColumn	the column which should be filled
        @param	_pFieldDesc	the source of the data
    */
    class OFieldDescription;
    void setColumnProperties(	const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _rxColumn,
                                const OFieldDescription* _pFieldDesc);

    ::rtl::OUString createDefaultName(	const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData>& _xMetaData,
                                        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess>& _xTables,
                                        const ::rtl::OUString& _sName);

    /** checks if the given name exists in the database context
    */
    sal_Bool checkDataSourceAvailable(	const ::rtl::OUString& _sDataSourceName,
                                        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xFactory_xORB);

    /** maps SvxCellHorJustify to com::sun::star::awt::TextAlign
        @param SvxCellHorJustify& _eAlignment
        @return the corresponding com::sun::star::awt::TextAlign
    */
    sal_Int32 mapTextAllign(const SvxCellHorJustify& _eAlignment);
    /** fill a column with ui data of a field description
        @param	_rxColumn	the column which should be filled
        @param	_pFieldDesc	the source of the data
    */
    void setColumnUiProperties(	const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _rxColumn,
                                const OFieldDescription* _pFieldDesc);

    /** convert Font to ::com::sun::star::awt::FontDescriptor
        @param	_rFont	Font to be converted
        @return	the new FontDescriptor
    */
    ::com::sun::star::awt::FontDescriptor CreateFontDescriptor( const Font& _rFont );

    /** call teh format dialog and set the selected format at the column
        @param	_xAffectedCol	Font to be converted
        @param	_xField			Font to be converted
    */
    void callColumnFormatDialog(const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xAffectedCol, 
                                const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet>& _xField,
                                SvNumberFormatter* _pFormatter,
                                Window* _pParent);

    /** second variant of the function before
    */
    sal_Bool callColumnFormatDialog(Window* _pParent,
                                    SvNumberFormatter* _pFormatter,
                                    sal_Int32 _nDataType,
                                    sal_Int32& _nFormatKey,
                                    SvxCellHorJustify& _eJustify,
                                    sal_uInt16&	_nFlags,
                                    sal_Bool  _bHasFormat);
    /** append a name to tablefilter of a datasource
        @param	_xConnection	the connection is need to get the datasource
        @param	_sName			the name which should be appended
        @param	_xFactory		needed to check if datasource is available
        @param	_pParent		needed when an error must be shown
        @return false when datsource is not available otherwise true
    */
    sal_Bool appendToFilter(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection>& _xConnection, 
                            const ::rtl::OUString& _sName,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _xFactory,
                            Window* _pParent);

    /** notifySystemWindow adds or remove the given window _pToRegister at the Systemwindow found when search _pWindow.
        @param	_pWindow
            The window which is used to search for the SystemWindow.
        @param	_pToRegister
            The window which should be added or removed on the TaskPaneList.
        @param	_rMemFunc
            The member function which should be called at the SystemWindow when found.
            Possible values are: 
            ::comphelper::mem_fun(&TaskPaneList::AddWindow) 
            ::comphelper::mem_fun(&TaskPaneList::RemoveWindow)
    */
    void notifySystemWindow(Window* _pWindow,
                            Window* _pToRegister, 
                            ::comphelper::mem_fun1_t<TaskPaneList,Window*> _rMemFunc);

    /** adjustToolBoxSize checks if the size of the ToolBox is still valid. If not it will be resized.
        @param	_pToolBox
            The Toolbox which should be resized.
    */
    void adjustToolBoxSize(ToolBox* _pToolBox);

    /** isHiContrast check if we are in hi contrast mode.
        @param	_pWindow
            The window we have to check on.
        @return
            <TRUE/> if so, otherwise <FALSE/>
    */
    sal_Bool isHiContrast(Window* _pWindow);

// .........................................................................
}
// .........................................................................
#endif // DBAUI_TOOLS_HXX


