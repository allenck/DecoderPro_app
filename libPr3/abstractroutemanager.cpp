#include "abstractroutemanager.h"

AbstractRouteManager::AbstractRouteManager(SystemConnectionMemo *memo, QObject *parent)
 : RouteManager(memo, parent)
{

}

/*public*/ Route* AbstractRouteManager::getBySystemName(QString name) {
    return (Route*)_tsys->value(name);
}

/*public*/ Route* AbstractRouteManager::getByUserName(QString key) {
    return (Route*)_tuser->value(key);
}
