/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OfficeDocument.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:06 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2007 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *    Copyright 2007 by Pentaho Corporation
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/


package com.sun.star.report.pentaho.model;

import org.jfree.report.JFreeReport;

/**
 * An office document represents the root of the report processing. In
 * OpenOffice reports, this is the only child of the report object.
 *
 * @author Thomas Morgner
 * @since 02.03.2007
 */
public class OfficeDocument extends JFreeReport
{
  private OfficeStylesCollection stylesCollection;

  public OfficeDocument()
  {
  }

  public OfficeStylesCollection getStylesCollection()
  {
    return stylesCollection;
  }

  public void setStylesCollection(final OfficeStylesCollection stylesCollection)
  {
    if (stylesCollection == null)
    {
      throw new NullPointerException();
    }
    this.stylesCollection = stylesCollection;
  }
}
