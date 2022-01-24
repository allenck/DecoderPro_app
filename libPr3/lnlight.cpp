#include "lnlight.h"
#include "lnlightmanager.h"

//LnLight::LnLight(QObject *parent) :
//    AbstractLight(parent)
//{
//}
/**
 * LnLight.java
 *
 * Implementation of the Light Object for Loconet
 * <P>
 *  Based in part on SerialLight.java
 *
 * @author      Dave Duchamp Copyright (C) 2006
 * @version     $Revision: 17977 $
 */
//public class LnLight extends AbstractLight {

/**
 * Create a Light object, with only system name.
 * <P>
 * 'systemName' was previously validated in LnLightManager
 */
/*public*/ LnLight::LnLight(QString systemName, LnTrafficController* tc, LnLightManager* mgr, QObject *parent) : AbstractLight(systemName, parent)
{
 // super(systemName);
 log = new Logger("LnLight");
 this->tc = tc;
 this->mgr = mgr;
 mBit = 0;
 // Initialize the Light
 initializeLight(systemName);
}
/**
 * Create a Light object, with both system and user names.
 * <P>
 * 'systemName' was previously validated in LnLightManager
 */
/*public*/ LnLight::LnLight(QString systemName, QString userName, LnTrafficController* tc, LnLightManager* mgr, QObject *parent) : AbstractLight(systemName, userName, parent)
{
 //super(systemName, userName);
 log = new Logger("LnLight");
 this->tc = tc;
 this->mgr = mgr;
 mBit = 0;
 initializeLight(systemName);
}


/*private*/ void LnLight::initializeLight(QString systemName)
{
 // Extract the Bit from the name
 mBit = mgr->getBitFromSystemName(systemName);
 // Set initial state
 setState( OFF );
}


/**
 *  Set the current state of this Light
 *     This routine requests the hardware to change.
 */
/*protected*/ void LnLight::doNewState(int /*oldState*/, int newState)
{
 LocoNetMessage* l = new LocoNetMessage(4);
 l->setOpCode(LnConstants::OPC_SW_REQ);
 // compute address fields
 int hiadr = (mBit-1)/128;
 int loadr = (mBit-1)-hiadr*128;
 // set bits for ON/OFF
 if (newState==ON)
 {
  hiadr |= 0x30;
 }
 else if (newState==OFF)
 {
  hiadr |= 0x10;
 }
 else
 {
//  log->warn("illegal state requested for Light: "+getSystemName());
     hiadr |= 0x10;
 }
 // store and send
 l->setElement(1,loadr);
 l->setElement(2,hiadr);
 tc->sendLocoNetMessage(l);
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnLight.class.getName());
//}
