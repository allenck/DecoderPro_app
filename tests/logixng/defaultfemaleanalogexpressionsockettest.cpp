#include "defaultfemaleanalogexpressionsockettest.h"
#include "logixng_thread.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultanalogexpressionmanager.h"
#include "instancemanager.h"
#include "defaultconditionalngscaffold.h"
#include "conditionalng.h"
#include "defaultmemorymanager.h"
#include "defaultanalogexpressionmanager.h"
#include "defaultanalogexpressionmanager.h"

/**
 * Test DefaultFemaleAnalogExpressionSocket
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/   class DefaultFemaleAnalogExpressionSocketTest extends FemaleSocketTestBase {



    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleAnalogExpressionSocketTest::getManager() {
        return (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
    }

    //@Test
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "E1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "?~" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "?~ E1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleAnalogExpressionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleAnalogExpressionSocket(nullptr, new MyFemaleSocketListener(this)
//        {
//            //@Override
//            /*public*/   void connected(FemaleSocket socket) {
//            }

//            //@Override
//            /*public*/   void disconnected(FemaleSocket socket) {
//            }
//        }
         , name);
    }

    //@Override
    /*protected*/ bool DefaultFemaleAnalogExpressionSocketTest::hasSocketBeenSetup() {
        return _expression->_hasBeenSetup;
    }

    //@Test
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::testSetValue() /*throws Exception*/ {
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test evaluate() when not connected
        Assert::assertTrue("values are equals", 0.0 == ((DefaultFemaleAnalogExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        // Test evaluate() when connected
        _femaleSocket->_connect(maleSocket);
        _memory->setValue(0.0);
        Assert::assertTrue("values are equals", 0.0 == ((DefaultFemaleAnalogExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        _memory->setValue(1.2);
        Assert::assertTrue("values are equals", 1.2 == ((DefaultFemaleAnalogExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::testGetConnectableClasses() {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = QHash<Category*, QList</*Class<? extends Base>*/QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList</*Class<? extends Base>*/QString>();
        classes.append("AnalogExpressionMemoryAnalogExpressionAnalogIO");
        classes.append("AnalogExpressionMemoryAnalogExpressionConstant");
        classes.append("AnalogExpressionMemoryAnalogExpressionMemory");
        classes.append("jmri.jmrit.logixng.expressions.TimeSinceMidnight");
        map.insert(Category::ITEM, classes);

        classes = QList</*Class<? extends Base>*/QString>();
        classes.append("jmri.jmrit.logixng.expressions.AnalogFormula");
        map.insert(Category::COMMON, classes);

        classes = QList</*Class<? extends Base>*/QString>();
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::setUp() {
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
        _expression = new MyAnalogExpressionMemory("IQAE321");
        _expression->setMemory(_memory);
        AnalogExpressionBean* otherExpression = new AnalogExpressionMemory("IQAE322", "");
        manager = (DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        maleSocket = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(_expression);
        otherMaleSocket = ((DefaultAnalogExpressionManager*)manager->mself())->registerExpression(otherExpression);
        _femaleSocket = new DefaultFemaleAnalogExpressionSocket(_conditionalNG, new My2FemaleSocketListener(this)
//        {
//            //@Override
//            /*public*/   void connected(FemaleSocket socket) {
//                flag.set(true);
//            }

//            //@Override
//            /*public*/   void disconnected(FemaleSocket socket) {
//                flag.set(true);
//            }
//        }
                                                                , "E1");
    }

    //@After
    /*public*/   void DefaultFemaleAnalogExpressionSocketTest::tearDown() {
//        JUnitAppender.clearBacklog();   // REMOVE THIS!!!!
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }



