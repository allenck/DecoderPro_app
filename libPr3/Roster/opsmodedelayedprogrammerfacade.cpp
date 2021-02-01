#include "opsmodedelayedprogrammerfacade.h"
#include "loggerfactory.h"
#include "sleeperthread.h"
#include <QThread>

/**
 * Programmer facade for access to Accessory Decoder Ops Mode programming
 * <p>
 * (Eventually implements four modes, passing all others to underlying
 * programmer:
 * <ul>
 * <li>OPSACCBYTEMODE
 * <li>OPSACCBITMODE
 * <li>OPSACCEXTBYTEMODE
 * <li>OPSACCEXTBITMODE
 * </ul>
 * <P>
 * Used through the String write/read/confirm interface. Accepts integers as
 * addresses, but then emits NMRA DCC packets through the default CommandStation
 * interface (which must be present)
 *
 * @see jmri.implementation.ProgrammerFacadeSelector
 *
 * @author Bob Jacobsen Copyright (C) 2014
 */
// @ToDo("transform to annotations requires e.g. http://alchemy.grimoire.ca/m2/sites/ca.grimoire/todo-annotations/")
// @ToDo("read handling needs to be aligned with other ops mode programmers")
// @ToDo("make sure jmri/jmrit/progsupport/ProgServiceModePane shows the modes, and that DP/DP3 displays them as it configures a decoder")
///*public*/ class OpsModeDelayedProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 * Programmer facade for access to Accessory Decoder Ops Mode programming.
 *
 * @param prog       The Ops Mode Programmer we are piggybacking on.
 * @param writeDelay A string representing the desired delay after a write
 *                   operation, in milliseconds.
 */
/*public*/ OpsModeDelayedProgrammerFacade::OpsModeDelayedProgrammerFacade(Programmer* prog, int writeDelay, QObject* parent) : AbstractProgrammerFacade(prog, parent)
{
    //super(prog);
    log->debug("Constructing OpsModeDelayedProgrammerFacade");
    this->_usingProgrammer = NULL;
    this->prog = prog;
    this->_readDelay = 0;
    this->_writeDelay = writeDelay;
    state = ProgState::NOTPROGRAMMING;
}


// programming interface
//@Override
/*public*/ /*synchronized*/ void OpsModeDelayedProgrammerFacade::writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException) {
    log->debug(tr("writeCV entry: ProgListener p is %1").arg(p->self()->metaObject()->className()));
    useProgrammer(p);
    state = ProgState::WRITECOMMANDSENT;
    prog->writeCV(cv, val, (ProgListener*)this);
}

//@Override
/*public*/ /*synchronized*/ void OpsModeDelayedProgrammerFacade::readCV(QString cv, ProgListener* p) throw (ProgrammerException) {
    useProgrammer(p);
    state = ProgState::READCOMMANDSENT;
    prog->readCV(cv, (ProgListener*)this);
}

//@Override
/*public*/ /*synchronized*/ void OpsModeDelayedProgrammerFacade::confirmCV(QString cv, int val, ProgListener* p) throw (ProgrammerException) {
    useProgrammer(p);
    state = ProgState::READCOMMANDSENT;
    prog->confirmCV(cv, val, (ProgListener*)this);
}


/**
 * Internal method to remember who's using the programmer.
 *
 *
 * @param p the programmer
 * @throws ProgrammerException if p is already in use
 */
/*protected*/ /*synchronized*/ void OpsModeDelayedProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if(_usingProgrammer)
     log->debug(tr("useProgrammer entry: _usingProgrammer is %1").arg(_usingProgrammer->self()->metaObject()->className()));
    if (_usingProgrammer != NULL && _usingProgrammer != p)
    {
        if (log->isInfoEnabled()) {
            log->info(tr("programmer already in use by ") + _usingProgrammer->self()->metaObject()->className());
        }
        throw ProgrammerException("programmer in use");
    } else
    {
        _usingProgrammer = p;
    }
    log->debug(tr("useProgrammer exit: _usingProgrammer is %1").arg(_usingProgrammer->self()->metaObject()->className()));
}


// get notified of the final result
// Note this assumes that there's only one phase to the operation
//@Override
/*public*/ /*synchronized*/ void OpsModeDelayedProgrammerFacade::programmingOpReply(int value, int status) {
    log->debug(tr("notifyProgListenerEnd value=%1, status=%2").arg(value).arg(status));

    if (status != ProgListener::OK) {
        // pass abort up
        log->debug("Reset and pass abort up");
        ProgListener* temp = _usingProgrammer;
        _usingProgrammer = NULL; // done
        state = ProgState::NOTPROGRAMMING;
        temp->programmingOpReply(value, status);
        return;
    }

    if (_usingProgrammer == NULL) {
        log->error("No listener to notify, reset and ignore");
        state = ProgState::NOTPROGRAMMING;
        return;
    }

    switch (state) {
        case READCOMMANDSENT:
            _delay = _readDelay;
            break;
        case WRITECOMMANDSENT:
            _delay = _writeDelay;
            break;
        default:
            log->error("Unexpected state on reply: " + QString::number(state));
            // clean up as much as possible
            _usingProgrammer = NULL;
            state = ProgState::NOTPROGRAMMING;
    }
#if 0
    new Thread(new Runnable() {
        @Override
        /*public*/ synchronized void run() {
            if (_delay > 0) {
                log.debug("delaying {} milliseconds", _delay);
                try {
                    Thread.sleep(_delay);
                } catch (InterruptedException ie) {
                    log.error("Interrupted while sleeping {}", ie);
                }
            }
            // the programmingOpReply handler might send an immediate reply, so
            // clear the current listener _first_
            log.debug("going NOTPROGRAMMING after value {}, status={}", value, status);
            jmri.ProgListener temp = _usingProgrammer;
            _usingProgrammer = null; // done
            state = ProgState.NOTPROGRAMMING;
            log.debug("notifying value " + value + " status " + status);
            temp.programmingOpReply(value, status);
        }
    }).start();
#else
    OPSMDelayWorker* worker = new OPSMDelayWorker(value, status, this);
    QThread* thread = new QThread();
    connect(thread, SIGNAL(started()), worker, SLOT(process()));
    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    worker->moveToThread(thread);
    thread->start();
#endif
}

OPSMDelayWorker::OPSMDelayWorker(int value, int status, OpsModeDelayedProgrammerFacade *facade)
{
 this->facade = facade;
 this->value = value;
 this->status = status;
}

void OPSMDelayWorker::process()
{
 if (facade->_delay > 0) {
     facade->log->debug(tr("delaying %1 milliseconds").arg(facade->_delay));
     try {
         //Thread.sleep(_delay);
      SleeperThread::msleep(facade->_delay);
     } catch (InterruptedException ie) {
         facade->log->error(tr("Interrupted while sleeping %1").arg(ie.getMessage()));
     }
 }
 // the programmingOpReply handler might send an immediate reply, so
 // clear the current listener _first_
 facade->log->debug(tr("going NOTPROGRAMMING after value %1, status=%2").arg(value).arg(status));
 ProgListener* temp = facade->_usingProgrammer;
 facade->_usingProgrammer = NULL; // done
 facade->state =  OpsModeDelayedProgrammerFacade::ProgState::NOTPROGRAMMING;
 facade->log->debug("notifying value " + QString(value) + " status " + QString::number(status));
 temp->programmingOpReply(value, status);
 emit finished();
}

/*private*/ /*final*/ /*static*/ Logger* OpsModeDelayedProgrammerFacade::log = LoggerFactory::getLogger("OpsModeDelayedProgrammerFacade");
