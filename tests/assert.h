#ifndef ASSERT_H
#define ASSERT_H

#include <QObject>

class Assert : public QObject
{
    Q_OBJECT
protected:
    explicit Assert(QObject *parent = nullptr);
public:
    /*public*/ static void assertTrue(QString message, bool condition);
    /*public*/ static void assertTrue(bool condition);
    /*public*/ static void assertFalse(QString message, bool condition);
    /*public*/ static void assertFalse(bool condition);
    /*public*/ static void fail(QString message);
    /*public*/ static void fail();
    /*public*/ static void assertEquals(QString message, QObject *expected, QObject *actual);
    /*public*/ static void assertEquals(QString message, bool expected, bool actual);
    /*public*/ static void assertEquals(QString message, QString expected, QString actual);
    /*public*/ static void assertEquals(QString message, double expected, double actual);
    /*public*/ static void assertEquals(QString message, float expected, float actual);
    /*public*/ static void assertEquals(QString message, int expected, int actual);
    /*public*/ static void assertEquals(double expected, double actual, double delta);
    /*public*/ static void assertEquals(float expected, float actual, float delta);


    /*public*/ static void assertNotNull(QString message, QObject* object);
    /*public*/ static void assertNotNull(QObject* object);
    /*public*/ static void assertNull(QString message, QObject* object);
    /*public*/ static void assertNull(QObject* object);

signals:

public slots:
};

#endif // ASSERT_H
