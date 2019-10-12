#include "proxyreportermanager.h"
#include "reportermanager.h"
#include "internalreportermanager.h"
#include "instancemanager.h"
#include "internalsystemconnectionmemo.h"

ProxyReporterManager::ProxyReporterManager(QObject *parent) :
    AbstractProxyReporterManager(parent)
{
 setObjectName("ProxyReporterManager");
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}

/**
 * Implementation of a ReporterManager that can serves as a proxy
 * for multiple system-specific implementations.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2010
 * @version	$Revision: 21455 $
 */
//public class ProxyReporterManager extends AbstractProxyManager implements ReporterManager {


//    public ProxyReporterManager() {
//    	super();
//    }
    /*protected*/ Manager* ProxyReporterManager::makeInternalManager() const
{
        return ((InternalSystemConnectionMemo*) InstanceManager::getDefault("InternalSystemConnectionMemo"))->getReporterManager();
    }
    /*public*/ int ProxyReporterManager::getXMLOrder(){
        return Manager::REPORTERS;
    }

/**
 * Locate via user name, then system name if needed.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ Reporter* ProxyReporterManager::getReporter(QString name)
{
 //return dynamic_cast<Reporter*>(/*super.*/AbstractProxyManager::getNamedBean(name));
 return (Reporter*)AbstractProxyReporterManager::getNamedBean(name);
}

/*protected*/ NamedBean* ProxyReporterManager::makeBean(int i, QString systemName, QString userName)
{
 AbstractReporterManager* mgr = (AbstractReporterManager*)getMgr(i);
 return mgr->newReporter(systemName, userName);
}

/*public*/ Reporter* ProxyReporterManager::provideReporter(QString sName)
{
//return dynamic_cast<Reporter*>( /*super.*/AbstractProxyManager::provideNamedBean(sName));
    return (Reporter*)AbstractProxyReporterManager::provideNamedBean(sName);
}

//@Override
/** {@inheritDoc} */
/*public*/ Reporter* ProxyReporterManager::provide(/*@Nonnull*/ QString name) throw (IllegalArgumentException) { return provideReporter(name); }

/**
 * Locate an instance based on a system name.  Returns NULL if no
 * instance already exists.
 * @return requested Reporter object or NULL if none exists
 */
/*public*/ Reporter* ProxyReporterManager::getBySystemName(QString sName) {
    //return dynamic_cast<Reporter*>( /*super.*/AbstractProxyManager::getBeanBySystemName(sName));
return (Reporter*)AbstractProxyReporterManager::getBeanBySystemName(sName);
}

/**
 * Locate an instance based on a user name.  Returns NULL if no
 * instance already exists.
 * @return requested Reporter object or NULL if none exists
 */
/*public*/ Reporter* ProxyReporterManager::getByUserName(QString userName) {
    return dynamic_cast<Reporter*>( /*super.*/AbstractProxyReporterManager::getBeanByUserName(userName));
}

/*public*/ Reporter* ProxyReporterManager::getByDisplayName(QString key) {
// First try to find it in the user list.
// If that fails, look it up in the system list
Reporter* retv = this->getByUserName(key);
if (retv == NULL) {
    retv = this->getBySystemName(key);
}
// If it's not in the system list, go ahead and return NULL
return(retv);
}

/**
 * Return an instance with the specified system and user names.
 * Note that two calls with the same arguments will get the same instance;
 * there is only one Reporter object representing a given physical Reporter
 * and therefore only one with a specific system or user name.
 *<P>
 * This will always return a valid object reference for a valid request;
 * a new object will be
 * created if necessary. In that case:
 *<UL>
 *<LI>If a NULL reference is given for user name, no user name will be associated
 *    with the Reporter object created; a valid system name must be provided
 *<LI>If a NULL reference is given for the system name, a system name
 *    will _somehow_ be inferred from the user name.  How this is done
 *    is system specific.  Note: a future extension of this interface
 *    will add an exception to signal that this was not possible.
 *<LI>If both names are provided, the system name defines the
 *    hardware access of the desired Reporter, and the user address
 *    is associated with it.
 *</UL>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects.  This is a problem, and we don't have a
 * good solution except to issue warnings.
 * This will mostly happen if you're creating Reporters when you should
 * be looking them up.
 * @return requested Reporter object (never NULL)
 */
/*public*/ Reporter* ProxyReporterManager::newReporter(QString systemName, QString userName)
{
 NamedBean* bean = newNamedBean(systemName, userName);
    //return dynamic_cast<Reporter*>( bean);
 return (Reporter*) bean;
}

/*public*/ bool ProxyReporterManager::allowMultipleAdditions(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ((ReporterManager*)getMgr(i))->allowMultipleAdditions(systemName);
    return ((ReporterManager*)getMgr(0))->allowMultipleAdditions(systemName);
}

/*public*/ QString ProxyReporterManager::getNextValidAddress(QString curAddress, QString prefix)
{
    for (int i=0; i<nMgrs(); i++)
    {
        if ( prefix == ( ((ProxyReporterManager*)getMgr(i))->getSystemPrefix()) )
        {
            //System.out.println((TurnoutManager)getMgr(i))
            return ((ReporterManager*)getMgr(i))->getNextValidAddress(curAddress, prefix);
        }
    }
    return NULL;
}

    // initialize logging
    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ProxyReporterManager.class.getName());
/*public*/ NamedBean* ProxyReporterManager::newNamedBean(QString systemName, QString userName) {
    // if the systemName is specified, find that system
    int i = matchTentative(systemName);
    if (i >= 0)
        return makeBean(i, systemName, userName);

    // did not find a manager, allow it to default to the primary
    log.debug("Did not find manager for system name "+systemName+", delegate to primary");
    return makeBean(1, systemName, userName);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString ProxyReporterManager::getEntryToolTip() {
    return "Enter a number from 1 to 9999"; // Basic number format help
}

//@Override
/*public*/ QString ProxyReporterManager::getBeanTypeHandled(bool plural) {
    return tr(plural ? "Reporters" : "Reporter");
}
