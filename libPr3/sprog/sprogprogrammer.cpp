#include "sprogprogrammer.h"
#include "loggerfactory.h"
#include "sprogreply.h"
#include <QMetaEnum>
#include "abstractidentify.h"

using namespace Sprog;

/**
 * Implement the jmri.Programmer interface via commands for the Sprog
 * programmer. This provides a service mode programmer.
 *
 * @author Bob Jacobsen Copyright (C) 2001
  */
///*public*/ class SprogProgrammer extends AbstractProgrammer implements SprogListener {


/*public*/ SprogProgrammer::SprogProgrammer(SprogSystemConnectionMemo* memo, QObject* parent) : AbstractProgrammer(parent) {
     _memo = memo;
 setObjectName("SprogProgrammer");
 progState = 0;
 _usingProgrammer = NULL;
 _controller = NULL;

}

/**
 * Implemented Types.
 */
//@Override
/*public*/ QList<QString> SprogProgrammer::getSupportedModes() {
    QList<QString> ret =  QList<QString>();
    ret.append("DIRECTBITMODE");
    ret.append("PAGEMODE");
    return ret;
}

//@Override
/*public*/ bool SprogProgrammer::getCanRead() {
    if (getMode()->equals(ProgrammingMode::PAGEMODE)) return true;
    else if (getMode()->equals(ProgrammingMode::DIRECTBITMODE)) return true;
    else {
        log->error(tr("Unknown internal mode %1 returned true from getCanRead()").arg(getMode()->toString()));
        return true;
    }
}

/*static*/ /*final*/ int SprogProgrammer::NOTPROGRAMMING = 0;    // is notProgramming
/*static*/ /*final*/ int SprogProgrammer::COMMANDSENT = 2;       // read/write command sent, waiting reply
/*synchronized*/ /*public*/ void SprogProgrammer::writeCV(QString CV, int val, ProgListener* p) throw (ProgrammerException)
{
 writeCV(CV.toInt(), val,p);
}

// programming interface
//@Override
/*synchronized*/ /*public*/ void SprogProgrammer::writeCV(int CV, int val, ProgListener* p) throw (ProgrammerException) {
    if (log->isDebugEnabled()) {
        log->debug("writeCV " + QString::number(CV) + " mode " + getMode()->toString() + " listens " + (QString(p->self()->metaObject()->className())));
    }
    useProgrammer(p);
    _val = val;
    startProgramming(_val, CV);
}

//@Override
/*synchronized*/ /*public*/ void SprogProgrammer::confirmCV(QString CV, int /*val*/, ProgListener* p) throw (ProgrammerException) {
    AbstractProgrammer::readCV(CV, p);
}

//@Override
/*public*/ void SprogProgrammer::readCV(QString CV, ProgListener* p) throw (ProgrammerException)
{
 this->readCV(CV.toInt(),p);
}

/*synchronized*/ /*public*/ void SprogProgrammer::readCV(int CV, ProgListener* p) throw (ProgrammerException)
{
 if (log->isDebugEnabled())
 {
  log->debug("readCV " +QString::number(CV) + " mode " + getMode()->toString() + " listens " + (QString(p->self()->metaObject()->className())));
 }
 useProgrammer(p);
 _val = -1;
 startProgramming(_val, CV);
}


/**
 * Send the command to start programming operation.
 *
 * @param val   Value to be written, or -1 for read
 * @param CV    CV to read/write
 */
/*private*/ void SprogProgrammer::startProgramming(int val, int CV)
{
 // here ready to send the read/write command
 progState = COMMANDSENT;
 // see why waiting
 try
 {
  startLongTimer();
  controller()->sendSprogMessage(progTaskStart(getMode(), val, CV), (SprogListener*)this);
 }
 catch (Exception e)
 {
  // program op failed, go straight to end
  log->error("program operation failed, exception " + e.getMessage());
  progState = NOTPROGRAMMING;
 }
}

/**
 * Internal method to remember who's using the programmer.
 */
/*protected*/ void SprogProgrammer::useProgrammer(ProgListener* p) throw (ProgrammerException)
{
 // test for only one!
 if (_usingProgrammer != NULL && _usingProgrammer != p)
 {
  if (log->isInfoEnabled())
  {
   log->info("programmer already in use by " + QString(_usingProgrammer->self()->metaObject()->className()));
  }
  throw  ProgrammerException("programmer in use");
 }
 else
 {
  _usingProgrammer = p;
  return;
 }
}

/**
 * Internal method to create the SprogMessage for programmer task start.
 */
/*protected*/ SprogMessage* SprogProgrammer::progTaskStart(ProgrammingMode* mode, int val, int cvnum) {
    // val = -1 for read command; mode is direct, etc
    if (val < 0) {
        return SprogMessage::getReadCV(cvnum, mode);
    } else {
        return SprogMessage::getWriteCV(cvnum, val, mode);
    }
}

//@Override
/*public*/ void SprogProgrammer::notifyMessage(SprogMessage* m) {
}

//@Override
/*synchronized*/ /*public*/ void SprogProgrammer::notifyReply(SprogReply* reply)
{
 if (progState == NOTPROGRAMMING)
 {
  // we get the complete set of replies now, so ignore these
  log->debug(tr("reply in NOTPROGRAMMING state") + " [" + reply->toString() + "]");
  return;
 }
 else if (progState == COMMANDSENT)
 {
  log->debug(tr("reply in COMMANDSENT state") + " [" + reply->toString() + "]");
  // operation done, capture result, then have to leave programming mode
  progState = NOTPROGRAMMING;
  // check for errors
  if (reply->match("No Ack") >= 0)
  {
   log->debug(tr("handle No Ack reply ") + reply->toString());
   // perhaps no loco present? Fail back to end of programming
   progState = NOTPROGRAMMING;
   notifyProgListenerEnd(-1, ProgListener::NoLocoDetected);
  }
  else if (reply->match("!O") >= 0)
  {
   log->debug("handle !O reply " + reply->toString());
   // Overload. Fail back to end of programming
   progState = NOTPROGRAMMING;
   notifyProgListenerEnd(-1, ProgListener::ProgrammingShort);
  }
  else
  {
   // see why waiting
   if (_val == -1) {
       // read was in progress - get return value
       _val = reply->value();
   }
   progState = NOTPROGRAMMING;
   stopTimer();
   // if this was a read, we cached the value earlier.  If its a
   // write, we're to return the original write value
   notifyProgListenerEnd(_val, ProgListener::OK);
  }

  // SPROG always leaves power off after programming so we inform the
  // power manager of the new state
  controller()->getAdapterMemo()->getPowerManager()->notePowerState(PowerManager::OFF);
 }
 else
 {
     log->debug("reply in un-decoded state");
 }
}

/**
 * Internal routine to handle a timeout
 */
//@Override
/*synchronized*/ /*protected*/ void SprogProgrammer::timeout()
{
 if (progState != NOTPROGRAMMING)
 {
  // we're programming, time to stop
  log->debug("Timeout in a programming state");
  // perhaps no loco present? Fail back to end of programming
  progState = NOTPROGRAMMING;
  notifyProgListenerEnd(_val, ProgListener::FailedTimeout);
 }
 else
 {
  log->debug("timeout in NOTPROGRAMMING state");
 }
}

// internal method to notify of the final result
/*protected*/ void SprogProgrammer::notifyProgListenerEnd(int value, int status)
{
 log->debug("notifyProgListenerEnd value " + QString::number(value) + " status " +   QString::number(status) + "-(" + ProgListener::statusString((ProgListener::status)status)+")");
 // the programmingOpReply handler might send an immediate reply, so
 // clear the current listener _first_
 if (_usingProgrammer == NULL) {
     log->error("No listener to notify");
 }
 else
 {
  ProgListener* temp = _usingProgrammer;
  _usingProgrammer = NULL;
//     if(qobject_cast<AbstractIdentify*>(temp) != NULL)
//       ((AbstractIdentify*)temp)->programmingOpReply(value, status);
//     else
//      temp->programmingOpReply(value, status);
  connect(this, SIGNAL(notify_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));
  emit notify_programmingOpReply(value, status);
  disconnect(this, SIGNAL(notify_programmingOpReply(int,int)), temp->self(), SLOT(programmingOpReply(int,int)));

 }
}

/*protected*/ SprogTrafficController* SprogProgrammer::controller() {
    // connect the first time
    if (_controller == NULL) {
        _controller = _memo->getSprogTrafficController();
    }
    return _controller;
}

/*private*/ /*final*/ /*static*/ Logger* SprogProgrammer::log = LoggerFactory::getLogger("SprogProgrammer");
