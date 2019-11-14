#include "doubleturnoutsignalheadtest.h"
#include "assert1.h"
#include "internalturnoutmanager.h"
#include "turnoutmanager.h"
#include "instancemanager.h"
#include "turnoutmanager.h"
#include "doubleturnoutsignalhead.h"
#include "sleeperthread.h"
#include "timer.h"

DoubleTurnoutSignalHeadTest::DoubleTurnoutSignalHeadTest(QObject* parent) : AbstractSignalHeadTestBase(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 * @author Balazs Racz Copyright (C) 2017
 */
// /*public*/ class DoubleTurnoutSignalHeadTest extends AbstractSignalHeadTestBase {


//@Test
/*public*/ void DoubleTurnoutSignalHeadTest::testCTor() {
    Turnout* it = ((TurnoutManager*)(InstanceManager::getDefault("TurnoutManager")))->provideTurnout("IT1");
    NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle", it);
    Turnout* it2 = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1"); // deliberately use same system name?
    NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle", it2);
    new DoubleTurnoutSignalHead("Test Head", green, red);
    //Assert::assertNotNull("exists",t);
}

void DoubleTurnoutSignalHeadTest::createHead() {
    mGreenTurnout = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT1");
    NamedBeanHandle<Turnout*>* green = new NamedBeanHandle<Turnout*>("green handle", mGreenTurnout);
    mRedTurnout = ((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"))->provideTurnout("IT2");
    NamedBeanHandle<Turnout*>* red = new NamedBeanHandle<Turnout*>("red handle", mRedTurnout);
    mHead = new DoubleTurnoutSignalHead("Test Head", green, red);
}

void DoubleTurnoutSignalHeadTest::waitForTimer()
{
 if (mHead->readUpdateTimer == nullptr) return;
 while (mHead->readUpdateTimer->isActive())
 {
  try
  {
         //Thread.sleep(60);
   SleeperThread::msleep(60);
   qApp->processEvents();
  } catch (InterruptedException e) {
   break;
  }
 }
 #if 0
 // Makes sure that the timer's callback is not still pending in the Swing execution
 // thread by scheduling an execution there and waiting for it.
 try
 {
     SwingUtilities.invokeAndWait(() -> {
     });
 } catch (InterruptedException e) {
 } catch (InvocationTargetException e) {
 //            e.printStackTrace();
 }
#endif
}


//@Test
/*public*/ void DoubleTurnoutSignalHeadTest::testSetAppearance() {
    createHead();

    mHead->setAppearance(SignalHead::RED);
    Assert::assertEquals(Turnout::THROWN, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::CLOSED, mGreenTurnout->getKnownState(), __FILE__, __LINE__);
    mHead->setAppearance(SignalHead::GREEN);
    Assert::assertEquals(Turnout::CLOSED, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::THROWN, mGreenTurnout->getKnownState(), __FILE__, __LINE__);
    mHead->setAppearance(SignalHead::YELLOW);
    Assert::assertEquals(Turnout::THROWN, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::THROWN, mGreenTurnout->getKnownState(), __FILE__, __LINE__);
    mHead->setAppearance(SignalHead::RED);
    Assert::assertEquals(Turnout::THROWN, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::CLOSED, mGreenTurnout->getKnownState(), __FILE__, __LINE__);
}

//@Test
/*public*/ void DoubleTurnoutSignalHeadTest::testNotify() {
    createHead();
    mHead->setAppearance(SignalHead::RED);
    mHead->addPropertyChangeListener(l);

    mHead->setAppearance(SignalHead::YELLOW);
    //JUnitUtil.waitFor( () -> { return l.getPropertyChanged(); } );
    JUnitUtil::waitFor(new WaitForChange(this), __FILE__, __LINE__ );
    Assert::assertEquals("called once",1,l->getCallCount(), __FILE__, __LINE__);

    waitForTimer();
    Assert::assertEquals("called once",1,l->getCallCount(), __FILE__, __LINE__);

    mHead->setAppearance(SignalHead::GREEN);
    //JUnitUtil.waitFor( () -> { return l.getPropertyChanged(); } );
    JUnitUtil::waitFor(new WaitForChange(this), __FILE__, __LINE__ );
    Assert::assertEquals("called twice",2,l->getCallCount(), __FILE__, __LINE__);

    waitForTimer();
    Assert::assertEquals("called twice",2,l->getCallCount(), __FILE__, __LINE__);
}

//@Test
/*public*/ void DoubleTurnoutSignalHeadTest::testReadOutput() {
    createHead();

    mHead->setAppearance(SignalHead::RED);
    mHead->addPropertyChangeListener(l);
    Assert::assertEquals(SignalHead::RED, mHead->getAppearance(), __FILE__, __LINE__);

    mRedTurnout->setCommandedState(Turnout::CLOSED);
    mGreenTurnout->setCommandedState(Turnout::THROWN);
    Assert::assertEquals(SignalHead::RED, mHead->getAppearance(), __FILE__, __LINE__);
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);
    Assert::assertNotNull((QObject*)mHead->readUpdateTimer, __FILE__, __LINE__); // Should be running.

    waitForTimer();
    //JUnitUtil.waitFor( () -> { return l.getPropertyChanged(); } );
    JUnitUtil::waitFor(new WaitForChange(this), __FILE__, __LINE__ );
    Assert::assertEquals(SignalHead::GREEN, mHead->getAppearance(), __FILE__, __LINE__);
    l->resetPropertyChanged();

    mRedTurnout->setCommandedState(Turnout::THROWN);
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);
    waitForTimer();
    //JUnitUtil.waitFor( () -> { return l.getPropertyChanged(); } );
    JUnitUtil::waitFor(new WaitForChange(this), __FILE__, __LINE__ );
    Assert::assertEquals(SignalHead::YELLOW, mHead->getAppearance(), __FILE__, __LINE__);
    Assert::assertEquals("called once",1,l->getCallCount(), __FILE__, __LINE__);

    mRedTurnout->setCommandedState(Turnout::CLOSED);
    mGreenTurnout->setCommandedState(Turnout::CLOSED);
    Assert::assertEquals("called once",1,l->getCallCount(), __FILE__, __LINE__);
    waitForTimer();
//        JUnitUtil.waitFor( () -> { return l.getPropertyChanged(); } );
    JUnitUtil::waitFor(new WaitForChange(this), __FILE__, __LINE__ );
}

//@Test
/*public*/ void DoubleTurnoutSignalHeadTest::testFlashingIgnoresTurnoutFeedback() {
    createHead();
    mHead->setAppearance(SignalHead::FLASHRED);
    mHead->addPropertyChangeListener(l);
    Assert::assertEquals(Turnout::THROWN, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::CLOSED, mGreenTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(SignalHead::FLASHRED, mHead->getAppearance(), __FILE__, __LINE__);
    // Should not be running, since all commands came from us.
    Assert::assertNull(mHead->readUpdateTimer, __FILE__, __LINE__);
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);

    // Wait for the flash
    try {
        //Thread.sleep(1000);
     SleeperThread::msleep(1000);
    } catch (InterruptedException e) {
    }
    Assert::assertEquals(SignalHead::FLASHRED, mHead->getAppearance(), __FILE__, __LINE__); // hasn't changed
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);

    Assert::assertEquals(Turnout::CLOSED, mRedTurnout->getKnownState(), __FILE__, __LINE__);
    Assert::assertEquals(Turnout::CLOSED, mGreenTurnout->getKnownState(), __FILE__, __LINE__);

    mGreenTurnout->setCommandedState(Turnout::THROWN);
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);
    Assert::assertNotNull(mHead->readUpdateTimer, __FILE__, __LINE__); // now it's started
    waitForTimer();
    Assert::assertEquals("not called",0,l->getCallCount(), __FILE__, __LINE__);
    Assert::assertEquals(SignalHead::FLASHRED, mHead->getAppearance(), __FILE__, __LINE__); // hasn't changed
}

//@Override
/*public*/ SignalHead* DoubleTurnoutSignalHeadTest::getHeadToTest() {
    createHead();
    return mHead;
}

// The minimal setup for log4J
//@Before
/*public*/ void DoubleTurnoutSignalHeadTest::setUp() {
    JUnitUtil::setUp();
    JUnitUtil::initInternalTurnoutManager();
    l = new PropertyChangeListenerScaffold();
}

//@After
/*public*/ void DoubleTurnoutSignalHeadTest::tearDown() {
    JUnitUtil::tearDown();
}
