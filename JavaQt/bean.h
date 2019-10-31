#ifndef BEAN_H
#define BEAN_H

#include <QObject>

class PropertyChangeListener;
class PropertyChangeEvent;
class PropertyChangeSupport;
class Bean : public QObject
{
 Q_OBJECT
public:
 explicit Bean(QObject *parent = 0);
 virtual /*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
 virtual /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
 virtual /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
 virtual /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName);
 virtual /*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
 virtual /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);

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
};

#endif // BEAN_H
