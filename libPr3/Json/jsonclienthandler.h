#ifndef JSONCLIENTHANDLER_H
#define JSONCLIENTHANDLER_H

#include <QObject>
#include "jsonexception.h"
#include "logger.h"

class JsonSocketService;
//class Logger;
class JsonConnection;
class JsonClientHandler : public QObject
{
 Q_OBJECT
public:
 explicit JsonClientHandler(JsonConnection* connection, QObject *parent = 0);
 /*public*/ static /*final*/ QString HELLO_MSG;// = "{\"" + JSON.TYPE + "\":\"" + JSON.HELLO + "\"}";
 /*public*/ void dispose();
 /*public*/ void sendHello(int heartbeat) throw (IOException);

signals:

public slots:
 /*public*/ void onMessage(QString string) throw (IOException);
 /*public*/ void onMessage(/*JsonNode*/QJsonObject root) throw (IOException);

private:
 /*private*/ /*final*/ JsonConnection* connection;
 /*private*/ /*final*/ QMap<QString, QSet<JsonSocketService*>*>* services;// = new HashMap<>();
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(JsonClientHandler.class);
 /*private*/ void sendErrorMessage(int code, QString message) /*throw (IOException)*/;
 /*private*/ void sendErrorMessage(JsonException *ex) /*throw (IOException)*/;

};

#endif // JSONCLIENTHANDLER_H
