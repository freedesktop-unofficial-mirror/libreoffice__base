/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: OfficeDocumentReportTarget.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2007-07-09 11:56:07 $
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


package com.sun.star.report.pentaho.output;

import java.awt.Image;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Reader;
import java.io.StringWriter;
import java.io.Writer;
import java.util.Iterator;
import java.util.Map;
import java.util.zip.DeflaterOutputStream;
import java.util.zip.InflaterInputStream;

import com.sun.star.report.ImageService;
import com.sun.star.report.InputRepository;
import com.sun.star.report.OutputRepository;
import com.sun.star.report.pentaho.OfficeNamespaces;
import com.sun.star.report.pentaho.layoutprocessor.ImageElementContext;
import com.sun.star.report.pentaho.model.OfficeDocument;
import com.sun.star.report.pentaho.model.OfficeStyle;
import com.sun.star.report.pentaho.model.OfficeStyles;
import com.sun.star.report.pentaho.model.OfficeStylesCollection;
import com.sun.star.report.pentaho.styles.LengthCalculator;
import com.sun.star.report.pentaho.styles.StyleMapper;
import org.jfree.io.IOUtils;
import org.jfree.layouting.input.style.parser.CSSValueFactory;
import org.jfree.layouting.input.style.parser.StyleSheetParserUtil;
import org.jfree.layouting.input.style.values.CSSNumericValue;
import org.jfree.layouting.layouter.style.CSSValueResolverUtility;
import org.jfree.layouting.namespace.NamespaceDefinition;
import org.jfree.layouting.namespace.Namespaces;
import org.jfree.layouting.util.AttributeMap;
import org.jfree.report.DataFlags;
import org.jfree.report.DataSourceException;
import org.jfree.report.JFreeReportBoot;
import org.jfree.report.JFreeReportInfo;
import org.jfree.report.ReportProcessingException;
import org.jfree.report.flow.AbstractReportTarget;
import org.jfree.report.flow.ReportJob;
import org.jfree.report.flow.ReportStructureRoot;
import org.jfree.report.flow.ReportTargetUtil;
import org.jfree.report.structure.Element;
import org.jfree.report.structure.Section;
import org.jfree.report.util.AttributeNameGenerator;
import org.jfree.report.util.IntegerCache;
import org.jfree.report.util.MemoryByteArrayOutputStream;
import org.jfree.resourceloader.ResourceException;
import org.jfree.resourceloader.ResourceKey;
import org.jfree.resourceloader.ResourceManager;
import org.jfree.util.FastStack;
import org.jfree.util.LineBreakIterator;
import org.jfree.util.Log;
import org.jfree.xmlns.common.AttributeList;
import org.jfree.xmlns.writer.DefaultTagDescription;
import org.jfree.xmlns.writer.XmlWriter;
import org.jfree.xmlns.writer.XmlWriterSupport;
import org.w3c.css.sac.LexicalUnit;

/**
 * Todo: Document me!
 *
 * @author Thomas Morgner
 * @since 08.03.2007
 */
public abstract class OfficeDocumentReportTarget extends AbstractReportTarget
{
  public static final String TAG_DEF_PREFIX = "com.sun.star.report.pentaho.output.";

  public static final int ROLE_NONE = 0;
  public static final int ROLE_REPORT_HEADER = 1;
  public static final int ROLE_REPORT_FOOTER = 2;
  public static final int ROLE_GROUP_HEADER = 3;
  public static final int ROLE_GROUP_FOOTER = 4;
  public static final int ROLE_REPEATING_GROUP_HEADER = 5;
  public static final int ROLE_REPEATING_GROUP_FOOTER = 6;
  public static final int ROLE_PAGE_HEADER = 7;
  public static final int ROLE_PAGE_FOOTER = 8;
  public static final int ROLE_DETAIL = 9;
  public static final int ROLE_VARIABLES = 10;
  public static final int ROLE_TEMPLATE = 11;

  public static final int STATE_IN_DOCUMENT = 0;
  public static final int STATE_IN_BODY = 1;
  public static final int STATE_IN_CONTENT = 2;
  public static final int STATE_IN_GROUP = 3;
  public static final int STATE_IN_GROUP_BODY = 4;
  public static final int STATE_IN_SECTION = 5;
  public static final int STATE_IN_OTHER = 6;

  protected static class BufferState
  {
    private XmlWriter xmlWriter;
    private MemoryByteArrayOutputStream xmlBuffer;
    private OfficeStylesCollection stylesCollection;

    protected BufferState(final XmlWriter xmlWriter,
                          final MemoryByteArrayOutputStream xmlBuffer,
                          final OfficeStylesCollection stylesCollection)
    {
      this.stylesCollection = stylesCollection;
      this.xmlWriter = xmlWriter;
      this.xmlBuffer = xmlBuffer;
    }


    public OfficeStylesCollection getStylesCollection()
    {
      return stylesCollection;
    }

    public XmlWriter getXmlWriter()
    {
      return xmlWriter;
    }

    public String getXmlBuffer() throws ReportProcessingException
    {
      try
      {
        final byte[] zippedData = xmlBuffer.getRaw();
        final InputStreamReader reader = new InputStreamReader
            (new InflaterInputStream(new ByteArrayInputStream(zippedData, 0, xmlBuffer.getLength())), "UTF-16");
        final StringWriter writer = new StringWriter((zippedData.length / 2) + 1);
        IOUtils.getInstance().copyWriter(reader, writer);
        return writer.toString();
      }
      catch (IOException e)
      {
        throw new ReportProcessingException("Failed to copy buffer", e);
      }
    }

    public Reader getXmlAsReader() throws ReportProcessingException
    {
      try
      {
        final byte[] zippedData = xmlBuffer.getRaw();
        return new InputStreamReader
            (new InflaterInputStream(new ByteArrayInputStream(zippedData, 0, xmlBuffer.getLength())), "UTF-16");
      }
      catch (IOException e)
      {
        throw new ReportProcessingException("Failed to copy buffer", e);
      }
    }
  }

