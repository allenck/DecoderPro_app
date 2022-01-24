#ifndef LOCKEDROUTE_H
#define LOCKEDROUTE_H

#include <QObject>
#include "propertychangeevent.h"
#include "sensor.h"
#include "reentrantlock.h"
#include "propertychangelistener.h"
#include "propertychangeevent.h"
#include <QSet>

class Sensor;
class LockedRoutesManager;
/*private*/ /*static*/ class CountedSensor : public QObject {
  Q_OBJECT
    /*private*/ /*final*/ Sensor*        _mSensor;
    /*private*/ int                 _mCount;
    /*private*/ /*final*/ ReentrantLock* _mLock = new ReentrantLock();
    /*private*/ CountedSensor(Sensor* sensor) {
        _mSensor = sensor;
        _mCount = 1;
    }
    /*private*/ Sensor* getSensor() { return _mSensor; }
    /*private*/ void lockedIncrementCount() {
        _mLock->lock();
        _mCount++;
        _mLock->unlock();
    }
    /*private*/ bool lockedDecrementCountAndCheckIfZero() {
        bool returnValue;
        _mLock->lock();
        _mCount--;                  // Can't throw
        returnValue = _mCount == 0; // Ditto
        _mLock->unlock();
        return returnValue;
    }
    /*private*/ QString dumpIt() { return _mSensor->getDisplayName() + "(" + QString::number(_mCount) + ")"; }
 friend class LockedRoute;
};

class LockedRoute : public QObject
{
  Q_OBJECT
 public:
  /*public*/ LockedRoute(LockedRoutesManager* lockedRoutesManager, QSet<Sensor*> sensors, QString osSectionDescription, QString ruleDescription, bool rightTraffic, QObject* parent = nullptr);
  /*public*/ QSet<CountedSensor*> getCountedSensors();
  /*public*/ QSet<Sensor*> getSensors();
  /*public*/ void allocateRoute();
  /*public*/ void mergeRoutes(LockedRoute* newLockedRoute);

  /*public*/ enum AnyInCommonReturn { NONE,       // NOTHING matches at all.
                                  YES,        // Absolute overlap.
                                  FLEETING };  // One overlaps, we were asked to checkDirection, and the direction matches
  /*public*/ AnyInCommonReturn anyInCommon(LockedRoute* lockedRoute, bool checkDirection, bool rightTraffic);
  /*public*/ void removeAllListeners();
  /*public*/ QString dumpRoute();

 signals:

 public slots:

 private:
  /*private*/ QSet<CountedSensor*> getCountedSensorHashSet(QSet<Sensor*> sensors);
  /*private*/ /*final*/ LockedRoutesManager* _mLockedRoutesManager;
  /*private*/ /*final*/ QString _mOSSectionDescription;                // For debugging
  /*private*/ /*final*/ QString _mRuleDescription;                     // Ditto
  /*private*/ /*final*/ QSet<CountedSensor*> _mCountedSensors;
  /*private*/ /*final*/ bool _mRightTraffic;

 private slots:
  /*private*/ void occupancyStateChange(PropertyChangeEvent* e);
  ///*private*/ /*final*/ PropertyChangeListener* _mSensorPropertyChangeListener;// = (PropertyChangeEvent e) -> { occupancyStateChange(e); };

};

#endif // LOCKEDROUTE_H
