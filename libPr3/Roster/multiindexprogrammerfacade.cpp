#include "multiindexprogrammerfacade.h"
#include "loggerfactory.h"
#include <QStringList>
#include "QDateTime"

//MultiIndexProgrammerFacade::MultiIndexProgrammerFacade(QObject *parent) :
//    AbstractProgrammerFacade(parent)
//{
//}
/**
 * Programmer facade for single index multi-CV access.
 * <p>
 * Used through the String write/read/confirm interface.  Accepts address formats:
 *<ul>
 *<li>If cvFirst is true:<ul>
 *<li> 123 Do write/read/confirm to 123
 *<li> 123.11 Writes 11 to the first index CV, then does write/read/confirm to 123
 *<li> 123.11.12 Writes 11 to the first index CV, then 12 to the second index CV, then does write/read/confirm to 123
 *</ul>
 *<li>If cvFirst is false:<ul>
 *<li> 123 Do write/read/confirm to 123
 *<li> 11.123 Writes 11 to the first index CV, then does write/read/confirm to 123
 *<li> 11.12.123 Writes 11 to the first index CV, then 12 to the second index CV, then does write/read/confirm to 123
 *</ul>
 *</ul>
 *
 * @see jmri.implementation.ProgrammerFacadeSelector
 *
 * @author      Bob Jacobsen  Copyright (C) 2013
 * @version	$Revision: 24246 $
 */
///*public*/ class MultiIndexProgrammerFacade extends AbstractProgrammerFacade implements ProgListener {

/**
 * @param indexPI  CV to which the first value is to be written for NN.NN and NN.NN.NN forms
 * @param indexSI  CV to which the second value is to be written for NN.NN.NN forms
 */
/*public*/ MultiIndexProgrammerFacade::MultiIndexProgrammerFacade(Programmer* prog, QString indexPI, QString indexSI, bool cvFirst, bool skipDupIndexWrite, QObject* parent)
    : AbstractProgrammerFacade(prog, parent)
{
 //super(prog);
 _usingProgrammer = nullptr;
 state = NOTPROGRAMMING;

 this->defaultIndexPI = indexPI;
 this->defaultIndexSI = indexSI;
 this->cvFirst = cvFirst;
 this->skipDupIndexWrite = skipDupIndexWrite;
}

// take the CV string and configure the actions to take
void MultiIndexProgrammerFacade::parseCV(QString cv)
{
 valuePI = -1;
 valueSI = -1;
 if (cv.contains("."))
 {
  if (cvFirst)
  {
   QStringList splits = cv.split(QRegExp("\\."));
   switch (splits.length())
   {
    case 2:
        if (hasAlternateAddress(splits[1])) {
            valuePI = getAlternateValue(splits[1]);
            indexPI = getAlternateAddress(splits[1]);
        } else {
            valuePI = splits.at(1).toInt();
            indexPI = defaultIndexPI;
        }
        _cv = splits[0];
        break;
    case 3:
        if (hasAlternateAddress(splits[1])) {
            valuePI = getAlternateValue(splits[1]);
            indexPI = getAlternateAddress(splits[1]);
        } else {
            valuePI = splits.at(1).toInt();
            indexPI = defaultIndexPI;
        }
        if (hasAlternateAddress(splits[2])) {
            valueSI = getAlternateValue(splits[2]);
            indexSI = getAlternateAddress(splits[2]);
        } else {
            valueSI = splits.at(2).toInt();
            indexSI = defaultIndexSI;
        }
        _cv = splits[0];
        break;
    default:
        log->error("Too many parts in CV name; taking 1st two " + cv);
        valuePI = splits.at(1).toInt();
        valueSI = splits.at(2).toInt();
        _cv = splits[0];
        break;
   }
  }
  else {
   QStringList splits = cv.split(QRegExp("\\."));
   switch (splits.length())
   {
    case 2:
        if (hasAlternateAddress(splits[0])) {
            valuePI = getAlternateValue(splits[0]);
            indexPI = getAlternateAddress(splits[0]);
        } else {
            valuePI = splits.at(0).toInt();
            indexPI = defaultIndexPI;
        }
        _cv = splits.at(1);
        break;
    case 3:
        if (hasAlternateAddress(splits[0])) {
            valuePI = getAlternateValue(splits[0]);
            indexPI = getAlternateAddress(splits[0]);
        } else {
            valuePI = splits.at(0).toInt();
            indexPI = defaultIndexPI;
        }
        if (hasAlternateAddress(splits[1])) {
            valueSI = getAlternateValue(splits[1]);
            indexSI = getAlternateAddress(splits[1]);
        } else {
            valueSI = splits.at(1).toInt();
            indexSI = defaultIndexSI;
        }
        _cv = splits[2];
        break;
    default:
        log->error("Too many parts in CV name; taking 1st two " + cv);
        valuePI = splits.at(0).toInt();
        valueSI = splits.at(1).toInt();
        _cv = splits[2];
        break;
   }
  }
 } else {
     _cv = cv;
 }
}


bool MultiIndexProgrammerFacade::hasAlternateAddress(QString cv) {
    return cv.contains("=");
}

QString MultiIndexProgrammerFacade::getAlternateAddress(QString cv) {
    return cv.split("=")[0];
}

int MultiIndexProgrammerFacade::getAlternateValue(QString cv) {
    return cv.split("=").at(1).toInt();
}

/**
 * Check if the last-written PI and SI values can still be counted on.
 *
 * @return true if last-written values are reliable; false otherwise
 */
