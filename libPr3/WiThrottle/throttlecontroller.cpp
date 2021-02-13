#include "throttlecontroller.h"
#include "loggerfactory.h"
#include "dccthrottle.h"
#include "rosterentry.h"
#include "withrottlemanager.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "throttlecontrollerlistener.h"
#include "controllerinterface.h"
#include "rosterentry.h"
#include "dccthrottle.h"
#include "roster.h"
#include "dcclocoaddress.h"
#include "withrottlepreferences.h"
#include "sleeperthread.h"
#include "consistfunctioncontroller.h"
#include "abstractthrottle.h"

// /*public*/ class ThrottleController implements ThrottleListener, PropertyChangeListener {

/*public*/ ThrottleController::ThrottleController(QObject *parent) : QObject(parent){
common();
}

/*public*/ ThrottleController::ThrottleController(QChar whichThrottleChar, ThrottleControllerListener* tcl, ControllerInterface* cl, QObject *parent) : QObject(parent) {
    //this();
 common();
    setWhichThrottle(whichThrottleChar);
    addThrottleControllerListener(tcl);
    addControllerListener(cl);
}
void ThrottleController::common()
{
speedMultiplier = 1.0f / 126.0f;
isMomF2 = WiThrottleManager::withrottlePreferencesInstance()->isUseMomF2();
 rosterLoco = NULL;
leadLocoF = NULL;
listeners = NULL;
controllerListeners = NULL;
}

/*public*/ void ThrottleController::setWhichThrottle(QChar c) {
    whichThrottle = c;
}

/*public*/ void ThrottleController::addThrottleControllerListener(ThrottleControllerListener* l) {
    if (listeners == NULL) {
        listeners = new QVector<ThrottleControllerListener*>(/*1*/);
    }
    if (!listeners->contains(l)) {
        listeners->append(l);
    }
}

/*public*/ void ThrottleController::removeThrottleControllerListener(ThrottleControllerListener* l) {
    if (listeners == NULL) {
        return;
    }
    if (listeners->contains(l)) {
        listeners->removeOne(l);
    }
}

/**
 * Add a listener to handle: listener.sendPacketToDevice(message);
 *
 */
/*public*/ void ThrottleController::addControllerListener(ControllerInterface* listener) {
    if (controllerListeners == NULL) {
        controllerListeners = new QVector<ControllerInterface*>(1);
    }
    if (!controllerListeners->contains(listener)) {
        controllerListeners->append(listener);
    }
}

/*public*/ void ThrottleController::removeControllerListener(ControllerInterface* listener) {
    if (controllerListeners == NULL) {
        return;
    }
    if (controllerListeners->contains(listener)) {
        controllerListeners->removeOne(listener);
    }
}

/**
 * Receive notification that an address has been released/dispatched
 */
