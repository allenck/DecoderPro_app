#include "accessoryopsmodeprogrammerfacade.h"
#include "addressedprogrammer.h"
#include "defaultprogrammermanager.h"
#include "commandstation.h"
#include "instancemanager.h"
#include "nmrapacket.h"

//AccessoryOpsModeProgrammerFacade::AccessoryOpsModeProgrammerFacade(QObject *parent) :
//    AbstractProgrammerFacade(parent)
//{
//}
/**
 * Programmer facade for access to Accessory Decoder Ops Mode programming
 * <p>
 * (Eventually implements four modes, passing all others to underlying programmer:
 * <ul>
 * <li>OPSACCBYTEMODE
 * <li>OPSACCBITMODE
 * <li>OPSACCEXTBYTEMODE
 * <li>OPSACCEXTBITMODE
 * </ul>
 * <P>
 * Used through the String write/read/confirm interface.  Accepts integers
 * as addresses, but then emits NMRA DCC packets through the
 * default CommandStation interface (which must be present)
 *
 * @see implementation.ProgrammerFacadeSelector
 *
 * @author      Bob Jacobsen  Copyright (C) 2014
 */
// @ToDo("transform to annotations requires e.g. http://alchemy.grimoire.ca/m2/sites/ca.grimoire/todo-annotations/")
// @ToDo("get address from underlyng programmer (which might require adding a new subclass structure to Programmer)")
// @ToDo("finish mode handling; what gets passed through?")
// @ToDo("write almost certainly needs a delay")
// @ToDo("read handling needs to be aligned with other ops mode programmers")
// @ToDo("make sure jmri/jmrit/progsupport/ProgServiceModePane shows the modes, and that DP/DP3 displays them as it configures a decoder")

// /*public*/ class AccessoryOpsModeProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/*public*/ AccessoryOpsModeProgrammerFacade::AccessoryOpsModeProgrammerFacade(AddressedProgrammer* prog, QObject* parent)
    : AbstractProgrammerFacade(prog, parent)
{
 //super(prog);
 this->mode = prog->getMode();
 this->prog = prog;
 _usingProgrammer = NULL;
 state = NOTPROGRAMMING;
}

//@Override
/*public*/ QList<ProgrammingMode*> AccessoryOpsModeProgrammerFacade::getSupportedModes() {
    QList<ProgrammingMode*> ret =  QList<ProgrammingMode*>();
    ret.append(DefaultProgrammerManager::OPSACCBYTEMODE);
    ret.append(DefaultProgrammerManager::OPSACCBITMODE);
    ret.append(DefaultProgrammerManager::OPSACCEXTBYTEMODE);
    ret.append(DefaultProgrammerManager::OPSACCEXTBITMODE);
    return ret;
}

/**
 * Don't pass this mode through, as the underlying doesn't have it (although we should check)
 */
/*public*/ void AccessoryOpsModeProgrammerFacade::setMode(ProgrammingMode* p) {}


/*public*/ bool AccessoryOpsModeProgrammerFacade::getCanRead() { return prog->getCanRead(); }
/*public*/ bool AccessoryOpsModeProgrammerFacade::getCanRead(QString addr) { return prog->getCanRead(addr); }

/*public*/ bool AccessoryOpsModeProgrammerFacade::getCanWrite()  { return prog->getCanWrite(); }
/*public*/ bool AccessoryOpsModeProgrammerFacade::getCanWrite(QString addr) { return prog->getCanWrite(addr); }




// programming interface
/*synchronized*/ /*public*/ void AccessoryOpsModeProgrammerFacade::writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException) {
    _val = val;
    useProgrammer(p);
    state = PROGRAMMING;

    // send DCC command to implement prog.writeCV(cv, val, (ProgListener*)this);
    QByteArray b = NmraPacket::accDecoderPktOpsMode(aprog->getAddressNumber(), cv.toInt(), val);
    ((CommandStation*)InstanceManager::getDefault("CommandStation"))->sendPacket(b,1);

    // and reply done
    p->programmingOpReply(val, ProgListener::OK);
}

/*synchronized*/ /*public*/ void AccessoryOpsModeProgrammerFacade::confirmCV(QString cv, int val, ProgListener* p) throw (ProgrammerException) {
    readCV(cv, p);
}

/*synchronized*/ /*public*/ void AccessoryOpsModeProgrammerFacade::readCV(QString cv, ProgListener* p) throw (ProgrammerException) {
    useProgrammer(p);
    state = PROGRAMMING;
    prog->readCV(cv, (ProgListener*)this);
}


// internal method to remember who's using the programmer
/*protected*/ void AccessoryOpsModeProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        if (log->isInfoEnabled()) log->info("programmer already in use by "+QString(_usingProgrammer->metaObject()->className()));
        throw new ProgrammerException("programmer in use");
    }
    else {
        _usingProgrammer = p;
        return;
    }
}


// get notified of the final result
// Note this assumes that there's only one phase to the operation
/*public*/ void AccessoryOpsModeProgrammerFacade::programmingOpReply(int value, int status) {
    if (log->isDebugEnabled()) log->debug("notifyProgListenerEnd value "+QString::number(value)+" status "+QString::number(status));

    if (_usingProgrammer == NULL) log->error("No listener to notify");

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
        default:
    {
            log->error("Unexpected state on reply: "+QString::number(state));
            // clean up as much as possible
            _usingProgrammer = NULL;
            state = NOTPROGRAMMING;
  }
 }
}

