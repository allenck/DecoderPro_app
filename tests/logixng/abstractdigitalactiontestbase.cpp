#include "abstractdigitalactiontestbase.h"
#include "assert1.h"
#include "digitalactionbean.h"

/**
 * Base class for classes that tests DigitalAction
 */
///*public*/  abstract class AbstractDigitalActionTestBase extends AbstractBaseTestBase {

//    /*public*/  abstract NamedBean createNewBean(String systemName);

    //@Test
    /*public*/  void AbstractDigitalActionTestBase::testBadSystemName() {
        bool hasThrown = false;
        try {
            // Create a bean with bad system name. This must throw an exception
            NamedBean* bean = createNewBean("IQ111");
            // We should never get here.
            Assert::assertNotNull("Bean is not null", bean->self(), __FILE__, __LINE__);
        } catch (IllegalArgumentException* e) {
            Assert::assertEquals("Exception is correct", "system name is not valid: IQ111", e->getMessage(), __FILE__, __LINE__);
            hasThrown = true;
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
//    /*public*/  void testBundle() {
//        Assert::assertEquals("strings are equal", "Memory", Bundle.getMessage("ActionMemory_Short"));
//        Assert::assertEquals("strings are equal", "Set memory IM1 to null", Bundle.getMessage("ActionMemory_Long_Null", "IM1"));
//        Assert::assertEquals("strings are equal", "Memory", Bundle.getMessage(Locale.CANADA, "ActionMemory_Short"));
//        Assert::assertEquals("strings are equal", "Set memory IM1 to null", Bundle.getMessage(Locale.CANADA, "ActionMemory_Long_Null", "IM1"));
//    }

    //@Test
    /*public*/  void AbstractDigitalActionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "Digital action" ==(((DigitalActionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }
