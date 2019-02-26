#include "slotmanager.h"
#include "lnthrottlemanager.h"
//#include "../Tables/slotmonitor.h"
#include "LocoIO/lncommandstationtype.h"
#include "instancemanager.h"
#include "defaultprogrammermanager.h"
#include "programmingmode.h"
#include "csopswaccess.h"

/*final static protected*/ int SlotManager::NUM_SLOTS = 128;

SlotManager::SlotManager(LnTrafficController* tc, QObject *parent) : AbstractProgrammer(parent)
{
 this->tc = tc;
 log = new Logger("SlotManager");
 log->setDebugEnabled(false);
 log->setInfoEnabled(true);
 // need a longer LONG_TIMEOUT for Fleischman command stations
 // change timeout values from AbstractProgrammer superclass
 LONG_TIMEOUT = 180000;  // Fleischman command stations take forever
 SHORT_TIMEOUT = 8000;   // DCS240 reads
 lastMessage = -1;
 mCanRead = true;
 throttledTransmitter = nullptr;
 mTurnoutNoRetry = false;
 mProgPowersOff = false;
 mProgEndSequence = false;
 progState = 0;
 // 1 is commandPending
 // 2 is commandExecuting
 // 0 is notProgramming
 _progRead = false;
 _progConfirm = false;
 _confirmVal =0;
 mServiceMode = true;
 _usingProgrammer = nullptr;
 //_mode = Programmer::PAGEMODE;
 mPowerTimer = nullptr;
 nextReadSlot = 0;
 _slots.reserve(128);
 csOpSwProgrammingMode = new ProgrammingMode(
             "LOCONETCSOPSWMODE",
             tr("Command Station Op Switches"));
 postProgDelay = 100;


 loadSlots();

 // listen to the LocoNet
 tc->addLocoNetListener(~0, (LocoNetListener*)this);
 if(qobject_cast<LnPacketizer*>(tc))
 {
  LnPacketizer* pkt = (LnPacketizer*)tc;
  connect(pkt, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 else
  connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));

 // We will scan the slot table every 10 s for in-use slots that are stale
 staleSlotCheckTimer = new QTimer();
 staleSlotCheckTimer->setInterval( 10000);
// , new java.awt.event.ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//              checkStaleSlots();
//            }
//          }
//        );
 connect(staleSlotCheckTimer, SIGNAL(timeout()), this, SLOT(checkStaleSlots()));
 staleSlotCheckTimer->setSingleShot(false);
 staleSlotCheckTimer->setInterval( 30000 );
 staleSlotCheckTimer->start();
}

/*protected*/ void SlotManager::loadSlots()
{
 // initialize slot array
 for (int i=0; i<NUM_SLOTS; i++)
     _slots.append( new LocoNetSlot(i));
}

/**
 * Send a DCC packet to the rails. This implements the CommandStation interface.
 * @param packet
 */
void SlotManager::sendPacket(QByteArray packet, int sendCount)
{
 if (sendCount > 8)
 {
  log->warn(tr("Ops Mode Accessory Packet 'Send count' reduced from %1 to 8.").arg(sendCount)); // NOI18N
  sendCount = 8;
 }
 if (sendCount < 1)
 {
  log->warn(tr("Ops Mode Accessory Packet 'Send count' of %1 is illegal and is forced to 1.").arg(sendCount)); // NOI18N
  sendCount = 1;
 }
 if (packet.length() <= 1)
 {
  log->error("Invalid DCC packet length: " + QString::number(packet.length())); // NOI18N
 }
 if (packet.length() > 6)
 {
  log->error("DCC packet length is too great: %1 bytes were passed; ignoring the request. " + QString::number(packet.length())); // NOI18N
    }

    LocoNetMessage* m = new LocoNetMessage(11);
    m->setElement(0,LnConstants::OPC_IMM_PACKET);
    m->setElement(1,0x0B);
    m->setElement(2,0x7F);
    // the incoming packet includes a check byte that's not included in LocoNet packet
    int length = packet.length()-1;

    m->setElement(3, ((sendCount - 1) & 0x7) + 16 * (length & 0x7));

    int highBits = 0;
    if (length>=1 && ((packet[0]&0x80) != 0)) highBits |= 0x01;
    if (length>=2 && ((packet[1]&0x80) != 0)) highBits |= 0x02;
    if (length>=3 && ((packet[2]&0x80) != 0)) highBits |= 0x04;
    if (length>=4 && ((packet[3]&0x80) != 0)) highBits |= 0x08;
    if (length>=5 && ((packet[4]&0x80) != 0)) highBits |= 0x10;
    m->setElement(4,highBits);

    m->setElement(5,0);
    m->setElement(6,0);
    m->setElement(7,0);
    m->setElement(8,0);
    m->setElement(9,0);
    for (int i=0; i<packet.length()-1; i++) m->setElement(5+i, packet[i]&0x7F);

    if (throttledTransmitter != nullptr)
        throttledTransmitter->sendLocoNetMessage(m);
    else
     tc->sendLocoNetMessage(m);
}


/**
 * Access the information in a specific slot.  Note that this is a
 * mutable access, so that the information in the LocoNetSlot object
 * can be changed.
 * @param i  Specific slot, counted starting from zero.
 * @return   The Slot object
 */
LocoNetSlot* SlotManager::slot(const int i) {return _slots[i];}

