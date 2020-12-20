#ifndef SWITCHDIRECTIONINDICATORS_H
#define SWITCHDIRECTIONINDICATORS_H

#include <QObject>
#include "nbhsensor.h"
#include "timer.h"
#include "ctcconstants.h"
#include "nbhturnout.h"
#include "propertychangeevent.h"

class SwitchDirectionIndicators : public QObject
{
  Q_OBJECT
 public:
  /*public*/ SwitchDirectionIndicators(   QString userIdentifier,
                                      NBHSensor* normalIndicatorSensor,
                                      NBHSensor* reveresedIndicatorSensor,
                                      NBHTurnout* actualTurnout,
                                      int codingTimeInMilliseconds,           // Instead of "CodingDistrict"
                                      bool feedbackDifferent, QObject *parent = nullptr);
  /*public*/ void removeAllListeners();
  /*public*/ void codeButtonPressed(int requestedState);
  /*public*/ int getLastIndicatorState();
  /*public*/ bool inCorrespondence();
  /*public*/ NBHSensor* getProperIndicatorSensor(bool isNormal);

 signals:

 public slots:

 private:
  /*private*/ NBHSensor* _mNormalIndicatorSensor;
  /*private*/ NBHSensor* _mReversedIndicatorSensor;
  /*private*/ NBHTurnout* _mActualTurnout;
  /*private*/ PropertyChangeListener* _mActualTurnoutPropertyChangeListener = nullptr;
  /*private*/ bool _mActualTurnoutHasFeedback;
  /*private*/ bool _mWaitingForFeedbackOrTimer = false;
  /*private*/ int _mLastActualTurnoutState = CTCConstants::CTC_UNKNOWN;
  /*private*/ Timer* _mSimulatedTurnoutFeedbackTimer = nullptr;
  /*private*/ ActionListener* _mSimulatedTurnoutFeedbackTimerActionListener = nullptr;
  /*private*/ int _mLastIndicatorState = CTCConstants::OUTOFCORRESPONDENCE;
  /*private*/ int getPresentState();
  /*private*/ void setSwitchIndicatorSensors(int requestedState);
  /*private*/ void setSwitchIndicationSensorsToPresentState();

  friend class ActualTurnoutPropertyChangeListener;
};

class ActualTurnoutPropertyChangeListener : public PropertyChangeListener
{
  Q_OBJECT
  SwitchDirectionIndicators* sdi;
 public:
  ActualTurnoutPropertyChangeListener(SwitchDirectionIndicators* sdi) {this->sdi = sdi;}
 public slots:
  void propertyChange(PropertyChangeEvent* e)
  {
    if (e->getPropertyName() == ("KnownState")) sdi->setSwitchIndicationSensorsToPresentState();
  }
};

class  SimulatedTurnoutFeedbackTimerActionListener : public ActionListener
{
  Q_OBJECT
  SwitchDirectionIndicators* sdi;
 public:
  SimulatedTurnoutFeedbackTimerActionListener(SwitchDirectionIndicators* sdi) {this->sdi = sdi;}
 public slots:
  void actionPerformed()
  {

  }
};
#endif // SWITCHDIRECTIONINDICATORS_H
