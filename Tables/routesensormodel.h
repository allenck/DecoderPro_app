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
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

 private:
  static Logger* log;
  /*private*/ /*final*/ AbstractRouteAddEditFrame* routeAddFrame;

};
#if 0
class RouteSensorModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum COLUMNS
    {
     SNAME_COLUMN = 0,
     UNAME_COLUMN = 1,
     INCLUDE_COLUMN = 2,
     STATE_COLUMN = 3
    };
    RouteSensorModel(RouteTableAction* self);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    void reset();

private:
    Logger* log;
    RouteTableAction* self;
};
#endif
#endif // ROUTESENSORMODEL_H
