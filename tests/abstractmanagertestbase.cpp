#include "abstractmanagertestbase.h"
#include "assert1.h"
#include "abstractmanager.h"
#include "proxymanager.h"

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

        l->addDataListener(listener);
        l->removeDataListener(listener);

        l->addDataListener(null);
        l->removeDataListener(null);

        l->addDataListener(null);
        l->removeDataListener(listener);

        l->addDataListener(listener);
        l->removeDataListener(null);
#endif
    }

    //@Test
    /*public*/ /*final*/ void AbstractManagerTestBase::testPropertyChangeListenerAddAndRemove() {
        int base = l->getPropertyChangeListeners().length();

        PropertyChangeListenerO2* listener = new PropertyChangeListenerO2();
//        {
//            @Override
//            /*public*/ void PropertyChangeListenerO2::propertyChange(PropertyChangeEvent* evt)
//            {
//                // do nothing
//            }
//        };

        Assert::assertEquals(base, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->addPropertyChangeListener(listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->removePropertyChangeListener(listener);
        Assert::assertEquals(base, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);

        Assert::assertEquals(base, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->addPropertyChangeListener("property", listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);
        Assert::assertEquals(1, ((AbstractManager*)l->self())->getPropertyChangeListeners("property").length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->removePropertyChangeListener("property", listener);
        Assert::assertEquals(base, ((AbstractManager*)l->self())->getPropertyChangeListeners().length(), __FILE__, __LINE__);

    }

    /*public*/ void PropertyChangeListenerO2::propertyChange(PropertyChangeEvent* evt)
    {
        // do nothing
    }


    //@Test
    /*public*/ /*final*/ void AbstractManagerTestBase::testVetoableChangeListenerAddAndRemove()
    {
        int base = ((AbstractManager*)l->self())->getVetoableChangeListeners().length();

        VetoableChangeListener* listener = new VetoableChangeListenerO1();
//        {
//            @Override
//            /*public*/ void vetoableChange(PropertyChangeEvent evt) throws PropertyVetoException {
//                // do nothing
//            }
//        };

        Assert::assertEquals(base, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->addVetoableChangeListener(listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->removeVetoableChangeListener(listener);
        Assert::assertEquals(base, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);

        Assert::assertEquals(base, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->addVetoableChangeListener("property", listener);
        Assert::assertEquals(base + 1, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);
        Assert::assertEquals(1, ((AbstractManager*)l->self())->getVetoableChangeListeners("property").length(), __FILE__, __LINE__);
        ((AbstractManager*)l->self())->removeVetoableChangeListener("property", listener);
        Assert::assertEquals(base, ((AbstractManager*)l->self())->getVetoableChangeListeners().length(), __FILE__, __LINE__);
    }

    /*public*/ void VetoableChangeListenerO1::vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException) {
            // do nothing
    }

    //@Test
    /*public*/ void AbstractManagerTestBase::testMakeSystemName() {
        QString s = ((AbstractManager*)l->self())->makeSystemName("1");
        Assert::assertNotNull(s, __FILE__, __LINE__);
        Assert::assertFalse(s.isEmpty(), __FILE__, __LINE__);
    }

