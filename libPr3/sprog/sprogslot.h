#ifndef SPROGSLOT_H
#define SPROGSLOT_H

#include <QObject>
#include <QByteArray>
#include "dcclocoaddress.h"
#include "nmrapacket.h"

class Logger;
namespace Sprog
{
 class SprogSlot : public QObject
 {
  Q_OBJECT
 public:
  explicit SprogSlot(int i, QObject *parent = nullptr);
 /*public*/ bool isF0to4Packet();
 /*public*/ bool isF5to8Packet();
 /*public*/ bool isF9to12Packet();
  /*public*/ void set(int address, QByteArray payload, int repeat) ;
  /*public*/ void setAccessoryPacket(int address, bool closed, int repeats);
  /*public*/ bool isSpeedPacket();
  /*public*/ void setSpeed(int mode, int address, bool isLongAddress, int speed, bool forward) ;
  /*public*/ void setOps(int address, bool longAddr, int cv, int val) ;
  /*public*/ void f5to8packet(int address, bool isLongAddress,
          bool f5, bool f5Momentary,
          bool f6, bool f6Momentary,
          bool f7, bool f7Momentary,
          bool f8, bool f8Momentary) ;
  /*public*/ void f9to12packet(int address, bool isLongAddress,
          bool f9, bool f9Momentary,
          bool f10, bool f10Momentary,
          bool f11, bool f11Momentary,
          bool f12, bool f12Momentary) ;
  /*public*/ void f0to4packet(int address, bool isLongAddress,
          bool f0, bool f0Momentary,
          bool f1, bool f1Momentary,
          bool f2, bool f2Momentary,
          bool f3, bool f3Momentary,
          bool f4, bool f4Momentary);
  /*public*/ bool isFinished();
  /*public*/ void eStop();
  /*public*/ void clear();
  /*public*/ bool isLongAddress() ;
  /*public*/ bool isFree();
  /*public*/ int slotStatus();
  /*public*/ int getRepeat();
  /*public*/ void setRepeat(int r);
  /*public*/ int speed();
  /*public*/ int locoAddr();
  /*public*/ int getAddr();
  /*public*/ void setAddr(int a);
  /*public*/ bool getIsLong();
  /*public*/ void setIsLong(bool a);
  /*public*/ bool isForward() ;
  /*public*/ bool isOpsPkt();
  /*public*/ bool isActiveAddressMatch(DccLocoAddress* address);
  /*public*/ QByteArray getPayload();
  /*public*/ int getSlotNumber();
  /*public*/ long getLastUpdateTime();

 signals:

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogSlot");
  /*private*/ bool speedPacket;// = false;
  /*private*/ int speedMode;// = DccThrottle.SpeedStepMode128;
  /*private*/ QByteArray payload;
  // repeat of -1 is a persistent entry, ie a loco slot
  /*private*/ int repeat;
  /*private*/ int addr;
  /*private*/ bool isLong;
  /*private*/ int spd;
  /*private*/ bool forward;
  /*private*/ int status;
  /*private*/ int slot;
  /*private*/ bool opsPkt;
  /*private*/ bool f0to4Packet;// = false;
  /*private*/ bool f5to8Packet;// = false;
  /*private*/ bool f9to12Packet;// = false;

  /*private*/ bool repeatF0;// = false;
  /*private*/ bool repeatF1;// = false;
  /*private*/ bool repeatF2;// = false;
  /*private*/ bool repeatF3;// = false;
  /*private*/ bool repeatF4;// = false;
  /*private*/ bool repeatF5;// = false;
  /*private*/ bool repeatF6;// = false;
  /*private*/ bool repeatF7;// = false;
  /*private*/ bool repeatF8;// = false;
  /*private*/ bool repeatF9;// = false;
  /*private*/ bool repeatF10;// = false;
  /*private*/ bool repeatF11;// = false;
  /*private*/ bool repeatF12;// = false;
  /*private*/ int doRepeat();
  /*private*/ int getPayloadLength();
  /*private*/ long lastUpdateTime; // Time of last update for detecting stale slots
  /*private*/ int addressFromPacket();

 public slots:
 };
}
#endif // SPROGSLOT_H
