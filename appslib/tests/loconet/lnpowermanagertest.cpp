#include "lnpowermanagertest.h"
#include "loconetinterfacescaffold.h"
#include "lnpowermanager.h"
#include "loconetsystemconnectionmemo.h"
#include "assert1.h"
#include "slotmanager.h"
#include "junitutil.h"

LnPowerManagerTest::LnPowerManagerTest()
{

}
/**
 * Tests for the Jmri package LnPowerManager.
 *
 * @author	Bob Jacobsen Copyright 2001
 */
// /*public*/ class LnPowerManagerTest extends AbstractPowerManagerTestBase {


    /**
     * service routines to simulate receiving on, off from interface
     */
    //@Override
    /*protected*/ void LnPowerManagerTest::hearOn() {
        LocoNetMessage* l = new LocoNetMessage(2);
        l->setOpCode(LnConstants::OPC_GPON);
        controller->sendTestMessage(l);
    }

    //@Override
    /*protected*/ void LnPowerManagerTest::sendOnReply() {
        hearOn();
    }

    //@Override
    /*protected*/ void LnPowerManagerTest::hearOff() {
        LocoNetMessage* l = new LocoNetMessage(2);
        l->setOpCode(LnConstants::OPC_GPOFF);
        controller->sendTestMessage(l);
    }

    //@Override
    /*protected*/ void LnPowerManagerTest::sendOffReply() {
        hearOff();
    }

    //@Override
    /*protected*/ void LnPowerManagerTest::hearIdle() {
        if (p->implementsIdle()) {
            LocoNetMessage* l = new LocoNetMessage(2);
            l->setOpCode(LnConstants::OPC_IDLE);
            controller->sendTestMessage(l);
        }
    }

    //@Override
    /*protected*/ void LnPowerManagerTest::sendIdleReply() {
        if (p->implementsIdle()) {
            hearIdle();
        }
    }

    //@Override
    /*protected*/ int LnPowerManagerTest::numListeners() {
        return controller->numListeners();
    }

    //@Override
    /*protected*/ int LnPowerManagerTest::outboundSize() {
        return controller->outbound.size();
    }

    //@Override
    /*protected*/ bool LnPowerManagerTest::outboundOnOK(int index) {
        return LnConstants::OPC_GPON
                == controller->outbound.at(index)->getOpCode();
    }

    //@Override
    /*protected*/ bool LnPowerManagerTest::outboundOffOK(int index) {
        return LnConstants::OPC_GPOFF
                == controller->outbound.at(index)->getOpCode();
    }

    //@Override
    /*protected*/ bool LnPowerManagerTest::outboundIdleOK(int index) {
        if (p->implementsIdle()) {
            return LnConstants::OPC_IDLE
                    == controller->outbound.at(index)->getOpCode();
        } else {
            return false;
        }
    }

    //@Override
    //@Test
    /*public*/ void LnPowerManagerTest::testImplementsIdle() {

        // DB150 implements IDLE power state
        memo->configureCommandStation(LnCommandStationType::getByName("DB150 (Empire Builder)"), false, false, false);
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        // DCS100 implements IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS100 (Chief)"));
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        // DCS200 implements IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS200"));
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        // DCS240 implements IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS240 (Advanced Command Station)"));
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        // DCS100 implements IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS210 (Evolution Command Station)"));
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        // DCS50 does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS50 (Zephyr)"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);
        // DCS51 does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("DCS51 (Zephyr Xtra)"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);
        // PR2 does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("PR2 standalone programmer"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);
        // PR3 does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("PR3 standalone programmer"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);
        // Standalone LocoNet does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("Stand-alone LocoNet"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);

    }

    //@Override
    //@Test
    /*public*/ void LnPowerManagerTest::testStateIdle() throw (JmriException) {
        hearOn();  // set up an initial state
        // DCS51 does not implement IDLE power state
        memo->configureCommandStation(LnCommandStationType::getByName("DCS200"), false, false, false);
        Assert::assertTrue(p->implementsIdle(), __FILE__, __LINE__);
        hearIdle();
        Assert::assertEquals("power state", PowerManager::IDLE, p->getPower(), __FILE__, __LINE__);

        hearOn(); // set up an initial state
        // PR2 does not implement IDLE power state
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("PR2 standalone programmer"));
        Assert::assertFalse(p->implementsIdle(), __FILE__, __LINE__);
        hearIdle();
        Assert::assertEquals("power state", PowerManager::ON, p->getPower(), __FILE__, __LINE__);
    }

    //@Test
    //@Override
    /*public*/ void LnPowerManagerTest::testSetPowerIdle() throw (JmriException) {
        memo->configureCommandStation(LnCommandStationType::getByName("DCS200)"), false, false, false);
        Assert::assertTrue("LocoNet implements IDLE", p->implementsIdle(), __FILE__, __LINE__);
        int initialSent = outboundSize();
        p->setPower(PowerManager::IDLE);
        // check one message sent, correct form, Idle state
        Assert::assertEquals("messages sent", initialSent + 1, outboundSize(), __FILE__, __LINE__);
        Assert::assertTrue("message type IDLE O.K.", outboundIdleOK(initialSent), __FILE__, __LINE__);
        Assert::assertEquals("state before reply ", PowerManager::UNKNOWN, p->getPower(), __FILE__, __LINE__);
        // arrange for reply
        sendIdleReply();
        Assert::assertEquals("state after reply ", PowerManager::IDLE, p->getPower(), __FILE__, __LINE__);

        p->setPower(PowerManager::OFF);
        memo->getSlotManager()->setCommandStationType(LnCommandStationType::getByName("PR2 standalone programmer"));
        Assert::assertFalse("LocoNet implements IDLE", p->implementsIdle(), __FILE__, __LINE__);
        initialSent = outboundSize();
        p->setPower(PowerManager::IDLE);
        // check no  message sent
        Assert::assertEquals("messages sent", initialSent, outboundSize(), __FILE__, __LINE__);
    }

    // setup a default interface
    //@Before
    ////@Override
    /*public*/ void LnPowerManagerTest::setUp() {
        JUnitUtil::setUp();
        controller = new LocoNetInterfaceScaffold();
        memo = new LocoNetSystemConnectionMemo(controller, nullptr);
        memo->getLnTrafficController()->memo = memo;

        p = pwr = new LnPowerManager(memo);
    }

    //@After
    /*public*/ void LnPowerManagerTest::tearDown() {
        pwr->dispose();
        memo->dispose();
        pwr = nullptr;
        memo = nullptr;
        controller = nullptr;
        JUnitUtil::tearDown();
    }

