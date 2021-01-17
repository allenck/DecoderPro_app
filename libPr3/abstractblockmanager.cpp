#include "abstractblockmanager.h"

AbstractBlockManager::AbstractBlockManager(QObject *parent) : AbstractManager(parent)
{

}

/*public*/ Block* AbstractBlockManager::getBySystemName(QString name) const
{
 return  (Block*)_tsys->value(name);
}

/*public*/ Block* AbstractBlockManager::getByUserName(QString userName)const
{
 QString normalizedUserName = NamedBean::normalizeUserName(userName);
 return normalizedUserName != "" ? (Block*)_tuser->value(normalizedUserName) : nullptr;

}
