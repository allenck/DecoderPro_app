#include "abstractthrottle.h"
#include "instancemanager.h"
#include "commandstation.h"
#include "nmrapacket.h"
#include "Throttle/throttlewindow.h"
#include "addresspanel.h"

/*public final*/ /*static*/ float AbstractThrottle::SPEED_STEP_14_INCREMENT=1.0f/14.0f;
/*public final*/ /*static*/ float AbstractThrottle::SPEED_STEP_27_INCREMENT=1.0f/27.0f;
/*public final*/ /*static*/ float AbstractThrottle::SPEED_STEP_28_INCREMENT=1.0f/28.0f;
/*public final*/ /*static*/ float AbstractThrottle::SPEED_STEP_128_INCREMENT=1.0f/126.0f; // remember there are only 126
                                                                // non-stop values in 128 speed

AbstractThrottle::AbstractThrottle(SystemConnectionMemo* memo, QObject *parent) //:    DccThrottle(parent)
{
 active = true;
 adapterMemo = memo;
 listeners = new QVector<PropertyChangeListener*>();
 re = nullptr;
 this->parent = parent;
 setObjectName("AbstractThrottle");
 speedStepMode = SpeedStepMode::UNKNOWN;

 log = new Logger("AbstractThrottle");
 durationRunning = 0;
 f0=f1=f2=f3=f4=f5=f6=f7=f8=f9=f10=f11=f12=f13=f14=f15=f16=f17=f18=f19=f20=f21=f22=f23=f24=f25=f26=f27=f28=false;
}
/**
 * An abstract implementation of DccThrottle.
 * Based on Glen Oberhauser's original LnThrottleManager implementation.
 * <P>
 * Note that this implements DccThrottle, not Throttle directly, so
 * it has some DCC-specific content.
 *
 * @author  Bob Jacobsen  Copyright (C) 2001, 2005
 * @version $Revision: 22484 $
 */
//abstract /*public*/ class AbstractThrottle implements DccThrottle {


//    /*public*/ AbstractThrottle(SystemConnectionMemo memo) {
//        active = true;
//        adapterMemo = memo;
//    }


/** speed - expressed as a value 0.0 -> 1.0. Negative means emergency stop.
 * This is an bound parameter.
 */
/*public*/ float AbstractThrottle::getSpeedSetting() {
    return speedSetting;
}

/*
 * setSpeedSetting - Implementing functions should override this
 * function, but should either make a call to super.setSpeedSetting()
 * to notify the listeners, or should notify the listeners themselves.
 */
//@Override
/*public*/ void AbstractThrottle::setSpeedSetting(float speed)
{
 if(qAbs(this->speedSetting - speed)>0.0001 )
  setSpeedSetting(speed, false, false);
}

/**
 * setSpeedSetting - Implementations should override this method only if they normally suppress
 * messages to the system if, as far as JMRI can tell, the new message would make no difference
 * to the system state (eg. the speed is the same, or effectivly the same, as the existing speed).
 * Then, the boolean options can affect this behaviour.
 *
 * @param speed - the new speed
 * @param allowDuplicates - don't suppress messages
 * @param allowDuplicatesOnStop - don't suppress messages if the new speed is 'stop'
 */
//@Override
/*public*/ void AbstractThrottle::setSpeedSetting(float speed, bool /*allowDuplicates*/, bool /*allowDuplicatesOnStop*/) {
    if (qAbs(this->speedSetting - speed) > 0.0001) {
        notifyPropertyChangeListener("SpeedSetting", this->speedSetting, this->speedSetting = speed);
    }
    record(speed);
}

/**
 * setSpeedSettingAgain - set the speed and don't ever supress the sending of messages to the system
 *
 * @param speed - the new speed
 */
//@Override
/*public*/ void AbstractThrottle::setSpeedSettingAgain(float speed) {
    setSpeedSetting(speed, true, true);
}

/** direction
 * This is an bound parameter.
 */
/*public*/ bool AbstractThrottle::getIsForward() {
    return isForward;
}

/*
 * setIsForward - Implementing functions should override this
 * function, but should either make a call to super.setIsForward()
 * to notify the listeners, or should notify the listeners themselves.
 */
/*public*/ void AbstractThrottle::setIsForward(bool forward)
{
 if(forward!=this->isForward)
  notifyPropertyChangeListener("IsForward",
                             (this->isForward),
                             (this->isForward=forward));
}

