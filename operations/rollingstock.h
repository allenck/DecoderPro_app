#ifndef ROLLINGSTOCK_H
#define ROLLINGSTOCK_H

#include <QObject>
#include <QDate>
#include "propertychangelistener.h"
#include "appslib_global.h"
#include "propertychangesupport.h"
#include "instancemanager.h"

class DefaultIdTag;
class PropertyChangeEvent;
class QDomElement;
class Logger;
class QDate;
namespace Operations
{
 class Division;
 class LocationManager;
 class Track;
 class Train;
 class RouteLocation;
 class Location;
 class APPSLIBSHARED_EXPORT RollingStock : public PropertyChangeSupport, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  //explicit RollingStock(QObject *parent = 0);
  /*public*/ static /*final*/ QString NONE;// = "";
  /*public*/ static /*final*/ int DEFAULT_BLOCKING_ORDER;// = 0;
  /*public*/ static /*final*/ bool FORCE;// = true; // ignore length, type, etc. when setting car's track
  /*public*/ RollingStock(QObject *parent = 0) ;
  /*public*/ RollingStock(QString road, QString number, QObject *parent = 0);
  /*public*/ static QString createId(QString road, QString number);
  /*public*/ QString getId();
  /*public*/ void setNumber(QString number);
  /*public*/ QString getNumber() ;
  /*public*/ void setRoadName(QString road) ;
  /*public*/ QString getRoadName();
  /*public*/ QString toString();
  /*public*/ RouteLocation* getRouteDestination();
  /*public*/ QString getRouteDestinationId();
  /*public*/ static /*final*/ QString LOCATION_UNKNOWN; //="0";

  /*public*/ static /*final*/ QString ERROR_TRACK; //="ERROR wrong track for location"; // NOI18N checks for coding error

  /*public*/ static /*final*/ QString LOCATION_CHANGED_PROPERTY; //="rolling stock location"; // NOI18N property change
  // descriptions
  /*public*/ static /*final*/ QString TRACK_CHANGED_PROPERTY; //="rolling stock track location"; // NOI18N
  /*public*/ static /*final*/ QString DESTINATION_CHANGED_PROPERTY; //="rolling stock destination"; // NOI18N
  /*public*/ static /*final*/ QString DESTINATION_TRACK_CHANGED_PROPERTY; //="rolling stock track destination"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_CHANGED_PROPERTY; //="rolling stock train"; // NOI18N
  /*public*/ static /*final*/ QString LENGTH_CHANGED_PROPERTY; //="rolling stock length"; // NOI18N
  /*public*/ static /*final*/ QString TYPE_CHANGED_PROPERTY; //="rolling stock type"; // NOI18N
  /*public*/ static /*final*/ QString ROUTE_LOCATION_CHANGED_PROPERTY; //="rolling stock route location"; // NOI18N
  /*public*/ static /*final*/ QString ROUTE_DESTINATION_CHANGED_PROPERTY; //="rolling stock route destination"; // NOI18N
  /*public*/ static /*final*/ int COUPLER;// = Setup.getLengthUnit().equals(Setup.FEET) ? Integer.parseInt(Bundle
  /*public*/ QString getLength();
  /*public*/ int getLengthInteger();
  /*public*/ int getTotalLength();
  /*public*/ RollingStock(QDomElement e, QObject* parent = 0);
  /*public*/ QString setLocation(Location* location, Track* track);
  /*public*/ QString setLocation(Location* location, Track* track, bool force);
  /*public*/ QString testLocation(Location* location, Track* track);
  /*public*/ Train* getTrain();
  /*public*/ QString getTrainName();
  /*public*/ virtual void setTypeName(QString type);
  /*public*/ virtual QString getTypeName();
  /*public*/ Location* getDestination() ;
  /*public*/ void setDestination(Location* destination);
  /*public*/ QString getDestinationName();
  /*public*/ QString getDestinationId();
  /*public*/ void setDestinationTrack(Track* track);
  /*public*/ Track* getDestinationTrack() ;
  /*public*/ QString getDestinationTrackName() ;
  /*public*/ QString getDestinationTrackId();
  /*public*/ Track* getTrack();
  /*public*/ void setDivision(Division* division);
  /*public*/ Division* getDivision();
  /*public*/ QString getDivisionName();
  /*public*/ QString getDivisionId();
  /*public*/ void setLastLocationId(QString id) ;
  /*public*/ QString getLastLocationId();
  /*public*/ QString setDestination(Location* destination, Track* track);
  /*public*/ QString setDestination(Location* destination, Track* track, bool force);
  /*public*/ virtual QString testDestination(Location* destination, Track* track) ;
  /*public*/ QString getSavedRouteId();
  /*public*/ void setLastRouteId(QString id);
  /*public*/ QString getValue();
  /*public*/ void setMoves(int moves);
  /*public*/ int getMoves();
  /*public*/ void setRouteLocation(RouteLocation* routeLocation);
  /*public*/ RouteLocation* getRouteLocation();
  /*public*/ void setRouteDestination(RouteLocation* routeDestination);
  /*public*/ void setLastDate(QDateTime date);
  /*public*/ QString getRouteLocationId();
  /*public*/ void setBuilt(QString built);
  /*public*/ QString getBuilt() ;
  /*public*/ QString getStatus();
  /*public*/ Location* getLocation() ;
  /*public*/ QString getLocationName();
  /*public*/ QString getLocationId();
  /*public*/ void setTrack(Track* track);
  /*public*/ QString getTrackName() ;
  /*public*/ QString getTrackId();
  /*public*/ void setOwner(QString owner) ;
  /*public*/ QString getOwner();
  /*public*/ void setLocationUnknown(bool unknown);
  /*public*/ bool isLocationUnknown();
  /*public*/ void setOutOfService(bool outOfService);
  /*public*/ void setBlocking(int number);
  /*public*/ int getBlocking();
  /*public*/ bool isOutOfService() ;
  /*public*/ void setSelected(bool selected);
  /*public*/ Q_DECL_DEPRECATED void setLastDate(QString date);
  /*public*/ QString getWhereLastSeenName() ;
  /*public*/ Location* getWhereLastSeen();
  /*public*/ Track* getTrackLastSeen();
  /*public*/ QString getTrackLastSeenName();
  /*public*/ QDateTime getWhenLastSeen();
  /*public*/ QString getWhenLastSeenDate();
  /*public*/ QString getLastDate();
  /*public*/ void setValue(QString value);
  /*public*/ QString getRfid();
  /*public*/ DefaultIdTag* getIdTag();
  /*public*/ void setIdTag(DefaultIdTag *tag);
  /*public*/ void setRfid(QString id);
  /*public*/ QDateTime getLastMoveDate() ;
  /*public*/ void setColor(QString color);
  /*public*/ QString getColor();
  /*public*/ void setTrain(Train* train);
  /*public*/ void setWeight(QString weight) ;
  /*public*/ QString getWeight();
  /*public*/ void setWeightTons(QString weight);
  /*public*/ QString getWeightTons();
  /*public*/ int getAdjustedWeightTons();
  /*public*/ bool isSelected();
  /*public*/ QString getLoadPriority();
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment();
  /*public*/ void reset();
  /*public*/ void dispose();
  /*public*/ Q_DECL_DEPRECATED QString getType();
  /*public*/ void setLength(QString length);

