#include "locobufferadapter.h"
#include "lnpacketizer.h"
#include "slotmanager.h"
#include "connectionstatus.h"

/**
 * Provide access to LocoNet via a LocoBuffer attached to a serial comm port.
 * <P>
 * Normally controlled by the LocoBufferFrame class.
 * @author			Bob Jacobsen   Copyright (C) 2001, 2008, 2010
 * @version			$Revision: 21225 $
 */
//public class LocoBufferAdapter extends LnPortController implements jmri.jmrix.SerialPortAdapter {


//LocoBufferAdapter::LocoBufferAdapter(QObject *parent)  : LnPortController(parent)
//{
// common();
// adaptermemo = new LocoNetSystemConnectionMemo();
//}
LocoBufferAdapter::LocoBufferAdapter(LocoNetSystemConnectionMemo* memo, QObject *parent)  : LnPortController(memo, parent)
{
 common();
 adaptermemo = memo;
}
void LocoBufferAdapter::common()
{
    //super();
 log = new Logger(this->objectName(), this);
 opened = false;
 serialStream = NULL;
 option1Name = "FlowControl";
 option2Name = "CommandStation";
 option3Name = "TurnoutHandle";
 validOption1  <<"hardware flow control (recommended)"<< "no flow control";
 validSpeeds <<"19,200 baud (J1 on 1&2)"<< "57,600 baud (J1 on 2&3)";
 validSpeedValues<<19200<<57600;
 options.insert(option1Name,  new Option("Connection uses:", validOption1));
 options.insert(option2Name,  new Option("Command station type:", commandStationNames, false));
 QStringList list;
 list <<"Normal"<< "Spread"<< "One Only"<< "Both";
 options.insert(option3Name,  new Option("Turnout command handling:", list));
 //adaptermemo = new LocoNetSystemConnectionMemo();
 portNameVector.clear();
 activeSerialPort = NULL;
 packets = NULL;
}


// @SuppressWarnings("unchecked")
/*public*/ QVector<QString> LocoBufferAdapter::getPortNames()
{
 // first, check that the comm package can be opened and ports seen
 portNameVector.clear();
// Enumeration<CommPortIdentifier> portIDs = CommPortIdentifier.getPortIdentifiers();
// // find the names of suitable ports
// while (portIDs.hasMoreElements()) {
//        CommPortIdentifier id = portIDs.nextElement();
//        // filter out line printers
//        if (id.getPortType() != CommPortIdentifier.PORT_PARALLEL )
//            // accumulate the names in a vector
//            portNameVector.addElement(id.getName());
// }
 foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
     portNameVector <<info.portName();
 return portNameVector;
}

