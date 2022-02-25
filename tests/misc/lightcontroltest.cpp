#include "lightcontroltest.h"
#include "assert1.h"
#include "abstractlight.h"
#include "junitappender.h"
#include "lightmanager.h"
#include "gregoriancalendar.h"
#include "defaultlightcontrol.h"

LightControlTest::LightControlTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the DefaultLightControl* class
 *
 * @author Paul Bender Copyright (C) 2016
 * @author Steve Young Copyright (C) 2019
 */
///*public*/ class DefaultLightControlTest {

//@Test
/*public*/ void LightControlTest::testCtor() {
    LightControl* l = new DefaultLightControl();
//    Assert::assertNotNull("DefaultLightControl* not null", l, __FILE__, __LINE__);
}

//@Test
/*public*/ void LightControlTest::testCLighttor() {
    Light* o = new AbstractLight("IL1", "test light");
    DefaultLightControl* l = new DefaultLightControl(o);
    Assert::assertNotNull("DefaultLightControl* not null", l, __FILE__, __LINE__);
}

//@Test
/*public*/ void LightControlTest::testLightControlCopyCtor() {
    DefaultLightControl* l = new DefaultLightControl();
    DefaultLightControl* copyOfl = new DefaultLightControl(l);
    Assert::assertNotNull("DefaultLightControl* Copy not null", copyOfl, __FILE__, __LINE__);
}

//@Test
//@SuppressWarnings("unlikely-arg-type") // String seems to be unrelated to DefaultLightControl
/*public*/ void LightControlTest::testEquals() {
    Light* o = new AbstractLight("IL1", "test light");
    DefaultLightControl* l1 = new DefaultLightControl(o);

    Assert::assertFalse(l1->equals(nullptr), __FILE__, __LINE__);
    Assert::assertTrue(l1->equals(l1), __FILE__, __LINE__);
    Assert::assertFalse(l1->equals(nullptr), __FILE__, __LINE__);

    DefaultLightControl* l2 = new DefaultLightControl(o);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlType(999);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(999);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);
    JUnitAppender::assertWarnMessage("Unexpected _controlType = 999", __FILE__, __LINE__);

    l1->setControlType(Light::SENSOR_CONTROL);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(Light::SENSOR_CONTROL);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlSensorName("S2");
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlSensorName("S2");
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlSensorSense(Sensor::ACTIVE);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__); // default is ACTIVE

    l1->setControlSensorSense(Sensor::INACTIVE);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlSensorSense(Sensor::INACTIVE);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlType(Light::FAST_CLOCK_CONTROL);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(Light::FAST_CLOCK_CONTROL);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setFastClockControlSchedule(0, 0, 0, 0); // onHr, OnMin, OffHr, OffMin  default
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setFastClockControlSchedule(1, 0, 0, 0); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l1->setFastClockControlSchedule(0, 1, 0, 0); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l1->setFastClockControlSchedule(0, 0, 1, 0); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l1->setFastClockControlSchedule(0, 0, 0, 1); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlType(Light::TURNOUT_STATUS_CONTROL);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(Light::TURNOUT_STATUS_CONTROL);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlTurnout("T1");
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlTurnout("T1");
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlTurnoutState(Turnout::CLOSED); // default CLOSED
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlTurnoutState(Turnout::THROWN);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlTurnoutState(Turnout::THROWN);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlType(Light::TIMED_ON_CONTROL);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(Light::TIMED_ON_CONTROL);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlTimedOnSensorName("S1");
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlTimedOnSensorName("S1");
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setTimedOnDuration(77);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setTimedOnDuration(77);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlType(Light::TWO_SENSOR_CONTROL);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlType(Light::TWO_SENSOR_CONTROL);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlSensorName("S1");
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlSensorName("S1");
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlSensor2Name("S2");
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlSensor2Name("S2");
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    l1->setControlSensorSense(Sensor::ACTIVE);
    Assert::assertFalse(l1->equals(l2), __FILE__, __LINE__);
    l2->setControlSensorSense(Sensor::ACTIVE);
    Assert::assertTrue(l1->equals(l2), __FILE__, __LINE__);

    Assert::assertNotNull("Has Hashcode", l1->hashCode(), __FILE__, __LINE__);

}

