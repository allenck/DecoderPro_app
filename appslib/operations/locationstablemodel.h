#ifndef LOCATIONSTABLEMODEL_H
#define LOCATIONSTABLEMODEL_H

#include "abstracttablemodel.h"
#include "appslib_global.h"

class Logger;
class PropertyChangeEvent;
namespace Operations {
 class LocationEditFrame;
 class Location;
 class LocationManager;
 class APPSLIBSHARED_EXPORT LocationsTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  LocationsTableModel(QObject* parent = 0);
  enum COLUMNS
  {
   // Defines the columns
   IDCOLUMN = 0,
   NAMECOLUMN = 1,
   TRACKCOLUMN = 2,
   LENGTHCOLUMN = 3,
   USEDLENGTHCOLUMN = 4,
   ROLLINGSTOCK = 5,
   PICKUPS = 6,
   DROPS = 7,
   ACTIONCOLUMN = 8,
   EDITCOLUMN = 9
  };
  enum SORTOPTIONS
  {
  SORTBYNAME = 1,
  SORTBYID = 2
  };
  /*public*/ void setSort(int sort);
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ void dispose();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  LocationManager* locationManager; // There is only one manager
  /*private*/ static /*final*/ int HIGHESTCOLUMN;// = EDITCOLUMN + 1;
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
