#ifndef JSONTHROTTLE_H
#define JSONTHROTTLE_H

#include <QObject>
#include "jsonqt.h"
#include "jsonexception.h"
#include "throttlelistener.h"

class DccThrottle;
class PropertyChangeEvent;
class ObjectNode;
class JsonNode;
class JsonThrottleSocketService;
class Logger;
class Throttle;
class DccLocoAddress;
class JsonThrottle : public QObject, public ThrottleListener
{
 Q_OBJECT
 Q_INTERFACES(ThrottleListener)
public:
 explicit JsonThrottle(QObject *parent = 0);
 /**
  * Token for type for throttle status messages.
  *
  * {@value #THROTTLE}
  */
 /*public*/ static /*final*/ QString THROTTLE;// = "throttle"; // NOI18N
 /**
  * {@value #ADDRESS}
  */
 /*public*/ static /*final*/ QString ADDRESS;// = "address"; // NOI18N
 /**
  * {@value #FORWARD}
  */
 /*public*/ static /*final*/ QString FORWARD;// = "forward"; // NOI18N
 /**
  * {@value #RELEASE}
  */
 /*public*/ static /*final*/ QString RELEASE;// = "release"; // NOI18N
 /**
  * {@value #ESTOP}
  */
 /*public*/ static /*final*/ QString ESTOP;// = "eStop"; // NOI18N
 /**
  * {@value #IDLE}
  */
 /*public*/ static /*final*/ QString IDLE;// = "idle"; // NOI18N
 /**
  * {@value #SPEED}
  */
 /*public*/ static /*final*/ QString SPEED;// = "speed"; // NOI18N
 /**
  * {@value #SPEED_STEPS}
  */
 /*public*/ static /*final*/ QString SPEED_STEPS;// = "speedSteps"; // NOI18N
 /**
  * Prefix for the throttle function keys (F0-F28).
  * <p>
  * {@value #F}
  */
 /*public*/ static /*final*/ QString F;// = "F"; // NOI18N
 /**
  * Used to notify clients of the number of clients controlling the same
  * throttle.
  * <p>
  * {@value #CLIENTS}
  */
 /*public*/ static /*final*/ QString CLIENTS;// = "clients"; // NOI18N
 /*public*/ static JsonThrottle* getThrottle(QString throttleId, QJsonObject data, JsonThrottleSocketService* server) throw (JsonException);
 /*public*/ void close(JsonThrottleSocketService* server, bool notifyClient);
 /*public*/ void release(JsonThrottleSocketService* server, bool notifyClient);
 /*public*/ void onMessage(QLocale locale, QJsonObject data, JsonThrottleSocketService* server);
 /*public*/ void sendMessage(QJsonObject data);
 /*public*/ void sendMessage(QJsonObject data, JsonThrottleSocketService* server);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
 /*private*/ QJsonObject getStatus();

signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* evt);
 /*public*/ void notifyThrottleFound(DccThrottle* throttle);


private:
 /*private*/ Throttle* throttle;
 /*private*/ int speedSteps = 1;
 /*private*/ DccLocoAddress* address = NULL;
 /*private*/ static /*final*/ Logger* log;//= LoggerFactory.getLogger(JsonThrottle.class);
 /*private*/ JsonThrottle(DccLocoAddress* address, JsonThrottleSocketService* server);
 /*private*/ void sendErrorMessage(JsonException message, JsonThrottleSocketService* server);
 /*private*/ void sendStatus();


protected:
 /*protected*/ void sendStatus(JsonThrottleSocketService* server);
 friend class JsonThrottleSocketService;
};

#endif // JSONTHROTTLE_H
