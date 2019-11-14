#include "abstractsignalheadtestbase.h"
#include "signalhead.h"
#include "assert1.h"

AbstractSignalHeadTestBase::AbstractSignalHeadTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Base support for testing SignalHead implementations
 *
 * @author	Bob Jacobsen Copyright (C) 2017
 */
///*public*/ abstract class AbstractSignalHeadTestBase {


    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testLit() {
        SignalHead* s = getHeadToTest();

        Assert::assertTrue("initial", s->getLit(), __FILE__, __LINE__);

        s->setLit(false);
        Assert::assertTrue("set", !s->getLit(), __FILE__, __LINE__);

        s->setLit(true);
        Assert::assertTrue("set again", s->getLit(), __FILE__, __LINE__);
    }

    /*private*/ bool AbstractSignalHeadTestBase::validAppearance(int appearance, SignalHead* s) {
        for (int item : s->getValidStates() ) if (item == appearance ) return true;
        return false;
    }

    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testHeld() {
        SignalHead* s = getHeadToTest();

        Assert::assertTrue("initial", ! s->getHeld(), __FILE__, __LINE__);

        s->setHeld(true);
        Assert::assertTrue("set", s->getHeld(), __FILE__, __LINE__);

        s->setHeld(false);
        Assert::assertTrue("set again", ! s->getHeld(), __FILE__, __LINE__);
    }

    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testLitDarkIndependent() {
        SignalHead* s = getHeadToTest();

        int appearance = s->getValidStates()[0];
        if (appearance == SignalHead::DARK) appearance = s->getValidStates()[1];

        s->setAppearance(appearance);
        s->setLit(false);
        Assert::assertTrue("not Lit", ! s->getLit(), __FILE__, __LINE__);
        Assert::assertEquals("not Lit", appearance, s->getAppearance(), __FILE__, __LINE__);

        appearance = s->getValidStates()[1];
        if (validAppearance(SignalHead::DARK, s)) appearance = SignalHead::DARK;

        s->setLit(true);
        s->setAppearance(appearance);
        Assert::assertTrue("Lit", s->getLit(), __FILE__, __LINE__);
        Assert::assertEquals("Lit", appearance, s->getAppearance(), __FILE__, __LINE__);
    }

    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testBaseAppearanceStop() {
        SignalHead* s = getHeadToTest();
        if (! validAppearance(SignalHead::RED, s)) return;
        s->setAppearance(SignalHead::RED);
        Assert::assertTrue( !s->isCleared() , __FILE__, __LINE__);
        Assert::assertTrue(  s->isAtStop() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isShowingRestricting() , __FILE__, __LINE__);
    }
    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testBaseAppearanceClearYellow() {
        SignalHead* s = getHeadToTest();
        if (! validAppearance(SignalHead::YELLOW, s)) return;
        s->setAppearance(SignalHead::YELLOW);
        Assert::assertTrue(  s->isCleared() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isAtStop() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isShowingRestricting() , __FILE__, __LINE__);
    }
    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testBaseAppearanceClearGreen() {
        SignalHead* s = getHeadToTest();
        if (! validAppearance(SignalHead::GREEN, s)) return;
        s->setAppearance(SignalHead::GREEN);
        Assert::assertTrue(  s->isCleared() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isAtStop() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isShowingRestricting() , __FILE__, __LINE__);
    }
    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testBaseAppearanceRestrictingFlashRed() {
        SignalHead* s = getHeadToTest();
        if (! validAppearance(SignalHead::FLASHRED, s)) return;
        s->setAppearance(SignalHead::FLASHRED);
        Assert::assertTrue( !s->isCleared() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isAtStop() , __FILE__, __LINE__);
        Assert::assertTrue(  s->isShowingRestricting() , __FILE__, __LINE__);
    }
    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testBaseAppearanceRestrictingLunar() {
        SignalHead* s = getHeadToTest();
        if (! validAppearance(SignalHead::LUNAR, s)) return;
        s->setAppearance(SignalHead::LUNAR);
        Assert::assertTrue( !s->isCleared() , __FILE__, __LINE__);
        Assert::assertTrue( !s->isAtStop() , __FILE__, __LINE__);
        Assert::assertTrue(  s->isShowingRestricting() , __FILE__, __LINE__);
    }


    //@Test
    /*final*/ /*public*/ void AbstractSignalHeadTestBase::testClearStopRestrictingOverlaps() {
        SignalHead* s = getHeadToTest();
        for (int appearance : s->getValidStates()) {
            checkOverlaps(appearance);
        }
    }

    /*final*/ void AbstractSignalHeadTestBase::checkOverlaps(int appearance) {
        SignalHead* s = getHeadToTest();
        s->setAppearance(appearance);

        Assert::assertTrue(! (s->isCleared() && s->isAtStop()), __FILE__, __LINE__);
        Assert::assertTrue(! (s->isAtStop() && s->isShowingRestricting()), __FILE__, __LINE__);
        Assert::assertTrue(! (s->isShowingRestricting() && s->isCleared()), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractSignalHeadTestBase::testGetBeanType(){
         SignalHead* s = getHeadToTest();
         Assert::assertEquals("bean type",s->getBeanType(), tr("SignalHead"), __FILE__, __LINE__);
    }
