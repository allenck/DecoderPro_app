#ifndef DENIALSERVLET_H
#define DENIALSERVLET_H
#include "httpservlet.h"

class DenialServlet : public HttpServlet
{
public:
 DenialServlet();

protected:
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
friend class RequestHandler;
};

#endif // DENIALSERVLET_H
