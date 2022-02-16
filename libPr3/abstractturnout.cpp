#include "abstractturnout.h"
#include "instancemanager.h"
#include "turnoutoperator.h"
#include "nofeedbackturnoutoperation.h"
#include "abstractsensor.h"
#include "pushbuttonpacket.h"
#include "signalspeedmap.h"
#include "rosterentry.h"
#include "loggerfactory.h"
#include "signalspeedmap.h"
#include "vptr.h"
#include "signalspeedmap.h"
#include "jmriexception.h"

AbstractTurnout::AbstractTurnout(QObject *parent) :
    Turnout(parent)
{
 _validFeedbackNames =  QVector<QString>();
 _validFeedbackModes =  QVector<int>();
 _validFeedbackNames << QString("DIRECT")<< QString("ONESENSOR")<< QString("TWOSENSOR")<< QString("DELAYED") ;

 _validFeedbackModes << Turnout::DIRECT<<Turnout::ONESENSOR<<Turnout::TWOSENSOR<<Turnout::DELAYED;
 _activeFeedbackType = Turnout::DIRECT;
 _validFeedbackTypes = Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR | Turnout::DELAYED;
 _knownState = UNKNOWN;

 _commandedState = UNKNOWN;

 _numberOutputBits = 1;
 _controlType = 0;
 _inverted = false;
 _cabLockout = false;

 _pushButtonLockout = false;

 _enableCabLockout = false;

 _enablePushButtonLockout = false;
 _reportLocked = true;
 inhibitOperation = false; // do not automate this turnout, even if globally operations are on
 binaryOutput = false;
 _firstNamedSensor = NULL;
 _secondNamedSensor = NULL;
 myTurnoutOperation = NULL;
 log = new Logger("AbstractTurnout");
}

/**
 * Abstract base for the Turnout interface.
 * <P>
 * Implements basic feedback modes:
 * <UL>
 * <LI>NONE feedback, where the KnownState and CommandedState track each other.
 * <LI>ONESENSOR feedback where the state of a single sensor specifies THROWN
 * vs CLOSED
 * <LI>TWOSENSOR feedback, where one sensor specifies THROWN and another
 * CLOSED.
 * </UL>
 * If you want to implement some other feedback, override and modify
 * setCommandedState() here.
 * <P>
 * Implements the parameter binding support.
 * <P>
 * Note that we consider it an error for there to be more than one object that
 * corresponds to a particular physical turnout on the layout.
 * <p>
 * Turnout system names are always upper case.
 * <P>
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2009
 * @version $Revision: 17977 $
 */
//public abstract class AbstractTurnout extends AbstractNamedBean implements
//		Turnout, java.io.Serializable, java.beans.PropertyChangeListener {

AbstractTurnout::AbstractTurnout(QString systemName, QObject *parent) :
    Turnout(systemName.toUpper(), parent)
{
 //super(systemName.toUpperCase());
 //  _validFeedbackNames = new QStringList();
 // _validFeedbackModes = new QList<int>();
 _validFeedbackNames << QString("DIRECT")<< QString("ONESENSOR")<< QString("TWOSENSOR") ;

 _validFeedbackModes << Turnout::DIRECT<<Turnout::ONESENSOR<<Turnout::TWOSENSOR;
 _activeFeedbackType = Turnout::DIRECT;
 _validFeedbackTypes = Turnout::DIRECT | Turnout::ONESENSOR | Turnout::TWOSENSOR;
 _knownState = UNKNOWN;

 _commandedState = UNKNOWN;

 _numberOutputBits = 1;
 _controlType = 0;
 _inverted = false;
 _cabLockout = false;

 _pushButtonLockout = false;

 _enableCabLockout = false;

 _enablePushButtonLockout = false;
 _reportLocked = true;
  inhibitOperation = false; // do not automate this turnout, even if globally operations are on
  binaryOutput = false;
_validDecoderNames = PushbuttonPacket::getValidDecoderNames();
_decoderName = PushbuttonPacket::unknown;
  _firstNamedSensor = NULL;
  _secondNamedSensor = NULL;
 setObjectName(systemName);
 myTurnoutOperation = NULL;
 log = new Logger("AbstractTurnout");
}

AbstractTurnout::AbstractTurnout(QString systemName, QString userName, QObject *parent) :
    Turnout(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpperCase(), userName);
// _validFeedbackNames = new QStringList();
// _validFeedbackModes = new QList<int>();

_validFeedbackNames << "DIRECT"<< "ONESENSOR"<< "TWOSENSOR" ;

_validFeedbackModes << Turnout::DIRECT<<Turnout::ONESENSOR<<Turnout::TWOSENSOR;
_activeFeedbackType = Turnout::DIRECT;
_validFeedbackTypes = Turnout::DIRECT |Turnout::ONESENSOR |Turnout::TWOSENSOR;
_knownState = UNKNOWN;

