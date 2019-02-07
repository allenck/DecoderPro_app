#include "lnreportermanager.h"
#include "lnreporter.h"

/**
 * LnReporterManager implements the ReporterManager.
 * <P>
 * System names are "LRnnn", where nnn is the Reporter number without padding.
 * <P>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project.  That permission
 * does not extend to uses in other software products.  If you wish to
 * use this code, algorithm or these message formats outside of JMRI, please
 * contact Digitrax Inc for separate permission.
 * <P>
 * Description:		Implement Reporter manager for loconet
 * @author			Bob Jacobsen Copyright (C) 2001
 * @version         $Revision: 17977 $
 */

LnReporterManager::LnReporterManager(LnTrafficController* tc, QString prefix, QObject *parent) :
    AbstractReporterManager(parent)
{
 setObjectName("LnReporterManager");
 this->prefix = prefix;
 this->tc = tc;
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

 if (tc != NULL)
 {
  tc->addLocoNetListener(~0, (LocoNetListener*)this);
  connect(tc, SIGNAL(messageProcessed(LocoNetMessage*)), this, SLOT(message(LocoNetMessage*)));
 }
 else
  log.error("No layout connection, Reporter manager can't function");
}

//public class LnReporterManager extends jmri.managers.AbstractReporterManager implements LocoNetListener {

//    // ctor has to register for LocoNet events
//    public LnReporterManager(LnTrafficController tc, QString prefix) {
//        this.prefix = prefix;
//        this.tc = tc;
//        if (tc != NULL)
//            tc.addLocoNetListener(~0, this);
//        else
//            log.error("No layout connection, Reporter manager can't function");
//    }


QString LnReporterManager::getSystemPrefix() { return prefix; }

void LnReporterManager::dispose()
{
 if (tc != NULL)
    tc->removeLocoNetListener(~0, (LocoNetListener*)this);
//super.dispose();
}

Reporter* LnReporterManager::createNewReporter(QString systemName, QString userName)
{
 Reporter* t;
//        int addr = Integer.valueOf(systemName.substring(prefix.length()+1)).intValue();
 int addr = QString(systemName.mid(prefix.length()+1)).toInt();
 t = (Reporter*)(new LnReporter(addr, tc, prefix, this));
 t->setUserName(userName);
 t->addPropertyChangeListener((PropertyChangeListener*)this);
 connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));

 return t;
}

/**
 * Get the bit address from the system name.
 *
 * @param systemName the system name
 * @return the bit address
 */
/*public*/ int LnReporterManager::getBitFromSystemName(QString systemName) {
    // validate the system Name leader characters
    if ((!systemName.startsWith(getSystemPrefix())) || (!systemName.startsWith(getSystemPrefix() + "R"))) {
        // here if an illegal LocoNet Reporter system name
        log.error(tr("invalid character in header field of loconet reporter system name: %1").arg(systemName));
        return (0);
    }
    // name must be in the LRnnnnn format (L is user configurable)
    int num;
    bool bok;
        num = systemName.mid(
                getSystemPrefix().length() + 1, systemName.length()).toInt(&bok);
    if(!bok) {
        log.warn(tr("invalid character in number field of system name: %1").arg(systemName));
        return (0);
    }
    if (num <= 0) {
        log.warn(tr("invalid loconet reporter system name: %1").arg(systemName));
        return (0);
    } else if (num > 4096) {
        log.warn(tr("bit number out of range in loconet reporter system name: %1").arg(systemName));
        return (0);
    }
    return (num);
}

/**
 * Validate system name format.
 *
 * @param systemName the name to validate
 * @return VALID if system name has a valid format; otherwise return INVALID
 */
//@Override
/*public*/ Manager::NameValidity LnReporterManager::validSystemNameFormat(QString systemName) {
    return (getBitFromSystemName(systemName) != 0) ? NameValidity::VALID : NameValidity::INVALID;
}

//@Override
/*public*/ QString LnReporterManager::getEntryToolTip() {
    return tr("enter a number from 1 to 2048 (inclusive).");
}

// listen for transponder messages, creating Reporters as needed
void LnReporterManager::message(LocoNetMessage* l)
{
 // check message type
 if (l->getOpCode() != 0xD0) return;
 if ( (l->getElement(1) & 0xC0) != 0) return;

 // message type OK, check address
 int addr = (l->getElement(1)&0x1F)*128 + l->getElement(2) +1;

 LnReporter* r = (LnReporter*) provideReporter("LR"+addr);
 r->message(l);	// make sure it got the message
}

//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnReporterManager.class.getName());
