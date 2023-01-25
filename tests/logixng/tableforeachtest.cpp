#include "tableforeachtest.h"
#include "defaultconditionalng.h"
#include "digitalmany.h"
#include "tableforeach.h"
#include "assert1.h"
#include "junitappender.h"
#include "junitutil.h"
#include "actionmemory.h"
#include "defaultlogixng.h"
#include "defaultconditionalngscaffold.h"
#include "defaultconditionalngmanager.h"
#include "symboltable.h"
#include "defaultnamedtablemanager.h"
#include <QString>
#include "logixng_thread.h"
#include <QStringList>

/**
 * Test TableForEach
 *
 * @author Daniel Bergqvist 2019
 */
// /*public*/  class TableForEachTest extends AbstractDigitalActionTestBase {


    //@Override
    /*public*/  ConditionalNG* TableForEachTest::getConditionalNG() {
        return _conditionalNG;
    }

    //@Override
    /*public*/  LogixNG* TableForEachTest::getLogixNG() {
        return _logixNG;
    }

    //@Override
    /*public*/  MaleSocket* TableForEachTest::getConnectableChild() {
        DigitalMany* action = new DigitalMany("IQDA999", "");
        MaleSocket* maleSocket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))->registerAction(action);
        return maleSocket;
    }

    //@Override
    /*public*/  QString TableForEachTest::getExpectedPrintedTree() {
        return QString(
                "Table: For each column of row \"\" in table \"''\" set variable \"\" and execute action A1 ::: Use default\n" \
                "   ! A1\n" \
                "      MyAction ::: Use default\n");
    }

    //@Override
    /*public*/  QString TableForEachTest::getExpectedPrintedTreeFromRoot() {
        return QString(
                "LogixNG: A new logix for test\n" \
                "   ConditionalNG: A conditionalNG\n" \
                "      ! A\n" \
                "         Table: For each column of row \"\" in table \"''\" set variable \"\" and execute action A1 ::: Use default\n" \
                "            ! A1\n" \
                "               MyAction ::: Use default\n");
    }

    //@Override
    /*public*/  NamedBean* TableForEachTest::createNewBean(QString systemName) {
        return new TableForEach(systemName, "");
    }

    //@Override
    /*public*/  bool TableForEachTest::addNewSocket() {
        return false;
    }

    //@Test
    /*public*/  void TableForEachTest::testCtor() {
        TableForEach* t = new TableForEach("IQDA321", "");
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
        t = new TableForEach("IQDA321", "");
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }
#if 0
/* DISABLE FOR NOW
    @Test
    /*public*/  void testCtorAndSetup1() {
        TableForEach* action = new TableForEach("IQDA321", "");
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        action->getChild(0)->setName("ZH12");
        action->setTimerActionSocketSystemName("IQDA554");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        // Setup action-> This connects the child actions to this action
        action->setup();

        JUnitAppender::assertMessage("cannot load digital action IQDA554", __FILE__, __LINE__);

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TableForEachTest::testCtorAndSetup2() {
        TableForEach* action = new TableForEach("IQDA321", "");
        Assert::assertNotNull("exists", action, __FILE__, __LINE__);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
        action->getChild(0)->setName("ZH12");
        action->setTimerActionSocketSystemName("");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        // Setup action-> This connects the child actions to this action
        action->setup();

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0)->getName(), __FILE__, __LINE__);
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0)->getClassName(), __FILE__, __LINE__);
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0)->isConnected(), __FILE__, __LINE__);

        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TableForEachTest::testCtorAndSetup3() {
        DigitalActionManager* m1 = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");

        MaleSocket* childSocket0 = m1.registerAction(new ActionMemory("IQDA554", null));

        TableForEach action = new TableForEach("IQDA321", null);
        Assert::assertNotNull("exists", action);
        Assert::assertEquals("action has 1 female socket", 1, action->getChildCount());
        action->getChild(0).setName("ZH12");
        action->setTimerActionSocketSystemName("IQDA554");

        Assert::assertEquals("action female socket name is ZH12",
                "ZH12", action->getChild(0).getName());
        Assert::assertEquals("action female socket is of correct class",
                "jmri.jmrit.logixng.implementation.DefaultFemaleDigitalActionSocket",
                action->getChild(0).getClass().getName());
        Assert::assertFalse("action female socket is not connected",
                action->getChild(0).isConnected());

        // Setup action-> This connects the child actions to this action
        action->setup();

        Assert::assertTrue("action female socket is connected",
                action->getChild(0).isConnected());
        Assert::assertEquals("child is correct bean",
                childSocket0,
                action->getChild(0).getConnectedSocket());

        Assert::assertEquals("action has 1 female sockets", 1, action->getChildCount());

        // Try run setup() again. That should not cause any problems.
        action->setup();

        Assert::assertEquals("action has 1 female sockets", 1, action->getChildCount());
    }
