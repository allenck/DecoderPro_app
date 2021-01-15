#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H
#include <QString>
#include "sensor.h"
#include "abstractmanager.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT SensorManager : public AbstractManager
{
    Q_OBJECT
public:
    explicit SensorManager(QObject *parent = nullptr) : AbstractManager(parent) {}
    SensorManager(SystemConnectionMemo* memo, QObject *parent = nullptr) : AbstractManager(memo,parent) {}
    /**
     * Interface for controlling sensors.
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
     * @author	Bob Jacobsen Copyright (C) 2001
     * @version	$Revision: 18178 $
     */
//    public interface SensorManager extends Manager {

        /**
         * Locate via user name, then system name if needed.
         * If that fails, create a new sensor: If the name
         * is a valid system name, it will be used for the new
         * sensor.  Otherwise, the makeSystemName method
         * will attempt to turn it into a valid system name.
         *
         * @param name User name, system name, or address which
         *      can be promoted to system name
         * @return Never null
         * @throws IllegalArgumentException if Sensor doesn't
         * already exist and the manager cannot create the Sensor
         * due to e.g. an illegal name or name that can't be parsed.
         */
        virtual  Sensor* provideSensor(QString /*name*/) { return NULL;}
        //@Override
        /** {@inheritDoc} */
        virtual /*default*/ /*public*/ Sensor* provide(/*@Nonnull*/ QString name) throw (IllegalArgumentException)
        { return provideSensor(name); }


        /**
         * Locate via user name, then system name if needed.
         * Does not create a new one if nothing found
         *
         * @param name
         * @return null if no match found
         */
        virtual Sensor* getSensor(QString /*name*/) const { return NULL;}

        // to free resources when no longer used
        virtual void dispose() const  {}

        /**
         * Return an instance with the specified system and user names.
         * Note that two calls with the same arguments will get the same instance;
         * there is only one Sensor object representing a given physical turnout
         * and therefore only one with a specific system or user name.
         *<P>
         * This will always return a valid object reference; a new object will be
         * created if necessary. In that case:
         *<UL>
         *<LI>If a null reference is given for user name, no user name will be associated
         *    with the Sensor object created; a valid system name must be provided
         *<LI>If both names are provided, the system name defines the
         *    hardware access of the desired sensor, and the user address
         *    is associated with it. The system name must be valid.
         *</UL>
         * Note that it is possible to make an inconsistent request if both
         * addresses are provided, but the given values are associated with
         * different objects.  This is a problem, and we don't have a
         * good solution except to issue warnings.
         * This will mostly happen if you're creating Turnouts when you should
         * be looking them up.
         * @return requested Sensor object (never null)
         * @throws IllegalArgumentException if cannot create the Sensor
         * due to e.g. an illegal name or name that can't be parsed.
         */
        virtual Sensor* newSensor(QString /*systemName*/, QString /*userName*/) { return NULL;}

        virtual NamedBean* getByUserName(QString /*s*/)  const { return NULL;}
        virtual NamedBean* getBySystemName(QString /*s*/) const { return NULL;}

//    virtual  QStringList getSystemNameList() const { return QStringList();}

        /**
         * Requests status of all layout sensors under this Sensor Manager.
         * This method may be invoked whenever the status of sensors needs to be updated from
         *		the layout, for example, when an XML configuration file is read in.
         * Note that there is a null implementation of this method in AbstractSensorManager.
         *		This method only needs be implemented in system-specific Sensor Managers where
         *		readout of sensor status from the layout is possible.
         */
        virtual void updateAll() const {}

        /**
        * A method that determines if it is possible to add a range
        * of sensors in numerical order eg 10 to 30 will return true.
        * where as if the address format is 1b23 this will return false.
        **/


         virtual bool allowMultipleAdditions(QString /*systemName*/) {return false;}

       /**
        * Determine if the address supplied is valid and free, if not then it shall
        * return the next free valid address up to a maximum of 10 address away from
        * the initial address.
        * @param prefix - The System Prefix used to make up the systemName
        * @param curAddress - The hardware address of the turnout we which to check.
        */

        virtual QString getNextValidAddress(QString /*curAddress*/, QString /*prefix*/) {return "";}// throws JmriException;

        virtual QString createSystemName(QString /*curAddress*/, QString /*prefix*/) const {return "";}// throws JmriException;

        virtual long getDefaultSensorDebounceGoingActive() {return 0;}
        virtual long getDefaultSensorDebounceGoingInActive() {return 0;}

        virtual void setDefaultSensorDebounceGoingActive(long /*timer*/) {}

        virtual void setDefaultSensorDebounceGoingInActive(long /*timer*/) {}
        /**
         * Do the sensor objects provided by this manager support configuring
         * an internal pullup or pull down resistor?
         *
         * @return true if pull up/pull down configuration is supported.
         */
        virtual /*public*/ bool isPullResistanceConfigurable() {return false;}
    /*public*/ QString toString() {return "SensorManager";}
signals:
    
public slots:
    
};
Q_DECLARE_INTERFACE(SensorManager, "Sensor manager")
#endif // SENSORMANAGER_H
