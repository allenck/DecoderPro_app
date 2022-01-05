#include "trainmanager.h"
#include "operationssetupxml.h"
#include "trainmanagerxml.h"
#include "train.h"
#include "control.h"
#include "propertychangesupport.h"
#include "jcombobox.h"
#include "rosterentry.h"
#include <QStringList>
#include "xml.h"
#include "location.h"
#include "routelocation.h"
#include "traincommon.h"
#include "route.h"
#include "carload.h"
#include <QMessageBox>
#include "trainstableframe.h"
#include "setup.h"
#include <QThread>
#include "car.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "traincustommanifest.h"
#include "traincustomswitchlist.h"

//TrainManager::TrainManager(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Manages trains.
 *
 * @author Bob Jacobsen Copyright (C) 2003
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 * 2014
 * @version $Revision: 29897 $
 */
// /*public*/ class TrainManager implements java.beans.PropertyChangeListener {
namespace Operations
{
 /*private*/ /*static*/ /*final*/ QString
 TrainManager::NONE = "";


 // property changes
 /*public*/ /*static*/ /*final*/ QString TrainManager::LISTLENGTH_CHANGED_PROPERTY = "TrainsListLength"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::PRINTPREVIEW_CHANGED_PROPERTY = "TrainsPrintPreview"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::OPEN_FILE_CHANGED_PROPERTY = "TrainsOpenFile"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::RUN_FILE_CHANGED_PROPERTY = "TrainsRunFile"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::TRAIN_ACTION_CHANGED_PROPERTY = "TrainsAction"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::ACTIVE_TRAIN_SCHEDULE_ID = "ActiveTrainScheduleId"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::ROW_COLOR_NAME_CHANGED_PROPERTY = "TrainsRowColorChange"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::TRAINS_BUILT_CHANGED_PROPERTY = "TrainsBuiltChange"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString TrainManager::TRAINS_SHOW_FULL_NAME_PROPERTY = "TrainsShowFullName"; // NOI18N

 /*public*/ TrainManager::TrainManager(QObject *parent) :
 PropertyChangeSupport(this, parent)
 {
  setObjectName("TrainManager");
  // Train frame attributes
  _trainAction = TrainsTableFrame::MOVE; // Trains frame table button action
  _buildMessages = true; // when true, show build messages
  _buildReport = false; // when true, print/preview build reports
  _printPreview = false; // when true, preview train manifest
  _openFile = false; // when true, open CSV file manifest
  _runFile = false; // when true, run CSV file manifest
  setProperty("InstanceManagerAutoDefault", "true");
  setProperty("InstanceManagerAutoInitialize", "true");


  // Trains window row colors
  _rowColorManual = true; // when true train colors are manually assigned
  _rowColorBuilt = NONE; // row color when train is built
  _rowColorBuildFailed = NONE; // row color when train build failed
  _rowColorTrainEnRoute = NONE; // row color when train is en route

  // Train frame table column widths (12), starts with Time column and ends with Edit
  _tableColumnWidths = QList<int>() << 50 << 50<< 72<< 100<< 140<< 120<< 120<< 120<< 120<< 120<< 90<< 70;

  _tableScheduleColumnWidths = QList<int>() << 50<< 70<< 120;
  _trainScheduleActiveId = NONE;

 /*protected*/
  // Scripts
  _startUpScripts =  QStringList(); // list of script pathnames to run at start up
  _shutDownScripts =  QStringList(); // list of script pathnames to run at shut down
  _id = 0; // train ids
  // stores known Train instances by id
  _trainHashTable = QMap<QString, Train*>();
  //pcs = new PropertyChangeSupport(this);


 }

 /**
  * Get the number of items in the roster
  *
  * @return Number of trains in the roster
  */
 /*public*/ int TrainManager::getNumEntries() {
     return _trainHashTable.size();
 }

 /**
  *
  * @return true if build messages are enabled
  */
 /*public*/ bool TrainManager::isBuildMessagesEnabled() {
     return _buildMessages;
 }

 /*public*/ void TrainManager::setBuildMessagesEnabled(bool enable) {
    bool old = _buildMessages;
    _buildMessages = enable;
    setDirtyAndFirePropertyChange("BuildMessagesEnabled", enable, old); // NOI18N
 }

 /**
  *
  * @return true if build reports are enabled
  */
 /*public*/ bool TrainManager::isBuildReportEnabled() {
     return _buildReport;
 }

 /*public*/ void TrainManager::setBuildReportEnabled(bool enable) {
     bool old = _buildReport;
     _buildReport = enable;
     setDirtyAndFirePropertyChange("BuildReportEnabled", enable, old); // NOI18N
 }

 /**
  *
  * @return true if open file is enabled
  */
 /*public*/ bool TrainManager::isOpenFileEnabled() {
     return _openFile;
 }

 /*public*/ void TrainManager::setOpenFileEnabled(bool enable) {
     bool old = _openFile;
     _openFile = enable;
     setDirtyAndFirePropertyChange(OPEN_FILE_CHANGED_PROPERTY, old ? "true" : "false", enable ? "true" // NOI18N
             : "false"); // NOI18N
 }

 /**
  *
  * @return true if open file is enabled
  */
 /*public*/ bool TrainManager::isRunFileEnabled() {
     return _runFile;
 }

 /*public*/ void TrainManager::setRunFileEnabled(bool enable) {
     bool old = _runFile;
     _runFile = enable;
     setDirtyAndFirePropertyChange(RUN_FILE_CHANGED_PROPERTY, old ? "true" : "false", enable ? "true" // NOI18N
             : "false"); // NOI18N
 }

 /**
  *
  * @return true if print preview is enabled
  */
 /*public*/ bool TrainManager::isPrintPreviewEnabled() {
     return _printPreview;
 }