//@Test
/*public*/ void LightControlTest::testSetGetNames() {
    // used while editing the control with no Sensors / turnouts etc. attached
    DefaultLightControl* t = new DefaultLightControl();
    t->setControlSensorName("MySensor");
    Assert::assertEquals("Same Name", "MySensor", t->getControlSensorName(), __FILE__, __LINE__);

    t->setControlTimedOnSensorName("Shirley");
    Assert::assertEquals("Same Name", "Shirley", t->getControlTimedOnSensorName(), __FILE__, __LINE__);

    t->setControlSensor2Name("DownMain7");
    Assert::assertEquals("Same Name", "DownMain7", t->getControlSensor2Name(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LightControlTest::testInvalidControlType() {
    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    lc = new DefaultLightControl(l);
    lc->activateLightControl();
    JUnitAppender::assertErrorMessage("Unexpected control type when activating Light: ILL1", __FILE__, __LINE__);
}

//@Test
/*public*/ void LightControlTest::testActivateNoLight() {
    lc = new DefaultLightControl();
    lc->activateLightControl();
    JUnitAppender::assertErrorMessage("No Parent Light when activating DefaultLightControl", __FILE__, __LINE__);
}

//@Test
/*public*/ void LightControlTest::testSingleSensorFollower() /*throw (JmriException)*/ {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Sensor* s = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S2");

    int startListeners = s->getPropertyChangeListeners().length();

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::SENSOR_CONTROL);
    lc->setControlSensorName("S2");
    lc->setControlSensorSense(Sensor::ACTIVE);

    l->addLightControl(lc);
    l->activateLight();

    Assert::assertEquals("+1 listener", startListeners + 1, s->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, s->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    s->setState(Sensor::ON);
    Assert::assertEquals("ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    s->setState(Sensor::OFF);
    Assert::assertEquals("OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    s->setState(Sensor::ON);
    Assert::assertEquals("ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    Assert::assertEquals("releases listener", startListeners, s->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    lc->setControlSensorSense(Sensor::INACTIVE);
    Assert::assertEquals("ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    l->activateLight();
    Assert::assertEquals("OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    s->setState(Sensor::OFF);
    Assert::assertEquals("ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    s->setState(Sensor::ON);
    Assert::assertEquals("OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->setEnabled(false);
    s->setState(Sensor::OFF);
    Assert::assertEquals("does not change", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();

}

//@Test
/*public*/ void LightControlTest::testNoSensor() {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    lc = new DefaultLightControl(l);
    lc->setControlType(Light::SENSOR_CONTROL);

    l->addLightControl(lc);
    l->activateLight();
    JUnitAppender::assertErrorMessage("Light ILL1 is linked to a Sensor that does not exist:", __FILE__, __LINE__);

}

//@Test
/*public*/ void LightControlTest::testNoTurnout() {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TURNOUT_STATUS_CONTROL);

    l->addLightControl(lc);
    l->activateLight();
    JUnitAppender::assertErrorMessageStartsWith("Invalid system name for Turnout: System name must start with \"IT\".", __FILE__, __LINE__);
    JUnitAppender::assertErrorMessageStartsWith("Light ILL1 is linked to a Turnout that does not exist", __FILE__, __LINE__);

    lc->setControlTurnoutState(999);
    JUnitAppender::assertErrorMessageStartsWith("Incorrect Turnout State Set", __FILE__, __LINE__);

}

//@Test
/*public*/ void LightControlTest::testTurnoutFollower() /*throw (JmriException)*/ {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Turnout* t = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("T1");

    int startListeners = t->getPropertyChangeListeners().length();

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TURNOUT_STATUS_CONTROL);
    lc->setControlTurnout("T1");
    lc->setControlTurnoutState(Turnout::THROWN);

    l->addLightControl(lc);
    l->activateLight();

    Assert::assertEquals("+1 listener", startListeners + 1, t->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    Assert::assertEquals("Turnout unknown state", Turnout::UNKNOWN, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    t->setState(Turnout::THROWN);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::CLOSED);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::THROWN);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::UNKNOWN);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::CLOSED);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    Assert::assertEquals("releases turnout listener", startListeners, t->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    lc->setControlTurnoutState(Turnout::CLOSED);

    l->activateLight();
    Assert::assertEquals("Activation polls the Turnout", Light::ON, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::THROWN);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    t->setState(Turnout::CLOSED);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    l->setEnabled(false);
    t->setState(Turnout::THROWN);
    Assert::assertEquals("does not update when light not enabled", Light::ON, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();

}

//@Test
/*public*/ void LightControlTest::testFastClockFollowingOneControl() throw (TimebaseRateException) {
    Timebase* timebase = (Timebase*)InstanceManager::getDefault("Timebase");
    timebase->setRun(false);
    Calendar* cal = new GregorianCalendar();
    cal->set(2018, 1, 12, 2, 00, 00); // 02:00:00
    timebase->setTime(cal->getTime());

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");

    Assert::assertEquals("OFF state by default", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default
    Assert::assertEquals("enabled by default", true, l->getEnabled(), __FILE__, __LINE__); // lights are enabled by default

    int startListeners = timebase->getMinuteChangeListeners().length();

    lc = new DefaultLightControl();
    lc->setParentLight((AbstractLight*)l->self());
    lc->setControlType(Light::FAST_CLOCK_CONTROL);
    lc->setFastClockControlSchedule(3, 0, 4, 0); // onHr, OnMin, OffHr, OffMin

    Assert::assertTrue("Total On Time",180==lc->getFastClockOnCombined(), __FILE__, __LINE__);
    Assert::assertTrue("Total Off Time",240==lc->getFastClockOffCombined(), __FILE__, __LINE__);

    l->addLightControl(lc);
    l->activateLight();
    Assert::assertEquals("+1 listener", startListeners + 1, timebase->getMinuteChangeListeners().length(), __FILE__, __LINE__);
    // JUnitUtil->waitFor(()->{return l->getState()==Light::OFF;},"Light goes OFF at 02:00");
    Assert::assertEquals("OFF at 02:00 when control 03:00 - 04:00", Light::OFF, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 2, 59, 00); // 02:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("OFF at 02:59 when control 03:00 - 04:00", Light::OFF, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 00, 00); // 03:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("ON at 03:00 when control 03:00 - 04:00", Light::ON, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 59, 00); // 03:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("ON at 03:59 when control 03:00 - 04:00", Light::ON, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 00, 00); // 04:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("OFF at 04:00 when control 03:00 - 04:00", Light::OFF, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 01, 00); // 04:01:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("OFF at 04:01 when control 03:00 - 04:00", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();

    Assert::assertEquals("listener removed", startListeners, timebase->getMinuteChangeListeners().length(), __FILE__, __LINE__);

    ((AbstractNamedBean*)l->self())->dispose();
}

//@Test
/*public*/ void LightControlTest::testFastClockFollowingOneControlStartOn() throw (TimebaseRateException) {
    Timebase* timebase = (Timebase*)InstanceManager::getDefault("Timebase");
    timebase->setRun(false);
    Calendar* cal = new GregorianCalendar();
    cal->set(2018, 1, 12, 21, 00, 00); // 21:00:00
    timebase->setTime(cal->getTime());

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Assert::assertEquals("OFF state by default", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::FAST_CLOCK_CONTROL);
    lc->setFastClockControlSchedule(18, 0, 7, 0); // onHr, OnMin, OffHr, OffMin

    l->addLightControl(lc);
    l->activateLight();
    Assert::assertEquals("ON when starting at 21:00 control 18:00 - 07:00", Light::ON, l->getState(), __FILE__, __LINE__);

    l->setState(Light::OFF);
    Assert::assertEquals("goes OFF when set by something else", Light::OFF, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 21, 01, 00); // 21:01:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes back ON on next minute update", Light::ON, l->getState(), __FILE__, __LINE__);

    l->setEnabled(false);

    cal->set(2018, 1, 12, 7, 59, 00); // 07:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("Light still on", Light::ON, l->getState(), __FILE__, __LINE__);

    cal->set(2018, 1, 12, 8, 00, 00); // 08:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("Light still on as not enabled", Light::ON, l->getState(), __FILE__, __LINE__);

    l->setEnabled(true);

    cal->set(2018, 1, 12, 8, 01, 00); // 08:01:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("Light goes off on next update re-enabled", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();
}

//@Test
/*public*/ void LightControlTest::testFastClockFollowingTwoControls() throw (TimebaseRateException) {
    Timebase* timebase = (Timebase*)InstanceManager::getDefault("Timebase");
    timebase->setRun(false);
    Calendar* cal = new GregorianCalendar();
    cal->set(2018, 1, 12, 21, 00, 00); // 21:00:00
    timebase->setTime(cal->getTime());

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Assert::assertEquals("OFF state by default", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::FAST_CLOCK_CONTROL);
    lc->setFastClockControlSchedule(3, 0, 4, 0); // onHr, OnMin, OffHr, OffMin

    DefaultLightControl* lcb = new DefaultLightControl(l);
    lcb->setControlType(Light::FAST_CLOCK_CONTROL);
    lcb->setFastClockControlSchedule(5, 0, 6, 0); // onHr, OnMin, OffHr, OffMin

    l->addLightControl(lc);
    l->addLightControl(lcb);
    l->activateLight();
    Assert::assertEquals("OFF starting at 21:00 controls 03:00-04:00, 05:00-06:00", Light::OFF, l->getState(), __FILE__, __LINE__);

    // adding the PCL to check that we don't get flickering on the Light
    // ie "normal" amount of PCEvents for a state change.
    // NOT testing the actual PCListeners
    ((AbstractNamedBean*)l->self())->addPropertyChangeListener(new ControlListen(this));

    cal->set(2018, 1, 12, 2, 59, 00); // 02:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("0 Light PropertyChangeEvents", 0, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 00, 00); // 03:00:00
    timebase->setTime(cal->getTime());
    // JUnitUtil->waitFor(()->{return l->getState()==Light::ON;},"Light goes ON at 03:00");
    Assert::assertEquals("goes ON", Light::ON, l->getState(), __FILE__, __LINE__);

    // At time of writing there are 2 PCE's on Light state change
    // "TargetIntensity" and "KnownState"
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 59, 00); // 03:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 00, 00); // 04:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents", 4, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 59, 00); // 04:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents", 4, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 5, 00, 00); // 05:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("6 Light PropertyChangeEvents", 6, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 5, 59, 00); // 05:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("6 Light PropertyChangeEvents", 6, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 6, 00, 00); // 06:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("8 Light PropertyChangeEvents for 4 actual changes", 8, _listenerkicks, __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();
}

//@Test
/*public*/ void LightControlTest::testFastClockFollowingTwoControlsOverlap() throw (TimebaseRateException) {
    Timebase* timebase = (Timebase*)InstanceManager::getDefault("Timebase");
    timebase->setRun(false);
    Calendar* cal = new GregorianCalendar();
    cal->set(2018, 1, 12, 02, 59, 00); // 02:59:00
    timebase->setTime(cal->getTime());

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Assert::assertEquals("OFF state by default", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::FAST_CLOCK_CONTROL);
    lc->setFastClockControlSchedule(3, 0, 4, 0); // onHr, OnMin, OffHr, OffMin

    DefaultLightControl* lcb = new DefaultLightControl(l);
    lcb->setControlType(Light::FAST_CLOCK_CONTROL);
    lcb->setFastClockControlSchedule(3, 30, 4, 30); // onHr, OnMin, OffHr, OffMin

    Assert::assertTrue("Total On Time",210==lcb->getFastClockOnCombined(), __FILE__, __LINE__);
    Assert::assertTrue("Total Off Time",270==lcb->getFastClockOffCombined(), __FILE__, __LINE__);

    l->addLightControl(lc);
    l->addLightControl(lcb);
    l->activateLight();
    Assert::assertEquals("OFF starting at 02:59 controls 03:00-04:00, 03:30-04:30", Light::OFF, l->getState(), __FILE__, __LINE__);

    // adding the PCL to check that we don't get flickering on the Light
    // ie "normal" amount of PCEvents for a state change.
    // NOT testing the actual PCListeners
    ((AbstractNamedBean*)l->self())->addPropertyChangeListener(new ControlListen(this));

    cal->set(2018, 1, 12, 3, 00, 00); // 03:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 29, 00); // 03:29:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 30, 00); // 03:30:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 3, 59, 00); // 03:59:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still ON", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 00, 00); // 04:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("goes OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents for 2 actual changes", 4, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 29, 00); // 04:29:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents for 2 actual changes", 4, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 30, 00); // 06:00:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents for 2 actual changes", 4, _listenerkicks, __FILE__, __LINE__);

    cal->set(2018, 1, 12, 4, 31, 00); // 04:31:00
    timebase->setTime(cal->getTime());
    Assert::assertEquals("still OFF", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents for 2 actual changes", 4, _listenerkicks, __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();
}

//@Test
/*public*/ void LightControlTest::testTimedSensorFollowing() /*throw (JmriException)*/ {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Sensor* s = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S2");

    int startListeners = s->getPropertyChangeListeners().length();

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TIMED_ON_CONTROL);
    lc->setControlTimedOnSensorName("S2");

    l->setState(Light::ON); // should go OFF when light enabled and Timed Sensor Control activated

    // adding the PCL to check the Light changes
    // ie "normal" amount of PCEvents for a state change.
    // NOT testing the actual PCListeners
    ((AbstractNamedBean*)l->self())->addPropertyChangeListener(new ControlListen(this));

    l->addLightControl(lc);
    l->activateLight();

    Assert::assertEquals("+1 listener", startListeners + 1, s->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, s->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // light set OFF by default
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    s->setState(Sensor::ON);
//        JUnitUtil->waitFor(() -> {
//            return 6 == _listenerkicks;
//        }, "Light goes ON, then OFF v quickly as time is 0");
    ReleaseUntilO15* r15 = new ReleaseUntilO15(this);
    JUnitUtil::waitFor(r15, "Light goes ON, then OFF v quickly as time is 0", __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // light set OFF after timeout

    s->setState(Sensor::OFF);
    Assert::assertEquals("still 6 Light PropertyChangeEvents", 6, _listenerkicks, __FILE__, __LINE__);

    l->deactivateLight();
    Assert::assertEquals("releases listener", startListeners, s->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    lc->setTimedOnDuration(40); // ms
    l->activateLight();

    s->setState(Sensor::ON);
    s->setState(Sensor::OFF);
    Assert::assertEquals("Light goes ON at start timer", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("8 Light PropertyChangeEvents", 8, _listenerkicks, __FILE__, __LINE__);

//        JUnitUtil->waitFor(() -> {
//            return Light::OFF == l->getState();
//        }, "Light goes back OFF after timer");
    ReleaseUntilO16* r16 = new ReleaseUntilO16(this);
    JUnitUtil::waitFor(r16, "Light goes back OFF after timer", __FILE__, __LINE__);
    Assert::assertEquals("10 Light PropertyChangeEvents", 10, _listenerkicks, __FILE__, __LINE__);

    l->setEnabled(false);
    s->setState(Sensor::ON);
    s->setState(Sensor::OFF);
    Assert::assertEquals("Light not enabled", Light::OFF, l->getState(), __FILE__, __LINE__);
    l->deactivateLight();

    l->setState(Light::ON);
    l->activateLight();
    Assert::assertEquals("Light not enabled so not switched off", Light::ON, l->getState(), __FILE__, __LINE__);
    l->deactivateLight();

    // deactivate light mid-timing
    l->setEnabled(true);
    lc->setTimedOnDuration(4000); // ms
    l->activateLight();
    Assert::assertEquals("Light enabled", Light::OFF, l->getState(), __FILE__, __LINE__);
    s->setState(Sensor::ON);
    s->setState(Sensor::OFF);
    Assert::assertEquals("Light triggered", Light::ON, l->getState(), __FILE__, __LINE__);
    l->deactivateLight();
    Assert::assertEquals("Light still on", Light::ON, l->getState(), __FILE__, __LINE__);

    l->activateLight();
    Assert::assertEquals("Light enabled", Light::OFF, l->getState(), __FILE__, __LINE__);

    lc->setControlType(999);
    l->deactivateLight();
    JUnitAppender::assertWarnMessage("Unexpected control type when deactivating Light: ILL1", __FILE__, __LINE__);

    ((AbstractNamedBean*)l->self())->dispose();

}

//@Test
/*public*/ void LightControlTest::testNoTimedSensor() {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TIMED_ON_CONTROL);

    l->addLightControl(lc);
    l->activateLight();
    JUnitAppender::assertErrorMessage("Light ILL1 is linked to a Sensor that does not exist:", __FILE__, __LINE__);

}

//@Test
/*public*/ void LightControlTest::testTwoSensorFollowingNoSensorSet() {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TWO_SENSOR_CONTROL);

    lc->setControlSensorName("");
    lc->setControlSensor2Name("");

    l->addLightControl(lc);
    l->activateLight();
    JUnitAppender::assertErrorMessage("Light ILL1 with 2 Sensor Control is linked to a Sensor that does not exist->", __FILE__, __LINE__);

    lc->setControlSensorName("S1");
    lc->setControlSensor2Name("");

    l->activateLight();
    JUnitAppender::assertErrorMessage("Light ILL1 with 2 Sensor Control is linked to a Sensor that does not exist->", __FILE__, __LINE__);

    lc->setControlSensorName("");
    lc->setControlSensor2Name("S2");

    l->activateLight();
    JUnitAppender::assertErrorMessage("Light ILL1 with 2 Sensor Control is linked to a Sensor that does not exist->", __FILE__, __LINE__);

    lc->setControlSensorSense(999);
    JUnitAppender::assertErrorMessage("Incorrect Sensor State Set", __FILE__, __LINE__);

}

//@Test
/*public*/ void LightControlTest::testTwoSensorFollowing() /*throw (JmriException)*/ {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Sensor* sOne = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S1");
    Sensor* sTwo = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S2");

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TWO_SENSOR_CONTROL);
    lc->setControlSensorName("S1");
    lc->setControlSensor2Name("S2");
    lc->setControlSensorSense(Sensor::ACTIVE);

    int startListenersOne = sOne->getPropertyChangeListeners().length();
    int startListenersTwo = sTwo->getPropertyChangeListeners().length();

    l->addLightControl(lc);
    l->activateLight();

    Assert::assertEquals("+1 listener", startListenersOne + 1, sOne->getPropertyChangeListeners().length(), __FILE__, __LINE__);
    Assert::assertEquals("+1 listener", startListenersTwo + 1, sTwo->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, sOne->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, sTwo->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    sOne->setState(Sensor::ON);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    sOne->setState(Sensor::OFF);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    sTwo->setState(Sensor::ON);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    sTwo->setState(Sensor::OFF);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    sOne->setState(Sensor::ON);
    sTwo->setState(Sensor::ON);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    sOne->setState(Sensor::OFF);
    Assert::assertEquals("Light ON state as Stwo still ACTIVE", Light::ON, l->getState(), __FILE__, __LINE__);
    sOne->setState(Sensor::ON);

    sTwo->setState(Sensor::OFF);
    Assert::assertEquals("Light ON state as sOne still ACTIVE", Light::ON, l->getState(), __FILE__, __LINE__);
    sOne->setState(Sensor::OFF);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    Assert::assertEquals("releases listener", startListenersOne, sOne->getPropertyChangeListeners().length(), __FILE__, __LINE__);
    Assert::assertEquals("releases listener", startListenersTwo, sTwo->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    sOne->setState(Sensor::ON);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);

    l->activateLight();
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);

    l->setEnabled(false);
    sOne->setState(Sensor::OFF);
    Assert::assertEquals("does not change", Light::ON, l->getState(), __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();

}

//@Test
/*public*/ void LightControlTest::testTwoSensorFollowingInactive() /*throw (JmriException)*/ {

    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Sensor* sOne = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S1");
    Sensor* sTwo = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("S2");

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::TWO_SENSOR_CONTROL);
    lc->setControlSensorName("S1");
    lc->setControlSensor2Name("S2");
    lc->setControlSensorSense(Sensor::INACTIVE);

    l->addLightControl(lc);
    l->activateLight();

    // adding the PCL to check the Light changes
    // ie "normal" amount of PCEvents for a state change.
    // NOT testing the actual PCListeners
    ((AbstractNamedBean*)l->self())->addPropertyChangeListener(new ControlListen(this));

    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, sOne->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Sensor unknown state", Sensor::UNKNOWN, sTwo->getState(), __FILE__, __LINE__);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    sOne->setState(Sensor::ACTIVE);
    sTwo->setState(Sensor::ACTIVE);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("0 Light PropertyChangeEvents", 0, _listenerkicks, __FILE__, __LINE__);

    sOne->setState(Sensor::INACTIVE);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    sTwo->setState(Sensor::INACTIVE);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    sOne->setState(Sensor::ACTIVE);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    sOne->setState(Sensor::ACTIVE);
    sTwo->setState(Sensor::INACTIVE);
    Assert::assertEquals("Light ON state", Light::ON, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("2 Light PropertyChangeEvents", 2, _listenerkicks, __FILE__, __LINE__);

    sTwo->setState(Sensor::ACTIVE);
    Assert::assertEquals("Light OFF state", Light::OFF, l->getState(), __FILE__, __LINE__);
    Assert::assertEquals("4 Light PropertyChangeEvents, 2 actual changes", 4, _listenerkicks, __FILE__, __LINE__);

    l->deactivateLight();
    ((AbstractNamedBean*)l->self())->dispose();

}

//@Test
/*public*/ void LightControlTest::testUniqueTimes() {
    l = ((LightManager*)InstanceManager::getDefault("LightManager"))->provideLight("L1");
    Assert::assertEquals("OFF state by default", Light::OFF, l->getState(), __FILE__, __LINE__); // lights are OFF by default

    lc = new DefaultLightControl(l);
    lc->setControlType(Light::FAST_CLOCK_CONTROL);
    lc->setFastClockControlSchedule(0, 0, 0, 0); // onHr, OnMin, OffHr, OffMin

    Assert::assertTrue(lc->onOffTimesFaulty(), __FILE__, __LINE__);
    lc->setFastClockControlSchedule(1, 2, 3, 4); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(lc->onOffTimesFaulty(), __FILE__, __LINE__);

    DefaultLightControl* lcb = new DefaultLightControl(l);
    lcb->setControlType(Light::FAST_CLOCK_CONTROL);
    lcb->setFastClockControlSchedule(1, 2, 0, 0); // onHr, OnMin, OffHr, OffMin

    l->addLightControl(lc);
    Assert::assertFalse(lc->areFollowerTimesFaulty(l->getLightControlList()), __FILE__, __LINE__);

    l->addLightControl(lcb);

    Assert::assertTrue(lcb->areFollowerTimesFaulty(l->getLightControlList()), __FILE__, __LINE__);
    lcb->setFastClockControlSchedule(0, 0, 0, 0); // onHr, OnMin, OffHr, OffMin
    Assert::assertTrue(lcb->areFollowerTimesFaulty(l->getLightControlList()), __FILE__, __LINE__);

    lcb->setFastClockControlSchedule(9, 0, 10, 0); // onHr, OnMin, OffHr, OffMin
    Assert::assertFalse(lcb->areFollowerTimesFaulty(l->getLightControlList()), __FILE__, __LINE__);

    lcb->setFastClockControlSchedule(0, 0, 3, 4); // onHr, OnMin, OffHr, OffMin
    Assert::assertTrue(lcb->areFollowerTimesFaulty(l->getLightControlList()), __FILE__, __LINE__);
    l->activateLight();

    JUnitAppender::assertErrorMessage("Light has multiple actions for the same time in Light Controller ILL1 ON at 01:02, OFF at 03:04.", __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("Light has multiple actions for the same time in Light Controller ILL1 ON at 00:00, OFF at 03:04.", __FILE__, __LINE__);

}


// internal PCL event counter
//    private class ControlListen implements java.beans->PropertyChangeListener {

    //@Override
    /*public*/ void ControlListen::propertyChange(PropertyChangeEvent* e) {
        test->_listenerkicks++;
        // log.warn("{}",e);
    }
//    }


// The minimal setup for log4J
//@Before
/*public*/ void LightControlTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetInstanceManager();
    JUnitUtil::initInternalTurnoutManager();
    JUnitUtil::initInternalLightManager();
    JUnitUtil::initInternalSensorManager();
    _listenerkicks = 0;
}

//@After
/*public*/ void LightControlTest::tearDown() {
    JUnitUtil::tearDown();
}
