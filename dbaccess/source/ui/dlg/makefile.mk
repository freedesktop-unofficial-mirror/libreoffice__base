 #########################################################################
 #
 #  $RCSfile: makefile.mk,v $
 #
 #  $Revision: 1.21 $
 #
 #  last change: $Author: oj $ $Date: 2002-04-29 08:27:33 $
 #
 #  The Contents of this file are made available subject to the terms of
 #  either of the following licenses
 #
 #         - GNU Lesser General Public License Version 2.1
 #         - Sun Industry Standards Source License Version 1.1
 #
 #  Sun Microsystems Inc., October, 2000
 #
 #  GNU Lesser General Public License Version 2.1
 #  =============================================
 #  Copyright 2000 by Sun Microsystems, Inc.
 #  901 San Antonio Road, Palo Alto, CA 94303, USA
 #
 #  This library is free software; you can redistribute it and/or
 #  modify it under the terms of the GNU Lesser General Public
 #  License version 2.1, as published by the Free Software Foundation.
 #
 #  This library is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 #  Lesser General Public License for more details.
 #
 #  You should have received a copy of the GNU Lesser General Public
 #  License along with this library; if not, write to the Free Software
 #  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 #  MA  02111-1307  USA
 #
 #
 #  Sun Industry Standards Source License Version 1.1
 #  =================================================
 #  The contents of this file are subject to the Sun Industry Standards
 #  Source License Version 1.1 (the "License"); You may not use this file
 #  except in compliance with the License. You may obtain a copy of the
 #  License at http://www.openoffice.org/license.html.
 #
 #  Software provided under this License is provided on an "AS IS" basis,
 #  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
 #  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 #  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 #  See the License for the specific provisions governing your rights and
 #  obligations concerning the Software.
 #
 #  The Initial Developer of the Original Code is: Sun Microsystems, Inc..
 #
 #  Copyright: 2000 by Sun Microsystems, Inc.
 #
 #  All Rights Reserved.
 #
 #  Contributor(s): _______________________________________
 #
 #
 ########################################################################/

PRJ=..$/..$/..
PRJINC=$(PRJ)$/source
PRJNAME=dbaccess
TARGET=uidlg

# --- Settings ----------------------------------

.INCLUDE : settings.mk
IMGLST_SRS=$(SRS)$/$(TARGET).srs
# --- Files -------------------------------------

# ... resource files ............................

BMP_IN=$(PRJ)$/res

SRCFILES =	\
        UserAdmin.src	\
        directsql.src	\
        missingdocdlg.src	\
        doclinkdialog.src	\
        AdabasStat.src	\
        AdabasPage.src	\
        indexdialog.src	\
        RelationDlg.src	\
        adtabdlg.src	\
        dlgsave.src		\
        queryorder.src	\
        queryfilter.src	\
        paramdialog.src	\
        dsselect.src	\
        dbadmin.src		\
        dbfindex.src	\
        dlgsize.src		\
        dlgattr.src		\
        sqlmessage.src

# ... object files ............................

SLOFILES=	\
        $(SLO)$/datasourceselector.obj	\
        $(SLO)$/datasourcemap.obj	\
        $(SLO)$/UserAdmin.obj	\
        $(SLO)$/directsql.obj	\
        $(SLO)$/generalpage.obj	\
        $(SLO)$/tablespage.obj	\
        $(SLO)$/missingdocdlg.obj	\
        $(SLO)$/doclinkdialog.obj	\
        $(SLO)$/AdabasStat.obj	\
        $(SLO)$/AdabasPage.obj	\
        $(SLO)$/indexfieldscontrol.obj	\
        $(SLO)$/indexdialog.obj	\
        $(SLO)$/RelationDlg.obj	\
        $(SLO)$/adtabdlg.obj	\
        $(SLO)$/dlgsave.obj		\
        $(SLO)$/dlgsize.obj		\
        $(SLO)$/dlgattr.obj		\
        $(SLO)$/queryorder.obj	\
        $(SLO)$/queryfilter.obj	\
        $(SLO)$/paramdialog.obj	\
        $(SLO)$/odbcconfig.obj	\
        $(SLO)$/dsselect.obj	\
        $(SLO)$/dbadmin.obj		\
        $(SLO)$/commonpages.obj	\
        $(SLO)$/detailpages.obj	\
        $(SLO)$/adminpages.obj	\
        $(SLO)$/sqlmessage.obj	\
        $(SLO)$/dbfindex.obj

EXCEPTIONSFILES=	\
        $(SLO)$/datasourcemap.obj	\
        $(SLO)$/UserAdmin.obj	\
        $(SLO)$/directsql.obj	\
        $(SLO)$/generalpage.obj	\
        $(SLO)$/tablespage.obj	\
        $(SLO)$/doclinkdialog.obj	\
        $(SLO)$/AdabasStat.obj	\
        $(SLO)$/AdabasPage.obj	\
        $(SLO)$/indexfieldscontrol.obj	\
        $(SLO)$/indexdialog.obj	\
        $(SLO)$/RelationDlg.obj	\
        $(SLO)$/adtabdlg.obj	\
        $(SLO)$/dlgsave.obj		\
        $(SLO)$/queryorder.obj	\
        $(SLO)$/queryfilter.obj	\
        $(SLO)$/paramdialog.obj	\
        $(SLO)$/dbadmin.obj		\
        $(SLO)$/commonpages.obj	\
        $(SLO)$/detailpages.obj	\
        $(SLO)$/sqlmessage.obj	\
        $(SLO)$/dbfindex.obj

# --- Targets ----------------------------------

.INCLUDE : target.mk


 #########################################################################
 # history:
 #	$Log: not supported by cvs2svn $
 #	Revision 1.20  2001/06/25 16:05:58  fs
 #	#88004# +datasourceselector.cxx / +datasourcemap.cxx
 #	
 #	Revision 1.19  2001/06/20 07:10:07  oj
 #	#88434# new page for user admin
 #	
 #	Revision 1.18  2001/06/19 11:00:02  fs
 #	#88393# +directsql.*
 #	
 #	Revision 1.0 20.09.00 10:58:55  fs
 ########################################################################/

