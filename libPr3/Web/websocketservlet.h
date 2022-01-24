#ifndef WEBSOCKETSERVLET_H
#define WEBSOCKETSERVLET_H
#include "httpservlet.h"

class WebSocketServlet : public HttpServlet
{
public:
 WebSocketServlet();

private:
// /*private*/ static /*final*/ long serialVersionUID;// = 1L;
// /*private*/ static /*final*/ byte[] WS_ACCEPT =
//         "258EAFA5-E914-47DA-95CA-C5AB0DC85B11".getBytes(
//                 B2CConverter.ISO_8859_1);
// /*private*/ static /*final*/ StringManager sm =
//         StringManager.getManager(Constants.Package);

// /*private*/ /*final*/ Queue<MessageDigest> sha1Helpers =
//         new ConcurrentLinkedQueue<MessageDigest>();
 /*private*/ QList<QString> getTokensFromHeader(HttpServletRequest* req, QString headerName);
 /*private*/ QString getWebSocketAccept(QString key) /*throw (ServletException)*/;
 /*private*/ bool headerContainsToken(HttpServletRequest* req, QString headerName, QString target);



protected:
 /*protected*/ void doGet(HttpServletRequest* req, HttpServletResponse* resp)throw (ServletException, IOException);
 /*protected*/ bool verifyOrigin(QString origin);
 /*protected*/ QString selectSubProtocol(QList<QString> subProtocols);
 /*protected*/ /*abstract*/ virtual QTextStream* createWebSocketInbound(QString subProtocol,
         HttpServletRequest* request);

};

#endif // WEBSOCKETSERVLET_H
