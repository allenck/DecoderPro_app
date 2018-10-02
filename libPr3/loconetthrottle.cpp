#include "loconetthrottle.h"
#include "loconetsystemconnectionmemo.h"
#include "nmrapacket.h"
#include "lnthrottlemanager.h"
#include "lnpacketizer.h"

//LocoNetThrottle::LocoNetThrottle(QObject *parent) :
//    AbstractThrottle(parent)
//{
//}
/**
 * An implementation of DccThrottle via AbstractThrottle with code specific
 * to a LocoNet connection.
 * <P>
 * Speed in the Throttle interfaces and AbstractThrottle is a float, but in LocoNet is an int
 * with values from 0 to 127.
 * <P>
 * @author  Glen Oberhauser, Bob Jacobsen  Copyright (C) 2003, 2004
 * @author  Stephen Williams  Copyright (C) 2008
 * @version $Revision: 22484 $
 */
//public class LocoNetThrottle extends AbstractThrottle implements SlotListener {


/**
 * Constructor
 * @param slot The LocoNetSlot this throttle will talk on.
 */
/*public*/ LocoNetThrottle::LocoNetThrottle(LocoNetSystemConnectionMemo* memo, LocoNetSlot* slot, QObject *parent) : AbstractThrottle(memo, parent)
{
 //super(memo);
 this->slot = slot;
 setObjectName("LocoNetThrottle");
 log = new Logger("LocoNetThrottle");
 mRefreshTimer = NULL;
 network = memo->getLnTrafficController();
 LocoNetMessage* msg = new LocoNetMessage(4);
 msg->setOpCode(LnConstants::OPC_MOVE_SLOTS);
 msg->setElement(1, slot->getSlot());
 msg->setElement(2, slot->getSlot());
 ((LnPacketizer*)network)->sendLocoNetMessage(msg);

 // save last known layout state for spd/dirf/snd so we can
 // avoid race condition if another LocoNet process queries
 // our slot while we are in the act of changing it.
 layout_spd  = slot->speed();
 layout_dirf = slot->dirf();
 layout_snd  = slot->snd();


    // cache settings
    this->speedSetting = floatSpeed(slot->speed());
    this->f0           = slot->isF0();
    this->f1           = slot->isF1();
    this->f2           = slot->isF2();
    this->f3           = slot->isF3();
    this->f4           = slot->isF4();
    this->f5           = slot->isF5();
    this->f6           = slot->isF6();
    this->f7           = slot->isF7();
    this->f8           = slot->isF8();

    // extended values
    this->f8           = slot->isF8();
    this->f9           = slot->isF9();
    this->f10          = slot->isF10();
    this->f11          = slot->isF11();
    this->f12          = slot->isF12();
    this->f13          = slot->isF13();
    this->f14          = slot->isF14();
    this->f15          = slot->isF15();
    this->f16          = slot->isF16();
    this->f17          = slot->isF17();
    this->f18          = slot->isF18();
    this->f19          = slot->isF19();
    this->f20          = slot->isF20();
    this->f21          = slot->isF21();
    this->f22          = slot->isF22();
    this->f23          = slot->isF23();
    this->f24          = slot->isF24();
    this->f25          = slot->isF25();
    this->f26          = slot->isF26();
    this->f27          = slot->isF27();
    this->f28          = slot->isF28();

    this->address      = slot->locoAddr();
    this->isForward    = slot->isForward();
    this->slotStatus   = slot->slotStatus();

//    switch(slot->decoderType())
//    {
//        case LnConstants::DEC_MODE_128:
//        case LnConstants::DEC_MODE_128A:
 if(slot->decoderType() == LnConstants::DEC_MODE_128 || slot->decoderType() == LnConstants::DEC_MODE_128A)
            setSpeedStepMode( DccThrottle::SpeedStepMode128 );
//            break;
//        case LnConstants::DEC_MODE_28:
//        case LnConstants::DEC_MODE_28A:
//        case LnConstants::DEC_MODE_28TRI:
 else if(slot->decoderType() == LnConstants::DEC_MODE_28 || slot->decoderType() == LnConstants::DEC_MODE_28A || slot->decoderType() == LnConstants::DEC_MODE_28TRI  )
            setSpeedStepMode( DccThrottle::SpeedStepMode28 );
//            break;
//        case LnConstants::DEC_MODE_14:
 else if(slot->decoderType() == LnConstants::DEC_MODE_14 )
            setSpeedStepMode( DccThrottle::SpeedStepMode14 );
//            break;
//    }

    // listen for changesQVariant
    slot->addSlotListener((SlotListener*)this);

    // start periodically sending the speed, to keep this
    // attached
    startRefresh();

}


