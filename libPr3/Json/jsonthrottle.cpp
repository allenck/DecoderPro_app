#include "jsonthrottle.h"
#include "loggerfactory.h"
#include "dcclocoaddress.h"
#include "throttle.h"
#include "jsonthrottlemanager.h"
#include "roster.h"
#include "jsonthrottlesocketservice.h"
#include "json.h"
#include "httpservletresponse.h"
#include "propertychangeevent.h"
#include "dccthrottle.h"
#include "rosterentry.h"

// /*public*/ class JsonThrottle implements ThrottleListener, PropertyChangeListener {

/**
 * Token for type for throttle status messages.
 *
 * {@value #THROTTLE}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::THROTTLE = "throttle"; // NOI18N
/**
 * {@value #ADDRESS}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::ADDRESS = "address"; // NOI18N
/**
 * {@value #FORWARD}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::FORWARD = "forward"; // NOI18N
/**
 * {@value #RELEASE}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::RELEASE = "release"; // NOI18N
/**
 * {@value #ESTOP}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::ESTOP = "eStop"; // NOI18N
/**
 * {@value #IDLE}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::IDLE = "idle"; // NOI18N
/**
 * {@value #SPEED}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::SPEED = "speed"; // NOI18N
/**
 * {@value #SPEED_STEPS}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::SPEED_STEPS = "speedSteps"; // NOI18N
/**
 * Prefix for the throttle function keys (F0-F28).
 * <p>
 * {@value #F}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::F = "F"; // NOI18N
/**
 * Used to notify clients of the number of clients controlling the same
 * throttle->
 * <p>
 * {@value #CLIENTS}
 */
/*public*/ /*static*/ /*final*/ QString JsonThrottle::CLIENTS = "clients"; // NOI18N
/*private*/ /*static*/ /*final*/ Logger* JsonThrottle::log = LoggerFactory::getLogger("JsonThrottle");

/*private*/ JsonThrottle::JsonThrottle(DccLocoAddress* address, JsonThrottleSocketService* /*server*/) {
    this->address = address;
 this->throttle = NULL;
}

/**
 * Creates a new JsonThrottle or returns an existing one if the request is
 * for an existing throttle->
 *
 * data can contain either a string {@link jmri.server.json.JSON#ID} node
 * containing the ID of a {@link jmri.jmrit.roster.RosterEntry} or an
 * integer {@link jmri.server.json.JSON#ADDRESS} node. If data contains an
 * ADDRESS, the ID node is ignored. The ADDRESS may be accompanied by a
 * bool {@link jmri.server.json.JSON#IS_LONG_ADDRESS} node specifying the
 * type of address, if IS_LONG_ADDRESS is not specified, the inverse of {@link jmri.ThrottleManager#canBeShortAddress(int)
 * } is used as the "best guess" of the address length.
 *
 * @param throttleId The client's identity token for this throttle
 * @param data       JSON object containing either an ADDRESS or an ID
 * @param server     The server requesting this throttle on behalf of a
 *                   client
 * @return The throttle
 * @throws jmri.server.json.JsonException if unable to get the requested
 *                                        {@link jmri.Throttle}
 */
/*public*/ /*static*/ JsonThrottle* JsonThrottle::getThrottle(QString /*throttleId*/, QJsonObject data, JsonThrottleSocketService* server) throw (JsonException)
{
 DccLocoAddress* address = NULL;
 QLocale locale = server->getConnection()->getLocale();
 JsonThrottleManager* manager = JsonThrottleManager::getDefault();
 if (!data.value(ADDRESS).isUndefined())
 {
  if (manager->canBeLongAddress(data.value(ADDRESS).toInt())
          || manager->canBeShortAddress(data.value(ADDRESS).toInt()))
  {
      address = new DccLocoAddress(data.value(ADDRESS).toInt(),
              data.value(JSON::IS_LONG_ADDRESS).toBool(!manager->canBeShortAddress(data.value(ADDRESS).toInt())));
  }
  else
  {
      log->warn(tr("Address \"%1\" is not a valid address.").arg( data.value(ADDRESS).toInt()));
      throw JsonException(HttpServletResponse::SC_BAD_REQUEST, tr(/*locale,*/ "The address %1 is invalid.").arg(data.value(ADDRESS).toInt())); // NOI18N
  }
 }
 else if (!data.value(JSON::ID).isUndefined())
 {
  try {
      address = Roster::getDefault()->getEntryForId(data.value(JSON::ID).toString())->getDccLocoAddress();
  } catch (NullPointerException ex) {
      log->warn(tr("Roster entry \"%1\" does not exist.").arg(data.value(JSON::ID).toString()));
      throw JsonException(HttpServletResponse::SC_NOT_FOUND, tr(/*locale,*/ "Unable to create throttle for roster entry %1. Perhaps it does not exist?").arg( data.value(JSON::ID).toString())); // NOI18N
  }
 }
 else {
     log->warn("No address specified");
     throw JsonException(HttpServletResponse::SC_BAD_REQUEST, tr(/*locale,*/ "Throttles must be requested with an address.")); // NOI18N
 }
 if (manager->containsKey(address)) {
     JsonThrottle* throttle = manager->get(address);
     manager->put(throttle, server);
//     throttle->sendMessage(server->getConnection()->getObjectMapper().createObjectNode().insert(CLIENTS, manager->getServers(throttle)->size()));
     QJsonObject obj = QJsonObject();
     obj.insert(CLIENTS, manager->getServers(throttle)->size());
     throttle->sendMessage(obj);
     return throttle;
 } else {
     JsonThrottle* throttle = new JsonThrottle(address, server);
     if (!manager->requestThrottle(address, (ThrottleListener*)throttle)) {
         log->error(tr("Unable to get throttle for \"%1\".").arg(address->toString()));
         throw JsonException(HttpServletResponse::SC_INTERNAL_SERVER_ERROR, /*server->getConnection()->getLocale(),*/ tr("Unable to get throttle for %1.").arg(address->toString()));
     }
     manager->put(address, throttle);
     manager->put(throttle, server);
     manager->attachListener(address, throttle);
     return throttle;
 }
}

