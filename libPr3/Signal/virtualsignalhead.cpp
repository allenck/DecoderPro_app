#include "virtualsignalhead.h"

//VirtualSignalHead::VirtualSignalHead(QObject *parent) :
//    DefaultSignalHead(parent)
//{
//}
/**
 * A signal head that exists only within the program.
 * <P>
 * This can be useful e.g. as part of a more complex signal calculation.
 *
 * @author	Bob Jacobsen Copyright (C) 2005
 * @version	$Revision: 17977 $
 */
///*public*/ class VirtualSignalHead extends DefaultSignalHead {

/*public*/ VirtualSignalHead::VirtualSignalHead(QString sys, QString user, QObject *parent) : DefaultSignalHead(sys, user, parent){
    //super(sys, user);
//    saveAppearance = SignalHead::DARK;
}

///*public*/ VirtualSignalHead(QString sys) {
//    super(sys);
//}

/*protected*/ void VirtualSignalHead::updateOutput()
{
#if 0
 // ACK formerly void function enhanced to show flashing aspects
 int newAppearance;
 if (mLit == false)
 {
  //mAppearance = SignalHead::DARK;
  return;
 }
 else if ( !mFlashOn &&
           ( (mAppearance == SignalHead::FLASHGREEN) ||
           (mAppearance == SignalHead::FLASHYELLOW) ||
           (mAppearance == SignalHead::FLASHRED) ) )
 {
  // flash says to make output dark
  saveAppearance = mAppearance;
  mAppearance = SignalHead::DARK;
  AbstractSignalHead::setAppearance(mAppearance);
  return;
 }
 else if ( mFlashOn &&
               ( (mAppearance == SignalHead::FLASHGREEN) ||
               (mAppearance == SignalHead::FLASHYELLOW) ||
               (mAppearance == SignalHead::FLASHRED) || mAppearance == SignalHead::DARK) )
 {
  mAppearance = saveAppearance;
  AbstractSignalHead::setAppearance(mAppearance);
 }
#endif
}

/**
 * Remove references to and from this object, so that it can
 * eventually be garbage-collected.
 */
/*public*/ void VirtualSignalHead::dispose() {
    DefaultSignalHead::dispose();
}
bool VirtualSignalHead::isTurnoutUsed(Turnout* t)
{
 return false;
}