  protected static class GroupContext
  {
    private GroupContext parent;
    private int iterationCount;

    protected GroupContext(final GroupContext parent)
    {
      this.parent = parent;
    }

    public GroupContext getParent()
    {
      return parent;
    }

    public int getIterationCount()
    {
      return iterationCount;
    }

    public void iterationFinished()
    {
      iterationCount += 1;
    }
  }

  private FastStack states;
  private int currentRole;

  private FastStack xmlWriters;
  private XmlWriter rootXmlWriter;

  /**
   * This styles-collection contains all styles that were predefined in the report definition file. The common styles
   * and the master-styles will be written unmodified, the automatic styles will be ignored.
   */
  private OfficeStylesCollection predefinedStylesCollection;

  /**
   * This styles-collection contains all master-styles that have been generated by the report definition process. It
   * also contains all automatic styles that have been generated for the page-bands (and the pagebands as well).
   */
  private OfficeStylesCollection globalStylesCollection;

  /**
   * The content styles collection contains all automatic styles that have been generated for the normal-flow content.
   */
  private OfficeStylesCollection contentStylesCollection;

  private OutputRepository outputRepository;
  private AttributeNameGenerator tableNameGenerator;
  private AttributeNameGenerator autoStyleNameGenerator;
  private String target;
  private static final int INITIAL_BUFFER_SIZE = 40960;
  private StyleMapper styleMapper;
  private StyleSheetParserUtil styleSheetParserUtil;
  private AttributeNameGenerator imageNames;
  private ImageProducer imageProducer;
  private GroupContext groupContext;
  private static final boolean DEBUG_ELEMENTS =
      JFreeReportBoot.getInstance().getExtendedConfig().getBoolProperty
      ("com.sun.star.report.pentaho.output.DebugElements");

  protected OfficeDocumentReportTarget(final ReportJob reportJob,
                                       final ResourceManager resourceManager,
                                       final ResourceKey baseResource,
                                       final InputRepository inputRepository,
                                       final OutputRepository outputRepository,
                                       final String target,
                                       final ImageService imageService)
      throws ReportProcessingException
  {
    super(reportJob, resourceManager, baseResource);
    if (imageService == null)
    {
      throw new NullPointerException("ImageService must not be null");
    }
    if (target == null)
    {
      throw new NullPointerException("Target-Name must not be null");
    }

    this.target = target;

    this.tableNameGenerator = new AttributeNameGenerator();
    this.autoStyleNameGenerator = new AttributeNameGenerator();
    this.outputRepository = outputRepository;
    this.states = new FastStack();
    this.xmlWriters = new FastStack();
    this.imageNames = new AttributeNameGenerator();

    this.imageProducer = new ImageProducer(inputRepository, outputRepository, imageService);

    try
    {
      final ResourceManager realResourceManager = getResourceManager();
      styleMapper = StyleMapper.loadInstance(realResourceManager);
    }
    catch (ResourceException e)
    {
      throw new ReportProcessingException("Failed to load style-mapper", e);
    }
  }

  protected abstract String getTargetMimeType();

  protected OutputRepository getOutputRepository()
  {
    return outputRepository;
  }

  /**
   * Starts the output of a new office document. This method writes the generic 'office:document-content' tag along with
   * all known namespace declarations.
   *
   * @param report the report object.
   * @throws DataSourceException       if there was an error accessing the datasource
   * @throws ReportProcessingException if some other error occured.
   */
  public void startReport(final ReportStructureRoot report)
      throws DataSourceException, ReportProcessingException
  {
    imageNames.reset();
    this.groupContext = new GroupContext(null);

    final DefaultTagDescription tagDescription = createTagDescription();
    try
    {
      final OutputStream outputStream = outputRepository.createOutputStream(target,"text/xml");
      final Writer writer = new OutputStreamWriter(outputStream, "UTF-8");

      this.rootXmlWriter = new XmlWriter(writer, tagDescription);
      this.rootXmlWriter.setAlwaysAddNamespace(true);

      final AttributeList rootAttributes = new AttributeList();
      rootAttributes.addNamespaceDeclaration("office", OfficeNamespaces.OFFICE_NS);
      rootAttributes.addNamespaceDeclaration("style", OfficeNamespaces.STYLE_NS);
      rootAttributes.addNamespaceDeclaration("text", OfficeNamespaces.TEXT_NS);
      rootAttributes.addNamespaceDeclaration("table", OfficeNamespaces.TABLE_NS);
      rootAttributes.addNamespaceDeclaration("draw", OfficeNamespaces.DRAWING_NS);
      rootAttributes.addNamespaceDeclaration("fo", OfficeNamespaces.FO_NS);
      rootAttributes.addNamespaceDeclaration("xlink", OfficeNamespaces.XLINK_NS);
      rootAttributes.addNamespaceDeclaration("dc", OfficeNamespaces.PURL_NS);
      rootAttributes.addNamespaceDeclaration("meta", OfficeNamespaces.META_NS);
      rootAttributes.addNamespaceDeclaration("number", OfficeNamespaces.DATASTYLE_NS);
      rootAttributes.addNamespaceDeclaration("svg", OfficeNamespaces.SVG_NS);
      rootAttributes.addNamespaceDeclaration("chart", OfficeNamespaces.CHART_NS);
      rootAttributes.addNamespaceDeclaration("dr3d", OfficeNamespaces.DR3D_NS);
      rootAttributes.addNamespaceDeclaration("math", OfficeNamespaces.MATHML_NS);
      rootAttributes.addNamespaceDeclaration("form", OfficeNamespaces.FORM_NS);
      rootAttributes.addNamespaceDeclaration("script", OfficeNamespaces.SCRIPT_NS);
      rootAttributes.addNamespaceDeclaration("ooo", OfficeNamespaces.OO2004_NS);
      rootAttributes.addNamespaceDeclaration("ooow", OfficeNamespaces.OOW2004_NS);
      rootAttributes.addNamespaceDeclaration("oooc", OfficeNamespaces.OOC2004_NS);
      rootAttributes.addNamespaceDeclaration("dom", OfficeNamespaces.XML_EVENT_NS);
      rootAttributes.addNamespaceDeclaration("xforms", OfficeNamespaces.XFORMS_NS);
      rootAttributes.addNamespaceDeclaration("xsd", OfficeNamespaces.XSD_NS);
      rootAttributes.addNamespaceDeclaration("xsi", OfficeNamespaces.XSI_NS);
      rootAttributes.setAttribute(OfficeNamespaces.OFFICE_NS, "version", "1.0");

      this.rootXmlWriter.writeXmlDeclaration("UTF-8");
      this.rootXmlWriter.writeTag(OfficeNamespaces.OFFICE_NS, "document-content", rootAttributes, XmlWriterSupport.OPEN);

      states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_DOCUMENT));

