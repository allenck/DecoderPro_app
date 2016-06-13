#include "routelocation.h"
#include "xml.h"
#include "setup.h"
#include "location.h"
#include "routemanagerxml.h"
#include "locationmanager.h"
#include "control.h"

//RouteLocation::RouteLocation(QObject *parent) :
//  QObject(parent)
//{
//}
/**
 * Represents a location in a route, a location can appear more than once in a
 * route.
 *
 * @author Daniel Boudreau Copyright (C) 2008, 2013
 * @version $Revision: 29886 $
 */
///*public*/ class RouteLocation implements java.beans.PropertyChangeListener {
namespace Operations
{
 /*public*/ /*static*/ /*final*/ QString RouteLocation::NONE = "";


 /*public*/ /*static final*/ int RouteLocation::EAST = 1; // train direction
 /*public*/ /*static final*/ int RouteLocation::WEST = 2;
 /*public*/ /*static final*/ int RouteLocation::NORTH = 4;
 /*public*/ /*static final*/ int RouteLocation::SOUTH = 8;

 /*public*/ /*static final*/ QString RouteLocation::EAST_DIR = tr("East");//Setup::EAST_DIR; // train directions text
 /*public*/ /*static final*/ QString RouteLocation::WEST_DIR = tr("West");//Setup::WEST_DIR;
 /*public*/ /*static final*/ QString RouteLocation::NORTH_DIR = tr("North");//Setup::NORTH_DIR;
 /*public*/ /*static final*/ QString RouteLocation::SOUTH_DIR = tr("South");//Setup::SOUTH_DIR;

 /*public*/ /*static final*/ QString RouteLocation::DISPOSE = "routeLocationDispose"; // NOI18N
 /*public*/ /*static final*/ QString RouteLocation::DELETED = tr("<location deleted>");

 /*public*/ /*static final*/ QString RouteLocation::DROP_CHANGED_PROPERTY = "dropChange"; // NOI18N
 /*public*/ /*static final*/ QString RouteLocation::PICKUP_CHANGED_PROPERTY = "pickupChange"; // NOI18N
 /*public*/ /*static final*/ QString RouteLocation::MAXMOVES_CHANGED_PROPERTY = "maxMovesChange"; // NOI18N
 /*public*/ /*static final*/ QString RouteLocation::TRAIN_DIRECTION_CHANGED_PROPERTY = "trainDirectionChange"; // NOI18N
 /*public*/ /*static final*/ QString RouteLocation::DEPARTURE_TIME_CHANGED_PROPERTY = "routeDepartureTimeChange"; // NOI18N

 /*public*/ /*static final*/ QString RouteLocation::DISABLED = "Off";

