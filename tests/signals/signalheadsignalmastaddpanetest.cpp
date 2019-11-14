#include "signalheadsignalmastaddpanetest.h"
#include "assert1.h"
#include "junitutil.h"
#include "signalmastaddpane.h"
#include "instancemanager.h"
#include "signalheadmanager.h"
#include "signalheadsignalmastaddpane.h"
#include "matrixsignalmast.h"
#include "signalheadsignalmast.h"
#include "signalsystemmanager.h"
#include "junitappender.h"

SignalHeadSignalMastAddPaneTest::SignalHeadSignalMastAddPaneTest()
{

}
/**
 * @author	Bob Jacobsen Copyright 2018
 */
// /*public*/ class SignalHeadSignalMastAddPaneTest extends AbstractSignalMastAddPaneTestBase {

    /** {@inheritDoc} */
    //@Override
    /*protected*/ SignalMastAddPane* SignalHeadSignalMastAddPaneTest::getOTT() { return new SignalHeadSignalMastAddPane(); }

    //@Test
    /*public*/ void SignalHeadSignalMastAddPaneTest::testSetMast() {
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead2("IH1", this));
//         {
//             @Override
//             protected void updateOutput() {
//             }
//         }
//        );
        SignalHeadSignalMast* s1 = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user name");
        MatrixSignalMast* m1 = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        SignalHeadSignalMastAddPane* vp = new SignalHeadSignalMastAddPane();

        Assert::assertTrue(vp->canHandleMast(s1), __FILE__, __LINE__);
        Assert::assertFalse(vp->canHandleMast(m1), __FILE__, __LINE__);

        vp->setMast(nullptr);

        vp->setAspectNames(s1->getAppearanceMap(), ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(s1);

        vp->setAspectNames(m1->getAppearanceMap(), ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(m1);
        vp->show();

        JUnitAppender::assertErrorMessage("mast was wrong type: IF$xsm:basic:one-low($0001)-3t jmri.implementation.MatrixSignalMast", __FILE__, __LINE__);
    }

    //@Before
    //@Override
    /*public*/ void SignalHeadSignalMastAddPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();
    }

    //@After
    //@Override
    /*public*/ void SignalHeadSignalMastAddPaneTest::tearDown() {
        JUnitUtil::tearDown();
    }
