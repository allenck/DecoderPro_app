#include "train.h"
#include "propertychangesupport.h"
#include "route.h"
#include "setup.h"
#include "trainmanagerxml.h"
#include "xml.h"
#include "routemanager.h"
#include "control.h"
#include "propertychangeevent.h"
#include "routelocation.h"
#include "trainicon.h"
#include "editor.h"
#include "engine.h"
#include "enginemanager.h"
#include "panelmenu.h"
#include "consist.h"
#include "instancemanager.h"
#include "throttlemanager.h"
#include "routelocation.h"
#include "roster.h"
#include "rosterentry.h"
#include "cartypes.h"
#include "carroads.h"
#include "enginetypes.h"
#include "enginemodels.h"
#include "stringutil.h"
#include "car.h"
#include "traincommon.h"
#include "carmanager.h"
#include "calendar.h"
#include "carload.h"
#include "locationmanager.h"
#include "location.h"
#include "track.h"
#include "carowners.h"
#include "trainmanager.h"
#include "trainmanifest.h"
#include "fileutil.h"
#include "trainprintutilities.h"
#include "trainbuilder.h"
#include "kernel.h"
#include "jsonmanifest.h"
#include "traincsvmanifest.h"
#include <QTextEdit>
#include "traincustommanifest.h"
#include "joptionpane.h"

/**
 * Represents a train on the layout
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2009, 2010, 2011, 2012, 2013,
 *         2014
 * @author Rodney Black Copyright (C) 2011
 * @version $Revision: 29897 $
 */
///*public*/ class Train implements java.beans.PropertyChangeListener {

namespace Operations
{

 /*
  * WARNING DO NOT LOAD CAR OR ENGINE MANAGERS WHEN Train.java IS CREATED IT
  * CAUSES A RECURSIVE LOOP AT LOAD TIME, SEE EXAMPLES BELOW CarManager
  * carManager = CarManager.instance(); EngineManager engineManager =
  * EngineManager.instance();
  */

 /*public*/ /*static*/ /*final*/ QString Train::NONE = "";



 // property change names
 /*public*/ /*static*/ /*final*/ QString Train::DISPOSE_CHANGED_PROPERTY = "TrainDispose"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::STOPS_CHANGED_PROPERTY = "TrainStops"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TYPES_CHANGED_PROPERTY = "TrainTypes"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::BUILT_CHANGED_PROPERTY = "TrainBuilt"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::BUILT_YEAR_CHANGED_PROPERTY = "TrainBuiltYear"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::BUILD_CHANGED_PROPERTY = "TrainBuild"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::ROADS_CHANGED_PROPERTY = "TrainRoads"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::LOADS_CHANGED_PROPERTY = "TrainLoads"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::OWNERS_CHANGED_PROPERTY = "TrainOwners"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::NAME_CHANGED_PROPERTY = "TrainName"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::DESCRIPTION_CHANGED_PROPERTY = "TrainDescription"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::STATUS_CHANGED_PROPERTY = "TrainStatus"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::DEPARTURETIME_CHANGED_PROPERTY = "TrainDepartureTime"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_LOCATION_CHANGED_PROPERTY = "TrainLocation"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_ROUTE_CHANGED_PROPERTY = "TrainRoute"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_REQUIREMENTS_CHANGED_PROPERTY = "TrainRequirements"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY = "TrainMoveComplete"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_ROW_COLOR_CHANGED_PROPERTY = "TrianRowColor"; // NOI18N

 // Train status
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_RESET = tr("TrainReset");
 /*public*/ /*static*/ /*final*/ QString Train::RUN_SCRIPTS = tr("RunScripts");
 /*public*/ /*static*/ /*final*/ QString Train::BUILDING = tr("Building");
 /*public*/ /*static*/ /*final*/ QString Train::BUILD_FAILED = tr("BuildFailed");
 /*public*/ /*static*/ /*final*/ QString Train::BUILT = tr("Built");
 /*public*/ /*static*/ /*final*/ QString Train::PARTIAL_BUILT = tr("Partial");
 /*public*/ /*static*/ /*final*/ QString Train::TRAIN_IN_ROUTE = tr("TrainInRoute");
 /*public*/ /*static*/ /*final*/ QString Train::TERMINATED = tr("Terminated");

// // Train status codes
// /*public*/ /*static*/ /*final*/ int Train::CODE_TRAIN_RESET = 0;
// /*public*/ /*static*/ /*final*/ int Train::CODE_RUN_SCRIPTS = 0x100;
// /*public*/ /*static*/ /*final*/ int Train::CODE_BUILDING = 0x01;
// /*public*/ /*static*/ /*final*/ int Train::CODE_BUILD_FAILED = 0x02;
// /*public*/ /*static*/ /*final*/ int Train::CODE_BUILT = 0x10;
// /*public*/ /*static*/ /*final*/ int Train::CODE_PARTIAL_BUILT = CODE_BUILT + 0x04;
// /*public*/ /*static*/ /*final*/ int Train::CODE_TRAIN_EN_ROUTE = CODE_BUILT + 0x08;
// /*public*/ /*static*/ /*final*/ int Train::CODE_TERMINATED = 0x80;
// /*public*/ /*static*/ /*final*/ int Train::CODE_UNKNOWN = 0xFFFF;

 // train requirements
 /*public*/ /*static*/ /*final*/ int Train::NO_CABOOSE_OR_FRED = 0; // default
 /*public*/ /*static*/ /*final*/ int Train::CABOOSE = 1;
 /*public*/ /*static*/ /*final*/ int Train::FRED = 2;

 // road options
 /*public*/ /*static*/ /*final*/ QString Train::ALL_ROADS = tr("All"); // train services all road names
 /*public*/ /*static*/ /*final*/ QString Train::INCLUDE_ROADS = tr("Include");
 /*public*/ /*static*/ /*final*/ QString Train::EXCLUDE_ROADS = tr("Exclude");

 // owner options
 /*public*/ /*static*/ /*final*/ QString Train::ALL_OWNERS = tr("All"); // train services all owner names
 /*public*/ /*static*/ /*final*/ QString Train::INCLUDE_OWNERS = tr("Include");
 /*public*/ /*static*/ /*final*/ QString Train::EXCLUDE_OWNERS = tr("Exclude");

 // load options
 /*public*/ /*static*/ /*final*/ QString Train::ALL_LOADS = tr("All"); // train services all loads
 /*public*/ /*static*/ /*final*/ QString Train::INCLUDE_LOADS = tr("Include");
 /*public*/ /*static*/ /*final*/ QString Train::EXCLUDE_LOADS = tr("Exclude");

 // Switch list status
 /*public*/ /*static*/ /*final*/ QString Train::UNKNOWN = "";
 /*public*/ /*static*/ /*final*/ QString Train::PRINTED = tr("Printed");

 /*public*/ /*static*/ /*final*/ QString Train::AUTO = tr("Auto"); // how engines are assigned to this train
 /*public*/ /*static*/ /*final*/ QString Train::AUTO_HPT = tr("AutoHPT"); // how engines are assigned to this train

/*public*/ Train::Train(QString id, QString name,QObject *parent) :
QObject(parent)
{
 common();
 log->debug(tr("New train (%1) id: %2").arg(name).arg(id));
 _name = name;
 _id = id;
 // a new train accepts all types
 setTypeNames(CarTypes::instance()->getNames());
 setTypeNames(EngineTypes::instance()->getNames());
 addPropertyChangeListerners();
}

void Train::common()
{
setObjectName("Train");
log = new Logger("Train");
pcs = new PropertyChangeSupport(this);
_skipLocationsList = QStringList();
_trainIconRl = NULL; // saves the icon current route location
_trainIcon = NULL;
debugFlag = false;
_ownerList = QStringList();
_loadList = QStringList();
_id = NONE;
_name = NONE;
_description = NONE;
_current = NULL;// where the train is located in its route
_buildFailedMessage = NONE; // the build failed message for this train
_built = false; // when true, a train manifest has been built
_modified = false; // when true, user has modified train after being built
_build = true; // when true, build this train
_buildFailed = false; // when true, build for this train failed
_printed = false; // when true, manifest has been printed
_sendToTerminal = false; // when true, cars picked up by train only go to terminal
_allowLocalMoves = true; // when true, cars with custom loads can be moved locally
_allowThroughCars = true; // when true, cars from the origin can be sent to the terminal
_buildNormal = false; // when true build this train in normal mode
_allowCarsReturnStaging = false; // when true allow cars to return to staging if necessary
_serviceAllCarsWithFinalDestinations = false; // when true, service cars with /*final*/ destinations
_buildConsist = false; // when true, build a consist for this train using single locomotives
_sendCarsWithCustomLoadsToStaging = false; // when true, send cars to staging if spurs full
_route = NULL;
_departureTrack = NULL;
_terminationTrack = NULL;
_roadOption = ALL_ROADS;// train road name restrictions
_requires = 0; // train requirements, caboose, FRED
_numberEngines = "0"; // number of engines this train requires
_engineRoad = NONE; // required road name for engines assigned to this train
_engineModel = NONE; // required model of engines assigned to this train
_cabooseRoad = NONE; // required road name for cabooses assigned to this train
_departureTime = Calendar::getInstance(); // departure time for this train
_leadEngineId = NONE; // lead engine for train icon info
_builtStartYear = NONE; // built start year
_builtEndYear = NONE; // built end year
_loadOption = ALL_LOADS;// train load restrictions
_ownerOption = ALL_OWNERS;// train owner name restrictions
_buildScripts =  QStringList(); // list of script pathnames to run before train is
// built
_afterBuildScripts =  QStringList(); // list of script pathnames to run after train
// is built
_moveScripts =  QStringList(); // list of script pathnames to run when train is
// moved
_terminationScripts =  QStringList(); // list of script pathnames to run when train
// is terminated
_railroadName = NONE; // optional railroad name for this train
_logoURL = NONE; // optional manifest logo for this train
_showTimes = true; // when true, show arrival and departure times for this train
_leadEngine = NULL; // lead engine for icon
_switchListStatus = UNKNOWN; // print switch list status
_comment = NONE;
_serviceStatus = NONE; // status only if train is being built
_statusCode = CODE_UNKNOWN;
_statusTerminatedDate = NONE;
_statusCarsRequested = 0;
_tableRowColorName = NONE; //color of row in Trains table

// Engine change and helper engines
_leg2Options = 0; // options
_leg2Start = NULL; // route location when 2nd leg begins
_end2Leg = NULL; // route location where 2nd leg ends
_leg2Engines = "0"; // number of engines 2nd leg
_leg2Road = NONE; // engine road name 2nd leg
_leg2Model = NONE; // engine model 2nd leg
_leg2CabooseRoad = NONE; // road name for caboose 2nd leg

_leg3Options = 0; // options
_leg3Start = NULL; // route location when 3rd leg begins
_leg3End = NULL; // route location where 3rd leg ends
_leg3Engines = "0"; // number of engines 3rd leg
_leg3Road = NONE; // engine road name 3rd leg
_leg3Model = NONE; // engine model 3rd leg
_leg3CabooseRoad = NONE; // road name for caboose 3rd leg

_typeList = QStringList();
_roadList = QStringList();

}

/*public*/ QString Train::getId() {
 return _id;
}

/**
* Sets the name of this train, normally a short name that can fit within
* the train icon.
*
* @param name the train's name.
*/
/*public*/ void Train::setName(QString name) {
 QString old = _name;
 _name = name;
 if (old!=(name)) {
     setDirtyAndFirePropertyChange(NAME_CHANGED_PROPERTY, old, name);
 }
}

// for combo boxes
/**
* Get's a train's name
*
* @return train's name
*/
/*public*/ QString Train::toString() {
 return _name;
}

/**
* Get's a train's name
*
* @return train's name
*/
/*public*/ QString Train::getName() {
 return _name;
}

/**
*
* @return The name of the color when highlighting the train's row
*/
/*public*/ QString Train::getTableRowColorName() {
 return _tableRowColorName;
}

/*public*/ void Train::setTableRowColorName(QString colorName) {
 QString old = _tableRowColorName;
 _tableRowColorName = colorName;
 if (old!=(colorName)) {
     setDirtyAndFirePropertyChange(TRAIN_ROW_COLOR_CHANGED_PROPERTY, old, colorName);
 }
}

/**
*
* @return The color when highlighting the train's row
*/
/*public*/ QColor Train::getTableRowColor() {
 return Setup::getColor(getTableRowColorName());
}

