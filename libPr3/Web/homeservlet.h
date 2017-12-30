#ifndef HOMESERVLET_H
#define HOMESERVLET_H
#include "httpservlet.h"

class HomeServlet : public HttpServlet
{
public:
 HomeServlet();
 /*public*/ QString getServletInfo();

protected:
 /*protected*/ void processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
friend class RequestHandler;
/*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException);
/*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response)
        throw (ServletException, IOException);

};

#endif // HOMESERVLET_H
