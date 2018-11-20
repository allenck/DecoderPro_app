#ifndef INTERNALSYSTEMCONNECTIONMEMO_H
#define INTERNALSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"

class InternalConsistManager;
class InternalLightManager;
class InternalSensorManager;
class InternalReporterManager;
class InternalTurnoutManager;
class DebugThrottleManager;
class DefaultPowerManager;
class DebugProgrammerManager;
class InternalSystemConnectionMemo : public SystemConnectionMemo
{
 Q_OBJECT
public:
 InternalSystemConnectionMemo(QObject* parent = nullptr);
 ~InternalSystemConnectionMemo() {}
 InternalSystemConnectionMemo(const InternalSystemConnectionMemo&) : SystemConnectionMemo() {}
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ void configureManagers();
 /*public*/ InternalConsistManager* getConsistManager();
 /*public*/ InternalLightManager* getLightManager() ;
 /*public*/ InternalSensorManager* getSensorManager() ;
 /*public*/ InternalReporterManager* getReporterManager();
 /*public*/ InternalTurnoutManager* getTurnoutManager();
 /*public*/ DebugThrottleManager* getThrottleManager();
 /*public*/ DefaultPowerManager* getPowerManager();
 /*public*/ DebugProgrammerManager* getProgrammerManager();
 /*public*/ bool provides(/*Class<?>*/QString type);
 /*public*/ QObject* get(/*Class<?>*/ QString className);
 /*public*/ void dispose();

private:
 bool configured;// = false;
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("InternalSystemConnectionMemo");
 /*private*/ InternalConsistManager* consistManager;
 /*private*/ InternalLightManager* lightManager;
 /*private*/ InternalSensorManager* sensorManager;
 /*private*/ InternalReporterManager* reporterManager;
 /*private*/ InternalTurnoutManager* turnoutManager;
 /*private*/ DebugThrottleManager* throttleManager;
 /*private*/ DefaultPowerManager* powerManager;
 /*private*/ DebugProgrammerManager* programManager;

};
Q_DECLARE_METATYPE(InternalSystemConnectionMemo)
#endif // INTERNALSYSTEMCONNECTIONMEMO_H
