#ifndef RPTUI_UNDO_HXX
#define RPTUI_UNDO_HXX
/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Undo.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:30 $
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

#ifndef RPTUI_UNDOACTIONS_HXX
#include "UndoActions.hxx"
#endif
#include <functional>

FORWARD_DECLARE_INTERFACE(awt,XControl)
FORWARD_DECLARE_INTERFACE(awt,XControlContainer)
FORWARD_DECLARE_INTERFACE(drawing,XShape)
namespace dbaui
{
    class IController;
}
namespace rptui
{
    class OObjectBase;
    
    
    /** \class OSectionUndo
     * Undo class for section add and remove.
     */
    class OSectionUndo : public OCommentUndoAction
    {
        OSectionUndo(const OSectionUndo&);
        void operator =(const OSectionUndo&);
    protected:
        ::std::vector< ::com::sun::star::uno::Reference< ::com::sun::star::drawing::XShape> > 
                                                    m_aControls;
        ::std::vector< ::std::pair< ::rtl::OUString ,::com::sun::star::uno::Any> > 
                                                    m_aValues;
        Action										m_eAction;
        sal_uInt16									m_nSlot;
        bool                                        m_bInserted;

        virtual void    implReInsert( ) = 0;
        virtual void    implReRemove( ) = 0;

        void collectControls(const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >& _xSection);
    public:
        TYPEINFO();
        OSectionUndo(	OReportModel& rMod
                        ,sal_uInt16 _nSlot
                        ,Action _eAction
                        ,USHORT nCommentID);
        virtual ~OSectionUndo();

        virtual void		Undo();
        virtual void		Redo();
    };

    /** Undo action for the group header, footer, page header, footer
    */
    class OReportSectionUndo : public OSectionUndo
    {
        OReportHelper								m_aReportHelper;
        ::std::mem_fun_t< ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >
                                    ,OReportHelper> m_pMemberFunction;

        void    implReInsert( );
        void    implReRemove( );
        OReportSectionUndo(const OReportSectionUndo&);
        void operator =(const OReportSectionUndo&);
    public:
        TYPEINFO();
        //OReportSectionUndo(	 const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >& _xSection
        OReportSectionUndo(	OReportModel& rMod
                            ,sal_uInt16 _nSlot
                            ,::std::mem_fun_t< ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >
                                ,OReportHelper> _pMemberFunction
                            ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XReportDefinition >& _xReport
                            ,Action _eAction
                            ,USHORT nCommentID);
        virtual ~OReportSectionUndo();
    };

    /** Undo action for the group header, footer
    */
    class OGroupSectionUndo : public OSectionUndo
    {
        OGroupHelper								m_aGroupHelper;
        ::std::mem_fun_t< ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >
                                    ,OGroupHelper> m_pMemberFunction;

        mutable ::rtl::OUString                     m_sName;

        void    implReInsert( );
        void    implReRemove( );
        OGroupSectionUndo(const OGroupSectionUndo&);
        void operator =(const OGroupSectionUndo&);
    public:
        TYPEINFO();
        //OGroupSectionUndo(	 const ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >& _xSection
        OGroupSectionUndo(	OReportModel& rMod
                            ,sal_uInt16 _nSlot
                            ,::std::mem_fun_t< ::com::sun::star::uno::Reference< ::com::sun::star::report::XSection >
                                            ,OGroupHelper> _pMemberFunction
                            ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XGroup >& _xGroup
                            ,Action _eAction
                            ,USHORT nCommentID);

        virtual String		GetComment() const;
    };

    /** \class OToggleSlotUndo
     * \brief calls the slot every time an undo or redo action is performed.
    */
    class OToggleSlotUndo : public OCommentUndoAction
    {
        sal_uInt16 m_nSlot;
    public:
        TYPEINFO();
        OToggleSlotUndo(OReportModel& rMod,sal_uInt16 _nSlot,USHORT nCommentID);
        virtual void		Undo();
        virtual void		Redo();
    };

    /** /class OGroupUndo
     * \brief Undo action for removing a group object.
    */
    class OGroupUndo : public OCommentUndoAction
    {
        ::com::sun::star::uno::Reference< ::com::sun::star::report::XGroup>				m_xGroup; ///<! the group for the undo redo action
        ::com::sun::star::uno::Reference< ::com::sun::star::report::XReportDefinition >	m_xReportDefinition; ///<! the parent report definition
        Action																			m_eAction; ///<! the current action
        sal_Int32																		m_nLastPosition; ///<! the last position of the group

        void    implReInsert( );
        void    implReRemove( );
    public:
        TYPEINFO();
        OGroupUndo(OReportModel& rMod
                    ,USHORT nCommentID
                    ,Action	_eAction
                    ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XGroup>& _xGroup
                    ,const ::com::sun::star::uno::Reference< ::com::sun::star::report::XReportDefinition >& _xReportDefinition);
        virtual void		Undo();
        virtual void		Redo();
    };
}
#endif // RPTUI_UNDO_HXX
