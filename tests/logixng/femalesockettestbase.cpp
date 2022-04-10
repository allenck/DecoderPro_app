#include "femalesockettestbase.h"
#include "femalesocket.h"
#include "assert1.h"
#include "system.h"
#include "runtimeexception.h"
#include "swingconfiguratorinterface.h"
#include "swingtools.h"
#include <QLocale>
#include "abstractmalesocket.h"
#include "abstractanalogexpressionswing.h"
#include "loggerfactory.h"

FemaleSocketTestBase::FemaleSocketTestBase(QObject *parent) : QObject(parent)
{

}

/**
 * Base class for testing FemaleStringExpressionSocket classes
 *
 * @author Daniel Bergqvist 2018
 */
// /*public*/  abstract class FemaleSocketTestBase {


/**
 * Get the manager that handles the type of beans that can connect to this
 * female socket
 * @return the manager
 */
// /*protected*/ /*abstract*/virtual  Manager/*<? extends NamedBean>*/* getManager()=0;



    /*private*/ /*SortedSet*/QSet<QString> FemaleSocketTestBase::getClassNames(QList</*Class<? extends Base>*/QString> classes) {
        //SortedSet<String> set = new TreeSet<>();
    QSet<QString> set = QSet<QString>();

        // If the category doesn't exist in one of the sets, 'classes' is null.
        if (classes.isEmpty()) return set;

        for (/*Class<? extends Base>*/QString clazz : classes) {
            set.insert(clazz/*.getName()*/);
        }

        return set;
    }

    /*private*/ bool FemaleSocketTestBase::isSetsEqual(Category* category, /*SortedSet*/QSet<QString> set1, /*SortedSet*/QSet<QString> set2) {
        for (QString s1 : set1) {
            if (!set2.contains(s1)) {
                System::out(tr("set1 contains %1 in category %2 which is missing in set2%n").arg(s1, category->name()));
                return false;
            }
        }
        for (QString s2 : set2) {
            if (!set1.contains(s2)) {
                System::out(tr("set2 contains %1 in category %2 which is missing in set1%n").arg(s2, category->name()));
                return false;
            }
        }
        if (set1.size() != set2.size()) {
            System::out(tr("set1 and set2 has different sizes: %1, %2%n").arg(set1.size(), set2.size()));
            return false;
        }
        return true;
    }

    /**
     * Asserts that the two maps of connection classes holds the same classes.
     * The reason to why this method returns a bool is because every test
     * method is expected to have an assertion. And the statistical analysis is
     * not able to see that that assertion is here, so we therefore also need
     * an assertion in the caller method.
     * @param expectedMap the expected result
     * @param actualMap the actual result
     * @return true if assertion is correct
     */
    /*public*/  /*final*/ bool FemaleSocketTestBase::isConnectionClassesEquals(
            QHash<Category*, QList</*Class<? extends Base>*/QString>> expectedMap,
            QHash<Category*, QList</*Class<? extends Base>*/QString>> actualMap) {

        QList</*Class<? extends Base>*/QString> classes;
/*
        for (Category category : Category.values()) {
            System::out(tr("FemaleSocket: %s, category: %s%n",
                    femaleSocket.getClass().getName(),
                    category.name());
            classes = femaleSocket.getConnectableClasses().get(category);
            for (Class<? extends Base>QString clazz : classes) {
                System::out(tr("FemaleSocket: %s, category: %s, class: %s%n",
                        femaleSocket.getClass().getName(),
                        category.name(),
                        clazz.getName());
            }
        }
*/
        for (Category* category : Category::values()) {

            if (!isSetsEqual(
                    category,
                    getClassNames(expectedMap.value(category)),
                    getClassNames(actualMap.value(category)))) {

                System::err(tr("Set of classes are different for category %1:%2").arg(category->name()));

                classes = _femaleSocket->getConnectableClasses().value(category);
                for (/*Class<? extends Base>*/QString clazz : classes) {
                    System::err(tr("Set of classes are different:%1"));
                    System::err(tr("FemaleSocket: %1, category: %2, class: %3%n").arg(
                            _femaleSocket->bself()->metaObject()->className(),
                            category->name(),
                            clazz/*.getName()*/));
/*
                    log.error("Set of classes are different:");
                    log.error("FemaleSocket: {}, category: {}, class: {}",
                            femaleSocket.getClass().getName(),
                            category.name(),
                            clazz.getName());
*/
                }

                return false;
            }
        }

        // We will not get here if assertion fails.
        return true;
    }

    /**
     * Returns a new FemaleSocket with the specified name.
     * The method is used to test that the constructor throws an exception if
     * invalid name.
     * @param name the name of the socket
     * @return the new female socket
     */
