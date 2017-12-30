#include "jsonrostersocketservice.h"
#include "roster.h"
#include "rosterentry.h"
#include "loggerfactory.h"
#include "json.h"
#include "jsonroster.h"
#include "jsonrosterhttpservice.h"
#include "jsonexception.h"
#include "httpservletresponse.h"
#include "propertychangeprovider.h"

/**
 * Listen for changes in the roster and notify subscribed clients of the change.
 *
 * @author Randall Wood Copyright (C) 2014, 2016
 */
///*public*/ class JsonRosterSocketService extends JsonSocketService {

/*private*/ /*final*/ /*static*/ Logger* JsonRosterSocketService::log = LoggerFactory::getLogger("JsonRosterSocketService");

/*public*/ JsonRosterSocketService::JsonRosterSocketService(JsonConnection* connection, QObject* parent): JsonSocketService(connection, parent)
{
    //super(connection);
    rosterListener = new JsonRosterListener(this);
    rosterEntryListener = new JsonRosterEntryListener(this);
    this->service = new JsonRosterHttpService(connection->getObjectMapper());
}

/*public*/ void JsonRosterSocketService::listen()
{
 if (!this->listening)
 {
  //Roster::getDefault().addPropertyChangeListener(this->rosterListener);
  disconnect(Roster::getDefault(), SIGNAL(propertyChange(PropertyChangeEvent*)), this->rosterListener, SLOT(propertyChange(PropertyChangeEvent*)));
 // Roster::getDefault().getEntriesInGroup(Roster::ALLENTRIES).stream().forEach((re) ->
  foreach(RosterEntry* re, Roster::getDefault()->getEntriesInGroup(Roster::ALLENTRIES))
  {
   // re.addPropertyChangeListener(this->rosterEntryListener);
   disconnect(re->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this->rosterEntryListener, SLOT(propertyChange(PropertyChangeEvent*)));
  }//);
  this->listening = true;
 }
}

//@Override
/*public*/ void JsonRosterSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException)
{
 QString method = data.value(JSON::METHOD).toString();
 if (method== JSON::DELETE)
   throw  JsonException(HttpServletResponse::SC_METHOD_NOT_ALLOWED, tr("Deleting %1 is not allowed.").arg(type));
 else if (method== JSON::POST || method == JSON::PUT)
         throw JsonException(HttpServletResponse::SC_NOT_IMPLEMENTED, tr("Method %1 not implemented for type %2.").arg(method).arg(type));
 else if (method== JSON::GET)
 {
  if(type == JsonRoster::ROSTER)
  {
   this->connection->sendMessage(this->service->getRoster(locale, data));
  }
  else if(type == JsonRoster::ROSTER_ENTRY)
  {
   this->connection->sendMessage(this->service->getRosterEntry(locale, data.value(JSON::NAME).toString()));
  }
  else if(type == JsonRoster::ROSTER_GROUP)
  {
   this->connection->sendMessage(this->service->getRosterGroup(locale, data.value(JSON::NAME).toString()));
  }
  else if(type ==  JsonRoster::ROSTER_GROUPS)
  {
   this->connection->sendMessage(this->service->getRosterGroups(locale));}
  else
  {
   throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, tr("Unknown object type {0} was requested.").arg(type));
  }
 }
 this->listen();
}

//@Override
/*public*/ void JsonRosterSocketService::onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->connection->sendMessage(service->doGetList(type, locale));
    this->listen();
}

