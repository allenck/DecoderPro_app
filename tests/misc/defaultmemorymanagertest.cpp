#include "defaultmemorymanagertest.h"
#include "junitutil.h"
#include "defaultmemorymanager.h"
#include "memory.h"
#include "assert1.h"
#include "junitappender.h"
#include "instancemanager.h"

DefaultMemoryManagerTest::DefaultMemoryManagerTest()
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class DefaultMemoryManagerTest extends AbstractProvidingManagerTestBase<jmri.MemoryManager,jmri.Memory> {

//@Test
/*public*/ void DefaultMemoryManagerTest::testIMthrows() {
    try {
        ((DefaultMemoryManager*)_manager->mself())->provideMemory("IM");
        Assert::fail("Expected exception not thrown", __FILE__, __LINE__);
    } catch (IllegalArgumentException* e) {
        // nothing to do
    }
    JUnitAppender::assertErrorMessage("Invalid system name for Memory: System name \"" + _manager->getSystemNamePrefix() + "\" is missing suffix.", __FILE__, __LINE__);
}

//@Test
/*public*/ void DefaultMemoryManagerTest::testBlankThrows() {
    try {
        ((DefaultMemoryManager*)_manager->mself())->provideMemory("");
        Assert::fail("Expected exception not thrown", __FILE__, __LINE__);
    } catch (IllegalArgumentException* e) {
        // nothing to do
    }
    JUnitAppender::assertErrorMessage("Invalid system name for Memory: System name must start with \"" + _manager->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
}

//@Test
/*public*/ void DefaultMemoryManagerTest::testCreatesiM() {
    Memory* im = ((DefaultMemoryManager*)_manager->mself())->provideMemory("iM");
    Assert::assertNotNull("iM created",im, __FILE__, __LINE__);
    Assert::assertEquals("correct system name","IMiM",im->getSystemName(), __FILE__, __LINE__);
}

//@Before
/*public*/ void DefaultMemoryManagerTest::setUp() {
    JUnitUtil::setUp();
    _manager = new DefaultMemoryManager((InternalSystemConnectionMemo*)InstanceManager::getDefault("InternalSystemConnectionMemo"));
}

//@After
/*public*/ void DefaultMemoryManagerTest::tearDown() {
    JUnitUtil::tearDown();
}
