/**
  @file
  @author Stefan Frings
*/

#ifndef SESSIONCONTROLLER_H
#define SESSIONCONTROLLER_H

#include "httpserver/httprequest.h"
#include "httpserver/httpresponse.h"
#include "httpserver/httprequesthandler.h"
#include "httpserver/httpsessionstore.h"

using namespace stefanfrings;

/**
  This controller demonstrates how to use sessions.
*/

class SessionController : public HttpRequestHandler {
    Q_OBJECT
    //Q_DISABLE_COPY(SessionController)
public:

    /** Constructor */
    SessionController();

    /** Generates the response */
    void service(HttpRequest* request, HttpResponse* response);

private:
    HttpSessionStore* sessionStore;
};

#endif // SESSIONCONTROLLER_H
