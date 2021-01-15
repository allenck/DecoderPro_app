#include "defaultroute.h"
#include "exceptions.h"
#include "instancemanager.h"
#include "sound.h"
#include "jmriscriptenginemanager.h"
#include "fileutil.h"

//DefaultRoute::DefaultRoute(QObject *parent) :
//    AbstractNamedBean(parent)
//{
//}
/**
 * Class providing the basic logic of the Route interface.
 *
 * @author	Dave Duchamp Copyright (C) 2004
 * @author Bob Jacobsen Copyright (C) 2006, 2007
 * @author Simon Reader Copyright (C) 2008
 * @author Pete Cressman Copyright (C) 2009
 *
 * @version     $Revision: 22198 $
 */
//import java.beans.PropertyChangeListener;
//import java.beans.PropertyChangeEvent;
//import java.util.ArrayList;
//import jmri.*;

///*public*/ class DefaultRoute extends AbstractNamedBean
//    implements Route, java.io.Serializable {

/*public*/ DefaultRoute::DefaultRoute(QString systemName, QString userName,QObject *parent) : Route(systemName.toUpper(), userName, parent)
{
 //super(systemName.toUpperCase(), userName);
 init();
}

/*public*/ DefaultRoute::DefaultRoute(QString systemName,QObject *parent) : Route(systemName.toUpper(), "", parent)
{
 //super(systemName.toUpperCase());
 init();
}

void DefaultRoute::init()
{
    log = new Logger("DefaultRoute");
/**
 *  Persistant instance variables (saved between runs)
 */
 mControlTurnout = "";
 mControlNamedTurnout = NULL;
 mControlTurnoutState = Turnout::THROWN;
  mDelay = 0;

 mLockControlTurnout = "";
 mLockControlNamedTurnout = NULL;
 mLockControlTurnoutState = Turnout::THROWN;

 mTurnoutsAlignedSensor = "";
 mTurnoutsAlignedNamedSensor = NULL;

 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");

 _controlSensorList = new QList<ControlSensor*>();
 mTurnoutListener = NULL;
 mLockTurnoutListener = NULL;
 _outputTurnoutList = new QList<OutputTurnout*>();


 /**
  *  Operational instance variables (not saved between runs)
  */
 _outputSensorList = new QList<OutputSensor*>();
  busy = false;
 _enabled = true;
 _locked = false;
}

/*public*/ bool DefaultRoute::getEnabled() const{
    return _enabled;
}
/*public*/ void DefaultRoute::setEnabled(bool v) {
    bool old = _enabled;
    _enabled = v;
    if (old != v) firePropertyChange("Enabled", QVariant(old), QVariant(v));
}

/*public*/ bool DefaultRoute::getLocked() {
     return _locked;
}
/*public*/ void DefaultRoute::setLocked(bool v) {
    lockTurnouts(v);
    bool old = _locked;
    _locked = v;
    if (old != v) firePropertyChange("Locked", QVariant(old), QVariant(v));
}
/**
 * Determine if route can be locked. Requres at least one turnout that can
 * be locked
 */
/*public*/ bool DefaultRoute::canLock() {
    for (int i=0; i<_outputTurnoutList->size(); i++) {
        if (((AbstractTurnout*)_outputTurnoutList->at(i)->getTurnout())->canLock(Turnout::CABLOCKOUT)) {
            return true;
        }
    }
    return false;
}


/**
 * Add an output Turnout to this Route
 * @param turnoutName The turnout system name
 * @param turnoutState must be Turnout.CLOSED, Turnout.THROWN, or Route.TOGGLE,
 *      which determines how the Turnout is to be switched when this Route is set
 */
/*public*/ bool DefaultRoute::addOutputTurnout(QString turnoutName, int turnoutState) {
    OutputTurnout* outputTurnout = new OutputTurnout(turnoutName, this);
    if (!outputTurnout->setState(turnoutState) ) {
        return false;
    }
    _outputTurnoutList->append(outputTurnout);
    return true;
}

/**
 * Delete all output Turnouts from this Route
 */
/*public*/ void DefaultRoute::clearOutputTurnouts() {
    _outputTurnoutList = new QList<OutputTurnout*>();
}

/*public*/ int DefaultRoute::getNumOutputTurnouts() {
    return _outputTurnoutList->size();
}

/**
 * Method to get a Route Turnout Name by Index
 *  Returns NULL if there is no turnout with that index
 */
/*public*/ QString DefaultRoute::getOutputTurnoutByIndex(int index)
{
    if(index >= _outputTurnoutList->size()) return NULL;
//    try {
        return _outputTurnoutList->at(index)->getName();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}

