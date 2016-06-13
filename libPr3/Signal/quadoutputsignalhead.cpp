#include "quadoutputsignalhead.h"
#include "turnout.h"

//QuadOutputSignalHead::QuadOutputSignalHead(QObject *parent) :
//    TripleTurnoutSIgnalHead(parent)
//{
//}
/**
 * Drive a single signal head via four "Turnout" objects.
 * <P>
 * After much confusion, the user-level terminology
 * was changed to call these "Triple Output"; the class
 * name remains the same to reduce recoding.
 * <P>
 * The four Turnout objects are provided during construction,
 * and each drives a specific color (RED, YELLOW, GREEN, and LUNAR).
 * Normally, "THROWN" is on, and "CLOSED" is off.
 * <P>
 * This class doesn't currently listen to the Turnout's to see if they've
 * been changed via some other mechanism.
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * @version	$Revision: 22323 $
 */
///*public*/ class QuadOutputSignalHead extends TripleTurnoutSignalHead {

/*public*/ QuadOutputSignalHead::QuadOutputSignalHead(QString sys, QString user, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, NamedBeanHandle<Turnout*> *lunar, QObject *parent) : TripleTurnoutSignalHead(sys, user, green, yellow, red, parent)
{
 //super(sys, user, green, yellow, red);
 mLunar = lunar;
}

/*public*/ QuadOutputSignalHead::QuadOutputSignalHead(QString sys, NamedBeanHandle<Turnout*>* green, NamedBeanHandle<Turnout*>* yellow, NamedBeanHandle<Turnout*>* red, NamedBeanHandle<Turnout*>* lunar, QObject *parent): TripleTurnoutSignalHead(sys, green, yellow, red, parent)
{
 //super(sys, green, yellow, red);
 mLunar = lunar;
}

/*protected*/ void QuadOutputSignalHead::updateOutput() {
 if (mLit == false) {
  TripleTurnoutSignalHead::updateOutput();
 } else if ( !mFlashOn &&
             ( (mAppearance == SignalHead::FLASHGREEN) ||
               (mAppearance == SignalHead::FLASHYELLOW) ||
               (mAppearance == SignalHead::FLASHRED) ||
               (mAppearance == SignalHead::FLASHLUNAR) ) ) {
  // flash says to make output dark
  mRed->getBean()->setCommandedState(Turnout::CLOSED);
  mYellow->getBean()->setCommandedState(Turnout::CLOSED);
  mGreen->getBean()->setCommandedState(Turnout::CLOSED);
  mLunar->getBean()->setCommandedState(Turnout::CLOSED);
  return;

 } else {
  switch (mAppearance) {
  case SignalHead::LUNAR:
  case SignalHead::FLASHLUNAR:
   mLunar->getBean()->setCommandedState(Turnout::THROWN);
   mRed->getBean()->setCommandedState(Turnout::CLOSED);
   mYellow->getBean()->setCommandedState(Turnout::CLOSED);
   mGreen->getBean()->setCommandedState(Turnout::CLOSED);
   break;
  default:
   // let parent handle rest of cases
   mLunar->getBean()->setCommandedState(Turnout::CLOSED);
   TripleTurnoutSignalHead::updateOutput();
   break;
  }
 }
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void QuadOutputSignalHead::dispose() {
 mLunar = NULL;
 TripleTurnoutSignalHead::dispose();
}


/*public*/ NamedBeanHandle<Turnout*>* QuadOutputSignalHead:: getLunar() {return mLunar;}
/*public*/ void QuadOutputSignalHead::setLunar(NamedBeanHandle<Turnout*>* t) {mLunar=t;}

// claim support for Lunar aspects

/*final*/ /*static*/ /*private*/QVector<int> QuadOutputSignalHead::validStates = QVector<int>() <<
    SignalHead::DARK <<
    SignalHead::RED <<
    SignalHead::LUNAR <<
    SignalHead::YELLOW <<
    SignalHead::GREEN <<
    SignalHead::FLASHRED <<
    SignalHead::FLASHLUNAR<<
    SignalHead::FLASHYELLOW <<
    SignalHead::FLASHGREEN;

/*final*/ /*static*/ /*private*/ QVector<QString> QuadOutputSignalHead::validStateNames = QVector<QString>() <<
    tr("Dark") <<
    tr("Red")<<
    tr("Lunar") <<
    tr("Yellow") <<
    tr("Green") <<
    tr("Flashing Red") <<
    tr("Flashing Lunar") <<
    tr("Flashing Yellow") <<
    tr("Flashing Green");


//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<int> QuadOutputSignalHead::getValidStates() {
 return validStates;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<QString> QuadOutputSignalHead::getValidStateNames() {
 return validStateNames;
}

//    static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(QuadOutputSignalHead.class.getName());
//}
