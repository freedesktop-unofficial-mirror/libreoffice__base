#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2011 Oracle and/or its affiliates.
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

$(eval $(call gb_Module_Module,dbaccess))

$(eval $(call gb_Module_add_targets,dbaccess,\
	AllLangResTarget_adabasui \
	AllLangResTarget_dba\
	AllLangResTarget_dbmm\
	AllLangResTarget_dbui\
	AllLangResTarget_sdbt\
	Library_adabasui\
	Library_dba\
	Library_dbaxml\
	Library_dbmm\
	Library_dbui\
	Library_sdbt\
	Executable_odbcconfig \
	Package_inc \
	Package_uiconfig \
	Package_xml \
))

$(eval $(call gb_Module_add_subsequentcheck_targets,dbaccess,\
	JunitTest_dbaccess_complex \
	JunitTest_dbaccess_unoapi \
))

# vim: set noet ts=4 sw=4:
