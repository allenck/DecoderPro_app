#include "rpssensormanager.h"
#include "rpssystemconnectionmemo.h"
#include "loggerfactory.h"
#include "rpssensor.h"
#include "distributor.h"
/**
 * Manage the RPS-specific Sensor implementation.
 * <p>
 * System names are "RSpppp", where ppp is a CSV representation of the region.
 *
 * @author	Bob Jacobsen Copyright (C) 2007, 2019
 */
// /*public*/ class RpsSensorManager extends jmri.managers.AbstractSensorManager {

/*public*/ RpsSensorManager::RpsSensorManager(RpsSystemConnectionMemo* memo,QObject* parent) : AbstractSensorManager(memo, parent){
    //super(memo);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo* RpsSensorManager::getMemo()const {
    return  memo;
}

// to free resources when no longer used
//@Override
/*public*/ void RpsSensorManager::dispose() {
    AbstractSensorManager::dispose();
}

/**
 * Create a new sensor if all checks are passed.
 * System name is normalized to ensure uniqueness.
 */
//@Override
/*public*/ Sensor* RpsSensorManager::createNewSensor(QString systemName, QString userName) {
//    try {
       RpsSensor* r = new RpsSensor(systemName, userName, getSystemPrefix());
       Distributor::instance()->addMeasurementListener(r);
       return r;
//   } catch(StringIndexOutOfBoundsException sioe){
//     throw  IllegalArgumentException("Invalid System Name: " + systemName);
//   }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString RpsSensorManager::createSystemName(QString curAddress, QString prefix) const throw (JmriException) {
    if (prefix != (getSystemPrefix())) {
        log->warn("prefix does not match memo.prefix");
        return "";
    }
    QString sys = getSystemPrefix() + typeLetter() + curAddress;
    // first, check validity
    try {
        validSystemNameFormat(sys);
    } catch (IllegalArgumentException e) {
        throw new JmriException(e.toString());
    }
    return sys;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString RpsSensorManager::validateSystemNameFormat(QString name, QLocale locale) {
    return ((RpsSystemConnectionMemo*)getMemo())->validateSystemNameFormat(name, this, locale);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ Manager::NameValidity RpsSensorManager::validSystemNameFormat(QString systemName) const{
    return ((RpsSystemConnectionMemo*)getMemo())->validSystemNameFormat(systemName, typeLetter());
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString RpsSensorManager::getEntryToolTip() {
    return tr("AddInputEntryToolTip");
}

/*private*/ /*final*/ /*static*/ Logger* RpsSensorManager::log = LoggerFactory::getLogger("RpsSensorManager");
