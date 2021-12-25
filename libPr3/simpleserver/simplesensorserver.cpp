#include "simplesensorserver.h"
#include <QDataStream>
#include <QTcpSocket>
#include "loggerfactory.h"
#include "sensormanager.h"
#include "instancemanager.h"

/**
 * Simple Server interface between the JMRI Sensor manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
///*public*/ class SimpleSensorServer extends AbstractSensorServer {


/*public*/ SimpleSensorServer::SimpleSensorServer(QTcpSocket* clientSocket, QObject* parent) : AbstractSensorServer(parent) {
    //super();
    this->clientSocket = clientSocket;
}

/*public*/ SimpleSensorServer::SimpleSensorServer(QDataStream* inStream, QDataStream* outStream, QObject* parent) {
    //super();
    output = outStream;
}


/*
 * Protocol Specific Abstract Functions
 */
////@Override
/*public*/ void SimpleSensorServer::sendStatus(QString sensorName, int Status) /*throw (IOException)*/ {
    addSensorToList(sensorName);

    if (Status == Sensor::INACTIVE) {
        this->sendMessage("SENSOR " + sensorName + " INACTIVE\n");
    } else if (Status == Sensor::ACTIVE) {
        this->sendMessage("SENSOR " + sensorName + " ACTIVE\n");
    } else {
        this->sendMessage("SENSOR " + sensorName + " UNKNOWN\n");
    }
}

//@Override
/*public*/ void SimpleSensorServer::sendErrorStatus(QString sensorName) /*throw (IOException)*/ {
    this->sendMessage("SENSOR ERROR\n");
}

//@Override
/*public*/ void SimpleSensorServer::parseStatus(QString statusString) throw (JmriException, IOException) {
    int index;
    index = statusString.indexOf(" ") + 1;
    if (statusString.contains("INACTIVE")) {
        if (log->isDebugEnabled()) {
            log->debug("Setting Sensor INACTIVE");
        }
        initSensor(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        setSensorInactive(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
    } else if (statusString.contains("ACTIVE")) {
        if (log->isDebugEnabled()) {
            log->debug("Setting Sensor ACTIVE");
        }
        initSensor(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
        setSensorActive(statusString.mid(index, statusString.indexOf(" ", index + 1)).toUpper());
    } else {
        // default case, return status for this sensor/
        QString sensorName = statusString.mid(index,statusString.length()-1).toUpper(); // remove the \n
        if( sensorName.contains(" ") ){
            // remove anything following the space.
            sensorName = sensorName.mid(0,sensorName.indexOf(" "));
        }
        try {
            Sensor* sensor = InstanceManager::sensorManagerInstance()->provideSensor(sensorName);
            sendStatus(sensorName, sensor->getKnownState());
        } catch (IllegalArgumentException* ex) {
            log->warn(tr("Failed to provide Sensor \"%1\" in sendStatus").arg(sensorName));
        }
    }
}

/*private*/ void SimpleSensorServer::sendMessage(QString message) /*throw (IOException)*/ {
    if (this->output != nullptr) {
        this->output->writeBytes(message.toLocal8Bit(), message.length());
    } else {
        this->clientSocket->write(message.toLocal8Bit());
    }
}
/*private*/ /*final*/ /*static*/ Logger* SimpleSensorServer::log = LoggerFactory::getLogger("SimpleSensorServer");
