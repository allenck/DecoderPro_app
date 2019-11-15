#include "turnoutsignalmastaddpanetest.h"
#include "junitutil.h"
#include "assert1.h"
#include "signalmastaddpane.h"
#include "turnoutsignalmast.h"
#include "matrixsignalmast.h"
#include "turnoutsignalmastaddpane.h"
#include "signalsystemmanager.h"
#include "junitappender.h"

TurnoutSignalMastAddPaneTest::TurnoutSignalMastAddPaneTest()
{

}
/**
 * @author	Bob Jacobsen Copyright 2018
 */
///*public*/ class TurnoutSignalMastAddPaneTest extends AbstractSignalMastAddPaneTestBase {

    /** {@inheritDoc} */
    //@Override
    /*protected*/ SignalMastAddPane* TurnoutSignalMastAddPaneTest::getOTT() { return new TurnoutSignalMastAddPane(); }

    //@Test
    /*public*/ void TurnoutSignalMastAddPaneTest::testSetMast() {
        TurnoutSignalMast* s1 = new TurnoutSignalMast("IF$tsm:basic:one-searchlight($1)", "user name");
        MatrixSignalMast* m1 = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        TurnoutSignalMastAddPane* vp = new TurnoutSignalMastAddPane();

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

//    @Before
//    @Override
    /*public*/ void TurnoutSignalMastAddPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();
    }

//    @After
//    @Override
    /*public*/ void TurnoutSignalMastAddPaneTest::tearDown() {
        JUnitUtil::tearDown();
    }
