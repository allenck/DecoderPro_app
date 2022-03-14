#include "logixng_managertest.h"
#include "logixng_thread.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"

/**
 * Test LogixNG_Manager
 *
 * @author Daniel Bergqvist 2020
 */
///*public*/  class LogixNG_ManagerTest {

    /*private*/ void LogixNG_ManagerTest::testSystemNameFormat(QString prefix) {
        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+"123"), __FILE__, __LINE__);

        // This is not valid since the dollar sign is missing after the prefix
        Assert::assertEquals("Validation is not correct",
                Manager::NameValidity::INVALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+"Hello World"), __FILE__, __LINE__);

        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":AUTO:123"), __FILE__, __LINE__);

        // This is not valid since :AUTO: names must be digits only after :AUTO:
        Assert::assertEquals("Validation is not correct",
                Manager::NameValidity::INVALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":AUTO:Hello"), __FILE__, __LINE__);

        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+"$123"), __FILE__, __LINE__);

        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+"$Hello World"), __FILE__, __LINE__);

        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":JMRI:Signal Mast System"), __FILE__, __LINE__);

        // This is invalid since JMRI is misspelled
        Assert::assertEquals("Validation is not correct",
                Manager::NameValidity::INVALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":JRMI:Signal Mast System"), __FILE__, __LINE__);

        // Validation is correct
        Assert::assertEquals("Validation is correct",
                Manager::NameValidity::VALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":JMRI-LIB:Track Warrant System"), __FILE__, __LINE__);

        // This is invalid since JMRI is misspelled
        Assert::assertEquals("Validation is not correct",
                Manager::NameValidity::INVALID,
                LogixNG_Manager::ng_validSystemNameFormat(prefix, prefix+":JRMI-LIB:Signal Mast System"), __FILE__, __LINE__);
    }

    /*private*/ void LogixNG_ManagerTest::testValidSystemNameFormat(QString prefix) {
        testSystemNameFormat(prefix);         // LogixNG
        testSystemNameFormat(prefix+"C");     // ConditionalNG
        testSystemNameFormat(prefix+"AA");    // Analog Action
        testSystemNameFormat(prefix+"AE");    // Analog Expression
        testSystemNameFormat(prefix+"DA");    // Digital Action
        testSystemNameFormat(prefix+"DE");    // Digital Expression
        testSystemNameFormat(prefix+"SA");    // String Action
        testSystemNameFormat(prefix+"SE");    // String Expression
    }

    //@Test
    /*public*/  void LogixNG_ManagerTest::testValidSystemNameFormat() {
        LogixNG* logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("A new logix for test");  // NOI18N
        testValidSystemNameFormat("IQ");
        testValidSystemNameFormat("I2Q");
        testValidSystemNameFormat("PQ");
        testValidSystemNameFormat("P55Q");
        ConditionalNG* conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        Assert::assertEquals("beanType is correct", "ConditionalNG", conditionalNG->getBeanType(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void LogixNG_ManagerTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/  void LogixNG_ManagerTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
