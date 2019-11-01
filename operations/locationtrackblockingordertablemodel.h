#ifndef LOCATIONTRACKBLOCKINGORDERTABLEMODEL_H
#define LOCATIONTRACKBLOCKINGORDERTABLEMODEL_H

#include "abstracttablemodel.h"

class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class Track;
 class Location;
 class LocationTrackBlockingOrderTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  LocationTrackBlockingOrderTableModel(QObject* parent = 0);
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ void dispose();

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) ;
 private:
  /*synchronized*/ void updateList();
  /*private*/ void initTable();
  Logger * log;

 protected:
  /*protected*/ Location* _location;
  /*protected*/ QList<Track*> _tracksList;// = new ArrayList<Track>();
  /*protected*/ JTable* _table;
  enum COLUMNS
  {
   // Defines the columns
   ID_COLUMN = 0,
   NAME_COLUMN = 1,
   TYPE_COLUMN = 2,
   ORDER_COLUMN = 3,
   UP_COLUMN = 4,
   DOWN_COLUMN = 5,

   HIGHESTCOLUMN = DOWN_COLUMN + 1
  };
  /*protected*/ void initTable(JTable* table, Location* location);
  /*protected*/ void removePropertyChangeTracks();
  friend class LocationTrackBlockingOrderFrame;
 };
}
#endif // LOCATIONTRACKBLOCKINGORDERTABLEMODEL_H
