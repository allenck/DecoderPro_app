#include "internallightmanager.h"
#include "abstractvariablelight.h"

InternalLightManager::InternalLightManager(QObject *parent) :
    AbstractLightManager(parent)
{
 setObjectName("InternalLightManager");
 setProperty("JavaClassName", "jmri.jmrix.internal.InternalLightManager");

 //registerSelf();
}
/**
 * Implement a light manager for "Internal" (virtual) lights.
 *
 * @author			Bob Jacobsen Copyright (C) 2009
 * @version			$Revision: 17977 $
 */
//public class InternalLightManager extends AbstractLightManager {

/**
 * Create and return an internal (no layout connection) Light
 */
/*protected*/ Light* InternalLightManager::createNewLight(QString systemName, QString userName)
{
 return (Light*)new AbstractVariableLight(systemName, userName);
//        //protected void forwardCommandChangeToLayout(int s) {}
//        protected void sendIntensity(double intensity) {}
//        protected void sendOnOffCommand(int newState) {}
//        protected int getNumberOfSteps() { return 100; }
//    };
}

/*public*/ QString InternalLightManager::getSystemPrefix() { return "I"; }
/*public*/ bool InternalLightManager::validSystemNameConfig(QString /*systemName*/) {
    return true;
}
/*public*/ Manager::NameValidity InternalLightManager::validSystemNameFormat(QString /*systemName*/) {
    return NameValidity::VALID;
}
/*public*/ bool InternalLightManager::supportsVariableLights(QString /*systemName*/) {
    return true;
}
/*public*/ bool InternalLightManager::allowMultipleAdditions(QString /*systemName*/) {
    return true;  }
