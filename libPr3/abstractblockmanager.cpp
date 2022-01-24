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
 //return normalizedUserName != "" ? static_cast<Block*>(_tuser->value(normalizedUserName)) : nullptr;
 NamedBean* bean = _tuser->value(normalizedUserName);
 if(bean == nullptr)
  return nullptr;
 Block* b = (Block*)bean;
 return b;
}
