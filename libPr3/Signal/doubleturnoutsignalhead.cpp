#include "doubleturnoutsignalhead.h"
#include "turnout.h"
#include "signalhead.h"

//DoubleTurnoutSignalHead::DoubleTurnoutSignalHead(QObject *parent) :
//    DefaultSignalHead(parent)
//{
//}
/**
 * Drive a single signal head via two "Turnout" objects.
 * <P>
 * After much confusion, the user-level terminology
 * was changed to call these "Double Output"; the class
 * name remains the same to reduce recoding.
 * <P>
 * The two Turnout objects are provided during construction,
 * and each drives a specific color (RED and GREEN).
 * Normally, "THROWN" is on, and "CLOSED" is off.
 * YELLOW is provided by turning both on ("THROWN")
 * <P>
 * This class doesn't currently listen to the Turnout's to see if they've
 * been changed via some other mechanism.
 *
 * @author	Bob Jacobsen Copyright (C) 2003, 2008
 * @version	$Revision: 17977 $
 */
///*public*/ class DoubleTurnoutSignalHead extends DefaultSignalHead {

/*public*/ DoubleTurnoutSignalHead::DoubleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent) : DefaultSignalHead(sys, user, parent){
   // super(sys, user);
log = new Logger("DoubleTurnoutSignalHead");
    mRed = red;
    mGreen = green;
}

/*public*/ DoubleTurnoutSignalHead::DoubleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent) : DefaultSignalHead(sys, parent) {
    //super(sys);
log = new Logger("DoubleTurnoutSignalHead");
    mRed = red;
    mGreen = green;
}

//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
/*protected*/ void DoubleTurnoutSignalHead::updateOutput()
{
 // assumes that writing a turnout to an existing state is cheap!
 if (mLit == false)
 {
  mRed->getBean()->setCommandedState(Turnout::CLOSED);
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
  mGreen->getBean()->setCommandedState(Turnout::CLOSED);
  return;

 }
 else
 {
//        switch (mAppearance) {
//            case RED:
//            case FLASHRED:
  if(mAppearance == SignalHead::FLASHRED || mAppearance == SignalHead::RED )
  {
   mRed->getBean()->setCommandedState(Turnout::THROWN);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
  }
//                break;
//            case YELLOW:
//            case FLASHYELLOW:
  else if(mAppearance == SignalHead::FLASHYELLOW || mAppearance == SignalHead::YELLOW )
  {
   mRed->getBean()->setCommandedState(Turnout::THROWN);
   mGreen->getBean()->setCommandedState(Turnout::THROWN);
  }
//                break;
//            case GREEN:
//            case FLASHGREEN:
  else if(mAppearance == SignalHead::FLASHGREEN || mAppearance == SignalHead::GREEN )
  {
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::THROWN);
  }
//                break;
//            default:
  else
  {
   log->warn("Unexpected new appearance: "+QString::number(mAppearance) + "(" + getAppearanceName(mAppearance)+ ")");
  // go dark by falling through
//            case DARK:
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
//                break;
  }
 }
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void DoubleTurnoutSignalHead::dispose() {
    mRed = NULL;
    mGreen = NULL;
    DefaultSignalHead::dispose();
}

/*public*/ NamedBeanHandle<Turnout*>* DoubleTurnoutSignalHead::getRed() {return mRed;}
/*public*/ NamedBeanHandle<Turnout*>* DoubleTurnoutSignalHead::getGreen() {return mGreen;}
/*public*/ void DoubleTurnoutSignalHead::setRed(NamedBeanHandle<Turnout*>* t) {mRed=t;}
/*public*/ void DoubleTurnoutSignalHead::setGreen(NamedBeanHandle<Turnout*>* t) {mGreen=t;}
