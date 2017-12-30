#ifndef MULTITHROTTLECONTROLLER_H
#define MULTITHROTTLECONTROLLER_H
#include "throttlecontroller.h"


class MultiThrottleController : public ThrottleController
{
public:
 MultiThrottleController(QChar id, QString key, ThrottleControllerListener* tcl, ControllerInterface* ci, QObject* parent = 0);
 /*public*/ QString buildPacketWithChar(QChar chr);
 /*public*/ void sendFunctionLabels(RosterEntry* re);
 /*public*/ void sendAllFunctionStates(DccThrottle* t);
 /*public*/ void sendAddress();

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("MultiThrottleController");
 QString locoKey;
protected:
 /*protected*/ void sendCurrentSpeed(DccThrottle* t);
 /*protected*/ void sendCurrentDirection(DccThrottle* t);
 /*protected*/ void sendSpeedStepMode(DccThrottle* t);
 /*protected*/ void sendAllMomentaryStates(DccThrottle* t);

};

#endif // MULTITHROTTLECONTROLLER_H