//@Override
/*public*/ void JsonRosterSocketService::onClose() {
    //Roster::getDefault().removePropertyChangeListener(this->rosterListener);
    disconnect(Roster::getDefault()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this->rosterListener, SLOT(propertyChange(PropertyChangeEvent*)));
    //Roster::getDefault().getEntriesInGroup(Roster::ALLENTRIES).stream().forEach((re) ->
    foreach(RosterEntry* re, Roster::getDefault()->getEntriesInGroup(Roster::ALLENTRIES))
    {
        //re.removePropertyChangeListener(this->rosterEntryListener);
        disconnect(re->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), rosterEntryListener, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
    this->listening = false;
}

///*private*/ class JsonRosterEntryListener implements PropertyChangeListener {
JsonRosterEntryListener::JsonRosterEntryListener( JsonRosterSocketService* jrss)
{
 this->jrss = jrss;
}
//@Override
/*public*/ void JsonRosterEntryListener::propertyChange(PropertyChangeEvent* evt) {
    try {
        if (evt->getPropertyName() == (RosterEntry::ID)) {
            // send old roster entry and new roster entry to client as roster changes
            QJsonObject root = QJsonObject();/*connection.getObjectMapper().createObjectNode()*/
            root.insert(JSON::TYPE, JsonRoster::ROSTER);
            QJsonObject data = QJsonObject();// root.putObject(DATA);
            RosterEntry* old = new RosterEntry((RosterEntry*) evt->getSource(), (evt->getOldValue().toString()));
            data.insert(JSON::ADD, jrss->service->getRosterEntry(jrss->connection->getLocale(), (RosterEntry*) evt->getSource()));
            data.insert(JSON::REMOVE, jrss->service->getRosterEntry(jrss->connection->getLocale(), old));
            root.insert(JSON::DATA, data);
            jrss->connection->sendMessage(root);
        } else if (evt->getPropertyName()!=(RosterEntry::DATE_UPDATED)
                && evt->getPropertyName()!=(RosterEntry::FILENAME)) {
            jrss->log->debug(tr("Triggering change on %1 (%2 => %3)").arg(evt->getPropertyName()).arg( evt->getOldValue().toString()).arg(evt->getNewValue().toString()));
            jrss->connection->sendMessage(jrss->service->getRosterEntry(jrss->connection->getLocale(), (RosterEntry*) evt->getSource()));
        }
    } catch (IOException ex) {
        jrss->onClose();
    }
}
//}

///*private*/ class JsonRosterListener implements PropertyChangeListener {
///
JsonRosterListener::JsonRosterListener(JsonRosterSocketService* jrss)
{
 this->jrss = jrss;
}



    //@Override
/*public*/ void JsonRosterListener::propertyChange(PropertyChangeEvent* evt) {
    QJsonObject root = QJsonObject(); //connection.getObjectMapper().createObjectNode().
    root.insert(JSON::TYPE, JsonRoster::ROSTER);
    try {
        if (evt->getPropertyName() == (Roster::ROSTER_GROUP_ADDED)
                || evt->getPropertyName() == (Roster::ROSTER_GROUP_REMOVED)
                || evt->getPropertyName() == (Roster::ROSTER_GROUP_RENAMED)) {
            try {
                jrss->connection->sendMessage(jrss->service->getRosterGroups(jrss->connection->getLocale()));
            } catch (JsonException ex) {
                jrss->connection->sendMessage(ex.getJsonMessage());
            }
        } else if (evt->getPropertyName()==(Roster::ADD)) {
            //root.putObject(DATA).put(ADD, service.getRosterEntry(connection.getLocale(), (RosterEntry) evt.getNewValue()));
         QJsonObject data = QJsonObject();
         data.insert(JSON::ADD, jrss->service->getRosterEntry(jrss->connection->getLocale(),VPtr<RosterEntry>::asPtr(evt->getNewValue())));
         root.insert(JSON::DATA, data);
//            ((PropertyChangeProvider*) evt->getNewValue()).addPropertyChangeListener(rosterEntryListener);
         connect(VPtr<RosterEntry>::asPtr(evt->getNewValue()), SIGNAL(propertyChange(PropertyChangeEvent*)), jrss->rosterEntryListener, SLOT(propertyChange(PropertyChangeEvent*)));
            jrss->connection->sendMessage(root);
        } else if (evt->getPropertyName() == (Roster::REMOVE)) {
            //root.putObject(DATA).put(REMOVE, service.getRosterEntry(connection.getLocale(), (RosterEntry) evt.getOldValue()));
         QJsonObject data = QJsonObject();
         data.insert(JSON::REMOVE, jrss->service->getRosterEntry(jrss->connection->getLocale(), VPtr<RosterEntry>::asPtr(evt->getOldValue())));
         root.insert(JSON::DATA,data);
            jrss->connection->sendMessage(root);
        } else if (evt->getPropertyName() != (Roster::SAVED)
                || evt->getPropertyName() == (Roster::CHANGE)) {
            // catch all events other than SAVED
            jrss->connection->sendMessage(jrss->service->getRoster(jrss->connection->getLocale(), root));
        }
    } catch (IOException ex) {
        jrss->onClose();
    }
}
//}
