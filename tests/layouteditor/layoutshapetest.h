#ifndef LAYOUTSHAPETEST_H
#define LAYOUTSHAPETEST_H

#include <QObject>

class LayoutEditor;
class LayoutShape;
class LayoutShapeTest : public QObject
{
 Q_OBJECT
public:
 explicit LayoutShapeTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();
 /*public*/ static void beforeClass();
 /*public*/ static void afterClass();

signals:

public slots:
 /*public*/ void testNew();
 /*public*/ void testToString();
 /*public*/ void testGetDisplayName();
 /*public*/ void testGetType();
#if 1
 /*public*/ void testSetType();
 /*public*/ void testGetBounds();
 /*public*/ void testSetCoordsCenter();
 /*public*/ void testScaleCoords();
 /*public*/ void testTranslateCoords();
 /*public*/ void testFindHitPointType();
#endif
private:
 /*private*/ static LayoutEditor* layoutEditor;// = nullptr;
 /*private*/ LayoutShape* ls = nullptr;

};

#endif // LAYOUTSHAPETEST_H