/**
 * Method to inquire if a Turnout is included in this Route.
 * <P>
 * Complicated by the fact that either the argument or the
 * internal names might be user or system names
 */
/*public*/ bool DefaultRoute::isOutputTurnoutIncluded(QString turnoutName)
{
 Turnout* t1 = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(turnoutName);
 for (int i=0; i<_outputTurnoutList->size(); i++)
 {
  if ( _outputTurnoutList->at(i)->getTurnout() == t1 )
  {
   // Found turnout
   return true;
  }
 }
 return false;
}

/**
 * Method to get the Set State of a Turnout included in this Route
 * <P>
 * Noth the input and internal names can be either a user or system name
 * @return -1 if there are less than 'k' Turnouts defined
 */
/*public*/ int DefaultRoute::getOutputTurnoutSetState(QString name) {
    Turnout* t1 = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
    for (int i=0; i<_outputTurnoutList->size(); i++) {
        if( _outputTurnoutList->at(i)->getTurnout() == t1 ) {
            // Found turnout
            return _outputTurnoutList->at(i)->getState();
        }
    }
    return -1;
}

/**
 * Method to return the 'k'th Turnout of the Route.
 * @return NULL if there are less than 'k' Turnouts defined
 */
/*public*/ Turnout* DefaultRoute::getOutputTurnout(int k)
{
    if(k >= _outputTurnoutList->size()) return NULL;
//    try {
        return _outputTurnoutList->at(k)->getTurnout();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}

/**
 * Method to get the desired state of 'k'th Turnout of the Route.
 *   Returns -1 if there are less than 'k' Turnouts defined
 */
/*public*/ int DefaultRoute::getOutputTurnoutState(int k)
{
    if(k >= _outputTurnoutList->size()) return -1;
//    try {
        return _outputTurnoutList->at(k)->getState();
//    } catch (IndexOutOfBoundsException ioob) {
//        return -1;
//    }
}

// output sensors (new interface only)

/**
 * Add an output Sensor to this Route
 * @param sensorName The sensor name either system or user
 * @param state must be Sensor.ACTIVE, Sensor.INACTIVE, or Route.TOGGLE,
 *      which determines how the Sensor is to be set when this Route is set
 */
/*public*/ bool DefaultRoute::addOutputSensor(QString sensorName, int state) {
    OutputSensor* outputSensor = new OutputSensor(sensorName,this);
    if (!outputSensor->setState(state) ) {
        return false;
    }
    _outputSensorList->append(outputSensor);
    return true;
}

/**
 * Delete all output Sensors from this Route
 */
/*public*/ void DefaultRoute::clearOutputSensors() {
    _outputSensorList = new QList<OutputSensor*>();
}

/*public*/ int DefaultRoute::getNumOutputSensors() {
    return _outputSensorList->size();
}

/**
 * Method to get an ouput Sensor name by Index
 *  Returns NULL if there is no sensor with that index
 */
/*public*/ QString DefaultRoute::getOutputSensorByIndex(int index)
{
    if(index >= _outputSensorList->size()) return NULL;
//    try {
        return _outputSensorList->at(index)->getName();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}

/**
 * Method to inquire if a Sensor is included in this Route
 */
/*public*/ bool DefaultRoute::isOutputSensorIncluded(QString sensorName) {
    Sensor* s1 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(sensorName);
    for (int i=0; i<_outputSensorList->size(); i++) {
        if ( _outputSensorList->at(i)->getSensor() == s1 ) {
            // Found turnout
            return true;
        }
    }
    return false;
}

/**
 * Method to get the Set State of a Sensor included in this Route
 *   If the Sensor is not found, -1 is returned.
 * <P>
 * Both the input or internal names can be either system or user names
 */
/*public*/ int DefaultRoute::getOutputSensorSetState(QString name) {
    Sensor* s1 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
    for (int i=0; i<_outputSensorList->size(); i++) {
        if( _outputSensorList->at(i)->getSensor() == s1 ) {
            // Found turnout
            return _outputSensorList->at(i)->getState();
        }
    }
    return -1;
}

/**
 * Method to return the 'k'th Sensor of the Route.
 * @return NULL if there are less than 'k' Sensors defined
 */
/*public*/ Sensor* DefaultRoute::getOutputSensor(int k)
{
 if(k >= _outputSensorList->size()) return NULL;

//    try {
        return _outputSensorList->at(k)->getSensor();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}

/**
 * Method to get the desired state of 'k'th Sensor of the Route.
 *   Returns -1 if there are less than 'k' Sensors defined
 */
/*public*/ int DefaultRoute::getOutputSensorState(int k)
{
    if(k >= _outputSensorList->size()) return -1;
//    try {
        return _outputSensorList->at(k)->getState();
//    } catch (IndexOutOfBoundsException ioob) {
//        return -1;
//    }
}


