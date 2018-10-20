#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "propertychangelistener.h"
#include "abstractnamedbean.h"
#include "namedbeanhandle.h"
#include "reporter.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT Sensor : public AbstractNamedBean
{
 Q_OBJECT
 Q_ENUMS(STATES)
public:
    explicit Sensor(QObject *parent = 0);
    Sensor(QString sysName, QObject* parent);
    Sensor(QString sysName, QString userName, QObject* parent);
    /**
     * General input device representation.  Often subclassed for specific
     * types of sensors.
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
     * @author			Bob Jacobsen Copyright (C) 2001
     * @version			$Revision: 20842 $
     */
//    virtual interface Sensor extends NamedBean {

        // states are parameters; both closed and thrown is possible!
    enum STATES
    {
      ACTIVE       =0x02,
      INACTIVE     =0x04,
      UNKNOWN      =0x01,
      INCONSISTENT =0x08
    };

        /**
         * Known state on layout is a bound parameter
         * @return known state value
         */
        virtual int getKnownState() const /*= 0*/ {return 0;}

        /**
         * Potentially allow the user to set the known state on the layout.
         * This might not always be available, depending on the limits of the
         * underlying system and implementation.
         */
        virtual void setKnownState(int /*newState*/) /* =0*/{} // throws jmri.JmriException;

        /**
         * Request an update from the layout soft/hardware.  May not even
         * happen, and if it does it will happen later; listen for the result.
         */
        virtual void requestUpdateFromLayout() const/* =0*/ {}

        /**
         * Control whether the actual sensor input is
         * considered to be inverted, e.g. the normal
         * electrical signal that results in an ACTIVE state
         * now results in an INACTIVE state.
         * <p>
         * Changing this changes the state from
         * ACTIVE to INACTIVE and vice-versa, with notifications;
         * UNKNOWN and INCONSISTENT are left unchanged.
         */
        virtual void setInverted(bool /*inverted*/) const/* =0*/{}

        /**
         * Get the inverted state.  If true, the
         * electrical signal that results in an ACTIVE state
         * now results in an INACTIVE state.
         */
        virtual bool getInverted() const /*=0*/ { return false;}

        /**
         * Request a call-back when the bound KnownState property changes.
         */
        virtual void addPropertyChangeListener(PropertyChangeListener* /*l*/) const /*=0*/{}

        /**
         * Remove a request for a call-back when a bound property changes.
         */
        virtual void removePropertyChangeListener(PropertyChangeListener* /*l*/) const /*=0*/ {}

        /**
         * Remove references to and from this object, so that it can
         * eventually be garbage-collected.
         */
        virtual  void dispose() const /*=0*/ {}  // remove _all_ connections!

        /**
         * Used to return the Raw state of a sensor prior to the known state of a
         * sensor being set. The raw state value can be different when the sensor
         * debounce option is used.
         * @return raw state value
         */
        virtual int getRawState() const /*=0*/ {return UNKNOWN;}

        /**
        * Set the Active debounce delay in milliSeconds.
        * If a zero value is entered then debounce delay is de-activated.
        */
        virtual void setSensorDebounceGoingActiveTimer(long /*timer*/) const /*=0*/{}

        /**
        * Get the Active debounce delay in milliSeconds.
        */
        virtual long getSensorDebounceGoingActiveTimer() const /*=0*/{return 0;}

        /**
        * Set the InActive debounce delay in milliSeconds.
        * If a zero value is entered then debounce delay is de-activated.
        */
        virtual void setSensorDebounceGoingInActiveTimer(long /*timer*/) const /*=0*/{}

        /**
        * Get the InActive debounce delay in milliSeconds.
        */
        virtual long getSensorDebounceGoingInActiveTimer() const /*=0*/ {return 0;}

        /**
        * Use the timers specified in the Sensor manager, for the debounce delay
        */
        virtual void useDefaultTimerSettings(bool /*boo*/) const /*=0*/{}

        /**
        * Does this sensor use the default timers for
        */
        virtual bool useDefaultTimerSettings() const /*=0*/ {return false;}

        /**
         * Some sensor boards also serve the function of being able to report
         * back train identities via such methods as RailCom.
         * The setting and creation of the reporter against the sensor should be
         * done when the sensor is created.  This information is not saved.
         * <p>
         * returns null if there is no direct reporter.
         */
        virtual void setReporter(Reporter* /*re*/) const/* =0*/{}


        /**
         * Retrieve the reporter assocated with this sensor if there is one.
         * <p>
         * returns null if there is no direct reporter.
         */
        virtual Reporter* getReporter() const /*=0*/ {return NULL;}
    int thisAddr;

signals:
    
public slots:
private:
    
};

Q_DECLARE_INTERFACE(Sensor, "Sensor")
#endif // SENSOR_H
