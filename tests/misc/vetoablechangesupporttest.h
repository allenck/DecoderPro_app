#ifndef VETOABLECHANGESUPPORTTEST_H
#define VETOABLECHANGESUPPORTTEST_H

#include <QObject>
#include "vetoablechangesupport.h"

class TestVetoableChangeListener;
class VetoableChangeSupportTest : public QObject
{
  Q_OBJECT
 public:
  explicit VetoableChangeSupportTest(QObject *parent = nullptr);
  Q_INVOKABLE /*public*/  void setup();
  Q_INVOKABLE /*public*/  void tearDown();

 public slots:
  /*public*/  void testFireVetoableChange_String_int_boolean_boolean();
  /*public*/  void testFireVetoableChange_String_int_int_int();
  /*public*/  void testFireVetoableChange_String_int_Object_Object();
  /*public*/  void testFireVetoableChange_VetoableChangeEvent();
  /*public*/  void testAddVetoableChangeListener_VetoableChangeListener();
  /*public*/  void testAddVetoableChangeListener_String_VetoableChangeListener();
  /*public*/  void testRemoveVetoableChangeListener_VetoableChangeListener();
  /*public*/  void testRemoveVetoableChangeListener_String_VetoableChangeListener();

 signals:

 private:
  /*private*/ VetoableChangeSupport* instance;
  /*private*/ TestVetoableChangeListener* listener;
  /*private*/ static QString PROPERTY;// = "property";
  /*private*/ static QString VETO;// = "veto";

};

#endif // VETOABLECHANGESUPPORTTEST_H
