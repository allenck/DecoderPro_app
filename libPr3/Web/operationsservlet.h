#ifndef OPERATIONSSERVLET_H
#define OPERATIONSSERVLET_H
#include "httpservlet.h"
#include "jsonqt.h"

class OperationsServlet : public HttpServlet
{
 Q_OBJECT
public:
 OperationsServlet();
 /*public*/ void init() throw (ServletException);
 /*public*/ QString getServletInfo();

private:
 /*private*/ ObjectMapper mapper;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("OperationsServlet");
 /*private*/ void processManifest(QString id, HttpServletRequest* request, HttpServletResponse* response) throw (IOException);

protected:
 /*protected*/ void processRequest(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException );
 /*protected*/ void processTrains(HttpServletRequest* request, HttpServletResponse* response) throw (IOException);
 /*private*/ void processConductor(QString id, HttpServletRequest* request, HttpServletResponse* response) throw (IOException);
 /*protected*/ void doGet(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
 /*protected*/ void doPut(HttpServletRequest* request, HttpServletResponse* response)
         throw (ServletException, IOException);
friend class RequestHandler;
};

#endif // OPERATIONSSERVLET_H
