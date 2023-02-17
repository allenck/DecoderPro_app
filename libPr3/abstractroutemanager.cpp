#include "abstractroutemanager.h"

AbstractRouteManager::AbstractRouteManager(SystemConnectionMemo *memo, QObject *parent)
 : RouteManager(memo, parent)
{

}

/*public*/ Route* AbstractRouteManager::getBySystemName(QString name)const {
    NamedBean* nb = _tsys->value(name);
    if(nb)
     return (Route*)nb->self();
    return nullptr;
}

/*public*/ Route* AbstractRouteManager::getByUserName(QString key) const{
    NamedBean* nb = _tuser->value(key);
    if(nb)
     return (Route*)nb->self();
    return nullptr;
}
