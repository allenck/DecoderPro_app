#ifndef MEASUREMENTLISTENER_H
#define MEASUREMENTLISTENER_H

class Measurement;
/**
 * Connect to a source of Measurements.
 *
 * @author	Bob Jacobsen Copyright (C) 2006
 */
/*public*/ class MeasurementListener {

 /*public*/ virtual void notify(Measurement* /*r*/) {}

};
Q_DECLARE_INTERFACE(MeasurementListener, "MeasurementListener")
#endif // MEASUREMENTLISTENER_H
