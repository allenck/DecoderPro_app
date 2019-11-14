#ifndef SINGLETURNOUTSIGNALHEADTEST_H
#define SINGLETURNOUTSIGNALHEADTEST_H
#include "abstractsignalheadtestbase.h"

class SingleTurnoutSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 SingleTurnoutSignalHeadTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testNoDarkValidTypes();
 /*public*/ void testDarkValidTypes1();
 /*public*/ void testDarkValidTypes2();


};

#endif // SINGLETURNOUTSIGNALHEADTEST_H