 /**
  * Get's train's departure time
  *
  * @return train's departure time in the String format hh:mm
  */
 /*public*/ QString Train::getDepartureTime()
 {
  // check to see if the route has a departure time
  RouteLocation* rl = getTrainDepartsRouteLocation();
  if (rl != NULL)
  {
   //rl->removePropertyChangeListener(this);
   disconnect(rl, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   //rl.addPropertyChangeListener(this);
   connect(rl, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   if (rl->getDepartureTime()!=(RouteLocation::NONE)) {
       return rl->getDepartureTime();
   }
  }
  int hour = _departureTime->get(Calendar::HOUR_OF_DAY);
  int minute = _departureTime->get(Calendar::MINUTE);
  QString h = QString::number(hour);
  if (hour < 10) {
      h = "0" + h;
  }
  if (minute < 10) {
      return h + ":0" + QString::number(minute); // NOI18N
  }
  return h + ":" + QString::number(minute);
 }

 /**
  * Get's train's departure time in 12hr or 24hr format
  *
  * @return train's departure time in the String format hh:mm or hh:mm(AM/PM)
  */
 /*public*/ QString Train::getFormatedDepartureTime() {
     // check to see if the route has a departure time
     RouteLocation* rl = getTrainDepartsRouteLocation();
     if (rl !=NULL&& rl->getDepartureTime()!=(RouteLocation::NONE)) {
         // need to forward any changes to departure time
         //rl.removePropertyChangeListener(this);
         disconnect(rl, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         //rl.addPropertyChangeListener(this);
         connect(rl, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         return rl->getFormatedDepartureTime();
     }
     int hour = _departureTime->get(Calendar::HOUR_OF_DAY);
     // AM_PM field
     QString am_pm = "";
     if (Setup::is12hrFormatEnabled()) {
         hour = _departureTime->get(Calendar::HOUR);
         if (hour == 0) {
             hour = 12;
         }
         am_pm = (_departureTime->get(Calendar::AM_PM) == Calendar::AM) ? " " + tr("AM") : " "
                 + tr("PM");
     }
     int minute = _departureTime->get(Calendar::MINUTE);
     QString h = QString::number(hour);
     if (hour < 10) {
         h = "0" + h;
     }
     if (minute < 10) {
         return h + ":0" + QString::number(minute) + am_pm; // NOI18N
     }
     return h + ":" + QString::number(minute) + am_pm;
 }

 /**
  * Get train's departure time in minutes from midnight for sorting
  *
  * @return int hh*60+mm
  */
 /*public*/ int Train::getDepartTimeMinutes() {
     int hour = getDepartureTimeHour().toInt();
     int minute = getDepartureTimeMinute().toInt();
     return (hour * 60) + minute;
 }

 /*public*/ void Train::setDepartureTime(QString hour, QString minute) {
     QString oldHour = getDepartureTimeHour();
     QString oldMinute = getDepartureTimeMinute();
     // new departure time?
     if ((hour.toInt() == oldHour.toInt())
             && (minute.toInt() == oldMinute.toInt()))
     {
         return;
     }
     _departureTime->set(Calendar::HOUR_OF_DAY, hour.toInt());
     _departureTime->set(Calendar::MINUTE, minute.toInt());
     setDirtyAndFirePropertyChange(DEPARTURETIME_CHANGED_PROPERTY, oldHour + ":" + oldMinute, hour + ":" + minute);
 }

 /*public*/ QString Train::getDepartureTimeHour() {
     QStringList time = getDepartureTime().split(":");
     return time[0];
 }

 /*public*/ QString Train::getDepartureTimeMinute() {
     QStringList time = getDepartureTime().split(":");
     return time[1];
 }

 /*public*/ /*static*/ /*final*/ QString Train::ALREADY_SERVICED = "-1"; // NOI18N

 /**
  * Gets the expected time when this train will arrive at the location rl.
  * Expected arrival time is based on the number of car pick up and set outs
  * for this train. TODO Doesn't provide expected arrival time if train is in
  * route, instead provides relative time. If train is at or has passed the
  * location return -1.
  *
  * @return expected arrival time
  */
 /*public*/ QString Train::getExpectedArrivalTime(RouteLocation* routeLocation) {
     int minutes = getExpectedTravelTimeInMinutes(routeLocation);
     if (minutes == -1) {
         return ALREADY_SERVICED;
     }
     log->debug(tr("Expected arrival time for train (%1) at (%2), %3 minutes").arg(getName()).arg(routeLocation
             ->getName()).arg(minutes));
     // TODO use fast clock to get current time vs departure time
     // for now use relative
     return parseTime(minutes);
 }

 /*public*/ QString Train::getExpectedDepartureTime(RouteLocation* routeLocation) {
     int minutes = getExpectedTravelTimeInMinutes(routeLocation);
     if (minutes == -1) {
         return ALREADY_SERVICED;
     }
     // figure out the work at this location, note that there can be consecutive locations with the same name
     if (getRoute() != NULL) {
         bool foundRouteLocation = false;
         foreach (RouteLocation* rl, *getRoute()->getLocationsBySequenceList()) {
             if (rl == routeLocation) {
                 foundRouteLocation = true;
             }
             if (foundRouteLocation) {
                 if (TrainCommon::splitString(rl->getName())==(TrainCommon::splitString(routeLocation->getName()))) {
                     minutes = minutes + calculateWorkTimeAtLocation(rl);
                 } else {
                     break; // done
                 }
             }
         }
     }
     log->debug(tr("Expected departure time %1 for train (%2) at (%3)").arg(minutes).arg(getName()).arg(routeLocation->getName()));
     return parseTime(minutes);
 }

 /*private*/ int Train::calculateWorkTimeAtLocation(RouteLocation* routeLocation) {
     int minutes = 0;
     // departure?
     if (routeLocation == getTrainDepartsRouteLocation())
         return minutes;
     // add any work at this location
     foreach (RollingStock* rs, *CarManager::instance()->getList(this)) {
         if (rs->getRouteLocation() == routeLocation && rs->getTrackName()!=(RollingStock::NONE)) {
             minutes += Setup::getSwitchTime();
         }
         if (rs->getRouteDestination() == routeLocation) {
             minutes += Setup::getSwitchTime();
         }
     }
     return minutes;
 }

 /*protected*/ int Train::getExpectedTravelTimeInMinutes(RouteLocation* routeLocation) {
     int minutes = 0;
     if (!isTrainInRoute()) {
         minutes += _departureTime->get(Calendar::MINUTE);
         minutes += 60 * _departureTime->get(Calendar::HOUR_OF_DAY);
     } else {
         minutes = -1; // -1 means train has already served the location
     }
     // bool trainAt = false;
     bool trainLocFound = false;
     if (getRoute() != NULL) {
         QList<RouteLocation*>* routeList = getRoute()->getLocationsBySequenceList();
         for (int i = 0; i < routeList->size(); i++) {
             RouteLocation* rl = routeList->at(i);
             if (rl == routeLocation) {
                 break; // done
             }
             // start recording time after finding where the train is
             if (!trainLocFound && isTrainInRoute()) {
                 if (rl == getCurrentLocation()) {
                     trainLocFound = true;
                     // add travel time
                     minutes = Setup::getTravelTime();
                 }
                 continue;
             }
             // is there a departure time from this location?
             if (rl->getDepartureTime()!=(RouteLocation::NONE)) {
                 QString dt = rl->getDepartureTime();
                 log->debug("Location " + rl->getName() + " departure time " + dt);
                 QStringList time = dt.split(":");
                 minutes = 60 * time[0].toInt() + time[1].toInt();
                 // log->debug("New minutes: "+minutes);
             }
             // add wait time
             minutes += rl->getWait();
             // add travel time if new location
             RouteLocation* next = routeList->at(i + 1);
             if (next != NULL
                     && TrainCommon::splitString(rl->getName())!=(TrainCommon::splitString(next->getName()))) {
                 minutes += Setup::getTravelTime();
             }
             // don't count work if there's a departure time
             if (i == 0 || rl->getDepartureTime()!=(RouteLocation::NONE)) {
                 continue;
             }
             // now add the work at the location
             minutes = minutes + calculateWorkTimeAtLocation(rl);
         }
     }
     return minutes;
 }

 /*private*/ QString Train::parseTime(int minutes) {
     int hours = 0;
     int days = 0;

     if (minutes >= 60) {
         int h = minutes / 60;
         minutes = minutes - h * 60;
         hours += h;
     }

     QString d = "";
     if (hours >= 24) {
         int nd = hours / 24;
         hours = hours - nd * 24;
         days += nd;
         d = QString::number(days) + ":";
     }

     // AM_PM field
     QString am_pm = "";
     if (Setup::is12hrFormatEnabled()) {
         am_pm = " " + tr("AM");
         if (hours >= 12) {
             hours = hours - 12;
             am_pm = " " + tr("PM");
         }
         if (hours == 0) {
             hours = 12;
         }
     }

     QString h = QString::number(hours);
     if (hours < 10) {
         h = "0" + h;
     }
     if (minutes < 10) {
         return d + h + ":0" + QString::number(minutes) + am_pm; // NOI18N
     }
     return d + h + ":" + QString::number(minutes) + am_pm;
 }

 /**
  * Set train requirements. If NONE, then train doesn't require a caboose or
  * car with FRED.
  *
  * @param requires NONE CABOOSE FRED
  */
 /*public*/ void Train::setRequirements(int requires) {
     int old = _requires;
     _requires = requires;
     if (old != requires) {
         setDirtyAndFirePropertyChange(TRAIN_REQUIREMENTS_CHANGED_PROPERTY, QString::number(old), (requires));
     }
 }

 /**
  * Get a train's requirements with regards to the last car in the train.
  *
  * @return NONE CABOOSE FRED
  */
 /*public*/ int Train::getRequirements() {
     return _requires;
 }

 /*public*/ void Train::setRoute(Route* route) {
     Route* old = _route;
     QString oldRoute = NONE;
     QString newRoute = NONE;
     if (old != NULL) {
         //old.removePropertyChangeListener(this);
//            oldRoute = old->toString();
     }
     if (route != NULL) {
         //route.addPropertyChangeListener(this);
      connect(route, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//            newRoute = route->toString();
     }
     _route = route;
     _skipLocationsList.clear();
     if (old ==NULL|| old!=(route)) {
         setDirtyAndFirePropertyChange(TRAIN_ROUTE_CHANGED_PROPERTY, oldRoute, newRoute);
     }
 }

 /**
  * Gets the train's route
  *
  * @return train's route
  */
 /*public*/ Route* Train::getRoute() {
     return _route;
 }

 /**
  * Get's the train's route name.
  *
  * @return Train's route name.
  */
 /*public*/ QString Train::getTrainRouteName() {
     if (_route == NULL) {
         return NONE;
     }
     return _route->getName();
 }

 /**
  * Get the train's departure location's name
  *
  * @return train's departure location's name
  */
 /*public*/ QString Train::getTrainDepartsName() {
     if (getTrainDepartsRouteLocation() != NULL) {
         return getTrainDepartsRouteLocation()->getName();
     }
     return NONE;
 }

 /*protected*/ RouteLocation* Train::getTrainDepartsRouteLocation() {
     if (_route == NULL) {
         return NULL;
     }
     return _route->getDepartsRouteLocation();
 }

 /*public*/ QString Train::getTrainDepartsDirection() {
     QString direction = NONE;
     if (getTrainDepartsRouteLocation() != NULL) {
         direction = getTrainDepartsRouteLocation()->getTrainDirectionString();
     }
     return direction;
 }

/**
* Get train's final location's name
*
* @return train's final location's name
*/
/*public*/ QString Train::getTrainTerminatesName() {
  if (getTrainTerminatesRouteLocation() != NULL) {
      return getTrainTerminatesRouteLocation()->getName();
  }
  return NONE;
}

/*protected*/ RouteLocation* Train::getTrainTerminatesRouteLocation() {
  if (_route == NULL) {
      return NULL;
  }
  return _route->getTerminatesRouteLocation();
}

/**
* Set train's current route location
*/
/*protected*/ void Train::setCurrentLocation(RouteLocation* location) {
  RouteLocation* old = _current;
  _current = location;
  if ((old != NULL && old!=location) || (old ==NULL && location != NULL)) {
      setDirtyAndFirePropertyChange("current", VPtr<RouteLocation>::asQVariant(old), VPtr<RouteLocation>::asQVariant(location)); // NOI18N
  }
}

/**
* Get train's current location name
*
* @return Train's current route location name
*/
/*public*/ QString Train::getCurrentLocationName() {
 if (getCurrentLocation() == NULL) {
     return NONE;
 }
 return getCurrentLocation()->getName();
}

/**
* Get train's current location
*
* @return Train's current route location
*/
/*public*/ RouteLocation* Train::getCurrentLocation() {
 if (getRoute() == NULL) {
     return NULL;
 }
 if (_current == NULL) {
     return NULL;
 }
 // this will verify that the current location still exists
 return getRoute()->getLocationById(_current->getId());
}

/**
* Get the train's next location name
*
* @return Train's next route location name
*/
/*public*/ QString Train::getNextLocationName() {
  return getNextLocationName(1);
}

/**
* Get a location name in a train's route from the current train's location.
* A number of "1" means get the next location name in a train's route.
*
* @param number The stop number, must be greater than 0
* @return Name of the location that is the number of stops away from the
*         train's current location.
*/
/*public*/ QString Train::getNextLocationName(int number) {
  RouteLocation* rl = getCurrentLocation();
  while (number-- > 0) {
      rl = getNextLocation(rl);
      if (rl == NULL) {
          return NONE;
      }
  }
  return rl->getName();
}

/*public*/ RouteLocation* Train::getNextLocation(RouteLocation* currentRouteLocation) {
 if (getRoute() == NULL) {
     return NULL;
 }
 QList<RouteLocation*>* routeList = getRoute()->getLocationsBySequenceList();
 for (int i = 0; i < routeList->size(); i++) {
     RouteLocation* rl = routeList->at(i);
     if (rl == currentRouteLocation) {
         i++;
         if (i < routeList->size()) {
             return routeList->at(i);
         }
         break;
     }
 }
 return NULL; // At end of route
}

 /*public*/ void Train::setDepartureTrack(Track* track) {
     Track* old = _departureTrack;
     _departureTrack = track;
     if (old != track) {
         setDirtyAndFirePropertyChange("DepartureTrackChanged", VPtr<Track>::asQVariant(old), VPtr<Track>::asQVariant(track)); // NOI18N
     }
 }

 /*public*/ Track* Train::getDepartureTrack() {
     return _departureTrack;
 }

 /*public*/ void Train::setTerminationTrack(Track* track) {
     Track* old = _terminationTrack;
     _terminationTrack = track;
     if (old != track) {
         setDirtyAndFirePropertyChange("TerminationTrackChanged", VPtr<Track>::asQVariant(old), VPtr<Track>::asQVariant(track)); // NOI18N
     }
 }

 /*public*/ Track* Train::getTerminationTrack() {
     return _terminationTrack;
 }

 /**
  * Set the train's machine readable status. Calls update train table row
  * color.
  *
  * @param status machine readable stringCode
  */
 /*public*/ void Train::setStatus(int status) {
     QString oldStatus = this->getStatus();
     int oldCode = _statusCode;
     _statusCode = status;
     // always fire property change for train in route
     if (oldCode != this->_statusCode || status == CODE_TRAIN_EN_ROUTE) {
         setDirtyAndFirePropertyChange(STATUS_CHANGED_PROPERTY, oldStatus, this->getStatus());
     }
//        updateTrainTableRowColor();
 }
#if 0
 private void updateTrainTableRowColor() {
     if (!TrainManager.instance().isRowColorManual()) {
         switch (_statusCode) {
             case CODE_TRAIN_RESET:
                 setTableRowColorName(NONE);
                 break;
             case CODE_BUILT:
             case CODE_PARTIAL_BUILT:
                 setTableRowColorName(TrainManager.instance()->getRowColorNameForBuilt());
                 break;
             case CODE_BUILD_FAILED:
                 setTableRowColorName(TrainManager.instance()->getRowColorNameForBuildFailed());
                 break;
             case CODE_TRAIN_EN_ROUTE:
                 setTableRowColorName(TrainManager.instance()->getRowColorNameForTrainEnRoute());
                 break;
             case CODE_TERMINATED:
                 setTableRowColorName(TrainManager.instance()->getRowColorNameForTerminated());
                 break;
             default: // all other cases do nothing
                 break;
         }
     }
 }
#endif
 /**
  * Get train's status in the default locale.
  *
  * @return Human-readable status
  */
 /*public*/ QString Train::getStatus() {
   return this->getStatus(QLocale());
 }

 /**
  * Get train's status in the specified locale.
  *
  * @param locale
  * @return Human-readable status
  */
 /*public*/ QString Train::getStatus(QLocale locale) {
     return this->getStatus(locale, this->getStatusCode());
 }

 /**
  * Get the human-readable status for the requested status code.
  *
  * @param locale
  * @param code requested status
  * @return Human-readable status
  */
 /*public*/ QString Train::getStatus(QLocale /*locale*/, int code)
{
  switch (code) {
      case CODE_RUN_SCRIPTS:
          return RUN_SCRIPTS;
      case CODE_BUILDING:
          return BUILDING;
      case CODE_BUILD_FAILED:
          return BUILD_FAILED;
      case CODE_BUILT:
          // getNumberCarsWorked() is assumed to be constant if status is "built" or "partially built"
          return tr(/*locale,*/ "Built %1 cars").arg(this->getNumberCarsWorked()); // NOI18N
      case CODE_PARTIAL_BUILT:
          // 0 should be number of cars requested to be worked
          return tr(/*locale,*/ "Partial %1/%2 cars").arg(this->getNumberCarsWorked()).arg(this
                  ->getNumberCarsRequested()); // NOI18N
      case CODE_TERMINATED:
          return tr(/*locale,*/ "Terminated %1").arg(this->getTerminationDate()); // NOI18N
      case CODE_TRAIN_EN_ROUTE:
          return tr(/*locale,*/ "Train en route %1 cars, %2 %3, %4 tons").arg(this->getNumberCarsInTrain()).arg(this->getTrainLength()).arg(Setup
                  ::getLengthUnit().toLower()).arg(this->getTrainWeight()); // NOI18N
      case CODE_TRAIN_RESET:
          return TRAIN_RESET;
      case CODE_UNKNOWN:
      default:
          return UNKNOWN;
  }
 }
#if 0
 /*public*/ QString getMRStatus() {
     switch (this._statusCode) {
         case CODE_PARTIAL_BUILT:
             return this._statusCode + "||" + this->getNumberCarsRequested(); // NOI18N
         case CODE_TERMINATED:
             return this._statusCode + "||" + this->getTerminationDate(); // NOI18N
         default:
             return QString::number(this._statusCode);
     }
 }
#endif
 /*public*/ int Train::getStatusCode() {
     return this->_statusCode;
 }

 /**
  * Used to determine if train has departed the first location in the train's
  * route
  *
  * @return true if train has departed
  */
 /*public*/ bool Train::isTrainInRoute() {
     return getCurrentLocationName()!=(NONE) && getTrainDepartsRouteLocation() != getCurrentLocation();
 }

 /**
  * Used to determine if train is a local switcher serving one location. Note
  * the the train can have more than location in its route, but all location
  * names must be "same". See TrainCommon::splitString(QString name) for the
  * definition of the "same" name.
  *
  * @return true if local switcher
  */
 /*public*/ bool Train::isLocalSwitcher() {
     QString departureName = TrainCommon::splitString(getTrainDepartsName());
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             QString name = TrainCommon::splitString(rl->getName());
             if (departureName!=(name)) {
                 return false; // not a local switcher
             }
         }
     }
     return true;
 }


 /*protected*/ QStringList Train::getTrainSkipsLocations() {
     QVector<QString> locationIds = QVector<QString>(_skipLocationsList.size());
     for (int i = 0; i < _skipLocationsList.size(); i++) {
         locationIds.replace(i, _skipLocationsList.at(i));
     }
     return locationIds.toList();
 }

 /*protected*/ void Train::setTrainSkipsLocations(QStringList locationIds) {
     if (locationIds.length() == 0) {
         return;
     }
     StringUtil::sort(locationIds);
     foreach (QString id, locationIds) {
         _skipLocationsList.append(id);
     }
 }

 /**
  * Train will skip the RouteLocation
  *
  * @param locationId RouteLocation* Id
  */
 /*public*/ void Train::addTrainSkipsLocation(QString locationId) {
     // insert at start of _skipLocationsList, sort later
     if (_skipLocationsList.contains(locationId)) {
         return;
     }
     _skipLocationsList.insert(0, locationId);
     log->debug("train does not stop at " + locationId);
     setDirtyAndFirePropertyChange(STOPS_CHANGED_PROPERTY, _skipLocationsList.size() - 1, _skipLocationsList.size());
 }

 /*public*/ void Train::deleteTrainSkipsLocation(QString locationId) {
     _skipLocationsList.removeOne(locationId);
     log->debug("train will stop at " + locationId);
     setDirtyAndFirePropertyChange(STOPS_CHANGED_PROPERTY, _skipLocationsList.size() + 1, _skipLocationsList.size());
 }

 /**
  * Determines if this train skips a location (doesn't service the location).
  *
  * @param locationId The route location id.
  * @return true if the train will not service the location.
  */
 /*public*/ bool Train::skipsLocation(QString locationId) {
     return _skipLocationsList.contains(locationId);
 }


 /**
  * Get's the type names of rolling stock this train will service
  *
  * @return The type names for cars and or engines
  */
 /*protected*/ QStringList Train::getTypeNames() {
     QVector<QString> types = QVector<QString>(_typeList.size());
     for (int i = 0; i < _typeList.size(); i++) {
         types.replace(i, _typeList.at(i));
     }
     return types.toList();
 }

 /*protected*/ QStringList Train::getCarTypeNames() {
     QStringList list = QStringList();
     foreach (QString type, _typeList) {
         if (CarTypes::instance()->containsName(type)) {
             list.append(type);
         }
     }
     QVector<QString> types = QVector<QString>(list.size());
     for (int i = 0; i < list.size(); i++) {
         types.replace(i, list.at(i));
     }
     return types.toList();
 }

 /*protected*/ QStringList Train::getLocoTypeNames() {
     QStringList list = QStringList();
     foreach (QString type, _typeList) {
         if (EngineTypes::instance()->containsName(type)) {
             list.append(type);
         }
     }
     QVector<QString> types = QVector<QString>(list.size());
     for (int i = 0; i < list.size(); i++) {
         types.replace(i, list.at(i));
     }
     return types.toList();
 }

 /**
  * Set the type of cars or engines this train will service, see types in
  * Cars and Engines.
  *
  * @param types The type names for cars and or engines
  */
 /*protected*/ void Train::setTypeNames(QStringList types) {
     if (types.length() == 0) {
         return;
     }
     StringUtil::sort(types);
     foreach (QString type, types) {
         _typeList.append(type);
     }
 }

 /**
  * Add a car or engine type name that this train will service.
  *
  * @param type The new type name to service.
  */
 /*public*/ void Train::addTypeName(QString type) {
     // insert at start of list, sort later
     if (type ==NULL|| _typeList.contains(type)) {
         return;
     }
     _typeList.insert(0, type);
     log->debug(tr("Train (%1) add car type (%2)").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _typeList.size() - 1, _typeList.size());
 }

 /*public*/ void Train::deleteTypeName(QString type) {
     if (!_typeList.contains(type)) {
         return;
     }
     _typeList.removeOne(type);
     log->debug(tr("Train (%1) delete car type (%2)").arg(getName()).arg(type));
     setDirtyAndFirePropertyChange(TYPES_CHANGED_PROPERTY, _typeList.size() + 1, _typeList.size());
 }

 /**
  * Returns true if this train will service the type of car or engine.
  *
  * @param type The car or engine type name.
  * @return true if this train will service the particular type.
  */
 /*public*/ bool Train::acceptsTypeName(QString type) {
     return _typeList.contains(type);
 }

 /*public*/ void Train::replaceType(QString oldType, QString newType) {
     if (acceptsTypeName(oldType)) {
         deleteTypeName(oldType);
         addTypeName(newType);
         // adjust custom loads
#if 0
         foreach (QString load, getLoadNames()) {
             QStringList splitLoad = load.split(CarLoad.SPLIT_CHAR);
             if (splitLoad.length() > 1) {
                 if (splitLoad[0]==(oldType)) {
                     deleteLoadName(load);
                     if (newType != NULL) {
                         load = newType + CarLoad.SPLIT_CHAR + splitLoad[1];
                         addLoadName(load);
                     }
                 }
             }
         }
#endif
     }
 }

 /**
  * Get how this train deals with road names.
  *
  * @return ALL_ROADS INCLUDE_ROADS EXCLUDE_ROADS
  */
 /*public*/ QString Train ::getRoadOption() {
     return _roadOption;
 }

 /**
  * Set how this train deals with car road names.
  *
  * @param option ALL_ROADS INCLUDE_ROADS EXCLUDE_ROADS
  */
 /*public*/ void Train ::setRoadOption(QString option) {
     QString old = _roadOption;
     _roadOption = option;
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, old, option);
 }

 /*protected*/ void Train ::Train::setRoadNames(QStringList roads) {
if (roads.length() == 0) {
         return;
     }
     StringUtil::sort(roads);
     foreach (QString road, roads) {
         if (road!=("")) {
             _roadList.append(road);
         }
     }
 }

 /**
  * Provides a list of road names that the train will either service or
  * exclude. See setRoadOption
  *
  * @return Array of road names as Strings
  */
 /*public*/ QStringList Train::getRoadNames() {
     QVector<QString> roads = QVector<QString>(_roadList.size());
     for (int i = 0; i < _roadList.size(); i++) {
      roads.replace(i, _roadList.at(i));
     }
     if (_roadList.size() == 0) {
         return roads.toList();
     }
     StringUtil::sort(roads.toList());
     return roads.toList();
 }

 /**
  * Add a road name that the train will either service or exclude. See
  * setRoadOption
  *
  * @return true if road name was added, false if road name wasn't in the
  *         list.
  */
 /*public*/ bool Train::addRoadName(QString road) {
     if (_roadList.contains(road)) {
         return false;
     }
     _roadList.append(road);
     log->debug("train (" + getName() + ") add car road " + road);
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, _roadList.size() - 1, _roadList.size());
     return true;
 }

 /**
  * Delete a road name that the train will either service or exclude. See
  * setRoadOption
  *
  * @return true if road name was removed, false if road name wasn't in the
  *         list.
  */
 /*public*/ bool Train::deleteRoadName(QString road) {
     if (!_roadList.contains(road)) {
         return false;
     }
     _roadList.removeOne(road);
     log->debug("train (" + getName() + ") delete car road " + road);
     setDirtyAndFirePropertyChange(ROADS_CHANGED_PROPERTY, _roadList.size() + 1, _roadList.size());
     return true;
 }

 /**
  * Determine if train will service a specific road name.
  *
  * @param road the road name to check.
  * @return true if train will service this road name.
  */
 /*public*/ bool Train ::acceptsRoadName(QString road) {
     if (_roadOption==(ALL_ROADS)) {
         return true;
     }
     if (_roadOption==(INCLUDE_ROADS)) {
         return _roadList.contains(road);
     }
     // exclude!
     return !_roadList.contains(road);
 }

 /*private*/ void Train::replaceRoad(QString oldRoad, QString newRoad) {
     if (newRoad != NULL) {
         if (deleteRoadName(oldRoad)) {
             addRoadName(newRoad);
         }
         if (getEngineRoad()==(oldRoad)) {
             setEngineRoad(newRoad);
         }
         if (getCabooseRoad()==(oldRoad)) {
             setCabooseRoad(newRoad);
         }
         if (getSecondLegEngineRoad()==(oldRoad)) {
             setSecondLegEngineRoad(newRoad);
         }
         if (getSecondLegCabooseRoad()==(oldRoad)) {
             setSecondLegCabooseRoad(newRoad);
         }
         if (getThirdLegEngineRoad()==(oldRoad)) {
             setThirdLegEngineRoad(newRoad);
         }
         if (getThirdLegCabooseRoad()==(oldRoad)) {
             setThirdLegCabooseRoad(newRoad);
         }
     }
 }

 /**
  * Gets the car load option for this train.
  *
  * @return ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ QString Train::getLoadOption() {
     return _loadOption;
 }

 /**
  * Set how this train deals with car loads
  *
  * @param option ALL_LOADS INCLUDE_LOADS EXCLUDE_LOADS
  */
 /*public*/ void Train::setLoadOption(QString option) {
     QString old = _loadOption;
     _loadOption = option;
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, old, option);
 }


