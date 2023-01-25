#include "defaultfemalestringexpressionsockettest.h"
#include "instancemanager.h"
#include "defaultstringexpressionmanager.h"
#include "assert1.h"
#include "junitutil.h"
#include "defaultfemalestringexpressionsocket.h"
#include "logixng_thread.h"
#include "defaultmemorymanager.h"
#include "defaultconditionalngscaffold.h"
#include "defaultstringexpressionmanager.h"
#include "defaultfemalestringexpressionsocket.h"

/**
 * Test DefaultFemaleStringExpressionSocket
 *
 * @author Daniel Bergqvist 2018
 */
///*public*/  class DefaultFemaleStringExpressionSocketTest extends FemaleSocketTestBase {


//    @Rule
//    /*public*/  final ExpectedException thrown = ExpectedException.none();

    //@Override
    /*protected*/  Manager/*<? extends NamedBean>*/* DefaultFemaleStringExpressionSocketTest::getManager() {
        return (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
    }

    //@Test
    /*public*/  void DefaultFemaleStringExpressionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "E1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleStringExpressionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "?s" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "?s E1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/  FemaleSocket* DefaultFemaleStringExpressionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleStringExpressionSocket(nullptr, new MyFemaleSocketListener03()
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
    /*protected*/  bool DefaultFemaleStringExpressionSocketTest::hasSocketBeenSetup() {
        return _expression->_hasBeenSetup;
    }

    //@Test
    /*public*/  void DefaultFemaleStringExpressionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test evaluate() when not connected
        Assert::assertEquals("strings are equals", "", ((DefaultFemaleStringExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        // Test evaluate() when connected
        _femaleSocket->_connect(maleSocket);
        _memory->setValue("");
        Assert::assertEquals("strings are equals", "", ((DefaultFemaleStringExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        _memory->setValue("Test");
        Assert::assertEquals("strings are equals", "Test", ((DefaultFemaleStringExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleStringExpressionSocketTest::testGetConnectableClasses() {
        QHash<Category, QList</*Class<? extends Base>*/QString>> map = QHash<Category, QList<QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList<QString>();
        classes.append("StringExpressionConstant");
        classes.append("StringExpressionMemory");
        map.insert(Category::ITEM, classes);

        classes = QList<QString>();
        classes.append("StringFormula");
        map.insert(Category::COMMON, classes);

        classes = QList<QString>();
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleStringExpressionSocketTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        flag = new AtomicBoolean();
        errorFlag = new AtomicBoolean();
        _memorySystemName = "IM1";
        _memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->provide(_memorySystemName);
        _expression = new MyStringExpressionMemory("IQSE321");
        _expression->setMemory(_memory);
        StringExpressionMemory* otherExpression = new StringExpressionMemory("IQSE322", "");
        manager = (DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager");
        maleSocket = ((DefaultStringExpressionManager*)manager->mself())->registerExpression(_expression);
        otherMaleSocket = ((DefaultStringExpressionManager*)manager->mself())->registerExpression(otherExpression);
        _femaleSocket = new DefaultFemaleStringExpressionSocket(_conditionalNG, new MyFemaleSocketListener04(this)
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
                                                                , "E1");
    }

    //@After
    /*public*/  void DefaultFemaleStringExpressionSocketTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



