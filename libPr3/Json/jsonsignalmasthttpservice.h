#ifndef JSONSIGNALMASTHTTPSERVICE_H
#define JSONSIGNALMASTHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"

class JsonSignalMastHttpService : public JsonNamedBeanHttpService
{
public:
 JsonSignalMastHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
  /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONSIGNALMASTHTTPSERVICE_H
