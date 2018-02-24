#ifndef ABOUTSERVLET_H
#define ABOUTSERVLET_H
#include "httpservlet.h"

class AboutServlet : public HttpServlet
{
public:
 AboutServlet(QObject* parent = 0);
 /*public*/ QString getServletInfo();

protected:
 /*protected*/ void processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response)         throw (ServletException, IOException);
;
 friend class RequestHandler;
};

#endif // ABOUTSERVLET_H
