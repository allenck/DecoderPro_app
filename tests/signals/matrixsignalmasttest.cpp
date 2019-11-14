#include "matrixsignalmasttest.h"
#include "assert1.h"
#include "matrixsignalmast.h"
#include "instancemanager.h"
#include <QMap>

MatrixSignalMastTest::MatrixSignalMastTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the MatrixSignalMast*  implementation.
 *
 * @author	Egbert Broerse Copyright (C) 2016, 2019
 */
// /*public*/ class MatrixSignalMastTest {

    //@Test
    /*public*/ void MatrixSignalMastTest::testSetup() {
        // provide 3 turnouts:
        Turnout* it11 = InstanceManager::turnoutManagerInstance()->provideTurnout("11");
        Turnout* it12 = InstanceManager::turnoutManagerInstance()->provideTurnout("12");
        Turnout* it13 = InstanceManager::turnoutManagerInstance()->provideTurnout("13");

        Assert::assertEquals("it11 before", Turnout::UNKNOWN, it11->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("it12 before", Turnout::UNKNOWN, it12->getCommandedState(), __FILE__, __LINE__);
        Assert::assertEquals("it13 before", Turnout::UNKNOWN, it13->getCommandedState(), __FILE__, __LINE__);
    }

    //@Test
    //@SuppressWarnings("unused") // it11 etc. are indirectly used as NamedBeans IT11 etc.
    /*public*/ void MatrixSignalMastTest::testCtor1() {
        // provide 3 turnouts:
        Turnout* it11 = InstanceManager::turnoutManagerInstance()->provideTurnout("11");
        Turnout* it12 = InstanceManager::turnoutManagerInstance()->provideTurnout("12");
        Turnout* it13 = InstanceManager::turnoutManagerInstance()->provideTurnout("13");

        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");
        m->setBitNum(3);
        m->setOutput("output1", "IT11");
        m->setOutput("output2", "IT12");
        m->setOutput("output3", "IT13");

        Assert::assertEquals("system name", "IF$xsm:basic:one-low($0001)-3t", m->getSystemName(), __FILE__, __LINE__);
        Assert::assertEquals("user name", "user", m->getUserName(), __FILE__, __LINE__);
        //System->out.println(it11->getDisplayName(DisplayOptions.USERNAME_SYSTEMNAME)); //debug
        Assert::assertEquals("output2", "IT12", m->outputsToBeans.value("output2")->getName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void MatrixSignalMastTest::testHeld() {
        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        Assert::assertFalse(m->getHeld(), __FILE__, __LINE__);

        m->setHeld(true);
        Assert::assertTrue(m->getHeld(), __FILE__, __LINE__);

        m->setHeld(false);
        Assert::assertFalse(m->getHeld(), __FILE__, __LINE__);
    }

    //@Test
    //@SuppressWarnings("unused") // it11 etc. are indirectly used as NamedBeans IT11 etc.
    /*public*/ void MatrixSignalMastTest::testLit() {
        // provide 3 turnouts:
        Turnout* it11 = InstanceManager::turnoutManagerInstance()->provideTurnout("11");
        Turnout* it12 = InstanceManager::turnoutManagerInstance()->provideTurnout("12");
        Turnout* it13 = InstanceManager::turnoutManagerInstance()->provideTurnout("13");

        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");
        m->setBitNum(3);
        m->setOutput("output1", "IT11"); // Note: "IT" added to name by system
        m->setOutput("output2", "IT12");
        m->setOutput("output3", "IT13");

        m->setBitstring("Clear", QString("111"));
        m->setBitstring("Approach", QString("100"));
        m->setBitstring("Stop", QString("001"));
        m->setBitstring("Unlit", QString("000"));

        m->setAllowUnLit(true);
        m->setUnLitBits(QString("000"));

        m->aspect = "Clear"; // define some initial aspect before setting any aspect
        // wait for outputs and outputbits to be set

        Assert::assertTrue(m->getLit(), __FILE__, __LINE__);

        m->setLit(false);
        Assert::assertTrue(!m->getLit(), __FILE__, __LINE__);

        m->setLit(true);
        Assert::assertTrue(m->getLit(), __FILE__, __LINE__);
    }

    //@Test
    //@SuppressWarnings("unused") // it11 etc. are indirectly used as NamedBeans IT11 etc.
    /*public*/ void MatrixSignalMastTest::testAspects() {
        // provide 3 turnouts:
        Turnout* it11 = InstanceManager::turnoutManagerInstance()->provideTurnout("11");
        Turnout* it12 = InstanceManager::turnoutManagerInstance()->provideTurnout("12");
        Turnout* it13 = InstanceManager::turnoutManagerInstance()->provideTurnout("13");

        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");
        m->setBitNum(3);
        m->setOutput("output1", "IT11");
        m->setOutput("output2", "IT12");
        m->setOutput("output3", "IT13");

        m->setBitstring("Clear", QString("111")); // used for test below
        m->setBitstring("Approach", QString("100"));
        m->setBitstring("Stop", QString("001")); // used for test below
        m->setBitstring("Unlit", QString("000"));

        m->setAllowUnLit(true);
        m->setUnLitBits(QString("000"));
        m->setAspectEnabled("Clear");
        m->setAspectEnabled("Approach");
        m->setAspectEnabled("Stop");
        m->setAspectEnabled("Unlit");

        m->aspect = "Stop"; // define some initial aspect before setting any aspect
        m->setMatrixMastCommandDelay(0);
        // wait for outputs and outputbits to be set

        //log.debug(java.util.Arrays.toString(m->getBitsForAspect("Stop")));
        Assert::assertEquals("check bitarray for Stop", "[0, 0, 1]", QString(m->getBitsForAspect("Stop")), __FILE__, __LINE__);

        m->setAspect("Clear");
        Assert::assertEquals("check Clear", "Clear", m->getAspect(), __FILE__, __LINE__);
        //JUnitUtil.waitFor( ()->{ return it11->getCommandedState() == Turnout::CLOSED; }, "it11 for Clear" , __FILE__, __LINE__);
        JUnitUtil::waitFor(new ReleaseUntilO18(it11, Turnout::CLOSED, this), "it11 for Clear", __FILE__, __LINE__);
        m->setAspect("Stop");
        Assert::assertEquals("check Stop", "Stop", m->getAspect(), __FILE__, __LINE__);
        //JUnitUtil.waitFor( ()->{ return it12->getCommandedState() == Turnout::THROWN; }, "it12 for Stop" , __FILE__, __LINE__);
        JUnitUtil::waitFor(new ReleaseUntilO18(it12, Turnout::THROWN, this), "it11 for Stop", __FILE__, __LINE__);
        // it12 state is more fragile
    }

    /*public*/ void MatrixSignalMastTest::testAspectAttributes() {
        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        m->setAspect("Clear");
        Assert::assertEquals("../../../resources/icons/smallschematics/aspects/AAR-1946/SL-1-low/rule-287.gif",
                m->getAppearanceMap()->getProperty("Clear", "imagelink"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void MatrixSignalMastTest::testAspectNotSet() {
        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        Assert::assertNull("check null", m->getAspect(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void MatrixSignalMastTest::testSetDelay() {
        MatrixSignalMast*  m = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        Assert::assertEquals("initial mast delay 0", 0, m->getMatrixMastCommandDelay(), __FILE__, __LINE__);
        m->setMatrixMastCommandDelay(150);
        Assert::assertEquals("get new mast delay", 150, m->getMatrixMastCommandDelay(), __FILE__, __LINE__);
        m->setMatrixMastCommandDelay(0);
    }

    // from here down is testing infrastructure

    // The minimal setup for log4J
    //@Before
    /*public*/ void MatrixSignalMastTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::resetInstanceManager();
    }

    //@After
    /*public*/ void MatrixSignalMastTest::tearDown() {
        JUnitUtil::tearDown();
    }
