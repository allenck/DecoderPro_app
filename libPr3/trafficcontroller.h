#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "commandstation.h"

class Logger;
class AbstractSerialPortController;
class DirectSystemConnectionMemo;
class TrafficController : public QObject, public CommandStation
{
  Q_INTERFACES(CommandStation)
 public:
  /*public*/ TrafficController(DirectSystemConnectionMemo* memo, QObject* parent=0);
  QT_DEPRECATED     static /*public*/ TrafficController* instance();
  /*public*/ bool sendPacket(QByteArray packet, int repeats);
  /*public*/ bool status();
  /*public*/ void connectPort(AbstractSerialPortController* p);
  /*public*/ void disconnectPort(AbstractSerialPortController* p);
  /*public*/ QString getUserName() override;
  /*public*/ QString getSystemPrefix() override;

 private:
  // methods to connect/disconnect to a source of data in an AbstractSerialPortController
  /*private*/ DirectSystemConnectionMemo* _memo = nullptr;
  /*private*/ AbstractSerialPortController* controller = nullptr;
  static Logger* log;

 protected:
  // data members to hold the streams
  /*protected*/ QDataStream* istream = nullptr;
  /*protected*/ QDataStream* ostream = nullptr;
};

#endif // TRAFFICCONTROLLER_H
