#ifndef VETOABLEPROPERTYCHANGELISTENER_H
#define VETOABLEPROPERTYCHANGELISTENER_H
#include "eventlistener.h"
#include "propertyvetoexception.h"

class PropertyChangeEvent;

class VetoableChangeListener :  public EventListener
{
 //Q_OBJECT
 Q_INTERFACES(EventListener)
public:
 VetoableChangeListener();
 QObject* self() {return (QObject*)this;}

public slots:
 virtual void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException)*/;
};

Q_DECLARE_INTERFACE(VetoableChangeListener, "VetoableChangeListener")
#endif // VETOABLEPROPERTYCHANGELISTENER_H
