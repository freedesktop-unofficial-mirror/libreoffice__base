/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: InputRepositoryLoader.java,v $
 * $Revision: 1.3 $
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


package com.sun.star.report.pentaho.loader;

import java.net.URL;
import java.util.Map;
import java.util.HashMap;

import com.sun.star.report.InputRepository;
import org.jfree.resourceloader.ResourceData;
import org.jfree.resourceloader.ResourceKey;
import org.jfree.resourceloader.ResourceKeyCreationException;
import org.jfree.resourceloader.ResourceLoader;
import org.jfree.resourceloader.ResourceLoadingException;
import org.jfree.resourceloader.ResourceManager;
import org.jfree.resourceloader.loader.LoaderUtils;

public class InputRepositoryLoader implements ResourceLoader
{
  private InputRepository inputRepository;
  private ResourceManager resourceManager;

  public InputRepositoryLoader (final InputRepository inputRepository)
  {
    if (inputRepository == null)
    {
      throw new NullPointerException();
    }
    this.inputRepository = inputRepository;
  }

  /**
   * Checks, whether this resource loader implementation was responsible for
   * creating this key.
   *
   * @param key
   * @return
   */
  public boolean isSupportedKey(final ResourceKey key)
  {
    if (InputRepositoryLoader.class.getName().equals(key.getSchema()))
    {
      return true;
    }
    return false;
  }

  /**
   * Creates a new resource key from the given object and the factory keys.
   *
   * @param value
   * @param factoryKeys
   * @return the created key or null, if the format was not recognized.
   * @throws org.jfree.resourceloader.ResourceKeyCreationException
   *          if creating the key failed.
   */
  public ResourceKey createKey(final Object value,
                               final Map factoryKeys)
      throws ResourceKeyCreationException
  {
    if (value instanceof String == false)
    {
      return null;
    }
    final String strVal = (String) value;
    if (strVal.startsWith("sun:oo://") == false)
    {
      return null;
    }
    return new ResourceKey(InputRepositoryLoader.class.getName(),
        new InputResourceKey(inputRepository.getId(), strVal), factoryKeys);
  }

  /**
   * Derives a new resource key from the given key. If neither a path nor new
   * factory-keys are given, the parent key is returned.
   *
   * @param parent      the parent
   * @param path        the derived path (can be null).
   * @param factoryKeys the optional factory keys (can be null).
   * @return the derived key.
   * @throws org.jfree.resourceloader.ResourceKeyCreationException
   *          if the key cannot be derived for any reason.
   */
  public ResourceKey deriveKey(final ResourceKey parent,
                               final String path,
                               final Map factoryKeys)
      throws ResourceKeyCreationException
  {
    if (isSupportedKey(parent) == false)
    {
      throw new ResourceKeyCreationException("Assertation: Unsupported parent key type");
    }

    final InputResourceKey parentKey = (InputResourceKey) parent.getIdentifier();
    final String resource;
    if (path.startsWith("sun:oo://"))
    {
      resource = path;
    }
    else if (path.startsWith("/"))
    {
      resource = "sun:oo:/" + path;
    }
    else
    {
      resource = LoaderUtils.mergePaths(parentKey.getPath(), path);
    }
    final Map map;
    if (factoryKeys != null)
    {
      map = new HashMap();
      map.putAll(parent.getFactoryParameters());
      map.putAll(factoryKeys);
    }
    else
    {
      map = parent.getFactoryParameters();
    }
    return new ResourceKey(parent.getSchema(),
        new InputResourceKey(parentKey.getInputRepositoryId(), resource), map);
  }

  public URL toURL(final ResourceKey key)
  {
    return null;
  }

  public ResourceData load (final ResourceKey key)
          throws ResourceLoadingException
  {
    if (isSupportedKey(key) == false)
    {
      throw new ResourceLoadingException("None of my keys.");
    }

    return new InputRepositoryResourceData(key, inputRepository);
  }

  public void setResourceManager (final ResourceManager manager)
  {
    this.resourceManager = manager;
  }

  public ResourceManager getResourceManager ()
  {
    return resourceManager;
  }
}
