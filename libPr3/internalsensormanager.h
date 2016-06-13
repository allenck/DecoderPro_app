#ifndef INTERNALSENSORMANAGER_H
#define INTERNALSENSORMANAGER_H
#include "abstractsensormanager.h"
#include "abstractsensor.h"
#include "libPr3_global.h"

class AbstractSensorManager;
class LIBPR3SHARED_EXPORT InternalSensorManager : public AbstractSensorManager
{
 Q_OBJECT
public:
    InternalSensorManager();
private:
 Logger log;
protected:
/*public*/ bool allowMultipleAdditions(QString systemName);
/*public*/ QString getNextValidAddress(QString curAddress, QString prefix);
/*public*/ QString getSystemPrefix();
/*public*/ static /*synchronized*/ void setDefaultStateForNewSensors(int defaultSetting);
/*public*/ static /*synchronized*/ int getDefaultStateForNewSensors();

private:
 static int defaultState;// = Sensor::UNKNOWN;
/**
 * Create an internal (dummy) sensor object
 * @return new null
 */
/*protected*/ Sensor* createNewSensor(QString systemName, QString userName);
/*protected*/ QString prefix;// = "I";
friend class InternalSensorManagerXml;
friend class SensorTableAction;
};
class InternalAbstractSensor : public AbstractSensor
{
 Q_OBJECT
public:
 InternalAbstractSensor(QString systemName, QString userName) : AbstractSensor(systemName, userName) {}
 /*public*/ void requestUpdateFromLayout() const {}
};

#endif // INTERNALSENSORMANAGER_H
