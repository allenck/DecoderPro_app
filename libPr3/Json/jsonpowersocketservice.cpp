#include "jsonpowersocketservice.h"
#include "instancemanager.h"
#include "powermanager.h"
#include "jsonpowerhttpservice.h"
#include "json.h"
#include "abstractpowermanager.h"
/**
 *
 * @author Randall Wood
 */
// /*public*/ class JsonPowerSocketService extends JsonSocketService implements PropertyChangeListener {


/*public*/ JsonPowerSocketService::JsonPowerSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
 //super(connection);
 listening = false;
 this->service = new JsonPowerHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonPowerSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException )
{
 if (!this->listening)
 {
//        ((PowerManager*)InstanceManager::getDefault("PowerManager"))->addPropertyChangeListener(this);
  AbstractPowerManager* pm = (AbstractPowerManager*)InstanceManager::getOptionalDefault("PowerManager");
  connect(pm->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  this->listening = true;
 }
 this->connection->sendMessage(this->service->doPost(type, NULL, data, locale));
}

//@Override
/*public*/ void JsonPowerSocketService::onList(QString type, QJsonObject /*data*/, QLocale /*locale*/) throw (JsonException) {
    throw JsonException(HttpServletResponse::SC_BAD_REQUEST, tr("%1 cannot be listed.").arg(type));
}

//@Override
/*public*/ void JsonPowerSocketService::propertyChange(PropertyChangeEvent* /*evt*/)
{
 try {
     try {
         this->connection->sendMessage(this->service->doGet(JSON::POWER, NULL, this->connection->getLocale()));
     } catch (JsonException ex) {
         this->connection->sendMessage(ex.getJsonMessage());
     }
 } catch (IOException ex) {
     // do nothing - we can only silently fail at this point
 }
}

//@Override
/*public*/ void JsonPowerSocketService::onClose() {
//    ((PowerManager*)InstanceManager::getOptionalDefault("PowerManager")->ifPresent((PowerManager pm) ->
 if(InstanceManager::getOptionalDefault("PowerManager") != NULL)
 {
       //pm.removePropertyChangeListener(JsonPowerSocketService.this);
  PowerManager* pm = (PowerManager*)InstanceManager::getOptionalDefault("PowerManager");
  disconnect(pm, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
}
