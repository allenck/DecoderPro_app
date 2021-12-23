#include "abstractsensormgrtestbase.h"
#include "assert1.h"
#include "sensor.h"
#include "junitappender.h"

AbstractSensorMgrTestBase::AbstractSensorMgrTestBase(QObject *parent) : AbstractManagerTestBase(parent)
{

}
/**
 * Abstract Base Class for SensorManager tests in specific jmrix packages. This
 * is not itself a test class, e.g. should not be added to a suite. Instead,
 * this forms the base for test classes, including providing some common tests
 *
 * @author	Bob Jacobsen 2003, 2006, 2008, 2016
 * @author      Paul Bender Copyright(C) 2016
 */
///*public*/ abstract class AbstractSensorMgrTestBase extends AbstractProvidingManagerTestBase<SensorManager, Sensor> {

    // implementing classes must provide these abstract members:
    //
    //@Before
    //abstract /*public*/ void setUp();    	// load l with actual object; create scaffolds as needed

    //abstract /*public*/ String getSystemName(int i);

    /*static*/ /*protected*/ bool AbstractSensorMgrTestBase::listenerResult = false;


    // start of common tests
    // test creation - real work is in the setup() routine
    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testCreate() {
       Assert::assertNotNull("Sensor Manager Exists",l, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testDispose() {
        l->dispose();  // all we're really doing here is making sure the method exists
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testSensorPutGet() {
        // create
        Sensor* t = (Sensor*)l->newSensor(getSystemName(getNumToTest1()), "mine");
        // check
        Assert::assertNotNull("real object returned ", t, __FILE__, __LINE__);
        Assert::assertEquals("user name correct ", t, l->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertEquals("system name correct ", t, l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    // Quite a few tests overload this to create their own name process
    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testProvideName() {
        // create
        Sensor* t = l->provide("" + QString::number(getNumToTest1()));
        // check
        Assert::assertNotNull("real object returned ", t, __FILE__, __LINE__);
        Assert::assertEquals("system name correct ", t, l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testDelete() {
        // create
        Sensor* t = l->provide(getSystemName(getNumToTest1()));

        // two-pass delete, details not really tested

        try {
            l->deleteBean(t, "CanDelete");
        } catch (PropertyVetoException e) {}
        try {
            l->deleteBean(t, "DoDelete");
        } catch (PropertyVetoException e) {}

        // check for bean
        Assert::assertNull("no bean", l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
        // check for lengths
        Assert::assertEquals(0, l->getNamedBeanList()->size(), __FILE__, __LINE__);
        Assert::assertEquals(0, l->getNamedBeanSet().size(), __FILE__, __LINE__);
        Assert::assertEquals(0, l->getSystemNameList().size(), __FILE__, __LINE__);
        Assert::assertEquals(0, l->getSystemNameArray().length(), __FILE__, __LINE__);
//        JUnitAppender::suppressWarnMessage("Manager#getSystemNameArray() is deprecated");
        Assert::assertEquals(0, l->getObjectCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testDefaultSystemName() {
        // create
        Sensor* t = l->provideSensor("" + getNumToTest1());
        // check
        Assert::assertNotNull("real object returned ", t, __FILE__, __LINE__);
        Assert::assertEquals("system name correct ", t, l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void AbstractSensorMgrTestBase::testProvideFailure() {
        try {
            l->provideSensor("");
        } catch (IllegalArgumentException* ex) {
            JUnitAppender::assertErrorMessage("Invalid system name for Sensor: System name must start with \"" + l->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
            throw ex;
        }
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testSettings() {
        l->setDefaultSensorDebounceGoingActive(1234L);
        Assert::assertEquals(1234L, l->getDefaultSensorDebounceGoingActive(), __FILE__, __LINE__);

        l->setDefaultSensorDebounceGoingInActive(12345L);
        Assert::assertEquals(12345L, l->getDefaultSensorDebounceGoingInActive(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testSingleObject() {
        // test that you always get the same representation
        Sensor* t1 = l->newSensor(getSystemName(getNumToTest1()), "mine");
        Assert::assertNotNull("t1 real object returned ", t1, __FILE__, __LINE__);
        Assert::assertEquals("same by user ", t1, l->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertEquals("same by system ", t1, l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);

        Sensor* t2 = l->newSensor(getSystemName(getNumToTest1()), "mine");
        Assert::assertNotNull("t2 real object returned ", t2, __FILE__, __LINE__);
        // check
        Assert::assertEquals("same new ", t1, t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testMisses() {
        // try to get nonexistant sensors
        Assert::assertNull(l->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertNull(l->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testMoveUserName() {
        Sensor* t1 = l->provideSensor("" + getNumToTest1());
        Sensor* t2 = l->provideSensor("" + getNumToTest2());
        t1->setUserName("UserName");
        Assert::assertEquals(t1, l->getByUserName("UserName"), __FILE__, __LINE__);

        t2->setUserName("UserName");
        Assert::assertEquals(t2, l->getByUserName("UserName"), __FILE__, __LINE__);

        Assert::assertNull(t1->getUserName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testUpperLower() {  // this is part of testing of (default) normalization
        Sensor* t = l->provideSensor("" + getNumToTest2());
        QString name = t->getSystemName();

        int prefixLength = l->getSystemPrefix().length()+1;     // 1 for type letter
        QString lowerName = name.mid(0, prefixLength)+name.mid(prefixLength, name.length()).toLower();

        Assert::assertEquals(t, l->getSensor(lowerName), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testRename() {
        // get sensor
        Sensor* t1 = l->newSensor(getSystemName(getNumToTest1()), "before");
        Assert::assertNotNull("t1 real object ", t1, __FILE__, __LINE__);
        t1->setUserName("after");
        Sensor* t2 = (Sensor*)l->getByUserName("after");
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertNull("no old object", l->getByUserName("before"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSensorMgrTestBase::testPullResistanceConfigurable(){
       Assert::assertFalse("Pull Resistance Configurable", l->isPullResistanceConfigurable(), __FILE__, __LINE__);
    }

    /**
     * Number of sensor to test. Made a separate method so it can be overridden
     * in subclasses that do or don't support various numbers
     * @return the number to test
     */
    /*protected*/ int AbstractSensorMgrTestBase::getNumToTest1() {
        return 9;
    }

    /*protected*/ int AbstractSensorMgrTestBase::getNumToTest2() {
        return 7;
    }

/*public*/ void ListenO3::propertyChange(PropertyChangeEvent* /*e*/) {
    base->listenerResult = true;
}
