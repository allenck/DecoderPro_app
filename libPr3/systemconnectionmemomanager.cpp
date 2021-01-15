#include "systemconnectionmemomanager.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "vptr.h"
#include "internalsystemconnectionmemo.h"

SystemConnectionMemoManager::SystemConnectionMemoManager()
{

}
/**
 * Manager for SystemConnectionMemos. Manages SystemConnectionMemos and
 * SystemConnectionMemo registration with the InstanceManager, ensuring that no
 * two SystemConnectionMemos have the same username or system connection prefix.
 * Also provides an object that other objects can listen to for notification of
 * changes in SystemConnectionMemos.
 *
 * @author Randall Wood Copyright 2017
 */
// /*public*/ class SystemConnectionMemoManager extends Bean {

/**
 * Property name change fired when a connection is registered. The fired
 * event has a null old value and the added connection as the new value.
 */
/*public*/ /*final*/ /*static*/ QString SystemConnectionMemoManager::CONNECTION_ADDED = "ConnectionAdded";
/**
 * Property name change fired when a connection is deregistered. The fired
 * event has the removed connection as the old value and a null new value.
 */
/*public*/ /*final*/ /*static*/ QString SystemConnectionMemoManager::CONNECTION_REMOVED = "ConnectionRemoved";
/*private*/ /*final*/ /*static*/ Logger* SystemConnectionMemoManager::log = LoggerFactory::getLogger("SystemConnectionMemoManager");

/**
 * Register a SystemConnectionMemo in the InstanceManager.
 *
 * @param memo the SystemConnectionMemo to register
 */
/*public*/ void SystemConnectionMemoManager::_register(SystemConnectionMemo* memo)
{
 if(log)
  log->debug(tr("registering connection %1").arg(memo->getUserName()));

  // check for special case
  /*QList<SystemConnectionMemo*>*/QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
  int size = list->size();
  //if (size > 0 && (list.at(size - 1) instanceof InternalSystemConnectionMemo))
  if(size > 0 && qobject_cast<InternalSystemConnectionMemo*>(list->at(size-1)) != NULL)
  {
    // last is internal, so insert before that one
    log->debug("   putting one before end");
    SystemConnectionMemo* internal = (SystemConnectionMemo*)list->at(size - 1);
    InstanceManager::deregister(internal->self(), "SystemConnectionMemo");
    InstanceManager::store(memo->self(), "SystemConnectionMemo");
    InstanceManager::store(internal->self(), "SystemConnectionMemo");
  }
  else {
    // just add on end
    InstanceManager::store(memo->self(), "SystemConnectionMemo");
  }
  this->firePropertyChange("ConnectionAdded", QVariant(), VPtr<SystemConnectionMemo>::asQVariant(memo));
}

/*public*/ void SystemConnectionMemoManager::deregister(SystemConnectionMemo* memo) {
 // removeFromActionList();
 InstanceManager::deregister(memo->self(), "SystemConnectionMemo");
 firePropertyChange("ConnectionRemoved", VPtr<SystemConnectionMemo>::asQVariant(memo), QVariant());
}

/*public*/ /*synchronized*/ SystemConnectionMemo* SystemConnectionMemoManager::getSystemConnectionMemo(/*@Nonnull*/ QString systemPrefix,/* @Nonnull*/ QString userName)
{
 foreach( QObject* memo, *InstanceManager::getList("SystemConnectionMemo"))
 {
     if (((SystemConnectionMemo*)memo)->getSystemPrefix() == (systemPrefix) && ((SystemConnectionMemo*)memo)->getUserName() == (userName)) {
         return (SystemConnectionMemo*)memo;
     }
 }
 return NULL;
}

/*public*/ /*synchronized*/ SystemConnectionMemo* SystemConnectionMemoManager::getSystemConnectionMemoForUserName(/*@Nonnull */QString userName) {
        foreach (QObject* memo, *InstanceManager::getList("SystemConnectionMemo")) {
            if (((SystemConnectionMemo*)memo)->getUserName() == (userName)) {
                return (SystemConnectionMemo*)memo;
            }
        }
        return NULL;
    }

/*public*/ /*synchronized*/ SystemConnectionMemo* SystemConnectionMemoManager::getSystemConnectionMemoForSystemPrefix(/*@Nonnull*/ QString systemPrefix) {
    foreach (QObject* memo, *InstanceManager::getList("SystemConnectionMemo")) {
        if (((SystemConnectionMemo*)memo)->getSystemPrefix() == (systemPrefix)) {
            return (SystemConnectionMemo*)memo;
        }
    }
    return NULL;
}

/**
 * Check if a system connection user name is available to be used.
 *
 * @param userName the user name to check
 * @return true if available; false if already in use
 */
/*public*/ /*synchronized*/ bool SystemConnectionMemoManager::isUserNameAvailable(/*@Nonnull*/ QString userName) {
//        return InstanceManager::getList("SystemConnectionMemo".stream().noneMatch((memo) -> (userName.equals(memo.getUserName())));
 foreach (QObject* memo, *InstanceManager::getList("SystemConnectionMemo"))
 {
  if (userName == ((SystemConnectionMemo*)memo)->getUserName())
   return false;
 }
 return true;
}

/**
 * Check if a system connection prefix for the system names of other objects
 * is available to be used.
 *
 * @param systemPrefix the system prefix to check
 * @return true if available; false if already in use
 */
/*public*/ /*synchronized*/ bool SystemConnectionMemoManager::isSystemPrefixAvailable(/*@Nonnull*/ QString systemPrefix) {
//        return InstanceManager.getList(SystemConnectionMemo.class).stream().noneMatch((memo) -> (memo.getSystemPrefix().equals(systemPrefix)));
 QObjectList* list = InstanceManager::getList("SystemConnectionMemo");
 foreach (QObject* obj, *InstanceManager::getList("SystemConnectionMemo"))
 {
  SystemConnectionMemo* memo = (SystemConnectionMemo*)obj;
  if (systemPrefix == memo->getSystemPrefix())
   return false;
 }
 return true;
}

/**
 * Get the default instance of this manager.
 *
 * @return the default instance, created if needed
 */
/*public*/ /*static*/ SystemConnectionMemoManager* SystemConnectionMemoManager::getDefault() {
//        return InstanceManager::getOptionalDefault(SystemConnectionMemoManager.class).orElseGet(() -> {
//            return InstanceManager.setDefault(SystemConnectionMemoManager.class, new SystemConnectionMemoManager());
//        });
 SystemConnectionMemoManager* mgr = (SystemConnectionMemoManager*)InstanceManager::getOptionalDefault("SystemConnectionMemoManager");
 if(mgr != NULL)
  return mgr;
 else
  return (SystemConnectionMemoManager*)InstanceManager::setDefault("SystemConnectionMemoManager", new SystemConnectionMemoManager());
}
