#include "sprogmessagetest.h"
#include "sprogmessage.h"
#include "assert1.h"
#include "junitutil.h"

using namespace Sprog;
SprogMessageTest::SprogMessageTest()
{

}
/**
 * JUnit tests for the SprogMessage class.
 *
 * @author	Bob Jacobsen Copyright 2012
 */
// /*public*/ class SprogMessageTest extends jmri.jmrix.AbstractMessageTestBase {


//@Test
/*public*/ void SprogMessageTest::testReadCv() {
    msg = SprogMessage::getReadCV(12, ProgrammingMode::PAGEMODE);
    Assert::assertEquals("string compare ", "V 0012", msg->toString());
}

//@Test
/*public*/ void SprogMessageTest::testWriteCV() {
    msg = SprogMessage::getWriteCV(12, 251, ProgrammingMode::PAGEMODE);
    Assert::assertEquals("string compare ", "V 0012 251", msg->toString());
}

//@Test
/*public*/ void SprogMessageTest::testReadCvLarge() {
    msg = SprogMessage::getReadCV(1021, ProgrammingMode::PAGEMODE);
    Assert::assertEquals("string compare ", "V 1021", msg->toString());
}

//@Test
/*public*/ void SprogMessageTest::testWriteCVLarge() {
    msg = SprogMessage::getWriteCV(1021, 251, ProgrammingMode::PAGEMODE);
    Assert::assertEquals("string compare ", "V 1021 251", msg->toString());
}

// The minimal setup for log4J
//@Before
//@Override
/*public*/ void SprogMessageTest::setUp() {
    JUnitUtil::setUp();
    m = msg = new SprogMessage(1);
}

//@After
/*public*/ void SprogMessageTest::tearDown() {
m = msg = nullptr;
    JUnitUtil::tearDown();
}
