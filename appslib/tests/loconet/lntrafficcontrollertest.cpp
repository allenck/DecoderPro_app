#include "lntrafficcontrollertest.h"
#include "assert1.h"
#include "loconetsystemconnectionmemo.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"

LnTrafficControllerTest::LnTrafficControllerTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Bob Jacobsen Copyright (c) 2002
 */
///*public*/ class LnTrafficControllerTest {


//@Test
/*public*/ void LnTrafficControllerTest::testCtor() {
    Assert::assertNotNull("exists", memo->getLnTrafficController() );
}

// The minimal setup for log4J
// @Before
/*public*/ void LnTrafficControllerTest::setUp() {
    JUnitUtil::setUp();
    memo = new LocoNetSystemConnectionMemo();
    LocoNetInterfaceScaffold* lnis = new LocoNetInterfaceScaffold(memo);
    memo->setLnTrafficController(lnis);
}

//@After
/*public*/ void LnTrafficControllerTest::tearDown() {
    memo->dispose();
    JUnitUtil::tearDown();
}
