#include "serialport.h"
#include "connectionstatus.h"
#include <QSerialPort>
#include <QTextStream>
#include <QTimer>
#include <QWaitCondition>
#include "lnpacketizer.h"

SerialPort::SerialPort(QObject *parent) :
    QObject(parent)
{
 log = new Logger("SerialPort", this);
 serial = new QSerialPort(this);
// rcvBuffer = new QByteArray(500,0);
// xmtBuffer = new QByteArray(500,0);

// istream = new QDataStream(rcvBuffer, QIODevice::ReadWrite);
// ostream = new QDataStream(xmtBuffer, QIODevice::ReadWrite);
 istream = NULL;
 ostream = NULL;
 bOpened = false;
 rcvTimeout = 0;

}
//activeSerialPort->setSerialPortParams(baud, SerialPort::DATABITS_8,
//                                     SerialPort::STOPBITS_1, SerialPort::PARITY_NONE);
void SerialPort::OnError()
{
 log->error("SerialPort '" + serial->portName() + ":  error " + serial->errorString());
}

void SerialPort::setSerialPortParams(int baud, int databits, int stopbits, int parity ) throw(UnsupportedCommOperationException)
{

 QSerialPort::BaudRate rate;
 switch (baud)
 {
 case 9600:
  rate = QSerialPort::Baud9600;  // used by Sprog
  break;
 case 115200:
  rate = QSerialPort::Baud115200;
  break;
 case 57600:
  rate = QSerialPort::Baud57600;  // used by LocoNet
  break;
 default:
  throw new UnsupportedCommOperationException("invalid baud rate");
  //rate = QSerialPort::Baud57600;
 }
 // TODO: translate parameters to those required by QtSerial port. Defaults here are OK for PR3 adapter.
 if (!serial->setBaudRate(rate))
 {
  emit error(tr("Can't set baud rate %3 baud to port %1, error code %2").arg(serial->portName()).arg(serial->errorString()).arg(baud));
  throw UnsupportedCommOperationException(tr("Can't set baud rate %3 baud to port %1, error code %2").arg(serial->portName()).arg(serial->errorString()).arg(baud));

  return;
 }
 QSerialPort::DataBits db;
 switch(databits)
 {
 case DATABITS_8:
  db = QSerialPort::Data8;
  break;
 default:
  break;
 }

 if (!serial->setDataBits(db))
 {
  emit error(tr("Can't set 8 data bits to port %1, error code %2")
                .arg(serial->portName()).arg(serial->errorString()));
  return;
 }

 QSerialPort::Parity p;
 switch(parity)
 {
  case PARITY_NONE:
  p = QSerialPort::NoParity;
  break;
 default:
  break;
 }

 if (!serial->setParity(p)) {
  emit error(tr("Can't set NoParity to port %1, error code %2")
                .arg(serial->portName()).arg(serial->errorString()));
  return;
 }

 QSerialPort::StopBits sb;
 switch(stopbits)
 {
 case STOPBITS_1:
  sb = QSerialPort::OneStop;
  break;
 default:
  break;
 }

 if (!serial->setStopBits(sb)) {
  emit error(tr("Can't set 1 stop bit to port %1, error code %2")
                .arg(serial->portName()).arg(serial->errorString()));
  return;
 }

}

