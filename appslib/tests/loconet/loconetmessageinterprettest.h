#ifndef LOCONETMESSAGEINTERPRETTEST_H
#define LOCONETMESSAGEINTERPRETTEST_H

#include <QObject>

class LocoNetMessageInterpretTest : public QObject
{
 Q_OBJECT
public:
 explicit LocoNetMessageInterpretTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testTransponding();
 /*public*/ void OpcPeerXfer7Byte();
 /*public*/ void testALM();
 /*public*/ void testRoutes();
 /*public*/ void testSVProgrammingProtocolV1();
 /*public*/ void testSVProgrammingProtocolV2();
 /*public*/ void testLissy();
 /*public*/ void testOpcAnalogIO();
 /*public*/ void testLACK();
 /*public*/ void testIPL();
 /*public*/ void testIplHostNumbers();
 /*public*/ void testIplPingMessages();
 /*public*/ void testSv1Messages();
 /*public*/ void testProgrammingMessages();
 /*public*/ void testTranspondingMessages();
 /*public*/ void testBasicConsistingMessages();
 /*public*/ void testBasicSensorReportMessages();
 /*public*/ void testTurnoutSensorStateMessages();
 /*public*/ void testBasicImmediatePacketMessages();
 /*public*/ void testPlayableWhistleMessages();
 /*public*/ void testBasicTurnoutControlMessages();
 /*public*/ void testTetherlessQueryAndReplies();
 /*public*/ void testBasicPM42Events();
 /*public*/ void testPR3ModeMessages();
 /*public*/ void testTrackPowerMessages();
 /*public*/ void testPM42OpSwMessages();
 /*public*/ void testDS64OpSwMessages();
 /*public*/ void testCmdStationCfgSlot();
 /*public*/ void testDuplexRadioScan();
 /*public*/ void textOpcPeerXfer();
 /*public*/ void testThrottleMessages();
 /*public*/ void testOpcPeerXfer10();
 /*public*/ void testAliasing();
 /*public*/ void testConvertToMixed();
 /*public*/ void testSwichMessages();
 /*public*/ void testDirf();
 /*public*/ void testPeerXfer20DuplexQuery();
 /*public*/ void testDownloadFirmware();
 /*public*/ void testExtendedCsOpSws();

};

#endif // LOCONETMESSAGEINTERPRETTEST_H
