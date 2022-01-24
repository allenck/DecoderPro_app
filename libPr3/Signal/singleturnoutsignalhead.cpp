#include "singleturnoutsignalhead.h"
#include "turnout.h"
#include "abstractturnout.h"

//SingleTurnoutSignalHead::SingleTurnoutSignalHead(QObject *parent) :
//    DefaultSignalHead(parent)
//{
//}
/**
 * Drive a single signal head via one "Turnout" objects.
 * <P>
 * After much confusion, the user-level terminology
 * was changed to call these "Single Output"; the class
 * name remains the same to reduce recoding.
 * <P>
 * One Turnout object is provided during construction,
 * and drives the aspect to be either ON or OFF.
 * Normally, "THROWN" is on, and "CLOSED" is off.
 * The facility to set the aspect via any of the four
 * aspect colors is provided, however they all do the same.
 *
 * <P>
 * This class doesn't currently listen to the Turnout's to see if they've
 * been changed via some other mechanism.
 *
 * Based Upon DoubleTurnoutSignalHead by Bob Jacobsen
 *
 * @author	Kevin Dickerson Copyright (C) 2010
 * @version	$Revision: 22323 $
 */
///*public*/ class SingleTurnoutSignalHead extends DefaultSignalHead {

/**
 * @param on Appearance constant from {@link jmri.SignalHead} for the output on (Turnout thrown) appearance
 * @param off Appearance constant from {@link jmri.SignalHead} for the signal off (Turnout closed) appearance
 */
/*public*/ SingleTurnoutSignalHead::SingleTurnoutSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* lit, int on, int off, QObject *parent) :    DefaultSignalHead(sys, user, parent)
{
    //super(sys, user);
    log = new Logger("SingleTurnoutSignalHead");
    mOutput = lit;
    mOnAppearance = on;
    mOffAppearance = off;
    setAppearance(off);
}

/**
 * @param on Appearance constant from {@link jmri.SignalHead} for the output on (Turnout thrown) appearance
 * @param off Appearance constant from {@link jmri.SignalHead} for the signal off (Turnout closed) appearance
 */
/*public*/ SingleTurnoutSignalHead::SingleTurnoutSignalHead(QString sys, NamedBeanHandle<Turnout*>* lit, int on, int off, QObject *parent) :
           DefaultSignalHead(sys, "", parent)
{
    //super(sys);
    log = new Logger("SingleTurnoutSignalHead");
    mOutput = lit;
    mOnAppearance = on;
    mOffAppearance = off;
    setAppearance(off);
}

//@Override
/*protected*/ void SingleTurnoutSignalHead::updateOutput()
{
 int oldAppearance = mAppearance;
 // assumes that writing a turnout to an existing state is cheap!
 if (mLit == false)
 {
  ((AbstractTurnout*)mOutput->getBean())->setCommandedState(Turnout::CLOSED);
  return;
 }
 else if ( !mFlashOn && (mAppearance == mOnAppearance*2) )
 {
  ((AbstractTurnout*)mOutput->getBean())->setCommandedState(Turnout::CLOSED);
  return;
 }
 else if ( !mFlashOn && (mAppearance == mOffAppearance*2)  )
 {
  ((AbstractTurnout*)mOutput->getBean())->setCommandedState(Turnout::THROWN);
  return;
 }
 else
 {
  if ((mAppearance==mOffAppearance) || (mAppearance==(mOffAppearance*2)))
  {
   ((AbstractTurnout*)mOutput->getBean())->setCommandedState(Turnout::CLOSED);
  }
  else if ((mAppearance==mOnAppearance) || (mAppearance==(mOnAppearance*2)))
  {
   ((AbstractTurnout*)mOutput->getBean())->setCommandedState(Turnout::THROWN);
  }
  else
  {
   log->warn("Unexpected new appearance: "+QString::number(mAppearance));
  }
 }
 firePropertyChange("Appearance", QVariant(oldAppearance), QVariant(mAppearance));
}


/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void SingleTurnoutSignalHead::dispose() {
    mOutput = NULL;
    DefaultSignalHead::dispose();
}