  QObject* self() override {return (QObject*)this; }

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) override;

 private:
  void common();
  LocationManager* locationManager = (LocationManager*)InstanceManager::getDefault("Operations::LocationManager");

  static Logger* log;
  bool verboseStore;// = false;
  /*private*/QString rsTestDestination(Location* destination, Track* track);
  /*private*/ DefaultIdTag* _tag;// = NULL;
  /*private*/ PropertyChangeListener* _tagListener;// = NULL;
  /*private*/ void addPropertyChangeListeners();


 protected:
  /*protected*/ virtual void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ static /*final*/ QString DEFAULT_WEIGHT;// = "0";
  /*protected*/ QString _id=NONE;
  /*protected*/ QString _number=NONE;
  /*protected*/ QString _road=NONE;
  /*protected*/ QString _type=NONE;
  /*protected*/ QString _length=NONE;
  /*protected*/ QString _color=NONE;
  /*protected*/ QString _weight=DEFAULT_WEIGHT;
  /*protected*/ QString _weightTons=DEFAULT_WEIGHT;
  /*protected*/ QString _built=NONE;
  /*protected*/ QString _owner=NONE;
  /*protected*/ QString _comment=NONE;
  /*protected*/ QString _routeId=NONE; // saved route for interchange tracks
  /*protected*/ QString _rfid=NONE;
  /*protected*/ QString _value=NONE;
  /*protected*/ QString _last=NONE;
  /*protected*/ QDateTime _lastDate=QDateTime();
  /*protected*/ bool _locationUnknown=false;
  /*protected*/ bool _outOfService=false;
  /*protected*/ bool _selected=false;

  /*protected*/ Location* _location=nullptr;
  /*protected*/ Track* _trackLocation=nullptr;
  /*protected*/ Location* _destination=nullptr;
  /*protected*/ Track* _trackDestination=nullptr;
  /*protected*/ Train* _train=nullptr;
  /*protected*/ RouteLocation* _routeLocation = nullptr;
  /*protected*/ RouteLocation* _routeDestination =nullptr;
  /*protected*/ Division* _division = nullptr;
  /*protected*/ int _moves=0;
  /*protected*/ QString _lastLocationId=LOCATION_UNKNOWN; // the rollingstock's last location id
  /*protected*/ int _blocking=0;
  /*protected*/ int number;// = 0; // used by rolling stock manager for sort by number
  /*protected*/ bool _lengthChange;// = false; // used for loco length change
  /*protected*/ QDomElement store(QDomElement e);
  /*protected*/ void moveRollingStock(RouteLocation* old, RouteLocation* next);

 friend class IdTagPropertyChangeListener;
 friend class RollingStockManager;
 };

 class IdTagPropertyChangeListener :  public QObject, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
  RollingStock* parent;
 public:
  IdTagPropertyChangeListener(RollingStock* parent);
  QObject* self() {return (QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e) ;
 };
} // end namespace
#endif // ROLLINGSTOCK_H
