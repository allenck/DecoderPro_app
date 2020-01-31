#include "jmrijframetestbase.h"
#include "assert1.h"
#include "assume.h"
#include "jmrijframe.h"
#include "junitutil.h"
#include "jframeoperator.h"

JmriJFrameTestBase::JmriJFrameTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Base tests for JmriJFrame derived frames.
 *
 * @author Paul Bender Copyright (C) 2017
 */
// abstract public class JmriJFrameTestBase {


    //@Test
    /*public*/ void JmriJFrameTestBase::testCTor() {
//        Assume::assumeFalse(GraphicsEnvironment.isHeadless());
        Assert::assertNotNull("exists",frame, __FILE__,  __LINE__);
    }

    //Test
    /*public*/ void JmriJFrameTestBase::testShowAndClose() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        frame->initComponents();
        //jmri.util.ThreadingUtil.runOnLayout(() -> {
            frame->setVisible(true);
        //});
        JFrameOperator* fo = new JFrameOperator(frame);
//        // It's up at this point, and can be manipulated
//        // Ask to close window
        fo->requestClose();
    }

    //@Before
    /*abstract*/ /*public*/ void setUp();  // set the value of frame.
                                   // do not call initComponents.

    //@After
    /*public*/ void JmriJFrameTestBase::tearDown() {
//        if(frame!=nullptr) {
//           JUnitUtil::dispose(frame);
//        }
//        frame = nullptr;
        //JUnitUtil::resetWindows(false,false);
        JUnitUtil::tearDown();
    }