/**
 * Obtain a slot for a particular loco address.
 * <P>This requires access to the command station, even if the
 * locomotive address appears in the current contents of the slot
 * array, to ensure that our local image is up-to-date.
 * <P>
 * This method sends an info request.  When the echo of this is
 * returned from the LocoNet, the
 * next slot-read is recognized as the response.
 * <P>
 * The object that's looking for this information must provide
 * a SlotListener to notify when the slot ID becomes available.
 * <P>
 * The SlotListener is not subscribed for slot notifications; it can
 * do that later if it wants.  We don't currently think that's a race
 * condition.
 * @param i  Specific slot, counted starting from zero.
 * @param l  The SlotListener to notify of the answer.
 */
void SlotManager::slotFromLocoAddress(int i, SlotListener* l)
{
 // store connection between this address and listener for later
//        mLocoAddrHash.insert(Integer.valueOf(i), l);
 mLocoAddrHash.insert(i, l);

 // send info request
 LocoNetMessage* m = new LocoNetMessage(4);
 m->setOpCode(LnConstants::OPC_LOCO_ADR);  // OPC_LOCO_ADR
 m->setElement(1, (i/128)&0x7F);
 m->setElement(2, i&0x7F);
 tc->sendLocoNetMessage(m);
}

/**
 * method to scan the slot array looking for slots that are in-use but have
 * not had any updates in over 90s and issue a read slot request to update
 * their state as the command station may have purged or stopped updating
 * the slot without telling us via a LocoNet message.
 *
 * This is intended to be called from the staleSlotCheckTimer
 */
void SlotManager::checkStaleSlots() // [slot]
{
  //long staleTimeout = QTime::currentTime() - 90000;
  QDateTime staleTimeout = QDateTime::currentDateTime();
  staleTimeout.addMSecs(-90000);
  LocoNetSlot* slot;

    // We will just check the normal loco slots 1 to 120
  for (int i = 1; i <= 120; i++) {
    slot = _slots[i];
    if ( (slot->slotStatus() == LnConstants::LOCO_IN_USE) &&
        (slot->getLastUpdateTime() <= staleTimeout))
      sendReadSlot(i);
  }
}

void SlotManager::addSlotListener(SlotListener* l) {
    // add only if not already registered
    if (!slotListeners.contains(l)) {
        slotListeners.append(l);
    }
}

void SlotManager::removeSlotListener(SlotListener* l) {
    if (slotListeners.contains(l)) {
        int i = slotListeners.indexOf(l);
        slotListeners.remove(i);
    }
}

/**
 * Trigger the notification of all SlotListeners.
 * @param s The changed slot to notify.
 */
//@SuppressWarnings("unchecked")
void SlotManager::notify(LocoNetSlot* s)
{
 // make a copy of the listener vector to synchronized not needed for transmit
 QVector<SlotListener*>* v = new QVector<SlotListener*>(slotListeners);
//    synchronized(this)
//        {
//            v = (Vector<SlotListener>) slotListeners.clone();
//        }
 if (log->isDebugEnabled()) log->debug(QString("notify %1 SlotListeners about slot %2").arg(v->size()).arg(s->getSlot()));
 // forward to all listeners
 foreach(SlotListener* l, *v)
 {
  connect(this, SIGNAL(changedSlot(LocoNetSlot*)), l, SLOT(notifyChangedSlot(LocoNetSlot*)));
 emit changedSlot(s);
  disconnect(this, SIGNAL(changedSlot(LocoNetSlot*)), l, SLOT(notifyChangedSlot(LocoNetSlot*)));
}
#if 0
    int cnt = v->size();
    for (int i=0; i < cnt; i++)
    {
        SlotListener* client = v->at(i);
        if(qobject_cast<SlotMonitor*>(client) != nullptr)
            ((SlotMonitor*)client)->notifyChangedSlot(s);
        else
         if(qobject_cast<ThrottleWindow*>(client) != nullptr)
           ((ThrottleWindow*)client)->notifyChangedSlot(s);
         else
          if(qobject_cast<LnClockControl*>(client) != nullptr)
           ((LnClockControl*)client)->notifyChangedSlot(s);
         else
          {
           log->error(tr("not implemented %1").arg(client->metaObject()->className()));
           client->notifyChangedSlot(s);
          }
    }
#endif
}


/**
 * Listen to the LocoNet. This is just a steering routine, which invokes
 * others for the various processing steps.
 * @param m incoming message
 */