/**
 * Set name of script file to be run when Route is fired
 */
/*public*/ void DefaultRoute::setOutputScriptName(QString filename) {
    scriptFilename = filename;
}

/**
 * Get name of script file to be run when Route is fired
 */
/*public*/ QString DefaultRoute::getOutputScriptName() {
    return scriptFilename;
}

/**
 * Set name of sound file to be played when Route is fired
 */
/*public*/ void DefaultRoute::setOutputSoundName(QString filename) {
    soundFilename = filename;
}

/**
 * Get name of sound file to be played when Route is fired
 */
/*public*/ QString DefaultRoute::getOutputSoundName() {
    return soundFilename;
}

/**
 * Method to set turnouts aligned sensor
 */
/*public*/ void DefaultRoute::setTurnoutsAlignedSensor(QString sensorName){
    if (log->isDebugEnabled()) log->debug("setTurnoutsAlignedSensor "+getSystemName()+" "+sensorName);

    mTurnoutsAlignedSensor = sensorName;
    if( mTurnoutsAlignedSensor.isEmpty() || mTurnoutsAlignedSensor==("")){
        mTurnoutsAlignedNamedSensor = NULL;
        return;
    }
    Sensor* s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                        provideSensor(mTurnoutsAlignedSensor);
    if(s!=NULL)
       mTurnoutsAlignedNamedSensor = nbhm->getNamedBeanHandle(mTurnoutsAlignedSensor, s);
}

/**
 * Method to get turnouts aligned sensor
 */
/*public*/ QString DefaultRoute::getTurnoutsAlignedSensor(){
    if(mTurnoutsAlignedNamedSensor!=NULL){
        return mTurnoutsAlignedNamedSensor->getName();
    }
    return mTurnoutsAlignedSensor;
}

/*public*/ Sensor* DefaultRoute::getTurnoutsAlgdSensor(){
    if(mTurnoutsAlignedNamedSensor!=NULL){
        return mTurnoutsAlignedNamedSensor->getBean();
    }
    else if ( mTurnoutsAlignedSensor!=NULL && mTurnoutsAlignedSensor!=(""))
    {
        Sensor* s = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                            provideSensor(mTurnoutsAlignedSensor);
        if(s!=NULL)
           mTurnoutsAlignedNamedSensor = nbhm->getNamedBeanHandle(mTurnoutsAlignedSensor, s);
        else {
            log->error("Unable to create Turnout aligned Sensor " + mTurnoutsAlignedSensor + " for Route " + getDisplayName());
            return NULL;
        }
    }
    return NULL;

}
// Inputs ----------------

/**
 * Method to delete all control Sensors from this Route
 */
/*public*/ void DefaultRoute::clearRouteSensors() {
    _controlSensorList = new QList<ControlSensor*>();
}

/**
 * Method to add a Sensor to the list of control Sensors for this Route.
 * @param sensorName either a system or username of a sensor
 */
/*public*/ bool DefaultRoute::addSensorToRoute(QString sensorName, int mode) {
    if (_controlSensorList->size() >= Route::MAX_CONTROL_SENSORS) {
        // reached maximum
        log->warn("Reached maximum number of control Sensors for Route: "+ getSystemName() );
    }
    ControlSensor* sensor = new ControlSensor(sensorName,this);
    if (log->isDebugEnabled()) log->debug("addSensorToRoute "+getSystemName()+" "+sensorName);
    if (!sensor->setState(mode) )
    {
        return false;
    }
    _controlSensorList->append(sensor);
    return true;
}

/**
 * Method to get the Name of a control Sensor in this Route
 *  'index' is the index in the Sensor array of the requested
 *      Sensor.
 *  If there is no Sensor with that 'index', or if 'index'
 *      is not in the range 0 thru MAX_SENSORS-1, NULL is returned.
 */
/*public*/ QString DefaultRoute::getRouteSensorName(int index)
{
    if(index >= _controlSensorList->size()) return NULL;
//    try {
        return _controlSensorList->at(index)->getName();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}
/**
 * Method to get the control Sensor in this Route
 *  'index' is the index in the Sensor array of the requested
 *      Sensor.
 *  If there is no Sensor with that 'index', or if 'index'
 *      is not in the range 0 thru MAX_SENSORS-1, NULL is returned.
 */
/*public*/ Sensor* DefaultRoute::getRouteSensor(int index)
{
    if(index >= _controlSensorList->size()) return NULL;

//    try {
        return _controlSensorList->at(index)->getSensor();
//    } catch (IndexOutOfBoundsException ioob) {
//        return NULL;
//    }
}
/**
 * Method to get the mode associated with a control Sensor in this Route
 *  'index' is the index in the Sensor array of the requested
 *      Sensor.
 *  If there is no Sensor with that 'index', or if 'index'
 *      is not in the range 0 thru MAX_SENSORS-1,
 *      ONACTIVE is returned
 */
