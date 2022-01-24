#ifndef ABSTRACTROUTEMANAGER_H
#define ABSTRACTROUTEMANAGER_H
#include "routemanager.h"

class AbstractRouteManager : public RouteManager
{
  Q_OBJECT
 public:
  AbstractRouteManager(SystemConnectionMemo* memo = nullptr, QObject* parent = nullptr);
  /*public*/ Route* getBySystemName(QString name)  override;
  /*public*/ Route* getByUserName(QString key)  override;
  QString getNamedBeanClass() const override {return "RouteManager";}
  /*public*/ QString getBeanTypeHandled(bool plural) const override {return tr(plural?"Routes":"Route");}

};

#endif // ABSTRACTROUTEMANAGER_H
