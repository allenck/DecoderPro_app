#ifndef LNCVDEVICESMANAGER_H
#define LNCVDEVICESMANAGER_H

#include <QObject>
#include "propertychangesupport.h"

class ProgrammingTool;
class LncvDevice;
class LocoNetMessage;
class LncvDevices;
class Logger;
class LocoNetSystemConnectionMemo;
class LncvDevicesManager : public PropertyChangeSupport
{
  Q_OBJECT
  //Q_INTERFACES(PropertyChangeListener)
 public:
  /*public*/ LncvDevicesManager(LocoNetSystemConnectionMemo* memo, QObject *parent = nullptr);
  /*public*/ enum ProgrammingResult {
      SUCCESS_PROGRAMMER_OPENED,
      FAIL_NO_SUCH_DEVICE,
      FAIL_NO_APPROPRIATE_PROGRAMMER,
      FAIL_NO_MATCHING_ROSTER_ENTRY,
      FAIL_DESTINATION_ADDRESS_IS_ZERO,
      FAIL_MULTIPLE_DEVICES_SAME_DESTINATION_ADDRESS,
      FAIL_NO_ADDRESSED_PROGRAMMER,
      FAIL_NO_LNCV_PROGRAMMER
  };
  /*public*/ bool deviceExists(LncvDevice* d);
  /*public*/ LncvDevice* getDevice(int art, int addr);
  /*public*/ LncvDevices* getDeviceList();
  /*public*/ int getDeviceCount();
  /*public*/ void clearDevicesList();
  /*public*/ void sendLncvDiscoveryRequest();
  /*public*/ void message(LocoNetMessage* m);
  /*public*/ ProgrammingResult prepareForSymbolicProgrammer(LncvDevice* dev, ProgrammingTool* t);
//  /*public*/ void addPropertyChangeListener(PropertyChangeListener*l);
//  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l);

 signals:

 public slots:

 private:
  static Logger* log;
  /*private*/ /*final*/ LocoNetSystemConnectionMemo* memo;
  /*private*/ /*final*/ LncvDevices* lncvDevices;
};

#endif // LNCVDEVICESMANAGER_H
