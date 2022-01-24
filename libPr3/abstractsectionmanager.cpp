#include "abstractsectionmanager.h"

AbstractSectionManager::AbstractSectionManager(InternalSystemConnectionMemo* memo, QObject *parent)
 : AbstractManager(memo, parent)
{

}
/*public*/ Section* AbstractSectionManager::AbstractSectionManager::getBySystemName(QString name) const{
    QString key = name.toUpper();
    return (Section*)_tsys->value(key);
}

/*public*/ Section* AbstractSectionManager::AbstractSectionManager::getByUserName(QString key) const{
    return (Section*)_tuser->value(key);
}
