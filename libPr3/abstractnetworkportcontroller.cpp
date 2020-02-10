#include "abstractnetworkportcontroller.h"
#include "jmrixconfigpane.h"
#include "exceptions.h"
#include <QTcpSocket>
#include "connectionstatus.h"
#include <QAbstractSocket>
#include "systemconnectionmemo.h"
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>


//AbstractNetworkPortController::AbstractNetworkPortController(QObject *parent) :
//  AbstractPortController(parent)
//{
//}
/**
 * Enables basic setup of a network client interface for a jmrix implementation.
 *
 *
 * @author Kevin Dickerson Copyright (C) 2010
 * @author Based upon work originally done by Paul Bender Copyright (C) 2009
 * @version	$Revision: 28746 $
 * @see jmri.jmrix.NetworkConfigException
 */
//abstract /*public*/ class AbstractNetworkPortController extends AbstractPortController implements NetworkPortAdapter {



/*protected*/ AbstractNetworkPortController::AbstractNetworkPortController(SystemConnectionMemo* connectionMemo, QObject *parent) :
  AbstractPortController(connectionMemo, parent) \
{
 //super(connectionMemo);
 log = new Logger("AbstractNetworkPortController");
 m_port = 0;
 socketConn = NULL;
 opened = false;
 setHostName(""); // give the host name a default value of
 // the empty string.
 allowConnectionRecovery = true;
//#if QT_VERSION < 0x50000
// qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");
// qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
//#endif
 msg = NULL;


}

//@Override
/*public*/ void AbstractNetworkPortController::_connect(QString host, int port) throw (Exception)
{
 setHostName(host);
 setPort(port);
 try
 {
  _connect();
 } catch (Exception e)
 {
  throw e;
 }
}

//@Override
/*public*/ void AbstractNetworkPortController::_connect() //throws Exception
{
 opened = false;
 if (getHostAddress() == "" || m_port == 0)
 {
  log->error("No host name or port set :" + m_HostName + ":" + m_port);
  return;
 }
 log->debug(tr("Attempting to connect to host: %1 on port %2").arg(m_HostName).arg(QString::number(m_port)));
 try
 {
  if(socketConn == NULL)
  {
   socketConn = new QTcpSocket(/*getHostAddress(), m_port*/);
   connect(socketConn, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socketConn_error(QAbstractSocket::SocketError)));
   connect(socketConn,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(st_stateChange(QAbstractSocket::SocketState)));
   connect(socketConn, SIGNAL(hostFound()), this, SLOT(on_socketConn_hostFound()));
   connect(socketConn, SIGNAL(connected()), this, SLOT(on_socketConn_connected()));
   connect(socketConn, SIGNAL(disconnected()), this, SLOT(on_socketConn_disconnected()));
  }
  //else socketConn->reset();

  socketConn->connectToHost(getHostAddress(), m_port);
     //socketConn.setKeepAlive(true);
  opened = true;

  if (m_port != 0)
  {
   ConnectionStatus::instance()->setConnectionState(
               m_HostName + ":" + QString::number(m_port), ConnectionStatus::CONNECTION_DOWN);
  }
  else
  {
   ConnectionStatus::instance()->setConnectionState(
               m_HostName, ConnectionStatus::CONNECTION_DOWN);
  }
  if (opened && m_port != 0)
  {
   ConnectionStatus::instance()->setConnectionState(
              m_HostName + ":" + m_port, ConnectionStatus::CONNECTION_UP);
  }
  else if (opened)
  {
   ConnectionStatus::instance()->setConnectionState(
              m_HostName, ConnectionStatus::CONNECTION_UP);
  }
 }
#if 1
//     opened = true;
 catch (IOException e) {
     log->error("error opening network connection: " + e.getMessage());
     if (m_port != 0) {
         ConnectionStatus::instance()->setConnectionState(
                 m_HostName + ":" + m_port, ConnectionStatus::CONNECTION_DOWN);
     } else {
         ConnectionStatus::instance()->setConnectionState(
                 m_HostName, ConnectionStatus::CONNECTION_DOWN);
     }
     throw (e);
 }
}
#endif
void AbstractNetworkPortController::on_socketConn_hostFound()
{
  log->debug(tr("host: %1 found").arg(m_HostName));
  //opened = true;
}

void AbstractNetworkPortController::on_socketConn_connected()
{
 opened = true;
 if (opened && m_port != 0)
 {
  ConnectionStatus::instance()->setConnectionState(
             m_HostName + ":" + QString::number(m_port),  ConnectionStatus::CONNECTION_UP);
 }
 else if (opened)
 {
  ConnectionStatus::instance()->setConnectionState(
             m_HostName, ConnectionStatus::CONNECTION_UP);
 }
 if(msg != NULL)
 {
  msg->close();
  msg = NULL;
 }
}

