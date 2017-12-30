#include "rosterservlet.h"
#include "json.h"
#include "servletutil.h"
#include <QJsonObject>
#include "roster.h"
#include "rosterentry.h"
#include "file.h"
#include "fileutil.h"
#include "servletcontext.h"
#include "jsonrosterservicefactory.h"
#include "instancemanager.h"
#include "stringutil.h"
#include "httpservletresponse.h"
#include "httpservletrequest.h"
#include "jsonrosterhttpservice.h"
#include <QDataStream>

RosterServlet::RosterServlet() : HttpServlet()
{

}
/**
 * Provide roster data to HTTP clients.
 *
 * Each method of this Servlet responds to a unique URL pattern.
 *
 * @author Randall Wood
 */
/*
 * TODO: Implement an XSLT that respects newlines in comments.
 * TODO: Include decoder defs and CVs in roster entry response->
 *
 */
//@WebServlet(name = "RosterServlet",
//        urlPatterns = {
//            "/roster", // default
//            "/prefs/roster.xml", // redirect to /roster?format=xml since ~ 9 Apr 2012
//        })
///*public*/ class RosterServlet extends HttpServlet {

    ///*private*/ transient ObjectMapper mapper;

    /*private*/ /*final*/ /*static*/ Logger* RosterServlet::log = LoggerFactory::getLogger("RosterServlet");

 //@Override
/*public*/ void RosterServlet::init() throw (ServletException) {
 if (this->getServletContext()->getContextPath() == ("/roster")) { // NOI18N
     //this->mapper = new ObjectMapper();
 }
}

/**
 * Route the request and response to the appropriate methods.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws java.io.IOException if communications is cut with client
 */
//@Override
/*protected*/ void RosterServlet::doGet(HttpServletRequest* request, HttpServletResponse* response) throw (IOException)
{
 if ( request->getRequestURI() == ("/prefs/roster.xml"))
 { // NOI18N
  response->sendRedirect("/roster?format=xml"); // NOI18N
  return;
 }
 if ( request->getPathInfo().length() == 1)
 {
  this->doList(request, response);
 }
 else
 {
  // split the path after removing the leading /
  QStringList pathInfo =  request->getPathInfo().mid(1).split("/"); // NOI18N
  if(pathInfo.at(0) == JSON::LIST)
  {
   this->doList(request, response);
  }
  else if(pathInfo.at(0) == JSON::GROUP)
  {
   if (pathInfo.length() == 2)
   {
    this->doGroup(request, response, pathInfo[1]);
   }
   else
   {
    this->doList(request, response);
   }
  }
  else
  {
   this->doEntry(request, response);
  }
 }
}

/**
 * Handle POST requests. POST requests are treated as GET requests.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws java.io.IOException if communications is cut with client
 * @see #doGet(javax.servlet.http.HttpServletRequest,
 * javax.servlet.http.HttpServletResponse)
 */
//@Override
/*protected*/ void RosterServlet::doPost(HttpServletRequest* request, HttpServletResponse* response) throw (IOException) {
    this->doGet(request, response);
}

/**
 * Get a roster group.
 *
 * Lists roster entries in the specified group and return an XML document
 * conforming to the JMRI JSON schema. This method can be passed multiple
 * filters matching the filter in {@link jmri.jmrit.roster.Roster#getEntriesMatchingCriteria(java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)
 * }. <b>Note:</b> Any given filter can be specified only once.
 *
 * This method responds to the following GET URL patterns: <ul>
 * <li>{@code/roster/group/<group name>}</li>
 * <li>{@code/roster/group/<group name>?filter=filter[&filter=filter]}</li>
 * </ul>
 *
 * This method responds to the POST URL {@code/roster/group/<group name>}
 * with a JSON payload for the filter.
 *
 * @param request  servlet request
 * @param response servlet response
 * @param group    The group name
 * @throws java.io.IOException if communications is cut with client
 */