/*public*/ QString LocoBufferAdapter::openPort(QString portName, QString appName) throw(NoSuchPortException)
{
 Q_UNUSED(appName)
    // open the primary and secondary ports in LocoNet mode, check ability to set moderators
//    try {
//        // get and open the primary port
//        CommPortIdentifier portID = CommPortIdentifier.getPortIdentifier(portName);
//        try {
//            //activeSerialPort = (SerialPort) portID.open(appName, 2000);  // name of program, msec to wait
//            if(!activeSerialPort->serial.open(QIODevice::ReadWrite)
//        }
//        catch (PortInUseException p) {
//            return handlePortBusy(p, portName, log);
//        }
//        // try to set it for LocoNet via LocoBuffer
//        try {
//            setSerialPort(activeSerialPort);
//        } catch (UnsupportedCommOperationException e) {
//            log->error("Cannot set serial parameters on port "+portName+": "+e.getMessage());
//            return "Cannot set serial parameters on port "+portName+": "+e.getMessage();
//        }

//        // set timeout
//        try {
//            activeSerialPort.enableReceiveTimeout(10);
//            log->debug("Serial timeout was observed as: "+activeSerialPort.getReceiveTimeout()
//                  +" "+activeSerialPort.isReceiveTimeoutEnabled());
//        } catch (Exception et) {
//            log->info("failed to set serial timeout: "+et);
//        }

//        // get and save stream
//        serialStream = activeSerialPort.getInputStream();

//        // purge contents, if any
//        int count = serialStream.available();
//        log->debug("input stream shows "+count+" bytes available");
//        while ( count > 0) {
//            serialStream.skip(count);
//            count = serialStream.available();
//        }

//        // report status?
//        if (log->isInfoEnabled()) {
//            // report now
//            log->info(portName+" port opened at "
//                     +activeSerialPort.getBaudRate()+" baud with"
//                     +" DTR: "+activeSerialPort.isDTR()
//                     +" RTS: "+activeSerialPort.isRTS()
//                     +" DSR: "+activeSerialPort.isDSR()
//                     +" CTS: "+activeSerialPort.isCTS()
//                     +"  CD: "+activeSerialPort.isCD()
//                     );
//        }
//        if (log->isDebugEnabled()) {
//            // report additional status
//            log->debug(" port flow control shows "+
//                      (activeSerialPort.getFlowControlMode()==SerialPort.FLOWCONTROL_RTSCTS_OUT?"hardware flow control":"no flow control"));
//        }
//        if (log->isDebugEnabled()) {
//            // arrange to notify later
//            activeSerialPort.addEventListener(new SerialPortEventListener(){
//                    public void serialEvent(SerialPortEvent e) {
//                        int type = e.getEventType();
//                        switch (type) {
//                        case SerialPortEvent.DATA_AVAILABLE:
//                            log->info("SerialEvent: DATA_AVAILABLE is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
//                            log->info("SerialEvent: OUTPUT_BUFFER_EMPTY is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.CTS:
//                            log->info("SerialEvent: CTS is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.DSR:
//                            log->info("SerialEvent: DSR is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.RI:
//                            log->info("SerialEvent: RI is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.CD:
//                            log->info("SerialEvent: CD is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.OE:
//                            log->info("SerialEvent: OE (overrun error) is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.PE:
//                            log->info("SerialEvent: PE (parity error) is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.FE:
//                            log->info("SerialEvent: FE (framing error) is "+e.getNewValue());
//                            return;
//                        case SerialPortEvent.BI:
//                            log->info("SerialEvent: BI (break interrupt) is "+e.getNewValue());
//                            return;
//                        default:
//                            log->info("SerialEvent of unknown type: "+type+" value: "+e.getNewValue());
//                            return;
//                        }
//                    }
//                }
//                                              );
//            try { activeSerialPort.notifyOnFramingError(true); }
//            catch (Exception e) { log->debug("Could not notifyOnFramingError: "+e); }

//            try { activeSerialPort.notifyOnBreakInterrupt(true); }
//            catch (Exception e) { log->debug("Could not notifyOnBreakInterrupt: "+e); }

//            try { activeSerialPort.notifyOnParityError(true); }
//            catch (Exception e) { log->debug("Could not notifyOnParityError: "+e); }

//            try { activeSerialPort.notifyOnOverrunError(true); }
//            catch (Exception e) { log->debug("Could not notifyOnOverrunError: "+e); }

//        }

//        opened = true;

//    } catch (NoSuchPortException p) {
//        return handlePortNotFound(p, portName, log);
//    } catch (Exception ex) {
//        log->error("Unexpected exception while opening port "+portName+" trace follows: "+ex);
//        ex.printStackTrace();
//        return "Unexpected error while opening port "+portName+": "+ex;
//    }
 activeSerialPort = new SerialPort;
#ifdef USE_THREAD
// if(portName == "")
// {
//  QList<QSerialPortInfo> list =QSerialPortInfo::availablePorts();
//  if(list.count() > 0)
//   portName = list.at(0).portName();
//  else
//   return false;
// }
 getCurrentBaudRate();
 if(!activeSerialPort->open(portName, QIODevice::ReadWrite))
 {
  log->error(tr("error opening port %1 error: %2").arg(portName).arg(activeSerialPort->errorString()));
  return tr("error opening port %1 error: %2").arg(portName).arg(activeSerialPort->errorString());
 }
 opened = true;

//((LocoNetSystemConnectionMemo*)adaptermemo)->configureManagers();

#else
 activeSerialPort->setPortName(portName);
 if(!activeSerialPort->open(QIODevice::ReadWrite))
 {
  log->error(tr("Can't open serial port %1, error %2").arg(portName).arg(activeSerialPort->errorString()));

  emit error(tr("Can't open serial port %1, error %2").arg(portName).arg(activeSerialPort->errorString()));
//     throw new NoSuchPortException(tr("Can't open %1, error code %2").arg(portName).arg(activeSerialPort->serial.error()));
  return false;
 }
#endif
 ConnectionStatus::instance()->setConnectionState(portName, ConnectionStatus::CONNECTION_UP);

 activeSerialPort->clear(); // clear out any data in serial port buffers.

 // try to set it for LocoNet via LocoBuffer
 try
 {
  //if (!opened)
   setSerialPort(activeSerialPort);
 }
 catch (UnsupportedCommOperationException e)
 {
  log->error("Cannot set serial parameters on port "+portName+": "+e.getMessage());
  emit error( "Cannot set serial parameters on port "+portName+": "+e.getMessage());
  return "";
 }
//    // set timeout
//    try {
//        activeSerialPort->serial.enableReceiveTimeout(10);
//        log->debug("Serial timeout was observed as: "+activeSerialPort.getReceiveTimeout()
//              +" "+activeSerialPort.isReceiveTimeoutEnabled());
//    } catch (Exception et) {
//        log->info("failed to set serial timeout: "+et);
//    }

    // get and save stream
  serialStream = activeSerialPort->getInputStream();

    // purge contents, if any
 activeSerialPort->flush();

 // report status?
 if (log->isInfoEnabled())
 {
  // report now
  log->info(portName+" port opened at "
                 +QString::number(activeSerialPort->baudRate())+" baud with "
                 + activeSerialPort->parity() + " parity"
                 + ", DataBits: " + QString::number(activeSerialPort->databits())
                 + ", StopBits: " + activeSerialPort->stopBits()
                 +", DTR: "+(activeSerialPort->isDTR()?"true":"false")
                 +", RTS: "+(activeSerialPort->isRTS()?"true":"false")
                 +", DSR: "+(activeSerialPort->isDSR()?"true":"false")
                 +", CTS: "+(activeSerialPort->isCTS()?"true":"false")
                 +",  CD: "+(activeSerialPort->isCD()?"true":"false")
                 + ", Flow control: " +activeSerialPort->flowControl()
                 );
 }
 if (log->isDebugEnabled())
 {
  // report additional status
  log->debug(" port flow control shows "+ activeSerialPort->flowControl() );
 }
 opened = true;
 return ""; // normal operation
}

