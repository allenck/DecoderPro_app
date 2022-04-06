#include "abstractstringexpressiontestbase.h"
#include "stringexpressionbean.h"
#include "junitappender.h"
#include "assert1.h"
#include "stringexpressionbean.h"
#include "stringio.h"
#include "malesocket.h"
#include "defaultmalestringexpressionsocket.h"

/**
 * Test AbstractStringExpression
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  abstract class AbstractStringExpressionTestBase extends AbstractBaseTestBase {

//    /*public*/  abstract NamedBean createNewBean(String systemName) throws Exception;

    //@Test
    /*public*/  void AbstractStringExpressionTestBase::testBadSystemName() /*throws Exception */{
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
    /*public*/  void AbstractStringExpressionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "String expression" ==(((StringExpressionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractStringExpressionTestBase::testState() /*throws JmriException*/ {
        StringExpressionBean* _expression = (StringExpressionBean*)_base->bself();
        _expression->setState(StringIO::INCONSISTENT);
        Assert::assertTrue("State matches", StringIO::INCONSISTENT == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringExpression.", __FILE__, __LINE__);
        _expression->setState(StringIO::UNKNOWN);
        Assert::assertTrue("State matches", StringIO::UNKNOWN == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringExpression.", __FILE__, __LINE__);
        _expression->setState(StringIO::INCONSISTENT);
        Assert::assertTrue("State matches", StringIO::INCONSISTENT == _expression->getState(), __FILE__, __LINE__);
        JUnitAppender::assertWarnMessage("Unexpected call to getState in AbstractStringExpression.", __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractStringExpressionTestBase::testEnableAndEvaluate() /*throws Exception*/ {
        StringExpressionBean* _expression = (StringExpressionBean*)_baseMaleSocket;
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertNotEquals("Strings don't match", "", _expression->evaluate(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(false);
        Assert::assertFalse("male socket is disabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertEquals("Strings match", "", _expression->evaluate(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(true);
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertNotEquals("Strings don't match", "", _expression->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractStringExpressionTestBase::testDebugConfig() /*throws Exception*/ {
        QString value1 = "Something else";
        QString value2 = "Some other thing";
        StringExpressionBean* _expression = (StringExpressionBean*)_baseMaleSocket;
        Assert::assertNotEquals("Strings don't match", value1, _expression->evaluate(), __FILE__, __LINE__);
        Assert::assertNotEquals("Strings don't match", value2, _expression->evaluate(), __FILE__, __LINE__);
        DefaultMaleStringExpressionSocket::StringExpressionDebugConfig* debugConfig = new DefaultMaleStringExpressionSocket::StringExpressionDebugConfig();
        debugConfig->_forceResult = true;
        debugConfig->_result = value1;
        _baseMaleSocket->setDebugConfig(debugConfig);
        Assert::assertEquals("String match", value1, _expression->evaluate(), __FILE__, __LINE__);
        debugConfig->_result = value2;
        Assert::assertEquals("String match", value2, _expression->evaluate(), __FILE__, __LINE__);
        debugConfig->_forceResult = false;
        Assert::assertNotEquals("String don't match", value1, _expression->evaluate(), __FILE__, __LINE__);
        Assert::assertNotEquals("String don't match", value2, _expression->evaluate(), __FILE__, __LINE__);
    }
