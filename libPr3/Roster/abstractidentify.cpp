#include "abstractidentify.h"
#include "lnprogrammermanager.h"
#include "instancemanager.h"
#include "globalprogrammermanager.h"

AbstractIdentify::AbstractIdentify(QObject *parent) :
    QObject(parent)
{
 log = new Logger("AbstractIdentify");
 state = 0;
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

    // The first test is invoked here; the rest are handled in the programmingOpReply callback
    state = 1;
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
/*public*/ void AbstractIdentify::programmingOpReply(int value, int status)
{
 // we abort if the status isn't normal
 if (status != ProgListener::OK)
 {
  log->warn("Stopping due to error: "
                 +((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer()->decodeErrorCode(status));
        statusUpdate("Stopping due to error: "
                     +((GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager"))->getGlobalProgrammer()->decodeErrorCode(status));
  state = 0;
  error();
  return;
 }
 // continuing for normal operation
 // this should eventually be something smarter, maybe using reflection,
 // but for now...
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
   if (test8(value)) identifyDone();
   else log->error("test8 with value = "+QString::number(value)+" returned false, but there is no next step");
   return;
  default:
   // this is an error
   log->error(tr("unexpected state in normal operation: ")+QString::number(state)+" value: "+QString::number(value)+", ending identification");
   identifyDone();
   return;
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
/*protected*/ void AbstractIdentify::readCV(int cv)
{
 //Programmer* p = InstanceManager::programmerManagerInstance()->getGlobalProgrammer();
 GlobalProgrammerManager* p = (GlobalProgrammerManager*)InstanceManager::getDefault("GlobalProgrammerManager");
 if (p == NULL)
 {
  statusUpdate("No programmer connected");
 }
 else
 {
//  try
//  {
  //SlotManager* s = (SlotManager*)p;
  AbstractProgrammer* s = (AbstractProgrammer*)p->getGlobalProgrammer();
  connect(s, SIGNAL(programmerException(QString)), this, SLOT(On_programmerException(QString)));
  s->readCV(QString::number(cv), (ProgListener*)this);
//  }
//  catch (ProgrammerException ex)
//  {
//   statusUpdate(ex.getMessage());
//  }
 }
}
void AbstractIdentify::On_programmerException(QString txt)
{
 statusUpdate(txt);
}

/*protected*/ void AbstractIdentify::writeCV(int cv, int value)
{
 SlotManager* p = (SlotManager*)((LnProgrammerManager*)InstanceManager::programmerManagerInstance())->getGlobalProgrammer();
 if (p == NULL)
 {
  statusUpdate("No programmer connected");
 }
 else
 {
//        try {
  p->writeCV(cv, value, (ProgListener*)this);
//        } catch (ProgrammerException ex) {
//            statusUpdate(ex.getMessage());
//        }
 }
}