_commandedState = UNKNOWN;

_numberOutputBits = 1;
_controlType = 0;
_inverted = false;
_cabLockout = false;

_pushButtonLockout = false;

_enableCabLockout = false;

_enablePushButtonLockout = false;
_reportLocked = true;
 inhibitOperation = true; // do not automate this turnout, even if globally operations are on
 binaryOutput = false;
 _validDecoderNames = PushbuttonPacket::getValidDecoderNames();
 _decoderName = PushbuttonPacket::unknown;
 _firstNamedSensor = NULL;
 _secondNamedSensor = NULL;
 setObjectName(systemName);
 myTurnoutOperation = NULL;
 log = new Logger("AbstractTurnout");
}

/**
 * Handle a request to change state, typically by sending a message to the
 * layout in some child class. Public version (used by TurnoutOperator)
 * sends the current commanded state without changing it.
 *
 * @param s new state value
 */
/*abstract protected*/ void AbstractTurnout::forwardCommandChangeToLayout(int s)
{
 Q_UNUSED(s)
}

/*protected*/ void AbstractTurnout::forwardCommandChangeToLayout() {
    forwardCommandChangeToLayout(_commandedState);
}

// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
//		public void firePropertyChange(String propertyName,
//					       	Object oldValue,
//						Object newValue)
// _once_ if anything has changed state

/**
 * Sets a new Commanded state, if need be notifying the listeners, but does
 * NOT send the command downstream. This is used when a new commanded state
 * is noticed from another command.
 */
/*protected*/ void AbstractTurnout::newCommandedState(int s)
{
 if(s < UNKNOWN || s > INCONSISTENT)
  s= UNKNOWN;

 if (_commandedState != s)
 {
  int oldState = _commandedState;
  _commandedState = s;
  firePropertyChange("CommandedState", QVariant(oldState), QVariant(_commandedState));
 }
}

/*public*/ int AbstractTurnout::getKnownState() {
    return _knownState;
}

/**
 * Public access to changing turnout state. Sets the commanded state and,
 * if appropriate starts a TurnoutOperator to do its thing. If there is no
 * TurnoutOperator (not required or nothing suitable) then just tell the layout
 * and hope for the best.
 */
/*public*/ void AbstractTurnout::setCommandedState(int s)
{
 log->debug("set commanded state for turnout " + getSystemName() + " to " + QString("%1").arg(s));
 newCommandedState(s);

 myOperator = getTurnoutOperator(); // MUST set myOperator before starting the thread
 if (myOperator == NULL)
 {
  forwardCommandChangeToLayout(s);
  // optionally handle feedback
  if (_activeFeedbackType == Turnout::DIRECT)
  {
   newKnownState(s);
  }
  else if (_activeFeedbackType == DELAYED)
  {
   newKnownState(INCONSISTENT);
#if 0 // TODO:
   jmri.util.ThreadingUtil.runOnLayoutDelayed( () -> { newKnownState(s); },
            DELAYED_FEEDBACK_INTERVAL );
#endif
  }
 }
 else
 {
  myOperator->start();
 }
}

/*public*/ int AbstractTurnout::getCommandedState() {
    return _commandedState;
}
/** {@inheritDoc}
 * Used in {@link jmri.implementation.DefaultRoute#setRoute()} and
 * {@link jmri.implementation.MatrixSignalMast#updateOutputs(char[])}.
 */
//@Override
/*public*/ void AbstractTurnout::setCommandedStateAtInterval(int s) {
    nextWait = InstanceManager::turnoutManagerInstance()->outputIntervalEnds();
    // nextWait time is calculated using actual turnoutInterval in TurnoutManager
#if 1
    if (nextWait->isAfter(LocalDateTime::now())) { // don't sleep if nextWait =< now()
        log->debug(tr("Turnout now() = %1, waitUntil = %2").arg(LocalDateTime::now()->toString(), nextWait->toString()));
        // insert wait before sending next output command to the layout
//        r = []() {
//            log->debug(tr("go to sleep for %1 ms...").arg(qMax(0ULL, LocalDateTime::now()->until(nextWait, LocalDateTime::ChronoUnit::MILLIS))));
//            try {
//                Thread.sleep(qMax(0L, LocalDateTime::now()->until(nextWait, LocalDateTime::ChronoUnit::MILLIS))); // nextWait might have passed in the meantime
//                log->debug(tr("back from sleep, forward on %1").arg(LocalDateTime::now()->toString()));
//                setCommandedState(s);
//            } catch (InterruptedException ex) {
//                log->debug(tr("setCommandedStateAtInterval(s) interrupted at {}", LocalDateTime.now());
//                Thread.currentThread().interrupt(); // retain if needed later
//            }
//        };
//        thr = new Thread(r);
//        thr.start();
        thr = new IntervalCheck(s, this);
        QThread* thread = new QThread();
        connect(thread, SIGNAL(started()), thr, SLOT(process()));
        connect(thr, SIGNAL(finished()), thread, SLOT(quit()));
        thr->moveToThread(thread);
        thread->start();
    } else {
        log->debug("nextWait has passed");
        setCommandedState(s);
    }
#endif
}
/**
 * Add a protected newKnownState() for use by implementations.
 * <P>
 * Use this to update internal information when a state change is detected
 * <em>outside</em> the Turnout object, e.g. via feedback from sensors on
 * the layout.
 * <P>
 * If the layout status of the Turnout is observed to change to THROWN or
 * CLOSED, this also sets the commanded state, because it's assumed that
 * somebody somewhere commanded that move. If it's observed to change to
 * UNKNOWN or INCONSISTENT, that's perhaps either an error or a move in
 * progress, and no change is made to the commanded state.
 * <P>
 * This implementation sends a command to the layout for the new state if
 * going to THROWN or CLOSED, because there may be others listening to
 * network state.
 * <P>
 * Not intended for general use, e.g. for users to set the KnownState.
 *
 * @param s
 *            New state value
 */
