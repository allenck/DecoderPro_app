#ifndef LNIPLIMPLEMENTATION_H
#define LNIPLIMPLEMENTATION_H
#include "jcomponent.h"
#include "loconetlistener.h"
#include "timer.h"

/*public*/ class DeviceTypes {
  //Q_OBJECT
 public:
  enum TYPES
  {
   UT4D,
   UT4X,
   DCS51,
   DCS52,
   DT402D,
   DT402X,
   PR3,
   UR92,
   DB210OPTO,
   DB210,
   DB220,
   PR4,
   BXP88,
   LNWI,
   DCS210,
   DCS240,
   DT500D,
   DT500X,
   DT602X,
   BXPA1,
   DCS210plus,
   RR_CKTS_TC64,
   RR_CKTS_TC_MKII,
   RR_CKTS_LNCP,
   RR_CKTS_MOTORMan,
   RR_CKTS_MOTORMANII,
   RR_CKTS_SIGNALMAN,
   RR_CKTS_TOWERMAN,
   RR_CKTS_WATCHMAN
  };
private:
    /*private*/ int manufacturer;
    /*private*/ int deviceIdNumber;
    /*private*/ int slaveManufacturer;
    /*private*/ int slaveDeviceIdNumber;
    /*private*/ QString manufacturerName;
    /*private*/ QString deviceName;

    /*private*/ DeviceTypes(int mfg, int devId, int slaveMfg, int slaveDevId,
            QString mfgName, QString devName) {
        this->manufacturer = mfg & 0x7f;
        this->deviceIdNumber = devId & 0x7f;
        this->slaveManufacturer = slaveMfg & 0x7f;
        this->slaveDeviceIdNumber = slaveDevId & 0x7f;
        this->manufacturerName = mfgName;
        this->deviceName = devName;
    }
    /*public*/ /*final*/ int getManufacturer() {
        return manufacturer;
    }
    /*public*/ /*final*/ int getDeviceIdNumber() {
        return deviceIdNumber;
    }
    /*public*/ /*final*/ int getSlaveManufacturer() {
        return slaveManufacturer;
    }
    /*public*/ /*final*/ int getSlaveDeviceIdNumber() {
        return slaveDeviceIdNumber;
    }
    /*public*/ /*final*/ bool isDeviceMatch(int mfg, int devId, int slaveMfg, int slaveDevId) {
        return (mfg==manufacturer) && (devId == deviceIdNumber) &&
                (slaveMfg == slaveManufacturer) && (slaveDevId == slaveDeviceIdNumber);
    }
    /*public*/ /*final*/ bool isDeviceMatch(int mfg, int devId) {
        return isDeviceMatch(mfg, devId, 0, 0);
    }
    /*public*/ /*final*/ QString getManufacturerName() {
        return manufacturerName;
    }
    /*public*/ /*final*/ QString getDeviceName() {
        return deviceName;
    }
};

class LnTrafficController;
class LocoNetSystemConnectionMemo;
class LnIPLImplementation : public QObject, public JComponent, public LocoNetListener
{
  Q_OBJECT
  Q_INTERFACES(LocoNetListener JComponent)
 public:
  LnIPLImplementation(LocoNetSystemConnectionMemo* lnMemo, QObject* parent = nullptr);
  QObject* self() {return (QObject*)this;}
  /*public*/ static /*final*/ LocoNetMessage* createQueryAllIplDevicesPacket();
  /*public*/ void sendIplQueryAllDevices();

  /*public*/ void connect(LnTrafficController* t);

  /*public*/ static QString getManufacturer(int manuf);
  /*public*/ static QString getDeviceName(int manuf, int device, int slaveManuf, int slave);

 private:
  /*private*/ bool waitingForIplReply;
  /*private*/ void moreInit();
  LnIPLImplementation* thisone;
  LocoNetSystemConnectionMemo* memo;
  /*private*/ Timer* swingTmrIplQuery;

};

#endif // LNIPLIMPLEMENTATION_H
