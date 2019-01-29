#ifndef VETOABLEPROPERTYCHANGELISTENER_H
#define VETOABLEPROPERTYCHANGELISTENER_H
#include "eventlistener.h"
#include "propertyvetoexception.h"

class PropertyChangeEvent;

class VetoableChangeListener : public EventListener
{
 Q_OBJECT
public:
 VetoableChangeListener();
public slots:
 virtual void vetoableChange(PropertyChangeEvent* evt) throw (PropertyVetoException);
};


#endif // VETOABLEPROPERTYCHANGELISTENER_H
