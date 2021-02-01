#include "lnopsmodeprogrammer.h"
#include "slotmanager.h"
#include "defaultprogrammermanager.h"
#include "rosterentry.h"
#include "programmingmode.h"
#include "lnprogrammermanager.h"
#include "locoio.h"
#include "loggerfactory.h"
#include <QStringList>

//LnOpsModeProgrammer::LnOpsModeProgrammer(QObject *parent) :
//    AddressedProgrammer(parent)
//{
//}
/**
 * Provide an Ops Mode Programmer via a wrapper what works with the LocoNet
 * SlotManager object.
 * @see             jmri.Programmer
 * @author			Bob Jacobsen Copyright (C) 2002
 * @version			$Revision: 28274 $
 */
// /*public*/ class LnOpsModeProgrammer implements AddressedProgrammer  {
/*public*/ LnOpsModeProgrammer::LnOpsModeProgrammer(LocoNetSystemConnectionMemo* memo,
            int pAddress, bool pLongAddr, QObject *parent) : QObject(parent)
{
    this->memo = memo;
    mode = ProgrammingMode::OPSBYTEMODE;
    mAddress = pAddress;
    mLongAddr = pLongAddr;
    // register to listen
    memo->getLnTrafficController()->addLocoNetListener(~0, (LocoNetListener*)this);
    connect(memo->getLnTrafficController(), SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
}

/*public*/ void LnOpsModeProgrammer::readCV(QString CV, ProgListener* pL) throw (ProgrammerException) {
// mSlotMgr->readCVOpsMode(CV, p, mAddress, mLongAddr);
 this->p = nullptr;
   // Check mode
   QStringList parts;
   LocoNetMessage* m;
   if (getMode()->equals(LnProgrammerManager::LOCONETCSOPSWMODE)) {
       memo->getSlotManager()->setMode(LnProgrammerManager::LOCONETCSOPSWMODE);
       memo->getSlotManager()->readCV(CV, pL); // deal with this via service-mode programmer
   }
   else if (getMode()->equals(LnProgrammerManager::LOCONETBDOPSWMODE))
   {
       /**
        * CV format is e.g. "113.12" where the first part defines the
        * typeword for the specific board type and the second is the specific bit number
        * Known values:
        * <ul>
        * <li>0x70 112 - PM4
        * <li>0x71 113 - BDL16
        * <li>0x72 114 - SE8
        * <li>0x73 115 - DS64
        * </ul>
        */
       if (bdOpSwAccessTimer == nullptr) {
           initiializeBdOpsAccessTimer();
       }
       p = pL;
       doingWrite = false;
       // Board programming mode
       log->debug(tr("read CV \"%1\" addr:%2").arg(CV).arg(mAddress));
       parts = CV.split(QRegExp("\\."));
       int typeWord = parts.at(0).toInt();
       int state = parts.at(parts.length()>1 ? 1 : 0).toInt();

       // make message
       m = new LocoNetMessage(6);
       m->setOpCode(LnConstants::OPC_MULTI_SENSE);
       int element = 0x62;
       if ((mAddress & 0x80) != 0) {
           element |= 1;
       }
       m->setElement(1, element);
       m->setElement(2, (mAddress-1) & 0x7F);
       m->setElement(3, typeWord);
       int loc = (state - 1) / 8;
       int bit = (state - 1) - loc * 8;
       m->setElement(4, loc * 16 + bit * 2);

       log->debug(tr("  Message %1").arg(m->toString()));
       memo->getLnTrafficController()->sendLocoNetMessage(m);
       bdOpSwAccessTimer->start();

   } else if (getMode()->equals(LnProgrammerManager::LOCONETSV1MODE)) {
       p = pL;
       doingWrite = false;
       // SV1 mode
       log->debug(tr("read CV \"%1\" addr:%2").arg(CV).arg(mAddress));
       // make message
       int locoIOAddress = mAddress&0xFF;
       int locoIOSubAddress = ((mAddress+256)/256)&0x7F;
       m = LocoIO::readCV(locoIOAddress, locoIOSubAddress, decodeCvNum(CV));
       // force version 1 tag
       m->setElement(4, 0x01);

       log->debug(tr("  Message %1").arg(m->toString()));
       memo->getLnTrafficController()->sendLocoNetMessage(m);
   } else if (getMode()->equals(LnProgrammerManager::LOCONETSV2MODE)) {
       p = pL;
       // SV2 mode
       log->debug(tr("read CV \"%1\" addr:%2").arg(CV).arg(mAddress));
       // make message
       m = new LocoNetMessage(16);
       loadSV2MessageFormat(m, mAddress, decodeCvNum(CV), 0);
       m->setElement(3, 0x02); // 1 byte read
       log->debug(tr("  Message %1").arg(m->toString()));
       memo->getLnTrafficController()->sendLocoNetMessage(m);
   } else {
       // DCC ops mode
       memo->getSlotManager()->readCVOpsMode(CV, pL, mAddress, mLongAddr);
   }
}

/*public*/ void LnOpsModeProgrammer::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 this->p = NULL;
// Check mode
 if (getMode()->equals(LnProgrammerManager::LOCONETSV1MODE))
 {
  this->p = p;
  doingWrite = true;
  // SV1 mode
  log->debug(tr("write CV \"%1\" to %2 addr:%3").arg(CV).arg(val).arg( mAddress));

  // make message
  int locoIOAddress = mAddress;
  int locoIOSubAddress = ((mAddress+256)/256)&0x7F;
  LocoNetMessage* m = LocoIO::writeCV(locoIOAddress, locoIOSubAddress, decodeCvNum(CV), val);
  // force version 1 tag
  m->setElement(4, 0x01);

  log->debug(tr("  Message %1").arg(m->toString()));
  memo->getLnTrafficController()->sendLocoNetMessage(m);
 }
 else if (getMode()->equals(LnProgrammerManager::LOCONETSV2MODE))
 {
  this->p = p;
  // SV2 mode
  log->debug(tr("write CV \"%1\" to %2 addr:%3").arg(CV).arg(val).arg( mAddress));
  // make message
  LocoNetMessage* m = new LocoNetMessage(16);
  loadSV2MessageFormat(m, mAddress, decodeCvNum(CV), val);
  m->setElement(3, 0x01); // 1 byte write
  log->debug(tr("  Message %1").arg( m->toString()));
  memo->getLnTrafficController()->sendLocoNetMessage(m);
 }
 else
 {
  // DCC ops mode
  writeCV(CV, val, p);
 }
}
#if 0
/*public*/ void LnOpsModeProgrammer::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
{
 this->p = NULL;
 // Check mode
 if (getMode()==(LnProgrammerManager::LOCONETSV1MODE))
 {
     this->p = p;
     doingWrite = false;
     // SV1 mode
     log->debug(tr("read CV \"%1\" addr:%2").arg(CV).arg(mAddress));

     // make message
     int locoIOAddress = mAddress&0xFF;
     int locoIOSubAddress = ((mAddress+256)/256)&0x7F;
     LocoNetMessage* m = LocoIO::readCV(locoIOAddress, locoIOSubAddress, decodeCvNum(CV));
     // force version 1 tag
     m->setElement(4, 0x01);

     log->debug(tr("  Message %1").arg(m->toString()));
     memo->getLnTrafficController()->sendLocoNetMessage(m);
    }
 else if (getMode()==(LnProgrammerManager::LOCONETSV2MODE))
 {
     this->p = p;
     // SV2 mode
  log->debug(tr("read CV \"%1\" addr:%2").arg(CV).arg( mAddress, mAddress));
     // make message
     LocoNetMessage* m = new LocoNetMessage(16);
     loadSV2MessageFormat(m, mAddress, decodeCvNum(CV), 0);
     m->setElement(3, 0x02); // 1 byte read
     log->debug(tr("  Message %1").arg(m->toString()));
     memo->getLnTrafficController()->sendLocoNetMessage(m);
 } else {
     // DCC ops mode
     readCV(CV, p);
 }
}
#endif
/*public*/ void LnOpsModeProgrammer::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 this->p = NULL;
 // Check mode
 if (getMode()->equals(LnProgrammerManager::LOCONETSV2MODE)) {
     // SV2 mode
  log->error(tr("confirm CV \"%1\" addr:%2 in SV2 mode not implemented").arg(CV).arg(mAddress));
     p->programmingOpReply(0, ProgListener::UnknownError);
 } else {
     // DCC ops mode
     confirmCV(CV, val, p);
 }
}

