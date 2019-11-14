#include "signalheadsignalmasttest.h"
#include "assert1.h"
#include "junitutil.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "signalheadmanager.h"
#include "signalheadsignalmast.h"
#include "junitappender.h"
#include "signalhead.h"

SignalHeadSignalMastTest::SignalHeadSignalMastTest(QObject *parent) : QObject(parent)
{

}
/**
 * Tests for the SignalHeadSignalMast implementation
 *
 * @author	Bob Jacobsen Copyright (C) 2009
 * updated to JUnit4 2016
 */
///*public*/ class SignalHeadSignalMastTest {

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testSetup() {
        Assert::assertNotNull(InstanceManager::getDefault("SignalHeadManager"), __FILE__, __LINE__);
        Assert::assertNotNull(((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testTwoNameOneHeadCtorOK() {
        new SignalHeadSignalMast("IF$shsm:basic:one-searchlight(IH1)", "user");
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testHeld() {
        SignalMast* m = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight(IH1)", "user");

        Assert::assertTrue(!m->getHeld(), __FILE__, __LINE__);

        m->setHeld(true);
        Assert::assertTrue(m->getHeld(), __FILE__, __LINE__);
        Assert::assertTrue(((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getHeld(), __FILE__, __LINE__);

        m->setHeld(false);
        Assert::assertTrue(!m->getHeld(), __FILE__, __LINE__);
        Assert::assertTrue(!((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getHeld(), __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testLit() {
        SignalMast* m = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight(IH1)", "user");

        Assert::assertTrue(m->getLit(), __FILE__, __LINE__);

        m->setLit(false);
        Assert::assertTrue(!m->getLit(), __FILE__, __LINE__);
        Assert::assertTrue(!((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getLit(), __FILE__, __LINE__);

        m->setLit(true);
        Assert::assertTrue(m->getLit(), __FILE__, __LINE__);
        Assert::assertTrue(((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getLit(), __FILE__, __LINE__);

    }
#if 1
    //@Test
    /*public*/ void SignalHeadSignalMastTest::testTwoNameSe8cHeadCtorOK() {
        // create the SE8c heads
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead1("IH:SE8C:\"255\";\"256\"", this));
//        {
//                    @Override
//                    protected void updateOutput() {
//                    }
//                }
//        );
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead1("IH:SE8C:\"257\";\"258\"",this));
// {
//                    @Override
//                    protected void updateOutput() {
//                    }
//                }
//        );

        // test uses those
        new SignalHeadSignalMast("IF$shsm:AAR-1946:PL-2-high(IH:SE8C:\"255\";\"256\")(IH:SE8C:\"257\";\"258\")", "user");
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testOneNameOneHeadCtorOK() {
        new SignalHeadSignalMast("IF$shsm:basic:one-searchlight(IH1)");
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testOldTwoNameCtorOK() {
        new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testOldOneNameCtorOK() {
        new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1");
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testOldOneNameCtorFailNoSystem() {
        try {
            new SignalHeadSignalMast("IF$shsm:notanaspect:one-searchlight:IH1");
            Assert::fail("should have thrown exception", __FILE__, __LINE__);
        } catch (IllegalArgumentException e1) {
            JUnitAppender::assertErrorMessage("Did not find signal definition: notanaspect", __FILE__, __LINE__);
        } catch (Exception e2) {
            Assert::fail("wrong exception: " + e2.getMessage(), __FILE__, __LINE__);
        }
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testAspects() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");

        s->setAspect("Clear");
        Assert::assertEquals("check clear", "Clear", s->getAspect(), __FILE__, __LINE__);
        s->setAspect("Stop");
        Assert::assertEquals("check stop", "Stop", s->getAspect(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testAspectAttributes() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");

        s->setAspect("Clear");
        Assert::assertEquals("../../../resources/icons/smallschematics/aspects/AAR-1946/SL-1-high-abs/rule-281.gif",
                s->getAppearanceMap()->getProperty("Clear", "imagelink"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testAspectNotSet() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");

        Assert::assertNull("check null", s->getAspect(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testAspectFail() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");

        s->setAspect("Clear");

        try {
            s->setAspect("Not An Aspect, I Hope");
            Assert::fail("should have thrown exception", __FILE__, __LINE__);
        } catch (IllegalArgumentException e1) {
            JUnitAppender::assertWarnMessage("attempting to set invalid aspect: Not An Aspect, I Hope on mast: user");
        } catch (Exception e2) {
            Assert::fail("wrong exception: " + e2.getMessage(), __FILE__, __LINE__);
        }

        Assert::assertEquals("check clear", "Clear", s->getAspect(), __FILE__, __LINE__); // unchanged after failed request
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testConfigureOneSearchLight() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:one-searchlight:IH1", "user");

        s->setAspect("Clear");
        Assert::assertEquals("check green", SignalHead::GREEN,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getAppearance(), __FILE__, __LINE__);

        s->setAspect("Approach");
        Assert::assertEquals("check yellow", SignalHead::YELLOW,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getAppearance(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testConfigureTwoSearchLight() {
        SignalMast* s = new SignalHeadSignalMast("IF$shsm:basic:two-searchlight:IH1:IH2", "user");

        s->setAspect("Clear");
        Assert::assertEquals("Clear head 1 green", SignalHead::GREEN,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Clear head 2 red", SignalHead::RED,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH2")->getAppearance(), __FILE__, __LINE__);

        s->setAspect("Diverging Approach");
        Assert::assertEquals("Diverging Approach head 1 red", SignalHead::RED,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH1")->getAppearance(), __FILE__, __LINE__);
        Assert::assertEquals("Diverging Approach head 2 yellow", SignalHead::YELLOW,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH2")->getAppearance(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testOneSearchLightViaManager() {
        SignalMast* s = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast("IF$shsm:basic:one-searchlight:IH2");

        s->setAspect("Clear");
        Assert::assertEquals("check green", SignalHead::GREEN,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH2")->getAppearance(), __FILE__, __LINE__);

        s->setAspect("Approach");
        Assert::assertEquals("check yellow", SignalHead::YELLOW,
                ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead("IH2")->getAppearance(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SignalHeadSignalMastTest::testSignalSystemLink() {
        SignalMast* s = ((SignalMastManager*)InstanceManager::getDefault("SignalMastManager"))->provideSignalMast("IF$shsm:basic:one-searchlight:IH2");

        SignalSystem* sy = s->getSignalSystem();
        Assert::assertNotNull(sy, __FILE__, __LINE__);

        Assert::assertEquals(QVariant("Proceed"), s->getSignalSystem()->getProperty("Clear", "indication"), __FILE__, __LINE__);
    }
#endif
    // from here down is testing infrastructure

    // The minimal setup for log4J
    //@Before
    /*public*/ void SignalHeadSignalMastTest::setUp() {
        JUnitUtil::setUp();
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead1("IH1", this));
//        {
//                    @Override
//                    protected void updateOutput() {
//                    }
//                }
//        );
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead1("IH2", this));
//        {
//                    @Override
//                    protected void updateOutput() {
//                    }
//                }
//        );
        ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->Register(
                new DefaultSignalHead1("IH3", this));
//        {
//                    @Override
//                    protected void updateOutput() {
//                    }
//                }
//        );
    }

    //@After
    /*public*/ void SignalHeadSignalMastTest::tearDown() {
        JUnitUtil::tearDown();
    }
