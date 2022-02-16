#include "simplesignalheadserver.h"

/**
 * Simple Server interface between the JMRI Sensor manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
// /*public*/ class SimpleSignalHeadServer extends AbstractSignalHeadServer {

    /*public*/ SimpleSignalHeadServer::SimpleSignalHeadServer(QTcpSocket* connection, QObject *parent) : AbstractSignalHeadServer(parent) {
        //super();
        this->connection = connection;
    }

//    /*public*/ SimpleSignalHeadServer(DataInputStream inStream, DataOutputStream outStream) {
//        super();
//        output = outStream;
//    }

    /*
     * Protocol Specific Abstract Functions
     */
    //@Override
    /*public*/ void SimpleSignalHeadServer::sendStatus(QString signalHeadName, int Status) /*throw (IOException)*/ {
        this->addSignalHeadToList(signalHeadName);
        this->sendMessage("SIGNALHEAD " + signalHeadName + " " + this->nameForAppearance(Status) + "\n");
    }

    //@Override
    /*public*/ void SimpleSignalHeadServer::sendErrorStatus(QString signalHeadName) /*throw (IOException)*/ {
        this->sendMessage("SIGNALHEAD ERROR\n");
    }

    //@Override
    /*public*/ void SimpleSignalHeadServer::parseStatus(QString statusString) /*throw (JmriException, IOException)*/ {
        QStringList status = statusString.split(QRegExp("\\s+"));
        if (status.length() == 3) {
            this->setSignalHeadAppearance(status[1], status[2]);
        } else {
            SignalHead* signalHead = qobject_cast<SignalHeadManager*>(InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(status[1]);
            if(signalHead != nullptr) {
               this->sendStatus(signalHead->getSystemName(), signalHead->getAppearance());
            } else {
               sendErrorStatus(status[1]);
            }
        }
    }

     /*private*/ void SimpleSignalHeadServer::sendMessage(QString message) /*throw (IOException)*/ {
        if (this->output != nullptr) {
            this->output->writeBytes(message.toLocal8Bit().data(),message.length());
        } else {
            this->connection->write(message.toLocal8Bit());
        }
    }