 /*protected*/ void Train::setLoadNames(QStringList loads) {
     if (loads.length() == 0) {
         return;
     }
     StringUtil::sort(loads);
     foreach (QString load, loads) {
         if (load!=("")) {
             _loadList.append(load);
         }
     }
 }

 /**
  * Provides a list of loads that the train will either service or exclude.
  * See setLoadOption
  *
  * @return Array of load names as Strings
  */
 /*public*/ QStringList Train::getLoadNames() {
     QVector<QString> loads = QVector<QString>(_loadList.size());
     for (int i = 0; i < _loadList.size(); i++) {
         loads.replace(i, _loadList.at(i));
     }
     if (_loadList.size() == 0) {
         return loads.toList();
     }
     StringUtil::sort(loads.toList());
     return loads.toList();
 }

 /**
  * Add a load that the train will either service or exclude. See
  * setLoadOption
  *
  * @return true if load name was added, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Train::addLoadName(QString load) {
     if (_loadList.contains(load)) {
         return false;
     }
     _loadList.append(load);
     log->debug("train (" + getName() + ") add car load " + load);
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _loadList.size() - 1, _loadList.size());
     return true;
 }

 /**
  * Delete a load name that the train will either service or exclude. See
  * setLoadOption
  *
  * @return true if load name was removed, false if load name wasn't in the
  *         list.
  */
 /*public*/ bool Train::deleteLoadName(QString load) {
     if (!_loadList.contains(load)) {
         return false;
     }
     _loadList.removeOne(load);
     log->debug("train (" + getName() + ") delete car load " + load);
     setDirtyAndFirePropertyChange(LOADS_CHANGED_PROPERTY, _loadList.size() + 1, _loadList.size());
     return true;
 }

 /**
  * Determine if train will service a specific load name.
  *
  * @param load the load name to check.
  * @return true if train will service this load.
  */
 /*public*/ bool Train::acceptsLoadName(QString load) {
     if (_loadOption==(ALL_LOADS)) {
         return true;
     }
     if (_loadOption==(INCLUDE_LOADS)) {
         return _loadList.contains(load);
     }
     // exclude!
     return !_loadList.contains(load);
 }

 /**
  * Determine if train will service a specific load and car type.
  *
  * @param load the load name to check.
  * @param type the type of car used to carry the load.
  * @return true if train will service this load.
  */
 /*public*/ bool Train::acceptsLoad(QString load, QString type) {
     if (_loadOption==(ALL_LOADS)) {
         return true;
     }
     if (_loadOption==(INCLUDE_LOADS)) {
         return _loadList.contains(load) || _loadList.contains(type + CarLoad::SPLIT_CHAR + load);
     }
     // exclude!
     return !_loadList.contains(load) && !_loadList.contains(type + CarLoad::SPLIT_CHAR + load);
 }

 /*public*/ QString Train::getOwnerOption() {
     return _ownerOption;
 }

 /**
  * Set how this train deals with car owner names
  *
  * @param option ALL_OWNERS INCLUDE_OWNERS EXCLUDE_OWNERS
  */
 /*public*/ void Train::setOwnerOption(QString option) {
     QString old = _ownerOption;
     _ownerOption = option;
     setDirtyAndFirePropertyChange(OWNERS_CHANGED_PROPERTY, old, option);
 }


 /*protected*/ void Train::setOwnerNames(QStringList owners) {
     if (owners.length() == 0) {
         return;
     }
     StringUtil::sort(owners);
     foreach (QString owner, owners) {
         if (owner!=("")) {
             _ownerList.append(owner);
         }
     }
 }

 /**
  * Provides a list of owner names that the train will either service or
  * exclude. See setOwnerOption
  *
  * @return Array of owner names as Strings
  */
 /*public*/ QStringList Train::getOwnerNames() {
     QVector<QString> owners = QVector<QString>(_ownerList.size());
     for (int i = 0; i < _ownerList.size(); i++) {
         owners.replace(i, _ownerList.at(i));
     }
     if (_ownerList.size() == 0) {
         return owners.toList();
     }
     StringUtil::sort(owners.toList());
     return owners.toList();
 }

 /**
  * Add a owner name that the train will either service or exclude. See
  * setOwnerOption
  *
  * @return true if owner name was added, false if owner name wasn't in the
  *         list.
  */
 /*public*/ bool Train::addOwnerName(QString owner) {
     if (_ownerList.contains(owner)) {
         return false;
     }
     _ownerList.append(owner);
     log->debug("train (" + getName() + ") add car owner " + owner);
     setDirtyAndFirePropertyChange(OWNERS_CHANGED_PROPERTY, _ownerList.size() - 1, _ownerList.size());
     return true;
 }

 /**
  * Delete a owner name that the train will either service or exclude. See
  * setOwnerOption
  *
  * @return true if owner name was removed, false if owner name wasn't in the
  *         list.
  */
 /*public*/ bool Train::deleteOwnerName(QString owner) {
     if (!_ownerList.contains(owner)) {
         return false;
     }
     _ownerList.removeOne(owner);
     log->debug("train (" + getName() + ") delete car owner " + owner);
     setDirtyAndFirePropertyChange(OWNERS_CHANGED_PROPERTY, _ownerList.size() + 1, _ownerList.size());
     return true;
 }

 /**
  * Determine if train will service a specific owner name.
  *
  * @param owner the owner name to check.
  * @return true if train will service this owner name.
  */
 /*public*/ bool Train::acceptsOwnerName(QString owner) {
     if (_ownerOption==(ALL_OWNERS)) {
         return true;
     }
     if (_ownerOption==(INCLUDE_OWNERS)) {
         return _ownerList.contains(owner);
     }
     // exclude!
     return !_ownerList.contains(owner);
 }

 /*public*/ void Train::replaceOwner(QString oldName, QString newName) {
     if (deleteOwnerName(oldName)) {
         addOwnerName(newName);
     }
 }

 /**
  * Only rolling stock built in or after this year will be used.
  *
  * @param year
  */
 /*public*/ void Train::setBuiltStartYear(QString year) {
     QString old = _builtStartYear;
     _builtStartYear = year;
     if (old!=year) {
         setDirtyAndFirePropertyChange(BUILT_YEAR_CHANGED_PROPERTY, old, year);
     }
 }

 /*public*/ QString Train::getBuiltStartYear() {
     return _builtStartYear;
 }

 /**
  * Only rolling stock built in or before this year will be used.
  *
  * @param year
  */
 /*public*/ void Train::setBuiltEndYear(QString year) {
     QString old = _builtEndYear;
     _builtEndYear = year;
     if (old!=year) {
         setDirtyAndFirePropertyChange(BUILT_YEAR_CHANGED_PROPERTY, old, year);
     }
 }

 /*public*/ QString Train::getBuiltEndYear() {
     return _builtEndYear;
 }

 /**
  * Determine if train will service rolling stock by built date.
  *
  * @param date
  * @return true is built date is in the acceptable range.
  */
 /*public*/ bool Train::acceptsBuiltDate(QString date) {
     if (getBuiltStartYear()==(NONE) && getBuiltEndYear()==(NONE)) {
         return true; // range dates not defined
     }
     int startYear = 0; // default start year;
     int endYear = 99999; // default end year;
     bool ok;
         startYear = getBuiltStartYear().toInt(&ok);
     if(!ok) {
         log->debug("Train (" + getName() + ") built start date not initialized, start: " + getBuiltStartYear());
     }
     //try {
         endYear = getBuiltEndYear().toInt(&ok);
     if(!ok) {
         log->debug("Train (" + getName() + ") built end date not initialized, end: " + getBuiltEndYear());
     }
     //try {
         int builtYear = date.toInt(&ok);
         if (startYear < builtYear && builtYear < endYear) {
             return true;
         } else {
             return false;
         }
     if(!ok) {
         // log->debug("Built date: "+date+" isn't an integer");
         // maybe the built date is in the format month-year
         QStringList built = date.split("-");
         if (built.length() > 1) {
             //try {
                 int builtYear = built[1].toInt(&ok);
                 if (builtYear < 100) {
                     builtYear = builtYear + 1900;
                 }
                 if (startYear < builtYear && builtYear < endYear) {
                     return true;
                 } else {
                     return false;
                 }
             if(!ok) {
                 log->debug("Unable to parse car built date " + date);
             }
         }
         return false;
     }
 }


 /**
  * Determines if this train will service this car-> Note this code doesn't
  * check the location or tracks that needs to be done separately. See
  * Router.java.
  *
  * @param car The car to be tested.
  * @return true if this train can service the car->
  */
 /*public*/ bool Train::services(Car* car) {
    return services(NULL, car);
 }

 /*protected*/ /*static*/ /*final*/ QString Train::SEVEN = "7"; //Setup::BUILD_REPORT_VERY_DETAILED;

