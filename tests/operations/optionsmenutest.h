#ifndef OPTIONSMENUTEST_H
#define OPTIONSMENUTEST_H

#include <QObject>

class OptionsMenuTest : public QObject
{
 Q_OBJECT
public:
 explicit OptionsMenuTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();

};
#endif // OPTIONSMENUTEST_H
