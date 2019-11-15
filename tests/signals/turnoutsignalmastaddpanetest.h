#ifndef TURNOUTSIGNALMASTADDPANETEST_H
#define TURNOUTSIGNALMASTADDPANETEST_H
#include "abstractsignalmastaddpanetestbase.h"

class SignalMastAddPane;
class TurnoutSignalMastAddPaneTest : public AbstractSignalMastAddPaneTestBase
{
 Q_OBJECT
public:
 TurnoutSignalMastAddPaneTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:
 /*public*/ void testSetMast();

protected:
 /*protected*/ SignalMastAddPane* getOTT();

};

#endif // TURNOUTSIGNALMASTADDPANETEST_H
