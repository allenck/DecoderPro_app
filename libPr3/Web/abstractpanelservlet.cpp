#include "abstractpanelservlet.h"
#include "loggerfactory.h"
#include "json.h"
#include "stringutil.h"
#include "servletutil.h"
#include "jsonhttpservice.h"
#include "fileutil.h"
#include "jsonutilhttpservice.h"
#include "instancemanager.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "jframe.h"
#include "servletcontext.h"
#include "webserver.h"

AbstractPanelServlet::AbstractPanelServlet() : HttpServlet()
{

}
/**
 * Abstract servlet for using panels in browser.
 *
 * @author Randall Wood
 */
//abstract class AbstractPanelServlet extends HttpServlet {

    /*private*/ /*final*/ /*static*/ Logger* AbstractPanelServlet::log = LoggerFactory::getLogger("AbstractPanelServlet");

/*abstract*/ /*protected*/  QString AbstractPanelServlet::getPanelType() {return "";}

//@Override
/*public*/ void AbstractPanelServlet::init() throw (ServletException)
{
 if (this->getServletContext()->getContextPath() != ("/web/showPanel.html"))
 {
     this->mapper = new ObjectMapper();
// TODO:        this->mapper->configure(SerializationFeature::FAIL_ON_EMPTY_BEANS, false);
 }
}

/**
 * Handle a GET request for a panel.
 *
 * The request is processed in this order:
 * <ol>
 * <li>If the request contains a parameter {@code name=someValue}, redirect
 * to {@code /panel/someValue} if {@code someValue} is an open panel,
 * otherwise redirect to {@code /panel/}.</li>
 * <li>If the request ends in {@code /}, return an HTML page listing all
 * open panels.</li>
 * <li>Return the panel named in the last element in the path in the
 * following formats based on the {@code format=someFormat} parameter:
 * <dl>
 * <dt>html</dt>
 * <dd>An HTML page rendering the panel.</dd>
 * <dt>png</dt>
 * <dd>A PNG image of the panel.</dd>
 * <dt>json</dt>
 * <dd>A JSON document of the panel (currently imcomplete).</dd>
 * <dt>xml</dt>
 * <dd>A XML document of the panel ready to render within a browser.</dd>
 * </dl>
 * If {@code format} is not specified, it is treated as {@code html}. All
 * other formats not listed are treated as {@code xml}.
 * </li>
 * </ol>
 *
 */
//@Override
/*protected*/  void AbstractPanelServlet::doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException)
{
  log->debug(tr("Handling GET request for %1").arg(request->getRequestURI()));
 if (request->getRequestURI() == ("/web/showPanel.html"))
 { // NOI18N
  response->sendRedirect("/panel/"); // NOI18N
  return;
 }
 if (request->getParameter(JSON::NAME) != NULL)
 {
  QString panelName = StringUtil::unescapeString(request->getParameter(JSON::NAME));
  if (getEditor(panelName) != NULL) {
      response->sendRedirect("/panel/" + StringUtil::escapeString(panelName)); // NOI18N
  } else {
      response->sendRedirect("/panel/"); // NOI18N
  }
 }
 else if (request->getRequestURI().endsWith("/")) { // NOI18N
     listPanels(request, response);
 }
 else
 {
  QStringList path = request->getRequestURI().split("/"); // NOI18N
  QString panelName = StringUtil::unescapeString(path[path.length() - 1]);
//  if(panelName == "panel") // hack by ACK
//   panelName = "LayoutEditor";
  if ("png" == (request->getParameter("format")))
  {
   QByteArray panel = getPanelImage(panelName);
   if (panel == NULL)
   {
    response->sendError(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, "See the JMRI console for details.");
   }
   else
   {
       //ByteArrayOutputStream baos = new ByteArrayOutputStream();
//                ImageIO.write(panel, "png", baos);
//                baos.close();
       response->setContentType(ServletUtil::IMAGE_PNG);
       response->setStatus(HttpServletResponse::SC_OK);
//       response->setContentLength(panel.size());
//                response->getOutputStream().write(baos.toByteArray());
//                response->getOutputStream().close();
       response->resp->write(panel,true);
   }
  }
  else if ("html" == (request->getParameter("format")) || NULL == request->getParameter("format")) {
      this->listPanels(request, response);
  }
  else
  {
   bool useXML = (JSON::_JSON != (request->getParameter("format")));
   response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
   QString panel = getPanelText(panelName, useXML);
   if (panel == NULL)
   {
    response->sendError(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, "See the JMRI console for details.");
   }
   else if (panel.startsWith("ERROR"))
   {
    response->sendError(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, panel.mid(5).trimmed());
   }
   else
   {
    response->setStatus(HttpServletResponse::SC_OK);
    //response->setContentLength(panel.toUtf8().length());
    //response->getOutputStream().print(panel);
    response->resp->write(panel.toUtf8(),true);
   }
  }
 }
}

