/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: StyleDefinitionReadHandler.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:10 $
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


package com.sun.star.report.pentaho.parser.style;

import java.util.ArrayList;

import com.sun.star.report.pentaho.parser.ElementReadHandler;
import org.jfree.report.structure.Element;
import org.jfree.report.structure.Section;
import org.jfree.xmlns.parser.XmlReadHandler;
import org.xml.sax.Attributes;
import org.xml.sax.SAXException;

/**
 * Reads all childs of a style-definition. This simply copies everything that
 * is contained in the source-file into a generic structure that can be
 * written out later.
 */
public class StyleDefinitionReadHandler extends ElementReadHandler
{
  private Section rawSection;
  private ArrayList childs;

  public StyleDefinitionReadHandler()
  {
    this.rawSection = new Section();
    this.childs = new ArrayList();
  }

  /**
   * Returns the handler for a child element.
   *
   * @param tagName the tag name.
   * @param atts    the attributes.
   * @return the handler or null, if the tagname is invalid.
   *
   * @throws org.xml.sax.SAXException if there is a parsing error.
   */
  protected XmlReadHandler getHandlerForChild(final String uri,
                                              final String tagName,
                                              final Attributes atts)
      throws SAXException
  {
    final StyleDefinitionReadHandler readHandler =
        new StyleDefinitionReadHandler();
    childs.add(readHandler);
    return readHandler;
  }


  /**
   * Done parsing.
   *
   * @throws org.xml.sax.SAXException if there is a parsing error.
   */
  protected void doneParsing()
      throws SAXException
  {
    for (int i = 0; i < childs.size(); i++)
    {
      final ElementReadHandler handler = (ElementReadHandler) childs.get(i);
      rawSection.addNode(handler.getElement());
    }
  }


  public Element getElement()
  {
    return rawSection;
  }
}
