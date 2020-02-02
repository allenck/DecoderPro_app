#include "consisttoolframetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "consisttoolframe.h"
#include "temporaryfolder.h"
#include "nullprofile.h"
#include "profile.h"
#include "instancemanager.h"
#include "consistpreferencesmanager.h"
#include "consisttoolscaffold.h"
#include "dcclocoaddress.h"
#include "roster.h"
#include "rosterentry.h"
#include "throttleoperator.h"
#include "RosterTest/rostertestutil.h"
#include "jemmyutil.h"
#include "sleeperthread.h"

ConsistToolFrameTest::ConsistToolFrameTest(QObject *parent) : QObject(parent)
{
  folder = new TemporaryFolder();
}
/**
 * Test simple functioning of ConsistToolFrame
 *
 * @author	Paul Bender Copyright (C) 2015,2016
 */
// /*public*/ class ConsistToolFrameTest {


//@Test
/*public*/ void ConsistToolFrameTest::testCtor() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    Assert::assertNotNull("exists", frame, __FILE__,  __LINE__);
    JUnitUtil::dispose(frame);
}

//@Test
/*public*/ void ConsistToolFrameTest::testCtorWithCSpossible() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    // overwrite the default consist manager set in setUp for this test
    // so that we can check initilization with CSConsists possible.
    InstanceManager::setDefault("ConsistManager", new TestConsistManagerO1());
//    {
//        @Override
//        /*public*/ boolean isCommandStationConsistPossible() {
//            return true;
//        }
//    });

    ConsistToolFrame* frame = new ConsistToolFrame();
    Assert::assertNotNull("exists", frame, __FILE__,  __LINE__);
    JUnitUtil::dispose(frame);
}

//@Test
/*public*/ void ConsistToolFrameTest::testAdd() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    //Assert::assertTrue("Consists List empty",((ConsistManager*)InstanceManager::getDefault("ConsistManager"))->getConsistList().isEmpty());
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    // set up a consist.
    cs->setConsistAddressValue("1");
    cs->setLocoAddressValue("12");
    cs->pushAddButton();
    // check to see if a consist was added
    DccLocoAddress* conAddr = new DccLocoAddress(1, false);
    //AbstractConsistManager* mgr = qobject_cast<AbstractConsistManager*>(InstanceManager::getDefault("ConsistManager"));
    AbstractConsistManager* mgr = qobject_cast<AbstractConsistManager*>(frame->consistManager->self());
    Assert::assertFalse("Consists has at least one entry", mgr->getConsistList()->isEmpty(), __FILE__,  __LINE__);
    Assert::assertTrue("Consists exists after add", mgr->getConsistList()->contains(conAddr), __FILE__,  __LINE__);
    // delete the consist
    cs->pushDeleteWithDismiss();
    Assert::assertFalse("Consists removed after delete", mgr->getConsistList()->contains(conAddr), __FILE__,  __LINE__);
    cs->requestClose();
// TODO: new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame to close
    qApp->processEvents(QEventLoop::AllEvents, 100);
}

//@Test
/*public*/ void ConsistToolFrameTest::testReverseButton() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    // set up a consist with two addresses.
    cs->setConsistAddressValue("1");
    cs->setLocoAddressValue("12");
    cs->pushAddButton();
    cs->setLocoAddressValue("13");
    cs->pushAddButton();
    DccLocoAddress* conAddr = new DccLocoAddress(1, false);
    //Consist* c = ((ConsistManager*)InstanceManager::getDefault("ConsistManager"))->getConsist(conAddr);
    AbstractConsistManager* mgr = qobject_cast<AbstractConsistManager*>(frame->consistManager->self());
    DccConsist* c = mgr->getConsist(conAddr);
    DccLocoAddress* addr12 = new DccLocoAddress(12, false);
    DccLocoAddress* addr13 = new DccLocoAddress(13, false);
    Assert::assertEquals("12 position before reverse", Consist::POSITION_LEAD, c->getPosition(addr12), __FILE__,  __LINE__);
    Assert::assertNotEquals("13 position before reverse", Consist::POSITION_LEAD, c->getPosition(addr13), __FILE__,  __LINE__);
    cs->pushReverseButton();
    Assert::assertNotEquals("12 position after reverse", Consist::POSITION_LEAD, c->getPosition(addr12), __FILE__,  __LINE__);
    Assert::assertEquals("13 position after reverse", Consist::POSITION_LEAD, c->getPosition(addr13), __FILE__,  __LINE__);
    // delete the consist
    cs->pushDeleteWithDismiss();
//    Assert::assertFalse("Consists removed after delete", qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->contains(conAddr), __FILE__,  __LINE__);
    Assert::assertFalse("Consists removed after delete", mgr->getConsistList()->contains(conAddr), __FILE__,  __LINE__);
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
}

