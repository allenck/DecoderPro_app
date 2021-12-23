#include "abstractserialportcontroller.h"
#include <QThread>
#include <QtSerialPort/QSerialPortInfo>
#include "instancemanager.h"
#include "joptionpane.h"
#include "connectionstatus.h"
#include "serialport.h"

Option::Option()
{
 displayText="";
 options.clear();
 advancedOption=false;
}

Option::Option(QString displayText, QStringList options, bool advanced)
{
 //this(displayText, options);
 this->displayText = displayText;
 this->options = options;
 advancedOption = advanced;
}

Option::Option(QString displayText, QStringList options)
{
 this->displayText = displayText;
 this->options = options;
 advancedOption = true;
}

void Option::configure( QString value)
{
 currentValue = value;
}

QString Option::getCurrent()
{
 if(currentValue.isEmpty()) return options[0];
    return currentValue;
}

QStringList Option::getOptions()
{
 return options;
}

QString Option::getDisplayText()
{
 return displayText;
}

bool Option::isAdvanced()
{
    return advancedOption;
}
bool  Option::isDirty()
{
 return (currentValue != "" && currentValue!=(options[0]));
}

#if 0
class reconnectwait : public QThread
{
public:
 /*public final */const static int THREADPASS     = 0;
 /*public final */const static int THREADFAIL     = 1;
 int         _status;

 /*public*/ int status() {
  return _status;
 }
 /*public*/ reconnectwait(AbstractSerialPortController* parent) {
  _status = THREADFAIL;
  asp = parent;
 }
 AbstractSerialPortController* asp;
 //@SuppressWarnings("unchecked")
 /*public*/ void run() {
  bool reply = true;
  int count = 0;
  int secondCount = 0;
  while(reply){
   safeSleep(asp->reconnectinterval, "Waiting");
   count++;
   try {
    log->error("Retrying Connection attempt " + QString("%1").arg(secondCount) + "-" + QString("%1").arg(count));
//                Enumeration<CommPortIdentifier> portIDs = CommPortIdentifier.getPortIdentifiers();
//                while (portIDs.hasMoreElements()) {
//                    CommPortIdentifier id = portIDs.nextElement();
//                    // filter out line printers
//                    if (id.getPortType() != CommPortIdentifier.PORT_PARALLEL)
//                        // accumulate the names in a vector
//                        if (id.getName().equals(mPort)){
//                            log->info(mPort + " port has reappeared as being valid trying to reconnect");
//                            openPort(mPort, "jmri");
//                        }
//                    }
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
     if(info.portName() == asp->mPort)
     {
      log->info(asp->mPort + " port has reappeared as being valid trying to reconnect");
      openPort(asp->mPort, "jmri");
     }
    }
   }catch (Exception e) {}
   reply=!asp->opened;
   if (count >=asp->retryAttempts){
    log->error("Unable to reconnect after " + QString("%1").arg(count) + " Attempts, increasing duration of retries");
                //retrying but with twice the retry interval.
    asp->reconnectinterval = asp->reconnectinterval*2;
    count = 0;
    secondCount++;
   }
   if (secondCount >=10){
    log->error("Giving up on reconnecting after 100 attempts to reconnect");
    reply=false;
    }
   }
   if (!asp->opened){
    log->error("Failed to re-establish connectivity");
   } else {
    log->error("Reconnected to " + asp->getCurrentPortName());
    asp->resetupConnection();
   }
  }
  Logger log;
};
#endif
AbstractSerialPortController::AbstractSerialPortController(SystemConnectionMemo* connectionMemo, QObject *parent) :
    SerialPortAdapter(connectionMemo, parent)
{
 InstanceManager::store(this, "PortController");
 log = new Logger("AbstractSerialPortController");
}
/**
*  Get the value of a specific option
*/
QString AbstractSerialPortController::getOptionState(QString option)
{
 if(options.contains(option))
 {
  Option* val = options.value(option);
  return val->getCurrent();
 }
 return "";
}

/**
 * Provide an abstract base for *PortController classes.
 * <P>
 * This is complicated by the lack of multiple inheritance.
 * SerialPortAdapter is an Interface, and its implementing
 * classes also inherit from various PortController types.  But we
 * want some common behaviours for those, so we put them here.
 *
 * @see jmri.jmrix.SerialPortAdapter
 *
 * @author			Bob Jacobsen   Copyright (C) 2001, 2002
 * @version			$Revision: 20030 $
 */
//abstract public class AbstractSerialPortController extends AbstractPortController implements SerialPortAdapter {

/**
 * Standard error handling for port-busy case
 */
/*public*/ QString AbstractSerialPortController::handlePortBusy(PortInUseException p,
            QString portName,
            Logger* log)
{
 log->error(portName+" port is in use: "+p.getMessage());
 JOptionPane::showMessageDialog(NULL, "Port is in use",
                                "Error", JOptionPane::ERROR_MESSAGE);
 ConnectionStatus::instance()->setConnectionState(this->getSystemPrefix(), portName, ConnectionStatus::CONNECTION_DOWN);
 return portName+" port is in use";
}

/**
 * Standard error handling for port-not-found case
 */
