#ifndef RPSSENSORMANAGER_H
#define RPSSENSORMANAGER_H
#include "abstractsensormanager.h"

class RpsSystemConnectionMemo;
class RpsSensorManager : public AbstractSensorManager
{
 Q_OBJECT
public:
 RpsSensorManager(RpsSystemConnectionMemo* memo,QObject* parent=nullptr);
 /*public*/ SystemConnectionMemo *getMemo();
 /*public*/ void dispose();
 /*public*/ Sensor* createNewSensor(QString systemName, QString userName);
 /*public*/ QString createSystemName(QString curAddress, QString prefix) throw (JmriException);
 /*public*/ QString validateSystemNameFormat(QString name, QLocale locale);
 /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName);
 /*public*/ QString getEntryToolTip();
private:
 static Logger* log;
};

#endif // RPSSENSORMANAGER_H