/*public*/ void LnOpsModeProgrammer::message(LocoNetMessage* m) {
    // see if reply to LNSV 1 or LNSV2 request
    if ((m->getElement( 0) & 0xFF) != 0xE5) return;
    if ((m->getElement( 1) & 0xFF) != 0x10) return;

    log->debug(tr("reply %1").arg(m->toString()));
    if (getMode()->equals(LnProgrammerManager::LOCONETSV1MODE)) {
        if ((m->getElement( 4) & 0xFF) != 0x01) return; // format 1
        if ((m->getElement( 5) & 0x70) != 0x00) return; // 5

        // check for src address (?) moved to 0x50
        // this might not be the right way to tell....
        if ((m->getElement(3) & 0x7F) != 0x50) return;

        // more checks needed? E.g. addresses?

        // Mode 1 return data comes back in
        // byte index 12, with the MSB in 0x01 of byte index 10
        //

        // check pending activity
        if (p == NULL) {
         log->warn(tr("received SV reply message with no reply object: %1").arg(m->toString()));
            return;
        } else {
         log->debug(tr("returning SV programming reply: %1").arg(m->toString()));
            int code = ProgListener::OK;
            int val;
            if (doingWrite) {
                val = m->getPeerXfrData()[7];
            } else {
                val = m->getPeerXfrData()[5];
            }
            ProgListener* temp = p;
            p = NULL;
            temp->programmingOpReply(val, code);
        }
    } else if (getMode()->equals(LnProgrammerManager::LOCONETSV2MODE)) {
        if ((m->getElement(3) != 0x41) && (m->getElement(3) != 0x42)) return; // need a "Write One Reply", or a "Read One Reply"
        if ((m->getElement( 4) & 0xFF) != 0x02) return; // format 2
        if ((m->getElement( 5) & 0x70) != 0x10) return; // need SVX1 high nibble = 1
        if ((m->getElement(10) & 0x70) != 0x10) return; // need SVX2 high nibble = 1

        // more checks needed? E.g. addresses?

        // return reply
        if (p == NULL) {
            log->error(tr("received SV reply message with no reply object: %1").arg(m->toString()));
            return;
        } else {
         log->debug(tr("returning SV programming reply: %1").arg(m->toString()));
            int code = ProgListener::OK;
            int val = (m->getElement(11)&0x7F)|(((m->getElement(10)&0x01) != 0x00)? 0x80:0x00);

            ProgListener* temp = p;
            p = NULL;
            temp->programmingOpReply(val, code);
        }
    }
}

