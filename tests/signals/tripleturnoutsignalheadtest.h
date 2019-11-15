#ifndef TRIPLETURNOUTSIGNALHEADTEST_H
#define TRIPLETURNOUTSIGNALHEADTEST_H
#include"abstractsignalheadtestbase.h"

class TripleTurnoutSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 TripleTurnoutSignalHeadTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testCTor();

};

#endif // TRIPLETURNOUTSIGNALHEADTEST_H
