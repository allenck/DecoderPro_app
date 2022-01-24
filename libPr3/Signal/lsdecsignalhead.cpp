#include "lsdecsignalhead.h"
#include  "loggerfactory.h"
/*
 * Implement SignalHead for Littfinski Daten Technik (LDT) signals.
 * <p>
 * These decoders can display up to 8 aspects. One position of a turnout is
 * associated with one signal aspect. The class assigns turnout positions to all
 * 7 JMRI signal aspects.
 * <p>
 * For more info on the signals, see
 * <A HREF="http://www.ldt-infocenter.com">http://www.ldt-infocenter.com</a>.
 *
 * @author Petr Koud'a Copyright (C) 2007
 */
// /*public*/  class LsDecSignalHead extends DefaultSignalHead {

/*public*/  LsDecSignalHead::LsDecSignalHead(QString sys, QString user,
                                             NamedBeanHandle<Turnout*>* t1, int s1,
                                             NamedBeanHandle<Turnout*>* t2, int s2,
                                             NamedBeanHandle<Turnout*>* t3, int s3,
                                             NamedBeanHandle<Turnout*>* t4, int s4,
                                             NamedBeanHandle<Turnout*>* t5, int s5,
                                             NamedBeanHandle<Turnout*>* t6, int s6,
                                             NamedBeanHandle<Turnout*>* t7, int s7, QObject* parent)
 : DefaultSignalHead(sys, user, parent)
{
 //super(sys, user);
    mGreen = t1;
    mYellow = t2;
    mRed = t3;
    mFlashGreen = t4;
    mFlashYellow = t5;
    mFlashRed = t6;
    mDark = t7;
    mGreenState = s1;
    mYellowState = s2;
    mRedState = s3;
    mFlashGreenState = s4;
    mFlashYellowState = s5;
    mFlashRedState = s6;
    mDarkState = s7;
}

/*public*/  LsDecSignalHead::LsDecSignalHead(QString sys,
                            NamedBeanHandle<Turnout*>* t1, int s1,
                            NamedBeanHandle<Turnout*>* t2, int s2,
                            NamedBeanHandle<Turnout*>* t3, int s3,
                            NamedBeanHandle<Turnout*>* t4, int s4,
                            NamedBeanHandle<Turnout*>* t5, int s5,
                            NamedBeanHandle<Turnout*>* t6, int s6,
                            NamedBeanHandle<Turnout*>* t7, int s7 , QObject* parent)
 : DefaultSignalHead(sys, parent)
{
    //super(sys);
    mGreen = t1;
    mYellow = t2;
    mRed = t3;
    mFlashGreen = t4;
    mFlashYellow = t5;
    mFlashRed = t6;
    mDark = t7;
    mGreenState = s1;
    mYellowState = s2;
    mRedState = s3;
    mFlashGreenState = s4;
    mFlashYellowState = s5;
    mFlashRedState = s6;
    mDarkState = s7;
}

/*
 * Modified from DefaultSignalHead
 * removed software flashing!!!
 */
//@Override
/*public*/  void LsDecSignalHead::setAppearance(int newAppearance) {
    int oldAppearance = mAppearance;
    mAppearance = newAppearance;

    if (oldAppearance != newAppearance) {
        updateOutput();

        // notify listeners, if any
        firePropertyChange("Appearance", (oldAppearance), (newAppearance));
    }
}

//@Override
/*public*/  void LsDecSignalHead::setLit(bool newLit) {
    bool oldLit = mLit;
    mLit = newLit;
    if (oldLit != newLit) {
        updateOutput();
        // notify listeners, if any
        firePropertyChange("Lit", (oldLit), (newLit));
    }
}

//@SuppressWarnings("fallthrough")
//@SuppressFBWarnings(value = "SF_SWITCH_FALLTHROUGH")
//@Override
/*protected*/ void LsDecSignalHead::updateOutput() {
    // assumes that writing a turnout to an existing state is cheap!
    if (mLit == false) {
        mDark->getBean()->setCommandedState(mDarkState);
        return;
    } else {
        switch (mAppearance) {
            case RED:
                mRed->getBean()->setCommandedState(mRedState);
                break;
            case FLASHRED:
                mFlashRed->getBean()->setCommandedState(mFlashRedState);
                break;
            case YELLOW:
                mYellow->getBean()->setCommandedState(mYellowState);
                break;
            case FLASHYELLOW:
                mFlashYellow->getBean()->setCommandedState(mFlashYellowState);
                break;
            case GREEN:
                mGreen->getBean()->setCommandedState(mGreenState);
                break;
            case FLASHGREEN:
                mFlashGreen->getBean()->setCommandedState(mFlashGreenState);
                break;
            default:
                log->warn(tr("Unexpected new appearance: %1").arg(mAppearance));
            // go dark by falling through
            case DARK:
                mDark->getBean()->setCommandedState(mDarkState);
                break;
        }
    }
}

