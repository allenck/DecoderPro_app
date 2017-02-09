#include "lnpowermanager.h"
#include "loconetlistener.h"

//LnPowerManager::LnPowerManager(QObject *parent) :
//    AbstractPowerManager(parent)
//{
//}
LnPowerManager::LnPowerManager(LocoNetSystemConnectionMemo* memo, QObject *parent) :
    AbstractPowerManager(memo, parent)
{
//    super(memo);
 power = UNKNOWN;
 tc = NULL;
 // standard LocoNet - connect
 if(memo->getLnTrafficController()==NULL)
 {
  log.error("Power Manager Created, yet there is no Traffic Controller");
  return;
 }
 this->tc = memo->getLnTrafficController();
 tc->addLocoNetListener(~0, (LocoNetListener*)this);
 connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));

 updateTrackPowerStatus();  // this delays a while then reads slot 0 to get current track status
}


void LnPowerManager::setPower(int v) // throws JmriException
{
 int oldPower = power;
 power = UNKNOWN;

 checkTC();
 if (v==ON)
 {
  // send GPON
  LocoNetMessage* l = new LocoNetMessage(2);
  l->setOpCode(LnConstants::OPC_GPON);
  tc->sendLocoNetMessage(l);
 }
 else if (v==OFF)
 {
  // send GPOFF
  LocoNetMessage* l = new LocoNetMessage(2);
  l->setOpCode(LnConstants::OPC_GPOFF);
  tc->sendLocoNetMessage(l);
 }
 firePropertyChange("Power", oldPower, power);
}

int LnPowerManager::getPower() { return power;}


// to free resources when no longer used
void LnPowerManager::dispose() {
    if (tc!=NULL) tc->removeLocoNetListener(~0, (LocoNetListener*)this);
    tc = NULL;
}


void LnPowerManager::checkTC() // throws JmriException
{
 if (tc == NULL)
 {
  log.error("Use power manager after dispose");
  //throw new std::exception(); //("Use power manager after dispose");
 }
}

// to listen for status changes from LocoNet
void LnPowerManager::message(LocoNetMessage* m)
{
 int oldPower = power;
 if (m->getOpCode() == LnConstants::OPC_GPON)
 {
  power = ON;
  firePropertyChange("Power", QVariant(), QVariant());
 }
 else if (m->getOpCode() == LnConstants::OPC_GPOFF)
 {
  power = OFF;
  firePropertyChange("Power", QVariant(), QVariant());
 }
 else if (m->getOpCode() == LnConstants::OPC_SL_RD_DATA)
 {
  // grab the track status any time that a slot read of a "normal" slot passes thru.
  // Ignore "reserved" and "master control" slots in slot numbers 120-127
  if ((m->getElement(1) == 0x0E) || (m->getElement(2) < 120))
  {
   int slotTrackStatus =
                    ((m->getElement(7) & LnConstants::GTRK_POWER) == LnConstants::GTRK_POWER) ? ON : OFF;
   if (power != slotTrackStatus)
   {
    // fire a property change only if slot status is DIFFERENT
    // from current local status
    power = slotTrackStatus; // update local track status from slot info
    firePropertyChange("Power", oldPower, power);
   }
  }\
 }
}

/**
 * Creates a thread which delays and then queries slot 0 to get the current
 * track status.  The LnListener will see the slot read data and use the
 * current track status to update the LnPowerManager's internal track
 * power state info.
 */

void LnPowerManager::updateTrackPowerStatus()
{
 LnTrackStatusUpdateThread* thread = new LnTrackStatusUpdateThread(tc);
 thread->start();
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnPowerManager.class.getName());
