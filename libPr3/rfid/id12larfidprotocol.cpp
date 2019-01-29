#include "id12larfidprotocol.h"
#include "abstractmrreply.h"
#include "loggerfactory.h"

Id12LARfidProtocol::Id12LARfidProtocol(QObject *parent) : RfidProtocol(parent)
{

}
/**
 * Common routines to extract the Tag information and validate checksum for
 * implementations that use the Olimex protocol.
 * <hr>
 * This file is part of JMRI.
 * <P>
 * JMRI is free software; you can redistribute it and/or modify it under the
 * terms of version 2 of the GNU General Public License as published by the Free
 * Software Foundation. See the "COPYING" file for a copy of this license.
 * <P>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * <P>
 *
 * @author Matthew Harris Copyright (C) 2014
 * @since 3.9.2
 */
///*public*/ class Id12LARfidProtocol extends RfidProtocol {

    /*public*/ /*static*/ /*final*/ int Id12LARfidProtocol::SPECIFICMAXSIZE = 16;

    /*public*/ /*static*/ /*final*/ int Id12LARfidProtocol::getMaxSize() {
        return SPECIFICMAXSIZE;
    }

    //@Override
    /*public*/ QString Id12LARfidProtocol::initString() {
        // Continuous scanning, single report per seen tag
        return "mc00"; // NOI18N
    }

    //@Override
    /*public*/ QString Id12LARfidProtocol::getTag(AbstractMRReply* msg) {
        QString sb;// = new StringBuilder(10);

        for (int i = 1; i < 13; i++) {
            sb.append((char) msg->getElement(i));
        }

        return sb;
    }

    //@Override
    /*public*/ QString Id12LARfidProtocol::getCheckSum(AbstractMRReply* msg) {
        return "";
    }

    //@Override
    /*public*/ bool Id12LARfidProtocol::isValid(AbstractMRReply* msg) {
        return ((!isConcentrator && msg->getElement(0) == 0x02 && msg->getElement(15) == 0x03)
                || (isConcentrator
                && msg->getElement(portPosition) >= concentratorFirst
                && msg->getElement(portPosition) <= concentratorLast))
                && msg->getElement(SPECIFICMAXSIZE - 1) == 0x3E;
    }

    //@Override
    /*public*/ bool Id12LARfidProtocol::endOfMessage(AbstractMRReply* msg) {
        if (msg->getNumDataElements() == SPECIFICMAXSIZE) {
            if ((msg->getElement(SPECIFICMAXSIZE - 1) & 0xFF) == 0x3E
                    && (msg->getElement(SPECIFICMAXSIZE - 2) & 0xFF) == 0x0A
                    && (msg->getElement(SPECIFICMAXSIZE - 3) & 0xFF) == 0x0D) {
                return true;
            }
            if (log->isDebugEnabled()) {
                log->debug("Not a correctly formed message"); // NOI18N
            }
            return true;
        }
        return false;
    }

    //@Override
    /*public*/ QString Id12LARfidProtocol::toMonitorString(AbstractMRReply* msg) {
        // check for valid message
        if (isValid(msg)) {
            QString sb;// = new StringBuilder();
            sb.append("Reply from Olimex reader.");
            if (isConcentrator) {
                sb.append(" Reply from port ");
                sb.append(getReaderPort(msg));
            }
            sb.append(" Tag read ");
            sb.append(getTag(msg));
            return sb;
        } else {
            return RfidProtocol::toMonitorString(msg);
        }
    }

    /*private*/ /*static*/ /*final*/ Logger* Id12LARfidProtocol::log = LoggerFactory::getLogger("Id12LARfidProtocol");
