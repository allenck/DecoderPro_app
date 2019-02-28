#ifndef JSONREPORTERHTTPSERVICE_H
#define JSONREPORTERHTTPSERVICE_H
#include "jsonhttpservice.h"

class JsonReporterHttpService : public JsonHttpService
{
public:
 JsonReporterHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONREPORTERHTTPSERVICE_H
