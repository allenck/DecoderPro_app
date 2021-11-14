#include "abstractautomaton.h"
#include "exceptions.h"
#include "automatsummary.h"
#include "sensor.h"
#include "turnout.h"
#include "namedbean.h"
#include <QTime>
#include <QThread>
#include "abstractsensor.h"
#include <QVector>
#include "instancemanager.h"
#include "programmer.h"
#include "slotmanager.h"
#include <QVBoxLayout>
#include "runnable.h"
#include <QMainWindow>
#include <QPushButton>
#include "propertychangelistener.h"
#include "lnthrottlemanager.h"
#include "Throttle/throttlelistener.h"
#include "abstractsensor.h"
#include "addressedprogrammermanager.h"
#include <QThread>

//AbstractAutomaton::AbstractAutomaton(QObject *parent) :
//    Runnable(parent)
//{
//}
/**
 * Abstract base for user automaton classes, which provide
 * individual bits of automation.
 * <P>
 * Each individual automaton runs in a separate thread, so they
 * can operate independently.  This class handles thread
 * creation and scheduling, and provides a number of services
 * for the user code.
 * <P>
 * Subclasses provide a "handle()" function, which does the needed
 * work, and optionally a "init()" function.
 * These can use any JMRI resources for input and output.  It should
 * not spin on a condition without explicit wait requests; it is more efficient
 * to use the explicit wait services when waiting for some specific
 * condition.
 * <P>
 * handle() is executed repeatedly until either the Automate object is
 * halted(), or it returns "false".  Returning "true" will just cause
 * handle() to be invoked again, so you can cleanly restart the Automaton
 * by returning from multiple points in the function.
 * <P>
 * Since handle() executes outside the GUI thread, it is important that
 * access to GUI (AWT, Swing) objects be scheduled through the
 * various service routines.
 * <P>
 * Services are provided by public member functions, described below.
 * They must only be invoked from the init and handle methods, as they
 * must be used in a delayable thread.  If invoked from the GUI thread,
 * for example, the program will appear to hang. To help ensure this,
 * a warning will be logged if they are used before the thread starts.
 * <P>
 * For general use, e.g. in scripts, the most useful functions are:
 *<UL>
 *<LI>Wait for a specific number of milliseconds: {@link #waitMsec(int)}
 *<LI>Wait for a specific sensor to be active: {@link #waitSensorActive(jmri.Sensor)}
 This is also available
 in a form that will wait for any of a group of sensors to be active.
 *<LI>Wait for a specific sensor to be inactive: {@link #waitSensorInactive(jmri.Sensor)}
 This is also available
 in a form that will wait for any of a group of sensors to be inactive.
 *<LI>Wait for a specific sensor to be in a specific state: {@link #waitSensorState(jmri.Sensor, int)}
 *<LI>Wait for a specific sensor to change: {@link #waitSensorChange(int, jmri.Sensor)}
 *<LI>Set a group of turnouts and wait for them to be consistent (actual position matches desired position): {@link #setTurnouts(jmri.Turnout[], jmri.Turnout[])}
 *<LI>Wait for a group of turnouts to be consistent (actually as set): {@link #waitTurnoutConsistent(jmri.Turnout[])}
 *<LI>Wait for any one of a number of Sensors, Turnouts and/or other objects to change: {@link #waitChange(jmri.NamedBean[])}
 *<LI>Obtain a DCC throttle: {@link #getThrottle}
 *<LI>Read a CV from decoder on programming track: {@link #readServiceModeCV}
 *<LI>Write a value to a CV in a decoder on the programming track: {@link #writeServiceModeCV}
 *<LI>Write a value to a CV in a decoder on the main track: {@link #writeOpsModeCV}
 *</UL>
 * <P>
 * Although this is named an "Abstract" class, it's actually concrete
 * so that Jython code can easily use some of the methods.
 *
 * @author	Bob Jacobsen    Copyright (C) 2003
 * @version     $Revision: 21621 $
 */
// /*public*/ class AbstractAutomaton implements Runnable {

/*public*/ AbstractAutomaton::AbstractAutomaton( QObject *parent) : QObject(parent)
{
 QString className = /*this.getClass().getName()*/metaObject()->className();
//    int lastdot = className.lastIndexOf(".");
//    setName(className.mid(lastdot+1, className.length()));
 setName(className);
 log = new Logger("AbstractAutomaton");
 debugWaitFrame = NULL;
 promptOnWait = false;
 inThread = false;
 _self = this;
 messageFrame = NULL;
 message = "";
 debugWaitFrame = NULL;
 summary = AutomatSummary::instance();
 terminateSensor = NULL;

 currentThread = NULL;
}
/*public*/ AbstractAutomaton::AbstractAutomaton(QString name, QObject *parent) : QObject(parent)
{
 setName(name);

 log = new Logger("AbstractAutomaton");
 debugWaitFrame = NULL;
 promptOnWait = false;
 inThread = false;
 _self = this;
 messageFrame = NULL;
 message = "";
 debugWaitFrame = NULL;
 summary = AutomatSummary::instance();
 terminateSensor = NULL;

 currentThread = NULL;
}

