#include "abstractidentify.h"
#include "lnprogrammermanager.h"
#include "instancemanager.h"
#include "globalprogrammermanager.h"
#include "loggerfactory.h"
#include "programmingmode.h"

/*static*/ /*final*/ int AbstractIdentify::RETRY_COUNT = 2;

AbstractIdentify::AbstractIdentify(Programmer* programmer, QObject *parent) :
    QObject(parent)
{
 state = 0;
 this->programmer = programmer;
}

/**
 * Abstract base for common code of IdentifyLoco and IdentifyDecoder, the
 * two classes that use a programmer to match Roster entries to what's on the
 * programming track.
 *
 * @author			Bob Jacobsen   Copyright (C) 2001
 * @version			$Revision: 17977 $
 * @see             jmri.jmrit.decoderdefn.IdentifyDecoder
 * @see             jmri.jmrit.roster.IdentifyLoco
 */
///*public*/ abstract class AbstractIdentify implements jmri.ProgListener {

//    abstract /*public*/ bool test1();  // no argument to start

//    abstract /*public*/ bool test2(int value);

//    abstract /*public*/ bool test3(int value);

//    abstract /*public*/ bool test4(int value);

//    abstract /*public*/ bool test5(int value);

//    abstract /*public*/ bool test6(int value);

//    abstract /*public*/ bool test7(int value);

//    abstract /*public*/ bool test8(int value);

/**
 * Update the status field (if any). Invoked with "Done" when
 * the results are in.
 */
//    abstract protected void statusUpdate(String status);


/**
 * Start the identification state machine.
 */
/*public*/ void AbstractIdentify::start() {
    if (log->isDebugEnabled()) log->debug("identify begins");
    // must be idle, or something quite bad has happened
    if (state !=0) log->error("start with state "+QString::number(state)+", should have been zero");

    if (programmer != NULL)
    {
     savedMode = programmer->getMode(); // In case we need to change modes
    }

    // The first test is invoked here; the rest are handled in the programmingOpReply callback
    state = 1;
    retry = 0;
    test1();
}

/**
 * Stop the identification state machine. This also stops the
 * identification process.  Its invoked when a testN returns true; that
 * routine should _not_ have invoked a read or write that will result in a callback.
 */

/*protected*/ void AbstractIdentify::identifyDone() {
    if (log->isDebugEnabled()) log->debug("identifyDone ends in state "+QString::number(state));
    statusUpdate("Done");
    state = 0;
}

/**
 * Internal method to handle the programmer callbacks, e.g. when
 * a CV read request terminates.  Each will reduce (if possible) the
 * list of consistent decoders, and starts the next step.
 */
