#include "rfidserialdriveradapter.h"
#include "loggerfactory.h"
#include "rfidsystemconnectionmemo.h"
#include "rfidconnectiontypelist.h"
#include "serialport.h"
#include "standalonetrafficcontroller.h"
#include "standalonesensormanager.h"
#include "serialport.h"
#include "standalonereportermanager.h"
#include <QDataStream>
#include "coreidrfidprotocol.h"
#include "olimexrfidprotocol.h"
#include "id12larfidprotocol.h"

/**
 * Provide access to RFID devices via a serial comm port. Derived from the
 * Oaktree code.
 *
 * @author Bob Jacobsen Copyright (C) 2006, 2007, 2008
 * @author Matthew Harris Copyright (C) 2011
 * @author Oscar A. Pruitt Copyright (C) 2015
 * @author B. Milhaupt Copyright (C) 2017
 * @since 2.11.4
 */
///*public*/ class SerialDriverAdapter extends RfidPortController implements jmri.jmrix.SerialPortAdapter {


/*public*/ RfidSerialDriverAdapter::RfidSerialDriverAdapter(QObject* parent) : RfidPortController(new RfidSystemConnectionMemo(), parent) {
    //super(new RfidSystemConnectionMemo());
    option1Name = "Adapter"; // NOI18N
    option2Name = "Concentrator-Range"; // NOI18N
    option3Name = "Protocol"; // NOI18N
    option4Name = "Device"; // NOI18N
    options.insert(option1Name,  new Option(tr("Adapter:"), QStringList() <<"Generic Stand-alone"/*, "MERG Concentrator"*/, false)); // NOI18N
    options.insert(option2Name,  new Option(tr("Concentrator range:"), QStringList() <<"A-H"<< "I-P", false)); // NOI18N
    options.insert(option3Name,  new Option(tr("Connection Protocol:"), QStringList()<<"CORE-ID" << "Olimex" << "Id-12LA"/*<< "Parallax"<< "SeeedStudio"<< "EM-18"*/, false)); // NOI18N
    options.insert(option4Name,  new Option(tr("Device Type:"), QStringList()<<"MOD-RFID125"/*<< "MOD-RFID1356MIFARE"*/, false)); // NOI18N
    this->manufacturerName = RfidConnectionTypeList::RFID;
}

//@Override
/*public*/ QString RfidSerialDriverAdapter::openPort(QString portName, QString appName) {
    try {
        // get and open the primary port
        //CommPortIdentifier portID = CommPortIdentifier.getPortIdentifier(portName);
        activeSerialPort = new SerialPort();
        try {
            //activeSerialPort = (SerialPort*) portID.open(appName, 2000);  // name of program, msec to wait
            activeSerialPort->open(portName, QIODevice::ReadWrite);
        } catch (PortInUseException p) {
            return handlePortBusy(p, portName, log);
        }
        // try to set it for serial
        try {
            setSerialPort();
        } catch (UnsupportedCommOperationException e) {
            log->error(tr("Cannot set serial parameters on port %1: %2").arg(portName).arg(e.getMessage())); // NOI18N
            return "Cannot set serial parameters on port " + portName + ": " + e.getMessage(); // NOI18N
        }

//        // set framing (end) character
//        try {
//            log->debug(tr("Serial framing was observed as: %1 %2").arg(activeSerialPort->isReceiveFramingEnabled()).arg(
//                    activeSerialPort->getReceiveFramingByte())); // NOI18N
//        } catch (Exception ef) {
//            log->debug(tr("failed to set serial framing: %1").arg(ef)); // NOI18N
//        }

        // set timeout; framing should work before this anyway
        try {
            activeSerialPort->enableReceiveTimeout(10);
            log->debug(tr("Serial timeout was observed as: %1 %2").arg(activeSerialPort->getReceiveTimeout()).arg(
                    activeSerialPort->isReceiveTimeoutEnabled())); // NOI18N
        } catch (UnsupportedCommOperationException et) {
            log->info(tr("failed to set serial timeout: %1").arg(et.getMessage())); // NOI18N
        }

        // get and save stream
        serialStream = activeSerialPort->getInputStream();

        // purge contents, if any
        purgeStream(serialStream);

        // report status?
        if (log->isInfoEnabled()) {
            // report now
            log->info(portName + " port opened at " // NOI18N
                    + activeSerialPort->getBaudRate() + " baud with" // NOI18N
                    + " DTR: " + activeSerialPort->isDTR() // NOI18N
                    + " RTS: " + activeSerialPort->isRTS() // NOI18N
                    + " DSR: " + activeSerialPort->isDSR() // NOI18N
                    + " CTS: " + activeSerialPort->isCTS() // NOI18N
                    + "  CD: " + activeSerialPort->isCD() // NOI18N
            );
        }
        if (log->isDebugEnabled()) {
            // report additional status
            log->debug(tr(" port flow control shows %1").arg
                    (activeSerialPort->getFlowControlMode() == SerialPort::FLOWCONTROL_RTSCTS_OUT ? "hardware flow control" : "no flow control")); // NOI18N

            // log events
            setPortEventLogging(activeSerialPort);
        }

        opened = true;

    } catch (NoSuchPortException p) {
        return handlePortNotFound(p, portName, log);
    } catch (IOException ex) {
        log->error(tr("Unexpected exception while opening port %1").arg(portName), ex);
        return "Unexpected error while opening port " + portName + ": " + ex.getMessage(); // NOI18N
    }

    return nullptr; // normal operation
}

