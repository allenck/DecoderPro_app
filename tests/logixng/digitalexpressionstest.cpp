#include "digitalexpressionstest.h"
#include"abstractnamedbeanmanagerconfigxml.h"
#include "andxml.h"
#include "junitutil.h"
#include "assert1.h"
#include "junitappender.h"
#include "antecedentxml.h"
#include "logixng_thread.h"
#include "truexml.h"

/**
 * Test DigitalExpressions
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  class DigitalExpressionsTest {

    //@Test
    /*public*/  void DigitalExpressionsTest::testLoad() /*throws JmriConfigureXmlException*/ {
        AbstractNamedBeanManagerConfigXML* b;

        b = new AndXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b->load(QDomElement(), nullptr);
        JUnitAppender::assertMessage("Invalid method called", __FILE__, __LINE__);

        b = new AntecedentXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b->load(QDomElement(), nullptr);
        JUnitAppender::assertMessage("Invalid method called");
#if 0
        b = new ExpressionLightXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new ExpressionSensorXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new ExpressionTurnoutXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new FalseXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new HoldXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new OrXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b.load((Element) null, (Object) null);
        JUnitAppender::assertMessage("Invalid method called");

        b = new TriggerOnceXml();
        Assert::assertNotNull("exists", b);
        b.load((Element) null, (Object) null, __FILE__, __LINE__);
        JUnitAppender::assertMessage("Invalid method called");
#endif
        b = new TrueXml();
        Assert::assertNotNull("exists", b, __FILE__, __LINE__);
        b->load(QDomElement(), nullptr);
        JUnitAppender::assertMessage("Invalid method called", __FILE__, __LINE__);

    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DigitalExpressionsTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void DigitalExpressionsTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
