#include "simplelightserver.h"
#include <QTcpSocket>
#include "loggerfactory.h"

/**
 * Simple Server interface between the JMRI light manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
///*public*/ class SimpleLightServer extends AbstractLightServer {


    /*public*/ SimpleLightServer::SimpleLightServer(QTcpSocket* connection, QObject *parent) {
        this->connection = connection;
    }

//    /*public*/ SimpleLightServer(DataInputStream inStream, DataOutputStream outStream) {

//        output = outStream;
//    }


    /*
     * Protocol Specific Abstract Functions
     */
    //@Override
    /*public*/ void SimpleLightServer::sendStatus(QString lightName, int Status) throw (IOException) {
        if (Status == Light::ON) {
            this->sendMessage("LIGHT " + lightName + " ON\n");
        } else if (Status == Light::OFF) {
            this->sendMessage("LIGHT " + lightName + " OFF\n");
        } else {
            //  unknown state
            this->sendMessage("LIGHT " + lightName + " UNKNOWN\n");
        }
    }

    //@Override
    /*public*/ void SimpleLightServer::sendErrorStatus(QString lightName) throw (IOException) {
        this->sendMessage("LIGHT ERROR\n");
    }

    //@Override
    /*public*/ void SimpleLightServer::parseStatus(QString statusString) throw (JmriException, IOException) {
        int index;
        index = statusString.indexOf(" ") + 1;
        if (statusString.contains("ON")) {
            if (log->isDebugEnabled()) {
                log->debug("Setting Light ON");
            }
            initLight(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
            lightOn(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        } else if (statusString.contains("OFF")) {
            if (log->isDebugEnabled()) {
                log->debug("Setting Light OFF");
            }
            initLight(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
            lightOff(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        }
    }

    /*private*/ void SimpleLightServer::sendMessage(QString message) throw (IOException) {
        if (this->output != nullptr) {
            this->output->writeBytes(message.toLocal8Bit(), message.length());
        } else {
            this->connection->write(message.toLocal8Bit());
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* SimpleLightServer::log = LoggerFactory::getLogger("SimpleLightServer");
