#ifndef VETOABLECHANGESUPPORT_H
#define VETOABLECHANGESUPPORT_H

#include <QObject>
#include "changelistenermap.h"
#include "vetoablechangelistener.h"
#include <QVector>
#include <QMap>
#include "java_vetoablechangesupport.h"
#include "propertychangesupport.h"
#include "vetoablechangeprovider.h"
#include "vetoablechangefirer.h"

class VetoableChangeListenerMap;
class VetoableChangeListener;
class PropertyChangeEvent;
class VetoableChangeSupport :  public PropertyChangeSupport, public VetoableChangeProvider, public VetoableChangeFirer
{
  Q_OBJECT
  Q_INTERFACES( VetoableChangeProvider VetoableChangeFirer PropertyChangeProvider)

public:
  explicit VetoableChangeSupport( QObject* parent=nullptr);
  /*public*/ void addVetoableChangeListener(VetoableChangeListener* listener) override;
  /*public*/ void addVetoableChangeListener(/*@CheckForNull*/ QString propertyName,/* @CheckForNull*/ VetoableChangeListener* listener) override;
  /*public*/ QVector<VetoableChangeListener *> *getVetoableChangeListeners() override;
  /*public*/ QVector<VetoableChangeListener*>* getVetoableChangeListeners(QString propertyName) override;
  /*public*/ void removeVetoableChangeListener(VetoableChangeListener* listener)override;
  /*public*/ void removeVetoableChangeListener(/*@CheckForNull*/ QString propertyName, /*@CheckForNull*/ VetoableChangeListener* listener)override;

  /*public*/ void fireVetoableChange(QString propertyName, bool oldValue, bool newValue) /*throw (PropertyVetoException)*/ override;
  /*public*/ void fireVetoableChange(PropertyChangeEvent* event) /*throw (PropertyVetoException)*/ override;
  /*public*/ void fireVetoableChange(QString propertyName, int oldValue, int newValue) /*throw (PropertyVetoException)*/ override;
  /*public*/ void fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue) /*throw (PropertyVetoException)*/ override;

  QObject* vself() override{return (QObject*)this;}
signals:

public slots:
private:

 protected:
 /**
  * Provide a {@link java.beans.VetoableChangeSupport} helper.
  */
 /*protected*/ /*final*/ Java_VetoableChangeSupport* vetoableChangeSupport = new Java_VetoableChangeSupport(this->vself());
};

Q_DECLARE_INTERFACE(VetoableChangeSupport, "VetoableChangeSupport")
#endif // VETOABLECHANGESUPPORT_H
