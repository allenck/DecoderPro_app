#ifndef LNTRAFFICCONTROLLERTEST_H
#define LNTRAFFICCONTROLLERTEST_H

#include <QObject>

class LocoNetSystemConnectionMemo;
class LnTrafficControllerTest : public QObject
{
    Q_OBJECT
public:
    explicit LnTrafficControllerTest(QObject *parent = nullptr);
    /*public*/ void testCtor();
    /*public*/ void setUp();
    /*public*/ void tearDown();
signals:

public slots:

private:
    /*private*/ LocoNetSystemConnectionMemo* memo;

};

#endif // LNTRAFFICCONTROLLERTEST_H
