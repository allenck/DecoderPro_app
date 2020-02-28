#include "pointdetailstest.h"
#include "assert1.h"
#include "entryexittesttools.h"
#include "layoutblockmanager.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "turnoutmanager.h"
#include "pointdetails.h"

PointDetailsTest::PointDetailsTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class PointDetailsTest {

 /*static*/ EntryExitTestTools* PointDetailsTest::tools = nullptr;
 /*static*/ QMap<QString, LayoutEditor*>* PointDetailsTest::panels = new QMap<QString, LayoutEditor*>();

 /*static*/ EntryExitPairs* PointDetailsTest::eep = nullptr;
 /*static*/ LayoutBlockManager* PointDetailsTest::lbm = nullptr;
 /*static*/ SensorManager* PointDetailsTest::sm = nullptr;
 /*static*/ TurnoutManager* PointDetailsTest::tm = nullptr;

    //@Test
    /*public*/ void PointDetailsTest::testCTor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        LayoutBlock* f = lbm->getLayoutBlock("B-Alpha-East");  // NOI18N
        LayoutBlock* p = lbm->getLayoutBlock("B-Alpha-Beta");  // NOI18N
        QList<LayoutBlock*> blockList = QList<LayoutBlock*>();
        blockList.append(p);
        PointDetails* pd = new PointDetails(f,blockList);
        Assert::assertNotNull("create failed", pd, __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void PointDetailsTest::testGetters() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        PointDetails* pd = tools->getPoint(sm->getSensor("NX-AW"), panels->value("Alpha"), eep);  // NOI18N
        Assert::assertNotNull("fetch failed", pd, __FILE__, __LINE__);  // NOI18N
        LayoutBlock* fblk = pd->getFacing();
        Assert::assertNotNull("getFacing", fblk, __FILE__, __LINE__);  // NOI18N
        QList<LayoutBlock*> pblk = pd->getProtecting();
        Assert::assertEquals("getProtecting", 1, pblk.size(), __FILE__, __LINE__);  // NOI18N

        Sensor* sensor = pd->getSensor();
        Assert::assertNotNull("getSensor", sensor, __FILE__, __LINE__);  // NOI18N
        NamedBean* signal = pd->getSignal();
        Assert::assertNull("getSignal", signal, __FILE__, __LINE__);  // NOI18N
    }

    //@Test
    /*public*/ void PointDetailsTest::testNxButton() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        PointDetails* pd = tools->getPoint(sm->getSensor("NX-AW-Main"), panels->value("Alpha"), eep);  // NOI18N
        Assert::assertNotNull("PointDetails fetch failed", pd, __FILE__, __LINE__);  // NOI18N
        pd->setButtonState(EntryExitPairs::NXBUTTONACTIVE);
        pd->setNXState(EntryExitPairs::NXBUTTONINACTIVE);
        int nxState = pd->getNXState();
        Assert::assertEquals("Button is active", nxState, EntryExitPairs::NXBUTTONINACTIVE, __FILE__, __LINE__);  // NOI18N
    }

    //@BeforeClass
    /*public*/ /*static*/ void PointDetailsTest::setUp() throw (Exception) {
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
    /*public*/ /*static*/ void PointDetailsTest::tearDown() {
        //panels.forEach((name, panel) -> JUnitUtil.dispose(panel));
        foreach(LayoutEditor* panel, *panels )
         panel->dispose();
        JUnitUtil::tearDown();
    }
