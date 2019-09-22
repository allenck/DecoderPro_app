#ifndef RPSSENSOR_H
#define RPSSENSOR_H
#include "abstractsensor.h"
#include "measurementlistener.h"
class Measurement;
class Region;
class RpsSensor : public AbstractSensor, public MeasurementListener
{
 Q_INTERFACES (MeasurementListener)
public:
 /*public*/ RpsSensor(QString systemName, QString prefix, QObject* parent= nullptr);
 /*public*/ RpsSensor(QString systemName, QString userName, QString prefix, QObject* parent=nullptr);
 /*public*/ void notify(Measurement *r);
 /*public*/ void setOwnState(int state);
 void notifyInRegion(int id);
 void notifyOutOfRegion(int id);
 void notifyLeaving(int id);
 void notifyArriving(int id);
 /*public*/ void dispose();
 /*public*/ void requestUpdateFromLayout();

private:
 static Logger* log;
 Region* getRegion();
 QList<int> getContents();
 /*transient*/ Region* region;
 QList<int> contents;// = new ArrayList<Integer>();

};

#endif // RPSSENSOR_H
