#ifndef TURNOUTSIGNALMASTTEST_H
#define TURNOUTSIGNALMASTTEST_H

#include <QObject>

class TurnoutSignalMastTest : public QObject
{
 Q_OBJECT
public:
 explicit TurnoutSignalMastTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testSetAspect();
 /*public*/ void testSetAspectResetOthers();
 /*public*/ void testUnLitNoTurnout();
 /*public*/ void testUnLitWithTurnout();

};

#endif // TURNOUTSIGNALMASTTEST_H
