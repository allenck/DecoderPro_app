#ifndef PROXYREPORTERMANAGERTEST_H
#define PROXYREPORTERMANAGERTEST_H
#include "abstractreportermgrtestbase.h"

class ProxyReporterManagerTest : public AbstractReporterMgrTestBase
{
 Q_OBJECT


public:
 ProxyReporterManagerTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();
 /*public*/ QString getSystemName(QString i);


 public slots:
 /*public*/ void testReporterPutGet();
 /*public*/ void testTwoNames();
 /*public*/ void testDefaultNotInternal();
 /*public*/ void testProvideUser();
 /*public*/ void testInstanceManagerIntegration();

};

#endif // PROXYREPORTERMANAGERTEST_H
