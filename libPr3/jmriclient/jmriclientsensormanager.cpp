#include "jmriclientsensormanager.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientsensor.h"
/**
 * Implement sensor manager for JMRIClient systems
 * <P>
 * System names are "prefixnnn", where prefix is the system prefix and nnn is
 * the sensor number without padding.
 *
 * @author Paul Bender Copyright (C) 2010
  */
// /*public*/ class JMRIClientSensorManager extends jmri.managers.AbstractSensorManager {


/*public*/ JMRIClientSensorManager::JMRIClientSensorManager(JMRIClientSystemConnectionMemo* memo, QObject *parent)
: AbstractSensorManager(parent)
{
    this->memo = memo;
    this->prefix = memo->getSystemPrefix();
}

//@Override
/*public*/ QString JMRIClientSensorManager::getSystemPrefix() {
    return prefix;
}

//@Override
/*public*/ Sensor* JMRIClientSensorManager::createNewSensor(QString systemName, QString userName) {
    Sensor* t;
    int addr = (systemName.mid(prefix.length() + 1).toInt());
    t = new JMRIClientSensor(addr, memo);
    t->setUserName(userName);
    return t;
}

/*
 * JMRIClient Sensors can take arbitrary names to match the names used
 * on the server.
 */
//@Override
/*public*/ QString JMRIClientSensorManager::createSystemName(QString curAddress, QString prefix) throw (JmriException) {
    return prefix + typeLetter() + curAddress;
}
