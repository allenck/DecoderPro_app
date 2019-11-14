#include "doubleturnoutsignalhead.h"
#include "turnout.h"
#include "signalhead.h"
#include "timer.h"
#include "loggerfactory.h"
#include "instancemanager.h"

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

/*public*/ DoubleTurnoutSignalHead::DoubleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent)
 : DefaultSignalHead(sys, user, parent){
   // super(sys, user);
 turnoutChangeListener = new TurnoutPropertyChangeListener(this);
 setRed(red);
 setGreen(green);
}

/*public*/ DoubleTurnoutSignalHead::DoubleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* red, QObject *parent)
 : DefaultSignalHead(sys, parent) {
    //super(sys);
 turnoutChangeListener = new TurnoutPropertyChangeListener(this);
 setRed(red);
 setGreen(green);
}

//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
/*protected*/ void DoubleTurnoutSignalHead::updateOutput()
{
 // assumes that writing a turnout to an existing state is cheap!
 if (mLit == false) {
     commandState(Turnout::CLOSED, Turnout::CLOSED);
     return;
 } else if (!mFlashOn
         && ((mAppearance == FLASHGREEN)
         || (mAppearance == FLASHYELLOW)
         || (mAppearance == FLASHRED))) {
     // flash says to make output dark
     commandState(Turnout::CLOSED, Turnout::CLOSED);
     return;

 } else {
     switch (mAppearance) {
         case RED:
         case FLASHRED:
             commandState(Turnout::THROWN, Turnout::CLOSED);
             break;
         case YELLOW:
         case FLASHYELLOW:
             commandState(Turnout::THROWN, Turnout::THROWN);
             break;
         case GREEN:
         case FLASHGREEN:
             commandState(Turnout::CLOSED, Turnout::THROWN);
             break;
         default:
             log->warn("Unexpected new appearance: " + QString::number(mAppearance));
         // go dark by falling through
         case DARK:
             commandState(Turnout::CLOSED, Turnout::CLOSED);
             break;
     }
 }

}
/**
 * Sets the output turnouts' commanded state.
 *
 * @param red   state to set the mRed turnout
 * @param green state to set the mGreen turnout.
 */
void DoubleTurnoutSignalHead::commandState(int red, int green) {
    mRedCommanded = red;
    mRed->getBean()->setCommandedState(red);
    mGreenCommanded = green;
    mGreen->getBean()->setCommandedState(green);
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void DoubleTurnoutSignalHead::dispose() {
 if (mRed != nullptr) {
     mRed->getBean()->removePropertyChangeListener(turnoutChangeListener);
 }
 if (mGreen != nullptr) {
     mGreen->getBean()->removePropertyChangeListener(turnoutChangeListener);
 }
 mRed = nullptr;
 mGreen = nullptr;
 InstanceManager::turnoutManagerInstance()->removeVetoableChangeListener((VetoableChangeListener*)this);
 DefaultSignalHead::dispose();
}

/*public*/ NamedBeanHandle<Turnout*>* DoubleTurnoutSignalHead::getRed() {return mRed;}
/*public*/ NamedBeanHandle<Turnout*>* DoubleTurnoutSignalHead::getGreen() {return mGreen;}

/*public*/ void DoubleTurnoutSignalHead::setRed(NamedBeanHandle<Turnout*>* t)
{
 if(mRed != nullptr)
  mRed->getBean()->removePropertyChangeListener(turnoutChangeListener);
 mRed=t;
 if(mRed != nullptr)
  mRed->getBean()->addPropertyChangeListener(turnoutChangeListener);
}

/*public*/ void DoubleTurnoutSignalHead::setGreen(NamedBeanHandle<Turnout*>* t)
{
 if(mGreen != nullptr)
  mGreen->getBean()->removePropertyChangeListener(turnoutChangeListener);

 mGreen=t;
 if(mGreen != nullptr)
  mGreen->getBean()->addPropertyChangeListener(turnoutChangeListener);

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
/*public*/ void TurnoutPropertyChangeListener::propertyChange(PropertyChangeEvent* propertyChangeEvent) {
    if (propertyChangeEvent->getPropertyName()==("KnownState")) {
        if (propertyChangeEvent->getSource() == (dtsh->mRed->getBean()) && propertyChangeEvent->getNewValue() == (dtsh->mRedCommanded)) {
            return; // ignore change that we commanded
        }
        if (propertyChangeEvent->getSource() == (dtsh->mGreen->getBean()) && propertyChangeEvent->getNewValue() == (dtsh->mGreenCommanded)) {
            return; // ignore change that we commanded
        }
        if (dtsh->readUpdateTimer == nullptr) {
//            readUpdateTimer = new Timer(200, (ActionEvent actionEvent) ->
//                    readOutput());
         dtsh->readUpdateTimer = new Timer(200, new TimerActionListener(dtsh));
         dtsh->readUpdateTimer->setRepeats(false);
         dtsh->readUpdateTimer->start();
        } else {
         dtsh->readUpdateTimer->reStart();
        }
    }
}
//};

void TimerActionListener::actionPerformed()
{
 dtsh->readOutput();
}


/**
* Checks if the turnouts' output state matches the commanded output state; if not, then
* changes the appearance to match the output's current state.
*/
void DoubleTurnoutSignalHead::readOutput() {
 if ((mAppearance == DoubleTurnoutSignalHead::FLASHGREEN)
         || (mAppearance == DoubleTurnoutSignalHead::FLASHYELLOW)
         || (mAppearance == DoubleTurnoutSignalHead::FLASHRED)
         || (mAppearance == DoubleTurnoutSignalHead::FLASHLUNAR)) {
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
     setAppearance(DoubleTurnoutSignalHead::DARK);
 } else if (red == Turnout::THROWN && green == Turnout::CLOSED) {
     setAppearance(DoubleTurnoutSignalHead::RED);
 } else if (red == Turnout::THROWN && green == Turnout::THROWN) {
     setAppearance(DoubleTurnoutSignalHead::YELLOW);
 } else if (red == Turnout::CLOSED && green == Turnout::THROWN) {
     setAppearance(DoubleTurnoutSignalHead::GREEN);
 }
}

/*static*/ Logger* DoubleTurnoutSignalHead::log = LoggerFactory::getLogger("DoubleTurnoutSignalHead");
