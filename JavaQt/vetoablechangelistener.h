#ifndef VETOABLEPROPERTYCHANGELISTENER_H
#define VETOABLEPROPERTYCHANGELISTENER_H
#include "eventlistener.h"
#include "exceptions.h"

class PropertyChangeEvent;
class PropertyVetoException : public Exception
{
 PropertyVetoException(QString msg = "") : Exception(msg) {}
 ~PropertyVetoException() throw() {}
 PropertyVetoException(const PropertyVetoException&) : Exception() {}
};

class VetoableChangeListener : public EventListener
{
 Q_OBJECT
public:
 VetoableChangeListener(QObject* parent = 0);
public slots:
 virtual void vetoableChange(PropertyChangeEvent* evt)
                            throw (PropertyVetoException);

};


#endif // VETOABLEPROPERTYCHANGELISTENER_H
