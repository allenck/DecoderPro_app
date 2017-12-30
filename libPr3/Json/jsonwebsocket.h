#ifndef JSONWEBSOCKET_H
#define JSONWEBSOCKET_H

#include <QObject>
#include "jsonconnection.h"
#include "jsonclienthandler.h"
#include "quietshutdowntask.h"
#include "exceptions.h"


class SocketTimeoutException : public Exception
{
 SocketTimeoutException(Exception* throwable) : Exception(throwable) {}
};

class JsonWebSocket : public QObject
{
 Q_OBJECT
public:
 explicit JsonWebSocket(QObject *parent = 0);
 /*public*/ void onOpen(/*Session*/QWebSocket* sn);
 /*public*/ void onClose(int i, QString string);
 /*public*/ void onError(Throwable* thrwbl);

signals:

public slots:
 /*public*/ void onMessage(QString string);

private:
 /*private*/ JsonConnection* connection;
 /*private*/ JsonClientHandler* handler;
 /*private*/ QuietShutDownTask* shutDownTask;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JsonWebSocket.class);

protected:
 /*protected*/ JsonConnection* getConnection();
 friend class JWSShutdownTask;
};

class JWSShutdownTask : public QuietShutDownTask
{
 Q_OBJECT
 JsonWebSocket* jws;
public:
 JWSShutdownTask(QString text, JsonWebSocket* jws);
 /*public*/ bool execute();
};

#endif // JSONWEBSOCKET_H
