#include "lnturnouttestaction.h"
#include "lnturnouttest.h"
#include "joptionpane.h"
#include "assert1.h"

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
     // tests in AbstractTurnoutTestBase
     test->testCreate();
     test->testAddListener();
     test->testRemoveListener();
     test->testDispose();
     test->testCommandClosed();
     test->testCommandThrown();
     test->testRequestUpdate();
     test->testGetAndSetInverted();
     test->testInvertedCommandClosed();
     test->testInvertedCommandThrown();
     test->testProvideFirstFeedbackSensor();
     test->testProvideSecondFeedbackSensor();
     test->testOneSensorFeedback();
     test->testTwoSensorFeedback();
     test->testDirectFeedback();
     test->testGetBeanType();

     // tests in LnTturnoutTest
     test->checkClosedMsgSent();
     test->checkThrownMsgSent();
     test->checkIncoming();
     test->checkIncomingWithAck();
     test->testLnTurnoutStatusMsg();
     test->testLnTurnoutStatusMsgAck();
     test->testLnTurnoutExactFeedback();
     test->testBasicSet();
     test->testPropertySet();
     test->testPropertySet1();
     test->testPropertySet2();
     test->testTurnoutLocks();
     test->testMessageFromManagerWrongType();
     test->testMyAddress();
     test->testCtorNumberOutOfBounds();
     test->testSetFeedback();
     test->testGetNumber();
     test->testSetUseOffSwReqAsConfirmation();
     test->testSetStateClosedAndThrown();
     test->testWarningSendingOffWhenUsingOffAsConfirmation();
     test->testFeedbackLateResend();
     test->testFeedbackLateResendAborted();
     test->testComputeKnownStateOpSwAckReq();
     test->testSetKnownStateFromOutputStateReport();
     test->testComputeFeedbackFromSwitchOffReport();
     test->testAdjustStateForInversion();
    }
    catch (AssertionError er)
    {
        JOptionPane::showMessageDialog(nullptr, er.getMessage(), tr("Assertion Error"), JOptionPane::WARNING_MESSAGE);
    }
}
