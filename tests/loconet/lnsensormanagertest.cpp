#include "lnsensormanagertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "loconetinterfacescaffold.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "loconetsystemconnectionmemo.h"
#include "sensormanager.h"
#include "sensor.h"
#include "lnsensor.h"
#include "junitappender.h"

LnSensorManagerTest::LnSensorManagerTest()
{

}
/**
 * Tests for the jmri.jmrix.loconet.LnSensorManagerTurnout class.
 *
 * @author	Bob Jacobsen Copyright 2001
 */
///*public*/ class LnSensorManagerTest extends jmri.managers.AbstractSensorMgrTestBase {


//@Override
/*public*/ QString LnSensorManagerTest::getSystemName(int i) {
    return "LS" + QString::number(i);
}

//@Test
/*public*/ void LnSensorManagerTest::testLnSensorCreate() {
    Assert::assertNotNull("exists", l, __FILE__, __LINE__);
}

//@Test
/*public*/ void LnSensorManagerTest::testByAddress() {
    // sample turnout object
    Sensor* t = l->newSensor("LS22", "test");

    // test get
    Assert::assertTrue(t == l->getByUserName("test"), __FILE__, __LINE__);
    Assert::assertTrue(t == l->getBySystemName("LS22"), __FILE__, __LINE__);
}

//@Test
//@Override
/*public*/ void LnSensorManagerTest::testMisses() {
    // sample turnout object
    Sensor* t = l->newSensor("LS22", "test");
    Assert::assertNotNull("exists", t, __FILE__, __LINE__);

    // try to get nonexistant turnouts
    Assert::assertTrue(nullptr == l->getByUserName("foo"), __FILE__, __LINE__);
    Assert::assertTrue(nullptr == l->getBySystemName("bar"), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnSensorManagerTest::testLocoNetMessages() {
    // send messages for 21, 22
    // notify the Ln that somebody else changed it...
    LocoNetMessage* m1 = new LocoNetMessage(4);
    m1->setOpCode(0xb2);         // OPC_INPUT_REP
    m1->setElement(1, 0x15);     // all but lowest bit of address
    m1->setElement(2, 0x60);     // Aux (low addr bit high), sensor high
    m1->setElement(3, 0x38);
    lnis->sendTestMessage(m1);

    // see if sensor exists
    Assert::assertTrue(nullptr != l->getBySystemName("LS44"), __FILE__, __LINE__);
}

//@Test
/*public*/ void LnSensorManagerTest::testAsAbstractFactory() {
    // ask for a Sensor, and check type
    SensorManager* t = InstanceManager::sensorManagerInstance();

    Sensor* o = t->newSensor("LS21", "my name");

    if (log->isDebugEnabled()) {
        log->debug("received sensor value " + o->getDisplayName());
    }
    Assert::assertTrue(nullptr != (LnSensor*) o, __FILE__, __LINE__);

    // make sure loaded into tables
    if (log->isDebugEnabled()) {
        log->debug("by system name: " + t->getBySystemName("LS21")->getDisplayName());
    }
    if (log->isDebugEnabled()) {
        log->debug("by user name:   " + t->getByUserName("my name")->getDisplayName());
    }

    Assert::assertTrue(nullptr != t->getBySystemName("LS21"), __FILE__, __LINE__);
    Assert::assertTrue(nullptr != t->getByUserName("my name"), __FILE__, __LINE__);

}

//@Test
/*public*/ void LnSensorManagerTest::testDeprecationWarningSensorNumberFormat() {
    bool excep= false;
    QString s = "";
    try {
        s = l->createSystemName("3:5", "L");
    } catch (JmriException* e) {
        excep = true;
    }
    Assert::assertEquals("no exception during createSystemName for arguments '3:5', 'L'", false, excep, __FILE__, __LINE__);
    Assert::assertEquals("check createSystemName for arguments '3:5', 'L'", "LS37", s, __FILE__, __LINE__);
    JUnitAppender::assertWarnMessage(
            "LnSensorManager.createSystemName(curAddress, prefix) support for curAddress using the '3:5' format is deprecated as of JMRI 4.17.4 and will be removed in a future JMRI release.  Use the curAddress format '37' instead.", __FILE__, __LINE__);
}

// The minimal setup for log4J
//@Override
//@Before
/*public*/ void LnSensorManagerTest::setUp() {
    JUnitUtil::setUp();
    // prepare an interface
    LocoNetSystemConnectionMemo* memo = new LocoNetSystemConnectionMemo();
    lnis = new LocoNetInterfaceScaffold(memo);
    memo->setLnTrafficController(lnis);
    Assert::assertNotNull("exists", lnis, __FILE__, __LINE__);

    // create and register the manager object
    l = new LnSensorManager(memo);
    InstanceManager::setSensorManager((SensorManager*)l);
}

//@After
/*public*/ void LnSensorManagerTest::tearDown() {
    l->dispose();
    lnis = nullptr;
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* LnSensorManagerTest::log = LoggerFactory::getLogger("LnSensorManagerTest");
