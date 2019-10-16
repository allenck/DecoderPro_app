#include "addressedhighcvprogranmmerfacadetest.h"
#include "loggerfactory.h"
#include "progdebugger.h"
#include "addressedhighcvprogrammerfacade.h"
#include "junitutil.h"
#include "assert1.h"
#include "sleeperthread.h"
#include "progdebugger.h"

AddressedHighCvProgranmmerFacadeTest::AddressedHighCvProgranmmerFacadeTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the AddressedHighCvProgrammerFacade class.
 *
 * @author	Bob Jacobsen Copyright 2013
 *
 */
///*public*/ class AddressedHighCvProgrammerFacadeTest {


//@Test
/*public*/ void AddressedHighCvProgranmmerFacadeTest::testWriteReadDirect() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(256);
    dp->setTestWriteLimit(256);

    Programmer* p = new AddressedHighCvProgrammerFacade(dp, "256", "253", "254", "255", "100");
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO6(this);

    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertTrue("index H not written", !dp->hasBeenWritten(253), __FILE__, __LINE__);
    Assert::assertTrue("index L not written", !dp->hasBeenWritten(254), __FILE__, __LINE__);
    Assert::assertTrue("index val not written", !dp->hasBeenWritten(255), __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

/*public*/ void ProgListenerO6::programmingOpReply(int value, int status) {
    test->log->debug("callback value=" + QString::number(value) + " status=" + QString::number(status));
    test->replied = true;
    test->readValue = value;
}

//@Test
/*public*/ void AddressedHighCvProgranmmerFacadeTest::testWriteReadDirectHighCV() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(1024);

    Programmer* p = new AddressedHighCvProgrammerFacade(dp, "256", "253", "254", "255", "100");
    //    ProgListener l = new ProgListener() {
    //        @Override
    //        /*public*/ void programmingOpReply(int value, int status) {
    //            log.debug("callback value=" + value + " status=" + status);
    //            replied = true;
    //            readValue = value;
    //        }
    //    };
        ProgListener* l = new ProgListenerO6(this);

    p->writeCV("258", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(258), __FILE__, __LINE__);
    Assert::assertTrue("index H not written", !dp->hasBeenWritten(253), __FILE__, __LINE__);
    Assert::assertTrue("index L not written", !dp->hasBeenWritten(254), __FILE__, __LINE__);
    Assert::assertTrue("index val not written", !dp->hasBeenWritten(255), __FILE__, __LINE__);

    p->readCV("258", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

//@Test
/*public*/ void AddressedHighCvProgranmmerFacadeTest::testWriteReadDirectHighCVRightSide() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(256);
    dp->setTestWriteLimit(1024);

    Programmer* p = new AddressedHighCvProgrammerFacade(dp, "256", "253", "254", "255", "100");
    //    ProgListener l = new ProgListener() {
    //        @Override
    //        /*public*/ void programmingOpReply(int value, int status) {
    //            log.debug("callback value=" + value + " status=" + status);
    //            replied = true;
    //            readValue = value;
    //        }
    //    };
        ProgListener* l = new ProgListenerO6(this);
    p->writeCV("258", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(258), __FILE__, __LINE__);
    Assert::assertTrue("index H not written", !dp->hasBeenWritten(253), __FILE__, __LINE__);
    Assert::assertTrue("index L not written", !dp->hasBeenWritten(254), __FILE__, __LINE__);
    Assert::assertTrue("index val not written", !dp->hasBeenWritten(255), __FILE__, __LINE__);

    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(256);

    p->readCV("258", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

//@Test
/*public*/ void AddressedHighCvProgranmmerFacadeTest::testWriteReadIndexed() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(256);
    dp->setTestWriteLimit(256);
    Programmer* p = new AddressedHighCvProgrammerFacade(dp, "256", "253", "254", "255", "100");
    //    ProgListener l = new ProgListener() {
    //        @Override
    //        /*public*/ void programmingOpReply(int value, int status) {
    //            log.debug("callback value=" + value + " status=" + status);
    //            replied = true;
    //            readValue = value;
    //        }
    //    };
        ProgListener* l = new ProgListenerO6(this);
    p->writeCV("258", 12, l);
    waitReply();
    Assert::assertTrue("target not written", !dp->hasBeenWritten(258), __FILE__, __LINE__);
    Assert::assertEquals("index H written", 2, dp->getCvVal(253), __FILE__, __LINE__);
    Assert::assertEquals("index L written", 58, dp->getCvVal(254), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(255), __FILE__, __LINE__);

    p->readCV("258", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

//@Test
/*public*/ void AddressedHighCvProgranmmerFacadeTest::testCvLimit() {
    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(256);
    dp->setTestWriteLimit(256);
    Programmer* p = new AddressedHighCvProgrammerFacade(dp, "256", "253", "254", "255", "100");
    Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
}

// from here down is testing infrastructure
/*synchronized*/ void AddressedHighCvProgranmmerFacadeTest::waitReply() throw (InterruptedException) {
    while (!replied) {
        //wait(200);
     SleeperThread::msleep(200);

    }
    replied = false;
}

//@Before
/*public*/ void AddressedHighCvProgranmmerFacadeTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void AddressedHighCvProgranmmerFacadeTest::tearDown(){
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* AddressedHighCvProgranmmerFacadeTest::log = LoggerFactory::getLogger("AddressedHighCvProgrammerFacadeTest");
