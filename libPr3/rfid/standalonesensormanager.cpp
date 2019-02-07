#include "standalonesensormanager.h"
#include "loggerfactory.h"
#include "rfidmessage.h"
#include "standalonemessage.h"
#include "instancemanager.h"
#include "rfidsystemconnectionmemo.h"
#include "standalonereply.h"
#include "timeoutrfidsensor.h"
#include "idtagmanager.h"
#include "rfidprotocol.h"

/**
 * Manage the Rfid-specific Sensor implementation.
 * <P>
 * System names are "FSpppp", where ppp is a representation of the RFID reader.
 * <P>
 * @author Bob Jacobsen Copyright (C) 2007
 * @author Matthew Harris Copyright (C) 2011
 * @since 2.11.4
 */
///*public*/ class StandaloneSensorManager extends RfidSensorManager {


/*public*/ StandaloneSensorManager::StandaloneSensorManager(RfidTrafficController* tc, QString prefix, QObject* parent) : RfidSensorManager(prefix, parent){
    //super(prefix);
    this->tc = tc;
    this->prefix = prefix;
    attach();
}

/*private*/ void StandaloneSensorManager::attach() {
    tc->addRfidListener((RfidListener*)this);
}

//@Override
/*protected*/ Sensor* StandaloneSensorManager::createNewSensor(QString systemName, QString userName) {
    log->debug("Create new Sensor");
    TimeoutRfidSensor* s;
    s = new TimeoutRfidSensor(systemName, userName);
    //s.addPropertyChangeListener(this);
    connect(s, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    return s;
}

//@Override
/*public*/ void StandaloneSensorManager::message(RfidMessage* m)
{

    if (m->toString() == StandaloneMessage(tc->getAdapterMemo()->getProtocol()->initString(), 0).toString()) {
        log->info("Sent init string: " + m->toString());
    } else {
        RfidSensorManager::message(m->toString());
    }
}

//@Override
/*public*/ /*synchronized*/ void StandaloneSensorManager::reply(RfidReply* r) {
    if (qobject_cast<StandaloneReply*>(r)) {
        processReply((StandaloneReply*) r);
    }
}

/*private*/ void StandaloneSensorManager::processReply(StandaloneReply* r) {
    if (!tc->getAdapterMemo()->getProtocol()->isValid(r)) {
        log->warn("Invalid message - skipping " + r->toString());
        return;
    }
    IdTag* idTag = static_cast<IdTagManager*>( InstanceManager::getDefault("IdTagManager"))->provideIdTag(tc->getAdapterMemo()->getProtocol()->getTag(r));
    TimeoutRfidSensor* sensor = (TimeoutRfidSensor*) provideSensor(prefix + typeLetter() + "1");
    sensor->notify(idTag);
}

// to free resources when no longer used
//@Override
/*public*/ void StandaloneSensorManager::dispose() {
    RfidSensorManager::dispose();
}

/*private*/ /*static*/ /*final*/ Logger* StandaloneSensorManager::log = LoggerFactory::getLogger("StandaloneSensorManager");


