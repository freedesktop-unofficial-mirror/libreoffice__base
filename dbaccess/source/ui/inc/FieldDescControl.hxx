/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: FieldDescControl.hxx,v $
 *
 *  $Revision: 1.14 $
 *
 *  last change: $Author: hr $ $Date: 2005-09-23 12:33:02 $
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
#ifndef DBAUI_FIELDDESCRIPTIONCONTROL_HXX
#define DBAUI_FIELDDESCRIPTIONCONTROL_HXX

#ifndef _SV_TABPAGE_HXX 
#include <vcl/tabpage.hxx>
#endif
#ifndef DBAUI_ENUMTYPES_HXX
#include "QEnumTypes.hxx"
#endif
#ifndef _COM_SUN_STAR_SDBC_XDATABASEMETADATA_HPP_
#include <com/sun/star/sdbc/XDatabaseMetaData.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XNUMBERFORMATTER_HPP_
#include <com/sun/star/util/XNumberFormatter.hpp>
#endif
#ifndef DBAUI_TYPEINFO_HXX
#include "TypeInfo.hxx"
#endif

//------------------------------------------------------------------
// die Spalten einer Feld-Beschreibung einer Tabelle
#define FIELD_NAME						1
#define FIELD_TYPE						2
#define FIELD_DESCR						3

#define FIELD_FIRST_VIRTUAL_COLUMN		4
                                        
#define FIELD_PROPERTY_REQUIRED			4
#define FIELD_PROPERTY_NUMTYPE			5
#define FIELD_PROPERTY_AUTOINC			6
#define FIELD_PROPERTY_DEFAULT			7
#define FIELD_PROPERTY_TEXTLEN			8
#define FIELD_PROPERTY_LENGTH			9
#define FIELD_PROPERTY_SCALE			10
#define FIELD_PROPERTY_BOOL_DEFAULT		11
#define FIELD_PROPERTY_FORMAT			12
#define FIELD_PRPOERTY_COLUMNNAME		13
#define FIELD_PRPOERTY_TYPE				14
#define FIELD_PRPOERTY_AUTOINCREMENT	15

class FixedText;
class PushButton;
class SvxNumberFormatShell;
class ScrollBar;
class Button;
class ListBox;
class Control;
class SvNumberFormatter;

namespace dbaui
{

    class OTableDesignHelpBar;
    class OPropListBoxCtrl;
    class OPropEditCtrl;
    class OPropNumericEditCtrl;
    class OFieldDescription;
    class OTypeInfo;
    class OPropColumnEditCtrl;
    //==================================================================
    class OFieldDescControl : public TabPage
    {
    private:
        OTableDesignHelpBar*	pHelp;
        Window*					pLastFocusWindow;
        Window*					m_pActFocusWindow;

        FixedText*				pDefaultText;
        FixedText*				pRequiredText;
        FixedText*				pAutoIncrementText;
        FixedText*				pTextLenText;
        FixedText*				pNumTypeText;
        FixedText*				pLengthText;
        FixedText*				pScaleText;
        FixedText*				pFormatText;
        FixedText*				pBoolDefaultText;
        FixedText*				m_pColumnNameText;
        FixedText*				m_pTypeText;
        FixedText*				m_pAutoIncrementValueText;

        OPropListBoxCtrl*		pRequired;
        OPropListBoxCtrl*		pNumType;
        OPropListBoxCtrl*		pAutoIncrement;
        OPropEditCtrl*			pDefault;
        OPropNumericEditCtrl*	pTextLen;
        OPropNumericEditCtrl*	pLength;
        OPropNumericEditCtrl*	pScale;
        OPropEditCtrl*			pFormatSample;
        OPropListBoxCtrl*		pBoolDefault;
        OPropColumnEditCtrl*	m_pColumnName;
        OPropListBoxCtrl*		m_pType;
        OPropEditCtrl*			m_pAutoIncrementValue;

        PushButton*				pFormat;

        ScrollBar*				m_pVertScroll;
        ScrollBar*				m_pHorzScroll;

        TOTypeInfoSP		m_pPreviousType;
        USHORT					nCurChildId;
        short					m_nPos;
        short					nOldDefaultPos;
        XubString				aYes;
        XubString				aNo;

