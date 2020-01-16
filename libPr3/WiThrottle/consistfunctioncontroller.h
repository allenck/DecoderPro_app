#ifndef CONSISTFUNCTIONCONTROLLER_H
#define CONSISTFUNCTIONCONTROLLER_H
#include "throttlelistener.h"

class Logger;
class RosterEntry;
class ThrottleController;
class ConsistFunctionController : public QObject, public ThrottleListener
{
 Q_OBJECT
 Q_INTERFACES(ThrottleListener)
public:
 /*public*/ ConsistFunctionController(ThrottleController* tc) ;
 /*public*/ ConsistFunctionController(ThrottleController* tc, RosterEntry* re);
 /*public*/ void dispose();
 /*public*/ DccThrottle* getThrottle();
 /*public*/QObject* self() {return (QObject*)this;}

public slots:
 /*public*/ void notifyThrottleFound(DccThrottle* t);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);

private:
 void common();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ConsistFunctionController.class.getName());
 /*private*/ DccThrottle* throttle;
 /*private*/ RosterEntry* rosterLoco;// = null;
 /*private*/ ThrottleController* throttleController;
 bool requestThrottle(DccLocoAddress* loco);

 friend class ThrottleController;
};

#endif // CONSISTFUNCTIONCONTROLLER_H
