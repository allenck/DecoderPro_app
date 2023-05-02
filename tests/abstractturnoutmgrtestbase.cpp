#include "abstractturnoutmgrtestbase.h"
#include "abstractturnout.h"
#include "assert1.h"
#include "assume.h"
#include "junitappender.h"
#include "junitutil.h"
#include "systemconnectionmemo.h"
#include "turnout.h"
#include "proxyturnoutmanager.h"
#include "jmriexception.h"

AbstractTurnoutMgrTestBase::AbstractTurnoutMgrTestBase(QObject *parent) : AbstractProvidingTurnoutManagerTestBase(parent)
{
 //this->_manager = (ProxyTurnoutManager*)AbstractProvidingTurnoutManagerTestBase::_manager->mself();
}
/**
 * Base for TurnoutManager tests in specific jmrix.* packages
 * <p>
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests.
 *
 * @author Bob Jacobsen
 */
///*public*/ abstract class AbstractTurnoutMgrTestBase extends AbstractProvidingManagerTestBase<TurnoutManager, Turnout> {

    // implementing classes must implement to convert integer (count) to a system name
    //abstract /*public*/ QString getSystemName(int i);

    /**
     * Overload to load l with actual object; create scaffolds as needed
     */
    //@Before
    //abstract /*public*/ void setUp();

    /*static*/ /*protected*/ bool AbstractTurnoutMgrTestBase::listenerResult = false;

//    /*protected*/ class Listen implements PropertyChangeListener {

