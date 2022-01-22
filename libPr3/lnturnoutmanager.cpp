#include "lnturnoutmanager.h"
#include "instancemanager.h"
#include "lnturnout.h"
#include "exceptions.h"
#include "locobufferadapter.h"

LnTurnoutManager::LnTurnoutManager(LnTrafficController* fastcontroller, LnTrafficController* throttledcontroller, QString prefix, bool mTurnoutNoRetry, QObject* parent) : AbstractTurnoutManager(nullptr,parent)
{
 setObjectName("LnTurnoutManager");
 setProperty("JavaClassName", "jmri.jmrix.loconet.LnTurnoutManager");
 this->fastcontroller = fastcontroller;
 this->throttledcontroller = throttledcontroller;
 this->prefix = prefix.mid(0,1);
 this->mTurnoutNoRetry = mTurnoutNoRetry;
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

 lastSWREQ = NULL;

 if (fastcontroller != NULL)
 {
  fastcontroller->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(fastcontroller, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 else
  log.error("No layout connection, turnout manager can't function");
}

// ctor has to register for LocoNet events
/*public*/ LnTurnoutManager::LnTurnoutManager(LocoNetSystemConnectionMemo* memo, LocoNetInterface* throttledcontroller, bool mTurnoutNoRetry, QObject* parent)
 : AbstractTurnoutManager(memo, parent)
{
    //super(memo);
 setObjectName("LnTurnoutManager");
 setProperty("JavaClassName", "jmri.jmrix.loconet.LnTurnoutManager");
    this->fastcontroller = memo->getLnTrafficController();
    this->throttledcontroller = throttledcontroller;
    this->mTurnoutNoRetry = mTurnoutNoRetry;
    this->prefix = memo->getSystemPrefix();

    if (fastcontroller != nullptr) {
        fastcontroller->addLocoNetListener(~0, (LocoNetListener*)this);
    connect(fastcontroller, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
    } else {
        log.error("No layout connection, turnout manager can't function");
    }
    registerSelf();
}

//public class LnTurnoutManager extends jmri.managers.AbstractTurnoutManager implements LocoNetListener {

//    // ctor has to register for LocoNet events
//    public LnTurnoutManager(/*LocoNetInterface*/LnTrafficController fastcontroller, /*LocoNetInterface*/LnTrafficController throttledcontroller, String prefix, boolean mTurnoutNoRetry) {
//        this.fastcontroller = fastcontroller;
//        this.throttledcontroller = throttledcontroller;
//        this.prefix = prefix;
//        this.mTurnoutNoRetry = mTurnoutNoRetry;

//        if (fastcontroller != NULL)
//            fastcontroller.addLocoNetListener(~0, this);
//        else
//            log.error("No layout connection, turnout manager can't function");
//    }

void LnTurnoutManager::dispose()
{
 if (fastcontroller != NULL)
  fastcontroller->removeLocoNetListener(~0, (LocoNetListener*)this);

 //super.dispose();
}

Turnout* LnTurnoutManager::createNewTurnout(QString systemName, QString userName)
{
 int addr;
 bool bok;
        //addr = Integer.valueOf(systemName.substring(getSystemPrefix().length()+1)).intValue();
  addr = systemName.mid(AbstractManager::getSystemPrefix().length()+1).toInt(&bok);
 if(!bok)
 {
  throw new IllegalArgumentException("Can't convert "+systemName.mid(AbstractManager::getSystemPrefix().length()+1)+" to LocoNet turnout address");
 }
 LnTurnout* t = new LnTurnout(AbstractManager::getSystemPrefix(), addr, throttledcontroller);
 t->setUserName(userName);
 return (Turnout*)t;
}

// listen for turnouts, creating them as needed
void LnTurnoutManager::message(LocoNetMessage* l)
{
 // parse message type
 int addr;
 switch (l->getOpCode())
 {
 case LnConstants::OPC_SW_REQ:
 {               /* page 9 of Loconet PE */
  int sw1 = l->getElement(1);
  int sw2 = l->getElement(2);
  addr = address(sw1, sw2);

  // store message in case resend is needed
  lastSWREQ = l;

  // Loconet spec says 0x10 of SW2 must be 1, but we observe 0
  if ( ((sw1&0xFC)==0x78) && ((sw2&0xCF)==0x07) ) return;  // turnout interrogate msg
  if (log.isDebugEnabled()) log.debug("SW_REQ received with address "+addr);
  break;
 }
 case LnConstants::OPC_SW_REP:
 {                /* page 9 of Loconet PE */
  // clear resend message, indicating not to resend
  lastSWREQ = NULL;

  // process this request
  int sw1 = l->getElement(1);
  int sw2 = l->getElement(2);
  addr = address(sw1, sw2);
  if (log.isDebugEnabled()) log.debug("SW_REP received with address "+addr);
  break;
 }
 case LnConstants::OPC_LONG_ACK:
 {
  // might have to resend, check 2nd byte
  if (lastSWREQ!=NULL && l->getElement(1)==0x30 && l->getElement(2)==0 && !mTurnoutNoRetry)
  {
   // received LONG_ACK reject msg, resend
   fastcontroller->sendLocoNetMessage(lastSWREQ);
  }

  // clear so can't resend recursively (we'll see
  // the resent message echo'd back)
  lastSWREQ = NULL;
  return;
 }
 default:  // here we didn't find an interesting command
  // clear resend message, indicating not to resend
  lastSWREQ = NULL;
  return;
 }
 // reach here for loconet switch command; make sure we know about this one
 QString s = prefix+"T"+QString("%1").arg(addr);
 if (getBySystemName(s) == NULL)
 {
  // no turnout with this address, is there a light
  QString sx = "LL"+QString("%1").arg(addr);
#if 1 // TODO:
  //if (InstanceManager::lightManagerInstance().getBySystemName(sx) == NULL)
  {
   // no light, create a turnout
   LnTurnout* t = (LnTurnout*) provideTurnout(s);
   t->message(l);
  }
#endif
 }
}

int LnTurnoutManager::address(int a1, int a2) {
    // the "+ 1" in the following converts to throttle-visible numbering
    return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1);
}

/*public*/ /*static*/ /*final*/ QString LnTurnoutManager::BYPASSBUSHBYBITKEY = "Bypass Bushby Bit";
/*public*/ /*static*/ /*final*/ QString LnTurnoutManager::SENDONANDOFFKEY = "Send ON/OFF";

    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnTurnoutManager.class.getName());
