#ifndef LOCATIONSTABLEMODEL_H
#define LOCATIONSTABLEMODEL_H

#include "abstracttablemodel.h"
#include "appslib_global.h"
#include "propertychangelistener.h"

class Logger;
class PropertyChangeEvent;
namespace Operations {
 class LocationEditFrame;
 class Location;
 class LocationManager;
 class APPSLIBSHARED_EXPORT LocationsTableModel : public AbstractTableModel, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  LocationsTableModel(QObject* parent = 0);
  enum COLUMNS
  {
   // Defines the columns
   ID_COLUMN = 0,
   NAME_COLUMN = 1,
   TRACK_COLUMN = 2,
   NUMBER_COLUMN = 3,
   LENGTH_COLUMN = 4,
   USED_LENGTH_COLUMN = 5,
   ROLLINGSTOCK_COLUMN = 6,
   CARS_COLUMN = 7,
   LOCOS_COLUMN = 8,
   PICKUPS_COLUMN= 9,
   DROPS_COLUMN = 10,
   DIVISION_COLUMN = 11,
   REPORTER_COLUMN = 12,
   ACTION_COLUMN = 13,
   EDIT_COLUMN = 14
  };
  enum SORTOPTIONS
  {
  SORTBYNAME = 1,
  SORTBYID = 2
  };
  /*public*/ void setSort(int sort);
  /*public*/ int rowCount(const QModelIndex &parent) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ void dispose();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ int getRowCount() const override {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() const override {return columnCount(QModelIndex());}
  /*public*/ QString getColumnClass(int col)const override;

  QObject* self() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  LocationManager* locationManager; // There is only one manager
  /*private*/ static /*final*/ int HIGHEST_COLUMN;// = EDITCOLUMN + 1;
  /*private*/ int _sort;// = SORTBYNAME;
  /*private*/ /*synchronized*/ void updateList();
  QList<Location*> locationsList;// = null;
  void initTable(JTable* table);
  QList<LocationEditFrame*> frameList;// = QList<LocationEditFrame*>();
  Logger* log;
  /*private*/ /*synchronized*/ void removePropertyChangeLocations();
  /*private*/ QString getTrackTypes(Location* location) const;
  /*private*/ /*synchronized*/ void editLocation(int row);
  /*private*/ /*synchronized*/ void launchYardmaster(int row);

  friend class LocationsTableFrame;
 };
}
#endif // LOCATIONSTABLEMODEL_H