// functions - note that we use the naming for DCC, though that's not the implication;
// see also DccThrottle interface
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QVector<bool> AbstractThrottle::getFunctions() {
    //return Arrays.copyOf(FUNCTION_BOOLEAN_ARRAY,FUNCTION_BOOLEAN_ARRAY.length);
 return QVector<bool>(FUNCTION_BOOLEAN_ARRAY);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QVector<bool> AbstractThrottle::getFunctionsMomentary() {
//    return Arrays.copyOf(FUNCTION_MOMENTARY_BOOLEAN_ARRAY,
//        FUNCTION_MOMENTARY_BOOLEAN_ARRAY.length);
 return QVector<bool>(FUNCTION_MOMENTARY_BOOLEAN_ARRAY);

}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool AbstractThrottle::getFunction(int fN) {
    if (fN<0 || fN > FUNCTION_BOOLEAN_ARRAY.length()-1){
        log->warn(tr("Unhandled get function: %1").arg(fN));
        return false;
    }
    return FUNCTION_BOOLEAN_ARRAY[fN];
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool AbstractThrottle::getFunctionMomentary(int fN) {
    if (fN<0 || fN > FUNCTION_MOMENTARY_BOOLEAN_ARRAY.length()-1){
        log->warn(tr("Unhandled get momentary function: %1").arg(fN));
        return false;
    }
    return FUNCTION_MOMENTARY_BOOLEAN_ARRAY[fN];

}

/*public*/ bool AbstractThrottle::getF0() {
    return f0;
}

/*public*/ bool AbstractThrottle::getF1() {
    return f1;
}

/*public*/ bool AbstractThrottle::getF2() {
    return f2;
}

/*public*/ bool AbstractThrottle::getF3() {
    return f3;
}

/*public*/ bool AbstractThrottle::getF4() {
    return f4;
}

/*public*/ bool AbstractThrottle::getF5() {
    return f5;
}

/*public*/ bool AbstractThrottle::getF6() {
    return f6;
}

/*public*/ bool AbstractThrottle::getF7() {
    return f7;
}

/*public*/ bool AbstractThrottle::getF8() {
    return f8;
}

/*public*/ bool AbstractThrottle::getF9() {
    return f9;
}

/*public*/ bool AbstractThrottle::getF10() {
    return f10;
}

/*public*/ bool AbstractThrottle::getF11() {
    return f11;
}

/*public*/ bool AbstractThrottle::getF12() {
    return f12;
}

/*public*/ bool AbstractThrottle::getF13() {
    return f13;
}

/*public*/ bool AbstractThrottle::getF14() {
    return f14;
}

/*public*/ bool AbstractThrottle::getF15() {
    return f15;
}

/*public*/ bool AbstractThrottle::getF16() {
    return f16;
}

/*public*/ bool AbstractThrottle::getF17() {
    return f17;
}

/*public*/ bool AbstractThrottle::getF18() {
    return f18;
}

/*public*/ bool AbstractThrottle::getF19() {
    return f19;
}

/*public*/ bool AbstractThrottle::getF20() {
    return f20;
}

/*public*/ bool AbstractThrottle::getF21() {
    return f21;
}

/*public*/ bool AbstractThrottle::getF22() {
    return f22;
}

/*public*/ bool AbstractThrottle::getF23() {
    return f23;
}

/*public*/ bool AbstractThrottle::getF24() {
    return f24;
}

/*public*/ bool AbstractThrottle::getF25() {
    return f25;
}

/*public*/ bool AbstractThrottle::getF26() {
    return f26;
}

/*public*/ bool AbstractThrottle::getF27() {
    return f27;
}

/*public*/ bool AbstractThrottle::getF28() {
    return f28;
}

// function momentary status  - note that we use the naming for DCC,
// though that's not the implication;
// see also DccThrottle interface
/*public*/ bool AbstractThrottle::getF0Momentary() {
    return f0Momentary;
}

/*public*/ bool AbstractThrottle::getF1Momentary() {
    return f1Momentary;
}

/*public*/ bool AbstractThrottle::getF2Momentary() {
    return f2Momentary;
}

/*public*/ bool AbstractThrottle::getF3Momentary() {
    return f3Momentary;
}

/*public*/ bool AbstractThrottle::getF4Momentary() {
    return f4Momentary;
}

/*public*/ bool AbstractThrottle::getF5Momentary() {
    return f5Momentary;
}

/*public*/ bool AbstractThrottle::getF6Momentary() {
    return f6Momentary;
}

/*public*/ bool AbstractThrottle::getF7Momentary() {
    return f7Momentary;
}

/*public*/ bool AbstractThrottle::getF8Momentary() {
    return f8Momentary;
}

/*public*/ bool AbstractThrottle::getF9Momentary() {
    return f9Momentary;
}

/*public*/ bool AbstractThrottle::getF10Momentary() {
    return f10Momentary;
}

/*public*/ bool AbstractThrottle::getF11Momentary() {
    return f11Momentary;
}

/*public*/ bool AbstractThrottle::getF12Momentary() {
    return f12Momentary;
}

/*public*/ bool AbstractThrottle::getF13Momentary() {
    return f13Momentary;
}

/*public*/ bool AbstractThrottle::getF14Momentary() {
    return f14Momentary;
}

/*public*/ bool AbstractThrottle::getF15Momentary() {
    return f15Momentary;
}

/*public*/ bool AbstractThrottle::getF16Momentary() {
    return f16Momentary;
}

/*public*/ bool AbstractThrottle::getF17Momentary() {
    return f17Momentary;
}

/*public*/ bool AbstractThrottle::getF18Momentary() {
    return f18Momentary;
}

/*public*/ bool AbstractThrottle::getF19Momentary() {
    return f19Momentary;
}

/*public*/ bool AbstractThrottle::getF20Momentary() {
    return f20Momentary;
}

/*public*/ bool AbstractThrottle::getF21Momentary() {
    return f21Momentary;
}

/*public*/ bool AbstractThrottle::getF22Momentary() {
    return f22Momentary;
}

/*public*/ bool AbstractThrottle::getF23Momentary() {
    return f23Momentary;
}

/*public*/ bool AbstractThrottle::getF24Momentary() {
    return f24Momentary;
}

/*public*/ bool AbstractThrottle::getF25Momentary() {
    return f25Momentary;
}

/*public*/ bool AbstractThrottle::getF26Momentary() {
    return f26Momentary;
}

/*public*/ bool AbstractThrottle::getF27Momentary() {
    return f27Momentary;
}

/*public*/ bool AbstractThrottle::getF28Momentary() {
    return f28Momentary;
}


// register for notification if any of the properties change
/*public*/ void AbstractThrottle::removePropertyChangeListener(PropertyChangeListener* l) {
    log->debug("Removing property change " + l->objectName());
    if (listeners->contains(l)) {
        listeners->remove(listeners->indexOf(l));
    }
    log->debug("remove listeners size is " + QString("%1").arg(listeners->size()));
    if ((listeners->size()==0))
    {
        log->debug("Listener Size is 0 so will call the dispose in the InstanceManger with an empty throttleListenr nullptr value");
// TODO:
//        InstanceManager::throttleManagerInstance().disposeThrottle(this, new ThrottleListener(){
//            /*public*/ void notifyFailedThrottleRequest(DccLocoAddress address, String reason){ }
//            /*public*/ void notifyThrottleFound(DccThrottle t) { }
//        });
    }
}

/*public*/ void AbstractThrottle::addPropertyChangeListener(PropertyChangeListener* l) {
    log->debug(QString("listeners added ") + QString(l?l->objectName():"null"));
    // add only if not already registered
    if (!listeners->contains(l))
    {
     listeners->append(l);
     connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
    }
    log->debug("listeners size is " + QString("%1").arg(listeners->size()));
}

/**
 * Trigger the notification of all PropertyChangeListeners
 */
//@SuppressWarnings("unchecked")
/*protected*/ void AbstractThrottle::notifyPropertyChangeListener(QString property, QVariant oldValue, QVariant newValue)
{
 if (oldValue==(newValue))
  Logger::error("notifyPropertyChangeListener without change");
 // make a copy of the listener vector to synchronized not needed for transmit
 QVector<PropertyChangeListener*>* v = new QVector<PropertyChangeListener*>();
 //synchronized(this)
 {
  //v = (QVector<PropertyChangeListener*>*) listeners->clone();
  QMutexLocker locker(&mutex);
  foreach (PropertyChangeListener* l, *listeners)
  {
   v->append(l);
  }
 }
 if (log->isDebugEnabled()) log->debug("notify "+QString("%1").arg(v->size()) +" listeners about property " +property);
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  PropertyChangeListener* client = v->at(i);
  if(client == nullptr)
      continue;
//  PropertyChangeEvent* event = new PropertyChangeEvent(this, property, oldValue, newValue);
//  if(qobject_cast<ThrottleWindow*>(client))
//  ((ThrottleWindow*)client)->propertyChange(event);
//  if(qobject_cast<AddressPanel*>(client))
//  ((AddressPanel*)client)->propertyChange(event);
 }
 emit propertyChange(new PropertyChangeEvent(this, property, oldValue, newValue));
}

/*public*/ QVector<PropertyChangeListener*>* AbstractThrottle::getListeners(){
    return listeners;
}


/**
 * Dispose when finished with this object.  After this, further usage of
 * this Throttle object will result in a JmriException.
 */
//    @Deprecated
//    /*public*/ void AbstractThrottle::dispose() {
//        if (!active) log.error("Dispose called when not active");
//        log.warn("Dispose called without knowing the original throttle listener");
//        InstanceManager.throttleManagerInstance().disposeThrottle(this, nullptr);
//    }

/*public*/ void AbstractThrottle::dispose(ThrottleListener* l) {
    if (!active) Logger::error("Dispose called when not active");
    InstanceManager::throttleManagerInstance()->disposeThrottle((DccThrottle*)this, l);
}

/*public*/ void AbstractThrottle::dispatch(ThrottleListener* l) {
    if (!active) log->warn("dispatch called when not active");
    InstanceManager::throttleManagerInstance()->dispatchThrottle((DccThrottle*)this, l);
}

/*public*/ void AbstractThrottle::release(ThrottleListener* l) {
    if (!active) log->warn("release called when not active");
    InstanceManager::throttleManagerInstance()->releaseThrottle((DccThrottle*)this, l);
}

//    /*abstract*/ /*protected*/ void throttleDispose();

/**
 * to handle quantized speed. Note this can change! Valued returned is
 * always positive.
 */
/*public*/ float AbstractThrottle::getSpeedIncrement() {
    return SpeedStepMode(speedStepMode).increment;
}

// functions - note that we use the naming for DCC, though that's not the implication;
// see also DccThrottle interface
/*public*/ void AbstractThrottle::setF0(bool f0) {
    bool old = this->f0;
    this->f0 = f0;
    sendFunctionGroup1();
    if (old != this->f0)
        notifyPropertyChangeListener(Throttle::F0, old, this->f0 );
}

/*public*/ void AbstractThrottle::setF1(bool f1) {
    bool old = this->f1;
    this->f1 = f1;
    sendFunctionGroup1();
    if (old != this->f1)
        notifyPropertyChangeListener(Throttle::F1, old, this->f1 );
}

/*public*/ void AbstractThrottle::setF2(bool f2) {
    bool old = this->f2;
    this->f2 = f2;
    sendFunctionGroup1();
    if (old != this->f2)
        notifyPropertyChangeListener(Throttle::F2, old, this->f2 );
}

/*public*/ void AbstractThrottle::setF3(bool f3) {
    bool old = this->f3;
    this->f3 = f3;
    sendFunctionGroup1();
    if (old != this->f3)
        notifyPropertyChangeListener(Throttle::F3, old, this->f3 );
}

/*public*/ void AbstractThrottle::setF4(bool f4) {
    bool old = this->f4;
    this->f4 = f4;
    sendFunctionGroup1();
    if (old != this->f4)
        notifyPropertyChangeListener(Throttle::F4, old, this->f4 );
}

/*public*/ void AbstractThrottle::setF5(bool f5) {
    bool old = this->f5;
    this->f5 = f5;
    sendFunctionGroup2();
    if (old != this->f5)
        notifyPropertyChangeListener(Throttle::F5, old, this->f5 );
}

/*public*/ void AbstractThrottle::setF6(bool f6) {
    bool old = this->f6;
    this->f6 = f6;
    sendFunctionGroup2();
    if (old != this->f6)
        notifyPropertyChangeListener(Throttle::F6, old, this->f6 );
}

/*public*/ void AbstractThrottle::setF7(bool f7) {
    bool old = this->f7;
    this->f7 = f7;
    sendFunctionGroup2();
    if (old != this->f7)
        notifyPropertyChangeListener(Throttle::F7, old, this->f7 );
}

/*public*/ void AbstractThrottle::setF8(bool f8) {
    bool old = this->f8;
    this->f8 = f8;
    sendFunctionGroup2();
    if (old != this->f8)
        notifyPropertyChangeListener(Throttle::F8, old, this->f8 );
}

/*public*/ void AbstractThrottle::setF9(bool f9) {
    bool old = this->f9;
    this->f9 = f9;
    sendFunctionGroup3();
    if (old != this->f9)
        notifyPropertyChangeListener(Throttle::F9, old, this->f9 );
}

/*public*/ void AbstractThrottle::setF10(bool f10) {
    bool old = this->f10;
    this->f10 = f10;
    sendFunctionGroup3();
    if (old != this->f10)
        notifyPropertyChangeListener(Throttle::F10, old, this->f10 );
}

/*public*/ void AbstractThrottle::setF11(bool f11) {
    bool old = this->f11;
    this->f11 = f11;
    sendFunctionGroup3();
    if (old != this->f11)
        notifyPropertyChangeListener(Throttle::F11, old, this->f11 );
}

/*public*/ void AbstractThrottle::setF12(bool f12) {
    bool old = this->f12;
    this->f12 = f12;
    sendFunctionGroup3();
    if (old != this->f12)
        notifyPropertyChangeListener(Throttle::F12, old, this->f12 );
}

/*public*/ void AbstractThrottle::setF13(bool f13) {
    bool old = this->f13;
    this->f13 = f13;
    sendFunctionGroup4();
    if (old != this->f13)
        notifyPropertyChangeListener(Throttle::F13, old, this->f13 );
}

/*public*/ void AbstractThrottle::setF14(bool f14) {
    bool old = this->f14;
    this->f14 = f14;
    sendFunctionGroup4();
    if (old != this->f14)
        notifyPropertyChangeListener(Throttle::F14, old, this->f14 );
}

/*public*/ void AbstractThrottle::setF15(bool f15) {
    bool old = this->f15;
    this->f15 = f15;
    sendFunctionGroup4();
    if (old != this->f15)
        notifyPropertyChangeListener(Throttle::F15, old, this->f15 );
}

/*public*/ void AbstractThrottle::setF16(bool f16) {
    bool old = this->f16;
    this->f16 = f16;
    sendFunctionGroup4();
    if (old != this->f16)
        notifyPropertyChangeListener(Throttle::F16, old, this->f16 );
}

/*public*/ void AbstractThrottle::setF17(bool f17) {
    bool old = this->f17;
    this->f17 = f17;
    sendFunctionGroup4();
    if (old != this->f17)
        notifyPropertyChangeListener(Throttle::F17, old, this->f17 );
}

/*public*/ void AbstractThrottle::setF18(bool f18) {
    bool old = this->f18;
    this->f18 = f18;
    sendFunctionGroup4();
    if (old != this->f18)
        notifyPropertyChangeListener(Throttle::F18, old, this->f18 );
}

/*public*/ void AbstractThrottle::setF19(bool f19) {
    bool old = this->f19;
    this->f19 = f19;
    sendFunctionGroup4();
    if (old != this->f19)
        notifyPropertyChangeListener(Throttle::F19, old, this->f19 );
}

/*public*/ void AbstractThrottle::setF20(bool f20) {
    bool old = this->f20;
    this->f20 = f20;
    sendFunctionGroup4();
    if (old != this->f20)
        notifyPropertyChangeListener(Throttle::F20, old, this->f20 );
}

/*public*/ void AbstractThrottle::setF21(bool f21) {
    bool old = this->f21;
    this->f21 = f21;
    sendFunctionGroup5();
    if (old != this->f21)
        notifyPropertyChangeListener(Throttle::F21, old, this->f21 );
}

/*public*/ void AbstractThrottle::setF22(bool f22) {
    bool old = this->f22;
    this->f22 = f22;
    sendFunctionGroup5();
    if (old != this->f22)
        notifyPropertyChangeListener(Throttle::F22, old, this->f22 );
}

/*public*/ void AbstractThrottle::setF23(bool f23) {
    bool old = this->f23;
    this->f23 = f23;
    sendFunctionGroup5();
    if (old != this->f23)
        notifyPropertyChangeListener(Throttle::F23, old, this->f23 );
}

/*public*/ void AbstractThrottle::setF24(bool f24) {
    bool old = this->f24;
    this->f24 = f24;
    sendFunctionGroup5();
    if (old != this->f24)
        notifyPropertyChangeListener(Throttle::F24, old, this->f24 );
}

/*public*/ void AbstractThrottle::setF25(bool f25) {
    bool old = this->f25;
    this->f25 = f25;
    sendFunctionGroup5();
    if (old != this->f25)
        notifyPropertyChangeListener(Throttle::F25, old, this->f25 );
}

/*public*/ void AbstractThrottle::setF26(bool f26) {
    bool old = this->f26;
    this->f26 = f26;
    sendFunctionGroup5();
    if (old != this->f26)
        notifyPropertyChangeListener(Throttle::F26, old, this->f26 );
}

/*public*/ void AbstractThrottle::setF27(bool f27) {
    bool old = this->f27;
    this->f27 = f27;
    sendFunctionGroup5();
    if (old != this->f27)
        notifyPropertyChangeListener(Throttle::F27, old, this->f27 );
}

/*public*/ void AbstractThrottle::setF28(bool f28) {
    bool old = this->f28;
    this->f28 = f28;
    sendFunctionGroup5();
    if (old != this->f28)
        notifyPropertyChangeListener(Throttle::F28, old, this->f28 );
}
/**
  * Send whole (DCC) Function Group for a particular function number.
  * @param functionNum Function Number
  * @param momentary False to send normal function status, true to send momentary.
  */
 /*protected*/ void AbstractThrottle::sendFunctionGroup(int functionNum, bool momentary){
     switch (FUNCTION_GROUPS[functionNum]) {
         case 1:
             if (momentary) sendMomentaryFunctionGroup1(); else sendFunctionGroup1();
             break;
         case 2:
             if (momentary) sendMomentaryFunctionGroup2(); else sendFunctionGroup2();
             break;
         case 3:
             if (momentary) sendMomentaryFunctionGroup3(); else sendFunctionGroup3();
             break;
         case 4:
             if (momentary) sendMomentaryFunctionGroup4(); else sendFunctionGroup4();
             break;
         case 5:
             if (momentary) sendMomentaryFunctionGroup5(); else sendFunctionGroup5();
             break;
         default:
             break;
     }
 }

 /**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractThrottle::setFunction(int functionNum, bool newState) {
    if (functionNum < 0 || functionNum > FUNCTION_BOOLEAN_ARRAY.length()-1) {
        log->warn(tr("Unhandled set function number: %1 %2").arg(functionNum).arg(this->metaObject()->className()));
        return;
    }
    bool old = FUNCTION_BOOLEAN_ARRAY[functionNum];
    FUNCTION_BOOLEAN_ARRAY[functionNum] = newState;
    sendFunctionGroup(functionNum,false);
//    firePropertyChange(Throttle::getFunctionString(functionNum), old, newState);
}

/**
 * Update the state of a single function. Updates function value and
 * ChangeListener. Does not send outward message TO hardware.
 *
 * @param fn    Function Number 0-28
 * @param state On - True, Off - False
 */
/*public*/ void AbstractThrottle::updateFunction(int fn, bool state) {
    if (fn < 0 || fn > FUNCTION_BOOLEAN_ARRAY.length()-1) {
        log->warn(tr("Unhandled update function number: %1 %2").arg(fn).arg(this->metaObject()->className()));
        return;
    }
    bool old = FUNCTION_BOOLEAN_ARRAY[fn];
    FUNCTION_BOOLEAN_ARRAY[fn] = state;
//    firePropertyChange(Throttle::getFunctionString(fn), old, state);
}

/**
 * Update the Momentary state of a single function.
 * Updates function value and ChangeListener.
 * Does not send outward message TO hardware.
 *
 * @param fn    Momentary Function Number 0-28
 * @param state On - True, Off - False
 */
/*public*/ void AbstractThrottle::updateFunctionMomentary(int fn, bool state) {
    if (fn < 0 || fn > FUNCTION_MOMENTARY_BOOLEAN_ARRAY.length()-1) {
        log->warn(tr("Unhandled update momentary function number: $1").arg(fn));
        return;
    }
    bool old = FUNCTION_MOMENTARY_BOOLEAN_ARRAY[fn];
    FUNCTION_MOMENTARY_BOOLEAN_ARRAY[fn] = state;
//    firePropertyChange(Throttle::getFunctionMomentaryString(fn), old, state);
}

/**
 * Send the message to set the state of
 * functions F0, F1, F2, F3, F4.
 * <P>
 * This is used in the setFn implementations provided in this class,
 * but a real implementation needs to be provided.
 */
/*protected*/ void AbstractThrottle::sendFunctionGroup1() {
    Logger::error("sendFunctionGroup1 needs to be implemented if invoked");
}

/**
 * Send the message to set the state of
 * functions F5, F6, F7, F8.
 * <P>
 * This is used in the setFn implementations provided in this class,
 * but a real implementation needs to be provided.
 */
/*protected*/ void AbstractThrottle::sendFunctionGroup2() {
    Logger::error("sendFunctionGroup2 needs to be implemented if invoked");
}

/**
 * Send the message to set the state of
 * functions F9, F10, F11, F12
 * <P>
 * This is used in the setFn implementations provided in this class,
 * but a real implementation needs to be provided.
 */
/*protected*/ void AbstractThrottle::sendFunctionGroup3() {
    Logger::error("sendFunctionGroup3 needs to be implemented if invoked");
}

/**
 * Send the message to set the state of
 * functions F13, F14, F15, F16, F17, F18, F19, F20
 * <P>
 * This is used in the setFn implementations provided in this class,
 * but a real implementation needs to be provided.
 */
/*protected*/ void AbstractThrottle::sendFunctionGroup4()
{
    DccLocoAddress* a = (DccLocoAddress*) getLocoAddress();
    QByteArray result = NmraPacket::function13Through20Packet(
            a->getNumber(), a->isLongAddress(),
            getF13(), getF14(), getF15(), getF16(),
            getF17(), getF18(), getF19(), getF20());

    //if the result returns as nullptr, we should quit.
    if (result.isNull())
        return;
    CommandStation* c;
    if((adapterMemo!=nullptr) && (adapterMemo->get("CommandStation")!=nullptr))
        c = (CommandStation*)adapterMemo->get("CommandStation");
    else
        c = (CommandStation*)InstanceManager::getDefault("CommandStation");

    // send it 3 times
    if (c != nullptr)
        c->sendPacket(result,3);
    else
        Logger::error("Can't send F13-F20 since no command station defined");
    return;
}

/**
 * Send the message to set the state of
 * functions F21, F22, F23, F24, F25, F26, F27, F28
 * <P>
 * This is used in the setFn implementations provided in this class,
 * but a real implementation needs to be provided.
 */
/*protected*/ void AbstractThrottle::sendFunctionGroup5()
{
    DccLocoAddress* a = (DccLocoAddress*) getLocoAddress();
    QByteArray result = NmraPacket::function21Through28Packet(
            a->getNumber(), a->isLongAddress(),
            getF21(), getF22(), getF23(), getF24(),
            getF25(), getF26(), getF27(), getF28());
    //if the result returns as nullptr, we should quit.
    if (result.isNull())
        return;
    CommandStation* c;
    if((adapterMemo!=nullptr) && (adapterMemo->get("CommandStation")!=nullptr))
        c = (CommandStation*)adapterMemo->get("CommandStation");
    else
        c = (CommandStation*)InstanceManager::getDefault("CommandStation");

    // send it 3 times
    if (c != nullptr)
        c->sendPacket(result,3);
    else
        Logger::error("Can't send F21-F28 since no command station defined");
    return;
}


// function momentary status  - note that we use the naming for DCC,
// though that's not the implication;
// see also DccThrottle interface
/*public*/ void AbstractThrottle::setF0Momentary(bool f0Momentary) {
    bool old = this->f0Momentary;
    this->f0Momentary = f0Momentary;
    sendMomentaryFunctionGroup1();
    if (old != this->f0Momentary)
        notifyPropertyChangeListener(Throttle::F0Momentary, old, this->f0Momentary );
}

/*public*/ void AbstractThrottle::setF1Momentary(bool f1Momentary) {
    bool old = this->f1Momentary;
    this->f1Momentary = f1Momentary;
    sendMomentaryFunctionGroup1();
    if (old != this->f1Momentary)
        notifyPropertyChangeListener(Throttle::F1Momentary, old, this->f1Momentary );
}

/*public*/ void AbstractThrottle::setF2Momentary(bool f2Momentary) {
    bool old = this->f2Momentary;
    this->f2Momentary = f2Momentary;
    sendMomentaryFunctionGroup1();
    if (old != this->f2Momentary)
        notifyPropertyChangeListener(Throttle::F2Momentary, old, this->f2Momentary );
}

/*public*/ void AbstractThrottle::setF3Momentary(bool f3Momentary) {
    bool old = this->f3Momentary;
    this->f3Momentary = f3Momentary;
    sendMomentaryFunctionGroup1();
    if (old != this->f3Momentary)
        notifyPropertyChangeListener(Throttle::F3Momentary, old, this->f3Momentary );
}

/*public*/ void AbstractThrottle::setF4Momentary(bool f4Momentary) {
    bool old = this->f4Momentary;
    this->f4Momentary = f4Momentary;
    sendMomentaryFunctionGroup1();
    if (old != this->f4Momentary)
        notifyPropertyChangeListener(Throttle::F4Momentary, old, this->f4Momentary );
}

/*public*/ void AbstractThrottle::setF5Momentary(bool f5Momentary) {
    bool old = this->f5Momentary;
    this->f5Momentary = f5Momentary;
    sendMomentaryFunctionGroup2();
    if (old != this->f5Momentary)
        notifyPropertyChangeListener(Throttle::F5Momentary, old, this->f5Momentary );
}

/*public*/ void AbstractThrottle::setF6Momentary(bool f6Momentary) {
    bool old = this->f6Momentary;
    this->f6Momentary = f6Momentary;
    sendMomentaryFunctionGroup2();
    if (old != this->f6Momentary)
        notifyPropertyChangeListener(Throttle::F6Momentary, old, this->f6Momentary );
}

/*public*/ void AbstractThrottle::setF7Momentary(bool f7Momentary) {
    bool old = this->f7Momentary;
    this->f7Momentary = f7Momentary;
    sendMomentaryFunctionGroup2();
    if (old != this->f7Momentary)
        notifyPropertyChangeListener(Throttle::F7Momentary, old, this->f7Momentary );
}

/*public*/ void AbstractThrottle::setF8Momentary(bool f8Momentary) {
    bool old = this->f8Momentary;
    this->f8Momentary = f8Momentary;
    sendMomentaryFunctionGroup2();
    if (old != this->f8Momentary)
        notifyPropertyChangeListener(Throttle::F8Momentary, old, this->f8Momentary );
}

/*public*/ void AbstractThrottle::setF9Momentary(bool f9Momentary) {
    bool old = this->f9Momentary;
    this->f9Momentary = f9Momentary;
    sendMomentaryFunctionGroup3();
    if (old != this->f9Momentary)
        notifyPropertyChangeListener(Throttle::F9Momentary, old, this->f9Momentary );
}

/*public*/ void AbstractThrottle::setF10Momentary(bool f10Momentary) {
    bool old = this->f10Momentary;
    this->f10Momentary = f10Momentary;
    sendMomentaryFunctionGroup3();
    if (old != this->f10Momentary)
        notifyPropertyChangeListener(Throttle::F10Momentary, old, this->f10Momentary );
}

/*public*/ void AbstractThrottle::setF11Momentary(bool f11Momentary) {
    bool old = this->f11Momentary;
    this->f11Momentary = f11Momentary;
    sendMomentaryFunctionGroup3();
    if (old != this->f11Momentary)
        notifyPropertyChangeListener(Throttle::F11Momentary, old, this->f11Momentary );
}

/*public*/ void AbstractThrottle::setF12Momentary(bool f12Momentary) {
    bool old = this->f12Momentary;
    this->f12Momentary = f12Momentary;
    sendMomentaryFunctionGroup3();
    if (old != this->f12Momentary)
        notifyPropertyChangeListener(Throttle::F12Momentary, old, this->f12Momentary );
}

/*public*/ void AbstractThrottle::setF13Momentary(bool f13Momentary) {
    bool old = this->f13Momentary;
    this->f13Momentary = f13Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f13Momentary)
        notifyPropertyChangeListener(Throttle::F13Momentary, old, this->f13Momentary );
}

