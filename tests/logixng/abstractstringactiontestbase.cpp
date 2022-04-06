#include "abstractstringactiontestbase.h"
#include "stringactionbean.h"
#include "assert1.h"
#include "junitappender.h"
#include "stringio.h"

/**
 * Test AbstractStringAction
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  abstract class AbstractStringActionTestBase extends AbstractBaseTestBase {

//    /*public*/  abstract NamedBean createNewBean(String systemName) throws Exception;

    //@Test
    /*public*/  void AbstractStringActionTestBase::testBadSystemName() /*throws Exception*/ {
        bool hasThrown = false;
        try {
            // Create a bean with bad system name. This must throw an exception
            NamedBean* bean = createNewBean("IQ111");
            // We should never get here.
            Assert::assertNotNull("Bean is not null", (QObject*)bean, __FILE__, __LINE__);
        } catch (IllegalArgumentException* e) {
            Assert::assertEquals("Exception is correct", "system name is not valid: IQ111", e->getMessage(), __FILE__, __LINE__);
            hasThrown = true;
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractStringActionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "String action" ==(((StringActionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractStringActionTestBase::testState() /*throws JmriException*/ {
        StringActionBean* _action = (StringActionBean*)_base->bself();
        _action->setState(StringIO::INCONSISTENT);
        Assert::assertTrue("State matches", StringIO::INCONSISTENT == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringAction.", __FILE__, __LINE__);
        _action->setState(StringIO::UNKNOWN);
        Assert::assertTrue("State matches", StringIO::UNKNOWN == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringAction.");
        _action->setState(StringIO::INCONSISTENT);
        Assert::assertTrue("State matches", StringIO::INCONSISTENT == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringAction.", __FILE__, __LINE__);
    }