/*public*/ void ThrottleController::addressRelease() {
    isAddressSet = false;
    InstanceManager::throttleManagerInstance()->releaseThrottle(throttle, (ThrottleListener*)this);
    //throttle.removePropertyChangeListener(this);
    disconnect((AbstractThrottle*)throttle->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    throttle = NULL;
    rosterLoco = NULL;
    sendAddress();
    clearLeadLoco();
    for (int i = 0; i < listeners->size(); i++) {
        ThrottleControllerListener* l = listeners->at(i);
        l->notifyControllerAddressReleased(this);
        if (log->isDebugEnabled()) {
            log->debug(tr("Notify TCListener address released: ") + l->metaObject()->className());
        }
    }
}

/*public*/ void ThrottleController::addressDispatch() {
    isAddressSet = false;
    InstanceManager::throttleManagerInstance()->dispatchThrottle(throttle, (ThrottleListener*)this);
    //throttle->removePropertyChangeListener(this);
    disconnect((AbstractThrottle*)throttle->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
    throttle = NULL;
    rosterLoco = NULL;
    sendAddress();
    clearLeadLoco();
    for (int i = 0; i < listeners->size(); i++) {
        ThrottleControllerListener* l = listeners->at(i);
        l->notifyControllerAddressReleased(this);
        if (log->isDebugEnabled()) {
            log->debug(tr("Notify TCListener address dispatched: ") + l->metaObject()->className());
        }
    }
}

/**
 * Recieve notification that a DccThrottle has been found and is in use.
 *
 * @param t The throttle which has been found
 */
//    /*public*/ void notifyAddressThrottleFound(DccThrottle throttle){
//@Override
/*public*/ void ThrottleController::notifyThrottleFound(DccThrottle* t) {
    if (isAddressSet) {
        log->debug("Throttle: " + getCurrentAddressString() + " is already set. (Found is: " + t->getLocoAddress()->toString() + ")");
        return;
    }
    if (t != NULL) {
        throttle = t;
        setFunctionThrottle(throttle);
        //throttle.addPropertyChangeListener(this);
        connect((AbstractThrottle*)throttle->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)) );
        isAddressSet = true;
        if (log->isDebugEnabled()) {
            log->debug(tr("DccThrottle found for: ") + throttle->getLocoAddress()->toString());
        }
    } else {
        log->error("*throttle is NULL!*");
        return;
    }
    for (int i = 0; i < listeners->size(); i++) {
        ThrottleControllerListener* l = listeners->at(i);
        l->notifyControllerAddressFound(this);
        if (log->isDebugEnabled()) {
            log->debug(tr("Notify TCListener address found: ") + l->metaObject()->className());
        }
    }

    if (rosterLoco == NULL) {
        rosterLoco = findRosterEntry(throttle);
    }

    syncThrottleFunctions(throttle, rosterLoco);

    sendAddress();

    sendFunctionLabels(rosterLoco);

    sendAllFunctionStates(throttle);

    sendCurrentSpeed(throttle);

    sendCurrentDirection(throttle);

    sendSpeedStepMode(throttle);

}

//@Override
/*public*/ void ThrottleController::notifyFailedThrottleRequest(DccLocoAddress* address, QString reason) {
    log->error("Throttle request failed for " + address->toString() + " because " + reason);
}


/*
 * Current Format:  RPF}|{whichThrottle]\[eventName}|{newValue
 * This format may be used to send multiple function status, for initial values.
 *
 * Event may be from regular throttle or consist throttle, but is handled the same.
 *
 * Bound params: SpeedSteps, IsForward, SpeedSetting, F##, F##Momentary
 */
//@Override
/*public*/ void ThrottleController::propertyChange(PropertyChangeEvent* event) {
    QString eventName = event->getPropertyName();
    if (log->isDebugEnabled()) {
        log->debug("property change: " + eventName);
    }
    if (eventName.startsWith("F")) {

        if (eventName.contains("Momentary")) {
            return;
        }
        QString message = QString("RPF}|{");
        message.append(whichThrottle);
        message.append("]\\[");
        message.append(eventName);
        message.append("}|{");
        message.append(event->getNewValue().toString());

        foreach (ControllerInterface* listener, *controllerListeners) {
            listener->sendPacketToDevice(message);
        }
    }

}

/*public*/ RosterEntry* ThrottleController::findRosterEntry(DccThrottle* t) {
    RosterEntry* re = NULL;
    if (t->getLocoAddress() != NULL) {
        QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, "" + ((DccLocoAddress*) t->getLocoAddress())->getNumber(), NULL, NULL, NULL, NULL);
        if (l.size() > 0) {
            if (log->isDebugEnabled()) {
                log->debug("Roster Loco found: " + l.at(0)->getDccAddress());
            }
            re = l.at(0);
        }
    }
    return re;
}

/*public*/ void ThrottleController::syncThrottleFunctions(DccThrottle* t, RosterEntry* re) {
    if (re != NULL) {
        for (int funcNum = 0; funcNum < 29; funcNum++) {
#if 0 // TODO:

            try {
                Class<?> partypes[] = {Boolean.TYPE};
                Method setMomentary = t.getClass().getMethod("setF" + funcNum + "Momentary", partypes);
                Object data[] = {Boolean.valueOf(!(re.getFunctionLockable(funcNum)))};

                setMomentary.invoke(t, data);

            } catch (NoSuchMethodException ea) {
                log->warn(ea.getLocalizedMessage(), ea);
            } catch (IllegalAccessException eb) {
                log->warn(eb.getLocalizedMessage(), eb);
         }
//             catch (InvocationTargetException ec) {
//                log->warn(ec.getLocalizedMessage(), ec);
//            }
#endif
        }
    }

}

