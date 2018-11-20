#include "simpletimebase.h"
#include "instancemanager.h"
#include "abstractmemorymanager.h"
#include "abstractmemory.h"
#include "proxysensormanager.h"
#include "abstractsensor.h"
//#include "../LayoutEditor/nixieclockframe.h"
//#include "../LayoutEditor/lcdclockframe.h"
//#include "../LayoutEditor/analogclock2display.h"
#include "defaultclockcontrol.h"

//SimpleTimebase::SimpleTimebase(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Provide basic Timebase implementation from system clock.
 * <P>
 * This implementation provides for the internal clock and for one hardware clock.
 * A number of hooks and comments are provided below for implementing multiple hardware clocks
 * should that ever be done.
 * <P>
 * The setTimeValue member is the fast time when the clock
 * started.  The startAtTime member is the wall-clock time
 * when the clock was started.  Together, those can be used
 * to calculate the current fast time.
 * <P>
 * The pauseTime member is used to indicate that the
 * timebase was paused. If non-NULL, it indicates the
 * current fast time when the clock was paused.
 *
 * @author			Bob Jacobsen Copyright (C) 2004, 2007
 *                  Dave Duchamp - 2007 additions/revisions for handling one hardware clock
 * @version			$Revision: 21910 $
 */
//public class SimpleTimebase extends jmri.implementation.AbstractNamedBean implements Timebase

/*public*/ SimpleTimebase::SimpleTimebase(QObject* parent) : Timebase(QString("SIMPLECLOCK"), parent)
{
//super("SIMPLECLOCK");
 setProperty("JavaClassName", "jmri.jmrit.simpleclock.SimpleTimebase");

 log = new Logger("SimpleTimebase");
 mFactor = 1.0;  // this is the rate factor for the JMRI fast clock
 hardwareFactor = 1.0;  // this is the rate factor for the hardware clock
    //  The above is necessary to support hardware clock Time Sources that fiddle with mFactor to
    //      synchronize, instead of sending over a new time to synchronize.
 clockSensor = NULL;   // active when clock is running, inactive when stopped
 clockMemory = NULL;   // contains current time on each tick
 factorMemory = NULL;  // contains the rate factor for the fast clock

 internalMaster = true;     // false indicates a hardware clock is the master
 masterName = "";		// name of hardware time source, if not internal master
 hardwareTimeSource = NULL;  // ClockControl instance of hardware time source
 synchronizeWithHardware = false;  // true indicates need to synchronize
 correctHardware = false;    // true indicates hardware correction requested
 display12HourClock = false; // true if 12-hour clock display is requested
 startStopped = false;    // true indicates start up with clock stopped requested
 startSetTime = false;    // true indicates set fast clock to specified time at
                                                            //start up requested
 startTime =  /*QDateTime()*/QDateTime::currentDateTime();	// specified time for setting fast clock at start up
 startAtTime =  /*QDateTime()*/QDateTime::currentDateTime();
 startClockOption = Timebase::NONE;	// request start of a clock at start up
 notInitialized = true;  // true before initialization received from start up
 pauseTime = QDateTime();

//    SimpleDateFormat timeStorageFormat = NULL;

 timer = NULL;
 pcMinutes = new PropertyChangeSupport(this);
 oldMinutes = 0;
 pcs = new PropertyChangeSupport(this);
 // initialize time-containing memory
 try
 {
  clockMemory = InstanceManager::memoryManagerInstance()->provideMemory("IMCURRENTTIME");
  clockMemory->setValue("--");
  clockMemory->setObjectName("clockMemory");
 }
 catch (IllegalArgumentException ex) {
  log->warn("Unable to create IMCURRENTTIME time memory variable");
 }
 // set to start counting from now
 setTime( QDateTime::currentDateTime());
 pauseTime = QDateTime();
 // initialize start/stop sensor for time running
 try
 {
  clockSensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor("ISCLOCKRUNNING");
  clockSensor->setKnownState(Sensor::ACTIVE);
//     clockSensor.addPropertyChangeListener(
//             new PropertyChangeListener() {
//                 @Override
//                 public void propertyChange(PropertyChangeEvent e) {
//                     clockSensorChanged();
//                 }
//             });
  connect(clockSensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(onPropertyChange(PropertyChangeEvent*)));
 }
 catch (JmriException e)
 {
  log->warn("Exception setting ISCLOCKRUNNING sensor ACTIVE: " + e.getMessage());
 }
 // initialize rate factor-containing memory
 if (InstanceManager::getNullableDefault("MemoryManager") != NULL)
 {
  // only try to create memory if memories are supported
  try
  {
   factorMemory = InstanceManager::memoryManagerInstance()->provideMemory("IMRATEFACTOR");
   factorMemory->setValue(userGetRate());
  }
  catch (IllegalArgumentException ex)
  {
   log->warn("Unable to create IMRATEFACTOR time memory variable");
  }
 }
}

