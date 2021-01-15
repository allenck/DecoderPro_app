#include "internalsensormanager.h"
#include "exceptions.h"
#include "abstractsensor.h"
#include "instancemanager.h"
#include "jmriuserpreferencesmanager.h"
#include "internalsystemconnectionmemo.h"
#include "loggerfactory.h"

/**
 * Implementation of the InternalSensorManager interface.
 * @author			Bob Jacobsen Copyright (C) 2001, 2003, 2006
 * @version			$Revision: 17977 $
 */
///*public*/ class InternalSensorManager extends AbstractSensorManager {
InternalSensorManager::InternalSensorManager(QObject *parent) : AbstractSensorManager(parent)
{
 setObjectName("InternalSensorManager");
 setProperty("JavaClassName", "jmri.jmrix.internal.InternalSensorManager");

 prefix = memo->getSystemPrefix();//"I";
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}

InternalSensorManager::InternalSensorManager(InternalSystemConnectionMemo* memo, QObject *parent) : AbstractSensorManager(memo,parent)
{
 setObjectName("InternalSensorManager");
 setProperty("JavaClassName", "jmri.jmrix.internal.InternalSensorManager");

 prefix = "I";
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}

/*public*/ InternalSensorManager::InternalSensorManager(QString prefix) {
    //super();
 setObjectName("InternalSensorManager");
 setProperty("JavaClassName", "jmri.jmrix.internal.InternalSensorManager");

 this->prefix = prefix;
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}

/*public*/ bool InternalSensorManager::allowMultipleAdditions(QString /*systemName*/)
{
 return true;
}

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
  try
  {
   sen->setKnownState(getDefaultStateForNewSensors());
  return sen;
  }
  catch (JmriException ex) {
   log->error("An error occurred while trying to set initial state for sensor " + sen->getDisplayName());
   log->error(ex.toString());
  }
  log->debug(tr("Internal Sensor \"%1\", \"%2\" created").arg(systemName).arg(userName));
}

/*static*/ int InternalSensorManager::defaultState = Sensor::UNKNOWN;

/*public*/ /*static*/ /*synchronized*/ void InternalSensorManager::setDefaultStateForNewSensors(int defaultSetting) {
    defaultState = defaultSetting;
}

/*public*/ /*static*/ /*synchronized*/ int InternalSensorManager::getDefaultStateForNewSensors() {
    return defaultState;
}

/** {@inheritDoc} */
//@Override
/*public*/ QString InternalSensorManager::getEntryToolTip() {
    return tr("abc123<br>(any string except $, :, \).");
}

/*public*/ QString InternalSensorManager::getNextValidAddress(QString curAddress, QString prefix)
{
    //If the hardware address past does not already exist then this can
    //be considered the next valid address.
    Sensor* s = (Sensor*)getBySystemName(prefix+QString(typeLetter())+curAddress);
    if(s==NULL){
        return curAddress;
    }

    // This bit deals with handling the curAddress, and how to get the next address.
    int iName = 0;
    try {
        iName = curAddress.toInt();
    } catch (NumberFormatException ex) {
        log->error("Unable to convert " + curAddress + " Hardware Address to a number");
        ((UserPreferencesManager*)InstanceManager::getDefault("UserPreferencesManager"))->showInfoMessage("Error","Unable to convert " + curAddress + " to a valid Hardware Address",ex.getMessage(), "",true, false);
        return NULL;
    }
    //Check to determine if the systemName is in use, return null if it is,
    //otherwise return the next valid address.
    s = (Sensor*)getBySystemName(prefix+typeLetter()+iName);
    if(s!=NULL){
        for(int x = 1; x<10; x++){
            iName = iName + 1;
            s = (Sensor*)getBySystemName(prefix+typeLetter()+iName);
            if(s==NULL)
                return QString("%1").arg(iName);
        }
        return NULL;
    } else {
        return QString("%1").arg(iName);
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo* InternalSensorManager::getMemo() const {
    return  memo;
}

/*private*/ /*final*/ /*static*/ Logger* InternalSensorManager::log = LoggerFactory::getLogger("InternalSensorManager");

