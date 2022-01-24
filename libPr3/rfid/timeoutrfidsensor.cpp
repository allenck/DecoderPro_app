#include "timeoutrfidsensor.h"
#include "loggerfactory.h"

/**
 * Timeout specific implementation of an RfidSensor.
 * <p>
 * Certain RFID readers only send a message when an RFID tag is within the
 * proximity of the reader - no message is sent when it leaves.
 * <p>
 * As a result, this implementation simulates this message using a timeout
 * mechanism - if no further tags are sensed within a pre-defined time period,
 * the Sensor state reverts to {@link IdTag#UNSEEN}.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General public License for more details.
 * <P>
 *
 * @author Matthew Harris Copyright (C) 2014
 * @since 3.9.2
 */
///*public*/ class TimeoutRfidSensor extends RfidSensor {

/**
 * Timeout in ms
 */
/*private*/ /*static*/ /*final*/ int TimeoutRfidSensor::TIMEOUT = 1000;

/*public*/ TimeoutRfidSensor::TimeoutRfidSensor(QString systemName, QObject*parent) : RfidSensor(systemName, parent)
{
    //super(systemName);
    logDebug = log->isDebugEnabled();
}

/*public*/ TimeoutRfidSensor::TimeoutRfidSensor(QString systemName, QString userName, QObject *parent) : RfidSensor(systemName, userName, parent) {
    //super(systemName, userName);
    logDebug = log->isDebugEnabled();

}

//@Override
/*public*/ void TimeoutRfidSensor::notify(IdTag *t) {
    RfidSensor::notify(t);
    whenLastSensed = QDateTime::currentMSecsSinceEpoch();
    if (timeoutThread == nullptr) {
        (timeoutThread = new RfidSensorTimeoutThread(this))->start();
    }
}

/*private*/ void TimeoutRfidSensor::cleanUpTimeout() {
    if (logDebug) {
        log->debug("Cleanup timeout thread for " + getSystemName());
    }
    timeoutThread = nullptr;
}

///*private*/ class TimeoutThread extends Thread {

//    TimeoutThread() {
//        super();
//        this.setName("Timeout-" + mSystemName);
//    }

//    @Override
//    @SuppressWarnings("SleepWhileInLoop")
//    /*public*/ void run() {
//        while ((whenLastSensed + TIMEOUT) > System.currentTimeMillis()) {
//            try {
//                Thread.sleep(50);
//            } catch (InterruptedException ex) {
//            }
//        }
//        TimeoutRfidSensor.super.notify(null);
//        if (logDebug) {
//            log.debug("Timeout-" + mSystemName);
//        }
//        cleanUpTimeout();
//    }

//}

/*private*/ /*static*/ /*final*/ Logger* TimeoutRfidSensor::log = LoggerFactory::getLogger("TimeoutRfidSensor");


