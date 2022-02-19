#include "abstractprovidingreportermanagertestbase.h"
#include "reportermanager.h"
#include "junitappender.h"
#include "assert1.h"
#include "assume.h"
#include "loggerfactory.h"
#include "loglevel.h"
#include "proxyreportermanager.h"

AbstractProvidingReporterManagerTestBase::AbstractProvidingReporterManagerTestBase(QObject *parent) : AbstractManagerTestBase(parent)
{

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
// /*public*/ abstract class AbstractProvidingManagerTestBase<T extends ProvidingManager/*<E>*/*, E extends NamedBean> extends AbstractManagerTestBase<T, E> {

    //@Test(expected = IllegalArgumentException.class)
    /*public*/ void AbstractProvidingReporterManagerTestBase::testProvideEmpty() throw (IllegalArgumentException) {
        ProxyReporterManager/*<E>*/* m = (ProxyReporterManager*)l->self();
        try {
            m->provide(""); // this should throw an IllegalArgumentException.
        } catch (IllegalArgumentException iae) {
            JUnitAppender::suppressErrorMessageStartsWith("Invalid system name for", __FILE__, __LINE__);
//            throw iae; // rethrow the expected exception, after suppressing the error
        }
    }

    //@Test
    /*public*/ void AbstractProvidingReporterManagerTestBase::testRegisterDuplicateSystemName() throw (PropertyVetoException, /*NoSuchFieldException,
            NoSuchFieldException,*/ IllegalArgumentException, IllegalAccessException) {
        ProxyReporterManager/*<E>*/* m = (ProxyReporterManager*)l->self();
        QString s1 = l->makeSystemName("1");
        QString s2 = l->makeSystemName("2");
        testRegisterDuplicateSystemName(m, s1, s2);
    }

    /*public*/ void AbstractProvidingReporterManagerTestBase::testRegisterDuplicateSystemName(ProxyReporterManager/*<E>*/* m, QString s1, QString s2)
            throw (PropertyVetoException, /*NoSuchFieldException,
            NoSuchFieldException, */IllegalArgumentException, IllegalAccessException) {
        Assert::assertNotNull(s1, __FILE__, __LINE__);
        Assert::assertFalse(s1.isEmpty(), __FILE__, __LINE__);
        Assert::assertNotNull(s2, __FILE__, __LINE__);
        Assert::assertFalse(s2.isEmpty(), __FILE__, __LINE__);

        Reporter* e1;
        Reporter* e2;

        try {
            e1 = (Reporter*)m->provide(s1);
            e2 = (Reporter*)m->provide(s2);
        } catch (
                IllegalArgumentException* /*|
                com.pi4j.io.gpio.exception.GpioPinExistsException |
                NullPointerException |
                ArrayIndexOutOfBoundsException*/ ex) {
            // jmri.jmrix.pi.RaspberryPiTurnout(Providing)ManagerTest gives a GpioPinExistsException here.
            // jmri.jmrix.openlcb.OlcbLightProvidingManagerTest gives a NullPointerException here.
            // jmri.jmrix.openlcb.OlcbSensorProvidingManagerTest gives a ArrayIndexOutOfBoundsException here.
            // Some other tests give an IllegalArgumentException here.

            // If the test is unable to provide a named bean, abort this test.
            JUnitAppender::clearBacklog(LogLevel::WARN);
            log->debug("Cannot provide a named bean", ex);
            Assume::assumeTrue("We got no exception");
            return;
        }
#if 0
        // Use reflection to change the systemName of e2
        // Try to find the field
        Field f1 = getField(e2.getClass(), "mSystemName");
        f1.setAccessible(true);
        f1.set(e2, e1.getSystemName());
#else
        ((AbstractNamedBean*)e2->self())->mSystemName = ((NamedBean*)e1->self())->getSystemName();
#endif

        // Remove bean if it's already registered
        if (l->getBeanBySystemName(((NamedBean*)e1->self())->getSystemName()) != nullptr) {
            l->deregister((NamedBean*)e1);
        }
        // Remove bean if it's already registered
        if (l->getBeanBySystemName(((NamedBean*)e2->self())->getSystemName()) != nullptr) {
            l->deregister((NamedBean*)e2);
        }

        // Register the bean once. This should be OK.
        l->Register((NamedBean*)e1);

        // Register bean twice. This gives only a debug message.
        l->Register((NamedBean*)e1);

        QString expectedMessage = "systemName is already registered: " + ((NamedBean*)e1->self())->getSystemName();
        try {
            // Register different bean with existing systemName.
            // This should fail with an DuplicateSystemNameException.
            ((ReporterManager*)l->self())->Register((NamedBean*)e2);
            Assert::fail("Expected exception not thrown", __FILE__, __LINE__);
        } catch (NamedBean::DuplicateSystemNameException* ex) {
            Assert::assertEquals("exception message is correct", expectedMessage, ex->getMessage(), __FILE__, __LINE__);
            JUnitAppender::assertErrorMessage(expectedMessage, __FILE__, __LINE__);
        }

        ((ReporterManager*)l->self())->deregister((NamedBean*)e1);
    }
#if 0
    protected Field getField(Class c, String fieldName) {
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
    /*private*/ /*final*/ /*static*/ Logger* AbstractProvidingReporterManagerTestBase::log = LoggerFactory::getLogger("AbstractProvidingManagerTestBase");

