#include "entryexitpairstest.h"
#include "entryexittesttools.h"
#include "layouteditor.h"
#include "entryexitpairs.h"
#include "sensormanager.h"
#include "turnoutmanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "sensormanager.h"
#include "destinationpoints.h"

EntryExitPairsTest::EntryExitPairsTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
+ * @author Dave Sand Copyright (C) 2018
 */
///*public*/ class EntryExitPairsTest {

    /*static*/ EntryExitTestTools* EntryExitPairsTest::tools = nullptr;
    /*static*/ QMap<QString, LayoutEditor*>* EntryExitPairsTest::panels = nullptr;

    /*static*/ EntryExitPairs* EntryExitPairsTest::eep = nullptr;
    /*static*/ LayoutBlockManager* EntryExitPairsTest::lbm = nullptr;
    /*static*/ SensorManager* EntryExitPairsTest::sm = nullptr;
    /*static*/ TurnoutManager* EntryExitPairsTest::tm = nullptr;

    //@Test
    /*public*/ void EntryExitPairsTest::testCTor() {
        EntryExitPairs* t = new EntryExitPairs();
        Assert::assertNotNull("exists", t, __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void EntryExitPairsTest::testAddNxSourcePoint() {
        Sensor* sensor = sm->getSensor("NX-From-Alpha");  // NOI18N
        eep->addNXSourcePoint(sensor, panels->value("Beta"));  // NOI18N
    }

    //@Test
    /*public*/ void EntryExitPairsTest::testGetSourceList() {
        QObjectList* list = eep->getSourceList(panels->value("Alpha"));  // NOI18N
        Assert::assertEquals("test source list", 4, list->size(), __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void EntryExitPairsTest::testSetSingleSegmentRoute() {
        DestinationPoints* dp = tools->getDestinationPoint(sm->getSensor("NX-AE"),  // NOI18N
                sm->getSensor("NX-AW-Main"), panels->value("Alpha"), eep);  // NOI18N
        Assert::assertNotNull("single segment route", dp, __FILE__, __LINE__);  // NOI18N
        eep->setSingleSegmentRoute(dp->getUniqueId());
        //new EventTool().waitNoEvent(1000);
        qApp->processEvents(QEventLoop::AllEvents, 1000);

        // Check the results
        //JUnitUtil::waitFor(()->{return lbm.getLayoutBlock("B-Alpha-Main").getUseExtraColor();}, "Route active");  // NOI18N
        ReleaseUntil_EEPT1* r1 = new ReleaseUntil_EEPT1(this);
        JUnitUtil::waitFor(r1, "Route active", __FILE__, __LINE__);
        //JUnitUtil.waitFor(()->{return tm.getTurnout("T-AE").getKnownState() == Turnout.CLOSED;}, "Turnout closed");  // NOI18N
        ReleaseUntil_EEPT2* r2 = new ReleaseUntil_EEPT2(this);
        JUnitUtil::waitFor(r2, "Turnout closed", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void EntryExitPairsTest::testDiscoverPairs() throw (Exception) {
        eep->automaticallyDiscoverEntryExitPairs(panels->value("Alpha"), EntryExitPairs::FULLINTERLOCK);  // NOI18N
    }

    //@Test
    /*public*/ void EntryExitPairsTest::testNxPairDelete() {
        Sensor* sensor = sm->getSensor("NX-From-Alpha");  // NOI18N
        bool chkDelete = eep->deleteNxPair(sensor);
        Assert::assertTrue("delete empty", chkDelete, __FILE__, __LINE__);  // NOI18N

        createModalDialogOperatorThread(tr("Warning"), tr("No"));  // NOI18N
        sensor = sm->getSensor("NX-Alpha-EB");  // NOI18N
        chkDelete = eep->deleteNxPair(sensor);
        Assert::assertFalse("delete active denied", chkDelete, __FILE__, __LINE__);  // NOI18N
    }

    void EntryExitPairsTest::createModalDialogOperatorThread(QString dialogTitle, QString buttonText) {
#if 0
        Thread t = new Thread(() -> {
            // constructor for jdo will wait until the dialog is visible
            JDialogOperator jdo = new JDialogOperator(dialogTitle);
            JButtonOperator jbo = new JButtonOperator(jdo, buttonText);
            new EventTool().waitNoEvent(1000);
            jbo.pushNoBlock();
        });
        t.setName(dialogTitle + " Close Dialog Thread");  // NOI18N
        t.start();
#endif
    }

    //@BeforeClass
//    /*public*/ static void EntryExitPairsTest::before() throw Exception
    /*public*/ void EntryExitPairsTest::setUp()
    {
        JUnitUtil::setUp();
        //Assume::assumeFalse(GraphicsEnvironment.isHeadless());
        JUnitUtil::resetProfileManager();

        tools = new EntryExitTestTools();
        panels = EntryExitTestTools::getPanels();
        Assert::assertNotNull("Get LE panels", (QObject*)panels, __FILE__, __LINE__);  // NOI18N
        eep = (EntryExitPairs*)InstanceManager::getDefault("EntryExitPairs");
        lbm = (LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager");
        sm = (ProxySensorManager*)InstanceManager::getDefault("SensorManager");
        tm = (ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager");
    }

    //@AfterClass
//    /*public*/ static void after() {
    /*public*/ void EntryExitPairsTest::tearDown()
    {
        //panels.forEach((name, panel) -> JUnitUtil.dispose(panel));
        foreach(LayoutEditor* panel, *EntryExitTestTools::getPanels())
         panel->dispose();
        eep = nullptr;
        lbm = nullptr;
        sm = nullptr;
        tm = nullptr;
        panels = nullptr;
        tools = nullptr;

        JUnitUtil::tearDown();
    }
