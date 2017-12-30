#ifndef JSONLIGHTHTTPSERVICE_H
#define JSONLIGHTHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"

class JsonLightHttpService : public JsonNamedBeanHttpService
{
 Q_OBJECT
public:
 JsonLightHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) ;
 /*public*/ QJsonObject doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONLIGHTHTTPSERVICE_H
