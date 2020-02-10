#ifndef SERIALDRIVERADAPTER_H
#define SERIALDRIVERADAPTER_H
#include "sprogportcontroller.h"
#include "serialport.h"
#include "sprogconstants.h"
#include "sprogtype.h"
#include "serialport.h"

namespace Sprog
{
 class SerialDriverAdapter : public SprogPortController
 {
  Q_OBJECT
 public:
  SerialDriverAdapter(QObject* parent = 0);
  /*public*/ SerialDriverAdapter(SprogConstants::SprogMode sm, QObject* parent=0);
  /*public*/ SerialDriverAdapter(SprogConstants::SprogMode sm, int baud, SprogType* type, QObject* parent = 0);
  /*public*/ SerialDriverAdapter(SprogConstants::SprogMode sm, int baud, QObject* parent = 0);
  /*public*/ QString openPort(QString portName, QString appName);
  QT_DEPRECATED static /*public*/ SerialDriverAdapter* instance();
  /*public*/ void setHandshake(QSerialPort::FlowControl mode);
  /*public*/ QDataStream* getInputStream();
  /*public*/ QDataStream* getOutputStream();
  /*public*/ void configure();
  /*public*/ void dispose();
  /*public*/ QString className();


 public slots:
  void handleError(QSerialPort::SerialPortError);
  void writeData(QByteArray bytes);
  void bytesWritten(qint64);

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SerialDriverAdapter");
  QSerialPort* activeSerialPort;// = null;

  /*private*/ qint32 baudRate;// = -1;
  void common();
  QDataStream* serialStream;// = NULL;
  QString stopBits();
  QString parity();
  QString flowControl();
   //int f = activeSerialPort->flowControl();
  friend class SprogTrafficController;
  friend class SprogRcvWorker;
 };
}
#endif // SERIALDRIVERADAPTER_H
