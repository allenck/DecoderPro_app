#ifndef LNIPLIMPLEMENTATION_H
#define LNIPLIMPLEMENTATION_H
#include "jcomponent.h"
#include "loconetlistener.h"
#include "timer.h"
#include "swingpropertychangesupport.h"

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
public:
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
  /*public*/ static /*final*/ LocoNetMessage* createIplSpecificHostQueryPacket(
    int hostMfr,
    int hostDevice);
  /*public*/ static /*final*/ LocoNetMessage* createIplSpecificSlaveQueryPacket(
    int slaveMfr,
    int slaveDevice);
  /*public*/ static /*final*/ LocoNetMessage* createIplSpecificSlaveQueryPacket(
          int hostMfr,
          int hostDevice,
          int slaveMfr,
          int slaveDevice);
  /*public*/ static /*final*/ LocoNetMessage* createIplUr92QueryPacket();
  /*public*/ static /*final*/ LocoNetMessage* createIplDt402QueryPacket();
  /*public*/ static /*final*/ LocoNetMessage* createIplUt4QueryPacket();
  /*public*/ static /*final*/ LocoNetMessage* createIplDcs51QueryPacket();
  /*public*/ static /*final*/ LocoNetMessage* createIplDcs52QueryPacket();
  /*public*/ static /*final*/ LocoNetMessage* createIplPr3QueryPacket();
  /*public*/ static /*final*/ bool isIplIdentityQueryMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplSpecificIdentityReportMessage(LocoNetMessage* m,
          int hostMfr, int hostDevice);
  /*public*/ static /*final*/ bool isIplUr92IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDt402IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplUt4IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDcs51IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDcs52IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplPr3IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDt402DIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplUt4DIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplPr4IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplBxp88IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplLnwiIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDcs240IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDcs210IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDcs210PlusIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDt500DIdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ bool isIplDt500IdentityReportMessage(LocoNetMessage* m);
  /*public*/ static /*final*/ QString extractInterpretedIplHostDevice(LocoNetMessage* m);
  /*public*/ static /*final*/ QString extractInterpretedIplSlaveDevice(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentityHostManufacturer(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentityHostDevice(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentitySlaveManufacturer(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentitySlaveDevice(LocoNetMessage* m);
  /*public*/ static /*final*/ QString extractIplIdentityHostFrimwareRev(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentityHostFrimwareRevNum(LocoNetMessage* m);
  /*public*/ static /*final*/ int extractIplIdentitySlaveFrimwareRevNum(LocoNetMessage* m);
  /*public*/ static /*final*/ QString extractIplIdentitySlaveFrimwareRev(LocoNetMessage* m);
  /*public*/ static /*final*/ long extractIplIdentityHostSerialNumber(LocoNetMessage* m);
  /*public*/ static /*final*/ long extractIplIdentitySlaveSerialNumber(LocoNetMessage* m);
  /*public*/ static /*final*/ QString interpretHostManufacturerDevice(int hostMfr, int hostDevice,
          int slaveMfr, int slaveDevice);
  /*public*/ static /*final*/ QString interpretHostManufacturerDevice(int hostMfr, int hostDevice);
  /*public*/ static /*final*/ QString interpretSlaveManufacturerDevice(int slaveMfr, int slaveDevice);
  /*public*/ void connect(LnTrafficController* t);
  /*public*/ void dispose();
  /*public*/ void message(LocoNetMessage* m)override;
  /*public*/ bool isIplQueryTimerRunning();
  /*public*/ static bool isValidMfgDevice(int mfg, int deviceType);
  /*public*/ static QString getManufacturer(int manuf);
  /*public*/ static QString getDeviceName(int manuf, int device, int slaveManuf, int slave);

  /*public*/ bool isOpaque() override{return true;}
  /*public*/ QColor getForeground() override{return QColor();}
  /*public*/ QColor getBackground() override{return QColor();}
  /*public*/ void setBackground(QColor) override{}
  /*public*/ void setOpaque(bool) override{}
  /*public*/ QFont getFont() override{return QFont();}
  /*public*/ void setFont(QFont) override{}
  QWidget* jself() override{return (QWidget*)this;}
  /*public*/ void setBorder(Border*) override{}
  /*public*/ Border* getBorder() override{return nullptr;}
  /*public*/ void setEnabled(bool) override{}

 private:
  /*private*/ bool waitingForIplReply;
  /*private*/ void moreInit();
  LnIPLImplementation* thisone;
  LocoNetSystemConnectionMemo* memo;
  /*private*/ Timer* swingTmrIplQuery;
  /*private*/ bool handleMessageIplDeviceQuery(LocoNetMessage* m);
  /*private*/ static /*final*/ bool isIplRf24SlaveIdentityReportMessage(LocoNetMessage* m);
  /*private*/ bool handleMessageIplDeviceReport(LocoNetMessage* m);
  static QMap<DeviceTypes::TYPES, DeviceTypes*> deviceTypes;
  SwingPropertyChangeSupport* pcs;

  friend class SwingTmr;
  friend class LnIplImplementationTest;
  friend class IMPActionListener;
};

class SwingTmr : public Timer
{
  Q_OBJECT
  LnIPLImplementation* thisone;
public:
  SwingTmr(int interval, ActionListener* listener, LnIPLImplementation* thisone)
   : Timer(interval, listener)
  {this->thisone = thisone;}
  //@Override
 public slots:
  /*public*/ void actionPerformed(/*ActionEvent e*/) {
      thisone->swingTmrIplQuery->stop();
      thisone->waitingForIplReply = false;
      int oldvalue = 9999;
      int newvalue = 0;
      thisone->pcs->firePropertyChange("LnIPLEndOfDeviceQuery", oldvalue, newvalue); // NOI18N
  }
};

class IMPActionListener : public QObject, public ActionListener
{
  Q_OBJECT
  Q_INTERFACES(ActionListener)
  LnIPLImplementation* lnI;
 public:
  IMPActionListener(LnIPLImplementation* lnI) {this->lnI = lnI;}
  QObject* self() override{return (QObject*)this;}
 public slots:
  void actionPerformed(JActionEvent* =0) override
  {
   lnI->swingTmrIplQuery->stop();
   lnI->waitingForIplReply = false;
   int oldvalue = 9999;
   int newvalue = 0;
   lnI->pcs->firePropertyChange("LnIPLEndOfDeviceQuery", oldvalue, newvalue); // NOI18N

  }
};

#endif // LNIPLIMPLEMENTATION_H
