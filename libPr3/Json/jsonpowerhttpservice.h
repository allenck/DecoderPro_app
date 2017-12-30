#ifndef JSONPOWERHTTPSERVICE_H
#define JSONPOWERHTTPSERVICE_H
#include "jsonhttpservice.h"

class Logger;
class JsonPowerHttpService : public JsonHttpService
{
public:
 /*public*/ JsonPowerHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);


private:
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory.getLogger(JsonPowerHttpService.class);

};

#endif // JSONPOWERHTTPSERVICE_H
