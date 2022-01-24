#include "jmrijframeservlet.h"
#include "loggerfactory.h"
#include "QAbstractButton"
#include "multisensoricon.h"
#include "webserverpreferences.h"
#include "json.h"
#include <QVector>
#include "stringutil.h"
#include <QStringList>
#include "lighticon.h"
#include "locoicon.h"
#include "lememoryicon.h"
#include "reportericon.h"
#include "rpspositionicon.h"
#include "slipturnouticon.h"
#include "turnouticon.h"
#include "class.h"
#include <QVector>
#include "jsonutilhttpservice.h"
#include "jframe.h"
#include <QPixmap>
#include "positionable.h"
#include <QGraphicsItem>
#include <QGraphicsItemGroup>

JmriJFrameServlet::JmriJFrameServlet()
{

}
/**
 * A simple servlet that returns a JMRI window as a PNG image or enclosing HTML
 * file.
 * <p>
 * The suffix of the request determines which. <dl>
 * <dt>.html<dd>Returns a HTML file that displays the frame enabled for clicking
 * via server side image map; see the .properties file for the content
 * <dt>.png<dd>Just return the image <dt>no name<dd>Return an HTML page with
 * links to available images </dl>
 * <P>
 * The associated .properties file contains the HTML fragments used to form
 * replies.
 * <P>
 * Parts taken from Core Web Programming from Prentice Hall and Sun Microsystems
 * Press, http://www.corewebprogramming.com/. &copy; 2001 Marty Hall and Larry
 * Brown; may be freely used or adapted.
 *
 * @author Modifications by Bob Jacobsen Copyright 2005, 2006, 2008
 */
//@WebServlet(name = "FrameServlet",
//        urlPatterns = {"/frame"})
///*public*/ class JmriJFrameServlet extends HttpServlet {

