#ifndef CODEBUTTONSIMULATOR_H
#define CODEBUTTONSIMULATOR_H

#include <QObject>
#include "nbhsensor.h"
#include "propertychangelistener.h"
#include "timer.h"
#include "actionevent.h"
#include "switchdirectionlever.h"
#include "signaldirectionlever.h"
class SwitchDirectionLever;
class SignalDirectionLever;
class TurnoutLock;
class CodeButtonSimulator : public QObject
{
  Q_OBJECT
 public:
  explicit CodeButtonSimulator(QObject *parent = nullptr);
  /*public*/ CodeButtonSimulator( int                     pauseTimeInMilliseconds,
                              NBHSensor*               codeButtonSensor,
                              SwitchDirectionLever*    switchDirectionLever,
                              SignalDirectionLever*    signalDirectionLever,
                              TurnoutLock*             turnoutLock, QObject *parent = nullptr);
  /*public*/ void removeAllListeners();

 signals:

 public slots:

 private:
  /*private*/ /*final*/ NBHSensor* _mCodeButtonSensor;
  /*private*/ /*final*/ NBHSensor* _mSwitchLeverSensor;
  /*private*/ /*final*/ NBHSensor* _mLeftSensor;
  /*private*/ /*final*/ NBHSensor* _mNormalSensor;
  /*private*/ /*final*/ NBHSensor* _mRightSensor;
  /*private*/ /*final*/ NBHSensor* _mDispatcherSensorLockToggle;
  /*private*/ /*final*/ PropertyChangeListener* _mAnySensorPropertyChangeListener;
  /*private*/ /*final*/ Timer* _mPauseTimer;
  /*private*/ /*final*/ ActionListener* _mPauseActionListener;
  /*private*/ void pauseActionListener();
  /*private*/ void anySensorPropertyChangeEvent();

  friend class AnySensorPropertyChangeListener;
  friend class PauseActionListener;
};
class AnySensorPropertyChangeListener : public PropertyChangeListener
{
  Q_OBJECT
  CodeButtonSimulator* codeButtonSimulator;
 public:
  AnySensorPropertyChangeListener(CodeButtonSimulator* codeButtonSimulator) {this->codeButtonSimulator = codeButtonSimulator;}
 public slots:
  void propertyChange(PropertyChangeEvent* e)
  {
   codeButtonSimulator->anySensorPropertyChangeEvent();
  }
};

class PauseActionListener : public ActionListener
{
  Q_OBJECT
  CodeButtonSimulator* codeButtonSimulator;
 public:
  PauseActionListener(CodeButtonSimulator* codeButtonSimulator) {this->codeButtonSimulator = codeButtonSimulator;}
 public slots:
  void actionPerformed()
  {
   codeButtonSimulator->pauseActionListener();
  }
};
#endif // CODEBUTTONSIMULATOR_H
