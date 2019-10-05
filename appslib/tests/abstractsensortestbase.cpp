#include "abstractsensortestbase.h"
#include "assert1.h"
#include "sensor.h"
#include "abstractsensor.h"
#include "assume.h"

AbstractSensorTestBase::AbstractSensorTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Abstract Base Class for Sensor tests in specific jmrix packages. This is not
 * itself a test class, e.g. should not be added to a suite. Instead, this forms
 * the base for test classes, including providing some common tests.
 *
 * @author	Bob Jacobsen 2016 from AbstractLightTestBase (which was called AbstractLightTest at the time)
 * @author  Paul Bender Copyright (C) 2018
*/
///*public*/ abstract class AbstractSensorTestBase {

// implementing classes must provide these these methods

// return number of listeners registered with the TrafficController
//abstract /*public*/ int numListeners();

//abstract /*public*/ void checkOnMsgSent();

//abstract /*public*/ void checkOffMsgSent();

//abstract /*public*/ void checkStatusRequestMsgSent();

// implementing classes must provide this abstract member:
//@Before
//abstract /*public*/ void setUp(); // load t with actual object; create scaffolds as needed

/*static*/ /*protected*/ bool AbstractSensorTestBase::listenerResult = false;

// start of common tests
// test creation - real work is in the setup() routine
//@Test
/*public*/ void AbstractSensorTestBase::testCreate() {
    // initial state when created must be UNKNOWN
    Assert::assertEquals("initial state 1", Sensor::UNKNOWN, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("initial state 2", "Unknown", t->describeState(t->getState()), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testAddListener() throw (JmriException)
{
  ListenO2* listen;

  t->addPropertyChangeListener(listen =new ListenO2(this));
  connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listen, SLOT(propertyChange(PropertyChangeEvent*)));
  listenerResult = false;
  t->setUserName("user id");
  Assert::assertTrue("listener invoked by setUserName", listenerResult, __FILE__, __LINE__);
  listenerResult = false;
  t->setState(Sensor::ACTIVE);
  Assert::assertTrue("listener invoked by setState", listenerResult, __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testRemoveListener() {
    ListenO2* ln = new ListenO2(this);
    t->addPropertyChangeListener(ln);
    connect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), ln, SLOT(propertyChange(PropertyChangeEvent*)));
    t->removePropertyChangeListener(ln);
    disconnect(t->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), ln, SLOT(propertyChange(PropertyChangeEvent*)));
    listenerResult = false;
    t->setUserName("user id");
    Assert::assertFalse("listener should not have heard message after removeListener",
            listenerResult, __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testDispose() throw (JmriException) {
    t->setState(Sensor::ACTIVE);  	// in case registration with TrafficController is deferred to after first use
    t->dispose();
    Assert::assertEquals("controller listeners remaining", 0, numListeners(), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testCommandInactive() throw (JmriException) {
    t->setState(Sensor::INACTIVE);
    // check
    Assert::assertEquals("state 1", Sensor::INACTIVE, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("state 2", "Inactive", t->describeState(t->getState()), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testCommandActive() throw (JmriException) {
    t->setState(Sensor::ACTIVE);
    // check
    Assert::assertEquals("state 1", Sensor::ACTIVE, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("state 2", "Active", t->describeState(t->getState()), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testInvertAfterInactive() throw (JmriException) {
    Assume::assumeTrue(t->canInvert());
    t->setState(Sensor::INACTIVE);
    t->setInverted(true);
    // check
    Assert::assertEquals("state 1", Sensor::ACTIVE, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("state 2", "Active", t->describeState(t->getState()), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testInvertAfterActive() throw (JmriException) {
    Assume::assumeTrue(t->canInvert());
    t->setState(Sensor::ACTIVE);
    t->setInverted(true);
    // check
    Assert::assertEquals("state 1", Sensor::INACTIVE, t->getState(), __FILE__, __LINE__);
    Assert::assertEquals("state 2", "Inactive", t->describeState(t->getState()), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testDebounceSettings() throw (JmriException) {
    t->setSensorDebounceGoingActiveTimer(81L);
    Assert::assertEquals("timer", 81L, t->getSensorDebounceGoingActiveTimer(), __FILE__, __LINE__);

    t->setSensorDebounceGoingInActiveTimer(31L);
    Assert::assertEquals("timer", 31L, t->getSensorDebounceGoingInActiveTimer(), __FILE__, __LINE__);

    Assert::assertEquals("initial default", false, t->getUseDefaultTimerSettings(), __FILE__, __LINE__);
    t->setUseDefaultTimerSettings(true);
    Assert::assertEquals("initial default", true, t->getUseDefaultTimerSettings(), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testDebounce() throw (JmriException) {
    t->setSensorDebounceGoingActiveTimer(81L);
    Assert::assertEquals("timer", 81L, t->getSensorDebounceGoingActiveTimer(), __FILE__, __LINE__);

    t->setSensorDebounceGoingInActiveTimer(31L);
    Assert::assertEquals("timer", 31L, t->getSensorDebounceGoingInActiveTimer(), __FILE__, __LINE__);

    Assert::assertEquals("initial state", Sensor::UNKNOWN, t->getState(), __FILE__, __LINE__);
    t->setOwnState(Sensor::ACTIVE); // next is considered to run immediately, before debounce
    Assert::assertEquals("post-set state", Sensor::UNKNOWN, t->getState(), __FILE__, __LINE__);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == t->getRawState();}, "raw state = state");
    ReleaseUntilO8* r08 = new ReleaseUntilO8(this);
    JUnitUtil::waitFor(r08, "raw state = state");
    Assert::assertEquals("2nd state", Sensor::ACTIVE, t->getState(), __FILE__, __LINE__);

    t->setOwnState(Sensor::INACTIVE); // next is considered to run immediately, before debounce
    Assert::assertEquals("post-set state", Sensor::ACTIVE, t->getState(), __FILE__, __LINE__);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == t->getRawState();}, "raw state = state");
    r08 = new ReleaseUntilO8(this);
    JUnitUtil::waitFor(r08, "raw state = state");
    Assert::assertEquals("Final state", Sensor::INACTIVE, t->getState(), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testGetPullResistance(){
    // default is off, override this test if this is supported.
    Assert::assertEquals("Pull Direction", Sensor::PullResistance::PULL_OFF, t->getPullResistance(), __FILE__, __LINE__);
}

//@Test
/*public*/ void AbstractSensorTestBase::testGetBeanType(){
    Assert::assertEquals("bean type", t->getBeanType(), tr("Sensor"),__FILE__, __LINE__);
}

// Test outgoing status request
//@Test
/*public*/ void AbstractSensorTestBase::testSensorStatusRequest() {
    t->requestUpdateFromLayout();
    // check that the correct message was sent
    checkStatusRequestMsgSent();
}

// Test the Sensor interface
//@Test
/*public*/ void AbstractSensorTestBase::testSensor() throw (JmriException) {
    t->setState(Sensor::ON);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == Sensor::ON;}, "state = ON");
    ReleaseUntilO9* r09 = new ReleaseUntilO9(Sensor::ON, this);
    JUnitUtil::waitFor(r09, "state = ON");
    Assert::assertTrue("Sensor is ON", t->getState() == Sensor::ON, __FILE__, __LINE__);
    t->setState(Sensor::OFF);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == Sensor::OFF;}, "state = OFF");
    r09 = new ReleaseUntilO9(Sensor::OFF, this);
    JUnitUtil::waitFor(r09, "state = OFF");
    Assert::assertTrue("Sensor is ON", t->getState() == Sensor::OFF, __FILE__, __LINE__);
    t->setCommandedState(Sensor::ON);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == Sensor::ON;}, "state = ON");
    r09 = new ReleaseUntilO9(Sensor::ON, this);
    JUnitUtil::waitFor(r09, "state = ON");
    Assert::assertTrue("Sensor is ON", t->getState() == Sensor::ON, __FILE__, __LINE__);
    t->setCommandedState(Sensor::OFF);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getState() == Sensor::OFF;}, "state = OFF");
    r09 = new ReleaseUntilO9(Sensor::OFF, this);
    JUnitUtil::waitFor(r09, "state = OFF");
    Assert::assertTrue("Sensor is ON", t->getState() == Sensor::OFF, __FILE__, __LINE__);
    t->setState(Sensor::ON);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getCommandedState() == Sensor::ON;}, "commanded state = ON");
    r09 = new ReleaseUntilO9(Sensor::ON, this);
    JUnitUtil::waitFor(r09, "state = ON");
    Assert::assertTrue("Sensor is ON", t->getCommandedState() == Sensor::ON, __FILE__, __LINE__);
    t->setState(Sensor::OFF);
    //jmri.util.JUnitUtil.waitFor(()->{return t->getCommandedState() == Sensor::OFF;}, "commanded state = OFF");
    r09 = new ReleaseUntilO9(Sensor::OFF, this);
    JUnitUtil::waitFor(r09, "state = OFF");
    Assert::assertTrue("Sensor is ON", t->getCommandedState() == Sensor::OFF, __FILE__, __LINE__);
}

//dispose of t.
//@After
//abstract /*public*/ void AbstractSensorTestBase::tearDown();

/*public*/ void ListenO2::propertyChange(PropertyChangeEvent* e) {
    test->listenerResult = true;
}
