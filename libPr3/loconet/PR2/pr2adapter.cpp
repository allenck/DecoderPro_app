#include "pr2adapter.h"
#include "loggerfactory.h"
#include "pr2systemconnectionmemo.h"
#include "lnpr2packtizer.h"
#include "lncommandstationtype.h"

/**
 * Update the code in jmri.jmrix.loconet.locobuffer so that it refers to the
 * switch settings on the new Digitrax PR2
 *
 * @author Bob Jacobsen Copyright (C) 2004, 2005, 2006
  */
// /*public*/ class PR2Adapter extends LocoBufferAdapter {

/*public*/ PR2Adapter::PR2Adapter(QObject *parent) : LocoBufferAdapter(new PR2SystemConnectionMemo(), parent) {
    //super(new PR2SystemConnectionMemo());

    options.remove(option2Name);
    options.insert(option2Name, new Option(tr("Command Station Type"), commandStationOptions(), false));
}

/**
 * Always use flow control, not considered a user-setable option
 */
//@Override
/*protected*/ void PR2Adapter::setSerialPort(SerialPort* activeSerialPort) throw (UnsupportedCommOperationException) {
    // find the baud rate value, configure comm options
    int baud = 57600;  // default, but also defaulted in the initial value of selectedSpeed
    for (int i = 0; i < validBaudNumber().length(); i++) {
        if (validBaudRates()[i] == (mBaudRate)) {
            baud = validBaudNumber()[i];
        }
    }
    activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS_8,
            SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);

    // configure flow control from option
    int flow = SerialPort::FLOWCONTROL_RTSCTS_OUT;
    if (getOptionState(option1Name) == (validOption1[1])) {
        flow = SerialPort::FLOWCONTROL_NONE;
    }
    configureLeadsAndFlowControl(activeSerialPort, flow);
    log->info(QString("PR2 adapter")
            +(activeSerialPort->getFlowControlMode() == SerialPort::FLOWCONTROL_RTSCTS_OUT ? " set hardware flow control, mode=" : " set no flow control, mode=")
            +activeSerialPort->getFlowControlMode()
            + " RTSCTS_OUT=" + SerialPort::FLOWCONTROL_RTSCTS_OUT
            + " RTSCTS_IN=" + SerialPort::FLOWCONTROL_RTSCTS_IN);
}

/**
 * Set up all of the other objects to operate with a PR2 connected to this
 * port. This overrides the version in loconet.locobuffer, but it has to
 * duplicate much of the functionality there, so the code is basically
 * copied.
 */
//@Override
/*public*/ void PR2Adapter::configure() {

    setCommandStationType(getOptionState(option2Name));
    setTurnoutHandling(getOptionState(option3Name));

    // connect to a packetizing traffic controller
    // that does echoing
    LnPr2Packetizer* packets = new LnPr2Packetizer();
    packets->connectPort(this);

    // create memo
    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->setLnTrafficController(packets);
    // do the common manager config
    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureCommandStation(commandStationType,
            mTurnoutNoRetry, mTurnoutExtraSpace, mTranspondingAvailable);
    ((LocoNetSystemConnectionMemo*)this->getSystemConnectionMemo())->configureManagers();

    // start operation
    packets->startThreads();

}

/**
 * Get an array of valid baud rates.
 */
//@Override
/*public*/ QStringList PR2Adapter::validBaudRates() {
    return QStringList() << "57,600 baud"; // NOI18N
}

/**
 * Get an array of valid baud rates as integers. This allows subclasses to
 * change the arrays of speeds.
 */
//Override
/*public*/ QVector<int> PR2Adapter::validBaudNumber() {
    return QVector<int>() <<57600;
}

// Option 1 does flow control, inherited from LocoBufferAdapter

/**
 * The PR2 has one mode
 */
/*public*/ QStringList PR2Adapter::commandStationOptions() {
    //return QStringList << LnCommandStationType::COMMAND_STATION_PR2_ALONE.getName()};
 return QStringList() << "PR2 standalone programmer";
}

/*private*/ /*final*/ /*static*/ Logger* PR2Adapter::log = LoggerFactory::getLogger("PR2Adapter");
