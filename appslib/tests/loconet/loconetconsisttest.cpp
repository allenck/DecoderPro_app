#include "loconetconsisttest.h"
#include "loconetinterfacescaffold.h"
#include "slotmanager.h"
#include "loconetsystemconnectionmemo.h"
#include "lnthrottlemanager.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "loconetconsist.h"
#include "assert1.h"
#include "consistpreferencesmanager.h"

LocoNetConsistTest::LocoNetConsistTest(QObject *parent) : AbstractConsistTestBase(parent)
{

}
/**
 *
 * @author	Paul Bender Copyright (C) 2016,2017
 */

///*public*/ class LocoNetConsistTest extends jmri.implementation.AbstractConsistTestBase {

// infrastructure objects, populated by setUp;

//utility function, handle slot messages required to suppress
// errors from the LnThrottleManager after constructor call.
/*private*/ void LocoNetConsistTest::ReturnSlotInfo(){
    // echo of the original message
    LocoNetMessage* m1 = new LocoNetMessage(4);
    m1->setOpCode(0xBF);
    m1->setElement(1, 0x00);
    m1->setElement(2, 0x03);
    slotmanager->message(m1);
    // reply says its in slot 3
    LocoNetMessage* m2 = new LocoNetMessage(14);
    m2->setElement(0, 0xe7);
    m2->setElement(1, 0xe);
    m2->setElement(2, 3);
    m2->setElement(3, 3);
    m2->setElement(4, 3);
    m2->setElement(5, 0);
    m2->setElement(6, 0);
    m2->setElement(7, 0);
    m2->setElement(8, 0);
    m2->setElement(9, 0);
    m2->setElement(10, 0);
    m2->setElement(11, 0);
    m2->setElement(12, 0);
    m2->setElement(13, 0x15);
    slotmanager->message(m2);
}

//@Test
/*public*/ void LocoNetConsistTest::testCtor2() {
    // DccLocoAddress constructor test.
    LocoNetConsist* c = new LocoNetConsist(new DccLocoAddress(3, false),memo);
    ReturnSlotInfo();
    Assert::assertNotNull(c);
}

//@Test
//@Override
/*public*/ void LocoNetConsistTest::testGetConsistType(){
    // LocoNet consists default to CS consists.
    Assert::assertEquals("default consist type",Consist::CS_CONSIST,c->getConsistType());
}

//@Test
//@Override
/*public*/ void LocoNetConsistTest::testSetConsistTypeCS(){
    c->setConsistType(Consist::CS_CONSIST);
    Assert::assertEquals("default consist type",Consist::CS_CONSIST,c->getConsistType());
}

//@Override
//@Test
/*public*/ void LocoNetConsistTest::checkAddressAllowedBad(){
    // LocoNet CS consists allow any valid address, so this test is empty
}

//@Test
/*public*/ void LocoNetConsistTest::checkAddressAllowedGoodAdvanced(){
    LocoNetConsist* c = new LocoNetConsist(3,memo);
    ReturnSlotInfo();
    c->setConsistType(Consist::ADVANCED_CONSIST);
    Assert::assertTrue("AddressAllowed", c->isAddressAllowed(new DccLocoAddress(200,true)));
}

//@Test
/*public*/ void LocoNetConsistTest::checkAddressAllowedBadAdvanced(){
    LocoNetConsist* c = new LocoNetConsist(3,memo);
    ReturnSlotInfo();
    c->setConsistType(Consist::ADVANCED_CONSIST);
    Assert::assertFalse("AddressAllowed", c->isAddressAllowed(new DccLocoAddress(0,false)));
}

//@Test
/*public*/ void LocoNetConsistTest::checkSizeLimitCS(){
    c->setConsistType(Consist::CS_CONSIST);
    Assert::assertEquals("CS Consist Limit",-1,c->sizeLimit());
}

//@Test
/*public*/ void LocoNetConsistTest::checkGetLocoDirectionCS(){
    LocoNetConsist* c = new LocoNetConsist(3,memo);
    ReturnSlotInfo();
    c->setConsistType(Consist::CS_CONSIST);
    DccLocoAddress* A = new DccLocoAddress(200,true);
    DccLocoAddress* B = new DccLocoAddress(250,true);
    c->restore(A,true); // use restore here, as it does not send
                       // any data to the command station
    c->restore(B,false); // revese direction.
    Assert::assertTrue("Direction in CS Consist", c->getLocoDirection(A));
    Assert::assertFalse("Direction in CS Consist", c->getLocoDirection(B));
}

// The minimal setup for log4J
//@Before
//@Override
/*public*/ void LocoNetConsistTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::resetProfileManager();
    JUnitUtil::initRosterConfigManager();
    InstanceManager::setDefault("ConsistPreferencesManager",new ConsistPreferencesManager());
    // prepare an interface
    lnis = new LocoNetInterfaceScaffold();
    slotmanager = new SlotManager(lnis);
    memo = new LocoNetSystemConnectionMemo(lnis, slotmanager);
    ltm = new LnThrottleManager(memo);
    memo->setThrottleManager(ltm);
    memo->setLnTrafficController(lnis);

    try {
    // set slot 3 to address 3
    LocoNetMessage* m = new LocoNetMessage(13);
    m->setOpCode(LnConstants::OPC_WR_SL_DATA);
    m->setElement(1, 0x0E);
    m->setElement(2, 0x03);
    m->setElement(4, 0x03);
    slotmanager->slot(3)->setSlot(m);

    // set slot 4 to address 255
    m->setElement(2, 0x04);
    m->setElement(4, 0x7F);
    m->setElement(9, 0x01);
    slotmanager->slot(4)->setSlot(m);
    } catch(LocoNetException lne) {
      Assert::fail("failed to add addresses to slot during setup",__FILE__, __LINE__);
    }
    c = new LocoNetConsist(3,memo);
    ReturnSlotInfo();

}

//@After
//@Override
/*public*/ void LocoNetConsistTest::tearDown() {
    ltm->dispose();
    c = nullptr;
    memo->dispose();
    JUnitUtil::tearDown();
}
