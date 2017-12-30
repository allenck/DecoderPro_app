#ifndef JSONTIMESOCKETSERVICE_H
#define JSONTIMESOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangeevent.h"

class JsonTimeHttpService;
class JsonTimeSocketService : public JsonSocketService
{
public:
 JsonTimeSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ void onClose();
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);

private:
 /*private*/ bool listening = false;
 /*private*/ /*final*/ JsonTimeHttpService* service;

};

#endif // JSONTIMESOCKETSERVICE_H
