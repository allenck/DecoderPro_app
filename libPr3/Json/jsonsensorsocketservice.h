#ifndef JSONSENSORSOCKETSERVICE_H
#define JSONSENSORSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"

class Sensor;
class PropertyChangeEvent;
class JsonSensorHttpService;
class SensorListener;
class JsonSensorSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonSensorSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

public slots:

private:
 /*private*/ /*final*/ JsonSensorHttpService* service;
 /*private*/ /*final*/ QMap<QString, SensorListener*>* sensors;// = new QMap<QString, SensorListener*>();
 /*private*/ QLocale locale;
friend class SensorListener;
};
/*private*/ class SensorListener : public PropertyChangeListener {
 Q_OBJECT
protected:
    /*protected*/ /*final*/ Sensor* sensor;
 JsonSensorSocketService* jsss;
public:
    /*public*/ SensorListener(Sensor* sensor, JsonSensorSocketService* jsss);

public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
 friend class JsonSensorSocketService;
};

#endif // JSONSENSORSOCKETSERVICE_H
