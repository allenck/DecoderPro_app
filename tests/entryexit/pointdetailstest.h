#ifndef POINTDETAILSTEST_H
#define POINTDETAILSTEST_H

#include <QObject>
#include "junitutil.h"

class EntryExitTestTools;
class LayoutEditor;
class EntryExitPairs;
class LayoutBlockManager;
class SensorManager;
class TurnoutManager;
class PointDetailsTest : public QObject
{
 Q_OBJECT
public:
 explicit PointDetailsTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ /*static*/ void setUp() throw (Exception) ;
 Q_INVOKABLE /*public*/ /*static*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testGetters();
 /*public*/ void testNxButton();

private:
 static EntryExitTestTools* tools;
 static QMap<QString, LayoutEditor*>* panels;// = new HashMap<>();

 static EntryExitPairs* eep;
 static LayoutBlockManager* lbm;
 static SensorManager* sm;
 static TurnoutManager* tm;

};

#endif // POINTDETAILSTEST_H
