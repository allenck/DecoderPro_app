#ifndef JSONSIGNALHEADHTTPSERVICE_H
#define JSONSIGNALHEADHTTPSERVICE_H
#include "jsonnamedbeanhttpservice.h"

class JsonSignalHeadHttpService : public JsonNamedBeanHttpService
{
public:
 /*public*/ JsonSignalHeadHttpService(ObjectMapper mapper, QObject* parent= 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);

};

#endif // JSONSIGNALHEADHTTPSERVICE_H
