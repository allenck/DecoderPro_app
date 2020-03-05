#ifndef SOURCETEST_H
#define SOURCETEST_H

#include <QObject>
#include "exceptions.h"
#include "junitutil.h"

class EntryExitTestTools;
class LayoutEditor;
class EntryExitPairs;
class LayoutBlockManager;
class SensorManager;
class TurnoutManager;
class SourceTest : public QObject
{
 Q_OBJECT

public:
 explicit SourceTest(QObject *parent = nullptr);
 ~SourceTest() override {}
 Q_INVOKABLE /*public*/ void setUp() throw (Exception) ;
 Q_INVOKABLE /*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testDestinationPoints();
 /*public*/ void testSourceMethods();

private:
 static EntryExitTestTools* tools;
 static QMap<QString, LayoutEditor*>* panels;// = new HashMap<>();

 static EntryExitPairs* eep;
 static LayoutBlockManager* lbm;
 static SensorManager* sm;
 static TurnoutManager* tm;

};

#endif // SOURCETEST_H
