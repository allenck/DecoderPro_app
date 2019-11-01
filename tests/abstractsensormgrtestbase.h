#ifndef ABSTRACTSENSORMGRTESTBASE_H
#define ABSTRACTSENSORMGRTESTBASE_H

#include "abstractmanagertestbase.h"
#include "propertychangelistener.h"
#include "sensormanager.h"
#include "proxysensormanager.h"

class AbstractSensorMgrTestBase : public AbstractManagerTestBase
{
 Q_OBJECT
public:
 explicit AbstractSensorMgrTestBase(QObject *parent = nullptr);
 virtual /*public*/ void setUp() =0;    	// load l with actual object; create scaffolds as needed
 virtual /*public*/ QString getSystemName(int i) {return "";}

signals:

public slots:
 /*public*/ void testCreate();
 /*public*/ void testDispose();
 /*public*/ void testSensorPutGet();
 /*public*/ void testDelete();
 /*public*/ void testProvideName();
 /*public*/ void testDefaultSystemName();
 /*public*/ void testProvideFailure();
 /*public*/ void testSettings();
 /*public*/ void testSingleObject();
 virtual /*public*/ void testMisses();
 /*public*/ void testMoveUserName();
 /*public*/ void testUpperLower();
 /*public*/ void testRename();
 /*public*/ void testPullResistanceConfigurable();
private:
 SensorManager* l;

protected:
 static /*protected*/ bool listenerResult;// = false;
 /*protected*/ int getNumToTest1();
 /*protected*/ int getNumToTest2();

 friend class ListenO3;
 friend class LnSensorManagerTest;
};

/*protected*/ class ListenO3 : public PropertyChangeListener {
 Q_OBJECT
 AbstractSensorMgrTestBase* base;
public:
 ListenO3(AbstractSensorMgrTestBase* base) {this->base = base;}
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

#endif // ABSTRACTSENSORMGRTESTBASE_H
