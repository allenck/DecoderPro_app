#ifndef ROUTESTABLEMODEL_H
#define ROUTESTABLEMODEL_H

#include "abstracttablemodel.h"
#include "propertychangelistener.h"
#include "routeeditframe.h"
#include <QPointer>

class PropertyChangeEvent;
class Logger;
namespace Operations
{
 class RouteEditFrame;
 class Route;
 class RouteManager;
 class RoutesTableModel : public AbstractTableModel, public PropertyChangeListener
 {
   Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  RoutesTableModel(QObject* parent = 0);
  // Defines the columns
  enum COLUMNS
  {
   IDCOLUMN = 0,
   NAMECOLUMN = IDCOLUMN + 1,
   COMMENTCOLUMN = NAMECOLUMN + 1,
   STATUSCOLUMN = COMMENTCOLUMN + 1,
   EDITCOLUMN = STATUSCOLUMN + 1,

   HIGHESTCOLUMN = EDITCOLUMN + 1
  };
  enum SORTOPTS
  {
    SORTBYNAME = 1,
    SORTBYID = 2
  };
  /*public*/ void setSort(int sort);
  /*public*/ void dispose();
  /*public*/ int rowCount(const QModelIndex &parent) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role)override;
  /*public*/ int getRowCount()const override{return rowCount(QModelIndex());}
  /*public*/ int getColumnCount()const override{return columnCount(QModelIndex());}

  QObject* self() override {return (QObject*)this;}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override;

 private:
  RouteManager* manager; // There is only one manager
  Logger* log;
  /*private*/ int _sort;// = SORTBYNAME;
  /*private*/ /*synchronized*/ void removePropertyChangeRoutes();
  /*private*/ /*synchronized*/ void updateList();
  QList<Route*> sysList;// = NULL;
  void initTable(JTable* table);
  QPointer<RouteEditFrame> ref;// = NULL;
  /*private*/ /*synchronized*/ void editRoute(int row);
 friend class RoutesTableFrame;
 };
}
#endif // ROUTESTABLEMODEL_H
