#include "virtualsignalheadtest.h"
#include "junitutil.h"
#include "assert1.h"
#include "virtualsignalhead.h"

VirtualSignalHeadTest::VirtualSignalHeadTest(QObject *parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class VirtualSignalHeadTest extends AbstractSignalHeadTestBase {

    //@Test
    /*public*/ void VirtualSignalHeadTest::testCTor() {
        VirtualSignalHead* t = new VirtualSignalHead("Virtual Signal Head Test");
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
    }

    //@Override
    /*public*/ SignalHead* VirtualSignalHeadTest::getHeadToTest() {
        return new VirtualSignalHead("Virtual Signal Head Test");
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void VirtualSignalHeadTest::setUp() {
        JUnitUtil::setUp();
    }

    //@After
    /*public*/ void VirtualSignalHeadTest::tearDown() {
        JUnitUtil::tearDown();
    }
