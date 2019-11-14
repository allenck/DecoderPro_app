#ifndef VIRTUALSIGNALHEADTEST_H
#define VIRTUALSIGNALHEADTEST_H
#include "abstractsignalheadtestbase.h"

class VirtualSignalHeadTest : public AbstractSignalHeadTestBase
{
 Q_OBJECT
public:
 VirtualSignalHeadTest(QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ SignalHead* getHeadToTest();

public slots:
 /*public*/ void testCTor();

};

#endif // VIRTUALSIGNALHEADTEST_H