/*public*/ void ThrottleController::sendFunctionLabels(RosterEntry* re) {

    if (re != NULL) {
        QString functionString;// = new StringBuilder();
        if (whichThrottle == 'S') {
            functionString.append("RS29}|{");
        } else {
            //  I know, it should have been 'RT' but this was before there were two throttles.
            functionString.append("RF29}|{");
        }
        functionString.append(getCurrentAddressString());

        int i;
        for (i = 0; i < 29; i++) {
            functionString.append("]\\[");
            if ((re->getFunctionLabel(i) != NULL)) {
                functionString.append(re->getFunctionLabel(i));
            }
        }
        foreach (ControllerInterface* listener, *controllerListeners) {
            listener->sendPacketToDevice(functionString);
        }
    }

}

/**
 * send all function states, primarily for initial status Current Format:
 * RPF}|{whichThrottle]\[function}|{state]\[function}|{state...
 */
/*public*/ void ThrottleController::sendAllFunctionStates(DccThrottle* t) {

    log->debug("Sending state of all functions");
    QString message(buildFStatesHeader());
#if 0 // TODO:
    try {
        for (int cnt = 0; cnt < 29; cnt++) {
            Method getF = t.getClass().getMethod("getF" + cnt, (Class[]) NULL);
            message.append("]\\[F");
            message.append(cnt);
            message.append("}|{");
            message.append(getF.invoke(t, (Object[]) NULL));
        }

    } catch (NoSuchMethodException ea) {
        log->warn(ea.getLocalizedMessage(), ea);
        return;
    } catch (IllegalAccessException eb) {
        log->warn(eb.getLocalizedMessage(), eb);
        return;
    } catch (java.lang.reflect.InvocationTargetException ec) {
        log->warn(ec.getLocalizedMessage(), ec);
        return;
    }
#endif
    foreach (ControllerInterface* listener, *controllerListeners) {
        listener->sendPacketToDevice(message);
    }

}

/*protected*/ QString ThrottleController::buildFStatesHeader() {
    return ("RPF}|{" + QString(whichThrottle));
}

/*protected*/ void ThrottleController::sendCurrentSpeed(DccThrottle* /*t*/) {
}

/*protected*/ void ThrottleController::sendCurrentDirection(DccThrottle* /*t*/) {
}

/*protected*/ void ThrottleController::sendSpeedStepMode(DccThrottle* /*t*/) {
}

/*protected*/ void ThrottleController::sendAllMomentaryStates(DccThrottle* /*t*/) {
}

/**
 * Figure out what the received command means, where it has to go, and
 * translate to a jmri method.
 *
 * @param inPackage The package minus its prefix which steered it here.
 * @return true to keep reading in run loop.
 */
