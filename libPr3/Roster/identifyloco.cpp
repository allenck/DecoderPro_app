#include "identifyloco.h"
#include "instancemanager.h"
#include "lnprogrammermanager.h"
#include "loggerfactory.h"

IdentifyLoco::IdentifyLoco(Programmer* programmer,QObject *parent) :
    AbstractIdentify(programmer, parent)
{
 address = -1;
 log = new Logger("IdentifyLoco");
}
/**
 * Interact with a programmer to identify the RosterEntry for a loco
 * on the programming track.
 *
 * This is a class (instead of a Roster member function) to simplify use of
 * ProgListener callbacks. It is abstract as we expect that local classes
 * will define the message and done members.
 *
 * Once started, this maintains a List of possible RosterEntrys as
 * it works through the identification progress.
 *
 * @author	Bob Jacobsen   Copyright (C) 2001
 * @version     $Revision: 20344 $
 * @see         jmri.jmrit.roster.RosterEntry
 */
//abstract /*public*/ class IdentifyLoco extends jmri.jmrit.AbstractIdentify {


// steps of the identification state machine
/*public*/ bool IdentifyLoco::test1()
{
 // request contents of CV 29
 statusUpdate(tr("Read CV 29"));
 readCV("29");
 return false;
}

/*public*/ bool IdentifyLoco::test2(int value)
{
 // check for long address vs short address
 if ( (value & 0x20) != 0 )
 {
  // long address needed
  shortAddr = false;
  statusUpdate(tr("Long address - read CV 17"));
  readCV("17");
 }
 else
 {
    // short - read address
    shortAddr = true;
    statusUpdate(tr("Short address - read CV 1"));
    readCV("1");
 }
 return false;
}

/*public*/ bool IdentifyLoco::test3(int value) {
    // check if we're reading short or long
    if (shortAddr) {
        // short - this is the address
        address = value;
        statusUpdate(tr("Reading Mfg Id CV 8"));
        readCV("7");
        return false;
    } else {
        // long - need CV18 also
        cv17val = value;
        statusUpdate(tr("LONG ADDRESS - READ CV 18"));
        readCV("18");
        return false;
    }
}

/*public*/ bool IdentifyLoco::test4(int value) {
    // only for long address
    if (shortAddr) {
        cv7val = value;
        statusUpdate(tr("Read MFG version - CV 7"));
        readCV("8");
        return false;

    }

    // value is CV18, calculate address
    cv18val = value;
    address = (cv17val & 0x3f)*256 + cv18val;
    statusUpdate(tr("Reading Mfg Id CV 8"));
    readCV("7");
    return false;
}

/*public*/ bool IdentifyLoco::test5(int value) {
    if(shortAddr){
        cv8val = value;
        //We have read manufacturer and decoder version details
        return true;
    }
    statusUpdate(tr("Read MFG version - CV 7"));
    readCV("8");
    cv7val = value;
    return false;
}

/*public*/ bool IdentifyLoco::test6(int value) {
    if(shortAddr){
        log->error(tr("test4 routine reached in short address mode"));
        return true;
    }
    cv8val = value;
    return true;
}

/*public*/ bool IdentifyLoco::test7(int value) {
    log->error("unexpected step 7 reached with value: "+QString::number(value));
    return true;
}

/*public*/ bool IdentifyLoco::test8(int value) {
    log->error("unexpected step 8 reached with value: "+QString::number(value));
    return true;
}

//@Override
/*public*/ bool IdentifyLoco::test9(int value) {
    log->error("unexpected step 9 reached with value: " + QString::number(value));
    return true;
}

/*protected*/ void IdentifyLoco::statusUpdate(QString s) {
    message(s);
    if (s==("Done")) done(address);
    else if (log->isDebugEnabled()) log->debug("received status: "+s);
}

//abstract /*protected*/ void done(int address);

//abstract /*protected*/ void message(String m);

// initialize logging
/*static*/ Logger* IdentifyLoco::log = LoggerFactory::getLogger("IdentifyLoco");

//}
