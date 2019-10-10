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
 /*protected*/ ProxyManager* l = nullptr;

};

class PropertyChangeListenerO2 : public PropertyChangeListener {
Q_OBJECT
    //@Override
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt) {
        // do nothing
    }
};
class VetoableChangeListenerO1 : public VetoableChangeListener
{
 Q_OBJECT
public:
      //@Override
      /*public*/ void vetoableChange(PropertyChangeEvent evt) throw (PropertyVetoException) {
          // do nothing
      }
};
#endif // ABSTRACTMANAGERTESTBASE_H
