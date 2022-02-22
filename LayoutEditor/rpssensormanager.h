#ifndef RPSSENSORMANAGER_H
#define RPSSENSORMANAGER_H
#include "abstractsensormanager.h"

class RpsSystemConnectionMemo;
class RpsSensorManager : public AbstractSensorManager
{
 Q_OBJECT
public:
 RpsSensorManager(RpsSystemConnectionMemo* memo,QObject* parent=nullptr);
 /*public*/ SystemConnectionMemo *getMemo()  override;
 /*public*/ void dispose()override;
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix) /*throw (JmriException)*/ override;
 /*public*/ QString validateSystemNameFormat(QString name, QLocale locale)override;
 /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName)  override;
 /*public*/ QString getEntryToolTip() override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Sensor";
 }
    QObject* vself() override {return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

private:
 static Logger* log;
};

#endif // RPSSENSORMANAGER_H
