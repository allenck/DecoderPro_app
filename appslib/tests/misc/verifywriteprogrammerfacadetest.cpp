#include "verifywriteprogrammerfacadetest.h"
#include "loggerfactory.h"
#include "junitutil.h"
#include "assert1.h"
#include "progdebugger.h"
#include "verifywriteprogrammerfacade.h"
#include "sleeperthread.h"

VerifyWriteProgrammerFacadeTest::VerifyWriteProgrammerFacadeTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the VerifyWriteProgrammerFacade class.
 *
 * @author	Bob Jacobsen Copyright 2013
 *
 */
///*public*/ class VerifyWriteProgrammerFacadeTest {


    //@Test
/*public*/ void VerifyWriteProgrammerFacadeTest::testWriteReadDirect() throw (ProgrammerException, InterruptedException){

    readCount = 0;
//        ProgDebugger* dp = new ProgDebugger() {
//            @Override
//            /*public*/ boolean getCanRead(String cv) { return false; }
//            @Override
//            /*public*/ boolean getCanRead() { return false; }
//            @Override
//            /*public*/ void readCV(String cv, ProgListener p) throws ProgrammerException { readCount++; super.readCV(cv, p); }
//        };
    ProgDebugger* dp = new ProgDebuggerO1(this);
    Programmer* p = new VerifyWriteProgrammerFacade(dp);
//        ProgListener l = new ProgListener() {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log.debug("callback value=" + value + " status=" + status);
//                replied = true;
//                readValue = value;
//            }
//        };
    ProgListener* l = new ProgListenerO8(this);

    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertEquals("reads", 0, readCount, __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

/*public*/ void ProgListenerO8::programmingOpReply(int value, int status) {
test->log->debug("callback value=" + QString::number(value) + " status=" + QString::number(status));
test->replied = true;
test->readValue = value;
}


//@Test
/*public*/ void VerifyWriteProgrammerFacadeTest::testWriteReadVerify() throw (ProgrammerException, InterruptedException){

    readCount = 0;
//    ProgDebugger* dp = new ProgDebugger() {
//        @Override
//        /*public*/ boolean getCanRead(String cv) { return true; }
//        @Override
//        /*public*/ boolean getCanRead() { return true; }
//        @Override
//        /*public*/ void readCV(String cv, ProgListener p) throws ProgrammerException { readCount++; super.readCV(cv, p); }
//    };
    ProgDebugger* dp = new ProgDebuggerO1(this);
    Programmer* p = new VerifyWriteProgrammerFacade(dp);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO8(this);


    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertEquals("reads", 1, readCount, __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
}

//@Test
/*public*/ void VerifyWriteProgrammerFacadeTest::testCvLimit() {
    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(1024);

    Programmer* p = new VerifyWriteProgrammerFacade(dp);

    Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
}

// from here down is testing infrastructure
/*synchronized*/ void VerifyWriteProgrammerFacadeTest::waitReply() throw (InterruptedException) {
    while (!replied) {
        //wait(200);
     SleeperThread::msleep(200);
     qApp->processEvents();
    }
    replied = false;
}

//@Before
/*public*/ void VerifyWriteProgrammerFacadeTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void VerifyWriteProgrammerFacadeTest::tearDown(){
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* VerifyWriteProgrammerFacadeTest::log = LoggerFactory::getLogger("VerifyWriteProgrammerFacadeTest");