void SlotManager::message(LocoNetMessage* m)
{
 // LACK processing for resend of immediate command
 if (!mTurnoutNoRetry && immedPacket != nullptr && m->getOpCode() == LnConstants::OPC_LONG_ACK && m->getElement(1) == 0x6D && m->getElement(2) == 0x00)
 {
  // LACK reject, resend immediately
  tc->sendLocoNetMessage(immedPacket);
  immedPacket = nullptr;
 }
 if (m->getOpCode() == LnConstants::OPC_IMM_PACKET/*0xED*/ && m->getElement(1) == 0x0B && m->getElement(2) == 0x7F )
  immedPacket = m;
 else
  immedPacket = nullptr;


 // slot specific message?
 int i = findSlotFromMessage(m);
 if (i != -1)
 {
  forwardMessageToSlot(m,i);
  respondToAddrRequest(m,i);
  programmerOpMessage(m,i);
 }

 if (m->getOpCode()==LnConstants::OPC_LONG_ACK)
 {
  handleLongAck(m);
 }

 // see if extended function message
 if (isExtFunctionMessage(m))
 {
  // yes, get address
  int addr = getDirectFunctionAddress(m);
  // find slot(s) containing this address
  // and route message to them
  bool found = false;
  for (int j = 0; j < 120; j++)
  {
   LocoNetSlot* _slot = slot(j);
   if ( _slot == nullptr ) continue;
   if ( (_slot->locoAddr() != addr)
                || (_slot->slotStatus() == LnConstants::LOCO_FREE) ) continue;
   // found!
   _slot->functionMessage(getDirectDccPacket(m));
   found = true;
  }
  if (!found)
  {
   // rats! Slot not loaded since program start.  Request it be
   // reloaded for later, but that'll be too late
   // for this one.
   LocoNetMessage* mo = new LocoNetMessage(4);
   mo->setOpCode(LnConstants::OPC_LOCO_ADR);  // OPC_LOCO_ADR
   mo->setElement(1, (addr/128)&0x7F);
   mo->setElement(2, addr&0x7F);
   tc->sendLocoNetMessage(mo);
  }
 }

 // save this message for context next time
 // unless it is a OPC_GPBUSY AJS 28-Mar-03
 if( m->getOpCode() != LnConstants::OPC_GPBUSY )
  lastMessage = m->getOpCode();
}

/**
 * If this is a direct function command, return -1,
 * otherwise return DCC address word
 */
int SlotManager::getDirectFunctionAddress(LocoNetMessage* m) {
    if (m->getElement(0) != 0xED) return -1;
    if (m->getElement(1) != 0x0B) return -1;
    if (m->getElement(2) != 0x7F) return -1;
    // Direct packet, check length
    if ( (m->getElement(3)&0x70) < 0x20) return -1;
    int addr = -1;
    // check long address
    if ( (m->getElement(5)&0x40) != 0) {
        addr = (m->getElement(5)&0x3F)*256 + (m->getElement(6)&0xFF);
        if ( (m->getElement(4)&0x02) != 0 ) addr+=128;  // and high bit
    } else {
        addr = (m->getElement(5)&0xFF);
        if ( (m->getElement(4)&0x01) != 0 ) addr+=128;  // and high bit
    }
    return addr;
}

/* if this is a direct DCC packet, return as one long
 * else return -1. Packet does not include
 * address bytes.
 */
int SlotManager::getDirectDccPacket(LocoNetMessage* m) {
    if (m->getElement(0) != 0xED) return -1;
    if (m->getElement(1) != 0x0B) return -1;
    if (m->getElement(2) != 0x7F) return -1;
    // Direct packet, check length
    if ( (m->getElement(3)&0x70) < 0x20) return -1;
    int result = 0;
    int n = (m->getElement(3)&0xF0)/16;
    int start;
    int high = m->getElement(4);
    // check long or short address
    if ( (m->getElement(5)&0x40) != 0) {
        start = 7;
        high = high>>2;
        n = n-2;
    } else {
        start = 6;
        high = high>>1;
        n = n-1;
    }
    // get result
    for (int i = 0; i<n; i++) {
        result = result*256+(m->getElement(start+i)&0x7F);
        if ((high & 0x01) !=0 ) result += 128;
        high = high >> 1;
    }
    return result;
}

/**
 * True if the message is an external DCC packet
 * request for F9-F28
 */
bool SlotManager::isExtFunctionMessage(LocoNetMessage* m)
{
    int pkt = getDirectDccPacket(m);
    if (pkt<0) return false;
    // check F9-12
    if ( (pkt&0xFFFFFF0) == 0xA0) return true;
    // check F13-28
    if ( (pkt&0xFFFFFE00) == 0xDE00) return true;
    return false;
}

/**
 * Find the slot number that a message references
 */
int SlotManager::findSlotFromMessage(LocoNetMessage* m) {

    int i = -1;  // find the slot index in the message and store here

    // decode the specific message type and hence slot number
    switch (m->getOpCode()) {
    case LnConstants::OPC_WR_SL_DATA:
    case LnConstants::OPC_SL_RD_DATA:
        i = m->getElement(2);
        break;

    case LnConstants::OPC_LOCO_DIRF:
    case LnConstants::OPC_LOCO_SND:
    case LnConstants::OPC_LOCO_SPD:
    case LnConstants::OPC_SLOT_STAT1:
        i = m->getElement(1);
        break;

    case LnConstants::OPC_MOVE_SLOTS:  // handle the follow-on message when it comes
        return i; // need to cope with that!!
 default:
  // nothing here for us
  return i;
 }
 // break gets to here
 return i;
}
/*
 * The following methods are for parsing LACK as response to CV programming. It is divided into numerous
 * small methods so that each bit can be overridden for special parsing for individual command station types.
 */
