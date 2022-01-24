#ifndef JSONTURNOUTHTTPSERVICE_H
#define JSONTURNOUTHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"

class JsonTurnoutHttpService : public JsonNamedBeanHttpService
{
public:
 JsonTurnoutHttpService(ObjectMapper mapper,QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) /*throw (JsonException)*/;
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) /*throw (JsonException)*/;
 /*public*/ QJsonValue doPut(QString type, QString name, QJsonObject data, QLocale locale) /*throw (JsonException)*/;
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) /*throw (JsonException)*/;

};

#endif // JSONTURNOUTHTTPSERVICE_H