/*public*/ int SingleTurnoutSignalHead::getOnAppearance() {return mOnAppearance;}
/*public*/ int SingleTurnoutSignalHead::getOffAppearance() {return mOffAppearance;}
/*public*/ void SingleTurnoutSignalHead::setOnAppearance(int on) {
    int old = on;
    mOnAppearance = on;
    firePropertyChange("ValidStatesChanged", old, on);
}
/*public*/ void SingleTurnoutSignalHead::setOffAppearance(int off) {
    int old = off;
    mOffAppearance = off;
    firePropertyChange("ValidStatesChanged", old, off);
}

/*public*/ NamedBeanHandle<Turnout*>* SingleTurnoutSignalHead::getOutput() {return mOutput;}

/*public*/ void SingleTurnoutSignalHead::setOutput(NamedBeanHandle<Turnout*>* t) {mOutput=t;}

/*public*/ QVector<int> SingleTurnoutSignalHead::getValidStates() {
    QVector<int> validStates;
    if(mOnAppearance == mOffAppearance){
        validStates = QVector<int>(2);
        validStates.replace(0, mOnAppearance);
        validStates.replace(1,mOffAppearance);
        return validStates;
    }
    else if (mOnAppearance == SignalHead::DARK || mOffAppearance == SignalHead::DARK){
        validStates = QVector<int>(3);
    }
    else {
        validStates =  QVector<int>(2);
    }
    int x = 0;
    validStates.replace(x, mOnAppearance);
    x++;
    if (mOffAppearance == SignalHead::DARK){
        validStates.replace(x, (mOnAppearance * 2));  // makes flashing
        x++;
    }
    validStates.replace(x, mOffAppearance);
    x++;
    if (mOnAppearance == SignalHead::DARK){
        validStates.replace(x, (mOffAppearance * 2));  // makes flashing
    }
    return validStates;
}

/*public*/ QVector<QString> SingleTurnoutSignalHead::getValidStateNames() {
    QVector<QString> validStateName;
    if(mOnAppearance == mOffAppearance){
        validStateName = QVector<QString>(2);
        validStateName.replace(0, getSignalColorKey(mOnAppearance));
        validStateName.replace(1, getSignalColorKey(mOffAppearance));
        return validStateName;
    }
    if (mOnAppearance == SignalHead::DARK || mOffAppearance == SignalHead::DARK){
        validStateName = QVector<QString>(3);
    }
    else {
        validStateName =QVector<QString>(2);
    }
    int x = 0;
    validStateName[x] = getSignalColorKey(mOnAppearance);
    x++;
    if (mOffAppearance == SignalHead::DARK){
        validStateName.replace(x, getSignalColorKey((mOnAppearance * 2)));  // makes flashing
        x++;
    }
    validStateName.replace(x, getSignalColorKey(mOffAppearance));
    x++;
    if (mOnAppearance == SignalHead::DARK){
        validStateName.replace(x,getSignalColorKey((mOffAppearance * 2)));  // makes flashing
    }
    return validStateName;
}

//@SuppressWarnings("fallthrough")
//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="SF_SWITCH_FALLTHROUGH")
/*private*/ QString SingleTurnoutSignalHead::getSignalColorKey(int mAppearance){
    switch(mAppearance){
    case  SignalHead::RED:
                return  tr("Red");
    case   SignalHead::FLASHRED:
                return tr("Flashing Red");
    case   SignalHead::YELLOW:
                return tr("Yellow");
    case   SignalHead::FLASHYELLOW:
                return tr("Flashing Yellow");
    case   SignalHead::GREEN:
                return tr("Green");
    case   SignalHead::FLASHGREEN:
                return tr("Flashing Green");
    case   SignalHead::LUNAR:
                return tr("Lunar");
    case   SignalHead::FLASHLUNAR:
                return tr("Flashing Lunar");
    default:
           log->warn("Unexpected appearance: "+QString::number(mAppearance));
           // go dark by falling through
    case   SignalHead::DARK:
           return  tr("Dark");
 }
}

/*private*/ QString SingleTurnoutSignalHead::getSignalColorName(int mAppearance) {
        return getSignalColorKey(mAppearance);
    }