 /*public*/ bool Train::services(PrintWriter* buildReport, Car* car) {
     bool addToReport = Setup::getRouterBuildReportLevel()==(SEVEN);
     setServiceStatus(NONE);
     // check to see if train can carry car
     if (!acceptsTypeName(car->getTypeName())) {
         if (addToReport) {
             TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't service car (%2) type (%3)").arg(getName()).arg(car->toString(),
                     car->getTypeName()));
         }
         return false;
     }
     if (!acceptsLoad(car->getLoadName(), car->getTypeName())) {
         if (addToReport) {
             TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't service car (%2) type (%3) with load (%4)").arg(getName()).arg(car->toString()).arg(
                     car->getTypeName()).arg(car->getLoadName()));
         }
         return false;
     }
     if (!acceptsBuiltDate(car->getBuilt()) || !acceptsOwnerName(car->getOwner())
             || !acceptsRoadName(car->getRoadName())) {
         if (addToReport) {
             TrainCommon::addLine(buildReport, SEVEN,
                     tr("Train (%1) can't service car (%2)").arg(getName()).arg(car->toString()));
         }
         return false;
     }

     int length = car->getTotalLength();
     // car can be a kernel so get total length
     if (car->getKernel() != NULL) {
         length = car->getKernel()->getTotalLength();
     }
     Route* route = getRoute();
     if (route != NULL) {
         // determine if the car's location and destination is serviced by this train
         if (route->getLastLocationByName(car->getLocationName()) == NULL) {
             if (addToReport) {
                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) doesn''t service location (%2)").arg(getName()).arg(car->getLocationName()));
             }
             return false;
         }
         if (car->getDestination() !=NULL&& route->getLastLocationByName(car->getDestinationName()) == NULL) {
             if (addToReport) {
                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) doesn''t service location (%2)").arg(getName()).arg(car->getDestinationName()));
             }
             return false;
         }
         QList<RouteLocation*>* rLocations = route->getLocationsBySequenceList();
         for (int j = 0; j < rLocations->size(); j++) {
             RouteLocation* rLoc = rLocations->at(j);
             if (rLoc->getName()==(car->getLocationName())
                     &&
                     rLoc->isPickUpAllowed()
                     &&
                     rLoc->getMaxCarMoves() > 0
                     &&
                     !skipsLocation(rLoc->getId())
                     &&
                     ((car->getLocation()->getTrainDirections() & rLoc->getTrainDirection()) > 0 || isLocalSwitcher())) {
                 if (car->getTrack() != NULL) {
                     if (((car->getTrack()->getTrainDirections() & rLoc->getTrainDirection()) == 0 && !isLocalSwitcher())
                             ||
                             !car->getTrack()->acceptsPickupTrain(this)) {
                         if (addToReport) {
                             TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't service car (%2) from (%3, %4) route id (%5)").arg(getName(),
                                     car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(rLoc->getId()));
                         }
                         continue;
                     }
                 }
                 if (debugFlag)
                 {
                     log->debug("Car (" + car->toString() + ") can be picked up by train (" + getName()
                             + ") location (" + car->getLocationName() + ", " + car->getTrackName()// NOI18N
                             +
                             ") destination ("// NOI18N
                             +
                             car->getDestinationName() +
                             ", "// NOI18N
                             +
                             car->getDestinationTrackName() +
                             ")"); // NOI18N
                 }
                 if (addToReport) {
                     TrainCommon::addLine(buildReport, SEVEN, tr("trainCanPickUpCar").arg(getName()).arg(car->toString()).arg(
                             car->getLocationName()).arg(car->getTrackName()).arg(rLoc->getId()));
                 }
                 if (car->getDestination() == NULL) {
                     if (debugFlag) {
                         log->debug("Car (" + car->toString() + ") does not have a destination");
                     }
                     return true;
                 }
                 // now check car's destination
                 for (int k = j; k < rLocations->size(); k++) {
                     RouteLocation* rldest = rLocations->at(k);
                     if (rldest->getName()==(car->getDestinationName())
                             &&
                             rldest->isDropAllowed()
                             &&
                             rldest->getMaxCarMoves() > 0
                             &&
                             !skipsLocation(rldest->getId())
                             &&
                             ((car->getDestination()->getTrainDirections() & rldest->getTrainDirection()) > 0 || isLocalSwitcher())
                             &&
                             (!Setup::isCheckCarDestinationEnabled() || car->getTrack() ==NULL|| car->getTrack()
                                     ->acceptsDestination(car->getDestination()))) {
                         // found a destination, now check destination track
                         if (car->getDestinationTrack() != NULL) {
                             if ((car->getDestinationTrack()->getTrainDirections() & rldest->getTrainDirection()) == 0
                                     && !isLocalSwitcher()) {
                                 if (addToReport) {
                                     TrainCommon::addLine(buildReport, SEVEN, tr("Can''t set out rolling stock (%1) using %2bound train,").arg(
                                             car->toString()).arg(rldest->getTrainDirectionString()));
                                     TrainCommon::addLine(buildReport, SEVEN, tr("destination track (%1) does not service this direction").arg(car
                                             ->getDestinationTrackName()));
                                 }
                                 continue;
                             }
                             if (!car->getDestinationTrack()->acceptsDropTrain(this)) {
                                 if (addToReport) {
                                     TrainCommon::addLine(buildReport, SEVEN, tr("buildCanNotDropCarTrain").arg(car->toString()).arg(
                                             getName()).arg(car->getDestinationTrack()->getTrackTypeName(),
                                             car->getDestinationTrackName()));
                                 }
                                 continue;
                             }
                         } else if (rldest->getLocation()->isStaging()
                                 && getStatusCode() == CODE_BUILDING && getTerminationTrack() != NULL
                                 && getTerminationTrack()->getLocation() == rldest->getLocation()) {
                             if (debugFlag) {
                                 log->debug("Car (" + car->toString() + ") destination is staging, check train ("
                                         + getName() + ") termination track (" + getTerminationTrack()->getName() // NOI18N
                                         +
                                         ")");
                             }
                             QString status = car->testDestination(getTerminationTrack()->getLocation(),
                                     getTerminationTrack());
                             if (status!=(Track::OKAY)) {
                                 if (addToReport) {
                                     TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't deliver car (%2) to staging (%3, %4) due to %5").arg(getName()).arg(
                                             car->toString()).arg(getTerminationTrack()->getLocation()->getName()).arg(
                                             getTerminationTrack()->getName()).arg(status));
                                 }
                                 continue;
                             }
                         } else {
                             if (debugFlag) {
                                 log->debug("Find track for car (" + car->toString() + ") at destination "
                                         + car->getDestinationName());
                             }
                             // determine if there's a track that is willing to accept this car
                             QString status = "";
                             QList<Track*> tracks = rldest->getLocation()->getTrackList();
                             foreach (Track* track, tracks) {
                                 if ((track->getTrainDirections() & rldest->getTrainDirection()) == 0
                                         && !isLocalSwitcher()) {
                                     if (addToReport) {
                                         TrainCommon::addLine(buildReport, SEVEN, tr("Can''t set out rolling stock (%1) using %2bound train,").arg(
                                                 car->toString()).arg(rldest->getTrainDirectionString()));
                                         TrainCommon::addLine(buildReport, SEVEN, tr("buildCanNotDropRsUsingTrain2").arg(track
                                                 ->getName()));
                                     }
                                     continue;
                                 }
                                 if (!track->acceptsDropTrain(this)) {
                                     if (addToReport) {
                                         TrainCommon::addLine(buildReport, SEVEN, tr("Can''t set out (%1) by train (%2) to %3 (%4)").arg(
                                                 car->toString(), getName(), track->getTrackTypeName(),
                                                 track->getName()));
                                     }
                                     continue;
                                 }
                                 // will the track accept this car?
                                 status = track->accepts(car);
                                 if (status==(Track::OKAY) || status.startsWith(Track::LENGTH)) {
                                     if (debugFlag) {
                                         log->debug("Found track (" + track->getName() + ") for car ("
                                                 + car->toString() + ")");
                                     }
                                     break; // yes, done
                                 }
                             }
                             if (status!=(Track::OKAY) && !status.startsWith(Track::LENGTH)) {
                                 if (debugFlag) {
                                     log->debug("Destination (" + car->getDestinationName() // NOI18N
                                             +
                                             ") can not service car (" +
                                             car->toString() // NOI18N
                                             +
                                             ") using train (" +
                                             getName() +
                                             ") no track available"); // NOI18N
                                 }
                                 if (addToReport) {
                                     TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't deliver car (%2) to (%3) route id (%4) no tracks able to service car").arg(getName(),
                                             car->toString(), car->getDestinationName(), rldest->getId()));
                                 }
                                 continue;
                             }
                         }
                         // carry cars only to terminal?
                         if (isSendCarsToTerminalEnabled()
                                 && TrainCommon::splitString(car->getLocationName())!=(
                                         TrainCommon::splitString(getTrainDepartsName()))
                                 && TrainCommon::splitString(car->getDestinationName())!=(
                                         TrainCommon::splitString(getTrainTerminatesName()))) {
                             if (debugFlag) {
                                 log->debug("option send cars to terminal is enabled");
                             }
                             if (addToReport) {
                                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't carry car (%2) from (%3, %4) to (%5, %6), option to send cars to terminal enabled ").arg(getName(),
                                         car->toString()).arg(car->getLocationName()).arg(car->getTrackName()).arg(
                                         car->getDestinationName()).arg(car->getDestinationTrackName()));
                             }

                             continue;

                         }
                         // allow car to return to staging?
                         if (isAllowReturnToStagingEnabled() && car->getTrack()->getTrackType()==(Track::STAGING)
                                 && rldest->getLocation() == car->getLocation()) {
                             if (addToReport) {
                                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can return car (%2) to staging (%3, %4)").arg(getName(),
                                         car->toString()).arg(car->getDestinationName()).arg(car->getDestinationTrackName()));
                             }
                             return true;
                         }
                         // is this a local move?
                         if (!isAllowLocalMovesEnabled()
                                 && !car->isCaboose()
                                 && !car->hasFred()
                                 && !car->isPassenger()
                                 && TrainCommon::splitString(car->getLocationName())==(
                                         TrainCommon::splitString(car->getDestinationName()))) {
                             if (debugFlag) {
                                 log->debug("Local moves is disabled");
                             }
                             if (addToReport) {
                                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't perform local move for car (%2) at location (%3)").arg(getName(),
                                         car->toString()).arg(car->getLocationName()));
                             }
                             continue;
                         }
                         // Can cars travel from origin to terminal?
                         if (!isAllowThroughCarsEnabled()
                                 && TrainCommon::splitString(getTrainDepartsName())==(
                                         TrainCommon::splitString(rLoc->getName()))
                                 && TrainCommon::splitString(getTrainTerminatesName())==(
                                         TrainCommon::splitString(rldest->getName())) && !isLocalSwitcher()
                                 && !car->isCaboose() && !car->hasFred() && !car->isPassenger()) {
                             if (debugFlag) {
                                 log->debug("Through car (" + car->toString() + ") not allowed");
                             }
                             if (addToReport) {
                                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) doesn''t carry cars from origin (%2) to terminal (%3)").arg(getName()).arg(
                                         car->getLocationName()).arg(car->getDestinationName()));
                             }
                             continue;
                         }
                         // check to see if moves are available
                         if (getStatusCode() == CODE_BUILDING && rldest->getMaxCarMoves() - rldest->getCarMoves() <= 0) {
                             setServiceStatus(tr("Train (%1) no moves left for route (%2) id (%3) destination (%4)").arg(
                                     getName()).arg(getRoute()->getName()).arg(rldest->getId()).arg(rldest->getName()));
                             if (debugFlag) {
                                 log->debug("No available moves for destination " + rldest->getName());
                             }
                             if (addToReport) {
                                 TrainCommon::addLine(buildReport, SEVEN, getServiceStatus());
                             }
                             continue;
                         }
                         if (debugFlag) {
                             log->debug("Car (" + car->toString() + ") can be dropped by train (" + getName()
                                     + ") to (" + car->getDestinationName() + ", " // NOI18N
                                     +
                                     car->getDestinationTrackName() +
                                     ")");
                         }
                         return true;
                     }
                     // check to see if train length is okay
                     if (getStatusCode() == CODE_BUILDING
                             && rLoc->getTrainLength() + length > rLoc->getMaxTrainLength())
                     {
                         setServiceStatus(tr("Train (%1) would exceed route (%2) id (%3) maximum train length (%4) %5 when departing (%6) with car (%7)").arg(
                                 getName()).arg(getRoute()->getName()).arg(rLoc->getId()).arg(
                                         rLoc->getMaxTrainLength()).arg(Setup::getLengthUnit().toLower()).arg(
                                         rLoc->getName()).arg(car->toString()));
                         if (debugFlag) {
                             log->debug("Car (" + car->toString() + ") exceeds maximum train length "
                                     + rldest->getMaxTrainLength() + " when departing (" // NOI18N
                                     +
                                     rldest->getName() +
                                     ")");
                         }
                         if (addToReport) {
                             TrainCommon::addLine(buildReport, SEVEN, getServiceStatus());
                         }
                         return false;
                     }
                 }
                 if (addToReport) {
                     TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't deliver car (%2) to (%3, %4)").arg(getName()).arg(
                             car->toString()).arg(car->getDestinationName()).arg(car->getDestinationTrackName()));
                 }
             } else if (addToReport && rLoc->getName()==(car->getLocationName())) {
                 TrainCommon::addLine(buildReport, SEVEN, tr("Train (%1) can't service car (%2) from (%3, %4) route id (%5)").arg(getName()).arg(car->toString()).arg(
                         car->getLocationName()).arg(car->getTrackName()).arg(rLoc->getId()));
             }
         }
     }
     if (debugFlag) {
         log->debug(tr("Train (%1) can't service car (%2) from (%3, %4)").arg(getName()).arg(car->toString()).arg(car
                 ->getLocationName()).arg(car->getTrackName()));
     }
     return false;
 }

 /*protected*/ void Train::setServiceStatus(QString status) {
     _serviceStatus = status;
 }

 /**
  * Returns the statusCode of the "services(Car)" routine. There are two
  * statusCodes that need special consideration when the train is being
  * built, the moves in a train's route and the maximum train length. NOTE:
  * The code using getServiceStatus() currently assumes that if there's a
  * service status that the issue is either route moves or maximum train
  * length.
  */
 /*public*/ QString Train::getServiceStatus() {
     return _serviceStatus;
 }

 /**
  *
  * @return The number of cars worked by this train
  */
 /*public*/ int Train::getNumberCarsWorked() {
     int count = 0;
     foreach (RollingStock* rs, *CarManager::instance()->getList(this)) {
         if (rs->getRouteLocation() != NULL) {
             count++;
         }
     }
     return count;
 }

 /*public*/ void Train::setNumberCarsRequested(int number) {
     _statusCarsRequested = number;
 }

 /*public*/ int Train::getNumberCarsRequested() {
     return _statusCarsRequested;
 }

 /*public*/ void Train::setTerminationDate(QString date) {
     _statusTerminatedDate = date;
 }

 /*public*/ QString Train::getTerminationDate() {
     return _statusTerminatedDate;
 }

 /**
  * Gets the number of cars in the train at the current location in the
  * train's route.
  *
  * @return The number of cars currently in the train
  */
 /*public*/ int Train::getNumberCarsInTrain() {
     return getNumberCarsInTrain(getCurrentLocation());
 }

 /**
  * Gets the number of cars in the train when train departs the route
  * location.
  *
  * @return The number of cars in the train departing the route location.
  */
 /*public*/ int Train::getNumberCarsInTrain(RouteLocation* routeLocation) {
     int number = 0;
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             foreach (RollingStock* rs,* CarManager::instance()->getList(this)) {
                 Car* car = (Car*) rs;
                 if (car->getRouteLocation() == rl) {
                     number++;
                 }
                 if (car->getRouteDestination() == rl) {
                     number--;
                 }
             }
             if (rl == routeLocation) {
                 break;
             }
         }
     }
     return number;
 }

 /**
  * Gets the number of empty cars in the train when train departs the route
  * location.
  *
  * @return The number of empty cars in the train departing the route
  *         location.
  */
 /*public*/ int Train::getNumberEmptyCarsInTrain(RouteLocation* routeLocation) {
     int number = 0;
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             foreach (RollingStock* rs, *CarManager::instance()->getList(this)) {
                 Car* car = (Car*) rs;
                 if (car->getLoadType()!=(CarLoad::LOAD_TYPE_EMPTY)) {
                     continue;
                 }
                 if (car->getRouteLocation() == rl) {
                     number++;
                 }
                 if (car->getRouteDestination() == rl) {
                     number--;
                 }
             }
             if (rl == routeLocation) {
                 break;
             }
         }
     }

     return number;
 }

 /**
  * Gets the train's length at the current location in the train's route.
  *
  * @return The train length at the train's current location
  */
 /*public*/ int Train::getTrainLength() {
     return getTrainLength(getCurrentLocation());
 }

 /**
  * Gets the train's length at the route location specified
  *
  * @param routeLocation The route location
  * @return The train length at the route location
  */
 /*public*/ int Train::getTrainLength(RouteLocation* routeLocation) {
     int length = 0;
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             foreach (RollingStock* rs, *EngineManager::instance()->getList(this)) {
                 Engine* eng = (Engine*) rs;
                 if (eng->getRouteLocation() == rl) {
                     length += eng->getTotalLength();
                 }
                 if (eng->getRouteDestination() == rl) {
                     length += -eng->getTotalLength();
                 }
             }
             foreach (RollingStock* rs, *CarManager::instance()->getList(this)) {
                 Car* car = (Car*) rs;
                 if (car->getRouteLocation() == rl) {
                     length += car->getTotalLength();
                 }
                 if (car->getRouteDestination() == rl) {
                     length += -car->getTotalLength();
                 }
             }
             if (rl == routeLocation) {
                 break;
             }
         }
     }
     return length;
 }

 /**
  * Get the train's weight at the current location.
  *
  * @return Train's weight in tons.
  */
 /*public*/ int Train::getTrainWeight() {
     return getTrainWeight(getCurrentLocation());
 }

 /*public*/ int Train::getTrainWeight(RouteLocation* routeLocation) {
     int weight = 0;
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             foreach (RollingStock* rs, *EngineManager::instance()->getList(this)) {
                 Engine* eng = (Engine*) rs;
                 if (eng->getRouteLocation() == rl) {
                     weight += eng->getAdjustedWeightTons();
                 }
                 if (eng->getRouteDestination() == rl) {
                     weight += -eng->getAdjustedWeightTons();
                 }
             }
             foreach (RollingStock* rs, *CarManager::instance()->getList(this)) {
                 Car* car = (Car*) rs;
                 if (car->getRouteLocation() == rl) {
                     weight += car->getAdjustedWeightTons();
                 }
                 if (car->getRouteDestination() == rl) {
                     weight += -car->getAdjustedWeightTons();
                 }
             }
             if (rl == routeLocation) {
                 break;
             }
         }
     }
     return weight;
 }

 /**
  * Gets the train's locomotive horsepower at the route location specified
  *
  * @param routeLocation The route location
  * @return The train's locomotive horsepower at the route location
  */
 /*public*/ int Train::getTrainHorsePower(RouteLocation* routeLocation) {
     int hp = 0;
     Route* route = getRoute();
     if (route != NULL) {
         foreach (RouteLocation* rl, *route->getLocationsBySequenceList()) {
             foreach (RollingStock* rs, *EngineManager::instance()->getList(this)) {
                 Engine* eng = (Engine*) rs;
                 if (eng->getRouteLocation() == rl) {
                     hp += eng->getHpInteger();
                 }
                 if (eng->getRouteDestination() == rl) {
                     hp += -eng->getHpInteger();
                 }
             }
             if (rl == routeLocation) {
                 break;
             }
         }
     }
     return hp;
 }

 /**
  * Gets the current caboose road and number if there's one assigned to the
  * train.
  *
  * @return Road and number of caboose.
  */
 /*public*/ QString Train::getCabooseRoadAndNumber() {
     QString cabooseRoadNumber = NONE;
     RouteLocation* rl = getCurrentLocation();
     QList<RollingStock*>* cars = CarManager::instance()->getByTrainList(this);
     foreach (RollingStock* rs, *cars) {
         Car* car = (Car*) rs;
         if (car->getRouteLocation() == rl && car->getRouteDestination() != rl && car->isCaboose()) {
             cabooseRoadNumber = car->toString();
         }
     }
     return cabooseRoadNumber;
 }

 /*public*/ void Train::setDescription(QString description) {
     QString old = _description;
     _description = description;
     if (old!=description) {
         setDirtyAndFirePropertyChange(DESCRIPTION_CHANGED_PROPERTY, old, description);
     }
 }

 /*public*/ QString Train::getRawDescription() {
     return _description;
 }

 /**
  * Returns a formated string providing the train's description. %1 = lead
  * engine number, %2 = train's departure direction %3 = lead engine road.
  */
 /*public*/ QString Train::getDescription()
 {
//  QString description = _description.arg(getLeadEngineNumber(), getTrainDepartsDirection(),
//              getLeadEngineRoadName()});
  QString description = tr("%1-%2-%3").arg(getLeadEngineNumber()).arg(getTrainDepartsDirection()).arg(getLeadEngineRoadName());
  return description;
 }

 /*public*/ void Train ::setNumberEngines(QString number) {
     QString old = _numberEngines;
     _numberEngines = number;
     if (old!=number) {
         setDirtyAndFirePropertyChange("trainNmberEngines", old, number); // NOI18N
     }
 }

 /**
  * Get the number of engines that this train requires.
  *
  * @return The number of engines that this train requires.
  */
 /*public*/ QString Train ::getNumberEngines() {
     return _numberEngines;
 }

 /**
  * Get the number of engines needed for the second set.
  *
  * @return The number of engines needed in route
  */
 /*public*/ QString Train ::getSecondLegNumberEngines() {
     return _leg2Engines;
 }

 /*public*/ void Train ::setSecondLegNumberEngines(QString number) {
     QString old = _leg2Engines;
     _leg2Engines = number;
     if (old!=number) {
         setDirtyAndFirePropertyChange("trainNmberEngines", old, number); // NOI18N
     }
 }

 /**
  * Get the number of engines needed for the third set.
  *
  * @return The number of engines needed in route
  */
 /*public*/ QString Train ::getThirdLegNumberEngines() {
     return _leg3Engines;
 }

 /*public*/ void Train ::setThirdLegNumberEngines(QString number) {
     QString old = _leg3Engines;
     _leg3Engines = number;
     if (old!=number) {
         setDirtyAndFirePropertyChange("trainNmberEngines", old, number); // NOI18N
     }
 }

 /**
  * Set the road name of engines servicing this train.
  *
  * @param road The road name of engines servicing this train.
  */
 /*public*/ void Train ::setEngineRoad(QString road) {
     QString old = _engineRoad;
     _engineRoad = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainEngineRoad", old, road); // NOI18N
     }
 }

 /**
  * Get the road name of engines servicing this train.
  *
  * @return The road name of engines servicing this train.
  */
 /*public*/ QString Train ::getEngineRoad() {
     return _engineRoad;
 }

 /**
  * Set the road name of engines servicing this train 2nd leg.
  *
  * @param road The road name of engines servicing this train.
  */
 /*public*/ void Train ::setSecondLegEngineRoad(QString road) {
     QString old = _leg2Road;
     _leg2Road = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainEngineRoad", old, road); // NOI18N
     }
 }

 /**
  * Get the road name of engines servicing this train 2nd leg.
  *
  * @return The road name of engines servicing this train.
  */
 /*public*/ QString Train ::getSecondLegEngineRoad() {
     return _leg2Road;
 }

 /**
  * Set the road name of engines servicing this train 3rd leg.
  *
  * @param road The road name of engines servicing this train.
  */
 /*public*/ void Train ::setThirdLegEngineRoad(QString road) {
     QString old = _leg3Road;
     _leg3Road = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainEngineRoad", old, road); // NOI18N
     }
 }

 /**
  * Get the road name of engines servicing this train 3rd leg.
  *
  * @return The road name of engines servicing this train.
  */
 /*public*/ QString Train ::getThirdLegEngineRoad() {
     return _leg3Road;
 }

 /**
  * Set the model name of engines servicing this train.
  *
  * @param model The model name of engines servicing this train.
  */
 /*public*/ void Train ::setEngineModel(QString model) {
     QString old = _engineModel;
     _engineModel = model;
     if (old!=model) {
         setDirtyAndFirePropertyChange("trainEngineModel", old, model); // NOI18N
     }
 }

 /*public*/ QString Train ::getEngineModel() {
     return _engineModel;
 }

 /**
  * Set the model name of engines servicing this train's 2nd leg.
  *
  * @param model The model name of engines servicing this train.
  */
 /*public*/ void Train ::setSecondLegEngineModel(QString model) {
     QString old = _leg2Model;
     _leg2Model = model;
     if (old!=model) {
         setDirtyAndFirePropertyChange("trainEngineModel", old, model); // NOI18N
     }
 }

 /*public*/ QString Train ::getSecondLegEngineModel() {
     return _leg2Model;
 }

 /**
  * Set the model name of engines servicing this train's 3rd leg.
  *
  * @param model The model name of engines servicing this train.
  */
 /*public*/ void Train ::setThirdLegEngineModel(QString model) {
     QString old = _leg3Model;
     _leg3Model = model;
     if (old!=model) {
         setDirtyAndFirePropertyChange("trainEngineModel", old, model); // NOI18N
     }
 }

 /*public*/ QString Train ::getThirdLegEngineModel() {
     return _leg3Model;
 }

 /*private*/ void Train ::replaceModel(QString oldModel, QString newModel) {
     if (getEngineModel()==(oldModel)) {
         setEngineModel(newModel);
     }
     if (getSecondLegEngineModel()==(oldModel)) {
         setSecondLegEngineModel(newModel);
     }
     if (getThirdLegEngineModel()==(oldModel)) {
         setThirdLegEngineModel(newModel);
     }
 }

 /**
  * Set the road name of the caboose servicing this train.
  *
  * @param road The road name of the caboose servicing this train.
  */
 /*public*/ void Train ::setCabooseRoad(QString road) {
     QString old = _cabooseRoad;
     _cabooseRoad = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainCabooseRoad", old, road); // NOI18N
     }
 }

 /*public*/ QString Train ::getCabooseRoad() {
     return _cabooseRoad;
 }

 /**
  * Set the road name of the second leg caboose servicing this train.
  *
  * @param road The road name of the caboose servicing this train's 2nd leg.
  */
 /*public*/ void Train ::setSecondLegCabooseRoad(QString road) {
     QString old = _leg2CabooseRoad;
     _leg2CabooseRoad = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainCabooseRoad", old, road); // NOI18N
     }
 }

 /*public*/ QString Train ::getSecondLegCabooseRoad() {
     return _leg2CabooseRoad;
 }

 /**
  * Set the road name of the third leg caboose servicing this train.
  *
  * @param road The road name of the caboose servicing this train's 3rd leg.
  */
 /*public*/ void Train ::setThirdLegCabooseRoad(QString road) {
     QString old = _leg3CabooseRoad;
     _leg3CabooseRoad = road;
     if (old!=road) {
         setDirtyAndFirePropertyChange("trainCabooseRoad", old, road); // NOI18N
     }
 }

 /*public*/ QString Train::getThirdLegCabooseRoad() {
     return _leg3CabooseRoad;
 }

 /*public*/ void Train ::setSecondLegStartLocation(RouteLocation* rl) {
     _leg2Start = rl;
 }

 /*public*/ RouteLocation* Train::getSecondLegStartLocation() {
     return _leg2Start;
 }

 /*public*/ QString Train::getSecondLegStartLocationName() {
     if (getSecondLegStartLocation() == NULL) {
         return NONE;
     }
     return getSecondLegStartLocation()->getName();
 }

 /*public*/ void Train ::setThirdLegStartLocation(RouteLocation* rl) {
     _leg3Start = rl;
 }

 /*public*/ RouteLocation* Train::getThirdLegStartLocation() {
     return _leg3Start;
 }

 /*public*/ QString Train ::getThirdLegStartLocationName() {
     if (getThirdLegStartLocation() == NULL) {
         return NONE;
     }
     return getThirdLegStartLocation()->getName();
 }

 /*public*/ void Train ::setSecondLegEndLocation(RouteLocation* rl) {
     _end2Leg = rl;
 }

 /*public*/ QString Train ::getSecondLegEndLocationName() {
     if (getSecondLegEndLocation() == NULL) {
         return NONE;
     }
     return getSecondLegEndLocation()->getName();
 }

 /*public*/ RouteLocation* Train ::getSecondLegEndLocation() {
     return _end2Leg;
 }

 /*public*/ void Train ::setThirdLegEndLocation(RouteLocation* rl) {
     _leg3End = rl;
 }

 /*public*/ RouteLocation* Train ::getThirdLegEndLocation() {
     return _leg3End;
 }

 /*public*/ QString Train ::getThirdLegEndLocationName() {
     if (getThirdLegEndLocation() == NULL) {
         return NONE;
     }
     return getThirdLegEndLocation()->getName();
 }

 /**
  * Optional changes to train while in route.
  *
  * @param options NONE, CHANGE_ENGINES, ADD_CABOOSE, HELPER_ENGINES,
  *            REMOVE_CABOOSE
  */
 /*public*/ void Train ::setSecondLegOptions(int options) {
     int old = _leg2Options;
     _leg2Options = options;
     if (old != options) {
         setDirtyAndFirePropertyChange("trainLegOptions", old, options); // NOI18N
     }
 }

 /*public*/ int Train ::getSecondLegOptions() {
     return _leg2Options;
 }

 /**
  * Optional changes to train while in route.
  *
  * @param options NONE, CHANGE_ENGINES, ADD_CABOOSE, HELPER_ENGINES,
  *            REMOVE_CABOOSE
  */
 /*public*/ void Train ::setThirdLegOptions(int options) {
     int old = _leg3Options;
     _leg3Options = options;
     if (old != options) {
         setDirtyAndFirePropertyChange("trainLegOptions", old, options); // NOI18N
     }
 }

 /*public*/ int Train ::getThirdLegOptions() {
     return _leg3Options;
 }

 /*public*/ void Train ::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=comment) {
         setDirtyAndFirePropertyChange("trainComment", old, comment); // NOI18N
     }
 }

