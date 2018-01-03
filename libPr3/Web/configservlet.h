#ifndef CONFIGSERVLET_H
#define CONFIGSERVLET_H
#include "httpservlet.h"

class ConfigServlet : public HttpServlet
{
 Q_OBJECT
public:
 ConfigServlet();
 /*public*/ QString getServletInfo();

protected:
 /*protected*/ void processRequest(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
friend class RequestHandler;
};

#endif // CONFIGSERVLET_H
