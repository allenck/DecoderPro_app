#ifndef ROUTELOCATION_H
#define ROUTELOCATION_H

#include <QObject>
#include "logger.h"
#include "propertychangesupport.h"
#include "appslib_global.h"
#include <QColor>

class QDomDocument;
class QDomElement;
namespace Operations
{
 class  Setup;
 class Location;
 class APPSLIBSHARED_EXPORT RouteLocation : public PropertyChangeSupport, public PropertyChangeListener
 {
  Q_OBJECT
   Q_INTERFACES(PropertyChangeListener)
 public:
  //explicit RouteLocation(QObject *parent = 0);
  /*public*/ static /*final*/ QString NONE; //="";
  /*public*/ RouteLocation(QString id, Location* location, QObject *parent = 0);
  /*public*/ static /*final*/ int EAST; //=1; // train direction
  /*public*/ static /*final*/ int WEST; //=2;
  /*public*/ static /*final*/ int NORTH; //=4;
  /*public*/ static /*final*/ int SOUTH; //=8;

  /*public*/ static /*final*/ QString EAST_DIR; //=Setup.EAST_DIR; // train directions text
  /*public*/ static /*final*/ QString WEST_DIR; //=Setup.WEST_DIR;
  /*public*/ static /*final*/ QString NORTH_DIR; //=Setup.NORTH_DIR;
  /*public*/ static /*final*/ QString SOUTH_DIR; //=Setup.SOUTH_DIR;

  /*public*/ static /*final*/ QString DISPOSE; //="routeLocationDispose"; // NOI18N
  /*public*/ static /*final*/ QString DELETED; //=Bundle.getMessage("locationDeleted");

  /*public*/ static /*final*/ QString DROP_CHANGED_PROPERTY; //="dropChange"; // NOI18N
  /*public*/ static /*final*/ QString PICKUP_CHANGED_PROPERTY; //="pickupChange"; // NOI18N
  /*public*/ static /*final*/ QString MAXMOVES_CHANGED_PROPERTY; //="maxMovesChange"; // NOI18N
  /*public*/ static /*final*/ QString TRAIN_DIRECTION_CHANGED_PROPERTY; //="trainDirectionChange"; // NOI18N
  /*public*/ static /*final*/ QString DEPARTURE_TIME_CHANGED_PROPERTY; //="routeDepartureTimeChange"; // NOI18N

  /*public*/ static /*final*/ QString DISABLED; //="Off";
  /*public*/ QString toString();
  /*public*/ QString getId() ;
  /*public*/ QString getName();
  PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
  /*public*/ Location* getLocation() ;
  /*public*/ int getSequenceId();
  /*public*/ void setSequenceId(int sequence) ;
  /*public*/ void setComment(QString comment);
  /*public*/ QString getComment();
  /*public*/ void setCommentColor(QColor color);
  /*public*/ QColor getCommentColor();
  /*public*/ QString getFormatedColorComment();
  /*public*/ void setCommentTextColor(QString color);
  /*public*/ QString getCommentTextColor();
  /*public*/ void setTrainDirection(int direction);
  /*public*/ int getTrainDirection() ;
  /*public*/ QString getTrainDirectionString();
  /*public*/ void setMaxTrainLength(int length);
  /*public*/ int getMaxTrainLength();
  /*public*/ void setTrainIconX(int x);
  /*public*/ int getTrainIconX() ;
  /*public*/ void setTrainIconY(int y);
  /*public*/ int getTrainIconY();
  /*public*/ void setTrainIconCoordinates() ;
  /*public*/ QPoint getTrainIconCoordinates();
  /*public*/ void dispose();
  /*public*/ RouteLocation(QDomElement e, QObject *parent = nullptr);
  /*public*/ QDomElement store(QDomDocument doc);
  /*public*/ int getMaxCarMoves();
  /*public*/ void setRandomControl(QString value);
  /*public*/ QString getRandomControl();
  /*public*/ void setDropAllowed(bool drops) ;
  /*public*/ bool isDropAllowed() ;
  /*public*/ void setPickUpAllowed(bool pickups) ;
  /*public*/ bool isPickUpAllowed();
  /*public*/ void setCarMoves(int moves);
  /*public*/ int getCarMoves();
  /*public*/ void setWait(int time);
  /*public*/ int getWait();
  /*public*/ void setDepartureTime(QString time) ;
  /*public*/ void setDepartureTime(QString hour, QString minute);
  /*public*/ QString getDepartureTime() ;
  /*public*/ QString getDepartureTimeHour();
  /*public*/ QString getDepartureTimeMinute() ;
  /*public*/ QString getFormatedDepartureTime() ;
  /*public*/ void setGrade(double grade);
  /*public*/ double getGrade();
  /*public*/ void setMaxCarMoves(int moves);
  /*public*/ void setTrainLength(int length) ;
  /*public*/ int getTrainLength();
  /*public*/ void setTrainWeight(int weight);
  /*public*/ int getTrainWeight();
  QObject* self() override {return (QObject*)this; }

 signals:

 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override;

 private:
  Logger* log;
  /*private*/ QString getNameId();
  void common();
  QColor _commentColor;

 protected:
  /*protected*/ QString _id; //=NONE;
  /*protected*/ Location* _location; //=NULL; // the location in the route
  /*protected*/ QString _locationId; //=NONE; // the location's id
  /*protected*/ int _trainDir; //=(Setup.getTrainDirection() == Setup.EAST + Setup.WEST) ? EAST : NORTH; // train direction
  /*protected*/ int _maxTrainLength; //=Setup.getMaxTrainLength();
  /*protected*/ int _maxCarMoves; //=Setup.getCarMoves();
  /*protected*/ QString _randomControl; //=DISABLED;
  /*protected*/ bool _drops; //=true; // when true set outs allowed at this location
  /*protected*/ bool _pickups; //=true; // when true pick ups allowed at this location
  /*protected*/ int _sequenceId; //=0; // used to determine location order in route
  /*protected*/ double _grade; //=0; // maximum grade between locations
  /*protected*/ int _wait; //=0; // wait time at this location
  /*protected*/ QString _departureTime; //=NONE; // departure time from this location
  /*protected*/ int _trainIconX; //=0; // the x & y coordinates for the train icon
  /*protected*/ int _trainIconY; //=0;
  /*protected*/ QString _comment; //=NONE;

  /*protected*/ int _carMoves; //=0; // number of moves at this location
  /*protected*/ int _trainWeight; //=0; // total car weight departing this location
  /*protected*/ int _trainLength; //=0; // train length departing this location
  /*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);
  /*protected*/ void setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n);

 };
} // end Operations
#endif // ROUTELOCATION_H
