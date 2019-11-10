#include "pushbuttonpacket.h"
#include "turnout.h"
#include "instancemanager.h"
#include "proxyturnoutmanager.h"
#include "abstractturnout.h"
#include "nmrapacket.h"
#include "loggerfactory.h"

PushbuttonPacket::PushbuttonPacket(QObject *parent) :
    QObject(parent)
{
}
/**
 * Generates an NMRA packet containing the correct payload to enable or
 * disable pushbutton lockout.  Currently supports the following Decoders
 * NCE
 * CVP AD4
 *
 *
 *
 * NCE is the easliest to implement, CV556 = 0 disable lockout, CV556 = 1 enable lockout
 *
 * CVP is a bit tricker, CV514 controls the lockout for four turnouts.  Each turnout
 * can have one or two button controls.  Therefore the user must specify if they are
 * using one or two buttons for each turnout.
 *
 * From the CVP user manual:
 *
 * Function			CV514
 * Lock all inputs	0
 * Unlock 1			1
 * Unlock 2			4
 * Unlock 3			16
 * Unlock 4			64
 * Unlock all		85
 * Enable 2 button	255
 *
 * This routine assumes that for two button operations the following table is true:
 *
 * Lock all inputs	0
 * Unlock 1			3
 * Unlock 2			12
 * Unlock 3			48
 * Unlock 4			192
 * Unlock all		255
 *
 * Each CVP can operate up to four turnouts, luckly for us, they are sequential.
 * Also note that CVP decoder's use the old legacy format for ops mode programming.
 *
 * @author      Daniel Boudreau Copyright (C) 2007
 * @version     $Revision: 17977 $
 *
 */
// /*public*/ class PushbuttonPacket {

/**
 * Valid stationary decoder names
 */
/*public*/ /*final*/ /*static*/ QString PushbuttonPacket::unknown = "None";
/*public*/ /*final*/ /*static*/ QString PushbuttonPacket::NCEname = "NCE_Rev_C";
/*public*/ /*final*/ /*static*/ QString PushbuttonPacket::CVP_1Bname = "CVP_AD4_1B";
/*public*/ /*final*/ /*static*/ QString PushbuttonPacket::CVP_2Bname = "CVP_AD4_2B";

/*private*/ /*final*/ /*static*/ QStringList PushbuttonPacket::VALIDDECODERNAMES = QStringList()
<<  PushbuttonPacket::unknown << PushbuttonPacket::NCEname << PushbuttonPacket::CVP_1Bname <<
    PushbuttonPacket::CVP_2Bname ;

/*public*/ /*static*/ QByteArray PushbuttonPacket::pushbuttonPkt(QString prefix, int turnoutNum, bool locked)
{
 AbstractTurnout* t = (AbstractTurnout*)((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getBySystemName(prefix + turnoutNum);
 QByteArray bl;

 if (t->getDecoderName()==(unknown))
  return NULL;

 else if (t->getDecoderName()==(NCEname))
 {
  if (locked)
   bl = NmraPacket::accDecoderPktOpsMode(turnoutNum, 556, 1);
  else
   bl = NmraPacket::accDecoderPktOpsMode(turnoutNum, 556, 0);
  return bl;

  // Note CVP decoders use the old legacy accessory  format
 }
 else if (t->getDecoderName()==(CVP_1Bname)
            || t->getDecoderName()==(CVP_2Bname))
 {
  int CVdata = CVPturnoutLockout(prefix, turnoutNum);
   bl = NmraPacket::accDecoderPktOpsModeLegacy(turnoutNum, 514, CVdata);
        return bl;
    } else {
        log.error("Invalid decoder name for turnout "+turnoutNum);
        return NULL;
    }
}

/*public*/ /*static*/ QStringList PushbuttonPacket::getValidDecoderNames() {
//    QStringList arrayCopy = new String[VALIDDECODERNAMES.length];
    QStringList arrayCopy = QStringList();

//    System.arraycopy(VALIDDECODERNAMES, 0, arrayCopy, 0, VALIDDECODERNAMES.length);
    foreach(QString s, VALIDDECODERNAMES)
    {
     arrayCopy.append(s);
    }

    return arrayCopy;
}

// builds the data byte for CVP decoders, builds based on JMRI's current
// knowledge of turnout pushbutton lockout states. If a turnout doesn't
// exist, assume single button operation.
/*private*/ /*static*/ int PushbuttonPacket::CVPturnoutLockout(QString prefix, int turnoutNum)
{
 Logger log("PushbuttonPacket::CVPturnoutLockout");
 int CVdata = 0;
 int oneButton = 1;							// one pushbutton enable
 int twoButton = 3;							// two pushbutton enable
 int modTurnoutNum = (turnoutNum-1) & 0xFFC; // mask off bits, there are 4 turnouts per
                                                // decoder

 for (int i = 0; i < 4; i++)
 {
  // set the default for one button in case the turnout doesn't exist
  int button = oneButton;
  modTurnoutNum++;
  AbstractTurnout* t = (AbstractTurnout*)((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getBySystemName(prefix + modTurnoutNum);
  if (t != NULL)
  {
   if (t->getDecoderName()==(CVP_1Bname))
   {
    // do nothing button already = oneButton
   }
   else if (t->getDecoderName()==(CVP_2Bname))
   {
    button = twoButton;
   } else {
                log.warn(tr("Turnout ") + QString::number(modTurnoutNum)
                        + ", all CVP turnouts on one decoder should be "
                        + CVP_1Bname + " or " + CVP_2Bname);
            }
            // zero out the bits if the turnout is locked
            if (t->getLocked(Turnout::PUSHBUTTONLOCKOUT)) {
                button = 0;
            }
        }
        CVdata = CVdata + button;
        oneButton = oneButton << 2; // move to the next turnout
        twoButton = twoButton << 2;

    }
    return CVdata;
}

/*private*/ /*final*/ /*static*/ Logger* PushbuttonPacket::log = LoggerFactory::getLogger("PushbuttonPacket");