AbstractAutomaton::~AbstractAutomaton()
{
 delete log;
}

/**
 * Start this automat processing.
 *
 * Overrides the superclass method to do local accounting.
 */
/*public*/ void AbstractAutomaton::start(bool bRunInThread )
{
 if (currentThread != NULL) log->error("Start with currentThread not NULL!");
 if(bRunInThread)
 {
  this->bRunInThread=bRunInThread;
  currentThread = new QThread();
  currentThread->setObjectName(name);
  moveToThread(currentThread);
  connect(currentThread, SIGNAL(started()), this, SLOT(process()));
  connect(this, SIGNAL(finished()), currentThread, SLOT(quit()));
  connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
  connect(currentThread, SIGNAL(finished()), currentThread, SLOT(deleteLater()));
  currentThread->start();

 }
 else
 {
  process();
 }
 summary->_register(this);
 count = 0;
}

/**
 * Part of the implementation; not for general use.
 * <p>
 * This is invoked on currentThread.
 */
/*public*/ void AbstractAutomaton::process()
{
 try
 {
  inThread = true;
  bRun = true;
  init();
  // the real processing in the next statement is in handle();
  // and the loop call is just doing accounting
  while (bRun && handle())
  {
   count++;
   summary->loop(this);
//   currentThread->wait(10);
   waitMsec(10);
//   qApp->processEvents();
  }
  log->debug("normal termination, handle() returned false");
  currentThread = NULL;
  done();
  emit finished();
 }
// catch (/*ThreadDeath*/Exception e1)
// {
//  log->debug("Received ThreadDeath, likely due to stop(): "+e1.getMessage() +" "+ e1.getMessage());
// }
 catch (Exception e2)
 {
  log->warn("Exception ends AbstractAutomaton thread: "+e2.getMessage() + " "+ e2.getMessage());
 }
}
void AbstractAutomaton::threadTerminated()
{
 log->debug( tr("thread %1 terminated").arg(currentThread->objectName()));
}

/**
 * Stop the thread immediately.
 *
 * Overrides superclass method to handle local accounting.
 */
// The stop method on a thread has been deprecated, we need to find another way to deal with this
//@SuppressWarnings("deprecation")
/*public*/ void AbstractAutomaton::stop()
{
 if (currentThread == NULL)
 {
  log->error("Stop with currentThread NULL!");
  return;
 }
 try
 {
  currentThread->exit();
 }
 catch (/*ThreadDeath*/Exception e)
 {
  log->error(e.getMessage());
 }
 currentThread = NULL;
 done();
}

/**
 * Part of the internal implementation; not for general use.
 *
 * Common internal end-time processing
 */
void AbstractAutomaton::done() {
 summary->remove(this);
}


/**
 * Returns the number of times the handle routine has executed.
 *
 * Used by e.g. {@link jmri.jmrit.automat.monitor} to monitor progress
 */
/*public*/ int AbstractAutomaton::getCount() {
    return count;
}

/**
 * Gives access to the thread name.
 * Used internally for e.g. {@link jmri.jmrit.automat.monitor}
 */
/*public*/ QString AbstractAutomaton::getName() {
    return name;
}
/**
 * Update the name of this object.
 *
 * name is not a bound parameter, so changes are not
 * notified to listeners
 * @see #getName
 */
/*public*/ void AbstractAutomaton::setName(QString name) {
    this->name = name;
}

void AbstractAutomaton::defaultName() {
}

/**
 * User-provided initialization routine.
 *
 * This is called exactly once for each object created.
 * This is where you put all the code that needs to be
 * run when your object starts up:  Finding sensors and turnouts,
 * getting a throttle, etc.
 */
/*protected*/ void AbstractAutomaton::init() {}

/**
 * User-provided main routine.
 *
 * This is run repeatedly until
 * it signals the end by returning false.  Many automata
 * are intended to run forever, and will always return true.
 *
 * @return false to terminate the automaton, for example due to an error.
 */
/*protected*/ bool AbstractAutomaton::handle() { return false; }


