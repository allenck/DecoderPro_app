#include "defaultconditionalmanagertest.h"
#include "defaultconditionalmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultlogix.h"
#include "defaultlogixmanager.h"
#include "instancemanager.h"

/**
 * Tests for the jmri.managers.DefaultConditionalManager class.
 *
 * @author Bob Jacobsen Copyright (C) 2015
 */
///*public*/  class DefaultConditionalManagerTest extends AbstractManagerTestBase<jmri.ConditionalManager,jmri.Conditional> {

    //@Test
    /*public*/  void DefaultConditionalManagerTest::testCtor() {
        Assert::assertNotNull("exists",_manager->mself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultConditionalManagerTest::testCreate() {
        ConditionalManager* m = (DefaultConditionalManager*)_manager->mself();

        Conditional* c1 = m->createNewConditional("IX01C01", "");
        Conditional* c2 = m->createNewConditional("IX01C02", "");

        Assert::assertFalse(c1 == c2, __FILE__, __LINE__);
        Assert::assertFalse(c1->equals(c2), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultConditionalManagerTest::testUserNameOverlap() {
        ConditionalManager* m = (DefaultConditionalManager*)_manager->mself();

        Conditional* c1 = m->createNewConditional("IX02C01", "Foo");
        Conditional* c2 = m->createNewConditional("IX02C02", "Foo");

        Assert::assertTrue(c1->getUserName() == ("Foo"), __FILE__, __LINE__);
        Assert::assertTrue(c2->getUserName() == ("Foo"), __FILE__, __LINE__);
    }

    // No manager-specific system name validation at present
    //@Test
    //@Override
    /*public*/  void testMakeSystemNameWithNoPrefixNotASystemName() {}

    // No manager-specific system name validation at present
    //@Test
    //@Override
    /*public*/  void testMakeSystemNameWithPrefixNotASystemName() {}

    //@BeforeEach
    /*public*/  void DefaultConditionalManagerTest::setUp() /*throws Exception*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initInternalLightManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initIdTagManager();
        JUnitUtil::initLogixManager();
        JUnitUtil::initConditionalManager();

        Logix* x1 = new DefaultLogix("IX01");
        Assert::assertNotNull("Logix x1 is null!", x1, __FILE__, __LINE__);
        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->Register(x1);

        Logix* x2 = new DefaultLogix("IX02");
        Assert::assertNotNull("Logix x2 is null!", x2, __FILE__, __LINE__);
        ((DefaultLogixManager*)InstanceManager::getDefault("LogixManager"))->Register(x2);
        _manager = new DefaultConditionalManager(InstanceManager::getDefault("InternalSystemConnectionMemo"));
    }

    //@AfterEach
    /*public*/  void DefaultConditionalManagerTest::tearDown() /*throws Exception*/ {
        _manager = nullptr;
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::deregisterEditorManagerShutdownTask();
        JUnitUtil::tearDown();
    }
