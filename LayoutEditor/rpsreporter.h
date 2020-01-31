#ifndef RPSREPORTER_H
#define RPSREPORTER_H
#include "abstractreporter.h"
#include "measurement.h"
#include "physicallocationreporter.h"
#include "measurementlistener.h"
class locoAddress;
class Region;
class RpsReporter : public AbstractReporter, MeasurementListener
{
 Q_OBJECT
 Q_INTERFACES (MeasurementListener)
public:
 /*public*/ RpsReporter(QString systemName, QObject* parent = 0) ;
 /*public*/ RpsReporter(QString systemName, QString userName, QObject* parent = 0);
 /*public*/ int getState();
 /*public*/ void setState(int i);
 /*public*/ void dispose();
 /*public*/ locoAddress* getLocoAddress(QString rep);
 /*public*/ PhysicalLocationReporter::Direction getDirection(QString rep);
 /*public*/ PhysicalLocation* getPhysicalLocation();
 /*public*/ PhysicalLocation* getPhysicalLocation(QString s);

public slots:
 void notify(Measurement*);
private:
     /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("RpsReporter");
 /*transient*/ Region* region;
 QList<int> contents;// = new ArrayList<Integer>();
 void notifyInRegion(int id);
 void notifyOutOfRegion(int id);
 void notifyLeaving(int id);
 void notifyArriving(int id);

};

#endif // RPSREPORTER_H
