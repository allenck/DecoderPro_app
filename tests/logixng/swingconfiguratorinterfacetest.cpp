#include "swingconfiguratorinterfacetest.h"
#include "junitutil.h"
#include "jtextfield.h"
#include "swingconfiguratorinterface.h"
#include "assert1.h"
#include "jlabel.h"
#include "logixng_thread.h"

SwingConfiguratorInterfaceTest::SwingConfiguratorInterfaceTest(QObject *parent)
    : QObject{parent}
{

}
/**
 * Test SwingConfiguratorInterface
 *
 * @author Daniel Bergqvist (C) 2020
 */
///*public*/ class SwingConfiguratorInterfaceTest {

    //@Test
    /*public*/ void SwingConfiguratorInterfaceTest::testSwingTools() {
//        Assume.assumeFalse(GraphicsEnvironment.isHeadless());

        // This test tests that the components can be in a different order than
        // expected, since different languages may order words in a different way.

        // If turnout 'IT2' 'is' 'thrown' then check if sensor 'IS34' is 'active' now
        QString message = "If turnout {2} {1} {4} then check if sensor {0} is {3} now";
        JTextField* component2_Turnout = new JTextField();
        JTextField* component1_Is_IsNot = new JTextField();
        JTextField* component4_thrownClosed = new JTextField();
        JTextField* component0_sensor = new JTextField();
        JTextField* component3_activeInactive = new JTextField();

        QList<JComponent*> components = QList<JComponent*>{
            component0_sensor,
            component1_Is_IsNot,
            component2_Turnout,
            component3_activeInactive,
            component4_thrownClosed};

        QList<JComponent*> list = SwingConfiguratorInterface::parseMessage(message, components);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(0)->jself()), __FILE__, __LINE__);
        Assert::assertEquals("If turnout ", ((JLabel*)list.at(0)->jself())->text(), __FILE__, __LINE__);

        Assert::assertEquals(component2_Turnout, list.at(1)->jself(), __FILE__, __LINE__);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(2)->jself()), __FILE__, __LINE__);
        Assert::assertEquals(" ", ((JLabel*)list.at(2)->jself())->text(), __FILE__, __LINE__);

        Assert::assertEquals(component1_Is_IsNot, list.at(3)->jself(), __FILE__, __LINE__);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(4)->jself()), __FILE__, __LINE__);
        Assert::assertEquals(" ", ((JLabel*)list.at(4)->jself())->text(), __FILE__, __LINE__);

        Assert::assertEquals(component4_thrownClosed, list.at(5), __FILE__, __LINE__);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(6)->jself()), __FILE__, __LINE__);
        Assert::assertEquals(" then check if sensor ", ((JLabel*)list.at(6)->jself())->text(), __FILE__, __LINE__);

        Assert::assertEquals(component0_sensor, list.at(7), __FILE__, __LINE__);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(8)->jself()), __FILE__, __LINE__);
        Assert::assertEquals(" is ", ((JLabel*)list.at(8)->jself())->text(), __FILE__, __LINE__);

        Assert::assertEquals(component3_activeInactive, list.at(9)->jself(), __FILE__, __LINE__);

        Assert::assertTrue(qobject_cast<JLabel*>(list.at(10)->jself()), __FILE__, __LINE__);
        Assert::assertEquals(" now", ((JLabel)list.at(10)->jself()).text(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void SwingConfiguratorInterfaceTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();
    }

    //@After
    /*public*/ void SwingConfiguratorInterfaceTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }
