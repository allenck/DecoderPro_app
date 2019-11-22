#include "warranttest.h"
#include "assert1.h"
#include "sensor.h"
#include "oblock.h"
#include "oblockmanager.h"
#include "blockorder.h"
#include "speedutil.h"
#include "junitappender.h"
#include "instancemanager.h"
#include "portalmanager.h"
#include "portal.h"
#include "turnoutmanager.h"
#include "beansetting.h"
#include "opath.h"
#include "throttlesetting.h"

WarrantTest::WarrantTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the Warrant creation
 *
 * @author Pete Cressman 2015
 *
 * todo - test error conditions
 */
 // /*public*/ class WarrantTest {


    //@Test
    /*public*/ void WarrantTest::testCTor() {
        Assert::assertNotNull("exists", warrant, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testSetAndGetTrainName() {
        warrant->setTrainName("TestTrain");
        Assert::assertEquals("Train Name", "TestTrain", warrant->getTrainName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testGetSpeedUtil() {
        SpeedUtil* su = warrant->getSpeedUtil();
        Assert::assertNotNull("SpeedUtil nullptr", su, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testAddPropertyChangeListener() {
        PropertyChangeListener* listener = new WarrantListener(warrant);
        Assert::assertNotNull("PropertyChangeListener", listener, __FILE__, __LINE__);
        warrant->addPropertyChangeListener(listener);
    }

    //@Test
    /*public*/ void WarrantTest::testAllocateAndDeallocateWarrant() {
        try {
            sWest->setState(Sensor::INACTIVE);
            sEast->setState(Sensor::ACTIVE);
            sNorth->setState(Sensor::INACTIVE);
            sSouth->setState(Sensor::ACTIVE);
        } catch (JmriException je) {
        }
        bWest->allocate(warrant);
        bEast->allocate(warrant);
        Assert::assertEquals("Block Detection 3", OBlock::UNOCCUPIED | OBlock::ALLOCATED, bWest->getState(), __FILE__, __LINE__);
        Assert::assertEquals("Block Detection 4", OBlock::OCCUPIED | OBlock::ALLOCATED, bEast->getState(), __FILE__, __LINE__);
        try {
            sEast->setState(Sensor::INACTIVE);
            sSouth->setState(Sensor::INACTIVE);
            sNorth->setState(Sensor::ACTIVE);     // start block of warrant
        } catch (JmriException je) {
        }
        bWest->deAllocate(warrant);
        bEast->deAllocate(warrant);
        Assert::assertEquals("Block Detection 5", OBlock::UNOCCUPIED, bWest->getState(), __FILE__, __LINE__);
        Assert::assertEquals("Block Detection 6", OBlock::UNOCCUPIED, bEast->getState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testSetRouteUsingViaOrders() {
        try {
            sEast->setState(Sensor::INACTIVE);
            sSouth->setState(Sensor::INACTIVE);
            sNorth->setState(Sensor::ACTIVE);     // start block of warrant
        } catch (JmriException je) {
        }
        QList<BlockOrder*>* orders = new QList<BlockOrder*>();
        orders->append(new BlockOrder(_OBlockMgr->getOBlock("North"), "NorthToWest", "", "NorthWest"));
        BlockOrder* viaOrder = new BlockOrder(_OBlockMgr->getOBlock("West"), "SouthToNorth", "NorthWest", "SouthWest");
        orders->append(viaOrder);
        BlockOrder* lastOrder = new BlockOrder(_OBlockMgr->getOBlock("South"), "SouthToWest", "SouthWest", nullptr);
        orders->append(lastOrder);

        warrant->setViaOrder(viaOrder);
        warrant->setBlockOrders(orders);
        Assert::assertEquals("BlockOrder", warrant->getLastOrder()->toString(), lastOrder->toString(), __FILE__, __LINE__);
        Assert::assertEquals("BlockOrder", warrant->getViaOrder()->toString(), viaOrder->toString(), __FILE__, __LINE__);

        QString msg = warrant->allocateRoute(false, orders);
        Assert::assertNull("allocateRoute - " + msg, msg, __FILE__, __LINE__);
        msg = warrant->checkStartBlock();
        Assert::assertNull("checkStartBlock - " + msg, msg, __FILE__, __LINE__);
        msg = warrant->checkRoute();
        Assert::assertNull("checkRoute - " + msg, msg, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testSetRoute() {
        try {
            sEast->setState(Sensor::INACTIVE);
            sSouth->setState(Sensor::INACTIVE);
            sNorth->setState(Sensor::ACTIVE);     // start block of warrant
        } catch (JmriException je) {
        }
        QList<BlockOrder*>* orders = new QList<BlockOrder*>();
        orders->append(new BlockOrder(_OBlockMgr->getOBlock("North"), "NorthToWest", "", "NorthWest"));
        BlockOrder* viaOrder = new BlockOrder(_OBlockMgr->getOBlock("West"), "SouthToNorth", "NorthWest", "SouthWest");
        orders->append(viaOrder);
        BlockOrder* lastOrder = new BlockOrder(_OBlockMgr->getOBlock("South"), "SouthToWest", "SouthWest", nullptr);
        orders->append(lastOrder);

        QString msg = warrant->allocateRoute(false, orders);
        Assert::assertNull("allocateRoute - " + msg, msg, __FILE__, __LINE__);
        msg = warrant->checkStartBlock();
        Assert::assertNull("checkStartBlock - " + msg, msg, __FILE__, __LINE__);
        msg = warrant->checkRoute();
        Assert::assertNull("checkRoute - " + msg, msg, __FILE__, __LINE__);

        Assert::assertEquals("BlockOrder", warrant->getLastOrder()->toString(), lastOrder->toString(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::setThrottleCommands() {
        warrant->setThrottleCommands(new QList<ThrottleSetting*>());
        warrant->addThrottleCommand(new ThrottleSetting(0, "Speed", "0.0", "North"));
        warrant->addThrottleCommand(new ThrottleSetting(10, "Speed", "0.4", "North"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "NoOp", "Enter Block", "West"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.5", "West"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "NoOp", "Enter Block", "South"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.3", "South"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.0", "South"));
        QList<ThrottleSetting*>* list = warrant->getThrottleCommands();
        Assert::assertEquals("ThrottleCommands", 7, list->size(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void WarrantTest::testWarrant() throw (JmriException) {
        sEast->setState(Sensor::INACTIVE);
        sSouth->setState(Sensor::INACTIVE);
        sNorth->setState(Sensor::ACTIVE);     // start block of warrant

        QList<BlockOrder*>* orders = new QList<BlockOrder*>();
        orders->append(new BlockOrder(_OBlockMgr->getOBlock("North"), "NorthToWest", "", "NorthWest"));
        BlockOrder* viaOrder = new BlockOrder(_OBlockMgr->getOBlock("West"), "SouthToNorth", "NorthWest", "SouthWest");
        orders->append(viaOrder);
        BlockOrder* lastOrder = new BlockOrder(_OBlockMgr->getOBlock("South"), "SouthToWest", "SouthWest", nullptr);
        orders->append(lastOrder);

        warrant->setThrottleCommands(new QList<ThrottleSetting*>());
        warrant->addThrottleCommand(new ThrottleSetting(0, "Speed", "0.0", "North"));
        warrant->addThrottleCommand(new ThrottleSetting(10, "Speed", "0.4", "North"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "NoOp", "Enter Block", "West"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.5", "West"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "NoOp", "Enter Block", "South"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.3", "South"));
        warrant->addThrottleCommand(new ThrottleSetting(100, "Speed", "0.0", "South"));

        warrant->getSpeedUtil()->setDccAddress("999(L)");
        QString msg = warrant->allocateRoute(false, orders);
        SpeedUtil* su = warrant->getSpeedUtil();
        su->setOrders(orders);

        warrant->setTrainName("TestTrain");
        PropertyChangeListener* listener = new WarrantListener(warrant);
        warrant->addPropertyChangeListener(listener);

        msg = warrant->setRunMode(Warrant::MODE_RUN, nullptr, nullptr, nullptr, false);
        Assert::assertNull("setRunMode - " + msg, msg, __FILE__, __LINE__);

//        jmri.util.JUnitUtil::waitFor(() -> {
//            QString m = warrant->getRunningMessage();
//            return m.endsWith("Cmd #2.") || m.endsWith("Cmd #3.");
//        }, "Train starts to move after 2nd command");
        ReleaseUntil* r1 = new ReleaseUntilWT1(this);
        JUnitUtil::waitFor(r1, "Train starts to move after 2nd command", __FILE__, __LINE__);
//        JUnitUtil::releaseThread(this, 100); // What should we specifically waitFor?

        // confirm one message logged
        JUnitAppender::assertWarnMessage("Path NorthToWest in block North has length zero. Cannot run NXWarrants or ramp speeds through blocks with zero length.", __FILE__, __LINE__);

//        jmri.util.ThreadingUtil.runOnLayout(() -> {
            try {
                sWest->setState(Sensor::ACTIVE);
            } catch (JmriException e) {
                Assert::fail("Unexpected Exception: " + e.getMessage(), __FILE__, __LINE__);
            }
//        });
//        jmri.util.JUnitUtil::releaseThread(this, 100); // What should we specifically waitFor?

//        jmri.util.ThreadingUtil.runOnLayout(() -> {
            try {
                sSouth->setState(Sensor::ACTIVE);
            } catch (JmriException e) {
                Assert::fail("Unexpected Exception: " + e.getMessage(), __FILE__, __LINE__);
            }
//        });
//        jmri.util.JUnitUtil::releaseThread(this, 100);

        // wait for done
//        jmri.util.JUnitUtil::waitFor(() -> {
//            return warrant->getRunningMessage().equals("Idle");
//        }, "warrant not done");
        JUnitUtil::waitFor(new ReleaseUntilWT2(this), "warrant not done", __FILE__, __LINE__);

    }

//    class WarrantListener implements PropertyChangeListener {

//        Warrant warrant;

//        WarrantListener(Warrant w) {
//            warrant = w;
//        }

        //@Override
        /*public*/ void WarrantListener::propertyChange(PropertyChangeEvent* e) {
//            String property = e->getPropertyName();
//            System.out.println("propertyChange \""+property+
//                    "\" old= "+e->getOldValue()+" new= "+e->getNewValue());
            Assert::assertEquals("propertyChange", warrant, e->getSource(), __FILE__, __LINE__);
//            System.out.println(warrant->getRunningMessage());
        }
//    }

    //@Before
    /*public*/ void WarrantTest::setUp() {
        JUnitUtil::setUp();

        JUnitUtil::resetProfileManager();
        JUnitUtil::initDebugThrottleManager();
        JUnitUtil::initShutDownManager();
        JUnitUtil::initRosterConfigManager();

        // setup the warrant preliminaries.
        _OBlockMgr = (OBlockManager*)InstanceManager::getDefault("OBlockManager");
        bWest = _OBlockMgr->createNewOBlock("OB1", "West");
        bEast = _OBlockMgr->createNewOBlock("OB2", "East");
        bNorth = _OBlockMgr->createNewOBlock("OB3", "North");
        bSouth = _OBlockMgr->createNewOBlock("OB4", "South");

        _portalMgr = (PortalManager*)InstanceManager::getDefault("PortalManager");
        Portal* pNorthWest = _portalMgr->createNewPortal(nullptr, "NorthWest");
        pNorthWest->setToBlock(bWest, false);
        pNorthWest->setFromBlock(bNorth, false);
        Portal* pSouthWest = _portalMgr->createNewPortal(nullptr, "SouthWest");
        pSouthWest->setToBlock(bWest, false);
        pSouthWest->setFromBlock(bSouth, false);

        Portal* pNorthEast = _portalMgr->createNewPortal(nullptr, "NorthEast");
        pNorthEast->setToBlock(_OBlockMgr->getOBlock("OB2"), false);
        pNorthEast->setFromBlock(_OBlockMgr->getOBlock("North"), false);
        Portal* pSouthEast = _portalMgr->createNewPortal(nullptr, "SouthEast");
        OBlock* east = _OBlockMgr->getOBlock("OB2");
        pSouthEast->setToBlock(east, false);
        pSouthEast->setFromBlock(_OBlockMgr->getOBlock("South"), false);

        _turnoutMgr = InstanceManager::turnoutManagerInstance();
        Turnout* northSwitch = _turnoutMgr->newTurnout("IT1", "NorthSwitch");
        QList<BeanSetting*> settings = QList<BeanSetting*>();
        settings.append(new BeanSetting(northSwitch, "NorthSwitch", Turnout::CLOSED));
        OBlock* north = _OBlockMgr->getOBlock("North");
        OPath* path = new OPath("NorthToWest", north, nullptr, _portalMgr->getPortal("NorthWest"), settings);
        north->addPath(path);

        settings = QList<BeanSetting*>();
        settings.append(new BeanSetting(northSwitch, "NorthSwitch", Turnout::THROWN));
        path = new OPath("NorthToEast", north, nullptr, _portalMgr->getPortal("NorthEast"), settings);
        north->addPath(path);

        Turnout* southSwitch = _turnoutMgr->newTurnout("IT2", "SouthSwitch");
        OBlock* south = _OBlockMgr->getOBlock("South");
        settings = QList<BeanSetting*>();
        settings.append(new BeanSetting(southSwitch, "SouthSwitch", Turnout::THROWN));
        path = new OPath("SouthToEast", south, nullptr, _portalMgr->getPortal("SouthEast"), settings);
        south->addPath(path);
        settings = QList<BeanSetting*>();
        settings.append(new BeanSetting(southSwitch, "SouthSwitch", Turnout::CLOSED));
        path = new OPath("SouthToWest", south, nullptr, south->getPortalByName("SouthWest"), settings);
        south->addPath(path);

        bSouth->setLength(100);

        settings = QList<BeanSetting*>();
        OBlock* block = _OBlockMgr->getOBlock("West");
        path = new OPath("SouthToNorth", block, _portalMgr->getPortal("NorthWest"), _portalMgr->getPortal("SouthWest"), settings);
        _OBlockMgr->getOBlock("West")->addPath(path);
        path->setLength(200);
        settings = QList<BeanSetting*>();
        block = _OBlockMgr->getOBlock("East");
        path = new OPath("NorthToSouth", block, south->getPortalByName("SouthEast"), north->getPortalByName("NorthEast"), settings);
        _OBlockMgr->getOBlock("East")->addPath(path);

        _sensorMgr = (SensorManager*)InstanceManager::getDefault("SensorManager");
        sWest = _sensorMgr->newSensor("IS1", "WestSensor");
        sEast = _sensorMgr->newSensor("IS2", "EastSensor");
        sNorth = _sensorMgr->newSensor("IS3", "NorthSensor");
        sSouth = _sensorMgr->newSensor("IS4", "SouthSensor");
        bWest->setSensor("WestSensor");
        bEast->setSensor("IS2");
        bNorth->setSensor("NorthSensor");
        bSouth->setSensor("IS4");
        warrant = new Warrant("IW0", "AllTestWarrant");
    }

    //@After
    /*public*/ void WarrantTest::tearDown() {
        _OBlockMgr = nullptr;
        _portalMgr = nullptr;
        _sensorMgr = nullptr;
        _turnoutMgr = nullptr;
        bWest = nullptr;
        bEast = nullptr;
        bNorth = nullptr;
        bSouth = nullptr;
        sWest = nullptr;
        sEast = nullptr;
        sNorth = nullptr;
        sSouth = nullptr;
        warrant = nullptr;
        JUnitUtil::tearDown();
    }
