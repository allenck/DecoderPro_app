#include "mergsd2signalhead.h"
#include "loggerfactory.h"

/**
 * Implement SignalHead for the MERG Signal Driver 2.
 * <p>
 * The Signal Driver, runs off of the output of a steady State Accessory
 * decoder. Can be configured to run 2, 3 or 4 Aspect signals. With 2 or 3
 * aspect signals it may have a feather included.
 * <p>
 * The driver is designed to be used with UK based signals.
 * <p>
 * The class assigns turnout positions for RED, YELLOW, GREEN and Double Yellow
 * aspects. THE SD2 does not support flashing double yellow aspects on turnouts, so
 * an alternative method is required to do this, as per the MERG SD2
 * documentation.
 * <p>
 * As there is no Double Yellow asigned within JMRI, we use the Lunar instead.
 * <p>
 * For more info on the signals, see
 * <a href="http://www.merg.info">http://www.merg.info</a>.
 *
 * @author Kevin Dickerson Copyright (C) 2009
 */
///*public*/  class MergSD2SignalHead extends DefaultSignalHead {

/*public*/  MergSD2SignalHead::MergSD2SignalHead(QString sys, QString user, int aspect,
                                                 NamedBeanHandle<Turnout*>* t1,
                                                 NamedBeanHandle<Turnout*>* t2,
                                                 NamedBeanHandle<Turnout*>* t3,
                                                 bool feather, bool home, QObject* parent)
 : DefaultSignalHead(sys, user, parent){
    //super(sys, user);
    mAspects = aspect;
    mInput1 = t1;
    if (t2 != nullptr) {
        mInput2 = t2;
    }
    if (t3 != nullptr) {
        mInput3 = t3;
    }
    mFeather = feather;
    mHome = home;
    if (mHome) {
        setAppearance(RED);
    } else {
        setAppearance(YELLOW);
    }
}

/*public*/  MergSD2SignalHead::MergSD2SignalHead(QString sys, int aspect, NamedBeanHandle<Turnout*>* t1, NamedBeanHandle<Turnout*>* t2, NamedBeanHandle<Turnout*>* t3, bool feather, bool home, QObject* parent)
 : DefaultSignalHead(sys)
{
    //super(sys);
    mAspects = aspect;
    mInput1 = t1;
    if (t2 != nullptr) {
        mInput2 = t2;
    }
    if (t3 != nullptr) {
        mInput3 = t3;
    }
    mFeather = feather;
    mHome = home;
    if (mHome) {
        setAppearance(RED);
    } else {
        setAppearance(YELLOW);
    }
}

/**
 * Set the Signal Head Appearance.
 * Modified from DefaultSignalHead. Removed option for software flashing.
 *
 * @param newAppearance integer representing a valid Appearance for this head
 */
//@Override
/*public*/  void MergSD2SignalHead::setAppearance(int newAppearance) {
    int oldAppearance = mAppearance;
    mAppearance = newAppearance;
    bool valid = false;
    switch (mAspects) {
        case 2:
            if (mHome) {
                if ((newAppearance == RED) || (newAppearance == GREEN)) {
                    valid = true;
                }
            } else {
                if ((newAppearance == GREEN) || (newAppearance == YELLOW)) {
                    valid = true;
                }
            }
            break;
        case 3:
            if ((newAppearance == RED) || (newAppearance == YELLOW) || (newAppearance == GREEN)) {
                valid = true;
            }
            break;
        case 4:
            if ((newAppearance == RED) || (newAppearance == YELLOW) || (newAppearance == GREEN) || (newAppearance == LUNAR)) {
                valid = true;
            }
            break;
        default:
            valid = false;
            break;
    }
    if ((oldAppearance != newAppearance) && (valid)) {
        updateOutput();

        // notify listeners, if any
        firePropertyChange("Appearance", oldAppearance, newAppearance);
    }

}

//@Override
/*public*/  void MergSD2SignalHead::setLit(bool newLit) {
    bool oldLit = mLit;
    mLit = newLit;
    if (oldLit != newLit) {
        updateOutput();
        // notify listeners, if any
        firePropertyChange("Lit", oldLit, newLit);
    }
}

