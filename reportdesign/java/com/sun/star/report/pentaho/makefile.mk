#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.7 $
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

PRJ	= ..$/..$/..$/..$/..$/..
PRJNAME = reportdesign
TARGET  = sun-report-builder
PACKAGE = com$/sun$/star$/report$/pentaho
# we have circular dependencies
nodep=true
# --- Settings -----------------------------------------------------
.INCLUDE: settings.mk

#----- compile .java files -----------------------------------------
JARFILES        = ridl.jar unoil.jar jurt.jar juh.jar jut.jar java_uno.jar
.IF "$(SYSTEM_JFREEREPORT)" == "YES"
XCLASSPATH!:=$(XCLASSPATH)$(PATH_SEPERATOR)$(JCOMMON_JAR)$(PATH_SEPERATOR)$(LIBXML_JAR)$(PATH_SEPERATOR)$(JFREEREPORT_JAR)$(PATH_SEPERATOR)$(LIBLOADER_JAR)$(PATH_SEPERATOR)$(SAC_JAR)$(PATH_SEPERATOR)$(LIBLAYOUT_JAR)$(PATH_SEPERATOR)$(JCOMMON_SERIALIZER_JAR)$(PATH_SEPERATOR)$(LIBFONTS_JAR)$(PATH_SEPERATOR)$(LIBFORMULA_JAR)$(PATH_SEPERATOR)librepository-0.1.4.jar
.ELSE
JARFILES += flute-1.3-jfree-20061107.jar jcommon-1.0.10.jar	jcommon-serializer-0.2.0.jar libfonts-0.3.3.jar libformula-0.1.14.jar liblayout-0.2.8.jar libloader-0.3.6.jar librepository-0.1.4.jar libxml-0.9.9.jar pentaho-reporting-flow-engine-0.9.2.jar sac.jar
.ENDIF

JAVAFILES       := $(shell @$(FIND) . -name "*.java")
# JAVACLASSFILES	= $(foreach,i,$(JAVAFILES) $(CLASSDIR)$/$(PACKAGE)$/$(i:s/.java/.class/))

#----- copy .properties and .css files -----------------------------------------
# external find gives / for 4nt too...
# PROPERTYFILES := $(subst,/,$/ $(subst,./,$(CLASSDIR)$/$(PACKAGE)$/ $(shell @$(FIND) . -name "*.properties")))
PROPERTYFILES := $(CLASSDIR)$/$(PACKAGE)$/configuration.properties \
                 $(CLASSDIR)$/$(PACKAGE)$/module.properties \
                 $(CLASSDIR)$/$(PACKAGE)$/parser$/selectors.properties
                 
# CSSFILES := $(subst,./,$(CLASSDIR)$/$(PACKAGE)$/ $(shell @$(FIND) . -name "*.css"))
CSSFILES := $(CLASSDIR)$/$(PACKAGE)$/oasis-datastyle.css\
            $(CLASSDIR)$/$(PACKAGE)$/oasis-draw.css\
            $(CLASSDIR)$/$(PACKAGE)$/oasis-form.css\
            $(CLASSDIR)$/$(PACKAGE)$/oasis-style.css\
            $(CLASSDIR)$/$(PACKAGE)$/oasis-table.css\
            $(CLASSDIR)$/$(PACKAGE)$/oasis-text.css\
            $(CLASSDIR)$/$(PACKAGE)$/smil.css\
            $(CLASSDIR)$/$(PACKAGE)$/star-office.css\
            $(CLASSDIR)$/$(PACKAGE)$/star-report.css\
            $(CLASSDIR)$/$(PACKAGE)$/star-rpt.css\
            $(CLASSDIR)$/$(PACKAGE)$/svg.css\
            $(CLASSDIR)$/$(PACKAGE)$/xsl-fo.css

XSDFILES := $(CLASSDIR)$/$(PACKAGE)$/parser$/rpt-schema-v1.0-os.xsd \
            $(CLASSDIR)$/$(PACKAGE)$/styles$/stylemapper.xsd
            
XMLFILES := $(CLASSDIR)$/$(PACKAGE)$/styles$/stylemapper.xml
            
TXTFILES := $(CLASSDIR)$/$(PACKAGE)$/parser$/style-mapping.txt

            
#----- make a jar from compiled files ------------------------------

JARCLASSDIRS    = .
JARTARGET       = $(TARGET).jar
JARCOMPRESS 	= TRUE
CUSTOMMANIFESTFILE = Manifest.mf


# --- Targets ------------------------------------------------------
.INCLUDE :  target.mk

.IF "$(JARTARGETN)"!=""
$(JARTARGETN) : $(PROPERTYFILES) $(CSSFILES) $(XSDFILES) $(TXTFILES) $(XMLFILES)
.ENDIF          # "$(JARTARGETN)"!=""

$(CLASSDIR)$/$(PACKAGE)$/%.properties : %.properties
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(CLASSDIR)$/$(PACKAGE)$/%.css : %.css
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@

$(CLASSDIR)$/$(PACKAGE)$/%.xsd : %.xsd
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@
    
$(CLASSDIR)$/$(PACKAGE)$/%.xml : %.xml
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@    

$(CLASSDIR)$/$(PACKAGE)$/%.txt : %.txt
    @@-$(MKDIRHIER) $(@:d)
    $(COPY) $< $@
    
