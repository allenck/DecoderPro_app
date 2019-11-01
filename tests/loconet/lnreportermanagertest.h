#ifndef LNREPORTERMANAGERTEST_H
#define LNREPORTERMANAGERTEST_H
#include "abstractreportermgrtestbase.h"

class LnTrafficController;
class LnReporterManagerTest : public AbstractReporterMgrTestBase
{
 Q_OBJECT
public:
 LnReporterManagerTest();
 /*public*/ QString getSystemName(QString i) override;
 Q_INVOKABLE /*public*/ void setUp() override;
 Q_INVOKABLE/*public*/ void tearDown();

private:
 /*private*/ LnTrafficController* tc = nullptr;
protected:
 /*protected*/ int maxN();


};

#endif // LNREPORTERMANAGERTEST_H
