#include "defaultfemalegenericexpressionsocket1_test.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "logixng_thread.h"
#include "runtimeexception.h"
#include "femalegenericexpressionsocket.h"
#include "defaultfemalegenericexpressionsocket.h"
#include "expressionmemory.h"
#include "defaultdigitalexpressionmanager.h"
#include "analogexpressionconstant.h"
#include "defaultanalogexpressionmanager.h"
#include "stringexpressionconstant.h"
#include "defaultstringexpressionmanager.h"
#include "analogexpressionmemory.h"
#include "stringexpressionmemory.h"
#include "defaultlogixngmanager.h"
#include "defaultconditionalngmanager.h"

/**
 * Test DefaultFemaleGenericExpressionSocket
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class DefaultFemaleGenericExpressionSocket1_Test extends FemaleSocketTestBase {


    //@Override
    /*protected*/ Manager/*<? extends NamedBean>*/* DefaultFemaleGenericExpressionSocket1_Test::getManager() {
        return nullptr;
    }

    //@Test
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testSWISystemName() {
        // Different types of beans may be able to connect to a generic socket, which makes this test impossible
    }

    //@Test
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testSetParentForAllChildren() /*throws SocketAlreadyConnectedException */{
        // This female socket has child female sockets, which requires special treatment
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        if (! _femaleSocket->setParentForAllChildren(QList<QString>())) throw new RuntimeException();
        Assert::assertNull("malesocket->getParent() is null", (QObject*)maleSocket->getParent(), __FILE__, __LINE__);
        _femaleSocket->_connect(maleSocket);
        if (! _femaleSocket->setParentForAllChildren(QList<QString>())) throw new RuntimeException();
        Assert::assertEquals("malesocket->getParent() is femaleSocket",
                _femaleGenericSocket,
                maleSocket->getParent(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testSocketType() {
        Assert::assertEquals("strings are equal",
                tr("Digital"),
                FemaleGenericExpressionSocket::toString(FemaleGenericExpressionSocket::DIGITAL), __FILE__, __LINE__);
        Assert::assertEquals("strings are equal",
                tr("Analog"),
                FemaleGenericExpressionSocket::toString(FemaleGenericExpressionSocket::ANALOG), __FILE__, __LINE__);
        Assert::assertEquals("strings are equal",
                tr("String"),
                FemaleGenericExpressionSocket::toString(FemaleGenericExpressionSocket::STRING), __FILE__, __LINE__);
        Assert::assertEquals("strings are equal",
                tr("Generic"),
                FemaleGenericExpressionSocket::toString(FemaleGenericExpressionSocket::GENERIC), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testGetName() {
        Assert::assertTrue("String matches", "E" == (_femaleSocket->getName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testGetDescription() {
        Assert::assertEquals("String matches", "?*", _femaleSocket->getShortDescription(), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "?* E", _femaleSocket->getLongDescription(), __FILE__, __LINE__);


        DefaultFemaleGenericExpressionSocket* socket;

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::DIGITAL, _conditionalNG, _listener, "E");
        Assert::assertEquals("String matches", "?*", socket->getShortDescription(QLocale()), __FILE__, __LINE__);
        Assert::assertEquals("String matches", "?* E", socket->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Override
    /*protected*/ FemaleSocket* DefaultFemaleGenericExpressionSocket1_Test::getFemaleSocket(QString name) {
        return new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, new MyFemaleSocketListener()
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
    /*protected*/ bool DefaultFemaleGenericExpressionSocket1_Test::hasSocketBeenSetup() {
        return _expression->_hasBeenSetup;
    }

    // DefaultFemaleGenericExpressionSocket is a virtual female socket that
    // is not used directly, but has inner /*private*/ classes that implements the
    // female sockets. See the classes AnalogSocket, DigitalSocket and StringSocket.
    //@Test
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testConnect() {
        try {
            _femaleSocket->_connect(maleSocket);

            // Try to connect twice. This should fail.
            bool hasThrown = false;
            try {
                _femaleSocket->_connect(maleSocket);
            } catch (SocketAlreadyConnectedException* e2) {
                hasThrown = true;
                Assert::assertEquals("Socket is already connected", e2->getMessage(), __FILE__, __LINE__);
            }
            Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
        } catch (SocketAlreadyConnectedException* e) {
            throw new RuntimeException(e);
        }
    }

    // DefaultFemaleGenericExpressionSocket is a virtual female socket that
    // is not used directly, but has inner /*private*/ classes that implements the
    // female sockets. See the classes AnalogSocket, DigitalSocket and StringSocket.
    //@Test
    //@Override
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testDisconnect() /*throws SocketAlreadyConnectedException */{
        // Test female generic socket
        ExpressionMemory* digitalExpression = new ExpressionMemory("IQDE351", "");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        DefaultFemaleGenericExpressionSocket* femaleSocket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, _listener, "E");

        Assert::assertNull("_currentActiveSocket is null",
               (QObject*) femaleSocket->getCurrentActiveSocket(), __FILE__, __LINE__);

        // Test disconnect() without connected socket
        femaleSocket->_disconnect();

        Assert::assertNull("_currentActiveSocket is null",
                (QObject*)femaleSocket->getCurrentActiveSocket(), __FILE__, __LINE__);

        // Test disconnect() without connected socket
        femaleSocket->_connect(digitalMaleSocket);

        Assert::assertEquals("_currentActiveSocket is has correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket",
                femaleSocket->getCurrentActiveSocket()->getClassName(), __FILE__, __LINE__);

        femaleSocket->_disconnect();


        // Test female digital socket
        femaleSocket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::DIGITAL, _conditionalNG, _listener, "E");

        // When the SocketType is not GENERIC, _currentActiveSocket is assigned to a socket
        Assert::assertNotNull("_currentActiveSocket is not null",
                femaleSocket->getCurrentActiveSocket()->bself(), __FILE__, __LINE__);

        // Test disconnect() without connected socket
        femaleSocket->_disconnect();

        // When the SocketType is not GENERIC, _currentActiveSocket is assigned to a socket
        Assert::assertNotNull("_currentActiveSocket is not null",
                femaleSocket->getCurrentActiveSocket()->bself(), __FILE__, __LINE__);

        // Test disconnect() without connected socket
        femaleSocket->_connect(digitalMaleSocket);

        Assert::assertEquals("_currentActiveSocket is has correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket",
                femaleSocket->getCurrentActiveSocket()->getClassName(), __FILE__, __LINE__);

        femaleSocket->_disconnect();
    }

    /*private*/ void DefaultFemaleGenericExpressionSocket1_Test::checkConnectableClasses(FemaleSocket* femaleSocket) {
        QHash<Category*, QList</*Class<? extends Base>*/QString>> classes = femaleSocket->getConnectableClasses();
        //Assert::assertNotNull("classes is not null", classes, __FILE__, __LINE__);
        Assert::assertTrue("classes is not null", !classes.isEmpty(), __FILE__, __LINE__);
        Assert::assertFalse("classes is not empty", classes.isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testConnectableClasses() /*throws SocketAlreadyConnectedException*/ {
        MyExpressionTurnout* digitalExpression = new MyExpressionTurnout("IQDE351");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        DefaultFemaleGenericExpressionSocket* socket;

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::DIGITAL, _conditionalNG, _listener, "E");
        socket->_connect(digitalMaleSocket);
        checkConnectableClasses(socket);
        socket->disconnect();
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testIsCompatibleSocket() {
        AnalogExpressionConstant* analogExpression = new AnalogExpressionConstant("IQAE351", "");
        MaleSocket* analogMaleSocket = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(analogExpression);

        // Test female generic socket
        ExpressionMemory* digitalExpression = new ExpressionMemory("IQDE351", "");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        StringExpressionConstant* stringExpression = new StringExpressionConstant("IQSE351", "");
        MaleSocket* stringMaleSocket = ((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))->registerExpression(stringExpression);

        DefaultFemaleGenericExpressionSocket* femaleSocket;

        femaleSocket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::DIGITAL, _conditionalNG, _listener, "E");
        Assert::assertTrue("Socket is compatible",
                femaleSocket->isCompatible(analogMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Socket is compatible",
                femaleSocket->isCompatible(digitalMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Socket is compatible",
                femaleSocket->isCompatible(stringMaleSocket), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testGetAndSetSocketType() /*throws SocketAlreadyConnectedException*/ {
        bool exceptionThrown;

        AnalogExpressionMemory* analogExpression = new AnalogExpressionMemory("IQAE351", "");
        MaleSocket* analogMaleSocket = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(analogExpression);

        ExpressionMemory* digitalExpression = new ExpressionMemory("IQDE351", "");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        StringExpressionMemory* stringExpression = new StringExpressionMemory("IQSE351", "");
        MaleSocket* stringMaleSocket = ((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))->registerExpression(stringExpression);

        // This should work
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::ANALOG);
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::ANALOG);   // Test calling setSocketType() twice
        Assert::assertEquals("Socket type is correct", FemaleGenericExpressionSocket::SocketType::ANALOG, _femaleGenericSocket->getSocketType(), __FILE__, __LINE__);
        Assert::assertEquals("Active socket is correct", "jmri.jmrit.logixng.implementation.DefaultFemaleAnalogExpressionSocket", _femaleGenericSocket->getCurrentActiveSocket()->getClassName(), __FILE__, __LINE__);

        // We can't change socket type if it's connected
        _femaleGenericSocket->_connect(analogMaleSocket);
        exceptionThrown = false;
        try {
            _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::DIGITAL);
        } catch (SocketAlreadyConnectedException e) {
            exceptionThrown = true;
            Assert::assertEquals("Error message is correct", "Socket is already connected", e.getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", exceptionThrown, __FILE__, __LINE__);
        _femaleGenericSocket->_disconnect();


        // This should work
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::DIGITAL);
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::DIGITAL);   // Test calling setSocketType() twice
        Assert::assertEquals("Socket type is correct", FemaleGenericExpressionSocket::SocketType::DIGITAL, _femaleGenericSocket->getSocketType(), __FILE__, __LINE__);
        Assert::assertEquals("Active socket is correct", "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalExpressionSocket", _femaleGenericSocket->getCurrentActiveSocket()->getClassName(), __FILE__, __LINE__);

        // We can't change socket type if it's connected
        _femaleGenericSocket->_connect(digitalMaleSocket);
        exceptionThrown = false;
        try {
            _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::GENERIC);
        } catch (SocketAlreadyConnectedException* e) {
            exceptionThrown = true;
            Assert::assertEquals("Error message is correct", "Socket is already connected", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", exceptionThrown, __FILE__, __LINE__);
        _femaleGenericSocket->_disconnect();


        // This should work
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::GENERIC);
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::GENERIC);   // Test calling setSocketType() twice
        Assert::assertEquals("Socket type is correct", FemaleGenericExpressionSocket::SocketType::GENERIC, _femaleGenericSocket->getSocketType(), __FILE__, __LINE__);
        Assert::assertNull("Active socket is null", _femaleGenericSocket->getCurrentActiveSocket()->bself(), __FILE__, __LINE__);

        // We can't change socket type if it's connected
        _femaleGenericSocket->_connect(stringMaleSocket);
        exceptionThrown = false;
        try {
            _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::STRING);
        } catch (SocketAlreadyConnectedException* e) {
            exceptionThrown = true;
            Assert::assertEquals("Error message is correct", "Socket is already connected", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", exceptionThrown, __FILE__, __LINE__);
        _femaleGenericSocket->_disconnect();


        // This should work
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::STRING);
        _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::STRING);   // Test calling setSocketType() twice
        Assert::assertEquals("Socket type is correct", FemaleGenericExpressionSocket::SocketType::STRING, _femaleGenericSocket->getSocketType(), __FILE__, __LINE__);
        Assert::assertEquals("Active socket is correct", "jmri.jmrit.logixng.implementation.DefaultFemaleStringExpressionSocket", _femaleGenericSocket->getCurrentActiveSocket()->getClassName(), __FILE__, __LINE__);

        // We can't change socket type if it's connected
        _femaleGenericSocket->_connect(stringMaleSocket);
        exceptionThrown = false;
        try {
            _femaleGenericSocket->setSocketType(FemaleGenericExpressionSocket::SocketType::DIGITAL);
        } catch (SocketAlreadyConnectedException* e) {
            exceptionThrown = true;
            Assert::assertEquals("Error message is correct", "Socket is already connected", e->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception thrown", exceptionThrown, __FILE__, __LINE__);
        _femaleGenericSocket->_disconnect();
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testIsCompatible() {
        AnalogExpressionMemory* analogExpression = new AnalogExpressionMemory("IQAE351", "");
        MaleSocket* analogMaleSocket = ((DefaultAnalogExpressionManager*)
                InstanceManager::getDefault("AnalogExpressionManager"))->registerExpression(analogExpression);

        ExpressionMemory* digitalExpression = new ExpressionMemory("IQDE351", "");
        MaleSocket* digitalMaleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(digitalExpression);

        StringExpressionMemory* stringExpression = new StringExpressionMemory("IQSE351", "");
        MaleSocket* stringMaleSocket = ((DefaultStringExpressionManager*)
                InstanceManager::getDefault("StringExpressionManager"))->registerExpression(stringExpression);

        DefaultFemaleGenericExpressionSocket* socket;

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::ANALOG, _conditionalNG, _listener, "E");
        Assert::assertTrue("Analog male socket is compatible", socket->isCompatible(analogMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Digital male socket is compatible", socket->isCompatible(digitalMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("String male socket is compatible", socket->isCompatible(stringMaleSocket), __FILE__, __LINE__);

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::DIGITAL, _conditionalNG, _listener, "E");
        Assert::assertTrue("Analog male socket is compatible", socket->isCompatible(analogMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Digital male socket is compatible", socket->isCompatible(digitalMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("String male socket is compatible", socket->isCompatible(stringMaleSocket), __FILE__, __LINE__);

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, _listener, "E");
        Assert::assertTrue("Analog male socket is compatible", socket->isCompatible(analogMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Digital male socket is compatible", socket->isCompatible(digitalMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("String male socket is compatible", socket->isCompatible(stringMaleSocket), __FILE__, __LINE__);

        socket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::STRING, _conditionalNG, _listener, "E");
        Assert::assertTrue("Analog male socket is compatible", socket->isCompatible(analogMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("Digital male socket is compatible", socket->isCompatible(digitalMaleSocket), __FILE__, __LINE__);
        Assert::assertTrue("String male socket is compatible", socket->isCompatible(stringMaleSocket), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::testDoI18N() {
        DefaultFemaleGenericExpressionSocket* socket =
                new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::ANALOG, _conditionalNG, _listener, "E");
        Assert::assertFalse("do_i18n is false", socket->getDoI18N(), __FILE__, __LINE__);
        socket->setDoI18N(true);
        Assert::assertTrue("do_i18n is true", socket->getDoI18N(), __FILE__, __LINE__);
        socket->setDoI18N(false);
        Assert::assertFalse("do_i18n is false", socket->getDoI18N(), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _listener = new MyFemaleSocketListener();
//        {
//            //@Override
//            /*public*/  void connected(FemaleSocket socket) {
//                // Do nothing
//            }

//            //@Override
//            /*public*/  void disconnected(FemaleSocket socket) {
//                // Do nothing
//            }
//        };

        LogixNG* logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                ->createLogixNG("A new logix for test");  // NOI18N

        _conditionalNG = ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))
                ->createConditionalNG(logixNG, "A conditionalNG");  // NOI18N
        flag = new AtomicBoolean();
        errorFlag = new AtomicBoolean();
        _expression = new MyExpressionTurnout("IQDE321");
        ExpressionTurnout* otherExpression = new ExpressionTurnout("IQDE322", "");
        maleSocket = ((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(_expression);
        otherMaleSocket =((DefaultDigitalExpressionManager*)
                          InstanceManager::getDefault("DigitalExpressionManager"))->registerExpression(otherExpression);
        _femaleGenericSocket = new DefaultFemaleGenericExpressionSocket(FemaleGenericExpressionSocket::SocketType::GENERIC, _conditionalNG, new MyFemaleSocketListener02(this)
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
                                                                        , "E");
        _femaleSocket = _femaleGenericSocket;
    }

    //@After
    /*public*/  void DefaultFemaleGenericExpressionSocket1_Test::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::deregisterBlockManagerShutdownTask();
        JUnitUtil::tearDown();
    }



