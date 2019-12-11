#ifndef POSITIONABLETESTBASE_H
#define POSITIONABLETESTBASE_H

#include <QObject>
#include "editor.h"
#include "positionable.h"
#include "junitutil.h"
#include "assert1.h"

class PositionableTestBase : public QObject
{
 Q_OBJECT
public:
 explicit PositionableTestBase(QObject *parent = nullptr);
 virtual /*public*/ void setUp();
 virtual /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testGetAndSetPositionable();
 /*public*/ void testGetAndSetEditable();
 /*public*/ void testGetAndSetShowToolTip();
 /*public*/ void testGetAndSetToolTip();
 /*public*/ void testGetAndSetViewCoordinates();
 /*public*/ void testGetAndSetControlling();
 /*public*/ void testGetAndSetHidden();
 /*public*/ void testGetAndSetDisplayLevel();
 /*public*/ void testGetAndSetEditor();
 /*public*/ void testClone();
 /*public*/ void testMaxWidth();
 /*public*/ void testMaxHeight();
 /*public*/ void testGetAndSetScale();
 /*public*/ void testGetAndSetRotationDegrees();
 /*public*/ void testGetTextComponent();
 /*public*/ void testStoreItem();
 /*public*/ void testDoViemMenu();
 /*public*/ void testGetNameString();
 /*public*/ void testShow();

protected:
 /*protected*/ Editor* editor = nullptr;   // derived classes should set editor in setup;
 /*protected*/ Positionable* p = nullptr;  //derived classes should set p in setUp

};

#endif // POSITIONABLETESTBASE_H
