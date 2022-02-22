#ifndef CARSTABLEMODEL_H
#define CARSTABLEMODEL_H

#include "abstracttablemodel.h"
#include <QList>
#include <QItemDelegate>
#include "appslib_global.h"
#include "propertychangelistener.h"

class PropertyChangeEvent;
class Logger;
namespace Operations
{
 class Car;
 class CarSetFrame;
 class CarEditFrame;
 class RollingStock;
 class CarsTableFrame;
 class CarManager;
 class APPSLIBSHARED_EXPORT CarsTableModel : public AbstractTableModel, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  //CarsTableModel(PropertyChangeListener);
  /*public*/ CarsTableModel(bool showAllCars, QString locationName, QString trackName, QObject* parent =0);
  enum SORTOPTIONS
  {
  SORTBY_NUMBER = 0,
  SORTBY_ROAD = 1,
  SORTBY_TYPE = 2,
  SORTBY_LOCATION = 3,
  SORTBY_DESTINATION = 4,
  SORTBY_TRAIN = 5,
  SORTBY_MOVES = 6,
  SORTBY_KERNEL = 7,
  SORTBY_LOAD = 8,
  SORTBY_COLOR = 9,
  SORTBY_BUILT = 10,
  SORTBY_OWNER = 11,
  SORTBY_RFID = 12,
  SORTBY_RWE = 13, // return when empty
  SORTBY_RWL = 14,
  SORTBY_DIVISION = 15,
  SORTBY_FINALDESTINATION = 16,
  SORTBY_VALUE = 17,
  SORTBY_WAIT = 18,
  SORTBY_PICKUP = 19,
  SORTBY_LAST = 20
  };

  /*public*/ int rowCount(const QModelIndex &parent) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  void initTable(JTable* table, CarsTableFrame* frame);
  /*public*/ void toggleSelectVisible();
  /*public*/ QList<Car *> *getSelectedCarList();
  /*public*/ QList<Car *> *getCarList(int sort);
  /*public*/ void setSort(int sort);
  /*public*/ QString getSortByName();
  /*public*/ QString getSortByName(int sort);
  /*public*/ void resetCheckboxes();
  /*public*/ int findCarByRoadNumber(QString roadNumber);
  /*public*/ Car* getCarAtIndex(int index);
  /*public*/ void dispose();
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  QObject* pself() override {return (QObject*)this; }

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;
  /*public*/ void setColumnToHoldButton(JTable* table, int column, QPushButton* /*sample*/);
  /*public*/ int getRowCount() const  override{return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() const  override{return columnCount(QModelIndex());}

 private:
  CarManager* manager;// = CarManager.instance(); // There is only one manager
  // Defines the columns
  enum COLUMNS
  {
  SELECT_COLUMN = 0,
  NUMBER_COLUMN = 1,
  ROAD_COLUMN = 2,
  TYPE_COLUMN = 3,
  LENGTH_COLUMN = 4,
  LOAD_COLUMN = 5,
  RWE_LOAD_COLUMN = 6,
  RWL_LOAD_COLUMN =7,
  COLOR_COLUMN = 8,
  KERNEL_COLUMN = 9,
  LOCATION_COLUMN = 10,
  RFID_WHERE_LAST_SEEN_COLUMN = 11,
  RFID_WHEN_LAST_SEEN_COLUMN = 12,
  DESTINATION_COLUMN = 13,
  FINAL_DESTINATION_COLUMN = 14,
  RWE_DESTINATION_COLUMN = 15,
  RWL_DESTINATION_COLUMN = 16,
  DIVISION_COLUMN = 17,
  TRAIN_COLUMN = 18,
  MOVES_COLUMN = 19,
  BUILT_COLUMN = 20,
  OWNER_COLUMN = 21,
  VALUE_COLUMN = 22,
  RFID_COLUMN = 23,
  WAIT_COLUMN = 24,
  PICKUP_COLUMN = 25,
  LAST_COLUMN = 26,
  SET_COLUMN = 27,
  EDIT_COLUMN = 28,

  HIGHESTCOLUMN  = EDIT_COLUMN + 1
  };
  /*private*/ int _sort;// = SORTBY_NUMBER;

  //QList<RollingStock*>* sysList;// = null; // list of cars
  QList<Car*>* carList = nullptr; // list of cars
  bool showAllCars;// = true; // when true show all cars
  QString locationName;// = null; // only show cars with this location
  QString trackName;// = null; // only show cars with this track
  JTable*_table;
  CarsTableFrame*_frame;
  void initTable();
  /*private*/ static bool isSelectVisible;// = false;
  CarEditFrame* cef;// = NULL;
  CarSetFrame* csf;// = NULL;
  /*synchronized*/ void updateList();
  /*private*/ void addPropertyChangeCars();
  /*private*/ void removePropertyChangeCars();
  /*private*/ void filterList(QList<RollingStock*>* list);
  QString _roadNumber;// = "";
  int _index;// = 0;
  /*private*/ int getIndex(int start, QString roadNumber);
  Logger* log;

 friend class CarsTableFrame;
 friend class DeleteCarRosterAction;
 };
}
#endif // CARSTABLEMODEL_H
