#include "rpssensor.h"
#include "loggerfactory.h"
#include "region.h"
#include "model.h"
#include "measurement.h"
#include <QVector3D>

/**
 * Extend jmri.AbstractSensor for RPS systems.
 * <p>
 * System names are "RSpppp", where ppp is a representation of the region, for
 * example "RS(0,0,0);(1,0,0);(1,1,0);(0,1,0)".
 *
 * @author	Bob Jacobsen Copyright (C) 2007
 */
// /*public*/ class RpsSensor extends AbstractSensor
//        implements MeasurementListener {

/*public*/ RpsSensor::RpsSensor(QString systemName, QString prefix, QObject* parent) : AbstractSensor(systemName, parent) {
    //super(systemName);
    // create Region from all but prefix
    contents = QList<int>();
    region = new Region(systemName.mid(prefix.length() + 1)); // multichar prefix from memo
    Model::instance()->addRegion(region);
}

/*public*/ RpsSensor::RpsSensor(QString systemName, QString userName, QString prefix, QObject* parent) : AbstractSensor(systemName, userName,parent){
    //super(systemName, userName);
    contents = QList<int>();
    // create Region from all but prefix
    region = new Region(systemName.mid(prefix.length() + 1)); // multichar prefix from memo
    Model::instance()->addRegion(region);
}

//@Override
/*public*/ void RpsSensor::notify(Measurement* r) {
    QVector3D p = QVector3D(r->getX(), r->getY(), r->getZ());
    int id = (r->getReading()->getID().toInt());

    // ignore if code not OK
    if (!r->isOkPoint()) {
        return;
    }

    // ignore if not in Z fiducial volume
    if (r->getZ() > 20 || r->getZ() < -20) {
        return;
    }

    log->debug(tr("starting %1").arg(getSystemName()));
    if (region->isInside(p)) {
        notifyInRegion(id);
    } else {
        notifyOutOfRegion(id);
    }
    if (contents.size() > 0) {
        setOwnState(Sensor::ACTIVE);
    } else {
        setOwnState(Sensor::INACTIVE);
    }
}

// if somebody outside sets state to INACTIVE, clear list
//@Override
/*public*/ void RpsSensor::setOwnState(int state) {
    if (state == Sensor::INACTIVE) {
        if (contents.size() > 0) {
            contents = QList<int>();
        }
    }
    AbstractSensor::setOwnState(state);
}

Region* RpsSensor::getRegion() {
    return region;
}

QList<int> RpsSensor::getContents() {
    return contents;
}

void RpsSensor::notifyInRegion(int id) {
    // make sure region contains this Reading.getId();
    if (!contents.contains(id)) {
        contents.append(id);
        notifyArriving(id);
    }
}

void RpsSensor::notifyOutOfRegion(int id) {
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
void RpsSensor::notifyLeaving(int id) {
    firePropertyChange("Leaving", 0, id);
}

/**
 * Notify parameter listeners that a device has entered the region covered
 * by this sensor
 */
void RpsSensor::notifyArriving(int id) {
    firePropertyChange("Arriving", 0, id);
}

//@Override
/*public*/ void RpsSensor::dispose() {
    Model::instance()->removeRegion(region);
}

//@Override
/*public*/ void RpsSensor::requestUpdateFromLayout()const {
}

/*private*/ /*final*/ /*static*/ Logger* RpsSensor::log = LoggerFactory::getLogger("RpsSensor");