/*protected*/ bool SlotManager::checkLackByte1 (int Byte1) {
    if ((Byte1 & 0xEF) == 0x6F)
        return true;
    else
        return false;
}
/*protected*/ bool SlotManager::checkLackTaskAccepted (int Byte2) {
    if (Byte2 == 1 // task accepted
        || Byte2 == 0x23 || Byte2 == 0x2B || Byte2 == 0x6B// added as DCS51 fix
        || Byte2 == 0x7F || Byte2 == 0x63) // added 0x63 (ACK)
        return true;
    else
        return false;
}
/*protected*/ bool SlotManager::checkLackProgrammerBusy (int Byte2) {
    if (Byte2 == 0)
        return true;
    else
        return false;
}
/*protected*/ bool SlotManager::checkLackAcceptedBlind (int Byte2)
{
 if (Byte2 == 0x40)
  return true;
 else
  return false;
}
/*protected*/ void SlotManager::handleLongAck (LocoNetMessage* m)
{
 // handle if reply to slot. There's no slot number in the LACK, unfortunately.
 // If this is a LACK to a Slot op, and progState is command pending,
 // assume its for us...
 if (log->isDebugEnabled())
  log->debug("LACK in state "+QString::number(progState)+" message: "+m->toString());
 if ( checkLackByte1(m->getElement(1)) && progState == 1 )
 {
  // in programming state
  // check status byte
  if (checkLackTaskAccepted(m->getElement(2)))
  {// task accepted
   // 'not implemented' (op on main)
   // but BDL16 and other devices can eventually reply, so
   // move to commandExecuting state
   log->debug("LACK accepted, next state 2-commandExecuting");
   if ( (_progRead || _progConfirm) && mServiceMode)
    startLongTimer();
   else
    startShortTimer();
   progState = 2;
  }
  else if (checkLackProgrammerBusy(m->getElement(2)))
  {// task aborted as busy
   // move to not programming state
   progState = 0;
   // notify user ProgListener
   stopTimer();
   notifyProgListenerLack(ProgListener::ProgrammerBusy);
  }
  else if (checkLackAcceptedBlind(m->getElement(2)))
  { // task accepted blind
   if((_progRead || _progConfirm) && !mServiceMode)
   {// incorrect Reserved OpSw setting can cause this response to OpsMode Read
    // just treat it as a normal OpsMode Read response
    // move to commandExecuting state
    log->debug("LACK accepted (ignoring incorrect OpSw), next state 2-commandExecuting");
    startShortTimer();
    progState = 2;
   }
   else
   {
    // move to not programming state
    progState = 0;
    // notify user ProgListener
    stopTimer();
    // have to send this in a little while to
    // allow command station time to execute
//    int delay = 100; // milliseconds
//    QTimer timer = new QTimer(delay, new java.awt.event.ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//                notifyProgListenerEnd(-1, 0); // no value (e.g. -1), no error status (e.g.0)
//            }
//        });
//    timer->stop();
//    timer->setInterval(delay);
//    timer->setSingleShot(true);
//    timer->start();
    QTimer::singleShot(postProgDelay, this, SLOT(On_notifyProgListenerEnd()));
   }
  }
  else
  { // not sure how to cope, so complain
   log->warn("unexpected LACK reply code "+QString::number(m->getElement(2)) + "(0x"+QString::number(m->getElement(2),16)+")");
   // move to not programming state
   progState = 0;
   // notify user ProgListener
   stopTimer();
   notifyProgListenerLack(ProgListener::UnknownError);
  }
 }
}
void SlotManager::On_notifyProgListenerEnd() // SLOT
{
 notifyProgListenerEnd(-1, 0); // no value (e.g. -1), no error status (e.g.0)
}

void SlotManager::forwardMessageToSlot(LocoNetMessage* m, int i) {

    // if here, i holds the slot number, and we expect to be able to parse
    // and have the slot handle the message
    if (i>=_slots.length() || i<0) log->error(QString("Received slot number %1 is greater than array length %2 Message was %3").arg(i).arg(_slots.size()).arg( m->toString()));
    try
    {
     _slots[i]->setSlot(m);
    }
    catch (LocoNetException* e)
    {
        // must not have been interesting, or at least routed right
        log->error("slot rejected LocoNetMessage"+m->toString());
        return;
    }
    // notify listeners that slot may have changed
    notify(_slots[i]);
}

void SlotManager::respondToAddrRequest(LocoNetMessage* m, int i)
{
 // is called any time a LocoNet message is received.  Note that we do _NOT_ know why a given message happens!

 // if this is OPC_SL_RD_DATA
 if (m->getOpCode() == LnConstants::OPC_SL_RD_DATA) {
     // yes, see if request exists
     // note that the appropriate _slots[] entry has already been updated
     // to reflect the content of the LocoNet message, so _slots[i]
     // has the locomotive address of this request
     int addr = _slots[i]->locoAddr();
     log->debug(tr("LOCO_ADR resp is slot %1 for addr %2").arg(i).arg(addr)); // NOI18N
     SlotListener* l = mLocoAddrHash.value((addr));
     if (l != nullptr) {
         // only notify once per request
         mLocoAddrHash.remove((addr));
         // and send the notification
         log->debug("notify listener"); // NOI18N
         connect(this, SIGNAL(notifyChangedSlot(LocoNetSlot*)), (SlotListener*)l, SLOT(notifyChangedSlot(LocoNetSlot*)));
         //l->notifyChangedSlot(_slots[i]);
         emit notifyChangedSlot(_slots[i]);
         disconnect(this, SIGNAL(notifyChangedSlot(LocoNetSlot*)), (SlotListener*)l, SLOT(notifyChangedSlot(LocoNetSlot*)));
     } else {
         log->debug(tr("no request for addr %1").arg(addr)); // NOI18N
     }
 }
}

