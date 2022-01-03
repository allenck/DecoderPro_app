#include "operationsservlet.h"
#include "loggerfactory.h"
#include "operationsmanager.h"
#include "servletutil.h"
#include "jsonoperations.h"
#include "servletcontext.h"
#include "json.h"
#include "jsonserver.h"
#include "train.h"
#include "trainmanager.h"
#include "jsonexception.h"
#include "carmanager.h"
#include "jsonutil.h"
#include "../operations/engine.h"
#include "htmlmanifest.h"
#include "setup.h"
#include "../operations/route.h"
#include "jsonmanifest.h"
#include "webserver.h"
#include "htmlconductor.h"
#include "stringescapeutils.h"
#include "../operations/engine.h"
#include "instancemanager.h"

OperationsServlet::OperationsServlet() : HttpServlet()
{

}
/**
 *
 * @author Randall Wood (C) 2014
 * @author Steve Todd (C) 2013
 */
//@WebServlet(name = "OperationsServlet",
//        urlPatterns = {
//            "/operations", // default
//            "/web/operationsConductor.html", // redirect to default since ~ 13 May 2014
//            "/web/operationsManifest.html", // redirect to default since ~ 13 May 2014
//            "/web/operationsTrains.html" // redirect to default since ~ 13 May 2014
//        })
///*public*/ class OperationsServlet extends HttpServlet {


/*private*/ /*final*/ /*static*/ Logger* OperationsServlet::log = LoggerFactory::getLogger("OperationsServlet");

//@Override
/*public*/ void OperationsServlet::init() throw (ServletException) {
    // only do complete initialization for default path, not redirections
    if (this->getServletContext()->getContextPath() == ("/operations")) { // NOI18N
        this->mapper =  ObjectMapper();
        // ensure all operations managers are functional before handling first request
        InstanceManager::getDefault("Operations::OperationsManager");
    }
}

/*
 * Valid paths are:
 * /operations/trains -or- /operations - get a list of trains for operations
 * /operations/manifest/id - get the manifest for train with Id "id"
 * /operations/conductor/id - get the conductor's screen for train with Id "id"
 */
/*protected*/ void OperationsServlet::processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException ){
    if (request->getRequestURI() == ("/web/operationsConductor.html") // NOI18N
            || request->getRequestURI() == ("/web/operationsManifest.html") // NOI18N
            || request->getRequestURI() == ("/web/operationsTrains.html")) { // NOI18N
        response->sendRedirect("/operations"); // NOI18N
        return;
    }
    QStringList pathInfo = request->getPathInfo().mid(1).split("/");
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    if (pathInfo[0] == ("") || (pathInfo[0] == ( JsonOperations::TRAINS) && pathInfo.length() == 1)) {
        this->processTrains(request, response);
    } else {
        if (pathInfo.length() == 1) {
            response->sendError(HttpServletResponse::SC_BAD_REQUEST);
        } else {
            QString id = pathInfo[1];
            QString report = pathInfo[0];
            if (report == ( JsonOperations::TRAINS) && pathInfo.length() == 3) {
                report = pathInfo[2];
            }
            log->debug(tr("Handling %1 with id %2").arg(report).arg(id));
            if (report == ("manifest")) {
                this->processManifest(id, request, response);
            } else if (report == ("conductor")) {
                this->processConductor(id, request, response);
            } else if (report == ("trains")) {
                // TODO: allow for editing/building/reseting train
                log->warn("Unhandled request for \"trains\"");
                response->sendError(HttpServletResponse::SC_BAD_REQUEST);
            } else {
                // Don't know what to do
                log->warn(tr("Unparsed request for \"%1\"").arg(report));
                response->sendError(HttpServletResponse::SC_BAD_REQUEST);
            }
        }
    }
}

