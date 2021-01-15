#ifndef SCHEDULETABLEMODEL_H
#define SCHEDULETABLEMODEL_H

#include "abstracttablemodel.h"
#include "tabledelegates.h"

class QComboBox;
class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class Schedule;
 class Track;
 class Location;
 class ScheduleEditFrame;
 class ScheduleItem;
 class ScheduleTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  ScheduleTableModel(QObject* parent = 0);
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ QString getColumnClass(int col);
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
  /*public*/ void dispose();
  /*public*/ void setMatchMode(bool mode);
  /*public*/ Track* getTrack();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  enum COLUMNS
  {
    ID_COLUMN = 0,
    CURRENT_COLUMN = ID_COLUMN + 1,
    TYPE_COLUMN = CURRENT_COLUMN + 1,
    RANDOM_COLUMN = TYPE_COLUMN + 1,
    SETOUT_DAY_COLUMN = RANDOM_COLUMN + 1,
    ROAD_COLUMN = SETOUT_DAY_COLUMN + 1,
    LOAD_COLUMN = ROAD_COLUMN + 1,
    SHIP_COLUMN = LOAD_COLUMN + 1,
    DEST_COLUMN = SHIP_COLUMN + 1,
    TRACK_COLUMN = DEST_COLUMN + 1,
    PICKUP_DAY_COLUMN = TRACK_COLUMN + 1,
    COUNT_COLUMN = PICKUP_DAY_COLUMN + 1,
    WAIT_COLUMN = COUNT_COLUMN + 1,
    UP_COLUMN = WAIT_COLUMN + 1,
    DOWN_COLUMN = UP_COLUMN + 1,
    DELETE_COLUMN = DOWN_COLUMN + 1,

    HIGHEST_COLUMN = DELETE_COLUMN + 1
  };
  Schedule* _schedule;
  Location* _location;
  Track* _track;
  JTable* _table;
  ScheduleEditFrame * _frame;
  bool _matchMode;// = false;
  /*synchronized*/ void updateList();
  QList<ScheduleItem*> _list;// = new ArrayList<ScheduleItem>();
  void initTable(ScheduleEditFrame* frame, JTable* table, Schedule* schedule, Location* location, Track* track);
  /*private*/ void initTable(JTable* table);
  /*private*/ void removePropertyChangeScheduleItems();
  Logger* log;
  /*private*/ QString getCurrentPointer(ScheduleItem* si) const;
  /*private*/ QString getType(ScheduleItem* si) const;
  ///*private*/ QComboBox* getRoadComboBox(ScheduleItem* si);
  ///*private*/ QComboBox* getLoadComboBox(ScheduleItem* si);
  //private*/ void filterLoads(ScheduleItem* si, QComboBox* cb);
  /*private*/ void setPreferredWidths(JTable* table);
  QStringList randomValues;// = {ScheduleItem.NONE, "50", "30", "25", "20", "15", "10", "5", "2", "1"};  // NOI18N
  /*private*/ void setCount(QVariant value, int row);
  /*private*/ void setWait(QVariant value, int row);
  /*private*/ void moveUpScheduleItem(int row);
  /*private*/ void moveDownScheduleItem(int row) ;
  /*private*/ void deleteScheduleItem(int row);
  /*private*/ void filterLoads(ScheduleItem* si, QComboBox* cb); // Note: must be public!
  /*private*/ void filterDestinations(QComboBox* cb, QString carType); // needs to be public
  /*private*/ void filterTracks(Location* loc, QComboBox* cb, QString carType, QString carRoad, QString carLoad);
  /*private*/ QComboBox* getRandomComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getSetoutDayComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getRoadComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getLoadComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getPickupDayComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getShipComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getDestComboBox(ScheduleItem* si);
  /*private*/ QComboBox* getTrackComboBox(ScheduleItem* si);
  /*private*/ void setRandom(QVariant value, int row);
  /*private*/ void setSetoutDay(QVariant value, int row) ;
  /*private*/ void setPickupDay(QVariant value, int row);
  /*private*/ void setRoad(QVariant value, int row);
  /*private*/ void setLoad(QVariant value, int row);
  /*private*/ void setShip(QVariant value, int row);
  /*private*/ bool checkForNotValidString(QString s);
  /*private*/ void setDestination(QVariant value, int row);
  /*private*/ void setTrack(QVariant value, int row);

  friend class ScheduleEditFrame;
  friend class STMComboBoxDelegate;
 };

 typedef QComboBox* (*GETCOMBO)(ScheduleItem*, ScheduleTableModel* );
 class STMComboBoxDelegate : public JComboBoxEditor
 {
 Q_OBJECT
 public:
   STMComboBoxDelegate(ScheduleTableModel* model, QObject *parent = 0);
   QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
//   void setEditorData(QWidget *editor, const QModelIndex &index) const;
//   void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
//   void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
   //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

 private:
   ScheduleTableModel* model;
   QStringList items;
   QComboBox* (*box)(ScheduleItem*, ScheduleTableModel*);

 };

}
#endif // SCHEDULETABLEMODEL_H
