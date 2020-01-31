#include "rpsreporter.h"
#include "loggerfactory.h"
#include "region.h"
#include "model.h"
#include "dcclocoaddress.h"
#include "engine.h"
/**
 * RPS implementation of the Reporter interface.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
 * @since 2.3.1
 */
///*public*/ class RpsReporter extends AbstractReporter implements MeasurementListener {

/*public*/ RpsReporter::RpsReporter(QString systemName, QObject* parent) : AbstractReporter(systemName, parent)
{
    //super(systemName);
 contents = QList<int>();
    // create Region from all but prefix
    region = new Region(systemName.mid(2, systemName.length()));
    Model::instance()->addRegion(region);
}

/*public*/ RpsReporter::RpsReporter(QString systemName, QString userName, QObject* parent) : AbstractReporter(systemName, userName, parent)
{
    //super(systemName, userName);
 contents = QList<int>();
    // create Region from all but prefix
    region = new Region(systemName.mid(2, systemName.length()));
    Model::instance()->addRegion(region);
}

//@Override
/*public*/ void RpsReporter::notify(Measurement* r) {
    QVector3D p = QVector3D(r->getX(), r->getY(), r->getZ());
    int id = (r->getReading()->getID()).toInt();

    // ignore if code not OK
    if (!r->isOkPoint()) {
        return;
    }

    // ignore if not in Z fiducial volume
    if (r->getZ() > 20 || r->getZ() < -20) {
        return;
    }

    if (log->isDebugEnabled()) {
        log->debug("starting " + getSystemName());
    }
    if (region->isInside(p)) {
        notifyInRegion(id);
    } else {
        notifyOutOfRegion(id);
    }
}

void RpsReporter::notifyInRegion(int id) {
    // make sure region contains this Reading.getId();
    if (!contents.contains(id)) {
        contents.append(id);
        notifyArriving(id);
    }
}

void RpsReporter::notifyOutOfRegion(int id) {
    // make sure region does not contain this Reading.getId();
    if (contents.contains(id)) {
        contents.removeOne(id);
        notifyLeaving(id);
    }
}


/**
 * Notify parameter listeners that a device has left the region covered by
 * this sensor
 */
void RpsReporter::notifyLeaving(int id) {
    firePropertyChange("Leaving", QVariant(), id);
    setReport("");
}

/**
 * Notify parameter listeners that a device has entered the region covered
 * by this sensor
 */
void RpsReporter::notifyArriving(int id) {
    firePropertyChange("Arriving", QVariant(), id);
    setReport("" + id);
}

/**
 * Numerical state is the number of transmitters in the region
 */
//@Override
/*public*/ int RpsReporter::getState() {
    return contents.size();
}

//@Override
/*public*/ void RpsReporter::setState(int i) {
}

//@Override
/*public*/ void RpsReporter::dispose() {
    Model::instance()->removeRegion(region);
}

// Methods to support PhysicalLocationReporter interface
/**
 * getLocoAddress()
 *
 * Parses out a (possibly old) RpsReporter-generated report string to
 * extract the address from the front. Assumes the RpsReporter format is
 * "NNNN"
 */
/*public*/ locoAddress* RpsReporter::getLocoAddress(QString rep) {
    // The report is a string, that is the ID of the locomotive (I think)
    log->debug("Parsed ID: " + rep);
    // I have no idea what kind of loco address an RPS reporter uses,
    // so we'll default to DCC for now.
    if (rep.length() > 0) {
        try {
            int id = (rep).toInt();
//            int addr = RPS::Engine::instance().getTransmitter(id).getAddress();
//            return (new DccLocoAddress(addr, LocoAddress::Protocol::DCC));
        } catch (NumberFormatException e) {
            return (NULL);
        }
    } else {
        return (NULL);
    }
}

/**
 * getDirection()
 *
 * Gets the direction (ENTER/EXIT) of the report. Because of the way Ecos
 * Reporters work (or appear to), all reports are ENTER type.
 */
/*public*/ PhysicalLocationReporter::Direction getDirection(QString rep) {
    // The RPS reporter only sends a report on entry.
    return (PhysicalLocationReporter::Direction::ENTER);
}

/**
 * getPhysicalLocation()
 *
 * Returns the PhysicalLocation of the Reporter
 *
 * Reports its own location, for now. Not sure if that's the right thing or
 * not. Would be nice if it reported the exact measured location of the
 * transmitter, but right now that doesn't appear to be being stored
 * anywhere retrievable. NOT DONE YET
 */
/*public*/ PhysicalLocation* RpsReporter::getPhysicalLocation() {
    return (PhysicalLocation::getBeanPhysicalLocation(this));
}

/**
 * getPhysicalLocation(String s)
 *
 * Returns the PhysicalLocation of the Transmitter with the given ID
 *
 * Given an ID (in String form), looks up the Transmitter and gets its
 * current PhysicalLocation (translated from the RPS Measurement).
 */
/*public*/ PhysicalLocation* RpsReporter::getPhysicalLocation(QString s) {
    if (s.length() > 0) {
        try {
            int id = (s).toInt();
//            QVector3D v = RPS::Engine::instance()->getTransmitter(id)->getLastMeasurement()->getVector();
//            return (new PhysicalLocation(QVector3D(v)));
        } catch (NumberFormatException e) {
            return (NULL);
        } catch (NullPointerException e) {
            return (NULL);
        }
    } else {
        return (NULL);
    }

}

/*private*/ /*final*/ /*static*/ Logger* RpsReporter::log = LoggerFactory::getLogger("RpsReporter");
