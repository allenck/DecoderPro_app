#include "jsonsignalmastsocketservice.h"
#include "jsonsignalmasthttpservice.h"
#include "jsonsignalmastsocketservice.h"
#include "jsonsignalmast.h"
#include "json.h"
#include "signalmastmanager.h"
#include "instancemanager.h"
/**
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalMastSocketService extends JsonSocketService {


/*public*/ JsonSignalMastSocketService::JsonSignalMastSocketService(JsonConnection* connection, QObject* parent): JsonSocketService(connection, parent)
{
 //super(connection);
 signalMasts = new QMap<QString, SignalMastListener*>();

 this->service = new JsonSignalMastHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonSignalMastSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    QString name = data.value(JSON::NAME).toString();
    if (data.value(JSON::METHOD).toString() == (JSON::PUT)) {
        this->connection->sendMessage(this->service->doPut(type, name, data, locale));
    } else {
        this->connection->sendMessage(this->service->doPost(type, name, data, locale));
    }
    if (!this->signalMasts->contains(name)) {
        SignalMast* signalMast =((SignalMastManager*) InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
        if (signalMast != NULL) {
            SignalMastListener* listener = new SignalMastListener(signalMast, this);
            //signalMast.addPropertyChangeListener(listener);
            connect(signalMast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),listener,                    SLOT(propertyChange(PropertyChangeEvent*)));
            this->signalMasts->insert(name, listener);
        }
    }
}

//@Override
/*public*/ void JsonSignalMastSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonSignalMastSocketService::onClose() {
    //signalMasts.values().stream().forEach((reporter) ->
 foreach(SignalMastListener* reporter, signalMasts->values())
    {
        disconnect(reporter->signalMast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), reporter, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
    signalMasts->clear();
}

///*private*/ class SignalMastListener implements PropertyChangeListener {

//    protected final SignalMast signalMast;

    /*public*/ SignalMastListener::SignalMastListener(SignalMast* signalMast, JsonSignalMastSocketService* jsmss) {
        this->signalMast = signalMast;
 this->jsmss = jsmss;
    }

    //@Override
    /*public*/ void SignalMastListener::propertyChange(PropertyChangeEvent* e) {
        if (e->getPropertyName()==("Aspect")
                || e->getPropertyName()==("Held")
                || e->getPropertyName()==("Lit")) {
            try {
                try {
                    jsmss->connection->sendMessage(jsmss->service->doGet(JsonSignalMast::SIGNAL_MAST, this->signalMast->getSystemName(), jsmss->locale));
                } catch (JsonException ex) {
                    jsmss->connection->sendMessage(ex.getJsonMessage());
                }
            } catch (IOException* ie) {
                // if we get an error, de-register
                //signalMast.removePropertyChangeListener(this);
          disconnect(signalMast->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                jsmss->signalMasts->remove(this->signalMast->getSystemName());
            }
        }
    }
//}
