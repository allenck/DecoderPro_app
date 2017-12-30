#ifndef JSONTHROTTLEMANAGER_H
#define JSONTHROTTLEMANAGER_H

#include <QObject>
#include "jsonqt.h"

class ThrottleListener;
class ObjectMapper;
class JsonThrottleSocketService;
class DccLocoAddress;
class JsonThrottle;
class JsonThrottleManager : public QObject
{
 Q_OBJECT
public:
 explicit JsonThrottleManager(QObject *parent = 0);
 /*public*/ static JsonThrottleManager* getDefault();
 /*public*/ QList<JsonThrottle*> getThrottles(); // Collection
 /*public*/ void put(DccLocoAddress* address, JsonThrottle* throttle);
 /*public*/ void put(JsonThrottle* throttle, JsonThrottleSocketService* service);
 /*public*/ bool containsKey(DccLocoAddress* address);
 /*public*/ JsonThrottle* get(DccLocoAddress* address);
 /*public*/ void remove(DccLocoAddress* address);
 /*public*/ QList<JsonThrottleSocketService*>* getServers(JsonThrottle* throttle);
 /*public*/ void remove(JsonThrottle* throttle, JsonThrottleSocketService* server);
 /*public*/ ObjectMapper getObjectMapper();
 /*public*/ bool canBeLongAddress(int asInt);
 /*public*/ bool canBeShortAddress(int asInt);
 /*public*/ bool requestThrottle(DccLocoAddress* address, ThrottleListener* listener);
 /*public*/ void attachListener(DccLocoAddress* address, JsonThrottle* throttle);

signals:

public slots:

private:
 /*private*/ /*final*/ QHash<DccLocoAddress*, JsonThrottle*>* throttles;// = new HashMap<>();
 /*private*/ /*final*/ QHash<JsonThrottle*, QList<JsonThrottleSocketService*>*>* services;// = new HashMap<>();
 /*private*/ /*final*/ ObjectMapper mapper;// = new ObjectMapper();

};

#endif // JSONTHROTTLEMANAGER_H