//@Override
/*protected*/ void MergSD2SignalHead::updateOutput() {
    // assumes that writing a turnout to an existing state is cheap!
    switch (mAppearance) {
        case RED:
            mInput1->getBean()->setCommandedState(Turnout::CLOSED);
            //if(mInput2!=null) mInput2.setCommandedState(Turnout::CLOSED);
            //if(mInput3!=null) mInput3.setCommandedState(Turnout::CLOSED);
            break;
        case YELLOW:
            if (mHome) {
                mInput1->getBean()->setCommandedState(Turnout::THROWN);
                if (mInput2 != nullptr) {
                    mInput2->getBean()->setCommandedState(Turnout::CLOSED);
                }
            } else {
                mInput1->getBean()->setCommandedState(Turnout::CLOSED);
            }
            break;
        case LUNAR:
            mInput1->getBean()->setCommandedState(Turnout::THROWN);
            mInput2->getBean()->setCommandedState(Turnout::THROWN);
            mInput3->getBean()->setCommandedState(Turnout::CLOSED);
            //mInput1.setCommandedState(
            //mFlashYellow.setCommandedState(mFlashYellowState);
            break;
        case GREEN:
            mInput1->getBean()->setCommandedState(Turnout::THROWN);
            if (mInput2 != nullptr) {
                mInput2->getBean()->setCommandedState(Turnout::THROWN);
            }
            if (mInput3 != nullptr) {
                mInput3->getBean()->setCommandedState(Turnout::THROWN);
            }
            break;
        default:
            mInput1->getBean()->setCommandedState(Turnout::CLOSED);

            log->warn(tr("Unexpected new appearance: %1").arg(mAppearance));
        // go dark
        }
    //}
}

/**
 * Remove references to and from this object, so that it can eventually be
 * garbage-collected.
 */
//@Override
/*public*/  void MergSD2SignalHead::dispose() {
    mInput1 = nullptr;
    mInput2 = nullptr;
    mInput3 = nullptr;
    DefaultSignalHead::dispose();
}



/*public*/  NamedBeanHandle<Turnout*>* MergSD2SignalHead::getInput1() {
    return mInput1;
}

/*public*/  NamedBeanHandle<Turnout*>* MergSD2SignalHead::getInput2() {
    return mInput2;
}

/*public*/  NamedBeanHandle<Turnout*>* MergSD2SignalHead::getInput3() {
    return mInput3;
}

/**
 * Return the number of aspects for this signal.
 *
 * @return the number of aspects
 */
/*public*/  int MergSD2SignalHead::getAspects() {
    return mAspects;
}

/*public*/  bool MergSD2SignalHead::getFeather() {
    return mFeather;
}

/**
 * Return whether this signal is a home or a distant/Repeater signal.
 *
 * @return true if signal is set up as Home signal (default); false if Distant
 */
/*public*/  bool MergSD2SignalHead::getHome() {
    return mHome;
}

/**
 * Set the first turnout used on the driver. Relates to the section directly
 * in front of the Signal {@literal (2, 3 & 4 aspect Signals)}.
 *
 * @param t turnout (named bean handel) to use as input 1
 */
/*public*/  void MergSD2SignalHead::setInput1(NamedBeanHandle<Turnout*>* t) {
    mInput1 = t;
}

/**
 * Set the second turnout used on the driver. Relates to the section in
 * front of the next Signal (3 and 4 aspect Signal).
 *
 * @param t turnout (named bean handel) to use as input 2
 */
/*public*/  void MergSD2SignalHead::setInput2(NamedBeanHandle<Turnout*>* t) {
    mInput2 = t;
}

/**
 * Set the third turnout used on the driver. Relates to the section directly
 * in front the third Signal (4 aspect Signal).
 *
 * @param t turnout (named bean handel) to use as input 3
 */
/*public*/  void MergSD2SignalHead::setInput3(NamedBeanHandle<Turnout*>* t) {
    mInput3 = t;
}

/**
 * Set the number of aspects on the signal.
 *
 * @param i the number of aspects on mast; valid values: 2, 3, 4
 */
/*public*/  void MergSD2SignalHead::setAspects(int i) {
    mAspects = i;
}

/*public*/  void MergSD2SignalHead::setFeather(bool boo) {
    mFeather = boo;
}

/**
 * Set whether the signal is a home or distance/repeater signal.
 *
 * @param boo true if configuring as a Home signal, false for a Distant
 */
