#include "jmriclientturnoutmanager.h"
#include "jmriclientsystemconnectionmemo.h"
#include "jmriclientturnout.h"
/**
 * Implement turnout manager for JMRIClient systems
 * <P>
 * System names are "prefixnnn", where prefix is the system prefix and nnn is
 * the turnout number without padding.
 *
 * @author Paul Bender Copyright (C) 2010
  */
// /*public*/ class JMRIClientTurnoutManager extends jmri.managers.AbstractTurnoutManager {


/*public*/ JMRIClientTurnoutManager::JMRIClientTurnoutManager(JMRIClientSystemConnectionMemo* memo, QObject *parent)
 : AbstractTurnoutManager(memo, parent)
{
    this->memo = memo;
    this->prefix = memo->getSystemPrefix();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo* JMRIClientTurnoutManager::getMemo() {
    return  memo;
}

//@Override
/*public*/ Turnout* JMRIClientTurnoutManager::createNewTurnout(QString systemName, QString userName) const {
    Turnout* t;
    int addr = (systemName.mid(prefix.length() + 1).toInt());
    t = new JMRIClientTurnout(addr, memo);
    t->setUserName(userName);
    return t;
}

/*
 * JMRIClient Turnouts can take arbitrary names to match the names used
 * on the server.
 */
//@Override
/*public*/ QString JMRIClientTurnoutManager::createSystemName(QString curAddress, QString prefix) const /*throw (JmriException)*/ {
    return prefix + typeLetter() + curAddress;
}

//@Override
/*public*/ bool JMRIClientTurnoutManager::allowMultipleAdditions(QString systemName) {
    return true;
}