/*public*/ void JsonThrottle::close(JsonThrottleSocketService* server, bool notifyClient) {
    if (this->throttle != NULL) {
        if (JsonThrottleManager::getDefault()->getServers(this)->size() == 1) {
            this->throttle->setSpeedSetting(0);
        }
        this->release(server, notifyClient);
    }
}

/*public*/ void JsonThrottle::release(JsonThrottleSocketService* server, bool notifyClient) {
    JsonThrottleManager* manager = JsonThrottleManager::getDefault();
    ObjectMapper mapper = server->getConnection()->getObjectMapper();
    if (this->throttle != NULL) {
        if (manager->getServers(this)->size() == 1) {
            this->throttle->release((ThrottleListener*)this);
//            this->throttle->removePropertyChangeListener(this);
         disconnect(throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
            this->throttle = NULL;
        }
        if (notifyClient) {
//            this->sendMessage(mapper.createObjectNode().insert(RELEASE, "null"), server);
         QJsonObject obj;
         obj.insert(RELEASE, /*"null"*/QJsonValue());
         this->sendMessage(obj, server);
        }
    }
    manager->remove(this, server);
    if (manager->getServers(this)->isEmpty()) {
        // Release address-based reference to this throttle if there are no servers using it
        // so that when the server releases its reference, this throttle can be garbage collected
        manager->remove(this->address);
    } else {
        //this->sendMessage(mapper.createObjectNode().insert(CLIENTS, manager->getServers(this)->size()));
     QJsonObject obj;
     obj.insert(CLIENTS, manager->getServers(this)->size());
     this->sendMessage(obj);
    }
}

/*public*/ void JsonThrottle::onMessage(QLocale /*locale*/, QJsonObject data, JsonThrottleSocketService* server)
{
 if(throttle == NULL)
  return; // not yet found.
    //Iterator<Entry<QString, JsonNode>> nodeIterator = data.fields();
 QMapIterator<QString, QVariant> nodeIterator(data.toVariantMap());
 while (nodeIterator.hasNext())
 {
//        Map.Entry<QString, JsonNode> entry = nodeIterator.next();
  nodeIterator.next();
//        QString k = entry.getKey();
  QString k = nodeIterator.key();
 //        JsonNode v = entry.getValue();
  QVariant v = nodeIterator.value();
 //        switch (k) {
  if(k ==  ESTOP )
  {
      this->throttle->setSpeedSetting(-1);
      return; // stop processing any commands that may conflict with ESTOP
  }
  else if(k ==  IDLE )
  {
      this->throttle->setSpeedSetting(0);
  }
  else if(k ==  SPEED)
  {
      this->throttle->setSpeedSetting((float) v.toDouble());
  } else
  if(k ==  FORWARD) {
      this->throttle->setIsForward(v.toBool());
      } else
  if(k ==   Throttle::F0 ) {
      this->throttle->setF0(v.toBool());
      } else
  if(k ==   Throttle::F1) {
      this->throttle->setF1(v.toBool());
      } else
  if(k ==   Throttle::F2 ) {
      this->throttle->setF2(v.toBool());
      } else
  if(k ==   Throttle::F3 ) {
      this->throttle->setF3(v.toBool());
      } else
  if(k ==   Throttle::F4 ) {
      this->throttle->setF4(v.toBool());
      } else
  if(k ==   Throttle::F5 ) {
      this->throttle->setF5(v.toBool());
      } else
  if(k ==   Throttle::F6 ) {
      this->throttle->setF6(v.toBool());
      } else
  if(k ==   Throttle::F7 ) {
      this->throttle->setF7(v.toBool());
      } else
  if(k ==   Throttle::F8 ) {
      this->throttle->setF8(v.toBool());
      } else
  if(k ==   Throttle::F9 ) {
      this->throttle->setF9(v.toBool());
      } else
  if(k ==   Throttle::F10 ) {
      this->throttle->setF10(v.toBool());
      } else
  if(k ==   Throttle::F11 ) {
      this->throttle->setF11(v.toBool());
      } else
  if(k ==   Throttle::F12 ) {
      this->throttle->setF12(v.toBool());
      } else
  if(k ==   Throttle::F13 ) {
      this->throttle->setF13(v.toBool());
      } else
  if(k ==   Throttle::F14 ) {
      this->throttle->setF14(v.toBool());
      } else
  if(k ==   Throttle::F15 ) {
      this->throttle->setF15(v.toBool());
      } else
  if(k ==   Throttle::F16 ) {
      this->throttle->setF16(v.toBool());
      } else
  if(k ==   Throttle::F17 ) {
      this->throttle->setF17(v.toBool());
      } else
  if(k ==   Throttle::F18 ) {
      this->throttle->setF18(v.toBool());
      } else
  if(k ==   Throttle::F19 ) {
      this->throttle->setF19(v.toBool());
      } else
  if(k ==   Throttle::F20 ) {
      this->throttle->setF20(v.toBool());
      } else
  if(k ==   Throttle::F21 ) {
      this->throttle->setF21(v.toBool());
      } else
  if(k ==   Throttle::F22 ) {
      this->throttle->setF22(v.toBool());
      } else
  if(k ==   Throttle::F23 ) {
      this->throttle->setF23(v.toBool());
      } else
  if(k ==   Throttle::F24 ) {
      this->throttle->setF24(v.toBool());
      } else
  if(k ==   Throttle::F25 ) {
      this->throttle->setF25(v.toBool());
      } else
  if(k ==   Throttle::F26 ) {
      this->throttle->setF26(v.toBool());
      } else
  if(k ==   Throttle::F27 ) {
      this->throttle->setF27(v.toBool());
      } else
  if(k ==   Throttle::F28 ) {
      this->throttle->setF28(v.toBool());
      } else
  if(k ==  RELEASE ) {
      server->release(this);
      } else
  if(k ==  JSON::STATUS ) {
      this->sendStatus(server);
  }
  else if(k ==  THROTTLE )
  {
  //default:
      // no action for throttle item; it always exists
      // silently ignore unknown or unexpected items, since a
      // following item may be an ESTOP and we always want to
      // catch those
     }
//        }
 }
}

/*public*/ void JsonThrottle::sendMessage(QJsonObject data) {
    //JsonThrottleManager::getDefault()->getServers(this).stream().forEach((server) ->
 foreach(JsonThrottleSocketService* server, *JsonThrottleManager::getDefault()->getServers(this))
    {
        this->sendMessage(data, server);
    } //);
}

/*public*/ void JsonThrottle::sendMessage(QJsonObject data, JsonThrottleSocketService* server) {
    try {
        server->sendMessage(this, data);
    } catch (IOException ex) {
        this->close(server, false);
        log->warn(tr("Unable to send message, closing connection: %1").arg(ex.getMessage()));
        try {
            server->getConnection()->close();
        } catch (IOException e1) {
            log->warn("Unable to close connection." + e1.getMessage());
        }
    }
}

//@Override
/*public*/ void JsonThrottle::propertyChange(PropertyChangeEvent* evt)
{
    QJsonObject data = JsonThrottleManager::getDefault()->getObjectMapper().createObjectNode();
    QString property = evt->getPropertyName();
    if (property == ("SpeedSetting"))
    { // NOI18N
        data.insert(SPEED, ( evt->getNewValue()).toFloat());
    }
    else if (property == ("IsForward"))
    { // NOI18N
        data.insert(FORWARD, (evt->getNewValue().toBool()));
    }
    else if (property.startsWith(F) && !property.contains("Momentary"))
    { // NOI18N
        data.insert(property, ( evt->getNewValue().toBool()));
    }
    this->sendMessage(data);
}

//@Override
/*public*/ void JsonThrottle::notifyThrottleFound(DccThrottle* throttle) {
    log->debug(tr("Found throttle %1").arg(throttle->getLocoAddress()->toString()));
    try {
        this->throttle = throttle;
//        throttle->addPropertyChangeListener(this);
     connect(throttle, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        switch (throttle->getSpeedStepMode()) {
            case DccThrottle::SpeedStepMode14:
                this->speedSteps = 14;
                break;
            case DccThrottle::SpeedStepMode27:
                this->speedSteps = 27;
                break;
            case DccThrottle::SpeedStepMode28:
            case DccThrottle::SpeedStepMode28Mot:
                this->speedSteps = 28;
                break;
            case DccThrottle::SpeedStepMode128:
            default:
                this->speedSteps = 126;
                break;
        }
        this->sendStatus();
    } catch (Exception e) {
        log->debug(e.getLocalizedMessage() +  e.getMessage());
    }
}

//@Override
/*public*/ void JsonThrottle::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason) {
    JsonThrottleManager* manager = JsonThrottleManager::getDefault();
    foreach (JsonThrottleSocketService* server, *manager->getServers(this)/*.toArray(new JsonThrottleSocketService[manager->getServers(this).size()])*/) {
        this->sendErrorMessage(JsonException(512, /*server->getConnection()->getLocale(),*/tr( "Unable to get throttle for %1 because: %2.").arg(address->toString()).arg(reason)), server);
        server->release(this);
    }
}

/*private*/ void JsonThrottle::sendErrorMessage(JsonException message, JsonThrottleSocketService* server) {
    try {
        server->getConnection()->sendMessage(message.getJsonMessage());
    } catch (IOException e) {
        log->warn("Unable to send message, closing connection. " + e.getMessage());
        try {
            server->getConnection()->close();
        } catch (IOException e1) {
            log->warn("Unable to close connection."+ e1.getMessage());
        }
    }
}

/*private*/ void JsonThrottle::sendStatus() {
    if (this->throttle != NULL) {
        this->sendMessage(this->getStatus());
    }
}

/*protected*/ void JsonThrottle::sendStatus(JsonThrottleSocketService* server) {
    if (this->throttle != NULL) {
        this->sendMessage(this->getStatus(), server);
    }
}

/*private*/ QJsonObject JsonThrottle::getStatus() {
    QJsonObject data = JsonThrottleManager::getDefault()->getObjectMapper().createObjectNode();
    data.insert(ADDRESS, this->throttle->getLocoAddress()->getNumber());
    data.insert(SPEED, this->throttle->getSpeedSetting());
    data.insert(FORWARD, this->throttle->getIsForward());
    data.insert( Throttle::F0, this->throttle->getF0());
    data.insert( Throttle::F1, this->throttle->getF1());
    data.insert( Throttle::F2, this->throttle->getF2());
    data.insert( Throttle::F3, this->throttle->getF3());
    data.insert( Throttle::F4, this->throttle->getF4());
    data.insert( Throttle::F5, this->throttle->getF5());
    data.insert( Throttle::F6, this->throttle->getF6());
    data.insert( Throttle::F7, this->throttle->getF7());
    data.insert( Throttle::F8, this->throttle->getF8());
    data.insert( Throttle::F9, this->throttle->getF9());
    data.insert( Throttle::F10, this->throttle->getF10());
    data.insert( Throttle::F11, this->throttle->getF11());
    data.insert( Throttle::F12, this->throttle->getF12());
    data.insert( Throttle::F13, this->throttle->getF13());
    data.insert( Throttle::F14, this->throttle->getF14());
    data.insert( Throttle::F15, this->throttle->getF15());
    data.insert( Throttle::F16, this->throttle->getF16());
    data.insert( Throttle::F17, this->throttle->getF17());
    data.insert( Throttle::F18, this->throttle->getF18());
    data.insert( Throttle::F19, this->throttle->getF19());
    data.insert( Throttle::F20, this->throttle->getF20());
    data.insert( Throttle::F21, this->throttle->getF21());
    data.insert( Throttle::F22, this->throttle->getF22());
    data.insert( Throttle::F23, this->throttle->getF23());
    data.insert( Throttle::F24, this->throttle->getF24());
    data.insert( Throttle::F25, this->throttle->getF25());
    data.insert( Throttle::F26, this->throttle->getF26());
    data.insert( Throttle::F27, this->throttle->getF27());
    data.insert( Throttle::F28, this->throttle->getF28());
    data.insert(SPEED_STEPS, this->speedSteps);
    data.insert(CLIENTS, JsonThrottleManager::getDefault()->getServers(this)->size());
    if (this->throttle->getRosterEntry() != NULL) {
        data.insert(JSON::ROSTER_ENTRY, this->throttle->getRosterEntry()->getId());
    }
    return data;
}
