#include "abstractlightmanager.h"
#include "systemconnectionmemo.h"
#include "manager.h"

AbstractLightManager::AbstractLightManager(SystemConnectionMemo* memo, QObject *parent) :
    AbstractManager(memo, parent)
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
/*public*/ QChar AbstractLightManager::typeLetter() const { return 'L'; }

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
    return light == nullptr ? newLight(AbstractManager::makeSystemName(name, true, QLocale()), "") : light;
}

/**
 * Locate via user name, then system name if needed.
 * Does not create a new one if nothing found
 *
 * @param name
 * @return NULL if no match found
 */
/*public*/ Light* AbstractLightManager::getLight(QString name) {
    Light* t = (Light*)getByUserName(name)->self();
    if (t!=NULL) return t;

    return (Light*)getBySystemName(name)->self();
}

/**
 * Locate a Light by its system name
 */
/*public*/ NamedBean* AbstractLightManager::getBySystemName(QString name)
{
 return /*(Light*)*/(_tsys->value(name));
}

/**
 * Locate a Light by its user name
 */
/*public*/ NamedBean *AbstractLightManager::getByUserName(QString key) {
    return /*dynamic_cast<Light*>*/(_tuser->value(key));
}

/**
 * Lookup Light by UserName, then provide by SystemName.
 * {@inheritDoc}
 */
//@Override
//@Nonnull
/*public*/ Light* AbstractLightManager::newLight(/*@Nonnull*/QString systemName, QString userName)
{
 if(systemName.isEmpty())
   throw new IllegalArgumentException("SystemName cannot be null. UserName was " + ((userName == "") ? "null" : userName));  // NOI18N)
 if (log->isDebugEnabled()) log->debug("newLight:"
                                        +( (systemName==NULL) ? "NULL" : systemName)
                                        +";"+( (userName==NULL) ? "NULL" : userName));
 systemName = AbstractManager::validateSystemNameFormat(systemName);
 // return existing if there is one
 Light* l = nullptr;
 if (userName != "") {
     l = (Light*)getByUserName(userName)->self();
     if (l != nullptr) {
         if ((Light*)getBySystemName(systemName)->self() != l) {
             log->error(tr("inconsistent user '%1' and system name '%2' results; user name related to %3").arg(
                 userName, systemName, l->getSystemName()));
         }
         return l;
     }
 }
 l = (Light*)getBySystemName(systemName)->self();
 if (l != nullptr) {
     if ((l->getUserName() == "") && (userName != "")) {
         l->setUserName(userName);
     } else if (userName != "") {
         log->warn(tr("Found light via system name '%1' with non-null user name '%2'").arg(
                 systemName, userName));
     }
     return l;
 }
 // doesn't exist, make a new one
 l = createNewLight(systemName, userName);

 // if that failed, blame it on the input arguements
 if (l == NULL)
 {
  log->error("cannot create new light "+systemName);
  throw new IllegalArgumentException("cannot create new light "+systemName);
 }
 // save in the maps
 AbstractManager::Register(qobject_cast<NamedBean*>(l->self()));
 //emit newLightCreated(this, s);
 return l;
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
        foreach(QString systemName, AbstractManager::getSystemNameList())
        {
        if (systemName.isEmpty()) {
            log->error("System name NULL during activation of Lights");
        }
        else {
            log->debug("Activated Light system name is "+systemName);
            ((Light*)getBySystemName(systemName)->self())->activateLight();
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
    return (plural ? tr("Lights") : tr("Light"));
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