/*protected*/ void RosterServlet::doGroup(HttpServletRequest* request, HttpServletResponse* response, QString group) throw (IOException)
{
 log->debug(tr("(Getting group %1").arg(group));
 QJsonObject data;
 if ( request->getContentType() != NULL &&  request->getContentType().contains(ServletUtil::UTF8_APPLICATION_JSON))
 {
  QJsonDocument doc = QJsonDocument::fromJson(request->getReader()->readLine().toLocal8Bit());
  data =  QJsonDocument::fromJson(request->req->getBody()).object();         //this->mapper.readTree( request->getReader());
  if (data.value(JSON::DATA).isObject()) {
      data = data.value(JSON::DATA).toObject();
  }
 }
 else {
  data = QJsonObject(); //this->mapper.createObjectNode();
  foreach (QString filter,  request->getParameterMap()->keys())
  {
   if (filter == (JSON::ID))
   {
       data.insert(JSON::NAME, QUrl( request->getParameter(filter)).toString());
   } else {
       data.insert(filter, QUrl( request->getParameter(filter)).toString());
   }
  }
 }
 data.insert(JSON::GROUP, QUrl(group).toString());
 log->debug(tr("Getting roster with %1").arg(data.value(JSON::GROUP).toString()));
 this->doRoster(request, response, data);
}

/**
 * List roster entries.
 *
 * Lists roster entries and return an XML document conforming to the JMRI
 * Roster XML schema. This method can be passed multiple filter filter
 * matching the filter in
 * {@link jmri.jmrit.roster.Roster#getEntriesMatchingCriteria(java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)}.
 * <b>Note:</b> Any given filter can be specified only once.
 *
 * This method responds to the following GET URL patterns: <ul>
 * <li>{@code/roster/}</li> <li>{@code/roster/list}</li>
 * <li>{@code/roster/list?filter=filter[&filter=filter]}</li> </ul>
 *
 * This method responds to POST URLs <code>/roster</code> and
 * <code>/roster/list</code> with a JSON payload for the filter.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws java.io.IOException if communications is cut with client
 */
/*protected*/ void RosterServlet::doList(HttpServletRequest* request, HttpServletResponse* response) throw (IOException)
{
 QJsonObject data;
 if ( request->getContentType() != NULL &&  request->getContentType().contains(ServletUtil::UTF8_APPLICATION_JSON))
 {
  QJsonDocument doc = QJsonDocument::fromJson(request->getReader()->readLine().toLocal8Bit());
  data = QJsonDocument::fromJson(request->req->getBody()).object(); //this->mapper.readTree( request->getReader());
  if (data.value(JSON::DATA).isObject())
  {
   data =  data.value(JSON::DATA).toObject();
  }
 }
 else
 {
  data = QJsonObject();//this->mapper.createObjectNode();
  for (QString filter :  request->getParameterMap()->keys())
  {
   QUrl url = QUrl::fromEncoded(request->getParameter(filter).toLocal8Bit());
   if(filter == JSON::GROUP)
   {
    QString group = url.toString();
    if (group != (Roster::AllEntries( request->getLocale())))
    {
        data.insert(JSON::GROUP, group);
    }
   }
   else if(filter== JSON:: ID)
   {
    data.insert(JSON::NAME, url.toString());
   }
   else
   {
    {
    }
    data.insert(filter, url.toString());
   }
  }
 }
 this->doRoster(request, response, data);
}

/**
 * Provide the XML representation of a roster entry given its ID.
 *
 * Lists roster entries and return an XML document conforming to the JMRI
 * Roster XML schema. Requests for roster entry images and icons can include
 * width and height specifiers, and always return PNG images.
 *
 * This method responds to the following URL patterns: <ul>
 * <li>{@code/roster/<ID>}</li> <li>{@code/roster/entry/<ID>}</li>
 * <li>{@code/roster/<ID>/image}</li> <li>{@code/roster/<ID>/icon}</li></ul>
 * <b>Note:</b> The use of the term <em>entry</em> in URLs is optional.
 *
 * Images and icons can be rescaled using the following parameters:<ul>
 * <li>height</li> <li>maxHeight</li> <li>minHeight</li> <li>width</li>
 * <li>maxWidth</li> <li>minWidth</li></ul>
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws java.io.IOException if communications is cut with client
 */
