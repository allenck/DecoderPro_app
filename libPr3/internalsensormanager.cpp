#include "internalsensormanager.h"
#include "exceptions.h"
#include "abstractsensor.h"
#include "instancemanager.h"
#include "defaultusermessagepreferences.h"

/**
 * Implementation of the InternalSensorManager interface.
 * @author			Bob Jacobsen Copyright (C) 2001, 2003, 2006
 * @version			$Revision: 17977 $
 */
///*public*/ class InternalSensorManager extends AbstractSensorManager {
InternalSensorManager::InternalSensorManager()
{
 setObjectName("InternalSensorManager");
 prefix = "I";
 registerSelf(); // Added by ACK
}
/*public*/ bool InternalSensorManager::allowMultipleAdditions(QString /*systemName*/) { return true;  }
/**
 * Create an internal (dummy) sensor object
 * @return new null
 */
/*protected*/ Sensor* InternalSensorManager::createNewSensor(QString systemName, QString userName)
{
  Sensor* sen = (Sensor*)new InternalAbstractSensor(systemName, userName);
//    {
//        /*public*/ void requestUpdateFromLayout(){}
//    };
  sen->setKnownState(getDefaultStateForNewSensors());
  return sen;
}
/*static*/ int InternalSensorManager::defaultState = Sensor::UNKNOWN;

/*public*/ /*static*/ /*synchronized*/ void InternalSensorManager::setDefaultStateForNewSensors(int defaultSetting) {
    defaultState = defaultSetting;
}

/*public*/ /*static*/ /*synchronized*/ int InternalSensorManager::getDefaultStateForNewSensors() {
    return defaultState;
}

/*public*/ QString InternalSensorManager::getNextValidAddress(QString curAddress, QString prefix)
{
    //If the hardware address past does not already exist then this can
    //be considered the next valid address.
    Sensor* s = getBySystemName(prefix+QString(typeLetter())+curAddress);
    if(s==NULL){
        return curAddress;
    }

    // This bit deals with handling the curAddress, and how to get the next address.
    int iName = 0;
    try {
        iName = curAddress.toInt();
    } catch (NumberFormatException ex) {
        log.error("Unable to convert " + curAddress + " Hardware Address to a number");
        ((DefaultUserMessagePreferences*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",ex.getMessage(), "",true, false, Level::_ERROR);
        return NULL;
    }
    //Check to determine if the systemName is in use, return null if it is,
    //otherwise return the next valid address.
    s = getBySystemName(prefix+typeLetter()+iName);
    if(s!=NULL){
        for(int x = 1; x<10; x++){
            iName = iName + 1;
            s = getBySystemName(prefix+typeLetter()+iName);
            if(s==NULL)
                return QString("%1").arg(iName);
        }
        return NULL;
    } else {
        return QString("%1").arg(iName);
    }
}

/*public*/ QString InternalSensorManager::getSystemPrefix() { return prefix; }

