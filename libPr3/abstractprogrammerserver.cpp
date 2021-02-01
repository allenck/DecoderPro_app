#include "abstractprogrammerserver.h"
#include "loggerfactory.h"
#include "globalprogrammermanager.h"
#include "instancemanager.h"
/**
 * Abstract interface between the a JMRI Programmer and a network connection
 * <p>
 * Connects to default global programmer at construction time.
 *
 * @author Paul Bender Copyright (C) 2012
 */
//abstract /*public*/ class AbstractProgrammerServer implements jmri.ProgListener {


    /*protected*/ Programmer* AbstractProgrammerServer::getProgrammer(QObject *parent) {
        return p;
    }


    /*public*/ AbstractProgrammerServer::AbstractProgrammerServer(QObject *parent) : QObject(parent) {
        if (InstanceManager::getNullableDefault("GlobalProgrammerManager") != nullptr) {
            p = ((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer();
        } else {
            log->warn("no Service Mode ProgrammerManager configured, network programming disabled");
        }
    }

    /*
     * Protocol Specific Abstract Functions
     * @param CV CV number (in DCC terms)
     * @param value vale to read/write to CV
     * @param status Denotes the completion code from a programming operation
     */
//    abstract /*public*/ void sendStatus(int CV, int value, int status) throws IOException;

//    abstract /*public*/ void sendNotAvailableStatus() throws IOException;

//    abstract /*public*/ void parseRequest(String statusString) throws jmri.JmriException, java.io.IOException;

    /*public*/ void AbstractProgrammerServer::writeCV(ProgrammingMode* mode, int CV, int value) {
        if (p == nullptr) {
            try {
                sendNotAvailableStatus();
            } catch (IOException ioe) {
                // Connection Terminated?
            }
            return;
        }
        lastCV = CV;
        try {
            p->setMode(mode); // need to check if mode is available
            p->writeCV(QString::number(CV), value, this);
        } catch (ProgrammerException ex) {
            //Send failure Status.
            try {
                sendNotAvailableStatus();
            } catch (IOException ioe) {
                // Connection Terminated?
            }
        }
    }

    /*public*/ void AbstractProgrammerServer::readCV(ProgrammingMode* mode, int CV) {
        if (p == nullptr || !(p->getCanRead())) {
            try {
                sendNotAvailableStatus();
            } catch (IOException ioe) {
                // Connection Terminated?
            }
            return;
        }
        lastCV = CV;
        try {
            p->setMode(mode); // need to check if mode is available
            p->readCV(QString::number(CV), this);
        } catch (ProgrammerException* ex) {
            //Send failure Status.
            try {
                sendNotAvailableStatus();
            } catch (IOException ioe) {
                // Connection Terminated?
            }
        }
    }

    /**
     * Receive a callback at the end of a programming operation.
     *
     * @param value  Value from a read operation, or value written on a write
     * @param status Denotes the completion code. Note that this is a bitwise
     *               combination of the various status coded defined in this
     *               interface.
     */
    //@Override
    /*public*/ void AbstractProgrammerServer::programmingOpReply(int value, int status) {
        if (log->isDebugEnabled()) {
            log->debug(tr("programmingOpReply called with value %1 and status %2").arg(value).arg(status));
        }
        try {
            sendStatus(lastCV, value, status);
        } catch (IOException ioe) {
            // Connection Terminated?
            if (log->isDebugEnabled()) {
                log->debug("Exception while sending reply");
            }
        }
    }

    /*public*/ void AbstractProgrammerServer::dispose() {
    }

    /*private*/ /*private*/ /*static*/ Logger* AbstractProgrammerServer::log = LoggerFactory::getLogger("AbstractProgrammerServer");