/*protected*/ void RosterServlet::doEntry(HttpServletRequest* request, HttpServletResponse* response) throw (IOException)
{
 QStringList pathInfo =  request->getPathInfo().mid(1).split("/");
 int idOffset = 0;
 QString type = NULL;
 if (pathInfo.at(0) == ("entry"))
 {
  if (pathInfo.length() == 1)
  {
   // path must be /roster/<id> or /roster/entry/<id>
   response->sendError(HttpServletResponse::SC_BAD_REQUEST);
  }
  idOffset = 1;
 }
 QString id = pathInfo[idOffset];
 if (pathInfo.length() > (1 + idOffset))
 {
  type = pathInfo[pathInfo.length() - 1];
 }
 RosterEntry* re = Roster::getDefault()->getEntryForId(id);
 try
 {
  if (re == NULL)
  {
   response->sendError(HttpServletResponse::SC_NOT_FOUND, "Could not find roster entry " + id);
  }
  else if (type == NULL || type == ("entry"))
  {
   // this should be an entirely different format than the table
   QJsonObject obj = QJsonObject();
   obj.insert(JSON::ID, id);
   this->doRoster(request, response, obj);
  }
  else if (type == (JSON::IMAGE))
  {
   if (re->getImagePath() != NULL)
   {
    this->doImage(request, response, FileUtil::getFile(re->getImagePath()));
   }
   else
   {
    response->sendError(HttpServletResponse::SC_NOT_FOUND);
   }
  }
  else if (type == (JSON::ICON))
  {
   int function = -1;
   if (pathInfo.length() != (2 + idOffset))
   {
    function = pathInfo.at(pathInfo.length() - 2).mid(1).toInt();
   }
   if (function == -1)
   {
    if (re->getIconPath() != NULL)
    {
     this->doImage(request, response, FileUtil::getFile(re->getIconPath()));
    }
    else
    {
     response->sendError(HttpServletResponse::SC_NOT_FOUND);
    }
   }
   else if (re->getFunctionImage(function) != NULL)
   {
    this->doImage(request, response, FileUtil::getFile(re->getFunctionImage(function)));
   }
   else
   {
    response->sendError(HttpServletResponse::SC_NOT_FOUND);
   }
  }
  else if (type == (JSON::SELECTED_ICON))
  {
   if (pathInfo.length() != (2 + idOffset)) {
       int function = pathInfo.at(pathInfo.length() - 2).mid(1).toInt();
       this->doImage(request, response, FileUtil::getFile(re->getFunctionSelectedImage(function)));
   }
  }
  else if (type == ("file"))
  {
   ServletUtil::getInstance()->writeFile(response, new File(Roster::getDefault()->getRosterLocation(), "roster" + File::separator + re->getFileName()), ServletUtil::UTF8_APPLICATION_XML); // NOI18N
  }
  else if (type == ("throttle"))
  {
   ServletUtil::getInstance()->writeFile(response, new File(FileUtil::getUserFilesPath(), "throttle" + File::separator + id + ".xml"), ServletUtil::UTF8_APPLICATION_XML); // NOI18N
  }
  else
  {
   // don't know what to do
   response->sendError(HttpServletResponse::SC_BAD_REQUEST);
  }
 } catch (NullPointerException ex)
 {
  // triggered by instanciating a File with NULL path
  // this would happen when an image or icon is requested for a
  // rosterEntry that has no such image or icon associated with it
  response->sendError(HttpServletResponse::SC_NOT_FOUND);
 }
}

