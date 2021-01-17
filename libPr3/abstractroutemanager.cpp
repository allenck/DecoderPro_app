#include "abstractroutemanager.h"

AbstractRouteManager::AbstractRouteManager(SystemConnectionMemo *memo, QObject *parent)
 : RouteManager(memo, parent)
{

}

/*public*/ Route* AbstractRouteManager::getBySystemName(QString name) const {
    return (Route*)_tsys->value(name);
}

/*public*/ Route* AbstractRouteManager::getByUserName(QString key) const {
    return (Route*)_tuser->value(key);
}
