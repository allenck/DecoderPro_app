#include "abstractsignalhead.h"
#include "stringutil.h"
#include "rosterentry.h"

//const int SignalHead::Dark = 0;
//const int SignalHead::RED =  0x01;
//const int SignalHead::FLASHRED    = 0x02;
//const int SignalHead::YELLOW      = 0x04;
//const int SignalHead::FLASHYELLOW = 0x08;
//const int SignalHead::GREEN       = 0x10;
//const int SignalHead::FLASHGREEN  = 0x20;
//const int SignalHead::LUNAR       = 0x40;
//const int SignalHead::FLASHLUNAR  = 0x80;
//const int SignalHead:: HELD 		= 0x0100;
/*private*/ /*static*/ const  QVector<int> AbstractSignalHead::validStates = QVector<int>() <<                                                                                                SignalHead::DARK <<                                                                                                                                                                                              SignalHead::RED <<                                                                                               SignalHead::YELLOW <<                                                                                                                                                                                              SignalHead::GREEN <<                                                                                                                                                                                              SignalHead::LUNAR <<                                                                                                                                                                                              SignalHead::FLASHRED <<                                                                                                                                                                                              SignalHead::FLASHYELLOW <<                                                                                                                                                                                              SignalHead::FLASHGREEN <<                                                                                                                                                                                              SignalHead::FLASHLUNAR;
/*private*/ /*static*/ const QVector<QString> AbstractSignalHead::validStateNames =  QVector<QString>() <<
tr("Dark") <<
tr("Red") <<
tr("Yellow") <<
tr("Green") <<
tr("Lunar") <<
tr("Flashing Red") <<
tr("Flashing Yellow") <<
tr("Flashing Green") <<
tr("Flashing Lunar");


//AbstractSignalHead::AbstractSignalHead(QObject *parent) :
//    SignalHead(parent)
//{
//}
/**
 * Abstract class providing the basic logic of the SignalHead interface.
 * <p>
 * SignalHead system names are always upper case.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @version     $Revision: 22323 $
 */
///*public*/ abstract class AbstractSignalHead extends AbstractNamedBean
//    implements SignalHead, java.io.Serializable {

/*public*/ AbstractSignalHead::AbstractSignalHead(QString systemName, QString userName, QObject *parent)
    : SignalHead(systemName, userName, parent)
{
 //super(systemName, userName);
    mAppearance = SignalHead::DARK;
    mLit = true;
    mHeld = false;
}

/*public*/ AbstractSignalHead::AbstractSignalHead(QString systemName, QObject *parent)  : SignalHead(systemName, parent)
{
 //super(systemName);
 //validStates <<  SignalHead::DARK <<
 mAppearance = SignalHead::DARK;
 mLit = true;
 mHeld = false;
}

/*public*/ QString AbstractSignalHead::getAppearanceName(int appearance)
{
 QString ret = StringUtil::getNameFromState(
         appearance, getValidStates(), getValidStateNames().toList());
 if (ret != "") return ret;
 else
  return ("");
}
/*public*/ QString AbstractSignalHead::getAppearanceName() {
    return getAppearanceName(getAppearance());
}

/*public*/ int AbstractSignalHead::getAppearance() { return mAppearance; }

// implementing classes will typically have a function/listener to get
// updates from the layout, which will then call
//		/*public*/ void firePropertyChange(QString propertyName,
//						Object oldValue,
//						Object newValue)
// _once_ if anything has changed state

/**
 * Determine whether this signal shows an aspect or appearance
 * that allows travel past it, e.g. it's "been cleared".
 * This might be a yellow or green appearance, or an Approach or Clear
 * aspect
 */
//@Override
/*public*/ bool AbstractSignalHead::isCleared() { return !isAtStop() && !isShowingRestricting() && getAppearance()!=DARK; }

/**
 * Determine whether this signal shows an aspect or appearance
 * that allows travel past it only at restricted speed.
 * This might be a flashing red appearance, or a
 * Restricting aspect.
 */
