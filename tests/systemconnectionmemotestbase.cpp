#include "systemconnectionmemotestbase.h"
#include "assert1.h"
#include "systemconnectionmemo.h"
#include "instancemanager.h"

SystemConnectionMemoTestBase::SystemConnectionMemoTestBase(QObject *parent) : QObject(parent)
{

}
/**
 * Abstract base class for SystemConnectionMemo objects.
 *
 * @author Paul Bender Copyright (C) 2017
 */
//abstract /*public*/ class SystemConnectionMemoTestBase {


    /*public*/ void SystemConnectionMemoTestBase::getTest(QString t){
       if(scm->provides(t)){
          // if the manager reports providing the class, make sure it exists.
          Assert::assertNotNull("Provides Class " + t/*->getName()*/, scm->get(t), __FILE__, __LINE__);
       } else {
          Assert::assertNull("Provides Class " + t/*->getName()*/, scm->get(t), __FILE__, __LINE__);
       }
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getPowerManager(){
        getTest("PowerManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getTurnoutManager(){
        getTest("TurnoutManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getThrottleManager(){
        getTest("ThrottleManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getSensorManager(){
        getTest("SensorManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getLightManager(){
        getTest("LightManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::getReporterManager(){
        getTest("ReporterManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::testCtor() {
        Assert::assertNotNull("exists", scm->self(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::testProvidesConsistManager() {
        getTest("ReporterManager");
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::testGetAndSetPrefix() {
       scm->setSystemPrefix("A2");
       Assert::assertEquals("System Prefix after set", "A2", scm->getSystemPrefix(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void SystemConnectionMemoTestBase::testMultipleMemosSamePrefix() {
        SystemConnectionMemo* t = new SystemConnectionMemoO1("t", "test", this);
//        {
//            @Override
//            protected ResourceBundle getActionModelResourceBundle() {
//                return null;
//            }
//        };
        Assert::assertEquals("t", t->getSystemPrefix(), __FILE__, __LINE__);
        t->_register();
        Assert::assertTrue(InstanceManager::getList("SystemConnectionMemo")->contains(t->self()), __FILE__, __LINE__);
        Assert::assertFalse(scm->setSystemPrefix("t"), __FILE__, __LINE__);
        Assert::assertTrue(scm->setSystemPrefix("t2"), __FILE__, __LINE__);
        Assert::assertEquals("t2", scm->getSystemPrefix(), __FILE__, __LINE__);
    }

    //@Before
    //abstract /*public*/ void setUp();

    //@After
    //abstract /*public*/ void tearDown();