void SlotManager::programmerOpMessage(LocoNetMessage* m, int i)
{
 // start checking for programming operations in slot 124
 if (i == 124)
 {
  // here its an operation on the programmer slot
  if (log->isDebugEnabled())
   log->debug(QString("Message %1 for slot 124 in state %2").arg(m->getOpCodeHex()).arg(progState));
  switch (progState)
  {
   case 0:   // notProgramming
    break;
   case 1:   // commandPending
    // we just sit here waiting for a LACK, handled above
    break;
   case 2:   // commandExecuting
    // waiting for slot read, is it present?
    if (m->getOpCode() == LnConstants::OPC_SL_RD_DATA)
    {
     // yes, this is the end
     // move to not programming state
     stopTimer();
     progState = 0;

     // parse out value returned
     int value = -1;
     int status = 0;
     if (_progConfirm )
     {
      // read command, get value; check if OK
      value = _slots[i]->cvval();
      if (value != _confirmVal) status = status | ProgListener::ConfirmFailed;
     }
     if (_progRead )
     {
      // read command, get value
      value = _slots[i]->cvval();
     }
     // parse out status
     if ( (_slots[i]->pcmd() & LnConstants::PSTAT_NO_DECODER ) != 0 )
      status = (status | ProgListener::NoLocoDetected);
     if ( (_slots[i]->pcmd() & LnConstants::PSTAT_WRITE_FAIL ) != 0 )
      status = (status | ProgListener::NoAck);
     if ( (_slots[i]->pcmd() & LnConstants::PSTAT_READ_FAIL ) != 0 )
      status = (status | ProgListener::NoAck);
     if ( (_slots[i]->pcmd() & LnConstants::PSTAT_USER_ABORTED ) != 0 )
      status = (status | ProgListener::UserAborted);

     // and send the notification
     notifyProgListenerEnd(value, status);
    }
    break;
  default:  // error!
    log->error("unexpected programming state "+QString::number(progState));
    break;
  }
 }
}

// members for handling the programmer interface


/**
 * Types implemented here.
 */
//@Override
/*public*/ QList<ProgrammingMode*> SlotManager::getSupportedModes()
{
 QList<ProgrammingMode*> ret = QList<ProgrammingMode*>();
 ret.append(ProgrammingMode::PAGEMODE);
 ret.append(ProgrammingMode::DIRECTBYTEMODE);
 ret.append(ProgrammingMode::REGISTERMODE);
 ret.append(ProgrammingMode::ADDRESSMODE);
 return ret;
}


/**
 * Trigger notification of PropertyChangeListeners. The only bound
 * property is Mode from the Programmer interface. It is not clear
 * why this is not in AbstractProgrammer...
 * @param name Changed property
 * @param oldval
 * @param newval
 */
//@SuppressWarnings("unchecked")
void SlotManager::notifyPropertyChange(QString name, int oldval, int newval) {
    // make a copy of the listener vector to synchronized not needed for transmit
 QVector<PropertyChangeListener*>* v = new QVector<PropertyChangeListener*>();
 QMutex mutex;
//    synchronized(this)
//        {
//            v = (Vector<PropertyChangeListener>) propListeners.clone();
    mutex.lock();
    foreach(PropertyChangeListener* l, *propListeners)
        v->append(l);
    mutex.unlock();
//        }
    if (log->isDebugEnabled()) log->debug(QString("notify %1 listeners of property change name: %2 oldval: %3 newval: %4").arg(v->size()).arg(name).arg(oldval).arg(newval));
    // forward to all listeners
    int cnt = v->size();
    for (int i=0; i < cnt; i++) {
        PropertyChangeListener* client = v->at(i);
        client->propertyChange(new PropertyChangeEvent(this, name,oldval, newval));
    }
    emit propertyChange(new PropertyChangeEvent(this, name,oldval, newval));
}

#if 0
/**
 * Determine whether this Programmer implementation powers off the
 * main track after a service track programming operation.
 * This is entirely determined by
 * the attached command station, not the code here, so it
 * refers to the mProgPowersOff member variable which is recording
 * the known state of that.
 * @return True if main track off after service operation
 */
bool SlotManager::getProgPowersOff() { return mProgPowersOff; }

/**
 * Configure whether this Programmer owers off the
 * main track after a service track programming operation.<P>
 * This is not part of the Programmer interface, but is used
 * as part of the startup sequence for the LocoNet objects.
 *
 * @param pProgPowersOff True if power is off afterward
 */
void SlotManager::setProgPowersOff(bool pProgPowersOff) {
    log->debug(QString("set progPowersOff to ")+(pProgPowersOff?"Off":"On"));
    mProgPowersOff = pProgPowersOff;
}

#endif

/**
 * Determine whether this Programmer implementation is capable of
 * reading decoder contents. This is entirely determined by
 * the attached command station, not the code here, so it
 * refers to the mCanRead member variable which is recording
 * the known state of that.
 * @return True if reads are possible
 */
bool SlotManager::getCanRead() { return mCanRead; }

/**
 * Returns the write confirm mode implemented by the command station.
 * <p>
 * Service mode always checks for DecoderReply.  (The DCS240 also seems to do
 * ReadAfterWrite, but that's not fully understood yet)
 * @param addr - This implementation ignores this parameter
 * @return the supported WriteConfirmMode
 */
//@Nonnull
//@Override
/*public*/ Programmer::WriteConfirmMode SlotManager::getWriteConfirmMode(QString /*addr*/) { return WriteConfirmMode::DecoderReply; }