/*
 * Remove references to and from this object, so that it can eventually be
 * garbage-collected.
 */
//@Override
/*public*/  void LsDecSignalHead::dispose() {
    mRed = nullptr;
    mYellow = nullptr;
    mGreen = nullptr;
    mFlashRed = nullptr;
    mFlashYellow = nullptr;
    mFlashGreen = nullptr;
    mDark = nullptr;
    DefaultSignalHead::dispose();
}



/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getRed() {
    return mRed;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getYellow() {
    return mYellow;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getGreen() {
    return mGreen;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getFlashRed() {
    return mFlashRed;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getFlashYellow() {
    return mFlashYellow;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getFlashGreen() {
    return mFlashGreen;
}

/*public*/  NamedBeanHandle<Turnout*>* LsDecSignalHead::getDark() {
    return mDark;
}

/*public*/  int LsDecSignalHead::getRedState() {
    return mRedState;
}

/*public*/  int LsDecSignalHead::getYellowState() {
    return mYellowState;
}

/*public*/  int LsDecSignalHead::getGreenState() {
    return mGreenState;
}

/*public*/  int LsDecSignalHead::getFlashRedState() {
    return mFlashRedState;
}

/*public*/  int LsDecSignalHead::getFlashYellowState() {
    return mFlashYellowState;
}

/*public*/  int LsDecSignalHead::getFlashGreenState() {
    return mFlashGreenState;
}

/*public*/  int LsDecSignalHead::getDarkState() {
    return mDarkState;
}

/*public*/  void LsDecSignalHead::setRed(NamedBeanHandle<Turnout*>* t) {
    mRed = t;
}

/*public*/  void LsDecSignalHead::setYellow(NamedBeanHandle<Turnout*>* t) {
    mYellow = t;
}

/*public*/  void LsDecSignalHead::setGreen(NamedBeanHandle<Turnout*>* t) {
    mGreen = t;
}

/*public*/  void LsDecSignalHead::setFlashRed(NamedBeanHandle<Turnout*>* t) {
    mFlashRed = t;
}

/*public*/  void LsDecSignalHead::setFlashYellow(NamedBeanHandle<Turnout*>* t) {
    mFlashYellow = t;
}

/*public*/  void LsDecSignalHead::setFlashGreen(NamedBeanHandle<Turnout*>* t) {
    mFlashGreen = t;
}

/*public*/  void LsDecSignalHead::setDark(NamedBeanHandle<Turnout*>* t) {
    mDark = t;
}

/*public*/  void LsDecSignalHead::setRedState(int i) {
    mRedState = i;
}

/*public*/  void LsDecSignalHead::setYellowState(int i) {
    mYellowState = i;
}

/*public*/  void LsDecSignalHead::setGreenState(int i) {
    mGreenState = i;
}

/*public*/  void LsDecSignalHead::setFlashRedState(int i) {
    mFlashRedState = i;
}

/*public*/  void LsDecSignalHead::setFlashYellowState(int i) {
    mFlashYellowState = i;
}

/*public*/  void LsDecSignalHead::setFlashGreenState(int i) {
    mFlashGreenState = i;
}

/*public*/  void LsDecSignalHead::setDarkState(int i) {
    mDarkState = i;
}

//@Override
bool LsDecSignalHead::isTurnoutUsed(Turnout* t) {
    if (getRed() != nullptr && t->equals(getRed()->getBean())) {
        return true;
    }
    if (getYellow() != nullptr && t->equals(getYellow()->getBean())) {
        return true;
    }
    if (getGreen() != nullptr && t->equals(getGreen()->getBean())) {
        return true;
    }
    if (getFlashRed() != nullptr && t->equals(getFlashRed()->getBean())) {
        return true;
    }
    if (getFlashYellow() != nullptr && t->equals(getFlashYellow()->getBean())) {
        return true;
    }
    if (getFlashGreen() != nullptr && t->equals(getFlashGreen()->getBean())) {
        return true;
    }
    if (getDark() != nullptr && t->equals(getDark()->getBean())) {
        return true;
    }
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* LsDecSignalHead::log = LoggerFactory::getLogger("LsDecSignalHead");

