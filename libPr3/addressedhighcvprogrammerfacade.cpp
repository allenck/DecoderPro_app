#include "addressedhighcvprogrammerfacade.h"
#include "proglistener.h"
#include "programmer.h"
#include "logger.h"

//AddressedHighCvProgrammerFacade::AddressedHighCvProgrammerFacade(QObject *parent) :
//  AbstractProgrammer(parent)
//{
//}
/**
 * Programmer facade, at this point just an example.
 * <p>
 * This is for decoders that have an alternate high-CV access method for command
 * stations that can't address all 1024. It falls back to that mode if the CS
 * can't directly address an requested CV address. In the fall back, CVs from 0
 * to "top" are addressed directly. (Top being a supplied parameter) Above the
 * top CV, the upper part of the CV address written to a specific CV, followed
 * by an write with just the lower part to a second CV, then access to a 3rd CV
 * for the value read/write. The upper and lower parts are calculated using a
 * supplied modulus, e.g. 100.
 * <p>
 * This method is used by some ESU decoders.
 *
 * @see implementation.ProgrammerFacadeSelector
 *
 * @author Bob Jacobsen Copyright (C) 2013
 * @version	$Revision: 24246 $
 */
///*public*/ class AddressedHighCvProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 * @param top        CVs above this use the indirect method
 * @param addrCVhigh CV to which the high part of address is to be written
 * @param addrCVlow  CV to which the low part of address is to be written
 * @param valueCV    Value read/written here once address has been written
 * @param modulo     Modulus for determining high/low address parts
 */
/*public*/ AddressedHighCvProgrammerFacade::AddressedHighCvProgrammerFacade(Programmer* prog, QString top, QString addrCVhigh, QString addrCVlow, QString valueCV, QString modulo, QObject *parent) :
AbstractProgrammerFacade(prog, parent) {
    //super(prog);
 log = new Logger("AddressedHighCvProgrammerFacade");
 state = NOTPROGRAMMING;
 _usingProgrammer = NULL;

 this->top = top.toInt();
 this->addrCVhigh = addrCVhigh;
 this->addrCVlow = addrCVlow;
 this->valueCV = valueCV;
 this->modulo = modulo.toInt();
 log->debug(tr("Created with ") + prog->self()->metaObject()->className() + ", " + QString::number(this->top) + ", " + this->addrCVhigh + ", " + this->addrCVlow + ", " + this->valueCV + ", " + QString::number(this->modulo));
}

//@Override
/*public*/ void AddressedHighCvProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 log->debug("start writeCV");
 _val = val;
 useProgrammer(p);
 if (prog->getCanWrite(CV) || _cv <= top)
 {
  state = PROGRAMMING;
  prog->writeCV(CV, val, (ProgListener*)this);
 } else {
  // write index first
  state = WRITELOWWRITE;
  prog->writeCV(addrCVhigh, _cv / modulo, (ProgListener*)this);
 }
}

//@Override
/*public*/ void AddressedHighCvProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
{
    log->debug("start readCV");
    useProgrammer(p);
    if (prog->getCanRead(CV) || _cv <= top) {
        state = PROGRAMMING;
        prog->readCV(CV, (ProgListener*)this);
    } else {
        // write index first
        state = WRITELOWREAD;
        prog->writeCV(addrCVhigh, _cv / modulo, (ProgListener*)this);
    }
}


// internal method to remember who's using the programmer
/*protected*/ void AddressedHighCvProgrammerFacade::useProgrammer(ProgListener* p) //throws ProgrammerException
{
 // test for only one!
 if (_usingProgrammer != NULL && _usingProgrammer != p) {
     if (log->isInfoEnabled()) {
         log->info(tr("programmer already in use by ") + _usingProgrammer->self()->metaObject()->className());
     }
     throw ProgrammerException("programmer in use");
 } else {
     _usingProgrammer = p;
     return;
 }
}


// get notified of the final result
// Note this assumes that there's only one phase to the operation
/*public*/ void AddressedHighCvProgrammerFacade::programmingOpReply(int value, int status) {
    if (log->isDebugEnabled()) {
        log->debug("notifyProgListenerEnd value " + QString::number(value) + " status " + QString::number(status));
    }

    if (status != ProgListener::OK)
    {
        // pass abort up
        log->debug("Reset and pass abort up");
        ProgListener* temp = _usingProgrammer;
        _usingProgrammer = nullptr; // done
        state = ProgState::NOTPROGRAMMING;
        temp->programmingOpReply(value, status);
        return;
    }

    if (_usingProgrammer == nullptr) {
        log->error("No listener to notify, reset and ignore");
        state = ProgState::NOTPROGRAMMING;
        return;
    }

    switch (state) {
    case PROGRAMMING:
    {
     // the programmingOpReply handler might send an immediate reply, so
     // clear the current listener _first_
     ProgListener* temp = _usingProgrammer;
     _usingProgrammer = NULL; // done
     state = NOTPROGRAMMING;
     temp->programmingOpReply(value, status);
     break;
    }
    case WRITELOWREAD:
     try {
         state = ProgState::FINISHREAD;
         prog->writeCV(addrCVlow, _cv % modulo, (ProgListener*)this);
     } catch (ProgrammerException e) {
         log->error("Exception doing final read"/*, e*/);
     }
     break;
    case WRITELOWWRITE:
    {
     try {
         state = FINISHWRITE;
         prog->writeCV(addrCVlow, _cv % modulo,(ProgListener*) this);
     } catch (ProgrammerException e) {
         log->error("Exception doing final write"/*, e*/);
     }
     break;
    }
    case FINISHREAD:
    {
     try {
         state = PROGRAMMING;
         prog->readCV(valueCV, (ProgListener*)this);
     } catch (ProgrammerException e) {
         log->error("Exception doing final read"/*, e*/);
     }
     break;
    }
    case FINISHWRITE:
        try {
            state = PROGRAMMING;
            prog->writeCV(valueCV, _val, (ProgListener*)this);
        } catch (ProgrammerException e) {
            log->error("Exception doing final write"/*, e*/);
        }
        break;
    default:
        log->error("Unexpected state on reply: " + state);
        // clean up as much as possible
        _usingProgrammer = nullptr;
        state = NOTPROGRAMMING;

    }

}

// Access to full address space provided by this->
/*public*/ bool AddressedHighCvProgrammerFacade::getCanRead() {
    return true;
}

/*public*/ bool AddressedHighCvProgrammerFacade::getCanRead(QString addr) {
 return addr.toInt() <= 1024;
}

/*public*/ bool AddressedHighCvProgrammerFacade::getCanWrite() {
    return true;
}

/*public*/ bool AddressedHighCvProgrammerFacade::getCanWrite(QString addr) {
    return addr.toInt() <= 1024;
}
