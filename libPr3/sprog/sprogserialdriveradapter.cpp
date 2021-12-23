#include "sprogserialdriveradapter.h"
#include "loggerfactory.h"
#include "sprogtrafficcontroller.h"
#include "systemconnectionmemo.h"
#include "powermanager.h"
#include <QDataStream>
#include "sprogprogrammermanager.h"
#include "sprogpowermanager.h"
#include "connectionstatus.h"
#include "joptionpane.h"
#include <QApplication>

using namespace Sprog;

/**
 * Implements SerialPortAdapter for the Sprog system.
 * <p>
 * This connects an Sprog command station via a serial com port. Also used for
 * the USB SPROG, which appears to the computer as a serial port.
 * <p>
 * The current implementation only handles the 9,600 baud rate, and does not use
 * any other options at configuration time.
 *
 * Updated January 2010 for gnu io (RXTX) - Andrew Berridge.
 *
 * @author Bob Jacobsen Copyright (C) 2001, 2002
 */
///*public*/ class SerialDriverAdapter extends SprogPortController implements jmri.jmrix.SerialPortAdapter {

/*public*/ SprogSerialDriverAdapter::SprogSerialDriverAdapter(QObject* parent)
 : SprogPortController(new SprogSystemConnectionMemo(SprogConstants::SprogMode::SERVICE),parent)
{
 //super(new SprogSystemConnectionMemo(SprogMode.SERVICE));
 // Set the username to match name, once refactored to handle multiple connections or user setable names/prefixes then this can be removed
 common();
 this->baudRate = 9600;
 this->getSystemConnectionMemo()->setUserName(tr("SPROG Programmer"));
 // create the traffic controller
 ((SprogSystemConnectionMemo*)this->getSystemConnectionMemo())->setSprogTrafficController(new SprogTrafficController(this->getSystemConnectionMemo()));
}

/*public*/ SprogSerialDriverAdapter::SprogSerialDriverAdapter(SprogConstants::SprogMode sm, QObject* parent)
 : SprogPortController(new SprogSystemConnectionMemo(sm), parent)
{
 //super(new SprogSystemConnectionMemo(sm));
 common();
 this->baudRate = 9600;
 this->getSystemConnectionMemo()->setUserName("SPROG");
 // create the traffic controller
 ((SprogSystemConnectionMemo*)this->getSystemConnectionMemo())->setSprogTrafficController(new SprogTrafficController(this->getSystemConnectionMemo()));
}

/*public*/ SprogSerialDriverAdapter::SprogSerialDriverAdapter(SprogConstants::SprogMode sm, int baud, SprogType* type, QObject* parent) : SprogPortController(new SprogSystemConnectionMemo(sm, type), parent)
{
 //super(new SprogSystemConnectionMemo(sm, type));
 common();
 this->baudRate = baud;
 this->getSystemConnectionMemo()->setUserName("SPROG");
 // create the traffic controller
 ((SprogSystemConnectionMemo*)this->getSystemConnectionMemo())->setSprogTrafficController(new SprogTrafficController(this->getSystemConnectionMemo()));
}

/*public*/ SprogSerialDriverAdapter::SprogSerialDriverAdapter(SprogConstants::SprogMode sm, int baud, QObject* parent)  : SprogPortController(new SprogSystemConnectionMemo(sm), parent)
{
 //super(new SprogSystemConnectionMemo(sm));
 common();
 this->baudRate = baud;
 this->getSystemConnectionMemo()->setUserName("SPROG");
 // create the traffic controller
 ((SprogSystemConnectionMemo*)this->getSystemConnectionMemo())->setSprogTrafficController(new SprogTrafficController(this->getSystemConnectionMemo()));
}

void SprogSerialDriverAdapter::common()
{
 activeSerialPort = NULL;
 baudRate = -1;
 serialStream = NULL;
 setManufacturer("SPROG DCC");
}

