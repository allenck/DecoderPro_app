#include "rfidusb.h"
#include <QDebug>
#include <QMessageBox>

RfidUsb::RfidUsb(QWidget *parent) :
    QObject(parent)
{
 this->parent = parent;
 serial = NULL;
 bIsOpen = false;
 baRfid.clear();
 foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
 {
#ifdef WIN32
     if(info.description() == "USB Serial Port" && info.manufacturer() == "FTDI")
#else
     if(info.portName().startsWith("ttyUSB") || (info.productIdentifier() == 0x6001 && info.vendorIdentifier() == 0x403))
#endif
   availPorts.append(info);
 }
 if(availPorts.count() > 0)
 {
  _portName = availPorts.at(0).portName();
  _portInfo = availPorts.at(0);
 }
}
RfidUsb::~RfidUsb()
{
 closeSerialPort();
}

bool RfidUsb::openPort(QString portName)
{
 this->_portName = portName;
 serial = new QSerialPort(this);
 connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
         SLOT(handleError(QSerialPort::SerialPortError)));
 serial->setPortName(this->_portName);
 bIsOpen = serial->open(QIODevice::ReadOnly);
 serial->clear();
 if(!bIsOpen)
 {
  qDebug()<< tr("Error opening %1 %2").arg(portName).arg(serial->errorString());
  return bIsOpen;
 }

 if(!serial->setBaudRate(QSerialPort::Baud9600))
 {
  qDebug() << tr("Can't set baud rate 9600 baud to port %1, error %2")
                 .arg(portName).arg(serial->errorString());
  return false;
 }
 if(!serial->setDataBits(QSerialPort::Data8))
 {
  qDebug() << tr("Can't set 8 data bits to port %1, error code %2")
              .arg(portName).arg(serial->error());
  return false;
 }
 if(!serial->setParity(QSerialPort::NoParity))
 {
  qDebug() << tr("Can't set no parity to port %1, error %2")
                                .arg(portName).arg(serial->errorString());
  return false;
 }
 if(!serial->setStopBits(QSerialPort::OneStop))
 {
  qDebug() << tr("Can't set 1 stop bit to port %1, error %2")
                                .arg(portName).arg(serial->errorString());
  return false;
 }
 if(!serial->setFlowControl(QSerialPort::HardwareControl))
 {
   qDebug() << tr("Can't set no flow control to port %1, error %2")
               .arg(portName).arg(serial->errorString());
   return false;
 }
 connect(serial, SIGNAL(readyRead()), this, SLOT(dataReady()));
 return true;
}
bool RfidUsb::isOpen() { return bIsOpen;}

void RfidUsb::dataReady() // [slot]
{
 rfidMsg msg;
 msg.portName = _portName;
 QByteArray ba = serial->readAll();
 baRfid.append(ba);
 if(baRfid.count()>= 16)
 {
  if(baRfid.at(0) == 0x02 && baRfid.at(15) == 0x03)
  {
   msg.rfid = "";
   for(int i=1; i< 13; i++)
   {
    msg.rfid.append(baRfid.at(i));
   }
   emit rfidMsgRcvd(&msg);
   qDebug() << QString("RFID id %1 from %2").arg(msg.rfid).arg(msg.portName);
   baRfid.remove(0, 16);
  }
 }
}
void RfidUsb::handleError(QSerialPort::SerialPortError error)
{
 if (error == QSerialPort::ResourceError)
 {
  QMessageBox::critical(parent, tr("Critical Error"), serial->errorString());
  closeSerialPort();
 }
}
void RfidUsb::closeSerialPort()
{
 if(serial)
 {
  serial->close();
  bIsOpen = false;
  serial = NULL;
 }
}
//QList<QSerialPortInfo>* RfidUsb::ports()
//{
// return &availPorts;
//}
QString RfidUsb::portName() { return _portName;}
QSerialPortInfo RfidUsb::portInfo() { return _portInfo;}
