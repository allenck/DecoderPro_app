#ifndef JSONSENSORHTTPSERVICE_H
#define JSONSENSORHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"
#include "jsonqt.h"
#include "jsonexception.h"

class JsonSensorHttpService : public JsonNamedBeanHttpService
{
 Q_OBJECT
public:
 JsonSensorHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONSENSORHTTPSERVICE_H
