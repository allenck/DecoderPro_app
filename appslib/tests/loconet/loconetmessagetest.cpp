#include "loconetmessagetest.h"
#include "junitutil.h"
#include "loconetmessage.h"
#include "assert1.h"
#include "junitappender.h"
#include "stringutil.h"
#include "loconetinterfacescaffold.h"
#include "lnturnoutmanager.h"
#include "lnsensormanager.h"
#include "instancemanager.h"
#include "lnsensor.h"

LocoNetMessageTest::LocoNetMessageTest(QObject *parent) : QObject(parent)
{

}

/**
 * Tests for the jmri.jmrix.loconet.LocoNetMessage class.
 * <hr>
 * This file is part of JMRI.
 * <p>
 * JMRI is free software; you can redistribute it and/or modify it under
 * the terms of version 2 of the GNU General public License as published
 * by the Free Software Foundation. See the "COPYING" file for a copy
 * of this license.
 * <p>
 * JMRI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General public License
 * for more details.
 * <p>
 * Some of the message formats used in this class are Copyright Digitrax, Inc.
 * and used with permission as part of the JMRI project. That permission does
 * not extend to uses in other software products. If you wish to use this code,
 * algorithm or these message formats outside of JMRI, please contact Digitrax
 * Inc for separate permission.
 *
 * @author	Bob Jacobsen
 * @author B. Milhaupt Copyright (C) 2018
 *
 */
///*public*/ class LocoNetMessageTest {

//@Test
/*public*/ void LocoNetMessageTest::testCtor() {
    LocoNetMessage* m = new LocoNetMessage(3);
    Assert::assertEquals("length", 3, m->getNumDataElements(), __FILE__, __LINE__);
    m = new LocoNetMessage(2);
    Assert::assertEquals("length", 2, m->getNumDataElements(), __FILE__, __LINE__);
    new LocoNetMessage(1);
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow object creation if length is less than 2.",__FILE__, __LINE__);

    new LocoNetMessage(0);
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow object creation if length is less than 2.",__FILE__, __LINE__);

    new LocoNetMessage(-1);
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow object creation if length is less than 2.",__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testArrayCtor() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>() <<11<< 12<< 13<< 14);
    Assert::assertEquals("length", 4, m->getNumDataElements(), __FILE__, __LINE__);
    Assert::assertEquals("first value", 11, m->getElement(0), __FILE__, __LINE__);
    Assert::assertEquals("second value", 12, m->getElement(1), __FILE__, __LINE__);
    Assert::assertEquals("third value", 13, m->getElement(2), __FILE__, __LINE__);
    Assert::assertEquals("fourth value", 14, m->getElement(3), __FILE__, __LINE__);
    new LocoNetMessage(QVector<int>() << 0x85);
    JUnitAppender::assertErrorMessage("Cannot create a LocoNet message of length shorter than two.",__FILE__, __LINE__);

    QVector<char> t1 = QVector<char> () <</*(byte)*/(char) 0x81;
    new LocoNetMessage(t1);
    JUnitAppender::assertErrorMessage("Cannot create a LocoNet message of length shorter than two.",__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testGetPeerXfr() {
    // basic message
    LocoNetMessage* m1 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0);
    checkPeerXfr(m1, 0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0);

    // some high data bits set
    LocoNetMessage* m2 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<0x80<< 0x81<< 3<< 4<< 0xf5<< 6<< 7<< 0xf8, 0);
    checkPeerXfr(m2, 0x1050, 0x1051,
            QVector<int>()<<0x80<< 0x81<< 3<< 4<< 0xf5<< 6<< 7<< 0xf8, 0);

    // all high data bits set
    LocoNetMessage* m3 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<0x80<< 0x81<< 0x83<< 0x84<< 0xf5<< 0x86<< 0x87<< 0xf8, 0);
    checkPeerXfr(m3, 0x1050, 0x1051,
            QVector<int>()<<0x80<< 0x81<< 0x83<< 0x84<< 0xf5<< 0x86<< 0x87<< 0xf8, 0);

    // check code three times
    LocoNetMessage* m4 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0x11);
    checkPeerXfr(m4, 0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0x11);

    m4 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0x38);
    checkPeerXfr(m4, 0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 0x38);

    m4 = LocoNetMessage::makePeerXfr(0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 63);
    checkPeerXfr(m4, 0x1050, 0x1051,
            QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8, 63);
}

//@Test
/*public*/ void LocoNetMessageTest::testConstructorNoParams() {
    LocoNetMessage* m = new LocoNetMessage();
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with no argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::LocoNetMessageTest::testConstructorString() {
    LocoNetMessage* m = new LocoNetMessage("");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);

    m = new LocoNetMessage("A");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);

    m = new LocoNetMessage("AB");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);

    m = new LocoNetMessage("ABC");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);

    m = new LocoNetMessage("ABCD");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(), __FILE__, __LINE__);

    m = new LocoNetMessage("81 7E");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(), __FILE__, __LINE__);

    m = new LocoNetMessage("81 7e");
    JUnitAppender::assertErrorMessage("LocoNetMessage does not allow a constructor with a 'String' argument",__FILE__, __LINE__);
    Assert::assertEquals("expect 0-length LocoNetMessage object", 0, m->getNumDataElements(),__FILE__, __LINE__);
}

// use the makePeerXfr calls, already tested to check the decoding
//@Test
/*public*/ void LocoNetMessageTest::testGetPeerXfrData() {
    QVector<int> test;
    QVector<int> data;
    LocoNetMessage* m;

    test = QVector<int>()<<1<< 2<< 3<< 4<< 5<< 6<< 7<< 8;
    m = LocoNetMessage::makePeerXfr(0x1050, 0x1051, test, 63);
    data = m->getPeerXfrData();
    for (int i = 0; i < 8; i++) {
        Assert::assertEquals("simple value " + i, "" + test[i], "" + data[i],__FILE__, __LINE__);
    }

    test = QVector<int>()<<0x81<< 0x21<< 0x83<< 0x84<< 0x54<< 0x86<< 0x66<< 0x88;
    m = LocoNetMessage::makePeerXfr(0x1050, 0x1051, test, 63);
    data = m->getPeerXfrData();
    for (int i = 0; i < 8; i++) {
        Assert::assertEquals("high-bit value " + i, "" + test[i], "" + data[i],__FILE__, __LINE__);
    }

    test = QVector<int>()<<0xB5<< 0xD3<< 0x63<< 0xF4<< 0x5E<< 0x77<< 0xFF<< 0x22;
    m = LocoNetMessage::makePeerXfr(0x1050, 0x1051, test, 63);
    data = m->getPeerXfrData();
    for (int i = 0; i < 8; i++) {
        Assert::assertEquals("complicated value " + i, "" + test[i], "" + data[i],__FILE__, __LINE__);
    }

    m->setOpCode(0);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong opcode 0x0",__FILE__, __LINE__);

    m->setOpCode(0xe4);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong opcode 228",__FILE__, __LINE__);

    m->setOpCode(0xe5);
    m->setElement(1, 9);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong secondary code 9",__FILE__, __LINE__);

    m = new LocoNetMessage(QVector<int>()<<0xe5<< 0x10<< 0x42<< 0x40<< 0x00<< 0x00<< 0<< 0<< 0<< 0<< 0<< 0<< 0<< 0<< 0<< 0<< 0);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong length 17",__FILE__, __LINE__);

    m = new LocoNetMessage(QVector<int>()<<0xe5<< 0x10<< 0x42<< 0x40<< 0x00<< 0x00);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong length 6",__FILE__, __LINE__);

    m = new LocoNetMessage(QVector<int>()<<0xe5<< 0x10<< 0x42<< 0x40<< 0x00);
    data = m->getPeerXfrData();
    JUnitAppender::assertErrorMessage("getPeerXfrData called with wrong length 5",__FILE__, __LINE__);

    for (int j = 0; j < 8; ++j) {
        test = QVector<int>()<<0x00<< 0x00<< 0x00<< 0x00<< 0x00<< 0x00<< 0x00<< 0x00;
        test[j] = 0x80;
        m = LocoNetMessage::makePeerXfr(0x101, 0x8581, test, 0);
        data = m->getPeerXfrData();
        for (int i = 0; i < 8; i++) {
            Assert::assertEquals("complicated value " + i, "" + test[i], "" + data[i],__FILE__, __LINE__);
        }
    }
}

