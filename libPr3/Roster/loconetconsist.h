#ifndef LOCONETCONSIST_H
#define LOCONETCONSIST_H
#include "dccconsist.h"
#include "slotmanager.h"

class LocoNetThrottle;
class LocoNetConsist : public DccConsist
{
 Q_OBJECT
public:
 /*public*/ LocoNetConsist(int address, LocoNetSystemConnectionMemo* lm, QObject* parent = nullptr);
 /*public*/ LocoNetConsist(DccLocoAddress* address, LocoNetSystemConnectionMemo* l, QObject* parent = nullptr);
 /*public*/ void dispose();
 /*public*/ void setConsistType(int consist_type)  ;
 /*public*/ bool isAddressAllowed(DccLocoAddress* address) ;
 /*public*/ int sizeLimit() const;
 /*public*/ bool contains(DccLocoAddress* address) ;
 /*public*/ bool getLocoDirection(DccLocoAddress* address) ;
 /*public*/ /*synchronized*/ void add(DccLocoAddress* LocoAddress, bool directionNormal) ;
 /*public*/ /*synchronized*/ void restore(DccLocoAddress* LocoAddress, bool directionNormal) ;
 /*public*/ /*synchronized*/ void remove(DccLocoAddress* LocoAddress)  ;
 /*public*/ /*synchronized*/ void removeFromCSConsist(DccLocoAddress* LocoAddress);

public slots:
 /*public*/ void notifyFailedThrottleRequest(LocoAddress* address, QString reason);
 /*public*/ void notifyChangedSlot(LocoNetSlot* s);
 /*public*/ void notifyThrottleFound(DccThrottle* t);
 /*public*/ void notifyStealThrottleRequired(LocoAddress* address);

private:
 /*private*/ SlotManager* slotManager;// = null;
 /*private*/ LnTrafficController* trafficController;// = null;
 /*private*/ AbstractThrottleManager* throttleManager;// = null;
 /*private*/ LocoNetSlot* leadSlot;// = null;
 /*private*/ QList<DccLocoAddress*> needToWrite;// = null;
 // State Machine states
 enum STATE
 {
  IDLESTATE = 0,
  LEADREQUESTSTATE = 1,
  LINKSTAGEONESTATE = 2,
  LINKSTAGETWOSTATE = 4,
  LINKSTAGETHREESTATE = 8,
  UNLINKSTAGEONESTATE = 16
 };
 /*private*/ int consistRequestState;// = IDLESTATE;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("LocoNetConsist");
 void common();
 /*private*/ /*synchronized*/ void addToConsistList(DccLocoAddress* LocoAddress, bool directionNormal);
 /*private*/ /*synchronized*/ void removeFromConsistList(DccLocoAddress* LocoAddress);
 /*private*/ /*synchronized*/ void delayedAdd();
 /*private*/ /*synchronized*/ void addToCSConsist(DccLocoAddress* LocoAddress, bool directionNormal);
 /*private*/ void linkSlots(LocoNetSlot* lead, LocoNetSlot* follow);
 /*private*/ void unlinkSlots(LocoNetSlot* lead, LocoNetSlot* follow);
 /*private*/ void setDirection(LocoNetThrottle* t);
 /*private*/ void setSlotModeAdvanced(LocoNetSlot* s);

protected:
 /*protected*/ /*synchronized*/ void addToAdvancedConsist(DccLocoAddress* LocoAddress, bool directionNormal);
 /*protected*/ /*synchronized*/ void removeFromAdvancedConsist(DccLocoAddress* LocoAddress);

};

#endif // LOCONETCONSIST_H