 /*public*/ RouteLocation::RouteLocation(QString id, Location* location, QObject *parent) :
QObject(parent)
 {
  common();
  log->debug(tr("New route location (%1) id: %2").arg(location->getName()).arg(id));
   _location = location;
   _id = id;
   // listen for name change or delete
   //location.addPropertyChangeListener(this);
   connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
 void RouteLocation::common()
 {
 log = new Logger("RouteLocation");

  _locationId = NONE; // the location's id
  _trainDir = (Setup::getTrainDirection() == Setup::EAST + Setup::WEST) ? EAST : NORTH; // train direction
  _maxTrainLength = Setup::getMaxTrainLength();
  _maxCarMoves = Setup::getCarMoves();
  _randomControl = DISABLED;
  _drops = true; // when true set outs allowed at this location
  _pickups = true; // when true pick ups allowed at this location
  _sequenceId = 0; // used to determine location order in route
  _grade = 0; // maximum grade between locations
  _wait = 0; // wait time at this location
  _departureTime = NONE; // departure time from this location
  _trainIconX = 0; // the x & y coordinates for the train icon
  _trainIconY = 0;
  _comment = NONE;
  _carMoves = 0; // number of moves at this location
  _trainWeight = 0; // total car weight departing this location
  _trainLength = 0; // train length departing this location
  _location = NULL;
  pcs = new PropertyChangeSupport(this);
 }

 // for combo boxes
 /*public*/ QString RouteLocation::toString()
 {
  if (_location != NULL) {
      return _location->getName();
  }
  return DELETED;
 }

 /*public*/ QString RouteLocation::getId() {
     return _id;
 }

 /*public*/ QString RouteLocation::getName() {
     if (_location != NULL) {
         return _location->getName();
     }
     return DELETED;
 }

 /*private*/ QString RouteLocation::getNameId() {
     if (_location != NULL) {
         return _location->getId();
     }
     return _locationId;
 }

 /*public*/ Location* RouteLocation::getLocation() {
     return _location;
 }

 /*public*/ int RouteLocation::getSequenceId() {
     return _sequenceId;
 }

 /*public*/ void RouteLocation::setSequenceId(int sequence) {
     // property change not needed
     _sequenceId = sequence;
 }

 /*public*/ void RouteLocation::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=(_comment)) {
         setDirtyAndFirePropertyChange("RouteLocationComment", old, comment); // NOI18N
     }
 }

 /*public*/ QString RouteLocation::getComment() {
     return _comment;
 }

 /*public*/ void RouteLocation::setTrainDirection(int direction) {
     int old = _trainDir;
     _trainDir = direction;
     if (old != direction) {
         setDirtyAndFirePropertyChange(TRAIN_DIRECTION_CHANGED_PROPERTY, old, (direction));
     }
 }

 /**
  * Gets the binary representation of the train's direction at this location
  *
  * @return int representing train direction EAST WEST NORTH SOUTH
  */
 /*public*/ int RouteLocation::getTrainDirection() {
     return _trainDir;
 }

 /**
  * Gets the String representation of the train's direction at this location
  *
  * @return String representing train direction at this location
  */
 /*public*/ QString RouteLocation::getTrainDirectionString() {
     return Setup::getDirectionString(getTrainDirection());
 }

 /*public*/ void RouteLocation::setMaxTrainLength(int length) {
     int old = _maxTrainLength;
     _maxTrainLength = length;
     if (old != length) {
         setDirtyAndFirePropertyChange("maxTrainLength", QString::number(old), QString::number(length)); // NOI18N
     }
 }

 /*public*/ int RouteLocation::getMaxTrainLength() {
     return _maxTrainLength;
 }

 /**
  * Set the train length departing this location when building a train
  *
  * @param length
  */
 /*public*/ void RouteLocation::setTrainLength(int length) {
     int old = _trainLength;
     _trainLength = length;
     if (old != length) {
         firePropertyChange("trainLength", QString::number(old), QString::number(length)); // NOI18N
     }
 }

 /*public*/ int RouteLocation::getTrainLength() {
     return _trainLength;
 }

 /**
  * Set the train weight departing this location when building a train
  *
  * @param weight
  */
 /*public*/ void RouteLocation::setTrainWeight(int weight) {
     int old = _trainWeight;
     _trainWeight = weight;
     if (old != weight) {
         firePropertyChange("trainWeight", QString::number(old), QString::number(weight)); // NOI18N
     }
 }

 /*public*/ int RouteLocation::getTrainWeight() {
     return _trainWeight;
 }

 /*public*/ void RouteLocation::setMaxCarMoves(int moves) {
     int old = _maxCarMoves;
     _maxCarMoves = moves;
     if (old != moves) {
         setDirtyAndFirePropertyChange(MAXMOVES_CHANGED_PROPERTY, QString::number(old), QString::number(moves));
     }
 }

 /**
  * Get the maximum number of moves for this location
  *
  * @return maximum number of moves
  */
 /*public*/ int RouteLocation::getMaxCarMoves() {
     return _maxCarMoves;
 }

 /*public*/ void RouteLocation::setRandomControl(QString value) {
     QString old = _randomControl;
     _randomControl = value;
     if (old!=(value)) {
         setDirtyAndFirePropertyChange("randomControl", old, value); // NOI18N
     }
 }

 /*public*/ QString RouteLocation::getRandomControl() {
     return _randomControl;
 }

 /**
  * When true allow car drops at this location
  *
  * @param drops when true drops allowed at this location
  */
 /*public*/ void RouteLocation::setDropAllowed(bool drops) {
     bool old = _drops;
     _drops = drops;
     if (old != drops) {
         setDirtyAndFirePropertyChange(DROP_CHANGED_PROPERTY, old ? "true" : "false", drops ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool RouteLocation::isDropAllowed() {
     return _drops;
 }

 /**
  * When true allow car pick ups at this location
  *
  * @param pickups when true pick ups allowed at this location
  */
 /*public*/ void RouteLocation::setPickUpAllowed(bool pickups) {
     bool old = _pickups;
     _pickups = pickups;
     if (old != pickups) {
         setDirtyAndFirePropertyChange(PICKUP_CHANGED_PROPERTY, old ? "true" : "false", pickups ? "true" : "false"); // NOI18N
     }
 }

 /*public*/ bool RouteLocation::isPickUpAllowed() {
     return _pickups;
 }

 /**
  * Set the number of moves that this location has when building a train
  *
  * @param moves
  */
 /*public*/ void RouteLocation::setCarMoves(int moves) {
     int old = _carMoves;
     _carMoves = moves;
     if (old != moves) {
         firePropertyChange("carMoves", QString::number(old), QString::number(moves)); // NOI18N
     }
 }

 /*public*/ int RouteLocation::getCarMoves() {
     return _carMoves;
 }

 /*public*/ void RouteLocation::setWait(int time) {
     int old = _wait;
     _wait = time;
     if (old != time) {
         setDirtyAndFirePropertyChange("waitTime", QString::number(old), QString::number(time)); // NOI18N
     }
 }

 /*public*/ int RouteLocation::getWait() {
     return _wait;
 }

 /*public*/ void RouteLocation::setDepartureTime(QString time) {
     QString old = _departureTime;
     _departureTime = time;
     if (old!=(time)) {
         setDirtyAndFirePropertyChange(DEPARTURE_TIME_CHANGED_PROPERTY, old, time);
     }
 }

 /*public*/ void RouteLocation::setDepartureTime(QString hour, QString minute) {
     QString old = _departureTime;
     int h = (hour.toInt());
     if (h < 10) {
         hour = "0" + h;
     }
     int m = (minute.toInt());
     if (m < 10) {
         minute = "0" + m;
     }
     QString time = hour + ":" + minute;
     _departureTime = time;
     if (old!=(time)) {
         setDirtyAndFirePropertyChange(DEPARTURE_TIME_CHANGED_PROPERTY, old, time);
     }
 }

 /*public*/ QString RouteLocation::getDepartureTime() {
     return _departureTime;
 }

 /*public*/ QString RouteLocation::getDepartureTimeHour() {
     QStringList time = getDepartureTime().split(":");
     return time[0];
 }

 /*public*/ QString RouteLocation::getDepartureTimeMinute() {
     QStringList time = getDepartureTime().split(":");
     return time[1];
 }

 /*public*/ QString RouteLocation::getFormatedDepartureTime() {
     if (getDepartureTime()==(NONE) || !Setup::is12hrFormatEnabled()) {
         return _departureTime;
     }
     QString AM_PM = " " + tr("AM");
     QStringList time = getDepartureTime().split(":");
     int hour = (time[0].toInt());
     if (hour >= 12) {
         AM_PM = " " + tr("PM");
         hour = hour - 12;
     }
     if (hour == 0) {
         hour = 12;
     }
     time[0] = QString::number(hour);
     return time[0] + ":" + time[1] + AM_PM;
 }

 /*public*/ void RouteLocation::setGrade(double grade) {
     double old = _grade;
     _grade = grade;
     if (old != grade) {
         setDirtyAndFirePropertyChange("grade", QString::number(old), QString::number(grade)); // NOI18N
     }
 }

 /*public*/ double RouteLocation::getGrade() {
     return _grade;
 }

/*public*/ void RouteLocation::setTrainIconX(int x) {
 int old = _trainIconX;
 _trainIconX = x;
 if (old != x) {
     setDirtyAndFirePropertyChange("trainIconX", QString::number(old), QString::number(x)); // NOI18N
 }
}

/*public*/ int RouteLocation::getTrainIconX() {
 return _trainIconX;
}

/*public*/ void RouteLocation::setTrainIconY(int y) {
 int old = _trainIconY;
 _trainIconY = y;
 if (old != y) {
     setDirtyAndFirePropertyChange("trainIconY", QString::number(old), QString::number(y)); // NOI18N
 }
}

/*public*/ int RouteLocation::getTrainIconY() {
 return _trainIconY;
}

/**
* Set the train icon panel coordinates to the location defaults.
* Coordinates are dependent on the train's departure direction.
*/
/*public*/ void RouteLocation::setTrainIconCoordinates() {
 Location* l = LocationManager::instance()->getLocationByName(getName());
 if ((getTrainDirection() & Location::EAST) > 0) {
  setTrainIconX(l->getTrainIconEast().x());
  setTrainIconY(l->getTrainIconEast().y());
 }
 if ((getTrainDirection() & Location::WEST) > 0) {
  setTrainIconX(l->getTrainIconWest().x());
  setTrainIconY(l->getTrainIconWest().y());
 }
 if ((getTrainDirection() & Location::NORTH) > 0) {
  setTrainIconX(l->getTrainIconNorth().x());
  setTrainIconY(l->getTrainIconNorth().y());
 }
 if ((getTrainDirection() & Location::SOUTH) > 0) {
  setTrainIconX(l->getTrainIconSouth().x());
  setTrainIconY(l->getTrainIconSouth().y());
 }
}

/*public*/ QPoint RouteLocation::getTrainIconCoordinates() {
 return QPoint(getTrainIconX(), getTrainIconY());
}

/*public*/ void RouteLocation::dispose() {
     if (_location != NULL) {
         //_location.removePropertyChangeListener(this);
      disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     firePropertyChange(DISPOSE, QVariant(), DISPOSE);
 }

 /**
  * Construct this Entry from XML. This member has to remain synchronized
  * with the detailed DTD in operations-config.xml
  *
  * @param e Consist XML element
  */
 /*public*/ RouteLocation::RouteLocation(QDomElement e)
 {
  common();
     // if (log->isDebugEnabled()) log->debug("ctor from element "+e);
     QString a;
     if ((a = e.attribute (Xml::ID)) != NULL) {
         _id = a;
     } else {
         log->warn("no id attribute in route location element when reading operations");
     }
     if ((a = e.attribute (Xml::LOCATION_ID)) != NULL) {
         _locationId = a;
         _location = LocationManager::instance()->getLocationById(a);
         if (_location != NULL)
         {
             //_location.addPropertyChangeListener(this);
          connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
     } // old way of storing a route location
     else if ((a = e.attribute (Xml::NAME)) != NULL) {
         _location = LocationManager::instance()->getLocationByName(a);
         if (_location != NULL) {
             //_location.addPropertyChangeListener(this);
          connect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
         // force rewrite of route file
         RouteManagerXml::instance()->setDirty(true);
     }
     if ((a = e.attribute (Xml::TRAIN_DIRECTION)) != NULL) {
         // early releases had text for train direction
         if (Setup::getTrainDirectionList().contains(a)) {
             _trainDir = Setup::getDirectionInt(a);
             log->debug(tr("found old train direction %1 new direction $2").arg(a).arg(_trainDir));
         } else {
             try {
                 _trainDir = a.toInt();
             } catch (NumberFormatException ee) {
                 log->error(tr("Route location (%1) direction (%2) is unknown").arg(getName()).arg(a));
             }
         }
     }
     if ((a = e.attribute (Xml::MAX_TRAIN_LENGTH)) != NULL) {
         try {
             _maxTrainLength = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) maximum train length (%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::GRADE)) != NULL) {
         try {
             _grade = (a.toDouble());
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) grade ({%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::MAX_CAR_MOVES)) != NULL) {
         try {
             _maxCarMoves = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) maximum car moves (%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::RANDOM_CONTROL)) != NULL) {
         _randomControl = a;
     }
     if ((a = e.attribute (Xml::PICKUPS)) != NULL) {
         _pickups = a==(Xml::YES);
     }
     if ((a = e.attribute (Xml::DROPS)) != NULL) {
         _drops = a==(Xml::YES);
     }
     if ((a = e.attribute (Xml::WAIT)) != NULL) {
         try {
             _wait = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) wait (%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::DEPART_TIME)) != NULL) {
         _departureTime = a;
     }
     if ((a = e.attribute (Xml::TRAIN_ICON_X)) != NULL) {
         try {
             _trainIconX = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) icon x (%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::TRAIN_ICON_Y)) != NULL) {
         try {
             _trainIconY = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) icon y (%2) isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::SEQUENCE_ID)) != NULL) {
         try {
             _sequenceId = a.toInt();
         } catch (NumberFormatException ee) {
             log->error(tr("Route location (%1) sequence id %2 isn't a valid number").arg(getName()).arg(a));
         }
     }
     if ((a = e.attribute (Xml::COMMENT)) != NULL) {
         _comment = OperationsXml::convertFromXmlComment(a);
     }
 }

 /**
  * Create an XML element to represent this Entry. This member has to remain
  * synchronized with the detailed DTD in operations-config.xml.
  *
  * @return Contents in a JDOM Element
  */
 /*public*/ QDomElement RouteLocation::store(QDomDocument doc) {
     //QDomElement e = new Element(Xml::LOCATION);
QDomElement e = doc.createElement(Xml::LOCATION);
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::NAME, getName());
     e.setAttribute(Xml::LOCATION_ID, getNameId());
     e.setAttribute(Xml::SEQUENCE_ID, QString::number(getSequenceId()));
     e.setAttribute(Xml::TRAIN_DIRECTION, QString::number(getTrainDirection()));
     e.setAttribute(Xml::MAX_TRAIN_LENGTH, QString::number(getMaxTrainLength()));
     e.setAttribute(Xml::GRADE, QString::number(getGrade()));
     e.setAttribute(Xml::MAX_CAR_MOVES, QString::number(getMaxCarMoves()));
     e.setAttribute(Xml::RANDOM_CONTROL, getRandomControl());
     e.setAttribute(Xml::PICKUPS, isPickUpAllowed() ? Xml::YES : Xml::NO);
     e.setAttribute(Xml::DROPS, isDropAllowed() ? Xml::YES : Xml::NO);
     e.setAttribute(Xml::WAIT, QString::number(getWait()));
     e.setAttribute(Xml::DEPART_TIME, getDepartureTime());
     e.setAttribute(Xml::TRAIN_ICON_X, QString::number(getTrainIconX()));
     e.setAttribute(Xml::TRAIN_ICON_Y, QString::number(getTrainIconY()));
     e.setAttribute(Xml::COMMENT, getComment());

     return e;
 }

 /*public*/ void RouteLocation::propertyChange(PropertyChangeEvent* e) {
     if (Control::showProperty) {
         log->debug(tr("Property change: (%1) old: (%2 new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::DISPOSE_CHANGED_PROPERTY)) {
         if (_location != NULL) {
             //_location.removePropertyChangeListener(this);
          disconnect(_location->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
         _location = NULL;
     }
     // forward property name change
     if (e->getPropertyName()==(Location::NAME_CHANGED_PROPERTY)) {
         firePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
     }
 }

#if 0
 /*public*/ synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*/ synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
#endif
 /*protected*/ void RouteLocation::firePropertyChange(QString p, QVariant old, QVariant n) {
     pcs->firePropertyChange(p, old, n);
 }

 /*protected*/ void RouteLocation::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     RouteManagerXml::instance()->setDirty(true);
     firePropertyChange(p, old, n);
 }


} // end Operations
