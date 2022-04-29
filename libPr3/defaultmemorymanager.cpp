#include "defaultmemorymanager.h"
#include "defaultmemory.h"
#include "internalsystemconnectionmemo.h"

DefaultMemoryManager::DefaultMemoryManager(InternalSystemConnectionMemo *memo, QObject *parent) :
    AbstractMemoryManager(memo, parent)
{
 setObjectName("DefaultMemoryManager");
 setProperty("JavaClassName", "jmri.managers.DefaultMemoryManager");
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}
/**
 * Provide the concrete implementation for the Internal Memory Manager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 17977 $
 */
//public class DefaultMemoryManager extends AbstractMemoryManager {

/*public*/ QString DefaultMemoryManager::getSystemPrefix()const { return "I"; }

/*protected*/ Memory* DefaultMemoryManager::createNewMemory(QString systemName, QString userName){
 // makeSystemName validates that systemName is correct
 return new DefaultMemory(makeSystemName(systemName), userName);
}


