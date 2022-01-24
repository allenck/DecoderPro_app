#include "sourcetest.h"
#include "assert1.h"
#include "entryexittesttools.h"
#include "layoutblockmanager.h"
#include "instancemanager.h"
#include "sensormanager.h"
#include "turnoutmanager.h"
#include "pointdetails.h"

SourceTest::SourceTest(QObject *parent) : QObject(parent)
{
}

/**
 *
 * @author Paul Bender Copyright (C) 2017
 * @author Dave Sand Copyright (C) 2018
 */
///*public*/ class SourceTest {

/*static*/ EntryExitTestTools* SourceTest::tools = nullptr;
/*static*/ QMap<QString, LayoutEditor*>* SourceTest::panels = new QMap<QString, LayoutEditor*>();
/*static*/ EntryExitPairs* SourceTest::eep = nullptr;
/*static*/ LayoutBlockManager* SourceTest::lbm = nullptr;
/*static*/ SensorManager* SourceTest::sm = nullptr;
/*static*/ TurnoutManager* SourceTest::tm = nullptr;
//@Test
/*public*/ void SourceTest::testCTor() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    LayoutBlock* facing = lbm->getLayoutBlock("B-Beta-East");  // NOI18N
    LayoutBlock* protect1 = lbm->getLayoutBlock("B-BE");  // NOI18N
    LayoutBlock* protect2 = lbm->getLayoutBlock("B-Beta-Main");  // NOI18N
    QList<LayoutBlock*> blockList = QList<LayoutBlock*>();
    blockList.append(protect1);
    blockList.append(protect2);
    PointDetails* pd = new PointDetails(facing, blockList);
    Assert::assertNotNull("PointDetails* create failed", pd, __FILE__, __LINE__);  // NOI18N
    Sensor* nxSensor = ((ProxySensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("NX-BE");  // NOI18N
    pd->setPanel(panels->value("Beta"));  // NOI18N
    pd->setSensor(nxSensor);
    pd->setRefObject(nxSensor);
    Source* src = new Source(pd);
    Assert::assertNotNull("Source CTor", src, __FILE__, __LINE__);  // NOI18N
}

//@Test
/*public*/ void SourceTest::testDestinationPoints() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless(), __FILE__, __LINE__);
    // Get a source object
    Source* src = tools->getSourceInstance(sm->getSensor("NX-AW"), panels->value("Alpha"), eep);  // NOI18N
    Assert::assertNotNull("Source fetch failed", src, __FILE__, __LINE__);  // NOI18N
    // Get a destination point
    PointDetails* destPt = tools->getPoint(sm->getSensor("NX-AE-Main"), panels->value("Alpha"), eep);  // NOI18N
    Assert::assertNotNull("Destination fetch failed", destPt, __FILE__, __LINE__);  // NOI18N
    Sensor* destSensor = sm->getSensor("NX-AE-Main");  // NOI18N
    Assert::assertNotNull("Destination sensor", destSensor, __FILE__, __LINE__);  // NOI18N

    // Disable pair, delete, add, enable
    src->setEnabled(destSensor, panels->value("Alpha"), false);  // NOI18N
    bool chkDisabled = src->isEnabled(destSensor, panels->value("Alpha"));  // NOI18N
    Assert::assertFalse("check disabled", chkDisabled, __FILE__, __LINE__);  // NOI18N
    src->removeDestination(destPt);
    QList<PointDetails*> dp1 = src->getDestinationPoints();
    Assert::assertEquals("one left", 1, dp1.size(), __FILE__, __LINE__);  // NOI18N
    src->addDestination(destPt, nullptr);
    QList<PointDetails*> dp2 = src->getDestinationPoints();
    Assert::assertEquals("now two", 2, dp2.size(), __FILE__, __LINE__);  // NOI18N
    src->setEnabled(destSensor, panels->value("Alpha"), true);  // NOI18N
    bool chkEnabled = src->isEnabled(destSensor, panels->value("Alpha"));  // NOI18N
    Assert::assertTrue("check enabled", chkEnabled, __FILE__, __LINE__);  // NOI18N
    bool chkActive = src->isRouteActive(destPt);
    Assert::assertFalse("check active", chkActive, __FILE__, __LINE__);  // NOI18N
    bool chkdest = src->isDestinationValid(destPt);
    Assert::assertTrue("check destination valid", chkdest, __FILE__, __LINE__);  // NOI18N
    QString uuid = src->getUniqueId(destSensor, panels->value("Alpha"));  // NOI18N
    Assert::assertTrue("check uuid", uuid.startsWith("IN:"), __FILE__, __LINE__);  // NOI18N
}

//@Test
/*public*/ void SourceTest::testSourceMethods() {
    // Get a source object
    Source* src = tools->getSourceInstance(sm->getSensor("NX-AE"), panels->value("Alpha"), eep);  // NOI18N
    Assert::assertNotNull("Source fetch failed", src, __FILE__, __LINE__);  // NOI18N

    PointDetails* pdx = src->getPoint();
    Assert::assertNotNull("getPoint", pdx, __FILE__, __LINE__);  // NOI18N
    LayoutBlock* lbx = src->getStart();
    Assert::assertNotNull("getStart", lbx, __FILE__, __LINE__);  // NOI18N
    QList<LayoutBlock*> lbprot = src->getSourceProtecting();
    Assert::assertEquals("getSourceProtecting", 1, lbprot.size(), __FILE__, __LINE__);  // NOI18N
    NamedBean* srcsig = src->getSourceSignal();
    Assert::assertNull("getSourceSignal", srcsig, __FILE__, __LINE__);  // NOI18N
    NamedBean* srcobj = src->getSourceObject();
    Assert::assertNotNull("getSourceObject", srcobj, __FILE__, __LINE__);  // NOI18N
}

//@BeforeClass
/*public*/ void SourceTest::setUp() throw (Exception) {
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
/*public*/ void SourceTest::tearDown() {
 //panels.forEach((name, panel) -> JUnitUtil.dispose(panel));
#if 1
 foreach(LayoutEditor* panel, *panels )
  panel->close();
#endif
 JUnitUtil::tearDown();
}
