#ifndef JMRICLIENTSENSORMANAGER_H
#define JMRICLIENTSENSORMANAGER_H
#include "abstractsensormanager.h"

class JMRIClientSystemConnectionMemo;
class JMRIClientSensorManager : public AbstractSensorManager
{
public:
 JMRIClientSensorManager(JMRIClientSystemConnectionMemo* memo, QObject* parent = nullptr);
 /*public*/ QString getSystemPrefix() const override;
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/ override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Sensor";
 }
 /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
 QObject* vself() override { return (QObject*)this;}
 QObject* pself() override{return (QObject*)this;}

private:
 /*private*/ JMRIClientSystemConnectionMemo* memo = nullptr;
 /*private*/ QString prefix;// = null;

};

#endif // JMRICLIENTSENSORMANAGER_H
