#ifndef LOCATIONTRACKPAIR_H
#define LOCATIONTRACKPAIR_H
#include <QObject>

class QString;
namespace Operations
{
 class Location;
 class Track;
 class LocationTrackPair :public QObject
 {
   Q_OBJECT
 public:
   LocationTrackPair() {}
  LocationTrackPair(Location* location, Track* track);
  ~LocationTrackPair() {}
  LocationTrackPair(const LocationTrackPair&) : QObject() {}
  /*public*/ QString toString();
  /*public*/ Track* getTrack();
  /*public*/ Location* getLocation();

 private:
  Location* _location;
  Track* _track;

 };
}
Q_DECLARE_METATYPE(Operations::LocationTrackPair)
#endif // LOCATIONTRACKPAIR_H
