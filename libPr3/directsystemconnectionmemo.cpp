#include "directsystemconnectionmemo.h"
#include "instancemanager.h"
#include "directcomponentfactory.h"
#include "trafficcontroller.h"
#include "loggerfactory.h"
#include "abstractthrottlemanager.h"
/**
 * Minimum required SystemConnectionMemo.
 *
 * @author Randall Wood randall.h.wood@alexandriasoftware.com
 */
// /*public*/ class DirectSystemConnectionMemo extends DefaultSystemConnectionMemo implements ConfiguringSystemConnectionMemo {



/*public*/ DirectSystemConnectionMemo::DirectSystemConnectionMemo(QObject * parent) : DefaultSystemConnectionMemo("N", "Others", parent){
    //this("N", "Others");
 InstanceManager::store(this, "DirectSystemConnectionMemo");

 // create and register the ComponentFactory
 InstanceManager::store(cf = new DirectComponentFactory(this),
         "ComponentFactory");

 log->debug("Created DirectSystemConnectionMemo");
}

/*public*/ DirectSystemConnectionMemo::DirectSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString userName, QObject * parent) : DefaultSystemConnectionMemo(prefix, userName, parent) {
    //super(prefix, userName);

    InstanceManager::store(this, "DirectSystemConnectionMemo");

    // create and register the ComponentFactory
    InstanceManager::store(cf = new DirectComponentFactory(this),
            "ComponentFactory");

    log->debug("Created DirectSystemConnectionMemo");
}


/**
 * Set the traffic controller instance associated with this connection memo.
 *
 * @param s jmri.jmrix.direct.TrafficController object to use.
 */
/*public*/ void DirectSystemConnectionMemo::setTrafficController(TrafficController* s){
    tc = s;
    store((Manager*)tc, "CommandStation");
    InstanceManager::store(tc,"CommandStation");
}

/**
 * Get the traffic controller instance associated with this connection memo.
 * @return traffic controller, provided if null.
 */
/*public*/ TrafficController* DirectSystemConnectionMemo::getTrafficController(){
    if (tc == nullptr) {
        setTrafficController(new TrafficController(this));
        log->debug("Auto create of TrafficController for initial configuration");
    }
    return tc;
}

/**
 * Set the traffic controller instance associated with this connection memo.
 *
 * @param s jmri.jmrix.direct.ThrottleManager object to use.
 */
/*public*/ void DirectSystemConnectionMemo::setThrottleManager(DefaultThrottleManager* s){
    store((Manager*)s,"ThrottleManager");
    InstanceManager::store((QObject*)get("ThrottleManager"),"ThrottleManager");
}

/**
 * Get the ThrottleManager instance associated with this connection memo.
 * @return throttle manager, provided if null.
 */
/*public*/ DefaultThrottleManager* DirectSystemConnectionMemo::getThrottleManager(){
#if 0
    return (ThrottleManager*) classObjectMap.computeIfAbsent(ThrottleManager.class,
            (Class c) -> {
                setThrottleManager(new ThrottleManager(this));
                log.debug("Auto create of ThrottleManager for initial configuration");
                return get(ThrottleManager.class);
            });
#else
 return nullptr;
#endif
}

//@Override
//protected ResourceBundle getActionModelResourceBundle() {
//    return null;
//}

//@Override
///*public*/ <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type) {
//    return new NamedBeanComparator<>();
//}

/*public*/ void DirectSystemConnectionMemo::configureManagers(){
    setThrottleManager((DefaultThrottleManager*)(new AbstractThrottleManager(this)));
    _register();
}

/*private*/ /*final*/ /*static*/ Logger* DirectSystemConnectionMemo::log = LoggerFactory::getLogger("DirectSystemConnectionMemo");