void JmriJFrameServlet::sendClick(QString /*name*/, QWidget* c, int xg, int yg, QWidget* FrameContentPane) {  // global positions
    int x = xg - c->pos().x();
    int y = yg - c->pos().y();
    log->debug(tr("component is %1 - %2").arg(c->metaObject()->className()).arg(c->objectName()));
    log->debug(tr("Local click at %1,%2").arg(x).arg(y));

    if (QString(c->metaObject()->className())==("QPushButton")) {
        ((QAbstractButton*) c)->click();
    } else if (QString(c->metaObject()->className())==("QCheckBox")) {
        ((QAbstractButton*) c)->click();
    } else if (QString(c->metaObject()->className())==("QRadioButton")) {
        ((QAbstractButton*) c)->click();
    }
#if 0
    else if (MouseListener.class.isAssignableFrom(c.getClass())) {
        log->debug("Invoke directly on MouseListener, at {},{}", x, y);
        sendClickSequence((MouseListener) c, c, x, y);
    }
#endif
    else if (qobject_cast<MultiSensorIcon*>(c) != NULL) {
        log->debug("Invoke Clicked on MultiSensorIcon");
#if 0
        MouseEvent e = new MouseEvent(c,
                MouseEvent.MOUSE_CLICKED,
                0, // time
                0, // modifiers
                xg, yg, // this component expects global positions for some reason
                1, // one click
                false // not a popup
        );
        ((Positionable) c).doMouseClicked(e);
#else
#endif
    }
    else if (isAssignable("Positionable",c))
    {
     log->debug("Invoke Pressed, Released and Clicked on Positionable");
#if 0
        MouseEvent e = new MouseEvent(c,
                MouseEvent.MOUSE_PRESSED,
                0, // time
                0, // modifiers
                x, y, // x, y not in this component?
                1, // one click
                false // not a popup
        );
        ((jmri.jmrit.display.Positionable) c).doMousePressed(e);

        e = new MouseEvent(c,
                MouseEvent.MOUSE_RELEASED,
                0, // time
                0, // modifiers
                x, y, // x, y not in this component?
                1, // one click
                false // not a popup
        );
        ((jmri.jmrit.display.Positionable) c).doMouseReleased(e);

        e = new MouseEvent(c,
                MouseEvent.MOUSE_CLICKED,
                0, // time
                0, // modifiers
                x, y, // x, y not in this component?
                1, // one click
                false // not a popup
        );
        ((jmri.jmrit.display.Positionable) c).doMouseClicked(e);
#endif
    }
#if 0
    else {
        MouseListener[] la = c.getMouseListeners();
        log->debug("Invoke {} contained mouse listeners", la.length);
        log->debug("component is {}", c);
        /*
         * Using c.getLocation() above we adjusted the click position for
         * the offset of the control relative to the frame. That works fine
         * in the cases above. In this case getLocation only provides the
         * offset of the control relative to the Widget*. So we also need
         * to adjust the click position for the offset of the Widget*
         * relative to the frame.
         */
        // was incorrect for zoomed panels, turned off
        // Point pc = c.getLocationOnScreen();
        // Point pf = FrameContentPane.getLocationOnScreen();
        // x -= (int)(pc.getX() - pf.getX());
        // y -= (int)(pc.getY() - pf.getY());
        for (MouseListener ml : la) {
            log->debug("Send click sequence at {},{}", x, y);
            sendClickSequence(ml, c, x, y);
        }
    }
#endif
}
#if 0
/*private*/ void sendClickSequence(MouseListener m, Widget* c, int x, int y) {
    /*
     * create the sequence of mouse events needed to click on a control:
     * MOUSE_ENTERED MOUSE_PRESSED MOUSE_RELEASED MOUSE_CLICKED
     */
    MouseEvent e = new MouseEvent(c,
            MouseEvent.MOUSE_ENTERED,
            0, // time
            0, // modifiers
            x, y, // x, y not in this component?
            1, // one click
            false // not a popup
    );
    m.mouseEntered(e);
    e = new MouseEvent(c,
            MouseEvent.MOUSE_PRESSED,
            0, // time
            0, // modifiers
            x, y, // x, y not in this component?
            1, // one click
            false, // not a popup
            MouseEvent.BUTTON1);
    m.mousePressed(e);
    e = new MouseEvent(c,
            MouseEvent.MOUSE_RELEASED,
            0, // time
            0, // modifiers
            x, y, // x, y not in this component?
            1, // one click
            false, // not a popup
            MouseEvent.BUTTON1);
    m.mouseReleased(e);
    e = new MouseEvent(c,
            MouseEvent.MOUSE_CLICKED,
            0, // time
            0, // modifiers
            x, y, // x, y not in this component?
            1, // one click
            false, // not a popup
            MouseEvent.BUTTON1);
    m.mouseClicked(e);
    e = new MouseEvent(c,
            MouseEvent.MOUSE_EXITED,
            0, // time
            0, // modifiers
            x, y, // x, y not in this component?
            1, // one click
            false, // not a popup
            MouseEvent.BUTTON1);
    m.mouseExited(e);
}
#endif

/*private*/ bool JmriJFrameServlet::isAssignable(QString type, QWidget* c)
{
 if(c == NULL)
  return false;
 try
 {
  return Class::forName(type)->isAssignableFrom(c->metaObject()->className());
 }
 catch (ClassNotFoundException* ex)
 {
  return false;
 }
}

