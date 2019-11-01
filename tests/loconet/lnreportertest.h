#ifndef LNREPORTERTEST_H
#define LNREPORTERTEST_H
#include "abstractreportertestbase.h"

class LocoNetInterfaceScaffold;
class LnReporterTest : public AbstractReporterTestBase
{
 Q_OBJECT
public:
 LnReporterTest();
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

public slots:
 /*public*/ void testLnReporterCreate();
 /*public*/ void testTranspond3Enter146();
 /*public*/ void testTranspond257Enter146();
 /*public*/ void testTranspond257Exit146();
 /*public*/ void testTranspond3Exits146() ;
 /*public*/ void testTranspond1056Enter175();
 /*public*/ void testLnReporterLissy1();
 /*public*/ void testLnReporterLissy2();
 /*public*/ void testMessageFromManagerFindReport();
 /*public*/ void testGetBeanPhysicalLocation();
 /*public*/ void testLnReporterGetLocoAddress();
 /*public*/ void testIsTranspondingLocationReport();
 /*public*/ void testIsTranspondingFindReport();
 /*public*/ void testGetLocoAddrFromTranspondingMsg();
 /*public*/ void testGetNumber();
 /*public*/ void testGetPhysicalLocationAndAddress() ;
 /*public*/ void testLnReporterLissyBad();
 /*public*/ void testGetDriectionString();
 /*public*/ void testCollectionAfterMessage();

private:
 /*private*/ LocoNetInterfaceScaffold* tc;

protected:
 /*protected*/ QVariant generateObjectToReport();

};

#endif // LNREPORTERTEST_H