 /*public*/ void TrainManager::setPrintPreviewEnabled(bool enable) {
     bool old = _printPreview;
     _printPreview = enable;
     setDirtyAndFirePropertyChange(PRINTPREVIEW_CHANGED_PROPERTY, old ? "Preview" : "Print", // NOI18N
             enable ? "Preview" : "Print"); // NOI18N
 }

// /*public*/ QString TrainManager::getTrainsFrameTrainAction() {
//     return _trainAction;
// }

// /*public*/ void TrainManager::setTrainsFrameTrainAction(QString action) {
//     QString old = _trainAction;
//     _trainAction = action;
//     if (old!=(action)) {
//         setDirtyAndFirePropertyChange(TRAIN_ACTION_CHANGED_PROPERTY, old, action);
//     }
// }

// /**
//  *
//  * @return get an array of table column widths for the trains frame
//  */
// /*public*/ QList<int> TrainManager::getTrainsFrameTableColumnWidths()
// {
//     //return _tableColumnWidths.clone();
//  return QList<int>(_tableColumnWidths);
// }

// /*public*/ QList<int> TrainManager::getTrainScheduleFrameTableColumnWidths() {
//     //return _tableScheduleColumnWidths.clone();
//  return QList<int>(_tableScheduleColumnWidths);
// }

// /**
//  * Sets the selected schedule id
//  *
//  * @param id Selected schedule id
//  */
// /*public*/ void TrainManager::setTrainSecheduleActiveId(QString id) {
//     QString old = _trainScheduleActiveId;
//     _trainScheduleActiveId = id;
//     if (old!=(id)) {
//         setDirtyAndFirePropertyChange(ACTIVE_TRAIN_SCHEDULE_ID, old, id);
//     }
// }

// /*public*/ QString TrainManager::getTrainScheduleActiveId() {
//     return _trainScheduleActiveId;
// }

 /**
  * When true show entire location name including hyphen
  *
  * @return true when showing entire location name
  */
 /*public*/ bool TrainManager::isShowLocationHyphenNameEnabled() {
     return _showLocationHyphenName;
 }

 /*public*/ void TrainManager::setShowLocationHyphenNameEnabled(bool enable) {
     bool old = _showLocationHyphenName;
     _showLocationHyphenName = enable;
     setDirtyAndFirePropertyChange(TRAINS_SHOW_FULL_NAME_PROPERTY, old, enable);
 }

 /*public*/ QString TrainManager::getTrainsFrameTrainAction() {
     return _trainAction;
 }

