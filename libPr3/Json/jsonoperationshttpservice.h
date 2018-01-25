#ifndef JSONOPERATIONSHTTPSERVICE_H
#define JSONOPERATIONSHTTPSERVICE_H
#include "jsonhttpservice.h"

class JsonOperationsHttpService : public JsonHttpService
{
public:
 /*public*/ JsonOperationsHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);
 /*public*/ QJsonArray getCars(QLocale locale);
 /*public*/ QJsonArray getEngines(QLocale locale);
 /*public*/ QJsonArray getLocations(QLocale locale) throw (JsonException);
 /*public*/ void setTrain(QLocale locale, QString id, QJsonObject data) throw (JsonException);


private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("JsonOperationsHttpService");

};

#endif // JSONOPERATIONSHTTPSERVICE_H
