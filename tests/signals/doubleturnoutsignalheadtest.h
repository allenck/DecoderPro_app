#ifndef DOUBLETURNOUTSIGNALHEADTEST_H
#define DOUBLETURNOUTSIGNALHEADTEST_H
#include "abstractsignalheadtestbase.h"
#include "junitutil.h"
#include "propertychangelistenerscaffold.h"

class Turnout;
class DoubleTurnoutSignalHead;
class PropertyChangeListenerScaffold;
class DoubleTurnoutSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 DoubleTurnoutSignalHeadTest(QObject *parent = nullptr);
 /*public*/ SignalHead* getHeadToTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testCTor();
 /*public*/ void testSetAppearance();
 /*public*/ void testNotify();
 /*public*/ void testReadOutput();
 /*public*/ void testFlashingIgnoresTurnoutFeedback();


private:
 /*private*/ Turnout* mRedTurnout;
 /*private*/ Turnout* mGreenTurnout;
 /*private*/ DoubleTurnoutSignalHead* mHead;
 void createHead();
 void waitForTimer();

protected:
 /*protected*/ PropertyChangeListenerScaffold* l;
friend class WaitForChange;
};

class WaitForChange : public ReleaseUntil
{
 Q_OBJECT
 DoubleTurnoutSignalHeadTest* test;
public:
 WaitForChange(DoubleTurnoutSignalHeadTest* test) {this->test = test;}
 bool ready() /*throw (Exception)*/
{return test->l->propertyChanged;}
};

#endif // DOUBLETURNOUTSIGNALHEADTEST_H
