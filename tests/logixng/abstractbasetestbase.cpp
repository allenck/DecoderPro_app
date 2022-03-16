#include "abstractbasetestbase.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "malesocket.h"
#include "assert1.h"
#include "conditionalng.h"
#include "logixng.h"
#include "femalesocket.h"
#include "stringwriter.h"
#include "printwriter.h"
#include "atomicboolean.h"

/**
 * Test AbstractAnalogExpression
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  abstract class AbstractBaseTestBase {



    /**
     * Returns the LogixNG for _base->
     * @return the LogixNG for _base or null if _base doesn't have any LogixNG
     */
//    /*public*/  abstract ConditionalNG getConditionalNG();

    /**
     * Returns a MaleSocket that can be connected to _base->getChild(0).
     * If _base cannot have any children, this method returns null.
     * @return a male socket or null
     */
    //@CheckForNull
//    /*public*/  abstract MaleSocket getConnectableChild();

    /**
     * Returns the LogixNG for _base->
     * @return the LogixNG for _base or null if _base doesn't have any LogixNG
     */
//    /*public*/  abstract LogixNG getLogixNG();

    /**
     * Creates a new socket.
     * Some items can create new sockets automaticly and this method is used
     * to test that.
     * @return true if a new socket is added. false if this item doesn't
     * support adding new sockets.
     * @throws jmri.jmrit.logixng.SocketAlreadyConnectedException if socket is already connected
     */
