#ifndef ASSERT1_H
#define ASSERT1_H

#include <QObject>
#include "exceptions.h"
#include <QtXml>

class ProgrammingMode;
class AssertionError : public Exception
{
public:
    AssertionError(QString s = "");
    ~AssertionError() throw() {}
};

class Logger;
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
    /*public*/ static void assertEquals(QDomElement expected, QDomElement actual, QDomElement delta);
    /*public*/ static void assertEquals(QString expected, QString actual);
    /*public*/ static void assertEquals(bool expected, bool actual);
    /*public*/ static void assertEquals(QString message, ProgrammingMode* expected, ProgrammingMode* actual);

    /*public*/ static void assertNotEquals(QString message, QObject* unexpected, QObject* actual);
    /*public*/ static void assertNotEquals(QString expected, QString actual);
    /*public*/ static void assertNotEquals(QObject* unexpected, QObject* actual);
    /*public*/ static void assertNotEquals(QString message, QString unexpected, QString actual);

    /*public*/ static void assertNotNull(QString message, QObject* object);
    /*public*/ static void assertNotNull(QString message, QDomElement object);
    /*public*/ static void assertNotNull(QObject* object);
    /*public*/ static void assertNotNull(QDomElement object);
    /*public*/ static void assertNotNull(QString message, int object);
    /*public*/ static void assertNotNull(QString message, QString object);

    /*public*/ static void assertNull(QString message, QObject* object);
    /*public*/ static void assertNull(QObject* object);
    /*public*/ static void assertNull(QString object);
    /*public*/ static void assertNull(QDomElement object);
    /*public*/ static void assertNull(QString message, QString object);

signals:

public slots:
private:
};

#endif // ASSERT1_H
