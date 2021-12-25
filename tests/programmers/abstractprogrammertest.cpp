#include "abstractprogrammertest.h"
#include "junitutil.h"
#include "assert1.h"
#include "junitappender.h"

AbstractProgrammerTest::AbstractProgrammerTest() : ProgrammerTestBase()
{

}
/**
 * JUnit tests for the AbstractProgrammer class
 * <p>
 * Copyright: Copyright (c) 2002</p>
 *
 * @author Bob Jacobsen
 */
///*public*/ class AbstractProgrammerTest extends jmri.ProgrammerTestBase {

    //@Test
    /*public*/ void AbstractProgrammerTest::testDefaultViaBestMode() {
        //Assume.assumeTrue(programmer instanceof AbstractProgrammer);
        Assert::assertEquals("Check Default", ProgrammingMode::DIRECTMODE,
                ((AbstractProgrammer*)programmer->self())->getBestMode(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractProgrammerTest::testRegisterFromCV() {
        //Assume.assumeTrue(programmer instanceof AbstractProgrammer);
        AbstractProgrammer* abstractprogrammer = (AbstractProgrammer*) programmer->self();
        int cv1 = -1;

        try {
            Assert::assertEquals("test CV 1", 1,
                    abstractprogrammer->registerFromCV(cv1 = 1), __FILE__, __LINE__);
            Assert::assertEquals("test CV 2", 2,
                    abstractprogrammer->registerFromCV(cv1 = 2), __FILE__, __LINE__);
            Assert::assertEquals("test CV 3", 3,
                    abstractprogrammer->registerFromCV(cv1 = 3), __FILE__, __LINE__);
            Assert::assertEquals("test CV 4", 4,
                    abstractprogrammer->registerFromCV(cv1 = 4), __FILE__, __LINE__);
            Assert::assertEquals("test CV 29", 5,
                    abstractprogrammer->registerFromCV(cv1 = 29), __FILE__, __LINE__);
            Assert::assertEquals("test CV 7", 7,
                    abstractprogrammer->registerFromCV(cv1 = 7), __FILE__, __LINE__);
            Assert::assertEquals("test CV 8", 8,
                    abstractprogrammer->registerFromCV(cv1 = 8), __FILE__, __LINE__);
        } catch (Exception* e) {
            Assert::fail("unexpected exception while cv = " + cv1, __FILE__, __LINE__);
        }

        // now try for some exceptions
        for (cv1 = 5; cv1 < 29; cv1++) {
            if (cv1 == 7 || cv1 == 8) {
                continue;
            }
            try {
                abstractprogrammer->registerFromCV(cv1); // should assert
                Assert::fail("did not throw as expected for cv = " + cv1, __FILE__, __LINE__);
            } catch (Exception* e) {
                JUnitAppender::assertWarnMessage("Unhandled register from cv:  "+QString::number(cv1));
            }
        }
    }

    //@BeforeEach
    //@Override
    /*public*/ void AbstractProgrammerTest::setUp() {
        JUnitUtil::setUp();

//        programmer = new APTAbstractProgrammer() {

//            @Override
//            /*public*/ List<ProgrammingMode> getSupportedModes() {
//                java.util.ArrayList<ProgrammingMode> retval = new java.util.ArrayList<ProgrammingMode>();

//                retval.add(ProgrammingMode.DIRECTMODE);
//                retval.add(ProgrammingMode.PAGEMODE);
//                retval.add(ProgrammingMode.REGISTERMODE);

//                return retval;
//            }

//            // Programmer implementation that uses getBestMode for setting default
//            @Override
//            /*public*/ ProgrammingMode getBestMode() { return ProgrammingMode.DIRECTMODE; }

//            @Override
//            /*public*/ void writeCV(String i, int j, ProgListener l) {}
//            @Override
//            /*public*/ void confirmCV(String i, int j, ProgListener l) {}
//            @Override
//            /*public*/ void readCV(String i, ProgListener l) {}
//            @Override
//            /*public*/ void timeout() {}
//            @Override
//            /*public*/ boolean getCanRead() { return true;}
//        };
    programmer = new APTAbstractProgrammer(this);
  }

    //@AfterEach
    //@Override
    /*public*/ void AbstractProgrammerTest::tearDown() {
        programmer = nullptr;
        JUnitUtil::tearDown();
    }
