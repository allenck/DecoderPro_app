#ifndef SECTIONTEST_H
#define SECTIONTEST_H

#include <QObject>

class SectionTest : public QObject
{
 Q_OBJECT
public:
 explicit SectionTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void SysNameConstructorTest();
 /*public*/ void TwoNameStringConstructorTest();
 /*public*/ void warnOnBlockAdd();
 /*public*/ void warnOnBlockAddWithNoUserName();

};

#endif // SECTIONTEST_H