//@Test
//@SuppressWarnings("unlikely-arg-type") // int[] seems to be unrelated to LocoNetMessage
/*public*/ void LocoNetMessageTest::testEqualsFromInt() {
    QVector<int> t1 = QVector<int>()<<0x81<< 0x01<< 0x02<< 0x02;
    QVector<int> t2 = QVector<int>()<<0x81<< 0x01<< 0x02<< 0x02<< 0x03;
    QVector<int>t3 = QVector<int>()<<0x81<< 0x01<< 0x02<< 0x0F02;
    QVector<int>t4 = QVector<int>()<<0x81<< 0x01<< 0x03<< 0x02;
    QVector<int> t5 = QVector<int>()<<0x81<< 0x01<< 0x02<< 0x03;  // last byte not checked
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t1)), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t3)), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(new LocoNetMessage(t2)), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(new LocoNetMessage(t4)), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t5)), __FILE__, __LINE__);
    Assert::assertFalse((new LocoNetMessage(t1))->equals(nullptr), __FILE__, __LINE__);
// TODO:    Assert::assertFalse((new LocoNetMessage(t1))->equals(QVector<int>()<<0x81<< 0x01<< 0x02<< 0x02), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testEqualsFromBytes() {
    QVector<char> t1 = QVector<char>()<< (char)0x81<< (char) 0x01<< (char) 0x02<< (char) 0x02;
    QVector<char> t2 = QVector<char>()<< (char)0x81<< (char) 0x01<< (char) 0x02<< (char) 0x02<< (char) 0x03;
    QVector<char> t3 = QVector<char>()<< (char)0x81<< (char) 0x01<< (char) 0x02<< (char) 0x02;
    QVector<char> t4 = QVector<char>()<< (char)0x81<< (char) 0x01<< (char) 0x03<< (char) 0x02;
    QVector<char> t5 = QVector<char>()<< (char)0x81<< (char) 0x01<< (char) 0x02<< (char) 0x03;  // last byte not checked
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t1)), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t3)), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(new LocoNetMessage(t2)), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(new LocoNetMessage(t4)), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(new LocoNetMessage(t5)), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testEqualsFromString() {
#if 0
    LocoNetMessage* t1 = new LocoNetMessage(StringUtil::bytesFromHexString("81 01 02 02"), __FILE__, __LINE__);
    LocoNetMessage* t2 = new LocoNetMessage(StringUtil::bytesFromHexString("81 01 02 02 03"), __FILE__, __LINE__);
    LocoNetMessage* t3 = new LocoNetMessage(StringUtil::bytesFromHexString("81 01 02 02"), __FILE__, __LINE__);
    LocoNetMessage* t4 = new LocoNetMessage(StringUtil::bytesFromHexString("81 01 03 02"), __FILE__, __LINE__);
    LocoNetMessage* t5 = new LocoNetMessage(StringUtil::bytesFromHexString("81 01 02 03"), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(t1), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(t3), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(t2), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1))->equals(t4), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1))->equals(t5), __FILE__, __LINE__);
#endif
}

