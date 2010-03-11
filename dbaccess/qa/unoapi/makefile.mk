#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
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

PRJNAME=dbaccess
TARGET=qa_unoapi

.INCLUDE: settings.mk

.INCLUDE: target.mk


ALLTAR : UNOAPI_TEST

UNOAPI_TEST:	
    +$(SOLARENV)$/bin$/checkapi -sce dbaccess.sce -ini dbaccess.props -xcl knownissues.xcl -tdoc $(PWD)$/testdocuments
    @echo =======================================================================
    @echo In case of problems make sure that you put valid values in the dbaccess.props and added an appropriate jdbc-driver to your office installation
    @echo =======================================================================
    @echo In case of problems with TableWindowAccessibility or JoinViewAccessibility this might be because of connection problems, just re-run the testcases 
    @echo =======================================================================		

run_%:
    +$(SOLARENV)$/bin$/checkapi -o dbaccess.$(@:s/run_//) -ini dbaccess.props -xcl knownissues.xcl -tdoc $(PWD)$/testdocuments
