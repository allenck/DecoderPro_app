#ifndef ROUTESTABLEMODEL_H
#define ROUTESTABLEMODEL_H

#include "abstracttablemodel.h"

class PropertyChangeEvent;
class Logger;
namespace Operations
{
 class RouteEditFrame;
 class Route;
 class RouteManager;
 class RoutesTableModel : public AbstractTableModel
 {
   Q_OBJECT
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
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  RouteManager* manager; // There is only one manager
  Logger* log;
  /*private*/ int _sort;// = SORTBYNAME;
  /*private*/ /*synchronized*/ void removePropertyChangeRoutes();
  /*private*/ /*synchronized*/ void updateList();
  QList<Route*> sysList;// = NULL;
  void initTable(JTable* table);
  RouteEditFrame* ref;// = NULL;
  /*private*/ /*synchronized*/ void editRoute(int row);
 friend class RoutesTableFrame;
 };
}
#endif // ROUTESTABLEMODEL_H
