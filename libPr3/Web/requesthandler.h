/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <../QtWebApp/QtWebApp/httpserver/httprequesthandler.h>
#include "../QtWebApp/QtWebApp/httpserver/httprequest.h"
#include "../QtWebApp/QtWebApp/httpserver/httpresponse.h"
#include "httpservlet.h"
#include "../QtWebApp/httpserver/staticfilecontroller.h"
#include <QWebSocket>

class HttpServlet;
//using namespace stefanfrings;

/**
  The request handler receives incoming HTTP requests and generates responses.
*/

class RequestHandler : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
    //Q_DISABLE_COPY(RequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestHandler(QObject* parent=0);

    /**
      Destructor
    */
    ~RequestHandler();

    /**
      Process an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);
    void websocketTextMessage(QWebSocket *ws, const QString &data);

private:
    HttpServlet* servlet;
    QSettings* listenerSettings;
    stefanfrings::HttpRequest* httpRequest;
    stefanfrings::HttpResponse* httpResponse;
    stefanfrings::StaticFileController* staticFileController;
    QSettings* docRootSettings;
};

#endif // REQUESTHANDLER_H
