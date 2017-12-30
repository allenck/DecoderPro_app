#ifndef JSONSERVLET_H
#define JSONSERVLET_H
#include "websocketservlet.h"
#include "jsonqt.h"

class WebSocketServletFactory;
class JsonHttpService;
class ObjectMapper;
class Logger;
class JsonServlet : public WebSocketServlet
{
public:
 JsonServlet(QObject* parent = 0);
 /*public*/ void init() throw (ServletException);
 /*public*/ void destroy();
 /*public*/ void configure(WebSocketServletFactory* factory);
 /*public*/ void sendError(HttpServletResponse* response, int code, QString message) throw (IOException);

private:
 /*private*/ /*transient*/ ObjectMapper mapper;
 /*private*/ /*final*/ /*transient*/ QMap<QString, QSet<JsonHttpService*>* >* services = new QMap<QString, QSet<JsonHttpService*>* >();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(JsonServlet.class);

protected:
 /*protected*/ void doGet(/*final*/ HttpServletRequest* request, HttpServletResponse* response) throw (IOException);
 /*protected*/ void doPost(HttpServletRequest* request, HttpServletResponse* response) throw (IOException);
 /*protected*/ void doPut(HttpServletRequest* request, HttpServletResponse* response) throw (IOException);
 /*protected*/ void doDelete(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException);
friend class RequestHandler;
};

#endif // JSONSERVLET_H
