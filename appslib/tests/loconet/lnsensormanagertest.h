#ifndef LNSENSORMANAGERTEST_H
#define LNSENSORMANAGERTEST_H
#include "abstractsensormgrtestbase.h"

class Logger;
class LocoNetInterfaceScaffold;
class LnSensorManagerTest : public AbstractSensorMgrTestBase
{
public:
 LnSensorManagerTest();
 /*public*/ QString getSystemName(int i);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

public slots:
 /*public*/ void testLnSensorCreate() ;
 /*public*/ void testByAddress();
 /*public*/ void testMisses();
 /*public*/ void testLocoNetMessages();
 /*public*/ void testAsAbstractFactory();
 /*public*/ void testDeprecationWarningSensorNumberFormat();

private:
 /*private*/ LocoNetInterfaceScaffold* lnis = nullptr;
 static Logger* log;

};

#endif // LNSENSORMANAGERTEST_H
