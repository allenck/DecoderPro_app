#include "proxysensormanagertest.h"
#include "proxysensormanager.h"
#include "junitutil.h"
#include "assert1.h"
#include "instancemanager.h"
#include "junitappender.h"
#include "internalsystemconnectionmemo.h"
#include "internalsensormanager.h"
#include "abstractsensormanager.h"
ProxySensorManagerTest::ProxySensorManagerTest(QObject *parent) : QObject(parent)
{

}
/**
 * Test the ProxySensorManager
 *
 * @author	Bob Jacobsen 2003, 2006, 2008, 2014
 */
// /*public*/ class ProxySensorManagerTest implements Manager.ManagerDataListener<Sensor>, PropertyChangeListener {


    //@Test
    /*public*/ void ProxySensorManagerTest::testDispose() {
        l->AbstractProxyManager::dispose();  // all we're really doing here is making sure the method exists
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testPutGetJ() {
        // create
        Sensor* tj = l->newSensor("JS1", "mine");
        // check
        Assert::assertTrue("real object returned ", tj != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", tj == l->AbstractProxyManager::getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", tj == l->AbstractProxyManager::getBySystemName("JS1"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testSensorNameCase() {
        Assert::assertEquals(0, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);
        // create
        Sensor* t = l->provideSensor("IS:XYZ");
        Assert::assertNotEquals(t, l->provideSensor("IS:xyz"), __FILE__, __LINE__);  // upper case and lower case are different objects
        // check
        Assert::assertTrue("real object returned ", t != nullptr, __FILE__, __LINE__);
        Assert::assertEquals("IS:XYZ", t->getSystemName(), __FILE__, __LINE__);  // we force upper
        Assert::assertTrue("system name correct ", t == l->AbstractProxyManager::getBySystemName("IS:XYZ"), __FILE__, __LINE__);
        Assert::assertEquals(2, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);
        Assert::assertEquals(2, l->AbstractProxyManager::getNamedBeanSet().size(), __FILE__, __LINE__);
        // test providing same name as existing Sensor* does not create new sensor
        l->provideSensor("IS:XYZ");
        Assert::assertEquals(2, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);
        Assert::assertEquals(2, l->AbstractProxyManager::getNamedBeanSet().size(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testPutGetI() {
        // create
        Sensor* ti = l->newSensor("IS1", "mine");
        // check
        Assert::assertTrue("real object returned ", ti != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", ti == l->AbstractProxyManager::getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", ti == l->AbstractProxyManager::getBySystemName("IS1"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testPutGetK() {
        // create
        Sensor* tk = l->newSensor("KS1", "mine");
        // check
        Assert::assertTrue("real object returned ", tk != nullptr, __FILE__, __LINE__);
        Assert::assertTrue("user name correct ", tk == l->AbstractProxyManager::getByUserName("mine"), __FILE__, __LINE__);
        Assert::assertTrue("system name correct ", tk == l->AbstractProxyManager::getBySystemName("KS1"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testDefaultSystemName() {
        // create
        Sensor* t = l->provideSensor("9");
        // check
        Assert::assertTrue("real object returned", t != nullptr, __FILE__, __LINE__);
        Assert::assertEquals("system name correct", "JS9", t->getSystemName(), __FILE__, __LINE__);
        Assert::assertEquals("can find by name", t, l->AbstractProxyManager::getBySystemName("JS9"), __FILE__, __LINE__);
    }

    //@Test(expected=IllegalArgumentException.class)
    /*public*/ void ProxySensorManagerTest::testProvideFailure() {
        try {
            l->provideSensor("");
            Assert::fail("didn't throw", __FILE__, __LINE__);
        }
        catch (IllegalArgumentException* ex) {
            JUnitAppender::assertErrorMessage("Invalid system name for Sensor: System name must start with \"" + l->AbstractProxyManager::getSystemNamePrefix() + "\".", __FILE__, __LINE__);
//            throw new ex;
        }
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testSingleObject() {
        // test that you always get the same representation
        Sensor* t1 = l->newSensor("JS1", "mine");
        Assert::assertTrue("t1 real object returned ", t1 != nullptr, __FILE__, __LINE__);
        Assert::assertEquals("same by user ", t1, l->AbstractProxyManager::getBySystemName("mine"), __FILE__, __LINE__);
        Assert::assertEquals("same by system ", t1, l->AbstractProxyManager::getBySystemName("JS1"), __FILE__, __LINE__);

        Sensor* t2 = l->newSensor("JS1", "mine");
        Assert::assertTrue("t2 real object returned ", t2 != nullptr, __FILE__, __LINE__);
        // check
        Assert::assertTrue("same new ", t1 == t2, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testMisses() {
        // try to get nonexistant objects
        Assert::assertTrue(nullptr == l->AbstractProxyManager::getBySystemName("foo"), __FILE__, __LINE__);
        Assert::assertTrue(nullptr == l->AbstractProxyManager::getBySystemName("bar"), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testUpperLower() {  // verify that names are case sensitive
        Sensor* t = l->provideSensor("JS1ABC");  // internal will always accept that name
        QString name = t->getSystemName();

        int prefixLength = l->AbstractProxyManager::getSystemPrefix().length()+1;     // 1 for type letter
        QString lowerName = name.mid(0,prefixLength)+name.mid(prefixLength, name.length()).toLower();

        Assert::assertNotEquals(t, l->getSensor(lowerName), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testRename() {
        // get
        Sensor* t1 = l->newSensor("JS1", "before");
        Assert::assertNotNull("t1 real object ", t1, __FILE__, __LINE__);
        t1->setUserName("after");
        Sensor* t2 = (Sensor*)l->AbstractProxyManager::getBySystemName("after");
        Assert::assertEquals("same object", t1, t2, __FILE__, __LINE__);
        Assert::assertEquals("no old object", nullptr, l->AbstractProxyManager::getBySystemName("before")->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testTwoNames() {
        Sensor* jl212 = l->provideSensor("JS212");
        Sensor* jl211 = l->provideSensor("JS211");

        Assert::assertNotNull(jl212, __FILE__, __LINE__);
        Assert::assertNotNull(jl211, __FILE__, __LINE__);
        Assert::assertTrue(jl212 != jl211, __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testDefaultNotInternal() {
        Sensor* lut = l->provideSensor("211");

        Assert::assertNotNull(lut, __FILE__, __LINE__);
        Assert::assertEquals("JS211", lut->getSystemName(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testProvideUser() {
        Sensor* l1 = l->provideSensor("211");
        l1->setUserName("user 1");
        Sensor* l2 = l->provideSensor("user 1");
        Sensor* l3 = l->getSensor("user 1");

        Assert::assertNotNull(l1, __FILE__, __LINE__);
        Assert::assertNotNull(l2, __FILE__, __LINE__);
        Assert::assertNotNull(l3, __FILE__, __LINE__);
        Assert::assertEquals(l1, l2, __FILE__, __LINE__);
        Assert::assertEquals(l3, l2, __FILE__, __LINE__);
        Assert::assertEquals(l1, l3, __FILE__, __LINE__);

        Sensor* l4 = l->getSensor("JLuser 1");
        Assert::assertNull(l4, __FILE__, __LINE__);
    }

    // the following methods test code in Manager and AbstractManager,
    // but they need a concrete implementation to do it, hence are here.

    //@Test
    /*public*/ void ProxySensorManagerTest::testAddTracking() {
        Sensor* s1 = l->provideSensor("IS1");
        s1->setUserName("Sensor* 1");

        l->AbstractProxyManager::addDataListener((Manager::ManagerDataListener*)this);
        l->PropertyChangeSupport::addPropertyChangeListener("length", (PropertyChangeListener*)this);
        l->PropertyChangeSupport::addPropertyChangeListener("DisplayListName", (PropertyChangeListener*)this);

        // add an item
        Sensor* s2 = l->provideSensor("IS2");

        // property listener should have been immediately invoked
        Assert::assertEquals("propertyListenerCount", 1, propertyListenerCount, __FILE__, __LINE__);
        Assert::assertEquals("last call", "length", propertyListenerLast, __FILE__, __LINE__);

        s2->setUserName("Sensor* 2");

        Assert::assertEquals("propertyListenerCount", 2, propertyListenerCount, __FILE__, __LINE__);
        Assert::assertEquals("last call", "DisplayListName", propertyListenerLast, __FILE__, __LINE__);

        // data listener should have been immediately invoked
        Assert::assertEquals("events", 1, events, __FILE__, __LINE__);
        Assert::assertEquals("last call 1", "Added", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type 1", Manager::ManagerDataEvent::INTERVAL_ADDED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("start == end 1", lastEvent0, lastEvent1, __FILE__, __LINE__);
        Assert::assertEquals("index 1", 1, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("content at index 1", s2, l->AbstractProxyManager::getNamedBeanList()->value(lastEvent0), __FILE__, __LINE__);

        // add an item
        Sensor* s3 = l->newSensor("IS3", "Sensor* 3");

        // property listener should have been immediately invoked
        Assert::assertEquals("propertyListenerCount", 3, propertyListenerCount, __FILE__, __LINE__);
        Assert::assertEquals("last call", "length", propertyListenerLast, __FILE__, __LINE__);

        // listener should have been immediately invoked
        Assert::assertEquals("events", 2, events, __FILE__, __LINE__);
        Assert::assertEquals("last call 2", "Added", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type 2", Manager::ManagerDataEvent::INTERVAL_ADDED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("start == end 2", lastEvent0, lastEvent1, __FILE__, __LINE__);
        Assert::assertEquals("index 2", 2, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("content at index 2", s3, l->AbstractProxyManager::getNamedBeanList()->value(lastEvent0), __FILE__, __LINE__);

        // can add a manager and still get notifications
#if 0
        Manager* ism = new InternalSensorManager(new InternalSystemConnectionMemo("Z", "Zulu"));
        l->addManager((new InternalSensorManager(new InternalSystemConnectionMemo("Z", "Zulu"))));
#endif
        Sensor* s4 = l->provideSensor("ZS2");

        // property listener should have been immediately invoked
        Assert::assertEquals("propertyListenerCount", 4, propertyListenerCount, __FILE__, __LINE__);
        Assert::assertEquals("last call", "length", propertyListenerLast, __FILE__, __LINE__);

        // listener should have been immediately invoked
        Assert::assertEquals("events", 3, events, __FILE__, __LINE__);
        Assert::assertEquals("last call 2", "Added", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type 2", Manager::ManagerDataEvent::INTERVAL_ADDED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("start == end 2", lastEvent0, lastEvent1, __FILE__, __LINE__);
        Assert::assertEquals("index 3", 3, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("content at added index", s4, l->AbstractProxyManager::getNamedBeanList()->value(lastEvent0), __FILE__, __LINE__);


    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testRemoveTrackingI() {

        Sensor* s1 = l->provideSensor("IS1");
        s1->setUserName("Sensor* 1");
        Sensor* s2 = l->provideSensor("IS2");
        l->provideSensor("IS3");

        l->AbstractProxyManager::addDataListener(this);
        QList<NamedBean*>* tlist = l->AbstractProxyManager::getNamedBeanList();

        l->AbstractProxyManager::deregister(s2);

        // listener should have been immediately invoked
        Assert::assertEquals("events", 1, events, __FILE__, __LINE__);
        Assert::assertEquals("last call", "Removed", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type", Manager::ManagerDataEvent::INTERVAL_REMOVED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("start == end 2", lastEvent0, lastEvent1, __FILE__, __LINE__);
        Assert::assertEquals("index", 1, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("content at index", s2, tlist->at(lastEvent0), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testRemoveTrackingJ() {

        l->provideSensor("IS10");
        l->provideSensor("IS11");

        Sensor* s1 = l->provideSensor("JS1");
        s1->setUserName("Sensor* 1");
        Sensor* s2 = l->provideSensor("JS2");
        l->provideSensor("JS3");

        l->AbstractProxyManager::addDataListener(this);
        QList<NamedBean*>* tlist = l->AbstractProxyManager::getNamedBeanList();

        l->AbstractProxyManager::deregister(s2);

        // listener should have been immediately invoked
        Assert::assertEquals("events", 1, events, __FILE__, __LINE__);
        Assert::assertEquals("last call", "Removed", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type", Manager::ManagerDataEvent::INTERVAL_REMOVED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("start == end 2", lastEvent0, lastEvent1, __FILE__, __LINE__);
        Assert::assertEquals("index", 3, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("content at index", s2, tlist->at(lastEvent0), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testGetObjectCount() {
        Assert::assertEquals(0, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);

        l->provideSensor("IS10");
        Assert::assertEquals(1, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);

        l->provideSensor("JS1");
        Assert::assertEquals(2, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);

        l->provideSensor("IS11");
        Assert::assertEquals(3, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);

        Sensor* s2 = l->provideSensor("JS2");
        l->provideSensor("JS3");
        Assert::assertEquals(5, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);

        l->AbstractProxyManager::deregister(s2);
        Assert::assertEquals(4, l->AbstractProxyManager::getObjectCount(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testRemoveTrackingJMute() {

        l->AbstractProxyManager::setDataListenerMute(true);

        l->provideSensor("IS10");
        l->provideSensor("IS11");

        Sensor* s1 = l->provideSensor("JS1");
        s1->setUserName("Sensor* 1");
        Sensor* s2 = l->provideSensor("JS2");
        l->provideSensor("JS3");

        l->AbstractProxyManager::addDataListener(this);

        l->AbstractProxyManager::deregister(s2);

        // listener should have not been invoked
        Assert::assertEquals("events", 0, events, __FILE__, __LINE__);

        // unmute and get notification
        l->AbstractProxyManager::setDataListenerMute(false);
        Assert::assertEquals("events", 1, events, __FILE__, __LINE__);
        Assert::assertEquals("last call", "Changed", lastCall, __FILE__, __LINE__);
        Assert::assertEquals("type", Manager::ManagerDataEvent::CONTENTS_CHANGED, lastType, __FILE__, __LINE__);
        Assert::assertEquals("index0", 0, lastEvent0, __FILE__, __LINE__);
        Assert::assertEquals("index1", 3, lastEvent1, __FILE__, __LINE__); // originally five items, deleted 1, so 4, and last index is then 3
    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testOrderVsSorted() {
        Sensor* s4 = l->provideSensor("IS4");
        Sensor* s2 = l->provideSensor("IS2");

        QList<QString> sortedList = l->AbstractProxyManager::getSystemNameList();
        QList<NamedBean*>* beanList = l->AbstractProxyManager::getNamedBeanList();
        QSet<NamedBean*> beanSet = l->AbstractProxyManager::getNamedBeanSet();
        QStringList sortedArray = l->AbstractProxyManager::getSystemNameArray();
        JUnitAppender::suppressWarnMessage("Manager#getSystemNameArray() is deprecated", __FILE__, __LINE__);

        Assert::assertEquals("sorted list length", 2, sortedList.size(), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 1st", "IS2", sortedList.at(0), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 2nd", "IS4", sortedList.at(1), __FILE__, __LINE__);

        Assert::assertEquals("bean list length", 2, beanList->size(), __FILE__, __LINE__);
        Assert::assertEquals("bean list 1st", s2, beanList->at(0), __FILE__, __LINE__);
        Assert::assertEquals("bean list 2nd", s4, beanList->at(1), __FILE__, __LINE__);

        Assert::assertEquals("bean set length", 2, beanSet.size(), __FILE__, __LINE__);
        //Iterator<Sensor> iter = beanSet.iterator();
        QSetIterator<NamedBean*> iter(beanSet);
        Assert::assertEquals("bean set 1st", s2, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 2nd", s4, iter.next(), __FILE__, __LINE__);

        Assert::assertEquals("sorted array length", 2, sortedArray.length(), __FILE__, __LINE__);
        Assert::assertEquals("sorted array 1st", "IS2", sortedArray[0], __FILE__, __LINE__);
        Assert::assertEquals("sorted array 2nd", "IS4", sortedArray[1], __FILE__, __LINE__);

        // add and test (non) liveness
        Sensor* s3 = l->provideSensor("IS3");
        Sensor* s1 = l->provideSensor("IS1");

        Assert::assertEquals("sorted list length", 2, sortedList.size(), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 1st", "IS2", sortedList.at(0), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 2nd", "IS4", sortedList.at(1), __FILE__, __LINE__);

        Assert::assertEquals("bean list length", 2, beanList->size(), __FILE__, __LINE__);
        Assert::assertEquals("bean list 1st", s2, beanList->at(0), __FILE__, __LINE__);
        Assert::assertEquals("bean list 2nd", s4, beanList->at(1), __FILE__, __LINE__);

        Assert::assertEquals("bean set length", 4, beanSet.size(), __FILE__, __LINE__);
        iter = QSetIterator<NamedBean*>(beanSet);//beanSet.iterator();
        Assert::assertEquals("bean set 1st", s1, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 2nd", s2, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 3rd", s3, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 4th", s4, iter.next(), __FILE__, __LINE__);

        Assert::assertEquals("sorted array length", 2, sortedArray.length(), __FILE__, __LINE__);
        Assert::assertEquals("sorted array 1st", "IS2", sortedArray[0], __FILE__, __LINE__);
        Assert::assertEquals("sorted array 2nd", "IS4", sortedArray[1], __FILE__, __LINE__);

        // update and test update
        sortedList = l->AbstractProxyManager::getSystemNameList();
        beanList = l->AbstractProxyManager::getNamedBeanList();
        beanSet = l->AbstractProxyManager::getNamedBeanSet();
        sortedArray = l->AbstractProxyManager::getSystemNameArray();
        JUnitAppender::suppressWarnMessage("Manager#getSystemNameArray() is deprecated", __FILE__, __LINE__);

        Assert::assertEquals("sorted list length", 4, sortedList.size(), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 1st", "IS1", sortedList.at(0), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 2nd", "IS2", sortedList.at(1), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 3rd", "IS3", sortedList.at(2), __FILE__, __LINE__);
        Assert::assertEquals("sorted list 4th", "IS4", sortedList.at(3), __FILE__, __LINE__);

        Assert::assertEquals("bean list length", 4, beanList->size(), __FILE__, __LINE__);
        Assert::assertEquals("bean list 1st", s1, beanList->at(0), __FILE__, __LINE__);
        Assert::assertEquals("bean list 2nd", s2, beanList->at(1), __FILE__, __LINE__);
        Assert::assertEquals("bean list 3rd", s3, beanList->at(2), __FILE__, __LINE__);
        Assert::assertEquals("bean list 4th", s4, beanList->at(3), __FILE__, __LINE__);

        Assert::assertEquals("bean set length", 4, beanSet.size(), __FILE__, __LINE__);
        iter = QSetIterator<NamedBean*>(beanSet);//beanSet.iterator();
        Assert::assertEquals("bean set 1st", s1, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 2nd", s2, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 3rd", s3, iter.next(), __FILE__, __LINE__);
        Assert::assertEquals("bean set 4th", s4, iter.next(), __FILE__, __LINE__);

        Assert::assertEquals("sorted array length", 4, sortedArray.length(), __FILE__, __LINE__);
        Assert::assertEquals("sorted array 1st", "IS1", sortedArray[0], __FILE__, __LINE__);
        Assert::assertEquals("sorted array 2nd", "IS2", sortedArray[1], __FILE__, __LINE__);
        Assert::assertEquals("sorted array 3rd", "IS3", sortedArray[2], __FILE__, __LINE__);
        Assert::assertEquals("sorted array 4th", "IS4", sortedArray[3], __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void ProxySensorManagerTest::testUnmodifiable() {
        Sensor* s1 = l->provideSensor("IS1");
        l->provideSensor("IS2");

        QList<QString> nameList = l->AbstractProxyManager::getSystemNameList();
        QList<NamedBean*>* beanList = l->AbstractProxyManager::getNamedBeanList();
        QSet<NamedBean*> beanSet = l->AbstractProxyManager::getNamedBeanSet();

        try {
            nameList.append("Foo");
            Assert::fail("nameList should have thrown", __FILE__, __LINE__);
        } catch (UnsupportedOperationException e) { /* this is OK */}

        try {
            beanList->append(s1);
            Assert::fail("beanList should have thrown", __FILE__, __LINE__);
        } catch (UnsupportedOperationException e) { /* this is OK */}

        try {
            beanSet.insert(s1);
            Assert::fail("beanSet should have thrown", __FILE__, __LINE__);
        } catch (UnsupportedOperationException e) { /* this is OK */}

    }

    // check how proxy is integrated with defaults
    //@Test
    /*public*/ void ProxySensorManagerTest::testInstanceManagerIntegration() {
        JUnitUtil::resetInstanceManager();
        Assert::assertNotNull(InstanceManager::getDefault("SensorManager"), __FILE__, __LINE__);

        JUnitUtil::initInternalSensorManager();

        Assert::assertTrue(qobject_cast<ProxySensorManager*>(InstanceManager::getDefault("SensorManager"))!= nullptr, __FILE__, __LINE__);

        Assert::assertNotNull(InstanceManager::getDefault("SensorManager"), __FILE__, __LINE__);
        Assert::assertNotNull(((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("IS1"), __FILE__, __LINE__);

        InternalSensorManager* m = new InternalSensorManager(new InternalSystemConnectionMemo("J", "Juliet"));
        InstanceManager::setSensorManager(m);

        Assert::assertNotNull(((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("JS1"), __FILE__, __LINE__);
        Assert::assertNotNull(((SensorManager*)InstanceManager::getDefault("SensorManager"))->provideSensor("IS2"), __FILE__, __LINE__);
    }

    // Property listen & audit methods
    /*static*/ /*protected*/ int ProxySensorManagerTest::propertyListenerCount = 0;
    /*static*/ /*protected*/ QString ProxySensorManagerTest::propertyListenerLast = nullptr;

    //@Override
    /*public*/ void ProxySensorManagerTest::propertyChange(PropertyChangeEvent* e) {
        propertyListenerCount++;
        propertyListenerLast = e->getPropertyName();
    }


    //@Override
    /*public*/ void ProxySensorManagerTest::intervalAdded(Manager::ManagerDataEvent/*<Sensor>*/* e) {
        events++;
        lastEvent0 = e->getIndex0();
        lastEvent1 = e->getIndex1();
        lastType = e->getType();
        lastCall = "Added";
    }
    //@Override
    /*public*/ void ProxySensorManagerTest::intervalRemoved(Manager::ManagerDataEvent/*<Sensor>*/* e) {
        events++;
        lastEvent0 = e->getIndex0();
        lastEvent1 = e->getIndex1();
        lastType = e->getType();
        lastCall = "Removed";
    }
    //@Override
    /*public*/ void ProxySensorManagerTest::contentsChanged(Manager::ManagerDataEvent/*<Sensor>*/* e) {
        events++;
        lastEvent0 = e->getIndex0();
        lastEvent1 = e->getIndex1();
        lastType = e->getType();
        lastCall = "Changed";
    }

    //@Before
    /*public*/ void ProxySensorManagerTest::setUp() {
        JUnitUtil::setUp();
        // create and register the manager object
        l = new ProxySensorManager();
        // initially has three systems: IS, JS, KS
#if 0
        l->addManager(new InternalSensorManager(new InternalSystemConnectionMemo("J", "Juliet")));
        l->addManager(new InternalSensorManager(new InternalSystemConnectionMemo("I", "India"))); // not in alpha order to make it exciting
        l->addManager(new InternalSensorManager(new InternalSystemConnectionMemo("K", "Kilo")));
#endif
        InstanceManager::setSensorManager((AbstractSensorManager*)l);

        propertyListenerCount = 0;
        propertyListenerLast = nullptr;

        events = 0;
        lastEvent0 = -1;
        lastEvent1 = -1;
        lastType = -1;
        lastCall = nullptr;
    }

    //@After
    /*public*/ void ProxySensorManagerTest::tearDown() {
        JUnitUtil::tearDown();
    }
