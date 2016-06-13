#include "locobufferusbadapter.h"

LocoBufferUsbAdapter::LocoBufferUsbAdapter(QObject *parent) :
    LocoBufferAdapter(new LocoNetSystemConnectionMemo, parent)
{
 options.remove(option1Name);
}
void LocoBufferUsbAdapter::configure()
{
  LocoBufferAdapter::configure();
  //packets->setSerial(&activeSerialPort->serial);
}

///**
// * Always use flow control, not considered a user-setable option
// */
///*protected*/ void LocoBufferUsbAdapter::setSerialPort(SerialPort activeSerialPort) // throws gnu.io.UnsupportedCommOperationException
//{
// // find the baud rate value, configure comm options
// int baud = 19200;  // default, but also defaulted in the initial value of selectedSpeed
// for (int i = 0; i<validBaudNumber().count(); i++ )
//  if (validBaudRates()[i]==(mBaudRate))
//   baud = validBaudNumber()[i];
// activeSerialPort.setSerialPortParams(baud, SerialPort::DATABITS_8,
//                                         SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);

// // set RTS high, DTR high - done early, so flow control can be configured after
// activeSerialPort.setRTS(true);		// not connected in some serial ports and adapters
// activeSerialPort.setDTR(true);		// pin 1 in Mac DIN8; on main connector, this is DTR

// // configure flow control to always on
// int flow = SerialPort::FLOWCONTROL_RTSCTS_OUT;
// activeSerialPort.setFlowControlMode(flow);
// log.debug("Found flow control "+QString("%1").arg(activeSerialPort.getFlowControlMode())
//              +" RTSCTS_OUT="+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_OUT)
//              +" RTSCTS_IN= "+QString("%1").arg(SerialPort::FLOWCONTROL_RTSCTS_IN));

////    if (!activeSerialPort.serial.setBaudRate(QSerialPort::Baud57600))
////    {
////        emit error(QString("Can't set baud rate 9600 baud to port %1, error code %2").arg(activeSerialPort.serial.portName()).arg(activeSerialPort.serial.error()));
////     return;
////    }
//}

/**
 * Get an array of valid baud rates.
 */
/*public*/ QStringList LocoBufferUsbAdapter::validBaudRates() {
    //return new QStringList{"57,600 baud"};
 QStringList list;
 list << "57,600 baud";
 return list;
}

/**
 * Get an array of valid baud rates as integers. This allows subclasses
 * to change the arrays of speeds.
 */
/*public*/ QVector<int> LocoBufferUsbAdapter::validBaudNumber() {
    //return new int[]{57600};
 QVector<int> list;
 list << 57600;
 return list;
}

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoBufferUsbAdapter.class.getName());
/*public*/ void LocoBufferUsbAdapter::dispose(){
//    if (adaptermemo!=NULL)
//        adaptermemo->dispose();
//    adaptermemo = NULL;
}