/**
 * Convert a LocoNet speed integer to a float speed value
 */
/*protected*/ float LocoNetThrottle::floatSpeed(int lSpeed) {
    if (lSpeed == 0) return 0.f;
    else if (lSpeed == 1) return -1.f;   // estop
    else return ( (lSpeed-1)/126.f);
}

/**
 * Convert a float speed value to a LocoNet speed integer
 */
/*protected*/ int LocoNetThrottle::intSpeed(float fSpeed) {
  if (fSpeed == 0.f)
    return 0;
  else if (fSpeed < 0.f)
    return 1;   // estop
    // add the 0.5 to handle float to int round for positive numbers
  return (int)(fSpeed * 126.f + 0.5) + 1 ;
}
/*public*/ void LocoNetThrottle::setF0(bool f0) {
    bool old = this->f0;
    this->f0 = f0;
    sendFunctionGroup1();
    if (old != this->f0)
        notifyPropertyChangeListener(Throttle::F0, old, this->f0 );
}
/*public*/ void LocoNetThrottle::setF1(bool f1) {
    bool old = this->f1;
    this->f1 = f1;
    sendFunctionGroup1();
    if (old != this->f1)
        notifyPropertyChangeListener(Throttle::F1, old, this->f1 );
}
/*public*/ void LocoNetThrottle::setF2(bool f2) {
    bool old = this->f2;
    this->f2 = f2;
    sendFunctionGroup1();
    if (old != this->f2)
        notifyPropertyChangeListener(Throttle::F2, old, this->f2 );
}

/*public*/ void LocoNetThrottle::setF3(bool f3) {
    bool old = this->f3;
    this->f3 = f3;
    sendFunctionGroup1();
    if (old != this->f3)
        notifyPropertyChangeListener(Throttle::F3, old, this->f3 );
}

/*public*/ void LocoNetThrottle::setF4(bool f4) {
    bool old = this->f4;
    this->f4 = f4;
    sendFunctionGroup1();
    if (old != this->f4)
        notifyPropertyChangeListener(Throttle::F4, old, this->f4 );
}

/*public*/ void LocoNetThrottle::setF5(bool f5) {
    bool old = this->f5;
    this->f5 = f5;
    sendFunctionGroup2();
    if (old != this->f5)
        notifyPropertyChangeListener(Throttle::F5, old, this->f5 );
}

/*public*/ void LocoNetThrottle::setF6(bool f6) {
    bool old = this->f6;
    this->f6 = f6;
    sendFunctionGroup2();
    if (old != this->f6)
        notifyPropertyChangeListener(Throttle::F6, old, this->f6 );
}

/*public*/ void LocoNetThrottle::setF7(bool f7) {
    bool old = this->f7;
    this->f7 = f7;
    sendFunctionGroup2();
    if (old != this->f7)
        notifyPropertyChangeListener(Throttle::F7, old, this->f7 );
}

/*public*/ void LocoNetThrottle::setF8(bool f8) {
    bool old = this->f8;
    this->f8 = f8;
    sendFunctionGroup2();
    if (old != this->f8)
        notifyPropertyChangeListener(Throttle::F8, old, this->f8 );
}

/*public*/ void LocoNetThrottle::setF9(bool f9) {
    bool old = this->f9;
    this->f9 = f9;
    sendFunctionGroup3();
    if (old != this->f9)
        notifyPropertyChangeListener(Throttle::F9, old, this->f9 );
}

/*public*/ void LocoNetThrottle::setF10(bool f10) {
    bool old = this->f10;
    this->f10 = f10;
    sendFunctionGroup3();
    if (old != this->f10)
        notifyPropertyChangeListener(Throttle::F10, old, this->f10 );
}