/**
 * Set the command station type
 */
void SlotManager::setCommandStationType(LnCommandStationType* value){
    commandStationType = value;
    mCanRead = value->getCanRead();
    mProgEndSequence = value->getProgPowersOff();
}

/**
 * Provide a ThrottledTransmitter for sending immediate packets
 */
void SlotManager::setThrottledTransmitter(LocoNetThrottledTransmitter* value, bool m){
    throttledTransmitter = value;
    mTurnoutNoRetry = m;
}
/**
 * Get the command station type
 */
LnCommandStationType* SlotManager::getCommandStationType(){
    return commandStationType;
}


/**
 * Internal routine to handle a timeout
 */
/*synchronized*/ /*protected*/ void SlotManager::timeout()
{
 if (log->isDebugEnabled()) log->debug("timeout fires in state "+QString::number(progState));
 if (progState != 0)
 {
  // we're programming, time to stop
  if (log->isDebugEnabled()) log->debug("timeout while programming");
  // perhaps no communications present? Fail back to end of programming
  progState = 0;
  // and send the notification; error code depends on state
  if (progState == 2 && !mServiceMode) // ops mode command executing,
   // so did talk to command station at first
   notifyProgListenerEnd(_slots[124]->cvval(), ProgListener::NoAck);
  else // all others
   notifyProgListenerEnd(_slots[124]->cvval(), ProgListener::FailedTimeout);
 }
}

void SlotManager::writeCVOpsMode(int CV, int val, ProgListener* p, int addr, bool longAddr) throw(ProgrammerException)
{
     Q_UNUSED(longAddr)
    lopsa = addr&0x7f;
    hopsa = (addr/128)&0x7f;
    mServiceMode = false;
    doWrite(CV, val, p, 0x67);  // ops mode byte write, with feedback
}

void SlotManager::writeCV(int CV, int val, ProgListener* p) throw(ProgrammerException)
{
 lopsa = 0;
 hopsa = 0;
 mServiceMode = true;
    // parse the programming command
 int pcmd = 0x43;       // LPE implies 0x40, but 0x43 is observed
 if (getMode() == (ProgrammingMode::PAGEMODE)) pcmd = pcmd | 0x20;
 else if (getMode() == ProgrammingMode::DIRECTBYTEMODE) pcmd = pcmd | 0x28;
 else if (getMode() == ProgrammingMode::REGISTERMODE
             || getMode() == ProgrammingMode::ADDRESSMODE) pcmd = pcmd | 0x10;
 else
 //throw (new ProgrammerException("mode not supported"));
  emit programmerException("mode not supported");

 doWrite(CV, val, p, pcmd);
}
void SlotManager::doWrite(int CV, int val, ProgListener* p, int pcmd) throw(ProgrammerException)
{
 if (log->isDebugEnabled()) log->debug("writeCV: "+QString::number(CV));
 stopEndOfProgrammingTimer();  // still programming, so no longer waiting for power off

 useProgrammer(p);
 _progRead = false;
 _progConfirm = false;
 // set commandPending state
 progState = 1;

 // format and send message
 startShortTimer();
 tc->sendLocoNetMessage(progTaskStart(pcmd, val, CV, true));
}

void SlotManager::confirmCVOpsMode(int CV, int val, ProgListener* p,
                           int addr, bool longAddr) throw(ProgrammerException)
{
 Q_UNUSED(longAddr)
    lopsa = addr&0x7f;
    hopsa = (addr/128)&0x7f;
    mServiceMode = false;
    doConfirm(CV, val, p, 0x2F);  // although LPE implies 0x2C, 0x2F is observed
}
void SlotManager::confirmCV(int CV, int val, ProgListener* p) throw(ProgrammerException)
{
    lopsa = 0;
    hopsa = 0;
    mServiceMode = true;
    // parse the programming command
    int pcmd = 0x03;       // LPE imples 0x00, but 0x03 is observed
    if (getMode() == ProgrammingMode::PAGEMODE) pcmd = pcmd | 0x20;
    else if (getMode() == ProgrammingMode::DIRECTBYTEMODE) pcmd = pcmd | 0x28;
    else if (getMode() == ProgrammingMode::REGISTERMODE
             || getMode() == ProgrammingMode::ADDRESSMODE) pcmd = pcmd | 0x10;
    else
     //throw new ProgrammerException("mode not supported");
     emit programmerException("mode not supported");

    doConfirm(CV, val, p, pcmd);
}

void SlotManager::doConfirm(int CV, int val, ProgListener* p,
                      int pcmd) /*throw(ProgrammerException)*/
{
    if (log->isDebugEnabled()) log->debug("confirmCV: "+QString::number(CV));
    stopEndOfProgrammingTimer();  // still programming, so no longer waiting for power off

    useProgrammer(p);
    _progRead = false;
    _progConfirm = true;
    _confirmVal = val;

    // set commandPending state
    progState = 1;

    // format and send message
    startShortTimer();
    tc->sendLocoNetMessage(progTaskStart(pcmd, -1, CV, false));
}

/**
 * Invoked by LnOpsModeProgrammer to start an ops-mode
 * read operation.
 * @param CV Which CV to read
 * @param p Who to notify on complete
 * @param addr Address of the locomotive
 * @param longAddr true if a long address, false if short address
 * @throws ProgrammerException
 */
