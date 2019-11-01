#include "abstractpowermanagertestbase.h"
#include "assert1.h"
#include "powermanager.h"

AbstractPowerManagerTestBase::AbstractPowerManagerTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Abstract base class for PowerManager tests in specific jmrix. packages.
 *
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests.
 *
 * @author	Bob Jacobsen Copyright 2007
 * @author	Bob Jacobsen Copyright (C) 2017
 */
///*public*/ abstract class AbstractPowerManagerTestBase {

    // required setup routine, must set p to an appropriate value.
    //@Before
    //abstract /*public*/ void setUp();

    /*static*/ /*protected*/ bool AbstractPowerManagerTestBase::listenerResult = false;


    // test creation - real work is in the setup() routine
    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testCreate() {
       Assert::assertNotNull("Power Manager Created",p, __FILE__, __LINE__);
    }

    // test setting power on, off, then getting reply from system
    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testSetPowerOn() throw (JmriException) {
        int initialSent = outboundSize();
        p->setPower(PowerManager::ON);
        // check one message sent, correct form, unknown state
        Assert::assertEquals("messages sent", initialSent + 1, outboundSize(), __FILE__, __LINE__);
        Assert::assertTrue("message type OK", outboundOnOK(initialSent), __FILE__, __LINE__);
        Assert::assertEquals("state before reply ", PowerManager::UNKNOWN, p->getPower(), __FILE__, __LINE__);
        // arrange for reply
        sendOnReply();
        Assert::assertEquals("state after reply ", PowerManager::ON, p->getPower(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testSetPowerOff() throw (JmriException) {
        int startingMessages = outboundSize();
        p->setPower(PowerManager::OFF);
        // check one message sent, correct form
        Assert::assertEquals("messages sent", startingMessages + 1, outboundSize(), __FILE__, __LINE__);
        Assert::assertTrue("message type OK", outboundOffOK(startingMessages), __FILE__, __LINE__);
        Assert::assertEquals("state before reply ", PowerManager::UNKNOWN, p->getPower(), __FILE__, __LINE__);
        // arrange for reply
        sendOffReply();
        Assert::assertEquals("state after reply ", PowerManager::OFF, p->getPower(), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testSetPowerIdle() throw (JmriException){
        if (p->implementsIdle()) {
            Assert::assertTrue("LocoNet implements IDLE", p->implementsIdle(), __FILE__, __LINE__);
            int initialSent = outboundSize();
            p->setPower(PowerManager::IDLE);
            // check one message sent, correct form, unknown state
            Assert::assertEquals("messages sent", initialSent + 1, outboundSize(), __FILE__, __LINE__);
            Assert::assertTrue("message type IDLE O.K.", outboundIdleOK(initialSent), __FILE__, __LINE__);
            Assert::assertEquals("state before reply ", PowerManager::UNKNOWN, p->getPower(), __FILE__, __LINE__);
            // arrange for reply
            sendIdleReply();
            Assert::assertEquals("state after reply ", PowerManager::IDLE, p->getPower(), __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testStateOn() throw (JmriException){
        hearOn();
        Assert::assertEquals("power state", PowerManager::ON, p->getPower(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testStateOff() throw (JmriException){
        hearOff();
        Assert::assertEquals("power state", PowerManager::OFF, p->getPower(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testStateIdle() throw (JmriException){
        if (p->implementsIdle()) {
            hearIdle();
            Assert::assertEquals("power state", PowerManager::IDLE, p->getPower(), __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testAddListener() throw (JmriException){
        p->addPropertyChangeListener(new Listen(this));
        listenerResult = false;
        p->setPower(PowerManager::ON);
        sendOnReply();
        Assert::assertTrue("listener invoked by GPOFF", listenerResult, __FILE__, __LINE__);
        listenerResult = false;
        p->setPower(PowerManager::OFF);
        sendOffReply();
        Assert::assertTrue("listener invoked by GPON", listenerResult, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testRemoveListener() {
        Listen* ln = new Listen(this);
        p->addPropertyChangeListener(ln);
        p->removePropertyChangeListener(ln);
        listenerResult = false;
        hearOn();
        Assert::assertTrue("listener should not have heard message after removeListener",
                !listenerResult, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testDispose1() throw (JmriException){
        p->setPower(PowerManager::ON); // in case registration is deferred
        int startingListeners = numListeners();
        p->getPower();
        p->dispose();
        Assert::assertEquals("controller listeners remaining", startingListeners -1 , numListeners(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testDispose2() throw (JmriException){
        p->addPropertyChangeListener(new Listen(this));
        p->setPower(PowerManager::ON);
        sendOnReply();
        int initialOutboundSize = outboundSize();
        p->dispose();
        try {
            p->setPower(PowerManager::OFF);
        } catch (JmriException e) {
            // this is OK branch, check message not sent
            Assert::assertEquals("messages sent", initialOutboundSize, outboundSize(), __FILE__, __LINE__); // just the first
            return;
        }
        Assert::fail("Should have thrown exception after dispose()",__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractPowerManagerTestBase::testImplementsIdle() {
        // assumes that Idle is not implemented; override this test for cases
        // where idle is implemented.
        Assert::assertFalse(p->implementsIdle(),__FILE__, __LINE__);
    }
