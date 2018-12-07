#ifndef STANDALONESENSORMANAGER_H
#define STANDALONESENSORMANAGER_H
#include "rfidsensormanager.h"

class StandaloneReply;
class StandaloneSensorManager : public RfidSensorManager
{
 Q_OBJECT
public:
 StandaloneSensorManager(RfidTrafficController* tc, QString prefix, QObject* parent = nullptr);
 /*public*/ void message(RfidMessage* m);
 /*public*/ /*synchronized*/ void reply(RfidReply* r);
 /*public*/ void dispose();

private:
 static Logger* log;
 /*private*/ /*final*/ RfidTrafficController* tc;
 /*private*/ /*final*/ QString prefix;
 /*private*/ void attach();
 /*private*/ void processReply(StandaloneReply* r);

protected:
 /*protected*/ Sensor* createNewSensor(QString systemName, QString userName);

};

#endif // STANDALONESENSORMANAGER_H