//@Override
/*protected*/ void JmriJFrameServlet::doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException)
{
 if (WebServerPreferences::getDefault()->isDisableFrames())
 {
  if (WebServerPreferences::getDefault()->isRedirectFramesToPanels())
  {
   if (JSON::_JSON == (request->getParameter("format"))) {
       response->sendRedirect("/panel?format=json");
   } else {
       response->sendRedirect("/panel");
   }
  }
  else {
      response->sendError(HttpServletResponse::SC_FORBIDDEN, tr(/*request->getLocale(),*/ "Frames are disabled."));
  }
  return;
 }
 JmriJFrame* frame = NULL;
 QString name = getFrameName(/*request->getRequestURI()*/request->req->getPath());
 QList<QString> disallowedFrames = WebServerPreferences::getDefault()->getDisallowedFrames().toList();
 if (name != NULL)
 {
  if (disallowedFrames.contains(name)) {
      response->sendError(HttpServletResponse::SC_FORBIDDEN, "Frame [" + name + "] not allowed (check Preferences)");
      return;
  }
  frame = JmriJFrame::getFrame(name);
  if (frame == NULL) {
      response->sendError(HttpServletResponse::SC_NOT_FOUND, "Can not find frame [" + name + "]");
      return;
  } else if (!frame->isVisible()) {
      response->sendError(HttpServletResponse::SC_FORBIDDEN, "Frame [" + name + "] hidden");
  }
  else if (!frame->getAllowInFrameServlet()) {
      response->sendError(HttpServletResponse::SC_FORBIDDEN, "Frame [" + name + "] not allowed by design");
      return;
  }
 }
 QMap<QString, QStringList*>* parameters = this->populateParameterMap(request->getParameterMap());
 if (parameters->contains("coords") && !(parameters->contains("protect") && (parameters->value("protect")->at(0)=="true"))) { // NOI18N
     this->doClick(frame, parameters->value("coords")->at(0)); // NOI18N
 }
 if (frame != NULL && request->getRequestURI().contains(".html")) { // NOI18N
     this->doHtml(frame, request, response, parameters);
 } else if (frame != NULL && request->getRequestURI().contains(".png")) { // NOI18N
     this->doImage(frame, request, response);
 } else {
     this->doList(request, response);
 }
}

//@Override
/*protected*/ void JmriJFrameServlet::doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    this->doGet(request, response);
}

