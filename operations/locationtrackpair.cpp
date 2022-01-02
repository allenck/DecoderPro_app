#include "locationtrackpair.h"
#include "location.h"
#include "track.h"

namespace Operations
{
/**
 * An Object representing a location and track.
 *
 * @author Daniel Boudreau Copyright (C) 2009
 *
 */
///*public*/ class LocationTrackPair {


 /*public*/ LocationTrackPair::LocationTrackPair(Location* location, Track* track) : QObject() {
     _location = location;
     _track = track;
 }

 // for combo boxes
 /*public*/ QString LocationTrackPair::toString() {
     return _location->getName() + " (" + _track->getName() + ")";
 }

 /*public*/ Track* LocationTrackPair::getTrack() {
     return _track;
 }

 /*public*/ Location* LocationTrackPair::getLocation() {
     return _location;
 }

}
