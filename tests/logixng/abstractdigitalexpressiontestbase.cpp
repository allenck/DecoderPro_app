#include "abstractdigitalexpressiontestbase.h"
#include "assert1.h"
#include "digitalexpressionbean.h"
#include "malesocket.h"
#include "defaultmaledigitalexpressionsocket.h"

/**
 * Base class for classes that tests DigitalAction
 */
// /*public*/  /*abstract*/ class AbstractDigitalExpressionTestBase extends AbstractBaseTestBase {

//    /*public*/  /*abstract*/ NamedBean* createNewBean(QString systemName) /*throws Exception*/;

    //@Test
    /*public*/  void AbstractDigitalExpressionTestBase::testBadSystemName() /*throws Exception*/ {
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
//    /*public*/  void testBundle() {
//        Assert::assertEquals("strings are equal", "Memory", Bundle.getMessage("Memory_Short"));
//        Assert::assertEquals("strings are equal", "Memory IM1 is null", Bundle.getMessage("Memory_Long_CompareNull", "IM1", Bundle.getMessage("MemoryOperation_IsNull")));
//        Assert::assertEquals("strings are equal", "Memory", Bundle.getMessage(Locale.CANADA, "Memory_Short"));
//        Assert::assertEquals("strings are equal", "Memory IM1 is null", Bundle.getMessage(Locale.CANADA, "Memory_Long_CompareNull", "IM1", Bundle.getMessage("MemoryOperation_IsNull")));
//    }

    //@Test
    /*public*/  void AbstractDigitalExpressionTestBase::testGetBeanType() {
        Assert::assertTrue("String matches", "Digital expression" ==(((DigitalExpressionBean*)_base->bself())->getBeanType()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractDigitalExpressionTestBase::testEnableAndEvaluate() /*throws Exception*/ {
        DigitalExpressionBean* _expression = (DigitalExpressionBean*)_baseMaleSocket;
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertTrue("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(false);
        Assert::assertFalse("male socket is disabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertFalse("evaluate() returns false", _expression->evaluate(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(true);
        Assert::assertTrue("male socket is enabled", _baseMaleSocket->isEnabled(), __FILE__, __LINE__);
        Assert::assertTrue("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractDigitalExpressionTestBase::testDebugConfig() /*throws Exception*/ {
        DigitalExpressionBean* _expression = (DigitalExpressionBean*)_baseMaleSocket;
        Assert::assertTrue("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
        DefaultMaleDigitalExpressionSocket::DigitalExpressionDebugConfig* debugConfig = new DefaultMaleDigitalExpressionSocket::DigitalExpressionDebugConfig();
        debugConfig->_forceResult = true;
        debugConfig->_result = false;
        _baseMaleSocket->setDebugConfig(debugConfig);
        Assert::assertFalse("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
        debugConfig->_result = true;
        Assert::assertTrue("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
        debugConfig->_result = false;
        Assert::assertFalse("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
        debugConfig->_forceResult = false;
        Assert::assertTrue("evaluate() returns true", _expression->evaluate(), __FILE__, __LINE__);
    }
