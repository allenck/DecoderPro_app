#ifndef LOCATIONTRACKPAIR_H
#define LOCATIONTRACKPAIR_H

class QString;
namespace Operations
{
 class Location;
 class Track;
 class LocationTrackPair
 {
 public:
  LocationTrackPair(Location* location, Track* track);
  /*public*/ QString toString();
  /*public*/ Track* getTrack();
  /*public*/ Location* getLocation();

 private:
  Location* _location;
  Track* _track;

 };
}
#endif // LOCATIONTRACKPAIR_H
