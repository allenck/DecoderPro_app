#ifndef ROUTE_H
#define ROUTE_H
#include "namedbean.h"
#include "turnout.h"

/**
 * Routes represent a collection of Turnouts that may be set at the same time.
 * <P>
 * When a user adds a Turnout to a Route, the user specifies whether the Turnout
 * state is to be set to CLOSED or THROWN when the Route is invoked (set).
 * <P>
 * Initially, Routes will have a fixed maximum number of sensors for simplicity
 * of implementation. We can revise this later to use Java Collections if this
 * becomes a problem.
 * <P>
 * To allow control via fascia panel pushbuttons, Routes may optionally be
 * invoked by one or more Sensors (up to the maximum allowed).
 * <p>
 * A route can be enabled or not.  By default it is enabled, and
 * will act when it's specified input conditions become satisfied.
 * When not enabled (the enabled parameter is false), the route will
 * not act even if the specified input conditions are satisfied.
 * When the route transitions from disabled to enabled, it may act,
 * depending on the conditions: Edge triggered conditions will not be satisfied,
 * but level-conditions may be.
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
 *
 * @author			Dave Duchamp Copyright (C) 2004
 * @author			Bob Jacobsen Copyright (C) 2007
 * @author          Simon Reader Copyright (C) 2008
 *
 * @version			$Revision: 19003 $
 */
