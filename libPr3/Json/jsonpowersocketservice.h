#ifndef JSONPOWERSOCKETSERVICE_H
#define JSONPOWERSOCKETSERVICE_H
#include "jsonsocketservice.h"

class PropertyChangeEvent;
class JsonPowerHttpService;
class JsonPowerSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 /*public*/ JsonPowerSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) ;
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (JsonException);
 /*public*/ void onClose();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);


private:
 /*private*/ bool listening;// = false;
 /*private*/ /*final*/ JsonPowerHttpService* service;

};

#endif // JSONPOWERSOCKETSERVICE_H