/*public*/ void AbstractThrottle::setF14Momentary(bool f14Momentary) {
    bool old = this->f14Momentary;
    this->f14Momentary = f14Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f14Momentary)
        notifyPropertyChangeListener(Throttle::F14Momentary, old, this->f14Momentary );
}

/*public*/ void AbstractThrottle::setF15Momentary(bool f15Momentary) {
    bool old = this->f15Momentary;
    this->f15Momentary = f15Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f15Momentary)
        notifyPropertyChangeListener(Throttle::F15Momentary, old, this->f15Momentary );
}

/*public*/ void AbstractThrottle::setF16Momentary(bool f16Momentary) {
    bool old = this->f16Momentary;
    this->f16Momentary = f16Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f16Momentary)
        notifyPropertyChangeListener(Throttle::F16Momentary, old, this->f16Momentary );
}

/*public*/ void AbstractThrottle::setF17Momentary(bool f17Momentary) {
    bool old = this->f17Momentary;
    this->f17Momentary = f17Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f17Momentary)
        notifyPropertyChangeListener(Throttle::F17Momentary, old, this->f17Momentary );
}

/*public*/ void AbstractThrottle::setF18Momentary(bool f18Momentary) {
    bool old = this->f18Momentary;
    this->f18Momentary = f18Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f18Momentary)
        notifyPropertyChangeListener(Throttle::F18Momentary, old, this->f18Momentary );
}

