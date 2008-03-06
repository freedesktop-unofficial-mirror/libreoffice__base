#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: kz $ $Date: 2008-03-06 18:04:43 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

PRJ=..$/..$/..
PRJINC=$(PRJ)$/source
PRJNAME=dbaccess
TARGET=dbmm
USE_DEFFILE=TRUE

ENABLE_EXCEPTIONS=TRUE

# --- Settings ----------------------------------

.INCLUDE : settings.mk

# --- Files -------------------------------------

# ... resource files ............................

SRS1NAME=$(TARGET)
SRC1FILES =	\
        macromigration.src

# ... object files ............................
SLOFILES=   $(SLO)$/macromigrationwizard.obj \
            $(SLO)$/macromigrationdialog.obj \
            $(SLO)$/macromigrationpages.obj \
            $(SLO)$/dbmm_module.obj \
            $(SLO)$/dbmm_services.obj \
            $(SLO)$/migrationengine.obj \
            $(SLO)$/docerrorhandling.obj \
            $(SLO)$/progresscapture.obj \
            $(SLO)$/migrationlog.obj \

# --- library -----------------------------------

SHL1TARGET=$(TARGET)$(DLLPOSTFIX)
SHL1VERSIONMAP=$(TARGET).map

SHL1STDLIBS= \
        $(CPPULIB)          \
        $(CPPUHELPERLIB)    \
        $(COMPHELPERLIB)    \
        $(UNOTOOLSLIB)      \
        $(TOOLSLIB)         \
        $(SALLIB)           \
        $(SVTOOLLIB)        \
        $(SVLLIB)           \
        $(VCLLIB)           \
        $(SVXLIB)

SHL1LIBS=       $(SLB)$/$(TARGET).lib
SHL1IMPLIB=     i$(TARGET)
SHL1DEPN=       $(SHL1LIBS)
SHL1DEF=        $(MISC)$/$(SHL1TARGET).def

DEF1NAME=       $(SHL1TARGET)

# --- .res files -------------------------------

RES1FILELIST=\
    $(SRS)$/$(TARGET).srs

RESLIB1NAME=$(TARGET)
RESLIB1IMAGES=$(PRJ)$/res
RESLIB1SRSFILES=$(RES1FILELIST)

# --- Targets ----------------------------------

.INCLUDE : target.mk

