#include "simpleturnoutserver.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include <QDataStream>
#include <QTcpSocket>
#include "jmriexception.h"

/**
 * Simple Server interface between the JMRI turnout manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class SimpleTurnoutServer extends AbstractTurnoutServer {


/*public*/ SimpleTurnoutServer::SimpleTurnoutServer(QTcpSocket* clientSocket, QObject* parent)
 : AbstractTurnoutServer(parent)
{
    this->clientSocket = clientSocket;
}

/*public*/ SimpleTurnoutServer::SimpleTurnoutServer(QDataStream* inStream, QDataStream* outStream, QObject* parent)
 : AbstractTurnoutServer(parent) {

    output = outStream;
}


/*
 * Protocol Specific Abstract Functions
 */
//@Override
/*public*/ void SimpleTurnoutServer::sendStatus(QString turnoutName, int Status) /*throw (IOException)*/ {
    addTurnoutToList(turnoutName);
    if (Status == Turnout::THROWN) {
        this->sendMessage("TURNOUT " + turnoutName + " THROWN\n");
    } else if (Status == Turnout::CLOSED) {
        this->sendMessage("TURNOUT " + turnoutName + " CLOSED\n");
    } else {
        //  unknown state
        this->sendMessage("TURNOUT " + turnoutName + " UNKNOWN\n");
    }
}

//@Override
/*public*/ void SimpleTurnoutServer::sendErrorStatus(QString turnoutName) /*throw (IOException)*/ {
    this->sendMessage("TURNOUT ERROR\n");
}

//@Override
/*public*/ void SimpleTurnoutServer::parseStatus(QString statusString) /*throw (JmriException, IOException)*/ {
    int index;
    index = statusString.indexOf(" ") + 1;
    log->debug(statusString);
    if (statusString.contains("THROWN")) {
        if (log->isDebugEnabled()) {
            log->debug("Setting Turnout THROWN");
        }
        // create turnout if it does not exist since throwTurnout() no longer does so
        this->initTurnout(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        throwTurnout(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
    } else if (statusString.contains("CLOSED")) {
        if (log->isDebugEnabled()) {
            log->debug("Setting Turnout CLOSED");
        }
        // create turnout if it does not exist since closeTurnout() no longer does so
        this->initTurnout(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        closeTurnout(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
    } else {
        // default case, return status for this turnout
        try {
            sendStatus(statusString.mid(index),
                InstanceManager::turnoutManagerInstance()->provideTurnout(statusString.mid(index).toUpper())->getKnownState());
        } catch (IllegalArgumentException* ex) {
            log->warn(tr("Failed to provide Turnout \"%1\" in parseStatus").arg(statusString.mid(index).toUpper()));
        }
    }
}

/*private*/ void SimpleTurnoutServer::sendMessage(QString message) /*throw (IOException)*/ {
    if (this->output != nullptr) {
        this->output->writeBytes(message.toLocal8Bit(), message.length());
    } else {
        this->clientSocket->write(message.toLocal8Bit());
    }
}

/*private*/ /*final*/ /*static*/ Logger* SimpleTurnoutServer::log = LoggerFactory::getLogger("SimpleTurnoutServer");