void SerialPort::setRTS(bool bRts)
{
 if(!serial->setRequestToSend(bRts))
 {
  emit error(tr("Can't set RTS to port %1, error code %2")
                   .arg(serial->portName()).arg(serial->errorString()));
  return;
 }
}
void SerialPort::setDTR(bool bDTR)
{
 if(!serial->setDataTerminalReady(bDTR))
 {
  emit error(tr("Can't set DTR to port %1, error code %2")
               .arg(serial->portName()).arg(serial->errorString()));
  return;
 }
}
void SerialPort::setFlowControlMode(int flow) throw (UnsupportedCommOperationException)
{
 QSerialPort::FlowControl myFlow;
 switch (flow)
 {
 case FLOWCONTROL_RTSCTS_OUT:
   myFlow = QSerialPort::HardwareControl;
   break;
  case FLOWCONTROL_NONE:
   myFlow = QSerialPort::NoFlowControl;
   break;
  default:
  //myFlow = QSerialPort::SoftwareControl;
   throw new UnsupportedCommOperationException("invalid flow control");
 }
 if(!serial->setFlowControl(myFlow))
 {
  emit error(tr("Can't set flow control to port %1, error code %2")
               .arg(serial->portName()).arg(serial->error()));
  return;
 }
}
int SerialPort::getFlowControlMode()
{
 return serial->flowControl();
}
QString SerialPort::flowControl()
{
 int f = serial->flowControl();
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

void SerialPort::setPortName(QString portName)
{
 serial->setPortName(portName);
 this->portName = portName;
}
QString SerialPort::errorString()
{
 return serial->errorString();
}
void SerialPort::clear()
{
 serial->clear();
}
bool SerialPort::flush()
{
 return serial->flush();
}

bool SerialPort::open(QString portName, QIODevice::OpenMode mode)
{
 serial->setPortName(portName);
 return open(mode);
}

bool SerialPort::open(QIODevice::OpenMode mode)

{
 if(bOpened)
  serial->close();
 //QSerialPortInfo info = QSerialPortInfo(portName);
 QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

 log->info("Available ports:");
 foreach (QSerialPortInfo info, list)
 {
  log->info(info.portName());
 }

// if(list.count() > 0)
//  serial = new QSerialPort(list.at(0));
// else
 connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(OnError()));

 this->portName = serial->portName();
 bOpened = serial->open(mode);
 if(!bOpened)
 {
  log->error(tr("Can't open serial port %1, error %2").arg(portName).arg(serial->errorString()));

  emit error(tr("Can't open serial port %1, error %2").arg(portName).arg(serial->errorString()));
  return false;
 }

 log->info(serial->errorString());
 QSerialPortInfo inf = QSerialPortInfo(portName);
 log->info(inf.isBusy()?"busy":"not busy");
 // Setup input and output streams

 //xmtTimer();
 istream = new QDataStream(serial);

 // now do the output
 ostream = new QDataStream(serial);
 //ostream = istream;
 serial->clear();

 return true;
}

//void SerialPort::dataReady()
//{
// QByteArray ba = serial->readAll();
// foreach(const char c, ba)
//  istream->writeBytes(&c,1);
//}
//void SerialPort::xmtTimer()
//{
// while(!ostream->atEnd())
// {
//  char* bytes;
//  uint iRead;
//  ostream->readBytes(bytes, iRead );
//  serial->write(bytes, iRead);
// }
// QTimer::singleShot(50, this, SLOT(xmtTimer()));
//}

//void SerialPort::dataReady()
//{
//  LnPacketizer::dataAvailable->wakeAll();
//}

int SerialPort::databits()
{
 int db = serial->dataBits();
 switch(db)
 {
  case QSerialPort::Data8:
   return 8;
  case QSerialPort::Data7:
   return 7;
 case QSerialPort::Data6:
   return 6;
  default:
   break;
 }
 return -1;
}
QString SerialPort::stopBits()
{
 int sb = serial->stopBits();
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
QString SerialPort::parity()
{
 int p = serial->parity();
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
void SerialPort::OnDataReady()
{
 log->info("Data ready");
}

qint32 SerialPort::getBaudRate()
{
 return serial->baudRate();
}

qint32 SerialPort::getReceiveTimeout()
{
 return rcvTimeout;
}

void SerialPort::enableReceiveTimeout(qint32 value) {rcvTimeout=value;}

QSerialPort* SerialPort::device() { return serial;}

bool SerialPort::isReceiveTimeoutEnabled() {return rcvTimeout != 0;}

QSerialPort::SerialPortError SerialPort::lastError() {return serial->error();}
