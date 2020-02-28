#include "destinationpointstest.h"
#include "assert1.h"
#include "entryexittesttools.h"
#include "layoutblockmanager.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "turnoutmanager.h"
#include "pointdetails.h"

DestinationPointsTest::DestinationPointsTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class DestinationPointsTest {

    /*static*/ EntryExitTestTools* DestinationPointsTest::tools = nullptr;
    /*static*/ QMap<QString, LayoutEditor*>* DestinationPointsTest::panels = new QMap<QString, LayoutEditor*>();

    /*static*/ EntryExitPairs* DestinationPointsTest::eep = nullptr;
    /*static*/ LayoutBlockManager* DestinationPointsTest::lbm = nullptr;
    /*static*/ SensorManager* DestinationPointsTest::sm = nullptr;
    /*static*/ TurnoutManager* DestinationPointsTest::tm = nullptr;

    //@Test
    /*public*/ void DestinationPointsTest::testCTor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        PointDetails* pdSrc = tools->getPoint(sm->getSensor("NX-From-Beta"), panels->value("Alpha") ,eep);  // NOI18N
        Assert::assertNotNull("testCTor - source point", pdSrc, __FILE__, __LINE__);  // NOI18N
        Source* src = new Source(pdSrc);
        Assert::assertNotNull("testCTor - source", src, __FILE__, __LINE__);  // NOI18N

        PointDetails* pdDest = tools->getPoint(sm->getSensor("NX-AE"), panels->value("Alpha") ,eep);  // NOI18N
        Assert::assertNotNull("testCTor - destination point", pdDest, __FILE__, __LINE__);  // NOI18N

        DestinationPoints* dp = new DestinationPoints(pdDest, nullptr, src);
        Assert::assertNotNull("testCTor", dp, __FILE__, __LINE__);  // NOI18N
        QString uuid = dp->getUniqueId();
        Assert::assertTrue("check uuid", uuid.startsWith("IN:"), __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void DestinationPointsTest::testSetRoute() throw (Exception) {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        // Create a route
        DestinationPoints* dp = tools->getDestinationPoint(sm->getSensor("NX-AW-Side"),  // NOI18N
                sm->getSensor("NX-Alpha-EB"), panels->value("Alpha"), eep);  // NOI18N
        dp->activeBean(false, false);
        dp->setRoute(true);
        //JUnitUtil.waitFor(()->{return dp.getState() == 2;}, "Route active", __FILE__, __LINE__);  // NOI18N
        ReleaseUntil_DPT1* r1 = new ReleaseUntil_DPT1(dp, 2);
        JUnitUtil::waitFor(r1, "Route active", __FILE__, __LINE__);  // NOI18N
        // Cancel the route
        dp->cancelClearInterlock(EntryExitPairs::CANCELROUTE);
        //JUnitUtil.waitFor(()->{return dp.getState() == 4;}, "Route inactive");  // NOI18N
        ReleaseUntil_DPT1* r2 = new ReleaseUntil_DPT1(dp, 4);
        JUnitUtil::waitFor(r2, "Route active", __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void DestinationPointsTest::testEnabled() {
        DestinationPoints* dp = tools->getDestinationPoint(sm->getSensor("NX-AE"),  // NOI18N
                sm->getSensor("NX-AW-Main"), panels->value("Alpha"), eep);  // NOI18N
        Assert::assertNotNull("test enabled", dp, __FILE__, __LINE__);  // NOI18N
        bool chkEnabled = dp->isEnabled();
        Assert::assertTrue("test enabled true", chkEnabled, __FILE__, __LINE__);  // NOI18N
        dp->setEnabled(false);
        chkEnabled = dp->isEnabled();
        Assert::assertFalse("test enabled false", chkEnabled, __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void DestinationPointsTest::testState() {
        DestinationPoints* dp = tools->getDestinationPoint(sm->getSensor("NX-AE"),  // NOI18N
                sm->getSensor("NX-AW-Side"), panels->value("Alpha"), eep);  // NOI18N
        Assert::assertNotNull("test state", dp, __FILE__, __LINE__);
        int state = dp->getState();
        Assert::assertEquals("test state inactive", 4, state, __FILE__, __LINE__);  // NOI18N
        dp->setActiveEntryExit(true);
        state = dp->getState();
        Assert::assertEquals("test state active", 2, state, __FILE__, __LINE__);  // NOI18N
    }

    //@BeforeClass
    /*public*/ /*static*/ void DestinationPointsTest::setUp() throw (Exception) {
        JUnitUtil::setUp();
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        JUnitUtil::resetProfileManager();
        tools = new EntryExitTestTools();
        panels = EntryExitTestTools::getPanels();
        Assert::assertEquals("Get LE panels", 2, panels->size(), __FILE__, __LINE__);  // NOI18N
        eep = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");
        lbm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
        sm = (ProxySensorManager*)InstanceManager::getDefault("SensorManager");
        tm = (ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager");
    }

    //@AfterClass
    /*public*/ /*static*/ void DestinationPointsTest::tearDown() {
        //panels.forEach((name, panel) -> JUnitUtil.dispose(panel));
        foreach(LayoutEditor* panel, *panels )
         panel->dispose();
        JUnitUtil::tearDown();
        tm = nullptr;
        sm = nullptr;
        lbm = nullptr;
        eep = nullptr;
        panels = nullptr;
        tools = nullptr;
    }

//     private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(DestinationPointsTest.class);