//    /*protected*/ abstract FemaleSocket getFemaleSocket(String name);

    //@Test
    /*public*/  void FemaleSocketTestBase::testBadSocketName() {
        bool hasThrown = false;
        try {
            getFemaleSocket("----");
        } catch (IllegalArgumentException* e) {
            hasThrown = true;
        }
        Assert::assertTrue("exception thrown", hasThrown, __FILE__, __LINE__);
    }

//    abstract /*protected*/ bool hasSocketBeenSetup();

    //@Test
    /*public*/  void FemaleSocketTestBase::testSetup() /*throws SocketAlreadyConnectedException*/ {
        Assert::assertFalse("not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);

        // Check that we can call setup() even if the socket is not connected.
        _femaleSocket->setup();

        _femaleSocket->_connect(maleSocket);
        Assert::assertTrue("is connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        Assert::assertFalse("not setup", hasSocketBeenSetup(), __FILE__, __LINE__);
        _femaleSocket->setup();
        Assert::assertTrue("is setup", hasSocketBeenSetup(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testConnectIncompatibleSocket() {
        MaleSocket* incompatibleSocket = new IncompatibleMaleSocket();
        Assert::assertFalse("socket not compatible", _femaleSocket->isCompatible(incompatibleSocket), __FILE__, __LINE__);

        // Test connect incompatible male socket
        errorFlag->set(false);
        try {
            _femaleSocket->_connect(incompatibleSocket);
        } catch (IllegalArgumentException* ex) {
            errorFlag->set(true);
        } catch (SocketAlreadyConnectedException* ex) {
            // We shouldn't be here.
            Assert::fail("socket is already connected", __FILE__, __LINE__);
        }

        Assert::assertTrue("socket is not compatible", errorFlag->get(), __FILE__, __LINE__);

        // Test connect null
        errorFlag->set(false);
        try {
            _femaleSocket->_connect(nullptr);
        } catch (NullPointerException* ex) {
            errorFlag->set(true);
        } catch (SocketAlreadyConnectedException* ex) {
            // We shouldn't be here.
            Assert::fail("socket is already connected", __FILE__, __LINE__);
        }

        Assert::assertTrue("cannot connect socket that is null", errorFlag->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testConnect() {

        // Test connect male socket
        flag->set(false);
        errorFlag->set(false);
        try {
            _femaleSocket->_connect(maleSocket);
        } catch (SocketAlreadyConnectedException* ex) {
            errorFlag->set(true);
        }

        Assert::assertTrue("Socket is connected", flag->get(), __FILE__, __LINE__);
        Assert::assertFalse("No error", errorFlag->get(), __FILE__, __LINE__);

        // Test connect male socket when already connected
        flag->set(false);
        errorFlag->set(false);
        try {
            _femaleSocket->_connect(otherMaleSocket);
        } catch (SocketAlreadyConnectedException* ex) {
            errorFlag->set(true);
        }

        Assert::assertFalse("Socket was not connected again", flag->get(), __FILE__, __LINE__);
        Assert::assertTrue("Socket already connected error", errorFlag->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testDisconnect() /*throws SocketAlreadyConnectedException*/ {

        // Ensure the socket is connected before this test.
        if (!_femaleSocket->isConnected()) {
            _femaleSocket->_connect(maleSocket);
        }

        // Test disconnect male socket
        flag->set(false);
        _femaleSocket->_disconnect();

        Assert::assertTrue("Socket is disconnected", flag->get(), __FILE__, __LINE__);

        // Test connect male socket
        flag->set(false);
        errorFlag->set(false);
        _femaleSocket->_disconnect();

        Assert::assertFalse("Socket is not disconnected again", flag->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testSetParentForAllChildren() /*throws SocketAlreadyConnectedException */{
        Assert::assertFalse("femaleSocket is not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        if (! _femaleSocket->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        Assert::assertNull("malesocket->getParent() is null", (QObject*)maleSocket->getParent(), __FILE__, __LINE__);
        _femaleSocket->_connect(maleSocket);
        if (! _femaleSocket->setParentForAllChildren(new QList<QString>())) throw new RuntimeException();
        Assert::assertEquals("malesocket.getParent() is femaleSocket", (QObject*)_femaleSocket->bself(), (QObject*)maleSocket->getParent()->bself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testValidateName() {
        // Valid names
        Assert::assertTrue(_femaleSocket->validateName("Abc"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("abc"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("Abc123"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("A123bc"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("Abc___"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("Abc___fsdffs"), __FILE__, __LINE__);
        Assert::assertTrue(_femaleSocket->validateName("Abc3123__2341fsdf"), __FILE__, __LINE__);

        // Invalid names
        Assert::assertFalse(_femaleSocket->validateName("12Abc"), __FILE__, __LINE__);  // Starts with a digit
        Assert::assertFalse(_femaleSocket->validateName("_Abc"), __FILE__, __LINE__);   // Starts with an underscore
        Assert::assertFalse(_femaleSocket->validateName(" Abc"), __FILE__, __LINE__);   // Starts with a non letter
        Assert::assertFalse(_femaleSocket->validateName("A bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
        Assert::assertFalse(_femaleSocket->validateName("A{bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
        Assert::assertFalse(_femaleSocket->validateName("A+bc"), __FILE__, __LINE__);   // Has a character that's not letter, digit or underscore
    }

    /*private*/ bool FemaleSocketTestBase::setName_verifyException(QString newName, QString expectedExceptionMessage) {
        AtomicBoolean* hasThrown = new AtomicBoolean(false);
        try {
            _femaleSocket->setName(newName);
        } catch (IllegalArgumentException* ex) {
            hasThrown->set(true);
            Assert::assertTrue("Error message is correct", ex->getMessage()==(expectedExceptionMessage), __FILE__, __LINE__);
        }
        return hasThrown->get();
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testSetName() {
        // Both letters and digits is OK
        _femaleSocket->setName("X12");
        Assert::assertTrue("name matches", "X12" == (_femaleSocket->getName()), __FILE__, __LINE__);

        // Only letters is OK
        _femaleSocket->setName("Xyz");
        Assert::assertTrue("name matches", "Xyz" == (_femaleSocket->getName()), __FILE__, __LINE__);

        // Both letters and digits in random order is OK as long as the first
        // character is a letter
        _femaleSocket->setName("X1b2c3Y");
        Assert::assertTrue("name matches", "X1b2c3Y" == (_femaleSocket->getName()), __FILE__, __LINE__);

        // Underscore is also a valid letter
        _femaleSocket->setName("X1b2___c3Y");
        Assert::assertTrue("name matches", "X1b2___c3Y" == (_femaleSocket->getName()), __FILE__, __LINE__);

        // The name must start with a letter, not a digit
        Assert::assertTrue("exception is thrown", setName_verifyException("123", "the name is not valid: 123"), __FILE__, __LINE__);

        // The name must not contain any spaces
        Assert::assertTrue("exception is thrown", setName_verifyException(" A123", "the name is not valid:  A123"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A1 23", "the name is not valid: A1 23"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A123 ", "the name is not valid: A123 "), __FILE__, __LINE__);

        // The name must not contain any character that's not a letter nor a digit
        Assert::assertTrue("exception is thrown", setName_verifyException("A12!3", "the name is not valid: A12!3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A+123", "the name is not valid: A+123"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("=A123", "the name is not valid: =A123"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12*3", "the name is not valid: A12*3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A123/", "the name is not valid: A123/"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12(3", "the name is not valid: A12(3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12)3", "the name is not valid: A12)3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12[3", "the name is not valid: A12[3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12]3", "the name is not valid: A12]3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12{3", "the name is not valid: A12{3"), __FILE__, __LINE__);
        Assert::assertTrue("exception is thrown", setName_verifyException("A12}3", "the name is not valid: A12}3"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testDisposeWithoutChild() {
        _femaleSocket->dispose();
        Assert::assertFalse("socket not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testDisposeWithChild() /*throws SocketAlreadyConnectedException*/ {
        Assert::assertFalse("socket not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        _femaleSocket->_connect(maleSocket);
        Assert::assertTrue("socket is connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
        _femaleSocket->dispose();
        Assert::assertFalse("socket not connected", _femaleSocket->isConnected(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testMethodsThatAreNotSupported() {
        errorFlag->set(false);
        try {
            int mutableInt=0;
            _femaleSocket->printTree((PrintWriter*)nullptr, "", &mutableInt);
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            int mutableInt =0;
            _femaleSocket->printTree(QLocale(), (PrintWriter*)nullptr, "", /*new MutableInt(0)*/&mutableInt);
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            _femaleSocket->getCategory();
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            _femaleSocket->getChild(0);
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            _femaleSocket->getChildCount();
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            _femaleSocket->getUserName();
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);

        errorFlag->set(false);
        try {
            _femaleSocket->setUserName("aaa");
        } catch (UnsupportedOperationException* ex) {
            errorFlag->set(true);
        }
        Assert::assertTrue("method not supported", errorFlag->get(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testCategory() {
        // Test that the classes method getCategory() returns the same value as
        // the factory.
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = _femaleSocket->getConnectableClasses();

        //for (QHash<Category*, QList</*Class<? extends Base>*/QString>> entry : map.entrySet()) {
        QHashIterator<Category*, QList</*Class<? extends Base>*/QString>> entry(map);
        while(entry.hasNext()){
            entry.next();
            for (/*Class<? extends Base>*.QString*/QString clazz : entry.value()) {
                // The class SwingToolsTest does not have a swing configurator
             SwingConfiguratorInterface* iface0 = nullptr;
             try{ // temporarily bypass until these classes have all been implemented
                iface0 = SwingTools::getSwingConfiguratorForClass(clazz);
             }
             catch(ClassNotFoundException * ex)
             {
              log-> info(tr("bypassing: %1").arg(ex->getMessage()));
              continue;
             }
                QObject* oIface = (QObject*)iface0->sself();
                QString cn = oIface->metaObject()->className();
                AbstractAnalogExpressionSwing* iface = (AbstractAnalogExpressionSwing*)oIface;

                iface0->getConfigPanel(new JPanel(new FlowLayout()));
                QString sys = iface0->getAutoSystemName();
                Base* obj = iface0->createNewObject(sys, nullptr);
                QString cn2 = obj->bself()->metaObject()->className();
                Assert::assertEquals(QString("category is correct for ")+cn2, entry.key(), obj->getCategory(), __FILE__, __LINE__);
//                Assert::assertEquals("category is correct for "+obj.getShortDescription(), entry.getKey(), obj.getCategory());
            }
        }
    }

    //@Test
    /*public*/  void FemaleSocketTestBase::testSWISystemName() {   // SWI = SwingConfiguratorInterface
        QHash<Category*, QList</*Class<? extends Base>*/QString>> map = _femaleSocket->getConnectableClasses();

//        for (Map.Entry<Category, List</*Class<? extends Base>*/QString>> entry : map.entrySet()) {
        QHashIterator<Category*, QList</*Class<? extends Base>*/QString>> entry(map);
        while(entry.hasNext()){
            entry.next();
            for (/*Class<? extends Base>*/QString clazz : entry.value()) {
                // The class SwingToolsTest does not have a swing configurator
                SwingConfiguratorInterface* iface = SwingTools::getSwingConfiguratorForClass(clazz);
                log->debug(tr("check valid SystemName: %1 %2").arg(getManager()->getSubSystemNamePrefix(), iface->getExampleSystemName() ));
                Assert::assertEquals("example system name is correct for "+clazz,
                        Manager::NameValidity::VALID,
                        getManager()->validSystemNameFormat(iface->getExampleSystemName()), __FILE__, __LINE__);
                Assert::assertEquals("auto system name is correct for "+clazz,
                         Manager::NameValidity::VALID,
                        getManager()->validSystemNameFormat(iface->getAutoSystemName()), __FILE__, __LINE__);
            }
        }
    }


#if 0
    /*private*/ class IncompatibleMaleSocket : MaleSocket {

        //@Override
        /*public*/  void setEnabled(bool enable) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setEnabledFlag(bool enable) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isEnabled() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Base getObject() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setDebugConfig(DebugConfig config) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  DebugConfig getDebugConfig() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  DebugConfig createDebugConfig() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  String getSystemName() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  String getUserName() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setUserName(String s) throws NamedBean.BadUserNameException {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  String getComment() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setComment(String s) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  String getShortDescription(Locale locale) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  String getLongDescription(Locale locale) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  ConditionalNG getConditionalNG() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  LogixNG getLogixNG() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  LogixNG getRoot() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Base getParent() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void setParent(Base parent) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  bool setParentForAllChildren(List<String> errors) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  FemaleSocket getChild(int index) throws IllegalArgumentException, UnsupportedOperationException {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  int getChildCount() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  Category getCategory() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void dispose() {
            throw new UnsupportedOperationException("Not supported.");
        }
/*
        //@Override
        /*public*/  void registerListeners() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void unregisterListeners() {
            throw new UnsupportedOperationException("Not supported.");
        }
*/
        //@Override
        /*public*/  void printTree(PrintTreeSettings settings, PrintWriter writer, String indent, MutableInt lineNumber) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void printTree(PrintTreeSettings settings, Locale locale, PrintWriter writer, String indent, MutableInt lineNumber) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void printTree(PrintTreeSettings settings, Locale locale, PrintWriter writer, String indent, String currentIndent, MutableInt lineNumber) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  bool isActive() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(PropertyChangeListener listener) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(String propertyName, PropertyChangeListener listener) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  PropertyChangeListener[] getPropertyChangeListeners() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  PropertyChangeListener[] getPropertyChangeListeners(String propertyName) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void removePropertyChangeListener(PropertyChangeListener listener) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void removePropertyChangeListener(String propertyName, PropertyChangeListener listener) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  ErrorHandlingType getErrorHandlingType() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setErrorHandlingType(ErrorHandlingType errorHandlingType) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(PropertyChangeListener listener, String name, String listenerRef) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addPropertyChangeListener(String propertyName, PropertyChangeListener listener, String name, String listenerRef) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void updateListenerRef(PropertyChangeListener l, String newName) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void vetoableChange(PropertyChangeEvent evt) throws PropertyVetoException {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  String getListenerRef(PropertyChangeListener l) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  ArrayList<String> getListenerRefs() {
            throw new UnsupportedOperationException("Not supported");
        }

        /** {@inheritDoc} */
        //@Override
        /*public*/  void getListenerRefsIncludingChildren(List<String> list) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  int getNumPropertyChangeListeners() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  PropertyChangeListener[] getPropertyChangeListenersByReference(String name) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  BaseManager<? extends NamedBean> getManager() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void addLocalVariable(String name, SymbolTable.InitialValueType initialValueType, String initialValueData) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void addLocalVariable(SymbolTable.VariableData variableData) {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void clearLocalVariables() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  List<SymbolTable.VariableData> getLocalVariables() {
            throw new UnsupportedOperationException("Not supported.");
        }

        //@Override
        /*public*/  void registerListeners() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void unregisterListeners() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  Base getDeepCopy(Map<String, String> map, Map<String, String> map1) throws JmriException {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  Base deepCopyChildren(Base base, Map<String, String> map, Map<String, String> map1) throws JmriException {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool getListen() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setListen(bool listen) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void getUsageDetail(int level, NamedBean bean, List<jmri.NamedBeanUsageReport> report, NamedBean cdl) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void getUsageTree(int level, NamedBean bean, List<jmri.NamedBeanUsageReport> report, NamedBean cdl) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isLocked() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setLocked(bool locked) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool isSystem() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setSystem(bool system) {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  bool getCatchAbortExecution() {
            throw new UnsupportedOperationException("Not supported");
        }

        //@Override
        /*public*/  void setCatchAbortExecution(bool catchAbortExecution) {
            throw new UnsupportedOperationException("Not supported");
        }
    };
#endif
    /*private*/ /*final*/ /*static*/ Logger* FemaleSocketTestBase::log = LoggerFactory::getLogger("FemaleSocketTestBase");

