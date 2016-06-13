#include "se8csignalhead.h"
#include "turnout.h"
#include "instancemanager.h"
#include "abstractturnoutmanager.h"
#include "signalhead.h"

//SE8cSignalHead::SE8cSignalHead(QObject *parent) :
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
 * <P>
 * We can't assume any form of numbering for Turnouts to address the digits,
 * so we take two turnout names as arguments.  As a convenience, we
 * manage the user names if they're not already set.
 * <P>The algorithms in this class are a collaborative effort of Digitrax, Inc
 * and Bob Jacobsen.
 *
 * @author			Bob Jacobsen Copyright (C) 2002
 * @version			$Revision: 17977 $
 */
///*public*/ class SE8cSignalHead extends DefaultSignalHead {

/**
 * Primary ctor
 * @param lowTO Lower-numbered Turnout reference
 * @param highTO higher-numbered Turnout reference
 */
/*public*/ SE8cSignalHead::SE8cSignalHead(NamedBeanHandle<Turnout*>* lowTO,
                        NamedBeanHandle<Turnout*>* highTO,
                        QString userName, QObject *parent)
    : DefaultSignalHead(makeSystemName(lowTO, highTO), userName, parent)
{
    // create systemname
    //super(makeSystemName(lowTO,highTO), userName);
    this->lowTurnout = lowTO;
    this->highTurnout = highTO;
    systemName = makeSystemName(lowTO,highTO);
    init();
}

///**
// * Primary ctor without user name
// * @param lowTO Lower-numbered Turnout reference
// * @param highTO higher-numbered Turnout reference
// */
///*public*/ SE8cSignalHead(NamedBeanHandle<Turnout> lowTO,
//                        NamedBeanHandle<Turnout> highTO) {
//    // create systemname
//    super(makeSystemName(lowTO,highTO));
//    this.lowTurnout = lowTO;
//    this.highTurnout = highTO;
//    systemName = makeSystemName(lowTO,highTO);
//    init();
//}

/**
 * Ctor for specifying system name
 * @param lowTO Lower-numbered Turnout reference
 * @param highTO higher-numbered Turnout reference
 */
/*public*/ SE8cSignalHead::SE8cSignalHead(QString sname, NamedBeanHandle<Turnout*>* lowTO,
                        NamedBeanHandle<Turnout*>* highTO,
                          QString userName, QObject *parent) : DefaultSignalHead(sname, userName, parent)
{
    // create systemname
    //super(sname, userName);
    this->lowTurnout = lowTO;
    this->highTurnout = highTO;
    systemName = sname;
    init();
}

///**
// * Ctor for specifying system name
// * @param lowTO Lower-numbered Turnout reference
// * @param highTO higher-numbered Turnout reference
// */
///*public*/ SE8cSignalHead(QString sname, NamedBeanHandle<Turnout> lowTO,
//                        NamedBeanHandle<Turnout> highTO) {
//    // create systemname
//    super(sname);
//    this.lowTurnout = lowTO;
//    this.highTurnout = highTO;
//    systemName = sname;
//    init();
//}

/**
 * Implement convention for making a system name.
 * Must pass arguments, as used before object is complete
 */
/*static*/ QString SE8cSignalHead::makeSystemName(NamedBeanHandle<Turnout*>* lowTO,
                        NamedBeanHandle<Turnout*>* highTO) {
    return ("IH:SE8c:\""+lowTO->getName()+"\";\""+highTO->getName()+"\"").toUpper();
}

/**
 * Compatibility ctor
 * @param pNumber number (address) of low turnout
 */
/*public*/ SE8cSignalHead::SE8cSignalHead(int pNumber, QString userName, QObject *parent) : DefaultSignalHead("LH"+QString::number(pNumber), userName,parent)
{
    //super("LH"+pNumber, userName);
    this->lowTurnout = makeHandle(pNumber);
    this->highTurnout = makeHandle(pNumber+1);
    systemName = "LH"+pNumber;
    init();
}

/**
 * Create a handle from a raw number.
 * Static, so can be referenced before ctor complete.
 */
/*static*/ NamedBeanHandle<Turnout*>* SE8cSignalHead::makeHandle(int i)
{
   QString number = QString::number(i);
   return ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(
        number,
        ((AbstractTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(number)
    );
}

///**
// * Compatibility ctor
// * @param pNumber number (address) of low turnout
// */
///*public*/ SE8cSignalHead::SE8cSignalHead(int pNumber, QObject* parent) : DefaultSignalHead("LH"+QString::number(pNumber), "", parent)
//{
//   // super("LH"+pNumber);
//    this->lowTurnout = makeHandle(pNumber);
//    this->highTurnout = makeHandle(pNumber+1);
//    systemName = "LH"+QString::number(pNumber);
//    init();
//}


void SE8cSignalHead::init() {
    log = new Logger("SE8cSignalHead");
    // basic operation, nothing but ON messages needed
    lowTurnout->getBean()->setBinaryOutput(true);
    highTurnout->getBean()->setBinaryOutput(true);

    // ensure default appearance
    mAppearance = SignalHead::DARK;  // start turned off
    updateOutput();
}

/*public*/ QString SE8cSignalHead::getSystemName() {
    return systemName;
}

// Handle a request to change state by sending a LocoNet command
/*protected*/ void SE8cSignalHead::updateOutput()  {
 if (!mLit) {
  highTurnout->getBean()->setCommandedState(Turnout::CLOSED);
 } else if ( !mFlashOn &&
             ( (mAppearance == SignalHead::FLASHGREEN) ||
               (mAppearance == SignalHead::FLASHYELLOW) ||
               (mAppearance == SignalHead::FLASHRED) ) ) {
  // flash says to make output dark;
  // flashing-but-lit is handled below
  highTurnout->getBean()->setCommandedState(Turnout::CLOSED);
 } else {
  // which of the four states?
  //        switch (mAppearance) {
  //        case FLASHRED:
  //        case RED:
  if(mAppearance== SignalHead::FLASHRED || mAppearance == SignalHead::RED)
   lowTurnout->getBean()->setCommandedState(Turnout::THROWN);
  //            break;
  //        case FLASHYELLOW:
  //        case YELLOW:
  else if(mAppearance== SignalHead::FLASHYELLOW || mAppearance == SignalHead::YELLOW)
   highTurnout->getBean()->setCommandedState(Turnout::THROWN);
  //            break;
  //        case FLASHGREEN:
  //        case GREEN:
  //        break;
  else if(mAppearance== SignalHead::FLASHGREEN || mAppearance == SignalHead::GREEN)
   lowTurnout->getBean()->setCommandedState(Turnout::CLOSED);
  else if(mAppearance == SignalHead::DARK)
   //        case DARK:
   highTurnout->getBean()->setCommandedState(Turnout::CLOSED);
  //break;
  // default:
  else
   log->error("Invalid state request: "+QString::number(mAppearance));
  return;
  //        }
 }
}

/*public*/ NamedBeanHandle<Turnout*>* SE8cSignalHead::getLow() { return lowTurnout; }
/*public*/ NamedBeanHandle<Turnout*>* SE8cSignalHead::getHigh() { return highTurnout; }

/*public*/ void SE8cSignalHead::dispose() {
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(SE8cSignalHead.class.getName());
//}
