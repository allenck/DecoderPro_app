#include "abstractsectionmanager.h"

AbstractSectionManager::AbstractSectionManager(InternalSystemConnectionMemo* memo, QObject *parent)
 : AbstractManager(memo, parent)
{

}
/*public*/ Section* AbstractSectionManager::AbstractSectionManager::getBySystemName(QString name) const{
    QString key = name.toUpper();
    if(_tsys->value(key))
    return (Section*)_tsys->value(key)->self();
    return nullptr;
}

/*public*/ Section* AbstractSectionManager::AbstractSectionManager::getByUserName(QString key) const{
    if(_tuser->value(key))
     return (Section*)_tuser->value(key)->self();
    return nullptr;
}
