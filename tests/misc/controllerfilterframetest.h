#ifndef CONTROLLERFILTERFRAMETEST_H
#define CONTROLLERFILTERFRAMETEST_H
#include "jmrijframetestbase.h"

class ControllerFilterFrameTest : public JmriJFrameTestBase
{
 Q_OBJECT
public:
 ControllerFilterFrameTest(QObject* parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

public slots:

};

#endif // CONTROLLERFILTERFRAMETEST_H
