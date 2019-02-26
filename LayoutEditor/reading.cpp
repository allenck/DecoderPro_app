#include "reading.h"
#include <QVector>

/**
 * Encodes a single set of input values (a "reading") for RPS.
 * <P>
 * The values are in time units (nominally usec), and need to be converted to
 * space units during later calculations.
 * <p>
 * The values are indexed by Receiver number, as known to the RPS system. For
 * example, getValue(2) will return the time from RPS receiver 2.
 *
 * <p>
 * Objects of this class are immutable once created.
 *
 * @author	Bob Jacobsen Copyright (C) 2006, 2008
  */
//@net.jcip.annotations.Immutable
///*public*/ class Reading {

//@SuppressFBWarnings(value = "EI_EXPOSE_REP2") // We accept the external access by design
/*public*/ Reading::Reading(QString id, QVector<double>* values, QObject *parent) : QObject(parent) {
    this->id = id;
    this->values = values;
    this->rawData = QVariant();
    this->time = 0;
}

//@SuppressFBWarnings(value = "EI_EXPOSE_REP2") // We accept the external access by design
/*public*/ Reading::Reading(QString id,QVector<double>* values, QString raw, QObject *parent) {
    this->id = id;
    this->values = values;
    this->rawData = raw;
    this->time = 0;
}

//@SuppressFBWarnings(value = "EI_EXPOSE_REP2") // We accept the external access by design
/*public*/ Reading::Reading(QString id, QVector<double>* values, int time) {
    this->id = id;
    this->values = values;
    this->rawData = QVariant();
    this->time = time;
}

/*public*/ Reading::Reading(Reading* r) {
    this->id = r->getID();
    this->values = r->getValues();
    this->rawData = QVariant();
    this->time = r->getTime();
}

/**
 * Return the time at which this Reading was requested
 */
/*public*/ int Reading::getTime() {
    return time;
}

/**
 * Return the ID int of the transmitter this reading describes
 */
/*public*/ QString Reading::getID() {
    return id;
}

/**
 * NValues is really the highest receiver number possible.
 */
/*public*/ int Reading::getNValues() {
    return values->length() - 1;
}

/**
 * Convenience method to get a specific one of the values
 */
/*public*/ double Reading::getValue(int i) {
    return values->at(i);
}

/*
 * Get the entire data array as an copy,
 * to preserve immutability
 */
/*public*/ QVector<double>* Reading::getValues() {
    QVector<double>* retval = new QVector<double>(values->length());
    for (int i = 0; i < values->length(); i++) {
        retval->replace(i, values->at(i));
    }
    return retval;
}


//@Override
/*public*/ QString Reading::toString() {
    QString b;// = new StringBuilder();
    b.append("Reading id=").append(getID()).append(" values=");
    for (int i = 1; i <= getNValues(); i++)
    {
        b.append(QString::number(getValue(i))).append(i != getNValues() ? "," : " ");
    }
    return b/*.toString()*/;
}

/**
 * Get the raw data from which this Reading was made.
 *
 * @return NULL if raw data was not preserved
 */
/*public*/ QVariant Reading::getRawData() {
    return rawData;
}

