#include "rfidsensor.h"

RfidSensor::RfidSensor(QObject *parent) :
    AbstractSensor(parent)
{
 contents = new QVector<int>();
}
/**
 * Extend jmri.AbstractSensor for RFID systems
 * <P>
 * System names are "FSpppp", where ppp is a
 * representation of the RFID reader.
 * <P>
 * @author	Bob Jacobsen Copyright (C) 2007
 * @author      Matthew Harris  Copyright (C) 2011
 * @version     $Revision: 17977 $
 * @since       2.11.4
 */
///*public*/ class RfidSensor extends AbstractSensor
//                    implements RfidTagListener {

/*public*/ RfidSensor::RfidSensor(QString systemName,QObject *parent) :AbstractSensor(systemName.toUpper(), parent)
{
    //super(systemName);
    contents = new QVector<int>();
}

/*public*/ RfidSensor::RfidSensor(QString systemName, QString userName,QObject *parent) : AbstractSensor(systemName.toUpper(), userName,parent)
{
    //super(systemName, userName);
    contents = new QVector<int>();
}

/*public*/ void RfidSensor::notify(DefaultIdTag* r) {
    setOwnState(r!=NULL?/*Sensor::ACTIVE*/0x02:/*Sensor::INACTIVE*/0x04);
}

// if somebody outside sets state to INACTIVE, clear list
//@Override
/*public*/ void RfidSensor::setOwnState(int state) {
    if (state == /*Sensor::INACTIVE*/0x04) {
        if (contents->size() > 0 )
            contents = new QVector<int>();
    }
    //super.setOwnState(state);
    AbstractSensor::setOwnState(state);
}

QList<int> RfidSensor::getContents() {
    return contents->toList();
}

void RfidSensor::notifyInRegion(int id) {
    // make sure region contains this Reading.getId();
    if (!contents->contains(id)) {
        contents->append(id);
        notifyArriving(id);
    }
}

void RfidSensor::notifyOutOfRegion(int id) {
    // make sure region does not contain this Reading.getId();
    if (contents->contains(id)) {
        contents->remove(contents->indexOf(id));
        notifyLeaving(id);
    }
}


/**
 * Notify parameter listeners that
 * a device has left the region covered by
 * this sensor
 */
void RfidSensor::notifyLeaving(int id) {
    firePropertyChange("Leaving", QVariant(), QVariant(id));
}

/**
 * Notify parameter listeners that
 * a device has entered the region covered by
 * this sensor
 */
void RfidSensor::notifyArriving(int id) {
    firePropertyChange("Arriving", QVariant(), QVariant(id));
}

//@Override
/*public*/ void RfidSensor::dispose() {
//        Model.instance().removeRegion(region);
}

/*public*/ void requestUpdateFromLayout() {
}


