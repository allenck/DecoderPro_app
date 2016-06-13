#include "tripleturnoutsignalhead.h"
#include "turnout.h"

//TripleTurnoutSignalHead::TripleTurnoutSignalHead(QObject *parent) :
//    DoubleTurnoutSignalHead(parent)
//{
//}
/**
 * Drive a single signal head via three "Turnout" objects.
 * <P>
 * After much confusion, the user-level terminology 
 * was changed to call these "Triple Output"; the class
 * name remains the same to reduce recoding.
 * <P>
 * The three Turnout objects are provided during construction,
 * and each drives a specific color (RED, YELLOW and GREEN).
 * Normally, "THROWN" is on, and "CLOSED" is off.
 * <P>
 * This class doesn't currently listen to the Turnout's to see if they've
 * been changed via some other mechanism.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2008
 * @version	$Revision: 17977 $
 */
// /*public*/ class TripleTurnoutSignalHead extends DoubleTurnoutSignalHead {

/*public*/ TripleTurnoutSignalHead::TripleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, QObject *parent) : DoubleTurnoutSignalHead(sys, user,green, red, parent)
{
    //super(sys, user, green, red);
    mYellow = yellow;
}

/*public*/ TripleTurnoutSignalHead::TripleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, QObject *parent) : DoubleTurnoutSignalHead(sys, green, red, parent)
{
    //super(sys, green, red);
    mYellow = yellow;
}

//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
/*protected*/ void TripleTurnoutSignalHead::updateOutput()
{
 // assumes that writing a turnout to an existing state is cheap!
 if (mLit == false)
 {
  mRed->getBean()->setCommandedState(Turnout::CLOSED);
  mYellow->getBean()->setCommandedState(Turnout::CLOSED);
  mGreen->getBean()->setCommandedState(Turnout::CLOSED);
  return;
 }
 else if ( !mFlashOn &&
        ( (mAppearance == SignalHead::FLASHGREEN) ||
        (mAppearance == SignalHead::FLASHYELLOW) ||
        (mAppearance == SignalHead::FLASHRED) ) )
 {
  // flash says to make output dark
  mRed->getBean()->setCommandedState(Turnout::CLOSED);
  mYellow->getBean()->setCommandedState(Turnout::CLOSED);
  mGreen->getBean()->setCommandedState(Turnout::CLOSED);
  return;
 }
 else
 {
  switch (mAppearance)
  {
  case SignalHead::RED:
  case SignalHead::FLASHRED:
   mRed->getBean()->setCommandedState(Turnout::THROWN);
   mYellow->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
   break;
  case SignalHead::YELLOW:
  case SignalHead::FLASHYELLOW:
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mYellow->getBean()->setCommandedState(Turnout::THROWN);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
   break;
  case SignalHead::GREEN:
  case SignalHead::FLASHGREEN:
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mYellow->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::THROWN);
   break;
  default:
   log->warn("Unexpected new appearance: "+mAppearance);
   // go dark by falling through
  case SignalHead::DARK:
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mYellow->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
   break;
  }
 }
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void TripleTurnoutSignalHead::dispose() {
    mYellow = NULL;
    DoubleTurnoutSignalHead::dispose();
}


/*public*/ NamedBeanHandle<Turnout*>* TripleTurnoutSignalHead::getYellow() {return mYellow;}
/*public*/ void TripleTurnoutSignalHead::setYellow(NamedBeanHandle<Turnout*>* t) {mYellow=t;}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(TripleTurnoutSignalHead.class.getName());
//}