SimpleTimebase::~SimpleTimebase()
{
 delete log;
}

// methods for getting and setting the current Fast Clock time
/*public*/ QDateTime SimpleTimebase::getTime()
{
 // is clock stopped?
 if (!pauseTime.isNull()) return QDateTime(pauseTime); // to ensure not modified outside
 // clock running
 qint64 elapsedMSec = ( QDateTime::currentDateTime().toMSecsSinceEpoch() - startAtTime.toMSecsSinceEpoch());
 qint64 nowMSec = setTimeValue.toMSecsSinceEpoch()+(long)(mFactor*elapsedMSec);
 // return  QDateTime(nowMSec);
 return QDateTime::fromMSecsSinceEpoch(nowMSec);
}
/*public*/ void SimpleTimebase::setTime(QDateTime d)
{
 startAtTime =  QDateTime::currentDateTime();	// set now in wall clock time
 setTimeValue =  QDateTime(d);   // to ensure not modified from outside
 if (synchronizeWithHardware)
 {
  // send new time to all hardware clocks, except the hardware time source if there is one
  // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
  if (((ClockControl*)InstanceManager::getDefault("ClockControl"))!=hardwareTimeSource)
  {
   ((ClockControl*)InstanceManager::getDefault("ClockControl"))->setTime(d);
  }
 }
 if (!pauseTime.isNull())
  pauseTime = setTimeValue;  // if stopped, continue stopped at new time
 handleAlarm();
}
/*public*/ void SimpleTimebase::userSetTime(QDateTime d)
{
 // this call only results from user changing fast clock time in Setup Fast Clock
 startAtTime =  QDateTime();	// set now in wall clock time
 setTimeValue =  QDateTime(d);   // to ensure not modified from outside
 if (synchronizeWithHardware)
 {
  // send new time to all hardware clocks, including the hardware time source if there is one
  // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
  ((ClockControl*)InstanceManager::getDefault("ClockControl"))->setTime(d);
 }
 else if (!internalMaster && (hardwareTimeSource!=NULL))
 {
  // if not synchronizing, send to the hardware time source if there is one
   hardwareTimeSource->setTime(d);
 }
 if (!pauseTime.isNull())
  pauseTime = setTimeValue;  // if stopped, continue stopped at new time
 handleAlarm();
}

// methods for starting and stopping the Fast Clock and returning status
/*public*/ void SimpleTimebase::setRun(bool run)
{
 if (run && !pauseTime.isNull())
 {
  // starting of stopped clock
  setTime(pauseTime);
  if (synchronizeWithHardware)
  {
   // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
   ((ClockControl*)InstanceManager::getDefault("ClockControl"))->startHardwareClock(getTime());
  }
  else if (!internalMaster && hardwareTimeSource!=NULL)
  {
   hardwareTimeSource->startHardwareClock(getTime());
  }
  pauseTime = QDateTime();
  if (clockSensor!=NULL)
  {
   try {
    ((AbstractSensor*)clockSensor)->setKnownState(Sensor::ACTIVE);
   }
   catch (JmriException e)
   {
    log->warn("Exception setting ISClockRunning sensor ACTIVE: "+e.getMessage());
   }
  }
 }
 else if (!run && pauseTime.isNull())
 {
  // stopping of running clock:
  // Store time it was stopped, and stop it
  pauseTime = getTime();
  if (synchronizeWithHardware)
  {
   // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
            ((ClockControl*)InstanceManager::getDefault("ClockControl"))->stopHardwareClock();
        }
        else if (!internalMaster && hardwareTimeSource!=NULL) {
            hardwareTimeSource->stopHardwareClock();
        }
        if (clockSensor!=NULL) {
            try {
                ((AbstractSensor*)clockSensor)->setKnownState(Sensor::INACTIVE);
            } catch (JmriException e) {
                log->warn("Exception setting ISClockRunning sensor INACTIVE: "+e.getMessage());
            }
        }
    }
    firePropertyChange("run", QVariant(run), QVariant(!run));
    handleAlarm();
}
/*public*/ bool SimpleTimebase::getRun() { return pauseTime.isNull(); }

