#include "sprogturnoutmanager.h"
#include "loggerfactory.h"
#include "sprogturnout.h"
#include "sprogcsturnout.h"

using namespace Sprog;

/**
 * Implement turnout manager for Sprog systems.
 * <P>
 * System names are "STnnn", where nnn is the turnout number without padding.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogTurnoutManager extends jmri.managers.AbstractTurnoutManager {


/*public*/ SprogTurnoutManager::SprogTurnoutManager(SprogSystemConnectionMemo* memo, QObject* parent) : AbstractTurnoutManager(memo,parent)
{
    _memo = memo;
}

//@Override
/*public*/ QString SprogTurnoutManager::getSystemPrefix() const{
    return _memo->getSystemPrefix();
}

// Sprog-specific methods

//@Override
/*public*/ Turnout* SprogTurnoutManager::createNewTurnout(QString systemName, QString userName) {
    int addr = (systemName.mid(getSystemPrefix().length() + 1)).toInt(); // multi char prefix
    Turnout* t;
    if (_memo->getSprogMode() == SprogConstants::SprogMode::OPS ) {
        t = new SprogCSTurnout(addr, _memo);
    } else {
        t = new SprogTurnout(addr, _memo);
    }
    t->setUserName(userName);
    return t;
}

/**
 * Get the bit address from the system name.
 */
/*public*/ int SprogTurnoutManager::getBitFromSystemName(QString systemName) {
    // validate the System Name leader characters
    if (!systemName.startsWith(getSystemPrefix() + "T")) {
        // here if an illegal sprog turnout system name
        log->error(tr("illegal character in header field of sprog turnout system name: %1").arg(systemName));
        return (0);
    }
    // name must be in the STnnnnn format (S is user configurable)
    int num = 0;
    try {
     bool ok;
        num = (systemName.mid(getSystemPrefix().length() + 1)).toInt(&ok);
        if(!ok) throw new Exception();
    } catch (Exception* e) {
        log->debug(tr("invalid character in number field of system name: %1").arg(systemName));
        return (0);
    }
    if (num <= 0) {
        log->debug(tr("invalid sprog turnout system name: %1").arg(systemName));
        return (0);
    } else if (num > SprogConstants::MAX_ACC_DECODER_JMRI_ADDR) { // undocumented for SPROG, higher causes error in NMRA Acc Packet
        log->debug(tr("bit number out of range in sprog turnout system name: %1").arg(systemName));
        return (0);
    }
    return (num);
}

/**
 * Public method to validate system name format.
 *
 * @return 'true' if system name has a valid format, else returns 'false'
 */
//@Override
/*public*/ Manager::NameValidity SprogTurnoutManager::validSystemNameFormat(QString systemName)
{
    return (getBitFromSystemName(systemName) != 0) ? NameValidity::VALID : NameValidity::INVALID;
}

//@Override
/*public*/ bool SprogTurnoutManager::allowMultipleAdditions(QString systemName) {
    return true;
}

/**
 * Provide a manager-specific tooltip for the Add new item beantable pane.
 */
//@Override
/*public*/ QString SprogTurnoutManager::getEntryToolTip() {
    QString entryToolTip = tr("enter a number from 1 to 2044 (inclusive).");
    return entryToolTip;
}

/**
 * @deprecated JMRI Since 4.4 instance() shouldn't be used; convert to JMRI multi-system support structure
 */
//@Deprecated
/*static*/ /*public*/ SprogTurnoutManager* SprogTurnoutManager::instance() {
    return NULL;
}

/*private*/ /*final*/ /*static*/ Logger* SprogTurnoutManager::log = LoggerFactory::getLogger("SprogTurnoutManager");
