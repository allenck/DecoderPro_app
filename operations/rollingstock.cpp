#include "rollingstock.h"
#include <QDate>
#include "setup.h"
#include "logger.h"
#include "locationmanager.h"
#include "routelocation.h"
#include "xml.h"
#include "location.h"
#include "track.h"
#include "train.h"
#include "rosterentry.h"
#include "route.h"
#include "traincommon.h"
#include "trainmanager.h"
#include "idtag.h"
#include "abstractidtag.h"
#include "instancemanager.h"
#include "idtagmanager.h"
#include "carroads.h"
#include <QtXml>
#include "carcolors.h"
#include "carowners.h"

//RollingStock::RollingStock(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations
{
/**
 * Represents rolling stock, both powered (locomotives) and not powered (cars)
 * on the layout.
 *
 * @author Daniel Boudreau Copyright (C) 2009, 2010, 2013
 * @version $Revision: 29598 $
 */
///*public*/ class RollingStock implements java.beans.PropertyChangeListener {
 /*public*/ /*static*/ /*final*/ QString RollingStock::NONE = "";
 /*public static final*/ int RollingStock::DEFAULT_BLOCKING_ORDER = 0;
 /*public static final*/ bool RollingStock::FORCE = true; // ignore length, type, etc. when setting car's track/*protected*/ /*static*/ /*final*/ QString RollingStock::DEFAULT_WEIGHT = "0";


 /*public*/ /*static*/ /*final*/ QString RollingStock::LOCATION_UNKNOWN = "0";


 /*public*/ /*static*/ /*final*/ QString RollingStock::ERROR_TRACK = "ERROR wrong track for location"; // NOI18N checks for coding error

 /*public*/ /*static*/ /*final*/ QString RollingStock::LOCATION_CHANGED_PROPERTY = "rolling stock location"; // NOI18N property change
 // descriptions
 /*public*/ /*static*/ /*final*/ QString RollingStock::TRACK_CHANGED_PROPERTY = "rolling stock track location"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::DESTINATION_CHANGED_PROPERTY = "rolling stock destination"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::DESTINATION_TRACK_CHANGED_PROPERTY = "rolling stock track destination"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::TRAIN_CHANGED_PROPERTY = "rolling stock train"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::LENGTH_CHANGED_PROPERTY = "rolling stock length"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::TYPE_CHANGED_PROPERTY = "rolling stock type"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::ROUTE_LOCATION_CHANGED_PROPERTY = "rolling stock route location"; // NOI18N
 /*public*/ /*static*/ /*final*/ QString RollingStock::ROUTE_DESTINATION_CHANGED_PROPERTY = "rolling stock route destination"; // NOI18N

 // the draw bar length must only be calculated once at startup
/*public*/ /*static*/ /*final*/ int RollingStock::COUPLER = (Setup::getLengthUnit()==/*(Setup::FEET)*/tr("feet") ? 4 :1); // stocks

/*protected*/ /*static*/ /*final*/ QString RollingStock::DEFAULT_WEIGHT = "0";

/*public*/ RollingStock::RollingStock(QObject *parent) :
 PropertyChangeSupport(this, parent) {
common();
 _lastDate = QDateTime(); //(new GregorianCalendar()).getGregorianChange(); // set to change date of the Gregorian Calendar.
}

/*public*/ RollingStock::RollingStock(QString road, QString number, QObject *parent) :
 PropertyChangeSupport(this, parent)
{
 //this();
common();
 if(log->isDebugEnabled()) log->debug(tr("New rolling stock (%1 %2)").arg(road).arg(number));
 _road = road;
 _number = number;
 _id = createId(road, number);
  addPropertyChangeListeners();
}
void RollingStock::common()
{
log = new Logger("RollingStocK");
setObjectName("RollingStock");
locationManager = ((LocationManager*)InstanceManager::getDefault("LocationManager"));
_id = NONE;
_number = NONE;
_road = NONE;
_type = NONE;
_length = NONE;
_color = NONE;
_weight = DEFAULT_WEIGHT;
_weightTons = DEFAULT_WEIGHT;
_built = NONE;
_owner = NONE;
_comment = NONE;
_routeId = NONE; // saved route for interchange tracks
_rfid = NONE;
_value = NONE;
_last = NONE;
_lastDate = QDateTime();
_locationUnknown = false;
_outOfService = false;
_selected = false;

_location = NULL;
_trackLocation= NULL;
_destination = NULL;
_trackDestination = NULL;
_train = NULL;
_routeLocation = NULL;
_routeDestination = NULL;
_moves = 0;
_lastLocationId = LOCATION_UNKNOWN; // the rollingstock's last location id
_blocking = 0;
number = 0; // used by rolling stock manager for sort by number
_lengthChange = false; // used for loco length change
verboseStore = false;
_tag = NULL;
_tagListener = NULL;
}

/*public*/ /*static*/ QString RollingStock::createId(QString road, QString number) {
 QString id = road + number;
 return id;
}

/*public*/ QString RollingStock::getId() {
  return _id;
}

/**
* Set the rolling stock identification or road number
*
* @param number
*/
/*public*/ void RollingStock::setNumber(QString number) {
  QString old = _number;
  _number = number;
  if (old!=(number)) {
      setDirtyAndFirePropertyChange("rolling stock number", old, number); // NOI18N
  }
}

/*public*/ QString RollingStock::getNumber() {
  return _number;
}

/*public*/ void RollingStock::setRoadName(QString road) {
  QString old = _road;
  _road = road;
  if (old!=(road)) {
      setDirtyAndFirePropertyChange("rolling stock road", old, road); // NOI18N
  }
}

/*public*/QString RollingStock::getRoadName() {
  return _road;
}

/**
* For combobox and identification
*/
/*public*/ QString RollingStock::toString() {
  return getRoadName() + " " + getNumber();
}

/**
* Sets the type of rolling stock. "Boxcar" for example is a type of car.
*
* @param type The type of rolling stock.
*/
/*public*/ void RollingStock::setTypeName(QString type) {
  QString old = _type;
  _type = type;
  if (old!=(type)) {
      setDirtyAndFirePropertyChange("rolling stock type", old, type); // NOI18N
  }
}

/*public*/ QString RollingStock::getTypeName() {
  return _type;
}

//@Deprecated
// saved for scripts
/*public*/ QString RollingStock::getType() {
  return getTypeName();
}


/*
* Sets the length of the rolling stock.
*
* @param length
*/
/*public*/ void RollingStock::setLength(QString length)
{
QString old = _length;
if (old!=(length))
{
// adjust used length if rolling stock is at a location
if (_location != NULL && _trackLocation != NULL)
{
     _location->setUsedLength( _location->getUsedLength() + length.toInt() - old.toInt());
     _trackLocation->setUsedLength( _trackLocation->getUsedLength() + length.toInt()
            - old.toInt());
    if (_destination != NULL && _trackDestination != NULL && !_lengthChange) {
        _lengthChange = true; // prevent recursive loop, and we want the "old" loco length
        if(log->isDebugEnabled()) log->debug(tr("Rolling stock (%1) has destination (%2, %3)").arg(toString()).arg(_destination->getName()).arg(
                _trackDestination->getName()));
         _trackLocation->deletePickupRS(this);
        _trackDestination->deleteDropRS(this);
        // now change the length and update tracks
        _length = length;
         _trackLocation->addPickupRS(this);
        _trackDestination->addDropRS(this);
        _lengthChange = false; // done
    }
}
_length = length;
setDirtyAndFirePropertyChange(LENGTH_CHANGED_PROPERTY, old, length);
}
}

/*public*/ QString RollingStock::getLength() {
  return _length;
}

/*public*/ int RollingStock::getLengthInteger() {
  //try {
return getLength().toInt();
//     } catch (Exception e) {
//         log->error("Rolling stock ({}) length ({}) is not valid ", toString(), getLength());
//     }
  return 0;
}
/**
* Returns the length of the rolling stock including the couplers
*
* @return total length of the rolling stock
*/
/*public*/ int RollingStock::getTotalLength() {
  return getLengthInteger() + RollingStock::COUPLER;
}

/*public*/ void RollingStock::setColor(QString color) {
  QString old = _color;
  _color = color;
  if (old!=(color)) {
      setDirtyAndFirePropertyChange("rolling stock color", old, color); // NOI18N
  }
}

/*public*/ QString RollingStock::getColor() {
  return _color;
}

 /**
  *
  * @param weight rolling stock weight in ounces.
  */
 /*public*/ void RollingStock::setWeight(QString weight) {
     QString old = _weight;
     _weight = weight;
     if (old!=(weight)) {
         setDirtyAndFirePropertyChange("rolling stock weight", old, weight); // NOI18N
     }
 }

 /*public*/ QString RollingStock::getWeight() {
     return _weight;
 }

 /**
  * Sets the full scale weight in tons.
  *
  * @param weight full scale rolling stock weight in tons.
  */
 /*public*/ void RollingStock::setWeightTons(QString weight) {
     QString old = _weightTons;
     _weightTons = weight;
     if (old!=(weight)) {
         setDirtyAndFirePropertyChange("rolling stock weight tons", old, weight); // NOI18N
     }
 }

 /*public*/ QString RollingStock::getWeightTons() {
     if (_weightTons!=(DEFAULT_WEIGHT)) {
         return _weightTons;
     }

     double weight = 0;
     try {
         weight = getWeight().toDouble();
     } catch (Exception e) {
         // log->debug("Weight not set for rolling stock ("+toString()+")");
     }
     return QString::number((int) (weight * Setup::getScaleTonRatio()));
 }

 /*public*/ int RollingStock::getAdjustedWeightTons() {
     int weightTons = 0;
     try {
         // get loaded weight
         weightTons = getWeightTons().toInt();
     } catch (Exception e) {
         log->debug(tr("Rolling stock (%1) weight not set").arg(toString()));
     }
     return weightTons;
 }

 /**
  * Set the date that the rolling stock was built. Use 4 digits for the year,
  * or the format MM-YY where MM is the two digit month, and YY is the last
  * two years if the rolling stock was built in the 1900s. Use MM-YYYY for
  * units build after 1999.
  *
  * @param built
  */
 /*public*/ void RollingStock::setBuilt(QString built) {
     QString old = _built;
     _built = built;
     if (old!=(built)) {
         setDirtyAndFirePropertyChange("rolling stock built", old, built); // NOI18N
     }
 }

 /*public*/ QString RollingStock::getBuilt() {
     return _built;
 }

 /**
  *
  * @return location unknown symbol, out of service symbol, or none if car
  *         okay
  */
 /*public*/ QString RollingStock::getStatus() {
     return (isLocationUnknown() ? "<?> " : (isOutOfService() ? "<O> " : NONE)); // NOI18N
 }

/*public*/ Location* RollingStock::getLocation() {
  return _location;
}


 /**
  * Get rolling stock's location name
  *
  * @return empty string if rolling stock isn't on layout
  */
 /*public*/ QString RollingStock::getLocationName() {
     if (_location != NULL) {
         return  _location->getName();
     }
     return NONE;
 }

 /**
  * Get rolling stock's location id
  *
  * @return empty string if rolling stock isn't on the layout
  */
 /*public*/ QString RollingStock::getLocationId() {
     if (_location != NULL) {
         return  _location->getId();
     }
     return NONE;
 }

 /*public*/ Track* RollingStock::getTrack() {
     return _trackLocation;
 }

 /**
  * Set the rolling stock's location and track. Doesn't do any checking and
  * does not fire a property change. Used exclusively by the Router code. Use
  * setLocation(Location, Track) instead.
  *
  * @param track to place the rolling stock on.
  */
 /*public*/ void RollingStock::setTrack(Track* track) {
     if (track != NULL) {
         _location = track->getLocation();
     }
     _trackLocation = track;
 }

 /**
  * Get rolling stock's track name
  *
  * @return empty string if rolling stock isn't on a track
  */
 /*public*/ QString RollingStock::getTrackName()
 {
     if (_trackLocation != NULL) {
         return  _trackLocation->getName();
     }
     return NONE;
 }

 /**
  * Get rolling stock's track id
  *
  * @return empty string if rolling stock isn't on a track
  */
 /*public*/ QString RollingStock::getTrackId() {
     if (_trackLocation != NULL) {
         return  _trackLocation->getId();
     }
     return NONE;
 }

/**
* Sets rolling stock location on the layout
*
* @param location
* @param track (yard, spur, staging, or interchange track)
*
* @return "okay" if successful, "type" if the rolling stock's type isn't
*         acceptable, or "length" if the rolling stock length didn't fit.
*/
/*public*/QString RollingStock::setLocation(Location* location, Track* track) {
  return setLocation(location, track, false);
}

 /**
 * Sets rolling stock location on the layout
 *
 * @param location
 * @param track (yard, spur, staging, or interchange track)
 * @param force when true place rolling stock ignore track length, type, &
 *            road
 * @return "okay" if successful, "type" if the rolling stock's type isn't
 *         acceptable, "road" if rolling stock road isn't acceptable, or
 *         "length" if the rolling stock length didn't fit.
 */
 /*public*/ QString RollingStock::setLocation(Location* location, Track* track, bool force)
 {
  // first determine if rolling stock can be move to the new location
  if (!force)
  {
   QString status = testLocation(location, track);
   if (status!=(Track::OKAY))
   {
     return status;
   }
  }
  // now update
  Location* oldLocation = _location;
  _location = location;
  Track* oldTrack = _trackLocation;
  _trackLocation = track;

  if (oldLocation != location || oldTrack != track)
  {
  // update rolling stock location on layout, maybe this should be a property change?
  // first remove rolling stock from existing location
  if (oldLocation != NULL)
  {
   oldLocation->deleteRS(this);
   oldLocation->removePropertyChangeListener(this);
   // if track is NULL, then rolling stock is in a train
   if (oldTrack != NULL)
   {
    oldTrack->deleteRS(this);
    oldTrack->removePropertyChangeListener(this);
    // if there's a destination then pickup complete
    if (_destination != NULL)
    {
     oldLocation->deletePickupRS();
     oldTrack->deletePickupRS(this);
     // don't update rs's previous location if just re-staging
     if (getTrain() != NULL && getTrain()->getRoute() != NULL && getTrain()->getRoute()->size() > 2)
     {
        setLastLocationId(oldLocation->getId());
     }
    }
   }
  }
  if (_location != NULL)
  {
   _location->addRS(this);
   // Need to know if location name changes so we can forward to listeners
  _location->PropertyChangeSupport::addPropertyChangeListener(this);
  }
  if (_trackLocation != NULL)
  {
   _trackLocation->addRS(this);
   // Need to know if location name changes so we can forward to listeners
   _trackLocation->PropertyChangeSupport::addPropertyChangeListener(this);
   // if there's a destination then there's a pick up
   if (_destination != NULL)
   {
       _location->addPickupRS();
       _trackLocation->addPickupRS(this);
    }
   }
   setDirtyAndFirePropertyChange(LOCATION_CHANGED_PROPERTY, VPtr<Location>::asQVariant(oldLocation), VPtr<Location>::asQVariant(location));
   setDirtyAndFirePropertyChange(TRACK_CHANGED_PROPERTY, VPtr<Track>::asQVariant(oldTrack), VPtr<Track>::asQVariant(track));
  }
  return Track::OKAY;
 }

 /*public*/ QString RollingStock::testLocation(Location* location, Track* track) {
  if (track == NULL) {
      return Track::OKAY;
  }
  if (location != NULL && !location->isTrackAtLocation(track)) {
      return ERROR_TRACK;
  }
  return track->accepts(this);
}

/**
* Sets rolling stock destination on the layout
*
* @param destination
* @param track (yard, spur, staging, or interchange track)
* @return "okay" if successful, "type" if the rolling stock's type isn't
*         acceptable, or "length" if the rolling stock length didn't fit.
*/
/*public*/ QString RollingStock::setDestination(Location* destination, Track* track) {
  return setDestination(destination, track, false);
}

/**
* Sets rolling stock destination on the layout
*
* @param destination
* @param track (yard, spur, staging, or interchange track)
* @param force when true ignore track length, type, & road when setting
*            destination
* @return "okay" if successful, "type" if the rolling stock's type isn't
*         acceptable, or "length" if the rolling stock length didn't fit.
*/
/*public*/ QString RollingStock::setDestination(Location* destination, Track* track, bool force) {
  // first determine if rolling stock can be move to the new destination
  if (!force) {
      QString status = rsTestDestination(destination, track);
      if (status!=(Track::OKAY)) {
          return status;
      }
  }
  // now set the rolling stock destination!
  Location* oldDestination = _destination;
  _destination = destination;
  Track* oldTrack = _trackDestination;
  _trackDestination = track;

  if (oldDestination != destination || oldTrack != track) {
      if (oldDestination != NULL)
      {
          oldDestination->deleteDropRS();
          //oldDestination->removePropertyChangeListener(this);
          disconnect(oldDestination, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
          // delete pick up in case destination is NULL
          if (_location != NULL && _trackLocation != NULL) {
               _location->deletePickupRS();
               _trackLocation->deletePickupRS(this);
          }
      }
      if (oldTrack != NULL) {
          oldTrack->deleteDropRS(this);
          //oldTrack::removePropertyChangeListener(this);
          disconnect(oldTrack, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
      }
      if (_destination != NULL) {
          _destination->addDropRS();
          if (_location != NULL && _trackLocation != NULL) {
               _location->addPickupRS();
               _trackLocation->addPickupRS(this);
          }

          // Need to know if destination name changes so we can forward to listeners
          //_destination.addPropertyChangeListener(this);
          connect(_destination, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
      }
      if (_trackDestination != NULL) {
          _trackDestination->addDropRS(this);
          // Need to know if destination name changes so we can forward to listeners
          //_trackDestination.addPropertyChangeListener(this);
          connect(_trackDestination, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
      } else {
          // rolling stock has been terminated or reset, bump rolling stock moves
          if (getTrain() != NULL && getTrain()->getRoute() != NULL) {
              setLastRouteId(getTrain()->getRoute()->getId());
          }
          if (getRouteDestination() != NULL) {
              setMoves(getMoves() + 1);
              setLastDate(TrainCommon::getDate(false));
          }
          setRouteLocation(NULL);
          setRouteDestination(NULL);
      }

      setDirtyAndFirePropertyChange(DESTINATION_CHANGED_PROPERTY, VPtr<Location>::asQVariant(oldDestination), VPtr<Location>::asQVariant(destination));
      setDirtyAndFirePropertyChange(DESTINATION_TRACK_CHANGED_PROPERTY, VPtr<Track>::asQVariant(oldTrack), VPtr<Track>::asQVariant(track));
  }
  return Track::OKAY;
}

/**
* Used to check destination track to see if it will accept rolling stock
*
* @param destination
* @param track
* @return status OKAY, TYPE, ROAD, LENGTH, ERROR_TRACK
*/
/*public*/ QString RollingStock::testDestination(Location* destination, Track* track) {
  return rsTestDestination(destination, track);
}

/*private*/ QString RollingStock::rsTestDestination(Location* destination, Track* track) {
  // first perform a code check
  if (destination != NULL && !destination->isTrackAtLocation(track)) {
      return ERROR_TRACK;
  }
  if (destination != NULL && !destination->acceptsTypeName(getTypeName())) {
      return Track::TYPE + " (" + getTypeName() + ")";
  }
  if (destination == NULL || track == NULL) {
      return Track::OKAY;
  }
  return track->accepts(this);
}

/*public*/ Location* RollingStock::getDestination() {
  return _destination;
}

/**
* Sets rolling stock destination without reserving destination track space
* or drop count. Does not fire a property change. Used by car router to
* test destinations. Use setDestination(Location, Track) instead.
*
* @param destination for the rolling stock
*/
/*public*/ void RollingStock::setDestination(Location* destination) {
  _destination = destination;
}

/*public*/ QString RollingStock::getDestinationName() {
  if (_destination != NULL) {
      return _destination->getName();
  }
  return NONE;
}

/*public*/ QString RollingStock::getDestinationId() {
  if (_destination != NULL) {
      return _destination->getId();
  }
  return NONE;
}

/**
* Sets rolling stock destination track without reserving destination track
* space or drop count. Used by car router to test destinations. Does not
* fire a property change. Use setDestination(Location, Track) instead.
*
* @param track
*/
/*public*/ void RollingStock::setDestinationTrack(Track* track) {
  if (track != NULL) {
      _destination = track->getLocation();
  }
  _trackDestination = track;
}

/*public*/ Track* RollingStock::getDestinationTrack() {
  return _trackDestination;
}

/*public*/ QString RollingStock::getDestinationTrackName() {
  if (_trackDestination != NULL) {
      return _trackDestination->getName();
  }
  return NONE;
}

/*public*/ QString RollingStock::getDestinationTrackId() {
  if (_trackDestination != NULL) {
      return _trackDestination->getId();
  }
  return NONE;
}

/**
* Used to block cars from staging
*
* @param id The location id from where the car came from before going into
*            staging.
*/
/*public*/ void RollingStock::setLastLocationId(QString id) {
  _lastLocationId = id;
}

/*public*/ QString RollingStock::getLastLocationId() {
  return _lastLocationId;
}

/*public*/ void RollingStock::setMoves(int moves) {
  int old = _moves;
  _moves = moves;
  if (old != moves) {
      setDirtyAndFirePropertyChange("rolling stock moves", (old), // NOI18N
              (moves));
  }
}

/*public*/ int RollingStock::getMoves() {
  return _moves;
}
 /**
  * Sets the train that will service this rolling stock.
  *
  * @param train
  */
 /*public*/ void RollingStock::setTrain(Train* train) {
     Train* old = _train;
     _train = train;
     if ((old != NULL && old!=(train)) || old != train) {
         if (old != NULL) {
             //old.removePropertyChangeListener(this);
          disconnect(old, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
         }
         if (train != NULL) {
             //train.addPropertyChangeListener(this);
          connect(train, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
       }
         setDirtyAndFirePropertyChange(TRAIN_CHANGED_PROPERTY, VPtr<Train>::asQVariant(old), VPtr<Train>::asQVariant(train));
     }
 }
 /*public*/ Train* RollingStock::getTrain() {
     return _train;
 }

 /*public*/ QString RollingStock::getTrainName() {
     if (getTrain() != NULL) {
         return getTrain()->getName();
     }
     return NONE;
 }

 /**
  * Sets the location where the rolling stock will be picked up by the train.
  *
  * @param routeLocation the pick up location for this rolling stock.
  */
 /*public*/ void RollingStock::setRouteLocation(RouteLocation* routeLocation) {
     // a couple of error checks before setting the route location
     if (_location == NULL && routeLocation != NULL) {
         if(log->isDebugEnabled()) log->debug(tr("WARNING rolling stock (%1) does not have an assigned location").arg(toString())); // NOI18N
     } else if (routeLocation != NULL && _location != NULL && routeLocation->getName()!=( _location->getName())) {
      log->error(tr("ERROR route location name(%1) not equal to location name (%2) for rolling stock (%3)").arg(
                 routeLocation->getName()).arg(_location->getName()).arg(toString())); // NOI18N
     }
     RouteLocation* old = _routeLocation;
     _routeLocation = routeLocation;
     if (old != routeLocation) {
         setDirtyAndFirePropertyChange(ROUTE_LOCATION_CHANGED_PROPERTY, VPtr<RouteLocation>::asQVariant(old), VPtr<RouteLocation>::asQVariant(routeLocation));
     }
 }

/*public*/ RouteLocation* RollingStock::getRouteLocation() {
  return _routeLocation;
}

/*public*/ QString RollingStock::getRouteLocationId() {
  if (_routeLocation != NULL) {
      return _routeLocation->getId();
  }
  return NONE;
}

/*public*/ QString RollingStock::getSavedRouteId() {
  return _routeId;
}

/**
* Sets the id of the route that was used to set out the rolling stock. Used
* to determine if the rolling stock can be pick ups from an interchange
* track.
*
* @param id The route id.
*/
/*public*/ void RollingStock::setLastRouteId(QString id) {
  _routeId = id;
}

/*public*/ QString RollingStock::getValue() {
  return _value;
}

 /**
  * Sets the value (cost, price) for this rolling stock. Currently has
  * nothing to do with operations. But nice to have.
  *
  * @param value a string representing what this item is worth.
  */
 /*public*/ void RollingStock::setValue(QString value) {
     QString old = _value;
     _value = value;
     if (old!=(value)) {
         setDirtyAndFirePropertyChange("rolling stock value", old, value); // NOI18N
     }
 }


 /*public*/ QString RollingStock::getRfid() {
     return _rfid;
 }

 /*public*/ DefaultIdTag *RollingStock::getIdTag() {
     return _tag;
 }

 /*public*/ void RollingStock::setIdTag(DefaultIdTag* tag)
{
     if (_tag != NULL)
     {
         //_tag.removePropertyChangeListener(_tagListener);
      disconnect(((AbstractIdTag*)_tag->self()), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
     _tag = tag;
     if (_tagListener == NULL) {
         // store the tag listener so we can reuse it and
         // dispose of it as necessary.
//            _tagListener = new PropertyChangeListener() {
//                //@Override
//                /*public*/ void propertyChange(PropertyChangeEvent e) {
//                    if (e.getPropertyName()==("whereLastSeen")) {
//                        log->debug("Tag Reader Position update received for {}", toString());
//                        // update the position of this piece of rolling
//                        // stock when it's IdTag is seen, but only if
//                        // the actual location changes.
//                        if (e.getNewValue() != NULL) {
//                            Location* newLocation = locationManager.getLocationByReporter((jmri.Reporter) e.getNewValue());
//                            if (newLocation != getLocation())
//                                setLocation(newLocation, NULL);
//                        }
//                    }
//                    if (e.getPropertyName()==("whenLastSeen")) {
//                        log->debug("Tag Reader Time at Location update received for {}", toString());
//                        // update the time when this car was last moved
//                        // stock when it's IdTag is seen, but only if
//                        // the actual location changes.
//                        if (e.getNewValue() != NULL) {
//                            Date newDate = ((Date) e.getNewValue());
//                            setLastDate(newDate);
//                        }
//                    }
//                }
//            };
      _tagListener = new IdTagPropertyChangeListener(this);
     }
     if (_tag != NULL)
         //_tag.addPropertyChangeListener(_tagListener);
      connect(((AbstractIdTag*)_tag->self()), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

 }
IdTagPropertyChangeListener::IdTagPropertyChangeListener(RollingStock* parent) { this->parent = parent ;}

/*public*/ void IdTagPropertyChangeListener::propertyChange(PropertyChangeEvent* e) {
  if (e->getPropertyName()==("whereLastSeen")) {
      parent->log->debug(tr("Tag Reader Position update received for %1").arg(parent->toString()));
      // update the position of this piece of rolling
      // stock when it's IdTag is seen, but only if
      // the actual location changes.
      if (e->getNewValue() != QVariant()) {
          Location* newLocation = parent->locationManager->getLocationByReporter(VPtr<Reporter>::asPtr(e->getNewValue()));
          if (newLocation != parent->getLocation())
              parent->setLocation(newLocation, NULL);
      }
  }
  if (e->getPropertyName()==("whenLastSeen")) {
      parent->log->debug(tr("Tag Reader Time at Location update received for %1").arg(parent->toString()));
      // update the time when this car was last moved
      // stock when it's IdTag is seen, but only if
      // the actual location changes.
      if (e->getNewValue() != QVariant()) {
          QString newDate =  e->getNewValue().toDateTime().toString("MM/dd/yyyy HH:mm:ss");
          parent->setLastDate(newDate);
      }
  }
}

 /**
  * Sets the RFID for this rolling stock.
  *
  * @param id 12 character RFID string.
  */
 /*public*/ void RollingStock::setRfid(QString id) {

     QString old = _rfid;
     _rfid = id;
     if(log->isDebugEnabled()) log->debug(tr("Changing IdTag for %1 to %1").arg(toString()).arg(id));
     if (old!=(id))
         setDirtyAndFirePropertyChange("rolling stock rfid", old, id); // NOI18N
     try {
      DefaultIdTag* tag = ((IdTagManager*)InstanceManager::getDefault("IdTagManager"))->getIdTag(id.toUpper());
         if(log->isDebugEnabled()) log->debug(tr("Tag %1 Found").arg(tag->toString()));
         setIdTag(tag);
     } catch (NullPointerException e) {
         log->error(tr("Tag %1 Not Found").arg(id));
     }
 }

 /**
  * Provides the last date when this rolling stock was moved, or was reset
  * from a built train, as a string.
  *
  * @return date
  */
 /*public*/ QString RollingStock::getLastDate() {
#if 0 // TODO:
     if (_lastDate==((new GregorianCalendar()).getGregorianChange()))
         return NONE; // return an empty string for the default date.
     SimpleDateFormat format =
             new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
     return format.format(_lastDate);
#else
return "";
#endif
 }

 /**
  * Provides the last date when this rolling stock was moved, or was reset
  * from a built train.
  *
  * @return date
  */
 /*public*/ QDateTime RollingStock::getLastMoveDate() {
     return _lastDate;
 }

 /**
  * Sets the last date when this rolling stock was moved, or was reset from a
  * built train.
  *
  * @param date
  * @deprecated This method will become a private method, used only for
  *             loading data from a file, in the future. Use
  *             setLastDate(Date) instead.
  */
 //@Deprecated
 /*public*/ void RollingStock::setLastDate(QString date)
 {
#if 1
     if (date == NONE)
         return; // there was no date specified.
     QString old = _last;
     QDateTime oldDate = _lastDate;
     _last = date;
     if (old!=(date)) {
         setDirtyAndFirePropertyChange("rolling stock date", old, date); // NOI18N
     }
     // create a date object from the value.
//     try {
         // try the new format (with seconds).
//         SimpleDateFormat formatter =
////                 new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
//         _lastDate = formatter.parse(_last);
     _lastDate = QDateTime::fromString(_last, "MM/dd/yyyy HH:mm:ss");

     if(!_lastDate.isValid())
     {
         // try the old 12 hour format (no seconds).
//         try {
//             SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy hh:mmaa");
//             _lastDate = formatter.parse(_last);
      _lastDate = QDateTime::fromString(_last, "MM/dd/yyyy HH:mmaa");

      if(!_lastDate.isValid())
      {
//             try {
                 // try 24hour clock.
//                 SimpleDateFormat formatter = new SimpleDateFormat("MM/dd/yyyy HH:mm");
//                 _lastDate = formatter.parse(_last);
       _lastDate = QDateTime::fromString(_last, "MM/dd/yyyy HH:mm");
       if(!_lastDate.isValid())
       {
        log->warn(tr("Not able to parse date: %1 for rolling stock (%2)").arg(_last).arg(toString()));
                 _lastDate = oldDate; // set the date back to what it was before
       }
      }
     }
#endif
 }

 /**
  * Sets the last date when this rolling stock was moved, or was reset from a
  * built train.
  *
  * @param date
  */
 /*public*/ void RollingStock::setLastDate(QDateTime date) {
     QDateTime old = _lastDate;
     _lastDate = date;
     if (old!=(_lastDate)) {
         setDirtyAndFirePropertyChange("rolling stock date", old, date); // NOI18N
     }
 }

 /*public*/ void RollingStock::setBlocking(int number) {
     int old = _blocking;
     _blocking = number;
     if (old != number) {
         setDirtyAndFirePropertyChange("rolling stock blocking changed", old, number); // NOI18N
     }
 }

 /*public*/ int RollingStock::getBlocking() {
     return _blocking;
 }

 /**
  * Set where in a train's route this rolling stock will be set out.
  *
  * @param routeDestination the location where the rolling stock is to leave
  *            the train.
  */
 /*public*/ void RollingStock::setRouteDestination(RouteLocation* routeDestination) {
     if (routeDestination != NULL && _destination != NULL
             && routeDestination->getName()!=(_destination->getName()))
     {
      log->warn(tr("WARNING route destination name (%1) not equal to destination name (%2) for rolling stock (%3)").arg(
                 routeDestination->getName()).arg(_destination->getName()).arg(toString())); // NOI18N
     }
     RouteLocation* old = _routeDestination;
     _routeDestination = routeDestination;
     if (old != routeDestination) {
         setDirtyAndFirePropertyChange(ROUTE_DESTINATION_CHANGED_PROPERTY, VPtr<RouteLocation>::asQVariant(old), VPtr<RouteLocation>::asQVariant(routeDestination));
     }
 }

 /*public*/ RouteLocation* RollingStock::getRouteDestination() {
     return _routeDestination;
 }

 /*public*/ QString RollingStock::getRouteDestinationId() {
     if (_routeDestination != NULL) {
         return _routeDestination->getId();
     }
     return NONE;
 }

/*public*/ void RollingStock::setOwner(QString owner) {
     QString old = _owner;
     _owner = owner;
     if (old!=(owner)) {
         setDirtyAndFirePropertyChange("rolling stock owner", old, owner); // NOI18N
     }
 }

 /*public*/ QString RollingStock::getOwner() {
     return _owner;
 }

 /**
  * Set the rolling stock location as unknown.
  *
  * @param unknown when true, the rolling stock location is unknown.
  */
 /*public*/ void RollingStock::setLocationUnknown(bool unknown) {
     bool old = _locationUnknown;
     _locationUnknown = unknown;
     if (!old == unknown) {
         setDirtyAndFirePropertyChange("car location known", old ? "true" : "false", unknown ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /**
  *
  * @return true when car's location is unknown
  */
 /*public*/ bool RollingStock::isLocationUnknown() {
     return _locationUnknown;
 }

 /**
  * Sets the rolling stock service state. When true, rolling stock is out of
  * service. Normal state is false, the rolling stock is in service and
  * available.
  *
  * @param outOfService when true, out of service
  */
 /*public*/ void RollingStock::setOutOfService(bool outOfService) {
     bool old = _outOfService;
     _outOfService = outOfService;
     if (!old == outOfService) {
         setDirtyAndFirePropertyChange("car out of service", old ? "true" : "false", outOfService ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /**
  *
  * @return true when rolling stock is out of service
  */
 /*public*/ bool RollingStock::isOutOfService() {
     return _outOfService;
 }

 /*public*/ void RollingStock::setSelected(bool selected) {
     bool old = _selected;
     _selected = selected;
     if (!old == selected) {
         setDirtyAndFirePropertyChange("selected", old ? "true" : "false", selected ? "true" // NOI18N
         : "false"); // NOI18N
     }
 }

 /**
  *
  * @return true when rolling stock is selected
  */
 /*public*/ bool RollingStock::isSelected() {
     return _selected;
 }

 // normally overridden
 /*public*/ QString RollingStock::getLoadPriority() {
     return NONE;
 }

 /*public*/ void RollingStock::setComment(QString comment) {
     QString old = _comment;
     _comment = comment;
     if (old!=(comment)) {
         setDirtyAndFirePropertyChange("rolling stock comment", old, comment); // NOI18N
     }
 }

 /*public*/ QString RollingStock::getComment() {
     return _comment;
 }

 /*protected*/ void RollingStock::moveRollingStock(RouteLocation* old, RouteLocation* next) {
     if (old == getRouteLocation()) {
         // Arriving at destination?
         if (getRouteLocation() == getRouteDestination() || next == NULL) {
             if (getRouteLocation() == getRouteDestination()) {
                 if(log->isDebugEnabled()) log->debug(tr("Rolling stock (%1) has arrived at destination (%2)").arg(toString()).arg(getDestination()->toString()));
             } else {
                 log->error(tr("Rolling stock (%1) has a NULL route location for next").arg(toString())); // NOI18N
             }
             setLocation(getDestination(), getDestinationTrack(), true); // force RS to destination
             setDestination(NULL, NULL); // this also clears the route locations
             setTrain(NULL); // this must come after setDestination (route id is set)
         } else {
          if(log->isDebugEnabled()) log->debug(tr("Rolling stock (%1) is in train (%2) leaves location (%3) destination (%4)").arg(toString()).arg(
                     getTrainName()).arg(old->getName()).arg(next->getName()));
             Location* nextLocation = locationManager->getLocationByName(next->getName());
             setLocation(nextLocation, NULL, true); // force RS to location
             setRouteLocation(next);
         }
     }
 }

 /*public*/ void RollingStock::reset() {
     // the order of the next two instructions is important, otherwise rs will have train's route id
     setTrain(NULL);
     setDestination(NULL, NULL);
 }

 /**
  * Remove rolling stock. Releases all listeners.
  */
 /*public*/ void RollingStock::dispose() {
     setTrain(NULL);
     setDestination(NULL, NULL);
     setLocation(NULL, NULL);
     //CarRoads::instance().removePropertyChangeListener(this);
     disconnect(((CarRoads*)InstanceManager::getDefault("CarRoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        CarOwners.instance().removePropertyChangeListener(this);
     disconnect(((CarOwners*)InstanceManager::getDefault("CarOwners")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
//        CarColors.instance().removePropertyChangeListener(this);
     disconnect(((CarColors*)InstanceManager::getDefault("CarColors")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     if (_tag != NULL) {
         //_tag.removePropertyChangeListener(_tagListener);
      disconnect(((AbstractIdTag*)_tag->self()), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     }
 }

 /**
  * Construct this Entry from XML.
  *
  * @param e RollingStock XML element
  */
 /*public*/ RollingStock::RollingStock(QDomElement e, QObject* parent)
 : PropertyChangeSupport(this, parent)
 {
     //this();
  common();
  if(log->isDebugEnabled()) log->debug("e = "+ e.tagName());
  QDomNamedNodeMap al = e.attributes();
   if(log->isDebugEnabled()) log->debug("attributes = " + QString::number(al.count()));
     QString a ="";
     if ((a = e.attribute (Xml::ID)) != NULL) {
         _id = a;
     } else {
         log->warn("no id attribute in rolling stock element when reading operations");
     }
     if ((a = e.attribute (Xml::ROAD_NUMBER)) != NULL) {
         _number = a;
     }
     if ((a = e.attribute (Xml::ROAD_NAME)) != NULL) {
         _road = a;
     }
     if ((a = e.attribute (Xml::TYPE)) != "") {
         _type = a;
     }
     if ((a = e.attribute (Xml::LENGTH)) != NULL) {
         _length = a;
     }
     if ((a = e.attribute (Xml::COLOR)) != NULL) {
         _color = a;
     }
     if ((a = e.attribute (Xml::WEIGHT)) != NULL) {
         _weight = a;
     }
     if ((a = e.attribute (Xml::WEIGHT_TONS)) != NULL) {
         _weightTons = a;
     }
     if ((a = e.attribute (Xml::BUILT)) != NULL) {
         _built = a;
     }

     Location* location = NULL;
     Track* track = NULL;
     if ((a = e.attribute (Xml::LOCATION_ID)) != NULL) {
         location = locationManager->getLocationById(a);
     }
     if ((a = e.attribute (Xml::SEC_LOCATION_ID)) != NULL && location != NULL) {
         track = location->getTrackById(a);
     }
     setLocation(location, track, true); // force location

     Location* destination = NULL;
     track = NULL;
     if ((a = e.attribute (Xml::DESTINATION_ID)) != NULL) {
         destination = locationManager->getLocationById(a);
     }
     if ((a = e.attribute (Xml::SEC_DESTINATION_ID)) != NULL && destination != NULL) {
         track = destination->getTrackById(a);
     }
     setDestination(destination, track, true); // force destination

     if ((a = e.attribute (Xml::MOVES)) != NULL) {
         try {
             _moves = a.toInt();
         } catch (NumberFormatException nfe) {
             log->error(tr("Move count (%1) for rollingstock (%2) isn't a valid number!").arg(a).arg(toString()));
         }
     }
     if ((a = e.attribute (Xml::LAST_LOCATION_ID)) != NULL) {
         _lastLocationId = a;
     }
     if ((a = e.attribute (Xml::TRAIN_ID)) != NULL) {
         setTrain(((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainById(a));
     } else if ((a = e.attribute (Xml::TRAIN)) != NULL) {
         setTrain(((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainByName(a));
     }
    if (getTrain() != NULL && getTrain()->getRoute() != NULL &&
             (a = e.attribute (Xml::ROUTE_LOCATION_ID)) != NULL) {
         _routeLocation = getTrain()->getRoute()->getLocationById(a);
         if ((a = e.attribute (Xml::ROUTE_DESTINATION_ID)) != NULL) {
             _routeDestination = getTrain()->getRoute()->getLocationById(a);
         }
     }
     if ((a = e.attribute (Xml::LAST_ROUTE_ID)) != NULL) {
         _routeId = a;
     }
     if ((a = e.attribute (Xml::OWNER)) != NULL) {
         _owner = a;
     }
     if ((a = e.attribute (Xml::COMMENT)) != NULL) {
         _comment = a;
     }
     if ((a = e.attribute (Xml::VALUE)) != NULL) {
         _value = a;
     }
     if ((a = e.attribute (Xml::RFID)) != NULL) {
         setRfid(a);
     }
     if ((a = e.attribute (Xml::LOC_UNKNOWN)) != NULL) {
         _locationUnknown = a==(Xml::_TRUE);
     }
     if ((a = e.attribute (Xml::OUT_OF_SERVICE)) != NULL) {
         _outOfService = a==(Xml::_TRUE);
     }
     if ((a = e.attribute (Xml::SELECTED)) != NULL) {
         _selected = a==(Xml::_TRUE);
     }
     if ((a = e.attribute (Xml::DATE)) != NULL) {
         setLastDate(a); // uses the setLastDate(String) method.
     }
     if ((a = e.attribute (Xml::BLOCKING)) != NULL) {
         _blocking = a.toInt();
     }
     // check for rolling stock without a track assignment
     if (getLocation() != NULL && getTrack() == NULL && getTrain() == NULL) {
         log->warn(tr("Rollingstock (%1) at (%2) doesn't have a track assignment").arg(toString()).arg(getLocationName()));
     }
     addPropertyChangeListeners();
 }


 /**
  * Add XML elements to represent this Entry.
  *
  * @return Contents in a JDOM Element
  */
 /*protected*/ QDomElement RollingStock::store(QDomElement e) {
     e.setAttribute(Xml::ID, getId());
     e.setAttribute(Xml::ROAD_NAME, getRoadName());
     e.setAttribute(Xml::ROAD_NUMBER, getNumber());
     e.setAttribute(Xml::TYPE, getTypeName());
     e.setAttribute(Xml::LENGTH, getLength());
     if (getColor()!=(NONE)) {
         e.setAttribute(Xml::COLOR, getColor());
     }
     if (getWeight()!=(DEFAULT_WEIGHT)) {
         e.setAttribute(Xml::WEIGHT, getWeight());
     }
     if (getWeightTons()!=(NONE)) {
         e.setAttribute(Xml::WEIGHT_TONS, getWeightTons());
     }
     if (getBuilt()!=(NONE)) {
         e.setAttribute(Xml::BUILT, getBuilt());
     }
     if (getLocationId()!=(NONE)) {
         e.setAttribute(Xml::LOCATION_ID, getLocationId());
     }
     if (getRouteLocationId()!=(NONE)) {
         e.setAttribute(Xml::ROUTE_LOCATION_ID, getRouteLocationId());
     }
     if (getTrackId()!=(NONE)) {
         e.setAttribute(Xml::SEC_LOCATION_ID, getTrackId());
     }
     if (getDestinationId()!=(NONE)) {
         e.setAttribute(Xml::DESTINATION_ID, getDestinationId());
     }
     if (getRouteDestinationId()!=(NONE)) {
         e.setAttribute(Xml::ROUTE_DESTINATION_ID, getRouteDestinationId());
     }
     if (getDestinationTrackId()!=(NONE)) {
         e.setAttribute(Xml::SEC_DESTINATION_ID, getDestinationTrackId());
     }
     if (getSavedRouteId()!=(NONE)) {
         e.setAttribute(Xml::LAST_ROUTE_ID, getSavedRouteId());
     }
     if (verboseStore) {
         e.setAttribute(Xml::LOCATION, getLocationName());
         e.setAttribute(Xml::TRACK, getTrackName());
         e.setAttribute(Xml::DESTINATION, getDestinationName());
         e.setAttribute(Xml::DES_TRACK, getDestinationTrackName());
     }
     e.setAttribute(Xml::MOVES, (getMoves()));
     e.setAttribute(Xml::DATE, getLastDate());
     e.setAttribute(Xml::SELECTED, isSelected() ? Xml::_TRUE : Xml::_FALSE);
     if (getLastLocationId()!=(LOCATION_UNKNOWN)) {
         e.setAttribute(Xml::LAST_LOCATION_ID, getLastLocationId());
     }
     if (getTrainName()!=(NONE)) {
         e.setAttribute(Xml::TRAIN, getTrainName());
         e.setAttribute(Xml::TRAIN_ID, getTrain()->getId());
     }
     if (getOwner()!=(NONE)) {
         e.setAttribute(Xml::OWNER, getOwner());
     }
     if (getValue()!=(NONE)) {
         e.setAttribute(Xml::VALUE, getValue());
     }
     if (getRfid()!=(NONE)) {
         e.setAttribute(Xml::RFID, getRfid());
     }
     if (isLocationUnknown()) {
         e.setAttribute(Xml::LOC_UNKNOWN, isLocationUnknown() ? Xml::_TRUE : Xml::_FALSE);
     }
     if (isOutOfService()) {
         e.setAttribute(Xml::OUT_OF_SERVICE, isOutOfService() ? Xml::_TRUE : Xml::_FALSE);
     }
     if (getBlocking() != 0) {
         e.setAttribute(Xml::BLOCKING, (getBlocking()));
     }
     if (getComment()!=(NONE)) {
         e.setAttribute(Xml::COMMENT, getComment());
     }
     return e;
 }

 /*private*/ void RollingStock::addPropertyChangeListeners() {
     //CarRoads.instance().addPropertyChangeListener(this);
  connect(((CarRoads*)InstanceManager::getDefault("CarRoads")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //        CarOwners.instance().addPropertyChangeListener(this);
  connect(((CarOwners*)InstanceManager::getDefault("CarOwners")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  //        CarColors.instance().addPropertyChangeListener(this);
  connect(((CarOwners*)InstanceManager::getDefault("CarOwners")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
 }

 // rolling stock listens for changes in a location name or if a location is deleted
 /*public*/ void RollingStock::propertyChange(PropertyChangeEvent* e)
 {
   if (log->isDebugEnabled()) log->debug("Property change for rolling stock: " + toString()+ " property name: "
   + e->getPropertyName()+ " old: "+e->getOldValue().toString()+ " new: "+e->getNewValue().toString());
  // notify if track or location name changes
  if (e->getPropertyName()==(Location::NAME_CHANGED_PROPERTY)) {
      if (log->isDebugEnabled()) {
       log->debug(tr("Property change for rolling stock: (%1) property name: (%2) old: (%3) new: (%4)").arg(
                  e->toString()).arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString()));
      }
      setDirtyAndFirePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
  }
  if (e->getPropertyName()==(Location::DISPOSE_CHANGED_PROPERTY)) {
      if (e->getSource() == _location) {
          if (log->isDebugEnabled()) {
              log->debug(tr("delete location for rolling stock: (%1)").arg(toString()));
          }
          setLocation(NULL, NULL);
      }
      if (e->getSource() == _destination) {
          if (log->isDebugEnabled()) {
              log->debug(tr("delete destination for rolling stock: (%1)").arg(toString()));
          }
          setDestination(NULL, NULL);
      }
  }
  if (e->getPropertyName()==(Track::DISPOSE_CHANGED_PROPERTY)) {
      if (e->getSource() == _trackLocation) {
          if (log->isDebugEnabled()) {
              log->debug(tr("delete location for rolling stock: (%1)").arg(toString()));
          }
          setLocation(_location, NULL);
      }
      if (e->getSource() == _trackDestination) {
          if (log->isDebugEnabled()) {
              log->debug(tr("delete destination for rolling stock: (%1)").arg(toString()));
          }
          setDestination(_destination, NULL);
      }
  }
  if (e->getPropertyName()==(Train::DISPOSE_CHANGED_PROPERTY) && e->getSource() == getTrain()) {
      if (log->isDebugEnabled()) {
          log->debug(tr("delete train for rolling stock: (%1)").arg(toString()));
      }
      setTrain(NULL);
  }
  if (e->getPropertyName()==(Train::TRAIN_LOCATION_CHANGED_PROPERTY) && e->getSource() == getTrain()) {
      if (log->isDebugEnabled()) {
          log->debug(tr("Rolling stock (%1) is serviced by train (%2)").arg(toString()).arg(getTrainName()));
      }
      moveRollingStock(VPtr<RouteLocation>::asPtr( e->getOldValue()), VPtr<RouteLocation>::asPtr(e->getNewValue()));
  }
  if (e->getPropertyName()==(Train::STATUS_CHANGED_PROPERTY) && e->getNewValue()==(Train::TRAIN_RESET)
          && e->getSource() == getTrain()) {
      if (log->isDebugEnabled()) {
          log->debug(tr("Rolling stock (%1) is removed from train (%2) by reset").arg(toString()).arg(getTrainName())); // NOI18N
      }
      reset();
  }
  if (e->getPropertyName()==(Train::NAME_CHANGED_PROPERTY)) {
      setDirtyAndFirePropertyChange(e->getPropertyName(), e->getOldValue(), e->getNewValue());
  }

  if (e->getPropertyName()==(CarRoads::CARROADS_NAME_CHANGED_PROPERTY)) {
      if (e->getOldValue()==(getRoadName())) {
          if (log->isDebugEnabled()) {
              log->debug(tr("Rolling stock (%1) sees road name change from (%2) to (%3)").arg(toString()).arg(
                      e->getOldValue().toString()).arg(e->getNewValue().toString())); // NOI18N
          }
          if (e->getNewValue() != QVariant()) {
              setRoadName( e->getNewValue().toString());
          }
      }
  }

  if (e->getPropertyName()==(CarOwners::CAROWNERS_NAME_CHANGED_PROPERTY)) {
      if (e->getOldValue()==(getOwner())) {
          if (log->isDebugEnabled()) {
              log->debug(tr("Rolling stock (%1) sees owner name change from (%2) to (%3)").arg(toString()).arg(e
                      ->getOldValue().toString()).arg(e->getNewValue().toString())); // NOI18N
          }
          setOwner( e->getNewValue().toString());
      }
  }
  if (e->getPropertyName()==(CarColors::CARCOLORS_NAME_CHANGED_PROPERTY)) {
      if (e->getOldValue()==(getColor())) {
          if (log->isDebugEnabled()) {
           log->debug(tr("Rolling stock (%1) sees color name change from (%2) to (%3)").arg(toString()).arg(e
                   ->getOldValue().toString()).arg(e->getNewValue().toString())); // NOI18N
          }
          setColor( e->getNewValue().toString());
      }
  }
 }

 /*protected*/ void RollingStock::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n)
 {
  firePropertyChange(p, old, n);
 }

} // end namespace
