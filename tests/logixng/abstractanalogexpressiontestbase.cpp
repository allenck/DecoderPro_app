#include "abstractanalogexpressiontestbase.h"
#include "assert1.h"
#include "Analogexpressionbean.h"
#include "analogio.h"
#include "junitappender.h"
#include "malesocket.h"
#include "defaultmaleanalogexpressionsocket.h"

/**
 * Test AbstractAnalogExpression
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  abstract class AbstractAnalogExpressionTestBase extends AbstractBaseTestBase {

//    /*public*/  abstract NamedBean createNewBean(String systemName) throws Exception;

    //@Test
    /*public*/  void AbstractAnalogExpressionTestBase::testBadSystemName() /*throws Exception*/ {
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
    /*public*/  void AbstractAnalogExpressionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "Analog expression" == (((AnalogExpressionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractAnalogExpressionTestBase::testState() /*throws JmriException */{
        AnalogExpressionBean* _expression = (AnalogExpressionBean*)_base->bself();
        _expression->setState(AnalogIO::INCONSISTENT);
        Assert::assertTrue("State matches", AnalogIO::INCONSISTENT == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogExpression.", __FILE__, __LINE__);
        _expression->setState(AnalogIO::UNKNOWN);
        Assert::assertTrue("State matches", AnalogIO::UNKNOWN == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogExpression.", __FILE__, __LINE__);
        _expression->setState(AnalogIO::INCONSISTENT);
        Assert::assertTrue("State matches", AnalogIO::INCONSISTENT == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractAnalogExpression.", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractAnalogExpressionTestBase::testEnableAndEvaluate() /*throws Exception*/ {
        AnalogExpressionBean* _expression = (AnalogExpressionBean*)_baseMaleSocket;
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertNotEquals("Double don't match", 0.0, _expression->evaluate(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(false);
        Assert::assertFalse("male socket is disabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertEquals("Double match", 0.0, _expression->evaluate(), 0, __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(true);
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertNotEquals("Double don't match", 0.0, _expression->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractAnalogExpressionTestBase::testDebugConfig() /*throws Exception*/ {
        double value1 = 88.99;
        double value2 = 99.88;
        AnalogExpressionBean* _expression = (AnalogExpressionBean*)_baseMaleSocket;
        Assert::assertNotEquals("Double don't match", value1, _expression->evaluate(), __FILE__, __LINE__);
        Assert::assertNotEquals("Double don't match", value2, _expression->evaluate(), __FILE__, __LINE__);
        AnalogExpressionDebugConfig* debugConfig = new AnalogExpressionDebugConfig();
        debugConfig->_forceResult = true;
        debugConfig->_result = value1;
        _baseMaleSocket->setDebugConfig(debugConfig);
        Assert::assertEquals("Double match", value1, _expression->evaluate(), 0, __FILE__, __LINE__);
        debugConfig->_result = value2;
        Assert::assertEquals("Double match", value2, _expression->evaluate(), 0, __FILE__, __LINE__);
        debugConfig->_forceResult = false;
        Assert::assertNotEquals("Double don't match", value1, _expression->evaluate(), __FILE__, __LINE__);
        Assert::assertNotEquals("Double don't match", value2, _expression->evaluate(), __FILE__, __LINE__);
    }
