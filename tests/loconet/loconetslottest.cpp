#include "loconetslottest.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"
#include "slotmanager.h"
#include "assert1.h"
#include "loconetmessage.h"
#include "junitappender.h"

LocoNetSlotTest::LocoNetSlotTest(QObject *parent) : QObject(parent)
{

}

// /*public*/ class LocoNetSlotTest {

//@Test
/*public*/ void LocoNetSlotTest::testGetSlotSend() {
    SlotManager* slotmanager = new SlotManager(lnis);
//    SlotListener p2 = new SlotListener() {
//        @Override
//        /*public*/ void notifyChangedSlot(LocoNetSlot l) {
//        }
//    };
    SlotListenerO2* p2 = new SlotListenerO2(this);
    slotmanager->slotFromLocoAddress(21, p2);
    Assert::assertEquals("slot request message",
            "BF 00 15 00",
            lnis->outbound.at(lnis->outbound.size() - 1)->toString().toUpper(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testCTor(){
    LocoNetSlot* t = new LocoNetSlot(5);
    Assert::assertNotNull("exists",t, __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testMessageCTor() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertNotNull("exists",t, __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testGetSlot(){
    LocoNetSlot* t = new LocoNetSlot(5);
    Assert::assertEquals("slot number",5,t->getSlot(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testSetSlot() throw (LocoNetException){
    QVector<int> ia = QVector<int>() <<0xEF<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60 ;
    LocoNetMessage* lm = new LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(1);

    bool exceptionCaught = false;
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("slot is 1", 1, t->getSlot(), __FILE__, __LINE__);
    Assert::assertEquals("Slot status is 0x30", 0x30, t->slotStatus(), __FILE__, __LINE__);
    Assert::assertEquals("Slot decoder type is 0x03", 3, t->decoderType(), __FILE__, __LINE__);
    Assert::assertEquals("Address is 5544", 5544, t->locoAddr(), __FILE__, __LINE__);
    Assert::assertEquals("Slot speed is 0", 0, t->speed(), __FILE__, __LINE__);
    Assert::assertEquals("Slot dirf is 0", 0, t->dirf(), __FILE__, __LINE__);
    Assert::assertEquals("Slot trk is 0x47", 0x47, t->getTrackStatus(), __FILE__, __LINE__);
    Assert::assertEquals("Slot status2 is 0", 0, t->ss2(), __FILE__, __LINE__);
    Assert::assertEquals("slot consist status is 0", 0, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("Slot snd is 0", 0, t->snd(), __FILE__, __LINE__);
    Assert::assertEquals("slot throttle id is 0", 0, t->id(), __FILE__, __LINE__);

    ia[1] = 0x0f;
    lm = new LocoNetMessage(ia);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);

    ia[1] = 0x0E;
    ia[2] = 3;
    lm = new LocoNetMessage(ia);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);

    JUnitAppender::assertErrorMessage("Asked to handle message not for this slot (1) EF 0E 03 33 28 00 00 47 00 2B 00 00 00 60",__FILE__, __LINE__);

    ia[0] = 0xE7;
    ia[2] = 1;
    lm = new LocoNetMessage(ia);
    qint64 lastTime = t->getLastUpdateTime();
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertNotEquals(QString("update time was updated"), QDateTime::fromMSecsSinceEpoch(lastTime).toString(), QDateTime::fromMSecsSinceEpoch(t->getLastUpdateTime()).toString(),__FILE__, __LINE__);

    QVector<int> ib = QVector<int>() <<0x81<< 0x00;
    lm = new LocoNetMessage(ib);
    try {
        t->setSlot(lm); // we are checking to make sure this throws an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertTrue("do expect an exception", exceptionCaught, __FILE__, __LINE__);

    exceptionCaught = false;
    QVector<int> ic = QVector<int>() <<0xb5<< 0x01<< 0x25<< 0;
    lm = new LocoNetMessage(ic);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("status updated", 0x20, t->slotStatus(), __FILE__, __LINE__);

    QVector<int> id = QVector<int>() <<0xa2<< 0x01<< 0x35<< 0x00;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("F5-F8 updated", 5, t->snd(), __FILE__, __LINE__);

    id[0] = 0xa0;
    id[2] = 0x7E;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Spd updated", 0x7e, t->speed(), __FILE__, __LINE__);

    id[0] = 0xa1;
    id[2] = 0x53;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x13, t->dirf(), __FILE__, __LINE__);

    QVector<int> ie = QVector<int>() <<0xb5<< 0x01<< 0x40<< 0;
    LocoNetMessage* lm2 = new LocoNetMessage(ie);
    t->setSlot(lm2);
    Assert::assertEquals("slot consist status is ", 0x40, t->consistStatus(), __FILE__, __LINE__);

    id[2] = 0x08;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x08, t->dirf(), __FILE__, __LINE__);

    id[2] = 0x37;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x17, t->dirf(), __FILE__, __LINE__);

    ie[2] = 0x48;
    lm2 = new LocoNetMessage(ie);
    t->setSlot(lm2);
    Assert::assertEquals("slot consist status is ", 0x48, t->consistStatus(), __FILE__, __LINE__);

    id[2] = 0x08;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x08, t->dirf(), __FILE__, __LINE__);

    id[2] = 0x37;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x17, t->dirf(), __FILE__, __LINE__);

    ie[2] = 0x08;
    lm2 = new LocoNetMessage(ie);
    t->setSlot(lm2);
    Assert::assertEquals("slot consist status is ", 0x08, t->consistStatus(), __FILE__, __LINE__);

    id[2] = 0x08;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x08, t->dirf(), __FILE__, __LINE__);

    id[2] = 0x37;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x37, t->dirf(), __FILE__, __LINE__);

    ie[2] = 0x00;
    lm2 = new LocoNetMessage(ie);
    t->setSlot(lm2);
    Assert::assertEquals("slot consist status is ", 0x0, t->consistStatus(), __FILE__, __LINE__);

    id[2] = 0x08;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x08, t->dirf(), __FILE__, __LINE__);

    id[2] = 0x37;
    lm = new LocoNetMessage(id);
    try {
        t->setSlot(lm); // we are checking to make sure this does not throw an
                       // exception.
    } catch (LocoNetException e) {
        exceptionCaught = true;
    }
    Assert::assertFalse("do not expect an exception", exceptionCaught, __FILE__, __LINE__);
    Assert::assertEquals("Dirf updated", 0x37, t->dirf(), __FILE__, __LINE__);

}

//@Test
/*public*/ void LocoNetSlotTest::testDecoderType() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("decoder type",LnConstants::DEC_MODE_128,t->decoderType(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testSlotStatus() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("Slot Status",LnConstants::LOCO_IN_USE,t->slotStatus(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testss2() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("Slot Status",0x00,t->ss2(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testConsistStatus() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("Consist Status",LnConstants::CONSIST_NO,t->consistStatus(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testIsForward() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertTrue("is Forward",t->isForward(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testIsF0() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F0",t->isF0(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF1() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F1",t->isF1(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testIsF2() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F2",t->isF2(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF3() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00 << 0x60 ;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F3",t->isF3(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF4() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F4",t->isF4(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF5() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F5",t->isF5(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF6() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F6",t->isF6(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF7() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F7",t->isF7(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testIsF8() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F8",t->isF8(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF9() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F9",t->isF9(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF10() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F10",t->isF10(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF11() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F11",t->isF11(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF12() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F12",t->isF12(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF13() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F13",t->isF13(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF14() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F14",t->isF14(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF15() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F15",t->isF15(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF16() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F16",t->isF16(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF17() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F17",t->isF17(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF18() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F18",t->isF18(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF19() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F19",t->isF19(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF20() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F20",t->isF20(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF21() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F21",t->isF21(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF22() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F22",t->isF22(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF23() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F23",t->isF23(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF24() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F24",t->isF24(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF25() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F25",t->isF25(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF26() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F26",t->isF26(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF27() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F27",t->isF27(), __FILE__, __LINE__);
}
//@Test
/*public*/ void LocoNetSlotTest::testIsF28() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertFalse("is F28",t->isF28(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testLocoAddr() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("address",5544,t->locoAddr(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testSpeed() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("speed",0,t->speed(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testDirf() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("directions and Functions",0x00,t->dirf(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testSnd() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("snd",0x00,t->snd(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testID() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    Assert::assertEquals("ID",0x00,t->id(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testWriteSlot() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    LocoNetMessage* lm2 = t->writeSlot();
    Assert::assertEquals("Opcode",LnConstants::OPC_WR_SL_DATA,lm2->getOpCode(), __FILE__, __LINE__);
    for(int i = 1;i<=12;i++){
        Assert::assertEquals("Element " + i,lm.getElement(i),lm2->getElement(i),__FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetSlotTest::testWriteThrottleID() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage lm = LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(new LocoNetMessage(lm));
    LocoNetMessage* lm2 = t->writeThrottleID(0x0171);
    Assert::assertEquals("Opcode",LnConstants::OPC_WR_SL_DATA,lm2->getOpCode(), __FILE__, __LINE__);
    for(int i = 1;i<=10;i++){
        Assert::assertEquals("Element " + i,lm.getElement(i),lm2->getElement(i),__FILE__, __LINE__);
    }
    Assert::assertEquals("Element 11",0x71,lm2->getElement(11),__FILE__, __LINE__);
    Assert::assertEquals("Element 12",0x02,lm2->getElement(12),__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::testConsistingStateVsSpeedAccept() throw (LocoNetException) {
    QVector<int> ia = QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x33<< 0x28<< 0x00<< 0x00<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;
    LocoNetMessage* lm = new LocoNetMessage(ia);
    LocoNetSlot* t = new LocoNetSlot(lm);
    Assert::assertEquals("Consist-mode is unconsisted", LnConstants::CONSIST_NO, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("Speed Set from slot read",0, t->speed(), __FILE__, __LINE__);
    QVector<int> ib = QVector<int>() <<0xA0<< 1<< 14<< 0;
    lm = new LocoNetMessage(ib);
    t->setSlot(lm);
    Assert::assertEquals("Speed Set for Unconsisted slot",14, t->speed(), __FILE__, __LINE__);
    QVector<int> id = QVector<int>() <<0xA1<< 1<< 2<< 0;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Function 1 set for Unconsisted slot",2, t->dirf(), __FILE__, __LINE__);
    id[2] = 0x20;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Change direction and F1 for unconsisted slot", 0x20, t->dirf(), __FILE__, __LINE__);

    QVector<int> ic =QVector<int>() <<0xE7<< 0x0E<< 0x01<< 0x0b<< 0x28<< 0x12<< 0x02<< 0x47<<
        0x00<< 0x2B<< 0x00<< 0x00<< 0x00<< 0x60;   // make slot consist_top
    lm = new LocoNetMessage(ic);
    t->setSlot(lm);
    Assert::assertEquals("Consist-mode is consist-top", LnConstants::CONSIST_TOP, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("Speed Set for consist-top from slot read",18, t->speed(), __FILE__, __LINE__);
    Assert::assertEquals("OPC_LOCO_SPD from slot read for consist-top",2, t->dirf(), __FILE__, __LINE__);

    ib[2] = 3;
    lm = new LocoNetMessage(ib);
    t->setSlot(lm);
    Assert::assertEquals("OPC_LOCO_SPD accepted for consist-top",3, t->speed(), __FILE__, __LINE__);
    id[2] = 7;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Function F1-F3 set for consist-top slot",7, t->dirf(), __FILE__, __LINE__);
    id[2] = 0x22;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Change direction and F1 & F3 for consist-top slot", 0x22, t->dirf(), __FILE__, __LINE__);

    ic[3] = 0x4b;   // make slot consist_mid, common
    lm = new LocoNetMessage(ic);
    t->setSlot(lm);
    Assert::assertEquals("Consist-mode is consist-mid", LnConstants::CONSIST_MID, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("'Speed' (slot pointer) set for consist-mid from slot read",18, t->speed(), __FILE__, __LINE__);
    ib[2] = 7;
    lm = new LocoNetMessage(ib);
    t->setSlot(lm);
    Assert::assertEquals("OPC_LOCO_SPD ignored when consist-mid",18, t->speed(), __FILE__, __LINE__);
    id[2] = 19;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Function F0, F2, F1 set for consist-mid slot",19, t->dirf(), __FILE__, __LINE__);
    id[2] = 0x27;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Change F0, F3 but NOT direction for consist-mid slot", 0x07, t->dirf(), __FILE__, __LINE__);

    ic[3] = 0x43;   // make slot consist_sub, common
    ic[6] = 0x28;   // DIRF: reverse, F4 on
    lm = new LocoNetMessage(ic);
    t->setSlot(lm);
    Assert::assertEquals("Consist-mode is consist-sub", LnConstants::CONSIST_SUB, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("'Speed' (slot pointer) set for consist-sub from slot read",18, t->speed(), __FILE__, __LINE__);
    Assert::assertEquals("DIRF for consist-sub from slot read", 0x28, t->dirf(), __FILE__, __LINE__);
    ib[2] = 9;
    lm = new LocoNetMessage(ib);
    t->setSlot(lm);
    Assert::assertEquals("OPC_LOCO_SPD ignored when consist-mid",18, t->speed(), __FILE__, __LINE__);
    id[2] = 0x3f;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Functions F0, F4-F1 set but not direction for consist-mid slot",63, t->dirf(), __FILE__, __LINE__);
    id[2] = 0x02;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Change F0, F4-F3, F1 for consist-top slot", 0x22, t->dirf(), __FILE__, __LINE__);

    ic[6] = 0x27;   // make slot DIRF direction reversed, F3-F1 on
    lm = new LocoNetMessage(ic);
    t->setSlot(lm);
    Assert::assertEquals("Consist-mode is consist-sub", LnConstants::CONSIST_SUB, t->consistStatus(), __FILE__, __LINE__);
    Assert::assertEquals("'Speed' (slot pointer) set for consist-sub from slot read",18, t->speed(), __FILE__, __LINE__);
    Assert::assertEquals("dirf is 0x27 from slot read", 0x27, t->dirf(), __FILE__, __LINE__);
    ib[2] = 9;
    lm = new LocoNetMessage(ib);
    t->setSlot(lm);
    Assert::assertEquals("OPC_LOCO_SPD ignored when consist-mid",18, t->speed(), __FILE__, __LINE__);
    id[2] = 0x00;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Functions F0, F4-F1 set but not direction for consist-mid slot",0x20, t->dirf(), __FILE__, __LINE__);
    id[2] = 0x3F;
    lm = new LocoNetMessage(id);
    t->setSlot(lm);
    Assert::assertEquals("Change F0, F4-F1, for consist-top slot", 0x3F, t->dirf(), __FILE__, __LINE__);

}


//@Test
/*public*/ void LocoNetSlotTest::checkFunctionMessage() {
    LocoNetSlot* s = new LocoNetSlot(15);
    Assert::assertEquals("initial slot function value - F9", false, s->localF9,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F10", false, s->localF10,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F11", false, s->localF11,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F12", false, s->localF12,__FILE__, __LINE__);
    s->functionMessage(0xA1L);
    Assert::assertEquals("F9 now", true, s->localF9,__FILE__, __LINE__);
    s->functionMessage(0xA0L);
    Assert::assertEquals("F9 now", false, s->localF9,__FILE__, __LINE__);
    s->functionMessage(0xA2L);
    Assert::assertEquals("F10 now", true, s->localF10,__FILE__, __LINE__);
    s->functionMessage(0xA0L);
    Assert::assertEquals("F10 now", false, s->localF10,__FILE__, __LINE__);
    s->functionMessage(0xA4L);
    Assert::assertEquals("F11 now", true, s->localF11,__FILE__, __LINE__);
    s->functionMessage(0xA0L);
    Assert::assertEquals("F11 now", false, s->localF11,__FILE__, __LINE__);
    s->functionMessage(0xA8L);
    Assert::assertEquals("F12 now", true, s->localF12,__FILE__, __LINE__);
    s->functionMessage(0xA0L);
    Assert::assertEquals("F12 now", false, s->localF12,__FILE__, __LINE__);

    Assert::assertEquals("initial slot function value - F13", false, s->localF13,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F14", false, s->localF14,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F15", false, s->localF15,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F16", false, s->localF16,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F17", false, s->localF17,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F18", false, s->localF18,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F19", false, s->localF19,__FILE__, __LINE__);
    Assert::assertEquals("initial slot function value - F20", false, s->localF20,__FILE__, __LINE__);
    s->functionMessage(0xDE01L);
    Assert::assertEquals("F13 now", true,  s->localF13,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F13 now", false, s->localF13,__FILE__, __LINE__);
    s->functionMessage(0xDE02L);
    Assert::assertEquals("F14 now", true,  s->localF14,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F14 now", false, s->localF14,__FILE__, __LINE__);
    s->functionMessage(0xDE04L);
    Assert::assertEquals("F15 now", true,  s->localF15,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F15 now", false, s->localF15,__FILE__, __LINE__);
    s->functionMessage(0xDE08L);
    Assert::assertEquals("F16 now", true,  s->localF16,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F16 now", false, s->localF16,__FILE__, __LINE__);
    s->functionMessage(0xDE10L);
    Assert::assertEquals("F17 now", true,  s->localF17,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F17 now", false, s->localF17,__FILE__, __LINE__);
    s->functionMessage(0xDE20L);
    Assert::assertEquals("F18 now", true,  s->localF18,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F18 now", false, s->localF18,__FILE__, __LINE__);
    s->functionMessage(0xDE40L);
    Assert::assertEquals("F19 now", true,  s->localF19,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F19 now", false, s->localF19,__FILE__, __LINE__);
    s->functionMessage(0xDE80L);
    Assert::assertEquals("F20 now", true,  s->localF20,__FILE__, __LINE__);
    s->functionMessage(0xDE00L);
    Assert::assertEquals("F20 now", false, s->localF20,__FILE__, __LINE__);
    s->functionMessage(0XDF01L);
    Assert::assertEquals("F21 now", true,  s->localF21,__FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F21 now", false, s->localF21, __FILE__, __LINE__);
    s->functionMessage(0XDF02L);
    Assert::assertEquals("F22 now", true,  s->localF22, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F22 now", false, s->localF22, __FILE__, __LINE__);
    s->functionMessage(0XDF04L);
    Assert::assertEquals("F23 now", true,  s->localF23, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F23 now", false, s->localF23, __FILE__, __LINE__);
    s->functionMessage(0XDF08L);
    Assert::assertEquals("F24 now", true,  s->localF24, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F24 now", false, s->localF24, __FILE__, __LINE__);
    s->functionMessage(0XDF10L);
    Assert::assertEquals("F25 now", true,  s->localF25, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F25 now", false, s->localF25, __FILE__, __LINE__);
    s->functionMessage(0XDF20L);
    Assert::assertEquals("F26 now", true,  s->localF26, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F26 now", false, s->localF26, __FILE__, __LINE__);
    s->functionMessage(0XDF40L);
    Assert::assertEquals("F27 now", true,  s->localF27, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F27 now", false, s->localF27, __FILE__, __LINE__);
    s->functionMessage(0XDF80L);
    Assert::assertEquals("F28 now", true,  s->localF28, __FILE__, __LINE__);
    s->functionMessage(0XDF00L);
    Assert::assertEquals("F28 now", false, s->localF28, __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::checkFastClockGetSetMethods() {
    LocoNetSlot* s = new LocoNetSlot(15);
    s->setFcFracMins(12);
    JUnitAppender::assertErrorMessage("setFcFracMins invalid for slot 15",__FILE__, __LINE__);
    s->setFcHours(1);
    JUnitAppender::assertErrorMessage("setFcHours invalid for slot 15",__FILE__, __LINE__);
    s->setFcMinutes(12);
    JUnitAppender::assertErrorMessage("setFcMinutes invalid for slot 15",__FILE__, __LINE__);
    s->setFcDays(5);
    JUnitAppender::assertErrorMessage("setFcDays invalid for slot 15",__FILE__, __LINE__);
    s->setFcRate(0);
    JUnitAppender::assertErrorMessage("setFcRate invalid for slot 15",__FILE__, __LINE__);

    s->getFcFracMins();
    JUnitAppender::assertErrorMessage("getFcFracMins invalid for slot 15",__FILE__, __LINE__);
    s->getFcHours();
    JUnitAppender::assertErrorMessage("getFcHours invalid for slot 15",__FILE__, __LINE__);
    s->getFcMinutes();
    JUnitAppender::assertErrorMessage("getFcMinutes invalid for slot 15",__FILE__, __LINE__);
    s->getFcDays();
    JUnitAppender::assertErrorMessage("getFcDays invalid for slot 15",__FILE__, __LINE__);
    s->getFcRate();
    JUnitAppender::assertErrorMessage("getFcRate invalid for slot 15",__FILE__, __LINE__);



    s = new LocoNetSlot(123);
    Assert::assertEquals("FcFracMins initial value", 0x3FFF, s->getFcFracMins(), __FILE__, __LINE__);
    Assert::assertEquals("FcMinutes initial value", 53, s->getFcMinutes(), __FILE__, __LINE__);
    Assert::assertEquals("FcHours initial value", 0, s->getFcHours(), __FILE__, __LINE__);
    Assert::assertEquals("FcDays initial value", 0, s->getFcDays(), __FILE__, __LINE__);
    s->setFcFracMins(18);
    s->setFcMinutes(41);
    s->setFcHours(2);
    s->setFcDays(3);
    Assert::assertEquals("getFcFracMins", 18, s->getFcFracMins(), __FILE__, __LINE__);
    Assert::assertEquals("getFcMinutes", 41, s->getFcMinutes(), __FILE__, __LINE__);
    Assert::assertEquals("getFcHours", 2, s->getFcHours(), __FILE__, __LINE__);
    Assert::assertEquals("getFcDays", 3, s->getFcDays(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetSlotTest::checkSetAndGetTrackStatus() {
    LocoNetSlot* s = new LocoNetSlot(19);
    Assert::assertEquals("Checking default track status",7   , s->getTrackStatus(), __FILE__, __LINE__);
    for (int i = 0; i < 256; ++i) {
        s->setTrackStatus(i);
        Assert::assertEquals("checking set/get track status for status "+i, i, s->getTrackStatus(), __FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetSlotTest::checkIsF0ToF8() {
    SlotManager* sm;
    LocoNetSystemConnectionMemo* memo;

    sm = new SlotManager(lnis);
    memo = new LocoNetSystemConnectionMemo(lnis, sm);
    sm->setSystemConnectionMemo(memo);

    LocoNetSlot* s = new LocoNetSlot(10);
    Assert::assertEquals("slot number assigned correctly", 10, s->getSlot(),__FILE__, __LINE__);
    LocoNetMessage* m = new LocoNetMessage(14);

    m->setOpCode(0xef);
    m->setElement(1, 0x0e);
    m->setElement(2, 0x0A);
    m->setElement(3, 0x00);
    m->setElement(4, 0x00);
    m->setElement(5, 0x00);
    m->setElement(7, 0x00);
    m->setElement(8, 0x00);
    m->setElement(9, 0x00);
    m->setElement(10, 0x00);
    m->setElement(11, 0x00);
    m->setElement(12, 0x00);
    m->setElement(13, 0x00);
    for (int i = 0; i < 128; ++i) {
        m->setElement(6, i);
        try {
            s->setSlot(m);
        } catch (LocoNetException e) {
            Assert::fail("unexpected exception " + e.getMessage(),__FILE__, __LINE__);
        }
        Assert::assertEquals("F0 value from LocoNet Message, loop "+i,((i & 0x10)== 0x10), s->isF0(), __FILE__, __LINE__);
        Assert::assertEquals("F1 value from LocoNet Message, loop "+i,((i & 0x01)== 0x01), s->isF1(), __FILE__, __LINE__);
        Assert::assertEquals("F2 value from LocoNet Message, loop "+i,((i & 0x02)== 0x02), s->isF2(), __FILE__, __LINE__);
        Assert::assertEquals("F3 value from LocoNet Message, loop "+i,((i & 0x04)== 0x04), s->isF3(), __FILE__, __LINE__);
        Assert::assertEquals("F4 value from LocoNet Message, loop "+i,((i & 0x08)== 0x08), s->isF4(), __FILE__, __LINE__);
        Assert::assertFalse ("F5 value from LocoNet Message, loop "+i, s->isF5(), __FILE__, __LINE__);
        Assert::assertFalse ("F6 value from LocoNet Message, loop "+i, s->isF6(), __FILE__, __LINE__);
        Assert::assertFalse ("F7 value from LocoNet Message, loop "+i, s->isF7(), __FILE__, __LINE__);
        Assert::assertFalse ("F8 value from LocoNet Message, loop "+i, s->isF8(), __FILE__, __LINE__);
        Assert::assertEquals("Dir value from LocoNet Message, loop "+1, ((i & 0x20) == 0x00), s->isForward(), __FILE__, __LINE__);
    }
    m->setElement(6, 0);
    for (int i = 0; i < 128; ++i) {
        m->setElement(10, i);
        try {
            s->setSlot(m);
        } catch (LocoNetException e) {
            Assert::fail("unexpected exception " + e.getMessage(),__FILE__, __LINE__);
        }
        Assert::assertFalse ("F0 value from LocoNet Message, loop "+i, s->isF0(), __FILE__, __LINE__);
        Assert::assertFalse ("F1 value from LocoNet Message, loop "+i, s->isF1(), __FILE__, __LINE__);
        Assert::assertFalse ("F2 value from LocoNet Message, loop "+i, s->isF2(), __FILE__, __LINE__);
        Assert::assertFalse ("F3 value from LocoNet Message, loop "+i, s->isF3(), __FILE__, __LINE__);
        Assert::assertFalse ("F4 value from LocoNet Message, loop "+i, s->isF4(), __FILE__, __LINE__);
        Assert::assertEquals("F5 value from LocoNet Message, loop "+i,((i & 0x01)== 0x01), s->isF5(), __FILE__, __LINE__);
        Assert::assertEquals("F6 value from LocoNet Message, loop "+i,((i & 0x02)== 0x02), s->isF6(), __FILE__, __LINE__);
        Assert::assertEquals("F7 value from LocoNet Message, loop "+i,((i & 0x04)== 0x04), s->isF7(), __FILE__, __LINE__);
        Assert::assertEquals("F8 value from LocoNet Message, loop "+i,((i & 0x08)== 0x08), s->isF8(), __FILE__, __LINE__);
        Assert::assertTrue  ("Dir value from LocoNet Message, loop "+1, s->isForward(), __FILE__, __LINE__);
    }
}

// The minimal setup for log4J
//@Before
/*public*/ void LocoNetSlotTest::setUp() {
    JUnitUtil::setUp();
    // prepare an interface
    lnis = new LocoNetInterfaceScaffold();
}

//@After
/*public*/ void LocoNetSlotTest::tearDown() {
    JUnitUtil::tearDown();
}

