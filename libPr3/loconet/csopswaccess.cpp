#include "csopswaccess.h"
#include "loggerfactory.h"
/**
 *
 * @author given
 */
///*public*/ class CsOpSwAccess implements LocoNetListener {


/*public*/ CsOpSwAccess::CsOpSwAccess(/*@NonNULL*/ LocoNetSystemConnectionMemo* memo, /*@NonNULL */ProgListener* p, QObject* parent) {
    this->memo = memo;
    this->p = p;
    // listen to the LocoNet
#if 0
    memo->getLnTrafficController()->addLocoNetListener(~0, this);
    csOpSwAccessTimer = NULL;
    csOpSwValidTimer = NULL;
    cmdStnOpSwState = CmdStnOpSwStateType::IDLE;
    opSwBytes = new int[] {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#endif
    haveValidLowBytes = false;
    haveValidHighBytes = false;
    log->debug("csOpSwAccess constructor");

}

/*public*/ void CsOpSwAccess::setProgrammerListener(/*@NonNULL*/ ProgListener* p) {
    this->p = p;
}

/*public*/ void CsOpSwAccess::readCsOpSw(QString opSw, /*@NonNULL*/ ProgListener* pL) throw (ProgrammerException) {
    log->debug(tr("reading a cs opsw : %1").arg(opSw));
    // Note: Only get here if decoder xml specifies LocoNetCsOpSwMode.

    if (csOpSwAccessTimer == NULL) {
        log->debug("initializing timers");
        initializeCsOpSwAccessTimer();
        initializeCsOpSwValidTimer();
    }

    p = pL;
    doingWrite = false;
    log->debug(tr("read Command Station OpSw%1").arg(opSw));

    QStringList parts;
    parts = opSw.split("\\.");
    ProgListener* temp = pL;
    if ((parts.length() == 2) &&
           (parts.at(0)==("csOpSw")) &&
            (((parts.at(1).toInt())) >= 1) &&
            ((parts.at(1).toInt()) <= 128)) {
        log->trace(tr("splitting CV: %1 becomes %2 and %3").arg(opSw).arg(parts[0]).arg(parts[1]));
        // a valid command station OpSw identifier was found
        log->trace(tr("Valid typeWord = 1; attempting to read OpSw%1.").arg( (parts[1])));
        log->trace(tr("starting from state %1").arg((int)cmdStnOpSwState));
        readCmdStationOpSw((parts[1].toInt()));
        return;
    } else {
        log->warn(tr("Cannot perform Cs OpSw access: parts.length=%1, parts[]=%2").arg(parts.length()).arg(/*parts*/opSw));
        p = NULL;
        if (temp != NULL) {
            temp->programmingOpReply(0,ProgListener::NotImplemented);
        }
        return;
    }
}
#if 0
/*public*/ void writeCsOpSw(String opSw, int val, @NonNULL ProgListener pL) throws ProgrammerException {
    p = NULL;
    String[] parts = opSw.split("\\.");
    if (((val != 0) && (val != 1)) ||
            (parts.length != 2) ||
            (!parts[0].equals("csOpSw")) ||
            (Integer.parseInt(parts[1]) <= 0) ||
            (Integer.parseInt(parts[1]) >= 129)) {
        // invalid request - signal it to the programmer
        log->warn("Cannot perform Cs OpSw access: parts.length={}, parts[]={}, val={}",parts.length, parts, val);
        if (pL != NULL) {
            pL.programmingOpReply(0,ProgListener.NotImplemented);
        }
        return;
    }

    if (csOpSwAccessTimer == NULL) {
        initializeCsOpSwAccessTimer();
        initializeCsOpSwValidTimer();
    }

    // Command Station OpSws are handled via slot 0x7f.
    p = pL;
    doingWrite = true;
    log->debug("write Command Station OpSw{} as {}", opSw, (val>0)?"c":"t");
    int opSwNum = Integer.parseInt(parts[1]);
    log->debug("CS OpSw number {}", opSwNum);
    if (!updateCmdStnOpSw(opSwNum,
            (val==1))) {
        sendFinalProgrammerReply(-1, ProgListener.ProgrammerBusy);
    }
}

@Override
/*public*/ void message(LocoNetMessage m) {
    if (cmdStnOpSwState == CmdStnOpSwStateType.IDLE) {
        return;
    }
    boolean value;
    if ((m.getOpCode() == LnConstants.OPC_SL_RD_DATA) &&
            (m.getElement(1) == 0x0E) &&
            ((m.getElement(2) & 0x7E) == 0x7E) &&
            ((cmdStnOpSwState == CmdStnOpSwStateType.QUERY) ||
            ((cmdStnOpSwState == CmdStnOpSwStateType.QUERY_ENHANCED)))) {
        log->debug("got slot {} read data", m.getElement(2));
        updateStoredOpSwsFromRead(m);
        if ((cmdStnOpSwState == CmdStnOpSwStateType.QUERY) ||
                (cmdStnOpSwState == CmdStnOpSwStateType.QUERY_ENHANCED)) {
            log->debug("got slot {} read data in response to OpSw query", m.getElement(2));
            if (((m.getElement(7) & 0x40) == 0x40) &&
                    (cmdStnOpSwState == CmdStnOpSwStateType.QUERY)){
                // attempt to get extended OpSw info
                csOpSwAccessTimer.restart();
                LocoNetMessage m2 = new LocoNetMessage(new int[] {0xbb, 0x7e, 0x00, 0x00});
                cmdStnOpSwState = CmdStnOpSwStateType.QUERY_ENHANCED;
                memo.getLnTrafficController().sendLocoNetMessage(m2);
                csOpSwAccessTimer.start();
                return;
            }
            csOpSwAccessTimer.stop();
            cmdStnOpSwState = CmdStnOpSwStateType.HAS_STATE;
            log->debug("starting valid timer");
            csOpSwValidTimer.start();   // start the "valid data" timer
            if (doingWrite == true) {
                log->debug("now can finish the write by updating the correct bit...");
                finishTheWrite();
            } else {
                if (!(((cmdStnOpSwNum > 0) && (cmdStnOpSwNum < 65) && (haveValidLowBytes)) ||
                        ((cmdStnOpSwNum > 64) && (cmdStnOpSwNum < 129) && (haveValidHighBytes)))) {
                    ProgListener temp = p;
                    p = NULL;
                    if (temp != NULL) {
                        log->debug("Aborting - OpSw {} beyond allowed range", cmdStnOpSwNum);
                        temp.programmingOpReply(0, ProgListener.NotImplemented);
                    } else {
                        log->warn("no programmer to which the error condition can be returned.");
                    }
                } else {
                    value = extractCmdStnOpSw(cmdStnOpSwNum);
                    log->debug("now can return the extracted OpSw{} read data ({}) to the programmer", cmdStnOpSwNum, value);
                    sendFinalProgrammerReply(value?1:0, ProgListener.OK);
                }
            }
        } else if ((cmdStnOpSwState == CmdStnOpSwStateType.QUERY_BEFORE_WRITE) ||
                (cmdStnOpSwState == CmdStnOpSwStateType.QUERY_ENHANCED_BEFORE_WRITE)){
            if (((m.getElement(7) & 0x40) == 0x40) &&
                    (cmdStnOpSwState == CmdStnOpSwStateType.QUERY_BEFORE_WRITE)) {
                csOpSwAccessTimer.restart();
                LocoNetMessage m2 = new LocoNetMessage(new int[] {0xbb, 0x7e, 0x00, 0x00});
                cmdStnOpSwState = CmdStnOpSwStateType.QUERY_ENHANCED_BEFORE_WRITE;
                memo.getLnTrafficController().sendLocoNetMessage(m2);
                csOpSwAccessTimer.start();
                return;
            }
            log->debug("have received OpSw query before a write; now can process the data modification");
            csOpSwAccessTimer.stop();
            cmdStnOpSwState = CmdStnOpSwStateType.WRITE;
            LocoNetMessage m2 = updateOpSwVal(cmdStnOpSwNum, cmdStnOpSwVal);
            log->debug("performing enhanced opsw write: {}",m2.toString());
            log->debug("todo; uncomment the send?");
            //memo.getLnTrafficController().sendLocoNetMessage(m2);
            csOpSwAccessTimer.start();
        }
    } else if ((m.getOpCode() == LnConstants.OPC_LONG_ACK) &&
            (m.getElement(1) == 0x6f) &&
            (m.getElement(2) == 0x7f) &&
            (cmdStnOpSwState == CmdStnOpSwStateType.WRITE)) {
        csOpSwAccessTimer.stop();
        cmdStnOpSwState = CmdStnOpSwStateType.HAS_STATE;
        value = extractCmdStnOpSw(cmdStnOpSwNum);
        sendFinalProgrammerReply(value?1:0,ProgListener.OK);
    }
}
#endif
/*public*/ void CsOpSwAccess::readCmdStationOpSw(int cv) {
    log->debug(tr("readCmdStationOpSw: state is %1, have lowvalid %2, have highvalid %3, asking for OpSw%4").arg(
            cmdStnOpSwState).arg( haveValidLowBytes?"true":"false").arg(
            haveValidHighBytes?"true":"false").arg(cv));
    if (cmdStnOpSwState == CmdStnOpSwStateType::HAS_STATE) {
        if ((((cv > 0) && (cv < 65) && haveValidLowBytes)) ||
            (((cv > 64) && (cv < 129) && haveValidHighBytes))) {
            // can re-use previous state - it has not "expired" due to time since read.
        log->debug(tr("readCmdStationOpSw: returning state from previously-stored state for OpSw%1").arg(cv));
            returnCmdStationOpSwVal(cv);
        } else {
            log->warn(tr("Cannot perform Cs OpSw access of OpSw %1 account out-of-range for this command station.").arg(cv));
            sendFinalProgrammerReply(-1,ProgListener::NotImplemented);
        }
    } else if ((cmdStnOpSwState == CmdStnOpSwStateType::IDLE) ||
            (cmdStnOpSwState == CmdStnOpSwStateType::HAS_STATE)) {
        // do not have valid data or old data has "expired" due to time since read.
        // Need to send a slot 127 (and 126, as appropriate) read to LocoNet
        log->debug("readCmdStationOpSw: attempting to read some CVs");
        updateCmdStnOpSw(cv,false);
    } else {
        log->warn(tr("readCmdStationOpSw: aborting - cmdStnOpSwState is odd: %1").arg( cmdStnOpSwState));
        sendFinalProgrammerReply(-1,ProgListener::UnknownError);
    }
}

/*public*/ void CsOpSwAccess::returnCmdStationOpSwVal(int cmdStnOpSwNum) {
    bool returnVal = extractCmdStnOpSw(cmdStnOpSwNum);
    if (p != NULL) {
        // extractCmdStnOpSw did not find an erroneous condition
        log->debug(tr("returnCmdStationOpSwVal: Returning OpSw%1 value of %2").arg(cmdStnOpSwNum).arg(returnVal));
        p->programmingOpReply(returnVal?1:0, ProgListener::OK);
    }
}

/*public*/ bool CsOpSwAccess::updateCmdStnOpSw(int opSwNum, bool val) {
    if (cmdStnOpSwState == CmdStnOpSwStateType::HAS_STATE) {
        if (!doingWrite) {
            log->debug("updateCmdStnOpSw: should already have OpSw values from previous read.");
            return false;
        } else {
            cmdStnOpSwVal = val;
            cmdStnOpSwNum = opSwNum;
            finishTheWrite();
            return true;
        }
    }
    if (cmdStnOpSwState != CmdStnOpSwStateType::IDLE)  {
        log->debug(tr("updateCmdStnOpSw: cannot query OpSw values from state %1").arg( cmdStnOpSwState));
        return false;
    }
    log->debug(tr("updateCmdStnOpSw: attempting to query the OpSws when state = %1").arg( cmdStnOpSwState));
    cmdStnOpSwState = CmdStnOpSwStateType::QUERY;
    cmdStnOpSwNum = opSwNum;
    cmdStnOpSwVal = val;
    QList<int> contents = QList<int>() <<LnConstants::OPC_RQ_SL_DATA<<0x7F<<0x0<<0x0;
    memo->getLnTrafficController()->sendLocoNetMessage(new LocoNetMessage(contents.toVector()));
    csOpSwAccessTimer->start();

    return true;
}

/*public*/ bool CsOpSwAccess::extractCmdStnOpSw(int cmdStnOpSwNum) {

    if (((cmdStnOpSwNum > 0) && (cmdStnOpSwNum < 65) && (haveValidLowBytes)) ||
            ((cmdStnOpSwNum > 64) && (cmdStnOpSwNum < 129) && (haveValidHighBytes))){

        log->debug(tr("attempting to extract value for OpSw %1 with haveValidLowBytes %2 and haveValidHighBytes %3").arg(
                cmdStnOpSwNum).arg(haveValidLowBytes).arg(haveValidHighBytes));
        int msgByte = (cmdStnOpSwNum-1) /8;
        int bitpos = (cmdStnOpSwNum-1)-(8*msgByte);
        bool retval = (((opSwBytes[msgByte] >> bitpos) & 1) == 1);
        log->debug(tr("extractCmdStnOpSw: opsw%1 from bit %2 of opSwByte[%3]=%4 gives %5").arg( cmdStnOpSwNum).arg(bitpos).arg(msgByte).arg(opSwBytes[msgByte]).arg(retval));
        return retval;
    } else {
        log->debug(tr("failing extract account problem with cmdStnOpSwNum=%1, haveValidLowBytes %2 and haveValidHighBytes %3").arg(
            cmdStnOpSwNum).arg(haveValidLowBytes).arg(haveValidHighBytes));
        csOpSwAccessTimer->stop();
        csOpSwValidTimer->stop();
        sendFinalProgrammerReply(-1,ProgListener::UnknownError);
        return false;
    }
}

/*public*/ LocoNetMessage* CsOpSwAccess::updateOpSwVal(int cmdStnOpSwNum, bool cmdStnOpSwVal) {
#if 0
    if (((cmdStnOpSwNum -1) & 0x07) == 7) {
        log->warn("Cannot program OpSw{} account LocoNet encoding limitations.",cmdStnOpSwNum);
        sendFinalProgrammerReply(-1,ProgListener.UnknownError);
        return new LocoNetMessage(new int[] {LnConstants.OPC_GPBUSY, 0x0});
    } else if ((cmdStnOpSwNum < 1) || (cmdStnOpSwNum > 128))  {
        log->warn("Cannot program OpSw{} account OpSw number out of range.",cmdStnOpSwNum);
        sendFinalProgrammerReply(-1, ProgListener.NotImplemented);
        return new LocoNetMessage(new int[] {LnConstants.OPC_GPBUSY, 0x0});
    }

    log->debug("updateOpSwVal: OpSw{} = {}", cmdStnOpSwNum, cmdStnOpSwVal);
    changeOpSwBytes(cmdStnOpSwNum, cmdStnOpSwVal);
    LocoNetMessage m = new LocoNetMessage(14);
    m.setOpCode(0xEF);
    m.setElement(1, 0x0e);
    m.setElement(2, (cmdStnOpSwNum >= 65)?0x7E:0x7F);

    m.setElement(3, opSwBytes[0+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(4, opSwBytes[1+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(5, opSwBytes[2+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(6, opSwBytes[3+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(7, 0);
    m.setElement(8, opSwBytes[4+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(9, opSwBytes[5+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(10, opSwBytes[6+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(11, opSwBytes[7+(8*(cmdStnOpSwNum>64?1:0))]);
    m.setElement(12, 0);
    m.setElement(13, 0);
    return m;
#endif
}

/*private*/ void CsOpSwAccess::finishTheWrite() {
    cmdStnOpSwState = CmdStnOpSwStateType::WRITE;
    LocoNetMessage* m2 = updateOpSwVal(cmdStnOpSwNum,
            cmdStnOpSwVal);
    if (m2->getNumDataElements() == 2) {
        // failure - no message provided - must be out-of-range opsw number
        sendFinalProgrammerReply(-1, ProgListener::UnknownError);
        return;
    }

    m2->setOpCode(LnConstants::OPC_WR_SL_DATA);
    log->debug(tr("finish the write sending LocoNet cmd stn opsw write message %1, length=%2").arg( m2->toString()).arg(m2->getNumDataElements()));
    memo->getLnTrafficController()->sendLocoNetMessage(m2);
    csOpSwAccessTimer->start();
}

/*private*/ void CsOpSwAccess::sendFinalProgrammerReply(int val, int response) {
    log->debug(tr("returning response %1 with value %2 to programmer").arg(response).arg(val));
        ProgListener* temp = p;
        p = NULL;
        if (temp != NULL) {
            temp->programmingOpReply(val, response);
        }

}

void CsOpSwAccess::initializeCsOpSwAccessTimer() {
    if (csOpSwAccessTimer == NULL) {
//        csOpSwAccessTimer = new Timer(500, (ActionEvent e) -> {
//            log->debug("csOpSwAccessTimer timed out!");
//            ProgListener temp = p;
//            p = NULL;
//            if (temp != NULL) {
//                temp.programmingOpReply(0, ProgListener.FailedTimeout);
//            }
//        });
    csOpSwAccessTimer= new QTimer();
    csOpSwAccessTimer->setSingleShot(true);
    csOpSwAccessTimer->setInterval(500);
    csOpSwAccessTimer->start(500);
    connect(csOpSwAccessTimer, SIGNAL(timeout()), this, SLOT(on_csOpSwAccessTimer_timeout()));
    //csOpSwAccessTimer.setRepeats(false);
    }
}

void CsOpSwAccess::on_csOpSwAccessTimer_timeout()
{
 log->debug("csOpSwAccessTimer timed out!");
 ProgListener* temp = p;
 p = NULL;
 if (temp != NULL) {
     temp->programmingOpReply(0, ProgListener::FailedTimeout);
 }
}

void CsOpSwAccess::initializeCsOpSwValidTimer() {
    if (csOpSwValidTimer == NULL) {
//        csOpSwValidTimer = new Timer(1000, (ActionEvent e) -> {
//            log->debug("csOpSwValidTimer timed out; invalidating held data!");
//            haveValidLowBytes = false;
//            haveValidHighBytes = false;
//            cmdStnOpSwState = CmdStnOpSwStateType.IDLE;
//            });
   csOpSwValidTimer = new QTimer();
   csOpSwValidTimer->setSingleShot(true);
   csOpSwValidTimer->setInterval(1000);
   connect(csOpSwValidTimer, SIGNAL(timeout()), this, SLOT(on_csOpSwValidTimer_timeout()));
   csOpSwValidTimer->start(1000);
   //csOpSwValidTimer.setRepeats(false);
    }
}

void CsOpSwAccess::on_csOpSwValidTimer_timeout()
{
 log->debug("csOpSwValidTimer timed out; invalidating held data!");
 haveValidLowBytes = false;
 haveValidHighBytes = false;
 cmdStnOpSwState = CmdStnOpSwStateType::IDLE;
}

#if 0
/*private*/ void updateStoredOpSwsFromRead(LocoNetMessage m) {
    if ((m.getOpCode() == 0xE7) &&
            (m.getElement(1) == 0x0e) &&
            (m.getElement(2) == 0x7f)) {
        opSwBytes[0] = m.getElement(3);
        opSwBytes[1] = m.getElement(4);
        opSwBytes[2] = m.getElement(5);
        opSwBytes[3] = m.getElement(6);
        opSwBytes[4] = m.getElement(8);
        opSwBytes[5] = m.getElement(9);
        opSwBytes[6] = m.getElement(10);
        opSwBytes[7] = m.getElement(11);
        opSwBytes[8] = 0;
        opSwBytes[10] = 0;
        opSwBytes[11] = 0;
        opSwBytes[12] = 0;
        opSwBytes[13] = 0;
        opSwBytes[14] = 0;
        opSwBytes[15] = 0;
        haveValidLowBytes = true;
        haveValidHighBytes = false;
    } else if ((m.getOpCode() == 0xE7) &&
            (m.getElement(1) == 0x0e) &&
            (m.getElement(2) == 0x7e)) {
        opSwBytes[8] = m.getElement(3);
        opSwBytes[9] = m.getElement(4);
        opSwBytes[10] = m.getElement(5);
        opSwBytes[11] = m.getElement(6);
        opSwBytes[12] = m.getElement(8);
        opSwBytes[13] = m.getElement(9);
        opSwBytes[14] = m.getElement(10);
        opSwBytes[15] = m.getElement(11);
        haveValidHighBytes = true;
    }
}
/*private*/ void changeOpSwBytes(int cmdStnOpSwNum, boolean cmdStnOpSwVal) {
    log->debug("updating OpSw{} to {}", cmdStnOpSwNum, cmdStnOpSwVal);
    int msgByte = (cmdStnOpSwNum-1) / 8;
    int bitpos = (cmdStnOpSwNum-1)-(8*msgByte);
    int newVal = (opSwBytes[msgByte] & (~(1<<bitpos))) | ((cmdStnOpSwVal?1:0)<<bitpos);
    log->debug("updating OpSwBytes[{}] from {} to {}", msgByte, opSwBytes[msgByte], newVal);
    opSwBytes[msgByte] = newVal;
}

// accessor
/*public*/ CmdStnOpSwStateType getState() {
    return cmdStnOpSwState;
}
#endif
// initialize logging
/*private*/ /*final*/ /*static*/ Logger* CsOpSwAccess::log = LoggerFactory::getLogger("CsOpSwAccess");
