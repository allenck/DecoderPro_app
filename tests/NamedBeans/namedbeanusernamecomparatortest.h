#ifndef NAMEDBEANUSERNAMECOMPARATORTEST_H
#define NAMEDBEANUSERNAMECOMPARATORTEST_H

#include <QObject>
#include "abstractturnout.h"

class NamedBeanUserNameComparatorTest : public QObject
{
    Q_OBJECT
public:
    explicit NamedBeanUserNameComparatorTest(QObject *parent = nullptr);
    Q_INVOKABLE /*public*/ void setUp();
    Q_INVOKABLE /*public*/ void tearDown();

public slots:
    /*public*/ void testNonNullUserNameCases();
    /*public*/ void testOneLetterCases();
    /*public*/ void testTwoLetterCases();
    /*public*/ void testThreeLetterCases();
    /*public*/ void testMixedUserNamesSystemNamesCase();
    /*public*/ void testSystemSpecificCase();


signals:

public slots:
private:
    bool hit = false;
friend class AbstractTurnoutO2;
};

class AbstractTurnoutO2 : public AbstractTurnout {
Q_OBJECT
    NamedBeanUserNameComparatorTest* test;
public:
    AbstractTurnoutO2(QString name, NamedBeanUserNameComparatorTest* test)
        : AbstractTurnout(name)
    {
        this->test = test;
    }
protected:
    //@Override
    /*protected*/ void forwardCommandChangeToLayout(int s) {
    }

    //@Override
    /*protected*/ void turnoutPushbuttonLockout(bool b) {
    }

    //@Override
    /*public*/ int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n) {
        test->hit = true;
        return AbstractTurnout::compareSystemNameSuffix(suffix1, suffix2, n);
    }
};

#endif // NAMEDBEANUSERNAMECOMPARATORTEST_H
