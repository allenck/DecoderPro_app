#include "defaultmemorymanager.h"
#include "defaultmemory.h"

DefaultMemoryManager::DefaultMemoryManager(QObject *parent) :
    AbstractMemoryManager(parent)
{
 setObjectName("DefaultMemoryManager");
 registerSelf(); // Added by ACK (can't be done by AbstractManager's ctor!

}
/**
 * Provide the concrete implementation for the Internal Memory Manager.
 *
 * @author			Bob Jacobsen Copyright (C) 2004
 * @version			$Revision: 17977 $
 */
//public class DefaultMemoryManager extends AbstractMemoryManager {

/*public*/ QString DefaultMemoryManager::getSystemPrefix() const { return "I"; }

/*protected*/ Memory* DefaultMemoryManager::createNewMemory(QString systemName, QString userName) const{
    // we've decided to enforce that memory system
    // names start with IM by prepending if not present
    if (!systemName.startsWith("IM"))
        systemName = "IM"+systemName;
    return (Memory*)(new DefaultMemory(systemName, userName));
}


