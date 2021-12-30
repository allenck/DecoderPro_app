#include "acelasystemconnectionmemo.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "acelatrafficcontroller.h"
#include "acelaconnectiontypelist.h"
/**
 * Lightweight class to denote that a system is active, and provide general
 * information.
 * <p>
 * Objects of specific subtypes are registered in the instance manager to
 * activate their particular system.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 */
///*public*/  class AcelaSystemConnectionMemo extends DefaultSystemConnectionMemo implements ConfiguringSystemConnectionMemo {

/*public*/  AcelaSystemConnectionMemo::AcelaSystemConnectionMemo(QObject* parent)
 : DefaultSystemConnectionMemo("A", AcelaConnectionTypeList::CTI, parent)
{
    //this("A", AcelaConnectionTypeList.CTI); // default to A
 common();
}

/*public*/  AcelaSystemConnectionMemo::AcelaSystemConnectionMemo(/*@Nonnull*/ QString prefix, QString userName, QObject* parent)
: DefaultSystemConnectionMemo(prefix, userName, parent)
{
    //super(prefix, userName);
 common();
}
void AcelaSystemConnectionMemo::common()
{

    InstanceManager::store(this, "AcelaSystemConnectionMemo");
#if 0
    // create and register the AcelaComponentFactory for the GUI
    InstanceManager.store(cf = new jmri.jmrix.acela.swing.AcelaComponentFactory(this),
            jmri.jmrix.swing.ComponentFactory.class);
#endif
    log->debug("Created AcelaSystemConnectionMemo");
}
#if 0
/*public*/  AcelaSystemConnectionMemo(AcelaTrafficController* tc) {
    super("A", AcelaConnectionTypeList.CTI); // default to A
    this.tc = tc;

    InstanceManager.store(this, AcelaSystemConnectionMemo.class);

    // create and register the AcelaComponentFactory for the GUI
    InstanceManager.store(cf = new jmri.jmrix.acela.swing.AcelaComponentFactory(this),
            jmri.jmrix.swing.ComponentFactory.class);
    log.debug("Created AcelaSystemConnectionMemo");
}

#endif

/**
 * Provides access to the TrafficController for this particular connection.
 * @return traffic controller, provided if null.
 */
/*public*/  AcelaTrafficController* AcelaSystemConnectionMemo::getTrafficController() {
#if 0
    if (tc == null) {
        setAcelaTrafficController(new AcelaTrafficController());
        log.debug("Auto create of AcelaTrafficController for initial configuration");
    }
#endif
    return tc;
}
#if 0
/**
 * Set the traffic controller instance associated with this connection memo.
 *
 * @param tc jmri.jmrix.acela.AcelaTrafficController object to use
 */
/*public*/  void setAcelaTrafficController(AcelaTrafficController tc) {
    this.tc = tc;
}

/**
 * Configure the common managers for Acela connections. This puts the
 * common manager config in one place.
 */
/*public*/  void configureManagers() {

    InstanceManager.setLightManager(getLightManager());

    InstanceManager.setSensorManager(getSensorManager());
    getTrafficController().setSensorManager(getSensorManager());

    InstanceManager.setTurnoutManager(getTurnoutManager());
    getTrafficController().setTurnoutManager(getTurnoutManager());

    register(); // registers general type
}

/*public*/  AcelaTurnoutManager getTurnoutManager() {
    if (getDisabled()) {
        return null;
    }
    return (AcelaTurnoutManager) classObjectMap.computeIfAbsent(TurnoutManager.class, (Class c) -> new AcelaTurnoutManager(this));
}

/*public*/  AcelaSensorManager getSensorManager() {
    if (getDisabled()) {
        return null;
    }
    return (AcelaSensorManager) classObjectMap.computeIfAbsent(SensorManager.class,(Class c) -> new AcelaSensorManager(this));
}

/*public*/  AcelaLightManager getLightManager() {
    if (getDisabled()) {
        return null;
    }
    return (AcelaLightManager) classObjectMap.computeIfAbsent(LightManager.class,(Class c) -> new AcelaLightManager(this));
}

@Override
protected ResourceBundle getActionModelResourceBundle() {
    return ResourceBundle.getBundle("jmri.jmrix.acela.AcelaActionListBundle");
}

@Override
/*public*/  <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type) {
    return new NamedBeanComparator<>();
}

@Override
/*public*/  void dAcelaSystemConnectionMemoispose() {
    tc = null;
    InstanceManager.deregister(this, AcelaSystemConnectionMemo.class);
    if (cf != null) {
        InstanceManager.deregister(cf, jmri.jmrix.swing.ComponentFactory.class);
    }
    super.dispose();
}
#endif
/*private*/ /*final*/ /*static*/ Logger* AcelaSystemConnectionMemo::log = LoggerFactory::getLogger("AcelaSystemConnectionMemo");
