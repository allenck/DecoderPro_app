#ifndef SPROGCOMMANDSTATION_H
#define SPROGCOMMANDSTATION_H
#include "commandstation.h"
#include <QLinkedList>
#include "sprogtrafficcontroller.h"
#include "sprogsystemconnectionmemo.h"
#include "dcclocoaddress.h"
#include "sprogslotlistener.h"

class Logger;
namespace Sprog
{
 class SprogSystemConnectionMemo;
 class SprogTrafficController;
 class SprogSlot;
 class SprogCommandStation : public CommandStation
 {
  Q_OBJECT
 public:
  SprogCommandStation(SprogTrafficController* controller, QObject* parent= 0);

  /*public*/ void setSystemConnectionMemo(SprogSystemConnectionMemo* memo);
  /*public*/ QString getUserName();
  /*public*/ bool sendPacket(QByteArray packet, int repeats);
  /*public*/ SprogSlot* slot(const int i);
  /*public*/ int getInUseCount();
  /*public*/ bool isBusy();
  /*public*/ void forwardCommandChangeToLayout(int address, bool closed);
  /*public*/ void function0Through4Packet(DccLocoAddress* address,
          bool f0, bool f0Momentary,
          bool f1, bool f1Momentary,
          bool f2, bool f2Momentary,
          bool f3, bool f3Momentary,
          bool f4, bool f4Momentary);
  /*public*/ void function5Through8Packet(DccLocoAddress* address,
          bool f5, bool f5Momentary,
          bool f6, bool f6Momentary,
          bool f7, bool f7Momentary,
          bool f8, bool f8Momentary);
  /*public*/ void function9Through12Packet(DccLocoAddress* address,
          bool f9, bool f9Momentary,
          bool f10, bool f10Momentary,
          bool f11, bool f11Momentary,
          bool f12, bool f12Momentary);
  /*public*/ void setSpeed(int mode, DccLocoAddress* address, int spd, bool isForward) ;
  /*public*/ SprogSlot* opsModepacket(int address, bool longAddr, int cv, int val) ;
  /*public*/ void release(DccLocoAddress* address);
  /*public*/ void estopAll();
  QT_DEPRECATED
  /*public*/ /*final*/ SprogCommandStation* instance();
  /*public*/ /*synchronized*/ void addSlotListener(SprogSlotListener* l);
  /*public*/ /*synchronized*/ void removeSlotListener(SprogSlotListener* l);
  /*public*/ QString getSystemPrefix();


 signals:
  void notifyChangedSlot(SprogSlot*);
  void finished();

 public slots:
  /*public*/ void notifyMessage(SprogMessage* m);
  /*public*/ void notifyReply(SprogReply* m);
  /*public*/ void run();


 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogCommandStation");
  SprogSystemConnectionMemo* adaptermemo;
  // data members to hold contact with the slot listeners
  /*final*/ /*private*/ QVector<SprogSlotListener*>* slotListeners;// = new Vector<>();
  /*private*/ SprogTrafficController* tc;// = null;
  /*final*/ QObject* lock;// = new Object();
  /*final*/ QObject* lock2;// = new Object();
  /*private*/ SprogReply* reply;
  /*private*/ bool waitingForReply = false;
  /*private*/ bool replyAvailable = false;
  /*private*/ bool sendSprogAddress = false;
  /*private*/ long time, timeNow, packetDelay;
  /*final*/ static int MAX_PACKET_DELAY;// = 25;
  /*private*/ int lastId;
  /*private*/ void clearAllSlots();
  /*private*/ SprogSlot* findAddress(DccLocoAddress* address);
  /*private*/ SprogSlot* findAddressSpeedPacket(DccLocoAddress* address);
  /*private*/ SprogSlot* findF0to4Packet(DccLocoAddress* address);
  /*private*/ SprogSlot* findF5to8Packet(DccLocoAddress* address);
  /*private*/ SprogSlot* findF9to12Packet(DccLocoAddress* address);
  /*private*/ int statusDue;// = 0;
  /*private*/ /*synchronized*/ void notifySlotListeners(SprogSlot* s);
  /*private*/ QByteArray getNextPacket();

 protected:
   /*protected*/ int currentSlot;// = 0;
   /*protected*/ int currentSprogAddress;//= -1;

   /*protected*/ QLinkedList<SprogSlot*>* _slots;
   /*protected*/ QQueue<SprogSlot*>* sendNow;
   /*protected*/ void sendMessage(SprogMessage* m);
   /*protected*/ SprogSlot* findFree();
   /*protected*/ void eStopSlot(SprogSlot* s) ;

 };
}
#endif // SPROGCOMMANDSTATION_H
