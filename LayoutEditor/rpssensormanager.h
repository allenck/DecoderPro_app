#ifndef RPSSENSORMANAGER_H
#define RPSSENSORMANAGER_H
#include "abstractsensormanager.h"

class RpsSystemConnectionMemo;
class RpsSensorManager : public AbstractSensorManager
{
 Q_OBJECT
public:
 RpsSensorManager(RpsSystemConnectionMemo* memo,QObject* parent=nullptr);
 /*public*/ SystemConnectionMemo *getMemo() const override;
 /*public*/ void dispose();
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName) override;
 /*public*/ QString createSystemName(QString curAddress, QString prefix)const /*throw (JmriException)*/ override;
 /*public*/ QString validateSystemNameFormat(QString name, QLocale locale);
 /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName) const override;
 /*public*/ QString getEntryToolTip() override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Sensor";
 }

private:
 static Logger* log;
};

#endif // RPSSENSORMANAGER_H