/*public*/ void AbstractThrottle::setF19Momentary(bool f19Momentary) {
    bool old = this->f19Momentary;
    this->f19Momentary = f19Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f19Momentary)
        notifyPropertyChangeListener(Throttle::F19Momentary, old, this->f19Momentary );
}

/*public*/ void AbstractThrottle::setF20Momentary(bool f20Momentary) {
    bool old = this->f20Momentary;
    this->f20Momentary = f20Momentary;
    sendMomentaryFunctionGroup4();
    if (old != this->f20Momentary)
        notifyPropertyChangeListener(Throttle::F20Momentary, old, this->f20Momentary );
}

/*public*/ void AbstractThrottle::setF21Momentary(bool f21Momentary) {
    bool old = this->f21Momentary;
    this->f21Momentary = f21Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f21Momentary)
        notifyPropertyChangeListener(Throttle::F21Momentary, old, this->f21Momentary );
}

/*public*/ void AbstractThrottle::setF22Momentary(bool f22Momentary) {
    bool old = this->f22Momentary;
    this->f22Momentary = f22Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f22Momentary)
        notifyPropertyChangeListener(Throttle::F22Momentary, old, this->f22Momentary );
}

/*public*/ void AbstractThrottle::setF23Momentary(bool f23Momentary) {
    bool old = this->f23Momentary;
    this->f23Momentary = f23Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f23Momentary)
        notifyPropertyChangeListener(Throttle::F23Momentary, old, this->f23Momentary );
}

