#ifndef TURNOUTLOCK_H
#define TURNOUTLOCK_H

#include <QObject>
#include "turnout.h"
#include "nbhturnout.h"
#include "nbhsensor.h"

class NBHSensor;

class TurnoutLock : public QObject
{
  Q_OBJECT
 public:
  explicit TurnoutLock(QObject *parent = nullptr);

  /*public*/ void externalLockTurnout();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ NBHSensor _mDispatcherSensorLockToggle;
  /*private*/ int _mCommandedState = Turnout::CLOSED;  // Assume
  /*private*/ QList<NBHTurnout*> _mTurnoutsMonitored = QList<NBHTurnout*>();
  /*private*/ PropertyChangeListener* _mTurnoutsMonitoredPropertyChangeListener = nullptr;
  /*private*/ bool _mLocked = false;
  /*private*/ NBHSensor* _mDispatcherSensorUnlockedIndicator;
  /*private*/ bool _mNoDispatcherControlOfSwitch = false;
  /*private*/ int _m_ndcos_WhenLockedSwitchState = 0;

  /*private*/ void updateDispatcherSensorIndicator(bool newLockedState);

};

#endif // TURNOUTLOCK_H
