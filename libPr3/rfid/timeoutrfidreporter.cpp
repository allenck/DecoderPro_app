#include "timeoutrfidreporter.h"
#include "loggerfactory.h"

/**
 * Timeout specific implementation of an RfidReporter.
 * <p>
 * Certain RFID readers only send a message when an RFID tag is within the
 * proximity of the reader - no message is sent when it leaves.
 * <p>
 * As a result, this implementation simulates this message using a timeout
 * mechanism - if no further tags are sensed within a pre-defined time period,
 * the Reporter value is nullified and state reverts to {@link IdTag#UNSEEN}.
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
///*public*/ class TimeoutRfidReporter extends RfidReporter {

/**
 * Timeout in ms
 */
/*private*/ /*static*/ /*final*/ int TimeoutRfidReporter::TIMEOUT = 2000;

    /*public*/ TimeoutRfidReporter::TimeoutRfidReporter(QString systemName, QObject* parent): RfidReporter(systemName, parent) {
        //super(systemName);
        logDebug = log->isDebugEnabled();
    }

    /*public*/ TimeoutRfidReporter::TimeoutRfidReporter(QString systemName, QString userName, QObject* parent) :RfidReporter(systemName, userName, parent){
        //super(systemName, userName);
        logDebug = log->isDebugEnabled();

    }

    //@Override
    /*public*/ void TimeoutRfidReporter::notify(DefaultIdTag* t) {
        RfidReporter::notify(t);
        whenLastReported = QDateTime::currentMSecsSinceEpoch();
        if (timeoutThread == nullptr) {
            (timeoutThread = new RfidReporterTimeoutThread(this))->start();
        }
    }

    /*private*/ void TimeoutRfidReporter::cleanUpTimeout() {
        if (logDebug) {
            log->debug("Cleanup timeout thread for " + mSystemName);
        }
        timeoutThread = nullptr;
    }


    /*private*/ /*static*/ /*final*/ Logger*TimeoutRfidReporter:: log = LoggerFactory::getLogger("TimeoutRfidReporter");


