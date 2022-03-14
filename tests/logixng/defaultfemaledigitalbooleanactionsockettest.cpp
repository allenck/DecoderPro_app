#include "defaultfemaledigitalbooleanactionsockettest.h"
#include "instancemanager.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultlogixngmanager.h"
#include "defaultfemaledigitalbooleanactionsocket.h"
#include "conditionalng.h"
#include "defaultconditionalngmanager.h"
#include "logixng_thread.h"

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultFemaleDigitalBooleanActionSocketTest extends FemaleSocketTestBase {


//    @Rule
//    /*public*/  final ExpectedException thrown = ExpectedException.none();

    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleDigitalBooleanActionSocketTest::getManager() {
        return (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
    }

    //@Test
//    /*public*/  void testBundleClass() {
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage("TestBundle", "aa", "bb", "cc"));
//        Assert::assertEquals("bundle is correct", "Generic", Bundle.getMessage(Locale.US, "SocketTypeGeneric"));
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage(Locale.US, "TestBundle", "aa", "bb", "cc"));
//    }

    //@Test
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "A1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "!b" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "!b A1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleDigitalBooleanActionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleDigitalBooleanActionSocket(nullptr, new MyFemaleSocketListener07(this)
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
    /*protected*/ bool DefaultFemaleDigitalBooleanActionSocketTest::hasSocketBeenSetup() {
        return _action->_hasBeenSetup;
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test execute() when not connected
        ((DefaultFemaleDigitalBooleanActionSocket*)_femaleSocket->bself())->execute(false, false);
    }

    //@Test
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::testGetConnectableClasses() {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = QHash<Category*, QList<QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList<QString>();
//        classes.add(jmri.jmrit.logixng.actions.ActionLight.class);
        map.insert(Category::ITEM, classes);

        classes = QList<QString>();
        classes.append("jmri.jmrit.logixng.actions.DigitalBooleanMany");
        classes.append("jmri.jmrit.logixng.actions.DigitalBooleanOnChange");
        map.insert(Category::COMMON, classes);

        classes = QList<QString>();
//        classes.add(jmri.jmrit.logixng.actions.ShutdownComputer.class);
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::setUp() {
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
        _action = new MyOnChangeAction("IQDB321");
        DigitalBooleanOnChange* otherAction = new MyOnChangeAction("IQDB322");
        manager = (DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager");
        maleSocket = ((DefaultDigitalBooleanActionManager*)manager->mself())->registerAction(_action);
        otherMaleSocket = ((DefaultDigitalBooleanActionManager*)manager->mself())->registerAction(otherAction);
        _femaleSocket = new DefaultFemaleDigitalBooleanActionSocket(conditionalNG, new MyFemaleSocketListener08(this)
//        {
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
    /*public*/  void DefaultFemaleDigitalBooleanActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



