#include "optionsmenutest.h"
#include "../operations/optionsmenu.h"
#include "../operations/dispatcherframe.h"
#include "assert1.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "../operations/optionsfile.h"

OptionsMenuTest::OptionsMenuTest(QObject *parent) : QObject(parent)
{

}
/**
 *
 * @author Paul Bender Copyright (C) 2017
 */
// /*public*/ class OptionsMenuTest {

    //@Test
    /*public*/ void OptionsMenuTest::testCTor() {
        //Assume.assumeFalse(GraphicsEnvironment.isHeadless());
        OptionsFile::setDefaultFileName("java/test/jmri/jmrit/dispatcher/dispatcheroptions.xml");  // exist?

        DispatcherFrame* d = (DispatcherFrame*)InstanceManager::getDefault("DispatcherFrame");
        OptionsMenu* t = new OptionsMenu(d);
        Assert::assertNotNull("exists",t, __FILE__, __LINE__);
        Assert::assertEquals("Stopping Speed Name", "Restricted", d->getStoppingSpeedName(), __FILE__, __LINE__);
        Assert::assertEquals("Use Connectivity Option", false, d->getUseConnectivity(), __FILE__, __LINE__);
        Assert::assertEquals("Trains From Roster", true, d->getTrainsFromRoster(), __FILE__,  __LINE__);
        Assert::assertEquals("Trains From Trains", false, d->getTrainsFromTrains(), __FILE__,  __LINE__);
        Assert::assertEquals("Trains From User", false, d->getTrainsFromUser(), __FILE__,  __LINE__);
        Assert::assertEquals("AutoAllocate", false, d->getAutoAllocate(), __FILE__,  __LINE__);
        Assert::assertEquals("Auto Turnouts", true, d->getAutoTurnouts(), __FILE__,  __LINE__);
        Assert::assertEquals("Occupancy detection", true, d->getHasOccupancyDetection(), __FILE__,  __LINE__);
        Assert::assertEquals("Short Active Train Name", false, d->getShortActiveTrainNames(), __FILE__,  __LINE__);
        Assert::assertEquals("Short Train Name in Block", true, d->getShortNameInBlock(), __FILE__,  __LINE__);
        Assert::assertEquals("Extra Colour for allocate", false, d->getExtraColorForAllocated(), __FILE__,  __LINE__);
        Assert::assertEquals("Name In Allocated Block", false, d->getNameInAllocatedBlock(), __FILE__,  __LINE__);
        Assert::assertEquals("Layout Scale", "G", d->getScale()->getScaleName(), __FILE__,  __LINE__);
        Assert::assertEquals("Use Metres", true, d->getUseScaleMeters(), __FILE__,  __LINE__);
        JUnitUtil::dispose(d);
    }

    // The minimal setup for log4J
    //@Before
    /*public*/ void OptionsMenuTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetProfileManager();
    }

    //@After
    /*public*/ void OptionsMenuTest::tearDown() {
        JUnitUtil::tearDown();
    }
