#include "jsonlightsocketservice.h"
#include "json.h"
#include "jsonlighthttpservice.h"
#include "proxylightmanager.h"
#include "light.h"
#include "instancemanager.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonLightSocketService extends JsonSocketService {


/*public*/ JsonLightSocketService::JsonLightSocketService(JsonConnection* connection, QObject *parent) : JsonSocketService(connection, parent) {
    //super(connection);
    this->service = new JsonLightHttpService(connection->getObjectMapper());
 lights = new QMap<QString, LightListener*>();
}

//@Override
/*public*/ void JsonLightSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    QString name = data.value(JSON::NAME).toString();
    if (data.value(JSON::METHOD).toString()==(JSON::PUT)) {
        this->connection->sendMessage(this->service->doPut(type, name, data, locale));
    } else {
        this->connection->sendMessage(this->service->doPost(type, name, data, locale));
    }
    if (!this->lights->contains(name)) {
        Light* light = ((ProxyLightManager*)InstanceManager::getDefault("LightManager"))->getLight(name);
        if (light != NULL) {
            LightListener* listener = new LightListener(light, this);
            //light.addPropertyChangeListener(listener);
            connect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
            this->lights->insert(name, listener);
        }
    }
}

//@Override
/*public*/ void JsonLightSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonLightSocketService::onClose() {
    //lights.values().stream().forEach((light) ->
    foreach(LightListener* listener, lights->values())
    {
        //light.removePropertyChangeListener(light);
     disconnect(listener->light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

    }//);
    lights->clear();
}

///*private*/ class LightListener implements PropertyChangeListener {

//    protected /*final*/ Light light;

    /*public*/ LightListener::LightListener(Light* light,JsonLightSocketService* jlss) {
        this->light = light;
 this->jlss = jlss;
    }

    //@Override
    /*public*/ void LightListener::propertyChange(PropertyChangeEvent* e) {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName()==("KnownState")) {
            try {
                try {
                    jlss->connection->sendMessage(jlss->service->doGet(JSON::LIGHT, this->light->getSystemName(), jlss->locale));
                } catch (JsonException ex) {
                    jlss->connection->sendMessage(ex.getJsonMessage());
                }
            } catch (IOException ex) {
                // if we get an error, de-register
                //light.removePropertyChangeListener(this);
          disconnect(light->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

                jlss->lights->remove(this->light->getSystemName());
            }
        }
    }
