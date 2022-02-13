#include "abstractproxymanager.h"
#include "exceptions.h"
#include <QSet>
#include "proxyreportermanager.h"
#include "proxyturnoutmanager.h"
#include "proxysensormanager.h"
#include "proxylightmanager.h"
#include "abstractturnoutmanager.h"
#include "abstractsensormanager.h"
#include "abstractlightmanager.h"
#include "abstractreportermanager.h"
#include "lnturnoutmanager.h"
#include "loggerfactory.h"
#include "namedbeancomparator.h"
#include "connectionconfigmanager.h"
#include "connectionconfig.h"
#include "loggingutil.h"
#include "vptr.h"
#include "namedbeancomparator.h"
#include "abstractturnoutmanager.h"
/**
 * Implementation of a Manager that can serves as a proxy for multiple
 * system-specific implementations.
 * <p>
 * Automatically includes an Internal system, which need not be separately added
 * any more.
 * <p>
 * Encapsulates access to the "Primary" manager, used by default, which is the
 * first one provided.
 * <p>
 * Internally, this is done by using an ordered list of all non-Internal
 * managers, plus a separate reference to the internal manager and default
 * manager.
 *
 * @param <E> the supported type of NamedBean
 * @author Bob Jacobsen Copyright (C) 2003, 2010, 2018
 */
//@SuppressWarnings("deprecation")
// abstract /*public*/  class AbstractProxyManager<E extends NamedBean> extends VetoableChangeSupport implements ProxyManager/*<E>*/*, PropertyChangeListener, Manager.ManagerDataListener<E> {

