/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: AuthorFunction.java,v $
 * $Revision: 1.2 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
package com.sun.star.report.function.metadata;

import com.sun.star.report.ReportEngineParameterNames;
import org.jfree.formula.EvaluationException;
import org.jfree.formula.FormulaContext;
import org.jfree.formula.LibFormulaErrorValue;
import org.jfree.formula.function.Function;
import org.jfree.formula.function.ParameterCallback;
import org.jfree.formula.lvalues.TypeValuePair;
import org.jfree.formula.typing.coretypes.TextType;

/**
 *
 * @author Ocke Janssen
 */
public class AuthorFunction implements Function
{

    public AuthorFunction()
    {
    }

    public String getCanonicalName()
    {
        return "AUTHOR";
    }

    public TypeValuePair evaluate(final FormulaContext context,final ParameterCallback parameters)
            throws EvaluationException
    {
        if (parameters.getParameterCount() != 0)
        {
            throw new EvaluationException(LibFormulaErrorValue.ERROR_ARGUMENTS_VALUE);
        }

        return new TypeValuePair(TextType.TYPE, context.getConfiguration().getConfigProperty(ReportEngineParameterNames.AUTHOR));
    }
}
