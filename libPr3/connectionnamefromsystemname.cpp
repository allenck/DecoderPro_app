#include "connectionnamefromsystemname.h"
#include "instancemanager.h"
#include "dccmanufacturerlist.h"
#include "systemconnectionmemo.h"

//ConnectionNameFromSystemName::ConnectionNameFromSystemName(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Common utility method for returning the System Connection Name from
 * the System Name Prefix
 *
 * @author Kevin Dickerson  Copyright 2010
 * @version $Revision: 17977 $
 */
///*public*/ class ConnectionNameFromSystemName{

/**
 * Locates the connected systems name from a given prefix.
 *
 * @param prefix the system prefix
 * @return The Connection System Name or null if no connection has the given
 *         prefix
 */
//@CheckForNull
/*static*/ /*public*/ QString ConnectionNameFromSystemName::getConnectionName(/*@Nonnull*/ QString prefix) {
    SystemConnectionMemo* memo = getSystemConnectionMemoFromSystemPrefix(prefix);
    if (memo != NULL) {
        return memo->getUserName();
    }
    return NULL;
}

/**
 * Locates the connected systems prefix from a given System name.
 *
 * @param name The user name
 * @return The system prefix or null if no connection has the given name
 */
//@CheckForNull
/*static*/ /*public*/ QString ConnectionNameFromSystemName::getPrefixFromName(/*@Nonnull*/ QString name) {
    SystemConnectionMemo* memo = getSystemConnectionMemoFromUserName(name);
    if (memo != NULL) {
        return memo->getSystemPrefix();
    }
    return NULL;
}

/**
 * Get the {@link jmri.jmrix.SystemConnectionMemo} for a given system
 * prefix.
 *
 * @param systemPrefix the system prefix
 * @return the SystemConnectionMemo or null if no memo exists
 */
//@CheckForNull
/*static*/ /*public*/ SystemConnectionMemo* ConnectionNameFromSystemName::getSystemConnectionMemoFromSystemPrefix(/*@Nonnull */QString systemPrefix) {
    foreach (QObject* memo,  *InstanceManager::getList("SystemConnectionMemo")) {
        if (((SystemConnectionMemo*)memo)->getSystemPrefix()==(systemPrefix)) {
            return (SystemConnectionMemo*)memo;
        }
    }
    return NULL;
}

/**
 * Get the {@link jmri.jmrix.SystemConnectionMemo} for a given user name.
 *
 * @param userName the user name
 * @return the SystemConnectionMemo or null if no memo exists
 */
//@CheckForNull
/*static*/ /*public*/ SystemConnectionMemo* ConnectionNameFromSystemName::getSystemConnectionMemoFromUserName(/*@Nonnull*/ QString userName) {
    foreach (QObject* memo, *InstanceManager::getList("SystemConnectionMemo")) {
        if (((SystemConnectionMemo*)memo)->getUserName() == (userName)) {
            return (SystemConnectionMemo*)memo;
        }
    }
    return NULL;
}
