#include "jsontimesocketservice.h"
#include "jsontimehttpservice.h"
#include "timebase.h"
#include "instancemanager.h"
#include "json.h"

/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonTimeSocketService extends JsonSocketService implements PropertyChangeListener {


/*public*/ JsonTimeSocketService::JsonTimeSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent){
    //super(connection);
    listening = false;
    this->service = new JsonTimeHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonTimeSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    if (!this->listening) {
        Timebase* manager = (Timebase*)InstanceManager::getDefault("Timebase");
        manager->addMinuteChangeListener((PropertyChangeListener*)this);
        //manager.addPropertyChangeListener(this);
        connect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        this->listening = true;
    }
    this->service->doPost(type, NULL, data, locale);
}

//@Override
/*public*/ void JsonTimeSocketService::onList(QString type, QJsonObject /*data*/, QLocale /*locale*/) throw (JsonException) {
    throw JsonException(HttpServletResponse::SC_BAD_REQUEST, tr(/*locale,*/ "{0} cannot be listed.").arg(type));
}

//@Override
/*public*/ void JsonTimeSocketService::onClose() {
    if (this->listening) {
     Timebase* manager = (Timebase*)InstanceManager::getDefault("Timebase");
        manager->removeMinuteChangeListener((PropertyChangeListener*)this);
        //manager.removePropertyChangeListener(this);
        disconnect(manager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }
}

//@Override
/*public*/ void JsonTimeSocketService::propertyChange(PropertyChangeEvent* evt) {
    try {
        try {
            this->connection->sendMessage(this->service->doGet(JSON::TIME, NULL, this->connection->getLocale()));
        } catch (JsonException ex) {
            this->connection->sendMessage(ex.getJsonMessage());
        }
    } catch (IOException ex) {
        // do nothing - the client has dropped off and a ping failure will
        // clean up the connection if its not already being torn down
    }
}

