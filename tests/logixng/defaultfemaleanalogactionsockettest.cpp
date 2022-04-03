#include "defaultfemaleanalogactionsockettest.h"
#include "defaultanalogactionmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "defaultfemaleanalogactionsocket.h"
#include "defaultconditionalngmanager.h"
#include "defaultmemorymanager.h"
#include "logixng_thread.h"
#include "defaultlogixngmanager.h"

DefaultFemaleAnalogActionSocketTest::DefaultFemaleAnalogActionSocketTest(QObject *parent)
{

}
#if 1
/**
 * Test ExpressionTimer
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultFemaleAnalogActionSocketTest extends FemaleSocketTestBase {


    //@Rule

    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleAnalogActionSocketTest::getManager() {
        return (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
    }
#if 0
    //@Test
    /*public*/  void DefaultFemaleAnalogActionSocketTest::testBundleClass() {
        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage("TestBundle", "aa", "bb", "cc"), __FILE__, __LINE__);
        Assert::assertEquals("bundle is correct", "Generic", Bundle.getMessage(Locale.US, "SocketTypeGeneric"), __FILE__, __LINE__);
        Assert::assertEquals("bundle is correct", "Test Bundle bb aa cc", Bundle.getMessage(Locale.US, "TestBundle", "aa", "bb", "cc"), __FILE__, __LINE__);
    }
#endif
    //@Test
    /*public*/  void DefaultFemaleAnalogActionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "A1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleAnalogActionSocketTest::testGetDescription() {
        Assert::assertEquals("String matches", "!~", _femaleSocket->getShortDescription(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "!~ A1", _femaleSocket->getLongDescription(), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleAnalogActionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleAnalogActionSocket(nullptr, new DFAAFemaleSocketListener()
//        {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//            }
//        }
       , name, this);
    }

    //@Override
    /*protected*/ bool DefaultFemaleAnalogActionSocketTest::hasSocketBeenSetup() {
        return _action->_hasBeenSetup;
    }

    //@Test
    /*public*/  void DefaultFemaleAnalogActionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test setValue() when not connected
        ((DefaultFemaleAnalogActionSocket*)_femaleSocket->bself())->setValue(0.0);
    }

    //@Test
    /*public*/  void DefaultFemaleAnalogActionSocketTest::testGetConnectableClasses() {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = QHash<Category*, QList</*Class<? extends Base>*/QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList</*Class<? extends Base>*/QString>();
        classes.append("AnalogActionLightIntensity");
        classes.append("AnalogActionMemory");
        map.insert(Category::ITEM, classes);

        classes = QList</*Class<? extends Base>*/QString>();
        classes.append("AnalogMany");
        map.insert(Category::COMMON, classes);

        classes = QList</*Class<? extends Base>*/QString>();
        map.insert(Category::OTHER, classes);

        QHash<Category*, QList<QString> > expected = _femaleSocket->getConnectableClasses();
        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }
/*
    @Test
    public  void DefaultFemaleAnalogActionSocketTest::testCategory() {
        // Test that the classes method getCategory() returns the same value as
        // the factory.
        QHash<Category*, QList<Class<? extends Base>QString>> map = femaleSocket.getConnectableClasses();

        for (Map.Entry<Category, List<Class<? extends Base>>> entry : map.entrySet()) {

            for (Class<? extends Base> clazz : entry.getValue()) {
                // The class SwingToolsTest does not have a swing configurator
                SwingConfiguratorInterface iface = SwingTools.getSwingConfiguratorForClass(clazz);
                iface.getConfigPanel();
                Base obj = iface.createNewObject(iface.getAutoSystemName(), null);
                Assert::assertEquals("category is correct", entry.getKey(), obj.getCategory());
            }
        }
    }
*/
    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleAnalogActionSocketTest::setUp() {
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
        _memorySystemName = "IM1";
        _memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide(_memorySystemName);
        _action = new MyAnalogActionMemory("IQAA321");
        _action->setMemory(_memory);
        AnalogActionBean* otherAction = new AnalogActionMemory("IQAA322", nullptr);
        manager = (DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager");
        maleSocket = ((DefaultAnalogActionManager*)manager->mself())->registerAction(_action);
        otherMaleSocket = ((DefaultAnalogActionManager*)manager->mself())->registerAction(otherAction);
        _femaleSocket = new DefaultFemaleAnalogActionSocket(conditionalNG, new DFAA2FemaleSocketListener(this)
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
      , "A1", this);
    }

    //@After
    /*public*/  void DefaultFemaleAnalogActionSocketTest::tearDown() {
       LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



//    /*private*/ class MyAnalogActionMemory extends AnalogActionMemory {

//        /*private*/ boolean _hasBeenSetup = false;

//        /*public*/  MyAnalogActionMemory(String systemName) {
//            super(systemName, null);
//        }

//        /** {@inheritDoc} */
//        //@Override
//        /*public*/  void setup() {
//            _hasBeenSetup = true;
//        }
//    }
#endif
