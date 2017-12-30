#ifndef JSONMEMORYHTTPSERVICE_H
#define JSONMEMORYHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"

class JsonMemoryHttpService : public JsonNamedBeanHttpService
{
public:
 /*public*/ JsonMemoryHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONMEMORYHTTPSERVICE_H
