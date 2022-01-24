#include "jsonturnoutsocketservice.h"
#include "turnout.h"
#include "json.h"
#include "proxyturnoutmanager.h"
#include "instancemanager.h"
#include "jsonturnouthttpservice.h"
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonTurnoutSocketService extends JsonSocketService {


/*public*/ JsonTurnoutSocketService::JsonTurnoutSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
 //super(connection);
 turnouts = new QMap<QString, TurnoutListener*>();
 this->service = new JsonTurnoutHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonTurnoutSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    QString name = data.value(JSON::NAME).toString();
    if (data.value(JSON::METHOD).toString()==(JSON::PUT)) {
        this->connection->sendMessage(this->service->doPut(type, name, data, locale));
    } else {
        this->connection->sendMessage(this->service->doPost(type, name, data, locale));
    }
    if (!this->turnouts->contains(name)) {
        Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->getTurnout(name);
        TurnoutListener* listener = new TurnoutListener(turnout, this);
        //turnout->SwingPropertyChangeSupport::addPropertyChangeListener(listener);
        connect(turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)) );
        this->turnouts->insert(name, listener);
    }
}

//@Override
/*public*/ void JsonTurnoutSocketService::onList(QString type, QJsonObject /*data*/, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonTurnoutSocketService::onClose() {
    //turnouts.values().stream().forEach((turnout) -> {
 foreach(TurnoutListener* listener, turnouts->values())
 {
        //turnout->turnout->removePropertyChangeListener(turnout);
  disconnect(listener->turnout()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)) );

    }//);
    turnouts->clear();
}

///*private*/ class TurnoutListener implements PropertyChangeListener {

//    protected /*final*/ Turnout turnout;

/*public*/ TurnoutListener::TurnoutListener(Turnout* turnout, JsonTurnoutSocketService* jtss) {
    this->_turnout = turnout;
this->jtss = jtss;
}

//@Override
/*public*/ void TurnoutListener::propertyChange(PropertyChangeEvent* e)
{
 // If the Commanded State changes, show transition state as "<inconsistent>"
 if (e->getPropertyName() == ("KnownState")) {
 try
  {
   try
   {
    jtss->connection->sendMessage(jtss->service->doGet(JSON::TURNOUT, this->_turnout->getSystemName(), jtss->locale));
   }
   catch (JsonException ex)
   {
    jtss->connection->sendMessage(ex.getJsonMessage());
   }
  }
  catch (IOException* ex)
  {
   // if we get an error, de-register
   //turnout->removePropertyChangeListener(this);
disconnect(_turnout->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
   jtss->turnouts->remove(this->_turnout->getSystemName());
  }
 }
}

