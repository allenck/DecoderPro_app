#ifndef LNSENSORTEST_H
#define LNSENSORTEST_H
#include "abstractsensortestbase.h"
#include "loconetinterfacescaffold.h"
#include "lnsensor.h"
class LnSensorTest : public AbstractSensorTestBase
{
    Q_OBJECT
public:
    LnSensorTest(QObject* parent=nullptr);
    /*public*/ int numListeners();
    /*public*/ void checkOnMsgSent();
    /*public*/ void checkOffMsgSent();
    /*public*/ void checkStatusRequestMsgSent();
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void testLnSensorStatusMsg();

private:
    static Logger* log;
    /*private*/ LocoNetInterfaceScaffold* lnis = nullptr;
friend class LocoNetInterfaceScaffoldO2;
};

class LocoNetInterfaceScaffoldO2 : public LocoNetInterfaceScaffold
{
    Q_OBJECT
    LnSensorTest* test;
public:
    LocoNetInterfaceScaffoldO2(LnSensorTest* test) {this->test = test;}
    //@Override
    /*public*/ void sendLocoNetMessage(LocoNetMessage* m) {
        test->log->debug(tr("sendLocoNetMessage [%1]").arg(m->toString()));
        // save a copy
        outbound.append(m);
        ((LnSensor*)test->t)->messageFromManager(m);
    }
};

#endif // LNSENSORTEST_H
