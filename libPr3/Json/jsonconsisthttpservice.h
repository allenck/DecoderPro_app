#ifndef JSONCONSISTHTTPSERVICE_H
#define JSONCONSISTHTTPSERVICE_H
#include "jsonhttpservice.h"
#include "dcclocoaddress.h"
#include "jsonconsistmanager.h"
#include "json.h"

class JsonConsistManager;
class JsonConsistHttpService : public JsonHttpService
{
 Q_OBJECT
public:
 JsonConsistHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ void doDelete(QString type, QString name, QLocale locale) throw (JsonException) ;
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException) ;
 /*public*/ QJsonObject getConsist(QLocale locale, DccLocoAddress* address) throw (JsonException);

private:
 /*final*/ JsonConsistManager* manager; // default package visibility
friend class JsonConsistSocketService;
friend class JsonConsistListListener;
friend class JsonConsistListener;
};

#endif // JSONCONSISTHTTPSERVICE_H