/*public*/ int DefaultRoute::getRouteSensorMode(int index) {
    if(index >= _controlSensorList->size()) return 0;
//    try {
        return _controlSensorList->at(index)->getState();
//    } catch (IndexOutOfBoundsException ioob) {
//        return 0;
//    }
}

/**
 * Method to set the Name of a control Turnout for this Route
 */
/*public*/ void DefaultRoute::setControlTurnout(QString turnoutName) {
    mControlTurnout = turnoutName;
    if( mControlTurnout==NULL || mControlTurnout==("")){
        mControlNamedTurnout = NULL;
        return;
    }
    Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                        provideTurnout(mControlTurnout);
    if(t!=NULL)
       mControlNamedTurnout = nbhm->getNamedBeanHandle(mControlTurnout, t);
}

/**
 * Method to get the Name of a control Turnout for this Route
 */
/*public*/ QString DefaultRoute::getControlTurnout() {
    if(mControlNamedTurnout!=NULL)
        return mControlNamedTurnout->getName();
    return mControlTurnout;
}

/*public*/ Turnout* DefaultRoute::getCtlTurnout(){
    if(mControlNamedTurnout!=NULL){
        return mControlNamedTurnout->getBean();
    }
    else if( mControlTurnout!=NULL && mControlTurnout==("")){
        Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                            provideTurnout(mControlTurnout);
        if(t!=NULL)
           mControlNamedTurnout = nbhm->getNamedBeanHandle(mControlTurnout, t);
        else {
            log->error("Unable to create control turnout " + mControlTurnout + " for Route " + getDisplayName());
            return NULL;
        }
    }
    return NULL;
}

/**
 * Method to set the Name of a lock control Turnout for this Route
 */
/*public*/ void DefaultRoute::setLockControlTurnout(QString turnoutName) {
    mLockControlTurnout = turnoutName;
    if( mLockControlTurnout==NULL || mLockControlTurnout==("")){
        mLockControlNamedTurnout = NULL;
        return;
    }
    Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                        provideTurnout(mLockControlTurnout);
    if(t!=NULL)
       mLockControlNamedTurnout = nbhm->getNamedBeanHandle(mLockControlTurnout, t);
}

/**
 * Method to get the Name of a lock control Turnout for this Route
 */
/*public*/ QString DefaultRoute::getLockControlTurnout() {
    if(mLockControlNamedTurnout!=NULL)
        return mLockControlNamedTurnout->getName();
    return mLockControlTurnout;
}

/*public*/ Turnout* DefaultRoute::getLockCtlTurnout(){
    if(mLockControlNamedTurnout!=NULL){
        return mLockControlNamedTurnout->getBean();
    }
    else if( mLockControlTurnout!=NULL && mLockControlTurnout!=("")){
        Turnout* t = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                            provideTurnout(mLockControlTurnout);
        if(t!=NULL)
           mLockControlNamedTurnout = nbhm->getNamedBeanHandle(mLockControlTurnout, t);
        else {
            log->error("Unable to create Lock control turnout " + mLockControlTurnout + " for Route " + getDisplayName());
            return NULL;
        }
    }
    return NULL;
}
/**
 * Method to set delay (milliseconds) between issuing Turnout commands
 */
/*public*/ void DefaultRoute::setRouteCommandDelay(int delay) {
    if (delay >= 0)
        mDelay = delay;
}

/**
 * Method to get delay (milliseconds) between issuing Turnout commands
 */
/*public*/ int DefaultRoute::getRouteCommandDelay() {
    return mDelay;
}

/**
 * Method to set the State of control Turnout that fires this Route
 */
/*public*/ void DefaultRoute::setControlTurnoutState(int turnoutState) {
    if ( (turnoutState == Route::ONTHROWN)
           || (turnoutState == Route::ONCLOSED)
           || (turnoutState == Route::ONCHANGE)
           || (turnoutState == Route::VETOCLOSED)
           || (turnoutState == Route::VETOTHROWN)
        ) {
        mControlTurnoutState = turnoutState;
    } else {
        log->error("Attempt to set invalid control Turnout state for Route.");
    }
}

/**
 * Method to get the State of control Turnout that fires this Route
 */
/*public*/ int DefaultRoute::getControlTurnoutState() {
    return (mControlTurnoutState);
}

/**
 * Method to set the State of lock control Turnout
 */
