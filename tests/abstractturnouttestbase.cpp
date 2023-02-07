#include "abstractturnouttestbase.h"
#include "assert1.h"
#include "instancemanager.h"
#include "abstractturnout.h"
#include "assume.h"
#include "junitutil.h"

AbstractTurnoutTestBase::AbstractTurnoutTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Abstract base class for Turnout tests in specific jmrix.* packages
 *
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests.
 *
 * @author	Bob Jacobsen
 */
// /*public*/ abstract class AbstractTurnoutTestBase {

    // implementing classes must provide these abstract members:
    //@Before
    //abstract /*public*/ void setUp();    	// load t with actual object; create scaffolds as needed

    /**
     * @return number of listeners registered with the TrafficController by the object under test
     */
    //abstract /*public*/ int numListeners();

    //abstract /*public*/ void checkThrownMsgSent() throw (InterruptedException);

    //abstract /*public*/ void checkClosedMsgSent() throw (InterruptedException);


    /*static*/ /*protected*/ bool AbstractTurnoutTestBase::listenerResult = false;
    /*static*/ /*protected*/ int AbstractTurnoutTestBase::listenStatus = Turnout::UNKNOWN;

//    /*public*/ class Listen implements PropertyChangeListener {

//        @Override
//        /*public*/ void propertyChange(java.beans.PropertyChangeEvent e) {
//            listenerResult = true;
//            if (e.getPropertyName().equals("KnownState")) {
//                listenStatus = (Integer) e.getNewValue();
//            }
//        }
//    }

    // start of common tests
    // test creation - real work is in the setup() routine
    //@Test
    /*public*/ void AbstractTurnoutTestBase::testCreate() {
        // initial commanded state when created must be UNKNOWN
        Assert::assertEquals("initial commanded state 1", Turnout::UNKNOWN, t->getCommandedState(), __FILE__, __LINE__);
        // initial known state when created must be UNKNOWN
        Assert::assertEquals("initial known state", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("initial commanded state 2", Turnout::UNKNOWN, t->getState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testAddListener() {
        ListenO1* l;
        t->addPropertyChangeListener(l= new ListenO1(this));
        connect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), l, SLOT(propertyChange(PropertyChangeEvent*)));
        listenerResult = false;
        t->setUserName("user id");
        Assert::assertTrue("listener invoked by setUserName", listenerResult, __FILE__, __LINE__);
        listenerResult = false;
        t->setCommandedState(Turnout::CLOSED);
        Assert::assertTrue("listener invoked by setCommandedState", listenerResult, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testRemoveListener() {
        ListenO1* ln = new ListenO1(this);
        t->addPropertyChangeListener(ln);
        connect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), ln, SLOT(propertyChange(PropertyChangeEvent*)));
        t->removePropertyChangeListener(ln);
        disconnect(t, SIGNAL(propertyChange(PropertyChangeEvent*)), ln, SLOT(propertyChange(PropertyChangeEvent*)));
        listenerResult = false;
        t->setUserName("user id");
        Assert::assertFalse("listener should not have heard message after removeListener",
                listenerResult, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testDispose() {
        t->setCommandedState(Turnout::CLOSED);  	// in case registration with TrafficController is deferred to after first use
        t->dispose();
        Assert::assertEquals("controller listeners remaining", 0, numListeners(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testCommandClosed() /*throw (InterruptedException)*/ {
        t->setCommandedState(Turnout::CLOSED);
        // check
        Assert::assertEquals("commanded state 1", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        ((AbstractTurnout*)t)->setKnownStateToCommanded();
        Assert::assertEquals("commanded state 2", Turnout::CLOSED, t->getState(), __FILE__, __LINE__);
        Assert::assertEquals("commanded state 3", "Closed", t->describeState(t->getState()), __FILE__, __LINE__);
        checkClosedMsgSent();
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testCommandThrown() /*throw (InterruptedException)*/ {
        t->setCommandedState(Turnout::THROWN);
        // check
        Assert::assertEquals("commanded state 1", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        ((AbstractTurnout*)t)->setKnownStateToCommanded();
        Assert::assertEquals("commanded state 2", Turnout::THROWN, t->getState(), __FILE__, __LINE__);
        Assert::assertEquals("commanded state 3", "Thrown", t->describeState(t->getState()), __FILE__, __LINE__);
        checkThrownMsgSent();
    }


    //@Test
    /*public*/ void AbstractTurnoutTestBase::testRequestUpdate() /*throw (JmriException)*/ {
        TestSensor* s1 = new TestSensor("IS1", "username1", this);
        TestSensor* s2 = new TestSensor("IS2", "username2",this);
        InstanceManager::sensorManagerInstance()->Register(s1);
        InstanceManager::sensorManagerInstance()->Register(s2);

        t->provideFirstFeedbackSensor("IS1");
        t->setFeedbackMode(Turnout::ONESENSOR);

        t->requestUpdateFromLayout();
        Assert::assertTrue("update requested, one sensor", s1->getRequest(), __FILE__, __LINE__);
        s1->resetRequest();

        t->provideSecondFeedbackSensor("IS2");
        t->setFeedbackMode(Turnout::TWOSENSOR);

        t->requestUpdateFromLayout();
        Assert::assertTrue("update requested, two sensor s1", s1->getRequest(), __FILE__, __LINE__);
        Assert::assertTrue("update requested, two sensor s2", s2->getRequest(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testGetAndSetInverted(){
        Assume::assumeTrue(t->canInvert());  // skip test if can't invert.
        Assert::assertFalse("Default Inverted State", t->getInverted(), __FILE__, __LINE__);
        t->setInverted(true);
        Assert::assertTrue("set Inverted", t->getInverted(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testInvertedCommandClosed() /*throw (InterruptedException)*/ {
        Assume::assumeTrue(t->canInvert());  // skip test if can't invert.
        t->setInverted(true);
        t->setCommandedState(Turnout::CLOSED);
        // check
        Assert::assertEquals("commanded state 1", Turnout::CLOSED, t->getCommandedState(), __FILE__, __LINE__);
        ((AbstractTurnout)t).setKnownStateToCommanded();
        Assert::assertEquals("commanded state 2", Turnout::CLOSED, t->getState(), __FILE__, __LINE__);
        Assert::assertEquals("commanded state 3", "Closed", t->describeState(t->getState()), __FILE__, __LINE__);
        checkThrownMsgSent();
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testInvertedCommandThrown() /*throw (InterruptedException)*/ {
        Assume::assumeTrue(t->canInvert());  // skip test if can't invert.
        t->setInverted(true);
        t->setCommandedState(Turnout::THROWN);
        // check
        Assert::assertEquals("commanded state 1", Turnout::THROWN, t->getCommandedState(), __FILE__, __LINE__);
        ((AbstractTurnout)t).setKnownStateToCommanded();
        Assert::assertEquals("commanded state 2", Turnout::THROWN, t->getState(), __FILE__, __LINE__);
        Assert::assertEquals("commanded state 3", "Thrown", t->describeState(t->getState()), __FILE__, __LINE__);
        checkClosedMsgSent();
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testProvideFirstFeedbackSensor() /*throw (JmriException)*/ {
        t->provideFirstFeedbackSensor("IS1");
        Assert::assertNotNull("first feedback sensor", t->getFirstSensor(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testProvideSecondFeedbackSensor() /*throw (JmriException)*/ {
        t->provideSecondFeedbackSensor("IS2");
        Assert::assertNotNull("first feedback sensor", t->getSecondSensor(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testOneSensorFeedback() /*throw (JmriException)*/ {
        Sensor* s1 = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("IS1");
        t->setFeedbackMode(Turnout::ONESENSOR);
        listenStatus = Turnout::UNKNOWN;
        t->addPropertyChangeListener(new ListenO1(this));
        t->provideFirstFeedbackSensor("IS1");
        s1->setKnownState(Sensor::INACTIVE);
        Assert::assertEquals("known state for ONESENSOR feedback Inactive", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);
        Assert::assertEquals("listener notified of change for ONESENSOR feedback", Turnout::CLOSED,listenStatus, __FILE__, __LINE__);
        s1->setKnownState(Sensor::ACTIVE);
        Assert::assertEquals("listener notified of change for ONESENSOR feedback", Turnout::THROWN,listenStatus, __FILE__, __LINE__);
        Assert::assertEquals("known state for ONESENSOR feedback active", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testTwoSensorFeedback() /*throw (JmriException)*/ {
        Sensor* s1 = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("IS1");
        Sensor* s2 = ((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("IS2");
        t->provideFirstFeedbackSensor("IS1");
        t->provideSecondFeedbackSensor("IS2");
        t->setFeedbackMode(Turnout::TWOSENSOR);
        Assert::assertEquals("known state for TWOSENSOR feedback (UNKNOWN,UNKNOWN)", Turnout::UNKNOWN, t->getKnownState(), __FILE__, __LINE__);

        listenStatus = Turnout::UNKNOWN;
        t->addPropertyChangeListener(new ListenO1(this));

        s1->setKnownState(Sensor::ACTIVE);
        s2->setKnownState(Sensor::INACTIVE);

//        JUnitUtil.waitFor( () -> {
//            return t->getKnownState() != Turnout::UNKNOWN;
//        });
        JUnitUtil::waitFor(0);
        t->getKnownState() != Turnout::UNKNOWN;

        Assert::assertEquals("state changed by TWOSENSOR feedback (Active, Inactive)", Turnout::THROWN, t->getKnownState(), __FILE__, __LINE__);

        Assert::assertEquals("listener notified of change for TWOSENSOR feedback", Turnout::THROWN,listenStatus, __FILE__, __LINE__);

        s1->setKnownState(Sensor::INACTIVE);
        s2->setKnownState(Sensor::INACTIVE);
        Assert::assertEquals("known state for TWOSENSOR feedback (Inactive, Inactive)", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);

        s1->setKnownState(Sensor::INACTIVE);
        s2->setKnownState(Sensor::ACTIVE);
        Assert::assertEquals("state changed by TWOSENSOR feedback (Inactive, Active)", Turnout::CLOSED, t->getKnownState(), __FILE__, __LINE__);

        Assert::assertEquals("listener notified of change for TWOSENSOR feedback ", Turnout::CLOSED,listenStatus, __FILE__, __LINE__);

        s1->setKnownState(Sensor::ACTIVE);
        s2->setKnownState(Sensor::ACTIVE);
        Assert::assertEquals("state changed by TWOSENSOR feedback (Active, Active)", Turnout::INCONSISTENT, t->getKnownState(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testDirectFeedback() /*throw (Exception)*/ {

        // DIRECT mode is implemented in the AbstractTurnout class, so
     // it is possible on all systems.
     if(t->getFeedbackMode() != Turnout::DIRECT){
         t->setFeedbackMode(Turnout::DIRECT);
     }
         Assert::assertEquals(Turnout::DIRECT, t->getFeedbackMode(), __FILE__, __LINE__);

     listenStatus = Turnout::UNKNOWN;
     t->addPropertyChangeListener(new ListenO1(this));

     // Check that state changes appropriately
     t->setCommandedState(Turnout::THROWN);
     checkThrownMsgSent();
     Assert::assertEquals(t->getState(), Turnout::THROWN, __FILE__, __LINE__);
     Assert::assertEquals("listener notified of change for DIRECT feedback", Turnout::THROWN,listenStatus,__FILE__, __LINE__);

     t->setCommandedState(Turnout::CLOSED);
     checkClosedMsgSent();
     Assert::assertEquals(t->getState(), Turnout::CLOSED, __FILE__, __LINE__);
     Assert::assertEquals("listener notified of change for DIRECT feedback", Turnout::CLOSED,listenStatus,__FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractTurnoutTestBase::testGetBeanType(){
         Assert::assertEquals("bean type", t->getBeanType(), ("Turnout"),__FILE__, __LINE__);
    }
