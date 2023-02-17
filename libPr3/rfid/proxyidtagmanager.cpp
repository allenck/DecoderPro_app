#include "proxyidtagmanager.h"
#include "idtagmanager.h"
#include "instancemanager.h"
#include "defaultidtagmanager.h"

/**
 * Implementation of a IdTagManager that can serve as a proxy for multiple
 * system-specific implementations.
 *
 * @author	Bob Jacobsen Copyright (C) 2010, 2018
 * @author	Dave Duchamp Copyright (C) 2004
 * @author	Paul Bender Copyright (C) 2019
 */
///*public*/ class ProxyIdTagManager extends AbstractProxyManager<IdTag>
//        implements IdTagManager {

    /*public*/ ProxyIdTagManager::ProxyIdTagManager(QObject* parent) : AbstractProvidingProxyManager(parent){
        //super();
     //propertyChangeSupport = new SwingPropertyChangeSupport(this,this);

    }

    //@Override
    /*public*/ int ProxyIdTagManager::getXMLOrder() const {
        return Manager::IDTAGS;
    }

    //@Override
    /*public*/ void ProxyIdTagManager::init() {
        if (!isInitialised()) {
            getDefaultManager();
        }
    }

    //@Override
    /*public*/ bool ProxyIdTagManager::isInitialised() {
//     return defaultManager!= nullptr &&
//                 getManagerList().stream().noneMatch(o->((IdTagManager)o).isInitialised());
     bool isInit = false;
     foreach(AbstractManager* o, getManagerList())
     {
      if(((IdTagManager*) o)->isInitialised())
       isInit= true;
     }
     return defaultManager!= nullptr && !isInit;
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@Nonnull
    /*public*/ AbstractManager/*<IdTag>*/* ProxyIdTagManager::getDefaultManager() const {
        if(defaultManager != getInternalManager()){
           defaultManager = getInternalManager();
        }
        return defaultManager;
    }
    //@Override
    /*protected*/ AbstractManager* ProxyIdTagManager::makeInternalManager() const  {
        // since this really is an internal tracking mechanisim,
        // build the new manager and add it here.
        DefaultIdTagManager* tagMan = new DefaultIdTagManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
        InstanceManager::setIdTagManager(tagMan);
        return tagMan;
    }

    /**
     * Locate via user name, then system name if needed.
     *
     * @return Null if nothing by that name exists
     */
    //@Override
    /*public*/ DefaultIdTag *ProxyIdTagManager::getIdTag(QString name) {
     init();
     return (DefaultIdTag *)AbstractProxyManager::getNamedBean(name)->self();
    }

    /** {@inheritDoc} */
    //@Override
    //@Nonnull
    /*public*/ /*SortedSet<IdTag>*/QSet<NamedBean*> ProxyIdTagManager::getNamedBeanSet(){
        init();
        return AbstractProxyManager::getNamedBeanSet();
    }

    //@Override
    /*protected*/ DefaultIdTag *ProxyIdTagManager::makeBean(AbstractManager *m, QString systemName, QString userName) {
     init();
     return ((DefaultIdTagManager*) m)->newIdTag(systemName, userName);
    }

    //@Override
    /**
     * {@inheritDoc}
     */
    /*public*/ DefaultIdTag *ProxyIdTagManager::provide(/*@Nonnull*/ QString name) /*throw (IllegalArgumentException)*/ {
        return provideIdTag(name);
    }

    /**
     * Locate via user name, then system name if needed. If that fails, create a
     * new IdTag: If the name is a valid system name, it will be used for the
     * new IdTag. Otherwise, the makeSystemName method will attempt to turn it
     * into a valid system name.
     *
     * @return Never null under normal circumstances
     */
    //@Override
    /*public*/ DefaultIdTag *ProxyIdTagManager::provideIdTag(QString name) throw (IllegalArgumentException) {
        return (DefaultIdTag*)provideNamedBean(name)->self();
    }

    /**
     * Locate an instance based on a system name. Returns null if no instance
     * already exists.
     *
     * @return requested IdTag object or null if none exists
     */
    //@Override
    /*public*/ DefaultIdTag *ProxyIdTagManager::getBySystemName(QString systemName)const {
        return (DefaultIdTag *)AbstractProxyManager::getBeanBySystemName(systemName)->self();
    }

    /**
     * Locate an instance based on a user name. Returns null if no instance
     * already exists.
     *
     * @return requested Turnout object or null if none exists
     */
    //@Override
    /*public*/ DefaultIdTag *ProxyIdTagManager::getByUserName(QString userName) const {
        return (DefaultIdTag*)AbstractProxyManager::getBeanByUserName(userName)->self();
    }

    /**
     * Return an instance with the specified system and user names. Note that
     * two calls with the same arguments will get the same instance; there is
     * only one IdTag object representing a given physical light and therefore
     * only one with a specific system or user name.
     * <p>
     * This will always return a valid object reference for a valid request; a
     * new object will be created if necessary. In that case:
     * <ul>
     * <li>If a null reference is given for user name, no user name will be
     * associated with the IdTag object created; a valid system name must be
     * provided
     * <li>If a null reference is given for the system name, a system name will
     * _somehow_ be inferred from the user name. How this is done is system
     * specific. Note: a future extension of this interface will add an
     * exception to signal that this was not possible.
     * <li>If both names are provided, the system name defines the hardware
     * access of the desired turnout, and the user address is associated with
     * it.
     * </ul>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects. This is a problem, and we don't have a good solution
     * except to issue warnings. This will mostly happen if you're creating
     * IdTags when you should be looking them up.
     *
     * @return requested IdTag object (never null)
     */
    //@Override
    /*public*/ DefaultIdTag *ProxyIdTagManager::newIdTag(QString systemName, QString userName) {
        return (DefaultIdTag*)newNamedBean(systemName, userName)->self();
    }

    //@Override
    /*public*/ DefaultIdTag* ProxyIdTagManager::getByTagID(QString tagID) {
        return (DefaultIdTag*)getBySystemName(AbstractProxyManager::makeSystemName(tagID));
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QString ProxyIdTagManager::getEntryToolTip() {
        return "Enter a number from 1 to 9999"; // Basic number format help
    }

    //@Override
    /*public*/ QString ProxyIdTagManager::getBeanTypeHandled(bool plural) const {
        //return Bundle.getMessage(plural ? "BeanNameIdTags" : "BeanNameIdTag");
     return "NameIdTag";
    }


    //@Override
    /*public*/ void ProxyIdTagManager::setStateStored(bool state) {
        stateSaved = state;
        for (Manager* mgr : getManagerList()) {
            ((IdTagManager*) mgr->mself())->setStateStored(state);
        }
    }

    //@Override
    /*public*/ bool ProxyIdTagManager::isStateStored() {
        stateSaved = true;
        for (Manager* mgr: getManagerList()) {
            if(!((DefaultIdTagManager*) mgr->mself())->isStateStored()) {
                stateSaved = false;
                break;
            }
        }
        return stateSaved;
    }


    //@Override
    /*public*/ void ProxyIdTagManager::setFastClockUsed(bool fastClock) {
        useFastClock = fastClock;
        for (Manager* mgr : getManagerList()) {
            ((IdTagManager*) mgr->mself())->setFastClockUsed(fastClock);
        }
    }

    //@Override
    /*public*/ bool ProxyIdTagManager::isFastClockUsed() {
        useFastClock = true;
        for (Manager* mgr: getManagerList()) {
            if (!((IdTagManager*) mgr->mself())->isFastClockUsed()) {
               useFastClock = false;
               break;
            }
        }
        return useFastClock;
    }

    //@Override
    /*public*/ QList<IdTag *> *ProxyIdTagManager::getTagsForReporter(Reporter* reporter, long threshold) {
        QList<IdTag*>* out = new QList<IdTag*>();
        return out;
    }
