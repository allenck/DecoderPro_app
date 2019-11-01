#ifndef TRAINSTABLEMODEL_H
#define TRAINSTABLEMODEL_H
#include "abstracttablemodel.h"
#include "appslib_global.h"
#include <QColor>

class Logger;
class PropertyChangeEvent;
namespace Operations
{
 class TrainConductorFrame;
 class RouteEditFrame;
 class TrainEditFrame;
 class Train;
 class TrainsTableFrame;
 class TrainManager;
 class APPSLIBSHARED_EXPORT TrainsTableModel : public AbstractTableModel
 {
  Q_OBJECT
 public:
  // Defines the columns
  enum COLUMNS
  {
   IDCOLUMN = 0,
   BUILDBOXCOLUMN = IDCOLUMN + 1,
   BUILDCOLUMN = BUILDBOXCOLUMN + 1,
   NAMECOLUMN = BUILDCOLUMN + 1,
   DESCRIPTIONCOLUMN = NAMECOLUMN + 1,
   ROUTECOLUMN = DESCRIPTIONCOLUMN + 1,
   DEPARTSCOLUMN = ROUTECOLUMN + 1,
   TERMINATESCOLUMN = DEPARTSCOLUMN + 1,
   CURRENTCOLUMN = TERMINATESCOLUMN + 1,
   STATUSCOLUMN = CURRENTCOLUMN + 1,
   ACTIONCOLUMN = STATUSCOLUMN + 1,
   EDITCOLUMN = ACTIONCOLUMN + 1,
   HIGHESTCOLUMN = EDITCOLUMN + 1
  };
  TrainsTableModel(QObject* parent = 0);
  /*public*/ /*final*/ int SORTBYTIME;// = 2;
  /*public*/ /*final*/ int SORTBYID;// = 7;
  /*public*/ void setSort(int sort);
  /*public*/ void setShowAll(bool showAll);
  /*public*/ bool isShowAll();
  /*public*/ int rowCount(const QModelIndex &parent) const;
  /*public*/ int columnCount(const QModelIndex &parent) const;
  /*public*/ QVariant data(const QModelIndex &index, int role) const;
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
  /*public*/ QVariant headerData(int section, Qt::Orientation orientation, int role) const;
  /*public*/ Qt::ItemFlags flags(const QModelIndex &index) const;
  /*public*/ bool setData(const QModelIndex &index, const QVariant &value, int role);
  void initTable(JTable* table, TrainsTableFrame* frame);
  /*public*/ void dispose();
  /*public*/ QColor getRowColor(int row) const;
  /*public*/ int getRowCount() {return rowCount(QModelIndex());}
  /*public*/ int getColumnCount() {return columnCount(QModelIndex());}

public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  TrainManager* trainManager;// = TrainManager.instance(); // There is only one manager
  /*private*/ int _sort;// = SORTBYTIME;
  /*private*/ bool _showAll;// = true;
  QList<Train*> sysList;// = null;
  JTable* _table;// = null;
  TrainsTableFrame* _frame;// = null;
  /*private*/ /*synchronized*/ void removePropertyChangeTrains() ;
  /*private*/ /*synchronized*/ void addPropertyChangeTrains();
  void initTable();
  TrainEditFrame* tef;// = NULL;
  /*private*/ /*synchronized*/ void updateList();
  Logger* log;
  RouteEditFrame* ref;// = NULL;
  /*private*/ /*synchronized*/ void editTrain(int row);
  /*private*/ static QHash<QString, TrainConductorFrame*> _trainConductorHashTable;// = new Hashtable<String, TrainConductorFrame>();
  /*private*/ /*synchronized*/ void actionTrain(int row);
  /*private*/ bool checkDepartureTrack(Train* train);
  /*private*/ void launchConductor(Train* train);
  /*private*/ /*synchronized*/ void editRoute(int row);
  QThread* buildThread;
  /*private*/ /*synchronized*/ void buildTrain(int row);
  QList<QColor> darkColors;// = {Color.BLACK, Color.BLUE, Color.GRAY, Color.RED, Color.MAGENTA};
  /*private*/ QColor getForegroundColor(QColor background) const;

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