      autoStyleNameGenerator.reset();
      tableNameGenerator.reset();

      final OfficeDocument reportDoc = (OfficeDocument) report;
      predefinedStylesCollection = reportDoc.getStylesCollection();

      final OfficeStyles commonStyles = predefinedStylesCollection.getCommonStyles();
      if (commonStyles.containsStyle("graphic", "Graphics") == false)
      {
        final OfficeStyle graphicsDefaultStyle = new OfficeStyle();
        graphicsDefaultStyle.setStyleFamily("graphic");
        graphicsDefaultStyle.setStyleName("Graphics");
        final Element graphicProperties = produceFirstChild(graphicsDefaultStyle, OfficeNamespaces.STYLE_NS, "graphic-properties");
        graphicProperties.setAttribute(OfficeNamespaces.TEXT_NS, "anchor-type", "paragraph");
        graphicProperties.setAttribute(OfficeNamespaces.SVG_NS, "x", "0cm");
        graphicProperties.setAttribute(OfficeNamespaces.SVG_NS, "y", "0cm");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "wrap", "dynamic");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "number-wrapped-paragraphs", "no-limit");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "wrap-contour", "false");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "vertical-pos", "top");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "vertical-rel", "paragraph");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "horizontal-pos", "center");
        graphicProperties.setAttribute(OfficeNamespaces.STYLE_NS, "horizontal-rel", "paragraph");
        commonStyles.addStyle(graphicsDefaultStyle);
      }

      // Make sure that later generated styles do not overwrite existing styles.
      fillStyleNameGenerator(predefinedStylesCollection);

      contentStylesCollection = new OfficeStylesCollection();
      globalStylesCollection = new OfficeStylesCollection();

      startBuffering(contentStylesCollection, true);
    }
    catch (IOException e)
    {
      throw new ReportProcessingException("Failed", e);
    }
  }

  protected AttributeNameGenerator getAutoStyleNameGenerator()
  {
    return autoStyleNameGenerator;
  }

  private void fillStyleNameGenerator(final OfficeStylesCollection stylesCollection)
  {
    final OfficeStyles commonStyles = stylesCollection.getCommonStyles();
    final OfficeStyle[] allCommonStyles = commonStyles.getAllStyles();
    for (int i = 0; i < allCommonStyles.length; i++)
    {
      final OfficeStyle style = allCommonStyles[i];
      autoStyleNameGenerator.generateName(style.getStyleName());
    }

    final OfficeStyles autoStyles = stylesCollection.getAutomaticStyles();
    final OfficeStyle[] allAutoStyles = autoStyles.getAllStyles();
    for (int i = 0; i < allAutoStyles.length; i++)
    {
      final OfficeStyle style = allAutoStyles[i];
      autoStyleNameGenerator.generateName(style.getStyleName());
    }
  }

  public OfficeStylesCollection getPredefinedStylesCollection()
  {
    return predefinedStylesCollection;
  }

  public OfficeStylesCollection getGlobalStylesCollection()
  {
    return globalStylesCollection;
  }

  public OfficeStylesCollection getContentStylesCollection()
  {
    return contentStylesCollection;
  }

  /**
   * Returns the XML-Writer tag description. This description defines whether an element can have character data inside.
   * Such element will disable the indention, as in that case the additional whitespaces might alter the meaning of the
   * element's contents.
   *
   * @return the tag description library.
   */
  protected DefaultTagDescription createTagDescription()
  {
    final DefaultTagDescription tagDescription = new DefaultTagDescription();
    tagDescription.configure(JFreeReportBoot.getInstance().getGlobalConfig(),
        OfficeDocumentReportTarget.TAG_DEF_PREFIX);
    return tagDescription;
  }

  /**
   * Returns the current processing state.
   *
   * @return the processing state.
   */
  protected int getCurrentState()
  {
    if (states.isEmpty())
    {
      throw new IllegalStateException();
    }
    final Integer o = (Integer) states.peek();
    return o.intValue();
  }

  /**
   * Starts the processing of an element and updates the processing state. This will select an apropriate handler method
   * for the call and will call one of the start* methods.
   *
   * @param attrs the attribute map for the current element
   * @throws DataSourceException
   * @throws ReportProcessingException
   */
  public final void startElement(final AttributeMap attrs)
      throws DataSourceException, ReportProcessingException
  {
    // todo
    if (DEBUG_ELEMENTS)
    {
      Log.debug("Starting " + getCurrentState() + "/" + states.size() + " " +
          ReportTargetUtil.getNamespaceFromAttribute(attrs) + " -> " +
          ReportTargetUtil.getElemenTypeFromAttribute(attrs));
    }
    try
    {
      switch (getCurrentState())
      {
        case OfficeDocumentReportTarget.STATE_IN_DOCUMENT:
        {
          if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OFFICE_NS, "body", attrs))
          {
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_BODY));
            startBody(attrs);
          }
          else
          {
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_OTHER));
            if (isFilteredNamespace(ReportTargetUtil.getNamespaceFromAttribute(attrs)) == false)
            {
              startOther(attrs);
            }
          }
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_BODY:
        {
          if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OFFICE_NS, "report", attrs))
          {
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_CONTENT));
            startContent(attrs);
          }
          else
          {
            throw new IllegalStateException
                ("The 'office:body' element must have exactly one child of type 'report'");
          }
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_CONTENT:
        case OfficeDocumentReportTarget.STATE_IN_GROUP:
        case OfficeDocumentReportTarget.STATE_IN_GROUP_BODY:
        {
          // A group.
          if (ReportTargetUtil.isElementOfType(OfficeNamespaces.INTERNAL_NS, "group-body", attrs) ||
              ReportTargetUtil.isElementOfType(OfficeNamespaces.INTERNAL_NS, "report-body", attrs))
          {
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_GROUP_BODY));
            startGroupBody(attrs);
          }
          else if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "group", attrs))
          {
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_GROUP));
            groupContext = new GroupContext(groupContext);
            startGroup(attrs);
          }
          else
          {
            // Either a page-header, page-footer, report-header, report-footer
            // or detail-band or variables-section
            states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_SECTION));
            currentRole = computeRoleForSection(attrs);
            startReportSection(attrs, currentRole);
          }
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_SECTION:
        {
          states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_OTHER));
          startOther(attrs);
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_OTHER:
        {
          states.push(IntegerCache.getInteger(OfficeDocumentReportTarget.STATE_IN_OTHER));
          startOther(attrs);
          return;
        }
        default:
          throw new IllegalStateException("Failure: " + getCurrentState());
      }
    }
    catch (IOException ioe)
    {
      ioe.printStackTrace();
      throw new ReportProcessingException("Failed to write content", ioe);
    }