//@Override
/*public*/ bool AbstractSignalHead::isShowingRestricting() { return getAppearance() == FLASHRED || getAppearance() == LUNAR || getAppearance() == FLASHLUNAR; }

/**
 * Determine whether this signal shows an aspect or appearance
 * that forbid travel past it.
 * This might be a red appearance, or a
 * Stop aspect. Stop-and-Proceed or Restricting would return false here.
 */
//@Override
/*public*/ bool AbstractSignalHead::isAtStop()  { return getAppearance() == RED; }

/**
 * Default behavior for "lit" parameter is
 * to track value and return it.
 */
/*public*/ bool AbstractSignalHead::getLit() {return mLit;}

/**
 * "Held" parameter is just tracked and notified.
 */
/*public*/ bool AbstractSignalHead::getHeld() {return mHeld;}

/**
 * Implement a shorter name for setAppearance.
 *<P>
 * This generally shouldn't be used by Java code; use
 * setAppearance instead.  The is provided to make Jython
 * script access easier to read.
 */
/*public*/ void AbstractSignalHead::setState(int s) { setAppearance(s); }

//void AbstractSignalHead::setAppearance(int appearance)
//{
// firePropertyChange("appearance", QVariant(), QVariant(appearance));
// //emit propertyChange(new PropertyChangeEvent((QObject*)this,"appearance", QVariant(), QVariant(appearance)));
//}

/**
 * Implement a shorter name for getAppearance.
 *<P>
 * This generally shouldn't be used by Java code; use
 * getAppearance instead.  The is provided to make Jython
 * script access easier to read.
 */
/*public*/ int AbstractSignalHead::getState() { return getAppearance(); }

//@edu.umd.cs.findbugs.annotations.SuppressWarnings({"EI_EXPOSE_REP", "MS_EXPOSE_REP"}) // OK until Java 1.6 allows return of cheap array copy
/*public*/ /*static*/ QVector<int> AbstractSignalHead::getDefaultValidStates()
{
 return validStates;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings({"EI_EXPOSE_REP", "MS_EXPOSE_REP"}) // OK until Java 1.6 allows return of cheap array copy
/*public*/ /*static*/ const QVector<QString> AbstractSignalHead::getDefaultValidStateNames() {
    return validStateNames;
}
/*public*/ /*static*/ const QString AbstractSignalHead::getDefaultStateName(int appearance)
{
 QString ret = StringUtil::getNameFromState(appearance, getDefaultValidStates(), getDefaultValidStateNames().toList());
 if (ret != "") return ret;
 else return ("");
}

///*private*/ static final QString[] validStateNames = new QString[]{
//    tr("SignalHeadStateDark"),
//    tr("SignalHeadStateRed"),
//    tr("SignalHeadStateYellow"),
//    tr("SignalHeadStateGreen"),
//    tr("SignalHeadStateLunar"),
//    tr("SignalHeadStateFlashingRed"),
//    tr("SignalHeadStateFlashingYellow"),
//    tr("SignalHeadStateFlashingGreen"),
//    tr("SignalHeadStateFlashingLunar"),
//};

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<int> AbstractSignalHead::getValidStates()
{
 return validStates;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<QString> AbstractSignalHead::getValidStateNames()
{
 return validStateNames;
}
/*public*/ void AbstractSignalHead::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException)
{
 if ("CanDelete"==(evt->getPropertyName()))
 { //IN18N
  if (isTurnoutUsed((Turnout*) VPtr<Turnout>::asPtr(evt->getOldValue())))
  {
   Logger::error(tr("Turnout is in use by SignalHead \"%1\"").arg(getDisplayName()));
   PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
   throw  PropertyVetoException(tr("Turnout is in use by Signal Head \"%1\"").arg( getDisplayName()), e); //IN18N
  }
 }
 else if ("DoDelete"==(evt->getPropertyName()))
 {
  //log.info("Call to do delete"); //IN18N
 }
}

/*public*/ QString AbstractSignalHead::getBeanType()
{
 return tr("SignalHead");
}
