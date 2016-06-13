#include "sensor.h"

//Sensor::Sensor(QObject *parent)
//{
//}
//const /*static*/ int Sensor::ACTIVE       =0x02;
//const /*static*/ int Sensor::INACTIVE     =0x04;
Sensor::Sensor(QObject *parent) : AbstractNamedBean(parent) {}
Sensor::Sensor(QString sysName, QObject* parent) : AbstractNamedBean(sysName, parent) {}
Sensor::Sensor(QString sysName, QString userName, QObject* parent) : AbstractNamedBean(sysName, userName, parent) {}