/*public*/ bool ThrottleController::sort(QString inPackage)
{
 if (isAddressSet)
 {

  try
  {
   QChar c = inPackage.at(0);
  if(c == 'V')  //	Velocity
   setSpeed(inPackage.mid(1).toInt());
  else if(c == 'X')
   eStop();
  else if(c == 'F')	//	Function
   handleFunction(inPackage);
  else if(c == 'f')	//v>=2.0	Force function
   forceFunction(inPackage.mid(1));
  else if(c == 'R')	//	Direction
   setDirection(!inPackage.endsWith("0")); // 0 sets to reverse, all others forward
  else if(c == 'r')//	Release
   addressRelease();
  else if(c == 'd')	//	Dispatch
   addressDispatch();
  else if(c == 'L')	//	Set a Long address.
  {
   addressRelease();
   int addr = inPackage.mid(1).toInt();
   setAddress(addr, true);
  }
  else if(c == 'S')//	Set a Short address.
  {
   addressRelease();
   int addr = inPackage.mid(1).toInt();
   setAddress(addr, false);
  }
  else if(c == 'E')       //v>=1.7    Address from RosterEntry
  {
   addressRelease();
   requestEntryFromID(inPackage.mid(1));
  }
  else if(c == 'C')
    setLocoForConsistFunctions(inPackage.mid(1));
  else if(c == 'c')      //v>=1.7      Consist Lead from RosterEntry
   setRosterLocoForConsistFunctions(inPackage.mid(1));
  else if(c == 'I')
   idle();
  else if(c == 's')     //v>=2.0
   handleSpeedStepMode((SpeedStepMode::SSMODES)inPackage.mid(1).toInt());
   else if(c == 'm')      //v>=2.0
    handleMomentary(inPackage.mid(1));
   else if(c == 'q')      //v>=2.0
    handleRequest(inPackage.mid(1));
  } catch (NullPointerException e)
  {
   log->warn("No throttle frame to receive: " + inPackage);
   return false;
  }
  try
  {    //  Some layout connections cannot handle rapid inputs
   //            Thread.sleep(20);
   SleeperThread::msleep(20);
  }
  catch (InterruptedException ex)
  {
  }
 }
 else
 {  //  Address not set
  QChar c = inPackage.at(0);

  if(c == 'L')	//	Set a Long address.
  {
   int addr = inPackage.mid(1).toInt();
   setAddress(addr, true);
  }
  else if(c == 'S')	//	Set a Short address.
  {
   int addr = inPackage.mid(1).toInt();
   setAddress(addr, false);
  }
  else if(c == 'E')      //v>=1.7      Address from RosterEntry
   requestEntryFromID(inPackage.mid(1));
  else if(c == 'C')
   setLocoForConsistFunctions(inPackage.mid(1));
  else if(c == 'c')      //v>=1.7      Consist Lead from RosterEntry
       setRosterLocoForConsistFunctions(inPackage.mid(1));

  }
  if (inPackage.at(0) == 'Q')
  {//	If device has Quit.
     shutdownThrottle();
     return false;
  }
 return true;
}

