#ifndef TRAINMANAGER_H
#define TRAINMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include "propertychangesupport.h"
#include "logger.h"
#include "jcombobox.h"
#include "appslib_global.h"
#include "instancemanagerautodefault.h"
#include "instancemanagerautoinitialize.h"
#include "runnable.h"
#include "train.h"

class PrintWriter;
class QDomDocument;
class QDomElement;
namespace Operations
{
 class Location;
 class Car;
 class Train;
 class APPSLIBSHARED_EXPORT TrainManager : public PropertyChangeSupport, public InstanceManagerAutoDefault, public InstanceManagerAutoInitialize
 {
  Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault InstanceManagerAutoInitialize)

 public:
  Q_INVOKABLE explicit TrainManager(QObject *parent = 0);
   ~TrainManager() {}
   TrainManager(const TrainManager&) : PropertyChangeSupport(this) {}
  // property changes
  /*public*/ static /*final*/ QString LISTLENGTH_CHANGED_PROPERTY;// = "TrainsListLength"; // NOI18N
  /*public*/ static /*final*/ QString PRINTPREVIEW_CHANGED_PROPERTY;// = "TrainsPrintPreview"; // NOI18N
  /*public*/ static /*final*/ QString OPEN_FILE_CHANGED_PROPERTY;// = "TrainsOpenFile"; // NOI18N
  /*public*/ static /*final*/ QString RUN_FILE_CHANGED_PROPERTY;// = "TrainsRunFile"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_ACTION_CHANGED_PROPERTY;// = "TrainsAction"; // NOI18N
  /*public*/ static /*final*/ QString ACTIVE_TRAIN_SCHEDULE_ID;// = "ActiveTrainScheduleId"; // NOI18N
  /*public*/ static /*final*/ QString ROW_COLOR_NAME_CHANGED_PROPERTY;// = "TrainsRowColorChange"; // NOI18N
  /*public*/ static /*final*/ QString TRAINS_BUILT_CHANGED_PROPERTY;// = "TrainsBuiltChange"; // NOI18N
  /*public*/ int getNumEntries();
  /*public*/ bool isBuildMessagesEnabled();
  /*public*/ void setBuildMessagesEnabled(bool enable);
  /*public*/ JComboBox* getTrainComboBox();
  /*public*/ void updateTrainComboBox(JComboBox* box);
  /*public*/ QList<Train*> getTrainsByNameList();
  /*public*/ Train* getTrainByName(QString name);
  /*public*/ Train* getTrainById(QString id);
  /*public*/ Train* newTrain(QString name);
  /*public*/ void _register(Train* train);
  /*public*/ void deregister(Train* train);
  /*public*/ void loadTrainIcons();
  /*public*/ QList<Train*> getTrainsByIdList();
  /*public*/ void load(QDomElement root);
  /*public*/ void store(QDomElement root, QDomDocument doc);
  /*public*/ QStringList getStartUpScripts() ;
  /*public*/ void runStartUpScripts();
  /*public*/ void addShutDownScript(QString pathname);
  /*public*/ void deleteShutDownScript(QString pathname);
  /*public*/ QStringList getShutDownScripts();
  PropertyChangeSupport* pcs;// = new java.beans.PropertyChangeSupport(this);
  /*public*/ void updateTrainComboBox(JComboBox* box, Car* car);
  /*public*/ int numEntries();
  /*public*/ QList<Train*> getTrainsArrivingThisLocationList(Location* location);
  /*public*/ QList<Train*> getTrainsByTimeList();
  /*public*/ QString getTrainsFrameTrainAction();
  /*public*/ bool isBuildReportEnabled();
  /*public*/ bool isPrintPreviewEnabled();
  /*public*/ bool isOpenFileEnabled();
  /*public*/ void setOpenFileEnabled(bool enable);
  /*public*/ bool isRunFileEnabled();
  /*public*/ QList<int> getTrainsFrameTableColumnWidths();
  /*public*/ void replaceLoad(QString type, QString oldLoadName, QString newLoadName);
  /*public*/ bool isAnyTrainBuilt();
 /*public*/ bool isAnyTrainBuilding();
  /*public*/ bool terminateSelectedTrains(QList<Train*> trains);
  /*public*/ void setBuildReportEnabled(bool enable);
  /*public*/ void setRunFileEnabled(bool enable);
  /*public*/ void setPrintPreviewEnabled(bool enable);
  /*public*/ void setTrainsFrameTrainAction(QString action);
  /*public*/ void runShutDownScripts();
  /*public*/ void dispose();
  /*public*/ bool isRowColorManual();
  /*public*/ void setRowColorsManual(bool manual) ;
  /*public*/ QString getRowColorNameForBuilt();
  /*public*/ void setRowColorNameForBuilt(QString colorName);
  /*public*/ QString getRowColorNameForBuildFailed();
  /*public*/ void setRowColorNameForBuildFailed(QString colorName);
  /*public*/ QString getRowColorNameForTrainEnRoute();
  /*public*/ void setRowColorNameForTrainEnRoute(QString colorName);
  /*public*/ QString getRowColorNameForTerminated();
  /*public*/ void setRowColorNameForTerminated(QString colorName);
  /*public*/ JComboBox* getRowColorComboBox();
  /*public*/ Train* copyTrain(Train* train, QString trainName);
  /*public*/ QString getTrainScheduleActiveId();
  /*public*/ bool printSelectedTrains(QList<Train*> trains);
  /*public*/ void setTrainsSwitchListStatus(QString status);
  /*public*/ void setTrainsModified();
  /*public*/ void buildSelectedTrains(/*final*/QList<Train*> trains);
  /*public*/ QList<Train*> getTrainsByDepartureList();
  /*public*/ QList<Train*> getTrainsByTerminatesList();
  /*public*/ QList<Train*> getTrainsByRouteList();
  /*public*/ QList<Train*> getTrainsByStatusList();
  /*public*/ Train* getTrainForCar(Car* car, PrintWriter* buildReport) ;
  /*public*/ Train* getTrainForCar(Car* car, Train* excludeTrain, PrintWriter* buildReport);
  /*public*/ QList<int> getTrainScheduleFrameTableColumnWidths();
  /*public*/ void setTrainSecheduleActiveId(QString id);
  /*public*/ void addStartUpScript(QString pathname) ;
  /*public*/ void deleteStartUpScript(QString pathname);
  Q_INVOKABLE /*public*/ void initialize();

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  Logger* log;
  /*private*/ static /*final*/ QString NONE;// = "";
  // Train frame attributes
  /*private*/ QString _trainAction;// = TrainsTableFrame.MOVE; // Trains frame table button action
  /*private*/ bool _buildMessages;// = true; // when true, show build messages
  /*private*/ bool _buildReport;// = false; // when true, print/preview build reports
  /*private*/ bool _printPreview;// = false; // when true, preview train manifest
  /*private*/ bool _openFile;// = false; // when true, open CSV file manifest
  /*private*/ bool _runFile;// = false; // when true, run CSV file manifest

