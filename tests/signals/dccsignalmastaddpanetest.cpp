#include "dccsignalmastaddpanetest.h"
#include "junitappender.h"
#include "junitutil.h"
#include "assert1.h"
#include "dccsignalmast.h"
#include "matrixsignalmast.h"
#include "dccsignalmastaddpane.h"
#include "signalsystemmanager.h"
#include "instancemanager.h"

DccSignalMastAddPaneTest::DccSignalMastAddPaneTest()
{

}
/**
 * @author	Bob Jacobsen Copyright 2018
 */
///*public*/ class DccSignalMastAddPaneTest extends AbstractSignalMastAddPaneTestBase {

    /** {@inheritDoc} */
    //@Override
    /*protected*/ SignalMastAddPane* DccSignalMastAddPaneTest::getOTT() { return new DccSignalMastAddPane(); }

    //@Test
    /*public*/ void DccSignalMastAddPaneTest::testSetMast() {
        DccSignalMast* s1 = new DccSignalMast("IF$dsm:AAR-1946:PL-1-high-abs(77)", "user name");
        // has to have its outputs configured so they exist
        QStringListIterator aspects = s1->getAppearanceMap()->getAspects();
        while (aspects.hasNext()) {
            s1->setOutputForAppearance(aspects.next(), 0);
        }
        Assert::assertEquals("DCC Address should be 77",77, s1->getDccSignalMastAddress(), __FILE__, __LINE__);

        // PacketSendCount default is 3
        Assert::assertEquals("Default should be 3",3, s1->getDccSignalMastPacketSendCount(), __FILE__, __LINE__);
        s1->setDccSignalMastPacketSendCount(1);
        Assert::assertEquals("Should have updated to 1",1, s1->getDccSignalMastPacketSendCount(), __FILE__, __LINE__);

        MatrixSignalMast* m1 = new MatrixSignalMast("IF$xsm:basic:one-low($0001)-3t", "user");

        DccSignalMastAddPane* vp = new DccSignalMastAddPane();

        Assert::assertTrue(vp->canHandleMast(s1), __FILE__, __LINE__);
        Assert::assertFalse(vp->canHandleMast(m1), __FILE__, __LINE__);

        vp->setMast(nullptr);

        vp->setAspectNames(s1->getAppearanceMap(),
            ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("AAR-1946"));
        vp->setMast(s1);

        vp->setAspectNames(m1->getAppearanceMap(),
            ((SignalSystemManager*)InstanceManager::getDefault("SignalSystemManager"))->getSystem("basic"));
        vp->setMast(m1);
        vp->show();
        JUnitAppender::assertErrorMessage("mast was wrong type: IF$xsm:basic:one-low($0001)-3t jmri.implementation.MatrixSignalMast", __FILE__, __LINE__);
    }

    //@Before
    //@Override
    /*public*/ void DccSignalMastAddPaneTest::setUp() {
        JUnitUtil::setUp();
        JUnitUtil::initDefaultUserMessagePreferences();

        JUnitUtil::initInternalTurnoutManager();

        CommandStation* c = new CommandStationO2(this);
//        {
//            @Override
//            /*public*/ boolean sendPacket(byte[] packet, int repeats) {
//                lastSentPacket = packet;
//                sentPacketCount++;
//                return true;
//            }

//            @Override
//            /*public*/ String getUserName() {
//                return null;
//            }

//            @Override
//            /*public*/ String getSystemPrefix() {
//                return "I";
//            }
//        };
        InstanceManager::store(c, "CommandStation");
        lastSentPacket = nullptr;
        sentPacketCount = 0;
    }

    //@After
    //@Override
    /*public*/ void DccSignalMastAddPaneTest::tearDown() {
        JUnitUtil::tearDown();
    }
