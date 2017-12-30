/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httpserver/httprequesthandler.h"
#include <QWebSocket>
#include "httpservlet.h"

namespace stefanfrings {

/**
  The request mapper dispatches incoming HTTP requests to controller classes
  depending on the requested path.
*/

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
    //Q_DISABLE_COPY(RequestMapper)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestMapper(QObject* parent=0);

    /**
      Destructor.
    */
    ~RequestMapper();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(stefanfrings::HttpRequest* request, stefanfrings::HttpResponse* response);

    void websocketTextMessage(QWebSocket *ws, const QString &data);
    void setServlet(HttpServlet*);

 private:
    QSettings* listenerSettings;// = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    HttpServlet* servlet;
    HttpServlet* getServlet();
    friend class ServletController;
};
} // end namespace
#endif // REQUESTMAPPER_H
