#ifndef REDIRECTIONSERVLET_H
#define REDIRECTIONSERVLET_H
#include "httpservlet.h"
#include "properties.h"

class Logger;
class Properties;
class RedirectionServlet : public HttpServlet
{
public:
 RedirectionServlet();
 /*public*/ RedirectionServlet(QString urlPattern, QString redirection);

private:
 /*private*/ /*final*/ Properties* redirections = new Properties();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(RedirectionServlet.class);
protected:
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);

};

#endif // REDIRECTIONSERVLET_H
