#ifndef CABSIGNALTABLEMODELTEST_H
#define CABSIGNALTABLEMODELTEST_H

#include <QObject>

class CabSignalTableModelTest : public QObject
{
 Q_OBJECT
public:
 explicit CabSignalTableModelTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testColumns();


};

#endif // CABSIGNALTABLEMODELTEST_H
