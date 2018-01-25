/**
  @file
  @author Stefan Frings
*/

#include <logging/filelogger.h>
#include "requesthandler.h"
#include "rosterservlet.h"
#include "httpserver/staticfilecontroller.h"
#include "httpserver/httprequest.h"
#include <QApplication>
#include "httpservletrequest.h"
#include "httpservletresponse.h"
#include "fileutil.h"
#include <QApplication>
#include "jsonclienthandler.h"
#include "jsonconnection.h"
#include "configservlet.h"
#include "homeservlet.h"
#include "jmrijframeservlet.h"
#include "servletutil.h"
#include "panelservlet.h"
#include "controlpanelservlet.h"
#include "directoryhandler.h"
#include "jsonservlet.h"
#include "layoutpanelservlet.h"
#include "denialservlet.h"
#include "operationsservlet.h"
#include "defaultservletconfig.h"

/** Logger class */
//extern FileLogger* logger;

/** Controller for static files */
//extern StaticFileController* staticFileController;

RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{
 qDebug("RequestHandler: created");
 docRootSettings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
 docRootSettings->beginGroup("docroot");
 docRootSettings->setValue("path", FileUtil::getProgramPath() + "web" /*+ File::separator*/);
 staticFileController = new stefanfrings::StaticFileController(docRootSettings);

}


RequestHandler::~RequestHandler()
{
 qDebug("RequestHandler: deleted");
}

void RequestHandler::service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response)
{
 httpRequest = &request;
 httpResponse = &response;
 QString path=request.getPath();
 path = path.replace("//", "/").replace("%20", " ").replace( "%23","#");

 //qDebug(tr("Controller: path=%s").arg(QString(path.data())));
 qDebug() << tr("Controller: path=%1").arg(QString(path.data()));
;
//    // Set a response header
//    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

//    // Return a simple HTML document
//    response.write("<html><body>Hello World</body></html>",true);

//    qDebug("RequestHandler: finished request");
 HttpServletRequest* req = new HttpServletRequest(httpRequest);
 HttpServletResponse* resp = new HttpServletResponse(httpResponse);
 //Q_ASSERT(!path.startsWith("/prefs"));
 //@WebServlet(name = "HomeServlet",
 //        urlPatterns = {
 //            "/", // default
 //            "/index.html", // redirect to default since ~ 1 FEB 2014
 //            "/prefs/index.html" // some WiThrottle clients require this URL to show web services
 if(path == "" || path == "/" || path == "/index.html" || path == "/prefs/index.html")
 {
  servlet = new HomeServlet();
  ((HomeServlet*)servlet)->processRequest(req, resp);
  return;
 }
 if(path == "/prefs" || path == "/web" || path == "/dist" || path == "/images" || path == "xml/signals")
 {
  DirectoryHandler* handler = new DirectoryHandler();
  if(path == "/prefs")
  {
   QString newPath = FileUtil::getPreferencesPath();
   handler->doDirectory(req, resp,  Resource::newResource(newPath));
   return;
  }
  if(path == "/web")
  {
   QString newPath = FileUtil::getProgramPath() + "web";
   handler->doDirectory(req, resp,  Resource::newResource(newPath));
   return;
  }
  if(path == "/dist")
  {
   QString newPath = FileUtil::getProgramPath() ;
   handler->doDirectory(req, resp,  Resource::newResource(newPath));
   return;
  }
  if(path == "/images")
  {
   QString newPath = FileUtil::getProgramPath() + "web"+ File::separator + "images";
   handler->doDirectory(req, resp,  Resource::newResource(newPath));
   return;
  }
  if(path == "/xml/signals")
  {
   QString newPath = FileUtil::getProgramPath() + "xml"+ File::separator + "signals";
   handler->doDirectory(req, resp,  Resource::newResource(newPath));
   return;
  }
 }
 if(path.startsWith("/json"))
 {
  JsonServlet* servlet = new JsonServlet();
  servlet->init();
  servlet->doGet(req,resp);
  return;
 }
 if(path == "/prefs/networkServices")
 {
  DenialServlet* servlet = new DenialServlet();
  servlet->doGet(req, resp);
  return;
 }
 if(path.startsWith("/panel/ControlPanel"))
 {
  servlet = new ControlPanelServlet();
  ((ControlPanelServlet*)servlet)->doGet(req, resp);
  return;
 }
 if(path.startsWith("/panel/Layout"))
 {
  servlet = new LayoutPanelServlet();
  ((LayoutPanelServlet*)servlet)->doGet(req, resp);
  return;
 }

 if(path == "/panel" || path == "/panel/" || path.startsWith("/panel/Panel") )//|| path.startsWith("/panel/Layout") || path == "/panel/panel" || path ==   "/web/showPanel.html") // redirect to /panel/ since ~ 19 Jan 2014
 {
  ServletConfig*  config = new DefaultServletConfig("PanelServlet", req);
  servlet = new PanelServlet();
  servlet->init(config);
  servlet->init();
  ((PanelServlet*)servlet)->doGet(req, resp);
  return;
 }

 if(path.startsWith( "/frame"))
 {
  servlet = new JmriJFrameServlet();
  if(path == "/frame")
   ((JmriJFrameServlet*)servlet)->doList(req,resp);
  else
   ((JmriJFrameServlet*)servlet)->doGet(req,resp);
  return;
 }


 QStringList sl = path.split('/');
 if(((sl.size()>= 3) && sl.at(1) == "servlet") || ((sl.size() == 2) && (sl.at(1) == "roster")) || ((sl.size() > 3) && (sl.at(2)== "entry")))
 {
  QString prefix;
  if(sl.size() >= 3)
  {
   prefix = sl.at(2);
   QDir::setCurrent(FileUtil::getProgramPath() + "web" + File::separator + "servlet");
  }
  else
  {
   prefix = sl.at(1);
   QDir::setCurrent(FileUtil::getProgramPath() + "web" + File::separator + "servlet" + File::separator + "roster");
  }
  if(prefix == "roster" || prefix == "entry" )
  {
   servlet = new RosterServlet();
   if((sl.size() > 2) && (sl.at(2)=="entry"))
    ((RosterServlet*)servlet)->doEntry(req, resp);
   else
    servlet->doList(req,resp);
   return;
  }
  if(path.startsWith("/roster" ))
  {
   servlet = new RosterServlet();
   ((RosterServlet*)servlet)->doGet(req, resp);
   return;
  }
  else
  {
   if( prefix == "config")
   {
    servlet = new ConfigServlet();
   ((ConfigServlet*)servlet)->processRequest(req,resp);
    return;
   }
  }
 }
 else  if(path.startsWith("/roster" ))
 {
  servlet = new RosterServlet();
  ServletConfig*  config = new DefaultServletConfig("RosterServlet", req);
  servlet->init(config);
  servlet->init();
  return;
 }
 else if(path.startsWith("/operations" ))
 {
  servlet = new OperationsServlet();
  ServletConfig*  config = new DefaultServletConfig("OperationsServlet", req);
  servlet->init(config);
  servlet->init();
  ((OperationsServlet*)servlet)->doGet(req, resp);
  return;
 }
 else
 {
  if(path.endsWith("panel.js") )
  {
   qDebug() << "calling staticFileController " << path;
  }
  staticFileController->service(request, response);
 }

 // Clear the log buffer
//    if (logger)
//    {
//       logger->clear();
//    }
}
void RequestHandler::websocketTextMessage(QWebSocket *ws, const QString &data)
{
 qDebug() << data;
 JsonClientHandler* handler = new JsonClientHandler(new JsonConnection(ws));
 handler->onMessage(data);
}


