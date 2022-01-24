#include "usbdcs52adapter.h"
#include "loggerfactory.h"
#include "usbdcs52systemconnectionmemo.h"
#include "PR2/lnpr2packtizer.h"
#include "serialport.h"

/**
 * Update the code in jmri.jmrix.loconet.locobuffer so that it refers to the
 * option settings for the Digitrax DCS52's USB interface
 * <p>
 * Based on PR3Adapter.java
 *
 * @author Bob Jacobsen Copyright (C) 2004, 2005, 2006, 2008
 * @author B. Milhaupt Copyright (C) 2019
 */
///*public*/ class UsbDcs52Adapter extends LocoBufferAdapter {

/*public*/ UsbDcs52Adapter::UsbDcs52Adapter(QObject* parent)
 : LocoBufferAdapter(new UsbDcs52SystemConnectionMemo())
{
    //super(new UsbDcs52SystemConnectionMemo());

    options.remove(option2Name);
    options.insert(option2Name, new Option(tr("Command Station Type:"), commandStationOptions(), false));

}

/**
 * Sets up the serial port characteristics.  Always uses flow control, which is
 * not considered a user-settable option.  Sets the DCS52 USB interface for the appropriate
 * operating mode, based on the selected "command station type".
 *
 * @param activeSerialPort  the port to be configured
 */
//@Override
/*protected*/ void UsbDcs52Adapter::setSerialPort(SerialPort* activeSerialPort) //throws UnsupportedCommOperationException
{
    // find the baud rate value, configure comm options
    int baud = currentBaudNumber(mBaudRate);
    activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS_8,
            SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);

    // configure flow control to always on
    int flow = SerialPort::FLOWCONTROL_RTSCTS_OUT;
    if (getOptionState(option1Name) == (validOption1[1])) {
        flow = SerialPort::FLOWCONTROL_NONE;
    }
    configureLeadsAndFlowControl(activeSerialPort, flow);

    log->info("USB DCS52 adapter"
            + QString(activeSerialPort->getFlowControlMode() == SerialPort::FLOWCONTROL_RTSCTS_OUT ? " set hardware flow control, mode=" : " set no flow control, mode=")
            + QString::number(activeSerialPort->getFlowControlMode())
            + " RTSCTS_OUT=" + QString::number(SerialPort::FLOWCONTROL_RTSCTS_OUT)
            + " RTSCTS_IN=" + QString::number(SerialPort::FLOWCONTROL_RTSCTS_IN));
}

/**
 * Set up all of the other objects to operate with a DCS52 USB interface connected to this
 * port. This overrides the version in loconet.locobuffer, but it has to
 * duplicate much of the functionality there, so the code is basically
 * copied.
 */
//@Override
/*public*/ void UsbDcs52Adapter::configure() {
    setCommandStationType(getOptionState(option2Name));
    setTurnoutHandling(getOptionState(option3Name));
    if (commandStationType->getType() == LnCommandStationType::COMMAND_STATION_USB_DCS52_ALONE) {
        // DCS52 USB in standalone programmer case:
        // connect to a packetizing traffic controller
        // that does echoing
        //
        // Note - already created a LocoNetSystemConnectionMemo, so re-use
        // it when creating a PR2 Packetizer.  (If create a new one, will
        // end up with two "LocoNet" menus...)
        LnPr2Packetizer* packets =
                new LnPr2Packetizer(this->getSystemConnectionMemo()->self());
        packets->connectPort(this);

        // set traffic controller and configure command station and mangers
        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
        // do the common manager config
        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
                mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);  // never transponding!
        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagersPR2();

        // start operation
        //packets->startThreads();

        // set mode
        LocoNetMessage* msg = new LocoNetMessage(6);
        msg->setOpCode(0xD3);
        msg->setElement(1, 0x10);
        msg->setElement(2, 1);  // set PR2
        msg->setElement(3, 0);
        msg->setElement(4, 0);
        packets->sendLocoNetMessage(msg);

    } else {
        // MS100 modes - connecting to a separate command station
        // get transponding option
        setTranspondingAvailable(getOptionState("TranspondingPresent"));
        // connect to a packetizing traffic controller
        LnPacketizer* packets = getPacketizer(getOptionState(option4Name));
        packets->connectPort(this);

        // set traffic controller and configure command station and mangers
        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
        // do the common manager config
        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
                mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);

        ((UsbDcs52SystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagersMS100();

        // start operation
        //packets->startThreads();

        // set mode
        LocoNetMessage* msg = new LocoNetMessage(6);
        msg->setOpCode(0xD3);
        msg->setElement(1, 0x10);
        msg->setElement(2, 0);  // set MS100, no power
        msg->setElement(3, 0);
        msg->setElement(4, 0);
        packets->sendLocoNetMessage(msg);
    }
}

/**
 * {@inheritDoc}
 *
 * @return String[] containing the single valid baud rate, "57,600".
 */
//@Override
/*public*/ QStringList UsbDcs52Adapter::validBaudRates() {
    return QStringList() <<"57,600 baud"; // TODO I18N
}

/**
 * {@inheritDoc}
 *
 * @return int[] containing the single valid baud rate, 57600.
 */
//@Override
/*public*/ QVector<int> UsbDcs52Adapter::validBaudNumbers() {
    return QVector<int>() << 57600;
}

//@Override
/*public*/ int UsbDcs52Adapter::defaultBaudIndex() {
    return 0;
}

// Option 1 does flow control, inherited from LocoBufferAdapter

/**
 * The DCS52 USB interface can be used as a "Standalone Programmer", or with various LocoNet
 * command stations, or as an interface to a "Standalone LocoNet".  Provide those
 * options.
 *
 * @return an array of strings containing the various command station names and
 *      name(s) of modes without command stations
 */
/*public*/ QStringList UsbDcs52Adapter::commandStationOptions() {
    QVector<QString> retval = QVector<QString>(commandStationNames.length() + 1);
    retval[0] = LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_USB_DCS52_ALONE)->getName();
    retval[1] = LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_DCS052)->getName();
    int count = 2;
    for (QString commandStationName : commandStationNames) {
        if (commandStationName != LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS052)->getName()) {
            // include all but COMMAND_STATION_DCS052, which was forced  to
            // the front of the list (above)
            retval[count++] = commandStationName;
        }
    }
    // Note: Standalone loconet does not make sense for DCS240 USB interface.
    return retval.toList();
}

//@Override
/*public*/ SystemConnectionMemo* UsbDcs52Adapter::getSystemConnectionMemo() {
    LocoNetSystemConnectionMemo* m = (LocoNetSystemConnectionMemo*)LocoBufferAdapter::getSystemConnectionMemo();
    if (qobject_cast<UsbDcs52SystemConnectionMemo*>(m)) {
        return (SystemConnectionMemo*) m;
    }
    log->error("Cannot cast the system connection memo to a UsbDcs52SystemConnection Memo.");
    return nullptr;
}

/*public*/ QString UsbDcs52Adapter::className()
{
 return "jrmi.jmrix.loconet.usb_dcs52.UsbDcs52Adapter";
}


/*private*/ /*final*/ /*static*/ Logger* UsbDcs52Adapter::log = LoggerFactory::getLogger("UsbDcs52Adapter");
