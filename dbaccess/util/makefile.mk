#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.25 $
#
#   last change: $Author: rt $ $Date: 2005-09-08 16:54:13 $
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

PRJ=..
PRJNAME=dbaccess
TARGET=dba
TARGET2=dbu
USE_DEFFILE=TRUE
GEN_HID=TRUE
GEN_HID_OTHER=TRUE

# --- Settings ----------------------------------

.INCLUDE :	svpre.mk
.INCLUDE :	settings.mk
.INCLUDE :	sv.mk

LDUMP=ldump2.exe

# --- database core (dba) -----------------------------------

LIB1TARGET=$(SLB)$/dbaccess.lib
LIB1FILES=\
        $(SLB)$/api.lib	\
        $(SLB)$/dataaccess.lib	\
        $(SLB)$/misc.lib	\
        $(SLB)$/core_resource.lib	\
        $(SLB)$/dbashared.lib	

SHL1TARGET=$(TARGET)$(UPD)$(DLLPOSTFIX)

SHL1STDLIBS= \
        $(SVTOOLLIB) \
        $(VCLLIB) \
        $(UNOTOOLSLIB) \
        $(TOOLSLIB) \
        $(DBTOOLSLIB) \
        $(COMPHELPERLIB) \
        $(CPPUHELPERLIB) \
        $(UCBHELPERLIB) \
        $(SVLLIB)	\
        $(CPPULIB) \
        $(VOSLIB) \
        $(SALLIB)

SHL1LIBS=$(LIB1TARGET)
SHL1DEF=$(MISC)$/$(SHL1TARGET).def
DEF1NAME=$(SHL1TARGET)
SHL1VERSIONMAP=$(TARGET).map

# --- .res file ----------------------------------------------------------

RES1FILELIST=\
    $(SRS)$/core_strings.srs

RESLIB1NAME=$(TARGET)
RESLIB1IMAGES=$(PRJ)$/res
RESLIB1SRSFILES=$(RES1FILELIST)

# --- database ui (dbu) -----------------------------------

LIB2TARGET=$(SLB)$/$(TARGET2).lib
LIB2FILES=\
        $(SLB)$/relationdesign.lib	\
        $(SLB)$/tabledesign.lib		\
        $(SLB)$/querydesign.lib		\
        $(SLB)$/uimisc.lib			\
        $(SLB)$/uidlg.lib			\
        $(SLB)$/dbushared.lib		\
        $(SLB)$/browser.lib			\
        $(SLB)$/uiuno.lib			\
        $(SLB)$/app.lib				\
        $(SLB)$/uicontrols.lib

SHL2TARGET=$(TARGET2)$(UPD)$(DLLPOSTFIX)

SHL2STDLIBS= \
        $(SVXLIB)				\
        $(SFXLIB)				\
        $(BASICLIB)				\
        $(SVTOOLLIB)			\
        $(TKLIB)				\
        $(VCLLIB)				\
        $(GOODIESLIB)			\
        $(SVLLIB)				\
        $(SOTLIB)				\
        $(UNOTOOLSLIB)			\
        $(TOOLSLIB)				\
        $(UCBHELPERLIB) 		\
        $(DBTOOLSLIB)			\
        $(COMPHELPERLIB)		\
        $(CPPUHELPERLIB)		\
        $(CPPULIB)				\
        $(SO2LIB)				\
        $(VOSLIB)				\
        $(SALLIB)

SHL2LIBS=$(LIB2TARGET)
SHL2DEF=$(MISC)$/$(SHL2TARGET).def
DEF2NAME=$(SHL2TARGET)
SHL2VERSIONMAP=$(TARGET2).map

ALL: \
    $(LIB2TARGET)	\
    ALLTAR

# --- .res file ----------------------------------------------------------

RES2FILELIST=\
    $(SRS)$/uidlg.srs				\
    $(SRS)$/app.srs					\
    $(SRS)$/uicontrols.srs			\
    $(SRS)$/browser.srs				\
    $(SRS)$/uiuno.srs				\
    $(SRS)$/querydesign.srs			\
    $(SRS)$/tabledesign.srs			\
    $(SRS)$/relationdesign.srs		\
    $(SRS)$/uiimglst.srs			\
    $(SRS)$/uimisc.srs

.IF "$(GUI)"=="WNT"
#needed by 		$(SLO)$/adodatalinks.obj
SHL2STDLIBS+=		ole32.lib \
                    oleaut32.lib \
                    uuid.lib
.ENDIF

RESLIB2NAME=$(TARGET2)
RESLIB2IMAGES=$(PRJ)$/res
RESLIB2SRSFILES=$(RES2FILELIST)

# --- Targets ----------------------------------

.INCLUDE : target.mk
