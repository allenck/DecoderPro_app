#include "proxylightmanager.h"
#include "lightmanager.h"
#include "internallightmanager.h"
#include "internalsystemconnectionmemo.h"
#include "meter.h"

ProxyLightManager::ProxyLightManager(QObject *parent) :
    AbstractProxyLightManager(parent)
{
 log = new Logger("ProxyLightManager");
 setObjectName("ProxyLightManager");
 //registerSelf();
}
/**
 * Implementation of a LightManager that can serves as a proxy
 * for multiple system-specific implementations.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @author	Dave Duchamp Copyright (C) 2004
 * @version	$Revision: 18102 $
 */
//public class ProxyLightManager extends AbstractProxyManager
//                            implements LightManager {


//    public ProxyLightManager() {
//    	super();
//    }

/*public*/ int ProxyLightManager::getXMLOrder()const{
    return Manager::LIGHTS;
}

/*protected*/ Manager* ProxyLightManager::makeInternalManager() const
{
 return ((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"))->getLightManager();
}

/**
 * Locate via user name, then system name if needed.
 *
 * @param name
 * @return Null if nothing by that name exists
 */
/*public*/ Light* ProxyLightManager::getLight(QString name) {
  return (Light*)AbstractProxyLightManager::getNamedBean(name);
}

/*protected*/ NamedBean* ProxyLightManager::makeBean(int i, QString systemName, QString userName)
{
 return ((AbstractLightManager*)getMgr(i))->newLight(systemName, userName);
}

//@Override
/** {@inheritDoc} */
/*public*/ Light* ProxyLightManager::provide(/*@Nonnull*/ QString name) throw (IllegalArgumentException) { return provideLight(name); }

/**
 * Locate via user name, then system name if needed.
 * If that fails, create a new Light: If the name
 * is a valid system name, it will be used for the new
 * Light.  Otherwise, the makeSystemName method
 * will attempt to turn it into a valid system name.
 *
 * @param name
 * @return Never null under normal circumstances
 */
/*public*/ Light* ProxyLightManager::provideLight(QString name) {
    return (Light*) AbstractProxyLightManager::provideNamedBean(name);
}

/**
 * Locate an instance based on a system name.  Returns null if no
 * instance already exists.
 * @return requested Light object or null if none exists
 */
/*public*/ Light *ProxyLightManager::getBySystemName(QString systemName) const {
    return (Light*)AbstractProxyLightManager::getBeanBySystemName(systemName);
}

/**
 * Locate an instance based on a user name.  Returns null if no
 * instance already exists.
 * @return requested Turnout object or null if none exists
 */
/*public*/ Light *ProxyLightManager::getByUserName(QString userName) const {
    return (Light*) AbstractProxyLightManager::getBeanByUserName(userName);
}

/**
 * Return an instance with the specified system and user names.
 * Note that two calls with the same arguments will get the same instance;
 * there is only one Light object representing a given physical light
 * and therefore only one with a specific system or user name.
 *<P>
 * This will always return a valid object reference for a valid request;
 * a new object will be
 * created if necessary. In that case:
 *<UL>
 *<LI>If a null reference is given for user name, no user name will be associated
 *    with the Light object created; a valid system name must be provided
 *<LI>If a null reference is given for the system name, a system name
 *    will _somehow_ be inferred from the user name.  How this is done
 *    is system specific.  Note: a future extension of this interface
 *    will add an exception to signal that this was not possible.
 *<LI>If both names are provided, the system name defines the
 *    hardware access of the desired turnout, and the user address
 *    is associated with it.
 *</UL>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects.  This is a problem, and we don't have a
 * good solution except to issue warnings.
 * This will mostly happen if you're creating Lights when you should
 * be looking them up.
 * @return requested Light object (never null)
 */
/*public*/ Light* ProxyLightManager::newLight(QString systemName, QString userName) {
    return (Light*) newNamedBean(systemName, userName);
}
///*public*/ NamedBean* ProxyLightManager::newNamedBean(QString systemName, QString userName) {
//    // if the systemName is specified, find that system
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return makeBean(i, systemName, userName);

//    // did not find a manager, allow it to default to the primary
//    log->debug("Did not find manager for system name "+systemName+", delegate to primary");
//    int iI = nMgrs()-1;
//    return makeBean(iI, systemName, userName);
//}

///**
// * Validate system name format
// * Locate a system specfic LightManager based on a system name.  Returns false if no
// *      manager exists.
// * If a manager is found, return its determination of validity of system name format
// */
///*public*/ Manager::NameValidity ProxyLightManager::validSystemNameFormat(QString systemName) {
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return ( (AbstractLightManager*)getMgr(i))->validSystemNameFormat(systemName);
//    return NameValidity::INVALID;
//}

/**
 * Validate system name against the hardware configuration
 * Locate a system specfic LightManager based on a system name.  Returns false if no
 *      manager exists.
 * If a manager is found, return its determination of validity of system name relative
 *      to the hardware configuration
 */
/*public*/ bool ProxyLightManager::validSystemNameConfig(QString systemName)const {
    int i = matchTentative(systemName);
    if (i >= 0)
    {
        return ( (LightManager*)getMgr(i))->validSystemNameConfig(systemName);
    }
    return false;
}

/**
 * Normalize a system name
 * Locate a system specfic LightManager based on a system name.  Returns "" if no
 * manager exists.
 * If a manager is found, return its determination of a normalized system name
 */
///*public*/ QString ProxyLightManager::normalizeSystemName(QString systemName) {
//    int i = matchTentative(systemName);
//    if (i >= 0)
//        return ( (AbstractLightManager*)getMgr(i))->normalizeSystemName(systemName);
//    return "";
//}

/**
 * Convert a system name to an alternate format
 * Locate a system specfic LightManager based on a system name.  Returns "" if no
 * manager exists.
 * If a manager is found, return its determination of an alternate system name
 */
/*public*/ QString ProxyLightManager::convertSystemNameToAlternate(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ( (AbstractLightManager*)getMgr(i))->convertSystemNameToAlternate(systemName);
    return "";
}

/**
 * Activate the control mechanism for each Light controlled by
 *    this LightManager.
 * Relay this call to all LightManagers.
 */
/*public*/ void ProxyLightManager::activateAllLights() {
    for (int i=0; i<nMgrs(); i++) {
        ((AbstractLightManager*)getMgr(i))->activateAllLights();
    }
}

/**
 * Responds 'true' if Light Manager is for a System that supports variable Lights.
 * Returns false if no manager exists.
 * If a manager is found, return its determination of support for variable lights.
 */
/*public*/ bool ProxyLightManager::supportsVariableLights(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ( (AbstractLightManager*)getMgr(i))->supportsVariableLights(systemName);
    return false;
}

/**
 * A method that determines if it is possible to add a range of lights in numerical
 * order eg 11 thru 18, primarily used to show/not show the add range box in the add Light window
 **/
/*public*/ bool ProxyLightManager::allowMultipleAdditions(QString systemName) {
    int i = matchTentative(systemName);
    if (i >= 0)
        return ( (AbstractLightManager*)getMgr(i))->allowMultipleAdditions(systemName);
    return false;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString ProxyLightManager::getEntryToolTip() {
    return "Enter a number from 1 to 9999"; // Basic number format help
}

//@Override
/*public*/ QString ProxyLightManager::getBeanTypeHandled(bool plural) const {
    return tr(plural ? "Lights" : "Light");
}
// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(ProxyLightManager.class.getName());
//}
