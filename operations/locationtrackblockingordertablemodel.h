#ifndef LOCATIONTRACKBLOCKINGORDERTABLEMODEL_H
#define LOCATIONTRACKBLOCKINGORDERTABLEMODEL_H

#include "abstracttablemodel.h"
#include "propertychangelistener.h"
class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class Track;
 class Location;
 class LocationTrackBlockingOrderTableModel : public AbstractTableModel, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  LocationTrackBlockingOrderTableModel(QObject* parent = 0);
  /*public*/ int rowCount(const QModelIndex &parent) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ void dispose();
  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override ;
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
