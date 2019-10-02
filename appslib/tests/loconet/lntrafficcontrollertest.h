#ifndef LNTRAFFICCONTROLLERTEST_H
#define LNTRAFFICCONTROLLERTEST_H

#include <QObject>

class LocoNetSystemConnectionMemo;
class LnTrafficControllerTest : public QObject
{
    Q_OBJECT
public:
    explicit LnTrafficControllerTest(QObject *parent = nullptr);
    Q_INVOKABLE/*public*/ void setUp();
    Q_INVOKABLE/*public*/ void tearDown();
signals:

public slots:
 /*public*/ void testCtor();

private:
    /*private*/ LocoNetSystemConnectionMemo* memo;

};

#endif // LNTRAFFICCONTROLLERTEST_H
