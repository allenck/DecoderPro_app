#ifndef LNPOWERMANAGERTEST_H
#define LNPOWERMANAGERTEST_H
#include "abstractpowermanagertestbase.h"
#include <QObject>

class LocoNetInterfaceScaffold;
class LnPowerManager;
class LocoNetSystemConnectionMemo;
class LnPowerManagerTest : public AbstractPowerManagerTestBase
{
    Q_OBJECT
public:
    LnPowerManagerTest();
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
public slots:
    /*public*/ void testImplementsIdle();
    /*public*/ void testStateIdle() throw (JmriException);
    /*public*/ void testSetPowerIdle() throw (JmriException);

private:
    LocoNetInterfaceScaffold* controller;  // holds dummy for testing
    LnPowerManager* pwr;
    /*private*/ LocoNetSystemConnectionMemo* memo;

protected:
    /*protected*/ void hearOn();
    /*protected*/ void sendOnReply();
    /*protected*/ void hearOff();
    /*protected*/ void sendOffReply();
    /*protected*/ void hearIdle();
    /*protected*/ void sendIdleReply();
    /*protected*/ int numListeners();
    /*protected*/ int outboundSize();
    /*protected*/ bool outboundOnOK(int index);
    /*protected*/ bool outboundOffOK(int index);
    /*protected*/ bool outboundIdleOK(int index);

};

#endif // LNPOWERMANAGERTEST_H