/*protected*/  void AbstractPanelServlet::listPanels(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException)
{
 if (JSON::_JSON == (request->getParameter("format")))
 {
  response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
  JsonUtilHttpService* service = new JsonUtilHttpService( ObjectMapper());
  //response->getWriter()->print(service->getPanels(request->getLocale(), JSON::XML));
  QJsonArray array = service->getPanels(request->getLocale(), JSON::XML);
  qDebug() << QJsonDocument(array).toJson();
  response->resp->write(QJsonDocument(array).toJson(),true);
 }
 else
 {
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//        response->getWriter()->print(String.format(request->getLocale(),
//                FileUtil::readURL(FileUtil::findURL(tr(request->getLocale(), "Panel.html"))),
//                String.format(request->getLocale(),
//                        tr(/*request->getLocale(),*/ "%2$s | %1$s"),
//                        ServletUtil::getInstance()->getRailroadName(false),
//                        tr(/*request->getLocale(),*/ "Panels")
//                ),
//                ServletUtil::getInstance()->getNavBar(request->getLocale(), "/panel"),
//                ServletUtil::getInstance()->getRailroadName(false),
//                ServletUtil::getInstance()->getFooter(request->getLocale(), "/panel")
//        ));
  QString contextPath = request->getContextPath();
  QString out = FileUtil::readURL(FileUtil::findURL(tr(/*request->getLocale(),*/ "web/servlet/panel/Panel.html")));
  QString title = tr("%2 | %1").arg(ServletUtil::getInstance()->getRailroadName(false)).arg(tr( /*request->getLocale(),*/ "Panels"));
  out = out.replace("%1$s", title);
  out = out.replace("%2$s", ServletUtil::getInstance()->getNavBar( request->getLocale(),  contextPath));
  out = out.replace("%4$s", ServletUtil::getInstance()->getFooter( request->getLocale(),  contextPath));
  out = out.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
  response->resp->write(out.toLocal8Bit(),true);
 }
}

/*protected*/  QByteArray AbstractPanelServlet::getPanelImage(QString name) {
    QWidget* panel = getPanel(name);
    if (panel == NULL) {
        return NULL;
    }
//    BufferedImage bi = new BufferedImage(panel.getWidth(), panel.getHeight(), BufferedImage.TYPE_INT_ARGB);
//    panel.paint(bi.getGraphics());
    QString saveExtension = "PNG";
    QByteArray ba;
    QBuffer* buf = new QBuffer(&ba);
    if(!panel->grab().save(buf, qPrintable(saveExtension)))
    {
     throw IOException(tr("Error capturing %s").arg(name));
    }
    return ba;
}

//@CheckForNull
/*protected*/  QWidget* AbstractPanelServlet::getPanel(QString name) {
    Editor* editor = getEditor(name);
    if (editor != NULL)
    {
     //return editor.getTargetPanel();
     return ((QGraphicsView*)((QGraphicsScene*)editor->getTargetPanel())->views().at(0))->parentWidget();
    }
    return NULL;
}

/*protected*/  QString AbstractPanelServlet::getPanelText(QString name, bool useXML)
{
 if (useXML)
 {
  return getXmlPanel(name);
 }
 else
 {
  return getJsonPanel(name);
 }
}