/*private*/ void JmriJFrameServlet::doHtml(JmriJFrame* frame, HttpServletRequest* /*request*/, HttpServletResponse* response, QMap<QString, QStringList*>* parameters) throw (ServletException, IOException) {
    QDateTime now = QDateTime::currentDateTime();
    bool click = false;
    bool useAjax = WebServerPreferences::getDefault()->isUseAjax();
    bool plain = WebServerPreferences::getDefault()->isSimple();
    QString clickRetryTime = QString::number(WebServerPreferences::getDefault()->getClickDelay());
    QString noclickRetryTime = QString::number(WebServerPreferences::getDefault()->getRefreshDelay());
    bool protect = false;
    if (parameters->contains("coords")) { // NOI18N
        click = true;
    }
    if (parameters->contains("retry")) { // NOI18N
        noclickRetryTime = parameters->value("retry")->at(0); // NOI18N
    }
    if (parameters->contains("ajax")) { // NOI18N
        useAjax = (parameters->value("ajax")->at(0)=="true"); // NOI18N
    }
    if (parameters->contains("plain")) { // NOI18N
        plain = (parameters->value("plain")->at(0)=="true"); // NOI18N
    }
    if (parameters->contains("protect")) { // NOI18N
        protect = (parameters->value("protect")->at(0)=="true"); // NOI18N
    }
    response->setStatus(HttpServletResponse::SC_OK);
    response->setContentType("text/html"); // NOI18N
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    response->setDateHeader("Date", now.currentMSecsSinceEpoch()); // NOI18N
    response->setDateHeader("Last-Modified", now.currentMSecsSinceEpoch()); // NOI18N
    response->setDateHeader("Expires", now.currentMSecsSinceEpoch()); // NOI18N
    // 0 is host
    // 1 is frame name  (after escaping special characters)
    // 2 is retry in META tag, click or noclick retry
    // 3 is retry in next URL, future retry
    // 4 is state of plain
    // 5 is the CSS stylesteet name addition, based on "plain"
    // 6 is ajax preference
    // 7 is protect
    QString fname = StringUtil::escapeString(frame->title()).toLocal8Bit();
    QString clicktime = click ? clickRetryTime : noclickRetryTime;

    QList<QByteArray> args = QList<QByteArray>() << "localhost" << // NOI18N
        StringUtil::escapeString(frame->title()).toLocal8Bit() <<
        clicktime.toLocal8Bit() <<
        noclickRetryTime.toLocal8Bit() <<
        (plain?"true":"false") <<
        (plain ? "-plain" : "") << // NOI18N
        (useAjax?"true":"false") <<
        (protect?"true":"false");

    //response->getWriter().write(tr(request->getLocale(), "FrameDocType")); // NOI18N
    response->resp->write("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">", false);
#if 0
    response->getWriter().write(MessageFormat.format(tr(request->getLocale(), "FramePart1"), args)); // NOI18N
    if (useAjax) {
        response->getWriter().write(MessageFormat.format(tr(request->getLocale(), "FramePart2Ajax"), args)); // NOI18N
    } else {
        response->getWriter().write(MessageFormat.format(tr(request->getLocale(), "FramePart2NonAjax"), args)); // NOI18N
    }
    response->getWriter().write(MessageFormat.format(tr(request->getLocale(), "FrameFooter"), args)); // NOI18N

#endif
    QByteArray out = QByteArray("<HTML><HEAD><TITLE>{1}</TITLE>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/miniServer{5}.css\" media=\"screen\">\n<meta name = \"viewport\" content = \"width = device-width\" />");
    if(useAjax)
      out = out.append("<script src=\"/web/js/jquery-1.8.2.min.js\"></script>\n<script type=\"text/javascript\"> \nvar frameName = \"{1}\";\nvar clickRetryTime = {2};\nvar noclickRetryTime = {3};\nvar plain = {4};\nvar useAjax = {6};\nvar protect = {7};\n</script>\n<script src=\"/web/js/frame_server_ajax.js\"></script>\n</HEAD><BODY>\n<DIV id='frame_image_wrapper'>\n<IMG id='frame_image' SRC=\"/frame/{1}.png\" BORDER=\"0\" ISMAP>\n</DIV>\n");
    else
      out = out.append("<meta http-equiv=\"refresh\" content=\"{2};url=/frame/{1}.html?ajax={6}&protect={7}&plain={4}&retry={3}\">\n</HEAD><BODY>\n<A id=\"frame_image_href\" HREF=\"/frame/{1}.html?ajax={6}&protect={7}&plain={4}&retry={3}\">\n<DIV id='frame_image_wrapper'>\n<IMG SRC=\"/frame/{1}.png\" BORDER=\"0\" ISMAP>\n</DIV></A>\n");
    out = out.
      append("<DIV class=\"frame-footer\"><A class=\"list\" href=\"/frame\">[List]</A> \n<A class=\"home\" href=\"/\">[Home]</A>\n<A class=\"help\" href=\"/help/en/html/web/FrameServlet.shtml\">[Help]</A>\n<A class=\"back\" href=\"javascript:history.go(-1);\">[Back]</A>\n<SPAN class=\"info\">Served by JMRIJFrameServlet, refresh={3}s</SPAN>\n</DIV>\n</BODY>\n</HTML>\n");
    for(int i = 0; i < 8; i++)
     out =out.replace(QString("{%1}").arg(i), args.at(i));
    response->resp->write(out,true);
    log->debug(tr("Sent jframe html with click=%1").arg(click ? "True" : "False"));
}

/*private*/ void JmriJFrameServlet::doImage(JmriJFrame* frame, HttpServletRequest* /*request*/, HttpServletResponse* response) throw (ServletException, IOException) {
    QDateTime now = QDateTime::currentDateTime();
    response->setStatus(HttpServletResponse::SC_OK);
    response->setContentType("image/png"); // NOI18N
    response->setDateHeader("Date", now.toMSecsSinceEpoch()); // NOI18N
    response->setDateHeader("Last-Modified", now.toMSecsSinceEpoch()); // NOI18N
    response->setHeader("Cache-Control", "no-cache"); // NOI18N
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    response->setHeader("Keep-Alive", "timeout=5, max=100"); // NOI18N
#if 0
    BufferedImage image = new BufferedImage(frame.getContentPane().getWidth(),
            frame.getContentPane().getHeight(),
            BufferedImage.TYPE_INT_RGB);
    frame.getContentPane().paint(image.createGraphics());
    //put it in a temp file to get post-compression size
    ByteArrayOutputStream tmpFile = new ByteArrayOutputStream();
    ImageIO.write(image, "png", tmpFile); // NOI18N
    tmpFile.close();
    response->setContentLength(tmpFile.size());
    response->getOutputStream().write(tmpFile.toByteArray());
    log->debug("Sent [{}] as {} byte png.", frame.getTitle(), tmpFile.size());
#endif
    QString saveExtension = "PNG";
    QByteArray ba;
    QBuffer* buf = new QBuffer(&ba);
    if(!frame->getContentPane()->grab().save(buf, qPrintable(saveExtension)))
    {
     throw new IOException(tr("Error capturing %s").arg(frame->title()));
    }
    //response->setContentLength(ba.size());
    response->resp->write(ba,true);
    log->debug(tr("Sent [%1] as %2 byte png.").arg(frame->title()).arg(ba.size()));

}
#if 1
/*private*/ void JmriJFrameServlet::doList(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException)
{
 QList<QString> disallowedFrames = (WebServerPreferences::getDefault()->getDisallowedFrames().toList());
 QString format = request->getParameter("format"); // NOI18N
//    ObjectMapper mapper = new ObjectMapper();
 QDateTime now = QDateTime();
 bool usePanels = (request->getParameter(JSON::PANELS)=="true");
 response->setStatus(HttpServletResponse::SC_OK);
 if ("json" == (format)) { // NOI18N
     response->setContentType("application/json"); // NOI18N
 } else {
     response->setContentType("text/html"); // NOI18N
 }
 response->setHeader("Connection", "Keep-Alive"); // NOI18N
 response->setDateHeader("Date", now.currentMSecsSinceEpoch()); // NOI18N
 response->setDateHeader("Last-Modified", now.currentMSecsSinceEpoch()); // NOI18N
 response->setDateHeader("Expires", now.currentMSecsSinceEpoch()); // NOI18N

 if ("json" == (format))
 { // NOI18N
  //ArrayNode root = mapper.createArrayNode();
  QJsonArray root = QJsonArray();
  QSet<JFrame*> frames = QSet<JFrame*>();
  JsonUtilHttpService* service = new JsonUtilHttpService( ObjectMapper());
  //JmriJFrame::getFrameList().stream().forEach((frame) ->
  foreach(JmriJFrame* frame, *JmriJFrame::getFrameList())
  {
   if (usePanels && qobject_cast<Editor*>(frame)!= NULL)
   {
    QJsonObject node = service->getPanel(request->getLocale(), (Editor*) frame, JSON::XML);
    if (node.isEmpty()) {
        root.append(node);
        frames.insert(((Editor*) frame)->getTargetFrame());
    }
   }
   else
   {
    QString title = frame->title();
    if (!title.isEmpty()
            && frame->getAllowInFrameServlet()
            && !disallowedFrames.contains(title)
            && !frames.contains(frame)
            && frame->isVisible()) {
     QJsonObject node = QJsonObject();//mapper.createObjectNode();
     node.insert(JSON::NAME, title);
     node.insert(JSON::URL, "/frame/" + StringUtil::escapeString(title) + ".html"); // NOI18N
     node.insert("png", "/frame/" + StringUtil::escapeString(title) + ".png"); // NOI18N
     root.append(node);
     frames.insert(frame);
    }
   }
  }//);
  //response->getWriter().write(mapper.writeValueAsString(root));
  response->resp->write(QJsonDocument(root).toJson(QJsonDocument::Compact),true);
 }
 else
 {
  //response->getWriter().append(tr(request->getLocale(), "FrameDocType")); // NOI18N
  response->resp->write("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">", false);
  //response.getWriter().append(Bundle.getMessage(request.getLocale(), "ListFront")); // NOI18N
  response->resp->write("<HTML>\n<HEAD>\n<TITLE>Available JMRI Frames</TITLE>\n<link rel=\"stylesheet\" type=\"text/css\" href=\"/css/miniServer.css\" media=\"screen\">\n<meta http-equiv=\"Cache-Control\" content=\"no-cache\"/>\n<meta name = \"viewport\" content = \"width = device-width\" />\n<META HTTP-EQUIV=\"PRAGMA\" CONTENT=\"NO-CACHE\"/>\n</HEAD>\n<BODY class=\"frame-list\">\n<DIV ID=\"mainContent\">\n<H1>Available JMRI Frames</H1>",false);
  //response->getWriter().write(tr(request->getLocale(), "TableHeader")); // NOI18N
  response->resp->write("<table class=\"frame-list\">\n<tr><th>Panel</th><th>Thumbnail</th></tr>",false);
  // list frames, (open JMRI windows)
  foreach (JmriJFrame* frame, *JmriJFrame::getFrameList())
  {
   QString title = frame->title();
   //don't add to list if blank or disallowed
   if (!title.isEmpty() && frame->getAllowInFrameServlet() && !disallowedFrames.contains(title) && frame->isVisible())
   {
    QString link = "/frame/" + StringUtil::escapeString(title) + ".html"; // NOI18N
    //format a table row for each valid window (frame)
    //response->getWriter().append("<tr><td><a href='" + link + "'>"); // NOI18N
    response->resp->write("<tr><td><a href='" + link.toLocal8Bit() + "'>",false);
    //response->getWriter().append(title);
    response->resp->write(title.toLocal8Bit(),false);
    //response->getWriter().append("</a></td>"); // NOI18N
    response->resp->write("</a></td>", false);
    //response->getWriter().append("<td><a href='");
    response->resp->write("<td><a href='", false);
    //response->getWriter().append(link);
    response->resp->write(link.toLocal8Bit(),false);
    //response->getWriter().append("'><img src='"); // NOI18N
    response->resp->write("'><img src='",false);
    //response->getWriter().append("/frame/" + StringUtil.escapeString(title) + ".png"); // NOI18N
    response->resp->write("/frame/" + StringUtil::escapeString(title).toLocal8Bit() + ".png",false);
    //response->getWriter().append("'></a></td></tr>\n"); // NOI18N
    response->resp->write("'></a></td></tr>\n",false);
   }
  }
  //response->getWriter().append("</table>"); // NOI18N
  response->resp->write("</table>", false);
  //response->getWriter().append(tr(request->getLocale(), "ListFooter")); // NOI18N
  response->resp->write("<DIV class=\"frame-footer\"><A class=\"home\" href=\"/\">[Home]</A>\n<A class=\"help\" href=\"/help/en/html/web/FrameServlet.shtml\">[Help]</A>\n<SPAN class=\"info\">Served by JMRIJFrameServlet</SPAN>\n</DIV></DIV>\n</BODY>\n</HTML>",true);
 }
}
#endif
// Requests for frames are always /frame/<name>.html or /frame/<name>.png
/*private*/ QString JmriJFrameServlet::getFrameName(QString URI) {
    if (!URI.contains(".")) { // NOI18N
        return NULL;
    } else {
        // if request contains parameters, strip those off
        int stop = (URI.contains("?")) ? URI.indexOf("?") : URI.length(); // NOI18N
        QString name = URI.mid(URI.lastIndexOf("/"), stop); // NOI18N
        // URI contains a leading / at this point
        name = name.mid(1, name.lastIndexOf(".")-1); // NOI18N
        name = StringUtil::unescapeString(name); //undo escaped characters
        log->debug(tr("Frame name is %1").arg(name)); // NOI18N
        return name;
    }
}

// The HttpServeletRequest does not like image maps, so we need to process
// the parameter names to see if an image map was clicked
/*protected*/ QMap<QString, QStringList*>* JmriJFrameServlet::populateParameterMap(/*@NonNULL*/ QMap<QString, QStringList*>* map)
{
 QMap<QString, QStringList*>* parameters = new QMap<QString, QStringList*>();
 //map.entrySet().stream().forEach((entry) ->
 QMapIterator<QString, QStringList*> entry(*map);
 while (entry.hasNext())
 {
  entry.next();
  QStringList* value = entry.value();
  QString key = entry.key();
  if (value->at(0).contains("?"))
  { // NOI18N
   // a user's click is in another key's value
   QStringList values = value->at(0).split(QRegExp("\\?")); // NOI18N
   QStringList* l0 = new QStringList(); l0->append(values.at(0));
   QStringList* l1 = new QStringList(); l1->append(values.at(1));
   if (values.at(0).contains(","))
   {
    parameters->insert(key, l1);
    parameters->insert("coords", l0); // NOI18N
   }
   else
   {
    parameters->insert(key,  l0);
    parameters->insert("coords", l1); // NOI18N
   }
  } else if (key.contains(",")) { // NOI18N
   // we have a user's click
   QStringList coords = QVector<QString>(1).toList();
   if (key.contains("?")) { // NOI18N
       // the key is combined
       coords.replace(0, key.mid(key.indexOf("?"))); // NOI18N
       key = key.mid(0, key.indexOf("?") - 1); // NOI18N
       parameters->insert(key, value);
   } else {
       coords.replace( 0, key);
   }
   log->debug(tr("Setting click coords to %1").arg(coords.at(0)));
   parameters->insert("coords", &coords); // NOI18N
  } else {
      parameters->insert(key, value);
  }
 }//);
 return parameters;
}

/*private*/ void JmriJFrameServlet::doClick(JmriJFrame* frame, QString coords) {
    QStringList click = coords.split(","); // NOI18N
    int x = click.at(0).toInt();
    int y = click.at(1).toInt();

    //send click to topmost component under click spot
    QWidget* c = frame->getContentPane()->childAt(x, y);
    log->debug(tr("topmost component is class=%1 object name='%2' parent = %3").arg(c->metaObject()->className()).arg(c->objectName()).arg(c->parentWidget()==NULL?"null":c->parentWidget()->metaObject()->className()));
    sendClick(frame->title(), c, x, y, frame->getContentPane());
//    QObjectList ol = frame->getContentPane()->children();
//    log->debug(tr("content pane contains %1 objects").arg(ol.size()));
//    for(int i =0; i < ol.size(); i++)
//     log->debug(tr(" #%1 = %2(%3)").arg(i).arg(ol.at(i)->metaObject()->className()).arg(ol.at(i)->objectName()));
       if(QString(c->parentWidget()->metaObject()->className()) == "QGraphicsView")
       {
        QGraphicsView* view = (QGraphicsView*)c->parentWidget();
        QGraphicsItem* item = view->itemAt(view->mapFromParent(QPoint(x,y)));
        if(item != NULL)
        {
         log->debug(tr("item is type %1 objname=%2").arg(item->type()).arg(item->toGraphicsObject()?item->toGraphicsObject()->metaObject()->className():"null"));
         MyGraphicsItemGroup* group = qgraphicsitem_cast<MyGraphicsItemGroup*>(item);
         if(group != NULL)
          log->debug(tr("Item name = %2").arg(group->name()));
         QList<QGraphicsItem *> l = item->childItems();
         log->debug(tr("item has %0 children").arg(l.count()));
         if(item->parentItem() != NULL)
         {
          QGraphicsItem* parent = item->parentItem();
          MyGraphicsItemGroup* group = qgraphicsitem_cast<MyGraphicsItemGroup*>(parent);
          if(group != NULL)
           log->debug(tr("Item type %1, name = %2").arg(group->type()).arg(group->name()));
          else
          {
           QGraphicsItem* grandParent = item->parentItem();
           if(grandParent != NULL)
           {
            MyGraphicsItemGroup* group = qgraphicsitem_cast<MyGraphicsItemGroup*>(parent);
            if(group != NULL)
             log->debug(tr("GrandParent type %1, name = %2").arg(group->type()).arg(group->name()));
           }
          }
         }
        }
       }
    //if clicked on background, search for layout editor target pane TODO: simplify id'ing background
#if 0 // done, see below
    if (QString(c->metaObject()->className()) != (/*"jmri.jmrit.display.Editor$TargetPane"*/ "Editor") // NOI18N
            && (qobject_cast<PositionableLabel*>(c) !=NULL)
            && !(qobject_cast<LightIcon*>(c) !=NULL)
            && !(qobject_cast<LocoIcon*>(c) !=NULL)
            && !(qobject_cast<MemoryIcon*>(c) !=NULL)
            && !(qobject_cast<MultiSensorIcon*>(c) !=NULL)
            && !(qobject_cast<PositionableIcon*>(c) !=NULL)
            && !(qobject_cast<ReporterIcon*>(c) !=NULL)
            && !(qobject_cast<RpsPositionIcon*>(c) !=NULL)
            && !(qobject_cast<SlipTurnoutIcon*>(c) !=NULL)
            && !(qobject_cast<TurnoutIcon*>(c) !=NULL))
    {
        clickOnEditorPane(frame->getContentPane(), x, y, frame);
    }
#endif
    if(QString(c->parentWidget()->metaObject()->className()) == "QGraphicsView" )
    {
     QGraphicsView* view = (QGraphicsView*)c->parentWidget();
     QGraphicsItem* item = view->itemAt(view->mapFromParent(QPoint(x,y)));
     if(item != NULL)
     {
      MyGraphicsItemGroup* group = findGroup(item);
      if(group != NULL)
      {
       QString name = group->name();
       if(name == "PositionableLabel" ||
          name == "LightIcon" ||
          name == "LocoIcon" ||
          name == "MemoryIcon" ||
          name == "MultiSensorIcon" ||
          name == "PositionableIcon" ||
          name == "ReporterIcon" ||
          name == "RpsPositionIcon" ||
          name == "SlipTurnoutIcon" ||
          name == "TurnoutIcon"
          )
      {
       QPoint ip = view->mapFromParent(QPoint(x,y));
       clickOnEditorPane(frame->getContentPane(), x, y, frame);
      }
     }
    }
   }
  }

//recursively search components to find editor target pane, where layout editor paints components
/*public*/ void JmriJFrameServlet::clickOnEditorPane(QWidget* c, int x, int y, JmriJFrame* f)
{
 if (QString(c->metaObject()->className()) == (/*"jmri.jmrit.display.Editor$TargetPane"*/ "Editor"))
 { // NOI18N
     log->debug("Sending additional click to Editor$TargetPane");
     //then click on it
     sendClick(f->getTitle(), c, x, y, f);

     //keep looking
 }
 //else if (Container.class.isAssignableFrom(c.getClass()))
 try
 {
  if(Class::forName("QWidget")->isAssignableFrom(c->metaObject()->className()))
  {
      //check this component's children
      for (QObject* child : ((QWidget*) c)->children())
      {
       if(qobject_cast<QWidget*>(child) != NULL)
          clickOnEditorPane((QWidget*)child, x, y, f);
      }
  }
 }
 catch (ClassNotFoundException* ex) {} // ignore if not found
}

/*private*/ MyGraphicsItemGroup* JmriJFrameServlet::findGroup(QGraphicsItem* item)
{
 if(item == NULL)
  return NULL;
 MyGraphicsItemGroup* group =  qgraphicsitem_cast<MyGraphicsItemGroup*>(item);
 if(group != NULL)
  return group;
 return findGroup(item->parentItem());
}

/*private*/ /*final*/ /*static*/ Logger* JmriJFrameServlet::log = LoggerFactory::getLogger("JmriJFrameServlet");
