#include "opsmodedelayedprogrammerfacadetest.h"
#include "loggerfactory.h"
#include "junitutil.h"
#include "assert1.h"
#include "sleeperthread.h"
#include "progdebugger.h"
#include "opsmodedelayedprogrammerfacade.h"
#include <QRegularExpression>
#include <QDateTime>

OpsModeDelayedProgrammerFacadeTest::OpsModeDelayedProgrammerFacadeTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the OpsModeDelayedProgrammerFacade class.
 *
 * @author	Bob Jacobsen Copyright 2014
 *
 */
///*public*/ class OpsModeDelayedProgrammerFacadeTest {

//@Test
/*public*/ void OpsModeDelayedProgrammerFacadeTest::testWrite4Val12Delay0() throw (ProgrammerException, InterruptedException){
    testMethod(123, true);
}

//@Test
/*public*/ void OpsModeDelayedProgrammerFacadeTest::testWrite37Val102Delay1000() throw (ProgrammerException, InterruptedException){
    testMethod(123, true);
}

//@Test
/*public*/ void OpsModeDelayedProgrammerFacadeTest::testWrite1024Val255Delay2000() throw (ProgrammerException, InterruptedException){
    testMethod(123, true);
}

//@Test
/*public*/ void OpsModeDelayedProgrammerFacadeTest::testWrite0Val23Delay100() throw (ProgrammerException, InterruptedException){
    testMethod(123, true);
}

//@Test
/*public*/ void OpsModeDelayedProgrammerFacadeTest::testCvLimit() {
    ProgDebugger* dp = new ProgDebugger(true, 123);
    dp->setTestReadLimit(1024);
    dp->setTestWriteLimit(1024);

    Programmer* p = new OpsModeDelayedProgrammerFacade(dp, 0);

    Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
    Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
}


// Perform tests with parameters parsed from the name of the calling method.
/*synchronized*/ void OpsModeDelayedProgrammerFacadeTest::testMethod(int addr, bool addrType) throw (ProgrammerException, InterruptedException){
    QString methodName = "";
    QString cv = "";
    int value = 0;
    int delay = 0;

    facProgRetValue = -2;
    facProgRetStatus = -2;
    facProgReplied = false;

    QList<QString> items = itemsFromMethodName(3, 3);
    if (!items.isEmpty()) {
        methodName = items.at(0);
        cv = items.at(2);
        value = items.at(4).toInt();
        delay = items.at(6).toInt();
    }
    log->debug(tr("Testing: %1:\nExtracted parameters cv='%2', value=%3, delay=%4").arg(methodName).arg(cv).arg(value).arg(delay));

    // Create a base addressed programmer.
    ProgDebugger* baseProg = new ProgDebugger(addrType, addr);

    // Create a facade over the base programmer and also a listener for the facade.
    Programmer* facProg = new OpsModeDelayedProgrammerFacade(baseProg, delay);
//        ProgListener facProgListnr = new ProgListener() {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log->debug("facProg callback value={},status={}", value, +status);
//                facProgReplied = true;
//                facProgRetValue = value;
//                facProgRetStatus = status;
//            }
//        };
    ProgListener* facProgListnr = new ProgListenerO7(this);

    // Write to the facade programmer.
    //Instant start = Instant.now();
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    facProg->writeCV(cv, value, facProgListnr);
    facProgWaitReply();
    //Instant end = Instant.now();
    qint64 end = QDateTime::currentMSecsSinceEpoch();
    long elapsed = end - start;//Duration.between(start, end).toMillis();

    // Check that the write flowed through to the base programmer.
    Assert::assertTrue("Original CV has been written", baseProg->hasBeenWritten((cv).toInt()), __FILE__, __LINE__);
    Assert::assertEquals("Original CV was last one written", (cv).toInt(), baseProg->lastWriteCv(), __FILE__, __LINE__);
    Assert::assertEquals("Original CV value is as expected", value, baseProg->lastWrite(), __FILE__, __LINE__);

    log->debug(tr("Notification delay=%1, elapsed=%2").arg(delay).arg(elapsed));
    Assert::assertEquals(tr("Elapsed time (%1) >= delay  (%2)").arg(elapsed).arg(delay), true, (elapsed >= delay), __FILE__, __LINE__);
    Assert::assertEquals("Facade listener return value OK", value, facProgRetValue, __FILE__, __LINE__);
    Assert::assertEquals("Facade listener return status OK", ProgListener::OK, facProgRetStatus, __FILE__, __LINE__);
}

/*public*/ void ProgListenerO7::programmingOpReply(int value, int status) {
 test->log->debug(tr("facProg callback value=%1,status=%2").arg(value).arg(+status));
 test->facProgReplied = true;
 test->facProgRetValue = value;
 test->facProgRetStatus = status;
}

// Extract test parameters from test name.
/*synchronized*/ QList<QString> OpsModeDelayedProgrammerFacadeTest::itemsFromMethodName(int methodOffset, int groupReps) {
    QString sb; // = new StringBuilder();
    //Pattern pattern;
    QRegularExpression pattern;
    //Matcher matcher;
    QRegularExpressionMatch matcher;
    QStringList retString = QStringList();

    // Extract test parameters from test name.
    QString methodName = JUnitUtil::getTestClassName();//Thread.currentThread().getStackTrace()[methodOffset].getMethodName();
    sb.append("^");
    for (int i = 1; i <= groupReps; i++) {
        sb.append("(\\D+)(\\d+)");
    }
    sb.append("(\\D*)$");
    QString pat = sb;
    pattern = QRegularExpression(pat);//Pattern.compile(pat);
    matcher = pattern.match(methodName);
    log->debug(tr("Test: %1 pat=\"%2\", groupCount=%3").arg(methodName).arg(pat).arg(matcher.lastCapturedIndex()));
    if (matcher.hasMatch()) {
        for (int j = 0; j <= matcher.lastCapturedIndex(); j++) {
            retString.append(matcher.captured(j));
            log->debug(tr("Adding item=%1, string=\"%2\"").arg(j).arg(matcher.captured(j)));
        }
    } else {
        log->error(tr("method=\"%1\" did not match pattern=\"%2\"").arg(methodName).arg(pat));
    }
    return retString;
}

/*synchronized*/ void OpsModeDelayedProgrammerFacadeTest::facProgWaitReply() throw (InterruptedException) {
    while (!facProgReplied) {
        //wait(10);
     SleeperThread::msleep(10);
    }
    facProgReplied = false;
}

// The minimal setup for log4J
//@Before
/*public*/ void OpsModeDelayedProgrammerFacadeTest::setUp() throw (Exception) {
    JUnitUtil::setUp();
}

//@After
/*public*/ void OpsModeDelayedProgrammerFacadeTest::tearDown() throw (Exception) {
    JUnitUtil::tearDown();
}

/*private*/ /*final*/ /*static*/ Logger* OpsModeDelayedProgrammerFacadeTest::log = LoggerFactory::getLogger("OpsModeDelayedProgrammerFacadeTest");
