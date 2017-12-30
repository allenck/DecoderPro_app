#include "servletcontroller.h"
#include "httpserver/staticfilecontroller.h"
#include "rosterservlet.h"
using namespace stefanfrings;
ServletController::ServletController(QSettings* listenerSettings) : HttpRequestHandler()
{
 this->listenerSettings = listenerSettings;
 this->mapper == NULL;
}

void ServletController::service(HttpRequest *request, HttpResponse *response, RequestMapper *mapper)
{
 this->mapper = mapper;
 QString path = request->getPath();
 QStringList sl = path.split('/');
 QString prefix = sl.at(2);

 // TODO: hard coded for now, must implement servlet registration to obtain servlet client handler
 if(prefix == "roster")
  mapper->setServlet(servlet = new RosterServlet());

 if(servlet != NULL)
 {
  HttpServletRequest* req = new HttpServletRequest(request);
  HttpServletResponse* resp = new HttpServletResponse(response);
  servlet->doList(req, resp);
 }
 else
   StaticFileController(listenerSettings).service(request, response);

}