/*public*/ void AbstractThrottle::setF24Momentary(bool f24Momentary) {
    bool old = this->f24Momentary;
    this->f24Momentary = f24Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f24Momentary)
        notifyPropertyChangeListener(Throttle::F24Momentary, old, this->f24Momentary );
}

/*public*/ void AbstractThrottle::setF25Momentary(bool f25Momentary) {
    bool old = this->f25Momentary;
    this->f25Momentary = f25Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f25Momentary)
        notifyPropertyChangeListener(Throttle::F25Momentary, old, this->f25Momentary );
}

/*public*/ void AbstractThrottle::setF26Momentary(bool f26Momentary) {
    bool old = this->f26Momentary;
    this->f26Momentary = f26Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f26Momentary)
        notifyPropertyChangeListener(Throttle::F26Momentary, old, this->f26Momentary );
}

/*public*/ void AbstractThrottle::setF27Momentary(bool f27Momentary) {
    bool old = this->f27Momentary;
    this->f27Momentary = f27Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f27Momentary)
        notifyPropertyChangeListener(Throttle::F27Momentary, old, this->f27Momentary );
}

/*public*/ void AbstractThrottle::setF28Momentary(bool f28Momentary) {
    bool old = this->f28Momentary;
    this->f28Momentary = f28Momentary;
    sendMomentaryFunctionGroup5();
    if (old != this->f28Momentary)
        notifyPropertyChangeListener(Throttle::F28Momentary, old, this->f28Momentary );
}

