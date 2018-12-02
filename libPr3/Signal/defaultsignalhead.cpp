#include "defaultsignalhead.h"
#include "virtualsignalhead.h"
#include "singleturnoutsignalhead.h"
#include "doubleturnoutsignalhead.h"

//DefaultSignalHead::DefaultSignalHead(QObject *parent) :
//    AbstractSignalHead(parent)
//{
//}
/**
 * Default implementation of the basic logic of the SignalHead interface.
 *
 * This class only claims support for the Red, Yellow and Green appearances,
 * and their corressponding flashing forms.  Support for Lunar is deferred
 * to DefaultLunarSignalHead.
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2009
 * @version     $Revision: 22323 $
 */
///*public*/ abstract class DefaultSignalHead extends AbstractSignalHead {

/*public*/ DefaultSignalHead::DefaultSignalHead(QString systemName, QString userName, QObject *parent) : AbstractSignalHead(systemName, userName, parent)
{
 //super(systemName, userName);
 log = new Logger("DefaultSignalHead");
 mFlashOn = true;
 delay = 750;
 timer = NULL;
}

/*public*/ DefaultSignalHead::DefaultSignalHead(QString systemName, QObject *parent)
    : AbstractSignalHead(systemName, parent)
{
 //super(systemName);
 log = new Logger("DefaultSignalHead");
 mFlashOn = true;
 delay = 750;
 timer = NULL;
}

/*public*/ void DefaultSignalHead::setAppearance(int newAppearance)
{
 int oldAppearance = mAppearance;
 mAppearance = newAppearance;
 appearanceSetsFlashTimer(newAppearance);

 /* there are circumstances (admittedly rare) where signals and turnouts can get out of sync
  * allow 'newAppearance' to be set to resync these cases - P Cressman
  * if (oldAppearance != newAppearance) */
 updateOutput();

 // notify listeners, if any
 firePropertyChange("Appearance", oldAppearance, newAppearance);
}

/**
 * Call to set timer when updating the appearance.
 *
 * @param newAppearance the new appearance
 */
/*protected*/ void DefaultSignalHead::appearanceSetsFlashTimer(int newAppearance)
{
 if (mLit && ((newAppearance == FLASHGREEN)
         || (newAppearance == FLASHYELLOW)
         || (newAppearance == FLASHRED)
         || (newAppearance == FLASHLUNAR)))
 {
  startFlash();
 }
 if ((!mLit) || ((newAppearance != FLASHGREEN)
         && (newAppearance != FLASHYELLOW)
         && (newAppearance != FLASHRED)
         && (newAppearance != FLASHLUNAR)))
 {
  stopFlash();
 }
}

/*public*/ void DefaultSignalHead::setLit(bool newLit)
{
 if(getSystemName() == "LH15" || getSystemName() == "LH1")
  log->debug(tr("setLit called curr mLit = %1, new = %2").arg(mLit).arg(newLit));
 bool oldLit = mLit;
 mLit = newLit;
 if (oldLit != newLit)
 {
  if ( mLit && ((mAppearance == SignalHead::FLASHGREEN)
                || (mAppearance == SignalHead::FLASHYELLOW)
                || (mAppearance == SignalHead::FLASHRED)
                || (mAppearance == SignalHead::FLASHLUNAR) ) )
            startFlash();
  if (!mLit)
   stopFlash();
  updateOutput();
  // notify listeners, if any
  firePropertyChange("Lit", QVariant(oldLit), QVariant(newLit));
 }
}

/**
 * Set the held parameter.
 * <P>
 * Note that this does not directly effect the output on the layout;
 * the held parameter is a local variable which effects the aspect
 * only via higher-level logic
 */
/*public*/ void DefaultSignalHead::setHeld(bool newHeld)
{
 bool oldHeld = mHeld;
 mHeld = newHeld;
 if (oldHeld != newHeld)
 {
  // notify listeners, if any
  firePropertyChange("Held", QVariant(oldHeld), QVariant(newHeld));
 }
}

/**
 * Type-specific routine to handle output to the layout hardware.
 *
 * Does not notify listeners of changes; that's done elsewhere.
 * Should use the following variables to determine what to send:
 *<UL>
 *<LI>mAppearance
 *<LI>mLit
 *<LI>mFlashOn
 *</ul>
 */
//abstract protected void updateOutput();


/*
 * Start the timer that controls flashing
 */
/*protected*/ void DefaultSignalHead::startFlash()
{
 // note that we don't force mFlashOn to be true at the start
 // of this; that way a flash in process isn't disturbed.
 if (timer==NULL)
 {
  timer = new QTimer();
//        new java.awt.event.ActionListener() {
//                /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                    timeout();
//                }
//            });
  connect(timer, SIGNAL(timeout()), this,  SLOT(timeout()));
  //timer->setInitialDelay(delay);
  //timer.setRepeats(true);
  timer->setSingleShot(false);
 }
 timer->start(delay);
}

/*private*/ void DefaultSignalHead::timeout()
{
 int oldMFlash = mFlashOn;
 mFlashOn = !mFlashOn;

 updateOutput();
 firePropertyChange("flash", oldMFlash, mFlashOn);
}

/*
 * Stop the timer that controls flashing.
 *
 * This is only a resource-saver; the actual use of
 * flashing happens elsewhere
 */
/*protected*/ void DefaultSignalHead::stopFlash()
{
 if (timer!=NULL)
 {
  timer->stop();
 }
 mFlashOn = true;
}

/*final*/ /*static*/ /*private*/ QVector<int> DefaultSignalHead::validStates = QVector<int>() <<
    SignalHead::DARK <<
    SignalHead::RED <<
    SignalHead::YELLOW <<
    SignalHead::GREEN <<
    SignalHead::FLASHRED <<
    SignalHead::FLASHYELLOW <<
    SignalHead::FLASHGREEN <<
    SignalHead::LUNAR <<
    SignalHead::FLASHLUNAR                                                                                              ;

/*final*/ /*static*/ /*private*/ QVector<QString> DefaultSignalHead::validStateNames =  QVector<QString>() <<
    tr("Dark") <<
    tr("Red") <<
    tr("Yellow") <<
    tr("Green") <<
    tr("Flashing Red") <<
    tr("Flashing Yellow") <<
    tr("Flashing Green") << tr("Lunar")  << tr("Flashing Lunar");

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<int> DefaultSignalHead::getValidStates() {
    return validStates;
}

//@edu.umd.cs.findbugs.annotations.SuppressWarnings(value="EI_EXPOSE_REP") // OK until Java 1.6 allows return of cheap array copy
/*public*/ QVector<QString> DefaultSignalHead::getValidStateNames() {
    return validStateNames;
}

bool DefaultSignalHead::isTurnoutUsed(Turnout* /*t*/)
{
 return false;
}

/*public*/ bool DefaultSignalHead::isFlashOn()
{
 return mFlashOn;
}
