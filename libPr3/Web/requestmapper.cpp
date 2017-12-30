/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include "requestmapper.h"
#include "logging/filelogger.h"
#include "httpserver/staticfilecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/templatecontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"
#include "controller/servletcontroller.h"
#include <QApplication>
#include "jsonclienthandler.h"
#include "jsonconnection.h"

using namespace stefanfrings;

/** Redirects log messages to a file */
//extern FileLogger* logger;

/** Controller for static files */
extern StaticFileController* staticFileController;
//extern HttpRequestHandler* httpRequestHandler;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("RequestMapper: created");
    listenerSettings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
}


RequestMapper::~RequestMapper()
{
    qDebug("RequestMapper: deleted");
}


void RequestMapper::service(HttpRequest* request, HttpResponse* response)
{
    QByteArray path=request->getPath();
    qDebug("RequestMapper: path=%s",path.data());

    // For the following pathes, each request gets its own new instance of the related controller.
    if (path.startsWith("/dump"))
    {
        DumpController().service(request, response);
    }

    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }

    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }

    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }
    else
     if(path.startsWith("/servlet"))
    {
      ServletController(listenerSettings).service(request, response, this);
    }
    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }
    qDebug("RequestMapper: finished request");
#if 0
    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
#endif

}

void RequestMapper::websocketTextMessage(QWebSocket *ws, const QString &data)
{
 qDebug() << data;
 JsonClientHandler* handler = new JsonClientHandler(new JsonConnection(ws));
 handler->onMessage(data);
}

void RequestMapper::setServlet(HttpServlet* servlet)
{
 this->servlet = servlet;
}
HttpServlet* RequestMapper::getServlet()
{
 return this->servlet;
}
