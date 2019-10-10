#ifndef BEAN_H
#define BEAN_H

#include <QObject>

class PropertyChangeEvent;
class PropertyChangeSupport;
class Bean : public QObject
{
 Q_OBJECT
public:
 explicit Bean(QObject *parent = 0);

signals:
 void propertyChange(PropertyChangeEvent*);

public slots:
protected:
 /**
  * Provide a {@link java.beans.PropertyChangeSupport} helper.
  */
 /*protected*/ /*final*/ PropertyChangeSupport* propertyChangeSupport;// = new PropertyChangeSupport(this);
 /*protected*/ void firePropertyChange(QString key, int oldValue, int value);
 /*protected*/ void firePropertyChange(QString key, QVariant oldValue, QVariant value);
 /*protected*/ void fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue);
friend class ManagerDefaultsConfigPane;
friend class SATableModel;
friend class ManagerDefaultSelector;
};

#endif // BEAN_H
