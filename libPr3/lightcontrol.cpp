#include "lightcontrol.h"
#include "turnout.h"
#include "timebase.h"
#include "predicate.h"

LightControl::LightControl(QObject *parent) :
    QObject(parent)
{
    common();
}
/**
 * Each LightControl object is linked to a specific Light, and provides one of the
 *    controls available for switching the Light ON/OFF in response to time or
 *	  events occurring on the layout.
 * <p>
 * Each LightControl holds the information for one control of the parent Light.
 *<p>
 * Each Light may have as many controls as desired by the user.  It is the
 *     user's responsibility to ensure that the various control mechanisms
 *     do not conflict with one another.
 *<p>
 * Available control types are those defined in the Light.java interface.
 *   Control types:
 *    SENSOR_CONTROL
 *    FAST_CLOCK_CONTROL
 *    TURNOUT_STATUS_CONTROL
 *    TIMED_ON_CONTROL
 *	  TWO_SENSOR_CONTROL
 *
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * <P>
 * @author			Dave Duchamp Copyright (C) 2010
 * @version			$Revision: 18023 $
 */
//public class LightControl {

    /**
     * Main constructor methods
     */
//	public LightControl() {
//	}

LightControl::LightControl(Light* l, QObject* parent) : QObject(parent)
{
    common();
    _parentLight = l;
}

