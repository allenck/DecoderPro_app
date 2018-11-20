#include "multiindexprogrammerfacade.h"

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
/*public*/ MultiIndexProgrammerFacade::MultiIndexProgrammerFacade(Programmer* prog, QString indexPI, QString indexSI, bool cvFirst, QObject* parent)
    : AbstractProgrammerFacade(prog, parent)
{
 //super(prog);
 this->indexPI = indexPI;
 this->indexSI = indexSI;
 this->cvFirst = cvFirst;
 _usingProgrammer = NULL;
 state = NOTPROGRAMMING;
 log = new Logger("MultiIndexProgrammerFacade");
}

void MultiIndexProgrammerFacade::parseCV(QString cv)
{
 valuePI = -1;
 valueSI = -1;
 if (cv.contains("."))
 {
  if (cvFirst)
  {
   QStringList splits = cv.split("\\.");
   if (splits.length() == 2)
   {
    valuePI = splits[1].toInt();
    _cv = splits[0];
   }
   else if (splits.length() == 3)
   {
    valuePI = splits[1].toInt();
    valueSI = splits[2].toInt();
    _cv = splits[0];
   }
   else
   {
    log->error("Too many parts in CV name "+cv);
    valuePI = splits[1].toInt();
    valueSI = splits[2].toInt();
    _cv = splits[0];
   }
  }
  else
  {
   QStringList splits = cv.split("\\.");
   if (splits.length() == 2)
   {
    valuePI = splits[0].toInt();
    _cv = splits[1];
   }
   else if (splits.length() == 3)
   {
    valuePI = splits[0].toInt();
    valueSI = splits[1].toInt();
    _cv = splits[2];
   }
   else
   {
    log->error("Too many parts in CV name "+cv);
    valuePI = splits[0].toInt();
    valueSI = splits[1].toInt();
    _cv = splits[2];
   }
  }
 }
 else
 {
  _cv = cv;
 }
}

// programming interface
/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    _val = val;
    useProgrammer(p);
    parseCV(CV);
    if (valuePI==-1) {
        state = PROGRAMMING;
        prog->writeCV(_cv, val, (ProgListener*)this);
    } else {
        // write index first
        state = FINISHWRITE;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}

/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::confirmCV(QString CV, int val, ProgListener* p) throw (ProgrammerException) {
    readCV(CV, p);
}

/*synchronized*/ /*public*/ void MultiIndexProgrammerFacade::readCV(QString CV, ProgListener* p) throw (ProgrammerException) {
    useProgrammer(p);
    parseCV(CV);
    if (valuePI==-1) {
        state = PROGRAMMING;
        prog->readCV(_cv, (ProgListener*)this);
    } else {
        // write index first
        state = FINISHREAD;
        prog->writeCV(indexPI, valuePI, (ProgListener*)this);
    }
}


// internal method to remember who's using the programmer
/*protected*/ void MultiIndexProgrammerFacade::useProgrammer(ProgListener* p) throw (ProgrammerException) {
    // test for only one!
    if (_usingProgrammer != NULL && _usingProgrammer != p) {
        if (log->isInfoEnabled()) log->info(QString("programmer already in use by ") +QString(_usingProgrammer->metaObject()->className()));
        throw new ProgrammerException("programmer in use");
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
        case FINISHREAD:
    {
            if (valueSI == -1 ) {
                try {
                    state = PROGRAMMING;
                    prog->readCV(_cv, (ProgListener*)this);
                } catch (ProgrammerException e) {
                    log->error("Exception doing final read"+ e.getMessage());
                }
            } else {
                try {
                    int tempSI = valueSI;
                    valueSI = -1;
                    state = FINISHREAD;
                    prog->writeCV(indexSI, tempSI, (ProgListener*)this);
                } catch (ProgrammerException e) {
                    log->error("Exception doing write SI for read"+ e.getMessage());
                }
            }
            break;
    }
        case FINISHWRITE:
    {
            if (valueSI == -1 ) {
                try {
                    state = PROGRAMMING;
                    prog->writeCV(_cv, _val, (ProgListener*)this);
                } catch (ProgrammerException e) {
                    log->error("Exception doing final write", e);
                }
            } else {
                try {
                    int tempSI = valueSI;
                    valueSI = -1;
                    state = FINISHWRITE;
                    prog->writeCV(indexSI, tempSI, (ProgListener*)this);
                } catch (ProgrammerException e) {
                    log->error("Exception doing write SI for write", e);
                }
            }
            break;
  }
  default:
  {
   log->error("Unexpected state on reply: "+state);
   // clean up as much as possible
   _usingProgrammer = NULL;
   state = NOTPROGRAMMING;
  }
 }
}