//@Test
/*public*/ void ConsistToolFrameTest::testRestoreButton() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    // set up a consist with two addresses.
    cs->setConsistAddressValue("1");
    cs->setLocoAddressValue("12");
    cs->pushAddButton();
    cs->setLocoAddressValue("13");
    cs->pushAddButton();
    int preRestoreCalls
            = qobject_cast<TestConsistManager*>(frame->consistManager->self())->addCalls;
    // referesh the consist
    cs->pushRestoreButton();
    // need to check that the consist was "written" again.
    Assert::assertEquals("consist written twice", 2 * preRestoreCalls,
            qobject_cast<TestConsistManager*>(frame->consistManager->self())->addCalls, __FILE__,  __LINE__);

    // delete the consist
    cs->pushDeleteWithDismiss();
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
}

//@Test
/*public*/ void ConsistToolFrameTest::testThrottle() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    // set up a consist with one addresses.
    cs->setConsistAddressValue("1");
    cs->setLocoAddressValue("12");
    cs->pushAddButton();
    cs->pushThrottleButton();
    // need to verify throttle is setup with two addresses.

    ThrottleOperator* to = new ThrottleOperator("12(S)");
    Assert::assertEquals("Throttle has right visible address",
            new DccLocoAddress(12, false),
            to->getAddressValue(), __FILE__,  __LINE__);
    Assert::assertEquals("Throttle has right consist address",
            new DccLocoAddress(1, false),
            to->getConsistAddressValue(), __FILE__,  __LINE__);
    to->pushReleaseButton();
    to->requestClose();

//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
}

//@Test
/*public*/ void ConsistToolFrameTest::testDeleteNoConsistAddress() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    JemmyUtil::pressDialogButton("Message", "Ok"); // wait for dialog an when it appears, dismiss it
    cs->pushDeleteButton(); // need to dismiss this ACK
    // this should trigger a warning dialog, which we want to dismiss.
    SleeperThread::msleep(2000); // wait for the dialog
    //JemmyUtil::pressDialogButton("Message", "Ok");
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
}

//@Test
/*public*/ void ConsistToolFrameTest::testScanEmptyRoster() {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    int numConsists = qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size();
    cs->startRosterScan();
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
    //Assert::assertEquals("No New Consists after scan", numConsists, qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void ConsistToolFrameTest::testScanRosterNoConsists() throw (IOException, FileNotFoundException) {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()), "rosterTest.xml");
    InstanceManager::setDefault("Roster", r);

    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    int numConsists = qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size();
    cs->startRosterScan();
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
    Assert::assertEquals("No New Consists after scan", numConsists, qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size(), __FILE__,  __LINE__);
}

//@Test
/*public*/ void ConsistToolFrameTest::testScanRosterWithConsists() throw (IOException, FileNotFoundException) {
    //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
    Roster* r = RosterTestUtil::createTestRoster(new File(Roster::getDefault()->getRosterLocation()), "rosterTest.xml");
    InstanceManager::setDefault("Roster", r);

    // set the consist address of one of the entries.
    RosterEntry* entry = Roster::getDefault()->getEntryForId("ATSF123");

    CvTableModel* cvTable = new CvTableModel(nullptr, nullptr);  // will hold CV objects
    VariableTableModel* varTable = new VariableTableModel(nullptr, QStringList() <<"Name" << "Value",  cvTable);
    entry->readFile();  // read, but don’t yet process

    // load from decoder file
    RosterTestUtil::loadDecoderFromLoco(entry, varTable);

    entry->loadCvModel(varTable, cvTable);
    CvValue* cv19Value = cvTable->getCvByNumber("19");
    cv19Value->setValue(0x02);

    entry->writeFile(cvTable, varTable);

    ConsistToolFrame* frame = new ConsistToolFrame();
    frame->setVisible(true);
    // get a ConsistToolScaffold
    ConsistToolScaffold* cs = new ConsistToolScaffold();
    int numConsists = qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size();
    cs->startRosterScan();
    cs->requestClose();
//    new org.netbeans.jemmy.QueueTool().waitEmpty(100);  //pause for frame tot close
    qApp->processEvents(QEventLoop::AllEvents, 100);
    //Assert::assertEquals("1 New Consists after scan", numConsists + 1, qobject_cast<AbstractConsistManager*>(frame->consistManager->self())->getConsistList()->size(), __FILE__,  __LINE__);
}

//@Before
/*public*/ void ConsistToolFrameTest::setUp() throw (IOException) {
    JUnitUtil::setUp();
    Profile* profile = new NullProfile(folder->newFolder(Profile::PROFILE));
    JUnitUtil::resetProfileManager(profile);
    JUnitUtil::initRosterConfigManager();
    InstanceManager::setDefault("ConsistManager", new TestConsistManager());
    InstanceManager::setDefault("ConsistPreferencesManager", new ConsistPreferencesManager());
    JUnitUtil::initDebugThrottleManager();
//    JUnitUtil::initDebugProgrammerManager(); // added ACK
}

//@After
/*public*/ void ConsistToolFrameTest::tearDown() {
    JUnitUtil::resetWindows(false,false);
    JUnitUtil::tearDown();
}

