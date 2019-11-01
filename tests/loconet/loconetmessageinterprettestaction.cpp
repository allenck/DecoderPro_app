#include "loconetmessageinterprettestaction.h"
#include "loconetmessageinterprettest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "junitutil.h"
LocoNetMessageInterpretTestAction::LocoNetMessageInterpretTestAction(QObject* parent) : AbstractAction(tr("LocoNetMessageInterpretTest"),parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}
void LocoNetMessageInterpretTestAction::actionPerformed()
{
 LocoNetMessageInterpretTest* test = new LocoNetMessageInterpretTest();
 try
 {
  QStringList testList = QStringList()
    << "testTransponding"
    << "OpcPeerXfer7Byte"
    << "testALM"
    << "testRoutes"
    << "testSVProgrammingProtocolV1"
    << "testSVProgrammingProtocolV2"
    << "testLissy"
    << "testOpcAnalogIO"
    << "testLACK"
    << "testIPL"
    << "testIplHostNumbers"
    << "testIplPingMessages"
    << "testSv1Messages"
    << "testProgrammingMessages"
    << "testTranspondingMessages"
    << "testBasicConsistingMessages"
    << "testBasicSensorReportMessages"
    << "testTurnoutSensorStateMessages"
    << "testBasicImmediatePacketMessages"
    << "testPlayableWhistleMessages"
    << "testBasicTurnoutControlMessages"
    << "testTetherlessQueryAndReplies"
    << "testBasicPM42Events"
    << "testPR3ModeMessages"
    << "testTrackPowerMessages"
    << "testPM42OpSwMessages"
    << "testDS64OpSwMessages"
    << "testCmdStationCfgSlot"
    << "testDuplexRadioScan"
    << "textOpcPeerXfer"
    << "testThrottleMessages"
    << "testOpcPeerXfer10"
    << "testAliasing"
    << "testConvertToMixed"
    << "testSwichMessages"
    << "testDirf"
    << "testPeerXfer20DuplexQuery"
    << "testDownloadFirmware"
    << "testExtendedCsOpSws"
 ;

 JUnitUtil::runTests(test, testList);
 }
 catch (AssertionError ex)
 {
  JOptionPane::showMessageDialog(nullptr, ex.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
 }
}
Logger* LocoNetMessageInterpretTestAction::log = LoggerFactory::getLogger("LocoNetMessageInterpretTestAction");