/**
 * Generate the JSON, XML, or HTML output specified by {@link #doList(javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)},
 * {@link #doGroup(javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse, java.lang.String)},
 * or
 * {@link #doEntry(javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)}.
 *
 * @param request  servlet request with format and locale for response
 * @param response servlet response
 * @param filter   a JSON object with name-value pairs of parameters for
 *                 {@link jmri.jmrit.roster.Roster#getEntriesMatchingCriteria(java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String, java.lang.String)}.
 * @throws java.io.IOException if communications is cut with client
 */
/*protected*/ void RosterServlet::doRoster(HttpServletRequest* request, HttpServletResponse* response, QJsonObject filter) throw (IOException)
{
 ServletUtil::getInstance()->setNonCachingHeaders(response);
//    log->debug(tr("Getting roster with filter %1").arg(QJsonDocument(filter).toJson()));
 QString group = (!filter.value(JSON::GROUP).isNull()) ? filter.value(JSON::GROUP).toString() : NULL;
 log->debug(tr("Group %1 was in filter").arg(group));

 QString format =  request->getParameter(JSON::FORMAT);
 if (format == NULL)
 {
  format = "";
 }
 if(format== JSON::_JSON)
 {
  response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
//            JsonRosterServiceFactory* factory = InstanceManager::getOptionalDefault("JsonRosterServiceFactory".orElseGet(() -> {
//                return InstanceManager.setDefault(JsonRosterServiceFactory.class, new JsonRosterServiceFactory());
//            });
  JsonRosterServiceFactory* factory = (JsonRosterServiceFactory*)InstanceManager::getOptionalDefault("JsonRosterServiceFactory");
  if(factory == NULL)
  {
   InstanceManager::setDefault("JsonRosterServiceFactory", factory = new JsonRosterServiceFactory() );
#if 1
  //response->getWriter()->print(factory->getHttpService(mapper).getRoster( request->getLocale(), filter));
   QJsonArray array = ((JsonRosterHttpService*)factory->getHttpService(/*mapper*/ObjectMapper()))->getRoster(request->getLocale(), filter);
   QJsonDocument doc = QJsonDocument(array);
   response->resp->write(doc.toJson(),true);
#endif
  }
 }
 else if( format == JSON::XML)
 {
  response->setContentType(ServletUtil::UTF8_APPLICATION_XML);
  File* roster = new File(Roster::getDefault()->getRosterIndexPath());
  if (roster->exists())
  {
#if 1
   //response->getWriter()->print(FileUtil::readFile(roster));
   response->resp->write(FileUtil::readFile(roster).toLocal8Bit(),true);
#endif
  }
 }
 else if( format == "html")
 {
  QString row;
  if ("simple" == ( request->getParameter("view")))
  {
   row = FileUtil::readURL(FileUtil::findURL(tr( "SimpleTableRow.html")));
  } else {
   row = FileUtil::readURL(FileUtil::findURL(tr( "TableRow.html")));
  }
  QString builder;// = new StringBuilder();
  response->setContentType(ServletUtil::UTF8_TEXT_HTML); // NOI18N
  if (Roster::AllEntries( request->getLocale()) == (group))
  {
   group = "";
  }
  QList<RosterEntry*> entries = Roster::getDefault()->getEntriesMatchingCriteria(
          (!filter.value(JSON::ROAD).isNull()) ? filter.value(JSON::ROAD).toString() : "",
          (!filter.value(JSON::NUMBER).isNull()) ? filter.value(JSON::NUMBER).toString() : "",
          (!filter.value(JSON::ADDRESS).isNull()) ? filter.value(JSON::ADDRESS).toString() : NULL,
          (!filter.value(JSON::MFG).isNull()) ? filter.value(JSON::MFG).toString() : NULL,
          (!filter.value(JSON::DECODER_MODEL).isNull()) ? filter.value(JSON::DECODER_MODEL).toString() : "",
          (!filter.value(JSON::DECODER_FAMILY).isNull()) ? filter.value(JSON::DECODER_FAMILY).toString() : "",
          (!filter.value(JSON::NAME).isNull()) ? filter.value(JSON::NAME).toString() : NULL,
          group
  );
  //entries.stream().forEach((entry) ->
  foreach(RosterEntry* entry, entries)
  {
   // NOTE: changing the following order will break JavaScript and HTML code
#if 0
   builder.append(tr(/*request.getLocale(),*/ row.toLocal8Bit()).arg(
                               entry->getId()).arg(
                               entry->getRoadName()).arg(
                               entry->getRoadNumber()).arg(
                               entry->getMfg()).arg(
                               entry->getModel()).arg(
                               entry->getOwner()).arg(
                               entry->getDccAddress()).arg(
                               entry->getDecoderModel()).arg(
                               entry->getDecoderFamily()).arg(
                               entry->getDecoderComment()).arg(
                               entry->getComment()).arg(
                               entry->getURL()).arg(
                               entry->getMaxSpeedPCT()).arg(
                               entry->getFileName()).arg(
                               StringUtil::escapeString(entry->getId())

   // get function buttons in a formatting loop
   // get attributes in a formatting loop
   ));
#endif
    builder = builder + row;
    builder = builder.replace("%1$s", entry->getId());
    builder = builder.replace("%2$s", entry->getRoadName());
    builder = builder.replace("%3$s", entry->getRoadNumber());
    builder = builder.replace("%4$s", entry->getMfg());
    builder = builder.replace("%5$s", entry->getModel());
    builder = builder.replace("%6$s", entry->getOwner());
    builder = builder.replace("%7$s", entry->getDccAddress());
    builder = builder.replace("%8$s", entry->getDecoderModel());
    builder = builder.replace("%9$s", entry->getDecoderFamily());
    builder = builder.replace("%10$s", entry->getDecoderComment());
    builder = builder.replace("%11$s", entry->getComment());
    builder = builder.replace("%12$s", entry->getURL());
    builder = builder.replace("%13$s%", QString::number(entry->getMaxSpeedPCT()));
    builder = builder.replace("%14$s", entry->getFileName());
    builder = builder.replace("%15$s", StringUtil::escapeString(entry->getId()));
   }
   //response->getWriter()->print(builder);
   response->resp->write(builder.toLocal8Bit(), true);
  }
  else
  {
   if (group == NULL)
   {
    group = Roster::AllEntries( request->getLocale());
   }
   response->setContentType(ServletUtil::UTF8_TEXT_HTML); // NOI18N
#if 1
   /*response->getWriter()->print*/

//   QString out =QString(
//           FileUtil::readURL(FileUtil::findURL(tr( /*request->getLocale(),*/ "web/servlet/roster/Roster.html"))).toLocal8Bit()).arg(
//           tr(
//                   tr( /*request->getLocale(),*/ "%2$s | %1$s").arg(
//                   ServletUtil::getInstance()->getRailroadName(false)).arg(
//                   tr( /*request->getLocale(),*/ "Roster")).toLocal8Bit()
//           ).arg(
//           ServletUtil::getInstance()->getNavBar( request->getLocale(),  request->getContextPath())).arg(
//           ServletUtil::getInstance()->getRailroadName(false)).arg(
//           ServletUtil::getInstance()->getFooter( request->getLocale(),  request->getContextPath()).arg(
//           group)
//   ));
   QString out = FileUtil::readURL(FileUtil::findURL(tr( /*request->getLocale(),*/ "web/servlet/roster/Roster.html")));
   QString title = tr("%2 | %1").arg(ServletUtil::getInstance()->getRailroadName(false)).arg(tr( /*request->getLocale(),*/ "Roster"));
   out = out.replace("%1$s", title);
   out =out.replace("%2$s", ServletUtil::getInstance()->getNavBar( request->getLocale(),  request->getContextPath()));
   out = out.replace("%4$s", ServletUtil::getInstance()->getFooter( request->getLocale(),  request->getContextPath()));
   out = out.replace("%1$s", ServletUtil::getInstance()->getRailroadName(false));
   out = out.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
   out = out.replace("%5$s", group);
//   qDebug() << out;
   response->resp->write(out.toLocal8Bit(),true);

#endif
 }
}

