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
# $Revision: 1.4 $
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

PRJ=..$/..

PRJNAME = reportdesign
PACKAGE = complex
TARGET = rptdesigntest

# --- Settings -----------------------------------------------------

.INCLUDE :  settings.mk

# --- Files --------------------------------------------------------

JARFILES = ridl.jar jurt.jar unoil.jar juh.jar OOoRunner.jar

JAVAFILES =	ReportDesignerTest.java

# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk

# JAVADEBUG=-Xdebug -Xrunjdwp:transport=dt_socket,server=y,address=8502,suspend=y
JAVADEBUG=

MYSQL_CONNECTOR=$(PWD)$/mysql-connector-java-5.0.6-bin.jar
CLASSPATH!:=$(CLASSPATH)$(PATH_SEPERATOR)$(MYSQL_CONNECTOR)

run: ALLTAR
    $(PERL) mysql-connector-exists.pl $(MYSQL_CONNECTOR)
#	@echo $(CLASSPATH)
#	@echo $(VCSID)
    @java $(JAVADEBUG) -cp $(CLASSPATH) -DVCSID=$(VCSID) -DCWS_WORK_STAMP=$(CWS_WORK_STAMP) -DUPDMINOR=$(UPDMINOR) org.openoffice.Runner -ini runner.props 
