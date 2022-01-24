#ifndef JMRICLIENTSYSTEMCONNECTIONMEMO_H
#define JMRICLIENTSYSTEMCONNECTIONMEMO_H
#include "defaultsystemconnectionmemo.h"

class AbstractTurnoutManager;
class AbstractLightManager;
class AbstractReporterManager;
class AbstractPowerManager;
class AbstractSensorManager;
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
 Q_INVOKABLE JMRIClientSystemConnectionMemo(QObject* parent = nullptr);
 /*public*/ JMRIClientSystemConnectionMemo(JMRIClientTrafficController* jt, QObject* parent = nullptr);
 /*public*/ JMRIClientTrafficController* getJMRIClientTrafficController();
 ~JMRIClientSystemConnectionMemo() {}
 JMRIClientSystemConnectionMemo(const JMRIClientSystemConnectionMemo& other)
  : DefaultSystemConnectionMemo(other.prefix, other.userName) {}
 /*public*/ void setJMRIClientTrafficController(JMRIClientTrafficController* jt);
 /*public*/ void dispose();
 /*public*/ void configureManagers();
 /*public*/ void requestAllStatus();
 /*public*/ AbstractPowerManager *getPowerManager();
 /*public*/ void setPowerManager(AbstractPowerManager *p);
 /*public*/ AbstractSensorManager *getSensorManager();
 /*public*/ void setSensorManager(AbstractSensorManager *s);
 /*public*/ TurnoutManager* getTurnoutManager();
 /*public*/ void setTurnoutManager(AbstractTurnoutManager *t);
 /*public*/ LightManager* getLightManager();
 /*public*/ void setLightManager(AbstractLightManager *t) ;
 /*public*/ ReporterManager* getReporterManager();
 /*public*/ void setReporterManager(AbstractReporterManager *t);
 /*public*/ void setTransmitPrefix(QString tPrefix);
 /*public*/ QString getTransmitPrefix();
 /*public*/  Manager* get(QString T);
 /*public*/ bool provides(QString type);

private:
 void common();
 ComponentFactory* cf = nullptr;
 /*private*/ JMRIClientTrafficController* jt;
 /*private*/ AbstractSensorManager* sensorManager = nullptr;
 /*private*/ AbstractTurnoutManager* turnoutManager = nullptr;
 /*private*/ AbstractLightManager* lightManager = nullptr;
 /*private*/ AbstractPowerManager* powerManager = nullptr;
 /*private*/ AbstractReporterManager* reporterManager = nullptr;
 /*private*/ QString transmitPrefix;// = null;

};
Q_DECLARE_METATYPE(JMRIClientSystemConnectionMemo)
#endif // JMRICLIENTSYSTEMCONNECTIONMEMO_H
