#ifndef ABSTRACTROUTEMANAGER_H
#define ABSTRACTROUTEMANAGER_H
#include "routemanager.h"

class AbstractRouteManager : public RouteManager
{
  Q_OBJECT
 public:
  AbstractRouteManager(SystemConnectionMemo* memo = nullptr, QObject* parent = nullptr);
  /*public*/ Route* getBySystemName(QString name) const;
  /*public*/ Route* getByUserName(QString key) const;
};

#endif // ABSTRACTROUTEMANAGER_H
