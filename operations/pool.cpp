#include "pool.h"
#include "track.h"
#include "swingpropertychangesupport.h"
#include "logger.h"

//Pool::Pool(QObject *parent) :
//  QObject(parent)
//{
//}
namespace Operations {
/**
 * Represents a pool of tracks that share their length.
 *
 * @author Daniel Boudreau Copyright (C) 2011
 * @author Gregory Madsen Copyright (C) 2012
 *
 * @version $Revision: 29531 $
 */
///*public*/ class Pool extends Bean {

    /*public*/ /*static*/ /*final*/ QString Pool::LISTCHANGE_CHANGED_PROPERTY = "poolListChange"; // NOI18N
    /*public*/ /*static*/ /*final*/ QString Pool::DISPOSE = "poolDispose"; // NOI18N

    //static Logger log = LoggerFactory.getLogger(Pool.class);

    // stores tracks for this pool
    /*public*/ QString Pool::getId() {
        return _id;
    }


    /*public*/ QString Pool::getName() {
        return _name;
    }

    /*public*/ void Pool::setName(QString name) {
        QString old = _name;
        _name = name;
        this->firePropertyChange("Name", old, name);
    }

    /**
     * The number of tracks in this pool.
     *
     * @return the number of tracks in this pool.
     */
    /*public*/ int Pool::getSize() {
        return _tracks.size();
    }

    // for combo boxes
    /*public*/ QString Pool::toString() {
        return _name;
    }

    /*public*/ Pool::Pool(QString id, QString name,QObject *parent) :
  Bean(parent) {
        log->debug(tr("New pool (%1) id: %2").arg(name).arg(id));
        _name = name;
        _id = id;
         _tracks = QList<Track*>();

          _id = "";
          _name = "";
          propertyChangeSupport = new SwingPropertyChangeSupport(this, nullptr);
          log = new Logger("Pool");
    }

    /*public*/ void Pool::dispose() {
 this->firePropertyChange(DISPOSE, QVariant(), DISPOSE);
    }

    /**
     * Adds a track to this pool
     *
     * @param track to be added.
     */
    /*public*/ void Pool::add(Track* track) {
        if (!_tracks.contains(track)) {

            int oldSize = _tracks.size();
            _tracks.append(track);

            this->firePropertyChange(LISTCHANGE_CHANGED_PROPERTY, (oldSize), (_tracks.size()));
        }
    }

    /**
     * Removes a track from this pool
     *
     * @param track to be removed.
     */
    /*public*/ void Pool::remove(Track* track) {
        if (_tracks.contains(track)) {

            int oldSize = _tracks.size();
            _tracks.removeOne(track);

            this->firePropertyChange(LISTCHANGE_CHANGED_PROPERTY, (oldSize), (_tracks.size()));
        }
    }

    /*public*/ QList<Track*> Pool::getTracks() {
        // Return a copy to protect the internal list
        return QList<Track*>(_tracks);
    }

    /*public*/ int Pool::getTotalLengthTracks() {
        int total = 0;
        foreach (Track* track, getTracks()) {
            total += track->getLength();
        }
        return total;
    }

    /**
     * Request track length from one of the other tracks in this pool. Other
     * tracks in the same pool may have their length shortened or lengthened by
     * this operation.
     *
     * @param track  the track requesting additional length
     * @param length the length of rolling stock
     * @return true if successful
     */
    /*public*/ bool Pool::requestTrackLength(Track* track, int length) {
        // only request enough length for the rolling stock to fit
        int additionalLength = track->getUsedLength() + track->getReserved() + length - track->getLength();

        foreach (Track* t, getTracks()) {
            // note that the reserved track length can be either positive or negative
            if (t != track) {
                if (t->getUsedLength() + t->getReserved() + additionalLength <= t->getLength()
                        && t->getLength() - additionalLength >= t->getMinimumLength()) {
                 log->debug(tr("Pool (%1) increasing track (%2) length (%3) decreasing (%4)").arg(getName()).arg(
                            track->getName()).arg(additionalLength).arg(t->getName())); // NOI18N
                    t->setLength(t->getLength() - additionalLength);
                    track->setLength(track->getLength() + additionalLength);
                    return true;
                } else {
                    // steal whatever isn't being used by this track
                    int available = t->getLength() - (t->getUsedLength() + t->getReserved());
                    int min = t->getLength() - t->getMinimumLength();
                    if (min < available) {
                        available = min;
                    }
                    if (available > 0) {
                        // adjust track lengths and reduce the additional length needed
                     log->debug(tr("Pool (%1) incremental increase for track (%2) length (%3) decreasing (%4)").arg(
                                getName()).arg(track->getName()).arg(available).arg(t->getName())); // NOI18N
                        t->setLength(t->getLength() - available);
                        track->setLength(track->getLength() + available);
                        additionalLength = additionalLength - available;
                    }
                }
            }
        }
        return false;
    }
}

