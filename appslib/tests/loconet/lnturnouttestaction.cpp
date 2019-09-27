#include "lnturnouttestaction.h"
#include "lnturnouttest.h"
#include "joptionpane.h"
#include "assert1.h"
#include "loggerfactory.h"


LnTurnoutTestAction::LnTurnoutTestAction(QObject* parent) : AbstractAction(tr("LnTurnout test"), parent)
{
 connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

void LnTurnoutTestAction::actionPerformed()
{
    LnTurnoutTest* test = new LnTurnoutTest();
    test->setUp();
    try
    {
     QStringList testList = QStringList()
     // tests in AbstractTurnoutTestBase
     << "testCreate"
     << "testAddListener"
     << "testRemoveListener"
     << "testDispose"
     << "testCommandClosed"
     << "testCommandThrown"
     << "testRequestUpdate"
     << "testGetAndSetInverted"
     << "testInvertedCommandClosed"
     << "testInvertedCommandThrown"
     << "testProvideFirstFeedbackSensor"
     << "testProvideSecondFeedbackSensor"
     << "testOneSensorFeedback"
     << "testTwoSensorFeedback"
     << "testDirectFeedback"
     << "testGetBeanType"

     // tests in LnTturnoutTest
     << "checkClosedMsgSent"
     << "checkThrownMsgSent"
     << "checkIncoming"
     << "checkIncomingWithAck"
     << "testLnTurnoutStatusMsg"
     << "testLnTurnoutStatusMsgAck"
     << "testLnTurnoutExactFeedback"
     << "testBasicSet"
     << "testPropertySet"
     << "testPropertySet1"
     << "testPropertySet2"
     << "testTurnoutLocks"
     << "testMessageFromManagerWrongType"
     << "testMyAddress"
     << "testCtorNumberOutOfBounds"
     << "testSetFeedback"
     << "testGetNumber"
     << "testSetUseOffSwReqAsConfirmation"
     << "testSetStateClosedAndThrown"
     << "testWarningSendingOffWhenUsingOffAsConfirmation"
     << "testFeedbackLateResend"
     << "testFeedbackLateResendAborted"
     << "testComputeKnownStateOpSwAckReq"
     << "testSetKnownStateFromOutputStateReport"
     << "testComputeFeedbackFromSwitchOffReport"
     << "testAdjustStateForInversion";
     foreach(QString testName, testList)
     {
      log->info(tr("begin '%1'").arg(testName));
      QMetaObject::invokeMethod(test, testName.toLocal8Bit(), Qt::DirectConnection);
      log->info(tr("end '%1'").arg(testName));
     }
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
    test->tearDown();
}
Logger* LnTurnoutTestAction::log = LoggerFactory::getLogger("LnTurnoutTestAction");
