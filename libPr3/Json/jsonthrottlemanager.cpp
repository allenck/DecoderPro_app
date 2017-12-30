#include "jsonthrottlemanager.h"
#include "instancemanager.h"
#include "jsonthrottle.h"

/**
 * Manager for {@link jmri.server.json.throttle.JsonThrottle} objects. A manager
 * is needed since multiple JsonThrottle objects may be controlling the same
 * {@link jmri.DccLocoAddress}.
 *
 * @author Randall Wood (C) 2016
 */
// /*public*/ class JsonThrottleManager {


/*public*/ JsonThrottleManager::JsonThrottleManager(QObject *parent) : QObject(parent) {
    // do nothing
 throttles = new QHash<DccLocoAddress*, JsonThrottle*>();
 services = new QHash<JsonThrottle*, QList<JsonThrottleSocketService*>*>();
 mapper = ObjectMapper();

}

/*public*/ /*static*/ JsonThrottleManager* JsonThrottleManager::getDefault() {
    if (InstanceManager::getNullableDefault("JsonThrottleManager") == NULL) {
        InstanceManager::setDefault("JsonThrottleManager", new JsonThrottleManager());
    }
    return (JsonThrottleManager*)InstanceManager::getDefault("JsonThrottleManager");
}

/*public*/ QList<JsonThrottle*> JsonThrottleManager::getThrottles() {
    return this->throttles->values();
}

/*public*/ void JsonThrottleManager::put(DccLocoAddress* address, JsonThrottle* throttle) {
    this->throttles->insert(address, throttle);
}

/*public*/ void JsonThrottleManager::put(JsonThrottle* throttle, JsonThrottleSocketService* service)
{
 if (this->services->value(throttle) == NULL)
 {
  this->services->insert(throttle, new  QList<JsonThrottleSocketService*>());
 }
 this->services->value(throttle)->append(service);
}

/*public*/ bool JsonThrottleManager::containsKey(DccLocoAddress* address) {
    return this->throttles->contains(address);
}

/*public*/ JsonThrottle* JsonThrottleManager::get(DccLocoAddress* address) {
    return this->throttles->value(address);
}

/*public*/ void JsonThrottleManager::remove(DccLocoAddress* address) {
    this->throttles->remove(address);
}

/*public*/ QList<JsonThrottleSocketService*>* JsonThrottleManager::getServers(JsonThrottle* throttle) {
    if (this->services->value(throttle) == NULL) {
        this->services->value(throttle, new QList<JsonThrottleSocketService*>());
    }
    return this->services->value(throttle);
}

/*public*/ void JsonThrottleManager::remove(JsonThrottle* throttle, JsonThrottleSocketService* server) {
    this->getServers(throttle)->removeOne(server);
}

/*public*/ ObjectMapper JsonThrottleManager::getObjectMapper() {
    return this->mapper;
}

/*public*/ bool JsonThrottleManager::canBeLongAddress(int asInt) {
    return ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->canBeLongAddress(asInt);
}

/*public*/ bool JsonThrottleManager::canBeShortAddress(int asInt) {
    return ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->canBeShortAddress(asInt);
}

/*public*/ bool JsonThrottleManager::requestThrottle(DccLocoAddress* address, ThrottleListener* listener) {
    return ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->requestThrottle(address, listener);
}

/*public*/ void JsonThrottleManager::attachListener(DccLocoAddress* address, JsonThrottle*throttle) {
    ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->attachListener(address, (PropertyChangeListener*)throttle);
}