/*public*/ QString Train ::getComment(bool asText)
{
 if(asText)
 {
  QTextEdit* edit = new QTextEdit(_comment);
  return edit->toPlainText();
 }
 return _comment;
}
// /*public*/ QString Train ::getComment() {
//     return _comment;
// }

 /**
  * Add a script to run before a train is built
  *
  * @param pathname The script's pathname
  */
 /*public*/ void Train::addBuildScript(QString pathname) {
     _buildScripts.append(pathname);
     setDirtyAndFirePropertyChange("addBuildScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void Train::deleteBuildScript(QString pathname) {
     _buildScripts.removeOne(pathname);
     setDirtyAndFirePropertyChange("deleteBuildScript", QVariant(), pathname); // NOI18N
 }

 /**
  * Gets a list of pathnames (scripts) to run before this train is built
  *
  * @return A list of pathnames to run before this train is built
  */
 /*public*/ QStringList Train::getBuildScripts() {
     return _buildScripts;
 }

 /**
  * Add a script to run after a train is built
  *
  * @param pathname The script's pathname
  */
 /*public*/ void Train::addAfterBuildScript(QString pathname) {
     _afterBuildScripts.append(pathname);
     setDirtyAndFirePropertyChange("addAfterBuildScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void Train::deleteAfterBuildScript(QString pathname) {
     _afterBuildScripts.removeOne(pathname);
     setDirtyAndFirePropertyChange("deleteAfterBuildScript", QVariant(), pathname); // NOI18N
 }

 /**
  * Gets a list of pathnames (scripts) to run after this train is built
  *
  * @return A list of pathnames to run after this train is built
  */
 /*public*/ QStringList Train::getAfterBuildScripts() {
     return _afterBuildScripts;
 }

 /**
  * Add a script to run when train is moved
  *
  * @param pathname The script's pathname
  */
 /*public*/ void Train::addMoveScript(QString pathname) {
     _moveScripts.append(pathname);
     setDirtyAndFirePropertyChange("addMoveScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void Train::deleteMoveScript(QString pathname) {
     _moveScripts.removeOne(pathname);
     setDirtyAndFirePropertyChange("deleteMoveScript", QVariant(), pathname); // NOI18N
 }

 /**
  * Gets a list of pathnames (scripts) to run when this train moved
  *
  * @return A list of pathnames to run when this train moved
  */
 /*public*/ QStringList Train::getMoveScripts() {
     return _moveScripts;
 }

 /**
  * Add a script to run when train is terminated
  *
  * @param pathname The script's pathname
  */
 /*public*/ void Train::addTerminationScript(QString pathname) {
     _terminationScripts.append(pathname);
     setDirtyAndFirePropertyChange("addTerminationScript", pathname, QVariant()); // NOI18N
 }

 /*public*/ void Train::deleteTerminationScript(QString pathname) {
     _terminationScripts.removeOne(pathname);
     setDirtyAndFirePropertyChange("deleteTerminationScript", QVariant(), pathname); // NOI18N
 }

 /**
  * Gets a list of pathnames (scripts) to run when this train terminates
  *
  * @return A list of pathnames to run when this train terminates
  */
 /*public*/ QStringList Train::getTerminationScripts() {
     return _terminationScripts;
 }

 /**
  * Gets the optional railroad name for this train.
  *
  * @return Train's railroad name.
  */
 /*public*/ QString Train::getRailroadName() {
     return _railroadName;
 }

 /**
  * Overrides the default railroad name for this train.
  *
  * @param name The railroad name for this train.
  */
 /*public*/ void Train::setRailroadName(QString name) {
     QString old = _railroadName;
     _railroadName = name;
     if (old!=name) {
         setDirtyAndFirePropertyChange("trainRailroadName", old, name); // NOI18N
     }
 }

 /*public*/ QString Train::getManifestLogoURL() {
     return _logoURL;
 }

 /**
  * Overrides the default logo for this train.
  *
  * @param pathName file location for the logo.
  */
 /*public*/ void Train::setManifestLogoURL(QString pathName) {
     _logoURL = pathName;
 }

 /*public*/ bool Train::isShowArrivalAndDepartureTimesEnabled() {
     return _showTimes;
 }

 /*public*/ void Train::setShowArrivalAndDepartureTimes(bool enable) {
     bool old = _showTimes;
     _showTimes = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("showArrivalAndDepartureTimes", old ? "true" : "false", // NOI18N
                 enable ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isSendCarsToTerminalEnabled() {
     return _sendToTerminal;
 }

 /*public*/ void Train::setSendCarsToTerminalEnabled(bool enable) {
     bool old = _sendToTerminal;
     _sendToTerminal = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("send cars to terminal", old ? "true" : "false", enable ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isAllowLocalMovesEnabled() {
     return _allowLocalMoves;
 }

 /*public*/ void Train::setAllowLocalMovesEnabled(bool enable) {
     bool old = _allowLocalMoves;
     _allowLocalMoves = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("allow local moves", old ? "true" : "false", enable ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isAllowThroughCarsEnabled() {
     return _allowThroughCars;
 }

 /*public*/ void Train::setAllowThroughCarsEnabled(bool enable) {
     bool old = _allowThroughCars;
     _allowThroughCars = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("allow through cars", old ? "true" : "false", enable ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isBuildTrainNormalEnabled() {
     return _buildNormal;
 }

 /*public*/ void Train::setBuildTrainNormalEnabled(bool enable) {
     bool old = _buildNormal;
     _buildNormal = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("build train normal", old ? "true" : "false", enable ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /**
  * When true allow a turn to return cars to staging. A turn is a train that
  * departs and terminates at the same location.
  *
  * @return true if cars can return to staging
  */
 /*public*/ bool Train::isAllowReturnToStagingEnabled() {
     return _allowCarsReturnStaging;
 }

 /*public*/ void Train::setAllowReturnToStagingEnabled(bool enable) {
     bool old = _allowCarsReturnStaging;
     _allowCarsReturnStaging = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("allow cars to return to staging", old ? "true" : "false", // NOI18N
                 enable ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isServiceAllCarsWithFinalDestinationsEnabled() {
     return _serviceAllCarsWithFinalDestinations;
 }

 /*public*/ void Train::setServiceAllCarsWithFinalDestinationsEnabled(bool enable) {
     bool old = _serviceAllCarsWithFinalDestinations;
     _serviceAllCarsWithFinalDestinations = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("TrainServiceAllCarsWithFinalDestinations", old ? "true" : "false", // NOI18N
                 enable ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isBuildConsistEnabled() {
     return _buildConsist;
 }

 /*public*/ void Train::setBuildConsistEnabled(bool enable) {
     bool old = _buildConsist;
     _buildConsist = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("TrainBuildConsist", old ? "true" : "false", // NOI18N
                 enable ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isSendCarsWithCustomLoadsToStagingEnabled() {
     return _sendCarsWithCustomLoadsToStaging;
 }

 /*public*/ void Train::setSendCarsWithCustomLoadsToStagingEnabled(bool enable) {
     bool old = _sendCarsWithCustomLoadsToStaging;
     _sendCarsWithCustomLoadsToStaging = enable;
     if (old != enable) {
         setDirtyAndFirePropertyChange("SendCarsWithCustomLoadsToStaging", old ? "true" : "false", // NOI18N
                 enable ? "true" : "false"); // NOI18N
     }
 }

 /*protected*/ void Train::setBuilt(bool built) {
     bool old = _built;
     _built = built;
     if (old != built) {
         setDirtyAndFirePropertyChange(BUILT_CHANGED_PROPERTY, old ? "true" : "false", built ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /**
  * Used to determine if this train has been built.
  *
  * @return true if the train was successfully built.
  */
 /*public*/ bool Train::isBuilt() {
     return _built;
 }

 /*public*/ void Train::setModified(bool modified) {
     bool old = _modified;
     _modified = modified;
     if (modified) {
         setPrinted(false);
     }
     if (old != modified) {
         setDirtyAndFirePropertyChange("TrainModified", old ? "true" : "false", modified ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /*public*/ bool Train::isModified() {
     return _modified;
 }
#if 0
 /**
  * Deprecated, kept for user scripts. Use isBuilt()
  *
  * @return true if the train was successfully built.
  *
  */
 @Deprecated
 /*public*/ bool getBuilt() {
     return isBuilt();
 }
#endif
 /**
  * Control flag used to decide if this train is to be built.
  *
  * @param build When true, build this train.
  */
 /*public*/ void Train::setBuildEnabled(bool build)
 {
  bool old = _build;
  _build = build;
  if (old != build)
  {
   setDirtyAndFirePropertyChange(BUILD_CHANGED_PROPERTY, old ? "true" : "false", build ? "true" // NOI18N
   : "false"); // NOI18N
  }
 }

 /**
  * Used to determine if train is to be built.
  *
  * @return true if train is to be built.
  */
 /*public*/ bool Train::isBuildEnabled() {
     return _build;
 }
#if 0
 /**
  * Deprecated, use setBuildEnabled(build).
  *
  * @param build When true, build this train.
  */
 @Deprecated
 /*public*/ void setBuild(bool build) {
     setBuildEnabled(build);
 }

 /**
  * Deprecated, use isBuildEnabled()
  *
  * @return true if train is to be built.
  */
 @Deprecated
 /*public*/ bool getBuild() {
     return isBuildEnabled();
 }
#endif
 /**
  * Build this train if the build control flag is true.
  *
  * @return True only if train is successfully built.
  */
 /*public*/ bool Train::buildIfSelected()
 {
  if (isBuildEnabled() && !isBuilt()) {
      build();
      return true;
  }
  log->debug("Train (" + getName() + ") not selected or already built, skipping build");
  return false;
 }
 void Train::on_error(QString title, QString msg)
 {
  emit error(title,msg);
  log->error(title, QVariant(msg));
 }

 /**
  * Build this train. Creates a train manifest.
  */
 /*public*/ void Train::build()
 {
  reset();
  // run before build scripts
  runScripts(getBuildScripts());
  TrainBuilder* tb = new TrainBuilder();
  connect(tb, SIGNAL(error(QString,QString)), this, SLOT(on_error(QString, QString)));
  tb->build(this);
  setPrinted(false);
  setSwitchListStatus(UNKNOWN);
  // run after build scripts
  runScripts(getAfterBuildScripts());
 }

 /**
  * Run train scripts, waits for completion before returning.
  */
 /*private*/ /*synchronized*/ void Train::runScripts(QStringList /*scripts*/)
{
#if 0 // TODO:
  if (scripts.size() > 0)
  {
      // save the current status
      int savedStatus = getStatusCode();
      setStatus(CODE_RUN_SCRIPTS);
      JmriScriptEngineManager->getDefault().initializeAllEngines(); // create the python interpreter thread
      // find the number of active threads
      ThreadGroup root = Thread.currentThread()->getThreadGroup();
      int numberOfThreads = root.activeCount();
      //	log->debug("Number of active threads: {}", numberOfThreads);
      for (QString scriptPathname : scripts) {
          try {
              JmriScriptEngineManager->getDefault().runScript(new File(jmri.util.FileUtil->getExternalFilename(scriptPathname)));
          } catch (Exception e) {
              log->error("Problem with script: {}", scriptPathname);
          }
      }
      // need to wait for scripts to complete or 2 seconds maximum
      int count = 0;
      while (root.activeCount() > numberOfThreads) {
          /*synchronized*/ (this) {
              log->debug("Number of active threads: {}, at start: {}", root.activeCount(), numberOfThreads);
              try {
                  wait(20);
              } catch (InterruptedException e) {
                  Thread.currentThread().interrupt(); // retain if needed later
              }
              if (count++ > 100) {
                  break; // 2 seconds maximum 20*100 = 2000
              }
          }
      }
      setStatus(savedStatus);
  }
#endif
 }

 /*public*/ void Train::printBuildReport() {
     bool isPreview = (TrainManager::instance()->isPrintPreviewEnabled() || Setup
             ::isBuildReportAlwaysPreviewEnabled());
     printBuildReport(isPreview);
 }

 /*public*/ bool Train::printBuildReport(bool isPreview) {
     File* buildFile = TrainManagerXml::instance()->getTrainBuildReportFile(getName());
     if (!buildFile->exists()) {
         log->warn("Build file missing for train " + getName());
         return false;
     }

     if (isPreview && Setup::isBuildReportEditorEnabled()) {
         TrainPrintUtilities::editReport(buildFile, getName());
     } else {
         TrainPrintUtilities::printReport(buildFile, tr("Train Build Report %1").arg(
                 getDescription()), isPreview, NONE, true, NONE, NONE, Setup::PORTRAIT, Setup
                 ::getBuildReportFontSize());
     }
     return true;
 }

 /*protected*/ void Train::setBuildFailed(bool status) {
     bool old = _buildFailed;
     _buildFailed = status;
     if (old != status) {
         setDirtyAndFirePropertyChange("buildFailed", old ? "true" : "false", status ? "true" : "false"); // NOI18N
     }
 }

 /**
  * Returns true if the train build failed. Note that returning false doesn't
  * mean the build was successful.
  *
  * @return true if train build failed.
  */
 /*public*/ bool Train::getBuildFailed() {
     return _buildFailed;
 }

 /*protected*/ void Train::setBuildFailedMessage(QString message) {
     QString old = _buildFailedMessage;
     _buildFailedMessage = message;
     if (old!=message) {
         setDirtyAndFirePropertyChange("buildFailedMessage", old, message); // NOI18N
     }
 }

 /*protected*/ QString Train::getBuildFailedMessage() {
     return _buildFailedMessage;
 }

 /**
  * Print manifest for train if already built.
  *
  * @return true if print successful.
  */
 /*public*/ bool Train::printManifestIfBuilt()
 {
  if (isBuilt())
  {
   bool isPreview = TrainManager::instance()->isPrintPreviewEnabled();
   printManifest(isPreview);
  }
  else
  {
   log->debug("Need to build train (" + getName() + ") before printing manifest");
   return false;
  }
  return true;
 }

 /**
  * Print manifest for train.
  *
  * @return true if print successful.
  */
 /*public*/ bool Train::printManifest(bool isPreview)
 {
  if (isModified())
  {
   new TrainManifest(this);

   try {
       (new JsonManifest(this))->build();
   } catch (IOException ex) {
       log->error(tr("Unable to create JSON manifest %1").arg(ex.getLocalizedMessage()));
   }
   if (Setup::isGenerateCsvManifestEnabled()) {
       new TrainCsvManifest(this);
   }

  }
  File* file = TrainManagerXml::instance()->getTrainManifestFile(getName());
  if (!file->exists())
  {
   log->warn(tr("Manifest file missing for train %1").arg(getName()));
   return false;
  }
  if (isPreview && Setup::isManifestEditorEnabled())
  {
#if 0
      TrainPrintUtilities::openDesktopEditor(file);
#endif
      return true;
  }
  QString logoURL = NONE;
  if (getManifestLogoURL()!=(NONE))
  {
      logoURL = FileUtil::getExternalFilename(getManifestLogoURL());
  } else if (Setup::getManifestLogoURL()!=(Setup::NONE)) {
      logoURL = FileUtil::getExternalFilename(Setup::getManifestLogoURL());
  }
  Location* departs = LocationManager::instance()->getLocationByName(getTrainDepartsName());
  QString printerName = Location::NONE;
  if (departs != NULL)
  {
   printerName = departs->getDefaultPrinterName();
  }
  TrainPrintUtilities::printReport(file, getDescription(), isPreview, Setup::getFontName(), false, logoURL,
          printerName, Setup::getManifestOrientation(), Setup::getManifestFontSize());
  if (!isPreview) {
      setPrinted(true);
  }

  return true;
 }

 /*public*/ bool Train::openFile() {
     File* file = createCSVManifestFile();
     if (file ==NULL|| !file->exists()) {
         log->warn(tr("CSV manifest file missing for train %1").arg(getName()));
         return false;
     }
#if 0 // TODO:
     TrainUtilities::openDesktop(file);
#endif
     return true;
 }

/*public*/ bool Train::runFile()
 {
  File* file = createCSVManifestFile();
  if (file ==NULL|| !file->exists()) {
      log->warn(tr("CSV manifest file missing for train %1").arg(getName()));
      return false;
  }
  // Set up to process the CSV file by the external Manifest program
  TrainCustomManifest::instance()->addCVSFile(file);
  if (!TrainCustomManifest::instance()->process())
  {
   if (!TrainCustomManifest::instance()->excelFileExists())
   {
       JOptionPane::showMessageDialog(NULL, tr(" Excel File that you want to run. Directory name: %1, File name: %2").arg(TrainCustomManifest::instance()->getDirectoryName()).arg(TrainCustomManifest::instance()->getFileName()), tr("Manifest Creator Excel file not found!"), JOptionPane::ERROR_MESSAGE);
   }
   return false;
  }
  return true;
 }

 /*public*/ File* Train::createCSVManifestFile() {
     if (isModified()) {
         new TrainManifest(this);
         try {
             (new JsonManifest(this))->build();
         } catch (IOException ex) {
             log->error(tr("Unable to create JSON manifest %1").arg(ex.getLocalizedMessage()));
         }
         if (Setup::isGenerateCsvManifestEnabled()) {
             new TrainCsvManifest(this);
         }
     }
     File* file = TrainManagerXml::instance()->getTrainCsvManifestFile(getName());
     if (!file->exists()) {
         log->warn("CSV manifest file was not created for train " + getName());
         return NULL;
     }
     return file;
 }

 /*private*/ void Train::setPrinted(bool printed) {
     bool old = _printed;
     _printed = printed;
     if (old != printed) {
         setDirtyAndFirePropertyChange("trainPrinted", old ? "true" : "false", printed ? "true" : "false"); // NOI18N
     }
 }

 /**
  * Used to determine if train manifest was printed.
  *
  * @return true if the train manifest was printed.
  *
  */
 /*public*/ bool Train::isPrinted() {
     return _printed;
 }
#if 0
 /**
  * Deprecated, kept for user scripts. Use isPrinted()
  *
  * @return true if the train manifest was printed.
  *
  */
 @Deprecated
 /*public*/ bool getPrinted() {
     return _printed;
 }
#endif

 /**
  * Sets the panel position for the train icon for the current route
  * location.
  *
  * @return true if train coordinates can be set
  */
 /*public*/ bool Train::setTrainIconCoordinates() {
     if (Setup::isTrainIconCordEnabled()) {
         _trainIconRl->setTrainIconX(((Positionable*)_trainIcon)->getX());
         _trainIconRl->setTrainIconY(((Positionable*)_trainIcon)->getY());
         return true;
     }
     return false;
 }

 /**
  * Terminate train.
  */
 /*public*/ void Train::terminate() {
     while (isBuilt()) {
         move();
     }
 }

 /**
  * Move train to next location in route. Will move engines, cars, and train
  * icon. Will also terminate a train after it arrives at its final
  * destination.
  */
 /*public*/ void Train::move() {
     log->debug("Move train (" + getName() + ")");
     if (getRoute() ==NULL|| getCurrentLocation() == NULL) {
         setBuilt(false); // break terminate loop
         return;
     }
     RouteLocation* rl = getCurrentLocation();
     RouteLocation* rlNext = getNextLocation(rl);

     setCurrentLocation(rlNext);
     moveTrainIcon(rlNext);
     // cars and engines will move via property change
     setDirtyAndFirePropertyChange(TRAIN_LOCATION_CHANGED_PROPERTY, VPtr<RouteLocation>::asQVariant(rl), VPtr<RouteLocation>::asQVariant(rlNext));
     updateStatus(rl, rlNext);
     // tell GUI that train has complete its move
     setDirtyAndFirePropertyChange(TRAIN_MOVE_COMPLETE_CHANGED_PROPERTY, VPtr<RouteLocation>::asQVariant(rl), VPtr<RouteLocation>::asQVariant(rlNext));
 }

 /**
  * Move train to a location in the train's route. Code checks to see if the
  * location requested is part of the train's route and if the train hasn't
  * already visited the location. This command can only move the train
  * forward in its route. Note that you can not terminate the train using
  * this command. See move() or terminate().
  *
  * @param locationName The name of the location to move this train.
  * @return true if train was able to move to the named location.
  */
 /*public*/ bool Train::move(QString locationName) {
     log->info("Move train (" + getName() + ") to location (" + locationName + ")");
     if (getRoute() ==NULL|| getCurrentLocation() == NULL) {
         return false;
     }
     QList<RouteLocation*>* routeList = getRoute()->getLocationsBySequenceList();
     for (int i = 0; i < routeList->size(); i++) {
         RouteLocation* rl = routeList->at(i);
         if (getCurrentLocation() == rl) {
             for (int j = i + 1; j < routeList->size(); j++) {
                 rl = routeList->at(j);
                 if (rl->getName()==(locationName)) {
                     log->debug("Found location (" + locationName + ") moving train to this location");
                     for (j = i + 1; j < routeList->size(); j++) {
                         rl = routeList->at(j);
                         move();
                         if (rl->getName()==(locationName)) {
                             return true;
                         }
                     }
                 }
             }
             break; // done
         }
     }
     return false;
 }

 /**
  * Move train to the next location in the train's route. The location name
  * provided must be equal to the next location name in the train's route.
  *
  * @param locationName The next location name in the train's route.
  * @return true if successful.
  */
 /*public*/ bool Train::moveToNextLocation(QString locationName) {
     if (getNextLocationName()==(locationName)) {
         move();
         return true;
     }
     return false;
 }

/*public*/ void Train::loadTrainIcon() {
 if (getCurrentLocation() != NULL) {
     moveTrainIcon(getCurrentLocation());
 }
}


/*
* rl = to the next route location for this train
*/
/*protected*/ void Train::moveTrainIcon(RouteLocation* rl)
{
 _trainIconRl = rl;
 // create train icon if at departure or if program has been restarted
 if (rl == getTrainDepartsRouteLocation() || _trainIcon == NULL)
 {
     createTrainIcon();
 }
 // is the lead engine still in train
 if (getLeadEngine() !=NULL&& getLeadEngine()->getRouteDestination() == rl && rl != NULL)
 {
     log->debug("Engine (" + getLeadEngine()->toString() + ") arriving at destination " + rl->getName());
 }
 if (_trainIcon !=NULL&& _trainIcon->isActive())
 {
     setTrainIconColor();
     _trainIcon->setShowToolTip(true);
     QString txt = NULL;
     if (getCurrentLocationName()==(NONE))
     {
      txt = getDescription() + " " + tr("Terminated") + " (" + getTrainTerminatesName() + ")";
     }
     else
     {
      txt = tr("%1} at {%2} next {%3}").arg(getDescription()).arg(
                 getCurrentLocationName()).arg(getNextLocationName());
     }
     _trainIcon->setToolTip(txt);
// TODO::        _trainIcon->getTooltip().setBackgroundColor(Color.white);
     if (rl != NULL)
     {
         if (rl->getTrainIconX() != 0 || rl->getTrainIconY() != 0)
         {
#if 0
             if (animation)
             {
                 TrainIconAnimation* ta = new TrainIconAnimation(_trainIcon, rl, _ta);
                 ta.start(); // start the animation
                 _ta = ta;
             }
             else
#endif
             {
                 _trainIcon->setLocation(rl->getTrainIconX(), rl->getTrainIconY());
             }
         }
     }
  }
 }

 /*public*/ QString Train::getIconName() {
  QString name = getName();
  if (isBuilt() && getLeadEngine() !=NULL&& Setup::isTrainIconAppendEnabled()) {
      name += " " + getLeadEngine()->getNumber();
  }
  return name;
 }

 /*public*/ QString Train::getLeadEngineNumber()
  {
   if (getLeadEngine() == NULL) {
       return NONE;
   }
   return getLeadEngine()->getNumber();
 }

 /*public*/ QString Train::getLeadEngineRoadName() {
  if (getLeadEngine() == NULL) {
      return NONE;
  }
  return getLeadEngine()->getRoadName();
 }

 /*public*/ QString Train::getLeadEngineRoadAndNumber() {
  if (getLeadEngine() == NULL) {
      return NONE;
  }
  return getLeadEngine()->toString();
 }

 /**
 * Gets the lead engine, will create it if the program has been restarted
 *
 * @return lead engine for this train
 */
 /*public*/ Engine* Train::getLeadEngine() {
  if (_leadEngine ==NULL&& _leadEngineId!=(NONE)) {
      _leadEngine = EngineManager::instance()->getById(_leadEngineId);
  }
  return _leadEngine;
 }

 /*public*/ void Train::setLeadEngine(Engine* engine) {
  if (engine == NULL) {
      _leadEngineId = NONE;
  }
  _leadEngine = engine;
 }

 /*public*/ TrainIcon* Train::getTrainIcon() {
     return _trainIcon;
 }

/*public*/ void Train::createTrainIcon()
{
 if (_trainIcon !=NULL&& _trainIcon->isActive())
 {
  _trainIcon->remove();
  _trainIcon->dispose();
 }
 // if there's a panel specified, get it and place icon
 if (Setup::getPanelName()!=(Setup::NONE))
 {
  Editor* editor = ((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->getEditorByName(Setup::getPanelName());
  if (editor != NULL)
  {
   _trainIcon = editor->addTrainIcon(getIconName());
   _trainIcon->setTrain(this);
   if (getIconName().length() > 9)
   {
    //_trainIcon->setFont(FontUtil.deriveFont(_trainIcon->getFont(), 8.f));
    QFont f = _trainIcon->font();
    f.setPointSize(8);
    _trainIcon->setFont(f);
   }
   if (getCurrentLocation() != NULL) {
       _trainIcon->setLocation(getCurrentLocation()->getTrainIconX(), getCurrentLocation()->getTrainIconY());
   }
   // add throttle if there's a throttle manager
   if (InstanceManager::throttleManagerInstance() != NULL)
   {
    // add throttle if JMRI loco roster entry exist
    RosterEntry* entry = NULL;
    if (getLeadEngine() != NULL)
    {
     // first try and find a match based on loco road number
     QList<RosterEntry*> entries = Roster::getDefault()->matchingList(NULL, getLeadEngine()->getNumber(),
             NULL, NULL, NULL, NULL, NULL);
     if (entries.size() > 0) {
         entry = entries.at(0);
     }
     if (entry == NULL)
     {
      // now try finding a match based on DCC address
      entries = Roster::getDefault()->matchingList(NULL, NULL, getLeadEngine()->getNumber(), NULL,
              NULL, NULL, NULL);
      if (entries.size() > 0) {
          entry = entries.at(0);
      }
     }
    }
    if (entry != NULL)
    {
     _trainIcon->setRosterEntry(entry);
     if (getLeadEngine()->getConsist() != NULL)
     {
         _trainIcon->setConsistNumber(getLeadEngine()->getConsist()->getConsistNumber());
     }
    }
    else {
        log->debug("Loco roster entry not found for train (" + getName() + ")");
    }
   }
  }
 }
}

/*private*/ void Train::setTrainIconColor() {
  // Terminated train?
  if (getCurrentLocationName()==(NONE)) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorTerminate());
      return;
  }
  // local train?
  if (getRoute()->getLocationsBySequenceList()->size() == 1) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorLocal());
      return;
  }
  // set color based on train direction at current location
  if (_trainIconRl->getTrainDirection() == RouteLocation::NORTH) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorNorth());
  }
  if (_trainIconRl->getTrainDirection() == RouteLocation::SOUTH) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorSouth());
  }
  if (_trainIconRl->getTrainDirection() == RouteLocation::EAST) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorEast());
  }
  if (_trainIconRl->getTrainDirection() == RouteLocation::WEST) {
      _trainIcon->setLocoColor(Setup::getTrainIconColorWest());
  }
}

 // LocationManager locationManager = LocationManager.instance();
 /*private*/ void Train::updateStatus(RouteLocation* /*old*/, RouteLocation* next)
 {
  if (next != NULL)
  {
   setStatus(CODE_TRAIN_EN_ROUTE);
   // run move scripts
   runScripts(getMoveScripts());
  }
  else
  {
   log->debug("Train (" + getName() + ") terminated");
   setTerminationDate(TrainCommon::getDate(false));
   setStatus(CODE_TERMINATED);
   setBuilt(false);
   // run termination scripts
   runScripts(getTerminationScripts());
  }
 }

 /**
  * Sets the print status for switch lists
  *
  * @param status UNKNOWN PRINTED
  */
 /*public*/ void Train::setSwitchListStatus(QString status) {
     QString old = _switchListStatus;
     _switchListStatus = status;
     if (old!=status) {
         setDirtyAndFirePropertyChange("switch list train status", old, status); // NOI18N
     }
 }

 /*public*/ QString Train::getSwitchListStatus() {
     return _switchListStatus;
 }

 /**
  * Resets the train, removes engines and cars from this train.
  *
  * @return true if reset successful
  */
 /*public*/ bool Train::reset() {
     // is this train in route?
     if (isTrainInRoute()) {
         log->info("Train (" + getName() + ") has started its route, can not be reset");
         return false;
     }
     setCurrentLocation(NULL);
     setDepartureTrack(NULL);
     setTerminationTrack(NULL);
     setBuilt(false);
     setBuildFailed(false);
     setBuildFailedMessage(NONE);
     setPrinted(false);
     // remove cars and engines from this train via property change
     setStatus(CODE_TRAIN_RESET);
     // remove train icon
     if (_trainIcon !=NULL&& _trainIcon->isActive()) {
         _trainIcon->remove();
         _trainIcon->dispose();
     }
     return true;
 }

 /*public*/ void Train::dispose() {
     if (getRoute() != NULL) {
         //getRoute().removePropertyChangeListener(this);
     }
     //CarRoads.instance().removePropertyChangeListener(this);
     disconnect(CarRoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //CarTypes.instance().removePropertyChangeListener(this);
     disconnect(CarTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //EngineTypes.instance().removePropertyChangeListener(this);
     disconnect(EngineTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        CarOwners.instance().removePropertyChangeListener(this);
     disconnect(CarOwners::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        EngineModels.instance().removePropertyChangeListener(this);
     disconnect(EngineModels::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     setDirtyAndFirePropertyChange(DISPOSE_CHANGED_PROPERTY, QVariant(), "Dispose"); // NOI18N
 }

 /**
  * Construct this Entry from XML. This member has to remain synchronized
  * with the detailed DTD in operations-trains.dtd
  *
  * @param e Consist XML element
  */
 /*public*/ Train::Train(QDomElement e)
 {
  common();
     QString a;
     if ((a = e.attribute(Xml::ID)) != NULL) {
         _id = a;
     } else {
         log->warn("no id attribute in train element when reading operations");
     }
     if ((a = e.attribute(Xml::NAME)) != NULL) {
         _name = a;
     }
     if ((a = e.attribute(Xml::DESCRIPTION)) != NULL) {
         _description = a;
     }

     // create the train calendar
     _departureTime = Calendar::getInstance();
     _departureTime->set(2008, 10, 29, 12, 00); // The first release date for JMRI operations
     if ((a = e.attribute(Xml::DEPART_HOUR)) != NULL) {
         QString hour = a;
         if ((a = e.attribute(Xml::DEPART_MINUTE)) != NULL) {
             QString minute = a;
             setDepartureTime(hour, minute);
         }
     }

     // Trains table row color
     QDomElement eRowColor = e.firstChildElement(Xml::ROW_COLOR);
     if (!eRowColor.isNull() && (a = eRowColor.attribute(Xml::NAME)) != NULL) {
         _tableRowColorName = a;
     }

     // new format for train's route added in 2.99.7
     QDomElement eRoute = e.firstChildElement(Xml::ROUTE);
     if (!eRoute.isNull()) {
         if ((a = eRoute.attribute(Xml::ID)) != NULL) {
             setRoute(((RouteManager*)InstanceManager::getDefault("RouteManager"))->getRouteById(a));
         }
         if (eRoute.firstChildElement(Xml::SKIPS) != QDomElement()) {
             //@SuppressWarnings("unchecked")
             QDomNodeList skips = eRoute.firstChildElement(Xml::SKIPS).elementsByTagName(Xml::LOCATION);
             QVector<QString> locs = QVector<QString>(skips.size());
             for (int i = 0; i < skips.size(); i++) {
                 QDomElement loc = skips.at(i).toElement();
                 if ((a = loc.attribute(Xml::ID)) != NULL) {
                     locs.replace(i, a);
                 }
             }
             setTrainSkipsLocations(locs.toList());
         }
     } else {
         // old format
         // try and first get the route by id then by name
         if ((a = e.attribute(Xml::ROUTE_ID)) != NULL) {
             setRoute(((RouteManager*)InstanceManager::getDefault("RouteManager"))->getRouteById(a));
         } else if ((a = e.attribute(Xml::ROUTE)) != NULL) {
             setRoute(((RouteManager*)InstanceManager::getDefault("RouteManager"))->getRouteByName(a));
         }
         if ((a = e.attribute(Xml::SKIP)) != NULL) {
             QString locationIds = a;
             QStringList locs = locationIds.split("%%"); // NOI18N
             // if (log->isDebugEnabled()) log->debug("Train skips : "+locationIds);
             setTrainSkipsLocations(locs);
         }
     }
     // new way of reading car types using elements
     if (e.firstChildElement(Xml::TYPES) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carTypes = e.firstChildElement(Xml::TYPES).elementsByTagName(Xml::CAR_TYPE);
         QVector<QString> types = QVector<QString>(carTypes.size());
         for (int i = 0; i < carTypes.size(); i++) {
             QDomElement type = carTypes.at(i).toElement();
             if ((a = type.attribute(Xml::NAME)) != NULL) {
                 types.replace(i, a);
             }
         }
         setTypeNames(types.toList());
         //@SuppressWarnings("unchecked")
         QDomNodeList locoTypes = e.firstChildElement(Xml::TYPES).elementsByTagName(Xml::LOCO_TYPE);
         types = QVector<QString>(locoTypes.size());
         for (int i = 0; i < locoTypes.size(); i++) {
             QDomElement type = locoTypes.at(i).toElement();
             if ((a = type.attribute(Xml::NAME)) != NULL) {
                 types[i] = a;
             }
         }
         setTypeNames(types.toList());
     } // old way of reading car types up to version 2.99.6
     else if ((a = e.attribute(Xml::CAR_TYPES)) != NULL) {
         QString names = a;
         QStringList types = names.split("%%"); // NOI18N
         // if (log->isDebugEnabled()) log->debug("Car types: "+names);
         setTypeNames(types);
     }
     // old misspelled format
     if ((a = e.attribute(Xml::CAR_ROAD_OPERATION)) != NULL) {
         _roadOption = a;
     }
     if ((a = e.attribute(Xml::CAR_ROAD_OPTION)) != NULL) {
         _roadOption = a;
     }
     // new way of reading car roads using elements
     if (e.firstChildElement(Xml::CAR_ROADS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carRoads = e.firstChildElement(Xml::CAR_ROADS).elementsByTagName(Xml::CAR_ROAD);
         QVector<QString> roads = QVector<QString>(carRoads.size());
         for (int i = 0; i < carRoads.size(); i++) {
             QDomElement road = carRoads.at(i).toElement();
             if ((a = road.attribute(Xml::NAME)) != NULL) {
                 roads.replace(i, a);
             }
         }
         setRoadNames(roads.toList());
     } // old way of reading car roads up to version 2.99.6
     else if ((a = e.attribute(Xml::CAR_ROADS)) != NULL) {
         QString names = a;
         QStringList roads = names.split("%%"); // NOI18N
         if (log->isDebugEnabled()) {
             log->debug("Train (" + getName() + ") " + getRoadOption() + " car roads: " + names);
         }
         setRoadNames(roads);
     }

     if ((a = e.attribute(Xml::CAR_LOAD_OPTION)) != NULL) {
         _loadOption = a;
     }
     if ((a = e.attribute(Xml::CAR_OWNER_OPTION)) != NULL) {
         _ownerOption = a;
     }
     if ((a = e.attribute(Xml::BUILT_START_YEAR)) != NULL) {
         _builtStartYear = a;
     }
     if ((a = e.attribute(Xml::BUILT_END_YEAR)) != NULL) {
         _builtEndYear = a;
     }

     // new way of reading car loads using elements
     if (e.firstChildElement(Xml::CAR_LOADS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carLoads = e.firstChildElement(Xml::CAR_LOADS).elementsByTagName(Xml::CAR_LOAD);
         QVector<QString> loads = QVector<QString>(carLoads.size());
         for (int i = 0; i < carLoads.size(); i++) {
             QDomElement load = carLoads.at(i).toElement();
             if ((a = load.attribute(Xml::NAME)) != NULL) {
                 loads.replace(i, a);
             }
         }
         setLoadNames(loads.toList());
     } // old way of reading car loads up to version 2.99.6
     else if ((a = e.attribute(Xml::CAR_LOADS)) != NULL) {
         QString names = a;
         QStringList loads = names.split("%%"); // NOI18N
         if (log->isDebugEnabled()) {
             log->debug("Train (" + getName() + ") " + getLoadOption() + " car loads: " + names);
         }
         setLoadNames(loads);
     }
     // new way of reading car owners using elements
     if (e.firstChildElement(Xml::CAR_OWNERS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList carOwners = e.firstChildElement(Xml::CAR_OWNERS).elementsByTagName(Xml::CAR_OWNER);
         QVector<QString> owners = QVector<QString>(carOwners.size());
         for (int i = 0; i < carOwners.size(); i++) {
             QDomElement owner = carOwners.at(i).toElement();
             if ((a = owner.attribute(Xml::NAME)) != NULL) {
                 owners[i] = a;
             }
         }
         setOwnerNames(owners.toList());
     } // old way of reading car owners up to version 2.99.6
     else if ((a = e.attribute(Xml::CAR_OWNERS)) != NULL) {
         QString names = a;
         QStringList owners = names.split("%%"); // NOI18N
         if (log->isDebugEnabled()) {
             log->debug("Train (" + getName() + ") " + getOwnerOption() + " car owners: " + names);
         }
         setOwnerNames(owners);
     }

     if ((a = e.attribute(Xml::NUMBER_ENGINES)) != NULL) {
         _numberEngines = a;
     }
     if ((a = e.attribute(Xml::LEG2_ENGINES)) != NULL) {
         _leg2Engines = a;
     }
     if ((a = e.attribute(Xml::LEG3_ENGINES)) != NULL) {
         _leg3Engines = a;
     }
     if ((a = e.attribute(Xml::ENGINE_ROAD)) != NULL) {
         _engineRoad = a;
     }
     if ((a = e.attribute(Xml::LEG2_ROAD)) != NULL) {
         _leg2Road = a;
     }
     if ((a = e.attribute(Xml::LEG3_ROAD)) != NULL) {
         _leg3Road = a;
     }
     if ((a = e.attribute(Xml::ENGINE_MODEL)) != NULL) {
         _engineModel = a;
     }
     if ((a = e.attribute(Xml::LEG2_MODEL)) != NULL) {
         _leg2Model = a;
     }
     if ((a = e.attribute(Xml::LEG3_MODEL)) != NULL) {
         _leg3Model = a;
     }
     if ((a = e.attribute(Xml::REQUIRES)) != NULL) {
         bool ok;
             _requires = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Requires (%1) isn't a valid number for train (%2)").arg(a).arg(getName()));
         }
     }
     if ((a = e.attribute(Xml::CABOOSE_ROAD)) != NULL) {
         _cabooseRoad = a;
     }
     if ((a = e.attribute(Xml::LEG2_CABOOSE_ROAD)) != NULL) {
         _leg2CabooseRoad = a;
     }
     if ((a = e.attribute(Xml::LEG3_CABOOSE_ROAD)) != NULL) {
         _leg3CabooseRoad = a;
     }
     if ((a = e.attribute(Xml::LEG2_OPTIONS)) != NULL) {
         bool ok;
             _leg2Options = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Leg 2 options (%1) isn't a valid number for train (%2)").arg(a).arg(getName()));
         }
     }
     if ((a = e.attribute(Xml::LEG3_OPTIONS)) != NULL) {
         bool ok;
             _leg3Options = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Leg 3 options (%1 isn't a valid number for train (%2)").arg(a).arg(getName()));
         }
     }
     if ((a = e.attribute(Xml::BUILD_NORMAL)) != NULL) {
         _buildNormal = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::TO_TERMINAL)) != NULL) {
         _sendToTerminal = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::ALLOW_LOCAL_MOVES)) != NULL) {
         _allowLocalMoves = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::ALLOW_THROUGH_CARS)) != NULL) {
         _allowThroughCars = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::ALLOW_RETURN)) != NULL) {
         _allowCarsReturnStaging = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::SERVICE_ALL)) != NULL) {
         _serviceAllCarsWithFinalDestinations = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::BUILD_CONSIST)) != NULL) {
         _buildConsist = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::SEND_CUSTOM_STAGING)) != NULL) {
         _sendCarsWithCustomLoadsToStaging = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::BUILT)) != NULL) {
         _built = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::BUILD)) != NULL) {
         _build = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::BUILD_FAILED)) != NULL) {
         _buildFailed = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::BUILD_FAILED_MESSAGE)) != NULL) {
         _buildFailedMessage = a;
     }
     if ((a = e.attribute(Xml::PRINTED)) != NULL) {
         _printed = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::MODIFIED)) != NULL) {
         _modified = a==(Xml::_TRUE);
     }
     if ((a = e.attribute(Xml::SWITCH_LIST_STATUS)) != NULL) {
         _switchListStatus = a;
     }
     if ((a = e.attribute(Xml::LEAD_ENGINE)) != NULL) {
         _leadEngineId = a;
     }
     if ((a = e.attribute(Xml::TERMINATION_DATE)) != NULL) {
         _statusTerminatedDate = a;
     }
     if ((a = e.attribute(Xml::REQUESTED_CARS)) != NULL) {
         bool ok;
             _statusCarsRequested = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Status cars requested (%1) isn't a valid number for train (%1)").arg(a).arg(getName()));
         }
     }
     if ((a = e.attribute(Xml::STATUS)) !=NULL&& e.attribute(Xml::STATUS_CODE) == NULL) {
         QString status = a;
         if (status.startsWith(BUILD_FAILED)) {
             _statusCode = CODE_BUILD_FAILED;
         } else if (status.startsWith(BUILT)) {
             _statusCode = CODE_BUILT;
         } else if (status.startsWith(PARTIAL_BUILT)) {
             _statusCode = CODE_PARTIAL_BUILT;
         } else if (status.startsWith(TERMINATED)) {
             QStringList splitStatus = status.split(" ");
             if (splitStatus.length() > 1) {
                 _statusTerminatedDate = splitStatus[1];
             }
             _statusCode = CODE_TERMINATED;
         } else if (status.startsWith(TRAIN_IN_ROUTE)) {
             _statusCode = CODE_TRAIN_EN_ROUTE;
         } else if (status.startsWith(TRAIN_RESET)) {
             _statusCode = CODE_TRAIN_RESET;
         } else {
             _statusCode = CODE_UNKNOWN;
         }
     }
     if ((a = e.attribute(Xml::STATUS_CODE)) != NULL) {
         bool ok;
             _statusCode = a.toInt(&ok);
         if(!ok) {
             log->error(tr("Status code (%1) isn't a valid number for train (%2)").arg(a).arg(getName()));
         }
     }
     if ((a = e.attribute(Xml::COMMENT)) != NULL) {
         _comment = OperationsXml::convertFromXmlComment(a);
     }
     if (_route != NULL) {
         if ((a = e.attribute(Xml::CURRENT)) != NULL) {
             _current = _route->getLocationById(a);
         }
         if ((a = e.attribute(Xml::LEG2_START)) != NULL) {
             _leg2Start = _route->getLocationById(a);
         }
         if ((a = e.attribute(Xml::LEG3_START)) != NULL) {
             _leg3Start = _route->getLocationById(a);
         }
         if ((a = e.attribute(Xml::LEG2_END)) != NULL) {
             _end2Leg = _route->getLocationById(a);
         }
         if ((a = e.attribute(Xml::LEG3_END)) != NULL) {
             _leg3End = _route->getLocationById(a);
         }
         if ((a = e.attribute(Xml::DEPARTURE_TRACK)) != NULL) {
             Location* location = LocationManager::instance()->getLocationByName(getTrainDepartsName());
             if (location != NULL) {
                 _departureTrack = location->getTrackById(a);
             } else {
                 log->error("Departure location not found for track " + a);
             }
         }
         if ((a = e.attribute(Xml::TERMINATION_TRACK)) != NULL) {
             Location* location = LocationManager::instance()->getLocationByName(getTrainTerminatesName());
             if (location != NULL) {
                 _terminationTrack = location->getTrackById(a);
             } else {
                 log->error("Termiation location not found for track " + a);
             }
         }
     }

     // check for scripts
     if (e.firstChildElement(Xml::SCRIPTS) != QDomElement()) {
         //@SuppressWarnings("unchecked")
         QDomNodeList lb = e.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::BUILD);
         //for (QDomElement es : lb) {
         for(int i=0; i < lb.size(); i++)
         {
          QDomElement es = lb.at(i).toElement();
             if ((a = es.attribute(Xml::NAME)) != NULL) {
                 addBuildScript(a);
             }
         }
         //@SuppressWarnings("unchecked")
         QDomNodeList lab = e.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::AFTER_BUILD);
         //foreach (QDomElement es : lab) {
         for(int i = 0; i < lab.size(); i++)
         {
          QDomElement es = lab.at(i).toElement();
             if ((a = es.attribute(Xml::NAME)) != NULL) {
                 addAfterBuildScript(a);
             }
         }
         //@SuppressWarnings("unchecked")
         QDomNodeList lm = e.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::MOVE);
         //for (QDomElement es : lm) {
         for(int i = 0; i < lm.size(); i++)
         {
          QDomElement es = lm.at(i).toElement();
             if ((a = es.attribute(Xml::NAME)) != NULL) {
                 addMoveScript(a);
             }
         }
         //@SuppressWarnings("unchecked")
         QDomNodeList lt = e.firstChildElement(Xml::SCRIPTS).elementsByTagName(Xml::TERMINATE);
         //for (QDomElement es : lt) {
         for(int i = 0; i < lt.size(); i++)
         {
          QDomElement es = lt.at(i).toElement();
             if ((a = es.attribute(Xml::NAME)) != NULL) {
                 addTerminationScript(a);
             }
         }
     }
     // check for optional railroad name and logo
     if ((e.firstChildElement(Xml::RAIL_ROAD) != QDomElement()) && (a = e.firstChildElement(Xml::RAIL_ROAD).attribute(Xml::NAME)) != NULL) {
         QString name = a;
         setRailroadName(name);
     }
     if ((e.firstChildElement(Xml::MANIFEST_LOGO) != QDomElement())) {
         if ((a = e.firstChildElement(Xml::MANIFEST_LOGO).attribute(Xml::NAME)) != NULL) {
             setManifestLogoURL(a);
         }
     }
     if ((a = e.attribute(Xml::SHOW_TIMES)) != NULL) {
         _showTimes = a==(Xml::_TRUE);
     }

     addPropertyChangeListerners();
 }

 /*private*/ void Train::addPropertyChangeListerners()
{
  //CarRoads.instance().addPropertyChangeListener(this);
 connect(CarRoads::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarTypes.instance().addPropertyChangeListener(this);
 connect(CarTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineTypes.instance().addPropertyChangeListener(this);
 connect(EngineTypes::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //CarOwners.instance().addPropertyChangeListener(this);
 connect(CarOwners::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //EngineModels.instance().addPropertyChangeListener(this);
  connect(EngineModels::instance(), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

}
 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-trains.dtd.
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement Train::store(QDomDocument doc) {
     QDomElement e = doc.createElement(Xml::TRAIN);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     e.setAttribute(Xml::DESCRIPTION, getRawDescription());
     e.setAttribute(Xml::DEPART_HOUR, getDepartureTimeHour());
     e.setAttribute(Xml::DEPART_MINUTE, getDepartureTimeMinute());

     QDomElement eRowColor = doc.createElement(Xml::ROW_COLOR);
     eRowColor.setAttribute(Xml::NAME, getTableRowColorName());
     e.appendChild(eRowColor);

     QDomElement eRoute = doc.createElement(Xml::ROUTE);
     if (getRoute() != NULL) {
         // old format
         if (Control::backwardCompatible) {
             e.setAttribute(Xml::ROUTE, getRoute()->getName());
             e.setAttribute(Xml::ROUTE_ID, getRoute()->getId());
         }
         // new format
         eRoute.setAttribute(Xml::NAME, getRoute()->getName());
         eRoute.setAttribute(Xml::ID, getRoute()->getId());
         e.appendChild(eRoute);
         // build list of locations that this train skips
         // new format
         QStringList locationIds = getTrainSkipsLocations();
         if (locationIds.length() > 0) {
             QDomElement eSkips = doc.createElement(Xml::SKIPS);
             foreach (QString id, locationIds) {
                 QDomElement eLoc = doc.createElement(Xml::LOCATION);
                 RouteLocation* rl = getRoute()->getLocationById(id);
                 if (rl != NULL) {
                     eLoc.setAttribute(Xml::NAME, rl->getName());
                     eLoc.setAttribute(Xml::ID, id);
                     eSkips.appendChild(eLoc);
                 }
             }
             eRoute.appendChild(eSkips);
         }
     }
     // build list of locations that this train skips
     // old format
     if (Control::backwardCompatible) {
         QString buf = ""; //new StringBuffer();
         foreach (QString id, getTrainSkipsLocations()) {
             buf.append(id + "%%"); // NOI18N
         }
         e.setAttribute(Xml::SKIP, buf/*.toString()*/);
     }
     if (getCurrentLocation() != NULL) {
         e.setAttribute(Xml::CURRENT, getCurrentLocation()->getId());
     }
     if (getDepartureTrack() != NULL) {
         e.setAttribute(Xml::DEPARTURE_TRACK, getDepartureTrack()->getId());
     }
     if (getTerminationTrack() != NULL) {
         e.setAttribute(Xml::TERMINATION_TRACK, getTerminationTrack()->getId());
     }
     if (Control::backwardCompatible) {
         e.setAttribute(Xml::CAR_ROAD_OPERATION, getRoadOption()); // misspelled should have been option not operation
     }
     e.setAttribute(Xml::BUILT_START_YEAR, getBuiltStartYear());
     e.setAttribute(Xml::BUILT_END_YEAR, getBuiltEndYear());
     e.setAttribute(Xml::NUMBER_ENGINES, getNumberEngines());
     e.setAttribute(Xml::ENGINE_ROAD, getEngineRoad());
     e.setAttribute(Xml::ENGINE_MODEL, getEngineModel());
     e.setAttribute(Xml::REQUIRES, QString::number(getRequirements()));
     e.setAttribute(Xml::CABOOSE_ROAD, getCabooseRoad());
     e.setAttribute(Xml::BUILD_NORMAL, isBuildTrainNormalEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::TO_TERMINAL, isSendCarsToTerminalEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::ALLOW_LOCAL_MOVES, isAllowLocalMovesEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::ALLOW_RETURN, isAllowReturnToStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::ALLOW_THROUGH_CARS, isAllowThroughCarsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::SERVICE_ALL, isServiceAllCarsWithFinalDestinationsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::SEND_CUSTOM_STAGING, isSendCarsWithCustomLoadsToStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::BUILD_CONSIST, isBuildConsistEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::BUILT, isBuilt() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::BUILD, isBuildEnabled() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::BUILD_FAILED, getBuildFailed() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::BUILD_FAILED_MESSAGE, getBuildFailedMessage());
     e.setAttribute(Xml::PRINTED, isPrinted() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::MODIFIED, isModified() ? Xml::_TRUE : Xml::_FALSE);
     e.setAttribute(Xml::SWITCH_LIST_STATUS, getSwitchListStatus());
     if (getLeadEngine() != NULL) {
         e.setAttribute(Xml::LEAD_ENGINE, getLeadEngine()->getId());
     }
     e.setAttribute(Xml::STATUS, getStatus());
     e.setAttribute(Xml::TERMINATION_DATE, getTerminationDate());
     e.setAttribute(Xml::REQUESTED_CARS, QString::number(getNumberCarsRequested()));
     e.setAttribute(Xml::STATUS_CODE, QString::number(getStatusCode()));
     e.setAttribute(Xml::COMMENT, getComment());
     e.setAttribute(Xml::SHOW_TIMES, isShowArrivalAndDepartureTimesEnabled() ? Xml::_TRUE : Xml::_FALSE);
     // build list of car types for this train
     QStringList types = getTypeNames();
     // Old way of saving car types
     if (Control::backwardCompatible) {
         QString buf = ""; //new StringBuffer();
         foreach (QString type, types) {
             // remove types that have been deleted by user
             if (CarTypes::instance()->containsName(type) || EngineTypes::instance()->containsName(type)) {
                 buf.append(type + "%%"); // NOI18N
             }
         }
         e.setAttribute(Xml::CAR_TYPES, buf/*.toString()*/);
     }
     // new way of saving car types
     QDomElement eTypes = doc.createElement(Xml::TYPES);
     foreach (QString type, types) {
         // don't save types that have been deleted by user
         if (EngineTypes::instance()->containsName(type)) {
             QDomElement eType = doc.createElement(Xml::LOCO_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         } else if (CarTypes::instance()->containsName(type)) {
             QDomElement eType = doc.createElement(Xml::CAR_TYPE);
             eType.setAttribute(Xml::NAME, type);
             eTypes.appendChild(eType);
         }
     }
     e.appendChild(eTypes);
     // save list of car roads for this train
     if (getRoadOption()!=(ALL_ROADS)) {
         e.setAttribute(Xml::CAR_ROAD_OPTION, getRoadOption());
         QStringList roads = getRoadNames();
         // old way of saving road names
         if (Control::backwardCompatible) {
             QString buf = ""; //new StringBuffer();
             foreach (QString road, roads) {
                 buf.append(road + "%%"); // NOI18N
             }
             e.setAttribute(Xml::CAR_ROADS, buf/*.toString()*/);
         }
         // new way of saving road names
         QDomElement eRoads = doc.createElement(Xml::CAR_ROADS);
         foreach (QString road, roads) {
             QDomElement eRoad = doc.createElement(Xml::CAR_ROAD);
             eRoad.setAttribute(Xml::NAME, road);
             eRoads.appendChild(eRoad);
         }
         e.appendChild(eRoads);
     }
     // save list of car loads for this train
     if (getLoadOption()!=(ALL_LOADS)) {
         e.setAttribute(Xml::CAR_LOAD_OPTION, getLoadOption());
         QStringList loads = getLoadNames();
         // old way of saving car loads
         if (Control::backwardCompatible) {
             QString buf = "";//new StringBuffer();
             foreach (QString load, loads) {
                 buf.append(load + "%%"); // NOI18N
             }
             e.setAttribute(Xml::CAR_LOADS, buf/*.toString()*/);
         }
         // new way of saving car loads
         QDomElement eLoads = doc.createElement(Xml::CAR_LOADS);
         foreach (QString load, loads) {
             QDomElement eLoad = doc.createElement(Xml::CAR_LOAD);
             eLoad.setAttribute(Xml::NAME, load);
             eLoads.appendChild(eLoad);
         }
         e.appendChild(eLoads);
     }
     // save list of car owners for this train
     if (getOwnerOption()!=(ALL_OWNERS)) {
         e.setAttribute(Xml::CAR_OWNER_OPTION, getOwnerOption());
         QStringList owners = getOwnerNames();
         // old way of saving car owners
         if (Control::backwardCompatible) {
             QString buf = "";//new StringBuffer();
             foreach (QString owner, owners) {
                 buf.append(owner + "%%"); // NOI18N
             }
             e.setAttribute(Xml::CAR_OWNERS, buf/*.toString()*/);
         }
         // new way of saving car owners
         QDomElement eOwners = doc.createElement(Xml::CAR_OWNERS);
         foreach (QString owner, owners) {
             QDomElement eOwner = doc.createElement(Xml::CAR_OWNER);
             eOwner.setAttribute(Xml::NAME, owner);
             eOwners.appendChild(eOwner);
         }
         e.appendChild(eOwners);
     }
     // save list of scripts for this train
     if (getBuildScripts().size() > 0 || getAfterBuildScripts().size() > 0 || getMoveScripts().size() > 0
             || getTerminationScripts().size() > 0) {
         QDomElement es = doc.createElement(Xml::SCRIPTS);
         if (getBuildScripts().size() > 0) {
             foreach (QString scriptPathname, getBuildScripts()) {
                 QDomElement em = doc.createElement(Xml::BUILD);
                 em.setAttribute(Xml::NAME, scriptPathname);
                 es.appendChild(em);
             }
         }
         if (getAfterBuildScripts().size() > 0) {
             foreach (QString scriptPathname, getAfterBuildScripts()) {
                 QDomElement em = doc.createElement(Xml::AFTER_BUILD);
                 em.setAttribute(Xml::NAME, scriptPathname);
                 es.appendChild(em);
             }
         }
         if (getMoveScripts().size() > 0) {
             foreach (QString scriptPathname, getMoveScripts()) {
                 QDomElement em = doc.createElement(Xml::MOVE);
                 em.setAttribute(Xml::NAME, scriptPathname);
                 es.appendChild(em);
             }
         }
         // save list of termination scripts for this train
         if (getTerminationScripts().size() > 0) {
             foreach (QString scriptPathname, getTerminationScripts()) {
                 QDomElement et = doc.createElement(Xml::TERMINATE);
                 et.setAttribute(Xml::NAME, scriptPathname);
                 es.appendChild(et);
             }
         }
         e.appendChild(es);
     }
     if (getRailroadName()!=(NONE)) {
         QDomElement r = doc.createElement(Xml::RAIL_ROAD);
         r.setAttribute(Xml::NAME, getRailroadName());
         e.appendChild(r);
     }
     if (getManifestLogoURL()!=(NONE)) {
         QDomElement l = doc.createElement(Xml::MANIFEST_LOGO);
         l.setAttribute(Xml::NAME, getManifestLogoURL());
         e.appendChild(l);
     }

     if (getSecondLegOptions() != NO_CABOOSE_OR_FRED) {
         e.setAttribute(Xml::LEG2_OPTIONS, QString::number(getSecondLegOptions()));
         e.setAttribute(Xml::LEG2_ENGINES, getSecondLegNumberEngines());
         e.setAttribute(Xml::LEG2_ROAD, getSecondLegEngineRoad());
         e.setAttribute(Xml::LEG2_MODEL, getSecondLegEngineModel());
         e.setAttribute(Xml::LEG2_CABOOSE_ROAD, getSecondLegCabooseRoad());
         if (getSecondLegStartLocation() != NULL) {
             e.setAttribute(Xml::LEG2_START, getSecondLegStartLocation()->getId());
         }
         if (getSecondLegEndLocation() != NULL) {
             e.setAttribute(Xml::LEG2_END, getSecondLegEndLocation()->getId());
         }
     }
     if (getThirdLegOptions() != NO_CABOOSE_OR_FRED) {
         e.setAttribute(Xml::LEG3_OPTIONS, QString::number(getThirdLegOptions()));
         e.setAttribute(Xml::LEG3_ENGINES, getThirdLegNumberEngines());
         e.setAttribute(Xml::LEG3_ROAD, getThirdLegEngineRoad());
         e.setAttribute(Xml::LEG3_MODEL, getThirdLegEngineModel());
         e.setAttribute(Xml::LEG3_CABOOSE_ROAD, getThirdLegCabooseRoad());
         if (getThirdLegStartLocation() != NULL) {
             e.setAttribute(Xml::LEG3_START, getThirdLegStartLocation()->getId());
         }
         if (getThirdLegEndLocation() != NULL) {
             e.setAttribute(Xml::LEG3_END, getThirdLegEndLocation()->getId());
         }
     }

     return e;
 }

 /*public*/ void Train::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Train ({}) sees property change: (%1) old: (%2) new: (%3)").arg(
                 getName()).arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString()));
     }
     if (e->getPropertyName()==(/*Route::DISPOSE)*/"DISPOSE"))
     {
         setRoute(NULL);
     }

     if (e->getPropertyName()==(CarTypes::CARTYPES_NAME_CHANGED_PROPERTY)
             || e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(EngineTypes::ENGINETYPES_NAME_CHANGED_PROPERTY)) {
         replaceType( e->getOldValue().toString(),  e->getNewValue().toString());
     }
     if (e->getPropertyName()==(CarRoads::CARROADS_NAME_CHANGED_PROPERTY)) {
         replaceRoad( e->getOldValue().toString(),  e->getNewValue().toString());
     }
#if 0
     if (e->getPropertyName()==(CarOwners.CAROWNERS_NAME_CHANGED_PROPERTY)) {
         replaceOwner( e->getOldValue(),  e->getNewValue());
     }
#endif
     if (e->getPropertyName()==(EngineModels::ENGINEMODELS_NAME_CHANGED_PROPERTY)) {
         replaceModel( e->getOldValue().toString(),  e->getNewValue().toString());
     }
     // forward route departure time property changes
     if (e->getPropertyName()==(RouteLocation::DEPARTURE_TIME_CHANGED_PROPERTY)) {
         setDirtyAndFirePropertyChange(DEPARTURETIME_CHANGED_PROPERTY, e->getOldValue(), e->getNewValue());
     }

     // forward any property changes in this train's route
     if (QString(e->getSource()->metaObject()->className()) ==("Route-")) {
         setDirtyAndFirePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
     }
 }

#if 0
 /*public*/ /*synchronized*/ void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ /*synchronized*/ void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
        pcs.removePropertyChangeListener(l);
 }
#endif
/*protected*/ void Train::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
    TrainManagerXml::instance()->setDirty(true);
    pcs->firePropertyChange(p, old, n);
 }
} //end namespace