        long					m_nOldVThumb;
        long					m_nOldHThumb;
        sal_Int32				m_nWidth;

        ULONG					nDelayedGrabFocusEvent;
        sal_Bool                m_bAdded;

        DECL_LINK( OnScroll, ScrollBar*);

        DECL_LINK( FormatClickHdl, Button * );
        DECL_LINK( ChangeHdl, ListBox * );

        DECL_LINK( DelayedGrabFocus, Control** );
            // von ActivatePropertyField benutzt
        DECL_LINK( OnControlFocusLost, Control* );
        DECL_LINK( OnControlFocusGot, Control* );

        void				UpdateFormatSample(OFieldDescription* pFieldDescr);
        void				ArrangeAggregates();

        void				SetPosSize( Control** ppControl, long nRow, USHORT nCol );

        void				ScrollAggregate(Control* pText, Control* pInput, Control* pButton, long nDeltaX, long nDeltaY);
        void				ScrollAllAggregates();

        sal_Bool			isTextFormat(const OFieldDescription* _pFieldDescr,sal_uInt32& _nFormatKey) const;
    protected:
        OFieldDescription*		pActFieldDescr; // falls geloescht werden soll
        sal_Bool				m_bRight;

        USHORT				CountActiveAggregates() const;

        virtual void		ActivateAggregate( EControlType eType );
        virtual void		DeactivateAggregate( EControlType eType );
        virtual BOOL		IsReadOnly() { return FALSE; };

        // Sind von den abgeleiteten Klassen zu impl.
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XNumberFormatter > GetFormatter() const = 0;
        
        virtual ::com::sun::star::lang::Locale	GetLocale() const = 0;

        virtual void							CellModified(long nRow, USHORT nColId ) = 0;
        virtual void							SetModified(BOOL bModified)				= 0;
                                                
        virtual TOTypeInfoSP					getTypeInfo(sal_Int32 _nPos)		= 0;
        virtual const OTypeInfoMap*				getTypeInfo() const  = 0;
                                                
        virtual sal_Bool						isAutoIncrementValueEnabled() const = 0; 
        virtual ::rtl::OUString					getAutoIncrementValue() const = 0; 

        String									BoolStringPersistent(const String& rUIString) const;
        String									BoolStringUI(const String& rPersistentString) const;

        const OPropColumnEditCtrl*				getColumnCtrl() const { return m_pColumnName; }

    public:
        OFieldDescControl( Window* pParent, OTableDesignHelpBar* pHelpBar);
        OFieldDescControl( Window* pParent, const ResId& rResId, OTableDesignHelpBar* pHelpBar);
        virtual ~OFieldDescControl();

        void				DisplayData(OFieldDescription* pFieldDescr );
        //	void				DisplayData(const OColumn* pColumn);

        void				SaveData( OFieldDescription* pFieldDescr );
        //	void				SaveData( OColumn* pColumn);

        void				SetControlText( USHORT nControlId, const String& rText );
        String				GetControlText( USHORT nControlId );
        void				SetReadOnly( BOOL bReadOnly );

        void				ActivatePropertyField(USHORT nVirtualField);
            // Parameter ist einer der FIELD_PROPERTY_xxx-Werte, das entsprechende Control wird aktiviert, wenn vorhanden

        // Resize aufegrufen
        void				CheckScrollBars();
        sal_Bool			isCutAllowed();
        sal_Bool			isCopyAllowed();
        sal_Bool			isPasteAllowed();

        void				cut();
        void				copy();
        void				paste();

        virtual void		Init();
        virtual void		GetFocus();
        virtual void		LoseFocus();
        virtual void		Resize();

        virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XDatabaseMetaData> getMetaData() = 0;
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection> getConnection() = 0;

        String				getControlDefault( const OFieldDescription* _pFieldDescr ,sal_Bool _bCheck = sal_True) const;

        inline void	setEditWidth(sal_Int32 _nWidth) { m_nWidth = _nWidth; }
    protected:
        void	implFocusLost(Window* _pWhich);
    };
}
#endif // DBAUI_FIELDDESCRIPTIONCONTROL_HXX


