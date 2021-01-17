#include "abstractlightmanager.h"
#include "systemconnectionmemo.h"
#include "manager.h"

AbstractLightManager::AbstractLightManager(SystemConnectionMemo* memo, QObject *parent) :
    LightManager(memo, parent)
{
 log= new Logger("AbstractLightManager");
}
/**
 * Abstract partial implementation of a LightManager.
 * <P>
 * Based on AbstractSignalHeadManager.java and AbstractSensorManager.java
 *
 * @author      Dave Duchamp Copyright (C) 2004
 * @version	$Revision: 18102 $
 */
//public abstract class AbstractLightManager extends AbstractManager
//    implements LightManager, java.beans.PropertyChangeListener, java.io.Serializable {

//    public AbstractLightManager() {
//        super();
//    }

/*public*/ int AbstractLightManager::getXMLOrder() const
{
    return Manager::LIGHTS;
}

/**
 * Returns the second letter in the system name for a Light
 */
/*public*/ char AbstractLightManager::typeLetter() const { return 'L'; }

/**
 * Locate via user name, then system name if needed.
 * If that fails, create a new Light: If the name
 * is a valid system name, it will be used for the new
 * Light.  Otherwise, the makeSystemName method
 * will attempt to turn it into a valid system name.
 *
 * @param name
 * @return Never NULL unless valid systemName cannot
 *     be found
 */
/*public*/ Light* AbstractLightManager::provideLight(QString name)
{
    Light* light = getLight(name);
    // makeSystemName checks for validity
    return light == nullptr ? newLight(makeSystemName(name, true, QLocale()), "") : light;
}

/**
 * Locate via user name, then system name if needed.
 * Does not create a new one if nothing found
 *
 * @param name
 * @return NULL if no match found
 */
/*public*/ Light* AbstractLightManager::getLight(QString name) {
    Light* t = (Light*)getByUserName(name);
    if (t!=NULL) return t;

    return (Light*)getBySystemName(name);
}
#if 1
/**
 * Locate a Light by its system name
 */
/*public*/ Light* AbstractLightManager::getBySystemName(QString name) const
{
 return (Light*)(_tsys->value(name));
}

/**
 * Locate a Light by its user name
 */
/*public*/ Light* AbstractLightManager::getByUserName(QString key) const {
    return dynamic_cast<Light*>(_tuser->value(key));
}
#endif
/**
 * Return an instance with the specified system and user names.
 * Note that two calls with the same arguments will get the same instance;
 * there is only one Light object representing a given physical Light
 * and therefore only one with a specific system or user name.
 *<P>
 * This will always return a valid object reference; a new object will be
 * created if necessary. In that case:
 *<UL>
 *<LI>If a NULL reference is given for user name, no user name will be associated
 *    with the Light object created; a valid system name must be provided
 *<LI>If both names are provided, the system name defines the
 *    hardware access of the desired sensor, and the user address
 *    is associated with it. The system name must be valid.
 *</UL>
 * Note that it is possible to make an inconsistent request if both
 * addresses are provided, but the given values are associated with
 * different objects.  This is a problem, and we don't have a
 * good solution except to issue warnings.
 * This will mostly happen if you're creating Lights when you should
 * be looking them up.
 * @return requested Light object (never NULL)
 */