void AbstractNetworkPortController::on_socketConn_error(QAbstractSocket::SocketError e)
{
 if(e == QAbstractSocket::ConnectionRefusedError)
 {
  log->error(m_HostName + ":" + QString::number(m_port) + " error: " + socketConn->errorString() );
  //QMessageBox::critical(NULL, tr("Error"), m_HostName + ":" + QString::number(m_port) + " error: " + socketConn->errorString());
  displayMsg();
 }
 else if(e != QAbstractSocket::SocketTimeoutError)
 {
  log->error(m_HostName + ":" + QString::number(m_port) + " error: " + socketConn->errorString() );
 }
}

void AbstractNetworkPortController::displayMsg()
{
 if(msg != NULL)
  msg->close();
 msg = new QMessageBox(QMessageBox::Critical, tr("Error"),m_HostName + ":" + QString::number(m_port) + " error: " + socketConn->errorString());
 msg->exec();
}

void AbstractNetworkPortController::st_stateChange(QAbstractSocket::SocketState socketState)
{
 log->debug("State change to " + statetoString(socketState) + " at " + QDateTime::currentDateTime().toString("hh:mm:ss dd.MM.yyyy"));
}

void AbstractNetworkPortController::on_socketConn_disconnected()
{
 if (m_port != 0)
 {
  ConnectionStatus::instance()->setConnectionState(
              m_HostName + ":" + QString::number(m_port), ConnectionStatus::CONNECTION_DOWN);
 }
 else
 {
  ConnectionStatus::instance()->setConnectionState(
              m_HostName, ConnectionStatus::CONNECTION_DOWN);
 }
 recover();
}

/**
 * Query the status of this connection. If all OK, at least as far as is
 * known, return true
 *
 * @return true if connection is open
 */
//@Override
/*public*/ bool AbstractNetworkPortController::status() {
    return opened;
}

/**
 * Remember the associated host name
 *
 * @param s
 */
//@Override
/*public*/ void AbstractNetworkPortController::setHostName(QString s)
{
 m_HostName = s;
 if (s==("") && !getMdnsConfigure())
 {
  m_HostName = JmrixConfigPane::NONE;
 }
}

//@Override
/*public*/ QString AbstractNetworkPortController::getHostName()
{
 return m_HostName;
}

/**
 * Remember the associated IP Address This is used internally for mDNS
 * configuration. Public access to the IP address is through the hostname
 * field.
 *
 * @param s
 */
/*protected*/ void AbstractNetworkPortController::setHostAddress(QString s)
{
 m_HostAddress = s;
 if (s==(""))
 {
  m_HostAddress = m_HostName;
 }
}

/*protected*/ QString AbstractNetworkPortController::getHostAddress()
{
 if (m_HostAddress == "")
 {
  return m_HostName;
 }
 return m_HostAddress;
}

/**
 * Remember the associated port number
 *
 * @param p
 *
 */
//@Override
/*public*/ void AbstractNetworkPortController::setPort(int p)
{
 m_port = p;
}

//@Override
/*public*/ void AbstractNetworkPortController::setPort(QString p) {
 m_port = p.toInt();
}

//@Override
/*public*/ int AbstractNetworkPortController::getPort()
{
 return m_port;
}

/**
 * Returns the connection name for the network connection in the format of
 * ip_address:port
 *
 * @return ip_address:port
 *
 */
//@Override
/*public*/ QString AbstractNetworkPortController::getCurrentPortName()
{
 QString t;
 if (getMdnsConfigure())
 {
  t = getHostAddress();
 }
 else
 {
  t = getHostName();
 }
 int p = getPort();
 if ( t!=(""))
 {
  if (p != 0)
  {
   return t + ":" + QString::number(p);
  }
  return t;
 }
 else
 {
  return JmrixConfigPane::NONE;
 }
}

/*
 * Set whether or not this adapter should be
 * configured automatically via MDNS.
 * Note: Default implementation ignores the parameter.
 * @param autoconfig boolean value.
 */
//@Override
/*public*/ void AbstractNetworkPortController::setMdnsConfigure(bool autoconfig) {
}

/*
 * Get whether or not this adapter is configured
 * to use autoconfiguration via MDNS
 * Default implemntation always returns false.
 * @return true if configured using MDNS.
 */
