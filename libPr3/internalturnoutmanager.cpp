#include "internalturnoutmanager.h"

/**
 * Implement a turnout manager for "Internal" (virtual) turnouts.
 *
 * @author			Bob Jacobsen Copyright (C) 2006
 * @version			$Revision: 18178 $
 */
//public class InternalTurnoutManager extends AbstractTurnoutManager {
InternalTurnoutManager::InternalTurnoutManager(QObject *parent) : AbstractTurnoutManager(nullptr, parent)
{
 setObjectName("InternalTurnoutManager");
 prefix = "I";
 registerSelf();
}

/*public*/ InternalTurnoutManager::InternalTurnoutManager(QString prefix, QObject *parent) : AbstractTurnoutManager(nullptr, parent)
 {
 setObjectName("InternalTurnoutManager");
        //super();
 this->prefix = prefix;
 registerSelf();

}

/*public*/ InternalTurnoutManager::InternalTurnoutManager(InternalSystemConnectionMemo* memo, QObject* parent) : AbstractTurnoutManager((SystemConnectionMemo*)memo, parent)
{
 setObjectName("InternalTurnoutManager");
 registerSelf();

}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ SystemConnectionMemo *InternalTurnoutManager::getMemo() const {
    return  memo;
}
/**
 * Create and return an internal (no layout connection) turnout
 */
/*protected*/ Turnout* InternalTurnoutManager::createNewTurnout(QString systemName, QString userName) const
{
//    return (Turnout*)new AbstractTurnout(systemName, userName)
//    {
//        /*protected*/ void forwardCommandChangeToLayout(int s) {}
//        /*protected*/ void turnoutPushbuttonLockout(boolean b){}
//    };
 return new AbstractTurnoutO1(systemName, userName);
}

//@Override
/*public*/ bool InternalTurnoutManager::allowMultipleAdditions(QString systemName) {
    return true;
}

/*public*/ QString InternalTurnoutManager::createSystemName(QString curAddress, QString prefix) const throw (JmriException)
{
    return prefix+QString(typeLetter())+curAddress;
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ QString InternalTurnoutManager::getEntryToolTip() {
    return tr("abc123<br>(any string except $, :, \).");
}

/*
 * Turnout operation support. Internal turnouts don't need retries.
 */

/*public*/ QStringList InternalTurnoutManager::getValidOperationTypes()
{
 QStringList list = QStringList()
  << "NoFeedback";
 return list;
}