//    abstract /*public*/  boolean addNewSocket() throws SocketAlreadyConnectedException;

    /*public*/  /*static*/ MaleSocket* AbstractBaseTestBase::getLastMaleSocket(MaleSocket* socket) {
        MaleSocket* lastMaleSocket = socket;
        Base* base = (Base*)socket;
        while ((base != nullptr) && qobject_cast<MaleSocket*>(base->bself())) {
            lastMaleSocket = (MaleSocket*) base->bself();
            base = ((MaleSocket*)base->bself())->getObject();
        }
        return lastMaleSocket;
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetConditionalNG() {
        if (getConditionalNG() == nullptr) {
            log->warn(tr("Method getConditionalNG() returns null for class %1").arg(this->metaObject()->className()));
            log->error(tr("Method getConditionalNG() returns null for class %1").arg(this->metaObject()->className()));
        }
        Assert::assertTrue("ConditionalNG is equal", getConditionalNG() == _base->getConditionalNG(), __FILE__, __LINE__);

        _base->getConditionalNG()->setEnabled(false);
        _base->setParent(nullptr);
        Assert::assertNull("ConditionalNG is null", _base->getConditionalNG()->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetLogixNG() {
        if (getLogixNG() == nullptr) {
            log->warn(tr("Method getLogixNG() returns null for class %1").arg(this->metaObject()->className()));
        }
        Assert::assertTrue("LogixNG is equal", getLogixNG()->equals(_base->getLogixNG()), __FILE__, __LINE__);

        _base->getConditionalNG()->setEnabled(false);
        _base->setParent(nullptr);
        Assert::assertNull("LogixNG is null", _base->getLogixNG()->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketGetConditionalNG() {
        Assert::assertTrue("conditionalNG is equal",
                _base->getConditionalNG() == _baseMaleSocket->getConditionalNG(), __FILE__, __LINE__);
//        _base->getConditionalNG().setEnabled(false);
//        _base->setParent(null);
//        Assert::assertTrue("conditionalNG is equal",
//                _base->getConditionalNG() == _baseMaleSocket->getConditionalNG());
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketGetLogixNG() {
        Assert::assertTrue("logixNG is equal",
                _base->getLogixNG() == _baseMaleSocket->getLogixNG(), __FILE__, __LINE__);
//        _base->getConditionalNG().setEnabled(false);
//        _base->setParent(null);
//        Assert::assertTrue("logixNG is equal",
//                _base->getLogixNG() == _baseMaleSocket->getLogixNG());
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketGetRoot() {
        Assert::assertTrue("root is equal", _base->getRoot() == _baseMaleSocket->getRoot(), __FILE__, __LINE__);
        _base->getConditionalNG()->setEnabled(false);
        _base->setParent(nullptr);
        Assert::assertTrue("root is equal", _base->getRoot() == _baseMaleSocket->getRoot(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetParent() {
        Assert::assertTrue("Object of _baseMaleSocket is _base", _base == getLastMaleSocket(_baseMaleSocket)->getObject(), __FILE__, __LINE__);
        Assert::assertTrue("Parent of _base is _baseMaleSocket", _base->getParent() == getLastMaleSocket(_baseMaleSocket), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testFemaleSocketSystemName() {
        for (int i=0; i < _base->getChildCount(); i++) {
            Assert::assertEquals(_base->getSystemName(), _base->getChild(i)->getSystemName(), __FILE__, __LINE__);
        }
    }
#if 0
    /**
     * Set parent to null for all children to item, and their children.
     */
    /*private*/ void AbstractBaseTestBase::clearParent(Base* item) {
        for (int i=0; i < item->getChildCount(); i++) {
            FemaleSocket* femaleSocket = item->getChild(i);
            femaleSocket->setParent(nullptr);

            if (femaleSocket->isConnected()) {
                clearParent(femaleSocket->getConnectedSocket());
            }
        }
    }

    /**
     * Check that parent is correct for all children to item, and their children.
     */
    /*private*/ void AbstractBaseTestBase::checkParent(Base* item) {
        for (int i=0; i < item->getChildCount(); i++) {
            FemaleSocket* femaleSocket = item->getChild(i);
            if (item != femaleSocket->getParent()) {
                log->error(tr("item: %1, %2 - parent: %3, %4").arg(item->bself()->metaObject()->className(), item->bself()->metaObject()->className(), femaleSocket->getParent()->bself()->metaObject()->className(), femaleSocket->getParent()->bself()->metaObject()->className()));
            }
            Assert::assertTrue("parent is correct", item == femaleSocket->getParent(), __FILE__, __LINE__);

            if (femaleSocket->isConnected()) {
                MaleSocket* connectedSocket = femaleSocket->getConnectedSocket();

                if (femaleSocket != connectedSocket->getParent()) {
                    log->error(tr("femaleSocket: %1, %2 - parent: %3, %4 - child: %5, %6")
                               .arg(femaleSocket->getSystemName(), femaleSocket->bself()->metaObject()->className(),
                                    connectedSocket->getParent()->getSystemName(), connectedSocket->getParent()->bself()->metaObject()->className()),
                               connectedSocket->getSystemName(), connectedSocket->bself()->metaObject()->className());
                }
                Assert::assertTrue("parent is correct", femaleSocket == connectedSocket->getParent(), __FILE__, __LINE__);
                checkParent(connectedSocket);
            }
        }
    }

    /*.*
     * Test that the method setParentForAllChildren() works when there are
     * connected children.
     *./
    //@Test
    /*public*/  void AbstractBaseTestBase::testSetParentForAllChildren_WithConnectedChildren() {
        _base->getConditionalNG()->setEnabled(false);
        clearParent(_base);     // Parent can't be set to null for AbstractFemaleSocket
        _base->setParentForAllChildren();
        checkParent(_base);
    }

    /*.*
     * Test that the method setParentForAllChildren() works when there are
     * no connected children.
     *./
    //@Test
    /*public*/  void AbstractBaseTestBase::testSetParentForAllChildren_WithoutConnectedChildren() {
        _base->getConditionalNG()->setEnabled(false);
        clearParent(_base);     // Parent can't be set to null for AbstractFemaleSocket
        for (int i=0; i < _base->getChildCount(); i++) {
            FemaleSocket* femaleSocket = _base->getChild(i);
            femaleSocket->_disconnect();
        }
        _base->setParentForAllChildren();
        checkParent(_base);
    }
*/
#endif
    /**
     * Returns the expected result of _base->printTree(writer, TREE_INDENT)
     * @return the expected printed tree
     */
//    /*public*/  abstract String getExpectedPrintedTree();

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetPrintTree() {
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _baseMaleSocket->printTree(QLocale("English"), printWriter, TREE_INDENT, &mutableInt);
        Assert::assertEquals("Tree is equal", getExpectedPrintedTree(), stringWriter->toString(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketGetPrintTree() {
        /// Test that the male socket of the item prints the same tree
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _baseMaleSocket->printTree(QLocale("English"), printWriter, TREE_INDENT, &mutableInt);
        Assert::assertEquals("Tree is equal", getExpectedPrintedTree(), stringWriter->toString(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetPrintTreeWithStandardLocale() {
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _baseMaleSocket->printTree(printWriter, TREE_INDENT, &mutableInt);
        Assert::assertEquals("Tree is equal", getExpectedPrintedTree(), stringWriter->toString(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketGetPrintTreeWithStandardLocale() {
        QLocale oldLocale = QLocale();
//        QLocale.setDefault(Locale.ENGLISH);
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _baseMaleSocket->printTree(printWriter, TREE_INDENT, &mutableInt);
        Assert::assertEquals("Tree is equal", getExpectedPrintedTree(), stringWriter->toString(), __FILE__, __LINE__);
//        Locale.setDefault(oldLocale);
    }

    /**
     * Returns the expected result of _base->getRoot().printTree(writer, TREE_INDENT)
     * @return the expected printed tree
     */
//    /*public*/  abstract String getExpectedPrintedTreeFromRoot();

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetPrintTreeFromRoot() {
        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _base->getRoot()->printTree(QLocale("English"), printWriter, TREE_INDENT,&mutableInt);
        Assert::assertEquals("Tree is equal", getExpectedPrintedTreeFromRoot(), stringWriter->toString(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testGetDeepCopy() /*throws JmriException*/ {
        QMap<QString, QString> systemNames = QMap<QString, QString>();
        QMap<QString, QString> userNames = QMap<QString, QString>();
        QMap<QString, QString> comments = QMap<QString, QString>();

        // The copy is not a male socket so it will not get the local variables
        _baseMaleSocket->clearLocalVariables();

        StringWriter* stringWriter = new StringWriter();
        PrintWriter* printWriter = new PrintWriter(stringWriter);
        int mutableInt=0;
        _baseMaleSocket->printTree(QLocale("English"), printWriter, TREE_INDENT, &mutableInt);
        QString originalTree = stringWriter->toString();

        Base* copy = _base->getDeepCopy(systemNames, userNames);

        stringWriter = new StringWriter();
        printWriter = new PrintWriter(stringWriter);

        Assert::assertTrue(copy != nullptr, __FILE__, __LINE__);
        mutableInt =0;
        copy->printTree(QLocale("English"), printWriter, TREE_INDENT, &mutableInt);
        QString copyTree = stringWriter->toString();
#if 0 // TODO:
        if ( originalTree !=(copyTree)) {
            System.out.format("---------------------%n%nOriginal tree:%n%s%n---------------------%n%nCopy tree:%n%s%n---------------------%n%n", originalTree, copyTree);
        }
#endif
        // REMOVE LATER!!!!!!!!
        // REMOVE LATER!!!!!!!!
        // REMOVE LATER!!!!!!!!
//        Assume.assumeTrue(originalTree.equals(copyTree));
        // REMOVE LATER!!!!!!!!
        // REMOVE LATER!!!!!!!!
        // REMOVE LATER!!!!!!!!

        Assert::assertEquals("Tree is equal", originalTree, copyTree, __FILE__, __LINE__);

#if 0
        // Test that we can give the copied items new system names and user names

        QList<Base*> originalList = QList<Base*>();
        _baseMaleSocket->forEntireTree((Base b) -> {
            if (qobject_cast<MaleSocket*>(b.bself())) {
                b.setComment(RandomStringUtils.randomAlphabetic(10));

                originalList.add(b);

                // A system name with a dollar sign after the sub system prefix
                // can have any character after the dollar sign.
                QString newSystemName =
                        ((MaleSocket)b).getManager()
                                .getSubSystemNamePrefix() + "$" + RandomStringUtils.randomAlphabetic(10);
                QString newUserName = RandomStringUtils.randomAlphabetic(20);

                systemNames.put(b.getSystemName(), newSystemName);
                userNames.put(b.getSystemName(), newUserName);
                comments.put(b.getSystemName(), b.getComment());
            }
        });

        copy = _base->getDeepCopy(systemNames, userNames);

        QList<Base*> copyList = QList<Base*>();
        copy->forEntireTree((Base b) -> {
            if (b instanceof MaleSocket) {
                copyList.add(b);
            }
        });

        for (int i=0; i < originalList.size(); i++) {
            Assert::assertEquals(copyList.at(i)->getSystemName(),
                    systemNames.value(originalList.at(i)->getSystemName()), __FILE__, __LINE__);

            Assert::assertEquals(copyList.at(i)->getUserName(),
                    userNames.value(originalList.at(i)->getSystemName()), __FILE__, __LINE__);

            Assert::assertEquals(copyList.at(i)->getComment(),
                    comments.value(originalList.at(i)->getSystemName()), __FILE__, __LINE__);
        }
#endif
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testIsActive() {
        Assert::assertEquals(_base->getParent(), getLastMaleSocket(_baseMaleSocket), __FILE__, __LINE__);

        Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(false);
        Assert::assertFalse("_base is not active", _base->isActive(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(true);
        Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);

        Assert::assertTrue(_base->isActive(), __FILE__, __LINE__);
        ConditionalNG* conditionalNG = _base->getConditionalNG();
        if (conditionalNG != nullptr) {
            conditionalNG->setEnabled(false);
            Assert::assertFalse("_base is not active", _base->isActive(), __FILE__, __LINE__);
            conditionalNG->setEnabled(true);
        } else {
            log->error("_base has no ConditionalNG as ancestor");
        }

        Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);
        LogixNG* logixNG = _base->getLogixNG();
        if (logixNG != nullptr) {
            logixNG->setEnabled(false);
            Assert::assertFalse("_base is not active", _base->isActive(), __FILE__, __LINE__);
            logixNG->setEnabled(true);
            Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);
        } else {
            log->error("_base has no LogixNG as ancestor");
        }

        Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);
        _base->getConditionalNG()->setEnabled(false);
        _base->setParent(nullptr);
        Assert::assertTrue("_base is active", _base->isActive(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testMaleSocketIsActive() {
        _baseMaleSocket->setEnabled(false);
        Assert::assertFalse("_baseMaleSocket is not active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
        _baseMaleSocket->setEnabled(true);
        Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);

        Base* parent = _baseMaleSocket->getParent();
        while ((parent != nullptr) && !(qobject_cast<MaleSocket*>(parent->bself()))) {
            parent = parent->getParent();
        }
        if (parent != nullptr) {
            ((MaleSocket*)parent->bself())->setEnabled(false);
            Assert::assertFalse("_baseMaleSocket is not active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
            ((MaleSocket*)parent->bself())->setEnabled(true);
        }

        Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
        ConditionalNG* conditionalNG = _baseMaleSocket->getConditionalNG();
        if (conditionalNG != nullptr) {
            conditionalNG->setEnabled(false);
            Assert::assertFalse("_baseMaleSocket is not active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
            conditionalNG->setEnabled(true);
        } else {
            log->error("_base has no ConditionalNG as ancestor");
        }

        Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
        LogixNG* logixNG = _baseMaleSocket->getLogixNG();
        if (logixNG != nullptr) {
            logixNG->setEnabled(false);
            Assert::assertFalse("_baseMaleSocket is not active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
            logixNG->setEnabled(true);
            Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
        } else {
            log->error("_base has no LogixNG as ancestor");
        }

        Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
        _base->getConditionalNG()->setEnabled(false);
        _baseMaleSocket->setParent(nullptr);
        Assert::assertTrue("_baseMaleSocket is active", _baseMaleSocket->isActive(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testConstants() {
        Assert::assertTrue("String matches", "ChildCount" == (Base::PROPERTY_CHILD_COUNT), __FILE__, __LINE__);
        Assert::assertTrue("String matches", "SocketConnected" == (Base::PROPERTY_SOCKET_CONNECTED), __FILE__, __LINE__);
        Assert::assertEquals("integer matches", 0x02, Base::SOCKET_CONNECTED, __FILE__, __LINE__);
        Assert::assertEquals("integer matches", 0x04, Base::SOCKET_DISCONNECTED, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testNames() {
        Assert::assertNotNull("system name not null", _base->getSystemName(), __FILE__, __LINE__);
        Assert::assertFalse("system name is not empty string", _base->getSystemName().isEmpty(), __FILE__, __LINE__);

        _base->setUserName("One user name");
        Assert::assertTrue("User name matches", "One user name" == (_base->getUserName()), __FILE__, __LINE__);
        _base->setUserName("Another user name");
        Assert::assertTrue("User name matches", "Another user name" ==(_base->getUserName()), __FILE__, __LINE__);
        _base->setUserName("");
        Assert::assertNull("User name matches", _base->getUserName(), __FILE__, __LINE__);
        _base->setUserName("One user name");
        Assert::assertTrue("User name matches", "One user name" == (_base->getUserName()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testParent() {
        _base->getConditionalNG()->setEnabled(false);
        MyBase* a = new MyBase();
        _base->setParent(nullptr);
        Assert::assertNull("Parent matches", _base->getParent()->bself(), __FILE__, __LINE__);
        _base->setParent(a);
        Assert::assertTrue("Parent matches", a == _base->getParent(), __FILE__, __LINE__);
        _base->setParent(nullptr);
        Assert::assertNull("Parent matches", _base->getParent()->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testIsEnabled() {
        MyBase* a = new MyBase();
        Assert::assertTrue("isEnabled() returns true by default", a->isEnabled(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testDispose() {
        _baseMaleSocket->setEnabled(false);
        _base->dispose();
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testRunOnGUIDelayed() {
        // Many tests doesn't work if runOnGUIDelayed is true, so this test
        // is to ensure that all the other tests behave as they should.
        // If a test want to test with runOnGUIDelayed true, that test can
        // set runOnGUIDelayed to true.
        Assert::assertFalse("runOnGUIDelayed is false",
                _base->getConditionalNG()->getRunDelayed(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testChildAndChildCount() {
        Assert::assertEquals("childCount is equal", _base->getChildCount(), _baseMaleSocket->getChildCount(), __FILE__, __LINE__);
        for (int i=0; i < _base->getChildCount(); i++) {
            Assert::assertTrue("child is equal", _base->getChild(i) == _baseMaleSocket->getChild(i), __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testBeanType() {
        Assert::assertEquals("getbeanType() is equal",
                ((NamedBean*)_base->bself())->getBeanType(),
                ((NamedBean*)_baseMaleSocket->bself())->getBeanType(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testDescribeState() {
        Assert::assertEquals("description matches",
                "Unknown",
                ((NamedBean*)_baseMaleSocket->bself())->describeState(NamedBean::UNKNOWN), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void AbstractBaseTestBase::testAddAndRemoveSocket() /*throws SocketAlreadyConnectedException*/ {
        AtomicBoolean* ab = new AtomicBoolean(false);
#if 0 // TODO:
        AtomicReference<PropertyChangeEvent> ar = new AtomicReference<>();

        _base->addPropertyChangeListener((PropertyChangeEvent evt) -> {
            ab.set(true);
            ar.set(evt);
        });

        ab.set(false);

        _baseMaleSocket->setEnabled(false);

        // Some item doesn't support adding new sockets.
        // Return if the item under test doesn't.
        if (!addNewSocket()) return;

        Assert::assertTrue("PropertyChangeEvent fired", ab.(), __FILE__, __LINE__);
        Assert::assertEquals(Base::PROPERTY_CHILD_COUNT, ar.get().getPropertyName(), __FILE__, __LINE__);
        Assert::assertTrue(ar.get().getNewValue() instanceof List, __FILE__, __LINE__);
        List list = (List)ar.get().getNewValue();
        for (Object o : list) {
            Assert::assertTrue(o instanceof FemaleSocket);
        }
#endif
    }
#if 0
/*
    @Test
    /*public*/  void testRemoveChild() {
        AtomicBoolean ab = new AtomicBoolean(false);

        _base->addPropertyChangeListener((PropertyChangeEvent evt) -> {
            ab.set(true);
        });

        for (int i=_base->getChildCount()-1; i > 0; i--) {
            ab.set(true);
            boolean hasThrown = false;

            try {
                _base->removeChild(i);
            } catch (UnsupportedOperationException e) {
                hasThrown = true;
                Assert::assertEquals("Correct error message",
                        "Child "+Integer.toString(i)+" cannot be removed",
                        e.getMessage());
            }

            if (_base->canRemoveChild(i)) {
                Assert::assertTrue("PropertyChange is fired", ab.get());
            } else {
                Assert::assertTrue("Exception is thrown", hasThrown);
            }
        }
    }
/*
    private void connect(FemaleSocket femaleSocket, MaleSocket maleSocket) throws SocketAlreadyConnectedException {
        if (femaleSocket.isConnected()) femaleSocket.disconnect();
        femaleSocket.connect(maleSocket);
    }

    private PropertyChangeListener getPropertyChangeListener(String name, AtomicBoolean flag, Object expectedNewValue) {
        return (PropertyChangeEvent evt) -> {
            if (name.equals(evt.getPropertyName())) {
                Assert::assertTrue("socket is correct", expectedNewValue == evt.getNewValue());
                flag.set(true);
            }
        };
    }

    private void assertListeners(
            PropertyChangeListener lc,
            PropertyChangeListener ld,
            boolean expectManagerListener,
            boolean expectConnectedListener,
            boolean expectDisconnectedListener) {

        boolean hasManagerListener = false;
        boolean hasConnectedListener = false;
        boolean hasDisconnectedListener = false;
        for (PropertyChangeListener l : ((NamedBean)_baseMaleSocket).getPropertyChangeListeners()) {
            if (l instanceof jmri.Manager) hasManagerListener = true;
            else if (l == lc) hasConnectedListener = true;
            else if (l == ld) hasDisconnectedListener = true;
            else Assert::fail("getPropertyChangeListeners() returns unknown listener: " + l.toString());
        }
        if (expectManagerListener) {
            Assert::assertTrue("getPropertyChangeListeners() has manager listener", hasManagerListener);
        } else {
            Assert::assertFalse("getPropertyChangeListeners() has not manager listener", hasManagerListener);
        }
        if (expectConnectedListener) {
            Assert::assertTrue("getPropertyChangeListeners() has connected listener", hasConnectedListener);
        } else {
            Assert::assertFalse("getPropertyChangeListeners() has not connected listener", hasConnectedListener);
        }
        if (expectDisconnectedListener) {
            Assert::assertTrue("getPropertyChangeListeners() has disconnected listener", hasDisconnectedListener);
        } else {
            Assert::assertFalse("getPropertyChangeListeners() has not disconnected listener", hasDisconnectedListener);
        }
    }

    // This method is needet to test property change methods which only listen
    // to a particular property, since these property change listeners uses a
    // proxy listener.
    private void assertListeners(
            String propertyName,
            FemaleSocket child,
            AtomicBoolean flag,
            boolean expectedResult) {

        // Check that we have the expected listener
        PropertyChangeListener[] listeners =
                ((NamedBean)_baseMaleSocket).getPropertyChangeListeners(propertyName);

        if (expectedResult) {
            Assert::assertEquals("num property change listeners matches",
                    1, listeners.length);
        } else {
            Assert::assertEquals("num property change listeners matches",
                    0, listeners.length);
            return;
        }

        // If here, we expect success.

        // We call propertyChange to check that it's the correct listener we have
        flag.set(false);
        listeners[0].propertyChange(new PropertyChangeEvent(this, propertyName, null, child));
        Assert::assertTrue("flag is set", flag.get());
        Assert::assertTrue("getPropertyChangeListeners("+propertyName+") has listener", flag.get());
    }



/*
    Note: PROPERTY_SOCKET_CONNECTED and PROPERTY_SOCKET_DISCONNECTED has been
    moved to FemaleSocket.


    // Test these methods:
    // * addPropertyChangeListener(PropertyChangeListener l)
    // * removePropertyChangeListener(PropertyChangeListener l)
    // * getNumPropertyChangeListeners()
    // * getPropertyChangeListeners()
    @Test
    /*public*/  void testPropertyChangeListener1() throws SocketAlreadyConnectedException {
        // We need at least one child to do this test.
        // Some item doesn't have children.
        // Return if the item under test doesn't.
        if (_base->getChildCount() == 0) return;

        _baseMaleSocket->setEnabled(false);

        MaleSocket maleSocket = getConnectableChild();

        FemaleSocket child = _base->getChild(0);

        AtomicBoolean flagConnected = new AtomicBoolean();
        PropertyChangeListener lc =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, flagConnected, child);

        AtomicBoolean flagDisconnected = new AtomicBoolean();
        PropertyChangeListener ld =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, flagDisconnected, child);

        // Note that AbstractManager.register() register itself as a
        // PropertyChangeListener. Therefore we have one listener before
        // adding our own listeners.
        Assert::assertEquals("num property change listeners matches",
                1, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(lc);
        Assert::assertEquals("num property change listeners matches",
                2, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, true, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(ld);
        Assert::assertEquals("num property change listeners matches",
                3, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, true, true);

        Assert::assertNull("listener ref is null", ((NamedBean)_baseMaleSocket).getListenerRef(lc));

        // Connect shall do a firePropertyChange which will set the flag
        flagConnected.set(false);
        connect(child, maleSocket);
        Assert::assertTrue("flag is set", flagConnected.get());

        // Disconnect shall do a firePropertyChange which will set the flag
        flagDisconnected.set(false);
        _base->getChild(0).disconnect();
        Assert::assertTrue("flag is set", flagDisconnected.get());

        // Try to remove the listeners

        // Check that we have the expected listeners
        assertListeners(lc, ld, true, true, true);
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(lc);

        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, true);
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(ld);

        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, false);
    }

    // Test these methods:
    // * addPropertyChangeListener(String propertyName, PropertyChangeListener l)
    // * removePropertyChangeListener(String propertyName, PropertyChangeListener l)
    // * getNumPropertyChangeListeners()
    @Test
    /*public*/  void testPropertyChangeListener2() throws SocketAlreadyConnectedException {
        // We need at least one child to do this test.
        // Some item doesn't have children.
        // Return if the item under test doesn't.
        if (_base->getChildCount() == 0) return;

        _baseMaleSocket->setEnabled(false);

        MaleSocket maleSocket = getConnectableChild();

        FemaleSocket child = _base->getChild(0);

        AtomicBoolean flagConnected = new AtomicBoolean();
        PropertyChangeListener lc =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, flagConnected, child);

        AtomicBoolean flagDisconnected = new AtomicBoolean();
        PropertyChangeListener ld =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, flagDisconnected, child);

        // Note that AbstractManager.register() register itself as a
        // PropertyChangeListener. Therefore we have one listener before
        // adding our own listeners.
        Assert::assertEquals("num property change listeners matches",
                1, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, lc);
        Assert::assertEquals("num property change listeners matches",
                2, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());

        // Check that we have the expected listener
        PropertyChangeListener[] listeners = ((NamedBean)_baseMaleSocket).getPropertyChangeListeners(Base::PROPERTY_SOCKET_CONNECTED);
        Assert::assertEquals("num property change listeners matches",
                1, listeners.length);

        // We call propertyChange to check that it's the correct listener we have
        flagConnected.set(false);
        listeners[0].propertyChange(new PropertyChangeEvent(this, Base::PROPERTY_SOCKET_CONNECTED, null, child));
        Assert::assertTrue("flag is set", flagConnected.get());

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, ld);
        Assert::assertEquals("num property change listeners matches",
                3, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());

        // Check that we have the expected listener
        listeners = ((NamedBean)_baseMaleSocket).getPropertyChangeListeners(Base::PROPERTY_SOCKET_DISCONNECTED);
        Assert::assertEquals("num property change listeners matches",
                1, listeners.length);

        // We call propertyChange to check that it's the correct listener we have
        flagDisconnected.set(false);
        listeners[0].propertyChange(new PropertyChangeEvent(this, Base::PROPERTY_SOCKET_DISCONNECTED, null, child));
        Assert::assertTrue("flag is set", flagConnected.get());

        Assert::assertNull("listener ref is null", ((NamedBean)_baseMaleSocket).getListenerRef(lc));

        // Connect shall do a firePropertyChange which will set the flag
        flagConnected.set(false);
        connect(child, maleSocket);
        Assert::assertTrue("flag is set", flagConnected.get());

        // Disconnect shall do a firePropertyChange which will set the flag
        flagDisconnected.set(false);
        _base->getChild(0).disconnect();
        Assert::assertTrue("flag is set", flagDisconnected.get());

        // Try to remove the listeners

        // Check that we have the expected listeners
        assertListeners(Base::PROPERTY_SOCKET_CONNECTED, child, flagConnected, true);
        assertListeners(Base::PROPERTY_SOCKET_DISCONNECTED, child, flagDisconnected, true);

        // This should be ignored since the name doesn't match the listener
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, lc);

        // Check that we have the expected listeners
        assertListeners(Base::PROPERTY_SOCKET_CONNECTED, child, flagConnected, true);
        assertListeners(Base::PROPERTY_SOCKET_DISCONNECTED, child, flagDisconnected, true);

        // This should work
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, lc);

        // Check that we have the expected listeners
        assertListeners(Base::PROPERTY_SOCKET_CONNECTED, child, flagConnected, false);
        assertListeners(Base::PROPERTY_SOCKET_DISCONNECTED, child, flagDisconnected, true);

        // This should be ignored since the name doesn't match the listener
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, ld);

        // Check that we have the expected listeners
        assertListeners(Base::PROPERTY_SOCKET_CONNECTED, child, flagConnected, false);
        assertListeners(Base::PROPERTY_SOCKET_DISCONNECTED, child, flagDisconnected, true);

        // This should work
        ((NamedBean)_baseMaleSocket).removePropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, ld);

        // Check that we have the expected listeners
        assertListeners(Base::PROPERTY_SOCKET_CONNECTED, child, flagConnected, false);
        assertListeners(Base::PROPERTY_SOCKET_DISCONNECTED, child, flagDisconnected, false);
    }

    // Test these methods:
    // * addPropertyChangeListener(PropertyChangeListener l, String name, String listenerRef)
    // * removePropertyChangeListener(PropertyChangeListener l, String name, String listenerRef)
    // * getNumPropertyChangeListeners()
    // * getPropertyChangeListeners()
    @Test
    /*public*/  void testPropertyChangeListener3() throws SocketAlreadyConnectedException {
        // We need at least one child to do this test.
        // Some item doesn't have children.
        // Return if the item under test doesn't.
        if (_base->getChildCount() == 0) return;

        _baseMaleSocket->setEnabled(false);

        MaleSocket maleSocket = getConnectableChild();

        FemaleSocket child = _base->getChild(0);

        AtomicBoolean flagConnected = new AtomicBoolean();
        PropertyChangeListener lc =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, flagConnected, child);

        AtomicBoolean flagDisconnected = new AtomicBoolean();
        PropertyChangeListener ld =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, flagDisconnected, child);

        // Note that AbstractManager.register() register itself as a
        // PropertyChangeListener. Therefore we have one listener before
        // adding our own listeners.
        Assert::assertEquals("num property change listeners matches",
                1, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(lc, _baseMaleSocket->getSystemName(), "Connected listener");
        Assert::assertEquals("num property change listeners matches",
                2, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, true, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(ld, _baseMaleSocket->getSystemName(), "Disconnected listener");
        Assert::assertEquals("num property change listeners matches",
                3, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, true, true);

        Assert::assertEquals("listener ref is correct", "Connected listener", ((NamedBean)_baseMaleSocket).getListenerRef(lc));
        Assert::assertEquals("listener ref is correct", "Disconnected listener", ((NamedBean)_baseMaleSocket).getListenerRef(ld));

        // Connect shall do a firePropertyChange which will set the flag
        flagConnected.set(false);
        connect(child, maleSocket);
        Assert::assertTrue("flag is set", flagConnected.get());

        // Disconnect shall do a firePropertyChange which will set the flag
        flagDisconnected.set(false);
        _base->getChild(0).disconnect();
        Assert::assertTrue("flag is set", flagDisconnected.get());
    }

    // Test these methods:
    // * addPropertyChangeListener(String propertyName, PropertyChangeListener l, String name, String listenerRef)
    // * removePropertyChangeListener(String propertyName, PropertyChangeListener l)
    // * getNumPropertyChangeListeners()
    @Test
    /*public*/  void testPropertyChangeListener4() throws SocketAlreadyConnectedException {
        // We need at least one child to do this test.
        // Some item doesn't have children.
        // Return if the item under test doesn't.
        if (_base->getChildCount() == 0) return;

        _baseMaleSocket->setEnabled(false);

        MaleSocket maleSocket = getConnectableChild();

        FemaleSocket child = _base->getChild(0);

        AtomicBoolean flagConnected = new AtomicBoolean();
        PropertyChangeListener lc =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, flagConnected, child);

        AtomicBoolean flagDisconnected = new AtomicBoolean();
        PropertyChangeListener ld =
                getPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, flagDisconnected, child);

        // Note that AbstractManager.register() register itself as a
        // PropertyChangeListener. Therefore we have one listener before
        // adding our own listeners.
        Assert::assertEquals("num property change listeners matches",
                1, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
        assertListeners(lc, ld, true, false, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(Base::PROPERTY_SOCKET_CONNECTED, lc, _baseMaleSocket->getSystemName(), "Connected listener");
        Assert::assertEquals("num property change listeners matches",
                2, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
//        assertListeners(lc, ld, true, true, false);

        ((NamedBean)_baseMaleSocket).addPropertyChangeListener(Base::PROPERTY_SOCKET_DISCONNECTED, ld, _baseMaleSocket->getSystemName(), "Disconnected listener");
        Assert::assertEquals("num property change listeners matches",
                3, ((NamedBean)_baseMaleSocket).getNumPropertyChangeListeners());
        // Check that we have the expected listeners
//        assertListeners(lc, ld, true, true, true);

        Assert::assertEquals("listener ref is correct", "Connected listener", ((NamedBean)_baseMaleSocket).getListenerRef(lc));
        Assert::assertEquals("listener ref is correct", "Disconnected listener", ((NamedBean)_baseMaleSocket).getListenerRef(ld));

        // Connect shall do a firePropertyChange which will set the flag
        flagConnected.set(false);
        connect(child, maleSocket);
        Assert::assertTrue("flag is set", flagConnected.get());

        // Disconnect shall do a firePropertyChange which will set the flag
        flagDisconnected.set(false);
        _base->getChild(0).disconnect();
        Assert::assertTrue("flag is set", flagDisconnected.get());
    }

    @Test
    /*public*/  void testPropertyChangeListeners5() {

        PropertyChangeListener listener1 = (PropertyChangeEvent evt) -> {};
        PropertyChangeListener listener2 = (PropertyChangeEvent evt) -> {};

        _baseMaleSocket->addPropertyChangeListener(listener1, "BeanA", "A name");
        _baseMaleSocket->addPropertyChangeListener(listener2, "BeanB", "Another name");
        Assert::assertEquals("A name", _baseMaleSocket->getListenerRef(listener1));
        List<String> listenerRefs = _baseMaleSocket->getListenerRefs();

        // The order of the listener refs may differ between runs so sort the list
        Collections.sort(listenerRefs);

        String listString = listenerRefs.stream().map(Object::toString)
                        .collect(Collectors.joining(", "));

        Assert::assertEquals("A name, Another name", listString);

        _baseMaleSocket->updateListenerRef(listener1, "New name");
        Assert::assertEquals("New name", _baseMaleSocket->getListenerRef(listener1));

        Assert::assertEquals(listener1,
                _baseMaleSocket->getPropertyChangeListenersByReference("BeanA")[0]);

        Assert::assertEquals(listener2,
                _baseMaleSocket->getPropertyChangeListenersByReference("BeanB")[0]);
    }
*/
#endif



    /**
     * Executes the method.
     * This interface is used by the method
     * {@link #assertIndexOutOfBoundsException(RunnableWithIndex, int, int)}
     */
    /*public*/  /*interface*/class RunnableWithIndex {
     public:
        /**
         * Run the method.
         * @param index the index
         */
        /*public*/  void run(int index);
    };

    /**
     * Assert that an IndexOutOfBoundsException is thrown and has the correct
     * error message.
     * <P>
     * This method is added since different Java versions gives different
     * error messages.
     * @param r the method to run
     * @param index the index
     * @param arraySize the size of the array
     */
    /*public*/  void AbstractBaseTestBase::assertIndexOutOfBoundsException(RunnableWithIndex* r, int index, int arraySize) {
        bool hasThrown = false;
        try {
            r->run(index);
        } catch (IndexOutOfBoundsException* ex) {
            hasThrown = true;
            QString msg1 = QString("Index: %1, Size: %2").arg(index, arraySize);
            QString msg2 = QString("Index %1 out of bounds for length %2").arg(index, arraySize);
            if (msg1 != (ex->getMessage()) && msg2 != (ex->getMessage())) {
                Assert::fail("Wrong error message: " + ex->getMessage(), __FILE__, __LINE__);
            }
        }
        Assert::assertTrue("Exception is thrown", hasThrown, __FILE__, __LINE__);
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractBaseTestBase::log = LoggerFactory::getLogger("AbstractBaseTestBase");
