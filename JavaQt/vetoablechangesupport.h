#ifndef VETOABLECHANGESUPPORT_H
#define VETOABLECHANGESUPPORT_H

#include <QObject>
#include "changelistenermap.h"
#include "vetoablechangelistener.h"
#include <QVector>
#include <QMap>

class VetoableChangeListenerMap;
class VetoableChangeListener;
class PropertyChangeEvent;
class VetoableChangeSupport : public QObject
{
 Q_OBJECT
public:
 explicit VetoableChangeSupport(QObject *source);
 /*public*/ void addVetoableChangeListener(VetoableChangeListener* listener);
 /*public*/ void removeVetoableChangeListener(VetoableChangeListener* listener);

 /*public*/ void fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue);
//         throws PropertyVetoException;
 /*public*/ void fireVetoableChange(QString propertyName, int oldValue, int newValue);
//         throws PropertyVetoException ;
 /*public*/ void fireVetoableChange(QString propertyName, bool oldValue, bool newValue);
//         throws PropertyVetoException
 /*public*/ void fireVetoableChange(PropertyChangeEvent* event);
 /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners();
 /*public*/ void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener);
 /*public*/ void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener);
 /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners(QString propertyName);
 /*public*/ /*final*/ VetoableChangeListener* extract(VetoableChangeListener* listener) ;

signals:
 void vetoablePropertyChange(PropertyChangeEvent*);

public slots:
private:
 QObject* source;
 VetoableChangeListenerMap* map = nullptr;
};

/*private*/ /*static*/ /*final*/ class VetoableChangeListenerMap : public ChangeListenerMap<VetoableChangeListener*>
{
 Q_OBJECT
    /*private*/ static /*final*/ QVector<VetoableChangeListener*> EMPTY;// = {};
public:
 /*public*/ /*final*/ VetoableChangeListener* extract(VetoableChangeListener* listener);

protected:
    /*protected*/ QVector<VetoableChangeListener*> newArray(int length);
    /*protected*/ VetoableChangeListener* newProxy(QString name, VetoableChangeListener* listener);

};

#endif // VETOABLECHANGESUPPORT_H
