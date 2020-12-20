#ifndef TURNOUTLOCK_H
#define TURNOUTLOCK_H

#include <QObject>
#include "turnout.h"
#include "nbhturnout.h"
#include "nbhsensor.h"
#include "codebuttonhandlerdata.h"

class NBHSensor;

class TurnoutLock : public QObject
{
  Q_OBJECT
 public:
  /*public*/ TurnoutLock( QString userIdentifier,
                      NBHSensor* dispatcherSensorLockToggle,          // Toggle switch that indicates lock/unlock on the panel.  If None, then PERMANENTLY locked by the Dispatcher!
                      NBHTurnout* actualTurnout,                       // The turnout being locked: LTxx a real turnout, like LT69.
                      bool actualTurnoutFeedbackDifferent,     // True / False, in case feedback backwards but switch command above isn't!
                      NBHSensor* dispatcherSensorUnlockedIndicator,   // Display unlocked status (when ACTIVE) back to the Dispatcher.
                      bool noDispatcherControlOfSwitch,        // Dispatcher doesn't control the switch.  If TRUE, then provide:
                      int ndcos_WhenLockedSwitchState,            // When Dispatcher does lock, switch should be set to: CLOSED/THROWN
                      CodeButtonHandlerData::LOCK_IMPLEMENTATION _mLockImplementation,  // Someday, choose which one to implement.  Right now, my own.
                      bool turnoutLocksEnabledAtStartup,
                      NBHTurnout* additionalTurnout1,
                      bool additionalTurnout1FeebackReversed,
                      NBHTurnout* additionalTurnout2,
                      bool additionalTurnout2FeebackReversed,
                      NBHTurnout* additionalTurnout3,
                      bool additionalTurnout3FeebackReversed, QObject *parent = nullptr);


  /*public*/ void externalLockTurnout();
  /*public*/ void externalUnlockTurnout();
  /*public*/ void codeButtonPressed();
  /*public*/ void dispatcherCommandedState(int commandedState);
  /*public*/ bool turnoutPresentlyLocked();
  /*public*/ bool getNewLockedState();
  /*public*/ bool tryingToChangeLockStatus();
  /*public*/ void removeAllListeners();
  /*public*/ NBHSensor* getDispatcherSensorLockToggle();


 signals:

 public slots:

 private:
  /*private*/ /*final*/ NBHSensor* _mDispatcherSensorLockToggle;
  /*private*/ int _mCommandedState = Turnout::CLOSED;  // Assume
  /*private*/ QList<NBHTurnout*> _mTurnoutsMonitored = QList<NBHTurnout*>();
  /*private*/ PropertyChangeListener* _mTurnoutsMonitoredPropertyChangeListener = nullptr;
  /*private*/ bool _mLocked = false;
  /*private*/ NBHSensor* _mDispatcherSensorUnlockedIndicator;
  /*private*/ bool _mNoDispatcherControlOfSwitch = false;
  /*private*/ int _m_ndcos_WhenLockedSwitchState = 0;

  /*private*/ void updateDispatcherSensorIndicator(bool newLockedState);
  /*private*/ void turnoutSetCommandedState(NBHTurnout *turnout, int state);
  /*private*/ void addTurnoutMonitored(QString userIdentifier, QString parameter, NBHTurnout* actualTurnout, bool FeedbackDifferent, bool required);
  /*private*/ void handleTurnoutChange(PropertyChangeEvent *e);

  friend class TurnoutsMonitoredPropertyChangeListener;
};

class TurnoutsMonitoredPropertyChangeListener : public PropertyChangeListener
{
  Q_OBJECT
  TurnoutLock* turnoutLock;
 public:
  TurnoutsMonitoredPropertyChangeListener(TurnoutLock* turnoutLock) {this->turnoutLock = turnoutLock;}
 public slots:
  void propertyChange(PropertyChangeEvent* e)
  {
   turnoutLock->handleTurnoutChange(e);
  }
};
#endif // TURNOUTLOCK_H
