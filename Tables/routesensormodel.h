#ifndef ROUTESENSORMODEL_H
#define ROUTESENSORMODEL_H
#include "routeoutputmodel.h"
#include "abstractrouteaddeditframe.h"

class RouteSensorModel : public RouteOutputModel
{
  Q_OBJECT
 public:
  RouteSensorModel(AbstractRouteAddEditFrame* routeAddFrame, QObject* parent = nullptr);
  /*public*/ int getRowCount() const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role)override;

 private:
  static Logger* log;
  /*private*/ /*final*/ AbstractRouteAddEditFrame* routeAddFrame;

};
#endif // ROUTESENSORMODEL_H
