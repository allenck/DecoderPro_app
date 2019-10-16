#include "multiindexprogrammerfacadetest.h"
#include "loggerfactory.h"
#include "progdebugger.h"
#include "assert1.h"
#include "multiindexprogrammerfacade.h"
#include "junitutil.h"
#include "sleeperthread.h"
#include "programmer.h"

MultiIndexProgrammerFacadeTest::MultiIndexProgrammerFacadeTest(QObject *parent) : QObject(parent)
{

}

/**
 * Test the MultiIndexProgrammerFacade* class.
 *
 * @author	Bob Jacobsen Copyright 2013
 *
 */
// /*public*/ class MultiIndexProgrammerFacadeTest {


//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDirect() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "", true, false);
    ProgListener* l = new ProgListenerO5(this);
//        {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log.debug("callback value=" + value + " status=" + status);
//                replied = true;
//                readValue = value;
//            }
//        };

    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
}

/*public*/ void ProgListenerO5::programmingOpReply(int value, int status) {
    test->log->debug("callback value=" + QString::number(value) + " status=" + QString::number(status));
    test->replied = true;
    test->readValue = value;
}


//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDirectSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "", true, true);
//    ProgListener* l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("4", 12, l);
    waitReply();
    Assert::assertEquals("target written", 12, dp->getCvVal(4), __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);

    p->readCV("4", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadSingleIndexed() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, false);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("123.45", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("123.45", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("index written", 45, dp->getCvVal(81), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadSingleIndexedSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);


    p->writeCV("123.45", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("123.45", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadSingleIndexedCvLast() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, false);
//    ProgListener* l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);


    p->writeCV("45.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("index written", 45, dp->getCvVal(81), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadSingleIndexedCvLastSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, true);
//    ProgListener* l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
      ProgListener* l = new ProgListenerO5(this);

      p->writeCV("22.88", 15, l);
    waitReply();
    Assert::assertEquals("index 1 written", 22, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 15, dp->getCvVal(88), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 88, dp->lastWriteCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->writeCV("45.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 123, dp->lastWriteCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("last read CV", 123, dp->lastReadCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("22.88", l);
    waitReply();
    Assert::assertEquals("read back", 15, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 22, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("last read CV", 88, dp->lastReadCv(), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteWriteSingleIndexedCvLastSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("2.51", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 2, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(51), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 51, dp->lastWriteCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->writeCV("2.52", 15, l);
    waitReply();
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 15, dp->getCvVal(52), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 52, dp->lastWriteCv(), __FILE__, __LINE__);

}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteWriteSingleIndexedCvFirstSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("51.2", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 2, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(51), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 51, dp->lastWriteCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->writeCV("52.2", 15, l);
    waitReply();
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 15, dp->getCvVal(52), __FILE__, __LINE__);
    Assert::assertEquals("last written CV", 52, dp->lastWriteCv(), __FILE__, __LINE__);

}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexed() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, false);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);


    p->writeCV("123.45.46", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("123.45.46", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedAltPiSi() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, false);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);


    p->writeCV("123.101=45.102=46", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("123.101=45.102=46", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", true, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("123.45.46", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);
    Assert::assertEquals("last write CV", 123, dp->lastWriteCv(), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("123.45.46", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);
    Assert::assertEquals("last read CV", 123, dp->lastReadCv(), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedCvList() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, false);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("45.46.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);

}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedCvListAltPiSi() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, false);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("101=45.102=46.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);

}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedCvListSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    MultiIndexProgrammerFacade* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("45.46.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(82), __FILE__, __LINE__);

    // add timeout
    p->lastOpTime = p->lastOpTime - 2*p->maxDelay;

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedCvListSkipAltPiSi() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    MultiIndexProgrammerFacade* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);


    p->writeCV("101=45.102=46.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(101), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(102), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(101), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(102), __FILE__, __LINE__);

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertTrue("index 1 not written", !dp->hasBeenWritten(101), __FILE__, __LINE__);
    Assert::assertTrue("index 2 not written", !dp->hasBeenWritten(102), __FILE__, __LINE__);

    // add timeout
    p->lastOpTime = p->lastOpTime - 2*p->maxDelay;

    dp->clearHasBeenWritten(101);
    dp->clearHasBeenWritten(102);

    p->readCV("101=45.102=46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(101), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(102), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testWriteReadDoubleIndexedCvListDelayedSkip() throw (ProgrammerException, InterruptedException) {

    ProgDebugger* dp = new ProgDebugger();
    MultiIndexProgrammerFacade* p = new MultiIndexProgrammerFacade(dp, "81", "82", false, true);
//    ProgListener l = new ProgListener() {
//        @Override
//        /*public*/ void programmingOpReply(int value, int status) {
//            log.debug("callback value=" + value + " status=" + status);
//            replied = true;
//            readValue = value;
//        }
//    };
    ProgListener* l = new ProgListenerO5(this);

    p->writeCV("45.46.123", 12, l);
    waitReply();
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
    Assert::assertEquals("value written", 12, dp->getCvVal(123), __FILE__, __LINE__);

    dp->clearHasBeenWritten(81);
    dp->clearHasBeenWritten(82);

    // pretend too long has elapsed, so should still program
    p->lastOpTime = p->lastOpTime - 2*p->maxDelay;

    p->readCV("45.46.123", l);
    waitReply();
    Assert::assertEquals("read back", 12, readValue, __FILE__, __LINE__);
    Assert::assertEquals("index 1 written", 45, dp->getCvVal(81), __FILE__, __LINE__);
    Assert::assertEquals("index 2 written", 46, dp->getCvVal(82), __FILE__, __LINE__);
}

//@Test
/*public*/ void MultiIndexProgrammerFacadeTest::testCvLimit() {
    ProgDebugger* dp = new ProgDebugger();
    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(1024);

    Programmer* p = new MultiIndexProgrammerFacade(dp, "81", "", true, false);

    Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
}

// from here down is testing infrastructure
/*synchronized*/ void MultiIndexProgrammerFacadeTest::waitReply() throw (InterruptedException) {
    while (!replied) {
        //wait(200);
     SleeperThread::msleep(200);
     qApp->processEvents();
    }
    replied = false;
}

//@Before
/*public*/ void MultiIndexProgrammerFacadeTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void MultiIndexProgrammerFacadeTest::tearDown(){
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* MultiIndexProgrammerFacadeTest::log = LoggerFactory::getLogger("MultiIndexProgrammerFacadeTest");