/*private*/ void ThrottleController::clearLeadLoco() {
    if (useLeadLocoF) {
        leadLocoF->dispose();
        //functionThrottle.removePropertyChangeListener(this);
        disconnect((AbstractThrottle*)functionThrottle->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        if (throttle != NULL) {
            setFunctionThrottle(throttle);
        }

        leadLocoF = NULL;
        useLeadLocoF = false;
    }
}

/*public*/ void ThrottleController::setFunctionThrottle(DccThrottle* t) {
    functionThrottle = t;
    //functionThrottle.addPropertyChangeListener(this);
    connect((AbstractThrottle*)functionThrottle->self(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void ThrottleController::setLocoForConsistFunctions(QString inPackage) {
    /*
     *      This is used to control speed an direction on the
     *      consist address, but have functions mapped to lead.
     *      Consist address must be set first!
     */

    leadAddress = new DccLocoAddress(inPackage.mid(1).toInt(), (inPackage.at(0) != 'S'));
    if (log->isDebugEnabled()) {
        log->debug("Setting lead loco address: " + leadAddress->toString()
                + ", for consist: " + getCurrentAddressString());
    }
    clearLeadLoco();
    leadLocoF = new ConsistFunctionController(this);
    useLeadLocoF = leadLocoF->requestThrottle(leadAddress);

    if (!useLeadLocoF) {
        log->warn("Lead loco address not available.");
        leadLocoF = NULL;
    }
}

/*public*/ void ThrottleController::setRosterLocoForConsistFunctions(QString id) {
    RosterEntry* re = NULL;
    QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, id);
    if (l.size() > 0) {
        if (log->isDebugEnabled()) {
            log->debug("Consist Lead Roster Loco found: " + l.at(0)->getDccAddress() + " for ID: " + id);
        }
        re = l.at(0);
        clearLeadLoco();
        leadLocoF = new ConsistFunctionController(this, re);
        useLeadLocoF = leadLocoF->requestThrottle(re->getDccLocoAddress());

        if (!useLeadLocoF) {
            log->warn("Lead loco address not available.");
            leadLocoF = NULL;
        }
    } else {
        log->debug("No Roster Loco found for: " + id);
        return;
    }
}

//  Device is quitting or has lost connection
/*public*/ void ThrottleController::shutdownThrottle() {

    try {
        if (isAddressSet) {
            throttle->setSpeedSetting(0);
            addressRelease();
        }
    } catch (NullPointerException e) {
        log->warn("No throttle to shutdown");
    }
    clearLeadLoco();
}

/**
 * handle the conversion from rawSpeed to the float value needed in the
 * DccThrottle
 *
 * @param rawSpeed Value sent from mobile device, range 0 - 126
 */
/*protected*/ void ThrottleController::setSpeed(int rawSpeed) {

    float newSpeed = (rawSpeed * speedMultiplier);

    log->debug(tr("raw: %1, NewSpd: %2").arg(rawSpeed).arg(newSpeed));
    throttle->setSpeedSetting(newSpeed);
}

/*protected*/ void ThrottleController::setDirection(bool isForward) {
    log->debug(tr("set direction to:%1").arg((isForward?"Fwd":"Rev")));
    throttle->setIsForward(isForward);
}

/*protected*/ void ThrottleController::eStop() {
    throttle->setSpeedSetting(-1);
}

/*protected*/ void ThrottleController::idle() {
    throttle->setSpeedSetting(0);
}

/*protected*/ void ThrottleController::setAddress(int number, bool isLong) {
    if (rosterLoco != NULL) {
        InstanceManager::throttleManagerInstance()->requestThrottle(rosterLoco, (ThrottleListener*)this);
    } else {
        InstanceManager::throttleManagerInstance()->requestThrottle(number, isLong, (ThrottleListener*)this);
    }
}

/*public*/ void ThrottleController::requestEntryFromID(QString id) {
    RosterEntry* re = NULL;
    QList<RosterEntry*> l = Roster::getDefault()->matchingList(NULL, NULL, NULL, NULL, NULL, NULL, id);
    if (l.size() > 0) {
        if (log->isDebugEnabled()) {
            log->debug("Roster Loco found: " + l.at(0)->getDccAddress() + " for ID: " + id);
        }
        re = l.at(0);
        rosterLoco = re;
        setAddress(re->getDccAddress().toInt(), re->isLongAddress());
    } else {
        log->debug("No Roster Loco found for: " + id);
    }
}

/*public*/ DccThrottle* ThrottleController::getThrottle() {
    return throttle;
}

/*public*/ DccThrottle* ThrottleController::getFunctionThrottle() {
    return functionThrottle;
}

/*public*/ DccLocoAddress* ThrottleController::getCurrentAddress() {
    return (DccLocoAddress*) throttle->getLocoAddress();
}

/**
 * Get the string representation of this throttles address. Returns 'Not
 * Set' if no address in use.
 */
/*public*/ QString ThrottleController::getCurrentAddressString() {
    if (isAddressSet) {
        return ((DccLocoAddress*) throttle->getLocoAddress())->toString();
    } else {
        return "Not Set";
    }
}

/*public*/ void ThrottleController::sendAddress() {
    foreach (ControllerInterface* listener, *controllerListeners) {
        listener->sendPacketToDevice(whichThrottle + getCurrentAddressString());
    }
}

//	Function methods
/*protected*/ void ThrottleController::handleFunction(QString inPackage)
{
 //	get the function # sent from device
 QString receivedFunction = inPackage.mid(2);
 bool state = false;

 if (inPackage.at(1) == '1')
 {	//	Function Button down
  if (log->isDebugEnabled())
  {
   log->debug("Trying to set function " + receivedFunction);
  }
  //	Toggle button state:
#if 1
  try
  {
//            Method getF = functionThrottle.getClass().getMethod("getF" + receivedFunction, (Class[]) NULL);
   QObject* obj = NULL;
   const char* className = functionThrottle->self()->metaObject()->className();
   int typeId = QMetaType::type(className);
   if(typeId > 0)
   {
 #if QT_VERSION < 0x050000
    obj = (QObject*)QMetaType::construct(typeId);
 #else
    obj = (QObject*)QMetaType::create(typeId);
#endif
   }
   else
    throw IllegalAccessException(tr("class %1 not found").arg(className));
   QString mName = "getF" + receivedFunction;
   int methodIndex = obj->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(mName.toLocal8Bit()));
   if(methodIndex <0 ) throw NoSuchMethodException(tr("%1::%2() not found").arg(className).arg(mName));
   QMetaMethod getF = obj->metaObject()->method(methodIndex);
//            Class<?> partypes[] = {Boolean.TYPE};
//            Method setF = functionThrottle.getClass().getMethod("setF" + receivedFunction, partypes);
   mName = "setf"+receivedFunction;
   methodIndex = obj->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(mName.toLocal8Bit()));
   if(methodIndex <0 ) throw NoSuchMethodException(tr("%1::%2() not found").arg(className).arg(mName));

   QMetaMethod setF = obj->metaObject()->method(methodIndex);
   if(!setF.invoke(obj, Qt::DirectConnection,  Q_ARG(bool, state)))
    throw InvocationTargetException(tr("%1::%2() failed").arg(className).arg(mName));

//            state = (Boolean) getF.invoke(functionThrottle, (Object[]) NULL);
   if(!getF.invoke(obj, Qt::DirectConnection, Q_RETURN_ARG(bool,state)))
    throw InvocationTargetException(tr("%1::%2() failed").arg(className).arg(mName));


//            Object data[] = {Boolean.valueOf(!state)};
    state = !state;

    //setF.invoke(functionThrottle, data);
    setF.invoke(obj, Qt::DirectConnection, Q_ARG(bool, state));

    if (log->isDebugEnabled())
    {
     log->debug(QString("Throttle: ") + functionThrottle->getLocoAddress()->toString() + ", Function: " + receivedFunction + ", set state: " + ((!state)?"true":"false"));
    }

  }
  catch (NoSuchMethodException ea)
  {
   log->warn(ea.getLocalizedMessage());
  }
  catch (IllegalAccessException eb)
  {
   log->warn(eb.getLocalizedMessage());
  }
  catch (InvocationTargetException ec)
  {
   log->warn(ec.getLocalizedMessage());
  }
#endif
 }
 else
 {	//	Function Button up

  //  F2 is momentary for horn, unless prefs are set to follow roster entry
  if ((isMomF2) && (receivedFunction == ("2"))) {
      functionThrottle->setF2(false);
      return;
  }

  //	Do nothing if lockable, turn off if momentary
#if 1
  try
  {
   //Method getFMom = functionThrottle.getClass().getMethod("getF" + receivedFunction + "Momentary", (Class[]) NULL);
   QObject* obj = NULL;
   const char* className = functionThrottle->self()->metaObject()->className();
   int typeId = QMetaType::type(className);
   if(typeId > 0)
   {
#if QT_VERSION < 0x050000
    obj = (QObject*)QMetaType::construct(typeId);
#else
    obj = (QObject*)QMetaType::create(typeId);
#endif
   }
   else
    throw IllegalAccessException(tr("class %1 not found").arg(className));
   QString mName = "getF" + receivedFunction + "Momentary";
   int methodIndex = obj->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(mName.toLocal8Bit()));
   if(methodIndex <0 ) throw NoSuchMethodException(tr("%1::%2() not found").arg(className).arg(mName));
   QMetaMethod getFMom = obj->metaObject()->method(methodIndex);
//            Class<?> partypes[] = {Boolean.TYPE};
      //Method setF = functionThrottle.getClass().getMethod("setF" + receivedFunction, partypes);
   mName = "setF"+receivedFunction+ "Momentary";
   methodIndex = obj->metaObject()->indexOfMethod(QMetaObject::normalizedSignature(mName.toLocal8Bit()));
   if(methodIndex <0 ) throw NoSuchMethodException(tr("%1::%2() not found").arg(className).arg(mName));

   QMetaMethod setFMom = obj->metaObject()->method(methodIndex);
   bool state;
   //   if ((Boolean) getFMom.invoke(functionThrottle, (Object[]) NULL)) {
   if(!getFMom.invoke(obj, Qt::DirectConnection, Q_RETURN_ARG(bool, state)))
    throw InvocationTargetException(tr("%1").arg(mName));
//                Object data[] = {Boolean.valueOf(false)};
   if(state)
   {

    //setF.invoke(functionThrottle, data);
    if(!setFMom.invoke(obj, Qt::DirectConnection, Q_ARG(bool, state)))
     throw InvocationTargetException("error doing setF" + receivedFunction+"Momentary");
    if (log->isDebugEnabled())
    {
     log->debug(QString("Throttle: ") + functionThrottle->getLocoAddress()->toString() + ", Momentary Function: " + receivedFunction + ", set false");
    }
   }

   } catch (NoSuchMethodException ea) {
       log->warn(ea.getLocalizedMessage());
   } catch (IllegalAccessException eb) {
       log->warn(eb.getLocalizedMessage());
   } catch (InvocationTargetException ec) {
       log->warn(ec.getLocalizedMessage());
   }
#endif
 }
}

