#include "defaultfemaledigitalexpressionsockettest.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultfemaledigitalexpressionsocket.h"
#include "logixng_thread.h"
#include "conditionalng.h"
#include "defaultconditionalngscaffold.h"

/**
 * Test DefaultFemaleDigitalExpressionSocket
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultFemaleDigitalExpressionSocketTest extends FemaleSocketTestBase {


//    @Rule
//    /*public*/  final ExpectedException thrown = ExpectedException.none();

    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleDigitalExpressionSocketTest::getManager() {
        return (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    }

    ////@Test
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::testGetName() {
        Assert::assertTrue("String matches", "E1" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    ////@Test
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::testGetDescription() {
        Assert::assertTrue("String matches", "?" == (_femaleSocket->getShortDescription()), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "? E1" == (_femaleSocket->getLongDescription()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleDigitalExpressionSocketTest::getFemaleSocket(QString name) {
        return new DefaultFemaleDigitalExpressionSocket(nullptr, new MyFemaleSocketListener05()
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
    /*protected*/ bool DefaultFemaleDigitalExpressionSocketTest::hasSocketBeenSetup() {
        return _expression->_hasBeenSetup;
    }

    ////@Test
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::testSetValue() /*throws Exception */{
        // Every test method should have an assertion
        Assert::assertNotNull("femaleSocket is not null", _femaleSocket->bself(), __FILE__, __LINE__);
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        // Test evaluate() when not connected
        Assert::assertFalse("result is false", ((DefaultFemaleDigitalExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        // Test evaluate() when connected
        _femaleSocket->_connect(maleSocket);
        if (! _conditionalNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        Turnout* t = ((ProxyTurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
        _expression->setTurnout(t);
        _expression->setBeanState(ExpressionTurnout::TurnoutState::Thrown);
        t->setState(Turnout::CLOSED);
        Assert::assertFalse("turnout is not thrown", ((DefaultFemaleDigitalExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
        t->setState(Turnout::THROWN);
        Assert::assertTrue("turnout is thrown", ((DefaultFemaleDigitalExpressionSocket*)_femaleSocket->bself())->evaluate(), __FILE__, __LINE__);
    }

    ////@Test
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::testGetConnectableClasses() {
        QHash<Category, QList</*Class<? extends Base>*/QString>> map = QHash<Category, QList</*Class<? extends Base>*/QString>>();

        QList</*Class<? extends Base>*/QString> classes = QList</*Class<? extends Base>*/QString>();
        classes.append("jmri.jmrit.logixng.expressions.ExpressionBlock");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionClock");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionConditional");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionDispatcher");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionEntryExit");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionLight");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionLocalVariable");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionMemory");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionOBlock");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionPower");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionReference");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionReporter");
#ifdef SCRIPTING_ENABLED
        classes.append("jmri.jmrit.logixng.expressions.ExpressionScript");
#endif
        classes.append("jmri.jmrit.logixng.expressions.ExpressionSensor");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionSignalHead");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionSignalMast");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionTurnout");
        classes.append("jmri.jmrit.logixng.expressions.ExpressionWarrant");
        map.insert(Category::ITEM, classes);

        classes = QList<QString>();
        classes.append("jmri.jmrit.logixng.expressions.And");
        classes.append("jmri.jmrit.logixng.expressions.Antecedent");
        classes.append("jmri.jmrit.logixng.expressions.DigitalFormula");
        classes.append("jmri.jmrit.logixng.expressions.Not");
        classes.append("jmri.jmrit.logixng.expressions.Or");
        map.insert(Category::COMMON, classes);

        classes = QList<QString>();
        classes.append("jmri.jmrit.logixng.expressions.DigitalCallModule");
        classes.append("jmri.jmrit.logixng.expressions.False");
        classes.append("jmri.jmrit.logixng.expressions.Hold");
        classes.append("jmri.jmrit.logixng.expressions.LastResultOfDigitalExpression");
        classes.append("jmri.jmrit.logixng.expressions.LogData");
        classes.append("jmri.jmrit.logixng.expressions.TriggerOnce");
        classes.append("jmri.jmrit.logixng.expressions.True");
        map.insert(Category::OTHER, classes);

        Assert::assertTrue("maps are equal",
                isConnectionClassesEquals(map, _femaleSocket->getConnectableClasses()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::setUp() {
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
        _expression = new MyExpressionTurnout("IQDE321");
        ExpressionTurnout* otherExpression = new ExpressionTurnout("IQDE322", nullptr);
        manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        maleSocket = ((DefaultDigitalExpressionManager*)manager->mself())->registerExpression(_expression);
        otherMaleSocket = ((DefaultDigitalExpressionManager*)manager->mself())->registerExpression(otherExpression);
        _femaleSocket = new DefaultFemaleDigitalExpressionSocket(_conditionalNG, new MyFemaleSocketListener06(this)
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
    /*public*/  void DefaultFemaleDigitalExpressionSocketTest::tearDown() {
//        JUnitAppender.clearBacklog();   // REMOVE THIS!!!
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::tearDown();
    }