bool MultiIndexProgrammerFacade::useCachePiSi() {
    return skipDupIndexWrite
            && (lastValuePI == valuePI)
            && (lastValueSI == valueSI)
            && ((/*System.currentTimeMillis() */QDateTime::currentMSecsSinceEpoch()- lastOpTime) < maxDelay);
}

// programming interface
//@Override
/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    _val = val;
    useProgrammer(p);
    parseCV(CV);
    if (valuePI == -1) {
        lastValuePI = -1;  // next indexed operation needs to write PI, SI
        lastValueSI = -1;

        // non-indexed operation
        state = ProgState::PROGRAMMING;
        prog->writeCV(_cv, val, (ProgListener*)this);
    } else if (useCachePiSi()) {
        // indexed operation with set values is same as non-indexed operation
        state = ProgState::PROGRAMMING;
        prog->writeCV(_cv, val, (ProgListener*)this);
    } else {
        lastValuePI = valuePI;  // after check in 'if' statement
        lastValueSI = valueSI;

        // write index first
        state = ProgState::FINISHWRITE;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}


//@Override
/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
    useProgrammer(p);
    parseCV(CV);
    if (valuePI == -1) {
        lastValuePI = -1;  // next indexed operation needs to write PI, SI
        lastValueSI = -1;

        state = ProgState::PROGRAMMING;
        prog->readCV(_cv, (ProgListener*)this);
    } else if (useCachePiSi()) {
        // indexed operation with set values is same as non-indexed operation
        state = ProgState::PROGRAMMING;
        prog->readCV(_cv, (ProgListener*)this);
    } else {
        lastValuePI = valuePI;  // after check in 'if' statement
        lastValueSI = valueSI;

        // write index first
        state = ProgState::FINISHREAD;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}

//@Override
/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    _val = val;
    useProgrammer(p);
    parseCV(CV);
    if (valuePI == -1) {
        lastValuePI = -1;  // next indexed operation needs to write PI, SI
        lastValueSI = -1;

        // non-indexed operation
        state = ProgState::PROGRAMMING;
        prog->confirmCV(_cv, val, (ProgListener*)this);
    } else if (useCachePiSi()) {
        // indexed operation with set values is same as non-indexed operation
        state = ProgState::PROGRAMMING;
        prog->confirmCV(_cv, val, (ProgListener*)this);
    } else {
        lastValuePI = valuePI;  // after check in 'if' statement
        lastValueSI = valueSI;

        // write index first
        state = ProgState::FINISHCONFIRM;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}


// internal method to remember who's using the programmer
/*protected*/ void MultiIndexProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        if (log->isInfoEnabled()) log->info(QString("programmer already in use by ") +QString(_usingProgrammer->self()->metaObject()->className()));
        throw ProgrammerException("programmer in use");
    }
    else {
        _usingProgrammer = p;
        return;
    }
}


// get notified of the final result
// Note this assumes that there's only one phase to the operation
/*public*/ void MultiIndexProgrammerFacade::programmingOpReply(int value, int status)
{
 if (log->isDebugEnabled()) log->debug("notifyProgListenerEnd value "+QString::number(value)+" status "+QString::number(status));

    if (_usingProgrammer == NULL) log->error("No listener to notify");

    if (status != ProgListener::OK)
    {
     // clear memory of last PI, SI written
     lastValuePI = -1;
     lastValueSI = -1;
     lastOpTime = -1;

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
         _usingProgrammer = nullptr; // done
         state = ProgState::NOTPROGRAMMING;
         lastOpTime = QDateTime::currentMSecsSinceEpoch(); //System.currentTimeMillis();
         temp->programmingOpReply(value, status);
         break;
     }
     case FINISHREAD:
         if (valueSI == -1) {
             try {
                 state = ProgState::PROGRAMMING;
                 prog->readCV(_cv, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing final read", e);
             }
         } else {
             try {
                 int tempSI = valueSI;
                 valueSI = -1;
                 state = ProgState::FINISHREAD;
                 prog->writeCV(indexSI, tempSI, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing write SI for read", e);
             }
         }
         break;
     case FINISHWRITE:
         if (valueSI == -1) {
             try {
                 state = ProgState::PROGRAMMING;
                 prog->writeCV(_cv, _val, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing final write", e);
             }
         } else {
             try {
                 int tempSI = valueSI;
                 valueSI = -1;
                 state = ProgState::FINISHWRITE;
                 prog->writeCV(indexSI, tempSI, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing write SI for write", e);
             }
         }
         break;
     case FINISHCONFIRM:
         if (valueSI == -1) {
             try {
                 state = ProgState::PROGRAMMING;
                 prog->confirmCV(_cv, _val, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing final confirm", e);
             }
         } else {
             try {
                 int tempSI = valueSI;
                 valueSI = -1;
                 state = ProgState::FINISHCONFIRM;
                 prog->writeCV(indexSI, tempSI, (ProgListener*)this);
             } catch (ProgrammerException e) {
                 log->error("Exception doing write SI for write", e);
             }
         }
         break;
     default:
         log->error("Unexpected state on reply: " + state);
         // clean up as much as possible
         _usingProgrammer = nullptr;
         state = ProgState::NOTPROGRAMMING;
         lastValuePI = -1;
         lastValueSI = -1;
         lastOpTime = -1;

 }
}

Logger* MultiIndexProgrammerFacade::log =  LoggerFactory::getLogger("MultiIndexProgrammerFacade");