// methods for setting and getting rate
/*public*/ void SimpleTimebase::setRate(double factor)
{
 if (factor < 0.1 || factor > 100)
 {
        log->error("rate of "+QString("%1").arg(factor)+" is out of reasonable range, set to 1");
        factor = 1;
    }
    if (internalMaster && (!notInitialized))
        log->error("Probable Error - questionable attempt to change fast clock rate");
    double oldFactor = mFactor;
    QDateTime now = getTime();
    // actually make the change
    mFactor = factor;
    if (internalMaster || notInitialized) hardwareFactor = factor;
    if (internalMaster || (synchronizeWithHardware && notInitialized))
    {
        // send new rate to all hardware clocks, except the hardware time source if there is one
        // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
  if (((ClockControl*)InstanceManager::getDefault("ClockControl"))!=hardwareTimeSource)
  {
   ((ClockControl*)InstanceManager::getDefault("ClockControl"))->setRate(factor);
  }
 }
 // make sure time is right with new rate
 setTime(now);
 // notify listeners if internal master
 if (internalMaster)
 {
  firePropertyChange("rate", QVariant(factor), QVariant(oldFactor));
 }
 handleAlarm();
}

/*public*/ void SimpleTimebase::userSetRate(double factor)
{
 // this call is used when user changes fast clock rate either in Setup Fast Clock or via a ClockControl
 //		implementation
 if (factor < 0.1 || factor > 100)
 {
  log->error("rate of "+QString("%1").arg(factor)+" is out of reasonable range, set to 1");
  factor = 1;
 }
 double oldFactor = hardwareFactor;
 QDateTime now = getTime();
 // actually make the change
    mFactor = factor;
    hardwareFactor = factor;
    if (synchronizeWithHardware)
    {
        // send new rate to all hardware clocks, including the hardware time source if there is one
        // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
        ((ClockControl*)InstanceManager::getDefault("ClockControl"))->setRate(factor);
    }
    else if (!internalMaster  && (hardwareTimeSource!=NULL)) {
        // if not synchronizing, send to the hardware time source if there is one
        hardwareTimeSource->setRate(factor);
    }
    // make sure time is right with new rate
    setTime(now);
    // update memory
    updateMemory(factor);
    // notify listeners
 firePropertyChange("rate", QVariant(factor), QVariant(oldFactor));
 handleAlarm();
}
/*public*/ double SimpleTimebase::getRate() { return mFactor; }
/*public*/ double SimpleTimebase::userGetRate()
{
 if (internalMaster) return mFactor;
 else return hardwareFactor;
}

/*public*/ void SimpleTimebase::setInternalMaster(bool master, bool update)
{
 if (master!=internalMaster)
 {
  internalMaster = master;
  if (internalMaster)
  {
   mFactor = hardwareFactor;  // get rid of any fiddled rate present
   if (update)
   {
    // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
    ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(mFactor, getTime(), false);
   }
  }
  else if (update)
  {
   // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
   ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(hardwareFactor, getTime(), false);
  }

  if (internalMaster)
  {
   masterName = "";
   hardwareTimeSource = NULL;
  }
  else
  {
   // Note if there are multiple hardware clocks, this should be changed to correctly
   //    identify which hardware clock has been chosen-currently assumes only one
   hardwareTimeSource = ((ClockControl*)InstanceManager::getDefault("ClockControl"));
   masterName = hardwareTimeSource->getHardwareClockName();
  }
 }
}
/*public*/ bool SimpleTimebase::getInternalMaster() {return internalMaster;}

/*public*/ void SimpleTimebase::setMasterName(QString name)
{
    if (!internalMaster)
    {
        masterName = name;
        // if multiple clocks, this must be replaced by a loop over all hardware clocks to identify
        // the one that is the hardware time source
        hardwareTimeSource = ((ClockControl*)InstanceManager::getDefault("ClockControl"));
    }
    else {
        masterName = "";
        hardwareTimeSource = NULL;
    }
}
/*public*/ QString SimpleTimebase::getMasterName() {return masterName;}