/*public*/ /*interface*/class LIBPR3SHARED_EXPORT Route : public  AbstractNamedBean
{
 //Q_OBJECT
public:
 Route(QString systemName, QString userName = "", QObject* parent = 0) : AbstractNamedBean(systemName, userName, parent) {}
    /*public*/ static /*final*/ const int TOGGLE = 0x08;
    static /*final*/ const int MAX_CONTROL_SENSORS = 3;

    /**
     * Set enabled status.
     */
    /*public*/ virtual void setEnabled(bool /*state*/) =0;
    /**
     * Get enabled status
    */
    /*public*/ virtual bool getEnabled() const =0;

    /**
     * Set locked status.
     */
    /*public*/ virtual void setLocked(bool /*state*/)  =0;
    /**
     * Get locked status.
    */
    /*public*/ virtual bool getLocked() =0;

    /**
     * Has at least one lockable turnout.
    */
    /*public*/ virtual bool canLock() =0;
    // new interface for outputs

    /**
     * Add an output Turnout to this Route.
     * @param systemName The turnout system name
     * @param state must be Turnout.CLOSED, Turnout.THROWN, or Route.TOGGLE,
     *      which determines how the Turnout is to be switched when this Route is set
     */
    /*public*/ virtual bool addOutputTurnout(QString /*systemName*/, int /*state*/) =0;

    /**
     * Delete all output Turnouts from this Route.
     */
    /*public*/ virtual void clearOutputTurnouts() =0;

    /*public*/ virtual int getNumOutputTurnouts() = 0;
    /**
     * Inquire if a Turnout is included in this Route as an output.
     */
    /*public*/ virtual bool isOutputTurnoutIncluded(QString /*systemName*/) =0;

    /**
     * Method to get the Set State of an output Turnout.
     * @return -1 if the Turnout is not found
     */
    /*public*/ virtual int getOutputTurnoutSetState(QString /*systemName*/) = 0;

    /**
     * Get an output Turnout system name by Index.
     * @return null if there is no turnout with that index
     */
    /*public*/ virtual QString getOutputTurnoutByIndex(int /*index*/) =0;

    /**
     * Method to get the 'k'th output Turnout of the Route.
     * @return null if there are less than 'k' Turnouts defined
     */
    /*public*/ virtual Turnout* getOutputTurnout(int /*k*/) =0;

    /**
     * Method to get the desired state of 'k'th Turnout of the Route.
     * @return -1 if there are less than 'k' Turnouts defined
     */
    /*public*/ virtual int getOutputTurnoutState(int k) = 0;

    /**
     * Add an output Sensor to this Route.
     * @param systemName The sensor system name
     * @param state must be Sensor.ACTIVE, Sensor.INACTIVE, or Route.TOGGLE,
     *      which determines how the Sensor is to be switched when this Route is set
     */
    /*public*/ virtual bool addOutputSensor(QString /*systemName*/, int /*state*/) =0;

    /**
     * Delete all output Sensors from this Route.
     */
    /*public*/ virtual void clearOutputSensors()  =0;

    /*public*/ virtual int getNumOutputSensors()  =0;
    /**
     * Inquire if a Sensor is included in this Route as an output.
     */
    /*public*/ virtual bool isOutputSensorIncluded(QString /*systemName*/) =0;

    /**
     * Method to get the Set State of an output Sensor.
     * @return -1 if the Sensor is not found
     */
    /*public*/ virtual int getOutputSensorSetState(QString /*systemName*/) =0;

    /**
     * Get an output Sensor system name by Index.
     * @return null if there is no sensor with that index
     */
    /*public*/ virtual QString getOutputSensorByIndex(int /*index*/)=0;

    /**
     * Get the 'k'th output Sensor of the Route.
     * @return null if there are less than 'k' Sensor defined
     */
    /*public*/ virtual Sensor* getOutputSensor(int /*k*/) =0;

    /**
     * Get the desired state of 'k'th Sensor of the Route.
     * @return -1 if there are less than 'k' Sensors defined
     */
    /*public*/ virtual int getOutputSensorState(int k) = 0;


    /**
     * Set name of script file to be run when Route is fired.
     */
    /*public*/ virtual void setOutputScriptName(QString /*filename*/)  =0;

    /**
     * Get name of script file to be run when Route is fired.
     */
    /*public*/ virtual QString getOutputScriptName() =0;

    /**
     * Set name of sound file to be played when Route is fired.
     */
    /*public*/ virtual void setOutputSoundName(QString /*filename*/)  =0;

    /**
     * Get name of sound file to be played when Route is fired.
     */
    /*public*/ virtual QString getOutputSoundName() =0;

     /**
     * Method to set turnouts aligned sensor
     */
    /*public*/ virtual void setTurnoutsAlignedSensor (QString /*sensorSystemName*/)  =0;
    /**
     * Method to get system name of turnouts aligned sensor.
     */
    /*public*/ virtual QString getTurnoutsAlignedSensor() =0;

    /**
     * Method to get sensor of turnouts aligned sensor.
     */
    /*public*/ virtual Sensor* getTurnoutsAlgdSensor() =0;

    // Interface for control inputs

    /**
     * Method to add a Sensor to the list of control Sensors for this Route.
     */
    /*public*/ virtual bool addSensorToRoute(QString /*sensorSystemName*/, int /*mode*/) =0;

    enum ACTIONS
    {
    /*static*/ /*final*/ /*const int */ONACTIVE = 0,    // route fires if sensor goes active
    /*static*/ /*final*/ /*const int */ONINACTIVE = 1,  // route fires if sensor goes inactive
    /*static*/ /*final*/ /*const int*/ VETOACTIVE = 2,  // sensor must be active for route to fire
    /*static*/ /*final*/ /*const int*/ VETOINACTIVE = 3,  // sensor must be inactive for route to fire

    /*static*/ /*final*/ /*const int*/ ONCHANGE = 32,   // route fires if turnout or sensor changes

    /*static*/ /*final*/ /*const int*/ ONCLOSED = 2,    // route fires if turnout goes closed
    /*static*/ /*final*/ /*const int*/ ONTHROWN = 4,  // route fires if turnout goes thrown
    /*static*/ /*final*/ /*const int*/ VETOCLOSED = 8,  // turnout must be closed for route to fire
    /*static*/ /*final*/ /*const int*/ VETOTHROWN = 16  // turnout must be thrown for route to fire
    };
    //Q_ENUM(ACTIONS)
    /**
     * Method to delete all control Sensors from this Route.
     */
    /*public*/ virtual void clearRouteSensors()  =0;

    /**
     * Method to get the SystemName of a control Sensor in this Route.
     *
     *@param index The index in the Sensor array of the requested
     *      Sensor.
     *@return  null If there is no Sensor with that 'index', or if 'index'
     *      is not in the range 0 thru MAX_SENSORS-1.
     */
    /*public*/ virtual QString getRouteSensorName(int /*index*/) =0;

    /**
     * Method to get the Sensor of a control Sensor in this Route.
     *
     *@param index The index in the Sensor array of the requested
     *      Sensor.
     *@return  null If there is no Sensor with that 'index', or if 'index'
     *      is not in the range 0 thru MAX_SENSORS-1.
     */
    /*public*/ virtual Sensor* getRouteSensor(int /*index*/) =0;

    /**
     * Method to get the mode of a particular Sensor in this Route.
     *
     *@param index The index in the Sensor array of the requested
     *      Sensor.
     *@return ONACTIVE if there is no Sensor with that 'index', or if 'index'
     *      is not in the range 0 thru MAX_SENSORS-1
     */
    /*public*/ virtual int getRouteSensorMode(int index) = 0;

    /**
     * Method to set the SystemName of a control Turnout for this Route.
     */
    /*public*/ virtual void setControlTurnout(QString /*turnoutSystemName*/) =0;

    /**
     * Method to get the SystemName of a control Turnout for this Route.
     */
    /*public*/ virtual QString getControlTurnout() =0;

    /**
     * Method to get the Turnout of a control Turnout for this Route.
     */
    /*public*/ virtual Turnout* getCtlTurnout() =0;

    /**
     * Method to set the State of control Turnout that fires this Route.
     */
    /*public*/ virtual void setControlTurnoutState(int /*turnoutState*/)  =0;

    /**
     * Method to get the State of control Turnout that fires this Route.
     */
    /*public*/ virtual int getControlTurnoutState() = 0;

    /**
     * Method to set the SystemName of a lock control Turnout for this Route.
     */
    /*public*/ virtual void setLockControlTurnout(QString /*turnoutSystemName*/)  =0;

    /**
     * Method to get the SystemName of a lock control Turnout for this Route.
     */
    /*public*/ virtual QString getLockControlTurnout() =0;

    /**
     * Method to get the Turnout of a lock control Turnout for this Route.
     */
    /*public*/ virtual Turnout* getLockCtlTurnout() =0;

    /**
     * Method to set the State of the lock control Turnout that locks this Route.
     */
    /*public*/ void virtual setLockControlTurnoutState(int /*turnoutState*/)  =0;

    /**
     * Method to get the State of the lock control Turnout that locks this Route.
     */
    /*public*/ virtual int getLockControlTurnoutState() = 0;

    /**
     * Method to set delay (milliseconds) between issuing Turnout commands.
     */
    /*public*/ virtual void setRouteCommandDelay(int /*delay*/) =0;

    /**
     * Method to get delay (milliseconds) between issuing Turnout commands.
     */
    /*public*/ virtual int getRouteCommandDelay() = 0;

    /**
     * Method to set the Route.
     *<p>
     * Sets all Route Turnouts to the state shown in the Route definition.
     */
    /*public*/ virtual void setRoute() =0;

    /**
     * Activate the Route.
     *<p>
     * This starts route processing by connecting to inputs, etc.
     * A Route must be activated before it will fire.
     */
    /*public*/ virtual void activateRoute()  =0;

    /**
     * Deactivate the Route.
     * <p>
     * This disconnects the Route from
     * all other objects and stops it from processing.
     * A Route must be deactivated before it's input
     * and output definitions are changed.
     */
    /*public*/ virtual void deActivateRoute() =0;

    /*public*/ virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(Route, "Route")
#endif // ROUTE_H
