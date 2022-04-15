#include "stringmanytest.h"
#include "stringmany.h"
#include "instancemanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "defaultstringactionmanager.h"
#include "defaultlogixngmanager.h"
#include "logixng_thread.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "defaultconditionalng.h"
#include "dostringaction.h"
#include "defaultdigitalactionmanager.h"
#include "junitappender.h"
#include "stringactionmemory.h"


StringManyTest::StringManyTest(QObject *parent) : AbstractStringActionTestBase(parent)
{
 setObjectName("StringManyTest");
}

/**
 * Test Many
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  class StringManyTest extends AbstractStringActionTestBase {


    //@Override
    /*public*/  ConditionalNG* StringManyTest::getConditionalNG() {
        return conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* StringManyTest::getLogixNG() {
        return logixNG;
    }

    //@Override
    /*public*/  MaleSocket* StringManyTest::getConnectableChild() {
        StringMany* action = new StringMany("IQSA999", "");
        MaleSocket* maleSocket = ((DefaultStringActionManager*)
                InstanceManager::getDefault("StringActionManager"))->registerAction(action);
        return maleSocket;
    }

    //@Override
    /*public*/  QString StringManyTest::getExpectedPrintedTree() {
        return QString(
                "Many ::: Use default\n" \
                "   !s A1\n" \
                "      Socket not connected\n");
    }

    //@Override
    /*public*/  QString StringManyTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Read string E and set string A ::: Use default\n" \
                "            ?s E\n" \
                "               Socket not connected\n" \
                "            !s A\n" \
                "               Many ::: Use default\n" \
                "                  !s A1\n" \
                "                     Socket not connected\n");
    }

    //@Override
    /*public*/  NamedBean* StringManyTest::createNewBean(QString systemName) {
        return new StringMany(systemName, "");
    }

    //@Override
    /*public*/  bool StringManyTest::addNewSocket() /*throws SocketAlreadyConnectedException */{
        int count = _base->getChildCount();
        for (int i=0; i < count; i++) {
            if (!_base->getChild(i)->isConnected()) {
                _base->getChild(i)->_connect(getConnectableChild());
            }
        }
        return true;
    }

    //@Test
    /*public*/  void StringManyTest::testCtor() {
        StringMany* action = new StringMany("IQSA321", "");
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has one female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket name is A1", "A1", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleStringActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
    }

    // Test action when at least one child socket is not connected
    //@Test
    /*public*/  void StringManyTest::testCtorAndSetup1() {
        StringActionManager* m = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");

        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA52", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA554", "")));
        maleSockets.append(nullptr);  // This is null by purpose
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA3", "")));

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQSA52"}});
        actionSystemNames.append(QMap<QString, QString> {{"ZH12", ""}});   // This is null by purpose
        actionSystemNames.append(QMap<QString, QString> {{"Hello", "IQSA554"}});
        // IQSA61232 doesn't exist by purpose
        actionSystemNames.append(QMap<QString, QString> {{"SomethingElse", "IQSA61232"}});
        actionSystemNames.append(QMap<QString, QString> {{"Yes123", "IQSA3"}});

        StringMany* action = new StringMany("IQSA321", "", actionSystemNames);
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 5 female sockets", 5, action->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
            QMap<QString,QString> map = actionSystemNames.at(i);
            QMapIterator<QString,QString> entry(map);
            while(entry.hasNext())
            {
            entry.next();
            Assert::assertEquals("action female socket name is "+entry.key(),
                    entry.key(), action->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("action female socket is of correct class",
                    "jmri.jmrit.logixng.implementation.DefaultFemaleStringActionSocket",
                    action->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("action female socket is not connected",
                    action->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
        }

        // Setup action-> This connects the child actions to this action
        action->setup();

        JUnitAppender::assertMessage("cannot load string action IQSA61232", __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
         QMap<QString,QString> map = actionSystemNames.at(i);
         QMapIterator<QString,QString> entry(map);
         while(entry.hasNext())
         {
         entry.next();

            Assert::assertEquals("action female socket name is "+entry.key(),
                    entry.key(), action->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("action female socket is connected",
                        action->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        action->getChild(i).getConnectedSocket(), __FILE__, __LINE__);
            } else {
                Assert::assertFalse("action female socket is not connected",
                        action->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
         }
        }

        Assert::assertEquals("action has 5 female sockets", 5, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void StringManyTest::testCtorAndSetup2() {
     StringActionManager* m = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");


        QList<MaleSocket*> maleSockets = QList<MaleSocket*>();
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA52", "")));
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA99", "")));
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA554", "")));
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA61232", "")));
        maleSockets.append(m->registerAction(new StringActionMemory("IQSA3", "")));

        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();
        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQSA52"}});
        actionSystemNames.append(QMap<QString, QString> {{"ZH12", "IQSA99"}});
        actionSystemNames.append(QMap<QString, QString> {{"Hello", "IQSA554"}});
        actionSystemNames.append(QMap<QString, QString> {{"SomethingElse", "IQSA61232"}});
        actionSystemNames.append(QMap<QString, QString> {{"Yes123", "IQSA3"}});

        StringMany* action = new StringMany("IQSA321", "", actionSystemNames);
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 5 female sockets", 5, action->getChildCount(), __FILE__, __LINE__);

        for (int i=0; i < 5; i++) {
         QMap<QString,QString> map = actionSystemNames.at(i);
         QMapIterator<QString,QString> entry(map);
         while(entry.hasNext())
         {
         entry.next();

            Assert::assertEquals("action female socket name is "+entry.key(),
                    entry.key(), action->getChild(i)->getName(), __FILE__, __LINE__);
            Assert::assertEquals("action female socket is of correct class",
                    "jmri.jmrit.logixng.implementation.DefaultFemaleStringActionSocket",
                    action->getChild(i)->getClassName(), __FILE__, __LINE__);
            Assert::assertFalse("action female socket is not connected",
                    action->getChild(i)->isConnected(), __FILE__, __LINE__);
         }
        }

        // Setup action-> This connects the child actions to this action
        action->setup();

        for (int i=0; i < 5; i++) {
         QMap<QString,QString> map = actionSystemNames.at(i);
         QMapIterator<QString,QString> entry(map);
         while(entry.hasNext())
         {
         entry.next();

            Assert::assertEquals("action female socket name is "+entry.key(),
                    entry.key(), action->getChild(i)->getName(), __FILE__, __LINE__);

            if (maleSockets.at(i) != nullptr) {
                Assert::assertTrue("action female socket is connected",
                        action->getChild(i)->isConnected(), __FILE__, __LINE__);
//                Assert::assertEquals("child is correct bean",
//                        maleSockets.get(i),
//                        action->getChild(i).getConnectedSocket(), __FILE__, __LINE__);
            } else {
                Assert::assertFalse("action female socket is not connected",
                        action->getChild(i)->isConnected(), __FILE__, __LINE__);
            }
         }
        }

        Assert::assertEquals("action has 6 female sockets", 6, action->getChildCount(), __FILE__, __LINE__);

        // Try run setup() again. That should not cause any problems.
        action->setup();

        Assert::assertEquals("action has 6 female sockets", 6, action->getChildCount(), __FILE__, __LINE__);
    }

    // Test calling setActionSystemNames() twice
    //@Test
    /*public*/  void StringManyTest::testCtorAndSetup3() /*throws NoSuchMethodException, IllegalAccessException, IllegalArgumentException */{
        QList<QMap<QString, QString>> actionSystemNames = QList<QMap<QString, QString>>();

        actionSystemNames.append(QMap<QString, QString> {{"XYZ123", "IQSA52"}});

        StringMany* action = new StringMany("IQSA321", "", actionSystemNames);
#if 0
        java.lang.reflect.Method method =
                action->getClass().getDeclaredMethod("setActionSystemNames", new Class<?>[]{List.class});
        method.setAccessible(true);

        bool hasThrown = false;
        try {
            method.invoke(action, new Object[]{null});
        } catch (InvocationTargetException* e) {
            if (e.getCause() instanceof RuntimeException) {
                hasThrown = true;
                Assert::assertEquals("Exception message is correct",
                        "action system names cannot be set more than once",
                        e.getCause().getMessage());
            }
        }
        Assert::assertTrue("Exception thrown", hasThrown, __FILE__, __LINE__);
#endif

    }

    //@Test
    /*public*/  void StringManyTest::testGetChild() /*throws SocketAlreadyConnectedException*/ {
        StringMany* action2 = new StringMany("IQSA321", "");

        for (int i=0; i < 3; i++) {
            Assert::assertTrue("getChildCount() returns "+i, i+1 == action2->getChildCount(), __FILE__, __LINE__);

            Assert::assertNotNull("getChild(0) returns a non null value",
                    (QObject*)action2->getChild(0), __FILE__, __LINE__);
#if 0
            assertIndexOutOfBoundsException(action2::getChild, i+1, i+1, __FILE__, __LINE__);
#endif
            // Connect a new child expression
            StringActionMemory* expr = new StringActionMemory("IQSA"+i, "");
            MaleSocket* maleSocket = ((DefaultStringActionManager*)
                    InstanceManager::getDefault("StringActionManager"))->registerAction(expr);
            action2->getChild(i)->_connect(maleSocket);
        }
    }

    //@Test
    /*public*/  void StringManyTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    // Test the methods connected(FemaleSocket) and getActionSystemName(int)
    //@Test
    /*public*/  void StringManyTest::testConnected_getActionSystemName() /*throws SocketAlreadyConnectedException */{
        StringMany* action = new StringMany("IQSA121", "");

        StringActionMemory* stringActionMemory = new StringActionMemory("IQSA122", "");
        MaleSocket* maleSAMSocket = ((DefaultStringActionManager*)
                InstanceManager::getDefault("StringActionManager"))->registerAction(stringActionMemory);

        Assert::assertEquals("Num children is correct", 1, action->getChildCount(), __FILE__, __LINE__);

        // Test connect and disconnect
        action->getChild(0)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertEquals("getActionSystemName(0) is correct", "IQSA122", action->getActionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(1) is null", action->getActionSystemName(1), __FILE__, __LINE__);
        action->getChild(0)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(0) is null", action->getActionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(1) is null", action->getActionSystemName(1), __FILE__, __LINE__);

        action->getChild(1)->_connect(maleSAMSocket);
        Assert::assertEquals("Num children is correct", 2, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(0) is null", action->getActionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getActionSystemName(1) is correct", "IQSA122", action->getActionSystemName(1), __FILE__, __LINE__);
        action->getChild(0)->_disconnect();    // Test removing child with the wrong index.
        Assert::assertEquals("Num children is correct", 2, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(0) is null", action->getActionSystemName(0), __FILE__, __LINE__);
        Assert::assertEquals("getActionSystemName(1) is correct", "IQSA122", action->getActionSystemName(1), __FILE__, __LINE__);
        action->getChild(1)->_disconnect();
        Assert::assertEquals("Num children is correct", 2, action->getChildCount(), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(0) is null", action->getActionSystemName(0), __FILE__, __LINE__);
        Assert::assertNull("getActionSystemName(1) is null", action->getActionSystemName(1), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void StringManyTest::testDescription() {
        StringMany* action = new StringMany("IQSA121", "");
        Assert::assertEquals("Short description", "Many", action->getShortDescription(QLocale()), __FILE__, __LINE__);
        Assert::assertEquals("Long description", "Many", action->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void StringManyTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _category = Category::COMMON;
        _isExternal = false;

        logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        conditionalNG = new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)conditionalNG->self());
        conditionalNG->setEnabled(true);
        conditionalNG->setRunDelayed(false);
        logixNG->addConditionalNG((DefaultConditionalNG*)conditionalNG);

        DoStringAction* doStringAction = new DoStringAction("IQDA321", "");
        MaleSocket* maleSocketDoStringAction = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->registerAction(doStringAction);
        conditionalNG->getChild(0)->_connect(maleSocketDoStringAction);

        StringMany* action = new StringMany("IQSA321", "");
        MaleSocket* maleSocket = ((DefaultStringActionManager*)
                InstanceManager::getDefault("StringActionManager"))->registerAction(action);
        doStringAction->getChild(1)->_connect(maleSocket);
        _base = action;
        _baseMaleSocket = maleSocket;

        if (! logixNG->setParentForAllChildren(new QStringList())) throw new RuntimeException();
        logixNG->setEnabled(true);
    }

    //@After
    /*public*/  void StringManyTest::tearDown() {
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
    }