/*protected*/ void ThrottleController::forceFunction(QString inPackage)
{
#if 0
    QString receivedFunction = inPackage.mid(1);
    Object data[] = new Object[1];

    if (inPackage.charAt(0) == '1') {	//	Set function on
        data[0] = Boolean.valueOf(true);
        if (log->isDebugEnabled()) {
            log->debug("Trying to set function " + receivedFunction + "to ON");
        }
    } else {
        data[0] = Boolean.valueOf(false);
        if (log->isDebugEnabled()) {
            log->debug("Trying to set function " + receivedFunction + "to OFF");
        }
    }
    try {
        Class<?> partypes[] = {Boolean.TYPE};
        Method setF = throttle.getClass().getMethod("setF" + receivedFunction, partypes);

        setF.invoke(throttle, data);

    } catch (NoSuchMethodException ea) {
        log->warn(ea.getLocalizedMessage(), ea);
    } catch (IllegalAccessException eb) {
        log->warn(eb.getLocalizedMessage(), eb);
    } catch (java.lang.reflect.InvocationTargetException ec) {
        log->warn(ec.getLocalizedMessage(), ec);
    }
#endif
}

/*protected*/ void ThrottleController::handleSpeedStepMode(SpeedStepMode::SSMODES newMode) {
    throttle->setSpeedStepMode(newMode);
}

