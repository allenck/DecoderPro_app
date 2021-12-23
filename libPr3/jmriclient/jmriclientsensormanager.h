#ifndef JMRICLIENTSENSORMANAGER_H
#define JMRICLIENTSENSORMANAGER_H
#include "abstractsensormanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientSensorManager : public AbstractSensorManager
{
public:
 JMRIClientSensorManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QString getSystemPrefix()const override;
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix)const /*throw (JmriException)*/ override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Sensor";
 }

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTSENSORMANAGER_H
