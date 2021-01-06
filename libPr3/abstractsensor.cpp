#include "abstractsensor.h"
#include "instancemanager.h"
#include <QThread>

AbstractSensor::AbstractSensor(QObject *parent) :
    Sensor(parent)
{
}
/**
 * Abstract class providing the basic logic of the Sensor interface
 * <p>
 * Sensor system names are always upper case.
 *
 * @author			Bob Jacobsen Copyright (C) 2001, 2009
 * @version         $Revision: 20843 $
 */
//public abstract class AbstractSensor extends AbstractNamedBean implements Sensor, java.io.Serializable {

// ctor takes a system-name string for initialization
AbstractSensor::AbstractSensor(QString systemName, QObject *parent)
    : Sensor(systemName.toUpper(), parent)
{
 //super(systemName.toUpperCase());
 sensorDebounceGoingActive = 0L;
 sensorDebounceGoingInActive = 0L;
 _useDefaultTimerSettings = false;
 restartcount = 0;
 _inverted = false;

 // internal data members
 _knownState     = UNKNOWN;
 _rawState       = UNKNOWN;
 reporter = NULL;
 lastKnownState = _knownState;
 thr = NULL;
}

AbstractSensor::AbstractSensor(QString systemName, QString userName, QObject *parent)
 : Sensor(systemName, userName, parent)
{
  //super(systemName.toUpperCase(), userName);
  sensorDebounceGoingActive = 0L;
  sensorDebounceGoingInActive = 0L;
  _useDefaultTimerSettings = false;
  restartcount = 0;
  _inverted = false;

  // internal data members
  _knownState     = UNKNOWN;
  _rawState       = UNKNOWN;
  reporter = NULL;
  lastKnownState = _knownState;
  thr = NULL;
}

//@Override
/*public*/ QString AbstractSensor::getBeanType() {
    return tr("Sensor");
}

//@Override
//@CheckReturnValue
/*public*/ QString AbstractSensor::describeState(int state) {
    switch (state) {
        case ACTIVE:
            return tr("Active");
        case INACTIVE:
            return tr("Inactive");
        default:
            return AbstractNamedBean::describeState(state);
    }
}

// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
//		public void firePropertyChange(QString propertyName,
//					       Object oldValue,
//					       Object newValue)
// _once_ if anything has changed state

int AbstractSensor::getKnownState() const  {return _knownState;}

void AbstractSensor::setSensorDebounceGoingActiveTimer(long time) const
{
 if(sensorDebounceGoingActive == time)
  return;
 qint32 oldValue = sensorDebounceGoingActive;
 sensorDebounceGoingActive = time;
 firePropertyChange("ActiveTimer", QVariant(oldValue), QVariant((qint32)sensorDebounceGoingActive));
}

long AbstractSensor::getSensorDebounceGoingActiveTimer() const
{ return sensorDebounceGoingActive; }

void AbstractSensor::setSensorDebounceGoingInActiveTimer(long time)
{
 if(sensorDebounceGoingInActive == time)
  return;
 qint32 oldValue = sensorDebounceGoingInActive;
 sensorDebounceGoingInActive = time;
 firePropertyChange("InActiveTimer", oldValue,  QVariant((qint32)sensorDebounceGoingActive));
}

long AbstractSensor::getSensorDebounceGoingInActiveTimer() const
{ return sensorDebounceGoingInActive; }

//@Override
/*public*/ void AbstractSensor::setUseDefaultTimerSettings(bool boo) {
    if (boo == _useDefaultTimerSettings) {
        return;
    }
    _useDefaultTimerSettings = boo;
    if (_useDefaultTimerSettings) {
        sensorDebounceGoingActive = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getDefaultSensorDebounceGoingActive();
        sensorDebounceGoingInActive = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getDefaultSensorDebounceGoingInActive();
    }
    firePropertyChange("GlobalTimer", !boo, boo);
}

//@Override
/*public*/ bool AbstractSensor::getUseDefaultTimerSettings() {
    return _useDefaultTimerSettings;
}

void AbstractSensor::useDefaultTimerSettings(bool boo)
{
 if(boo==_useDefaultTimerSettings)
  return;
 _useDefaultTimerSettings = boo;
 if(_useDefaultTimerSettings)
 {
  sensorDebounceGoingActive = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getDefaultSensorDebounceGoingActive();
  sensorDebounceGoingInActive = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getDefaultSensorDebounceGoingInActive();
 }
 firePropertyChange("GlobalTimer", !boo, boo);
}

bool AbstractSensor::useDefaultTimerSettings() { return _useDefaultTimerSettings; }

/*
 * Before going active or inactive or checking that we can go active, we will wait 500ms
 * for things to settle down to help prevent a race condition
 */
void AbstractSensor::sensorDebounce()
{
//    /*final*/ int lastKnownState = _knownState;
    // TODO:
//        r = new Runnable() {
//            void run() {
//                try {
//                    long sensorDebounceTimer = sensorDebounceGoingInActive;
//                    if(_rawState==ACTIVE)
//                        sensorDebounceTimer = sensorDebounceGoingActive;
//                    QThread.sleep(sensorDebounceTimer);
//                    restartcount=0;
//                    _knownState=_rawState;
//                    firePropertyChange("KnownState", Integer.valueOf(lastKnownState), Integer.valueOf(_knownState));

//                } catch (InterruptedException ex) {
//                    restartcount ++;
//                }
//            }
//        };
    r = new ASRunnable(this);
    thr = new QThread(r);
    thr->start();
}

