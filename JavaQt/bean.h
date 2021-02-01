#ifndef BEAN_H
#define BEAN_H

#include "unboundbean.h"
#include "propertychangeprovider.h"

class PropertyChangeListener;
class PropertyChangeEvent;
class PropertyChangeSupport;

class Bean : public UnboundBean, public PropertyChangeProvider
{
 Q_OBJECT
 Q_INTERFACES(PropertyChangeProvider)
public:
  Bean(QObject *parent = 0);
  /*protected*/
  Bean(bool notifyOnEDT, QObject *parent = 0);
  ~Bean() {}
  Bean(const Bean&) : UnboundBean() {}

 virtual /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 virtual /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
 virtual /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
 virtual /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName);
 virtual /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 virtual /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
 virtual /*public*/ QString getClass();

signals:
// void propertyChange(PropertyChangeEvent*);

public slots:
protected:
 /**
  * Provide a {@link java.beans.PropertyChangeSupport} helper.
  */
 /*protected*/ /*final*/ PropertyChangeSupport* propertyChangeSupport;// = new PropertyChangeSupport(this);
 /*protected*/ void firePropertyChange(QString key, int oldValue, int value);
 /*protected*/ void firePropertyChange(QString key, QVariant oldValue, QVariant value);
 /*protected*/ void fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue);
 /*protected*/ void fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue);
 /*protected*/ void fireIndexedPropertyChange(QString propertyName, int index, int oldValue, int newValue);
 /*protected*/ void firePropertyChange(QString key, bool oldValue, bool value);
 /*protected*/ void firePropertyChange(PropertyChangeEvent* evt);

friend class ManagerDefaultsConfigPane;
friend class SATableModel;
friend class ManagerDefaultSelector;
friend class UserMessagePreferencesPane;
friend class AmpMeterFrame;
friend class RosterFrame;
};
Q_DECLARE_METATYPE(Bean)
#endif // BEAN_H
