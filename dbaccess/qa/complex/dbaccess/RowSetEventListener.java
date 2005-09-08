/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: RowSetEventListener.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 09:48:54 $
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

package complex.dbaccess;

import com.sun.star.sdb.XRowSetApproveListener;
import com.sun.star.sdbc.XRowSetListener;
import com.sun.star.sdb.RowChangeEvent;
import com.sun.star.lang.EventObject;
import com.sun.star.beans.XPropertyChangeListener;

public class RowSetEventListener implements XRowSetApproveListener,XRowSetListener,XPropertyChangeListener
{
    public static final int APPROVE_CURSOR_MOVE = 0;
    public static final int APPROVE_ROW_CHANGE  = 1;
    public static final int COLUMN_VALUE        = 2;
    public static final int CURSOR_MOVED        = 3;
    public static final int ROW_CHANGED         = 4;
    public static final int IS_MODIFIED         = 5;
    public static final int IS_NEW              = 6;
    public static final int ROW_COUNT           = 7;
    public static final int IS_ROW_COUNT_FINAL  = 8;    
    
    RowSet rowset;
    int callPos = 1;
    int calling [];
    
    RowSetEventListener(RowSet _rowset){
        rowset = _rowset;
        calling = new int [9];
        clearCalling();
    }
    public int[] getCalling(){
        return calling;
    }
    public void clearCalling(){
        for(int i = 0 ; i < calling.length; ++i){
            calling[i] = -1;
        }
        callPos = 1;
    }
    // XEventListener
    public void disposing(com.sun.star.lang.EventObject event)
    {
    }
    // XRowSetApproveBroadcaster
    public boolean approveCursorMove(EventObject event)
    {
        calling[APPROVE_CURSOR_MOVE] = callPos++;
        return true;
    }
    public boolean approveRowChange(RowChangeEvent event)
    {
        calling[APPROVE_ROW_CHANGE] = callPos++;
        return true;
    }
    public boolean approveRowSetChange(EventObject event)
    {
        return true;
    }

    // XRowSetListener
    public void cursorMoved(com.sun.star.lang.EventObject event)
    {
        calling[CURSOR_MOVED] = callPos++;
    }
    public void rowChanged(com.sun.star.lang.EventObject event)
    {
        calling[ROW_CHANGED] = callPos++;
    }
    public void rowSetChanged(com.sun.star.lang.EventObject event)
    {
    }

    public void propertyChange(com.sun.star.beans.PropertyChangeEvent propertyChangeEvent) {
        if ( propertyChangeEvent.PropertyName.equals("Value") ){
            calling[COLUMN_VALUE] = callPos++;
        } else if ( propertyChangeEvent.PropertyName.equals("IsModified") ){
            calling[IS_MODIFIED] = callPos++;
        } else if ( propertyChangeEvent.PropertyName.equals("IsNew") ){
            calling[IS_NEW] = callPos++;
        } else if ( propertyChangeEvent.PropertyName.equals("RowCount") ){
            calling[ROW_COUNT] = callPos++;
        } else if ( propertyChangeEvent.PropertyName.equals("IsRowCountFinal") ){
            calling[IS_ROW_COUNT_FINAL] = callPos++;
        }
    }

}
