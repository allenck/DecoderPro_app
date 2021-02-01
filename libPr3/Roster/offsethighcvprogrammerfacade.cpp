#include "offsethighcvprogrammerfacade.h"
#include "loggerfactory.h"

/**
 * Programmer facade, at this point just an example.
 * <p>
 * This is for decoders that have an alternate high-CV access method for command
 * stations that can't address all 1024. It falls back to that mode if the CS
 * can't directly address an requested CV address. In the fall back, CVs from 0
 * to "top" are addressed directly. Above the top CV, the upper part of the
 * address is written to a specific CV, followed by an operation to just the
 * lower part of the address. The upper and lower parts are calculated using a
 * supplied modulus, e.g. 100.
 * <p>
 * For example, to write the value N to CV xyy, this will do (modulo = 100):
 * <ul>
 * <li>Write x*10 to CV7 where 10 is cvFactor and 7 is addrCV
 * <li>Write N to CVyy
 * </ul>
 * <p>
 * This method is used by some Zimo decoders
 *
 * @see jmri.implementation.ProgrammerFacadeSelector
 *
 * @author Bob Jacobsen Copyright (C) 2013
 */
// /*public*/ class OffsetHighCvProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 * @param prog     the programmer to attach this facade to
 * @param top      CVs above this use the indirect method
 * @param addrCV   CV to which the high part of address is to be written
 * @param cvFactor CV to which the low part of address is to be written
 * @param modulo   Modulus for determining high/low address parts
 */
/*public*/ OffsetHighCvProgrammerFacade::OffsetHighCvProgrammerFacade(Programmer* prog, QString top, QString addrCV, QString cvFactor, QString modulo, QObject* parent) : AbstractProgrammerFacade(prog, parent)
{
    //super(prog);
 _usingProgrammer = NULL;
 state = ProgState::NOTPROGRAMMING;

    this->top = top.toInt();
    this->addrCV = addrCV;
    this->cvFactor = cvFactor.toInt();
    this->modulo = modulo.toInt();

}


//@Override
/*public*/ void OffsetHighCvProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    log->debug("start writeCV");
    _cv = CV.toInt();
    _val = val;
    useProgrammer(p);
    if (prog->getCanWrite(CV) || _cv <= top) {
        state = ProgState::PROGRAMMING;
        prog->writeCV(CV, val, (ProgListener*)this);
    } else {
        // write index first
        state = ProgState::FINISHWRITE;
        prog->writeCV(addrCV, (_cv / modulo) * cvFactor, (ProgListener*)this);
    }
}

//@Override
/*public*/ void OffsetHighCvProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
    log->debug("start readCV");
    useProgrammer(p);
    if (prog->getCanRead(CV) || _cv <= top) {
        state = ProgState::PROGRAMMING;
        prog->readCV(CV, (ProgListener*)this);
    } else {
        // write index first
        state = ProgState::FINISHREAD;
        prog->writeCV(addrCV, (_cv / modulo) * cvFactor, (ProgListener*)this);
    }
}


// internal method to remember who's using the programmer
/*protected*/ void OffsetHighCvProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        if (log->isInfoEnabled()) {
            log->info(tr("programmer already in use by ") + _usingProgrammer->self()->metaObject()->className());
        }
        throw ProgrammerException("programmer in use");
    } else {
        _usingProgrammer = p;
    }
}


// get notified of the final result
// Note this assumes that there's only one phase to the operation
//@Override
/*public*/ void OffsetHighCvProgrammerFacade::programmingOpReply(int value, int status) {
    if (log->isDebugEnabled()) {
        log->debug("notifyProgListenerEnd value " + QString::number(value) + " status " + QString::number(status));
    }

    if (status != ProgListener::OK ) {
        // pass abort up
        log->debug("Reset and pass abort up");
        ProgListener* temp = _usingProgrammer;
        _usingProgrammer = NULL; // done
        state = ProgState::NOTPROGRAMMING;
        //temp.programmingOpReply(value, status);
        connect(this, SIGNAL(on_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));
        emit on_programmingOpReply(value, status);
        disconnect(this, SIGNAL(on_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));

        return;
    }

    if (_usingProgrammer == NULL) {
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
            state = ProgState::NOTPROGRAMMING;
            //temp.programmingOpReply(value, status);
            connect(this, SIGNAL(on_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));
            emit on_programmingOpReply(value, status);
            disconnect(this, SIGNAL(on_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));
            break;
    }
        case FINISHREAD:
            try {
                state = ProgState::PROGRAMMING;
                prog->readCV(QString::number(_cv % modulo), (ProgListener*)this);
            } catch (ProgrammerException e) {
                log->error("Exception doing final read", e);
            }
            break;
        case FINISHWRITE:
            try {
                state = ProgState::PROGRAMMING;
                prog->writeCV(""+(_cv % modulo), _val, (ProgListener*)this);
            } catch (ProgrammerException e) {
                log->error("Exception doing final write", e);
            }
            break;
        default:
            log->error("Unexpected state on reply: " + state);
            // clean up as much as possible
            _usingProgrammer = NULL;
            state = ProgState::NOTPROGRAMMING;

    }

}

// Access to full address space provided by this.
//@Override
/*public*/ bool OffsetHighCvProgrammerFacade::getCanRead() {
    return true;
}

//@Override
/*public*/ bool OffsetHighCvProgrammerFacade::getCanRead(QString addr) {
    return addr.toInt() <= 1024;
}

//@Override
/*public*/ bool OffsetHighCvProgrammerFacade::getCanWrite() {
    return true;
}

//@Override
/*public*/ bool OffsetHighCvProgrammerFacade::getCanWrite(QString addr) {
    return addr.toInt() <= 1024;
}

/*private*/ /*final*/ /*static*/ Logger* OffsetHighCvProgrammerFacade::log = LoggerFactory::getLogger("OffsetHighCvProgrammerFacade");
