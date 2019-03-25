#include "simplepowerserver.h"
#include <QTcpSocket>
#include "powermanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"

/**
 * Simple Server interface between the JMRI power manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2010
 */
///*public*/ class SimplePowerServer extends AbstractPowerServer {

/*public*/ SimplePowerServer::SimplePowerServer(QDataStream* inStream, QDataStream* outStream, QObject* parent)
 : AbstractPowerServer(parent)
{
    output = outStream;
    mgrOK();
}

/*public*/SimplePowerServer:: SimplePowerServer(QTcpSocket *clientSocket) {
    this->clientSocket = clientSocket;
    mgrOK();
}

/*
 * Protocol Specific Abstract Functions
 */
//@Override
/*public*/ void SimplePowerServer::sendStatus(int Status) throw (IOException) {
    if (Status == PowerManager::ON) {
        this->sendStatus("POWER ON\n");
    } else if (Status == PowerManager::OFF) {
        this->sendStatus("POWER OFF\n");
    } else {
        this->sendStatus("POWER UNKNOWN\n");
    }
}

//@Override
/*public*/ void SimplePowerServer::sendErrorStatus() throw (IOException) {
    this->sendStatus("POWER ERROR\n");
}

//@Override
/*public*/ void SimplePowerServer::parseStatus(QString statusString) throw (JmriException) {
 log->debug("statusString = " + statusString);
#if 0
    JmriServerParser p = new JmriServerParser(new java.io.StringReader(statusString));
    try{
       try{
          SimpleNode e=p.powercmd();
          SimpleVisitor v = new SimpleVisitor();
          e.jjtAccept(v,this);
          if(v.getOutputString() != null ){
             sendStatus(v.getOutputString());
          }
       } catch(ParseException pe){
          sendErrorStatus();
       }
    } catch(IOException ioe) {
      // we should check to see if there is an
    }
#endif
    int status = p->getPower();
    QStringList sl = statusString.split(" ");
    if(sl.count()> 1 && sl.at(0) == "ON")
    {
     if(status != PowerManager::ON)
      p->setPower(PowerManager::ON);
     else
      sendStatus(status);
    }
    if(sl.count()> 1 && sl.at(0) == "OFF")
    {
     if(status != PowerManager::OFF)
      p->setPower(PowerManager::OFF);
     else
      sendStatus(status);
    }
}

/*public*/ void SimplePowerServer::sendStatus(QString status) throw (IOException) {
    if (this->output != nullptr) {
        this->output->writeBytes(status.toLocal8Bit(), status.length());
    } else {
        this->clientSocket->write(status.toLocal8Bit());
    }
}

/*private*/ /*static*/ Logger* SimplePowerServer::log = LoggerFactory::getLogger("SimplePowerServer");
