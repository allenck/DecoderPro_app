#include "proxymetermanager.h"
#include "manager.h"
#include "internalsystemconnectionmemo.h"
#include "instancemanager.h"
#include "defaultmeter.h"

/**
 * Implementation of a MeterManager that can serve as a proxy for multiple
 * system-specific implementations.
 *
 * @author  Bob Jacobsen      Copyright (C) 2010, 2018
 * @author  Dave Duchamp      Copyright (C) 2004
 * @author  Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ class ProxyMeterManager extends AbstractProxyManager<Meter>
//        implements MeterManager {

    ProxyMeterManager::ProxyMeterManager(QObject *parent) : AbstractProxyMeterManager(parent)
    {
     setObjectName("ProxyMeterManager");
    }


    //@Override
    /*public*/ int ProxyMeterManager::getXMLOrder() const {
        return Manager::METERS;
    }

    //@Override
    /*protected*/ ProxyMeterManager* ProxyMeterManager::makeInternalManager() const {
        return (ProxyMeterManager*)((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"))->getMeterManager();
    }

    //@Override
    //@Nonnull
    /*public*/ QString ProxyMeterManager::getBeanTypeHandled(bool plural) {
        return (plural ? tr("Meters") : tr("Meter"));
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ProxyMeterManager::getNamedBeanClass() {
        return "Meter";
    }

    /* {@inheritDoc} */
    //@Override
    //@CheckReturnValue
    //@CheckForNull
    /*public*/ NamedBean* ProxyMeterManager::getBySystemName(/*@Nonnull*/ QString systemName) const {
        NamedBean* meter = AbstractProxyMeterManager::getBySystemName(systemName);
        if (meter == nullptr) {
            meter = ((AbstractMeterManager*) initInternal())->getBySystemName(systemName);
        }
        return meter;
    }

    /** {@inheritDoc} */
    //@Override
    //@CheckForNull
    /*public*/ NamedBean* ProxyMeterManager::getByUserName(/*@Nonnull*/ QString userName) const {
        NamedBean* meter = AbstractProxyMeterManager::getByUserName(userName);
        if (meter == nullptr) {
            meter = ((AbstractMeterManager*)initInternal())->getByUserName(userName);
        }
        return meter;
    }

    /**
     * Try to create a system manager.If this proxy manager is able to create
     * a system manager, the concrete class must implement this method.
     *
     * @param memo the system connection memo for this connection
     * @return the new manager or null if it's not possible to create the manager
     */
    //@Override
    /*protected*/ MeterManager* ProxyMeterManager::createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo) const {
        MeterManager* m = new AbstractMeterManager(memo);
        InstanceManager::setMeterManager(m);
        return m;
    }

    //@Override
    /*public*/ void ProxyMeterManager::propertyChange(PropertyChangeEvent* e) {
        AbstractProxyMeterManager::propertyChange(e);

        // When we add or remove the Light to the internal Meter manager,
        // we get a propertyChange for that.
        if (muteUpdates) return;

        if ("beans" == (e->getPropertyName())) {
#if 0
            for (QString clazz : registerBeans) {
                // A NamedBean is added
                if (!e->getNewValue().isNull())
                        && clazz.isAssignableFrom(e.getNewValue().getClass())) {
                    Manager/*<Meter>*/ internalManager = initInternal();
                    muteUpdates = true;
                    internalManager.Register((Meter) e->getNewValue());
                    muteUpdates = false;
                }

                // A NamedBean is removed
                if ((e.getOldValue() != null)
                        && clazz.isAssignableFrom(e.getOldValue().getClass())) {
                    Manager<Meter> internalManager = initInternal();
                    muteUpdates = true;
                    internalManager.deregister((Meter) e.getOldValue());
                    muteUpdates = false;
                }
            }
#endif
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ProxyMeterManager::dispose() {
        AbstractProxyMeterManager::dispose();
//        for (Manager<? extends NamedBean> manager : registerBeanManagers) {
//            manager.removePropertyChangeListener("beans", this);
//        }
    }
