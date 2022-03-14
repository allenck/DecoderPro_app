#ifndef ABSTRACTMANAGERTESTBASE_H
#define ABSTRACTMANAGERTESTBASE_H

#include <QObject>
#include "proxymanager.h"
#include "propertychangelistener.h"

class AbstractManagerTestBase : public QObject
{
 Q_OBJECT
public:
 explicit AbstractManagerTestBase(QObject *parent = nullptr);

signals:

public slots:
 /*public*/ /*final*/ void testManagerDataListenerAddAndRemove();
 /*public*/ /*final*/ void testPropertyChangeListenerAddAndRemove();
 /*public*/ /*final*/ void testVetoableChangeListenerAddAndRemove();
 /*public*/ void testMakeSystemName();

protected:
 // Manager<E> under test - setUp() loads this
 /*protected*/ Manager* _manager = nullptr;

};

class PropertyChangeListenerO2 : public QObject, public PropertyChangeListener {
Q_OBJECT
Q_INTERFACES(PropertyChangeListener)
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* /*evt*/);
    QObject* pself() {return (QObject*)this;}public slots:
};

class VetoableChangeListenerO1 : public QObject, public VetoableChangeListener
{
 Q_OBJECT
Q_INTERFACES(VetoableChangeListener)public:
      //@Override
      /*public*/ void vetoableChange(PropertyChangeEvent* /*evt*/) throw (PropertyVetoException);
QObject* self() {return (QObject*)this;}
};
#endif // ABSTRACTMANAGERTESTBASE_H
