#include "rfidsensormanager.h"
#include "rfidsensor.h"

RfidSensorManager::RfidSensorManager(QObject *parent) :
    AbstractSensorManager(parent)
{
 this->prefix = "F";
 //tc = NULL;
}
/**
 * Manage the Rfid-specific Sensor implementation.
 * <P>
 * System names are "FSpppp", where ppp is a
 * representation of the RFID reader.
 * <P>
 * @author      Bob Jacobsen Copyright (C) 2007
 * @author      Matthew Harris Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
//abstract /*public*/ class RfidSensorManager extends jmri.managers.AbstractSensorManager implements RfidListener {


/*public*/ RfidSensorManager::RfidSensorManager(QString prefix, QObject* parent) : AbstractSensorManager(parent)
{
    //super();
    this->prefix = prefix;
    //tc = NULL;
}

/*public*/ QString RfidSensorManager::getSystemPrefix() {
    return prefix;
}

// to free resources when no longer used
//@Override
/*public*/ void RfidSensorManager::dispose() {
    //super.dispose();
 AbstractSensorManager::dispose();
}

//    /*public*/ Sensor createNewSensor(String systemName, String userName) {
//        RfidSensor r = new RfidSensor(systemName, userName);
//        return r;
//    }

/*public*/ void RfidSensorManager::message(/*RfidMessage*/QString m) {
    log.warn("Unexpected message received"+m);
}

//    private static final org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(RfidSensorManager.class.getName());

//}
Sensor* RfidSensorManager::createNewSensor(QString systemName, QString userName)
{
 RfidSensor* s = new RfidSensor(systemName, userName, this);
 s->AbstractNamedBean::setUserName(userName);
 return (Sensor*)s;
}
