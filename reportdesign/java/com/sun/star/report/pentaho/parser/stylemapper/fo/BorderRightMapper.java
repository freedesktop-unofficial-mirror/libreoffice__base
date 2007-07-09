/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: BorderRightMapper.java,v $
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


/*
 * BorderRightMapper.java
 *
 * Created on 16. Februar 2007, 13:00
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

package com.sun.star.report.pentaho.parser.stylemapper.fo;
import com.sun.star.report.pentaho.parser.StyleMapper;
import org.jfree.layouting.input.style.CSSDeclarationRule;
/**
 *
 * @author oj93728
 */
public class BorderRightMapper implements StyleMapper
{

  /** Creates a new instance of BorderRightMapper */
  public BorderRightMapper()
  {
  }
  public void updateStyle (String uri,
                           String attrName,
                           String attrValue,
                           CSSDeclarationRule targetRule)
  {
    targetRule.setPropertyValueAsString(attrName, attrValue);
  }
}
