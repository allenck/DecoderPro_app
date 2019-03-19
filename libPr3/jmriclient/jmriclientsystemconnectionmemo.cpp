#include "jmriclientsystemconnectionmemo.h"
#include "jmriclienttrafficcontroller.h"
#include "instancemanager.h"

/**
 * Lightweight class to denote that a system is active and provide general
 * information.
 * <p>
 * Objects of specific subtypes are registered in the instance manager to
 * activate their particular system.
 *
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class JMRIClientSystemConnectionMemo extends jmri.jmrix.SystemConnectionMemo {

/*public*/ JMRIClientSystemConnectionMemo::JMRIClientSystemConnectionMemo(JMRIClientTrafficController* jt)
 : SystemConnectionMemo("J", "JMRI Client")
{
    //super("J", "JMRI Client");
    this->jt = jt;
    _register(); // registers general type
    InstanceManager::store(this, "JMRIClientSystemConnectionMemo"); // also register as specific type
#if 0
    // create and register the JMRIClientComponentFactory
    InstanceManager::store(cf = new jmri.jmrix.jmriclient.swing.JMRIClientComponentFactory(this),
            jmri.jmrix.swing.ComponentFactory.class);
#endif
}

/*public*/ JMRIClientSystemConnectionMemo::JMRIClientSystemConnectionMemo() : SystemConnectionMemo("J", "JMRI Client") {
    //super("J", "JMRIClient");
    this->jt = new JMRIClientTrafficController();
    _register(); // registers general type
    InstanceManager::store(this, "JMRIClientSystemConnectionMemo"); // also register as specific type
#if 0
    // create and register the JMRIClientComponentFactory
    InstanceManager.store(cf = new jmri.jmrix.jmriclient.swing.JMRIClientComponentFactory(this), jmri.jmrix.swing.ComponentFactory.class);
#endif
}



/**
 * Provides access to the TrafficController for this particular connection.
 */
/*public*/ JMRIClientTrafficController* JMRIClientSystemConnectionMemo::getJMRIClientTrafficController() {
    return jt;
}

/*public*/ void JMRIClientSystemConnectionMemo::setJMRIClientTrafficController(JMRIClientTrafficController* jt) {
    this->jt = jt;
}

//@Override
/*public*/ void JMRIClientSystemConnectionMemo::dispose() {
    jt = nullptr;
    InstanceManager::deregister(this, "JMRIClientSystemConnectionMemo");
    if (cf != nullptr) {
        InstanceManager::deregister((QObject*)cf, "ComponentFactory");
    }
    SystemConnectionMemo::dispose();
}

/**
 * Configure the common managers for Internal connections. This puts the
 * common manager config in one place.
 */
/*public*/ void JMRIClientSystemConnectionMemo::configureManagers() {
#if 0 // TODO:
    setPowerManager(new jmri.jmrix.jmriclient.JMRIClientPowerManager(this));
    jmri.InstanceManager.store(getPowerManager(), jmri.PowerManager.class);
    setTurnoutManager(new jmri.jmrix.jmriclient.JMRIClientTurnoutManager(this));
    jmri.InstanceManager.setTurnoutManager(getTurnoutManager());
    setSensorManager(new jmri.jmrix.jmriclient.JMRIClientSensorManager(this));
    jmri.InstanceManager.setSensorManager(getSensorManager());
    setLightManager(new jmri.jmrix.jmriclient.JMRIClientLightManager(this));
    jmri.InstanceManager.setLightManager(getLightManager());
    setReporterManager(new jmri.jmrix.jmriclient.JMRIClientReporterManager(this));
    jmri.InstanceManager.setReporterManager(getReporterManager());
#endif
}

/**
 * Request all status from the configured managers.
 */
