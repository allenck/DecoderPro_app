#ifndef JMRICONNECTION_H
#define JMRICONNECTION_H

#include <QObject>
#include <exceptions.h>
#include <QTextStream>
#include <QWebSocket>
#include "logger.h"

//class Logger;
class Session;
typedef QTextStream DataOutputStream;
class JmriConnection : public QObject
{
 Q_OBJECT
public:
 explicit JmriConnection(QObject *parent = 0);
 ///*public*/ JmriConnection(Session* connection, QObject *parent = 0);
 /*public*/ JmriConnection(QWebSocket* connection, QObject *parent = 0);
 /*public*/ JmriConnection(DataOutputStream* output, QObject *parent = 0);
// /*public*/ Session* getSession();
 /*public*/ QWebSocket* getSocket();
 //QT_DEPRECATED /*public*/ Session* getWebSocketConnection();
// /*public*/ void setSession(Session* session);
 //QT_DEPRECATED /*public*/ void setWebSocketConnection(Session* webSocketConnection);
 /*public*/ DataOutputStream* getDataOutputStream();
 /*public*/ void setDataOutputStream(DataOutputStream* dataOutputStream);
 /*public*/ void sendMessage(QString message) /*throw (IOException)*/;
 /*public*/ void close() /*throw (IOException)*/;
 /*public*/ QLocale getLocale();
 /*public*/ void setLocale(QLocale locale);

signals:

public slots:
 void on_socketDisconnected();

private:
 void common();
 /*private*/ Session* session;// = null;
 /*private*/ QWebSocket* webSocket;
 /*private*/ DataOutputStream* dataOutputStream;// = null;
 /*private*/ QLocale locale;// = Locale.getDefault();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(JmriConnection.class);


};

#endif // JMRICONNECTION_H