/*public*/ void DefaultRoute::setLockControlTurnoutState(int turnoutState) {
    if ((turnoutState == Route::ONTHROWN)
            || (turnoutState == Route::ONCLOSED)
            || (turnoutState == Route::ONCHANGE)) {
        mLockControlTurnoutState = turnoutState;
    } else {
        log->error("Attempt to set invalid lock control Turnout state for Route.");
    }
}

/**
 * Method to get the State of lock control Turnout
 */
/*public*/ int DefaultRoute::getLockControlTurnoutState() {
    return (mLockControlTurnoutState);
}

/**
 * Lock or unlock turnouts that are part of a route
 */
/*private*/ void DefaultRoute::lockTurnouts(bool lock) {
    // determine if turnout should be locked
    for (int i=0; i < _outputTurnoutList->size(); i++) {
        _outputTurnoutList->at(i)->getTurnout()->setLocked(
            Turnout::CABLOCKOUT + Turnout::PUSHBUTTONLOCKOUT, lock);
    }
}


/**
 * Method to set the Route
 * Sets all Route Turnouts to the state shown in the Route definition
 * This call is ignored if the Route is 'busy', i.e., if there is a
 *    thread currently sending commands to this Route's turnouts.
 */
/*public*/ void DefaultRoute::setRoute()
{
 if ((_outputTurnoutList->size()>0)
            || (_outputSensorList->size()>0)
            || (soundFilename != NULL)
            || (scriptFilename != NULL)
        )
 {
  if (!busy)
  {
   setRouteBusy();
   SetRouteThread* thread = new SetRouteThread(this);
   thread->start();
  }
 }
}

/**
 * Handle sensor update event to see if that will set the route.
 * <P>
 * Called when a "KnownState" event is received, it assumes that
 * only one sensor is changing right now, so can use state calls
 * for everything other than this sensor.
 *<P>
 * This will fire the route if the conditions are correct
 * <P>
 * Returns noting explicitly, but has the side effect of firing route
 */
/*protected*/ void DefaultRoute::checkSensor(int newState, int oldState, Sensor* sensor)
{
    // check for veto of change
    if (isVetoed()) return; // don't fire

    QString name = sensor->getSystemName();
    if (log->isDebugEnabled()) log->debug("check Sensor "+name+" for "+getSystemName());
    bool fire = false;  // dont fire unless we find something
    for (int i=0; i<_controlSensorList->size(); i++) {
        if (getRouteSensor(i)==(sensor)) {
            // here for match, check mode & handle onActive, onInactive
            int mode = getRouteSensorMode(i);
            if (log->isDebugEnabled()) log->debug("match mode: "+QString("%1").arg(mode)+" new state: "+QString("%1").arg(newState)+" old state: "+QString("%1").arg(oldState));

            // if in target mode, note whether to act
            if (  ( (mode==Route::ONACTIVE) && (newState==Sensor::ACTIVE) )
                || ( (mode==Route::ONINACTIVE) && (newState==Sensor::INACTIVE) )
                || ( (mode==Route::ONCHANGE) && (newState!=oldState) )
                )
               fire = true;

            // if any other modes, just skip because
            // the sensor might be in list more than once
        }
    }

    log->debug("check activated");
    if (!fire) return;

    // and finally set the route
    if (log->isDebugEnabled()) log->debug("call setRoute for "+getSystemName());
    setRoute();
}

/**
 * Turnout has changed, check to see if this fires.
 * Will fire route if appropriate
 */
 void DefaultRoute::checkTurnout(int newState, int oldState, Turnout* /*t*/) {
    if (isVetoed()) return; // skip setting route
    switch (mControlTurnoutState) {
        case Route::ONCLOSED:
            if (newState == Turnout::CLOSED) setRoute();
            return;
        case Route::ONTHROWN:
            if (newState == Turnout::THROWN) setRoute();
            return;
        case Route::ONCHANGE:
            if (newState != oldState) setRoute();
            return;
        default:
            // if not a firing state, return
            return;
    }
}

 /**
  * Turnout has changed, check to see if this
  * will lock or unlock route
  */
  void DefaultRoute::checkLockTurnout(int newState, int oldState, Turnout* /*t*/) {
     switch (mLockControlTurnoutState) {
     case Route::ONCLOSED:
         if (newState == Turnout::CLOSED) setLocked(true);
            else setLocked(false);
         return;
     case Route::ONTHROWN:
         if (newState == Turnout::THROWN) setLocked(true);
            else setLocked(false);
         return;
     case Route::ONCHANGE:
         if (newState != oldState){
             if (getLocked())
                    setLocked(false);
             else
                 setLocked(true);
         }
         return;
     default:
         // if none, return
         return;
     }
 }

