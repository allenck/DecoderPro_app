#include "controllerfilterframetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "controllerfilterframe.h"

ControllerFilterFrameTest::ControllerFilterFrameTest(QObject *parent)
 : JmriJFrameTestBase(parent)
{

}
/**
 * Test simple functioning of ControllerFilterFrame
 *
 * @author	Paul Bender Copyright (C) 2016
 */
//public class ControllerFilterFrameTest extends jmri.util.JmriJFrameTestBase {

    //@Before
    //@Override
    /*public*/ void ControllerFilterFrameTest::setUp() {
        JUnitUtil::setUp();
//        if(!GraphicsEnvironment.isHeadless()){
           frame = new ControllerFilterFrame();
           frame->initComponents();
//        }
           Assert::assertNull("exists",frame, __FILE__,  __LINE__);

    }

    //@After
    //@Override
    /*public*/ void ControllerFilterFrameTest::tearDown() {
        JmriJFrameTestBase::tearDown();
    }