//        @Override
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            listenerResult = true;
//        }
//    }

    // start of common tests
    // test creation - real work is in the setup() routine
    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testCreate() {
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testDispose() {
        if (_manager != nullptr) {
            _manager->dispose();  // all we're really doing here is making sure the method exists
        }
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void AbstractTurnoutMgrTestBase::testProvideFailure() {
        try {
            l->provideTurnout("");
        } catch (IllegalArgumentException* ex) {
          JUnitAppender::assertErrorMessage("Invalid system name for Turnout: System name must start with \"" + _manager->getSystemNamePrefix() + "\".", __FILE__, __LINE__);
//          throw ex;
        }
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testTurnoutPutGet() {
        // create
        Turnout* t = l->newTurnout(getSystemName(getNumToTest1()), "mine");
        // check
        Assert::assertNotNull("real object returned ", t, __FILE__, __LINE__);
        Assert::assertEquals("user name correct ", t, l->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertEquals("system name correct ", t, l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testProvideName() {
        // create
        Turnout* t = l->provide("" + QString::number(getNumToTest1()));
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testProvideWithoutWithPrefix() /*throws IllegalArgumentException */{
        Turnout* psa = l->provide(""+getASystemNameWithNoPrefix());
        Turnout* psb = l->provide(l->getSystemPrefix()+"T"+getASystemNameWithNoPrefix());
        Assert::assertTrue("Provide Without then With Prefix", psa == psb, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testProvideWithWithoutPrefix() /*throws IllegalArgumentException*/ {
        Turnout* psa = l->provide(l->getSystemNamePrefix()+getASystemNameWithNoPrefix());
        Turnout* psb = l->provide(""+getASystemNameWithNoPrefix());
        Assert::assertTrue("Provide With then Without Prefix", psa == psb, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testProvideFailWithPrefix() /*throws IllegalArgumentException*/ {

//        Assert.assertThrows(IllegalArgumentException.class, () -> l.provide(l.getSystemPrefix()+"T"));
//        JUnitAppender.assertErrorMessageStartsWith("Invalid system name for Turnout: ");
     bool thrown = false;
     try {
      l->provide(l->getSystemPrefix()+"T");
     }
     catch (IllegalArgumentException* e)
     {
      thrown = true;
     }
     JUnitAppender::assertErrorMessageStartsWith("Invalid system name for Turnout: ", __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testDefaultSystemName() {
        // create
        Turnout* t = l->provideTurnout("" + getNumToTest1());
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", t == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testSingleObject() {
        // test that you always get the same representation
        Turnout* t1 = l->newTurnout(getSystemName(getNumToTest1()), "mine");
        Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("same by user ", t1 == l->getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("same by system ", t1 == l->getBySystemName(getSystemName(getNumToTest1())), __FILE__, __LINE__);

        Turnout* t2 = l->newTurnout(getSystemName(getNumToTest1()), "mine");
        Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
        // check
        Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testMisses() {
        // try to get nonexistant turnouts
        Assert::assertTrue(nullptr == l->getByUserName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == l->getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testUpperLower() {
        Turnout* t = l->provideTurnout("" + getNumToTest2());

        Assert::assertNull(l->getTurnout(t->getSystemName().toLower()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testRename() {
        // get turnout
        Turnout* t1 = l->newTurnout(getSystemName(getNumToTest1()), "before");
        Assert::assertNotNull("t1 real object ", t1, __FILE__, __LINE__);
        t1->setUserName("after");
        Turnout* t2 = (AbstractTurnout*)l->getByUserName("after")->self();
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertEquals("no old object", nullptr, l->getByUserName("before")->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testThrownText(){
         Assert::assertEquals("thrown text",tr("Thrown"),l->getThrownText(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testClosedText(){
         Assert::assertEquals("closed text",tr("Closed"),l->getClosedText(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testSetAndGetOutputInterval() {
        Assert::assertEquals("default outputInterval", 250, l->getOutputInterval(), __FILE__, __LINE__);
        l->getMemo()->setOutputInterval(21);
        Assert::assertEquals("new outputInterval in memo", 21, l->getMemo()->getOutputInterval(), __FILE__, __LINE__); // set & get in memo
        Assert::assertEquals("new outputInterval via manager", 21, l->getOutputInterval(), __FILE__, __LINE__);// get via turnoutManager
        l->setOutputInterval(50);
        Assert::assertEquals("new outputInterval from manager", 50, l->getOutputInterval(), __FILE__, __LINE__); // interval stored in AbstractTurnoutManager
        Assert::assertEquals("new outputInterval from manager", 50, l->getMemo()->getOutputInterval(), __FILE__, __LINE__);// get from memo
    }

    //@Disabled("Turnout managers don't support auto system names")
    //@Test
    //@Override
    /*public*/ void AbstractTurnoutMgrTestBase::testAutoSystemNames() {
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testGetEntryToolTip(){
        Assert::assertNotNull("getEntryToolTip not null", l->getEntryToolTip(), __FILE__, __LINE__);
        Assert::assertTrue("Entry ToolTip Contains text",(l->getEntryToolTip().length()>5), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testGetNextValidAddress() /*throws JmriException*/ {

        if (!l->allowMultipleAdditions(l->getSystemNamePrefix())){
            return;
        }

        Assert::assertNotNull("next valid before OK", l->getNextValidAddress(getASystemNameWithNoPrefix(), l->getSystemPrefix(),false), __FILE__, __LINE__);

        Assert::assertNotEquals("requesting ignore existing does not return same",
                l->getNextValidAddress(getASystemNameWithNoPrefix(), l->getSystemPrefix(),true),
                l->getNextValidAddress(getASystemNameWithNoPrefix(), l->getSystemPrefix(),false), __FILE__, __LINE__);

        Turnout* t =  l->provideTurnout(getASystemNameWithNoPrefix());
        Assert::assertNotNull("exists", t, __FILE__, __LINE__);

        QString nextValidAddr = l->getNextValidAddress(getASystemNameWithNoPrefix(), l->getSystemPrefix(),false);
        Turnout* nextValid =  l->provideTurnout(nextValidAddr);
        Assert::assertNotNull("exists", nextValid, __FILE__, __LINE__);
        Assert::assertNotEquals(nextValid, t, __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void AbstractTurnoutMgrTestBase::testIncorrectGetNextValidAddress() {
        if (!l->allowMultipleAdditions(l->getSystemNamePrefix())){
            return;
        }
//        bool contains = Assert::assertThrows(JmriException.class,
//            ()->{
        bool contains = false;
        try{
                l->getNextValidAddress("NOTANINCREMENTABLEADDRESS", l->getSystemPrefix(),false);
//            }).getMessage().contains("NOTANINCREMENTABLEADDRESS");
        }
        catch(JmriException* e)
        {
         contains = e->getMessage().contains("NOTANINCREMENTABLEADDRESS");
        }
        Assert::assertTrue("Exception contained incorrect address", contains, __FILE__, __LINE__);
    }

    /**
     * Number of turnout to test. Made a separate method so it can be overridden
     * in subclasses that do or don't support various numbers
     */
    /*protected*/ int AbstractTurnoutMgrTestBase::getNumToTest1() {
        return 9;
    }

    /*protected*/ int AbstractTurnoutMgrTestBase::getNumToTest2() {
        return 7;
    }
