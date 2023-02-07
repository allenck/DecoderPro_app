#include "abstractmanagertestbase.h"
#include "assert1.h"
#include "abstractmanager.h"
#include "proxymanager.h"
#include "junitappender.h"
#include "namedbean.h"

AbstractManagerTestBase::AbstractManagerTestBase(QObject *parent) : QObject(parent)
{

}

/**
 * Base for the various Abstract*MgrTestBase base classes for NamedBean Manager test classes
 * <p>
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests.
 * <p>
 * Quite a bit of AbstractManager testing is done in InternalSensorManagerTest
 * to give it a concrete platform
 *
 * @author Bob Jacobsen Copyright (C) 2017
 * @param <T> the class being tested
 * @param <E> the class of NamedBean handled by T
 */
// /*public*/ abstract class AbstractManagerTestBase<T extends Manager<E>, E extends NamedBean> {


    // check that you can add and remove listeners
    //@Test
    /*public*/ /*final*/ void AbstractManagerTestBase::testManagerDataListenerAddAndRemove() {
#if 0  // need ManagerDataListener in Manager
        Manager.ManagerDataListener<E> listener = new Manager.ManagerDataListener<E>(){
            @Override /*public*/ void contentsChanged(Manager.ManagerDataEvent<E> e){}
            @Override /*public*/ void intervalAdded(Manager.ManagerDataEvent<E> e) {}
            @Override /*public*/ void intervalRemoved(Manager.ManagerDataEvent<E> e) {}
        };

        _manager->addDataListener(listener);
        _manager->removeDataListener(listener);

        _manager->addDataListener(null);
        _manager->removeDataListener(null);

        _manager->addDataListener(null);
        _manager->removeDataListener(listener);

        _manager->addDataListener(listener);
        _manager->removeDataListener(null);
#endif
    }

    //@Test
    /*public*/ /*final*/ void AbstractManagerTestBase::testPropertyChangeListenerAddAndRemove() {
        int base = ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length();

        PropertyChangeListenerO2* listener = new PropertyChangeListenerO2();
//        {
//            @Override
//            /*public*/ void PropertyChangeListenerO2::propertyChange(PropertyChangeEvent* evt)
//            {
//                // do nothing
//            }
//        };

        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->PropertyChangeSupport::addPropertyChangeListener(listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->PropertyChangeSupport::removePropertyChangeListener(listener);
        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);

        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->PropertyChangeSupport::addPropertyChangeListener("property", listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);
        Assert::assertEquals(1, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners("property").length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->PropertyChangeSupport::removePropertyChangeListener("property", listener);
        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->PropertyChangeSupport::getPropertyChangeListeners().length(), __FILE__, __LINE__);

    }

    /*public*/ void PropertyChangeListenerO2::propertyChange(PropertyChangeEvent* evt)
    {
        // do nothing
    }


    //@Test
    /*public*/ /*final*/ void AbstractManagerTestBase::testVetoableChangeListenerAddAndRemove()
    {
        int base = ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length();

        VetoableChangeListener* listener = new VetoableChangeListenerO1();
//        {
//            @Override
//            /*public*/ void vetoableChange(PropertyChangeEvent evt) throws PropertyVetoException {
//                // do nothing
//            }
//        };

        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->VetoableChangeSupport::addVetoableChangeListener(listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->VetoableChangeSupport::removeVetoableChangeListener(listener);
        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);

        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->VetoableChangeSupport::addVetoableChangeListener("property", listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);
        Assert::assertEquals(1, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners("property")->length(), __FILE__, __LINE__);
        ((AbstractManager*)_manager->mself())->VetoableChangeSupport::removeVetoableChangeListener("property", listener);
        Assert::assertEquals(base, ((AbstractManager*)_manager->mself())->VetoableChangeSupport::getVetoableChangeListeners()->length(), __FILE__, __LINE__);
    }

    /*public*/ void VetoableChangeListenerO1::vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/ {
            // do nothing
    }

    //@Test
    /*public*/ void AbstractManagerTestBase::testMakeSystemName() {
        QString s = ((AbstractManager*)_manager->mself())->makeSystemName("1");
        Assert::assertNotNull(s, __FILE__, __LINE__);
        Assert::assertFalse(s.isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractManagerTestBase::testMakeSystemNameWithPrefix() {
        QString s = _manager->makeSystemName(_manager->getSystemNamePrefix()+getASystemNameWithNoPrefix());
        Assert::assertNotNull(s, __FILE__, __LINE__);
        Assert::assertFalse(s.isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/ void AbstractManagerTestBase::testMakeSystemNameWithNoPrefixNotASystemName() {

        //Assert::assertThrows("BadSystemNameException", () -> _manager->makeSystemName("$:"), __FILE__, __LINE__);
        bool thrown = false;
        try{
         _manager->makeSystemName("$:");
        }
        catch(NamedBean::BadSystemNameException*)
        {
         thrown = true;
        }
        Assert::assertTrue(thrown, __FILE__, __LINE__);
        JUnitAppender::assertErrorMessageStartsWith("Invalid system name for " + _manager->getBeanTypeHandled() + ": ", __FILE__, __LINE__);

    }

    //@Test
    /*public*/ void AbstractManagerTestBase::testMakeSystemNameWithPrefixNotASystemName() {

        //Assert::assertThrows("NamedBean::BadSystemNameException", [=]{ _manager->makeSystemName(_manager->getSystemNamePrefix()+"$:");});
        bool thrown = false;
        try{
         _manager->makeSystemName(_manager->getSystemNamePrefix()+"$:");
        }
        catch(NamedBean::BadSystemNameException*)
        {
         thrown = true;
        }
        JUnitAppender::assertErrorMessageStartsWith("Invalid system name for " + _manager->getBeanTypeHandled() + ": ", __FILE__, __LINE__);

    }



    //@Test
    /*public*/ void AbstractManagerTestBase::testAutoSystemNames() {
        AbstractManager* m = (AbstractManager/*<E>*/*) _manager->mself();
        QString sysPrefix = _manager->getSystemNamePrefix();
        Assert::assertEquals(sysPrefix + ":AUTO:0001", m->getAutoSystemName(), __FILE__, __LINE__);
        Assert::assertEquals(sysPrefix + ":AUTO:0002", m->getAutoSystemName(), __FILE__, __LINE__);
        Assert::assertEquals(sysPrefix + ":AUTO:0003", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(sysPrefix + ":AUTO:0011");
        Assert::assertEquals(sysPrefix + ":AUTO:0012", m->getAutoSystemName(), __FILE__, __LINE__);
        Assert::assertEquals(sysPrefix + ":AUTO:0013", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(sysPrefix + ":AUTO:0005");
        Assert::assertEquals(sysPrefix + ":AUTO:0014", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(sysPrefix + ":AUTO:0098");
        Assert::assertEquals(sysPrefix + ":AUTO:0099", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(sysPrefix + ":AUTO:0097");
        Assert::assertEquals(sysPrefix + ":AUTO:0100", m->getAutoSystemName(), __FILE__, __LINE__);
        Assert::assertEquals(sysPrefix + ":AUTO:0101", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(sysPrefix + ":AUT:0203");
        Assert::assertEquals(sysPrefix + ":AUTO:0102", m->getAutoSystemName(), __FILE__, __LINE__);
        m->updateAutoNumber(QString("12") + ":AUT:0203"); // Bad system name prefix
        Assert::assertEquals(sysPrefix + ":AUTO:0103", m->getAutoSystemName(), __FILE__, __LINE__);
    }

    /*protected*/ QString AbstractManagerTestBase::getASystemNameWithNoPrefix() {
        return "1";
    }