/*public*/ void JMRIClientSystemConnectionMemo::requestAllStatus() {
#if 0 //TODO:
    getTurnoutManager().getNamedBeanSet().forEach((turn) -> {
        ((JMRIClientTurnout)(turn)).requestUpdateFromLayout();
    });
    getSensorManager().getNamedBeanSet().forEach((sen) -> {
        ((JMRIClientSensor)(sen)).requestUpdateFromLayout();
    });
    getLightManager().getNamedBeanSet().forEach((light) -> {
        ((JMRIClientLight)light).requestUpdateFromLayout();
    });
    getReporterManager().getNamedBeanSet().forEach((rep) -> {
        ((JMRIClientReporter)(rep)).requestUpdateFromLayout();
    });
#endif
}

/*
 * Provides access to the Power Manager for this particular connection.
 */
/*public*/ PowerManager* JMRIClientSystemConnectionMemo::getPowerManager() {
    return powerManager;
}

/*public*/ void JMRIClientSystemConnectionMemo::setPowerManager(PowerManager* p) {
    powerManager = p;
}

/*
 * Provides access to the Sensor Manager for this particular connection.
 */
/*public*/ SensorManager* JMRIClientSystemConnectionMemo::getSensorManager() {
    return sensorManager;

}

/*public*/ void JMRIClientSystemConnectionMemo::setSensorManager(SensorManager* s) {
    sensorManager = s;
}


/*
 * Provides access to the Turnout Manager for this particular connection.
 * NOTE: Turnout manager defaults to NULL
 */
/*public*/ TurnoutManager* JMRIClientSystemConnectionMemo::getTurnoutManager() {
    return turnoutManager;

}

/*public*/ void JMRIClientSystemConnectionMemo::setTurnoutManager(TurnoutManager* t) {
    turnoutManager = t;
}

/*
 * Provides access to the Light Manager for this particular connection.
 * NOTE: Light manager defaults to NULL
 */
/*public*/ LightManager* JMRIClientSystemConnectionMemo::getLightManager() {
    return lightManager;
}

/*public*/ void JMRIClientSystemConnectionMemo::setLightManager(LightManager* t) {
    lightManager = t;
}

/*
 * Provides access to the Reporter Manager for this particular connection.
 * NOTE: Reporter manager defaults to NULL
 */
/*public*/ ReporterManager* JMRIClientSystemConnectionMemo::getReporterManager() {
    return reporterManager;
}

/*public*/ void JMRIClientSystemConnectionMemo::setReporterManager(ReporterManager* t) {
    reporterManager = t;
}


/*public*/ void JMRIClientSystemConnectionMemo::setTransmitPrefix(QString tPrefix) {
    transmitPrefix = tPrefix.toUpper();
}

/*public*/ QString JMRIClientSystemConnectionMemo::getTransmitPrefix() {
    if (transmitPrefix == "") {
        return getSystemPrefix();
    }
    return transmitPrefix;
}


//@Override
//protected ResourceBundle getActionModelResourceBundle() {
//    //No actions that can be loaded at startup
//    return null;
//}

//@Override
//@SuppressWarnings("unchecked")
/*public*/  QObject *JMRIClientSystemConnectionMemo::get(QString T) {
    if (getDisabled()) {
        return nullptr;
    }
    if (T == ("PowerManager")) {
        return  (Manager*) getPowerManager();
    }
    if (T == ("SensorManager")) {
        return  (Manager*) getSensorManager();
    }
    if (T == ("TurnoutManager")) {
        return  (Manager*) getTurnoutManager();
    }
    if (T == ("LightManager")) {
        return  (Manager*) getLightManager();
    }
    if (T == ("ReporterManager")) {
        return  (Manager*) getReporterManager();
    }
    return SystemConnectionMemo::get (T);
}

/**
 * Tells which managers this class provides.
 */
//@Override
/*public*/ bool JMRIClientSystemConnectionMemo::provides(QString type) {
    if (getDisabled()) {
        return false;
    }
    if (type == ("PowerManager")) {
        return (nullptr != powerManager);
    }
    if (type == ("SensorManager")) {
        return (nullptr != sensorManager);
    }
    if (type == ("TurnoutManager")) {
        return (nullptr != turnoutManager);
    }
    if (type == ("LightManager")) {
        return (nullptr != lightManager);
    }
    if (type == ("ReporterManager")) {
        return (nullptr != reporterManager);
    }
    return SystemConnectionMemo::provides(type);
}
