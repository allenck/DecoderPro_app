#ifndef JMRICLIENTSENSORMANAGER_H
#define JMRICLIENTSENSORMANAGER_H
#include "abstractsensormanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientSensorManager : public AbstractSensorManager
{
public:
 JMRIClientSensorManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QString getSystemPrefix();
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName);
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTSENSORMANAGER_H