int LnOpsModeProgrammer::decodeCvNum(QString CV)
{
    //try {
 return CV.toInt();
//    } catch (java.lang.NumberFormatException e) {
//        return 0;
//    }
}

void LnOpsModeProgrammer::loadSV2MessageFormat(LocoNetMessage* m, int mAddress, int cvAddr, int data) {
    m->setElement(0, 0xE5);
    m->setElement(1, 0x10);
    m->setElement(2, 0x01);
    // 3 SV_CMD to be filled in later
    m->setElement(4, 0x02);
    // 5 will come back to SVX1
    m->setElement(6, mAddress&0xFF);
    m->setElement(7, (mAddress>>8)&0xFF);
    m->setElement(8, cvAddr&0xFF);
    m->setElement(9, (cvAddr/256)&0xFF);

    // set SVX1
    int svx1 = 0x10
                |((m->getElement(6)&0x80) != 0 ? 0x01 : 0)  // DST_L
                |((m->getElement(7)&0x80) != 0 ? 0x02 : 0)  // DST_L
                |((m->getElement(8)&0x80) != 0 ? 0x04 : 0)  // DST_L
                |((m->getElement(9)&0x80) != 0 ? 0x08 : 0); // SV_ADRH
    m->setElement(5, svx1);
    m->setElement(6, m->getElement(6)&0x7F);
    m->setElement(7, m->getElement(7)&0x7F);
    m->setElement(8, m->getElement(8)&0x7F);
    m->setElement(9, m->getElement(9)&0x7F);

    // 10 will come back to SVX2
    m->setElement(11, data&0xFF);
    m->setElement(12, (data>>8)&0xFF);
    m->setElement(13, (data>>16)&0xFF);
    m->setElement(14, (data>>24)&0xFF);

    // set SVX2
    int svx2 = 0x10
                |((m->getElement(11)&0x80) != 0 ? 0x01 : 0)
                |((m->getElement(12)&0x80) != 0 ? 0x02 : 0)
                |((m->getElement(13)&0x80) != 0 ? 0x04 : 0)
                |((m->getElement(14)&0x80) != 0 ? 0x08 : 0);
    m->setElement(10, svx2);
    m->setElement(11, m->getElement(11)&0x7F);
    m->setElement(12, m->getElement(12)&0x7F);
    m->setElement(13, m->getElement(13)&0x7F);
    m->setElement(14, m->getElement(14)&0x7F);
}


//@Override
/*public*/ /*final*/ void LnOpsModeProgrammer::setMode(ProgrammingMode* m)
{
    if (getSupportedModes().contains(m->getStandardName())) {
        mode = m;
        notifyPropertyChange("Mode", VPtr<ProgrammingMode>::asQVariant(mode), VPtr<ProgrammingMode>::asQVariant(m));
    } else {
        throw IllegalArgumentException("Invalid requested mode: "+m->toString());
    }
}
/*public*/ /*final*/ ProgrammingMode* LnOpsModeProgrammer::getMode() { return mode; }

 /**
 * Types implemented here.
 */