//@Test
/*public*/ void LocoNetMessageTest::testEqualsSpecificCase() {
#if 0
    LocoNetMessage* t1 = new LocoNetMessage(StringUtil::bytesFromHexString("D7 12 00 09 20 13"), __FILE__, __LINE__);
    LocoNetMessage* t2 = new LocoNetMessage(StringUtil::bytesFromHexString("D7 12 00 09 20 13"), __FILE__, __LINE__);
    LocoNetMessage* t3 = new LocoNetMessage(StringUtil::bytesFromHexString("D7 1F 00 01 00 36"), __FILE__, __LINE__);
    LocoNetMessage* t4 = new LocoNetMessage(StringUtil::bytesFromHexString("D7 1F 00 01 00 36"), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1)).equals(t1), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t1)).equals(t2), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t3)).equals(t3), __FILE__, __LINE__);
    Assert::assertTrue((new LocoNetMessage(t3)).equals(t4), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t1)).equals(t3), __FILE__, __LINE__);
    Assert::assertTrue(!(new LocoNetMessage(t3)).equals(t1), __FILE__, __LINE__);
#endif
}

// service routine to check the contents of a single message (not a test)
/*protected*/ void LocoNetMessageTest::checkPeerXfr(LocoNetMessage* m, int src, int dst, QVector<int> d, int code) {
    Assert::assertEquals("opcode ", 0xE5, m->getElement(0), __FILE__, __LINE__);
    Assert::assertEquals("secondary op code ", 0x10, m->getElement(1), __FILE__, __LINE__);

    // check the 8 data bytes
    int pxct1 = m->getElement(5);
    int pxct2 = m->getElement(10);

    Assert::assertEquals("data 0", d[0], (m->getElement(6) & 0x7F) + ((pxct1 & 0x01) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 1", d[1], (m->getElement(7) & 0x7F) + ((pxct1 & 0x02) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 2", d[2], (m->getElement(8) & 0x7F) + ((pxct1 & 0x04) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 3", d[3], (m->getElement(9) & 0x7F) + ((pxct1 & 0x08) != 0 ? 0x80 : 0), __FILE__, __LINE__);

    Assert::assertEquals("data 4", d[4], (m->getElement(11) & 0x7F) + ((pxct2 & 0x01) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 5", d[5], (m->getElement(12) & 0x7F) + ((pxct2 & 0x02) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 6", d[6], (m->getElement(13) & 0x7F) + ((pxct2 & 0x04) != 0 ? 0x80 : 0), __FILE__, __LINE__);
    Assert::assertEquals("data 7", d[7], (m->getElement(14) & 0x7F) + ((pxct2 & 0x08) != 0 ? 0x80 : 0), __FILE__, __LINE__);

    // check code
    Assert::assertEquals("code low nibble", code & 0x7, (m->getElement(5) & 0x70) / 16, __FILE__, __LINE__);
    Assert::assertEquals("code high nibble", (code & 0x38) / 8, (m->getElement(10) & 0x70) / 16, __FILE__, __LINE__);

    // check the source address
    Assert::assertEquals("low 7 src address", src & 0x7F, m->getElement(2), __FILE__, __LINE__);

    // check the dest address
    Assert::assertEquals("low 7 dst address", dst & 0x7F, m->getElement(3), __FILE__, __LINE__);
    Assert::assertEquals("high 7 dst address", (dst & 0x7F00) / 256, m->getElement(4), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testToString() {
    LocoNetMessage* m1, *m2;
    m1 = new LocoNetMessage(QVector<int>()<<0x81<< 0x7e);
    m2 = new LocoNetMessage(QVector<int>()<<0xd0<< 0x00<< 0x40<< 0x00<< 0x48<< 0x65);

    Assert::assertEquals("first toString test", "81 7E", m1->toString().toUpper(), __FILE__, __LINE__);
    Assert::assertEquals("second toString test", "D0 00 40 00 48 65", m2->toString().toUpper(), __FILE__, __LINE__);

    m1 = new LocoNetMessage(QVector<int>()<<0xff<< 0x00);
    Assert::assertEquals("third toString test", "FF 00", m1->toString().toUpper(), __FILE__, __LINE__);
    m2 = new LocoNetMessage(QVector<int>()<<0xEF<< 0x0E<< 0x01<< 0x33<< 0x03<< 0x00<< 0x30<< 0x47<< 0x00<< 0x00<< 0x00<< 0x17<< 0x53<< 0x1C);
    Assert::assertEquals("fourth toString test", "EF 0E 01 33 03 00 30 47 00 00 00 17 53 1C", m2->toString().toUpper(), __FILE__, __LINE__);

}

//@Test
/*public*/ void LocoNetMessageTest::testToMonitorString() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0xB2<< 0x15<< 0x63<< 0x72);
    Assert::assertEquals("no LocoNet Sensor Manager installed yet", "Sensor LS812 () is Low.  (BDL16 # 51, DS12; DS54/DS64 # 102, SwiB/S2).\n", m->toMonitorString(), __FILE__, __LINE__);

    m = new LocoNetMessage(QVector<int>()<<0xb2<< 0x1E<< 0x47<< 0x00);

    LocoNetInterfaceScaffold* lnis = new LocoNetInterfaceScaffold(new LocoNetSystemConnectionMemo());
    LocoNetInterfaceScaffold* lnis2 = new LocoNetInterfaceScaffold(new LocoNetSystemConnectionMemo("L2", "LocoNet2"));

    LnTurnoutManager* lntm = new LnTurnoutManager(lnis->getSystemConnectionMemo(), lnis, false);
    LnTurnoutManager* lntm2 = new LnTurnoutManager(lnis2->getSystemConnectionMemo(), lnis2, false);
    LnSensorManager* lnsm = new LnSensorManager(lnis->getSystemConnectionMemo());
    LnSensorManager* lnsm2 = new LnSensorManager(lnis2->getSystemConnectionMemo());

    InstanceManager::setTurnoutManager(lntm);
    InstanceManager::setTurnoutManager(lntm2);
    InstanceManager::setSensorManager(lnsm);
    InstanceManager::setSensorManager(lnsm2);

    LnSensor* s1 = (LnSensor*) lnsm->provideSensor("LS1853");
    LnSensor* s2 = (LnSensor*) lnsm2->provideSensor("L2S1853");
    Assert::assertEquals("Sensor LS1853 () is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString(), __FILE__, __LINE__);
    Assert::assertEquals("Sensor LS1853 () is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L"), __FILE__, __LINE__);
    Assert::assertEquals("Sensor L2S1853 () is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L2"), __FILE__, __LINE__);

    s1->setUserName("grime");

    Assert::assertEquals("Sensor LS1853 (grime) is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString(), __FILE__, __LINE__);
    Assert::assertEquals("Sensor LS1853 (grime) is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L"), __FILE__, __LINE__);
    Assert::assertEquals("Sensor L2S1853 () is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L2"), __FILE__, __LINE__);

    s2->setUserName("brightly");

    Assert::assertEquals("Sensor LS1853 (grime) is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString(), __FILE__, __LINE__);
    Assert::assertEquals("Sensor LS1853 (grime) is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L"), __FILE__, __LINE__);
    Assert::assertEquals("Sensor L2S1853 (brightly) is Low.  (BDL16 # 116, DS13; DS54/DS64 # 232, AuxC/A3).\n", m->toMonitorString("L2"), __FILE__, __LINE__);

    lntm->dispose();
    lntm2->dispose();
    lnsm->dispose();
    lnsm2->dispose();

}

//@Test
/*public*/ void LocoNetMessageTest::testLowByte() {
    for (int i = 0; i < 1025; ++i) {
        Assert::assertEquals("testing lowbyte for "+i, i & 0xFF, LocoNetMessage::lowByte(i), __FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetMessageTest::testHighByte() {
    for (int i = 0; i < 18; ++i) {
        Assert::assertEquals("testing highbyte for " + (1 << i),
                ((1 << i) & 0xFF00) >> 8, LocoNetMessage::highByte(1 << i), __FILE__, __LINE__);
        Assert::assertEquals("testing highbyte for "+ (0x0ffff >> i),
                ((0xffff >> (i+8)) & 0xFF),
                LocoNetMessage::highByte(0xffff >> i), __FILE__, __LINE__);
    }
    JUnitAppender::assertErrorMessage("highByte called with too large value: 10000",__FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("highByte called with too large value: 20000",__FILE__, __LINE__);
    LocoNetMessage::highByte(0xfeffff);
    JUnitAppender::assertErrorMessage("highByte called with too large value: feffff",__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testHighBit() {
    for (int i = -1; i < 1025; ++i) {
        Assert::assertEquals(((i & 0x80)== 0x80),LocoNetMessage::highBit(i), __FILE__, __LINE__);
        if ((i < 0) || ((i > 255))) {
            JUnitAppender::assertErrorMessage(
                    "highBit called with too large value: 0x"+QString::number(i,0,16),__FILE__, __LINE__);
        }
    }

}

//@Test
/*public*/ void LocoNetMessageTest::testInputRepAddr() {
    LocoNetMessage* m = new LocoNetMessage(2);
    m->setOpCode(0x81);
    Assert::assertEquals(-1, m->inputRepAddr(), __FILE__, __LINE__);
    m = new LocoNetMessage(QVector<int>()<<0xb2<< 0x00<< 0x00<< 0x00);
    Assert::assertEquals(0, m->inputRepAddr(), __FILE__, __LINE__);
    m->setElement(1, 0x1);
    Assert::assertEquals(2, m->inputRepAddr(), __FILE__, __LINE__);
    m->setElement(1, 0x0);
    m->setElement(2, 0x1);
    Assert::assertEquals(256, m->inputRepAddr(), __FILE__, __LINE__);
    m->setElement(2, 0x21);
    Assert::assertEquals(257, m->inputRepAddr(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testSensorAddr() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0x00<< 0x00<< 0x00<< 0x00);
    Assert::assertEquals(0, m->sensorAddr(), __FILE__, __LINE__);
    for (int i = 0; i < 7; ++i) {
        m->setElement(1, 1<<i);
        Assert::assertEquals(1 << (i+1), m->sensorAddr(), __FILE__, __LINE__);
    }
    m->setElement(1, 0);
    for (int i = 0; i < 7; ++i) {
        m->setElement(2, 1<<i);
        Assert::assertEquals("iteration "+i,
                256 * ((1 << i) & 0xF) + (((1 << i) & 0x20)==0x20 ? 1:0),
                m->sensorAddr(), __FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetMessageTest::testGetOpCodeHex() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0x81<< 0x00);
    Assert::assertEquals("0x81", m->getOpCodeHex(), __FILE__, __LINE__);
    m->setOpCode(5);
    Assert::assertEquals("0x5", m->getOpCodeHex(), __FILE__, __LINE__);
    m->setOpCode(0xef);
    Assert::assertEquals("0xef", m->getOpCodeHex(), __FILE__, __LINE__);
    m->setOpCode(0xe3);
    m->setElement(1, 0x38);
    Assert::assertEquals("0xe3", m->getOpCodeHex(), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testTurnoutAddr() {
    LocoNetMessage* m = new LocoNetMessage(QVector<int>()<<0x00<< 0x00<< 0x00<< 0x00);
    Assert::assertEquals(1, m->turnoutAddr(), __FILE__, __LINE__);
    for (int i = 0; i < 7; ++i) {
        m->setElement(1, 1<<i);
        Assert::assertEquals((1 << i) +1, m->turnoutAddr(), __FILE__, __LINE__);
    }
    m->setElement(1, 0);
    for (int i = 0; i < 7; ++i) {
        m->setElement(2, 1<<i);
        Assert::assertEquals("iteration "+i,
                128 * ((1 << i) & 0xF) + 1,
                m->turnoutAddr(), __FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetMessageTest::testGetElement() {

    QVector<int> a = QVector<int>()<< 33<< 32<< 31<< 30<< 29<<
                28<< 27<< 26<< 25<< 24<<
                23<< 22<< 21<< 20<< 19<<
                18<< 17<< 16<< 15<< 14;

    LocoNetMessage* m = new LocoNetMessage(a);
    m->getElement(-1);
    JUnitAppender::assertErrorMessage("reference element -1 in message of 20 elements: 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 14 13 12 11 10 0F 0E",__FILE__, __LINE__);

    m->getElement(21);
    JUnitAppender::assertErrorMessage("reference element 21 in message of 20 elements: 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 14 13 12 11 10 0F 0E",__FILE__, __LINE__);

    m->getElement(20);
    JUnitAppender::assertErrorMessage("reference element 20 in message of 20 elements: 21 20 1F 1E 1D 1C 1B 1A 19 18 17 16 15 14 13 12 11 10 0F 0E",__FILE__, __LINE__);

    for (int i = 0; i < 20; ++i) {
        Assert::assertEquals(a[i], m->getElement(i), __FILE__, __LINE__);
    }
}

//@Test
/*public*/ void LocoNetMessageTest::testsetElement() {

    LocoNetMessage* m = new LocoNetMessage(20);
    int val = 0;
    for (int i = 0; i < 20; ++i) {
        Assert::assertEquals(0, m->getElement(i), __FILE__, __LINE__);
    }

    for (int i = 0; i < 20; ++i) {
        int val2 = (val ^ 0x24) << 1;
        val = ((val2 & 0x100) == 1 ? 1:0) + (val2 & 0xFE);
        m->setElement(i, val);
        Assert::assertEquals(val, m->getElement(i), __FILE__, __LINE__);
    }
    int startingPoint = val;
    for (int i = 0; i < 20; ++i) {
        int val2 = (val ^ 0x24) << 1;
        val = ((val2 & 0x100) == 1 ? 1:0) + (val2 & 0xFE);
        m->setElement(i, val);
    }
    val = startingPoint;
    for (int i = 0; i < 20; ++i) {
        int val2 = (val ^ 0x24) << 1;
        val = ((val2 & 0x100) == 1 ? 1:0) + (val2 & 0xFE);
        Assert::assertEquals(val, m->getElement(i), __FILE__, __LINE__);
    }

    m->setElement(2, 0x150);
    m->setElement(3, -1);
    Assert::assertEquals(0xff, m->getElement(3), __FILE__, __LINE__);
    m->setElement(-1, 3);
    JUnitAppender::assertErrorMessage(
        "reference element -1 in message of 20 elements: 38 38 50 FF 38 38 38 38 38 38 38 38 38 38 38 38 38 38 38 38",__FILE__, __LINE__);

    m->setElement(21, 45);
    Assert::assertEquals(0x50, m->getElement(2), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage(
        "reference element 21 in message of 20 elements: 38 38 50 FF 38 38 38 38 38 38 38 38 38 38 38 38 38 38 38 38",__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testHashCode() {
    QVector<int>a = QVector<int>()<<0xE7<< 0x0E<< 0x02<< 0x23<< 0x00<< 0x00<< 0x00<< 0x47<< 0x00<< 0x00<< 0x00<< 0x17<< 0x53<< 0x34;
    LocoNetMessage* m = new LocoNetMessage(a);

    int expectHash = 0;
    for (int i = 2; i >=0; --i) {
        expectHash = (expectHash << 7) +a[i];
    }
    expectHash += m->getNumDataElements();

    Assert::assertEquals(expectHash, m->hashCode(), __FILE__, __LINE__);

    LocoNetMessage* m2 = new LocoNetMessage(QVector<int>()<<0x81<< 0x52);
    Assert::assertEquals(0x81+(0x52*128)+2, m2->hashCode(), __FILE__, __LINE__);

    LocoNetMessage* m3 = new LocoNetMessage(QVector<int>()<<0x97);
    Assert::assertEquals(0x98, m3->hashCode(), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("Cannot create a LocoNet message of length shorter than two.",__FILE__, __LINE__);

    LocoNetMessage* m4 = new LocoNetMessage(QVector<int>());
    Assert::assertEquals(0x0, m4->hashCode(), __FILE__, __LINE__);
    JUnitAppender::assertErrorMessage("Cannot create a LocoNet message of length shorter than two.",__FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testSetParity() {
    QVector<int> a = QVector<int>()<<0xE7<< 0x0E<< 0x02<< 0x23<< 0x00<< 0x00<< 0x00<< 0x47<< 0x00<< 0x00<< 0x00<< 0x17<< 0x53<< 99;
    LocoNetMessage* m = new LocoNetMessage(a);
    m->setParity();
    Assert::assertEquals(0x34, m->getElement(13), __FILE__, __LINE__);

    QVector<int> b = QVector<int>()<<0xD3<< 0x12<< 0x34<< 0x56<< 0x78<< 0<< 0x98<< 0x87<< 0x76<< 0x65<< 0;
    m = new LocoNetMessage(b);
    m->setParity();
    Assert::assertEquals("byte 5 expected", 0x24, m->getElement(5), __FILE__, __LINE__);
    Assert::assertEquals("byte 10 expected", 0xF3, m->getElement(10), __FILE__, __LINE__);

    QVector<int> c = QVector<int>()<<0xD3<< 0x34<< 0x12<< 0x78<< 0x56<< 0;
    m = new LocoNetMessage(c);
    m->setParity();
    Assert::assertEquals("byte 5 expected", 0x24, m->getElement(5), __FILE__, __LINE__);

    QVector<int> d = QVector<int>()<<0xD3<< 0x34<< 0x10<< 0x78<< 0x56<< 0;
    m = new LocoNetMessage(d);
    m->setParity();
    Assert::assertEquals("byte 5 expected", 0x26, m->getElement(5), __FILE__, __LINE__);
}

//@Test
/*public*/ void LocoNetMessageTest::testCheckParity() {
    QVector<int> a = QVector<int>()<<0xD3<< 0x12<< 0x34<< 0x56<< 0x78<< 0<< 0x98<< 0x87<< 0x76<< 0x65<< 0;
    LocoNetMessage* m = new LocoNetMessage(a);
    Assert::assertEquals(11, m->getNumDataElements(), __FILE__, __LINE__);
    Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);
    for (int i = 0; i < 128; ++i) {
        m->setElement(10, i);
        Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);
    }
    m->setElement(5, 0x24);
    Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);
    m->setElement(10, 0xF3);
    Assert::assertTrue(m->checkParity(), __FILE__, __LINE__);
    m->setElement(5, 0x23);
    Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);

    a = QVector<int>()<<0xD3<< 0x2<< 0x4<< 0x8<< 0x20<< 0;
    m = new LocoNetMessage(a);
    Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);
    m->setElement(5, 2);
    Assert::assertTrue(m->checkParity(), __FILE__, __LINE__);

    m = new LocoNetMessage(QVector<int>()<<0x89<< 0x53<< 0x3c<< 0x12);
    Assert::assertFalse(m->checkParity(), __FILE__, __LINE__);
    m->setElement(3, 0x19);
    Assert::assertTrue(m->checkParity(), __FILE__, __LINE__);
}

//@Before
/*public*/ void LocoNetMessageTest::setUp() {
    JUnitUtil::setUp();
}

//@After
/*public*/ void LocoNetMessageTest::tearDown() {
    JUnitUtil::tearDown();
}