AbstractProxyManager::AbstractProxyManager(QObject* parent ) : VetoableChangeSupport(parent) {}

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QList<AbstractManager *> AbstractProxyManager::getManagerList()    {
        // make sure internal present
        initInternal();
        return QList<AbstractManager*>(mgrs.toList());
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QList<AbstractManager/*<E>*/*> AbstractProxyManager::getDisplayOrderManagerList()  {
        // make sure internal present
        initInternal();

        QList<AbstractManager/*<E>*/*> retval = QList<AbstractManager/*<E>*/*>();
        if (defaultManager != nullptr) {
            retval.append(defaultManager);
        }
//        mgrs.stream()
//                .filter(manager -> manager != defaultManager && manager != internalManager)
//                .forEachOrdered(retval::add);
        for(AbstractManager* manager : mgrs)
        {
         if(manager != defaultManager && manager != internalManager)
         {
           retval.append(manager);
         }
        }
        if (internalManager != nullptr && internalManager != defaultManager) {
            retval.append(internalManager);
        }
        return retval;
    }

    /*public*/  AbstractManager/*<E>*/* AbstractProxyManager::getInternalManager() const    {
        initInternal();
        return internalManager;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@Nonnull
    /*public*/  AbstractManager/*<E>*/* AbstractProxyManager::getDefaultManager() const
    {
        return defaultManager != nullptr ? defaultManager : getInternalManager();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@SuppressWarnings("deprecation")
    /*public*/  void AbstractProxyManager::addManager(/*@Nonnull*/ AbstractManager/*<E>*/* m) {
//        Objects.requireNonNull(m, "Can only add non-null manager");
        // check for already present
        for (AbstractManager/*<E>*/* check : mgrs) {
            if (m == check) { // can't use contains(..) because of Comparator ==  is on the prefix
                // already present, complain and skip
                log->warn(QString("Manager already present: %1").arg(m->toString())); // NOI18N
                return;
            }
        }
        mgrs.insert(m);

        if (defaultManager == nullptr) defaultManager = m;  // 1st one is default

        //Arrays.stream(getPropertyChangeListeners()).forEach(l -> m.addPropertyChangeListener(l));
        for(PropertyChangeListener* l : PropertyChangeSupport::getPropertyChangeListeners())
         //for(Manager* m : mgrs)
          m->PropertyChangeSupport::addPropertyChangeListener(l);
        //Arrays.stream(getVetoableChangeListeners()).forEach(l -> m.addVetoableChangeListener(l));
        for(VetoableChangeListener* l : VetoableChangeSupport::getVetoableChangeListeners())
         //for(AbstractManager* m : mgrs)
             m->VetoableChangeSupport::addVetoableChangeListener(l);
//        boundPropertyNames
//                .forEach(n -> Arrays.stream(getPropertyChangeListeners(n))
//                .forEach(l -> m.addPropertyChangeListener(n, l)));
        for(QString n : boundPropertyNames)
         for(PropertyChangeListener* l : PropertyChangeSupport::getPropertyChangeListeners(n))
          m->PropertyChangeSupport::addPropertyChangeListener(n, l);
//        vetoablePropertyNames
//                .forEach(n -> Arrays.stream(getVetoableChangeListeners(n))
//                .forEach(l -> m.addVetoableChangeListener(n, l)));
        for(QString n : vetoablePropertyNames)
         for(VetoableChangeListener* l : VetoableChangeSupport::getVetoableChangeListeners(n))
          m->VetoableChangeSupport::addVetoableChangeListener(n, l);
        m->PropertyChangeSupport::addPropertyChangeListener("beans", this);
        ((AbstractManager*)m)->addDataListener(this);
        recomputeNamedBeanSet();
        log->debug(QString("added manager %1").arg(QString(m->metaObject()->className())));
    }

    /*protected*/ AbstractManager *AbstractProxyManager::initInternal() const       {
        if (internalManager == nullptr) {
            log->debug(QString("create internal manager when first requested")); // NOI18N
            internalManager = makeInternalManager();
        }
        return internalManager;
    }

    /**
     * Create specific internal manager as needed for concrete type.
     *
     * @return an internal manager
     */
    //abstract /*protected*/ Manager/*<E>*/* makeInternalManager();

    /** {@inheritDoc} */
    //@Override
    /*public*/  /*E*/NamedBean* AbstractProxyManager::getNamedBean(/*@Nonnull*/ QString name)  {
        /*E*/NamedBean* t = getByUserName(name);
        if (t != nullptr) {
            return t;
        }
        return getBySystemName(name);
    }

    /** {@inheritDoc} */
    //@Override
    //@CheckReturnValue
    //@CheckForNull
    /*public*/  /*E*/NamedBean* AbstractProxyManager::getBySystemName(/*@Nonnull*/ QString systemName)  {
        AbstractManager/*<E>*/* m = getManager(systemName);
        if (m == nullptr) {
            log->debug(QString("getBySystemName did not find manager from name %1, defer to default manager").arg(systemName));
            m = getDefaultManager();
        }
        return m->getBySystemName(systemName);
    }

    /** {@inheritDoc} */
    //@Override
    //@CheckReturnValue
    //@CheckForNull
    /*public*/  /*E*/NamedBean* AbstractProxyManager::getByUserName(/*@Nonnull*/ QString userName) {
        for (Manager/*<E>*/* m : this->mgrs) {
            /*E*/NamedBean* b = m->getByUserName(userName);
            if (b != nullptr) {
                return b;
            }
        }
        return nullptr;
    }

    /**
     * {@inheritDoc}
     * <p>
     * This implementation locates a specific Manager based on the system name
     * and validates against that. If no matching Manager exists, the default
     * Manager attempts to validate the system name.
     */
    //@Override
    //@Nonnull
    /*public*/  QString AbstractProxyManager::validateSystemNameFormat(/*@Nonnull*/ QString systemName, /*@Nonnull*/ QLocale locale)   {
        Manager/*<E>*/* manager = getManager(systemName);
        if (manager == nullptr) {
            manager = getDefaultManager();
        }
        return manager->validateSystemNameFormat(systemName, locale);
    }

    /**
     * Validate system name format. Locate a system specific Manager based on a
     * system name.
     *
     * @return if a manager is found, return its determination of validity of
     *         system name format. Return INVALID if no manager exists.
     */
    //@Override
    /*public*/  Manager::NameValidity AbstractProxyManager::validSystemNameFormat(/*@Nonnull*/ QString systemName)  {
        Manager/*<E>*/* m = getManager(systemName);
        return m == nullptr ? Manager::NameValidity::INVALID : m->validSystemNameFormat(systemName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractProxyManager::dispose() {
     //mgrs.forEach(m -> m.dispose());
     for(Manager* m : mgrs)
      m->dispose();
        mgrs.clear();
      if (internalManager != nullptr) {
          internalManager->dispose(); // don't make if not made yet
      }
    }

    /**
     * Get the manager for the given system name.
     *
     * @param systemName the given name
     * @return the requested manager or null if there is no matching manager
     */
    //@CheckForNull
    /*protected*/ AbstractManager/*<E>*/* AbstractProxyManager::getManager(/*@Nonnull*/ QString systemName)   {
        // make sure internal present
        initInternal();
        for (AbstractManager/*<E>*/* m : getManagerList()) {
            if (systemName.startsWith(m->getSystemNamePrefix())) {
                return m;
            }
        }
        return nullptr;
    }

    /**
     * Get the manager for the given system name or the default manager if there
     * is no matching manager.
     *
     * @param systemName the given name
     * @return the requested manager or the default manager if there is no
     *         matching manager
     */
    //@Nonnull
    /*protected*/ AbstractManager *AbstractProxyManager::getManagerOrDefault(/*@Nonnull*/ QString systemName) {
        AbstractManager/*<E>*/* manager = getManager(systemName);
        if (manager == nullptr) {
            manager = getDefaultManager();
        }
        return manager;
    }

    /**
     * Shared method to create a systemName based on the address base, the prefix and manager class.
     *
     * @param curAddress base address to use
     * @param prefix system prefix to use
     * @param beanType Bean Type for manager (method is used for Turnout and Sensor Managers)
     * @return a valid system name for this connection
     * @throws JmriException if systemName cannot be created
     */
    QString AbstractProxyManager::createSystemName(QString curAddress, QString prefix, QString beanType) /*throws JmriException */{
        for (Manager/*<E>*/* m : mgrs) {
            if (prefix == (m->getSystemPrefix()) && beanType == (m->getNamedBeanClass())) {
                try {
                    if (beanType == "Turnout") {
                        return ((TurnoutManager*) m)->createSystemName(curAddress, prefix);
                    } else if (beanType == "Sensor") {
                        return ((SensorManager*) m)->createSystemName(curAddress, prefix);
                    }
                    else if (beanType == "Light") {
                        return ((LightManager*) m)->createSystemName(curAddress, prefix);
                    }
                    else if (beanType == "Reporter") {
                        return ((ReporterManager*) m)->createSystemName(curAddress, prefix);
                    }
                    else {
                        log->warn("createSystemName requested for incompatible Manager");
                    }
                } catch (JmriException* ex) {
                    throw ex;
                }
            }
        }
        throw new JmriException("Manager could not be found for System Prefix " + prefix);
    }

    //@Nonnull
    /*public*/  QString AbstractProxyManager::createSystemName(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix) /*throws jmri.JmriException*/ {
        return createSystemName(curAddress, prefix, getNamedBeanClass());
    }

    //@SuppressWarnings("deprecation") // user warned by actual manager class
    /*public*/  QString AbstractProxyManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*//@Nonnull*/ QString prefix, QChar typeLetter) /*throws jmri.JmriException*/ {
        for (AbstractManager/*<E>*/* m : mgrs) {
            log->debug(QString("NextValidAddress requested for %1").arg(curAddress));
            if (prefix == (m->getSystemPrefix()) && typeLetter == m->typeLetter()) {
                try {
                    switch (typeLetter.toLatin1()) { // use #getDefaultManager() instead?
                        case 'T':
                            return ((AbstractTurnoutManager*) m)->getNextValidAddress(curAddress, prefix);
                        case 'S':
                            return ((SensorManager*) m)->getNextValidAddress(curAddress, prefix);
                        case 'R':
                            return ((ReporterManager*) m)->getNextValidAddress(curAddress, prefix);
                        default:
                            return nullptr;
                    }
                } catch (JmriException* ex) {
                    throw ex;
                }
            }
        }
        return nullptr;
    }

    /*public*/  QString AbstractProxyManager::getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting, QChar typeLetter) /*throws jmri.JmriException*/ {
        for (AbstractManager/*<E>*/* m : mgrs) {
            log->debug(QString("NextValidAddress requested for %1").arg(curAddress));
            if (prefix == (m->getSystemPrefix()) && typeLetter == m->typeLetter()) {
                try {
                    switch (typeLetter.toLatin1()) { // use #getDefaultManager() instead?
                        case 'T':
                            return m->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                        case 'S':
                            return m->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                        case 'L':
                            return m->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                        case 'R':
                            return m->getNextValidAddress(curAddress, prefix, ignoreInitialExisting);
                        default:
                            return nullptr;
                    }
                } catch (JmriException* ex) {
                    throw ex;
                }
            }
        }
        return nullptr;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractProxyManager::deleteBean(/*@Nonnull*/ /*E*/NamedBean* s, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/ {
        Manager/*<E>*/* m = getManager(s->getSystemName());
        if (m != nullptr) {
            m->deleteBean(s, property);
        }
    }

    /**
     * Try to create a system manager. If this proxy manager is able to create
     * a system manager, the concrete class must implement this method.
     *
     * @param memo the system connection memo for this connection
     * @return the new manager or null if it's not possible to create the manager
     */
    /*protected*/ AbstractManager *AbstractProxyManager::createSystemManager(/*@Nonnull*/ SystemConnectionMemo* /*memo*/) {
        return nullptr;
    }

    /**
     * Get the Default Manager ToolTip.
     * {@inheritDoc}
     */
    //@Override
    /*public*/  QString AbstractProxyManager::getEntryToolTip() {
        return getDefaultManager()->getEntryToolTip();
    }

    /**
     * Try to create a system manager.
     *
     * @param systemPrefix the system prefix
     * @return the new manager or null if it's not possible to create the manager
     */
    /*private*/ Manager/*<E>*/* AbstractProxyManager::createSystemManager(/*@Nonnull*/ QString systemPrefix) {
        Manager/*<E>*/* m = nullptr;

        ConnectionConfigManager* manager = (ConnectionConfigManager*)InstanceManager::getNullableDefault("ConnectionConfigManager");
        if (manager == nullptr) return nullptr;

        QVector<ConnectionConfig*> connections = manager->getConnections();

        for (ConnectionConfig* connection : connections) {
            if (systemPrefix == (connection->getAdapter()->getSystemPrefix())) {
                m = createSystemManager(connection->getAdapter()->getSystemConnectionMemo());
            }
            if (m != nullptr) break;
        }
//        if (m == null) throw new RuntimeException("Manager not created");
        return m;
    }

    /**
     * {@inheritDoc}
     * <p>
     * Forwards the register request to the matching system.
     */
    //@Override
    /*public*/  void AbstractProxyManager::Register(/*@Nonnull*/ /*E*/NamedBean* s)  {
        AbstractManager/*<E>*/* m = getManager(s->getSystemName());
        if (m == nullptr) {
            QString systemPrefix = Manager::getSystemPrefix(s->getSystemName());
            m = (AbstractManager*)createSystemManager(systemPrefix)->self();
        }
        if (m != nullptr) {
            m->Register(s);
        } else {
            log->error(QString("Unable to register %1 in this proxy manager. No system specific manager supports this bean.").arg(s->getSystemName()));
        }
    }

    /**
     * {@inheritDoc}
     * <p>
     * Forwards the deregister request to the matching system.
     *
     * @param s the name
     */
    //@Override
    /*public*/  void AbstractProxyManager::deregister(/*@Nonnull*/ /*E*/NamedBean* s) {
     if(s==nullptr) throw NullPointerException("null NamedBean");
        Manager/*<E>*/* m = getManager(s->getSystemName());
        if (m != nullptr) {
            m->deregister(s);
        }
    }

    /**
     * {@inheritDoc}
     * List does not contain duplicates.
     */
    //@Nonnull
    //@Override
    /*public*/  QList<NamedBeanPropertyDescriptor/*<?>*/*> AbstractProxyManager::getKnownBeanProperties() {
        // Create List as set to prevent duplicates from multiple managers
        // of the same hardware type.
        QSet<NamedBeanPropertyDescriptor/*<?>*/*> set = QSet<NamedBeanPropertyDescriptor*>();
        //mgrs.forEach(m -> set.addAll(m->getKnownBeanProperties()));
        for(Manager* m : mgrs)
         for(NamedBeanPropertyDescriptor* d : m->getKnownBeanProperties())
          set.insert(d);
        return QList<NamedBeanPropertyDescriptor/*<?>*/*>(set.toList());
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  /*synchronized*/ void AbstractProxyManager::addPropertyChangeListener(PropertyChangeListener* l) {
        PropertyChangeSupport::addPropertyChangeListener(l);
        //mgrs.forEach(m -> m->addPropertyChangeListener(l));
        for(Manager* m : mgrs)
         m->addPropertyChangeListener(l);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  /*synchronized*/ void AbstractProxyManager::removePropertyChangeListener(PropertyChangeListener* l) {
        PropertyChangeSupport::removePropertyChangeListener(l);
        //mgrs.forEach(m -> m->removePropertyChangeListener(l));
        foreach(Manager* m, mgrs)
         m->removePropertyChangeListener(l);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractProxyManager::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        PropertyChangeSupport::addPropertyChangeListener(propertyName, listener);
        boundPropertyNames.append(propertyName);
        //mgrs.forEach(m -> m->addPropertyChangeListener(propertyName, listener));
        for(Manager* m : mgrs)
         m->addPropertyChangeListener(propertyName, listener);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractProxyManager::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
        PropertyChangeSupport::removePropertyChangeListener(propertyName, listener);
        //mgrs.forEach(m -> m->removePropertyChangeListener(propertyName, listener));
        for(Manager* m : mgrs)
         m->removePropertyChangeListener(propertyName, listener);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  /*synchronized*/ void AbstractProxyManager::addVetoableChangeListener(VetoableChangeListener* l) {
        VetoableChangeSupport::addVetoableChangeListener(l);
//        mgrs.forEach(m -> m->addVetoableChangeListener(l));
        for(Manager* m : mgrs)
         m->addVetoableChangeListener(l);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  /*synchronized*/ void AbstractProxyManager::removeVetoableChangeListener(VetoableChangeListener* l) {
        VetoableChangeSupport::removeVetoableChangeListener(l);
        //mgrs.forEach(m -> m->removeVetoableChangeListener(l));
        for(Manager* m : mgrs)
         m->removeVetoableChangeListener( l);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractProxyManager::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
        VetoableChangeSupport::addVetoableChangeListener(propertyName, listener);
        vetoablePropertyNames.append(propertyName);
        //mgrs.forEach(m -> m->addVetoableChangeListener(propertyName, listener));
        for(Manager* m : mgrs)
         m->addVetoableChangeListener(propertyName, listener);
    }

    /** {@inheritDoc} */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractProxyManager::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
        VetoableChangeSupport::removeVetoableChangeListener(propertyName, listener);
        //mgrs.forEach(m -> m->removeVetoableChangeListener(propertyName, listener));
        for(Manager* m : mgrs)
         m->removeVetoableChangeListener(propertyName, listener);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/  void AbstractProxyManager::propertyChange(PropertyChangeEvent* event) {
        if (event->getPropertyName() == ("beans")) {
            recomputeNamedBeanSet();
        }
        event->setPropagationId(VPtr<AbstractProxyManager>::asQVariant(this));
        if (!silencedProperties.value(event->getPropertyName(), false)) {
            firePropertyChange(event);
        }
    }

    /**
     * {@inheritDoc}
     *
     * @return The system connection memo for the manager returned by
     *         {@link #getDefaultManager()}, or the Internal system connection
     *         memo if there is no default manager
     */
    //@Override
    //@Nonnull
    /*public*/  SystemConnectionMemo* AbstractProxyManager::getMemo()    {
        try {
            return getDefaultManager()->getMemo();
        } catch (IndexOutOfBoundsException ex) {
            return (InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo");
        }
    }

    /**
     * @return The system-specific prefix letter for the primary implementation
     */
    //@Override
    //@Nonnull
    /*public*/  QString AbstractProxyManager::getSystemPrefix() const   {
        try {
            return getDefaultManager()->getSystemPrefix();
        } catch (IndexOutOfBoundsException* ie) {
            return "?";
        }
    }

    /**
     * @return The type letter for for the primary implementation
     */
    //@Override
    /*public*/  QChar AbstractProxyManager::typeLetter() const  {
        return getDefaultManager()->typeLetter();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@Nonnull
    /*public*/  QString AbstractProxyManager::makeSystemName(/*@Nonnull*/ QString s) {
        return getDefaultManager()->makeSystemName(s);
    }

    /** {@inheritDoc} */
    //@CheckReturnValue
    //@Override
    /*public*/  int AbstractProxyManager::getObjectCount() {
        //return mgrs.stream().map(m -> m->getObjectCount()).reduce(0, Integer::sum);
     int count;
     for(Manager* m : mgrs)
      count += m->getObjectCount();
     return count;
    }

    /** {@inheritDoc} */
    //@Nonnull
    //@Override
    //@Deprecated  // will be removed when superclass method is removed due to //@Override
    /*public*/  QStringList AbstractProxyManager::getSystemNameList() {
        LoggingUtil::deprecationWarning(log, "getSystemNameList");
        QList<NamedBean*>* list = getNamedBeanList();
        QVector<QString> retval = QVector<QString>(list->size());
        //list.forEach(e -> retval.add(e.getSystemName()));
        for(NamedBean* e : *list)
         retval.append(e->getSystemName());
        //return Collections.unmodifiableList(retval);
        return QStringList(retval.toList());
    }

    /** {@inheritDoc} */
    //@Override
    //@Deprecated  // will be removed when superclass method is removed due to //@Override
    //@Nonnull
    /*public*/  QList<NamedBean*>* AbstractProxyManager::getNamedBeanList() {
        LoggingUtil::deprecationWarning(log, "getNamedBeanList"); // used by getSystemNameList
        // by doing this in order by manager and from each managers ordered sets, its /*final*/ly in order
        QList<NamedBean*> tl = QList<NamedBean*>();
        //mgrs.forEach(m -> tl.addAll(m->getNamedBeanSet()));
        for(Manager* m : mgrs)
         for(NamedBean* b : m->getNamedBeanSet())
          tl.append(b);
        //return Collections.unmodifiableList(tl);
        return new QList<NamedBean*>(tl);
    }

    /*protected*/ void AbstractProxyManager::recomputeNamedBeanSet() const {
        if (namedBeanSet != nullptr) { // only maintain if requested
            namedBeanSet->clear();
            //mgrs.forEach(m -> namedBeanSet.addAll(m->getNamedBeanSet()));
            foreach(Manager* m, mgrs)
             foreach(NamedBean* b, m->getNamedBeanSet())
              namedBeanSet->insert(b);


        }
    }

    NamedBeanComparator<NamedBean*> comparator4 = NamedBeanComparator<NamedBean*>();
    bool sortLessThanconst4( NamedBean* s1,  NamedBean* s2)
    {
     return comparator4.compare(s1, s2) < 0;
    }

    /** {@inheritDoc} */
    //@Override
    //@Nonnull
    /*public*/  QSet<NamedBean*> AbstractProxyManager::getNamedBeanSet() {
        if (namedBeanSet == nullptr) {
            namedBeanSet = new QSet<NamedBean*>();//TreeSet<>(new NamedBeanComparator<>());
//            std::sort(namedBeanSet->begin(), namedBeanSet->end(), sortLessThanconst4);
            recomputeNamedBeanSet();
        }
        //return Collections.unmodifiableSortedSet(namedBeanSet);
        return QSet<NamedBean*>(*namedBeanSet);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@OverridingMethodsMustInvokeSuper
    /*public*/  void AbstractProxyManager::setPropertyChangesSilenced(QString propertyName, bool silenced) {
        // since AbstractProxyManager has no explicit constructors, acccept
        // "beans" as well as anything needed to be accepted by subclasses
        if (!"beans" == (propertyName) && !silenceableProperties.contains(propertyName)) {
            throw new IllegalArgumentException("Property " + propertyName + " cannot be silenced.");
        }
        silencedProperties.insert(propertyName, silenced);
        if (propertyName == ("beans") && !silenced) {
            fireIndexedPropertyChange("beans", getNamedBeanSet().size(), 0, 0);
        }
    }

    /** {@inheritDoc} */
    //@Override
    //@Deprecated
    /*public*/  void AbstractProxyManager::addDataListener(Manager::ManagerDataListener/*<E>*/* e) {
        if (e != nullptr) listeners.append(e);
    }

    /** {@inheritDoc} */
    //@Override
    //@Deprecated
    /*public*/  void AbstractProxyManager::removeDataListener(Manager::ManagerDataListener/*<E>*/* e) {
        if (e != nullptr) listeners.removeOne(e);
    }


    /**
     * {@inheritDoc}
     * From Manager.ManagerDataListener, receives notifications from underlying
     * managers.
     */
    //@Override
    //@Deprecated
    /*public*/  void AbstractProxyManager::contentsChanged(Manager::ManagerDataEvent* /*e*/) {
    }

    /**
     * {@inheritDoc}
     * From Manager.ManagerDataListener, receives notifications from underlying
     * managers.
     */
    //@Override
    //@Deprecated
    //@SuppressWarnings("deprecation")
    /*public*/  void AbstractProxyManager::intervalAdded(AbstractProxyManager::ManagerDataEvent/*<E>*/* e) {
        if (namedBeanSet != nullptr && e->getIndex0() == e->getIndex1()) {
            // just one element added, and we have the object reference
            namedBeanSet->insert(e->getChangedBean());
        } else {
            recomputeNamedBeanSet();
        }

        if (muted) return;

        int offset = 0;
        for (Manager/*<E>*/* m : mgrs) {
            if (m == e->getSource()) break;
            offset += m->getObjectCount();
        }

        ManagerDataEvent/*<E>*/* eOut = new ManagerDataEvent(this, Manager::ManagerDataEvent::INTERVAL_ADDED, e->getIndex0()+offset, e->getIndex1()+offset, e->getChangedBean());

        //listeners.forEach(m -> m->intervalAdded(eOut));
        for (Manager::ManagerDataListener/*<E>*/* m : listeners)
         m->intervalAdded(eOut);
    }

    /**
     * {@inheritDoc}
     * From Manager.ManagerDataListener, receives notifications from underlying
     * managers.
     */
    //@Override
    //@Deprecated
    //@SuppressWarnings("deprecation")
    /*public*/  void AbstractProxyManager::intervalRemoved(AbstractProxyManager::ManagerDataEvent/*<E>*/* e) {
        recomputeNamedBeanSet();

        if (muted) return;

        int offset = 0;
        for (Manager/*<E>*/* m : mgrs) {
            if (m == e->getSource()) break;
            offset += m->getObjectCount();
        }

        ManagerDataEvent/*<E>*/* eOut = new ManagerDataEvent(this, Manager::ManagerDataEvent::INTERVAL_REMOVED, e->getIndex0()+offset, e->getIndex1()+offset, e->getChangedBean());

        //listeners.forEach(m -> m->intervalRemoved(eOut));
        for (Manager::ManagerDataListener/*<E>*/* m : listeners)
         m->intervalRemoved(eOut);
    }

    /** {@inheritDoc} */
    //@Override
    //@Deprecated
    //@SuppressWarnings("deprecation")
    /*public*/  void AbstractProxyManager::setDataListenerMute(bool m) {
        if (muted && !m) {
            // send a total update, as we haven't kept track of specifics
            ManagerDataEvent/*<E>*/* e = new ManagerDataEvent(this, ManagerDataEvent::CONTENTS_CHANGED, 0, getObjectCount()-1, nullptr);
            //listeners.forEach((listener) -> listener.contentsChanged(e));
            for (Manager::ManagerDataListener/*<E>*/* m : listeners)
             m->contentsChanged(e);
        }
        this->muted = m;
    }



// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractProxyManager::log = LoggerFactory::getLogger("AbstractProxyManager");
