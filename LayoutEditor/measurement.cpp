#include "measurement.h"
#include <QVector3D>
/**
 * Encodes a single measurement point for RPS
 * <P>
 * Immutable
 *
 * @author	Bob Jacobsen Copyright (C) 2006
  */
// /*public*/ class Measurement {

/*public*/ Measurement::Measurement(Reading* r, QObject *parent) : QObject(parent)
{
 valid = true;

    this->r = r;
}

/*public*/ Measurement::Measurement(Reading* r, double x, double y, double z, double vsound, int code,
                                    QString source, QObject *parent) : QObject(parent)
{
    //this(r);
  valid = true;

    this->x = x;
    this->y = y;
    this->z = z;
    this->vsound = vsound;
    this->code = code;
    this->source = source;
}

/**
 * Return the Reading this measurement made from.
 * <P>
 * By definition, Reading objects are immutable
 *
 */
/*public*/ Reading* Measurement::getReading() {
    return r;
}

/**
 * Return the ID int of the transmitter this measurement describes
 */
/*public*/ QString Measurement::getID() {
    if (r == NULL) {
        return "<none>";
    }
    return r->getID();
}

/*public*/ double Measurement::getX() {
    return x;
}

/*public*/ double Measurement::getY() {
    return y;
}

/*public*/ double Measurement::getZ() {
    return z;
}

/*public*/ double Measurement::getVSound() {
    return vsound;
}

/*public*/ bool Measurement::isValidPosition() {
    if (!valid) {
        return false;
    }
    return !(qAbs(x) > 1.E10 || qAbs(x) > 1.E10 || qAbs(x) > 1.E10);
}

/*public*/ void Measurement::setValidPosition(bool val) {
    valid = val;
}

/**
 * Error code, defined specifically by generator
 */
/*public*/ int Measurement::getCode() {
    return code;
}

/**
 * Should this be considered a valid measurement?
 */
/*public*/ bool Measurement::isOkPoint() {
    if (getCode() > 0) {
        return true;
    }
    return false;
}

/**
 * Get the error code as a human-readable string
 */
/*public*/ QString Measurement::textCode() {
    return "" + getCode();
}

/*public*/ QVector3D Measurement::getPoint() {
    return QVector3D(x, y, z);
}

/*public*/ QVector3D Measurement::getVector() {
    return QVector3D(x, y, z);
}

/**
 * Get name of the source
 */
/*public*/ QString Measurement::getSource() {
    return source;
}



/*public*/ QString Measurement::toString() {
    if (!isValidPosition()) {
        // out-of-range
        return "Measurement id=" + getID() + " invalid position";
    }
    return "Measurement id=" + getID() + " position= "
            + truncate(x) + ", " + truncate(y) + ", " + truncate(z);
}

// provide a quick decimal truncation for formatting
double Measurement::truncate(double x) {
    return (int) qRound(x * 10) / 10.;
}
