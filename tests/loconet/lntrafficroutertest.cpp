#include "lntrafficroutertest.h"
#include "lntrafficrouter.h"
#include "assert1.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"
#include "loconetsystemconnectionmemo.h"

LnTrafficRouterTest::LnTrafficRouterTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Bob Jacobsen Copyright (c) 2002
 */
///*public*/ class LnTrafficRouterTest {

//@Test
/*public*/ void LnTrafficRouterTest::testConnectAndSend() {
    // scaffold for upstream
    LocoNetInterfaceScaffold* upstream = new LocoNetInterfaceScaffold();

    // create object
    LnTrafficRouter* router = new LnTrafficRouter(memo);
    memo->setLnTrafficController(router);

    Assert::assertEquals("router is tc", memo->getLnTrafficController(), router, __FILE__, __LINE__);

    // connect
    router->connect(upstream);
    Assert::assertTrue("connected", router->status(), __FILE__, __LINE__);

    // send a message
    LocoNetMessage* m = new LocoNetMessage(3);
    router->sendLocoNetMessage(m);

    // check receipt
    Assert::assertEquals("one message sent", 1, upstream->outbound.size(), __FILE__, __LINE__);
    Assert::assertTrue(upstream->outbound.at(0) == m, __FILE__, __LINE__);
}

/*static*/ int LnTrafficRouterTest::count = 0;

//@Test
/*public*/ void LnTrafficRouterTest::testReceiveAndForward() {
    // create object
    LnTrafficRouter* router = new LnTrafficRouter(memo);
    memo->setLnTrafficController(router);
    Assert::assertEquals("router is tc", memo->getLnTrafficController(), router, __FILE__, __LINE__);

    count = 0;
    // register a listener
//    LocoNetListener l = new LocoNetListener() {
//        @Override
//        /*public*/ void message(LocoNetMessage m) {
//            count++;
//        }
//    };
    LocoNetListenerO1* l = new LocoNetListenerO1(this);
    router->addLocoNetListener(~0, l);
    connect(router, SIGNAL(messageProcessed(LocoNetMessage*)), l, SLOT(message(LocoNetMessage*)));

    // send a message
    LocoNetMessage* m = new LocoNetMessage(3);
    router->message(m);

    // check receipt
    Assert::assertEquals("one message sent", 1, count, __FILE__, __LINE__);
}

//@Test
/*public*/ void LnTrafficRouterTest::testConnectAndDisconnect() {
    // scaffold for upstream
    LocoNetInterfaceScaffold* upstream = new LocoNetInterfaceScaffold(memo);

    // create object
    LnTrafficRouter* router = new LnTrafficRouter(memo);
    memo->setLnTrafficController(router);
    Assert::assertEquals("router is tc", memo->getLnTrafficController(), router, __FILE__, __LINE__);

    // connect
    router->connect(upstream);
    Assert::assertTrue("connected", router->status(), __FILE__, __LINE__);

    // disconnect
    router->disconnectPort(upstream);
    Assert::assertTrue("not connected", !router->status(), __FILE__, __LINE__);
}


// The minimal setup for log4J
//@Before
/*public*/ void LnTrafficRouterTest::setUp() {
    JUnitUtil::setUp();
    memo = new LocoNetSystemConnectionMemo();
}

//@After
/*public*/ void LnTrafficRouterTest::tearDown() {
    memo->dispose();
    JUnitUtil::tearDown();
}
