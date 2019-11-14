#include "abstractsignalmastaddpanetestbase.h"
#include "junitutil.h"
#include "assert1.h"
#include "signalmastaddpane.h"

AbstractSignalMastAddPaneTestBase::AbstractSignalMastAddPaneTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Base-class of the
 * tests of individual implementations of {@link SignalMastAddPane} subclasses.
 * <p>
 * See {@link SignalMastAddPaneTest} for tests of the overall
 * operation of {@link SignalMastAddPane} services.
 *
 * @author	Bob Jacobsen Copyright 2018
 */
//abstract /*public*/ class AbstractSignalMastAddPaneTestBase {

    /**
     * Subclass provides Object Under Test
     */
//    abstract protected SignalMastAddPane getOTT();

    //@Test
    /*public*/ void AbstractSignalMastAddPaneTestBase::testInfoMethods() {
        SignalMastAddPane* testPane = getOTT();

        Assert::assertNotNull(testPane->getPaneName(), __FILE__, __LINE__);
        Assert::assertFalse(testPane->getPaneName().isEmpty(), __FILE__, __LINE__);
    }

    //@Before
    /*public*/ void AbstractSignalMastAddPaneTestBase::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();
    }

    //@After
    /*public*/ void AbstractSignalMastAddPaneTestBase::tearDown() {
        JUnitUtil::tearDown();
    }
