#include "accessoryopsmodeprogrammerfacadetest.h"
#include "junitutil.h"
#include "loggerfactory.h"
#include "assert1.h"
#include "instancemanager.h"
#include "mockcommandstation.h"
#include "progdebugger.h"
#include "accessoryopsmodeprogrammerfacade.h"
#include <qstringlist.h>
#include "sleeperthread.h"

AccessoryOpsModeProgrammerFacadeTest::AccessoryOpsModeProgrammerFacadeTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the AccessoryOpsModeProgrammerFacade class.
 *
 * @author	Bob Jacobsen Copyright 2014
 * @author	Dave Heap 2017
 *
 */
// @ToDo("transform to annotations requires e.g. http://alchemy.grimoire.ca/m2/sites/ca.grimoire/todo-annotations/")
// @ToDo("test mode handling")
// @ToDo("test packet contents in each mode")
// @ToDo("test address handling")
// /*public*/ class AccessoryOpsModeProgrammerFacadeTest {

    //@Test
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::testCvLimit() {
        ProgDebugger* dp = new ProgDebugger(true, 123);
        dp->setTestReadLimit(1024);
        dp->setTestWriteLimit(1024);

        Programmer* p = new AccessoryOpsModeProgrammerFacade(dp, "", 0, dp);

        Assert::assertTrue("CV limit read OK", p->getCanRead("1024"), __FILE__, __LINE__);
        Assert::assertTrue("CV limit write OK", p->getCanWrite("1024"), __FILE__, __LINE__);
        Assert::assertTrue("CV limit read fail", !p->getCanRead("1025"), __FILE__, __LINE__);
        Assert::assertTrue("CV limit write fail", !p->getCanWrite("1025"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::testWriteAddr123long1cv234val14delay200signal() throw (ProgrammerException, InterruptedException) {
        testMethod();
    }

    //@Test
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::testWriteAddr3long0cv12val0delay500accessory() throw (ProgrammerException, InterruptedException) {
        testMethod();
    }

    //@Test
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::testWriteAddr511long1cv1024val255delay0decoder() throw (ProgrammerException, InterruptedException) {
        testMethod();
    }

    // from here down is testing infrastructure
    // Perform tests with parameters parsed from the name of the calling method.
    /*synchronized*/ void AccessoryOpsModeProgrammerFacadeTest::testMethod() throw (ProgrammerException, InterruptedException) {
        QString methodName = "";
        int addr = 0;
        bool isLong = false;
        QString addrType = "";
        QString cv = "";
        int value = 0;
        int delay = 0;

        QStringList items = itemsFromMethodName(3, 5);
        if (!items.isEmpty()) {
            methodName = items.at(0);
            addr = items.at(2).toInt();
            isLong = (items.at(4).toInt() != 0);
            cv = items.at(6);
            value = items.at(8).toInt();
            delay = items.at(10).toInt();
            addrType = items.at(11);
        }
        log->debug(tr(
                "Testing: %1:\nExtracted parameters addr='%2',isLong=%3,cv='%4', value=%5, delay=%6, addrType='%7'").arg(
                methodName).arg(addr).arg(isLong).arg(cv).arg(value).arg(delay).arg(addrType));

        // Create an addressed programmer.
        ProgDebugger* dp = new ProgDebugger(isLong, addr);
        // Create a facade over the base programmer and also a listener for the facade.
        Programmer* p = new AccessoryOpsModeProgrammerFacade(dp, addrType, 0, dp);
//        ProgListener l = new ProgListener() {
//            @Override
//            /*public*/ void programmingOpReply(int value, int status) {
//                log.debug("callback value=" + value + " status=" + status);
//                replied = true;
//                readValue = value;
//            }
//        };
        ProgListener* l = new ProgListenerO10(this);

        // Write to the facade programmer.
        p->writeCV(cv, value, l);
        waitReply();

        // Check that the write did not through to the base programmer.
        Assert::assertTrue("target not directly written", !dp->hasBeenWritten(value), __FILE__, __LINE__);
        Assert::assertTrue("index not written", !dp->hasBeenWritten(81), __FILE__, __LINE__);
        // Check that a packet was sent.
        Assert::assertNotNull("packet sent", mockCS->lastPacket, __FILE__, __LINE__);
    }

    void ProgListenerO10::programmingOpReply(int value, int status)
    {
        test->log->debug("callback value=" + QString::number(value) + " status=" + QString::number(status));
        test->replied = true;
        test->readValue = value;
    }


    // Extract test parameters from test name.
    /*synchronized*/ QStringList AccessoryOpsModeProgrammerFacadeTest::itemsFromMethodName(int methodOffset, int groupReps) {
        QString sb; // = new StringBuilder();
        //Pattern pattern;
        QRegularExpression pattern;
        //Matcher matcher;
        QRegularExpressionMatch matcher;
        QStringList retString = QStringList();

        // Extract test parameters from test name.
        //String methodName = Thread.currentThread().getStackTrace()[methodOffset].getMethodName();
        QString methodName = JUnitUtil::getTestClassName();//Thread.currentThread().getStackTrace()[methodOffset].getMethodName();
        sb.append("^");
        for (int i = 1; i <= groupReps; i++) {
            sb.append("(\\D+)(\\d+)");
        }
        sb.append("(\\D*)$");
        QString pat = sb/*.toString()*/;
        pattern = QRegularExpression(pat);//Pattern.compile(pat);
        matcher = pattern.match(methodName);
        log->debug(tr("Test: %1 pat=\"%2\").arg(groupCount=%3").arg(methodName).arg(pat).arg(matcher.lastCapturedIndex()));
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


    /*synchronized*/ void AccessoryOpsModeProgrammerFacadeTest::waitReply() throw (InterruptedException) {
        while (!replied) {
            //wait(200);
         SleeperThread::msleep(200);
        }
        replied = false;
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::setUp() throw (Exception) {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
        InstanceManager::setDefault("CommandStation", mockCS = new MockCommandStation());
        mockCS->lastPacket = nullptr;
    }

    //@After
    /*public*/ void AccessoryOpsModeProgrammerFacadeTest::tearDown() throw (Exception) {
        JUnitUtil::tearDown();
    }

    /*private*/ /*final*/ /*static*/ Logger* AccessoryOpsModeProgrammerFacadeTest::log = LoggerFactory::getLogger("AccessoryOpsModeProgrammerFacadeTest");