//@Override
/*public*/ bool AbstractNetworkPortController::getMdnsConfigure() {
    return false;
}
/*
 * set the server's host name and port
 * using mdns autoconfiguration.
 * Default implementation does nothing.
 */
//@Override
/*public*/ void AbstractNetworkPortController::autoConfigure() {
}

/*
 * Get and set the ZeroConf/mDNS advertisement name.
 * Default implementation does nothing.
 */
//@Override
/*public*/ void AbstractNetworkPortController::setAdvertisementName(QString AdName) {
}

//@Override
/*public*/ QString AbstractNetworkPortController::getAdvertisementName() {
 return "";
}

/*
 * Get and set the ZeroConf/mDNS service type.
 * Default implementation does nothing.
 */
//@Override
/*public*/ void AbstractNetworkPortController::setServiceType(QString ServiceType) {
}

//@Override
/*public*/ QString AbstractNetworkPortController::getServiceType() {
 return "";
}

//@Override
/*public*/ QDataStream* AbstractNetworkPortController::getInputStream()
{
 if (!opened)
 {
  log->error("AbstractNetworkPortController::getInputStream called before load(), stream not available");
  if (m_port != 0)
  {
   ConnectionStatus::instance()->setConnectionState(
              m_HostName + ":" + m_port, ConnectionStatus::CONNECTION_DOWN);
  }
  else
  {
   ConnectionStatus::instance()->setConnectionState(
              m_HostName, ConnectionStatus::CONNECTION_DOWN);
  }
 }
 bool connected = socketConn->waitForConnected();
 //try {
      //return new DataInputStream(socketConn.getInputStream());
 if(connected)
  return new QDataStream(socketConn);
 else
//    } catch (java.io.IOException ex1)
 {
     log->error("Exception getting input stream: " + socketConn->errorString());
     return nullptr;
 }
}

//@Override
/*public*/ QDataStream* AbstractNetworkPortController::getOutputStream()
{
 if (!opened)
 {
  log->error("AbstractNetworkPortController::getOutputStream called before load(), stream not available");
 }
//    try {
        //return new DataOutputStream(socketConn.getOutputStream());
 return new QDataStream(socketConn);
//    } catch (java.io.IOException e) {
//        log->error("getOutputStream exception: " + e);
//        if (m_port != 0) {
//            ConnectionStatus.instance().setConnectionState(
//                    m_HostName + ":" + m_port, ConnectionStatus.CONNECTION_DOWN);
//        } else {
//            ConnectionStatus.instance().setConnectionState(
//                    m_HostName, ConnectionStatus.CONNECTION_DOWN);
//        }
//    }
//    return null;
}

//@Override
/*public*/ void AbstractNetworkPortController::dispose() {
    AbstractPortController::dispose();
}

///*private*/ boolean allowConnectionRecovery = false;
/**
 * This is called when a connection is initially lost. It closes the client
 * side socket connection, resets the open flag and attempts a reconnection.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value = "DE_MIGHT_IGNORE",
//        justification = "we are trying to close a failed connection, it doesn't matter if it generates an error")
//@Override
/*public*/ void AbstractNetworkPortController::recover()
{
 if (!allowConnectionRecovery)
 {
  log->warn("No automatic recovery allowed!");

  return;
 }
 opened = false;

 try
 {
  socketConn->close();
 }
 catch (IOException e) { }
 reconnect();
}

/**
 * Attempts to reconnect to a failed Server
 */
/*public*/ void AbstractNetworkPortController::reconnect()
{
 // If the connection is already open, then we shouldn't try a re-connect.
 if (opened && !allowConnectionRecovery)
 {
  return;
 }

 Reconnectwait* reconnectWait = new Reconnectwait(this);
 reconnectWait->setObjectName("Reconnectwait ");

 //_connect();

 if(!socketConn->waitForConnected())
 {
  log->debug("timed out waiting for reconnect");
 }

// thread->start();

// try {
////        thread->join();
//  thread->wait();
// }
// catch (InterruptedException e)
// {
//  log->error("Unable to join to the reconnection thread");
// }

// if (!opened)
// {
//  log->error("Failed to re-establish connectivity");
// }
// else
// {
//  resetupConnection();
//  log->info("Reconnected to " + getHostName());
// }
}

/**
 * Customizable method to deal with resetting a system connection after a
 * sucessful recovery of a connection.
 */
/*protected*/ void AbstractNetworkPortController::resetupConnection()
{

}

//class reconnectwait extends Thread {

