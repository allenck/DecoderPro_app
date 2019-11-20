#include "logixactiontest.h"
#include "junitutil.h"
#include "assert1.h"
#include "logix.h"
#include "configxmlmanager.h"
#include "instancemanager.h"
#include "logixmanager.h"
#include "signalheadmanager.h"
#include "oblockmanager.h"
#include "oblock.h"
#include "warrantmanager.h"
#include "warrant.h"

LogixActionTest::LogixActionTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the OPath class
 *
 * @author	Pete Cressman Copyright 2014
 */
///*public*/ class LogixActionTest {

    //@Test
    /*public*/ void LogixActionTest::testLogixAction() throw (Exception) {
        ConfigXmlManager* cm = new ConfigXmlManager();
//        {
//        };

        // load and display sample file. Panel file does not display screen
        File* f = new File("java/test/jmri/jmrit/logix/valid/LogixActionTest.xml");
        cm->load(f);
        ((LogixManager*)InstanceManager::getDefault("LogixManager"))->activateAllLogixs();

        Memory* im6 = InstanceManager::memoryManagerInstance()->getMemory("IM6");
        Assert::assertNotNull("Memory* IM6", im6, __FILE__, __LINE__);
        Assert::assertEquals("Contents IM6", "EastToWestOnSiding", im6->getValue(), __FILE__, __LINE__);

        // Find Enable Logix button  <<< Use GUI, but need Container to find button in
        // JUnitUtil::pressButton(container, "Enable/Disable Tests");
        // OK, do it this way
        Sensor* sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("enableButton");
        Assert::assertNotNull("Sensor* IS5", sensor, __FILE__, __LINE__);
        sensor->setState(Sensor::ACTIVE);
        sensor->setState(Sensor::INACTIVE);
        sensor->setState(Sensor::ACTIVE);
        SignalHead* sh1 = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1");
        Assert::assertNotNull("shi null", sh1, __FILE__, __LINE__);
        Assert::assertEquals("SignalHead IH1", SignalHead::RED, sh1->getAppearance(), __FILE__, __LINE__);

        // do some buttons -Sensors
        sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("ISLITERAL");
        Assert::assertNotNull("Sensor* null", sensor, __FILE__, __LINE__);
        sensor->setState(Sensor::ACTIVE);		// activate direct logix action
        Sensor* is1 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("sensor1");
        Assert::assertNotNull("is1 null", is1, __FILE__, __LINE__);
        Assert::assertEquals("direct set Sensor* IS1 active", Sensor::ACTIVE, is1->getState(), __FILE__, __LINE__);		// action
        sensor = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("ISINDIRECT");
        Assert::assertNotNull("Sensor* null", sensor, __FILE__, __LINE__);
        sensor->setState(Sensor::ACTIVE);		// activate Indirect logix action
        Assert::assertEquals("Indirect set Sensor* IS1 inactive", Sensor::INACTIVE, is1->getState(), __FILE__, __LINE__);		// action

        // SignalHead buttons
        Sensor* is4 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS4");
        Assert::assertNotNull("is4 null", is4, __FILE__, __LINE__);
        is4->setState(Sensor::ACTIVE);		// activate direct logix action
        Assert::assertEquals("direct set SignalHead IH1 to Green", SignalHead::GREEN, sh1->getAppearance(), __FILE__, __LINE__);
        is4->setState(Sensor::INACTIVE);		// activate direct logix action
        Assert::assertEquals("direct set SignalHead IH1 to Red", SignalHead::RED, sh1->getAppearance(), __FILE__, __LINE__);

        Memory* im3 = InstanceManager::memoryManagerInstance()->getMemory("IM3");
        Assert::assertNotNull("Memory* IM3", im3, __FILE__, __LINE__);
        Assert::assertEquals("Contents IM3", "IH1", im3->getValue(), __FILE__, __LINE__);
        Sensor* is3 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS3");
        Assert::assertNotNull("is3 null", is3, __FILE__, __LINE__);
        is3->setState(Sensor::ACTIVE);		// activate indirect logix action
        Assert::assertEquals("Indirect set SignalHead IH1 to Green", SignalHead::GREEN, sh1->getAppearance(), __FILE__, __LINE__);
        is3->setState(Sensor::INACTIVE);		// activate indirect logix action
        Assert::assertEquals("Indirect set SignalHead IH1 to Red", SignalHead::RED, sh1->getAppearance(), __FILE__, __LINE__);
        // change Memory* value
        im3->setValue("IH2");
        is3->setState(Sensor::ACTIVE);		// activate logix action
        Assert::assertEquals("Contents IM3", "IH2", im3->getValue(), __FILE__, __LINE__);
        SignalHead* sh2 = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH2");
        Assert::assertNotNull("sh2 null", sh2, __FILE__, __LINE__);
        Assert::assertEquals("Indirect SignalHead IH2", SignalHead::GREEN, sh2->getAppearance(), __FILE__, __LINE__);

        // Turnout Buttons
        Sensor* is6 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS6");
        Assert::assertNotNull("is6 null", is6, __FILE__, __LINE__);
        is6->setState(Sensor::ACTIVE);		// activate direct logix action
        Turnout* it2 = InstanceManager::turnoutManagerInstance()->getTurnout("IT2");
        Assert::assertNotNull("it2 null", it2, __FILE__, __LINE__);
        Assert::assertEquals("direct set Turnout IT2 to Closed", Turnout::CLOSED, it2->getState(), __FILE__, __LINE__);
        Memory* im4 = InstanceManager::memoryManagerInstance()->getMemory("IM4");
        Assert::assertNotNull("im4 null", im4, __FILE__, __LINE__);
        Assert::assertEquals("Contents IM4", "IT3", im4->getValue(), __FILE__, __LINE__);
        Sensor* is7 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS7");
        Assert::assertNotNull("is7 null", is7, __FILE__, __LINE__);
        is7->setState(Sensor::INACTIVE);		// activate indirect logix action
        Turnout* it3 = InstanceManager::turnoutManagerInstance()->getTurnout("IT3");
        Assert::assertNotNull("it3 null", it3, __FILE__, __LINE__);
        Assert::assertEquals("Indirect set Turnout IT2 to Thrown", Turnout::THROWN, it3->getState(), __FILE__, __LINE__);
        is7->setState(Sensor::ACTIVE);		// activate indirect logix action
        Assert::assertEquals("Indirect set Turnout IT2 to Closed", Turnout::CLOSED, it3->getState(), __FILE__, __LINE__);
        // change Memory* value
        im4->setValue("IT2");
        Assert::assertEquals("Contents IM4", "IT2", im4->getValue(), __FILE__, __LINE__);
        is7->setState(Sensor::INACTIVE);		// activate indirect logix action
        Assert::assertEquals("Indirect set Turnout IT2 to Thrown", Turnout::THROWN, it2->getState(), __FILE__, __LINE__);
        is7->setState(Sensor::ACTIVE);		// activate indirect logix action
        Assert::assertEquals("Indirect set Turnout IT2 to Closed", Turnout::CLOSED, it2->getState(), __FILE__, __LINE__);

        // OBlock Buttons
        Sensor* is10 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS10");
        int st = is10->getKnownState();
        OBlock* ob1 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("Left");
        Assert::assertEquals("OBlock OB1", (OBlock::OUT_OF_SERVICE | Sensor::INACTIVE), ob1->getState(), __FILE__, __LINE__);
        OBlock* ob2 = ((OBlockManager*)InstanceManager::getDefault("OBlockManager"))->getOBlock("Right");
        Assert::assertEquals("OBlock OB2", (OBlock::TRACK_ERROR | Sensor::INACTIVE), ob2->getState(), __FILE__, __LINE__);
        Sensor* is8 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS8");
        Assert::assertNotNull("is8 null", is8, __FILE__, __LINE__);
        is8->setState(Sensor::ACTIVE);			// direct action
        Assert::assertEquals("Direct set OBlock OB1 to normal", Sensor::INACTIVE, ob1->getState(), __FILE__, __LINE__);
        is8->setState(Sensor::INACTIVE);			// direct action
        Assert::assertEquals("Direct set OBlock OB1 to OOS", (OBlock::OUT_OF_SERVICE | Sensor::INACTIVE), ob1->getState(), __FILE__, __LINE__);
        Sensor* is9 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS9");
        Assert::assertNotNull("is9 null", is9, __FILE__, __LINE__);
        is9->setState(Sensor::ACTIVE);			// indirect action
        Assert::assertEquals("Indirect set OBlock OB2 to normal", Sensor::INACTIVE, ob2->getState(), __FILE__, __LINE__);
        // change Memory* value
        Memory* im5 = InstanceManager::memoryManagerInstance()->getMemory("IM5");
        Assert::assertNotNull("im5 null", im5, __FILE__, __LINE__);
        im5->setValue("OB1");
        is9->setState(Sensor::INACTIVE);			// indirect action
        Assert::assertEquals("Indirect set OBlock OB1 to normal",
                (OBlock::TRACK_ERROR | OBlock::OUT_OF_SERVICE | Sensor::INACTIVE), ob1->getState(), __FILE__, __LINE__);
        is9->setState(Sensor::ACTIVE);			// indirect action
        is8->setState(Sensor::ACTIVE);			// indirect action
        Assert::assertEquals("Direct set OBlock OB1 to normal", Sensor::INACTIVE, ob1->getState(), __FILE__, __LINE__);

        // Warrant buttons
        Sensor* is14 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS14");
        Assert::assertNotNull("is14 null", is14, __FILE__, __LINE__);
        is14->setState(Sensor::ACTIVE);			// indirect action
        Warrant* w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant("EastToWestOnSiding");
        Assert::assertTrue("warrant EastToWestOnSiding allocated", w->isAllocated(), __FILE__, __LINE__);
        Sensor* is15 = ((ProxySensorManager*)InstanceManager::sensorManagerInstance())->getSensor("IS15");
        Assert::assertNotNull("is15 null", is15, __FILE__, __LINE__);
        is15->setState(Sensor::ACTIVE);			// indirect action
        Assert::assertFalse("warrant EastToWestOnSiding deallocated", w->isAllocated(), __FILE__, __LINE__);
        // change Memory* value
        im6->setValue("WestToEastOnMain");
        is14->setState(Sensor::INACTIVE);			// toggle
        is14->setState(Sensor::ACTIVE);			// indirect action
        Warrant* w2 = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant("WestToEastOnMain");
        Assert::assertTrue("warrant WestToEastOnMain allocated", w2->isAllocated(), __FILE__, __LINE__);
        im6->setValue("LeftToRightOnPath");
        is14->setState(Sensor::INACTIVE);			// toggle
        is14->setState(Sensor::ACTIVE);			// indirect action
        w = ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getWarrant("LeftToRightOnPath");
        Assert::assertTrue("warrant LeftToRightOnPath allocated", w->isAllocated(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void LogixActionTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();

        JUnitUtil::initLogixManager();
        JUnitUtil::initConditionalManager();
    }

    //@After
    /*public*/ void LogixActionTest::tearDown() {
        JUnitUtil::tearDown();
    }
