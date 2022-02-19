#include "abstractprovidingmemorymanagertestbase.h"
#include "junitappender.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "assume.h"
#include "memorymanager.h"

AbstractProvidingMemoryManagerTestBase::AbstractProvidingMemoryManagerTestBase()
{
 l= (MemoryManager*)InstanceManager::memoryManagerInstance();
}
/**
 * Extension of AbstractManagerTestBase base for ProvidingManager test classes.
 * <p>
 * This is not itself a test class, e.g. should not be added to a suite.
 * Instead, this forms the base for test classes, including providing some
 * common tests.
 *
 * @author Paul Bender Copyright (C) 2019
 * @param <T> the class being tested
 * @param <E> the class of NamedBean handled by T
 */
// /*public*/ abstract class <T extends ProvidingManager<E>, E extends NamedBean> extends AbstractManagerTestBase<T, E> {

//@Test(expected = IllegalArgumentException.class)
/*public*/ void AbstractProvidingMemoryManagerTestBase::testProvideEmpty() throw (IllegalArgumentException) {
   MemoryManager* m = (MemoryManager*)l->self();
    try {
        m->provide(""); // this should throw an IllegalArgumentException.
    } catch (IllegalArgumentException iae) {
        JUnitAppender::suppressErrorMessageStartsWith("Invalid system name for", __FILE__, __LINE__);
//        throw iae; // rethrow the expected exception, after suppressing the error
    }
}

//@Test
/*public*/ void AbstractProvidingMemoryManagerTestBase::testRegisterDuplicateSystemName() throw (PropertyVetoException,/* NoSuchFieldException,
        NoSuchFieldException,*/ IllegalArgumentException, IllegalAccessException ){
    MemoryManager* m = (MemoryManager*)l->self();
    QString s1 = m->makeSystemName("1");
    QString s2 = m->makeSystemName("2");
    testRegisterDuplicateSystemName(m, s1, s2);
}

/*public*/ void AbstractProvidingMemoryManagerTestBase::testRegisterDuplicateSystemName(MemoryManager* m, QString s1, QString s2)
        throw (PropertyVetoException, /*NoSuchFieldException,
        NoSuchFieldException, */IllegalArgumentException, IllegalAccessException) {
    Assert::assertNotNull(s1, __FILE__, __LINE__);
    Assert::assertFalse(s1.isEmpty(), __FILE__, __LINE__);
    Assert::assertNotNull(s2, __FILE__, __LINE__);
    Assert::assertFalse(s2.isEmpty(), __FILE__, __LINE__);

    Memory* e1;
    Memory* e2;

    try {
        e1 = m->provide(s1);
        e2 = m->provide(s2);
    } catch (
            IllegalArgumentException */* |
            com.pi4j.io.gpio.exception.GpioPinExistsException |
            NullPointerException |
            ArrayIndexOutOfBoundsException*/ ex)
            {
        // jmri.jmrix.pi.RaspberryPiTurnout(Providing)ManagerTest gives a GpioPinExistsException here.
        // jmri.jmrix.openlcb.OlcbLightProvidingManagerTest gives a NullPointerException here.
        // jmri.jmrix.openlcb.OlcbSensorProvidingManagerTest gives a ArrayIndexOutOfBoundsException here.
        // Some other tests give an IllegalArgumentException here.

        // If the test is unable to provide a named bean, abort this test.
        JUnitAppender::clearBacklog(LogLevel::WARN);
        log->debug("Cannot provide a named bean", ex);
        Assume::assumeTrue("We got no exception", false);
        return;
    }
#if 0
    // Use reflection to change the systemName of e2
    // Try to find the field
    Field f1 = getField(e2.getClass(), "mSystemName");
    f1.setAccessible(true);
    f1.set(e2, e1.getSystemName());
#else
    e2->mSystemName = e1->getSystemName();
#endif

    // Remove bean if it's already registered
    if (l->getBeanBySystemName(e1->getSystemName()) != nullptr) {
        l->deregister(e1);
    }
    // Remove bean if it's already registered
    if (l->getBeanBySystemName(e2->getSystemName()) != nullptr) {
        l->deregister(e2);
    }

    // Register the bean once. This should be OK.
    l->Register(e1);

    // Register bean twice. This gives only a debug message.
    l->Register(e1);

    QString expectedMessage = "systemName is already registered: " + e1->getSystemName();
    try {
        // Register different bean with existing systemName.
        // This should fail with an DuplicateSystemNameException.
        l->Register(e2);
        Assert::fail("Expected exception not thrown", __FILE__, __LINE__);
    } catch (NamedBean::DuplicateSystemNameException* ex) {
        Assert::assertEquals("exception message is correct", expectedMessage, ex->getMessage(), __FILE__, __LINE__);
        JUnitAppender::assertErrorMessage(expectedMessage, __FILE__, __LINE__);
    }

    l->deregister(e1);
}
#if 0
/*protected*/ Field getField(Class c, String fieldName) {
    try {
        return c.getDeclaredField(fieldName);
    } catch (NoSuchFieldException ex) {
        if (c.getSuperclass() != null)
            return getField(c.getSuperclass(), fieldName);
    }

    // Field not found
    return null;
}
#endif
/*private*/ /*final*/ /*static*/ Logger* AbstractProvidingMemoryManagerTestBase::log = LoggerFactory::getLogger("AbstractProvidingManagerTestBase");