/*public*/ Light* AbstractLightManager::newLight(QString systemName, QString userName)
{
 if (log->isDebugEnabled()) log->debug("newLight:"
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
 if (systemName == NULL)
 {
  log->error("SystemName cannot be NULL. UserName was "
                                    +( (userName==NULL) ? "NULL" : userName));
  return NULL;
 }
 // is system name in correct format?
 if ( validSystemNameFormat(systemName) != NameValidity::VALID)
 {
  log->error("Invalid system name for newLight: "+systemName);
  return NULL;
 }
 // return existing if there is one
 Light* s = NULL;
 if ( (userName!=NULL) && ((s = (Light*)getByUserName(userName)) != NULL))
 {
  if (getBySystemName(systemName)!=s)
   log->error("inconsistent user ("+userName+") and system name ("
                    +systemName+") results; userName related to ("+s->getSystemName()+")");
  return s;
 }
 if ( (s = (Light*)getBySystemName(systemName)) != NULL)
 {
  if ((s->getUserName() == NULL) && (userName != NULL))
   s->setUserName(userName);
  else if (userName != NULL) log->warn("Found light via system name ("+systemName
                                +") with non-NULL user name ("+userName+")");
   return s;
 }

 // doesn't exist, make a new one
 s = createNewLight(systemName, userName);

 // if that failed, blame it on the input arguements
 if (s == NULL)
 {
  log->error("cannot create new light "+systemName);
  throw new IllegalArgumentException("cannot create new light "+systemName);
 }
 // save in the maps
 Register(s);
 emit newLightCreated(this, s);
 return s;
}

/**
 * Internal method to invoke the factory, after all the
 * logic for returning an existing method has been invoked.
 * @return new NULL
 */
///*abstract protected*/ Light* createNewLight(QString systemName, QString userName);

/**
 * Activate the control mechanism for each Light controlled by
 *    this LightManager.  Note that some Lights don't require
 *    any activation.  The activateLight method in AbstractLight.java
 *    determines what needs to be done for each Light.
 */
/*public*/ void AbstractLightManager::activateAllLights() {
    // Set up an iterator over all Lights contained in this manager
//    java.util.Iterator<String> iter =
//                                getSystemNameList().iterator();
//    while (iter.hasNext()) {
//        String systemName = iter.next();
        foreach(QString systemName, getSystemNameList())
        {
        if (systemName.isEmpty()) {
            log->error("System name NULL during activation of Lights");
        }
        else {
            log->debug("Activated Light system name is "+systemName);
            ((Light*)getBySystemName(systemName))->activateLight();
        }
    }
}

/**
 * Normalize the system name
 * <P>
 * This routine is used to ensure that each system name is uniquely linked to
 *      one C/MRI bit, by removing extra zeros inserted by the user.
 * <P>
 * If a system implementation has names that could be normalized, the
 *      system-specific Light Manager should override this routine and supply
 *      a normalized system name.
 */
/*public*/ QString AbstractLightManager::normalizeSystemName(QString systemName) {
    return systemName;
}

/**
 * Convert the system name to a normalized alternate name
 * <P>
 * This routine is to allow testing to ensure that two Lights with
 *      alternate names that refer to the same output bit are not
 *      created.
 * <P>
 * If a system implementation has alternate names, the system specific
 *      Light Manager should override this routine and supply the alternate
 *      name.
 */
/*public*/ QString AbstractLightManager::convertSystemNameToAlternate(QString /*systemName*/) {
    return "";
}

/**
 * Returns 'true' if the System can potentially support variable Lights
 *    Note: LightManagers for Systems that can support variable Lights should
 *         override this method and return 'true'.
 */
/*public*/ bool AbstractLightManager::supportsVariableLights(QString /*systemName*/) {
    return false;
}

/**
* A method that determines if it is possible to add a range of lights in numerical
* order eg 11 thru 18, primarily used to show/not show the add range box in the add Light window
**/
/*public*/ bool AbstractLightManager::allowMultipleAdditions(QString /*systemName*/) { return false;  }

/**
 * Get bean type handled.
 *
 * @return a string for the type of object handled by this manager
 */
//@Override
/*public*/ QString AbstractLightManager::getBeanTypeHandled(bool plural) const {
    return (plural ? tr("Lights") : ("Light"));
}

/**
 * {@inheritDoc}
 */
//@Override
//@CheckForNull
/*public*/ QString AbstractLightManager::getEntryToolTip() {
    return "Enter a number from 1 to 9999"; // Basic number format help
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractLightManager.class.getName());