//    finally
//    {
//      Log.debug ("Started " + getNamespaceFromAttribute(attrs) + ":" +
//                 getElemenTypeFromAttribute(attrs) + " -> " + getCurrentState());
//    }
  }

  protected GroupContext getGroupContext()
  {
    return groupContext;
  }

  protected void performStyleProcessing(final AttributeMap attrs)
      throws ReportProcessingException
  {
    final OfficeStylesCollection stylesCollection = getStylesCollection();
    final OfficeStylesCollection predefCollection = getPredefinedStylesCollection();
    final OfficeStylesCollection globalStylesCollection = getGlobalStylesCollection();

    final String elementNamespace =
        ReportTargetUtil.getNamespaceFromAttribute(attrs);
    final String elementName =
        ReportTargetUtil.getElemenTypeFromAttribute(attrs);

    final String[] namespaces = attrs.getNameSpaces();
    for (int i = 0; i < namespaces.length; i++)
    {
      final String attrNamespace = namespaces[i];
      if (isFilteredNamespace(attrNamespace))
      {
        continue;
      }

      final Map attributes = attrs.getAttributes(attrNamespace);
      final Iterator iterator = attributes.entrySet().iterator();
      while (iterator.hasNext())
      {
        final Map.Entry entry = (Map.Entry) iterator.next();
        final String attrName = (String) entry.getKey();
        final String attrValue = String.valueOf(entry.getValue());

        final String styleFamily = styleMapper.getStyleFamilyFor
            (elementNamespace, elementName, attrNamespace, attrName);
        if (styleFamily == null)
        {
          // None of the known style attributes.
          continue;
        }

        if (styleMapper.isListOfStyles
            (elementNamespace, elementName, attrNamespace, attrName))
        {
          // ignored for now.
          Log.warn("List of styles is not yet implemented.");
          continue;
        }

        // Copy styles is only called once per style.
        StyleUtilities.copyStyle(styleFamily, attrValue, stylesCollection, globalStylesCollection, predefCollection);
      }
    }
  }


  private int computeRoleForSection(final AttributeMap attrs)
  {
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.INTERNAL_NS, "template", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_TEMPLATE;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "group-header", attrs))
    {
      if ("true".equals(attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "repeated-section")))
      {
        return OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_HEADER;
      }
      return OfficeDocumentReportTarget.ROLE_GROUP_HEADER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "group-footer", attrs))
    {
      if ("true".equals(attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "repeated-section")))
      {
        return OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_FOOTER;
      }
      return OfficeDocumentReportTarget.ROLE_GROUP_FOOTER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "page-header", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_PAGE_HEADER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "page-footer", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_PAGE_FOOTER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "report-header", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_REPORT_HEADER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "report-footer", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_REPORT_FOOTER;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.OOREPORT_NS, "detail", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_DETAIL;
    }
    if (ReportTargetUtil.isElementOfType(OfficeNamespaces.INTERNAL_NS, "variables-section", attrs))
    {
      return OfficeDocumentReportTarget.ROLE_VARIABLES;
    }
    throw new IllegalStateException();
    //return OfficeDocumentReportTarget.ROLE_NONE;
  }

  protected void startBody(final AttributeMap attrs)
      throws IOException
  {
    getXmlWriter().writeTag(OfficeNamespaces.OFFICE_NS, "body", XmlWriterSupport.OPEN);
  }

  protected void startReportSection(final AttributeMap attrs, final int role)
      throws IOException, DataSourceException, ReportProcessingException
  {
    if (role == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_FOOTER ||
        role == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_HEADER ||
        role == OfficeDocumentReportTarget.ROLE_TEMPLATE)
    {
      startBuffering(new OfficeStylesCollection(), true);
    }
  }

  protected abstract void startContent(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException;

  protected void startGroup(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException
  {
  }

  protected void startGroupBody(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException
  {
  }

  protected abstract void startOther(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException;

  public void processText(final String text)
      throws DataSourceException, ReportProcessingException
  {
    try
    {
      final XmlWriter xmlWriter = getXmlWriter();
      final LineBreakIterator lb = new LineBreakIterator(text);
      while (lb.hasNext())
      {
        final String line = (String) lb.next();
        final String normalizedText = XmlWriterSupport.normalize(line, false);
        xmlWriter.writeText(normalizedText);
        if (lb.hasNext())
        {
          xmlWriter.writeTag(OfficeNamespaces.TEXT_NS, "line-break", XmlWriterSupport.CLOSE);
        }
      }
    }
    catch (IOException e)
    {
      throw new ReportProcessingException("Failed", e);
    }
  }

  protected boolean isFilteredNamespace(final String namespace)
  {
    if (Namespaces.LIBLAYOUT_NAMESPACE.equals(namespace))
    {
      return true;
    }
    if (JFreeReportInfo.REPORT_NAMESPACE.equals(namespace))
    {
      return true;
    }
    if (OfficeNamespaces.INTERNAL_NS.equals(namespace))
    {
      return true;
    }
    if (JFreeReportInfo.COMPATIBILITY_NAMESPACE.equals(namespace))
    {
      return true;
    }
    if (OfficeNamespaces.OOREPORT_NS.equals(namespace))
    {
      return true;
    }
    return false;
  }

  public void processContent(final DataFlags value)
      throws DataSourceException, ReportProcessingException
  {
    final Object rawvalue = value.getValue();
    if (rawvalue == null)
    {
      return;
    }

    // special handler for image (possibly also for URL ..)
    if (rawvalue instanceof Image)
    {
      // do nothing yet. We should define something for that later ..
      return;
    }

    final XmlWriter xmlWriter = getXmlWriter();
    final String text = String.valueOf(rawvalue);
    try
    {
      final LineBreakIterator lb = new LineBreakIterator(text);
      while (lb.hasNext())
      {
        final String line = (String) lb.next();
        final String normalizedText = XmlWriterSupport.normalize(line, false);
        xmlWriter.writeText(normalizedText);
        if (lb.hasNext())
        {
          xmlWriter.writeTag(OfficeNamespaces.TEXT_NS, "line-break", XmlWriterSupport.CLOSE);
        }
      }
    }
    catch (IOException e)
    {
      throw new ReportProcessingException("Failed", e);
    }
  }


  public void endElement(final AttributeMap attrs)
      throws DataSourceException, ReportProcessingException
  {
    // final int oldState = getCurrentState();
    try
    {

      switch (getCurrentState())
      {
        case OfficeDocumentReportTarget.STATE_IN_OTHER:
        {
          endOther(attrs);
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_SECTION:
        {
          endReportSection(attrs, currentRole);
          currentRole = OfficeDocumentReportTarget.ROLE_NONE;
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_GROUP:
        {
          endGroup(attrs);
          groupContext = groupContext.getParent();
          groupContext.iterationFinished();
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_GROUP_BODY:
        {
          endGroupBody(attrs);
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_CONTENT:
        {
          endContent(attrs);
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_BODY:
        {
          endBody(attrs);
          return;
        }
        case OfficeDocumentReportTarget.STATE_IN_DOCUMENT:
        {
          throw new IllegalStateException("This cannot be.");
        }
        default:
        {
          throw new IllegalStateException("Invalid state encountered.");
        }
      }
    }
    catch (IOException ioe)
    {
      throw new ReportProcessingException("IO Error while writing content",
          ioe);
    }
    finally
    {
      states.pop();

      if (DEBUG_ELEMENTS)
      {
        Log.debug("Finished " + getCurrentState() + "/" + states.size() + " " +
            ReportTargetUtil.getNamespaceFromAttribute(attrs) + ":" +
            ReportTargetUtil.getElemenTypeFromAttribute(attrs));
      }

    }
  }

  protected void endGroupBody(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException
  {

  }

  public int getCurrentRole()
  {
    return currentRole;
  }

  protected abstract void endOther(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException;

  protected void endReportSection(final AttributeMap attrs,
                                  final int role)
      throws IOException, DataSourceException, ReportProcessingException
  {
    if (role == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_FOOTER ||
        role == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_HEADER ||
        role == OfficeDocumentReportTarget.ROLE_TEMPLATE)
    {
      finishBuffering();
    }
  }

  protected void endGroup(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException
  {
  }

  protected abstract void endContent(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException;

  protected void endBody(final AttributeMap attrs)
      throws IOException, DataSourceException, ReportProcessingException
  {
    getXmlWriter().writeCloseTag();
  }

  public void endReport(final ReportStructureRoot report)
      throws DataSourceException, ReportProcessingException
  {
    if (xmlWriters.size() != 1)
    {
      throw new IllegalStateException("Invalid writer-stack state");
    }

    try
    {
      final StylesWriter inlineStylesWriter = new StylesWriter(rootXmlWriter);
      inlineStylesWriter.writeContentStyles
          (predefinedStylesCollection, contentStylesCollection);

      final BufferState state = finishBuffering();
      this.rootXmlWriter.writeStream(state.getXmlAsReader());

      final OutputStream stylesOutStream =
          outputRepository.createOutputStream("styles.xml","text/xml");
      final OutputStreamWriter osw =
          new OutputStreamWriter(stylesOutStream, "UTF-8");
      final StylesWriter stylesWriter = new StylesWriter(osw);
      stylesWriter.writeGlobalStyles
          (predefinedStylesCollection, globalStylesCollection);
      stylesWriter.close();

      this.rootXmlWriter.writeCloseTag();
      this.rootXmlWriter.close();
    }
    catch (IOException e)
    {
      throw new ReportProcessingException("Failed", e);
    }
  }

  public XmlWriter getXmlWriter()
  {
    final BufferState bufferState = (BufferState) xmlWriters.peek();
    return bufferState.getXmlWriter();
  }

  public OfficeStylesCollection getStylesCollection()
  {
    final BufferState bufferState = (BufferState) xmlWriters.peek();
    return bufferState.getStylesCollection();
  }

  public void startBuffering(final OfficeStylesCollection stylesCollection,
                             final boolean indent) throws ReportProcessingException
  {
    final XmlWriter currentWriter;
    if (xmlWriters.isEmpty())
    {
      currentWriter = rootXmlWriter;
    }
    else
    {
      final BufferState bufferState = (BufferState) xmlWriters.peek();
      currentWriter = bufferState.getXmlWriter();
    }

    try
    {
      final MemoryByteArrayOutputStream out =
          new MemoryByteArrayOutputStream(INITIAL_BUFFER_SIZE, 256 * INITIAL_BUFFER_SIZE);
      final DeflaterOutputStream deflateOut = new DeflaterOutputStream(out);
      final OutputStreamWriter xmlBuffer = new OutputStreamWriter(deflateOut, "UTF-16");
      //    final StringWriter xmlBuffer = new StringWriter
      //        (OfficeDocumentReportTarget.INITIAL_BUFFER_SIZE);
      final XmlWriter contentXmlWriter = new XmlWriter(xmlBuffer, createTagDescription());
      contentXmlWriter.copyNamespaces(currentWriter);
      if (indent)
      {
        contentXmlWriter.setAdditionalIndent(currentWriter.getCurrentIndentLevel());
        contentXmlWriter.setWriteFinalLinebreak(true);
      }
      else
      {
        contentXmlWriter.setWriteFinalLinebreak(false);
      }
      contentXmlWriter.setAlwaysAddNamespace(true);
      xmlWriters.push(new BufferState(contentXmlWriter, out, stylesCollection));
    }
    catch (IOException ioe)
    {
      throw new ReportProcessingException("Unable to create the buffer");
    }
  }

  public BufferState finishBuffering() throws ReportProcessingException
  {
    final BufferState state = (BufferState) xmlWriters.pop();
    try
    {
      state.getXmlWriter().close();
    }
    catch (IOException e)
    {
      e.printStackTrace();
    }
    return state;
  }

  public void commit()
      throws ReportProcessingException
  {
    // do not call flush before the report is fully finished. Every flush
    // causes the Office-Backend to fully ZIP all contents (it acts like a
    // 'Save' call from the UI) and that's expensive like hell
  }

  public NamespaceDefinition getNamespaceByUri(final String uri)
  {
    return null;
  }

  protected AttributeList buildAttributeList(final AttributeMap attrs)
  {
    final AttributeList attrList = new AttributeList();
    final String[] namespaces = attrs.getNameSpaces();
    for (int i = 0; i < namespaces.length; i++)
    {
      final String attrNamespace = namespaces[i];
      if (isFilteredNamespace(attrNamespace))
      {
        continue;
      }

      final Map localAttributes = attrs.getAttributes(attrNamespace);
      final Iterator entries = localAttributes.entrySet().iterator();
      while (entries.hasNext())
      {
        final Map.Entry entry = (Map.Entry) entries.next();
        final String key = String.valueOf(entry.getKey());
        if (OfficeNamespaces.TABLE_NS.equals(attrNamespace) &&
            "name".equals(key))
        {
          final String tableName = String.valueOf(entry.getValue());
          final String saneName = sanitizeName(tableName);
          attrList.setAttribute(attrNamespace, key,
              tableNameGenerator.generateName(saneName));
        }
        else
        {
          attrList.setAttribute
              (attrNamespace, key, String.valueOf(entry.getValue()));
        }
      }
    }
    return attrList;
  }

  protected String sanitizeName(final String name)
  {
    // A table name cannot contain spaces and should only contain
    // ascii-characters.
    if (name == null)
    {
      return "";
    }
    final char[] chars = name.toCharArray();
    final StringBuffer buffer = new StringBuffer();
    for (int i = 0; i < chars.length; i++)
    {
      final char aChar = chars[i];
      if (Character.isWhitespace(aChar))
      {
        buffer.append('_');
      }
      else
      {
        buffer.append(aChar);
      }
    }
    return buffer.toString();
  }

  /**
   * Returns the length in point. This method is f**king slow, it eats half of the processing time. I surely should
   * replace it with something more efficient later.
   *
   * @param text
   * @return
   */
  protected CSSNumericValue parseLength(final String text)
  {
    if (styleSheetParserUtil == null)
    {
      styleSheetParserUtil = StyleSheetParserUtil.getInstance();
    }

    final LexicalUnit cssValue = styleSheetParserUtil.parseLexicalStyleValue(
        text);
    return CSSValueFactory.createLengthValue(cssValue);
  }

  public boolean isRepeatingSection()
  {
    return (currentRole == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_FOOTER ||
        currentRole == OfficeDocumentReportTarget.ROLE_REPEATING_GROUP_HEADER ||
        currentRole == OfficeDocumentReportTarget.ROLE_PAGE_FOOTER ||
        currentRole == OfficeDocumentReportTarget.ROLE_PAGE_HEADER ||
        currentRole == OfficeDocumentReportTarget.ROLE_VARIABLES);

  }

  protected OfficeStyle deriveStyle(final String styleFamily, final String styleName)
      throws ReportProcessingException
  {
    // autogenerate a style. The style has already been added to the current
    // auto-collection.
    final OfficeStyle style = StyleUtilities.deriveStyle(styleFamily, styleName,
        getStylesCollection(), getGlobalStylesCollection(),
        getPredefinedStylesCollection(), getAutoStyleNameGenerator());
    return style;
  }


  protected void startImageProcessing(final AttributeMap attrs)
      throws ReportProcessingException
  {
    final Object imageData = attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "image-data");
    final boolean preserveIRI = "true".equals(attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "preserve-IRI"));

    // for the first shot, do nothing fancy ..
    final ImageProducer.OfficeImage image = imageProducer.produceImage(imageData, preserveIRI);
    if (image != null)
    {
      final ImageElementContext imageContext = (ImageElementContext)
          attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "image-context");

      // When scaling, we have to create an image-style.
      final CSSNumericValue width = image.getWidth(); // always in 100th of a mm
      final CSSNumericValue height = image.getHeight(); // always in 100th of a mm

      Log.debug ("Image " + imageData + " Width: " + width + ", Height: " + height);

      CSSNumericValue imageAreaWidthVal;
      CSSNumericValue imageAreaHeightVal;
      String styleName = null;
      if (imageContext != null)
      {
        imageAreaWidthVal = computeImageWidth(imageContext);
        imageAreaHeightVal = computeImageHeight(imageContext);

        // compute the clip-area ..
        final CSSNumericValue normalizedImageWidth =
            CSSValueResolverUtility.convertLength(width, imageAreaWidthVal.getType());
        final CSSNumericValue normalizedImageHeight =
            CSSValueResolverUtility.convertLength(height, imageAreaHeightVal.getType());

        final boolean scale = "true".equals(attrs.getAttribute(OfficeNamespaces.INTERNAL_NS, "scale"));
        if (scale == false && normalizedImageWidth.getValue() > 0 && normalizedImageHeight.getValue() > 0)
        {
          final double clipWidth = normalizedImageWidth.getValue() - imageAreaWidthVal.getValue();
          final double clipHeight = normalizedImageHeight.getValue() - imageAreaHeightVal.getValue();
          if (clipWidth > 0 && clipHeight > 0)
          {
            final OfficeStyle imageStyle = deriveStyle("graphic", "Graphics");
            final Element graphProperties = produceFirstChild(imageStyle, OfficeNamespaces.STYLE_NS, "graphic-properties");
            final StringBuffer buffer = new StringBuffer();
            buffer.append("rect(");
            buffer.append(clipHeight / 2);
            buffer.append(imageAreaHeightVal.getType().getType());
            buffer.append(" ");
            buffer.append(clipWidth / 2);
            buffer.append(imageAreaWidthVal.getType().getType());
            buffer.append(" ");
            buffer.append(clipHeight / 2);
            buffer.append(imageAreaHeightVal.getType().getType());
            buffer.append(" ");
            buffer.append(clipWidth / 2);
            buffer.append(imageAreaWidthVal.getType().getType());
            buffer.append(")");
            graphProperties.setAttribute(OfficeNamespaces.FO_NS, "clip", buffer.toString());

            styleName = imageStyle.getStyleName();
            getStylesCollection().getAutomaticStyles().addStyle(imageStyle);
          }
          else if (clipWidth > 0)
          {
            final OfficeStyle imageStyle = deriveStyle("graphic", "Graphics");
            final Element graphProperties = produceFirstChild(imageStyle, OfficeNamespaces.STYLE_NS, "graphic-properties");
            final StringBuffer buffer = new StringBuffer();
            buffer.append("rect(0cm ");
            buffer.append(clipWidth / 2);
            buffer.append(imageAreaWidthVal.getType().getType());
            buffer.append(" 0cm ");
            buffer.append(clipWidth / 2);
            buffer.append(imageAreaWidthVal.getType().getType());
            buffer.append(")");
            graphProperties.setAttribute(OfficeNamespaces.FO_NS, "clip", buffer.toString());

            styleName = imageStyle.getStyleName();
            getStylesCollection().getAutomaticStyles().addStyle(imageStyle);
            imageAreaHeightVal = normalizedImageHeight;
          }
          else if (clipHeight > 0)
          {
            final OfficeStyle imageStyle = deriveStyle("graphic", "Graphics");
            final Element graphProperties = produceFirstChild(imageStyle, OfficeNamespaces.STYLE_NS, "graphic-properties");
            final StringBuffer buffer = new StringBuffer();
            buffer.append("rect(");
            buffer.append(clipHeight / 2);
            buffer.append(imageAreaHeightVal.getType().getType());
            buffer.append(" 0cm ");
            buffer.append(clipHeight / 2);
            buffer.append(imageAreaHeightVal.getType().getType());
            buffer.append(" 0cm)");
            graphProperties.setAttribute(OfficeNamespaces.FO_NS, "clip", buffer.toString());

            styleName = imageStyle.getStyleName();
            getStylesCollection().getAutomaticStyles().addStyle(imageStyle);
            imageAreaWidthVal = normalizedImageWidth;
          }
          else
          {
            imageAreaWidthVal = normalizedImageWidth;
            imageAreaHeightVal = normalizedImageHeight;
          }
        }
        // If we do scale, then we simply use the given image-area-size as valid image size and dont
        // care about the image itself ..
      }
      else
      {
        Log.debug ("There is no image-context, so we have to rely on the image's natural bounds. " +
            "This may go awfully wrong.");
        imageAreaWidthVal = image.getWidth();
        imageAreaHeightVal = image.getHeight();
      }

      final AttributeList frameList = new AttributeList();
      frameList.setAttribute(OfficeNamespaces.DRAWING_NS, "name", imageNames.generateName("Image"));
      if (styleName != null)
      {
        frameList.setAttribute(OfficeNamespaces.DRAWING_NS, "style-name", styleName);
      }
      frameList.setAttribute(OfficeNamespaces.TEXT_NS, "anchor-type", "paragraph");
      frameList.setAttribute(OfficeNamespaces.SVG_NS, "z-index", "0");
      frameList.setAttribute(OfficeNamespaces.SVG_NS, "x", "0cm");
      frameList.setAttribute(OfficeNamespaces.SVG_NS, "y", "0cm");

      Log.debug ("Image " + imageData + " A-Width: " + imageAreaWidthVal + ", A-Height: " + imageAreaHeightVal);

      if (imageAreaWidthVal != null)
      {
        frameList.setAttribute(OfficeNamespaces.SVG_NS,
            "width", String.valueOf(imageAreaWidthVal.getValue()) + imageAreaWidthVal.getType().getType());
      }

      if (imageAreaHeightVal != null)
      {
        frameList.setAttribute(OfficeNamespaces.SVG_NS,
            "height", String.valueOf(imageAreaHeightVal.getValue()) + imageAreaHeightVal.getType().getType());
      }


      final AttributeList imageList = new AttributeList();
      imageList.setAttribute(OfficeNamespaces.XLINK_NS, "href", image.getEmbeddableLink());
      imageList.setAttribute(OfficeNamespaces.XLINK_NS, "type", "simple");
      imageList.setAttribute(OfficeNamespaces.XLINK_NS, "show", "embed");
      imageList.setAttribute(OfficeNamespaces.XLINK_NS, "actuate", "onLoad");


      try
      {
        getXmlWriter().writeTag(OfficeNamespaces.DRAWING_NS, "frame", frameList, XmlWriterSupport.OPEN);
        getXmlWriter().writeTag(OfficeNamespaces.DRAWING_NS, "image", imageList, XmlWriterSupport.CLOSE);
        getXmlWriter().writeCloseTag();
      }
      catch (IOException ioe)
      {
        throw new ReportProcessingException("Failed", ioe);
      }
    }
  }

  private CSSNumericValue computeImageWidth(final ImageElementContext imageElementContext)
  {
    final LengthCalculator calculator = new LengthCalculator();
    final String[] strings = imageElementContext.getColStyles();
    for (int i = 0; i < strings.length; i++)
    {
      final String styleName = strings[i];
      final CSSNumericValue value = computeColumnWidth(styleName);
      if (value != null)
      {
        calculator.add(value);
      }
    }
    return calculator.getResult();
  }

  private CSSNumericValue computeImageHeight(final ImageElementContext imageElementContext)
  {
    final LengthCalculator calculator = new LengthCalculator();
    final String[] strings = imageElementContext.getRowStyles();
    for (int i = 0; i < strings.length; i++)
    {
      final String styleName = strings[i];
      final CSSNumericValue value = computeRowHeight(styleName);
      if (value != null)
      {
        calculator.add(value);
      }
    }
    return calculator.getResult();
  }


  protected CSSNumericValue computeRowHeight(final String rowStyle)
  {
    final OfficeStylesCollection contentStyles = getContentStylesCollection();
    final OfficeStyle style = contentStyles.getStyle("table-row", rowStyle);
    if (style != null)
    {
      final Element element = style.getTableRowProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "row-height");
        if (height != null)
        {
          return parseLength(height);
        }
      }

      final String styleParent = style.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }

    final OfficeStylesCollection globalStyles = getGlobalStylesCollection();
    final OfficeStyle globalStyle = globalStyles.getStyle("table-row", rowStyle);
    if (globalStyle != null)
    {
      final Element element = globalStyle.getTableRowProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "row-height");
        if (height != null)
        {
          return parseLength(height);
        }
      }
      final String styleParent = globalStyle.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }

    final OfficeStylesCollection predefStyles = getPredefinedStylesCollection();
    final OfficeStyle predefStyle = predefStyles.getStyle("table-row", rowStyle);
    if (predefStyle != null)
    {
      final Element element = predefStyle.getTableRowProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "row-height");
        if (height != null)
        {
          return parseLength(height);
        }
      }
      final String styleParent = predefStyle.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }
    // not found.
    return null;
  }


  protected CSSNumericValue computeColumnWidth(final String colStyle)
  {
    final OfficeStylesCollection contentStyles = getContentStylesCollection();
    final OfficeStyle style = contentStyles.getStyle("table-column", colStyle);
    if (style != null)
    {
      final Element element = style.getTableColumnProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "column-width");
        if (height != null)
        {
          return parseLength(height);
        }
      }

      final String styleParent = style.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }

    final OfficeStylesCollection globalStyles = getGlobalStylesCollection();
    final OfficeStyle globalStyle = globalStyles.getStyle("table-column", colStyle);
    if (globalStyle != null)
    {
      final Element element = globalStyle.getTableColumnProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "column-width");
        if (height != null)
        {
          return parseLength(height);
        }
      }
      final String styleParent = globalStyle.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }

    final OfficeStylesCollection predefStyles = getPredefinedStylesCollection();
    final OfficeStyle predefStyle = predefStyles.getStyle("table-column", colStyle);
    if (predefStyle != null)
    {
      final Element element = predefStyle.getTableColumnProperties();
      if (element != null)
      {
        final String height = (String) element.getAttribute(OfficeNamespaces.STYLE_NS, "column-width");
        if (height != null)
        {
          return parseLength(height);
        }
      }
      final String styleParent = predefStyle.getStyleParent();
      if (styleParent != null)
      {
        return computeRowHeight(styleParent);
      }
    }
    // not found.
    return null;
  }

  protected Element produceFirstChild(final Section style,
                                      final String nameSpace,
                                      final String type)
  {
    Element paragraphProps = style.findFirstChild(nameSpace, type);
    if (paragraphProps == null)
    {
      paragraphProps = new Section();
      paragraphProps.setNamespace(nameSpace);
      paragraphProps.setType(type);
      style.addNode(paragraphProps);
    }
    return paragraphProps;
  }


}