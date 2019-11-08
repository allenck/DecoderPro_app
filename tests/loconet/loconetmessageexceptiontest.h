#ifndef LOCONETMESSAGEEXCEPTIONTEST_H
#define LOCONETMESSAGEEXCEPTIONTEST_H

#include <QObject>

class LocoNetMessageExceptionTest : public QObject
{
    Q_OBJECT
public:
    explicit LocoNetMessageExceptionTest(QObject *parent = nullptr);
    Q_INVOKABLE /*public*/ void setUp();
    Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
    /*public*/ void ConstructorTest();
    /*public*/ void StringConstructorTest();

};

#endif // LOCONETMESSAGEEXCEPTIONTEST_H