/*protected*/ void AbstractTurnout::newKnownState(int s)
{
 if(s < UNKNOWN || s > INCONSISTENT)
  s= UNKNOWN;
 if (_knownState != s)
 {
  int oldState = _knownState;
  _knownState = s;
  firePropertyChange("KnownState", QVariant(oldState), QVariant(_knownState));
 }
 // if known state has moved to Thrown or Closed,
 // set the commanded state to match
 if (((_knownState == Turnout::THROWN) && (_commandedState != Turnout::THROWN))
         || ((_knownState == Turnout::CLOSED) && (_commandedState != Turnout::CLOSED)))
        newCommandedState(_knownState);
}

/**
 * Show whether state is one you can safely run trains over
 * @return	true iff state is a valid one and the known state is the same as commanded
 */
/*public*/ bool AbstractTurnout::isConsistentState()
{
 return (_commandedState == _knownState)
            && (_commandedState == Turnout::CLOSED || _commandedState == Turnout::THROWN);
}

/**
 * The name pretty much says it.
 *<P>
 * Triggers all listeners, etc. For use by the TurnoutOperator classes.
 */
void AbstractTurnout::setKnownStateToCommanded()
{
 newKnownState(_commandedState);
}

/**
 * Implement a shorter name for setCommandedState.
 * <P>
 * This generally shouldn't be used by Java code; use setCommandedState
 * instead. The is provided to make Jython script access easier to read.
 * <P>
 * Note that getState() and setState(int) are not symmetric: getState is the
 * known state, and set state modifies the commanded state.
 */
/*public*/ void AbstractTurnout::setState(int s) {
    setCommandedState(s);
}

/**
 * Implement a shorter name for getKnownState.
 * <P>
 * This generally shouldn't be used by Java code; use getKnownState instead.
 * The is provided to make Jython script access easier to read.
 * <P>
 * Note that getState() and setState(int) are not symmetric: getState is the
 * known state, and set state modifies the commanded state.
 */
/*public*/ int AbstractTurnout::getState() {
    return getKnownState();
}
//@Override
    //@CheckReturnValue
 /*public*/ QString AbstractTurnout::describeState(int state) {
     switch (state) {
         case THROWN: return tr("Thrown");
         case CLOSED: return tr("Closed");
         default: return Turnout::describeState(state);
     }
 }

/* Type of turnout control - defaults to 0 for 'steady state' */

/*public*/ int AbstractTurnout::getNumberOutputBits() {
    return _numberOutputBits;
}

/*public*/ void AbstractTurnout::setNumberOutputBits(int num) {
    _numberOutputBits = num;
}

/*public*/ int AbstractTurnout::getControlType() {
    return _controlType;
}

/*public*/ void AbstractTurnout::setControlType(int num) {
    _controlType = num;
}

