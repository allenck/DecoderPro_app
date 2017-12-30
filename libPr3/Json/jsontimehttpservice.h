#ifndef JSONTIMEHTTPSERVICE_H
#define JSONTIMEHTTPSERVICE_H
#include "jsonhttpservice.h"

class JsonTimeHttpService : public JsonHttpService
{
public:
 /*public*/ JsonTimeHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONTIMEHTTPSERVICE_H
