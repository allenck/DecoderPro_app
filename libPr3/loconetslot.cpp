#include "loconetslot.h"
#include "lnconstants.h"
#include "Throttle/throttlewindow.h"

LocoNetSlot::LocoNetSlot(int slotNum, QObject *parent) :
    QObject(parent)
{
  log = new Logger("LocoNetSlot");
  slot = slotNum;
  localF9 = false;
  localF10 = false;
  localF11 = false;
  localF12 = false;
  localF13 = false;
  localF14 = false;
  localF15 = false;
  localF16 = false;
  localF17 = false;
  localF18 = false;
  localF19 = false;
  localF20 = false;
  localF21 = false;
  localF22 = false;
  localF23 = false;
  localF24 = false;
  localF25 = false;
  localF26 = false;
  localF27 = false;
  localF28 = false;
  trk = 7;
  stat = 0;	// <STAT> is the status of the slot
  addr = 0;	// full address of the loco, made from
  //    <ADDR> is the low 7 (0-6) bits of the Loco address
  //    <ADD2> is the high 7 bits (7-13) of the 14-bit loco address
  spd = 0;	// <SPD> is the current speed (0-127)
  _dirf = 0;	// <DIRF> is the current Direction and the setting for functions F0-F4
  trk = 0;	// <TRK> is the global track status
  _ss2 = 0;	// <SS2> is the an additional slot status
  _snd = 0; 	// <SND> is the settings for functions F5-F8
  _id = 0;  // throttle id, made from
  //     <ID1> and <ID2> normally identify the throttle controlling the loco

}
// methods to interact with LocoNet
//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
void LocoNetSlot::setSlot(LocoNetMessage* l)// throws LocoNetException
{ // exception if message can't be parsed
    // sort out valid messages, handle
    switch (l->getOpCode()) {
    case LnConstants::OPC_SL_RD_DATA:
      lastUpdateTime = QDateTime::currentDateTime();
      //fall through
    case LnConstants::OPC_WR_SL_DATA: {
        if ( l->getElement(1) != 0x0E ) return;  // not an appropriate reply
        // valid, so fill contents
        if (slot != l->getElement(2))
            log->error(QString("Asked to handle message not for this slot (%1) ").arg(slot));
        stat = l->getElement(3);
        _pcmd = l->getElement(4);
        addr = l->getElement(4)+128*l->getElement(9);
        spd =  l->getElement(5);
        _dirf = l->getElement(6);
        trk =  l->getElement(7);
        _ss2 =  l->getElement(8);
        // item 9 is in add2
        _snd =  l->getElement(10);
        _id =   l->getElement(11)+128*l->getElement(12);

        notifySlotListeners();
        return;
    }
    case LnConstants::OPC_SLOT_STAT1:
        if (slot != l->getElement(1))
            log->error(QString("Asked to handle message not for this slot %1").arg(l->getElement(1)));
        stat = l->getElement(2);
        notifySlotListeners();
        lastUpdateTime = QDateTime::currentDateTime() ;
        return;
    case LnConstants::OPC_LOCO_SND: {
        // set sound functions in slot - first, clear bits
        _snd &= ~(LnConstants::SND_F5 | LnConstants::SND_F6
                 | LnConstants::SND_F7 | LnConstants::SND_F8);
        // and set them as masked
        _snd |= ((LnConstants::SND_F5 | LnConstants::SND_F6
                 | LnConstants::SND_F7 | LnConstants::SND_F8) & l->getElement(2));
        notifySlotListeners();
        lastUpdateTime = QDateTime::currentDateTime() ;
        return;
    }
    case  LnConstants::OPC_LOCO_DIRF: {
        // set direction, functions in slot - first, clear bits
        _dirf &= ~(LnConstants::DIRF_DIR | LnConstants::DIRF_F0
                  | LnConstants::DIRF_F1 | LnConstants::DIRF_F2
                  | LnConstants::DIRF_F3 | LnConstants::DIRF_F4);
        // and set them as masked
        _dirf += ((LnConstants::DIRF_DIR | LnConstants::DIRF_F0
                  | LnConstants::DIRF_F1 | LnConstants::DIRF_F2
                  | LnConstants::DIRF_F3 | LnConstants::DIRF_F4) & l->getElement(2));
        notifySlotListeners();
        lastUpdateTime = QDateTime::currentDateTime() ;
        return;
    }
    case LnConstants::OPC_MOVE_SLOTS: {
        // change in slot status will be reported by the reply,
        // so don't need to do anything here (but could)
        lastUpdateTime = QDateTime::currentDateTime() ;
        return;
    }
    case LnConstants::OPC_LOCO_SPD: {
        // set speed
        spd  = l->getElement(2);
        notifySlotListeners();
        lastUpdateTime = QDateTime::currentDateTime() ;
        return;
    }
    default:
    {
//     throw new LocoNetException("message can't be parsed");
      emit LocoNetException("message can't be parsed");
    }
 }
}

/**
 * Load functions 9 through 28 from loconet "Set Direct"
 * message.
 */
void LocoNetSlot::functionMessage(long pkt)
{
    // parse for which set of functions
    if ( (pkt&0xFFFFFF0) == 0xA0) {
        // F9-12
        localF9  = ((pkt&0x01) != 0);
        localF10 = ((pkt&0x02) != 0);
        localF11 = ((pkt&0x04) != 0);
        localF12 = ((pkt&0x08) != 0);
        notifySlotListeners();
    } else if ( (pkt&0xFFFFFF00) == 0xDE00) {
        // check F13-20
        localF13 = ((pkt&0x01) != 0);
        localF14 = ((pkt&0x02) != 0);
        localF15 = ((pkt&0x04) != 0);
        localF16 = ((pkt&0x08) != 0);
        localF17 = ((pkt&0x10) != 0);
        localF18 = ((pkt&0x20) != 0);
        localF19 = ((pkt&0x40) != 0);
        localF20 = ((pkt&0x80) != 0);
        notifySlotListeners();
    } else if ( (pkt&0xFFFFFF00) == 0xDF00) {
        // check F21-28
        localF21 = ((pkt&0x01) != 0);
        localF22 = ((pkt&0x02) != 0);
        localF23 = ((pkt&0x04) != 0);
        localF24 = ((pkt&0x08) != 0);
        localF25 = ((pkt&0x10) != 0);
        localF26 = ((pkt&0x20) != 0);
        localF27 = ((pkt&0x40) != 0);
        localF28 = ((pkt&0x80) != 0);
        notifySlotListeners();
    }
}

/**
 * Update the decoder type bits in STAT1 (D2, D1, D0)
 * @param status New values for STAT1 (D2, D1, D0)
 * @return Formatted LocoNet message to change value.
 */
LocoNetMessage* LocoNetSlot::writeMode(int status)
{
    LocoNetMessage* l = new LocoNetMessage(4);
    l->setOpCode( LnConstants::OPC_SLOT_STAT1 );
    l->setElement(1, slot);
    l->setElement(2, (stat&~LnConstants::DEC_MODE_MASK)|status);
    return l;
}

/**
 * Update the status mode bits in STAT1 (D5, D4)
 * @param status New values for STAT1 (D5, D4)
 * @return Formatted LocoNet message to change value.
 */
LocoNetMessage*  LocoNetSlot::writeStatus(int status)
{
    LocoNetMessage* l = new LocoNetMessage(4);
    l->setOpCode( LnConstants::OPC_SLOT_STAT1 );
    l->setElement(1, slot);
    l->setElement(2, (stat&~LnConstants::LOCOSTAT_MASK)|status);
    return l;
}

LocoNetMessage* LocoNetSlot::dispatchSlot()
{
    LocoNetMessage* l = new LocoNetMessage(4);
    l->setOpCode( LnConstants::OPC_MOVE_SLOTS );
    l->setElement(1, slot);
    l->setElement(2, 0);
    return l;
}

LocoNetMessage* LocoNetSlot::writeSlot() {
    LocoNetMessage* l = new LocoNetMessage(14);
    l->setOpCode( LnConstants::OPC_WR_SL_DATA );
    l->setElement(1, 0x0E);
    l->setElement(2, slot & 0x7F);
    l->setElement(3, stat & 0x7F);
    l->setElement(4, addr & 0x7F); l->setElement(9, (addr/128)&0x7F);
    l->setElement(5, spd & 0x7F);
    l->setElement(6, _dirf & 0x7F);
    l->setElement(7, trk & 0x7F);
    l->setElement(8, _ss2 & 0x7F);
    // item 9 is add2
    l->setElement(10, _snd & 0x7F);
    l->setElement(11, _id&0x7F); l->setElement(12, (_id/128)&0x7F );
    return l;
}


/*public*/ /*synchronized*/ void LocoNetSlot::addSlotListener(SlotListener* l)
{
    QMutexLocker locker(&mutex);
    // add only if not already registered
    if (!slotListeners.contains(l))
    {
        slotListeners.append(l);
    }
}

/*public*/ /*synchronized*/ void LocoNetSlot::removeSlotListener(SlotListener* l)
{
    QMutexLocker locker(&mutex);
    if (slotListeners.contains(l)) {
        slotListeners.remove(slotListeners.indexOf(l));
    }
}


void LocoNetSlot::notifySlotListeners()
{
 // make a copy of the listener list to synchronized not needed for transmit
 QVector<SlotListener*>* v  = new QVector<SlotListener*>(slotListeners);
//    synchronized(this)
//        {
//            v = new ArrayList<SlotListener>(slotListeners);
//        }
 if (log->isDebugEnabled()) log->debug(QString("notify %1 SlotListeners").arg(v->size()));
 // forward to all listeners
 int cnt = v->size();
 for (int i=0; i < cnt; i++)
 {
  SlotListener* client = v->at(i);
  if(qobject_cast<ThrottleWindow*>(client)!= NULL)
   ((ThrottleWindow*)client)->notifyChangedSlot(this);
  else
  if(qobject_cast<LocoNetThrottle*>(client)!= NULL)
   ((LocoNetThrottle*)client)->notifyChangedSlot(this);
  else
  {
   client->notifyChangedSlot(this);
   log->debug(tr("Unhandled SlotListener '%1'").arg(client->metaObject()->className()));
  }
 }
}

/**
 * Only valid for fast-clock slot.
 * @return "Days" value currently in fast-clock slot.
 */
int LocoNetSlot::getFcDays() {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("getFcDays invalid for slot "+getSlot());
    return (addr&0x3f80)/0x80;
}
/**
 * For fast-clock slot, set "days" value.
 */
void LocoNetSlot::setFcDays(int val) {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("setFcDays invalid for slot "+getSlot());
    addr = val*128+(addr&0x7f);
}

/**
 * Only valid for fast-clock slot.
 * @return "Hours" value currently stored in fast clock slot.
 */
int LocoNetSlot::getFcHours() {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("getFcHours invalid for slot "+getSlot());
    int temp = ((256-_ss2) &0x7F) % 24;
    return (24 - temp) % 24;
}
/**
 * For fast-clock slot, set "hours" value.
 */
void LocoNetSlot::setFcHours(int val) {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("setFcHours invalid for slot "+getSlot());
    _ss2 = (256-(24-val))&0x7F;
}

/**
 * Only valid for fast-clock slot.
 * @return Return minutes value currently stored in the fast clock slot.
 */
int LocoNetSlot::getFcMinutes()
{
    if (getSlot()!=LnConstants::FC_SLOT) log->error("getFcMinutes invalid for slot "+getSlot());
    int temp = ((255-_dirf) & 0x7F) % 60;
    return (60-temp)% 60;
}
/**
 * For fast-clock slot, set "minutes" value.
 */
void LocoNetSlot::setFcMinutes(int val) {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("setFcMinutes invalid for slot "+getSlot());
    _dirf = (255-(60-val))&0x7F;
}

/**
 * Only valid for fast-clock slot.
 * @return Return frac_mins field which is the number of 65ms ticks until then
 * next minute rollover. These ticks step at the current fast clock rate
 */
int LocoNetSlot::getFcFracMins() {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("getFcMinutes invalid for slot "+getSlot());
    return 0x3FFF - ( (addr & 0x7F) | ((spd & 0x7F ) << 7 ) ) ;
}
/**
 * For fast-clock slot, set "frac_mins" value.
 */
void LocoNetSlot::setFcFracMins(int val) {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("setFcMinutes invalid for slot "+getSlot());
    int temp = 0x3FFF - val ;
    addr = addr | (temp & 0x7F);
    spd = ( temp >> 7 ) & 0x7F;
}

/**
 * Only valid for fast-clock slot.
 * @return Rate stored in fast clock slot.
 */
int LocoNetSlot::getFcRate() {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("getFcMinutes invalid for slot "+getSlot());
    return stat;
}
/**
 * For fast-clock slot, set "rate" value.
 */
void LocoNetSlot::setFcRate(int val) {
    if (getSlot()!=LnConstants::FC_SLOT) log->error("setFcMinutes invalid for slot "+getSlot());
    stat = val & 0x7F;
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoNetSlot.class.getName());