/**
 * Can the port accept additional characters? Yes, always
 *
 * @return True if OK
 */
/*public*/ bool RfidSerialDriverAdapter::okToSend() {
    return true;
}

/**
 * Set up all of the other objects to operate connected to this port
 */
//@Override
/*public*/ void RfidSerialDriverAdapter::configure()
{
 RfidTrafficController* control;
 RfidProtocol* protocol;

 // set up the system connection first
 QString opt1 = getOptionState(option1Name);
 if(opt1 == "Generic Stand-alone") // NOI18N
 {
  // create a Generic Stand-alone port controller
  log->debug("Create Generic Standalone SpecificTrafficController"); // NOI18N
  control = new StandaloneTrafficController((RfidSystemConnectionMemo*)this->getSystemConnectionMemo());
  ((RfidSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers(
          new StandaloneSensorManager(control, this->getSystemPrefix()),
          new StandaloneReporterManager(control, this->getSystemPrefix()));
 }
 else if(opt1 == "MERG Concentrator")
 {// NOI18N
//            // create a MERG Concentrator port controller
//            log->debug("Create MERG Concentrator SpecificTrafficController"); // NOI18N
//            control = new ConcentratorTrafficController(this.getSystemConnectionMemo(), getOptionState(option2Name));
//            this.getSystemConnectionMemo().configureManagers(
//                    new ConcentratorSensorManager(control, this.getSystemPrefix()),
//                    new ConcentratorReporterManager(control, this.getSystemPrefix()));
 }
 else
 {
  // no connection at all - warn
  log->warn(tr("adapter option %1 defaults to Generic Stand-alone").arg(opt1)); // NOI18N
  // create a Generic Stand-alone port controller
  control = new StandaloneTrafficController((RfidSystemConnectionMemo*)this->getSystemConnectionMemo());
  ((RfidSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers(
          new StandaloneSensorManager(control, this->getSystemPrefix()),
          new StandaloneReporterManager(control, this->getSystemPrefix()));
  //break;
 }

 // Now do the protocol
 QString opt3 = getOptionState(option3Name);
 QString opt4 = getOptionState(option4Name);
 if (opt1 ==("MERG Concentrator"))
 { // NOI18N
#if 0
     // MERG Concentrator only supports CORE-ID
     log->info("set protocol to CORE-ID"); // NOI18N
     QString opt2 = getOptionState(option2Name);
     switch (opt2) {
         case "A-H": // NOI18N
             log->info("set concentrator range to 'A-H' at position 1"); // NOI18N
             protocol = new CoreIdRfidProtocol('A', 'H', 1);
             break;
         case "I-P": // NOI18N
             log->info("set concentrator range to 'I-P' at position 1"); // NOI18N
             protocol = new CoreIdRfidProtocol('I', 'P', 1);
             break;
         default:
             // unrecognised concentrator range - warn
             log->warn("concentrator range '{}' not supported - default to no concentrator", opt2); // NOI18N
             protocol = new CoreIdRfidProtocol();
             break;
     }
#endif
 }
 else {
     if(opt3==  "CORE-ID") // NOI18N
     {
      log->info("set protocol to CORE-ID"); // NOI18N
      protocol = (RfidProtocol*)new CoreIdRfidProtocol();
     }
     else if(opt3== "Olimex")
     {// NOI18N
      if (opt4 == ("MOD-RFID1356MIFARE")) { // NOI18N
          log->info("set protocol for Olimex MOD-RFID1356MIFARE"); // NOI18N
//                    protocol = new OlimexRfid1356mifareProtocol();
      } else {
          log->info("set protocol for Olimex MOD-RFID125"); // NOI18N
          protocol = new OlimexRfidProtocol();
      }
     }
     else if(opt3=="Parallax") // NOI18N
     {
             log->info("set protocol to Parallax"); // NOI18N
//                protocol = new ParallaxRfidProtocol();
     }
     else if(opt3== "SeeedStudio") // NOI18N
     {
             log->info("set protocol to SeeedStudio"); // NOI18N
//                protocol = new SeeedStudioRfidProtocol();
     }
     else if(opt3=="EM-18") // NOI18N
     {
             log->info("set protocol to EM-18"); // NOI18N
//                protocol = new Em18RfidProtocol();
     }
     else if(opt3=="Id-12LA") // NOI18N
     {
             log->info("set protocol to EM-18"); // NOI18N
             protocol = new Id12LARfidProtocol();
     }
     else
     {
             // no protocol at all - warn
             log->warn(tr("protocol option %1 defaults to CORE-ID").arg(opt3));
             // create a coreid protocol
             protocol = new CoreIdRfidProtocol();
     }
 }
 ((RfidSystemConnectionMemo*) this->getSystemConnectionMemo())->setProtocol(protocol);

 // connect to the traffic controller
 ((RfidSystemConnectionMemo*) this->getSystemConnectionMemo())->setRfidTrafficController(control);
 control->setAdapterMemo((RfidSystemConnectionMemo*)this->getSystemConnectionMemo());
 control->connectPort(this);
 control->sendInitString();
}

// base class methods for the RfidPortController interface
//@Override
/*public*/ QDataStream* RfidSerialDriverAdapter::getInputStream() {
    if (!opened) {
        log->error("getInputStream called before load(), stream not available");
        return nullptr;
    }
    //return new QDataStream(*serialStream);
    return serialStream;
}

//@Override
/*public*/ QDataStream* RfidSerialDriverAdapter::getOutputStream() {
    if (!opened) {
        log->error("getOutputStream called before load(), stream not available");
    }
    try {
        //return new QDataStream(*activeSerialPort->getOutputStream());
     return activeSerialPort->getOutputStream();
    } catch (IOException e) {
        log->error(tr("getOutputStream exception: %1").arg(e.getMessage()));
    }
    return nullptr;
}

//@Override
/*public*/ bool RfidSerialDriverAdapter::status() {
    return opened;
}

/**
 * Local method to do specific port configuration
 *
 * @throws UnsupportedCommOperationException if unable to configure port
 */
/*protected*/ void RfidSerialDriverAdapter::setSerialPort() throw (UnsupportedCommOperationException) {
    // find the baud rate value, configure comm options
    int baud = 9600;  // default, but also defaulted in the initial value of selectedSpeed

    // check for specific port type
    activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS_8,
            SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);

    // find and configure flow control
    int flow = SerialPort::FLOWCONTROL_NONE; // default
    if (getOptionState(option1Name) == ("MERG Concentrator")) {
        // Set Hardware Flow Control for Concentrator
        log->debug("Set hardware flow control for Concentrator");
        flow = SerialPort::FLOWCONTROL_RTSCTS_OUT;
    }
    configureLeadsAndFlowControl(activeSerialPort, flow);
}

//@Override
/*public*/ QStringList RfidSerialDriverAdapter::validBaudRates() {
    //return Arrays.copyOf(validSpeeds, validSpeeds.length);
 return QStringList(validSpeeds);
}

/**
 * Set the baud rate.
 *
 * @param rate the baud rate to set
 */
//@Override
/*public*/ void RfidSerialDriverAdapter::configureBaudRate(QString rate) {
    log->debug(tr("configureBaudRate: %1").arg(rate));
    selectedSpeed = rate;
    SerialPortAdapter::configureBaudRate(rate);
}



/*private*/ /*static*/ /*final*/ Logger* RfidSerialDriverAdapter::log = LoggerFactory::getLogger("SerialDriverAdapter");