/*public*/ void SimpleTimebase::setSynchronize(bool synchronize, bool update)
{
 if (synchronizeWithHardware!=synchronize)
 {
  synchronizeWithHardware = synchronize;
  if (update)
  {
   if (internalMaster)
   {
    // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
    ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(mFactor,
                                                getTime(), false);
   }
   else
   {
    // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
    ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(hardwareFactor,
                                                getTime(), false);
   }
  }
 }
}
/*public*/ bool SimpleTimebase::getSynchronize() {return synchronizeWithHardware;}

/*public*/ void SimpleTimebase::setCorrectHardware(bool correct, bool update) {
    if (correctHardware!=correct) {
        correctHardware = correct;
        if (update) {
            if (internalMaster) {
                // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
                ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(mFactor, getTime(), false);
            }
            else {
                // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
                ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(hardwareFactor,
                                                getTime(), false);
            }
        }
    }
}
/*public*/ bool SimpleTimebase::getCorrectHardware() {return correctHardware;}

/*public*/ void SimpleTimebase::set12HourDisplay(bool display, bool update) {
    if (display!=display12HourClock) {
        display12HourClock = display;
        if (update) {
            if (internalMaster) {
                // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
                ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(mFactor,
                                                getTime(), false);
            }
            else {
                // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
                ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(hardwareFactor,
                                                getTime(), false);
            }
        }
    }
}
/*public*/ bool SimpleTimebase::use12HourDisplay() {return display12HourClock;}

/*public*/ void SimpleTimebase::setStartStopped(bool stopped) {
    startStopped = stopped;
}
/*public*/ bool SimpleTimebase::getStartStopped() {return startStopped;}

/*public*/ void SimpleTimebase::setStartSetTime(bool set, QDateTime time) {
    startSetTime = set;
    startTime = time;
}
/*public*/ bool SimpleTimebase::getStartSetTime() {return startSetTime;}

/*public*/ QDateTime SimpleTimebase::getStartTime() {return  startTime;}

/*public*/ void SimpleTimebase::setStartClockOption(int option) {startClockOption = option;}
/*public*/ int SimpleTimebase::getStartClockOption() {return startClockOption;}
// Note the following method should only be invoked at start up
/*public*/ void SimpleTimebase::initializeClock ()
{
// TODO:
 switch (startClockOption)
 {
// case Timebase::NIXIE_CLOCK:
//    NixieClockFrame f =
//                            new NixieClockFrame();
//    f.setVisible(true);
//    break;
// case Timebase::ANALOG_CLOCK:
//    AnalogClockFrame g =
//                            new AnalogClockFrame();
//    g.setVisible(true);
//    break;
// case Timebase::LCD_CLOCK:
//    LcdClockFrame* h = new LcdClockFrame();
//    h->setVisible(true);
//    break;
 }
}

/**
 * Method to initialize hardware clock at start up
 * Note: This method is always called at start up after all options have been set.
 *		It should be ignored if there is no communication with a hardware clock.
 */
/*public*/ void SimpleTimebase::initializeHardwareClock() {
    if (synchronizeWithHardware || correctHardware) {
        if (startStopped) {
            // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
            ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(0,
                    getTime(),(!internalMaster && !startSetTime));
        }
        else {
            // Note if there are multiple hardware clocks, this should be a loop over all hardware clocks
            ((ClockControl*)InstanceManager::getDefault("ClockControl"))->initializeHardwareClock(mFactor,
                    getTime(),(!internalMaster && !startSetTime));
        }
    }
    else if (!internalMaster) {
        if (startStopped) {
            hardwareTimeSource->initializeHardwareClock(0,getTime(),(!startSetTime));
        }
        else {
            hardwareTimeSource->initializeHardwareClock(hardwareFactor,getTime(),(!startSetTime));
        }
    }
    notInitialized = false;
}
/*public*/ bool SimpleTimebase::getIsInitialized() {return (!notInitialized);}

/*protected*/ void SimpleTimebase::firePropertyChange(QString p, QVariant old, QVariant n)
{
 pcs->firePropertyChange(p,old,n);
 emit(propertyChange(new PropertyChangeEvent(this,p, old,n)));
}

