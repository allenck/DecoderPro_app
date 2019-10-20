#ifndef TRAINSSCHEDULETABLEMODEL_H
#define TRAINSSCHEDULETABLEMODEL_H

#include "abstracttablemodel.h"

class Logger;
class JTable;
class PropertyChangeEvent;
namespace Operations
{
 class TrainSchedule;
 class TrainsScheduleTableFrame;
 class Train;
 class TrainManager;
 class TrainScheduleManager;
 class TrainsScheduleTableModel : public AbstractTableModel
 {
 public:
  TrainsScheduleTableModel(QObject* parent = 0);
  /*public*/ void dispose();
  /*public*/ void setSort(int sort);
  /*public*/ /*synchronized*/ QList<Train*> getSelectedTrainList();
  /*public*/ int getFixedColumn() const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ TrainSchedule* getSchedule(int col) const;
  void initTable(JTable* table, TrainsScheduleTableFrame* frame);


 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  TrainManager* trainManager;// = TrainManager.instance();
  TrainScheduleManager* scheduleManager;// = TrainScheduleManager.instance();
  // Defines the columns
  enum COLUMNS
  {
   IDCOLUMN = 0,
   NAMECOLUMN = IDCOLUMN + 1,
   DESCRIPTIONCOLUMN = NAMECOLUMN + 1,

   FIXEDCOLUMN = DESCRIPTIONCOLUMN + 1
  };
 private:
  /*private*/ int _sort;// = SORTBYTIME;
  enum SORTOPTS
  {
   SORTBYNAME = 1,
   SORTBYTIME = 2,
   SORTBYDEPARTS = 3,
   SORTBYTERMINATES = 4,
   SORTBYROUTE = 5,
   SORTBYID = 6
  };
  /*private*/ /*synchronized*/ void updateList();
  Logger* log;
  QList<Train*> sysList;// = null;
  JTable* _table;// = NULL;
  TrainsScheduleTableFrame* _frame;// = null;
  void initTable();
  /*private*/ void removePropertyChangeTrainSchedules();
  /*private*/ void addPropertyChangeTrainSchedules();
  /*private*/ /*synchronized*/ void removePropertyChangeTrains();
  /*private*/ /*synchronized*/ void addPropertyChangeTrains();
  friend class TrainsScheduleTableFrame;
 };
}
#endif // TRAINSSCHEDULETABLEMODEL_H