/*public*/ QString AbstractSerialPortController::handlePortNotFound(NoSuchPortException /*p*/,
                        QString portName,
                        Logger* log) {
            log->error("Serial port "+portName+" not found");
            JOptionPane::showMessageDialog(NULL, "Serial port "+portName+" not found",
                                            "Error", JOptionPane::ERROR_MESSAGE);
 ConnectionStatus::instance()->setConnectionState(this->getSystemPrefix(), portName, ConnectionStatus::CONNECTION_DOWN);
            return portName+" not found";
}

/*public*/ void AbstractSerialPortController::_connect() //throw( Exception)
{
//    openPort(mPort, "JMRI app");
}

/*public*/ void AbstractSerialPortController::setPort(QString port) {
    mPort= port;
}

/*public*/ QString AbstractSerialPortController::getCurrentPortName()
{
 if (mPort.isEmpty())
 {
  if(getPortNames().isEmpty())
  {
   //This shouldn't happen but in the tests for some reason this happens
   log->error("Port names returned as NULL");
   return NULL;
  }
  if (getPortNames().size()<=0)
  {
      log->error("No usable ports returned");
      return NULL;
  }
  return NULL;
  // return (String)getPortNames().elementAt(0);
 }
 return mPort;
}
/**
 * Set the control leads and flow control. This handles any necessary
 * ordering.
 *
 * @param serialPort Port to be updated
 * @param flow       flow control mode from (@link purejavacomm.SerialPort}
 * @param rts        Set RTS active if true
 * @param dtr        set DTR active if true
 */
/*protected*/ void AbstractSerialPortController::configureLeadsAndFlowControl(SerialPort* serialPort, int flow, bool rts, bool dtr) {
    // (Jan 2018) PJC seems to mix termios and ioctl access, so it's not clear
    // what's preserved and what's not. Experimentally, it seems necessary
    // to write the control leads, set flow control, and then write the control
    // leads again.
    serialPort->setRTS(rts);
    serialPort->setDTR(dtr);

    try {
        if (flow != SerialPort::FLOWCONTROL_NONE) {
            serialPort->setFlowControlMode(flow);
        }
    } catch (UnsupportedCommOperationException* e) {
        log->warn("Could not set flow control, ignoring");
    }
    if (flow!=SerialPort::FLOWCONTROL_RTSCTS_OUT) serialPort->setRTS(rts);  // not connected in some serial ports and adapters
    serialPort->setDTR(dtr);
}

/**
 * Set the flow control, while also setting RTS and DTR to active.
 *
 * @param serialPort Port to be updated
 * @param flow       flow control mode from (@link purejavacomm.SerialPort}
 */
/*protected*/ void AbstractSerialPortController::configureLeadsAndFlowControl(SerialPort* serialPort, int flow) {
    configureLeadsAndFlowControl(serialPort, flow, true, true);
}

/**
 * Set the baud rate.  This records it for later.
 */
/*public*/ void AbstractSerialPortController::configureBaudRate(QString rate) { mBaudRate = rate;}

/*public*/ QString AbstractSerialPortController::getCurrentBaudRate()
{
 if(validBaudRates().isEmpty())
  return "";
 if (mBaudRate.isEmpty()) return validBaudRates()[0];
    return mBaudRate;
}

QStringList AbstractSerialPortController::validBaudRates()
{
 QStringList list;
 foreach(int rate, validBaudNumbers())
  list.append(QString("%1").arg(rate));
 return list;
}

/**
 * Get an array of valid baud rates as integers. This allows subclasses
 * to change the arrays of speeds.
 *
 * This method need not be reimplemented unless the subclass is using
 * currentBaudNumber, which requires it.
 */
/*public*/ QVector<int> AbstractSerialPortController::validBaudNumbers() {
    log->error("default validBaudNumber implementation should not be used");
//TODO:    new Exception().printStackTrace();
    return QVector<int>();
}

/**
 * Convert a baud rate string to a number.
 *
 * Uses the validBaudNumber and validBaudRates methods to do this.
 * @return -1 if no match (configuration system should prevent this)
 */
/*public*/ int AbstractSerialPortController::currentBaudNumber(QString currentBaudRate) {
    QStringList rates = validBaudRates();
    QVector<int> numbers = validBaudNumbers();

    // return if arrays invalid
    if (numbers.isEmpty()) {
        log->error("numbers array NULL in currentBaudNumber");
        return -1;
    }
    if (rates.isEmpty()) {
        log->error("rates array NULL in currentBaudNumber");
        return -1;
    }
    if (numbers.size()<1 || (numbers.size() != rates.length()) ) {
        log->error("arrays wrong length in currentBaudNumber: "+QString("%1").arg(numbers.size())+","+QString("%1").arg(rates.length()));
        return -1;
    }

    // find the baud rate value, configure comm options
    for (int i = 0; i<numbers.size(); i++ )
        if (rates[i]==(currentBaudRate))
            return numbers[i];

    // no match
    log->error("no match to ("+ currentBaudRate +") in currentBaudNumber");
    return -1;
}
/**
 * Set event logging
 */
