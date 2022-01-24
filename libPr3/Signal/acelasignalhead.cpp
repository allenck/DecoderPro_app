#include "acelasignalhead.h"
#include "loggerfactory.h"
#include "acelanode.h"
#include "acelasystemconnectionmemo.h"
#include "acelatrafficcontroller.h"
#include "acelaaddress.h"
#include "loggerfactory.h"

/**
 * Extend jmri.AbstractSignalHead for Acela signals based upon
 * Grapevine example by Bob Jacobsen.
 *
 * @author Bob Coleman Copyright (C) 2009
 */
// /*public*/  class AcelaSignalHead extends DefaultSignalHead {
/**
 * Create a SignalHead object, with only a system name.
 * <p>
 * @param systemName should have been previously validated.
 * @param memo system connection.
 */
/*public*/  AcelaSignalHead::AcelaSignalHead(QString systemName, AcelaSystemConnectionMemo* memo, QObject *parent)
 : DefaultSignalHead(systemName, parent)
{
    //super(systemName);
    _memo = memo;
    // Save system Name
    tSystemName = systemName;

    // Extract the Bit from the name
    int num = AcelaAddress::getBitFromSystemName(systemName, _memo->getSystemPrefix());
    addr = num;

    AcelaNode* tNode = AcelaAddress::getNodeFromSystemName(tSystemName, _memo);
    if (tNode == nullptr) {
        // node does not exist, ignore call
        log->error(tr("Can't find new Acela Signal with name '%1'").arg(tSystemName));
        return;
    }
    tNode->setOutputSpecial(addr, 1);
    tNode->setOutputSignalHeadType(addr, AcelaNode::UKNOWN);
}

/**
 * Create a SignalHead object, with both system and user names.
 * <p>
 * @param systemName should have been previously validated.
 * @param userName user name.
 * @param memo system connection.
 */
/*public*/  AcelaSignalHead::AcelaSignalHead(QString systemName, QString userName, AcelaSystemConnectionMemo* memo, QObject *parent)
 : DefaultSignalHead(systemName, userName, parent)
{
    //super(systemName, userName);
    _memo = memo;
    // Save system Name
    tSystemName = systemName;

    // Extract the Bit from the name
    int num = AcelaAddress::getBitFromSystemName(systemName, _memo->getSystemPrefix());
    addr = num;

    AcelaNode* tNode = AcelaAddress::getNodeFromSystemName(tSystemName, _memo);
    if (tNode == nullptr) {
        // node does not exist, ignore call
        log->error(tr("Can't find new Acela Signal with name '%1'").arg(tSystemName));
        return;
    }
    tNode->setOutputSpecial(addr, 1);
    tNode->setOutputSignalHeadType(addr, AcelaNode::UKNOWN);
}

/**
 * Handle a request to change state on layout
 */
//@Override
/*protected*/ void AcelaSignalHead::updateOutput() {
    AcelaNode* tNode = AcelaAddress::getNodeFromSystemName(tSystemName,_memo);
    if (tNode == nullptr) {
        // node does not exist, ignore call
        log->error(tr("Can't resolve Acela Signal with name '%1'. command ignored").arg(tSystemName));
        return;
    }

    // sort out states
    int cmd;
    if (mLit) {
        switch (mAppearance) {
            case RED:
                cmd = 1;
                break;
            case FLASHRED:
                cmd = 2;
                break;
            case YELLOW:
                cmd = 3;
                break;
            case FLASHYELLOW:
                cmd = 4;
                break;
            case GREEN:
                cmd = 5;
                break;
            case FLASHGREEN:
                cmd = 6;
                break;
            case DARK:
                cmd = 7;
                break;
            default:
                log->warn(tr("Unexpected new appearance: %1").arg(mAppearance));
                cmd = 2;
                break;  // flash red for error
        }
    } else {
        cmd = 7; // set dark if not lit
    }
    tNode->setOutputSpecial(addr, cmd);
    tNode->setOutputBit(addr, true);

}

// flashing is done on the cards, so we don't have to
// do it manually
//@Override
/*public*/  void AcelaSignalHead::startFlash() {
}

//@Override
/*public*/  void AcelaSignalHead::stopFlash() {
}


/*private*/ /*final*/ /*static*/ Logger* AcelaSignalHead::log = LoggerFactory::getLogger("AcelaSignalHead");