/**
 * Sets Momentary Function and sends to layout.
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractThrottle::setFunctionMomentary(int momFuncNum, bool state){
    if (momFuncNum < 0 || momFuncNum > FUNCTION_MOMENTARY_BOOLEAN_ARRAY.length()-1) {
        log->warn(tr("Unhandled set momentary function number: %1").arg(momFuncNum));
        return;
    }
    bool old = FUNCTION_MOMENTARY_BOOLEAN_ARRAY[momFuncNum];
    FUNCTION_MOMENTARY_BOOLEAN_ARRAY[momFuncNum] = state;
    sendFunctionGroup(momFuncNum,true);
//    firePropertyChange(Throttle::getFunctionMomentaryString(momFuncNum), old, state);
}

/**
 * Send the message to set the momentary state of
 * functions F0, F1, F2, F3, F4.
 * <P>
 * This is used in the setFnMomentary implementations provided in this
 * class, a real implementation needs to be provided if the
 * hardware supports setting functions momentary.
 */
/*protected*/ void AbstractThrottle::sendMomentaryFunctionGroup1() {
}

/**
 * Send the message to set the momentary state of
 * functions F5, F6, F7, F8.
 * <P>
 * This is used in the setFnMomentary implementations provided in this
 * class, but a real implementation needs to be provided if the
 * hardware supports setting functions momentary.
 */
