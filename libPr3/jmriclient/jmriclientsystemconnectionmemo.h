#ifndef JMRICLIENTSYSTEMCONNECTIONMEMO_H
#define JMRICLIENTSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"

class ReporterManager;
class LightManager;
class PowerManager;
class TurnoutManager;
class SensorManager;
class ComponentFactory;
class JMRIClientTrafficController;
class JMRIClientSystemConnectionMemo : public DefaultSystemConnectionMemo
{
 Q_OBJECT
public:
 JMRIClientSystemConnectionMemo();
 /*public*/ JMRIClientSystemConnectionMemo(JMRIClientTrafficController* jt);
 /*public*/ JMRIClientTrafficController* getJMRIClientTrafficController();
 ~JMRIClientSystemConnectionMemo() {}
 JMRIClientSystemConnectionMemo(const JMRIClientSystemConnectionMemo& other)
  : DefaultSystemConnectionMemo(other.prefix, other.userName) {}
 /*public*/ void setJMRIClientTrafficController(JMRIClientTrafficController* jt);
 /*public*/ void dispose();
 /*public*/ void configureManagers();
 /*public*/ void requestAllStatus();
 /*public*/ PowerManager* getPowerManager();
 /*public*/ void setPowerManager(PowerManager* p);
 /*public*/ SensorManager* getSensorManager();
 /*public*/ void setSensorManager(SensorManager* s);
 /*public*/ TurnoutManager* getTurnoutManager();
 /*public*/ void setTurnoutManager(TurnoutManager* t);
 /*public*/ LightManager* getLightManager();
 /*public*/ void setLightManager(LightManager *t) ;
 /*public*/ ReporterManager* getReporterManager();
 /*public*/ void setReporterManager(ReporterManager* t);
 /*public*/ void setTransmitPrefix(QString tPrefix);
 /*public*/ QString getTransmitPrefix();
 /*public*/  Manager* get(QString T);
 /*public*/ bool provides(QString type);

private:
 ComponentFactory* cf = nullptr;
 /*private*/ JMRIClientTrafficController* jt;
 /*private*/ SensorManager* sensorManager = nullptr;
 /*private*/ TurnoutManager* turnoutManager = nullptr;
 /*private*/ LightManager* lightManager = nullptr;
 /*private*/ PowerManager* powerManager = nullptr;
 /*private*/ ReporterManager* reporterManager = nullptr;
 /*private*/ QString transmitPrefix;// = null;

};
Q_DECLARE_METATYPE(JMRIClientSystemConnectionMemo)
#endif // JMRICLIENTSYSTEMCONNECTIONMEMO_H
