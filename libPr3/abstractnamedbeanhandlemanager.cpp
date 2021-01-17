#include "abstractnamedbeanhandlemanager.h"

AbstractNamedBeanHandleManager::AbstractNamedBeanHandleManager(QObject *parent)
{

}
/*public*/ NamedBean* AbstractNamedBeanHandleManager::getBySystemName(QString name) const{
    QString key = name.toUpper();
    return (NamedBean*)_tsys->value(key);
}

/*public*/ NamedBean* AbstractNamedBeanHandleManager::getByUserName(QString userName) const{
 QString normalizedUserName = NamedBean::normalizeUserName(userName);
 return normalizedUserName != nullptr ? _tuser->value(normalizedUserName) : nullptr;
}
