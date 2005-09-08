/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: TableConnectionData.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 15:35:10 $
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
#ifndef DBAUI_TABLECONNECTIONDATA_HXX
#define DBAUI_TABLECONNECTIONDATA_HXX

#ifndef DBAUI_CONNECTIONLINEDATA_HXX
#include "ConnectionLineData.hxx"
#endif
#include <vector>
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif
#ifndef _STRING_HXX
#include <tools/string.hxx>
#endif

namespace dbaui
{
#define MAX_CONN_COUNT 2
    //==================================================================
    // ConnData		---------->*	ConnLineData
    //    ^1							^1
    //    |								|
    //	Conn		---------->*	ConnLine
    //==================================================================

    
    //==================================================================
    /*
        the class OTableConnectionData contains all connection data which exists between	two windows
    **/
    class OTableConnectionData
    {
        
    protected:
        String m_aSourceWinName;
        String m_aDestWinName;
        String m_aConnName;

        OConnectionLineDataVec m_vConnLineData;

        void	Init();
        void	Init(const String& rSourceWinName, const String& rDestWinName, const String& rConnName = String() );
            // Das erste Init baut darauf, dass die 3 String-Members schon korrekt gesetzt sind und aConnLineDataList leer ist.
            // Das zweite stellt genau diesen Zustand her

        virtual OConnectionLineDataRef CreateLineDataObj();
        virtual OConnectionLineDataRef CreateLineDataObj( const OConnectionLineData& rConnLineData );

        OTableConnectionData& operator=( const OTableConnectionData& rConnData );
    public:
        TYPEINFO();
        OTableConnectionData();
        OTableConnectionData( const String& rSourceWinName, const String& rDestWinName, const String& rConnName = String() );
        OTableConnectionData( const OTableConnectionData& rConnData );
        virtual ~OTableConnectionData();

        // sich aus einer Quelle initialisieren (das ist mir irgendwie angenehmer als ein virtueller Zuweisungsoperator)
        virtual void CopyFrom(const OTableConnectionData& rSource);

        // eine neue Instanz meines eigenen Typs liefern (braucht NICHT initialisiert sein)
        virtual OTableConnectionData* NewInstance() const;
            // (von OTableConnectionData abgeleitete Klasse muessen entsprechend eine Instanz ihrer Klasse liefern)

        

        BOOL SetConnLine( USHORT nIndex, const String& rSourceFieldName, const String& rDestFieldName );
        BOOL AppendConnLine( const ::rtl::OUString& rSourceFieldName, const ::rtl::OUString& rDestFieldName );
        void ResetConnLines( BOOL bUseDefaults = TRUE );

        /** normalizeLines moves the empty lines to the back
        */
        void normalizeLines();
            // loescht die Liste der ConnLines, bei bUseDefaults == TRUE werden danach MAX_CONN_COUNT neue Dummy-Linien eingefuegt

        OConnectionLineDataVec* GetConnLineDataList(){ return &m_vConnLineData; }

        String GetSourceWinName() const { return m_aSourceWinName; }
        String GetDestWinName() const { return m_aDestWinName; }
        String GetConnName() const { return m_aConnName; }

        virtual void SetSourceWinName( const String& rSourceWinName ){ m_aSourceWinName = rSourceWinName; }
        virtual void SetDestWinName( const String& rDestWinName ){ m_aDestWinName = rDestWinName; }
        virtual void SetConnName( const String& rConnName ){ m_aConnName = rConnName; }
        /** Update create a new connection

            @return true if successful
        */
        virtual BOOL Update(){ return TRUE; }
    };

}
#endif // DBAUI_TABLECONNECTIONDATA_HXX


