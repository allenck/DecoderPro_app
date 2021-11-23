#include "trainbycartypeframe.h"
#include "car.h"
#include "train.h"
#include "locationmanager.h"
#include "jcombobox.h"
#include "gridbaglayout.h"
#include <QBoxLayout>
#include "trainmanager.h"
#include "cartypes.h"
#include "logger.h"
#include <QGroupBox>
#include <vptr.h>
#include <QSize>
#include <QScrollArea>
#include "route.h"
#include <QLabel>
#include <QMessageBox>
#include "routelocation.h"
#include "location.h"
#include "track.h"
#include "schedule.h"
#include "scheduleitem.h"
#include "carmanager.h"
#include "rollingstock.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame to display by rolling stock, the locations serviced by this train
  *
  * @author Dan Boudreau Copyright (C) 2010, 2013, 2014
  * @version $Revision: 29261 $
  */
 ///*public*/ class TrainByCarTypeFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -5894248098711372139L;


 /*public*/ TrainByCarTypeFrame::TrainByCarTypeFrame(QWidget* parent)
     : OperationsFrame(parent)
 {
     //super();
 log = new Logger("TrainByCarTypeFrame");
 locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));

// panels
 pRoute = new JPanel();

     // radio buttons
     // combo boxes
     trainsComboBox = ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainComboBox();
     typeComboBox = ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getComboBox();
     carsComboBox = new JComboBox();
 }

 /*public*/ void TrainByCarTypeFrame::initComponents(Train* train) {

     _train = train;

     // general GUI config
     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

     // Set up the panels
     JPanel* pTrain = new JPanel();
     pTrain->setLayout(new GridBagLayout());
     pTrain->setBorder(BorderFactory::createTitledBorder(tr("Train")));
     pTrain->setMaximumSize(QSize(2000, 50));

     addItem(pTrain, trainsComboBox, 0, 0);
     trainsComboBox->setCurrentIndex(trainsComboBox->findData(VPtr<Train>::asQVariant(train)));

     JPanel* pCarType = new JPanel();
     pCarType->setLayout(new GridBagLayout());
     pCarType->setBorder(BorderFactory::createTitledBorder(tr("Type")));
     pCarType->setMaximumSize(QSize(2000, 50));

     addItem(pCarType, typeComboBox, 0, 0);
     addItem(pCarType, carsComboBox, 1, 0);

     // increase width of combobox so large text names display properly
     QSize boxsize = typeComboBox->minimumSize();
     if (boxsize != QSize())
     {
         //boxsize.setSize(boxsize.width + 10, boxsize.height);
         boxsize.setWidth(boxsize.width() + 10);
         typeComboBox->setMinimumSize(boxsize);
     }

     adjustCarsComboBoxSize();

     JPanel*pRouteFrame = new JPanel;
     pRouteFrame->setLayout(new QVBoxLayout);
     pRoute->setLayout(new GridBagLayout());
     QScrollArea* locationPane = new QScrollArea(/*pRoute*/);
     pRouteFrame->layout()->addWidget(locationPane);
     locationPane->setWidgetResizable(true);
     //locationPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
     pRouteFrame->setBorder(BorderFactory::createTitledBorder(tr("Route")));
     updateCarsComboBox();
     updateRoute();

     thisLayout->addWidget(pTrain);
     thisLayout->addWidget(pCarType);
     locationPane->setWidget(pRoute);
     thisLayout->addWidget(/*locationPane*/pRouteFrame);

     // setup combo box
     addComboBoxAction(trainsComboBox);
     addComboBoxAction(typeComboBox);
     addComboBoxAction(carsComboBox);

     //locationManager.addPropertyChangeListener(this);
     connect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().addPropertyChangeListener(this);
     connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     // listen to all tracks and locations
     addLocationAndTrackPropertyChange();

     addHelpMenu("package.jmri.jmrit.operations.Operations_TrainShowCarTypesServiced", true); // NOI18N

     resize(QSize());
     initMinimumSize();
 }

 /*public*/ void TrainByCarTypeFrame::comboBoxActionPerformed(QWidget* ae) {
     log->debug("combo box action");
     JComboBox* source = (JComboBox*)ae;
     if (source == (typeComboBox)) {
         updateCarsComboBox();
     }
     updateRoute();
 }

 /*private*/ void TrainByCarTypeFrame::updateRoute() {
     if (_train != NULL) {
        // _train->removePropertyChangeListener(this);
      disconnect(_train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }

     //pRoute.removeAll();
     QLayoutItem* item;
     while ( ( item = pRoute->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }

     if (trainsComboBox->currentText() == NULL) {
         _train = NULL;
     } else {
         _train = (Train*) VPtr<Train>::asPtr(trainsComboBox->currentData());
     }

     if (_train == NULL) {
         setTitle(tr("Show Car Types"));
         update();
         return;
     }

     setTitle(tr("Show Car Types") + " " + _train->getName());
     //_train->addPropertyChangeListener(this);
     connect(_train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     setTitle(tr("Show Car Types") + " " + _train->getName());
     log->debug(tr("update locations served by train (%1)").arg(_train->getName()));

     int y = 0;
     QString carType =  typeComboBox->currentText();
     if (_car != NULL) {
         //_car->removePropertyChangeListener(this);
      disconnect(_car, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     _car = NULL;
     if (carsComboBox->currentText() != NULL) {
         _car = (Car*) VPtr<Car>::asPtr(carsComboBox->currentData());
         //_car->addPropertyChangeListener(this);
         connect(_car, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     Route* route = _train->getRoute();
     if (route == NULL) {
         return;
     }
     QList<RouteLocation*>* routeList = route->getLocationsBySequenceList();
     foreach (RouteLocation* rl, *routeList) {
         QLabel* loc = new QLabel();
         QString locationName = rl->getName();
         loc->setText(locationName);
         addItemLeft(pRoute, loc, 0, y++);
         Location* location = locationManager->getLocationByName(locationName);
         if (_car != NULL && _car->getTrack() != NULL && !_car->getTrack()->acceptsDestination(location) && _car->getLocation() != location) {
             QLabel* locText = new QLabel();
             locText->setText(tr("Car (%1) on track (%2) has destination restriction").arg(
                     _car->toString()).arg(_car->getTrackName()));
             addItemWidth(pRoute, locText, 2, 1, y++);
             continue;
         }
         QList<Track*> tracks = location->getTrackByNameList(NULL);
         foreach (Track* track, tracks) {
             // show the car's track if there's a track destination restriction
             if (_car != NULL && _car->getTrack() != NULL && !_car->getTrack()->acceptsDestination(location)
                     && _car->getTrack() != track) {
                 continue;
             }
             QLabel* trk = new QLabel();
             trk->setText(track->getName());
             addItemLeft(pRoute, trk, 1, y);
             // is the car at this location and track?
             if (_car != NULL && location==(_car->getLocation()) && track==(_car->getTrack())) {
                 QLabel* here = new QLabel("  -->"); // NOI18N
                 addItemLeft(pRoute, here, 0, y);
             }
             QLabel* op = new QLabel();
             addItemLeft(pRoute, op, 2, y++);
             if (!_train->acceptsTypeName(carType)) {
                 op->setText(tr("X (Train Type)"));
             } else if (_car != NULL && !_train->acceptsRoadName(_car->getRoadName())) {
                 op->setText(tr("X (Train Road)"));
             } // TODO need to do the same tests for caboose changes in the train's route
             else if (_car != NULL && _car->isCaboose() && (_train->getRequirements() & Train::CABOOSE) > 0
                     && location==(_car->getLocation()) && track==(_car->getTrack())
                     && _train->getCabooseRoad()!=(Train::NONE) && _car->getRoadName()!=(_train->getCabooseRoad())
                     && location->getName()==(_train->getTrainDepartsName())) {
                 op->setText(tr("X (Train Road)"));
             } else if (_car != NULL && _car->hasFred() && (_train->getRequirements() & Train::FRED) > 0
                     && location==(_car->getLocation()) && track==(_car->getTrack())
                     && _train->getCabooseRoad()!=(Train::NONE) && _car->getRoadName()!=(_train->getCabooseRoad())
                     && location->getName()==(_train->getTrainDepartsName())) {
                 op->setText(tr("X(TrainRoad)"));
             } else if (_car != NULL && !_car->isCaboose() && !_car->isPassenger()
                     && !_train->acceptsLoad(_car->getLoadName(), _car->getTypeName())) {
                 op->setText(tr("X (Train Load)"));
             } else if (_car != NULL && !_train->acceptsBuiltDate(_car->getBuilt())) {
                 op->setText(tr("X (Train Built)"));
             } else if (_car != NULL && !_train->acceptsOwnerName(_car->getOwner())) {
                 op->setText(tr("X (Train Owner)"));
             } else if (_train->skipsLocation(rl->getId())) {
                 op->setText(tr("X (Train Skips)"));
             } else if (!rl->isDropAllowed() && !rl->isPickUpAllowed()) {
                 op->setText(tr("X(Route)"));
             } else if (rl->getMaxCarMoves() <= 0) {
                 op->setText(tr("X (Route Moves)"));
             } else if (!location->acceptsTypeName(carType)) {
                 op->setText(tr("X (Location Type)"));
             } // check route before checking train, check train calls check route
             else if (!track->acceptsPickupRoute(route) && !track->acceptsDropRoute(route)) {
                 op->setText(tr("X(TrackRoute)"));
             } else if (!track->acceptsPickupTrain(_train) && !track->acceptsDropTrain(_train)) {
                 op->setText(tr("X(TrackTrain)"));
             } else if (!track->acceptsTypeName(carType)) {
                 op->setText(tr("X(TrackType)"));
             } else if (_car != NULL && !track->acceptsRoadName(_car->getRoadName())) {
                 op->setText(tr("X(TrackRoad)"));
             } else if (_car != NULL && !track->acceptsLoad(_car->getLoadName(), _car->getTypeName())) {
                 op->setText(tr("X(TrackLoad)"));
             } else if (_car != NULL && !track->acceptsDestination(_car->getFinalDestination())) {
                 op->setText(tr("X(TrackDestination)"));
             } else if ((rl->getTrainDirection() & location->getTrainDirections()) == 0) {
                 op->setText(tr("X(DirLoc)"));
             } else if ((rl->getTrainDirection() & track->getTrainDirections()) == 0) {
                 op->setText(tr("X(DirTrk)"));
             } else if (!checkScheduleAttribute(TYPE, carType, NULL, track)) {
                 op->setText(tr("X(ScheduleType)"));
             } else if (!checkScheduleAttribute(LOAD, carType, _car, track)) {
                 op->setText(tr("X(ScheduleLoad)"));
             } else if (!checkScheduleAttribute(ROAD, carType, _car, track)) {
                 op->setText(tr("X(ScheduleRoad)"));
             } else if (!checkScheduleAttribute(TIMETABLE, carType, _car, track)) {
                 op->setText(tr("X(ScheduleTimeTable)"));
             } else if (!checkScheduleAttribute(ALL, carType, _car, track)) {
                 op->setText(tr("X(Schedule)"));
             } else if (!track->acceptsPickupTrain(_train)) {
                 // can the train drop off car?
                 if (rl->isDropAllowed() && track->acceptsDropTrain(_train)) {
                     op->setText(tr("DropOnly"));
                 } else {
                     op->setText(tr("X(TrainPickup)"));
                 }
             } else if (!track->acceptsDropTrain(_train)) // can the train pick up car?
             {
                 if (rl->isPickUpAllowed() && track->acceptsPickupTrain(_train)) {
                     op->setText(tr("PickupOnly"));
                 } else {
                     op->setText(tr("X(TrainDrop)"));
                 }
             } else if (rl->isDropAllowed() && rl->isPickUpAllowed()) {
                 op->setText(tr("OK"));
             } else if (rl->isDropAllowed()) {
                 op->setText(tr("DropOnly"));
             } else if (rl->isPickUpAllowed()) {
                 op->setText(tr("PickupOnly"));
             } else {
                 op->setText("X"); // default shouldn't occur
             }
         }
     }
     pRoute->update();
     update();
 }

 /*private*/ /*static*/ /*final*/ QString TrainByCarTypeFrame::ROAD = "road"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainByCarTypeFrame::LOAD = "load"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainByCarTypeFrame::TIMETABLE = "timetable"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainByCarTypeFrame::TYPE = "type"; // NOI18N
 /*private*/ /*static*/ /*final*/ QString TrainByCarTypeFrame::ALL = "all"; // NOI18N

 /*private*/ bool TrainByCarTypeFrame::checkScheduleAttribute(QString attribute, QString carType, Car* car, Track* track) {
     Schedule* schedule = track->getSchedule();
     if (schedule == NULL) {
         return true;
     }
     // if car is already placed at track, don't check car type and load
     if (car != NULL && car->getTrack() == track) {
         return true;
     }
     QList<ScheduleItem*> scheduleItems = schedule->getItemsBySequenceList();
     foreach (ScheduleItem* si, scheduleItems) {
         // check to see if schedule services car type
         if (attribute==(TYPE) && si->getTypeName()==(carType)) {
             return true;
         }
         // check to see if schedule services car type and load
         if (attribute==(LOAD)
                 && si->getTypeName()==(carType)
                 && (si->getReceiveLoadName()==(ScheduleItem::NONE) || car == NULL || si->getReceiveLoadName()==(
                         car->getLoadName()))) {
             return true;
         }
         // check to see if schedule services car type and road
         if (attribute==(ROAD) && si->getTypeName()==(carType)
                 && (si->getRoadName()==(ScheduleItem::NONE) || car == NULL || si->getRoadName()==(car->getRoadName()))) {
             return true;
         }
         // check to see if schedule timetable allows delivery
         if (attribute==(TIMETABLE)
                 && si->getTypeName()==(carType)
                 && (si->getSetoutTrainScheduleId()==("") || ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainScheduleActiveId()
                 ==(si->getSetoutTrainScheduleId()))) {
             return true;
         }
         // check to see if at least one schedule item can service car
         if (attribute==(ALL)
                 && si->getTypeName()==(carType)
                 && (si->getReceiveLoadName()==(ScheduleItem::NONE) || car == NULL || si->getReceiveLoadName()==(
                         car->getLoadName()))
                 && (si->getRoadName()==(ScheduleItem::NONE) || car == NULL || si->getRoadName()==(car->getRoadName()))
                 && (si->getSetoutTrainScheduleId()==(ScheduleItem::NONE) || ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainScheduleActiveId()
                 ==(si->getSetoutTrainScheduleId()))) {
             return true;
         }
     }
     return false;
 }

 /*private*/ void TrainByCarTypeFrame::updateComboBox() {
     log->debug("update combobox");
     ((CarTypes*)InstanceManager::getDefault("CarTypes"))->updateComboBox(typeComboBox);
 }

 /*private*/ void TrainByCarTypeFrame::updateCarsComboBox() {
     log->debug("update car combobox");
     carsComboBox->clear();
     QString carType =  typeComboBox->currentText();
     // load car combobox
     carsComboBox->addItem(NULL);
     QList<RollingStock*>* cars = ((CarManager*)InstanceManager::getDefault("CarManager"))->getByTypeList(carType);
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         carsComboBox->addItem(car->toString(), VPtr<Car>::asQVariant(car));
     }
 }

 /*private*/ void TrainByCarTypeFrame::adjustCarsComboBoxSize() {
     QList<RollingStock*>* cars = ((CarManager*)InstanceManager::getDefault("CarManager"))->getList();
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         carsComboBox->addItem(car->toString(), VPtr<Car>::asQVariant(car));
     }
     QSize boxsize = carsComboBox->minimumSize();
     if (boxsize != QSize()) {
         //boxsize.setSize(boxsize.width + 10, boxsize.height);
      boxsize.setWidth(boxsize.width()+10);
         carsComboBox->setMinimumSize(boxsize);
     }
     carsComboBox->clear();
 }

 /**
  * Add property listeners for locations and tracks
  */
 /*private*/ void TrainByCarTypeFrame::addLocationAndTrackPropertyChange() {
     foreach (Location* loc, locationManager->getList()) {
         //loc.addPropertyChangeListener(this);
      connect(loc, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         foreach (Track* track, loc->getTrackList()) {
             //track->addPropertyChangeListener(this);
          connect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             Schedule* schedule = track->getSchedule();
             if (schedule != NULL) {
                 //schedule.addPropertyChangeListener(this);
              connect(schedule, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             }
         }
     }
 }

 /**
  * Remove property listeners for locations and tracks
  */
 /*private*/ void TrainByCarTypeFrame::removeLocationAndTrackPropertyChange() {
     foreach (Location* loc, locationManager->getList()) {
         //loc.removePropertyChangeListener(this);
      disconnect(loc, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         foreach (Track* track, loc->getTrackList()) {
             //track->removePropertyChangeListener(this);
          disconnect(track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             Schedule* schedule = track->getSchedule();
             if (schedule != NULL) {
                 //schedule.removePropertyChangeListener(this);
              disconnect(schedule, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
             }
         }
     }
 }

 /*public*/ void TrainByCarTypeFrame::dispose() {
     //locationManager.removePropertyChangeListener(this);
 disconnect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
 disconnect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     removeLocationAndTrackPropertyChange();
     if (_train != NULL) {
         //_train->removePropertyChangeListener(this);
      disconnect(_train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     if (_car != NULL) {
         //_car->removePropertyChangeListener(this);
      disconnect(_car, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void TrainByCarTypeFrame::propertyChange(PropertyChangeEvent* e) {
     log->debug(tr("Property change (%1) old: (%2) new: (%3").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString())); // NOI18N
     if (e->getSource()==(_car) || e->getSource()==(_train)
             || QString(e->getSource()->metaObject()->className())==("Track") || QString(e->getSource()->metaObject()->className())==("Location")
             || QString(e->getSource()->metaObject()->className())==("Schedule")
             || e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Route::LISTCHANGE_CHANGED_PROPERTY)) {
         updateRoute();
     }
     if (e->getPropertyName()==(Train::DISPOSE_CHANGED_PROPERTY)) {
         dispose();
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)) {
         updateComboBox();
     }
     if (e->getPropertyName()==(Location::LENGTH_CHANGED_PROPERTY)) {
         // a track has been add or deleted update property listeners
         removeLocationAndTrackPropertyChange();
         addLocationAndTrackPropertyChange();
     }
 }
/*public*/ QString TrainByCarTypeFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainByCarTypeFrame";
}

}