*/
#endif
    //@Test
    /*public*/  void TableForEachTest::testGetChild() {
        Assert::assertTrue("getChildCount() returns 1", 1 == _tableForEach->getChildCount(), __FILE__, __LINE__);

        Assert::assertNotNull("getChild(0) returns a non null value",
                _tableForEach->getChild(0)->bself(), __FILE__, __LINE__);

        bool hasThrown = false;
        try {
            _tableForEach->getChild(1);
        } catch (IllegalArgumentException* ex) {
            hasThrown = true;
            Assert::assertEquals("Error message is correct", "index has invalid value: 1", ex->getMessage(), __FILE__, __LINE__);
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TableForEachTest::testCategory() {
        Assert::assertTrue("Category matches", Category::COMMON == _base->getCategory(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TableForEachTest::testDescription() {
        TableForEach* a1 = new TableForEach("IQDA321", "");
        Assert::assertEquals("strings are equal", "Table: For each", a1->getShortDescription(QLocale()), __FILE__, __LINE__);
        TableForEach* a2 = new TableForEach("IQDA321", "");
        Assert::assertEquals("strings are equal", "Table: For each column of row \"\" in table \"''\" set variable \"\" and execute action A1", a2->getLongDescription(QLocale()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void TableForEachTest::testExecute() /*throws IOException */{

        _maleSocket->addLocalVariable("MyVariable", InitialValueType::None, nullptr);

        _logixNG->setEnabled(false);

        // Load table turnout_and_signals.csv
        NamedTable* csvTable = ((DefaultNamedTableManager*)
                InstanceManager::getDefault("NamedTableManager"))
                        ->loadTableFromCSV("IQT1", "", "program:java/test/jmri/jmrit/logixng/panel_and_data_files/turnout_and_signals.csv");

        _tableForEach->setTable(csvTable);
        _tableForEach->setRowOrColumn(TableRowOrColumn::Column);
        _tableForEach->setRowOrColumnName("1");
        _tableForEach->setLocalVariableName("MyVariable");
        _logixNG->setEnabled(true);

        Assert::assertEquals("IT1 :::  ::: IH1 :::  :::  ::: IT1 ::: IT3 ::: IH1" \
                " ::: IH6 :::  ::: IH4 ::: IH6 ::: IT1 ::: IH1 ::: IH3 ::: IH4" \
                " ::: IH6 ::: IT1 ::: IT3 :::  :::  ::: ",
                 _cells.join(" ::: "), __FILE__, __LINE__);
    }

    //@Test
    //@Override
    /*public*/  void TableForEachTest::testIsActive() {
        _logixNG->setEnabled(true);
        AbstractDigitalActionTestBase::testIsActive();
    }

    //@Test
    //@Override
    /*public*/  void TableForEachTest::testMaleSocketIsActive() {
        _logixNG->setEnabled(true);
        AbstractDigitalActionTestBase::testMaleSocketIsActive();
    }

    // The minimal setup for log4J
    //@Before
    /*public*/  void TableForEachTest::setUp() /*throws SocketAlreadyConnectedException*/ {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        JUnitUtil::resetProfileManager();
        JUnitUtil::initConfigureManager();
        JUnitUtil::initInternalSensorManager();
        JUnitUtil::initInternalTurnoutManager();
        JUnitUtil::initLogixNGManager();

        _category = Category::OTHER;
        _isExternal = false;

        _logixNG = ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))->createLogixNG("A new logix for test");  // NOI18N
        _conditionalNG = /*(DefaultConditionalNG*)*/new DefaultConditionalNGScaffold("IQC1", "A conditionalNG");  // NOI18N;
        ((DefaultConditionalNGManager*)InstanceManager::getDefault("ConditionalNG_Manager"))->Register((AbstractNamedBean*)_conditionalNG->self());
        _conditionalNG->setEnabled(true);
        _conditionalNG->setRunDelayed(false);
        _logixNG->addConditionalNG((DefaultConditionalNG*)_conditionalNG->bself());
        _tableForEach = new TableForEach("IQDA321", "");
//        _maleSocket = ((DefaultDigitalActionManager*)
//                InstanceManager::getDefault("DigitalActionManager"))->registerAction(_tableForEach);
        DefaultDigitalActionManager* mgr = (DefaultDigitalActionManager*)
                          InstanceManager::getDefault("DigitalActionManager");
        _maleSocket = mgr->registerAction(_tableForEach);
        _conditionalNG->getChild(0)->_connect(_maleSocket);
        _base = _tableForEach;
        _baseMaleSocket = _maleSocket;

//        _tableForEach->getChild(0)->_connect(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
//                ->registerAction(new MyAction04("IQDA999", "", _cells)));
        MaleDigitalActionSocket* socket = mgr->registerAction(new MyAction04("IQDA999", "", _cells));
        _tableForEach->getChild(0)->_connect(socket);

        if (! _logixNG->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        _logixNG->setEnabled(false);
    }

    //@After
    /*public*/  void TableForEachTest::tearDown() {
        JUnitAppender::suppressErrorMessage("tableHandle is null", __FILE__, __LINE__);
        _logixNG->setEnabled(false);
        LogixNG_Thread::stopAllLogixNGThreads();
        JUnitUtil::tearDown();
        _category = Other();
        _logixNG = nullptr;
        _conditionalNG = nullptr;
        _tableForEach = nullptr;
        _base = nullptr;
        _baseMaleSocket = nullptr;
        _maleSocket = nullptr;
    }


