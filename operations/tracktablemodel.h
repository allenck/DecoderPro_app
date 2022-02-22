#ifndef TRACKTABLEMODEL_H
#define TRACKTABLEMODEL_H

#include "abstracttablemodel.h"
#include "appslib_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class Logger;
namespace Operations
{
 class TrackEditFrame;
 class Track;
 class Location;
 class APPSLIBSHARED_EXPORT TrackTableModel : public AbstractTableModel, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  TrackTableModel(QObject* parent = 0);
  enum SORTOPTS
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
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  /*public*/ void dispose();
  QObject* pself() override {return (QObject*)this; }

 public slots:
  /*public*/ virtual void propertyChange(PropertyChangeEvent* e) override;

 private:
  Logger* log;
  /*synchronized*/ virtual void updateList();
  /*private*/ virtual void initTable();
  /*private*/ QString getModifiedString(int number, bool all, bool accept) const;
  TrackEditFrame* tef;// = NULL;

 protected:
  enum COLUMNS
  {
   // Defines the columns
     ID_COLUMN = 0,
     NAME_COLUMN = 1,
     LENGTH_COLUMN = 2,
     USED_LENGTH_COLUMN = 3,
     RESERVED_COLUMN = 4,
     CARS_COLUMN = 5,
     LOCOS_COLUMN = 6,
     PICKUPS_COLUMN = 7,
     SETOUT_COLUMN = 8,
     ROAD_COLUMN = 9,
     LOAD_COLUMN = 10,
     SHIP_COLUMN = 11,
     DESTINATION_COLUMN = 12,
     POOL_COLUMN = 13,
     PLANPICKUP_COLUMN = 14,
     ALT_TRACK_COLUMN = 15,
     EDIT_COLUMN = 16,

     HIGHESTCOLUMN = EDIT_COLUMN + 1,
  };
  /*protected*/ Location* _location;
  /*protected*/ QList<Track*> tracksList;// = new ArrayList<Track>();
  /*protected*/ int _sort;// = SORTBYNAME;
  /*protected*/ QString _trackType;// = "";
  /*protected*/ bool _showPoolColumn;// = false;
  /*protected*/ JTable* _table;
  /*protected*/ virtual void initTable(JTable* table, Location* location, QString trackType);
   /*protected*/ void setColumnsVisible();
  /*protected*/ void removePropertyChangeTracks();
  /*protected*/ virtual void editTrack(int row);

  friend class YardTableModel;
  friend class SpurTableModel;
  friend class InterchangeTableModel;
  friend class StagingTableModel;
 };
}
#endif // TRACKTABLEMODEL_H
