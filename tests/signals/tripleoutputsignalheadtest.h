#ifndef TRIPLEOUTPUTSIGNALHEADTEST_H
#define TRIPLEOUTPUTSIGNALHEADTEST_H
#include "abstractsignalheadtestbase.h"

class TripleOutputSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 TripleOutputSignalHeadTest();
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testCTor();

};

#endif // TRIPLEOUTPUTSIGNALHEADTEST_H
