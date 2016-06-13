#include "internalturnoutmanager.h"

/**
 * Implement a turnout manager for "Internal" (virtual) turnouts.
 *
 * @author			Bob Jacobsen Copyright (C) 2006
 * @version			$Revision: 18178 $
 */
//public class InternalTurnoutManager extends AbstractTurnoutManager {
InternalTurnoutManager::InternalTurnoutManager()
{
 setObjectName("InternalTurnoutManager");
 prefix = "I";
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
