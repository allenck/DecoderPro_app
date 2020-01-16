#ifndef THROTTLECONTROLLER_H
#define THROTTLECONTROLLER_H

#include <QObject>
#include "speedstepmode.h"
#include "throttlelistener.h"

class PropertyChangeEvent;
class ConsistFunctionController;
class ThrottleControllerListener;
class ControllerInterface;
class RosterEntry;
class DccThrottle;
class DccLocoAddress;
class Logger;
class ThrottleController : public QObject, public ThrottleListener
{
 Q_OBJECT
 Q_INTERFACES(ThrottleListener)
public:
 explicit ThrottleController(QObject *parent = 0);
 /*public*/ ThrottleController(QChar whichThrottleChar, ThrottleControllerListener* tcl, ControllerInterface* cl, QObject *parent = 0);
 /*public*/ void setWhichThrottle(QChar c);
 /*public*/ void addThrottleControllerListener(ThrottleControllerListener* l);
 /*public*/ void removeThrottleControllerListener(ThrottleControllerListener* l);
 /*public*/ void addControllerListener(ControllerInterface* listener);
 /*public*/ void removeControllerListener(ControllerInterface* listener);
 /*public*/ void setRosterLocoForConsistFunctions(QString id);
 /*public*/ void shutdownThrottle();
 /*public*/ RosterEntry* findRosterEntry(DccThrottle* t);
 /*public*/ void syncThrottleFunctions(DccThrottle* t, RosterEntry* re);
 /*public*/ void sendFunctionLabels(RosterEntry* re);
 /*public*/ void sendAllFunctionStates(DccThrottle* t);
 /*public*/ bool sort(QString inPackage);
 /*public*/ void setFunctionThrottle(DccThrottle* t);
 /*public*/ void setLocoForConsistFunctions(QString inPackage);
 /*public*/ void requestEntryFromID(QString id);
 /*public*/ DccThrottle* getThrottle();
 /*public*/ DccThrottle* getFunctionThrottle() ;
 /*public*/ DccLocoAddress* getCurrentAddress();
 /*public*/ QString getCurrentAddressString();
 /*public*/ void sendAddress();
 /*public*/QObject* self() {return (QObject*)this;}


signals:

public slots:
 /*public*/ void addressRelease();
 /*public*/ void addressDispatch();
 /*public*/ void notifyThrottleFound(DccThrottle* t);
 /*public*/ void notifyFailedThrottleRequest(DccLocoAddress* address, QString reason);
 /*public*/ void propertyChange(PropertyChangeEvent* event);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("ThrottleController");
 DccThrottle* throttle;
 DccThrottle* functionThrottle;
 RosterEntry* rosterLoco;// = null;
 DccLocoAddress* leadAddress;
 QChar whichThrottle;
 float speedMultiplier;
 bool isAddressSet;
 bool useLeadLocoF;
 ConsistFunctionController* leadLocoF;// = null;
 void common();
 /*final*/ bool isMomF2;// = WiThrottleManager.withrottlePreferencesInstance().isUseMomF2();
 /*private*/ void clearLeadLoco();


protected:QVector<ThrottleControllerListener*>* listeners;
 /*protected*/ QVector<ControllerInterface*>* controllerListeners;
 /*protected*/ QString buildFStatesHeader();
 /*protected*/ void sendCurrentSpeed(DccThrottle* t);
 /*protected*/ void sendCurrentDirection(DccThrottle* t);
 /*protected*/ void sendSpeedStepMode(DccThrottle* t);
 /*protected*/ void sendAllMomentaryStates(DccThrottle* t);
 /*protected*/ void setSpeed(int rawSpeed);
 /*protected*/ void setDirection(bool isForward) ;
 /*protected*/ void eStop();
 /*protected*/ void idle();
 /*protected*/ void setAddress(int number, bool isLong);
 /*protected*/ void handleFunction(QString inPackage);
 /*protected*/ void forceFunction(QString inPackage);
 /*protected*/ void handleSpeedStepMode(SpeedStepMode::SSMODES newMode);
 /*protected*/ void handleMomentary(QString inPackage);
 /*protected*/ void handleRequest(QString inPackage);

 friend class MultiThrottleController;
};

#endif // THROTTLECONTROLLER_H
