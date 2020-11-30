#ifndef CONTROLPANELTEST_H
#define CONTROLPANELTEST_H

#include <QObject>
#include "jframe.h"
#include "dccthrottle.h"
#include "controlpanel.h"

class ControlPanelTest : public QObject
{
    Q_OBJECT
public:
    explicit ControlPanelTest(QObject *parent = nullptr);
    Q_INVOKABLE /*public*/ void setUp();
    Q_INVOKABLE /*public*/ void tearDown();
    /*public*/ void testSpeedStepModes(SpeedStepMode::SSMODES mode);

signals:

public slots:
    /*public*/ void testCtor();
    /*public*/ void testExtendedThrottle();
    /*public*/ void testIconThrottle();

private:
    ControlPanel* panel;
    JFrame* frame;
    DccThrottle* throttle;
    /*private*/ void setupControlPanel();
    /*private*/ void checkFrameOverlap(QWidget *f);
friend class CPTThrottleListener;
};

class CPTThrottleListener : public QObject, public ThrottleListener
{
  Q_OBJECT
    Q_INTERFACES(ThrottleListener)
    ControlPanelTest* test;
    SpeedStepMode::SSMODES mode;
public:
    CPTThrottleListener(SpeedStepMode::SSMODES mode, ControlPanelTest* test) {
        this->test = test;
        this->mode = mode;
    }
    QObject* self() {return (QObject*)this;}
public slots:
  //@Override
  /*public*/ void notifyThrottleFound(DccThrottle* t) {
    test->throttle = t;
    test->throttle->setSpeedStepMode(mode);
    test->panel->notifyAddressThrottleFound(t);
  }

  //@Override
  /*public*/ void notifyFailedThrottleRequest(LocoAddress* address,
      QString reason) {
  }
  //@Override
  /*public*/ void notifyDecisionRequired(LocoAddress* address,
      DecisionType question) {
  }
};

#endif // CONTROLPANELTEST_H
