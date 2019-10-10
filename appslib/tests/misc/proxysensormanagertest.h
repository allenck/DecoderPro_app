#ifndef PROXYSENSORMANAGERTEST_H
#define PROXYSENSORMANAGERTEST_H

#include <QObject>
#include "manager.h"

class PropertyChangeEvent;
class ProxySensorManager;
class ProxySensorManagerTest : public QObject
{
 Q_OBJECT
public:
 explicit ProxySensorManagerTest(QObject *parent = nullptr);
 Q_INVOKABLE /*public*/ void setUp();
 Q_INVOKABLE /*public*/ void tearDown();


signals:

public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

 /*public*/ void testDispose();
 /*public*/ void testPutGetJ();
 /*public*/ void testSensorNameCase();
 /*public*/ void testPutGetI();
 /*public*/ void testPutGetK();
 /*public*/ void testDefaultSystemName();
 /*public*/ void testProvideFailure();
 /*public*/ void testSingleObject();
 /*public*/ void testMisses();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();
 /*public*/ void testTwoNames();
 /*public*/ void testDefaultNotInternal();
 /*public*/ void testProvideUser();
 /*public*/ void testAddTracking();
 /*public*/ void testRemoveTrackingI();
 /*public*/ void testRemoveTrackingJ();
 /*public*/ void testGetObjectCount();
 /*public*/ void testRemoveTrackingJMute();
 /*public*/ void testOrderVsSorted();
 /*public*/ void testUnmodifiable();
 /*public*/ void testInstanceManagerIntegration();

 /*public*/ void intervalAdded(Manager::ManagerDataEvent/*<Sensor>*/* e);
 /*public*/ void intervalRemoved(Manager::ManagerDataEvent/*<Sensor>*/* e);
 /*public*/ void contentsChanged(Manager::ManagerDataEvent/*<Sensor>*/* e);

private:
 // Data listen & audit methods
 int events;
 int lastEvent0;
 int lastEvent1;
 int lastType;
 QString lastCall;


protected:
 /*protected*/ ProxySensorManager* l = nullptr;	// holds objects under test
 // Property listen & audit methods
 static /*protected*/ int propertyListenerCount;// = 0;
 static /*protected*/ QString propertyListenerLast;// = null;

};

#endif // PROXYSENSORMANAGERTEST_H
