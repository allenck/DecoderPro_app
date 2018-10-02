#include "lnse8csignalhead.h"
#include "instancemanager.h"
#include "lntrafficcontroller.h"

//Se8cSignalHead::Se8cSignalHead(QObject *parent) :
//    DefaultSignalHead(parent)
//{
//}
/**
 * Extend jmri.SignalHead for signals implemented by an SE8c
 * <P>
 * This implementation writes out to the physical signal when
 * it's commanded to change appearance, and updates its internal state
 * when it hears commands from other places.
 * <P>To get a complete set of aspects, we assume that the
 * SE8C board has been configured such that the 4th aspect is "dark".
 * We then do flashing aspects by commanding the lit appearance to change.
 *
 * <p>
 * This is a grandfathered implementation that is specific to
 * loconet systems.  A more general implementation, which can work
 * with any system(s), is available in {@link jmri.implementation.SE8cSignalHead}.
 * This package is maintained so that existing XML files can continue
 * to be read.  In particular, it only works with the first LocoNet
 * connection (names LHnnn, not L2Hnnn etc).
 *
 * <P>The algorithms in this class are a collaborative effort of Digitrax, Inc
 * and Bob Jacobsen.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 *
 * @author			Bob Jacobsen Copyright (C) 2002
 * @version			$Revision: 17977 $
 */
///*public*/ class SE8cSignalHead extends DefaultSignalHead implements LocoNetListener {

/*public*/ LnSE8cSignalHead::LnSE8cSignalHead(int pNumber, QString userName, QObject *parent) : DefaultSignalHead("LH"+QString::number(pNumber), userName, parent)
{
    // create systemname
    //super("LH"+pNumber, userName);
    init(pNumber);
}

///*public*/ Se8cSignalHead::SE8cSignalHead(int pNumber, QObject *parent) {
//    // create systemname
//    super("LH"+pNumber);
//    init(pNumber);
//}

void LnSE8cSignalHead::init(int pNumber)
{
    log = new Logger("Se8cSignalHead");
    tc = (LnTrafficController*)InstanceManager::getDefault("LnTrafficController");
    mNumber = pNumber;
    mAppearance = SignalHead::DARK;  // start turned off
    // At construction, register for messages
    tc->addLocoNetListener(~0, (LocoNetListener*)this);
    updateOutput();
}


/*public*/ int LnSE8cSignalHead::getNumber() { return mNumber; }
/*public*/ QString LnSE8cSignalHead::getSystemName() { return "LH"+getNumber(); }

// Handle a request to change state by sending a LocoNet command
/*protected*/ void LnSE8cSignalHead::updateOutput()
{
 // send SWREQ for close
 LocoNetMessage* l = new LocoNetMessage(4);
 l->setOpCode(LnConstants::OPC_SW_REQ);

 int address = 0;
 bool closed = false;
 if (!mLit) {
     address = mNumber+1;
     closed = true;
 } else if ( !mFlashOn &&
             ( (mAppearance == SignalHead::FLASHGREEN) ||
               (mAppearance == SignalHead::FLASHYELLOW) ||
               (mAppearance == SignalHead::FLASHRED) ) )
 {
  // flash says to make output dark;
  // flashing-but-lit is handled below
  address = mNumber+1;
  closed = true;
 }
 else
 {
     // which of the four states?
//        switch (mAppearance) {
//        case SignalHead::FLASHRED:
//        case SignalHead::RED:
  if(mAppearance == SignalHead::FLASHRED || mAppearance == SignalHead::RED)
  {
      address = mNumber;
      closed = false;
  }
//        case SignalHead::FLASHYELLOW:
//        case SignalHead::YELLOW:
  if(mAppearance == SignalHead::FLASHYELLOW || mAppearance == SignalHead::YELLOW)
  {  address = mNumber+1;
      closed = false;
  }
//        case SignalHead::FLASHGREEN:
//        case SignalHead::GREEN:
  if(mAppearance == SignalHead::FLASHGREEN || mAppearance == SignalHead::GREEN)
  {
      address = mNumber;
      closed = true;
  }
  //case SignalHead::DARK:
  if(mAppearance == SignalHead::DARK)
  {
      address = mNumber+1;
      closed = true;
  }
  else
  {
      log->error("Invalid state request: "+QString::number(mAppearance));
      return;
  }
 }
 // compute address fields
 int hiadr = (address-1)/128;
 int loadr = (address-1)-hiadr*128;
 if (closed) hiadr |= 0x20;

 // set "on" bit
 hiadr |= 0x10;

 // store and send
 l->setElement(1,loadr);
 l->setElement(2,hiadr);
 tc->sendLocoNetMessage(l);
}

// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
//		/*public*/ void firePropertyChange(QString propertyName,
//						Object oldValue,
//						Object newValue)
// _once_ if anything has changed state (or set the commanded state directly)
/*public*/ void LnSE8cSignalHead::message(LocoNetMessage* l) {
    int oldAppearance = mAppearance;
    // parse message type
    switch (l->getOpCode()) {
    case LnConstants::OPC_SW_REQ: {               /* page 9 of Loconet PE */
        int sw1 = l->getElement(1);
        int sw2 = l->getElement(2);
        if (myAddress(sw1, sw2)) {
            if ((sw2 & LnConstants::OPC_SW_REQ_DIR)!=0) {
                // was set CLOSED
                if (mAppearance!=SignalHead::FLASHGREEN)
                    mAppearance =SignalHead:: GREEN;
            } else {
                // was set THROWN
                if (mAppearance!=SignalHead::FLASHRED)
                    mAppearance = SignalHead::RED;
            }
        }
        if (myAddressPlusOne(sw1, sw2)) {
            if ((sw2 & LnConstants::OPC_SW_REQ_DIR)!=0) {
                // was set CLOSED, which means DARK
                // don't change if one of the possibilities already
                if ( ! (mAppearance==SignalHead::FLASHYELLOW|| mAppearance==SignalHead::DARK
                        || mAppearance==SignalHead::FLASHGREEN || mAppearance==SignalHead::FLASHRED
                        || !mLit || !mFlashOn ))
                    mAppearance = SignalHead::DARK;    // that's the setting by default
            } else {
                // was set THROWN
                if (mAppearance!=SignalHead::FLASHYELLOW)
                    mAppearance = SignalHead::YELLOW;
            }
        }
        break;
    }
    case LnConstants::OPC_SW_REP:
    {               /* page 9 of Loconet PE */
        int sw1 = l->getElement(1);
        int sw2 = l->getElement(2);
        if (myAddress(sw1, sw2))
        {
            // see if its a turnout state report
            if ((sw2 & LnConstants::OPC_SW_REP_INPUTS)==0)
            {
                // sort out states
                if ((sw2 & LnConstants::OPC_SW_REP_CLOSED) != 0)
                {
                    // was set CLOSED
                    if (mAppearance!=SignalHead::FLASHGREEN)
                        mAppearance = SignalHead::GREEN;
                }
                if ((sw2 & LnConstants::OPC_SW_REP_THROWN) != 0) {
                    // was set THROWN
                    if (mAppearance!=SignalHead::FLASHRED)
                        mAppearance = SignalHead::RED;
                }
            }
        }
        if (myAddressPlusOne(sw1, sw2)) {
            // see if its a turnout state report
            if ((sw2 & LnConstants::OPC_SW_REP_INPUTS)==0) {
                // was set CLOSED, which means DARK
                // don't change if one of the possibilities already
                if ( ! (mAppearance==SignalHead::FLASHYELLOW|| mAppearance==SignalHead::DARK
                        || mAppearance==SignalHead::FLASHGREEN || mAppearance==SignalHead::FLASHRED
                        || !mLit || !mFlashOn ))
                    mAppearance = SignalHead::DARK;    // that's the setting by default
            }
            if ((sw2 & LnConstants::OPC_SW_REP_THROWN) != 0) {
                // was set THROWN
                if (mAppearance!=SignalHead::FLASHYELLOW)
                    mAppearance = SignalHead::YELLOW;
            }
        }
        return;
    }
    default:
        return;
    }
    // reach here if the state has updated
    if (oldAppearance != mAppearance) {
        firePropertyChange("Appearance", QVariant(oldAppearance), QVariant(mAppearance));
    }
}

/*public*/ void LnSE8cSignalHead::dispose() {
    tc->removeLocoNetListener(~0, (LocoNetListener*)this);
}

// data members
int mNumber;   // loconet turnout number with lower address (0 based)

/*private*/ bool LnSE8cSignalHead::myAddress(int a1, int a2) {
    // the "+ 1" in the following converts to throttle-visible numbering
    return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1) == mNumber;
}
/*private*/ bool LnSE8cSignalHead::myAddressPlusOne(int a1, int a2) {
    // the "+ 1" in the following converts to throttle-visible numbering
    return (((a2 & 0x0f) * 128) + (a1 & 0x7f) + 1) == mNumber+1;
}
//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SE8cSignalHead.class.getName());

//}