/**
 * Handle a change in the clock running sensor
 */
/*private*/ void SimpleTimebase::clockSensorChanged()
{
 if (((AbstractSensor*)clockSensor)->getKnownState() == Sensor::ACTIVE)
 {
  // simply return if clock is already running
  if (pauseTime.isNull()) return;
  setRun(true);
 }
 else
 {
  // simply return if clock is already stopped
  if (!pauseTime.isNull()) return;
  setRun(false);
 }
}

/**
 * Request a call-back when the bound Rate or Run property changes.
 * <P>
 * Not yet implemented.
 */
/*public*/ /*synchronized*/ void SimpleTimebase::addPropertyChangeListener(PropertyChangeListener* l) {
    pcs->addPropertyChangeListener(l);
}

/**
 * Remove a request for a call-back when a bound property changes.
 * <P>
 * Not yet implemented.
 */
/*public*/ /*synchronized*/ void SimpleTimebase::removePropertyChangeListener(PropertyChangeListener* l) {
    pcs->removePropertyChangeListener(l);
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 *
 */
/*public*/ void SimpleTimebase::dispose() {}


/**
 * Start the minute alarm ticking, if it isnt
 * already.
 */
void SimpleTimebase::startAlarm() {
    if (timer == NULL) handleAlarm();
}

/**
 * Handle an "alarm", which is used to count off minutes.
 *<P>
 * Listeners won't be notified if the minute value hasn't changed since the last time.
 */
//@SuppressWarnings("deprecation")
void SimpleTimebase::handleAlarm()
{
 // on first pass, set up the timer to call this routine
 if (timer==NULL)
 {
//        timer = new QTimer(60*1000, new java.awt.event.ActionListener() {
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    handleAlarm();
//                }
//            });
  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(handleAlarm()));
  timer->setInterval(60*1000);
 }

 timer->stop();
 QDateTime date = getTime();
 int waitSeconds = 60-date.time().second();
 int delay = (int)(waitSeconds*1000/mFactor)+100;  // make sure you miss the time transition
 //timer->setInitialDelay(delay);
 timer->setInterval(delay);
 //timer->setRepeats(true);     // in case we run by
 timer->setSingleShot(false);
 timer->start();

 // and notify the others
 int minutes = date.time().minute();
 if (minutes != oldMinutes)
 {
  // update memory
  updateMemory(date);
  // notify listeners
  pcMinutes->firePropertyChange("minutes", QVariant(oldMinutes),QVariant(minutes));
  emit minuteTick();
  //emit Timebase::minuteTick();
 }
 oldMinutes = minutes;
}

void SimpleTimebase::updateMemory(QDateTime date)
{
//    if (timeStorageFormat == NULL) {
//        try {
//            timeStorageFormat = new SimpleDateFormat(tr("TimeStorageFormat"));
//        } catch (IllegalArgumentException e) {
//            log->info("Dropping back to default time format due to exception "+e);
//            timeStorageFormat = new SimpleDateFormat("h:mm a");
//        }
//    }
//    clockMemory->setValue(timeStorageFormat.format(date));
    ((AbstractMemory*)clockMemory)->setValue(date);
}

void SimpleTimebase::updateMemory(double factor) {
    ((AbstractMemory*)factorMemory)->setValue(QVariant(factor));
}

/**
 * Request a call-back when the minutes place of the time changes.
 */
/*public*/ void SimpleTimebase::addMinuteChangeListener(PropertyChangeListener* l) {
    pcMinutes->addPropertyChangeListener(l);
    connect(this, SIGNAL(minuteTick()), l, SLOT(propertyChange(PropertyChangeEvent*)));
    startAlarm();
}

/**
 * Remove a request for call-back when the minutes place of the time changes.
 */
/*public*/ void SimpleTimebase::removeMinuteChangeListener(PropertyChangeListener* l) {
    pcMinutes->removePropertyChangeListener(l);
    disconnect(this, SIGNAL(minuteTick()), l, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void SimpleTimebase::setState(int s) throw (JmriException){}
/*public*/ int SimpleTimebase::getState(){ return 0; }

/*public*/ void SimpleTimebase::onPropertyChange(PropertyChangeEvent* e)
{
 clockSensorChanged();
}
