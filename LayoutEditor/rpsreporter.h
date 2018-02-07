#ifndef RPSREPORTER_H
#define RPSREPORTER_H
#include "abstractreporter.h"
#include "measurement.h"
#include "physicallocationreporter.h"

class LocoAddress;
class Region;
class RpsReporter : public AbstractReporter
{
 Q_OBJECT
public:
 /*public*/ RpsReporter(QString systemName, QObject* parent = 0) ;
 /*public*/ RpsReporter(QString systemName, QString userName, QObject* parent = 0);
 /*public*/ int getState();
 /*public*/ void setState(int i);
 /*public*/ void dispose();
 /*public*/ LocoAddress* getLocoAddress(QString rep);
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