/*protected*/ void AbstractThrottle::sendMomentaryFunctionGroup2() {
}

/**
 * Send the message to set the Momentary state of
 * functions F9, F10, F11, F12
 * <P>
 * This is used in the setFnMomentary implementations provided in this
 * class, but a real implementation needs to be provided if the
 * hardware supports setting functions momentary.
 */
/*protected*/ void AbstractThrottle::sendMomentaryFunctionGroup3() {
}

/**
 * Send the message to set the Momentary state of
 * functions F13, F14, F15, F16, F17, F18, F19, F20
 * <P>
 * This is used in the setFnMomentary implementations provided in this
 * class, but a real implementation needs to be provided if the
 * hardware supports setting functions momentary.
 */
/*protected*/ void AbstractThrottle::sendMomentaryFunctionGroup4() {
 }


/**
 * Send the message to set the Momentary state of
 * functions F21, F22, F23, F24, F25, F26, F27, F28
 * <P>
 * This is used in the setFnMomentary implementations provided in this
 * class, but a real implementation needs to be provided if the
 * hardware supports setting functions momentary.
 */
/*protected*/ void AbstractThrottle::sendMomentaryFunctionGroup5() {
}


/*
 * setSpeedStepMode - set the speed step value and the related
 *                    speedIncrement value.
 * <P>
 * specific implementations should override this function
 * <P>
 * @param Mode - the current speed step mode - default should be 128
 *              speed step mode in most cases
 */
