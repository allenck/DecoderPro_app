#ifndef LIGHTCONTROLTEST_H
#define LIGHTCONTROLTEST_H

#include <QObject>
#include "exceptions.h"
#include "propertychangelistener.h"
#include "junitutil.h"
#include "light.h"

class PropertyChangeEvent;
class LightControl;
class Light;
class LightControlTest : public QObject
{
 Q_OBJECT
public:
 explicit LightControlTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testCLighttor();
 /*public*/ void testLightControlCopyCtor();
 /*public*/ void testEquals();
 /*public*/ void testSetGetNames();
 /*public*/ void testInvalidControlType();
 /*public*/ void testActivateNoLight();
 /*public*/ void testSingleSensorFollower() throw (JmriException);
 /*public*/ void testNoSensor();
 /*public*/ void testNoTurnout();
 /*public*/ void testTurnoutFollower() throw (JmriException);
 /*public*/ void testFastClockFollowingOneControl() throw (TimebaseRateException);
 /*public*/ void testFastClockFollowingOneControlStartOn() throw (TimebaseRateException);
 /*public*/ void testFastClockFollowingTwoControls() throw (TimebaseRateException);
 /*public*/ void testFastClockFollowingTwoControlsOverlap() throw (TimebaseRateException);
 /*public*/ void testTimedSensorFollowing() throw (JmriException);
 /*public*/ void testNoTimedSensor();
 /*public*/ void testTwoSensorFollowingNoSensorSet();
 /*public*/ void testTwoSensorFollowing() throw (JmriException);
 /*public*/ void testTwoSensorFollowingInactive() throw (JmriException);
 /*public*/ void testUniqueTimes();

private:
 /*private*/ Light* l;
 /*private*/ LightControl* lc;
 /*private*/ int _listenerkicks;

 friend class ControlListen;
 friend class ReleaseUntilO15;
 friend class ReleaseUntilO16;
};

class ControlListen : public QObject, public PropertyChangeListener
{
 Q_OBJECT
 Q_INTERFACES(PropertyChangeListener)LightControlTest* test;
public:
 ControlListen(LightControlTest* test) { this->test = test;}
QObject* self() {return (QObject*)this;}public slots:
 //@Override
 /*public*/ void propertyChange(PropertyChangeEvent* e);

};

class ReleaseUntilO15 : public ReleaseUntil
{
 Q_OBJECT
 LightControlTest* test;
public:
 ReleaseUntilO15(LightControlTest* test) {this->test = test;}
 bool ready() throw (Exception) { return test->_listenerkicks == 6;}
};

class ReleaseUntilO16 : public ReleaseUntil
{
 Q_OBJECT
 LightControlTest* test;
public:
 ReleaseUntilO16(LightControlTest* test) {this->test = test;}
 bool ready() throw (Exception) { return Light::OFF == test->l->getState();}
};
#endif // LIGHTCONTROLTEST_H
