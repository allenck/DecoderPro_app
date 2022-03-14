#include "abstractreportermgrtestbase.h"
#include "assert1.h"
#include "reporter.h"
#include "proxymanager.h"
#include "junitappender.h"
#include "proxyreportermanager.h"
#include "abstractreportermanager.h"

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
        Assert::assertNotNull(_manager->mself(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testDispose() {
        _manager->dispose();  // all we're really doing here is making sure the method exists
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testProvideName() {
        // Create
        Reporter* t = (Reporter*)((ReporterManager*)_manager->mself())->provide("" + getNameToTest1());
        Assert::assertTrue("real object returned ", t->self() != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", ((NamedBean*)t->self())->equals (((ProxyReporterManager*)_manager->mself())->AbstractProxyManager::getBySystemName(getSystemName(getNameToTest1()))->self()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterProvideReporter() {
        // Create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        ((NamedBean*)t->self())->setUserName("Fred");
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", ((NamedBean*)t->self()) == ((AbstractReporterManager*)_manager->mself())->getByUserName("Fred"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", ((NamedBean*)t->self()) == ((AbstractReporterManager*)_manager->mself())->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);

        // Check that "providing" an already-created Reporter* returns the same object.
        Reporter* t2 = ((AbstractReporterManager*)_manager->mself())->provideReporter(((NamedBean*)t->self())->getSystemName());
        Assert::assertTrue("provided same object ", t == t2, __FILE__, __LINE__);
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void AbstractReporterMgrTestBase::testProvideFailure() {
        try {
            ((AbstractReporterManager*)_manager->mself())->provideReporter("");
        } catch (IllegalArgumentException* ex) {
          JUnitAppender::assertErrorMessage("Invalid system name for Reporter: System name must start with \"" + ((AbstractReporterManager*)_manager->mself())->AbstractManager::getSystemNamePrefix() + "\".", __FILE__, __LINE__);
//          throw ex;
        }
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetBySystemName() {
        // Create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        ((NamedBean*)t->self())->setUserName("Fred");

        // Try a successful one
        t = (Reporter*)((AbstractReporterManager*)_manager->mself())->getBySystemName(getSystemName(getNameToTest1()));
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        // Try a nonexistant one. Should return null
        if (maxN()<2) return;
        t = (Reporter*)((AbstractReporterManager*)_manager->mself())->getBySystemName(getSystemName(getNameToTest2()));
        Assert::assertTrue("get nonexistant object ", t == nullptr, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetByUserName() {
        // Create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        ((NamedBean*)t->self())->setUserName("Fred");

        // Try a successful one
        t = (Reporter*)((AbstractReporterManager*)_manager->mself())->getByUserName("Fred");
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        // Try a nonexistant one. Should return null
        t = (Reporter*)((AbstractReporterManager*)_manager->mself())->getBySystemName("Barney");
        Assert::assertTrue("get nonexistant object ", t == nullptr, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterGetByDisplayName() {
        // Create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        ((NamedBean*)t->self())->setUserName("Fred");

        // Try a successful one
        t = ((AbstractReporterManager*)_manager->mself())->getByDisplayName(getSystemName(getNameToTest1()));
        Assert::assertTrue("get retrieved existing object ", t != nullptr, __FILE__, __LINE__);

        Reporter* t2 = ((AbstractReporterManager*)_manager->mself())->getByDisplayName("Fred");
        Assert::assertTrue("get retrieved existing object ", t2 == t, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testReporterProvideByNumber() {
        // Create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("1");
        Assert::assertNotNull("provide by number", t->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testDefaultSystemName() {
        // create
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", ((NamedBean*)t->self()) == ((AbstractReporterManager*)_manager->mself())->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testSingleObject() {
        // test that you always get the same representation
        Reporter* t1 = ((ProxyReporterManager*)_manager->mself())->newReporter(getSystemName(getNameToTest1()), "mine");
        Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("same by user ", ((NamedBean*)t1->self()) == ((AbstractReporterManager*)_manager->mself())->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("same by system ", ((NamedBean*)t1->self()) == ((AbstractReporterManager*)_manager->mself())->getBySystemName(getSystemName(getNameToTest1())), __FILE__, __LINE__);

        Reporter* t2 = ((AbstractReporterManager*)_manager->mself())->newReporter(getSystemName(getNameToTest1()), "mine");
        Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
        // check
        Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testMisses() {
        // try to get nonexistant Reporters
        Assert::assertTrue(nullptr == ((AbstractReporterManager*)_manager->mself())->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == ((AbstractReporterManager*)_manager->mself())->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testUpperLower() {
        Reporter* t = ((AbstractReporterManager*)_manager->mself())->provideReporter("" + getNameToTest1());
        QString name = ((NamedBean*)t->self())->getSystemName();
        Assert::assertNull(((AbstractReporterManager*)_manager->mself())->getReporter(name.toLower())->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractReporterMgrTestBase::testRename() {
        // get reporter
        Reporter* t1 = ((ProxyReporterManager*)_manager->mself())->newReporter(getSystemName(getNameToTest1()), "before");
        Assert::assertNotNull("t1 real object ", t1->self(), __FILE__, __LINE__);
        ((NamedBean*)t1->self())->setUserName("after");
        Reporter* t2 =(Reporter*) ((AbstractReporterManager*)_manager->mself())->getByUserName("after");
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertEquals("no old object", nullptr, ((AbstractReporterManager*)_manager->mself())->getByUserName("before")->self(), __FILE__, __LINE__);
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

