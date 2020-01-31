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
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testConnectAndSend();
 /*public*/ void testReceiveAndForward();
 /*public*/ void testConnectAndDisconnect();

private:
    /*private*/ LocoNetSystemConnectionMemo* memo;
    static int count;// = 0;
friend class LocoNetListenerO1;
};
class LocoNetListenerO1 : public QObject, public LocoNetListener {
    Q_OBJECT
 Q_INTERFACES(LocoNetListener)
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
