#include "lnsensortest.h"
#include "loggerfactory.h"
#include "assert1.h"
#include "lnsensor.h"

LnSensorTest::LnSensorTest(QObject *parent) : AbstractSensorTestBase(parent)
{

}
/**
 * Tests for the jmri.jmrix.loconet.LnSensor class.
 *
 * @author	Bob Jacobsen Copyright 2001, 2002
 */
///*public*/ class LnSensorTest extends jmri.implementation.AbstractSensorTestBase {


    //@Override
    /*public*/ int LnSensorTest::numListeners() {return lnis->numListeners();}

    //@Override
    /*public*/ void LnSensorTest::checkOnMsgSent() {}

    //@Override
    /*public*/ void LnSensorTest::checkOffMsgSent() {}

    //@Override
    /*public*/ void LnSensorTest::checkStatusRequestMsgSent() {
        // doesn't send a message right now, pending figuring out what
        // to send.
    }

    // LnSensor test for incoming status message
    //@Test
    /*public*/ void LnSensorTest::testLnSensorStatusMsg() {
        // create a new unregistered sensor.
        LnSensor* s = new LnSensor("LS044", lnis, "L");
        LocoNetMessage* m;

        // notify the Ln that somebody else changed it...
        m = new LocoNetMessage(4);
        m->setOpCode(0xb2);         // OPC_INPUT_REP
        m->setElement(1, 0x15);     // all but lowest bit of address
        m->setElement(2, 0x60);     // Aux (low addr bit high), sensor low
        m->setElement(3, 0x38);
        s->messageFromManager(m);
        Assert::assertEquals("Known state after inactivate ", Sensor::INACTIVE, s->getKnownState(), __FILE__, __LINE__);

        m = new LocoNetMessage(4);
        m->setOpCode(0xb2);         // OPC_INPUT_REP
        m->setElement(1, 0x15);     // all but lowest bit of address
        m->setElement(2, 0x70);     // Aux (low addr bit high), sensor high
        m->setElement(3, 0x78);
        s->messageFromManager(m);
        Assert::assertEquals("Known state after activate ", Sensor::ACTIVE, s->getKnownState(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    ////@Override
    /*public*/ void LnSensorTest::setUp() {
        JUnitUtil::setUp();
        // prepare an interface the sensor t, is unregistered so
        // we must feedback the message manually
//        lnis = new LocoNetInterfaceScaffold() {
//            //@Override
//            /*public*/ void sendLocoNetMessage(LocoNetMessage m) {
//                log.debug("sendLocoNetMessage [{}]", m);
//                // save a copy
//                outbound.addElement(m);
//                ((LnSensor)t).messageFromManager(m);
//            }
//        };
        lnis = new LocoNetInterfaceScaffoldO2(this);
        t = new LnSensor("LS042", lnis, "L");
    }

    //@After
    ////@Override
    /*public*/ void LnSensorTest::tearDown() {
        t->dispose();
//	    lnis = null;
        JUnitUtil::tearDown();
    }

    /*private*/ /*final*/ /*static*/ Logger* LnSensorTest::log = LoggerFactory::getLogger("LnSensorTest");


