#ifndef JSONPOWERSOCKETSERVICE_H
#define JSONPOWERSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class JsonPowerHttpService;
class JsonPowerSocketService : public JsonSocketService, public PropertyChangeListener
{
 Q_OBJECT
Q_INTERFACES(PropertyChangeListener)
 public:
 /*public*/ JsonPowerSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) /*throw (IOException, JmriException, JsonException)*/  override;
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) /*throw (JsonException)*/ override;
 /*public*/ void onClose() override;

  QObject* self() override {return (QObject*)this;}
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt) override;


private:
 /*private*/ bool listening;// = false;
 /*private*/ /*final*/ JsonPowerHttpService* service;

};

#endif // JSONPOWERSOCKETSERVICE_H
