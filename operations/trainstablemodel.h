#ifndef TRAINSTABLEMODEL_H
#define TRAINSTABLEMODEL_H
#include "abstracttablemodel.h"
#include "appslib_global.h"
#include <QColor>
#include "trainconductorframe.h"
#include <QPointer>
#include "propertychangelistener.h"

class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class RouteEditFrame;
 class TrainEditFrame;
 class Train;
 class TrainsTableFrame;
 class TrainManager;
 class APPSLIBSHARED_EXPORT TrainsTableModel : public AbstractTableModel, public PropertyChangeListener

 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  // Defines the columns
  enum COLUMNS
  {
   ID_COLUMN = 0,
   TIME_COLUMN = ID_COLUMN + 1,
   BUILD_BOXCOLUMN = TIME_COLUMN + 1,
   BUILD_COLUMN = BUILD_BOXCOLUMN + 1,
   NAME_COLUMN = BUILD_COLUMN + 1,
   DESCRIPTION_COLUMN = NAME_COLUMN + 1,
   BUILT_COLUMN = DESCRIPTION_COLUMN + 1,
   ROAD_COLUMN = BUILT_COLUMN + 1,
   LOAD_COLUMN = ROAD_COLUMN + 1,
   OWNER_COLUMN = LOAD_COLUMN + 1,
   ROUTE_COLUMN = OWNER_COLUMN + 1,
   DEPARTS_COLUMN = ROUTE_COLUMN + 1,
   TERMINATES_COLUMN = DEPARTS_COLUMN + 1,
   CURRENT_COLUMN = TERMINATES_COLUMN + 1,
   STATUS_COLUMN = CURRENT_COLUMN + 1,
   ACTION_COLUMN = STATUS_COLUMN + 1,
   EDIT_COLUMN = ACTION_COLUMN + 1,
   HIGHESTCOLUMN = EDIT_COLUMN + 1
  };
  TrainsTableModel(QObject* parent = 0);
  /*public*/ /*final*/ int SORTBYTIME;// = 2;
  /*public*/ /*final*/ int SORTBYID;// = 7;
  /*public*/ void setSort(int sort);
  /*public*/ void setShowAll(bool showAll);
  /*public*/ bool isShowAll();
  /*public*/ int rowCount(const QModelIndex &parent) const override;
  /*public*/ int columnCount(const QModelIndex &parent) const override;
  /*public*/ QVariant data(const QModelIndex &index, int role) const override;
  /*public*/ static /*final*/ QString IDCOLUMNNAME;//= r("Id");
  /*public*/ static /*final*/ QString TIMECOLUMNNAME;//= r("Time");
  /*public*/ static /*final*/ QString BUILDBOXCOLUMNNAME;//= r("Build");
  /*public*/ static /*final*/ QString BUILDCOLUMNNAME;//= r("Function");
  /*public*/ static /*final*/ QString NAMECOLUMNNAME;//= r("Name");
  /*public*/ static /*final*/ QString DESCRIPTIONCOLUMNNAME;//= r("Description");
  /*public*/ static /*final*/ QString ROUTECOLUMNNAME;//= r("Route");
  /*public*/ static /*final*/ QString DEPARTSCOLUMNNAME;//= r("Departs");
  /*public*/ static /*final*/ QString CURRENTCOLUMNNAME;//= r("Current");
  /*public*/ static /*final*/ QString TERMINATESCOLUMNNAME;//= r("Terminates");
  /*public*/ static /*final*/ QString STATUSCOLUMNNAME;//= r("Status");
  /*public*/ static /*final*/ QString ACTIONCOLUMNNAME;//= r("Action");
  /*public*/ static /*final*/ QString EDITCOLUMNNAME;//= r("Edit");
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const override;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  void initTable(JTable* table, TrainsTableFrame* frame);
  /*public*/ void dispose();
  /*public*/ QColor getRowColor(int row) const;
  /*public*/ int getRowCount()const override {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() const override {return columnCount(QModelIndex());}
  /*public*/ QString getColumnClass(int col) const override;

  QObject* self() override {return (QObject*)this;}
public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  TrainManager* trainManager;// = TrainManager.instance(); // There is only one manager
  /*private*/ int _sort;// = SORTBYTIME;
  /*private*/ bool _showAll;// = true;
  QList<Train*> sysList;// = null;
  JTable* _table;// = null;
  QPointer<TrainsTableFrame> _frame;// = null;
  /*private*/ /*synchronized*/ void removePropertyChangeTrains() ;
  /*private*/ /*synchronized*/ void addPropertyChangeTrains();
  void initTable();
  QPointer<TrainEditFrame> tef;// = NULL;
  /*private*/ /*synchronized*/ void updateList();
  Logger* log;
  //QPointer<RouteEditFrame> ref;// = NULL;
  /*private*/ /*synchronized*/ void editTrain(int row);
  /*private*/ static QHash<QString, TrainConductorFrame*> _trainConductorHashTable;// = new Hashtable<String, TrainConductorFrame>();
  /*private*/ /*synchronized*/ void actionTrain(int row);
  /*private*/ bool checkDepartureTrack(Train* train);
  /*private*/ void launchConductor(Train* train);
  ///*private*/ /*synchronized*/ void editRoute(int row);
  QThread* buildThread;
  /*private*/ /*synchronized*/ void buildTrain(int row);
  QList<QColor> darkColors;// = {Color.BLACK, Color.BLUE, Color.GRAY, Color.RED, Color.MAGENTA};
  /*private*/ QColor getForegroundColor(QColor background) const;
  // Train frame table column widths, starts with id column and ends with edit
  /*private*/ /*final*/ QList<int> _tableColumnWidths = { 50, 50, 50, 72, 100, 140, 50, 50, 50, 50, 120, 120, 120, 120, 120, 90,
          70 };
  /*private*/ void updateColumnVisible();
  /*private*/ QString getBuiltString(Train* train) const;
  /*private*/ QString getModifiedString(int number, bool all, bool accept) const;

 };

 class Build : public QObject
 {
  Q_OBJECT
  TrainsTableModel* parent;
  Train* train;
 public:
  Build(Train* train, TrainsTableModel* parent);
 public slots:
   void process();
  signals:
   void finished();
 };
}
#endif // TRAINSTABLEMODEL_H
