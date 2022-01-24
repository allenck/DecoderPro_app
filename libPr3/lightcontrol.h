#ifndef LIGHTCONTROL_H
#define LIGHTCONTROL_H

#include <QObject>
#include "light.h"
#include "instancemanager.h"
#include "namedbean.h"
#include "namedbeanhandlemanager.h"
#include "namedbeanhandle.h"
#include "actionlistener.h"
#include <QTimer>
#include "predicate.h"
#include "propertychangelistener.h"
//#include "abstractlight.h"

class AbstractLight;
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
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * @author Dave Duchamp      Copyright (C) 2010
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
/*public*/ /*interface*/class LightControl {

 public:
    /**
     * Get the control type used by the Control
     *
     * @return the Control Type, eg. FAST_CLOCK_CONTROL
     */
    /*public*/  virtual  int getControlType()=0;

    /**
     * Set the control type used by the Control
     * Does NOT update any changelisteners
     *
     * @param type the Control Type, eg. FAST_CLOCK_CONTROL
     */
    /*public*/  virtual  void setControlType(int type)=0;

    /**
     * Set Sensor 1 used by the 1 Sensor and 2 Sensor Control
     * Does NOT update any changelisteners
     * If Sensor not present and name not empty, is provided by the SensorManager
     * when #activateLightControl() is called
     *
     * @param sensorName the Sensor name
     */
    /*public*/  virtual  void setControlSensorName(QString sensorName)=0;

    /**
     * Get the Sensor State used by the 1 Sensor Control
     *
     * @return Sensor.ACTIVE or Sensor.INACTIVE
     */
    /*public*/  virtual  int getControlSensorSense()=0;

    /**
     * Get the Sensor 1 name for 1 and 2 Sensor Control Types.
     *
     * @return  If a Sensor is registered, returns the Sensor.getName()
     *          else the Sensor Name as set by #setControlSensorName
     */
    /*public*/  virtual  QString getControlSensorName()=0;

    /**
     * Set the Sensor State used by the Control
     * Does NOT update any changelisteners
     *
     * @param sense The state to react to, eg. Sensor.ACTIVE or Sensor.INACTIVE
     */
    /*public*/  virtual  void setControlSensorSense(int sense)=0;

    /**
     * Get the Fast Clock On Hour.
     *
     * @return  On Hour value
     */
    /*public*/  virtual  int getFastClockOnHour()=0;

    /**
     * Get the Fast Clock On Minute.
     *
     * @return  On Minute value
     */
    /*public*/  virtual  int getFastClockOnMin()=0;

    /**
     * Get the Fast Clock On Hours and Minutes Combined
     * Convenience method of separate getFastClockOnHour() and getFastClockOnMin()
     * @return  Total combined Minute value
     */
    /*public*/  virtual  int getFastClockOnCombined()=0;

    /**
     * Get the Fast Clock Off Hour.
     *
     * @return  Off Hour value
     */
    /*public*/  virtual  int getFastClockOffHour()=0;

    /**
     * Get the Fast Clock Off Minute.
     *
     * @return  Off Minute value
     */
    /*public*/  virtual  int getFastClockOffMin()=0;

    /**
     * Get the Fast Clock Off Hours and Minutes Combined
     * Convenience method of separate getFastClockOnHour() and getFastClockOnMin()
     * @return  Total combined Minute value
     */
    /*public*/  virtual  int getFastClockOffCombined()=0;

    /**
     * Set a Fast Clock LightControl Schedule.
     *
     * @param onHour Hour the Light should switch On
     * @param onMin Minute the Light should switch On
     * @param offHour Hour the Light should switch Off
     * @param offMin Minute the Light should switch Off     *
     */
    /*public*/  virtual  void setFastClockControlSchedule(int onHour, int onMin, int offHour, int offMin)=0;

    /**
     * Get the LightControl Turnout Name.
     *
     * @return  The Turnout name
     */
    /*public*/  virtual  QString getControlTurnoutName()=0;

    /**
     * Set the Turnout used by the Control
     * Does NOT update any changelisteners
     * <p>
     * A Turnout of this name is provided by the TurnoutManager
     * on LightControl Initialisation
     *
     * @param turnoutName The Turnout name
     */
    /*public*/  virtual  void setControlTurnout(QString turnoutName)=0;

    /**
     * Get the LightControl Turnout Name.
     *
     * @return  The Turnout name
     */
    /*public*/  virtual  int getControlTurnoutState()=0;

    /**
     * Set the Turnout State used by the Control
     * Does NOT update any changelisteners
     *
     * @param state Turnout state to act on, eg. Turnout.CLOSED or Turnout.THROWN
     */
    /*public*/  virtual  void setControlTurnoutState(int state)=0;

    /**
     * Get the Timed On Trigger Sensor name.
     *
     * @return  The Sensor Name as set by #setControlTimedOnSensorName
     */
    /*public*/  virtual  QString getTimedSensorName()=0;

    /**
     * Get the Timed On Trigger Sensor name.
     *
     * @return  If a Sensor is registered, returns the Sensor.getName()
     *          else the Sensor Name as set by #setControlTimedOnSensorName
     */
    /*public*/  virtual  QString getControlTimedOnSensorName()=0;

    /**
     * Set Sensor used by the Timed On Control
     * Does NOT update any changelisteners
     *
     * @param sensorName the Sensor name to be used for the On Trigger
     */
    /*public*/  virtual  void setControlTimedOnSensorName(QString sensorName)=0;

    /**
     * Get the Timed On Control Duration
     *
     * @return duration in ms
     */
    /*public*/  virtual  int getTimedOnDuration()=0;

    /**
     * Set Duration used by the Timed On Control
     * Does NOT update any changeListeners
     *
     * @param duration in ms following the Sensor On Trigger
     */
    /*public*/  virtual  void setTimedOnDuration(int duration)=0;

    /**
     * Get the Second Sensor name.
     * as used in the 2 Sensor Control Group.
     *
     * @return  If a 2nd Sensor is registered, returns the Sensor.getName()
     *          else the 2nd Sensor Name as set by #setControlSensor2Name
     */
    /*public*/  virtual  QString getControlSensor2Name()=0;

    /**
     * Set Sensor 2 used by the 2 Sensor Control
     * Does NOT update any changelisteners
     *
     * @param sensorName the Sensor 2 name
     */
    /*public*/  virtual  void setControlSensor2Name(QString sensorName)=0;

    /**
     * Set Light to control
     * Does NOT update any changelisteners
     *
     * @param l the Light object to control
     */
    /*public*/  virtual  void setParentLight(AbstractLight* l)=0;

    /**
     * Get a Textual Description
     * eg. Light Control TestLight ON when TestSensor is Active
     * eg. Light Control ON at 14:00, OFF at 15:00.
     *
     * @param lightName the Light Name, can be empty.
     * @return An I18N full-text description of thiscontrol
     */
    /*public*/  virtual  QString getDescriptionText(QString lightName)=0;

    /**
     * Activates a Light Control by control type. This method tests the control
     * type, and set up a control mechanism, appropriate for the control type.
     * Adds PropertyChangeListeners to Sensors / Turnout / Fast Clock as necessary
     */
    /*public*/  virtual  void activateLightControl()=0;

    /**
     * Check to see if we have the FastClock Follower has unique times for a single Light Control.
     * <p>
     * Hour / Minute combination must be unique for each Light to avoid flicker.
     *
     * @return true if the clock on time equals the off time, otherwise false.
     */
    /*public*/  virtual  bool onOffTimesFaulty()=0;

    /**
     * Check to see if we have the FastClock Follower has unique times for a single Light.
     * <p>
     * Hour / Minute combination must be unique for each Light to avoid flicker.
     *
     * @param compareList the ArrayList of other Light Controls to compare against
     * @return true if there are multiple exact same times
     */
    /*public*/  virtual  bool areFollowerTimesFaulty( QList<LightControl*> compareList )=0;

    /**
     * Deactivates a LightControl by control type. This method tests the control
     * type, and deactivates the control mechanism, appropriate for the control
     * type.
     */
    /*public*/  virtual  void deactivateLightControl()=0;

   virtual QObject* self() =0;
};

Q_DECLARE_INTERFACE(LightControl, "LightControl")
#endif // LIGHTCONTROL_H