/**
 * Can the port accept additional characters?
 * The state of CTS determines this, as there seems to
 * be no way to check the number of queued bytes and buffer length.
 * This might
 * go false for short intervals, but it might also stick
 * off if something goes wrong.
 */
/*public*/ bool LocoBufferAdapter::okToSend()
{
 return activeSerialPort->isCTS();
}

/**
 * Set up all of the other objects to operate with a LocoBuffer
 * connected to this port.
 */
/*public*/ void LocoBufferAdapter::configure()
{

 // setCommandStationType(getOptionState(option2Name));
 setTurnoutHandling(getOptionState(option3Name));
 // connect to a packetizing traffic controller
//    LnPacketizer* packets = new LnPacketizer();
 packets = new LnPacketizer();
 packets->connectPort((LnPortController*)this);
 //packets->setSerial(&activeSerialPort->serial);

 // create memo
 ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
 // do the common manager config

 ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
                                                mTurnoutNoRetry, mTurnoutExtraSpace);
 ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers();

 // start operation
 //packets->startThreads();
 ActiveFlag::setActive();
}

// base class methods for the LnPortController interface
/*public*/ QDataStream* LocoBufferAdapter::getInputStream()
{
 if (!opened)
 {
  log->error("LocoBufferAdapter::getInputStream called before load(), stream not available");
  //return NULL;
 }
 //return new QDataStream();
 return activeSerialPort->getInputStream();
 }

/*public*/ QDataStream* LocoBufferAdapter::getOutputStream()
{
 if (!opened) log->error("LocoBufferAdapter::getOutputStream called before load(), stream not available");
 try
 {
  //return new  DataOutputStream(activeSerialPort.getOutputStream());
  return activeSerialPort->getOutputStream();
 }
 catch (IOException e)
 {
  log->error("getOutputStream exception: "+e.getMessage());
 }
 return activeSerialPort->getOutputStream();
}
QSerialPort* LocoBufferAdapter::getSerialPort()
{
 return activeSerialPort->getSerialPort();
}

/*public*/ bool LocoBufferAdapter::status() {return opened;}

/**
 * Local method to do specific configuration, overridden in class
 */
/*protected*/ void LocoBufferAdapter::setSerialPort(SerialPort* activeSerialPort) throw(UnsupportedCommOperationException)
{
 // find the baud rate value, configure comm options

 int baud = currentBaudNumber(mBaudRate);
 Q_UNUSED(baud);
 activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS8,
                                         SerialPort::STOPBITS_1, SerialPort::PARITYNONE);

 // set RTS high, DTR high - done early, so flow control can be configured after
 activeSerialPort->setRTS(true);		// not connected in some serial ports and adapters
 activeSerialPort->setDTR(true);		// pin 1 in Mac DIN8; on main connector, this is DTR

 // find and configure flow control
 int flow = SerialPort::FLOWCONTROL_RTSCTS_OUT; // default, but also defaults in selectedOption1
 if (getOptionState(option1Name)==(validOption1[1]))
  flow = SerialPort::FLOWCONTROL_NONE;
 activeSerialPort->setFlowControlMode(flow);
 log->debug("Found flow control "+QString::number(activeSerialPort->getFlowControlMode())
            +" RTSCTS_OUT="+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_OUT)
            +" RTSCTS_IN= "+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_IN));
}

/**
 * Get an array of valid baud rates as strings. This allows subclasses
 * to change the arrays of speeds.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
/*public*/ QStringList LocoBufferAdapter::validBaudRates() {
    return validSpeeds;
}

/**
 * Get an array of valid baud rates as integers. This allows subclasses
 * to change the arrays of speeds.
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK to expose array instead of copy until Java 1.6
/*public*/ QVector<int> LocoBufferAdapter::validBaudNumber()
{
 return validSpeedValues;
}

/*public*/ void LocoBufferAdapter::dispose()
{
 if (adaptermemo!=NULL)
  adaptermemo->dispose();
 adaptermemo = NULL;
}
    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoBufferAdapter.class.getName());
LnPacketizer* LocoBufferAdapter::packetizer()
{
 return packets;
}
void LocoBufferAdapter::sendLocoNetMessage(LocoNetMessage* m)
{
 packets->sendLocoNetMessage(m);
}
