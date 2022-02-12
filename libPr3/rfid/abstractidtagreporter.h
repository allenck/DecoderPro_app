#ifndef ABSTRACTIDTAGREPORTER_H
#define ABSTRACTIDTAGREPORTER_H
#include "abstractreporter.h"
#include "physicallocationreporter.h"
#include "idtaglistener.h"

class LocoAddress;
class IdTag;
class AbstractIdTagReporter : public AbstractReporter, public IdTagListener, public PhysicalLocationReporter
{
 Q_OBJECT
 Q_INTERFACES(IdTagListener PhysicalLocationReporter)
public:
 /*public*/ AbstractIdTagReporter(QString systemName, QObject* parent = nullptr);
 /*public*/ AbstractIdTagReporter(QString systemName, QString userName, QObject* parent = nullptr);
 ///*public*/ virtual void notify(DefaultIdTag *id);
  /*public*/ void notify(IdTag* id) override;
 /*public*/ void setState(int s)override;
 /*public*/ int getState()override;
 /*public*/ LocoAddress* getLocoAddress(QString rep)override;
 /*public*/ virtual PhysicalLocationReporter::Direction getDirection(QString rep)override;
 /*public*/ virtual PhysicalLocation *getPhysicalLocation()override;
 /*public*/ virtual PhysicalLocation* getPhysicalLocation(QString s)override;

private:
 static Logger* log;
 /*private*/ int state = PhysicalLocationReporter::UNKNOWN;
 /*private*/ void notifyPreviousReporter(Reporter* r, IdTag* id);

};

#endif // ABSTRACTIDTAGREPORTER_H