  // Trains window row colors
  /*private*/ bool _rowColorManual;// = true; // when true train colors are manually assigned;// = NONE; // row color when train is built
  /*private*/ QString _rowColorBuilt;// = NONE; // row color when train is built
  /*private*/ QString _rowColorBuildFailed;// = NONE; // row color when train build failed
  /*private*/ QString _rowColorTrainEnRoute;// = NONE; // row color when train is en route
  /*private*/ QString _rowColorTerminated;// = NONE; // row color when train is terminated

  // Train frame table column widths (12), starts with Time column and ends with Edit
  /*private*/ QList<int> _tableColumnWidths;// = {50, 50, 72, 100, 140, 120, 120, 120, 120, 120, 90, 70};

  /*private*/ QList<int>_tableScheduleColumnWidths;// = {50, 70, 120};
  /*private*/ QString _trainScheduleActiveId;// = NONE;
  /*private*/ int _id;// = 0; // train ids
  // stores known Train instances by id
  /*private*/ QMap<QString, Train*> _trainHashTable;// = new Hashtable<QString, Train>();
  /*private*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*private*/ QList<Train*> getTrainsByList(QList<Train*> sortList, int attribute);
  enum SORTOPTIONS
  {
   // the various sort options for trains
   GET_TRAIN_DEPARTES_NAME = 0,
   GET_TRAIN_NAME = 1,
   GET_TRAIN_ROUTE_NAME = 2,
   GET_TRAIN_TERMINATES_NAME = 3,
   GET_TRAIN_TIME = 4,
   GET_TRAIN_STATUS = 5,
   GET_TRAIN_ID = 6
  };
  /*private*/ QVariant getTrainAttribute(Train* train, int attribute);
  /*private*/ QList<Train*> getList();
  /*private*/ QList<Train*> getTrainsByIntList(QList<Train*> sortList, int attribute);

 private slots:
  void onError(QString title, QString msg);

 protected:
  // Scripts
  /*protected*/ QStringList _startUpScripts;// = new ArrayQStringList(); // list of script pathnames to run at start up
  /*protected*/ QStringList _shutDownScripts;// = new ArrayQStringList(); // list of script pathnames to run at shut down
//  /*private*/ static TrainManager* _instance;// = null;
 friend class MyBuild;
 friend class TMRunnable;
 };

 class MyBuild : public QObject
 {
  Q_OBJECT
  TrainManager* parent;
  QList<Train*> trains;
 public:
   MyBuild(QList<Train*> trains, TrainManager* parent);
 public slots:
   void process();

 signals:
   void finished();
   void error(QString title, QString msg);
 };

 class TMRunnable : public Runnable
 {
   Q_OBJECT
   QList<Train*> trains;
   TrainManager* tm;
  public:
   TMRunnable(QList<Train*> trains, TrainManager* tm) {
    this->trains = trains;
   this->tm = tm;
   }
   /*public*/ void run() {
       for (Train* train : trains) {
           train->buildIfSelected();
       }
       tm->setDirtyAndFirePropertyChange(TrainManager::TRAINS_BUILT_CHANGED_PROPERTY, false, true);
   }
 };
} // end operations
Q_DECLARE_METATYPE(Operations::TrainManager)
#endif // TRAINMANAGER_H
