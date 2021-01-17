#include "internallightmanager.h"
#include "internalsystemconnectionmemo.h"

InternalLightManager::InternalLightManager(InternalSystemConnectionMemo* memo, QObject *parent) :
    AbstractLightManager(memo, parent)
{
 setObjectName("InternalLightManager");
 setProperty("JavaClassName", "jmri.jmrix.internal.InternalLightManager");

 registerSelf();
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
//@Override
/*protected*/ Light* InternalLightManager::createNewLight(QString systemName, QString userName) {
//    return new AbstractVariableLight(systemName, userName) {

//        //protected void forwardCommandChangeToLayout(int s) {}
//        @Override
//        protected void sendIntensity(double intensity) {
//        }

//        @Override
//        protected void sendOnOffCommand(int newState) {
//        }

//        @Override
//        protected int getNumberOfSteps() {
//            return 100;
//        }
//    };
 return new AbstractVariableLightO1(systemName, userName);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo* InternalLightManager::getMemo() const {
    return  memo;
}

/*public*/ bool InternalLightManager::validSystemNameConfig(QString /*systemName*/) const {
    return true;
}

/*public*/ bool InternalLightManager::supportsVariableLights(QString /*systemName*/) {
    return true;
}
/*public*/ bool InternalLightManager::allowMultipleAdditions(QString /*systemName*/) {
    return true;  }
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString InternalLightManager::getEntryToolTip() {
    return tr("abc123<br>(any string except $, :, \\).");
}
