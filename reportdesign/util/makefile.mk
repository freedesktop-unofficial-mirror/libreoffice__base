#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: rt $ $Date: 2007-07-09 11:56:41 $
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
PRJNAME=reportdesign
TARGET=rpt
TARGET2=$(TARGET)ui
# USE_DEFFILE=TRUE
GEN_HID=TRUE
GEN_HID_OTHER=TRUE
# ???
no_common_build_zip=true

# --- Settings ----------------------------------
.INCLUDE :	settings.mk
# ------------------------------------------------------------------

# --- reportdesign core (rpt) -----------------------------------

LIB1TARGET=$(SLB)$/$(TARGET).lib
LIB1FILES=\
        $(SLB)$/api.lib				\
        $(SLB)$/coreshared.lib		\
        $(SLB)$/core_resource.lib	\
        $(SLB)$/core_sdr.lib

SHL1TARGET=$(TARGET)$(UPD)$(DLLPOSTFIX)

SHL1STDLIBS= \
        $(SVXLIB)				\
        $(SFXLIB)				\
        $(TOOLSLIB) 			\
        $(SVLLIB)				\
        $(SVTOOLLIB)			\
        $(UNOTOOLSLIB)			\
        $(DBTOOLSLIB)			\
        $(COMPHELPERLIB) 		\
        $(CPPUHELPERLIB) 		\
        $(CPPULIB)				\
        $(VCLLIB)				\
        $(TKLIB)				\
        $(VOSLIB)				\
        $(SALLIB)
.IF "$(GUI)"=="WNT"
SHL1STDLIBS+= \
        idbu.lib
.ELSE
SHL1STDLIBS+= \
        -ldbu$(UPD)$(DLLPOSTFIX)
.ENDIF

SHL1IMPLIB=i$(TARGET)
SHL1USE_EXPORTS=ordinal
SHL1LIBS=$(LIB1TARGET)
SHL1DEF=$(MISC)$/$(SHL1TARGET).def

DEF1NAME=$(SHL1TARGET)
DEFLIB1NAME=$(TARGET)

# --- .res file ----------------------------------------------------------

RES1FILELIST=\
    $(SRS)$/core_strings.srs

RESLIB1NAME=$(TARGET)
RESLIB1IMAGES=$(PRJ)$/res
RESLIB1SRSFILES=$(RES1FILELIST)


# --- reportdesign UI core (rptui) -----------------------------------
LIB2TARGET=$(SLB)$/$(TARGET2).lib
LIB2FILES=\
        $(SLB)$/uimisc.lib			\
        $(SLB)$/uidlg.lib			\
        $(SLB)$/uishared.lib		\
        $(SLB)$/ui_inspection.lib	\
        $(SLB)$/report.lib

SHL2TARGET=$(TARGET2)$(UPD)$(DLLPOSTFIX)

SHL2STDLIBS= \
        $(SVXLIB)				\
        $(SFXLIB)				\
        $(SVTOOLLIB)			\
        $(TKLIB)				\
        $(VCLLIB)				\
        $(SVLLIB)				\
        $(SOTLIB)				\
        $(UNOTOOLSLIB)			\
        $(TOOLSLIB)				\
        $(DBTOOLSLIB)			\
        $(COMPHELPERLIB)		\
        $(CPPUHELPERLIB)		\
        $(CPPULIB)				\
        $(SO2LIB)				\
        $(I18NISOLANGLIB)		\
        $(SALLIB)
.IF "$(GUI)"=="WNT"
SHL2STDLIBS+= \
        idbu.lib				\
        i$(TARGET).lib
.ELSE
SHL2STDLIBS+= \
        -ldbu$(UPD)$(DLLPOSTFIX) \
        -l$(TARGET)$(UPD)$(DLLPOSTFIX)
.ENDIF

SHL2DEPN=$(SHL1TARGETN)
SHL2LIBS=$(LIB2TARGET)
SHL2DEF=$(MISC)$/$(SHL2TARGET).def
DEF2NAME=$(SHL2TARGET)
SHL2VERSIONMAP=$(TARGET2).map

# --- .res file ----------------------------------------------------------

