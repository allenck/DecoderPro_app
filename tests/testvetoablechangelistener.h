#ifndef TESTVETOABLECHANGELISTENER_H
#define TESTVETOABLECHANGELISTENER_H

#include <vetoablechangelistener.h>

class TestVetoableChangeListener : public QObject, public VetoableChangeListener
{
  Q_OBJECT
  Q_INTERFACES(VetoableChangeListener)
 public:
  TestVetoableChangeListener();
  /*public*/  void vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/;
  /*public*/  PropertyChangeEvent* getLastEvent();
  /*public*/  QList<PropertyChangeEvent*> getEvents();
  /*public*/  void clear();
  /*public*/  void throwNext(QString mess);
  /*public*/  bool willThrowNext();

  QObject* self() override {return this;}

 private:
  /*private*/ QString _throwNext = "";
  /*private*/ /*final*/ QList<PropertyChangeEvent*> events = QList<PropertyChangeEvent*>();

};

#endif // TESTVETOABLECHANGELISTENER_H
