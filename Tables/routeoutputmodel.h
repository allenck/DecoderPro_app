#ifndef ROUTEOUTPUTMODEL_H
#define ROUTEOUTPUTMODEL_H
#include "abstracttablemodel.h"
#include "propertychangeevent.h"

class RouteOutputModel : public AbstractTableModel
{
  Q_OBJECT
 public:
  RouteOutputModel(QObject* parent=nullptr) : AbstractTableModel(parent){}
  enum COLS
  {
   SNAME_COLUMN = 0,
   UNAME_COLUMN = 1,
   INCLUDE_COLUMN = 2,
   STATE_COLUMN = 3
  };
  /*public*/ QString getColumnClass(int c) const override;
  /*public*/ QString getColumnName(int c) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  void dispose();

  friend class AbstractRouteAddEditFrame;
  friend class RouteAddFrame;

};

#endif // ROUTEOUTPUTMODEL_H
