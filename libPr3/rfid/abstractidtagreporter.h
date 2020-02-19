#ifndef ABSTRACTIDTAGREPORTER_H
#define ABSTRACTIDTAGREPORTER_H
#include "abstractreporter.h"
#include "physicallocationreporter.h"
#include "idtaglistener.h"

class LocoAddress;
class IdTag;
class AbstractIdTagReporter : public AbstractReporter
{
 Q_OBJECT
 //Q_INTERFACES(IdTagListener)
public:
 /*public*/ AbstractIdTagReporter(QString systemName, QObject* parent = nullptr);
 /*public*/ AbstractIdTagReporter(QString systemName, QString userName, QObject* parent = nullptr);
 /*public*/ virtual void notify(DefaultIdTag *id);
 /*public*/ void setState(int s);
 /*public*/ int getState();
 /*public*/ LocoAddress* getLocoAddress(QString rep);
 /*public*/ virtual PhysicalLocationReporter::Direction getDirection(QString rep);
 /*public*/ virtual PhysicalLocation *getPhysicalLocation();
 /*public*/ virtual PhysicalLocation* getPhysicalLocation(QString s);

private:
 static Logger* log;
 /*private*/ int state = UNKNOWN;

};

#endif // ABSTRACTIDTAGREPORTER_H