/**
 * Method to check if the turnouts for this route are correctly aligned.
 *  Sets turnouits aligned sensor (if there is one) to active if the turnouts are aligned.
 *  Sets the sensor to inactive if they are not aligned
 */
/*public*/ void DefaultRoute::checkTurnoutAlignment(){

    //check each of the output turnouts in turn
    //turnouts are deemed not aligned if:
    // - commanded and known states don't agree
    // - non-toggle turnouts known state not equal to desired state
    // turnouts aligned sensor is then set accordingly

    if (getTurnoutsAlgdSensor()!=NULL) {
        bool aligned = true;
        for (int k=0; k<_outputTurnoutList->size(); k++) {
            Turnout* t = _outputTurnoutList->at(k)->getTurnout();
            if (!t->isConsistentState()) {
                aligned= false;
                break;
            }
            int targetState = _outputTurnoutList->at(k)->getState();
            if (targetState!=Route::TOGGLE && targetState!=((AbstractTurnout*)t)->getKnownState()) {
                aligned= false;
                break;
            }
        }
        try {
            if (aligned) {
                ((AbstractSensor*)getTurnoutsAlgdSensor())->setKnownState(Sensor::ACTIVE);
            } else {
                ((AbstractSensor*)getTurnoutsAlgdSensor())->setKnownState(Sensor::INACTIVE);
            }
        } catch (JmriException ex) {
                log->warn("Exception setting sensor "+getTurnoutsAlignedSensor()+" in route");
        }
    }
}


/**
 * Method to activate the Route via Sensors and control Turnout
 * Sets up for Route activation based on a list of Sensors and a control Turnout
 * Registers to receive known state changes for output turnouts
 */
/*public*/ void DefaultRoute::activateRoute() {

    //register output turnouts to return Known State if a turnouts aligned sensor is defined
    if (getTurnoutsAlignedSensor()!=("")) {

        for (int k=0; k< _outputTurnoutList->size(); k++) {
            _outputTurnoutList->at(k)->addListener();
        }
    }

    for (int k=0; k< _controlSensorList->size(); k++) {
        _controlSensorList->at(k)->addListener();
    }
    if (getCtlTurnout()!=NULL)
    {
//        getCtlTurnout()->addPropertyChangeListener(mTurnoutListener =
//                                        new PropertyChangeListener());
        AbstractTurnout* t = (AbstractTurnout*)getCtlTurnout();
        connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), SLOT(propertyChange(PropertyChangeEvent*)));
//        {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    if (e.getPropertyName().equals("KnownState")) {
//                        int now = ((Integer) e.getNewValue()).intValue();
//                        int then = ((Integer) e.getOldValue()).intValue();
//                        checkTurnout(now, then, (Turnout)e.getSource());
//                    }
//                }
//            }, getControlTurnout(), "Route " + getDisplayName());
    }

    if (getLockCtlTurnout()!=NULL)
    {
//        getLockCtlTurnout()->addPropertyChangeListener(mLockTurnoutListener =
//                                        new PropertyChangeListener());
      AbstractTurnout* t = (AbstractTurnout*)getLockCtlTurnout();
      connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), SLOT(propertyChange(PropertyChangeEvent*)));
//        {
//                /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                    if (e.getPropertyName().equals("KnownState")) {
//                        int now = ((Integer) e.getNewValue()).intValue();
//                        int then = ((Integer) e.getOldValue()).intValue();
//                        checkLockTurnout(now, then, (Turnout)e.getSource());
//                    }
//                }
//            }, getLockControlTurnout(), "Route " + getDisplayName());
    }
// register for updates to the Output Turnouts
}

/*public*/ void DefaultRoute::propertyChange(PropertyChangeEvent* e) // SLOT[]
{
  if (e->getPropertyName()==("KnownState"))
  {
      int now =  e->getNewValue().toInt();
      int then = e->getOldValue().toInt();
      checkTurnout(now, then, (Turnout*)e->getSource());
  }
}

/**
 * Internal method to check whether
 * operation of the route has been vetoed by a sensor
 * or turnout setting.
 * @return true if veto, i.e. don't fire route; false if no veto, OK to
 */
bool DefaultRoute::isVetoed() {
    log->debug("check for veto");
    // check this route not enabled
    if (!_enabled) return true;

    // check sensors
    for (int i=0; i<_controlSensorList->size(); i++) {
        ControlSensor* controlSensor = _controlSensorList->at(i);
        int s = controlSensor->getSensor()->getKnownState();
        int mode = controlSensor->getState();
        if (  ( (mode==Route::VETOACTIVE) && (s==Sensor::ACTIVE) )
                || ( (mode==Route::VETOINACTIVE) && (s==Sensor::INACTIVE) ) )
             return true;  // veto set
    }
    // check control turnout
    if (getCtlTurnout() != NULL) {
        int tstate = getCtlTurnout()->getKnownState();
        if (mControlTurnoutState==Route::VETOCLOSED && tstate==Turnout::CLOSED) return true;
        if (mControlTurnoutState==Route::VETOTHROWN && tstate==Turnout::THROWN) return true;
    }
    return false;
}

