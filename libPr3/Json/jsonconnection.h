#ifndef JSONCONNECTION_H
#define JSONCONNECTION_H
#include "jmriconnection.h"
#include "jsonqt.h"

class JsonConnection : public JmriConnection
{
public:
 JsonConnection(QObject* parent = 0);
 /*public*/ JsonConnection(Session* connection, QObject* parent = 0);
 /*public*/ JsonConnection(QWebSocket* connection, QObject* parent = 0);
 /*public*/ JsonConnection(DataOutputStream* output, QObject* parent = 0) ;
 /*public*/ ObjectMapper getObjectMapper() ;
 /*public*/ void sendMessage(QJsonObject message) /*throw (IOException)*/;
 /*public*/ void sendMessage(QJsonArray message) /*throw (IOException)*/;
 /*public*/ void sendMessage(QJsonValue message) /*throw (IOException)*/;


private:
 /*private*/ /*final*/ ObjectMapper objectMapper;// = new ObjectMapper();

};

#endif // JSONCONNECTION_H
