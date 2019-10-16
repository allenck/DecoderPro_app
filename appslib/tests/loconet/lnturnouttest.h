#ifndef LNTURNOUTTEST_H
#define LNTURNOUTTEST_H
#include "abstractturnouttestbase.h"
#include "junitutil.h"
#include "loconetinterfacescaffold.h"

class LocoNetInterfaceScaffold;
class LocoNetSystemConnectionMemo;
class LnTurnout;
class LnTurnoutTest : public AbstractTurnoutTestBase
{
    Q_OBJECT
public:
    LnTurnoutTest(QObject* parent = nullptr);
    /*public*/ int numListeners();
    /*public*/ void checkClosedMsgSent() throw (InterruptedException);
    /*public*/ void checkThrownMsgSent() throw (InterruptedException);
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void checkIncoming();
    /*public*/ void checkIncomingWithAck();
    /*public*/ void testLnTurnoutStatusMsg();
    /*public*/ void testLnTurnoutStatusMsgAck();
    /*public*/ void testLnTurnoutExactFeedback();
    /*public*/ void testBasicSet() throw (InterruptedException);
    /*public*/ void testPropertySet() throw (InterruptedException);
    /*public*/ void testPropertySet1() throw (InterruptedException);
    /*public*/ void testPropertySet2() throw (InterruptedException);
    /*public*/ void testTurnoutLocks();
    /*public*/ void testMessageFromManagerWrongType();
    /*public*/ void testMyAddress();
    /*public*/ void testCtorNumberOutOfBounds();
    /*public*/ void testSetFeedback();
    /*public*/ void testGetNumber();
    /*public*/ void testSetUseOffSwReqAsConfirmation();
    /*public*/ void testSetStateClosedAndThrown();
    /*public*/ void testWarningSendingOffWhenUsingOffAsConfirmation();
    /*public*/ void testFeedbackLateResend();
    /*public*/ void testFeedbackLateResendAborted();
    /*public*/ void testComputeKnownStateOpSwAckReq();
    /*public*/ void testSetKnownStateFromOutputStateReport();
    /*public*/ void testComputeFeedbackFromSwitchOffReport();
    /*public*/ void testAdjustStateForInversion();

private:
    static Logger* log;
    LnTurnout* lnt;
    LocoNetInterfaceScaffold* lnis;
    LocoNetSystemConnectionMemo* memo;
    void wait(int secs);

    friend class ReleaseUntilO7;
};
class  ReleaseUntilO7 : public ReleaseUntil
{
    Q_OBJECT
    LnTurnoutTest* test;
    int i;
public:
    ReleaseUntilO7(int i, LnTurnoutTest* test) {this->i = i; this->test = test;}
    bool ready() throw (Exception) {return test->lnis->outbound.size()==i;}
};
#endif // LNTURNOUTTEST_H