/*protected*/ void AbstractSerialPortController::setPortEventLogging(SerialPort* port) {
    // arrange to notify later
#if 0 // TODO:
    try {
        port.addEventListener(new SerialPortEventListener() {
            @Override
            public void serialEvent(SerialPortEvent e) {
                int type = e.getEventType();
                switch (type) {
                    case SerialPortEvent.DATA_AVAILABLE:
                        log.info("SerialEvent: DATA_AVAILABLE is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
                        log.info("SerialEvent: OUTPUT_BUFFER_EMPTY is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.CTS:
                        log.info("SerialEvent: CTS is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.DSR:
                        log.info("SerialEvent: DSR is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.RI:
                        log.info("SerialEvent: RI is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.CD:
                        log.info("SerialEvent: CD is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.OE:
                        log.info("SerialEvent: OE (overrun error) is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.PE:
                        log.info("SerialEvent: PE (parity error) is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.FE:
                        log.info("SerialEvent: FE (framing error) is " + e.getNewValue()); // NOI18N
                        return;
                    case SerialPortEvent.BI:
                        log.info("SerialEvent: BI (break interrupt) is " + e.getNewValue()); // NOI18N
                        return;
                    default:
                        log.info("SerialEvent of unknown type: " + type + " value: " + e.getNewValue()); // NOI18N
                        return;
                }
            }
        }
        );
    } catch (java.util.TooManyListenersException ex) {
        log.warn("cannot set listener for SerialPortEvents; was one already set?");
    }

    try {
        port.notifyOnFramingError(true);
    } catch (Exception e) {
        log.debug("Could not notifyOnFramingError: " + e); // NOI18N
    }

    try {
        port.notifyOnBreakInterrupt(true);
    } catch (Exception e) {
        log.debug("Could not notifyOnBreakInterrupt: " + e); // NOI18N
    }

    try {
        port.notifyOnParityError(true);
    } catch (Exception e) {
        log.debug("Could not notifyOnParityError: " + e); // NOI18N
    }

    try {
        port.notifyOnOverrunError(true);
    } catch (Exception e) {
        log.debug("Could not notifyOnOverrunError: " + e); // NOI18N
    }

    port.notifyOnCarrierDetect(true);
    port.notifyOnCTS(true);
    port.notifyOnDSR(true);
#endif
}

//@SuppressWarnings("unchecked")
/*public*/ QVector<QString> AbstractSerialPortController::getPortNames() {
    //reloadDriver(); // Refresh the list of communication ports
    // first, check that the comm package can be opened and ports seen
    portNameVector.clear();
//    Enumeration<CommPortIdentifier> portIDs = CommPortIdentifier.getPortIdentifiers();
//    // find the names of suitable ports
//    while (portIDs.hasMoreElements()) {
//        CommPortIdentifier id = portIDs.nextElement();
//        // filter out line printers
//        if (id.getPortType() != CommPortIdentifier.PORT_PARALLEL)
//            // accumulate the names in a vector
//            portNameVector.addElement(id.getName());
//      }
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        portNameVector.append(info.portName());
     return portNameVector;
}
/*This in place here until all systems are converted over to the systemconnection memo
this will then become abstract, once all the code has been refactored*/
///*public*/ SystemConnectionMemo* AbstractSerialPortController::getSystemConnectionMemo() { return NULL; }

/*Set disable should be handled by the local port controller in each connection
this is abstract in the Portcontroller and can be removed once all the other codes has
been refactored */
/*public*/ void AbstractSerialPortController::setDisabled(bool disabled) {
    mDisabled = disabled;
}

/*Dispose should be handled by the port adapters and this should be abstract
However this is in place until all the other code has been refactored */
/*public*/ void AbstractSerialPortController::dispose(){
}

/**
 * This is called when a connection is initially lost.  It closes the client side
 * socket connection, resets the open flag and attempts a reconnection.
 */
/*public*/ void AbstractSerialPortController::recover(){
    if (!allowConnectionRecovery) return;
    opened = false;
    try {
        closeConnection();
    } catch (Exception e) { }
    reconnect();
}
/*Each serial port adapter should handle this and it should be abstract.
 However this is in place until all the other code has been refactored */
/*protected*/ void AbstractSerialPortController::closeConnection() throw(Exception) { log->error("crap Called"); }

/*Each port adapter should handle this and it should be abstract.
 However this is in place until all the other code has been refactored */
/*protected*/ void AbstractSerialPortController::resetupConnection(){ }

/**
 * Attempts to reconnect to a failed Server
 */
/*public*/ void AbstractSerialPortController::reconnect(){
    // If the connection is already open, then we shouldn't try a re-connect.
    if (opened && !allowConnectionRecovery){
        return;
    }
#if 0
    reconnectwait* thread = new reconnectwait(this);
    thread->start();
    try{
        thread->join();
    } catch (InterruptedException e) {
        log->error("Unable to join to the reconnection thread " + e.getMessage());
    }
#endif
    if (!opened){
        log->error("Failed to re-establish connectivity");
    } else {
        log->info("Reconnected to " + getCurrentPortName());
        resetupConnection();
    }
}



    //final static protected org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(AbstractSerialPortController.class.getName());
