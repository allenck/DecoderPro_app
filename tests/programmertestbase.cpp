#include "programmertestbase.h"
#include "assert1.h"
#include "programmingmode.h"

ProgrammerTestBase::ProgrammerTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * JUnit tests for the Programmer interface
 * <p>
 * Copyright: Copyright (c) 2002</p>
 *
 * @author Bob Jacobsen
 */
// /*abstract*/ /*public*/ class ProgrammerTestBase {


    //@Test
    /*public*/ void ProgrammerTestBase::testCtor() {
        Assert::assertNotNull(programmer->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testDefault() {
        Assert::assertEquals("Check Default", ProgrammingMode::DIRECTMODE,
                programmer->getMode(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testGetCanRead() {
        Assert::assertTrue("can read", programmer->getCanRead(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testGetCanWrite() {
        Assert::assertTrue("can write", programmer->getCanWrite(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testGetCanReadAddress() {
        Assert::assertFalse("can read address", programmer->getCanRead("1234"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testGetCanWriteAddress() {
        Assert::assertTrue("can write address", programmer->getCanWrite("1234"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testSetGetMode() {
        programmer->setMode(ProgrammingMode::REGISTERMODE);
        Assert::assertEquals("Check mode matches set", ProgrammingMode::REGISTERMODE,
                programmer->getMode(), __FILE__, __LINE__);
    }

    //@Test(expected = java.lang.IllegalArgumentException.class)
    /*public*/ void ProgrammerTestBase::testSetModeNull() {
        programmer->setMode(nullptr);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testGetWriteConfirmMode(){
        Assert::assertEquals("Write Confirm Mode",Programmer::WriteConfirmMode::NotVerified,
                programmer->getWriteConfirmMode("1234"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProgrammerTestBase::testWriteCVNullListener() throw (ProgrammerException) {
                programmer->writeCV("1",42,nullptr);
    }

    // The minimal setup for log4J
    //@Before
    //abstract /*public*/ void setUp();

    //@After
    //abstract /*public*/ void tearDown();
