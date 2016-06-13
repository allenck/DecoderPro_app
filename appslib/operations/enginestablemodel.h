#ifndef ENGINESTABLEMODEL_H
#define ENGINESTABLEMODEL_H
#include "abstracttablemodel.h"
#include "appslib_global.h"

class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class EngineEditFrame;
 class EngineSetFrame;
 class EnginesTableFrame;
 class RollingStock;
 class EngineManager;
 class APPSLIBSHARED_EXPORT EnginesTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  explicit EnginesTableModel(QObject *parent = 0);
 enum SORTOPTIONS
 {
   SORTBYNUMBER = 1,
   SORTBYROAD = 2,
   SORTBYMODEL = 3,
   SORTBYLOCATION = 4,
   SORTBYDESTINATION = 5,
   SORTBYTRAIN = 6,
   SORTBYMOVES = 7,
   SORTBYCONSIST = 8,
   SORTBYBUILT = 9,
   SORTBYOWNER = 10,
   SORTBYVALUE = 11,
   SORTBYRFID = 12,
   SORTBYLAST = 13,
   SORTBYHP = 14
 };
 /*public*/ QList<RollingStock*>* getSelectedEngineList();
 /*public*/ int rowCount(const QModelIndex &parent) const;
 /*public*/ int columnCount(const QModelIndex &parent) const;
 /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
 /*public*/ QVariant data(const QModelIndex &index, int role) const;
 /*public*/ void dispose() ;
 /*public*/ void setSort(int sort);
 /*public*/ int findEngineByRoadNumber(QString roadNumber);
 /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);

 signals:

 public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:

  enum COLUMNS
  {
   // Defines the columns
    NUM_COLUMN = 0,
    ROAD_COLUMN = 1,
    MODEL_COLUMN = 2,
    HP_COLUMN = 3,
    TYPE_COLUMN = 4,
    LENGTH_COLUMN = 5,
    CONSIST_COLUMN = 6,
    LOCATION_COLUMN = 7,
    DESTINATION_COLUMN = 8,
    TRAIN_COLUMN = 9,
    MOVES_COLUMN = 10,
    SET_COLUMN = 11,
    EDIT_COLUMN = 12,

    HIGHEST_COLUMN = EDIT_COLUMN + 1
  };
 enum SHOW
 {
    SHOWMOVES = 0,
    SHOWBUILT = 1,
    SHOWOWNER = 2,
    SHOWVALUE = 3,
    SHOWRFID = 4,
    SHOWLAST = 5
  };
 /*private*/ int showMoveCol;// = SHOWMOVES;

 /*private*/ int _sort;// = SORTBYNUMBER;
 static EngineManager* manager;// = EngineManager.instance(); // There is only one manager
 QString _roadNumber;// = "";
 int _index;// = 0;
 QList<RollingStock*>* sysList;// = null;

 JTable* _table;
 EnginesTableFrame* _frame;
 /*synchronized*/ void updateList();
 /*private*/ void removePropertyChangeEngines();
 EngineEditFrame* eef;// = NULL;
 EngineSetFrame* esf;// = NULL;
 Logger* log;
 // Engines frame table column widths (12), starts with Number column and ends with Edit
 /*private*/ QList<int> _enginesTableColumnWidths;// = {60, 60, 65, 50, 65, 35, 75, 190, 190, 65, 50, 65, 70};
 void initTable(JTable* table, EnginesTableFrame* frame);
 void initTable();
 friend class EnginesTableFrame;
 /*private*/ int getIndex(int start, QString roadNumber);

 };
}
#endif // ENGINESTABLEMODEL_H