/*public*/ void LocoNetThrottle::setF11(bool f11) {
    bool old = this->f11;
    this->f11 = f11;
    sendFunctionGroup3();
    if (old != this->f11)
        notifyPropertyChangeListener(Throttle::F11, old, this->f11 );
}

/*public*/ void LocoNetThrottle::setF12(bool f12) {
    bool old = this->f12;
    this->f12 = f12;
    sendFunctionGroup3();
    if (old != this->f12)
        notifyPropertyChangeListener(Throttle::F12, old, this->f12 );
}

/*public*/ void LocoNetThrottle::setF13(bool f13) {
    bool old = this->f13;
    this->f13 = f13;
    sendFunctionGroup4();
    if (old != this->f13)
        notifyPropertyChangeListener(Throttle::F13, old, this->f13 );
}

/*public*/ void LocoNetThrottle::setF14(bool f14) {
    bool old = this->f14;
    this->f14 = f14;
    sendFunctionGroup4();
    if (old != this->f14)
        notifyPropertyChangeListener(Throttle::F14, old, this->f14 );
}

/*public*/ void LocoNetThrottle::setF15(bool f15) {
    bool old = this->f15;
    this->f15 = f15;
    sendFunctionGroup4();
    if (old != this->f15)
        notifyPropertyChangeListener(Throttle::F15, old, this->f15 );
}

/*public*/ void LocoNetThrottle::setF16(bool f16) {
    bool old = this->f16;
    this->f16 = f16;
    sendFunctionGroup4();
    if (old != this->f16)
        notifyPropertyChangeListener(Throttle::F16, old, this->f16 );
}

/*public*/ void LocoNetThrottle::setF17(bool f17) {
    bool old = this->f17;
    this->f17 = f17;
    sendFunctionGroup4();
    if (old != this->f17)
        notifyPropertyChangeListener(Throttle::F17, old, this->f17 );
}

/**
 * Send the LocoNet message to set the state of locomotive
 * direction and functions F0, F1, F2, F3, F4
 */
/*protected*/ void LocoNetThrottle::sendFunctionGroup1()
{
 int new_dirf = ((getIsForward() ? 0 : LnConstants::DIRF_DIR) |
                 (getF0() ? LnConstants::DIRF_F0 : 0) |
                 (getF1() ? LnConstants::DIRF_F1 : 0) |
                 (getF2() ? LnConstants::DIRF_F2 : 0) |
                 (getF3() ? LnConstants::DIRF_F3 : 0) |
                 (getF4() ? LnConstants::DIRF_F4 : 0));
 if (new_dirf != layout_dirf)
 {
  LocoNetMessage* msg = new LocoNetMessage(4);
  msg->setOpCode(LnConstants::OPC_LOCO_DIRF);
  msg->setElement(1, slot->getSlot());
  msg->setElement(2, new_dirf);
  ((LnPacketizer*)network)->sendLocoNetMessage(msg);
 }
}

/**
 * Send the LocoNet message to set the state of
 * functions F5, F6, F7, F8
 */
/*protected*/ void LocoNetThrottle::sendFunctionGroup2()
{
 int new_snd = ((getF8() ? LnConstants::SND_F8 : 0) |
                   (getF7() ? LnConstants::SND_F7 : 0) |
                   (getF6() ? LnConstants::SND_F6 : 0) |
                   (getF5() ? LnConstants::SND_F5 : 0));
 if (new_snd != layout_snd)
 {
  LocoNetMessage* msg = new LocoNetMessage(4);
  msg->setOpCode(LnConstants::OPC_LOCO_SND);
  msg->setElement(1, slot->getSlot());
  msg->setElement(2, new_snd);
  ((LnPacketizer*)network)->sendLocoNetMessage(msg);
 }
}

/*protected*/ void LocoNetThrottle::sendFunctionGroup3()
{
 // LocoNet practice is to send F9-F12 as a DCC packet
 QByteArray result = NmraPacket::function9Through12Packet(address, (address >= 128),
          getF9(), getF10(), getF11(), getF12());

  log->debug(tr("sendFunctionGroup3 sending %1 to LocoNet slot %2").arg(result.constData()).arg(slot->getSlot()));
  ((CommandStation*) adapterMemo->get("CommandStation"))->sendPacket(result, 4); // repeat = 4
}

