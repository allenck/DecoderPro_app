#ifndef NMRAPACKETTEST_H
#define NMRAPACKETTEST_H

#include <QObject>

class NmraPacketTest : public QObject
{
 Q_OBJECT
public:
 explicit NmraPacketTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();


signals:

public slots:
 /*public*/ void testAccDecoderPacket1();
 /*public*/ void testAccDecoderPacket2();
 /*public*/ void testAccDecoderPacket3();
 /*public*/ void testAccDecoderPacket4();
 /*public*/ void testAccDecoderPacket5();
 /*public*/ void testAccDecoderPacket6();
 /*public*/ void testAccDecoderPacket7();
 /*public*/ void testAccDecoderPacket8();
 /*public*/ void testAccDecoderPacket9();
 /*public*/ void testAccDecoderPacket10();
 /*public*/ void testAccDecoderPacket11();
 /*public*/ void testAccDecoderPacket12();
 /*public*/ void testAccDecoderPacket13();
 /*public*/ void testOpsModeLong();
 /*public*/ void testOpsModeShort();
 /*public*/ void testAnalog1();
 /*public*/ void testAnalog2();
 /*public*/ void testF13F20A();
 /*public*/ void testF13F20B();
 /*public*/ void testF21F28A();
 /*public*/ void testF21F28B();
 /*public*/ void testConsist1();
 /*public*/ void testConsist2();
 /*public*/ void testConsist3();
 /*public*/ void testIsAccSignalDecoderPktOK();
 /*public*/ void testIsAccSignalDecoderPktFalseConsist();
 /*public*/ void testIsAccSignalDecoderPktFalseFunction();
 /*public*/ void testIsAccSignalDecoderPktFalseAnalog();
 /*public*/ void testIsAccSignalDecoderPktFalseOpsWrite();
 /*public*/ void testIsAccSignalDecoderPktFalseAccDecoder();
 /*public*/ void testIsAccSignalDecoderPktFalseAccDecoderPktOpsMode();
 /*public*/ void testIsAccSignalDecoderPktFalseAccDecoderPktOpsModeLegacy();
 /*public*/ void testIsAccDecoderPktOpsModeFalseSignalDecoderPkt();
 /*public*/ void testIsAccDecoderPktOpsModeFalseConsist();
 /*public*/ void testIsAccDecoderPktOpsModeFalseFunction();
 /*public*/ void testIsAccDecoderPktOpsModeFalseAnalog();
 /*public*/ void testIsAccDecoderPktOpsModeFalseOpsWrite();
 /*public*/ void testIsAccDecoderPktOpsModeFalseAccDecoder();
 /*public*/ void testIsAccDecoderPktOpsModeOK();
 /*public*/ void testIsAccDecoderPktOpsModeFalseAccDecoderPktOpsModeLegacy();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseSignalDecoderPkt();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseConsist();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseFunction();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseAnalog();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseOpsWrite();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseAccDecoder();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyFalseAccDecoderPktOpsMode();
 /*public*/ void testIsAccDecoderPktOpsModeLegacyOK();
 /*public*/ void testGetAccSignalDecoderPktAddr1();
 /*public*/ void testGetAccSignalDecoderPktAddr2();
 /*public*/ void testGetAccSignalDecoderPktAddr4();
 /*public*/ void testGetAccSignalDecoderPktAddr8();
 /*public*/ void testGetAccSignalDecoderPktAddr16();
 /*public*/ void testGetAccSignalDecoderPktAddr32();
 /*public*/ void testGetAccSignalDecoderPktAddr64();
 /*public*/ void testGetAccSignalDecoderPktAddr128();
 /*public*/ void testGetAccSignalDecoderPktAddr256();
 /*public*/ void testGetAccSignalDecoderPktAddr512();
 /*public*/ void testGetAccSignalDecoderPktAddr1024();
 /*public*/ void testGetAccSignalDecoderPktAddr2044();
 /*public*/ void testAccDecPktOpsModeLegacy1();
 /*public*/ void testAccDecPktOpsMode1();
 /*public*/ void testAccDecPktOpsModeLegacy2();
 /*public*/ void testAccDecPktOpsMode2();
 /*public*/ void testAccDecPktOpsModeLegacy510();
 /*public*/ void testAccDecPktOpsMode510();
 /*public*/ void testAccDecPktOpsModeLegacy511();
 /*public*/ void testAccDecPktOpsMode511();
 /*public*/ void testAccDecoderPktOpsModeLegacy1();
 /*public*/ void testAccDecoderPktOpsMode1();
 /*public*/ void testAccDecoderPktOpsModeLegacy4();
 /*public*/ void testAccDecoderPktOpsMode4();
 /*public*/ void testAccDecoderPktOpsModeLegacy5();
 /*public*/ void testAccDecoderPktOpsMode5();
 /*public*/ void testAccDecoderPktOpsMode252();
 /*public*/ void testAccDecoderPktOpsMode253();
 /*public*/ void testAccDecoderPktOpsMode256();
 /*public*/ void testAccDecoderPktOpsMode257();
 /*public*/ void testAccDecoderPktOpsModeLegacy2037();
 /*public*/ void testAccDecoderPktOpsMode2037();
 /*public*/ void testAccDecoderPktOpsModeLegacy2040();
 /*public*/ void testAccDecoderPktOpsMode2040();
 /*public*/ void testAccDecoderPktOpsModeLegacy2044();
 /*public*/ void testAccDecoderPktOpsMode2044() ;
 /*public*/ void testAccSignalDecoderPktOpsMode1();
 /*public*/ void testAccSignalDecoderPktOpsMode4();
 /*public*/ void testAccSignalDecoderPktOpsMode5();
 /*public*/ void testAccSignalDecoderPktOpsMode252();
 /*public*/ void testAccSignalDecoderPktOpsMode253();
 /*public*/ void testAccSignalDecoderPktOpsMode256();
 /*public*/ void testAccSignalDecoderPktOpsMode257();
 /*public*/ void testAccSignalDecoderPktOpsMode2037();
 /*public*/ void testAccSignalDecoderPktOpsMode2040();
 /*public*/ void testAccSignalDecoderPktOpsMode2044();
 /*public*/ void testAccSignalDecoderPkt1Aspect23();
 /*public*/ void testAccSignalDecoderPkt2Aspect5();
 /*public*/ void testAccSignalDecoderPkt3Aspect9();
 /*public*/ void testAccSignalDecoderPkt4Aspect11();
 /*public*/ void testAccSignalDecoderPkt5Aspect15();
 /*public*/ void testAccSignalDecoderPkt6Aspect28();
 /*public*/ void testAccSignalDecoderPkt7Aspect10();
 /*public*/ void testAccSignalDecoderPkt8Aspect11();
 /*public*/ void testAccSignalDecoderPkt252Aspect13();
 /*public*/ void testAccSignalDecoderPkt253Aspect19();
 /*public*/ void testAccSignalDecoderPkt254Aspect2();
 /*public*/ void testAccSignalDecoderPkt255Aspect3();
 /*public*/ void testAccSignalDecoderPkt256Aspect7();
 /*public*/ void testAccSignalDecoderPkt2044Aspect0();
 /*public*/ void testAccSignalDecoderPkt2044Aspect31();
 /*public*/ void testAltAccSignalDecoderPktOpsMode1();
 /*public*/ void testAltAccSignalDecoderPktOpsMode4();
 /*public*/ void testAltAccSignalDecoderPktOpsMode5();
 /*public*/ void testAltAccSignalDecoderPktOpsMode8();
 /*public*/ void testAltAccSignalDecoderPktOpsMode9();
 /*public*/ void testAltAccSignalDecoderPktOpsMode256();
 /*public*/ void testAltAccSignalDecoderPktOpsMode257();
 /*public*/ void testAltAccSignalDecoderPktOpsMode260();
 /*public*/ void testAltAccSignalDecoderPktOpsMode261();
 /*public*/ void testAltAccSignalDecoderPktOpsMode2041();
 /*public*/ void testAltAccSignalDecoderPktOpsMode2044();
 /*public*/ void testExtractAddressTypeAcc();
 /*public*/ void testExtractAddressTypeShort();
 /*public*/ void testExtractAddressTypeLong();
 /*public*/ void testExtractAddressNumberAccSignal1();
 /*public*/ void testExtractAddressNumberAccSignal2();
 /*public*/ void testExtractAddressNumberAccSignal4();
 /*public*/ void testExtractAddressNumberAccSignal8();
 /*public*/ void testExtractAddressNumberAccSignal16();
 /*public*/ void testExtractAddressNumberAccSignal32();
 /*public*/ void testExtractAddressNumberAccSignal64();
 /*public*/ void testExtractAddressNumberAccSignal128();
 /*public*/ void testExtractAddressNumberAccSignal256();
 /*public*/ void testExtractAddressNumberAcc1();
 /*public*/ void testExtractAddressNumberAcc2();
 /*public*/ void testExtractAddressNumberAcc4();
 /*public*/ void testExtractAddressNumberAcc8();
 /*public*/ void testExtractAddressNumberAcc16();
 /*public*/ void testExtractAddressNumberAcc32();
 /*public*/ void testExtractAddressNumberAcc64();
 /*public*/ void testExtractAddressNumberAcc128();
 /*public*/ void testExtractAddressNumberAcc256();
 /*public*/ void testExtractAddressNumberAcc512() ;
 /*public*/ void testExtractAddressNumberShort();
 /*public*/ void testExtractAddressNumberLong();
 /*public*/ void testSpeedStep28PacketOld();
 /*public*/ void testSpeedStep28Packet();
 /*public*/ void testToStringNoPacket();
 /*public*/ void testToStringShortLocoPacket();
 /*public*/ void testToStringAccessoryPacket1();
 /*public*/ void testToStringAccessoryPacket257();

private:
 /*private*/ static int decAddr(int accyAddr);

};

#endif // NMRAPACKETTEST_H