/**
 * Wait for a specified number of milliseconds, and then
 * return control.
 */
/*public*/ void AbstractAutomaton::waitMsec( int milliseconds )
{
 //QDateTime time;
 qint64 target = /*System.currentTimeMillis()*/QDateTime::currentMSecsSinceEpoch()+ milliseconds;
 while (true)
 {
  long stillToGo = target - QDateTime::currentMSecsSinceEpoch();
  if (stillToGo <= 0) {
      break;
  }
  try {
      //QThread::msleep(stillToGo);
   SleeperThread::msleep(stillToGo);
  } catch (InterruptedException e) {
      QThread::currentThread()->exit(); // retain if needed later
  }
 }
}

/**
 * Part of the intenal implementation, not intended for users.
 * <P>
 * This handles exceptions internally,
 * so they needn't clutter up the code.  Note that the current
 * implementation doesn't guarantee the time, either high or low.
 * <P>
 * Because of the way Jython access handles synchronization, this
 * is explicitly synchronized internally.
 * @param milliseconds
 */
/*protected*/ void AbstractAutomaton::wait(int milliseconds)
{
 int eRslt = 0;
 if (!inThread) log->debug("wait invoked from invalid context");
 /*synchronized(this) */
 {
//  try
//  {
   //QMutexLocker locker(&mutex);
   if (milliseconds <0)
   {
    if(!bRunInThread)
    eRslt = loop.exec();
    else
     SleeperThread::msleep(100);
    //QThread::wait();
    //sleep(-1);
//    SleeperThread::msleep(-1);
    //condition.wait(&mutex);
   }
   else
    //QThread::wait(milliseconds);
    SleeperThread::msleep(milliseconds);
//  }
  //catch (InterruptedException e)
  if(eRslt != 0)
  {
   QThread::currentThread()->exit(0); // retain if needed later
   log->warn("interrupted in wait");
   bRun = false;
  }
 }
 if (promptOnWait) debuggingWait();
}

class SensorListener : public QObject, public PropertyChangeListener
{
 Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 AbstractAutomaton* aa;
public:
 SensorListener(AbstractAutomaton* aa) {this->aa = aa;}
 QObject* self() {return (QObject*)this;}
public slots:
 void propertyChange(PropertyChangeEvent* evt)
 {
  aa->sensorChange(evt);
 }

};
/**
 * Wait for a sensor to change state.
 * <P>
 * The current (OK) state of the Sensor is passed to avoid
 * a possible race condition. The new state is returned
 * for a similar reason.
 * <P>
 * This works by registering a listener, which is likely to
 * run in another thread.  That listener then interrupts the automaton's
 * thread, who confirms the change.
 *
 * @param mState Current state of the sensor
 * @param mSensor Sensor to watch
 * @return newly detected Sensor state
 */
/*public*/ int AbstractAutomaton::waitSensorChange(int mState, Sensor* mSensor)
{
 if (!inThread) log->warn("waitSensorChange invoked from invalid context");
 if (log->isDebugEnabled()) log->debug("waitSensorChange starts: "+mSensor->getSystemName());
 // register a listener
 //PropertyChangeListener* l;
    SensorListener* l= new SensorListener(this);
    mSensor->addPropertyChangeListener(l );
// AbstractSensor* sensor = (AbstractSensor*)mSensor;
// connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
//    {
//        /*public*/ void propertyChange(PropertyChangeEvent* e) {
//            synchronized (self) {
//                self.notifyAll(); // should be only one thread waiting, but just in case
//            }
//        }
//    });

 int now;
 while (mState == (now = mSensor->getKnownState()))
 {
  wait(-1);
 }

 // remove the listener & report new state
 mSensor->removePropertyChangeListener(l);
 //disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));

 return now;
}
void AbstractAutomaton::sensorChange(PropertyChangeEvent *)
{
 _self->notifyAll();
}

/**
 * Wait for a sensor to be active. (Returns immediately if already active)
 *
 * @param mSensor Sensor to watch
 */
/*public*/ void AbstractAutomaton::waitSensorActive(Sensor* mSensor)
{
 if (log->isDebugEnabled()) log->debug("waitSensorActive starts");
 waitSensorState(mSensor, Sensor::ACTIVE);
 return;
}

/**
 * Wait for a sensor to be inactive. (Returns immediately if already inactive)
 *
 * @param mSensor Sensor to watch
 */
/*public*/ void AbstractAutomaton::waitSensorInactive(Sensor* mSensor)
{
 if (log->isDebugEnabled()) log->debug("waitSensorInActive starts");
 waitSensorState(mSensor, Sensor::INACTIVE);
 return;
}

