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

//#define Assert(a, b, c, d, e) Assert1(a, b, c, d, e)
//#define Assert(a, b, c, d) Assert1(a, b, c, d)
//#define Assert(a, b, c) Assert1(a, b, c, __FILE__, __LINE__)
//#define Assert(a, b) Assert1(a, b, __FILE__, __LINE__)
//#define Assert(a ) Assert1(a, __FILE__, __LINE__)
//#define Assert Assert1

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
    /*public*/ static void assertEquals(float expected, double actual, double delta, QString file, int line);
    /*public*/ static void assertEquals(QDomElement expected, QDomElement actual, QDomElement delta, QString file, int line);
    /*public*/ static void assertEquals(QString expected, QString actual, QString file, int line);
    /*public*/ static void assertEquals(bool expected, bool actual, QString file, int line);
//    /*public*/ static void assertEquals(QString message, ProgrammingMode* expected, ProgrammingMode* actual);
//    /*public*/ static void assertEquals(QString message, Reporter* expected, Reporter* actual);
    /*public*/ static void assertEquals(QString message, QVariant expected, QVariant actual, QString file, int line);
    /*public*/ static void assertEquals(QVariant expected, QVariant actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, QChar expected, QChar actual, QString file, int line);
    /*public*/ static void assertEquals(QString message, double expected, double actual, double delta, QString file, int line);


    /*public*/ static void assertNotEquals(QString message, QObject* unexpected, QObject* actual, QString file, int line);
    /*public*/ static void assertNotEquals(QString expected, QString actual, QString file, int line);
    /*public*/ static void assertNotEquals(QObject* unexpected, QObject* actual, QString file, int line);
    /*public*/ static void assertNotEquals(QString message, QString unexpected, QString actual, QString file, int line);
    /*public*/ static void assertNotEquals(QString message, int unexpected, int actual, QString file, int line);


    /*public*/ static void assertNotNull(QString message, QObject* object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QDomElement object, QString file, int line);
    /*public*/ static void assertNotNull(QObject* object, QString file, int line);
    /*public*/ static void assertNotNull(QDomElement object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, int object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QString object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QVariant object, QString file, int line);
    /*public*/ static void assertNotNull(QString object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QByteArray object, QString file, int line);
    /*public*/ static void assertNotNull(QString message, QWidget* object, QString file, int line);

    /*public*/ static void assertNull(QVariant object, QString file, int line);
    /*public*/ static void assertNull(QString message, QObject* object, QString file, int line);
    /*public*/ static void assertNull(QObject* object, QString file, int line);
    /*public*/ static void assertNull(QString object, QString file, int line);
    /*public*/ static void assertNull(QDomElement object, QString file, int line);
    /*public*/ static void assertNull(QString message, QString object, QString file, int line);
    /*public*/ static void assertNull(QString message, QVariant object, QString file, int line);
    /*public*/ static void assertNull(QString message, QByteArray object, QString file, int line);

    /*public*/ static void assertNotSame(QString message, int unexpected, int actual, QString file, int line);

    /*public*/ static void assertArrayEquals(QString message, QVector<int> expecteds, QVector<int> actuals, QString file, int line); //throw (ArrayComparisonFailure)
    /*public*/ static void assertArrayEquals(QVector<int> expecteds, QVector<int> actuals, QString file, int line);

signals:

public slots:
private:
};

class Assertions : public QObject
{
 public:
  /*public*/ static void assertNotNull(QObject* obj, QString msg, QString file,int line);
  /*public*/ static void assertEquals(QString s1, QString s2, QString msg, QString file,int line);
  /*public*/ static void assertTrue(bool cond, QString msg, QString file,int line);
  /*public*/ static void assertFalse(bool condition, QString msg, QString file,int line);
  /*public*/ static void assertNull(QObject* obj, QString msg, QString file,int line);

  /*public*/ static void assertEquals(int i1, int i2, QString msg, QString file,int line);

};

#endif // ASSERT1_H