/*public*/ int AbstractTurnout::getValidFeedbackTypes() {
    return _validFeedbackTypes;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of //cheap array copy
/*public*/ QVector<QString> AbstractTurnout::getValidFeedbackNames() {
    return _validFeedbackNames;
}

/*public*/ void AbstractTurnout::setFeedbackMode(QString mode) /*throw(IllegalArgumentException)*/
{
 for (int i = 0; i < _validFeedbackNames.length(); i++)
 {
  if (mode==_validFeedbackNames.at(i))
  {
   setFeedbackMode(_validFeedbackModes.at(i));
   return;
  }
 }
 throw new IllegalArgumentException("Unexpected mode: " + mode);
}

/*public*/ void AbstractTurnout::setFeedbackMode(int mode) /*throw(IllegalArgumentException)*/ {
    // check for error - following removed the low bit from mode
    int test = mode & (mode - 1);
    if (test != 0)
        throw new IllegalArgumentException("More than one bit set: " + mode);
    // set the value
    int oldMode = _activeFeedbackType;
    _activeFeedbackType = mode;
    if (oldMode != _activeFeedbackType)
        firePropertyChange("feedbackchange", QVariant(oldMode),
                QVariant(_activeFeedbackType));
    // unlock turnout if feedback is changed
    setLocked(Turnout::CABLOCKOUT, false);
}

/*public*/ int AbstractTurnout::getFeedbackMode() {
    return _activeFeedbackType;
}

/*public*/ QString AbstractTurnout::getFeedbackModeName()
{
 for (int i = 0; i < _validFeedbackNames.length(); i++)
 {
  if (_activeFeedbackType == _validFeedbackModes.at(i)) {
      return _validFeedbackNames.at(i);
  }
 }
 log->error("Unexpected internal mode: "
         + QString::number(_activeFeedbackType));
 throw new IllegalArgumentException("Unexpected internal mode: "
         + QString::number(_activeFeedbackType));
}

//@Override
/*public*/ void AbstractTurnout::requestUpdateFromLayout() {
    if (_activeFeedbackType == ONESENSOR || _activeFeedbackType == TWOSENSOR) {
        Sensor* s1 = getFirstSensor();
        if (s1 != NULL) s1->requestUpdateFromLayout();
    }
    if (_activeFeedbackType == TWOSENSOR) {
        Sensor* s2 = getSecondSensor();
        if (s2 != NULL) s2->requestUpdateFromLayout();
    }
}

/*public*/ void AbstractTurnout::setInverted(bool inverted)
{
 bool oldInverted = _inverted;
 _inverted = inverted;
 if (oldInverted != _inverted)
 {
  firePropertyChange("inverted", QVariant(oldInverted),
          QVariant(_inverted));
  int state = _knownState;
  if (state == Turnout::THROWN) {
      newKnownState(Turnout::CLOSED);
  } else if (state == Turnout::CLOSED) {
      newKnownState(Turnout::THROWN);
  }
 }
}

/**
 * Get the turnout inverted state. If true, commands sent to the layout are
 * reversed. Thrown becomes Closed, and Closed becomes Thrown.
 * <P>
 * Used in polling loops in system-specific code, so made final to allow
 * optimization.
 */
/*final public*/ bool AbstractTurnout::getInverted() {
    return _inverted;
}


/**
 * Determine if the turnouts can be inverted. If true inverted turnouts
 * supported.
 */

/*public*/ bool AbstractTurnout::canInvert() const {
    return false;
}

/**
 * Turnouts that are locked should only respond to JMRI commands to change
 * state. We simulate a locked turnout by monitoring the known state
 * (turnout feedback is required) and if we detect that the known state has
 * changed, negate it by forcing the turnout to return to the commanded
 * state. Turnout that have local buttons can also be locked if their
 * decoder supports it.
 *
 * @param locked
 */

/*public*/ void AbstractTurnout::setLocked(int turnoutLockout, bool locked) {
 bool firechange = false;
 if ((turnoutLockout & Turnout::CABLOCKOUT) > 0 && _cabLockout != locked)
 {
  firechange = true;
  if (canLock(Turnout::CABLOCKOUT))
  {
   _cabLockout = locked;
  }
  else
  {
   _cabLockout = false;
  }
 }
 if ((turnoutLockout & Turnout::PUSHBUTTONLOCKOUT) > 0
            && _pushButtonLockout != locked)
 {
  firechange = true;
  if (canLock(Turnout::PUSHBUTTONLOCKOUT))
  {
   _pushButtonLockout = locked;
   // now change pushbutton lockout state on layout
   turnoutPushbuttonLockout();
  }
  else
  {
   _pushButtonLockout = false;
  }
 }
 if (firechange)
  firePropertyChange("locked", QVariant(!locked), QVariant(locked));
}

/**
 * Determine if turnout is locked. Returns true if turnout is locked.
 * There are two types of locks, cab lockout, and pushbutton lockout.
 */
/*public*/ bool AbstractTurnout::getLocked(int turnoutLockout)
{
 if (turnoutLockout == Turnout::CABLOCKOUT)
  return _cabLockout;
 else if (turnoutLockout == Turnout::PUSHBUTTONLOCKOUT)
  return _pushButtonLockout;
 else if (turnoutLockout == (Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT))
  return _cabLockout || _pushButtonLockout;
 else
  return false;
}


/*public*/ bool AbstractTurnout::canLock(int turnoutLockout) {
 Q_UNUSED(turnoutLockout)
    return false;
}

/*public*/ void AbstractTurnout::enableLockOperation(int turnoutLockout, bool enabled) {
 Q_UNUSED(turnoutLockout)
 Q_UNUSED(enabled)
}

/**
 *  When true, report to console anytime a cab attempts to change the
 *  state of a turnout on the layout.  When a turnout is cab locked, only
 *  JMRI is allowed to change the state of a turnout.
 */
/*public*/ void AbstractTurnout::setReportLocked(bool reportLocked) {
    bool oldReportLocked = _reportLocked;
    _reportLocked = reportLocked;
    if (oldReportLocked != _reportLocked)
        firePropertyChange("reportlocked", QVariant(oldReportLocked),
                QVariant(_reportLocked));
}

/**
 *  When true, report to console anytime a cab attempts to change the
 *  state of a turnout on the layout.  When a turnout is cab locked, only
 *  JMRI is allowed to change the state of a turnout.
 */
/*public*/ bool AbstractTurnout::getReportLocked() {
    return _reportLocked;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QStringList AbstractTurnout::getValidDecoderNames() {
    return _validDecoderNames;
}


/*public*/ QString AbstractTurnout::getDecoderName() {
    return _decoderName;
}

/*public*/ void AbstractTurnout::setDecoderName(QString decoderName) {
    _decoderName = decoderName;
}

/*abstract protected*/ void AbstractTurnout::turnoutPushbuttonLockout(bool locked)
{
 Q_UNUSED(locked)
}

/*protected*/ void AbstractTurnout::turnoutPushbuttonLockout() {
    turnoutPushbuttonLockout(_pushButtonLockout);
}

/*
 * Support for turnout automation (see TurnoutOperation and related classes)
 */

#if 1 // TODO:
/*public*/ TurnoutOperator* AbstractTurnout::getCurrentOperator() {
    return myOperator;
}
#endif
/*public*/ TurnoutOperation* AbstractTurnout::getTurnoutOperation() {
    return myTurnoutOperation;
}

/*public*/ void AbstractTurnout::setTurnoutOperation(TurnoutOperation* toper) {
    TurnoutOperation* oldOp = myTurnoutOperation;
    if (myTurnoutOperation != NULL) {
        myTurnoutOperation->removePropertyChangeListener(this);
    }
    myTurnoutOperation = toper;
    if (myTurnoutOperation != NULL) {
        myTurnoutOperation->addPropertyChangeListener(this);
    }
    firePropertyChange("TurnoutOperationState", VPtr<TurnoutOperation>::asQVariant(oldOp), VPtr<TurnoutOperation>::asQVariant(myTurnoutOperation));
}

/*protected*/ void AbstractTurnout::operationPropertyChange(PropertyChangeEvent* evt) {
    if ((SwingPropertyChangeSupport*)evt->getSource() == myTurnoutOperation)
    {
        if (((TurnoutOperation*) evt->getSource())->isDeleted()) {
            setTurnoutOperation(NULL);
        }
    }
}

/*public*/ bool AbstractTurnout::getInhibitOperation() {
    return inhibitOperation;
}

/*public*/ void AbstractTurnout::setInhibitOperation(bool io) {
    inhibitOperation = io;
}
#if 1 // TODO:

/**
 * find the TurnoutOperation class for this turnout, and get an instance
 * of the corresponding operator
 * Override this function if you want another way to choose the operation
 * @return	newly-instantiated TurnoutOPerator, or NULL if nothing suitable
 */
/*protected*/ TurnoutOperator*  AbstractTurnout::getTurnoutOperator()
{
 TurnoutOperator* to = NULL;
 if (!inhibitOperation)
 {
  if (myTurnoutOperation != nullptr)
  {
   to = ((NoFeedbackTurnoutOperation*) myTurnoutOperation)->getOperator(this);
  }
  else
  {
   TurnoutOperation* toper = TurnoutOperationManager::getInstance()->getMatchingOperation((Turnout*)this, getFeedbackModeForOperation());
   if (toper != nullptr)
   {
    to = ((NoFeedbackTurnoutOperation*)toper)->getOperator(this);
   }
  }
 }
 return to;
}
#endif
/**
 * Allow an actual turnout class to transform private
 * feedback types into ones that the generic turnout operations know about
 * @return	apparent feedback mode for operation lookup
 */
/*protected*/ int AbstractTurnout::getFeedbackModeForOperation() {
    return getFeedbackMode();
}


/*public*/ void AbstractTurnout::provideFirstFeedbackSensor(QString pName) /*throw(JmriException)*/
{
 if (InstanceManager::sensorManagerInstance()!=NULL)
 {
  if (pName.isEmpty())
   provideFirstFeedbackNamedSensor(NULL);
  else
  {
   Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(pName);
   if (sensor != NULL)
   {
    provideFirstFeedbackNamedSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
   }
   else
   {
    log->error("Sensor '"+pName+"' not available");
                throw new JmriException("Sensor '"+pName+"' not available");
   }
  }
 }
 else
 {
  log->error("No SensorManager for this protocol");
  throw new JmriException("No Sensor Manager Found");
 }
}

/*public*/ void AbstractTurnout::provideFirstFeedbackNamedSensor(NamedBeanHandle<Sensor*>*s)
{
 if (getFirstSensor() != NULL)
 {
  (getFirstSensor())->removePropertyChangeListener(this);
  Sensor* anb = getFirstSensor();
  disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 _firstNamedSensor = s;

 // if need be, set listener
 if (getFirstSensor() != NULL)
 {
  ((AbstractNamedBean*)getFirstSensor())->addPropertyChangeListener(this, s->getName(), "Feedback Sensor for " + getDisplayName());
  Sensor* anb = getFirstSensor();
  connect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ Sensor* AbstractTurnout::getFirstSensor()
{
 if (_firstNamedSensor==NULL)
 {
  return NULL;
 }
 return _firstNamedSensor->getBean();
}

/*public*/ NamedBeanHandle <Sensor*>* AbstractTurnout::getFirstNamedSensor() {
    return _firstNamedSensor;
}

/*public*/ void AbstractTurnout::provideSecondFeedbackSensor(QString pName) /*throw(JmriException)*/
{

 if (InstanceManager::sensorManagerInstance()!=NULL)
 {
  if (pName.isEmpty())
   provideSecondFeedbackNamedSensor(NULL);
  else
  {
   Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(pName);
   if (sensor != NULL)
   {
             //InstanceManager::getDefault(NamedBeanHandleManager<Sensor*>)->metaObject()->className();
    provideSecondFeedbackNamedSensor(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(pName, sensor));
   }
   else
   {
    log->error("Sensor '"+pName+"' not available");
    throw new JmriException("Sensor '"+pName+"' not available");
   }
  }
 }
 else
 {
  log->error("No SensorManager for this protocol");
  throw new JmriException("No Sensor Manager Found");
 }
}

/*public*/ void AbstractTurnout::provideSecondFeedbackNamedSensor(NamedBeanHandle<Sensor*>* s)
{
 // if need be, clean listener
 if (getSecondSensor() != NULL)
 {
  ((AbstractSensor*)getSecondSensor())->removePropertyChangeListener(this);
  Sensor* anb = getSecondSensor();
  disconnect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 _secondNamedSensor = s;

 // if need be, set listener
 if (getSecondSensor() != NULL)
 {
  ((AbstractNamedBean*)getSecondSensor())->addPropertyChangeListener(this, s->getName(), "Feedback Sensor for " + getDisplayName());
  Sensor* anb = getSecondSensor();
  connect(anb->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/*public*/ Sensor* AbstractTurnout::getSecondSensor() 
{
 if (_secondNamedSensor==NULL)
 {
  return NULL;
 }
 return _secondNamedSensor->getBean();
}

/*public*/ NamedBeanHandle <Sensor*>* AbstractTurnout::getSecondNamedSensor() {
    return _secondNamedSensor;
}

/*public*/ void AbstractTurnout::setInitialKnownStateFromFeedback()
{
 if (_activeFeedbackType == Turnout::ONESENSOR)
 {
  // ONESENSOR feedback
  if (getFirstSensor() != NULL)
  {
   // set according to state of sensor
   int sState = ((AbstractSensor*)getFirstSensor())->getKnownState();
   if (sState == Sensor::ACTIVE)
    newKnownState(Turnout::THROWN);
   else if (sState == Sensor::INACTIVE)
    newKnownState(Turnout::CLOSED);
   }
  else
  {
   log->warn("expected Sensor 1 not defined - " + getSystemName());
   newKnownState(UNKNOWN);
  }
 }
 else if (_activeFeedbackType == Turnout::TWOSENSOR)
 {
  // TWOSENSOR feedback
  int s1State = Sensor::UNKNOWN;
  int s2State = Sensor::UNKNOWN;
  if (getFirstSensor() != NULL)
   s1State = ((AbstractSensor*)getFirstSensor())->getKnownState();
  else
  {
   log->warn("expected Sensor 1 not defined - " + getSystemName());
  }
  if (getSecondSensor() != NULL)
   s2State = ((AbstractSensor*)getSecondSensor())->getKnownState();
  else
  {
   log->warn("expected Sensor 2 not defined - " + getSystemName());
  }
  // set Turnout state according to sensors
  if ((s1State == Sensor::ACTIVE) && (s2State == Sensor::INACTIVE))
   newKnownState(Turnout::THROWN);
  else if ((s1State == Sensor::INACTIVE) && (s2State == Sensor::ACTIVE))
   newKnownState(Turnout::CLOSED);
  else if (_knownState != UNKNOWN)
    newKnownState(UNKNOWN);
 }
 else
 {
  // nothing required at this time for other modes
 }
}

/**
 * React to sensor changes by changing the KnownState
 * if using an appropriate sensor mode
 */

/*public*/ void AbstractTurnout::propertyChange(PropertyChangeEvent* evt)
{
 if ((TurnoutOperation*)evt->getSource() == myTurnoutOperation)
 {
  operationPropertyChange(evt);
 }
 else if ((Sensor*)evt->getSource() == getFirstSensor()
            || (Sensor*)evt->getSource() == getSecondSensor())
 {
  sensorPropertyChange(evt);
 }
}

/*protected*/ void AbstractTurnout::sensorPropertyChange(PropertyChangeEvent* evt)
{
 // top level, find the mode

 if (_activeFeedbackType == Turnout::ONESENSOR)
 {
  // check for match
  if ((Sensor*)evt->getSource() == getFirstSensor())
  {
   // check change type
   if (evt->getPropertyName()!=("KnownState"))
    return;
   // OK, now have to handle it
   int mode = ((/*Integer*/int) evt->getNewValue().toInt());
   if (mode == Sensor::ACTIVE)
    newKnownState(Turnout::THROWN);
   else if (mode == Sensor::INACTIVE)
    newKnownState(Turnout::CLOSED);
  }
  else
  {
   // unexected mismatch
   log->warn("expected sensor " + getFirstNamedSensor()->getName()
                    + " was " + ((Sensor*) evt->getSource())->getSystemName());
  }
        // end ONESENSOR block
 }
 else if (_activeFeedbackType == Turnout::TWOSENSOR)
 {
  // check change type
  if (evt->getPropertyName()!=("KnownState"))
            return;
  // OK, now have to handle it
  int mode =  evt->getNewValue().toInt();
  Sensor* s = (Sensor*) evt->getSource();
  if ((mode == Sensor::ACTIVE) && (s == getSecondSensor()))
   newKnownState(Turnout::CLOSED);
  else if ((mode == Sensor::ACTIVE) && (s == getFirstSensor()))
   newKnownState(Turnout::THROWN);
  else if (!(((((AbstractSensor*)getFirstSensor())->getKnownState() == Sensor::ACTIVE) && (((AbstractSensor*)getSecondSensor())
                ->getKnownState() == Sensor::INACTIVE)) || ((((AbstractSensor*)getFirstSensor())
                ->getKnownState() == Sensor::INACTIVE) && (((AbstractSensor*)getSecondSensor())
                ->getKnownState() == Sensor::ACTIVE)))) // INCONSISTENT if sensor has transitioned to an inconsistent state
  newKnownState(INCONSISTENT);
        // end TWOSENSOR block
 }
 else
  // don't need to do anything
  return;
}

/*public*/ void AbstractTurnout::setBinaryOutput(bool state) 
{
 Q_UNUSED(state)
 binaryOutput = true;
}


/*public*/ void AbstractTurnout::dispose()
{
 if (getFirstSensor() != NULL)
 {
  ((AbstractSensor*)getFirstSensor())->removePropertyChangeListener(this);
 }
 _firstNamedSensor = NULL;
 if (getSecondSensor() != NULL)
 {
  ((AbstractSensor*)getSecondSensor())->removePropertyChangeListener(this);
    }
    _secondNamedSensor = NULL;
//    super.dispose();
}


/*public*/ float AbstractTurnout::getDivergingLimit()
{
 if ((_divergeSpeed==NULL) || (_divergeSpeed==""))
  return -1;

 QString speed = _divergeSpeed;
 if(_divergeSpeed==("Global")){
   speed = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultThrownSpeed();
    }
    if(speed==("Block"))
        return -1;
    try {
        return speed.toFloat();
        //return Integer.parseInt(_blockSpeed);
    }catch (NumberFormatException* nx) {
        //considered normal if the speed is not a number.
    }
    try
    {
      return static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
    }
    catch (Exception* ex) {
      return -1;
    }
}

/*public*/ QString AbstractTurnout::getDivergingSpeed() {
    if(_divergeSpeed==("Global")){
        return ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultThrownSpeed());
    }
    if(_divergeSpeed==("Block"))
        return ("Use Block Speed");
    return _divergeSpeed;
}

/*public*/ void AbstractTurnout::setDivergingSpeed(QString s) const /*throw(JmriException)*/ {
    if(s.isEmpty())
        throw new JmriException("Value of requested turnout thrown speed can not be NULL");
    if(_divergeSpeed==(s))
        return;
    if (s.contains("Global"))
        s = "Global";
    else if (s.contains("Block"))
        s="Block";
    else {

        bool ok;
            s.toFloat(&ok);
        if(!ok) {
            try{
             ((SignalSpeedMap*)InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(s);
            } catch (Exception* ex){
                throw new JmriException("Value of requested block speed is not valid");
            }
        }
    }
    QString oldSpeed = _divergeSpeed;
    _divergeSpeed=s;
    firePropertyChange("TurnoutDivergingSpeedChange", oldSpeed, s);
}

/*public*/ float AbstractTurnout::getStraightLimit() {
    if ((_straightSpeed==NULL) || (_straightSpeed==""))
        return -1;
    QString speed = _straightSpeed;
    if(_straightSpeed==("Global")){
        speed = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultClosedSpeed();
    } else if (speed==("Block")){
        return -1;
    }
    try {
        return speed.toFloat();
    }
 catch (NumberFormatException* nx)
 {
        //considered normal if the speed is not a number.
 }
 try
 {
    return static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(speed);
 }
 catch (Exception* ex)
 {
  return -1;
 }
}

/*public*/ QString AbstractTurnout::getStraightSpeed() {
    if(_straightSpeed==("Global"))
        return ("Use Global " + ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getDefaultClosedSpeed());
    if(_straightSpeed==("Block"))
        return (tr("Use Block Speed"));
    return _straightSpeed;
}

/*public*/ void AbstractTurnout::setStraightSpeed(QString s) const /*throw(JmriException)*/
{
    if(s==NULL)
        throw new JmriException("Value of requested turnout straight speed can not be NULL");
    if(_straightSpeed==(s))
        return;
    if (s.contains("Global"))
        s = "Global";
    else if (s.contains("Block"))
        s= "Block";
    else {
#if 1 // TODO:
            //Float.parseFloat(s);
      bool bok;
      s.toFloat(&bok);
if(!bok)
{
 try{
    static_cast<SignalSpeedMap*>(InstanceManager::getDefault("SignalSpeedMap"))->getSpeed(s);
      } catch (Exception* ex){
          throw new JmriException("Value of requested turnout straight speed is not valid");
      }
     }
#endif
    }
    QString oldSpeed = _straightSpeed;
    _straightSpeed=s;
    firePropertyChange("TurnoutStraightSpeedChange", oldSpeed, s);
}

/** {@inheritDoc} */
//@Override
/*public*/ void AbstractTurnout::vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ {
    if ("CanDelete" ==(evt->getPropertyName())) { // NOI18N
        QVariant old = evt->getOldValue();
        if (old == VPtr<Sensor>::asQVariant(getFirstSensor()) || old == VPtr<Sensor>::asQVariant(getSecondSensor()) || old ==VPtr<Turnout>::asQVariant(leadingTurnout)) {
            PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
            throw new PropertyVetoException(tr("Sensor is in use by Turnout \"%1\" for feedback").arg(getDisplayName()), e); // NOI18N
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ QList<NamedBeanUsageReport*> AbstractTurnout::getUsageReport(NamedBean* bean) {
    QList<NamedBeanUsageReport*> report = QList<NamedBeanUsageReport*>();
    if (bean != nullptr) {
        if (bean->equals(getFirstSensor())) {
            report.append(new NamedBeanUsageReport("TurnoutFeedback1"));  // NOI18N
        }
        if (bean->equals(getSecondSensor())) {
            report.append(new NamedBeanUsageReport("TurnoutFeedback2"));  // NOI18N
        }
        if (bean->equals(getLeadingTurnout())) {
            report.append(new NamedBeanUsageReport("LeadingTurnout")); // NOI18N
        }
    }
    return report;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool AbstractTurnout::isCanFollow() {
    return false;
}

/**
 * {@inheritDoc}
 */
//@Override
//@CheckForNull
/*public*/ Turnout* AbstractTurnout::getLeadingTurnout() {
    return leadingTurnout;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractTurnout::setLeadingTurnout(/*@CheckForNull*/ Turnout* turnout) {
    if (isCanFollow()) {
        Turnout* old = leadingTurnout;
        leadingTurnout = turnout;
        firePropertyChange("LeadingTurnout", VPtr<Turnout>::asQVariant(old), VPtr<Turnout>::asQVariant(leadingTurnout));
        if (old != nullptr) {
            old->removePropertyChangeListener("KnownState", this);
        }
        if (leadingTurnout != nullptr) {
            leadingTurnout->addPropertyChangeListener("KnownState", this);
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractTurnout::setLeadingTurnout(/*@CheckForNull*/ Turnout* turnout, bool followingCommandedState) {
    setLeadingTurnout(turnout);
    setFollowingCommandedState(followingCommandedState);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool AbstractTurnout::isFollowingCommandedState() {
    return followingCommandedState;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void AbstractTurnout::setFollowingCommandedState(bool following) {
    followingCommandedState = following;
}
/*static*/ Logger* AbstractTurnout::log = LoggerFactory::getLogger("AbstractTurnout");
