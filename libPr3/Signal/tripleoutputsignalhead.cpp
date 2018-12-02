#include "tripleoutputsignalhead.h"
#include "turnout.h"
#include "loggerfactory.h"

/**
 * Drive a single searchlight signal head via three "Turnout" objects.
 * <P>
 * "Triple Output RGB" to differentiate from the existing RYG triple output
 * head; The class name fits in with the quad output name which is the
 * equivalent discrete lamp head.
 * <P>
 * The three Turnout objects are provided during construction, and each drives a
 * specific color (RED, GREEN and BLUE). Normally, "THROWN" is on, and "CLOSED"
 * is off.
 * <P>
 * Red = Red Green = Green Yellow = Red and Green Lunar = Red, Green and Blue
 * <P>
 * This class doesn't currently listen to the Turnout's to see if they've been
 * changed via some other mechanism.
 *
 * @author Suzie Tall based on Bob Jacobsen's work
 * @author Bob Jacobsen Copyright (C) 2003, 2008
 */
///*public*/ class TripleOutputSignalHead extends DoubleTurnoutSignalHead {

/*public*/ TripleOutputSignalHead::TripleOutputSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout *> *blue, NamedBeanHandle<Turnout *> *red, QObject* parent) : DoubleTurnoutSignalHead(sys, user, green, red, parent){
    //super(sys, user, green, red);
    mBlue = blue;
}

/*public*/ TripleOutputSignalHead::TripleOutputSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* blue, NamedBeanHandle<Turnout*>* red, QObject* parent) : DoubleTurnoutSignalHead(sys, green, red, parent)
{
    //super(sys, green, red);
    mBlue = blue;
}

//@SuppressWarnings("fallthrough")
//@SuppressFBWarnings(value = "SF_SWITCH_FALLTHROUGH")
//@Override
/*protected*/ void TripleOutputSignalHead::updateOutput() {
    // assumes that writing a turnout to an existing state is cheap!
    if (mLit == false) {
        mRed->getBean()->setCommandedState(Turnout::CLOSED);
        mBlue->getBean()->setCommandedState(Turnout::CLOSED);
        mGreen->getBean()->setCommandedState(Turnout::CLOSED);
        return;
    } else if (!mFlashOn
            && ((mAppearance == FLASHGREEN)
            || (mAppearance == FLASHYELLOW)
            || (mAppearance == FLASHLUNAR)
            || (mAppearance == FLASHRED))) {
        // flash says to make output dark
        mRed->getBean()->setCommandedState(Turnout::CLOSED);
        mBlue->getBean()->setCommandedState(Turnout::CLOSED);
        mGreen->getBean()->setCommandedState(Turnout::CLOSED);
        return;

    } else {
        switch (mAppearance) {
            case RED:
            case FLASHRED:
                mRed->getBean()->setCommandedState(Turnout::THROWN);
                mBlue->getBean()->setCommandedState(Turnout::CLOSED);
                mGreen->getBean()->setCommandedState(Turnout::CLOSED);
                break;
            case YELLOW:
            case FLASHYELLOW:
                mRed->getBean()->setCommandedState(Turnout::THROWN);
                mBlue->getBean()->setCommandedState(Turnout::CLOSED);
                mGreen->getBean()->setCommandedState(Turnout::THROWN);
                break;
            case GREEN:
            case FLASHGREEN:
                mRed->getBean()->setCommandedState(Turnout::CLOSED);
                mBlue->getBean()->setCommandedState(Turnout::CLOSED);
                mGreen->getBean()->setCommandedState(Turnout::THROWN);
                break;
            case LUNAR:
            case FLASHLUNAR:
                mRed->getBean()->setCommandedState(Turnout::THROWN);
                mBlue->getBean()->setCommandedState(Turnout::THROWN);
                mGreen->getBean()->setCommandedState(Turnout::THROWN);
                break;
            default:
                log->warn("Unexpected new appearance: " + QString::number(mAppearance));
            // go dark by falling through
            case DARK:
                mRed->getBean()->setCommandedState(Turnout::CLOSED);
                mBlue->getBean()->setCommandedState(Turnout::CLOSED);
                mGreen->getBean()->setCommandedState(Turnout::CLOSED);
                break;
        }
    }
}

/**
 * Remove references to and from this object, so that it can eventually be
 * garbage-collected.
 */
//@Override
/*public*/ void TripleOutputSignalHead::dispose() {
    mBlue = nullptr;
    DoubleTurnoutSignalHead::dispose();
}

/*public*/ NamedBeanHandle<Turnout*>* TripleOutputSignalHead::getBlue() {
    return mBlue;
}

/*public*/ void TripleOutputSignalHead::setBlue(NamedBeanHandle<Turnout*>* t) {
    mBlue = t;
}

// claim support for Lunar aspects
/*final*/ /*static*/ /*private*/ QVector<int> TripleOutputSignalHead::validStates = QVector<int>() <<
    TripleOutputSignalHead::DARK <<
    TripleOutputSignalHead::RED <<
    TripleOutputSignalHead::LUNAR <<
    TripleOutputSignalHead::YELLOW <<
    TripleOutputSignalHead::GREEN <<
    TripleOutputSignalHead::FLASHRED <<
    TripleOutputSignalHead::FLASHLUNAR <<
    TripleOutputSignalHead::FLASHYELLOW <<
    TripleOutputSignalHead::FLASHGREEN;

/*final*/ /*static*/ /*private*/ QVector<QString> TripleOutputSignalHead::validStateNames = QVector<QString>() <<
    tr("Dark") <<
    tr("Red") <<
    tr("Lunar") <<
    tr("Yellow") <<
    tr("Green") <<
    tr("FlashingRed") <<
    tr("FlashingLunar")<<
    tr("FlashingYellow") <<
    tr("FlashingGreen");

//@Override
/*public*/ QVector<int> TripleOutputSignalHead::getValidStates() {
    //return Arrays.copyOf(validStates, validStates.length);
 return QVector<int>(validStates);
}

//@Override
/*public*/ QVector<QString> TripleOutputSignalHead::getValidStateNames() {
    //return Arrays.copyOf(validStateNames, validStateNames.length);
 return QVector<QString>(validStateNames);
}

//@Override
bool TripleOutputSignalHead::isTurnoutUsed(Turnout* t) {
    if (DoubleTurnoutSignalHead::isTurnoutUsed(t)) {
        return true;
    }
    if (getBlue() != nullptr && t->equals(getBlue()->getBean())) {
        return true;
    }
    return false;
}

/**
 * Disables the feedback mechanism of the DoubleTurnoutSignalHead.
 */
//@Override
void TripleOutputSignalHead::readOutput() { }

/*private*/ /*final*/ /*static*/ Logger* TripleOutputSignalHead::log = LoggerFactory::getLogger("TripleOutputSignalHead");
