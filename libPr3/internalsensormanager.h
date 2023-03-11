#ifndef INTERNALSENSORMANAGER_H
#define INTERNALSENSORMANAGER_H
#include "abstractsensormanager.h"
#include "abstractsensor.h"
#include "libPr3_global.h"
#include "preferNumericComparator.h"

class InternalSystemConnectionMemo;
class AbstractSensorManager;
class LIBPR3SHARED_EXPORT InternalSensorManager : public AbstractSensorManager
{
 Q_OBJECT
public:
    QT_DEPRECATED InternalSensorManager(QObject* parent = nullptr);
    InternalSensorManager(InternalSystemConnectionMemo *memo, QObject* parent = nullptr);

    /*public*/ InternalSensorManager(QString prefix, QObject* parent = nullptr);
    /*public*/ static /*synchronized*/ void setDefaultStateForNewSensors(int defaultSetting);
    /*public*/ static /*synchronized*/ int getDefaultStateForNewSensors();
    /*public*/ bool allowMultipleAdditions(QString systemName) override;
    /*public*/ QString getNextValidAddress(QString curAddress, QString prefix) override;
    // /*public*/ QString getSystemPrefix();
    /*public*/ SystemConnectionMemo* getMemo() override;
    /*public*/ QString getEntryToolTip() override;
    /*public*/ QString getNamedBeanClass()const override {
        return "Sensor";
    }
    /*public*/ QString toString() override {return "InternalSensorManager";}
    QObject* vself() override { return (QObject*)this;}
    QObject* mself() override { return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

    void addPropertyChangeListener(PropertyChangeListener* l) override {PropertyChangeSupport::addPropertyChangeListener(l);}

private:
 static Logger* log;

private:
 static int defaultState;// = Sensor::UNKNOWN;

 protected:

 /**
  * Create an internal (dummy) sensor object
  * @return new null
  */
 /*protected*/ Sensor* createNewSensor(QString systemName, QString userName) override;
 /*protected*/ QString prefix;// = "I";
 friend class InternalSensorManagerXml;
 friend class SensorTableAction;
 friend class JUnitUtil;
};

class InternalAbstractSensor : public AbstractSensor
{
 Q_OBJECT
public:
 InternalAbstractSensor(QString systemName, QString userName) : AbstractSensor(systemName, userName) {}
 /*public*/ void requestUpdateFromLayout() const {
  // nothing to do
 }
 //@Override
 /*public*/ int compareSystemNameSuffix(/*@Nonnull*/ QString suffix1, /*@Nonnull*/ QString suffix2, NamedBean* n) override{
     return (new PreferNumericComparator())->compare(suffix1, suffix2);
 }
};

#endif // INTERNALSENSORMANAGER_H