/*abstract*/ /*protected*/  QString AbstractPanelServlet::getJsonPanel(QString /*name*/) {return "";}

/*abstract*/ /*protected*/  QString AbstractPanelServlet::getXmlPanel(QString /*name*/){return "";}


//@CheckForNull
/*protected*/  Editor* AbstractPanelServlet::getEditor(QString name)
{
 foreach (Editor* editor, Editor::getEditors())
 {
  QWidget* container = editor->window();
  //if (Frame.class.isInstance(container))
  if(qobject_cast<JFrame*>(container) != NULL)
  {
   if (((JFrame*) container)->title() == (name)) {
       return editor;
   }
   if(((JFrame*) container)->title().contains(name))
    return editor;
  }
 }
 return NULL;
}

/*protected*/  void AbstractPanelServlet::parsePortableURIs(QDomElement element)
{
 if (element != QDomElement())
 {
  //loop thru and update attributes of this element if value is a portable filename
  //for (QString attr : element.getAttributes())
  QDomNamedNodeMap map =  element.attributes();
  for(int i =0; i < map.count(); i++)
  {
   QDomNode n = map.item(i);
   QDomAttr attr = n.toAttr();
   if (FileUtil::isPortableFilename(attr.value()))
   {
    QString url = WebServer::URIforPortablePath(attr.value());
    if (url != NULL)
    {  // if portable path conversion fails, don't change the value
     attr.setValue(url);
    }
   }
  }
  //recursively call for each child
  //for (Object child : element.getChildren())
  QDomNodeList children = element.childNodes();
  for(int i =0; i < children.count(); i++)
  {
   parsePortableURIs( children.at(i).toElement());
  }
 }
}

//build and return an "icons" element containing icon urls for all signalmast states,
//  element names are cleaned-up aspect names, aspect attribute is actual name of aspect
QDomElement AbstractPanelServlet::getSignalMastIconsElement(QString name)
{
 QDomDocument doc;
    QDomElement icons = doc.createElement("icons");
    SignalMast* signalMast = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
    foreach (QString aspect, signalMast->getValidAspects()) {
        QDomElement ea = doc.createElement(aspect.replace("[ ()]", "")); //create element for aspect after removing invalid chars
        QString url = signalMast->getAppearanceMap()->getImageLink(aspect, "default");  //TODO: use correct imageset
        if (!url.contains("preference:")) {
            url = "program:" + url.mid(url.indexOf("resources"));
        }
        ea.setAttribute(JSON::ASPECT, aspect);
        ea.setAttribute("url", url);
        icons.appendChild(ea);
    }
   QString url = signalMast->getAppearanceMap()->getImageLink("$held", "default");  //add "Held" aspect if defined
    if (!url.isEmpty()) {
        if (!url.contains("preference:")) {
            url = "program:" + url.mid(url.indexOf("resources"));
        }
        QDomElement ea = doc.createElement(JSON::ASPECT_HELD);
        ea.setAttribute(JSON::ASPECT, JSON::ASPECT_HELD);
        ea.setAttribute("url", url);
        icons.appendChild(ea);
    }
    url = signalMast->getAppearanceMap()->getImageLink("$dark", "default");  //add "Dark" aspect if defined
    if (!url.isEmpty()) {
        if (!url.contains("preference:")) {
            url = "program:" + url.mid(url.indexOf("resources"));
        }
        QDomElement ea = doc.createElement(JSON::ASPECT_DARK);
        ea.setAttribute(JSON::ASPECT, JSON::ASPECT_DARK);
        ea.setAttribute("url", url);
        icons.appendChild(ea);
    }
    QDomElement ea = doc.createElement(JSON::ASPECT_UNKNOWN);
    ea.setAttribute(JSON::ASPECT, JSON::ASPECT_UNKNOWN);
    ea.setAttribute("url", "program:resources/icons/misc/X-red.gif");  //add icon for unknown state
    icons.appendChild(ea);

    return icons;
}