/*protected*/ void ThrottleController::handleMomentary(QString inPackage)
{
#if 0
    QString receivedFunction = inPackage.mid(1);
    Object data[] = new Object[1];

    if (inPackage.charAt(0) == '1') {	//	Set Momentary TRUE
        data[0] = Boolean.valueOf(true);
        if (log->isDebugEnabled()) {
            log->debug("Trying to set function " + receivedFunction + " to Momentary");
        }
    } else {
        data[0] = Boolean.valueOf(false);
        if (log->isDebugEnabled()) {
            log->debug("Trying to set function " + receivedFunction + " to Locking");
        }
    }
    try {
        Class<?> partypes[] = {Boolean.TYPE};
        Method setF = throttle.getClass().getMethod("setF" + receivedFunction + "Momentary", partypes);

        setF.invoke(throttle, data);

    } catch (NoSuchMethodException ea) {
        log->warn(ea.getLocalizedMessage(), ea);
    } catch (IllegalAccessException eb) {
        log->warn(eb.getLocalizedMessage(), eb);
    } catch (java.lang.reflect.InvocationTargetException ec) {
        log->warn(ec.getLocalizedMessage(), ec);
    }
#endif
}

/*protected*/ void ThrottleController::handleRequest(QString inPackage) {
    QChar c = inPackage.at(0);
    if(c ==  'V')
      sendCurrentSpeed(throttle);
     else if(c == 'R')
      sendCurrentDirection(throttle);
      else if(c == 's')
      sendSpeedStepMode(throttle);
     else if(c == 'm')
      sendAllMomentaryStates(throttle);
}

/*private*/ /*final*/ /*static*/ Logger* ThrottleController::log = LoggerFactory::getLogger("ThrottleController");