/**
 * Process the image for a roster entry image or icon  request->
 *
 * @param file     {@link java.io.File} object containing an image
 * @param request  contains parameters for drawing the image
 * @param response sends a PNG image or a 403 Not Found error.
 * @throws java.io.IOException if communications is cut with client
 */
void RosterServlet::doImage(HttpServletRequest* request, HttpServletResponse* response, File* file) throw (IOException) {
#if 1
    QImage image;
    //try {
        image = QImage(file->getPath());/*ImageIO.read(file);*/
    if(image.isNull()) {
        // file not found or unreadable
        response->sendError(HttpServletResponse::SC_NOT_FOUND);
        return;
    }
    QString fname = file->getName();
    int height = image.height();
    int width = image.width();
    int pWidth = width;
    int pHeight = height;
    if ( request->getParameter("maxWidth") != NULL) {
        pWidth = ( request->getParameter("maxWidth").toInt());
        if (pWidth < width) {
            width = pWidth;
        }
        log->debug(tr("%1 @maxWidth: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if ( request->getParameter("minWidth") != NULL) {
        pWidth =  (request->getParameter("minWidth").toInt());
        if (pWidth > width) {
            width = pWidth;
        }
        log->debug(tr("%1 @minWidth: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if ( request->getParameter("width") != NULL) {
        width = ( request->getParameter("width").toInt());
    }
    if (width != image.width()) {
        height = (int) (height * (1.0 * width / image.width()));
        pHeight = height;
        log->debug(tr("%1 @adjusting height: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if ( request->getParameter("maxHeight") != NULL) {
        pHeight = ( request->getParameter("maxHeight").toInt());
        if (pHeight < height) {
            height = pHeight;
        }
        log->debug(tr("%1 @maxHeight: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if ( request->getParameter("minHeight") != NULL) {
        pHeight = ( request->getParameter("minHeight").toInt());
        if (pHeight > height) {
            height = pHeight;
        }
        log->debug(tr("%1 @minHeight: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if ( request->getParameter("height") != NULL) {
        height = ( request->getParameter("height").toInt());
        log->debug(tr("%1 @height: width: %2, pWidth: %3, height: %5, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    if (height != image.height() && width == image.width()) {
        width = (int) (width * (1.0 * height / image.height()));
        log->debug(tr("%1 @adjusting width: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    }
    log->debug(tr("%1 @responding: width: %2, pWidth: %3, height: %4, pHeight: %5").arg(fname).arg(width).arg(pWidth).arg(height).arg(pHeight));
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    if (height != image.height() || width != image.width()) {
        QImage resizedImage =  image.scaled(width, height); //image.getType());
//        Graphics2D g = resizedImage.createGraphics();
//        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
//        g.drawImage(image, 0, 0, width, height, 0, 0, image.getWidth(), image.getHeight(), NULL);
//        g.dispose();
//        // ImageIO needs the simple type ("jpeg", "png") instead of the mime type ("image/jpeg", "image/png")
//        ImageIO.write(resizedImage, "png", baos);
        resizedImage.save(&buffer, "PNG");
    } else {
        //ImageIO.write(image, "png", baos);
     image.save(&buffer, "PNG");
    }
    //baos.close();
    response->setContentType(ServletUtil::IMAGE_PNG);
    response->setStatus(HttpServletResponse::SC_OK);
//    response->setContentLength(ba->size());
//    response->getOutputStream()->write(baos.toByteArray());
    response->resp->write(ba,true);
//    response->getOutputStream().close();

#endif
}