// setKnownState() for implementations that can't
// actually do it on the layout. Not intended for use by implementations
// that can
void AbstractSensor::setKnownState(int s)// throws jmri.JmriException
{
 setOwnState(s);
}


/**
 * Set our internal state information, and notify bean listeners.
 */
void AbstractSensor::setOwnState(int s)
{
 if (_rawState != s)
 {
  if(((s==Sensor::ACTIVE) && (sensorDebounceGoingActive > 0)) ||
            ((s==Sensor::INACTIVE) && (sensorDebounceGoingInActive > 0)))
  {
   int oldRawState = _rawState;
   _rawState = s;
   if (thr!=nullptr)
   {
    try {
//TODO:                        thr.interrupt();
     thr->exit();
    } catch (Exception ie)
    {
     //Can be considered normal.
    }
   }

   if((restartcount != 0) && (restartcount % 10 == 0))
   {
    log.warn(tr("Sensor \"%1\" state keeps flapping: %2").arg(getDisplayName()).arg(restartcount));
   }
   firePropertyChange("RawState", QVariant(oldRawState), QVariant(s));
   sensorDebounce();
   return;
  }
  else
  {
   //we shall try to stop the thread as one of the state changes
   //might start the thread, while the other may not.
   if(thr!=nullptr)
   {
    try
    {
     thr->exit();
    } catch (Exception ie)
    {
     //Can be considered normal.
    }
   }
   _rawState=s;
  }
 }
 if (_knownState != s)
 {
  int oldState = _knownState;
  _knownState = s;
  firePropertyChange("KnownState", QVariant(oldState), QVariant(_knownState));
 }
}

int AbstractSensor::getRawState() const
{
    return _rawState;
}

/**
 * Implement a shorter name for setKnownState.
 *<P>
 * This generally shouldn't be used by Java code; use
 * setKnownState instead.  The is provided to make Jython
 * script access easier to read.
 */
void AbstractSensor::setState(int s) //throws jmri.JmriException
{ setKnownState(s); }

/**
 * Implement a shorter name for getKnownState.
 *<P>
 * This generally shouldn't be used by Java code; use
 * getKnownState instead.  The is provided to make Jython
 * script access easier to read.
 */
int AbstractSensor::getState() { return getKnownState(); }

/**
 * Control whether the actual sensor input is
 * considered to be inverted, e.g. the normal
 * electrical signal that results in an ACTIVE state
 * now results in an INACTIVE state.
 */
void AbstractSensor::setInverted(bool inverted)
{
 bool oldInverted = _inverted;
 _inverted = inverted;
 if (oldInverted != _inverted)
 {
  firePropertyChange("inverted", QVariant(oldInverted), QVariant(_inverted));
  int state = _knownState;
  if (state == Sensor::ACTIVE)
  {
   setOwnState(Sensor::INACTIVE);
  } else if (state == Sensor::INACTIVE)
  {
   setOwnState(Sensor::ACTIVE);
  }
 }
}

/**
 * Get the inverted state.  If true, the
 * electrical signal that results in an ACTIVE state
 * now results in an INACTIVE state.
 * <P>
 * Used in polling loops in system-specific code,
 * so made final to allow optimization.
 */
/*final public */bool AbstractSensor::getInverted() const { return _inverted; }


/**
 * By default, all implementations based on this can invert
 */
//@Override
/*public*/ bool AbstractSensor::canInvert() { return true; }

/**
 * Some sensor boards also serve the function of being able to report
 * back train identities via such methods as RailCom.
 * The setting and creation of the reporter against the sensor should be
 * done when the sensor is created.  This information is not saved.
 * <p>
 * returns NULL if there is no direct reporter.
 */
void AbstractSensor::setReporter(Reporter* er){
    reporter = er;
}

Reporter* AbstractSensor::getReporter() const{
    return reporter;
}

/**
 * Set the pull resistance
 * <p>
 * In this default implementation, the input value is ignored.
 *
 * @param r PullResistance value to use.
 */
//@Override
/*public*/ void AbstractSensor::setPullResistance(Sensor::PullResistance r){
}

/**
 * Get the pull resistance.
 *
 * @return the currently set PullResistance value.  In this default
 * implementation, PullResistance.PULL_OFF is always returned.
 */
//@Override
/*public*/ Sensor::PullResistance::PULLRESISTANCE AbstractSensor::getPullResistance(){
   return Sensor::PullResistance::PULL_OFF;
}

ASRunnable::ASRunnable(QObject *as) : Runnable(as)
{
 this->as = as;
}

void ASRunnable::run()
{
 try
 {
  long sensorDebounceTimer = ((AbstractSensor*)as)->sensorDebounceGoingInActive;
  if(((AbstractSensor*)as)->_rawState==Sensor::ACTIVE)
      sensorDebounceTimer = ((AbstractSensor*)as)->sensorDebounceGoingActive;
  sleep(sensorDebounceTimer);
  restartcount=0;
  ((AbstractSensor*)as)->_knownState=((AbstractSensor*)as)->_rawState;
  ((AbstractSensor*)as)->firePropertyChange("KnownState", (((AbstractSensor*)as)->lastKnownState), (((AbstractSensor*)as)->_knownState));
 }
 catch (InterruptedException ex)
 {
  restartcount ++;
 }
//                }
}
QString AbstractSensor::getStateName(int state)
{
 switch(state)
 {
 case Sensor::ACTIVE:
     return tr("Active");
 case Sensor::INACTIVE:
     return tr("Inactive");
 case Sensor::INCONSISTENT:
     return tr("Inconsistent");
 default:
 case Sensor::UNKNOWN:
     return tr("Unknown");
 }
}
