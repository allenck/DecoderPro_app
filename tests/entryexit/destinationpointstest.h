#ifndef DESTINATIONPOINTSTEST_H
#define DESTINATIONPOINTSTEST_H

#include <QObject>
#include "exceptions.h"
#include "junitutil.h"
#include "destinationpoints.h"

class EntryExitTestTools;
class LayoutEditor;
class EntryExitPairs;
class LayoutBlockManager;
class SensorManager;
class TurnoutManager;
class DestinationPointsTest : public QObject
{
 Q_OBJECT
public:
 explicit DestinationPointsTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ /*static*/ void setUp() throw (Exception) ;
 Q_INVOKABLE /*public*/ /*static*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testSetRoute() throw (Exception);
 /*public*/ void testEnabled();
 /*public*/ void testState();

private:
 static EntryExitTestTools* tools;
 static QMap<QString, LayoutEditor*>* panels;// = new HashMap<>();

 static EntryExitPairs* eep;
 static LayoutBlockManager* lbm;
 static SensorManager* sm;
 static TurnoutManager* tm;

 friend class ReleaseUntil_DPT1;
};

class ReleaseUntil_DPT1 : public ReleaseUntil
{
 Q_OBJECT
 DestinationPoints* dp;
 int state;
public:
 ReleaseUntil_DPT1(DestinationPoints* dp, int state) {this->dp = dp; this->state = state;}
 bool ready() /*throw (Exception)*/

 {
  return dp->getState() == state;
 }
};
#endif // DESTINATIONPOINTSTEST_H
