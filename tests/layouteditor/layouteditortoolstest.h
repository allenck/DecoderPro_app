#ifndef LAYOUTEDITORTOOLSTEST_H
#define LAYOUTEDITORTOOLSTEST_H

#include <QObject>
#include "exceptions.h"

class LayoutEditor;
class LayoutEditorTools;
class LayoutBlock;
class Turnout;
class SignalHead;
class Sensor;
class LayoutTurnout;
class PositionablePoint;
class LayoutEditorToolBarPanel;
class LayoutEditorToolsTest : public QObject
{
 Q_OBJECT
public:
 explicit LayoutEditorToolsTest(QObject *parent = nullptr);
Q_INVOKABLE /*public*/ void setUp() throw (Exception);
Q_INVOKABLE /*public*/ void tearDown() throw (Exception);
 /*public*/ LayoutEditorToolBarPanel* getLayoutEditorToolBarPanel();

signals:

public slots:
 /*public*/ void testCtor();
 /*public*/ void testHitEndBumper();
 /*public*/ void testSetSignalsAtTurnout();
 /*public*/ void testSetSignalsAtTurnoutWithDone();

private:
 /*private*/ LayoutEditor* layoutEditor = nullptr;
 /*private*/ LayoutEditorTools* let = nullptr;

 //these all have to contain the same number of elements
 /*private*/ QList<LayoutBlock*> layoutBlocks;
 /*private*/ QList<Turnout*> turnouts;
 /*private*/ QList<SignalHead*> signalHeads;
 /*private*/ QList<Sensor*> sensors;

 /*private*/ LayoutTurnout* layoutTurnout = nullptr;
 /*private*/ PositionablePoint* positionablePoint1 = nullptr;
 /*private*/ PositionablePoint* positionablePoint2 = nullptr;
 /*private*/ PositionablePoint* positionablePoint3 = nullptr;

};

#endif // LAYOUTEDITORTOOLSTEST_H
