#include "lnlighttest.h"
#include "junitutil.h"
#include "assert1.h"
#include "loconetsystemconnectionmemo.h"
#include "loconetinterfacescaffold.h"
#include "lnlight.h"
#include "lnlightmanager.h"

LnLightTest::LnLightTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class LnLightTest {

    //@Test
    /*public*/ void LnLightTest::testCTor() {
        LocoNetSystemConnectionMemo* memo = new LocoNetSystemConnectionMemo();
        LnTrafficController* lnis = new LocoNetInterfaceScaffold(memo);
        memo->setLnTrafficController(lnis);
        LnLightManager* lm = new LnLightManager(memo);
        LnLight* t = new LnLight("LL1", lnis, lm);
        Assert::assertNotNull("exists", t, __FILE__, __LINE__);
    }

    //@Before
    /*public*/ void LnLightTest::setUp() {
        JUnitUtil::setUp();
    }

    //@After
    /*public*/ void LnLightTest::tearDown() {
        JUnitUtil::tearDown();
    }