/**
 * Internal service routine to wait for one sensor to be
 * in (or become in) a specific state.
 * <P>
 * Used by waitSensorActive and waitSensorInactive
 * <P>
 * This works by registering a listener, which is likely to
 * run in another thread.  That listener then interrupts the automaton's
 * thread, who confirms the change.
 */
/*public*/ /*synchronized*/ void AbstractAutomaton::waitSensorState(Sensor* mSensor, int state)
{
 if (!inThread) log->warn("waitSensorState invoked from invalid context");
 if (((AbstractSensor*)mSensor)->getKnownState() == state) return;
 if (log->isDebugEnabled()) log->debug("waitSensorState starts: "+mSensor->getSystemName()+" "+QString::number(state));
 // register a listener
    SensorListener* l = new SensorListener(this);
    mSensor->addPropertyChangeListener((PropertyChangeListener*)l);
// AbstractSensor* sensor = (AbstractSensor*)mSensor;
// connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));
//    {
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e)
//        {
//            synchronized (self) {
//                self->notifyAll(); // should be only one thread waiting, but just in case
//            }
//        }
//    });

 while (bRun && state != ((AbstractSensor*)mSensor)->getKnownState())
 {
  wait(-1);  // wait for notification
 }

 // remove the listener & report new state
 mSensor->removePropertyChangeListener((PropertyChangeListener*)l);
// disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));

 return;
}

/**
 * Wait for one of a list of sensors to be be inactive.
 */
/*public*/ void AbstractAutomaton::waitSensorInactive(QList<Sensor*> mSensors)
{
 if (log->isDebugEnabled()) log->debug("waitSensorInactive[] starts");
 waitSensorState(mSensors, Sensor::INACTIVE);
}

/**
 * Wait for one of a list of sensors to be be active.
 */
/*public*/ void AbstractAutomaton::waitSensorActive(QList<Sensor*> mSensors)
{
 if (log->isDebugEnabled()) log->debug("waitSensorActive[] starts");
 waitSensorState(mSensors, Sensor::ACTIVE);
}

/**
 * Wait for one of a list of sensors to be be in a selected state.
 * <P>
 * This works by registering a listener, which is likely to
 * run in another thread.  That listener then interrupts the automaton's
 * thread, who confirms the change.
 *
 * @param mSensors Array of sensors to watch
 * @param state State to check (static value from jmri.Sensors)
 */
/*public*/ /*synchronized*/ void AbstractAutomaton::waitSensorState(QList<Sensor*> mSensors, int state)
{
 QMutexLocker locker(&mutex);
 if (!inThread) log->warn("waitSensorState invoked from invalid context");
 if (log->isDebugEnabled()) log->debug("waitSensorState[] starts");

 // do a quick check first, just in case
 if (checkForState(mSensors, state))
 {
  log->debug("returns immediately");
  return;
 }
 // register listeners
 int i;
 QVector<PropertyChangeListener*>* listeners =
         new QVector<PropertyChangeListener*>(mSensors.length());
 for (i=0; i<mSensors.length(); i++)
 {
  listeners->replace(i, (PropertyChangeListener*)this);
  mSensors.at(i)->addPropertyChangeListener((PropertyChangeListener*)this);
//  AbstractSensor* sensor = (AbstractSensor*)mSensors.at(i);
//  connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));

//     {
//      /*public*/ void propertyChange(PropertyChangeEvent* e)
//      {
//       /*synchronized (self)*/
//       {
//        QMutexLocker locker(&mutex);
//        log->debug("notify waitSensorState[] of property change");
//        self->notifyAll(); // should be only one thread waiting, but just in case
//       }
//      }
//     })));
 }

 while (!checkForState(mSensors, state))
 {
     wait(-1);
 }

 // remove the listeners
 for (i=0; i<mSensors.length(); i++)
 {
     //mSensors.at(i)->removePropertyChangeListener(listeners->at(i));
     AbstractSensor* sensor = (AbstractSensor*)mSensors.at(i);
    disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(sensorChange(PropertyChangeEvent*)));

 }

 return;
}

/**
 * Wait for a list of turnouts to all be in a consistent state
 * <P>
 * This works by registering a listener, which is likely to
 * run in another thread.  That listener then interrupts the automaton's
 * thread, who confirms the change.
 *
 * @param mTurnouts list of turnouts to watch
 */
