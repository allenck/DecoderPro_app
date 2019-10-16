#include "twoindextcsprogrammerfacadetest.h"
#include "progdebugger.h"
#include "junitutil.h"
#include "assert1.h"
#include "sleeperthread.h"
#include "twoindexprogrammerfacade.h"
#include "loggerfactory.h"


TwoIndexTcsProgrammerFacadeTest::TwoIndexTcsProgrammerFacadeTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author	Bob Jacobsen Copyright 2014
 *
 */
///*public*/ class TwoIndexTcsProgrammerFacadeTest {


//@Test
/*public*/ void TwoIndexTcsProgrammerFacadeTest::testWriteReadDirect() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new TwoIndexTcsProgrammerFacade(dp);
//        ProgListener l = new ProgListener() {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log.debug("callback value=" + value + " status=" + status);
//                replied = true;
//                readValue = value;
//            }
//        };
    ProgListener* l = new ProgListenerO9(this);


    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
}

/*public*/ void ProgListenerO9::programmingOpReply(int value, int status) {
    test->log->debug("callback value=" + QString::number(value) + " status=" + QString::number(status));
    test->replied = true;
    test->readValue = value;
}


//@Test
/*public*/ void TwoIndexTcsProgrammerFacadeTest::testWriteReadDoubleIndexed() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new TwoIndexTcsProgrammerFacade(dp);
//        ProgListener l = new ProgListener() {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log.debug("callback value=" + value + " status=" + status);
//                replied = true;
//                readValue = value;
//            }
//        };
    ProgListener* l = new ProgListenerO9(this);

    p->writeCV("T2CV.10.20", 12 * 256 + 13, l);
    waitReply();
    Assert::assertEquals("index 1 written", 10, dp->getCvVal(201), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 20, dp->getCvVal(202), __FILE__, __LINE__);
    Assert::assertEquals("value MSB written", 12, dp->getCvVal(203), __FILE__, __LINE__);
    Assert::assertEquals("value LSB written", 13, dp->getCvVal(204), __FILE__, __LINE__);

    dp->clearHasBeenWritten(201);
    dp->clearHasBeenWritten(202);
    dp->clearHasBeenWritten(203);
    dp->clearHasBeenWritten(204);
    dp->resetCv(203, 12);
    dp->resetCv(204, 20);

    p->readCV("T2CV.10.20", l);
    waitReply();
    Assert::assertEquals("index 1 written", 100 + 10, dp->getCvVal(201), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 20, dp->getCvVal(202), __FILE__, __LINE__);
    Assert::assertEquals("dummy 204 written", 100, dp->getCvVal(204), __FILE__, __LINE__); // TCS says this is arbitrary, so
    // we write the offset value

    Assert::assertEquals("read back", 12 * 256 + 100, readValue, __FILE__, __LINE__);         // We get 100 from the LSB
    // because we wrote the offset
    // and the test Programmer remembers that
}

//@Test
/*public*/ void TwoIndexTcsProgrammerFacadeTest::testWriteReadTripleIndexed() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new TwoIndexTcsProgrammerFacade(dp);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO9(this);

    p->writeCV("T3CV.10.20.30", 13, l);
    waitReply();
    Assert::assertEquals("index 1 written", 10, dp->getCvVal(201), __FILE__, __LINE__);
    Assert::assertEquals("value written", 13, dp->getCvVal(202), __FILE__, __LINE__);
    Assert::assertEquals("index written to MSB", 20, dp->getCvVal(203), __FILE__, __LINE__);
    Assert::assertEquals("index written to LSB", 30, dp->getCvVal(204), __FILE__, __LINE__);

    dp->clearHasBeenWritten(201);
    dp->resetCv(202, 13);
    dp->clearHasBeenWritten(203);
    dp->clearHasBeenWritten(204);

    p->readCV("T3CV.10.20.30", l);
    waitReply();
    Assert::assertEquals("index 1 written", 100 + 10, dp->getCvVal(201), __FILE__, __LINE__);
    Assert::assertEquals("SI not written, left at start value", 13, dp->getCvVal(202), __FILE__, __LINE__);
    Assert::assertEquals("index written to MSB", 20, dp->getCvVal(203), __FILE__, __LINE__);
    Assert::assertEquals("index written to LSB", 30, dp->getCvVal(204), __FILE__, __LINE__);

    Assert::assertEquals("read back", 13, readValue, __FILE__, __LINE__);
}

//@Test
/*public*/ void TwoIndexTcsProgrammerFacadeTest::testCvLimit() {
    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(1024);

    Programmer* p = new TwoIndexTcsProgrammerFacade(dp);

    Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
}

// from here down is testing infrastructure
/*synchronized*/ void TwoIndexTcsProgrammerFacadeTest::waitReply() throw (InterruptedException) {
    while (!replied) {
        //wait(200);
     SleeperThread::msleep(200);
     qApp->processEvents();
    }
    replied = false;
}

//@Before
/*public*/ void TwoIndexTcsProgrammerFacadeTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void TwoIndexTcsProgrammerFacadeTest::tearDown(){
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* TwoIndexTcsProgrammerFacadeTest::log = LoggerFactory::getLogger("TwoIndexTcsProgrammerFacadeTest");