//@Override
/*public*/ QString SprogSerialDriverAdapter::openPort(QString portName, QString appName)
{
 // open the port, check ability to set moderators
 try {
  QSerialPortInfo inf = QSerialPortInfo(portName);
  log->info(inf.isBusy()?"busy":"not busy");
  // get and open the primary port
  //CommPortIdentifier portID = CommPortIdentifier.getPortIdentifier(portName);
  try
  {
   //activeSerialPort = (SerialPort) portID.open(appName, 2000);  // name of program, msec to wait
   if(inf.isBusy()) throw PortInUseException(portName);
   log->info(tr("Manufacturer %1, Vendor id: %2 : Product id: %3").arg(inf.manufacturer()).arg(inf.vendorIdentifier(),0,16).arg(inf.productIdentifier(),0,16));
  }
  catch (PortInUseException p) {
      return handlePortBusy(p, portName, log);
  }

 // get and open the primary port
     activeSerialPort = new QSerialPort(this);//SerialPort();

     // try to set it for comunication via SerialDriver
#if 0
     try {
         activeSerialPort->setSerialPortParams(baudRate, SerialPort::DATABITS_8, SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);
     } catch (UnsupportedCommOperationException* e) {
         log->error(tr("Cannot set serial parameters on port %1: %2").arg(portName).arg(e.getMessage()));
         return "Cannot set serial parameters on port " + portName + ": " + e.getMessage();
     }
     activeSerialPort->setFlowControlMode(SerialPort::FLOWCONTROL_NONE);
#else
     activeSerialPort->setPortName(portName);
     activeSerialPort->setBaudRate(baudRate, QSerialPort::AllDirections);
     activeSerialPort->setDataBits(QSerialPort::Data8);
     activeSerialPort->setParity(QSerialPort::NoParity);
     activeSerialPort->setStopBits(QSerialPort::OneStop);
     activeSerialPort->setFlowControl(QSerialPort::NoFlowControl);
#endif
     if(!activeSerialPort->open(QIODevice::ReadWrite))
     {
      log->error(tr("error opening comm port '%1': %2").arg(portName).arg(activeSerialPort->errorString()));
      if(activeSerialPort->error() == QSerialPort::SerialPortError::DeviceNotFoundError)
       throw NoSuchPortException(portName);
      if(activeSerialPort->error() == QSerialPort::PermissionError)
       throw PortInUseException();
      return activeSerialPort->errorString();
     }

     // set RTS high, DTR high
     // activeSerialPort->setRTS(true);		// not connected in some serial ports and adapters
#if 1
     if(!activeSerialPort->setRequestToSend(true))
     {
       return (tr("Can't set RTS to port %1, error code %2")
                       .arg(activeSerialPort->portName()).arg(activeSerialPort->errorString()));
     }
     //activeSerialPort->setDTR(true);		// pin 1 in DIN8; on main connector, this is DTR
     if(!activeSerialPort->setDataTerminalReady(true))
     {
      return (tr("Can't set DTR to port %1, error code %2")
                   .arg(activeSerialPort->portName()).arg(activeSerialPort->errorString()));
     }
#endif
     // disable flow control; hardware lines used for signaling, XON/XOFF might appear in data
     //AJB: Removed Jan 2010 -
     //Setting flow control mode to zero kills comms - SPROG doesn't send data
     //Concern is that will disabling this affect other SPROGs? Serial ones?
     //activeSerialPort.setFlowControlMode(0);

     // set timeout
     // activeSerialPort.enableReceiveTimeout(1000);

//     log->debug(tr("Serial timeout was observed as: %1 %2").arg(activeSerialPort->getReceiveTimeout()).arg((activeSerialPort->isReceiveTimeoutEnabled()?"true":"false")));

     // get and save stream
     serialStream = new QDataStream(activeSerialPort);//activeSerialPort->getInputStream();
     log->debug(tr("stream status: %1, %2 bytes available").arg(serialStream->status()).arg(activeSerialPort->bytesAvailable()));

     // purge contents, if any
     //purgeStream(serialStream); // note: SerialPort does a clear() after opening the port.
     activeSerialPort->clear();

     // report status?
     if (log->isInfoEnabled())
     {
      QString dataBits = QString::number(activeSerialPort->dataBits());
      QString stopBits = this->stopBits();
      QString parity = this->parity();
      QString flowControl = this->flowControl();

         log->info(portName + " port opened at "
                 + QString::number(activeSerialPort->baudRate()) + " baud, sees "
                 + QString(" DTR: ") + (activeSerialPort->isDataTerminalReady()?"true":"false")
                 + QString(", RTS: ") + (activeSerialPort->isRequestToSend()?"true":"false")
                 + QString(", DSR: ") + (activeSerialPort->pinoutSignals()&QSerialPort::DataSetReadySignal?"true":"false")
                 + QString(", CTS: ") + (activeSerialPort->pinoutSignals()&QSerialPort::ClearToSendSignal?"true":"false")
                 + QString(",  CD: ") + (activeSerialPort->pinoutSignals()&QSerialPort::DataCarrierDetectSignal?"true":"false")
                   + ", databits: " +dataBits + ", parity: " + parity + ", stop bits: " + stopBits + ", flow control: " + flowControl
                   );
     }
#if 0
     //add Sprog Traffic Controller as event listener
     try {
         activeSerialPort.addEventListener(this->getSystemConnectionMemo().getSprogTrafficController());
     } catch (TooManyListenersException e) {
     }

     // AJB - activate the DATA_AVAILABLE notifier
     activeSerialPort.notifyOnDataAvailable(true);
#endif
     connect(activeSerialPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
     connect(activeSerialPort, SIGNAL(readyRead()), this->getSystemConnectionMemo()->getSprogTrafficController(), SLOT(handleOneIncomingReply()));
     connect(activeSerialPort, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
     opened = true;
     mBaudRate = QString::number(activeSerialPort->baudRate());
     ConnectionStatus::instance()->setConnectionState(NULL, portName, ConnectionStatus::CONNECTION_UP); // Added ACK
 }
 catch (NoSuchPortException p)
 {
  return handlePortNotFound(p, portName, log);
 }
 catch (IOException* ex) {
     log->error(tr("Unexpected exception while opening port %1").arg(portName), ex);
     return "Unexpected error while opening port " + portName + ": " + ex->getMessage();
 }
 return ""; // indicates OK return

}

void SprogSerialDriverAdapter::bytesWritten(qint64 bytes)
{
 log->info(tr("serial port reports %1 bytes written").arg(bytes));
}

/*public*/ void SprogSerialDriverAdapter::setHandshake(QSerialPort::FlowControl mode) {
    try {
        activeSerialPort->setFlowControl(mode);
    } catch (UnsupportedCommOperationException* ex) {
        log->error("Unexpected exception while setting COM port handshake mode,", ex);
    }
}

// base class methods for the SprogPortController interface
//@Override
/*public*/ QDataStream* SprogSerialDriverAdapter::getInputStream() {
    if (!opened) {
        log->error("getInputStream called before load(), stream not available");
        return NULL;
    }
    //return serialStream;//new QDataStream(serialStream);
    return new QDataStream(activeSerialPort);
}

//@Override
/*public*/ QDataStream* SprogSerialDriverAdapter::getOutputStream() {
    if (!opened) {
        log->error("getOutputStream called before load(), stream not available");
    }
    try {
        return new QDataStream(activeSerialPort);
     //return serialStream; //activeSerialPort->getOutputStream();
    } catch (IOException e) {
        log->error("getOutputStream exception: " + e.getMessage());
    }
    return NULL;
}

/**
 * Get an array of valid baud rates. This is currently only 9,600 bps
 */
//@Override
/*public*/ QStringList validBaudRates() {
    return QStringList() <<"9,600 bps";
}


/**
 * @deprecated JMRI Since 4.4 instance() shouldn't be used, convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ SprogSerialDriverAdapter* SprogSerialDriverAdapter::instance() {
    return NULL;
}

/**
 * Set up all of the other objects to operate with an Sprog command station
 * connected to this port.
 */
//@Override
/*public*/ void SprogSerialDriverAdapter::configure()
{
 // connect to the traffic controller
 this->getSystemConnectionMemo()->getSprogTrafficController()->connectPort(this);

 this->getSystemConnectionMemo()->configureCommandStation();
 this->getSystemConnectionMemo()->configureManagers();

 if (getOptionState("TrackPowerState") != NULL && getOptionState("TrackPowerState")==(tr("PowerStateOn")))
 {
  try
  {
      this->getSystemConnectionMemo()->getPowerManager()->setPower(PowerManager::ON);
  } catch (JmriException* e) {
      log->error(e->toString());
  }
 }
}

//@Override
/*public*/ void SprogSerialDriverAdapter::dispose() {
    SprogPortController::dispose();
}

/*public*/void  SprogSerialDriverAdapter::handleError(QSerialPort::SerialPortError error)
{
 JOptionPane::showMessageDialog(NULL, tr("Comm error: %1 %2").arg(error).arg(activeSerialPort->errorString()));
}
QString SprogSerialDriverAdapter::stopBits()
{
 int sb = activeSerialPort->stopBits();
 switch(sb)
 {
  case QSerialPort::OneStop:
   return "One";
  case QSerialPort::OneAndHalfStop:
   return "One and half";
 case QSerialPort::TwoStop:
   return "Two";
 default:
   return "Unknown";
 }
}
QString SprogSerialDriverAdapter::parity()
{
 int p = activeSerialPort->parity();
 switch (p)
 {
  case QSerialPort::EvenParity:
   return "Even";
  case QSerialPort::OddParity:
   return "Odd";
  case QSerialPort::NoParity:
   return "No Parity";
  default:
   break;
 }
 return "unknown";
}
QString SprogSerialDriverAdapter::flowControl()
{
 int f = activeSerialPort->flowControl();
 switch(f)
 {
 case QSerialPort::NoFlowControl:
  return "No Flow Control";
 case QSerialPort::HardwareControl:
  return "Hardware Flow Control";
 case QSerialPort::SoftwareControl:
  return "Software flow control";
 case QSerialPort::UnknownFlowControl:
 default:
  return "Unknown flow control";
 }
}

void SprogSerialDriverAdapter::writeData(QByteArray bytes)
{
 try
 {
  int bytesWritten = serialStream->writeRawData(bytes.constData(), bytes.length());
  if(bytesWritten!=bytes.length()) throw Exception(tr("%1 bytes not written").arg(bytes.length()));

    log->debug(tr("sendSprogMessage %1 bytes written to ostream").arg(bytesWritten));

  }
  catch (Exception e)
 {
  log->warn("sendMessage: Exception: " + e.getMessage());
 }
}

/*public*/ QString SprogSerialDriverAdapter::className()
{
 return "jmri.jmrix.sprog.serialdriver.SerialDriverAdapter";
}


/*private*/ /*final*/ /*static*/ Logger* SprogSerialDriverAdapter::log = LoggerFactory::getLogger("SerialDriverAdapter");
