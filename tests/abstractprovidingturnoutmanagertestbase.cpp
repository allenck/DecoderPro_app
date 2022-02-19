#include "abstractprovidingturnoutmanagertestbase.h"
#include "junitappender.h"
#include "assert1.h"
#include "loggerfactory.h"
#include "manager.h"
#include "level.h"
#include "assume.h"
#include "turnout.h"
#include "field.h"
#include "turnoutmanager.h"
#include "instancemanager.h"

// NOTE: This is a non-template version of AbstractProvidingManagerTestBase

AbstractProvidingTurnoutManagerTestBase::AbstractProvidingTurnoutManagerTestBase(QObject *parent)
{
 l= qobject_cast<Manager*>(InstanceManager::turnoutManagerInstance()->self());
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
    /*public*/ void AbstractProvidingTurnoutManagerTestBase::testProvideEmpty() throw (IllegalArgumentException) {
        TurnoutManager* m = (TurnoutManager*)l->self();
        try {
            m->provide(""); // this should throw an IllegalArgumentException.
        } catch (IllegalArgumentException iae) {
            JUnitAppender::suppressErrorMessageStartsWith("Invalid system name for", __FILE__, __LINE__);
//            throw iae; // rethrow the expected exception, after suppressing the error
        }
    }

    //@Test
    /*public*/ void AbstractProvidingTurnoutManagerTestBase::testRegisterDuplicateSystemName() throw (PropertyVetoException, /*NoSuchFieldException,
            NoSuchFieldException,*/ IllegalArgumentException, IllegalAccessException ){
        TurnoutManager* m = (TurnoutManager*)l->self();
        QString s1 = l->makeSystemName("1");
        QString s2 = l->makeSystemName("2");
        testRegisterDuplicateSystemName(m, s1, s2);
    }

    /*public*/ void AbstractProvidingTurnoutManagerTestBase::testRegisterDuplicateSystemName(TurnoutManager* m, QString s1, QString s2)
            throw (PropertyVetoException,/* NoSuchFieldException,
            NoSuchFieldException,*/ IllegalArgumentException, IllegalAccessException) {
        Assert::assertNotNull(s1, __FILE__, __LINE__);
        Assert::assertFalse(s1.isEmpty(), __FILE__, __LINE__);
        Assert::assertNotNull(s2, __FILE__, __LINE__);
        Assert::assertFalse(s2.isEmpty(), __FILE__, __LINE__);

        Turnout* e1;
        Turnout* e2;

        try {
            e1 = (Turnout*)m->provide(s1);
            e2 = (Turnout*)m->provide(s2);
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
            Assume::assumeTrue("We got no exception", false);
            return;
        }
#if 0
        // Use reflection to change the systemName of e2
        // Try to find the field
        Field f1 = getField(e2->getClass(), "mSystemName");
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
    /*protected*/ Field AbstractProvidingTurnoutManagerTestBase::getField(Class c, QString fieldName) {
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
    /*private*/ /*final*/ /*static*/ Logger* AbstractProvidingTurnoutManagerTestBase::log = LoggerFactory::getLogger("AbstractProvidingTurnoutManagerTestBase");