/**
 * Sends Function Group 4 values - F13 thru F20, using an "OPC_IMM_PACKET" LocoNet
 * Message.
 */
//@Override
/*protected*/ void LocoNetThrottle::sendFunctionGroup4()
{
 // LocoNet practice is to send F13-F20 as a DCC packet
 QByteArray result = NmraPacket::function13Through20Packet(address, (address >= 128),
         getF13(), getF14(), getF15(), getF16(),
         getF17(), getF18(), getF19(), getF20());

 log->debug(tr("sendFunctionGroup3 sending %1 to LocoNet slot %2").arg(result.constData()).arg(slot->getSlot()));
 ((CommandStation*) adapterMemo->get("CommandStation"))->sendPacket(result, 4); // repeat = 4
}

/**
 * Sends Function Group 5 values - F21 thru F28, using an "OPC_IMM_PACKET" LocoNet
 * Message.
 */
//@Override
/*protected*/ void LocoNetThrottle::sendFunctionGroup5() {
    // LocoNet practice is to send F21-F28 as a DCC packet
    QByteArray result = NmraPacket::function21Through28Packet(address, (address >= 128),
            getF21(), getF22(), getF23(), getF24(),
            getF25(), getF26(), getF27(), getF28());

    log->debug(tr("sendFunctionGroup3 sending %1 to LocoNet slot %2").arg(result.constData()).arg(slot->getSlot()));
    ((CommandStation*) adapterMemo->get("CommandStation"))->sendPacket(result, 4); // repeat = 4
}

/**
 * Set the speed.
 * <P>
 * This intentionally skips the emergency stop value of 1.
 * @param speed Number from 0 to 1; less than zero is emergency stop
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point, notify on any change
/*public*/ void LocoNetThrottle::setSpeedSetting(float speed)
{
 if( LnConstants::CONSIST_MID==slot->consistStatus()||
    LnConstants::CONSIST_SUB==slot->consistStatus() )
 {
    // Digitrax slots use the same memory location to store the
    // speed AND the slot to which a locomotive is consisted.
    // if the locomotive is either a CONSIST_MID or a CONSIST_SUB,
    // we need to ignore the request to change the speed
    if(log->isDebugEnabled()) log->debug(tr("Attempt to change speed on locomotive ") + ((DccLocoAddress*)getLocoAddress())->toString() + tr(" which is a ") + LnConstants::CONSIST_STAT(slot->consistStatus()));
    return;
 }
 float oldSpeed = this->speedSetting;
 this->speedSetting = speed;
 if (speed<0) this->speedSetting = -1.f;

 int new_spd = intSpeed( speed );
 if (new_spd != layout_spd)
 {
  LocoNetMessage* msg = new LocoNetMessage(4);
  msg->setOpCode(LnConstants::OPC_LOCO_SPD);
  msg->setElement(1, slot->getSlot());
  log->debug( "setSpeedSetting: float speed: " + QString::number(speed) + " LocoNet speed: " + QString::number(new_spd ));
  msg->setElement(2, new_spd);
  ((LnPacketizer*)network)->sendLocoNetMessage(msg);
 }

 // reset timeout
 if (mRefreshTimer != NULL)
 { // got NullPointerException sometimes
     mRefreshTimer->stop();
     mRefreshTimer->setSingleShot(false);     // refresh until stopped by dispose
     mRefreshTimer->start();
 }
 if (oldSpeed != this->speedSetting)
     notifyPropertyChangeListener("SpeedSetting", oldSpeed, this->speedSetting );
 record(speed);
}

/**
 * LocoNet actually puts forward and backward in the same message
 * as the first function group.
 */
/*public*/ void LocoNetThrottle::setIsForward(bool forward)
{
 bool old = isForward;
 isForward = forward;
 sendFunctionGroup1();
 if (old != this->isForward)
  notifyPropertyChangeListener("IsForward", old, this->isForward);
}

/*public*/ LocoNetSlot* LocoNetThrottle::getLocoNetSlot(){
    return slot;
}

