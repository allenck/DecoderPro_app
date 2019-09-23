#ifndef LNTRAFFICROUTERTEST_H
#define LNTRAFFICROUTERTEST_H

#include <QObject>
#include "loconetlistener.h"

class LocoNetSystemConnectionMemo;
class LnTrafficRouterTest : public QObject
{
    Q_OBJECT
public:
    explicit LnTrafficRouterTest(QObject *parent = nullptr);
    /*public*/ void testConnectAndSend();


    //@Test
    /*public*/ void testReceiveAndForward();
    /*public*/ void testConnectAndDisconnect();
    /*public*/ void setUp();
    /*public*/ void tearDown();

signals:

public slots:

private:
    /*private*/ LocoNetSystemConnectionMemo* memo;
    static int count;// = 0;
friend class LocoNetListenerO1;
};
class LocoNetListenerO1 : public LocoNetListener {
    Q_OBJECT
    LnTrafficRouterTest* ltrt;
public:
    LocoNetListenerO1(LnTrafficRouterTest* ltrt) {this->ltrt = ltrt;}
public slots:
    //@Override
    /*public*/ void message(LocoNetMessage* m) {
        ltrt->count++;
    }
};

#endif // LNTRAFFICROUTERTEST_H
