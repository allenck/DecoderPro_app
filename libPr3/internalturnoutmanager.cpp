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
}
/*public*/ InternalTurnoutManager::InternalTurnoutManager(QString prefix, QObject *parent) : AbstractTurnoutManager(nullptr, parent)
 {
 setObjectName("InternalTurnoutManager");
        //super();
 this->prefix = prefix;
}
/*public*/ InternalTurnoutManager::InternalTurnoutManager(InternalSystemConnectionMemo* memo, QObject* parent) : AbstractTurnoutManager((SystemConnectionMemo*)memo, parent)
{
 setObjectName("InternalTurnoutManager");
}
/**
 * Create and return an internal (no layout connection) turnout
 */
/*protected*/ Turnout* InternalTurnoutManager::createNewTurnout(QString systemName, QString userName)
{
    return (Turnout*)new AbstractTurnout(systemName, userName);
//    {
//        /*protected*/ void forwardCommandChangeToLayout(int s) {}
//        /*protected*/ void turnoutPushbuttonLockout(boolean b){}
//    };
}


/*public*/ QString InternalTurnoutManager::getSystemPrefix() { return prefix; }

/*public*/ QString InternalTurnoutManager::createSystemName(QString curAddress, QString prefix) throw (JmriException)
{
    return prefix+QString(typeLetter())+curAddress;
}
/*
 * Turnout operation support. Internal turnouts don't need retries.
 */

/*public*/ QStringList InternalTurnoutManager::getValidOperationTypes()
{
 QStringList list;
 list << "NoFeedback";
//    return new QStringList{"NoFeedback"}; }
 return list;
}