RES2FILELIST=\
    $(SRS)$/uidlg.srs				\
    $(SRS)$/ui_inspection.srs		\
    $(SRS)$/report.srs


RESLIB2NAME=$(TARGET2)
RESLIB2IMAGES=$(PRJ)$/res
RESLIB2SRSFILES=$(RES2FILELIST)

# ------------------- rptxml -------------------
TARGET3=rptxml
# --- Library -----------------------------------
LIB3TARGET=$(SLB)$/rpt_flt.lib
LIB3FILES=\
        $(SLB)$/xmlshared.lib	\
        $(SLB)$/$(TARGET3).lib

SHL3TARGET=$(TARGET3)$(UPD)$(DLLPOSTFIX)

SHL3STDLIBS=\
    $(SVXLIB)			\
    $(XMLOFFLIB)		\
    $(VCLLIB)			\
    $(UNOTOOLSLIB)		\
    $(TOOLSLIB)			\
    $(DBTOOLSLIB)		\
    $(COMPHELPERLIB)	\
    $(CPPUHELPERLIB)	\
    $(CPPULIB)			\
    $(UCBHELPERLIB)		\
    $(SFXLIB)			\
    $(SVLLIB)			\
    $(SOTLIB)			\
    $(SO2LIB)			\
    $(SALLIB)
.IF "$(GUI)"=="WNT"
SHL3STDLIBS+= \
    irpt.lib
.ELSE
SHL3STDLIBS+= \
        -l$(TARGET)$(UPD)$(DLLPOSTFIX)
.ENDIF


SHL3DEPN=
SHL3LIBS=$(LIB3TARGET)
SHL3IMPLIB=	i$(SHL3TARGET)
SHL3VERSIONMAP=rptui.map
SHL3DEF=	$(MISC)$/$(SHL3TARGET).def

DEF3NAME=$(SHL3TARGET)

# create Extension -----------------------------

ZIP1TARGET=reportdesign
ZIP1FLAGS=-r
ZIP1DIR=$(OUT)$/zip
ZIP1LIST=*
ZIP1EXT=.oxt

XMLFILES := $(ZIP1DIR)$/description.xml \
            $(ZIP1DIR)$/META-INF$/manifest.xml

TXTFILES := $(ZIP1DIR)$/registration$/license_de.txt \
            $(ZIP1DIR)$/registration$/license_en_US.txt

HTMLFILES := $(ZIP1DIR)$/THIRDPARTYREADMELICENSE.html

REPRORTJARFILES := \
    $(ZIP1DIR)$/jcommon-1.0.10.jar										\
    $(ZIP1DIR)$/sac.jar													\
    $(ZIP1DIR)$/libxml-0.9.5.jar										\
    $(ZIP1DIR)$/flute-1.3-jfree-20061107.jar							\
    $(ZIP1DIR)$/jfreereport-0.9.0-05.jar								\
    $(ZIP1DIR)$/liblayout-0.2.6.jar										\
    $(ZIP1DIR)$/libloader-0.3.4.jar										\
    $(ZIP1DIR)$/libformula-0.1.8.jar									\
    $(ZIP1DIR)$/librepository-0.1.1.jar									\
    $(ZIP1DIR)$/libfonts-0.2.6.jar										\
    $(ZIP1DIR)$/jcommon-serializer-0.1.0.jar							\
    $(ZIP1DIR)$/reportdesign.jar

.INCLUDE : target.mk
# --- Targets ----------------------------------
.IF "$(ZIP1TARGETN)"!=""
$(ZIP1TARGETN) :  $(TXTFILES) $(XMLFILES) $(HTMLFILES) $(REPRORTJARFILES)
.ENDIF          # "$(ZIP1TARGETN)"!=""

$(ZIP1DIR)$/%.xml : %.xml
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(ZIP1DIR)$/%.jar : $(SOLARBINDIR)$/%.jar
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(ZIP1DIR)$/%.jar : $(CLASSDIR)$/%.jar
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@    

$(ZIP1DIR)$/META-INF$/%.xml : %.xml
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(ZIP1DIR)$/registration$/%.txt : %.txt
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(ZIP1DIR)$/THIRDPARTYREADMELICENSE.html : THIRDPARTYREADMELICENSE.html
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@
