#include "vetoablechangesupporttest.h"
#include "junitutil.h"
#include "assert1.h"
#include "testvetoablechangelistener.h"
#include "junitappender.h"

VetoableChangeSupportTest::VetoableChangeSupportTest(QObject *parent) : QObject(parent)
{
 setObjectName("VetoableChangeSupportTest");
}
/**
 * @author Randall Wood Copyright 2020
 */
// /*public*/  class VetoableChangeSupportTest {

/*private*/ /*static*/ QString VetoableChangeSupportTest::PROPERTY = "property";
/*private*/ /*static*/ QString VetoableChangeSupportTest::VETO = "veto";

    //@Test
    /*public*/  void VetoableChangeSupportTest::testFireVetoableChange_String_int_boolean_boolean() {
        instance->addVetoableChangeListener(listener);
        Assert::assertFalse(listener->willThrowNext(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, false, true)).doesNotThrowAnyException();
        bool thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, false, true);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);
        Assert::assertEquals(listener->getEvents().size(), 1, __FILE__, __LINE__);
        PropertyChangeEvent* event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(), PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(),false, __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(),true, __FILE__, __LINE__);
        listener->clear();
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, false, false)).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, false, false);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        listener->throwNext(VETO);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, false, true)).isInstanceOf(PropertyVetoException.class).hasMessage(VETO);
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, false, true);
        }
        catch(Exception* ex)
        {
         if(ex->name == "PropertyVetoException")
          thrown = true;
        }
        Assert::assertTrue(thrown, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testFireVetoableChange_String_int_int_int() {
        instance->addVetoableChangeListener(listener);
        Assert::assertFalse(listener->willThrowNext(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, -1, 1)).doesNotThrowAnyException();
        bool thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, -1, 1);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);
        Assert::assertEquals(listener->getEvents().size(), 1, __FILE__, __LINE__);
        PropertyChangeEvent* event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(), PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(),-1, __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(),1, __FILE__, __LINE__);
        listener->clear();
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, 0, 0)).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, 0, 0);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        listener->throwNext(VETO);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, -1, 1)).isInstanceOf(PropertyVetoException.class).hasMessage(VETO);
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, -1, 1);
        }
        catch(Exception* ex)
        {
         if(ex->name == "PropertyVetoException")
          thrown = true;
        }
        Assert::assertTrue(thrown, __FILE__, __LINE__); }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testFireVetoableChange_String_int_Object_Object() {
        instance->addVetoableChangeListener(listener);
        QVariant object1 = QVariant();
        QVariant object2 = QVariant();
        Assert::assertNotEquals(object1,object2, __FILE__, __LINE__);
        Assert::assertTrue(listener->willThrowNext(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, object1, object2)).doesNotThrowAnyException();
        bool thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, object1, object2);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);Assert::assertEquals(listener->getEvents().size(),1, __FILE__, __LINE__);
        PropertyChangeEvent* event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(),PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(),object1, __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(), object2, __FILE__, __LINE__);
        listener->clear();
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, object1, object1)).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, object1, object1);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);
        Assert::assertTrue(listener->getEvents().isEmpty(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, ).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, object1, QVariant());
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(), PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(),object1, __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(),QVariant(), __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, null, object2)).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY,  QVariant(), object2);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(),PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(), QVariant(), __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(),object2, __FILE__, __LINE__);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, null, null)).doesNotThrowAnyException();
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, QVariant(),QVariant());
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);event = listener->getLastEvent();
        Assert::assertEquals(event->getPropertyName(),PROPERTY, __FILE__, __LINE__);
        Assert::assertEquals(event->getOldValue(),QVariant(), __FILE__, __LINE__);
        Assert::assertEquals(event->getNewValue(),QVariant(), __FILE__, __LINE__);
        listener->throwNext(VETO);
        //assertThatCode(() -> instance->fireVetoableChange(PROPERTY, object1, object2)).isInstanceOf(PropertyVetoException.class).hasMessage(VETO);
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, object1, object2);
        }
        catch(Exception* ex)
        {
         if(ex->name == "PropertyVetoException")
          thrown = true;
        }
        Assert::assertTrue(thrown, __FILE__, __LINE__);
}

    //@Test
    /*public*/  void VetoableChangeSupportTest::testFireVetoableChange_VetoableChangeEvent() {
        instance->addVetoableChangeListener(listener);
        QVariant object1 = QVariant();
        QVariant object2 = QVariant();
        Assert::assertNotEquals(object1,object2, __FILE__, __LINE__);
        PropertyChangeEvent* sent = new PropertyChangeEvent(instance, PROPERTY, object1, object2);
        //assertThatCode(() -> instance->fireVetoableChange(sent)).doesNotThrowAnyException();
        bool thrown = false;
        try
        {
         instance->fireVetoableChange(sent);
        }
        catch(Exception* ex)
        {
         thrown = true;
        }
        Assert::assertFalse(thrown, __FILE__, __LINE__);Assert::assertEquals(listener->getEvents().size(),1, __FILE__, __LINE__);
        Assert::assertEquals(listener->getLastEvent(),sent, __FILE__, __LINE__);
        listener->throwNext(VETO);
        //assertThatCode(() -> instance->fireVetoableChange(sent)).isInstanceOf(PropertyVetoException.class).hasMessage(VETO);
        thrown = false;
        try
        {
         instance->fireVetoableChange(PROPERTY, object1, object2);
        }
        catch(Exception* ex)
        {
         if(ex->name == "PropertyVetoException" && ex->getMessage() == VETO)
          thrown = true;
        }
        Assert::assertTrue(thrown, __FILE__, __LINE__); }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testAddVetoableChangeListener_VetoableChangeListener() {
        Assert::assertTrue(instance->getVetoableChangeListeners()->isEmpty(), __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
        instance->addVetoableChangeListener(listener);
        //assertThat(instance->getVetoableChangeListeners()).containsExactly(listener);
        Assert::assertTrue(instance->getVetoableChangeListeners()->count() == 1 && instance->getVetoableChangeListeners()->at(0)== listener, __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testAddVetoableChangeListener_String_VetoableChangeListener() {
        Assert::assertTrue(instance->getVetoableChangeListeners()->isEmpty(), __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
        instance->addVetoableChangeListener(PROPERTY, listener);
        VetoableChangeListener* listener2 = instance->getVetoableChangeListeners()->at(0);
//        assertThat(listener2).isExactlyInstanceOf(VetoableChangeListenerProxy.class);
//        Assert::assertTrue(((VetoableChangeListenerProxy) listener2).getListener()).isEqualTo(listener);
//        Assert::assertTrue(((VetoableChangeListenerProxy) listener2).getPropertyName()).isEqualTo(PROPERTY);
        //assertThat(instance->getVetoableChangeListeners(PROPERTY)).containsExactly(listener);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->count() ==1 && instance->getVetoableChangeListeners(PROPERTY)->at(0) == listener, __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testRemoveVetoableChangeListener_VetoableChangeListener() {
        instance->addVetoableChangeListener(listener);
        //assertThat(instance->getVetoableChangeListeners()).containsExactly(listener);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->count() ==1 && instance->getVetoableChangeListeners(PROPERTY)->at(0) == listener, __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
        instance->removeVetoableChangeListener(listener);
        Assert::assertTrue(instance->getVetoableChangeListeners()->isEmpty(), __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
    }

    //@Test
    /*public*/  void VetoableChangeSupportTest::testRemoveVetoableChangeListener_String_VetoableChangeListener() {
        instance->addVetoableChangeListener(PROPERTY, listener);
//        assertThat(instance->getVetoableChangeListeners()[0]).isExactlyInstanceOf(VetoableChangeListenerProxy.class);
        //assertThat(instance->getVetoableChangeListeners(PROPERTY)).containsExactly(listener);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->count() ==1 && instance->getVetoableChangeListeners(PROPERTY)->at(0) == listener, __FILE__, __LINE__);
        instance->removeVetoableChangeListener(PROPERTY, listener);
        Assert::assertTrue(instance->getVetoableChangeListeners()->isEmpty(), __FILE__, __LINE__);
        Assert::assertTrue(instance->getVetoableChangeListeners(PROPERTY)->isEmpty(), __FILE__, __LINE__);
    }

    //@BeforeEach
    /*public*/  void VetoableChangeSupportTest::setup() {
        JUnitUtil::setUp();
        instance = new VetoableChangeSupport();
        listener = new TestVetoableChangeListener();
    }

    //@AfterEach
    /*public*/  void VetoableChangeSupportTest::tearDown() {
        instance = nullptr;
        listener = nullptr;
        JUnitUtil::tearDown();
    }
