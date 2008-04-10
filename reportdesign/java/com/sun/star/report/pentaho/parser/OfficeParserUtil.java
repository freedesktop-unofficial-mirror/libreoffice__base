/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: OfficeParserUtil.java,v $
 * $Revision: 1.4 $
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
package com.sun.star.report.pentaho.parser;

import java.util.Iterator;
import java.util.Properties;
import java.util.Map;
import java.util.HashMap;

import org.jfree.resourceloader.Resource;
import org.jfree.resourceloader.ResourceException;
import org.jfree.resourceloader.ResourceManager;
import org.jfree.util.DefaultConfiguration;
import org.jfree.util.Log;
import org.jfree.report.JFreeReportBoot;
import org.jfree.layouting.namespace.NamespaceDefinition;
import org.jfree.layouting.namespace.Namespaces;

public class OfficeParserUtil
{

    private static OfficeParserUtil instance;
    private static final String NAMESPACES_PREFIX = "namespaces.";

    public static synchronized OfficeParserUtil getInstance()
    {
        if (instance == null)
        {
            instance = new OfficeParserUtil();
        }
        return instance;
    }
    private DefaultConfiguration props;
    private NamespaceDefinition[] namespaces;

    private OfficeParserUtil()
    {
        props = new DefaultConfiguration();

        ResourceManager resourceManager = new ResourceManager();
        resourceManager.registerDefaults();
        try
        {
            final Resource res = resourceManager.createDirectly("res://com/sun/star/report/pentaho/parser/selectors.properties", Properties.class);
            final Properties resProps = (Properties) res.getResource();
            props.putAll(resProps);
        }
        catch (ResourceException e)
        {
            Log.warn("Unable to load mapping rules. Parsing services may not be available.", e);
        }

        namespaces = Namespaces.createFromConfig(JFreeReportBoot.getInstance().getGlobalConfig(),
                "org.jfree.report.namespaces.", resourceManager);
    }

    public NamespaceDefinition getNamespaceDeclaration(String uri)
    {
        if (uri == null)
        {
            throw new NullPointerException("URI must not be null");
        }

        for (int i = 0; i < namespaces.length; i++)
        {
            final NamespaceDefinition definition = namespaces[i];
            if (uri.equals(definition.getURI()))
            {
                return definition;
            }
        }
        return null;
    }

    public String getGenericFont(String officeFont)
    {
        return props.getProperty("font-family." + officeFont.toLowerCase(), officeFont);
    }

    public String getNamespaceURI(String namespacePrefix)
    {
        return props.getProperty(NAMESPACES_PREFIX + namespacePrefix);
    }

    public String getNamespaceForStyleFamily(String styleFamily)
    {
        return props.getProperty("style-family." + styleFamily);
    }

    public Map getNamespaces()
    {
        Map map = new HashMap();
        Iterator keys = props.findPropertyKeys(NAMESPACES_PREFIX);
        while (keys.hasNext())
        {
            String key = (String) keys.next();
            String value = props.getConfigProperty(key);
            map.put(key.substring(NAMESPACES_PREFIX.length()), value);
        }
        return map;
    }

    public String getNamespacePrefix(String namespaceURI)
    {
        Iterator keys = props.findPropertyKeys(NAMESPACES_PREFIX);
        while (keys.hasNext())
        {
            String key = (String) keys.next();
            String value = props.getConfigProperty(key);
            if (namespaceURI.equals(value))
            {
                return key.substring(NAMESPACES_PREFIX.length());
            }
        }
        return null;
    }

    public AttributeSpecification parseStyleAttrDefinition(final String key, final String prefix, final String tagname)
    {
        final String configPrefix = "attr." + prefix + "." + tagname + ".";
        final String configSuffix = key.substring(configPrefix.length());
        final int dotPosition = configSuffix.indexOf('.');
        if (dotPosition == -1)
        {
            return null;
        }
        final String namespaceUri = getNamespaceURI(configSuffix.substring(0, dotPosition));
        final String attrName = configSuffix.substring(dotPosition + 1);
        final String value = props.getProperty(key);
        return new AttributeSpecification(namespaceUri, attrName, value);
    }

    public Iterator findStylesForElement(final String prefix,
            final String tagname)
    {
        final String configPrefix = "attr." + prefix + "." + tagname + ".";
        return props.findPropertyKeys(configPrefix);
    }

    public boolean isValidStyleElement(String uri, String tagName)
    {
        final String prefix = getNamespacePrefix(uri);
        if (prefix == null)
        {
            return false;
        }

        final Iterator stylesForElement = findStylesForElement(prefix, tagName);
        return stylesForElement.hasNext();
    }

    public String getSelectorPattern()
    {
        return props.getConfigProperty("style-selector.pattern");
    }

    public static void main(String[] args)
    {
        JFreeReportBoot.getInstance().start();
        System.out.print(OfficeParserUtil.getInstance().getNamespaces());
    }
}