void SlotManager::readCVOpsMode(int CV, ProgListener* p, int addr, bool longAddr) throw(ProgrammerException)
{
 Q_UNUSED(longAddr)
    lopsa = addr&0x7f;
    hopsa = (addr/128)&0x7f;
    mServiceMode = false;
    doRead(CV, p, 0x2F);  // although LPE implies 0x2C, 0x2F is observed
}

void SlotManager::readCV(int CV, ProgListener* p) throw(ProgrammerException)
{
    lopsa = 0;
    hopsa = 0;
    mServiceMode = true;
    // parse the programming command
    int pcmd = 0x03;       // LPE imples 0x00, but 0x03 is observed
    if (getMode() == ProgrammingMode::PAGEMODE) pcmd = pcmd | 0x20;
    else if (getMode() == ProgrammingMode::DIRECTBYTEMODE) pcmd = pcmd | 0x28;
    else if (getMode() == ProgrammingMode::REGISTERMODE
             || getMode() == ProgrammingMode::ADDRESSMODE) pcmd = pcmd | 0x10;
    else
     throw new ProgrammerException("mode not supported");

    doRead(CV, p, pcmd);
}

void SlotManager::doRead(int CV, ProgListener* p, int progByte) throw(ProgrammerException)
{
    if (log->isDebugEnabled()) log->debug("readCV: "+QString::number(CV));
    stopEndOfProgrammingTimer();  // still programming, so no longer waiting for power off

    useProgrammer(p);
    _progRead = true;
    _progConfirm = false;
    // set commandPending state
    progState = 1;

    // format and send message
    startShortTimer();
    tc->sendLocoNetMessage(progTaskStart(progByte, -1, CV, false));
}


// internal method to remember who's using the programmer
void SlotManager::useProgrammer(ProgListener* p) // throws jmri.ProgrammerException
{
 // test for only one!
 if (_usingProgrammer != nullptr && _usingProgrammer != p)
 {
  if (log->isInfoEnabled())
   log->info(QString("programmer already in use by %1").arg(_usingProgrammer->objectName()));
  throw new ProgrammerException("programmer in use");
 }
 else
 {
  _usingProgrammer = p;
  return;
 }
}

/**
 * Internal method to create the LocoNetMessage for programmer task start
 */
LocoNetMessage* SlotManager::progTaskStart(int pcmd, int val, int cvnum, bool write)
{

 Q_UNUSED(write)
 int  addr = cvnum-1;    // cvnum is in human readable form; addr is what's sent over loconet

 LocoNetMessage* m = new LocoNetMessage(14);

 m->setOpCode(LnConstants::OPC_WR_SL_DATA);
 m->setElement(1, 0x0E);
 m->setElement(2, LnConstants::PRG_SLOT);

 m->setElement(3, pcmd);

 // set zero, then HOPSA, LOPSA, TRK
 m->setElement(4, 0);
 m->setElement(5, hopsa);
 m->setElement(6, lopsa);
 m->setElement(7, 0);  // TRK was 0, then 7 for PR2, now back to zero

 // store address in CVH, CVL. Note CVH format is truely wierd...
 m->setElement(8, (addr&0x300)/16 + (addr&0x80)/128 + (val&0x80)/128*2 );
 m->setElement(9,addr & 0x7F);

 // store low bits of CV value
 m->setElement(10, val&0x7F);

 // throttle ID
 m->setElement(11, 0x7F);
 m->setElement(12, 0x7F);
 return m;
}

/**
 * internal method to notify of the final result
 * @param value The cv value to be returned
 * @param status The error code, if any
 */
void SlotManager::notifyProgListenerEnd(int value, int status)
{
 // (re)start power timer
 restartEndOfProgrammingTimer();
 // and send the reply
 ProgListener* p = _usingProgrammer;
 _usingProgrammer = nullptr;
 if (p!=nullptr) sendProgrammingReply(p, value, status);
}

/**
 * Internal method to notify of the LACK result.
 * This is a separate routine from nPLRead in case we need to handle something later
 * @param status The error code, if any
 */
void SlotManager::notifyProgListenerLack(int status)
{
 // (re)start power timer
 restartEndOfProgrammingTimer();
 // and send the reply
 sendProgrammingReply(_usingProgrammer, -1, status);
 _usingProgrammer = nullptr;
}

/**
 * Internal routine to forward a programing reply.
 * This is delayed to prevent overruns of the
 * command station.
 * @param value the value to return
 * @param status The error code, if any
 */
void SlotManager::sendProgrammingReply(ProgListener* p, int value, int status)
{
 int delay = 20;  // value in service mode
 new SendProgrammingReplyDelay(p, value, status,  delay);
}
 SendProgrammingReplyDelay::SendProgrammingReplyDelay(ProgListener *p, int value, int status, int delay)
 {
  this->p = p;
  this->value = value;
  this->status = status;
  this->delay = delay;
  QTimer* timer = new QTimer();
  timer->setSingleShot(true);
  connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
  timer->start(delay);
 }
 void SendProgrammingReplyDelay::timeout()
 {
//         p.programmingOpReply(value, status);
  connect(this, SIGNAL(on_programmingOpReply(int,int)), p, SLOT(programmingOpReply(int,int)));
  emit on_programmingOpReply(value, status);
  disconnect(this, SIGNAL(on_programmingOpReply(int,int)), p, SLOT(programmingOpReply(int,int)));
 }

/**
 * Internal routine to stop power timer, as another programming
 * operation has happened
 */