void LightControl::common()
{
    log = new Logger("LightControl");
    // instance variables - saved with Light in configuration file
    _controlType = Light::NO_CONTROL;    // control type
    _controlSensorName = "";   // controlling Sensor if SENSOR_CONTROL
    _fastClockOnHour = 0;         // on Hour if FAST_CLOCK_CONTROL
    _fastClockOnMin = 0;          // on Minute if FAST_CLOCK_CONTROL
    _fastClockOffHour = 0;        // off Hour if FAST_CLOCK_CONTROL
    _fastClockOffMin = 0;         // off Minute if FAST_CLOCK_CONTROL
    _controlTurnoutName = "";  // turnout whose status is shown if TURNOUT_STATUS_CONTROL
    _turnoutState = Turnout::CLOSED;  // turnout state corresponding to this Light ON
    _timedSensorName = "";     // trigger Sensor if TIMED_ON_CONTROL
    _controlSensor2Name = ""; // second controlling sensor if TWO_SENSOR_CONTROL
    // operational instance variables - not saved between runs
    _parentLight = nullptr;        // Light that is being controlled
    _active = false;
     _namedControlSensor = nullptr;
    _sensorListener = nullptr;
    _namedControlSensor2 = nullptr;
    _sensor2Listener = nullptr;
    _timebaseListener = nullptr;
    _clock = nullptr;
    _timeOn = 0;
    _timeOff = 0;
    _controlTurnout = nullptr;
    _turnoutListener = nullptr;
    _namedTimedControlSensor = nullptr;
     _timedSensorListener = nullptr;
    _timedControlTimer = nullptr;
    _timedControlListener = nullptr;
    _lightOnTimerActive = false;

    nbhm = (NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager");

}

/*
 * Test if a LightControl is equal to this one
 *
 * @param o the LightControl object to be checked
 * @return True if the LightControl is equal, else false
 */
//@Override
/*public*/ bool LightControl::equals(QObject* o) {
    if (o == nullptr) return false;
    if (this == o) {
        return true;
    }
    if (!(qobject_cast<LightControl*>(o))) {
        return false;
    }
    LightControl* that = (LightControl*) o;
    if (that->_controlType != this->_controlType) return false;

    switch(_controlType) {
        case Light::NO_CONTROL :
            return true;
        case Light::SENSOR_CONTROL :
            if (that->_controlSensorName != (this->_controlSensorName)) return false;
            if (that->_controlSensorSense != this->_controlSensorSense) return false;
            return true;
        case Light::FAST_CLOCK_CONTROL :
            if (that->getFastClockOffCombined() != this->getFastClockOffCombined()) return false;
            if (that->getFastClockOnCombined() != this->getFastClockOnCombined()) return false;
            return true;
        case Light::TURNOUT_STATUS_CONTROL :
            if (that->_controlTurnoutName != (this->_controlTurnoutName)) return false;
            if (that->_turnoutState != this->_turnoutState) return false;
            return true;
        case Light::TIMED_ON_CONTROL :
            if (that->_timedSensorName != (this->_timedSensorName)) return false;
            if (that->_timeOnDuration != this->_timeOnDuration) return false;
            return true;
        case Light::TWO_SENSOR_CONTROL :
            if (that->_controlSensorName !=(this->_controlSensorName)) return false;
            if (that->_controlSensorSense != this->_controlSensorSense) return false;
            if (that->_controlSensor2Name !=(this->_controlSensor2Name)) return false;
            return true;
        default:
            // unexpected _controlType value
//            jmri.util.Log4JUtil.warnOnce(log, "Unexpected _controlType = {}", _controlType);
     log->warn(tr("Unexpected _controlType = %1").arg(_controlType));
            return true; // since _controlType matches
    }
}

//@Override
/*public*/ int LightControl::hashCode() {
    // matches with equals() by contract
    return _controlType;
}

/**
 * Accessor methods
 */
/*public*/ int LightControl::getControlType() {return _controlType;}
/*public*/ void LightControl::setControlType(int type) {_controlType = type;}
/*public*/ void LightControl::setControlSensorName(QString sensorName) {_controlSensorName = sensorName;}
/*public*/ int LightControl::getControlSensorSense() {return _controlSensorSense;}

/*public*/ QString LightControl::getControlSensorName() {
    if (_namedControlSensor!=nullptr)
        return _namedControlSensor->getName();
    return _controlSensorName;
}

/*public*/ void LightControl::setControlSensorSense(int sense) {_controlSensorSense = sense;}
/*public*/ int LightControl::getFastClockOnHour() {return _fastClockOnHour;}
/*public*/ int LightControl::getFastClockOnMin() {return _fastClockOnMin;}
/*
 * Get the Fast Clock On Hours and Minutes Combined
 * Convenience method of separate getFastClockOnHour() and getFastClockOnMin()
 * @return  Total combined Minute value
 */
/*protected*/ int LightControl::getFastClockOnCombined() {
    return _fastClockOnHour*60+_fastClockOnMin;
}

/*
 * Get the Fast Clock Off Hours and Minutes Combined
 * Convenience method of separate getFastClockOnHour() and getFastClockOnMin()
 * @return  Total combined Minute value
 */
/*protected*/ int LightControl::getFastClockOffCombined() {
    return _fastClockOffHour*60+_fastClockOffMin;
}

/*public*/ int LightControl::getFastClockOffHour() {return _fastClockOffHour;}
/*public*/ int LightControl::getFastClockOffMin() {return _fastClockOffMin;}
/*public*/ void LightControl::setFastClockControlSchedule(int onHour,int onMin,int offHour, int offMin) {
    _fastClockOnHour = onHour;
    _fastClockOnMin = onMin;
    _fastClockOffHour = offHour;
    _fastClockOffMin = offMin;
}
/*public*/ QString LightControl::getControlTurnoutName() {return _controlTurnoutName;}
/*public*/ void LightControl::setControlTurnout(QString turnoutName) {_controlTurnoutName = turnoutName;}
/*public*/ int LightControl::getControlTurnoutState() {return _turnoutState;}
/*public*/ void LightControl::setControlTurnoutState(int state) {_turnoutState = state;}

/*public*/ QString LightControl::getControlTimedOnSensorName() {
    if(_namedTimedControlSensor!=nullptr)
        return _namedTimedControlSensor->getName();
    return _timedSensorName;
}

/*public*/ void LightControl::setControlTimedOnSensorName(QString sensorName) {_timedSensorName = sensorName;}
/*public*/ int LightControl::getTimedOnDuration() {return _timeOnDuration;}
/*public*/ void LightControl::setTimedOnDuration(int duration) {_timeOnDuration = duration;}

/*public*/ QString LightControl::getControlSensor2Name() {
    if (_namedControlSensor2!=nullptr)
        return _namedControlSensor2->getName();
    return _controlSensor2Name;
}

/*public*/ void LightControl::setControlSensor2Name(QString sensorName) {_controlSensor2Name = sensorName;}
/*public*/ void LightControl::setParentLight(Light* l) {_parentLight = l;}


/**
 * Activates a Light Control by control type.  This method tests the
 *   control type, and set up a control mechanism, appropriate
 *   for the control type.
 */
/*public*/ void LightControl::activateLightControl() {
    // skip if Light Control is already active
    if (!_active) {
        // activate according to control type
        switch (_controlType) {
            case Light::SENSOR_CONTROL:
                _namedControlSensor = nullptr;
                if (_controlSensorName.length()>0){
                    Sensor* sen = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                            provideSensor(_controlSensorName);
                    _namedControlSensor = nbhm->getNamedBeanHandle(_controlSensorName, sen);
                }
                if (_namedControlSensor!=nullptr) {
                    // if sensor state is currently known, set light accordingly
                    int kState = _namedControlSensor->getBean()->getKnownState();
                    if (kState==Sensor::ACTIVE) {
                        if (_controlSensorSense==Sensor::ACTIVE) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }
                    else if (kState==Sensor::INACTIVE) {
                        if (_controlSensorSense==Sensor::INACTIVE) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }

                    // listen for change in sensor state
//                    _namedControlSensor->getBean().addPropertyChangeListener(_sensorListener =
//                                            new PropertyChangeListener()
//                    {
//                            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                                if (!_parentLight->getEnabled()) return;  // ignore property change if user disabled Light
//                                if (e.getPropertyName().equals("KnownState")) {
//                                    int now = _namedControlSensor->getBean().getKnownState();
//                                    if (now==Sensor.ACTIVE) {
//                                        if (_controlSensorSense==Sensor.ACTIVE) {
//                                            // Turn light on
//                                            _parentLight->setState(Light.ON);
//                                        }
//                                        else {
//                                            // Turn light off
//                                            _parentLight->setState(Light.OFF);
//                                        }
//                                    }
//                                    else if (now==Sensor.INACTIVE) {
//                                        if (_controlSensorSense==Sensor.INACTIVE) {
//                                            // Turn light on
//                                            _parentLight->setState(Light.ON);
//                                        }
//                                        else {
//                                            // Turn light off
//                                            _parentLight->setState(Light.OFF);
//                                        }
//                                    }
//                                }
//                            }
//                    }, _controlSensorName, "Light Control " + _parentLight->getDisplayName());
                    _active = true;
                }
                else {
                    // control sensor does not exist
                    log->error("Light "+_parentLight->getSystemName()+
                            " is linked to a Sensor that does not exist: "+_controlSensorName);
                    return;
                }
                break;

            case Light::FAST_CLOCK_CONTROL:
                if (_clock==nullptr) {
                    _clock = (Timebase*)InstanceManager::getDefault("Timebase");
                }
                // set up time as minutes in a day
                _timeOn = _fastClockOnHour * 60 + _fastClockOnMin;
                _timeOff = _fastClockOffHour * 60 + _fastClockOffMin;
                // initialize light based on current fast time
                updateClockControlLight ();
                // set up to listen for time changes on a minute basis
//                _clock.addMinuteChangeListener( _timebaseListener =
//                    new java.beans.PropertyChangeListener() {
//                        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                            if (_parentLight->getEnabled()) {  // don't change light if not enabled
//                                // update control if light is enabled
//                                updateClockControlLight();
//                            }
//                        }
//                    });
                _active = true;
                break;
            case Light::TURNOUT_STATUS_CONTROL:
                _controlTurnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->
                                        provideTurnout(_controlTurnoutName);
                if (_controlTurnout!=nullptr) {
                    // set light based on current turnout state if known
                    int tState = _controlTurnout->getKnownState();
                    if (tState==Turnout::CLOSED) {
                        if (_turnoutState==Turnout::CLOSED) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }
                    else if (tState==Turnout::THROWN) {
                        if (_turnoutState==Turnout::THROWN) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }

                    // listen for change in turnout state
//                    _controlTurnout.addPropertyChangeListener(_turnoutListener =
//                                            new java.beans.PropertyChangeListener() {
//                            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                                if (!_parentLight->getEnabled()) return;  // ignore property change if user disabled light
//                                if (e.getPropertyName().equals("KnownState")) {
//                                    int now = _controlTurnout.getKnownState();
//                                    if (now==Turnout.CLOSED) {
//                                        if (_turnoutState==Turnout.CLOSED) {
//                                            // Turn light on
//                                            _parentLight->setState(Light.ON);
//                                        }
//                                        else {
//                                            // Turn light off
//                                            _parentLight->setState(Light.OFF);
//                                        }
//                                    }
//                                    else if (now==Turnout.THROWN) {
//                                        if (_turnoutState==Turnout.THROWN) {
//                                            // Turn light on
//                                            _parentLight->setState(Light.ON);
//                                        }
//                                        else {
//                                            // Turn light off
//                                            _parentLight->setState(Light.OFF);
//                                        }
//                                    }
//                                }
//                            }
//                    });
                    _active = true;
                }
                else {
                    // control turnout does not exist
                    log->error("Light "+_parentLight->getSystemName()+
                            " is linked to a Turnout that does not exist: "+_controlSensorName);
                    return;
                }
                break;
            case Light::TIMED_ON_CONTROL:
                if (_timedSensorName.length()>0){
                    Sensor* sen = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                        provideSensor(_timedSensorName);
                    _namedTimedControlSensor = nbhm->getNamedBeanHandle(_timedSensorName, sen);
                }
                if (_namedTimedControlSensor!=nullptr) {
                    // set initial state off
                    _parentLight->setState(Light::OFF);
                    // listen for change in timed control sensor state
//                    _namedTimedControlSensor.getBean().addPropertyChangeListener(_timedSensorListener =
//                                            new java.beans.PropertyChangeListener() {
//                            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                                if (!_parentLight->getEnabled()) return;  // ignore property change if user disabled light
//                                if (e.getPropertyName().equals("KnownState")) {
//                                    int now = _namedTimedControlSensor.getBean().getKnownState();
//                                    if (!_lightOnTimerActive) {
//                                        if (now==Sensor.ACTIVE) {
//                                            // Turn light on
//                                            _parentLight->setState(Light.ON);
//                                            // Create a timer if one does not exist
//                                            if (_timedControlTimer==nullptr) {
//                                                _timedControlListener = new TimeLight();
//                                                _timedControlTimer = new Timer(_timeOnDuration,
//                                                        _timedControlListener);
//                                            }
//                                            // Start the Timer to turn the light OFF
//                                            _lightOnTimerActive = true;
//                                            _timedControlTimer.start();
//                                        }
//                                    }
//                                }
//                            }
//                    }, _timedSensorName, "Light Control " + _parentLight->getDisplayName());
                    _active = true;
                }
                else {
                    // timed control sensor does not exist
                    log->error("Light "+_parentLight->getSystemName()+
                                " is linked to a Sensor that does not exist: "+_timedSensorName);
                    return;
                }
                break;
            case Light::TWO_SENSOR_CONTROL:
                _namedControlSensor = nullptr;
                _namedControlSensor2 = nullptr;
                if (_controlSensorName.length()>0){
                    Sensor* sen = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                            provideSensor(_controlSensorName);
                    _namedControlSensor = nbhm->getNamedBeanHandle(_controlSensorName, sen);
                }
                if (_controlSensor2Name.length()>0){
                    Sensor* sen = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->
                                            provideSensor(_controlSensor2Name);
                    _namedControlSensor2 = nbhm->getNamedBeanHandle(_controlSensor2Name, sen);
                }
                if ( (_namedControlSensor!=nullptr) && (_namedControlSensor2!=nullptr) ) {
                    // if sensor state is currently known, set light accordingly
                    int kState = _namedControlSensor->getBean()->getKnownState();
                    int kState2 = _namedControlSensor2->getBean()->getKnownState();
                    if (_controlSensorSense==Sensor::ACTIVE) {
                        if ( (kState==Sensor::ACTIVE) || (kState2==Sensor::ACTIVE) ) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }
                    else if (_controlSensorSense==Sensor::INACTIVE) {
                        if 	( (kState==Sensor::INACTIVE) || (kState2==Sensor::INACTIVE) ) {
                            // Turn light on
                            _parentLight->setState(Light::ON);
                        }
                        else {
                            // Turn light off
                            _parentLight->setState(Light::OFF);
                        }
                    }

                    // listen for change in sensor states
//                    _namedControlSensor->getBean().addPropertyChangeListener(_sensorListener =
//                                            new java.beans.PropertyChangeListener() {
//                            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                                twoSensorChanged(e);
//                           }
//                    }, _controlSensorName, "Light Control " + _parentLight->getDisplayName());
//                    _namedControlSensor2->getBean().addPropertyChangeListener(_sensor2Listener =
//                                            new java.beans.PropertyChangeListener() {
//                            /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//                                twoSensorChanged(e);
//                           }
//                    }, _controlSensor2Name, "Light Control " + _parentLight->getDisplayName());
                    _active = true;
                }
                else {
                    // at least one control sensor does not exist
                    log->error("Light "+_parentLight->getSystemName()+
                            " is linked to a Sensor that does not exist: ");
                    return;
                }
                break;
            default:
                log->warn("Unexpected control type when activating Light: "+_parentLight->getSystemName());
        }
    }
}
/*protected*/ void LightControl::twoSensorChanged(PropertyChangeEvent* e) {
    if (!_parentLight->getEnabled()) return;  // ignore property change if user disabled Light
    if (e->getPropertyName()==("KnownState")) {
        int kState = _namedControlSensor->getBean()->getKnownState();
        int kState2 = _namedControlSensor2->getBean()->getKnownState();
        if (_controlSensorSense==Sensor::ACTIVE) {
            if ( (kState==Sensor::ACTIVE) || (kState2==Sensor::ACTIVE) ) {
                // Turn light on
                _parentLight->setState(Light::ON);
            }
            else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
        }
        else if (_controlSensorSense==Sensor::INACTIVE) {
            if 	( (kState==Sensor::INACTIVE) || (kState2==Sensor::INACTIVE) ) {
                // Turn light on
                _parentLight->setState(Light::ON);
            }
            else {
                // Turn light off
                _parentLight->setState(Light::OFF);
            }
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
/*private*/ bool LightControl::isMasterFastClockFollower()
{
    QList<int> otherControlTimes= QList<int>();
    QList<int> thisControlTimes= QList<int>();

    // put all other times in a single List to compare
    //_parentLight.getLightControlList().forEach((otherLc) -> {
    foreach(LightControl* otherLc, _parentLight->getLightControlList())
    {
        if ((otherLc!=this )&& (otherLc->getControlType()==Light::FAST_CLOCK_CONTROL))
        {
            // by adding 1440 mins to the today times, we can check yesterday in the same list.
            otherControlTimes.append( otherLc->getFastClockOnCombined() ); // yesterdayOnTime
            otherControlTimes.append( otherLc->getFastClockOffCombined() ); // yesterdayOffTime
            otherControlTimes.append( otherLc->getFastClockOnCombined()+1440 ); // todayOnTime
            otherControlTimes.append( otherLc->getFastClockOffCombined()+1440 ); // todayOffTime
        }
    }//);
    log->debug(tr("%1 other control times in list %2").arg(otherControlTimes.size()).arg("otherControlTimes"));

    thisControlTimes.append( getFastClockOnCombined() ); // yesterdayOnTime
    thisControlTimes.append( getFastClockOffCombined() ); // yesterdayOffTime
    thisControlTimes.append( getFastClockOnCombined()+1440 ); // todayOnTime
    thisControlTimes.append( getFastClockOffCombined()+1440 ); // todayOffTime

    //otherControlTimes.removeIf( e -> ( e > ( _timeNow +1440 ) )); // remove future times
    bool wrk = true;
    while(wrk)
    {
     foreach (int e, otherControlTimes)
     {
      if(e>_timeNow +1440)
      {
       otherControlTimes.removeOne(e);
       break;
      }
     }
     wrk = false;
    }
    //thisControlTimes.removeIf( e -> ( e > ( _timeNow +1440 ) )); // remove future times
    wrk = true;
    while(wrk)
    {
     foreach (int e, thisControlTimes)
     {
      if(e>_timeNow +1440)
      {
       thisControlTimes.removeOne(e);
       break;
      }
     }
     wrk = false;
    }

    if (otherControlTimes.size()==0){
        return true;
    }
#if 0 //TODO:
    if (Collections.max(thisControlTimes) < Collections.max(otherControlTimes)){
        return false;
    }
#endif
    return true;
}

/**
 * Check to see if we have the FastClock Follower has unique times for a single Light Control.
 * <p>
 * Hour / Minute combination must be unique for each Light to avoid flicker.
 *
 * @return true if the clock on time equals the off time, otherwise false.
 */
/*public*/ bool LightControl::onOffTimesFaulty() {
    return (getFastClockOnCombined()==getFastClockOffCombined());
}

/**
 * @param time Combined hours / mins to check against.
 */
/*private*/ Predicate<LightControl*> LightControl::isFastClockEqual(int time) {
#if 0 // TODO:
    return p -> ( (p!=this) && (
        p.getFastClockOnCombined() == time || p.getFastClockOffCombined() == time ) );
#endif
}

/**
 * Check to see if we have the FastClock Follower has unique times for a single Light.
 * <p>
 * Hour / Minute combination must be unique for each Light to avoid flicker.
 *
 * @param compareList the ArrayList of other Light Controls to compare against
 * @return true if there are multiple exact same times
 */
/*public*/ bool LightControl::areFollowerTimesFaulty( QList<LightControl*> compareList ) {
    if (onOffTimesFaulty()){
        return true;
    }
//    return (compareList.stream().anyMatch(isFastClockEqual(getFastClockOnCombined())) ||
//        compareList.stream().anyMatch(isFastClockEqual(getFastClockOffCombined())));
    foreach (LightControl* lc, compareList) {

    }
}

/**
 *  Updates the status of a Light under FAST_CLOCK_CONTROL.  This
 *   method is called every FastClock minute.
 */
//@SuppressWarnings("deprecation")
/*private*/ void LightControl::updateClockControlLight() {
    if (_clock!=nullptr) {
        QDateTime now = _clock->getTime();
        int timeNow = now.time().hour() * 60 + now.time().minute();
        int state = _parentLight->getState();
        if (_timeOn <= _timeOff) {
            // on and off the same day
            if ( (timeNow<_timeOn) || (timeNow>=_timeOff) ) {
                // Light should be OFF
                if (state == Light::ON) _parentLight->setState(Light::OFF);
            }
            else {
                // Light should be ON
                if (state == Light::OFF) _parentLight->setState(Light::ON);
            }
        }
        else {
            // on and off - different days
            if ( (timeNow>=_timeOn) || (timeNow<_timeOff) ) {
                // Light should be ON
                if (state == Light::OFF) _parentLight->setState(Light::ON);
            }
            else {
                // Light should be OFF
                if (state == Light::ON) _parentLight->setState(Light::OFF);
            }
        }
    }
}

/**
 * Deactivates a LightControl by control type.  This method tests the
 *   control type, and deactivates the control mechanism, appropriate
 *   for the control type.
 */
/*public*/ void LightControl::deactivateLightControl() {
    // skip if Light Control is not active
    if (_active) {
        // deactivate according to control type
        switch (_controlType) {
            case Light::SENSOR_CONTROL:
                if (_sensorListener!=nullptr) {
                    _namedControlSensor->getBean()->removePropertyChangeListener(_sensorListener);
                    _sensorListener = nullptr;
                }
                break;
            case Light::FAST_CLOCK_CONTROL:
                if ( (_clock!=nullptr) && (_timebaseListener!=nullptr) ) {
                    _clock->removeMinuteChangeListener(_timebaseListener);
                    _timebaseListener = nullptr;
                }
                break;
            case Light::TURNOUT_STATUS_CONTROL:
                if (_turnoutListener!=nullptr) {
                    _controlTurnout->removePropertyChangeListener(_turnoutListener);
                    _turnoutListener = nullptr;
                }
                break;
            case Light::TIMED_ON_CONTROL:
                if (_timedSensorListener!=nullptr) {
                    _namedTimedControlSensor->getBean()->removePropertyChangeListener(_timedSensorListener);
                    _timedSensorListener = nullptr;
                }
                if (_lightOnTimerActive) {
                    _timedControlTimer->stop();
                    _lightOnTimerActive = false;
                }
                if (_timedControlTimer!=nullptr) {
                    if (_timedControlListener!=nullptr) {
//                        _timedControlTimer->removeActionListener(_timedControlListener);
                        _timedControlListener = nullptr;
                    }
                    _timedControlTimer = nullptr;
                }
                break;
            case Light::TWO_SENSOR_CONTROL:
                if (_sensorListener!=nullptr) {
                    _namedControlSensor->getBean()->removePropertyChangeListener(_sensorListener);
                    _sensorListener = nullptr;
                }
                if (_sensor2Listener!=nullptr) {
                    _namedControlSensor2->getBean()->removePropertyChangeListener(_sensor2Listener);
                    _sensor2Listener = nullptr;
                }
                break;
            default:
                log->warn("Unexpected control type when activating Light: "+_parentLight->getSystemName());
        }
        _active = false;
    }
}
#if 0 // TODO:
/**
 *	Class for defining ActionListener for TIMED_ON_CONTROL
 */
class TimeLight : public ActionListener
{
 public:
    /*public*/ void actionPerformed(ActionEvent* event)
    {
        // Turn Light OFF
        _parentLight->setState(Light::OFF);
        // Turn Timer OFF
        _timedControlTimer.stop();
        _lightOnTimerActive = false;
    }
}

#endif
////static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LightControl.class.getName());
//}

/* @(#)LightControl.java */
