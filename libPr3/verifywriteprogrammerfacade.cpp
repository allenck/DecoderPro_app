#include "verifywriteprogrammerfacade.h"
#include "loggerfactory.h"


///*public*/ class VerifyWriteProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 * @param prog    the programmer to which this facade is attached
 */
/*public*/VerifyWriteProgrammerFacade:: VerifyWriteProgrammerFacade(Programmer* prog, QObject* parent) : AbstractProgrammerFacade(prog, parent)                                                                                                                      {
    //super(prog);
 _usingProgrammer = NULL;
 state = ProgState::NOTPROGRAMMING;
 temp = _usingProgrammer;

}


// programming interface
//@Override
/*synchronized*/ /*public*/ void VerifyWriteProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    _val = val;
    _cv = CV;
    useProgrammer(p);

    // write value first
    state = ProgState::FINISHWRITE;
    prog->writeCV(CV, val, (ProgListener*)this);
}

//@Override
/*synchronized*/ /*public*/ void VerifyWriteProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
    _cv = CV;
    useProgrammer(p);

    state = ProgState::READING;
    prog->readCV(CV, (ProgListener*)this);
}

/**
 * This facade ensures that {@link Programmer.WriteConfirmMode#ReadAfterWrite}
 * is done, so long as it has permission to read the CV after writing.
 */
//@Override
//@Nonnull
/*public*/ Programmer::WriteConfirmMode VerifyWriteProgrammerFacade::getWriteConfirmMode(QString addr) {
    if ( prog->getCanRead(addr) ) {
        return WriteConfirmMode::ReadAfterWrite;
    } else {
         return prog->getWriteConfirmMode(addr);
    }
}


// internal method to remember who's using the programmer
/*protected*/ void VerifyWriteProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        log->info(tr("programmer already in use by %1").arg(_usingProgrammer->self()->metaObject()->className()));
        throw ProgrammerException("programmer in use");
    } else {
        _usingProgrammer = p;
    }
}

/**

// Get notified of the result from the underlying programmer, and work
// through the state machine for needed requests
//@Override
/*public*/ void VerifyWriteProgrammerFacade::programmingOpReply(int value, int status) {
    log->debug(tr("notifyProgListenerEnd value %1 status %2 ").arg(value).arg(status));

    if (status != ProgListener::OK ) {
        // pass abort up
        ProgListener* temp = _usingProgrammer;
        _usingProgrammer = NULL; // done
        state = ProgState::NOTPROGRAMMING;
//        connect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
//        //temp->programmingOpReply(value, status);
//        emit do_programmingOpReply(value, status);
//        disconnect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
        if(!QMetaObject::invokeMethod(temp->self(), "programmingOpReply", Qt::AutoConnection, Q_ARG(int, value), Q_ARG(int, status)))
        {
            log->error(tr("invoke method 'programmingOpReply' failed for %1").arg(temp->self()->metaObject()->className()));
            return;
        }

        return;
    }

    if (_usingProgrammer == NULL) {
        log->error("No listener to notify, reset and ignore");
        state = ProgState::NOTPROGRAMMING;
        return;
    }

    ProgListener* temp = _usingProgrammer;

    switch (state) {
        case FINISHWRITE:
            // write completed, can we do read, and is it not already being done?
            if (prog->getCanRead(_cv) && ! prog->getWriteConfirmMode(_cv) == (WriteConfirmMode::ReadAfterWrite) ) {
                state = ProgState::FINISHREAD;
                try {
                    prog->readCV(_cv, (ProgListener*)this);
                } catch (ProgrammerException e) {
                    // pass abort up
                    _usingProgrammer = NULL; // done
                    state = ProgState::NOTPROGRAMMING;
                    //temp->programmingOpReply(value, ProgListener::ConfirmFailed);
//                connect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
//                //temp->programmingOpReply(value, status);
//                emit do_programmingOpReply(value, status);
//                disconnect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
                    if(!QMetaObject::invokeMethod(temp->self(), "programmingOpReply", Qt::AutoConnection, Q_ARG(int, value), Q_ARG(int, status)))
                    {
                        log->error(tr("invoke method 'programmingOpReply' failed for %1").arg(temp->self()->metaObject()->className()));
                        return;
                    }
                    return;
                }
                break;
            }
            // can't read or it's already being done
            // deliberately fall through to normal completion
            //$FALL-THROUGH$
        case READING: // done, forward the return code and data
            // the programmingOpReply handler might send an immediate reply, so
            // clear the current listener _first_
            _usingProgrammer = NULL; // done
            state = ProgState::NOTPROGRAMMING;
//            connect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
//            //temp->programmingOpReply(value, status);
//            emit do_programmingOpReply(value, status);
//            disconnect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
            if(!QMetaObject::invokeMethod(temp->self(), "programmingOpReply", Qt::AutoConnection, Q_ARG(int, value), Q_ARG(int, status)))
            {
                log->error(tr("invoke method 'programmingOpReply' failed for %1").arg(temp->self()->metaObject()->className()));
                return;
            }
            break;

        case FINISHREAD:
            _usingProgrammer = NULL; // done
            state = ProgState::NOTPROGRAMMING;
            // check if we got it right
            if (value == _val) {
                // ok, reply OK
                //temp.programmingOpReply(value, status);
//                connect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
//                //temp->programmingOpReply(value, status);
//                emit do_programmingOpReply(value, status);
//                disconnect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
             if(!QMetaObject::invokeMethod(temp->self(), "programmingOpReply", Qt::AutoConnection, Q_ARG(int, value), Q_ARG(int, status)))
             {
                 log->error(tr("invoke method 'programmingOpReply' failed for %1").arg(temp->self()->metaObject()->className()));
                 return;
             }
            } else {
                // error, reply error
                //temp.programmingOpReply(value, ProgListener.ConfirmFailed);
//                connect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
//                //temp->programmingOpReply(value, status);
//                emit do_programmingOpReply(value, status);
//                disconnect(this, SIGNAL(do_programmingOpReply(int,int)), temp, SLOT(programmingOpReply(int,int)));
             if(!QMetaObject::invokeMethod(temp->self(), "programmingOpReply", Qt::AutoConnection, Q_ARG(int, value), Q_ARG(int, status)))
             {
                 log->error(tr("invoke method 'programmingOpReply' failed for %1").arg(temp->self()->metaObject()->className()));
                 return;
             }
            }
            break;

        default:
            log->error("Unexpected state on reply: " + state);
            // clean up as much as possible
            _usingProgrammer = NULL;
            state = ProgState::NOTPROGRAMMING;
            break;
    }
}

/*private*/ /*final*/ /*static*/ Logger* VerifyWriteProgrammerFacade::log = LoggerFactory::getLogger("VerifyWriteProgrammerFacade");
