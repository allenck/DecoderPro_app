#include "jsonsensorsocketservice.h"
#include "json.h"
#include "jsonsensor.h"
#include "jsonsensorhttpservice.h"
#include "instancemanager.h"
#include "proxysensormanager.h"
#include "sensor.h"

/**
 * JSON Socket service for {@link jmri.Sensor}s.
 *
 * @author Randall Wood
 */
///*public*/ class JsonSensorSocketService extends JsonSocketService {


/*public*/ JsonSensorSocketService::JsonSensorSocketService(JsonConnection* connection, QObject* parent) :JsonSocketService(connection, parent)
{
 //super(connection);
 this->service = new JsonSensorHttpService(connection->getObjectMapper());
 this->sensors = new QMap<QString, SensorListener*>();
}

//@Override
/*public*/ void JsonSensorSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    QString name = data.value(JSON::NAME).toString();
    if (data.value(JSON::METHOD).toString() == (JSON::PUT))
    {
        this->connection->sendMessage(this->service->doPut(type, name, data, locale));
    } else {
        this->connection->sendMessage(this->service->doPost(type, name, data, locale));
    }
    if (!this->sensors->contains(name))
    {
        Sensor* sensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->getSensor(name);
        if (sensor != NULL) {
            SensorListener* listener = new SensorListener(sensor, this);
            //sensor.addPropertyChangeListener(listener);
            connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
            this->sensors->insert(name, listener);
        }
    }
}

//@Override
/*public*/ void JsonSensorSocketService::onList(QString type, /*JsonNode*/ QJsonObject /*data*/, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonSensorSocketService::onClose() {
    //sensors.values().stream().forEach((listener) ->
    foreach(SensorListener* listener, sensors->values())
    {
        //listener.sensor.removePropertyChangeListener(listener);
     disconnect(listener->sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),listener, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
    sensors->clear();
}

///*private*/ class SensorListener implements PropertyChangeListener {

//    protected /*final*/ Sensor sensor;

    /*public*/ SensorListener::SensorListener(Sensor* sensor, JsonSensorSocketService* jsss) {
        this->sensor = sensor;
 this->jsss = jsss;
    }

    //@Override
    /*public*/ void SensorListener::propertyChange(PropertyChangeEvent* e) {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName() == ("KnownState")) {
            try {
                try {
                    jsss->connection->sendMessage(jsss->service->doGet(JSON::SENSOR, this->sensor->getSystemName(), jsss->locale));
                } catch (JsonException ex) {
                    jsss->connection->sendMessage(ex.getJsonMessage());
                }
            } catch (IOException* ex) {
                // if we get an error, de-register
                //sensor->removePropertyChangeListener(this);
          disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)));
                jsss->sensors->remove(this->sensor->getSystemName());
            }
        }
    }
//}
