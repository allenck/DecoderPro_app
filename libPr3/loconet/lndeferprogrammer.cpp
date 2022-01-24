#include "lndeferprogrammer.h"
#include "loggerfactory.h"
#include "slotmanager.h"
#include "loconetsystemconnectionmemo.h"

/**
 * Programmer implementation for Programmer that uses a SlotManager (which is also an AbstractProgrammer)
 * that might be provided later. This is done by connecting through a LocoNetSystemConnectionMemo.
 *
 * @author Bob Jacobsen Copyright (C) 2018
 */
// /*public*/ class LnDeferProgrammer implements Programmer {

/*public*/ LnDeferProgrammer::LnDeferProgrammer(/*@Nonnull*/ LocoNetSystemConnectionMemo* memo, QObject* parent)
 : AbstractProgrammer(parent)
{
    this->memo = memo;
}

/** {@inheritDoc} */
//@Override
/*public*/ void LnDeferProgrammer::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->writeCV(CV, val, p);
    } else {
        log->warn("writeCV called without a SlotManager");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void LnDeferProgrammer::readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->readCV(CV, p);
    } else {
        log->warn("readCV called without a SlotManager");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/ void LnDeferProgrammer::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->confirmCV(CV, val, p);
    } else {
        log->warn("confirmCV called without a SlotManager");
    }
}

//@Override
/*@Nonnull*/ /*public*/ QList<QString> LnDeferProgrammer::getSupportedModes() {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getSupportedModes();
    } else {
        log->warn("getSupportedModes() called without a SlotManager");
        return QList<QString>(); // empty
    }
}

//@Override
/*public*/ void LnDeferProgrammer::setMode(ProgrammingMode* p) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->setMode(p);
    } else {
        log->warn("setMode() called without a SlotManager");
    }
}

//@Override
/*public*/ ProgrammingMode* LnDeferProgrammer::getMode() {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getMode();
    } else {
        log->warn("getMode() called without a SlotManager");
        return ProgrammingMode::ADDRESSMODE; // being cautious
    }
}

//@Override
/*public*/ bool LnDeferProgrammer::getCanRead() {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getCanRead();
    } else {
        log->warn("getCanRead() called without a SlotManager");
        return true; // being cautious
    }
}

//@Override
/*public*/ bool LnDeferProgrammer::getCanRead(QString addr) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
//        return m->getCanRead(addr);
    } else {
        log->warn("getCanRead(String) called without a SlotManager");
        return true; // being cautious
    }
}

//@Override
/*public*/ bool LnDeferProgrammer::getCanWrite() {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getCanWrite();
    } else {
        log->warn("getCanWrite() called without a SlotManager");
        return true; // being cautious
    }
}

//@Override
/*public*/ bool LnDeferProgrammer::getCanWrite(QString addr) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getCanWrite(addr);
    } else {
        log->warn("getCanWrite(String) called without a SlotManager");
        return true; // being cautious
    }
}

//@Override
/*@Nonnull*/
/*public*/ Programmer::WriteConfirmMode LnDeferProgrammer::getWriteConfirmMode(QString addr) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->getWriteConfirmMode(addr);
    } else {
        log->warn("getWriteConfirmMode() called without a SlotManager");
        return Programmer::WriteConfirmMode::DecoderReply; // being cautious
    }
}


//@Override
/*public*/ void LnDeferProgrammer::notifyProgListenerEnd(ProgListener* p, int value, int status) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        ((Programmer*)m)->notifyProgListenerEnd(p, value, status);
    } else {
        log->warn("notifyProgListenerEnd called without a SlotManager");
    }
}


//@Override
/*public*/ void LnDeferProgrammer::addPropertyChangeListener(PropertyChangeListener* p) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->addPropertyChangeListener(p);
    } else {
        log->warn("addPropertyChangeListener called without a SlotManager");
    }
}

//@Override
/*public*/ void LnDeferProgrammer::removePropertyChangeListener(PropertyChangeListener* p) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        m->removePropertyChangeListener(p);
    } else {
        log->warn("removePropertyChangeListener called without a SlotManager");
    }
}

//@Override
/*public*/ QString LnDeferProgrammer::decodeErrorCode(int i) {
    SlotManager* m = memo->getSlotManager();
    if (m!=nullptr) {
        return m->decodeErrorCode(i);
    } else {
        log->warn("decodeErrorCode called without a SlotManager");
        return "<unknown>"; // being cautious
    }
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* LnDeferProgrammer::log = LoggerFactory::getLogger("LnDeferProgrammer");
