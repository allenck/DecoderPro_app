#include "defaultlightcontrol.h"
#include "loggerfactory.h"
#include "lighttableaction.h"
#include "loggingutil.h"
/**
 * Each LightControl object is linked to a specific Light, and provides one of
 * the controls available for switching the Light ON/OFF in response to time or
 * events occurring on the layout.
 * <p>
 * Each LightControl holds the information for one control of the parent Light.
 * <p>
 * Each Light may have as many controls as desired by the user. It is the user's
 * responsibility to ensure that the various control mechanisms do not conflict
 * with one another.
 * <p>
 * Available control types are those defined in the Light.java interface.
 * Control types: SENSOR_CONTROL FAST_CLOCK_CONTROL TURNOUT_STATUS_CONTROL
 * TIMED_ON_CONTROL TWO_SENSOR_CONTROL
 *
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 *
 * @author Dave Duchamp Copyright (C) 2010
 */
// /*public*/ class DefaultLightControl implements LightControl {

    /**
     * Main constructor methods
     */
    /*public*/ DefaultLightControl::DefaultLightControl() : LightControl(){
    }

    /*public*/ DefaultLightControl::DefaultLightControl(Light* l) : LightControl(){
        _parentLight = l;
    }


    /**
     * Create a New LightControl from existing,
     * for use when editing a LightControl
     *
     * @param lc the LightControl to be copied
     */
    /*public*/ DefaultLightControl::DefaultLightControl(/*@Nonnull*/ LightControl* lc) {
        this->_controlType = lc->getControlType();
        this->_controlSensorName = lc->getControlSensorName();
        this->_controlSensorSense = lc->getControlSensorSense();
        this->_fastClockOnHour = lc->getFastClockOnHour();
        this->_fastClockOnMin = lc->getFastClockOnMin();
        this->_fastClockOffHour = lc->getFastClockOffHour();
        this->_fastClockOffMin = lc->getFastClockOffMin();
        this->_controlTurnoutName = lc->getControlTurnoutName();
        this->_turnoutState = lc->getControlTurnoutState();
        this->_timedSensorName = lc->getTimedSensorName();
        this->_timeOnDuration = lc->getTimedOnDuration();
        this->_controlSensor2Name = lc->getControlSensor2Name();
    }

    /**
     * Test if a LightControl is equal to this one
     *
     * @param o the LightControl object to be checked
     * @return True if the LightControl is equal, else false
     */
    //@Override
    /*public*/ bool DefaultLightControl::equals(QObject* o) {
        if (!(qobject_cast< LightControl*>(o))) {
            return false;
        }
        LightControl* that = (LightControl*) o;
        if (that->getControlType() != this->_controlType) return false;
        bool _shouldReturn = true;
        switch(_controlType) {
            case Light::NO_CONTROL :
                break;
            case Light::SENSOR_CONTROL :
                if (( that->getControlSensorName() != (this->_controlSensorName)) ||
                    ( that->getControlSensorSense() != this->_controlSensorSense)) _shouldReturn = false;
                break;
            case Light::FAST_CLOCK_CONTROL :
                if ((that->getFastClockOffCombined() != this->getFastClockOffCombined()) ||
                    (that->getFastClockOnCombined() != this->getFastClockOnCombined())) _shouldReturn = false;
                break;
            case Light::TURNOUT_STATUS_CONTROL :
                if (( that->getControlTurnoutName() != (this->_controlTurnoutName)) ||
                    (that->getControlTurnoutState() != this->_turnoutState)) _shouldReturn = false;
                break;
            case Light::TIMED_ON_CONTROL :
                if (( that->getTimedSensorName() != (this->_timedSensorName)) ||
                    (that->getTimedOnDuration() != this->_timeOnDuration)) _shouldReturn = false;
                break;
            case Light::TWO_SENSOR_CONTROL :
                if (( that->getControlSensorName() != (this->_controlSensorName)) ||
                    (that->getControlSensorSense() != this->_controlSensorSense) ||
                    ( that->getControlSensor2Name() != (this->_controlSensor2Name))) _shouldReturn = false;
                break;
            default:
                // unexpected _controlType value
                LoggingUtil::warnOnce(log, tr("Unexpected _controlType = %1").arg(_controlType));
        }
        return _shouldReturn;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::hashCode() {
        // matches with equals() by contract
        return _controlType;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getControlType() {
        return _controlType;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlType(int type) {
        _controlType = type;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlSensorName(QString sensorName) {
        _controlSensorName = sensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getControlSensorSense() {
        return _controlSensorSense;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getControlSensorName() {
        if (_namedControlSensor != nullptr) {
            return _namedControlSensor->getName();
        }
        return _controlSensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlSensorSense(int sense) {
        if ( sense != Sensor::ACTIVE && sense != Sensor::INACTIVE ) {
            log->error("Incorrect Sensor State Set");
        } else {
            _controlSensorSense = sense;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOnHour() {
        return _fastClockOnHour;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOnMin() {
        return _fastClockOnMin;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOnCombined() {
        return _fastClockOnHour*60+_fastClockOnMin;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOffHour() {
        return _fastClockOffHour;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOffMin() {
        return _fastClockOffMin;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getFastClockOffCombined() {
        return _fastClockOffHour*60+_fastClockOffMin;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setFastClockControlSchedule(int onHour, int onMin, int offHour, int offMin) {
        _fastClockOnHour = onHour;
        _fastClockOnMin = onMin;
        _fastClockOffHour = offHour;
        _fastClockOffMin = offMin;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getControlTurnoutName() {
        return _controlTurnoutName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlTurnout(QString turnoutName) {
        _controlTurnoutName = turnoutName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getControlTurnoutState() {
        return _turnoutState;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlTurnoutState(int state) {
        if ( state != Turnout::CLOSED && state != Turnout::THROWN ) {
            log->error("Incorrect Turnout State Set");
        } else {
            _turnoutState = state;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getTimedSensorName() {
        return _timedSensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getControlTimedOnSensorName() {
        if (_namedTimedControlSensor != nullptr) {
            return _namedTimedControlSensor->getName();
        }
        return _timedSensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlTimedOnSensorName(QString sensorName) {
        _timedSensorName = sensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int DefaultLightControl::getTimedOnDuration() {
        return _timeOnDuration;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setTimedOnDuration(int duration) {
        _timeOnDuration = duration;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getControlSensor2Name() {
        if (_namedControlSensor2 != nullptr) {
            return _namedControlSensor2->getName();
        }
        return _controlSensor2Name;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setControlSensor2Name(QString sensorName) {
        _controlSensor2Name = sensorName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::setParentLight(Light* l) {
        _parentLight = l;
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ QString DefaultLightControl::getDescriptionText(QString lightName){
        QString name = QString(LightTableAction::lightControlTitle);
        name.append(" ");
        name.append(lightName);
        name.append(" ");
        name.append(LightTableAction::getDescriptionText(this, getControlType()));
        return name;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::activateLightControl() {
        // skip if Light Control is already active
        if (_active) {
            return;
        }

        if (_parentLight == nullptr){
            log->error("No Parent Light when activating LightControl");
            return;
        }

        // register LightControl with Parent Light to indicate Control
        // in use if user attempts to delete light
//        _parentLight->addPropertyChangeListener(
//            _parentLightListener = (PropertyChangeEvent e) -> {
//        },_parentLight.toString(), getDescriptionText("") );
        _parentLight->addPropertyChangeListener(new LC1PropertyChangeListener(this), _parentLight->getDisplayName(), getDescriptionText("") );

        // activate according to control type
        switch (_controlType) {
            case Light::SENSOR_CONTROL:
                _namedControlSensor = nullptr;
                if (!_controlSensorName.isEmpty()) {
                    Sensor* sen = InstanceManager::sensorManagerInstance()->
                            provideSensor(_controlSensorName);
                    _namedControlSensor = nbhm->getNamedBeanHandle(_controlSensorName, sen);
                }
                if (_namedControlSensor != nullptr) {
                    // if sensor state is currently known, set light accordingly
                    oneSensorChanged( _namedControlSensor->getBean()->getKnownState() );
                    // listen for change in sensor state
//                    _namedControlSensor.getBean().addPropertyChangeListener(
//                        _sensorListener = (PropertyChangeEvent e) -> {
//                            if (e.getPropertyName() == ("KnownState")) {
//                                oneSensorChanged( (int) e.getNewValue() );
//                            }
//                    }, _controlSensorName, getDescriptionText(_parentLight.getDisplayName()));
                    _namedControlSensor->getBean()->addPropertyChangeListener(new LC2PropertyChangeListener(this), _controlSensorName,
                                                                            getDescriptionText(_parentLight->getDisplayName()));
                    _active = true;
                } else {
                    // control sensor does not exist
                    log->error(tr("Light %1 is linked to a Sensor that does not exist: %2").arg(
                        _parentLight->getSystemName(), _controlSensorName));
                }
                break;
            case Light::FAST_CLOCK_CONTROL:
                if (areFollowerTimesFaulty(_parentLight->getLightControlList())){
                    log->error(tr("Light has multiple actions for the same time in %1").arg(
                        getDescriptionText(_parentLight->getDisplayName())));
                }
                if (_clock == nullptr) {
                    _clock = (Timebase*)InstanceManager::getDefault("Timebase");
                }
                // initialize light based on current fast time
                updateClockControlLightFollower();
                // set up to listen for time changes on a minute basis
//                _clock->addMinuteChangeListener(
//                    _timebaseListener = (PropertyChangeEvent e) -> {
//                        updateClockControlLightFollower();
//                    });
                //connect(_clock,  &Timebase::propertyChange, [=], {updateClockControlLightFollower();});
                _clock->addMinuteChangeListener(_timebaseListener = new DLC_minuteListener(this));
                _active = true;
                break;
            case Light::TURNOUT_STATUS_CONTROL:
                try {
                    _controlTurnout = InstanceManager::turnoutManagerInstance()->
                            provideTurnout(_controlTurnoutName);
                } catch (IllegalArgumentException e) {
                    // control turnout does not exist
                    log->error(tr("Light %1 is linked to a Turnout that does not exist: %2").arg(_parentLight->getSystemName(), _controlSensorName));
                    return;
                }
                // set light based on current turnout state if known
                oneTurnoutChanged( _controlTurnout->getKnownState() );
                // listen for change in turnout state
//                _controlTurnout.addPropertyChangeListener(
//                    _turnoutListener = (PropertyChangeEvent e) -> {
//                        if (e.getPropertyName() == ("KnownState")) {
//                            oneTurnoutChanged( (int) e.getNewValue() );
//                        }
//                    }, _controlTurnoutName, getDescriptionText(_parentLight.getDisplayName()));
                _controlTurnout->addPropertyChangeListener(new LC4PropertyChangeListener(this),_controlTurnoutName, getDescriptionText(_parentLight->getDisplayName()));
                _active = true;
                break;
            case Light::TIMED_ON_CONTROL:
                if (!_timedSensorName.isEmpty()) {
                    Sensor* sen = (Sensor*)InstanceManager::sensorManagerInstance()->
                            provideSensor(_timedSensorName);
                    _namedTimedControlSensor = nbhm->getNamedBeanHandle(_timedSensorName, sen);
                }
                if (_namedTimedControlSensor != nullptr) {
                    if (_parentLight->getEnabled()) {
                        // set initial state off
                        _parentLight->setState(Light::OFF);
                    }

                    addNamedTimedControlListener();
                    // listen for change in timed control sensor state
                    _active = true;
                } else {
                    // timed control sensor does not exist
                    log->error(tr("Light %1 is linked to a Sensor that does not exist: %2").arg(_parentLight->getSystemName(), _timedSensorName));
                }
                break;
            case Light::TWO_SENSOR_CONTROL:
                _namedControlSensor = nullptr;
                _namedControlSensor2 = nullptr;
                if (!_controlSensorName.isEmpty()) {
                    Sensor* sen = (Sensor*)InstanceManager::sensorManagerInstance()->
                            provideSensor(_controlSensorName);
                    _namedControlSensor = nbhm->getNamedBeanHandle(_controlSensorName, sen);
                }
                if (!_controlSensor2Name.isEmpty()) {
                    Sensor* sen = InstanceManager::sensorManagerInstance()->
                            provideSensor(_controlSensor2Name);
                    _namedControlSensor2 = nbhm->getNamedBeanHandle(_controlSensor2Name, sen);
                }
                if ((_namedControlSensor != nullptr) && (_namedControlSensor2 != nullptr)) {
                    // if sensor state is currently known, set light accordingly
                    twoSensorChanged();
                    // listen for change in sensor states
                    _sensorListener = addTwoSensorListener(_namedControlSensor->getBean());
                    _sensor2Listener = addTwoSensorListener(_namedControlSensor2->getBean());
                    _active = true;
                } else {
                    // at least one control sensor does not exist
                    log->error(tr("Light %1 with 2 Sensor Control is linked to a Sensor that does not exist.").arg(_parentLight->getSystemName()));
                }
                break;
            default:
                log->error(tr("Unexpected control type when activating Light: %1").arg(_parentLight->getDisplayName()));
        }

    }

    /**
     * Property Change Listener for Two Sensor.
     */
    /*private*/ PropertyChangeListener* DefaultLightControl::addTwoSensorListener(Sensor* sensor) {
        PropertyChangeListener* pcl;
//        sensor->addPropertyChangeListener(
//            pcl = (PropertyChangeEvent e) -> {
//                if (e.getPropertyName() == ("KnownState")) {
//                    twoSensorChanged();
//                }
//            }, sensor.getDisplayName(), getDescriptionText(_parentLight.getDisplayName()));
        sensor->addPropertyChangeListener(new LC6PropertyChangeListener(this), sensor->getDisplayName(), getDescriptionText(_parentLight->getDisplayName()));
        return pcl;
    }

    /**
     * Add a Timed Control Listener to a Sensor.
     *
     */
    /*private*/ void DefaultLightControl::addNamedTimedControlListener(){
//        _namedTimedControlSensor->getBean()->addPropertyChangeListener(
//            _timedSensorListener = (PropertyChangeEvent e) -> {
//                if (e.getPropertyName() == ("KnownState")
//                    && (int) e.getNewValue() == Sensor::ACTIVE
//                    && _timedControlTimer == nullptr
//                    && _parentLight->getEnabled()) {
//                    // Turn light on
//                    _parentLight->setState(Light.ON);
//                    // Create a timer if one does not exist
//                    _timedControlListener = new TimeLight();
//                    _timedControlTimer = new Timer(_timeOnDuration,
//                        _timedControlListener);
//                    // Start the Timer to turn the light OFF
//                    _timedControlTimer.start();
//                }
//            },
     _namedTimedControlSensor->getBean()->addPropertyChangeListener(
     _timedSensorListener,
     _timedSensorName, getDescriptionText(_parentLight->getDisplayName()));
    }

    /**
     * Internal routine for handling sensor change or startup
     * for the 1 Sensor Control Type
     */
    /*private*/ void DefaultLightControl::oneSensorChanged(int newSensorState){
        if (!_parentLight->getEnabled()) {
            return;  // ignore property change if user disabled Light
        }
        if (newSensorState == Sensor::ACTIVE) {
            if (_controlSensorSense == Sensor::ACTIVE) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        } else if (newSensorState == Sensor::INACTIVE) {
            if (_controlSensorSense == Sensor::INACTIVE) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        }
    }

    /**
     * Internal routine for handling Turnout change or startup
     * for the TURNOUT_STATUS_CONTROL Control Type
     */
    /*private*/ void DefaultLightControl::oneTurnoutChanged(int newTurnoutState){
        if (!_parentLight->getEnabled()) {
            return;  // ignore property change if user disabled light
        }
        if (newTurnoutState == Turnout::CLOSED) {
            if (_turnoutState == Turnout::CLOSED) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        } else if (newTurnoutState == Turnout::THROWN) {
            if (_turnoutState == Turnout::THROWN) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        }
    }

    /**
     * Internal routine for handling sensor changes
     * for the 2 Sensor Control Type
     */
    /*protected*/ void DefaultLightControl::twoSensorChanged() {
        if (!_parentLight->getEnabled()) {
            return;  // ignore property change if user disabled Light
        }
        int kState = _namedControlSensor->getBean()->getKnownState();
        int kState2 = _namedControlSensor2->getBean()->getKnownState();
        if (_controlSensorSense == Sensor::ACTIVE) {
            if ((kState == Sensor::ACTIVE) || (kState2 == Sensor::ACTIVE)) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        } else if (_controlSensorSense == Sensor::INACTIVE) {
            if ((kState == Sensor::INACTIVE) || (kState2 == Sensor::INACTIVE)) {
                // Turn light on
                _parentLight->setState(Light::ON);
            } else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        }
    }

    /**
     * Internal routine for seeing if we have the latest time to control the FastClock Follower.
     * <p>
     * Takes previous day times
     *
     * @return True if we have the most recent time ( either on or off ), otherwise False.
     */
    /*private*/ bool DefaultLightControl::isMasterFastClockFollower(){
        QList<int> otherControlTimes= QList<int>();
        QList<int> thisControlTimes= QList<int>();

        // put all other times in a single List to compare
        //_parentLight->getLightControlList().forEach((otherLc) ->
        for(LightControl*  otherLc : _parentLight->getLightControlList())
        {
            if (otherLc!=this && otherLc->getControlType()==Light::FAST_CLOCK_CONTROL) {
                // by adding 1440 mins to the today times, we can check yesterday in the same list.
                otherControlTimes.append( otherLc->getFastClockOnCombined() ); // yesterdayOnTime
                otherControlTimes.append( otherLc->getFastClockOffCombined() ); // yesterdayOffTime
                otherControlTimes.append( otherLc->getFastClockOnCombined()+1440 ); // todayOnTime
                otherControlTimes.append( otherLc->getFastClockOffCombined()+1440 ); // todayOffTime
            }
        }//);
        // log.debug("{} other control times in list {}",otherControlTimes.size(),otherControlTimes);

        thisControlTimes.append( getFastClockOnCombined() ); // yesterdayOnTime
        thisControlTimes.append( getFastClockOffCombined() ); // yesterdayOffTime
        thisControlTimes.append( getFastClockOnCombined()+1440 ); // todayOnTime
        thisControlTimes.append( getFastClockOffCombined()+1440 ); // todayOffTime

//        otherControlTimes.removeIf( e -> ( e > ( _timeNow +1440 ) )); // remove future times
//        thisControlTimes.removeIf( e -> ( e > ( _timeNow +1440 ) )); // remove future times

        if (otherControlTimes.isEmpty()){
            return true;
        }
        //return Collections.max(thisControlTimes) >= Collections.max(otherControlTimes);
        int max = -1;
        int max2 = -1;
        for(int i1 : thisControlTimes)
        {
         if(i1 > max)
          max = i1;
        }
        for(int i1 : otherControlTimes)
        {
         if(i1 > max2)
          max2 = i1;
        }
        return max >= max2;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool DefaultLightControl::onOffTimesFaulty() {
        return (getFastClockOnCombined()==getFastClockOffCombined());
    }

    /**
     * @param time Combined hours / mins to check against.
     */
    /*private*/ /*Predicate<LightControl*>*/bool DefaultLightControl::isFastClockEqual(int time) {
//        return p -> ( !(p==this) && (
//            p.getFastClockOnCombined() == time || p.getFastClockOffCombined() == time ) );
     return this->_timeNow != time && (this->getFastClockOnCombined() == time || this->getFastClockOffCombined()==time);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ bool DefaultLightControl::areFollowerTimesFaulty( QList<LightControl*> compareList ) {
        if (onOffTimesFaulty()){
            return true;
        }
//        return (compareList.stream().anyMatch(isFastClockEqual(getFastClockOnCombined())) ||
//            compareList.stream().anyMatch(isFastClockEqual(getFastClockOffCombined())));
        for(LightControl* lc : compareList)
        {
         if(lc->isFastClockEqual(getFastClockOnCombined()))
         {
          return true;
         }
         if(lc->isFastClockEqual(getFastClockOffCombined()))
         {
          return true;
         }
        }
    }

    /**
     * Updates the local int of the FastClock Time
     */
    //@SuppressWarnings("deprecation")
    /*private*/ void DefaultLightControl::setTheTime(){
     QDateTime now = _clock->getTime();
     _timeNow = now.time().hour() * 60 + now.time().minute();
    }

    /**
     * Updates the status of a Light under FAST_CLOCK_CONTROL. This method is
     * called every FastClock minute.
     */
    /*private*/ void DefaultLightControl::updateClockControlLightFollower() {
        if (!_parentLight->getEnabled()) {
            return;  // ignore property change if user disabled Light
        }
        if (_clock != nullptr) {
            setTheTime();
            // log.debug("updateClockControl, now is {} master {}",_timeNow,isMasterFastClockFollower());
            if (!isMasterFastClockFollower()){
                return;
            }
            int state = _parentLight->getState();
            if (getFastClockOnCombined() <= getFastClockOffCombined()) {
                // on and off the same day
                if ((_timeNow < getFastClockOnCombined()) || (_timeNow >= getFastClockOffCombined())) {
                    // Light should be OFF
                    if (state == Light::ON) {
                        logTimeChanges("OFF");
                        _parentLight->setState(Light::OFF);
                    }
                } else {
                    // Light should be ON
                    if (state == Light::OFF) {
                        logTimeChanges("ON");
                        _parentLight->setState(Light::ON);
                    }
                }
            } else {
                // on and off - different days
                if ((_timeNow >= getFastClockOnCombined()) || (_timeNow < getFastClockOffCombined())) {
                    // Light should be ON
                    if (state == Light::OFF) {
                        logTimeChanges("ON");
                        _parentLight->setState(Light::ON);
                    }
                } else {
                    // Light should be OFF
                    if (state == Light::ON) {
                        logTimeChanges("OFF");
                        _parentLight->setState(Light::OFF);
                    }
                }
            }
        }
    }

    /**
     * Outputs Time and Light Change info to log file.
     * eg Output "DEBUG - 11:05 Setting Light My Light 2751 OFF"
     */
    /*private*/ void DefaultLightControl::logTimeChanges(QString onOrOff){
//        log->debug(tr("%1:%2 Setting Light %3 %4",
//            (_timeNow/60),String.format("%02d", (_timeNow % 60)),
//            _parentLight->getDisplayName(),onOrOff);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void DefaultLightControl::deactivateLightControl() {
        // skip if Light Control is not active
        if (_active) {
            _parentLight->removePropertyChangeListener(_parentLightListener);
            if (_sensorListener != nullptr) {
                _namedControlSensor->getBean()->removePropertyChangeListener(_sensorListener);
                _sensorListener = nullptr;
            }
            if ((_clock != nullptr) && (_timebaseListener != nullptr)) {
                _clock->removeMinuteChangeListener(_timebaseListener);
                _timebaseListener = nullptr;
            }
            if (_turnoutListener != nullptr) {
                _controlTurnout->removePropertyChangeListener(_turnoutListener);
                _turnoutListener = nullptr;
            }
            if (_timedSensorListener != nullptr) {
                _namedTimedControlSensor->getBean()->removePropertyChangeListener(_timedSensorListener);
                _timedSensorListener = nullptr;
            }
            if (_timedControlListener != nullptr && _timedControlTimer != nullptr) {
//                _timedControlTimer->removeActionListener(_timedControlListener);
                _timedControlListener = nullptr;
            }
            if (_timedControlTimer != nullptr) {
                _timedControlTimer->stop();
                _timedControlTimer = nullptr;
            }
            if (_sensor2Listener != nullptr) {
                _namedControlSensor2->getBean()->removePropertyChangeListener(_sensor2Listener);
                _sensor2Listener = nullptr;
            }
            _active = false;
        }
    }

//    /**
//     * Class for defining ActionListener for TIMED_ON_CONTROL
//     */
//    /*private*/ class TimeLight implements java.awt.event.ActionListener {

//        @Override
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent event) {
//            // Turn Light OFF
//            _parentLight->setState(Light.OFF);
//            // Turn Timer OFF
//            if (_timedControlTimer != null ) {
//                _timedControlTimer.stop();
//            }
//            _timedControlTimer = null;
//        }
//    }

    /*private*/ /*final*/ /*static*/ Logger* DefaultLightControl::log = LoggerFactory::getLogger("DefaultLightControl");