/*public*/ QString LocoNetThrottle::toString() {
    return ((DccLocoAddress*)getLocoAddress())->toString();
}

/**
 * Dispose when finished with this object.  After this, further usage of
 * this Throttle object will result in a JmriException.
 */
/*protected*/ void LocoNetThrottle::throttleDispose() {
    // stop timeout
    if (mRefreshTimer != NULL)
        mRefreshTimer->stop();

    // release connections
    if (slot != NULL)
        slot->removeSlotListener((SlotListener*)this);

    mRefreshTimer = NULL;
    slot = NULL;
    network = NULL;

    finishRecord();
 }


/*protected*/ void LocoNetThrottle::startRefresh()
{
//    mRefreshTimer = new javax.swing.Timer(50000, new java.awt.event.ActionListener() {
//        /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//            timeout();
//        }
//    });
    mRefreshTimer = new QTimer(this);
    mRefreshTimer->setInterval(50000);
    connect(mRefreshTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    mRefreshTimer->setSingleShot(false);     // refresh until stopped by dispose
    mRefreshTimer->start();
}

/**
 * Internal routine to resend the speed on a timeout
 */
/*synchronized*/ /*protected*/ void LocoNetThrottle::timeout()
{
 QMutexLocker locker(&mutex);
 // clear the last known layout_spd so that we will actually send the
 // message.
 layout_spd = -1;
 setSpeedSetting(speedSetting);
}

/**
 * Get notified when underlying slot information changes
 */
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="FE_FLOATING_POINT_EQUALITY") // OK to compare floating point, notify on any change
/*public*/ void LocoNetThrottle::notifyChangedSlot(LocoNetSlot* pSlot)
{
 if (slot!=pSlot) log->error("notified of change in different slot");

 // Save current layout state of spd/dirf/snd so we won't run amok
 // toggling values if another LocoNet entity accesses the slot while
 // our most recent change request is still in-flight.
 layout_spd  = slot->speed();
 layout_dirf = slot->dirf();
 layout_snd  = slot->snd();

 // handle change in each state
 float newSpeed = ( floatSpeed(slot->speed() ) ) ;
 if (this->speedSetting != newSpeed)
 {
  log->debug( "notifyChangedSlot: old speed: " + QString::number(this->speedSetting) + " new Speed: " + QString::number(newSpeed ));
  notifyPropertyChangeListener("SpeedSetting", (this->speedSetting), newSpeed );
  this->speedSetting = newSpeed ;
 }

 bool temp;
 if (this->isForward != slot->isForward())
 {
  temp = this->isForward;
  this->isForward = slot->isForward();
  notifyPropertyChangeListener("IsForward", (temp), (slot->isForward()));
 }

 // Slot status
 if (slotStatus != slot->slotStatus())
 {
  int newStat = slot->slotStatus();
  if (log->isDebugEnabled())
      log->debug("Slot status changed from "+LnConstants::LOCO_STAT(slotStatus)+" to "+LnConstants::LOCO_STAT(newStat) );
  // PropertyChangeListeners notification: ThrottleConnected from True to False when disconnected
  notifyPropertyChangeListener("ThrottleConnected", (slotStatus & LnConstants::LOCOSTAT_MASK) == LnConstants::LOCO_IN_USE,
                                                      ! ( (slotStatus & LnConstants::LOCOSTAT_MASK) == LnConstants::LOCO_IN_USE) );
  slotStatus = newStat;
 }

 // Functions
 if (this->f0 != slot->isF0()) {
     temp = this->f0;
     this->f0 = slot->isF0();
     notifyPropertyChangeListener(Throttle::F0, (temp), (slot->isF0()));
 }
 if (this->f1 != slot->isF1()) {
     temp = this->f1;
     this->f1 = slot->isF1();
     notifyPropertyChangeListener(Throttle::F1, (temp), (slot->isF1()));
 }
 if (this->f2 != slot->isF2()) {
     temp = this->f2;
     this->f2 = slot->isF2();
     notifyPropertyChangeListener(Throttle::F2, (temp), (slot->isF2()));
 }
 if (this->f3 != slot->isF3()) {
     temp = this->f3;
     this->f3 = slot->isF3();
     notifyPropertyChangeListener(Throttle::F3, (temp), (slot->isF3()));
 }
 if (this->f4 != slot->isF4()) {
     temp = this->f4;
     this->f4 = slot->isF4();
     notifyPropertyChangeListener(Throttle::F4, (temp), (slot->isF4()));
 }
 if (this->f5 != slot->isF5()) {
     temp = this->f5;
     this->f5 = slot->isF5();
     notifyPropertyChangeListener(Throttle::F5, (temp), (slot->isF5()));
 }
 if (this->f6 != slot->isF6()) {
     temp = this->f6;
     this->f6 = slot->isF6();
     notifyPropertyChangeListener(Throttle::F6, (temp), (slot->isF6()));
 }
 if (this->f7 != slot->isF7()) {
     temp = this->f7;
     this->f7 = slot->isF7();
     notifyPropertyChangeListener(Throttle::F7, (temp), (slot->isF7()));
 }
 if (this->f8 != slot->isF8()) {
     temp = this->f8;
     this->f8 = slot->isF8();
     notifyPropertyChangeListener(Throttle::F8, (temp), (slot->isF8()));
 }

 // extended slot
 if (this->f9 != slot->isF9()) {
     temp = this->f9;
     this->f9 = slot->isF9();
     notifyPropertyChangeListener(Throttle::F9, (temp), (slot->isF9()));
 }
 if (this->f10 != slot->isF10()) {
     temp = this->f10;
     this->f10 = slot->isF10();
     notifyPropertyChangeListener(Throttle::F10, (temp), (slot->isF10()));
 }
 if (this->f11 != slot->isF11()) {
     temp = this->f11;
     this->f11 = slot->isF11();
     notifyPropertyChangeListener(Throttle::F11, (temp), (slot->isF11()));
 }
 if (this->f12 != slot->isF12()) {
     temp = this->f12;
     this->f12 = slot->isF12();
     notifyPropertyChangeListener(Throttle::F12, (temp), (slot->isF12()));
 }
 if (this->f13 != slot->isF13()) {
     temp = this->f13;
     this->f13 = slot->isF13();
     notifyPropertyChangeListener(Throttle::F13, (temp), (slot->isF13()));
 }
 if (this->f14 != slot->isF14()) {
     temp = this->f14;
     this->f14 = slot->isF14();
     notifyPropertyChangeListener(Throttle::F14, (temp), (slot->isF14()));
 }
 if (this->f15 != slot->isF15()) {
     temp = this->f15;
     this->f15 = slot->isF15();
     notifyPropertyChangeListener(Throttle::F15, (temp), (slot->isF15()));
 }
 if (this->f16 != slot->isF16()) {
     temp = this->f16;
     this->f16 = slot->isF16();
     notifyPropertyChangeListener(Throttle::F16, (temp), (slot->isF16()));
 }
 if (this->f17 != slot->isF17()) {
     temp = this->f17;
     this->f17 = slot->isF17();
     notifyPropertyChangeListener(Throttle::F17, (temp), (slot->isF17()));
 }
 if (this->f18 != slot->isF18()) {
     temp = this->f18;
     this->f18 = slot->isF18();
     notifyPropertyChangeListener(Throttle::F18, (temp), (slot->isF18()));
 }
 if (this->f19 != slot->isF19()) {
     temp = this->f19;
     this->f19 = slot->isF19();
     notifyPropertyChangeListener(Throttle::F19, (temp), (slot->isF19()));
 }
 if (this->f20 != slot->isF20()) {
     temp = this->f20;
     this->f20 = slot->isF20();
     notifyPropertyChangeListener(Throttle::F20, (temp), (slot->isF20()));
 }
 if (this->f21 != slot->isF21()) {
     temp = this->f21;
     this->f21 = slot->isF21();
     notifyPropertyChangeListener(Throttle::F21, (temp), (slot->isF21()));
 }
 if (this->f22 != slot->isF22()) {
     temp = this->f22;
     this->f22 = slot->isF22();
     notifyPropertyChangeListener(Throttle::F22, (temp), (slot->isF22()));
 }
 if (this->f23 != slot->isF23()) {
     temp = this->f23;
     this->f23 = slot->isF23();
     notifyPropertyChangeListener(Throttle::F23, (temp), (slot->isF23()));
 }
 if (this->f24 != slot->isF24()) {
     temp = this->f24;
     this->f24 = slot->isF24();
     notifyPropertyChangeListener(Throttle::F24, (temp), (slot->isF24()));
 }
 if (this->f25 != slot->isF25()) {
     temp = this->f25;
     this->f25 = slot->isF25();
     notifyPropertyChangeListener(Throttle::F25, (temp), (slot->isF25()));
 }
 if (this->f26 != slot->isF26()) {
     temp = this->f26;
     this->f26 = slot->isF26();
     notifyPropertyChangeListener(Throttle::F26, (temp), (slot->isF26()));
 }
 if (this->f27 != slot->isF27()) {
     temp = this->f27;
     this->f27 = slot->isF27();
     notifyPropertyChangeListener(Throttle::F27, (temp), (slot->isF27()));
 }
 if (this->f28 != slot->isF28()) {
     temp = this->f28;
     this->f28 = slot->isF28();
     notifyPropertyChangeListener(Throttle::F28, (temp), (slot->isF28()));
 }
}