/*protected*/ void SlotManager::stopEndOfProgrammingTimer()
{
    if (mPowerTimer!=nullptr) mPowerTimer->stop();
}

/**
 * Internal routine to handle timer restart if needed to restore
 * power.  This is only needed in service mode.
 */
void SlotManager::restartEndOfProgrammingTimer()
{
 if (mProgEndSequence)
 {
  if (mPowerTimer==nullptr)
  {
   mPowerTimer = new QTimer();
//   2000, new java.awt.event.ActionListener()
//   {
//    public void actionPerformed(java.awt.event.ActionEvent e)
//    {
//     doPowerOn();
//    }
//   }
   connect(mPowerTimer, SIGNAL(timeout()), this, SLOT(doEndOfProgramming()));
  }
  mPowerTimer->stop();
  mPowerTimer->setInterval(2000);
  mPowerTimer->setSingleShot(true);
  mPowerTimer->start();
 }
}

/**
 * Internal routine to handle a programming timeout by turning power off
 */
void SlotManager::doEndOfProgramming()
{
 if (progState == 0)
 {
  // we're not programming, time to power on
  if (log->isDebugEnabled()) log->debug("timeout: turn power on");
  try
  {
   static_cast<PowerManager*>(InstanceManager::getDefault("PowerManager"))->setPower(PowerManager::ON);
  }
  catch (std::exception& e)
  {
   log->error(QString("exception during power on at end of programming: %1").arg("??"));
  }
 }
}



/**
 * Start the process of checking each slot for contents.
 * <P>
 * This is not invoked by this class, but can be invoked
 * from elsewhere to start the process of scanning all
 * slots to update their contents.
 */
void SlotManager::update()
{
 nextReadSlot = 0;
 readNextSlot();
}

/**
 * Send a message requesting the data from a particular slot.
 * @param slot Slot number
 */
void SlotManager::sendReadSlot(int slot)
{
 LocoNetMessage* m = new LocoNetMessage(4);
 m->setOpCode(LnConstants::OPC_RQ_SL_DATA);
 m->setElement(1, slot&0x7F);
 m->setElement(2, 0);
 tc->sendLocoNetMessage(m);
}

void SlotManager::readNextSlot()
{
 // send info request
 sendReadSlot(nextReadSlot++);

 // schedule next read if needed
 if (nextReadSlot < 127)
 {
//        javax.swing.Timer t = new javax.swing.Timer(500, new java.awt.event.ActionListener() {
//            public void actionPerformed(java.awt.event.ActionEvent e) {
//                readNextSlot();
//            }
//        });
//        QTimer t;

//        t.setSingleShot(true);
//        t.start(500);
  QTimer::singleShot(500, this, SLOT(readNextSlot()));
 }
}

/**
 * Provide a snapshot of the slots in use
 */
int SlotManager::getInUseCount() {
    int result = 0;
    for (int i = 0; i<=120; i++) {
        if (slot(i)->slotStatus() == LnConstants::LOCO_IN_USE ) result++;
    }
    return result;
}

void SlotManager::setSystemConnectionMemo(LocoNetSystemConnectionMemo* memo)
{
 adaptermemo = memo;
}


QString SlotManager::getUserName()
{
 if(adaptermemo==nullptr)
  return "LocoNet";
 return adaptermemo->getUserName();
}

QString SlotManager::getSystemPrefix()
{
 if(adaptermemo==nullptr)
  return "L";
 return adaptermemo->getSystemPrefix();
}
/*public*/ void SlotManager::setTranspondingAvailable(bool val) { transpondingAvailable = val; }
/*public*/ bool SlotManager::getTranspondingAvailable() { return transpondingAvailable; }

LocoNetSystemConnectionMemo* SlotManager::getSystemConnectionMemo()
{
 return adaptermemo;
}

// initialize logging
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SlotManager.class.getName());

/*public*/ void SlotManager::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 writeCV(CV.toInt(), val, p);
}
/**
 * Read a CV via the OpsMode programmer
 * <p>
 * @param cvNum a String containing the CV number
 * @param p programmer
 * @throws jmri.ProgrammerException if an unsupported programming mode is exercised
 */
//@Override
/*public*/ void SlotManager::readCV(QString cvNum, ProgListener* p) throw (ProgrammerException) {
    log->debug(tr("readCV(string): cvNum=%1").arg(cvNum));
    if (getMode()== (csOpSwProgrammingMode)) {
        log->debug("cvOpSw mode!");
        //handle Command Station OpSw programming here
        QStringList parts = cvNum.split("\\.");
        if ((parts[0]==("csOpSw")) && (parts.length()==2)) {
            if (csOpSwAccessor == nullptr) {
                csOpSwAccessor = new CsOpSwAccess(adaptermemo, p);
            } else {
                csOpSwAccessor->setProgrammerListener(p);
            }
            // perform the CsOpSwMode read access
            log->debug("going to try the opsw access");
            csOpSwAccessor->readCsOpSw(cvNum, p);
            return;

        } else {
            log->warn("rejecting the cs opsw access account unsupported CV name format");
            // unsupported format in "cv" name.  Signal an error.
            p->programmingOpReply(1, ProgListener::SequenceError);
            return;

        }
    } else {
        readCV((cvNum.toInt()), p);
    }
}
/*public*/ void SlotManager::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 confirmCV(CV.toInt(), val, p);
}
