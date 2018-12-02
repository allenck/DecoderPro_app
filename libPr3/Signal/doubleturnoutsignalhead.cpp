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

/*public*/ void DoubleTurnoutSignalHead::setRed(NamedBeanHandle<Turnout*>* t)
{
 if(mRed != nullptr)
  disconnect(mRed->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 mRed=t;
 if(mRed != nullptr)
  connect(mRed->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void DoubleTurnoutSignalHead::setGreen(NamedBeanHandle<Turnout*>* t)
{
 if(mGreen != nullptr)
  disconnect(mGreen->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 mGreen=t;
 if(mGreen != nullptr)
  connect(mGreen->getBean()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

}

//@Override
bool DoubleTurnoutSignalHead::isTurnoutUsed(Turnout* t)
{
    if (getRed() != nullptr && t->equals(getRed()->getBean())) {
        return true;
    }
    if (getGreen() != nullptr && t->equals(getGreen()->getBean())) {
        return true;
    }
    return false;
}


//private PropertyChangeListener turnoutChangeListener = new PropertyChangeListener() {
//    @Override
/*public*/ void DoubleTurnoutSignalHead::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
    if (propertyChangeEvent->getPropertyName()==("KnownState")) {
        if (propertyChangeEvent->getSource() == (mRed->getBean()) && propertyChangeEvent->getNewValue() == (mRedCommanded)) {
            return; // ignore change that we commanded
        }
        if (propertyChangeEvent->getSource() == (mGreen->getBean()) && propertyChangeEvent->getNewValue() == (mGreenCommanded)) {
            return; // ignore change that we commanded
        }
        if (readUpdateTimer == nullptr) {
//            readUpdateTimer = new QTimer(200, (ActionEvent actionEvent) ->
//                    readOutput());
            //readUpdateTimer.setRepeats(false);
         readUpdateTimer = new QTimer();
         readUpdateTimer->setInterval(200);
         readUpdateTimer->setSingleShot(true);
         connect(readUpdateTimer, SIGNAL(timeout()), this, SLOT(readOutput()));
            readUpdateTimer->start();
        } else {
            readUpdateTimer->start(200);
        }
    }
}
//};

/**
* Checks if the turnouts' output state matches the commanded output state; if not, then
* changes the appearance to match the output's current state.
*/
void DoubleTurnoutSignalHead::readOutput() {
 if ((mAppearance == FLASHGREEN)
         || (mAppearance == FLASHYELLOW)
         || (mAppearance == FLASHRED)
         || (mAppearance == FLASHLUNAR)) {
     // If we are actively flashing right now, then we ignore external changes, since
     // those might be coming from ourselves and will be overwritten shortly.
     return;
 }
 int red = mRed->getBean()->getKnownState();
 int green = mGreen->getBean()->getKnownState();
 if (mRedCommanded == red && mGreenCommanded == green) return;
 // The turnouts' known state has diverged from what we set. We attempt to decode the
 // actual state to an appearance. This is a lossy operation, but the user has done
 // something very explicitly to make this happen, like manually clicking the turnout throw
 // button, or setting up an external signaling logic system.
 if (red == Turnout::CLOSED && green == Turnout::CLOSED) {
     setAppearance(DARK);
 } else if (red == Turnout::THROWN && green == Turnout::CLOSED) {
     setAppearance(RED);
 } else if (red == Turnout::THROWN && green == Turnout::THROWN) {
     setAppearance(YELLOW);
 } else if (red == Turnout::CLOSED && green == Turnout::THROWN) {
     setAppearance(GREEN);
 }
}

