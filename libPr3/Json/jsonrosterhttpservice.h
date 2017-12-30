#ifndef JSONROSTERHTTPSERVICE_H
#define JSONROSTERHTTPSERVICE_H

#include "jsonhttpservice.h"

class RosterEntry;
class JsonRosterHttpService : public JsonHttpService
{
public:
 /*public*/ JsonRosterHttpService(ObjectMapper mapper, QObject* parent = 0);
 /*public*/ QJsonValue doGet(QString type, QString name, QLocale locale) throw (JsonException);
 /*public*/ QJsonObject doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException);

 /*public*/ QJsonValue doGetList(QString type, QLocale locale) throw (JsonException);
 /*public*/ QJsonArray getRoster(/*@NonNUll*/ QLocale locale, /*@NonNUll*/ QJsonObject data);
 /*public*/ QJsonValue getRosterEntry(QLocale locale, QString id) throw (JsonException);
 /*public*/ QJsonValue getRosterEntry(QLocale locale, /*@NonNUll*/ RosterEntry* entry);
 /*public*/ QJsonArray getRosterGroups(QLocale locale) throw (JsonException);
 /*public*/ QJsonObject getRosterGroup(QLocale locale, QString name) throw (JsonException);

};

#endif // JSONROSTERHTTPSERVICE_H
