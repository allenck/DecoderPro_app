#ifndef ASSERT1_H
#define ASSERT1_H

#include <QObject>
#include "exceptions.h"
#include <QtXml>


//class ProgrammingMode;
//class Reporter;
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
    /*public*/ static void assertTrue(QString message, bool condition, QString file, int line);
    /*public*/ static void assertTrue(bool condition, QString file, int line);
    /*public*/ static void assertFalse(QString message, bool condition, QString file, int line);
    /*public*/ static void assertFalse(bool condition, QString file, int line);
    /*public*/ static void fail(QString message, QString file, int line);
    /*public*/ static void fail(QString file, int line);
    /*public*/ static void assertEquals(QString message, QObject *expected, QObject *actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, bool expected, bool actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, QString expected, QString actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, double expected, double actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, float expected, float actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, int expected, int actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, long expected, long actual, QString file, int line);
    /*public*/ static void assertEquals(double expected, double actual, double delta, QString file, int line);
    /*public*/ static void assertEquals(float expected, float actual, float delta, QString file, int line);
    /*public*/ static void assertEquals(QDomElement expected, QDomElement actual, QDomElement delta, QString file, int line);
    /*public*/ static void assertEquals(QString expected, QString actual, QString file, int line);
    /*public*/ static void assertEquals(bool expected, bool actual, QString file, int line);
//    /*public*/ static void assertEquals(QString message, ProgrammingMode* expected, ProgrammingMode* actual);
//    /*public*/ static void assertEquals(QString message, Reporter* expected, Reporter* actual);
    /*public*/ static void assertEquals(QString message, QVariant expected, QVariant actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, QChar expected, QChar actual, QString file, int line);


    /*public*/ static void assertNotEquals(QString message, QObject* unexpected, QObject* actual, QString file, int line);
    /*public*/ static void assertNotEquals(QString expected, QString actual, QString file, int line);
    /*public*/ static void assertNotEquals(QObject* unexpected, QObject* actual, QString file, int line);
    /*public*/ static void assertNotEquals(QString message, QString unexpected, QString actual, QString file, int line);

    /*public*/ static void assertNotNull(QString message, QObject* object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QDomElement object, QString file, int line);
    /*public*/ static void assertNotNull(QObject* object, QString file, int line);
    /*public*/ static void assertNotNull(QDomElement object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, int object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QString object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QVariant object, QString file, int line);
    /*public*/ static void assertNotNull(QString object, QString file, int line);


    /*public*/ static void assertNull(QString message, QObject* object, QString file, int line);
    /*public*/ static void assertNull(QObject* object, QString file, int line);
    /*public*/ static void assertNull(QString object, QString file, int line);
    /*public*/ static void assertNull(QDomElement object, QString file, int line);
    /*public*/ static void assertNull(QString message, QString object, QString file, int line);
    /*public*/ static void assertNull(QString message, QVariant object, QString file, int line);

    /*public*/ static void assertNotSame(QString message, int unexpected, int actual, QString file, int line);

signals:

public slots:
private:
};

#endif // ASSERT1_H