/*public*/  void MergSD2SignalHead::setHome(bool boo) {
    mHome = boo;
}

/*final*/ /*static*/ /*private*/ QVector<int> MergSD2SignalHead::validStates2AspectHome = QVector<int> {
    RED,
    GREEN
};
/*final*/ /*static*/ /*private*/ QVector<QString> MergSD2SignalHead::validStateKeys2AspectHome = QVector<QString>{
    "SignalHeadStateRed",
    "SignalHeadStateGreen"
};

/*final*/ /*static*/ /*private*/ QVector<int> MergSD2SignalHead::validStates2AspectDistant = QVector<int>{
    YELLOW,
    GREEN
};
/*final*/ /*static*/ /*private*/ QVector<QString> MergSD2SignalHead::validStateKeys2AspectDistant = QVector<QString>{
    "SignalHeadStateYellow",
    "SignalHeadStateGreen"
};

/*final*/ /*static*/ /*private*/ QVector<int> MergSD2SignalHead::validStates3Aspect = QVector<int>{
    RED,
    YELLOW,
    GREEN
};
/*final*/ /*static*/ /*private*/ QVector<QString> MergSD2SignalHead::validStateKeys3Aspect = QVector<QString>{
    "SignalHeadStateRed",
    "SignalHeadStateYellow",
    "SignalHeadStateGreen"
};

/*final*/ /*static*/ /*private*/ QVector<int> MergSD2SignalHead::validStates4Aspect = QVector<int>{
    RED,
    YELLOW,
    LUNAR,
    GREEN
};
/*final*/ /*static*/ /*private*/ QVector<QString> MergSD2SignalHead::validStateKeys4Aspect = QVector<QString>{
    "SignalHeadStateRed",
    "SignalHeadStateYellow",
    "SignalHeadStateLunar",
    "SignalHeadStateGreen"
};

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  QVector<int> MergSD2SignalHead::getValidStates() {
    if (!mHome) {
        return QVector<int>(validStates2AspectDistant/*, validStates2AspectDistant.length*/);
    } else {
        switch (mAspects) {
            case 2:
                return QVector<int>(validStates2AspectHome/*, validStates2AspectHome.length*/);
            case 3:
                return QVector<int>(validStates3Aspect/*, validStates3Aspect.length*/);
            case 4:
                return QVector<int>(validStates4Aspect/*, validStates4Aspect.length*/);
            default:
                log->warn(tr("Unexpected number of aspects: %1").arg(mAspects));
                return QVector<int>(validStates3Aspect/*, validStates3Aspect.length*/);
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  QVector<QString> MergSD2SignalHead::getValidStateKeys() {
    if (!mHome) {
        return QVector<QString>(validStateKeys2AspectDistant/*, validStateKeys2AspectDistant.length*/);
    } else {
        switch (mAspects) {
            case 2:
                return QVector<QString>(validStateKeys2AspectHome/*, validStateKeys2AspectHome.length*/);
            case 3:
                return QVector<QString>(validStateKeys3Aspect/*, validStateKeys3Aspect.length*/);
            case 4:
                return QVector<QString>(validStateKeys4Aspect/*, validStateKeys3Aspect.length*/);
            default:
                log->warn(tr("Unexpected number of aspects: %1").arg(mAspects));
                return QVector<QString>(validStateKeys3Aspect/*, validStateKeys3Aspect.length*/);
        }
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/  QVector<QString> MergSD2SignalHead::getValidStateNames() {
    QVector<QString> stateNames = QVector<QString>(getValidStateKeys().length());
    int i = 0;
    for (QString stateKey : getValidStateKeys()) {
        //stateNames[i++] = Bundle.getMessage(stateKey);
     stateNames[i++] = stateMap.value(stateKey);
    }
    return stateNames;
}

//@Override
bool MergSD2SignalHead::isTurnoutUsed(Turnout* t) {
    if (getInput1() != nullptr && t->equals(getInput1()->getBean())) {
        return true;
    }
    if (getInput2() != nullptr && t->equals(getInput2()->getBean())) {
        return true;
    }
    if (getInput3() != nullptr && t->equals(getInput3()->getBean())) {
        return true;
    }
    return false;
}

/*private*/ /*final*/ /*static*/ Logger* MergSD2SignalHead::log = LoggerFactory::getLogger("MergSD2SignalHead");


