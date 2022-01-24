#include "lnreportermanagertest.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"
#include "lnreportermanager.h"
#include "loconetsystemconnectionmemo.h"

LnReporterManagerTest::LnReporterManagerTest()
{

}
/**
 * Tests for the LnReporterManager class
 *
 * @author Paul Bender Copyright (C) 2012,2016
 */
///*public*/ class LnReporterManagerTest extends jmri.managers.AbstractReporterMgrTestBase {

    //@Override
    /*public*/ QString LnReporterManagerTest::getSystemName(QString i) {
        return "LR" + i;
    }


    // The minimal setup for log4J
    //@Before
    //@Override
    /*public*/ void LnReporterManagerTest::setUp() {
        JUnitUtil::setUp();
        LocoNetSystemConnectionMemo* memo;
        tc = new LocoNetInterfaceScaffold(memo = new LocoNetSystemConnectionMemo());
        memo->setLnTrafficController(tc);
#if 0
        l = new LnReporterManager(tc->getSystemConnectionMemo());
#endif
    }

    //@After
    /*public*/ void LnReporterManagerTest::tearDown() {
        tc = nullptr;
        JUnitUtil::tearDown();
    }

    //@Override
    /*protected*/ int LnReporterManagerTest::maxN() { return 1; }