/*public*/ /*synchronized*/ void AbstractAutomaton::waitTurnoutConsistent(QList<Turnout*> mTurnouts)
{
 QMutexLocker locker(&mutex);

 if (!inThread) log->warn("waitTurnoutConsistent invoked from invalid context");
 if (log->isDebugEnabled()) log->debug("waitTurnoutConsistent[] starts");

 // do a quick check first, just in case
 if (checkForConsistent(mTurnouts)) {
     log->debug("returns immediately");
     return;
 }
 // register listeners
 int i;
 QVector<PropertyChangeListener*>* listeners =
         new QVector<PropertyChangeListener*>(mTurnouts.length());
 for (i=0; i<mTurnouts.length(); i++)
 {
  PropertyChangeListener* l = (PropertyChangeListener*)this;
  listeners->replace(i, l);
  mTurnouts.at(i)->addPropertyChangeListener(l);
//  connect(mTurnouts.at(i)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        {
//            /*public*/ void propertyChange(PropertyChangeEvent* e) {
//                synchronized (self) {
//                    log->debug("notify waitTurnoutConsistent[] of property change");
//                    self->notifyAll(); // should be only one thread waiting, but just in case
//                }
//            }
//        });

 }

 while (!checkForConsistent(mTurnouts))
 {
  wait(-1);
 }

 // remove the listeners
 for (i=0; i<mTurnouts.length(); i++)
 {
  mTurnouts.at(i)->removePropertyChangeListener(listeners->at(i));
  disconnect(mTurnouts.at(i)->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 return;
}
/*public*/ void AbstractAutomaton::propertyChange(PropertyChangeEvent* /*e*/)
{
 /*synchronized (self)*/
 {
  QMutexLocker locker(&mutex);
  log->debug("notify waitTurnoutConsistent[] of property change");
  notifyAll(); // should be only one thread waiting, but just in case
 }
}
/**
 * Convenience function to set a bunch of turnouts and wait until they are all
 * in a consistent state
 * @param closed	turnouts to set to closed state
 * @param thrown	turnouts to set to thrown state
 */
/*public*/ void AbstractAutomaton::setTurnouts(QList<Turnout*> closed, QList<Turnout*> thrown)
{
 QVector<Turnout*> turnouts =  QVector<Turnout*>(closed.length() + thrown.length());
 int ti = 0;
 for (int i=0; i<closed.length(); ++i)
 {
  turnouts.replace(ti++,  closed.at(i));
  ((AbstractTurnout*)closed.at(i))->setCommandedState(Turnout::CLOSED);
 }
 for (int i=0; i<thrown.length(); ++i)
 {
  turnouts.replace(ti++, thrown.at(i));
  ((AbstractTurnout*)thrown.at(i))->setCommandedState(Turnout::THROWN);
 }
 waitTurnoutConsistent(turnouts.toList());
}

/**
 * Wait for one of a list of NamedBeans (sensors, signal heads and/or turnouts) to change.
 * <P>
 * This works by registering a listener, which is likely to
 * run in another thread.  That listener then interrupts the automaton's
 * thread, who confirms the change.
 *
 * @param mInputs Array of NamedBeans to watch
 */
// dboudreau, removed synchronized from the method below.
// The synchronized can cause thread lockup when a one thread
// is held at the inner synchronized (self)

/*public*/ void AbstractAutomaton::waitChange(QVector<NamedBean*> mInputs)
{
 if (!inThread) log->warn("waitChange invoked from invalid context");
 if (log->isDebugEnabled()) log->debug("waitChange[] starts");

 // register listeners
 int i;
 QVector<PropertyChangeListener*> listeners =
            QVector<PropertyChangeListener*>(mInputs.size());
 for (i=0; i<mInputs.size(); i++)
 {
  PropertyChangeListener* l = (PropertyChangeListener*)this;
  listeners.replace(i, l);
  //mInputs.at(i)->addPropertyChangeListener(l);
  if(static_cast<AbstractSensor*>(mInputs.at(i))!= NULL)
  {
   AbstractSensor* sensor = (AbstractSensor*)mInputs.at(i);
   connect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }

//        {
//            /*public*/ void propertyChange(PropertyChangeEvent* e) {
//                /*synchronized (self)*/ {
//                    QMutexLocker locker(&mutex);
//                    log->debug("notify waitChange[] of property change "+e.getPropertyName()+" from "+((NamedBean)e.getSource()).getSystemName());
//                    self.notifyAll(); // should be only one thread waiting, but just in case
//                }
//            }
//        });

 }

 // wait for notify
 wait(-1);

 // remove the listeners
 for (i=0; i<mInputs.size(); i++)
 {
  //mInputs.at(i)->removePropertyChangeListener(listeners.at(i));
  if(static_cast<AbstractSensor*>(mInputs.at(i))!= NULL)
  {
   AbstractSensor* sensor = (AbstractSensor*)mInputs.at(i);
   disconnect(sensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
 }
 return;
}

/**
 * Wait for one of an array of sensors to change.
 * <P>
 * This is an older method, now superceded by waitChange, which can wait
 * for any NamedBean.
 *
 * @param mSensors Array of sensors to watch
 */
/*public*/ /*synchronized*/ void AbstractAutomaton::waitSensorChange(QList<Sensor*> mSensors)
{
 QMutexLocker locker(&mutex);
 QVector<NamedBean*> v =  QVector<NamedBean*>();
 foreach (Sensor* s, mSensors)
 {
  v.append((NamedBean*)s);
 }
 //waitChange((QVector<NamedBean*>)mSensors.toVector());
 waitChange(v);
 return;
}

/**
 * Check an array of sensors to see if any are in a specific state
 * @param mSensors Array to check
 * @return true if any are ACTIVE
 */
/*private*/ bool AbstractAutomaton::checkForState(QList<Sensor*> mSensors, int state)
{
 for (int i=0; i<mSensors.length(); i++)
 {
  if (mSensors.at(i)->getKnownState() == state) return true;
 }
 return false;
}

/*private*/ bool AbstractAutomaton::checkForConsistent(QList<Turnout*> mTurnouts)
{
 for (int i=0; i<mTurnouts.length(); ++i)
 {
  if (!mTurnouts.at(i)->isConsistentState())
  {
   return false;
  }
 }
 return true;
}

/**
 * Obtains a DCC throttle, including waiting for the command station response.
 * @param address
 * @param longAddress true if this is a long address, false for a short address
 * @return A usable throttle, or NULL if error
 */
/*public*/ DccThrottle* AbstractAutomaton::getThrottle(int address, bool longAddress, int waitSecs)
{
 log->debug(tr("requesting DccThrottle for addr %1").arg(address));
    if (!inThread) log->warn("getThrottle invoked from invalid context");
    throttle = NULL;
    ThrottleListener* throttleListener = new AAThrottleListener(this);

    bool ok = ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->requestThrottle(
        new DccLocoAddress(address, longAddress), throttleListener, false);
    // check if reply is coming
    if (!ok) {
        log->info("Throttle for loco "+QString::number(address)+" not available");
        return NULL;
    }

    // now wait for reply from identified throttle
    int waited = 0;
    while (throttle == nullptr && failedThrottleRequest == false && waited <= waitSecs) {
        log->debug("waiting for throttle");
        wait(10000);
        if (throttle == NULL) log->warn("Still waiting for throttle "+QString::number(address)+"!");
    }
    return throttle;
}

/*public*/ DccThrottle* AbstractAutomaton::getThrottle(int address, bool longAddress) {
        return getThrottle(address, longAddress, 30);  //default to 30 seconds wait
    }

/**
 * Obtains a DCC throttle, including waiting for the command station
 * response.
 *
 * @param re       specifies the desired locomotive
 * @param waitSecs number of seconds to wait for throttle to acquire before
 *                 returning null
 * @return A usable throttle, or null if error
 */
/*public*/ DccThrottle*AbstractAutomaton:: getThrottle(BasicRosterEntry* re, int waitSecs) {
    log->debug(tr("requesting DccThrottle for rosterEntry %1").arg(re->getId()));
    if (!inThread) {
        log->warn("getThrottle invoked from invalid context");
    }
    throttle = nullptr;
//    ThrottleListener throttleListener = new ThrottleListener() {
//        @Override
//        public void notifyThrottleFound(DccThrottle t) {
//            throttle = t;
//            synchronized (self) {
//                self.notifyAll(); // should be only one thread waiting, but just in case
//            }
//        }

//        @Override
//        public void notifyFailedThrottleRequest(jmri.LocoAddress address, String reason) {
//            log.error("Throttle request failed for {} because {}", address, reason);
//            failedThrottleRequest = true;
//            synchronized (self) {
//                self.notifyAll(); // should be only one thread waiting, but just in case
//            }
//        }

//        /**
//         * No steal or share decisions made locally
//         * {@inheritDoc}
//         */
//        @Override
//        public void notifyDecisionRequired(jmri.LocoAddress address, DecisionType question) {
//        }
//    };
    ThrottleListener* throttleListener = new AAThrottleListener(this);

    bool ok = ((ThrottleManager*)InstanceManager::getDefault("DefaultThrottleManager"))
            ->requestThrottle(re, throttleListener, false);

    // check if reply is coming
    if (!ok) {
        log->info(tr("Throttle for loco %1 not available").arg(re->getId()));
        ((ThrottleManager*)InstanceManager::getDefault("ThrottleManager"))->cancelThrottleRequest(
            re->getDccLocoAddress(), throttleListener);  //kill the pending request
        return nullptr;
    }

    // now wait for reply from identified throttle
    int waited = 0;
    while (throttle == nullptr && failedThrottleRequest == false && waited <= waitSecs) {
        log->debug("waiting for throttle");
        wait(1000);  //  1 seconds
        waited++;
        if (throttle == nullptr) {
            log->warn(tr("Still waiting for throttle %1!").arg(re->getId()));
        }
    }
    if (throttle == nullptr) {
        log->debug(tr("canceling request for Throttle %1").arg(re->getId()));
        ((ThrottleManager*)InstanceManager::getDefault("DefaultThrottleManager"))->cancelThrottleRequest(
            re->getDccLocoAddress(), throttleListener);  //kill the pending request
    }
    return throttle;
}

/*public*/ DccThrottle* AbstractAutomaton::getThrottle(BasicRosterEntry* re) {
    return getThrottle(re, 30);  //default to 30 seconds
}
/**
 * Write a CV on the service track, including waiting for completion.
 * @param CV Number 1 through 512
 * @param value
 * @return true if completed OK
 */
/*public*/ bool AbstractAutomaton::writeServiceModeCV(QString CV, int value) {
    // get service mode programmer
    Programmer* programmer = ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
#if 1
    // do the write, response will wake the thread
    try {
        programmer->writeCV(CV, value, new ProgListener1(this));
//        {
//            /*public*/ void programmingOpReply(int value, int status)
//            {
//                /*synchronized (self)*/ {
//                    QMutexLocker locker(&mutex);
//                    self->notifyAll(); // should be only one thread waiting, but just in case
//                }
//            }
//        });
    } catch (ProgrammerException e) {
        log->warn("Exception during writeServiceModeCV: "+e.getMessage());
        return false;
    }
    // wait for the result
    wait(-1);
#endif
    return true;
}


/**
 * Read a CV on the service track, including waiting for completion.
 * @param CV Number 1 through 512
 * @return -1 if error, else value
 */
/*public*/ int AbstractAutomaton::readServiceModeCV(QString CV) {
    // get service mode programmer
    Programmer* programmer = ((DefaultProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager*"))
                    ->getGlobalProgrammer();
#if 1
    // do the write, response will wake the thread
    cvReturnValue = -1;
    try {
         programmer->readCV(CV, new ProgListener2(this));
//         {
//            /*public*/ void programmingOpReply(int value, int status) {
//                cvReturnValue = value;
//                /*synchronized (self) */{
//                    QMutexLocker locker(&mutex);
//                    self->notifyAll(); // should be only one thread waiting, but just in case
//                }
//            }
//        });
    } catch (ProgrammerException e) {
        log->warn("Exception during writeServiceModeCV: "+e.getMessage());
        return -1;
    }
    // wait for the result
    wait(-1);
#endif
    return cvReturnValue;
}

/**
 * Write a CV in ops mode, including waiting for completion.
 * @param CV Number 1 through 512
 * @param value
 * @param loco   Locomotive decoder address
 * @param longAddress true is the locomotive is using a long address
 * @return true if completed OK
 */
/*public*/ bool AbstractAutomaton::writeOpsModeCV(QString CV, int value, bool longAddress, int loco) {
    // get service mode programmer
    Programmer* programmer = (Programmer*)((DefaultProgrammerManager*)InstanceManager::getDefault("AddressedProgrammerManager*"))->                    getAddressedProgrammer(longAddress, loco);
#if 1
    // do the write, response will wake the thread
    try {
        programmer->writeCV(CV, value, new ProgListener3(this));
//        {
//            /*public*/ void programmingOpReply(int value, int status) {
//                synchronized (self) {
//                    self.notifyAll(); // should be only one thread waiting, but just in case
//                }
//            }
//        });
    } catch (ProgrammerException e) {
        log->warn("Exception during writeServiceModeCV: "+e.getMessage());
        return false;
    }
    // wait for the result
    wait(-1);
#endif
    return true;
}


/**
 * Internal class to show a Frame
 */
 MsgFrame::MsgFrame()
 {
    mFrame = NULL;
 }
 /*public*/ void MsgFrame::hide()
 {
    mShow = false;
    // invoke the operation
    //javax.swing.SwingUtilities.invokeLater(this);
}

/**
 * Show a message in the message frame, and optionally wait for the user to acknowledge
 */
/*public*/ void MsgFrame::show(QString pMessage, bool pPause) {
    mMessage = pMessage;
    mPause = pPause;
    mShow = true;

    // invoke the operation
    //javax.swing.SwingUtilities.invokeLater(this);
    // wait to proceed?
    if (mPause) {
        /*synchronized(self)*/ {
            //QMutexLocker locker(&mutex);
//                new WaitHandler(this);
        }
    }
}


/*public*/ void MsgFrame::run()
{
 // create the frame if it doesn't exist
 if (mFrame==NULL)
 {
  mFrame = new JFrame;
  mArea = new QTextEdit();
//            mArea->setEditable(false);
//            mArea->setLineWrap(false);
//            mArea->setWrapStyleWord(true);
  mButton = new QPushButton("Continue");
  mFrame->centralWidget()->setLayout(new QVBoxLayout());
  mFrame->centralWidget()->layout()->addWidget(mArea/*, BorderLayout.CENTER */);
  mFrame->centralWidget()->layout()->addWidget(mButton/*, BorderLayout.SOUTH*/ );
//            mButton.addActionListener(new java.awt.event.ActionListener() {
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    synchronized (self) {
//                        self.notifyAll(); // should be only one thread waiting, but just in case
//                    }
//                    mFrame.setVisible(false);
//                }
//            });
//            connect()
  mFrame->adjustSize();
 }
 if (mShow)
 {
  // update message, show button if paused
  mArea->setPlainText(mMessage);
  if (mPause) {
      mButton->setVisible(true);
  } else {
      mButton->setVisible(false);
  }
  // do optional formatting

  format();
  // center the frame
  mFrame->adjustSize();
#if 0
  Dimension screen = mFrame.getContentPane().getToolkit().getScreenSize();
  Dimension size = mFrame.getSize();
  mFrame.setLocation((screen.width-size.width)/2,(screen.height-size.height)/2);
#endif
  // and show it to the user
  mFrame->setVisible(true);
 }
 else mFrame->setVisible(false);
}

/**
 * Abstract method to handle formatting of the text on a show
 */
/*protected*/ void MsgFrame::format() {}


/**
 * Wait for the user to OK moving forward. This is complicated
 * by not running in the GUI thread, and by not wanting to use
 * a modal dialog->
 */
/*private*/ void AbstractAutomaton::debuggingWait() {
#if 0 // done
    // post an event to the GUI pane
    Runnable* r = new Runnable( [] {
        /*public*/ void run() {
            // create a prompting frame
            if (debugWaitFrame==NULL) {
                debugWaitFrame = new QMainWindow();
                debugWaitFrame->setWindowTitle(tr("Automaton paused"));
                QPushButton* b = new JButton("Continue");
                debugWaitFrame.getContentPane().add(b);
                b.addActionListener(new java.awt.event.ActionListener() {
                    /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
                        synchronized (self) {
                            self->notifyAll(); // should be only one thread waiting, but just in case
                        }
                        debugWaitFrame.setVisible(false);
                    }
                });
                debugWaitFrame.pack();
            }
            debugWaitFrame.setVisible(true);
        }
    };)
    //javax.swing.SwingUtilities.invokeLater(r);
    // wait to proceed
    try {
        super.wait();
    }  catch (InterruptedException e) {
        QThread::currentThread()->stop(); // retain if needed later
        log->warn("Interrupted during debugging wait, not expected");
    }
#endif
    Runnable1* r = new Runnable1(this);
}
void AbstractAutomaton::notifyAll()
{
//    QMutexLocker locker(&mutex);
//    condition.wait(&mutex);
 //condition.wakeAll();
 loop.exit(0);
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractAutomaton.class.getName());
//}

///* @(#)AbstractAutomaton.java */
/*public*/ void AbstractAutomaton::notifyThrottleFound(DccThrottle* t)
{
 throttle = t;
 /*synchronized (self)*/
 {
  QMutexLocker locker(&throttleMutex);
  _self->notifyAll(); // should be only one thread waiting, but just in case
 }
}
/*public*/ void AbstractAutomaton::notifyFailedThrottleRequest(DccLocoAddress* /*address*/, QString /*reason*/)
{
}
/*public*/ void AbstractAutomaton::setTerminateSensor(Sensor* ts)
{
 terminateSensor = ts;
 connect(terminateSensor->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(terminateSensor_changed(PropertyChangeEvent*)));
}

void AbstractAutomaton::terminateSensor_changed(PropertyChangeEvent*)
{
 //emit terminate();
 bRun = false;
 loop.exit(1);
}