//@Override
/*public*/ QList<QString> LnOpsModeProgrammer::getSupportedModes()
{
 QStringList ret =  QStringList();//  (4,nullptr);
 ret.append("OPSBYTEMODE");
 ret.append("LOCONETOPSBOARD");
 ret.append("LOCONETSV1MODE");
 ret.append("LOCONETSV2MODE");
 ret.append("LOCONETBDOPSWMODE");
 ret.append("LOCONETCSOPSWMODE");
 return ret;
}

///**
// * Provide a {@link java.beans.PropertyChangeSupport} helper.
// */
//private final PropertyChangeSupport propertyChangeSupport = new PropertyChangeSupport(this);

/**
 * Add a PropertyChangeListener to the listener list.
 *
 * @param listener The PropertyChangeListener to be added
 */
/*public*/ void LnOpsModeProgrammer::addPropertyChangeListener(PropertyChangeListener* listener) {
 //propertyChangeSupport.addPropertyChangeListener(listener);
 connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*public*/ void LnOpsModeProgrammer::removePropertyChangeListener(PropertyChangeListener* listener) {
//    propertyChangeSupport.removePropertyChangeListener(listener);
 disconnect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
}

/*protected*/ void LnOpsModeProgrammer::notifyPropertyChange(QString key, QVariant oldValue, QVariant value) {
    //propertyChangeSupport.firePropertyChange(key, oldValue, value);
    emit propertyChange(new PropertyChangeEvent(this, key, oldValue, value));
}

/**
 * {@inheritDoc}
 *
 * Can this ops-mode programmer read back values? Yes, if transponding
 * hardware is present and regular ops mode, or if in any other mode.
 *
 * @return always true
 */
//@Override
/*public*/ bool LnOpsModeProgrammer::getCanRead() {
 if (getMode()->equals(ProgrammingMode::OPSBYTEMODE))
  return memo->getSlotManager()->getTranspondingAvailable(); // only way can be false
 return true;
}

//@Override
/*public*/ bool LnOpsModeProgrammer::getCanRead(QString /*addr*/) {
   return getCanRead();
}

//@Override
/*public*/ bool LnOpsModeProgrammer::getCanWrite()  { return true; }
//@Override
/*public*/ bool LnOpsModeProgrammer::getCanWrite(QString addr) {
    return getCanWrite() && addr.toInt()<=1024;
}
/**
 * Learn about whether the programmer does any kind of verification of write
 * operations
 *
 * @param addr A CV address to check (in case this varies with CV range) or
 *             null for any
 * @return The confirmation behavior that can be counted on (might be better
 *         in some cases)
 */
//@Nonnull
/*public*/ Programmer::WriteConfirmMode LnOpsModeProgrammer::getWriteConfirmMode(QString addr){
 if (getMode()->equals(ProgrammingMode::OPSBYTEMODE)) {
     return (Programmer::WriteConfirmMode)WriteConfirmMode::NotVerified;
 }
 return (Programmer::WriteConfirmMode)WriteConfirmMode::DecoderReply;
}

/**
 * wrapper to call {@link jmri.ProgListener#programmingOpReply} that verifies
 * the specified progListener is not null.
 *
 * @param p listener to notify
 * @param value result value
 * @param status code from jmri.ProgListener
 */
/*default*/ /*public*/ void LnOpsModeProgrammer::notifyProgListenerEnd(ProgListener* p, int value, int status) {
    if ( p != nullptr ) {
       p->programmingOpReply(value, status);
    }
}

/*public*/ QString LnOpsModeProgrammer::decodeErrorCode(int i) {
    return mSlotMgr->decodeErrorCode(i);
}

/*public*/ bool LnOpsModeProgrammer::getLongAddress() {return mLongAddr;}

/*public*/ int LnOpsModeProgrammer::getAddressNumber() { return mAddress; }

/*public*/ QString LnOpsModeProgrammer::getAddress() { return QString::number(getAddressNumber())+" "+QString::number(getLongAddress()); }
void LnOpsModeProgrammer::initiializeBdOpsAccessTimer() {
        if (bdOpSwAccessTimer == nullptr) {
//            bdOpSwAccessTimer = new javax.swing.Timer(1000, (ActionEvent e) -> {
//                ProgListener temp = p;
//                p = null;
//                notifyProgListenerEnd(temp, 0, ProgListener.FailedTimeout);
//            });
         bdOpSwAccessTimer = new OpSwAccessTimer(this);
        //bdOpSwAccessTimer->setInitialDelay(1000);
           bdOpSwAccessTimer->setInterval(1000);
        //bdOpSwAccessTimer->setRepeats(false);
           bdOpSwAccessTimer->setSingleShot(true);
        }
    }
// initialize logging
/*static*/ Logger* LnOpsModeProgrammer::log = LoggerFactory::getLogger("LnOpsModeProgrammer");

//}