/**
 * Method to deactivate the Route
 * Deactivates Route based on a list of Sensors and two control Turnouts
 */
/*public*/ void DefaultRoute::deActivateRoute() {
    // remove control turnout if there's one
    for (int k=0; k<_controlSensorList->size(); k++) {
        _controlSensorList->at(k)->removeListener();
    }
    if (mTurnoutListener!=NULL) {
        getCtlTurnout()->removePropertyChangeListener(mTurnoutListener);
        mTurnoutListener = NULL;
    }
    // remove lock control turnout if there's one
    if (mLockTurnoutListener!=NULL) {
        getLockCtlTurnout()->removePropertyChangeListener(mLockTurnoutListener);
        mLockTurnoutListener = NULL;
    }
    //remove listeners on output turnouts if there are any
    if (mTurnoutsAlignedSensor!=""){
        for (int k=0; k< _outputTurnoutList->size(); k++) {
            _outputTurnoutList->at(k)->removeListener();
        }
    }
}

/**
 * Method to set Route busy when commands are being issued to
 *   Route turnouts
 */
/*public*/ void DefaultRoute::setRouteBusy() {
    busy = true;
}

/**
 * Method to set Route not busy when all commands have been
 *   issued to Route turnouts
 */
/*public*/ void DefaultRoute::setRouteNotBusy() {
    busy = false;
}

/**
 * Method to query if Route is busy (returns true if commands are
 *   being issued to Route turnouts)
 */
/*public*/ bool DefaultRoute::isRouteBusy() {
    return (busy);
}

/**
 * Not needed for Routes - included to complete implementation of the NamedBean interface.
 */
/*public*/ int DefaultRoute::getState() {
    log->warn("Unexpected call to getState in DefaultRoute.");
    return UNKNOWN;
}


/**
 * Not needed for Routes - included to complete implementation of the NamedBean interface.
 */
/*public*/ void DefaultRoute::setState(int /*state*/) {
    log->warn("Unexpected call to setState in DefaultRoute.");
    return;
}

OutputSensor::OutputSensor(QString name, DefaultRoute* parent)
{
    log = new Logger("OutputSensor");
    Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->provideSensor(name);
    nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
    _sensor = nbhm->getNamedBeanHandle(name, sensor);
    _state = Sensor::ACTIVE;
    this->parent = parent;
}
QString OutputSensor::getName() {
    if (_sensor != NULL)
    {
        return _sensor->getName();
    }
    return NULL;
}
bool OutputSensor::setState(int state)
{
    if (_sensor == NULL) {
        return false;
    }
    if ((state!=Sensor::ACTIVE) && (state!=Sensor::INACTIVE) && (state!=Route::TOGGLE)) {
        log->warn("Illegal Sensor state for Route: "+getName() );
        return false;
    }
    _state = state;
    return true;
}
int OutputSensor::getState() {
    return _state;
}
Sensor* OutputSensor::getSensor()
{
 if(_sensor !=NULL)
  return _sensor->getBean();
 return NULL;
}

