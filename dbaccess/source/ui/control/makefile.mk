#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.17 $
#
#   last change: $Author: obo $ $Date: 2004-11-17 14:48:26 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRUNTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRUNTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc..
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..$/..
PRJINC=$(PRJ)$/source
PRJNAME=dbaccess
TARGET=uicontrols

# --- Settings ----------------------------------

.INCLUDE : settings.mk

# --- Files -------------------------------------

# ... resource files ............................

SRS1NAME=$(TARGET)
SRC1FILES =	\
        TableGrantCtrl.src	\
        undosqledit.src		\
        tabletree.src		

# ... exception files .........................

EXCEPTIONSFILES=\
        $(SLO)$/statusbarontroller.obj	\
        $(SLO)$/RelationControl.obj		\
        $(SLO)$/toolboxcontroller.obj	\
        $(SLO)$/tabletree.obj			\
        $(SLO)$/TableGrantCtrl.obj		\
        $(SLO)$/dbtreelistbox.obj       \
        $(SLO)$/sqledit.obj				\
        $(SLO)$/ColumnControlWindow.obj	\
        $(SLO)$/FieldDescControl.obj

# ... object files ............................

SLOFILES=	\
        $(EXCEPTIONSFILES)				\
        $(SLO)$/ScrollHelper.obj		\
        $(SLO)$/VertSplitView.obj		\
        $(SLO)$/SqlNameEdit.obj			\
        $(SLO)$/listviewitems.obj		\
        $(SLO)$/undosqledit.obj			\
        $(SLO)$/marktree.obj			\
        $(SLO)$/curledit.obj

# --- Targets ----------------------------------

.INCLUDE : target.mk