/*public*/ /*final static*/ int Reconnectwait::THREADPASS = 0;
/*public*/ /*final static*/ int Reconnectwait::THREADFAIL = 1;
//    int _status;

/*public*/ int Reconnectwait::status() {
    return _status;
}

/*public*/ Reconnectwait::Reconnectwait(AbstractNetworkPortController* self) {
 _status = THREADFAIL;
 this->self = self;
 count = 0;
 secondCount = 0;
 reconnectinterval = self->reconnectinterval;
 timer = new QTimer;
 connect(timer, SIGNAL(timeout()), this, SLOT(checkSocket()));
 timer->start(reconnectinterval);
 bFirstTime = true;
}

void Reconnectwait::checkSocket() // [slot]
{
 if(bFirstTime)
 {
  bFirstTime = false;
  self->socketConn->close();
  self->_connect();
 }
// while (reply)
// {
//  AbstractPortController::safeSleep(reconnectinterval, "Waiting");
  count++;
//  try
//  {
//   // if the device allows autoConfiguration,
//   // we need to run the autoConfigure() call
//   // before we try to reconnect.
//   if (self->getMdnsConfigure())
//   {
//    AbstractNetworkPortController* selfautoConfigure();
//   }
//   //self->_connect();
//   //emit _connect();
//  }
//  catch (Exception e)
//  {
//  }

  //self->socketConn->waitForConnected();
  QAbstractSocket::SocketState s = self->socketConn->state();
  QString state;
  switch(s)
  {
  case QAbstractSocket::UnconnectedState:
   state = "unconnected";
   break;
  case QAbstractSocket::HostLookupState:
   state = "hostlookingup";
   break;
  case QAbstractSocket::ConnectingState:
   state = "connecting";
   break;
  case QAbstractSocket::ConnectedState:
   state = "connected";
   break;
  case QAbstractSocket::ClosingState:
   state = "closing";
   break;
  case QAbstractSocket::ListeningState:
   state = "listening";
   break;
  default:
   state = "unknown";
   break;
  }
  self->log->debug("socket state = " + state);

  if(self->socketConn->state() == QAbstractSocket::ConnectedState)
  {
   self->log->debug("socket now connected");
   self->opened = true;
   timer->stop();
   disconnect(timer, SIGNAL(timeout()), this, SLOT(checkSocket()));
   return;
  }
  reply = !self->opened;
  if (count >= self->retryAttempts)
  {
   self->log->error("Unable to reconnect after " + QString::number(count) + " Attempts, increasing duration of retries");
   //retrying but with twice the retry interval.
   reconnectinterval = reconnectinterval * 2;
   count = 0;
   secondCount++;
   self->socketConn->abort();
   self->_connect();
  }
  if (secondCount >= 10)
  {
   self->log->error("Giving up on reconnecting after 100 attempts");
   reply = false;
   disconnect(timer,SIGNAL(timeout()), this, SLOT(checkSocket()));
   timer->stop();
   return;
  }
  timer->start(reconnectinterval);
// }  // end of wait loop
}
//};

QString AbstractNetworkPortController::statetoString(QAbstractSocket::SocketState socketState)
{
    QString statestring;
    switch(socketState)
    {
        case QAbstractSocket::UnconnectedState : statestring="the socket is not connected";
            break;
        case QAbstractSocket::HostLookupState : statestring="the socket is performing a host name lookup";
            break;
        case QAbstractSocket::ConnectingState : statestring="the socket has started establishing a connection";
            break;
        case QAbstractSocket::ConnectedState : statestring="a connection is established";
            break;
        case QAbstractSocket::BoundState : statestring="the socket is bound to an address and port";
            break;
        case QAbstractSocket::ClosingState : statestring="the socket is about to close";
            break;
        case QAbstractSocket::ListeningState : statestring="listening state";
            break;
        default: statestring="unknown state";
    }
    return statestring;
}
/*
 * Set the connection timeout to the specified value.
 * If the socket is not null, set the SO_TIMEOUT option on the
 * socket as well.
 * @param t timeout value in milliseconds.
 */
/*protected*/ void AbstractNetworkPortController::setConnectionTimeout(int t) {
    connTimeout = t;
#if 0
    try {
        if (socketConn != nullptr) {
            socketConn->s->setSoTimeout(getConnectionTimeout());
        }
    } catch (SocketException se) {
        log->debug("Unable to set socket timeout option on socket");
    }
#endif
}

/*
 * Get the connection timeout value.
 * @return timeout value in milliseconds.
 */
/*protected*/ int AbstractNetworkPortController::getConnectionTimeout() {
    return connTimeout;
}

