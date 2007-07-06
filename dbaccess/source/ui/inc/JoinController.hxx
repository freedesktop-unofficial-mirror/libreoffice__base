/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: JoinController.hxx,v $
 *
 *  $Revision: 1.22 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-06 08:23:57 $
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
#ifndef DBAUI_JOINCONTROLLER_HXX
#define DBAUI_JOINCONTROLLER_HXX

#ifndef DBAUI_SINGLEDOCCONTROLLER_HXX
#include "singledoccontroller.hxx"
#endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
#include <com/sun/star/beans/XPropertySet.hpp>
#endif
#ifndef _DBAUI_MODULE_DBU_HXX_
#include "moduledbu.hxx"
#endif
#ifndef DBAUI_JOINTABLEVIEW_HXX
#include "JoinTableView.hxx"
#endif
#ifndef DBAUI_JOINDESIGNVIEW_HXX
#include "JoinDesignView.hxx"
#endif
#ifndef _MEMORY_
#include <memory>
#endif

class VCLXWindow;
namespace dbaui
{
    class OAddTableDlg;
    class AddTableDialogContext;
    class OTableConnectionData;
    class OTableWindowData;
    class OTableWindow;
    typedef OSingleDocumentController OJoinController_BASE;
    class OJoinController : public OJoinController_BASE
    {
        OModuleClient                    m_aModuleClient;
    protected:
        ::std::vector<OTableConnectionData*>	m_vTableConnectionData;
        ::std::vector<OTableWindowData*>		m_vTableData;

        Fraction								m_aZoom;
        ::dbtools::SQLExceptionInfo				m_aExceptionInfo;

        OAddTableDlg*	                            m_pAddTableDialog;
        ::std::auto_ptr< AddTableDialogContext >    m_pDialogContext;

        // state of a feature. 'feature' may be the handle of a ::com::sun::star::util::URL somebody requested a dispatch interface for OR a toolbar slot.
        virtual FeatureState	GetState(sal_uInt16 nId) const;
        // execute a feature
        virtual void			Execute(sal_uInt16 nId, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aArgs);

        /** loads the information for the windows.
            @param	_aViewProps
                The properties which comes from the layout information.
        */
        void loadTableWindows(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _aViewProps);

        /** loads the information for one window.
            @param	_rTable
                The properties which comes from the layout information.
        */
        void loadTableWindow(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _rTable);

        /** saves the TableWindows structure in a sequence of property values
            @param	_rViewProps
                Contains the new sequence.
        */
        void saveTableWindows(::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& _rViewProps);

        virtual ~OJoinController();
    public:
        OJoinController(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rM);

        // ---------------------------------------------------------------
        // attribute access
        ::std::vector< OTableWindowData*>*		getTableWindowData()		{ return &m_vTableData; }
        ::std::vector< OTableConnectionData*>*	getTableConnectionData()	{ return &m_vTableConnectionData;}

        OAddTableDlg*   getAddTableDialog() const { return m_pAddTableDialog; }

        // ---------------------------------------------------------------
        // OSingleDocumentController overridables
        virtual void        reconnect( sal_Bool _bUI );
        virtual void        setModified( sal_Bool _bModified = sal_True );

        // ---------------------------------------------------------------
        // own overridables
        /** determines whether or not it's allowed for database views to participate in the game
        */
        virtual bool allowViews() const = 0;

        /** determines whether or not it's allowed for queries to participate in the game
        */
        virtual bool allowQueries() const = 0;

        /** provides access to the OJoinDesignView belonging to the controller, which might
            or might not be the direct view (getView)
        */
        virtual OJoinDesignView*	getJoinView();


        // ---------------------------------------------------------------
        /** erase the data in the data vector
            @param	_pData
                    the data whioch should be erased
        */
        void    removeConnectionData(OTableConnectionData* _pData);

        void    SaveTabWinsPosSize( OJoinTableView::OTableWindowMap* pTabWinList, long nOffsetX, long nOffsetY );

        void	SaveTabWinPosSize(OTableWindow* pTabWin, long nOffsetX, long nOffsetY);

        // ---------------------------------------------------------------
        // UNO interface overridables
        // XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw(::com::sun::star::uno::RuntimeException);

        // ::com::sun::star::lang::XComponent
        virtual void	SAL_CALL disposing();
        // ::com::sun::star::frame::XController
        virtual sal_Bool SAL_CALL suspend(sal_Bool bSuspend) throw( ::com::sun::star::uno::RuntimeException );


        // ---------------------------------------------------------------
        // misc
        /** only defines a method to save a SQLException in d&d methods to show the error at a later state
            set the internal member m_aExceptionInfo to _rInfo
        */
        void setErrorOccured(const ::dbtools::SQLExceptionInfo& _rInfo)
        {
            m_aExceptionInfo = _rInfo;
        }
        /**
            just returns the internal member and clears it
        */
        ::dbtools::SQLExceptionInfo clearOccuredError()
        {
            ::dbtools::SQLExceptionInfo aInfo = m_aExceptionInfo;
            m_aExceptionInfo = ::dbtools::SQLExceptionInfo();
            return aInfo;
        }

    protected:
        virtual OTableWindowData* createTableWindowData() = 0;
        // ask the user if the design should be saved when it is modified
        virtual short saveModified() = 0;
        // called when the orignal state should be reseted (first time load)
        virtual void reset()		 = 0;
        virtual void describeSupportedFeatures();

        AddTableDialogContext&  impl_getDialogContext() const;
    };
}
#endif // DBAUI_JOINCONTROLLER_HXX

