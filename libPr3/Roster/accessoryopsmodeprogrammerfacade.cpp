#include "accessoryopsmodeprogrammerfacade.h"
#include "addressedprogrammer.h"
#include "defaultprogrammermanager.h"
#include "commandstation.h"
#include "instancemanager.h"
#include "nmrapacket.h"
#include "sleeperthread.h"
#include "programmingmode.h"

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

/**
 * Programmer facade for access to Accessory Decoder Ops Mode programming.
 *
 * @param prog     The (possibly already decorated) programmer we are
 *                 piggybacking on.
 * @param addrType A string. "accessory" or "output" causes the address to
 *                 be interpreted as an 11 bit accessory output address.
 *                 "decoder" causes the address to be interpreted as a 9 bit
 *                 accessory decoder address "signal" causes the address to
 *                 be interpreted as an 11 bit signal decoder address.
 * @param delay    A string representing the desired delay between
 *                 programming operations, in milliseconds.
 * @param baseProg The underlying undecorated Ops Mode Programmer we are
 *                 piggybacking on.
 */
//@SuppressFBWarnings(value = "DM_CONVERT_CASE",
//        justification = "parameter value is never localised")  // NOI18N
/*public*/ AccessoryOpsModeProgrammerFacade::AccessoryOpsModeProgrammerFacade(Programmer* prog, /*@NonNULL */QString addrType, int delay, AddressedProgrammer* baseProg, QObject *parent)
 : AbstractProgrammerFacade(prog)
{
   // super(prog);
    log->debug("Constructing AccessoryOpsModeProgrammerFacade");
    this->_usingProgrammer = NULL;
    this->mode = prog->getMode();
    this->aprog = (AddressedProgrammer*)prog;
    this->_addrType = (addrType == NULL) ? "" : addrType.toLower(); // NOI18N
    this->_delay = delay;
    this->_baseProg = baseProg;
}
//@Override
/*public*/ QList<QString> AccessoryOpsModeProgrammerFacade::getSupportedModes() {
    QList<QString> ret =  QList<QString>();
    ret.append("OPSACCBYTEMODE");
    ret.append("OPSACCBITMODE");
    ret.append("OPSACCEXTBYTEMODE");
    ret.append("OPSACCEXTBITMODE");
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
/*synchronized*/ /*public*/ void AccessoryOpsModeProgrammerFacade::writeCV(QString cv, int val, ProgListener* p) throw (ProgrammerException)
{
 _val = val;
 useProgrammer(p);
 state = PROGRAMMING;
 QByteArray b;

 // Send DCC commands to implement prog.writeCV(cv, val, this);
 if (_addrType ==  "accessory" || _addrType == "output")
 {
         // interpret address as accessory address
         log->debug(tr("Send an accDecoderPktOpsMode: address=%1, cv=%2, value=%3").arg(
                 _baseProg->getAddressNumber()).arg((cv.toInt())).arg(val));
         b = NmraPacket::accDecoderPktOpsMode(_baseProg->getAddressNumber(), (cv.toInt()), val);
 }
 else if(_addrType ==  "signal")
 {
         // interpret address as signal address
         log->debug(tr("Send an accSignalDecoderPktOpsMode: address=%1, cv=%2, value=%3").arg(
                 _baseProg->getAddressNumber()).arg(cv.toInt()).arg(val));
         b = NmraPacket::accSignalDecoderPktOpsMode(_baseProg->getAddressNumber(), (cv.toInt()), val);
  }
  else if (_addrType == "altsignal")
  {
         // interpret address as signal address using the alternative interpretation of S-9.2.1
         log->debug(tr("Send an altAccSignalDecoderPktOpsMode: address=%1, cv=%2, value=%3").arg(
                 _baseProg->getAddressNumber()).arg(cv.toInt()).arg(val));
         b = NmraPacket::altAccSignalDecoderPktOpsMode(_baseProg->getAddressNumber(), cv.toInt(), val);
  }
  else if (_addrType == "decoder")
  {
         // interpet address as decoder address
         log->debug(tr("Send an accDecPktOpsMode: address=%1, cv=%2, value=%3").arg(
                 _baseProg->getAddressNumber()).arg(cv.toInt()).arg(val));
         b = NmraPacket::accDecPktOpsMode(_baseProg->getAddressNumber(), (cv.toInt()), val);
 }
 else if (_addrType == "legacy")
 {
         // interpet address as decoder address and send legacy packet
         log->debug(tr("Send an accDecPktOpsModeLegacy: address=%1, cv=%2, value=%3").arg(
                 _baseProg->getAddressNumber()).arg(cv.toInt()).arg(val));
         b = NmraPacket::accDecPktOpsModeLegacy(_baseProg->getAddressNumber(), cv.toInt(), val);
  }
 else
 {log->error(tr("Unknown Address Type \"%1\"").arg(_addrType));
         programmingOpReply(val, ProgListener::UnknownError);
         return;
 }
 ((CommandStation*)InstanceManager::getDefault("CommandStation"))->sendPacket(b, 2); // send two packets

 // set up a delayed completion reply
#if 0
 new Thread(new Runnable() {
     @Override
     public synchronized void run() {
         log.debug("delaying {} milliseconds for cv={}, value={}", _delay, Integer.parseInt(cv), val);
         if (_delay > 0) {
             try {
                 Thread.sleep(_delay);
             } catch (InterruptedException ie) {
                 log.error("Interrupted while sleeping {}", ie);
             }
         }
         log.debug("            delay elapsed for cv={}, value={}", Integer.parseInt(cv), val);
         programmingOpReply(val, ProgListener.OK);
     }
 }).start();
#else
 DelayWorker* worker = new DelayWorker(cv, val, this);
 QThread* thread = new QThread();
 connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
 connect(thread, SIGNAL(started()), worker, SLOT(process()));
 worker->moveToThread(thread );
 thread->start();

#endif
}

DelayWorker::DelayWorker(QString cv, int val, AccessoryOpsModeProgrammerFacade *facade) : QObject()
{
 this->facade = facade;
 this->cv = cv;
 this->val = val;
}

void DelayWorker::process()
{
 facade->log->debug(tr("delaying %1 milliseconds for cv=%2, value=%3").arg(facade->_delay).arg(cv).arg(val));
 if (facade->_delay > 0) {
     try {
         //Thread.sleep(_delay);
   SleeperThread::msleep(facade->_delay);
     } catch (InterruptedException ie) {
         facade->log->error(tr("Interrupted while sleeping %1").arg(ie.getMessage()));
     }
 }
 facade->log->debug(tr("            delay elapsed for cv=%1, value=%2").arg(cv).arg(val));
 facade->programmingOpReply(val, ProgListener::OK);
 emit finished();
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
        if (log->isInfoEnabled()) log->info("programmer already in use by "+QString(_usingProgrammer->self()->metaObject()->className()));
        throw ProgrammerException("programmer in use");
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

