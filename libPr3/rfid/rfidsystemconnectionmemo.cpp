#include "rfidsystemconnectionmemo.h"
#include "instancemanager.h"
#include "rfidtrafficcontroller.h"
#include "rfidcomponentfactory.h"

/**
 * Lightweight class to denote that a system is active, and provide general
 * information.
 * <p>
 * Objects of specific subtypes are registered in the instance manager to
 * activate their particular system.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 * <P>
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Matthew Harris Copyright (C) 2011
 */
// /*public*/ class RfidSystemConnectionMemo extends jmri.jmrix.SystemConnectionMemo {


/*public*/ RfidSystemConnectionMemo::RfidSystemConnectionMemo(RfidTrafficController* rt, QObject *parent) : DefaultSystemConnectionMemo("F", "Rfid", parent)
{
    //this();
    setRfidTrafficController(rt);
}

/*public*/ RfidSystemConnectionMemo::RfidSystemConnectionMemo( QObject *parent) : DefaultSystemConnectionMemo("F", "Rfid", parent)
{
    //super("F", "Rfid");
    _register(); // registers general type
    InstanceManager::store(this, "RfidSystemConnectionMemo"); // also register as specific type

    // Create and register the ComponentFactory
    InstanceManager::store(new RfidComponentFactory(this),
            "ComponentFactory");
}

/*public*/ RfidTrafficController* RfidSystemConnectionMemo::getTrafficController() {
    return rt;
}

/*public*/ /*final*/ void RfidSystemConnectionMemo::setRfidTrafficController(RfidTrafficController* rt) {
    this->rt = rt;
    rt->setAdapterMemo(this);
}

/*public*/ void RfidSystemConnectionMemo::configureManagers(RfidSensorManager* sensorManager, RfidReporterManager* reporterManager) {
    this->sensorManager = sensorManager;
    this->reporterManager = reporterManager;
    InstanceManager::setSensorManager(this->sensorManager);
    InstanceManager::setReporterManager(this->reporterManager);
}

/*public*/ RfidProtocol* RfidSystemConnectionMemo::getProtocol() {
    return protocol;
}

/*public*/ /*final*/ void RfidSystemConnectionMemo::setProtocol(RfidProtocol* protocol) {
    this->protocol = protocol;
}

/*public*/ RfidSensorManager* RfidSystemConnectionMemo::getSensorManager() {
    return sensorManager;
}

/*public*/ RfidReporterManager* RfidSystemConnectionMemo::getReporterManager() {
    return reporterManager;
}

/**
 * Tells which managers this class provides.
 *
 * @param type manager type to check
 * @return true if provided
 */
//@Override
/*public*/ bool RfidSystemConnectionMemo::provides(/*Class<?> */QString type) {
    if (type == ("SensorManager")) {
        return true;
    }
    if (type == "ReporterManager") {
        return true;
    }
    // Delegate to super class
    return SystemConnectionMemo::provides(type);
}

//@Override
//@SuppressWarnings("unchecked")
/*public*/ /*<T> */Manager *RfidSystemConnectionMemo::get(/*Class<?>*/QString T) {
    if (getDisabled()) {
        return nullptr;
    }
    if (T == "SensorManager") {
        return (Manager*) getSensorManager();
    }
    if (T == "ReporterManager") {
        return (Manager*) getReporterManager();
    }
    // nothing, by default
    return nullptr;
}
#if 0
@Override
/*protected*/ ResourceBundle getActionModelResourceBundle() {
    return ResourceBundle.getBundle("jmri.jmrix.rfid.RfidActionListBundle");
}
#endif

//@Override
/*public*/ void RfidSystemConnectionMemo::dispose() {
    rt = nullptr;
    InstanceManager::deregister(this, "RfidSystemConnectionMemo");
    if (reporterManager != nullptr) {
        InstanceManager::deregister(reporterManager, "RfidReporterManager");
    }
    if (sensorManager != nullptr) {
        InstanceManager::deregister(sensorManager, "RfidSensorManager");
    }
    protocol = nullptr;
    SystemConnectionMemo::dispose();
}