/*public*/ void AbstractThrottle::setSpeedStepMode(SpeedStepMode::SSMODES newMode) {
 log->debug(tr("Speed Step Mode Change from:%1 to Mode:%2").arg(this->speedStepMode).arg(newMode));
 if (speedStepMode != newMode) {
     notifyPropertyChangeListener("SpeedSteps", this->speedStepMode, newMode);
     this->speedStepMode = newMode;
 }
}

/*
 * getSpeedStepMode - get the current speed step value.
 * <P>
 */
 /*public*/ SpeedStepMode::SSMODES AbstractThrottle::getSpeedStepMode() {
    return speedStepMode;
 }

/*protected*/ void AbstractThrottle::record(float speed){
    if(re==nullptr)
        return;
    if(speed==0){
        stopClock();
    } else {
        startClock();
    }
}
/*protected*/ void AbstractThrottle::startClock()
{
 if(start==0)
  start = /*System.currentTimeMillis()*/ QDateTime::currentDateTime().toMSecsSinceEpoch();
}

void AbstractThrottle::stopClock() {
    if(start==0)
        return;
    qint64 stop = /*System.currentTimeMillis()*/QDateTime::currentDateTime().toMSecsSinceEpoch();;
    //Set running duration in seconds
    durationRunning = durationRunning + ((stop-start)/1000);
    start=0;
}

/*protected*/ void AbstractThrottle::finishRecord()
{
 if(re==nullptr)
 {
  return;
 }
 stopClock();
 QString currentDurationString = re->getAttribute("OperatingDuration");
 long currentDuration = 0;
// try
// {
  bool bOk = false;
  currentDuration = currentDurationString.toInt(&bOk);
  if(!bOk) //throw new Exception();
// }
// catch (Exception e)
 {
  log->warn("current stored duration is not a valid number \"" + currentDurationString +" \"");
 }
 currentDuration = currentDuration + durationRunning;
 re->putAttribute("OperatingDuration", QString::number(currentDuration));
 QDate date = QDate();
 re->putAttribute("LastOperated", date.toString("yyyy/MM/dd"));
 //Only store if the roster entry isn't open.
 if(!re->isOpen())
     re->store();
 else
     log->warn("Roster Entry " + re->getId() + " running time not saved as entry is already open for editing");
 re=nullptr;
}


 /*public*/ void AbstractThrottle::setRosterEntry(BasicRosterEntry* re){
    this->re = re;
 }

 /*public*/ BasicRosterEntry* AbstractThrottle::getRosterEntry(){
    return re;
 }

/*protected*/ int AbstractThrottle::intSpeed(float speed) {
    return this->intSpeed(speed, 127);
}                                       // non-stop values in 128 speed

/**
 * Get an integer speed for the given raw speed value.
 *
 * @param speed the speed as a percentage of maximum possible speed.
 *              Negative values indicate a need for an emergency stop.
 * @param steps number of possible speeds. Values less than 2 will cause
 *              errors.
 * @return an integer in the range 0-steps
 */
/*protected*/ int AbstractThrottle::intSpeed(float speed, int steps) {
    // test that speed is < 0 for emergency stop since calculation of
    // value returns 0 for some values of -1 < rawSpeed < 0
    if (speed < 0) {
        return 1; // emergency stop
    }
    // since Emergency Stop (estop) is speed 1, and a negative speed
    // is used for estop, subtract 1 from steps to avoid the estop
    // Use ceil() to prevent smaller positive values from being 0
    int value = (int) qCeil((steps - 1) * speed);
    if (value < 0) {
        // if we get here, something is wrong and needs to be reported.
        Exception ex =  Exception("Error calculating speed. Please send logs to the JMRI developers.");
        log->error(ex.getMessage(), ex);
        return 1;
    } else if (value >= steps) {
        return steps; // maximum possible speed
    } else if (value > 0) {
        return value + 1; // add 1 to the value to avoid the estop
    } else {
        return 0; // non-emergency stop
    }
}
//    // initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractThrottle.class.getName());

//}
