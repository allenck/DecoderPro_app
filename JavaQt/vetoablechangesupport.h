#ifndef VETOABLECHANGESUPPORT_H
#define VETOABLECHANGESUPPORT_H

#include <QObject>

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

signals:
 void vetoablePropertyChange(PropertyChangeEvent*);

public slots:
private:
 QObject* source;
};

#endif // VETOABLECHANGESUPPORT_H
