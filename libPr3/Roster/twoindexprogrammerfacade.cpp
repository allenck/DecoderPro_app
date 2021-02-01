#include "twoindexprogrammerfacade.h"

//TwoIndexTcsProgrammerFacade::TwoIndexTcsProgrammerFacade(QObject *parent) :
//    AbstractProgrammerFacade(parent)
//{
//}
/**
 * Programmer facade for single index multi-CV access.
 * <p>
 * Used through the String write/read/confirm interface.  Accepts address formats:
 *<ul>
 *<li> T2CV.11.12 <BR>
 *      The write operation writes 11 to the first index CV (201), 12 to the 2nd index CV (202),
 *      then writes the data to CV 203 (MSB) and 204 (LSB).<BR>
 *      The read operation is slightly different, writing 111 (100+11) to CV201, then
 *      then 12 to the 2nd index CV (202), then writes 100 to CV204, then reads the two values
 *      from CV203 and CV204.
 *<li> T3CV.11.12.13 <BR>
 *      The write operation writes 11 to the first index CV (201), the data to the 2nd index CV (202),
 *      then writes 12 to CV203 and 13 to CV204.<BR>
 *      The read operation writes 11 to CV201, then 12 to CV203, then 13 to CV204, then reads from CV202.
  *</ul>
 * All others pass through to the next facade or programmer. E.g. 123 will do a write/read/confirm to 123,
 * or some other facade can provide "normal" indexed addressing.
 *
 * @see jmri.implementation.ProgrammerFacadeSelector
 *
 * @author      Bob Jacobsen  Copyright (C) 2013
 * @version	$Revision: 24246 $
 */
// /*public*/ class TwoIndexTcsProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 */
/*public*/ TwoIndexTcsProgrammerFacade::TwoIndexTcsProgrammerFacade(Programmer* prog,QObject *parent) :
    AbstractProgrammerFacade(prog, parent)
{
 //super(prog);
 state = NOTPROGRAMMING;
 _usingProgrammer = NULL;
 log = new Logger("TwoIndexTcsProgrammerFacade");
}

// these could be constructor arguments, but until there's another decoder
// this weird, for simplicity we leave them as constants
/*static final*/ QString TwoIndexTcsProgrammerFacade::indexPI = "201";
/*static final*/ QString TwoIndexTcsProgrammerFacade::indexSI = "202";
/*static final*/ QString TwoIndexTcsProgrammerFacade::valMSB  = "203";
/*static final*/ QString TwoIndexTcsProgrammerFacade::valLSB  = "204";
/*static final*/ QString TwoIndexTcsProgrammerFacade::readStrobe = "204";  // CV that has to be written before read
/*static final*/ QString TwoIndexTcsProgrammerFacade::format2Flag = "T2CV"; // flag to indicate this type of CV
/*static final*/ QString TwoIndexTcsProgrammerFacade::format3Flag = "T3CV"; // flag to indicate this type of CV
/*static final*/ int TwoIndexTcsProgrammerFacade::readOffset = 100;



void TwoIndexTcsProgrammerFacade::parseCV(QString cv) throw (IllegalArgumentException)
{
 valuePI = -1;
 valueSI = -1;
 if (cv.contains("."))
 {
  QStringList splits = cv.split(QRegExp("\\."));
  if (splits.length() == 3 && splits[0]==(format2Flag))
  {
            valuePI = splits[1].toInt();
            valueSI = splits[2].toInt();
  } else if (splits.length() == 4 && splits[0]==(format3Flag)) {
            valuePI = splits[1].toInt();
            valueMSB = splits[2].toInt();
            valueLSB = splits[3].toInt();
        } else {
            _cv = cv;  // this is a pass through operation
        }
    } else {
        _cv = cv;
    }
}

// programming interface
/*synchronized*/ /*public*/ void TwoIndexTcsProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
    _val = val;
    useProgrammer(p);
    parseCV(CV);
    upperByte = 0;
    if (valuePI==-1) { // this is pass through
        state = PROGRAMMING;
        prog->writeCV(_cv, val, (ProgListener*)this);
    } else {
        // write index first
        state = DOSIFORWRITE;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}

/*synchronized*/ /*public*/ void TwoIndexTcsProgrammerFacade::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
    readCV(CV, p);
}

/*synchronized*/ /*public*/ void TwoIndexTcsProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
{
    useProgrammer(p);
    parseCV(CV);
    upperByte = 0;
    if (valuePI==-1) {
        state = PROGRAMMING;
        prog->readCV(_cv, (ProgListener*)this);
    } else {
        // write index first; 2nd operation depends on type
        if (valueSI==-1)
            state = DOMSBFORREAD;
        else
            state = DOSIFORREAD;
        prog->writeCV(indexPI, valuePI+readOffset, (ProgListener*)this);
    }
}

// internal method to remember who's using the programmer
/*protected*/ void TwoIndexTcsProgrammerFacade::useProgrammer(ProgListener* p) //throws jmri.ProgrammerException
{
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        if (log->isInfoEnabled()) log->info("programmer already in use by "+QString(_usingProgrammer->self()->metaObject()->className()));
        //throw new jmri.ProgrammerException("programmer in use");
        emit ProgrammerException("programmer in use");
    }
    else {
        _usingProgrammer = p;
        return;
    }
}



// get notified of the final result
// Note this assumes that there's only one phase to the operation
/*public*/ void TwoIndexTcsProgrammerFacade::programmingOpReply(int value, int status) {
    if (log->isDebugEnabled()) log->debug("notifyProgListenerEnd value "+QString::number(value)+" status "+QString::number(status));

    if (_usingProgrammer == NULL) log->error("No listener to notify");

    switch (state) {
        case DOSIFORREAD:
//            try {
                state = DOSTROBEFORREAD;
                prog->writeCV(indexSI, valueSI, (ProgListener*)this);
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing write SI for read", e);
//            }
            break;
        case DOSTROBEFORREAD:
//            try {
                state = DOREADFIRST;
                prog->writeCV(readStrobe, readOffset, (ProgListener*)this);
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing write strobe for read", e);
//            }
            break;
        case DOREADFIRST:
//            try {
                state = FINISHREAD;
                prog->readCV(valMSB, (ProgListener*)this);
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing write strobe for read", e);
//            }
            break;
        case FINISHREAD:
//            try {
                state = PROGRAMMING;
                if (valuePI != -1 && valueSI == -1) {
                    upperByte = 0;
                    prog->readCV(indexSI, (ProgListener*)this);
                } else {
                    upperByte = value;
                    prog->readCV(valLSB, (ProgListener*)this);
                }
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing final read", e);
//            }
            break;

        case DOMSBFORREAD:
//            try {
                state = DOLSBFORREAD;
                prog->writeCV(valMSB, valueMSB, (ProgListener*)this);
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing write strobe for read", e);
//            }
            break;
        case DOLSBFORREAD:
//            try {
                state = FINISHREAD;
                prog->writeCV(valLSB, valueLSB, (ProgListener*)this);
//            } catch (jmri.ProgrammerException e) {
//                log->error("Exception doing write strobe for read", e);
//            }
            break;

        case DOSIFORWRITE:
            if (valueSI != -1) {
                // writing SI index after PI
//                try {
                    state = DOWRITEFIRST;
                    prog->writeCV(indexSI, valueSI, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing write SI for write", e);
//                }
            } else {
                // writing data after PI
//                try {
                    state = DOWRITEFIRST;
                    prog->writeCV(indexSI, _val, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing write SI for write", e);
//                }
            }
            break;
        case DOWRITEFIRST:
            if (valueSI != -1) {
                // write upper data
//                try {
                    state = FINISHWRITE;
                    prog->writeCV(valMSB, _val/256, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing write MSB for write", e);
//                }
            } else {
                // write 2nd index
//                try {
                    state = FINISHWRITE;
                    prog->writeCV(valMSB, valueMSB, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing write MSB for write", e);
//                }
            }
            break;
        case FINISHWRITE:
            if (valueSI != -1) {
//                try {
                    state = PROGRAMMING;
                    prog->writeCV(valLSB, _val&255, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing final write", e);
//                }
            } else {
//                try {
                    state = PROGRAMMING;
                    prog->writeCV(valLSB, valueLSB, (ProgListener*)this);
//                } catch (jmri.ProgrammerException e) {
//                    log->error("Exception doing final write", e);
//                }
            }
            break;

  case PROGRAMMING:
  {
   // the programmingOpReply handler might send an immediate reply, so
   // clear the current listener _first_
   ProgListener* temp = _usingProgrammer;
   _usingProgrammer = NULL; // done
   state = NOTPROGRAMMING;
   temp->programmingOpReply(upperByte*256+value, status);
   break;
  }
  default:
  {
   log->error("Unexpected state on reply: "+state);
   // clean up as much as possible
   _usingProgrammer = NULL;
   state = NOTPROGRAMMING;
   break;
  }
 }
}
