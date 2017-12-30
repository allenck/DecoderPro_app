#ifndef JSONUTILHTTPSERVICE_H
#define JSONUTILHTTPSERVICE_H
#include "jsonhttpservice.h"
#include "editor.h"

class DccLocoAddress;
class JsonUtilHttpService : public JsonHttpService
{
public:
 /*public*/ JsonUtilHttpService(ObjectMapper mapper, QObject* parent= 0);
 /*public*/ QJsonObject getPanel(QLocale locale, Editor* editor, QString format);
 /*public*/ QJsonArray getPanels(QLocale locale, QString format);
 /*public*/ QJsonArray getPanels(QLocale locale);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException) ;
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject getHello(QLocale locale, int heartbeat);
 /*public*/ QJsonObject getMetadata(QLocale locale, QString name) throw (JsonException);
 /*public*/ QJsonArray getMetadata(QLocale locale) throw (JsonException);
 /*public*/ QJsonObject getNode(QLocale locale);
 /*public*/ QJsonObject getRailroad(QLocale locale);
 /*public*/ QJsonArray getSystemConnections(QLocale locale);
 static /*public*/ DccLocoAddress* addressForString(QString address);
 /*public*/ QJsonArray getNetworkServices(QLocale locale);
 /*public*/ QJsonObject getNetworkService(QLocale locale, QString name) throw (JsonException);

};

#endif // JSONUTILHTTPSERVICE_H