 /*public*/ void TrainManager::setTrainsFrameTrainAction(QString action) {
     QString old = _trainAction;
     _trainAction = action;
     if (old!=(action)) {
         setDirtyAndFirePropertyChange(TRAIN_ACTION_CHANGED_PROPERTY, old, action);
     }
 }
 /**
  * Add a script to run after trains have been loaded
  *
  * @param pathname The script's pathname
  */
 /*public*/ void TrainManager::addStartUpScript(QString pathname) {
     _startUpScripts.append(pathname);
     setDirtyAndFirePropertyChange("addStartUpScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void TrainManager::deleteStartUpScript(QString pathname) {
     _startUpScripts.removeOne(pathname);
     setDirtyAndFirePropertyChange("deleteStartUpScript", QVariant(), pathname); // NOI18N
 }

 /**
  * Gets a list of pathnames to run after trains have been loaded
  *
  * @return A list of pathnames to run after trains have been loaded
  */
 /*public*/ QStringList TrainManager::getStartUpScripts() {
     return _startUpScripts;
 }

 /*public*/ void TrainManager::runStartUpScripts() {
#if 0
  // use thread to prevent object (Train) thread lock
         Thread scripts = jmri.util.ThreadingUtil.newThread(new Runnable() {
             @Override
             public void run() {
                 for (String scriptPathName : getStartUpScripts()) {
                     try {
                         JmriScriptEngineManager.getDefault()
                                 .runScript(new File(jmri.util.FileUtil.getExternalFilename(scriptPathName)));
                     } catch (Exception e) {
                         log.error("Problem with script: {}", scriptPathName);
                     }
                 }
             }
         });
         scripts.setName("Startup Scripts"); // NOI18N
         scripts.start();
#endif
 }

 /**
  * Add a script to run at shutdown
  *
  * @param pathname The script's pathname
  */
 /*public*/ void TrainManager::addShutDownScript(QString pathname) {
     _shutDownScripts.append(pathname);
     setDirtyAndFirePropertyChange("addShutDownScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void TrainManager::deleteShutDownScript(QString pathname) {
     _shutDownScripts.removeAt(_shutDownScripts.indexOf(pathname));
     setDirtyAndFirePropertyChange("deleteShutDownScript", QVariant(), pathname); // NOI18N
 }
 /**
  * Gets a list of pathnames to run at shutdown
  *
  * @return A list of pathnames to run at shutdown
  */
 /*public*/ QStringList TrainManager::getShutDownScripts() {
     return _shutDownScripts;
 }


 /*public*/ void TrainManager::runShutDownScripts() {
     foreach (QString scriptPathName, getShutDownScripts()) {
#if 0 // TODO:
         try {
             JmriScriptEngineManager.getDefault().runScript(new File(jmri.util.FileUtil.getExternalFilename(scriptPathName)));
         } catch (Exception* e) {
             log->error("Problem with script: {}", scriptPathName);
         }
#endif
     }
 }

 /*public*/ bool TrainManager::isBuiltRestricted() {
     for (Train* train : getList()) {
         if (train->getBuiltStartYear()!=(Train::NONE) || train->getBuiltEndYear()!=(Train::NONE)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ bool TrainManager::isLoadRestricted() {
     for (Train* train : getList()) {
         if (train->getLoadOption()!=(Train::ALL_LOADS)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ bool TrainManager::isRoadRestricted() {
     for (Train* train : getList()) {
         if (train->getRoadOption()!=(Train::ALL_ROADS)) {
             return true;
         }
     }
     return false;
 }

 /*public*/ bool TrainManager::isOwnerRestricted() {
     for (Train* train : getList()) {
         if (train->getOwnerOption()!=(Train::ALL_OWNERS)) {
             return true;
         }
     }
     return false;
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD")
 /*public*/ void TrainManager::dispose() {
     _trainHashTable.clear();
     _id = 0;
//     _instance = nullptr;	// we need to reset the instance for testing purposes
 }


/**
* @return requested Train object or NULL if none exists
*/
/*public*/ Train* TrainManager::getTrainByName(QString name)
{
 if (!((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->isTrainFileLoaded()) {
     log->error("TrainManager getTrainByName called before trains completely loaded!");
 }
 Train* train;
 //Enumeration<Train> en = _trainHashTable.elements();
 QListIterator<Train*> en(_trainHashTable.values());
 while (en.hasNext()) {
     train = en.next();
     // windows file names are case independent
     if (train->getName().toLower()==(name.toLower())) {
         return train;
     }
 }
 log->debug(tr("Train (%1) doesn't exist").arg(name));
 return nullptr;
}

/*public*/ Train* TrainManager::getTrainById(QString id) {
 if (!((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->isTrainFileLoaded()) {
     log->error("TrainManager getTrainById called before trains completely loaded!");
 }
 return _trainHashTable.value(id);
}

/**
* Finds an existing train or creates a new train if needed requires train's
* name creates a unique id for this train
*
* @param name
*
* @return new train or existing train
*/
/*public*/ Train* TrainManager::newTrain(QString name) {
 Train* train = getTrainByName(name);
 if (train == nullptr) {
     _id++;
     train = new Train(QString::number(_id), name);
     int oldSize = _trainHashTable.size();
     _trainHashTable.insert(train->getId(), train);
     setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize,
             _trainHashTable.size());
 }
 return train;
}

/**
* Remember a NamedBean Object created outside the manager.
*/
/*public*/ void TrainManager::_register(Train* train) {
 int oldSize = _trainHashTable.size();
 _trainHashTable.insert(train->getId(), train);
 // find last id created
 int id = train->getId().toInt();
 if (id > _id) {
     _id = id;
 }
 setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize,
        _trainHashTable.size());
 // listen for name and state changes to forward
}

/**
* Forget a NamedBean Object created outside the manager.
*/
/*public*/ void TrainManager::deregister(Train* train) {
 if (train == nullptr) {
     return;
 }
 train->dispose();
 int oldSize = _trainHashTable.size();
 _trainHashTable.remove(train->getId());
 setDirtyAndFirePropertyChange(LISTLENGTH_CHANGED_PROPERTY, oldSize,
         _trainHashTable.size());
}

 /*public*/ void TrainManager::replaceLoad(QString type, QString oldLoadName, QString newLoadName) {
     foreach (Train* train, getTrainsByIdList()) {
         foreach (QString loadName, train->getLoadNames()) {
             if (loadName==(oldLoadName)) {
                 train->deleteLoadName(oldLoadName);
                 if (newLoadName != "") {
                     train->addLoadName(newLoadName);
                 }
             }
             // adjust combination car type and load name
             QStringList splitLoad = loadName.split(CarLoad::SPLIT_CHAR);
             if (splitLoad.length() > 1) {
                 if (splitLoad[0]==(type) && splitLoad[1]==(oldLoadName)) {
                     train->deleteLoadName(loadName);
                     if (newLoadName != "") {
                         train->addLoadName(type + CarLoad::SPLIT_CHAR + newLoadName);
                     }
                 }
             }
         }
     }
 }

 /**
  *
  * @return true if there's a built train
  */
 /*public*/ bool TrainManager::isAnyTrainBuilt() {
     foreach (Train* train, getTrainsByIdList()) {
         if (train->isBuilt()) {
             return true;
         }
     }
     return false;
 }

 /**
 *
 * @return true if there's a train being built
 */
/*public*/ bool TrainManager::isAnyTrainBuilding() {
    foreach (Train* train, getTrainsByIdList()) {
        if (train->getStatusCode() == Train::CODE_BUILDING) {
            return true;
        }
    }
    return false;
}

 /**
  *
  * @param car
  * @return Train that can service car from its current location to the its
  * destination.
  */
 /*public*/ Train* TrainManager::getTrainForCar(Car* car, PrintWriter* buildReport) {
     return getTrainForCar(car, nullptr, buildReport);
 }

 /**
  *
  * @param car
  * @param excludeTrain The only train not to try.
  * @param buildReport
  * @return Train that can service car from its current location to the its
  * destination.
  */
 /*public*/ Train* TrainManager::getTrainForCar(Car* car, Train* excludeTrain, PrintWriter* buildReport) {
     log->debug("Find train for car (" + car->toString() + ") location (" + car->getLocationName() + ", " // NOI18N
             + car->getTrackName() + ") destination (" + car->getDestinationName() + ", " // NOI18N
             + car->getDestinationTrackName() + ")"); // NOI18N
     if (Setup::getRouterBuildReportLevel()==(Setup::BUILD_REPORT_VERY_DETAILED)) {
         TrainCommon::addLine(buildReport, Setup::BUILD_REPORT_VERY_DETAILED, TrainCommon::BLANK_LINE);
         TrainCommon::addLine(buildReport, Setup::BUILD_REPORT_VERY_DETAILED, tr("trainFindForCar").arg(car->toString()).arg(car->getLocationName(),
                     car->getTrackName()).arg(car->getDestinationName()).arg(car->getDestinationTrackName()));
     }
     foreach (Train* train, getTrainsByIdList()) {
         if (train == excludeTrain) {
             continue;
         }
         if (Setup::isOnlyActiveTrainsEnabled() && !train->isBuildEnabled()) {
             continue;
         }
         // does this train service this car?
         if (train->services(buildReport, car)) {
             return train;
         }
     }
     return nullptr;
 }

 /**
  * Sort by train name
  *
  * @return list of train ids ordered by name
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByNameList() {
     return getTrainsByList(getList(), GET_TRAIN_NAME);
 }

 /**
  * Sort by train departure time
  *
  * @return list of train ids ordered by departure time
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByTimeList() {
     return getTrainsByIntList(getTrainsByNameList(), GET_TRAIN_TIME);
 }

 /**
  * Sort by train departure name
  *
  * @return list of train ids ordered by departure name
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByDepartureList() {
     return getTrainsByList(getTrainsByNameList(), GET_TRAIN_DEPARTES_NAME);
 }

 /**
  * Sort by train termination name
  *
  * @return list of train ids ordered by termination name
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByTerminatesList() {
     return getTrainsByList(getTrainsByNameList(), GET_TRAIN_TERMINATES_NAME);
 }

 /**
  * Sort by train route name
  *
  * @return list of train ids ordered by route name
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByRouteList() {
     return getTrainsByList(getTrainsByNameList(), GET_TRAIN_ROUTE_NAME);
 }

 /**
  * Sort by train route name
  *
  * @return list of train ids ordered by route name
  */
 /*public*/ QList<Train*> TrainManager::getTrainsByStatusList() {
     return getTrainsByList(getTrainsByNameList(), GET_TRAIN_STATUS);
 }

/**
* Sort by train id
*
* @return list of train ids ordered by id
*/
/*public*/ QList<Train*> TrainManager::getTrainsByIdList() {
 return getTrainsByIntList(getList(), GET_TRAIN_ID);
}

/*private*/ QList<Train*> TrainManager::getTrainsByList(QList<Train*> sortList, int attribute) {
 QList<Train*> out = QList<Train*>();
 foreach (Train* train, sortList) {
     QString trainAttribute =  getTrainAttribute(train, attribute).toString();
     for (int j = 0; j < out.size(); j++) {
         //if (trainAttribute.compareToIgnoreCase((QString) getTrainAttribute(out.value(j), attribute)) < 0)
      if(QString::compare(trainAttribute, getTrainAttribute(out.value(j), attribute).toString(), Qt::CaseInsensitive) < 0)
         {
             out.insert(j, train);
             break;
         }
     }
     if (!out.contains(train)) {
         out.append(train);
     }
 }
 return out;
}

/*private*/ QList<Train*> TrainManager::getTrainsByIntList(QList<Train*> sortList, int attribute) {
 QList<Train*> out =QList<Train*>();
 foreach (Train* train, sortList) {
     int trainAttribute =  getTrainAttribute(train, attribute).toInt();
     for (int j = 0; j < out.size(); j++) {
         if (trainAttribute < getTrainAttribute(out.at(j), attribute).toInt()) {
             out.insert(j, train);
             break;
         }
     }
     if (!out.contains(train)) {
         out.append(train);
     }
 }
 return out;
}


/*private*/ QVariant TrainManager::getTrainAttribute(Train* train, int attribute) {
 switch (attribute) {
//            case GET_TRAIN_DEPARTES_NAME:
//                return train->getTrainDepartsName();
     case GET_TRAIN_NAME:
         return train->getName();
//            case GET_TRAIN_ROUTE_NAME:
//                return train->getTrainRouteName();
//            case GET_TRAIN_TERMINATES_NAME:
//                return train->getTrainTerminatesName();
//            case GET_TRAIN_TIME:
//                return train->getDepartTimeMinutes();
//            case GET_TRAIN_STATUS:
//                return train.getStatus();
     case GET_TRAIN_ID:
         return train->getId().toInt();
     default:
         return "unknown"; // NOI18N
 }
}

/*private*/ QList<Train*> TrainManager::getList() {
 if (!((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->isTrainFileLoaded()) {
     log->error("TrainManager getList called before trains completely loaded!");
 }
 QList<Train*> out = QList<Train*>();
 //Enumeration<Train> en = _trainHashTable.elements();
 QListIterator<Train*> en(_trainHashTable.values());
   while (en.hasNext()) {
     out.append(en.next());
 }
 return out;
}

/*public*/ JComboBox* TrainManager::getTrainComboBox() {
 JComboBox* box = new JComboBox();
 updateTrainComboBox(box);
 return box;
}

/*public*/ void TrainManager::updateTrainComboBox(JComboBox* box) {
 box->clear();
 box->addItem("");
 foreach (Train* train, getTrainsByNameList()) {
     box->addItem(train->_name, VPtr<Train>::asQVariant(train));
 }
}

 /**
  * Update combo box with trains that will service this car
  *
  * @param box the combo box to update
  * @param car the car to be serviced
  */
 /*public*/ void TrainManager::updateTrainComboBox(JComboBox* box, Car* car) {
     box->clear();
     box->addItem("");
     foreach (Train* train, getTrainsByNameList()) {
         if (train->services(car)) {
             box->addItem(train->getName(), VPtr<Train>::asQVariant(train));
         }
     }
 }

 /**
  * @return Number of trains
  */
 /*public*/ int TrainManager::numEntries() {
     return _trainHashTable.size();
 }

 /*public*/ bool TrainManager::isRowColorManual() {
     return _rowColorManual;
 }

 /*public*/ void TrainManager::setRowColorsManual(bool manual) {
     bool old = _rowColorManual;
     _rowColorManual = manual;
     setDirtyAndFirePropertyChange(ROW_COLOR_NAME_CHANGED_PROPERTY, old, manual);
 }

 /*public*/ QString TrainManager::getRowColorNameForBuilt() {
     return _rowColorBuilt;
 }

 /*public*/ void TrainManager::setRowColorNameForBuilt(QString colorName) {
     QString old = _rowColorBuilt;
     _rowColorBuilt = colorName;
     setDirtyAndFirePropertyChange(ROW_COLOR_NAME_CHANGED_PROPERTY, old, colorName);
 }

 /*public*/ QString TrainManager::getRowColorNameForBuildFailed() {
     return _rowColorBuildFailed;
 }

 /*public*/ void TrainManager::setRowColorNameForBuildFailed(QString colorName) {
     QString old = _rowColorBuildFailed;
     _rowColorBuildFailed = colorName;
     setDirtyAndFirePropertyChange(ROW_COLOR_NAME_CHANGED_PROPERTY, old, colorName);
 }

 /*public*/ QString TrainManager::getRowColorNameForTrainEnRoute() {
     return _rowColorTrainEnRoute;
 }

 /*public*/ void TrainManager::setRowColorNameForTrainEnRoute(QString colorName) {
     QString old = _rowColorTrainEnRoute;
     _rowColorTrainEnRoute = colorName;
     setDirtyAndFirePropertyChange(ROW_COLOR_NAME_CHANGED_PROPERTY, old, colorName);
 }

 /*public*/ QString TrainManager::getRowColorNameForTerminated() {
     return _rowColorTerminated;
 }

 /*public*/ void TrainManager::setRowColorNameForTerminated(QString colorName) {
     QString old = _rowColorTerminated;
     _rowColorTerminated = colorName;
     setDirtyAndFirePropertyChange(ROW_COLOR_NAME_CHANGED_PROPERTY, old, colorName);
 }

 /**
  *
  * @return the available text colors used for printing
  */
 /*public*/ JComboBox* TrainManager::getRowColorComboBox() {
     JComboBox* box = new JComboBox();
     box->addItem(NONE);
     box->addItem(Setup::BLACK);
     box->addItem(Setup::RED);
     box->addItem(Setup::PINK);
     box->addItem(Setup::ORANGE);
     box->addItem(Setup::YELLOW);
     box->addItem(Setup::GREEN);
     box->addItem(Setup::MAGENTA);
     box->addItem(Setup::CYAN);
     box->addItem(Setup::BLUE);
     box->addItem(Setup::GRAY);
     return box;
 }

 /**
  * Makes a copy of an existing train. Only the train's description isn't
  * copied.
  *
  * @param train the train to copy
  * @param trainName the name of the new train
  * @return a copy of train
  */
 /*public*/ Train* TrainManager::copyTrain(Train* train, QString trainName) {
     Train* _newTrain = newTrain(trainName);
     // route, departure time and types
     _newTrain->setRoute(train->getRoute());
     _newTrain->setTrainSkipsLocations(train->getTrainSkipsLocations());
     _newTrain->setDepartureTime(train->getDepartureTimeHour(), train->getDepartureTimeMinute());
     _newTrain->_typeList.clear(); // remove all types loaded by create
     _newTrain->setTypeNames(train->getTypeNames());
     // set road, load, and owner options
     _newTrain->setRoadOption(train->getRoadOption());
     _newTrain->setRoadNames(train->getRoadNames());
     _newTrain->setLoadOption(train->getLoadOption());
     _newTrain->setLoadNames(train->getLoadNames());
     _newTrain->setOwnerOption(train->getOwnerOption());
     _newTrain->setOwnerNames(train->getOwnerNames());
     // build dates
     _newTrain->setBuiltStartYear(train->getBuiltStartYear());
     _newTrain->setBuiltEndYear(train->getBuiltEndYear());
     // locos start of route
     _newTrain->setNumberEngines(train->getNumberEngines());
     _newTrain->setEngineModel(train->getEngineModel());
     _newTrain->setEngineRoad(train->getEngineRoad());
     _newTrain->setRequirements(train->getRequirements());
     _newTrain->setCabooseRoad(train->getCabooseRoad());
     // second leg
     _newTrain->setSecondLegNumberEngines(train->getSecondLegNumberEngines());
     _newTrain->setSecondLegEngineModel(train->getSecondLegEngineModel());
     _newTrain->setSecondLegEngineRoad(train->getSecondLegEngineRoad());
     _newTrain->setSecondLegOptions(train->getSecondLegOptions());
     _newTrain->setSecondLegCabooseRoad(train->getSecondLegCabooseRoad());
     _newTrain->setSecondLegStartLocation(train->getSecondLegStartLocation());
     _newTrain->setSecondLegEndLocation(train->getSecondLegEndLocation());
     // third leg
     _newTrain->setThirdLegNumberEngines(train->getThirdLegNumberEngines());
     _newTrain->setThirdLegEngineModel(train->getThirdLegEngineModel());
     _newTrain->setThirdLegEngineRoad(train->getThirdLegEngineRoad());
     _newTrain->setThirdLegOptions(train->getThirdLegOptions());
     _newTrain->setThirdLegCabooseRoad(train->getThirdLegCabooseRoad());
     _newTrain->setThirdLegStartLocation(train->getThirdLegStartLocation());
     _newTrain->setThirdLegEndLocation(train->getThirdLegEndLocation());
     // scripts
     foreach (QString scriptName, train->getBuildScripts()) {
         _newTrain->addBuildScript(scriptName);
     }
     foreach (QString scriptName, train->getMoveScripts()) {
         _newTrain->addMoveScript(scriptName);
     }
     foreach (QString scriptName, train->getTerminationScripts()) {
         _newTrain->addTerminationScript(scriptName);
     }
     // manifest options
     _newTrain->setRailroadName(train->getRailroadName());
     _newTrain->setManifestLogoURL(train->getManifestLogoURL());
     _newTrain->setShowArrivalAndDepartureTimes(train->isShowArrivalAndDepartureTimesEnabled());
     // build options
     _newTrain->setAllowLocalMovesEnabled(train->isAllowLocalMovesEnabled());
     _newTrain->setAllowReturnToStagingEnabled(train->isAllowReturnToStagingEnabled());
     _newTrain->setAllowThroughCarsEnabled(train->isAllowThroughCarsEnabled());
     _newTrain->setBuildConsistEnabled(train->isBuildConsistEnabled());
     _newTrain->setSendCarsWithCustomLoadsToStagingEnabled(train->isSendCarsWithCustomLoadsToStagingEnabled());
     _newTrain->setBuildTrainNormalEnabled(train->isBuildTrainNormalEnabled());
     _newTrain->setSendCarsToTerminalEnabled(train->isSendCarsToTerminalEnabled());
     _newTrain->setServiceAllCarsWithFinalDestinationsEnabled(train->isServiceAllCarsWithFinalDestinationsEnabled());
     // comment
     _newTrain->setComment(train->getComment());
     // description
     _newTrain->setDescription(train->getRawDescription());
     return _newTrain;
 }

 /**
  * Provides a list of trains ordered by arrival time to a location
  *
  * @param location The location
  * @return A list of trains ordered by arrival time.
  */
 /*public*/ QList<Train*> TrainManager::getTrainsArrivingThisLocationList(Location* location) {
     // get a list of trains
     QList<Train*> out = QList<Train*>();
     QList<int> arrivalTimes = QList<int>();
     foreach (Train* train, getTrainsByTimeList()) {
         if (!train->isBuilt()) {
             continue; // train wasn't built so skip
         }
         Route* route = train->getRoute();
         if (route == nullptr) {
             continue; // no route for this train
         }
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             if (TrainCommon::splitString(rl->getName())==(TrainCommon::splitString(location->getName()))) {
                 int expectedArrivalTime = train->getExpectedTravelTimeInMinutes(rl);
                 // is already serviced then "-1"
                 if (expectedArrivalTime == -1) {
                     out.insert(0, train); // place all trains that have already been serviced at the start
                     arrivalTimes.insert(0, expectedArrivalTime);
                 } // if the train is in route, then expected arrival time is in minutes
                 else if (train->isTrainInRoute()) {
                     for (int j = 0; j < out.size(); j++) {
                         Train* t = out.at(j);
                         int time = arrivalTimes.at(j);
                         if (t->isTrainInRoute() && expectedArrivalTime < time) {
                             out.insert(j, train);
                             arrivalTimes.insert(j, expectedArrivalTime);
                             break;
                         }
                         if (!t->isTrainInRoute()) {
                             out.insert(j, train);
                             arrivalTimes.insert(j, expectedArrivalTime);
                             break;
                         }
                     }
                     // Train has not departed
                 } else {
                     for (int j = 0; j < out.size(); j++) {
                         Train* t = out.at(j);
                         int time = arrivalTimes.at(j);
                         if (!t->isTrainInRoute() && expectedArrivalTime < time) {
                             out.insert(j, train);
                             arrivalTimes.insert(j, expectedArrivalTime);
                             break;
                         }
                     }
                 }
                 if (!out.contains(train)) {
                     out.append(train);
                     arrivalTimes.append(expectedArrivalTime);
                 }
                 break; // done
             }
         }
     }
     return out;
 }

 /**
  * Loads train icons if needed
  */
/*public*/ void TrainManager::loadTrainIcons() {
     foreach (Train* train, getTrainsByIdList()) {
         train->loadTrainIcon();
     }
 }

 /**
  * Sets the switch list status for all built trains. Used for switch lists
  * in consolidated mode.
  */
 /*public*/ void TrainManager::setTrainsSwitchListStatus(QString status) {
     foreach (Train* train, getTrainsByTimeList()) {
         if (!train->isBuilt()) {
             continue; // train isn't built so skip
         }
         train->setSwitchListStatus(status);
     }
 }

 /**
  * Sets all built trains manifests to modified. This causes the train's
  * manifest to be recreated.
  */
 /*public*/ void TrainManager::setTrainsModified() {
     foreach (Train* train, getTrainsByTimeList()) {
         if (!train->isBuilt() || train->isTrainInRoute()) {
             continue; // train wasn't built or in route, so skip
         }
         train->setModified(true);
     }
 }

 /*public*/ void TrainManager::buildSelectedTrains(/*final*/ QList<Train*> trains) {
#if 1
     // use a thread to allow table updates during build
     Thread* build = new Thread(new TMRunnable(trains, this));
//     {
//         /*public*/ void run() {
//             for (Train train : trains) {
//                 train.buildIfSelected();
//             }
//             setDirtyAndFirePropertyChange(TRAINS_BUILT_CHANGED_PROPERTY, false, true);
//         }
//     });
     build->setName("Build Trains"); // NOI18N
     build->start();
#endif

 }

 void TrainManager::onError(QString title, QString msg)
 {
  QMessageBox::critical(nullptr, title, msg);
 }

 MyBuild::MyBuild(QList<Train*> trains, TrainManager *parent)
 {
  this->trains = trains;
  this->parent = parent;
 }

 void MyBuild::process()
 {
  foreach (Train* train,  trains)
  {
   train->buildIfSelected();
  }
  parent->setDirtyAndFirePropertyChange(TrainManager::TRAINS_BUILT_CHANGED_PROPERTY, false, true);
  emit finished();
 }

 /*public*/ bool TrainManager::printSelectedTrains(QList<Train*> trains)
 {
  bool status = true;
  foreach (Train* train, trains)
  {
   if (train->isBuildEnabled())
   {
    if (train->printManifestIfBuilt()) {
        continue;
    }
    status = false; // failed to print all selected trains
    if (isBuildMessagesEnabled())
    {
//                    JOptionPane.showMessageDialog(NULL, MessageFormat.format(Bundle
//                            .getMessage("NeedToBuildBeforePrinting"), new Object[]{train.getName(),
//                                (isPrintPreviewEnabled() ? Bundle.getMessage("preview") : Bundle.getMessage("print"))}),
//                            MessageFormat.format(Bundle.getMessage("CanNotPrintManifest"),
//                                    new Object[]{isPrintPreviewEnabled() ? Bundle.getMessage("preview") : Bundle
//                                                .getMessage("print")}), JOptionPane.ERROR_MESSAGE);
     QMessageBox::critical(nullptr, tr("Can not %1 manifest").arg(isPrintPreviewEnabled()?tr("preview"):tr("print")), tr("Need to build train (%1) before you can %2 manifest").arg(train->getName()).arg(isPrintPreviewEnabled()?tr("preview"):tr("print")) );
    }
   }
  }
  return status;
 }

 /*public*/ bool TrainManager::terminateSelectedTrains(QList<Train*> trains) {
     bool status = true;
     foreach (Train* train, trains) {
         if (train->isBuildEnabled() && train->isBuilt()) {
             if (train->isPrinted()) {
                 train->terminate();
             } else {
                 status = false;
//                    int response = JOptionPane.showConfirmDialog(NULL, Bundle
//                            .getMessage("WarningTrainManifestNotPrinted"), MessageFormat.format(Bundle
//                                    .getMessage("TerminateTrain"), new Object[]{train.getName(), train.getDescription()}),
//                            JOptionPane.YES_NO_OPTION);
//                    if (response == JOptionPane.YES_OPTION) {
                 int response = QMessageBox::question(nullptr, tr("Terminate Train (%1) %2?").arg(train->getName()).arg(train->getDescription()), tr("Warning, train manifest hasn't been printed!"), QMessageBox::Yes | QMessageBox::No);
                 if(response == QMessageBox::Yes)
                 {
                     train->terminate();
                 }
                 // Quit?
                 if (response == QMessageBox::No)
                 {
                     break;
                 }
             }
         }
     }
     return status;
 }

 /*public*/ void TrainManager::resetBuildFailedTrains() {
         for (Train* train : getList()) {
             if (train->isBuildFailed())
                 train->reset();
         }
     }

 /*public*/ void TrainManager::load(QDomElement root)
     {
      if (!root.firstChildElement(Xml::OPTIONS).isNull())
      {
         QDomElement options = root.firstChildElement(Xml::OPTIONS);
         ((TrainCustomManifest*)InstanceManager::getDefault("TrainCustomManifest"))->load(options);
         ((TrainCustomSwitchList*)InstanceManager::getDefault("TrainCustomSwitchList"))->load(options);
         QDomElement e = options.firstChildElement(Xml::TRAIN_OPTIONS);
         QString a;
         if (!e .isNull()) {
          if ((a = e.attribute (Xml::BUILD_MESSAGES)) != "") {
                 _buildMessages = a==(Xml::_TRUE);
             }
             if ((a = e.attribute (Xml::BUILD_REPORT)) != "") {
                 _buildReport = a==(Xml::_TRUE);
             }
             if ((a = e.attribute (Xml::PRINT_PREVIEW)) != "") {
                 _printPreview = a==(Xml::_TRUE);
             }
             if ((a = e.attribute (Xml::OPEN_FILE)) != "") {
                 _openFile = a==(Xml::_TRUE);
             }
             if ((a = e.attribute (Xml::RUN_FILE)) != "") {
                 _runFile = a==(Xml::_TRUE);
             }

             // verify that the Trains Window action is valid
             if ((a = e.attribute (Xml::TRAIN_ACTION)) != ""
                     && (a==(TrainsTableFrame::MOVE) || a==(TrainsTableFrame::RESET)
                     || a==(TrainsTableFrame::TERMINATE) || a==(
                             TrainsTableFrame::CONDUCTOR))) {
                 _trainAction = a;
             }

             // TODO This here is for backwards compatibility, remove after next major release
             if ((a = e.attribute (Xml::COLUMN_WIDTHS)) != "") {
                 QStringList widths = a.split(" ");
                 for (int i = 0; i < widths.length(); i++) {
                     try {
                   _tableColumnWidths.replace(i, widths.at(i).toInt());
                     } catch (NumberFormatException* ee) {
                         log->error("Number format exception when reading trains column widths");
                     }
                 }
             }
         }

         // Row color options
         QDomElement eRowColorOptions = options.firstChildElement(Xml::ROW_COLOR_OPTIONS);
         if (eRowColorOptions != QDomElement())
         {
             if ((a = eRowColorOptions.attribute (Xml::ROW_COLOR_MANUAL)) != nullptr) {
                 _rowColorManual = a==(Xml::_TRUE);
             }
             if ((a = eRowColorOptions.attribute (Xml::ROW_COLOR_BUILD_FAILED)) != nullptr) {
                 _rowColorBuildFailed = a;
             }
             if ((a = eRowColorOptions.attribute (Xml::ROW_COLOR_BUILT)) != nullptr) {
                 _rowColorBuilt = a;
             }
             if ((a = eRowColorOptions.attribute (Xml::ROW_COLOR_TRAIN_EN_ROUTE)) != nullptr) {
                 _rowColorTrainEnRoute = a;
             }
             if ((a = eRowColorOptions.attribute (Xml::ROW_COLOR_TERMINATED)) != nullptr) {
                 _rowColorTerminated = a;
             }
         }

         e = options.firstChildElement(Xml::TRAIN_SCHEDULE_OPTIONS);
         if (e != QDomElement()) {
             if ((a = e.attribute (Xml::ACTIVE_ID)) != "") {
                 _trainScheduleActiveId = a;
             }
             // TODO This here is for backwards compatibility, remove after next major release
             if ((a = e.attribute (Xml::COLUMN_WIDTHS)) != "") {
                 QStringList widths = a.split(" ");
                 //_tableScheduleColumnWidths =  QList<int>();
                 QVector<int> temp = QVector<int>(widths.length());
                 for (int i = 0; i < widths.length(); i++) {
                     try {
                         //_tableScheduleColumnWidths[i] = Integer.parseInt(widths[i]);
                   temp.replace(i, widths.at(i).toInt());
                     } catch (NumberFormatException* ee) {
                         log->error("Number format exception when reading trains column widths");
                     }
                 }
                 _tableScheduleColumnWidths = temp.toList();
             }
         }

         // check for scripts
         if (options.firstChildElement(Xml::SCRIPTS) != QDomElement()) {
             //@SuppressWarnings("unchecked")
             QDomNodeList lm = options.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::START_UP);
             for (int i=0; i < lm.size(); i++) {
              QDomElement es =  lm.at(i).toElement();
                 if ((a = es.attribute (Xml::NAME)) != "") {
                     addStartUpScript(a);
                 }
             }
             //@SuppressWarnings("unchecked")
             QDomNodeList lt = options.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::SHUT_DOWN);
             for (int i=0; i < lt.size(); i++) {
              QDomElement es =  lt.at(i).toElement();
                 if ((a = es.attribute (Xml::NAME)) != "") {
                     addShutDownScript(a);
                 }
             }
         }

     }
      if (root.firstChildElement(Xml::TRAINS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList eTrains = root.firstChildElement(Xml::TRAINS).elementsByTagName(Xml::TRAIN);
         log->debug(tr("readFile sees %1 trains").arg(eTrains.size()));
         //for (Element eTrain : eTrains) {
         for(int i = 0; i < eTrains.size(); i++)
         {
          _register(new Train(eTrains.at(i).toElement()));
         }
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-trains.dtd.
  *
  */
 /*public*/ void TrainManager::store(QDomElement root, QDomDocument doc) {
     QDomElement options = doc.createElement(Xml::OPTIONS);
     //Element e = doc.createElement(Xml::TRAIN_OPTIONS);
      QDomElement e = doc.createElement(Xml::TRAIN_OPTIONS);

     e.setAttribute(Xml::BUILD_MESSAGES, (isBuildMessagesEnabled() ? Xml::_TRUE : Xml::_FALSE));
     e.setAttribute(Xml::BUILD_REPORT, isBuildReportEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::PRINT_PREVIEW, isPrintPreviewEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::OPEN_FILE, isOpenFileEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::RUN_FILE, isRunFileEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::TRAIN_ACTION, getTrainsFrameTrainAction());
     options.appendChild(e);

     // Conductor options
     e = doc.createElement(Xml::CONDUCTOR_OPTIONS);
     e.setAttribute(Xml::SHOW_HYPHEN_NAME, isShowLocationHyphenNameEnabled() ? Xml::_TRUE : Xml::_FALSE);
     options.appendChild(e);


     // Trains table row color options
     //e = doc.createElement(Xml::ROW_COLOR_OPTIONS);
     e = doc.createElement(Xml::ROW_COLOR_OPTIONS);
     e.setAttribute(Xml::ROW_COLOR_MANUAL, isRowColorManual() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::ROW_COLOR_BUILD_FAILED, getRowColorNameForBuildFailed());
     e.setAttribute(Xml::ROW_COLOR_BUILT, getRowColorNameForBuilt());
     e.setAttribute(Xml::ROW_COLOR_TRAIN_EN_ROUTE, getRowColorNameForTrainEnRoute());
     e.setAttribute(Xml::ROW_COLOR_TERMINATED, getRowColorNameForTerminated());
     options.appendChild(e);

     if (getStartUpScripts().size() > 0 || getShutDownScripts().size() > 0) {
         // save list of shutdown scripts
         QDomElement es = doc.createElement(Xml::SCRIPTS);
         foreach (QString scriptName, getStartUpScripts()) {
             QDomElement em = doc.createElement(Xml::START_UP);
             em.setAttribute(Xml::NAME, scriptName);
             es.appendChild(em);
         }
         // save list of termination scripts
         foreach (QString scriptName, getShutDownScripts()) {
             QDomElement et = doc.createElement(Xml::SHUT_DOWN);
             et.setAttribute(Xml::NAME, scriptName);
             es.appendChild(et);
         }
         options.appendChild(es);
     }
#if 0
     TrainCustomManifest.store(options);	// save custom manifest elements
     TrainCustomSwitchList.store(options);	// save custom manifest elements
#endif
     root.appendChild(options);

     //Element trains = doc.createElement(Xml::TRAINS);
     QDomElement trains = doc.createElement(Xml::TRAINS);
     root.appendChild(trains);
     // add entries
     foreach (Train* train, getTrainsByIdList()) {
         trains.appendChild(train->store(doc));
     }
 }

 /**
  * Check for car type and road name replacements. Also check for engine type
  * replacement.
  *
  */
 /*public*/ void TrainManager::propertyChange(PropertyChangeEvent* e) {
     log->debug("TrainManager sees property change: " + e->getPropertyName() + " old: "
             + e->getOldValue().toString() + " new " + e->getNewValue().toString()); // NOI18N
     // TODO use listener to determine if load name has changed
     // if (e.getPropertyName()==(CarLoads.LOAD_NAME_CHANGED_PROPERTY)){
     // replaceLoad((QString)e.getOldValue(), (QString)e.getNewValue());
     // }
 }
#if 0
 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*private*/ void TrainManager::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     ((TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"))->setDirty(true);
     firePropertyChange(p, old, n);
 }
 //@Override
 /*public*/ void TrainManager::initialize() {
     (OperationsSetupXml*)InstanceManager::getDefault("OperationsSetupXml"); // load setup
     (TrainManagerXml*)InstanceManager::getDefault("TrainManagerXml"); // load trains
 }
  /*private*/ /*final*/ /*static*/ Logger* TrainManager::log = LoggerFactory::getLogger("TrainManager");
} // end namespace
