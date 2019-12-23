#ifndef VETOABLEPROPERTYCHANGELISTENER_H
#define VETOABLEPROPERTYCHANGELISTENER_H
#include "eventlistener.h"
#include "propertyvetoexception.h"

class PropertyChangeEvent;

class VetoableChangeListener : public QObject, public EventListener
{
 Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 VetoableChangeListener();
 QObject* self() {return (QObject*)this;}

public slots:
 virtual void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException);
};


#endif // VETOABLEPROPERTYCHANGELISTENER_H
