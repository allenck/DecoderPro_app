#ifndef ABSTRACTSIGNALHEADTESTBASE_H
#define ABSTRACTSIGNALHEADTESTBASE_H

#include <QObject>

class SignalHead;
class AbstractSignalHeadTestBase : public QObject
{
 Q_OBJECT
public:
 explicit AbstractSignalHeadTestBase(QObject *parent = nullptr);

signals:

public slots:
 /*final*/ /*public*/ void testLit();
 /*final*/ /*public*/ void testHeld();
 /*final*/ /*public*/ void testLitDarkIndependent();
 /*final*/ /*public*/ void testBaseAppearanceStop();
 /*final*/ /*public*/ void testBaseAppearanceClearYellow();
 /*final*/ /*public*/ void testBaseAppearanceClearGreen();
 /*final*/ /*public*/ void testBaseAppearanceRestrictingFlashRed();
 /*final*/ /*public*/ void testBaseAppearanceRestrictingLunar();
 /*final*/ /*public*/ void testClearStopRestrictingOverlaps();
 /*public*/ void testGetBeanType();

private:
 virtual /*abstract*/ SignalHead* getHeadToTest() =0;
 /*final*/ void checkOverlaps(int appearance);
 /*private*/ bool validAppearance(int appearance, SignalHead* s);

};

#endif // ABSTRACTSIGNALHEADTESTBASE_H
