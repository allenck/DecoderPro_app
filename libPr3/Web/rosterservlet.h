#ifndef ROSTERSERVLET_H
#define ROSTERSERVLET_H
#include "httpservlet.h"
#include "loggerfactory.h"
#include "file.h"

class RosterServlet : public HttpServlet
{
 Q_OBJECT
public:
 RosterServlet();
 ~RosterServlet() {}
 RosterServlet(const RosterServlet&) : HttpServlet() {}
 /*public*/ void init() throw (ServletException);

private:

 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(RosterServlet.class.getName());
 void doImage(HttpServletRequest* request, HttpServletResponse* response, File* file) /*throw (IOException)*/;

protected:
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/;
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/;
 /*protected*/ void doGroup(HttpServletRequest* request, HttpServletResponse* response, QString group) /*throw (IOException)*/;
 /*protected*/ void doList(HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/;
 /*protected*/ void doEntry(HttpServletRequest* request, HttpServletResponse* response) /*throw (IOException)*/;
 /*protected*/ void doRoster(HttpServletRequest* request, HttpServletResponse* response, QJsonObject filter) /*throw (IOException)*/;
friend class RequestHandler;
};
Q_DECLARE_METATYPE(RosterServlet)
#endif // ROSTERSERVLET_H
