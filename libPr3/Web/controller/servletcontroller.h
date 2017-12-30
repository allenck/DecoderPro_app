#ifndef SERVLETCONTROLLER_H
#define SERVLETCONTROLLER_H
#include "httpserver/httprequest.h"
#include "httpserver/httpresponse.h"
#include "httpserver/httprequesthandler.h"
#include "requestmapper.h"

using namespace stefanfrings;

class ServletController : public HttpRequestHandler
{
 Q_OBJECT
 //Q_DISABLE_COPY(ServletController)
public:
 ServletController(QSettings* listenerSettings);

 /** Generates the response */
 void service(HttpRequest* request, HttpResponse* response, RequestMapper* mapper);

private:
QSettings* listenerSettings;
RequestMapper* mapper;
HttpServlet* servlet;
};

#endif // SERVLETCONTROLLER_H
