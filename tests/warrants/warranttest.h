#ifndef WARRANTTEST_H
#define WARRANTTEST_H

#include <QObject>
#include "exceptions.h"
#include "propertychangelistener.h"
#include "junitutil.h"
#include "warrant.h"

class Warrant;
class OBlock;
class OBlockManager;
class PortalManager;
class Sensor;
class SensorManager;
class TurnoutManager;
class WarrantTest : public QObject
{
 Q_OBJECT
public:
 explicit WarrantTest(QObject *parent = nullptr);
 Q_INVOKABLE/*public*/ void setUp();
 Q_INVOKABLE/*public*/ void tearDown();

signals:

public slots:
 /*public*/ void testCTor();
 /*public*/ void testSetAndGetTrainName();
 /*public*/ void testGetSpeedUtil();
 /*public*/ void testAddPropertyChangeListener();
 /*public*/ void testAllocateAndDeallocateWarrant();
 /*public*/ void testSetRouteUsingViaOrders();
 /*public*/ void testSetRoute();
 /*public*/ void setThrottleCommands();
 /*public*/ void testWarrant() throw (JmriException);

protected:
 /*protected*/ OBlockManager* _OBlockMgr;
 /*protected*/ PortalManager* _portalMgr;
 /*protected*/ SensorManager* _sensorMgr;
 /*protected*/ TurnoutManager* _turnoutMgr;
 /*protected*/ OBlock* bWest;
 /*protected*/ OBlock* bEast;
 /*protected*/ OBlock* bNorth;
 /*protected*/ OBlock* bSouth;
 /*protected*/ Warrant* warrant;
 /*protected*/ Sensor* sWest;
 /*protected*/ Sensor* sEast;
 /*protected*/ Sensor* sNorth;
 /*protected*/ Sensor* sSouth;

 friend class ReleaseUntilWT1;
 friend class ReleaseUntilWT2;
};

class WarrantListener : public PropertyChangeListener {
Q_OBJECT
    Warrant* warrant;

    WarrantListener(Warrant* w) {
        warrant = w;
    }

    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
    friend class WarrantTest;
};

class ReleaseUntilWT1 : public ReleaseUntil
{
 Q_OBJECT
 WarrantTest* test;
public:
 ReleaseUntilWT1(WarrantTest* test) {this->test = test;}
 bool ready() throw (Exception)
 {
  QString m = test->warrant->getRunningMessage();
  return m.endsWith("Cmd #2.") || m.endsWith("Cmd #3.");
 }
};

class ReleaseUntilWT2 : public ReleaseUntil
{
 Q_OBJECT
 WarrantTest* test;
public:
 ReleaseUntilWT2(WarrantTest* test) {this->test = test;}
 bool ready() throw (Exception)
 {
  QString m = test->warrant->getRunningMessage();
  return m == "Idle";
 }
};

#endif // WARRANTTEST_H