ControlSensor::ControlSensor (QString name, DefaultRoute* parent) : OutputSensor(name, parent)
{
 //super(name);
}
bool ControlSensor::setState(int state)
{
 if (_sensor == NULL)
 {
  return false;
 }
 _state = state;
 return true;
}
void ControlSensor::addListener()
{
 if(_sensor!=NULL)
 {
  ((AbstractNamedBean*)_sensor->getBean())->addPropertyChangeListener((PropertyChangeListener*)this, getName(), QString("Route ") + _sensor->getBean()->getDisplayName() + "Output Sensor");
  AbstractSensor* s = (AbstractSensor*)_sensor->getBean();
  connect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
void ControlSensor::removeListener()
{
 if(_sensor!=NULL)
 {
  _sensor->getBean()->removePropertyChangeListener((PropertyChangeListener*)this);
  AbstractSensor* s = (AbstractSensor*)_sensor->getBean();
  disconnect(s->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public*/ void ControlSensor::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("KnownState"))
 {
  int now = e->getNewValue().toInt();
  int then = e->getOldValue().toInt();
  parent->checkSensor(now, then, (Sensor*)e->getSource());
 }
}

OutputTurnout::OutputTurnout(QString name, DefaultRoute* parent)
{
 this->parent = parent;
 log = new Logger("OutputTurnout");
 nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");
 Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
 _turnout = nbhm->getNamedBeanHandle(name, turnout);
}

QString OutputTurnout::getName()
{
    if (_turnout != NULL)
    {
        return _turnout->getName();
    }
    return NULL;
}
bool OutputTurnout::setState(int state)
{
    if (_turnout == NULL) {
        return false;
    }
    if ((state!=Turnout::THROWN) && (state!=Turnout::CLOSED) && (state!=Route::TOGGLE)) {
        log->warn("Illegal Turnout state for Route: "+getName() );
        return false;
    }
    _state = state;
    return true;
}
int OutputTurnout::getState() {
    return _state;
}
Turnout* OutputTurnout::getTurnout() {
    if (_turnout!=NULL)
        return _turnout->getBean();
    return NULL;
}
void OutputTurnout::addListener()
{
 if(_turnout!=NULL)
 {
  _turnout->getBean()->addPropertyChangeListener(this, getName(), "Route " + _turnout->getBean()->getDisplayName() + " Output Turnout");
  AbstractTurnout* t = (AbstractTurnout*)_turnout->getBean();
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
void OutputTurnout::removeListener()
{
 if(_turnout!=NULL)
 {
  _turnout->getBean()->removePropertyChangeListener(this);
  AbstractTurnout* t = (AbstractTurnout*)_turnout->getBean();
  disconnect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}
/*public*/ void OutputTurnout::propertyChange(PropertyChangeEvent* e)
{
 if (e->getPropertyName()==("KnownState")
                 || e->getPropertyName()==("CommandedState"))
 {
  //check alignement of all turnouts in route
  parent->checkTurnoutAlignment();
 }
}

/**
 * Constructs the thread
 */
/*public*/ SetRouteThread::SetRouteThread(DefaultRoute* aRoute)
{
   r = aRoute;
   log = new Logger("SetRouteThread");
}

/**
* Runs the thread - performs operations in the order:
* <ul>
* <li>Run script (can run in parallel)
* <li>Play Sound (runs in parallel)
* <li>Set Turnouts
* <li>Set Sensors
* </UL>
*/
/*public*/ void SetRouteThread::run()
{
#if 1 // TODO:
   // run script defined for start of route set
   if ((r->getOutputScriptName() != nullptr) && (r->getOutputScriptName() != (""))) {
    JmriScriptEngineManager::getDefault()->runScript(new File(FileUtil::getExternalFilename(r->getOutputScriptName())));

   }

   // play sound defined for start of route set
   if ((r->getOutputSoundName() != "") && (r->getOutputSoundName() != ("")))
   {
    try {
        (new Sound(r->getOutputSoundName()))->play();
    } catch (NullPointerException ex) {
        log->error(tr("Cannot find file %1").arg(r->getOutputSoundName()));
    }
   }
#endif
 // set sensors at
 for (int k = 0; k < r->getNumOutputSensors(); k++)
 {
  Sensor* t = r->getOutputSensor(k);
  int state = r->getOutputSensorState(k);
  if (state==Route::TOGGLE)
  {
   int st = ((AbstractSensor*)t)->getKnownState();
   if (st==Sensor::ACTIVE)
   {
    state = Sensor::INACTIVE;
   }
   else
   {
    state = Sensor::ACTIVE;
   }
  }
  try
  {
   ((AbstractSensor*)t)->setKnownState(state);
  }
  catch (JmriException e)
  {
   log->warn("Exception setting sensor "+t->getSystemName()+" in route");
  }
  try
  {
   QThread::msleep(50);
  }
  catch (InterruptedException e)
  {
   //Thread.currentThread().interrupt(); // retain if needed later
   QThread::exit(0);
  }
 }

 // set turnouts
 int delay = r->getRouteCommandDelay();

 for (int k=0; k<r->getNumOutputTurnouts(); k++)
 {
  Turnout* t = r->getOutputTurnout(k);
  int state = r->getOutputTurnoutState(k);
  if (state==Route::TOGGLE)
  {
   int st = ((AbstractTurnout*)t)->getKnownState();
   if (st==Turnout::CLOSED)
   {
    state = Turnout::THROWN;
   }
   else
   {
    state = Turnout::CLOSED;
   }
  }
  ((AbstractTurnout*)t)->setCommandedState(state);
  try
  {
   QThread::msleep(250 + delay);
  }
  catch (InterruptedException e)
  {
   //Thread.currentThread().interrupt(); // retain if needed later
   QThread::exit(0);
  }
 }
 //set route not busy
 r->setRouteNotBusy();
 //check turnout alignment
 r->checkTurnoutAlignment();
}

