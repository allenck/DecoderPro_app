#include "defaultfemalestringactionsockettest.h"
#include "logixng_thread.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "defaultstringactionmanager.h"
#include "defaultfemalestringactionsocket.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"
#include "defaultmemorymanager.h"

/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultFemaleStringActionSocketTest extends FemaleSocketTestBase {


//    @Rule
//    /*public*/  final ExpectedException thrown = ExpectedException.none();

    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleStringActionSocketTest::getManager() {
        return (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
    }

    //@Test
//    /*public*/  void testBundleClass() {
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage("TestBundle", "aa", "bb", "cc"));
//        Assert::assertEquals("bundle is correct", "Generic", Bundle.getMessage(Locale.US, "SocketTypeGeneric"));
//        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage(Locale.US, "TestBundle", "aa", "bb", "cc"));
//    }

    //@Test
    /*public*/  void DefaultFemaleStringActionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "A1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleStringActionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "!s" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "!s A1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleStringActionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleStringActionSocket(nullptr, new MyFemaleSocketListener09(this)
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
    /*protected*/ bool DefaultFemaleStringActionSocketTest::hasSocketBeenSetup() {
        return _action->_hasBeenSetup;
    }

    //@Test
    /*public*/  void DefaultFemaleStringActionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test setValue() when not connected
        ((DefaultFemaleStringActionSocket*)_femaleSocket->bself())->setValue("");
    }

    //@Test
    /*public*/  void DefaultFemaleStringActionSocketTest::testGetConnectableClasses() {
        QHash<Category, QList<QString>> map = QHash<Category, QList<QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList<QString>();
        classes.append("jmri.jmrit.logixng.actions.StringActionMemory");
        classes.append("jmri.jmrit.logixng.actions.StringActionStringIO");
        map.insert(Category::ITEM, classes);

        classes = QList<QString>();
        classes.append("jmri.jmrit.logixng.actions.StringMany");
        map.insert(Category::COMMON, classes);

        classes = QList<QString>();
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleStringActionSocketTest::setUp() {
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
                ->createConditionalNG(logixNG, "An empty conditionalNG");

        flag = new AtomicBoolean();
        errorFlag = new AtomicBoolean();
        _memorySystemName = "IM1";
        _memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide(_memorySystemName);
        _action = new MyStringActionMemory("IQSA321");
        _action->setMemory(_memory);
        StringActionMemory* otherAction = new StringActionMemory("IQSA322", "");
        manager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
        maleSocket = ((DefaultStringActionManager*)manager->mself())->registerAction(_action);
        otherMaleSocket = ((DefaultStringActionManager*)manager->mself())->registerAction(otherAction);
        _femaleSocket = new DefaultFemaleStringActionSocket(conditionalNG, new MyFemaleSocketListener10(this)
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
    /*public*/  void DefaultFemaleStringActionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