//@override
/*public*/ void AbstractIdentify::programmingOpReply(int value, int status)
{
 // we abort if there's no programmer
 //  (doing this now to simplify later)
 if (programmer == NULL) {
     log->warn("No programmer connected");
     statusUpdate("No programmer connected");

  state = 0;
  retry = 0;
  error();
  return;
 }
 log->debug(tr("Entering programmingOpReply, state %1, isOptionalCv %2,retry %3, value %4, status %5").arg(state).arg(isOptionalCv()?"true":"false").arg(retry).arg(value).arg(programmer->decodeErrorCode(status)));

 // we check if the status isn't normal
 if (status != ProgListener::OK)
 {
  if (retry < RETRY_COUNT) {
      statusUpdate("Programmer error: "
              + programmer->decodeErrorCode(status));
      state--;
      retry++;
      value = lastValue;  // Restore the last good value. Needed for retries.
  } else if (state ==1 && !programmer->getMode()->equals(ProgrammingMode::PAGEMODE)
          && programmer->getSupportedModes().contains("PAGEMODE")) {
      programmer->setMode(ProgrammingMode::PAGEMODE);
      retry = 0;
      state--;
      value = lastValue;  // Restore the last good value. Needed for retries.
      log->warn(programmer->decodeErrorCode(status)
              + ", trying " + programmer->getMode()->toString() + " mode");
  } else {
   retry = 0;
   if (programmer->getMode() != savedMode) {  // restore original mode
       log->warn(tr("Restoring %1 mode").arg(savedMode->toString()));
       programmer->setMode(savedMode);
   }
   if (isOptionalCv()) {
       log->warn(tr("CV %1 is optional. Will assume not present...").arg(cvToRead));
       statusUpdate("CV " + cvToRead + " is optional. Will assume not present...");
   } else {
       log->warn(tr("Stopping due to error: %1").arg(programmer->decodeErrorCode(status)));
       statusUpdate("Stopping due to error: "
               + programmer->decodeErrorCode(status));
       state = 0;
       error();
       return;
   }
  }
 } else {
     retry = 0;
     lastValue = value;  // Save the last good value. Needed for retries.
     setOptionalCv(false); // successful read clears flag
 }
 // continuing for normal operation
 // this should eventually be something smarter, maybe using reflection,
 // but for now...
 log->debug(tr("Was state %1, switching to state %2, test%3, isOptionalCv %4,retry %5, value %6, status %7").arg(
              state).arg(state + 1).arg(state + 1).arg(isOptionalCv()).arg(retry).arg(value).arg(programmer->decodeErrorCode(status)));
     switch (state)
 {
  case 1:
   state = 2;
   if (test2(value)) identifyDone();
   return;
  case 2:
   state = 3;
   if (test3(value)) identifyDone();
   return;
  case 3:
   state = 4;
  if (test4(value)) identifyDone();
   return;
  case 4:
   state = 5;
   if (test5(value)) identifyDone();
    return;
  case 5:
   state = 6;
   if (test6(value)) identifyDone();
   return;
  case 6:
   state = 7;
   if (test7(value)) identifyDone();
   return;
 case 7:
   state = 8;
   if (test8(value)) {
       identifyDone();
   }
   return;
 case 8:
   state = 9;
   if (test9(value))
   {
    identifyDone();
   }
   else {
     log->error("test9 with value = " + QString::number(value) + " returned false, but there is no next step");
   }
   return;
default:
   // this is an error
   log->error("unexpected state in normal operation: " + QString::number(state) + " value: " + QString::number(value) + ", ending identification");
   identifyDone();
 }
}

/**
 * Abstract routine to notify of errors
 */
//abstract protected void error();

/** To check if running now */
/*public*/ bool AbstractIdentify::isRunning() { return state != 0; }


/**
 * Access a single CV for the next step
 */
/*protected*/ void AbstractIdentify::readCV(QString cv)
{
 if (programmer == NULL)
 {
  statusUpdate("No programmer connected");
 }
 else
 {
  cvToRead = cv;
  log->debug(tr("Invoking readCV %1").arg(cvToRead));
  try
  {
   programmer->readCV(cv, (ProgListener*)this);
  }
  catch (ProgrammerException ex)
  {
   statusUpdate(ex.getMessage());
  }
 }
}

/*protected*/ void AbstractIdentify::writeCV(QString cv, int value)
{
 if (programmer == NULL)
 {
  statusUpdate("No programmer connected");
 }
 else
 {
  cvToWrite = cv;
  log->debug(tr("Invoking writeCV %1").arg(cvToWrite));
  try
  {
   programmer->writeCV(cv, value, (ProgListener*)this);
  } catch (ProgrammerException ex) {
      statusUpdate(ex.getMessage());
  }
 }
}

/**
 * Check the current status of the {@code optionalCv} flag.
 * <ul>
 * <li>If {@code true}, prevents the next CV read from aborting the
 * identification process.</li>
 * <li>Always {@code false} after a successful read.</li>
 * </ul>
 *
 * @return the current status of the {@code optionalCv} flag
 */
/*public*/ bool AbstractIdentify::isOptionalCv() {
    return optionalCv;
}

/**
 *
 * Specify whether the next CV read may legitimately fail in some cases.
 *
 * @param flag Set {@code true} to indicate that the next read may fail. A
 *             successful read will automatically set to {@code false}.
 */
/*public*/ void AbstractIdentify::setOptionalCv(bool flag) {
    this->optionalCv = flag;
}

// initialize logging
/*private*/ /*final*/ /*static*/ Logger* AbstractIdentify::log = LoggerFactory::getLogger("AbstractIdentify");
