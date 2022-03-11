#include "proxyanalogiomanager.h"
#include "instancemanager.h"
#include "internalanalogiomanager.h"
#include "proxymetermanager.h"
#include "analogio.h"

/**
 * Implementation of a AnalogIOManager that can serve as a proxy for multiple
 * system-specific implementations.
 *
 * @author  Bob Jacobsen      Copyright (C) 2010, 2018
 * @author  Dave Duchamp      Copyright (C) 2004
 * @author  Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/  class ProxyAnalogIOManager extends AbstractProxyManager<AnalogIO>
//        implements AnalogIOManager {


/*public*/  ProxyAnalogIOManager::ProxyAnalogIOManager(QObject* parent)
 : AbstractProxyManager(parent) {
 setObjectName("ProxyAnalogIOManager");
    internalAnalogIOManager = new InternalAnalogIOManager((InternalSystemConnectionMemo*)InstanceManager::getDefault(
            "InternalSystemConnectionMemo"));
    addManager(internalAnalogIOManager);
}

//@Nonnull
/*public*/  ProxyAnalogIOManager* ProxyAnalogIOManager::init() {
    // Note that not all lights in LightManager are VariableLight.
// TODO:    addBeanType("Meter", (AbstractProxyManager*)InstanceManager::getDefault("MeterManager"));
    addBeanType("VariableLight", (AbstractProxyManager*)InstanceManager::getDefault("LightManager"));
    return this;
}

//@Override
/*public*/  int ProxyAnalogIOManager::getXMLOrder() const  {
    return Manager::ANALOGIOS;
}

//@Override
/*protected*/ AbstractManager/*<AnalogIO>*/* ProxyAnalogIOManager::makeInternalManager() const{
    return internalAnalogIOManager;
}

//@Override
//@Nonnull
/*public*/  QString ProxyAnalogIOManager::getBeanTypeHandled(bool plural) const{
    return plural ? tr("AnalogIOs") : tr("AnalogIO");
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  /*Class<AnalogIO>*/QString ProxyAnalogIOManager::getNamedBeanClass() const{
    return "AnalogIO";
}

/* {@inheritDoc} */
//@Override
//@CheckReturnValue
//@CheckForNull
/*public*/  NamedBean* ProxyAnalogIOManager::getBySystemName(/*@Nonnull*/ QString systemName) {
    NamedBean* analogIO = AbstractProxyManager::getBySystemName(systemName);
    if (analogIO == nullptr) {
        analogIO = initInternal()->getBySystemName(systemName);
    }
    return analogIO;
}

/** {@inheritDoc} */
//@Override
//@CheckForNull
/*public*/  NamedBean* ProxyAnalogIOManager::getByUserName(/*@Nonnull*/ QString userName) {
    NamedBean* analogIO = AbstractProxyManager::getByUserName(userName);
    if (analogIO == nullptr) {
        analogIO = initInternal()->getByUserName(userName);
    }
    return analogIO;
}

//@Override
/*public*/  void ProxyAnalogIOManager::propertyChange(PropertyChangeEvent* e) {
    AbstractProxyManager::propertyChange(e);

    // When we add or remove the Light to the internal AnalogIO manager,
    // we get a propertyChange for that.
    if (muteUpdates) return;

    if ("beans" == (e->getPropertyName())) {
    #if 0 // TODO:
        for (/*Class<? extends AnalogIO>*/QString clazz : registerBeans) {
            // A NamedBean is added
            if ((e->getNewValue() != null)
                    && clazz.isAssignableFrom(e.getNewValue().getClass())) {
                Manager<AnalogIO> internalManager = initInternal();
                muteUpdates = true;
                internalManager.register((AnalogIO) e.getNewValue());
                muteUpdates = false;
            }

            // A NamedBean is removed
            if ((e.getOldValue() != null)
                    && clazz.isAssignableFrom(e.getOldValue().getClass())) {
                Manager<AnalogIO> internalManager = initInternal();
                muteUpdates = true;
                internalManager.deregister((AnalogIO) e.getOldValue());
                muteUpdates = false;
            }
        }
#endif
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ProxyAnalogIOManager::dispose() {
    AbstractProxyManager::dispose();
    for (Manager/*<? extends NamedBean>*/* manager : registerBeanManagers) {
        manager->removePropertyChangeListener("beans", this);
    }
}

/**
 * Add a type of NamedBean, for example VariableLight, that should be also registred in AnalogIOManager.
 * @param clazz the NamedBean class that should be registered in this manager
 * @param manager the manager that managers the NamedBeans of type clazz
 */
//@Override
/*public*/  void ProxyAnalogIOManager::addBeanType(/*Class<? extends AnalogIO>*/QString clazz, Manager/*<? extends NamedBean>*/* manager) {
    registerBeans.append(clazz);
    manager->addPropertyChangeListener("beans", this);

    // Add all the existing beans to the manager
    Manager/*<AnalogIO>*/* internalManager = initInternal();
    muteUpdates = true;
    for (NamedBean* bean : manager->getNamedBeanSet()) {
        internalManager->Register(/*(AnalogIO*)*/ bean);
    }
    muteUpdates = false;
}

/**
 * Remove a type of NamedBean, for example VariableLight, from beeing registred in AnalogIOManager.
 * @param clazz the NamedBean class that should be registered in this manager
 * @param manager the manager that managers the NamedBeans of type clazz
 */
//@Override
/*public*/  void ProxyAnalogIOManager::removeBeanType(/*Class<? extends AnalogIO>*/QString clazz, Manager/*<? extends NamedBean>*/* manager) {
    manager->removePropertyChangeListener("beans", this);
    registerBeans.removeOne(clazz);
}
