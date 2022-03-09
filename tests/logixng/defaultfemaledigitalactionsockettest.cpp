#include "defaultfemaledigitalactionsockettest.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultfemaledigitalactionsocket.h"
#include "categorydisplay.h"
#include "defaultlogixngmanager.h"
#include "logixng_thread.h"
#include "defaultconditionalngmanager.h"

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultFemaleDigitalActionSocketTest extends FemaleSocketTestBase {


    //@Rule
    ///*public*/  final ExpectedException thrown = ExpectedException.none();

    //@Override
    /*protected*/  Manager/*<? extends NamedBean>*/* DefaultFemaleDigitalActionSocketTest::getManager() {
        return (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    }

    //@Test
//    /*public*/  void DefaultFemaleDigitalActionSocketTest::testBundleClass() {
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage("TestBundle", "aa", "bb", "cc"), __FILE__, __LINE__);
//        Assert::assertEquals("bundle is correct", "Generic", Bundle.getMessage(Locale.US, "SocketTypeGeneric"), __FILE__, __LINE__);
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage(Locale.US, "TestBundle", "aa", "bb", "cc"), __FILE__, __LINE__);
//    }

    //@Test
    /*public*/  void DefaultFemaleDigitalActionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "A1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalActionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "!" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "! A1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/  FemaleSocket* DefaultFemaleDigitalActionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleDigitalActionSocket(nullptr, new MyFemaleSocketListener01()
//        {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//            }
//        }
                                                    , name);
    }

    //@Override
    /*protected*/  bool DefaultFemaleDigitalActionSocketTest::hasSocketBeenSetup() {
        return _action->_hasBeenSetup;
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalActionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test execute() when not connected
        ((DefaultFemaleDigitalActionSocket*)_femaleSocket->bself())->execute();
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalActionSocketTest::testGetConnectableClasses() {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = QHash<Category*, QList</*Class<? extends Base>*/QString>>();

        QList<QString> classes = QList<QString>();
        classes.append("ActionAudio");
        classes.append("ActionBlock");
        classes.append("ActionClock");
        classes.append("ActionDispatcher");
        classes.append("ActionEntryExit");
        classes.append("ActionLight");
        classes.append("ActionLightIntensity");
        classes.append("ActionLocalVariable");
        classes.append("ActionMemory");
        classes.append("ActionOBlock");
        classes.append("ActionPower");
        classes.append("ActionReporter");
        classes.append("ActionScript");
        classes.append("ActionSensor");
        classes.append("ActionSignalHead");
        classes.append("ActionSignalMast");
        classes.append("ActionSound");
        classes.append("ActionThrottle");
        classes.append("ActionTurnout");
        classes.append("ActionTurnoutLock");
        classes.append("ActionWarrant");
        classes.append("EnableLogix");
        classes.append("TriggerRoute");
        map.insert(Category::ITEM, classes);

        classes = QList<QString>();
        classes.append("ActionTimer");
        classes.append("DoAnalogAction");
        classes.append("DoStringAction");
        classes.append("ExecuteDelayed");
        classes.append("For");
        classes.append("IfThenElse");
        classes.append("DigitalMany");
        classes.append("Sequence");
        classes.append("TableForEach");
        map.insert(Category::COMMON, classes);

        classes = QList<QString>();
        classes.append("ActionPositionable");
        map.insert(CategoryDisplay::DISPLAY, classes);

        classes = QList<QString>();
        classes.append("ActionListenOnBeans");
        classes.append("ActionListenOnBeansTable");
        classes.append("DigitalCallModule");
        classes.append("Logix");
        classes.append("LogData");
        classes.append("LogLocalVariables");
        classes.append("ShutdownComputer");
        classes.append("WebBrowser");
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleDigitalActionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        LogixNG* logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("A new logix for test");  // NOI18N

        ConditionalNG* conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        flag = new AtomicBoolean();
        errorFlag = new AtomicBoolean();
        _action = new MyActionTurnout("IQDA321");
        ActionTurnout* otherAction = new MyActionTurnout("IQDA322");
        manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        maleSocket = ((DefaultDigitalActionManager*)manager->mself())->registerAction(_action);
        otherMaleSocket = ((DefaultDigitalActionManager*)manager->mself())->registerAction(otherAction);
        _femaleSocket = new DefaultFemaleDigitalActionSocket(conditionalNG, new MyFemaleSocketListener02(this)
//         {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//                flag.set(true);
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//                flag.set(true);
//            }
//        }
                                                             , "A1");
    }

    //@After
    /*public*/  void DefaultFemaleDigitalActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::deregisterEditorManagerShutdownTask();
        JUnitUtil::tearDown();
    }