/*protected*/ void OperationsServlet::processTrains(HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/
{
#if 1
 if (JSON::_JSON == (request->getParameter("format")))
 {
  response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
  try
  {
//         JsonUtil* utilities = new JsonUtil(this->mapper);
      //response->getWriter().print(utilities->getTrains(request->getLocale()));
   response->resp->write(QJsonDocument(JsonUtil::getTrains(request->getLocale())).toJson());
  }
  catch (JsonException ex)
  {
   int code = ex.getJsonMessage().value(JSON::DATA).toObject().value(JsonException::CODE).toInt(200);
//         response->sendError(code, (new ObjectMapper()).writeValueAsString(ex.getJsonMessage()));
   response->sendError(code, QJsonDocument(ex.getJsonMessage()).toJson());
  }
 }
 else if ("html" == (request->getParameter("format")))
 {
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
  bool showAll = ("all" == (request->getParameter("show")));
  //StringBuilder html = new StringBuilder();
  QString html;
  QString format = FileUtil::readURL(FileUtil::findURL("web/servlet/operations/TrainsSnippet.html"));
  foreach (Operations::Train* train, ((Operations::TrainManager*)InstanceManager::getDefault("OperationsTrainManager"))->getTrainsByNameList())
  {
   if (showAll || !((Operations::CarManager*)InstanceManager::getDefault("Operations::CarManager"))->getByTrainDestinationList(train)->isEmpty())
   {
//       html.append(String.format(request->getLocale(), format,
//               train.getIconName(),
//               StringEscapeUtils.escapeHtml4(train.getDescription()),
//               train.getLeadEngine() != NULL ? train.getLeadEngine().toString() : "",
//               StringEscapeUtils.escapeHtml4(train.getTrainDepartsName()),
//               train.getDepartureTime(),
//               train.getStatus(),
//               StringEscapeUtils.escapeHtml4(train.getCurrentLocationName()),
//               StringEscapeUtils.escapeHtml4(train.getTrainTerminatesName()),
//               StringEscapeUtils.escapeHtml4(train.getTrainRouteName()),
//               train.getId()
//       ));
    html = html + format;
    html = html.replace("%1$s", train->getIconName());
    html = html.replace("%2$s", StringEscapeUtils::escapeHtml4(train->getDescription()));
    html = html.replace("%3$s", (train->getLeadEngine() != NULL ? train->getLeadEngine()->toString() : ""));
    html = html.replace("%4$s", train->getTrainDepartsName());
    html = html.replace("%5$s", train->getDepartureTime());
    html = html.replace("%6$s", train->getStatus());
    html = html.replace("%7$s", train->getCurrentLocationName());
    html = html.replace("%8$s", train->getTrainTerminatesName());
    html = html.replace("%9$s", train->getTrainRouteName());
    html = html.replace("%10$s", train->getId());
   }
  }
  //response->getWriter().print(html.toString());
  response->resp->write(html.toLocal8Bit(), true);
 }
 else
 {
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//  response->getWriter().print(String.format(request->getLocale(),
//          FileUtil::readURL(FileUtil::findURL(Bundle.getMessage(request->getLocale(), "Operations.html"))),
//          String.format(request->getLocale(),
//                  Bundle.getMessage(request->getLocale(), "HtmlTitle"),
//                  ServletUtil::getInstance().getRailroadName(false),
//                  Bundle.getMessage(request->getLocale(), "TrainsTitle")
//          ),
//          ServletUtil::getInstance().getNavBar(request->getLocale(), request->getContextPath()),
//          ServletUtil::getInstance().getRailroadName(false),
//          ServletUtil::getInstance().getFooter(request->getLocale(), request->getContextPath()),
//          "" // no train Id
//  ));
  QString contextPath = request->getContextPath();
  QString out = FileUtil::readURL(FileUtil::findURL(tr(/*request->getLocale(),*/ "web/servlet/operations/Operations.html")));
  QString title = tr("%2 | %1").arg(ServletUtil::getInstance()->getRailroadName(false)).arg(tr( /*request->getLocale(),*/ "Trains"));
  out = out.replace("%1$s", title);
  out = out.replace("%2$s", ServletUtil::getInstance()->getNavBar( request->getLocale(),  contextPath));
  out = out.replace("%4$s", ServletUtil::getInstance()->getFooter( request->getLocale(),  contextPath));
  out = out.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
  out = out.replace("%5$s", "");
  qDebug() << out;
  response->resp->write(out.toLocal8Bit(),true);
 }
#endif
}

/*private*/ void OperationsServlet::processManifest(QString id, HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/
{
 Operations::Train* train = ((Operations::TrainManager*)InstanceManager::getDefault("OperationsTrainManager"))->getTrainById(id);
 log->debug(tr("train id=%1 name=%2 %3").arg(id).arg(train->getName()).arg(train->getDescription()));
#if 1
 if ("html" == (request->getParameter("format")))
 {
  log->debug(tr("Getting manifest HTML code for train %1").arg(id));
  Operations::HtmlManifest* manifest = new Operations::HtmlManifest(request->getLocale(), train);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//     response->getWriter().print(String.format(request->getLocale(),
//             FileUtil::readURL(FileUtil::findURL(Bundle.getMessage(request->getLocale(), "ManifestSnippet.html"))),
//             train.getIconName(),
//             StringEscapeUtils.escapeHtml4(train.getDescription()),
//             Setup.isPrintValidEnabled() ? manifest.getValidity() : "",
//             StringEscapeUtils.escapeHtml4(train.getComment()),
//             Setup.isPrintRouteCommentsEnabled() ? train.getRoute().getComment() : "",
//             manifest.getLocations()
//     ));
  QString snippet = FileUtil::readURL(FileUtil::findURL(tr( "web/servlet/operations/ManifestSnippet.html")));
  snippet = snippet.replace("%1$s", train->getIconName());
  snippet = snippet.replace("%2$s", StringEscapeUtils::escapeHtml4(train->getDescription()));
  snippet = snippet.replace("%3$s", (Operations::Setup::isPrintValidEnabled() ? manifest->getValidity() : ""));
  snippet = snippet.replace("%4$s", StringEscapeUtils::escapeHtml4(train->getComment()));
  snippet = snippet.replace("%5$s", (Operations::Setup::isPrintRouteCommentsEnabled() ? train->getRoute()->getComment() : ""));
  snippet = snippet.replace("%6$s", manifest->getLocations());
  response->resp->write(snippet.toLocal8Bit(), true);
 }
 else if (QString(JSON::_JSON) == (request->getParameter("format")))
 {
     log->debug(tr("Getting manifest JSON code for train %1").arg(id));
     //QJsonObject manifest = this->mapper.readTree(new JsonManifest(train).getFile());
     File* file = Operations::JsonManifest(train).getFile();
     QFile f(file->getPath());
     if(!f.open(QIODevice::ReadOnly)) throw  new FileNotFoundException(f.fileName());
     QTextStream is(&f);
     QJsonObject manifest = QJsonDocument::fromBinaryData(is.readAll().toLocal8Bit()).object();
     if (manifest.value(JSON::IMAGE).isString())
     {
      manifest.insert(JSON::IMAGE, WebServer::URIforPortablePath(FileUtil::getPortableFilename(manifest.value(JSON::IMAGE).toString())));
     }
     //QString content = this->mapper.writeValueAsString(manifest);
     QByteArray content = QJsonDocument(manifest).toBinaryData();
     response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
//     response->setContentLength(content.getBytes(UTF8).length);
//     response->getWriter().print(content);
     response->resp->write(content,true);
 }
 else
 {
     response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//     response->getWriter().print(String.format(request->getLocale(),
//             FileUtil::readURL(FileUtil::findURL(Bundle.getMessage(request->getLocale(), "Operations.html"))),
//             String.format(request->getLocale(),
//                     Bundle.getMessage(request->getLocale(), "HtmlTitle"),
//                     ServletUtil::getInstance().getRailroadName(false),
//                     String.format(request->getLocale(),
//                             Bundle.getMessage(request->getLocale(), "ManifestTitle"),
//                             train.getIconName(),
//                             StringEscapeUtils.escapeHtml4(train.getDescription())
//                     )
//             ),
//             ServletUtil::getInstance().getNavBar(request->getLocale(), request->getContextPath()),
//             !train.getRailroadName() == ("") ? train.getRailroadName() : ServletUtil::getInstance().getRailroadName(false),
//             ServletUtil::getInstance().getFooter(request->getLocale(), request->getContextPath()),
//             train.getId()
//     ));
     QString html = FileUtil::readURL(FileUtil::findURL(tr("web/servlet/operations/Operations.html")));
     QString manifestTitle = tr("%1$s (%2$s) Manifest");
     manifestTitle = manifestTitle.replace("%1$s", train->getIconName());
     manifestTitle = manifestTitle.replace("%2$s", StringEscapeUtils::escapeHtml4(train->getDescription()));
     QString title = tr("%2 | %1").arg(ServletUtil::getInstance()->getRailroadName(false)).arg(manifestTitle);
     html = html.replace("%1$s", title);
     html = html.replace("%2$s", ServletUtil::getInstance()->getNavBar(request->getLocale(), request->getContextPath()));
     html = html.replace("%3$s", train->getRailroadName() != ("") ? train->getRailroadName() : ServletUtil::getInstance()->getRailroadName(false));
     html = html.replace("%4$s", ServletUtil::getInstance()->getFooter(request->getLocale(), request->getContextPath()));
     html = html.replace("%5$s", train->getId());
     response->resp->write(html.toLocal8Bit(), true);
 }
#endif
}

/*private*/ void OperationsServlet::processConductor(QString id, HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/
{
 Operations::Train* train = ((Operations::TrainManager*)InstanceManager::getDefault("OperationsTrainManager"))->getTrainById(id);
 QJsonObject data;
#if 1
 if (request->getContentType() != NULL && request->getContentType().contains(ServletUtil::APPLICATION_JSON))
 {
     //data = this->mapper.readTree(request->getReader());
  data =  QJsonDocument::fromJson(request->req->getBody()).object();  //QJsonDocument::fromJson(string.toUtf8());
     if (!data.value(JSON::DATA).isUndefined()) {
         data = data.value(JSON::DATA).toObject();
     }
 } else {
     data = QJsonObject(); //this->mapper.createObjectNode();
     ( data).insert("format", request->getParameter("format"));
 }
 if (data.value("format").toString() == ("html"))
 {
  if (!data.value( JsonOperations::LOCATION).isUndefined())
  {
   QString location = data.value(JsonOperations::LOCATION).toString();
   if (location == (JSON::_NULL) || train->getNextLocationName() == (location))
   {
    train->move();
    return; // done property change will cause update to client
   }
  }
  log->debug(tr("Getting conductor HTML code for train %1").arg(id));
  Operations::HtmlConductor* conductor = new Operations::HtmlConductor(request->getLocale(), train);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
  //response->getWriter().print(conductor.getLocation());
  response->resp->write(conductor->getLocation().toLocal8Bit(),true);
 }
 else
 {
  response->setContentType(ServletUtil::UTF8_TEXT_HTML);
//  response->resp->write(String::format(request->getLocale(),
//          FileUtil::readURL(FileUtil::findURL(tr( "web/servlet/operations/Operations.html"))),
//          String::format(request->getLocale(),
//                  tr( "%2$s | %1$s"),
//                  ServletUtil::getInstance()->getRailroadName(false),
//                  String::format(request->getLocale(),
//                          tr( "%1$s (%2$s) Conductor"),
//                          train->getIconName(),
//                          QString(QUrl(train->getDescription()).toEncoded()
//                  )
//          ),
//          ServletUtil::getInstance()->getNavBar(request->getLocale(), request->getContextPath()),
//          train->getRailroadName() != ("") ? train->getRailroadName() : ServletUtil::getInstance()->getRailroadName(false),
//          ServletUtil::getInstance()->getFooter(request->getLocale(), request->getContextPath()),
//          train->getId()
//  )).toLocal8Bit(), true);
  QString html = FileUtil::readURL(FileUtil::findURL(tr("web/servlet/operations/Operations.html")));
  QString manifestTitle = tr("%1$s (%2$s) Manifest");
  manifestTitle = manifestTitle.replace("%1$s", train->getIconName());
  manifestTitle = manifestTitle.replace("%2$s", StringEscapeUtils::escapeHtml4(train->getDescription()));
  QString title = tr("%1 | %2").arg(ServletUtil::getInstance()->getRailroadName(false)).arg(manifestTitle);
  html = html.replace("%1$s", title);
  html = html.replace("%2$s", ServletUtil::getInstance()->getNavBar(request->getLocale(), request->getContextPath()));
  html = html.replace("%3$s", train->getRailroadName() != ("") ? train->getRailroadName() : ServletUtil::getInstance()->getRailroadName(false));
  html = html.replace("%4$s", ServletUtil::getInstance()->getFooter(request->getLocale(), request->getContextPath()));
  html = html.replace("%5$s", train->getId());
  response->resp->write(html.toLocal8Bit(), true);
 }
#endif
}
// <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">

/**
 * Handles the HTTP <code>GET</code> method.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
//@Override
/*protected*/ void OperationsServlet::doGet(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Handles the HTTP <code>POST</code> method.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
//@Override
/*protected*/ void OperationsServlet::doPost(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Handles the HTTP <code>PUT</code> method.
 *
 * @param request  servlet request
 * @param response servlet response
 * @throws ServletException if a servlet-specific error occurs
 * @throws IOException      if an I/O error occurs
 */
//@Override
/*protected*/ void OperationsServlet::doPut(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException) {
    processRequest(request, response);
}

/**
 * Returns a short description of the servlet.
 *
 * @return a String containing servlet description
 */
//@Override
/*public*/ QString OperationsServlet::getServletInfo() {
    return "Operations Servlet";
}// </editor-fold>
