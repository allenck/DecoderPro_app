#ifndef INTERNALSYSTEMCONNECTIONMEMO_H
#define INTERNALSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"
#include "instancemanagerautodefault.h"

class InternalMeterManager;
class InternalConsistManager;
class InternalLightManager;
class InternalSensorManager;
class InternalReporterManager;
class InternalTurnoutManager;
class DebugThrottleManager;
class DefaultPowerManager;
class DebugProgrammerManager;
class InternalSystemConnectionMemo : public DefaultSystemConnectionMemo, public InstanceManagerAutoDefault
{
 Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault)
public:
 Q_INVOKABLE /*public*/ InternalSystemConnectionMemo(QObject* parent=nullptr);
 InternalSystemConnectionMemo(QString prefix, QString name, bool defaultInstanceType, QObject* parent = nullptr);
 /*public*/ InternalSystemConnectionMemo(QString prefix, QString name, QObject* parent = nullptr);
 /*public*/ InternalSystemConnectionMemo(bool defaultInstanceType, QObject* parent = nullptr);
 ~InternalSystemConnectionMemo() override{}
 InternalSystemConnectionMemo(const InternalSystemConnectionMemo& other)
  : DefaultSystemConnectionMemo(other.prefix, other.userName) {}
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ void configureManagers();
 /*public*/ InternalConsistManager* getConsistManager();
 /*public*/ InternalLightManager* getLightManager() ;
 /*public*/ InternalSensorManager* getSensorManager() ;
 /*public*/ InternalReporterManager* getReporterManager();
 /*public*/ InternalTurnoutManager* getTurnoutManager();
 /*public*/ InternalMeterManager* getMeterManager();
 /*public*/ DebugThrottleManager* getThrottleManager();
 /*public*/ DefaultPowerManager* getPowerManager();
 /*public*/ DebugProgrammerManager* getProgrammerManager();
 /*public*/ bool provides(/*Class<?>*/QString type) override;
 /*public*/ Manager* get(/*Class<?>*/ QString className) override;
 /*public*/ void dispose() override;

private:
 void common(QString prefix, QString name, bool defaultInstanceType);
 bool configured = false;
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger("InternalSystemConnectionMemo");
 // if true, this is the default Internal instance, which
 // only provides a subset of types
 bool defaultInstanceType = false;

};
Q_DECLARE_METATYPE(InternalSystemConnectionMemo)
#endif // INTERNALSYSTEMCONNECTIONMEMO_H