/*
 * setSpeedStepMode - set the speed step value and the related
 *                    speedIncrement value.
 * <P>
 * specific implementations should override this function
 * <P>
 * @param Mode - the current speed step mode - default should be 128
 *              speed step mode in most cases
 */
//@Override
/*public*/ void LocoNetThrottle::setSpeedStepMode(int Mode)
{
 int status=slot->slotStatus();
 if(log->isDebugEnabled())
 {
  log->debug("Speed Step Mode Change to Mode: " + QString::number(Mode) +
            " Current mode is: " + QString::number(this->speedStepMode));
  log->debug("Current Slot Mode: " +LnConstants::DEC_MODE(status));
 }
 if(speedStepMode!=Mode)
   notifyPropertyChangeListener("SpeedSteps", this->speedStepMode,
                                          this->speedStepMode=Mode );
 if(Mode==DccThrottle::SpeedStepMode14)
 {
  speedIncrement=SPEED_STEP_14_INCREMENT;
  log->debug("14 speed step change");
  status=status&((~LnConstants::DEC_MODE_MASK)|
                            LnConstants::STAT1_SL_SPDEX)
                         | LnConstants::DEC_MODE_14;
 }
 else if(Mode==DccThrottle::SpeedStepMode28Mot)
 {
            speedIncrement=SPEED_STEP_28_INCREMENT;
            log->debug("28-Tristate speed step change");
            status=status&((~LnConstants::DEC_MODE_MASK)|
                            LnConstants::STAT1_SL_SPDEX)
                         | LnConstants::DEC_MODE_28TRI;
 }
 else if(Mode==DccThrottle::SpeedStepMode28)
 {
            speedIncrement=SPEED_STEP_28_INCREMENT;
            log->debug("28 speed step change");
            status=status&((~LnConstants::DEC_MODE_MASK)|
                            LnConstants::STAT1_SL_SPDEX)
                         | LnConstants::DEC_MODE_28;         // DEC_MODE_28 has a zero value, here for documentation
                                                            // but it unfortunately shows a INT_VACUOUS_BIT_OPERATION
                                                            // in Findbugs
 }
 else
 { // default to 128 speed step mode
            speedIncrement=SPEED_STEP_128_INCREMENT;
            log->debug("128 speed step change");
            status=status&((~LnConstants::DEC_MODE_MASK)|
                            LnConstants::STAT1_SL_SPDEX)
                         | LnConstants::DEC_MODE_128;
 }
 if(log->isDebugEnabled())
          log->debug("New Slot Mode: " +LnConstants::DEC_MODE(status));
 if(mRefreshTimer!=NULL) // the refresh timer isn't created until
                            // after initilization.  We only want to
                            // modify the slot after the initilization
                            // is complete.
 ((LnPacketizer*)network)->sendLocoNetMessage(slot->writeMode(status));
}



/*public*/ LocoAddress* LocoNetThrottle::getLocoAddress() {
    return new DccLocoAddress(address, LnThrottleManager::isLongAddress(address));
}

//    // initialize logging
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoNetThrottle::class.getName());

//}
