#include "abstractreportermgrtestbase.h"
#include "assert1.h"
#include "reporter.h"
#include "proxymanager.h"
#include "junitappender.h"
#include "proxyreportermanager.h"

AbstractReporterMgrTestBase::AbstractReporterMgrTestBase()
{

}

/**
 * Abstract Base Class for ReporterManager tests in specific jmrix packages. This
 * is not itself a test class, e.g. should not be added to a suite. Instead,
 * this forms the base for test classes, including providing some common tests
 *
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests
 *
 * @author	Bob Jacobsen 2003, 2006, 2008
 * @author      Paul Bender Copyright (C) 2016
 */
///*public*/ abstract class AbstractReporterMgrTestBase extends AbstractProvidingManagerTestBase<ReporterManager, Reporter> {


    // implementing classes must provide these abstract members:
    //abstract /*public*/ void setUp();    	// load l with actual object; create scaffolds as needed, tag @Before

    //abstract /*public*/ String getSystemName(String i);

    /*static*/ /*protected*/ bool AbstractReporterMgrTestBase::listenerResult = false;

    //protected class Listen implements PropertyChangeListener {

        //@Override
        /*public*/ void ListenO6::propertyChange(PropertyChangeEvent* e) {
            base->listenerResult = true;
        }
    //}

    // start of common tests
    // test creation - real work is in the setup() routine
    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testCreate() {
        Assert::assertNotNull(l, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testDispose() {
        l->dispose();  // all we're really doing here is making sure the method exists
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testProvideName() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provide("" + getNameToTest1());
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterProvideReporter() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        t->setUserName("Fred");
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", t == ((ProxyReporterManager*)l)->getByUserName("Fred"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);

        // Check that "providing" an already-created Reporter* returns the same object.
        Reporter* t2 = ((ProxyReporterManager*)l)->provideReporter(t->getSystemName());
        Assert::assertTrue("provided same object ", t == t2, __FILE__, __LINE__);
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void AbstractReporterMgrTestBase::testProvideFailure() {
        try {
            ((ProxyReporterManager*)l)->provideReporter("");
        } catch (IllegalArgumentException ex) {
          JUnitAppender::assertErrorMessage("Invalid system name for Reporter: System name must start with \"" + ((ProxyReporterManager*)l)->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
          throw ex;
        }
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetBySystemName() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        t->setUserName("Fred");

        // Try a successful one
        t = ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1()));
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        // Try a nonexistant one. Should return null
        if (maxN()<2) return;
        t = ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest2()));
        Assert::assertTrue("get nonexistant object ", t == nullptr, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetByUserName() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        t->setUserName("Fred");

        // Try a successful one
        t = ((ProxyReporterManager*)l)->getByUserName("Fred");
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        // Try a nonexistant one. Should return null
        t = ((ProxyReporterManager*)l)->getBySystemName("Barney");
        Assert::assertTrue("get nonexistant object ", t == nullptr, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetByDisplayName() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        t->setUserName("Fred");

        // Try a successful one
        t = ((ProxyReporterManager*)l)->getByDisplayName(getSystemName(getNameToTest1()));
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        Reporter* t2 = ((ProxyReporterManager*)l)->getByDisplayName("Fred");
        Assert::assertTrue("get retrieved existing object ", t2 == t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterProvideByNumber() {
        // Create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("1");
        Assert::assertNotNull("provide by number", t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testDefaultSystemName() {
        // create
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testSingleObject() {
        // test that you always get the same representation
        Reporter* t1 = ((ProxyReporterManager*)l)->newReporter(getSystemName(getNameToTest1()), "mine");
        Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("same by user ", t1 == ((ProxyReporterManager*)l)->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("same by system ", t1 == ((ProxyReporterManager*)l)->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);

        Reporter* t2 = ((ProxyReporterManager*)l)->newReporter(getSystemName(getNameToTest1()), "mine");
        Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
        // check
        Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testMisses() {
        // try to get nonexistant Reporters
        Assert::assertTrue(nullptr == ((ProxyReporterManager*)l)->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == ((ProxyReporterManager*)l)->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testUpperLower() {
        Reporter* t = ((ProxyReporterManager*)l)->provideReporter("" + getNameToTest1());
        QString name = t->getSystemName();
        Assert::assertNull(((ProxyReporterManager*)l)->getReporter(name.toLower()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testRename() {
        // get reporter
        Reporter* t1 = ((ProxyReporterManager*)l)->newReporter(getSystemName(getNameToTest1()), "before");
        Assert::assertNotNull("t1 real object ", t1, __FILE__, __LINE__);
        t1->setUserName("after");
        Reporter* t2 = ((ProxyReporterManager*)l)->getByUserName("after");
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertEquals("no old object", nullptr, ((ProxyReporterManager*)l)->getByUserName("before"), __FILE__, __LINE__);
    }

    /**
     * Number of Reporter* to test. Made a separate method so it can be overridden
     * in subclasses that do or don't support various numbers
     */
    /*protected*/ QString AbstractReporterMgrTestBase::getNameToTest1() {
        return "1";
    }

    /*protected*/ QString AbstractReporterMgrTestBase::getNameToTest2() {
        return "2";
    }

