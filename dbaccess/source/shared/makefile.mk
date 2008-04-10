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
# $Revision: 1.10 $
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
PRJINC=$(PRJ)$/source
PRJNAME=dbaccess
LIBTARGET=NO
TARGET=shared
LIB1TARGET=$(SLB)$/dbashared.lib
LIB2TARGET=$(SLB)$/dbushared.lib
LIB3TARGET=$(SLB)$/fltshared.lib
LIB4TARGET=$(SLB)$/cfgshared.lib
LIB5TARGET=$(SLB)$/sdbtshared.lib

#ENABLE_EXCEPTIONS=TRUE

# --- Settings ----------------------------------

.INCLUDE : settings.mk

# --- Types -------------------------------------

# --- Files -------------------------------------
EXCEPTIONSFILES=	\
        $(SLO)$/apitools.obj	\
        $(SLO)$/dbu_reghelper.obj	\
        $(SLO)$/cfg_reghelper.obj	\
        $(SLO)$/flt_reghelper.obj
        
SLOFILES=	\
        $(EXCEPTIONSFILES)			\
        $(SLO)$/cfgstrings.obj		\
        $(SLO)$/xmlstrings.obj		\
        $(SLO)$/dbastrings.obj		\
        $(SLO)$/dbustrings.obj


LIB1OBJFILES=	\
        $(SLO)$/dbastrings.obj	\
        $(SLO)$/apitools.obj
        
LIB2OBJFILES=	\
        $(SLO)$/dbu_reghelper.obj	\
        $(SLO)$/dbustrings.obj
        
LIB3OBJFILES=	\
        $(SLO)$/flt_reghelper.obj	\
        $(SLO)$/xmlstrings.obj
        
LIB4OBJFILES=	\
        $(SLO)$/cfg_reghelper.obj	\
        $(SLO)$/cfgstrings.obj

LIB5OBJFILES=	\
        $(SLO)$/sdbtstrings.obj

# --- Targets ----------------------------------

.INCLUDE : target.mk

