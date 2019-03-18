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
#if 0
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
#if 0
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

#if 0
/*
 * Provides access to the Sensor Manager for this particular connection.
 */
/*public*/ SensorManager getSensorManager() {
    return sensorManager;

}

/*public*/ void setSensorManager(SensorManager s) {
    sensorManager = s;
}

private SensorManager sensorManager = null;

/*
 * Provides access to the Turnout Manager for this particular connection.
 * NOTE: Turnout manager defaults to NULL
 */
/*public*/ TurnoutManager getTurnoutManager() {
    return turnoutManager;

}

/*public*/ void setTurnoutManager(TurnoutManager t) {
    turnoutManager = t;
}

private TurnoutManager turnoutManager = null;

/*
 * Provides access to the Light Manager for this particular connection.
 * NOTE: Light manager defaults to NULL
 */
/*public*/ LightManager getLightManager() {
    return lightManager;
}

/*public*/ void setLightManager(LightManager t) {
    lightManager = t;
}
private LightManager lightManager = null;

/*
 * Provides access to the Reporter Manager for this particular connection.
 * NOTE: Reporter manager defaults to NULL
 */
/*public*/ ReporterManager getReporterManager() {
    return reporterManager;
}

/*public*/ void setReporterManager(ReporterManager t) {
    reporterManager = t;
}

private ReporterManager reporterManager = null;

/*public*/ void setTransmitPrefix(String tPrefix) {
    transmitPrefix = tPrefix.toUpperCase();
}

/*public*/ String getTransmitPrefix() {
    if (transmitPrefix == null) {
        return getSystemPrefix();
    }
    return transmitPrefix;
}

private String transmitPrefix = null;

//@Override
protected ResourceBundle getActionModelResourceBundle() {
    //No actions that can be loaded at startup
    return null;
}

//@Override
@SuppressWarnings("unchecked")
/*public*/ <T> T get(Class<?> T) {
    if (getDisabled()) {
        return null;
    }
    if (T.equals(jmri.PowerManager.class)) {
        return (T) getPowerManager();
    }
    if (T.equals(jmri.SensorManager.class)) {
        return (T) getSensorManager();
    }
    if (T.equals(jmri.TurnoutManager.class)) {
        return (T) getTurnoutManager();
    }
    if (T.equals(jmri.LightManager.class)) {
        return (T) getLightManager();
    }
    if (T.equals(jmri.ReporterManager.class)) {
        return (T) getReporterManager();
    }
    return super.get(T);
}

/**
 * Tells which managers this class provides.
 */
//@Override
/*public*/ bool provides(Class<?> type) {
    if (getDisabled()) {
        return false;
    }
    if (type.equals(jmri.PowerManager.class)) {
        return (null != powerManager);
    }
    if (type.equals(jmri.SensorManager.class)) {
        return (null != sensorManager);
    }
    if (type.equals(jmri.TurnoutManager.class)) {
        return (null != turnoutManager);
    }
    if (type.equals(jmri.LightManager.class)) {
        return (null != lightManager);
    }
    if (type.equals(jmri.ReporterManager.class)) {
        return (null != reporterManager);
    }
    return super.provides(type);
}

#endif
