#include "abstractanalogactiontestbase.h"
#include "assert1.h"
#include "junitappender.h"
#include "analogactionbean.h"
#include "analogio.h"

/**
 * Test AbstractAnalogAction
 *
 * @author Daniel Bergqvist 2018
 */
//public abstract class AbstractAnalogActionTestBase extends AbstractBaseTestBase {

//    /*public*/ abstract NamedBean createNewBean(String systemName) throws Exception;

    //@Test
    /*public*/ void AbstractAnalogActionTestBase::testBadSystemName() /*throws Exception */{
        bool hasThrown = false;
        try {
            // Create a bean with bad system name. This must throw an exception
            NamedBean* bean = createNewBean("IQ111");
            // We should never get here.
            Assert::assertNotNull("Bean is not null", (QObject*)bean, __FILE__, __LINE__);
        } catch (IllegalArgumentException* e) {
            Assert::assertEquals("Exception is correct", "system name is not valid", e->getMessage(), __FILE__, __LINE__);
            hasThrown = true;
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractAnalogActionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "Analog action" == (((AnalogActionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractAnalogActionTestBase::testState() /*throws JmriException*/ {
        AnalogActionBean* _action = (AnalogActionBean*)_base->bself();
        _action->setState(AnalogIO::INCONSISTENT);
        Assert::assertTrue("State matches", AnalogIO::INCONSISTENT == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogAction.");
        _action->setState(AnalogIO::UNKNOWN);
        Assert::assertTrue("State matches", AnalogIO::UNKNOWN == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogAction.");
        _action->setState(AnalogIO::INCONSISTENT);
        Assert::assertTrue("State matches", AnalogIO::INCONSISTENT == _action->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogAction.");
    }
